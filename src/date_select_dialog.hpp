#ifndef DATE_SELECT_DIALOG_HPP
#define DATE_SELECT_DIALOG_HPP

#include <QDialog>
#include "main_window.hpp"

class DaySelectGrid;

class DateSelectDialog : public QDialog {
private:
    int year, month;
    DaySelectGrid *grid = nullptr;

    void setGrid();
public:
    DateSelectDialog(int _year, int _month, QWidget *parent = nullptr);
    void selectDate(int d);
Q_OBJECT
private slots:
    void onYearChange(int y);
    void onMonthChange(int m);
};

class DaySelectGrid : public QWidget {
public:
    DaySelectGrid(int y, int m, DateSelectDialog *parent = nullptr);
Q_OBJECT
private slots:
    void select();
};

#endif