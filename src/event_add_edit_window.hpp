#ifndef EVENT_ADD_EDIT_WINDOW_HPP
#define EVENT_ADD_EDIT_WIDNOW_HPP

#include <QDialog>
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QSpinBox>
#include "event.hpp"
#include "main_window.hpp"

class DateSelectSpinBox : public QSpinBox {
public:
    DateSelectSpinBox(QWidget *parent = nullptr);
Q_OBJECT
public slots:
    void setMonthDayRange(int m);
};

class EventAddEditWindow : public QDialog {
protected:
    QLineEdit *title_edit;
    QTextEdit *description_edit;
    DateSelectSpinBox *start_day, *start_month, *start_year, *start_hour, *start_min;
    DateSelectSpinBox *end_day, *end_month, *end_year, *end_hour, *end_min;

    QVBoxLayout *vbox;
public:
    EventAddEditWindow(QWidget *parent = nullptr);
};

class EventAdderWindow : public EventAddEditWindow {
public:
    EventAdderWindow(QWidget *parent = nullptr);
Q_OBJECT
private slots:
    void createEvent();
};

class EventEditorWindow : public EventAddEditWindow {
private:
    Event *event;
public:
    EventEditorWindow(Event *_event, QWidget *parent = nullptr);
Q_OBJECT
private slots: 
    void save();
};

#endif