package com.example.amadev.select;

import android.Manifest;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v4.app.Fragment;
import android.os.Bundle;
import android.support.v4.content.ContextCompat;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Spinner;
import android.widget.Button;
import android.widget.SearchView;
import android.widget.SeekBar;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class Fragment1 extends Fragment implements ActivityCompat.OnRequestPermissionsResultCallback{

    private OnFragmentInteractionListener mListener;

    private SearchView searchView;
    private SeekBar seekBar;
    private Button update;
    private Button goToSavedData;

    private AlertDialog.Builder builder;

    private String userData;

    private String filename = "SampleFile.txt";
    private String filepath = "MyFileStorage";
    File myExternalFile = new File(filepath);
    String myData = "";

    private final int REQUEST_CODE = 1;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment1, container, false);

        String[] spinnerTitles;
        String[] spinnerPrice;

        spinnerTitles = new String[]{
            "Pen1",
            "Spoon4",
            "Fork",
            "Knife1",
            "Knife2",
            "Fork3"
        };
        spinnerPrice = new String[]{
            "54",
            "45",
            "220",
            "100",
            "87",
            "201"
        };

        Spinner spinner = (Spinner) v.findViewById(R.id.cities);
        DishListAdapter mCustomAdapter = new DishListAdapter(this.getActivity(), spinnerTitles, spinnerPrice);
        spinner.setAdapter(mCustomAdapter);

        builder = new AlertDialog.Builder(this.getActivity());

        searchView = (SearchView)v.findViewById(R.id.searchView);
        seekBar = (SeekBar)v.findViewById(R.id.seekBar);

        update = (Button)v.findViewById(R.id.buttonOk);
        update.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                userData = "Product: " + searchView.getQuery().toString() + "\nPrice:" + seekBar.getProgress();

                SharedPreferences preferences = getActivity().getSharedPreferences("myPref",Context.MODE_PRIVATE);
                SharedPreferences.Editor editor = preferences.edit();
                editor.putString("userData", userData);
                editor.commit();
                checkFileStorgePermission();

                onButtonPressed(userData);
            }
        });

        goToSavedData = v.findViewById(R.id.goToSecondActivity);
        goToSavedData.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getContext(), SomeActivity.class);
                startActivity(intent);
            }
        });

        return v;
    }


    public void onButtonPressed(String userContent) {
        if (mListener != null) {
            mListener.onFragmentInteraction(userContent);
        }
    }

    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        try {
            mListener = (OnFragmentInteractionListener) activity;
        } catch (ClassCastException e) {
            throw new ClassCastException(activity.toString() + " must implement OnFragmentInteractionListener");
        }
    }

    @Override
    public void onDetach() {
        super.onDetach();
        mListener = null;
    }

    public interface OnFragmentInteractionListener {
        public void onFragmentInteraction(String userContent);
    }

    private void tryToSaveFile(){
        try {
            FileOutputStream fos = new FileOutputStream(myExternalFile);
            fos.write(userData.getBytes());
            fos.close();

            builder.setTitle("Success!")
                    .setMessage("File saved!")
                    .setCancelable(false)
                    .setNegativeButton("Ok",
                            new DialogInterface.OnClickListener() {
                                public void onClick(DialogInterface dialog, int id) {
                                    dialog.cancel();
                                }
                            });
            AlertDialog alert = builder.create();
            alert.show();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    private void checkFileStorgePermission(){
        if (ContextCompat.checkSelfPermission(getActivity(), Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
            requestPermissions(new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, REQUEST_CODE);
        } else {
            tryToSaveFile();
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        switch (requestCode){
            case REQUEST_CODE:
                if (grantResults.length > 0
                        && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    tryToSaveFile();
                }
                break;
        }
    }
}