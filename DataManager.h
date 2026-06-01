#pragma once
#include "Structs.h"
#include "HashTable.h"
#include "BST.h"
#include <fstream>
#include <sstream>
#include <cstring>

#define MAX_RECORDS 1000

class DataManager {
public:
    // ── Массивы данных ────────────────────────────
    Volunteer volunteers[MAX_RECORDS];
    Event     events[MAX_RECORDS];
    int       volCount;
    int       evCount;

    // ── Структуры данных ──────────────────────────
    HashTable* htVolunteers;   // ключ: ФИО+Город
    HashTable* htEvents;       // ключ: ФИО волонтёра+Город
    BST* bstVolunteers;  // ключ: ФИО+Город
    BST* bstEvents;      // ключ: ФИО волонтёра+Город
    std::string operationLog;

    // ── Конструктор ───────────────────────────────
    DataManager(int htSize = 17)
        : volCount(0), evCount(0)
    {
        htVolunteers = new HashTable(htSize);
        htEvents = new HashTable(htSize);
        bstVolunteers = new BST();
        bstEvents = new BST();
    }

    ~DataManager() {
        delete htVolunteers;
        delete htEvents;
        delete bstVolunteers;
        delete bstEvents;
    }

    // ── Пересобрать СД заново (при изменении размера ХТ) ──
    void RebuildStructures(int newHtSize) {
        delete htVolunteers;
        delete htEvents;
        delete bstVolunteers;
        delete bstEvents;

        htVolunteers = new HashTable(newHtSize);
        htEvents = new HashTable(newHtSize);
        bstVolunteers = new BST();
        bstEvents = new BST();

        for (int i = 0; i < volCount; i++)
            InsertToStructures_Vol(i);
        for (int i = 0; i < evCount; i++)
            InsertToStructures_Ev(i);
    }

    // ── Составной ключ поиска ─────────────────────
    // Волонтёр: "ФИО|Город"
    void MakeKeyVol(const Volunteer& v, char* out, int outSize) {
        snprintf(out, outSize, "%s|%s", v.fio, v.city);
    }
    // Мероприятие: "ФИО волонтёра|Город"
    void MakeKeyEv(const Event& e, char* out, int outSize) {
        snprintf(out, outSize, "%s|%s", e.vol_fio, e.city);
    }

    // ── Вставка в СД ──────────────────────────────
    void InsertToStructures_Vol(int idx, bool log = false) {
        char key[300];
        MakeKeyVol(volunteers[idx], key, 300);
        HTInsertInfo info = htVolunteers->InsertEx(key, idx);
        bstVolunteers->Insert(key, idx);
        if (log) {
            char buf[512];
            snprintf(buf, sizeof(buf),
                "[ХТ Волонтёры] Вставка: \"%s\"\n"
                "  Первичный хеш H1 = %d\n"
                "  Шагов зондирования: %d\n"
                "  Факт. слот: %d\n",
                key,
                info.primaryHash,
                info.steps,
                (info.primaryHash + (info.steps - 1) * 3) % htVolunteers->GetSize()
            );
            operationLog += buf;
            snprintf(buf, sizeof(buf),
                "[КЧД Волонтёры] Вставка ключа: \"%s\"\n", key);
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
                "  Первичный хеш H1 = %d\n"
                "  Шагов зондирования: %d\n"
                "  Факт. слот: %d\n",
                key,
                info.primaryHash,
                info.steps,
                (info.primaryHash + (info.steps - 1) * 3) % htEvents->GetSize()
            );
            operationLog += buf;
            snprintf(buf, sizeof(buf),
                "[КЧД Мероприятия] Вставка ключа: \"%s\"\n", key);
            operationLog += buf;
        }
    }

    // ════════════════════════════════════════════
    // CRUD — ВОЛОНТЁРЫ
    // ════════════════════════════════════════════

    // Добавить волонтёра
    // Возвращает: 0=ок, 1=массив полон, 2=дубликат
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
        snprintf(buf, sizeof(buf), "ФИО: %s | Город: %s\n", fio, city);
        operationLog += buf;
        operationLog += "---\n";
        InsertToStructures_Vol(idx, true);
        return 0;
    }

    // Удалить волонтёра по индексу
    // Возвращает: 0=ок, 1=не найден, 2=есть связанные мероприятия
    int DeleteVolunteer(int idx) {
        if (idx < 0 || idx >= volCount) return 1;
        for (int i = 0; i < evCount; i++)
            if (strcmp(events[i].vol_fio, volunteers[idx].fio) == 0)
                return 2;

        char key[300];
        MakeKeyVol(volunteers[idx], key, 300);

        operationLog = "=== УДАЛЕНИЕ ВОЛОНТЁРА ===\n";
        char buf[256];
        snprintf(buf, sizeof(buf), "ФИО: %s | Ключ: \"%s\"\n",
            volunteers[idx].fio, key);
        operationLog += buf;
        operationLog += "[ХТ] Мягкое удаление (статус -> 2/DELETED)\n";
        operationLog += "[КЧД] Удаление через макс. левого поддерева\n";

        htVolunteers->Delete(key);
        bstVolunteers->Delete(key, idx);

        for (int i = idx; i < volCount - 1; i++)
            volunteers[i] = volunteers[i + 1];
        volCount--;
        RebuildAfterDelete();
        return 0;
    }

    // Поиск волонтёра по ФИО + Город
    // Возвращает индекс в массиве, steps = кол-во шагов
    int SearchVolunteer(const char* fio, const char* city, int& steps) {
        char key[300];
        snprintf(key, 300, "%s|%s", fio, city);
        int h0 = 0;
        int result = htVolunteers->Search(key, steps);

        operationLog = "=== ПОИСК ВОЛОНТЁРА ===\n";
        char buf[512];
        snprintf(buf, sizeof(buf),
            "Запрос: ФИО=\"%s\" Город=\"%s\"\n"
            "Ключ: \"%s\"\n"
            "[ХТ] Шагов зондирования: %d\n"
            "[ХТ] Результат: %s (индекс %d)\n",
            fio, city, key, steps,
            result >= 0 ? "НАЙДЕН" : "НЕ НАЙДЕН", result);
        operationLog += buf;

        // Поиск в КЧД
        int bstSteps = 0;
        int bstResult = bstVolunteers->Search(key, bstSteps);
        snprintf(buf, sizeof(buf),
            "[КЧД] Шагов: %d | Результат: %s\n",
            bstSteps, bstResult >= 0 ? "НАЙДЕН" : "НЕ НАЙДЕН");
        operationLog += buf;

        return result;
    }

    // ════════════════════════════════════════════
    // CRUD — МЕРОПРИЯТИЯ
    // ════════════════════════════════════════════

    // Добавить мероприятие
    // Возвращает: 0=ок, 1=массив полон, 2=волонтёр не найден, 3=дубликат
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
                strcmp(events[i].name, name) == 0)
                return 3;

        int idx = evCount++;
        strncpy_s(events[idx].vol_fio, vol_fio, 99);
        strncpy_s(events[idx].city, city, 99);
        strncpy_s(events[idx].name, name, 199);
        events[idx].hours = hours;
        strncpy_s(events[idx].date, date, 49);

        operationLog = "=== ДОБАВЛЕНИЕ МЕРОПРИЯТИЯ ===\n";
        char buf[256];
        snprintf(buf, sizeof(buf), "Название: %s | Волонтёр: %s\n", name, vol_fio);
        operationLog += buf;
        operationLog += "---\n";
        InsertToStructures_Ev(idx, true);
        return 0;
    }

    // Удалить мероприятие по индексу
    int DeleteEvent(int idx) {
        if (idx < 0 || idx >= evCount) return 1;

        char key[300];
        MakeKeyEv(events[idx], key, 300);

        operationLog = "=== УДАЛЕНИЕ МЕРОПРИЯТИЯ ===\n";
        char buf[256];
        snprintf(buf, sizeof(buf), "Название: %s | Ключ: \"%s\"\n",
            events[idx].name, key);
        operationLog += buf;
        operationLog += "[ХТ] Мягкое удаление (статус -> 2/DELETED)\n";
        operationLog += "[КЧД] Удаление через макс. левого поддерева\n";

        htEvents->Delete(key);
        bstEvents->Delete(key, idx);

        for (int i = idx; i < evCount - 1; i++)
            events[i] = events[i + 1];
        evCount--;
        RebuildAfterDelete();
        return 0;
    }

    // Поиск мероприятия по ФИО волонтёра + Город
    

    int SearchEvent(const char* vol_fio, const char* city, int& steps) {
        char key[300];
        snprintf(key, 300, "%s|%s", vol_fio, city);
        int result = htEvents->Search(key, steps);

        operationLog = "=== ПОИСК МЕРОПРИЯТИЯ ===\n";
        char buf[512];
        snprintf(buf, sizeof(buf),
            "Запрос: ФИО=\"%s\" Город=\"%s\"\n"
            "Ключ: \"%s\"\n"
            "[ХТ] Шагов зондирования: %d\n"
            "[ХТ] Результат: %s (индекс %d)\n",
            vol_fio, city, key, steps,
            result >= 0 ? "НАЙДЕН" : "НЕ НАЙДЕН", result);
        operationLog += buf;

        int bstSteps = 0;
        int bstResult = bstEvents->Search(key, bstSteps);
        snprintf(buf, sizeof(buf),
            "[КЧД] Шагов: %d | Результат: %s\n",
            bstSteps, bstResult >= 0 ? "НАЙДЕН" : "НЕ НАЙДЕН");
        operationLog += buf;

        return result;
    }

    // ════════════════════════════════════════════
    // ФАЙЛЫ
    // ════════════════════════════════════════════

    // Загрузить волонтёров из файла
    // Формат строки (будет уточнён): ФИО;Город;Навыки
    bool LoadVolunteers(const char* path) {
        std::ifstream f(path);
        if (!f.is_open()) return false;

        // Очищаем
        volCount = 0;
        htVolunteers->Clear();
        bstVolunteers->Clear();

        std::string line;
        while (std::getline(f, line) && volCount < MAX_RECORDS) {
            if (line.empty()) continue;
            char buf[512];
            strncpy_s(buf, line.c_str(), 511);

            char* ctx = nullptr;
            char* fio = strtok_s(buf, ";", &ctx);
            char* city = strtok_s(nullptr, ";", &ctx);
            char* skills = strtok_s(nullptr, ";", &ctx);

            if (!fio || !city || !skills) continue;

            int idx = volCount++;
            strncpy_s(volunteers[idx].fio, fio, 99);
            strncpy_s(volunteers[idx].city, city, 99);
            strncpy_s(volunteers[idx].skills, skills, 199);
            InsertToStructures_Vol(idx);
        }
        f.close();
        return true;
    }

    // Загрузить мероприятия из файла
    // Формат строки: ФИО волонтёра;Город;Название;Часы;Дата
    bool LoadEvents(const char* path) {
        std::ifstream f(path);
        if (!f.is_open()) return false;

        evCount = 0;
        htEvents->Clear();
        bstEvents->Clear();

        std::string line;
        while (std::getline(f, line) && evCount < MAX_RECORDS) {
            if (line.empty()) continue;
            char buf[512];
            strncpy_s(buf, line.c_str(), 511);

            char* ctx = nullptr;
            char* vol_fio = strtok_s(buf, ";", &ctx);
            char* city = strtok_s(nullptr, ";", &ctx);
            char* name = strtok_s(nullptr, ";", &ctx);
            char* hours_s = strtok_s(nullptr, ";", &ctx);
            char* date = strtok_s(nullptr, ";", &ctx);

            if (!vol_fio || !city || !name || !hours_s || !date) continue;

            int idx = evCount++;
            strncpy_s(events[idx].vol_fio, vol_fio, 99);
            strncpy_s(events[idx].city, city, 99);
            strncpy_s(events[idx].name, name, 199);
            events[idx].hours = atoi(hours_s);
            strncpy_s(events[idx].date, date, 49);
            InsertToStructures_Ev(idx);
        }
        f.close();
        return true;
    }

    // Сохранить волонтёров в файл
    bool SaveVolunteers(const char* path) {
        std::ofstream f(path);
        if (!f.is_open()) return false;
        for (int i = 0; i < volCount; i++) {
            f << volunteers[i].fio << ";"
                << volunteers[i].city << ";"
                << volunteers[i].skills << "\n";
        }
        f.close();
        return true;
    }

    // Сохранить мероприятия в файл
    bool SaveEvents(const char* path) {
        std::ofstream f(path);
        if (!f.is_open()) return false;
        for (int i = 0; i < evCount; i++) {
            f << events[i].vol_fio << ";"
                << events[i].city << ";"
                << events[i].name << ";"
                << events[i].hours << ";"
                << events[i].date << "\n";
        }
        f.close();
        return true;
    }

private:
    // Пересобрать только ХТ и КЧД после удаления
    // (индексы в массиве сдвинулись — надо обновить)
    void RebuildAfterDelete() {
        int htSize = htVolunteers->GetSize();
        delete htVolunteers;
        delete htEvents;
        delete bstVolunteers;
        delete bstEvents;

        htVolunteers = new HashTable(htSize);
        htEvents = new HashTable(htSize);
        bstVolunteers = new BST();
        bstEvents = new BST();

        for (int i = 0; i < volCount; i++)
            InsertToStructures_Vol(i);
        for (int i = 0; i < evCount; i++)
            InsertToStructures_Ev(i);
    }
};