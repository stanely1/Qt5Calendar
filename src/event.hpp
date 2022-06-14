#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <QTextStream>
#include <QDateTime>
#include <QWidget>

class Event {
private:
    QString title;
    QString description;
    QDateTime start;
    QDateTime end;
public:
    Event(const QString &_title, const QString &_description, const QDateTime &_start, const QDateTime &_end);
    void runEditor();

    QString toString();

    QString getTitle();
    QString getDescription();
    QDateTime getStart();
    QDateTime getEnd();

    void setTitle(QString &_title);
    void setDescription(QString &_description);
    void setStart(QDateTime &_start);
    void setEnd(QDateTime &_end);
};

class EventDisplayWindow : public QWidget {
private: 
    Event &event;
public:
    EventDisplayWindow(Event &_event, QWidget *parent = nullptr);
Q_OBJECT
private slots:
    void onClick();
};

#endif