#include <stdexcept>
#include "Ray_test.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Ray_exception_start
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Ray::increase_capacity() {
	capacity *= COEFFICIENT;
}

void Ray::expand_ray() {
	increase_capacity();
	TT* temp = new TT[capacity];

	for (size_t i = 0; i < size; i++) {
		temp[i] = data[i];
	}

	delete[] data;
	data = temp;
}

bool  Ray::is_empty() const {
	return (size == 0) ? true : false;
}

const TT& Ray::value(size_t index) const {
	return data[index];
}

TT& Ray::value(size_t index) {
	return data[index];
}

void Ray::add_to_back(const TT& value) {
	if (size == capacity) {
		expand_ray();
	}

	data[size] = value;
	++size;
}

void Ray::add_to_start(const TT& value) {
	if (size == capacity)
		expand_ray();

	for (size_t i = size; i > 0; --i) {
		data[i] = data[i - 1];
	}
	data[0] = value;
	++size;
}

void Ray::clear() {
	delete[] data;
	capacity = 10u;
	data = new TT[capacity];
	size = 0;
}

Ray::~Ray() {
	delete[] data;
}

Ray Ray::operator()(size_t index_first, size_t index_behind_last) const {
	//!!! THROW EXCEPT
	size_t& index1 = index_first;
	size_t& index2 = index_behind_last;

	size_t max = index2;
	size_t min = index1;

	if (index1 > index2) {
		max = index_first;
		min = index2;
	}

	size_t N = max - min;
	Ray sub_data(N);
	sub_data.size = N;

	for (size_t i = 0; i < N; i++)
	{
		sub_data.data[i] = data[i + min];
	}

	return sub_data;
}

TT& Ray::operator[](size_t index) {
	if (index >= size)
		throw std::out_of_range("TT& operator[](size_t index): index >= size");
	return value(index);
}

const TT& Ray::operator[](size_t index) const {
	return value(index);
}

Ray& Ray::operator=(const Ray& other) {
	//this - адрес левого операнда
	if (this != &other) {
		capacity = other.capacity;
		size = other.size;
		COEFFICIENT = other.COEFFICIENT;
		delete[] data;
		data = new TT[capacity];
		for (size_t i = 0; i < other.size; ++i)
			data[i] = other.data[i];
	}

	return *this;
}

Ray::Ray(const Ray& other) :capacity(other.capacity), size(other.size), COEFFICIENT(other.COEFFICIENT) {
	data = new TT[capacity];
	for (size_t i = 0; i < other.size; ++i)
		data[i] = other.data[i];
}

Ray::Ray(size_t capacity, size_t coefficient) :capacity(capacity), size(0), COEFFICIENT(coefficient) {
	data = new TT[capacity];
}

Ray::Ray(size_t capacity) :Ray(capacity, 2u) {

}

Ray::Ray() :Ray(10u) {

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Ray_exception_end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
