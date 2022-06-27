#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <QTextStream>
#include <QDateTime>
#include <QWidget>
#include <QMouseEvent>

/// Klasa reprezentująca wydarzenia
///
/// Wydarzenie składa się z tytułu, opisu oraz daty rozpoczęcia i zakończenia.
class Event {
private:
    QString title;
    QString description;
    QDateTime start;
    QDateTime end;
public:
    /// Konstruktor
    Event(const QString &_title, const QString &_description, const QDateTime &_start, const QDateTime &_end);
    /// Uruchamia edytor wydarzenia
    ///
    /// Ta metoda tworzy obiekt klasy EventEditorWindow.
    void runEditor();

    /// Zwraca tekstową reprezentację wydarzenia w formacie czytelnym dla użytkownika
    QString toString();
    /// Zwraca tekstową reprezentację wydarzenia w specjalnym formacie
    ///
    /// Ta funkcja jest używana przez klasę EventSaver przy zapisie wydarzeń do pliku.
    QString toStringStorable();

    /// Zwraca tytuł wydarzenia
    QString getTitle() const;
    /// Zwraca opis wydarzenia
    QString getDescription() const;
    /// Zwraca datę rozpoczęcia wydarzenia
    QDateTime getStart() const;
    /// Zwraca datę zakończenia wydarzenia
    QDateTime getEnd() const;

    /// Ustawia tytuł wydarzenia
    void setTitle(const QString &_title);
    /// Ustawia opis wydarzenia
    void setDescription(const QString &_description);
    /// Ustawia datę rozpoczęcia wydarzenia
    void setStart(const QDateTime &_start);
    /// Ustawia datę zakończenia wydarzenia
    void setEnd(const QDateTime &_end);
};

/// Klasa implementująca graficzną reprezentację wydarzenia
class EventDisplayWindow : public QWidget {
private: 
    Event *event;
public:
    /// Konstruktor
    ///
    /// @param _event Reprezentowane wydarzenie.
    /// @param parent Obiekt klasy QWidget, będący rodzicem tworzonego obiektu.
    /// @param size Wskazuje, jak dużo informacji będzie wyświetlanych. Jeśli ten parametr ma wartość
    /// 1, to widoczny jest tylko tytuł wydarzenia, jeśli 2, wyświetlana jest także data rozpoczęcia,
    /// a jeśli 3, to dodatkowo widoczna jest data zakończenia.
    EventDisplayWindow(Event *_event, QWidget *parent = nullptr, int size = 3);
protected:
    /// Ta metoda nadpisuje metodę QWidget::mousePressEvent() z klasy bazowej
    ///
    /// Jest ona wywoływana, gdy wykryte zostanie kliknięcie myszką na dany obiekt.
    /// Jeśli nastąpiło kliknięcie lewym przyciskiem myszy, wywoływana jest
    /// metoda Event::runEditor() dla reprezentowanego wydarznia.
    virtual void mousePressEvent(QMouseEvent *mouse_event);
};

#endif