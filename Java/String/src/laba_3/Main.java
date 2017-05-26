package laba_3;

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		String strin;
		StringBuilder sb = new StringBuilder();
        StringBuilder[] arrayOfWords = new StringBuilder[100];
        System.out.println("Input your initial string: ");
		Scanner sc = new Scanner(System.in);
		strin = sc.nextLine();
		sb.append(strin);

        System.out.println("Input length of words, witch you want to change: ");
		int targetLengthOfWord = sc.nextInt();
		int index = -1;
		int indexOfWord = 0;
		final String newWord = "newWord";

		while(index < sb.length()){
		    if (sb.indexOf(" ", index + 1) == -1) {
                arrayOfWords[indexOfWord] = new StringBuilder(sb.substring(index + 1, sb.length()));
                System.out.println(arrayOfWords[indexOfWord]);
                indexOfWord++;
                break;
            } else {
                arrayOfWords[indexOfWord] = new StringBuilder(sb.substring(index + 1, sb.indexOf(" ", index + 1)));
                index = sb.indexOf(" ", index + 1);
                indexOfWord++;
            }
		}

		for(int j = 0; j < indexOfWord; j++) {
			if(arrayOfWords[j].length() == targetLengthOfWord) {
                arrayOfWords[j] = new StringBuilder(newWord);
			}
		}

		sb = new StringBuilder();
		for(int j = 0; j < indexOfWord; j++) {
			sb = sb.append(arrayOfWords[j]);
			sb = sb.append(" ");
		}
		System.out.println(sb);
	}
}
