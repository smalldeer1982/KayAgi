# Complete the MST

## 题目描述

As a teacher, Riko Hakozaki often needs to help her students with problems from various subjects. Today, she is asked a programming task which goes as follows.

You are given an undirected complete graph with $ n $ nodes, where some edges are pre-assigned with a positive weight while the rest aren't. You need to assign all unassigned edges with non-negative weights so that in the resulting fully-assigned complete graph the [XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) sum of all weights would be equal to $ 0 $ .

Define the ugliness of a fully-assigned complete graph the weight of its [minimum spanning tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree), where the weight of a spanning tree equals the sum of weights of its edges. You need to assign the weights so that the ugliness of the resulting graph is as small as possible.

As a reminder, an undirected complete graph with $ n $ nodes contains all edges $ (u, v) $ with $ 1 \le u < v \le n $ ; such a graph has $ \frac{n(n-1)}{2} $ edges.

She is not sure how to solve this problem, so she asks you to solve it for her.

## 说明/提示

The following image showcases the first test case. The black weights are pre-assigned from the statement, the red weights are assigned by us, and the minimum spanning tree is denoted by the blue edges.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1508C/827fbacb0172346baa457498441b70bb4c8865ad.png)

## 样例 #1

### 输入

```
4 4
2 1 14
1 4 14
3 2 15
4 3 8```

### 输出

```
15```

## 样例 #2

### 输入

```
6 6
3 6 4
2 4 1
4 5 7
3 4 10
3 5 1
5 2 15```

### 输出

```
0```

## 样例 #3

### 输入

```
5 6
2 3 11
5 3 7
1 4 10
2 4 14
4 3 8
2 5 6```

### 输出

```
6```

# 题解

## 作者：syksykCCC (赞：14)

**引理**：所有未确定权值的边中，只有一条被确定为 $x$，其余所有边的权值都被确定为 $0$。

**证明**：考虑生成树的形态，有两种情况。

* MST 使用了所有未确定权值的边，那么根据 $\bigoplus w_e = x$，可以得到 $\sum w_e \ge x$。这是因为总是存在 $\sum w \ge \bigoplus w$。故可以在 $w_k = x, w_i =0$（$i\ne k$）的情况下取等。
* MST 没有使用所有未确定权值的边，那么我们可以令没被用的某条边的权值为 $x$，其他边的权值都为 $0$，代价显然是最小的。

我们在所有未确定权值的边上面进行 DFS。仅根据这些未被确定权值的边，这张图会被划分为若干个联通块，于是我们需要使用一些已经确定权值的边来确定 MST。我们将已经确定权值的边划分为 3 中类型：

1. MST 中必须使用的边：按照边权排序后，最小的那些连接两个不同连通块的边。
2. MST 中不可能存在的边：与边权更小的边形成环的边。换言之，不在原图 MSF（最小生成森林）中的边。
3. 不属于前两种情况的边。

对于未被确定权值的边，可以划分为两种情况：

* 未被确定权值的边形成了至少一个环：我们可以钦定这个环上的任意一条边为 $x$，其他为 $0$，那么使用这个环上的边权为 $0$ 的边以及第一类已经确定边权的边构造 MST。
* 未被确定权值的边没有形成环。假定我们仅仅使用未确定边权的边和第一类已经确定边权的边构造了一棵 ST，那么任何第三种类型的边可以替换一条未被确定权值的边。这是因为第三种类型的边必然会和第一种类型以及未确定权值的边构成一个环（否则它就是第一类或者第二类了）。如果存在某条第三种类型的边 $<x$，那么我们就可以进行替换。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
struct edge
{
	int u, v, w;
	bool operator < (const edge &oth) const
	{
		return w < oth.w;
	}
} e[N << 1];
int n, m, x, mn = INT_MAX;
long long ans, rem;
struct disjoint_sets_union
{
	int fa[N];
	int Query(int p)
	{
		if(fa[p] == p) return p;
		return fa[p] = Query(fa[p]);
	}
	
} dsu;
queue<int> que;
set<int> unvised, G[N];
bool vis[N], type[N];
void FindBlocks()
{
	for(int i = 1; i <= n; i++) if(!vis[i])
	{
		que.push(i);
		vis[i] = true;
		unvised.erase(i);
		dsu.fa[i] = i;
		while(!que.empty())
		{
			int u = que.front();
			que.pop();
			for(set<int>::iterator it = unvised.begin(); it != unvised.end();)
			{
				int v = *it;
				it++;
				if(G[u].count(v)) continue;
				dsu.fa[v] = u;
				unvised.erase(v);
				vis[v] = true;
				que.push(v);
				rem--;
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m;
	rem = 1LL * n * (n - 1) / 2 - m;
	for(int i = 1; i <= n; i++) unvised.insert(i);
	for(int i = 1; i <= m; i++)
	{
		cin >> e[i].u >> e[i].v >> e[i].w;
		G[e[i].u].insert(e[i].v);
		G[e[i].v].insert(e[i].u);
		x ^= e[i].w;
	}
	sort(e + 1, e + m + 1);
	FindBlocks(); 
	for(int i = 1; i <= m; i++)
	{
		int fau = dsu.Query(e[i].u), fav = dsu.Query(e[i].v);
		if(fau != fav)
		{
			dsu.fa[fau] = fav;
			ans += e[i].w;
			type[i] = 1; // type 1
		}
	}
	if(rem > 0) return printf("%lld\n", ans) && 0;
	for(int i = 1; i <= n; i++) dsu.fa[i] = i;
	for(int i = 1; i <= m; i++)
	{
		int fau = dsu.Query(e[i].u), fav = dsu.Query(e[i].v);
		if(fau == fav) continue; // type 2
		dsu.fa[fau] = fav;
		if(!type[i]) { mn = e[i].w; break; } // type 3
	}
	printf("%lld\n", ans + min(x, mn));
	return 0; 
}
```

---

## 作者：hater (赞：6)

分类讨论做法 /lb 

首先，我们自己构造的权值只会贴在一条边上，分类讨论即可证明。

如果这个图边很稀疏且随机，那么答案大概率是$0$，我们可以找到补图的一个生成树，之后把权值贴在其他边上。

那么什么情况下答案不为$0$呢？

可能是补图不连通，也可能是补图刚好为一棵生成树，我们找不到多余的一条边让我们贴权值。

情况有点多，我们先考虑后者。

补图刚好为一棵生成树，也就是说给出图边数接近完全图，这个时候点数不会超过$700$，这数据范围可以乱搞。

枚举把权值给在哪条边上，每次跑一遍最小生成树即可。

注意这个时候边数可以缩到$n$的级别，大概是先做一遍krusal，具体看代码。

再考虑前一种情况。

这个时候也要分两种情况，是否可以找到一条无用边贴权值，即补图是否有环。

有环即意味着我们可以把权值贴在不在生成树中的那条边。

如果找不到，点数也是少于$700$，套用上述做法也可以做。

如果找得到，我们可以把补图的连通块找出来，再用给的边做krusal。

怎么做补图的连通块，这是一道CF920E原题，先学学那题，蛤蛤。

这个憨憨用的是均摊做法。

先找到补图度数最大的点，将其全部联通，至少有$n-m/n$个点联通了，再将剩余$m/n$暴力$O(n)$做，时间复杂度均摊是$O(n+m)$

代码 ： 

```cpp
#include<bits/stdc++.h> 
#define rg register 
#define fp( i , x , y ) for( rg int i=(x); i<=(y); ++i ) 
#define fq( i , x , y ) for( rg int i=(y); i>=(x); --i ) 
#define i60 long long 
#define inf 1e18 
using namespace std ; 
const int N = 2e5+10 ;
struct node { 
  int x , y , z ; 
  friend bool operator < ( node A , node B ) { return A.z < B.z ; } 
} b[N] , c[N] , d[N] , e[N] ;   
vector <int> v[N] ; 
int n , m , len , pre[N] , me , deg[N] , lend ; bool is[805][805] , vis[N] , vis2[N] ;   
int f( int x ) { return pre[x] == x ? x : pre[x] = f(pre[x]) ; } 
bool too( int x , int y ) { return f(x) == f(y) ; } 
void merge( int x , int y ) { pre[f(x)] = f(y) ; } 
i60 calc( ) { 
  sort( e+1 , e+1+me ) ;  
  fp( i , 1 , n ) pre[i] = i ; 
  i60 ans = 0 ;  
  fp( i , 1 , me ) { 
    if( too( e[i].x , e[i].y ) ) continue ; 
	merge( e[i].x , e[i].y ) ; ans += e[i].z ;  
  } 
  return ans ; 
}  
void Sub2( ) { 
  fp( i , 1 , m ) { 
    deg[b[i].x] ++ ; deg[b[i].y] ++ ; 
    v[b[i].x].push_back(b[i].y) ; 
    v[b[i].y].push_back(b[i].x) ; 
  } 
  int id = 1 ; 
  fp( i , 1 , n ) pre[i] = i ; 
  fp( i , 1 , n ) if( deg[i] < deg[id] ) id = i ; 
  fp( i , 1 , (int)v[id].size() ) vis[v[id][i-1]] = 1 ; 
  fp( i , 1 , n ) if( !vis[i] ) pre[i] = id ; 
  fp( i , 1 , n ) { 
     if( !vis[i] || i == id ) continue ; 
     fp( j , 1 , n ) vis2[j] = 0 ; int tf = f(i) ; 
     fp( j , 1 , (int)v[i].size() ) vis2[v[i][j-1]] = 1 ; 
     fp( j , 1 , n ) if( !vis2[j] ) pre[f(j)] = tf ;  
  } 
  sort( b+1 , b+1+m ) ; 
  i60 ans = 0 ; 
  fp( i , 1 , m ) { 
    if( too( b[i].x , b[i].y ) ) continue ; 
    ans += b[i].z ; merge( b[i].x , b[i].y ) ; 
  } 
  cout << ans << '\n' ; 
} 
void Sub1( ) { 
  sort( b+1 , b+1+m ) ; 
  fp( i , 1 , n ) pre[i] = i ; 
  int al = 0 ;  
  fp( i , 1 , m ) { 
    is[b[i].x][b[i].y] = 1 ; al ^= b[i].z ; 
	if( too( b[i].x , b[i].y ) ) continue ; 
    merge( b[i].x , b[i].y ) ; c[++len] = b[i] ; 
  } 
  fp( i , 1 , n ) pre[i] = i ; 
  fp( i , 1 , n ) fp( j , i+1 , n ) { 
    if( is[i][j] || is[j][i] ) continue ; 
    if( too( i , j ) ) { Sub2() ; return ; } 
    merge( i , j ) ; d[++lend] = (node){ i , j , 0 } ; 
  } 
  i60 ans = inf ; 
  fp( i , 1 , lend ) { 
    me = 0 ; 
    fp( j , 1 , len ) e[++me] = c[j] ; 
    fp( j , 1 , lend ) { e[++me] = d[j] ; if( j == i ) e[me].z = al ; } 
	ans = min( ans , calc() ) ;  
  } 
  cout << ans << '\n' ; 	
} 
signed main( ) { 
  ios::sync_with_stdio(false) ; 
  cin.tie(0) ; 
  cin >> n >> m ; 
  fp( i , 1 , m ) cin >> b[i].x >> b[i].y >> b[i].z ; 
  if( n <= 705 ) Sub1() ; else Sub2() ; 
} 
```

这个憨批考场完全图点数判错了，$700$弄成$500$，下大分蛤蛤蛤。

---

## 作者：zjjws (赞：5)

### 题意

给定 $n$ 个点的无向完全图，其中 $m$ 条边的权值已给定，且为正值。

你需要给剩下的边赋上权值（非负），在满足所有边（$\frac{n\cdot (n-1)}{2}$ 条）权值异或起来为 $0$ 的情况下，让最小生成树的权值最小。

---

### Solution

##### Part 1 仅有一条边会被附上值

设那些已经赋上权值的边的异或和为 $x$。

对于那些没有确定权值的边，我们一定是将其中一条边赋为 $x$，并且将剩下的边定为 $0$。

否则，我们可以将其看做一条边权为 $x$ 的边在逐渐和边权为 $0$ 的边进行权值交换，这样显然 $\texttt{MST}$ 只可能会变大。

---

##### Part 2 稠密图的情况

考虑这样一种情况：剩下没有赋上边权的边和 $n$ 同阶。

那么这个时候，我们可以暴力枚举哪一条边被修改成了 $x$，然后跑一遍 $\texttt{MST}$，复杂度大致可以看做 $\operatorname O(n\sqrt n\log n)$ 的，这里的 $n$ 是 $2\cdot 10^5$。

（我考场上没时间想优化了，就写了这么丑陋的复杂度，事实上它跑得飞快）

---

##### Part 3 稀疏图的情况

如果剩下没赋值的边 $\ge n$，那么这些边构成的新图**一定存在环**，那么，我们就可以将 $x$ 这个边权塞到任意一条环上的边上，它不会对 $\texttt{MST}$ 产生影响。

现在问题在于：我们如何将这个 “补图”，边数如此多的东西提出来一个森林。

事实上这是一个 [原题](https://www.luogu.com.cn/problem/CF920E)。

然后再把那些初始有边权的边按边权从小到大加入，跑 Kruskal 即可。

---

### Code

非常丑，因为是考场代码（

真心不建议你们借鉴，除非你们有奇怪的审美癖好。

进行了一些修改，因为原来的考场代码是有锅的可能会挂掉（

~~大概是数据比较水赛场上把我放过去了~~

```cpp
int n,m;
int u[N];
int v[N];
int w[N];
int f[N];
int du[N];
int num[N];
map<int,bool>qy[N];
vector<pair<int,int> >d;
inline bool myru_num(int x,int y){return w[x]<w[y];}
inline int find(int i){return f[i]==i?i:(f[i]=find(f[i]));}
inline void work()
{
    rin>>n>>m;for(int i=1;i<=n;i++)f[i]=i,du[i]=n-1;
    int val=0;bool tag=false;
    for(int i=1;i<=m;i++)
    {
        rin>>u[i]>>v[i]>>w[i];qy[u[i]][v[i]]=qy[v[i]][u[i]]=true;
        val^=w[i];num[i]=i;du[u[i]]--;du[v[i]]--;
    }
    sort(num+1,num+m+1,myru_num);
    
    if((1LL*n*(n-1)>>1)>=n+m)
    {
        int st=0;
        for(int i=1;i<=n;i++)if(du[i]>du[st])st=i;
        for(int i=1;i<=n;i++)if(!qy[i][st])f[find(i)]=st;
        for(int i=1;i<=n;i++)
        if(find(i)!=st)
        {
            for(int j=1;j<=n&&find(i)!=st;j++)if(find(j)!=find(i)&&!qy[i][j])f[find(i)]=find(j);
        }
        LL ans=0;
        for(int i=1;i<=m;i++){int now=num[i];if(find(u[now])!=find(v[now]))ans+=w[now],f[find(u[now])]=find(v[now]);}
        printf("%lld\n",ans);
        return;
    }

    LL ans=0x3f3f3f3f3f3f3f3f;
    for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)if(!qy[i][j])d.push_back(make_pair(i,j));
    for(vector<pair<int,int> >::iterator to=d.begin(),i;to!=d.end();to++)
    {
        LL sum=0;for(int j=1;j<=n;j++)f[j]=j;
        for(i=d.begin();i!=d.end();i++)if(i!=to)f[find(i->first)]=find(i->second);
        int j;for(j=1;j<=m;j++){int now=num[j];if(w[now]>=val)break;if(find(u[now])!=find(v[now]))f[find(u[now])]=find(v[now]),sum+=w[now];}
        if(find(to->first)!=find(to->second))f[find(to->first)]=find(to->second),sum+=val;
        for(;j<=m;j++){int now=num[j];if(find(u[now])!=find(v[now]))f[find(u[now])]=find(v[now]),sum+=w[now];}
        ans=min(ans,sum);
    }
    printf("%lld\n",ans);
    return;
}
```

---

## 作者：L0vely_NaiL0ng (赞：2)

**好题**。

首先我先给出非给定边的赋权方案：非给定边一条边权为已知边权异或和，其余为 $0$。因为显然有若干个非负数的异或和小于等于这些数的和（将异或理解为不进位的加法），这样给非给定边赋权既可以让非给定边总和取到下界，也可以尽量多的使用权为 $0$ 的边（你考虑非给定边只有一条非 $0$，相比其它赋权方案很大概率这条非 $0$ 的边不在最终完全图的最小生成树上）。

然后用[这道题](https://www.luogu.com.cn/problem/CF920E)求出**只有非给定边的图**的每个连通块（这个比较简单就不展开讲了）。

将每个连通块缩点后得到的图的最小生成树上的边一定是最终最小生成树上的边（因为最终图是连通的，必须用给定边将它们连起来）。

如果某个连通块中有环，则一定可以把非 $0$ 的那条非给定边放到这个环上同时不计入最终完全图的最小生成树（将这条边断掉这个连通块仍然连通），答案为缩点后最小生成树（连通块内部的边全用 $0$）。

否则的话，相当于非给定边构成的每个连通块是树。

以下代码处理这种情况：

```
	int ans = 0;
	if (n * (n - 1) / 2 - m > c) res = 0;
	for (int i = 1; i <= n; i++) pa[i] = i;
	for (int i = 1; i <= m; i++) {
		int x = E[i].u, y = E[i].v, z = E[i].w;
		if (findfa(x) != findfa(y)) {
			mergefa(x, y); mergepa(x, y); ans += z;
		}
	} 
	for (int i = 1; i <= m; i++) {
		int x = E[i].u, y = E[i].v, z = E[i].w;
		if (findpa(x) != findpa(y)) res = min(res, z);
	}
	cout << ans + res;
```

$ans$ 为缩点后的最小生成树，$res$ 初始为已知边权异或和（非给定边中非 $0$ 的那条边的边权）。

这段代码之前，同一连通块中的 $fa$ 合并在了一起。

首先按边权从小到大遍历每条边，如果 `findfa(x) != findfa(y)` 代表这条边在缩点后的最小生成树上，加入答案，注意这里我们将 $pa$ 数组也合并了起来。

第二次循环，我们有判断 `findpa(x) != findpa(y)`，如果这二者相等，代表这条边和若干条在缩点后的最小生成树上的边形成了环，并且环上的边一定比这条边小（否则这条边可以替换环上的边让缩点后的最小生成树变小），这条边无法替换非给定边，略过。

否则这条边一定与若干条非给定边还有若干条缩点后最小生成树成环，那么可以尝试用这条边将其中一条非给定边（给这条非给定边赋权为初始的 $res$）替换掉，连通性不变。

以上的内容可能会有些难以理解，希望大家结合代码和众多题解反复研读，笔者在阅读了各类题解、代码数个小时后才写下这篇题解。

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, m, res, c, tot, cnt[N];
vector<int> e[N], z, pos[N];
set<int> s, t;
bool flag[N], vis[N];
queue<int> qu;
int fa[N], pa[N];
struct edge {
	int u, v, w;
} E[N];
bool cmp(edge i, edge j) {
	return i.w < j.w;
}
int findfa(int x) {
	if (fa[x] == x) return x;
	return fa[x] = findfa(fa[x]);
}
void mergefa(int x, int y) {
	int fx = findfa(x), fy = findfa(y);
	if (fx != fy) {
		fa[fy] = fx;
	}
}
int findpa(int x) {
	if (pa[x] == x) return x;
	return pa[x] = findpa(pa[x]);
}
void mergepa(int x, int y) {
	int fx = findpa(x), fy = findpa(y);
	if (fx != fy) {
		pa[fy] = fx;
	}
}
void bfs(int st) {
	qu.push(st); 
	flag[st] = 1;
	if (s.find(st) != s.end()) s.erase(st);
	pos[tot].push_back(st);
	while (!qu.empty()) {
		int x = qu.front(); qu.pop();
		t.clear(); z.clear();
		for (int y : e[x]) 
			if (s.find(y) != s.end()) {
				s.erase(y); t.insert(y);
			}
		for (int y : s) {
			qu.push(y); mergefa(pos[tot][pos[tot].size() - 1], y);
			flag[y] = 1; c++;
			if (s.find(y) != s.end()) z.push_back(y);
		}
		for (int y : z) s.erase(y);
		for (int y : t) s.insert(y);
	}
}
signed main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y, w; cin >> x >> y >> w;
		e[x].push_back(y); e[y].push_back(x);
		E[i] = {x, y, w}; res ^= w;
	}
	sort(E + 1, E + m + 1, cmp);
	for (int i = 1; i <= n; i++) {
		s.insert(i); fa[i] = i;
	}
	for (int i = 1; i <= n; i++) {
		if (!flag[i]) {
			tot++; bfs(i);
		}
	}
	int ans = 0;
	if (n * (n - 1) / 2 - m > c) res = 0;
	for (int i = 1; i <= n; i++) pa[i] = i;
	for (int i = 1; i <= m; i++) {
		int x = E[i].u, y = E[i].v, z = E[i].w;
		if (findfa(x) != findfa(y)) {
			mergefa(x, y); mergepa(x, y); ans += z;
		}
	} 
	for (int i = 1; i <= m; i++) {
		int x = E[i].u, y = E[i].v, z = E[i].w;
		if (findpa(x) != findpa(y)) res = min(res, z);
	}
	cout << ans + res;
	return 0;
}
```

---

## 作者：弦巻こころ (赞：2)

题意:你有一个完全图,其中$m$条边的边权是给定的,你需要给剩下的边赋权值,使得$xor$和为$0$,并且使得对于这个完全图求出的$mst$最小,输出最小的$mst$边权和.

首先有一个结论就是,我们一定只会用一条边来使得$xor$和为$0$,我们记这条边的权值为$mm$.

我们考虑怎么暴力实现这个东西,我们先求出这东西的补图,然后补图中的边权值都是0(先不考虑特殊边).然后我们暴力跑kruskal,发现我们会先把补图缩成一个连通块,然后再对剩下的k条边继续跑kruskal,然后对于特殊边,我们判下有没有环,如果有环特殊边就没有意义,如果没有环,我们则需要将答案加上 **与剩下的能替换的没选过的边**(没选过指没在kruskal中出现的边,能替换指它能替换一条补图边)和$mm$取个$min$.

对于怎么维护这个边,我们就再开个并查集,将树边缩起来,然后如果剩下未选中的边两端f不相同就是有效边,原理就是如果你f相同,那么你未选中的原因是因为后来跑kruskal导致了它出现了环中,而不是补图导致他出现在环中.

然后我们发现我们的时间复杂度瓶颈在于求补图连通块,这个可以用$set$维护下.就优化到$O(mlogm)$,具体怎么实现可以百度自学下(我考场上现学了这个,~~然后时间就不够用了~~).

总结一下:你先求出补图连通块,然后暴力跑kruskal,求下是否有补图环,如果没有你则需要再找下是否有可替换边,然后与$mm$去个min即可


代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=214514;
#define rep(i,j,k) for(int i=(j);i<=(k);i++)
#define per(i,j,k) for(int i=(j);i>=(k);i--)
#define int long long
struct ask{int x,y,z;}q[N];
int n,m,sp,ss,st,as,sm,mm,ct,v[N],f[N],gg[N],al[N],c[N];
set<int>s,G[N];
set<int>::iterator it;
bool cmp(ask a,ask b){return a.z<b.z;}
int get(int x){return gg[x]==x?x:gg[x]=get(gg[x]);} 
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
void bfs(int x){
    queue<int>q;s.erase(x);
    q.push(x);f[x]=ss;
    while(!q.empty()){
        int k=q.front();q.pop();
        for(it = s.begin();it != s.end();){
            int to = *it++;
            if(!G[to].count(k)){s.erase(to);q.push(to);f[to]=ss;}
        }
    }
}//求补图连通块
signed main(){scanf("%lld%lld",&n,&m);
	rep(i,1,n)s.insert(i),gg[i]=i;
	rep(i,1,m){scanf("%lld%lld%lld",&q[i].x,&q[i].y,&q[i].z)
		,mm^=q[i].z,G[q[i].x].insert(q[i].y),G[q[i].y].insert(q[i].x);
	}rep(i,1,n)if(!f[i])ct++,ss=i,bfs(i);
    rep(i,1,n)c[f[i]]++;
	rep(i,1,m)if(f[q[i].x]==f[q[i].y])al[f[q[i].y]]++;
	rep(i,1,n)if(c[f[i]]<=(1ll*(c[f[i]]*(c[f[i]]-1)/2)-al[f[i]]))sp=1;//判补图环
    sort(q+1,q+m+1,cmp);st=2e9;
	rep(i,1,m){int x=find(q[i].x),y=find(q[i].y);
		if(x==y){v[i]=1;continue;}
		f[x]=y;as+=q[i].z;
	}
	rep(i,1,m)if(!v[i])gg[get(q[i].x)]=get(q[i].y);//将树边缩起来
	rep(i,1,m)if(v[i]&&get(q[i].x)!=get(q[i].y))st=min(st,q[i].z);//如果f不相同,那么说明他可以替换边
	if(!sp)as+=min(st,mm);printf("%lld\n",as);
} 
```




小插曲:我考场上是这样实现判补图环的
```cpp
rep(i,1,n)if(c[f[i]]<=(1ll*(c[f[i]]*(c[f[i]]-1)/2)-al[f[i]]))sp=1;
```
但是我将它放在了kruskal的后面,然后就喜闻乐见的判挂了,~~(痛失rk1)~~


---

## 作者：7KByte (赞：1)

令所有给定边的异或和为 $x$ 。

那么一定只有一条非给定边为 $x$ ，其他非给定边一定全部为 $0$ 。

反证，假定有 $k>1$ 条指定边非零，如果答案的生成树包含所有 $k$ 条边，则等价于指定一条边为 $x$ ，否则，我们可以令包含的指定边为 $0$ ，答案一定更优。

如果非给定边成环，则等价于所有非给定边为 $0$ 。

反证，如果答案生成树包含为 $x$ 的边，则加入成环的条边，删去为 $x$ 的边使得答案更优。

所以我们分两种情况讨论。

第一种情况是有环的，我们用所有非给定边将原图上的连通块缩成一个点，再跑最小生成树。

第二种情况是没有环的，我们也用所有非给定边将原图上的连通块缩成一个点，跑最小生成树。但是得到的生成树中存在一条边权值为 $x$ 我们没有算进去。

对于这棵生成树上的给定边将连通块缩点。然后对于不在其中的给定边，如果属于两个不同的连通块，则可以用它替换原来的 $x$ 边。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
#define int long long
using namespace std;
int n,m,fa[N],in[N],f[N],cir,sum,ans,v[N];map<int,int>h[N];
struct node{
	int u,v,w;
	bool operator<(const node o)const{return w<o.w;}
}e[N];
int get(int x){return fa[x]==x?x:fa[x]=get(fa[x]);}
int g(int x){return f[x]==x?x:f[x]=g(f[x]);}
void solve(){
	int st=1;
	rep(i,1,n)if(in[i]>in[st])st=i;
	rep(i,1,n)if(i!=st&&!h[st].count(i))cir--,fa[i]=st,v[i]=1;
	rep(i,1,n)if(!v[i]){
		rep(j,1,n)if(i!=j&&!h[i].count(j)&&get(i)!=get(j))cir--,fa[get(i)]=get(j);
	}
}
signed main(){
	scanf("%lld%lld",&n,&m);cir=min(n*(n-1)/2-m,n+1);
	rep(i,1,n)fa[i]=f[i]=i,in[i]=i-1;
	rep(i,1,m)scanf("%lld%lld%lld",&e[i].u,&e[i].v,&e[i].w),sum^=e[i].w,
		h[e[i].u][e[i].v]=h[e[i].v][e[i].u]=1,in[e[i].u]--,in[e[i].v]--;
	sort(e+1,e+m+1);solve();int mn=0x7fffffff;
	rep(i,1,m)if(get(e[i].u)!=get(e[i].v))ans+=e[i].w,fa[get(e[i].u)]=get(e[i].v),f[g(e[i].u)]=g(e[i].v);
	rep(i,1,m)if(g(e[i].u)!=g(e[i].v))mn=min(mn,e[i].w);
	if(cir)printf("%lld\n",ans);else printf("%lld\n",ans+min(mn,sum));
	return 0;
}
```

---

## 作者：王江睿 (赞：0)

一种广为人知的算法可在补图上实现 $O(n+m)$ 的 BFS，其中 $n$ 是点数，$m$ 是原始边数。具体地：

``` python pseudo
# Q is a queue, L is a list, B is a boolean array

L.delete(s), Q.push(s);
while ~Q.empty():
    u ← Q.front()
    for v ∈ E[u]: B[v] ← true
    for v ∈ L: 
        if B[v] == false:
            L.delete(v), Q.push(v)
    for v ∈ E[u]:
        B[v] ← false
    Q.pop()
```

这样，用并查集就得到完全由补图边构成的连通块。

XOR 和不大于和，若选择 2 条带权边必劣于仅选 1 条。即补图中仅 1 条边带权，权为原边的 XOR 和，其余边权均为 $0$。

若在补图中形成了一个环，我们总是将环上的非树边置值。可以清楚地看到，这和补边权均为 $0$ 等价。

是时，答案是 **通过原始边收缩由补图边组成的连通分量的总权重**。

否则，需要找到一条最小的原始非树边，该边可以代替树补图边。这样的边满足，原图通过树原始边收缩后，它的 2 端位于不同的分量中。答案即为之前的总和加上它的边权。

用 Borůvka 算法，复杂度 $O((m+n)\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
enum{_n=200007};
int PR[_n],SU[_n];
void del(int x)
{SU[PR[x]]=SU[x],PR[SU[x]]=PR[x];}
bitset<_n> B;
int q[_n],f,e;
u32string ans;
struct{int x,y,l;}E[_n];
int idx;
u32string G[_n];
int n,m,dis[_n],to[_n],ori[_n],cnt;
int64_t sum;
bitset<_n> cb;
struct FIN{ 
	int operator()(int x){return F[x]?F[x]=(*this)(F[x]):x;} 
	int F[_n]; }T1,T2;
void boruvka(){
	for(int i=0;i<m;++i)if(!cb[i]){
		auto[x,y,l]=E[i]; x=T1(x),y=T1(y);
		if(x!=y){
			if(dis[x]>l)
				to[x]=y,dis[x]=l,ori[x]=i;
			if(dis[y]>l)
				to[y]=x,dis[y]=l,ori[y]=i;
		}else cb[i]=1;
	}
	for(int i=1,t;i<=n;++i)if(!T1.F[i]){
		t=T1(to[i]);
		if(t!=i)
			T1.F[i]=t,T2.F[T2(E[ori[i]].x)]=E[ori[i]].y,--cnt,sum+=dis[i];
		else to[i]=0,dis[i]=1.1e9;
	}
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m;
	int ex=0;
	for(int i=0,x,y,w;i<m;++i)
		cin>>x>>y>>w,G[x]+=y,G[y]+=x,ex^=w,E[idx++]={x,y,w};
	iota(PR+1,PR+n+1,0);
	iota(SU,SU+n,1);
	bool fc=0;
	for(int64_t pt,deg;q[e=1,f=0]=SU[0];){
	  for(del(SU[0]),pt=deg=0;f!=e;++f){
		++pt; int u=q[f];
		for(int v:G[u]) B[v]=1;
		deg+=n-1-G[u].size();
		for(int v=SU[0];v;v=SU[v])
			if(!B[v]) 
				T1.F[T1(v)]=u,q[e++]=v,del(v);
		for(int v:G[u]) B[v]=0;
	  } fc|=deg^2*pt-2; ++cnt; }
	for(memset(dis+1,99,4*n);cnt^1;)
		boruvka();
	if(fc) cout<<sum<<'\n';
	else{ for(int i=0;i<m;++i)
			if(T2(E[i].x)!=T2(E[i].y))
				ex=min(ex,E[i].l);
		cout<<sum+ex<<'\n';
	}
}
```

---

## 作者：lsj2009 (赞：0)

### Solution

好题。

显然最优地情况下是我们只通过 $0$ 的边就可以构成这个最小生成树。我们考虑先把补图连通块给拿出来，这个也就是 CF920E，然后再补图上不连通的点显然就是要通过已经给定的边连通，再跑个最小生成树即可。

但是题目还有一个要求是，需要整张图的边权异或值为 $0$。我们考虑设已知边权的异或值为 $x$，那么有个结论是，我们恰好只让一条边的边权非 $0$，为 $x$。

- 证明：带权边的数量越少，越不容易选到带权边，所以如果说我们只令一条边带权，也必须要选那条边的话，那么我们把那条带权边拆成若干条边，则被拆出来的所有边都要选；又因为 $\sum w_i\ge \oplus w_i$，所有我们只令一条边带权是最优的。

如果说补图连通块中存在一个环，我们令这条带权边成为环上一条没用的边即可，这样子就不会被选到。

否则这条带权边必然会被选到，但是如果说另一条已经给定的带权边可以使得我们已经求出的生成树出现一个环，那么我们就可以让那条带权边替代这条边权为 $x$ 的边，取个 $\min$ 即可。

然后就做完了，复杂度 $\Theta(m\log{m})$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=1e6+5;
int head[N],out[N],len;
struct node {
	int from,to,w,nxt;
	bool operator < (const node &tmp) const {
		return w<tmp.w;
	}
}; node edge[N<<1];
void add_edge(int u,int v) {
	edge[++len]={u,v,0,head[u]}; head[u]=len; ++out[u];
}
int fa[N],pa[N];
int get_fa(int x) {
	if(fa[x]!=x)
		fa[x]=get_fa(fa[x]);
	return fa[x];
}
int get_pa(int x) {
	if(pa[x]!=x)
		pa[x]=get_pa(pa[x]);
	return pa[x];
}
int used[N],p,n,m;
bool usedd[N];
void update(int u,bool sign) {
	++p;
	for(int i=head[u];i;i=edge[i].nxt) {
		int v=edge[i].to; used[v]=p;
		if(sign)
			usedd[v]=true;
	}
	rep(i,1,n) {
		if(used[i]!=p)
			fa[get_fa(i)]=get_fa(u);
	}
}
int solve() {
	int k=1;
	rep(i,1,n) {
		if(out[i]<out[k])
			k=i;
	}
	update(k,1);
	rep(i,1,n) {
		if(usedd[i]&&i!=k)
			update(i,0);
	}
	int cnt=0;
	rep(i,1,n)
		cnt+=get_fa(i)==i;
	return cnt;
}
vector<node> e;
signed main() {
	scanf("%lld%lld",&n,&m);
	rep(i,1,n)
		fa[i]=pa[i]=i;
	int res=0;
	rep(i,1,m) {
		int u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w); res^=w;
		add_edge(u,v);
		add_edge(v,u);
		e.push_back({u,v,w,0});
	}
	int cnt=solve(),ans=0;
	if(n*(n-1)/2-m-n+cnt>0)
		res=0;
	sort(e.begin(),e.end());
	for(auto x:e) {
		int u=x.from,v=x.to,w=x.w;
		if(get_fa(u)!=get_fa(v)) {
			fa[get_fa(u)]=get_fa(v); pa[get_pa(u)]=get_pa(v);
			ans+=w;
		}
	}
	for(auto x:e) {
		int u=x.from,v=x.to,w=x.w;
		u=get_pa(u); v=get_pa(v);
		if(u!=v)
			res=min(res,w);
	}
	printf("%lld\n",ans+res);
    return 0;
}
```

---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1508C)

## 思路

首先我们有一个简单的结论：你一定只给一条边赋上边权，另外边权都是 $0$。

简单证明一下：

设给出的边的边权的异或和为 $r$，假设你赋值了 $k\ (k>1)$ 条边，权值分别为 $a_1,...,a_k$，显然 $\sum a_i \ge r$。那么有以下几种情况：

+ 这 $k$ 条边都在最小生成树中，那么把边权都转移到一条边上一定不劣。

+ 有一些边在最小生成树中，一些边不在，那么把边权都转移到不在的那条边上一定更优。

那么，我们现在的目标就是给最小生成树内尽可能多的边赋上 $0$ 权。

接下来先求出补图的连通块，这是一个经典问题，可以在 $\mathcal O(n+m)$ 的时间复杂度内解决。

然后又有两种情况：

+ 这些连通块中存在环。

+ 这些连通块中不存在环。

存在环是简单的，因为此时存在没用的边，任选一条没用的边，然后把边权设为 $r$，此时这条边一定不在最小生成树中，最后把给出的 $m$ 条边按边权排序后 $\rm Kruskal$ 即可。

如果不存在环，则每条边都是有用的，似乎不可避免的需要把 $r$ 加进答案。

不过我们可以选择一条边权更小的边替换 $r$。

列举以下某条边可以替换 $r$ 的条件：

+ 加入这条边后最小生成树上出现了一个环。

+ 环上至少存在一条边不是给出的 $m$ 条边中的。

于是跑两遍 $\rm Kruskal$ 即可，第一遍求出最小生成树，第二遍求出替换 $r$ 的边。

时间复杂度 $\mathcal O(n+m \log m)$，瓶颈在于排序。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face is invincible.
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=2e5+10;
int du[N],r,mp[N],ind[N],fa[N],a1[N],a2[N];
bitset<N>g[1005];
struct node{int x,y,w;}a[N];
int find(int x){
	return (x==fa[x])?x:fa[x]=find(fa[x]);
}
void solve(){
	int n,m;cin>>n>>m;
	for (int i=1;i<=m;++i){
		cin>>a[i].x>>a[i].y>>a[i].w;
		++du[a[i].x],++du[a[i].y],r^=a[i].w;
	}
	int mi=1;
	for (int i=1;i<=n;++i) fa[i]=i;
	for (int i=1;i<=n;++i)
		if (du[i]<du[mi]) mi=i;
	for (int i=1;i<=m;++i){
		if (a[i].x==mi) mp[a[i].y]=1;
		if (a[i].y==mi) mp[a[i].x]=1;
	}
	for (int i=1;i<=n;++i)
		if (mp[i]==1) a1[++a1[0]]=i,a2[i]=a1[0];
		else fa[i]=mi;
	for (int i=1;i<=m;++i){
		if (mp[a[i].x]==1) g[a2[a[i].x]][a[i].y]=1;
		if (mp[a[i].y]==1) g[a2[a[i].y]][a[i].x]=1;
	}
	for (int i=1;i<=a1[0];++i){
		int x=a1[i];
		for (int j=1;j<=n;++j){
			if (g[i][j]) continue;
			if (find(x)==find(j)) continue;
			fa[find(x)]=find(j);
		}
	}
	int ct=0,k=n*(n-1)/2-m,ans=0;
	for (int i=1;i<=n;++i) ct+=(find(i)==i);
	sort(a+1,a+m+1,[](node a,node b){return a.w<b.w;});
	for (int i=1;i<=m;++i){
		int x=find(a[i].x);
		int y=find(a[i].y);
		if (x^y) ind[i]=1,fa[x]=y,ans+=a[i].w;
	}
	if (n-ct==k){
		ans+=r;
		for (int i=1;i<=n;++i) fa[i]=i;
		for (int i=1;i<=m;++i){
			int x=find(a[i].x);
			int y=find(a[i].y);
			if (x==y) continue;
			fa[x]=y;
			if (!ind[i]){ans+=min(0ll,a[i].w-r);break;}
		}
		cout<<ans<<'\n';
	}else cout<<ans<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t=1;
	// cin>>t;
	while (t--) solve();
	cerr<<"Running Time: "<<(double)clock()/CLOCKS_PER_SEC<<" s\n";
	return 0;
}
```

---

## 作者：_ZSR_ (赞：0)

### [CF1508C Complete the MST](https://www.luogu.com.cn/problem/CF1508C)

因为要最小化最小生成树的边权和，所以对于没有确定边权的边肯定尽量赋成 $0$。但是我们还要满足异或和为 $0$，这使得我们不得不把一些边设成非零的边权。众所周知，异或又叫做不进位加法，因此有一个结论：假设所有给定的边权异或和为 $x$，那么对于所有没有给定边权的边，把其中一条赋成 $x$，其余的都赋成 $0$ 一定是最优的。

证明：因为所有没有确定边权的边的边权异或和要等于 $x$，所以 $\sum w \geq x$，故把其中一条边赋成 $x$，其余的都赋成 $0$ 一定是最优的。

接下来考虑最小生成树的权值和。对于给定边权的边，可以分成三类。一种是肯定会选的，即在只考虑不确定边权的边的情况下，连接两个连通块的边权最小的边。一种是肯定不会选的，即在只考虑确定边权的边的情况下都不会选进最小生成树的边。还有一种就是不属于上面两种情况的边。

对于没有确定边权的边，如果它们成环了，那么我们直接把环上的一条边设成 $x$，然后不选它。如果没有成环，我们先求出一棵只包含没有确定边权的边和所有肯定会选的边组成的生成树。在这棵树上，我们唯一能改变的就是那条边权为 $x$ 的边，所以考虑换掉它会不会更优。但是要换就只能拿第三种确定边权的边来换，所以我们求出最小的第三种确定边权的边的边权，如果小于 $x$，那么就把 $x$ 换掉，否则就继续保留 $x$。

至于怎么求出是哪种类型，可以参考 [CF920E Connected Components?](https://www.luogu.com.cn/problem/CF920E)。

code
```
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
typedef long long ll;
int n,m,sum;
ll ans,rest;
set<int> S,to[N];
struct Edge{
    int u,v,w;
    bool operator< (const Edge &t) const
    {
        return w<t.w;
    }
}edge[N];
int fa[N],type[N];
bool vis[N];
int find(int x)
{
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
inline void findblocks()
{
    queue<int> q;
    for (int i=1;i<=n;++i)
    {
        if (vis[i]) continue;
        q.push(i);
        vis[i]=true;
        fa[i]=i;
        S.erase(i);
        while (q.size())
        {
            int u=q.front();
            q.pop();
            for (auto it=S.begin();it!=S.end();)
            {
                int v=*it;
                ++it;
                if (to[u].count(v)) continue;
                fa[v]=u;
                vis[v]=true;
                S.erase(v);
                q.push(v);
                --rest;
            }
        }       
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    rest=1ll*n*(n-1)/2-m;
    for (int i=1;i<=n;++i) S.insert(i);
    for (int i=1;i<=m;++i)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        edge[i]={u,v,w};
        to[u].insert(v),to[v].insert(u);
        sum^=w;
    }
    findblocks();
    sort(edge+1,edge+m+1);
    for (int i=1;i<=m;++i)
    {
        int u=find(edge[i].u),v=find(edge[i].v);
        if (u!=v)
        {
            fa[u]=v;
            ans+=edge[i].w;
            type[i]=1;
        }
    }
    if (rest>0) printf("%lld\n",ans);
    else
    {
        for (int i=1;i<=n;++i) fa[i]=i;
        for (int i=1;i<=m;++i)
        {
            int u=find(edge[i].u),v=find(edge[i].v);
            if (u==v) continue;
            fa[u]=v;
            if (!type[i]) 
            {
                ans+=min(sum,edge[i].w);
                break;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```


---

## 作者：EuphoricStar (赞：0)

比较需要观察的题。

设 $v$ 为所有边权异或和。直觉是设一条未确定权值的边边权为 $v$，其他的为 $0$ 最优。证明大概就是讨论 MST 是否全部使用未确定权值的边。若全使用了，那么根据 $\oplus w \le \sum w$ 可知 $\min \sum w = \oplus w$，并且在 $w$ 两两按位与均为 $0$ 时取等；若没有全使用，可以把没使用的赋成 $v$，其他全赋成 $0$。

发现若补图存在环，我们只要把一条构成环的边边权设为 $v$ 即可，显然它会被环上其他边替代。补图存在环的一个必要条件是 $m < \frac{n(n - 1)}{2} - n + 1$，因为补图边数 $\ge n$。这种情况下，我们先求出补图连通块，将他们作为边权为 $0$ 的边在并查集上 merge 起来，再做一遍 Kruskal 即可。至于如何求补图连通块，这是个[典题](https://www.luogu.com.cn/problem/CF920E)，可以考虑暴力 + 链表（并查集），具体见[此](https://www.luogu.com.cn/blog/275273/solution-cf920e)。这部分时间复杂度 $O(m \log m + (n + m) \log n)$。

若 $m \ge \frac{n(n - 1)}{2} - n + 1$，此时补图边数 $< n$，又因为 $m$ 是 $O(n^2)$ 级别，因此 $n$ 是 $O(\sqrt{m})$ 的。此时可以直接暴力枚举将补图的哪条边边权设为 $v$，再做 Kruskal 即可。这部分时间复杂度 $O(m \sqrt{m} \log n)$，实际用时不多。

[code](https://codeforces.com/problemset/submission/1508/213104587)

---

## 作者：MuelsyseU (赞：0)

[0-1 MST](https://www.luogu.com.cn/problem/CF1242B) 强化版，考虑补图连通块。

异或和等于 $0$ 其实是虚的，因为但凡有 $1$ 条未给定边一定用不到就可以直接令它为给定边异或和，规避这个限制了。

形式化地说，这个补图的连通块中有至少一个连通块有环。

另一方面，会发现若都没有环，补图就是森林，边数不超过 $n - 1$。于是边数至少为 $\frac{n(n-1)}{2}-n+1=O(n^2)$。考虑枚举其中一条边贴权值再跑 Kruskal。$O(nm\log n)$ 显然不优秀，但是每次既然只改变一条边，那么每次修改被贴权值的边，拿个 `vector` 朴素地移动发生更改的两条边的位置，就是 $O(nm)=O(m\sqrt{m})$。

实际上是根号分治。后面部分也可以在分类讨论后做到 $O(m\log n)$。



---

