#include <QFile>
#include <QTextStream>
#include "event_saver.hpp"
#include <iostream>
#include <set>

/// Nazwa pliku, w którym zapisywane są wydarzenia
#define FILENAME "events.dat"

/// Przekształca strukturę `std::map<QDate,std::vector<Event*>>` na `std::set<Event*>`.
std::set<Event*> toSet(const std::map<QDate,std::vector<Event*>> &events)
{
    std::set<Event*> res;
    for(auto p : events)
        for(auto e : p.second)
            res.insert(e);
    return res;
}

void EventSaver::saveEvents(const std::map<QDate,std::vector<Event*>> &events)
{
    std::cout << "Saving events ...\n";
    QFile f(FILENAME);

    if(!f.open(QIODevice::WriteOnly)) throw std::ios_base::failure("Error saving events");

    auto event_set = toSet(events);

    QTextStream os(&f);

    os << event_set.size() << "\n";
    for(auto e : event_set) os << e->toStringStorable() << "\n";
}
void EventSaver::readEvents(MainWindow *_main_window)
{
    std::cout << "Reading events ...\n";
    QFile f(FILENAME);

    if(!f.open(QIODevice::ReadOnly)) {
        std::cout << "File \"" << FILENAME << "\" not found\n"; return;
    }

    QTextStream is(&f);
    int events_cnt; is >> events_cnt;
    is.readLine();

    while(events_cnt--)
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
        _main_window->addEvent(new Event(title,description,QDateTime(QDate(sy,sm,sd),QTime(sh,smin)),
                                                           QDateTime(QDate(ey,em,ed),QTime(eh,emin))),
                               true);
        is.readLine();
    }
}