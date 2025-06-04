package org.example;
import java.io.*;
import java.util.Scanner;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;


public class Parser {
    private static final Logger logger = LogManager.getLogger(Parser.class);
    String ParserFromFile(BufferedReader reader) throws IOException {
        String data = reader.readLine();
        logger.info("The program considered a line: " + data);
        return data;
    }

    String ParserFromConsole(Scanner in) {
        String data = in.nextLine();
        logger.info("The program considered a line: " + data);
        return data;
    }
}
