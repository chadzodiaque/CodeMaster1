#ifndef PAGE_ACCUEIL_H
#define PAGE_ACCUEIL_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Page_accueil;
}

class Page_accueil : public QDialog
{
    Q_OBJECT

public:
    explicit Page_accueil(QWidget *parent = 0);
    ~Page_accueil();
    bool verif();



private slots:

    void on_Sinscrire_clicked();


    void on_connexion_clicked();

private:
    Ui::Page_accueil *ui;
    QString username;
    QString password;
    QMessageBox msgbox;
};

#endif // PAGE_ACCUEIL_H
