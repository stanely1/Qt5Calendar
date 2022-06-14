#ifndef EVENT_ADD_EDIT_WINDOW_HPP
#define EVENT_ADD_EDIT_WIDNOW_HPP

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QTextStream>
#include <QVBoxLayout>
#include "event.hpp"
#include "main_window.hpp"

class EventAddEditWindow : public QWidget {
protected:
    QLineEdit *title_edit;
    QTextEdit *description_edit;
    QLineEdit *start_edit;
    QLineEdit *end_edit;

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