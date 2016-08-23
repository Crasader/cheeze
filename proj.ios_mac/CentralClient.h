#ifndef __okeya__CentralClient__
#define __okeya__CentralClient__

#include "ProtocolIAP.h"
#include "PluginManager.h"
#include "network/HttpRequest.h"
#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "platform/CCFileUtils.h"
#include "RestClient.h"
#include <ctime>
#include <future>

using namespace cocos2d;
using namespace cocos2d::plugin;
using namespace cocos2d::network;
using namespace cocos2d::extension;

class PlayerBase;

class CentralClient
{
public:
#if TARGET_IPHONE_SIMULATOR
    static constexpr auto CENTRAL_API_URL = "http://localhost:3000";
#elif COCOS2D_DEBUG
    static constexpr auto CENTRAL_API_URL = "https://ocentral-api-stg.herokuapp.com/";
    //static constexpr auto CENTRAL_API_URL = "http://192.168.0.2:3000";
#else
    static constexpr auto CENTRAL_API_URL = "https://ocentral-api.herokuapp.com/";
#endif
    //static constexpr auto CENTRAL_API_URL = "http://yalab.example.com:3000";
    
    static constexpr auto AMOUNT = "amount";
    static constexpr auto ITEM_ID = "itemId";
    using ChargeSyncCallback = std::function<void(const int status, ValueMap& vmap)>;
    CentralClient() = default;
    virtual ~CentralClient() = default;
    static const int ChargeNone;
    static const int INVALID_ITEM_BOUGHT;
    static CentralClient* getInstance();
    void init(PlayerBase* player, std::function<void(void)> callback);
    void buyCharge(PlayerBase* player, const int price, const ChargeSyncCallback& callback);
    void getCurrentCharge(PlayerBase* player, const ChargeSyncCallback& callback);
    void syncCharges(PlayerBase* player, const ValueMap& charges, const ChargeSyncCallback& callback);
    void postPlayLog(PlayerBase* player, const std::string& data);
    void s3backup(PlayerBase* player, const ccHttpRequestCallback callback);
    void backup(PlayerBase* player, const ccHttpRequestCallback callback, const std::string& password = "");
    void s3restore(PlayerBase* player, const ccHttpRequestCallback callback);
    const std::string getS3Path(PlayerBase* player);
    void downloadAssets(const std::function<void(EventAssetsManagerEx* event)>& callback);
    void savePlayData(ValueMap& dict);
    const ValueMap loadPlayData();
    void valueMapCompact(ValueMap& valueMap);
    void valueVectorCompact(ValueVector& valueVector);
    void swapPlayer(PlayerBase* player, const std::string& playerId, const std::string& password, const ccHttpRequestCallback callback);
    
    inline const std::string getBackupFilePath(){
        return FileUtils::getInstance()->getWritablePath() + "/backup.plist";
    }
    void printValueMap(cocos2d::ValueMap& vmap);
    void addSpriteCaches(const std::function<void(int)>& callback, const std::function<void(const int count, const int maxCount)>& progress, const std::string prefix="");
    void postMessage(const std::string& token, const std::string& name, const std::string& content, const std::function<void(void)>& successCallback, const std::function<void(void)>& errorCallback);
private:
    void httpResponseToValueMap(HttpResponse* pResponse, Value& value);
    const std::string valueToStr(Value& value);
    inline const std::string getAssetDir(){ return FileUtils::getInstance()->getWritablePath() + "/Reources"; }
    void putS3(const std::string& fpath, const std::string& data, const std::string& header, const ccHttpRequestCallback callback);
    void getS3(const std::string& fpath, const std::string& header, const ccHttpRequestCallback);
    void paymentSuccess(PlayerBase* player, const std::string& paymentId, const ChargeSyncCallback& callback, int status, std::string& receit);
    void createUser(PlayerBase* player, std::function<void(void)> callback);
    static CentralClient* _singleton;
    bool _init { false };
    ProtocolIAP* s_protocolIAP;
    std::atomic<int> _spriteLoadingCounter{ 0 };
    void runChargeSyncCallback(const ChargeSyncCallback& callback, HttpResponse* response);
public:
    const std::string SHA256Hash(const std::string& key);
};

#endif /* defined(__okeya__CentralClient__) */
