#include<bits/stdc++.h>
using namespace std;
int ans = -1, n, a[50], b[50][50], f[50], p[50], k;
void cc(int k)
{
	if (p[k] == 0) 
	{
		cout << k << " ";
		return;
	}
	cc(p[k]);
	cout << k << " ";
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) 
	{
		cin >> a[i];
	}
	for (int i = 1; i <= n - 1; i++) 
	{
		for (int j = i + 1; j <= n; j++) 
		{
			cin >> b[i][j];
		}
	}
	for (int i = 1; i <= n; i++) 
	{
		f[i] = a[i];
		for (int j = 1; j <= n; j++) 
		{
			if (b[j][i]) 
			{
				if (f[i] < f[j] + a[i]) 
				{
					f[i] = f[j] + a[i];
					p[i] = j;
				}
			}
			if (ans < f[i]) 
			{
				ans = f[i];
				k = i;
			}
		}
	}
	cc(k);
	cout << endl << ans << endl;
	return 0;
}