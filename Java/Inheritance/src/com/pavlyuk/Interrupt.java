package com.pavlyuk;
public class Interrupt extends Contribution{

    public int time;

    Interrupt(int time, int money, int period, int month_12,int month_6, int month_3) {
        super(money, period, month_12, month_6, month_3);
        this.time = time;
    }

    Interrupt(int time, int money, int period, int month_12,int month_6) {
        super(money, period, month_12, month_6);
        this.time = time;
    }

    Interrupt(int time, int money, int period, int month_12) {
        super(money, period, month_12);
        this.time = time;
    }
}

