#include "Pidrevo.h"
#include <algorithm>

void Pidrevo::PidrevoTree::_Insert(Node*& node, int el) {
  if (_Find(node, el)) return;
  auto tmp = _Split(node, el);
  Node* new_node = new Node;
  new_node->key = el;
  new_node->priority = mersenne();
  root = _Merge(_Merge(tmp.first, new_node), tmp.second);
}

void Pidrevo::PidrevoTree::_Delete(Node*& node, int el) {
  if (!node) return;
  if (node->key == el) {
    auto to_delete = node;
    node = _Merge(node->left, node->right);
    delete to_delete;
  } else if (node->key > el) {
    _Delete(node->left, el);
  } else {
    _Delete(node->right, el);
  }
}

Pidrevo::Node* Pidrevo::PidrevoTree::_Merge(Node* left, Node* right) {
  if (!left && !right) {
    return nullptr;
  }
  if (!left) return right;
  if (!right) return left;
  if (left->priority < right->priority) {
    left->right = _Merge(left->right, right);
    Recalc(left);
    return left;
  } else if (left->priority > right->priority) {
    right->left = _Merge(left, right->left);
    Recalc(right);
    return right;
  } else {
    return nullptr;
  }
}

std::pair<Pidrevo::Node*, Pidrevo::Node*> Pidrevo::PidrevoTree::_Split(
    Node*& node, int key) {
  if (!node) return {nullptr, nullptr};
  if (node->key <= key) {
    auto res = _Split(node->right, key);
    node->right = res.first;
    Recalc(node);
    res.first = node;
    return res;
  } else {
    auto res = _Split(node->left, key);
    node->left = res.second;
    Recalc(node);
    res.second = node;
    return res;
  }
}

bool Pidrevo::PidrevoTree::_Find(Node* node, int el) {
  if (!node) return false;
  if (node->key == el)
    return true;
  else if (node->key > el)
    return _Find(node->left,el);
  else
    return _Find(node->right,el);
}

int Pidrevo::PidrevoTree::_RecalcPos(Node *node, int depth, int indent)
{
  int base_h_indent = 100, base_v_indednt = 100;
  if (node == nullptr) return indent - base_h_indent;
  indent = _RecalcPos(node->left, depth + 1, indent) + base_h_indent;
  node->pos = QPoint(indent, depth * base_v_indednt);
  indent = _RecalcPos(node->right, depth + 1, indent + base_h_indent);
  return indent;
}

Pidrevo::PidrevoTree::PidrevoTree() {
  mersenne.seed(static_cast<unsigned int>(time(0)));
}

void Pidrevo::PidrevoTree::Insert(int el) { _Insert(root, el); }

void Pidrevo::PidrevoTree::Delete(int el) { _Delete(root, el); }

void Pidrevo::PidrevoTree::Merge(Node* right) { root = _Merge(root, right); }

std::pair<Pidrevo::Node*, Pidrevo::Node*> Pidrevo::PidrevoTree::Split(int key) {
  return _Split(root, key);
}

bool Pidrevo::PidrevoTree::Find(int el) { return _Find(root, el);
}

void Pidrevo::PidrevoTree::RecalcPos() { _RecalcPos(root);
}

void Pidrevo::PidrevoTree::Recalc(Node* node) {
  node->size = SafeSize(node);
}

int Pidrevo::PidrevoTree::SafeSize(Node* node) { 
  int res = 0;
  if (node) {
    res++;
    if (node->left) res += node->left->size;
    if (node->right) res += node->right->size;
  }
  return res;
}
