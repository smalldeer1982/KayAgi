#include<bits/stdc++.h>
using namespace std;
int main()
{
	long n, a[1005], sum = 0;
	string b[1005];
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i] >> b[i];
	}
	for (int i = 0; i < n; i++)
	{
		sum = 0;
		for (int j = b[i].length() - 1; j >= 0; j--)
		{
			if (b[i][j] >= 'A' && b[i][j] <= 'Z')
			{
				sum += (b[i][j] - '7') * pow(a[i], (b[i].length() - j - 1));
			}
			else
			{
//				cout << b[i][j] - '0' << endl;
//				cout << a[i] << endl;
//				cout << (b[i].length() - j - 1) << endl << endl;
				sum += (b[i][j] - '0') * pow(a[i], (b[i].length() - j - 1));
			}
		}
		cout << sum << endl;
	}
	return 0;
}