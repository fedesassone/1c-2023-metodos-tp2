#include <iostream>
#include <Eigen/Dense>

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;

pair<double, VectorXd> powerIteration(MatrixXd, int, double, int n);
pair<VectorXd, MatrixXd> eigen(MatrixXd, int, double, int);
MatrixXd agregarVecAColumna(MatrixXd A, VectorXd v, int col, int n, int cant);

pair<VectorXd, MatrixXd> eigen(MatrixXd A, int niter, double eps, int cant)
{
    int n = A.cols();

    VectorXd eigenvalues(cant);
    MatrixXd AV(n, cant);
    pair<double, VectorXd> temp;
    

    for (int i = 0; i < cant; i++)
    {
        cout << "autovalor: " << i << endl;

        temp = powerIteration(A, niter, eps, n);

        eigenvalues[i] = temp.first;
        AV = agregarVecAColumna(AV, temp.second, i, n, cant);
        A -= temp.first * (temp.second * temp.second.transpose());

        cout << "valor = " << temp.first << endl;
        cout << "=======================" << endl;

    }
    pair<VectorXd, MatrixXd> res = make_pair(eigenvalues, AV);
    return res;
}


pair<double, VectorXd> powerIteration(MatrixXd A, int niter, double eps, int n)
{
    VectorXd b = VectorXd::Random(n);

    VectorXd old(n);
    bool stop = false;

    int i = 0;
    while (i < niter && !stop)
    {
        old = b;
        b = (A * b).normalized();

        double cosAngle = b.dot(old);
        if ((1 - eps) < cosAngle && cosAngle <= 1)
        {
            stop = true;
            cout << "frene en iteracion: " << i << endl;
        }
        i++;
    }
    if (stop == false){
        cout << "frene en iteracion: " << niter << endl;
    }
    double eigenvalue = b.dot(A * b);
    return make_pair(eigenvalue, b);
}

MatrixXd agregarVecAColumna(MatrixXd A, VectorXd v, int col, int n, int cant)
{
    // Agrega el vector v a la columna i de la matriz A
    for (int i = 0; i < n; i++)
    {
        A(i, col) = v[i];
    }
    return A;
}