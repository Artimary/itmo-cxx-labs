#pragma once
#include <iostream>

class ShipMatrix {
private:
    int** matrix;      // Указатель на матрицу
    int shipPosition;  // Позиция корабля в виде номера клетки (нумерация от 0)

public:
    int rows;          // Количество строк в матрице
    int cols;          // Количество столбцов в матрице

    // Конструктор по умолчанию (создаём матрицу 2x2)
    ShipMatrix(int rows, int cols);

    // Конструктор копирования
    ShipMatrix(const ShipMatrix& other);

    // Конструктор перемещения
    ShipMatrix(ShipMatrix&& other) noexcept;

    // Оператор присваивания (копирование)
    ShipMatrix& operator=(const ShipMatrix& other);

    // Оператор присваивания (перемещение)
    ShipMatrix& operator=(ShipMatrix&& other) noexcept;

    // Деструктор
    ~ShipMatrix();

    // Функция для установки позиции корабля
    void setShipPosition(int position);

    // Функция для получения позиции корабля
    int getShipPosition();

    // Функция для отображения матрицы
    void display();
};