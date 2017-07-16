#include "smdialog.h"
#include "ui_smdialog.h"
#include <QLabel>
#include <QFileDialog>
#include <QBuffer>
SMDialog::SMDialog(QWidget *parent) :
QWidget(parent),
ui(new Ui::SMDialog),sharedmemory("QSharedMemoryExample")
{
ui->setupUi(this);
setWindowTitle("Contoh shared memory");
}
SMDialog::~SMDialog()
{
delete ui;
}
void SMDialog::on_pushButton_clicked()
{
}
void SMDialog::on_loadfileButton_clicked()
{
if(sharedmemory.isAttached()) detach();
ui->label->setText(tr("Pilih gambar "));
QString filename = QFileDialog::getOpenFileName(0, QString(), QString(), tr("Gambar(*.png *.xpm *.jpg)"));
QImage image;
if (!image.load(filename))
{
ui->label->setText(tr("File yang anda pilih bukan merupakan gambar, silakan pilih yang lain."));
return;
}
ui->label->setPixmap(QPixmap::fromImage(image));
//memasukkan data ke dalam shared memory
QBuffer buffer;
buffer.open(QBuffer::ReadWrite);
QDataStream out(&buffer);
out << image;
int size = buffer.size();
if(!sharedmemory.create(size))
{
ui->label->setText(tr("Tidak bisa membuat segmen shared memory"));
return;
}
sharedmemory.lock();
char *to = (char*)sharedmemory.data();
const char* from = buffer.data().data();
memcpy(to, from, qMin(sharedmemory.size(), size));
sharedmemory.unlock();
}
void SMDialog::detach()
{
if(!sharedmemory.detach())
{
ui->label->setText("Tidak bisa melepaskan shared memory");
}
}
void SMDialog::on_loadButton_clicked()
{
if (!sharedmemory.attach())
{
ui->label->setText(tr("Tidak bisa menggandengkan ke segmen shared memory. \n" "Muat gambar terlebih dahulu"));
return;
}
QBuffer buffer;
QDataStream in(&buffer);
QImage image;
sharedmemory.lock();
buffer.setData((char*)sharedmemory.constData(),sharedmemory.size());
buffer.open(QBuffer::ReadOnly);
in >> image;
sharedmemory.unlock();
sharedmemory.detach();
ui->label->setPixmap(QPixmap::fromImage(image));
}
