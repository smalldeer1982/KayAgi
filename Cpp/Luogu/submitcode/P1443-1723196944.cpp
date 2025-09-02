#include<bits/stdc++.h>
using namespace std;
struct point
{
	int x, y;
};
int main()
{
	int n, m, x0, y0, ans[402][402], dx[8] = {-1, -2, -2, -1, 1, 2, 2, 1}, dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
	queue<point>q;
	memset(ans, -1, sizeof(ans));
	cin >> n >> m >> x0 >> y0;
	ans[x0][y0] = 0;
	point tp = {x0, y0}, p;
	q.push(tp);
	while (!q.empty())
	{
		tp = q.front();
		q.pop();
		for (int i = 0; i < 8; i++)
		{
			int x = dx[i] + tp.x;
			int y = dy[i] + tp.y;
			if (x < 1 || x > n || y < 1 || y > m || ans[x][y] != -1)
			{
				continue;
			}
			ans[x][y] = ans[tp.x][tp.y] + 1;
			p = {x, y};
			q.push(p);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			cout << ans[i][j] << "    ";
		}
		cout << endl;
	}
	return 0;
}