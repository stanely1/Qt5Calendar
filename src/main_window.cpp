#include <QVBoxLayout>
#include <QApplication>
#include <QAction>
#include <QMenu>
#include "main_window.hpp"
#include "event_add_edit_window.hpp"
#include "event_saver.hpp"
#include "date_select_dialog.hpp"

MainWindow *main_window;

// constructor
MainWindow::MainWindow(QWidget *parent) : QWidget(parent), current_date(QDate::currentDate())
{
    EventSaver::readEvents(this);

    this->resize(WIDTH,HEIGHT);
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

    // options
    auto *option_menu = new QMenu;

    auto *clear_option = new QAction("Clear all events");

    option_menu->addAction(clear_option);
    option_button->setMenu(option_menu);
    option_button->setStyleSheet("QPushButton::menu-indicator{width:0px;}");

    // cursors
    date_button->setCursor(Qt::PointingHandCursor);
    add_event_button->setCursor(Qt::PointingHandCursor);
    left_button->setCursor(Qt::PointingHandCursor);
    right_button->setCursor(Qt::PointingHandCursor);
    option_button->setCursor(Qt::PointingHandCursor);

    // connections
    // main buttons
    connect(date_button, &QPushButton::clicked, this, &MainWindow::runDateSelector);
    connect(left_button, &QPushButton::clicked, this, &MainWindow::decrementDate);
    connect(right_button,&QPushButton::clicked, this, &MainWindow::incrementDate);
    connect(add_event_button, &QPushButton::clicked, this, &MainWindow::onAddEvent);
    // options
    connect(clear_option, &QAction::triggered, this, &MainWindow::clearEvents);

    hbox->addWidget(option_button,1,Qt::AlignLeft);
    hbox->addWidget(left_button,1,Qt::AlignRight);
    hbox->addWidget(date_button,0,Qt::AlignCenter);
    hbox->addWidget(right_button,1,Qt::AlignLeft);
    hbox->addWidget(add_event_button,1,Qt::AlignRight);

    timetable = new TimetableWindow(current_date,&events[current_date],this);

    vbox->addLayout(hbox);
    vbox->addWidget(timetable);
    vbox->setSpacing(20);

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

// resize event
void MainWindow::resizeEvent(QResizeEvent *event)
{
    updateGUI();
}

//run date selector
void MainWindow::runDateSelector()
{
    auto *date_selector = new DateSelectDialog(current_date.year(),current_date.month(),this);
    date_selector->show();
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
    timetable = new TimetableWindow(current_date,&events[current_date],this);

    l->addWidget(timetable);
}

// handling event adding actions
void MainWindow::onAddEvent()
{
    auto *adder = new EventAdderWindow(this);
    adder->show();
}

void MainWindow::addEvent(Event *event, bool _init)
{
    auto end_date = event->getEnd().date();

    for(auto date = event->getStart().date(); date <= end_date; date = date.addDays(1))
        events[date].push_back(event);

    if(!_init) updateGUI();
}

// date getter
QDate MainWindow::getCurrentDate() const {return current_date;}

// date setter
void MainWindow::setDate(const QDate &date)
{
    current_date = date;
    updateGUI();
}

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

void MainWindow::clearEvents()
{
    events.clear();
    updateGUI();
}