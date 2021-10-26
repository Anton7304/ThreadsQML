#include "parser.h"
#include <algorithm>


Parser::Parser() : QObject(nullptr)
{

    thread1.setObjectName("WorkerThread");
}

Parser::~Parser()
{
    thread1.quit();
    thread1.wait();
}

void Parser::parseFile(QString path)
{

    WordsCalc * wordsCalc = new WordsCalc;
    wordsCalc->setFileData(FileSystem::readFile(path));
    qDebug() << "Now worker is placed in: " << wordsCalc->thread();
    wordsCalc->moveToThread(&thread1);
    qDebug() << "Now worker is placed in: " << wordsCalc->thread();

    connect(wordsCalc, &WordsCalc::dataLoading,this,&Parser::transitLoading);
    connect(wordsCalc, &WordsCalc::dataChanged,this,&Parser::transitData);
    connect(wordsCalc, &WordsCalc::maxYAxisChanged,this,&Parser::transitMaxCount);
    connect(wordsCalc, &WordsCalc::finished, wordsCalc, &QObject::deleteLater);
    connect(this, &Parser::startCalc, wordsCalc, &WordsCalc::calc);
    thread1.start();
    /*fileData.clear();
    qDebug() << "Path: " << path;
    fileData = FileSystem::readFile(path);
    qDebug() << "Now worker is placed in: " << this->thread();
    this->thread()->moveToThread(&thread1);
    qDebug() << "Now worker is placed in: " << thread1.thread();
    connect(&thread1, &QThread::started, this, &Parser::parse);
    connect(this, &Parser::finished, &thread1, &QThread::terminate);
    thread1.start();
    //parse(FileSystem::readFile(path));*/
}

void Parser::parse(const QVariantMap &data)
{

//    qDebug()<<"THREAD:"<<data;

//    m_loading = true;
//    emit dataLoading(m_loading);
//    //thread1.msleep(7000);
//    QTextStream st(fileData);
//    QMap<QString, int> wordsCount;
//    QMap<QString, int> wordsMap;

//    QString word;

//    while(!st.atEnd())
//    {
//        st>>word;
//        ++wordsCount[word];
//    }
//    QList<QPair<QString,int>> listOfPairs;//(wordsCount.begin(),wordsCount.end());
//    for(auto k : wordsCount.keys())
//    {
//        listOfPairs.append(QPair<QString,int>(k,wordsCount.value(k)));
//    }
//    //std::sort(listOfPairs.begin(),listOfPairs.end());
//    std::sort(std::begin(listOfPairs), std::end(listOfPairs),pred);
//    m_maxCount = listOfPairs.at(0).second;
//    emit maxYAxisChanged(m_maxCount);
//    for(int i = 0; i < listOfPairs.count(); i++)
//    {
//        qDebug()<<listOfPairs.at(i).first<<listOfPairs.at(i).second;
//    }
//    for(int i = 0; i < 15; i++)
//    {
//        wordsMap.insert(listOfPairs.at(i).first,listOfPairs.at(i).second);
//    }

////    for(int i = 0; i< wordsMap.count(); i++)
////    {
////        qDebug()<<wordsMap.keys().at(i)<<wordsMap.values().at(i);
////    }


//    QMapIterator<QString, int> i(wordsMap);
//    while (i.hasNext()) {
//        i.next();
//        m_data.insert(i.key(), i.value());
//    }
//    m_loading = false;
//    emit dataLoading(m_loading);
//    emit dataChanged(m_data);
//    emit finished();

    //for(QString word; st >> word; ++wordsCount[word]);
}

void Parser::transitData(const QVariantMap &data)
{
    //qDebug()<<"Parser::parse"<<data;
    m_data = data;
    emit dataChanged(m_data);
}

void Parser::transitMaxCount(int maxCount)
{
    m_maxCount = maxCount;
    emit maxYAxisChanged(m_maxCount);
}

void Parser::transitLoading(bool loading)
{
    m_loading = loading;
    emit dataLoading(m_loading);
}

//bool Parser::pred(const QPair<QString, int> &a, const QPair<QString, int> &b)
//{
//    return a.second > b.second;
//}
