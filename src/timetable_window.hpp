#ifndef TIMETABLE_WINDOW_HPP
#define TIMETABLE_WINDOW_HPP

#include <QWidget>
#include <vector>
#include "event.hpp"

class TimetableWindow : public QWidget {
private:
    std::vector<Event*> events;
public:
    TimetableWindow(std::vector<Event*> _events = {}, QWidget *parent = nullptr);
    // ~TimetableWindow();

    TimetableWindow & operator = (const TimetableWindow &t);
};

#endif