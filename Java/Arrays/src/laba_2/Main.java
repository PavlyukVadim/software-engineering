package laba_2;

import java.util.Random;

public class Main {

	public static void main(String[] args) {

		int Gradebook = 5115;
		System.out.println(Gradebook % 5);
		System.out.println(Gradebook % 7);
		System.out.println(Gradebook % 11);
		System.out.println("\n");

		final Random random = new Random();
		final int a = 2;
		final int n = 3;
		final int m = 3;
		char[][]data = new char[n][m];
		char[][]C = new char[n][m];
		char sum = 0;
		
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				data[i][j] = (char)((int)(random.nextDouble() * 100) + 28);
			}
		}
		
		System.out.println("B:");
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				System.out.print((int)data[i][j] + " ");
			}
			System.out.print("\n");
		}
		
		
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				C[i][j] = (char)((int)(data[i][j]) * a);
			}
		}
		
		System.out.println("C = B * " + a);
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				System.out.print((int)C[i][j] + " ");
			}
			System.out.print("\n");
		}
		
		int min = 128;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				if((int)C[i][j] < min) min = (int)C[i][j];
			}
			sum += (char)min;
		    min = 128;
		}
		System.out.println("\nSum = " + (int)sum);
	}
}
