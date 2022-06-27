#include "timetable_window.hpp"
#include <QGridLayout>
#include <QLabel>

TimetableWindow::TimetableWindow(const QDate &_date, std::vector<Event*> *_events, QWidget *parent) : 
    QWidget(parent), events(_events), current_date(_date)
{
    if(parent != nullptr) WIDTH = parent->width(), HEIGHT = parent->height() - 70;
    resize(WIDTH,HEIGHT);

    static const int total_mins = 1440;

    QLabel *hlbl;

    for(int h = 0; h < 24; h+=1)
    {
        hlbl = new QLabel(QString("%1:00").arg(h),this);
        hlbl->move(0,h*60*HEIGHT/total_mins);
    }

    int hwidth = hlbl->width();

    for(auto e : *events)
    {
        int start_pos, end_pos, size;
        start_pos = e->getStart().date() < current_date ? 
                    0 : e->getStart().time().hour() * 60 + e->getStart().time().minute();
        end_pos = e->getEnd().date() > current_date ? 
                    total_mins : e->getEnd().time().hour() * 60 + e->getEnd().time().minute();

        int h = end_pos-start_pos;
        if(h < 120) size = 1;
        else if(h < 180) size = 2;
        else size = 3;

        start_pos = start_pos * HEIGHT / total_mins;
        end_pos   = end_pos * HEIGHT / total_mins;

        auto *edw = new EventDisplayWindow(e,this,size);
        edw->move(hwidth,start_pos);
        edw->resize(WIDTH-hwidth,end_pos-start_pos);
    }
}
