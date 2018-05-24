package com.example.amadev.select;

import android.app.Activity;
import android.support.v4.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Spinner;
import android.widget.Button;
import android.widget.SearchView;
import android.widget.SeekBar;

public class Fragment1 extends Fragment {

    private OnFragmentInteractionListener mListener;

    private SearchView searchView;
    private SeekBar seekBar;
    private Button update;

    private String userData;

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

        searchView = (SearchView)v.findViewById(R.id.searchView);
        seekBar = (SeekBar)v.findViewById(R.id.seekBar);

        update = (Button)v.findViewById(R.id.buttonOk);
        update.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                userData = "Product: " + searchView.getQuery().toString() + "\nPrice:" + seekBar.getProgress();
                onButtonPressed(userData);
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
}