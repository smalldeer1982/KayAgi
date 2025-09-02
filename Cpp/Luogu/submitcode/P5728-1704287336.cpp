#include<iostream>
using namespace std;
int main()
{
	int n, a[1005], b[1005], c[1005], sum = 0;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		cin >> b[i];
		cin >> c[i];
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j < i; j++)
		{
			if (abs(a[i]+b[i]+c[i]-(a[j]+b[j]+c[j]))<=10&&abs(a[i]-a[j])<=5&&abs(b[i]-b[j])<=5&&abs(c[i]-c[j])<=5)
			{
				sum+=1;
			}
		}
	}
	cout<<sum;
	return 0;
}