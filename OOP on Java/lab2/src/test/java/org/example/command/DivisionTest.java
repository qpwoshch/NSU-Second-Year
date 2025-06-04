package org.example.command;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

import static org.junit.jupiter.api.Assertions.*;


public class DivisionTest {
    @Test
    void testPerformDevision() throws Exception {
        Stack<Double> stack = new Stack<>();
        Map<String, Double> parametrsOfDefine = new HashMap<>();
        Division division = new Division();
        Push push = new Push(parametrsOfDefine);
        push.performCommand(stack, "PUSH 9");
        push.performCommand(stack, "PUSH 9");
        division.performCommand(stack, "/");
        assertEquals(1, stack.peek());
    }
    @Test
    void testDivisionByZero() throws Exception {
        Stack<Double> stack = new Stack<>();
        Map<String, Double> parametrsOfDefine = new HashMap<>();
        Division division = new Division();
        Push push = new Push(parametrsOfDefine);
        push.performCommand(stack, "PUSH 9");
        push.performCommand(stack, "PUSH 0");
        Exception exception = assertThrows(Exception.class, () -> {
            division.performCommand(stack, "/");
        });
        String expectedMessage = "It cannot be divided by 0";
        assertTrue(exception.getMessage().contains(expectedMessage));
    }
    @Test
    void testZeroValuesOnSTack() throws Exception {
        Stack<Double> stack = new Stack<>();
        Division division = new Division();
        Exception exception = assertThrows(Exception.class, () -> {
            division.performCommand(stack, "/");
        });
        String expectedMessage = "there are 0 values on the stack, you need at least 2";
        assertTrue(exception.getMessage().contains(expectedMessage));
    }
}
