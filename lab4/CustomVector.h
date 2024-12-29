#pragma once
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <utility>
#include <vector>

// Класс для разреженного вектора
class SparseVector {
private:
    std::unordered_map<int, double> elements;
    int size;

public:

    SparseVector (const std::vector<double>& v) {
        for (int i = 0; i < v.size(); ++i) {
            if (v[i] != 0) {
                elements.emplace(i, v[i]);
            }
        }
        size = v.size();
        for (int i = 0; i < size; ++i) {
            if (elements[i] == 0) elements.erase(i);
        }
    }

    SparseVector (int size_) : size(size_) {}

    int getVectorSize() const { return size; }

    auto IterBegin() { return elements.begin(); }
    auto IterEnd() { return elements.begin(); }
    auto IterCbegin() const { return elements.cbegin(); }
    auto IterCend() const { return elements.cend(); }
    
    // Оператор доступа
    double operator[](int index) const {
        auto it = elements.find(index);
        return (it != elements.end()) ? it->second : 0.0;
    }

    // Метод для изменения значения
    void setValue(int index, double value) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        if (value != 0) {
            elements[index] = value;
        } else {
            elements.erase(index);
        }
    }

    double getValue(int index) const {
        auto it = elements.find(index);
        return it != elements.end() ? it->second : 0.0;
    }

    // Транспонирование 
    SparseVector transpose() const {
        return *this;
    }

    // Операции с числами (скаляры)
    SparseVector operator+(double scalar) const {
        SparseVector result(size);
        for (const auto& pair : elements) {
            int index = pair.first;
            int value = pair.second;
            result.elements[index] = value + scalar;
        }
        return result;
    }

    // Перегрузка оператора сложения для двух векторов
    SparseVector operator+(const SparseVector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must be of the same size for addition.");
        }
        SparseVector result(size);

        // Сначала копируем текущий вектор
        for (const auto& elem : elements) {
            result.setValue(elem.first, elem.second);
        }

        // Затем добавляем элементы из другого вектора
        for (const auto& elem : other.elements) {
            double newValue = result.getValue(elem.first) + elem.second;
            result.setValue(elem.first, newValue);
        }

        return result;
    }

    SparseVector operator-(double scalar) const {
        SparseVector result(size);
        for (const auto& pair : elements) {
            int index = pair.first;
            int value = pair.second;
            result.elements[index] = value - scalar;
        }
        return result;
    }

    SparseVector operator*(double scalar) const {
        SparseVector result(size);
        for (const auto& pair : elements) {
            int index = pair.first;
            int value = pair.second;
            result.elements[index] = value * scalar;
        }
        return result;
    }

    // Покоординатное умножение двух векторов
    SparseVector operator*(const SparseVector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must be of the same size for element-wise multiplication.");
        }

        SparseVector result(size);

        // Перебираем элементы текущего вектора и умножаем только те, которые присутствуют в обоих
        for (const auto& elem : elements) {
            auto it = other.elements.find(elem.first);
            if (it != other.elements.end()) {
                result.setValue(elem.first, elem.second * it->second);
            }
        }

        return result;
    }

    // Скалярное произведение векторов
    double dot(const SparseVector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must be of the same size");
        }

        double result = 0.0;
        for (const auto& pair : elements) {
            int index = pair.first;
            double value = pair.second;
            
            auto it = other.elements.find(index);
            if (it != other.elements.end()) {
                result += value * it->second;
            }
        }
        return result;
    }

    SparseVector operator/(double scalar) const {
        if (scalar == 0) throw std::runtime_error("Division by zero");
        SparseVector result(size);
        for (const auto& pair : elements) {
            int index = pair.first;
            int value = pair.second;
            result.elements[index] = value / scalar;
        }
        return result;
    }

    // Вывод вектора
    void print() const {
        std::cout << "SparseVector: ";
        for (int i = 0; i < size; ++i) {
            if (this->operator[](i) != 0)
            std::cout << this->operator[](i) << " ";
        }
        std::cout << "\n";
    }
};

