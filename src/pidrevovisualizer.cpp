#include "pidrevovisualizer.h"
#include "ui_pidrevovisualizer.h"
#include <QtMath>
#include "mainwindow.h"


PidrevoVisualizer::PidrevoVisualizer(QWidget *parent) :
                                                        QWidget(parent),
                                                        ui(new Ui::PidrevoVisualizer)
{
  ui->setupUi(this);
  pen.setWidth(2);
}

PidrevoVisualizer::~PidrevoVisualizer()
{
  delete ui;
}

void PidrevoVisualizer::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setPen(pen);
  QFont font;
  font = painter.font();
  font.setPointSize(15 * zoom);
  painter.setFont(font);

  VisualizeTree(&painter, tree.root);
}

void PidrevoVisualizer::mouseMoveEvent(QMouseEvent *event) {
  QPoint drag = event->pos() - pressed_pos;
  offset += drag - prev_drag;
  prev_drag = drag;
  update();
}

void PidrevoVisualizer::mousePressEvent(QMouseEvent *event) {
  prev_drag.setX(0);
  prev_drag.setY(0);
  pressed_pos = event->pos();
}

void PidrevoVisualizer::wheelEvent(QWheelEvent *event) {
  float new_zoom = zoom;
  if (event->angleDelta().y() > 0) {
    new_zoom *= 1.05;
  } else {
    new_zoom *= 0.95;
  }
  QPoint mouse_pos = this->mapFromGlobal(QCursor::pos());
  offset += (-offset + mouse_pos) * (1 - new_zoom / zoom);
  zoom = new_zoom;
  update();
}

void PidrevoVisualizer::mouseReleaseEvent(QMouseEvent *event) {
  CheckDeletion(event->pos(), tree.root);
}

void PidrevoVisualizer::VisualizeTree(QPainter *painter, Pidrevo::Node *node) {
  if (node == nullptr) return;
  QRect frame = BoxForNode(node);
  painter->drawRect(frame);
  painter->drawText(frame, Qt::AlignTop | Qt::AlignHCenter, QString::number(node->key));
  painter->drawText(frame, Qt::AlignBottom | Qt::AlignHCenter,
                    QString::number(node->priority));

  if (node->left != nullptr) {
    QPoint first(frame.center().x(), frame.bottom());
    QPoint second(BoxForNode(node->left).center().x(),
                  BoxForNode(node->left).top());
    painter->drawLine(first, second);
    VisualizeTree(painter, node->left);
  }
  if (node->right != nullptr) {
    QPoint first(frame.center().x(), frame.bottom());
    QPoint second(BoxForNode(node->right).center().x(),
                  BoxForNode(node->right).top());
    painter->drawLine(first, second);
    VisualizeTree(painter, node->right);
  }
}

QRect PidrevoVisualizer::BoxForNode(Pidrevo::Node *node) {
  QSize rect_size(130 * zoom, 50 * zoom);
  QPoint rect_point((node->pos.x() - rect_size.width() / 2 -
                     tree.root->pos.x() + this->size().width() / 2) *
                            zoom +
                        offset.x(),
                    node->pos.y() * zoom + offset.y());
  QRect frame(rect_point, rect_size);
  return frame;
}

bool PidrevoVisualizer::CheckDeletion(QPoint pos, Pidrevo::Node *node) {
  if (node == nullptr) return false;
  QRect collider = BoxForNode(node);
  if (collider.contains(pos)) {
    dynamic_cast<MainWindow *>(
        parentWidget()->parentWidget()->parentWidget()->parentWidget())
        ->ElementDeleted(node->key);
    return true;
  } else {
    if (node->left && CheckDeletion(pos, node->left)) {
      return true;
    }
    if (node->right && CheckDeletion(pos, node->right)) {
      return true;
    }
    return false;
  }
}

