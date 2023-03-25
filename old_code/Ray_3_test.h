
#ifndef RAY_3_TEST_H__

#define  RAY_3_TEST_H__

#include <iomanip>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <utility>

#include "Point.h"

using TTT = Dot;
using reference_type = TTT&;

class Ray_3_ {
private:

	TTT* ray_ = nullptr;

	size_t LEFT = 0;
	size_t F_LEFT = 0;
	size_t RIGHT = 0;
	size_t F_RIGHT = 0;

	size_t COEFFICIENT = 0;

	size_t saved_LEFT = LEFT;
	size_t saved_RIGHT = RIGHT;

	void create_();

	void LEFT_increase_();

	void RIGHT_increase_();

	// LEFT|------------------0------------------|RIGHT
	// LEFT|------------------0-------F_RIGHT----|RIGHT
	// LEFT|----F_LEFT--------0-------F_RIGHT----|RIGHT
	// LEFT|----LEFT - F_LEFT-0-------F_RIGHT----|RIGHT
	// LEFT|----INDEX---------0-------F_RIGHT----|RIGHT
	// LEFT|-------------LEFT+-+RIGHT------------|RIGHT

	TTT& get_element_(size_t index);

	const TTT& get_element_(size_t index) const;

public:


	Ray_3_();
	//LEFT, RIGHT
	Ray_3_(size_t LEFT, size_t RIGHT);
	//LEFT, RIGHT, COEFFICIENT
	Ray_3_(size_t LEFT, size_t RIGHT, size_t COEFFICIENT);

	Ray_3_(const Ray_3_& other);

	// LEFT
	void add_to_first(const TTT& value);

	//RIGHT
	void add_to_back(const TTT& value);

	TTT& at_(size_t index);

	const TTT& at_(size_t index) const;

	TTT& operator[](size_t index);

	const TTT& operator[](size_t index) const;

	void print() const;

	void push_back(const TTT& value);

	void push_begin(const TTT& value);

	//LEFT
	void pop_front();

	//RIGHT
	void pop_back();

	void remove(size_t index);

	void insert(size_t index, TTT& value);

	size_t size() const;

	size_t capacity() const;

	void cut();

	void shrink_to_fit();

	void clear();

	~Ray_3_();

	Ray_3_& operator=(const Ray_3_& other);
};






#endif //!  RAY_3_TEST_H__

