#pragma once
#include <cmath>
#include <QPoint>

namespace RB {
struct Node {
  int data;
  bool red;
  Node *left, *right, *parent;
  QPoint pos;
};

class RBTree {
 public:
  void Insert(int el);
  Node* root = nullptr;
  Node* TNULL;
  void Recalc();
  void Erase(int el);

  RBTree() {
    TNULL = new Node;
    TNULL->red = 0;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
  }

 private:
  void InsertRecolor(Node* node);
  void DeleteRecolor(Node* node);
  void RightRotate(Node* node);
  void LeftRotate(Node* node);
  void Transplant(Node* u, Node* v);
  Node* Maximum(Node* node);
  Node* Minimum(Node* node);
  int SafeHeight(Node* node);
  int _Recalc(Node* node, int depth = 0, int indent = 0);
  void _Erase(Node* node, int el);
};
}

