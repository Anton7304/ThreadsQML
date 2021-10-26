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
    void calc();
private:
    QByteArray fileData;
signals:
    void dataChanged(const QVariantMap& data);
    void maxYAxisChanged(int maxCount);
    void dataLoading(bool loading);
    void finished();

};

#endif // WORDSCALC_H
