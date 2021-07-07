#ifndef MIANWINDOWS_H
#define MIANWINDOWS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindows; }
QT_END_NAMESPACE

class mainwindows : public QMainWindow
{
    Q_OBJECT

public:
    mainwindows(QWidget *parent = nullptr);
    ~mainwindows();

    void showInfo();
    void showInfo2();

private:
    Ui::MainWindows *ui;
};
#endif // MIANWINDOWS_H
