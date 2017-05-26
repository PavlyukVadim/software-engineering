public class Words {
    String[]data = new String[100];
    int i = 0;
    public void words() {
        StringBuilder s = Main.sb;
        int index = -1;
        while(index < s.length()) {
            int found_space = s.indexOf(" ", index + 1);
            if(found_space != -1) {
                data[i] = s.substring(index + 1, found_space);
                index = found_space;
                i++;
            } else {
                data[i] = s.substring(index + 1, s.length());
                i++;
                break;
            }
        }
    }
}
