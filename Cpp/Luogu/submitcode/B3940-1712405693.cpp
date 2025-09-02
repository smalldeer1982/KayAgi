#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n, a[50][50], x, y;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			a[i][j] = 0;
		}
	}
	a[1][(n + 1) / 2] = 1;
	x = 1;
	y = (n + 1) / 2;
	for (int i = 2; i <= n * n; i++)
	{
		if (x == 1 && y != n)
		{
			a[n][y + 1] = i;
			x = n;
			y += 1;
		}
		else if (x != 1 && y == n)
		{
			a[x - 1][1] = i;
			x -= 1;
			y = 1;
		}
		else if (x == 1 && y == n)
		{
			a[x + 1][y] = i;
			x += 1;
		}
		else if (x != 1 && y != n && a[x - 1][y + 1] == 0)
		{
			a[x - 1][y + 1] = i;
			x -= 1;
			y += 1;
		}
		else
		{
			a[x + 1][y] = i;
			x += 1;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}