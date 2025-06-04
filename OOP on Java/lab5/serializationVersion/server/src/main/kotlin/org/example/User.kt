package org.example

import java.io.*
import java.net.Socket

class User(private val socket : Socket, private val server: Server, private val history: History) : Runnable {
    private val writer = ObjectOutputStream(socket.getOutputStream())
    private val reader = ObjectInputStream(socket.getInputStream())
    private var name = ""
    override fun run() {
        try {
            val messageAboutNameOfNewClient = reader.readObject() as? Message ?: return
            name = messageAboutNameOfNewClient.name
            server.broadcast(Message(name, "connect in chat", " ", "change in chat participants"), writer)
            logger.info("$name connect on server")
            val listOfHistory = history.getHistory()
            writer.flush()
            for (message in listOfHistory) {
                writer.writeObject(message)
                writer.flush()
                println(message.message)
            }
            val clients = server.getClients()
            for (clientName in clients) {
                writer.writeObject(Message(clientName, "connect in chat", " ", "add in list of client"))
                writer.flush()
            }
            server.addClient(name, writer)
            while (true) {
                val message = reader.readObject() as? Message ?: break
                val sender = message.name
                val text = message.message
                val time = message.time
                val mes = Message(sender, text, time, "new message")
                logger.info("$name wrote: $text")
                server.broadcast(mes, writer)
                history.addMessage(mes)
            }
        } catch (e: EOFException) {
            println("$name is disconnect")
        } catch (e: Exception) {
            e.printStackTrace()
        }finally {
            server.broadcast(Message(name, "leave from chat", " ", "change in chat participants"), writer)
            logger.info("$name is disconnect")
            server.removeClient(name)
            reader.close()
            writer.close()
            socket.close()
        }
    }
}