#ifndef DATE_SELECT_DIALOG_HPP
#define DATE_SELECT_DIALOG_HPP

#include <QDialog>
#include "main_window.hpp"

class DaySelectGrid;

/// Klasa implementująca okno wyboru daty
///
/// Obiekt tej klasy jest tworzony przez klasę MainWindow, po kliknięciu na przycisk
/// wyświetlający bieżącą datę.
class DateSelectDialog : public QDialog {
private:
    int year, month;
    DaySelectGrid *grid = nullptr;

    void setGrid();
public:
    /// Konstruktor
    ///
    /// Parametry `_year` i `_month` określają bieżący rok i miesiąc. Są potrzebne do inicjalizacji
    /// okna wyboru daty.
    DateSelectDialog(int _year, int _month, QWidget *parent = nullptr);
    /// Metoda służąca do wyboru daty
    ///
    /// Ustawia ona bieżącą datę wywołując metodę MainWindow::setDate() dla globalnego obiektu `main_window`,
    /// po czym zamyka okno wyboru daty.
    /// @param d Określa wybrany dzień.
    void selectDate(int d);
Q_OBJECT
private slots:
    void onYearChange(int y);
    void onMonthChange(int m);
};

/// Klasa implementująca siatkę rozmieszczenia dni w miesiącu
///
/// Układa przyciski reprezentujące kolejne dni danego miesiąca w siatkę,
/// której kolumny reprezentują poszczególne dni tygodnia.
class DaySelectGrid : public QWidget {
public:
    /// Konstruktor
    /// 
    /// @param y Rok.
    /// @param m Miesiąc.
    /// @param parent Obiekt klasy DateSelectDialog - rodzic.
    DaySelectGrid(int y, int m, DateSelectDialog *parent = nullptr);
Q_OBJECT
private slots:
    void select();
};

#endif