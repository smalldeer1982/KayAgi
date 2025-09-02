#include<bits/stdc++.h>
using namespace std;
int a[35][35]={0}, mark[35][35] = {0}, n, tmp;
struct point
{
	int x,y;
};
queue <point> q;
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> tmp;
			if (tmp)
			{
				a[i][j] = 1;
			}
		}
	}
	mark[0][0] = 1;
	q.push(point{0, 0});
	while (!q.empty())
	{
		point p = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int x = p.x + dx[i];
			int y = p.y + dy[i];
			if (x < 0 || x > n + 1 || y < 0 || y > n + 1)
			{
				continue;
			}
			if (a[x][y] == 0 && mark[x][y] == 0)
			{
				mark[x][y] = 1;
				q.push(point{x, y});
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (a[i][j] == 0 && mark[i][j] == 0)
			{
				cout << 2 << " ";
			}
			else if (a[i][j] == 1)
			{
				cout << 1 << " ";
			}
			else
			{
				cout << 0 << " ";
			}
		}
		cout << endl;
	}
	return 0;
}