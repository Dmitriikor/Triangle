//#include <iostream>
//using namespace std;
//
//struct Struct
//{
//	int var;
//
//	void foo()
//	{
//		int& ref = var;
//		auto f = [&ref]() { ref = 5;  cout << ref << endl; };
//
//		auto f = [&obj = var]() {cout << obj << endl; };
//	}
//};
//
//class Foo
//{
//public:
//	Foo() : mBar1(1), mBar2(2) {}
//
//	void doBar()
//	{
//		auto test = [this->mBar1]()
//		{
//			std::cout << mBar1 << "\n";
//			// Trying to access 'mBar2' here would fail to compile...
//		};
//
//		test();
//	}
//
//	int mBar1;
//	int mBar2;
//};
//
//int main()
//{
//	int a, b, c;
//
//	auto f = [a]() { a = 5;  cout << a << endl; };
//
//	f();
//
//	cout << a << endl;
//
//	return 0;
//}