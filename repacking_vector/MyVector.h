#pragma once

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

template <typename T>
class Vector {
private:
	double multiplier = 2;

	int n = 0;
	int capacity = 0;
	T* arr = nullptr;

	void resize(int newCapacity) {
		T* newarr = new T[newCapacity];
		for (int i = 0; i < n; i++) {
			newarr[i] = this->arr[i];
		}
		delete[] this->arr;
		this->arr = newarr;
		this->capacity = newCapacity;
	}
public:
	Vector() {
		this->capacity = 1;
		this->arr = new T[this->capacity];
	};

	Vector(const Vector& c) {
		this->n = c.n;
		this->capacity = c.capacity;
		this->arr = new T[this->capacity];
		for (int i = 0; i < this->n; i++) {
			this->arr[i] = c.arr[i];
		}
	};

	Vector(int n, const T p = 0) {
		this->n = n;
		this->capacity = n * multiplier;
		this->arr = new T[this->capacity];
		for (int i = 0; i < n; i++) {
			this->arr[i] = p;
		}
	};

	~Vector() {
		delete[] this->arr;
	};

	Vector& operator=(const Vector& a) {
		this->n = a.n;
		this->capacity = a.capacity;
		delete[] this->arr;
		this->arr = new T[this->capacity];
		for (int i = 0; i < a.n; i++) {
			this->arr[i] = a.arr[i];
		}
		return *this;
	};

	void multiplier_change(double value) { this->multiplier = value;; }

	int capacity_get() { return this->capacity; }

	template <typename U>
	Vector<decltype(T() + U())> operator+(const Vector<U>& b) const {
		Vector<decltype(T() + U())> result(min(this->size(), b.size()));

		for (int i = 0; i < min(this->size(), b.size()); i++) {
			result[i] = (*this)[i] + b[i];
		}

		return result;
	};

	Vector operator *(T b) {
		Vector c;
		for (int i = 0; i < this->n; i++) {
			c.arr[i] = this->arr[i] * b;
		}
		return c;
	};

	bool operator==(const Vector& a) {
		if (this->n == a.n) {
			for (int i = 0; i < this->n; i++) {
				if (this->arr[i] != a.arr[i]) {
					return false;
				}
			}
		}
		else {
			return false;
		}
		return true;
	};

	T operator[](int i) const {
		if (i < 0 || this->capacity <= i) {
			throw "Index out of range";
		}
		return this->arr[i];
	};

	T& operator[](int i) {
		if (i < 0 || this->capacity <= i) {
			throw "Index out of range";
		}
		return this->arr[i];
	};

	bool empty() const {
		return this->n == 0;
	};

	double size() const {
		return this->n;
	};

	void push_back(const T next) {
		if (this->n == this->capacity) {
			resize(capacity * multiplier);
		}
		this->arr[n] = next;
		this->n++;
	};

	void pop_back() {
		if (this->n > 0) {
			this->n--;
		}
	};

	void swap(int j, int k) {
		T p = this->arr[j];
		this->arr[j] = this->arr[k];
		this->arr[k] = p;
	};

	friend ostream& operator<<(ostream& ostr, const Vector& v) {
		ostr << '(';
		for (int i = 0; i < v.size(); i++) {
			ostr << v[i] << ' ';
		}
		ostr << ')';
		return ostr;
	};

	void insert(int j, T a) {
		if (this->n == this->capacity) {
			resize(capacity * multiplier);
		}
		for (int i = this->n; i > j; i--) {
			this->arr[j] = this->arr[j - 1];
		}
		this->arr[j] = a;
	};

	void erase(int j) {
		for (int i = j - 1; i < this->n - 1; i++) {
			this->arr[i] = this->arr[i + 1];
		}
		this->n--;
	};
};