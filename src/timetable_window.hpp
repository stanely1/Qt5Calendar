#ifndef TIMETABLE_WINDOW_HPP
#define TIMETABLE_WINDOW_HPP

#include <QWidget>
#include <vector>
#include "event.hpp"

class TimetableWindow : public QWidget {
private:
    std::vector<Event*> *events;
    QDate current_date;
public:
    TimetableWindow(const QDate &_date, std::vector<Event*> *_events = nullptr, QWidget *parent = nullptr);
    //~TimetableWindow();

    TimetableWindow & operator = (const TimetableWindow &t);
};

#endif