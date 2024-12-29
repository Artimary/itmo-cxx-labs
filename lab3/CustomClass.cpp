#include "CustomClass.h"

// Конструктор по умолчанию
ShipMatrix::ShipMatrix(int rows, int cols) : rows(rows), cols(cols), shipPosition(-1) {
    // std::cout << "Default constructor" << std::endl;
    matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols]();
    }
}

// Дополнительный конструктор по умолчанию
ShipMatrix::ShipMatrix() : rows(0), cols(0), shipPosition(-1), matrix(nullptr) {}

// Конструктор копирования
ShipMatrix::ShipMatrix(const ShipMatrix& other) : rows(other.rows), cols(other.cols), shipPosition(other.shipPosition) {
    // std::cout << "Copy constructor" << std::endl;
    matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
}

// Конструктор перемещения
ShipMatrix::ShipMatrix(ShipMatrix&& other) noexcept: rows(other.rows), cols(other.cols), shipPosition(other.shipPosition), matrix(other.matrix) {
    // std::cout << "Move constructor" << std::endl;
    other.matrix = nullptr;  // Обнуляем указатель у перемещённого объекта
    other.rows = 0;
    other.cols = 0;
}

// Оператор присваивания (копирование)
ShipMatrix& ShipMatrix::operator=(const ShipMatrix& other) {
    // std::cout << "Copy assignment operator" << std::endl;

    // Освобождаем старую память
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    // Копируем данные из другого объекта
    rows = other.rows;
    cols = other.cols;
    shipPosition = other.shipPosition;

    matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
             matrix[i][j] = other.matrix[i][j];
        }
    }

    return *this;
}

// Оператор присваивания (перемещение)
ShipMatrix& ShipMatrix::operator=(ShipMatrix&& other) noexcept{
    // std::cout << "Move assignment operator" << std::endl;
    if (this == &other) {
        return *this;  // Защита от самоприсваивания
    }

    // Освобождаем старую память
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    // Перемещаем данные
    rows = other.rows;
    cols = other.cols;
    shipPosition = other.shipPosition;
    matrix = other.matrix;

    other.matrix = nullptr;  // Обнуляем указатель у перемещённого объекта
    other.rows = 0;
    other.cols = 0;

    return *this;
}

// Деструктор
ShipMatrix::~ShipMatrix() {
    // std::cout << "Destructor" << std::endl;
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Функция для установки позиции корабля
void ShipMatrix::setShipPosition(int position) {
    if (position < 0 || position >= rows * cols) {
        throw std::out_of_range("Invalid ship position.");
    }
    shipPosition = position;
}

// Функция для получения позиции корабля
int ShipMatrix::getShipPosition() {
    return shipPosition;
}

// Функция для отображения матрицы
void ShipMatrix::display() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i * cols + j == shipPosition) {
                std::cout << "S ";  // Отображаем корабль
            } else {
                std::cout << matrix[i][j] << " ";  // Пустая клетка
            }
        }
        std::cout << std::endl;
    }
}