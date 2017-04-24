package laba_1;

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		
		System.out.println(5114 % 2);
		System.out.println(5114 % 3);
		System.out.println(5114 % 5);
		System.out.println(5114 % 7);

		final int c = 2; 
		double s = 0.0;
		int n = 0, m = 0;
		
		System.out.println("n : ");
		if (sc.hasNextInt()) {
			n = sc.nextInt();
		} else {
			System.out.println("no int");
			System.out.println(s);
			return;
		}
		
		System.out.println("m : ");
		if (sc.hasNextInt()) {
			m = sc.nextInt();
		} else {
			System.out.println("no int");
			System.out.println(s);
			return;
		}
		
		for(char i = 0; i <= n; i++) {
			for(char j = 0; j <= m; j++) {
				if (i != j) {
					s += (double) (i - j) / (double) (i + c);
				}
			}
		}

		System.out.println("Result: " + s);
	}
}
