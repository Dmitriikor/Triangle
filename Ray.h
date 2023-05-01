#ifndef RAY_TEMPLATE_H_ 

#define RAY_TEMPLATE_H_ 

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <initializer_list>
//include <utility>
#include <span>

#include <iterator>

template <typename T>
class Ray {
private:

	///!!! initialization in initializer-list (in constructors)
	//friend class iterator;

	T* ray_ = nullptr;

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

	T& get_element_(size_t index);

	const T& get_element_(size_t index) const;

	template<typename T>
	friend void print(const Ray<T>& Ray);
	friend class iterator;
	friend class с_iterator;

		void MOVE_(Ray<T>& other);
	void SWAP_(Ray& other);

public:


	//class star_it {
	//public:
	//	explicit star_it(T* p) : ptr_(p) {}
	//	auto operator<=>(const star_it& other) const
	//	{
	//		return ptr_ <=> other.ptr_;
	//	}
	//	T& operator*() const
	//	{
	//		return *ptr_;
	//	}
	//	T* operator->() const
	//	{
	//		return ptr_;
	//	}
	//	star_it& operator++() {
	//		++ptr_;
	//		return *this;
	//	}
	//	bool operator==(star_it& other)
	//	{
	//		return ptr_ == other.ptr_;
	//	}
	//	star_it& operator+=(int n)
	//	{
	//		ptr_ += n;
	//		return *ptr_;
	//	}
	//private:
	//	T* ptr_;
	//};
	//star_it s_begin() { return star_it(ray_ + (LEFT - F_LEFT)); }
	//star_it s_end() { return star_it(ray_ + (LEFT + F_RIGHT)); }



	class iterator {
	private:
		friend class Ray;

		//!!! МОЖНО ПЕРЕДАВАТЬ THIS
		explicit iterator(Ray* ray_sended, size_t ind) : _Ray_(ray_sended), index_(ind)
		{
		}

	public:
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::contiguous_iterator_tag;


		///////

		pointer data()
		{
			return _Ray_->data();
		}
		const pointer cdata() const {
			return _Ray_->data();
		}
		const pointer data() const {
			return _Ray_->data();
		}
		bool empty() const {
			return _Ray_->empty();
		}
		size_t size() const {
			return _Ray_->size();
		}
		reference operator[](size_t index) {
			return *(_Ray_->ray_[index]);  
		}

		//////


		reference operator*() const
		{
			return _Ray_->ray_[index_];
		}
		pointer operator->() const
		{
			return _Ray_->ray_ + index_;
		}
		iterator& operator++()
		{
			++index_;
			return *this;
		}
		iterator operator++(int)
		{
			iterator tmp = *this;
			++(*this);
			return tmp;
		}
		iterator& operator--()
		{
			--index_;
			return *this;
		}
		iterator operator--(int)
		{
			iterator tmp = *this;
			--(*this);
			return tmp;
		}
		iterator& operator+=(difference_type n)
		{
			index_ += n;
			return *this;
		}
		iterator operator+(difference_type n) const
		{
			iterator tmp = *this;
			tmp.index_ += n;
			return tmp;
		}
		iterator& operator-=(difference_type n)
		{
			index_ -= n;
			return *this;
		}
		iterator operator-(difference_type n) const
		{
			//return *this + (-n);
			iterator tmp = *this;
			tmp.index_ -= n;
			return tmp;
		}
		difference_type operator-(const iterator& other) const
		{
			return index_ - other.index_;
		}
		bool operator==(const iterator& other) const
		{
			return index_ == other.index_;
		}
		/*std::strong_ordering operator<=>(const iterator& other) const
		{
			return index_ <=> other.index_;
		}*/
		//bool operator!=(const iterator& other) const
		//{
		//	return index_ != other.index_;
		//}
		//bool operator<(const iterator& other) const
		//{
		//	return index_ < other.index_;
		//}
		std::strong_ordering operator<=>(const iterator& other) const
		{
			//return (index_ < other.index_) ? std::strong_ordering::less
			//	: (index_ == other.index_) ? std::strong_ordering::equal
			//	: std::strong_ordering::greater;

			if (index_ < other.index_)
				return std::strong_ordering::less;
			else if (index_ == other.index_)
				return std::strong_ordering::equal;
			else
				return std::strong_ordering::greater;
		}
	private:
		Ray<T>* _Ray_;
		size_t index_;

	public:
		//explicit iterator(T* p/*, size_t initial_size*/)
		//	: ptr_(p)/*, initial_size_(initial_size)*/
		//{
		//	//saved_ptr_ = ptr_;
		//}
		//size_t initial_size() const { return initial_size_; }
	//	T& operator*() const
	//	{
	//		return *ptr_;
		//}
		//T* operator->() const {
		//	return ptr_;
		//}
		//iterator& operator++()
		//{
		//	//std::cout << " ++ iterator size = " << initial_size_ << " \n";
		//	++ptr_;
		//	return *this;
		//}
		//iterator operator++(int)
		//{
		//	iterator tmp = *this;
		//	++(*this);
		//	return tmp;
		//}
		//iterator& operator--() {
		//	--ptr_;
		//	return *this;
		//}
		//iterator operator--(int)
		//{
		//	iterator tmp = *this;
		//	--(*this);
		//	return tmp;
		//}
		//bool operator==(const iterator& other) const
		//{
		//	return ptr_ == other.ptr_;
		//}
		//iterator& operator+=(std::ptrdiff_t n)
		//{
		//	ptr_ += n;
		//	return *this;
		//}
		//iterator operator+(std::ptrdiff_t n) const
		//{
		//	iterator tmp(*this);
		//	tmp += n;
		//	return tmp;
		//}
		/*
		static void upd()
		{
			throw std::runtime_error("!");
			//ptr_ = p;
			//initial_size_ = initial_size;
		}

		iterator& saved_ptr()const
		{
			return saved_ptr_;
		}
		*/
		//T* ptr_;
		//size_t initial_size_;
		//T* saved_ptr_;
		//void iterator_check()
		//{
		//	auto R_size = this.F_LEFT + this.F_RIGHT;
		//	
		//	if (initial_size_ != R_size)
		//	{
		//		std::cout << " != iterator size = " << initial_size_ << "; iterator R_size " << R_size <<" \n";
		//		iterator begin();
		//		iterator end();
		//	}
		//	if (initial_size_ > R_size)
		//	{
		//		std::cout << " >  iterator size = " << initial_size_ << "; iterator R_size " << R_size << " \n";
		//		//throw std::runtime_error("!");
		//	}
		//}
	};


	//iterator begin() { return iterator(ray_ + (LEFT - F_LEFT)/*, size()*/); }
	//iterator end() { return iterator(ray_ + (LEFT + F_RIGHT)/*, size()*/); }

	//!!! ДОБИТЬ на базе обычного итератора
	class c_iterator {
	private:
		friend class Ray;

		explicit c_iterator(const Ray* ray_sended, size_t ind) : _Ray_(ray_sended), index_(ind)
		{
		}

	public:
		using value_type = T;
		using pointer = const T*;
		using reference = const T&;
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::contiguous_iterator_tag;

		///////

		pointer data()
		{
			return _Ray_->data();
		}
		const pointer cdata() const {
			return _Ray_->data();
		}
		const pointer data() const {
			return _Ray_->data();
		}
		bool empty() const {
			return _Ray_->empty();   
		}
		size_t size() const {
			return _Ray_->size();
		}
		reference operator[](size_t index) {
			return *(_Ray_->ray_[index_]);  
		}

		//////


		reference operator*() const
		{
			return _Ray_->ray_[index_];
		}
		pointer operator->() const
		{
			return _Ray_->ray_ + index_;
		}
		c_iterator& operator++()
		{
			++index_;
			return *this;
		}
		c_iterator operator++(int)
		{
			c_iterator tmp(*this);
			++(*this);
			return tmp;
		}
		c_iterator& operator--()
		{
			--index_;
			return *this;
		}
		c_iterator operator--(int)
		{
			c_iterator tmp = *this;
			--(*this);
			return tmp;
		}
		c_iterator& operator+=(difference_type n)
		{
			index_ += n;
			return *this;
		}
		c_iterator operator+(difference_type n) const
		{
			c_iterator tmp = *this;
			tmp.index_ += n;
			return tmp;
		}
		c_iterator& operator-=(difference_type n)
		{
			index_ -= n;
			return *this;
		}
		c_iterator operator-(difference_type n) const
		{
			c_iterator tmp = *this;
			tmp.index_ -= n;
			return tmp;
		}
		difference_type operator-(const c_iterator& other) const
		{
			return index_ - other.index_;
		}
		bool operator==(const c_iterator& other) const
		{
			return index_ == other.index_;
		}
		std::strong_ordering operator<=>(const c_iterator& other) const
		{
			return index_ <=> other.index_;
		}

	private:
		const Ray<T>* _Ray_;
		size_t index_;
	};

	iterator begin() { return iterator(this, (LEFT - F_LEFT)); }
	iterator end() { return iterator(this, (LEFT + F_RIGHT)); }

	c_iterator begin() const { return c_iterator(this, (LEFT - F_LEFT)); }
	c_iterator end() const { return c_iterator(this, (LEFT + F_RIGHT)); }
	c_iterator const_begin() const { return c_iterator(this, (LEFT - F_LEFT)); }
	c_iterator const_end() const { return c_iterator(this, (LEFT + F_RIGHT)); }


	Ray();
	//LEFT, RIGHT
	Ray(size_t LEFT, size_t RIGHT);
	//LEFT, RIGHT, COEFFICIENT
	Ray(size_t LEFT, size_t RIGHT, size_t COEFFICIENT);

	Ray(const Ray& other);

	Ray(Ray&& other) noexcept;

	explicit Ray(const std::initializer_list<T>& li);

	Ray(const T* val, size_t size);

	explicit Ray(std::span<T> span);

	~Ray();
	// LEFT
	void add_to_first(const T& value);

	//RIGHT
	void add_to_back(const T& value);

	T& at_(size_t index);

	const T& at_(size_t index) const;

	T& operator[](size_t index);

	const T& operator[](size_t index) const;

	Ray& operator=(const Ray& other);

	Ray& operator=(Ray&& other) noexcept;

	void push_back(const T& value);

	void push_begin(const T& value);

	//LEFT
	void pop_front();

	//RIGHT
	void pop_back();

	void remove(size_t index);

	void insert(size_t index, T& value);

	size_t size() const;

	size_t capacity() const;

	void cut();

	void shrink_to_fit();

	void clear();

	T* data()
	{
		return this->ray_;
	}
	const T* data() const
	{
		return this->ray_;
	}
	const T* cdata() const
	{
		return this->ray_;
	}
	bool empty()
	{
		if ((LEFT - F_LEFT == LEFT) && (RIGHT - F_RIGHT == RIGHT))
			return true;

		return false;
	}

};

template <typename T>
void Ray<T>::create_() {
	ray_ = new T[LEFT + RIGHT]();
}

template <typename T>
void Ray<T>::LEFT_increase_() {
	int new_LEFT = LEFT * COEFFICIENT;
	size_t new_long = new_LEFT + RIGHT;
	T* new_ray = new T[new_long]();

	size_t N = F_LEFT + F_RIGHT; //number of items to carry
	size_t diff = new_LEFT - LEFT + (LEFT - F_LEFT); //offset from start
	for (size_t i = LEFT - F_LEFT; i < N; ++i) { //!!!array out of bounds
		new_ray[i + diff] = std::move(ray_[i]);
	}

	delete[] ray_;

	ray_ = new_ray;
	LEFT = new_LEFT;

	//if (Ray<T>::iterator::count())
	//	Ray<T>::iterator::upd();
}

template <typename T>
void Ray<T>::RIGHT_increase_() {
	int new_RIGHT = RIGHT * COEFFICIENT;
	size_t new_long = LEFT + new_RIGHT;
	T* new_ray = new T[new_long]();

	size_t N = F_LEFT + F_RIGHT; //number of items to carry
	size_t diff = LEFT - F_LEFT; // offset from start
	for (size_t i = 0; i < N; ++i) { //!!!array out of bounds
		new_ray[i + diff] = std::move(ray_[i + diff]);
	}

	delete[] ray_;

	ray_ = new_ray;
	RIGHT = new_RIGHT;

	//if (Ray<T>::iterator::count())
	//	Ray<T>::iterator::upd();
}

template <typename T>
T& Ray<T>::get_element_(size_t index) {
	return ray_[(LEFT - F_LEFT) + index];
}

template <typename T>
const T& Ray<T>::get_element_(size_t index) const {
	return ray_[(LEFT - F_LEFT) + index];
}

template <typename T>
Ray<T>::Ray() :Ray<T>(10u, 10u, 2) {

}

template <typename T>
Ray<T>::Ray(size_t LEFT, size_t RIGHT) : Ray<T>(LEFT, RIGHT, 2u) {

}

template <typename T>
Ray<T>::Ray(size_t LEFT, size_t RIGHT, size_t COEFFICIENT)
	: LEFT(LEFT), COEFFICIENT(COEFFICIENT), RIGHT(RIGHT) {

}

template <typename T>
Ray<T>::Ray(const Ray<T>& other)
{
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

template <typename T>
Ray<T>::Ray(Ray<T>&& other) noexcept :Ray()
{
	SWAP_(other);
}

template <typename T>
Ray<T>::Ray(const std::initializer_list<T>& li)
{
	LEFT = 1;
	RIGHT = li.size();
	COEFFICIENT = 2;
	create_();

	for (auto it = li.begin(); it != li.end(); it++)
	{
		ray_[LEFT + F_RIGHT] = *it;
		++F_RIGHT;
	}
	shrink_to_fit();
}

template <typename T>
void Ray<T>::add_to_first(const T& value) {
	if (ray_ == nullptr)
		create_();

	if (F_LEFT == LEFT) {
		LEFT_increase_();

	}

	ray_[LEFT - F_LEFT - 1] = value;
	++F_LEFT;
}



template <typename T>
void Ray<T>::add_to_back(const T& value) {
	if (ray_ == nullptr)
		create_();

	if (F_RIGHT == RIGHT) {
		RIGHT_increase_();
	}

	ray_[LEFT + F_RIGHT] = value;
	++F_RIGHT;
}

template <typename T>
Ray<T>::Ray(const T* val, size_t size)
{
	LEFT = 1;
	RIGHT = size;
	COEFFICIENT = 2;
	create_();

	for (size_t i = 0; i < size; ++i)
	{
		ray_[LEFT + F_RIGHT] = val[i];
		++F_RIGHT;
	}
	//shrink_to_fit();
}


template <typename T>
T& Ray<T>::at_(size_t index) {
	//if (index ...)
	return Ray<T>::get_element_(index);
}

template <typename T>
const T& Ray<T>::at_(size_t index) const {
	//if (index ...)
	return Ray<T>::get_element_(index);
}

template <typename T>
T& Ray<T>::operator[](size_t index) {
	return get_element_(index);
}

template <typename T>
const T& Ray<T>::operator[](size_t index) const {
	return get_element_(index);
}

template <typename T>
void Ray<T>::push_back(const T& value) {
	add_to_back(value);
}

template <typename T>
void Ray<T>::push_begin(const T& value) {
	add_to_first(value);
}

template <typename T>
void Ray<T>::pop_front() {
	--F_LEFT;
}

template <typename T>
void Ray<T>::pop_back() {
	--F_RIGHT;
}

template <typename T>
void Ray<T>::remove(size_t index) {
	if (index > (LEFT + RIGHT))
		return;

	if (index < F_LEFT) { //index on the left side

		int diff = LEFT - F_LEFT;
		for (int i = index; i > 0; --i) //move to remove
		{
			ray_[diff + i] = ray_[diff + (i - 1)];
		}
		--F_LEFT;

		std::cout << "\n";
	}
	else {
		int diff = LEFT - F_LEFT;
		for (size_t i = index; i < F_RIGHT - 1; ++i) //where do I copy
		{
			ray_[diff + i] = ray_[diff + (i + 1)];
		}

		--F_RIGHT;
	}
}

template <typename T>
void Ray<T>::insert(size_t index, T& value) {

	if (ray_ == nullptr)
		create_();

	if (index >= (LEFT + RIGHT))
		return;

	//number of free
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

template <typename T>
size_t Ray<T>::size() const {
	return F_LEFT + F_RIGHT;
}

template <typename T>
size_t Ray<T>::capacity() const {
	return LEFT + RIGHT;
}

template <typename T>
void Ray<T>::cut() {
	size_t new_long = size();
	T* new_ray = new T[new_long]();

	for (size_t i = 0; i < new_long; i++)
	{
		new_ray[i] = ray_[(LEFT - F_LEFT) + i];
	}
	delete[] ray_;
	LEFT = F_LEFT;
	RIGHT = F_RIGHT;
	ray_ = new_ray;
}

template <typename T>
void Ray<T>::shrink_to_fit() {
	cut();
}

template <typename T>
void Ray<T>::clear() {
	if (ray_ != nullptr)
	{
		delete[] ray_;
		ray_ = nullptr;
	}
	LEFT = saved_LEFT;
	F_LEFT = 0;
	RIGHT = saved_RIGHT;
	F_RIGHT = 0;
}

template <typename T>
Ray<T>::~Ray() {
	clear();
	///delete[] ray_; 
	///std::cout << "\t ! \n";
}

template <typename T>
Ray<T>& Ray<T>::operator=(const Ray<T>& other) {
	///std::cout << "operator=" << std::endl;
	///this -left operand address
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

template <typename T>
Ray<T>& Ray<T>::operator=(Ray<T>&& other) noexcept
{
	if (this != &other)
	{
		clear();
		SWAP_(other);
	}

	return *this;

}

template <typename T>
void Ray<T>::SWAP_(Ray<T>& other)
{
	std::swap(LEFT, other.LEFT);
	std::swap(RIGHT, other.RIGHT);
	std::swap(F_LEFT, other.F_LEFT);
	std::swap(F_RIGHT, other.F_RIGHT);
	std::swap(saved_LEFT, other.saved_LEFT);
	std::swap(saved_RIGHT, other.saved_RIGHT);

	std::swap(COEFFICIENT, other.COEFFICIENT);

	std::swap(ray_, other.ray_);
}

template <typename T>
void Ray<T>::MOVE_(Ray<T>& other)
{

	LEFT = other.LEFT;
	RIGHT = other.RIGHT;
	F_LEFT = other.F_LEFT;
	F_RIGHT = other.F_RIGHT;
	saved_LEFT = other.saved_LEFT;
	saved_RIGHT = other.saved_RIGHT;

	COEFFICIENT = other.COEFFICIENT;

	ray_ = other.ray_;

	//!!! default_initialize - like in default-constructor
	other.ray_ = nullptr;
	other.LEFT = 0;
	other.RIGHT = 0;
	other.F_LEFT = 0;
	other.F_RIGHT = 0;
	other.saved_LEFT = 0;
	other.saved_RIGHT = 0;
	other.COEFFICIENT = 0;
	///}
}


template <typename T>
void print(const Ray<T>& Ray) {

	std::cout << "\n";
	for (size_t i = 0; i < Ray.LEFT + Ray.RIGHT; i++)
		std::cout << std::setw(2) << i << " ";
	std::cout << "\n";

	for (size_t i = 0; i < Ray.LEFT - Ray.F_LEFT; i++)
		std::cout << std::setw(2) << "_" << " ";
	for (size_t i = 0; i < Ray.F_LEFT + Ray.F_RIGHT; i++)
		std::cout << std::setw(2) << i << " ";
	for (size_t i = Ray.F_RIGHT; i < Ray.RIGHT; i++)
		std::cout << std::setw(2) << "_" << " ";
	std::cout << "\n";

	for (size_t i = 0; i < Ray.LEFT - Ray.F_LEFT; i++)
		std::cout << std::setw(2) << "." << " ";
	for (size_t i = Ray.LEFT - Ray.F_LEFT; i < Ray.LEFT + Ray.F_RIGHT; i++) {
		std::cout << std::setw(2) << Ray.ray_[i] << " ";
	}
	///std::cout << std::setw(2) << ray_[i].x << " " << ray_[i].y << " ";
	for (size_t i = Ray.F_RIGHT; i < Ray.RIGHT; i++)
		std::cout << std::setw(2) << "." << " ";
	std::cout << "\n";
}


#endif // !RAY_TEMPLATE_H_ 
