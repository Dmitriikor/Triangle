#ifndef RAY_TEST_H__
#define RAY_TEST_H__

using TT = int;
using pointer_type_Ray = TT*;

class Ray {
private:
	TT* data = nullptr;

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

	const TT& operator[](size_t index) const;

	TT& operator[](size_t index);

	//[index1; index2)
	Ray operator()(size_t index_first, size_t index_behind_last) const;

	bool is_empty() const;

	const TT& value(size_t index) const;

	TT& value(size_t index);

	void add_to_back(const TT& value);

	void add_to_start(const TT& value);

	void clear();

	~Ray();

};

#endif //! RAY_TEST_H__
