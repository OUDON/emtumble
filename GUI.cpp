#include "GUI.hpp"
#include "common.hpp"

#include <QPushButton>


GUI::GUI() : app(nullptr) {}

int GUI::start(int *argcp, char *argv[])
{
    if (app != nullptr) {
        std::cerr << "This application is already started." << std::endl;
        return -1;
    }

    app = new QApplication(*argcp, argv);
    main_window = new MainWindow;
    main_window->show();
    return app->exec();
}

GUI& GUI::get_instance()
{
    static GUI gui;
    return gui;
}
