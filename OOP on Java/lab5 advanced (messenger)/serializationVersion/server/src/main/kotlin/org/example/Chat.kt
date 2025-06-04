import org.example.History
import org.example.Message
import org.example.Server
import java.io.EOFException
import java.io.ObjectInputStream
import java.io.ObjectOutputStream
import java.net.Socket

class Chat(private val socket : Socket, private val server: Server, private val history: MutableMap<String, History>, private val listOfChat: MutableList<String>) : Runnable {
    private val writer = ObjectOutputStream(socket.getOutputStream())
    private val reader = ObjectInputStream(socket.getInputStream())
    private var name = ""
    private var currentChat: String = ""
    override fun run() {
        try {
            for (chat in listOfChat) {
                writer.writeObject(Message("", "", "", "chat", chat))
                writer.flush()
            }
            while (true) {
                val message = reader.readObject() as? Message ?: break
                val key = message.key
                currentChat = message.chat
                if (key == "New chat") {
                    server.addChat(currentChat)
                    server.broadcastForChats(Message("", "", "", "chat", currentChat))
                }
            }
        } catch (e: EOFException) {
            println("$name is disconnect")
        } catch (e: Exception) {
            e.printStackTrace()
        }finally {

        }
    }
}