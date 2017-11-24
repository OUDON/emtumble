#include "GUI.hpp"
#include "common.hpp"

GUI::GUI() : board(nullptr) {}
void GUI::display() {}

int GUI::start(int *argcp, char *argv[])
{
    load_board("sample/sample1.txt");

    QApplication app(*argcp, argv);
    Paint paint;
    paint.show();
    return app.exec();
}

void GUI::load_board(std::string fname)
{
    board = new Board(common::read_file(fname));
    board->print();
}

GUI& GUI::get_instance()
{
    static GUI gui;
    return gui;
}

void Paint::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen my_pen(Qt::black, 2, Qt::SolidLine);
    painter.setPen(my_pen);
    painter.drawLine(100, 100, 100, 1);
}
