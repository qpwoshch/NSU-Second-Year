package org.example;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class ControllerTest {

    @Test
    void testStart() {
        Controller controller = new Controller();

        assertDoesNotThrow(() -> controller.start());
    }
}
