#ifndef INCLUDES_H
#define INCLUDES_H

#include <QPair>

#include <QtCore>
#include <QObject>
#include <QApplication>

#include <QWidget>
#include <QPixmap>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPainter>

#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>

#include <QtSql>
#include <QTableView>
//этот заголовочный файл служит основой для подключения необходимых классов и определения сигналов,
// которые будут использоваться в приложении на основе Qt.
enum class EMITS_BTN_SIGNALS
{
    // Сигналы для левого вертикального меню
    SIG0,
    SIG1,
    SIG2,
    SIG3,
    // Сигналы для верхнего горизонтального меню (режимы отображения)
    EDIT,
    ONLY_VIEW,
};

#endif // INCLUDES_H
