#ifndef MESSAGERIE_H
#define MESSAGERIE_H
#include "page_accueil.h"
#include <QDateTime>

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>

namespace Ui {
class Messagerie;
}

class Messagerie : public QDialog
{
    Q_OBJECT

public:
    explicit Messagerie(QString, QWidget *parent = 0);
    ~Messagerie();
    void insertion_message();
    void afficher_message();
    void list_amis();

private slots:
    void on_envoyer_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::Messagerie *ui;
    QString message;
    QSqlQuery query;
    QString name;
    QString date;
    QString name_ami;
    QMessageBox msg;

};

#endif // MESSAGERIE_H
