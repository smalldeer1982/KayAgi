# [ABC289E] Swap Places

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc289/tasks/abc289_e

頂点に $ 1 $ から $ N $ までの、辺に $ 1 $ から $ M $ までの番号がついた $ N $ 頂点 $ M $ 辺の単純無向グラフがあります。 辺 $ i $ は頂点 $ u_i $ と頂点 $ v_i $ を結んでいます。  
 また、全ての頂点は赤か青のいずれか一方で塗られています。頂点 $ i $ の色は $ C_i $ で表されて、$ C_i $ が $ 0 $ ならば頂点 $ i $ は赤く、$ 1 $ ならば頂点 $ i $ は青く塗られています。

今、高橋君が頂点 $ 1 $ に、青木君が頂点 $ N $ にいます。  
 2 人は次の行動を $ 0 $ 回以上好きな回数繰り返します。

- 2 人が同時に、今いる頂点に隣接している頂点のいずれか 1 個に移動する。  
   ただし、高橋君の移動先の頂点の色と、青木君の移動先の頂点の色は異なる必要がある。
 
上記の行動を繰り返すことで、高橋君が頂点 $ N $ に、青木君が頂点 $ 1 $ にいる状態にできますか？  
 可能である場合は必要な行動回数の最小値を答えてください。不可能である場合は `-1` を出力してください。

入力のはじめに $ T $ が与えられるので、$ T $ 個のテストケースについて問題を解いてください。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 1000 $
- $ 2\ \leq\ N\ \leq\ 2000 $
- $ 1\ \leq\ M\ \leq\ \min(\frac{N(N-1)}{2},\ 2000) $
- $ C_i\ \in\ \lbrace\ 0,\ 1\ \rbrace $
- $ 1\ \leq\ u_i,\ v_i\ \leq\ N $
- 入力で与えられるグラフは単純
- 入力される値は全て整数
- 全てのテストケースに対する $ N $ の総和は $ 2000 $ を超えない。
- 全てのテストケースに対する $ M $ の総和は $ 2000 $ を超えない。
 
### Sample Explanation 1

1 番目のテストケースでは、高橋君と青木君は以下のように行動することで、 $ 3 $ 回の行動で目的の状態を達成することができて、これが最小です。 - 高橋君が頂点 $ 3 $ に、青木君が頂点 $ 2 $ に移動する。 - 高橋君が頂点 $ 2 $ に、青木君が頂点 $ 3 $ に移動する。 - 高橋君が頂点 $ 4 $ に、青木君が頂点 $ 1 $ に移動する。 ここで、$ 1 $ 回目の移動で高橋君と青木君がともに頂点 $ 2 $ に移動することはできないのに注意してください。(なぜならば、高橋君の移動先の頂点の色と青木君の移動先の頂点の色は異なる必要があるからです。) 2 番目のテストケースでは、2 人はどのように行動しても目的の状態を達成することはできません。

## 样例 #1

### 输入

```
3
4 4
0 1 0 1
1 2
2 3
1 3
2 4
3 3
0 1 0
1 2
2 3
1 3
6 6
0 0 1 1 0 1
1 2
2 6
3 6
4 6
4 5
2 4```

### 输出

```
3
-1
3```

# 题解

## 作者：ForgotDream_CHN (赞：6)

# ATABC289E Swap Places

感觉这题没有 ABC 的 E 该有的难度，出题人背大锅。

### 题意

给定一张 $N$ 个节点的无向无权图，每个节点要么是红色要么是蓝色，现在 Takahashi 在 $1$ 号点，Aoki 在 $N$ 号点，询问否存在路径，使得 Takahashi 能够走到 $N$ 号点， Aoki 能够走到 $1$ 号点，两人同时到达终点并且每一步他俩所在的节点颜色都不一样，如存在，输出路径最小值，不然输出 $-1$。多测，$T \le 1000$，$N \le 2000$。

### 思路

无向无权图上的最短路，我们不难想到 BFS。问题在于同时有两个人的移动，还要考虑颜色不能相同。

其实还是可以通过 BFS 来解决，普通的 BFS 只记录了一个坐标，于是类似地，我们考虑在状态中把两个人的位置都记录下来，这样判重以及判断合法性都会很方便。

时间复杂度为 $O(TN^2)$，但是跑不满，在 AtCoder 神机的加持下可以通过此题。

### 代码

```cpp
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

const int N = 2e3 + 50;
int T, n, m;
int c[N];
vector<int> e[N];	// vector 存图
int dis[N][N];		// 用于判重以及记录路径长度

inline void init() {
	memset(dis, -1, sizeof(dis));
	for (int i = 1; i <= n; i++) e[i].clear();
	return;
}

inline void add(int u, int v) {
	return (void) (e[u].push_back(v));
}

int bfs() {
	queue<pair<int, int>> q;	// 队列里同时存两个人的坐标
	q.emplace(1, n), dis[1][n] = 0;

	while (!q.empty()) {		// 普通的 BFS
		auto u = q.front();
		int curx = u.first, cury = u.second;
		for (auto i : e[curx]) 	
			for (auto j : e[cury])
				// 要同时枚举两个点的邻接点 
				if (dis[i][j] == -1 && c[i] != c[j]) {
					dis[i][j] = dis[curx][cury] + 1;
					if (i == n && j == 1) return dis[i][j];
					q.emplace(i, j);
				}
		q.pop();
	}

	return -1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> T;
	while (T--) {
		init();		// 多测不要忘了初始化
		cin >> n >> m;
		// cerr << n << ' ' << m << '\n';
		for (int i = 1; i <= n; i++) cin >> c[i];
		for (int i = 1, u, v; i <= m; i++) 
			cin >> u >> v, add(u, v), add(v, u);
		if (c[1] == c[n]) cout << -1 << '\n';
		else cout << bfs() << '\n';
	}

	return 0;
}
```



---

## 作者：SkyLines (赞：1)

## 题目翻译

有一个 $n$ 个点 $m$ 条边的无向图，第 $i$ 个点的点权为 $c_i$，$c_i$ 可以为 $0$ 或 $1$。有两个人分别在 $1$ 号和 $n$ 号点上，这两个人每次可以向相邻的点移动，求位置互换的最小次数。

## 思路

可以用 bfs 解决，$step_{i,j}$ 表示第一个人在 $i$ 点，第二个人在 $j$ 点所需的最小次数。在搜索到点 $u,v$ 时，两层循环枚举与 $u$ 相邻的点 $x$，和与 $v$ 相邻的点 $y$，如果 $x,y$ 还没走过且能走就更新 $step_{x,y}=step_{i,j}+1$，并将 $x,y$ 加入队列。初始 $step_{1,n}=0$，其他全为负数。$c_1=c_n$ 时输出 $-1$ 即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, m, s, head[2005], c[2005], x, y, step[2005][2005];
queue<pair<int, int> > q;
struct node{
	int v, next;
};
node edge[4005];
void addedge(int uu, int vv){
	edge[++s].v = vv;
	edge[s].next = head[uu];
	head[uu] = s;
}
int bfs(){
	q.push(make_pair(1, n));
	step[1][n] = 0;
	while(!q.empty()){
		int frx = q.front().first, fry = q.front().second;
		q.pop();
		for(int i = head[frx]; i; i = edge[i].next){
			for(int j = head[fry]; j; j = edge[j].next){
				int nex = edge[i].v, ney = edge[j].v;
				if(step[nex][ney] != -1) continue;
				if(c[nex] == c[ney]) continue;
				step[nex][ney] = step[frx][fry] + 1;
				if(nex == n && ney == 1){
					while(!q.empty()) q.pop();
					return step[nex][ney];
				}
				q.push(make_pair(nex, ney));
			}
		}
	}
	return -1;
}
int main(){
	scanf("%d", &t);
	for(int tt = 1; tt <= t; tt++){
		for(int i = 0; i < 2005; i++) head[i] = 0;
		for(int i = 0; i < 2005; i++){
			edge[i].v = 0;
			edge[i].next = 0;
		}
		for(int i = 0; i < 2005; i++) for(int j = 0; j < 2005; j++) step[i][j] = -1;
		s = 0;
		scanf("%d %d", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%d", &c[i]);
		for(int i = 1; i <= m; i++){
			scanf("%d %d", &x, &y);
			addedge(x, y);
			addedge(y, x);
		}
		if(c[1] == c[n]){
			printf("-1\n");
			continue;
		}
		printf("%d\n", bfs());
	}
	return 0;
}
```

---

## 作者：ImposterAnYu (赞：1)

这题毫无疑问，和最短路挂钩。但是和普通的最短路不同的是，这题有两个点需要**同时**转移，并且每次的转移都会有一个限制——两个点的点权必须不同。

不过这题还有个性质——边权都为 $1$。

边权为 $1$、最短路、指定起点和终点……怎么和走迷宫有点像呢？

我们平常做走迷宫的题用什么？没错，BFS。

那这题可以用 BFS 吗？显然可以。虽然这题是两个人在移动，但是因为是同时移动，所以也可以同时转移，不至于拓展出太多的状态。而且我们可以用记忆化判重，因为最先到达某个状态时的答案一定比后面再到达这个状态时的答案更优。

所以我们的思路就很明显了。用 $(x,y,st)$ 来表示高桥君在点 $x$、青木君在点 $y$，移动了 $st$ 次，$vis_{x,y}$ 表示高桥君在点 $x$ 时，青木君是否到过点 $y$（或者高桥君是否可以在点 $x$ 的同时，青木君在点 $y$）。初始状态是 $(1,n,0)$，只要 $vis_{n,1}$（注意不是 $vis_{1,n}$）为 $1$ 就一定有解，否则无解。

时间复杂度 $O(TN^2)$（因为最多有 $N^2$ 种状态），理论上会超时，但是样例下面有这么一句话：

> 全てのテストケースに対する $N$ の総和は $2000$ を超えない。

（翻译：所有的 $N$ 的和不超过 $2000$。）

所以这个复杂度是跑不满的。加上这题时间限制 $2s$，可以过。

一点小优化：

1. 多测清空时不用 `memset` 而用手动清空可能会快一点，因为数组里的元素并不全部需要清零。

2. BFS 搜到答案就可以直接退出了，因为最先到达某个状态时的答案一定比后面再到达这个状态时的答案更优。~~BFS 不是都这样吗？~~

最后放一下代码~

```cpp
#include<bits/stdc++.h>
#define N 2000
#define M 4000 
#define int1 int
using namespace std;
int1 t,n,m,i,j,bs,ta[N + 5],pre[M + 5],to[M + 5];
bool a[N + 5],vis[N + 5][N + 5];
void C(){//关同步。 
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	return ;
}
void add_edge(int1 x,int1 y){//加边 
	pre[++bs] = ta[x],ta[x] = bs,to[bs] = y;
	return ;
}
void two_edge(int1 x,int1 y){//加双向边 
	add_edge(x,y),add_edge(y,x);
	return ;
}
struct owo{
	int1 x,y,st;//x:高桥君的位置 y:青木君的位置 st:移动次数 
} now;
int1 bfs(){//BFS
	queue<owo> q;
	q.push((owo){1,n,0});//初始状态 
	vis[1][n] = 1; 
	while(!q.empty()){
		now = q.front();
		q.pop();
		int1 x = now.x,y = now.y,st = now.st + 1;
		for(int1 i = ta[x]; i; i = pre[i]){
			for(int1 j = ta[y]; j; j = pre[j]){//双重循环枚举可以走的点 
				int1 xx = to[i],yy = to[j];
				if(a[xx] ^ a[yy] && !vis[xx][yy]){//可以走 
					vis[xx][yy] = 1;//标记 
					if(xx == n && yy == 1){//搜到了就退出 
						return st;
					}
					q.push((owo){xx,yy,st});
				}
			}
		}
	}
	return -1;
}
int main(){
	C();
	cin >> t;
	n = N,bs = M;
	while(t--){
		for(i = 1; i <= bs; i++){//多测清空 
			pre[i] = to[i] = 0;
		}
		for(i = 1; i <= n; i++){//多测清空 
			a[i] = ta[i] = 0;
			for(j = 1; j <= n; j++){//多测清空 
				vis[i][j] = 0;
			}
		}
		bs = 0;
		cin >> n >> m;
		for(i = 1; i <= n; i++){
			cin >> a[i];
		}
		for(i = 1; i <= m; i++){
			int1 x,y;
			cin >> x >> y;
			two_edge(x,y);
		}
		if(!(a[1] ^ a[n])){//1和n号点的点权一样 
			cout<< -1 << endl;//无解 
			continue;
		}
		cout<< bfs() << endl;
	}
	return 0;
}
```

[目前最快评测记录（AT）](https://atcoder.jp/contests/abc289/submissions/43683665)（在洛谷上 UKE 了）

~~目前是最优解，贼快！~~

---

## 作者：zzx0102 (赞：1)

6，我这种菜都能过 E（~~只可惜报名晚了，unrated，不然就绿名了~~）

这题和 D 一样，也是 bfs，只是这是个图论。

那么这个标记状态是二维的，$\mathit{vis}_{i,j}$ 表示高桥在 $i$，青木在 $j$ 时有没有访问过。

那么转移时直接两个循环枚举 $i,j$ 的所有连着的点就可以了。

当然，$c_i=c_j$ 的时候要忽略掉，这样可以快一点（不判就寄了）。

总复杂度 $O(Tn^2)$，但是实际上跑不满。

多测不清空，爆零两行泪。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define CI const int
#define gc getchar
#define Mt(a, b) memset(a, b, sizeof a)
#define pc putchar
#define W while
#define I inline
namespace SlowIO{
	I int read() {
		int x = 0, f = 1; char ch = gc();
		W(ch < '0' || ch > '9') {if(ch == '-') f = -f; ch = gc();}
		W(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gc();
		return x * f;
	}
	I void Read(int &x) {x = read();}
	I void Read(int &x, int &y) {Read(x), Read(y);}
	I void write(int x) {
		if(x < 0) pc('-'), x = -x;
		if(x > 9) write(x / 10);
		pc(x % 10 + '0');
	}
	I void writeln(int x) {write(x); pc('\n');}
	I void Write(int x) {write(x); pc(' ');}
} using namespace SlowIO;
CI N = 2010; vector<int> v[N]; bool vis[N][N]; int c[N]; int n, m;
I void add(int a, int b) {v[a].push_back(b);} // 加边
struct node{
	int u, v, step;
	node(int a, int b, int c) {u = a, v = b, step = c;}
};
I int bfs() {
	queue<node> q; q.push(node(1, n, 0)); vis[1][n] = 1;
	W(!q.empty()) {
		node f = q.front(); q.pop(); int x = f.u, y = f.v;
		for(int a: v[x]) {
			for(int b: v[y]) { // 大力出奇迹
				if(c[a] == c[b]) continue; if(vis[a][b]) continue; // 不合法情况
				if(a == n && b == 1) return f.step + 1; // 到了
				vis[a][b] = 1;
				q.push(node(a, b, f.step + 1));
			}
		}
	}
	return -1;
}
int main() {
	int t; Read(t);
	W(t--) {
		Read(n, m);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) vis[i][j] = 0; // 初始化
		for(int i = 1; i <= n; i++) Read(c[i]);
		W(m--) {int a, b; Read(a, b); add(a, b); add(b, a);}
		writeln(bfs());
		for(int i = 1; i <= n; i++) v[i].clear(); // 清空
	}
	return 0;
}
```

---

## 作者：Demons_Killer (赞：0)

# 解题思路：
一道图上的动态规划。

先用邻接矩阵构图，在使用队列进行广度优先遍历。动态规划数组 $f_{i,j}$ 表示 $i$ 和 $j$ 两点要跑的最短路，$f_{i,j}$ 所求的值要加上之前所遍历的点跑的路径长度，可得状态转移方程为 $f_{i1,j1}=f_{i2,j2}$。

最后我们的答案为 $f_{1,n}$。

# code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2050;
vector<int>e[maxn];
int c[maxn];
int f[maxn][maxn];
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n,m;cin>>n>>m;
		for(int i=1;i<=n;i++)e[i].clear();
		for(int i=1;i<=n;i++)cin>>c[i];
		for(int i=1;i<=m;i++){
			int u,v;
			cin>>u>>v;
			e[u].push_back(v);
			e[v].push_back(u);
		}
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
			f[i][j]=-1;
		}
		queue<pair<int,int> >q;
		q.push({n,1});f[n][1]=0;
		while(q.size()){
			auto [u1,u2]=q.front();q.pop();
			for(int v1:e[u1]){
				for(int v2:e[u2]){
					if(c[v1]!=c[v2]&&f[v1][v2]==-1){
						f[v1][v2]=f[u1][u2]+1;
						q.push({v1,v2});
					}
				}
			}
		}
		cout<<f[1][n]<<endl;
	}
	return 0;
}
```

---

## 作者：highkj (赞：0)

# 思路
我们其实一眼就可以看出这道题的思路，那么我们其实可以跑一个最短路，我们还是定义 $dis_{i,j}$ 为两个人分别 $1,n$ 走到 $i,j$ 的最短代价，那么因为我们用的是 BFS 所以第一次 $dis_{n,1}$ 有值时就一定是最小值。而在转移的途中其实就是和最短路差不多，然后就是加上判断两个点的颜色是否相同即可。
# 代码
```cpp
#include <bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(fasle);cin.tie(NULL);cout.tie(NULL)
#define int long long
#define ri register int
#define rep(i,x,y) for(ri i=x;i<=y;i++)
#define rep1(i,x,y) for(ri i=x;i>=y;i--)
#define il inline
#define fire signed
#define pai(a,x,y) sort(a+x,a+y+1)
using namespace std ;
il int qmi(int a,int b) {
	int res=1;
	while(b) {
		if(b&1) res=(res*a);
		a=a*a;
		b>>=1;
	}
	return res;
}
void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
#define gcd(x,y) __gcd(x,y)
#define lcm(x,y) x*y/gcd(x,y)
int t;
int n,m;
const int N=2e3+10;
vector<int>v[N];
int c[N],f,dis[N][N];
#define pa pair<int,int>
void dij(int s) {
	queue<pair<int,int> >q;
	q.push({1,n});
	memset(dis,0x3f,sizeof dis);
	dis[1][n]=0;
	while(q.size()) {
		int nx=q.front().first,ny=q.front().second;
		q.pop();
		if(dis[n][1]<0x3f3f32f3f/2) {
			print(dis[n][1]);
			putchar('\n');
			f=1;
			return ;
		}
		for(auto x:v[nx]) {
			for(auto y:v[ny]) {
				if(c[x]==c[y]) continue;
				if(dis[x][y]>dis[nx][ny]+1) {
					dis[x][y]=dis[nx][ny]+1;
					q.push({x,y});
				}
			}
		}
	}
}
fire main() {
	cin>>t;
	while(t--) {
		f=0;
		cin>>n>>m;
		rep(i,1,n) v[i].clear();
		rep(i,1,n) cin>>c[i];
		rep(i,1,m) {
			int x,y;
			cin>>x>>y;
			v[x].push_back(y);
			v[y].push_back(x);
		}
		dij(1);
		if(!f) cout<<"-1\n";
	}
	return 0;
}

```

---

## 作者：incra (赞：0)

### 前言
感谢管理员多次审核这个蒟蒻不符合要求的部分，还挑出以前未审核出来了的错误。

管理员大大。
### [题目链接](https://atcoder.jp/contests/abc289/tasks/abc289_e)
### 题意
给定一个无向连图，每个节点都有一种颜色，现在 Takahashi 在 $1$ 号点，Aoki 在 $n$ 号点，请问是否存在路径，使得 Takahashi 能走到 $n$ 号点，Aoki 能走到 $1$ 号点，并且使得两人同时到达终点并且每一步他们两个所在的点颜色不同。若有，输出最小步数，若没有输出 $-1$。

题意参考[这篇题解](https://fd-chn.blog.luogu.org/atabc289e-swap-places)，在此表示感谢。
### 题解
很容易想到了 BFS，直接把两个人所在的位置作为状态，也就是说，要从 $(1,n)$ 的状态走到 $(n,1)$ 的状态，可以很方便的判断颜色相同或不同。

### 时间复杂度
每组测试数据一共有 $n^2$ 个状态，所以复杂度是 $O(n^2)$，总复杂度是 $O(\displaystyle \sum n^2)$ 的限制 $2s$ 可以通过。
### 代码
```cpp
#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
#define x first
#define y second
using namespace std;
typedef pair <int,int> PII;
const int N = 2010,M = 2 * N;
int n,m;
int c[N];
int h[N],e[M],ne[M],idx;
bool vis[N];
int dist[N][N];
void add (int a,int b) {
	e[idx] = b;
	ne[idx] = h[a];
	h[a] = idx++;
}
int bfs () {
	queue <PII> q;
	q.push ({1,n});
	memset (dist,0x3f,sizeof (dist));
	dist[1][n] = 0;
	while (q.size ()) {
		PII t = q.front ();
		if (t.x == n && t.y == 1) return dist[n][1];
		q.pop ();
		vector <int> v;
		for (int i = h[t.x];~i;i = ne[i]) v.push_back (e[i]);
		for (int i = h[t.y];~i;i = ne[i]) {
			int y = e[i];
			for (int x : v) {
				if (c[x] != c[y]) {
					if (dist[x][y] > dist[t.x][t.y] + 1) {
						dist[x][y] = dist[t.x][t.y] + 1;
						q.push ({x,y});
					}
				}
			}
		}
	}
	return -1;
}
int main () {
	int T;
	cin >> T;
	while (T--) {
		cin >> n >> m;
		for (int i = 1;i <= n;i++) cin >> c[i];
		memset (h,-1,sizeof (h));
		idx = 0;
		while (m--) {
			int a,b;
			cin >> a >> b;
			add (a,b),add (b,a);
		}
		cout << bfs () << endl;
	}
    return 0;
}
```

---

## 作者：Neil_Qian (赞：0)

# [ABC289E] Swap Places 题解

### 题目描述

给定一个 $n$ 个点 $m$ 条边的无向图，点有点权，值可以为 $0$ 或 $1$。两个人分别在点 $1$ 和 $n$，每次他们同时向自己这个结点的任意一个邻居移动，任意时刻，他们所在的结点的权值不得相同。最后要使得他们互相交换位置。输出最小次数或输出无解。$n\le2\times10^3$。

### 解决方案

注意到 $n\le2\times10^3$，$O(n^2)$ 完全可以通过。那么，现在两个人所在的结点的权值是否和下一次能否踏上某两个结点有关系呢？没有，是否能踏上某两个结点只有那两个结点的点权决定，也没有说不能重复踏上同一个结点，因此无后效性。我们考虑动态规划。

#### 状态

根据之前说的，我们只需要记录两个人分别在 $i$ 号结点和 $j$ 号结点的答案即可。

#### 转移

我们遍历 $i$ 和 $j$ 的邻居，如果两个结点的权值不同，设其分别为 $u$ 和 $v$，有 $dp_{u,v}=dp_{i,j}+1$。我们还要考虑遍历的顺序。

#### 顺序

此题如果顺序枚举 $i,j$ 显然是错的，因为一开始我们在 $1,n$ 上而且这是在一张图上啊！图上？何不考虑广搜呢？根据上面的转移方法可以知道这会是一个无权图（因为每次都是 $+1$），广搜完全可以胜任。如果最后 $dp_{n,1}$ 还没有被更新的话就无解。

单次时间复杂度 $O(m^2)$，因为要枚举边。最后：多测不清空，爆零两行泪。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;using P=pair<int,int>;const int N=2e3+2;
int T,n,m,x,y,c[N],dp[N][N];
queue<P> q;vector<int> v[N];bool inq[N][N];//vector存图+广搜的queue及inq
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);//读入
		for(int i=1;i<=n;i++){//多测不清空，爆零两行泪
			v[i].clear();
			for(int j=1;j<=n;j++)dp[i][j]=1e9;
		}
		for(int i=1;i<=n;i++)scanf("%d",&c[i]);//读入
		while(m--)scanf("%d%d",&x,&y),
			v[x].push_back(y),v[y].push_back(x);//建图
		if(c[1]==c[n]){printf("-1\n");continue;}//先来个判断
		dp[1][n]=0,q.push(P{1,n});
		while(!q.empty()){
			x=q.front().first,y=q.front().second;
			inq[x][y]=0,q.pop();
			for(int u:v[x])for(int t:v[y])if(c[u]!=c[t]&&
			dp[x][y]+1<dp[u][t]){//虽然这里是无权图，不过判断是否更优放心一些
				dp[u][t]=dp[x][y]+1;//更新
				if(!inq[u][t])q.push(P{u,t}),inq[u][t]=1;
			}
			if(dp[n][1]!=1e9){//更新到了，提前退出
				while(!q.empty())//要把queue和inq清空掉，否则下一次会出问题
					x=q.front().first,y=q.front().second,
					inq[x][y]=0,q.pop();
				break;
			}
		}
		printf("%d\n",(dp[n][1]==1e9?-1:dp[n][1]));//无解情况
	}
	return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

## 题意

给定一张无向图，有 $n$ 个节点，每个点不是蓝色就是红色，初始 Takahashi 在节点 $1$，Aoki 在节点 $n$，Takahashi 和 Aoki 同时到达对方初始节点，每一步两人的节点颜色必须不一样，如果存在，输出路径长度，否则输出 $-1$。

## 思路
这是一道 DP 题，设 $dp_{u1,u2}$ 表示 Aoki 走到 $u1$，Takahashi 走到 $u2$ 的方案个数，那么可以暴力枚举与 $u1,u2$ 相邻的点 $v1,v2$，找到 $v1,v2$ 颜色不同的点变成 $dp_{u1,u2}+1$，表示可以从 $dp_{u1,u2}$ 走到 $dp_{v1,v2}$。

最后输出 $dp_{1,n}$ 即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2050;
vector<int>e[maxn];
int c[maxn];
int dp[maxn][maxn];
signed main(){
	int T;
	cin>>T;
	while(T--){
		int n,m;cin>>n>>m;
		for(int i=1;i<=n;i++)e[i].clear();
		for(int i=1;i<=n;i++)cin>>c[i];
		for(int i=1;i<=m;i++){
			int u,v;
			cin>>u>>v;
			e[u].push_back(v);
			e[v].push_back(u);
		}
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
			dp[i][j]=-1;
		}
		queue<pair<int,int>>Q;
		Q.push({n,1});dp[n][1]=0;
		while(Q.size()){
			auto [u1,u2]=Q.front();Q.pop();
			for(int v1:e[u1]){
				for(int v2:e[u2]){
					if(c[v1]!=c[v2]&&dp[v1][v2]==-1){
						dp[v1][v2]=dp[u1][u2]+1;
						Q.push({v1,v2});
					}
				}
			}
		}
		cout<<dp[1][n]<<"\n";
	}
	return 0;
}
```

---

## 作者：Mikefeng (赞：0)

# [ABC289E] Swap Places

## 题目翻译

给定一个图。

初始时有两个棋子 $a,b$ 分别在 $1$ 和 $n$ 上，要求它们分别同时到达 $n$ 和 $1$。每次将两个棋子各移动一步，但是要保证两个棋子所在的点的颜色不同，问最少要走几步。

$1\le n,m\le2000$

## 做法

每次枚举两个人分别能走到的下一个点，如果不符合要求就跳过，否则就转移。

复杂度显然爆表，但是如果我们重新走到之前走过的状态那么一定是不会更优的，因为我们浪费了一些步数绕圈子，所以可以记忆化。

实现时可以利用 bfs 进行 dp 转移，走到之前走过的状态时直接 continue。初始状态 $f_{1,n}=0$，答案就是 $f_{n,1}$。

时间复杂度 $O(n^2)$。

## 代码

```cpp
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
const int N=2005;
const int inf=0x3f3f3f3f;
int t,n,m;
int a[N];
int f[N][N];
queue<pii> q;
vector<int> e[N];
inline void get_ans(){
	q.push({1,n});
	f[1][n]=0;
	while(!q.empty()){
		pii tmp=q.front();q.pop();
		int x=tmp.fi,y=tmp.se;
		for(int fx:e[x]) for(int fy:e[y]){
			if(a[fx]==a[fy]||f[fx][fy]!=inf) continue;
			f[fx][fy]=f[x][y]+1;
			q.push({fx,fy});
		}
	}
}
int main(){
	t=read();
	while(t--){
		n=read();m=read();
		F(i,1,n) a[i]=read();
		F(i,1,n) e[i].clear();
		F(i,1,n) F(j,1,n) f[i][j]=inf;
		F(i,1,m){
			int u=read(),v=read();
			e[u].push_back(v);
			e[v].push_back(u);
		}
		get_ans();
		if(f[n][1]==inf) puts("-1");
		else printf("%d\n",f[n][1]);
	}
	return 0;
}
```


---

