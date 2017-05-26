package com.pavlyuk;

public class Main{

     public static void main(String args[]){
         //Banks b1 = new Banks(21, 20, 19);
         //Interrupt b1 = new Interrupt(2, 1000, 12, 5);
         Search search = new Search("money");
         search.output();
         search.add(1,1000);
         search.take(1,500);
         search.find("money", 5000);
         search.output();
     }
}
