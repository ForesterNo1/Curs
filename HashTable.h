#pragma once
#include <string>
#include <cstring>

// Статус ячейки
enum SlotStatus { EMPTY = 0, OCCUPIED = 1, DELETED = 2 };

// Ячейка таблицы
struct HTSlot {
    char      key[300];
    int       index;
    SlotStatus status;

    HTSlot() : index(-1), status(EMPTY) { key[0] = '\0'; }
};

struct HTInsertInfo {
    int  primaryHash;
    int  steps;
    bool success;
};

class HashTable {
private:
    HTSlot* table;
    int     size;
    static const int STEP = 3;  // шаг линейного зондирования k > 1

    // ── Хеш-функция: СВЁРТКА ──────────────────────
    // Разбиваем ключ на 4-байтовые блоки, суммируем
    int hash(const char* key) const {
        unsigned long sum = 0;
        int len = (int)strlen(key);
        int i = 0;
        while (i < len) {
            unsigned int chunk = 0;
            for (int j = 0; j < 4 && i < len; j++, i++)
                chunk |= ((unsigned char)key[i]) << (j * 8);
            sum += chunk;
        }
        return (int)(sum % (unsigned long)size);
    }

    // ── Линейное зондирование с шагом k > 1 ───────
    int probe(int h0, int i) const {
        return (h0 + i * STEP) % size;
    }

public:
    HashTable(int sz) : size(sz) {
        table = new HTSlot[size];
    }

    ~HashTable() { delete[] table; }

    int GetSize() const { return size; }

    // ── Вставка ───────────────────────────────────
   

    HTInsertInfo InsertEx(const char* key, int index) {
        HTInsertInfo info;
        info.primaryHash = hash(key);
        info.steps = 0;
        info.success = false;

        int h0 = info.primaryHash;
        for (int i = 0; i < size; i++) {
            int h = probe(h0, i);
            info.steps++;
            if (table[h].status == EMPTY || table[h].status == DELETED) {
                strncpy_s(table[h].key, key, 299);
                table[h].index = index;
                table[h].status = OCCUPIED;
                info.success = true;
                return info;
            }
        }
        return info;
    }

    // Оставляем старый Insert как обёртку
    bool Insert(const char* key, int index) {
        return InsertEx(key, index).success;
    }

    // ── Поиск ─────────────────────────────────────
    // steps — кол-во шагов зондирования
    int Search(const char* key, int& steps) const {
        int h0 = hash(key);
        steps = 0;
        for (int i = 0; i < size; i++) {
            int h = probe(h0, i);
            steps++;
            if (table[h].status == EMPTY)
                return -1; // цепочка зондирования оборвалась
            if (table[h].status == OCCUPIED &&
                strcmp(table[h].key, key) == 0)
                return table[h].index;
            // DELETED — пропускаем, продолжаем
        }
        return -1;
    }

    // ── Удаление — помечаем как DELETED (статус 2) ─
    bool Delete(const char* key) {
        int h0 = hash(key);
        for (int i = 0; i < size; i++) {
            int h = probe(h0, i);
            if (table[h].status == EMPTY)
                return false;
            if (table[h].status == OCCUPIED &&
                strcmp(table[h].key, key) == 0) {
                table[h].status = DELETED;  // мягкое удаление
                return true;
            }
        }
        return false;
    }

    // ── Очистка ───────────────────────────────────
    void Clear() {
        for (int i = 0; i < size; i++) {
            table[i].key[0] = '\0';
            table[i].index = -1;
            table[i].status = EMPTY;
        }
    }

    // ── Печать для окна отладки ───────────────────
    // Выводим: адрес | статус | первичный хеш | ключ | индекс
    std::string Print() const {
        std::string out = "";
        char buf[512];
        snprintf(buf, sizeof(buf),
            "Размер: %d  |  Шаг зондирования k=%d  |  ХФ: свёртка\n",
            size, STEP);
        out += buf;
        snprintf(buf, sizeof(buf), "%-6s %-3s %-6s %-6s  %s\n",
            "Слот", "Ст", "H1", "H_факт", "Ключ (индекс)");
        out += buf;
        out += std::string(60, '-') + "\n";

        for (int i = 0; i < size; i++) {
            const char* stStr =
                (table[i].status == EMPTY) ? " 0 " :
                (table[i].status == OCCUPIED) ? " 1 " : " 2 ";

            if (table[i].status == EMPTY) {
                snprintf(buf, sizeof(buf), "[%3d] %s ---    ---    пусто\n", i, stStr);
            }
            else if (table[i].status == DELETED) {
                snprintf(buf, sizeof(buf), "[%3d] %s ---    ---    удалено\n", i, stStr);
            }
            else {
                int h0 = hash(table[i].key);
                snprintf(buf, sizeof(buf),
                    "[%3d] %s H1=%-3d H=%-3d  \"%s\" (idx=%d)\n",
                    i, stStr, h0, i, table[i].key, table[i].index);
            }
            out += buf;
        }
        return out;
    }
};