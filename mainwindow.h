#ifndef WIDGET_H
#define WIDGET_H

#include "includes.h"
#include "menu_bar/CustomButton.h"
#include "menu_bar/MenuBar.h"
#include "menu_bar/TopBar.h"
#include "table_view_model/DBViewer.h"
// этот заголовочный файл определяет класс виджета с основными
// компонентами пользовательского интерфейса и необходимыми зависимостями.
class Widget : public QWidget
{
    Q_OBJECT

private:
    // CustomButton* ctm_btm;
    // QVBoxLayout* layout;
    MenuBar* p_mBar; // Указатель на объект MenuBar (панель меню)
    TopBar* p_topBar; // Указатель на объект TopBar (верхняя панель инструментов)
    QPalette* p_backColor; // Указатель на объект QPalette для настройки цветовой схемы виджета

public:
    Widget(QString, QWidget *parent = nullptr); // Конструктор класса Widget, принимающий строку и указатель на родительский виджет
    ~Widget();
};
#endif // WIDGET_H
