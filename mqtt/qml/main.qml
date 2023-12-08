import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.2

Window {
  id: root
  width: 640
  height: 480
  visible: true

  property int linesCount: 0
  property int messagesCount: 0

  property string message

  Component.onCompleted: {
    manager.finish.connect(onFinish)
  }

  Component.onDestruction: {
    manager.finish.disconnect(onFinish)
  }

  Connections {
    target: manager

    function onError(errorText) {
      root.message = errorText
      dialog.open()
    }
  }

  function onFinish(linesCount, messagesCount) {
    root.linesCount = linesCount
    root.messagesCount = messagesCount
    root.message = "Lines readed : " + root.linesCount + "\n" + "Messages sent : " + root.messagesCount
    dialog.open()
  }

  Dialog {
    id: dialog
    standardButtons: Dialog.Ok
    Label {
      text: root.message
    }
  }


  Item {
    anchors.fill: parent
    anchors.margins: 10

    Column {
      spacing: 10

      TextField {
        id: hostInput
        placeholderText: "host"
        text: "test.mosquitto.org"
      }

      TextField {
        id: portInput
        placeholderText: "port"
        inputMethodHints: Qt.ImhDigitsOnly
        text: manager.port
      }

      TextField {
        id: userNameInput
        placeholderText: "username"
        text: manager.userName
      }

      TextField {
        id: passwordInput
        placeholderText: "password"
        echoMode: TextInput.Password

        Button {
          anchors.right: parent.right
          width: height
          flat: true
          icon.source: "qrc:/icon/showPass"
          icon.width: width
          icon.height: width / 2

          onClicked: {
            if (passwordInput.echoMode === TextInput.Password) {
              icon.source = "qrc:/icon/hidePass"
              passwordInput.echoMode = TextInput.Normal
            } else {
              icon.source = "qrc:/icon/showPass"
              passwordInput.echoMode = TextInput.Password
            }
          }
        }

      }

      TextField {
        id: topicInput
        placeholderText: "topic"
        text: "piklema/test"

      }

      TextField {
        id: filepathInput
        placeholderText: "Enter filepath"
        readOnly: true

        Button {
          anchors.right: parent.right
          height: parent.height
          width: height
          flat: true
          icon.source: "qrc:/icon/openFile"
          icon.width: width

          onClicked: fileDialog.open()
        }
      }

      FileDialog {
        id: fileDialog
        title: "Choose a file"
        modality: Qt.ApplicationModal
        folder: shortcuts.home
        onAccepted: {
          filepathInput.text = fileDialog.fileUrl
        }
      }

      Button {
        text: "RUN"
        enabled: hostInput.text && portInput.text && userNameInput.text && passwordInput.text && topicInput.text && filepathInput.text

        onClicked: {
          manager.host = hostInput.text
          manager.port = Number(portInput.text)
          manager.userName = userNameInput.text
          manager.password = passwordInput.text
          manager.topic = topicInput.text
          manager.filePath = filepathInput.text

          manager.run()
        }
      }
    }

    Rectangle {
      id: statusRect
      anchors.right: parent.right
      anchors.bottom: parent.bottom
      width: 20
      height: width
      radius: width / 2
      color: manager.isConnected ? "lime" : "#FF0000"
    }
  }
}
