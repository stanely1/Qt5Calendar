#ifndef EVENT_ADD_EDIT_WINDOW_HPP
#define EVENT_ADD_EDIT_WIDNOW_HPP

#include <QDialog>
#include <QTextEdit>
#include <QLineEdit>
#include <QTextStream>
#include <QVBoxLayout>
#include <QSpinBox>
#include "event.hpp"
#include "main_window.hpp"

class EventAddEditWindow : public QDialog {
protected:
    QLineEdit *title_edit;
    QTextEdit *description_edit;
    QSpinBox *start_day, *start_month, *start_year, *start_hour, *start_min;
    QSpinBox *end_day, *end_month, *end_year, *end_hour, *end_min;

    QVBoxLayout *vbox;
    MainWindow *main_window;
public:
    EventAddEditWindow(MainWindow *_main_window = nullptr, QWidget *parent = nullptr);
};

class EventAdderWindow : public EventAddEditWindow {
public:
    EventAdderWindow(MainWindow *_main_window = nullptr, QWidget *parent = nullptr);
Q_OBJECT
private slots:
    void createEvent();
};

class EventEditorWindow : public EventAddEditWindow {
private:
    Event &event;
public:
    EventEditorWindow(Event &_event, MainWindow *_main_window = nullptr, QWidget *parent = nullptr);
// Q_OBJECT
// private slots: 
//     void save();
};

#endif