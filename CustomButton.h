#ifndef CUSTOMBUTTON_H // Защита от множественного включения файла
#define CUSTOMBUTTON_H

#include "../includes.h" // Подключение необходимых заголовков

class CustomButton : public QPushButton
{
    Q_OBJECT

private:
    QPixmap* ico_obj; // Указатель на объект QPixmap (иконка кнопки)
    EMITS_BTN_SIGNALS btn_sig; // Переменная для хранения сигнала
    // QString btn_text;

protected:
    virtual void paintEvent(QPaintEvent*) override
    {
        QPainter painter;

        // смещения для масштабирования изображения в виде эллипса
        int sqr_offset = 10;
        int sqr_volume = 20;

        // Получение прямоугольника кнопки
        QRect menuItem_draw_ellipse
            (
                this->rect().x(),
                this->rect().y(),
                this->rect().width(),
                this->rect().height()
                );
        // draw grey rect if enable // Рисование фона кнопки
        painter.begin(this);
        {
            if(this->isChecked()) // Если кнопка нажата
                painter.setBrush(QBrush(Qt::black)); //Установить черный цвет
            else if(this->underMouse() && !this->isChecked() ) // Если мышь над кнопкой и она не нажата
            {
                painter.setBrush(QBrush(Qt::lightGray)); // Установить светло-серый цвет
            }
            else
                painter.setBrush(QBrush(Qt::white)); // Установить белый цвет
            painter.drawEllipse // Рисование овала, представляющего кнопку
                (
                    menuItem_draw_ellipse.x(),
                    menuItem_draw_ellipse.y(),
                    menuItem_draw_ellipse.width(),
                    menuItem_draw_ellipse.height()
                    );
        }
        painter.end();
        if(this->ico_obj != nullptr) // Если иконка задана, рисуем её
        {
            painter.begin(this);
            painter.drawPixmap
                (
                    QRect
                    (
                        menuItem_draw_ellipse.x()+sqr_offset,
                        menuItem_draw_ellipse.y()+sqr_offset,
                        menuItem_draw_ellipse.width()-sqr_volume,
                        menuItem_draw_ellipse.height()-sqr_volume
                        ),
                    *(this->ico_obj)
                    );
            painter.end();
        }
    }

public:
    CustomButton // Конструктор с параметрами
        (
            EMITS_BTN_SIGNALS,
            QString& _ico_path
            // QString& _btn_text
            );
    ~CustomButton();

    QPixmap* get_ico_obj(); // Метод для получения указателя на иконку
    void set_ico_obj(QPixmap*); // Метод для установки иконки
    EMITS_BTN_SIGNALS get_emitted_sig(); // Метод для получения сигнала

public slots:
    void checked();

signals:
    void is_be_checked(EMITS_BTN_SIGNALS);
};

// ================

class AugmentButton : public QPushButton
{
    Q_OBJECT
private:
    EMITS_BTN_SIGNALS btn_sig;
    QString btn_txt;

public:
    AugmentButton(EMITS_BTN_SIGNALS, QString&);  // Конструктор с параметрами
    ~AugmentButton();

public slots:
    void checked();

signals:
    void is_be_checked(EMITS_BTN_SIGNALS); // Сигнал, который будет испускаться при проверке кнопки

};

#endif // CUSTOMBUTTON_H
