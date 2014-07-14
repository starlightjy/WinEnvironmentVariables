#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Environment.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // TODO Voir pour mettre les premieres colonnes de chaque tableaux en ResizeToContents et la derniere en Stretch.
    // Enlever les resizeColumnsToContents et le strech last section sur les tables
//    ui->variablesTable->horizontalHeader()->

    loadVariables();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void    MainWindow::loadVariables()
{
    QList<Environment::Variable>    variables;

    variables = mEnvironment.variables();
    ui->variablesTable->setRowCount(variables.size());
    for (int i = 0; i < variables.size(); i++)
    {
        QTableWidgetItem*   newItem;

        newItem = new QTableWidgetItem(variables[i].name);
        ui->variablesTable->setItem(i, 0, newItem);

        // TODO put the owner in a combo box
        newItem = new QTableWidgetItem(variables[i].owner);
        ui->variablesTable->setItem(i, 1, newItem);

        newItem = new QTableWidgetItem(variables[i].value);
        ui->variablesTable->setItem(i, 2, newItem);

        newItem = new QTableWidgetItem(variables[i].expandedValue);
        ui->variablesTable->setItem(i, 3, newItem);
    }

    QList<Environment::Path>    paths;

    paths = mEnvironment.paths();
    ui->pathsTable->setRowCount(paths.size());
    for (int i = 0; i < paths.size(); i++)
    {
        QTableWidgetItem*   newItem;

        newItem = new QTableWidgetItem(paths[i].name);
        ui->pathsTable->setItem(i, 0, newItem);

        // TODO put the owner in a combo box
        newItem = new QTableWidgetItem(paths[i].owner);
        ui->pathsTable->setItem(i, 1, newItem);
    }

    ui->pathsTable->resizeColumnsToContents();
    ui->pathValuesTable->resizeColumnsToContents();
}

void MainWindow::on_pathsTable_itemSelectionChanged()
{
    ui->pathValuesTable->clearContents();
    ui->pathValuesTable->clearSelection();

    if (ui->pathsTable->selectionModel()->selectedRows().empty())
        return;

    int i = ui->pathsTable->selectionModel()->selectedRows().at(0).row();
    QList<Environment::Path>    paths;

    paths = mEnvironment.paths();
    ui->pathValuesTable->setRowCount(paths[i].paths.size());
    for (int j = 0; j < paths[i].paths.size(); j++)
    {
        QTableWidgetItem*   newItem;

        newItem = new QTableWidgetItem(paths[i].paths[j]);
        ui->pathValuesTable->setItem(j, 0, newItem);

        newItem = new QTableWidgetItem(paths[i].evaluatedPaths[j]);
        ui->pathValuesTable->setItem(j, 1, newItem);
    }

    ui->pathValuesTable->resizeColumnsToContents();
}
