#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n, max = 0, min = 1001, a[1005], y=0, z=0;
	double x=0;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++)
	{
		if (a[i] > max)
		{
			max = a[i];
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (a[i] < min)
		{
			min = a[i];
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (a[i] == max)
		{
			if (y != 1)
			{
				a[i] = 0;
				y=1;
			}
		}
		else if (a[i] == min)
		{
			if(z!=1)
			{
				a[i] = 0;	
				z=1;
			}	
		}
	}
	for (int i = 1; i <= n; i++)
	{
		x += a[i];
	}
	x = x / (n - 2);
	printf("%.2f\n", x);
	return 0;
}