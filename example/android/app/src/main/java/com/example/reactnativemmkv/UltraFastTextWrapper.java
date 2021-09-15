package com.example.reactnativemmkv;

import android.content.Context;
import android.view.View;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.uimanager.annotations.ReactProp;
import com.facebook.react.views.text.ReactTextView;
import com.facebook.react.views.view.ReactViewGroup;


class UltraFastTextWrapper extends UltraFastAbstractComponentWrapper {
  public UltraFastTextWrapper(Context context) {
    super(context);
  }

  @Override
  public void setValue(String value) {

    View child = getChildAt(0);
    if (child instanceof ReactTextView) {
      ((ReactTextView) child).setText(value);
    }
  }

}
