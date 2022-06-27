#ifndef EVENT_ADD_EDIT_WINDOW_HPP
#define EVENT_ADD_EDIT_WIDNOW_HPP

#include <QDialog>
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QSpinBox>
#include "event.hpp"
#include "main_window.hpp"

/// Klasa implementująca pole wyboru daty przy tworzeniu lub edycji wydarzenia.
class DateSelectSpinBox : public QSpinBox {
private:
    int year, month;
public:
    /// Konstruktor
    DateSelectSpinBox(QWidget *parent = nullptr);
Q_OBJECT
public slots:
    /// Ustawia zasięg w zależności od miesiąca
    ///
    /// Zasięg jest ustawiany zgodnie z liczbą dni w danym miesiącu. Funkcja uwzględnia przypadek
    /// roku przestępnego.
    void setMonthDayRange(int m);
    /// Ustawia rok
    void setYear(int y);
};

/// Klasa bazowa dla klas EventAdderWindow i EventEditorWindow
class EventAddEditWindow : public QDialog {
protected:
    /// Pole tektowe do podania tytułu wydarzenia
    QLineEdit *title_edit;
    /// Pole tektowe do podania opisu wydarzenia
    QTextEdit *description_edit;

    /// Pole do wyboru dnia rozpoczęcia
    DateSelectSpinBox *start_day;
    /// Pole do wyboru miesiąca rozpoczęcia
    DateSelectSpinBox *start_month;
    /// Pole do wyboru roku rozpoczęcia
    DateSelectSpinBox *start_year;
    /// Pole do wyboru godziny rozpoczęcia
    DateSelectSpinBox *start_hour;
    /// Pole do wyboru minuty rozpoczęcia
    DateSelectSpinBox *start_min;

    /// Pole do wyboru dnia zakończenia
    DateSelectSpinBox *end_day;
    /// Pole do wyboru miesiąca zakończenia
    DateSelectSpinBox *end_month;
    /// Pole do wyboru roku zakończenia
    DateSelectSpinBox *end_year;
    /// Pole do wyboru godziny zakończenia
    DateSelectSpinBox *end_hour;
    /// Pole do wyboru minuty zakończenia
    DateSelectSpinBox *end_min;

    /// Obiekt zarządzający ułożeniem elementów w wyświetlanym oknie
    QVBoxLayout *vbox;
public:
    /// Konstruktor
    EventAddEditWindow(QWidget *parent = nullptr);
    /// Destruktor
    ~EventAddEditWindow();
};

/// Klasa reprezentująca okno umożliwiające dodanie nowego wydarzenia
class EventAdderWindow : public EventAddEditWindow {
public:
    /// Konstruktor
    EventAdderWindow(QWidget *parent = nullptr);
Q_OBJECT
private slots:
    void createEvent();
};

/// Klasa reprezentująca okno edytora wydarzenia
class EventEditorWindow : public EventAddEditWindow {
private:
    Event *event;
public:
    /// Konstruktor
    ///
    /// Parametr `_event` określa wydarzenie, które będzie edytowane.
    EventEditorWindow(Event *_event, QWidget *parent = nullptr);
Q_OBJECT
private slots: 
    void save();
    void deleteEvent();
};

/// Klasa reprezentująca okienko wyświetlane przy próbie usunięcia wydarzenia
///
/// Obiekty tej klasy są tworzone przez obiekt klasy EventEditorWindow, po wybraniu
/// przez użytkownika opcji usuwania wydarzenia. Celem tej klasy jest potwierdzenie,
/// że usunięcie danego wydarzenia jest celem użytkownika.
class DeleteEventDialog : public QDialog {
private:
    Event *event;
public:
    /// Konstruktor
    DeleteEventDialog(Event *_event, QWidget *parent = nullptr);
Q_OBJECT
private slots:
    void onYes();
};

#endif