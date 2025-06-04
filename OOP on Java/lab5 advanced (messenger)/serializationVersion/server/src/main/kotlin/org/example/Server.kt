package org.example

import Chat
import java.io.ObjectOutputStream
import java.net.ServerSocket
import java.util.concurrent.Executors

class Server {

    private val clients = mutableMapOf<String, MutableMap<String, ObjectOutputStream>>()
    private val chats = mutableListOf<String>()
    private val serverSocketForClient = ServerSocket(8081)
    private val serverSocketForChat = ServerSocket(8082)
    private val threadPool1 = Executors.newCachedThreadPool()
    private val threadPool2 = Executors.newCachedThreadPool()
    private val history = mutableMapOf<String, History>()



    fun startServer() {
        threadPool1.submit {
            while (true) {
                val clientSocket = serverSocketForClient.accept()
                threadPool1.submit {
                    val user = User(clientSocket, this, history, chats)
                    user.run()
                }
            }
        }
        threadPool2.submit {
            while (true) {
                val clientSocket = serverSocketForChat.accept()
                threadPool1.submit {
                    val chat = Chat(clientSocket, this, history, chats)
                    chat.run()
                }
            }
        }
    }


    fun addClient(name: String, writer: ObjectOutputStream, chat : String) {
        val chatClients = clients.getOrPut(chat) { mutableMapOf() }
        chatClients[name] = writer
    }

    fun addChat(name : String) {
        if (name !in chats) {
            chats.add(name)
        }
    }

    fun removeClient(name: String, chat: String) {
        synchronized(clients) {
            clients[chat]?.remove(name)
        }
    }




    fun broadcast(message: Message, sender: ObjectOutputStream) {
        synchronized(clients) {
            clients.values.forEach { chatClients ->
                chatClients.values.forEach { clientWriter ->
                    if (clientWriter != sender) {
                        clientWriter.writeObject(message)
                        println("Отправил $message $clientWriter")
                        clientWriter.flush()
                    }
                }
            }
        }
    }

    fun getClientsInChat(chat: String): List<String> {
        return clients[chat]?.keys?.toList() ?: emptyList()
    }


    fun broadcastForChats(message: Message) {
        synchronized(clients) {
            clients.values.forEach { chatClients ->
                chatClients.values.forEach { clientWriter ->
                    clientWriter.writeObject(message)
                    clientWriter.flush()
                }
            }
        }
    }



}