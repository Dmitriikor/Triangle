#include "Switch_cls_clear_from_os_type_test.h"
void clear_cls(int OS) 
{

	if (OS < 1 || OS > 2)
	{
		throw std::runtime_error("Switch_cls_clear_from_os_type_test.cpp clear_cls OS !=1,2");
		return;
	}
	switch (OS) {
	case 1:
		system("cls");
		break;
	case 2:
		system("clear");
		break;
	}
}