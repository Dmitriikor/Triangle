#include "utilities.h"

bool utilities::isEqual(long double a, long double b, long double eps)
{
	if (std::abs(a - b) <= eps)
		return true;

	return false;
}

double utilities::round_by_step(double x, double step) {
	double modulo = fmod(x, step);
	if (modulo < step / 2)
		return x - modulo;
	return x - modulo + step;
}


int utilities::random_INT(int start, int end)
{
	std::random_device rnd;
	std::uniform_int_distribution<int> dist(start, end);

	return dist(rnd);
}


void utilities::fast_print()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
}

void utilities::fastscan(std::istream& cin)
{
	// variable to indicate sign of input number
	bool negative = false;
	int long long number_int;
	int digit_counter;

	// extract current character from buffer
	char c = getchar();
	if (c == '-' || c == '+')
	{
		// number is negative
		if (c == '-')
			negative = true;

		// extract the next character from the buffer
		c = getchar();
	}

	// if scanned input has a negative sign
	//std::cout << "\n\t" << (negative ? "-" : "");

	number_int = 0;
	digit_counter = 0;
	// Keep on extracting characters if they are integers
	// i.e ASCII Value lies from '0'(48) to '9' (57)
	while (c >= '0' && c <= '9')
	{
		//std::cout << c - '0';
		int digit = c - '0';
		number_int = number_int * 10 + digit;
		++digit_counter;
		c = getchar();
	}
	// if scanned input has a negative sign, negate the
	// value of the input number
	if (negative)
		number_int *= -1;

	std::cout << "\n\t" << number_int << "\n";
	std::cout << "\n\t" << digit_counter << "\n";
}


int utilities::get_distance_between(int min_coord, int max_coord)
{
	if (min_coord >= 0 && max_coord >= 0)
		return abs(max_coord);

	if (min_coord <= 0 && max_coord <= 0)
		return abs(min_coord);

	return abs(max_coord) + abs(min_coord);
}



////Dot* utilities::start_dialoge(std::streamsize MAX_STREAMSIZE, size_t n_points, std::string path_in, std::string path_out)
////{
//	// { start dialoge
//
//
//	//clear_cls(OS);
//
//	//  } start dialoge

