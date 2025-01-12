#include "TopBar.h"
//два класса: InputArea, который представляет собой область ввода текста,
// и TopBar, который является верхней панелью управления с меткой, несколькими полями ввода и кнопкой.
//Эти классы взаимодействуют через сигналы и слоты, что позволяет передавать данные между элементами интерфейса

InputArea::InputArea(QString _area_txt) // Определение класса InputArea
{
    this->p_ledit = new QLineEdit(_area_txt); // Создание нового поля ввода QLineEdit с текстом _area_txt
    this->setBuddy(this->p_ledit);

    connect // Подключение сигнала нажатия клавиши Enter к слоту обработки нажатия
        (
            this->p_ledit,
            &QLineEdit::returnPressed,
            this,
            &InputArea::slot_enter_pressed // Слот, который будет вызван при нажатии Enter
            );
}

InputArea::~InputArea()
{}

QLineEdit* InputArea::get_edit_area() // Метод для получения указателя на поле ввода
{
    return this->p_ledit; // Возвращает указатель на поле ввода
}

void InputArea::slot_enter_pressed() // Слот, обрабатывающий нажатие клавиши Enter
{
    emit this->sig_get_text(this->p_ledit->text()); // Испускает сигнал с текстом из поля ввода
}

// ==============

TopBar::TopBar // Определение класса TopBar
    (
        QSize* _pos, //позиция-указатель
        QSize* _size, //рамер
        QWidget* _parent //родительский виджет
        ) :
    QWidget(_parent), // Инициализация базового класса QWidget и указателей на размер и позицию
    pos{_pos},
    size{_size}
{
    this->p_curr_tname = new QLabel("test"); // Создание метки QLabel с текстом "test"
    this->p_filter = new InputArea("Enter filter"); // Создание области ввода для фильтрации
    this->p_delete_line = new InputArea("Enter row num for delete"); // Создание области ввода для удаления строки
    this->p_add_new_row = new QPushButton("Add row"); //для добавления

    // setup layout
    this->p_layout = new QHBoxLayout; // Создание горизонтальной компоновки

    this->p_layout->addWidget(this->p_curr_tname);

    this->p_layout->addWidget(this->p_filter); // Добавление области ввода фильтра в компоновку
    this->p_layout->addWidget(this->p_filter->get_edit_area()); // Добавление виджета для ввода фильтра в компоновку

    this->p_layout->addWidget(this->p_delete_line); // Добавление области ввода для удаления строки в компоновку
    this->p_layout->addWidget(this->p_delete_line->get_edit_area()); // Добавление виджета для ввода номера строки в компоновку

    this->p_layout->addWidget(this->p_add_new_row); // Добавление кнопки "Add row" в компоновку

    this->setLayout(this->p_layout); // Установка компоновки для TopBar

    // setup geometry
    this->setGeometry
        (
            _pos->width(), // X-координата (ширина позиции)
            _pos->height(),  // Y-координата (высота позиции)
            _size->width(), //ширина
            _size->height() //высота
            );

    connect // filter // Подключение сигналов от областей ввода к слотам TopBar для обработки текста
        (
            this->p_filter,
            &InputArea::sig_get_text,
            this,
            &TopBar::slot_filter_transmitter
            );

    connect
        (
            this->p_delete_line,
            &InputArea::sig_get_text, // Сигнал от p_delete_line при получении текста
            this,
            &TopBar::slot_delete_rownum_transmitter // Слот для передачи номера строки в TopBar
            );

    connect
        (
            this->p_add_new_row,
            &QPushButton::clicked, // Сигнал от кнопки при её нажатии
            this,
            &TopBar::slot_add_new_row // Слот для обработки нажатия кнопки добавления новой строки
            );
}

TopBar::~TopBar() {}

void TopBar::slot_set_tname(QString& _tname) // Слот для изменения имени текущего элемента
{
    emit this->sig_change_tname(_tname);
}

void TopBar::slot_filter_transmitter(const QString& _filter) // Слот для передачи фильтра данных
{
    emit this->sig_filter_data_transmitter(_filter);
}

void TopBar::slot_delete_rownum_transmitter(const QString& _rownum) // Слот для передачи номера строки для удаления
{
    emit this->sig_delete_rownum_transmitter(_rownum);
}

void TopBar::slot_add_new_row() // Слот для обработки добавления новой строки
{
    emit this->sig_add_new_row();
}
