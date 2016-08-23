#include "platform/CCCommon.h"
#include "CentralClient.h"
#include "Env.h"
#include "EnvPrivate.h"
#include "RestClient.h"
#include "valuemapwriter.h"
#include "CocosGUI.h"
#include "PlayerBase.h"
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include "SupportFunctions.h"
#ifdef __APPLE__
#include "TargetConditionals.h"
#include "DoNotBackup.h"
#endif

static constexpr auto CENTRAL_S3_URL = "https://oke-ya-central.s3.amazonaws.com";

const char* PAYMENT_USER_TOKEN = "paymentUserToken";
const int CentralClient::ChargeNone = -1;
const int CentralClient::INVALID_ITEM_BOUGHT = -1;

using namespace cocos2d::ui;

CentralClient* CentralClient::getInstance()
{
    static CentralClient s_instance;
    return &s_instance;
}

void CentralClient::init(PlayerBase* player, std::function<void(void)> callback)
{
    player->load();
    if(!player->hasToken()){
        createUser(player, callback);
    }else{
        callback();
    }
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    TIAPDeveloperInfo pGoogleInfo;
    pGoogleInfo["GooglePlayAppKey"] = GOOGLE_APPKEY;
    
    if(pGoogleInfo.empty()) {
        char msg[256] = { 0 };
        sprintf(msg, "Google App Key info is empty. PLZ fill your Google App Key info in %s(nearby line %d)", __FILE__, __LINE__);
        MessageBox(msg, "Google IAP Warning");
    }
    s_protocolIAP = dynamic_cast<ProtocolIAP*>(PluginManager::getInstance()->loadPlugin("IAPGooglePlay"));
    s_protocolIAP->configDeveloperInfo(pGoogleInfo);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    if(_init){
        return;
    }
    TIAPDeveloperInfo info;
    s_protocolIAP = dynamic_cast<ProtocolIAP*>(PluginManager::getInstance()->loadPlugin("IOSIAP"));
    
    auto itr = SKU.begin();
    std::string productKeys = (*itr).second;
    itr ++;
    for(; itr != SKU.end(); itr++) {
        productKeys += "," + (*itr).second;
    }
    info["iapKeys"] = productKeys;
    s_protocolIAP->configDeveloperInfo(info);
#endif

#if COCOS2D_DEBUG
    s_protocolIAP->setDebugMode(true);
#endif
    
    _init = true;
}

void CentralClient::buyCharge(PlayerBase* player, const int price, const ChargeSyncCallback& callback)
{
    TProductInfo info;
    const std::string IAPId = SKU.at(price);
    RestClient::PostData postData;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    postData["platform"] = "googleplay";
    info["IAPId"] = IAPId;
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    postData["platform"] = "appstore";
    info["productId"] = IAPId;
#endif
    auto userToken = player->getToken();
    if(userToken.length() < 1){
        MessageBox("API エラーにより現在課金が行えません", "もうしわけございません");
        return;
    }

    postData["iap_id"] = IAPId;
    postData["token"] = userToken;
    postData["price"] = std::to_string(price);

    RestClient::getInstance()->post("/payments",  postData, [&, callback, info, player](HttpClient* client, HttpResponse* response){
        if(response->isSucceed()){
            auto v = *response->getResponseData();
            const std::string paymentId(v.begin(), v.end());
#if COCOS2D_DEBUG
            std::string receipt = "";
            paymentSuccess(player, paymentId, callback, PayResultCode::kPaySuccess, receipt);
            return;
#endif
            s_protocolIAP->payForProduct(info, [&, callback, paymentId, info, player](int status, std::string& receipt){
                log("Payment result %i %s", status, receipt.c_str());
//                s_protocolIAP->consumeForProduct(info);
                if(status == PayResultCode::kPaySuccess){
                    paymentSuccess(player, paymentId, callback, status, receipt);
                }else{
                    HttpRequest req;
                    HttpResponse res(&req);
                    runChargeSyncCallback(callback, &res);
                }
            });
        }else{
            MessageBox("API エラーにより現在課金が行えません", "もうしわけございません");
        }
    });
}

void CentralClient::createUser(PlayerBase* player, std::function<void(void)> callback)
{
    RestClient::PostData postData;
    postData["game_id"] = GAME_ID;
    RestClient::getInstance()->post("/players", postData, [&, player, callback](HttpClient* client, HttpResponse* response){
        if(response->isSucceed()){
            auto v = *response->getResponseData();
            const std::string body(v.begin(), v.end());
            player->setIdToken(body);
            player->save();
            callback();
        }else{
            callback();
        }
    });
}

void CentralClient::paymentSuccess(PlayerBase* player, const std::string& paymentId, const ChargeSyncCallback& callback, int status, std::string& receipt)
{
    RestClient::PostData postData;
    postData["receipt_data"] = receipt;
    postData["token"] = player->getToken();
    log("token %s", player->getToken().c_str());
    auto url = "/payments/" + paymentId + ".json";
    RestClient::getInstance()->put(url, postData, [&, callback](HttpClient* client, HttpResponse* response){
        runChargeSyncCallback(callback, response);
    });
}

void CentralClient::getCurrentCharge(PlayerBase* player, const ChargeSyncCallback& callback)
{
    RestClient::getInstance()->get("/payments.json?token=" + player->getToken(), [&, callback](HttpClient* client, HttpResponse* response){
        runChargeSyncCallback(callback, response);
    });
}

void CentralClient::syncCharges(PlayerBase* player, const ValueMap& charges, const ChargeSyncCallback& callback)
{
    RestClient::PostData postData;
    postData["token"] = player->getToken();
    for(auto itr = charges.cbegin(); itr != charges.cend(); itr++){
        auto& v = itr->second.asValueMap();
        auto time = itr->first;
        postData["charges[" + time + "][amount]"] = std::to_string(v.at(AMOUNT).asInt());
        postData["charges[" + time + "][item_id]"] = std::to_string(v.at(ITEM_ID).asInt());
    }
    RestClient::getInstance()->post("/charges.json", postData, [&, callback](HttpClient* client, HttpResponse* response){
        auto v = *response->getResponseData();
        const std::string body(v.begin(), v.end());
        log("%s", body.c_str());
        runChargeSyncCallback(callback, response);
    });
}

void CentralClient::runChargeSyncCallback(const ChargeSyncCallback& callback, HttpResponse* response)
{
    ValueMap vmap;
    Value value(vmap);
    if(response->isSucceed()){
        httpResponseToValueMap(response, value);
    }
    callback(static_cast<int>(response->getResponseCode()), value.asValueMap());
}

void CentralClient::postPlayLog(PlayerBase* player, const std::string& data)
{
    RestClient::PostData postData;
    postData["token"] = player->getToken();
    RestClient::getInstance()->post("/play_logs", postData, [](HttpClient* client, HttpResponse* response){});
}

const std::string CentralClient::getS3Path(PlayerBase* player)
{
    auto token = player->getToken();
    return  "/" + GAME_ID + "/" + token.substr(0, 3) + "/" + token + ".plist";
}

void CentralClient::backup(PlayerBase* player, const ccHttpRequestCallback callback, const std::string& password)
{
    const auto& playData = player->getPlayData();
    auto token = player->getToken();
    const std::string fpath = getS3Path(player);
    auto v = Value(playData);
    const auto data = valueToStr(v);
    RestClient::PostData postData;
    postData["play_data"] = data;
    if(password.size() > 0){
        postData["password"] = password;
    }
    const auto url = "/players/" + player->getToken() + ".json";
    RestClient::getInstance()->put(url, postData, [callback](HttpClient* client, HttpResponse* response){
        callback(client, response);
    });
}

void CentralClient::s3backup(PlayerBase* player, const ccHttpRequestCallback callback)
{
    const auto& playData = player->getPlayData();
    auto token = player->getToken();
    const std::string fpath = getS3Path(player);
    auto v = Value(playData);
    const auto data = valueToStr(v);
    const auto sha256 = SHA256Hash(data);;
    RestClient::PostData postData;
    postData["hashed_payload"] = sha256;
    postData["method"] = "PUT";
    postData["filename"] = fpath;
    const std::string url = "/players/" + token + "/s3_header";
    RestClient::getInstance()->post(url, postData, [&, data, fpath, callback](HttpClient* client, HttpResponse* response){
        if(response->getResponseCode() != 200){
            callback(client, response);
            return;
        }
        auto v = *response->getResponseData();
        const std::string header(v.begin(), v.end());
        putS3(fpath, data, header, callback);
    });
}

void CentralClient::s3restore(PlayerBase* player, const ccHttpRequestCallback callback)
{
    RestClient::PostData postData;
    postData["hashed_payload"] = SHA256Hash("");;
    postData["method"] = "GET";
    postData["filename"] = getS3Path(player);
    auto token = player->getToken();
    const std::string url = "/players/" + token + "/s3_header";
    auto restClient = RestClient::getInstance();
    restClient->post(url, postData, [&, player, callback](HttpClient* client, HttpResponse* response){
        const std::string fpath = getS3Path(player);
        if(response->getResponseCode() != 200){
            callback(client, response);
            return;
        }
        auto v = *response->getResponseData();
        const std::string header(v.begin(), v.end());
        getS3(fpath, header, [&, player, callback](HttpClient* client, HttpResponse* response){
            if(response->getResponseCode() != 200){
                callback(client, response);
                return;
            }
            auto v = *response->getResponseData();
            const std::string body(v.begin(), v.end());
            ValueMap vmap;
            Value value(vmap);
            httpResponseToValueMap(response, value);
            player->setPlayData(value.asValueMap());
            player->save();
            callback(client, response);
        });
    });
}

void CentralClient::putS3(const std::string& fpath, const std::string& data, const std::string& header, const ccHttpRequestCallback callback)
{
    auto* request = new HttpRequest();
    request->setUrl((CENTRAL_S3_URL + fpath).c_str());
    request->setRequestType(HttpRequest::Type::PUT);
    request->setRequestData(data.c_str(), data.length());
    std::vector<std::string> headers;
    std::istringstream iss(header);
    std::string line;
    while(std::getline(iss, line)){
        headers.push_back(line);
    }
    request->setHeaders(headers);
    request->setResponseCallback([callback](HttpClient* client, HttpResponse* response){
        if(response->getResponseCode() != 200){
            callback(client, response);
            return;
        }
        auto v = *response->getResponseData();
        const std::string body(v.begin(), v.end());
        log("PutS3 finish %s", body.c_str());
        callback(client, response);
    });
    HttpClient::getInstance()->send(request);
    request->release();
}

void CentralClient::getS3(const std::string& fpath, const std::string& header, const ccHttpRequestCallback callback)
{
    auto* request = new HttpRequest();
    request->setUrl((CENTRAL_S3_URL + fpath).c_str());
    request->setRequestType(HttpRequest::Type::GET);
    std::vector<std::string> headers;
    std::istringstream iss(header);
    std::string line;
    while(std::getline(iss, line)){
        headers.push_back(line);
    }
    request->setHeaders(headers);
    request->setResponseCallback(callback);
    HttpClient::getInstance()->send(request);
    request->release();

}


const std::string CentralClient::SHA256Hash(const std::string& key)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, key.c_str(), key.size());
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    log("%s", ss.str().c_str());
    return ss.str();
}


void CentralClient::downloadAssets(const std::function<void(EventAssetsManagerEx* event)>& callback)
{
    std::stringstream ss;
    ss << "Manifests/";
    ss << GAME_ID;
    ss << ".project.";
#if TARGET_IPHONE_SIMULATOR
    ss << "l";
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    ss << "a";
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    ss << "i";
#endif
    
    ss << ".manifest";
    
#if TARGET_IPHONE_SIMULATOR
    ss << ".dev";
#elif COCOS2D_DEBUG
    ss << ".stg";
#else
    ss << ".prod";
#endif
    
    const std::string manifest = ss.str();
    log("manifest %s", manifest.c_str());
    auto destDir = getAssetDir();
#ifdef __APPLE__
    auto futils = FileUtils::getInstance();
    if(!futils->isDirectoryExist(destDir)){
        futils->createDirectory(destDir);
    }
    platform::DoNotBackup::set(destDir);
#endif
    auto assetManager = AssetsManagerEx::create(manifest, destDir);
    assetManager->retain();
    auto eventListener = EventListenerAssetsManagerEx::create(assetManager, [=](EventAssetsManagerEx* event){
        callback(event);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(eventListener, 1);
    assetManager->update();
}

#include <dirent.h>
void CentralClient::addSpriteCaches(const std::function<void(int)>& callback, const std::function<void(const int count, const int maxCount)>& progress, const std::string prefix)
{
    auto assetDir = getAssetDir();
    const std::string cacheExt = ".plist";
    struct dirent *ent;
    DIR *dir;
    std::vector<std::string> plistPaths;
    if((dir = opendir(assetDir.c_str())) != NULL){
        while((ent = readdir (dir)) != NULL){
            auto plist = std::string(ent->d_name);
            std::string::size_type index = plist.find_last_of(".");
            if(index == std::string::npos){
                continue;
            }
            auto extname = plist.substr(index);
            if(extname != cacheExt){
                continue;
            }
            if(prefix.size() > 0 && plist.substr(0, prefix.size()) != prefix){
                continue;
            }
            plistPaths.emplace_back(assetDir + "/" + plist);
        }
        closedir(dir);
    }
    _spriteLoadingCounter = static_cast<int>(plistPaths.size());
#ifdef __APPLE__
    auto ext = "pvr.ccz";
#else
    auto ext = "etc1";
#endif
    auto textureCache = Director::getInstance()->getTextureCache();
    auto maxCount = plistPaths.size();
    for(auto& plistPath: plistPaths){
        const auto texturePath = plistPath.substr(0, plistPath.size() - 5) + ext;
        textureCache->addImageAsync(texturePath, [&, plistPath, callback, progress, maxCount](Texture2D* texture){
            progress(maxCount - _spriteLoadingCounter, maxCount);
            if(texture){
                SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistPath, texture);
            }else{
                SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistPath);
                log("cannot read texture %s", plistPath.c_str());
            }
            _spriteLoadingCounter --;
            if(_spriteLoadingCounter < 1){
                callback(maxCount);
            }
        });
    }
}

void CentralClient::valueMapCompact(ValueMap& valueMap)
{
    auto itr = valueMap.begin();
    while(itr != valueMap.end()){
        auto vtype = itr->second.getType();
        switch(vtype){
            case Value::Type::NONE:{
                itr = valueMap.erase(itr);
                continue;
            }
                break;
            case Value::Type::MAP:{
                valueMapCompact(itr->second.asValueMap());
            }
                break;
            case Value::Type::VECTOR:{
                valueVectorCompact(itr->second.asValueVector());
            }
                break;
            default:
                break;
        }
        itr++;
    }
}

void CentralClient::valueVectorCompact(ValueVector& valueVector)
{
    auto itr = valueVector.begin();
    while(itr != valueVector.end()){
        auto vtype = (*itr).getType();
        switch(vtype){
            case Value::Type::NONE:{
                itr = valueVector.erase(itr);
                continue;
            }
                break;
            case Value::Type::MAP:{
                valueMapCompact((*itr).asValueMap());
            }
                break;
            case Value::Type::VECTOR:{
                valueVectorCompact((*itr).asValueVector());
            }
                break;
            default:
                break;
        }
        itr++;
    }
}

void CentralClient::savePlayData(ValueMap& dict)
{
    valueMapCompact(dict);
    FileUtils::getInstance()->writeToFile(dict, getBackupFilePath());
}

const ValueMap CentralClient::loadPlayData()
{
    return FileUtils::getInstance()->getValueMapFromFile(getBackupFilePath());
}

void CentralClient::printValueMap(cocos2d::ValueMap& vmap)
{
    auto v = Value(vmap);
    log("%s", valueToStr(v).c_str());
}

const std::string CentralClient::valueToStr(Value& value)
{
    std::stringstream ss;
    switch(value.getType()){
        case Value::Type::MAP :{
            ss << "{";
            auto& vmap = value.asValueMap();
            auto size = vmap.size();
            int i = 0;
            for(auto& v: vmap){
                ss << "\"" + v.first + "\"";
                ss << ": ";
                ss << valueToStr(v.second);
                i++;
                if(i < size){
                    ss << ", ";
                }
            }
            ss << "}";
            return ss.str();
            break;
        }
        case Value::Type::VECTOR :{
            ss << "[";
            auto& vec = value.asValueVector();
            auto size = vec.size();
            int i = 0;
            for(auto& v: vec){
                ss << valueToStr(v);
                i++;
                if(i < size){
                    ss << ", ";
                }
            }
            ss << "]";
            return ss.str();
            break;
        }
        case Value::Type::INTEGER :{
            ss << value.asInt();
            return ss.str();
            break;
        }
        case Value::Type::STRING :{
            ss << "\"";
            auto str = value.asString();
            supportfunctions::escapeNL(str);
            ss << str;
            ss << "\"";
            return ss.str();
            break;
        }
        case Value::Type::NONE :{
            return "null";
        }
        case Value::Type::BOOLEAN: {
            if(value.asBool()){
                return "true";
            }else{
                return "false";
            }
        }
        default: {
            CCASSERT(false, "Not defined print type");
        }
    }
    return "";
}

void CentralClient::httpResponseToValueMap(HttpResponse* pResponse, Value& value)
{
    auto code = pResponse->getResponseCode();
    if(code != 200){
        return;
    }
    auto vecChar = pResponse->getResponseData();
    std::string responseBody(vecChar->begin(), vecChar->end());
    if(responseBody.size() < 1){
        return;
    }
    rapidjson::ValueMapWriter writer(value);
    //    GenericStringBuffer< UTF8<> > buffer;
    //    Writer< GenericStringBuffer< UTF8<> > > writer;
    rapidjson::Document doc;
    doc.Parse<0>(responseBody.c_str());
    doc.Accept(writer);

}


void CentralClient::postMessage(const std::string& token, const std::string& name, const std::string& content, const std::function<void(void)>& successCallback, const std::function<void(void)>& errorCallback)
{
    RestClient::PostData postData;
    postData["inquiry[name]"] = name;
    postData["inquiry[content]"] = content;
    postData["inquiry[game_id]"] = GAME_ID;
    postData["token"] = token;
    postData["game_id"] = GAME_ID;
    RestClient::getInstance()->post("/inquiries.json", postData, [&successCallback, &errorCallback](HttpClient* pClient, HttpResponse* pResponse){
        if(pResponse->getResponseCode() == 200){
            successCallback();
        }else{
            errorCallback();
        }
    });
}

void CentralClient::swapPlayer(PlayerBase* player, const std::string& playerId, const std::string& password, const ccHttpRequestCallback callback)
{
    RestClient::PostData postData;
    postData["password"] = password;
    auto token = player->getToken();
    std::string url;
    auto finishCallback =  [&, player, callback](HttpClient* client, HttpResponse* response){
        if(response->getResponseCode() == 200){
            auto v = *response->getResponseData();
            const std::string body(v.begin(), v.end());
            ValueMap vmap;
            Value value(vmap);
            httpResponseToValueMap(response, value);
            player->setPlayData(value.asValueMap());
            player->save();
        }
        callback(client, response);
    };
    if(token.size() > 0){
        postData["player[player_id]"] = playerId;
        url = "/players/" + player->getToken() + "/swap.json";
        RestClient::getInstance()->post(url, postData,finishCallback);
    }else{
        url = "/players/" + playerId + ".json?password=" + password;
        RestClient::getInstance()->get(url, finishCallback);
    }
}
