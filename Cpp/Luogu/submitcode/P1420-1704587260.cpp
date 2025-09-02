#include <bits/stdc++.h>
using namespace std;
int main()
{
	int a[10005], n, maxx = 0, x = 0;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++)
	{
		if (a[i] == a[i + 1] - 1)
		{
			x += 1;
		}
		else
		{
			x+=1;
			if (x > maxx)
			{
				maxx = x;
			}
			x = 0;
		}
	}
	cout << maxx;
	return 0;
}