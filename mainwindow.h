#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <characters.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

extern QList<QString> stats_list;

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void pbNewChar_clicked();

    void pbCreateChar_clicked();

    void pbSave_clicked();

    void pbItemMenu_clicked();

    void pbLoadChar_clicked();

    void pbNextItem_clicked();

    void pbEquip_clicked();

    void pbRemoveItem_clicked();

    void pbNewItem_clicked();

    void pbCreateItem_clicked();

    void pbRemoveChar_clicked();

private:
    Ui::MainWindow *ui;
    Character *character = nullptr;
    Item *cur_item = nullptr;

    // connect all buttons to functions
    void set_connections();

    // load radio buttons in Item creation menu
    void init_types_rbs();

    // print character stats in Character menu
    void print_characters();

    // set min-max values of the spinbox in Main menu
    void refresh_char_count(int);

    // change to Character menu
    void showCharacterMenu();

    // print list of characters in Main menu
    void print_character();

    // get chosen race in Create character menu
    int get_race();

    // get chosen class in Create character menu
    int get_class();

    // change to Main menu
    void showMainMenu();

    // print item stats in Item menu
    void print_item();

    // get chosen item type in Create item menu
    string get_type();
};

#endif // MAINWINDOW_H
