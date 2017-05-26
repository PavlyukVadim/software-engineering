package com.pavlyuk;

import java.io.Serializable;

public class Invest extends Banks implements Serializable {

    public int period;

    Invest(int period, int month_12,int month_6, int month_3){
        super(month_12, month_6, month_3);
        this.period = period;
    }

    Invest(int period, int month_12,int month_6){
        super(month_12, month_6);
        this.period = period;
    }

    Invest(int period, int month_12){
        super(month_12);
        this.period = period;
    }

}
