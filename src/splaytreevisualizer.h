#ifndef SPLAYTREEVISUALIZER_H
#define SPLAYTREEVISUALIZER_H

#include <QWidget>
#include "SplayTree.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>


namespace Ui {
class SplayTreeVisualizer;
}

class SplayTreeVisualizer : public QWidget
{
  Q_OBJECT

 public:
  explicit SplayTreeVisualizer(QWidget *parent = nullptr);
  ~SplayTreeVisualizer();
  void paintEvent(QPaintEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);

  Splay::SplayTree tree;

 private:
  void VisualizeTree(QPainter *painter, Splay::Node *node);
  QRect BoxForNode(Splay::Node *node);
  Ui::SplayTreeVisualizer *ui;
  float zoom = 1;
  QPoint offset, prev_drag, pressed_pos;
  QPen pen;
  float base_indent = 170;
  float ver_indent = 100;
  bool CheckDeletion(QPoint pos, Splay::Node *node);
};

#endif // SPLAYTREEVISUALIZER_H
