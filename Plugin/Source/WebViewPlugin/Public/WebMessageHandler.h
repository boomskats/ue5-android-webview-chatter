#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WebMessageHandler.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWebMessageReceived, const FString&, Message);

/**
 * Handles communication between UE5 and web interface
 */
UCLASS(BlueprintType)
class WEBVIEWPLUGIN_API UWebMessageHandler : public UObject
{
    GENERATED_BODY()

public:
    UWebMessageHandler();

    /**
     * Sends a message to the web interface
     * @param Message - The message to send
     */
    UFUNCTION(BlueprintCallable, Category = "Web Communication")
    void SendMessageToWeb(const FString& Message);

    /**
     * Receives a message from the web interface
     * @param Message - The received message
     */
    void NativeOnMessageFromWeb(const FString& Message);

    /**
     * Blueprint event that fires when a message is received from the web
     */
    UFUNCTION(BlueprintImplementableEvent, Category = "Web Communication")
    void OnMessageFromWeb(const FString& Message);

    /**
     * Delegate that fires when a message is received from the web
     */
    UPROPERTY(BlueprintAssignable, Category = "Web Communication")
    FOnWebMessageReceived OnWebMessageReceived;

#if PLATFORM_ANDROID
    /**
     * JNI method to be called from Java
     */
    static void JNI_OnMessageFromWeb(JNIEnv* env, jobject thiz, jstring message);
#endif
};
