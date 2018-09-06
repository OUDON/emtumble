#ifndef BOARD_SIZE_DIALOG_H
#define BOARD_SIZE_DIALOG_H

#include <QDialog>

namespace Ui {
class BoardSizeDialog;
}

class BoardSizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BoardSizeDialog(QWidget *parent = 0, int cur_width = 0, int cur_height = 0);
    ~BoardSizeDialog();

    int get_new_width() const;
    int get_new_height() const;

private:
    Ui::BoardSizeDialog *ui;
};

#endif // BOARD_SIZE_DIALOG_H
