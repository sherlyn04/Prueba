#include "Principal.h"
#include <QTranslator>
#include <QInputDialog>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator T;
    QStringList langs;
    langs << "Español" <<"Italiano";
    const QString lang = QInputDialog::getItem(NULL,"Languaje", "Select a languaje", langs);
    if (lang == "Italiano"){
        T.load(":/italiano.qm");
    }
    if(lang != "Español"){
        a.installTranslator(&T);
    }
    a.setStyle("fusion");
    Principal w;
    w.show();
    return a.exec();
}
