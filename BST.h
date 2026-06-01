#pragma once
#include <string>
#include <cstring>

struct ChainNode {
    int        index;
    ChainNode* next;
    ChainNode(int idx) : index(idx), next(nullptr) {}
};

enum RBColor { RB_RED, RB_BLACK };

struct RBNode {
    char       key[300];
    ChainNode* chain;
    RBColor    color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;

    RBNode(const char* k, int idx, RBColor c = RB_RED)
        : color(c), left(nullptr), right(nullptr), parent(nullptr)
    {
        strncpy_s(key, k, 299);
        chain = new ChainNode(idx);
    }
};

class BST {
private:
    RBNode* root;
    RBNode* NIL;

    void InitNIL() {
        NIL = new RBNode("", -1, RB_BLACK);
        NIL->left = NIL->right = NIL->parent = nullptr;
        // Удаляем автоматически созданную цепочку
        delete NIL->chain;
        NIL->chain = nullptr;
    }

    // ── Повороты ──────────────────────────────────
    void RotateLeft(RBNode* x) {
        RBNode* y = x->right;
        x->right = y->left;
        if (y->left != NIL) y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent)                root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else                           x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void RotateRight(RBNode* x) {
        RBNode* y = x->left;
        x->left = y->right;
        if (y->right != NIL) y->right->parent = x;
        y->parent = x->parent;
        if (!x->parent)                 root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else                            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    // ── Балансировка после вставки ────────────────
    void InsertFix(RBNode* z) {
        while (z->parent && z->parent->color == RB_RED) {
            RBNode* gp = z->parent->parent;
            if (!gp) break;
            if (z->parent == gp->left) {
                RBNode* uncle = gp->right;
                if (uncle && uncle != NIL && uncle->color == RB_RED) {
                    z->parent->color = RB_BLACK;
                    uncle->color = RB_BLACK;
                    gp->color = RB_RED;
                    z = gp;
                }
                else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        RotateLeft(z);
                    }
                    z->parent->color = RB_BLACK;
                    gp->color = RB_RED;
                    RotateRight(gp);
                }
            }
            else {
                RBNode* uncle = gp->left;
                if (uncle && uncle != NIL && uncle->color == RB_RED) {
                    z->parent->color = RB_BLACK;
                    uncle->color = RB_BLACK;
                    gp->color = RB_RED;
                    z = gp;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        RotateRight(z);
                    }
                    z->parent->color = RB_BLACK;
                    gp->color = RB_RED;
                    RotateLeft(gp);
                }
            }
        }
        root->color = RB_BLACK;
    }

    // ── Transplant ────────────────────────────────
    void Transplant(RBNode* u, RBNode* v) {
        if (!u->parent)                root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else                           u->parent->right = v;
        if (v) v->parent = u->parent;
    }

    // ── Максимум левого поддерева (для удаления) ──
    RBNode* MaxNode(RBNode* node) {
        while (node->right != NIL) node = node->right;
        return node;
    }

    // ── Балансировка после удаления ───────────────
    void DeleteFix(RBNode* x, RBNode* xParent) {
        while (x != root && (!x || x == NIL || x->color == RB_BLACK)) {
            if (!xParent) break;
            if (x == xParent->left) {
                RBNode* w = xParent->right;
                if (w && w != NIL && w->color == RB_RED) {
                    w->color = RB_BLACK;
                    xParent->color = RB_RED;
                    RotateLeft(xParent);
                    w = xParent->right;
                }
                if (!w || w == NIL) break;
                bool leftBlack = (!w->left || w->left == NIL || w->left->color == RB_BLACK);
                bool rightBlack = (!w->right || w->right == NIL || w->right->color == RB_BLACK);
                if (leftBlack && rightBlack) {
                    w->color = RB_RED;
                    x = xParent; xParent = x->parent;
                }
                else {
                    if (rightBlack) {
                        if (w->left && w->left != NIL) w->left->color = RB_BLACK;
                        w->color = RB_RED;
                        RotateRight(w);
                        w = xParent->right;
                    }
                    w->color = xParent->color;
                    xParent->color = RB_BLACK;
                    if (w->right && w->right != NIL) w->right->color = RB_BLACK;
                    RotateLeft(xParent);
                    x = root; xParent = nullptr;
                }
            }
            else {
                RBNode* w = xParent->left;
                if (w && w != NIL && w->color == RB_RED) {
                    w->color = RB_BLACK;
                    xParent->color = RB_RED;
                    RotateRight(xParent);
                    w = xParent->left;
                }
                if (!w || w == NIL) break;
                bool leftBlack = (!w->left || w->left == NIL || w->left->color == RB_BLACK);
                bool rightBlack = (!w->right || w->right == NIL || w->right->color == RB_BLACK);
                if (leftBlack && rightBlack) {
                    w->color = RB_RED;
                    x = xParent; xParent = x->parent;
                }
                else {
                    if (leftBlack) {
                        if (w->right && w->right != NIL) w->right->color = RB_BLACK;
                        w->color = RB_RED;
                        RotateLeft(w);
                        w = xParent->left;
                    }
                    w->color = xParent->color;
                    xParent->color = RB_BLACK;
                    if (w->left && w->left != NIL) w->left->color = RB_BLACK;
                    RotateRight(xParent);
                    x = root; xParent = nullptr;
                }
            }
        }
        if (x && x != NIL) x->color = RB_BLACK;
    }

    // ── Удаление узла (через макс. левого поддерева)
    void DeleteNode(RBNode* z) {
        RBNode* y = z;
        RBNode* x = nullptr;
        RBNode* xParent = nullptr;
        RBColor yOrigColor = y->color;

        if (z->left == NIL) {
            x = z->right; xParent = z->parent;
            Transplant(z, z->right);
        }
        else if (z->right == NIL) {
            x = z->left; xParent = z->parent;
            Transplant(z, z->left);
        }
        else {
            // ── МАКСИМУМ ЛЕВОГО поддерева ─────────
            y = MaxNode(z->left);
            yOrigColor = y->color;
            x = y->left;  // у максимума нет правого потомка
            if (y->parent == z) {
                xParent = y;
            }
            else {
                xParent = y->parent;
                Transplant(y, y->left);   // заменяем y его левым
                y->left = z->left;
                if (y->left) y->left->parent = y;
            }
            Transplant(z, y);
            y->right = z->right;
            if (y->right) y->right->parent = y;
            y->color = z->color;
        }

        // Освобождаем цепочку удаляемого узла
        ChainNode* c = z->chain;
        while (c) { ChainNode* t = c->next; delete c; c = t; }
        z->chain = nullptr;
        delete z;

        if (yOrigColor == RB_BLACK)
            DeleteFix(x, xParent);
    }

    // ── Поиск узла ────────────────────────────────
    RBNode* FindNode(const char* key) const {
        RBNode* cur = root;
        while (cur && cur != NIL) {
            int cmp = strcmp(key, cur->key);
            if (cmp == 0) return cur;
            else if (cmp < 0) cur = cur->left;
            else               cur = cur->right;
        }
        return nullptr;
    }

    // ── Печать: СПРАВА НАЛЕВО (убывающий порядок) ─
    // right → node → left
    void Print(RBNode* node, std::string& out, int depth) const {
        if (!node || node == NIL) return;

        // Сначала правое поддерево
        Print(node->right, out, depth + 1);

        // Узел
        std::string indent(depth * 4, ' ');
        const char* col = (node->color == RB_RED) ? "[R]" : "[B]";
        char buf[512];
        snprintf(buf, sizeof(buf), "%s%s \"%s\"", indent.c_str(), col, node->key);
        out += buf;

        // Цепочка индексов
        out += "  idx:";
        ChainNode* c = node->chain;
        while (c) {
            snprintf(buf, sizeof(buf), "%d", c->index);
            out += buf;
            if (c->next) out += ",";
            c = c->next;
        }
        out += "\n";

        // Потом левое поддерево
        Print(node->left, out, depth + 1);
    }

    void Clear(RBNode* node) {
        if (!node || node == NIL) return;
        Clear(node->left);
        Clear(node->right);
        ChainNode* c = node->chain;
        while (c) { ChainNode* t = c->next; delete c; c = t; }
        delete node;
    }

public:
    BST() : root(nullptr) { InitNIL(); }

    ~BST() { Clear(root); delete NIL; }

    // ── Вставка ───────────────────────────────────
    void Insert(const char* key, int index) {
        RBNode* existing = FindNode(key);
        if (existing) {
            ChainNode* c = new ChainNode(index);
            c->next = existing->chain;
            existing->chain = c;
            return;
        }
        RBNode* z = new RBNode(key, index, RB_RED);
        z->left = z->right = NIL;

        RBNode* y = nullptr;
        RBNode* x = root;
        while (x && x != NIL) {
            y = x;
            if (strcmp(z->key, x->key) < 0) x = x->left;
            else                             x = x->right;
        }
        z->parent = y;
        if (!y)                                  root = z;
        else if (strcmp(z->key, y->key) < 0)     y->left = z;
        else                                     y->right = z;

        InsertFix(z);
    }

    // ── Удаление ──────────────────────────────────
    bool Delete(const char* key, int index) {
        RBNode* node = FindNode(key);
        if (!node) return false;

        ChainNode* cur = node->chain, * prev = nullptr;
        while (cur) {
            if (cur->index == index) {
                if (prev) prev->next = cur->next;
                else      node->chain = cur->next;
                delete cur;
                break;
            }
            prev = cur; cur = cur->next;
        }
        if (!node->chain)
            DeleteNode(node);
        return true;
    }

    // ── Поиск ─────────────────────────────────────
    int Search(const char* key, int& steps) const {
        steps = 0;
        RBNode* cur = root;
        while (cur && cur != NIL) {
            steps++;
            int cmp = strcmp(key, cur->key);
            if (cmp == 0) return cur->chain->index;
            else if (cmp < 0) cur = cur->left;
            else               cur = cur->right;
        }
        return -1;
    }

    // ── Печать для отладки ────────────────────────
    std::string Print() const {
        if (!root || root == NIL) return "[КЧД пусто]\n";
        std::string out = "Обход: справа налево (убывание)\n";
        out += "Удаление: через макс. левого поддерева\n";
        out += "[R]=красный  [B]=чёрный\n";
        out += std::string(50, '-') + "\n";
        Print(root, out, 0);
        return out;
    }

    void Clear() { Clear(root); root = nullptr; }
};