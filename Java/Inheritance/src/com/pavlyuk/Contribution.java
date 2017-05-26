package com.pavlyuk;

public class Contribution extends Invest {

    public int money;

    Contribution(int money, int period, int month_12, int month_6, int month_3) {
        super(period, month_12, month_6, month_3);
        this.money = money;
    }

    Contribution(int money, int period, int month_12,int month_6) {
        super(period, month_12, month_6);
        this.money = money;
    }

    Contribution(int money, int period, int month_12) {
        super(period, month_12);
        this.money = money;
    }
}
