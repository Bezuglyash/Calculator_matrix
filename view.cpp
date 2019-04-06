#include "view.h"
#include "model_matrix.h"
#include "ui_view.h"
#include <QDebug>
#include "QString"
#include "QTimer"

View::View(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::View)
{
    ui->setupUi(this);
    connect (ui->Row, SIGNAL(currentIndexChanged(const QString &)), this, SLOT (on_Row_currentTextChanged (const QString)));
    connect (ui->Column, SIGNAL(currentIndexChanged(const QString &)), this, SLOT (on_Column_currentTextChanged(const QString)));
    connect (ui->Row, SIGNAL(currentIndexChanged(const QString &)), this, SLOT (Update_matrix (const QString &)));
    connect (ui->Column, SIGNAL(currentIndexChanged(const QString &)), this, SLOT (Update_matrix (const QString &)));
    connect (ui->Choise_of_number, SIGNAL(currentIndexChanged(const QString &)), this, SLOT (on_Choise_of_number_currentTextChanged(const QString &)));

}

View::~View()
{
    delete ui;
}

void View::on_Row_currentTextChanged(const QString &arg1)
{
    int row;
    row = arg1.toInt();
    array->set_rows(row);
    /**qDebug()<<array->rows;*/
}

void View::on_Column_currentTextChanged(const QString &arg1)
{
    int column;
    column = arg1.toInt();
    array->set_columns(column);
    /**qDebug()<<array->columns;*/
}

void View::Update_matrix(const QString & r_c)
{
    int rows_matrix, columns_matrix;
    rows_matrix = array->rows;
    columns_matrix = array->columns;

    if (array->count_matrix > 5)
    {
        array->count_matrix = 1;
        ui->Matrix_2->setVisible(false);
    }

    if (rows_matrix > 7)
    {
        rows_matrix = 2;
    }

    if (columns_matrix > 7)
    {
        columns_matrix = 2;
    }

    QLayoutItem* ch;
    while ((ch = ui->gridLayout->takeAt(0))!= nullptr)
    {
        delete ch->widget();
    }

    while ((ch = ui->gridLayout_2->takeAt(0))!= nullptr)
    {
        delete ch->widget();
    }

    if (array->count_matrix == 1)
    {
        for (int i = 0; i < rows_matrix; i++)
        {
            for (int j = 0; j < columns_matrix; j++)
            {
                QLineEdit* size = new QLineEdit("");
                ui->gridLayout->addWidget (size = new QLineEdit ("  0"), i + 2, j + 1);
                size->setFixedSize(24, 19);
                ui->gridLayout->setRowStretch(rows_matrix, i);
                ui->gridLayout->setColumnStretch(columns_matrix, j);
            }
        }
    }

    else if (array->count_matrix == 2)
    {
        for (int i = 0; i < rows_matrix; i++)
        {
            for (int j = 0; j < columns_matrix; j++)
            {
                QLineEdit* size = new QLineEdit("");
                ui->gridLayout->addWidget (size = new QLineEdit ("  0"), i + 2, j + 1);
                size->setFixedSize(24, 19);
                ui->gridLayout->setRowStretch(rows_matrix, i);
                ui->gridLayout->setColumnStretch(columns_matrix, j);

                QLineEdit* size2 = new QLineEdit("");
                ui->gridLayout_2->addWidget (size2 = new QLineEdit ("  0"), i + 2, j + 1);
                size2->setFixedSize(24, 19);
                ui->gridLayout_2->setRowStretch(rows_matrix, i);
                ui->gridLayout_2->setColumnStretch(columns_matrix, j);
            }
        }
    }
}

void View::on_Choise_of_number_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Несколько матриц")
    {
        array->set_count_matrix(2);
        ui->many_Matrix->setEnabled(true);
        ui->one_Matrix->setEnabled(false);
        ui->Matrix_2->setVisible(true);

        for (int i = 0; i < array->rows; i++)
        {
            for (int j = 0; j < array->columns; j++)
            {
                QLineEdit* size2 = new QLineEdit("");
                ui->gridLayout_2->addWidget (size2 = new QLineEdit ("  0"), i + 2, j + 1);
                size2->setFixedSize(24, 19);
            }
        }
        connect (ui->Row, SIGNAL(currentIndexChanged(const QString &)), this, SLOT (Update_matrix (const QString &)));
        connect (ui->Column, SIGNAL (currentIndexChanged(const QString &)), this, SLOT (Update_matrix (const QString &)));
    }
    else if (arg1 == "Одна матрица")
    {
        array->set_count_matrix(1);
        ui->many_Matrix->setEnabled(false);
        ui->one_Matrix->setEnabled(true);
        ui->Matrix_2->setVisible(false);
        connect (ui->Row, SIGNAL(currentIndexChanged(const QString &)), this, SLOT (Update_matrix (const QString &)));
        connect (ui->Column, SIGNAL (currentIndexChanged(const QString &)), this, SLOT (Update_matrix (const QString &)));
    }
}


