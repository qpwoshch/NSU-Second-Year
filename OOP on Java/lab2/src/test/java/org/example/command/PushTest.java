package org.example.command;

import org.junit.jupiter.api.Test;

import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

import static org.junit.jupiter.api.Assertions.*;

public class PushTest {
    @Test
    void testPerformPush() throws Exception {
        Stack<Double> stack = new Stack<>();
        Map<String, Double> parametrsOfDefine = new HashMap<>();
        Push push = new Push(parametrsOfDefine);
        push.performCommand(stack, "PUSH 8");
        assertEquals(8.0, stack.peek());
    }
    @Test
    void testPushWithDefine() throws Exception {
        Stack<Double> stack = new Stack<>();
        Map<String, Double> parametrsOfDefine = new HashMap<>();
        Push push = new Push(parametrsOfDefine);
        Define define = new Define(parametrsOfDefine);
        define.performCommand(stack, "DEFINE a 2");
        push.performCommand(stack, "PUSH a");
        assertEquals(2.0, stack.peek());
    }
    @Test
    void testPushWithoutNumeriacalParametr() throws Exception {
        Stack<Double> stack = new Stack<>();
        Map<String, Double> parametrsOfDefine = new HashMap<>();
        Push push = new Push(parametrsOfDefine);
        Exception exception = assertThrows(Exception.class, () -> {
            push.performCommand(stack, "PUSH b");
        });
        String expectedMessage = "Enter the number with the parameter";
        assertTrue(exception.getMessage().contains(expectedMessage));
    }
}
