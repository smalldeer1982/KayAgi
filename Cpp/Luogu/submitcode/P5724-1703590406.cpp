#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n, max = 0, min = 1001, a[1005];
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
	cout<<max-min;
	return 0;
}