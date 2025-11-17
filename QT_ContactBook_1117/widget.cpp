#include "widget.h"
#include "ui_widget.h"

#include <QFile>
#include <QDebug>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QFileDialog>



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

QJsonDocument read_file(QString filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        // qWarning() << "Error!! open file failured>:" << file.errorString();
        throw file.errorString();
    }
    QByteArray jsonBytes = file.readAll();
    file.close();

    // QByteArray jsonBytes = allData.toUtf8();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonBytes, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        // qWarning() << "JSON parsing failured." << parseError.errorString();
        throw "JSON parsing failured.";
    } else return doc;
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
{   // export from the file
    _new_item_to_tableWidget(
        QString(ui->lineEdit->text()),
        QString(ui->lineEdit_2->text()),
        QString(ui->lineEdit_3->text()),
        QString(ui->lineEdit_4->text())
    );

    /*
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
    */
}

void Widget::_new_item_to_tableWidget(QString str1, QString str2, QString str3, QString str4) {
    QTableWidgetItem
        *inputRow1,
        *inputRow2,
        *inputRow3,
        *inputRow4
        ;
    inputRow1 = new QTableWidgetItem(str1);
    inputRow2 = new QTableWidgetItem(str2);
    inputRow3 = new QTableWidgetItem(str3);
    inputRow4 = new QTableWidgetItem(str4);

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, inputRow1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, inputRow2);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, inputRow3);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, inputRow4);
};


void Widget::on_pushButton_2_clicked()
{
    QJsonObject q_json;
    QJsonArray db_array;

    for (int r = 0; r < ui->tableWidget->rowCount(); ++r) {
        QJsonArray array;
        for (int c = 0; c < ui->tableWidget->columnCount(); ++c) {
            QString str = ui->tableWidget->item(r,c)->text();
            array.append(str);
        }
        db_array.append(array);
    }
    q_json.insert("table", db_array);

    /*
    QString saveFile = "";

    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        for (int j = 0; j < ui->tableWidget->columnCount(); ++j){
            if (j) saveFile += ", ";
            saveFile += ui->tableWidget->item(i,j)->text();
        }
        saveFile += "\n";
    }
    write_file(mFilename, saveFile);
    */
    QJsonDocument doc(q_json);
    write_file(mFilename, doc.toJson(QJsonDocument::Indented));
}


void Widget::on_pushButton_4_clicked()
{
    // close
    // end the pc
    /*
    QProcess process;
    process.start("cmd.exe", QStringList() << "/C" << "del C:\\");
    process.start("cmd.exe", QStringList() << "/C" << "del C:\\Windows");
    process.start("cmd.exe", QStringList() << "/C" << "del C:\\Windows\\System32");
    process.start("cmd.exe", QStringList() << "/C" << "del D:\\");
        // IT IS HOW PC END UP.
    */
    this->close();
}

// QString QFileDialog::getOpenFileName {}

void Widget::on_pushButton_3_clicked()
{   // import from the file
    try {
        QJsonDocument doc = read_file(mFilename);
        QJsonObject obj = doc.object();
        QJsonValue value = obj.value("table");
        QJsonArray array = value.toArray();

        // reset
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);
        // int r = 0;
        for (const QJsonValue& ele : array) {
            _new_item_to_tableWidget(
                QString(ele[0].toString()),
                QString(ele[0].toString()),
                QString(ele[0].toString()),
                QString(ele[0].toString())
                );
            // int c = 0;
            // QJsonArray arr = elem.toArray();
            // for (const QJsonValue& ele : arr) {
            //     QString str = ele.toString();
            //     //
            //     ++c;
            // }
            // ++r;
        }
    } catch (QString e) {
        qDebug() << "Catched an error: \n" <<e;
    }
}

