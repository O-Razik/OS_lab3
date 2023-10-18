#include <iostream>
#define f(x) ((x) + sin((x)) + sin(pow((x),2)) + sin(pow((x),3)))

int main(int argc, char* argv[])
{
	double x1 = atof(argv[1]), x2 = atof(argv[2]), step = atof(argv[3]);
	
	if(x1<x2)
	{
		int i = 0;
		for (double x = x1; x <= x2; x += step)
			std::cout << " | " << ++i << " | " << x << " | " << f(x) << " | " << std::endl;
	}
	else
		std::cout << "Error: x1>x2" << std::endl;

	getchar();
	return 0;
}
