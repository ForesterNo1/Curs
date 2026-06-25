#pragma once
#include "Structs.h"
#include "HashTable.h"
#include "BST.h"
#include <fstream>
#include <cstring>

#define MAX_RECORDS 1000

// ── Вспомогательная: название месяца (cp1251) → номер ──
static int MonthToNum(const char* month) {
    int len = (int)strlen(month);
    unsigned char f = (unsigned char)month[0];
    unsigned char s = len > 1 ? (unsigned char)month[1] : 0;
    unsigned char t = len > 2 ? (unsigned char)month[2] : 0;
    switch (len) {
    case 3: return 5;                          // май
    case 4:
        if (f == 0xEC) return 3;               // март
        return (t == 0xED) ? 6 : 7;            // июнь / июль
    case 6:
        if (f == 0xFF) return 1;               // январь
        if (f == 0xED) return 11;              // ноябрь
        return (s == 0xEF) ? 4 : 8;            // апрель / август
    case 7:
        if (f == 0xF4) return 2;               // февраль
        if (f == 0xEE) return 10;              // октябрь
        return 12;                              // декабрь
    case 8: return 9;                          // сентябрь
    default: return 0;
    }
}

class DataManager {
public:
    // ── Массивы данных ────────────────────────────
    Volunteer volunteers[MAX_RECORDS];
    Event     events[MAX_RECORDS];
    int       volCount;
    int       evCount;

    // ── Структуры данных ──────────────────────────
    HashTable* htVolunteers;
    HashTable* htEvents;
    BST* bstVolunteers;
    BST* bstEvents;        // ключ: ФИО волонтёра|Город
    BST* bstEventsByDate;  // ключ: YYYYMMDD (для отчёта по периоду)

    std::string operationLog;

    // ── Конструктор ───────────────────────────────
    DataManager(int htSize = 17) : volCount(0), evCount(0) {
        htVolunteers = new HashTable(htSize);
        htEvents = new HashTable(htSize);
        bstVolunteers = new BST();
        bstEvents = new BST();
        bstEventsByDate = new BST();
    }

    ~DataManager() {
        delete htVolunteers;
        delete htEvents;
        delete bstVolunteers;
        delete bstEvents;
        delete bstEventsByDate;
    }

    // ── Пересобрать все СД с новым размером ХТ ───
    void RebuildStructures(int newHtSize) {
        delete htVolunteers;  delete htEvents;
        delete bstVolunteers; delete bstEvents; delete bstEventsByDate;

        htVolunteers = new HashTable(newHtSize);
        htEvents = new HashTable(newHtSize);
        bstVolunteers = new BST();
        bstEvents = new BST();
        bstEventsByDate = new BST();

        for (int i = 0; i < volCount; i++) InsertToStructures_Vol(i);
        for (int i = 0; i < evCount; i++) {
            InsertToStructures_Ev(i);
            InsertToStructures_EvDate(i);
        }
    }

    // ══════════════════════════════════════════════
    // КЛЮЧИ
    // ══════════════════════════════════════════════

    void MakeKeyVol(const Volunteer& v, char* out, int sz) {
        snprintf(out, sz, "%s|%s", v.fio, v.city);
    }

    void MakeKeyEv(const Event& e, char* out, int sz) {
        snprintf(out, sz, "%s|%s", e.vol_fio, e.city);
    }

    // Ключ даты: "15 январь 2024" → "20240115" (сортируется правильно)
    void MakeKeyEvDate(const Event& e, char* out, int sz) {
        char tmp[50];
        strncpy_s(tmp, e.date, 49);
        char* ctx = nullptr;
        char* dayStr = strtok_s(tmp, " ", &ctx);
        char* monthStr = strtok_s(nullptr, " ", &ctx);
        char* yearStr = strtok_s(nullptr, " ", &ctx);
        if (!dayStr || !monthStr || !yearStr) {
            strncpy_s(out, sz, e.date, sz - 1);
            return;
        }
        int day = atoi(dayStr);
        int month = MonthToNum(monthStr);
        int year = atoi(yearStr);
        snprintf(out, sz, "%04d%02d%02d", year, month, day);
    }

    // ══════════════════════════════════════════════
    // ВСТАВКА В СД
    // ══════════════════════════════════════════════

    void InsertToStructures_Vol(int idx, bool log = false) {
        char key[300];
        MakeKeyVol(volunteers[idx], key, 300);
        HTInsertInfo info = htVolunteers->InsertEx(key, idx);
        bstVolunteers->Insert(key, idx);
        if (log) {
            char buf[512];
            snprintf(buf, sizeof(buf),
                "[ХТ Волонтёры] Вставка: \"%s\"\n"
                "  H1 = %d | Шагов: %d | Факт. слот: %d\n",
                key, info.primaryHash, info.steps,
                (info.primaryHash + (info.steps - 1) * 3) % htVolunteers->GetSize());
            operationLog += buf;
            snprintf(buf, sizeof(buf), "[КЧД Волонтёры] Ключ: \"%s\"\n", key);
            operationLog += buf;
        }
    }

    void InsertToStructures_Ev(int idx, bool log = false) {
        char key[300];
        MakeKeyEv(events[idx], key, 300);
        HTInsertInfo info = htEvents->InsertEx(key, idx);
        bstEvents->Insert(key, idx);
        if (log) {
            char buf[512];
            snprintf(buf, sizeof(buf),
                "[ХТ Мероприятия] Вставка: \"%s\"\n"
                "  H1 = %d | Шагов: %d | Факт. слот: %d\n",
                key, info.primaryHash, info.steps,
                (info.primaryHash + (info.steps - 1) * 3) % htEvents->GetSize());
            operationLog += buf;
            snprintf(buf, sizeof(buf), "[КЧД Мероприятия по ФИО|Город] Ключ: \"%s\"\n", key);
            operationLog += buf;
        }
    }

    void InsertToStructures_EvDate(int idx, bool log = false) {
        char dateKey[50];
        MakeKeyEvDate(events[idx], dateKey, 50);
        bstEventsByDate->Insert(dateKey, idx);
        if (log) {
            char buf[256];
            snprintf(buf, sizeof(buf),
                "[КЧД Мероприятия по Дате] Ключ: \"%s\" (исх. дата: \"%s\")\n",
                dateKey, events[idx].date);
            operationLog += buf;
        }
    }

    // ══════════════════════════════════════════════
    // CRUD — ВОЛОНТЁРЫ
    // ══════════════════════════════════════════════

    // 0=OK, 1=полон, 2=дубликат
    int AddVolunteer(const char* fio, const char* city, const char* skills) {
        if (volCount >= MAX_RECORDS) return 1;
        char key[300];
        snprintf(key, 300, "%s|%s", fio, city);
        int steps;
        if (htVolunteers->Search(key, steps) >= 0) return 2;

        int idx = volCount++;
        strncpy_s(volunteers[idx].fio, fio, 99);
        strncpy_s(volunteers[idx].city, city, 99);
        strncpy_s(volunteers[idx].skills, skills, 199);

        operationLog = "=== ДОБАВЛЕНИЕ ВОЛОНТЁРА ===\n";
        char buf[256];
        snprintf(buf, sizeof(buf), "ФИО: %s | Город: %s\n---\n", fio, city);
        operationLog += buf;
        InsertToStructures_Vol(idx, true);

        // Авторасширение ХТ при заполнении > 80%
        if (volCount >= (int)(htVolunteers->GetSize() * 0.8)) {
            int newSize = NextPrime(htVolunteers->GetSize() * 2);
            RebuildStructures(newSize);
            operationLog += "[ХТ авторасширение] Новый размер: "
                + std::to_string(newSize) + "\n";
        }
        return 0;
    }

    // 0=OK, 1=не найден, 2=есть мероприятия
    int DeleteVolunteer(int idx) {
        if (idx < 0 || idx >= volCount) return 1;
        for (int i = 0; i < evCount; i++)
            if (strcmp(events[i].vol_fio, volunteers[idx].fio) == 0) return 2;

        char key[300];
        MakeKeyVol(volunteers[idx], key, 300);

        operationLog = "=== УДАЛЕНИЕ ВОЛОНТЁРА ===\n";
        char buf[256];
        snprintf(buf, sizeof(buf), "ФИО: %s | Ключ: \"%s\"\n", volunteers[idx].fio, key);
        operationLog += buf;
        operationLog += "[ХТ] Мягкое удаление (статус → 2)\n"
            "[КЧД] Удаление через макс. левого поддерева\n";

        htVolunteers->Delete(key);
        bstVolunteers->Delete(key, idx);

        for (int i = idx; i < volCount - 1; i++) volunteers[i] = volunteers[i + 1];
        volCount--;
        RebuildAfterDelete();
        return 0;
    }

    int SearchVolunteer(const char* fio, const char* city, int& steps) {
        char key[300];
        snprintf(key, 300, "%s|%s", fio, city);
        int result = htVolunteers->Search(key, steps);

        operationLog = "=== ПОИСК ВОЛОНТЁРА ===\n";
        char buf[512];
        snprintf(buf, sizeof(buf),
            "ФИО: \"%s\" | Город: \"%s\"\nКлюч: \"%s\"\n"
            "[ХТ] Шагов: %d | %s (idx=%d)\n",
            fio, city, key, steps,
            result >= 0 ? "НАЙДЕН" : "НЕ НАЙДЕН", result);
        operationLog += buf;

        int bstSteps = 0;
        int bstResult = bstVolunteers->Search(key, bstSteps);
        snprintf(buf, sizeof(buf), "[КЧД] Шагов: %d | %s\n",
            bstSteps, bstResult >= 0 ? "НАЙДЕН" : "НЕ НАЙДЕН");
        operationLog += buf;
        return result;
    }

    // ══════════════════════════════════════════════
    // CRUD — МЕРОПРИЯТИЯ
    // ══════════════════════════════════════════════

    // 0=OK, 1=полон, 2=волонтёр не найден, 3=дубликат
    int AddEvent(const char* vol_fio, const char* city,
        const char* name, int hours, const char* date)
    {
        if (evCount >= MAX_RECORDS) return 1;

        bool found = false;
        for (int i = 0; i < volCount; i++)
            if (strcmp(volunteers[i].fio, vol_fio) == 0) { found = true; break; }
        if (!found) return 2;

        for (int i = 0; i < evCount; i++)
            if (strcmp(events[i].vol_fio, vol_fio) == 0 &&
                strcmp(events[i].city, city) == 0 &&
                strcmp(events[i].name, name) == 0) return 3;

        int idx = evCount++;
        strncpy_s(events[idx].vol_fio, vol_fio, 99);
        strncpy_s(events[idx].city, city, 99);
        strncpy_s(events[idx].name, name, 199);
        events[idx].hours = hours;
        strncpy_s(events[idx].date, date, 49);

        operationLog = "=== ДОБАВЛЕНИЕ МЕРОПРИЯТИЯ ===\n";
        char buf[256];
        snprintf(buf, sizeof(buf), "Назв.: %s | Волонтёр: %s\n---\n", name, vol_fio);
        operationLog += buf;
        InsertToStructures_Ev(idx, true);
        InsertToStructures_EvDate(idx, true);

        // Авторасширение ХТ
        if (evCount >= (int)(htEvents->GetSize() * 0.8)) {
            int newSize = NextPrime(htEvents->GetSize() * 2);
            RebuildStructures(newSize);
            operationLog += "[ХТ авторасширение] Новый размер: "
                + std::to_string(newSize) + "\n";
        }
        return 0;
    }

    int DeleteEvent(int idx) {
        if (idx < 0 || idx >= evCount) return 1;

        char key[300], dateKey[50];
        MakeKeyEv(events[idx], key, 300);
        MakeKeyEvDate(events[idx], dateKey, 50);

        operationLog = "=== УДАЛЕНИЕ МЕРОПРИЯТИЯ ===\n";
        char buf[256];
        snprintf(buf, sizeof(buf),
            "Назв.: %s\nКлюч ФИО|Город: \"%s\"\nКлюч даты: \"%s\"\n",
            events[idx].name, key, dateKey);
        operationLog += buf;
        operationLog += "[ХТ] Мягкое удаление (статус → 2)\n"
            "[КЧД ФИО|Город] Удаление через макс. левого поддерева\n"
            "[КЧД Дата] Удаление через макс. левого поддерева\n";

        htEvents->Delete(key);
        bstEvents->Delete(key, idx);
        bstEventsByDate->Delete(dateKey, idx);

        for (int i = idx; i < evCount - 1; i++) events[i] = events[i + 1];
        evCount--;
        RebuildAfterDelete();
        return 0;
    }

    int SearchEvent(const char* vol_fio, const char* city, int& steps) {
        char key[300];
        snprintf(key, 300, "%s|%s", vol_fio, city);
        int result = htEvents->Search(key, steps);

        operationLog = "=== ПОИСК МЕРОПРИЯТИЯ ===\n";
        char buf[512];
        snprintf(buf, sizeof(buf),
            "ФИО: \"%s\" | Город: \"%s\"\nКлюч: \"%s\"\n"
            "[ХТ] Шагов: %d | %s (idx=%d)\n",
            vol_fio, city, key, steps,
            result >= 0 ? "НАЙДЕН" : "НЕ НАЙДЕН", result);
        operationLog += buf;

        int bstSteps = 0;
        int bstResult = bstEvents->Search(key, bstSteps);
        snprintf(buf, sizeof(buf), "[КЧД ФИО|Город] Шагов: %d | %s\n",
            bstSteps, bstResult >= 0 ? "НАЙДЕН" : "НЕ НАЙДЕН");
        operationLog += buf;
        return result;
    }

    // ══════════════════════════════════════════════
    // ФАЙЛЫ
    // ══════════════════════════════════════════════

    bool LoadVolunteers(const char* path) {
        std::ifstream f(path);
        if (!f.is_open()) return false;
        volCount = 0;
        htVolunteers->Clear();
        bstVolunteers->Clear();

        std::string line;
        while (std::getline(f, line) && volCount < MAX_RECORDS) {
            if (line.empty()) continue;
            // Убрать \r если есть
            if (!line.empty() && line.back() == '\r') line.pop_back();
            char buf[512]; strncpy_s(buf, line.c_str(), 511);
            char* ctx = nullptr;
            char* fio = strtok_s(buf, ";", &ctx);
            char* city = strtok_s(nullptr, ";", &ctx);
            char* skills = strtok_s(nullptr, ";", &ctx);
            if (!fio || !city || !skills) continue;
            // Trim пробелов
            while (*fio == ' ') fio++;
            while (*city == ' ') city++;
            while (*skills == ' ') skills++;
            int idx = volCount++;
            strncpy_s(volunteers[idx].fio, fio, 99);
            strncpy_s(volunteers[idx].city, city, 99);
            strncpy_s(volunteers[idx].skills, skills, 199);
            InsertToStructures_Vol(idx);
        }
        f.close();

        // Авторасширение при заполнении > 70%
        if (volCount >= (int)(htVolunteers->GetSize() * 0.7)) {
            int newSize = NextPrime(volCount * 2);
            delete htVolunteers; delete bstVolunteers;
            htVolunteers = new HashTable(newSize);
            bstVolunteers = new BST();
            for (int i = 0; i < volCount; i++) InsertToStructures_Vol(i);
        }
        return true;
    }

    bool LoadEvents(const char* path) {
        std::ifstream f(path);
        if (!f.is_open()) return false;
        evCount = 0;
        htEvents->Clear();
        bstEvents->Clear();
        bstEventsByDate->Clear();

        std::string line;
        while (std::getline(f, line) && evCount < MAX_RECORDS) {
            if (line.empty()) continue;
            if (!line.empty() && line.back() == '\r') line.pop_back();
            char buf[512]; strncpy_s(buf, line.c_str(), 511);
            char* ctx = nullptr;
            char* vol_fio = strtok_s(buf, ";", &ctx);
            char* city = strtok_s(nullptr, ";", &ctx);
            char* name = strtok_s(nullptr, ";", &ctx);
            char* hours_s = strtok_s(nullptr, ";", &ctx);
            char* date = strtok_s(nullptr, ";", &ctx);
            if (!vol_fio || !city || !name || !hours_s || !date) continue;
            while (*vol_fio == ' ') vol_fio++;
            while (*city == ' ') city++;
            while (*name == ' ') name++;
            while (*hours_s == ' ') hours_s++;
            while (*date == ' ') date++;
            int idx = evCount++;
            strncpy_s(events[idx].vol_fio, vol_fio, 99);
            strncpy_s(events[idx].city, city, 99);
            strncpy_s(events[idx].name, name, 199);
            events[idx].hours = atoi(hours_s);
            strncpy_s(events[idx].date, date, 49);
            InsertToStructures_Ev(idx);
            InsertToStructures_EvDate(idx);
        }
        f.close();

        if (evCount >= (int)(htEvents->GetSize() * 0.7)) {
            int newSize = NextPrime(evCount * 2);
            delete htEvents; delete bstEvents; delete bstEventsByDate;
            htEvents = new HashTable(newSize);
            bstEvents = new BST();
            bstEventsByDate = new BST();
            for (int i = 0; i < evCount; i++) {
                InsertToStructures_Ev(i);
                InsertToStructures_EvDate(i);
            }
        }
        return true;
    }

    bool SaveVolunteers(const char* path) {
        std::ofstream f(path);
        if (!f.is_open()) return false;
        for (int i = 0; i < volCount; i++)
            f << volunteers[i].fio << ";"
            << volunteers[i].city << ";"
            << volunteers[i].skills << "\n";
        f.close(); return true;
    }

    bool SaveEvents(const char* path) {
        std::ofstream f(path);
        if (!f.is_open()) return false;
        for (int i = 0; i < evCount; i++)
            f << events[i].vol_fio << ";"
            << events[i].city << ";"
            << events[i].name << ";"
            << events[i].hours << ";"
            << events[i].date << "\n";
        f.close(); return true;
    }

private:
    // Следующее простое число >= n
    int NextPrime(int n) {
        if (n < 3) return 3;
        int c = (n % 2 == 0) ? n + 1 : n;
        for (;; c += 2) {
            bool ok = true;
            for (int j = 3; j * j <= c; j += 2)
                if (c % j == 0) { ok = false; break; }
            if (ok) return c;
        }
    }

    // Пересобрать все СД после удаления (индексы сдвинулись)
    void RebuildAfterDelete() {
        int sz = htVolunteers->GetSize();
        delete htVolunteers;  delete htEvents;
        delete bstVolunteers; delete bstEvents; delete bstEventsByDate;

        htVolunteers = new HashTable(sz);
        htEvents = new HashTable(sz);
        bstVolunteers = new BST();
        bstEvents = new BST();
        bstEventsByDate = new BST();

        for (int i = 0; i < volCount; i++) InsertToStructures_Vol(i);
        for (int i = 0; i < evCount; i++) {
            InsertToStructures_Ev(i);
            InsertToStructures_EvDate(i);
        }
    }
};