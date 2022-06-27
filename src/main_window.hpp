#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QWidget>
#include <QDate>
#include <QPushButton>
#include "timetable_window.hpp"

/// Klasa reprezentująca główne okno interfejsu programu
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
    /// Konstruktor
    MainWindow(QWidget *parent = nullptr);
    /// Destruktor
    ~MainWindow();

    /// Dodaje nowe wydarzenie
    ///
    /// @param event Wydarzenie, które ma zostać dodane.
    /// @param _init Wskazuje, czy funkcja jest wywoływana przy inicjalizacji programu (domyślnie nie jest).
    void addEvent(Event *event, bool _init = false);
    /// Usuwa istniejące wydarzenie
    ///
    /// @param event Wydarzenie, które jest usuwane.
    /// @param free_ptr Wskazuje, czy pamięć usuwanego wydarzenia ma być zwolniona.
    void deleteEvent(Event *event, bool free_ptr = true);

    /// Aktualizuje graficzny interfejs programu
    ///
    /// Funkcja ta jest wywoływana, gdy nastąpi zmiana stanu programu, wpływająca na wygląd interfejsu.
    void updateGUI();

    /// Ustawia bieżącą datę
    void setDate(const QDate &date);
    /// Zwraca bieżącą datę
    QDate getCurrentDate() const;
Q_OBJECT
private slots:
    void runDateSelector();
    void incrementDate();
    void decrementDate();
    void onAddEvent();
    void clearEvents();
protected:
    /// Ta metoda nadpisuje metodę QWidget::closeEvent() z klasy bazowej
    ///
    /// Zapisuje wszystkie istniejące wydarzenia i zamyka program.
    virtual void closeEvent(QCloseEvent *event);
    /// Ta metoda nadpisuje metodę QWidget::resizeEvent() z klasy bazowej
    ///
    /// Wywołuje metodę updateGUI(), żeby dostosować rozmiar innych elementów interfejsu.
    virtual void resizeEvent(QResizeEvent *event);
};

/// Globalny obiekt klasy MainWindow
extern MainWindow *main_window;

#define MIN_YEAR 2020
#define MAX_YEAR 3000

#endif