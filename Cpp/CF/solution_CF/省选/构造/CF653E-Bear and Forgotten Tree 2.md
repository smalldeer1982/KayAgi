# Bear and Forgotten Tree 2

## 题目描述

A tree is a connected undirected graph consisting of $ n $ vertices and $ n-1 $ edges. Vertices are numbered $ 1 $ through $ n $ .

Limak is a little polar bear. He once had a tree with $ n $ vertices but he lost it. He still remembers something about the lost tree though.

You are given $ m $ pairs of vertices $ (a_{1},b_{1}),(a_{2},b_{2}),...,(a_{m},b_{m}) $ . Limak remembers that for each $ i $ there was no edge between $ a_{i} $ and $ b_{i} $ . He also remembers that vertex $ 1 $ was incident to exactly $ k $ edges (its degree was equal to $ k $ ).

Is it possible that Limak remembers everything correctly? Check whether there exists a tree satisfying the given conditions.

## 说明/提示

In the first sample, there are $ n=5 $ vertices. The degree of vertex $ 1 $ should be $ k=2 $ . All conditions are satisfied for a tree with edges $ 1-5 $ , $ 5-2 $ , $ 1-3 $ and $ 3-4 $ .

In the second sample, Limak remembers that none of the following edges existed: $ 1-2 $ , $ 1-3 $ , $ 1-4 $ , $ 1-5 $ and $ 1-6 $ . Hence, vertex $ 1 $ couldn't be connected to any other vertex and it implies that there is no suitable tree.

## 样例 #1

### 输入

```
5 4 2
1 2
2 3
4 2
4 1
```

### 输出

```
possible
```

## 样例 #2

### 输入

```
6 5 3
1 2
1 3
1 4
1 5
1 6
```

### 输出

```
impossible
```

# 题解

## 作者：_Anchor (赞：3)

##### Problem

一棵$n$个点的树，再给出如下信息：

- 点 $1$ 的度数是 $k$
- 给定 $m$对 $u$和$v$，满足 $u$和 $v$之间**不存在**边

询问以上信息是否合法（是否存在这样的树）

合法输出 $possible$，否则输出 $impossible$

##### Solution

我们分开考虑两个条件，首先，我们把$1$结点分开来，也就是说，我们先考虑第一个限制：

首先，如果$1$结点的度数小于$k$，那么直接输出$impossible$

否则，说明$1$结点的度数大于等于$k$，我们继续往下。

我们考虑这样的事情：

我们把除了$1$结点之外的所有点都进行连边，也就是说，我们先把不能连的边全部去掉，再把能连的边全部连上

那么原图就变成了一个个连通块，那么现在我们可以考虑$1$号点的限制了

如果我们的连通块个数大于$k$，那么就不行，输出$impossible$，因为在这种情况下，$1$连出去的边一定是大于$k$的，不符合题意

否则我们继续考虑：

如果某一个连通块不能到达$1$号结点（即该连通块中每一个点都不能连向$1$），那么输出$impossible$，因为这样的话整张图不连通，不可能构成树

那么其余所有情况都是可能的，输出$possible$

至于实现，我们肯定不能强行加边然后求连通块，这样干复杂度爆炸，所以我们使用$set/unordered$_$set$来维护连通块的元素，使用$BFS$来找连通块，于是这道题就做完了，剩下的看代码实现

##### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
    x=0;char ch=getchar();bool f=false;
    while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=f?-x:x;
    return ;
}
template <typename T>
inline void write(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10^48);
    return ;
}
template <typename T>
inline void print(T x){write(x),putchar(' ');}
#define ll long long
#define ull unsigned long long
#define inc(x,y) (x+y>=MOD?x+y-MOD:x+y)
#define dec(x,y) (x-y<0?x-y+MOD:x-y)
#define min(x,y) (x<y?x:y)
#define max(x,y) (x>y?x:y)
const int N=3e5+5,M=1e6+5,MOD=1e9+7;
int n,m,k,to;
unordered_set<int> now,inv[N];
vector<int> vec;
bool vis[N];
bool bfs(int st){
    queue<int> q;
    bool flag=true;q.push(st);vis[st]=true;
    vec.clear();
    while(!q.empty()){
        int x=q.front();q.pop();
        for(auto v:now){
            if(!vis[v]&&!inv[x].count(v)&&v!=x){
                vec.push_back(v);
                vis[v]=true;
                q.push(v);
            }
        }
        if(!inv[x].count(1)) flag=false;
        for(auto v:vec) now.erase(v);
        vec.clear();
    }
    return flag;
}
int main(){
    read(n),read(m),read(k);to=n-1;
    for(int i=2;i<=n;i++) now.insert(i);
    for(int i=1;i<=m;i++){
        int u,v; 
        read(u),read(v);
        inv[u].insert(v);
        inv[v].insert(u);
        if(u==1||v==1) to--;
    }
    if(to<k){puts("impossible");return 0;}
    for(int i=2;i<=n;i++){
        if(!vis[i]&&now.count(i)){
            if(bfs(i)){
                puts("impossible");return 0;
            }
        }
    }
    if(now.size()>k) puts("impossible");
    else puts("possible");
    return 0;
}
```


---

## 作者：Purslane (赞：1)

# Solution

`*2400` 的简单题。

考虑求出和 $1$ 相邻的边数的最大值 $mx$ 以及最小值 $mn$（要求 $G$ 的补图联通）。题目要求的是 $mn \le k \le mx$。

> 这一步的原理：考虑求出 $mn$ 对应的一个生成树，把不在生成树的、和 $1$ 相邻的边加入生成树里，直到 $1$ 的度数是 $k$。

考虑求 $mx$：将和 $1$ 相邻的边赋值为 $0$，和 $1$ 不相邻的边赋值为 $1$，求 MST；考虑求 $mn$：将和 $1$ 相邻的边赋值为 $1$，和 $1$ 不相邻的边赋值为 $0$，求 MST。

模仿 Kruskal 的形式，我们只需要解决以下问题：给定图 $G$，求出他补图 $G'$ 形成的联通块。

使用增量法，每次加一个点。对于之前每一个联通块，暴力计算他和这个点之间的连边个数。如果之间没有连边，那么可以合并两个联通块，这部分复杂度是 $O(n)$（势能分析）；否则，这部分的总复杂度是 $O(m)$（必须至少有一条边）。

总的复杂度是 $O((n + m) \log n)$。（使用 set 维护所有所有联通块的编号。实际上使用双向链表可以把整道题做到线性）

---

## 作者：FreedomKing (赞：1)

### 思路

首先对输入所给出的边进行分析，输入的边是不能存在于图中的，而数据范围又过大，我们不能建出整个图来。考虑这张图的小性质，这是一张极其稠密的图，我们可以枚举每个点连接其他点寻找连通块，复杂度为平方。考虑使用 set 进行优化，每次遍历完都将节点从 set 中进行 erase 操作，复杂度为线性，可以接受。

处理完图的遍历的问题，思考如何解决是否存在合法生成树的问题。显然的整张图中包含了若干个连通块，可以通过遍历寻找出来，设共有 $s$ 个连通块，对其进行讨论：

- 当 $s=k$，每个连通块可以由任意一个节点连接一条边到节点 $1$，如果有，输出 `possible`，如果整个连通块不存在可以连接到节点 $1$ 第节点那次连通块必然不与生成树连通，输出 `possible`。

- 当 $s<k$，虽然连通块个数少于节点 $1$ 的入度，但是可以通过对连通块进行若干次拆解，将 $s$ 个连通块拆解为 $k$ 个，化成了第一种情况，输出 `possible`。

- 当 $s>k$，连通块个数过多，无论如何也无法构建合法生成树，输出 `impossible`。

### AC Code

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#define int long long
using namespace std;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
const int N=1e6+5,mN=5e3+5,mod=1e9+7;
namespace FreedomKing_qwq{
#define lowbit(_) (_&-_)
	struct Tree{
		int tree[N];
		inline void add(int x,int k){
			for(int i=1;i<=x;i+=lowbit(i)) tree[i]+=k;
			return;
		}
		inline int query(int x){
			int ans=0;
			for(int i=x;i>1;i-=lowbit(i)) ans+=tree[i];
			return ans;
		}
	};
	struct Dset{
		int fa[N];
		inline void init(int x){
			for(int i=1;i<=x;i++) fa[i]=i;
			return;
		}
		inline int find(int x){
			return (fa[x]==x?x:fa[x]=find(fa[x]));
		}
		inline void update(int x,int y){
			x=find(x);y=find(y);
			fa[y]=x;
			return;
		}
	};
#define lc (p<<1)
#define rc (p<<1|1)
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}	
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:1e18);
		if(p<0) return qpow(qpow(x,-p,mod),mod-2,mod);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){return (x/gcd(x,y)*y);}
	//	inline int max(int x,int y){return (x>y?x:y);}
	//	inline int min(int x,int y){return (x<y?x:y);}
	//	inline int abss(int x){return (x>=0?x:-x);}
}
map<pair<int,int>,bool>mp;
unordered_set<int>st;
bool vis[N];
vector<int>f;
inline void bfs(int x){
	queue<int>q;
	q.push(x);
	vis[x]=true;
	bool flag=false;
	while(!q.empty()){
		int u=q.front();q.pop();
		flag|=!mp[{1,u}];
		for(auto v:st){
			if(!vis[v]&&!mp[{u,v}]&&x!=v){
				vis[v]=true;
				q.push(v);
				f.push_back(v);
			}
		}
		for(auto x:f) st.erase(x);
		f.clear();
	}
	if(!flag){
		puts("impossible");
		exit(0);
	}
	return;
}
signed main(){
	int n=qr,m=qr,k=qr;
	for(int i=2;i<=n;i++) st.insert(i);
	int cnt=0;
	for(int i=1;i<=m;i++){
		int u=qr,v=qr;
		cnt+=(u==1||v==1);
		mp[{u,v}]=true;
		mp[{v,u}]=true;
	}
	if(n-1-cnt<k) return puts("impossible"),0;
	for(int i=2;i<=n;i++) if(!vis[i]&&st.count(i)) bfs(i);
	if(st.size()>k) return puts("impossible"),0;
	puts("possible");
	return 0;
}
```

---

## 作者：幻影星坚强 (赞：1)

假如能到达1的边数小于k肯定不行。然后则看除1号节点的其他节点，如果他们所组成联通块的数量大于了k，那么每一个联通块连到1才能构成树，这样度数就大于k了。如果有个联通块它不能到达1，那么显然整个图也是不联通的。否则一定能通过将一个块分成一些小块来使得1的度数为k。

至于求联通块采用bfs，显然不能直接建图，于是用链表来存储未走过的点来枚举防止暴力枚举复杂度到$O(n)$

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
struct bian
{
	int from, to;
}eg[300010 << 1];
int front[300010], num;
void lian(int x, int y)
{
	eg[++ num].to = y;
	eg[num].from = front[x];
	front[x] = num;
}
vector<int>v;
int vis[300010], col[300010], sf[300010], can[300010], y[300010];
int n, m, k, d, ans;
int q[300010];
int rr[300010], ll[300010];
void bfs(int o)
{
	int l = 0, r = 0;
	q[r ++] = o;
	while(l < r)
	{
		int now = q[l ++];
		vis[now] = 1;
		int first = 0;
		for (int i = front[now]; i; i = eg[i].from)
		{
			int to = eg[i].to;
			y[to] = 1;
		}
		for (int i = 1; i <= n; i = rr[i])
		{
			if(y[i] == 0 && vis[i] == 0)
			{
				col[i] = col[now];
				q[r ++] = i;
				rr[ll[i]] = rr[i];
				ll[rr[i]] = ll[i];
			}
			else
			y[i] = 0;
		}
	}
}
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; ++ i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		lian(x, y);
		lian(y, x);
		if(x == 1)
		v.push_back(y);
		if(y == 1)
		v.push_back(x);
	}
	if(n - 1 - v.size() < k)
	{
		printf("impossible\n");
		return 0;
	}
	for (int i = 1; i <= n; ++ i)
	{
		ll[i] = i - 1;
		rr[i] = i + 1;
		col[i] = i;
	}
	vis[1] = 1;
	for (int i = 2; i <= n; ++ i)
	{
		if(vis[i] == 0)
		bfs(i);
	}
	for (int i = 2; i <= n; ++ i)
	{
		if(sf[col[i]] == 0)
		++ ans;
		++ sf[col[i]];
	}
	if(ans > k)
	{
		printf("impossible\n");
		return 0;
	}
	for (int i = 0; i < v.size(); ++ i)
	{
		int to = v[i];
		++ can[col[to]];
	}
	for (int i = 2; i <= n; ++ i)
	{
		if(can[i] == sf[i] && can[i] > 0)
		{
			printf("impossible\n");
			return 0;
		}
	}
	printf("possible\n");
}
```


---

## 作者：_fairytale_ (赞：0)

>如果只转身后退就能回到那个夏天
>
>把动作逐一背下就能复现当时画面
>
>无意伸手触碰到你指尖
>
>怔然着忘记语言
>
>于是扭头佯不悦 兀自品念

删边 bfs。

题目要求找到这个图的一棵生成树，满足点 $1$ 的度数为 $k$。分析一下性质：首先这个图要有生成树，也就是图要连通，其次点 $1$ 的度数要恰好为 $k$，那么有一个显然的必要条件是点 $1$ 的度数要 $\ge k$。

接下来，先从图中删掉点 $1$，找到图中的若干连通块，如果连通块数 $>k$，那么点 $1$ 的度数也会 $>k$，无解。如果连通块数 $\le k$，考虑从 $1$ 向这些连通块各连一条边，因为前面保证了 $1$ 的度数 $\ge k$，所以如果还有剩下的度数就可以随便连。如果形成环了就替换掉对应连通块的一条边。 

因此还要判掉 $1$ 与某个连通块没有边的情况。

关键来了：该怎么找到去掉 $1$ 号点之后的连通块数呢？我们这样做：每次找到一个还未被访问过的点，从它开始 bfs，但是这张图边数太多了，所以我们维护一个 `set` 存放还没有被访问过的点，每次只枚举 `set` 中的点，如果恰好没有边就跳过，否则标记为访问过并加入队列，从 `set` 中删除，同时用一个并查集维护连通块。

这样做的复杂度是多少呢？每次跳过当且仅当有一条被删过的边，因此每条边最多被它的两个端点各跳过一次。而如果没有跳过，连通块数会减少 $1$，因此总复杂度为 $\mathcal O(m\log n)$ 的。

```cpp
#include<bits/stdc++.h>
bool Mst;
#define rep(x,qwq,qaq) for(int (x)=(qwq);(x)<=(qaq);++(x))
#define per(x,qwq,qaq) for(int (x)=(qwq);(x)>=(qaq);--(x))
using namespace std;
#define inf 0x3f3f3f3f
#define maxn 301000
int n,m,k;
int a[maxn],b[maxn];
#ifndef int
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
#endif
gp_hash_table<int,int>mp[maxn];
set<int>s;
int bel[maxn];
bool can[maxn];
int fa[maxn];
int fd(int x) {
	return x==fa[x]?x:fa[x]=fd(fa[x]);
}
bool vis[maxn];
bool Med;
signed main() {
	cerr<<(&Mst-&Med)/1024.0/1024.0<<" MB\n";
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	int deg1=n-1;
	rep(i,1,m) {
		cin>>a[i]>>b[i];
		if(a[i]>b[i])swap(a[i],b[i]);
		mp[a[i]][b[i]]=mp[b[i]][a[i]]=1;
		if(a[i]==1)--deg1;
	}
	if(deg1<k)return cout<<"impossible",0;
	rep(i,2,n)s.insert(i);
	rep(i,1,n)fa[i]=i;
	queue<int>q;
	rep(i,2,n) {
		if(vis[i])continue;
		q.push(i),vis[i]=1;
		while(!q.empty()) {
			int i=q.front();
			q.pop();
			s.erase(i);
			for(auto it=s.begin(); it!=s.end();) {
				int v=*it;
				if(mp[i][v]) {
					++it;
					continue;
				}
				fa[fd(v)]=fd(i);
				if(!vis[v])q.push(v),vis[v]=1;
				it=s.erase(it);
			}
		}
	}
	int tot=0;
	rep(i,2,n)if(fd(i)==i)++tot;
	rep(i,2,n)bel[i]=fd(i);
	if(tot>k)return cout<<"impossible",0;
	rep(i,2,n) {
		if(mp[1][i])continue;
		can[bel[i]]=1;
	}
	rep(i,2,n)if(!can[bel[i]])return cout<<"impossible",0;
	cout<<"possible";
	return 0;
}
```

---

## 作者：__ycx2010__ (赞：0)

## solution

首先判断 $1$ 剩余的度数，若小于 $k$ 则直接输出 `impossible`，然后我们需要求出图中删去 $1$ 节点及其连边后的连通块个数。

我们用一个 `set` 维护出还没有去过的点，每一次访问到 $u$，只在 `set` 中找 $v$，由于只删去了 $m$ 条边，所以匹配失败次数至多为 $m$，最终复杂度 $O((n+m)\log n)$。

## code

注意要用 bfs，dfs 可能会栈溢出。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 300010;
int n, m, k;
unordered_map<int, int> g[N];
set<int> s;
bool flg;

void bfs(int u) {
	queue<int> q;
	vector<int> tmp;
	q.push(u);
	s.erase(u);
	while (q.size()) {
		int t = q.front();
		q.pop();
		for (int v : s) {
			if (!g[t].count(v)) {
				tmp.push_back(v);
				q.push(v);
			}
		}
		while (tmp.size()) s.erase(tmp.back()), tmp.pop_back();
		if (!g[t].count(1)) flg = false;
	}
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    int t = 0;
    for (int i = 1; i <= m; i ++ ) {
    	int u, v;
    	scanf("%d%d", &u, &v);
    	g[u][v] = 1;
    	g[v][u] = 1;
    	if (u == 1 || v == 1) t ++ ;
	}
	if (n - 1 - t < k) {
		puts("impossible");
		return 0;
	}
	for (int i = 2; i <= n; i ++ ) {
		s.insert(i);
	}
	int cnt = 0;
	for (int i = 2; i <= n; i ++ )
		if (s.count(i)) {
			s.erase(i);
			flg = true;
			bfs(i);
			cnt ++ ;
			if (flg) {
				puts("impossible");
				return 0;
			}
		}
	if (cnt > k) puts("impossible");
	else puts("possible");
    return 0;
}
```

---

## 作者：hyman00 (赞：0)

# CF653E 题解

这题评灰不太应该吧，难度肯定不到黑题，建议紫。

### 题意

给定一个图，求是否有一个它的**反图**的**生成树**满足节点 $1$ 的度数**恰好**是 $k$。

### 题解

分析下有解的条件。

首先，反图连通。

其次，反图里节点 $1$ 的度数至少是 $k$。

这两个条件显然是**必要**条件，那是否是充分的呢？

发现第一个条件限制了**有生成树**，第二个限制了节点 $1$ 的度数**至少**是 $k$，对比原题还缺节点 $1$ 的度数**不超过** $k$。

具体的，如果反图去掉节点 $1$，分成了**大于** $k$ 个连通块，也是无解的。

考虑如何判定，类似 CF920E 的方法，使用 bfs，把目前还没访问的节点村进一个 set 里。

bfs 到一个节点时，遍历所有 set 里的节点，如果没有边就从 set 里删去。

这样每操作一次，要么 set 大小减一，要么就对应一条原图的边，复杂度是对的。

先删去节点 $1$，对于所有邻居 bfs 一遍，如果除节点 $1$ 外的连通块大于 $k$ 或者反图不连通，就无解。 

---

