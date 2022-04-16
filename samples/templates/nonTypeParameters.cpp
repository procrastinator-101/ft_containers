#include <iostream>

float s = 15.36;

class court
{
	public:
	int s;

	court(){};
	void	set(int i) {s = i;}
	int		get() const {return s;}
};

template <typename T, float& val=s>
T max(T x, T y)
{
	std::cout << val << std::endl;
    return (x > y) ? x : y;
}

template <typename T, int cl::*ptr>
T foo(T x)
{
	std::cout << typeid(T).name() << std::endl;
    return x;
}

template <typename T, int size>
T bar(T x)
{
	std::cout << typeid(T).name() << std::endl;
    return x;
}

static float d = 0.2365;
const int court::*ptr = &court::s;

int main()
{
	int i=10, j=20;
	double x=10.1, y=23.3;
	char a='x', b='z';

	// ptr = &cl::s;
	max<int, d>('c', 'j');
	max(i, j);
	max<>(i, j);
	max(x, y);
	max(a, b);
	foo<float, &court::s>(14);
	// foo<float, ptr>(14); //invalid

	bar<int, 5>(10);

	return 0;
}