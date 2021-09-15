package com.example.reactnativemmkv;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.uimanager.ThemedReactContext;
import com.facebook.react.uimanager.ViewGroupManager;
import com.facebook.react.uimanager.annotations.ReactProp;


class UltraFastTextWrapperManager extends UltraFastAbstractComponentWrapperManager<UltraFastTextWrapper> {
  public static final String REACT_CLASS = "UltraFastTextWrapper";

  public UltraFastTextWrapperManager(ReactApplicationContext reactContext) {
    super(reactContext);
  }

  @Override
  public String getName() {
    return REACT_CLASS;
  }

  @Override
  public UltraFastTextWrapper createViewInstance(ThemedReactContext context) {
    return new UltraFastTextWrapper(context);
  }
}
