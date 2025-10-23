#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->TreesTW->clear();
  avl_tree.setParent(this);
  pidr_tree.setParent(this);
  rb_tree.setParent(this);
  splay_tree.setParent(this);
  ui->TreesTW->addTab(&avl_tree, "AVL Tree");
  ui->TreesTW->addTab(&pidr_tree, "Cartesian Tree");
  ui->TreesTW->addTab(&rb_tree, "Red-Black Tree");
  ui->TreesTW->addTab(&splay_tree, "Splay Tree");


  connect(ui->AddButton, &QPushButton::clicked, this,
          &MainWindow::on_AddButton_clicked);
  connect(ui->DeleteButton, &QPushButton::clicked, this,
          &MainWindow::on_DeleteButton_clicked);
  connect(ui->AddManyButton, &QPushButton::clicked, this,
          &MainWindow::on_AddManyButton_clicked);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::ElementDeleted(int el) {
  avl_tree.tree.Erase(el);
  avl_tree.tree.Recalc();
  avl_tree.update();

  pidr_tree.tree.Delete(el);
  pidr_tree.tree.RecalcPos();
  pidr_tree.update();

  rb_tree.tree.Erase(el);
  rb_tree.tree.Recalc();
  rb_tree.update();

  splay_tree.tree.Erase(el);
  splay_tree.tree.Recalc();
  splay_tree.update();
}

void MainWindow::ElementInserted(int el) {
  avl_tree.tree.Insert(el);
  avl_tree.tree.Recalc();
  avl_tree.update();

  pidr_tree.tree.Insert(el);
  pidr_tree.tree.RecalcPos();
  pidr_tree.update();

  rb_tree.tree.Insert(el);
  rb_tree.tree.Recalc();
  rb_tree.update();

  splay_tree.tree.Insert(el);
  splay_tree.tree.Recalc();
  splay_tree.update();
}

void MainWindow::on_AddButton_clicked() {
  bool ok;
  int value = ui->AddValue->toPlainText().toInt(&ok);
  if (ok) {
    ElementInserted(value);
  }
}

void MainWindow::on_DeleteButton_clicked() {
  bool ok;
  int value = ui->DeleteValue->toPlainText().toInt(&ok);
  if (ok) {
    ElementDeleted(value);
  }
}

void MainWindow::on_AddManyButton_clicked() {
  bool ok;
  int value = ui->AddManyValue->toPlainText().toInt(&ok);
  if (ok) {
    std::mt19937 mersenne(static_cast<unsigned int>(std::time(0)));
    for (int i = 0; i < value; ++i) {
      ElementInserted(mersenne());
    }
  }
}

