#ifndef HELLO_H__

#define  HELLO_H__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>

#include "Ray_template.h"

//#include "Ray_3_test.h"

#include "Point_test.h"
#include "Matrix_test.h"
#include "Is_equal_test.h"

#include "utilities.h"

class Canvas
{
public:
	Point MAX_VIRTUAL_;
	Point MIN_VIRTUAL_;

	Ray_template<Dot> points_to_draw_;		//свободные точки для рисования

};

class Canvas_console : public Canvas
{
protected:

	Coordinates ORIGIN_;

	int width_x_;
	int width_y_;

	int axis_x_indents_;
	int axis_x_strings_;

	int width_x_with_indent_;
	int width_y_with_indent_;

	int coefficient;

	bool debug;

	void max_min_init();
	void initialize_width();

	void x_axis_filling(Matrix& arr, size_t axis_length, int min_x, int axis_location);
	void y_axis_filling(Matrix& arr, size_t axis_length, int min_x, int axis_location);
	int get_distance_between(int min_coord, int max_coord);
	void add_point_to_arr_for_print_line(const Dot& A, const Dot& B, bool is_round = true, char symbol = '+'); //add point to arr for print
	void update_min_max_by(const Dot& pt);
	void set_min_max();


	void remove_no_rounding_line(const Dot& A, const Dot& B);
	void remove_rounding_line(const Dot& A, const Dot& B);

	Coordinates& ZERO() ///!!!
	{
		return ORIGIN_;
	}
	Ray_template<Dot> calculate_line_with_rounding(const Dot& A, const Dot& B, char symbol = '+');
	Ray_template<Dot> calculate_line_swap(const Dot& A, const Dot& B, char symbol = '+');

public:
	Canvas_console();

	//Canvas_console(const Canvas_console& other) = default; //!!! system copy-cobstructor

	void operator+=(const Canvas_console& other)
	{
		insert(other.points_to_draw_); //another method (private)

		//!!! ONLY HERE (Canvas)
		//set_min_max(); //!!! max and min is from this or other (NOT checking ALL OF IT)
		//initialize_width(); //!!! same 
	}

	//!!! operator + 

	template <typename T>
	void insert(const Ray_template<T>& points); //!!! так можно, но тут не нужно => перегрузка


	void insert(const Dot& pt)
	{
		update_min_max_by(pt); //!!! more effective
	}

	void check_and_insert_point(const Dot& pt);
	void add_lines(const Dot& A, const Dot& B, bool is_round, char symbol); //!!! is_round
	void remove_line_total(const Dot& A, const Dot& B);
	void remove_point(const Dot& dl);

	virtual void print() {}
	virtual void remove_line(const Dot& A, const Dot& B) {}

	void go_debug(bool is_debug = false);


	//~Canvas_console() = default; //!!! system
};



class Corner : public Canvas_console
{
public:
	void fill(char fill_symbol)
	{
		create(fill_symbol);
	}
	void print()
	{
		corner_arr().clear();
		create();
		add_points_to_corner();
		/*this_.*/corner_arr().print();
		//corner_arr().print_to_raw();
	}
	void print_zero();
	void remove(const Dot& dot_to_erase)
	{
		remove_line_total(dot_to_erase, dot_to_erase);
		erase_point_from_corner(dot_to_erase);
	}
	void remove_line(const Dot& A, const Dot& B)
	{
		remove_line_total(A, B);
	}
	void change_file_path(Ray_template <char> adress)
	{
		outfile_adress = adress;
	}
	void print(int a/*std::ostream& output*/)/////////////////////////////////////////////////!!!!!!!!!!!
	{
		T* outfile_adress_2 = new T[outfile_adress.size() + 1];	// Серьезность	Код	Описание	Проект	Файл	Строка	Состояние подавления
																//Предупреждение	C6386	Переполнение буфера при записи в "outfile_adress_2".matrix	Z : \с++\Triangle\hello.h	196


		for (int i = 0; i < outfile_adress.size(); ++i)
			outfile_adress_2[i] = outfile_adress[i];

		outfile_adress_2[outfile_adress.size()] = '\0';

		std::ofstream outfile_corner(outfile_adress_2); //////////////////////////////////////////////???????????????????????????????????????????????

		corner_arr().print(outfile_corner);
		delete[] outfile_adress_2;
	}
	void clear();

private:
	Matrix corner_arr_;
	Ray_template <char> outfile_adress = { 'c', 'o', 'r','n','e','r','_','p','a','t','h','_','o','u','t','.','t','x','t' }; //!!! string
	template <typename T>
	void draw_points_or_line_corner(Ray_template<T>& loc_arr_to_draw, Matrix& loc_arr); //not for public mb move to Canvas
	void add_points_to_corner();
	void create(/*Canvas& this_,*/ char axys_arr_fill_symbol = ' ');
	void erase_point_from_corner(const Dot& err);
	Matrix& corner_arr()
	{
		return corner_arr_;
	}
};



class Axys : public Canvas_console
{
public:
	void set_at(Coordinates cell, char symbol)
	{
		axys_arr_.set_at(cell.i, cell.j, symbol);
	}
	void erase_point_from_axys(Dot& err);
	void create(char axys_arr_fill_symbol = ' ');
	void remove()
	{
		/*this_.*/axys_arr_.clear();
	}
	void print()
	{
		axys_arr_.clear();
		create();
		draw_points();
		axys_arr_.print();
	}
	void draw_points();
	void print(std::ostream& output)
	{
		axys_arr_.print(output);
	}

private:

	Matrix axys_arr_;
	template <typename T>
	void draw_points_or_line_axys(Ray_template<T>& loc_arr_to_draw, Matrix& loc_arr);
};


#endif //!  HELLO_H__