package org.example.command;

import org.junit.jupiter.api.Test;

import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

import static org.junit.jupiter.api.Assertions.*;

public class SqrtTest {
    @Test
    void testPerformSqrt() throws Exception {
        Stack<Double> stack = new Stack<>();
        Map<String, Double> parametrsOfDefine = new HashMap<>();
        Sqrt sqrt = new Sqrt();
        Push push = new Push(parametrsOfDefine);
        push.performCommand(stack, "PUSH 9");
        sqrt.performCommand(stack, "SQRT");
        assertEquals(3.0, stack.peek());
    }
    @Test
    void testWithEmptyStack() throws Exception {
        Stack<Double> stack = new Stack<>();
        Sqrt sqrt = new Sqrt();
        Exception exception = assertThrows(Exception.class, () -> {
            sqrt.performCommand(stack, "SQRT");
        });
        String expectedMessage = "Stack is empty";
        assertTrue(exception.getMessage().contains(expectedMessage));
    }
    @Test
    void testWithNegativeNumber() throws Exception {
        Stack<Double> stack = new Stack<>();
        Map<String, Double> parametrsOfDefine = new HashMap<>();
        Sqrt sqrt = new Sqrt();
        Push push = new Push(parametrsOfDefine);
        push.performCommand(stack, "PUSH -3");
        Exception exception = assertThrows(Exception.class, () -> {
            sqrt.performCommand(stack, "SQRT");
        });
        String expectedMessage = "Number -3.0<0, but the number must be non-negative";
        assertTrue(exception.getMessage().contains(expectedMessage));
    }
}
