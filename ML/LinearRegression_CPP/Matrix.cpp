//
// Created by jim on 07.08.24.
//

#include "Matrix.h"

Matrix::Matrix(size_t _rows, size_t _columns) : rows(_rows), columns(_columns), data{(double **) new double* [_rows]}{
    for (size_t i = 0; i < rows; i++) {
        data[i] = (double *) new double[columns];
        for (size_t j = 0; j < columns; ++j) {
            data[i][j] = 0;
        }
    }
}

[[maybe_unused]] Matrix::Matrix(const Matrix& _m) : rows(_m.getShape().first), columns(_m.getShape().second), data{(double **) new double* [_m.getShape().first]} {
    for (int i = 0; i < rows; i++) {
        data[i] = (double *) new double[columns];
    }
    for (size_t i = 0; i < rows; ++i){
        for (int j = 0; j < columns; ++j) {
            data[i][j] = _m.getElement(i, j);
        }
    }
}

[[maybe_unused]] Matrix::Matrix(Matrix&& rMatrix)  noexcept : rows(rMatrix.getShape().first), columns(rMatrix.getShape().second), data{rMatrix.data} {
    rMatrix.data = nullptr;
}

Matrix::~Matrix(){
    if (columns > 0) {
        for (size_t i = 0; i < rows; ++i) {
            delete[] data[i];
        }
    }
    if (rows > 0) {
        delete[] data;
    }
}


[[nodiscard]] std::pair<size_t, size_t>  Matrix::getShape() const {
    return std::pair{this->rows, this->columns};
}

[[nodiscard]] double  Matrix::getElement(size_t r, size_t c) const {
    if ((data != nullptr) && r < rows && c < columns)
        return data[r][c];
    else
        throw std::out_of_range("out of matrix range");
}

void  Matrix::setElement( size_t r,  size_t c, double value){
    if (r < rows && c < columns)
        data[r][c] = value;
    else
        throw std::out_of_range("out of matrix range");
}

void  Matrix::print(const char* label) const {
    cout << "Matrix: " << label << "; " << rows << " x " << columns << endl;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            cout << data[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "-------------------------------" << endl << endl;
}

void  Matrix::makeEye(){
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            data[i][j] = (i == j) ?  1 : 0;
        }
    }
}

Matrix Matrix::concatRight(Matrix& B) const {
    if (B.rows != this->rows){
        throw std::logic_error("Concat of matrices with different dimensions");
    }

    size_t a = this->rows, b = this->columns;

    Matrix A(a, b + B.columns); // Создаём матрицу размера m x (n + B.n)
    for (size_t i = 0; i < a; ++i) { // Записываем исходную матрицу в A
        for (size_t j = 0; j < b; ++j) {
            A.setElement(i, j, data[i][j]);
        }
    }
    for (int i = 0; i < B.rows; ++i) {
        for (int j = 0; j < B.columns; ++j) {
            A.setElement(i, b + j, B.getElement(i, j));
        }
    }
    return A;
}

Matrix&  Matrix::operator=(const Matrix &m){
    if (this == &m) {
        return *this;
    }
    if (columns > 0) {
        for (int i = 0; i < rows; ++i)
            delete[] data[i];
    }
    if (rows > 0) {
        delete[] data;
    }

    rows = m.rows;
    columns = m.columns;

    data = (double **) new double *[rows];
    for (size_t i = 0; i < rows; ++i) {
        data[i] = (double *) new double[columns];
        for (int j = 0; j < columns; ++j)
            data[i][j] = m.data[i][j];
    }
    return *this;
}

Matrix& Matrix::operator=(Matrix &&m) noexcept {
    if (this->columns > 0) {
    for (int i = 0; i < rows; ++i)
    delete[] data[i];
    }
    if (this->rows > 0) {
    delete[] data;
    }

    rows = m.rows;
    columns = m.columns;

    data = m.data;
    m.data = nullptr;
    m.rows = 0;
    m.columns = 0;
    return *this;
}

Matrix  Matrix::operator+(Matrix &m) const {
    if (this->rows != m.rows || this->columns != m.columns)
        throw std::logic_error("e: Addition of matrices with different dimensions");

    Matrix tmp(rows, columns);
    for (size_t i = 0; i < rows ; i++) {
        for (size_t j = 0; j < columns; ++j) {
            tmp.setElement(i, j, data[i][j] + m.data[i][j]);
        }
    }

    return tmp;
}
Matrix&  Matrix::transpose(){
    Matrix tmp(columns, rows);

    for (size_t i = 0; i < columns; ++i) {
        for (size_t j = 0; j < rows; ++j) {
            tmp.setElement(i, j, data[j][i]);
        }
    }
    *this = tmp;
    return *this;
}

Matrix&  Matrix::randomise(unsigned factor){
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            data[i][j] = rand()%factor;
        }
    }
    return *this;
}


Matrix  Matrix::inverse() const {
    double determinant_this = this->det();
    return this->AlgebraicComplements() / determinant_this;
}

Matrix Matrix::getMinor(int r, int c) const {
    Matrix _M(rows - 1, columns - 1);
    int t = 0, p = 0;
    for (size_t k = 0; k < rows; ++k) {
        if (k == r) {
            continue;
        }
        for (size_t l = 0; l < columns; ++l) {
            if (l == c) {
                continue;
            }
            _M.setElement(t, p, data[k][l]);
            ++p;
        }
        ++t;
        p = 0;
    }
    return _M;
}

double Matrix::det() const {
    if (columns != rows) {
        throw std::logic_error("To find the determinant of a matrix, the matrix must be square");
    }
    if (columns == 1) {
        return data[0][0];
    }
    if (columns == 2) {
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }
    double sum = 0;

    for (int i = 0; i < columns; ++i) {
        sum += pow(-1.0, 0 + i) * data[0][i] * ((this->getMinor(0, i)).det());
    }
    return sum;
}

Matrix Matrix::AlgebraicComplements() const {
    Matrix tmp_ag(rows, columns);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            auto tmp = this->getMinor(i, j);
            tmp_ag.setElement(i, j, tmp.det() * pow(-1, i + j));
        }
    }
    tmp_ag.transpose();
    return tmp_ag;
}

Matrix Matrix::operator-(const Matrix &m) const{
    if (this->rows != m.rows || this->columns != m.columns)
        throw std::logic_error("Addition of matrices with different dimensions");

    Matrix tmp(rows, columns);
    for (size_t i = 0; i < rows ; i++) {
        for (size_t j = 0; j < columns; ++j) {
            tmp.setElement(i, j, data[i][j] - m.data[i][j]);
        }
    }

    return tmp;
}

Matrix Matrix::operator*(const Matrix &right) const {
    Matrix tmp(rows, right.columns);
    if (columns != right.rows) {
        throw std::logic_error("To multiply matrices, the number of columns of the left matrix must be equal to the number of rows of the right matrix ");
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < right.columns; ++j) {
            for (size_t r = 0; r < right.rows; ++r) {
                tmp.setElement(i, j, tmp.getElement(i, j) + data[i][r] * right.data[r][j]);
            }
        }
    }
    return tmp;
}

Matrix Matrix::operator/(const double factor) const {
    Matrix tmp(rows, columns);
    for (size_t i = 0; i < rows ; i++) {
        for (size_t j = 0; j < columns; ++j) {
            tmp.setElement(i, j, data[i][j] / factor);
        }
    }

    return tmp;
}

Matrix::Matrix(size_t _rows, size_t _columns, double values)  : rows(_rows), columns(_columns), data((double **) new double* [_rows]) {
    for (size_t i = 0; i < rows; i++) {
        data[i] = (double *) new double[columns];
        for (size_t j = 0; j < columns; ++j) {
            data[i][j] = values;
        }
    }
}

Matrix Matrix::concatLeft(Matrix &B) const {
    if (B.rows != this->rows){
        throw std::logic_error("Concat of matrices with different number of rows");
    }

    Matrix A(this->rows, columns + B.columns); // Создаём матрицу размера m x (n + B.n)
    for (size_t i = 0; i < rows; ++i) { // Записываем исходную матрицу в A
        for (size_t j = 0; j < B.columns; ++j) {
            A.setElement(i, j, B.getElement(i, j));
        }
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = B.columns; j < B.columns + columns; ++j) {
            A.setElement(i, j, data[i][j]);
        }
    }
    return A;
}

Matrix::Matrix(const vector<vector<double>> &_m) : rows(_m.size()), columns(_m[0].size()), data((double **) new double* [_m.size()]){
    for (size_t i = 0; i < rows; i++) {
        data[i] = (double *) new double[columns];
        for (size_t j = 0; j < columns; ++j) {
            data[i][j] = _m[i][j];
        }
    }

}

Matrix::Matrix() : rows(0), columns(0), data(nullptr) {

}

Matrix::Matrix(const vector<double> &_v) : rows(_v.size()), columns(1), data( (double**) new double*[_v.size()]){
    for (size_t i = 0; i < rows; ++i) {
        data[i] = (double *) new double[columns];
        data[i][0] = _v[i];
    }
}

Matrix::Matrix(const map<std::string, vector<double>> _map) : rows(_map.begin()->second.size()), columns(_map.size()), data((double **) new double* [_map.begin()->second.size()]) {

    for (size_t i = 0; i < rows; ++i) {
        data[i] = (double *) new double[columns];
    }

    auto it = _map.begin();
    for (int i = 0; i < columns ; ++i) {
        if (it->second.size() != rows)
            throw std::range_error("Map has vectors with different size!");

        for (size_t j = 0; j < rows; ++j) {
            data[j][i] = it->second[j];
        }
        ++it;
    }
}

Matrix Matrix::getRow(size_t r) const {
    if (r >= rows)
        throw std::range_error(" ");
    Matrix tmp(1, columns);
    for (int i = 0; i < columns; ++i) {
        tmp.setElement(0, i, data[r][i]);
    }
    return tmp;
}

Matrix Matrix::getRows(size_t from, size_t count) const {
    if (from + count >= rows)
        throw std::range_error(" ");
    Matrix tmp(count, columns);
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < columns; ++j) {
            tmp.setElement(i, j, data[from + i][j]);
        }
    }
    return tmp;
}

Matrix Matrix::operator*(const double right) const {
    Matrix tmp = *this;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            tmp.setElement(i, j, tmp.getElement(i, j)*right);
        }
    }
    return tmp;
}

Matrix &Matrix::normalize() {
    for (size_t j = 0; j < columns; ++j) {
        double mean = 0.0;
        double max_val = 0.0;
//        double sd = 0.0;

        for (size_t i = 0; i < rows; ++i) {
            mean += data[i][j];
            if (data[i][j] > max_val) max_val = data[i][j];
        }
        mean /= (double)rows;
//
//        for  (size_t i = 0; i < rows; ++i) {
//            sd += pow(data[i][j] - mean, 2);
//        }

//        sd = sqrt(sd/((double)rows-1));

        for (size_t i = 0; i < rows; ++i) {
            data[i][j] = (data[i][j] - mean) / max_val;
        }
    }
    return *this;
}


Matrix operator*(double val, const Matrix& M){
    return M * val;
}
