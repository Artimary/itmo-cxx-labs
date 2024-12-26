#include <iostream>
// #include <stdexcept>
#include <vector>
#include <list>
#include "CustomClass.cpp"
#include "CustomClass.h"


// Функция для обработки вектора, содержащего экземпляры ShipMatrix
void processMatrixVector(std::vector<ShipMatrix>& matrices) {
    std::cout << "Processing vector of ShipMatrix instances..." << std::endl;
    for (auto& mat : matrices) {
        mat.setShipPosition(rand() % (mat.rows * mat.cols)); // Случайная позиция корабля
        mat.display();
        std::cout << std::endl;
    }
}

// Функция с передачей объекта по ссылке и возврата его из функции
ShipMatrix& modifyMatrix(ShipMatrix& mat) {
    mat.setShipPosition(rand() % (mat.rows * mat.cols)); // Устанавливаем случайную позицию
    std::cout << "Matrix modified inside function:" << std::endl;
    mat.display();
    return mat;  // Возвращаем ссылку на изменённый объект
}

// Функция работы с элементами матрицы
void processMatrixReference(ShipMatrix& mat) {
    std::cout << "Processing matrix passed by reference:" << std::endl;
    mat.setShipPosition(rand() % (mat.rows * mat.cols));  // Устанавливаем случайную позицию
    mat.display();
}

int main() {
    ShipMatrix mat1(3, 3);
    mat1.setShipPosition(2);
    mat1.display();

    // Копирование матрицы
    ShipMatrix mat2 = mat1;
    mat2.setShipPosition(5);
    mat2.display();

    // Перемещение матрицы
    ShipMatrix mat3 = std::move(mat1);
    mat3.setShipPosition(7);
    mat3.display();

    // Присваивание копированием
    ShipMatrix mat4(3, 3);
    mat4 = mat2;
    // mat4.setShipPosition(1);
    mat4.display();

    // Присваивание перемещением
    ShipMatrix mat5(3, 3);
    mat5 = std::move(mat3);
    // mat5.setShipPosition(8);
    mat5.display();

    // Статическое создание объекта ShipMatrix
    std::cout << "\nCreating static ShipMatrix:" << std::endl;
    ShipMatrix staticMatrix(4, 4);
    staticMatrix.setShipPosition(5);  // Устанавливаем позицию корабля
    // staticMatrix.display();

     // Передача объекта по ссылке и возврат из функции
    std::cout << "\nBefore modification:" << std::endl;
    staticMatrix.display();
    modifyMatrix(staticMatrix);
    std::cout << "\nAfter modification:" << std::endl;
    staticMatrix.display();

    // Динамическое создание объекта ShipMatrix
    std::cout << "\nCreating dynamic ShipMatrix:" << std::endl;
    ShipMatrix* dynamicMatrix = new ShipMatrix(3, 3);
    dynamicMatrix->setShipPosition(3);
    dynamicMatrix->display();
    modifyMatrix(*dynamicMatrix);
    std::cout << "\nAfter modification:" << std::endl;
    dynamicMatrix->display();
    delete dynamicMatrix;  // Освобождаем память

    // Статическое создание вектора ShipMatrix
    std::cout << "\nCreating vector of ShipMatrix instances:" << std::endl;
    std::vector<ShipMatrix> matrixVector;
    for (int i = 0; i < 5; ++i) {
        matrixVector.emplace_back(3, 3);  // Добавляем матрицу 3x3
    }

    // Обработка вектора с помощью функции
    processMatrixVector(matrixVector);

    // for (auto mat : matrixVector) {
    //     mat.display();
    // }

    // Создание списка объектов ShipMatrix
    std::cout << "\nCreating list of ShipMatrix instances:" << std::endl;
    std::list<ShipMatrix> matrixList;
    for (int i = 0; i < 6; ++i) {
        matrixList.push_back(ShipMatrix(2, 2));  // Добавляем матрицу 2x2
    }
    

    // Обработка списка
    for (auto& mat : matrixList) {
        processMatrixReference(mat);
    }
    // for (auto mat : matrixList) {
    //     mat.display();
    // }

    return 0;
}
