#include "DBTableViewModel.h"
//Класс DBTableViewModel предоставляет удобный интерфейс для работы с данными в виде таблицы.
//Он позволяет устанавливать модель данных, применять фильтры, добавлять и удалять строки,
// а также автоматически изменять размеры колонок.

DBTableViewModel::DBTableViewModel
    (
        QMap<EMITS_BTN_SIGNALS, QString>* _link_sig_names, // Указатель на карту сигналов
        QWidget* _parent
        ) : QTableView(_parent), p_link_sig_names(_link_sig_names) // Инициализация базового класса QTableView и указателя на карту сигналов
{
    this->setPalette(QPalette(Qt::white)); // Установка палитры (цвета) для виджета в белый цвет
    this->current_table = new QString(""); //пустой строкой
}

DBTableViewModel::~DBTableViewModel() // Деструктор
{
    delete this->p_link_sig_names; // Освобождение памяти, занятой картой сигналов
}

void DBTableViewModel::set_model // Метод для установки модели данных в таблице
    (
        EMITS_BTN_SIGNALS _emitted_sig
        )
{
    *(this->current_table) = this->p_link_sig_names->lowerBound(_emitted_sig).value(); // Получение имени таблицы по сигналу
    QSqlTableModel* tmp_rel_mdl = new QSqlTableModel; // Создание временной модели данных
    tmp_rel_mdl->setTable // Установка таблицы для модели
        (
            *(this->current_table)
            );
    tmp_rel_mdl->select();


    this->setModel(tmp_rel_mdl); // Установка текущей модели для представления
}

void DBTableViewModel::exec_filter(const QString& _filter) // Метод для применения фильтра к данным в таблице
{
    QSqlTableModel* tmp_rel_mdl = new QSqlTableModel; // Создание временной модели данных
    tmp_rel_mdl->setTable // Установка таблицы для модели
        (
            *(this->current_table)
            );
    tmp_rel_mdl->setFilter(_filter); // Установка фильтра
    tmp_rel_mdl->select(); // Загрузка данных с применением фильтра

    this->setModel(tmp_rel_mdl); // Установка текущей модели для представления
}

void DBTableViewModel::add_new_row() // Метод для добавления новой строки в таблицу
{
    QSqlTableModel* tmp_rel_mdl = new QSqlTableModel; // Создание временной модели данных
    tmp_rel_mdl->setTable
        (
            *(this->current_table)
            );

    QSqlRecord rec = tmp_rel_mdl->record(0); // Получение записи (строки) по индексу 0

    int index_row = 0; // Индекс строки, в которую будет добавлена новая запись
    tmp_rel_mdl->insertRows(index_row, 1); // Вставка новой строки в модель

    for(int col_ind = 0; col_ind < tmp_rel_mdl->columnCount(); ++col_ind)
    {
        tmp_rel_mdl->setData(tmp_rel_mdl->index(index_row, col_ind), "0"); // Установка значения "0" для каждой колонки новой строки
    }

    if(!tmp_rel_mdl->submitAll())
    {
        qDebug("create new row error!"); // Вывод сообщения об ошибке при добавлении строки
    }
    this->exec_filter(""); // may be not work
}

void DBTableViewModel::remove_row(const QString& _filter) // Метод для удаления строк из таблицы по фильтру
{
    QSqlTableModel* tmp_rel_mdl = new QSqlTableModel; // Создание временной модели данных
    tmp_rel_mdl->setTable
        (
            *(this->current_table) // Установка таблицы для модели
            );
    tmp_rel_mdl->setFilter(_filter); // Установка фильтра
    tmp_rel_mdl->select(); // Загрузка данных с применением фильтра
    tmp_rel_mdl->removeRows(0, tmp_rel_mdl->rowCount()); // Удаление всех строк, соответствующих фильтру
    tmp_rel_mdl->submitAll(); // Подтверждение изменений в базе данных

    delete tmp_rel_mdl; //освобождаем память
    tmp_rel_mdl = new QSqlTableModel; // Создание новой временной модели данных
    tmp_rel_mdl->setTable // Установка таблицы для новой модели
        (
            *(this->current_table)
            );
    tmp_rel_mdl->select(); // Загрузка данных из таблицы без фильтрации
    this->setModel(tmp_rel_mdl); // Установка текущей модели для представления
}

void DBTableViewModel::to_resize() // Метод для автоматического изменения размера колонок в таблице
{
    if(this->model() != NULL)
    {
        int colCount = this->model()->columnCount(); // Получение количества колонок в модели
        for(int colNum = 0; colNum < colCount; ++colNum)
        {
            this->resizeColumnToContents(colNum); // Изменение размера колонки по содержимому
        }
    }
}
