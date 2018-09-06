#include "board_size_dialog.h"
#include "ui_board_size_dialog.h"
#include <QValidator>

BoardSizeDialog::BoardSizeDialog(QWidget *parent, int cur_width, int cur_height) :
    QDialog(parent),
    ui(new Ui::BoardSizeDialog)
{
    ui->setupUi(this);

    ui->current_width_label->setText(QString::number(cur_width));
    ui->current_height_label->setText(QString::number(cur_height));
    ui->new_width_edit->setText(QString::number(cur_width));
    ui->new_height_edit->setText(QString::number(cur_height));

    QValidator *validator = new QIntValidator(1, 1000, this);
    ui->new_width_edit->setValidator(validator);
    ui->new_height_edit->setValidator(validator);
}

int BoardSizeDialog::get_new_width() const
{
    return ui->new_width_edit->text().toInt();
}

int BoardSizeDialog::get_new_height() const
{
    return ui->new_height_edit->text().toInt();
}

BoardSizeDialog::~BoardSizeDialog()
{
    delete ui;
}
