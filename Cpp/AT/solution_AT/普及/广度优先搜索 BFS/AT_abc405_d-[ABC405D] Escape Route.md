# [ABC405D] Escape Route

## 题目描述

高桥去到了电影院。在电影院的地面上，每块瓷砖上都画有指向最近的安全出口的箭头。

给你一个 $H$ 行 $W$ 列的网格 $S$，其中 `.` 表示空白地面，`#` 表示不可穿过的墙，`E` 表示安全出口。

在一个空白格子，你可以用一步移动到相邻的非墙格子。两个格子相邻当且仅当它们有公共的边。

令从一个空白格子 $(i,j)$ 移动到任意一个安全出口需要的最小步数为 $d(i,j)$。\
你需要在所有空白的格子上画上箭头（指向上下左右中的一个），使得从每一个空白格子 $(i,j)$ 开始，每次向当前所在格子的箭头方向走一步，恰好 $d(i,j)$ 步后将到达安全出口。

**数据保证每一个空白格子都可以到达至少一个安全出口。**

## 说明/提示

**样例 1 解释**

在样例输出中，$d(2,3)=2$，并且沿着箭头格子 $(2,3)$ 需要恰好 $2$ 步到达安全出口。

其他所有空白格子也满足像这样的条件。

**样例 2 解释**

存在没有空白格子或安全出口的情况。

By @[chenxi2009](/user/1020063)

## 样例 #1

### 输入

```
3 4
...E
.#..
....```

### 输出

```
>>>E
^#>^
>>>^```

## 样例 #2

### 输入

```
3 2
##
##
##```

### 输出

```
##
##
##```

## 样例 #3

### 输入

```
7 20
....................
..#..#..####..#E##..
..#..#..#..#..#.....
..E###..#..#..####..
.....#..#..E.....#..
.....#..####..####..
....................```

### 输出

```
>v<<<<<>>>>>>>>v<<<<
>v#^<#^^####v^#E##vv
>v#^<#v^#>v#vv#^<<<<
>>E###vv#>v#vv####^<
>>^<<#vv#>>E<<<<<#^<
>>^<<#vv####^<####^<
>>^<<<<<>>>>^<<<<<^<```

# 题解

## 作者：Clare613 (赞：2)

## 思路：
BFS 简单题，这要理解这样一个道理：从 $a$ 到 $b$ 的最短路和从 $b$ 到 $a$ 的最短路时一样的。\
那么我们只要存储每一个出口的坐标，然后用 BFS 来算出到每个点的最短路，记得路径标向反方向，输出即可。
## code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
queue<int> xx,yy;
char a[1005][1005];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
char s[4]={'^','v','<','>'};
int n,m;
void bfs(){
	queue<int> x,y;
	while(!xx.empty()){
		x.push(xx.front());
		xx.pop();
	}
	while(!yy.empty()){
		y.push(yy.front());
		yy.pop();
	}
	while(!x.empty()){
		int tx=x.front();
		int ty=y.front();
		x.pop();
		y.pop();
		for(int i=0;i<4;i++){
			int nx=tx+dx[i];
			int ny=ty+dy[i];
			if(nx<1||nx>n||ny<1||ny>m) continue;
			if(a[nx][ny]!='.') continue;
			a[nx][ny]=s[i];
			x.push(nx);
			y.push(ny);
		}
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			if(a[i][j]=='E'){
				xx.push(i);
				yy.push(j);
			}
		}
	}
	bfs();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cout<<a[i][j];
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：littlesnake (赞：2)

- 题目大意

这道题的意思是有一个 $H \times W$ 大小的地图，每个地图可能是墙壁、路或者安全通道，设 $d_{i,j}$ 为坐标 $(i,j)$ 距离最近的安全通道的距离（不能走斜路），那么让我们在路上标记方向，已让每个 $(i,j)$ 都可以通过方向达到最近的安全通道。

- 思路

这个 $d_{i,j}$ 肯定有用，所以建立一个数组以来维护，然后我们思考一下，对于一个点 $(i-1,j)$，如果它选择向 $(i,j)$ 画箭头，那么说明 $d_{i,j}+1<d_{i-1,j}$，当然是更新之前，更新后一定要 $d_{i-1,j}=d_{i,j}+1$，首先我们要将所有的安全通道放入队列中。那么显然如果可以像上面一样更新，说明 $(i-1,j)$ 来自 $(i,j)$，那么设一个父亲数组，代表一个点的上一步在哪里，然后根据此数组修改箭头指向即可。

- 代码

```cpp
# include <bits/stdc++.h>
# define ll long long
# define N 1010

using namespace std;

int h, w;
char s[N][N];
int d[N][N], fax[N][N], fay[N][N];
bool vis[N][N];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
queue <pair <int, int> > q;

int main () {

	scanf ("%d%d", &h, &w);
	for (int i = 1; i <= h; i ++)
		for (int j = 1; j <= w; j ++)
			cin >> s[i][j];
	memset (d, 0x3f, sizeof (d));
	for (int i = 1; i <= h; i ++)
		for (int j = 1; j <= w; j ++) 
			if (s[i][j] == 'E') q.push ({i, j}), d[i][j] = 0;
	while (! q.empty ()) {
		int x = q.front ().first;
		int y = q.front ().second;
		vis[x][y] = 1;
		q.pop ();
		for (int i = 0; i < 4; i ++) {
			int xx = x + dx[i];
			int yy = y + dy[i];
			if (xx < 1 || xx > h || yy < 1 || yy > w || vis[xx][yy] || s[xx][yy] == '#')
				continue;
			if (d[x][y] + 1 < d[xx][yy]) {
				d[xx][yy] = d[x][y] + 1;
				fax[xx][yy] = x;
				fay[xx][yy] = y;
				q.push ({xx, yy}); 
			}
		}
	}
	for (int i = 1; i <= h; i ++) {
		for (int j = 1; j <= w; j ++) {
			if (s[i][j] == '.') {
				int x = fax[i][j];
				int y = fay[i][j];
				if (x == i - 1 && y == j) s[i][j] = '^';
				if (x == i + 1 && y == j) s[i][j] = 'v';
				if (x == i && y == j - 1) s[i][j] = '<';
				if (x == i && y == j + 1) s[i][j] = '>';
			}
		}
	}
	for (int i = 1; i <= h; i ++) {
		for (int j = 1; j <= w; j ++) {
			cout << s[i][j];
		}
		cout << "\n";
	}

	return 0;

}

```

---

## 作者：Jerry20231029 (赞：1)

## 思路

直接 BFS。

开始时把所有为 `E`（安全出口）的点入队，往外搜时根据方向往格子上画箭头：

- 从右边来画向右的箭头（`>`）
- 从左边来画向左的箭头（`<`）
- 从上边来画向上的箭头（`^`）
- 从下边来画向下的箭头（`v`）

已经画过箭头的点就不要在画一遍了。

## 代码

[AC 记录](https://atcoder.jp/contests/abc405/submissions/65683011)

```cpp
#include<iostream>
#include<queue>
#include<utility>
using namespace std;

const int D[2][4] = {{0,1,0,-1},{1,0,-1,0}};
const char C[4] = {'<','^','>','v'};

char a[1100][1100];

int main(){
	int n,m,x=0,y=0;
	queue<pair<int,int>> q;
	cin>>n>>m;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin>>a[i][j];
			if(a[i][j] == 'E'){
				q.push({i,j});
			}
		}
	}
	while(!q.empty()){
		x = q.front().first;
		y = q.front().second;
		q.pop();
		int _x,_y;
		for(int i = 0; i < 4; i++){
			_x = x+D[0][i];
			_y = y+D[1][i];
			if(a[_x][_y] == '.'){
				a[_x][_y] = C[i];
				q.push({_x,_y});
			}
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cout<<a[i][j];
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：XXh0919 (赞：1)

“一道题调试时间和自己犯的愚蠢程度成正比”，这句话是真的。

### 题意

给出一个 $H\times W$ 大小的网格，每个格子要么是路（`.`），要么是墙（`#`），要么是安全出口（`E`），要求输出从每一个单元格沿着上下左右走到和自己邻近的非墙单元格，直到走到安全出口的路径，若有多个输出一个即可。（感觉不太好描述，看样例理解吧）

### 解法

这题可以用 BFS 解决。令 $dis_{i,j}$ 表示任意一个安全出口到该点的距离（因为本题是 SPJ，所以是“任意一个”），则我们只需要先 BFS 一遍整张网格，找到所有的 $dis_{i,j}$，然后再倒推回去找到路径，最后输出就行了。

注：因为我没发现安全出口可以有多个，所以这代码调了我 $40$ 多分钟。。。

可以看代码理解。

### Code

```cpp
#include <bits/stdc++.h>
#define pi pair <int, int>
using namespace std;
const int N = 2000;

int n, m;
char a[N][N], ans[N][N];
int ex, ey, dis[N][N];
int dx[5] = {0, -1, 1, 0, 0},
	dy[5] = {0, 0, 0, -1, 1};
char g[5] = {' ', '^', 'v', '<', '>'};

queue <pi> q;

void bfs () {
	while (!q.empty ()) {
		int x = q.front().first, y = q.front().second;
		q.pop ();
		for (int i = 1; i <= 4; ++ i) {
			int xx = x + dx[i], yy = y + dy[i];
			if (xx > 0 && xx <= n && yy > 0 && yy <= m) {
				if (a[xx][yy] == '.' && dis[xx][yy] == -1) {
					dis[xx][yy] = dis[x][y] + 1;
					q.push (make_pair (xx, yy));
				}
			}
		}
	}
}//找到 dis

int main () {
	memset (dis, -1, sizeof dis);//原因见下
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			cin >> a[i][j];
			if (a[i][j] == 'E') {
				ex = i, ey = j;
				q.push (make_pair (ex, ey));
				dis[ex][ey] = 0;//找到一个安全出口，到自己距离是 0，所以上面要全部赋值为 -1
			}
		}
	}
  /*
  q.push (make_pair (ex, ey));
  dis[ex][ey] = 0;
  */
  //最开始我就栽在这里了
	bfs ();
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			if (a[i][j] == '.') {
				for (int k = 1; k <= 4; ++ k) {
					int xx = i + dx[k], yy = j + dy[k];
					if (xx > 0 && xx <= n && yy > 0 && yy <= m) {
						if (dis[xx][yy] != -1 && dis[xx][yy] == dis[i][j] - 1) {
							a[i][j] = g[k];
							break;
						}//倒推
					}
				}
			}
		}
	}
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			cout << a[i][j];
		}
		puts ("");
	}
	return 0;
}
```

---

## 作者：Ashankamiko (赞：1)

# 题目解析
### 题意
给一定一个 $H \times W$ 的地图，输出一个地图，满足以下条件。
- 该地图在任意一个不是 `#` 的地方，跟着箭头走最终一定可以走到 `E`。
- 向上走应该表示为 `^`。
- 向下走应该表示为 `v`。
- 向左走应该表示为 `<`。
- 向右走应该表示为 `>`。
### 思路
错误想法：遍历地图上的每一个点，尝试进行 dfs 或 bfs 向终点搜索，并每时每刻更新地图？很显然，这样的想法过于复杂且不可行。

所以我们要换一种思路，思考：每一个点最终都会走到终点，终点可以连接到任意一个点，所以我们要以终点 `E` 为开始，对 `E` 进行广度优先搜索，并且把每一次入队的 $(x,y)$ 所在的位置都改为指向拓展前的位置。
### 过程
我们以以下数据举例。
```
3 4
.#..
.E.#
#...
```
用 bfs 从 `E` 开始搜索，地图将会这样变化。
#### 第0次操作
```
.#..
.E.#
#...
```
#### 第1次操作
```
.#..
>E<#
#^..
```
#### 第2次操作
```
v#v.
>E<#
#^<.
```
#### 第3次操作
```
v#v<
>E<#
#^<<
```
这样我们就得到了一个正确、合理的地图，并且代码的实现难度不高。
## [AC 代码](https://atcoder.jp/contests/abc405/submissions/65678751)
```
#include <bits/stdc++.h>
using namespace std;
#define in cin
#define out cout
#define int long long //防止溢出
struct node {
	int x, y;
};
queue<node> q;
int n, m, dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1}; //方向数组
char maps[1005][1005];
char check(int x) { // return地图指向的方向
	if (x == 0) // x相当于方向数组的下标，x=0时应该指向当前坐标的下面，故reutrn 'v'
		return 'v';
	else if (x == 1)
		return '^';
	else if (x == 2)
		return '>';
	else
		return '<';
}
void bfs() {; //广度优先搜索
	while (!q.empty()) {
		int ux = q.front().x, uy = q.front().y;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int tx = dx[i] + ux, ty = uy + dy[i];
			if (tx >= 0 && tx < n && ty >= 0 && ty < m && maps[tx][ty] == '.')
				q.push({tx, ty}), maps[tx][ty] = check(i);
//入队并更改地图，使(tx,ty)指向(x,y)的地方
		}
	}
}
signed main() {
	in >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			in >> maps[i][j];
			if (maps[i][j] == 'E')
				q.push({i, j}); //从终点开始搜索
		}
	bfs();
	for (int i = 0; i < n; i++) { //输出地图
		for (int j = 0; j < m; j++)
			out << maps[i][j];
		out << '\n';
	}
	return 0;
}
```

---

## 作者：Clover_Lin (赞：1)

## 博客
这里：https://blog.csdn.net/ArmeriaLeap/article/details/147859748 ，欢迎点进去阅读。
## 前言
BFS 算法在 AtCoder 比赛中还是会考的，因为不常练习导致没想到，不仅错误 TLE 了很多，还影响了心态，3 发罚时后才 AC。
## 思路
首先，我们把所有位置和出口的距离算出来（用 BFS），记为 $d_{x,y}$，顺便求出离它最近的出口坐标，记为 $(X_{x,y},Y_{x,y})$。我们发现这个需要在队列里记下这个点的最近出口位置以及具体坐标。

然后我们像涟漪一样扩散着用 BFS 去求方向。找每个位置的上一步，然后判断是否是一条路上的（即最近出口相同且距离**大于**这个点的距离），如果是，那么修改方向并压入队列，否则忽略。

似乎很成功地做完了，那么有哪些易错点呢？
- 更新方向的时候一定要注意距离是否**大于**当前点的距离。注意：必须是**严格大于**，等于也不可以，因为加上这一步之后就不是最优。 
- 记得把安全疏散出口的最近出口位置设为它自己。
- 一定要用 BFS，而不是 DFS，两个函数都得用 BFS。
## 代码
AC 提交记录：[Submission #65683293](https://atcoder.jp/contests/abc405/submissions/65683293)。

TLE 提交记录：[第一发](https://atcoder.jp/contests/abc405/submissions/65675086)、[第二发](https://atcoder.jp/contests/abc405/submissions/65677726)、[第三发](https://atcoder.jp/contests/abc405/submissions/65679213)。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

int h, w, d[1010][1010];
char a[1010][1010];
pair<int, int> p[1010][1010];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
char cc[] = {'v', '^', '>', '<'};

void work()
{
	queue<pair<pair<int, int>, pair<int, int> > > q;
	for (int x = 1; x <= h; x++)
		for (int y = 1; y <= w; y++)
			if (a[x][y] == 'E')
			{
				p[x][y] = make_pair(x, y);
				q.push(make_pair(make_pair(x, y), make_pair(x, y)));
				d[x][y] = 0;
			}
	while (q.size())
	{
		int fx = q.front().first.first;
		int fy = q.front().first.second;
		int xx = q.front().second.first;
		int yy = q.front().second.second;
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int nx = fx + dx[i];
			int ny = fy + dy[i];
			if (nx < 1 || nx > h)
				continue;
			if (ny < 1 || ny > w)
				continue;
			if (a[nx][ny] != '.')
				continue;
			if (d[nx][ny] > d[fx][fy] + 1)
			{
				d[nx][ny] = d[fx][fy] + 1;
				p[nx][ny] = make_pair(xx, yy);
				q.push(make_pair(make_pair(nx, ny), make_pair(xx, yy)));
			}
		}
	}
}

void calc()
{
	queue<pair<int, int> > q;
	for (int x = 1; x <= h; x++)
		for (int y = 1; y <= w; y++)
			if (a[x][y] == 'E')
				q.push(make_pair(x, y));
	while (q.size())
	{
		int fx = q.front().first;
		int fy = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int nx = fx + dx[i];
			int ny = fy + dy[i];
			if (nx < 1 || nx > h)
				continue;
			if (ny < 1 || ny > w)
				continue;
			if (a[nx][ny] != '.')
				continue;
			if (p[nx][ny] != p[fx][fy])
				continue;
			if (d[nx][ny] <= d[fx][fy])
				continue;
			a[nx][ny] = cc[i];
			q.push(make_pair(nx, ny));
		}
	}
}

int main()
{
	cin >> h >> w;
	for (int i = 1; i <= h; i++)
		for (int j = 1; j <= w; j++)
			cin >> a[i][j];
	memset(d, 0x3f, sizeof(d));
	work();
	calc();
	for (int i = 1; i <= h; i++)
	{
		for (int j = 1; j <= w; j++)
			cout << a[i][j];
		cout << endl;
	}
	return 0;
}
```

---

## 作者：__hjyakioi__ (赞：1)

多源 `BFS` 模板题。\
众所周知，在无向图中，点 $x$ 到点 $y$ 的最短路同时也是点 $y$ 到点 $x$ 的最短路。\
考虑从所有起点（`E`）向外做 `BFS`，同时记录转移的方向即可。

多源 `BFS` 的实现：只需要在进行 `BFS` 前将所有起点加入队列即可。

[AC code](https://atcoder.jp/contests/abc405/submissions/65654345)

---

## 作者：jackzhangcn2013 (赞：0)

# 解法

首先，可以想到如果从每个点出发搜索到安全出口，其时间复杂度是远远不如从安全出口搜索到每个点的，并且两者的结果等价，不过是要将输出的方向反以下而已。

接下去我们可以发现这道题属于多源搜索，一般使用 BFS。接下去我们就可以发现只要在 BFS 过程中记录下到安全出口的距离，每次判断当前距离是否小于记录的距离，如果小于则更新距离和方向即可。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
const int N = 1005;
const int Mod = 1e9 + 7;
using namespace std;
int n, m;
char a[N][N];
int dis[N][N];
int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};
char c[4] = {'<', 'v', '>', '^'};
struct node
{
    int x, y, d;
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    queue<node> q;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            dis[i][j] = 1e18;
            cin >> a[i][j];
            if (a[i][j] == 'E')
            {
                dis[i][j] = 0;
                q.push({i, j, 0});
            }
        }
    }
    while (!q.empty())
    {
        auto [x, y, d] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (tx < 1 || tx > n || ty < 1 || ty > m)
            {
                continue;
            }
            if (a[tx][ty] == '#')
            {
                continue;
            }
            if (d + 1 >= dis[tx][ty])
            {
                continue;
            }
            dis[tx][ty] = d + 1;
            a[tx][ty] = c[i];
            q.push({tx, ty, d + 1});
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cout << a[i][j];
        }
        cout << endl;
    }
    return 0;
}
```

[提交记录](https://atcoder.jp/contests/abc405/submissions/65721821)

---

## 作者：__CrossBow_EXE__ (赞：0)

# 前言

第一次场切 D 题，发题解庆祝一下。

# 题解

数据范围较小，可以使用 BFS 求解。

可以想象这样一个情景：假设有一个超级源点（记作 $A$），它连向所有出口。那么一开始，我们肯定要将它入队。将 $A$ 入队的后果是什么呢？是它所有的邻接点也入队。也就是说，所有出口一开始都要入队。

如何输出路径呢？我们不难发现，如果对地图跑一遍 BFS，可以求出每个点离最近的出口有多远。如果有一个人站在这个点上，为了最快到达出口，肯定要去一个离这个出口更近的一个点。把这个过程抽象一下：一开始求出每个点 $(x,y)$ 到最近的出口的距离 $t_{x,y}$，接着遍历它旁边的四个点，将箭头指向 $t$ 的值比它小的点的方向即可。

# 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define endl '\n'
using namespace std;
int n,m;
const int N=1005;
char a[N][N];
bool vis[N][N];
struct pos{
	int x,y;
};
queue<pos> q;
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
char work(int fx){
	if(fx==0) return '>';
	else if(fx==1) return '<';
	else if(fx==2) return '^';
	else return 'v';
}
int t[N][N];
void bfs(){
	while(!q.empty()){
		pos f=q.front();q.pop();
		for(int i=0;i<4;i++){
			int xx=f.x+dx[i],yy=f.y+dy[i];
			if(xx>=1&&xx<=n&&yy>=1&&yy<=m&&!vis[xx][yy]){
				t[xx][yy]=t[f.x][f.y]+1;
				q.push((pos){xx,yy});
				vis[xx][yy]=1;
			}
		}
	}
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(NULL);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	memset(t,0x3f,sizeof(t));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			if(a[i][j]=='#') vis[i][j]=1;
			if(a[i][j]=='E') q.push((pos){i,j}),vis[i][j]=1,t[i][j]=0;
		}
	}
	bfs();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int minn=t[i-1][j];
			char ch='^';
			if(a[i][j]=='E'){
				cout<<'E';
				continue;
			}
			if(a[i][j]=='#'){
				cout<<'#';
				continue;
			}
			if(t[i][j+1]<minn){
				minn=t[i][j+1];
				ch='>';
			}
			if(t[i+1][j]<minn){
				minn=t[i+1][j];
				ch='v';
			}
			if(t[i][j-1]<minn){
				minn=t[i][j-1];
				ch='<';
			}
			cout<<ch;
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：残阳如血 (赞：0)

以 $\texttt{E}$ 作为起点，那么有多个起点，考虑使用多源 BFS。

那么如何记录每一个结点应该向哪个方向移动呢？我们可以在 BFS 的同时记录每一个点由哪一个点转移而来，这样就可以反推出方向了。

[Code](https://atcoder.jp/contests/abc405/submissions/65663903)。

---

## 作者：lyx128 (赞：0)

本题目考虑使用多源广度优先搜索，将所有安全出口设为起点，并计算其他非出口和非墙点到最近出口的距离。

最后可以根据周围 $4$ 个点的距离进行路径计算。我们发现于当前点与周围距离差为 $1$ 的点为本节点去往安全出口的最优方向。

代码实现如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1000;
int n,m;
char s[N+5][N+5];
int dis[N+5][N+5];
int ex[N+5],ey[N+5],tot;
int d[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
char d_t[4]={'<','^','>','v'};
char out[N+5][N+5];
struct Point{
	int x,y;
	int step;
};

void bfs(){
	queue<Point> q;
	memset(dis,0x3f,sizeof(dis));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(s[i][j]=='E'){
				dis[i][j]=0;
				q.push({i,j,0});
			}
	while(!q.empty()){
		Point u=q.front();
		q.pop();
		for(int i=0;i<4;i++){
			int dx=u.x+d[i][0];
			int dy=u.y+d[i][1];
			if(dx<1||dy<1||dx>n||dy>m||s[dx][dy]=='#')
				continue;
			if(u.step+1<dis[dx][dy]){
				dis[dx][dy]=u.step+1;
				q.push({dx,dy,dis[dx][dy]});
			}
		}
	}
	return ;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>s[i][j];
	bfs();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(s[i][j]=='#')
				cout<<"#";
			else if(s[i][j]=='E')
				cout<<"E";
			else{
				for(int k=0;k<4;k++){
					int dx=i+d[k][0];;
					int dy=j+d[k][1];
					if(dx<1||dx>n||dy<1||dy>m||s[dx][dy]=='#')
						continue;
					if(dis[dx][dy]!=dis[i][j]-1)
						continue;
					cout<<d_t[k];
					break;
				}
			}
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：player_1_Z (赞：0)

[atcoder 原题](https://atcoder.jp/contests/abc405/tasks/abc405_d)

### 思路

这题本质是求每个走廊格子到紧急出口的最短路，只不过让你把路线画到图上。因为有多个的要求最短路，所以想到可以用 bfs 做。初始把每个出口加入队列，记下位置，和走的方向，方便更新这个点，于是这题就过了。具体请看注释。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,d[1005][1005],ax[4]={0,0,1,-1},ay[4]={1,-1};
//d数组为这个点到最近出口最短路长度  
char c[1005][1005];
struct A{
	int x,y,z;
};
queue<A> q;
int main(){
	memset(d,0x3f3f3f3f,sizeof(d));
	//初始化d为极大值，防止dfs时判断错误 
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>c[i][j];
			if(c[i][j]=='E'){
				d[i][j]=-1;
				q.push({i,j,-1});
				//把出口存入队列，d赋值-1防止这个点被其它点走到 
			}
		}
	}
	while(!q.empty()){
		A x=q.front();
		q.pop();
		if(x.z==0) c[x.x][x.y]='<';
		if(x.z==1) c[x.x][x.y]='>';
		if(x.z==2) c[x.x][x.y]='^';
		if(x.z==3) c[x.x][x.y]='v';
		//根据走过来的方向更新这个点 
		for(int i=0;i<4;i++){
			int xx=x.x+ax[i],yy=x.y+ay[i];
			if(c[xx][yy]=='.'&&d[xx][yy]>d[x.x][x.y]){
				//不能走到墙上，也不能打断其它点到出口的最短路 
				d[xx][yy]=d[x.x][x.y]; 
				q.push({xx,yy,i});
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cout<<c[i][j];
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Hyh_111 (赞：0)

### 思路

以每个紧急出口为起点做 `BFS`，在到达每个点时，根据到达之前的点的方向在答案数组中写入对应的箭头。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
//#define USE_FREOPEN
//#define MUL_TEST
#define FILENAME ""
using namespace std;
constexpr int N = 5005, M = 5005;
int dx[4] = {0, 1, 0, -1}; 
int dy[4] = {1, 0, -1, 0}; 
char da[4] = {'<', '^', '>', 'v'}; //各个方向对应箭头
char mp[N][M],ans[N][M];
bool vis[N][M];
queue<pair<int, int> > q;

void solve() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> mp[i][j];
			if (mp[i][j] == 'E') { //将每个紧急出口加入队列
				q.push(make_pair(i, j));
				vis[i][j] = 1;
			}
			ans[i][j] = mp[i][j];
		}
	}
	
	while (q.size()) { //BFS
		int x = q.front().first, y = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int tx = x + dx[i], ty = y + dy[i];
			if (tx <= 0 || tx > n || ty <= 0 || ty > m || mp[tx][ty] == '#' || vis[tx][ty]) continue; //判边界、墙和已走过的位置
			q.push(make_pair(tx, ty));
			vis[tx][ty] = 1;
			ans[tx][ty] = da[i]; //写入答案
		}
	}

    //输出答案
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			cout << ans[i][j];
		cout << '\n';
	}
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	#ifdef USE_FREOPEN
		freopen(FILENAME ".in","r",stdin);
		freopen(FILENAME ".out","w",stdout);
	#endif
	int _ = 1;
	#ifdef MUL_TEST
		cin >> _;
	#endif
	while (_--)
		solve();
	_^=_;
	return 0^_^0;
}


```

---

## 作者：Nahida_Official (赞：0)

[原题 Link](https://atcoder.jp/contests/abc405/tasks/abc405_d)

## 题目大意：
给定 $h \times w$ 的地图，有若干墙壁和**若干**出口，你需要在所有的空地上加上四种箭头，分别表示上下左右四种方向，构造一种地图要求**无论你站在那个格子上**都可以通过**最短路径**走到出口。

看见最短路，看见地图，自然而然就想到用 BFS。

定义三个数组 $mp,ans,d$，分别表示输入的地图，答案地图，转换后的地图，如果输入的是空地，那么转换为数字 2，墙壁为 1，出口为 0。

再定义一个方向数组，存储四种方向，注意：你的四种方向要跟遍历过程中的方向变化**相反**，例如你向上遍历到的地图那么就要放置向下的箭头，**而且 C++中的坐标变化与日常变化不同**，以我以下代码为例，坐标 $x$ 减少 1，那么我们实际在二维数组中的变换实际上是**上移**了一位。

剩下的按照正常 BFS 写就可以了，注意将走过的空地转换为 0，以防重复遍历；而且这道题有很多出口，记得全部保存下来。

## Code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define Sangonomiya signed
#define Kokomi main()
#define Love return
#define Nahida 0
#define Forever ;
#define IOS cin.tie(nullptr)->sync_with_stdio(false)
#define cin std::cin
#define cout std::cout
const int N=1e6;
int n,w;
char mp[1005][1005];
char ans[1005][1005];
int d[1005][1005];
int dx[]={-1,1,0,0};
int dy[]={0,0,1,-1};
char ansd[]={'v','^','<','>'};
struct node{
    int x,y;
    node (int a,int b){
        x=a;
        y=b;
    }
};
std::queue<node> enter;
void bfs(){
    while(!enter.empty()){
        node now=enter.front();
        enter.pop();
        int x=now.x;
        int y=now.y;
        for(int i=0;i<4;i++){
            int nx,ny;
            nx=x+dx[i];
            ny=y+dy[i];
            if(nx>=1&&nx<=n&&ny>=1&&ny<=w&&d[nx][ny]==2){
                d[nx][ny]=d[x][y]-2;
                ans[nx][ny]=ansd[i];
                enter.push((node{nx,ny}));
            }
        }
    }
}
Sangonomiya Kokomi{
	IOS;
	cin>>n>>w;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=w;j++){
			cin>>mp[i][j];
            ans[i][j]=mp[i][j];
            d[i][j]=2;
            if(mp[i][j]=='E'){
                enter.push((node){i,j});
                d[i][j]=0;
            }else if(mp[i][j]=='#'){
                d[i][j]=1;
            }
		}
	}
    bfs();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=w;j++){
            cout<<ans[i][j];
        }
        cout<<'\n';
    }
	Love Nahida Forever;
}
```

---

## 作者：linjinkun (赞：0)

首先一看就知道要先跑[多源最短路](https://www.cnblogs.com/linjinkun/p/18751269)，然后标箭头就相当于找最短路，其实可以用 $d_{r,c} = d_{i,j}-1$ 来判断对于 $(i,j)$ 走 $(r,c)$ 这个位置是否是最短路，然后就可以确定箭头方向了。
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1005;
int d[N][N];
char a[N][N];
struct node
{
    int x;
    int y;
    int cnt;
};
int dx[] = {0,0,-1,1};
int dy[] = {-1,1,0,0};
char s[] = {'<','>','^','v'};
char b[N][N];
signed main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=n;i++)
    {
        scanf("%s",a[i]+1);
    }
    memset(d,0x3f,sizeof(d));
    queue<node>q;
    for(int i = 1;i<=n;i++)
    {
        for(int j = 1;j<=m;j++)
        {
            if(a[i][j] == 'E')
            {
                q.push({i,j,0});
                d[i][j] = 0;
            }
        }
    }
    while(q.size())
    {
        node num = q.front();
        q.pop();
        for(int i = 0;i<4;i++)
        {
            int r = num.x+dx[i];
            int c = num.y+dy[i];
            if(r>=1&&c>=1&&r<=n&&c<=m&&a[r][c]!='#'&&d[r][c]>d[num.x][num.y]+1)
            {
                d[r][c] = d[num.x][num.y]+1;
                q.push({r,c,d[r][c]});
            }
        }
    }
    for(int i = 1;i<=n;i++)
    {
        for(int j = 1;j<=m;j++)
        {
            b[i][j] = a[i][j];
            for(int k = 0;k<4;k++)
            {
                int r = i+dx[k];
                int c = j+dy[k];
                if(r>=1&&c>=1&&r<=n&&c<=m&&a[r][c]!='#'&&d[r][c] == d[i][j]-1)
                {
                    b[i][j] = s[k];
                    break;
                }
            }
            printf("%c",b[i][j]);
        }
        printf("\n");
    }
    return 0;
}
```

---

## 作者：xy_mc (赞：0)

题意很简单，就是画一个逃生路线图，很容易想到 BFS。

从每一个 `.` 去 BFS，走到紧急出口，大概率是不行的（毕竟一个电影院里走廊单元格总是要比紧急出口多的吧）。所以我们可以记录下每一个紧急出口的位置，从这些位置向外 BFS，接下来就很简单了，写模版就行，注意：如果当前走到的是走廊单元格，那么把当前单元格改为某一个方向，这一个方向是要与走的方向相反的，因为 BFS 是从紧急出口往外走，而我们要画的是从走廊向紧急出口走。

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int,int>
#define pll pair<ll,ll>
#define yes "Yes"
#define no "No"
#define debug(x) cout<<#x<<" = "<<x<<"\n"
#define rep(i,x,y) for(int i=x;i<=(y);++i)
#define per(i,x,y) for(int i=x;i>=(y);--i)

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int INF=0x3f3f3f3f;
const ll LNF=0x3f3f3f3f3f3f3f3f;
const int N=1010;

int h,w;
string mp[N];
int dis[N][N];
queue<pii> q;

int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
char dir[]=">v<^";

void solve(){
	cin>>h>>w;
	rep(i,0,h-1){
		cin>>mp[i];
	}
	rep(i,0,h-1){
		rep(j,0,w-1){
			if(mp[i][j]=='E'){
				dis[i][j]=0;
				q.push(make_pair(i,j));
			}
		}
	}
	while(!q.empty()){
		pii p=q.front();q.pop();
        rep(i,0,3){
            int xa=p.fi+dx[i];
            int ya=p.se+dy[i];
            if(xa<0||ya<0||xa>=h||ya>=w) continue;
            if(mp[xa][ya]!='.') continue;
            mp[xa][ya]=dir[i^2]; //取反
            q.push(make_pair(xa,ya));
        }
	}
	rep(i,0,h-1){
		cout<<mp[i]<<"\n";
	}
}

int main(){
	int t=1;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：Chase12345 (赞：0)

赛时没有想出 BFS。

无向图中，最短路的起点和终点显然是可以交换的，那么这里可以设所有的 `E` 为起点，直接在队列存所有 `E` 点的坐标即可。

 ```cpp
 #include <bits/stdc++.h>
 using namespace std;
 using pii = pair<int, int>;
 
 const char di[] = {'^', 'v', '<', '>'};
 const int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
 const int N = 1e3 + 5;
 int n, m, dist[N][N];
 char a[N][N];
 
 void bfs() {
 	queue <pii> q;
 	memset(dist, -1, sizeof(dist));
 	for (int i = 1; i <= n; i++)
 		for (int j = 1; j <= m; j++)
 			if (a[i][j] == 'E') {
 				q.push({i, j});
 				dist[i][j] = 0;
 			}
 	while (!q.empty()) {
 		auto [x, y] = q.front();
 		q.pop();
 		for (int d = 0; d < 4; d++) {
 			int nx = x + dx[d], ny = y + dy[d];
 			if (nx < 1 || nx > n || ny < 1 || ny > m)
 				continue;
 			if (a[nx][ny] == '#' || dist[nx][ny] != -1)
 				continue;
 			dist[nx][ny] = dist[x][y] + 1;
 			q.push({nx, ny});
 		}
 	}
 }
 
 void solve() {
 	for (int i = 1; i <= n; i++)
 		for (int j = 1; j <= m; j++) {
 			if (a[i][j] != '.' || dist[i][j] == -1)
 				continue;
 			for (int d = 0; d < 4; d++) {
 				int ni = i + dx[d], nj = j + dy[d];
 				if (ni < 1 || ni > n || nj < 1 || nj > m)
 					continue;
 				if (dist[ni][nj] == dist[i][j] - 1) {
 					a[i][j] = di[d];
 					break;
 				}
 			}
 		}
 }
 
 int main() {
 	cin >> n >> m;
 	for (int i = 1; i <= n; i++)
 		for (int j = 1; j <= m; j++)
 			cin >> a[i][j];
 	bfs();
 	solve();
 	for (int i = 1; i <= n; i++) {
 		for (int j = 1; j <= m; j++)
 			cout << a[i][j];
 		cout << '\n';
 	}
 	return 0;
 }
 ```

---

## 作者：lw393 (赞：0)

显然是一道网格上的搜索，而且要求每个点的下一步走的路，就知道一定是 BFS 了。

我们将每个起点都加入队列，再做一遍 BFS，在 BFS 中，注意需要记录这个点的前驱，这样方便于处理每个点箭头的方向。

[提交记录](https://atcoder.jp/contests/abc405/submissions/65655454)

---

## 作者：All_Wrong_Answer (赞：0)

[luogu 题目传送门](https://www.luogu.com.cn/problem/AT_abc405_d)

[AT 题目传送门](https://atcoder.jp/contests/abc405/tasks/abc405_d)

## 思路：

首先发现 ```.``` 是很多的，直接从每个 ```.``` 跑 BFS 或最短路都是不行的，那么就逆向思维，考虑从每个 ```E``` 出发跑多源，这种图显然 BFS 最合适。

那么就在开始输入时把所有 ```E``` 的坐标压进队列跑多源 BFS，遇到走过的点就退出即可。

至于记录答案，只需要记录每个点是往那一边扩展的，输出时反着输出就可以了，例如一个 ```E``` 往左走到一个 ```.```，那这个 ```.``` 输出时输出左的反方向也就是右就可以了。

## 完整代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
char m[1005][1005];
int da[1005][1005];
bool f[1005][1005];
long long x,y;
struct node{
	int mqx,mqy;
	int sl;
};
int main(){
	cin>>x>>y;
	queue<node>q;
	for(int i=0;i<=1000;i++){
		for(int j=0;j<=1000;j++) f[i][j]=true;
	}
	for(int i=1;i<=x;i++){
		for(int j=1;j<=y;j++){
			cin>>m[i][j];
			if(m[i][j]=='E')q.push((node){i,j,0});
			f[i][j]=false;
		}
	}
	while(!q.empty()){
		node mq=q.front();
		q.pop();
		
		if(mq.mqx<=0||mq.mqx>x||mq.mqy<=0||mq.mqy>y) continue;
		if(f[mq.mqx][mq.mqy]==true||m[mq.mqx][mq.mqy]=='#') continue;
		f[mq.mqx][mq.mqy]=true;
		da[mq.mqx][mq.mqy]=mq.sl;
		if(f[mq.mqx-1][mq.mqy]==false) q.push((node){mq.mqx-1,mq.mqy,1});//上 
		if(f[mq.mqx][mq.mqy-1]==false) q.push((node){mq.mqx,mq.mqy-1,2});//左 
		if(f[mq.mqx+1][mq.mqy]==false) q.push((node){mq.mqx+1,mq.mqy,3});//下 
		if(f[mq.mqx][mq.mqy+1]==false) q.push((node){mq.mqx,mq.mqy+1,4});//右 
	}
	for(int i=1;i<=x;i++){
		for(int j=1;j<=y;j++){
			if(m[i][j]=='#') cout<<"#";
			else if(m[i][j]=='E') cout<<"E";
			else{
				if(da[i][j]==1) cout<<"v";
				if(da[i][j]==2) cout<<">";
				if(da[i][j]==3) cout<<"^";
				if(da[i][j]==4) cout<<"<";
			}
		}
		cout<<endl;
	}
	return 0;
}

```

---

## 作者：xiaoyin2011 (赞：0)

## AT_abc405_d [ABC405D] 逃生路线 题解

[题目链接](https://www.luogu.com.cn/problem/AT_abc405_d)

### 题目大意

$H \times W$ 的矩阵仅有 `.`、`#` 和 `E` 组成，其中 `.` 是空地、`#` 是墙壁，而 `E` 是安全出口。

现在要求输出将原矩阵中所有 `.` 替换成 `^`（上）、`v`（下）、`<`（左）、`>`（右）的箭头表示最近的安全通道的方向。具体来说，假设 $(i, j)$ 到最近的通道距离 $dis(i, j)$，则沿着箭头行走 $dis(i, j)$ 次，总能抵达一个 `E`。

### 思路及实现

显然是一个 BFS。这里提供如何把程序写的更加有条理。

---

首先，对于 BFS 部分。可以在输入时记录 `E` 的位置，加入到 `vector<pair<int, int> >` 的同时可以记录其序号，标记其顺序以区别。

然后，在对于 BFS 初始值时，可以遍历这个 `vector` 并依次加入。

BFS 过程，可以把多个变量放入同一个 `queue` 中，无论是使用 `tuple` 还是结构体。这里，我选择利用 $O(HW)$ 的 BFS 求出每个 $(i, j)$ 的最短逃生距离 $dis(i, j)$ 和最近出口的序号 $dest(i, j)$。

BFS 过程中，可以用 `memset` 把地图刷成全 `#` 再以 1-base 输入，此时不必考虑出界，直接判断 `#` 即可。

BFS 可以选择用常量数组，如下面程序中的 `dx`、`dy` 记录偏移量，从而在循环中找到本格的四连通格子。同样的，八连通和马走日也可以类似的制作。本题尤甚，可以如下定义常量字符数组 `dir`，顺便把方向转化为箭头字符。

另外，本题中 BFS 要把所有出口同时加入并运行，否则一个一个复杂度可能达到 $O(H^2W^2)$。这里，可以通过 `vis`，也可以通过比较 `dis`，因为 BFS 总是先填充并标记先来的，所以 `vis` 标了的，`dis` 不会更大。

---

然后是具体箭头路径的生成。有些人会选择 BFS 时记录，这样字符串处理会坨很大一团。

这里，我们会发现，对于点 $(i, j)$ 和 $dest(i, j)$，其周围必然有一个点的 $dest$ 和它相同，$dis$ 比它小，否则，这就不是 BFS 会形成的图形。同时由于可能多个答案，我们从周围任一不是墙并且起源相同距离更短的点选一个即可，这样，就一定会连成原来 BFS 的顺序。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
const char dir[4] = {'^', 'v', '<', '>'};
int H, W;
char mp[1005][1005];
vector<pair<int, int> > exi;
int dis[1005][1005], dest[1005][1005];
bool vis[1005][1005];
queue<tuple<int, int, int, int> > q;
void add(int sx, int sy, int sid)
{
	q.push({sx, sy, 0, sid});
	vis[sx][sy] = 1;
	dis[sx][sy] = 0;
	dest[sx][sy] = sid;
}
void fill()
{
	while (!q.empty())
	{
		auto now = q.front(); q.pop();
		for (int i = 0; i < 4; i++)
		{
			int nx = get<0>(now) + dx[i], ny = get<1>(now) + dy[i], nd = get<2>(now) + 1, sid = get<3>(now);
			if (mp[nx][ny] == '#' || vis[nx][ny] || dis[nx][ny] <= nd) continue;
			q.push({nx, ny, nd, sid});
			vis[nx][ny] = 1;
			dis[nx][ny] = nd;
			dest[nx][ny] = sid;
		}
	}
} 
int main()
{
	memset(mp, '#', sizeof(mp));
	memset(vis, 0, sizeof(vis));
	memset(dis, 0x3f, sizeof(dis));
	memset(dest, 0x80, sizeof(dest));
	scanf("%d%d", &H, &W);
	for (int i = 1; i <= H; i++)
		for (int j = 1; j <= W; j++)
		{
			scanf("\n%c", &mp[i][j]);
			if (mp[i][j] == 'E')
				exi.push_back({i, j});
		}
	for (int i = 0; i < exi.size(); i++)
		add(exi[i].first, exi[i].second, i);
	fill();
	for (int i = 1; i <= H; i++)
		for (int j = 1; j <= W; j++)
			if (mp[i][j] == '.')
				for (int k = 0; k < 4; k++)
				{
					int nx = i + dx[k], ny = j + dy[k];
					if (mp[nx][ny] == '#' || dis[nx][ny] >= dis[i][j]) continue;
					if (dest[nx][ny] != dest[i][j]) continue;
					mp[i][j] = dir[k]; break;
				}
	for (int i = 1; i <= H; i++)
	{
		for (int j = 1; j <= W; j++)
			printf("%c", mp[i][j]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：LittleAcbg (赞：0)

## 题意简述

给定一个图，图上有空地、墙和安全出口。对每个空地，为其赋予一个方向，使得从任意空地开始，不断向此空地对应方向移动（不能穿过墙），可以到达距离起点最近的安全出口，且走的路线是最短路。

## 解法分析

考虑求 $(i,j)$ 到最近的安全出口的最短距离 $d(i,j)$，这可以通过一次 BFS 得到。

考虑 BFS 过程，当从一个点 $(x,y)$ 走到一个未访问过的点 $(x',y')$ 时，我们会进行 $d(x',y')\leftarrow d(x,y)+1$ 这一操作以记录 $(x',y')$ 到最近安全出口的最短距离。

在这个时候，我们可以将 $(x',y')$ 这一位置的方向设置为指向 $(x,y)$。可以发现这样做能够保证其移动到最近安全出口时走的是最短路。

## 代码实现

一些细节能够帮助我们的代码更简单：

- 我们只需要知道每个空位的方向，而这可以在 BFS 过程中完成，不需要记录 $d(i,j)$。
- 对每个空位，如果其方向已经确定，就说明它已经被访问过，否则就还没有被访问。因此，我们在 BFS 时不需要使用 `vst` 记录每个位置是否访问过。

代码并不困难：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1009;
const int dx[] = {1,-1,0, 0};
const int dy[] = {0, 0,1,-1};
const char dc[] = "^v<>";
int n,m;
char mp[N][N];
struct Node {int x,y;};
void bfs()
{
    queue<Node> q;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j)
        if (mp[i][j] == 'E') q.push((Node){i, j});
    while (q.size())
    {
        int x = q.front().x,y = q.front().y; q.pop();
        for (int k = 0; k < 4; ++k)
        {
            int nx = x + dx[k],ny = y + dy[k];
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            if (mp[nx][ny] != '.') continue;
            q.push((Node){nx, ny});
            mp[nx][ny] = dc[k];
        }
    }
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) cin >> mp[i][j];
    bfs();
    for (int i = 1; i <= n; ++i,puts("")) for (int j = 1; j <= m; ++j) putchar(mp[i][j]);
    return 0;
}
```

---

