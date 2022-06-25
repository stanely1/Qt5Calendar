#include <QVBoxLayout>
#include <QFrame>
#include <QApplication>
#include "main_window.hpp"
#include "event_add_edit_window.hpp"
#include "event_saver.hpp"

#include <iostream>

MainWindow *main_window;

// constructor
MainWindow::MainWindow(QWidget *parent) : QWidget(parent), current_date(QDate::currentDate())
{
    EventSaver::readEvents(events);

    this->resize(width,height);
    font = QFont(font_family,font_size);
    this->setFont(font);

    auto *vbox = new QVBoxLayout;
    auto *hbox = new QHBoxLayout;

    date_button = new QPushButton(current_date.toString(),this);
    auto *left_button = new QPushButton("<",this);
    auto *right_button = new QPushButton(">",this);
    auto *add_event_button = new QPushButton("+",this);
    auto *option_button = new QPushButton("=",this);

    add_event_button->setToolTip("Add new event");
    date_button->setToolTip("Select day");
    option_button->setToolTip("Options");

    connect(left_button, &QPushButton::clicked, this, &MainWindow::decrementDate);
    connect(right_button, &QPushButton::clicked, this, &MainWindow::incrementDate);
    connect(add_event_button, &QPushButton::clicked, this, &MainWindow::onAddEvent);

    hbox->addWidget(option_button,1,Qt::AlignLeft);
    hbox->addWidget(left_button,1,Qt::AlignRight);
    hbox->addWidget(date_button,0,Qt::AlignCenter);
    hbox->addWidget(right_button,1,Qt::AlignLeft);
    hbox->addWidget(add_event_button,1,Qt::AlignRight);

    timetable = new TimetableWindow(&events[current_date],this);

    vbox->addLayout(hbox);
    vbox->addWidget(timetable);

    this->setLayout(vbox);
}
// destructor
MainWindow::~MainWindow()
{
    delete date_button;
    delete timetable;
    events.clear();
}

// close window => quit app
void MainWindow::closeEvent(QCloseEvent *event)
{
    EventSaver::saveEvents(events);
    qApp->quit();
}

// change current date
void MainWindow::incrementDate()
{
    current_date = current_date.addDays(1);
    updateGUI();
}
void MainWindow::decrementDate()
{
    current_date = current_date.addDays(-1);
    updateGUI();
}

// update GUI
void MainWindow::updateGUI()
{
    date_button->setText(current_date.toString());

    auto *l = layout();
    l->removeWidget(timetable);

    delete timetable;
    timetable = new TimetableWindow(&events[current_date],this);

    l->addWidget(timetable);
}

// handling event adding actions
void MainWindow::onAddEvent()
{
    auto *adder = new EventAdderWindow(this);
    adder->show();
}

void MainWindow::addEvent(Event *event)
{
    auto end_date = event->getEnd().date();

    for(auto date = event->getStart().date(); date <= end_date; date = date.addDays(1))
        events[date].push_back(event);

    updateGUI();
}

// date getter
QDate MainWindow::getCurrentDate() {return current_date;}

// delete event
void MainWindow::deleteEvent(Event *event, bool free_ptr)
{
    auto end_date = event->getEnd().date();

    for(auto date = event->getStart().date(); date <= end_date; date = date.addDays(1))
        for(auto i = events[date].begin(); i != events[date].end(); i++)
            if(*i == event) 
            {
                if(free_ptr) delete event, free_ptr = false; // memory should be freed only once
                events[date].erase(i);
                break;
            }

    updateGUI();
}