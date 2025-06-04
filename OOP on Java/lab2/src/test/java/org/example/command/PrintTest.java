package org.example.command;

import org.junit.jupiter.api.Test;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

import static org.junit.jupiter.api.Assertions.*;

public class PrintTest {
    @Test
    void testPerformPrint() throws Exception{
        Stack<Double> stack = new Stack<>();
        Map<String, Double> parametrsOfDefine = new HashMap<>();
        Print print = new Print();
        Push push = new Push(parametrsOfDefine);
        push.performCommand(stack, "PUSH 8");
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        System.setOut(new PrintStream(outputStream));
        print.performCommand(stack, "PRINT");
        String output = outputStream.toString().trim();
        assertEquals("8.0", output);
        System.setOut(System.out);
    }
    @Test
    void testWithEmptyStack() throws Exception {
        Stack<Double> stack = new Stack<>();
        Print print = new Print();
        Exception exception = assertThrows(Exception.class, () -> {
            print.performCommand(stack, "PRINT");
        });
        String expectedMessage = "Stack is empty";
        assertTrue(exception.getMessage().contains(expectedMessage));
    }
}
