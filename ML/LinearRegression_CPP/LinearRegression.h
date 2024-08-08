//
// Created by jim on 07.08.24.
//

#ifndef LINEARREGRESSION_CPP_LINEARREGRESSION_H
#define LINEARREGRESSION_CPP_LINEARREGRESSION_H
#include "Matrix.h"
#include <vector>
#include <cmath>

using std::vector;
using std::pow;

class LinearRegression {
private:
    Matrix X, Y;
    Matrix _coef;
    vector<std::string> featureNames;

    Matrix mnk();
    void gd(double learningRate=0.1);

    double MSE();
    double MAE();


public:

    LinearRegression(Matrix& _X, Matrix& _Y);
    void fit();
    double predict(Matrix& _X);


};

class RegressionMetrics{
public:
    static double mean(const Matrix &a);
    static double MSE(Matrix y_true, Matrix y_predicted);
    static double MAE(Matrix y_true, Matrix y_predicted);
    static double MAPE(Matrix y_true, Matrix y_predicted);
    static double R2(Matrix y_true, Matrix y_predicted);
};


#endif //LINEARREGRESSION_CPP_LINEARREGRESSION_H
