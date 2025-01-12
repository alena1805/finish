#include "../includes.h"
#include "CustomButton.h"

CustomButton::CustomButton // Определение конструктора класса CustomButton
    (
        EMITS_BTN_SIGNALS _btn_sig, // Параметр для сигнала, который будет испускаться кнопкой
        QString& _ico_path // Путь к иконке для кнопки
        // QString& _btn_text
        ) :
    QPushButton(), btn_sig(_btn_sig) // Инициализация базового класса QPushButton и присвоение значения сигнала
{
    // set image
    if(_ico_path != "") // Проверка, что путь к иконке не пустой
    {
        this->ico_obj = new QPixmap(_ico_path); // Создание нового объекта QPixmap с заданным путем к изображению
        this->setIcon(*(this->ico_obj)); // Установка иконки для кнопки
        this->setIconSize(QSize(50, 50)); // Установка размера иконки
    }
    else
        this->ico_obj = nullptr; // Если путь пустой, указатель на иконку устанавливается в nullptr

    this->setMouseTracking(true); // Включение отслеживания мыши для кнопки (для выделения)
    this->setCheckable(true); // Установка кнопки как переключаемой (можно выделить/снять выделение)
    this->setCursor(Qt::PointingHandCursor); // Установка курсора в виде руки при наведении на кнопку

    connect
        (
            this,
            &QPushButton::clicked, // Сигнал нажатия кнопки
            this,
            &CustomButton::checked/*emit EMITS_BTN_SIGNALS::<signal>*/
            );
}

CustomButton::~CustomButton()
{
    delete this->ico_obj; // Освобождение памяти, занятой объектом QPixmap
}

inline QPixmap* CustomButton::get_ico_obj() // Получение указателя на объект иконки
{
    return this->ico_obj; // Возвращает указатель на объект иконки
}

void CustomButton::set_ico_obj(QPixmap* _px_map) // Установка нового объекта иконки
{
    delete this->ico_obj; // Освобождение старого объекта иконки
    this->ico_obj = _px_map; // Присвоение нового объекта иконки
}

EMITS_BTN_SIGNALS CustomButton::get_emitted_sig()
{
    return this->btn_sig;
}

void CustomButton::checked() // Слот, вызываемый при нажатии кнопки
{
    emit this->is_be_checked(this->btn_sig); // Испускание сигнала is_be_checked с текущим значением btn_sig
}

// =========

AugmentButton::AugmentButton // Определение конструктора класса AugmentButton
    (
        EMITS_BTN_SIGNALS _btn_sig, // Параметр для сигнала, который будет испускаться кнопкой
        QString& _btn_txt // Текст кнопки
        ) : btn_sig(_btn_sig),
    btn_txt(_btn_txt)
{
    connect
        (
            this,
            &QPushButton::clicked, // Сигнал нажатия кнопки
            this,
            &AugmentButton::checked // Слот, который будет вызван при нажатии
            );
}

AugmentButton::~AugmentButton() {}

void AugmentButton::checked() // Слот, вызываемый при нажатии кнопки
{
    emit this->is_be_checked(this->btn_sig);
}
