package org.example

import Chat
import java.net.Socket
import javafx.stage.Stage
import org.example.view.ButtonStart
import org.example.view.MainMenu

class User {
    private val socket = Socket("localhost", 8081)


    fun connect(stage : Stage) {
        val menu = MainMenu(socket)
        menu.setListener(object : ButtonStart {
            override fun setName(name : String) {
                Chat(socket).show(stage, name, this@User)
            }
        })
        menu.show(stage)
    }
}