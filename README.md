# UE5 Android WebView Plugin

This plugin enables communication between Unreal Engine 5 and a WebView on Android devices (i.e. Oculus headsets). Importantly, it lets webapps loaded into UE5 webviews send messages to the parent UE5 runtime without the runtime having to rely on parsing innerHTML content or document.titles, or setting up listeners to page load events or URL change events, all of which seem to utterly suck on Android.

## Features

- Bidirectional communication between UE5 and web content
- Blueprint-friendly API for easy use in both C++ and Blueprint projects
- Automatic Android manifest and build process configuration

## Installation

1. Clone this repository into your UE5 project's `Plugins` directory:
   ```
   git clone https://github.com/boomskats/ue5-android-webview-chatter.git YourProject/Plugins/AndroidWebViewPlugin
   ```
2. Rebuild your project
3. Enable the plugin in your project settings

## Usage

### C++ Example

1. Include the necessary headers in your C++ file:
   ```cpp
   #include "WebMessageHandler.h"
   #include "WebViewPlugin.h"
   ```

2. Send a message to the web content:
   ```cpp
   FWebViewPluginModule::Get().SendMessageToWeb("Hello from UE5!");
   ```

3. Receive messages from web content:
   ```cpp
   // In your class declaration
   UFUNCTION()
   void OnWebMessageReceived(const FString& Message);

   // In your class implementation
   void AYourClass::BeginPlay()
   {
       Super::BeginPlay();
       
       if (UWebMessageHandler* Handler = FWebViewPluginModule::Get().WebMessageHandler)
       {
           Handler->OnWebMessageReceived.AddDynamic(this, &AYourClass::OnWebMessageReceived);
       }
   }

   void AYourClass::OnWebMessageReceived(const FString& Message)
   {
       UE_LOG(LogTemp, Log, TEXT("Received message from web: %s"), *Message);
       // Handle the message
   }
   ```

### Web Content Example

In your web content, you can send and receive messages like this:

```javascript
// Send a message to UE5
window.AndroidBridge.sendMessageToUE5("Hello from Web!");

// Receive messages from UE5
window.onMessageFromUE5 = function(message) {
    console.log("Received message from UE5:", message);
    // Handle the message
};
```

## Configuration

The plugin should automatically configures the necessary Android settings. However, you can customize the WebView setup by modifying the `WebViewPlugin_UPL.xml` file in the `Build/Android/Java` directory.

## Requirements

- Unreal Engine 5.0 or later
- Android SDK 21 or later

## License

This plugin is released under the MIT License. See the LICENSE file for details.
