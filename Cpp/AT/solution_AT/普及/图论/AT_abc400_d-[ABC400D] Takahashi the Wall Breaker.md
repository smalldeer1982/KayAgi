# [ABC400D] Takahashi the Wall Breaker

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc400/tasks/abc400_d

高桥君想去鱼店买鳗鱼。

高桥君居住的城镇由 $H$ 行 $W$ 列的网格状区域构成，每个区域是道路或墙壁。  
以下，将从上往下第 $i$ 行（$1 \leq i \leq H$）、从左往右第 $j$ 列（$1 \leq j \leq W$）的区域表示为区域 $(i, j)$。  
各区域的信息由 $H$ 个长度为 $W$ 的字符串 $S_1, S_2, \ldots, S_H$ 给出。具体来说，当 $S_i$ 的第 $j$ 个字符（$1 \leq i \leq H$，$1 \leq j \leq W$）为 `.` 时，区域 $(i, j)$ 是道路；当为 `#` 时，区域 $(i, j)$ 是墙壁。

高桥君可以按任意顺序重复执行以下两种操作：

- 移动到上下左右相邻的、位于城镇内且为道路的区域。
- 选择一个上下左右方向，进行**前踢**。  
  当高桥君进行前踢时，可以将当前区域在该方向上 **前 1 格** 和 **前 2 格** 的区域（如果它们是墙壁）变为道路。  
  注意：即使前 1 格或前 2 格位于城镇外，仍然可以进行前踢操作，但城镇外的区域不会发生变化。

高桥君最初位于区域 $(A, B)$，想要到达位于区域 $(C, D)$ 的鱼店。  
保证高桥君初始所在的区域及鱼店所在的区域是道路。  
请计算高桥君到达鱼店所需的最小**前踢次数**。

## 说明/提示

### 约束条件

- $1 \leq H \leq 1000$
- $1 \leq W \leq 1000$
- $S_i$ 是仅由 `.` 和 `#` 组成的长度为 $W$ 的字符串
- $1 \leq A, C \leq H$
- $1 \leq B, D \leq W$
- $(A, B) \neq (C, D)$
- $H, W, A, B, C, D$ 均为整数
- 高桥君初始所在的区域及鱼店所在的区域保证是道路

### 样例解释 1

高桥君最初位于区域 $(1, 1)$。通过反复移动到道路区域，可以到达区域 $(7, 4)$。在区域 $(7, 4)$ 向左方向进行前踢后，区域 $(7, 3)$ 和 $(7, 2)$ 会从墙壁变为道路。之后，通过反复移动（包括新变为道路的区域）即可到达位于区域 $(7, 1)$ 的鱼店。此时前踢次数为 $1$ 次，且无法在不使用前踢的情况下到达鱼店，因此输出 $1$。

### 样例解释 2

高桥君最初位于区域 $(1, 1)$。向右方向进行前踢后，区域 $(1, 2)$ 会从墙壁变为道路（向右前 2 格超出城镇范围，因此无变化）。之后可以从区域 $(1, 1)$ 移动到区域 $(1, 2)$，再到达区域 $(2, 2)$ 的鱼店。此时前踢次数为 $1$ 次，且无法在不使用前踢的情况下到达鱼店，因此输出 $1$。

### 样例解释 3

前踢操作可能影响包含鱼店所在区域的区画，但鱼店所在区域原本就是道路，因此不会发生变化。特别是前踢操作不会破坏鱼店。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
10 10
..........
#########.
#.......#.
#..####.#.
##....#.#.
#####.#.#.
.##.#.#.#.
###.#.#.#.
###.#.#.#.
#.....#...
1 1 7 1```

### 输出

```
1```

## 样例 #2

### 输入

```
2 2
.#
#.
1 1 2 2```

### 输出

```
1```

## 样例 #3

### 输入

```
1 3
.#.
1 1 1 3```

### 输出

```
1```

## 样例 #4

### 输入

```
20 20
####################
##...##....###...###
#.....#.....#.....##
#..#..#..#..#..#..##
#..#..#....##..#####
#.....#.....#..#####
#.....#..#..#..#..##
#..#..#.....#.....##
#..#..#....###...###
####################
####################
##..#..##...###...##
##..#..#.....#.....#
##..#..#..#..#..#..#
##..#..#..#..#..#..#
##.....#..#..#..#..#
###....#..#..#..#..#
#####..#.....#.....#
#####..##...###...##
####################
3 3 18 18```

### 输出

```
3```

# 题解

## 作者：LucasAoSaic (赞：8)

## 题目翻译
### 问题描述
Takahashi 即将去鱼店买鳗鱼。  
他所在的小镇被划分为 $ H $ 行 $ W $ 列的网格。每个格子要么是道路，要么是墙。  
我们将从顶部数第 $ i $ 行（$ 1 \le i \le H $）和从左侧数第 $ j $ 列（$ 1 \le j \le W $）的格子记为 $ (i,j) $。  
每个格子的相关信息由 $ H $ 个字符串 $ S_1, S_2, \dots, S_H $ 给出，每个字符串长度为 $ W $。具体来说，如果 $ S_i $ 的第 $ j $ 个字符（$ 1 \le i \le H,\ 1 \le j \le W $）为 `.` 则表示 $ (i,j) $ 为道路；若为 `#` 则为墙。

他可以重复以任意顺序执行以下两种操作：

- **移动**：移动到上下左右相邻且为道路的格子。  
- **前踢**：选择四个方向中的一个（上、下、左或右），并向该方向前踢。当执行前踢时，从当前格子起该方向上最多 `2` 步远内的每个格子，如果该格子为墙，则其变为道路。如果距离超过 `2` 步的格子或超出小镇范围，则不会改变（但操作仍可执行）。

他从格子 $ (A,B) $ 出发，希望到达鱼店所在的格子 $ (C,D) $。  
保证起点和鱼店所在的格子均为道路。  
求他到达鱼店所需执行的最小前踢次数。


## 核心思想

求出从起点到终点所需的最少前踢次数。 

存在两种操作：  
- **相邻移动**（只允许在道路上，且费用为 `0`，  
- **前踢操作**（将墙转换为道路，费用为 `1`，

操作的代价不同，因此我们可用 **BFS** 来求解问题。

1. 利用双端队列`deque`来存储状态，  
2. 当执行相邻移动（`0`成本）时，将状态放到队列前端；  
3. 当执行前踢操作（`1`成本）时，将状态放到队列尾部；  
4. 使用一个二维数组 `dis` 来记录从起点到每个格子的最小前踢次数，并依据新的状态更新 `dis` 以进行松弛操作。  

**为什么要将`0`成本的移动放在队列前，将`1`成本的移动放在队列后？**

- `0` 成本的边：

  当边权为 `0` 时，也就是说我们可以“免费”地从一个状态转换到另一个状态，那么我们希望这个转换能够尽快被处理，以免延迟可能带来的更优解。  
  因此，我们将新状态加入到双端队列的前端，使得这些状态能够更快地被取出并扩展，确保低成本状态优先被探索。

- `1` 成本的边:

  当边的权值为 `1` 时，意味着转换会增加一步前踢的代价。我们希望这些状态在所有“免费”状态全部扩展完之后再被处理。  
所以，
将它们放到队列尾部，这样即使先处理了多次 `0` 成本的移动，最终也能保证以较低的总成本到达目标。

通过这种方式，双端队列自然地按照转换的累计成本从低到高排序，确保我们能够找到从起点到终点的最小前踢次数，且可以优化一定的效率。

这样便可以保证先处理成本低的状态，最终得到到达终点的最小前踢次数。

## AC代码

```cpp
#include <iostream>
#include <vector>
#include <deque>
#include <cstring>
using namespace std;

const int N = 1005, inf = 0x3f3f3f3f;  // 定义最大尺寸和一个很大的初始值

int h, w, a, b, c, d;  // h, w: 地图尺寸；a,b: 起点；c,d: 终点
int dx[4] = {-1, 1, 0, 0};  // 定义四个方向的行偏移量（上、下、左、右）
int dy[4] = {0, 0, -1, 1};  // 定义四个方向的列偏移量（上、下、左、右）

vector<vector<char>> grid(N, vector<char>(N));  // grid 存储地图信息，'.' 表示道路，'#' 表示墙
vector<vector<int>> dis(N, vector<int>(N, inf));  // dis 数组记录从起点到每个格子所需的最少前踢次数，初始值设置为 inf 表示未到达
deque<pair<int, int>> dq;  // 使用 deque 实现 BFS，存储队列状态为 (行, 列)

int main()
{
    scanf("%d%d", &h, &w);
    for (int i = 1; i <= h; ++ i)
    {
        string s;
        cin >> s;
        for (int j = 1; j <= w; ++ j)  // 将每一行的字符存入 grid 数组中
        {
            grid[i][j] = s[j - 1];
        }
    }
    scanf("%d%d%d%d", &a, &b, &c, &d);

    dis[a][b] = 0;  // 初始化起点状态，前踢次数为 0
    dq.push_back({a, b});  // 将起点加入队列

    while (!dq.empty())  // BFS 主循环
    {
        auto [curi, curj] = dq.front();  // 取出队头状态（C++ 17新写法）
        dq.pop_front();
        int cur = dis[curi][curj];  // 当前状态的前踢次数

        if (curi == c && curj == d)  // 如果当前状态为终点，则输出结果并退出
        {
            printf("%d\n", cur);
            return 0;
        }

        // 1. 0成本移动：尝试从当前格子向四个方向移动到相邻的格子
        for (int i = 0; i < 4; ++ i)  // 只能移动到道路格（'.'）并且松弛更新可以获得更小的前踢次数
        {
            int nowi = curi + dx[i],
                nowj = curj + dy[i];

            if (nowi <= 0 || nowi > h || nowj <= 0 || nowj > w)  // 判断是否越界
            {
                continue;
            }

            if (grid[nowi][nowj] == '.' && dis[nowi][nowj] > cur)  // 如果目标格子为道路且可以通过当前状态获得更优结果，则更新并加入队列前端
            {
                dis[nowi][nowj] = cur;
                dq.push_front({nowi, nowj});
            }
        }

        // 2. 1成本移动：尝试前踢操作，向四个方向每个最多移动 2 格
        for (int i = 0; i < 4; ++ i)  // 无论目标格子原本是墙还是道路，只要通过前踢操作能更新更低的前踢次数，则进行更新
        {
            for (int j = 1; j <= 2; ++j) {
                int nowi = curi + dx[i] * j,
                    nowj = curj + dy[i] * j;

                if (nowi <= 0 || nowi > h || nowj <= 0 || nowj > w)  // 判断是否越界
                {
                    break;
                }

                if (dis[nowi][nowj] <= cur + 1)  // 如果该格子已经以小于等于 (cur + 1) 的前踢次数到达，则无需更新
                {
                    continue;
                }

                dis[nowi][nowj] = cur + 1;  // 更新前踢次数为 cur + 1 并将状态加入队列尾部（1成本操作）
                dq.push_back({nowi, nowj});
            }
        }
    }

    printf("-1\n");  // 如果无法到达终点，则输出 -1
    return 0;
}
```

---

## 作者：wmrqwq (赞：4)

这是一篇视频题解。

![](bilibili:BV19BRdYdEHk?t=294)

[参考代码](https://atcoder.jp/contests/abc400/submissions/64527412)

---

## 作者：__hjyakioi__ (赞：3)

## 解析
因为这道题只有 _不使用前踢_ 和 _使用前踢_ 两种转移方式，所以我们可以使用 `01bfs` 在 $O(HW)$ 时间内解决。\
前踢操作对点的影响可以等效为花费 $1$ 的代价，到达该点。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
char c[1010][1010];
int h, w;
int d[1010][1010];
pii g(int x, int y) { return {x,y}; }
int bfs(pii st, pii ed)
{
    deque<pair<pii, int>> dq;
    dq.push_back({st, 1});
    while (dq.size())
    {
        auto [pos, dis] = dq.front();
        dq.pop_front();
        auto [x,y]=pos;
        if (d[x][y])
            continue;
        if (g(x, y) == ed)
            return dis;
        d[x][y] = dis;
        // cout<<x<<" "<<y<<" "<<dis<<endl;
        if (x >= 1 && x <= h && y + 1 >= 1 && y + 1 <= w && c[x][y + 1] == '.' && d[x][y + 1] == 0)
        {
            dq.push_front({g(x, y + 1), dis});
        }
        if (x >= 1 && x <= h && y - 1 >= 1 && y - 1 <= w && c[x][y - 1] == '.' && d[x][y - 1] == 0)
        {
            dq.push_front({g(x, y - 1), dis});
        }
        if (x + 1 >= 1 && x + 1 <= h && y >= 1 && y <= w && c[x + 1][y] == '.' && d[x + 1][y] == 0)
        {
            dq.push_front({g(x + 1, y), dis});
        }
        if (x - 1 >= 1 && x - 1 <= h && y >= 1 && y <= w && c[x - 1][y] == '.' && d[x - 1][y] == 0)
        {
            dq.push_front({g(x - 1, y), dis});
        }
        if (x >= 0 && x <= h+1 && y + 2 >= 0 && y + 2 <= w+1 && d[x][y + 2] == 0)
        {
            dq.push_back({g(x, y + 2), dis + 1});
            dq.push_back({g(x, y + 1), dis + 1});
        }
        if (x >= 0 && x <= h+1 && y - 2 >= 0 && y - 2 <= w+1 && d[x][y - 2] == 0)
        {
            dq.push_back({g(x, y - 2), dis + 1});
            dq.push_back({g(x, y - 1), dis + 1});
        }
        if (x + 2 >= 0 && x + 2 <= h+1 && y >= 0 && y <= w+1 && d[x + 2][y] == 0)
        {
            dq.push_back({g(x + 2, y), dis + 1});
            dq.push_back({g(x + 1, y), dis + 1});
        }
        if (x - 2 >= 0 && x - 2 <= h+1 && y >= 0 && y <= w+1 && d[x - 2][y] == 0)
        {
            dq.push_back({g(x - 2, y), dis + 1});
            dq.push_back({g(x - 1, y), dis + 1});
        }
    }
    return -1;
}
int main()
{
    cin >> h >> w;
    memset(c,'.',sizeof c);
    for (int i = 1; i <= h; i++)
    {
        cin >> (c[i] + 1);
    }
    int stx, sty, edx, edy;
    cin >> stx >> sty >> edx >> edy;
    cout << bfs(g(stx, sty), g(edx, edy))-1;
}
```

---

## 作者：szh_AK_all (赞：2)

很显然的广搜题？

每次从当前点开始，分别向四个方向拓展，而这个拓展至多可以一次拓展两个点，那么跟着模拟即可。

我用了优先队列实现，用 $vis$ 数组表示到达每个点的最少操作次数，那么当其他点重新到达这个点并且操作次数更优时，就可以更新一下 $vis$ 数组。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int x, y, xx, yy, h, w;
char a[1005][1005];
int vis[1005][1005];

struct node {
	int x, y, z;
	node(int aa = 0, int bb = 0, int cc = 0) {
		x = aa;
		y = bb;
		z = cc;
	}
	friend bool operator<(node l, node r) {
		return l.z > r.z;
	}
};

int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
void bfs() {
	priority_queue<node>q;
	q.push(node(x, y, 0));
	vis[x][y] = 0;
	while (!q.empty()) {
		int nx = q.top().x, ny = q.top().y, z = q.top().z;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int sx = nx + dx[i], sy = ny + dy[i];
			int sxx = sx + dx[i], syy = sy + dy[i];
			if (1 <= sx && sx <= h && 1 <= sy && sy <= w) {
				if (a[sx][sy] == '#') {
					if (vis[sx][sy] > z + 1 || vis[sx][sy] == -1)
						q.push(node(sx, sy, z + 1)), vis[sx][sy] = z + 1;
				} else if (vis[sx][sy] > z || vis[sx][sy] == -1)
					q.push(node(sx, sy, z)), vis[sx][sy] = z;

			}
			if (1 <= sxx && sxx <= h && 1 <= syy && syy <= w) {
				if ((a[sx][sy] == '#' || a[sxx][syy] == '#')) {
					if (vis[sxx][syy] > z + 1 || vis[sxx][syy] == -1)
						q.push(node(sxx, syy, z + 1)), vis[sxx][syy] = z + 1;
				} else if (vis[sxx][syy] > z || vis[sxx][syy] == -1)
					q.push(node(sxx, syy, z)), vis[sxx][syy] = z;
			}
		}
	}
	cout << vis[xx][yy];
}

signed main() {
	memset(vis, -1, sizeof(vis));
	cin >> h >> w;
	for (int i = 1; i <= h; i++)
		for (int j = 1; j <= w; j++)
			cin >> a[i][j];
	cin >> x >> y >> xx >> yy;
	bfs();
}
```

---

## 作者：Merge_all (赞：1)

# Solution
考虑到从一个点往上下左右走，对于答案的贡献只有 $0$ 和 $1$，因此一眼确定可以用 01bfs 写。

对于每个点走一步，要么是空地，要么是墙。那么对于答案的贡献肯定也只有 $0$ 和 $1$。

如果是墙的话就多走一步即可，转换出来就是一个板子题。
# Code
```
#include <bits/stdc++.h>
using namespace std;
static constexpr size_t N = 2e5 + 5, M = 2e3 + 5;
static constexpr int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
int n, m, dist[M][M], sx, sy, zx, zy;
char G[M][M];
deque<pair<int, int>> q;
void bfs(int sx, int sy) {
	memset(dist, 0x3f, sizeof dist);
	dist[sx][sy] = 0, q.push_front ({sx, sy});
	while (q.size ()) {
		auto [x, y] = q.front (); q.pop_front ();
		for (int i = 0; i < 4; i ++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (nx < 0 || nx > n || ny < 0 || ny > m) continue;
			if (G[nx][ny] == '.') {
				if (dist[nx][ny] > dist[x][y]) dist[nx][ny] = dist[x][y], q.push_front ({nx, ny});
			} 
			else {
				if (dist[nx][ny] > dist[x][y] + 1) dist[nx][ny] = dist[x][y] + 1, q.push_back ({nx, ny});
				nx += dx[i], ny += dy[i];
				if (nx < 0 || nx > n || ny < 0 || ny > m) continue;
				if (dist[nx][ny] > dist[x][y] + 1) dist[nx][ny] = dist[x][y] + 1, q.push_back ({nx, ny});
			}
		}
	}
	cout << dist[zx][zy] << '\n';
}
int main () {
	*cin.tie(nullptr) << fixed << setprecision (20);
	cout.tie(nullptr) -> ios_base :: sync_with_stdio (false);
	
	cin >> n >> m;
	for (int i = 1; i <= n; i ++) 
		for (int j = 1; j <= m; j ++) 
			cin >> G[i][j];
	cin >> sx >> sy >> zx >> zy;
	bfs(sx, sy);
	return 0;
}
```

---

## 作者：zbzbzzb (赞：1)

考虑最短路。

我们建一个以前踢为边权的图，具体建法如下：

- 首先为矩阵的每一个点建立一个图中的点。

- 枚举整个矩阵，向它的上下左右四个方向看。如果为道路就建一条边权为 $0$ 的边，代表不用前踢。如果为墙就建两条边权为 $1$ 的边，因为一次前踢可以破两个墙。

建完图就可以跑最短路了。

解释的可能不太清楚，看代码理解吧。


```cpp
#include<bits/stdc++.h>//这里我用的是dijkstra
using namespace std;
const int M=8e6+20；
int n,m,a,b,c,d,r,dis[M],cnt[1010][1010],vis[1000010],mi=0x3f3f3f3f;
int to[M],nxt[M],bgn[M],e=0,w[M];//前向星
string s[1010];
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
void add(int x,int y,int z){
	e++,to[e]=y,w[e]=z;
	nxt[e]=bgn[x],bgn[x]=e;
}struct node{
	int id;
	long long val;
};
bool operator < (node a,node b){
	return a.val>b.val;
}priority_queue<node>q;
void dijkstra(int s){//dij就不用过多解释了吧
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=r+10;i++){
		dis[i]=0x3f3f3f3f;
	}dis[s]=0;
	q.push((node){s,0});
	while(!q.empty()){
		node temp=q.top();
		q.pop();
		int x=temp.id;
		if(vis[x]==1){
			continue;
		}vis[x]=1;
		for(int j=bgn[x];j;j=nxt[j]){
			int y=to[j],z=w[j];
			if(dis[y]>dis[x]+z){
				dis[y]=dis[x]+z;
				q.push((node){y,dis[y]});
			}
		}
	}
}int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		cin>>s[i];
		s[i]=" "+s[i];//这里因为是string只能这样把下标转成从1开始
	}scanf("%d%d%d%d",&a,&b,&c,&d);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			r++;
			cnt[i][j]=r;//用一个数组存下每个点在图中是哪个点
		}
	}for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=0;k<4;k++){
				int ii=i+dx[k],jj=j+dy[k];//上下左右
				if(ii>=1&&ii<=n&&jj>=1&&jj<=m){
					if(s[ii][jj]=='.'){//发现为道路
						add(cnt[i][j],cnt[ii][jj],0);//建一条边权为0的，从(i,j)到(ii,jj)的边
					}else if(s[ii][jj]=='#'){//不能走
						add(cnt[i][j],cnt[ii][jj],1);//先建一条边权为1的，从(i,j)到(ii,jj)的边
						if(ii+dx[k]>=1&&ii+dx[k]<=n&&jj+dy[k]>=1&&jj+dy[k]<=m){//然后判断往后一个点是否在边界外
							add(cnt[i][j],cnt[ii+dx[k]][jj+dy[k]],1);//不是，那么也可以直接到这里，再建一条边
						}
					}
				}
			}
		}
	}dijkstra(cnt[a][b]);
	printf("%d",dis[cnt[c][d]]);
	return 0;
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：0)

[ABC400D](https://www.luogu.com.cn/problem/AT_abc400_d)

## Statement

给定一个 $n\times m$ 的网格图，每个格子要么是 `#` 或者 `.`，其中 `#` 表示墙壁，`.` 表示道路。

高桥现在要从 $(a,b)$ 出发前往 $(c,d)$，假设他处于 $(x,y)$，他可以执行：

- 向上下左右任一方向最多走两格，如果遇到墙壁就破掉墙，如果不是墙壁则直接通行。

问最少进行多少次破墙操作。

## Solution

考虑在网格图上建图跑最短路即可，如果当前方向上第一格可通过，连一条边权 $0$ 的边；如果不可通过，就连一条边权为 $1$ 的边，再向后走一格看是否为墙，如果是再连一条边权 $1$ 的边。

**总边数可能较多**。

## Code

[Submission](https://atcoder.jp/contests/abc400/submissions/64575969)

---

## 作者：x1489631649 (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc400_d)
### 分析
这道题目是一道枚举题。输入一个方阵，可以走是道路的位置，可以将是墙壁的位置连续两个方块变成道路，然后答案加一。

可以考虑使用枚举，先从开始的地点枚举不需要打破墙壁的，由这些地点打破四周的墙壁，标记为 1 ，然后再从标记为 1 的地方枚举，一直到可以到达目标地点。

### Code
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,x,y,u,v;
int a[1005][1005],f[1005][1005],vis[1005][1005];
struct node{
	int x,y;
}q[1000005];
int dx[5]={0,0,0,-1,1};
int dy[5]={0,1,-1,0,0};
void bfs(int x,int y,int cnt)//常规 bfs
{
	int h,t;
	h=t=1;
	q[h].x=x;
	q[h].y=y;
	f[x][y]=cnt-1;
	vis[x][y]=1;
	while(h<=t)
	{
		for(int i=1;i<=4;i++)
		{
			int nx=q[h].x+dx[i];
			int ny=q[h].y+dy[i];
			if(a[nx][ny]==1&&1<=nx&&nx<=n&&1<=ny&&ny<=m&&vis[nx][ny]==0)
			{
				t++;
				q[t].x=nx;
				q[t].y=ny;
				vis[nx][ny]=1;
				f[nx][ny]=cnt-1;
			}
		}
		h++;
	}
}
void slove()
{
	int cnt=0;
	f[x][y]=0;
	while(++cnt)
	{
		
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(vis[i][j]==0&&f[i][j]==cnt-1)
				{
					bfs(i,j,cnt);
					if(f[u][v]!=-1)//如果能走到目标方块直接输出。
					{
						cout<<f[u][v];
						return;
					}
				}
			}
		}
		
		for(int i=1;i<=n;i++)//打破墙壁，并将答案加一。
		{
			for(int j=1;j<=m;j++)
			{
				if(f[i][j]==cnt-1)
				{
					for(int k=1;k<=4;k++)
					{
						int nx=i+2*dx[k];
						int ny=j+2*dy[k];
						int nx1=i+dx[k];
						int ny1=j+dy[k];
						if(f[nx][ny]==-1&&1<=nx&&nx<=n&&1<=ny&&ny<=m)
						{
							a[nx][ny]=1;
							f[nx][ny]=cnt;
						}
						if(f[nx1][ny1]==-1&&1<=nx1&&nx1<=n&&1<=ny1&&ny1<=m)
						{
							a[nx1][ny1]=1;
							f[nx1][ny1]=cnt;
						}
					}
				}
			}
		}
		if(f[u][v]!=-1)
		{
			cout<<f[u][v];
			return;
		}
	}
}
signed main()
{
	string str;
	memset(f,-1,sizeof(f));
	cin>>n>>m;
	for(int i=1;i<=n;i++)//处理出入
	{
		cin>>str;
		for(int j=1;j<=m;j++)
		{
			if(str[j-1]=='.')
				a[i][j]=1;
			else a[i][j]=0;
		}
	}
	cin>>x>>y>>u>>v;
	slove();
	return 0;
}
```
### 时间复杂度
每块方格最多走一次，时间复杂度为 $O(n^2)$，显然可以通过。

---

## 作者：Big_Dinosaur (赞：0)

需要使用 [0-1 BFS](https://oi-wiki.org/graph/bfs/#%E5%8F%8C%E7%AB%AF%E9%98%9F%E5%88%97-bfs)。

观察发现，这道题可以转化为：

- 向上下左右移动一格，权值为接下来到的一格是否为障碍，若是，为 $1$，否则为 $0$。
- 若朝上下左右中一个方向的两格中有任意一格为障碍，则向这个方向走 $2$ 格，权值为 $1$。

发现移动权值为 $1$ 或 $0$，考虑用 0-1 BFS 解决。

```cpp
#include<bits/stdc++.h>
//#define int long long
#define ri register int
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second
using namespace std;
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
		#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
 	#else
		#define gh() getchar()
	#endif
	inline int r(){
		int o=1,p=0;
		char q=gh();
		while(q<'0'||q>'9'){if(q=='-')o=-1;q=gh();}
		while(q>='0'&&q<='9'){p=(p<<1)+(p<<3)+(q^48);q=gh();}
		return o*p;
	}
	inline char gc(){char q=gh();while(q<=' ')q=gh();return q;}
	inline string gs(){string s="";char g=gh();while(g<=' ')g=gh();while(g>' '){s+=g;g=gh();}return s;}
	inline void Wi(int E){
		if(E==0)return;if(E<0){E=-E;putchar('-');}
		Wi(E/10);putchar((E%10)^48);
	}
	inline void wln(int J){if(J==0)putchar('0');else Wi(J);putchar('\n');}
	inline void w(int J){if(J==0)putchar('0');else Wi(J);}
	inline void ww(int J){if(J==0)putchar('0');else Wi(J);putchar(' ');}
}
using namespace IO;
namespace D1n0{
	int h,w,t[1003][1003];
	int X[4]={0,0,1,-1},Y[4]={-1,1,0,0};
	bool p[1003][1003],vi[1003][1003];
	deque<pii>d;
	inline void zyt(){
		h=r(),w=r();
		for(ri i=1;i<=h;++i){
			string s=gs();
			for(ri j=1;j<=w;++j)if(s[j-1]=='#')p[i][j]=1;else p[i][j]=0;
		}
		int x1=r(),y1=r(),x2=r(),y2=r();
		d.push_back(mp(x1,y1));
		memset(t,1,sizeof t);t[x1][y1]=0;
		while(!d.empty()){
			int x=d.front().fi,y=d.front().se;d.pop_front();
			if(vi[x][y])continue;
			for(ri i=0;i<4;++i){
				int xx=x+X[i],yy=y+Y[i];
				if(xx>0&&xx<=h&&yy>0&&yy<=w){
					if(p[xx][yy]==0&&t[xx][yy]>t[x][y]){
						t[xx][yy]=t[x][y];
						d.push_front(mp(xx,yy));
					}else{
						if(t[xx][yy]>t[x][y]+1){
							t[xx][yy]=t[x][y]+1;
							d.push_back(mp(xx,yy));
						}
						xx+=X[i],yy+=Y[i];
						if(xx>0&&xx<=h&&yy>0&&yy<=w){
							if(t[xx][yy]>t[x][y]+1){
								t[xx][yy]=t[x][y]+1;
								d.push_back(mp(xx,yy));
							}
						}
					}
				}
			}
		}
		wln(t[x2][y2]);
	}
}
signed main(){D1n0::zyt();}
```

---

## 作者：XZDZD (赞：0)

# **[[ABC400D] Takahashi the Wall Breaker](https://www.luogu.com.cn/problem/AT_abc400_d)**

### **题意分析**

题目大意是简单的搜索，搜到墙时更新状态踢腿次数加一，搜完就可以了。但是这样搜会T，并且更新比较混乱。于是我们考虑优化。

### **优化**

考虑开两条队列，第一条队列用来放次数为零也就是没有踢腿的点。第二条存踢过腿的点。优先处理第一条队列的点。这样就可以大大优化效率。


### **注意**

对于练习搜索的初学者，需要注意 dis 要初始化一个大的值以便于更新，对于本题，由于踢腿范围是两格因此需要多写一种情况。

注意不要越界！！！

## _**Code**_ 


```cpp
#include<bits/stdc++.h>
#define ll long long
const int N = 1e5 + 10;
using namespace std;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
struct point
{
    int x,y,step;
};
int dis[1005][1005];
queue <point> q[2];
char mmap[1005][1005];
int h,w;
int sx,sy,ex,ey;
int main() {
    cin>>h>>w;
    for(int i = 1;i <= h; ++i){
        for(int j = 1;j <= w; ++j){
            cin>>mmap[i][j];
            if(mmap[i][j] == '#'){
                dis[i][j] = 1e9;
            }
            else{
                dis[i][j] = 1e9;
            }
        }
    }
    cin>>sx>>sy>>ex>>ey;
    q[0].push({sx,sy,0});
    dis[sx][sy] = 0;
    int cur = 0,nxt = 1;
    while (!q[0].empty() || !q[1].empty() ) {
        while (!q[cur].empty())
        {
            point u = q[cur].front(), v;
            q[cur].pop();
            for (int i = 0;i < 4; ++i) {
            	bool wall = false;
            	for (int j = 1;j <= 2; ++j) {
            		v.x = u.x + dx[i] * j;
            		v.y = u.y + dy[i] * j;
            		if (v.x < 1 || v.x > h || v.y > w || v.y < 1) continue;
            		if (mmap[v.x][v.y] == '#'){
            			wall = true;
            		} 
            		int to;
            		if (wall) { //关键代码，判断入哪个队列
            			to = nxt;
            			v.step = u.step + 1;
            		}else {
            			to = cur;
            			v.step = u.step;
            		}
            		if (dis[v.x][v.y] <= v.step) continue;
            		q[to].push(v);
            		dis[v.x][v.y] = v.step;
            	}
            }
        }
        swap(cur,nxt);
    }
    cout<<dis[ex][ey];
    return 0;
}

```

---

## 作者：Cosine_Func (赞：0)

容易发现题目中的两种走法花费分别为 $0$ 和 $1$，考虑使用 01BFS，然后就是标准的板子，注意一下枚举 $1$ 到 $3$ 的距离即可。时间复杂度是 $O(W\times H)$，优于 Dijkstra。由于本题是 01 权图，使用 SPFA 也能实现线性时间复杂度。
```python
from collections import deque
import sys
input = sys.stdin.readline
H, W = map(int, input().split())
g = [list(input().strip()) for _ in range(H)]
A, B, C, D = map(int, input().split())
s = (A - 1, B - 1)
e = (C - 1, D - 1)
INF = 10**9
d = [[INF] * W for _ in range(H)]
d[s[0]][s[1]] = 0
adj = [(-1, 0), (1, 0), (0, -1), (0, 1)]
dq = deque([s])
while dq:
    r, c = dq.popleft()
    if (r, c) == e:
        print(d[r][c])
        sys.exit(0)
    for dr, dc in adj:
        nr, nc = r + dr, c + dc
        if 0 <= nr < H and 0 <= nc < W and g[nr][nc] == '.' and d[nr][nc] > d[r][c]:
            d[nr][nc] = d[r][c]
            dq.appendleft((nr, nc))
    for dr, dc in adj:
        for s in range(1, 3):
            nr, nc = r + dr * s, c + dc * s
            if 0 <= nr < H and 0 <= nc < W and d[nr][nc] > d[r][c] + 1:
                d[nr][nc] = d[r][c] + 1
                dq.append((nr, nc))

print(d[e[0]][e[1]])
```

---

## 作者：Tairitempest (赞：0)

## [ABC400D] Takahashi the Wall Breaker
没学过 01BFS，所以现场推了个类似的东西。

用两个队列，一个处理普通移动，然后把处理后可达的格子扔到另一个队列里；一个处理踢，踢完再把可到达的格子扔进普通移动队列里。

记录一下走过的格子可以防止再次访问。因为是按照踢墙次数从小到大处理的所以得到的一定是最优解。

复杂度 $O(N^2)$。

## [Code](https://atcoder.jp/contests/abc400/submissions/64530481)

---

