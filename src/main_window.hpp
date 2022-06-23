#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QWidget>
#include <QDate>
#include <QPushButton>
#include "timetable_window.hpp"

class MainWindow : public QWidget {
private:
    QDate current_date;
    QPushButton *date_button;
    // TimetableWindow *timetable;
    std::map<QDate,std::vector<Event>> events;

    QFont font;
    int font_size = 16;
    QString font_family = "Ubuntumono";

    int width = 960, height = 720;
    
    void updateGUI();
public:
    MainWindow(QWidget *parent = nullptr);
    void addEvent(Event &event);
    void deleteEvent(Event &event);

    QDate getCurrentDate();
Q_OBJECT
private slots:
    void incrementDate();
    void decrementDate();
    void onAddEvent();
protected:
    virtual void closeEvent(QCloseEvent *event);
};

#endif