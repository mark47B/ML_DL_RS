#include "LinearRegression.h"


Matrix LinearRegression::mnk(){
    Matrix X_Transposed = X;
    X_Transposed.transpose();
    Matrix X_quadric = (X_Transposed * X);
    Matrix Inversed = X_quadric.inverse();

    Matrix tmp_2 = X_Transposed * Y;

    _coef = Inversed * tmp_2;

    return this->_coef;
}

LinearRegression::LinearRegression(Matrix &_X, Matrix &_Y) : X(_X), Y(_Y) {
    Matrix leftMatrix(X.getShape().first, 1, 1);

    auto matrixShape = _X.getShape();

    X = Matrix(matrixShape.first, matrixShape.second + 1);


    for (int i = 0; i < matrixShape.first; ++i) {
        for (int j = 0; j < matrixShape.second + 1; ++j) {
            if (j == 0)
                X.setElement(i, j, 1);
            else
                X.setElement(i, j, _X.getElement(i,j-1));
        }
    }
    this->_coef = Matrix(X.getShape().second, 1, 0.01);
}

Matrix LinearRegression::predict(Matrix& _X) const {
    Matrix leftMatrix(_X.getShape().first, 1, 1);
    auto c = leftMatrix.concatRight(_X);
    return c*_coef;
}

Matrix LinearRegression::predict_without_bias(Matrix& _X) const {
    return _X*_coef;
}

double LinearRegression::predict(vector<double> x) const {
    auto  matrixSize =  this->_coef.getShape();

    if (x.size() != matrixSize.second)
        throw std::logic_error("Different size of x and vector coefficients");
    double y_predicted = 0;
    for(int i = 0; i <  matrixSize.second; ++i){
        y_predicted += x[i] * this->_coef.getElement(0, i);
    }
    return y_predicted;
}

double LinearRegression::predict(const double x[], size_t size_x) const {
    auto  matrixSize =  this->_coef.getShape();
    if (size_x != matrixSize.second)
        throw std::logic_error("Different size of x and vector coefficients");
    double y_predicted = 0;
    for(size_t i = 0; i <  matrixSize.second; ++i){
        y_predicted += x[i] * this->_coef.getElement(0, i);
    }
    return y_predicted;
}

void LinearRegression::fit(LinearRegression::TrainingMethods method){
    switch (method) {
        case TrainingMethods::GradientDecent:
            this->sgd();
            break;
        case TrainingMethods::LeastSquares:
            this->mnk();
            break;
        default:
            this->mnk();
    }
}

void LinearRegression::sgd(double learningRate, int epoch, size_t batch_size) {

    X.normalize();

    for (size_t e = 0; e < epoch; ++e) {
        size_t num_rows = X.getShape().first;

        for (size_t i = 0; i < num_rows; i += batch_size) {
            size_t current_batch_size = (i + batch_size > num_rows) ? (num_rows - i - 1) : batch_size;

            Matrix rows = X.getRows(i, current_batch_size);

            Matrix y_pred = rows * this->_coef;

            Matrix error = y_pred - Y.getRows(i, current_batch_size);

            rows.transpose();

            auto grad = (2.0 / (double)current_batch_size) * (rows * error);
            _coef = this->_coef - (learningRate * grad);
            _coef.print();
        }
    }
}

Matrix LinearRegression::getCoefficients() {
    return this->_coef;
}

LinearRegression::LinearRegression(Matrix &_X, Matrix &_Y, Matrix &coefficients) : X(_X), Y(_Y), _coef(coefficients) {
    Matrix leftMatrix(X.getShape().first, 1, 1);

    auto matrixShape = _X.getShape();

    X = Matrix(matrixShape.first, matrixShape.second + 1);


    for (int i = 0; i < matrixShape.first; ++i) {
        for (int j = 0; j < matrixShape.second + 1; ++j) {
            if (j == 0)
                X.setElement(i, j, 1);
            else
                X.setElement(i, j, _X.getElement(i,j-1));
        }
    }
}

// ----------- RegressionMetrics ------------------
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
