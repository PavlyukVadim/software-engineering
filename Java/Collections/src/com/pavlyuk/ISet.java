package com.pavlyuk;

public interface ISet {

    int size();
    void add(Contribution contribution);
    boolean contains(Contribution contribution);
    void remove(int index);
    void removeAll();
    boolean isEmpty();
    void output();
}
