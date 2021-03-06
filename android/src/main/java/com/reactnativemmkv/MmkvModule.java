package com.reactnativemmkv;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.Callback;
import com.facebook.react.bridge.JavaScriptContextHolder;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.module.annotations.ReactModule;

import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

@ReactModule(name = "MMKV")
public class MmkvModule extends ReactContextBaseJavaModule {
  static {
    System.loadLibrary("reactnativemmkv");
  }

  private ReactContext context;
  public MmkvModule (ReactContext reactContext) {
    super();
    this.context = reactContext;
  }

  private JavaScriptContextHolder jsContext;

  public static void setTimeout(Runnable runnable, int delay){
    new Thread(() -> {
      try {
        Thread.sleep(delay);
        runnable.run();
      }
      catch (Exception e){
        System.err.println(e);
      }
    }).start();
  }

  private static native void nativeInstall(long jsiPtr, String path);
  private static native int getArraySize(long jsiPtr);

  private static native long getValueAtIndex(long jsiPtr, int index);
  private static native byte[] getValueAtIndexString(long jsiPtr, int index);


  @ReactMethod
  public void testGettingArray(Callback callback) {
  }

  public int arraySize() {
    //return 1000;
    return getArraySize(this.context.getJavaScriptContextHolder().get());
  }

  public long valueAtIndex(int index) {
     return getValueAtIndex(this.context.getJavaScriptContextHolder().get(), index);
  }

  public String valueAtIndexString(int index) {
    return new String(getValueAtIndexString(this.context.getJavaScriptContextHolder().get(), index), StandardCharsets.UTF_8);
  }



  public static void install(JavaScriptContextHolder jsContext, String storageDirectory) {
    nativeInstall(jsContext.get(), storageDirectory);
//    setTimeout(() -> {
//      byte[] x = nativeInstall3(jsContext.get(), 0);
//      String c = new String(x, Charset.forName("UTF-8"));
//      Log.d("sss", c);
//    }, 3000);


  }

  @NonNull
  @Override
  public String getName() {
    return "MMKV";
  }
}
