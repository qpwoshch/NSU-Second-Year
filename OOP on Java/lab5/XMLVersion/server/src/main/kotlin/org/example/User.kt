package org.example


import java.io.*
import java.net.Socket


class User(private val socket : Socket, private val server: Server, private val history: History) : Runnable {
    private val reader = BufferedReader(InputStreamReader(socket.getInputStream()))
    private val writer = BufferedWriter(OutputStreamWriter(socket.getOutputStream()))
    private val xml = XML()
    private var name = ""
    override fun run() {
        try {
            name = xml.parseXMLLogin(reader.readLine() ?: return)["name"] ?: ""
            writer.write(xml.success() + "\n")
            writer.flush()
            server.broadcast(xml.makeXMLNewClient(name), writer)
            logger.info("$name connect on server")
            val listOfHistory = history.getHistory()
            for (message in listOfHistory) {
                writer.write(message + "\n")
                writer.flush()
            }
            val clients = server.getClients()
            for (clientName in clients) {
                writer.write(xml.addNewClient(clientName) + "\n")
                writer.flush()
            }
            server.addClient(name, writer)
            while (true) {
                val parsedMessage = xml.parseXMLMessage(reader.readLine() ?: break)
                val sender = parsedMessage["name"] ?: ""
                val text = parsedMessage["message"] ?: ""
                val time = parsedMessage["time"] ?: ""
                val mes = xml.makeXMLMessage(sender, text, time)
                logger.info("$name wrote: $text")
                server.broadcast(mes, writer)
                history.addMessage(mes)
            }
        } catch (e: EOFException) {
            println("$name is disconnect")
        } catch (e: Exception) {
            writer.write(xml.error(e.toString()) + "\n")
            writer.flush()
            e.printStackTrace()
        }finally {
            server.broadcast(xml.makeXMLLeaveClient(name), writer)
            logger.info("$name is disconnect")
            server.removeClient(name)
            reader.close()
            writer.close()
            socket.close()
        }
    }





}