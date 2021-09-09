package com.example.reactnativemmkv;


import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;

import com.facebook.react.uimanager.ThemedReactContext;
import com.facebook.react.views.text.ReactTextView;
import com.facebook.react.views.view.ReactViewGroup;
import com.reactnativemmkv.MmkvModule;

import java.util.List;

public class MyRecyclerViewAdapter extends RecyclerView.Adapter<MyRecyclerViewAdapter.ViewHolder> {

    private LayoutInflater mInflater;
    private ItemClickListener mClickListener;
    private ThemedReactContext mContext;
    private MmkvModule mModule;
    private View mView;
    // data is passed into the constructor
    MyRecyclerViewAdapter(ThemedReactContext context, View view) {
        mView = view;
        this.mInflater = LayoutInflater.from(context);
        mContext = context;
        mModule = context.getNativeModule(MmkvModule.class);
    }

    // inflates the row layout from xml when needed
    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        LinearLayout view = (LinearLayout) mInflater.inflate(R.layout.recyclerview_row, parent, false);
        return new ViewHolder(view);
    }

    // binds the data to the TextView in each row
    @Override
    public void onBindViewHolder(ViewHolder holder, int position) {
        String animal = String.valueOf(mModule.valueAtIndex(position));
        //String animal = mModule.valueAtIndexString(position);
        //holder.myTextView.setText(animal);
        if (holder.mLayout.getChildCount() == 0) {
          ViewGroup vg = ((ViewGroup) mView.getParent().getParent().getParent());
          ViewGroup vgv = (ViewGroup) vg.getChildAt(0);
          if (vgv.getChildCount() != 0) {
            View viewToReparent = vgv.getChildAt(0);
            vgv.removeView(viewToReparent);
            holder.mLayout.addView(viewToReparent);
          }
//          ((ViewGroup) mView.getParent().getParent().getParent()).removeView(vg);
//          holder.mLayout.addView(vg);
        }

        if (holder.mLayout.getChildCount() != 0) {
          Log.d("GG", "GG");
          ((ReactTextView)((ViewGroup)((ViewGroup)holder.mLayout.getChildAt(0)).getChildAt(0)).getChildAt(0)).setText(animal);
        }
    }

    // total number of rows
    @Override
    public int getItemCount() {
        return this.mModule.arraySize();
    }


    // stores and recycles views as they are scrolled off screen
    public class ViewHolder extends RecyclerView.ViewHolder implements View.OnClickListener {
        TextView myTextView;
        ReactViewGroup mRVG;
        LinearLayout mLayout;

        ViewHolder(LinearLayout itemView) {
            super(itemView);
            mLayout = itemView;
           // myTextView = itemView.findViewById(R.id.tvAnimalName);
            itemView.setOnClickListener(this);
//            mRVG = itemView.findViewById(R.id.tvAnimalName2);
        }

        @Override
        public void onClick(View view) {
            if (mClickListener != null) mClickListener.onItemClick(view, getAdapterPosition());
        }
    }

    // convenience method for getting data at click position
//    String getItem(int id) {
//        return mData.get(id);
//    }

    // allows clicks events to be caught
    void setClickListener(ItemClickListener itemClickListener) {
        this.mClickListener = itemClickListener;
    }

    // parent activity will implement this method to respond to click events
    public interface ItemClickListener {
        void onItemClick(View view, int position);
    }
}
