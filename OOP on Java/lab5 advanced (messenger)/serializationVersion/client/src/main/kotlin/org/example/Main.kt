
package org.example

import javafx.application.Application
import javafx.stage.Stage

class Main : Application() {
    override fun start(primaryStage: Stage) {
        User().connect(primaryStage)
    }
}

fun main() {
    Application.launch(Main::class.java)
}
