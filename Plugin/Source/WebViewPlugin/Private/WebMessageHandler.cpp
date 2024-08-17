#include "WebMessageHandler.h"
#include "WebViewPlugin.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif

UWebMessageHandler::UWebMessageHandler()
{
    // Constructor logic if needed
}

void UWebMessageHandler::SendMessageToWeb(const FString& Message)
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
#else
    // Implement for other platforms if needed
    UE_LOG(LogTemp, Warning, TEXT("SendMessageToWeb not implemented for this platform"));
#endif
}

void UWebMessageHandler::NativeOnMessageFromWeb(const FString& Message)
{
    // Call the Blueprint event
    OnMessageFromWeb(Message);

    // Broadcast the delegate
    OnWebMessageReceived.Broadcast(Message);
}

#if PLATFORM_ANDROID
void UWebMessageHandler::JNI_OnMessageFromWeb(JNIEnv* env, jobject thiz, jstring message)
{
    const char* nativeMessage = env->GetStringUTFChars(message, 0);
    FString MessageString(nativeMessage);
    env->ReleaseStringUTFChars(message, nativeMessage);

    // Get the WebMessageHandler instance from the plugin module
    if (FWebViewPluginModule::IsAvailable())
    {
        UWebMessageHandler* Handler = FWebViewPluginModule::Get().WebMessageHandler;
        if (Handler)
        {
            // Call the native handler method
            Handler->NativeOnMessageFromWeb(MessageString);
        }
    }
}
#endif
