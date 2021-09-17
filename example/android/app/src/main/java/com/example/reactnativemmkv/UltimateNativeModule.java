package com.example.reactnativemmkv;

import android.util.Log;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.module.annotations.ReactModule;
import com.reactnativemmkv.MmkvModule;

@ReactModule(name = "UltimateNative")
class UltimateNativeModule extends ReactContextBaseJavaModule {
  static {
    System.loadLibrary("reactnativemmkv");
  }

  private static native long getValueAtIndex(long jsiPtr, int index);
  private static native void installPointerGetter(long animatedRuntimeAddress);

  public long sAnimatedRuntimeAddress = -1;

  private ReactContext context;

  public UltimateNativeModule(ReactContext reactContext) {
    super();
    this.context = reactContext;
  }

  @ReactMethod
  public void setUIThreadPointer(String animatedRuntimeAddress) {
    Log.d("[GGG]", animatedRuntimeAddress);
    sAnimatedRuntimeAddress = Long.parseLong(animatedRuntimeAddress);
    installPointerGetter(sAnimatedRuntimeAddress);
  }

  @NonNull
  @Override
  public String getName() {
    return "UltimateNative";
  }
}
