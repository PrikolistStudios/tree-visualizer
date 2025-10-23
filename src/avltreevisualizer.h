#ifndef AVLTREEVISUALIZER_H
#define AVLTREEVISUALIZER_H

#include <QWidget>
#include <QPainter>
#include "AVLTree.h"
#include <QMouseEvent>
#include <QWheelEvent>

namespace Ui {
class AVLTreeVisualizer;
}

class AVLTreeVisualizer : public QWidget {
  Q_OBJECT

      public:
       explicit AVLTreeVisualizer(QWidget *parent = nullptr);
       ~AVLTreeVisualizer();

       void paintEvent(QPaintEvent *event);
       void mouseMoveEvent(QMouseEvent *event);
       void mousePressEvent(QMouseEvent *event);
       void wheelEvent(QWheelEvent *event);

       AVL::AVLTree tree;
      private:
       void VisualizeTree(QPainter *painter, AVL::Node *node);
       QRect BoxForNode(AVL::Node *node);
       Ui::AVLTreeVisualizer *ui;
       float zoom = 1;
       QPoint offset, prev_drag, pressed_pos;
       QPen pen;
       float base_indent = 170;
       float ver_indent = 100;
       bool CheckDeletion(QPoint pos, AVL::Node *node);
};

#endif // AVLTREEVISUALIZER_H
