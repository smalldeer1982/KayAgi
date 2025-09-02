#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n, x = 1;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (x / 10 == 0)
			{
				cout << 0 << x;
			}
			else
			{
				cout << x;
			}
			x += 1;
		}
		cout << endl;
	}
	cout << endl;
	x = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int k = 0; k <= (n - i)-1; k++)
		{
			cout << "  ";
		}
		for (int j = 1; j <= i; j++)
		{
			if (x / 10 == 0)
			{
				cout << 0 << x;
			}
			else
			{
				cout << x;
			}
			x += 1;
		}
		cout << endl;
	}

	return 0;
}