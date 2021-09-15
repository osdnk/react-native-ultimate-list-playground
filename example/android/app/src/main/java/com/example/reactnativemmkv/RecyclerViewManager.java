package com.example.reactnativemmkv;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.uimanager.ThemedReactContext;
import com.facebook.react.uimanager.ViewGroupManager;
import com.facebook.react.uimanager.annotations.ReactProp;

class RecyclerViewManager extends ViewGroupManager<RecyclerListView> {

  public static final String REACT_CLASS = "RecyclerListView";
  ReactApplicationContext mCallerContext;

  public RecyclerViewManager(ReactApplicationContext reactContext) {
    mCallerContext = reactContext;
  }

  @ReactProp(name = "count")
  public void setCount(RecyclerListView view, int count) {
    view.mCount = count;
  }

  @Override
  public String getName() {
    return REACT_CLASS;
  }

  @Override
  public RecyclerListView createViewInstance(ThemedReactContext context) {
    return new RecyclerListView(context);
  }
}
