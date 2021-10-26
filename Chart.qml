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
            //console.log(i, "=", p)
            //barSer.append(i,p)
            //count.push(p)
            wrd.append(p, 0)
            wordCategories.push(i)
        }
        //wrd.append(8, 0)
        barCategoriesAxis.categories = wordCategories
        //barSet.values = count
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
                //title: "Bar series"
//                Layout.fillWidth: true
//                Layout.fillHeight: true
                width: chartItem.width
                height: chartItem.height
                animationOptions: ChartView.SeriesAnimations
                //anchors.fill: parent
                //legend.alignment: Qt.AlignBottom
                antialiasing: true

                BarCategoryAxis {
                    id: barCategoriesAxis
                    //titleText: "Words"
                }
                ValueAxis{
                    id: valueAxisY2
                    //tickType: ValueAxis.TicksFixed
                    tickCount: 6
                    min: 0
                    max: 10
                    //titleText: "Count"
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
