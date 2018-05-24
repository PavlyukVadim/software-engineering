package com.example.amadev.select;

import android.content.Context;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

public class DishListAdapter extends ArrayAdapter {

    /**
     * Holds variables in a View
     */
    private static class ViewHolder {
        TextView mName;
        TextView tvPrice;
    }

    /**
     * Default constructor for the DishListAdapter
     * @param context
     * @param resource
     * @param objects
     */

    String[] spinnerTitles;
    String[] spinnerPrice;
    Context mContext;

    public DishListAdapter(@NonNull Context context, String[] titles, String[] price) {
        super(context, R.layout.adapter_view_layout);
        this.spinnerTitles = titles;
        this.spinnerPrice = price;
        this.mContext = context;
    }

    @Override
    public int getCount() {
        return spinnerTitles.length;
    }


    @NonNull
    @Override
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
        ViewHolder mViewHolder = new ViewHolder();
        if (convertView == null) {
            LayoutInflater mInflater = (LayoutInflater) mContext.
                    getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            convertView = mInflater.inflate(R.layout.adapter_view_layout, parent, false);
            mViewHolder.mName = (TextView) convertView.findViewById(R.id.tvName);
            mViewHolder.tvPrice = (TextView) convertView.findViewById(R.id.tvPrice);
            convertView.setTag(mViewHolder);
        } else {
            mViewHolder = (ViewHolder) convertView.getTag();
        }
        mViewHolder.mName.setText(spinnerTitles[position]);
        mViewHolder.tvPrice.setText(spinnerPrice[position]);

        return convertView;
    }

    @Override
    public View getDropDownView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
        return getView(position, convertView, parent);
    }
}
