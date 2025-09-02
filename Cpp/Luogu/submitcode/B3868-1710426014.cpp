#include <bits/stdc++.h>
using namespace std;

int main()
{
	char a[1005];
	int n, b = 1, c = 1, d = 1, e = 1;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a;
		b = 1, c = 1, d = 1, e = 1;
		for (int j = 0; a[j] != '\0'; j++)
		{
			if (a[j] >= '2')
			{
				b = 0;
			}
			if (a[j] >= '8')
			{
				c = 0;
			}
			if (a[j] > '9')
			{
				d = 0;
			}
			if (a[j] > 'F')
			{
				e = 0;
			}
		}
		cout << b << " " << c << " " << d << " " << e << endl;
	}
	return 0;
}