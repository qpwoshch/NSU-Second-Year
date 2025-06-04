package org.example.command;
import org.junit.jupiter.api.Test;
import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

import static org.junit.jupiter.api.Assertions.*;


public class DefineTest {
    @Test
    void TestPerformDefine() throws Exception {
        Map<String, Double> parametrsOfDefine = new HashMap<>();
        Stack<Double> stack = new Stack<>();
        Define define = new Define(parametrsOfDefine);
        define.performCommand(stack, "DEFINE a 2");
        assertEquals(2, parametrsOfDefine.get("a"));
    }
    @Test
    void TestPerformDefineWithException() throws Exception {
        Map<String, Double> parametrsOfDefine = new HashMap<>();
        Stack<Double> stack = new Stack<>();
        Define define = new Define(parametrsOfDefine);
        Exception exception = assertThrows(Exception.class, () -> {
            define.performCommand(stack, "DEFINE b c");
        });
        String expectedMessage = "Enter the number with the second parameter";
        assertTrue(exception.getMessage().contains(expectedMessage));
    }
}
