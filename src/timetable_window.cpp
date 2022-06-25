#include "timetable_window.hpp"
#include <QGridLayout>
#include <QLabel>

TimetableWindow::TimetableWindow(const QDate &_date, std::vector<Event*> *_events, QWidget *parent) : 
    QWidget(parent), events(_events), current_date(_date)
{
    if(parent != nullptr) WIDTH = parent->width(), HEIGHT = parent->height() - 40;
    resize(WIDTH,HEIGHT);
    // auto *grid = new QGridLayout;

    // for(int i = 0; i < events->size(); i++)
    //     grid->addWidget(new EventDisplayWindow((*events)[i],this),i,0);
    // auto total_HEIGHT = HEIGHT();
    // auto total_WIDTH  = WIDTH();
    static const int total_mins = 1440;

    for(auto e : *events)
    {
        int start_pos, end_pos;
        start_pos = e->getStart().date() < current_date ? 
                    0 : e->getStart().time().hour() * 60 + e->getStart().time().minute();
        end_pos = e->getEnd().date() > current_date ? 
                    total_mins : e->getEnd().time().hour() * 60 + e->getEnd().time().minute();

        start_pos = start_pos * HEIGHT / total_mins;
        end_pos   = end_pos * HEIGHT / total_mins;

        auto *edw = new EventDisplayWindow(e,this);
        edw->setGeometry(0,start_pos,WIDTH,end_pos-start_pos);
    }

    // setLayout(grid);
}

TimetableWindow & TimetableWindow::operator = (const TimetableWindow &t)
{
    if(this != &t)
        events = t.events;
    return *this;
}
