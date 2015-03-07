#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <cmath>
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(),
    listePoints(),
    listePointsFinaux(),
    tabT()
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);

    scene.setSceneRect(0,0,400,300);

    listePoints.push_back(QPointF(150, 200));
    listePoints.push_back(QPointF(100, 100));
    listePoints.push_back(QPointF(200, 100));
    listePoints.push_back(QPointF(300, 150));
    for (size_t i = 0; i < listePoints.size(); ++i) {
        afficherPoint(listePoints[i], qRgb(255, 0, 0));
    }

    draw();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw() {
    int k = 2;
    int n = int(listePoints.size())-1;
    int m = n+k+1;

    tabT = std::vector<double>(m+1);
    for (size_t i = 0; i < tabT.size(); ++i) {
        tabT[i] = i;
    }

    std::vector<QPointF> etageDuDessus;
    std::vector<QPointF> listPointTmp;

    for (double t = tabT[k]; t <= tabT[n+1]; t += 0.1) {
        int j = floor(t);
        // Initialization de etageDuDessus, ok !
        etageDuDessus.clear();
        for (int var = 0; var < k+1; ++var) {
            etageDuDessus.push_back(listePoints[j-k+var]);
        }

        // Calcul du d(k,j)
        for (int r = 1; r < k+1; ++r) {
            for (size_t i = 1; i < etageDuDessus.size(); ++i) {
                double om = calculOmega(j-k+r+i-1, k-r+1, t);
                double nouvX = om * etageDuDessus[i].x() + (1.0-om) * etageDuDessus[i-1].x();
                double nouvY = om * etageDuDessus[i].y() + (1.0-om) * etageDuDessus[i-1].y();
                listPointTmp.push_back(QPointF(nouvX,nouvY));
            }

            etageDuDessus = listPointTmp;
            listPointTmp.clear();
        }

        listePointsFinaux.push_back(etageDuDessus[0]);
    }

    afficherListePoints(listePoints,qRgb(0,0,0));
    afficherListePoints(listePointsFinaux, qRgb(0,255,0));
}

QPointF MainWindow::rechercherPoint(QPointF p1, QPointF p2, double t)
{
    QPointF res(0,0);

    res.setX(p1.x()+t*(p2.x()-p1.x()));
    res.setY(p1.y()+t*(p2.y()-p1.y()));

    return res;
}

void MainWindow::afficherListePoints(std::vector<QPointF> &listeP, QRgb rgb) {
    QPointF temp(listeP[0]);
    for (size_t i = 1; i < listeP.size(); ++i) {
        scene.addLine(temp.x(), temp.y(), listeP[i].x(), listeP[i].y(), QPen(QColor(rgb)));
        temp = listeP[i];
    }
}

void MainWindow::afficherPoint(QPointF &p, QRgb rgb) {
    scene.addLine(p.x()-4, p.y()-4, p.x()+4, p.y()+4, QPen(QColor(rgb)));
    scene.addLine(p.x()-4, p.y()+4, p.x()+4, p.y()-4, QPen(QColor(rgb)));
}

double MainWindow::calculOmega(int i, int k, double t) {
    if (tabT[i] < tabT[i+k]) {
        return (t - tabT[i])/(double(tabT[i+k])-double(tabT[i]));
    } else {
        return 0;
    }
}
