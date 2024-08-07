//
// Created by jim on 07.08.24.
//

#ifndef LINEARREGRESSION_CPP_MATRIX_H
#define LINEARREGRESSION_CPP_MATRIX_H

#include <tuple>
#include <cstdlib>
#include <iostream>
#include <cmath>

using std::tuple;
using std::cout;
using std::endl;
using std::pow;


class Matrix {
private:



    double** data;
    size_t rows, columns;
public:
    Matrix();
    Matrix(size_t _rows, size_t _columns);
    Matrix(const Matrix &_m);
    Matrix(Matrix &&rMatrix) noexcept;
    ~Matrix();




    void makeEye();
    Matrix& randomise();
    Matrix& transpose();


    void print(const char *label = "noname") const;
    double getElement(size_t r, size_t c) const;
    std::pair<size_t, size_t> getShape() const;

    Matrix getMinor(int r, int c) const;
    Matrix concatRight(Matrix &B) const;
    Matrix inverse() const;

    void setElement(size_t r, size_t c, double value);


    Matrix& operator=(const Matrix &_M);
    Matrix& operator=(Matrix &&m) noexcept;
    Matrix  operator+(Matrix &m);
    Matrix operator-(const Matrix &right);
    Matrix operator*(const Matrix &right); // Перемножение матриц O(n^3)
    Matrix operator/(const double right); // Поделить каждый элемент матрицы на число

    [[nodiscard]] double det() const;

    Matrix AlgebraicComplements() const;
};


#endif //LINEARREGRESSION_CPP_MATRIX_H
