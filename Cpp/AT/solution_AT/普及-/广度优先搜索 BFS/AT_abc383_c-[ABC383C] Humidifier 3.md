# [ABC383C] Humidifier 3

## 题目描述

给你一个 $H$ 行 $W$ 列的矩阵，如果为 `#` 代表为障碍物，`.` 为空地， `H` 为喷水器。   
定义一个地方是湿的，当且仅当有从一个喷水器可以通过最多 $D$ 步移动（四联通）到达这个地方。   
**注意，喷水器所在的地方也是湿的。**   
求有多少个湿的地方。

## 说明/提示

$1\le H,W\le1000$   
$1\le D\le H\times W$

## 样例 #1

### 输入

```
3 4 1
H...
#..H
.#.#```

### 输出

```
5```

## 样例 #2

### 输入

```
5 6 2
##...H
H.....
..H.#.
.HH...
.###..```

### 输出

```
21```

## 样例 #3

### 输入

```
1 6 3
...#..```

### 输出

```
0```

# 题解

## 作者：ikunTLE (赞：12)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc383_c)

### 思路

本题可以使用**记忆化搜索**。

定义二维数组 $f$，$f_{i,j}$ 表示从 $(i,j)$ 点出发到最近加湿器的距离。首先用 $\infty$ 将 $f$ 填充，以每个加湿器为起点作 bfs。当到达 $(i,j)$ 点时，若其距离小于 $f_{i,j}$，则继续 bfs；否则在这个点终止，因为再以这点继续遍历，其剩余可走的长度必定不如之前的长。bfs 需记录其走过的长度 $L$，当 $L=D$ 时终止当前点的 bfs。最后统计不为 $\infty$ 的点的数量即可。

如果不做记忆化，那么最差情况下，以每一个加湿器都会遍历整个网格，时间复杂度为 $\mathcal{O}(N^4)$。做了记忆化以后，不存在所有的点都会被走过的情况，时间复杂度约为 $\mathcal{O}(N^3)$，且常数非常小，实测时间不会超过 $400$ 毫秒，可以通过此题。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=1e3+10;
char s[N][N];
struct node{
	int x,y,step;
};queue<node>q;
int h,w,d,f[N][N];
int dx[]={0,-1,1,0,0},dy[]={0,0,0,-1,1};
void bfs(int sx,int sy){
	while(!q.empty())
		q.pop();
	q.push({sx,sy,0});
	while(!q.empty()){
		node u=q.front();q.pop();
		int x=u.x,y=u.y,step=u.step;
		if(step>=d)
			continue;
		for(int i=1;i<=4;++i){
			int xx=x+dx[i],yy=y+dy[i];
			if(xx>=1&&xx<=h&&yy>=1&&yy<=w&&s[xx][yy]!='#'&&f[x][y]+1<f[xx][yy]){
				f[xx][yy]=f[x][y]+1;
				q.push({xx,yy,step+1});
			}
		}
	}
	return;
}
signed main(){
	h=read(),w=read(),d=read();
	for(int i=1;i<=h;++i)
		scanf("%s",s[i]+1);
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=h;++i)
		for(int j=1;j<=w;++j)
			if(s[i][j]=='H')
				f[i][j]=0;
	for(int i=1;i<=h;++i)
		for(int j=1;j<=w;++j)
			if(s[i][j]=='H')
				bfs(i,j);
	int sum=0;
	for(int i=1;i<=h;++i)
		for(int j=1;j<=w;++j)
			sum+=(f[i][j]<N*N);
	printf("%lld\n",sum);
	return 0;
}
```

---

## 作者：xk2013 (赞：6)

题目传送门：[AT_abc383_c [ABC383C] Humidifier 3](/problem/AT_abc383_c)

## 前置知识
- 洪水填充；
- 广度优先搜索（BFS）。

## 题意简述
给定加湿器位置和加湿长度，求有几个地板被加湿。

## 解题思路
### 暴力 BFS
对于每个加湿器跑一遍 BFS，总共跑 $nm$ 遍 BFS，时间复杂度 $\Omicron(h^2w^2)$，[直接 T 飞](/record/193445885)。

### 正解
把所有加湿器扔进一个广搜队列里一起跑，时间复杂度就只有 $\Omicron(hw)$，[轻松过](/record/193442136)。

## 完整代码
看完上面再看这儿，不能只看这儿，更不能 Copy！
```cpp
#include <algorithm>
#include <cstdio>
#include <queue>
#include <utility>
#include <vector>

struct Node
{
	int x;
	int y;
	int step;
};

const int H = 1e3 + 5, W = 1e3 + 5, dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int h, w, d, ans;
bool vis[H][W];
char map[H][W];
std::vector <std::pair<int, int>> v;
std::queue <Node> q;

void bfs(void);

int main(void)
{
	scanf("%d %d %d", &h, &w, &d);
	
	for (int i = 0; i < h; i++)
	{
		scanf("%s", map[i]);
		
		for (int j = 0; j < w; j++)
		{
			if (map[i][j] == 'H')
			{
				q.push(Node{i, j, 0}); // 扔到同一个队列里，注意不要标记
			}
		}
	}
	
	bfs(); // 跑 BFS 板子
	
	for (int i = 0; i < h; i++) // 统计答案
	{
		for (int j = 0; j < w; j++)
		{
			if (map[i][j] == 'H' || map[i][j] == '!')
			{
				ans++;
			}
		}
	}
	
	printf("%d", ans);
	return 0;
}

void bfs(void)
{
	while (!q.empty())
	{
		Node f = q.front();
		q.pop();
		
		if (f.step > d)
		{
			continue;
		}
		
		if (map[f.x][f.y] == '.')
		{
			map[f.x][f.y] = '!';
		}
		
		for (int i = 0; i < 4; i++)
		{
			int tx = f.x + dir[i][0], ty = f.y + dir[i][1];
			
			if (0 <= tx && tx < h && 0 <= ty && ty < w && map[tx][ty] != '#' && !vis[tx][ty])
			{
				vis[tx][ty] = true;
				q.push(Node{tx, ty, f.step + 1});
			}
		}
	}
}

```
----------------------
这是本五年级蒟蒻小学生的第 18 篇题解，不喜可喷，但求你不要喷太猛了哦~

## 更新日志
- 2024/12/08：初版。

---

## 作者：4041nofoundGeoge (赞：4)

~~为什么 c 题这么简单却把 d 题题解入口关了。~~

## 思路

这道题经典的 BFS。

什么是 BFS？BFS 即广度优先搜索，对于每一个符合条件的点，我们都寻找他的上下左右四个点，去寻找下一个满足条件的点，并把他加入到一个容器里面方便下一次求解。那么什么容器可以先进先出呢，没错就是队列，于是我们就可以用队列来解决广度优先搜索的题目。

关于这一道题安排的 BFS，我们可以发现在题目中提到我们在地板上放置若干个加湿器，每个加湿器可以触及到的范围，我们可以设每一个加湿器是一个起点，搜索可以触及到的点，这道题就迎刃而解了。


## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int dx[] = {1, -1, 0, 0}; // 右、左、下、上
const int dy[] = {0, 0, 1, -1}; // 右、左、下、上
char grid[1005][1005];
bool vis[1005][1005];
int main() {
    int H, W, D;
    cin >> H >> W >> D;
    for (int i = 0; i < H; ++i) {
        cin >> grid[i];
    }
    queue<pair<int, int>> q;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (grid[i][j] == 'H') {
                q.push({i, j});//每一个加湿器入队 
                vis[i][j] = true; // 加湿器位置标记为加湿
            }
        }
    }

    // BFS可以算作模板了。
    int steps = 0;
    while (!q.empty() && steps < D) {//队列不为空且范围不到 D
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            auto x = q.front().first;
            auto y = q.front().second;
            q.pop();
            for (int d = 0; d < 4; ++d) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                if (nx >= 0 && nx < H && ny >= 0 && ny < W &&
				 !vis[nx][ny] && grid[nx][ny] == '.') {//边界条件、是否访问过、是否为地板不是墙
                    vis[nx][ny] = true;//标记走过了
                    q.push({nx, ny});//入队
                }
            }
        }
        steps++;
    }

    // 统计加湿的地板单元格数量
    int cnt = 0;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (vis[i][j]) {
                cnt++;
            }
        }
    }
    cout << cnt << endl;
    return 0;
}

```

---

## 作者：FlowerAccepted (赞：3)

## 前言

赛时的蒟蒻居然不会 BFS，用 DFS 使劲剪枝还是 $\small{\text{\colorbox{#000055}{\color{#ffffff}{TLE}}}}$ 了。

[这个帖子](https://www.luogu.com.cn/discuss/1016710)中大佬 @[da_ke](https://www.luogu.com.cn/user/766675) 就有回复：

> @FlowerAccepted 用 DFS 不能保证深度相同，不可取。用 BFS 可以保证宽搜时每层的最短路相同，所以被访问的点的最短路就确定了，以后访问的都没这次的优。所以可以不用访问第二次。
> 
> DFS 不可取吧。

## 解题思路

### BFS 算法
这个题可以当之无愧的成为多源 BFS 算法板子题。

首先介绍一下 BFS 算法。它的全称是 Breadth-First Search（广度优先搜索）。它的原理就是一层一层拓展已遍历的节点，达到搜索的效果。它的实现需要借助队列的帮助。

具体来讲，将始发的若干节点入队，每次循环让队首节点出队，并将可到达的节点入队，标记访问过以防止重复访问和死循环。重复执行到队列为空，这个联通域就遍历完了。

### 大致思路

注意到一个地板单元格可能会被多次遍历，但能拓展出最多地板单元格的访问一定是剩余距离最大，即访问来源加湿器单元格与当前地板单元格的曼哈顿距离最小的访问。再注意到因为 BFS 是一层一层遍历的，所以后面的遍历总没有前面的优。

一旦访问到一个未标记的地板单元格，就立即入队并标记，后面如果访问到标记的单元格就可以跳过了。

### 实现细节

我们使用 `STL` 中的 `queue` 定义一个队列 $q$。标准库好闪，拜谢标准库。

再定义 $dx$、$dy$ 数组，存标记和下一步的变换

```cpp
int
dx[] = { 1, -1,  0,  0},
dy[] = { 0,  0,  1, -1};
```

为了方便存储每一个单元格，我们定义一个结构体 `Node{int x, y, s}`，其中 $x$、$y$ 代表此单元格的坐标，$s$ 代表与加湿器的距离。

首先在输入第 $i$ 行第 $j$ 列的单元格时判断这个单元格是否是加湿器（`H`），如果是，使 `Node {i, j, 0}` 入队；

输入完成后，进行 BFS 操作。

先令 $p$ 为队首单元格，标记 $p$，然后对于每一个 $0 \le i < 4$，检查 $a_{p.x + dx_i, p.y + dy_i}$ 是否为地板单元格（`.`），如果是则检查 $p.s$ 是否小于等于 $d$，如果是则将 `{p.x + dx[i], p.y + dy[i], p.s + 1}` 入队，让 $p$ 出队。

重复执行这个操作直到 $q$ 为空，最后遍历 $vis$，遇到标记就将答案加一，遍历结束后输出答案即可。

## 代码呈现

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

struct Node {
    int x, y, s;
};
char a[1005][1005];
bool vis[1005][1005];
int d,
dx[] = { 1, -1,  0,  0},
dy[] = { 0,  0,  1, -1};
queue<Node> q;

void bfs() {
    while (!q.empty()) {
        Node p = q.front();
        vis[p.x][p.y] = 1;
        for (int i = 0; i < 4; i ++) {
            if (a[p.x + dx[i]][p.y + dy[i]] == '.' && p.s < d && !vis[p.x + dx[i]][p.y + dy[i]]) {
                q.push({p.x + dx[i], p.y + dy[i], p.s + 1});
            }
        }
        q.pop();
    }
}

int main() {
    int h, w, ans = 0;
    cin >> h >> w >> d;
    for (int i = 1; i <= h; i ++) {
        for (int j = 1; j <= w; j ++) {
            cin >> a[i][j];
            if (a[i][j] == 'H') {
                q.push({i, j, 0});
                vis[i][j] = 1;
            }
        }
    }
    bfs();
    for (int i = 1; i <= h; i ++) {
        for (int j = 1; j <= w; j ++) {
            if (vis[i][j]) {
                ans ++;
            }
        }
    }
    cout << ans;
    return 0;
}

```

至此，本题 Accepted。

## 复杂度分析

输入、遍历 $vis$ 数组的时间复杂度均为 $O(HW)$，BFS 在最坏情况（全是地板且都能被访问到）时的时间复杂度也是 $O(HW)$，但一般情况下不会这么大。

综合来看，算法的时间复杂度是 $O(HW)$。

---

## 作者：Walrus (赞：2)

这个题就是 dfs 和 bfs 本质不同的问题。

如果直接 dfs 记忆化搜索不难发现一个问题，本来有些点是可达的，但是需要通过以前已经被标记的点从而变得不可达，所以考虑怎么改变记搜的策略。

记搜的本质是对每个 $S_{i,j}=H$ 为起点跑一遍记搜，会存在搜不到的情况，因为在 dfs 时递归是有先后顺序的，dfs 是直接把一个点给搜完然后再搜下一个点，也就是对于每一个点的「扩散过程」。而 bfs 避免了这个问题，考虑把所有起点扔进队列，那么答案会一层一层扩展，而不会出现 dfs 的问题，同样也是记搜，由于每个点只会被搜到一次，所以复杂度为 $O(NM)$。

整张图最后的结果就是所有点依次扩展 $k$ 层的样子，而不是每一个点扩展 $k$ 层，注意「依次扩展」和「每一个点扩展」是不同的，在顺序上有差异。

code

```cpp
rep(i, 1, n) rep(j, 1, m) if(s[i][j] == 'H') q.push({i, j, k});
while(q.size()) {
	int x = q.front().x, y = q.front().y, k = q.front().k;
	q.pop();
	if(vis[x][y]) continue;
	vis[x][y] = 1;
	if(k <= 0) continue;
	rep(i, 0, 3) {
		int xx = x + dx[i], yy = y + dy[i];
		if(xx < 1 || xx > n || yy < 1 || yy > m || s[xx][yy] == '#') continue;
		q.push({xx, yy, k - 1});
	}
}
```

---

## 作者：sjh0626 (赞：2)

## 题意概括

给定一个 $H$ 行 $W$ 列的表格和步数限制 $d$，定义 $(i,j)$ 为从上到下的第 $i$ 行的从左到右的第 $j$ 列的单元格。

如果单元格 $(i,j)$ 为 `.`，则单元格为空，如果单元格 $(i,j)$ 为 `#`，则单元格有障碍物，如果单元格 $(i,j)$ 为 `H`，则单元格有加湿器。

对于每一个加湿器，它能移动到其他相邻单元格（上、下、左、右）不经过有障碍物的单元格，并且步数 $\le d$ 的一条路线上的单元格都将被标记为加湿。

请你计算总共被加湿的单元格的个数。

## 思路分析

本质上是一个多源 BFS，我们可以直接套上 BFS 的模板，时间复杂度 $O(NM)$。

## 代码解析

```cpp
#include<bits/stdc++.h>
#define sjh0626s return
#define code 0
using namespace std;
int n,m,k,dx[4]={0,0,1,-1},dy[4]={1,-1,0,0},cnt;
char g[1010][1010];
bool humid[1010][1010];
struct node{
	int x,y,step;
};
void bfs(){
	bool vis[1010][1010]={0};
	queue<node>q;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(g[i][j]!='H')continue;
			q.push({i,j,0});
			vis[i][j]=1;
			humid[i][j]=1;
		}
	}
	while(!q.empty()){
		node u=q.front();
		q.pop();
		if(u.step==k)continue;
		for(int i=0;i<4;i++){
			int nx=u.x+dx[i],ny=u.y+dy[i];
			if(vis[nx][ny]||nx<1||nx>n||ny<1||ny>m||g[nx][ny]=='#')continue;
			humid[nx][ny]=vis[nx][ny]=1;
			q.push({nx,ny,u.step+1});
		}
	}
}
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>g[i][j];
		}
	}
	bfs();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cnt+=humid[i][j];
		}
	}
	cout<<cnt;
	sjh0626s code;
}
```

---

## 作者：SegmentTree_ (赞：2)

题目中格子被加湿的条件可以看成“有至少一个加湿器格子与它的最短路径长度小于等于 $D$”。  
所以可以从每个格子向它上下左右的四个格子连边（注意 `#` 不要连），然后建一个源点向所有加湿器格子连边，最后跑一遍最短路，看距离是否小于等于 $D$ 就好了。  
code:  
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned ll
#define ui unsigned int
#define i128 __int128
#define lid (id << 1)
#define rid (id << 1 | 1)
const int N = 1e6+5;
namespace tianyu{
	int h, w, d;
	int n;
	#define gid(i, j) ((((i) - 1) * w) + (j) + 1)
	char mp[1001][1001];
	vector<int> G[N];
	int dis[N];
	bool vis[N];
	void dij(){
		memset(dis, 0x3f, sizeof dis);
		dis[1] = -1;
		priority_queue<pair<int, int>> pq;
		pq.emplace(-1, 1);
		while (pq.size()){
			int u = pq.top().second;
			pq.pop();
			vis[u] = 1;
			for (int v : G[u]){
				if (dis[v] > dis[u] + 1){
					dis[v] = dis[u] + 1;
					if (!vis[v]) pq.emplace(-dis[v], v);
				}
			}
		}
	}
	void awa(){
		cin >> h >> w >> d;
		n = h * w + 1;
		for (int i = 1;i <= h;i++){
			for (int j = 1;j <= w;j++){
				cin >> mp[i][j];
				int id = gid(i, j);
				if (mp[i][j] == 'H') G[1].emplace_back(id);
				if (mp[i][j] != '#'){
					if (i > 1 && mp[i - 1][j] != '#') G[id].emplace_back(gid(i - 1, j));
					if (j > 1 && mp[i][j - 1] != '#') G[id].emplace_back(gid(i, j - 1));
					if (i < h && mp[i + 1][j] != '#') G[id].emplace_back(gid(i + 1, j));
					if (j < w && mp[i][j + 1] != '#') G[id].emplace_back(gid(i, j + 1));
				}
			}
		}
		dij();int ans = 0;
		for (int i = 1;i <= h;i++){
			for (int j = 1;j <= w;j++){
				if (mp[i][j] != '#' && dis[gid(i, j)] <= d) ++ans;
			}
		}
		cout << ans;
	}
}
signed main(){
	int T = 1;
	while (T--) tianyu::awa();
	return 0;
}
```

---

## 作者：xyx404 (赞：2)

## 思路：
多源 bfs。

把每一个加湿器看做一个起点，求他们走 $D$ 步最多可以走到几个格子。

对每一个加湿器的坐标进行 bfs。

bfs 模版里的标记数组要修改成 `int` 类型，并且标记的是到达这个位置的最小步数。  
如果到达这个点时的步数小于标记的步数，才可以继续往下搜，因为只有还可以走的步数大于原本可以走的步数，才有可能走到更多的点，否则走到的点只会是走过的点。  
其余的就是模版了。


## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long
char s[1100][1100];
int H,W,D;
int bj[1100][1100];
struct node{
	int x,y,step;
};
void bfs(int x,int y){
	queue<node>dl;
	dl.push({x,y,0});
	while(dl.empty()==0){
		node tamp=dl.front();dl.pop();
		int step=tamp.step;
		if(bj[tamp.x][tamp.y]<=step)continue;
		bj[tamp.x][tamp.y]=step;
		if(tamp.step==D){
			continue;
		}
		if(s[tamp.x][tamp.y+1]=='.'){
			dl.push({tamp.x,tamp.y+1,step+1});
		}
		if(s[tamp.x][tamp.y-1]=='.'){
			dl.push({tamp.x,tamp.y-1,step+1});
		}
		if(s[tamp.x+1][tamp.y]=='.'){
			dl.push({tamp.x+1,tamp.y,step+1});
		}
		if(s[tamp.x-1][tamp.y]=='.'){
			dl.push({tamp.x-1,tamp.y,step+1});
		}
	}
}
int main(){
	cin>>H>>W>>D;
	memset(bj,100,sizeof(bj));
	for(int i=1;i<=H;i++){
		for(int j=1;j<=W;j++)cin>>s[i][j];
	}
	for(int i=1;i<=H;i++){
		for(int j=1;j<=W;j++){
			if(s[i][j]=='H'){
				s[i][j]='.';
				bfs(i,j);
			}
		}
	}
	int an=0;
	for(int i=1;i<=H;i++){
		for(int j=1;j<=W;j++){
			if(bj[i][j]!=1684300900)an++;
		}
	}
	cout<<an;
	return 0;
}

```

---

## 作者：jiangjiangQwQ (赞：1)

### 思路
与前两题的思路相同，意思是从一个湿水器出发可以到曼哈顿距离不超过 $d$ 的位置，有墙不能走。于是就可以将所有湿水器加入队列跑广搜，用一个标记数组记录到达这个点的剩余最大步数，这个用来优化广搜，如果一个点向外扩展时发现当前步数比下个要去的点的记录值要小，那么以这个点过去再进行往后几次扩展肯定是不优的，否则我们可以直接更新标记数组为当前步数，最后统计所有被遍历过的点即可。
### 代码
```cpp
#include<bits/stdc++.h>
#include<cmath>
using namespace std;
#define int long long

const int N=1e3+6;
int h,w,d;
string s[N];int ans;
int dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
struct node{int x,y,step;};
queue<node> q;int vis[N][N];
bool record[N][N];
void bfs(){
    while(q.size()){
        node u=q.front();q.pop();
        record[u.x][u.y]=1;
        if(u.step==0) continue;
        for(int i=0;i<4;i++){
            int tx=u.x+dir[i][0],ty=u.y+dir[i][1];
            if(tx<=h&&tx>=1&&ty>=0&&ty<w&&s[tx][ty]!='#'&&u.step-1>vis[tx][ty]){
                vis[tx][ty]=u.step-1;q.push((node){tx,ty,u.step-1});
            }
        }
    }
}
signed main(){
    cin>>h>>w>>d;memset(vis,-1,sizeof vis);
    for(int i=1;i<=h;i++) cin>>s[i];
    for(int i=1;i<=h;i++){
        for(int j=0;j<w;j++){
            if(s[i][j]=='H') q.push((node){i,j,d}),vis[i][j]=d;
        }
    }bfs();
    for(int i=1;i<=h;i++){for(int j=0;j<w;j++){ans+=record[i][j];}}
    cout<<ans;
    return 0;
}
```

---

## 作者：ljk8886 (赞：1)

# 题目大意
给你一个 $n \times m$ 的矩阵。`#` 代表墙壁，`.` 代表空地，`H` 代表加湿器。

若一个方格可以由至少一个加湿器 $D$ 步之内到达，则该方格被视为加湿方格。**注意：任何带有加湿器的方格也是加湿方格。**

求：加湿方格的个数。

# 题目分析
有一个很明显的思路，从每一个加湿器一个一个进行 BFS。但显然会超时。其实，我们可以把所有加湿器放进同一个队列里，这样只需要一次 BFS，就求出来加湿方格的个数了。

# 代码
```cpp
#include <bits/stdc++.h>
#define ft first
#define sd second
#define endl '\n'
#define pb push_back
#define md make_pair
#define gc() getchar()
#define pc(ch) putchar(ch)
#define umap unordered_map
#define pque priority_queue
using namespace std;
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 bint;
typedef pair<int, int> pii;
typedef pair<pii, int> pi1;
typedef pair<pii, pii> pi2;
const int INF = 0x3f3f3f3f;
inline ll read()
{
	ll res = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') f = (ch == '-' ? -1 : f), ch = getchar();
	while (ch >= '0' && ch <= '9') res = res * 10 + ch - '0', ch = getchar();
	return res * f;
}
inline void write(ll x)
{
	if (x < 0) x = -x, pc('-');
	if (x > 9) write(x / 10);
	pc(x % 10 + '0');
}
inline void writech(ll x, char ch) { write(x), putchar(ch); }
const int N = 1e3 + 5;
char ch[N][N];
int n, m, d;
bool check(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m; } // 判断这个点有没有出界
int dx[] = {1, -1, 0, 0}; // 方向数组
int dy[] = {0, 0, 1, -1};
bool vis[N][N];
int main()
{
	queue<pi1> q; pi1 tmp;
	n = read(), m = read(), d = read();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			cin >> ch[i][j];
			if (ch[i][j] == 'H') // 加湿方格
			{
				tmp = md(md(i, j), 0);
				q.push(tmp);
			}
		}
	while (!q.empty())
	{
		tmp = q.front(); q.pop();
		int x = tmp.ft.ft, y = tmp.ft.sd, step = tmp.sd;
		if (step > d) break;
		vis[x][y] = true; // 标记
		for (int i = 0; i < 4; i++)
		{
			int nx = x + dx[i], ny = y + dy[i];
			if (!check(nx, ny) || ch[nx][ny] == '#' || vis[nx][ny]) continue; // 不合法
			pi1 ttmp = md(md(nx, ny), step + 1);
			q.push(ttmp); // 入队
		}
	}
	int ans = 0; // 统计加湿方格的个数
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			ans += vis[i][j];
	write(ans);
	return 0;
}
```

---

## 作者：hwc2011 (赞：1)

显然这道题每个加湿器都做一遍深搜或广搜的话，会炸，当然也可能会卡过。  
但是我们可以吧所有加湿器的坐标和当前还能走的步数丢进一个队列里，让每个可以走到的单元格只进一次队列，就可以做到 $O(NM)$ 的时间复杂度了，可过。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,d,b[1005][1005];
char a[1005][1005];
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
struct Node{
	int x,y,dis;
};
queue<Node>q;
signed main(){
	cin>>n>>m>>d;
	for(int i=1;i<=n;i++) scanf("%s",a[i]+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='H'){
				q.push({i,j,d});
				b[i][j]=1;
			}
		}
	}
	int ans=0;
	while(!q.empty()){
		int x=q.front().x,y=q.front().y,dis=q.front().dis;
		q.pop();
		ans++;
		if(dis==0) continue;
		for(int i=0;i<4;i++){
			int xx=x+dx[i],yy=y+dy[i];
			if(xx<1||yy<1||xx>n||yy>m||a[xx][yy]=='#'||b[xx][yy]) continue;
			b[xx][yy]=1;
			q.push({xx,yy,dis-1}); 
		}
	}
	cout<<ans;
} 
```

---

## 作者：hjyowl (赞：1)

### 思路

宽度优先搜索。

队列里，先把所有的加湿器的位置扔进去。

然后拿出队列头部的东西，步数小于等于 $k$ 时去扩散。

最后数一下有多少个被染了色的就行了。

时间复杂度：$\Theta(n\times m)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};
const int N = 5010;
char g[N][N];
bool st[N][N];
int main(){
	int n,m,k;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i ++ ){
		for (int j = 1; j <= m; j ++ ){
			cin >> g[i][j];
		}
	}
	queue<pair<pair<int,int>,int>>q;
	for (int i = 1; i <= n; i ++ ){
		for (int j = 1; j <= m; j ++ ){
			if (g[i][j] == 'H'){
				q.push({{i,j},0});
				st[i][j] = 1;
			}
		}
	}
	while (q.size()){
		auto [t,stt] = q.front();
		q.pop();
		int x = t.first,y = t.second;
		if (stt >= k){
			continue;
		}
		for (int i = 0; i < 4; i ++ ){
			int gx = x + dx[i],gy = y + dy[i];
			if (gx >= 1 && gx <= n && gy >= 1 && gy <= m && !st[gx][gy] && g[gx][gy] != '#'){
				st[gx][gy] = 1;
				q.push({{gx,gy},stt + 1});
			}
		}
	}
	int res = 0;
	for (int i = 1; i <= n; i ++ ){
		for (int j = 1; j <= m; j ++ ){
			if (st[i][j] && g[i][j] != '#'){
				res ++; 
			}
		}
	}
	cout << res;
	return 0;
}
```

---

## 作者：Cosine_Func (赞：1)

很好的 BFS。对于每个加湿器单元格，将其加入队列和加湿集合。使用队列进行 BFS，从队列中取出一个单元格，检查其上下左右四个方向的相邻单元格。如果相邻单元格是地板且未被访问过，并且移动步数不超过 $D$，则将其加入队列和加湿集合。最后输出集合大小即可。

参考代码：
```python
from collections import deque
def count_humid_cells(H, W, D, grid):
    queue = deque()
    humid_set = set()
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    for i in range(H):
        for j in range(W):
            if grid[i][j] == 'H':
                queue.append((i, j, 0))
                humid_set.add((i, j))
    while queue:
        x, y, steps = queue.popleft()
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            if 0 <= nx < H and 0 <= ny < W and grid[nx][ny] == '.' and (nx, ny) not in humid_set:
                if steps + 1 <= D:
                    queue.append((nx, ny, steps + 1))
                    humid_set.add((nx, ny))
    return len(humid_set)
H, W, D = map(int, input().split())
grid = [input().strip() for _ in range(H)]
result = count_humid_cells(H, W, D, grid)
print(result)
```

---

## 作者：lucasincyber (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc383_c)
## 思路
我们可以把问题转化一下。这道题实际上要求的是有多少个点，和每一个加湿器的距离的最小值是否 $\le d$。那这就是一个多源最短路，其中起点就是所有加湿器的位置。

跑一遍 bfs 即可。最终暴力遍历整个网格图求答案。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int h, w, d, ans;
char mp[N][N];
int dist[N][N];
bool vis[N][N];
queue<pair<int, int> > q;
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

int main()
{
	memset(dist, 0x3f, sizeof(dist));
	scanf("%d%d%d", &h, &w, &d);
	for (int i = 1; i <= h; i++)
	{
		for (int j = 1; j <= w; j++)
		{
			cin >> mp[i][j];
			if (mp[i][j] == 'H')
			{
				q.push({i, j});
				dist[i][j] = 0;
			}
		}
	}
	while (q.size())
	{
		int x = q.front().first, y = q.front().second;
		q.pop();
		if (vis[x][y]) continue;
		vis[x][y] = 1;
		for (int i = 0; i < 4; i++)
		{
			int bx = x + dx[i], by = y + dy[i]; 
			if (bx <= 0 || bx > h || by <= 0 || by > w || dist[bx][by] != 0x3f3f3f3f || vis[bx][by] || mp[bx][by] == '#') continue;
			dist[bx][by] = dist[x][y] + 1;
			q.push({bx, by});
		}
	}
	for (int i = 1; i <= h; i++)
		for (int j = 1; j <= w; j++)
			if (dist[i][j] <= d) ans++;
	printf("%d\n", ans);
	return 0;
}

```

---

## 作者：long_long__int (赞：0)

赛时死磕 DFS 直接 T 飞……

# 题目解法

用 BFS。因为 DFS 会 TLE，怎么优化都会 TLE 几个测试点。在输入的时候直接判断一下，如果是 `H` 就直接把坐标放进队列里，然后搜索一遍，时间复杂度 $O(HW)$，不会超时。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int h,w,d;
char ch[1005][1005];
bool vis[1005][1005];
int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
struct node{
	int x,y,d;
};
queue<node>q;
int main(){
	cin>>h>>w>>d;
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			cin>>ch[i][j];
			if(ch[i][j]=='H') q.push({i,j,0}),vis[i][j]=true;
		}
	}
	while(q.size()){
		int x=q.front().x,y=q.front().y,xd=q.front().d;
		q.pop();
		for(int i=0;i<4;i++){
			int nx=x+dx[i],ny=y+dy[i];
			int nd=xd+1;
			if(nd<=d and nx>=1 and nx<=h and ny>=1 and ny<=w and ch[nx][ny]!='#' and !vis[nx][ny]){
				vis[nx][ny]=true;
				q.push({nx,ny,nd});
			}
		}
	}
	int ans=0;
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			ans+=vis[i][j];
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：stripe_python (赞：0)

【模板】多源 01-BFS。

把所有加湿器都扔进队列跑 BFS 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

#define pos pair<int, int>
#define x first
#define y second

int n, m, d;
char s[N][N];
queue<pos> q;
int dis[N][N];

int dirx[] = {0, 1, -1, 0, 0};
int diry[] = {0, 0, 0, 1, -1};

void _main() {
	cin >> n >> m >> d;
	memset(dis, 0x3f, sizeof(dis));
	for (int i = 1; i <= n; i++) {
		cin >> (s[i] + 1);
		for (int j = 1; j <= m; j++) {
			if (s[i][j] == 'H') dis[i][j] = 0, q.emplace(i, j);
		}
	}
	while (!q.empty()) {
		pos u = q.front(); q.pop();
		for (int idx = 1; idx <= 4; idx++) {
			int nx = u.x + dirx[idx], ny = u.y + diry[idx];
			if (nx <= 0 || ny <= 0 || nx > n || ny > m || s[nx][ny] == '#') continue;
			if (dis[nx][ny] > dis[u.x][u.y] + 1) {
				dis[nx][ny] = dis[u.x][u.y] + 1;
				q.emplace(nx, ny);
			}
		}
	}
	int res = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (dis[i][j] <= d) res++;
		}
	}
	cout << res;
}
```

---

## 作者：Hacker_Cracker (赞：0)

## ABC383C Humidifier 3 题解
### Solution
就是简单 bfs 加一点标记
思路如下：

首先，开一个 $dis$ 数组，记录 $(i,j)$ 点距离**最近一个**加湿器的距离。初始时，令 $dis_{i,j}$ 等于 $+\infty$，然后给所有加湿器格子的值赋为 $0$。

然后遍历地图，找到一个 `H` 点就开始 bfs。每次枚举四联通，判断是否在地图内、是否是 `.` 或者 `H`，符合条件就更新 $dis$ 数组，取步数最小值。

最后统计答案：如果这个点没有被走到，即 $dis_{i,j} \neq +\infty$，那么答案加一。

结束。
### [AC](https://www.luogu.com.cn/record/193459920) Code
```cpp
#include<iostream>
#include<queue>
#include<cstring>
using namespace std; 
const int N=1e3+10;
struct Node{
	int x;
	int y;
	int stp;
};
queue<Node>q;
int dx[]={0,0,0,1,-1};
int dy[]={0,1,-1,0,0};
int dis[N][N],n,m,d;
char mp[N][N];
void bfs(int sx,int sy){
	q.push({sx,sy,0});
	while(!q.empty()){
		Node tmp=q.front();
		q.pop();
		int x=tmp.x,y=tmp.y,stp=tmp.stp;
		if(stp>=d) continue;
		for(int i=1;i<=4;i++){
			int xx=x+dx[i],yy=y+dy[i];
			if(xx>=1&&xx<=n&&yy>=1&&yy<=m&&mp[xx][yy]!='#'&&dis[x][y]+1<dis[xx][yy]){
				dis[xx][yy]=dis[x][y]+1;
				q.push({xx,yy,stp+1});
			}
		}
	}
	return;
}
int main(){
	cin>>n>>m>>d;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>mp[i][j];
			dis[i][j]=1e9-(mp[i][j]=='H'?1e9:0);
		} 
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mp[i][j]=='H') bfs(i,j);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(dis[i][j]<=n*m) ans++;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：PigNotFound (赞：0)

首先，从每一个加湿器一起开始跑多源 bfs，求出每个点到最近加湿器的距离。

答案即为到最近加湿器距离小于 $D$ 的所有点。

代码：

```cpp
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;

const ll Pig = 1e3 + 10;

bitset<Pig> mp[Pig];
ll n, m, ds, f[Pig][Pig], ans = 0;

vector<pair<ll, ll> > humid;

bool check(ll i, ll j) {
    return (i >= 0 and j >= 0 and i < n and j < m and mp[i][j]);
}

void bfs() {
    queue<pair<pair<ll, ll>, ll> > q;
    for (auto i : humid)
        q.push({i, 0});
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        if (!check(p.first.first, p.first.second))
            continue;
        if (p.second >= f[p.first.first][p.first.second])
            continue;
        f[p.first.first][p.first.second] = p.second;
        q.push({{p.first.first, p.first.second + 1}, p.second + 1});
        q.push({{p.first.first, p.first.second - 1}, p.second + 1});
        q.push({{p.first.first + 1, p.first.second}, p.second + 1});
        q.push({{p.first.first - 1, p.first.second}, p.second + 1});
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> ds;
    memset(f, 0x3f, sizeof(f));
    for (ll i = 0; i < n; i++)
        for (ll j = 0; j < m; j++) {
            char c;
            cin >> c;
            if (c == '.')
                mp[i][j] = 1;
            if (c == 'H')
                mp[i][j] = 1, humid.emplace_back(i, j);
        }
    bfs();
    for (ll i = 0; i < n; i++)
        for (ll j = 0; j < m; j++)
            ans += (f[i][j] <= ds);
    cout << ans;
    return 0;
}

```

---

## 作者：cyq32ent (赞：0)

本题为多源 BFS 板子。开始时把所有加湿器推进队列，然后开始 BFS 即可。正确性是因为边权都为 $1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int H,W,D,A,dis[1010][1010];char S[1010][1010];
queue<pair<int,int>>Q;
int main(){
	cin>>H>>W>>D;memset(dis,0x3f,sizeof dis);
	for(int i=1;i<=H;i++)for(int j=1;j<=W;j++)cin>>S[i][j];
	for(int i=1;i<=H;i++){
		for(int j=1;j<=W;j++){
			if(S[i][j]=='H')Q.push({i,j}),dis[i][j]=0;
		}
	}while(Q.size()){
		auto u=Q.front();Q.pop();
		int i=u.first,j=u.second;
		const int dx[]={0,-1,0,1},dy[]={1,0,-1,0};
		for(int k=0;k<4;k++){
			int x=i+dx[k],y=j+dy[k];
			if(S[x][y]=='.'&&dis[i][j]+1<dis[x][y]){
				dis[x][y]=dis[i][j]+1;Q.push({x,y});
			}
		}
	}for(int i=1;i<=H;i++)for(int j=1;j<=W;j++)if(dis[i][j]<=D)A++;
	cout<<A<<endl;
	return 0;
}
```

---

## 作者：HuangBarry (赞：0)

方法：多源 BFS。  
实现：就是 BFS 模版，但是要在搜索前一次把所有起点都放入队列中，然后进行模版 BFS 即可。  
代码如下：
```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define Made return
#define by 0
#define Barry +0
#define fre(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
using ll=long long;
int h,w,d;
char Map[1111][1111];
bool f[1111][1111],vis[1111][1111];
ll ans=0;
int dx[]={0,0,-1,1};
int dy[]={1,-1,0,0};
struct node{
    int x,y,sum=0;
};
queue<node>q;
int main(){
    //fre("name");
    ios::sync_with_stdio(false);
    cin>>h>>w>>d;
    for(int i=1;i<=h;i++)
        for(int j=1;j<=w;j++){
            cin>>Map[i][j];
            if(Map[i][j]=='H'){
                q.push(node{i,j,0});//多源BFS一次把所有起点都放入队列中
                vis[i][j]=1;
                f[i][j]=1;
            }
        }
    while(!q.empty()){//就是BFS模版
        node u=q.front();
        q.pop();
        for(int i=0;i<4;i++){//四个方向
            int nx=u.x+dx[i];//新点x坐标
            int ny=u.y+dy[i];//新点y坐标
            if(nx>=1&&ny>=1&&nx<=h&&ny<=w&&Map[nx][ny]!='#'&&u.sum<d&&!vis[nx][ny]){//判断此点是否合法
                q.push(node{nx,ny,u.sum+1});//把下一步放到队列中
                vis[nx][ny]=1;//记录已遍历
                f[nx][ny]=1;//记录此点可被加湿
            }
        }
    }
    for(int i=1;i<=h;i++)//把所有可加湿的点统计
        for(int j=1;j<=w;j++)
            ans+=f[i][j];
    cout<<ans<<endl;
    Made by Barry;
}
```

---

## 作者：Liuhy2996 (赞：0)

## 思路
可以发现题目实际上是问有多少个点与某一个加湿器的最短路不超过 $D$，可以想到多源 bfs。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define x first
#define y second
const int N=2e3+10,inf=1e15;
int n,m,k,ans,d[N][N],dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
char c[N][N];
bool chk(int x,int y){return (x&&y&&x<=n&&y<=m&&c[x][y]!='#'&&d[x][y]==inf);}
queue<pair<int,int>>q;
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			cin>>c[i][j];
			if(c[i][j]=='H') q.push({i,j});
			else d[i][j]=inf;
		}
	while(!q.empty()){
		int x=q.front().x,y=q.front().y; q.pop();
		++ans;
		if(d[x][y]==k) continue;
		for(int i=0;i<4;++i)
			if(chk(x+dx[i],y+dy[i])) d[x+dx[i]][y+dy[i]]=d[x][y]+1,q.push({x+dx[i],y+dy[i]});
	}
	cout<<ans;
	return 0;
}
```

---

