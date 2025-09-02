# Make It Connected

## 题目描述

You are given an undirected graph consisting of $ n $ vertices. A number is written on each vertex; the number on vertex $ i $ is $ a_i $ . Initially there are no edges in the graph.

You may add some edges to this graph, but you have to pay for them. The cost of adding an edge between vertices $ x $ and $ y $ is $ a_x + a_y $ coins. There are also $ m $ special offers, each of them is denoted by three numbers $ x $ , $ y $ and $ w $ , and means that you can add an edge connecting vertices $ x $ and $ y $ and pay $ w $ coins for it. You don't have to use special offers: if there is a pair of vertices $ x $ and $ y $ that has a special offer associated with it, you still may connect these two vertices paying $ a_x + a_y $ coins for it.

What is the minimum number of coins you have to spend to make the graph connected? Recall that a graph is connected if it's possible to get from any vertex to any other vertex using only the edges belonging to this graph.

## 说明/提示

In the first example it is possible to connect $ 1 $ to $ 2 $ using special offer $ 2 $ , and then $ 1 $ to $ 3 $ without using any offers.

In next two examples the optimal answer may be achieved without using special offers.

## 样例 #1

### 输入

```
3 2
1 3 3
2 3 5
2 1 1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
4 0
1 3 3 7
```

### 输出

```
16
```

## 样例 #3

### 输入

```
5 4
1 2 3 4 5
1 2 8
1 3 10
1 4 7
1 5 15
```

### 输出

```
18
```

# 题解

## 作者：一扶苏一 (赞：8)

## Description

给定 $n$ 个点，每个点有点权，连结两个点花费的代价为两点的点权和。另外有 $m$ 条特殊边，参数为 $x,y,z$。意为如果你选择这条边，就可以花费 $z$ 的代价将点 $x$ 和点 $y$ 连结起来，当然你也可以不选择这条边。求使整个图联通的最小代价

## Input

第一行是两个整数，分别是点数 $n$ 和特殊边的数量 $m$

下面一行 $n$ 个数，第 $i$ 个数代表点 $i$ 的点权

下面 $m$ 行，每行三个数 $x,y,z$，代表一条特殊边

## Output

输出一行一个整数，最小代价

## Hint

$1~\leq~n~\leq~2~\times~10^5~,0~\leq~m~\leq~2~\times~10^5$

设第 $i$ 个点的点权为 $a_i$，第 $j$ 条特殊边的边权为 $z_j$，保证

$1~\leq~a_i,z_j~\leq~10^{12}$

保证特殊边的参数 $x~\neq~y$

## Solution

显然这个题目是要求一个 MST (最小生成树)，但是 $O(n^2)$ 建图显然不可取。

我们考虑克鲁斯卡尔算法的本质：

有若干个联通块，每次寻找联通块间权值最小的边将之连结。

考虑对于本题来说，在不考虑特殊边的情况下，连结两个联通块，显然要分别选择两个联通块内点权最小的点连结。于是我们对每个集合维护点权最小的点，每次取出点权前两小的集合进行连边即可。维护点权前两小的集合显然可以用一个堆做。

考虑有特殊边怎么办：

我们把特殊边排序，每次比较当前的特殊边的权值小还是前两个联通块的点权小，选择更小的合并。

注意处理一下当前选出的两个点在一个集合中的情况。

因为一共要做 $O(n)$ 次，每次会有 $O(1)$ 次对堆的插入和删除操作，于是复杂度 $O(n \log n)$

## Code

```cpp
#include <cstdio>
#include <queue>
#include <algorithm>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 200010;
const int maxm = 400010;

struct Edge {
	int from, to;
	ll v;
	inline bool operator<(const Edge &_others) const {
		return this->v < _others.v;
	}
};
Edge edge[maxm];

int n, m;
int ufs[maxn], vec[maxn], rk[maxn];
ll ans;
ll MU[maxn];

struct Zay {
	int id;
	ll v;
	inline bool operator<(const Zay &_others) const {
		return this->v > _others.v;
	}
};
std::priority_queue<Zay>Q;

int find(ci x) {return ufs[x] == x ? x : ufs[x] = find(ufs[x]);}

int main() {
	freopen("1.in", "r", stdin);
	qr(n); qr(m);
	for (rg int i = 1; i <= n; ++i) qr(MU[i]);
	for (rg int i = 1; i <= m; ++i) {
		qr(edge[i].from); qr(edge[i].to); qr(edge[i].v);
	}
	std::sort(edge + 1, edge + 1 + m);
	edge[m + 1].v = 1ll << 62;
	for (rg int i = 1; i <= n; ++i) ufs[i] = i, vec[i] = i, rk[i] = 1, Q.push((Zay){i, MU[i]});
	for (rg int i = 1, cur = 1; i < n; ++i) {
		while ((cur <= m) && (find(edge[cur].from) == find(edge[cur].to))) ++cur;
		Zay t1 = Q.top(); Q.pop(); Zay t2 = Q.top(); Q.pop();
		while (find(t1.id) == find(t2.id)) {t2 = Q.top(); Q.pop();}
		if ((t1.v + t2.v) <= edge[cur].v) {
			int fa = find(t1.id), fb = find(t2.id);
			ans += t1.v + t2.v;
			if (rk[fa] < rk[fb]) ufs[fb] = fa;
			else if (rk[fa] > rk[fb]) ufs[fa] = fb;
			else ufs[fa] = fb, ++rk[fb];
			Q.push((Zay){find(fa), t1.v});
			vec[find(fa)] = vec[fa];
		} else {
			int fa = find(edge[cur].from), fb = find(edge[cur].to);
			ans += edge[cur].v;
			if (rk[fa] < rk[fb]) ufs[fb] = fa;
			else if (rk[fa] > rk[fb]) ufs[fa] = fb;
			else ufs[fa] = fb, ++rk[fb];
			Q.push((Zay){find(fa), MU[vec[fa]]});
			vec[find(fa)] = vec[fa];
			Q.push(t1); Q.push(t2);
		}
	}
	qw(ans, '\n', true);
	return 0;
}
```



---

## 作者：starseven (赞：6)

[我的博客中链接](https://www.cnblogs.com/starseven/p/13052401.html)

[题目链接](https://codeforces.com/problemset/problem/1095/F)

[luogu题目链接](https://www.luogu.com.cn/problem/CF1095F)

$因为自己想了很久都没有想出来，所以记录下来$

题目大意：

给你n个点,每个点有一个权值$a[i]$,已知连接两点的代价为$a[i]+a[j]$,现在还有其他的$m$种连接方法,连接$x,y$的代价为$w$,求出让这个图连通的最小代价.

我们看到了**求出让这个图连通的最小代价.**

那明显就是最小生成树了啊。

但是如果我们常规建边，那么需要$n\times(n-1)+m$的时间复杂度，而数据强度是：

$$ n <= 2\times10^5 $$

所以$n^2$的建边是要炸掉的。

所以我们需要思考一些可以帮助我们优化算法的性质。

1. 无用边

对于那个$n\times(n-1)$的边，我们很明显看得出来是完全图。

那么完全图的最小生成树是怎样的呢？

很显然是点值最小的点连接其他所有的点（~~俗称菊花图~~）


而其他边在增加了m条边后还有没有用？

假设有一条边$<x,y>$是有用的，那么其权值为$val[x]+val[y]$,而我们根据最小生成树的定义可以知道，在最小生成树里，这两个点要么都没有和最小点（我们将其设为minn）有边，要么只有一个点和minn有边（因为如果两个点都右边的话就形成图了）

（默认$val[x]<val[y]$）

当都没有连边时：

我们将$<x,y>$这条边删去，再将minn连向其中一个点，那么最小生成树中全职的变化是：

$$ -val[x]-val[y]+val[minn]+val[x/y] $$

我们可以轻松看出是负数，所以这才是真正的最小生成树。

当有连边时：

和上面一样。

所以我们可以知道剩下的边对于最终的最小生成树都没有贡献。所以我们只需要加入$n-1$个边，于是

$$ n\times(n-1)---->n-1$$

时间和空间复杂度大大降低，于是此题可做。

$$ Show\;my\;code\;!$$

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#define ri register int
#define Starseven main
#define ll long long
using namespace std;
const int N=2e5+20;
int n,m,fa[N];
ll ans;

struct node{
	ll val;
	int id;
}num[N];

bool cmp(const node &a,const node &b){
	return a.val<b.val;
}

struct nod{
	int from,to;
	ll cos;
}tr[N<<1];
int cnt;

bool cmd(const nod &a,const nod &b){
	return a.cos<b.cos;
}

void Add(int x,int y,ll va){
	tr[++cnt].from=x;tr[cnt].to=y;tr[cnt].cos=va;
	return ;
}

int Find(int x){
	if(fa[x]==x) return x;
	else return fa[x]=Find(fa[x]);
}

int Starseven(void){
	cin>>n>>m;
	for(ri i=1;i<=n;i++) num[i].id=fa[i]=i,cin>>num[i].val;
	sort(num+1,num+1+n,cmp);
	for(ri i=2;i<=n;i++) Add(num[1].id,num[i].id,num[1].val+num[i].val);
	for(ri i=1;i<=m;i++){
		int x,y;ll va;
		cin>>x>>y>>va;
		Add(x,y,va);
	}
	sort(tr+1,tr+1+cnt,cmd);
	int judge=0;
	for(ri i=1;i<=cnt;i++){
		int fx=Find(tr[i].from),fy=Find(tr[i].to);
		if(fx==fy) continue;
		fa[fx]=fy;
		ans+=tr[i].cos;
		judge++;
		if(judge==n-1) break;
	}
	cout<<ans<<endl;
	return 0;
}
```


后记：

我最开始的时候想到了要和最小点连边，但是我没有在最后想到最小生成树，而是想到了一个一个m的边加入，然后判断是否能够替换，现在想来我就是在没有Kus的基础上想最小生成树，看来我对于图论的知识点还不够熟悉，所以还要加强学习！





---

## 作者：ytm2004 (赞：3)

# 核心思想：一个完全图的最小生成树是权值最小的点与其它点连边构成的树
如何实现这一点：
```cpp
    minn = 1;
    for(ll i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
        if(a[minn] > a[i]) minn = i;//如果有更小的权值就更新
    }
    for(ll i = 1; i <= n; i++){
        if(minn == i) continue;//不能自己和自己连边
        //上面这句删了其实也行，因为并查集不会让一个点加入自己所在集合
        
        e[i].u = minn;
        e[i].v = i;
        e[i].w = a[i] + a[minn];
        //正常加边
    }
```
下面贴上我的高清~~无码~~的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 3;
const int maxm = 2e5 + 3;
struct edge{
    ll u, v, w;
}e[maxn << 1]; //这里要开大一点 因为后面还要加入n-1条边
ll f[maxn], n, m, a[maxn], minn;
bool vis[maxn];
ll findf(ll x){//查询父亲
    return x == f[x] ? x : f[x] = findf(f[x]);//路径压缩
}
ll merge(ll x, ll y){
    ll fx = findf(x), fy = findf(y);
    if(fx == fy) return 0; //如果已经在统一集合中就返回0
    else {
        f[fy] = fx;//合并
        return 1;//返回1
    }
}
bool cmp(const edge &x, const edge &y){
    return x.w < y.w;
}
int main(){
    scanf("%lld%lld", &n, &m);
    for(ll i = 1; i <= n; i++){
        f[i] = i;
    }
    minn = 1;
    for(ll i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
        if(a[minn] > a[i]) minn = i;
    }
    for(ll i = 1; i <= m; i++){
        scanf("%lld%lld%lld", &e[i].u, &e[i].v, &e[i].w);
    }
    
    for(ll i = 1; i <= n; i++){
        if(minn == i) continue;
        e[i + m].u = minn;
        e[i + m].v = i;
        e[i + m].w = a[i] + a[minn];
    }
    
    //Kruskal核心：
    sort(e + 1, e + m + n + 1, cmp);
    ll tot = 0, cnt = 0;
    for(ll i = 2; i <= m + n; i++){
        if(merge(e[i].u, e[i].v)){
            tot += e[i].w;
            cnt++;
            if(cnt == n) break;//一满足条件就退出循环
        }
    }
    printf("%lld\n", tot);
    return 0;
}
```

---

## 作者：寒冰大大 (赞：2)

首先我们能够发现这道题显然是和生成树有关，关键怎么建这个模？

首先我们考虑最普通的连接方法，发现首先每个点都要加进答案一次，还有$(n-1)$的点的$a$要被加进答案，我们就要最小化这个值，很容易想到我们的边全部由$a_{min}$所在的点连就有最小值，可以看做$a_{min}$的点向所有点连边

对于其他的连接方法，这东西也可以看做一条边，并且和要普通连接方法中的$a_{u}+a_{v}+2*a_{min}$
比较，对答案的其他部分没有影响，所以可以直接比较然后加进答案

换句话说我们在最小生成树生成的过程中要判断，实际我们不用判断，把这两条边都加进去就行了。

附上奇丑无比的代码
```cpp
#include<touwenjian.h>

#define int long long

using namespace std;

const int maxn=200100;

struct edge{
	int x,y,cost;
	bool operator <(const edge &ano)
	const {
		return cost<ano.cost;
	}
}e[maxn*2]; 

int n,m;
int mmn=0x3f3f3f3f3f3f3f3f,target,szp;
int f[maxn],a[maxn];

int getfather(int x)
{
	if(f[x]==x) return x;
	return f[x]=getfather(f[x]);
}

int kru()
{
	int i,j;
	int totans=0,tot=0;
	for(i=1;i<=szp&&tot<=n-1;i++)
	{
		int x,y;
		x=e[i].x;
		y=e[i].y;
		x=getfather(x);
		y=getfather(y);
		if(x==y) continue;
		f[x]=y;
		tot++;
		totans+=e[i].cost;
	}
	return totans;
}

signed main()
{
	ios::sync_with_stdio(false);
	register int i,j;
	cin>>n>>m;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
		f[i]=i;
		if(a[i]<mmn) mmn=a[i],target=i;
	}
	for(i=1;i<=n;i++)
	{
		if(i==target) continue;
		e[++szp].cost=a[i]+mmn;
		e[szp].x=target;
		e[szp].y=i;
	}
	int t1,t2,t3;
	for(i=1;i<=m;i++)
	{
		cin>>t1>>t2>>t3;	
		e[++szp].cost=t3;
		e[szp].x=t1;
		e[szp].y=t2;
	}
	sort(e+1,e+szp+1);
	cout<<kru()<<endl;
}

```


---

## 作者：cbdsopa (赞：1)

### 题意简述

$n$( $1≤n≤2×10^5$ )个点，每个点 $i$ 有一个点权 $a_i$ ( $1≤a_i≤2×10^{12}$ )，将两个点 $i$,$j$ 直接相连的花费是两个点的点权和 $a_i+a_j$，并且对于特别的$m$( $1≤m≤2×10^5$ )条边 $u_i$ , $v_i$ 可以通过花费 $w$ 点费用连接，求使得所有点互相连通的最小费用。

我们可以从数据范围看出需要注意的事项：

分析1.从$n$和$m$的范围可以看出我们最终的复杂度是带 ```log``` 的。

分析2.从$a_i$，很显然需要 ```long long```。

接下来就从分析1导入正题。

### Solution

看到关键词"连边","最小费用","边权"。

想到什么了？这不是我们可爱的最小生成树吗！

然后上来敲了一手 Kruskal[(不会最小生成树可以点这里)](https://oi-wiki.org/graph/mst/#kruskal)，然后越打越不对劲——是不是忘了点东西——还可以用 $a_i+a_j$ 直接连边。

好，于是就用 $O(n^2)$ 来加边....不对啊，这复杂度直接爆了。

真的 $n^2$ 条边都要用吗？似乎不是的。

对于一个图最少需要连 $n-1$ 条边来使图连通，**我们只需要以权值最小的点作为核心，他连出来的那一组边是最小的，且是能使图连通的，我们只需找到权值最小的点，把它与其他点相连的费用计算出来并进行 Kruskal。所以总共只需 $O(n+m)$ 加边即可**

之后用最小生成树算法就可以了，复杂度约为 $O((n+m)log(n+m))$。

### 代码

那么代码如下:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define file(a) freopen(#a".in","r",stdin),freopen(#a".out","w",stdout);
int n,m,fa[200010],cnt,deals[200010];
long long v[200010],ans,minn=1000000000010,mid;
struct edge
{
	int u,v;
	long long w;
}q[500010];//记得开到两倍n
bool cmp(edge a,edge b)
{
	return a.w<b.w;
}
int find(int x)
{
	return x==fa[x]?x:fa[x]=find(fa[x]); 
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		scanf("%lld",&v[i]);
		fa[i]=i;
		if(v[i]<minn)
		{
			minn=v[i];
			mid=i;
		}
	}
	for(int i=1;i<=n;++i)
	{
		if(i==mid) continue;
		q[i].u=mid;q[i].v=i;
		q[i].w=v[mid]+v[i];
	}
	for(int i=n+1;i<=n+m;++i)
	{
		scanf("%d%d%lld",&q[i].u,&q[i].v,&q[i].w);
	}
	sort(q+1,q+1+n+m,cmp);
	for(int i=1;i<=n+m;++i)
	{
		int x=find(q[i].u),y=find(q[i].v);
		if(x!=y)
		{
			fa[y]=x;
			ans+=q[i].w;
		}
	}
	printf("%lld",ans);
	return 0;
}

```


---

## 作者：Caicz (赞：1)

### [在博客食用效果更佳](https://www.luogu.com.cn/blog/224229/solution-cf1095f)
### [题目链接](https://www.luogu.com.cn/problem/CF1095F)

------------
这题首先看完题，第一个想法就是先将每个点之间连上边，然后和$m$条边一起跑最小生成树

但是，这个做法很明显是有问题的，不仅在时间上，空间上也承受不住

所以我们考虑优化 我们可以很容易观察到，因为是求一棵最小生成树，我们只需要n-1条边，那么我们就只需要对每一个节点$u$找与其相连的最短边。

发现什么了没有？
> 当选取的边为其余点与权值最小的点所连的边时，权值和最小

那么其余的边都是无用边，所以我们就可以先在读入时处理出权值最小的点的点号，然后其与其他点之间的连边时，即为所用边，再将这连接出来的边与$m$条特殊边加在一起跑一遍最小生成树，即可

>> **_Talk is cheap,show you the code_**

```cpp
#include<touwenjian.h>从MMM处偷来的万能头文件
#define ll long long
#define maxn 200005
using namespace std;
int n,m,cnt,fa[maxn];
struct node
{
	ll val;
	int num;
}a[maxn];
struct  eage
{
	int u,v;
	ll w;
}e[maxn];
ll ans;
bool cmp1(const node &a,const node &b){return a.val<b.val;}
bool cmp2(const eage &a,const eage &b){return a.w<b.w;}

ll read()
{
	ll num,sign=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')sign=-1;
	num=c-'0';
	while((c=getchar())>='0'&&c<='9')
		num=(num<<1)+(num<<3)+c-'0';
	return num*sign;
}

void addeage(int u ,int v,ll w)
{
	e[++cnt].u=u;
	e[cnt].v=v;
	e[cnt].w=w;
}

int find(int x)
{
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}

void kruskal()
{
	int k=0;
	for(register int i=1;i<=n;++i)fa[i]=i;
	for(register int i=1;i<=cnt;++i)
	{
		int x=find(e[i].u);
		int y=find(e[i].v);
		if(x!=y)
		{
			fa[x]=y;
			ans+=e[i].w;
			++k;
		}
		if(k==n-1)break;
	}
}

int main()
{
	n=read(),m=read();
	for(register int i=1;i<=n;++i)a[i].val=read(),a[i].num=i;
	sort(a+1,a+1+n,cmp1);
	for(register int i=2;i<=n;++i)addeage(a[1].num,a[i].num,a[1].val+a[i].val);
	for(register int u,v,i=1;i<=m;++i)
	{
		u=read(),v=read();
		addeage(u,v,read());
	}
	sort(e+1,e+n+m,cmp2);
	kruskal();
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：开始新的记忆 (赞：0)

题目大意：给你n个点，m条边，每个点i都有对应的值ai，告诉你每条边连接哪两个点及其权值，并且可以在i和j之间生成一条边，并且权值为ai+aj，求最小让图联通的边权之和。

主要考点就是最小生成树。

大致思路：不难想到，可以找出n个点中对应值最小的点，与其他所有点都做一条边，再和系统给出的边进行最小生成树的算法即可。可以保证必定可以建出一棵树（最不济就是将我们找出的对应值最小的点与其他一一连接）。时间复杂度大概为O(n)？（~~我也不确定~~）

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,fa[200010],cnt=0;
long long a[200010],mixn=1e18,x=0;
struct node{
	int fr,to;
	long long va;
} size[500010];

bool cmp(node xx,node yy)
{
	return xx.va<yy.va;
}

int find(int xx)
{
	if(fa[xx]!=xx)
		return fa[xx]=find(fa[xx]);
	return fa[xx]; 
}

long long kru()
{
	long long ans=0;
	for(int i=0;i<cnt;++i)
	{
		int xx=find(size[i].fr),yy=find(size[i].to);
		if(xx!=yy)
		{
			fa[xx]=yy;
			ans+=size[i].va;
		}
	}
	return ans;
}

int main()
{	cin>>n>>m;
	for(int i=1;i<=n;++i)
	{
		cin>>a[i];
		fa[i]=i;
		if(a[i]<mixn)
			mixn=a[i],x=i;
	}
	for(long long xx,yy,zz,i=1;i<=m;++i)
	{
		cin>>xx>>yy>>zz;
		zz=min(a[xx]+a[yy],zz);
		size[cnt].fr=xx;
		size[cnt].to=yy;
		size[cnt].va=zz;
		cnt++;
	}
	for(int i=1;i<=n;++i)
	{
		if(i==x)
			continue;
		size[cnt].fr=i;
		size[cnt].to=x;
		size[cnt].va=a[i]+a[x];
		cnt++;
	}
	sort(size,size+cnt,cmp);
	long long ans=kru();
	cout<<ans<<endl;
	return 0;	
} 
```


---

## 作者：Memory_of_winter (赞：0)

[我的博客](https://www.cnblogs.com/Memory-of-winter/p/10340017.html)

**题目大意：**给你$n(n\leqslant2\times10^5)$个点和$m(m\leqslant2\times10^5)$条边，第$i$个点点权为$a_i$。连接$u,v$两个点的代价为$a_u+a_v$或者一条连接$u,v$的边的边权。问连通的最小代价

**题解：**发现若不考虑特殊边，一定是点权最小的点连向其他点。于是建出由点权最小的点连向其他各点的边，边权为两点点权和。与特殊边一起跑最小生成树即可。



**C++ Code：**

```cpp
#include <algorithm>
#include <cstdio>
#define maxn 200010
int n, m;
int l[maxn << 1], r[maxn << 1], rnk[maxn << 1];
long long ans, a[maxn], w[maxn << 1];

int f[maxn];
int find(int x) { return x == f[x] ? x : (f[x] = find(f[x])); }

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", a + i);
		rnk[i] = f[i] = i;
	}
	std::sort(rnk + 1, rnk + n + 1, [] (int x, int y) { return a[x] < a[y]; });
	const long long base = a[rnk[1]];
	const int L = rnk[1];
	for (int i = 1; i < n; ++i) {
		w[i] = a[rnk[i + 1]] + base;
		l[i] = L, r[i] = rnk[i + 1];
		rnk[i] = i;
	}
	for (int i = n; i < n + m; ++i) {
		scanf("%d%d%lld", l + i, r + i, w + i);
		rnk[i] = i;
	}
	std::sort(rnk + 1, rnk + n + m, [] (int x, int y) { return w[x] < w[y]; });
	int num = n - 1;
	for (int i = 1, u, v; i < n + m && num; ++i) {
		u = find(l[rnk[i]]), v = find(r[rnk[i]]);
		if (u != v) {
			f[u] = v;
			ans += w[rnk[i]];
			--num;
		}
	}
	printf("%lld\n", ans);
	return 0;
}

```



---

## 作者：Zechariah (赞：0)

F比E好想系列  
由于任意点之间可以通过点权连边，我们贪心地想，两个点如果一定要通过点权连边，那么他们同时连到点权最小的点一定是最优的，因为如果我们直接连这两个点，那么组成的联通块还需要与点权最小的点相连  
如此一来问题就简单了，添加每个点到点权最小点的边，然后跑最小生成树
```cpp
#include <bits/stdc++.h>
#define rg register
#define inl inline
typedef long long ll;
const int N = 4e5 + 10, mod = 998244353, oo = 0x3F3F3F3F3F3F3Fll;
using namespace std;
namespace fast_IO {
    long long read()
    {
        rg long long num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) >= '0'&&ch <= '9')
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    int getnum(rg int num, ...)
    {
        va_list vl;
        va_start(vl, num);
        for (rg int i = 0; i != num; ++i)
            if (!~(*va_arg(vl, int*) = read()))return EOF;
        return num;
    }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
int fa[N];
ll a[N];
inl int findf(rg int x)
{
    if (fa[x] == x)return x;
    return fa[x] = findf(fa[x]);
}
struct Node {
    int x, y;
    ll c;
    Node() {}
    Node(ll c, int y, int x) :x(x), y(y), c(c) {}
    bool operator <(const rg Node &s)const { return c < s.c; }
}e[N];
inl bool cmp(rg int s, rg int t) { return a[s] < a[t]; }

int main()
{
    rg int n = fast_IO::read(), m = fast_IO::read();
    rg ll ans = 0;
    for (rg int i = 1; i <= n; ++i)a[fa[i] = i] = fast_IO::read();
    sort(fa + 1, fa + n + 1, cmp);
    for (rg int i = 1; i <= m; ++i)e[i] = Node(fast_IO::read(), fast_IO::read(), fast_IO::read());
    rg int tot = m;
    for (rg int i = 2; i <= n; ++i)e[++tot] = Node(a[fa[i]] + a[fa[1]], fa[1], fa[i]);
    for (rg int i = 1; i <= n; ++i)fa[i] = i;
    sort(e + 1, e + tot + 1);
    for (rg int i = 1; i <= tot; ++i)
    {
        rg int fx = findf(e[i].x), fy = findf(e[i].y);
        if (fx == fy)continue;
        ans += e[i].c;
        fa[fy] = fx;
    }
    fast_IO::write(ans);
    return 0;
}

```

---

