//
// Created by jim on 07.08.24.
//

#ifndef LINEARREGRESSION_CPP_LINEARREGRESSION_H
#define LINEARREGRESSION_CPP_LINEARREGRESSION_H
#include "Matrix.h"
#include <vector>

using std::vector;

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


#endif //LINEARREGRESSION_CPP_LINEARREGRESSION_H
