package org.example

import java.io.*
import java.net.Socket

class User(private val socket : Socket, private val server: Server, private val history: MutableMap<String, History>, private val listOfChat: MutableList<String>) : Runnable {
    private val writer = ObjectOutputStream(socket.getOutputStream())
    private val reader = ObjectInputStream(socket.getInputStream())
    private var name = ""
    private var currentChat: String = ""
    override fun run() {
        try {
            while (true) {
                val message = reader.readObject() as? Message ?: break
                val sender = message.name
                val text = message.message
                val time = message.time
                val key = message.key
                currentChat = message.chat
                if (key == "Name for new client") {
                    name = sender
                    server.broadcast(Message(name, "connect in chat", " ", "change in chat participants", currentChat), writer)
                    logger.info("$name connect on server")
                    val listOfHistory = history[currentChat]?.getHistory()
                    writer.flush()
                    for (message in listOfHistory ?: emptyList()) {
                        writer.writeObject(message)
                        writer.flush()
                        println(message.message)
                    }
                    val clients = server.getClientsInChat(currentChat)
                    for (clientName in clients) {
                        writer.writeObject(Message(clientName, "connect in chat", " ", "add in list of client", currentChat))
                        writer.flush()
                    }
                    server.addClient(name, writer, currentChat)
                }
                else {
                    val mes = Message(sender, text, time, "new message", currentChat)
                    logger.info("$name wrote: $text")
                    server.broadcast(mes, writer)
                    history.getOrPut(currentChat) { History() }.addMessage(mes)
                }
            }
        } catch (e: EOFException) {
            println("$name is disconnect")
        } catch (e: Exception) {
            e.printStackTrace()
        }finally {
            server.broadcast(Message(name, "leave from chat", " ", "change in chat participants", currentChat), writer)
            logger.info("$name is disconnect")
            server.removeClient(name, currentChat)
            reader.close()
            writer.close()
            socket.close()
        }
    }
}