#pragma once

#include <QPoint>

namespace Splay {
struct Node {
  int data;
  Node *right = nullptr, *left = nullptr;
  QPoint pos;
};

class SplayTree {
 public:
  void Insert(int el);
  void Erase(int el);
  void Recalc();
  Node* root = nullptr;

 private:
  int _Recalc(Node* node, int depth = 0, int indent = 0);
  Node* Zig(Node* node);
  Node* Zag(Node* node);
  Node* Splay(Node* root, int el);
};
}


