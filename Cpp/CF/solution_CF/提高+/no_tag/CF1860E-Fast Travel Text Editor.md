# Fast Travel Text Editor

## 题目描述

You are given a string $ s $ , consisting of lowercase Latin letters.

There's a cursor, initially placed between two adjacent letters of the string. The cursor can't be placed before the first or after the last letter.

In one move, you can perform one of three actions:

- move a cursor one position to the left (if that doesn't place it before the first letter);
- move a cursor one position to the right (if that doesn't place it after the last letter);
- let $ x $ be the letter immediately to the left of the cursor, and $ y $ be the letter immediately to the right of the cursor. Choose any pair of adjacent letters in the string such that the left of them is $ x $ and the right of them is $ y $ , and move the cursor to the position between these two letters.

You are asked $ m $ queries. In each query, you are given two integers $ f $ and $ t $ , which correspond to two valid positions of the cursor in the string. In response to the query, you have to calculate the minimum number of operations required to move the cursor from position $ f $ to position $ t $ .

## 样例 #1

### 输入

```
codecode
3
1 7
3 5
3 6```

### 输出

```
3
2
2```

## 样例 #2

### 输入

```
abcdefghij
3
1 9
9 1
5 5```

### 输出

```
8
8
0```

## 样例 #3

### 输入

```
aaaaaaaaaaaa
4
10 8
3 7
6 1
11 11```

### 输出

```
1
1
1
0```

# 题解

## 作者：EuphoricStar (赞：9)

没场切。/ng

考虑将原问题转成：

> 给长度为 $n$ 的序列 $a_{1 \sim n}$，你要从 $x$ 位置走到 $y$ 位置，每次你可以走到相邻位置，或走到与当前位置数字相同的位置，求最少步数。

这是一类经典问题，考虑建图后最短路解决。给每个位置建点 $p_i$，值域上每个数建点 $q_i$，然后连 $p_{i - 1} \leftrightarrow p_i$，边权为 $1$；连 $p_i \to q_{a_i}$，边权为 $1$；$q_{a_i} \to p_i$，边权为 $0$。图上 $p_x \to p_y$ 的最短路就是答案。

但是现在有 $m$ 组询问。对每个起点都跑一遍最短路显然不现实。观察到 $n, m$ 同阶，且 $a_i$ 值域较小（$a_i \le V = 26^2$），可以考虑 meet-in-the-middle 的思想。

我们发现，$p_x \to p_y$ 要么是只通过相邻位置走过去（此时步数为 $|x - y|$），要么必须经过至少一个 $q_i$。考虑对于 $\forall i \in [1, V], j \in [1, n]$，预处理出 $q_i \to p_j$ 的最短路 $f_{i, j}$ 和 $p_j \to q_i$ 的最短路 $g_{i, j}$，询问时我们枚举经过了哪个 $q_i$，答案就是 $\min(|x - y|, \min\limits_{i = 1}^V g_{i, x} + f_{i, y} + 1)$。

如果使用 01bfs 求最短路，时间复杂度就是 $O(nV)$。

[code](https://codeforces.com/contest/1860/submission/219458241)

---

## 作者：Purslane (赞：4)

# Solution

简单题。

考虑把该问题变为最短路问题。相邻两个节点之间有长度为 $1$ 的双向道路。

对于每个位置，都可以用一个字符二元组 $(c_1,c_2)$ 表示它左边和右边的字符。第三种移动方式（我们称之为“跃迁”好了）就是所有 $(c_1,c_2)$ 相同的节点之间两两连长度为 $1$ 的边。

这种连边方式是很经典的虚点优化建图。对于每个字符二元组我们都建立一个新的节点 $u$。所有字符二元组与此相同的原节点都和这个虚点有双向边。你可以考虑这样的边权为 $0.5$，不过这样你得用 Dijkstra。所以你可以让到虚点的边权是 $1$，出虚点的边权是 $0$，就可以用 01-BFS 了。

你想的是对于每个真实点跑最短路，这样复杂度是 $O(n^2)$，难以接受。

还有一种想法，就是以每个虚点为源跑最短路。假设虚点 $u$ 连着 $v_{1,2,3,\dots,x}$，那么我们知道 $u$ 到某个点的距离为 $dis$。但是我们的 $v$ 到这个点，可能经过 $u$ ，答案要加 $1$；但是可能不经过 $u$，答案不变。

我们发现，把虚点作为源点跑最短路，如果规定了一定“跃迁”那么就没有这个麻烦。考虑我们最终最优路径上，必定有一次跃迁，否则直接计算 $|s-t|$。那么我们枚举虚点的时候，把经过它当做第一次“跃迁”即可。

我们需要从 $s$ 走到 $v_i$，花费 $\min_{i=1}^x |s-v_i|$，这个可以提前 $O(n)$ 预处理，然后再花 $1$ 走到 $u$，最后花费 $dis_t$ 走到终点。

总体复杂度 $O(|\sum|^2(n+|\sum|^2))$，$|\sum|$ 表示字符集大小，这里是 $26$。足以通过本题。

代码（我的代码里面把出虚点的边当成 $1$ 了，有一点微小的改动）：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=6e4+10;
int n,m,tot,len,f[MAXN],t[MAXN],dis[MAXN],ans[MAXN],nrst[MAXN];
string S;
map<pair<char,char>,vector<int>> mp;
vector<pair<int,int>> G[MAXN];
void bfs(int s) {
	memset(dis,0x3f,sizeof(dis));	
	deque<int> q;
	q.push_back(s),dis[s]=0;
	while(!q.empty()) {
		int u=q.front();
		q.pop_front();
		for(auto pr:G[u]) {
			int to=pr.first,w=pr.second;
			if(dis[u]+w<dis[to]) {
				dis[to]=dis[u]+w;
				if(w==0) q.push_front(to);
				else q.push_back(to);	
			}
		}
	}
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>S>>n; ffor(i,1,n) cin>>f[i]>>t[i],ans[i]=abs(f[i]-t[i]);
	len=S.size(),tot=len-1,S="*"+S;
	ffor(i,1,len-1) mp[{S[i],S[i+1]}].push_back(i);
	ffor(i,1,len-2) G[i].push_back({i+1,1}),G[i+1].push_back({i,1});
	for(auto pr:mp) {
		++tot;
		for(auto id:pr.second) G[id].push_back({tot,0}),G[tot].push_back({id,1});	
	}
	int tmp=len-1;
	for(auto pr:mp) {
		++tmp,bfs(tmp);
		memset(nrst,0,sizeof(nrst));
		int lst=0;
		for(auto id:pr.second) {
			if(lst==0) ffor(i,1,id) nrst[i]=abs(id-i);
			else ffor(i,lst+1,id) nrst[i]=min(abs(i-lst),abs(i-id));
			lst=id;
		}
		ffor(i,lst+1,len-1) nrst[i]=abs(i-lst);
		ffor(i,1,n) ans[i]=min(ans[i],nrst[f[i]]+dis[t[i]]);
	}
	ffor(i,1,n) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：UniGravity (赞：3)

## Solution CF1860E Fast Travel Text Editor

### 题目思路
对于这种求最小代价的题目，我们可以将其转换到图上来做。（算是一种套路）

#### 如何建图
根据题意描述，设节点 $i$ 为光标在 $s_i$ 和 $s_{i+1}$ 之间，发现光标可以移到相邻位置，可得：
$$i\leftrightarrow i+1$$

接下来考虑跳转。发现如果直接连边，最坏会有 $n^2$ 条边（当 $s$ 的字符相同时），无法承受。   
此时增加中转点，我们可以连接 $i$ 和其相邻的字符组成的点，此时最坏情况下会有 $26^2$ 种边，可以承受。

放张图（样例）：

![](https://cdn.luogu.com.cn/upload/image_hosting/ihjn8xdd.png)

题目的每条边边权为 $1$ ，然而添加中转点后距离变为 $2$。

我们把图变为有向边，从 $i$ 前往中转点边权为 $1$，从中转点回到 $i$ 边权为 $0$。

然后在建完的图上直接对于每一个询问跑 [01-bfs](https://oi-wiki.org/graph/bfs/#%E5%8F%8C%E7%AB%AF%E9%98%9F%E5%88%97-bfs) 就可以了。

### 完整代码
```cpp
// E. Fast Travel Text Editor
#include <bits/stdc++.h>
using namespace std;

const int N = 50005, M = 2005;

vector< pair< int, bool > > edge[N + M];

char s[N];
int n, m;

int getpoint(char a, char b) {
    return 50005 + (a - 'A' + 1) + (b - 'A' + 1) * 30;
}

bool vis[N];
int dis[N];

// 0/1 bfs
void bfs(int s) {
    deque< int > q;
    
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x3f3f3f3f, sizeof(dis));
    
    q.push_front(s);
    dis[s] = 0;
    vis[s] = true;
    
    int x, y;
    bool f;
    
    while (!q.empty()) {
        x = q.front();
        q.pop_front();
        
        for (int i = 0; i < edge[x].size(); i++) {
            y = edge[x][i].first;
            f = edge[x][i].second;
            if (vis[y]) continue;
            
            vis[y] = true;
            if (f) {
                dis[y] = dis[x] + 1;
                q.push_back(y);
            }  else {
                dis[y] = dis[x];
                q.push_front(y);
            }
        }
    }
}

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    
    // build edge
    for (int i = 1; i < n; i++) {
        edge[i].push_back({i + 1, 1});
        edge[i + 1].push_back({i, 1});
        
        int x = getpoint(s[i], s[i + 1]);
        edge[i].push_back({x, 1});
        edge[x].push_back({i, 0});
    }
    
    scanf("%d", &m);
    int f, t;
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &f, &t);
        
        bfs(f);
        
        printf("%d\n", dis[t]);
    }
    return 0;
}
```

---

## 作者：arrow_king (赞：1)

很常规的套路题。

# Sol

考虑建图跑最短路。

考虑设节点 $1\sim(n-1)$ 是字符串中的节点，那么可以建出 $i\leftrightarrow i+1$，边权为 $1$；同时第三种操作要求我们把状态相同的位置联系起来，因此考虑建 $26\times26$ 个虚点代表每个状态。连边时由于靠保持边权和为 $1$，所以节点向对应虚点连边权为 $0$ 的边，虚点向节点连边权为 $1$ 的边。这样求最短路可以使用 01bfs。

但是从每个点出发跑 bfs 仍然不现实，还是利用虚点数量很少的限制。我们枚举每个虚点作为出发点，代表路径经过该虚点进行中转。因为虚点向下连边权为 $1$ 的边，所以统计答案的时候会认为进入虚点的边权为 $1$，因此要把这个多算的贡献去掉。复杂度是 $O(n\times|\Sigma|^2)$。

写的时候因为边数组没开够而显示 TLE /cf

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
#define N 50705
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
struct Edge {
	int nxt,u,v,w;
	Edge() {nxt=u=v=w=0;}
	Edge(int _nxt,int _u,int _v,int _w) {nxt=_nxt,u=_u,v=_v,w=_w;}
};
Edge edge[N*4];
int head[N],num_edge;
il void add_edge(int u,int v,int w) {
	edge[++num_edge]=Edge(head[u],u,v,w);
	head[u]=num_edge;
}
int n,q,dis[700][N];
char s[N];
bool vis[N];
il int Val(char c,char d) {return (c-'a')*26+(d-'a');}
int que[N*2],he,ta;
il void bfs(int S) {
	for(int i=1;i<n+676;i++) dis[S][i]=0x3f3f3f3f,vis[i]=0;
	he=N,ta=he;
	que[he]=S+n,dis[S][S+n]=0;
	while(he<=ta) {
		int u=que[he++];
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];i;i=edge[i].nxt) {
			int v=edge[i].v,w=edge[i].w;
			if(dis[S][v]>dis[S][u]+w) {
				dis[S][v]=dis[S][u]+w;
				if(vis[v]) continue;
				if(w==0) que[--he]=v;
				else que[++ta]=v;
			}
		}
	}
}
int main() {
	scanf("%s",s+1),n=strlen(s+1);
	for(int i=1;i<n;i++) {
		if(i!=1) add_edge(i,i-1,1);
		if(i!=n-1) add_edge(i,i+1,1);
		add_edge(i,n+Val(s[i],s[i+1]),0);
		add_edge(n+Val(s[i],s[i+1]),i,1);
	}
	for(int i=0;i<676;i++) bfs(i);
	q=read();
	while(q--) {
		int l=read(),r=read();if(l>r) swap(l,r);
		int ans=r-l;
		for(int i=0;i<676;i++) ans=min(ans,dis[i][l]+dis[i][r]-1);
		printf("%d\n",ans);
	}
	return 0;
}

```

---

## 作者：Xy_top (赞：1)

第一二种操作很显然，重要的是第三种操作。

为了方便描述，我们将每个点的字母组合抽象成一个数字，这个数字就是这个位置的字母的 $26$ 倍 $+$ 下一个字母。

如果对于数字相同的点两两建边就会爆炸，所以见虚点。（常用套路）

进入虚点的边权值为 $1$，出虚点权值为 $0$，每个点 $i$ 和 $i+1$ 之间还有一条边权为 $1$ 的边，这样就转换成了最短路问题。

$q$ 次任意两点最短路的问题十分困难，我知道的做法有两种：

其一是把图转换成树，然后就行了。

其二是预处理一些必经过的特殊点，恰巧是这题的解法。

对于每个虚点预处理到其他所有点的最短路，然后枚举两点间的最短路径经过哪个虚点，也可以一个都不经过，取个最小值即可。

代码：

```cpp
#include <bits/stdc++.h>
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
using namespace std;
char s[60005];
int n, m, len;
int k, sum;
int d[676][60005], pre[60005];
int d_[676][60005];
deque <int> Q;
struct Edge {int v, w, nxt;}a[500005];
void add (int u, int v, int w) {
	a[++ k] = {v, w, pre[u]};
	pre[u] = k;
}
void BFS (int s) {
	Q.push_back (s);
	d[s - len][s] = 0;
	while (!Q.empty () ) {
		int u = Q[0];
		Q.pop_front ();
		for (int i = pre[u]; i; i = a[i].nxt) {
			int v = a[i].v;
			if (d[s - len][v] > d[s - len][u] + a[i].w) {
				d[s - len][v] = d[s - len][u] + a[i].w;
				if (a[i].w == 0) Q.push_front (v);
				else Q.push_back (v);
			}
		}
	}
}
void BFS_ (int s) {
	Q.push_back (s);
	d_[s - len][s] = 0;
	while (!Q.empty () ) {
		int u = Q[0];
		Q.pop_front ();
		for (int i = pre[u]; i; i = a[i].nxt) {
			int v = a[i].v;
			if (max (u, v) - min (u, v) == 1 && max (u, v) != len) a[i].w = 0;
			if (d_[s - len][v] > d_[s - len][u] + 1 - a[i].w) {
				d_[s - len][v] = d_[s - len][u] + 1 - a[i].w;
				if (1 - a[i].w == 0) Q.push_front (v);
				else Q.push_back (v);
			}
			if (max (u, v) - min (u, v) == 1 && max (u, v) != len) a[i].w = 1;
		}
	}
}
signed main () {
	scanf ("%s", s + 1);
	len = strlen (s + 1);
	sum = len + 675;
	For (i, 1, len) s[i] -= 'a';
	For (i, 1, len - 2) {
		add (i, i + 1, 1);
		add (i + 1, i, 1);
	}
	For (i, 1, len - 1) {
		add (i, s[i] * 26 + s[i + 1] + len, 0);
		add (s[i] * 26 + s[i + 1] + len, i, 1);
	}
	For (i, len, sum) {
		For (j, 1, sum) d[i - len][j] = d_[i - len][j] = 1000000;
		if (!pre[i]) continue;
		BFS (i);
		BFS_ (i);
	}
	cin >> m;
	while (m --) {
		int f, t, ans;
		cin >> f >> t;
		ans = abs (f - t);
		For (i, len, sum) ans = min (ans, d[i - len][f] + d_[i - len][t]);
		cout << ans << '\n';
	}
	return 0;
}
```


---

## 作者：masonpop (赞：1)

首先朴素建图是显然的，把每个空隙当作一个点，互相可达的点就连边权为 $1$ 的边即可。但是这样边的数量是 $n^2$ 级别的，无法通过。

注意到，本质不同的小写字母对是很少的（可以哈希到一个 $26^2$ 内的正整数，并定义其为字母对的“权值”）。那么考虑**建立虚点**以降低边的数量。对于每个权值 $x$，将其和所有权值为 $x$ 的间隙连边。这样如果两个间隙 $i,j$ 的颜色均为 $x$，它们就可以通过 $i\to x\to j$ 的路线联通。但是这样虚点连出去的边的权值需要变为 $\frac{1}{2}$ 才能与原来的一次操作等价。为避免小数，先将边权扩倍。

但是这样建完图后跑 floyd 显然还是超时。注意到当不用第三类操作时答案是显然的。否则，考虑只找出每个虚点到其它点的距离。每次 dijkstra 还是太慢了。注意边权只有 $1$ 和 $2$ 两种，因此可以把边权为 $2$ 的边拆成两个边权为 $1$ 的边，然后 bfs 即可。本地有点卡常，实际 CF 跑的挺快的。[代码](https://codeforces.com/contest/1860/submission/219684876)。

---

## 作者：Anamnesis (赞：1)

用类似网络流建模的方式思考。

题意存在两种连边的关系：

- $i\leftrightarrow i+1$
- $i\leftrightarrow j\mid color_i=color_j$。

第一种边的数量级是 $\mathcal{O}(n)$ 的，直接连边即可。而第二种边可能是 $\mathcal{O}(n^2)$ 的（所有字符均相同时）。

考虑怎么在不破坏连边关系的情况下，减少边的数量。

颜色只有 $26^2$ 种，不妨对每个颜色建立虚点，向所有该颜色的点连边。这描述了相同的关系。只是连向虚点 $x$ 的边权应当是第一种边边权的一半，因为 $i\leftrightarrow x$、$x\leftrightarrow j$ 两条边才表示了 $i\leftrightarrow j$ 的关系。

边权设成 $0.5$ 有点阴间，不如把第一种边的边权改成 $2$，最后对答案除 $2$ 即可。

接下来的问题是我们不能跑全源最短路。但是可以注意到，只要不是只走第一种边，就必然经过至少一个虚点。因此分别以各虚点为起点，跑 $26^2$ 次单源最短路就可以了。而只走第一种边的情况下，答案是显然的。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  cin >> s;
  int m, n = s.size();
  for (char &i : s)
    i -= 'a';

  vector<vector<int>> idx(26 * 26);
  for (int i = 0; i < n - 1; ++i) {
    idx[s[i] + 26 * s[i + 1]].push_back(i);
  }
  vector<vector<array<int, 2>>> e(n + 26 * 26);
  for (int i = 0; i < n - 1; ++i) {
    e[i].push_back({i + 1, 2});
    e[i + 1].push_back({i, 2});
  }
  for (int id = 0; id < 26 * 26; ++id) {
    for (int i : idx[id]) {
      e[n + id].push_back({i, 1});
      e[i].push_back({n + id, 1});
    }
  }

  const int inf = 1e9 + 233, N = n + 26 * 26;
  function<vector<int>(int)> dijkstra = [&](int st) {
    vector<int> dis(N, inf);
    vector<int> vis(N);
    priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>> q;
    q.push({0, st});
    dis[st] = 0;
    while (!q.empty()) {
      st = q.top()[1];
      q.pop();
      if (vis[st])
        continue;
      vis[st] = 1;
      for (auto [ed, w] : e[st]) {
        if (dis[ed] > dis[st] + w) {
          dis[ed] = dis[st] + w;
          if (!vis[ed])
            q.push({dis[ed], ed});
        }
      }
    }
    return dis;
  };

  vector<vector<int>> dis(26 * 26);
  for (int l = 0; l < 26; ++l) {
    for (int r = 0; r < 26; ++r) {
      if (!idx[l + 26 * r].empty())
        dis[l + 26 * r] = dijkstra(n + l + 26 * r);
    }
  }

  cin >> m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    int ans = 2 * abs(u - v);
    for (int l = 0; l < 26; ++l)
      for (int r = 0; r < 26; ++r)
        if (!idx[l + 26 * r].empty())
          ans = min(ans, dis[l + 26 * r][u] + dis[l + 26 * r][v]);
    cout << ans / 2 << '\n';
  }
  return 0;
}
```

---

## 作者：冷却心 (赞：0)

[更好的阅读体验](https://ladexx.github.io/2025/03/17/CF1860E-sol/)。

[CF1860E. Fast Travel Text Editor](https://codeforces.com/problemset/problem/1860/E)。煎蛋题。

> 给定长度为 $n$ 的小写字母字符串，你有一个光标，光标在每一个时刻只能位于相邻两个字符之间：可以移动光标，有两种移动方式：
>
> - 往前（仅当光标不在第一个字符之后）或往后（仅当光标不在最后一个字符之前）一格
> - 移动到一个位置满足其两边的字符和光标所在位置两边的字符相同。
>
> $Q$ 次询问，指定 $s,t$，求从 $s$ 到 $t$ 光标最小移动次数。

先考虑一次询问怎么做。很 naive 的问题，首先往前往后可以直接连边，边权为 $1$，第二种移动方式连边数量太多，考虑对于每一种字符对建一个虚点，每个位置向他对应的左右字符对连一条边权 $1$ 的单向边，虚点反过来连一条边权为 $0$ 的单向边。此时两个点的最短路就是答案。单次询问时间复杂度 $O(n)$，使用 01 BFS 做最短路。

但是多次询问每次跑最短路显然不理想。我们注意到虚点个数只有 $26^2=676$ 个，并且两个点的最短路，要么直接一格一格移动到达，否则必须经过至少一个虚点。我们处理出 $f_{i,j},g_{i,j}$ 分别表示从第 $i$ 个虚点到 $j$ 位置的最短路和从 $j$ 位置到第 $i$ 个虚点的最短路，于是枚举中转的是哪个虚点即可，也就是说，对于一个询问 $(s,t)$，答案为：
$$
\text{Answer}=\min(|s-t|, \min_{i=1}^{676} f_{i,s} + g_{i,t}).
$$
总时间复杂度 $O((n+q)V^2)$，$V$ 表示字符集大小，使用 01 BFS 求最短路。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 8e4 + 10;
const int V = 26 * 26;
int n, m; char S[N]; 
vector<pair<int, int> > G[N], F[N]; int dist1[V][N], dist2[V][N];
int q[N * 2]; 
int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> (S + 1) >> m; n = strlen(S + 1);
	for (int i = 1; i < n; i ++) {
		if (i > 1) G[i].emplace_back(make_pair(i - 1, 1)), F[i].emplace_back(make_pair(i - 1, 1));
		if (i < n - 1) G[i].emplace_back(make_pair(i + 1, 1)), F[i].emplace_back(make_pair(i + 1, 1));
		int t = (S[i] - 'a') * 26 + S[i + 1] - 'a';
		G[i].emplace_back(make_pair(n + t + 1, 1)); G[n + t + 1].emplace_back(make_pair(i, 0));
		F[n + t + 1].emplace_back(make_pair(i, 1)); F[i].emplace_back(make_pair(n + t + 1, 1));
	}
	for (int i = 0; i < V; i ++) {
		for (int j = 1; j <= n + V; j ++) dist1[i][j] = dist2[i][j] = 1e9;
		dist1[i][n + i + 1] = dist2[i][n + i + 1] = 0;
		int fr = n + V, tl = n + V; q[fr] = n + i + 1;
		while (fr <= tl) {
			int u = q[fr ++];
			for (auto [v, w] : G[u]) if (dist1[i][v] > dist1[i][u] + w) {
				if (!w) { q[-- fr] = v; dist1[i][v] = dist1[i][u]; }
				else { q[++ tl] = v; dist1[i][v] = dist1[i][u] + 1; }
			}
		}
		fr = n + V, tl = n + V; q[fr] = n + i + 1;
		while (fr <= tl) {
			int u = q[fr ++];
			for (auto [v, w] : F[u]) if (dist2[i][v] > dist2[i][u] + w) {
				if (!w) { q[-- fr] = v; dist2[i][v] = dist2[i][u];  }
				else { q[++ tl] = v; dist2[i][v] = dist2[i][u] + 1; }
			}
		}
		
	}
	while (m --) {
		int u, v; cin >> u >> v; int Ans = abs(v - u);
		for (int i = 0; i < V; i ++) Ans = min(Ans, dist1[i][u] + dist2[i][v]);
		cout << Ans << "\n";
	}
	return 0;
}
```

---

## 作者：Kketchup (赞：0)

### [CF1860E Fast Travel Text Editor](https://codeforces.com/problemset/problem/1860/E)

- 最短路
- $\text{01-bfs}$

**Sol:** 考虑建图。对字符串中每个位置设点 $p$ 向两边连边，边权为 $1$。对于能跳到相同值的点之间，建立一个虚点 $q$（至多有 $26^2$ 个），节点连向虚点，边权为 $1$，虚点连向节点，边权为 $0$（如果都设为 $\frac{1}{2}$ 也可以，但是这样就只能用 $\text{dijkstra}$），然后跑 $\text{01-bfs}$ 求最短路。

但是每个点都跑一遍最短路复杂度会爆炸，观察路径形式可以发现，如果 $p_x$ 不是一步一步到 $p_y$，那么必然会经过 $q$ 点。而 $q$ 点总数很少，所以可以对于每个虚点 $q$ 预处理出它到所有 $p_i$ 的最短路。统计答案时枚举经过的 $q$ 点即可，注意虚点向节点连边边权为 $0$，所以真实长度需要加一。时间复杂度 $O(nV^2)$。

**Idea:** 首先观察到值域很小，求最小代价可以往建图方向上想一想。然后虚点建图，发现最短路上必定经过虚点后优化预处理。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
#define F(i,x,y) for(int i=(x);i<=(y);++i)
#define Fo(i,x,y) for(int i=(x);i>=(y);--i)
const int N=1e5+10,M=700;
int n,m;
string ch;
struct edge{
    int v,next,w;
}e[N<<3];
int head[N<<1],tot;
void add(int u,int v,int w){
    e[++tot]={v,head[u],w};
    head[u]=tot;
}
bool c[N];
int f[M][N];
vector<int> v;
deque<int> q;
void bfs(int s){
    q.push_back(s+n);
    f[s][s+n]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop_front();
        for(int i=head[u];i;i=e[i].next){
            int v=e[i].v,w=e[i].w;
            if(f[s][v]>f[s][u]+w){
                f[s][v]=f[s][u]+w;
                if(w) q.push_back(v);
                else q.push_front(v);
            }
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>ch;
    n=ch.size();
    ch=" "+ch;
    for(int i=1;i<=n;++i) ch[i]-='a';
    for(int i=1;i<n-1;++i){
        add(i,i+1,1);
        add(i+1,i,1);
    }
    for(int i=1,tmp;i<n;++i){
        tmp=ch[i]*26+ch[i+1]+n;
        add(i,tmp,1);
        add(tmp,i,0);
    }
    memset(f,0x3f,sizeof(f));
    for(int i=0;i<676;++i) bfs(i);
    cin>>m;
    for(int i=1,x,y,ans;i<=m;++i){
        cin>>x>>y;
        ans=abs(x-y);
        for(int j=0;j<676;++j) ans=min(ans,f[j][x]+f[j][y]+1);
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：simonG (赞：0)

过于一眼。

称所有相同的字符对的光标位置为一组。

由于对于一个组的点，要两两连接在一起，这时候不得不拿出一个经典套路：

建立虚点，边权 $0.5$，然后连向一个组的所有点。为方便将边权 $\times2$。

由于虚点非常少，只有 $26^2=676$ 个，这启发我们对于每个虚点跑一遍 BFS。

对于每次询问来说，只需要遍历所有虚点，求强制经过这个点的最短路。

但是如果不经过虚点了呢？我们可以直接作差求绝对值求出不经过虚点的长度。

这样就做完了。关于边权是 $1,2$ 的 BFS，我们考虑将 $2$ 的拆成两个点就行了。

复杂度是 $O(676(n+q))$。

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int N=1.1e5+10;
int n,q,tot;
char s[N];
int id[26][26];
vector<int> e[N];
void add(int x,int y) {e[x].push_back(y); e[y].push_back(x);}
int dis[676][N];
void solve(int i,int s) {
	memset(dis[i],63,sizeof dis[i]);
	if(!e[s].size()) return ;
	queue<int> q;
	q.push(s); dis[i][s]=0;
	for(; q.size(); ) {
		int x=q.front(); q.pop();
		for(int y:e[x]) {
			if(dis[i][y]>dis[i][x]+1) {
				dis[i][y]=dis[i][x]+1;
				q.push(y);
			}
		}
	}
}
int main() {
	scanf("%s",s+1);
	n=strlen(s+1);
	tot=n-1;
	for(int i=0; i<26; i++) for(int j=0; j<26; j++)
		id[i][j]=++tot;
	for(int i=1; i<n; i++) {
		int u=s[i]-'a',v=s[i+1]-'a';
		add(i,id[u][v]); add(id[u][v],i);
		if(i>1) {tot++; add(i-1,tot); add(tot,i);}
	}
	for(int i=0; i<26; i++) for(int j=0; j<26; j++)
		solve(i*26+j,id[i][j]);
	scanf("%d",&q);
	for(; q; q--) {
		int x,y; scanf("%d%d",&x,&y);
		int ans=abs(x-y);
		for(int i=0; i<676; i++) ans=min(ans,(dis[i][x]+dis[i][y])/2); 
		printf("%d\n",ans);
	}
	return 0;
}
```


---

