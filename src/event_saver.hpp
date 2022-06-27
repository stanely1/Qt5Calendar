#ifndef EVENT_SAVER_HPP
#define EVENT_SAVER_HPP

#include "event.hpp"
#include "main_window.hpp"

/// Klasa implementująca mechanizm zapisu i odczytu wydarzeń do/z zewnętrznego pliku
class EventSaver {
public:
    /// Zapisuje wydarzenia do pliku
    ///
    /// @param events Zbiór wydarzeń do zapisania.
    static void saveEvents(const std::map<QDate,std::vector<Event*>> &events);
    /// Odczytuje wydarzenia z pliku i dodaje do programu
    ///
    /// @param _main_window Obiekt klasy MainWindow, do którego dodawane są odczytane wydarzenia
    /// za pomocą metody MainWindow::addEvent().
    static void readEvents(MainWindow *_main_window);
};

#endif