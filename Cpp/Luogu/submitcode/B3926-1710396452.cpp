#include <bits/stdc++.h>
using namespace std;
int main()
{
	string b[1005], c[1005], d[1005],e[1005];
	int a[1005],n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i] >> b[i] >> c[i] >> d[i] >> e[i];
	}
	for (int i = 1; i <= n; i++)
	{
		if (b[i] == "km" && e[i] == "m")
		{
			d[i] = to_string(a[i] * 1000);
		}
		else if (b[i] == "km" && e[i] == "mm")
		{
			d[i] = to_string(a[i] * 1000000);
		}
		else if (b[i] == "m" && e[i] == "mm")
		{
			d[i] = to_string(a[i] * 1000);
		}
		else if (b[i] == "kg" && e[i] == "g")
		{
			d[i] = to_string(a[i] * 1000);
		}
		else if (b[i] == "kg" && e[i] == "mg")
		{
			d[i] = to_string(a[i] * 1000000);
		}
		else if (b[i] == "g" && e[i] == "mg")
		{
			d[i] = to_string(a[i] * 1000);
		}
		cout<<a[i]<<" "<<b[i]<<" "<<c[i]<<" "<<d[i]<<" "<<e[i]<<endl;
	}
	return 0;
}