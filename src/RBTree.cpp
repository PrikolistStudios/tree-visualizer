#include "RBTree.h"

void RB::RBTree::Recalc() { _Recalc(root);
}

void RB::RBTree::Erase(int el) {
  Node* to_del = root;
  while (to_del != TNULL) {
    if (to_del->data > el) {
      to_del = to_del->left;
    } else if (to_del->data < el) {
      to_del = to_del->right;
    } else {
      break;
    }
  }

  if (to_del == TNULL) return;

  if (to_del->right == TNULL) {
    Transplant(to_del, to_del->left);
    if(!to_del->red) {
      DeleteRecolor(to_del->left);
    }
    delete to_del;
    return;
  } else if (to_del->left == TNULL) {
    Transplant(to_del, to_del->right);
    if(!to_del->red) {
      DeleteRecolor(to_del->right);
    }
    delete to_del;
    return;
  }


  auto max = Maximum(to_del->left);
  to_del->data = max->data;

  if (max->red) {
    if (max == max->parent->left) {
      max->parent->left = TNULL;
    } else {
      max->parent->right = TNULL;
    }
    delete max;
  } else if (max->left->red) {
    max->left->red = 0;
    if (max == max->parent->left) {
      max->parent->left = max->left;
    } else {
      max->parent->right = max->left;
    }
    delete max;
  } else {
    DeleteRecolor(max);
    if (max == max->parent->left) {
      max->parent->left = TNULL;
    } else {
      max->parent->right = TNULL;
    }
    delete max;
  }
}

void RB::RBTree::RightRotate(Node* x) {
  Node* y = x->left;
  x->left = y->right;
  if (y->right != TNULL) {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nullptr) {
    this->root = y;
  } else if (x == x->parent->right) {
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;}

void RB::RBTree::LeftRotate(Node* x) {
  Node* y = x->right;
  x->right = y->left;
  if (y->left != TNULL) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nullptr) {
    this->root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;}

void RB::RBTree::Transplant(Node* u, Node* v) { 
  if (u->parent==nullptr) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

RB::Node* RB::RBTree::Maximum(Node* node) {
  if (node == TNULL) return TNULL;
  while (node->right != TNULL) node = node->right;
  return node;
}

RB::Node* RB::RBTree::Minimum(Node* node) {
  while (node->left != TNULL) {
    node = node->left;
  }
  return node;
}

int RB::RBTree::_Recalc(Node* node, int depth, int indent) {
  int base_h_indent = 100, base_v_indednt = 100;
  if (node == TNULL) return indent - base_h_indent;
  indent = _Recalc(node->left, depth + 1, indent) + base_h_indent;
  node->pos = QPoint(indent, depth * base_v_indednt);
  indent = _Recalc(node->right, depth + 1, indent + base_h_indent);
  return indent;
}

void RB::RBTree::Insert(int el) {
  Node* node = new Node;
  node->parent = nullptr;
  node->data = el;
  node->left = TNULL;
  node->right = TNULL;
  node->red = 1;

  Node* par = nullptr;
  Node* tmp = this->root;

  while (tmp != TNULL) {
    par = tmp;
    if (node->data < tmp->data) {
      tmp = tmp->left;
    } else if (node->data > tmp->data) {
      tmp = tmp->right;
    } else {
      return;
    }
  }

  node->parent = par;
  if (par == nullptr) {
    root = node;
    root->red = 0;
  } else if (node->data < par->data) {
    par->left = node;
  } else {
    par->right = node;
  }

  if (node->parent == nullptr) return;
  if (node->parent->parent == nullptr) return;
  InsertRecolor(node);
}

void RB::RBTree::InsertRecolor(Node* node) {
  while (node->parent != nullptr && node->parent->red) {
    if (node->parent == node->parent->parent->left) {
      Node* uncle = node->parent->parent->right;
      if (uncle->red) {
        node->parent->red = uncle->red = 0;
        node = node->parent->parent;
        node->red = 1;
      } else if (node == node->parent->left && !uncle->red) {
        node->parent->parent->red = 1;
        node->parent->red = 0;
        RightRotate(node->parent->parent);
        return;
      } else if (node == node->parent->right && !uncle->red) {
        node = node->parent;
        LeftRotate(node);
      }
    } else {
      Node* uncle = node->parent->parent->left;
      if (uncle->red) {
        node->parent->red = uncle->red = 0;
        node = node->parent->parent;
        node->red = 1;
      } else if (node == node->parent->right && !uncle->red) {
        node->parent->parent->red = 1;
        node->parent->red = 0;
        LeftRotate(node->parent->parent);
        return;
      } else if (node == node->parent->left && !uncle->red) {
        node = node->parent;
        RightRotate(node);
      }
    }
  }
  root->red = 0;
}

void RB::RBTree::DeleteRecolor(Node* node) {
  while (node != root && !node->red) {
    if (node == node->parent->left) {
      Node* sib = node->parent->right;
      if (!node->parent->red && !sib->red && !sib->left->red &&
          !sib->right->red) {
        // all black
        sib->red = 1;
        node = node->parent;
      } else if (node->parent->red) {
        node->parent->red = 0;
        sib->red = 1;
        return;
      } else if (!sib->red && sib->right->red) {
        std::swap(sib->red, node->parent->red);
        sib->right->red = 0;
        LeftRotate(node->parent);
        return;
      } else if (!sib->red && sib->left->red) {
        sib->red = 1;
        sib->left->red = 0;
        RightRotate(sib);
      } else if (sib->red) {
        sib->red = 0;
        node->parent->red = 1;
        LeftRotate(node->parent);
      }
    } else {
      Node* sib = node->parent->left;
      if (!node->parent->red && !sib->red && !sib->right->red &&
          !sib->left->red) {
        // all black
        sib->red = 1;
        node = node->parent;
      } else if (node->parent->red) {
        node->parent->red = 0;
        sib->red = 1;
        return;
      } else if (!sib->red && sib->left->red) {
        std::swap(sib->red, node->parent->red);
        sib->left->red = 0;
        RightRotate(node->parent);
        return;
      } else if (!sib->red && sib->right->red) {
        sib->red = 1;
        sib->right->red = 0;
        LeftRotate(sib);
      } else if (sib->red) {
        sib->red = 0;
        node->parent->red = 1;
        RightRotate(node->parent);
      }
    }
  }
  node->red = 0;
}
