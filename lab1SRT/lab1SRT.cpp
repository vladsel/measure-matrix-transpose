#include <iostream>
#include "time_measure.h"

int **newMatrix(int **matrix, const size_t &n, const size_t &m);
void inputMatrix(int **matrix, const size_t &n, const size_t &m);
void outputMatrix(const int *const *matrix, const size_t &n, const size_t &m);
void deleteMatrix(int **matrix, const size_t &n);
int **measureTransposeMatrix(int **matrix, int **tsMatrix, const size_t &n, const size_t &m);

int main() {
	srand(time(NULL));
	int **matrix = nullptr;
	int **tsMatrix = nullptr;
	size_t n = 0, m = 0;

	n = 1600, m = 800;
	std::cout << "first transpose matrix measure (mcsec): n = " << n << ", m = " << m << "." << std::endl;
	matrix = newMatrix(matrix, n, m);
	tsMatrix = newMatrix(tsMatrix, m, n);
	tsMatrix = measureTransposeMatrix(matrix, tsMatrix, n, m);
	deleteMatrix(matrix, n);
	deleteMatrix(tsMatrix, m);
	matrix = nullptr, tsMatrix = nullptr;

	n = 1400, m = 700;
	std::cout << "second transpose matrix measure (mcsec): n = " << n << ", m = " << m << "." << std::endl;
	matrix = newMatrix(matrix, n, m);
	tsMatrix = newMatrix(tsMatrix, m, n);
	tsMatrix = measureTransposeMatrix(matrix, tsMatrix, n, m);
	deleteMatrix(matrix, n);
	deleteMatrix(tsMatrix, m);
	matrix = nullptr, tsMatrix = nullptr;

	n = 1200, m = 600;
	std::cout << "third transpose matrix measure (mcsec): n = " << n << ", m = " << m << "." << std::endl;
	matrix = newMatrix(matrix, n, m);
	tsMatrix = newMatrix(tsMatrix, m, n);
	tsMatrix = measureTransposeMatrix(matrix, tsMatrix, n, m);
	deleteMatrix(matrix, n);
	deleteMatrix(tsMatrix, m);
	matrix = nullptr, tsMatrix = nullptr;

	n = 1000, m = 500;
	std::cout << "fourth transpose matrix measure (mcsec): n = " << n << ", m = " << m << "." << std::endl;
	matrix = newMatrix(matrix, n, m);
	tsMatrix = newMatrix(tsMatrix, m, n);
	tsMatrix = measureTransposeMatrix(matrix, tsMatrix, n, m);
	deleteMatrix(matrix, n);
	deleteMatrix(tsMatrix, m);
	matrix = nullptr, tsMatrix = nullptr;

	n = 800, m = 400;
	std::cout << "fifth transpose matrix measure (mcsec): n = " << n << ", m = " << m << "." << std::endl;
	matrix = newMatrix(matrix, n, m);
	tsMatrix = newMatrix(tsMatrix, m, n);
	tsMatrix = measureTransposeMatrix(matrix, tsMatrix, n, m);
	deleteMatrix(matrix, n);
	deleteMatrix(tsMatrix, m);
	matrix = nullptr, tsMatrix = nullptr;

	n = 600, m = 300;
	std::cout << "sixth transpose matrix measure (mcsec): n = " << n << ", m = " << m << "." << std::endl;
	matrix = newMatrix(matrix, n, m);
	tsMatrix = newMatrix(tsMatrix, m, n);
	tsMatrix = measureTransposeMatrix(matrix, tsMatrix, n, m);
	deleteMatrix(matrix, n);
	deleteMatrix(tsMatrix, m);
	matrix = nullptr, tsMatrix = nullptr;

	n = 400, m = 200;
	std::cout << "seventh transpose matrix measure (mcsec): n = " << n << ", m = " << m << "." << std::endl;
	matrix = newMatrix(matrix, n, m);
	tsMatrix = newMatrix(tsMatrix, m, n);
	tsMatrix = measureTransposeMatrix(matrix, tsMatrix, n, m);
	deleteMatrix(matrix, n);
	deleteMatrix(tsMatrix, m);
	matrix = nullptr, tsMatrix = nullptr;

	n = 200, m = 100;
	std::cout << "eighth transpose matrix measure (mcsec): n = " << n << ", m = " << m << "." << std::endl;
	matrix = newMatrix(matrix, n, m);
	tsMatrix = newMatrix(tsMatrix, m, n);
	tsMatrix = measureTransposeMatrix(matrix, tsMatrix, n, m);
	deleteMatrix(matrix, n);
	deleteMatrix(tsMatrix, m);
	matrix = nullptr, tsMatrix = nullptr;

	n = 100, m = 50;
	std::cout << "ninth transpose matrix measure (mcsec): n = " << n << ", m = " << m << "." << std::endl;
	matrix = newMatrix(matrix, n, m);
	tsMatrix = newMatrix(tsMatrix, m, n);
	tsMatrix = measureTransposeMatrix(matrix, tsMatrix, n, m);
	deleteMatrix(matrix, n);
	deleteMatrix(tsMatrix, m);
	matrix = nullptr, tsMatrix = nullptr;

	n = 50, m = 25;
	std::cout << "tenth transpose matrix measure (mcsec): n = " << n << ", m = " << m << "." << std::endl;
	matrix = newMatrix(matrix, n, m);
	tsMatrix = newMatrix(tsMatrix, m, n);
	tsMatrix = measureTransposeMatrix(matrix, tsMatrix, n, m);
	deleteMatrix(matrix, n);
	deleteMatrix(tsMatrix, m);
	matrix = nullptr, tsMatrix = nullptr;

	return 0;
}

int **newMatrix(int **matrix, const size_t &n, const size_t &m) {
	if (matrix == nullptr) {
		int **matrix = new int *[n];
		for (size_t i = 0; i < n; i++)
			matrix[i] = new int[m];
		return matrix;
	}
	return nullptr;
}

void inputMatrix(int **matrix, const size_t &n, const size_t &m) {
	if (matrix != nullptr) {
		for (size_t i = 0; i < n; i++)
			for (size_t j = 0; j < m; j++)
				matrix[i][j] = rand() % 500 - 250;
	}
}

void outputMatrix(const int *const *matrix, const size_t &n, const size_t &m) {
	if (matrix != nullptr) {
		for (size_t i = 0; i < n; i++) {
			for (size_t j = 0; j < m; j++)
				std::cout << matrix[i][j] << "\t| ";
			std::cout << "\n";
		}
	}
}

void deleteMatrix(int **matrix, const size_t &n) {
	if (matrix != nullptr) {
		for (size_t i = 0; i < n; i++) {
			if (matrix[i] != nullptr)
				delete[] matrix[i];
		}
		delete[] matrix;
		matrix = nullptr;
	}
}

int **measureTransposeMatrix(int **matrix, int **tsMatrix, const size_t &n, const size_t &m) {
	if (matrix != nullptr && tsMatrix != nullptr) {
		TimeMeasure tm(1, 15, 1000000);

		for (size_t k = 0; k < 15; k++) {
			inputMatrix(matrix, n, m);
			//std::cout << "Matrix [" << k << "]:\n";
			//outputMatrix(matrix, n, m);
			//std::cout << "\n";

			tm.Start();
			for (size_t i = 0; i < n; i++)
				for (size_t j = 0; j < m; j++)
					tsMatrix[j][i] = matrix[i][j];
			tm.Save(0);

			//std::cout << "Transposed Matrix [" << k << "]:\n";
			//outputMatrix(tsMatrix, m, n);
			//std::cout << "\n";
		}
		return tsMatrix;
	}
	return nullptr;
}
