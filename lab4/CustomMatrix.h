#pragma once
#include <stdexcept>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include <cmath>

namespace std {
    // Специализация хеш-функции для std::pair<int, int>
    template <>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int>& p) const {
            auto h1 = std::hash<int>{}(p.first);
            auto h2 = std::hash<int>{}(p.second);
            return h1 ^ (h2 << 1); // XOR с сдвигом для комбинирования хешей
        }
    };
}

// Класс для разреженной матрицы
class SparseMatrix {
private:
    std::unordered_map<std::pair<int, int>, double> matrix_elem;
    int numRows, numCols;
    int size;

public:
    
    SparseMatrix (const std::vector<std::vector<double>>& entry_matrix) {
        for (int i = 0; i < entry_matrix.size(); ++i) {
            for (int j = 0; j < entry_matrix[i].size(); ++j) {
                if (entry_matrix[i][j] != 0) {
                    matrix_elem.emplace(std::make_pair(i, j), entry_matrix[i][j]);
                }
            }
        }
        numRows = entry_matrix.size();
        numCols = entry_matrix[0].size();
        size = numRows + numCols;
    }

    SparseMatrix(int row, int col) : numRows(row), numCols(col) {}

    int getNumRows() const { return numRows; }
    int getNumCols() const { return numCols; }

    auto IterBegin() { return matrix_elem.begin(); }
    auto IterEnd() { return matrix_elem.begin(); }
    auto IterCbegin() const { return matrix_elem.cbegin(); }
    auto IterCend() const { return matrix_elem.cend(); }
    
    // Получение элемента
    double getValue(int row, int col) const {
        auto it = matrix_elem.find(std::make_pair(row, col));
        return it != matrix_elem.end() ? it->second : 0.0;
    }

    // Установка элемента
    void setValue(int row, int col, double value) {
        if (value != 0) {
            matrix_elem[std::make_pair(row, col)] = value;
        } 
    }

    int getMatrixSize() const { return size; }

    // Транспонирование
    SparseMatrix transpose() const {
        SparseMatrix result(numCols, numRows);
        for (const auto& pair : matrix_elem) {
            std::pair<int, int> pos = pair.first;
            double value = pair.second;

            result.setValue(pos.second, pos.first, value);
        }
        return result;
    }

     // Операции с числами (скаляры)
    SparseMatrix operator+(double scalar) const {
        SparseMatrix result(numRows, numCols);
        for (const auto& pair : matrix_elem) {
            std::pair<int, int> key = pair.first;
            double value = pair.second;
            result.matrix_elem[key] = value + scalar;
        }
        return result;
    }

    // Перегрузка операции сложения для сложения двух матриц
    SparseMatrix operator+(const SparseMatrix& other) const {
        if (this->numRows != other.numRows || this->numCols != other.numCols) {
            throw std::invalid_argument("Matrices must have the same dimensions for addition.");
        }

        SparseMatrix result(this->numRows, this->numCols);  // Результат сложения

        // Добавляем элементы из текущей матрицы
        for (const auto& pair : this->matrix_elem) {
            result.matrix_elem[pair.first] = pair.second;
        }

        // Добавляем элементы из другой матрицы
        for (const auto& pair : other.matrix_elem) {
            result.matrix_elem[pair.first] += pair.second;  // Сложение поэлементно
        }

        return result;
    }

    SparseMatrix operator-(double scalar) const {
        SparseMatrix result(numRows, numCols);
        for (const auto& pair : matrix_elem) {
            std::pair<int, int> key = pair.first;
            double value = pair.second;
            result.matrix_elem[key] = value - scalar;
        }
        return result;
    }

    SparseMatrix operator*(double scalar) const {
        SparseMatrix result(numRows, numCols);
        for (const auto& pair : matrix_elem) {
            std::pair<int, int> key = pair.first;
            double value = pair.second;
            result.matrix_elem[key] = value * scalar;
        }
        return result;
    }

    SparseMatrix operator/(double scalar) const {
        if (scalar == 0) throw std::runtime_error("Division by zero");
        SparseMatrix result(numRows, numCols);
        for (const auto& pair : matrix_elem) {
            std::pair<int, int> key = pair.first;
            double value = pair.second;
            result.matrix_elem[key] = value / scalar;
        }
        return result;
    }

    // Готовая функция для обращения матрицы (метод Гаусса)
    SparseMatrix inverse() const {
        if (numRows != numCols) {
            throw std::invalid_argument("Matrix must be square to be inverted.");
        }

        // Инициализация единичной матрицы для формирования обратной
        SparseMatrix inverse(numRows, numCols);

        // Создаем копию текущей матрицы
        SparseMatrix matrix_copy = *this;

        // Инициализируем единичную матрицу
        for (int i = 0; i < numRows; ++i) {
            inverse.setValue(i, i, 1.0);
        }

        // Прямой ход метода Гаусса
        for (int i = 0; i < numRows; ++i) {
            // Поиск максимального элемента в текущем столбце для стабильности
            auto pivot_it = matrix_copy.matrix_elem.find({i, i});
            if (pivot_it == matrix_copy.matrix_elem.end() || pivot_it->second == 0) {
                bool row_swapped = false;
                for (int j = i + 1; j < numRows; ++j) {
                    auto swap_it = matrix_copy.matrix_elem.find({j, i});
                    if (swap_it != matrix_copy.matrix_elem.end() && swap_it->second != 0) {
                        // Меняем строки i и j
                        for (int k = 0; k < numCols; ++k) {
                            std::swap(matrix_copy.matrix_elem[{i, k}], matrix_copy.matrix_elem[{j, k}]);
                            std::swap(inverse.matrix_elem[{i, k}], inverse.matrix_elem[{j, k}]);
                        }
                        row_swapped = true;
                        break;
                    }
                }
                if (!row_swapped) {
                    throw std::runtime_error("Matrix is singular and cannot be inverted.");
                }
            }

            // Нормализация строки (делим на элемент диагонали)
            double pivot = matrix_copy.matrix_elem.at({i, i});
            for (int col = 0; col < numCols; ++col) {
                if (matrix_copy.matrix_elem.find({i, col}) != matrix_copy.matrix_elem.end()) {
                    matrix_copy.matrix_elem[{i, col}] /= pivot;
                }
                if (inverse.matrix_elem.find({i, col}) != inverse.matrix_elem.end()) {
                    inverse.matrix_elem[{i, col}] /= pivot;
                }
            }

            // Обнуление остальных элементов в текущем столбце
            for (int j = 0; j < numRows; ++j) {
                if (j != i) {
                    double factor = matrix_copy.getValue(j, i);
                    if (factor != 0) {
                        for (int col = 0; col < numCols; ++col) {
                            double val1 = matrix_copy.getValue(j, col);
                            double val2 = matrix_copy.getValue(i, col) * factor;
                            matrix_copy.setValue(j, col, val1 - val2);

                            double inv_val1 = inverse.getValue(j, col);
                            double inv_val2 = inverse.getValue(i, col) * factor;
                            inverse.setValue(j, col, inv_val1 - inv_val2);
                        }
                    }
                }
            }
        }

    return inverse;
    }


    // Поэлементное возведение в степень
    SparseMatrix power(double exponent) const {
        SparseMatrix result(numRows, numCols);
        for (const auto& pair : matrix_elem) {
            std::pair<int, int> key = pair.first;
            double value = pair.second;
            result.matrix_elem[key] = std::pow(value, exponent);
        }
        return result;
    }

    // Вывод для проверки
    void print() const {
        for (const auto& pair : matrix_elem) {
            std::pair<int, int> key = pair.first;
            double value = pair.second;
            std::cout << "Row: " << key.first << " Col: " << key.second << " Value: " << value << std::endl;
        }
    }

    // Умножение матриц
    SparseMatrix multiply(const SparseMatrix& other) const {
        if (numCols != other.numRows) {
            throw std::invalid_argument("The number of columns of the first matrix must match the number of rows of the second one.");
        }

        SparseMatrix result(numRows, other.numCols);
        for (const auto& pair : matrix_elem) {
            std::pair<int, int> posA = pair.first;
            double valueA = pair.second;
            
            int rowA = posA.first;
            int colA = posA.second;
            for (int colB = 0; colB < other.numCols; ++colB) {
                double valueB = other.getValue(colA, colB);
                if (valueB != 0) {
                    double newValue = result.getValue(rowA, colB) + valueA * valueB;
                    result.setValue(rowA, colB, newValue);
                }
            }
        }

        return result;
    }

    // Умножение матрицы на вектор
    std::vector<double> multiply(const std::vector<double>& vec) const {
        if (numCols != vec.size()) {
            throw std::invalid_argument("Vector size must match the number of matrix columns.");
        }

        std::vector<double> result(numRows, 0.0);

        for (const auto& elem : matrix_elem) {
            int row = elem.first.first;
            int col = elem.first.second;
            double value = elem.second;

            result[row] += value * vec[col];
        }

        return result;
    }
};
