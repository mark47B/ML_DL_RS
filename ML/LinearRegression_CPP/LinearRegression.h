//
// Created by jim on 07.08.24.
//

#ifndef LINEARREGRESSION_CPP_LINEARREGRESSION_H
#define LINEARREGRESSION_CPP_LINEARREGRESSION_H
#include "Matrix.h"
#include <utility>
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
    void sgd(double learningRate=0.9, int epoch = 1000, size_t batch_size = 32);

public:

    enum TrainingMethods{
        GradientDecent, // SGD
        LeastSquares // МНК
    };

    LinearRegression(Matrix& _X, Matrix& _Y);
    LinearRegression(Matrix& _X, Matrix& _Y, Matrix& coefficients);

    void setFeatureNames( vector<std::string> _featureNames){
        featureNames = std::move(_featureNames);
    }

    Matrix getCoefficients();

    void fit(LinearRegression::TrainingMethods method);
    Matrix predict(Matrix& _X) const;
    Matrix predict_without_bias(Matrix& _X) const;


    double predict(vector<double> x) const;

    double predict(const double *x, size_t size_x) const;
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
