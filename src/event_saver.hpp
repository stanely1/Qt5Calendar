#ifndef EVENT_SAVER_HPP
#define EVENT_SAVER_HPP

#include "event.hpp"
#include "main_window.hpp"

class EventSaver {
public:
    static void saveEvents(const std::map<QDate,std::vector<Event*>> &events);
    static void readEvents(MainWindow *_main_window);
};

#endif