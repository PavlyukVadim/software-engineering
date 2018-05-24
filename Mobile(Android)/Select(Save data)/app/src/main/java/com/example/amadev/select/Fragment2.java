package com.example.amadev.select;

import android.support.v4.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class Fragment2 extends Fragment {

    private TextView updateText;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment2, container, false);
        updateText = (TextView)v.findViewById(R.id.textView5);
        return v;
    }

    public void updateTextField(String newText){
        updateText.setText(newText);
    }
}
