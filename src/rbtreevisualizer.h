#ifndef RBTREEVISUALIZER_H
#define RBTREEVISUALIZER_H

#include <QWidget>
#include <RBTree.h>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>

namespace Ui {
class RBTreeVisualizer;
}

class RBTreeVisualizer : public QWidget
{
  Q_OBJECT

 public:
  explicit RBTreeVisualizer(QWidget *parent = nullptr);
  ~RBTreeVisualizer();
  void paintEvent(QPaintEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);

  RB::RBTree tree;

 private:
  void VisualizeTree(QPainter *painter, RB::Node *node);
  QRect BoxForNode(RB::Node *node);
  float zoom = 1;
  QPoint offset, prev_drag, pressed_pos;
  QPen pen;
  float base_indent = 170;
  float ver_indent = 100;
  bool CheckDeletion(QPoint pos, RB::Node *node);

  Ui::RBTreeVisualizer *ui;
};

#endif // RBTREEVISUALIZER_H
