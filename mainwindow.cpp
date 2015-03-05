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

    listePoints.push_back(QPointF(150,150));
    listePoints.push_back(QPointF(200,100));
    listePoints.push_back(QPointF(300,110));
    listePoints.push_back(QPointF(400, 150));

    draw();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw()
{
    int k = 2; //degré de la courbe
    int n = 6; //nb de pts de la courbe

    int m = k+n+1;

    tabT = std::vector<double>(m+1); //tableau des noeuds

    //Remplissage du tableau de noeuds
    for (size_t i = 0; i < tabT.size(); ++i) {
        tabT[i] = i;
    }


    ///Ajouts Louis
    std::vector<QPointF> etageDuDessus;
    std::vector<QPointF> listPointTmp;

    for (float t = tabT[k]; t < tabT[n+1]; t+=0.2) {
        etageDuDessus = listePoints;

        int j = (int)t;
        //while (t < tabT[j+1]) {
            //Calcul de d(k,j)
            for (int r = 1; r < k+1; ++r) {//il y a une modif ici
                for (int i = r; i <= j; ++i) {
                    double om = calculOmega(k-r,i,t);
//                    std::cout << " k-r = " << k-r << " i = " << i << " t = " << t
//                              << " j = " << j << " n = " << n << std::endl;
//                    std::cout << "om = " << om << std::endl;
                    double nouvX = om*etageDuDessus[i].x() + (1.0-om)*etageDuDessus[i-1].x();
                    double nouvY = om*etageDuDessus[i].y() + (1.0-om)*etageDuDessus[i-1].y();
                    listPointTmp.push_back(QPointF(nouvX,nouvY));
                }
                etageDuDessus = listPointTmp;
                listPointTmp.clear();
            }
            listePointsFinaux.push_back(etageDuDessus[0]);
            t = t + 0.1;

        //}
    }


//    for (int j = k; j < n+1; ++j) {
//        etageDuDessus = listePoints;

//        double t = tabT[j];
//        while (t < tabT[j+1]) {
//            //Calcul de d(k,j)
//            for (int r = 1; r < k+1; ++r) {//il y a une modif ici
//                for (int i = r; i < k+1; ++i) {
//                    double om = calculOmega(k-r,i,t);
////                    std::cout << " k-r = " << k-r << " i = " << i << " t = " << t
////                              << " j = " << j << " n = " << n << std::endl;
////                    std::cout << "om = " << om << std::endl;
//                    double nouvX = om*etageDuDessus[i].x() + (1.0-om)*etageDuDessus[i-1].x();
//                    double nouvY = om*etageDuDessus[i].y() + (1.0-om)*etageDuDessus[i-1].y();
//                    listPointTmp.push_back(QPointF(nouvX,nouvY));
//                }
//                etageDuDessus = listPointTmp;
//                listPointTmp.clear();
//            }
//            listePointsFinaux.push_back(etageDuDessus[0]);
//            t = t + 0.1;

//        }
//    }

    afficherListePoints(listePoints,qRgb(0,0,0));
    afficherListePoints(listePointsFinaux, qRgb(0,255,0));

    for (size_t var = 0; var < listePoints.size(); ++var) {
        std::cout << "(" << listePoints[var].x() << "," << listePoints[var].y() << ")" << std::endl;
    }

    for (size_t var = 0; var < listePointsFinaux.size(); ++var) {
        std::cout << "(" << listePointsFinaux[var].x() << "," << listePointsFinaux[var].y() << ")" << std::endl;
    }


//    for (int i = k; i < n+1; ++i) {
//        listePoints.push_back(S(t));
//    }
//    afficherListePoints(listePoints);
}


//std::vector<double> * MainWindow::polynomeNi(int i, int k, std::vector<double> &t) {
//    std::vector<double> *res = std::vector<double>(t.size());

//    if (k == 0) {
//        for (size_t j = 0; j < t.size(); ++j) {
//            if (t[j] >= tabT[i] && t[j] < tabT[i+1]) {
//                res[j] = 1;
//            } else {
//                res[j] = 0;
//            }
//        }
//        return res;
//    }

//    std::vector<double> *omega1 = calculOmega(i, k, t);
//    std::vector<double> *omega2 = calculOmega(i+1, k, t);

//    std::vector<double> *Nikmoins1 = polynomeNi(i, k-1, t);
//    std::vector<double> *Niplus1kmoins1 = polynomeNi(i+1, k-1, t);

//    for (size_t j = 0; j < t.size(); ++j) {
//        res[j] = omega1[j] * Nikmoins1[j] + (1 - omega2[j]) * Niplus1kmoins1[j];
//    }

//    return res;
//}

//std::vector<double> * MainWindow::clone( std::vector<double>& vect){
//    std::vector<QPointF> *res = new std::vector<QPointF>(0);
//    for (size_t i = 0; i < vect.size(); ++i) {
//        res[i] = vec[i];
//    }
//    return res;
//}

//std::vector<double> * MainWindow::fonctionRecursive(int i, int r, std::vector<double> &t) {
//    std::vector<double> *res = std::vector<double>(t.size());
//    int k = 2;
//    std::vector<QPointF> *listPointTmp1;
//    std::vector<QPointF> *listPointTmp2 = new std::vector<QPointF>(0);

//    std::vector<double> *omega = calculOmega(i, k-r-1, t);

//    for (size_t i = 0; i < t.size()-1; ++i) {
//        listPointTmp1 = clone(listePoints);
//        listPointTmp2->clear();
//        for (size_t j = 0; j < listePointTmp1.size(); ++j) {
//            if (t >= t[i] && t < t[i+1]) {
//                listPointTmp2->push_back( omega[i] * listPointTmp1[j] + (1 - omega[i]) * listPointTmp1[j+1] );
//            }
//        }
//    }


//    for (size_t j = 0; j < t.size(); ++j) {
//        res[j] = omega1[j] * Nikmoins1[j] + (1 - omega2[j]) * Niplus1kmoins1[j];
//    }

//    return res;
//}

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
        return (t - tabT[i])/(double(tabT[i+k])-double(tabT[i]));
    } else {
        return 0;
    }
}

double MainWindow::calculNi(int k, int i, double t)
{
    return 0.0;
}

