#include <iostream>
using namespace std;
int main() {
	int n, x, sum = 0;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		string str = to_string(i);
		for (char c : str)
		{
			x = (int)c - '0';
			if (x == 0 || x == 1 || x == 2 || x == 9)
			{
				sum += i;
				break;
			}
		}
	}
	cout << sum;
	return 0;
}