

#include "Ray_3_test.h"


//using TTT = std::vector<int>;


void Ray_3_::create_() {
	ray_ = new TTT[LEFT + RIGHT]();
}

void Ray_3_::LEFT_increase_() {
	int new_LEFT = LEFT * COEFFICIENT;
	size_t new_long = new_LEFT + RIGHT;
	TTT* new_ray = new TTT[new_long]();

	size_t N = F_LEFT + F_RIGHT; //количество переносимых элементов 
	size_t diff = new_LEFT - LEFT + (LEFT - F_LEFT); // сдвиг относительно начала
	for (size_t i = LEFT - F_LEFT; i < N; ++i) { //!!!выход за границы массива
		new_ray[i + diff] = std::move(ray_[i]);
	}

	delete[] ray_;

	ray_ = new_ray;
	LEFT = new_LEFT;
}

void Ray_3_::RIGHT_increase_() {
	int new_RIGHT = RIGHT * COEFFICIENT;
	size_t new_long = LEFT + new_RIGHT;
	TTT* new_ray = new TTT[new_long]();

	size_t N = F_LEFT + F_RIGHT; //количество переносимых элементов 
	size_t diff = LEFT - F_LEFT; // сдвиг относительно начала
	for (size_t i = 0; i < N; ++i) { //!!!выход за границы массива
		new_ray[i + diff] = std::move(ray_[i + diff]);
	}

	delete[] ray_;

	ray_ = new_ray;
	RIGHT = new_RIGHT;
}

TTT& Ray_3_::get_element_(size_t index) {
	return ray_[(LEFT - F_LEFT) + index];
}

const TTT& Ray_3_::get_element_(size_t index) const {
	return ray_[(LEFT - F_LEFT) + index];
}

Ray_3_::Ray_3_():Ray_3_(10u, 10u, 2) {

}

Ray_3_::Ray_3_(size_t LEFT, size_t RIGHT) : Ray_3_(LEFT, RIGHT, 2u) {

}

Ray_3_::Ray_3_(size_t LEFT, size_t RIGHT, size_t COEFFICIENT)
	:LEFT(LEFT), COEFFICIENT(COEFFICIENT), RIGHT(RIGHT) {

}

Ray_3_::Ray_3_(const Ray_3_& other)
/*:LEFT(LEFT), COEFFICIENT(COEFFICIENT), RIGHT(RIGHT) */
{
	std::cout << "copy-constructor " << std::endl;
	LEFT = other.LEFT;
	RIGHT = other.RIGHT;
	F_LEFT = other.F_LEFT;
	F_RIGHT = other.F_RIGHT;

	COEFFICIENT = other.COEFFICIENT;

	saved_LEFT = LEFT;
	saved_RIGHT = RIGHT;

	create_();

	for (size_t i = LEFT - F_LEFT; i < LEFT + F_RIGHT; ++i)
		ray_[i] = other.ray_[i];
}

void Ray_3_::add_to_first(const TTT& value) {
	if (ray_ == nullptr)
		create_();

	if (F_LEFT == LEFT) {
		LEFT_increase_();

	}

	ray_[LEFT - F_LEFT - 1] = value;
	++F_LEFT;
}

void Ray_3_::add_to_back(const TTT& value) {
	if (ray_ == nullptr)
		create_();

	if (F_RIGHT == RIGHT) {
		RIGHT_increase_();
	}

	ray_[LEFT + F_RIGHT] = value;
	++F_RIGHT;
}

TTT& Ray_3_::at_(size_t index) {
	//if (index ...)
	return Ray_3_::get_element_(index);
}

const TTT& Ray_3_::at_(size_t index) const {
	//if (index ...)
	return Ray_3_::get_element_(index);
}

TTT& Ray_3_::operator[](size_t index) {
	return get_element_(index);
}

const TTT& Ray_3_::operator[](size_t index) const {
	return get_element_(index);
}

void Ray_3_::print() const {

	std::cout << "\n";
	for (size_t i = 0; i < LEFT + RIGHT; i++)
		std::cout << std::setw(2) << i << " ";
	std::cout << "\n";

	for (size_t i = 0; i < LEFT - F_LEFT; i++)
		std::cout << std::setw(2) << "_" << " ";
	for (size_t i = 0; i < F_LEFT + F_RIGHT; i++)
		std::cout << std::setw(2) << i << " ";
	for (size_t i = F_RIGHT; i < RIGHT; i++)
		std::cout << std::setw(2) << "_" << " ";
	std::cout << "\n";

	for (size_t i = 0; i < LEFT - F_LEFT; i++)
		std::cout << std::setw(2) << "." << " ";
	for (size_t i = LEFT - F_LEFT; i < LEFT + F_RIGHT; i++)
		std::cout << std::setw(2) << ray_[i].x << " " << ray_[i].y << " ";
	for (size_t i = F_RIGHT; i < RIGHT; i++)
		std::cout << std::setw(2) << "." << " ";
	std::cout << "\n";
}

void Ray_3_::push_back(const TTT& value) {
	add_to_back(value);
}

void Ray_3_::push_begin(const TTT& value) {
	add_to_first(value);
}

void Ray_3_::pop_front() {
	--F_LEFT;
}

void Ray_3_::pop_back() {
	--F_RIGHT;
}

void Ray_3_::remove(size_t index) {
	if (index > (LEFT + RIGHT))
		return;

	if (index < F_LEFT) { //индекс в левой части

		int diff = LEFT - F_LEFT;
		for (int i = index; i > 0; --i) //сдвигаем для удаления
		{
			ray_[diff + i] = ray_[diff + (i - 1)];
		}
		--F_LEFT;

		std::cout << "\n";
	}
	else {
		int diff = LEFT - F_LEFT;
		for (size_t i = index; i < F_RIGHT - 1; ++i) //куда копирую
		{
			ray_[diff + i] = ray_[diff + (i + 1)];
		}

		--F_RIGHT;
	}
}

void Ray_3_::insert(size_t index, TTT& value) {

	if (ray_ == nullptr)
		create_();

	if (index >= (LEFT + RIGHT))
		return;

	//количество свободных
	int L = LEFT - F_LEFT;
	int R = RIGHT - F_RIGHT;

	if (L == 0) {
		LEFT_increase_();
		L = LEFT - F_LEFT;
	}

	int diff = LEFT - F_LEFT;
	++F_LEFT;
	for (int i = 0; i < index; ++i)
	{
		ray_[diff + i - 1] = std::move(ray_[diff + i]);
	}
	ray_[diff + index - 1] = value;
}

size_t Ray_3_::size() const {
	return F_LEFT + F_RIGHT;
}

size_t Ray_3_::capacity() const {
	return LEFT + RIGHT;
}

void Ray_3_::cut() {
	size_t new_long = size();
	TTT* new_ray = new TTT[new_long]();

	for (size_t i = 0; i < new_long; i++)
	{
		new_ray[i] = ray_[(LEFT - F_LEFT) + i];
	}
	delete[] ray_;
	LEFT = F_LEFT;
	RIGHT = F_RIGHT;
	ray_ = new_ray;
}

void Ray_3_::shrink_to_fit() {
	cut();
}

void Ray_3_::clear() {
	delete[] ray_;
	ray_ = nullptr;
	LEFT = saved_LEFT;
	F_LEFT = 0;
	RIGHT = saved_RIGHT;
	F_RIGHT = 0;
}

Ray_3_::~Ray_3_()  {
	clear();
	//delete[] ray_; 
	//std::cout << "\t ! \n";
}

Ray_3_& Ray_3_::operator=(const Ray_3_& other) {
	//std::cout << "operator=" << std::endl;
	//this - адрес левого операнда
	if (this != &other) {
		LEFT = other.LEFT;
		RIGHT = other.RIGHT;
		F_LEFT = other.F_LEFT;
		F_RIGHT = other.F_RIGHT;

		COEFFICIENT = other.COEFFICIENT;

		saved_LEFT = LEFT;
		saved_RIGHT = RIGHT;

		delete[] ray_;
		create_();

		for (size_t i = LEFT - F_LEFT; i < LEFT + F_RIGHT; ++i)
			ray_[i] = other.ray_[i];
	}

	return *this;
}


void print_out(double time_, size_t i) {
	printf("\033[%d;%dH", 0 + 1, 0 + 1);
	std::cout << std::setw(10) << time_ << " ";
	std::cout << "\t\t";
	std::cout << i;
	std::cout << "\t ";

}
