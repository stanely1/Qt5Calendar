#ifndef EVENT_SAVER_HPP
#define EVENT_SAVER_HPP

#include "event.hpp"

class EventSaver {
public:
    static void saveEvents(const std::map<QDate,std::vector<Event*>> &events);
    static void readEvents(std::map<QDate,std::vector<Event*>> &events);
};

#endif