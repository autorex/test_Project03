#ifndef SMDIALOG_H
#define SMDIALOG_H
#include <QWidget>
#include <QSharedMemory>
namespace Ui {
class SMDialog;
}
class SMDialog : public QWidget
{
Q_OBJECT
public:
explicit SMDialog(QWidget *parent = 0);
~SMDialog();
private slots:
void on_pushButton_clicked();
void on_loadfileButton_clicked();
void on_loadButton_clicked();
private:
void detach();
private:
Ui::SMDialog *ui;
QSharedMemory sharedmemory;
};
#endif // SMDIALOG_H
