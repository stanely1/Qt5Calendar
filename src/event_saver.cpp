#include "event_saver.hpp"
#include <QFile>
#include <QTextStream>

#include <iostream>

#define FILENAME "events.dat"

void EventSaver::saveEvents(const std::map<QDate,std::vector<Event*>> &events)
{
    std::cout << "Saving events ...\n";
    QFile f(FILENAME);

    if(!f.open(QIODevice::WriteOnly)) throw std::ios_base::failure("Error saving events");

    QTextStream os(&f);
    os << events.size() << "\n";
    for(auto p : events)
    {
        os << p.first.year() << " " << p.first.month() << " " << p.first.day() << "\n";
        os << p.second.size() << "\n";
        for(auto e : p.second) os << e->toStringStorable() << "\n";
    }
}
void EventSaver::readEvents(std::map<QDate,std::vector<Event*>> &events)
{
    std::cout << "Reading events ...\n";
    QFile f(FILENAME);

    if(!f.open(QIODevice::ReadOnly)) {
        std::cout << "File \"" << FILENAME << "\" not found\n"; return;
    }

    QTextStream is(&f);
    int days_cnt; is >> days_cnt;

    while(days_cnt--)
    {
        int y,m,d; is >> y >> m >> d;
        auto date = QDate(y,m,d);
        int s; is >> s; is.readLine();     
        while(s--)
        {
            QString title = is.readLine();
            QString description;

            while(true)
            {
                description += is.readLine();
                if(*(description.rbegin()) == '\1') break;
                description += "\n";
            }
            description.chop(1);

            int sy,sm,sd,sh,smin;
            int ey,em,ed,eh,emin;
            is >> sy >> sm >> sd >> sh >> smin >> ey >> em >> ed >> eh >> emin;
            events[date].push_back(new Event(title,description,QDateTime(QDate(sy,sm,sd),QTime(sh,smin)),
                                                               QDateTime(QDate(ey,em,ed),QTime(eh,emin))));
            is.readLine();
        }
    }
}