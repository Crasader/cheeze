LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

CPP_FILES := $(shell find $(LOCAL_PATH)/../../../Classes -name *.cpp | grep -v "\#")
CPP_FILES += $(LOCAL_PATH)/../../../Vendor/lib/Touchable.cpp
CPP_FILES += $(LOCAL_PATH)/../../../Vendor/lib/ImageManager.cpp
CPP_FILES += $(LOCAL_PATH)/../../../Vendor/lib/BGMPlayer.cpp
CPP_FILES += $(shell find $(LOCAL_PATH)/../../../Vendor/CCSocialShare/CCSocialShare/android -name *.cpp)
CPP_FILES += $(shell find $(LOCAL_PATH)/../../../Vendor/CCFirebase/Classes -name *.cpp)
CPP_FILES += $(shell find $(LOCAL_PATH)/../../../Vendor/CCFirebase/proj.android -name *.cpp)
CPP_FILES += $(shell find $(LOCAL_PATH)/../../../Vendor/CCLocalNotification/Classes -name *.cpp)
CPP_FILES += $(shell find $(LOCAL_PATH)/../../../Vendor/CCLocalNotification/proj.android -name *.cpp)


LOCAL_SRC_FILES := hellocpp/main.cpp
LOCAL_SRC_FILES += $(CPP_FILES:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(shell find $(LOCAL_PATH)/../../../Classes -type d)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../cocos2d/cocos/ui
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Vendor/lib
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Vendor/PluginXProtocols/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../cocos2d/external/curl/include/android
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Vendor/CCSocialShare/CCSocialShare
LOCAL_C_INCLUDES += /opt/boxen/homebrew/Cellar/openssl/1.0.2e_1/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Vendor/CCFirebase/Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Vendor/CCLocalNotification/Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
