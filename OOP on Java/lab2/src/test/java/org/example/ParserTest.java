package org.example;

import org.junit.jupiter.api.Test;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.StringReader;
import java.util.Scanner;

import static org.junit.jupiter.api.Assertions.*;


public class ParserTest {
    @Test
    void testParserFromFile() throws IOException {
        String testData = "Hello, world!";
        BufferedReader reader = new BufferedReader(new StringReader(testData));
        Parser parser = new Parser();
        String result = parser.ParserFromFile(reader);
        assertEquals(testData, result);
    }

    @Test
    void testParserFromConsole() {
        String testData = "Hello, world!";
        Scanner scanner = new Scanner(testData);
        Parser parser = new Parser();
        String result = parser.ParserFromConsole(scanner);
        assertEquals(testData, result);

    }
}
