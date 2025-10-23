#pragma once

#include <random>
#include <utility>
#include <time.h>
#include <QPoint>

namespace Pidrevo {
struct Node {
  int priority, key, size = 1;
  Node *right = nullptr, *left = nullptr;
  QPoint pos;
};

struct SplitRes {
  Node *less = nullptr, *greater = nullptr, *equal = nullptr;
};

class PidrevoTree {
 public:
  PidrevoTree();
  Node* root = nullptr;
  void Insert(int el);
  void Delete(int el);
  void Merge(Node* right);
  std::pair<Node*,Node*> Split(int key);
  bool Find(int el);
  void RecalcPos();
 private:
  std::mt19937 mersenne;
  void Recalc(Node* node);
  int SafeSize(Node* node);
  void _Insert(Node*& node, int el);
  void _Delete(Node*& node, int el);
  Node* _Merge(Node* left, Node* right);
  std::pair<Node*,Node*> _Split(Node*& node, int key);
  bool _Find(Node* node, int el);
  int _RecalcPos(Node* node, int depth=0, int indent=0);
};
}

