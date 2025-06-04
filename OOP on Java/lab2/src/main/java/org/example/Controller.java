package org.example;
import java.io.*;
import java.util.Scanner;
import java.util.Stack;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class Controller {
    public Stack<Double> stack = new Stack<>();
    private static final Logger logger = LogManager.getLogger(Controller.class);


    int VerificationOfTheInputFile(String[] args) {
        if (args.length == 0) {
            return 0;
        }
        return 1;
    }


    void start(String[] args) {
        int presence_input = VerificationOfTheInputFile(args);
        Parser parser = new Parser();
        Factory factory = new Factory();
        String str;
        if (presence_input == 1) {
            logger.info("The program will read data from the file");
            try  (BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(args[0])))){
                while (reader.ready()) {
                    str = parser.ParserFromFile(reader);
                    if (str.contains("#")) {
                        logger.info("The program considered a comment");
                        continue;
                    }
                    try {
                        factory.factory(str, stack);
                    } catch (Exception e) {
                        System.err.println(e);
                        logger.error("Error executing command " + e.getMessage());
                    }
                }
            } catch (IOException e) {
                System.err.println("Error while open file" + e.getMessage());
                logger.error("Error while open file" + e.getMessage());
            }
            logger.info("Program completed");
        }
        else {
            logger.info("The program will read data from the console");
            System.out.println("Enter commands or \"Exit\" to complete the program");
            Scanner in = new Scanner(System.in);
            while (true) {
                str = parser.ParserFromConsole(in);
                if (str.split(" ")[0].equals("EXIT")) {
                    logger.info("Program completed");
                    break;
                }
                else if (str.contains("#")) {
                    logger.info("The program considered a comment");
                    continue;
                }
                try {
                    factory.factory(str, stack);
                } catch (Exception e) {
                    System.err.println(e);
                    logger.error("Error executing command " + e.getMessage());
                }
            }
            in.close();
        }
    }
}
