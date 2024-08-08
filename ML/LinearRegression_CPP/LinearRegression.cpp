//
// Created by jim on 07.08.24.
//

#include "LinearRegression.h"


Matrix LinearRegression::mnk(){
    Matrix X_Transposed = X;
    X_Transposed.transpose();
    Matrix X_quadric = (X_Transposed * X);
    Matrix Inversed = X_quadric.inverse();

    Matrix tmp_2 = X_Transposed * Y;

    _coef = Inversed * tmp_2;

    _coef.print("coeff");

    return this->_coef;
}

LinearRegression::LinearRegression(Matrix &_X, Matrix &_Y) : X(_X), Y(_Y) {
    Matrix leftMatrix(X.getShape().first, 1, 1);
}


double RegressionMetrics::MAE(Matrix y_true, Matrix y_predicted) {
    if(y_true.getShape().first != y_predicted.getShape().first || y_true.getShape().second != y_predicted.getShape().second)
        throw std::logic_error("vector dimensions do not match ");
    double result = 0;
    for(size_t i = 0; i < y_true.getShape().first; ++i){
        result += std::abs(y_true.getElement(i, 0) - y_predicted.getElement(i, 0));
    }
    return result / (double)y_true.getShape().first;
}

double RegressionMetrics::MSE(Matrix y_true, Matrix y_predicted) {
    if(y_true.getShape().first != y_predicted.getShape().first || y_true.getShape().second != y_predicted.getShape().second)
        throw std::logic_error("vector dimensions do not match ");
    double result = 0;
    for(size_t i = 0; i < y_true.getShape().first; ++i){
        result += pow(y_true.getElement(i, 0) - y_predicted.getElement(i, 0), 2);
    }
    return result / (double)y_true.getShape().first;
}

double RegressionMetrics::MAPE(Matrix y_true, Matrix y_predicted) {
    if(y_true.getShape().first != y_predicted.getShape().first || y_true.getShape().second != y_predicted.getShape().second)
        throw std::logic_error("vector dimensions do not match ");
    double result = 0;
    for(size_t i = 0; i < y_true.getShape().first; ++i){
        result += std::abs(y_true.getElement(i, 0) - y_predicted.getElement(i, 0))/ std::abs(y_true.getElement(i, 0));
    }
    // TODO("Сделать ветвление на случай вектора [1xn]")
    return result / (double)y_true.getShape().first;
}

double RegressionMetrics::mean(const Matrix &a) {
    double result = 0;
    for (size_t i = 0; i < a.getShape().first; ++i) {
        for (size_t j = 0; j < a.getShape().second; ++j) {
            result += a.getElement(i, j);
        }
    }
    return result/(double)(a.getShape().first * a.getShape().second);
}

double RegressionMetrics::R2(Matrix y_true, Matrix y_predicted)  {
    // TODO("Сделать ветвление на случай вектора [1xn]")

    if(y_true.getShape().first != y_predicted.getShape().first || y_true.getShape().second != y_predicted.getShape().second)
        throw std::logic_error("vector dimensions do not match ");
    double ss_res = 0, ss_tot = 0;
    double mean = RegressionMetrics::mean(y_predicted);

    for(size_t i = 0; i < y_true.getShape().first; ++i){
        ss_res += pow((y_true.getElement(i, 0) - y_predicted.getElement(i, 0)), 2);
        ss_tot +=  pow((y_true.getElement(i, 0) - mean), 2);
    }
    return 1 - (ss_res / ss_tot);
}
