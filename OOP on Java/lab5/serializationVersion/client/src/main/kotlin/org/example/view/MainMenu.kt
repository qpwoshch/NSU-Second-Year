package org.example.view

import javafx.geometry.Pos
import javafx.scene.Scene
import javafx.scene.control.Button
import javafx.scene.control.Label
import javafx.scene.control.TextField
import javafx.scene.layout.VBox
import javafx.stage.Stage
import java.net.Socket

class MainMenu(private val socket : Socket) : VBox() {
    private val sendButton = Button("Start")
    private val text = Label("Hello, for continue Enter your name")
    private val inputField = TextField().apply {
        promptText = "Enter your name"
        maxWidth = 200.0
    }

    private var listenerForButton: ButtonStart? = null

    fun setListener(listener: ButtonStart) {
        this.listenerForButton = listener
    }

    fun show(stage: Stage) {
        spacing = 20.0
        alignment = Pos.CENTER
        children.addAll(text, inputField, sendButton)

        sendButton.setOnAction {
            val name = inputField.text.trim()
            if (name.isNotEmpty()) {
                listenerForButton?.setName(name)
            }
        }

        stage.scene = Scene(this, 400.0, 500.0)
        stage.title = "Menu"
        stage.show()
        stage.setOnCloseRequest {
            socket.close()
        }
    }


}
