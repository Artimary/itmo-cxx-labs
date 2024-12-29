#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <list>
#include "CustomClass.cpp"
#include "CustomClass.h"


// Функция для обработки вектора, содержащего экземпляры ShipMatrix
void processMatrixVector(std::vector<ShipMatrix>& matrices) {
    std::cout << "Processing vector of ShipMatrix instances..." << std::endl;
    for (auto& mat : matrices) {
        mat.setShipPosition(rand() % (mat.rows * mat.cols)); // Случайная позиция корабля
        /*mat.display();
        std::cout << std::endl; */ // раскомментировать для отображения всех матриц вектора v1
    }
}

bool greater_compare(const ShipMatrix& left, const ShipMatrix& right) {
        return (left.shipPosition > right.shipPosition);  // Сравнение по shipPosition
}

bool less_compare(const ShipMatrix& left, const ShipMatrix& right) {
        return (left.shipPosition < right.shipPosition);  // Сравнение по shipPosition
}

// Функция для вычисления среднего значения shipPosition
int calculateAverage(const std::list<ShipMatrix>& lst) {
    int average = std::accumulate(lst.begin(), lst.end(), 0.0,
        [](double sum, const ShipMatrix& obj) {
            return sum + obj.shipPosition;
        }) / lst.size();

    auto closest = std::min_element(lst.begin(), lst.end(),
        [average](const ShipMatrix& a, const ShipMatrix& b) {
            return std::abs(a.shipPosition - average) < std::abs(b.shipPosition - average);
        });
    return closest->shipPosition;
}

void display_ships (std::list<ShipMatrix>& smth) {
    for (auto& mat : smth) {
        std::cout << mat.getShipPosition() << " ";
    }
    std::cout << std::endl;
}

void display_ships (std::vector<ShipMatrix>& smth) {
    for (auto& mat : smth) {
        std::cout << mat.getShipPosition() << " ";
    }
    std::cout << std::endl;
}

int main() {
    // ShipMatrix mat1(3, 3);
    srand(time(NULL));
    int size = rand() % 501 + 500;
    int x = 0;
    int y = 0;
    std::vector<ShipMatrix> v1;
    for (int i = 0; i < size; ++i) {
        x = rand() % 8 + 1;
        y = rand() % 8 + 1;
        v1.emplace_back(x, y);  // Добавляем матрицу
    }
    std::cout << "v1 contains " << v1.size() << " elements." << std::endl;

    processMatrixVector(v1); // 1. Задаем случайные позиции корабля в каждом экземпляре класса

    std::vector<ShipMatrix> v2(v1.end() - 200, v1.end());  // 2. Копирование последних 200 элементов
    std::cout << "v2 contains " << v2.size() << " elements." << std::endl;

    int begin_2, end_2;
    std::cout << "v2_1 starts: ";
    std::cin >> begin_2;
    std::cout << "v2_1 ends: ";
    std::cin >> end_2;
    std::vector<ShipMatrix> v2_1(v1.begin() + begin_2 - 1, v1.begin() + end_2); // 2.1. Копирование от b до e элементов
    std::cout << "v2_1 contains " << v2_1.size() << " elements." << std::endl;

    int n = rand() % 31 + 20;  // n от 20 до 50

    std::sort(v1.begin(), v1.end(), greater_compare);  // Сортируем по убыванию

    std::list<ShipMatrix> list1(v1.begin(), v1.begin() + n);  // 3. Берём первые n элементов
    std::cout << "list1 contains " << list1.size() << " elements." << std::endl;
    display_ships(list1);

    std::sort(v2.begin(), v2.end(), less_compare);  // Сортируем по возрастанию
    std::list<ShipMatrix> list2(v2.end() - n, v2.end());  // 4. Берём последние n элементов
    std::cout << "list2 contains " << list2.size() << " elements." << std::endl;
    display_ships(list2);

    v1.erase(v1.begin(), v1.begin() + n);  // 5. Удаляем первые n элементов из v1
    v2.erase(v2.end() - n, v2.end());  // Удаляем последние n элементов из v2
    std::cout << "Now v1 contains " << v1.size() << " elements." << std::endl;
    std::cout << "Now v2 contains " << v2.size() << " elements." << std::endl;
    // display_ships(v2);

    // 6. Вычисляем среднее значение shipPosition
    int average = calculateAverage(list1);
    std::cout << "Average shipPosition: " << average << std::endl;

    // Перегруппируем элементы списка относительно найденного значения
    list1.sort([average](const ShipMatrix& a, const ShipMatrix& b) {
        return (a.shipPosition > average && b.shipPosition <= average) ||
               (a.shipPosition > b.shipPosition && !(b.shipPosition > average));
    });

    // Вывод перегруппированного списка
    std::cout << "Regrouped list1:" << std::endl;
    display_ships(list1);

    // 7. Удаляем элементы shipPosition
    int average_list2 = calculateAverage(list2);
    std::cout << "Average shipPosition: " << average_list2 << std::endl;
    list2.remove_if([average_list2](const ShipMatrix& obj) {
        return (obj.shipPosition < average_list2); // Критерий: удаляем элементы меньше среднего shipPosition
    });
    std::cout << "New list2:" << std::endl;
    display_ships(list2);

    // 8. Создаём вектор для пересечения
    std::vector<ShipMatrix> v3;
    std::sort(v1.begin(), v1.end(), less_compare);
    std::sort(v2.begin(), v2.end(), less_compare);

    // Вычисляем пересечение
    std::set_intersection(
        v1.begin(), v1.end(),
        v2.begin(), v2.end(),
        std::back_inserter(v3),
        [](const ShipMatrix& a, const ShipMatrix& b) {
            return a.shipPosition < b.shipPosition;
        }
    );

    // Уменьшаем размер вектора до количества пересечений

    // display_ships(v3);
    std::cout << "v3 size: " << v3.size() << std::endl;

    // 9. Cформируем список list3, в котором хранятся пары list1, list2.
    size_t min = std::min(list1.size(), list2.size());
    (list1.size() > min) ? list1.resize(min) : list2.resize(min);
    std::list<std::pair<ShipMatrix, ShipMatrix>> list3;
    std::transform(
      list1.begin(), list1.end(),
      list2.begin(),
      std::back_inserter(list3),
      [](const ShipMatrix& a, const ShipMatrix& b) {
            return std::make_pair(a, b); 
    });

    std::cout << "list3 size: " << list3.size() << std::endl;
    // Расскоментировать для вывода list3
    // for (auto elem : list3) {
    //     std::cout << elem.first.shipPosition << " ";
    // }
    // std::cout << std::endl;

    // for (auto elem : list3) {
    //     std::cout << elem.second.shipPosition << " ";
    // }
    // std::cout << std::endl;

    // 10. Создаем вектор пар элементов из двух векторов
    std::vector<std::pair<ShipMatrix, ShipMatrix>> v4;
    std::transform(v1.begin(), v1.begin() + std::min(v1.size(), v2.size()), 
                   v2.begin(),
                   std::back_inserter(v4),
                   [](const ShipMatrix& a, const ShipMatrix& b) { return std::make_pair(a, b); 
    });

    std::cout << "v4 size: " << v4.size() << std::endl;
    // Расскоментировать для вывода v4
    // for (auto elem : v4) {
    //     std::cout << elem.first.shipPosition << " ";
    // }
    // std::cout << std::endl;

    // for (auto elem : v4) {
    //     std::cout << elem.second.shipPosition << " ";
    // }
    // std::cout << std::endl;

    return 0;
}