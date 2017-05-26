package com.pavlyuk;

public class Search {
    Contribution banks[] = new Contribution[7];
    Search(String field) {
        banks[0] = new Contribution(6000, 3, 20, 19, 18);
        banks[1] = new Contribution(8000, 6, 25, 24, 23);
        banks[2] = new Contribution(3000, 12, 22, 21, 20);
        banks[3] = new Contribution(4000, 12, 21, 20, 19);
        banks[4] = new Contribution(5000, 12, 23, 19, 18);
        banks[5] = new Contribution(5000, 12, 25, 23, 17);
        banks[6] = new Contribution(10000, 12, 25, 23, 17);
        Sort(field);
    }

    void Sort(String field) {
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
        } else if(field == "period") {
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
    }

    int exist(int index, int sort[]) {
        for(int i = 0; i < banks.length; i++) {
            if(sort[i] == index) {
                return 1;
            }
        }
        return 2;
    }

    void find(String field, int value){
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
        } else if(field == "period") {
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

    void add(int index, int value) {
        banks[index - 1].money = banks[index - 1].money + value;
    }

    void take(int index, int value) {
        banks[index - 1].money = banks[index - 1].money - value;
    }

    void output(int sort[]) {
        System.out.printf("%10s %10s %10s %10s %10s\n", "Вклад", "термін", "% за 12","% за 6","% за 3");
        for(int i = 0; i < sort.length; i++) {
            System.out.printf("%10d %10d %10d %10d %10d\n", banks[sort[i]].money, banks[sort[i]].period, banks[sort[i]].month_12, banks[sort[i]].month_6, banks[sort[i]].month_3);
        }
    }

    void output() {
        System.out.printf("%10s %10s %10s %10s %10s\n", "Вклад", "термін", "% за 12","% за 6","% за 3");
        for(int i = 0; i < banks.length; i++) {
            System.out.printf("%10d %10d %10d %10d %10d\n", banks[i].money, banks[i].period, banks[i].month_12, banks[i].month_6, banks[i].month_3);
        }
    }
}
