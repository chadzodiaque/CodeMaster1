#include "messagerie.h"
#include "ui_messagerie.h"
#include "invitation.h"
#include "page_accueil.h"
#include <QSqlQueryModel>
#include <QModelIndex>
#include <QVector>
Messagerie::Messagerie(QString username, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Messagerie)
{

    ui->setupUi(this);
    this->name = username;
    ui->label_2->setText(this->name);
    this->list_amis();
    this->name_ami = ui->comboBox->currentText();



    ui->label_3->setText(this->name_ami);
    this->afficher_message();
}

Messagerie::~Messagerie()
{
    delete ui;
}

void Messagerie::on_envoyer_clicked()
{
    ui->contenu_messages->clear();
    this->message = ui->message->toPlainText();
    QDateTime a = QDateTime::currentDateTime();
    QString time_format = "yyyy-MM-dd  HH:mm:ss";
    this->date = a.toString(time_format);
    this->name_ami = ui->comboBox->currentText();
    this->insertion_message();
    this->afficher_message();
    ui->message->clear();
    //QDateTime a = QDateTime::currentDateTime();
    //QString time_format = "yyyy-MM-dd  HH:mm:ss";
    //this->date = a.toString(time_format);
    /*this->name_ami = ui->comboBox->currentText();
    ui->contenu_messages->append(message);
    ui->message->clear();
    QPushButton affiche_message;
    affiche_message.setText(message);
    QHBoxLayout hlayout(ui->scrollArea);
    hlayout.addLayout(affiche_message);*/
}

void Messagerie::insertion_message()
{
    int id1, id2, idd, idd_d;
    query.prepare("SELECT id FROM Connexion WHERE username = (:username)");
    query.bindValue(":username", this->name_ami);
    query.exec();
    while(query.next())
    {
        id1 = query.value(0).toInt();
    }
    query.prepare("SELECT id FROM Connexion WHERE username = (:username)");
    query.bindValue(":username", this->name);
    query.exec();
    while(query.next())
    {
        id2 = query.value(0).toInt();
    }
    query.prepare("SELECT id_discussion FROM Discussion WHERE utilisateur1 = (:id1) AND utilisateur2 = (:id2)");
    query.bindValue(":id1", id2);
    query.bindValue(":id2", id1);
    query.exec();
    if(query.next() == false)
    {
        query.prepare("INSERT INTO Discussion (utilisateur1, utilisateur2) VALUES ((:user1), (:user2))");
        query.bindValue(":user1", id2);
        query.bindValue(":user2", id1);
        query.exec();
    }
    query.prepare("SELECT id_discussion FROM Discussion WHERE utilisateur1 = (:id1) AND utilisateur2 = (:id2)");
    query.bindValue(":id1", id1);
    query.bindValue(":id2", id2);
    query.exec();
    if(query.next() == false)
    {
        query.prepare("INSERT INTO Discussion (utilisateur1, utilisateur2) VALUES ((:user1), (:user2))");
        query.bindValue(":user1", id1);
        query.bindValue(":user2", id2);
        query.exec();
    }
    query.prepare("SELECT id_discussion FROM Discussion WHERE utilisateur1 = (:id1) AND utilisateur2 = (:id2)");
    query.bindValue(":id1", id2);
    query.bindValue(":id2", id1);
    query.exec();
    while(query.next())
    {
        idd = query.value(0).toInt();
    }
    query.prepare("SELECT id_discussion FROM Discussion WHERE utilisateur1 = (:id1) AND utilisateur2 = (:id2)");
    query.bindValue(":id1", id1);
    query.bindValue(":id2", id2);
    query.exec();
    while(query.next())
    {
        idd_d = query.value(0).toInt();
    }
    query.prepare("INSERT INTO Messages (message, date, discussion) VALUES ((:message), (:date), (:discussion))");
    query.bindValue(":message", this->message);
    query.bindValue(":date", this->date);
    query.bindValue(":discussion", idd);
    query.exec();
    query.prepare("INSERT INTO Messages (message, date, discussion) VALUES ((:message), (:date), (:discussion))");
    query.bindValue(":message", this->message);
    query.bindValue(":date", this->date);
    query.bindValue(":discussion", idd_d);
    query.exec();
}

void Messagerie::afficher_message()
{
    int id1, id2, idd;
    query.prepare("SELECT id FROM Connexion WHERE username = (:username)");
    query.bindValue(":username", this->name_ami);
    query.exec();
    while(query.next())
    {
        id1 = query.value(0).toInt();
    }
    query.prepare("SELECT id FROM Connexion WHERE username = (:username)");
    query.bindValue(":username", this->name);
    query.exec();
    while(query.next())
    {
        id2 = query.value(0).toInt();
    }
    query.prepare("SELECT id_discussion FROM Discussion WHERE utilisateur1 = (:id1) AND utilisateur2 = (:id2)");
    query.bindValue(":id1", id2);
    query.bindValue(":id2", id1);
    query.exec();
    while(query.next())
    {
        idd = query.value(0).toInt();
    }
    query.prepare("SELECT id_discussion FROM Discussion WHERE utilisateur1 = (:id1) AND utilisateur2 = (:id2)");
    query.bindValue(":id1", id2);
    query.bindValue(":id2", id1);
    query.exec();
    while(query.next())
    {
        idd = query.value(0).toInt();
    }
    query.prepare("SELECT message, date FROM Messages WHERE discussion = (:idd) ORDER BY date");
    query.bindValue(":idd", idd);
    query.exec();
    while(query.next())
    {
        QString mess = query.value(0).toString();
        QString date = query.value(1).toString();
        ui->contenu_messages->append(mess +" "+date);
    }
}

void Messagerie::list_amis()
{
    QVector <int> tableau_id;
    int id1;
    query.prepare("SELECT id FROM Connexion WHERE username = (:username)");
    query.bindValue(":username", this->name);
    query.exec();
    while(query.next())
    {
        id1 = query.value(0).toInt();
    }
    query.prepare("SELECT utilisateur_ami FROM Amis WHERE utilisateur = (:id) AND status = 1");
    query.bindValue(":id", id1);
    query.exec();
    while (query.next())
    {
        tableau_id.append(query.value(0).toInt());
    }
    for(int i = 0 ; i<tableau_id.size(); i++)
    {
        query.prepare("SELECT username FROM Connexion WHERE id = (:id)");
        query.bindValue(":id", tableau_id[i]);
        query.exec();
        while (query.next())
        {
            ui->comboBox->addItem(query.value(0).toString());
        }
    }

    /*query.prepare("SELECT username FROM Connexion WHERE "
                  "id =(SELECT utilisateur_ami FROM Amis WHERE utilisateur = (:id) AND status = (:status))");
    query.bindValue(":id", id1);
    query.bindValue(":status", 1);
    query.exec();
    QStringList list;
    while(query.next())
    {
        QString username = query.value(0).toString();
        list.append(username);
        ui->comboBox->addItem(query.value(0).toString());
       ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QTableWidgetItem cell = QTableWidgetItem(Stri(complet));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,ui->tableWidget->columnCount(),cell);
        qDebug() << "9:"<< username;
    }*/

    //qDebug() << "9:"<< list;
}

void Messagerie::on_pushButton_3_clicked()
{
    this->name_ami = ui->comboBox->currentText();
    ui->label_3->setText(name_ami);
    ui->contenu_messages->clear();
    this->name_ami = ui->comboBox->currentText();
    this->afficher_message();
}

void Messagerie::on_pushButton_2_clicked()
{
    ui->contenu_messages->clear();
    this->name = ui->label_2->text();
    this->name_ami = ui->comboBox->currentText();
    this->afficher_message();
}

void Messagerie::on_pushButton_4_clicked()
{
    this->hide();
    Invitation i(this->name);
    i.exec();

}

void Messagerie::on_pushButton_clicked()
{
    int response = msg.question(this, "Information", "Voulez-vous déconnecter ??", QMessageBox::Yes, QMessageBox::No);
    if (response == QMessageBox::Yes)
    {
        this->hide();
        Page_accueil p;
        p.exec();
    }
    else if (response == QMessageBox::No)
    {
        msg.close();
    }


}
