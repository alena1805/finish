#ifndef TOPBAR_H
#define TOPBAR_H

#include "../includes.h"

//код определяет интерфейс панели инструментов с элементами управления для фильтрации данных,
//удаления строк и добавления новых строк.

class InputArea : public QLabel
{
    Q_OBJECT
private:
    QLineEdit* p_ledit; // Указатель на объект QLineEdit для ввода текста

public:
    InputArea(QString); // Конструктор класса InputArea, принимающий строку для инициализации
    ~InputArea();
    QLineEdit* get_edit_area(); // Метод для получения указателя на область редактирования

public slots:
    void slot_enter_pressed(); // Слот, вызываемый при нажатии клавиши Enter

signals:
    void sig_get_text(const QString&); // Сигнал для передачи текста
};


class TopBar : public QWidget // Определение класса TopBar, наследующего QWidget
{
    Q_OBJECT
private:
    QHBoxLayout* p_layout; // Указатель на объект QHBoxLayout для горизонтального размещения элементов

    QLabel* p_curr_tname; // Указатель на текущую метку (имя таблицы)
    InputArea* p_filter; // Указатель на область ввода фильтрации
    InputArea* p_delete_line; // Указатель на область ввода для удаления строки
    QPushButton* p_add_new_row; // Указатель на кнопку добавления новой строки

    QSize* pos; // Указатель на объект QSize, представляющий позицию панели
    QSize* size; // Указатель на объект QSize, представляющий размер панели

public:
    TopBar // Конструктор класса TopBar, принимающий указатели на позицию и размер
        (
            QSize* _pos,
            QSize* _size,
            QWidget* _parent = nullptr
            );
    ~TopBar();

public slots:
    void slot_set_tname(QString&); // Слот для установки имени таблицы
    void slot_filter_transmitter(const QString&);  // Слот для передачи фильтра
    void slot_delete_rownum_transmitter(const QString&); // Слот для передачи номера строки для удаления
    void slot_add_new_row(); // Слот для добавления новой строки

signals:
    void sig_change_tname(const QString&); // Сигнал для изменения имени таблицы
    void sig_filter_data_transmitter(const QString&); // Сигнал для передачи данных фильтрации
    void sig_delete_rownum_transmitter(const QString&); // Сигнал для передачи номера строки для удаления
    void sig_add_new_row(); // Сигнал для добавления новой строки
};


#endif // TOPBAR_H
