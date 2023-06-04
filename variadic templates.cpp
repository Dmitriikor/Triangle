#include <iostream>
using namespace std;

void print()
{
}

template<typename T, typename... Elements>
void print(T first, Elements... values)
{
	cout << first << endl;
	print(values...);
}

int main_v()
{
	int n = 15;

	print("Number is ", 12, '*', n);
	//printf("%s%d%c%d", "Number is ", 12, '\n', n);

	return 0;
}