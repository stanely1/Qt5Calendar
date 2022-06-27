#ifndef TIMETABLE_WINDOW_HPP
#define TIMETABLE_WINDOW_HPP

#include <QWidget>
#include <vector>
#include "event.hpp"

/// Klasa implementująca obszar, w którym wyświetlane są wydarzenia
///
/// Zakres wyświetlanych wydarzeń obejmuje jeden dzień. Obiekty klasy EventDisplayWindow,
/// reprezentujące wyświetlane wydarzenia są odpowiednio skalowane i umieszczane w odpowiedniej pozycji,
/// w zależności od godziny rozpoczęcia i czasu trwania.
class TimetableWindow : public QWidget {
private:
    std::vector<Event*> *events;
    QDate current_date;
    int WIDTH = 720, HEIGHT = 960;
public:
    /// Konstruktor
    ///
    /// @param _date Określa datę, dla której mają zostać wyświetlone wydarzenia.
    /// @param _events Zbiór wydarzeń które należy wyświetlić.
    /// @param parent Obiekt klasy QWidget - rodzic.
    TimetableWindow(const QDate &_date, std::vector<Event*> *_events = nullptr, QWidget *parent = nullptr);
};

#endif