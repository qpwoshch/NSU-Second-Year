package org.example.view

import javafx.application.Platform
import javafx.geometry.Insets
import javafx.geometry.Pos
import javafx.scene.control.*
import javafx.scene.layout.*
import javafx.stage.Stage
import javafx.util.Callback
import org.example.Message
import java.io.IOException
import java.io.ObjectInputStream
import java.io.ObjectOutputStream
import java.net.Socket
import kotlin.concurrent.thread

class ListOfChat(
    private val socket: Socket,
    private val stage: Stage,
    private val writer: ObjectOutputStream,
    private val reader: ObjectInputStream
) : VBox() {

    private val listOfChat = mutableListOf<String>()
    private var listenerForButton: ButtonConnect? = null
    private val listView = ListView<String>()
    private val createButton = Button("CreateNewChat").apply {
        styleClass.add("menu-button")
        maxWidth = Double.MAX_VALUE
        prefHeight = 40.0
    }

    init {
        spacing = 10.0
        padding = Insets(10.0)
        styleClass.add("menu-background")
        maxWidth = Double.MAX_VALUE
        VBox.setVgrow(listView, Priority.ALWAYS)

        listView.prefHeight = 300.0
        listView.maxWidth = Double.MAX_VALUE
        listView.selectionModel.selectionMode = SelectionMode.SINGLE

        listView.cellFactory = Callback {
            object : ListCell<String>() {
                private val connectButton = Button("Connect").apply {
                    styleClass.add("connect-button")
                    prefWidth = 100.0
                    prefHeight = 30.0
                }

                private val label = Label().apply {
                    maxWidth = Double.MAX_VALUE
                    isWrapText = true
                }

                private val hbox = HBox(10.0).apply {
                    alignment = Pos.CENTER
                    padding = Insets(5.0, 10.0, 5.0, 10.0)
                    maxWidth = Double.MAX_VALUE
                    HBox.setHgrow(label, Priority.ALWAYS)
                    children.addAll(label, connectButton)
                }

                init {
                    connectButton.setOnAction {
                        item?.let { listenerForButton?.setChat(it) }
                    }
                    style = "-fx-border-color: transparent transparent #CCCCCC transparent; -fx-border-width: 0 0 1 0;"
                }

                override fun updateItem(item: String?, empty: Boolean) {
                    super.updateItem(item, empty)
                    if (empty || item == null) {
                        text = null
                        graphic = null
                    } else {
                        label.text = item
                        graphic = hbox
                    }
                }
            }
        }

        children.addAll(listView, createButton)

        createButton.setOnAction {
            showCreateDialog()
        }

        startListening()
    }

    fun setListener(listener: ButtonConnect) {
        this.listenerForButton = listener
    }

    private fun startListening() {
        val thread = thread (isDaemon = true) {
            try {
                while (!socket.isClosed) {
                    val obj = reader.readObject() as? Message ?: break
                    parsing(obj)
                }
            } catch (e: Exception) {

            }
        }
        stage.setOnCloseRequest {
            try {
                socket.close()
                reader.close()
                writer.close()
            } catch (e: IOException) {
                e.printStackTrace()
            }
        }
    }

    private fun showCreateDialog() {
        val dialog = Dialog<String>().apply {
            title = "Create New Chat"
            headerText = "Enter chat name:"
        }

        val dialogPane = dialog.dialogPane
        val textField = TextField()
        val addButton = ButtonType("Add", ButtonBar.ButtonData.OK_DONE)

        dialogPane.content = VBox(10.0).apply {
            padding = Insets(20.0)
            children.add(textField)
        }
        dialogPane.buttonTypes.addAll(addButton, ButtonType.CANCEL)

        dialog.setResultConverter { buttonType -> if (buttonType == addButton) textField.text else null }

        val result = dialog.showAndWait()
        result.ifPresent { chatName ->
            if (chatName.isNotBlank()) {
                addChat(chatName)
                writer.writeObject(Message(" ", " ", " ", "New chat", chatName))
            }
        }
    }

    fun addChat(chatName: String) {
        if (chatName in listOfChat) return
        listOfChat.add(chatName)
        updateListView()
    }

    private fun updateListView() {
        listView.items.setAll(listOfChat)
    }

    private fun parsing(message: Message) {
        val key = message.key
        val chat = message.chat
        Platform.runLater {
            when (key) {
                "chat" -> addChat(chat)
            }
        }
    }
}
