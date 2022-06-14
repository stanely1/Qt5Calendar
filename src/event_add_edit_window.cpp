#include "event_add_edit_window.hpp"
#include <QFormLayout>
#include <QPushButton>

EventAddEditWindow::EventAddEditWindow(MainWindow *_main_window, QWidget *parent) : 
    QWidget(parent), main_window(_main_window)
{
    title_edit = new QLineEdit(this);
    description_edit = new QTextEdit(this);
    start_edit = new QLineEdit(this);
    end_edit = new QLineEdit(this);

    auto *form = new QFormLayout;
    form->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    form->addRow("Title: ", title_edit);
    form->addRow("Description: ", description_edit);
    form->addRow("Start date: ", start_edit);
    form->addRow("End date: ", end_edit);

    vbox = new QVBoxLayout;
    vbox->addLayout(form);
    setLayout(vbox);
}

// adder

EventAdderWindow::EventAdderWindow(MainWindow *_main_window, QWidget *parent) : 
    EventAddEditWindow(_main_window, parent) 
{
    auto *cancel_button = new QPushButton("Cancel");
    auto *add_button = new QPushButton("Add Event");

    connect(cancel_button,&QPushButton::clicked,this, &QWidget::close);
    connect(add_button,&QPushButton::clicked,this,&EventAdderWindow::createEvent);

    auto *hbox = new QHBoxLayout;
    hbox->addWidget(cancel_button,1,Qt::AlignLeft);
    hbox->addWidget(add_button,1,Qt::AlignRight);

    vbox->addLayout(hbox);
}

void EventAdderWindow::createEvent()
{
    auto event = Event(title_edit->text(),description_edit->toPlainText(),
                       QDateTime::currentDateTime(), QDateTime::currentDateTime());
    main_window->addEvent(event);
}

// editor
EventEditorWindow::EventEditorWindow(Event &_event, MainWindow *_main_window, QWidget *parent) : 
    EventAddEditWindow(_main_window, parent), event(_event)
{
    
}