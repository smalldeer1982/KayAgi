# [BalticOI 2012] 山峰 (Day1)

## 题目描述

有一个 $N \times M$ 大小的岛屿，每个点有不同的海拔。定义相邻为两个点横纵坐标差均不超过 $1$。定义路径为任意两个连续点都相邻的序列。定义平坦的区域是一组联通的海拔相同的点的极大集合，山峰是一个不与任何海拔更高的点相邻的平坦区域。

给出这个岛屿上每个点的海拔，你需要求出岛屿上所有的山峰与前往比其高度更高的山峰所需经过的最低点的海拔的最大值。

## 说明/提示

**【样例解释】** 

![](https://cdn.luogu.com.cn/upload/image_hosting/flr0h9rs.png)  
如上图所示，其中圆圈圈出的为山峰，从海拔为15的山峰前往其他山峰的一条路径用深色标出。

**【数据范围】**

- 对于 15% 的数据，满足 $\min (N,M)\leq 2$
- 对于 50% 的数据，满足 $P \leq 500$
- 对于 80% 的数据，满足 $P \leq 5000$
- 对于 100% 的数据，满足 $1 \leq N,M \leq 2000$，$N \times M \leq 10^5$，$1 \leq E_{i,j} \leq 10^6$

**【说明】**

译自 [BalticOI 2012 Day1 T3. Peaks](http://www.boi2012.lv/data/day1/eng/peaks.pdf)

## 样例 #1

### 输入

```
6 6
21 16 9 11 6 7
21 21 10 14 15 9
18 20 8 9 13 14
11 10 9 9 8 13
8 12 12 14 13 8
7 13 12 9 5 1```

### 输出

```
4
21 0
15 11
14 13
13 12```

# 题解

## 作者：Find_Yourself (赞：1)

通过观察，可以发现此题和最小生成树十分相似（两个地点之间途经的最小值最大）。

于是可以考虑这么做：

1. 通过 bfs 将每一个块预处理出来，并记录其编号、高度、类型（是否为高地）以及边缘的点。

2. 将每一个块按高度从大到小排序。

3. 依次枚举每个块：
	- 对于当前要处理的块，枚举其边界的所有点，看会与哪些已插入的块相连，同时用并查集找到他们的“祖先”，即该块所连接形成的连通块内最高的高地。然后除了最高的“祖先”，其他高地途经的最小值最大为当前块的高度。

	- 将这些集合合并，更新其“祖先”。
    
4. 排序并输出答案。

要注意的是，由于每个集合内最高的高地可能有多个，所以需要开个数组记录一下。

具体看代码吧。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2000 + 5, N2 = 1e5 + 5;
int n, m, a[N][N], id[N][N], fa[N2], vis[N2], dd[N2], dx[] = {0, 0, -1, 1, -1, -1, 1, 1}, dy[] = {-1, 1, 0, 0, -1, 1, 1, -1}, num[N2], tot = 0;
struct node{int id, h, type; vector<int> v;}b[N2]; //块 
struct node2{int i, j; node2(int i = 0, int j = 0):i(i), j(j){}};
struct node3{int h, minn;}ans[N2];
bool cmp(node x, node y) {return x.h > y.h;}
bool cmp2(int x, int y) {return b[x].h > b[y].h;}
bool cmp3(node3 x, node3 y) {if (x.h != y.h) return x.h > y.h; return x.minn > y.minn;}
int ff(int x) {return (fa[x] == x)?x:fa[x] = ff(fa[x]);}
queue<node2> q;
vector<int> tmp;
void bfs(int sx, int sy) {
	q.push(node2(sx, sy)); ++tot;
	b[tot].id = tot; b[tot].h = a[sx][sy];
	id[sx][sy] = tot;
	int f1 = 1; //该连通块是否为高地 
	while (!q.empty()) {
		node2 u = q.front(); q.pop();
		int f2 = 0; //该点是否在边缘上 
		for (int k = 0; k <= 7; ++k) {
			int tx = u.i + dx[k], ty = u.j + dy[k];
			if (tx < 1 || tx > n || ty < 1 || ty > m) continue;
			if (a[tx][ty] == a[sx][sy] && !id[tx][ty]) q.push(node2(tx, ty)), id[tx][ty] = tot;
			if (a[tx][ty] != a[u.i][u.j]) f2 = 1;
			if (a[tx][ty] > a[u.i][u.j]) f1 = 0;
		}
		if (f2) b[tot].v.push_back((u.i - 1) * m + u.j); 
	}
	b[tot].type = f1;
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m; for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) cin >> a[i][j];
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (!id[i][j]) bfs(i, j);
		}
	}
	int maxn = 0, cnt = 0;
	sort(b + 1, b + tot + 1, cmp);
	for (int i = 1; i <= tot; ++i) {
		fa[i] = i; dd[b[i].id] = i; maxn = max(maxn, b[i].h);
		num[i] = b[i].type;
	}
	for (int i = 1; i <= tot; ++i) if (b[i].h == maxn) ans[++cnt].h = maxn, ans[cnt].minn = 0; //先将最高的高地的答案处理了 
	for (int t = 1; t <= tot; ++t) {
		vis[t] = 1; //记录每个块是否已插入 
		tmp.clear(); tmp.push_back(t); //tmp记录与当前块相邻的块 
		for (int i = 0; i < b[t].v.size(); ++i) {
			int x = (b[t].v[i] - 1) / m + 1, y = b[t].v[i] % m;
			if (!y) y = m;
			for (int k = 0; k <= 7; ++k) {
				int tx = x + dx[k], ty = y + dy[k];
				if (tx < 1 || tx > n || ty < 1 || ty > m) continue;
				int d = ff(dd[id[tx][ty]]);
				if (vis[d] && d != t) tmp.push_back(d); //记录其下标 
			}
		}
		sort(tmp.begin(), tmp.end());
		tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end()); //去重 
		sort(tmp.begin(), tmp.end(), cmp2); //将其高度从大到小排序，方便后续处理 
		int fir = tmp[0], c = 0; //fir表示最高的高地 
		for (int i = 0; i < tmp.size(); ++i) {
			if (b[tmp[i]].type && num[tmp[i]]) {
				++c;
				if (c == 1) fir = tmp[i];
				else {
					if (b[tmp[i]].h == b[fir].h) { //高度一样，合并到fir 
						num[fir] += num[tmp[i]];
						num[tmp[i]] = 0;
					} else {
						for (int j = 0; j < num[tmp[i]]; ++j) ans[++cnt].h = b[tmp[i]].h, ans[cnt].minn = b[t].h; //记录答案 
						num[tmp[i]] = 0;
					}
				}
			}
		}
		for (int i = 0; i < tmp.size(); ++i) { //合并集合 
			if (tmp[i] != fir) {
				fa[tmp[i]] = fir;
			}
		}
	}
	sort(ans + 1, ans + cnt + 1, cmp3);
	cout << cnt << endl;
	for (int i = 1; i <= cnt; ++i) cout << ans[i].h << " " << ans[i].minn << endl;
	return 0;
}
```


---

## 作者：__Floze3__ (赞：0)

## 思路简述

题目中的输出格式很明显的提醒我们要把这道题分为两个部分：找到所有的山峰，以及求出走到海拔更高的山峰所经过的最低海拔最大值。接下来的题解也会以这两个部分分开来讲述。

### 第一部分

我们注意到，一个山峰是一个周围没有海拔比它高的连通块，我们不难想到用并查集维护这一点。我们对于每一个方格，遍历与它联通的方格所在的连通块，根据连通块所在的情况来更新状态。具体而言，若旁边的方格海拔比他高，那么当前方格所在的连通块必不可能是山峰；若旁边的方格与它的海拔相同，就合并两个连通块，同时更新联通块是否可能是山峰。代码如下：

```cpp
  // 初始化：ispeak （代表当前连通块是否可能是山峰） 全为真，每个方格的父亲为它本身。
  // 由于采用的是一维的输入方式，getid(x, y) 表示找到 (x, y) 在一维数组中的位置。
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      for (int k = 0; k < 8; ++k) {
        int nx = i + dx[k], ny = j + dy[k];
        if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
        if (a[getid(nx, ny)] > a[getid(i, j)])
          ispeak[find(getid(i, j))] = false; // 不可能是山峰
        else if (a[getid(nx, ny)] == a[getid(i, j)]) {
          // 合并，通过两个连通块的状态更新状态
          int fx = find(getid(nx, ny)), fy = find(getid(i, j));
          if (fx != fy) ispeak[fy] = ispeak[fx] && ispeak[fy], fa[fx] = fy;
        }
      }
    }
  }
```

当然，我们要给不同的山峰打上不同的标记记录下来，代码如下：

```cpp
  for (int i = 1; i <= n * m; ++i) {
    int ff = find(i); // 连通块编号
    if (!vis[ff] && ispeak[ff]) // 记录下每个山峰的连通块编号，并打上标记
      peak[++tot] = ff, rev[ff] = tot;
    vis[ff] = true;
  }
  for (int i = 1; i <= n * m; ++i)
    has[i] = rev[find(i)]; // 记录每个方格处于哪个山峰中
```

求出 has 数组之后，我们就可以去求每个山峰走到海拔更高的山峰所经过的最低海拔最大值。

### 第二部分

我们考虑按照海拔排序，从大到小在图上加入方格，通过对图的连通性的实时维护求出答案。我们考虑再一次使用并查集。我们需要明确 has 数组在这一部分的定义：**在这一个连通块内还没有得到答案的山峰编号**。假设新合并的两个连通块所剩的山峰高度不同，那么可以直接得出较矮的山峰的答案，那么合并后的 has 值只剩下了高的那个山峰；但如果两个山峰海拔相同呢？我们当然可以把数组换成 vector，搞启发式合并，但我采取的是另一种方法：对于山峰的编号也开一个并查集，在这种情况时直接在并查集上合并即可。理清了思路，我们可以写出以下的合并函数：

```cpp
il void merge(int x, int y, int d) {
  x = find(x), y = find(y); // 连通块的并查集
  if (x == y) return ;
  int nx = find2(has[x]), ny = find2(has[y]); // 山峰编号的并查集
  if (a[peak[nx]] == a[peak[ny]]) {
    fa[x] = y, fa2[nx] = ny;
    return ;
  }
  else if (a[peak[nx]] > a[peak[ny]]) ans[ny] = max(ans[ny], d), fa[y] = x;
  else ans[nx] = max(ans[nx], d), fa[x] = y;
  return ;
}
```

那么我们只需要不断的加入方格，实时更新连通性即可：

```cpp
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      b[getid(i, j)] = (node){a[getid(i, j)], i, j};
    }
  }
  std::sort(b + 1, b + 1 + n * m); // 这里按海拔从大到小排序
  for (int i = 1; i <= n * m; ++i) {
    int v = b[i].v, x = b[i].x, y = b[i].y;
    for (int j = 0; j < 8; ++j) {
      int nx = x + dx[j], ny = y + dy[j];
      // 注意这里需要判断相邻的点是否有被加入图中
      if (nx < 1 || nx > n || ny < 1 || ny > m || a[getid(nx, ny)] < v) continue;
      merge(getid(x, y), getid(nx, ny), v);
    }
  }
```

最后就可以愉快的统计答案了，排序输出即可。

## 代码

由于模拟赛时代码较长（有着极长的无用头文件），代码放在了[剪贴板](https://www.luogu.com.cn/paste/417mfjzg)中。

---

## 作者：ZHR100102 (赞：0)

一道大模拟，很暴力，也很难写。建议紫或蓝，标签为模拟、广度优先搜索、并查集。

# 思路

首先观察到答案取决于路线上的最低点，所以我们可以把所有点的高度丢进一个桶里，从大到小枚举，尝试更新答案。这应该是个挺经典的 trick 了。

所以我们先 BFS 一遍，找出所有是山峰的极大连通块，在里面随便找一个点标记一下。

然后接下来就是从大到小往一开始的空图中加点，每次加点的时候找到旁边八连通的点，如果已经加入图中，就连一条边，也就是把他们合并到一个连通块里。这个可以用并查集实现。

那么某个山峰的答案怎么统计？考虑把某个连通块的最高的山峰存进一个 vector 中，并且在合并的时候，做一个类似启发式合并的一个东西，把最高山峰的高度低的连通块的答案记录一下，然后将他们全部删除。如果两个连通块最高的山峰高度相同，就先不记录答案，把其中一个 vector 的山峰加到另一个 vector 里就可以了。

注意到这题有点卡空间，开 $10^6$ 的数组还会导致消耗多余的空间，所以我们用 unordered_map 存一下就可以把空间卡过去了。

# 代码

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
typedef pair<short,short> ps;
int n,m,nh;
unordered_map<int,int>h[2005],mh[2005],ans[2005];
vector<ps>d[1000010];
vector<pi>tot;
vector<ps>mg[2005][2005];
ps f[2005][2005];
bitset<2005>vis[2005],istop[2005];
int gox[]={0,0,1,1,1,-1,-1,-1};
int goy[]={1,-1,1,0,-1,1,0,-1};
void init()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			f[i][j]={i,j};
			mh[i][j]=0;
		}
	}
}
pi findf(pi x)
{
	pi fa=f[x.fi][x.se];
	if(fa.fi!=x.fi||fa.se!=x.se)f[x.fi][x.se]=findf(fa);
	return f[x.fi][x.se];
}
void combine(ps x,ps y)
{
	pi fx=findf(x),fy=findf(y);
	if(fx!=fy)
	{
		int ls=mh[fx.fi][fx.se],mr=mh[fy.fi][fy.se];
		if(ls>mr)
		{
			swap(ls,mr);
			swap(fx,fy);
		}
		if(ls<mr)
		{
			for(auto tmp:mg[fx.fi][fx.se])
			{
				ans[tmp.fi][tmp.se]=nh;
			}
		}
		else
		{
			for(auto tmp:mg[fx.fi][fx.se])
			{
				mg[fy.fi][fy.se].push_back(tmp);
			}
		}
		mg[fx.fi][fx.se].clear();
		mg[fx.fi][fx.se].shrink_to_fit();
		mh[fx.fi][fx.se]=mh[fy.fi][fy.se];
		f[fx.fi][fx.se]=fy;
	}
}
bool legal(int x,int y)
{
	return (x>=1&&x<=n&&y>=1&&y<=m);
}
void bfs(int sx,int sy)
{
	bool flag=1;
	queue<pi>q;
	q.push({sx,sy});
	vis[sx][sy]=1;
	while(!q.empty())
	{
		pi u=q.front();
		q.pop();
		int x=u.fi,y=u.se;
		for(int i=0;i<8;i++)
		{
			int tx=x+gox[i],ty=y+goy[i];
			if(legal(tx,ty))
			{
				if(h[tx][ty]>h[sx][sy])flag=0;
				if(vis[tx][ty]==0&&h[tx][ty]==h[sx][sy])
				{
					vis[tx][ty]=1;
					q.push({tx,ty});
				}
			}
		}
	}
	if(flag)
	{
		istop[sx][sy]=1;
		mg[sx][sy].push_back({sx,sy});
		mh[sx][sy]=h[sx][sy];
	}
}
void gettop()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(vis[i][j]==0)
			{
				bfs(i,j);
			}
		}
	}
}
bool cmp(pi x,pi y)
{
	return x>y;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>h[i][j];
			d[h[i][j]].push_back({i,j});
		}
	}
	init();
	gettop();
	nh=1000001;
	while(nh>=1)
	{
		for(auto tmp:d[nh])
		{
			int x=tmp.fi,y=tmp.se;
			for(int i=0;i<8;i++)
			{
				int tx=x+gox[i],ty=y+goy[i];
				if(legal(tx,ty))
				{
					if(h[tx][ty]>=nh)
					{
						combine({x,y},{tx,ty});
					}
				}
			}
		}		
		nh--;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(istop[i][j]==1)
			{
				tot.push_back({h[i][j],ans[i][j]});
			}
		}
	}
	cout<<tot.size()<<endl;
	sort(tot.begin(),tot.end(),cmp);
	for(auto tmp:tot)
	{
		cout<<tmp.fi<<' '<<tmp.se<<endl;
	}
	return 0;
}
```

# 后记

写完突然发现我们不用知道某个连通块里最高的山峰到底是哪个，所以可以不用启发式合并，只要记录最高山峰的个数就好了。

---

## 作者：MusicBox (赞：0)

首先将题意转化，我们要求出的是两两山峰之间的 “最大瓶颈路”（即路径上最小边最大的路径）。

首先将图缩成若干连通块，之间相邻的连边后，建出“最大生成树”，那么两个点之间的最大瓶颈路就是树上路径。

设连通块个数为 $k$，$k$ 最大为 $n\times m$，我们通过暴力统计两两山峰的最大瓶颈路有了一个 $\mathcal{O(k\log{k} + k^2)}$ 的做法。

考虑如何优化，我们发现在通过 kruskal 生成最大生成树的时候，每条边加进去连接两个连通块，若某个连通块内有没有更新答案的峰，且另外一个连通块的最高峰比它高的时候，就可以更新它的答案。

我们用 vector 存储一个连通块内没有更新答案的点集，然后启发式合并即可，复杂度 $\mathcal{O(k\log{k})}$。

code:

```cpp
int n, m, cnt, mnt;
int f[2005][2005], t[2005][2005], p[L], ans[L];
bool mou[L];
int dx[] = {0, 0, 1, -1, 1, -1, 1, -1};
int dy[] = {1, -1, 0, 0, 1, -1, -1, 1};
vector<pii> e[L];
vector<pair<int, pii> > edges;
vector<pii> Tans;

bool check(int x, int y) {
    if(x > n || y > m || x < 1 || y < 1) return false;
    return true;
}

void dfs(int x, int y, int id) { 
    t[x][y] = id;
    rep(i, 0, 7) if(check(x + dx[i], y + dy[i]) && f[x][y] == f[x + dx[i]][y + dy[i]] && !t[x + dx[i]][y + dy[i]]) {
        dfs(x + dx[i], y + dy[i], id);
    }
}

namespace Merge {
    vector<int> nds[L];
    int fa[L], siz[L];
    void init() {
        rep(i, 1, cnt) {
            fa[i] = i; if(mou[i]) nds[i].pb(i); siz[i] = 1;
        }
    }
    int getfa(int x) {
        return (x == fa[x]) ? x : (fa[x] = getfa(fa[x])); 
    }
    void merge(int a, int b, int c) {
        a = getfa(a), b = getfa(b);  
        if(siz[a] > siz[b]) swap(a, b);
        if(a == b) return ;
        fa[a] = b; siz[b] += siz[a];
        while(!nds[a].empty() && !nds[b].empty() && p[nds[a][nds[a].size() - 1]] < p[nds[b][0]]) ans[nds[a][nds[a].size() - 1]] = c, nds[a].pop_back();
        while(!nds[a].empty() && !nds[b].empty() && p[nds[b][nds[b].size() - 1]] < p[nds[a][0]]) ans[nds[b][nds[b].size() - 1]] = c, nds[b].pop_back();
        rep(i, 0, signed(nds[a].size() - 1)) nds[b].pb(nds[a][i]);
    }
}

signed main() {
    rd(n, m);    
    rep(i, 1, n) rep(j, 1, m) rd(f[i][j]);
    rep(i, 1, n) rep(j, 1, m) if(!t[i][j]) { dfs(i, j, ++ cnt); p[cnt] = f[i][j]; }
    rep(i, 1, n) rep(j, 1, m) {
        rep(k, 0, 7) {
            int x = i + dx[k], y = j + dy[k]; if(!check(x, y)) continue;
            if(t[x][y] != t[i][j]) e[t[i][j]].pb({t[x][y], min(f[x][y], f[i][j])});
        }
    }
    rep(i, 1, cnt) {
        sort(e[i].begin(), e[i].end());
        e[i].erase(unique(e[i].begin(), e[i].end()), e[i].end());
        for(auto v : e[i]) {
            edges.pb({v.second, {i, v.first}});
        }
    }
    rep(i, 1, cnt) {
        mou[i] = true;
        for(auto v : e[i]) if(p[v.first] > p[i]) mou[i] = false;
        if(mou[i]) mnt ++;
    }
    Merge::init();
    sort(edges.begin(), edges.end(), [](pair<int, pii> a, pair<int, pii> b) { return a.first > b.first; });
    rep(i, 0, signed(edges.size() - 1)) {
        Merge::merge(edges[i].second.first, edges[i].second.second, edges[i].first);
    }
    rep(i, 1, cnt) {
        if(mou[i]) {
            Tans.pb({p[i], ans[i]});
        }
    }
    int T = 0;
    rep(i, 1, cnt) {
        T += Merge::siz[i];
    }
    sort(Tans.begin(), Tans.end(), [](pii a, pii b) { return a > b; } );
    cout << mnt << endl;
    for(auto v : Tans) {
        cout << v.first << ' ' << v.second << '\n';
    }
    return 0;
}
```

---

