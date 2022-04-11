#ifndef INVITATION_H
#define INVITATION_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QMessageBox>

namespace Ui {
class Invitation;
}

class Invitation : public QDialog
{
    Q_OBJECT

public:
    explicit Invitation(QString ,QWidget *parent = 0);
    ~Invitation();
    void afficher_invitations();
    void envoyer_inviatation();
    void invitation_accepter();
    void invitation_refuser();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Invitation *ui;
    QString name;
    QSqlQuery query;
    QMessageBox msg;
};

#endif // INVITATION_H
