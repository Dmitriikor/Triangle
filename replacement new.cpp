#include <iostream>
namespace reint
{
	struct reinterpret_Strukt
	{
		char str[100];
		reinterpret_Strukt() { std::cout << "constructor" << std::endl; }
		~reinterpret_Strukt() { std::cout << "destructor" << std::endl; }
	};

	int reinterpret_sample()
	{
		//S* ptr = new S();
		//delete ptr;

		reinterpret_Strukt* ptr = reinterpret_cast<reinterpret_Strukt*> (malloc(sizeof(reinterpret_Strukt)));
		new(ptr) reinterpret_Strukt();

		new((char*)ptr + 10) int[10]();

		for (int i = 0; i < 100; ++i)
			std::cout << (int)ptr->str[i] << " ";
		std::cout << std::endl;

		ptr->~reinterpret_Strukt();
		free(ptr);

		return 0;
	}
}