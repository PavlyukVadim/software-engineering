package com.pavlyuk;

import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {

    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        Collection collection = new Collection();
        boolean perform = true;
        while (perform) {
            System.out.printf("\n\n%-25s%3s\n", "Добавити внесок", "1");
            System.out.printf("%-25s%3s\n", "Кількість внесків", "2");
            System.out.printf("%-25s%3s\n", "Перевірити наявність", "3");
            System.out.printf("%-25s%3s\n", "Видалити внесок", "4");
            System.out.printf("%-25s%3s\n", "Видалити усі", "5");
            System.out.printf("%-25s%3s\n", "Перевірити на пустоту", "6");
            System.out.printf("%-25s%3s\n", "Вивести внески", "7");
            System.out.printf("%-25s%3s\n\n", "Вийти", "8");
            int n = 0;
            try {
                n = sc.nextInt();
                if (n <= 0 || n > 11) {
                    throw new MyException("Не коректна команда.");
                }
            } catch (MyException e) {
                System.out.println(e);
            }
            switch (n) {
                case 1: {
                    add(collection);
                    break;
                }
                case 2: {
                    size(collection);
                    break;
                }
                case 3: {
                    contains(collection);
                    break;
                }
                case 4: {
                    remove(collection);
                    break;
                }
                case 5: {
                    removeAll(collection);
                    break;
                }
                case 6: {
                    isEmpty(collection);
                    break;
                }
                case 7: {
                    output(collection);
                    break;
                }

                case 8: {
                    perform = false;
                }
            }
        }
    }

    public static Contribution input() throws MyException {
        Scanner sc = new Scanner(System.in);
        int money = 0, period = 0, month_12 = 0, month_6 = 0, month_3 = 0;

        try {
            System.out.print("Введіть суму: ");
            money = sc.nextInt();
            System.out.print("Введіть термін вкладу: ");
            period = sc.nextInt();

            System.out.print("Введіть банківські нарахування за 12 місяців : ");
            month_12 = sc.nextInt();
            System.out.print("Введіть банківські нарахування за 6 місяців : ");
            month_6 = sc.nextInt();
            System.out.print("Введіть банківські нарахування за 3 місяці : ");
            month_3 = sc.nextInt();
        } catch (InputMismatchException e) {
            throw new MyException("Не коректні дані!");
        }
        System.out.println("Дані коректні...");
        Contribution contribution = new Contribution(money, period, month_12, month_6, month_3);
        return contribution;
    }

    public static void size(Collection collection) {
        int n = collection.size();
        System.out.printf("Size : %d", n);
    }

    public static void add(Collection collection) {
        try {
            Contribution contribution = input();
            collection.add(contribution);
        } catch (MyException e) {
            System.out.println(e);
        }
    }

    public static void contains(Collection collection) {
        Contribution contribution = new Contribution(0, 0, 0, 0);
        try {
            contribution = input();
        } catch (MyException e) {
            System.out.println(e);
        }
        boolean result = collection.contains(contribution);
        if (result) {
            System.out.println("Існує");
        } else {
            System.out.println("Не існує");
        }
    }

    public static void remove(Collection collection) {
        Scanner sc = new Scanner(System.in);
        System.out.printf("Введіть індекс : ");
        int n = sc.nextInt();
        collection.remove(n);
    }

    public static void removeAll(Collection collection) {
        collection.removeAll();
    }

    public static void isEmpty(Collection collection) {
        boolean result = collection.isEmpty();
        if (result)
            System.out.println("Так");
        else
            System.out.println("Ні");
    }

    public static void output(Collection collection) {
        collection.output();
    }
}
