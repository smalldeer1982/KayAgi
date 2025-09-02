#include <bits/stdc++.h>
using namespace std;
int main()
{
	int a[200][200], n, m, k, x, y, sum = 0;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			a[i][j] = 0;
		}
	}
	for (int i = 1; i <= m; i++)
	{
		cin >> x >> y;
		a[x][y] = 1, a[x - 2][y] = 1, a[x - 1][y] = 1, a[x + 1][y] = 1, a[x + 2][y] = 1, a[x][y - 1] = 1, a[x][y - 2] = 1, a[x][y + 1] = 1, a[x][y + 2] = 1, a[x - 1][y - 1] = 1, a[x + 1][y - 1] = 1, a[x - 1][y + 1] = 1, a[x + 1][y + 1] = 1;
	}
	for (int i = 1; i <= k; i++)
	{
		if(k==0)
		{
			break;
		}
		cin >> x >> y;
		for (int j = x - 2; j <= x + 2; j++)
		{
			for (int l = y - 2; l <= y + 2; l++)
			{
				a[j][l] = 1;
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if(a[i][j]==0)
			{
				sum+=1;
			}
		}
	}
	cout<<sum;
	return 0;
}