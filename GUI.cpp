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
    board->add_ball(2, -1, BLUE);

    app = new QApplication(*argcp, argv);
    main_window = new MainWindow;

    // QPushButton *button_step = ui.button_step;
    // QObject::connect(button_step, SIGNAL(clicked()), &app, SLOT(Ui::MainWindow::step()));

    // ui.graphics_view->setScene(scene);

    main_window->show();
    return app->exec();
}

void GUI::step()
{
    board->step();
}

void GUI::draw(QGraphicsScene *scene)
{
    board->draw(scene);
}

void GUI::load_board(std::string fname)
{
    board = new BoardGUI(common::read_file(fname));
    board->print();
}

GUI& GUI::get_instance()
{
    static GUI gui;
    return gui;
}
