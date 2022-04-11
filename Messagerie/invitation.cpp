#include "invitation.h"
#include "ui_invitation.h"
#include "messagerie.h"

Invitation::Invitation(QString name,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Invitation)
{
    ui->setupUi(this);
    this->name = name;
    this->afficher_invitations();

}

Invitation::~Invitation()
{
    delete ui;
}

void Invitation::afficher_invitations()
{
    int id;
    query.prepare("SELECT id FROM Connexion WHERE username = (:username)");
    query.bindValue(":username", this->name);
    query.exec();
    while(query.next())
    {
        id = query.value(0).toInt();
    }
    query.prepare("SELECT username FROM Connexion WHERE "
                  "id =(SELECT utilisateur_ami FROM Amis WHERE utilisateur = (:id) AND status = 0)");
    query.bindValue(":id", id);
    query.exec();
    while(query.next())
    {
        QString username = query.value(0).toString();
        ui->comboBox->addItem(username);
       /* ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QTableWidgetItem cell = QTableWidgetItem(Stri(complet));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,ui->tableWidget->columnCount(),cell);*/
    }


}

void Invitation::envoyer_inviatation()
{
    int id, id1, status;
    QString ami = ui->lineEdit->text();
    query.prepare("SELECT id FROM Connexion WHERE username = (:user)");
    query.bindValue(":user", ami);
    query.exec();
    if(query.next())
    {
        id = query.value(0).toInt();
        query.prepare("SELECT id FROM Connexion WHERE username = (:username)");
        query.bindValue(":username", this->name);
        query.exec();
        while(query.next())
        {
            id1 = query.value(0).toInt();
        }

        query.prepare("SELECT status FROM Amis WHERE utilisateur = (:user) AND utilisateur_ami = (:user_a)");
        query.bindValue(":user", id1);
        query.bindValue(":user_a", id);
        query.exec();
        if(query.next())
        {
            status = query.value(0).toInt();
            if(status == 0)
            {
                msg.setIcon(QMessageBox::Information);
                msg.setWindowTitle("Information");
                msg.setText("Vous avez envoyé une invitation à cette personne");
                msg.exec();
            }
            else
            {
                msg.setIcon(QMessageBox::Information);
                msg.setWindowTitle("Information");
                msg.setText("Vous êtes ami avec cette personne");
                msg.exec();
            }

        }
        else
        {
            query.prepare("INSERT INTO Amis (utilisateur, utilisateur_ami, status) VALUES ((:user), (:user_a), (:stat))");
            query.bindValue(":user", id1);
            query.bindValue(":user_a", id);
            query.bindValue(":stat", 0);
            query.exec();

            query.prepare("INSERT INTO Amis (utilisateur, utilisateur_ami, status) VALUES ((:user), (:user_a), (:stat))");
            query.bindValue(":user", id);
            query.bindValue(":user_a", id1);
            query.bindValue(":stat", 0);
            query.exec();
        }
        msg.setIcon(QMessageBox::Information);
        msg.setWindowTitle("Information");
        msg.setText("Invitation envoyé");
        msg.exec();
    }
    else
    {
        msg.setIcon(QMessageBox::Information);
        msg.setWindowTitle("Information");
        msg.setText("L'utilisateur n'existe pas. Vous êtes sûr qu'il est inscrit dans cette messagerie ??");
        msg.exec();
    }
}

void Invitation::invitation_accepter()
{
    int id, id1;
    QString ami = ui->comboBox->currentText();
    query.prepare("SELECT id FROM Connexion WHERE username = (:username)");
    query.bindValue(":username", this->name);
    query.exec();
    while(query.next())
    {
        id = query.value(0).toInt();
    }
    query.prepare("SELECT id FROM Connexion WHERE username = (:username)");
    query.bindValue(":username", ami);
    query.exec();
    while(query.next())
    {
        id1 = query.value(0).toInt();
    }
    query.prepare("UPDATE Amis SET status = 1 WHERE utilisateur = (:user) AND utilisateur_ami = (:user_ami)");
    query.bindValue(":user", id);
    query.bindValue(":user_ami", id1);
    query.exec();
    query.prepare("UPDATE Amis SET status = 1 WHERE utilisateur = (:user) AND utilisateur_ami = (:user_ami)");
    query.bindValue(":user", id1);
    query.bindValue(":user_ami", id);
    query.exec();

}

void Invitation::invitation_refuser()
{
    int id, id1;
    QString ami = ui->comboBox->currentText();
    query.prepare("SELECT id FROM Connexion WHERE username = (:username)");
    query.bindValue(":username", this->name);
    query.exec();
    while(query.next())
    {
        id = query.value(0).toInt();
    }
    query.prepare("SELECT id FROM Connexion WHERE username = (:username)");
    query.bindValue(":username", ami);
    query.exec();
    while(query.next())
    {
        id1 = query.value(0).toInt();
    }
    query.prepare("DELETE FROM Amis WHERE utilisateur = (:user) AND utilisateur_ami = (:user_ami)");
    query.bindValue(":user", id);
    query.bindValue(":user_ami", id1);
    query.exec();
    query.prepare("DELETE FROM Amis WHERE utilisateur = (:user) AND utilisateur_ami = (:user_ami)");
    query.bindValue(":user", id1);
    query.bindValue(":user_ami", id);
    query.exec();
}

void Invitation::on_pushButton_clicked()
{
    this->envoyer_inviatation();
}



void Invitation::on_pushButton_2_clicked()
{
    if(ui->comboBox->currentText() != "")
    {
        this->invitation_accepter();
        msg.setIcon(QMessageBox::Information);
        msg.setWindowTitle("Information");
        msg.setText("Invitation acceptée. Vous êtes amis avec cette personne");
        msg.exec();
        this->afficher_invitations();
    }
    this->afficher_invitations();


}

void Invitation::on_pushButton_3_clicked()
{
    if(ui->comboBox->currentText() != "")
    {
        this->invitation_refuser();
        msg.setIcon(QMessageBox::Information);
        msg.setWindowTitle("Information");
        msg.setText("Invitation refusée");
        msg.exec();
        this->afficher_invitations();
    }
    this->afficher_invitations();

}

void Invitation::on_pushButton_4_clicked()
{
    this->hide();
    Messagerie m(this->name);
    m.exec();
}
