#include<iostream>

struct Point {
	int X;
	int Y;
	Point() : X(0), Y(0) {}
};

// 1
bool operator < (const Point& l, const Point& r)
{
	return l.X < r.X;
}

// 2
bool IsLessX(const Point& l, const Point& r)
{
	return l.X < r.X;
}

bool IsLessY(const Point& l, const Point& r)
{
	return l.Y < r.Y;
}

// 3
template<class T>
bool IsLessDefault(const T& l, const T& r)
{
	return l < r;
}

// 4
template<class T>
class IsLess {
public:
	bool operator()(const T& l, const T& r) { return l < r; } 
};

template<class T, class Compare>
void mySort(T* arr, int from, int to, Compare cmp/*bool (*isLess)(const T&, const T&) = IsLessDefault*/)
{
	for( int i = from; i < to; i++ )
		for( int j = from; j < to - 1; j++ )
			if( cmp(arr[j + 1], arr[j]) )
				std::swap(arr[j], arr[j + 1]);
}

int main()
{
	int n = 0;
	std::cin >> n;
	// 10 12 3 4 21 32 1 2 0 56 2
	Point* arr = new Point[n];
	for( int i = 0; i < n; i++ )
		std::cin >> arr[i].X >> arr[i].Y;

	mySort(arr, 0, n, IsLessX);
	
	for( int i = 0; i < n; i++ )
		std::cout << "(" << arr[i].X << ", " << arr[i].Y << "), ";

	mySort(arr, 0, n, IsLessY);
	
	for( int i = 0; i < n; i++ )
		std::cout << "(" << arr[i].X << ", " << arr[i].Y << "), ";

	delete [] arr;

	return 0;
}