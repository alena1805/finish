#ifndef MENUBAR_H
#define MENUBAR_H
// Класс MenuBar: Это пользовательский виджет, который представляет собой панель меню.
// Он содержит кнопки, созданные на основе класса CustomButton.
#include "../includes.h"
#include "CustomButton.h"

class MenuBar : public QWidget // Определение класса MenuBar, наследующего QWidget
{
Q_OBJECT
private:
    QBoxLayout* p_menu_layout; // Указатель на объект QBoxLayout для размещения кнопок в меню
    QList<CustomButton*>* p_items_list; // Список указателей на объекты CustomButton

    QSize* p_size; // Указатель на объект QSize, представляющий размер меню
    QSize* p_position; // Указатель на объект QSize, представляющий позицию меню

public:
    MenuBar // Конструктор класса MenuBar
    (
        QSize*, // Указатель на размер
        QSize*, // Указатель на позицию
        bool _orient_layout = true/*true -> vertical*/, // Ориентация макета (по умолчанию вертикальная)
        QWidget* _parent = 0
        // int _counter = 0
    );
    ~MenuBar();

    void appendObject(EMITS_BTN_SIGNALS, QString, QString); // Метод для добавления объекта в меню с двумя параметрами
    void appendObject(EMITS_BTN_SIGNALS, QString);  // Метод для добавления объекта в меню с одним параметром
    QList<CustomButton*>* getObjectsList(); // Метод для получения списка объектов
    QBoxLayout* get_layout(); // Метод для получения макета

protected:
    // show all buttons
    void paintEvent(QPaintEvent*) override
    {
        QPainter painter(this); // Создание объекта рисовальщика

        for // Проход по всем элементам списка и их отображение
        (
            auto beg = this->p_items_list->begin();
            beg != this->p_items_list->end();
            ++beg
        )
        {
            (*beg)->show(); // Показываем каждую кнопку
        }
    }

signals:
    void sig_transmission(EMITS_BTN_SIGNALS); // Сигнал для передачи данных

public slots:
    void sig_distrib_handler(EMITS_BTN_SIGNALS); // Слот для обработки сигнала
};


#endif // MENUBAR_H
