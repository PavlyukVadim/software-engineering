package com.pavlyuk;

public class Banks {

    public int month_12, month_6, month_3;

    Banks(int month_12,int month_6, int month_3) {
        this.month_12 = month_12;
        this.month_6 = month_6;
        this.month_3 = month_3;
    }

    Banks(int month_12,int month_6) {
        this.month_12 = month_12;
        this.month_6 = month_6;
    }

    Banks(int month_12) {
        this.month_12 = month_12;
    }
}
