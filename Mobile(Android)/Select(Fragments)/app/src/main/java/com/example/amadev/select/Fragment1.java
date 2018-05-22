package com.example.amadev.select;

import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Spinner;

public class Fragment1 extends Fragment {

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

        return v;
    }
}