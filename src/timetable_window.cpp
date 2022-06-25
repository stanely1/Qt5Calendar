#include "timetable_window.hpp"
#include <QGridLayout>
#include <QLabel>

TimetableWindow::TimetableWindow(const QDate &_date, std::vector<Event*> *_events, QWidget *parent) : 
    QWidget(parent), events(_events), current_date(_date)
{
    auto *grid = new QGridLayout;

    for(int i = 0; i < events->size(); i++)
        grid->addWidget(new EventDisplayWindow((*events)[i],this),i,0);
    // for(auto e : *events)

    setLayout(grid);
}

TimetableWindow & TimetableWindow::operator = (const TimetableWindow &t)
{
    if(this != &t)
        events = t.events;
    return *this;
}
