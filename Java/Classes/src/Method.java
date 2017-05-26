public class Method {
    public static Words word;

    public void method() {
        word = new Words();
        word.words();
        final int len = 2;
        final String str = "aa";
        for(int j = 0; j < word.i; j++) {
            if(word.data[j].length() == len) {
                word.data[j] = str;
            }
        }
        String result = "";
        for(int j = 0; j < word.i; j++) {
            result += word.data[j] + " ";
        }
        System.out.println(result);
    }
}
