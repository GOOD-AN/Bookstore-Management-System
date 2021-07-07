#ifndef MIAN_H
#define MIAN_H

#include <QObject>
#include <QSqlDatabase>

class main : public QObject
{
    Q_OBJECT
public:
    static QSqlDatabase database;
};

#endif // MIAN_H
