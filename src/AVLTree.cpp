#include "AVLTree.h"

void AVL::AVLTree::_InOrder(Node* node) {
  if (node) {
    _InOrder(node->left);
    _InOrder(node->right);
  }
}

void AVL::AVLTree::InOrder() { _InOrder(root); }

void AVL::AVLTree::_Insert(Node*& node, int el) {
  if (node == nullptr) {
    node = new Node;
    node->data = el;
    return;
  }

  if (node->data > el) {
    _Insert(node->left, el);
    node->h = std::max(_SafeHeight(node->left), _SafeHeight(node->right)) + 1;
    Balance(node);
  } else if (node->data < el) {
    _Insert(node->right, el);
    node->h = std::max(_SafeHeight(node->left), _SafeHeight(node->right)) + 1;
    Balance(node);
  } else {
    return;
  }
}

void AVL::AVLTree::Insert(int el) { _Insert(root, el);
}

void AVL::AVLTree::_Erase(Node*& node, int el) {
  if (node == nullptr) return;
  if (node->data == el) {
    DelElem(node);
  } else if (node->data > el) {
    _Erase(node->left, el);
    node->h = std::max(_SafeHeight(node->left), _SafeHeight(node->right)) + 1;
    Balance(node);
  } else {
    _Erase(node->right, el);
    node->h = std::max(_SafeHeight(node->left), _SafeHeight(node->right)) + 1;
    Balance(node);
  }
  return;
}

void AVL::AVLTree::Erase(int el) { _Erase(root, el); }

int AVL::AVLTree::_SafeHeight(Node* node) {
  if (node)
    return node->h;
  else
    return 0;
}

int AVL::AVLTree::_Recalc(Node* node, int depth, int indent) {
  int base_h_indent = 100, base_v_indednt = 100;
  if (node == nullptr) return indent - base_h_indent;
  indent = _Recalc(node->left, depth + 1, indent) + base_h_indent;
  node->pos = QPoint(indent, depth * base_v_indednt);
  indent = _Recalc(node->right, depth + 1, indent + base_h_indent);
  return indent;
}

int AVL::AVLTree::SafeHeight() { return _SafeHeight(root); }

void AVL::AVLTree::Recalc() { _Recalc(root); }

void AVL::AVLTree::DelElem(Node*& node) {
  if (node->left == nullptr) {
    Node* tmp = node;
    node = node->right;
    delete tmp;
  } else {
    node->data = DelMax(node->left);
  }
}

int AVL::AVLTree::DelMax(Node*& node) { 
  if (node->right == nullptr) {
    auto tmp = node;
    int res = node->data;
    node = node->left;
    if (node) {
      node->h = std::max(_SafeHeight(node->left), _SafeHeight(node->right)) + 1;
    }
    delete tmp;
    return res;
  }
  int res = DelMax(node->right);
  if (node) {
  node->h = std::max(_SafeHeight(node->left), _SafeHeight(node->right)) + 1;
  Balance(node);
  }
  return res;
}

void AVL::AVLTree::Balance(Node*& node) {
  if (std::abs(_SafeHeight(node->left) - _SafeHeight(node->right)) >= 2) {
    if (_SafeHeight(node->left) > _SafeHeight(node->right)) {
      if (_SafeHeight(node->left->right) > _SafeHeight(node->left->left)) {
        BigRot(node);
      } else {
        SmallRot(node);
      }
    } else {
      if (_SafeHeight(node->right->left) > _SafeHeight(node->right->right)) {
        BigRot(node);
      } else {
        SmallRot(node);
      }
    }
  }
}

void AVL::AVLTree::SmallRot(Node*& node) {
  if (_SafeHeight(node->right) > _SafeHeight(node->left)) {
    auto tmp = node->right;
    node->right = tmp->left;
    node->h = std::max(_SafeHeight(node->left), _SafeHeight(node->right)) + 1;
    tmp->left = node;
    node = tmp;
    node->h = std::max(_SafeHeight(node->left), _SafeHeight(node->right)) + 1;
  } else {
    auto tmp = node->left;
    node->left = tmp->right;
    node->h = std::max(_SafeHeight(node->left), _SafeHeight(node->right)) + 1;
    tmp->right = node;
    node = tmp;
    node->h = std::max(_SafeHeight(node->left), _SafeHeight(node->right)) + 1;
  }
}

void AVL::AVLTree::BigRot(Node*& node) {
  if (_SafeHeight(node->right) > _SafeHeight(node->left)) {
    auto tmp_b = node->right, tmp_d = tmp_b->left;
    node->right = tmp_d->left;
    node->h = std::max(_SafeHeight(node->left), _SafeHeight(node->right)) + 1;
    tmp_b->left = tmp_d->right;
    tmp_b->h = std::max(_SafeHeight(tmp_b->left), _SafeHeight(tmp_b->right)) + 1;
    tmp_d->left = node;
    tmp_d->right = tmp_b;
    node = tmp_d;
    node->h = std::max(_SafeHeight(node->left), _SafeHeight(node->right)) + 1;
  } else {
    auto tmp_b = node->left, tmp_d = tmp_b->right;
    node->left = tmp_d->right;
    node->h = std::max(_SafeHeight(node->left), _SafeHeight(node->right)) + 1;
    tmp_b->right = tmp_d->left;
    tmp_b->h = std::max(_SafeHeight(tmp_b->left), _SafeHeight(tmp_b->right)) + 1;
    tmp_d->right = node;
    tmp_d->left = tmp_b;
    node = tmp_d;
    node->h = std::max(_SafeHeight(node->left), _SafeHeight(node->right)) + 1;
  }
}
