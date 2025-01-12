#include "../includes.h"
#include "MenuBar.h"

// класс MenuBar, который управляет набором кнопок в виде горизонтального или вертикального меню.
//Он позволяет добавлять кнопки и обрабатывать их события, обеспечивая взаимодействие с пользователем через сигналы и слоты.

MenuBar::MenuBar
(
    QSize* _size,
    QSize* _pos,
    // QPair<int, int>* _iter_buttons_cluster,
    bool _orient_layout, // Параметр для определения ориентации компоновки (горизонтальная или вертикальная)
    QWidget* _parent
    ) :
    QWidget(_parent), // Инициализация базового класса QWidget с указателем на родительский виджет
    p_size(_size),
    p_position(_pos)
{
 // Выбор компоновки в зависимости от параметра _orient_layout
    if(_orient_layout)
        this->p_menu_layout = new QVBoxLayout; // Вертикальная компоновка
    else
        this->p_menu_layout = new QHBoxLayout; // Горизонтальная компоновка

    // this->p_menu_layout->addWidget(this);
    this->setLayout(this->p_menu_layout); // Установка компоновки для меню
    this->setGeometry  // Установка геометрии (позиции и размера) для меню
    (
        _pos->width(), // X-координата (ширина позиции)
        _pos->height(), // Y-координата (высота позиции)
        _size->width(), // ширина меню
        _size->height() //высота меню
    );

    this->p_items_list = new QList<CustomButton*>; // Инициализация списка кнопок
}


MenuBar::~MenuBar()
{ // Освобождение памяти
    delete this->p_size;
    delete this->p_position;
    delete this->p_menu_layout;
    delete this->p_items_list;
}


void MenuBar::appendObject // Метод для добавления объекта типа CustomButton в меню
(
    EMITS_BTN_SIGNALS _btn_sig,
    QString _p_obj, /*for rvalue arguments */ // Путь к изображению для кнопки
    QString _p_txt //текст для кнопки
)
{
    CustomButton* tmp_object = new CustomButton(_btn_sig, _p_obj); // Создание новой кнопки CustomButton
    this->p_menu_layout->addWidget(tmp_object); // Добавление кнопки в компоновку меню
    this->p_items_list->append(tmp_object); // Добавление кнопки в список кнопок

    connect // Подключение сигнала is_be_checked к слоту sig_distrib_handler для обработки события нажатия на кнопку
    (
        tmp_object,
        &CustomButton::is_be_checked,
        this,
        &MenuBar::sig_distrib_handler
    );
}

void MenuBar::appendObject // Перегрузка метода для добавления объекта типа AugmentButton в меню
(
    EMITS_BTN_SIGNALS _btn_sig, // Сигнал, который будет испускаться кнопкой
    QString _btn_txt // Текст для кнопки
)
{
    AugmentButton* tmp_object = new AugmentButton(_btn_sig, _btn_txt); // Создание новой кнопки AugmentButton

    // set white color on button
    tmp_object->setPalette(QPalette(Qt::white)); //цвет
    tmp_object->setText(_btn_txt); //текст
    this->p_menu_layout->addWidget(tmp_object); // Добавление кнопки в компоновку меню

    connect // Подключение сигнала is_be_checked к слоту sig_distrib_handler для обработки события нажатия на кнопку
    (
        tmp_object,
        &AugmentButton::is_be_checked,
        this,
        &MenuBar::sig_distrib_handler
    );
}

QList<CustomButton*>* MenuBar::getObjectsList() // Метод для получения списка объектов (кнопок) в меню
{
    return this->p_items_list; // Возвращает указатель на список кнопок
}

QBoxLayout* MenuBar::get_layout() // Метод для получения компоновки меню
{
    return this->p_menu_layout; // Возвращает указатель на компоновку меню
}

void MenuBar::sig_distrib_handler(EMITS_BTN_SIGNALS _clicked_btn_sig) // Метод-обработчик сигнала нажатия на кнопку
{
    for
    (
        int iter_btn = 0;
        iter_btn != this->p_items_list->size();
        ++iter_btn
    )
    {
        CustomButton* tmp_obj = this->p_items_list->at(iter_btn); // Получение текущей кнопки из списка
        if
        (
            tmp_obj->get_emitted_sig() != _clicked_btn_sig // Если сигнал текущей кнопки не равен сигналу нажатой кнопки
        )
        {
            tmp_obj->setChecked(false); // Снять выделение с кнопки
        }
    }
    this->update(); // Обновление виджета

    emit this->sig_transmission(_clicked_btn_sig); // Испускание сигнала передачи с идентификатором нажатой кнопки
}
