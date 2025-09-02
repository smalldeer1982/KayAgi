#include <bits/stdc++.h>
using namespace std;
int main()
{
	int a[100], b[50], x, y, z, sum = 0;
	cin >> x >> y >> z;
	for (int i = 1; i <= 40; i++)
	{
		a[i] = 0;
		b[i] = i;
	}
	for (int i = 1; i <= x; i++)
	{
		for (int j = 1; j <= y; j++)
		{
			for (int k = 1; k <= z; k++)
			{
				sum = i + j + k;
				a[sum] += 1;
			}
		}
	}
	int maxCount = 0, result = 0;
	for (int i = 1; i <= x + y + z; i++) 
	{
		if (a[i] > maxCount) 
		{
			maxCount = a[i];
			result = i;
		}
	}
	cout << result;
	return 0;
}