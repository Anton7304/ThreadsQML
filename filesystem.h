#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QObject>
#include <QFile>


class FileSystem : public QObject
{
    Q_OBJECT
public:
    explicit FileSystem(QObject *parent = nullptr);
    static QByteArray readFile(QString path);

};

#endif // FILESYSTEM_H
