package com.pavlyuk;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.Serializable;

public class Contribution extends Invest implements Serializable {

    public int money;

    Contribution(int money, int period, int month_12,int month_6, int month_3) {
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

    private void readObject(ObjectInputStream in) throws IOException, ClassNotFoundException {
        in.defaultReadObject();
    }
}
