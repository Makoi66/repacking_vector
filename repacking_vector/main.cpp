#include <iostream>
#include <vector>
#include <chrono>
#include "MyVector.h";

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    // ��������� ������ �������
    const int initial_size = 10;

    // ���������� �������� ��� ���������� �����������
    const int iterations = 10000;

    // ���� �� ��������� ����������
    for (double multiplier = 1.1; multiplier <= 10; multiplier+=0.1) {

        int reallocations = 0;

        // ����� �������
        auto start_time = chrono::high_resolution_clock::now();

        for (int i = 0; i < iterations; ++i) {

            Vector<int> vec(initial_size);
            vec.multiplier_change(multiplier);

            // ��������� ������ �� ��� ���, ���� �� �� ����� ����������
            for (int j = 0; j < initial_size * 100; j++) {
                size_t old_capacity = vec.capacity_get();

                vec.push_back(j);

                // ���������, ��������� �� �������������
                if (vec.capacity_get() != old_capacity) {
                    reallocations++;
                }
            }
        }

        // ��������� ������� ����� ����������
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        double average_time = static_cast<double>(duration) / iterations;

        cout << "���������: " << multiplier << endl;
        cout << "���������� �������������: " << reallocations/iterations << endl;
        cout << "������� ����� ���������� (���): " << average_time << endl << endl;
    }

    return 0;
}