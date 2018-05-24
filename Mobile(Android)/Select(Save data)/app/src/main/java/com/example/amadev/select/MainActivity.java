package com.example.amadev.select;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity implements Fragment1.OnFragmentInteractionListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    public void onFragmentInteraction(String userContent) {
        Fragment2 secondFragment = (Fragment2)getSupportFragmentManager().findFragmentById(R.id.fragment2);
        secondFragment.updateTextField(userContent);
    }
}
