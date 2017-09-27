LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
$(call import-add-path,$(LOCAL_PATH)/../..)

LOCAL_MODULE := cocos2dlua_shared
LOCAL_SHARED_LIBRARIES += libYvImSdk

LOCAL_MODULE_FILENAME := libcocos2dlua

LOCAL_SRC_FILES := \
../../Classes/AppDelegate.cpp \
hellolua/main.cpp \
$(subst $(LOCAL_PATH)/,, \
$(wildcard $(LOCAL_PATH)/../../Classes/AutoUpdate/*.cpp) \
$(wildcard $(LOCAL_PATH)/../../Classes/Socket/*.cpp) \
$(wildcard $(LOCAL_PATH)/../../Classes/PBC/*.c) \
$(wildcard $(LOCAL_PATH)/../../Classes/Platform/*.cpp) \
$(wildcard $(LOCAL_PATH)/../../Classes/YunVaSDK/*.cpp) \
)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes\
$(LOCAL_PATH)/../../Classes/YunVaSDK\
$(LOCAL_PATH)/../../IM_SDK/include

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END

LOCAL_STATIC_LIBRARIES := cocos2d_lua_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,scripting/lua-bindings/proj.android)
$(call import-module,.)
$(call import-module,IM_SDK)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
