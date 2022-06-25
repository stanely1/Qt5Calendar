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
    TimetableWindow *timetable;
    std::map<QDate,std::vector<Event*>> events;

    QFont font;
    int font_size = 14;
    QString font_family = "Ubuntumono";

    int WIDTH = 720, HEIGHT = 960;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addEvent(Event *event, bool _init = false);
    void deleteEvent(Event *event, bool free_ptr = true);

    void updateGUI();

    QDate getCurrentDate();
Q_OBJECT
private slots:
    void incrementDate();
    void decrementDate();
    void onAddEvent();
protected:
    virtual void closeEvent(QCloseEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
};

extern MainWindow *main_window;

#endif