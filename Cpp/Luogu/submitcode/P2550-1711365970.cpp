#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n, a[10], b[10], c[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, sum = 7;
	cin >> n;
	for (int i = 0; i < 7; i++)
	{
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++)
	{
		sum = 7;
		for (int j = 0; j < 7; j++)
		{
			cin >> b[j];
			for (int k = 0; k < 7; k++)
			{
				if (b[j] == a[k])
				{
					sum -= 1;
					break;
				}
			}
		}
		if (sum != 7)
		{
			c[sum] += 1;
		}
	}
	for (int i = 0; i < 7; i++)
	{
		cout<<c[i]<<" ";
	}
	return 0;
}