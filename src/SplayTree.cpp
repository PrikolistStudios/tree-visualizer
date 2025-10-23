#include "SplayTree.h"
#include <algorithm>

void Splay::SplayTree::Insert(int el) {
  if (root == nullptr) {
    Node* new_node = new Node;
    new_node->data = el;
    root = new_node;
    return;
  }
  root = Splay(root, el);
  if (root->data == el) return;

  Node* new_node = new Node;
  new_node->data = el;

  if (root->data > el) {
    new_node->right = root;
    new_node->left = root->left;
    root->left = nullptr;
    root = new_node;
  } else {
    new_node->left = root;
    new_node->right = root->right;
    root->right = nullptr;
    root = new_node;
  }
}
void Splay::SplayTree::Erase(int el) {
  if (root == nullptr) return;
  root = Splay(root, el);
  if (root->data != el) return;
  if (root->left == nullptr) {
    auto tmp = root;
    root = tmp->right;
    delete tmp;
    return;
  }

  auto tmp = root->left;
  while (tmp->right != nullptr) tmp = tmp->right;
  root->left = Splay(root->left, tmp->data);
  root->left->right = root->right;
  auto to_del = root;
  root = root->left;
  delete to_del;
}
void Splay::SplayTree::Recalc() { _Recalc(root);
}

int Splay::SplayTree::_Recalc(Node *node, int depth, int indent)
{
  int base_h_indent = 100, base_v_indednt = 100;
  if (node == nullptr) return indent - base_h_indent;
  indent = _Recalc(node->left, depth + 1, indent) + base_h_indent;
  node->pos = QPoint(indent, depth * base_v_indednt);
  indent = _Recalc(node->right, depth + 1, indent + base_h_indent);
  return indent;
}

Splay::Node* Splay::SplayTree::Zig(Node* node) {
  Node* tmp = node->left;
  node->left = tmp->right;
  tmp->right = node;
  return tmp;
}
Splay::Node* Splay::SplayTree::Zag(Node* node) {
  Node* tmp = node->right;
  node->right = tmp->left;
  tmp->left = node;
  return tmp;
}
Splay::Node* Splay::SplayTree::Splay(Node* root, int el) {
  if (root == nullptr || root->data == el) return root;
  if (root->data > el) {
    if (root->left == nullptr) return root;
    if (root->left->data > el) {
      root->left->left = Splay(root->left->left, el);
      root = Zig(root);
    } else if (root->left->data < el) {
      root->left->right = Splay(root->left->right, el);
      if (root->left->right != nullptr) {
        root->left = Zag(root->left);
      }
    }
    return (root->left == nullptr) ? root : Zig(root);
  } else {
    if (root->right == nullptr) return root;
    if (root->right->data > el) {
      root->right->left = Splay(root->right->left, el);
      if (root->right->left != nullptr) {
        root->right = Zig(root->right);
      }
    } else if (root->right->data < el) {
      root->right->right = Splay(root->right->right, el);
      root = Zag(root);
    }
    return (root->right == nullptr) ? root : Zag(root);

  }
}
