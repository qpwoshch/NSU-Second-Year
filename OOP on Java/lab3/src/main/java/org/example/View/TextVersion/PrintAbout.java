package org.example.View.TextVersion;

import java.io.InputStream;
import java.util.Scanner;

public class PrintAbout {
    public void print() {
        try (InputStream inputStream = getClass().getResourceAsStream("/about");
            Scanner about = new Scanner(inputStream)) {
            while (about.hasNextLine()) {
                System.out.println(about.nextLine());
            }
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}
