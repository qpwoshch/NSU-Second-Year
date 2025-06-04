package org.example

import Chat
import java.net.Socket
import javafx.stage.Stage
import org.example.view.ButtonStart
import org.example.view.ListOfChat
import org.example.view.MainMenu
import org.example.view.ButtonConnect
import java.io.IOException
import java.io.ObjectInputStream
import java.io.ObjectOutputStream

class User {
    private val socket = Socket("localhost", 8081)
    private val writer = ObjectOutputStream(socket.getOutputStream())
    private val reader = ObjectInputStream(socket.getInputStream())
    private val socket2 = Socket("localhost", 8082)
    private val writer2 = ObjectOutputStream(socket2.getOutputStream())
    private val reader2 = ObjectInputStream(socket2.getInputStream())

    fun connect(stage: Stage) {
        val menu = MainMenu(socket)
        val listOfChat = ListOfChat(socket2, stage, writer2, reader2)

        menu.setListener(object : ButtonStart {
            override fun setName(name: String) {
                listOfChat.setListener(object : ButtonConnect {
                    override fun setChat(nameOfChat: String) {
                        Chat(socket, writer, reader).show(stage, name, nameOfChat)
                    }
                })
                stage.scene.root = listOfChat
            }
        })

        menu.show(stage)
//        stage.setOnCloseRequest {
//            try {
//                reader.close()
//                writer.close()
//                socket.close()
//                reader2.close()
//                writer2.close()
//                socket2.close()
//            } catch (e: IOException) {
//                e.printStackTrace()
//            }
//        }
    }

}
