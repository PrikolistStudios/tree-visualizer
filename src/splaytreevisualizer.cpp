#include "splaytreevisualizer.h"
#include "ui_splaytreevisualizer.h"
#include "mainwindow.h"

SplayTreeVisualizer::SplayTreeVisualizer(QWidget *parent) :
                                                            QWidget(parent),
                                                            ui(new Ui::SplayTreeVisualizer)
{
  ui->setupUi(this);
  pen.setWidth(2);
}

SplayTreeVisualizer::~SplayTreeVisualizer()
{
  delete ui;
}

void SplayTreeVisualizer::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setPen(pen);
  QFont font;
  font = painter.font();
  font.setPointSize(15 * zoom);
  painter.setFont(font);
  VisualizeTree(&painter, tree.root);
}

void SplayTreeVisualizer::mouseMoveEvent(QMouseEvent *event) {
  QPoint drag = event->pos() - pressed_pos;
  offset += drag - prev_drag;
  prev_drag = drag;
  update();
}

void SplayTreeVisualizer::mousePressEvent(QMouseEvent *event) {
  prev_drag.setX(0);
  prev_drag.setY(0);
  pressed_pos = event->pos();

  CheckDeletion(event->pos(), tree.root);
}

void SplayTreeVisualizer::wheelEvent(QWheelEvent *event) {
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

void SplayTreeVisualizer::VisualizeTree(QPainter *painter, Splay::Node *node) {
  if (node == nullptr) return;
  QRect frame = BoxForNode(node);
  painter->drawRect(frame);
  painter->drawText(frame, Qt::AlignCenter, QString::number(node->data));
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

QRect SplayTreeVisualizer::BoxForNode(Splay::Node* node) {
  QSize rect_size(130 * zoom, 30 * zoom);
  QPoint rect_point(
      (node->pos.x() - rect_size.width() / 2 - tree.root->pos.x() + this->size().width()/2) * zoom +
          offset.x(),
      node->pos.y() * zoom + offset.y());
  QRect frame(rect_point, rect_size);
  return frame;
}

bool SplayTreeVisualizer::CheckDeletion(QPoint pos, Splay::Node *node) {
  if (node == nullptr) return false;
  QRect collider = BoxForNode(node);
  if (collider.contains(pos)) {
    dynamic_cast<MainWindow *>(
        parentWidget()->parentWidget()->parentWidget()->parentWidget())
        ->ElementDeleted(node->data);
    return true;
  } else {
    if (node->left &&
        CheckDeletion(pos, node->left)) {
      return true;
    }
    if (node->right &&
        CheckDeletion(pos, node->right)) {
      return true;
    }
    return false;
  }
}
