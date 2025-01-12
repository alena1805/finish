#ifndef DBVIEWER_H
#define DBVIEWER_H

#include "../includes.h"
#include "DBTableViewModel.h"
// класс DBViewer служит основным интерфейсом для взаимодействия с данными из базы данных,
// предоставляя пользователю возможность просматривать, фильтровать и изменять данные в виде таблицы.
class DBViewer : public QWidget // Определение класса DBViewer, наследующего QWidget
{
    Q_OBJECT
private:
    QBoxLayout* p_layout; // Указатель на компоновщик для управления размещением виджетов
    DBTableViewModel* p_models_views; // Указатель на объект модели представления таблицы
    QMap<QString, QString>* p_view_mod_queries;  // Указатель на карту, связывающую представления с запросами к базе данных

    // TABLE_VIEW_MOD view_mod;
    EMITS_BTN_SIGNALS view_mod; // Переменная для хранения текущего режима отображения

    QSize* p_size; // Указатель на объект QSize для хранения размера виджета
    QSize* p_position; // Указатель на объект QSize для хранения позиции виджета

public:
    DBViewer // Конструктор класса DBViewer, принимающий различные параметры для инициализации
        (
            QString&, // DB resource // Ресурс базы данных
            QMap<QString, QString>*, // table<->query links // Связи между таблицами и запросами
            QMap<EMITS_BTN_SIGNALS, QString>*, // Связь между сигналами и их строковыми представлениями
            QSize*,
            QSize*,
            QBoxLayout::Direction,  // Направление компоновки
            QWidget* _parent = 0 // Указатель на родительский виджет (по умолчанию nullptr)
            );
    ~DBViewer();

public:
    void set_view_mod(EMITS_BTN_SIGNALS); // Метод для установки режима отображения
    void clean_layout(); // Метод для очистки компоновки виджетов

public slots:
    void table_swapper(EMITS_BTN_SIGNALS); // Слот для переключения таблицы
    void view_mod_swapper(EMITS_BTN_SIGNALS); // Слот для переключения режима отображения

    void exec_filter(const QString&); // Слот для выполнения фильтрации данных
    void add_new_row(); // Слот для добавления новой строки в таблицу
    void remove_row(const QString&); // Слот для удаления строки из таблицы
};

#endif // DBVIEWER_H
