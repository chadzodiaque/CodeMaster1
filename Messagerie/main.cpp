#include "page_accueil.h"
#include "basedonne.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap image(":/Images/splashscreen.png");
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(image.scaled(862,500, Qt::KeepAspectRatio));
    splash->show();
    if (connexion())
    {
        Page_accueil w;
        QTimer::singleShot(2500, splash,SLOT(close()));
        QTimer::singleShot(2500, &w, SLOT(show()));
        return a.exec();
    }

}
