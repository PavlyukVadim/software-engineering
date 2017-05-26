import java.util.Scanner;

public class Main {

    public static Symbols symb;
    public static Words word;
    public static Sentence sent;
    public static Text text;
    public static Method meth;
    public static StringBuilder sb = new StringBuilder();

    public static void main(String[] args) {
        String strin;
        Scanner sc = new Scanner(System.in);
        strin = sc.nextLine();
        sb.append(strin);

        symb = new Symbols();
        word = new Words();
        sent = new Sentence();
        text = new Text();
        meth = new Method();

        symb.symbols();
        word.words();
        sent.sentense();
        text.text();
        meth.method();
    }
}
