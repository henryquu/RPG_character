/**
  * \mainpage
  * \par RPG Character creator
  * App for creating a rpg character and it's items
  * \note Wording used:
  * \b base stats: intelligence, dexterity and strength
  * \b inventory - all items belonging to a character
  * \b equipment - items with equipped status
  * \author Sebastian Płaczek
  * \date 13.05.2023
  */

#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
