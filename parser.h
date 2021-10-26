#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QQmlListProperty>
#include <QDebug>
#include <QTextStream>
#include <QThread>
#include "filesystem.h"
#include "wordscalc.h"

class Parser : public QObject
{
    Q_OBJECT
public:
    Parser();
    ~Parser();
    Q_INVOKABLE void parseFile(QString path);
    Q_PROPERTY(const QVariantMap data READ data NOTIFY dataChanged)
    Q_PROPERTY(int maxCount READ maxCount NOTIFY maxYAxisChanged)
    Q_PROPERTY(bool loading READ loading NOTIFY dataLoading)

    QVariantMap data() const
    {
        return m_data;
    }
    int maxCount() const
    {
        return m_maxCount;
    }
    bool loading() const
    {
        return m_loading;
    }
public slots:
    void transitData(const QVariantMap& data);
    void transitMaxCount(int maxCount);
    void transitLoading(bool loading);
private:
    QByteArray fileData;
    QVariantMap m_data;
    int m_maxCount;
    bool m_loading;
    QThread thread1;
signals:
    void dataChanged(const QVariantMap& data);
    void maxYAxisChanged(int maxCount);
    void dataLoading(bool loading);
    void finished();
    Q_INVOKABLE void startCalc();
};

#endif // PARSER_H
