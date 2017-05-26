package com.pavlyuk;

import java.util.ArrayList;
import java.util.Arrays;

public class Collection implements ISet{

    int arr_size = 10;
    Contribution banks[] = new Contribution[10];
    int amount = 0;
    Collection() {

    }

    Collection(Contribution contribution) {
        banks[amount] = new Contribution(contribution.money,
                                         contribution.period,
                                         contribution.month_12,
                                         contribution.month_6,
                                         contribution.month_3);
        amount++;
    }

    Collection(ArrayList<Contribution> arrBanks) {
        for(int i = 0; i < arrBanks.size(); i++) {
            if(Exist(arrBanks.get(i)) == false) {
                if(amount + 1 == arr_size) {
                    banks = Arrays.copyOf(banks, arr_size / 2);
                    arr_size = (int) 1.5 * arr_size;
                }
                banks[amount] = new Contribution(arrBanks.get(i).money,
                                                 arrBanks.get(i).period,
                                                 arrBanks.get(i).month_12,
                                                 arrBanks.get(i).month_6,
                                                 arrBanks.get(i).month_3);
                amount++;
            }
        }
    }

    @Override
    public int size() {
        return amount;
    }

    @Override
    public void add(Contribution contribution) {
        /*if(amount + 1 == arr_size){
            banks = Arrays.copyOf(banks, arr_size/2);
            arr_size = (int) 1.5 * arr_size;
        }*/
        if(Exist(contribution) == false) {
            banks[amount] = new Contribution(contribution.money,
                                             contribution.period,
                                             contribution.month_12,
                                             contribution.month_6,
                                             contribution.month_3);
            amount++;
        }
    }

    @Override
    public boolean contains(Contribution contribution) {
        for(Contribution b : banks) {
            if(b.money == contribution.money &&
               b.period == contribution.period &&
               b.month_12 == contribution.month_12 &&
               b.month_6 == contribution.month_6 &&
               b.month_3 == contribution.month_3 ) {
                return true;
            }
        }
        return false;
    }

    @Override
    public void remove(int index) {
        index--;
        if(index > amount || index < 0) {
            return;
        }
        for(int i = index; i < amount; i++) {
            if(banks[i + 1] == null || i == amount - 1) {
                banks[i] = null;
                amount--;
                break;
            }
            banks[i] = banks[i + 1];
        }
    }

    @Override
    public void removeAll() {
        for (Contribution b : banks) {
            b = null;
        }
        amount = 0;
    }

    @Override
    public boolean isEmpty() {
        if(amount == 0) {
            return true;
        }
        return false;
    }

    @Override
    public void output() {
        System.out.printf("\n\n%10s %10s %10s %10s %10s\n", "Вклад", "термін", "% за 12","% за 6","% за 3");
        for (int i = 0; i < amount; i++) {
            System.out.printf("%10d %10d %10d %10d %10d\n", banks[i].money, banks[i].period, banks[i].month_12, banks[i].month_6, banks[i].month_3);
        }
    }

    public boolean Exist(Contribution contribution) {
        for(int i = 0; i < amount; i++) {
            if(banks[i].money == contribution.money &&
               banks[i].period == contribution.period &&
               banks[i].month_12 == contribution.month_12 &&
               banks[i].month_6 == contribution.month_6 &&
               banks[i].month_3 == contribution.month_3) {
                return true;
            }
        }
        return false;
    }
}
