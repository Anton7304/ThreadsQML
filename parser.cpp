#include "parser.h"
#include <algorithm>


Parser::Parser() : QObject(nullptr)
{
    thread1.setObjectName("SecondThread");
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
    qDebug() << "Now WordsCalc is placed in: " << wordsCalc->thread();
    wordsCalc->moveToThread(&thread1);//переводим класс для расчётов в отдельный поток
    qDebug() << "Now WordsCalc is placed in: " << wordsCalc->thread();

    connect(wordsCalc, &WordsCalc::dataLoading,this,&Parser::transitLoading);
    connect(wordsCalc, &WordsCalc::dataChanged,this,&Parser::transitData);
    connect(wordsCalc, &WordsCalc::maxYAxisChanged,this,&Parser::transitMaxCount);
    connect(wordsCalc, &WordsCalc::finished, wordsCalc, &QObject::deleteLater);
    connect(this, &Parser::startCalc, wordsCalc, &WordsCalc::calc);
    thread1.start();
}

void Parser::transitData(const QVariantMap &data)
{
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
