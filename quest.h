#ifndef QUEST_H
#define QUEST_H

#include <QDialog>

class QUEST : public QDialog
{
    Q_OBJECT

public:
    explicit QUEST(QWidget *parent = nullptr);
    ~QUEST();

    bool qusetuser(QString username,QString password);

private:
};

#endif // QUEST_H
