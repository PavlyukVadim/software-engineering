package com.pavlyuk;

public class Count {

    public int income;

    Count(Interrupt ob) {
        if (ob.period == 12) {
            if (ob.month_12 != 0) {
                if(ob.time > 12) {
                    System.out.println("НЕ коректні дані");
                } else {
                    income = ob.money + ob.money * ob.month_12 / 100 / (12 / (12 - ob.time));
                }
            } else {
                System.out.println(" В банку не має внеску на такий період ");
            }
        }
        if (ob.period == 6) {
            if (ob.month_6 != 0) {
                if(ob.time > 6) {
                    System.out.println("НЕ коректні дані");
                } else {
                    income = ob.money + ob.money * ob.month_6 / 100 / (12 / (6 - ob.time));
                }
            } else {
                System.out.println(" В банку не має внеску на такий період ");
            }
        }
        if (ob.period == 12) {
            if (ob.month_3 != 0) {
                if(ob.time > 3) {
                    System.out.println("НЕ коректні дані");
                } else {
                    income = ob.money + ob.money * ob.month_3 / 100 / (12 / (3 - ob.time));
                }
            } else {
                System.out.println(" В банку не має внеску на такий період ");
            }
        }
    }

    Count(Contribution ob) {
        if(ob.period == 12) {
            if(ob.month_12 != 0) {
                income = ob.money + ob.money * ob.month_12 / 100;
            } else {
                System.out.println(" В банку не має внеску на такий період ");
            }
        }
        if(ob.period == 6) {
            if(ob.month_6 != 0) {
                income = ob.money + ob.money * ob.month_6 / 100 / 2;
            } else {
                System.out.println(" В банку не має внеску на такий період ");
            }
        }
        if(ob.period == 3) {
            if(ob.month_3 != 0) {
                income = ob.money + ob.money * ob.month_3 / 100 / 4;
            } else {
                System.out.println(" В банку не має внеску на такий період ");
            }
        }
        else {
            System.out.println(" В банку не має внеску на такий період ");
        }
    }
}
