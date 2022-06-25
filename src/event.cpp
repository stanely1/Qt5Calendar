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
QString Event::toStringStorable()
{
    return title + "\n" + description + "\1\n" 
    + QString("%1 %2 %3 %4 %5 ").arg(start.date().year()).arg(start.date().month()).arg(start.date().day())
                               .arg(start.time().hour()).arg(start.time().minute())
    + QString("%1 %2 %3 %4 %5").arg(end.date().year()).arg(end.date().month()).arg(end.date().day())
                               .arg(end.time().hour()).arg(end.time().minute());
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
EventDisplayWindow::EventDisplayWindow(Event *_event, QWidget *parent, int size) : QWidget(parent), event(_event) 
{
    setToolTip(event->toString());
 
    QPalette col;
    col.setColor(QPalette::Window, Qt::blue);

    setAutoFillBackground(true);
    setPalette(col);
    
    auto *vbox = new QVBoxLayout;

    auto *title = new QLabel(event->getTitle());
    vbox->addWidget(title);
    if(size >= 2) 
    {
        auto *start = new QLabel("start: " + event->getStart().toString());
        vbox->addWidget(start);
    }
    if(size >= 3) 
    {
        auto *end   = new QLabel("end: " + event->getEnd().toString());
        vbox->addWidget(end);
    }
    setLayout(vbox);
}

// slots
void EventDisplayWindow::mousePressEvent(QMouseEvent *mouse_event)
{
    if(mouse_event->button() == Qt::LeftButton) event->runEditor();
}