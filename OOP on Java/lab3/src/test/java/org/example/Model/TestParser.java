package org.example.Model;

import org.junit.jupiter.api.Test;


import java.util.Scanner;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class TestParser {
    @Test
    public void testParser() {
        String simulatedInput = "open 2 3";
        Scanner scanner = new Scanner(simulatedInput);

        Parser parser = new Parser();
        String result = parser.parsing(scanner);

        assertEquals(simulatedInput, result);
    }
}
