#include "mainwindow.h"
Widget::Widget(QString _db_source, QWidget *parent)
    : QWidget(parent)
{
    // setup color pallete for main window background
    this->setAutoFillBackground(true); // Установка фона для главного окна

    this->p_backColor = new QPalette; // Создаем новый объект QPalette
    this->p_backColor->setColor(this->backgroundRole(), Qt::white); //цвет фона белый
    this->setPalette(*p_backColor); // Применяем палитру к виджету

    // settup mainwindow
    // this->showMaximized();
    this->setBaseSize(500, 1000); // Устанавливаем базовый размер окна

    // настройка области кнопок
    this->p_mBar = new MenuBar
        (
            new QSize(80, 300), // Размер меню
            new QSize(10, 20), // Размер кнопок
            true,
            this
            );
    { // Добавление кнопок в меню
        this->p_mBar->appendObject(EMITS_BTN_SIGNALS::SIG0, ":/ico/users1_cleaned.png", "");
        this->p_mBar->appendObject(EMITS_BTN_SIGNALS::SIG1, ":/ico/books1_cleaned.png", "");
        this->p_mBar->appendObject(EMITS_BTN_SIGNALS::SIG2, ":/ico/orders1_cleaned.png", "");
        this->p_mBar->appendObject(EMITS_BTN_SIGNALS::SIG3, ":/ico/feedback1_cleaned.png", "");
    }
    /* Сигналы кнопок были подключены к обработчику сигналов меню */
    this->p_mBar->show(); // Отображаем меню


    // Настройка верхнего меню
    this->p_topBar = new TopBar
        (
            new QSize(
                this->p_mBar->size().width(), // Ширина верхнего меню равна ширине меню
                this->p_mBar->pos().y() // Положение по оси Y соответствует положению меню
                ),
            new QSize(
                this->width()-this->p_mBar->size().width(), // Ширина верхнего меню
                60 // Высота верхнего меню
                ),
            this
            );
    this->p_topBar->show(); // Отображаем верхнее меню


    // Настройка области просмотра базы данных
    /* Определяем запросы для режима просмотра */
    QMap<QString, QString>* p_queries = nullptr;
    /* Определяем связи сигналов с таблицами для переключателя таблиц */
    QMap<EMITS_BTN_SIGNALS, QString>* p_links_sig_table = new QMap<EMITS_BTN_SIGNALS, QString>;
    {
        p_links_sig_table->insert(EMITS_BTN_SIGNALS::SIG0, "readers");
        p_links_sig_table->insert(EMITS_BTN_SIGNALS::SIG1, "books");
        p_links_sig_table->insert(EMITS_BTN_SIGNALS::SIG2, "orders");
        p_links_sig_table->insert(EMITS_BTN_SIGNALS::SIG3, "feedbacks");
    }
    DBViewer* p_db_viewer = new DBViewer
        (
            _db_source, // Источник базы данных
            p_queries,  // Запросы
            p_links_sig_table, // Связи сигналов с таблицами
            // new QSize(this->width(), this->height()),
            new QSize // Размер области просмотра базы данных
            (
                1500,
                900
                ),
            new QSize
            ( // Размер области для отображения данных
                this->p_mBar->width(),
                this->p_topBar->height()
                ), // not optimazed
            QBoxLayout::Direction::TopToBottom,
            this
            );

    connect // choose table
        (
            this->p_mBar,
            &MenuBar::sig_transmission,
            p_db_viewer,
            &DBViewer::table_swapper
            );

    connect // filter
        (
            this->p_topBar,
            &TopBar::sig_filter_data_transmitter,
            p_db_viewer,
            &DBViewer::exec_filter
            );

    connect // filter for delete row
        (
            this->p_topBar,
            &TopBar::sig_delete_rownum_transmitter,
            p_db_viewer,
            &DBViewer::remove_row
            );

    connect
        (
            this->p_topBar,
            &TopBar::sig_add_new_row,
            p_db_viewer,
            &DBViewer::add_new_row
            );

    p_db_viewer->show();
}


Widget::~Widget()
{
}
