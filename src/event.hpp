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

    QString getTitle() const;
    QString getDescription() const;
    QDateTime getStart() const;
    QDateTime getEnd() const;

    void setTitle(const QString &_title);
    void setDescription(const QString &_description);
    void setStart(const QDateTime &_start);
    void setEnd(const QDateTime &_end);
};

class EventDisplayWindow : public QWidget {
private: 
    Event *event;
public:
    EventDisplayWindow(Event *_event, QWidget *parent = nullptr);
Q_OBJECT
private slots:
    void onEdit();
    void onDelete();
};

#endif