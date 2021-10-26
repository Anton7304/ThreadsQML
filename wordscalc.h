#ifndef WORDSCALC_H
#define WORDSCALC_H
#include <QObject>
#include <QDebug>
#include <QTextStream>
#include <QThread>

class WordsCalc : public QObject
{
    Q_OBJECT
public:
    WordsCalc();
    static bool pred(const QPair<QString,int> &a, const QPair<QString,int> &b);
    void setFileData(QByteArray data);
   // Q_INVOKABLE void parseFile(QString path);
//    Q_PROPERTY(const QVariantMap data READ data NOTIFY dataChanged)
//    Q_PROPERTY(int maxCount READ maxCount NOTIFY maxYAxisChanged)
//    Q_PROPERTY(bool loading READ loading NOTIFY dataLoading)
//    QVariantMap data() const
//    {
//        return m_data;
//    }
//    int maxCount() const
//    {
//        return m_maxCount;
//    }
//    bool loading() const
//    {
//        return m_loading;
//    }
//public slots:
    void calc();
private:
    QByteArray fileData;
//    QVariantMap m_data;
//    int m_maxCount;
//    bool m_loading;
//    QThread thread1;
signals:
    void dataChanged(const QVariantMap& data);
    void maxYAxisChanged(int maxCount);
    void dataLoading(bool loading);
    void finished();

};

#endif // WORDSCALC_H
