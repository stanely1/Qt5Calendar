#include <QVBoxLayout>
#include <QFrame>
#include "main_window.hpp"
#include "event_add_edit_window.hpp"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), current_date(QDate::currentDate())
{
    this->resize(960,720);

    font = QFont(font_family,font_size);
    this->setFont(font);

    auto *vbox = new QVBoxLayout(this);
    auto *hbox = new QHBoxLayout(this);

    date_button = new QPushButton(current_date.toString(),this);
    auto *left_button = new QPushButton("<",this);
    auto *right_button = new QPushButton(">",this);
    auto *add_event_button = new QPushButton("+",this);
    auto *option_button = new QPushButton("=",this);

    connect(left_button, &QPushButton::clicked, this, &MainWindow::decrementDate);
    connect(right_button, &QPushButton::clicked, this, &MainWindow::incrementDate);
    connect(add_event_button, &QPushButton::clicked, this, &MainWindow::onAddEvent);

    hbox->addWidget(option_button,1,Qt::AlignLeft);
    hbox->addWidget(left_button,1,Qt::AlignRight);
    hbox->addWidget(date_button,0,Qt::AlignCenter);
    hbox->addWidget(right_button,1,Qt::AlignLeft);
    hbox->addWidget(add_event_button,1,Qt::AlignRight);

    vbox->addLayout(hbox);
    vbox->addStretch(1);

    this->setLayout(vbox);
}

void MainWindow::incrementDate()
{
    current_date = current_date.addDays(1);
    updateGUI();
}
void MainWindow::decrementDate()
{
    current_date = current_date.addDays(-1);
    updateGUI();
}

void MainWindow::updateGUI()
{
    date_button->setText(current_date.toString());
}

void MainWindow::onAddEvent()
{
    auto *adder = new EventAdderWindow();
    adder->show();
}

void MainWindow::addEvent(Event &event)
{
    QTextStream out(stdout);
    out << "add event: " << event.toString() << "\n";
}