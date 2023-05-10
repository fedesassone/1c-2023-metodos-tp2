#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "eigen.cpp"
#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;

MatrixXd generarMatrizDesdeArchivo(ifstream &, int);
int encuentroDimensionMatrizEntrada(ifstream &);

// argumentos
// 0 - main.-
// 1 - Matriz: archivo con la matriz de entrada.-
// 2 - iter: cantidad de iteraciones.-
// 3 - eps: tolerancia para la convergencia.-

// Ejemplo para correr :
// ./tp ../tests/karateclub_matriz.txt 5 0.00001
int main(int argc, char **argv)
{
	if (argc != 4)
	{
		cout << "Error, Faltan Argumentos." << endl;
		return 1;
	}

	cout << "Corriendo el programa..." << endl;

	ifstream archivoDeEntrada(argv[1]);

	// Preparo archivo de salida 1:
	ofstream archivoAutovalores;
	archivoAutovalores.setf(ios::fixed, ios::floatfield);
	archivoAutovalores.precision(10);
	string nombreCarpetaAutovalores = "./";
	nombreCarpetaAutovalores += argv[1];
	nombreCarpetaAutovalores += "_autovalores.out";

	// Preparo archivo de salida 2:
	ofstream archivoAutovectores;
	archivoAutovectores.setf(ios::fixed, ios::floatfield);
	archivoAutovectores.precision(10);
	string nombreCarpetaAutovectores = "./";
	nombreCarpetaAutovectores += argv[1];
	nombreCarpetaAutovectores += "_autovectores.out";

	int niter = std::stoi(argv[2]);
	double eps = std::stod(argv[3]);

	int dim = encuentroDimensionMatrizEntrada(archivoDeEntrada);

	// Generamos (copiamos) la matriz que dada por archivo.-
	MatrixXd X = generarMatrizDesdeArchivo(archivoDeEntrada, dim);

	// Copio la matriz original para que no sufra cambios (mat_copy = mat).-
	MatrixXd mat_copy = X;

	//  CORREMOS EL METODO DE LA POTENCIA CON DEFLACION.-
	pair<VectorXd, MatrixXd> res = eigen(mat_copy, niter, eps);

	// Abro los archivos de salida.-
	archivoAutovectores.open(nombreCarpetaAutovectores);
	archivoAutovalores.open(nombreCarpetaAutovalores);

	// Cargo el archivo con los autovalores.-
	for (int i = 0; i < dim; i++)
	{
		archivoAutovalores << res.first[i] << endl;
	}

	// Cargo el archivo con los autovectores.-
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			archivoAutovectores << res.second.coeff(i, j) << ' ';
		}
		archivoAutovectores << endl;
	}

	// Cierro los archivos de salida.-
	archivoAutovalores.close();
	archivoAutovectores.close();

	return 0;
}

MatrixXd generarMatrizDesdeArchivo(ifstream &archivoDeEntrada, int n)
{
	double val = 0;
	MatrixXd res(n, n);

	if (archivoDeEntrada.is_open())
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				archivoDeEntrada >> val;

				// Seteo del valor 1 a la posición [i][j]:
				res(i, j) = val;
			}
		}
	}
	return res;
}

int encuentroDimensionMatrizEntrada(ifstream &archivoDeEntrada)
{
	int res = 0;
	std::string line;
	while (std::getline(archivoDeEntrada, line))
	{
		res += 1;
	}
	archivoDeEntrada.clear(); // Clear the eof and fail flags (para volver al inicio)
	archivoDeEntrada.seekg(0);
	return res;
}