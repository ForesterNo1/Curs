#pragma once
#include <string>

// ── Волонтёр ──────────────────────────────────────
struct Volunteer {
    char fio[100];
    char city[100];
    char skills[200];
};

// ── Мероприятие ───────────────────────────────────
struct Event {
    char vol_fio[100];
    char city[100];
    char name[200];
    int  hours;
    char date[50];   // формат: DD январь YYYY
};
