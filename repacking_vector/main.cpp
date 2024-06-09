#include <iostream>
#include <vector>
#include <chrono>
#include "MyVector.h";

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    // начальный размер вектора
    const int initial_size = 10;

    // количество итераций для усреднения результатов
    const int iterations = 10000;

    // Цикл по различным множителям
    for (double multiplier = 1.1; multiplier <= 10; multiplier+=0.1) {

        int reallocations = 0;

        // Замер времени
        auto start_time = chrono::high_resolution_clock::now();

        for (int i = 0; i < iterations; ++i) {

            Vector<int> vec(initial_size);
            vec.multiplier_change(multiplier);

            // Заполняем вектор до тех пор, пока он не будет переполнен
            for (int j = 0; j < initial_size * 100; j++) {
                size_t old_capacity = vec.capacity_get();

                vec.push_back(j);

                // Проверяем, произошла ли переаллокация
                if (vec.capacity_get() != old_capacity) {
                    reallocations++;
                }
            }
        }

        // Вычисляем среднее время выполнения
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        double average_time = static_cast<double>(duration) / iterations;

        cout << "Множитель: " << multiplier << endl;
        cout << "Количество переаллокаций: " << reallocations/iterations << endl;
        cout << "Среднее время выполнения (мкс): " << average_time << endl << endl;
    }

    return 0;
}