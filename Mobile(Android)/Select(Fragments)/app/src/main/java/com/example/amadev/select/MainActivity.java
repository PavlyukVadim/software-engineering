package com.example.amadev.select;

import android.support.v4.app.FragmentActivity;
import android.os.Bundle;
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

public class MainActivity extends FragmentActivity {

    final Context context = this;
    private Button button;
    private SearchView searchView;
    private SeekBar seekBar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

//        ListView mListView = (ListView) findViewById(R.id.listView);
//
//
//        button = (Button) findViewById(R.id.buttonOk);
//        searchView = (SearchView)findViewById(R.id.searchView);
//        seekBar = (SeekBar)findViewById(R.id.seekBar);
//
//        // add button listener
//        button.setOnClickListener(new OnClickListener() {
//
//            @Override
//            public void onClick(View arg0) {
//
//                AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(
//                        context);
//
//                // set title
//                alertDialogBuilder.setTitle("Your request:");
//
//                // set dialog message
//                alertDialogBuilder
//                    .setMessage("Product: " + searchView.getQuery().toString() + "\nPrice:" + seekBar.getProgress())
//                    .setCancelable(false)
//                    .setPositiveButton("Yes", new DialogInterface.OnClickListener() {
//                        public void onClick(DialogInterface dialog, int id) {
//                            // the dialog box and do nothing
//                            dialog.cancel();
//                        }
//                    });
//
//                // create alert dialog
//                AlertDialog alertDialog = alertDialogBuilder.create();
//
//                // show it
//                alertDialog.show();
//            }
//        });
    }
}
