#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Inscription;
}

class Inscription : public QDialog
{
    Q_OBJECT

public:
    explicit Inscription(QWidget *parent = 0);
    ~Inscription();
    bool verification();
    bool inscrit();
    bool verify();
    bool insertion();

private slots:

    void on_inscrire_clicked();

    void on_retour_clicked();

private:
    Ui::Inscription *ui;
    QString name;
    QString surname;
    QString sexe;
    int age;
    QString mail;
    QString username;
    QString password;
    QMessageBox msgbox;

};

#endif // INSCRIPTION_H
