#include<bits/stdc++.h>
using namespace std;
int a, b, m, n, sum = 0, d = 2, t;
int main()
{
	cin >> a >> b >> m >> n;
	sum = a + b;
	while (d < n)
	{
		t = a + b;
		a = b;
		b = t;
		sum += b;
		if (t > m)
		{
			break;
		}
		else if (t == m)
		{
			break;
		}
		d += 1;
	}
	cout << sum;
	return 0;
}