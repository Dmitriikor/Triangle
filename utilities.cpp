#include "utilities.h"


double utilities::round_by_step(double x, double step) {
	double modulo = fmod(x, step);
	if (modulo < step / 2)
		return x - modulo;
	return x - modulo + step;
}

 

Point* utilities::start_dialoge(std::streamsize MAX_STREAMSIZE, size_t n_points, std::string path_in, std::string path_out)
{
	// { start dialoge
	 
	int OS_start_dialoge_type_;
	std::cout << "Choise OS:\n \t1 Win, \n \t2 Ubuntu: \n \t3 Manual path to save:\n";
	std::cin >> OS_start_dialoge_type_;
	//std::string path_in;
	//std::string path_out;

	switch (OS_start_dialoge_type_) {
	case 1: {
		path_in = { "points.txt" };
		path_out = { "out.txt" };
		break;
	}
	case 2: {
		path_in = { "Tiangle_RE/points.txt" };
		path_out = { "Tiangle_RE/out2.txt" };
		break;
	}
	case 3: {
		//std::getline (std::cin,name);
		std::cout << "\n Enter path_in \n\t";
		std::getline(std::cin, path_in);
		std::cout << "\n Enter path_out \n\t";
		std::getline(std::cin, path_out);
		break;
	}
	default: {
		std::cout << "PROGRAM OVER\n";
		return 0;
	}
	}


	std::cout << "Choise mode:\n \t1 input on file, \n \t2 input manual: \n \t3 auto:\n";
	int input_switch;
	std::cin >> input_switch;
	std::cin.ignore(MAX_STREAMSIZE, '\n');

	if (input_switch != 1 && input_switch != 2 && input_switch != 3) {
		std::cout << "PROGRAM OVER\n";
		return 0;
	}

	std::ifstream infile(path_in);
	std::ofstream outfile(path_out);
	

	std::istream& input = input_switch == 1 ? infile : std::cin;

	//if (input_switch == 2 || input_switch == 3)


	if (input_switch == 2)
		std::cout << "Enter points:\n";

	int max_x = INT_MIN;
	int max_y = INT_MIN;
	int min_x = INT_MAX;
	int min_y = INT_MAX;

	Point* point_arr = new Point[n_points];

	for (size_t i = 0; i < n_points; i++) {
		Point temp;

		if (input_switch == 3) {
			//(rand()%range)±shift
			srand(time(NULL) + (rand() % 225000));
			temp.x = (rand() % 76) + (-38);  // 76 -38
			//Sleep(1000);
			srand(time(NULL) + (rand() % 155000));
			temp.y = (rand() % 60) + (-30);  // 60 - 30
			std::cout << temp.x << " " << temp.y << "\n";
		}
		else {
			input >> temp.x >> temp.y;
		}

		if (temp.x > max_x)
			max_x = temp.x;
		if (temp.y > max_y)
			max_y = temp.y;

		if (temp.x < min_x)
			min_x = temp.x;
		if (temp.y < min_y)
			min_y = temp.y;

		point_arr[i] = temp;
	}

	//clear_cls(OS);
	return point_arr;
	//  } start dialoge
}
