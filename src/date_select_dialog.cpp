#include "date_select_dialog.hpp"
#include <QSpinBox>
#include <QHBoxLayout>
#include <QLabel>

DateSelectDialog::DateSelectDialog(int _year, int _month, QWidget *parent) : 
    QDialog(parent), year(_year), month(_month)
{
    setModal(true);
    setWindowTitle("Select Date");

    // year and month selection
    auto *year_selector = new QSpinBox;
    auto *month_selector = new QSpinBox;

    year_selector ->setRange(MIN_YEAR,MAX_YEAR);
    month_selector->setRange(1,12);

    year_selector ->setValue(year);
    month_selector->setValue(month);

    year_selector ->setMinimumWidth(80);
    month_selector->setMinimumWidth(80);

    connect(year_selector, qOverload<int>(&QSpinBox::valueChanged),this,&DateSelectDialog::onYearChange);
    connect(month_selector,qOverload<int>(&QSpinBox::valueChanged),this,&DateSelectDialog::onMonthChange);

    auto *hbox = new QHBoxLayout;
    hbox->addWidget(year_selector);
    hbox->addWidget(month_selector);

    // vbox layout
    auto *vbox = new QVBoxLayout;
    setLayout(vbox);
    vbox->addLayout(hbox);
    // vbox->addLayout(weekday_hbox);

    // day selection
    setGrid();
}

void DateSelectDialog::setGrid()
{
    if(grid != nullptr) layout()->removeWidget(grid), delete grid;

    grid = new DaySelectGrid(year,month);
    layout()->addWidget(grid);
}

// slots
void DateSelectDialog::onYearChange(int y)
{
    year = y;
    setGrid();
}
void DateSelectDialog::onMonthChange(int m)
{
    month = m;
    setGrid();
}

void DateSelectDialog::selectDate(int d)
{
    main_window->setDate(QDate(year,month,d));
    close();
}

// day select grid
DaySelectGrid::DaySelectGrid(int y, int m, DateSelectDialog *parent) : QWidget(parent)
{
    auto *grid = new QGridLayout(this);

    static QStringList weekday_name {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
    for(int i = 0; i < 7; i++) grid->addWidget(new QLabel(weekday_name[i]), 0, i+1, Qt::AlignCenter);

    int week_number = 1;
    for(auto date = QDate(y,m,1); date.month() == m; date = date.addDays(1))
    {
        auto *button = new QPushButton(QString("%1").arg(date.day()));
        connect(button,&QPushButton::clicked,this,&DaySelectGrid::select);
        button->setCursor(Qt::PointingHandCursor);
        grid->addWidget(button, week_number, date.dayOfWeek());

        if(date.dayOfWeek() == 7) week_number++;
    }
}

void DaySelectGrid::select()
{
    qobject_cast<DateSelectDialog*>(parent())->selectDate(qobject_cast<QPushButton*>(sender())->text().toInt());
}