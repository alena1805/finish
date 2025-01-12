#include "mainwindow.h"

#include <QApplication>
// Основная функция
int main(int argc, char *argv[])
{
    QApplication app_master(argc, argv); // Создание экземпляра QApplication, который управляет управлением приложением и его жизненным циклом

// Создание экземпляра виджета и передача пути к базе данных
    Widget* mainwgd = new Widget( "C:/Users/Алёнка/Documents/untitled8/build/Desktop_Qt_6_8_1_MinGW_64_bit-Debug/test.db");
    mainwgd->show(); // Отображение главного окна виджета


    return app_master.exec(); // Запуск главного цикла обработки событий приложения
}
