#include <iostream>
#include <vector>
#include <chrono>
#include "CustomVector.h"
#include "CustomMatrix.h"

std::vector<double> stlVectorAddition(const std::vector<double>& v1, const std::vector<double>& v2) {
	std::vector<double> result(v1.size());
	for (int i = 0; i < v1.size(); ++i) {
		result[i] = v1[i] + v2[i];
	}
	return result;
}

double stlVectorMultiplication(const std::vector<double>& v1, const std::vector<double>& v2) {
	double result = 0.0;
	for (int i = 0; i < v1.size(); ++i) {
		result += v1[i] * v2[i];
	}
	return result;
}

std::vector<double> stlVectorMultiplyByValue(const std::vector<double>& v, double value) {
	std::vector<double> result(v.size());
	for (int i = 0; i < v.size(); ++i) {
		result[i] = v[i] * value;
	}
	return result;
}

void testing_vector() {
    // Создаем два разреженных вектора
    SparseVector vec1({1.0, 0.0, 2.0, 0.0, 0.0, 3.0});
    SparseVector vec2({0.0, 4.0, 2.0, 0.0, 1.0, 0.0});

    vec1.print();
    vec2.print();
    // Сложение векторов
    SparseVector sum = vec1 + vec2;
    std::cout << "Sum of vectors:\n";
    sum.print();

    // Скалярное произведение
    double dotProduct = vec1.dot(vec2);
    std::cout << "Dot product of vectors: " << dotProduct << "\n";

    // Транспонирование (идентичная операция для вектора)
    SparseVector transposed = vec1.transpose();
    std::cout << "Transposed vector:\n";
    transposed.print();
}

void testing_matrix() {
    // Создание разреженной матрицы
    std::vector<std::vector<double>> data = {
        {0, 0, 3},
        {0, 5, 0},
        {7, 0, 0}
    };

    SparseMatrix mat(data);

    // Вывод оригинальной матрицы
    std::cout << "Original Matrix:" << std::endl;
    for (int i = 0; i < mat.getNumRows(); ++i) {
        for (int j = 0; j < mat.getNumCols(); ++j) {
            std::cout << mat.getValue(i, j) << " ";
        }
        std::cout << std::endl;
    }

    // Транспонирование
    SparseMatrix transposed_mat = mat.transpose();
    std::cout << "\nTransposed Matrix:" << std::endl;
    for (int i = 0; i < transposed_mat.getNumRows(); ++i) {
        for (int j = 0; j < transposed_mat.getNumCols(); ++j) {
            std::cout << transposed_mat.getValue(i, j) << " ";
        }
        std::cout << std::endl;
    }

    // Умножение матриц
    SparseMatrix mat2(data); // Вторую матрицу создаем аналогичной
    SparseMatrix product = mat.multiply(mat2);
    // std::cout << "\nProduct of Matrices:" << std::endl;
    for (int i = 0; i < product.getNumRows(); ++i) {
        for (int j = 0; j < product.getNumCols(); ++j) {
            std::cout << product.getValue(i, j) << " ";
        }
        std::cout << std::endl;
    }

    // Возведение в степень
    SparseMatrix powered = mat.power(2);
    std::cout << "\nMatrix Raised to Power 2:" << std::endl;
    for (int i = 0; i < powered.getNumRows(); ++i) {
        for (int j = 0; j < powered.getNumCols(); ++j) {
            std::cout << powered.getValue(i, j) << " ";
        }
        std::cout << std::endl;
    }

    // Обращение матрицы
    SparseMatrix inverted = mat.inverse();
    std::cout << "\nInverse Matrix:" << std::endl;
    for (int i = 0; i < inverted.getNumRows(); ++i) {
        for (int j = 0; j < inverted.getNumCols(); ++j) {
            std::cout << inverted.getValue(i, j) << " ";
        }
        std::cout << std::endl;
    }

    std::vector<double> vector = {2.0, 1.0, 3.0};
    // Умножение матрицы на вектор
    std::vector<double> result = mat.multiply(vector);
    std::cout << "\nMatrix multiply by vector: " << std::endl;
    // Вывод результата
    for (double val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

void timing_vector() {
    constexpr int VECTOR_SIZE = 10000000;
	std::vector<double> v1(VECTOR_SIZE, 0.0);
	std::vector<double> v2(VECTOR_SIZE, 0.0);

	for (int i = 0; i < VECTOR_SIZE; i += 500) {
		v1[i] = 1.0;
		v2[i] = 1.0;
	}

	SparseVector vect1(v1);
	SparseVector vect2(v2);

	// Custom
	auto customVectorStart = std::chrono::high_resolution_clock::now();

	SparseVector customResult = vect1 + vect2;			// vectors add
	// SparseVector customResult = vect1 * vect2;			// vectors multiply
	// SparseVector customResult = vect1 * 2;					// vector value multiply

	auto customVectorEnd = std::chrono::high_resolution_clock::now();

	// std::cout << "Custom: ";
    // customResult.print();

	// STL
	auto stlVectorStart = std::chrono::high_resolution_clock::now();

	std::vector<double> stlResult = stlVectorAddition(v1, v2);		           // vectors add
	// double stlResult = stlVectorMultiplication(v1, v2);				           // vectors multiply
	// std::vector<double> stlResult = stlVectorMultiplyByValue(v1, 2);	    // vector value multiply

	auto stlVectorEnd = std::chrono::high_resolution_clock::now();

	// std::cout << "Stl: ";
	// for (auto val : stlResult) {
	// 	std::cout << val << " ";
	// }
	// std::cout << "\n";

    auto duration_custom = std::chrono::duration_cast<std::chrono::milliseconds>(customVectorEnd - customVectorStart);
    auto duration_stl = std::chrono::duration_cast<std::chrono::milliseconds>(stlVectorEnd - stlVectorStart);
	std::cout << "Custom time - " << duration_custom.count() << " ms." <<  "\nStl time - " << duration_stl.count() << " ms.\n";
}

std::vector<std::vector<double>> stlMatrixAddition(const std::vector<std::vector<double>>& m1, const std::vector<std::vector<double>>& m2) {
	std::vector<std::vector<double>> result(m1.size(), std::vector<double>(m1[0].size()));
	for (int i = 0; i < m1.size(); ++i) {
		for (int j = 0; j < m1[0].size(); ++j) {
			result[i][j] = m1[i][j] + m2[i][j];
		}
	}
	return result;
}

void timing_matrix() {
	constexpr int MATRIX_SIZE = 1500, DELTA_STEP = 10;
	std::vector<std::vector<double>> m1(MATRIX_SIZE, std::vector<double>(MATRIX_SIZE));
	std::vector<std::vector<double>> m2(MATRIX_SIZE, std::vector<double>(MATRIX_SIZE));

	for (int i = 0; i < MATRIX_SIZE; i += DELTA_STEP) {
		for (int j = 0; j < MATRIX_SIZE; j += DELTA_STEP) {
			m1[i][j] = 3.20;
			m2[i][j] = 32.0;
		}
	}

	SparseMatrix matr1(m1);
	SparseMatrix matr2(m2);

	// Custom
	auto customMatrixStart = std::chrono::high_resolution_clock::now();

	SparseMatrix customResult = matr1 + matr2;			// matrices add

	auto customMatrixEnd = std::chrono::high_resolution_clock::now();

	// std::cout << "Custom: ";
    // customResult.print();

	// STL
	auto stlMatrixStart = std::chrono::high_resolution_clock::now();

	std::vector<std::vector<double>> stlResult = stlMatrixAddition(m1, m2);		// matrices add

	auto stlMatrixEnd = std::chrono::high_resolution_clock::now();

	auto duration_custom = std::chrono::duration_cast<std::chrono::milliseconds>(customMatrixEnd - customMatrixStart);
    auto duration_stl = std::chrono::duration_cast<std::chrono::milliseconds>(stlMatrixEnd - stlMatrixStart);
	std::cout << "Custom time - " << duration_custom.count() << " ms." <<  "\nStl time - " << duration_stl.count() << " ms.\n";
}

int main() {
    
    testing_vector();
    testing_matrix();

    timing_vector();
    timing_matrix();

    return 0;
}