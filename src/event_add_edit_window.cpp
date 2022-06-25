#include "event_add_edit_window.hpp"
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <iostream>

// date select spin box

bool leapYear(int y)
{
    return y % 100 ? y % 4 == 0 : y % 400 == 0;
}

DateSelectSpinBox::DateSelectSpinBox(QWidget *parent) : QSpinBox(parent) {};

void DateSelectSpinBox::setMonthDayRange(int m)
{
    month = m;
    static int days_in_month[13] = {29,31,28,31,30,31,30,31,31,30,31,30,31}; // 0 - luty w roku przestępczym :)
    if(m == 2 && leapYear(year)) m = 0;
    setRange(1,days_in_month[m]);
}
void DateSelectSpinBox::setYear(int y) 
{
    year = y;
    setMonthDayRange(month);
}

// Windows:

EventAddEditWindow::EventAddEditWindow(QWidget *parent) : QDialog(parent)
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
  
    const int min_spin_box_width = 55;

    start_day->setMinimumWidth(min_spin_box_width);
    start_month->setRange(1,12); start_month->setMinimumWidth(min_spin_box_width);
    start_year-> setRange(2022,3000); start_year->setMinimumWidth(80);
    start_hour-> setRange(0,23); start_hour->setMinimumWidth(min_spin_box_width);
    start_min->  setRange(0,59); start_min->setMinimumWidth(min_spin_box_width);

    end_day->setMinimumWidth(min_spin_box_width);
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
    connect(start_year,qOverload<int>(&DateSelectSpinBox::valueChanged),start_day,
            &DateSelectSpinBox::setYear);
    connect(end_year,qOverload<int>(&DateSelectSpinBox::valueChanged),end_day,
            &DateSelectSpinBox::setYear);

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

EventAddEditWindow::~EventAddEditWindow()
{
    delete title_edit;
    delete description_edit;

    delete start_day;
    delete start_month;
    delete start_year;
    delete start_hour;
    delete start_min;

    delete end_day;
    delete end_month;
    delete end_year;
    delete end_hour;
    delete end_min;

    delete vbox;
}

// adder

EventAdderWindow::EventAdderWindow(QWidget *parent) : 
    EventAddEditWindow(parent) 
{
    setWindowTitle("Add new event");
    // initialize date select values
    auto current_time = QTime::currentTime();
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

    start_day->setYear(start_year->value());
    end_day  ->setYear(end_year->value());
    start_day->setMonthDayRange(start_month->value());
    end_day  ->setMonthDayRange(end_month->value()); 

    // cancel and add buttons
    auto *cancel_button = new QPushButton("Cancel");
    auto *add_button = new QPushButton("Add Event");

    cancel_button->setCursor(Qt::PointingHandCursor);
    add_button->setCursor(Qt::PointingHandCursor);

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

    auto *event = 
    new Event(title_edit->text(),description_edit->toPlainText(), start_date, end_date);
    main_window->addEvent(event);
    
    close();
}

// editor
EventEditorWindow::EventEditorWindow(Event *_event, QWidget *parent) : 
    EventAddEditWindow(parent), event(_event)
{
    setWindowTitle("Event editor");
    // intitalize event fields editors
    title_edit->setText(event->getTitle());
    description_edit->setText(event->getDescription());

    auto start_date = event->getStart().date();
    auto start_time = event->getStart().time();
    start_day  ->setValue(start_date.day());
    start_month->setValue(start_date.month());
    start_year ->setValue(start_date.year());
    start_hour ->setValue(start_time.hour());
    start_min  ->setValue(start_time.minute());

    auto end_date = event->getEnd().date();
    auto end_time = event->getEnd().time();
    end_day  ->setValue(end_date.day());
    end_month->setValue(end_date.month());
    end_year ->setValue(end_date.year());
    end_hour ->setValue(end_time.hour());
    end_min  ->setValue(end_time.minute());

    // save and cancel buttons
    auto *cancel_button = new QPushButton("Cancel");
    auto *save_button   = new QPushButton("Save changes");
    auto *delete_button = new QPushButton("Delete event");

    cancel_button->setCursor(Qt::PointingHandCursor);
    save_button  ->setCursor(Qt::PointingHandCursor);
    delete_button->setCursor(Qt::PointingHandCursor);

    connect(cancel_button,&QPushButton::clicked,this,&QWidget::close);
    connect(save_button,  &QPushButton::clicked,this,&EventEditorWindow::save);
    connect(delete_button,&QPushButton::clicked,this,&EventEditorWindow::deleteEvent);

    auto *hbox = new QHBoxLayout;
    hbox->addWidget(cancel_button,1,Qt::AlignLeft);
    hbox->addWidget(delete_button,1,Qt::AlignCenter);
    hbox->addWidget(save_button,  1,Qt::AlignRight);

    vbox->addLayout(hbox);
}

void EventEditorWindow::save()
{
    auto start_date = 
    QDateTime(QDate(start_year->value(), start_month->value(), start_day->value()),
              QTime(start_hour->value(), start_min->value()));
    auto end_date = 
    QDateTime(QDate(end_year->value(), end_month->value(), end_day->value()),
              QTime(end_hour->value(), end_min->value()));

    if(end_date < start_date) 
    {
        std::cerr << "Cannot apply changes: end date is less than start date\n";
        return;
    }
    
    main_window->deleteEvent(event,false);

    event->setTitle(title_edit->text());
    event->setDescription(description_edit->toPlainText());
    event->setStart(start_date);
    event->setEnd(end_date);

    main_window->addEvent(event);
}

void EventEditorWindow::deleteEvent()
{
    auto delete_dialog = new DeleteEventDialog(event,this);
    delete_dialog->show();
}

// DeleteEventDialog
DeleteEventDialog::DeleteEventDialog(Event *_event, QWidget *parent) :
    QDialog(parent), event(_event)
{
    setModal(true);
    setWindowTitle("Delete event");

    auto *label = new QLabel("Do you really want do delete this event?");
    auto *yes_button = new QPushButton("Yes");
    auto *no_button  = new QPushButton("No");

    yes_button->setCursor(Qt::PointingHandCursor);
    no_button ->setCursor(Qt::PointingHandCursor);

    connect(yes_button,&QPushButton::clicked,this,&DeleteEventDialog::onYes);
    connect(no_button, &QPushButton::clicked,this,&DeleteEventDialog::close);

    auto *hbox = new QHBoxLayout;
    hbox->addWidget(no_button ,1,Qt::AlignLeft);
    hbox->addWidget(yes_button,1,Qt::AlignRight);

    auto *vbox = new QVBoxLayout;
    vbox->addWidget(label);
    vbox->addLayout(hbox);

    setLayout(vbox);
}

// slots
void DeleteEventDialog::onYes()
{
    main_window->deleteEvent(event);
    parentWidget()->close();
    close();
}