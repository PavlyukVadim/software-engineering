package com.example.amadev.select;

import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class SomeActivity extends AppCompatActivity {

    private String getFromFile;

    TextView textView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_some);

        SharedPreferences sharedPreferences = getSharedPreferences("myPref",MODE_PRIVATE);
        getFromFile = sharedPreferences.getString("userData", "");

        textView = findViewById(R.id.secActivity);
        textView.setText(getFromFile);
    }
}
