package com.pavlyuk;

public class MyException extends Exception {
    String type;
    MyException(String type) {
        this.type = type;
    }

    public String toString() {
        return type;
    }
}
