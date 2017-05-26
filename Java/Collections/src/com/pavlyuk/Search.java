package com.pavlyuk;

import java.util.Scanner;

public class Search {

    Scanner sc = new Scanner(System.in);

    Contribution banks[] = new Contribution[10];
    int index = 0;
    int summa, period, month_12, month_6, month_3;

    void input(int n) {
        for(int i = index; i < n + index; i++) {
            System.out.print("Введіть суму: ");
            summa = sc.nextInt();
            System.out.print("Введіть термін вкладу: ");
            period = sc.nextInt();
            System.out.print("Введіть банківські нарахування за 12 місяців : ");
            month_12 = sc.nextInt();
            System.out.print("Введіть банківські нарахування за 6 місяців : ");
            month_6 = sc.nextInt();
            System.out.print("Введіть банківські нарахування за 3 місяці : ");
            month_3 = sc.nextInt();
            banks[i] = new Contribution(summa, period, month_12, month_6, month_3);
        }
        index += n;
    }

    void sort(String field) {
        int sort[] = new int[banks.length];
        for(int i = 0; i < sort.length; i++) {
            sort[i] = -1;
        }
        if(field == "money") {
            int index = 0;
            for(int j = 0; j < banks.length; j++) {
                int max = 0;
                for(int i = 0; i < banks.length; i++) {
                    if(banks[i].money > max && exist(i, sort) == 2) {
                        max = banks[i].money;
                        index = i;
                    }
                }
                sort[j] = index;
            }
        }
        if(field == "period") {
            int index = 0;
            for(int j = 0; j < banks.length; j++) {
                int max = 0;
                for(int i = 0; i < banks.length; i++) {
                    if(banks[i].period > max && exist(i, sort) == 2) {
                        max = banks[i].period;
                        index = i;
                    }
                }
                sort[j] = index;
            }
        }
        output(sort);
    }

    int exist(int index, int sort[]) {
        for(int i = 0; i < banks.length; i++) {
            if(sort[i] == index) {
                return 1;
            }
        }
        return 2;
    }

    void find(String field, int value) {
        int n = 0;
        if(field == "money") {
            for(int i = 0; i < banks.length; i++) {
                if(banks[i].money == value) {
                    n++;
                    if(n == 1) {
                        System.out.printf("\n\n%10s %10s %10s %10s %10s\n", "Вклад", "термін", "% за 12","% за 6","% за 3");
                    }
                    System.out.printf("%10d %10d %10d %10d %10d\n", banks[i].money, banks[i].period, banks[i].month_12, banks[i].month_6, banks[i].month_3);
                }
            }
            if(n == 0) {
                System.out.println("НЕ знайдено");
            } else {
                n = 0;
            }
        }

        if(field == "period") {
            for(int i = 0; i < banks.length; i++) {
                if(banks[i].period == value) {
                    n++;
                    if(n == 1) {
                        System.out.printf("\n\n%10s %10s %10s %10s %10s\n", "Вклад", "термін", "% за 12","% за 6","% за 3");
                    }
                    System.out.printf("%10d %10d %10d %10d %10d\n", banks[i].money, banks[i].period, banks[i].month_12, banks[i].month_6, banks[i].month_3);
                    System.out.printf("%10d %10d %10d %10d %10d\n", banks[i].money, banks[i].period, banks[i].month_12, banks[i].month_6, banks[i].month_3);
                }
            }
            if(n == 0) {
                System.out.println("НЕ знайдено");
            } else {
                n = 0;
            }
        }
    }

    void add(int index, int value){
        banks[index - 1].money = banks[index - 1].money + value;
    }

    void take(int index, int value){
        banks[index - 1].money = banks[index - 1].money - value;
    }

    void output(int sort[]){
        System.out.printf("%10s %10s %10s %10s %10s\n", "Вклад", "термін", "% за 12","% за 6","% за 3");
        for(int i = 0; i < sort.length; i++) {
            System.out.printf("%10d %10d %10d %10d %10d\n", banks[sort[i]].money, banks[sort[i]].period, banks[sort[i]].month_12, banks[sort[i]].month_6, banks[sort[i]].month_3);
        }
    }

    void output() {
        System.out.println("\nКількість внесків : " + index + "\n");
        System.out.printf("%10s %10s %10s %10s %10s\n", "Вклад", "термін", "% за 12","% за 6","% за 3");
        for(int i = 0; i < index; i++) {
            System.out.printf("%10d %10d %10d %10d %10d\n", banks[i].money, banks[i].period, banks[i].month_12, banks[i].month_6, banks[i].month_3);
        }
    }
}
