# [AGC005E] Sugigma: The Showdown

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc005/tasks/agc005_e

しぐま君とすぎむ君はゲームをすることにしました。

このゲームは $ N $ 頂点のグラフの上で行います。頂点には $ 1,2,...,N $ と番号がついています。グラフには $ N-1 $ 本の赤い辺と $ N-1 $ 本の青い辺があり、どちらも木となっています。赤い辺は $ (a_i,\ b_i) $ で表し、青い辺は $ (c_i,\ d_i) $ で表します。

二人はそれぞれ駒を $ 1 $ 個ずつ持っており、しぐま君の駒の初期位置は頂点 $ X $、すぎむ君の駒の初期位置は頂点 $ Y $ です。

このゲームはターン制で、ターン $ 1 $, ターン $ 2 $, ターン $ 3 $, ... と進んでいきます。そして、ターン $ 1,\ 3,\ 5,\ ... $ はしぐま君、ターン $ 2,\ 4,\ 6,\ ... $ はすぎむ君の手番です。

二人は自分の手番では、自分の駒を動かすかパスをします。ただし動かせる頂点には制限があり、しぐま君は赤い辺、すぎむ君は青い辺で隣り合った頂点のみに駒を動かせます。

もし二つの駒が同じ頂点に来るとその時点でゲームは終了します。そしてターン $ i $ での操作の後にゲームが終了したならば、$ i $ を総ターン数とします。

しぐま君は総ターン数を出来る限り大きく、すぎむ君は出来る限り小さくしたいです。

二人はこの目的のもとで最適に行動をすると仮定したとき、ゲームは終了するかを判定し、終了する場合は総ターン数はいくつになるか求めてください。

## 说明/提示

### 制約

- $ 2\ ≦\ N\ ≦\ 200,000 $
- $ 1\ ≦\ X,\ Y\ ≦\ N $
- $ X\ \neq\ Y $
- $ 1\ ≦\ a_i,\ b_i,\ c_i,\ d_i\ ≦\ N $
- 赤い辺と青い辺はそれぞれ木である

### Sample Explanation 1

!\[\](https://atcoder.jp/img/agc005/0f55f48518cb9031ee9f1cc30f686228.png)

### Sample Explanation 2

!\[\](https://atcoder.jp/img/agc005/df982a9959ce46d5d5f63800f8972bff.png)

### Sample Explanation 3

!\[\](https://atcoder.jp/img/agc005/11ce9a2283a853025b7075769439d745.png)

## 样例 #1

### 输入

```
4 1 2
1 2
1 3
1 4
2 1
2 3
1 4```

### 输出

```
4```

## 样例 #2

### 输入

```
3 3 1
1 2
2 3
1 2
2 3```

### 输出

```
4```

## 样例 #3

### 输入

```
4 1 2
1 2
3 4
2 4
1 2
3 4
1 3```

### 输出

```
2```

## 样例 #4

### 输入

```
4 2 1
1 2
3 4
2 4
1 2
3 4
1 3```

### 输出

```
-1```

## 样例 #5

### 输入

```
5 1 2
1 2
1 3
1 4
4 5
2 1
1 3
1 5
5 4```

### 输出

```
6```

# 题解

## 作者：yijan (赞：19)

神仙题。

首先捋清楚：先手最大化进行的回合数量，后手最小化，先手在红树，后手在蓝树。

通过观察可以发现，如果存在一条红边连接 $u,v$ 满足 $u,v$ 在蓝树上的距离大于等于 $3$ ，那么只要先手跑到了 $u,v$ 中的一个，同时后手并没能在这回合内抓到它，接下来先手必然可以通过在 $u,v$ 左右横跳来使得后手永远抓不到它。因为在后手距离先手在蓝树上是 $1$ 的时候就可以通过红边让后手距离先手变成 $2$ ，可以无限循环这个过程。

我们假定这个游戏还没有进行到先手能够让游戏无限循环下去的状态。也就是说当前先手可以用的红边在蓝树上距离必然小于等于 $2$ 。然后我们考虑一个事实：以后手起点为蓝树的根，先手所在的点在蓝树上一定随时处在后手所在点的子树内。因为一定不会出现先手通过红边跨过后手所在的点的情况。红边在蓝树上的长度小于等于 $2$ ，如果跨过了那么后手必然可以一步到达当前先手的地方，这么跳还不如就待在原地。

在有了这个结论后，对于一个点 $u$ ，假定蓝树上这个点到根的距离是 $d$ ，这个点在红树上到根的距离是 $r$ ，如果有 $d \le r$ ，那么先手一定不会把棋子移动到这个点上。因为先手的棋子不会跨过后手的棋子，所以先手走了一步后，后手一定可以往先手所在的子树走一步。如果后手一直选择这么走，那么先手一定会在到达这个点之前或者到达这个点的时候就被后手截住了。如果正好到达这个点就会被截住，那么前一步还不如就不走这一步。所以相当于，先后在任何一次行动的时候都得保证 $d > r$ 。

所以我们可以 `dfs` 一次，算出哪些点是可以通过走的时候满足 $d > r$ 到达的，然后看看这里面是否存在前面说的导致无限循环的点存在。如果存在，答案就是 $-1$ ，如果不存在，那么答案就是这里面最大的 $d$ 的两倍。最优决策一定是走到 $d$ 最大的点然后开始原地等待。

感觉这题比这场的 `F` 仙啊（？）

```cpp
int n , x , y;
int A[MAXN];

vi R[MAXN] , B[MAXN];
int db[MAXN] , fa[MAXN];
void afs( int u , int f ) {
	for( int v : B[u] ) if( v != f ) {
		fa[v] = u;
		db[v] = db[u] + 1 , afs( v , u );
	}
}
bool chk2( int u , int v ) {
	if( db[u] < db[v] ) swap( u , v );
	if( db[u] == db[v] ) {
		return fa[u] == fa[v];
	} else if( db[u] == db[v] + 1 ) {
		return fa[u] == v;
	} else if( db[u] == db[v] + 2 ) {
		return fa[fa[u]] == v;
	}
	return 0;
}
pii er[MAXN];
int ok[MAXN] , mx = 0;
void rfs( int u , int f , int dep ) {
	if( dep >= db[u] ) return;
	if( ok[u] ) puts("-1") , exit(0);
	mx = max( mx , db[u] );
	for( int v : R[u] ) if( v != f ) {
		rfs( v , u , dep + 1 );
	}
}

void solve() {
	cin >> n >> x >> y;
	rep( i , 2 , n ) {
		static int u , v;
		scanf("%d%d",&u,&v);
		R[u].pb( v ) , R[v].pb( u );
		er[i] = mp( u , v );
	}
	rep( i , 2 , n ) {
		static int u , v;
		scanf("%d%d",&u,&v);
		B[u].pb( v ) , B[v].pb( u );
	}
	afs( y , y );
	rep( i , 2 , n ) if( !chk2( er[i].fi , er[i].se ) ) ok[er[i].fi] = ok[er[i].se] = 1;
	rfs( x , x , 0 );
	cout << mx * 2 << endl;
}

signed main() {
//    int T;cin >> T;while( T-- ) solve();
    solve();
}

```

---

## 作者：Felix72 (赞：7)

直接想这题的形式化做法显然是不容易的，不妨将自己代入角色，假如你正在玩杀机或者第五，你会怎么操作。

对于这种追杀模型，我们分角色讨论一下：

### 最大化游戏轮数

假设你打逃生者，想要躲避追击有两种方式：

- 在某个点位反复拉扯、左右横跳，主打博弈色彩；
- 一直马拉松式逃跑，主打无脑拉点。

显然这道题里，适用前者的只有某些边（这些边的特点是追你的人从一端赶到另一端至少要走三条边，这样你就相当于进入了无敌点，可以进行无限轮游戏），如果没有无敌点，只能用后面这种方法了。显然，这种情况下你在逃跑时不会停留、不会走回头路（因为白白亏距离），那么你走的肯定是从你当前的位置到某个叶子。

### 最小化游戏轮数

假设你打杀手，想要快速追击同样有两种方式：

- 架住一个点位让对方出不去，等待技能 cd 后瓮中捉鳖；
- 跟在要追的人后面，直到慢慢追上。

这个题压根没技能这一说，所以只能用后者来做。同理，杀手也是不会走回头路的。

这么一来，整个过程就清晰了：两人走的一定都是一条链！

我们 dfs 判断一下可行性，最后对于逃生者能到达的所有地方，判断一下是不是无敌点即可。

```cpp
/*蛋糕鱼乐园*/
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 200010;
int n, px, py; vector < int > edge[2][N];

int step[N], fa[N], ans; bool vis[N];
vector < int > con[N];
inline void init(int now, int prt, int dist)
{
	step[now] = dist; fa[now] = prt;
	for(int i = 0; i < (int)edge[1][now].size(); ++i)
	{
		int to = edge[1][now][i];
		if(to == prt) continue;
		init(to, now, dist + 1);
	}
}
inline void solve(int now, int prt, int dist)
{
//	cerr << "! " << now << " " << prt << " " << dist << '\n';
	ans = max(ans, step[now] * 2);
	for(int i = 0; i < (int)edge[0][now].size(); ++i)
	{
		int to = edge[0][now][i];
		con[now].push_back(to);
		if(to == prt) continue;
		if(step[to] == dist) ans = max(ans, dist * 2 + 1);
		else if(abs(step[to] - dist) == 1) ans = max(ans, dist * 2 + 2);
		else solve(to, now, dist + 1);
	}
}
inline bool check(int p1, int p2)
{
	if(fa[p1] == p2) return false;
	if(fa[p2] == p1) return false;
	if(fa[fa[p1]] == p2) return false;
	if(fa[p1] && fa[p1] == fa[p2]) return false;
	if(fa[fa[p2]] == p1) return false;
	return true;
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> px >> py;
	for(int i = 1; i < n; ++i)
	{
		int x, y; cin >> x >> y;
		edge[0][x].push_back(y);
		edge[0][y].push_back(x); 
	}
	for(int i = 1; i < n; ++i)
	{
		int x, y; cin >> x >> y;
		edge[1][x].push_back(y);
		edge[1][y].push_back(x);
	}
	init(py, 0, 0);
	solve(px, 0, 0);
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j < (int)con[i].size(); ++j)
			if(check(i, con[i][j]))
				{cout << -1 << '\n'; return 0;}
	cout << ans << '\n';
	return 0;
}
/*

*/
```

---

## 作者：zhiyangfan (赞：4)

推销一下博客：[qwq](https://www.luogu.com.cn/blog/i-am-zhiyangfan/atcoder-grand-contest-005-bu-ti-zong-jie)
### 题意
两个人在一棵 $n$ 个结点的图上做游戏，一开始先手的棋子在 $X$，后手的棋子在 $Y$。这张图上有 $n-1$ 条蓝边和 $n-1$ 条红边。每种颜色的边和图上的 $n$ 个点都构成一棵树。先后手轮流操作，每次操作先手可以把棋子移动到一个由红边连接的相邻结点或选择不动，后手可以把棋子移动到一个由蓝边连接的相邻结点或选择不动，当两个棋子相遇时游戏结束。先手的目标是最大化游戏轮次，后手的目标是最小化游戏轮次，问在二人都采取最优策略的情况下，游戏的轮数是否有限，如果有限，求出游戏轮数。($2\le n\le2\times10^5$)

### 题解
神仙博弈论Orz。首先我们先来解释一下题意，先后手各有一棵点集相同的树，先手从 $X$ 出发使用红树尝试逃脱后手从 $Y$ 出发使用蓝树的追捕。约定 $dis_r(u,v)$ 表示在红树上 $u,v$ 点之间的距离，$dis_b(u,v)$ 表示在蓝树上 $u,v$ 点之间的距离。如果存在这样的 $u,v$ 满足 $dis_r(u,v)=1$ 且 $dis_b(u,v)\ge3$，则当先手到达 $u,v$ 中的任意一个结点且后手不能在这之后立即抓到他，游戏就可以一直进行下去了，即先手就可以一直逃脱后手的抓捕了。不妨设先手到的是 $u$，则他可以一直在那等直到后手追到一个与 $u$ 在蓝树上相邻的结点 $x$，这时他就会去 $v$，而因为 $dis_b(x,u)=1,dis_b(u,v)\ge3$，所以有 $dis_b(x,v)\ge 2$，后手不能一步追上先手。之后先手就可以一直这样在 $u,v$ 之间反复横跳来逃避抓捕，所以此时游戏轮数是无限的。我们称 $u,v$ 之间的红边为长边。

有了这个结论后，我们再来审视一下原题面给出的树。我们把蓝树考虑为一棵以 $Y$ 为根的有根树，而其中长边两端的点是特殊的，因为如果先手到达这些点且后手不能立即捉到他游戏就会无限进行，除了长边，红边还有短边，满足 $dis_r(u,v)=1,dis_b(u,v)\le 2$。我们可以把这些红边看做一次跳跃，现在问题就变为了在一棵有根树上的问题，先手在这些短边上跳跃尝试去走到特殊点或尝试去逃离后手的抓捕。一个非常重要的发现是，先手永远不会跳过后手，因为跳跃的最远距离是 $2$，所以最后到达的点一定会和后手相邻，下一轮就会被抓到。也就是说，先手一定会一直在后手所在的子树内。显然后手的最优策略是一直朝着先手的方向往下走，而如果这样先手一旦到达一个满足 $dis_b(Y,x)\le t$ 的结点 $x$ 用了 $t$ 步，就会被抓到。反之，如果先手一直尽量保持 $dis_b(Y,x)>t$ 就不会被抓住，这就是他的最优策略。

这样，游戏就可以理解为先手的单人游戏了。他到达的第 $i$ 个结点 $u_i$（$u_0=X$）应满足 $dis_b(u_i,Y)>i$，在这个限制下，如果他能到达某个特殊结点则游戏轮数就为无限，否则答案即为可能的路径中的最长路径长度。这些都可以用一次 $\rm dfs$ 求出，时间复杂度 $\mathcal{O}(n)$。
```cpp
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>
const int N = 2e5 + 10; std::vector<int> R[N], B[N];
struct edge{ int u, v; }e[N]; int n, x, y, ans, depr[N], depb[N], fa[N], vis[N];
void dfsB(int u, int f)
{
	fa[u] = f;
	for (int i = 0, v; i < B[u].size(); ++i)
	{
		v = B[u][i]; if (v == f) continue;
		depb[v] = depb[u] + 1; dfsB(v, u);
	}
}
void dfsR(int u, int f)
{
	if (vis[u]) printf("-1\n"), exit(0);
	ans = std::max(ans, depb[u]);
	for (int i = 0, v; i < R[u].size(); ++i)
	{
		v = R[u][i]; if (v == f) continue;
		depr[v] = depr[u] + 1;
		if (depr[v] < depb[v]) dfsR(v, u);
	}
}
inline bool check(int u, int v)
{
	if (depb[u] < depb[v]) std::swap(u, v);
	if (depb[u] == depb[v]) 
	{	
		if (fa[u] != fa[v]) return true;
		return false;
	}
	else if (depb[u] == depb[v] + 1)
	{
		if (fa[u] != v) return true;
		return false;
	}
	else if (depb[u] == depb[v] + 2)
	{
		if (fa[fa[u]] != v) return true;
		return false;
	}
	return true;
}
int main()
{
	scanf("%d%d%d", &n, &x, &y);
	for (int i = 1, u, v; i < n; ++i)
	{
		scanf("%d%d", &u, &v);
		R[u].push_back(v); R[v].push_back(u);
		e[i].u = u; e[i].v = v;
	}
	for (int i = 1, u, v; i < n; ++i)
	{
		scanf("%d%d", &u, &v);
		B[u].push_back(v); B[v].push_back(u);
	}
	dfsB(y, y);
	for (int i = 1, u, v; i <= n; ++i)
	{
		u = e[i].u; v = e[i].v;
		if (check(u, v)) vis[u] = vis[v] = 1;
	}
	dfsR(x, x); printf("%d\n", ans << 1); return 0;
}
```

---

## 作者：yqbylty (赞：4)

### 解题思路：

首先判断$-1$的情况，游戏可以无限进行下去，当且仅当和$A$当前所在节点$u$直接相连的点中存在点$v$满足在树$b$上$dis_{u,v}>2$。这个是很显然的，因为当$B$走到这两个节点中间的时候，$A$回去就好了。

然后考虑$A$的最优方案，肯定是在树$b$上一个距离$x$最远的节点$v_1$上等$B$来找到他，那么对答案的贡献就是$dis_{x,v_1}$，这里的$dis$指的是在树$b$上的距离。

#### Code：

```cpp
/*Program from Luvwgyx*/
#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2e5+10;
int n,x,y,ans,vis[maxn];
int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void print(int x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar(x%10+'0');
}
void write(int x){print(x);puts("");}
struct Heavy_Light_Decomposition{
    struct edge{int to,nxt;}e[maxn<<1];int tot,head[maxn];
    int idx,fa[maxn],dfn[maxn],dep[maxn],son[maxn],top[maxn],size[maxn];
    void add(int u,int v){e[++tot].to=v;e[tot].nxt=head[u];head[u]=tot;}
    void insert(int u,int v){add(u,v);add(v,u);}
    void build(int x){
        dep[x]=dep[fa[x]]+1;size[x]=1;int mx=0;
        for(int i=head[x],v=e[i].to;i;i=e[i].nxt,v=e[i].to){
            if(v==fa[x])continue;
            fa[v]=x;build(v);size[x]+=size[v];
            if(size[v]>mx)mx=size[v],son[x]=v;
        }
    }
    void dfs(int x){
        if(!x)return ;dfn[x]=++idx;
        top[x]=son[fa[x]]==x?top[fa[x]]:x;
        dfs(son[x]);
        for(int i=head[x],v=e[i].to;i;i=e[i].nxt,v=e[i].to)
            if(v!=fa[x]&&v!=son[x])dfs(v);
    }
    int query(int u,int v){
        while(top[u]!=top[v]){
            if(dep[top[u]]<dep[top[v]])swap(u,v);
            u=fa[top[u]];
        }if(dep[u]>dep[v])swap(u,v);
        return u;
    }
    int get_dis(int u,int v){return dep[u]+dep[v]-2*dep[query(u,v)];}
}HLD[2];
void init(int S){
    queue<int >q;
    q.push(S);vis[S]=1;
    while(!q.empty()){
        int x=q.front();q.pop();
        for(int i=HLD[0].head[x],v=HLD[0].e[i].to;i;i=HLD[0].e[i].nxt,v=HLD[0].e[i].to)
            if(!vis[v]&&HLD[0].dep[v]<HLD[1].dep[v])vis[v]=1,q.push(v);
    }
}
void solve(){
    for(int x=1;x<=n;x++){
        if(!vis[x])continue;
        ans=max(ans,HLD[1].dep[x]-1);
        for(int i=HLD[0].head[x],v=HLD[0].e[i].to;i;i=HLD[0].e[i].nxt,v=HLD[0].e[i].to)
            if(HLD[1].get_dis(v,x)>2){puts("-1");return ;}
    }write(ans<<1);
}
int main(){
    n=read();x=read();y=read();
    if(x==y){puts("0");return 0;}
    for(int i=1;i<n;i++)HLD[0].insert(read(),read());
    for(int i=1;i<n;i++)HLD[1].insert(read(),read());
    HLD[0].build(x);HLD[0].dfs(x);HLD[1].build(y);HLD[1].dfs(y);
    init(x);solve();
    return 0;
}
```

---

## 作者：约瑟夫用脑玩 (赞：2)

~~总感觉 AGC 的模拟构造的题在谷难度都虚高，比如~~[这场的 C](https://www.luogu.com.cn/problem/AT2061)~~。~~

这是人类智慧模拟博弈过程情况，和其他题解考虑距离和子树的不太一样。

由于可以不动，想办法考虑最大化步数的 A 肯定更简单。

自然的想法考虑 A 一直走下去可能的办法，重要的性质就是在一棵树上，没有环。

同时 A 肯定是在一两条边上无限跳跃就够了，而不用在一条更长的路径上走。

考虑 A 树上的一条边使得 A 无限循环，自然的就发现以下两种情况不可行：

- 如果这条边在两棵树上都有，走过这条边 B 立马可以跟上，A 就会被赶走，显然不行。

- 如果这条边在 A 树上，但是 B 树上两端点都连向了同一个点，那么只要 B 走到那个点就可以支配这两个点，A 也会被赶走。

其他的边由于 B 既无法跟上又不能支配，只能被 A 放风筝。

这样的边对 A 极有优势，将这样边的两个端点都进行标记，表示走到这个点就永远不会被抓住。

如果没有这样的边 A 只能找躲的最远的位置，DFS 一下即可。

否则是有这样的边，也就有标记点，A 肯定想去往那边走，那么 B 就会去拦。

考虑怎么会被拦住，由于是在树上走，只有一条路径，所以只要有一个点 B 能在 A 之前到达，B 就能拦住去往这个点子树内的标记点。

如果只是像这样来回横跳的话在一条边上跳就够了，也就是直接去找标记点。

但还有一种情况就是 B 可以拦住 A 去标记点的路但还是抓不住，也就是两条边无限循环走的情况。

对于 B 来说，最优秀的情况就是 A 能到达的所有标记点都被某一个点给拦住，然后由于不可行以无限循环的边都可以把 A 赶着走，B 必定能把 A 抓住。

否则，B 要么拦不住，要么由于有两个拦 A 的点而抓不到，如果 B 往其中一边走 A 是可以退回去往另一边的标记点走的。

这种思路没有利用一般题解利用的子树的性质，如果利用了可以直接忽略第二种情况，~~反正咱也不需要我就不说了啊~~。

所以这道题分两步走就行了，先判是否能抓住，就是要么没有标记点，要么标记点没被 B 拦住，要么有两个子树分别被拦（注意不能是两个点被一条边支配的拦住）。

然后像这样被抓住的如前文所说躲一个最远的位置，否则输出 -1 即可。

---

## 作者：water_tomato (赞：1)

本文同步发表于个人博客：[Link](https://www.watertomato.com/at2063-agc005e-sugigma-the-showdown-%e9%a2%98%e8%a7%a3/)。

## 题意

[题目链接](https://www.luogu.com.cn/problem/AT2063)。

有一棵红树和一棵蓝树，结点相同而边不同。双方各在某一点，只能在自己颜色的树上移动，红方先手。红方需要最大化游戏轮数，蓝方则需要最小化游戏轮数。求最终游戏轮数。

## 解析

首先发现，如果存在一条连接 $u,v$ 的红边，且 $u,v$ 两点在蓝树上的距离不小于 $3$，则若红方到达其中某一点且蓝方下一步抓不住他，游戏就会进行无限轮。画图易证，这里不赘述。

因此我们假定目前游戏还尚不能使红方无敌。 我们记一个点 $u$ 在红树上的深度为 $depa_u$，在蓝树上的深度为 $depb_u$，我们发现红方可以走的点一定满足 $depa_u<depb_u$。

证明：在红方不能无敌的情况下，一定不存在红方跨过蓝方到蓝树上深度更低的点的情况（一定会被抓住），因此红方既然绕不过去，那么对于 $depa_u \ge depb_u$ 即蓝方先于红方到达或与红方同时到达的这些点，红方也一定到达不了（一样会被抓）。

同时，如果红方不能无敌，那么显然最优解是在所有可以到达的点中走到在蓝树中最深的那个然后等死。

因此，我们只需先跑一边蓝树处理出所有点的 $depb$，然后判断出哪些点能够使红方无敌（在无敌边上），接着再在红树上进行 dfs，只走那些能走的点，每次统计最优解以及能否无敌即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
vector<int> R[N],B[N];
struct edge{
	int u,v;
}e[N];
int n,X,Y,depa[N],depb[N],fa[N],ans;
bool win[N];
inline void dfs2(int u,int f){//处理出蓝树上的深度
	fa[u]=f;
	for(int i=0;i<B[u].size();i++){
		int v=B[u][i];if(v==f) continue;
		depb[v]=depb[u]+1;dfs2(v,u);
	}
}
inline void dfs1(int u,int f){
	if(win[u]){//判断是否无敌
		printf("-1");
		exit(0);
	}
	ans=max(ans,depb[u]);
	for(int i=0;i<R[u].size();i++){
		int v=R[u][i];if(v==f) continue;
		depa[v]=depa[u]+1;
		if(depa[v]<depb[v]) dfs1(v,u);//判断是否可走
	}
}
inline bool check(int u,int v){//分类讨论，画图易理解
	if(depb[u]<depb[v]) swap(u,v);
	if(depb[u]==depb[v]){
		if(fa[u]!=fa[v]) return true;
		return false;
	}
	else if(depb[u]==depb[v]+1){
		if(fa[u]!=v) return true;
		return false;
	}
	else if(depb[u]==depb[v]+2){
		if(fa[fa[u]]!=v) return true;
		return false;
	}
	return true;
}
int main(){
	scanf("%d%d%d",&n,&X,&Y);
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		R[u].push_back(v);
		R[v].push_back(u);
		e[i].u=u;
		e[i].v=v;
	}
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		B[u].push_back(v);
		B[v].push_back(u);
	}
	dfs2(Y,Y);//先跑蓝树
	for(int i=1;i<n;i++){//统计哪些点可以使红方无敌
		int u=e[i].u,v=e[i].v;
		if(check(u,v)) win[u]=win[v]=1;
	}
	dfs1(X,X);
	printf("%d\n",ans<<1);
	return 0;
}
```



---

## 作者：lgswdn_SA (赞：1)

考虑什么时候先手一定可以不被后手追到。我们可以形象地联系生活场景（指自己在教室追/被追），一定是存在一条红边 $(x,y)$，使得先手只要不停地在 $(x,y)$ 徘徊，后手永远都没法追上。这样需要满足蓝树上 $(x,y)$ 路径的距离 $>2$。只要先手不断往那条边跑，如果能跑到，那么后手就追不上先手。我们称这样的红边为游击边。

由于是树，走的路径很具有局限性。我们发现，对于一个节点 $u$，它能在不被捉到的情况下被先手达到当且仅当 $u$ 到红色先手出发点的距离小于 $u$ 到蓝色后手出发点的距离（否则后手一定可以在半路逮到先手）。我们可以通过 dfs 就能求出哪些点是可以被先手到达的，然后判断这些点的红色导出子树存不存在那样的游击边。如果可以到达游击边，$ans=-1$。否则就是这些点中离后手出发点最远的距离 $\times 2$，先手跑到那里去等死就行了，容易证明这是最佳方案。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=1e6+9;

inline long long read() {
    register long long x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int n,s,t,d1[N],d2[N],f[N],ans2;
bool ans;
vector<int>e1[N],e2[N];

void dfs1(int u,int fa) {
	for(auto v:e1[u]) if(v!=fa) d1[v]=d1[u]+1, dfs1(v,u);
}
void dfs2(int u,int fa) {
	for(auto v:e2[u]) if(v!=fa) d2[v]=d2[u]+1, dfs2(v,u), f[v]=u;
}
bool check(int u,int v) {return u!=f[v]&&v!=f[u]&&f[v]!=f[u]&&u!=f[f[v]]&&v!=f[f[u]];}
void dfs3(int u,int fa) {
	for(auto v:e1[u]) if(v!=fa) {
		if(check(u,v)) {ans=1; return;}
		if(d1[v]>=d2[v]) continue;
		dfs3(v,u);
	}
	ans2=max(ans2,d2[u]);
}

int main() {
	n=read(), s=read(), t=read();
	rep(i,1,n-1) {
		int u=read(), v=read();
		e1[u].push_back(v), e1[v].push_back(u);
	}
	rep(i,1,n-1) {
		int u=read(), v=read();
		e2[u].push_back(v), e2[v].push_back(u);
	}
	dfs1(s,0), dfs2(t,0), dfs3(s,0);
	if(ans) puts("-1");
	else printf("%d\n",ans2*2);
	return 0;
} 
```

---

## 作者：无意识躺枪人 (赞：1)

有一个无向图，边分为红边和蓝边，两种边分别构成一棵树。两个人在两棵树上各一个点。

两人轮流移动，操作只有两个：走或不走。你只能走到与所在点相连的点上。

先手在红树上移动，后手在蓝树上移动。如果任意时刻两个人位于同一个点即可输出

红树需要最大化玩家的操作次数，蓝树需要最小化玩家的操作次数。求最终操作次数的值

$\color{gray}\text{（谷歌翻译提供题意）}$

------------

建树，先建蓝树（想想为什么）

对于一条红边$xy$，若在蓝树上x到y路径长$>2$，且先手走到该边端点时两人仍未相遇，则只能输出$-1$

把长度大于$2$的边删掉（称为“长边”）

很明显，走短边不可能走出蓝子树

因此先手走到一个能走到的深度最大的点之后等后手即可 

```c
/*
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
*/
#include<bits/stdc++.h>
#define MAXN 200005
using namespace std;

int n,cnt,last[MAXN];
int father[MAXN],deep[MAXN],dis[MAXN];
int q[MAXN],nnn[MAXN],mx[MAXN];
int tim,a[MAXN][2],xx,yy;
bool vis[MAXN],win[MAXN];

struct edge
{
    int to,next,h;
}t[MAXN*4];

void add(int u,int v,int h)
{
    t[++cnt].to=v;t[cnt].h=h;
    t[cnt].next=last[u];last[u]=cnt;
    t[++cnt].to=u;t[cnt].h=h;
    t[cnt].next=last[v];last[v]=cnt;
}

void dfs(int x)
{
    deep[x]=deep[father[x]]+1;nnn[x]=++tim;
    for (int i=last[x];i;i=t[i].next)
        if (t[i].to!=father[x]) father[t[i].to]=x,dfs(t[i].to);
    mx[x]=++tim;
}

bool check(int x,int y)
{
    if (nnn[x]>nnn[y]) swap(x,y);
    if (nnn[x]<nnn[y]&&mx[x]>nnn[y]) return deep[y]-deep[x]>2 ? true : false;
    if (father[x]==father[y]) return false;
    return true;
}

void bfs()
{
    int h=1,tt=1;q[1]=xx;vis[xx]=1;
    while (h<=tt)
    {
        int x=q[h++];
        for (int i=last[x];i;i=t[i].next)
            if (!t[i].h&&!vis[t[i].to])
            {
                dis[t[i].to]=dis[x]+1;
                if (dis[t[i].to]<deep[t[i].to]) vis[t[i].to]=1,q[++tt]=t[i].to;
            }
    }
}

int max(int a,int b){return a<b?a:b;}//

template<class T>inline void read(T &res)
{
    static char ch;T flag=1;
    while((ch=getchar())<'0'||ch>'9')if(ch=='-')flag=-1;res=ch-48;
    while((ch=getchar())>='0'&&ch<='9')res=res*10+ch-48;res*=flag;
}

int main()
{
    int ans=0;
    read(n);read(xx);read(yy);

    for (int i=1;i<n;i++) {read(a[i][0]);read(a[i][1]);}
    
    for (int i=1;i<n;i++)
    {
        int x,y;
        read(x);read(y);
        add(x,y,1);
    }

    deep[0]=-1;
    dfs( yy );

    for (int i=1;i<n;i++)
    {
        if (check(a[i][0],a[i][1]))
            win[a[i][0]]=win[a[i][1]]=1;
        else add(a[i][0],a[i][1],0);
    }

    bfs();

    for (int i=1;i<=n;i++)
        if (win[i]&&vis[i])
            {putchar('-');putchar('1');return 0;}

    for (int i=1;i<=n;i++)
        if (vis[i])
            ans=max(ans,deep[i]<<1);

    printf("%d\n",ans);
    return 0;
}
```

这题贪心比较好想，博弈策略一定要认真思考（我也是借鉴了$dalao$的思路才做出来的）

代码看一会儿就好了，代码里有一个很明显的错误防无脑抄，如果真懂了的话可以直接打出来的

思维难度比代码难度大

---

## 作者：SalN (赞：0)

link : [[AGC005E] Sugigma: The Showdown](https://www.luogu.com.cn/problem/AT_agc005_e)

首先回头走不优，实在要停，如果非要停这等死最后再停不劣，A 牵制 B 大致有一下方式：

+ 往离 B 远的地方走加长 B 的走路时间。

+ 找到一个位置，可以一直跟 B 绕无限久，此时答案就是 $-1$，我们称可以一直绕的地方为无敌点。

我们先考虑怎么判定一个无敌点，我们手玩答案为 $-1$ 的样例，发现无敌点形式是，对于树 B 上的简单路径 $p_1\to\dots\to p_x(x\geq 4)$，A 有一条 $(p_1,p_x)$ 这样的边，如此一来，只要通过这条边一直靠在离 B 远的点就永远不会被抓到了 w

我们考虑树 A 的边的对应点对 $u,v$ 在树 B 上的距离，如果 $距离\geq 3$，那么 $u,v$ 是无敌点，我们处理出 B 那棵树以 $y$ 为根时（只是算无敌点的话根不是 $y$ 也行）每个点的深度 $g[]$，判定的话，不妨设 $g[u]\leq g[v]$，分类讨论可得如果满足$fa[v]=u,fa[fa[v]]=u,fa[u]=fa[v]$ 其中之一那么这个边没有无敌点的贡献。

然后考虑 A 有没有命活到点 $i$，需要 $x\to pre(i)$ 上的点都有命到达，以及 $i$ 也要有命到达，设 $f[i]$ 表示 A 上 $x\to i$ 的距离，然后 $i$ 额外的条件感觉是一个 $f[x]<g[x]$，但是这样有一个问题，比如有两条路径 $\alpha,\beta$ 分别可以被 B 阻止，可以保证 B 能同时挡下来嘛，是可以的，无敌点不需要继续拉点，于是 A 拉点的边在 B 连接的一定是距离为 $1$ 或 $2$ 的点，又因为 A 不能跳到 B 或者 B 相邻的位置，所以 A 一直会在树 B 以 B 为根的包含 A 的子树里面跳不出去，B 会一直往包含 A 的子树里面走，这样追捕关系是清晰的。

```cpp
#include<bits/stdc++.h>
#define up(i,l,r) for(int i=l; i<=r; ++i)
#define dn(i,r,l) for(int i=r; i>=l; --i)
#define pb push_back

using namespace std;

const int N=200005;

int n, x, y, u, v, fa[N], val[N], tag[N], diff, f[N], g[N], Ans;
vector<int> F[N], G[N];

void dfs1(int x,int fad) {
	f[x]=f[fad]+1;
	for(int y:F[x]) if(y!=fad) dfs1(y,x);
}

void dfs2(int x,int fad) {
	fa[x]=fad, g[x]=g[fad]+1; 
	for(int y:G[x]) if(y!=fad) dfs2(y,x);
}

void solve(int x,int fad) {
	if(f[x]>=g[x]) return;
	if(val[x]) { cout << -1; exit(0); }
	Ans=max(Ans,g[x]-1);
	for(int y:F[x]) if(y!=fad) solve(y,x);
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> x >> y;
	up(i,2,n) cin >> u >> v, F[u].pb(v), F[v].pb(u);
	up(i,2,n) cin >> u >> v, G[u].pb(v), G[v].pb(u);
	dfs1(x,0), dfs2(y,0);
	up(i,1,n) for(int j:F[i]) {
		u=i, v=j; if(g[u]>g[v]) swap(u,v);
		if(!(fa[v]==u||fa[fa[v]]==u||fa[u]==fa[v])) val[u]=val[v]=1;
	}
	solve(x,0), cout << 2*Ans;
	return 0;
}
```

---

## 作者：Xy_top (赞：0)

差一步想出来！

模拟样例可得，如果有两个点在 $A$ 树中相邻，且在 $B$ 树中距离大于等于 $3$，玩家 $A$ 又能到这对相邻的点中的任意一个，那他就可以一直耗下去了，称这种点为胜点，称距离为跨度。

很显然的想到通过 ``dfs`` 求出从 $A$ 树的点 $x$ 出发能到哪些点，但难求的就是这个，暂且不考虑胜点。考虑 $B$ 玩家的行动，这里有一个性质没有用到，就是没有胜点，这样把 $A$ 玩家的行动在 $B$ 树中画出来的话，每一步最多跨越两个点。考虑以 $Y$ 为根的 $B$ 树，初始时 $X$ 点一定在 $B$ 的子树内，每一步 $B$ 的行动一定是看看 $A$ 在哪个子树内，然后走到那个子树里。

这样貌似就能把 $A$ 锁死了，但即使跨度大于等于 $3$ 的点不能用，$A$ 也能用跨度为 $2$ 的点跳到 $B$ 的父亲上，此时 $B$ 只要向上走就能把游戏结束了，所以事实就是能把 $A$ 一直锁死在当前节点的子树内。

有人问如果有跨度很大的边让 $A$ 直接走到当前节点的兄弟的子树，或者其他类似的节点怎么办，也好办，这个点一定是能够到达的，那么 ``dfs`` 一遍后，看看能到的所有点中有没有胜点即可。

既然 $B$ 能够把 $A$ 锁死，如果 $A$ 想要到一个点 $u$，并且它需要 $x$ 步到点 $u$，那么 $B$ 到 $u$ 的步数一定要大于 $x$ 才行，不然就无法到（因为一直在它的子树内，它可以守株待兔），这样就得到 $A$ 能够到哪些点了。

之后就很简单了，先把胜点判掉，如果没有胜点，枚举 $A$ 走到哪个点，然后看一下多久后会被抓到取个 $\max$ 这题就做完了。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, x, y, ans;
int d[200005], dep[200005];
int f[200005][18];
bool vis[200005];
vector <int> G_[200005], G[200005];
void dfs (int u) {
	For (i, 1, 17) f[u][i] = f[f[u][i - 1] ][i - 1];
	for (int v : G[u]) {
		if (v == y || d[v]) continue;
		dep[v] = dep[u] + 1;
		d[v] = d[u] + 1;
		f[v][0] = u;
		dfs (v);
	}
}
int lca (int x, int y) {
	if (dep[x] < dep[y]) swap (x, y);
	foR (i, 17, 0) if (dep[f[x][i] ] >= dep[y]) {
		x = f[x][i];
	}
	if (x == y) return x;
	foR (i, 17, 0) {
		if (f[x][i] != f[y][i]) {
			x = f[x][i];
			y = f[y][i];
		}
	}
	return f[x][0];
}
int dis (int x, int y) {return dep[x] + dep[y] - 2 * dep[lca (x, y)];}
void dfs_ (int u, int di) {
	ans = max (ans, 2 * d[u]);
	vis[u] = 1;
	for (int v : G_[u]) if (!vis[v] && d[v] >= di + 1) dfs_ (v, di + 1);
}
void solve () {
	cin >> n >> x >> y;
	For (i, 2, n) {
		int u, v;
		cin >> u >> v;
		G_[u].push_back (v);
		G_[v].push_back (u);
	}
	For (i, 2, n) {
		int u, v;
		cin >> u >> v;
		G[u].push_back (v);
		G[v].push_back (u);
	}
	d[y] = 0;
	dep[y] = 1;
	dfs (y);
	dfs_ (x, 1);
	For (i, 1, n) {
		if (vis[i]) {
			for (int v : G_[i]) {
				if (dis (i, v) >= 3) {
					cout << -1;
					return;
				}
			}
		}
	}
	cout << ans;
}
signed main () {
	ios::sync_with_stdio (false);
	int _ = 1;
//	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}

```


---

## 作者：happybob (赞：0)

先考虑什么时候输出 $-1$。

我们令 $dis_{1,u}$ 表示树 $a$ 中从 $x$ 点走到 $u$ 经过的边数，同理 $dis_{2,u}$ 表示树 $b$ 中从 $y$ 点到 $u$ 经过边数。

我们对于一个点 $p$，当且仅当 $dis_{1,p} < dis_{2,p}$ 时，$x$ 点才可以到达 $p$。如果 $dis_{1,p}\geq dis_{2,p}$，那么一定会被抓到。

如果存在两个点 $u,v$，满足 $u$ 和 $v$ 直接相连，且 $x$ 点可以到达 $u$ 且可以到达 $v$ 的时候，如果 $u,v$ 两点在树 $a$ 的距离 $\geq 2$ 时，那么应该输出 $-1$，应为这时候 B 一定抓不到 A。

反之，如果不存在这样的点对 $(u,v)$，那么 $dis_{2,u} \times2$ 最大的 $u$ 使得 $x$ 可以到达 $u$ 就是答案，即 $x$ 走到 $u$，然后一直不走等着被抓。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
using namespace std;

const int N = 2e5 + 5;

vector<int> G1[N], G2[N];
int n, a, b, dis[N];
int ans, f[N];

void dfs(int u, int fa)
{
	dis[u] = dis[fa] + 1;
	f[u] = fa;
	for (int j : G2[u])
	{
		if (j != fa) dfs(j, u);
	}
}

void dfs2(int u, int fa, int len)
{
	if (len >= dis[u])
	{
		return;
	}
	ans = max(ans, dis[u]);
	//printf("%d %d\n", u, dis[u]);
	for (int j : G1[u])
	{
		if (j != fa)
		{
			int nlen = len + 1;
			int nu = u, nv = j;
			if (f[nu] != nv && f[nv] != nu && f[f[nu]] != nv && f[f[nv]] != nu && f[nu] != f[nv])
			{
				printf("-1\n");
				exit(0);
			}
			dfs2(j, u, nlen);
		}
	}
}

int main()
{
	scanf("%d%d%d", &n, &a, &b);
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		G1[u].emplace_back(v);
		G1[v].emplace_back(u);
	}
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		G2[u].emplace_back(v);
		G2[v].emplace_back(u);
	}
	dis[b] = -1;
	dfs(b, b);
	dfs2(a, 0, 0);
	printf("%d\n", ans * 2);
	return 0;
}
```



---

## 作者：Sktic (赞：0)

[AT2063 [AGC005E] Sugigma: The Showdown](https://www.luogu.com.cn/problem/AT2063)

$2022:10:12$ 修复部分 $\LaTeX$，现在公式和句号之间没有空格了。


神仙的博弈论！~~什么破壁人类智慧题~~



首先我们可以考虑什么时候游戏存在无解输出  ``-1`` 的情况。



通过手玩#4可以发现，当~~反复横跳~~逃方存在一条边 $u,v$，使得追方的树中 $u,v$ 两点之间的距离 $\ge3$ 时，且逃方先达到 $u,v$ 间任意一点不立刻被抓住，游戏就会一直进行。我们可以感性理解：因为追方想要到逃方所在的那个点，必须要走至少 $3$ 步，而在走到一半时追方必定无法同时守住 $u,v$，于是逃方只要随着追方的移动所移动然后反复横跳就行。



于是我们判定了无解的情况，接下来看看有解时追逃方的行动。假设目前的树有解，那么我们根据前面的结论可以发现，必然剩下的所有边中当逃方树的 $u,v$ 两点间距离 $=1$ 时，追方两点间 $u,v$ 距离必定 $\le 2$。



接着我们又可以发现，当以追方开始所在的节点为根作为一颗有根树时，逃方每走一步，都逃不出追方往下走所在的子树，因为追方可以同时控制它向上和向下的边，而逃方每次走一步在追方树上的距离又 $\le 2$ ，于是先手永远跳不过后手，因为跳一次就会被抓到。于是我们可以发现 $deep_x$ 一定小于 $deep_y$。于是追方的策略就是追着逃方的子树往下走。



于是我们可以发现，对于逃方不能反复横跳的情况，逃方一定是在不先被抓到的情况下，先走到一个在追方树中深度最大的节点，然后等死就行。



于是我们只需要先对追方的树进行一遍 $\text{dfs}$，然后算出每个节点深度与判断无解，再对逃方的树进行一遍 $\text{dfs}$，判断能走到的最深节点即可。



时间复杂度 $O(n)$，可以通过此题。

AC Code:

```C++
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
struct edge
{
	int u,v;
}c[maxn];
vector<int> tf[maxn],zf[maxn];
int deept[maxn],deepz[maxn],fa[maxn],vis[maxn];
int ans,op;
inline void init(int u,int f)
{
	fa[u]=f;
	for(int i=0;i<zf[u].size();i++)
	{
		int v=zf[u][i];
		if(v==f)
			continue;
		deepz[v]=deepz[u]+1;
		init(v,u);
	}
	return;
}
inline void dfs(int u,int f)
{
	if(vis[u])
	{
		cout<<-1<<endl;
		op=1;
		return;
	}
	ans=max(ans,deepz[u]);
	for(int i=0;i<tf[u].size();i++)
	{
		int v=tf[u][i];
		if(v==f)
			continue;
		deept[v]=deept[u]+1;
		if(deept[v]<deepz[v])
			dfs(v,u);
	}
	return;
}
inline int check(int u,int v)
{
	if(deepz[u]<deepz[v])
		swap(u,v);
	if(deepz[u]==deepz[v])
		if(fa[u]!=fa[v])
			return 1;
		else
			return 0;
	else if(deepz[u]==deepz[v]+1)
		if(fa[u]!=v)
			return 1;
		else
			return 0;
	else if(deepz[u]==deepz[v]+2)
		if(fa[fa[u]]!=v)
			return 1;
		else
			return 0;
	return 1;
}
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return x*f;
}
int main()
{
	int n,sta,stb;
	n=read();sta=read();stb=read();
	for(int i=1;i<=n-1;i++)
	{
		int u,v;
		u=read();v=read();
		tf[u].push_back(v);
		tf[v].push_back(u);
		c[i].u=u;
		c[i].v=v;
	}
	for(int i=1;i<=n-1;i++)
	{
		int u,v;
		u=read();v=read();
		zf[u].push_back(v);
		zf[v].push_back(u);
	}
	init(stb,-1);
	for(int i=1;i<n;i++)
	{
		int u=c[i].u,v=c[i].v;
		if(check(u,v)==1)
			vis[u]=vis[v]=1;
	}
	dfs(sta,-1);
	if(!op)
		cout<<ans*2<<endl;
	return 0;
}
```



---

