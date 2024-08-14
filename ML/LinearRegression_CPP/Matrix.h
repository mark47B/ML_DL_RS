//
// Created by jim on 07.08.24.
//

#ifndef LINEARREGRESSION_CPP_MATRIX_H
#define LINEARREGRESSION_CPP_MATRIX_H

#include <tuple>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>

using std::tuple;
using std::cout;
using std::endl;
using std::pow;
using std::map;
using std::vector;

class Matrix {
private:
    double** data;
    size_t rows, columns;
    friend class MatrixAdapter;
public:
    Matrix();
    Matrix(size_t _rows, size_t _columns);
    Matrix(size_t _rows, size_t _columns, double values);
    Matrix(const Matrix &_m);
    Matrix(Matrix &&rMatrix) noexcept;
    Matrix(map<std::string, vector<double>> _map);
    explicit Matrix(const vector<vector<double>> &_m);
    explicit Matrix(const vector<double> &_m);
    ~Matrix();


    void makeEye();
    Matrix& randomise(unsigned factor = 10);
    Matrix& transpose();
    Matrix& normalize();


    void print(const char *label = "noname") const;
    double getElement(size_t r, size_t c) const;
    Matrix getRow(size_t r) const;
    Matrix getRows(size_t from, size_t count = 1) const;
    std::pair<size_t, size_t> getShape() const;

    Matrix getMinor(int r, int c) const;
    Matrix concatRight(Matrix &B) const;
    Matrix concatLeft(Matrix &B) const;
    Matrix inverse() const;

    void setElement(size_t r, size_t c, double value);

    Matrix& operator=(const Matrix &_M);
    Matrix& operator=(Matrix &&m) noexcept;
    Matrix operator+(Matrix &m) const;
    Matrix operator-(const Matrix &right) const;
    Matrix operator*(const Matrix &right) const; // Перемножение матриц O(n^3)
    Matrix operator*(double right) const; // Перемножение матриц O(n^3)
    Matrix operator/(double right) const; // Поделить каждый элемент матрицы на число

    [[nodiscard]] double det() const;
    [[nodiscard]] Matrix AlgebraicComplements() const;
};

//  Определение дополнительных операций для класса Matrix
Matrix operator*(double val, const Matrix& M);


// MatrixAdapter  нужен для преобразования C++ контейнеров в Matrix и обратно

class MatrixAdapter{
public:
    static vector<vector<double>> MatrixToVector(Matrix& m){
        auto rows = m.getShape().first;
        auto cols = m.getShape().second;
        vector<vector<double>> new_vector(rows, vector<double>(cols));

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                new_vector[i][j] = m.getElement(i, j);
            }
        }
        return std::move(new_vector);
    }

    static double** MatrixToPointer(Matrix& m) { // THERE IS DANGEROUS METHOD!
        return m.data;
    }
};


#endif //LINEARREGRESSION_CPP_MATRIX_H
