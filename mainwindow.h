#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QPainter>
#include <QMouseEvent>
#include <queue>
#include <utility>
#include <QMap>
#include <QIntValidator>
#include "binarytree.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_File_triggered();

    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

    void on_actionSave_File_triggered();



private:
    void initialization_item();
    void hideAllObject();
    void updateWindow();
    void paintEvent(QPaintEvent *event);

    Node * root = nullptr; // Корень дерева
    std::map<std::string, QLine> lines_to_ellipse; // Контейнер с названием круга и самим лейблом круга
    QVector< std::pair<QLabel*,QLabel*> >arrayNumberLabels; // Хранит в себе пару круг и значение
    std::queue<int> queue_numbers_to_tree; // вставка элементов с файла в очередь
    BinaryTree bn; // Объект дерева
    Ui::MainWindow *ui;
    QString strNumbers; // строка в которую считываются цифры с файла
    std::string ID_LABELS[15]; // идентификатор названия элементов


};

#endif // MAINWINDOW_H
