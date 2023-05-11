#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <iomanip>

QList<QString> stats_list = {"Intelligence", "Dexterity", "Strength"};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    init_types_rbs();

    set_connections();
    ui->stackedWidget->setCurrentIndex(0); // main menu page as default
    print_characters();
}

MainWindow::~MainWindow()
{
    delete character;
    delete ui;
}

void MainWindow::set_connections(){
    connect(ui->pbNewChar, &QPushButton::clicked,
            this, &MainWindow::pbNewChar_clicked);

    connect(ui->pbMainMenu_2, &QPushButton::clicked,
            this, &MainWindow::showMainMenu);

    connect(ui->pbCreateChar, &QPushButton::clicked,
            this, &MainWindow::pbCreateChar_clicked);

    connect(ui->pbMainMenu, &QPushButton::clicked,
            this, &MainWindow::showMainMenu);

    connect(ui->pbSave, &QPushButton::clicked,
            this, &MainWindow::pbSave_clicked);

    connect(ui->pbItemMenu, &QPushButton::clicked,
            this, &MainWindow::pbItemMenu_clicked);

    connect(ui->pbCharMenu, &QPushButton::clicked,
            this, &MainWindow::showCharacterMenu);

    connect(ui->pbCharMenu2, &QPushButton::clicked,
            this, &MainWindow::showCharacterMenu);

    connect(ui->pbLoadChar, &QPushButton::clicked,
            this, &MainWindow::pbLoadChar_clicked);

    connect(ui->pbNextItem, &QPushButton::clicked,
            this, &MainWindow::pbNextItem_clicked);

    connect(ui->pbEquip, &QPushButton::clicked,
            this, &MainWindow::pbEquip_clicked);

    connect(ui->pbRemoveItem, &QPushButton::clicked,
            this, &MainWindow::pbRemoveItem_clicked);

    connect(ui->pbNewItem, &QPushButton::clicked,
            this, &MainWindow::pbNewItem_clicked);

    connect(ui->pbCreateItem, &QPushButton::clicked,
            this, &MainWindow::pbCreateItem_clicked);

    connect(ui->pbRemoveChar, &QPushButton::clicked,
            this, &MainWindow::pbRemoveChar_clicked);
}

void MainWindow::init_types_rbs(){
    QGroupBox *group = ui->gbItemType;
    QRadioButton *rb = nullptr;

    int y = 25, x = 0;
    for (int i = 0; i < ITEMS_TYPES_COUNT; i++){
        rb = new QRadioButton(group);
        rb->resize(140, 25);
        rb->move(x, y);
        rb->setText(QString::fromStdString(item_types[i]));
        rb->setObjectName(QString::fromStdString("rb" + item_types[i]));

        y += 25;
        if (i == ceil(ITEMS_TYPES_COUNT / 2)){
            y = 25;
            x = 140;
        }
    }
}

void MainWindow::print_characters(){
    string line;
    QString name;
    QTextBrowser *text = ui->charList;
    int name_length;
    int nr = 0;

    std::ifstream file(PATH_CHAR);

    text->clear();
    while (file.good()){
        std::getline(file, line);
        name_length = line.find(" ");

        if (line.length() > 0){
            name = line.substr(0, name_length).c_str();
            text->append(QString::number(++nr) + ". " + name);
        }
    }

    refresh_char_count(nr);

    file.close();
}

void MainWindow::refresh_char_count(int nr){
    QSpinBox *spinbox = ui->sbCharNr;

    if (nr > 0)
        spinbox->setMinimum(1);
    else
        spinbox->setMinimum(0);

    spinbox->setMaximum(nr);
}

void MainWindow::pbNewChar_clicked()
{
    ui->leName->clear();

    ui->rbMage->setChecked(true);
    ui->rbHuman->setChecked(true);

    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::pbCreateChar_clicked()
{
    if (character)
        delete character;

    QString name = ui->leName->text();

    if (name.isEmpty()){
        ui->statusbar->clearMessage();
        ui->statusbar->showMessage("Insert a name");
        return;
    }
    if (check_for_symbols(name)){
        ui->statusbar->showMessage("Non alphanumeric characters not allowed!");
        return;
    }

    character = create_character(
        name.toStdString(), get_class(), get_race()
    );

    showCharacterMenu();
}

void MainWindow::pbRemoveChar_clicked(){
    remove_from_file(character->name, PATH_CHAR);
    remove_from_file(character->name, PATH_EQ);

    character = nullptr;
    cur_item = nullptr;

    showMainMenu();
}

void MainWindow::showCharacterMenu(){
    if (character == nullptr){
        ui->statusbar->clearMessage();
        ui->statusbar->showMessage("No character to load");
        return;
    }

    ui->stackedWidget->setCurrentIndex(2);
    print_character();
}

void MainWindow::print_character(){
    ui->charStats->clear();

    int *eq_stats = stats_from_equipment(character->inventory);

    int stats_with_eq[3];
    for (int i=0; i < 3; i++)
        stats_with_eq[i] = character->stats[i] + eq_stats[i];

    QTextBrowser *text = ui->charStats;

    text->append(
        "Name: " + QString::fromStdString(character->name) + "\n" +
        "Race: " + QString::fromStdString(character->race) + "\n" +
        "Class: " + QString::fromStdString(character->class_) + "\n\n" +
        "Carry capacity: " + QString::number(weight_avaible(character->inventory)) +
            " / " + QString::number(MAX_WEIGHT) + "\n\n" +
        "  Health: " + QString::number(stats_with_eq[2] * 2) + "\n" +
        "  Mana: " + QString::number(stats_with_eq[0] * 1.5) + "\n" +
        "  Attack speed: " + QString::number(stats_with_eq[1] / 80.) + "\n" +
        "  Range: " + QString::number(character->range + eq_stats[3]) + "\n" +
        "  Damage: " + QString::number(eq_stats[4]) + " - " +QString::number(eq_stats[5]) + "\n"
        );


    text->append("Stats: ");
    for (int i = 0; i < 3; i++)
        text->append("  " + stats_list[i] + " " + QString::number(stats_with_eq[i])  +
                     " (" + QString::number(character->stats[i]) + ")"
                     );


    delete [] eq_stats;
}

int MainWindow::get_race(){
    int result;

    if (ui->rbHuman->isChecked())
        result = 0;
    else if (ui->rbElf->isChecked())
        result = 1;
    else
        result = 2;

    return result;
}

int MainWindow::get_class(){
    int result;

    if (ui->rbMage->isChecked())
        result = 0;
    else if (ui->rbArcher->isChecked())
        result = 1;
    else
        result = 2;

    return result;
}

void MainWindow::showMainMenu(){
    ui->stackedWidget->setCurrentIndex(0);
    print_characters();
}

void MainWindow::pbSave_clicked()
{
    character->save();
}

void MainWindow::pbItemMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->itemStats->clear();

    cur_item = character->inventory;

    print_item();
}


void MainWindow::print_item(){
    QTextBrowser *text = ui->itemStats;
    QString str;

    text->clear();

    if (cur_item == nullptr){
        ui->itemStats->append("No item to show. Create your first item.");
        return;
    }

    QTextStream(&str) << "Item name: " << QString::fromStdString(cur_item->name) << "\n";
    QTextStream(&str) << "Type: " << QString::fromStdString(cur_item->type) << "\n\n";
    QTextStream(&str) << "Weight: " << cur_item->weight << "\n";

    QTextStream(&str) << "Equipped: " << (cur_item->equipped ? "True": "False") << "\n\n";

    if (is_weapon(cur_item->type)){
        QTextStream(&str) << "Damage: " << cur_item->damage[0] << "-" << cur_item->damage[1] << "\n";
        QTextStream(&str) << "Range: " << cur_item->range << "\n\n";
    }

    QTextStream(&str) << "Stats: " << "\n";
    for (int i = 0; i < 3; i++)
        QTextStream(&str) << "   " << stats_list[i] << " " << cur_item->stats[i] << "\n";

    text->append(str);
}

void MainWindow::pbLoadChar_clicked()
{
    if (character)
        delete character;

    int nr = ui->sbCharNr->value();

    character = load_character(nr - 1);

    showCharacterMenu();
}

void MainWindow::pbNextItem_clicked()
{
    if (cur_item->next)
        cur_item = cur_item->next;
    else
        cur_item = character->inventory;

    print_item();
}

void MainWindow::pbEquip_clicked()
{
    if (!cur_item)
        return;

    if (cur_item->equipped)
        cur_item->equipped = false;
    else if (!type_available(character->inventory, cur_item->type)){
        ui->statusbar->showMessage("Cannot equip, slot taken!");
        return;
    }
    else
        cur_item->equipped = true;

    print_item();
}

void MainWindow::pbRemoveItem_clicked(){
    delete_item_name(character->inventory, cur_item->name);
    pbItemMenu_clicked();
}

void MainWindow::pbNewItem_clicked(){
    ui->leItemName->clear();

    QList<QRadioButton *> allButtons = ui->gbItemType->findChildren<QRadioButton *>();
    allButtons[0]->setChecked(true);

    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::pbCreateItem_clicked(){
    QString name = ui->leItemName->text();

    if (name.isEmpty()){
        ui->statusbar->clearMessage();
        ui->statusbar->showMessage("Insert a name");
        return;
    }

    if (check_for_symbols(name)){
        ui->statusbar->showMessage("Non alphanumeric characters not allowed!");
        return;
    }

    cur_item = create_item(name.toStdString(), get_type());

    if (cur_item->weight > weight_avaible(character->inventory)){
        ui->statusbar->clearMessage();
        ui->statusbar->showMessage("No enough space for the item! Clear some items first!");

        cur_item = character->inventory;
        return;
    }

    add_item(character->inventory, cur_item);

    ui->stackedWidget->setCurrentIndex(3);
    ui->itemStats->clear();

    print_item();
}

string MainWindow::get_type(){
    int checked = 0;
    QList<QRadioButton *> allButtons = ui->gbItemType->findChildren<QRadioButton *>();


    for(int i = 0; i < allButtons.size(); ++i)
        if (allButtons[i]->isChecked()){
            checked = i;
            break;
        }

    return item_types[checked];
}

bool MainWindow::check_for_symbols(QString name){
    static QRegularExpression re(R"([^a-zA-Z\d\s:])");

    return re.match(name).hasMatch();
}
