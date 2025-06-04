package org.example.View.TextVersion;



import org.example.Model.Field;


import static java.lang.Math.sqrt;

public class PrintTextField {
    public void printField(Field field) {
        int side = (int)sqrt(field.field.size());
        System.out.print("  ");
        for (int i = 0; i < side; i++) {
            System.out.print(i + " ");
        }
        System.out.println();
        System.out.print("  ");
        for (int i = 0; i < side*2; i++) {
            System.out.print("-");
        }
        System.out.println();
        for (int i = 0; i < side; i++) {
            System.out.print(i + "|");
            for (int j = 0; j < side; j++) {
                if (field.field.get(i * side + j).isFlagOpen()) {
                    System.out.print("F ");
                }
                else {
                    System.out.print(field.field.get(i * side + j).getValue() + " ");
                }
            }
            System.out.println();
        }
    }



}
