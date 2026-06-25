#pragma once
#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

#include "DataManager.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;

static std::string ToStd(String^ s) {
    const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
    std::string result(chars);
    Marshal::FreeHGlobal(IntPtr((void*)chars));
    return result;
}

// ═══════════════════════════════════════════════════
// ДИАЛОГ: Добавить волонтёра
// ═══════════════════════════════════════════════════
ref class AddVolunteerForm : public Form {
public:
    TextBox^ tbFio;
    TextBox^ tbCity;
    TextBox^ tbSkills;

    AddVolunteerForm() {
        this->Text = L"Добавить волонтёра";
        this->Size = System::Drawing::Size(440, 240);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->StartPosition = FormStartPosition::CenterParent;
        this->MaximizeBox = false; this->MinimizeBox = false;

        Label^ l1 = gcnew Label(); l1->Text = L"ФИО:";    l1->Location = Point(10, 15); l1->Width = 90;
        Label^ l2 = gcnew Label(); l2->Text = L"Город:";  l2->Location = Point(10, 55); l2->Width = 90;
        Label^ l3 = gcnew Label(); l3->Text = L"Навыки:"; l3->Location = Point(10, 95); l3->Width = 90;

        tbFio = gcnew TextBox(); tbFio->Location = Point(105, 12); tbFio->Width = 305;
        tbCity = gcnew TextBox(); tbCity->Location = Point(105, 52); tbCity->Width = 305;
        tbSkills = gcnew TextBox(); tbSkills->Location = Point(105, 92); tbSkills->Width = 305;

        Label^ hint = gcnew Label();
        hint->Text = L"Поля не должны содержать символ «;»";
        hint->Location = Point(105, 118); hint->Width = 305;
        hint->ForeColor = System::Drawing::Color::Gray;

        Button^ btnOk = gcnew Button(); btnOk->Text = L"Добавить";
        btnOk->Location = Point(105, 148); btnOk->Width = 120;
        btnOk->Click += gcnew EventHandler(this, &AddVolunteerForm::OnOk);

        Button^ btnCancel = gcnew Button(); btnCancel->Text = L"Отмена";
        btnCancel->Location = Point(235, 148); btnCancel->Width = 80;
        btnCancel->Click += gcnew EventHandler(this, &AddVolunteerForm::OnCancel);

        this->Controls->Add(l1); this->Controls->Add(tbFio);
        this->Controls->Add(l2); this->Controls->Add(tbCity);
        this->Controls->Add(l3); this->Controls->Add(tbSkills);
        this->Controls->Add(hint);
        this->Controls->Add(btnOk); this->Controls->Add(btnCancel);
    }
private:
    void OnOk(Object^ s, EventArgs^ e) {
        if (tbFio->Text->Trim()->Length == 0 || tbCity->Text->Trim()->Length == 0) {
            MessageBox::Show(L"Поля «ФИО» и «Город» обязательны для заполнения!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning); return;
        }
        if (tbFio->Text->Contains(";") || tbCity->Text->Contains(";") || tbSkills->Text->Contains(";")) {
            MessageBox::Show(L"Поля не должны содержать символ «;»!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning); return;
        }
        this->DialogResult = System::Windows::Forms::DialogResult::OK;
    }
    void OnCancel(Object^ s, EventArgs^ e) {
        this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
    }
};

// ═══════════════════════════════════════════════════
// ДИАЛОГ: Добавить мероприятие
// ═══════════════════════════════════════════════════
ref class AddEventForm : public Form {
public:
    TextBox^ tbFio;
    TextBox^ tbCity;
    TextBox^ tbName;
    TextBox^ tbHours;
    TextBox^ tbDate;

    AddEventForm() {
        this->Text = L"Добавить мероприятие";
        this->Size = System::Drawing::Size(440, 320);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->StartPosition = FormStartPosition::CenterParent;
        this->MaximizeBox = false; this->MinimizeBox = false;

        Label^ l1 = gcnew Label(); l1->Text = L"ФИО волонтёра:";
        l1->Location = Point(10, 12); l1->Width = 130;
        Label^ l2 = gcnew Label(); l2->Text = L"Город:";
        l2->Location = Point(10, 52); l2->Width = 130;
        Label^ l3 = gcnew Label(); l3->Text = L"Название:";
        l3->Location = Point(10, 92); l3->Width = 130;
        Label^ l4 = gcnew Label(); l4->Text = L"Часы (1–24):";
        l4->Location = Point(10, 132); l4->Width = 130;
        Label^ l5 = gcnew Label(); l5->Text = L"Дата:";
        l5->Location = Point(10, 172); l5->Width = 130;

        tbFio = gcnew TextBox(); tbFio->Location = Point(145, 12);  tbFio->Width = 270;
        tbCity = gcnew TextBox(); tbCity->Location = Point(145, 52);  tbCity->Width = 270;
        tbName = gcnew TextBox(); tbName->Location = Point(145, 92);  tbName->Width = 270;
        tbHours = gcnew TextBox(); tbHours->Location = Point(145, 132); tbHours->Width = 270;
        tbDate = gcnew TextBox(); tbDate->Location = Point(145, 172); tbDate->Width = 270;

        Label^ hint = gcnew Label();
        hint->Text = L"Пример даты: 15 январь 2024";
        hint->Location = Point(145, 197); hint->Width = 270;
        hint->ForeColor = System::Drawing::Color::Gray;

        Button^ btnOk = gcnew Button(); btnOk->Text = L"Добавить";
        btnOk->Location = Point(145, 228); btnOk->Width = 120;
        btnOk->Click += gcnew EventHandler(this, &AddEventForm::OnOk);

        Button^ btnCancel = gcnew Button(); btnCancel->Text = L"Отмена";
        btnCancel->Location = Point(275, 228); btnCancel->Width = 80;
        btnCancel->Click += gcnew EventHandler(this, &AddEventForm::OnCancel);

        this->Controls->Add(l1); this->Controls->Add(tbFio);
        this->Controls->Add(l2); this->Controls->Add(tbCity);
        this->Controls->Add(l3); this->Controls->Add(tbName);
        this->Controls->Add(l4); this->Controls->Add(tbHours);
        this->Controls->Add(l5); this->Controls->Add(tbDate);
        this->Controls->Add(hint);
        this->Controls->Add(btnOk); this->Controls->Add(btnCancel);
    }
private:
    void OnOk(Object^ s, EventArgs^ e) {
        if (tbFio->Text->Trim()->Length == 0 || tbCity->Text->Trim()->Length == 0 ||
            tbName->Text->Trim()->Length == 0) {
            MessageBox::Show(L"Поля «ФИО», «Город» и «Название» обязательны!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning); return;
        }
        if (tbDate->Text->Trim()->Length == 0) {
            MessageBox::Show(L"Поле «Дата» обязательно!\nПример: 15 январь 2024", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning); return;
        }
        if (tbFio->Text->Contains(";") || tbCity->Text->Contains(";") ||
            tbName->Text->Contains(";") || tbDate->Text->Contains(";")) {
            MessageBox::Show(L"Поля не должны содержать символ «;»!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning); return;
        }
        int h = 0;
        try { h = int::Parse(tbHours->Text->Trim()); }
        catch (...) {
            MessageBox::Show(L"«Часы» должны быть целым числом!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning); return;
        }
        if (h <= 0 || h > 24) {
            MessageBox::Show(L"«Часы» должны быть в диапазоне от 1 до 24!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning); return;
        }
        this->DialogResult = System::Windows::Forms::DialogResult::OK;
    }
    void OnCancel(Object^ s, EventArgs^ e) {
        this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
    }
};

// ═══════════════════════════════════════════════════
// ДИАЛОГ: Поиск
// ═══════════════════════════════════════════════════
ref class SearchForm : public Form {
public:
    TextBox^ tbFio;
    TextBox^ tbCity;

    SearchForm() {
        this->Text = L"Поиск по ФИО + Город";
        this->Size = System::Drawing::Size(390, 200);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->StartPosition = FormStartPosition::CenterParent;
        this->MaximizeBox = false; this->MinimizeBox = false;

        Label^ hint = gcnew Label();
        hint->Text = L"Можно заполнить одно или оба поля.";
        hint->Location = Point(10, 8); hint->Width = 355;
        hint->ForeColor = System::Drawing::Color::Gray;

        Label^ l1 = gcnew Label(); l1->Text = L"ФИО:";   l1->Location = Point(10, 33); l1->Width = 75;
        Label^ l2 = gcnew Label(); l2->Text = L"Город:"; l2->Location = Point(10, 70); l2->Width = 75;

        tbFio = gcnew TextBox(); tbFio->Location = Point(90, 30); tbFio->Width = 270;
        tbCity = gcnew TextBox(); tbCity->Location = Point(90, 67); tbCity->Width = 270;

        Button^ btnOk = gcnew Button(); btnOk->Text = L"Найти";
        btnOk->Location = Point(90, 110); btnOk->Width = 100;
        btnOk->Click += gcnew EventHandler(this, &SearchForm::OnOk);

        Button^ btnCancel = gcnew Button(); btnCancel->Text = L"Отмена";
        btnCancel->Location = Point(200, 110); btnCancel->Width = 80;
        btnCancel->Click += gcnew EventHandler(this, &SearchForm::OnCancel);

        this->Controls->Add(hint);
        this->Controls->Add(l1); this->Controls->Add(tbFio);
        this->Controls->Add(l2); this->Controls->Add(tbCity);
        this->Controls->Add(btnOk); this->Controls->Add(btnCancel);
    }
private:
    void OnOk(Object^ s, EventArgs^ e) {
        this->DialogResult = System::Windows::Forms::DialogResult::OK;
    }
    void OnCancel(Object^ s, EventArgs^ e) {
        this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
    }
};

// ═══════════════════════════════════════════════════
// ДИАЛОГ: Фильтры
// ═══════════════════════════════════════════════════
ref class FilterForm : public Form {
public:
    TextBox^ tbSkills;
    TextBox^ tbCity;
    TextBox^ tbYearFrom;
    TextBox^ tbYearTo;
    bool resetPressed;

    FilterForm(String^ curSkills, String^ curCity, String^ curFrom, String^ curTo) {
        resetPressed = false;
        this->Text = L"Фильтры (применяются к таблицам и отчёту)";
        this->Size = System::Drawing::Size(430, 310);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->StartPosition = FormStartPosition::CenterParent;
        this->MaximizeBox = false; this->MinimizeBox = false;

        Label^ lS = gcnew Label(); lS->Text = L"Навыки (Спр.1):";
        lS->Location = Point(10, 15); lS->Width = 140;
        tbSkills = gcnew TextBox(); tbSkills->Location = Point(155, 12); tbSkills->Width = 245; tbSkills->Text = curSkills;

        Label^ lC = gcnew Label(); lC->Text = L"Город (Спр.2):";
        lC->Location = Point(10, 52); lC->Width = 140;
        tbCity = gcnew TextBox(); tbCity->Location = Point(155, 49); tbCity->Width = 245; tbCity->Text = curCity;

        Label^ lP = gcnew Label(); lP->Text = L"Период (год, Спр.2):";
        lP->Location = Point(10, 90); lP->Width = 140;

        Label^ lF = gcnew Label(); lF->Text = L"от:"; lF->Location = Point(10, 125); lF->Width = 30;
        tbYearFrom = gcnew TextBox(); tbYearFrom->Location = Point(45, 122); tbYearFrom->Width = 70; tbYearFrom->Text = curFrom;

        Label^ lT = gcnew Label(); lT->Text = L"до:"; lT->Location = Point(125, 125); lT->Width = 30;
        tbYearTo = gcnew TextBox(); tbYearTo->Location = Point(160, 122); tbYearTo->Width = 70; tbYearTo->Text = curTo;

        Label^ hint = gcnew Label();
        hint->Text = L"Пустое поле = фильтр по этому критерию не применяется.";
        hint->Location = Point(10, 158); hint->Width = 390;
        hint->ForeColor = System::Drawing::Color::Gray;

        Button^ btnApply = gcnew Button(); btnApply->Text = L"Применить";
        btnApply->Location = Point(10, 190); btnApply->Width = 110;
        btnApply->Click += gcnew EventHandler(this, &FilterForm::OnApply);

        Button^ btnReset = gcnew Button(); btnReset->Text = L"Сбросить всё";
        btnReset->Location = Point(130, 190); btnReset->Width = 110;
        btnReset->Click += gcnew EventHandler(this, &FilterForm::OnReset);

        Button^ btnClose = gcnew Button(); btnClose->Text = L"Закрыть";
        btnClose->Location = Point(250, 190); btnClose->Width = 80;
        btnClose->Click += gcnew EventHandler(this, &FilterForm::OnClose);

        this->Controls->Add(lS); this->Controls->Add(tbSkills);
        this->Controls->Add(lC); this->Controls->Add(tbCity);
        this->Controls->Add(lP);
        this->Controls->Add(lF); this->Controls->Add(tbYearFrom);
        this->Controls->Add(lT); this->Controls->Add(tbYearTo);
        this->Controls->Add(hint);
        this->Controls->Add(btnApply); this->Controls->Add(btnReset); this->Controls->Add(btnClose);
    }
private:
    void OnApply(Object^ s, EventArgs^ e) {
        int yf = 0, yt = 9999;
        bool yfOk = true, ytOk = true;
        if (tbYearFrom->Text->Trim()->Length > 0) {
            try { yf = int::Parse(tbYearFrom->Text->Trim()); }
            catch (...) { yfOk = false; }
            if (yfOk && yf < 1900) yfOk = false;
        }
        if (tbYearTo->Text->Trim()->Length > 0) {
            try { yt = int::Parse(tbYearTo->Text->Trim()); }
            catch (...) { ytOk = false; }
            if (ytOk && yt > 2200) ytOk = false;
        }
        if (!yfOk) {
            MessageBox::Show(L"«Год от» должен быть целым числом в диапазоне 1900–2200!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning); return;
        }
        if (!ytOk) {
            MessageBox::Show(L"«Год до» должен быть целым числом в диапазоне 1900–2200!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning); return;
        }
        if (tbYearFrom->Text->Trim()->Length > 0 && tbYearTo->Text->Trim()->Length > 0 && yf > yt) {
            MessageBox::Show(L"«Год от» не может быть больше «Год до»!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning); return;
        }
        resetPressed = false;
        this->DialogResult = System::Windows::Forms::DialogResult::OK;
    }
    void OnReset(Object^ s, EventArgs^ e) {
        resetPressed = true;
        this->DialogResult = System::Windows::Forms::DialogResult::OK;
    }
    void OnClose(Object^ s, EventArgs^ e) {
        this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
    }
};

// ═══════════════════════════════════════════════════
// ДИАЛОГ: Размер ХТ
// ═══════════════════════════════════════════════════
ref class HtSizeForm : public Form {
public:
    TextBox^ tbSize;

    HtSizeForm(int current) {
        this->Text = L"Задать размер хеш-таблицы";
        this->Size = System::Drawing::Size(360, 170);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->StartPosition = FormStartPosition::CenterParent;
        this->MaximizeBox = false; this->MinimizeBox = false;

        Label^ lbl = gcnew Label();
        lbl->Text = L"Новый размер ХТ (целое число > кол-ва записей):";
        lbl->Location = Point(10, 12); lbl->Width = 330;

        tbSize = gcnew TextBox(); tbSize->Location = Point(10, 42); tbSize->Width = 100;
        tbSize->Text = gcnew String(std::to_string(current).c_str());

        Label^ hint = gcnew Label();
        hint->Text = L"Текущий размер: " + gcnew String(std::to_string(current).c_str());
        hint->Location = Point(120, 45); hint->Width = 220;
        hint->ForeColor = System::Drawing::Color::Gray;

        Button^ btnOk = gcnew Button(); btnOk->Text = L"Применить";
        btnOk->Location = Point(10, 78); btnOk->Width = 100;
        btnOk->Click += gcnew EventHandler(this, &HtSizeForm::OnOk);

        Button^ btnCancel = gcnew Button(); btnCancel->Text = L"Отмена";
        btnCancel->Location = Point(120, 78); btnCancel->Width = 80;
        btnCancel->Click += gcnew EventHandler(this, &HtSizeForm::OnCancel);

        this->Controls->Add(lbl); this->Controls->Add(tbSize); this->Controls->Add(hint);
        this->Controls->Add(btnOk); this->Controls->Add(btnCancel);
    }
private:
    void OnOk(Object^ s, EventArgs^ e) {
        int sz = 0;
        try { sz = int::Parse(tbSize->Text->Trim()); }
        catch (...) {
            MessageBox::Show(L"Введите целое число!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning); return;
        }
        if (sz <= 0) {
            MessageBox::Show(L"Размер должен быть положительным числом!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning); return;
        }
        this->DialogResult = System::Windows::Forms::DialogResult::OK;
    }
    void OnCancel(Object^ s, EventArgs^ e) {
        this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
    }
};

// ═══════════════════════════════════════════════════
// ГЛАВНАЯ ФОРМА
// ═══════════════════════════════════════════════════
namespace BureauOfGoodDeeds {

    public ref class MainForm : public Form {
    public:
        MainForm(void) {
            InitializeComponent();
            dm = new DataManager(17);

            // Состояние фильтров
            filterActive = false;
            filterSkills = "";
            filterCity = "";
            filterYearFrom = 0;
            filterYearTo = 9999;

            // Начальное состояние СД ещё не захвачено
            initialStateCaptured = false;

            AutoLoadFromFiles();
            RefreshGrids();
            RefreshCurrentSD();
            UpdateFilterStatus();
        }

    protected:
        ~MainForm() {
            if (components) delete components;
            if (dm) delete dm;
        }

    private:
        System::ComponentModel::Container^ components;
        DataManager* dm;

        // ── Состояние фильтров ─────────────────────────
        bool    filterActive;
        String^ filterSkills;
        String^ filterCity;
        int     filterYearFrom;
        int     filterYearTo;

        // ── Начальное состояние СД ─────────────────────
        bool    initialStateCaptured;

        // ── Контролы ──────────────────────────────────
        ToolStrip^ toolStrip;
        TabControl^ tabMain;
        TabPage^ tabVolunteers;
        TabPage^ tabEvents;
        TabPage^ tabInitialSD;
        TabPage^ tabCurrentSD;

        DataGridView^ gridVolunteers;
        DataGridView^ gridEvents;

        // Начальные СД
        SplitContainer^ splitInitial;
        Panel^ panelIHT;
        Panel^ panelIBST;
        Label^ lblIHT;
        Label^ lblIBST;
        RichTextBox^ rtbInitialHT;
        RichTextBox^ rtbInitialBST;

        // Текущие СД
        SplitContainer^ splitCurrent;
        Panel^ panelCHT;
        Panel^ panelCBST;
        Label^ lblCHT;
        Label^ lblCBST;
        RichTextBox^ rtbCurrentHT;
        RichTextBox^ rtbCurrentBST;

        // Кнопки тулбара
        ToolStripButton^ btnLoad;
        ToolStripButton^ btnSave;
        ToolStripButton^ btnAdd;
        ToolStripButton^ btnDelete;
        ToolStripButton^ btnSearch;
        ToolStripButton^ btnFilter;
        ToolStripButton^ btnResetFilter;
        ToolStripButton^ btnReport;
        ToolStripButton^ btnHtSize;
        ToolStripLabel^ lblFilterStatus;

        // ── Вспомогательная: кнопка тулбара ───────────
        ToolStripButton^ MakeBtn(String^ text, String^ tip) {
            ToolStripButton^ btn = gcnew ToolStripButton(text);
            btn->DisplayStyle = ToolStripItemDisplayStyle::Text;
            btn->ToolTipText = tip;
            btn->AutoSize = true;
            return btn;
        }

        // ── Обновить статус фильтра ────────────────────
        void UpdateFilterStatus() {
            if (filterActive) {
                String^ s = L"Фильтр: ";
                if (filterSkills->Length > 0) s += L"Навыки=\"" + filterSkills + L"\" ";
                if (filterCity->Length > 0) s += L"Город=\"" + filterCity + L"\" ";
                if (filterYearFrom > 0)        s += L"от " + gcnew String(std::to_string(filterYearFrom).c_str()) + L" ";
                if (filterYearTo < 9999)      s += L"до " + gcnew String(std::to_string(filterYearTo).c_str());
                lblFilterStatus->Text = s;
                lblFilterStatus->ForeColor = System::Drawing::Color::DarkOrange;
                btnResetFilter->Enabled = true;
            }
            else {
                lblFilterStatus->Text = L"Фильтр: не задан";
                lblFilterStatus->ForeColor = System::Drawing::Color::Gray;
                btnResetFilter->Enabled = false;
            }
        }

        // ── Автозагрузка из файлов ─────────────────────
        void AutoLoadFromFiles() {
            bool volOk = dm->LoadVolunteers("volunteers.txt");
            bool evOk = dm->LoadEvents("events.txt");

            if (volOk || evOk) {
                std::string log = "=== АВТОЗАГРУЗКА ===\n";
                log += volOk
                    ? "volunteers.txt -> " + std::to_string(dm->volCount) + " записей\n"
                    : "volunteers.txt -> не найден\n";
                log += evOk
                    ? "events.txt -> " + std::to_string(dm->evCount) + " записей\n"
                    : "events.txt -> не найден\n";
                dm->operationLog = log;
                if (!initialStateCaptured) CaptureInitialState();
            }
            else {
                dm->operationLog = "=== ФАЙЛЫ НЕ НАЙДЕНЫ ===\nЗагрузите данные через «Загрузить».\n";
                MessageBox::Show(
                    L"Файлы volunteers.txt и events.txt не найдены.\n\n"
                    L"Положите их рядом с .vcxproj\nили загрузите вручную через кнопку «Загрузить».",
                    L"Автозагрузка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }

        // ── Захватить начальное состояние СД (один раз) ─
        void CaptureInitialState() {
            std::string htOut = "=== ХТ Волонтёры (начальная) ===\n";
            htOut += dm->htVolunteers->Print();
            htOut += "\n=== ХТ Мероприятия (начальная) ===\n";
            htOut += dm->htEvents->Print();
            rtbInitialHT->Text = gcnew String(htOut.c_str());

            std::string bstOut = "=== КЧД Волонтёры по ФИО|Город (начальное) ===\n";
            bstOut += dm->bstVolunteers->Print();
            bstOut += "\n=== КЧД Мероприятия по ФИО|Город (начальное) ===\n";
            bstOut += dm->bstEvents->Print();
            bstOut += "\n=== КЧД Мероприятия по Дате (начальное) ===\n";
            bstOut += "Легенда ключа: ГГГГММДД (напр. 20240115 = 15 январь 2024)\n";
            bstOut += std::string(40, '-') + "\n";
            bstOut += dm->bstEventsByDate->Print();
            rtbInitialBST->Text = gcnew String(bstOut.c_str());

            initialStateCaptured = true;
        }

        // ── Обновить таблицы справочников ─────────────
        void RefreshGrids() {
            gridVolunteers->Rows->Clear();
            for (int i = 0; i < dm->volCount; i++) {
                gridVolunteers->Rows->Add(
                    gcnew String(dm->volunteers[i].fio),
                    gcnew String(dm->volunteers[i].city),
                    gcnew String(dm->volunteers[i].skills));
            }
            gridEvents->Rows->Clear();
            for (int i = 0; i < dm->evCount; i++) {
                char buf[20]; snprintf(buf, 20, "%d", dm->events[i].hours);
                gridEvents->Rows->Add(
                    gcnew String(dm->events[i].vol_fio),
                    gcnew String(dm->events[i].city),
                    gcnew String(dm->events[i].name),
                    gcnew String(buf),
                    gcnew String(dm->events[i].date));
            }
        }

        // ── Обновить вкладку «Текущие СД» ─────────────
        void RefreshCurrentSD() {
            std::string htOut =
                "===========================\n"
                "     ЛОГ ОПЕРАЦИИ\n"
                "===========================\n";
            htOut += dm->operationLog + "\n";
            htOut += "===========================\n"
                "     ХТ Волонтёры\n"
                "===========================\n";
            htOut += dm->htVolunteers->Print();
            htOut += "\n===========================\n"
                "     ХТ Мероприятия\n"
                "===========================\n";
            htOut += dm->htEvents->Print();
            rtbCurrentHT->Text = gcnew String(htOut.c_str());

            std::string bstOut =
                "===========================\n"
                "     ЛОГ ОПЕРАЦИИ\n"
                "===========================\n";
            bstOut += dm->operationLog + "\n";

            bstOut += "===========================\n"
                "  КЧД Волонтёры ФИО|Город\n"
                "===========================\n";
            bstOut += dm->bstVolunteers->Print();

            bstOut += "\n===========================\n"
                "  КЧД Мероприятия ФИО|Город\n"
                "===========================\n";
            bstOut += dm->bstEvents->Print();

            bstOut += "\n===========================\n"
                "  КЧД Мероприятия по Дате\n"
                "  Ключ: ГГГГММДД\n"
                "===========================\n";
            bstOut += "Пример: 20240115 = 15 январь 2024\n";
            bstOut += std::string(40, '-') + "\n";
            bstOut += dm->bstEventsByDate->Print();

            rtbCurrentBST->Text = gcnew String(bstOut.c_str());
        }

        // ════════════════════════════════════════════════
        // ОБРАБОТЧИКИ КНОПОК
        // ════════════════════════════════════════════════

        // ── Загрузить ─────────────────────────────────
        void OnLoad(Object^ s, EventArgs^ e) {
            MessageBox::Show(
                L"Загрузка выполняется в два шага:\n\n"
                L"1)  Выберите файл ВОЛОНТЁРОВ\n"
                L"2)  Выберите файл МЕРОПРИЯТИЙ\n\n"
                L"Формат: ФИО;Город;Навыки (волонтёры)\n"
                L"        ФИО;Город;Название;Часы;Дата (мероприятия)",
                L"Порядок загрузки", MessageBoxButtons::OK, MessageBoxIcon::Information);

            OpenFileDialog^ dlg = gcnew OpenFileDialog();
            dlg->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы|*.*";

            dlg->Title = L"Шаг 1 — Файл ВОЛОНТЁРОВ";
            if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                if (dm->LoadVolunteers(ToStd(dlg->FileName).c_str())) {
                    MessageBox::Show(
                        L"Волонтёры загружены: " +
                        gcnew String(std::to_string(dm->volCount).c_str()) + L" записей.",
                        L"Шаг 1 выполнен", MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
                else {
                    MessageBox::Show(L"Не удалось открыть файл волонтёров!", L"Ошибка",
                        MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }

            dlg->Title = L"Шаг 2 — Файл МЕРОПРИЯТИЙ";
            if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                if (dm->LoadEvents(ToStd(dlg->FileName).c_str())) {
                    MessageBox::Show(
                        L"Мероприятия загружены: " +
                        gcnew String(std::to_string(dm->evCount).c_str()) + L" записей.",
                        L"Шаг 2 выполнен", MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
                else {
                    MessageBox::Show(L"Не удалось открыть файл мероприятий!", L"Ошибка",
                        MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }

            dm->operationLog = "=== ЗАГРУЗКА ИЗ ФАЙЛОВ ===\n"
                "Волонтёров: " + std::to_string(dm->volCount) + "\n"
                "Мероприятий: " + std::to_string(dm->evCount) + "\n";

            if (!initialStateCaptured && (dm->volCount > 0 || dm->evCount > 0))
                CaptureInitialState();

            // Сброс фильтров при новой загрузке
            filterActive = false; filterSkills = ""; filterCity = "";
            filterYearFrom = 0; filterYearTo = 9999;
            UpdateFilterStatus();
            RefreshGrids();
            RefreshCurrentSD();
        }

        // ── Сохранить ─────────────────────────────────
        void OnSave(Object^ s, EventArgs^ e) {
            if (dm->volCount == 0 && dm->evCount == 0) {
                MessageBox::Show(L"Нет данных для сохранения!", L"Внимание",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }
            SaveFileDialog^ dlg = gcnew SaveFileDialog();
            dlg->Filter = L"Текстовые файлы (*.txt)|*.txt";

            dlg->Title = L"Сохранить волонтёров"; dlg->FileName = L"volunteers.txt";
            if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::OK)
                dm->SaveVolunteers(ToStd(dlg->FileName).c_str());

            dlg->Title = L"Сохранить мероприятия"; dlg->FileName = L"events.txt";
            if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                dm->SaveEvents(ToStd(dlg->FileName).c_str());
                MessageBox::Show(L"Файлы успешно сохранены!", L"OK",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        // ── Добавить ──────────────────────────────────
        void OnAdd(Object^ s, EventArgs^ e) {
            if (tabMain->SelectedIndex == 0)      OnAddVolunteer();
            else if (tabMain->SelectedIndex == 1)  OnAddEvent();
            else MessageBox::Show(L"Перейдите на вкладку «Волонтёры» или «Мероприятия».",
                L"Добавление", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        void OnAddVolunteer() {
            AddVolunteerForm^ dlg = gcnew AddVolunteerForm();
            if (dlg->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

            std::string fio = ToStd(dlg->tbFio->Text->Trim());
            std::string city = ToStd(dlg->tbCity->Text->Trim());
            std::string skills = ToStd(dlg->tbSkills->Text->Trim());

            int res = dm->AddVolunteer(fio.c_str(), city.c_str(), skills.c_str());
            if (res == 0) {
                if (!initialStateCaptured) CaptureInitialState();
                RefreshGrids(); RefreshCurrentSD();
                MessageBox::Show(L"Волонтёр успешно добавлен!", L"OK",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            else if (res == 1) {
                MessageBox::Show(L"Массив данных заполнен!\nУдалите ненужные записи или увеличьте размер ХТ.", L"Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            else if (res == 2) {
                MessageBox::Show(
                    L"Волонтёр с ФИО «" + gcnew String(fio.c_str()) + L"»\n"
                    L"и городом «" + gcnew String(city.c_str()) + L"» уже существует в справочнике!",
                    L"Дубликат", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }

        void OnAddEvent() {
            if (dm->volCount == 0) {
                MessageBox::Show(L"Справочник «Волонтёры» пуст!\nСначала добавьте хотя бы одного волонтёра.",
                    L"Ошибка целостности", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }
            AddEventForm^ dlg = gcnew AddEventForm();
            if (dlg->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

            std::string fio = ToStd(dlg->tbFio->Text->Trim());
            std::string city = ToStd(dlg->tbCity->Text->Trim());
            std::string name = ToStd(dlg->tbName->Text->Trim());
            std::string date = ToStd(dlg->tbDate->Text->Trim());
            int hours = int::Parse(dlg->tbHours->Text->Trim());

            int res = dm->AddEvent(fio.c_str(), city.c_str(), name.c_str(), hours, date.c_str());
            if (res == 0) {
                if (!initialStateCaptured) CaptureInitialState();
                RefreshGrids(); RefreshCurrentSD();
                MessageBox::Show(L"Мероприятие успешно добавлено!", L"OK",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            else if (res == 1) {
                MessageBox::Show(L"Массив данных заполнен!\nУдалите ненужные записи.", L"Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            else if (res == 2) {
                MessageBox::Show(
                    L"Нарушение целостности данных!\n"
                    L"Волонтёр «" + gcnew String(fio.c_str()) + L"» не найден в справочнике «Волонтёры».\n"
                    L"Сначала добавьте этого волонтёра.",
                    L"Ошибка целостности", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            else if (res == 3) {
                MessageBox::Show(
                    L"Мероприятие «" + gcnew String(name.c_str()) + L"» для волонтёра «" +
                    gcnew String(fio.c_str()) + L"» в городе «" + gcnew String(city.c_str()) +
                    L"» уже существует!",
                    L"Дубликат", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }

        // ── Удалить ───────────────────────────────────
        void OnDelete(Object^ s, EventArgs^ e) {
            int tab = tabMain->SelectedIndex;

            if (tab == 0) {
                if (gridVolunteers->SelectedRows->Count == 0) {
                    MessageBox::Show(L"Выберите строку волонтёра для удаления!", L"Внимание",
                        MessageBoxButtons::OK, MessageBoxIcon::Warning); return;
                }
                int idx = gridVolunteers->SelectedRows[0]->Index;
                if (idx < 0 || idx >= dm->volCount) {
                    MessageBox::Show(L"Некорректный выбор. Попробуйте снова.", L"Ошибка",
                        MessageBoxButtons::OK, MessageBoxIcon::Error); return;
                }

                String^ volName = gcnew String(dm->volunteers[idx].fio);

                // Подсчёт связанных мероприятий
                int related = 0;
                for (int i = 0; i < dm->evCount; i++)
                    if (strcmp(dm->events[i].vol_fio, dm->volunteers[idx].fio) == 0) related++;

                String^ msg = L"Удалить волонтёра:\n«" + volName + L"»?";
                if (related > 0)
                    msg += L"\n\nВНИМАНИЕ: У волонтёра есть " + gcnew String(std::to_string(related).c_str()) +
                    L" мероприятий в справочнике.\nСначала удалите связанные мероприятия.";

                if (MessageBox::Show(msg, L"Подтверждение удаления",
                    MessageBoxButtons::YesNo, MessageBoxIcon::Question)
                    != System::Windows::Forms::DialogResult::Yes) return;

                int res = dm->DeleteVolunteer(idx);
                if (res == 2) {
                    MessageBox::Show(
                        L"Невозможно удалить волонтёра «" + volName + L"»!\n"
                        L"В справочнике «Мероприятия» есть записи, ссылающиеся на него.\n"
                        L"Удалите все мероприятия этого волонтёра и повторите попытку.",
                        L"Ошибка целостности", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
                else {
                    RefreshGrids(); RefreshCurrentSD();
                    MessageBox::Show(L"Волонтёр «" + volName + L"» успешно удалён.", L"OK",
                        MessageBoxButtons::OK, MessageBoxIcon::Information);
                }

            }
            else if (tab == 1) {
                if (gridEvents->SelectedRows->Count == 0) {
                    MessageBox::Show(L"Выберите строку мероприятия для удаления!", L"Внимание",
                        MessageBoxButtons::OK, MessageBoxIcon::Warning); return;
                }
                int idx = gridEvents->SelectedRows[0]->Index;
                if (idx < 0 || idx >= dm->evCount) {
                    MessageBox::Show(L"Некорректный выбор. Попробуйте снова.", L"Ошибка",
                        MessageBoxButtons::OK, MessageBoxIcon::Error); return;
                }
                String^ evName = gcnew String(dm->events[idx].name);
                if (MessageBox::Show(L"Удалить мероприятие:\n«" + evName + L"»?",
                    L"Подтверждение удаления", MessageBoxButtons::YesNo, MessageBoxIcon::Question)
                    != System::Windows::Forms::DialogResult::Yes) return;

                dm->DeleteEvent(idx);
                RefreshGrids(); RefreshCurrentSD();
                MessageBox::Show(L"Мероприятие «" + evName + L"» успешно удалено.", L"OK",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);

            }
            else {
                MessageBox::Show(L"Перейдите на вкладку «Волонтёры» или «Мероприятия».",
                    L"Удаление", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        // ── Поиск ─────────────────────────────────────
        void OnSearch(Object^ s, EventArgs^ e) {
            SearchForm^ dlg = gcnew SearchForm();
            if (dlg->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

            std::string fio = ToStd(dlg->tbFio->Text->Trim());
            std::string city = ToStd(dlg->tbCity->Text->Trim());

            if (fio.empty() && city.empty()) {
                MessageBox::Show(L"Введите хотя бы одно поле для поиска: «ФИО» или «Город»!",
                    L"Поиск", MessageBoxButtons::OK, MessageBoxIcon::Warning); return;
            }

            int steps = 0;
            int idx = dm->SearchVolunteer(fio.c_str(), city.c_str(), steps);
            RefreshCurrentSD();

            if (idx >= 0) {
                tabMain->SelectedIndex = 0;
                gridVolunteers->ClearSelection();
                if (idx < gridVolunteers->Rows->Count) {
                    gridVolunteers->Rows[idx]->Selected = true;
                    gridVolunteers->FirstDisplayedScrollingRowIndex = idx;
                }
                MessageBox::Show(
                    L"Найдено в «Волонтёры»!\n"
                    L"Индекс в массиве: " + gcnew String(std::to_string(idx).c_str()) + L"\n"
                    L"Шагов поиска (ХТ): " + gcnew String(std::to_string(steps).c_str()),
                    L"Результат поиска", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            else {
                int steps2 = 0;
                int idx2 = dm->SearchEvent(fio.c_str(), city.c_str(), steps2);
                RefreshCurrentSD();
                if (idx2 >= 0) {
                    tabMain->SelectedIndex = 1;
                    gridEvents->ClearSelection();
                    if (idx2 < gridEvents->Rows->Count) {
                        gridEvents->Rows[idx2]->Selected = true;
                        gridEvents->FirstDisplayedScrollingRowIndex = idx2;
                    }
                    MessageBox::Show(
                        L"Найдено в «Мероприятия»!\n"
                        L"Индекс в массиве: " + gcnew String(std::to_string(idx2).c_str()) + L"\n"
                        L"Шагов поиска (ХТ): " + gcnew String(std::to_string(steps2).c_str()),
                        L"Результат поиска", MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
                else {
                    MessageBox::Show(
                        L"Запись не найдена ни в одном справочнике.\n"
                        L"Шагов поиска: " + gcnew String(std::to_string(steps).c_str()),
                        L"Не найдено", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                }
            }
        }

        // ── Фильтр ────────────────────────────────────
        void OnFilter(Object^ s, EventArgs^ e) {
            String^ curFrom = filterYearFrom > 0 ? gcnew String(std::to_string(filterYearFrom).c_str()) : "";
            String^ curTo = filterYearTo < 9999 ? gcnew String(std::to_string(filterYearTo).c_str()) : "";

            FilterForm^ dlg = gcnew FilterForm(filterSkills, filterCity, curFrom, curTo);
            if (dlg->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

            if (dlg->resetPressed) {
                OnResetFilter(nullptr, nullptr); return;
            }

            filterSkills = dlg->tbSkills->Text->Trim();
            filterCity = dlg->tbCity->Text->Trim();
            filterYearFrom = 0; filterYearTo = 9999;
            try { if (dlg->tbYearFrom->Text->Trim()->Length > 0) filterYearFrom = int::Parse(dlg->tbYearFrom->Text->Trim()); }
            catch (...) {}
            try { if (dlg->tbYearTo->Text->Trim()->Length > 0) filterYearTo = int::Parse(dlg->tbYearTo->Text->Trim()); }
            catch (...) {}

            filterActive = (filterSkills->Length > 0 || filterCity->Length > 0 ||
                filterYearFrom > 0 || filterYearTo < 9999);

            // Применяем к таблицам
            gridVolunteers->Rows->Clear();
            for (int i = 0; i < dm->volCount; i++) {
                String^ sk = gcnew String(dm->volunteers[i].skills);
                if (filterSkills->Length == 0 || sk->ToLower()->Contains(filterSkills->ToLower())) {
                    gridVolunteers->Rows->Add(
                        gcnew String(dm->volunteers[i].fio),
                        gcnew String(dm->volunteers[i].city), sk);
                }
            }

            gridEvents->Rows->Clear();
            for (int i = 0; i < dm->evCount; i++) {
                String^ ct = gcnew String(dm->events[i].city);
                String^ dt = gcnew String(dm->events[i].date);
                int year = 0;
                array<String^>^ parts = dt->Split(' ');
                if (parts->Length >= 3) try { year = int::Parse(parts[2]); }
                catch (...) {}
                bool cityOk = (filterCity->Length == 0 || ct->ToLower()->Contains(filterCity->ToLower()));
                bool yearOk = (year >= filterYearFrom && year <= filterYearTo);
                if (cityOk && yearOk) {
                    char buf[20]; snprintf(buf, 20, "%d", dm->events[i].hours);
                    gridEvents->Rows->Add(
                        gcnew String(dm->events[i].vol_fio), ct,
                        gcnew String(dm->events[i].name), gcnew String(buf), dt);
                }
            }

            UpdateFilterStatus();

            int vv = gridVolunteers->Rows->Count;
            int ev = gridEvents->Rows->Count;
            if (filterActive) {
                if (vv == 0 && ev == 0)
                    MessageBox::Show(L"По заданным фильтрам ни одной записи не найдено.",
                        L"Фильтр применён", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                else
                    MessageBox::Show(
                        L"Фильтр применён.\n"
                        L"Волонтёров: " + gcnew String(std::to_string(vv).c_str()) + L"\n"
                        L"Мероприятий: " + gcnew String(std::to_string(ev).c_str()) + L"\n\n"
                        L"Отчёт будет сформирован с этим фильтром.",
                        L"Фильтр", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        // ── Сбросить фильтр ───────────────────────────
        void OnResetFilter(Object^ s, EventArgs^ e) {
            filterActive = false;
            filterSkills = "";
            filterCity = "";
            filterYearFrom = 0;
            filterYearTo = 9999;
            UpdateFilterStatus();
            RefreshGrids();
            MessageBox::Show(L"Все фильтры сброшены. Показаны все записи.", L"Сброс фильтра",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        // ── Отчёт ─────────────────────────────────────
        void OnReport(Object^ s, EventArgs^ e) {
            if (dm->evCount == 0) {
                MessageBox::Show(L"Справочник «Мероприятия» пуст.\nНет данных для формирования отчёта.",
                    L"Отчёт", MessageBoxButtons::OK, MessageBoxIcon::Warning); return;
            }

            Form^ rpt = gcnew Form();
            rpt->Text = filterActive
                ? L"Отчёт — Волонтёры и мероприятия [фильтр активен]"
                : L"Отчёт — Волонтёры и мероприятия [все записи]";
            rpt->Size = System::Drawing::Size(1000, 560);
            rpt->StartPosition = FormStartPosition::CenterParent;

            // Панель с описанием фильтра
            Panel^ panelInfo = gcnew Panel();
            panelInfo->Dock = DockStyle::Top;
            panelInfo->Height = 28;
            panelInfo->BackColor = filterActive
                ? System::Drawing::Color::FromArgb(255, 243, 205)
                : System::Drawing::Color::FromArgb(220, 240, 220);

            Label^ infoLbl = gcnew Label();
            infoLbl->Text = filterActive
                ? L"  Фильтр: " + lblFilterStatus->Text
                : L"  Фильтр не задан — отображаются все записи.";
            infoLbl->Dock = DockStyle::Fill;
            infoLbl->ForeColor = filterActive
                ? System::Drawing::Color::FromArgb(120, 60, 0)
                : System::Drawing::Color::FromArgb(0, 80, 0);
            infoLbl->TextAlign = ContentAlignment::MiddleLeft;
            panelInfo->Controls->Add(infoLbl);

            DataGridView^ grid = gcnew DataGridView();
            grid->Dock = DockStyle::Fill;
            grid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            grid->ReadOnly = true;
            grid->AllowUserToAddRows = false;
            grid->BackgroundColor = System::Drawing::Color::White;
            grid->SelectionMode = DataGridViewSelectionMode::FullRowSelect;

            grid->Columns->Add(L"fio", L"ФИО волонтёра");
            grid->Columns->Add(L"v_city", L"Город (вол.)");
            grid->Columns->Add(L"skills", L"Навыки");
            grid->Columns->Add(L"e_city", L"Город (меропр.)");
            grid->Columns->Add(L"ev_name", L"Название мероприятия");
            grid->Columns->Add(L"hours", L"Часы");
            grid->Columns->Add(L"date", L"Дата");

            int rowCount = 0;

            for (int i = 0; i < dm->evCount; i++) {

                // ── Фильтр мероприятий по городу и периоду ──
                if (filterActive) {
                    String^ ct = gcnew String(dm->events[i].city);
                    String^ dt = gcnew String(dm->events[i].date);
                    int year = 0;
                    array<String^>^ parts = dt->Split(' ');
                    if (parts->Length >= 3) try { year = int::Parse(parts[2]); }
                    catch (...) {}
                    bool cityOk = (filterCity->Length == 0 || ct->ToLower()->Contains(filterCity->ToLower()));
                    bool yearOk = (year >= filterYearFrom && year <= filterYearTo);
                    if (!cityOk || !yearOk) continue;
                }

                // ── Поиск волонтёра ──
                int vIdx = -1;
                for (int j = 0; j < dm->volCount; j++)
                    if (strcmp(dm->volunteers[j].fio, dm->events[i].vol_fio) == 0) { vIdx = j; break; }

                // ── Фильтр по навыкам волонтёра ──
                if (filterActive && filterSkills->Length > 0 && vIdx >= 0) {
                    String^ sk = gcnew String(dm->volunteers[vIdx].skills);
                    if (!sk->ToLower()->Contains(filterSkills->ToLower())) continue;
                }

                char buf[20]; snprintf(buf, 20, "%d", dm->events[i].hours);
                if (vIdx >= 0) {
                    grid->Rows->Add(
                        gcnew String(dm->volunteers[vIdx].fio),
                        gcnew String(dm->volunteers[vIdx].city),
                        gcnew String(dm->volunteers[vIdx].skills),
                        gcnew String(dm->events[i].city),
                        gcnew String(dm->events[i].name),
                        gcnew String(buf),
                        gcnew String(dm->events[i].date));
                }
                else {
                    // Волонтёр не найден — нарушение целостности, показываем с пометкой
                    grid->Rows->Add(
                        gcnew String(dm->events[i].vol_fio),
                        L"(волонтёр не найден)", L"—",
                        gcnew String(dm->events[i].city),
                        gcnew String(dm->events[i].name),
                        gcnew String(buf),
                        gcnew String(dm->events[i].date));
                }
                rowCount++;
            }

            // Статус-бар отчёта
            StatusStrip^ ss = gcnew StatusStrip();
            ToolStripStatusLabel^ sl = gcnew ToolStripStatusLabel();
            sl->Text = rowCount == 0
                ? L"По заданным фильтрам записей не найдено."
                : L"Записей в отчёте: " + gcnew String(std::to_string(rowCount).c_str()) +
                (filterActive ? L" (применён фильтр)" : L" (все записи)");
            ss->Items->Add(sl);

            rpt->Controls->Add(grid);
            rpt->Controls->Add(ss);
            rpt->Controls->Add(panelInfo);

            if (rowCount == 0) {
                MessageBox::Show(
                    L"По заданным фильтрам записей для отчёта не найдено!\n\n"
                    L"Проверьте критерии фильтрации или нажмите «Сбросить фильтр».",
                    L"Отчёт пуст", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }

            rpt->ShowDialog();
        }

        // ── Размер ХТ ─────────────────────────────────
        void OnHtSize(Object^ s, EventArgs^ e) {
            HtSizeForm^ dlg = gcnew HtSizeForm(dm->htVolunteers->GetSize());
            if (dlg->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

            int sz = int::Parse(dlg->tbSize->Text->Trim());
            int maxRec = dm->volCount > dm->evCount ? dm->volCount : dm->evCount;

            if (sz <= maxRec) {
                MessageBox::Show(
                    L"Размер ХТ должен быть больше текущего количества записей!\n"
                    L"Записей сейчас: " + gcnew String(std::to_string(maxRec).c_str()) + L"\n"
                    L"Введите число больше " + gcnew String(std::to_string(maxRec).c_str()) + L".",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            dm->RebuildStructures(sz);
            dm->operationLog = "=== ИЗМЕНЕНИЕ РАЗМЕРА ХТ ===\nНовый размер: " +
                std::to_string(sz) + "\n";
            RefreshCurrentSD();
            MessageBox::Show(
                L"Размер хеш-таблицы изменён на " + gcnew String(std::to_string(sz).c_str()) + L".",
                L"OK", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        // ════════════════════════════════════════════════
        // ИНИЦИАЛИЗАЦИЯ ФОРМЫ
        // ════════════════════════════════════════════════
        void InitializeComponent(void) {
            components = gcnew System::ComponentModel::Container();
            this->Text = L"Бюро добрых дел";
            this->Size = System::Drawing::Size(1280, 800);
            this->MinimumSize = System::Drawing::Size(900, 600);

            // ── ToolStrip ──────────────────────────────
            toolStrip = gcnew ToolStrip();

            btnLoad = MakeBtn(L"Загрузить", L"Загрузить справочники из файлов");
            btnSave = MakeBtn(L"Сохранить", L"Сохранить справочники в файлы");
            btnAdd = MakeBtn(L"Добавить", L"Добавить запись (активная вкладка)");
            btnDelete = MakeBtn(L"Удалить", L"Удалить выбранную запись");
            btnSearch = MakeBtn(L"Поиск", L"Поиск по ФИО + Город");
            btnFilter = MakeBtn(L"Фильтр", L"Задать фильтры (применяются и к отчёту)");
            btnResetFilter = MakeBtn(L"Сбросить фильтр", L"Отменить все фильтры");
            btnReport = MakeBtn(L"Отчёт", L"Сформировать отчёт (с учётом фильтров)");
            btnHtSize = MakeBtn(L"Размер ХТ", L"Задать размер хеш-таблицы");

            btnLoad->Click += gcnew EventHandler(this, &MainForm::OnLoad);
            btnSave->Click += gcnew EventHandler(this, &MainForm::OnSave);
            btnAdd->Click += gcnew EventHandler(this, &MainForm::OnAdd);
            btnDelete->Click += gcnew EventHandler(this, &MainForm::OnDelete);
            btnSearch->Click += gcnew EventHandler(this, &MainForm::OnSearch);
            btnFilter->Click += gcnew EventHandler(this, &MainForm::OnFilter);
            btnResetFilter->Click += gcnew EventHandler(this, &MainForm::OnResetFilter);
            btnReport->Click += gcnew EventHandler(this, &MainForm::OnReport);
            btnHtSize->Click += gcnew EventHandler(this, &MainForm::OnHtSize);

            btnResetFilter->Enabled = false;

            lblFilterStatus = gcnew ToolStripLabel(L"Фильтр: не задан");
            lblFilterStatus->ForeColor = System::Drawing::Color::Gray;

            toolStrip->Items->Add(btnLoad);
            toolStrip->Items->Add(btnSave);
            toolStrip->Items->Add(gcnew ToolStripSeparator());
            toolStrip->Items->Add(btnAdd);
            toolStrip->Items->Add(btnDelete);
            toolStrip->Items->Add(gcnew ToolStripSeparator());
            toolStrip->Items->Add(btnSearch);
            toolStrip->Items->Add(gcnew ToolStripSeparator());
            toolStrip->Items->Add(btnFilter);
            toolStrip->Items->Add(btnResetFilter);
            toolStrip->Items->Add(gcnew ToolStripSeparator());
            toolStrip->Items->Add(btnReport);
            toolStrip->Items->Add(gcnew ToolStripSeparator());
            toolStrip->Items->Add(btnHtSize);
            toolStrip->Items->Add(gcnew ToolStripSeparator());
            toolStrip->Items->Add(lblFilterStatus);

            // ── TabControl (4 вкладки) ─────────────────
            tabMain = gcnew TabControl();
            tabMain->Dock = DockStyle::Fill;

            tabVolunteers = gcnew TabPage(L"Волонтёры");
            tabEvents = gcnew TabPage(L"Мероприятия");
            tabInitialSD = gcnew TabPage(L"Начальные СД");
            tabCurrentSD = gcnew TabPage(L"Текущие СД");

            // ── GridVolunteers ─────────────────────────
            gridVolunteers = gcnew DataGridView();
            gridVolunteers->Dock = DockStyle::Fill;
            gridVolunteers->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            gridVolunteers->ReadOnly = true;
            gridVolunteers->AllowUserToAddRows = false;
            gridVolunteers->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            gridVolunteers->BackgroundColor = System::Drawing::Color::White;
            gridVolunteers->Columns->Add(L"fio", L"ФИО");
            gridVolunteers->Columns->Add(L"city", L"Город");
            gridVolunteers->Columns->Add(L"skills", L"Навыки");
            tabVolunteers->Controls->Add(gridVolunteers);

            // ── GridEvents ─────────────────────────────
            gridEvents = gcnew DataGridView();
            gridEvents->Dock = DockStyle::Fill;
            gridEvents->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            gridEvents->ReadOnly = true;
            gridEvents->AllowUserToAddRows = false;
            gridEvents->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            gridEvents->BackgroundColor = System::Drawing::Color::White;
            gridEvents->Columns->Add(L"vol_fio", L"ФИО волонтёра");
            gridEvents->Columns->Add(L"city", L"Город");
            gridEvents->Columns->Add(L"name", L"Название");
            gridEvents->Columns->Add(L"hours", L"Часы");
            gridEvents->Columns->Add(L"date", L"Дата");
            tabEvents->Controls->Add(gridEvents);

            // ── Вкладка: Начальные СД ──────────────────
            splitInitial = gcnew SplitContainer();
            splitInitial->Dock = DockStyle::Fill;
            splitInitial->Orientation = Orientation::Vertical;
            splitInitial->SplitterDistance = 500;

            panelIHT = gcnew Panel(); panelIHT->Dock = DockStyle::Fill;
            lblIHT = gcnew Label();
            lblIHT->Text = L"  Хеш-таблица (снимок при первой загрузке — не изменяется)";
            lblIHT->Dock = DockStyle::Top; lblIHT->Height = 24;
            lblIHT->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
            lblIHT->BackColor = System::Drawing::Color::FromArgb(255, 220, 185);
            rtbInitialHT = gcnew RichTextBox();
            rtbInitialHT->Dock = DockStyle::Fill; rtbInitialHT->ReadOnly = true;
            rtbInitialHT->Font = gcnew System::Drawing::Font(L"Consolas", 9);
            rtbInitialHT->BackColor = System::Drawing::Color::FromArgb(255, 248, 235);
            rtbInitialHT->Text = L"[Данные ещё не загружены]";
            panelIHT->Controls->Add(rtbInitialHT);
            panelIHT->Controls->Add(lblIHT);
            splitInitial->Panel1->Controls->Add(panelIHT);

            panelIBST = gcnew Panel(); panelIBST->Dock = DockStyle::Fill;
            lblIBST = gcnew Label();
            lblIBST->Text = L"  КЧД (снимок при первой загрузке — не изменяется)";
            lblIBST->Dock = DockStyle::Top; lblIBST->Height = 24;
            lblIBST->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
            lblIBST->BackColor = System::Drawing::Color::FromArgb(200, 230, 200);
            rtbInitialBST = gcnew RichTextBox();
            rtbInitialBST->Dock = DockStyle::Fill; rtbInitialBST->ReadOnly = true;
            rtbInitialBST->Font = gcnew System::Drawing::Font(L"Consolas", 9);
            rtbInitialBST->BackColor = System::Drawing::Color::FromArgb(235, 248, 235);
            rtbInitialBST->Text = L"[Данные ещё не загружены]";
            panelIBST->Controls->Add(rtbInitialBST);
            panelIBST->Controls->Add(lblIBST);
            splitInitial->Panel2->Controls->Add(panelIBST);
            tabInitialSD->Controls->Add(splitInitial);

            // ── Вкладка: Текущие СД ────────────────────
            splitCurrent = gcnew SplitContainer();
            splitCurrent->Dock = DockStyle::Fill;
            splitCurrent->Orientation = Orientation::Vertical;
            splitCurrent->SplitterDistance = 500;

            panelCHT = gcnew Panel(); panelCHT->Dock = DockStyle::Fill;
            lblCHT = gcnew Label();
            lblCHT->Text = L"  Хеш-таблица (актуальное состояние + лог)";
            lblCHT->Dock = DockStyle::Top; lblCHT->Height = 24;
            lblCHT->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
            lblCHT->BackColor = System::Drawing::Color::FromArgb(180, 210, 255);
            rtbCurrentHT = gcnew RichTextBox();
            rtbCurrentHT->Dock = DockStyle::Fill; rtbCurrentHT->ReadOnly = true;
            rtbCurrentHT->Font = gcnew System::Drawing::Font(L"Consolas", 9);
            rtbCurrentHT->BackColor = System::Drawing::Color::FromArgb(235, 242, 255);
            rtbCurrentHT->Text = L"[ХТ пуста]";
            panelCHT->Controls->Add(rtbCurrentHT);
            panelCHT->Controls->Add(lblCHT);
            splitCurrent->Panel1->Controls->Add(panelCHT);

            panelCBST = gcnew Panel(); panelCBST->Dock = DockStyle::Fill;
            lblCBST = gcnew Label();
            lblCBST->Text = L"  КЧД (актуальное состояние + лог)";
            lblCBST->Dock = DockStyle::Top; lblCBST->Height = 24;
            lblCBST->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
            lblCBST->BackColor = System::Drawing::Color::FromArgb(220, 200, 255);
            rtbCurrentBST = gcnew RichTextBox();
            rtbCurrentBST->Dock = DockStyle::Fill; rtbCurrentBST->ReadOnly = true;
            rtbCurrentBST->Font = gcnew System::Drawing::Font(L"Consolas", 9);
            rtbCurrentBST->BackColor = System::Drawing::Color::FromArgb(245, 240, 255);
            rtbCurrentBST->Text = L"[КЧД пусто]";
            panelCBST->Controls->Add(rtbCurrentBST);
            panelCBST->Controls->Add(lblCBST);
            splitCurrent->Panel2->Controls->Add(panelCBST);
            tabCurrentSD->Controls->Add(splitCurrent);

            // ── Сборка ────────────────────────────────
            tabMain->TabPages->Add(tabVolunteers);
            tabMain->TabPages->Add(tabEvents);
            tabMain->TabPages->Add(tabInitialSD);
            tabMain->TabPages->Add(tabCurrentSD);

            this->Controls->Add(tabMain);
            this->Controls->Add(toolStrip);
        }
    };

} // namespace BureauOfGoodDeeds