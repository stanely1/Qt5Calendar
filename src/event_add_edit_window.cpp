#include "event_add_edit_window.hpp"
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <iostream>

EventAddEditWindow::EventAddEditWindow(MainWindow *_main_window, QWidget *parent) : 
    QDialog(parent), main_window(_main_window)
{
    setModal(true);

    title_edit = new QLineEdit(this);
    description_edit = new QTextEdit(this);

    // date
    static int days_in_month[13] = {29,31,28,31,30,31,30,31,31,30,31,30,31}; // 0 - luty w roku przestępczym :) 

    start_day   = new QSpinBox(this); start_day->  setRange(1,31); start_day->setMinimumWidth(50);
    start_month = new QSpinBox(this); start_month->setRange(1,12); start_month->setMinimumWidth(50);
    start_year  = new QSpinBox(this); start_year-> setRange(2022,3000); start_year->setMinimumWidth(80);
    start_hour  = new QSpinBox(this); start_hour-> setRange(0,23); start_hour->setMinimumWidth(50);
    start_min   = new QSpinBox(this); start_min->  setRange(0,59); start_min->setMinimumWidth(50);

    end_day   = new QSpinBox(this); end_day->  setRange(1,31); end_day->setMinimumWidth(50);
    end_month = new QSpinBox(this); end_month->setRange(1,12); end_month->setMinimumWidth(50);
    end_year  = new QSpinBox(this); end_year-> setRange(2022,3000); end_year->setMinimumWidth(80);
    end_hour  = new QSpinBox(this); end_hour-> setRange(0,23); end_hour->setMinimumWidth(50);
    end_min   = new QSpinBox(this); end_min->  setRange(0,59); end_min->setMinimumWidth(50);

    auto *start_hbox = new QHBoxLayout;
    auto *end_hbox   = new QHBoxLayout;

    start_hbox->addWidget(new QLabel("day:"));
    start_hbox->addWidget(start_day,1);
    start_hbox->addWidget(new QLabel("month:"));
    start_hbox->addWidget(start_month,1);
    start_hbox->addWidget(new QLabel("year:"));
    start_hbox->addWidget(start_year,1);
    start_hbox->addWidget(new QLabel("hour:"));
    start_hbox->addWidget(start_hour,1);
    start_hbox->addWidget(new QLabel("minute:"));
    start_hbox->addWidget(start_min,1);

    end_hbox->addWidget(new QLabel("day:"));
    end_hbox->addWidget(end_day,1);
    end_hbox->addWidget(new QLabel("month:"));
    end_hbox->addWidget(end_month,1);
    end_hbox->addWidget(new QLabel("year:"));
    end_hbox->addWidget(end_year,1);
    end_hbox->addWidget(new QLabel("hour:"));
    end_hbox->addWidget(end_hour,1);
    end_hbox->addWidget(new QLabel("minute:"));
    end_hbox->addWidget(end_min,1);

    auto *form = new QFormLayout;
    form->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    form->addRow("Title:", title_edit);
    form->addRow("Description:", description_edit);
    form->addRow("Start date:", start_hbox);
    form->addRow("End date:", end_hbox);

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
    auto start_date = 
    QDateTime(QDate(start_year->value(), start_month->value(), start_day->value()),
              QTime(start_hour->value(), start_min->value()));
    auto end_date = 
    QDateTime(QDate(end_year->value(), end_month->value(), end_day->value()),
              QTime(end_hour->value(), end_min->value()));

    if(end_date < start_date) 
    {
        std::cerr << "Cannot create event: end date is less than start date\n";
        return;
    }

    auto event = 
    Event(title_edit->text(),description_edit->toPlainText(), start_date, end_date);
    main_window->addEvent(event);
}

// editor
EventEditorWindow::EventEditorWindow(Event &_event, MainWindow *_main_window, QWidget *parent) : 
    EventAddEditWindow(_main_window, parent), event(_event)
{
    
}