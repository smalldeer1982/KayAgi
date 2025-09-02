#include <iostream>
using namespace std;
int main()
{
	float m, h, x;
	cin >> m >> h;
	x = m / h / h;
	if (x < 18.5)
	{
		cout << "Underweight";
	}
	if (x >= 18.5 && x < 24)
	{
		cout << "Normal";
	}
	if (x > 24)
	{
		cout << x << endl;
		cout << "Overweight";
	}
	return 0;
}
