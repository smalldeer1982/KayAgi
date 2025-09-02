#include<bits/stdc++.h>
using namespace std;
int n, x, k;
int main()
{
	cin >> n;
	for (int i = 100; i >= 1; i--)
	{
		for (int j = 1; j < n; j++)
		{
			if ((7 * i + 21 * j) * 52 == n)
			{
				x = i;
				k = j;
				cout << x << endl;
				cout << k << endl;
				return 0;
			}
		}
	}
	return 0;
}