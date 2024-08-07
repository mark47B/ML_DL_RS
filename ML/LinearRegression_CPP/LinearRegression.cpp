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