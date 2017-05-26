public class Symbols {

    char[]data = new char[100];

    public void symbols() {
        StringBuilder s = Main.sb;
        for(int i = 0; i < s.length();i++) {
            data[i] = s.charAt(i);
        }
    }
}
