package com.boomskats.webviewplugin;

import android.webkit.JavascriptInterface;
import com.epicgames.unreal.GameActivity_UEDelegate;
import android.webkit.WebView;

public class JavaWebViewBridge {
    private GameActivity_UEDelegate gameActivity;
    private WebView webView;

    public JavaWebViewBridge(GameActivity_UEDelegate activity, WebView webView) {
        this.gameActivity = activity;
        this.webView = webView;
    }

    @JavascriptInterface
    public void sendMessageToUE5(final String message) {
        gameActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                // Call UE5 C++ method
                gameActivity.nativeOnMessageFromWeb(message);
            }
        });
    }

    public void sendMessageToWeb(final String message) {
        gameActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                webView.loadUrl("javascript:window.onMessageFromUE5('" + message + "')");
            }
        });
    }

    // Method to be called from UE5 C++ code
    public static void sendMessageToWebStatic(final String message) {
        GameActivity_UEDelegate.instance.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                WebView webView = GameActivity_UEDelegate.instance.currentWebView;
                if (webView != null) {
                    webView.loadUrl("javascript:window.onMessageFromUE5('" + message + "')");
                }
            }
        });
    }
}
