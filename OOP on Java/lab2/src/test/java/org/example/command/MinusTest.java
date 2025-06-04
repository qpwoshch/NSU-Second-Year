package org.example.command;
import org.junit.jupiter.api.Test;

import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

import static org.junit.jupiter.api.Assertions.*;


public class MinusTest {
    @Test
    void testPerformMinus() throws Exception {
        Stack<Double> stack = new Stack<>();
        Map<String, Double> parametrsOfDefine = new HashMap<>();
        Minus minus = new Minus();
        Push push = new Push(parametrsOfDefine);
        push.performCommand(stack, "PUSH 8");
        push.performCommand(stack, "PUSH 7");
        minus.performCommand(stack, "-");
        assertEquals(1, stack.peek());
    }
    @Test
    void testZeroValuesOnStack() throws Exception {
        Stack<Double> stack = new Stack<>();
        Minus minus = new Minus();
        Exception exception = assertThrows(Exception.class, () -> {
            minus.performCommand(stack, "-");
        });
        String expectedMessage = "there are 0 values on the stack, you need at least 2";
        assertTrue(exception.getMessage().contains(expectedMessage));
    }
}
