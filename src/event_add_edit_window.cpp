#include "event_add_edit_window.hpp"
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <iostream>

// date select spin box

DateSelectSpinBox::DateSelectSpinBox(QWidget *parent) : QSpinBox(parent) {};

void DateSelectSpinBox::setMonthDayRange(int m)
{
    static int days_in_month[13] = {29,31,28,31,30,31,30,31,31,30,31,30,31}; // 0 - luty w roku przestępczym :)
    setRange(1,days_in_month[m]);
}

// Windows:

EventAddEditWindow::EventAddEditWindow(MainWindow *_main_window, QWidget *parent) : 
    QDialog(parent), main_window(_main_window)
{
    setModal(true);

    title_edit = new QLineEdit(this);
    description_edit = new QTextEdit(this);

    // date
    start_day   = new DateSelectSpinBox(this);
    start_month = new DateSelectSpinBox(this);
    start_year  = new DateSelectSpinBox(this);
    start_hour  = new DateSelectSpinBox(this);
    start_min   = new DateSelectSpinBox(this);

    end_day   = new DateSelectSpinBox(this);
    end_month = new DateSelectSpinBox(this);
    end_year  = new DateSelectSpinBox(this);
    end_hour  = new DateSelectSpinBox(this);
    end_min   = new DateSelectSpinBox(this);

    auto current_time = QTime::currentTime();
    const int min_spin_box_width = 55;

    start_day  ->setValue(main_window->getCurrentDate().day());
    start_month->setValue(main_window->getCurrentDate().month());
    start_year ->setValue(main_window->getCurrentDate().year());
    start_hour ->setValue(current_time.hour());
    start_min  ->setValue(current_time.minute());
    
    end_day  ->setValue(main_window->getCurrentDate().day());
    end_month->setValue(main_window->getCurrentDate().month());
    end_year ->setValue(main_window->getCurrentDate().year());
    end_hour ->setValue(current_time.hour());
    end_min  ->setValue(current_time.minute());

    start_day->  setMonthDayRange(start_month->value()); start_day->setMinimumWidth(min_spin_box_width);
    start_month->setRange(1,12); start_month->setMinimumWidth(min_spin_box_width);
    start_year-> setRange(2022,3000); start_year->setMinimumWidth(80);
    start_hour-> setRange(0,23); start_hour->setMinimumWidth(min_spin_box_width);
    start_min->  setRange(0,59); start_min->setMinimumWidth(min_spin_box_width);

    end_day->  setMonthDayRange(end_month->value()); end_day->setMinimumWidth(min_spin_box_width);
    end_month->setRange(1,12); end_month->setMinimumWidth(min_spin_box_width);
    end_year-> setRange(2022,3000); end_year->setMinimumWidth(80);
    end_hour-> setRange(0,23); end_hour->setMinimumWidth(min_spin_box_width);
    end_min->  setRange(0,59); end_min->setMinimumWidth(min_spin_box_width);

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

    connect(start_month,qOverload<int>(&DateSelectSpinBox::valueChanged),start_day,
            &DateSelectSpinBox::setMonthDayRange);
    connect(end_month,qOverload<int>(&DateSelectSpinBox::valueChanged),end_day,
            &DateSelectSpinBox::setMonthDayRange);

    // layout
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