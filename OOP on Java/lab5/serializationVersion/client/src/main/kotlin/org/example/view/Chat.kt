import javafx.application.Platform
import javafx.geometry.Insets
import javafx.geometry.Pos
import javafx.scene.Scene
import javafx.scene.control.*
import javafx.scene.layout.HBox
import javafx.scene.layout.Priority
import javafx.scene.layout.Region
import javafx.scene.layout.VBox
import javafx.stage.Stage
import org.example.Message
import java.io.*
import java.lang.Integer.parseInt
import java.net.Socket
import kotlin.concurrent.thread

class Chat(private val socket: Socket) : VBox() {
    private val writer = ObjectOutputStream(socket.getOutputStream())
    private val reader = ObjectInputStream(socket.getInputStream())
    private var clients = mutableListOf<String>()

    private val historyBox = VBox().apply {
        spacing = 5.0
        padding = Insets(10.0)
    }

    private val scrollPane = ScrollPane(historyBox).apply {
        prefHeight = 400.0
        isFitToWidth = true
        vbarPolicy = ScrollPane.ScrollBarPolicy.ALWAYS
    }

    private val inputField = TextField().apply {
        promptText = "Enter a message"
    }

    private val sendButton = Button("Send")
    private val buttonOfUsers = Button("Participants")

    private val usersPopupBox = VBox().apply {
        style = "-fx-background-color: white; -fx-border-color: #ccc; -fx-padding: 10;"
        spacing = 5.0
        isVisible = false
        isManaged = false
        maxHeight = 150.0
    }

    fun show(stage: Stage, name: String) {
        writer.writeObject(Message(name, " ", " ", "new client"))
        writer.flush()
        clients.add(name)

        spacing = 10.0
        padding = Insets(10.0)

        sendButton.setOnAction {
            val message = inputField.text
            if (message.isNotBlank()) {
                val time = java.time.LocalTime.now().withNano(0).toString()
                writer.writeObject(Message(name, message, time, "new message"))
                writer.flush()
                addMessage("You: $message", time, Pos.CENTER_RIGHT)
                inputField.clear()
            }
        }

        buttonOfUsers.setOnAction {
            if (usersPopupBox.isVisible) {
                usersPopupBox.isVisible = false
                usersPopupBox.isManaged = false
            } else {
                usersPopupBox.children.clear()
                for (nameOfClient in clients.distinct()) {
                    usersPopupBox.children.add(Label(nameOfClient))
                }
                usersPopupBox.isVisible = true
                usersPopupBox.isManaged = true
            }
        }

        val buttonBox = HBox().apply {
            spacing = 10.0
            alignment = Pos.CENTER
            children.addAll(sendButton, Region(), buttonOfUsers)
            HBox.setHgrow(children[1], Priority.ALWAYS)
        }

        children.addAll(scrollPane, inputField, buttonBox, usersPopupBox)

        stage.scene = Scene(this, 400.0, 500.0)
        stage.title = "Chat"
        stage.show()

        thread {
            try {
                while (!socket.isClosed) {
                    parsing(reader.readObject() as? Message ?: break)
                }
            } catch (e: Exception) {
                println("${e.message}")
            }
        }

        stage.setOnCloseRequest {
            socket.close()
        }
    }

    private fun addMessage(text: String, time: String, alignment: Pos) {
        val messageLabel = Label(text).apply {
            style = "-fx-background-color: lightgray; -fx-padding: 5px; -fx-background-radius: 5px;"
            maxWidth = 300.0
            isWrapText = true
        }

        val timeLabel = Label(time).apply {
            style = "-fx-font-size: 10px; -fx-text-fill: gray;"
        }

        val messageBox = VBox(messageLabel, timeLabel).apply {
            spacing = 2.0
            this.alignment = alignment
        }

        val container = HBox(messageBox).apply {
            this.alignment = alignment
        }

        HBox.setHgrow(messageBox, Priority.ALWAYS)
        historyBox.children.add(container)
        scrollPane.vvalue = 1.0
    }



    private fun addInfo(text: String, alignment: Pos) {
        val label = Label(text).apply {
            maxWidth = Double.MAX_VALUE
            isWrapText = true
            style = "-fx-alignment: center;"
        }
        val container = HBox(label).apply {
            this.alignment = alignment
            prefWidth = Double.MAX_VALUE
        }
        HBox.setHgrow(label, Priority.ALWAYS)
        historyBox.children.add(container)
        scrollPane.vvalue = 1.0
    }

    private fun parsing(message : Message) {
        val nameFromServer = message.name
        val text = message.message
        val key = message.key
        val time = message.time
        Platform.runLater {
            when (key) {
                "new message" -> addMessage("$nameFromServer: $text", time, Pos.CENTER_LEFT)
                "change in chat participants" -> {
                    addInfo("$nameFromServer: $text", Pos.CENTER)
                    if (text == "leave from chat") {
                        clients.remove(nameFromServer)
                    } else {
                        if (!clients.contains(nameFromServer)) {
                            clients.add(nameFromServer)
                        }
                    }
                    if (usersPopupBox.isVisible) {
                        usersPopupBox.children.clear()
                        for (nameOfClient in clients.distinct()) {
                            usersPopupBox.children.add(Label(nameOfClient))
                        }
                    }
                }
                "add in list of client" -> {
                    if (!clients.contains(nameFromServer)) {
                        clients.add(nameFromServer)
                    }
                }
            }
        }
    }
}
