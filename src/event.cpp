#include "event.hpp"
#include "event_add_edit_window.hpp"

// event
Event::Event(const QString &_title, const QString &_description, 
             const QDateTime &_start, const QDateTime &_end) : 
title(_title), description(_description), start(_start), end(_end) {}

// run event editor window
void Event::runEditor()
{
    auto editor = new EventEditorWindow(*this);
    editor->show();
}
QString Event::toString()
{
    return title + "\n" + description + "\nstart: " +
           start.toString() + "\nend: " + end.toString();
}
//get event title
QString Event::getTitle() {return title;} 
// get event description
QString Event::getDescription() {return description;}
// get event start date
QDateTime Event::getStart() {return start;}
// get event end date
QDateTime Event::getEnd() {return end;}

void Event::setTitle(QString &_title) {title = _title;}
void Event::setDescription(QString &_description) {description = _description;}
void Event::setStart(QDateTime &_start) {start = _start;}
void Event::setEnd(QDateTime &_end) {end = _end;}

// event dispaly window
EventDisplayWindow::EventDisplayWindow(Event &_event, QWidget *parent) : event(_event), QWidget(parent) 
{
    
}

void EventDisplayWindow::onClick()
{
    event.runEditor();
}