#include <QApplication>
#include "main_window.hpp"

/// Program main function
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    main_window = new MainWindow;

    main_window->show();
    return app.exec();
}