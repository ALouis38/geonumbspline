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

    srand (time(NULL));

    int n = 4;
    listePoints.push_back(QPointF(50,50));
    listePoints.push_back(QPointF(140,180));
    listePoints.push_back(QPointF(60,130));
    listePoints.push_back(QPointF(3.14159265369, 0.5));


//    listePoints.push_back(QPointF(200,200));

//    draw2();
//   draw3();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::draw()
{
    int k = 2; //degré de la courbe
    int n = 4; //nb de pts de la courbe

    int m = k+n+1;

    tabT = std::vector<double>(m+1); //tableau des noeuds

    //Remplissage du tableau de noeuds
    for (int i = 0; i < tabT.size(); ++i) {
        tabT[i] = i;
    }


//    for (int i = k; i < n+1; ++i) {
//        listePoints.push_back(S(t));
//    }
//    afficherListePoints(listePoints);
}


std::vector<double> * MainWindow::polynomeNi(int i, int k, std::vector<double> &t) {
    std::vector<double> *res = std::vector<double>(t.size());

    if (k == 0) {
        for (size_t j = 0; j < t.size(); ++j) {
            if (t[j] >= tabT[i] && t[j] < tabT[i+1]) {
                res[j] = 1;
            } else {
                res[j] = 0;
            }
        }
        return res;
    }

    std::vector<double> *omega1 = calculOmega(i, k, t);
    std::vector<double> *omega2 = calculOmega(i+1, k, t);

    std::vector<double> *Nikmoins1 = polynomeNi(i, k-1, t);
    std::vector<double> *Niplus1kmoins1 = polynomeNi(i+1, k-1, t);

    for (size_t j = 0; j < t.size(); ++j) {
        res[j] = omega1[j] * Nikmoins1[j] + (1 - omega2[j]) * Niplus1kmoins1[j];
    }

    return res;
}

std::vector<double> * MainWindow::clone( std::vector<double>& vect){
    std::vector<QPointF> *res = new std::vector<QPointF>(0);
    for (size_t i = 0; i < vect.size(); ++i) {
        res[i] = vec[i];
    }
    return res;
}

std::vector<double> * MainWindow::fonctionRecursive(int i, int r, std::vector<double> &t) {
    std::vector<double> *res = std::vector<double>(t.size());
    int k = 2;
    std::vector<QPointF> *listPointTmp1;
    std::vector<QPointF> *listPointTmp2 = new std::vector<QPointF>(0);

    std::vector<double> *omega = calculOmega(i, k-r-1, t);

    for (size_t i = 0; i < t.size()-1; ++i) {
        listPointTmp1 = clone(listePoints);
        listPointTmp2->clear();
        for (size_t j = 0; j < listePointTmp1.size(); ++j) {
            if (t >= t[i] && t < t[i+1]) {
                listPointTmp2->push_back( omega[i] * listPointTmp1[j] + (1 - omega[i]) * listPointTmp1[j+1] );
            }
        }
    }


    for (size_t j = 0; j < t.size(); ++j) {
        res[j] = omega1[j] * Nikmoins1[j] + (1 - omega2[j]) * Niplus1kmoins1[j];
    }

    return res;
}

std::vector<double> * MainWindow::calculOmega(int i, int k, std::vector<double> &t)
{
    std::vector<double> *res;
    if (t[i] < t[i+k]) {
        res = new std::vector<double>(t.size());
        for (size_t j = 0; j < t.size(); ++j) {
            res->push_back( (double)(t[j] - t[i]) / (double)(t[i+k] - t[i]) );
        }
    } else {
        res = new std::vector<double>(t.size(), 0);
    }
    return res;
}

QPointF MainWindow::rechercherPoint(QPointF p1, QPointF p2, double t)
{
    QPointF res(0,0);

    res.setX(p1.x()+t*(p2.x()-p1.x()));
    res.setY(p1.y()+t*(p2.y()-p1.y()));

    return res;
}

void MainWindow::afficherListePoints(std::vector<QPointF> &listeP, QRgb rgb)
{
    QPointF temp(listeP[0]);
    for (size_t i = 1; i < listeP.size(); ++i) {
        scene.addLine(temp.x(), temp.y(), listeP[i].x(), listeP[i].y(),QPen(QColor(rgb)));
        temp = listeP[i];
    }
}


//Fonctions Louis

double MainWindow::calculOmega(int k, int i, double t)
{
    if (tabT[i] < tabT[i+k]) {
        return (t - tabT[i])/(tabT[i+k]-tabT[i]);
    } else {
        return 0;
    }
}

double MainWindow::calculNi(int k, int i, double t)
{

}

