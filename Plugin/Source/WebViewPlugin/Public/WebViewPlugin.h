#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class UWebMessageHandler;

class FWebViewPluginModule : public IModuleInterface
{
public:
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    /**
     * Singleton-like access to this module's interface.  This is just for convenience!
     * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
     *
     * @return Returns singleton instance, loading the module on demand if needed
     */
    static inline FWebViewPluginModule& Get()
    {
        return FModuleManager::LoadModuleChecked<FWebViewPluginModule>("WebViewPlugin");
    }

    /**
     * Checks to see if this module is loaded and ready.
     *
     * @return True if the module is loaded and ready to use
     */
    static inline bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded("WebViewPlugin");
    }

    /** Sends a message to the web interface */
    void SendMessageToWeb(const FString& Message);

    /** The WebMessageHandler instance */
    UWebMessageHandler* WebMessageHandler;
};
