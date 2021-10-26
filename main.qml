import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtMultimedia 5.14
import QtQuick.Layouts 1.14
import QtCharts 2.14
import QtQuick.Dialogs 1.2
import ru.test.parser 1.0

Window {
    visible: true
    width: 1080
    height: 2400
    title: qsTr("Hello World")

    function progressBarVisible(loading){
        console.log("LOADING IS",loading);
        progressRect.visible = loading
    }

    Parser {
        id: parser
        onDataChanged: chart.fillChart()
        onMaxYAxisChanged: chart.setMaxAxisY()
        onDataLoading:  progressBarVisible(parser.loading)
    }
    Chart {
        id: chart
    }
    Row{
        Button {
            id: openFileBtn
            text: "Открыть файл"
            onClicked: {
                filePicker.open()
            }
        }
        Button {
            id: clearChartBtn
            text: "Очистить"
            onClicked: {
                chart.clearChart()
            }
        }
    }
    Rectangle {
        id: progressRect
        anchors.fill: parent
        color: "#80FFFFFF"
        visible: false
        ProgressBar {
            anchors.verticalCenter: parent.verticalCenter
            indeterminate: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

    }

    FileDialog {
        id: filePicker
        selectExisting: true
        selectFolder: false
        selectMultiple: false
        onAccepted: {
            parser.parseFile(filePicker.fileUrl)
            parser.startCalc()
        }
    }
}
