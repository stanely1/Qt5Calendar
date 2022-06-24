#include "timetable_window.hpp"
#include <QGridLayout>
#include <QLabel>

TimetableWindow::TimetableWindow(std::vector<Event*> *_events, QWidget *parent) : 
    QWidget(parent), events(_events)
{
    auto *grid = new QGridLayout;

    for(int i = 0; i < events->size(); i++)
        grid->addWidget(new EventDisplayWindow((*events)[i],this),i,0);

    setLayout(grid);
}

TimetableWindow & TimetableWindow::operator = (const TimetableWindow &t)
{
    if(this != &t)
        events = t.events;
    return *this;
}
