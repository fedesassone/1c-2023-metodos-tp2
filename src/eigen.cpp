#include <iostream>
#include <Eigen/Dense>

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;

pair<double, VectorXd> powerIteration(MatrixXd, int, double);
pair<VectorXd, MatrixXd> eigen(MatrixXd, int, double);
VectorXd normalize(VectorXd v);
MatrixXd agregarVecAColumna(MatrixXd A, VectorXd v, int col);

pair<double, VectorXd> powerIteration(MatrixXd A, int niter, double eps)
{
    VectorXd b = normalize(VectorXd::Random(A.cols()));
    VectorXd old(A.cols());
    VectorXd new_b(A.cols());
    bool stop = false;

    int i = 0;
    while (i < niter && !stop)
    {
        old = b;
        new_b = normalize(A * b);

        double cosAngle = new_b.dot(old);
        if (((1 - eps) < cosAngle) && cosAngle <= 1)
        {
            stop = true;
        }
        b = new_b;
        i++;
    }
    new_b = A * b;
    double eigenvalue = b.dot(new_b);
    return make_pair(eigenvalue, b);
}

pair<VectorXd, MatrixXd> eigen(MatrixXd A, int niter, double eps)
{
    VectorXd eigenvalues(A.cols());
    MatrixXd AV(A.cols(), A.cols());
    pair<double, VectorXd> temp;

    for (int i = 0; i < A.cols(); i++)
    {
        temp = powerIteration(A, niter, eps);
        eigenvalues[i] = temp.first;
        AV = agregarVecAColumna(AV, temp.second, i);
        A -= temp.first * (temp.second * temp.second.transpose());
    }
    pair<VectorXd, MatrixXd> res = make_pair(eigenvalues, AV);
    return res;
}

VectorXd normalize(VectorXd v)
{
    double sum = 0.00;
    for (int i = 0; i < v.size(); i++)
    {
        sum += double(v[i] * v[i]);
    }
    sum = double(sqrt(sum));

    for (int j = 0; j < v.size(); j++)
    {
        v[j] /= sum;
    }
    return v;
}

MatrixXd agregarVecAColumna(MatrixXd A, VectorXd v, int col)
{
    // Agrega el vector v a la columna i de la matriz A
    for (int i = 0; i < A.cols(); i++)
    {
        A(i, col) = v[i];
    }
    return A;
}