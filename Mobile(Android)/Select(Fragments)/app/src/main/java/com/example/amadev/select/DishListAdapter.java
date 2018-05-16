package com.example.amadev.select;

import android.content.Context;
import android.support.annotation.NonNull;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

public class DishListAdapter extends ArrayAdapter<Dish> {

    private static final String TAG = "DishListAdapter";

    private Context mContext;
    private int mResource;
    private int lastPosition = -1;

    /**
     * Holds variables in a View
     */
    private static class ViewHolder {
        TextView name;
        TextView price;
        TextView category;
    }

    /**
     * Default constructor for the DishListAdapter
     * @param context
     * @param resource
     * @param objects
     */
    public DishListAdapter(Context context, int resource, ArrayList<Dish> objects) {
        super(context, resource, objects);
        mContext = context;
        mResource = resource;
    }

    @NonNull
    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        //get the dishs information
        String name = getItem(position).getName();
        String price = getItem(position).getPrice();
        String category = getItem(position).getCategory();

        //Create the dish object with the information
        Dish dish = new Dish(name, price, category);

        //create the view result for showing the animation
        final View result;

        //ViewHolder object
        ViewHolder holder;


        if(convertView == null){
            LayoutInflater inflater = LayoutInflater.from(mContext);
            convertView = inflater.inflate(mResource, parent, false);
            holder = new ViewHolder();
            holder.name = (TextView) convertView.findViewById(R.id.textView1);
            holder.price = (TextView) convertView.findViewById(R.id.textView2);
            holder.category = (TextView) convertView.findViewById(R.id.textView3);

            result = convertView;

            convertView.setTag(holder);
        }
        else{
            holder = (ViewHolder) convertView.getTag();
            result = convertView;
        }


        Animation animation = AnimationUtils.loadAnimation(mContext,
                (position > lastPosition) ? R.anim.load_down_anim : R.anim.load_up_anim);
        result.startAnimation(animation);
        lastPosition = position;

        holder.name.setText(dish.getName());
        holder.price.setText(dish.getPrice());
        holder.category.setText(dish.getCategory());


        return convertView;
    }
}
