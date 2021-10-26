#include "wordscalc.h"

WordsCalc::WordsCalc()
{

}

bool WordsCalc::pred(const QPair<QString, int> &a, const QPair<QString, int> &b)
{
    return a.second > b.second;
}

void WordsCalc::setFileData(QByteArray data)
{
    fileData = data;
}

void WordsCalc::calc()
{
    bool m_loading = true;
    emit dataLoading(m_loading);
    //QThread::sleep(4);//for test
    QTextStream st(fileData);
    st.setCodec("UTF-8");
    QMap<QString, int> wordsCount;
    QMap<QString, int> wordsMap;

    QString word;

    while(!st.atEnd())
    {
        st>>word;
        ++wordsCount[word];
    }
    QList<QPair<QString,int>> listOfPairs;//(wordsCount.begin(),wordsCount.end());
    for(auto k : wordsCount.keys())
    {
        listOfPairs.append(QPair<QString,int>(k,wordsCount.value(k)));
    }
    //std::sort(listOfPairs.begin(),listOfPairs.end());
    std::sort(std::begin(listOfPairs), std::end(listOfPairs),pred);
    int m_maxCount = listOfPairs.at(0).second;
    emit maxYAxisChanged(m_maxCount);
//    for(int i = 0; i < listOfPairs.count(); i++)
//    {
//        qDebug()<<listOfPairs.at(i).first<<listOfPairs.at(i).second;
//    }
    for(int i = 0; i < 15; i++)
    {
        wordsMap.insert(listOfPairs.at(i).first,listOfPairs.at(i).second);
    }

//    for(int i = 0; i< wordsMap.count(); i++)
//    {
//        qDebug()<<wordsMap.keys().at(i)<<wordsMap.values().at(i);
//    }


    QMapIterator<QString, int> i(wordsMap);
    QVariantMap m_data;
    while (i.hasNext()) {
        i.next();
        m_data.insert(i.key(), i.value());
    }
    m_loading = false;
    emit dataLoading(m_loading);
    emit dataChanged(m_data);
    emit finished();
}
