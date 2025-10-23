#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "avltreevisualizer.h"
#include "pidrevovisualizer.h"
#include "rbtreevisualizer.h"
#include "splaytreevisualizer.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ElementDeleted(int el);
    void ElementInserted(int el);

   private slots:
    void on_AddButton_clicked();
    void on_DeleteButton_clicked();
    void on_AddManyButton_clicked();

   private:
    Ui::MainWindow *ui;
    AVLTreeVisualizer avl_tree;
    PidrevoVisualizer pidr_tree;
    RBTreeVisualizer rb_tree;
    SplayTreeVisualizer splay_tree;
};
#endif // MAINWINDOW_H
