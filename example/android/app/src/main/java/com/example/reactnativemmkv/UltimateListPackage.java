package com.example.reactnativemmkv;

import android.content.Context;
import android.widget.LinearLayout;

import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.facebook.react.ReactPackage;
import com.facebook.react.bridge.NativeModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.UIManager;
import com.facebook.react.uimanager.ThemedReactContext;
import com.facebook.react.uimanager.ViewGroupManager;
import com.facebook.react.uimanager.ViewManager;
import com.reactnativemmkv.MmkvModule;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

class CustomView extends LinearLayout {
  private ThemedReactContext context;
  MyRecyclerViewAdapter adapter;

  public CustomView(ThemedReactContext context) {
    super(context);//ADD THIS
    this.context = context;
    init();
  }

  public void init() {
    inflate(context, R.layout.activity_main, this);

    ArrayList<String> animalNames = new ArrayList<>();
    for (int i = 0; i < 100; i++){
      animalNames.add("Horse");
      animalNames.add("Cow");
      animalNames.add("Camel");
      animalNames.add("Sheep");
      animalNames.add("Goat");
    }


    // set up the RecyclerView
    RecyclerView recyclerView = findViewById(R.id.rvAnimals);
    recyclerView.setLayoutManager(new LinearLayoutManager(context));

    adapter = new MyRecyclerViewAdapter(context, recyclerView);
    //adapter.setClickListener(c);
    recyclerView.setAdapter(adapter);
  }
}

class UltimateViewManager extends ViewGroupManager<LinearLayout> {

  public static final String REACT_CLASS = "UltimateView";
  ReactApplicationContext mCallerContext;

  public UltimateViewManager(ReactApplicationContext reactContext) {
    mCallerContext = reactContext;
  }

  @Override
  public String getName() {
    return REACT_CLASS;
  }

  @Override
  public CustomView createViewInstance(ThemedReactContext context) {
    return new CustomView(context);
  }
}

public class UltimateListPackage implements ReactPackage {

  @Override
  public List<NativeModule> createNativeModules(ReactApplicationContext reactContext) {
    return Collections.emptyList();
  }

  @Override
  public List<ViewManager> createViewManagers(ReactApplicationContext reactContext) {
    return Arrays.asList(
      new UltimateViewManager(reactContext));
  }
}

