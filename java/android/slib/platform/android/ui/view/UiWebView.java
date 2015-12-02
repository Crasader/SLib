package slib.platform.android.ui.view;

import android.content.Context;
import android.graphics.Bitmap;
import android.view.View;
import android.webkit.JavascriptInterface;
import android.webkit.JsPromptResult;
import android.webkit.JsResult;
import android.webkit.WebChromeClient;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import slib.platform.android.Logger;

public class UiWebView extends WebView {
	
	public static UiWebView _create(Context context) {
		try {
			UiWebView ret = new UiWebView(context);
			return ret;
		} catch (Exception e) {
			Logger.exception(e);
		}
		return null;
	}
	
	public static void _load(View view, final String url) {
		if (url == null || url.length() == 0) {
			return;
		}
		if (view instanceof WebView) {
			final WebView wv = (WebView)view;
			wv.post(new Runnable() {
				public void run() {
					try {
						wv.loadUrl(url);						
					} catch (Exception e) {
						Logger.exception(e);
					}
				}
			});
		}
	}
	
	public static void _loadHTML(View view, final String html, final String url) {
		if (view instanceof WebView) {
			final WebView wv = (WebView)view;
			wv.post(new Runnable() {
				public void run() {
					try {
						if (url == null || url.length() == 0) {
							wv.loadData(url, "text/html", "utf-8");
						} else {
							wv.loadDataWithBaseURL(url, html, "text/html", "utf-8", null);
						}						
					} catch (Exception e) {
						Logger.exception(e);
					}
				}
			});
		}
	}

	public static String _getURL(View view) {
		try {
			if (view instanceof WebView) {
				WebView wv = (WebView)view;
				return wv.getUrl();
			}	
		} catch (Exception e) {
			Logger.exception(e);
		}
		return null;
	}
	
	public static String _getTitle(View view) {
		try {
			if (view instanceof WebView) {
				WebView wv = (WebView)view;
				return wv.getTitle();
			}	
		} catch (Exception e) {
			Logger.exception(e);
		}
		return null;
	}
	
	public static void _goBack(View view) {
		if (view instanceof WebView) {
			final WebView wv = (WebView)view;
			wv.post(new Runnable() {
				public void run() {
					try {
						wv.goBack();						
					} catch (Exception e) {
						Logger.exception(e);
					}
				}
			});
		}
	}

	public static void _goForward(View view) {
		if (view instanceof WebView) {
			final WebView wv = (WebView)view;
			wv.post(new Runnable() {
				public void run() {
					try {
						wv.goForward();						
					} catch (Exception e) {
						Logger.exception(e);
					}
				}
			});
		}
	}

	public static void _reload(View view) {
		if (view instanceof WebView) {
			final WebView wv = (WebView)view;
			wv.post(new Runnable() {
				public void run() {
					try {
						wv.reload();						
					} catch (Exception e) {
						Logger.exception(e);
					}
				}
			});
		}
	}

	public static void _runJavaScript(View view, final String script) {
		if (script != null && script.length() > 0) {
			if (view instanceof WebView) {
				final WebView wv = (WebView)view;
				wv.post(new Runnable() {
					public void run() {
						try {
							wv.loadUrl("javascript:" + script);
						} catch (Exception e) {
							Logger.exception(e);
						}
					}
				});
			}				
		}
	}
	
	private static native void nativeOnStartLoad(long instance, String url);
	public static void onStartLoad(View view, String url) {
		long instance = UiView.getInstance(view);
		if (instance != 0) {
			nativeOnStartLoad(instance, url);
		}
	}
	
	private static native void nativeOnFinishLoad(long instance, String url);
	public static void onFinishLoad(View view, String url) {
		long instance = UiView.getInstance(view);
		if (instance != 0) {
			nativeOnFinishLoad(instance, url);
		}
	}

	private static native void nativeOnErrorLoad(long instance, String url, String error);
	public static void onErrorLoad(View view, String url, String error) {
		long instance = UiView.getInstance(view);
		if (instance != 0) {
			nativeOnErrorLoad(instance, url, error);
		}
	}

	private static native void nativeOnMessage(long instance, String msg, String param);
	public static void onMessage(View view, String msg, String param) {
		long instance = UiView.getInstance(view);
		if (instance != 0) {
			nativeOnMessage(instance, msg, param);
		}
	}
	
	public UiWebView(Context context) {
		super(context);
		
		WebSettings webSettings = this.getSettings();
		webSettings.setJavaScriptEnabled(true);
		//webSettings.setBuiltInZoomControls(true);
		
		setWebViewClient(new MyWebViewClient());
		setWebChromeClient(new MyWebChromeClient());
		
		requestFocusFromTouch();
		
		addJavascriptInterface(new MyJavaScriptObject(), "SlibNative");
	}

	class MyWebViewClient extends WebViewClient {
		
		public boolean shouldOverrideUrlLoading(WebView view, String url) {
			return false;
		}
		
		public void onPageStarted(WebView view, String url, Bitmap favicon) {
			onStartLoad(UiWebView.this, url);
			try {
				UiWebView.this.loadUrl("javascript:window.slib_send=function(msg, param) {SlibNative.send(msg, param);};");
			} catch (Exception e) {
				Logger.exception(e);
			}
		}
		
		public void onPageFinished(WebView view, String url) {
			onFinishLoad(UiWebView.this, url);
		}
		
		public void onReceivedError (WebView view, int errorCode, String description, String failingUrl) {
			onErrorLoad(UiWebView.this, failingUrl, description);
		}
		
	}
	
	class MyWebChromeClient extends WebChromeClient {
		
		public boolean onJsAlert(WebView view, String url, String message, JsResult result) {
			return false;
		}
		
		public boolean onJsConfirm(WebView view, String url, String message, JsResult result) {
			return false;
		}
		
		public boolean onJsPrompt(WebView view, String url, String message, String defaultValue, JsPromptResult result) {
			return false;
		}
	}
	
	class MyJavaScriptObject {
		
		@JavascriptInterface
		public void send(String msg, String param) {
			onMessage(UiWebView.this, msg, param);
		}
	}
}
