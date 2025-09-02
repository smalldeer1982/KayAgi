#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n, x = 1;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		for (int j = (n + 1 - i); j > 0; j--)
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