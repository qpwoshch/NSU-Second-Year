package org.example;

import org.junit.jupiter.api.Test;

import java.io.*;

import static org.junit.jupiter.api.Assertions.*;

public class ControllerTest {
    @Test
    void testVerificationOfTheInputFile() {
        Controller controller = new Controller();
        String[] data = new String[0];
        int a = controller.VerificationOfTheInputFile(data);
        assertEquals(0, a);
        String[] data1 = new String[1];
        data1[0] = "fg";
        a = controller.VerificationOfTheInputFile(data1);
        assertEquals(1, a);
    }

    @Test
    void testStartWithConsole() {
        Controller controller = new Controller();
        String data = "+\nPUSH 5\nPUSH 3\n# gf\nEXIT";
        InputStream input = new ByteArrayInputStream(data.getBytes());
        System.setIn(input);
        controller.start(new String[0]);
        assertEquals(2, controller.stack.size());
        assertEquals(3.0, controller.stack.pop());
        assertEquals(5.0, controller.stack.pop());
        System.setIn(System.in);
    }
    @Test
    void testStartWithFile() throws IOException {
        Controller controller = new Controller();
        ByteArrayOutputStream errContent = new ByteArrayOutputStream();
        File file = File.createTempFile("test", ".txt");
        FileWriter writer = new FileWriter(file);
        writer.write("PUSH 9\n# fg");
        writer.close();
        controller.start(new String[]{file.getAbsolutePath()});
        assertEquals(1, controller.stack.size());
        assertEquals(9.0, controller.stack.pop());
    }

    @Test
    void testStartWithFIleWithException() throws IOException {
        Controller controller = new Controller();
        ByteArrayOutputStream errContent = new ByteArrayOutputStream();
        System.setErr(new PrintStream(errContent));
        File file = File.createTempFile("test", ".txt");
        FileWriter writer = new FileWriter(file);
        writer.write("+");
        writer.close();
        controller.start(new String[]{file.getAbsolutePath()});
        String errorOutput = errContent.toString();
        assertTrue(errorOutput.contains("java.lang.Exception: there are 0 values on the stack, you need at least 2"));
        System.setErr(System.err);
    }

    @Test
    void TestStartWithErrorFile() {
        File file = new File("file.txt");
        ByteArrayOutputStream errContent = new ByteArrayOutputStream();
        System.setErr(new PrintStream(errContent));
        Controller controller = new Controller();
        controller.start(new String[]{file.getAbsolutePath()});
        String errorOutput = errContent.toString();
        assertTrue(errorOutput.contains("Error while open file"));
        System.setErr(System.err);
    }
}
