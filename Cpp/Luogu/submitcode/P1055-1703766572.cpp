#include<iostream>
using namespace std;
int main()
{
	int sum = 0, x = 1;
	int a[18];
	char b[18];
	int y = 0;
	cin >> b;
	for (int i = 0; b[i] != '\0'; i++)
	{
		a[i + 1] = b[i] - '0';
	}
	for (int i = 1; i <= 11; i++)
	{
		if (i == 2 || i == 6)
		{
			continue;
		}
		sum += a[i] * x;
		x++;
	}
	if (sum % 11 == 10)
	{
		y = 40;
	}
	if (sum % 11==a[13] || y == a[13])
	{
		cout << "Right";
	}
	else
	{
		for (int i = 1; i <= 12; i++)
		{
			if (i == 2 || i == 6 || i == 12)
			{
				cout << '-';
			}
			else
			{
				cout << a[i];
			}
		}
		if (sum % 11 == 10)
		{
			cout << "X";
		}
		else
		{
			cout << sum % 11;
		}
	}
	return 0;
}