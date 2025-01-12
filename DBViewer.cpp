#include "../includes.h"
#include "DBViewer.h"


DBViewer::DBViewer
    (
        QString& _db_soruce, // Путь к источнику базы данных
        QMap<QString, QString>* _table_query_links, // Ссылки между таблицами и запросами
        QMap<EMITS_BTN_SIGNALS, QString>* _link_sig_table, // Ссылки сигналов на таблицы
        QSize* _size, // Размер виджета
        QSize* _position,
        QBoxLayout::Direction _layout_format, // Формат компоновки (горизонтальная или вертикальная)
        QWidget* _parent
        ) :
    QWidget(_parent),
    p_size(_size), // Инициализация указателя на размер
    p_position(_position) //на позицию
{
    // make layout
    this->p_layout = new QBoxLayout(_layout_format); // Создание нового объекта компоновки с заданным форматом
    this->setLayout(this->p_layout); // Установка созданной компоновки как текущей для виджета
    this->setGeometry
        (
            _position->width(),
            _position->height(),
            _size->width(),
            _size->height()
            );

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); // Подключение к базе данных SQLite и Добавление драйвера базы данных SQLite
    db.setDatabaseName(_db_soruce); // Установка имени базы данных
    if(!db.open())
    {
        qDebug("Error database open"); // Вывод сообщения об ошибке при открытии базы данных
    }

    // add models view to layout
    this->p_models_views = new DBTableViewModel(_link_sig_table, this); // Создание объекта модели представления таблицы
    this->p_models_views->setGeometry
        (
            _position->width(),
            _position->height(),
            _size->width(),
            _size->height()
            );
    this->p_layout->addWidget(this->p_models_views);


    /*
        TEST SECTION
    */
}

DBViewer::~DBViewer() //освобождение памяти
{
    delete this->p_position;
    delete this->p_size;
}

void DBViewer::set_view_mod(EMITS_BTN_SIGNALS _view_mod) // Установка режима представления
{
    this->view_mod = _view_mod; // Присваивание нового значения режиму представления
}

void DBViewer::table_swapper(EMITS_BTN_SIGNALS _emitted_sig) // Переключение таблицы в зависимости от сигнала
{
    this->p_models_views->set_model(_emitted_sig); // Установка модели в зависимости от сигнала
    this->p_models_views->to_resize(); //изменение размера
}

void DBViewer::view_mod_swapper(EMITS_BTN_SIGNALS _view_mod) // Переключение режима представления в зависимости от сигнала
{
    switch (_view_mod) // Проверка режима представления
    {
    case EMITS_BTN_SIGNALS::EDIT: // Если режим редактирования
        this->p_models_views->to_resize(); //изменение размера
        this->p_models_views->show(); //отображение модели
        break;
    case EMITS_BTN_SIGNALS::ONLY_VIEW: // Если режим только просмотра
        this->p_models_views->hide(); //скрытие режима представления
        break;
    default: // Если режим не выбран
        this->p_layout->addWidget
            (
                new QLabel( // Добавление метки с подсказкой о выборе режима представления
                    "THE DISPLAY OPTION IS NOT SELECTED\nHint: buttons 'View' and 'Edit' at the top")
                );
        break;
    }
}

void DBViewer::exec_filter(const QString& _filter) // Применение фильтра к данным
{
    this->p_models_views->exec_filter(_filter); // Применение фильтра
    this->p_models_views->to_resize(); // Изменение размера
}

void DBViewer::add_new_row() // Добавление новой строки в модель
{
    this->p_models_views->add_new_row(); // Вызов метода добавления новой строки
    this->p_models_views->to_resize();
}

void DBViewer::remove_row(const QString& _filter) // Удаление строки из модели представления по фильтру
{
    this->p_models_views->remove_row(_filter); // Вызов метода удаления строки
    this->p_models_views->to_resize();
}
