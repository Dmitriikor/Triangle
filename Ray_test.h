#ifndef RAY_TEST_H__
#define RAY_TEST_H__

using T = int;
using pointer_type = T*;

class Ray {
private:
	T* data = nullptr;

	size_t capacity = 0;
	size_t size = 0;

	size_t COEFFICIENT;

	void increase_capacity();

	void expand_ray();

public:
	Ray();

	Ray(size_t capacity);

	Ray(size_t capacity, size_t coefficient);

	Ray(const Ray& other);

	Ray& operator=(const Ray& other);

	const T& operator[](size_t index) const;

	T& operator[](size_t index);

	//[index1; index2)
	Ray operator()(size_t index_first, size_t index_behind_last) const;

	bool is_empty() const;

	const T& value(size_t index) const;

	T& value(size_t index);

	void add_to_back(const T& value);

	void add_to_start(const T& value);

	void clear();

	~Ray();

};

#endif //! RAY_TEST_H__
