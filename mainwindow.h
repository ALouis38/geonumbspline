#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPointF>
#include <iostream>
#include <vector>

#define ITERATION 100


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene scene;
    std::vector<QPointF> listePoints;
    std::vector<QPointF> listePointsFinaux;
    std::vector<double> tabT;

    void draw();
    std::vector<double> * calculOmega(int i, int k, std::vector<double> & t);

    QPointF rechercherPoint(QPointF p1, QPointF p2, double t);
    void afficherListePoints(std::vector<QPointF> &listeP,QRgb rgb);
    void afficherPoint(QPointF &p,QRgb rgb);

    double calculOmega(int i, int k, double t);
};

#endif // MAINWINDOW_H
