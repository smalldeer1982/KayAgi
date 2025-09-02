#include <iostream>
using namespace std;
int main()
{
	int n, i, sum = 0, x, a, b, c, a1, b1, c1;
	cin >> n;
	while (n != 495)
	{
		i = 0;
		string str = to_string(n);
		for (char d : str)
		{
			i += 1;
			x = (int)d - '0';
			if (i == 1)
			{
				a = x;
			}
			if (i == 2)
			{
				b = x;
			}
			if (i == 3)
			{
				c = x;
			}
		}
		a1 = a;
		b1 = b;
		c1 = c;
		if (a > c)
		{
			swap(a, c);
		}
		if (a > b)
		{
			swap(a, b);
		}
		if (b > c)
		{
			swap(b, c);
		}
		if (a1 < c1)
		{
			swap(a1, c1);
		}
		if (a1 < b1)
		{
			swap(a1, b1);
		}
		if (b1 < c1)
		{
			swap(b1, c1);
		}
		n = (a1 * 100 + b1 * 10 + c1) - (a * 100 + b * 10 + c) ;
		sum += 1;
	}
	cout << sum;
	return 0;
}