#include "event.hpp"
#include "event_add_edit_window.hpp"
#include <QLabel>
#include <QToolBar>

// event
Event::Event(const QString &_title, const QString &_description, 
             const QDateTime &_start, const QDateTime &_end) : 
title(_title), description(_description), start(_start), end(_end) {}

// run event editor window
void Event::runEditor()
{
    auto editor = new EventEditorWindow(this);
    editor->show();
}
QString Event::toString()
{
    return title + "\n" + description + "\nstart: " +
           start.toString() + "\nend: " + end.toString();
}
//get event title
QString Event::getTitle() const {return title;} 
// get event description
QString Event::getDescription() const {return description;}
// get event start date
QDateTime Event::getStart() const {return start;}
// get event end date
QDateTime Event::getEnd() const {return end;}

void Event::setTitle(const QString &_title) {title = _title;}
void Event::setDescription(const QString &_description) {description = _description;}
void Event::setStart(const QDateTime &_start) {start = _start;}
void Event::setEnd(const QDateTime &_end) {end = _end;}

// event dispaly window
EventDisplayWindow::EventDisplayWindow(Event *_event, QWidget *parent) : QWidget(parent), event(_event) 
{
    auto *vbox = new QVBoxLayout;
    auto *toolbar = new QToolBar(this);
    auto *label = new QLabel(event->toString());

    auto *edit_action = toolbar->addAction("edit");
    toolbar->addSeparator();
    auto *del_action  = toolbar->addAction("delete");

    connect(edit_action, &QAction::triggered, this, &EventDisplayWindow::onEdit);
    connect(del_action, &QAction::triggered, this, &EventDisplayWindow::onDelete);

    QPalette col;
    col.setColor(QPalette::Window, Qt::blue);

    setAutoFillBackground(true);
    setPalette(col);

    vbox->addWidget(toolbar);
    vbox->addWidget(label);
    setLayout(vbox);
}

// slots

void EventDisplayWindow::onEdit()
{
    event->runEditor();
}
void EventDisplayWindow::onDelete()
{
    main_window->deleteEvent(event);
}