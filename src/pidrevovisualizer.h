#ifndef PIDREVOVISUALIZER_H
#define PIDREVOVISUALIZER_H

#include <QWidget>
#include <Pidrevo.h>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>

namespace Ui {
class PidrevoVisualizer;
}

class PidrevoVisualizer : public QWidget
{
  Q_OBJECT

 public:
  explicit PidrevoVisualizer(QWidget *parent = nullptr);
  ~PidrevoVisualizer();

  void paintEvent(QPaintEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

  Pidrevo::PidrevoTree tree;

 private:
  void VisualizeTree(QPainter *painter, Pidrevo::Node *node);
  QRect BoxForNode(Pidrevo::Node *node);
  Ui::PidrevoVisualizer *ui;
  float zoom = 1;
  QPoint offset, prev_drag, pressed_pos;
  QPen pen;
  float base_indent = 170;
  float ver_indent = 100;

 private:
  bool CheckDeletion(QPoint pos, Pidrevo::Node *node);
};

#endif // PIDREVOVISUALIZER_H
