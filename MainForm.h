#pragma once
#pragma once
#include <string>
#include <cstring>


#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

#include "DataManager.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;

// ═══════════════════════════════════════════════════════
// УТИЛИТА: String^ -> std::string
// ═══════════════════════════════════════════════════════
static std::string ToStd(String^ s) {
    const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
    std::string result(chars);
    Marshal::FreeHGlobal(IntPtr((void*)chars));
    return result;
}

// ═══════════════════════════════════════════════════════
// ДИАЛОГ: Добавить волонтёра
// ═══════════════════════════════════════════════════════
ref class AddVolunteerForm : public Form {
public:
    TextBox^ tbFio;
    TextBox^ tbCity;
    TextBox^ tbSkills;

    AddVolunteerForm() {
        this->Text = L"Добавить волонтёра";
        this->Size = System::Drawing::Size(420, 220);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->StartPosition = FormStartPosition::CenterParent;
        this->MaximizeBox = false;
        this->MinimizeBox = false;

        Label^ l1 = gcnew Label(); l1->Text = L"ФИО:";
        l1->Location = Point(10, 15); l1->Width = 90;
        Label^ l2 = gcnew Label(); l2->Text = L"Город:";
        l2->Location = Point(10, 55); l2->Width = 90;
        Label^ l3 = gcnew Label(); l3->Text = L"Навыки:";
        l3->Location = Point(10, 95); l3->Width = 90;

        tbFio = gcnew TextBox(); tbFio->Location = Point(105, 12); tbFio->Width = 280;
        tbCity = gcnew TextBox(); tbCity->Location = Point(105, 52); tbCity->Width = 280;
        tbSkills = gcnew TextBox(); tbSkills->Location = Point(105, 92); tbSkills->Width = 280;

        Button^ btnOk = gcnew Button();
        btnOk->Text = L"Добавить";
        btnOk->Location = Point(105, 140);
        btnOk->Width = 120;
        btnOk->Click += gcnew EventHandler(this, &AddVolunteerForm::OnOk);

        Button^ btnCancel = gcnew Button();
        btnCancel->Text = L"Отмена";
        btnCancel->Location = Point(235, 140);
        btnCancel->Width = 80;
        btnCancel->Click += gcnew EventHandler(this, &AddVolunteerForm::OnCancel);

        this->Controls->Add(l1); this->Controls->Add(tbFio);
        this->Controls->Add(l2); this->Controls->Add(tbCity);
        this->Controls->Add(l3); this->Controls->Add(tbSkills);
        this->Controls->Add(btnOk);
        this->Controls->Add(btnCancel);
    }
private:
    void OnOk(Object^ s, EventArgs^ e) {
        if (tbFio->Text->Trim()->Length == 0 || tbCity->Text->Trim()->Length == 0) {
            MessageBox::Show(L"ФИО и Город обязательны!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }
        this->DialogResult = System::Windows::Forms::DialogResult::OK;
    }
    void OnCancel(Object^ s, EventArgs^ e) {
        this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
    }
};

// ═══════════════════════════════════════════════════════
// ДИАЛОГ: Добавить мероприятие
// ═══════════════════════════════════════════════════════
ref class AddEventForm : public Form {
public:
    TextBox^ tbFio;
    TextBox^ tbCity;
    TextBox^ tbName;
    TextBox^ tbHours;
    TextBox^ tbDate;

    AddEventForm() {
        this->Text = L"Добавить мероприятие";
        this->Size = System::Drawing::Size(440, 300);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->StartPosition = FormStartPosition::CenterParent;
        this->MaximizeBox = false;
        this->MinimizeBox = false;

        Label^ l1 = gcnew Label(); l1->Text = L"ФИО волонтёра:";
        l1->Location = Point(10, 12); l1->Width = 130;
        Label^ l2 = gcnew Label(); l2->Text = L"Город:";
        l2->Location = Point(10, 52); l2->Width = 130;
        Label^ l3 = gcnew Label(); l3->Text = L"Название:";
        l3->Location = Point(10, 92); l3->Width = 130;
        Label^ l4 = gcnew Label(); l4->Text = L"Часы:";
        l4->Location = Point(10, 132); l4->Width = 130;
        Label^ l5 = gcnew Label(); l5->Text = L"Дата (DD месяц YYYY):";
        l5->Location = Point(10, 172); l5->Width = 130;

        tbFio = gcnew TextBox(); tbFio->Location = Point(145, 12);  tbFio->Width = 265;
        tbCity = gcnew TextBox(); tbCity->Location = Point(145, 52);  tbCity->Width = 265;
        tbName = gcnew TextBox(); tbName->Location = Point(145, 92);  tbName->Width = 265;
        tbHours = gcnew TextBox(); tbHours->Location = Point(145, 132); tbHours->Width = 265;
        tbDate = gcnew TextBox(); tbDate->Location = Point(145, 172); tbDate->Width = 265;

        Label^ hint = gcnew Label();
        hint->Text = L"Пример: 15 январь 2024";
        hint->Location = Point(145, 197);
        hint->ForeColor = System::Drawing::Color::White;
        hint->Width = 265;

        Button^ btnOk = gcnew Button();
        btnOk->Text = L"Добавить";
        btnOk->Location = Point(145, 225);
        btnOk->Width = 120;
        btnOk->Click += gcnew EventHandler(this, &AddEventForm::OnOk);

        Button^ btnCancel = gcnew Button();
        btnCancel->Text = L"Отмена";
        btnCancel->Location = Point(275, 225);
        btnCancel->Width = 80;
        btnCancel->Click += gcnew EventHandler(this, &AddEventForm::OnCancel);

        this->Controls->Add(l1); this->Controls->Add(tbFio);
        this->Controls->Add(l2); this->Controls->Add(tbCity);
        this->Controls->Add(l3); this->Controls->Add(tbName);
        this->Controls->Add(l4); this->Controls->Add(tbHours);
        this->Controls->Add(l5); this->Controls->Add(tbDate);
        this->Controls->Add(hint);
        this->Controls->Add(btnOk);
        this->Controls->Add(btnCancel);
    }
private:
    void OnOk(Object^ s, EventArgs^ e) {
        if (tbFio->Text->Trim()->Length == 0 ||
            tbCity->Text->Trim()->Length == 0 ||
            tbName->Text->Trim()->Length == 0) {
            MessageBox::Show(L"ФИО, Город и Название обязательны!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }
        try { int::Parse(tbHours->Text->Trim()); }
        catch (...) {
            MessageBox::Show(L"Часы должны быть числом!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }
        this->DialogResult = System::Windows::Forms::DialogResult::OK;
    }
    void OnCancel(Object^ s, EventArgs^ e) {
        this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
    }
};
// ═══════════════════════════════════════════════════════
// ДИАЛОГ: Поиск
// ═══════════════════════════════════════════════════════
ref class SearchForm : public Form {
public:
    TextBox^ tbFio;
    TextBox^ tbCity;

    SearchForm() {
        this->Text = L"Поиск по ФИО + Город";
        this->Size = System::Drawing::Size(380, 175);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->StartPosition = FormStartPosition::CenterParent;
        this->MaximizeBox = false;
        this->MinimizeBox = false;

        Label^ l1 = gcnew Label(); l1->Text = L"ФИО:";
        l1->Location = Point(10, 15); l1->Width = 75;
        Label^ l2 = gcnew Label(); l2->Text = L"Город:";
        l2->Location = Point(10, 55); l2->Width = 75;

        tbFio = gcnew TextBox(); tbFio->Location = Point(90, 12); tbFio->Width = 260;
        tbCity = gcnew TextBox(); tbCity->Location = Point(90, 52); tbCity->Width = 260;

        Button^ btnOk = gcnew Button();
        btnOk->Text = L"Найти";
        btnOk->Location = Point(90, 95);
        btnOk->Width = 100;
        btnOk->Click += gcnew EventHandler(this, &SearchForm::OnOk);

        Button^ btnCancel = gcnew Button();
        btnCancel->Text = L"Отмена";
        btnCancel->Location = Point(200, 95);
        btnCancel->Width = 80;
        btnCancel->Click += gcnew EventHandler(this, &SearchForm::OnCancel);

        this->Controls->Add(l1); this->Controls->Add(tbFio);
        this->Controls->Add(l2); this->Controls->Add(tbCity);
        this->Controls->Add(btnOk);
        this->Controls->Add(btnCancel);
    }
private:
    void OnOk(Object^ s, EventArgs^ e) {
        this->DialogResult = System::Windows::Forms::DialogResult::OK;
    }
    void OnCancel(Object^ s, EventArgs^ e) {
        this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
    }
};

// ═══════════════════════════════════════════════════════
// ДИАЛОГ: Фильтры
// ═══════════════════════════════════════════════════════
ref class FilterForm : public Form {
public:
    TextBox^ tbSkills;
    TextBox^ tbCity;
    TextBox^ tbYearFrom;
    TextBox^ tbYearTo;
    bool     resetPressed;

    FilterForm() {
        resetPressed = false;
        this->Text = L"Фильтры";
        this->Size = System::Drawing::Size(420, 270);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->StartPosition = FormStartPosition::CenterParent;
        this->MaximizeBox = false;
        this->MinimizeBox = false;

        Label^ lS = gcnew Label(); lS->Text = L"Навыки (Спр.1):";
        lS->Location = Point(10, 15); lS->Width = 135;
        tbSkills = gcnew TextBox(); tbSkills->Location = Point(150, 12); tbSkills->Width = 235;

        Label^ lC = gcnew Label(); lC->Text = L"Город (Спр.2):";
        lC->Location = Point(10, 55); lC->Width = 135;
        tbCity = gcnew TextBox(); tbCity->Location = Point(150, 52); tbCity->Width = 235;

        Label^ lP = gcnew Label(); lP->Text = L"Период (год):";
        lP->Location = Point(10, 95); lP->Width = 135;

        Label^ lF = gcnew Label(); lF->Text = L"от:";
        lF->Location = Point(10, 130); lF->Width = 30;
        tbYearFrom = gcnew TextBox(); tbYearFrom->Location = Point(45, 127); tbYearFrom->Width = 70;

        Label^ lT = gcnew Label(); lT->Text = L"до:";
        lT->Location = Point(130, 130); lT->Width = 30;
        tbYearTo = gcnew TextBox(); tbYearTo->Location = Point(165, 127); tbYearTo->Width = 70;

        Button^ btnApply = gcnew Button();
        btnApply->Text = L"Применить";
        btnApply->Location = Point(10, 185);
        btnApply->Width = 110;
        btnApply->Click += gcnew EventHandler(this, &FilterForm::OnApply);

        Button^ btnReset = gcnew Button();
        btnReset->Text = L"Сбросить";
        btnReset->Location = Point(130, 185);
        btnReset->Width = 100;
        btnReset->Click += gcnew EventHandler(this, &FilterForm::OnReset);

        Button^ btnClose = gcnew Button();
        btnClose->Text = L"Закрыть";
        btnClose->Location = Point(240, 185);
        btnClose->Width = 80;
        btnClose->Click += gcnew EventHandler(this, &FilterForm::OnClose);

        this->Controls->Add(lS); this->Controls->Add(tbSkills);
        this->Controls->Add(lC); this->Controls->Add(tbCity);
        this->Controls->Add(lP);
        this->Controls->Add(lF); this->Controls->Add(tbYearFrom);
        this->Controls->Add(lT); this->Controls->Add(tbYearTo);
        this->Controls->Add(btnApply);
        this->Controls->Add(btnReset);
        this->Controls->Add(btnClose);
    }
private:
    void OnApply(Object^ s, EventArgs^ e) {
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

// ═══════════════════════════════════════════════════════
// ДИАЛОГ: Размер ХТ
// ═══════════════════════════════════════════════════════
ref class HtSizeForm : public Form {
public:
    TextBox^ tbSize;

    HtSizeForm(int currentSize) {
        this->Text = L"Задать размер хеш-таблицы";
        this->Size = System::Drawing::Size(320, 150);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->StartPosition = FormStartPosition::CenterParent;
        this->MaximizeBox = false;
        this->MinimizeBox = false;

        Label^ lbl = gcnew Label();
        lbl->Text = L"Новый размер ХТ (простое число):";
        lbl->Location = Point(10, 15);
        lbl->Width = 290;

        tbSize = gcnew TextBox();
        tbSize->Location = Point(10, 45);
        tbSize->Width = 100;
        tbSize->Text = gcnew String(std::to_string(currentSize).c_str());

        Button^ btnOk = gcnew Button();
        btnOk->Text = L"Применить";
        btnOk->Location = Point(10, 80);
        btnOk->Width = 100;
        btnOk->Click += gcnew EventHandler(this, &HtSizeForm::OnOk);

        Button^ btnCancel = gcnew Button();
        btnCancel->Text = L"Отмена";
        btnCancel->Location = Point(120, 80);
        btnCancel->Width = 80;
        btnCancel->Click += gcnew EventHandler(this, &HtSizeForm::OnCancel);

        this->Controls->Add(lbl);
        this->Controls->Add(tbSize);
        this->Controls->Add(btnOk);
        this->Controls->Add(btnCancel);
    }
private:
    void OnOk(Object^ s, EventArgs^ e) {
        try { int::Parse(tbSize->Text->Trim()); }
        catch (...) {
            MessageBox::Show(L"Введите целое число!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }
        this->DialogResult = System::Windows::Forms::DialogResult::OK;
    }
    void OnCancel(Object^ s, EventArgs^ e) {
        this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
    }
};

// ═══════════════════════════════════════════════════════
// ГЛАВНАЯ ФОРМА
// ═══════════════════════════════════════════════════════
namespace BureauOfGoodDeeds {

    public ref class MainForm : public Form {
    public:
        MainForm(void) {
            InitializeComponent();
            dm = new DataManager(17);
            AutoLoadFromFiles();
            RefreshGrids();
            RefreshDebug();
        }
    protected:
        ~MainForm() {
            if (components) delete components;
            if (dm) delete dm;
        }
    private:
        System::ComponentModel::Container^ components;
        DataManager* dm;

        ToolStrip^ toolStrip;
        SplitContainer^ splitMain;
        SplitContainer^ splitDebug;
        TabControl^ tabDirectories;
        TabPage^ tabVolunteers;
        TabPage^ tabEvents;
        DataGridView^ gridVolunteers;
        DataGridView^ gridEvents;
        RichTextBox^ rtbHashTable;
        RichTextBox^ rtbBST;
        Label^ lblHT;
        Label^ lblBST;

        ToolStripButton^ btnLoad;
        ToolStripButton^ btnSave;
        ToolStripButton^ btnAdd;
        ToolStripButton^ btnDelete;
        ToolStripButton^ btnSearch;
        ToolStripButton^ btnFilter;
        ToolStripButton^ btnReport;
        ToolStripButton^ btnHtSize;


        void AutoLoadFromFiles() {
            // Ищем файлы рядом с exe — в папке проекта при запуске из VS
            bool volOk = dm->LoadVolunteers("volunteers.txt");
            bool evOk = dm->LoadEvents("events.txt");

            if (volOk && evOk) {
                dm->operationLog =
                    "=== АВТОЗАГРУЗКА ИЗ ФАЙЛОВ ===\n"
                    "volunteers.txt -> " + std::to_string(dm->volCount) + " записей\n"
                    "events.txt     -> " + std::to_string(dm->evCount) + " записей\n";
            }
            else if (!volOk && !evOk) {
                dm->operationLog = "=== ФАЙЛЫ НЕ НАЙДЕНЫ ===\n"
                    "Положите volunteers.txt и events.txt\n"
                    "рядом с .exe или в папку проекта.\n";
                MessageBox::Show(
                    L"Файлы volunteers.txt и events.txt не найдены.\n\n"
                    L"Положите их в папку проекта (рядом с .vcxproj)\n"
                    L"или загрузите вручную через кнопку 'Загрузить'.",
                    L"Автозагрузка",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
            }
            else if (!volOk) {
                dm->operationLog = "=== АВТОЗАГРУЗКА: volunteers.txt не найден ===\n";
                MessageBox::Show(L"Файл volunteers.txt не найден!",
                    L"Автозагрузка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
            else {
                dm->operationLog = "=== АВТОЗАГРУЗКА: events.txt не найден ===\n";
                MessageBox::Show(L"Файл events.txt не найден!",
                    L"Автозагрузка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }

       

        // ── Обновление таблиц ─────────────────────────
        void RefreshGrids() {
            gridVolunteers->Rows->Clear();
            for (int i = 0; i < dm->volCount; i++) {
                gridVolunteers->Rows->Add(
                    gcnew String(dm->volunteers[i].fio),
                    gcnew String(dm->volunteers[i].city),
                    gcnew String(dm->volunteers[i].skills)
                );
            }
            gridEvents->Rows->Clear();
            for (int i = 0; i < dm->evCount; i++) {
                char buf[20];
                snprintf(buf, 20, "%d", dm->events[i].hours);
                gridEvents->Rows->Add(
                    gcnew String(dm->events[i].vol_fio),
                    gcnew String(dm->events[i].city),
                    gcnew String(dm->events[i].name),
                    gcnew String(buf),
                    gcnew String(dm->events[i].date)
                );
            }
        }

        // ── Обновление отладки ────────────────────────
        void RefreshDebug() {
            // ── ХТ ──
            std::string htOut = "";
            htOut += "╔══════════════════════════════════════╗\n";
            htOut += "║          ЛОГ ОПЕРАЦИИ                ║\n";
            htOut += "╚══════════════════════════════════════╝\n";
            htOut += dm->operationLog;
            htOut += "\n";
            htOut += "╔══════════════════════════════════════╗\n";
            htOut += "║       ХТ Волонтёры                   ║\n";
            htOut += "╚══════════════════════════════════════╝\n";
            htOut += dm->htVolunteers->Print();
            htOut += "\n";
            htOut += "╔══════════════════════════════════════╗\n";
            htOut += "║       ХТ Мероприятия                 ║\n";
            htOut += "╚══════════════════════════════════════╝\n";
            htOut += dm->htEvents->Print();
            rtbHashTable->Text = gcnew String(htOut.c_str());

            // ── КЧД ──
            std::string bstOut = "";
            bstOut += "╔══════════════════════════════════════╗\n";
            bstOut += "║          ЛОГ ОПЕРАЦИИ                ║\n";
            bstOut += "╚══════════════════════════════════════╝\n";
            bstOut += dm->operationLog;
            bstOut += "\n";
            bstOut += "╔══════════════════════════════════════╗\n";
            bstOut += "║       КЧД Волонтёры                  ║\n";
            bstOut += "╚══════════════════════════════════════╝\n";
            bstOut += dm->bstVolunteers->Print();
            bstOut += "\n";
            bstOut += "╔══════════════════════════════════════╗\n";
            bstOut += "║       КЧД Мероприятия                ║\n";
            bstOut += "╚══════════════════════════════════════╝\n";
            bstOut += dm->bstEvents->Print();
            rtbBST->Text = gcnew String(bstOut.c_str());
        }

        // ── Загрузить ─────────────────────────────────
        void OnLoad(Object^ s, EventArgs^ e) {
            MessageBox::Show(
                L"Загрузка выполняется в два шага:\n\n"
                L"1️⃣  Сначала выберите файл ВОЛОНТЁРОВ\n"
                L"2️⃣  Затем выберите файл МЕРОПРИЯТИЙ\n\n"
                L"Формат строки волонтёров:  ФИО;Город;Навыки\n"
                L"Формат строки мероприятий: ФИО;Город;Название;Часы;Дата",
                L"Порядок загрузки",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information);

            OpenFileDialog^ dlg = gcnew OpenFileDialog();
            dlg->Title = L"Шаг 1 — Выберите файл ВОЛОНТЁРОВ";
            dlg->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы|*.*";
            if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                std::string path = ToStd(dlg->FileName);
                if (dm->LoadVolunteers(path.c_str()))
                    MessageBox::Show(L"✅ Волонтёры загружены!", L"Шаг 1 выполнен",
                        MessageBoxButtons::OK, MessageBoxIcon::Information);
                else
                    MessageBox::Show(L"❌ Ошибка открытия файла волонтёров!", L"Ошибка",
                        MessageBoxButtons::OK, MessageBoxIcon::Error);
            }

            dlg->Title = L"Шаг 2 — Выберите файл МЕРОПРИЯТИЙ";
            if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                std::string path = ToStd(dlg->FileName);
                if (dm->LoadEvents(path.c_str()))
                    MessageBox::Show(L"✅ Мероприятия загружены!", L"Шаг 2 выполнен",
                        MessageBoxButtons::OK, MessageBoxIcon::Information);
                else
                    MessageBox::Show(L"❌ Ошибка открытия файла мероприятий!", L"Ошибка",
                        MessageBoxButtons::OK, MessageBoxIcon::Error);
            }

            dm->operationLog = "=== ЗАГРУЗКА ИЗ ФАЙЛОВ ===\n"
                "Волонтёров: " + std::to_string(dm->volCount) + "\n"
                "Мероприятий: " + std::to_string(dm->evCount) + "\n";
            RefreshGrids();
            RefreshDebug();
        }

        // ── Сохранить ─────────────────────────────────
        void OnSave(Object^ s, EventArgs^ e) {
            SaveFileDialog^ dlg = gcnew SaveFileDialog();
            dlg->Title = L"Сохранить волонтёров";
            dlg->Filter = L"Текстовые файлы (*.txt)|*.txt";
            dlg->FileName = L"volunteers.txt";
            if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::OK)
                dm->SaveVolunteers(ToStd(dlg->FileName).c_str());

            dlg->Title = L"Сохранить мероприятия";
            dlg->FileName = L"events.txt";
            if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                dm->SaveEvents(ToStd(dlg->FileName).c_str());
                MessageBox::Show(L"Файлы сохранены!", L"OK",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        // ── Добавить ──────────────────────────────────
        void OnAdd(Object^ s, EventArgs^ e) {
            if (tabDirectories->SelectedIndex == 0) OnAddVolunteer();
            else                                     OnAddEvent();
        }

        void OnAddVolunteer() {
            AddVolunteerForm^ dlg = gcnew AddVolunteerForm();
            if (dlg->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

            std::string fio = ToStd(dlg->tbFio->Text->Trim());
            std::string city = ToStd(dlg->tbCity->Text->Trim());
            std::string skills = ToStd(dlg->tbSkills->Text->Trim());

            int res = dm->AddVolunteer(fio.c_str(), city.c_str(), skills.c_str());
            if (res == 1) MessageBox::Show(L"Массив заполнен!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            else if (res == 2) MessageBox::Show(L"Волонтёр с таким ФИО и городом уже существует!",
                L"Дубликат", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            else { RefreshGrids(); RefreshDebug(); }
        }

        void OnAddEvent() {
            AddEventForm^ dlg = gcnew AddEventForm();
            if (dlg->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

            std::string fio = ToStd(dlg->tbFio->Text->Trim());
            std::string city = ToStd(dlg->tbCity->Text->Trim());
            std::string name = ToStd(dlg->tbName->Text->Trim());
            std::string date = ToStd(dlg->tbDate->Text->Trim());
            int hours = int::Parse(dlg->tbHours->Text->Trim());

            int res = dm->AddEvent(fio.c_str(), city.c_str(), name.c_str(), hours, date.c_str());
            if (res == 1) MessageBox::Show(L"Массив заполнен!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            else if (res == 2) MessageBox::Show(L"Волонтёр не найден!\nСначала добавьте волонтёра.",
                L"Ошибка целостности", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            else if (res == 3) MessageBox::Show(L"Такое мероприятие уже существует!",
                L"Дубликат", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            else { RefreshGrids(); RefreshDebug(); }
        }

        // ── Удалить ───────────────────────────────────
        void OnDelete(Object^ s, EventArgs^ e) {
            if (tabDirectories->SelectedIndex == 0) {
                if (gridVolunteers->SelectedRows->Count == 0) {
                    MessageBox::Show(L"Выберите волонтёра!", L"Внимание",
                        MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }
                int idx = gridVolunteers->SelectedRows[0]->Index;
                String^ name = gcnew String(dm->volunteers[idx].fio);
                if (MessageBox::Show(L"Удалить: " + name + L"?", L"Подтверждение",
                    MessageBoxButtons::YesNo, MessageBoxIcon::Question)
                    != System::Windows::Forms::DialogResult::Yes) return;

                int res = dm->DeleteVolunteer(idx);
                if (res == 2)
                    MessageBox::Show(L"Нельзя удалить: есть связанные мероприятия!\nСначала удалите их.",
                        L"Ошибка целостности", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                else { RefreshGrids(); RefreshDebug(); }
            }
            else {
                if (gridEvents->SelectedRows->Count == 0) {
                    MessageBox::Show(L"Выберите мероприятие!", L"Внимание",
                        MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }
                int idx = gridEvents->SelectedRows[0]->Index;
                if (MessageBox::Show(L"Удалить мероприятие?", L"Подтверждение",
                    MessageBoxButtons::YesNo, MessageBoxIcon::Question)
                    != System::Windows::Forms::DialogResult::Yes) return;

                dm->DeleteEvent(idx);
                RefreshGrids();
                RefreshDebug();
            }
        }

        // ── Поиск ─────────────────────────────────────
        void OnSearch(Object^ s, EventArgs^ e) {
            SearchForm^ dlg = gcnew SearchForm();
            if (dlg->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

            std::string fio = ToStd(dlg->tbFio->Text->Trim());
            std::string city = ToStd(dlg->tbCity->Text->Trim());
            int steps = 0;
            int idx = dm->SearchVolunteer(fio.c_str(), city.c_str(), steps);

            if (idx >= 0) {
                gridVolunteers->ClearSelection();
                gridVolunteers->Rows[idx]->Selected = true;
                gridVolunteers->FirstDisplayedScrollingRowIndex = idx;
                tabDirectories->SelectedIndex = 0;
                MessageBox::Show(
                    L"Найден в волонтёрах!\nИндекс: " + idx.ToString() +
                    L"\nШагов поиска (ХТ): " + steps.ToString(),
                    L"Результат", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            else {
                int steps2 = 0;
                int idx2 = dm->SearchEvent(fio.c_str(), city.c_str(), steps2);
                if (idx2 >= 0) {
                    gridEvents->ClearSelection();
                    gridEvents->Rows[idx2]->Selected = true;
                    gridEvents->FirstDisplayedScrollingRowIndex = idx2;
                    tabDirectories->SelectedIndex = 1;
                    MessageBox::Show(
                        L"Найдено в мероприятиях!\nИндекс: " + idx2.ToString() +
                        L"\nШагов поиска (ХТ): " + steps2.ToString(),
                        L"Результат", MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
                else {
                    MessageBox::Show(
                        L"Не найдено.\nШагов поиска: " + steps.ToString(),
                        L"Результат", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                }
            }
        }

        // ── Фильтр ────────────────────────────────────
        void OnFilter(Object^ s, EventArgs^ e) {
            FilterForm^ dlg = gcnew FilterForm();
            if (dlg->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

            if (dlg->resetPressed) {
                RefreshGrids();
                return;
            }

            String^ filterSkill = dlg->tbSkills->Text->Trim()->ToLower();
            String^ filterCity = dlg->tbCity->Text->Trim()->ToLower();
            int yearFrom = 0, yearTo = 9999;
            try {
                if (dlg->tbYearFrom->Text->Trim()->Length > 0)
                    yearFrom = int::Parse(dlg->tbYearFrom->Text->Trim());
            }
            catch (...) {}
            try {
                if (dlg->tbYearTo->Text->Trim()->Length > 0)
                    yearTo = int::Parse(dlg->tbYearTo->Text->Trim());
            }
            catch (...) {}

            // Фильтр волонтёров по навыкам
            gridVolunteers->Rows->Clear();
            for (int i = 0; i < dm->volCount; i++) {
                String^ skills = gcnew String(dm->volunteers[i].skills);
                if (filterSkill->Length == 0 || skills->ToLower()->Contains(filterSkill)) {
                    gridVolunteers->Rows->Add(
                        gcnew String(dm->volunteers[i].fio),
                        gcnew String(dm->volunteers[i].city),
                        skills
                    );
                }
            }

            // Фильтр мероприятий по городу и периоду
            gridEvents->Rows->Clear();
            for (int i = 0; i < dm->evCount; i++) {
                String^ city = gcnew String(dm->events[i].city);
                String^ date = gcnew String(dm->events[i].date);
                int year = 0;
                array<String^>^ parts = date->Split(' ');
                if (parts->Length >= 3)
                    try { year = int::Parse(parts[2]); }
                catch (...) {}

                bool cityOk = (filterCity->Length == 0 || city->ToLower()->Contains(filterCity));
                bool yearOk = (year >= yearFrom && year <= yearTo);

                if (cityOk && yearOk) {
                    char buf[20]; snprintf(buf, 20, "%d", dm->events[i].hours);
                    gridEvents->Rows->Add(
                        gcnew String(dm->events[i].vol_fio),
                        city,
                        gcnew String(dm->events[i].name),
                        gcnew String(buf),
                        date
                    );
                }
            }
            MessageBox::Show(L"Фильтр применён!", L"OK",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        // ── Отчёт ─────────────────────────────────────
        void OnReport(Object^ s, EventArgs^ e) {
            Form^ rpt = gcnew Form();
            rpt->Text = L"Отчёт — Волонтёры и мероприятия";
            rpt->Size = System::Drawing::Size(1000, 500);
            rpt->StartPosition = FormStartPosition::CenterParent;

            DataGridView^ grid = gcnew DataGridView();
            grid->Dock = DockStyle::Fill;
            grid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            grid->ReadOnly = true;
            grid->AllowUserToAddRows = false;
            grid->BackgroundColor = System::Drawing::Color::White;

            grid->Columns->Add(L"fio", L"ФИО волонтёра");
            grid->Columns->Add(L"v_city", L"Город (вол.)");
            grid->Columns->Add(L"skills", L"Навыки");
            grid->Columns->Add(L"e_city", L"Город (меропр.)");
            grid->Columns->Add(L"ev_name", L"Название мероприятия");
            grid->Columns->Add(L"hours", L"Часы");
            grid->Columns->Add(L"date", L"Дата");

            for (int i = 0; i < dm->evCount; i++) {
                int vIdx = -1;
                for (int j = 0; j < dm->volCount; j++) {
                    if (strcmp(dm->volunteers[j].fio, dm->events[i].vol_fio) == 0) {
                        vIdx = j; break;
                    }
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
                        gcnew String(dm->events[i].date)
                    );
                }
                else {
                    grid->Rows->Add(
                        gcnew String(dm->events[i].vol_fio),
                        L"—", L"—",
                        gcnew String(dm->events[i].city),
                        gcnew String(dm->events[i].name),
                        gcnew String(buf),
                        gcnew String(dm->events[i].date)
                    );
                }
            }
            rpt->Controls->Add(grid);
            rpt->ShowDialog();
        }

        // ── Размер ХТ ─────────────────────────────────
        void OnHtSize(Object^ s, EventArgs^ e) {
            HtSizeForm^ dlg = gcnew HtSizeForm(dm->htVolunteers->GetSize());
            if (dlg->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;
            int sz = int::Parse(dlg->tbSize->Text->Trim());
            if (sz < 1) sz = 17;
            dm->RebuildStructures(sz);
            RefreshDebug();
            MessageBox::Show(L"Размер ХТ изменён на " + sz.ToString(), L"OK",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        // ── Вспомогательная кнопка ────────────────────
        ToolStripButton^ MakeBtn(String^ text, String^ tip) {
            ToolStripButton^ btn = gcnew ToolStripButton(text);
            btn->DisplayStyle = ToolStripItemDisplayStyle::Text;
            btn->ToolTipText = tip;
            btn->AutoSize = true;
            return btn;
        }

        // ══════════════════════════════════════════════
        // ИНИЦИАЛИЗАЦИЯ ФОРМЫ
        // ══════════════════════════════════════════════
        void InitializeComponent(void) {
            components = gcnew System::ComponentModel::Container();
            this->Text = L"Бюро добрых дел";
            this->Size = System::Drawing::Size(1280, 800);
            this->MinimumSize = System::Drawing::Size(1000, 600);

            // ToolStrip
            toolStrip = gcnew ToolStrip();
            btnLoad = MakeBtn(L"Загрузить", L"Загрузить из файлов");
            btnSave = MakeBtn(L"Сохранить", L"Сохранить в файлы");
            btnAdd = MakeBtn(L"Добавить", L"Добавить запись");
            btnDelete = MakeBtn(L"Удалить", L"Удалить запись");
            btnSearch = MakeBtn(L"Поиск", L"Поиск по ФИО + Город");
            btnFilter = MakeBtn(L"Фильтр", L"Фильтры");
            btnReport = MakeBtn(L"Отчёт", L"Сформировать отчёт");
            btnHtSize = MakeBtn(L"Размер ХТ", L"Задать размер хеш-таблицы");

            btnLoad->Click += gcnew EventHandler(this, &MainForm::OnLoad);
            btnSave->Click += gcnew EventHandler(this, &MainForm::OnSave);
            btnAdd->Click += gcnew EventHandler(this, &MainForm::OnAdd);
            btnDelete->Click += gcnew EventHandler(this, &MainForm::OnDelete);
            btnSearch->Click += gcnew EventHandler(this, &MainForm::OnSearch);
            btnFilter->Click += gcnew EventHandler(this, &MainForm::OnFilter);
            btnReport->Click += gcnew EventHandler(this, &MainForm::OnReport);
            btnHtSize->Click += gcnew EventHandler(this, &MainForm::OnHtSize);

            toolStrip->Items->Add(btnLoad);
            toolStrip->Items->Add(btnSave);
            toolStrip->Items->Add(gcnew ToolStripSeparator());
            toolStrip->Items->Add(btnAdd);
            toolStrip->Items->Add(btnDelete);
            toolStrip->Items->Add(gcnew ToolStripSeparator());
            toolStrip->Items->Add(btnSearch);
            toolStrip->Items->Add(gcnew ToolStripSeparator());
            toolStrip->Items->Add(btnFilter);
            toolStrip->Items->Add(gcnew ToolStripSeparator());
            toolStrip->Items->Add(btnReport);
            toolStrip->Items->Add(gcnew ToolStripSeparator());
            toolStrip->Items->Add(btnHtSize);

            // SplitMain
            splitMain = gcnew SplitContainer();
            splitMain->Dock = DockStyle::Fill;
            splitMain->Orientation = Orientation::Horizontal;
            splitMain->SplitterDistance = 420;
            splitMain->Panel1MinSize = 200;
            splitMain->Panel2MinSize = 150;

            // TabControl
            tabDirectories = gcnew TabControl();
            tabDirectories->Dock = DockStyle::Fill;
            tabVolunteers = gcnew TabPage(L"Волонтёры");
            tabEvents = gcnew TabPage(L"Мероприятия");

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

            tabVolunteers->Controls->Add(gridVolunteers);
            tabEvents->Controls->Add(gridEvents);
            tabDirectories->TabPages->Add(tabVolunteers);
            tabDirectories->TabPages->Add(tabEvents);
            splitMain->Panel1->Controls->Add(tabDirectories);

            // SplitDebug
            splitDebug = gcnew SplitContainer();
            splitDebug->Dock = DockStyle::Fill;
            splitDebug->Orientation = Orientation::Vertical;
            splitDebug->SplitterDistance = 500;

            lblHT = gcnew Label();
            lblHT->Text = L"  Хеш-таблица (отладка)";
            lblHT->Dock = DockStyle::Top; lblHT->Height = 22;
            lblHT->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
            lblHT->BackColor = System::Drawing::Color::FromArgb(255, 220, 185);

            rtbHashTable = gcnew RichTextBox();
            rtbHashTable->Dock = DockStyle::Fill; rtbHashTable->ReadOnly = true;
            rtbHashTable->Font = gcnew System::Drawing::Font(L"Consolas", 9);
            rtbHashTable->BackColor = System::Drawing::Color::FromArgb(255, 245, 230);
            rtbHashTable->Text = L"[ХТ пуста]";

            Panel^ panelHT = gcnew Panel();
            panelHT->Dock = DockStyle::Fill;
            panelHT->Controls->Add(rtbHashTable);
            panelHT->Controls->Add(lblHT);
            splitDebug->Panel1->Controls->Add(panelHT);

            lblBST = gcnew Label();
            lblBST->Text = L"  Красно-чёрное дерево (отладка)";
            lblBST->Dock = DockStyle::Top; lblBST->Height = 22;
            lblBST->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
            lblBST->BackColor = System::Drawing::Color::FromArgb(200, 230, 200);

            rtbBST = gcnew RichTextBox();
            rtbBST->Dock = DockStyle::Fill; rtbBST->ReadOnly = true;
            rtbBST->Font = gcnew System::Drawing::Font(L"Consolas", 9);
            rtbBST->BackColor = System::Drawing::Color::FromArgb(230, 245, 230);
            rtbBST->Text = L"[КЧД пусто]";

            Panel^ panelBST = gcnew Panel();
            panelBST->Dock = DockStyle::Fill;
            panelBST->Controls->Add(rtbBST);
            panelBST->Controls->Add(lblBST);
            splitDebug->Panel2->Controls->Add(panelBST);

            splitMain->Panel2->Controls->Add(splitDebug);
            this->Controls->Add(splitMain);
            this->Controls->Add(toolStrip);
        }
    };
}