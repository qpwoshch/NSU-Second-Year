package org.example

import java.io.BufferedWriter
import java.io.ObjectOutputStream
import java.net.ServerSocket
import java.util.concurrent.Executors

class Server {
    private val clients = mutableMapOf<String, BufferedWriter>()
    private val serverSocket = ServerSocket(8081)
    private val threadPool = Executors.newCachedThreadPool()
    private val history = History()



    fun startServer() {
        while (true) {
            val clientSocket = serverSocket.accept()
            threadPool.submit {
                val user = User(clientSocket, this, history)
                user.run()
            }
        }
    }

    fun addClient(name: String, writer: BufferedWriter) {
        clients[name] = writer
    }


    fun removeClient(name: String) {
        synchronized(clients) {
            clients.remove(name)
        }
    }


    fun broadcast(message: String, sender: BufferedWriter) {
        synchronized(clients) {
            clients.forEach { (_, clientWriter) ->
                if (clientWriter != sender) {
                    clientWriter.write(message + "\n")
                    clientWriter.flush()
                }
            }
        }
    }



    fun getClients(): List<String> {
        return clients.keys.toList()
    }


}