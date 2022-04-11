#include "inscription.h"
#include "ui_inscription.h"
#include "page_accueil.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>

Inscription::Inscription(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Inscription)
{
    ui->setupUi(this);
    msgbox.setStyleSheet("font-family : century-gothic;font-size : 15px;color : balck;");
}

Inscription::~Inscription()
{
    delete ui;
}

void Inscription::on_inscrire_clicked()
{
    /*this->name = ui->lineedit_nom->text();
    this->surname = ui->lineedit_prenom->text();
    this->mail = ui->lineedit_mail->text();
    this->age = ui->spinbox_age->value();
    this->sexe = ui->combobox_sexe->currentText();*/
    if(this->verification() && this->verify())
    {
        this->name = ui->lineedit_nom->text();
        this->surname = ui->lineedit_prenom->text();
        this->mail = ui->lineedit_mail->text();
        this->age = ui->spinbox_age->value();
        this->sexe = ui->combobox_sexe->currentText();
        this->username = ui->lineEdit_utilisateur->text();
        this->password = ui->lineEdit_password->text();
        if(this->inscrit() && this->insertion())
        {
            /*QSqlQuery query;
            query.prepare("SELECT id FROM Utilisateur WHERE mail = (:mail)");
            query.bindValue(":mail", this->mail);
            while(query.next())
            {
                this->set_id(query.value(0).toInt());
            }
            Inscription_user i;
            i.exec();*/
            msgbox.setIcon(QMessageBox::Information);
            msgbox.setWindowTitle("Félicitations");
            msgbox.setText("Vous êtes inscrit");
            msgbox.exec();
            this->hide();
            Page_accueil p;
            p.exec();

        }
    }

}

bool Inscription::verification()
{
    bool verif = true;
    if ((ui->lineedit_nom->text() == "") || (ui->lineedit_prenom->text() == "") || (ui->lineedit_mail->text() == "") || (ui->spinbox_age->value() == 0))
    {
        msgbox.setIcon(QMessageBox::Warning);
        msgbox.setWindowTitle("Erreur");
        msgbox.setText("Veuillez rentrer vos informations");
        msgbox.exec();
        verif = false;
    }
    else
    {
        QRegExp rx("\\b^[a-z0-9._-]+@[a-z0-9._-]{2,}\\.[a-z]{2,4}\\b");
        ;
        if (rx.exactMatch(ui->lineedit_mail->text())== false)
        {
            msgbox.setIcon(QMessageBox::Warning);
            msgbox.setWindowTitle("Erreur");
            msgbox.setText("Veuillez rentrer un mail valide");
            msgbox.exec();
            verif = false;
        }
    }
    return verif;

}

bool Inscription::inscrit()
{
    bool verify = true;
    QSqlQuery requete, requete1;
    requete.exec("SELECT mail FROM Utilisateur");
    while(requete.next())
    {
        QString mai = requete.value(1).toString();
        if(mail == mai)
        {
            msgbox.setIcon(QMessageBox::Warning);
            msgbox.setWindowTitle("Attention");
            msgbox.setText("Cette adresse mail existe. Veuillez rentrez un autre mail");
            msgbox.exec();
            verify = false;
        }
    }
    if(verify)
    {
        requete1.prepare("INSERT INTO Utilisateur (nom, prenom, age, sexe, mail) VALUES ((:nom), (:prenom), (:age), (:sexe), (:mail))");
        requete1.bindValue(":nom", name);
        requete1.bindValue(":prenom", surname);
        requete1.bindValue(":age", age);
        requete1.bindValue(":sexe", sexe);
        requete1.bindValue(":mail", mail);
        requete1.exec();
    }
    return verify;
}
bool Inscription::verify()
{
    bool verif = true;
    if(ui->lineEdit_utilisateur->text() != "" || ui->lineEdit_password->text() != "" || ui->lineEdit_password2->text() != "")
    {
        if (ui->lineEdit_password->text() != ui->lineEdit_password2->text())
        {
            msgbox.setIcon(QMessageBox::Warning);
            msgbox.setWindowTitle("Attention");
            msgbox.setText("Les mots de passes doit être identiques");
            msgbox.exec();
            verif = false;
        }
    }
    else
    {
      msgbox.setIcon(QMessageBox::Warning);
      msgbox.setWindowTitle("Attention");
      msgbox.setText("Tous les champs doivent être remplie");
      msgbox.exec();
      verif = false;
    }
    return verif;
}

bool Inscription::insertion()
{
    bool verif = true;
    QSqlQuery query, query1, query2;
    query.exec("SELECT username FROM Connexion");
    while (query.next())
    {
        QString n = query.value(0).toString();
        if (n == this->username)
        {
            msgbox.setIcon(QMessageBox::Warning);
            msgbox.setWindowTitle("Attention");
            msgbox.setText("Votre nom d'utilisateur a été utilisé. Veuillez choisir un autre");
            msgbox.exec();
            verif = false;
        }
    }
    if(verif)
    {
        int id_utilisateur;
        query2.prepare("SELECT id FROM Utilisateur WHERE mail = (:mail)");
        query2.bindValue(":mail", this->mail);
        query2.exec();
        while(query2.next())
        {
            id_utilisateur = query2.value(0).toInt();
        }

        query1.prepare("INSERT INTO Connexion (username, password, id_utilisateur) VALUES ((:name), (:password), (:id))");
        query1.bindValue(":name", this->username);
        query1.bindValue(":password", this->password);
        query1.bindValue(":id", id_utilisateur);
        query1.exec();
    }
    return verif;
}


void Inscription::on_retour_clicked()
{
    this->hide();
    Page_accueil p;
    p.exec();
}
