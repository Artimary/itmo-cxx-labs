#pragma once
#include <iostream>

class ShipMatrix {
private:
    int** matrix;      // Указатель на матрицу

public:
    int rows;          // Количество строк в матрице
    int cols;          // Количество столбцов в матрице
    int shipPosition;  // Позиция корабля в виде номера клетки (нумерация от 0)

    // Конструктор по умолчанию
    ShipMatrix(int rows, int cols);

    ShipMatrix();

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