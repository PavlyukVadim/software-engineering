package com.example.amadev.select;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.L0g;
import android.widget.ListView;
import java.util.ArrayList;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.SearchView;
import android.widget.SeekBar;

public class MainActivity extends AppCompatActivity {

    private static final String TАG = "MainActivity";
    final Context context = this;
    private Button button;
    private SearchView searchView;
    private SeekBar seekBar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.d(TAG, "onCreate: Started.");
        ListView mListView = (ListView) findViewById(R.id.listView);

        //Create the Dish objects
        Dish pen1 = new Dish("Pen1","54","pen");
        Dish spoon4 = new Dish("Spoon4","45","spoon");
        Dish fork = new Dish("Fork","220","fork");
        Dish knife1 = new Dish("Knife1","100","knife");
        Dish knife2 = new Dish("Knife2","87","knife");
        Dish fork3 = new Dish("Fork3","201","fork");
        Dish spoon2 = new Dish("Spoon2","21","spoon");
        Dish caps1 = new Dish("Caps1","999","caps");
        Dish fork2 = new Dish("Fork2","354","fork");
        Dish spoon3 = new Dish("Spoon3","900","spoon");
        Dish caps2 = new Dish("Caps2","700","caps");
        Dish fork1 = new Dish("Fork1","200","fork");

        //Add the Dish objects to an ArrayList
        ArrayList<Dish> dishesList = new ArrayList<>();
        dishesList.add(pen1);
        dishesList.add(spoon4);
        dishesList.add(fork);
        dishesList.add(knife1);
        dishesList.add(knife2);
        dishesList.add(fork3);
        dishesList.add(spoon2);
        dishesList.add(caps1);
        dishesList.add(fork2);
        dishesList.add(spoon3);
        dishesList.add(caps2);
        dishesList.add(fork1);

        DishListAdapter adapter = new DishListAdapter(this, R.layout.adapter_view_layout, dishesList);
        mListView.setAdapter(adapter);

        button = (Button) findViewById(R.id.buttonOk);
        searchView = (SearchView)findViewById(R.id.searchView);
        seekBar = (SeekBar)findViewById(R.id.seekBar);

        // add button listener
        button.setOnClickListener(new OnClickListener() {

            @Override
            public void onClick(View arg0) {

                AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(
                        context);

                // set title
                alertDialogBuilder.setTitle("Your request:");

                // set dialog message
                alertDialogBuilder
                    .setMessage("Product: " + searchView.getQuery().toString() + "\nPrice:" + seekBar.getProgress())
                    .setCancelable(false)
                    .setPositiveButton("Yes", new DialogInterface.OnClickListener() {
                        public void onClick(DialogInterface dialog, int id) {
                            // the dialog box and do nothing
                            dialog.cancel();
                        }
                    });

                // create alert dialog
                AlertDialog alertDialog = alertDialogBuilder.create();

                // show it
                alertDialog.show();
            }
        });
    }
}
