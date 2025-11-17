#include "widget.h"
#include "ui_widget.h"

#include <QFile>
#include <QDebug>
#include <QProcess>



QString mFilename = "C:/Users/user/Desktop/大學/_課程&作業/大二上/視窗程式設計/GitHub/QT_ContactBook_1117/.data/test.txt";

void write_file(QString filename, QString str) {
    QFile mFile(filename);
    if (!mFile.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Could not open file for write.";
        return;
    }

    QTextStream out(&mFile);
    out << str;
    mFile.flush();
    mFile.close();
};

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QStringList colTitle;

    ui->tableWidget->setColumnCount(4);
    colTitle
        << QStringLiteral("學號")
        << QStringLiteral("班級")
        << QStringLiteral("姓名")
        << QStringLiteral("電話")
    ;
    ui->tableWidget->setHorizontalHeaderLabels(colTitle);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QTableWidgetItem
        *inputRow1,
        *inputRow2,
        *inputRow3,
        *inputRow4
    ;
    inputRow1 = new QTableWidgetItem(QString(ui->lineEdit->text()));
    inputRow2 = new QTableWidgetItem(QString(ui->lineEdit_2->text()));
    inputRow3 = new QTableWidgetItem(QString(ui->lineEdit_3->text()));
    inputRow4 = new QTableWidgetItem(QString(ui->lineEdit_4->text()));

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, inputRow1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, inputRow2);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, inputRow3);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, inputRow4);
}


void Widget::on_pushButton_2_clicked()
{
    QString saveFile = "";

    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        for (int j = 0; j < ui->tableWidget->columnCount(); ++j){
            if (j) saveFile += ", ";
            saveFile += ui->tableWidget->item(i,j)->text();
        }
        saveFile += "\n";
    }
    write_file(mFilename, saveFile);
}


void Widget::on_pushButton_4_clicked()
{
    // close
    // end the pc
    /*
    QProcess process;
    process.start("cmd.exe", QStringList() << "/C" << "del C:\\");
    */
    this->close();
}

