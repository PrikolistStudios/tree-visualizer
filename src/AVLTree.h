#pragma once
#include <cmath>
#include <QPoint>

namespace AVL {
struct Node {
  int data = 0, h = 1;
  Node *left = nullptr, *right = nullptr;
  QPoint pos;
};

class AVLTree {
 public:
  void InOrder();
  void Insert(int el);
  void Erase(int el);
  int SafeHeight();
  void Recalc();
  Node *root = nullptr;
 private:
  void DelElem(Node*& node);
  int DelMax(Node*& node);
  void Balance(Node*& node);
  void SmallRot(Node*& node);
  void BigRot(Node*& node);
  void _InOrder(Node* node);
  void _Insert(Node*& node, int el);
  void _Erase(Node*& node, int el);
  int _SafeHeight(Node* node);
  int _Recalc(Node* node, int depth = 0, int indent = 0);
};
}
