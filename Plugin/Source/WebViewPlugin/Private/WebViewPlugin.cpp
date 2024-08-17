// WebViewPlugin.cpp
#include "WebViewPlugin.h"
#include "WebMessageHandler.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif

void FWebViewPlugin::StartupModule()
{
    // Create WebMessageHandler
    WebMessageHandler = NewObject<UWebMessageHandler>();
}

void FWebViewPlugin::ShutdownModule()
{
    // Cleanup if necessary
}

void FWebViewPlugin::SendMessageToWeb(const FString& Message)
{
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        const char* MethodName = "sendMessageToWeb";
        const char* Signature = "(Ljava/lang/String;)V";
        jstring JavaString = Env->NewStringUTF(TCHAR_TO_UTF8(*Message));
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, MethodName, Signature), JavaString);
        Env->DeleteLocalRef(JavaString);
    }
#endif
}

extern "C" void Java_com_epicgames_unreal_GameActivity_1UEDelegate_nativeOnMessageFromWeb(JNIEnv* env, jobject thiz, jstring message)
{
    const char* nativeMessage = env->GetStringUTFChars(message, 0);
    FString MessageString(nativeMessage);
    env->ReleaseStringUTFChars(message, nativeMessage);

    // Assuming WebMessageHandler is accessible here
    if (WebMessageHandler)
    {
        WebMessageHandler->NativeOnMessageFromWeb(MessageString);
    }
}
