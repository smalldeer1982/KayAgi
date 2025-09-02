#include <iostream>
using namespace std;
int main()
{
	int n, x, i = 0, a[105];
	cin >> n;
	x = n;
	while (n != 1)
	{
		if (n % 2 == 1)
		{
			n = n * 3 + 1;
			a[i] = n;
		}
		else
		{
			n = n / 2;
			a[i] = n;
		}
		i += 1;
	}
	for (int j = i - 1; j >= 0; j--)
	{
		cout << a[j] << " ";
	}
	cout << x;
	return 0;
}