#pragma once
#include <string>
#include <cstring>

// ═══════════════════════════════════════════════
// Узел двусвязного списка в элементе дерева
// ═══════════════════════════════════════════════
struct ChainNode {
    int        index;
    ChainNode* prev;
    ChainNode* next;

    ChainNode(int idx) : index(idx), prev(nullptr), next(nullptr) {}
};

// ═══════════════════════════════════════════════
// Двусвязный список индексов (в узле дерева)
// ═══════════════════════════════════════════════
struct ChainList {
    ChainNode* head;
    ChainNode* tail;
    int        count;

    ChainList() : head(nullptr), tail(nullptr), count(0) {}

    // Добавить в конец
    void AddLast(int index) {
        ChainNode* node = new ChainNode(index);
        if (!tail) {
            head = tail = node;
        }
        else {
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
        count++;
    }

    // Удалить по значению индекса
    bool Remove(int index) {
        ChainNode* cur = head;
        while (cur) {
            if (cur->index == index) {
                if (cur->prev) cur->prev->next = cur->next;
                else           head = cur->next;
                if (cur->next) cur->next->prev = cur->prev;
                else           tail = cur->prev;
                delete cur;
                count--;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    // Очистить весь список
    void Clear() {
        ChainNode* cur = head;
        while (cur) {
            ChainNode* tmp = cur->next;
            delete cur;
            cur = tmp;
        }
        head = tail = nullptr;
        count = 0;
    }

    bool Empty() const { return head == nullptr; }

    // Печать цепочки для отладки
    std::string Print() const {
        std::string out = "";
        ChainNode* cur = head;
        while (cur) {
            char buf[32];
            snprintf(buf, sizeof(buf), "%d", cur->index);
            out += buf;
            if (cur->next) out += " ↔ ";
            cur = cur->next;
        }
        return out;
    }
};

// ═══════════════════════════════════════════════
// Цвет узла КЧД
// ═══════════════════════════════════════════════
enum RBColor { RB_RED, RB_BLACK };

// ═══════════════════════════════════════════════
// Узел красно-чёрного дерева
// ═══════════════════════════════════════════════
struct RBNode {
    char      key[300];
    ChainList chain;       // двусвязный список индексов
    RBColor   color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;

    RBNode(const char* k, int idx, RBColor c = RB_RED)
        : color(c), left(nullptr), right(nullptr), parent(nullptr)
    {
        strncpy_s(key, k, 299);
        chain.AddLast(idx);
    }
};

// ═══════════════════════════════════════════════
// Красно-чёрное дерево
// ═══════════════════════════════════════════════
class BST {
private:
    RBNode* root;
    RBNode* NIL;

    void InitNIL() {
        NIL = new RBNode("", -1, RB_BLACK);
        NIL->chain.Clear();
        NIL->left = NIL->right = NIL->parent = nullptr;
    }

    // ── Повороты ──────────────────────────────
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

    // ── Балансировка после вставки ────────────
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
                    if (z == z->parent->right) { z = z->parent; RotateLeft(z); }
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
                    if (z == z->parent->left) { z = z->parent; RotateRight(z); }
                    z->parent->color = RB_BLACK;
                    gp->color = RB_RED;
                    RotateLeft(gp);
                }
            }
        }
        root->color = RB_BLACK;
    }

    // ── Трансплантация ────────────────────────
    void Transplant(RBNode* u, RBNode* v) {
        if (!u->parent)                root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else                           u->parent->right = v;
        if (v) v->parent = u->parent;
    }

    // ── Максимум левого поддерева ─────────────
    RBNode* MaxNode(RBNode* node) {
        while (node->right != NIL) node = node->right;
        return node;
    }

    // ── Балансировка после удаления ───────────
    void DeleteFix(RBNode* x, RBNode* xParent) {
        while (x != root && (!x || x == NIL || x->color == RB_BLACK)) {
            if (!xParent) break;
            if (x == xParent->left) {
                RBNode* w = xParent->right;
                if (w && w != NIL && w->color == RB_RED) {
                    w->color = RB_BLACK;
                    xParent->color = RB_RED;
                    RotateLeft(xParent); w = xParent->right;
                }
                if (!w || w == NIL) break;
                bool lB = (!w->left || w->left == NIL || w->left->color == RB_BLACK);
                bool rB = (!w->right || w->right == NIL || w->right->color == RB_BLACK);
                if (lB && rB) {
                    if (w) w->color = RB_RED;
                    x = xParent; xParent = x->parent;
                }
                else {
                    if (rB) {
                        if (w->left && w->left != NIL) w->left->color = RB_BLACK;
                        if (w) w->color = RB_RED; RotateRight(w); w = xParent->right;
                    }
                    if (w) w->color = xParent->color;
                    xParent->color = RB_BLACK;
                    if (w->right && w->right != NIL) w->right->color = RB_BLACK;
                    RotateLeft(xParent); x = root; xParent = nullptr;
                }
            }
            else {
                RBNode* w = xParent->left;
                if (w && w != NIL && w->color == RB_RED) {
                    w->color = RB_BLACK;
                    xParent->color = RB_RED;
                    RotateRight(xParent); w = xParent->left;
                }
                if (!w || w == NIL) break;
                bool lB = (!w->left || w->left == NIL || w->left->color == RB_BLACK);
                bool rB = (!w->right || w->right == NIL || w->right->color == RB_BLACK);
                if (lB && rB) {
                    if (w) w->color = RB_RED;
                    x = xParent; xParent = x ? x->parent : nullptr;
                }
                else {
                    if (lB) {
                        if (w->right && w->right != NIL) w->right->color = RB_BLACK;
                        if (w) w->color = RB_RED; RotateLeft(w); w = xParent->left;
                    }
                    if (w) w->color = xParent->color;
                    xParent->color = RB_BLACK;
                    if (w->left && w->left != NIL) w->left->color = RB_BLACK;
                    RotateRight(xParent); x = root; xParent = nullptr;
                }
            }
        }
        if (x && x != NIL) x->color = RB_BLACK;
    }

    // ── Удаление узла ─────────────────────────
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
            y = MaxNode(z->left);
            yOrigColor = y->color;
            x = y->left;
            if (y->parent == z) { xParent = y; }
            else {
                xParent = y->parent;
                Transplant(y, y->left);
                y->left = z->left;
                if (y->left) y->left->parent = y;
            }
            Transplant(z, y);
            y->right = z->right;
            if (y->right) y->right->parent = y;
            y->color = z->color;
        }

        z->chain.Clear();
        delete z;

        if (yOrigColor == RB_BLACK) DeleteFix(x, xParent);
    }

    // ── Поиск узла ────────────────────────────
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

    // ── Печать: правое → узел → левое (убывание)
    void Print(RBNode* node, std::string& out, int depth) const {
        if (!node || node == NIL) return;
        Print(node->right, out, depth + 1);

        std::string indent(depth * 4, ' ');
        const char* col = (node->color == RB_RED) ? "[R]" : "[B]";
        char buf[512];
        snprintf(buf, sizeof(buf), "%s%s \"%s\"", indent.c_str(), col, node->key);
        out += buf;
        out += "  список(";
        out += std::to_string(node->chain.count) + "): ";
        out += node->chain.Print();
        out += "\n";

        Print(node->left, out, depth + 1);
    }

    void Clear(RBNode* node) {
        if (!node || node == NIL) return;
        Clear(node->left);
        Clear(node->right);
        node->chain.Clear();
        delete node;
    }

public:
    BST() : root(nullptr) { InitNIL(); }

    ~BST() { Clear(root); delete NIL; }

    // ── Вставка ───────────────────────────────
    void Insert(const char* key, int index) {
        RBNode* existing = FindNode(key);
        if (existing) {
            existing->chain.AddLast(index);
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
        if (!y)                                root = z;
        else if (strcmp(z->key, y->key) < 0)   y->left = z;
        else                                   y->right = z;

        InsertFix(z);
    }

    // ── Удаление ──────────────────────────────
    bool Delete(const char* key, int index) {
        RBNode* node = FindNode(key);
        if (!node) return false;
        node->chain.Remove(index);
        if (node->chain.Empty()) DeleteNode(node);
        return true;
    }

    // ── Поиск ─────────────────────────────────
    int Search(const char* key, int& steps) const {
        steps = 0;
        RBNode* cur = root;
        while (cur && cur != NIL) {
            steps++;
            int cmp = strcmp(key, cur->key);
            if (cmp == 0) return cur->chain.head->index;
            else if (cmp < 0) cur = cur->left;
            else               cur = cur->right;
        }
        return -1;
    }

    // ── Печать для отладки ────────────────────
    std::string Print() const {
        if (!root || root == NIL) return "[КЧД пусто]\n";
        std::string out = "Обход: справа налево | Удаление: макс. левого поддерева\n";
        out += "[R]=красный  [B]=чёрный | список(N): head ↔ ... ↔ tail\n";
        out += std::string(50, '-') + "\n";
        Print(root, out, 0);
        return out;
    }

    void Clear() { Clear(root); root = nullptr; }
};