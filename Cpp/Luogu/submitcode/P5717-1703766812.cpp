#include <iostream>
#include<algorithm>
using namespace std;
int main()
{
	int a, b, c, d[3], n = 0;
	for (int i = 0; i < 3; i++)
	{
		cin >> d[i];
	}
	sort(d, d + 3);
	a = d[0];
	b = d[1];
	c = d[2];
	for (int i = 1; i <= 3; i++)
	{
		if (i == 1 && a + b <= c)
		{
			n += 1;
		}
		if (i == 2 && a + c <= b)
		{
			n += 1;
		}
		if (i == 3 && c + b <= a)
		{
			n += 1;
		}
	}
	if (n != 0)
	{
		cout << "Not triangle" << endl;
	}
	else
	{
		if (a * a + b * b == c * c)
		{
			cout << "Right triangle" << endl;
		}
		if (a * a + b * b > c * c)
		{
			cout << "Acute triangle" << endl;
		}
		if (a * a + b * b < c * c)
		{
			cout << "Obtuse triangle" << endl;
		}
		if (a == b || b == c || a == c)
		{
			cout << "Isosceles triangle" << endl;
		}
		if (a == b && b == c)
		{
			cout << "Equilateral triangle" << endl;
		}
	}

	return 0;
}