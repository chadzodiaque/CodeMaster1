#include "page_accueil.h"
#include "ui_page_accueil.h"
#include "inscription.h"
#include "messagerie.h"
#include <QMessageBox>
#include <QtSql>
#include <QSqlDatabase>


Page_accueil::Page_accueil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Page_accueil)
{
    ui->setupUi(this);
    msgbox.setStyleSheet("font-family : century-gothic;font-size : 24px;color : balck;");
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS Utilisateur (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, nom VARCHAR (50, 150) NOT NULL, prenom VARCHAR (50, 150) NOT NULL, age INTEGER (2, 3) NOT NULL, sexe CHAR (1) NOT NULL, mail VARCHAR (255) NOT NULL)");
    query.exec("CREATE TABLE IF NOT EXISTS Connexion (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username VARCHAR (255) NOT NULL UNIQUE, password VARCHAR (50) NOT NULL, id_utilisateur INTEGER REFERENCES Utilisateur(id) NOT NULL)");
    query.exec("CREATE TABLE IF NOT EXISTS Discussion (id_discussion INTEGER PRIMARY KEY AUTOINCREMENT, utilisateur1 INTEGER REFERENCES Connexion(id), utilisateur2 INTEGER REFERENCES Connexion(id) )");
    query.exec("CREATE TABLE IF NOT EXISTS Messages (id INTEGER PRIMARY KEY AUTOINCREMENT, message VARCHAR, date VARCHAR, discussion INTEGER REFERENCES Discussion (id) )");
    query.exec("CREATE TABLE IF NOT EXISTS Amis (id_amis INTEGER PRIMARY KEY AUTOINCREMENT,utilisateur INTEGER REFERENCES Connexion (id), utilisateur_ami INTEGER REFERENCES Connexion (id), status INTEGER)");

}

Page_accueil::~Page_accueil()
{
    delete ui;
}


void Page_accueil::on_Sinscrire_clicked()
{
    this->hide();
    Inscription i;
    i.exec();
}

void Page_accueil::on_connexion_clicked()
{
    if(this->verif())
    {
        msgbox.setIcon(QMessageBox::Information);
        msgbox.setWindowTitle("Information");
        msgbox.setText("Connexion acceptée");
        msgbox.exec();
        this->hide();
        Messagerie m(ui->lineEdit_user->text());
        m.exec();


    }
    else
    {
        msgbox.setIcon(QMessageBox::Information);
        msgbox.setWindowTitle("Erreur");
        msgbox.setText("Veuillez rentrer vos informations de connexion valide");
        msgbox.exec();
    }

}

bool Page_accueil::verif()
{
    bool verif = true;
    if(ui->lineEdit_user->text() != "" || ui->lineEdit_pass->text() != "")
    {
        this->username = ui->lineEdit_user->text();
        this->password = ui->lineEdit_pass->text();
        QSqlQuery query;
        query.prepare("SELECT * FROM Connexion WHERE username = (:name) and password = (:pass)");
        query.bindValue(":name", this->username);
        query.bindValue(":pass", this->password);
        query.exec();
        if(!(query.next()))
        {
            verif = false;
        }

    }
    else
    {
        msgbox.setIcon(QMessageBox::Warning);
        msgbox.setWindowTitle("Erreur");
        msgbox.setText("Veuillez rentrer vos informations de connexion valide");
        msgbox.exec();
        verif = false;
    }
    return verif;
}

