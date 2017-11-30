#include "GUI.hpp"
#include "common.hpp"

#include <QPushButton>


GUI::GUI() : app(nullptr), board(nullptr) {}
void GUI::display() {}

int GUI::start(int *argcp, char *argv[])
{
    if (app != nullptr) {
        std::cerr << "This application is already started." << std::endl;
        return -1;
    }

    load_board("sample/sample1.txt");

    app = new QApplication(*argcp, argv);
    main_window = new MainWindow;
    main_window->show();
    return app->exec();
}

void GUI::step()
{
    board->step();
}

void GUI::draw(QGraphicsScene *scene)
{
    scene->clear();
    board->draw(scene);
}

void GUI::load_board(std::string fname)
{
    board = new BoardGUI(common::read_file(fname));
    board->add_ball(2, -1, BLUE);
}

GUI& GUI::get_instance()
{
    static GUI gui;
    return gui;
}
