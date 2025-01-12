#ifndef DBTABLEVIEWMODEL_H
#define DBTABLEVIEWMODEL_H

#include "../includes.h"
// класс DBTableViewModel представляет собой расширение стандартного представления таблицы в Qt,
// добавляя функциональность для работы с динамическими данными и управления ими через сигналы и слоты.

class DBTableViewModel : public QTableView // Определение класса DBTableViewModel, наследующего QTableView
{
    Q_OBJECT
private:
    QMap<EMITS_BTN_SIGNALS, QString>* p_link_sig_names; // Указатель на карту, связывающую сигналы с их именами
    QString* current_table; // Указатель на строку, представляющую текущую таблицу

public:
    DBTableViewModel // Конструктор класса DBTableViewModel, принимающий указатель на карту сигналов и указатель на родительский виджет
        (
            QMap<EMITS_BTN_SIGNALS, QString>*,
            QWidget* _parent = nullptr
            );

    ~DBTableViewModel();

    void set_model(EMITS_BTN_SIGNALS); // Метод для установки модели представления на основе сигнала
    void apeendConnect(EMITS_BTN_SIGNALS, QString); // Метод для добавления соединения между сигналом и именем
    void to_resize(); // Метод для изменения размера представления
    void exec_filter(const QString&); // Метод для выполнения фильтрации данных
    void remove_row(const QString&); // Метод для удаления строки по её идентификатору
    void add_new_row(); // Метод для добавления новой строки в таблицу
};


#endif // DBTABLEVIEWMODEL_H
