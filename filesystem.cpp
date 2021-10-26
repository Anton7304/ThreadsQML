#include "filesystem.h"

FileSystem::FileSystem(QObject *parent) : QObject(parent)
{

}

QByteArray FileSystem::readFile(QString path)
{
    QFile file(path.replace("file:///",""));
        if (!file.open(QIODevice::ReadOnly))
            return QByteArray();
        return file.readAll();
}
