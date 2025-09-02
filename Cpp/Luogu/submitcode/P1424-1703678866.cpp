#include<iostream>
using namespace std;
int main() {
	int x, n, sum = 0;
	cin >> x >> n;
	for (int i = 1; i <= n; i++)
	{
		if (x > 7)
		{
			x = 1;
		}
		if (x <= 5)
		{
			sum += 250;
		}
		else
		{
			sum += 0;
		}
		x += 1;
	}
	cout << sum;
	return 0;
}