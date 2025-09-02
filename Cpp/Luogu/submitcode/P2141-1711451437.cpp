#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n, a[105], sum = 0, x[105] = {0};
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = n - 1; j > i; j--)
		{
			for (int k = 0; k < n; k++)
			{
				if (k == i || k == j || x[k])
				{
					continue;
				}
				if (a[i] + a[j] == a[k])
				{
					sum += 1;
					x[k] = 1;
				}

			}
		}
	}
	cout << sum;
	return 0;
}