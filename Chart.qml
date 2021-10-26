import QtQuick 2.14
import QtCharts 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

Item {
    anchors.fill: parent
    id: chartItem

    property var barSer
    property var wordCategories:[]
    property var count:[]

    function fillChart() {
        clearChart()
        for(var i in parser.data) {
            var p = parser.data[i];
            wrd.append(p, 0)
            wordCategories.push(i)
        }
        barCategoriesAxis.categories = wordCategories
    }
    function clearChart() {
        wordCategories = []
        for(var i = wrd.count-1; i > -1; i--) {
            wrd.remove(i)
        }
        barCategoriesAxis.clear()
        valueAxisY2.min = 0
        valueAxisY2.max = 10
        valueAxisY2.tickCount = 6
        setMaxAxisY()
    }

    function setMaxAxisY() {
        if(valueAxisY2.max < parser.maxCount){
            valueAxisY2.max = parser.maxCount
            valueAxisY2.applyNiceNumbers()
        }
    }

    Flickable {
        anchors.fill: parent
        contentHeight: columnChart.height+100
        ColumnLayout {
            id: columnChart
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 0
            ChartView {
                id: barSeriesChart
                width: chartItem.width
                height: chartItem.height
                animationOptions: ChartView.SeriesAnimations
                antialiasing: true

                BarCategoryAxis {
                    id: barCategoriesAxis
                }
                ValueAxis{
                    id: valueAxisY2
                    tickCount: 6
                    min: 0
                    max: 10
                }
                HorizontalBarSeries {
                    id: myBarSeries
                    axisY: barCategoriesAxis
                    axisX: valueAxisY2
                    BarSet {
                        id: wrd
                        label: "TEST"
                    }
                }
            }
        }
    }

}
