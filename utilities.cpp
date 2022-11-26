#include "utilities.h"


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
	//variable to indicate sign of input number
	bool negative = false;
	register int c;
	int digit_counter = 0;
	int number = 0;
	int long long number_int = 0;

	// extract current character from buffer
	c = getchar();
	if (c == '-')
	{
		// number is negative
		negative = true;

		// extract the next character from the buffer
		c = getchar();
	}

	// if scanned input has a negative sign
	std::cout << "\n\t";
	if (negative)
		std::cout << "-";
	// Keep on extracting characters if they are integers
	// i.e ASCII Value lies from '0'(48) to '9' (57)
	for (; (c > 47 && c < 58); c = getchar())
	{
		std::cout << number * 10 + c - 48;
		number_int = number_int * 10 + c - 48;
		++digit_counter;
	}
	// if scanned input has a negative sign, negate the
	// value of the input number
	if (negative)
		number_int *= -1;

	std::cout << "\n\t" << number_int << "\n";
	std::cout << "\n\t" << digit_counter << "\n";
}

 

//Dot* utilities::start_dialoge(std::streamsize MAX_STREAMSIZE, size_t n_points, std::string path_in, std::string path_out)
//{
	// { start dialoge
	 

	//clear_cls(OS);

	//  } start dialoge

