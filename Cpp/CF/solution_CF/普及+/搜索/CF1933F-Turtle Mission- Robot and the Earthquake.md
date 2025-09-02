# Turtle Mission: Robot and the Earthquake

## 题目描述

The world is a grid with $ n $ rows and $ m $ columns. The rows are numbered $ 0, 1, \ldots, n-1 $ , while the columns are numbered $ 0, 1, \ldots, m-1 $ . In this world, the columns are cyclic (i.e. the top and the bottom cells in each column are adjacent). The cell on the $ i $ -th row and the $ j $ -th column ( $ 0 \le i < n, 0 \le j < m $ ) is denoted as $ (i,j) $ .

At time $ 0 $ , the cell $ (i,j) $ (where $ 0 \le i < n, 0 \le j < m $ ) contains either a rock or nothing. The state of cell $ (i,j) $ can be described using the integer $ a_{i,j} $ :

- If $ a_{i,j} = 1 $ , there is a rock at $ (i,j) $ .
- If $ a_{i,j} = 0 $ , there is nothing at $ (i,j) $ .

As a result of aftershocks from the earthquake, the columns follow tectonic plate movements: each column moves cyclically upwards at a velocity of $ 1 $ cell per unit of time. Formally, for some $ 0 \le i < n, 0 \le j < m $ , if $ (i,j) $ contains a rock at the moment, it will move from $ (i, j) $ to $ (i - 1, j) $ (or to $ (n - 1, j) $ if $ i=0 $ ).

The robot called RT is initially positioned at $ (0,0) $ . It has to go to $ (n-1,m-1) $ to carry out an earthquake rescue operation (to the bottom rightmost cell). The earthquake doesn't change the position of the robot, they only change the position of rocks in the world.

Let RT's current position be $ (x,y) $ ( $ 0 \le x < n, 0 \le y < m $ ), it can perform the following operations:

- Go one cell cyclically upwards, i.e. from $ (x,y) $ to $ ((x+n-1) \bmod n, y) $ using $ 1 $ unit of time.
- Go one cell cyclically downwards, i.e. $ (x,y) $ to $ ((x+1) \bmod n, y) $ using $ 1 $ unit of time.
- Go one cell to the right, i.e. $ (x,y) $ to $ (x, y+1) $ using $ 1 $ unit of time. (RT may perform this operation only if $ y < m-1 $ .)

Note that RT cannot go left using the operations nor can he stay at a position.

Unfortunately, RT will explode upon colliding with a rock. As such, when RT is at $ (x,y) $ and there is a rock at $ ((x+1) \bmod n, y) $ or $ ((x+2) \bmod n, y) $ , RT cannot move down or it will be hit by the rock.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1933F/e6c2eefb52b92661f33f40565f8703b698e45850.png)Similarly, if $ y+1 < m $ and there is a rock at $ ((x+1) \bmod n, y+1) $ , RT cannot move right or it will be hit by the rock.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1933F/fb10a6984c9e2fa62a504f01d0bebb40cf60e8a4.png)However, it is worth noting that if there is a rock at $ (x \bmod n, y+1) $ and $ ((x+1) \bmod n, y) $ , RT can still move right safely.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1933F/7a53bd04bd2915c103d70abe831abd04969b7ef5.png)Find the minimum amount of time RT needs to reach $ (n-1,m-1) $ without colliding with any rocks. If it is impossible to do so, output $ -1 $ .

## 说明/提示

Visual explanation of the first test case in the example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1933F/765b33690d3fb490f30273f591cef774fd4d800f.png)

## 样例 #1

### 输入

```
6
4 5
0 1 0 0 0
0 0 1 0 0
1 0 1 1 0
0 0 0 0 0
3 3
0 0 0
1 0 0
0 0 0
5 3
0 0 0
0 0 0
1 0 0
0 0 0
1 0 0
3 7
0 0 1 0 0 1 0
1 0 1 0 1 0 0
0 1 0 0 0 0 0
3 4
0 1 0 0
1 0 0 0
0 1 1 0
5 5
0 0 0 0 0
0 1 0 1 0
0 1 0 1 0
0 1 0 1 0
0 0 0 1 0```

### 输出

```
7
3
3
8
-1
12```

## 样例 #2

### 输入

```
6
3 3
0 0 0
0 0 0
0 0 0
4 3
0 1 0
1 0 0
0 1 0
1 0 0
4 3
0 1 0
0 1 0
0 1 0
0 1 0
3 3
0 0 0
1 1 0
0 0 0
3 3
0 1 0
0 0 0
0 1 0
5 5
0 0 0 0 0
0 1 1 0 0
0 1 1 0 0
0 0 0 0 0
0 0 1 0 0```

### 输出

```
3
3
-1
-1
3
8```

# 题解

## 作者：Swirl (赞：8)

# 思路简述

如果让石子一直移动的话，需要更改的地方太多，不妨把所有的石头都**看作是静止的**，那么 Robot 和终点每次都向下一格。

那么 Robot 的三种运动就分别看作：

- 向下两格
- 静止
- 向右一格，向下一格

由于静止在到达最后一列之前没有意义，故我们可以使用 BFS
搜索剩下两种情况。

最后在 $m - 1$ 列的时候计算到终点的步数，两种情况：

- 静止，那么终点相较于 Robot 向下一格
- 向下两格，那么终点相较于 Robot 向上一格

注意事项：

1. 稍微卡卡常（本人因此超时了一发）；
2. 多测清空；
3. 记得取模，并且要注意边界情况；

那么就可以写出代码：

[code](https://codeforces.com/contest/1933/submission/258803928)。

---

## 作者：wsx248 (赞：5)

### 题目大意：
给出一个 $n\times m$ 的矩阵，矩阵中有障碍物的地方设置为 $1$，没有障碍物的地方为 $0$，保证第 $m-1$ 列一定没有障碍物。

初始时人在 $(0,0)$ 位置，要前往 $(n-1, m-1)$。每一秒钟人可以向右、向上、向下移动一格，并且可以循环移动（即第 $n-1$ 行可以向下移动到第 $0$ 行，第 $0$ 行可以向上移动到第 $n-1$ 行）。

矩阵中的所有格子每秒钟都会向上整体移动一格，同样也可以循环移动。

人不能碰到障碍物，求最少需要多少秒才能从 $(0,0)$ 移动到 $(n-1,m-1)$，如果无法做到输出 $-1$。

### 题解
模拟一下样例可以发现，如果将所有的格子固定不动，那么向右走等价于向右下走、向下走等价于向下走 $2$ 步，而向上走只有在最后一列才有价值。

直接考虑广搜即可，每次只扩展右下角、向下 $2$ 步的情况。当走到了最后一行时，先计算此时的终点 $(n-1,m-1)$ 位于第几行，然后算需要多少时间。

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<set>
#include<map>
#include<queue>
using namespace std;
const int N = 1e3+5;
int n, m, k;
int g[N][N];
int dis[N][N];
struct node{
	int x, y;
};
void bfs(int x, int y)
{
	queue<node> q;
	q.push({x, y});
	dis[x][y] = 0;
	int ans = 1e9;
	
	while(q.size())
	{
		int tx = q.front().x, ty = q.front().y;
		q.pop();
		
		if(ty==m-1)
		{
			int ed = (n - 1 + dis[tx][ty]) % n;	//当前终点所在行 
			int tmp = (ed - tx + n) % n;	//从当前行向下到达终点行 
			int tmp2 = (tx - ed + n) % n;	//从当前行向上到达终点行 
			ans = min(ans, dis[tx][ty]+min(tmp, tmp2));
		}
		
		int nx, ny;
		
		//向右走 
		nx = (tx + 1) % n;
		ny = ty + 1;
		if(ny<=m-1 && g[nx][ny]==0 && dis[nx][ny]==-1)
		{
			dis[nx][ny] = dis[tx][ty] + 1;
			q.push({nx, ny});
		}
      
		nx = (tx + 2) % n;
		ny = ty;
		if(g[(tx+1)%n][ty]==0 && g[nx][ny]==0 && dis[nx][ny]==-1)
		{
			dis[nx][ny] = dis[tx][ty] + 1;
			q.push({nx, ny});	
		}
	}
	
	if(ans==1e9)
		puts("-1");
	else
		cout<<ans<<endl;
}

int main()
{
	int _;
	cin>>_;
	while(_--)
	{
		cin>>n>>m;
		memset(dis, 0, sizeof dis);
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				cin>>g[i][j], dis[i][j] = -1;
		bfs(0, 0);
	}
	return 0;
}
```

---

## 作者：__YSC__ (赞：4)

# 题目描述

在一个 $N \times M$ 的网格图中（$0$ 下标），每一列都是循环的，即 $(i,j)$ 的下方是 $((i+1) \operatorname{mod} N,j)$。在每一格中要么是空的要么是石头。在每一秒，所有石头都会向上移动一格，即从 $(i,j)$ 到 $((i + n - 1) \operatorname{mod} N,j)$。一开始在 $(0,0)$ 位置有一个机器人，每一秒，它可以往上下右走一格（不能不移动）。求机器人最少要多少秒可以到达 $(N-1,M-1)$。**保证最后一列没有石头。**

# 思路

由于每秒钟让石头都移动太麻烦了，所以我们可以换一个参考系：让石头不动，往下走转化为往下走两格，往上变为不动，往右变成往右下走。由于不移动没有作用，所以不需要这种转移。可是这样就会导致终点每秒钟往下走一格。所以我们可以先 BFS 一遍，但是不做最后一列（只求不做）。注意到最后一列没有石头，所以可以直接计算出答案为 $\min \limits_{i=0}^{N-1}\{ dist_{M-1,i} + \min((x - (n-1+dist_{M-1,i})\operatorname{mod} N+N)\operatorname{mod} N,((n-1+dist_{M-1,i})\operatorname{mod} N -x+N)\operatorname{mod} N)\}$。

时间复杂度 $O(TNM)$，空间复杂度 $O(NM)$。

## 细节

无。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1001, INF = MAXN * MAXN + 1;

struct Node {
  int x, y;
};

int t, n, m, dist[MAXN][MAXN], ans = INF;
bool a[MAXN][MAXN], vis[MAXN][MAXN];
queue<Node> que;

void Record(int x, int y, int dis) {
  if(vis[x][y]) {
    return;
  }
  vis[x][y] = 1;
  dist[x][y] = dis;
  if(y == m - 1) {
    return;
  }
  que.push({x, y});
}

void bfs() {
  Record(0, 0, 0);
  while(!que.empty()) {
    auto [x, y] = que.front();
    int dis = dist[x][y];
    que.pop();
    if(!a[(x + 1) % n][y] && !a[(x + 2) % n][y]) {
      Record((x + 2) % n, y, dis + 1);
    }
    if(y < m - 1 && !a[(x + 1) % n][y + 1]) {
      Record((x + 1) % n, y + 1, dis + 1);
    }
  }
}

int Calc(int x, int s) {
  int y = (n - 1 + s) % n;
  return s + min((x - y + n) % n, (y - x + n) % n);
}

void Solve() {
  cin >> n >> m;
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < m; ++j) {
      cin >> a[i][j];
    }
  }
  fill(vis[0], vis[n - 1] + m, 0);
  fill(dist[0], dist[n - 1] + m, INF);
  bfs();
  ans = INF;
  for(int i = 0; i < n; ++i) {
    ans = min(ans, Calc(i, dist[i][m - 1]));
  }
  cout << (ans == INF ? -1 : ans) << "\n";
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> t;
  while(t--) {
    Solve();
  }
  return 0;
}

```

---

## 作者：Little_Cabbage (赞：2)

### 题目大意

给你一张地图，机器人在左上角，目标在右下角，地图中有一些石头，每一个单位时间石头向上移动一格。机器人可以往上、下、右三个方向移动，求机器人走到终点的最短时间。

### 思路

石头肯定不能像题目描述一样动的。

可以考虑让石头不动，机器人相对石头运动。

设机器人当前的位置是 $(i, j)$。

- 上：$(i, j)$.

- 下：$(i + 2, j)$

- 右：$(i + 1, j + 1)$

由于向上走相当于不动，所以只用考虑向下走和向右走。

然后宽搜就可以了。

### 代码

```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
#define int long long
#define ll __int128
#define ldb long double
#define db double
#define bl bool
#define endl '\n'
#define PII pair<int, int>
#define PIII pair<int, PII>
#define p_q priority_queue
#define n_m unordered_map
#define il inline
#define re register
#define ve vector
#define bs bitset
#define m_p make_pair
using namespace std;

namespace OI {
	template <typename T>
	il T read() {
		T x = 0, f = 1;
		int ch = getchar();
		while (!isdigit(ch)) {
			if (ch == '-') f = -1;
			ch = getchar();
		}
		while (isdigit(ch)) {
			x = (x << 3) + (x << 1) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	template <typename TE>
	il void write(TE x) {
		if (x < 0) {
			x = -x;
			putchar('-');
		}
		TE sta[35];
		int top = 0;
		do {
			sta[top++] = x % 10, x /= 10;
		} while (x);
		while (top) putchar(sta[--top] + '0');
	}
	il string read_with_string() {
		string s = "";
		char ch = getchar();
		while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
			s += ch;
			ch = getchar();
		}
		return s;
	}
	il void write_with_string(string s) {
		for (int i = 0; i < s.size(); i++) putchar(s[i]);
	}
}
using namespace OI;

//#define fre 1
//#define IOS 1
#define multitest 1

const int N = 1e3 + 10;
const int M = 4e5 + 10;
const int inf = 1e12;

int n, m, a[N][N];
bl vis[N][N];
int dp[N][N];
queue<PII> q;
int ans = inf;

il void Solve() {
	ans = inf;
	n = read<int>(), m = read<int>();
	for (re int i = 0; i < n; i++)
		for (re int j = 0; j < m; j++) {
			a[i][j] = read<int>();
			vis[i][j] = 0;
			dp[i][j] = inf;
		}
	q.push(m_p(0, 0));
	vis[0][0] = 1;
	dp[0][0] = 0;
	while (!q.empty()) {
		PII t = q.front();
		q.pop();
		int x = t.first;
		int y = t.second;
		if (y == m - 1) {
			int now = (n + dp[x][y] - 1) % n;
			ans = min(ans, min((now - x + n) % n, (x - now + n) % n) + dp[x][y]);
			continue;
		}
		int i, j;
		i = (x + 2) % n;
		if (a[(x + 1) % n][y] == 0 && a[i][y] == 0 && !vis[i][y]) {
			q.push(m_p(i, y));
			dp[i][y] = min(dp[i][y], dp[x][y] + 1);
			vis[i][y] = 1;
		}
		i = (x + 1) % n, j = (y + 1) % m;
		if (a[i][j] == 0 && !vis[i][j]) {
			q.push(m_p(i, j));
			dp[i][j] = min(dp[i][j], dp[x][y] + 1);
			vis[i][j] = 1;
		}
	}
	cout << (ans == inf ? -1 : ans) << endl;
}

signed main() {
	int T;
#ifdef IOS
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#endif
#ifdef fre
	freopen(".in", "r", stdin);
	freopen(".ans", "w", stdout);
#endif
#ifdef multitest
	cin >> T;
#else
	T = 1;
#endif
	while (T--) Solve();
	return 0;
}
/*

*/
```

[`AC` 记录](https://www.luogu.com.cn/record/163995144)。

### 注意

一定要在更新队列元素的时候把当前移动到的点标记，这样可以避免一些坐标的重复计算，不然第 $9$ 个点会 `TLE`。

---

## 作者：yuhong056 (赞：0)

# 题解：CF1933F Turtle Mission: Robot and the E
本蒟蒻提供一个 dp 题解。
## 思路
这道题，如果暴力将每个石头移动的话明显不现实。

因此，我们将其改变为机器人和终点的移动：
- 机器人上移 $\to$ 终点下移，机器人不变。
- 机器人下移 $\to$ 终点下移，机器人下移两格。
- 机器人右移 $\to$ 终点下移，机器人下移一格且右移一格。
## dp 状态
很明显，$dp_{x, y}$ 代表走到 $(x, y)$ 点所需的最小步数。
## dp 转移
两种：
1. $dp_{x, y} = dp_{x - 1, y - 1}$（机器人下移一格且右移一格）。
2. $dp_{x, y} = dp_{x - 2, y}$（机器人下移两格）。

但是，有一个严重的问题：dp 处理机器人下移两格没有拓扑序。

我的~~偷懒~~办法是跑 $3$ 遍，这样子不仅可以有拓扑序，而且代码也比较好写。

为什么是跑 $3$ 遍？

粗略的讲，$dp_1$ 依赖 $dp_{n - 1}$，$dp_2$ 依赖 $dp_{n}$，跑一遍可以算出 $dp_3 \sim dp_n$。

再跑一遍，可以正确算出 $dp_1, dp_2$。

最后跑一遍，就可以正确算出 $dp_3 \sim dp_n$。

其他细节可见代码。
## Code
```cpp
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 5;
const int INF = 1e9;
bool a[MAXN][MAXN];
int dp[MAXN][MAXN];
int n, m, t;

int up(int s) { //求第 s 行向上一行
	return (s == 0 ? n - 1 : s - 1);
}

void solve() {
	cin >> n >> m;
	for(int i = 0; i < n; i++) {
		dp[i][0] = INF;
		for(int j = 1; j <= m; j++) { //从 1 开始，避免越界
			dp[i][j] = INF;
			cin >> a[i][j];
		}
	}
	dp[0][1] = 0;
	for(int i = 1; i <= m; i++) {
		for(int j = 0; j < n; j++) { //进行机器人下移一格且右移一格的 dp 转移
			if(a[j][i]) {
				continue;
			}
			dp[j][i] = min(dp[j][i], dp[up(j)][i - 1] + 1);
		}
		for(int g = 3; g--;) { // 跑 3 遍
			for(int j = 0; j < n; j++) {//进行机器人下移两格的 dp 转移
				int u = up(j);
				if(a[j][i] || a[u][i]) {
					continue;
				}
				dp[j][i] = min(dp[j][i], dp[up(u)][i] + 1);
			}
		}
		
	}
	int ans = INF;
	for(int i = 0; i < n; i++) {
		if(dp[i][m] == INF) {
			continue;
		}
		int pos = (n - 1 + dp[i][m]) % n; // 求出终点位置
		if(pos < i) pos += n;
		int step = dp[i][m] + min(pos - i/*不断下移两格，追上终点*/, n - (pos - i)/*停下不动，等终点*/);
		ans = min(ans, step);
	}
	cout << (ans == INF ? -1 : ans) << '\n';
}

int main() {
	for(cin >> t; t--; solve());
	return 0;
}
```

---

## 作者：Merge_all (赞：0)

## 思路：
1. 求出最短路径，首先考虑使用 bfs。bfs 要想要考难，要么从增加维度，要么转移的方式变复杂，而这道题就是将转移的方式弄复杂了。
2. 题目本身将石头也进行了移动，石头当 robot 每走一步就会向下一格。如果 robot 和石头都进行移动，直接模拟的时间复杂度就会很高，时间接受不了。我们要选择固定它们的**相对位置**，我们不妨让石头不动，看一下 robot 每一次移动的方式有什么改变。
- 向右移动：由于石头固定了，那么向下移动的操作就附加在了 robot 每一个操作上，这时向右移动对于石头来说 robot 进行了向**右下**移动。在最后一列的时候其实就用不到这个操作了，如果使用就会增加步数。
- 向上移动：先考虑什么时候这个操作是有意义的，显然是在第 $m$ 列时才会对于终点距离有意义（原因是最后一列没有石头）。而在其它列的时候就没有意义（向上一步又向下一步等于没有移动）。
- 向下移动：除了在最后一列，每次进行一次操作就会向下移动 $2$ 行。在最后一列时还是向下移动一行。

3. 所以这道题已经被转化成了常规 bfs，只是将偏移数组改变成向下 $2$ 格和向右下 $1$ 格。
4. **注意：你移动 $1$ 步，终点也会向下 $1$ 格！**
5. 定义最终答案 $ans$，终点横坐标 $now$，当前 robot 横坐标 $x$，已经走了 $step$ 次，则有：
$$ans=step+\min(\mid now-x \mid,\mid n-\max(x,now)+\min(x,now) \mid)$$

[code](https://www.luogu.com.cn/paste/oicww5os)

---

## 作者：Day_Tao (赞：0)

### 题目大意

一个机器人在一个 $n\times m$ 的平面上运动，起点为 $(0,0)$，终点为 $(n-1,m-1)$。平面上有一些石头，用 $1$ 表示。平面一直在向上循环运动，机器人和终点不随之运动。机器人可以向上、向右、向下走，每次行动平面都会上移一次，求最少要走多少步才能到终点，并且不碰到石块。

### Sol

对于一个移动的平面我们很难直接去做，所以我们可以以平面为参照物，就相当于平面不动，每次机器人行动都额外向下移动一次，终点也向下移动一次。这样机器人的运动就可以这样来描述：

>向上走：原地不动  
>向下走：向下走两格  
>向右走：向右走一格并向下走一格

可以发现向上走时没有贡献的，所以就只有两种情况，再进行 BFS。BFS 的时候可以采用类似于 SPFA 的操作对答案进行更新。

写好这样算法的代码之后，你会发现第二个样例无法通过，这是因为当你到了最后一列的时候，你可以选择在一次行动中向上走，效果是原地不动，并使终点再向下移动一次，所以对于到了最后一行的情况再考虑待在原地，让终点自己过来。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 1001;
const int INF = 0x7fffffff;
const int dx[] = {2, 1};
const int dy[] = {0, 1};
int T, n, m, a[MAX][MAX], ans[MAX][MAX];
struct Day_Tao
{
    int x,y;
};
queue<Day_Tao> q;
inline void bfs()
{
    while (!q.empty())
        q.pop();
    q.push({0, 0});
    ans[0][0] = 0;
    while (!q.empty())
    {
        int x = q.front().x, y = q.front().y;
        q.pop();
        if (x == (ans[x][y] + n - 1) % n && y == m - 1)//ans[x][y] + n - 1 就是经过 ans[x][y] 次运动终点到的地方
        {
            printf("%d\n", ans[x][y]);
            return;
        }
        for (int i = 0; i < 2; i++)
        {
            int xx = x + dx[i], yy = y + dy[i];
            if (i == 0 && a[(xx - 1) % n][yy] == 1)//注意这种向下走的情况，必须满足下面的两个格子都不是 1
                continue;
            xx %= n;
            if (yy < m && a[xx][yy] == 0 && ans[xx][yy] > ans[x][y] + 1)//更新 ans
                q.push({xx, yy}),ans[xx][yy] = ans[x][y] + 1;
        }
        if (y == m - 1)//考虑最后一列的情况
            q.push({x, y}), ans[x][y]++;
    }
    puts("-1");
    return;
}
signed main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                scanf("%d", &a[i][j]), ans[i][j] = INF;
        bfs();
    }
    return 0;
}
```

---

### END

---

## 作者：Iniaugoty (赞：0)

感觉 *2100 高了，*1800 这样子。

石头有很多，同时动很不好处理，但由于上下是循环的，我们可以转化为机器人和石头的相对运动，即，我们假设石头是静止的。

抛开最后一列不谈：机器人向上移动，变为静止；向右移动，变为向右下移动；向下移动，变为向下移动两格。

建出有向图瞎跑最短路即可，由于范围达到 $10 ^ 6$，我选择了 01-bfs。

最后，枚举最后一列每个位置的最短路径然后求答案即可，注意终点不和石头一起动，要稍微处理一下。

```cpp
#include <bits/stdc++.h>

#define F(i, a, b) for(int i = (a); i <= (b); ++i)
#define dF(i, a, b) for(int i = (a); i >= (b); --i)

using namespace std;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned int uint;
const int M = 1e3 + 5;
const int N = 1e6 + 5;
const int inf = 1e9;

int _, n, m, a[M][M], dis[N], ans; vector<int> e[N];
int id(int x, int y) { return x * m + y + 1; }
void Addedge(int u, int v) { e[u].push_back(v); }
void Bfs() { F(i, 2, n * m) dis[i] = inf; queue<int> q; q.push(1);
    while (!q.empty()) { int u = q.front(); q.pop();
        for (auto v : e[u]) if (dis[v] == inf)
            dis[v] = dis[u] + 1, q.push(v);
    }
}

int main() {
    // freopen("wmyr.in", "r", stdin);
    // freopen("wmyr.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> _; while (_--) { ans = inf;
        cin >> n >> m; F(i, 0, n - 1) F(j, 0, m - 1) cin >> a[i][j];
        F(i, 0, n - 1) F(j, 0, m - 2) if (!a[i][j]) {
            if (!a[i][j] && !a[(i + 1) % n][j + 1])
                Addedge(id(i, j), id((i + 1) % n, j + 1));
            if (!a[i][j] && !a[(i + 1) % n][j] && !a[(i + 2) % n][j])
                Addedge(id(i, j), id((i + 2) % n, j));
        } Bfs(); F(i, 0, n - 1) {
            int k = ((dis[id(i, m - 1)] - 1) % n + n) % n;
            ans = min(ans, dis[id(i, m - 1)] + min(abs(i - k), n - abs(i - k)));
        } cout << (ans >= inf ? -1 : ans) << "\n";
        F(i, 1, n * m) e[i].clear();
    }
    return 0;
}
```

---

## 作者：pyiming (赞：0)

# Turtle Mission: Robot and the Earthquake 题解
## 题目描述
在一个由 $ n $ 行 $ m $ 列组成的网格世界中，机器人 RT 需要从 $ (0,0) $ 移动到 $ (n-1,m-1) $ 以执行救援任务。网格的每一列会以每单位时间上升一格的速度循环移动。机器人不能与岩石碰撞，且不能向左移动或停留在原地。求机器人到达目的地的最短时间，若无法到达则输出 -1。
## 输入格式
第一行输入一个整数 $ t $ 表示测试用例数量。
每个测试用例的第一行输入两个整数 $ n $ 和 $ m $ 表示网格的大小。
接下来 $ n $ 行，每行 $ m $ 个整数，表示网格中每个位置是否有岩石。
## 输出格式
对于每个测试用例，输出机器人到达目的地的最短时间，若无法到达则输出 -1。
## 思路
1. **参考系转换**：考虑以岩石为参考系，研究机器人的运动。向上运动相当于原地不动，向下运动相当于向下移动两格，向右运动相当于向右下移动一格。
2. **最短路径计算**：使用 `dist[i][j]` 数组维护到达每个位置的最短时间。使用 SPFA 算法进行松弛操作，因为机器人可能会回到之前的位置。
3. **结果获取**：在 SPFA 算法结束后，遍历最后一列的所有点，找到最短时间。
## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e3, INF = 1e18;
bool flag[N + 1][N + 1];
ll dist[N + 1][N + 1];
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        ll n, m;
        scanf("%lld%lld", &n, &m);
        for (ll i = 1; i <= n; i++) {
            for (ll j = 1; j <= m; j++) {
                scanf("%d", &flag[i][j]);
                dist[i][j] = INF;
            }
        }
        queue<pair<ll, ll>> q;
        q.push({1, 1});
        dist[1][1] = 0;
        while (!q.empty()) {
            auto it = q.front();
            q.pop();
            ll x = it.first, y = it.second;
            if (!flag[x % n + 1][y] && !flag[(x + 1) % n + 1][y]) {
                if (dist[x][y] + 1 < dist[(x + 1) % n + 1][y]) {
                    dist[(x + 1) % n + 1][y] = dist[x][y] + 1;
                    q.push({(x + 1) % n + 1, y});
                }
            }
            if (y < m && !flag[x % n + 1][y + 1]) {
                if (dist[x][y] + 1 < dist[x % n + 1][y + 1]) {
                    dist[x % n + 1][y + 1] = dist[x][y] + 1;
                    q.push({x % n + 1, y + 1});
                }
            }
        }
        ll ans = INF;
        for (ll i = 1; i <= n; i++) {
            ll t = ((i - dist[i][m] - 1) % n + n) % n + 1;
            ans = min(ans, dist[i][m] + min(t, n - t));
        }
        printf("%lld\n", ans >= INF ? -1 : ans);
    }
    return 0;
}
```
## 注意事项
- 使用 SPFA 算法时，注意队列的使用和松弛条件的判断。
- 在计算最终结果时，需要考虑机器人到达最后一列后，到达目的地的剩余时间。

---

## 作者：yhylivedream (赞：0)

## 分析

我们可以将石头循环移动看作，人和终点每次固定向下循环移动一格。

这样向下移动一格就变成了向下移动两格，向右移动一格就变成了向右下移动一格，向上移动一格就变成了静止不动。

发现一般的情况，我们是不会选择向上移动的，除了现在已经到了最后一列，这时由于终点会不断往下移，所以可以原地等待，我们可以用 BFS 以 $[x,y,l]$ 为状态，表示当前在 $x$ 行 $y$ 列已经走了 $l$ 步，输出答案即可。

细节看代码。

## 代码

```cpp
# include <bits/stdc++.h> 

using namespace std;
using ll = long long;
using PII = pair <int, int>;

const int N = 1e3 + 5, inf = 0x3f3f3f3f;
int T, n, m, a[N][N], d[N][N];
queue <PII> q;

signed main () {
  for (cin >> T; T; T --) {
    for (; !q.empty(); q.pop()) {}
    cin >> n >> m;
    for (int i = 0; i < n; i ++) {
      for (int j = 0; j < m; j ++) {
        cin >> a[i][j];
        d[i][j] = inf;
      }
    }
    int ans = inf;
    d[0][0] = 0, q.push ({0, 0}); 
    for (; !q.empty(); q.pop()) {
      int x = q.front().first, y = q.front().second;
      if (y == m - 1) {
        ans = min (ans, d[x][y] + ((x - (n - 1 + d[x][y])) % n + n) % n);
      }
      int nx = (x + 2) % n, ny = y;
      if (!a[(x + 1) % n][y] && !a[nx][ny] && d[nx][ny] == inf) {
        d[nx][ny] = d[x][y] + 1, q.push({nx, ny});
      }
      nx = (x + 1) % n, ny = y + 1;
      if (!a[nx][ny] && d[nx][ny] == inf && ny <= m - 1) {
        d[nx][ny] = d[x][y] + 1, q.push({nx, ny});
      }
    }
    cout << (ans != inf ? ans : -1) << '\n';
  }
  return 0;
}
```

---

## 作者：Graph_Theory (赞：0)

### 思路
我们伟大的物理老师曾经这样说过：物体的运动是相对的。也就是说图中网格虽然在运动，但从网格的角度来说，机器人只会每次往右下移动一个格子或者往下运动 $2$ 个格子。

同时，当机器人想要从最下面再往下运动，他会直接跳到最上面。

到这里，我们将题目转化为了广搜板子，再特判一下即可。

### 代码
```cpp
int bfs(int x, int y)
{
	queue<pair<int,int> > q;
	q.push(make_pair(x,y));
	dis[x][y] = 0;
	int ans = INF;
	while(!q.empty())
	{
		int xx = q.front().first, yy = q.front().second;
		q.pop();
		if(yy==m-1) ans = min(ans, dis[xx][yy]+min(((((n-1+dis[xx][yy])%n)-xx+n)%n),((xx-((n-1+dis[xx][yy])%n)+n)%n)));
		int nx, ny;
		nx=(xx+1)%n;
		ny=yy+1;
		if(ny<=m-1&&mp[nx][ny]==0 && dis[nx][ny]==-1)
		{
			dis[nx][ny]=dis[xx][yy]+1;
			q.push(make_pair(nx, ny));
		}
		nx=(xx+2)%n;
		ny=yy;
		if(mp[(xx+1)%n][yy]==0 && mp[nx][ny]==0 && dis[nx][ny]==-1)
		{
			dis[nx][ny]=dis[xx][yy]+1;
			q.push(make_pair(nx,ny));	
		}
	}
	return ans;
}
```

---

## 作者：florrygg (赞：0)

# CF1933F Turtle Mission: Robot and the Earthquake 题解

## 思路

这道题不可能移动石头，所以我们可以以石头为参照物，那么机器人的移动就变成了：

- 向上一格 $\rightarrow$ 不动
- 向下一格 $\rightarrow$ 向下两格
- 向右一格 $\rightarrow$ 向右一格，再向下一格

因为不动绝对没有移动快，所以只有：

- 向下两格
- 向右一格，再向下一格

然后就可以 bfs 了。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define endl '\n'

const int maxn=1e3+1;
int t,n,m,a[maxn][maxn];
queue<pair<pair<int,int>,int>>q;
int ans=0;
bool flag[maxn][maxn];

void bfs()
{
	q.push({{1,1},0});
	while(!q.empty()&&ans==1e9)
	{
		pair<int,int>id=q.front().first;
		int cnt=q.front().second;
//		cout<<"i="<<((id.first-cnt)%n+n)%n<<" j="<<id.second<<" cnt="<<cnt<<endl;
		q.pop();
		if(flag[id.first][id.second])
		{
			continue;
		}
		flag[id.first][id.second]=true;
		if(id.second==m)
		{
			int now=cnt%n;
			if(now==0)
			{
				now=n;
			}
//			cout<<"now="<<now<<endl;
			ans=cnt+min(abs(now-id.first),abs(n-max(id.first,now)+min(id.first,now)));
		}
		else
		{
			id.first+=2;
			if(id.first>n)
			{
				id.first-=n;
			}
			int x=id.first-1;
			if(x==0)
			{
				x=n;
			}
			if(!a[x][id.second]&&!a[id.first][id.second])
			{
				q.push({id,cnt+1});
			}
			id.first--;
			if(id.first<1)
			{
				id.first+=n;
			}
			if(!a[id.first][id.second+1])
			{
				q.push({{id.first,id.second+1},cnt+1});
			}
			
		}
	}
	while(!q.empty())
	{
		q.pop();
	}
}

signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				cin>>a[i][j];
				flag[i][j]=false;
			}
		}
		ans=1e9;
		bfs();
		cout<<(ans==1e9?-1:ans)<<endl;
	}
	return 0;
}
```

---

