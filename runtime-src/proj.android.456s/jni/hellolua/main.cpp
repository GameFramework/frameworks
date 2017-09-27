#include "AppDelegate.h"
#include "cocos2d.h"
#include <android/log.h>

#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include "Platform/KPlatformLogin.h"

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

void cocos_android_app_init (JNIEnv* env) {
    LOGD("cocos_android_app_init");
    AppDelegate *pAppDelegate = new AppDelegate();
}

extern "C" {
	JNIEXPORT void JNICALL Java_com_sdk_mgr_utility_callEventToLua(JNIEnv* env, jobject obj, jstring eventType, jstring response, jstring token){
		LOGD("javaToC++:callEventToLua");
		KPlatformLogin::getInstance()->androidEventToLua(JniHelper::jstring2string(eventType), JniHelper::jstring2string(response), JniHelper::jstring2string(token));
	}

	JNIEXPORT void JNICALL Java_com_sdk_mgr_utility_setPlatformId(JNIEnv* env, jobject obj, jint platformId){
		LOGD("javaToC++:setPlatformId");
		KPlatformLogin::getInstance()->setPlatformId(platformId);
	}
}
