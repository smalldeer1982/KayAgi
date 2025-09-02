# [ARC069F] Flags

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc069/tasks/arc069_d

すぬけくんは旗が好きです。

すぬけくんは $ N $ 本の旗を一直線上に並べることにしました。

$ i $ 番目の旗は座標 $ x_i $ か座標 $ y_i $ のどちらかに設置することができます。

すぬけくんは、$ 2 $ つの旗同士の距離の最小値 $ d $ が大きいほど、旗の並びの見栄えが良いと考えています。$ d $ としてありうる値の最大値を求めなさい。

## 说明/提示

### 制約

- $ 2\ ≦\ N\ ≦\ 10^{4} $
- $ 1\ ≦\ x_i,\ y_i\ ≦\ 10^{9} $
- $ x_i,\ y_i $ は整数

### Sample Explanation 1

旗 $ 1 $ を座標 $ 1 $ に、旗 $ 2 $ を座標 $ 5 $ に、旗 $ 3 $ を座標 $ 9 $ に設置するのが最適であり、このとき旗同士の距離の最小値は $ 4 $ となります。

### Sample Explanation 2

旗の位置は重なることもあります。

## 样例 #1

### 输入

```
3
1 3
2 5
1 9```

### 输出

```
4```

## 样例 #2

### 输入

```
5
2 2
2 2
2 2
2 2
2 2```

### 输出

```
0```

## 样例 #3

### 输入

```
22
93 6440
78 6647
862 11
8306 9689
798 99
801 521
188 206
6079 971
4559 209
50 94
92 6270
5403 560
803 83
1855 99
42 504
75 484
629 11
92 122
3359 37
28 16
648 14
11 269```

### 输出

```
17```

# 题解

## 作者：w1049 (赞：16)

二分答案，并用2-sat判定。

大致思路：
1. 二分一个距离mid，作为最大距离。
2. 判断是否可以让每个旗子之间的距离都小于等于mid。如果可以，更新答案，尝试增大mid；如果不可以，缩小mid并重新判断。

本题最大范围如果$O(n^2)$建边是无法通过的，由于每次都是向左右一个区间内建边，所以用线段树辅助建图。

用$x_i$表示旗帜$i$的一个位置，对应的另一个位置为$x'_i$，那么我们需要建的边就是$x_i->\{x'_j||x_i-x_j|>mid\}$（此处的$x_j$可以是题中的$x$，也可以是题中的$y$）。

可以看出，从$x_i$到左右$mid$范围内需要建边。

因此，我们将题中$x$、$y$放在一起排序，并在此之上建立一颗线段树。

有几种不同的方式可以实现这一目的，我采用的是以下这种：

对于排序后的每个点建立一个“占位符”作为线段树的叶子，由占位符向对立的点离岸边；线段树中父亲向儿子连边。
这样，向一个范围内的对立点连边就转换成了线段树上的区间操作。

可以看图：

建出的线段树：
![1](https://cdn.luogu.com.cn/upload/image_hosting/vhfrsv7z.png)

由$x_2$向蓝色线标注区间内连边：

（红色为实际连边，粉色为达到的效果，即：使得$x_2$与区间内点都联通）
![2](https://cdn.luogu.com.cn/upload/image_hosting/wdocex65.png)

代码：
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

#define clear(x) memset(x, 0, sizeof(x))
#define op(x) ((x) <= n ? (x) + n : (x) - n)
// op可以求出一个点x的对立点
#define mid ((l + r) / 2)
#define ls now * 2
#define rs now * 2 + 1

const int N = 4e4 + 10, M = N * 20;

int hd[N * 5], nxt[M], t[M], ec;
void addEdge(int u, int v) {
    t[++ec] = v;
    nxt[ec] = hd[u];
    hd[u] = ec;
}
struct Flag {
    int pos, id;
    bool operator<(const Flag& f) const { return pos < f.pos; }
    Flag(int pos = 0): pos(pos) {}
} flgs[N * 2];

int n;
int cnt;
int id[N * 5];

void build(int now, int l, int r) {
    id[now] = ++cnt;
    if (l == r) {
        addEdge(id[now], op(flgs[l].id));
        // 由“占位符”向真实点的对立点连边
        return;
    }
    build(ls, l, mid);
    build(rs, mid + 1, r);
    addEdge(id[now], id[ls]);
    addEdge(id[now], id[rs]);
    // 由父亲向儿子连边
}

void link(int now, int l, int r, int x, int y, int point) {
    // 由point向区间[x,y]连边
    if (y < x) return;
    if (l == x && y == r) addEdge(point, id[now]);
    else if (y <= mid) link(ls, l, mid, x, y, point);
    else if(x > mid) link(rs, mid + 1, r, x, y, point);
    else link(ls, l, mid, x, mid, point), link(rs, mid + 1, r, mid + 1, y, point);
}

#undef mid

int dfn[N * 5], low[N * 5], tim;
int stk[N * 5], tp;
int scc[N * 5], sc;
bool in[N * 5];

void dfs(int u) { // Tarjan算法 强连通分量
    in[u] = 1;
    dfn[u] = low[u] = ++tim;
    stk[++tp] = u;
    int v;
    for (int i = hd[u]; i; i = nxt[i]) {
        if (!dfn[v = t[i]]) dfs(v), low[u] = min(low[u], low[v]);
        else if (in[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        ++sc;
        do {
            scc[v = stk[tp--]] = sc;
            in[v] = 0;
        } while (v != u);
    }
}

bool check(int v) {
    tp = tim = ec = 0;
    clear(hd), clear(dfn), clear(low);
    build(1, 1, cnt = 2 * n);
    int l, r;
    for (int i = 1; i <= 2 * n; i++) {
        l = upper_bound(flgs + 1, flgs + 1 + 2 * n, Flag(flgs[i].pos - v)) - flgs;
        r = upper_bound(flgs + 1, flgs + 1 + 2 * n, Flag(flgs[i].pos + v - 1)) - flgs - 1;
        link(1, 1, 2 * n, l, i - 1, flgs[i].id), link(1, 1, 2 * n, i + 1, r, flgs[i].id);
    }
    for (int i = 1; i <= 2 * n; i++) if (!dfn[i]) dfs(i);
    for (int i = 1; i <= n; i++) if(scc[i] == scc[i + n]) return 0;
    // 判断x与y是否在同一个强连通分量内
    return 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &flgs[i].pos, &flgs[i + n].pos);
        flgs[i].id = i, flgs[i + n].id = i + n;
    }

    sort(flgs + 1, flgs + n * 2 + 1);
    
    int l = 0, r = flgs[2 * n].pos - flgs[1].pos + 1, mid, ans;
    while (l <= r) { // 二分
        mid = (l + r) / 2;
        if (check(mid)) l = mid + 1, ans = mid;
        else r = mid - 1;
    }

    printf("%d", ans);
}
```

---

## 作者：Little09 (赞：10)

典中典题，但是别写线段树优化建图了，常数很大。

先二分答案，那么就变成了 2-SAT 问题，但是边数是 $O(n^2)$ 的。建边规则是每个点向一个区间内的点连边。

直接 kosaraju，只需要在原图和反图上实现 DFS 过程就行。暴力 DFS 复杂度还是不对，考虑怎么不访问到已经访问的点，用一个并查集维护每个点是否被访问，那么容易找到区间内第一个没被访问的点。

复杂度是 $O(n\log n\log v)$，其中 $\log n$ 是区间上并查集的复杂度，也可以加个启发式合并得到 $\alpha(n)$。这样常数很小，在 AT 上可以得到次优解，比线段树优化建图和分块优化建图高明多了。

---

## 作者：Ebola (赞：6)

# 【ARC069F】Flags  题解

首先我们二分答案

二分答案之后，就变成了经典的2-SAT问题。即：每个集合有两个元素，每个集合需要选出一个元素，并且满足一些条件形如“选了集合A的x就不能选集合B的x”，这样的条件可以转换为“选了集合A的x就必须选集合B的y”，然后集合A的x向集合B的y连边，跑一遍Tarjan缩点，如果某个集合的两个元素在同一个强连通分量中，说明无解

复杂度瓶颈在于建边，这个部分的复杂度是O(n²)

于是我们就有了线段树优化建边这个神奇的东西。具体地，先将所有点排序，线段树中的一个叶子结点[l,l]，存排序后第l个点在排序前的**反点的编号**（反点定义为集合中的另一个点）。然后线段树的一个非叶子结点作为图中的辅助节点，向两个子节点连边。此时我们向[l,r]连边，就相当于向排序后第l到第r的所有点的反点连边。容易发现，对于一个点u，他要连出的边在线段树上是连续的，于是就可以采用经典的区间询问方式去连边。

由于不能向自己的反点连边，连边要拆成两次，即[x-mid,x-1]、[x+1,x+mid]，其中x表示正在考虑的点，mid表示当前二分出来的答案。

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int N=40010;
struct Edge{int from,to,next;} e[N<<5];
int h[N<<2],sum=0;
int low[N<<2],pre[N<<2];
int scc[N<<2],dfn,cnt;
int a[2][N],n;
pii Hash[N<<1];
stack<int> stk;
int node[N<<4],tot;

void add_edge(int u,int v)
{
	if(u==v) return;
	e[++sum].to=v;
	e[sum].from=u;
	e[sum].next=h[u];
	h[u]=sum;
}

void Build(int o,int l,int r)
{
	if(l==r)
	{
		node[o]=Hash[l].second;
		return;
	}
	node[o]=++tot;
	int mid=(l+r)/2;
	Build(o<<1,l,mid);
	Build(o<<1|1,mid+1,r);
	add_edge(node[o],node[o<<1]);
	add_edge(node[o],node[o<<1|1]);
}

void link(int o,int l,int r,int nl,int nr,int u)
{
	if(nl>nr) return;
	if(l>=nl&&r<=nr)
	{
		add_edge(u,node[o]);
		return;
	}
	int mid=(l+r)/2;
	if(nl<=mid) link(o<<1,l,mid,nl,nr,u);
	if(nr>mid) link(o<<1|1,mid+1,r,nl,nr,u);
}

void Init()
{
	for(int i=1;i<=n;i++)
	{
		Hash[2*i-1].first=a[0][i];
		Hash[2*i-1].second=i+n;
		Hash[2*i].first=a[1][i];
		Hash[2*i].second=i;
	}
	sort(Hash+1,Hash+1+2*n);
}

void Tarjan(int u)
{
	stk.push(u);
	low[u]=pre[u]=++dfn;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
		if(!pre[e[tmp].to])
		{
			Tarjan(e[tmp].to);
			low[u]=min(low[u],low[e[tmp].to]);
		}
		else if(!scc[e[tmp].to]) low[u]=min(low[u],pre[e[tmp].to]);
	if(pre[u]==low[u])
	{
		int o;cnt++;
		do{
			o=stk.top();
			stk.pop();
			scc[o]=cnt;
		}while(o!=u);
	}
}

bool check(int x)
{
	sum=dfn=cnt=0;tot=2*n;
	memset(h,0,sizeof(h));
	Build(1,1,2*n);
	for(int i=1;i<=n;i++)
		for(int k=0;k<2;k++)
		{
			int l=lower_bound(Hash+1,Hash+1+2*n,pii(a[k][i]-x+1,0))-Hash;
			int r=upper_bound(Hash+1,Hash+1+2*n,pii(a[k][i]+x-1,2*n+1))-Hash-1;
			int m=lower_bound(Hash+1,Hash+1+2*n,pii(a[k][i],(k^1)*n+i))-Hash;
			link(1,1,2*n,l,m-1,k*n+i);
			link(1,1,2*n,m+1,r,k*n+i);
		}
	while(!stk.empty()) stk.pop();
	memset(pre,0,sizeof(pre));
	memset(low,0,sizeof(low));
	memset(scc,0,sizeof(scc));
	for(int i=1;i<=tot;i++)
		if(!pre[i]) Tarjan(i);
	for(int i=1;i<=n;i++)
		if(scc[i]==scc[i+n]) return 0;
	return 1;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[0][i],&a[1][i]);
	Init();
	int l=0,r=int(1e9),mid;
	while(l<r)
	{
		mid=(l+r)/2;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",check(l)?l:l-1);
	return 0;
}
```



---

## 作者：hater (赞：4)

蛮神仙的一道题 

思路 ： 

二分答案 两旗之间的最小距离 

转化为 2 — SAT 问题 用tarjan求解 

分块优化建边 

剖析一下思路 

每个旗子只有两种选择 

要么在 $x_{i}$ 要么在 $y_{i}$ 


考虑这种情况  

———————— @ —————— @ ———— 

                            ^ 
                          
（ @ 为插旗子的点 ， 假如我选了 ^ 指的旗子 ）  
 
当我们把 两旗之间的最小距离 二分出来时 

我可以判断出 前面那面旗子是否可选 

假如可选 就不管他 

假如不可选 那么前面那面旗子只能换个地方插了 

因为一面旗子只有两种选择 

我可以断定前面那面旗子插在哪里 

2 — SAT 模型到此应该非常显眼了 

但是建图有个问题 暴力是 n 方的 ~~暴力出奇迹~~ 

我们可以用个数据结构优化建边 这里是分块 

code : 

```cpp
#include <bits/stdc++.h> 
#define Rg register 
#define IL inline  
using namespace std ; 
const int N = 3e4 + 5 ;  
int n , tot , sum , col[N] , dfn[N] , low[N] , top , sta[N] , pos[N] , block ; 
vector <int> v[N] ; bool In[N] ; 
struct node { int whe , id ; } a[N] ; 
bool cmp ( node A , node B ) { return A.whe < B.whe ; } 
IL void add( Rg int x , Rg int y ) { v[x].push_back(y) ; } 
IL int op ( Rg int x ) { return x % 2 == 0 ? x-1 : x+1 ; }   
IL int Sch ( Rg int Val ) { 
    Rg int l = 1 , r = (n<<1) , mid , Ans = 0 ; 
    if( Val <= a[l].whe ) return l ;  
    if( Val >= a[r].whe ) return r ; 
    while( l <= r ) { 
    	mid = l+r >> 1 ; 
    	if( Val <= a[mid].whe ) Ans = mid , r = mid - 1 ; 
		  else l = mid+1 ;  
	} 
	return Ans ; 
} 
IL void tarjan( Rg int x ) { 
	In[x] = 1 ; dfn[x] = low[x] = ++ tot ; sta[++top] = x ;  
	for(Rg int i=0 ; i<v[x].size(); i++) { 
		int u = v[x][i] ; 
		if( !dfn[u] ) tarjan( u ) , low[x] = min( low[x] , low[u] ) ; 
		  else if( In[u] ) low[x] = min( low[x] , dfn[u] ) ;  
	} 
	if( dfn[x] == low[x] ) { 
	     sum ++ ; int per = sta[top] ;  
	     while( per != x ) 
	         col[per] = sum , In[per] = 0 , per = sta[--top] ; 
		 col[x] = sum , In[x] = 0 , top -- ;  
	} 
} 
void Build( int fro , int x , int y ) { 
    if( x > y ) return ; int l = pos[x] , r = pos[y] ; 
	if( l == r ) { for(Rg int i=x; i<=y; i++) add( fro , op(a[i].id) ) ; return ; } 
	for(Rg int i=x; i<=l*block; i++) add( fro , op(a[i].id) ) ; 
	for(Rg int i=l+1; i<r; i++) add( fro , i+(n<<1) ) ;  
	for(Rg int i=(r-1)*block+1 ; i<=y; i++) add( fro , op(a[i].id) )  ; 
} 
bool check( int H ) { 
    for(Rg int i=1; i<=(n<<1)+pos[n] ; i++) col[i] = dfn[i] = low[i] = 0 ; 
    for(Rg int i=1; i<=(n<<1)+pos[n] ; i++) v[i].clear( ) ; 
    for(Rg int i=1; i<=(n<<1) ; i++) v[(n<<1)+pos[i]].push_back(op(a[i].id)) ; 
    tot = sum = top = 0 ; int l , r ; 
    for(Rg int i=1; i<=(n<<1) ; i++) {  
        l = Sch( a[i].whe-H+1 ) ; r = Sch( a[i].whe+H ) ; 
        Build( a[i].id , l , i-1 ) ; Build( a[i].id , i+1 , r-1 ) ; 
	} 
	for(Rg int i=1; i<=(n<<1); i++) if( !dfn[i] ) tarjan(i) ; 
	for(Rg int i=1; i<=n; i++) if( col[a[i].id] == col[op(a[i].id)] ) return 0 ; 
	return 1 ; 
} 
signed main() { 
    ios::sync_with_stdio(false) ; 
    cin.tie(0) ; cout.tie(0) ; 
    cin >> n ; 
    for(Rg int i=1; i<=n; i++) 
      cin >> a[(i<<1)-1].whe >> a[i<<1].whe , 
       a[(i<<1)-1].id = (i<<1) - 1 , a[i<<1].id = ( i<<1 ) ; 
    sort( a+1 , a+(n<<1)+1 , cmp ) ; 
    block = sqrt( n << 1 ) ; 
    for(Rg int i=1; i<=(n<<1); i++) pos[i] = (i-1)/block+1 ; 
    Rg int l = 1 , r = a[n<<1].whe - a[1].whe , mid , Ans = 0  ;  
    while( l <= r ) { 
    	mid = l+r >> 1 ; 
    	if( check(mid) ) Ans = mid , l = mid+1 ; 
    	  else r = mid-1 ; 
	}  
	cout << Ans << '\n' ;
	return 0 ; 
} 
```
op 是相对应的那个点 

其他细节不懂欢迎来问

lower_bound 不会用手打二分 

闲话 ： 

其实题解我看不太懂 打出来没信心

但是打着打着就打完了 挑着挑着就AC了 

所以还是要自己摸索 题解只是一个思路的提示 

---

## 作者：happybob (赞：3)

考虑二分答案。

每个点要么选 $x$，要么选 $y$，这本质上是一个 2-SAT 模型。

直接建边的话，枚举 $i,j$，并且判断 $|x_i-x_j| < d$ 时，若 $i$ 取 $x$，那么 $j$ 取 $y$。其余的 $(x,y),(y,x),(y,y)$ 同理，复杂度 $O(n^2 \log V)$。

考虑优化，发现如果按 $x$ 排序，对于一个 $i$，连到的 $j$ 是一个区间的，可以直接用线段树或分块优化建图。

由于数据范围很小，$n \leq 10^4$，所以我选择写了好写的分块优化建图，大概是对于每一块建一个虚点向块内所有点连边。$u$ 向 $[l,r]$ 连边时整块直接连向虚点，散块暴力。结合二分，总复杂度 $O(n \sqrt{n} \log V)$。

启示：直接连边很慢时，考虑一些性质，例如连的是一段区间或前后缀时，可以优化建图。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

vector<int> G[N];
int dfn[N], low[N], idx, cnt, id[N];
bool in_stk[N];
int stk[N], top;
int n, m;
int len;
int cc;

struct Node
{
	int a, b, id;
	Node(int _a, int _b, int _i): a(_a), b(_b), id(_i){}
	Node() = default;
}p[N];

inline int get(int x)
{
	return x / len;
}

inline int L(int x)
{
	return max(1, x * len);
}

int idp[N];

void add(int u, int l, int r)
{
	if (l > r) return;
	if (r - l <= len + 5)
	{
		for (int i = l; i <= r; i++)
		{
			G[u].emplace_back(p[i].id + n);
		}
		return;
	}
	int L = get(l) + 1, R = get(r) - 1;
	for (int i = L; i <= R; i++)
	{
		G[u].emplace_back(idp[i]);
	}
	for (; get(l) != L; l++) G[u].emplace_back(p[l].id + n);
	for (; get(r) != R; r--) G[u].emplace_back(p[r].id + n);
}

void add2(int u, int l, int r)
{
	if (l > r) return;
	if (r - l <= len + 5)
	{
		for (int i = l; i <= r; i++)
		{
			//cout << "Edge: ";
			G[u].emplace_back(p[i].id);
		}
		return;
	}
	int L = get(l) + 1, R = get(r) - 1;
	for (int i = L; i <= R; i++)
	{
		G[u].emplace_back(idp[i]);
	}
	for (; get(l) != L; l++) G[u].emplace_back(p[l].id);
	for (; get(r) != R; r--) G[u].emplace_back(p[r].id);
}

void tarjan(int u)
{
	dfn[u] = low[u] = ++idx;
	stk[++top] = u;
	in_stk[u] = 1;
	for (auto &j : G[u])
	{
		if (!dfn[j])
		{
			tarjan(j);
			low[u] = min(low[u], low[j]);
		}
		else if (in_stk[j]) low[u] = min(low[u], dfn[j]);
	}
	if (dfn[u] == low[u])
	{
		cnt++;
		int y = 0;
		do
		{
			y = stk[top--];
			in_stk[y] = 0;
			id[y] = cnt;
		} while (y != u);
	}
}

inline bool check(int x)
{
	sort(p + 1, p + n + 1, [&](const Node& x, const Node& y){return x.a < y.a;});
	sort(p + n + 1, p + n + n + 1, [&](const Node& x, const Node& y){return x.b < y.b;});
	for (int i = 1; i <= cc; i++)
	{
		G[i].clear(), dfn[i] = low[i] = id[i] = in_stk[i] = 0;
	}
	cc = 2 * n;
	top = 0;
	for (int i = get(1); i <= get(n); i++)
	{
		idp[i] = ++cc;
		int l = L(i), r = min(n, L(i + 1) - 1);
		for (int j = l; j <= r; j++) 
		{
			G[cc].emplace_back(p[j].id + n);
			//cout << "Edge: " << cc << " " << p[j].id + n << "\n"; 
		}
	}
	for (int i = 1; i <= n; i++)
	{
		int l = p[i].a - x + 1, r = p[i].a + x - 1;
		int ll = lower_bound(p + 1, p + n + 1, Node(l, 0, 0), [&](const Node& x, const Node& y){return x.a < y.a;}) - p; 
		int rr = upper_bound(p + 1, p + n + 1, Node(r, 0, 0), [&](const Node& x, const Node& y){return x.a < y.a;}) - p - 1;
		if (ll >= 1 && ll <= n && rr >= 1 && rr <= n && rr >= ll)
		{
			add(p[i].id, ll, i - 1);
			add(p[i].id, i + 1, rr);
		} 
	}
	for (int i = 1; i <= n; i++)
	{
		int l = p[i].b - x + 1, r = p[i].b + x - 1;
		int ll = lower_bound(p + 1, p + n + 1, Node(l, 0, 0), [&](const Node& x, const Node& y){return x.a < y.a;}) - p; 
		int rr = upper_bound(p + 1, p + n + 1, Node(r, 0, 0), [&](const Node& x, const Node& y){return x.a < y.a;}) - p - 1;
		if (ll >= 1 && ll <= n && rr >= 1 && rr <= n && rr >= ll)
		{//cout << "djb: " << i << " " << ll << " " << rr << "\n";
			if (i >= ll && i <= rr)
			{
				add(p[i].id + n, ll, i - 1);
				add(p[i].id + n, i + 1, rr);
			}
			else add(p[i].id + n, ll, rr);
		} 
	}
	//
	for (int i = get(0); i <= get(2 * n); i++)
	{
		idp[i] = ++cc;
		int l = L(i), r = min(2 * n, L(i + 1) - 1);
		for (int j = l; j <= r; j++) 
		{
			//cout << "Edge: " << cc << " " << p[j].id << "\n"; 
			G[cc].emplace_back(p[j].id);	
		}
	}
	for (int i = n + 1; i <= 2 * n; i++)
	{
		int l = p[i].a - x + 1, r = p[i].a + x - 1;
		int ll = lower_bound(p + n + 1, p + 2 * n + 1, Node(0, l, 0), [&](const Node& x, const Node& y){return x.b < y.b;}) - p; 
		int rr = upper_bound(p + n + 1, p + 2 * n + 1, Node(0, r, 0), [&](const Node& x, const Node& y){return x.b < y.b;}) - p - 1;
		if (ll >= n && ll <= 2 * n && rr >= n && rr <= 2 * n && rr >= ll)
		{
			if (i >= ll && i <= rr)
			{
				add2(p[i].id, ll, i - 1);
				add2(p[i].id, i + 1, rr);
			}
			else add2(p[i].id, ll, rr);
		} 
	}
	for (int i = n + 1; i <= 2 * n; i++)
	{
		int l = p[i].b - x + 1, r = p[i].b + x - 1;
		int ll = lower_bound(p + n + 1, p + 2 * n + 1, Node(0, l, 0), [&](const Node& x, const Node& y){return x.b < y.b;}) - p; 
		int rr = upper_bound(p + n + 1, p + 2 * n + 1, Node(0, r, 0), [&](const Node& x, const Node& y){return x.b < y.b;}) - p - 1;
		if (ll >= n && ll <= 2 * n && rr >= n && rr <= 2 * n && rr >= ll)
		{
			add2(p[i].id + n, ll, i - 1);
			add2(p[i].id + n, i + 1, rr);
		} 
	}
	for (int i = 1; i <= cc; i++) if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; i++) 
	{
		if (id[i] == id[i + n]) return 0;
	}
	return 1;
} 

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	len = sqrt(n);
	for (int i = 1; i <= n; i++) 
	{
		cin >> p[i].a >> p[i].b, p[i].id = i;
	}
	for (int i = 1; i <= n; i++) p[i + n] = p[i];
	int l = 0, r = (int)1e9, ans = 0;
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (check(mid)) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	cout << ans << "\n";
	return 0;
}
```


---

## 作者：cosf (赞：2)

## [ARC069F](https://atcoder.jp/contests/arc069/tasks/arc069_d) [Flags](https://www.luogu.com.cn/problem/AT_arc069_d)

Atcoder 上题号错了……

怎么成 D 题了……

做完这道题后，可以做 [这道题](https://www.luogu.com.cn/problem/UVA1146)，领取一下双倍经验。

大体复制自 [我的另一篇博客](https://www.luogu.com.cn/blog/cosf/A71-uva1146)。

## 思路

### 二分

可以发现，直接求答案非常难。于是我们可以想到用二分答案的方法。

我们二分一个答案，看看能否满足要求即可。

### 2-Sat

我们令（新的）$x_i$ 表示旗子 $i$ 可以放在哪里。这里不分它是题目中的 $x_i$ 还是 $y_i$。我们只需要令 $\bar{x}_i$ 表示 $i$ 的另一个位置即可。

那么，当我们钦定了 $mid$ 作为答案时，显然对于所有 $|x_i - x_j| \lt mid$ 的 $i, j$，都是两者只能取其一的。这就是典型的 2-Sat 模型。我们可以连两条边 $<x_i, \bar{x}_j>, <x_j, \bar{x}_i>$。相当于 $x_i$ 递推至 $\bar{x}_j$，以及 $x_j$ 递推至 $\bar{x}_i$。如果发现有 $x_i$ 与 $\bar{x}_i$ 互相递推，那么显然就矛盾了。

具体怎么做，就是一个 2-Sat 板子，用强连通分量算法。

到此，这单次 $O(n^2\log t)$ 的复杂度**还不能**能通过本题，还需要进一步优化。

### 线段树优化建边

我们能发现，对于一个 $x_i$，我们要将所有 $|x_i - x_j| < mid$ 的 $j$，将 $x_i$ 连一条边到 $\bar{x}_j$。可以发现，满足这个条件的 $x_j$ 一定是一个区间内的。想到区间，我们就可以用线段树。

具体来说，我们可以建立一系列**虚点** $x'_i$，而与之对应的 $x_i$ 则是**实点**。则对于每一个 $x_i$，它要连接到的 $\bar{x}_j$ 所对应的 $\bar{x}'_j$ 的位置一定是属于一个区间的。

注意，$x_i$ 与 $\bar{x}'_i$ 在位置上是相同的。但是，它们的本质是不同的。也就是说，连接到 $\bar{x}'_i$ 并不意味着连接到 $x_i$。

怎么建边？我们可以先将所有虚点连向与之对应的实点。然后给虚点建一棵线段树。线段树除了叶子结点的其他点都给自己两个子节点连边。这样，例如你想连边到 $i \in [1, 3]$ 的每一个 $\bar{x}'_i$，你只需要连接到代表区间 $[1, 2]$ 和 $[3, 3]$ 的线段树点即可。其他的边在建树的时候已经连好了。

最终，边数优化到了 $O(n\log n)$ 级别的。单次测试复杂度 $O(n\log n\log t)$。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;

#define MAXN 20005

#define rev(x) (x > n ? x - n : x + n) // 它的对应点，也就是 \bar{x}

using ll = long long;
using pli = pair<ll, int>;

int n;

pli val[MAXN];

namespace SCC // 强连通分量
{
    vector<int> e[MAXN << 2];
    int dfn[MAXN << 2], low[MAXN << 2];
    int idx;

    stack<int> stk;
    bool ins[MAXN << 2];

    int scc[MAXN << 2];
    int cnt;

    void tarjan(int p)
    {
        dfn[p] = low[p] = ++idx;
        stk.push(p);
        ins[p] = true;
        for (int u : e[p])
        {
            if (!dfn[u])
            {
                tarjan(u);
                low[p] = min(low[p], low[u]);
            }
            else if (ins[u])
            {
                low[p] = min(low[p], dfn[u]);
            }
        }
        if (low[p] == dfn[p])
        {
            cnt++;
            while (stk.top() != p)
            {
                int t = stk.top();
                scc[t] = cnt;
                ins[t] = false;
                stk.pop();
            }
            scc[p] = cnt;
            ins[p] = false;
            stk.pop();
        }
    }
};

namespace SGT
{
    struct Tree
    {
        int l, r;
        int v;
    } t[MAXN << 2];
    int idx;
    void build(int p, int l, int r)
    {
        t[p] = {l, r, ++idx};
        if (l == r)
        {
            SCC::e[idx].push_back(rev(val[l].second)); // 虚向实连边
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        SCC::e[t[p].v].push_back(t[p << 1].v);
        SCC::e[t[p].v].push_back(t[p << 1 | 1].v);
    }
    void update(int p, int l, int r, int f)
    {
        if (l > r)
        {
            return;
        }
        if (l <= t[p].l && t[p].r <= r)
        {
            SCC::e[f].push_back(t[p].v);
            return;
        }
        int mid = (t[p].l + t[p].r) >> 1;
        if (mid >= l)
        {
            update(p << 1, l, r, f);
        }
        if (mid < r)
        {
            update(p << 1 | 1, l, r, f);
        }
    }
};

bool check(ll mid)
{
    SGT::idx = 2 * n;
    SCC::idx = 0;
    for (int i = 1; i <= n * 8; i++)
    {
        SCC::e[i].clear();
    }
    while (SCC::stk.size())
    {
        SCC::stk.pop();
    }
    memset(SCC::ins, 0, sizeof(SCC::ins));
    memset(SCC::dfn, 0, sizeof(SCC::dfn));
    memset(SCC::low, 0, sizeof(SCC::low));
    memset(SCC::scc, 0, sizeof(SCC::scc));
    SGT::build(1, 1, 2 * n);
    for (int i = 1; i <= 2 * n; i++)
    {
        int l = upper_bound(val + 1, val + 2 * n + 1, pli{val[i].first - mid, 0x3ffff3ff}) - val; // 注意不要写错
        int r = lower_bound(val + 1, val + 2 * n + 1, pli{val[i].first + mid, -1}) - val - 1;
        SGT::update(1, l, i - 1, val[i].second);
        SGT::update(1, i + 1, r, val[i].second);
    }
    for (int i = 1; i <= 2 * n; i++)
    {
        if (!SCC::dfn[i])
        {
            SCC::tarjan(i);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (SCC::scc[i] == SCC::scc[i + n])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> val[i].first >> val[i + n].first;
        val[i].second = i;
        val[i + n].second = i + n;
    }
    sort(val + 1, val + 2 * n + 1);
    ll l = 0, r = val[2 * n].first - val[1].first + 1;
    while (l < r - 1)
    {
        ll mid = (l + r) >> 1;
        bool res = check(mid);
        if (res)
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }
    cout << l << endl;
    return 0;
}

```


---

## 作者：ezoixx174 (赞：2)

链接：[AT2336 Flags](https://www.luogu.org/problemnew/show/AT2336)
（题意不解释了）

#### 解法：2-sat + tarjan-scc + 线段树/分块####

（话说2-sat这东西我读成二坐，zh大佬每次都要纠正我233333）

使用2-sat建模，将每个点$i$拆为$i$与$i'$，题目转化为选点问题。一条边$(u,v)$表示若选择了$u$，则$v$必须被选择。这东西有啥用呢？由于输入的每对数要么必须选$x$，要么必须选$y$，也就是说若我们能用2-sat推出“选$u$必须选$u'$”那么问题解决。

考虑如何连边。首先二分答案，设答案为$m$，那么我们用线段树优化连边（或使用分块优化连边），将所有读入的值排序，对于一个点$u$，在排序的值中二分查找区间$[l,r]$，让$[l,r]$上的每个数与$u$的相对差均小于$m$，然后由于二分出的答案为$m$，所以若$[l,r]$区间上的选了，则$u$不能选，从而$u'$必须选，于是将$[l,r]$区间上的每个点向$u'$连边。

判断时，先求出所有强连通分量，若某个点$u$与$u'$处于同一强连通分量内，那么即是说：若$u$选了，则$u'$必须选，与题设矛盾，验证返回伪。

时间复杂度：线段树连边$O(N\log^2N)$，分块连边$O(N\sqrt{N}\log N)$，均可过。

#### 代码（只有线段树版本的，我太懒了QAQ）#### 
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<stack>
#include<algorithm>

using namespace std;

struct data{
	int x,i;
	data():x(0),i(0){}
	data(int y,int j):x(y),i(j){}
	friend bool operator<(const data &dt1,const data &dt2){return dt1.x<dt2.x;}
};

stack<int> s;
int n,x[80001],idx,tot,id[80001],low[80001],dfn[80001],scc,cid[80001];
vector<data> vec;
vector<int> point[80001];

void build(int o,int l,int r){
	id[o]=++tot;
	if(o>1)point[id[o>>1]].push_back(tot);
	if(l==r){int v=vec[l-1].i;point[id[o]].push_back(v<=n?v+n:v-n);return;}
	int m=l+r>>1;
	build(o<<1,l,m),build(o<<1|1,m+1,r);
}

void update(int o,int l,int r,int a,int b,int x){
	if(a>b)return;
	if(l==a&&r==b){point[x].push_back(id[o]);return;}
	int m=l+r>>1;
	if(m>=b)update(o<<1,l,m,a,b,x);else if(m<a)update(o<<1|1,m+1,r,a,b,x);else update(o<<1,l,m,a,m,x),update(o<<1|1,m+1,r,m+1,b,x);
}

pair<int,int> get(int i,int m){
	pair<int,int> res;int l=1,r=i,mid;
	while(l<=r)if(vec[i-1].x-vec[(mid=l+r>>1)-1].x>=m)l=mid+1;else r=mid-1;
	res.first=r+1,l=i,r=n<<1;
	while(l<=r)if(vec[(mid=l+r>>1)-1].x-vec[i-1].x<m)l=mid+1;else r=mid-1;
	res.second=l-1;
	return res;
}

void dfs(int u){
	low[u]=dfn[u]=++idx;s.push(u);
	for(int v:point[u])if(!dfn[v]){dfs(v);low[u]=min(low[u],low[v]);}else if(dfn[v]>0)low[u]=min(low[u],dfn[v]);
	if(low[u]==dfn[u]){int x;++scc;while(x!=u)x=s.top(),s.pop(),dfn[x]=-dfn[x],cid[x]=scc;}
}

bool check(int m){
	memset(low,scc=idx=0,sizeof(low)),memset(dfn,0,sizeof(dfn));for(int i=1;i<=80000;++i)point[i].clear();
	build(1,1,tot=n<<1);
	for(int i=1;i<=n<<1;++i){int r=vec[i-1].i;pair<int,int> pr=get(i,m);update(1,1,n<<1,pr.first,i-1,r),update(1,1,n<<1,i+1,pr.second,r);}
	for(int i=1;i<=n<<1;++i)if(!dfn[i])dfs(i);
	for(int i=1;i<=n;++i)if(cid[i]==cid[i+n])return false;
	return true;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d%d",x+i,x+n+i),vec.push_back(data(x[i],i)),vec.push_back(data(x[i+n],i+n));
	sort(vec.begin(),vec.end());
	int l=0,r=1000000000,m;while(l<=r)if(check(m=l+r>>1))l=m+1;else r=m-1;
	printf("%d",l-1);
}
```

---

## 作者：灼眼的夏娜 (赞：2)

蒟蒻的又一篇题解

我的一到考试题，当时一眼就看出来是个数据结构，但死活不会做，听到正解是

## 外面二分，里面用线段树套$2-SAT$，再跑个$tarjan$求强联通分量$check$一遍

。。。。。。

这TMD是什么玩意，于是我就去学了学$2-SAT$，简单来说，就是有两排点，它们两两互相限制，假如第一列点，选了A就不能选B那就向B的第二个点连边，B同理，假如选了B就必须选A那就如第三列那样

![](https://cdn.luogu.com.cn/upload/image_hosting/sfs1q0qz.png)

建议先去看看$2-SAT$的模板，我可能讲不清。。。（~~因为太弱啦~~）题

号[P4782](https://www.luogu.org/problem/P4782)对于这道题，显然答案

可以二分出来，如果有不满足条件的A,B(即A,B的差值大于二分的$x$)，我

们从A向B连边，表示选了A就不能选B，然后跑$tarjan$，求出强联通分量，

假如有同一列的两个A,B在同一个强联通分量，那么其含义就为既不能选A，

又不能选B，这就是不合法的情况，说明当前二分的值太小，不能满足所有

的限制，需要更大的答案，反正则需要更小的答案。

那线段树是干啥的呢？如果你是暴力建图的话，时间复杂度是

$O(n^{2})$的，对于此题显然不行，所以线段树使用来优化建图的，具体操作如下：

$1.$将每个点的权值与编号打包到一个结构体里，第一排的编号为$1->n$，
第二

排的编号为$n+1->2n$，把它们按照编号从小到大排序

$2.$二分出一个答案，在$check$函数中，首先用线段树优化建图，建图时，对于每

一个点，找到一个$l,r$，满足$v_i-v_r<x$，$v_l-v_i<x$，再在$r-i$与$i-l$这

两段区间内寻找不合法的点，由这些点向$l,r,i$连边，表示他们互相限制

$3.$用$tarjan$求出联通分量，如果有同一列两个点在同一个强联通分量中，返回

$false$否则为$true$

算法讲述完毕，接下来是代码

## code
```cpp
//变量名与数组名为个人习惯与偏好
//请先从主函数看起
#include <stack>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define inf 1e9+7
#define LL (k << 1)
#define RR (k << 1 | 1)

using namespace std;
const int N = 200005;
const int P = N + (N << 2);
const int M = N + P + N * 20;
int n, pos[N];
int scc[P], dfn[P], low[P];
struct saber {
	int nxt, to;
}rin[M];
int head[P], cnt, tot, Index, violet;
stack<int> s;
struct SIN {
	int v, p;
	bool operator < (const SIN &o) const {
		return v < o.v;
	}
}shana[N];//shana数组用来存储点的信息
bool vis[P];

inline void add(int from, int to) {
	rin[++cnt].to = to;
	rin[cnt].nxt = head[from];
	head[from] = cnt;
}

void tarjan(int x) {//普通的tarjan求强联通分量
	dfn[x] = low[x] = ++ Index;
	s.push(x), vis[x] = true;
	for(int i = head[x]; i ;i = rin[i].nxt) {
		int vc = rin[i].to;
		if(!dfn[vc]) {
			tarjan(vc);
			low[x] = min(low[x], low[vc]);
		}
		else if(vis[vc]) low[x] = min(low[x], dfn[vc]);
	}
	if(dfn[x] == low[x]) {
		++ tot; int k = 0;
		do {
			k = s.top();
			s.pop();
			scc[k] = tot;
			vis[k] = false;
		}while(k != x);
	}
}

void build(int k, int l, int r) {
	if(l == r) {
    	//violet为点的总个数，她等于n<<1
        //p<=n说明是第一排点，否则是第二排点，由叶子节点连边
		add(k + violet, 
			shana[l].p <= n ? shana[l].p + n : shana[l].p - n);
		return;
	}
	int mid = (l + r) >> 1;
	build(LL, l, mid), build(RR, mid + 1, r);
    //相当于pushup
	add(k + violet, LL + violet);
	add(k + violet, RR + violet);
}

void insert(int k, int l, int r, int x, int y, int v) {
	if(l >= x && r <= y) {
    	//在线段树的区间上由v点向k+violet连边
		add(v, k + violet);
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) insert(LL, l, mid, x, y, v);
	if(y > mid) insert(RR, mid + 1, r, x, y, v);
}

inline bool check(int x) {
	//核心部分
	cnt = Index = tot = 0;
	while(!s.empty()) s.pop();
	memset(head, 0, sizeof(head));
	memset(dfn, 0, sizeof(dfn));
	build(1, 1, violet);
	int l = 1, r = 1;
	for(int i = 1;i <= violet;++ i) {
		int op, p = shana[i].p;
        //op点为中间点
		if(p <= n) op = pos[p + n];
		else op = pos[p - n];
        //找到合法的区间，在该区间内寻找不合法的点
		while(r <= i && shana[r].v + x < shana[i].v) r ++;
        //现在有r不符合要求
		if(r < i  && r >= 1 && shana[r].v + x > shana[i].v) {
			if(r <= op && op < i) {//op到i或r点不合法，连边
				if(r < op) insert(1, 1, violet, r, op - 1, shana[i].p);
				if(op < i - 1) insert(1, 1, violet, op + 1, i - 1, shana[i].p);
			}//否则直接由r向i连边
			else insert(1, 1, violet, r, i - 1, shana[i].p);
		}//l同理
		while(l <= violet && shana[l].v - x < shana[i].v) l ++;
		l --;
		if(l <= violet && l > i && shana[l].v - x < shana[i].v) {
			if(i + 1 <= op && op <= l) {
				if(i + 1 < op) insert(1, 1, violet, i + 1, op - 1, shana[i].p);
				if(op < l) insert(1, 1, violet, op + 1, l, shana[i].p);
			}
			else insert(1, 1, violet, i + 1, l, shana[i].p);
		}
	}
    //求完强联通分量，i和i+n是同一列的点，在同一个环里则不合法
	for(int i = 1;i <= violet;++ i) 
		if(!dfn[i]) tarjan(i);
	for(int i = 1;i <= n;++ i)
		if(scc[i] == scc[i + n])
			return 0;
	return 1;
}

int main() {
	// freopen("disaster.in", "r", stdin);
	// freopen("disaster.out", "w", stdout);
	scanf("%d", &n);
	int ans, maxn = -1e9, minn = 1e9;
	for(int i = 1, u, v;i <= n;++ i) {
		scanf("%d%d", &u, &v);
		minn = min(minn, min(u, v));
		maxn = max(maxn, max(u, v));
		shana[++violet] = (SIN) {u, i};
		shana[++violet] = (SIN) {v, i + n};
	}
    //特判，如果最大值减去最小值比n还小，直接输出0
	if(maxn - minn + 1 < n) { printf("0\n"); return 0; }
	sort(shana + 1, shana + violet + 1);
	for(int i = 1;i <= violet;++ i) pos[shana[i].p] = i;
	int l = 0, r = maxn;
	while(l < r) {
		int mid = (l + r) >> 1;
		if(check(mid)) ans = mid, l = mid + 1;
		else r = mid;
	}
	printf("%d\n", ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
```


---

## 作者：Pwtking (赞：1)

主要讲解线段树优化建图。



------------


正常建图的话复杂度是平方级的，加上二分答案的复杂度直接炸。

观察到我们建图时每一个位置连边的其他位置都是一个区间，所以我们考虑线段树优化建图。核心思想是：像线段树一样的构型的连边以减少连边数量。

首先先将每个位置点排序。

方法是，构造线段树时，将每一个父亲向自己的每个儿子连边直到 $l=r$ 时，此时将叶子向自己的相对位置（如 $x_1$ 与 $y_1$ 相对）连一个边。

接下来你只需要把当前需要连边的节点与自己需要连向的范围在线段树上进行连边即可。


------------


```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 0x7fffffff
const ll maxn=3e5+10;
ll low[maxn],dfn[maxn],vis[maxn];
ll tot,cnt,color[maxn],n;
pair<ll,ll> node[maxn];
stack<ll> q;
vector<ll> G[maxn];
struct tree{ll l,r,id;}t[maxn];
inline void solve(ll u) {
	q.pop();
	vis[u]=0;color[u]=tot;
}
inline void tarjan(ll u) {
	dfn[u]=low[u]=vis[u]=++cnt;
	q.push(u);
	for (ll i=0;i<G[u].size();++i) {
		ll v=G[u][i];
		if (!dfn[v]) {
			tarjan(v);
			low[u]=min(low[v],low[u]);
		}
		else if (vis[v]) low[u]=min(low[u],dfn[v]);
	}
	if (low[u]==dfn[u]) {
		tot++;
		while (q.top()!=u) solve(q.top());
		solve(u);
	}
}
ll cntt;
inline ll opposite(ll x) {
	if (x<=n) return x+n;
	else return x-n;
}
inline void init() {
	while (!q.empty()) q.pop();
	for (ll i=1;i<=cntt;++i) low[i]=dfn[i]=vis[i]=color[i]=0;
	for (ll i=1;i<=cntt;++i) G[i].clear(); 
	tot=cnt=0;cntt=2*n;
}
inline void build(ll p,ll l,ll r) {
	t[p].id=++cntt;t[p].l=l;t[p].r=r;
//	cout<<p<<" "<<t[p].l<<" "<<t[p].r<<" "<<endl;
	if (l==r) {
		G[t[p].id].push_back(opposite(node[l].second));
		return;
	}
	ll mid=(l+r)>>1;
	build(p<<1,l,mid);build(p<<1|1,mid+1,r);
	G[t[p].id].push_back(t[p<<1].id);
	G[t[p].id].push_back(t[p<<1|1].id);
	
}
inline void link(ll p,ll l,ll r,ll x) {
//	cout<<p<<" "<<t[p].l<<" "<<t[p].r<<" "<<l<<" "<<r<<endl;
	if (l>r) return;
	if (t[p].l>=l&&t[p].r<=r) {
		G[x].push_back(t[p].id);
		return;
	}
	ll mid=(t[p].l+t[p].r)>>1;
	if (l<=mid) link(p<<1,l,r,x);
	if (r>mid) link(p<<1|1,l,r,x);
}
inline bool check(ll x) {
	init();
	build(1,1,2*n);
	for (ll i=1;i<=2*n;++i) {
		ll inff=inf;
		ll l=upper_bound(node+1,node+1+n*2,make_pair(node[i].first-x,inff))-node;
		ll r=upper_bound(node+1,node+1+2*n,make_pair(node[i].first+x-1,inff))-node-1;
		link(1,l,i-1,node[i].second);link(1,i+1,r,node[i].second);
	}
	for (ll i=1;i<=2*n;++i) if (!dfn[i]) tarjan(i);
	for (ll i=1;i<=n;++i) if (color[i]==color[i+n]) return false;
	return true;
}
inline ll in() {
    char a=getchar();
	ll t=0,f=1;
	while(a<'0'||a>'9') {if (a=='-') f=-1;a=getchar();}
    while(a>='0'&&a<='9') {t=(t<<1)+(t<<3)+a-'0';a=getchar();}
    return t*f;
}
signed main() {
	n=in();
	for (ll i=1;i<=n;++i) {
		node[i].first=in(),node[i+n].first=in();
		node[i].second=i;node[i+n].second=i+n;
	}
	sort(node+1,node+1+2*n);
	ll l=0,r=node[n*2].first-node[1].first+1,mid;
	while (l<r) {
		mid=(l+r+1)>>1;
		if (check(mid)) l=mid;
		else r=mid-1;
	}
	printf("%lld",l);
	return 0;
}
```


---

## 作者：Leasier (赞：1)

前置芝士：[2-SAT](https://oi-wiki.org/graph/2-sat/)、[分块](https://oi-wiki.org/ds/decompose/)

显然二分答案，则考虑 check；显然 2-SAT，则考虑建图。

将所有 $x_i$ 和 $y_i$ 排序，设合在一起排序后得到的数组为 $a$。

对于一个 $i$，拆出两个点 $i$ 和 $i'$，分别表示选择 $x_i$ 和 $y_i$。

设二分答案的值为 $mid$，对于一个 $i$，$pos_i$ 向满足 $j \neq i$ 且 $|a_i - a_j| < mid$ 的 $pos_j$ 连边，其中 $pos_i$ 表示 $a_i$ 在原来的 $x$ 中的编号或 $y$ 中的编号 $+ n$。

直接分块优化建图即可。时间复杂度为 $O(n \sqrt{n} \log w)$。

~~不要问我为什么不写线段树优化建图，因为我爱分块。~~

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <stack>
#include <cmath>

using namespace std;

typedef struct Node_tag {
	int val;
	int pos;
	int type;
	Node_tag(){}
	Node_tag(int val_, int pos_, int type_){
		val = val_;
		pos = pos_;
		type = type_;
	}
} Node;

typedef struct {
	int nxt;
	int end;
} Edge;

int cnt;
int x[10007], y[10007], bel[20007], id1[20007], id2[20007], lft[147], rt[147], id3[147], head[20147], dfn[20147], low[20147], belong[20147];
bool vis1[20147], vis2[20147];
Node a[20007];
Edge edge[16840007];
stack<int> s;

bool operator <(const Node a, const Node b){
	return a.val < b.val;
}

inline void init(int n){
	cnt = 0;
	for (register int i = 1; i <= n; i++){
		head[i] = 0;
		vis1[i] = false;
	}
}

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

inline void tarjan(int u, int &id1, int &scc_cnt){
	dfn[u] = low[u] = ++id1;
	vis1[u] = vis2[u] = true;
	s.push(u);
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (!vis1[x]){
			tarjan(x, id1, scc_cnt);
			low[u] = min(low[u], low[x]);
		} else if (vis2[x]){
			low[u] = min(low[u], dfn[x]);
		}
	}
	if (dfn[u] == low[u]){
		int cur;
		scc_cnt++;
		do {
			cur = s.top();
			s.pop();
			vis2[cur] = false;
			belong[cur] = scc_cnt;
		} while (cur != u);
	}
}

inline void connect(int x, int l, int r){
	if (bel[l] == bel[r]){
		for (register int i = l; i <= r; i++){
			add_edge(x, id2[i]);
		}
		return;
	}
	for (register int i = l; i <= rt[bel[l]]; i++){
		add_edge(x, id2[i]);
	}
	for (register int i = lft[bel[r]]; i <= r; i++){
		add_edge(x, id2[i]);
	}
	for (register int i = bel[l] + 1; i < bel[r]; i++){
		add_edge(x, id3[i]);
	}
}

inline bool check(int n, int m, int k){
	int x = n * 2, dfn_id = 0, scc_cnt = 0;
	init(id3[k]);
	for (register int i = 1; i <= k; i++){
		add_edge(id3[bel[i]], id2[i]);
	}
	for (register int i = 1; i <= x; i++){
		int l = 1, r = i, pos = i;
		while (l <= r){
			int mid = (l + r) >> 1;
			if (a[i].val - a[mid].val < m){
				r = mid - 1;
				pos = mid;
			} else {
				l = mid + 1;
			}
		}
		if (pos < i) connect(id1[i], pos, i - 1);
		l = i;
		r = x;
		pos = i;
		while (l <= r){
			int mid = (l + r) >> 1;
			if (a[mid].val - a[i].val < m){
				l = mid + 1;
				pos = mid;
			} else {
				r = mid - 1;
			}
		}
		if (i < pos) connect(id1[i], i + 1, pos);
	}
	for (register int i = 1; i <= id3[k]; i++){
		if (!vis1[i]) tarjan(i, dfn_id, scc_cnt);
	}
	for (register int i = 1; i <= n; i++){
		if (belong[i] == belong[i + n]) return false;
	}
	return true;
}

int main(){
	int n, m, block, k, l = 0, r, ans;
	cin >> n;
	m = n * 2;
	block = sqrt(m);
	k = (m - 1) / block + 1;
	for (register int i = 1, j = 0; i <= n; i++){
		cin >> x[i] >> y[i];
		a[++j] = Node(x[i], i, 0);
		a[++j] = Node(y[i], i, 1);
	}
	sort(a + 1, a + m + 1);
	r = a[m].val - a[1].val;
	for (register int i = 1; i <= m; i++){
		bel[i] = (i - 1) / block + 1;
		if (a[i].type == 0){
			id1[i] = a[i].pos;
			id2[i] = a[i].pos + n;
		} else {
			id1[i] = a[i].pos + n;
			id2[i] = a[i].pos;
		}
	}
	for (register int i = 1; i <= k; i++){
		lft[i] = block * (i - 1) + 1;
		rt[i] = min(i * block, m);
		id3[i] = i + m;
	}
	while (l <= r){
		int mid = (l + r) >> 1;
		if (check(n, mid, k)){
			l = mid + 1;
			ans = mid;
		} else {
			r = mid - 1;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：ez_lcw (赞：1)

首先先二分答案。

然后判断能否使得两两旗子之间的距离都大于 $mid$。

然后发现这是一个 2-SAT 问题。

2-SAT 问题：通俗地说，有 $n$ 个 bool 变量 $a_i$，并给出一些形如 $a_i\oplus a_j=0/1$ 的条件（其中 $\oplus$ 可以是 $\operatorname{and}$、$\operatorname{or}$ 或 $\operatorname{xor}$），然后询问满足这组方程的一组解 $a_i$。

这题同样也给出了一些条件，比如说对于所有的 $i$，$x_i$ 和 $y_i$ 中必须选一个但是不能同时选。同时在 $mid$ 的约束下，也有一些数不能同时选。

那我们可以设 bool 变量 $a_i$ 表示取不取 $x_i$，bool 变量 $b_i$ 表示取不取 $y_i$。那么 $a_i$ 和 $b_i$ 不能同时等于 $\text{true}$，且两者中肯定有一者为 $\text{true}$，这就可以用 $a_i\operatorname{xor}b_i=1$ 来表示。

那么这就变成了一个 2-SAT 问题了。

但是这道题只用判断是否有解，也就是可行性。这时可以用 Tarjan 求解：

首先把每一个 bool 变量 $x$ 拆成两个命题：命题 $x_0$ 表示 $x=\text{false}$，命题 $x_1$ 表示 $x=\text{true}$。设命题 $y$ 的反面是 $y'$，显然 $x_0'$ 就是 $x_1$。

那么显然当 $x_0$ 成立时，$x_1$ 不成立；当 $x_1$ 成立时，$x_0$ 不成立。而且 $x_0$ 和 $x_1$ 之间肯定有一者成立。

那么 $a_i\operatorname{xor}b_i=1$ 就等价于：

当 $a_{i,0}$ 成立时，$b_{i,1}$ 成立；当 $b_{i,1}$ 成立时，$a_{i,0}$ 成立。

当 $a_{i,1}$ 成立时，$b_{i,0}$ 成立；当 $b_{i,0}$ 成立时，$a_{i,1}$ 成立。

考虑用图论的方式来表达这种关系。

设单向边 $(u,v)$ 表示当命题 $u$ 成立时，命题 $v$ 也必定成立。

那么上述关系就可以表示成单向边 $(a_{i,0},b_{i,1})$、$(b_{i,1},a_{i,0})$、$(a_{i,1},b_{i,0})$、$(b_{i,0},a_{i,1})$。

然后题目中还有一些条件：某两个数不能同时取，即某两个 bool 变量 $a$、$b$ 不能同时为 $1$，即 $a\operatorname{and} b=0$，考虑也用图论来表示这个。

发现可以用有向边 $(a_1,b_0)$、$(b_1,a_0)$ 来表示。

那么我们就能把所有的条件都用图来表示了。

至于如何判断解的可行性：

我们可以先对这个图做一遍 Tarjan，然后看是否存在两个反命题在一个环中（即出现 “当命题 $x$ 成立时，可得命题 $x'$ 成立，当 $x'$ 成立时，也可得 $x$ 成立，但 $x$、$x'$ 为相反的命题” 这种情况）。如果存在，那么原方程无解，否则有解。

然后这道题需要用线段树优化建图才能过，这部分其他巨佬已经讲得很详细了，我就不多讲了。

代码如下：

```cpp
//1~n 取x[i]
//n+1~2n 取y[i]
//2n+1~3n 不取x[i]
//3n=1~4n 不取y[i] 
#include<bits/stdc++.h>

#define N 20010

using namespace std;

struct data
{
	int val,id;
	data(){};
	data(int a,int b){val=a,id=b;} 
}a[N<<1];

int n;
int node,id[N<<3];
int idx,dfn[N*12],low[N*12];
int top,sta[N*12];
int tot,num[N*12];
int cnt,head[N*12],to[N*44],nxt[N*44];
bool ins[N*12];

bool cmp(data a,data b)
{
	return a.val<b.val;
}

void adde(int u,int v)
{
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}

void build(int k,int l,int r)
{
	if(l==r)
	{
		id[k]=(n<<1)+a[l].id;
		return;
	}
	id[k]=++node;
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	adde(id[k],id[k<<1]);
	adde(id[k],id[k<<1|1]);
}

void link(int k,int l,int r,int ql,int qr,int rt)
{
	if(ql<=l&&r<=qr)
	{
		adde(rt,id[k]);
		return;
	}
	int mid=(l+r)>>1;
	if(ql<=mid) link(k<<1,l,mid,ql,qr,rt);
	if(qr>mid) link(k<<1|1,mid+1,r,ql,qr,rt);
}

void Tarjan(int u)
{
	dfn[u]=low[u]=++idx;
	sta[++top]=u;
	ins[u]=true;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(!dfn[v])
		{
			Tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(!num[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		tot++;
		int v;
		do
		{
			v=sta[top];
			top--;
			ins[v]=false;
			num[v]=tot;
		}while(u!=v);
	}
}

bool check(int mid)
{
	cnt=idx=tot=0,node=n<<2;
	memset(head,0,sizeof(head));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(num,0,sizeof(num));
	build(1,1,n<<1);
	for(int i=1;i<=n;i++)
	{
		adde(i,n+(n<<1)+i);//取x[i]则不取y[i] 
		adde(n+(n<<1)+i,i);//不取y[i]则取x[i] 
		adde(n+i,(n<<1)+i);//取y[i]则不取x[i]
		adde((n<<1)+i,n+i); //不取x[i]则取y[i]
	}
	int nowl=1,nowr=1;
	for(int i=1;i<=(n<<1);i++)
	{
		while(nowl<i&&a[i].val-a[nowl].val>=mid) nowl++;
		while(nowr<(n<<1)&&a[nowr+1].val-a[i].val<mid) nowr++;
		if(nowl<i) link(1,1,n<<1,nowl,i-1,a[i].id);
		if(nowr>i) link(1,1,n<<1,i+1,nowr,a[i].id);
	}
	for(int i=1;i<=(n<<1);i++)
		if(!dfn[i])
			Tarjan(i);
	for(int i=1;i<=(n<<1);i++)
		if(num[i]==num[i+(n<<1)])
			return false;
	return true;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].val,&a[n+i].val);
		a[i].id=i,a[n+i].id=n+i;
	}
	sort(a+1,a+(n<<1)+1,cmp);
	int l=0,r=1e9,ans;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：xujindong_ (赞：0)

首先二分答案。此时有若干个限制，对于两个不同的标志放置的位置 $A,B$，若 $dis(A,B)<mid$，则 $A,B$ 互斥，即 $A\Rightarrow\neg B,B\Rightarrow\neg A$。

将所有位置排序，则一个位置会向两个区间对应的相反点连边。考虑线段树优化建图，建一棵叶向线段树，叶节点指向对应的相反点。$O(n\log n\log V)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,num[100005],dfn[100005],low[100005],st[100005],top,cc,d;
bool vis[100005];
pair<int,int>x[20005];
vector<int>e[100005],g[100005];
void dfs(int pos,vector<int>e[],int num[]){
  low[pos]=dfn[pos]=++d,st[++top]=pos,vis[pos]=1;
  for(int i=0;i<e[pos].size();i++){
    if(!dfn[e[pos][i]])dfs(e[pos][i],e,num),low[pos]=min(low[pos],low[e[pos][i]]);
    else if(vis[e[pos][i]])low[pos]=min(low[pos],dfn[e[pos][i]]);
  }
  if(dfn[pos]==low[pos]){
    cc++;
    do num[st[top]]=cc,vis[st[top]]=0;
    while(st[top--]!=pos);
  }
}
int tarjan(int n,vector<int>e[],int num[]){
  for(int i=1;i<=n;i++)if(!dfn[i])dfs(i,e,num);
  return cc;
}
void build(int pos,int nl,int nr){
  if(nl==nr)e[2*n+pos].push_back(x[nl].second<=n?x[nl].second+n:x[nl].second-n);
  else{
    int mid=(nl+nr)>>1;
    e[2*n+pos].push_back(2*n+(pos<<1)),e[2*n+pos].push_back(2*n+(pos<<1|1));
    build(pos<<1,nl,mid),build(pos<<1|1,mid+1,nr);
  }
}
void add(int pos,int nl,int nr,int gl,int gr,int k){
  if(gl>gr)return;
  if(gl<=nl&&nr<=gr){
    e[k].push_back(2*n+pos);
    return;
  }
  int mid=(nl+nr)>>1;
  if(gl<=mid)add(pos<<1,nl,mid,gl,gr,k);
  if(gr>mid)add(pos<<1|1,mid+1,nr,gl,gr,k);
}
bool check(int mid){
  memset(dfn,0,sizeof(dfn)),top=cc=d=0;
  for(int i=1;i<=10*n;i++)e[i]=g[i];
  for(int i=1;i<=2*n;i++){
    int l=lower_bound(x+1,x+2*n+1,make_pair(x[i].first-mid+1,0))-x,r=lower_bound(x+1,x+2*n+1,make_pair(x[i].first+mid-1,2*n+1))-x-1;
    add(1,1,2*n,l,i-1,x[i].second),add(1,1,2*n,i+1,r,x[i].second);
  }
  tarjan(10*n,e,num);
  for(int i=1;i<=n;i++)if(num[i]==num[n+i])return 0;
  return 1;
}
int main(){
  cin>>n;
  for(int i=1;i<=n;i++)cin>>x[i].first>>x[n+i].first,x[i].second=i,x[n+i].second=n+i;
  sort(x+1,x+2*n+1),build(1,1,2*n);
  for(int i=1;i<=10*n;i++)g[i]=e[i];
  int l=0,r=1e9;
  while(l<r){
    int mid=(l+r+1)>>1;
    if(check(mid))l=mid;
    else r=mid-1;
  }
  return cout<<l<<'\n',0;
}
```

考虑不建图，直接求出强连通分量。首先需要抛弃 Tarjan，因为 Tarjan 需要访问返祖边，无法优化。

使用结构更简单的 Kosaraju，则只需要支持在原图和反图上 DFS，每个点的连边是一个区间内的相反点/相反点对应的一个区间，也就需要快速访问一个区间内未访问的点。维护一个序列并查集，每个位置指向下一个未被访问的位置。$O(n\log n\log V)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p[20005],l[20005],r[20005],f[20005],num[20005],st[20005],top,cc;
pair<int,int>x[20005];
int find(int x){
  return f[x]?f[x]=find(f[x]):x;
}
bool merge(int u,int v){
  return u=find(u),v=find(v),u==v?0:(f[u]=v,1);
}
int id(int x){
  return x<=n?x+n:x-n;
}
void dfs1(int pos){
  merge(p[id(pos)],p[id(pos)]+1);
  for(int i=find(l[pos]);i<r[pos];i=find(i+1))if(x[i].second!=pos)dfs1(id(x[i].second));
  st[++top]=pos;
}
void dfs2(int pos){
  num[pos]=cc,merge(p[pos],p[pos]+1);
  for(int i=find(l[id(pos)]);i<r[id(pos)];i=find(i+1))if(x[i].second!=id(pos))dfs2(x[i].second);
}
bool check(int mid){
  memset(f,0,sizeof(f)),top=cc=0;
  for(int i=1,j=1,k=1;i<=2*n;i++){
    while(j<=2*n&&x[j].first<=x[i].first-mid)j++;
    while(k<=2*n&&x[k].first<x[i].first+mid)k++;
    l[x[i].second]=j,r[x[i].second]=k;
  }
  for(int i=1;i<=2*n;i++)if(!f[p[id(i)]])dfs1(i);
  memset(f,0,sizeof(f));
  for(int i=top;i>=1;i--)if(!f[p[st[i]]])cc++,dfs2(st[i]);
  for(int i=1;i<=n;i++)if(num[i]==num[n+i])return 0;
  return 1;
}
int main(){
  cin>>n;
  for(int i=1;i<=n;i++)cin>>x[i].first>>x[n+i].first,x[i].second=i,x[n+i].second=n+i;
  sort(x+1,x+2*n+1);
  for(int i=1;i<=2*n;i++)p[x[i].second]=i;
  int l=0,r=1e9;
  while(l<r){
    int mid=(l+r+1)>>1;
    if(check(mid))l=mid;
    else r=mid-1;
  }
  return cout<<l<<'\n',0;
}
```

进一步地，序列并查集可以做到线性。按 $B=w$ 分块，块间用并查集指向下一个没有全部访问的块，块内压进一个整数直接查。$O(n\log V)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p[20005],l[20005],r[20005],f[317],num[20005],st[20005],top,cc;
unsigned long long v[317];
pair<int,int>x[20005];
int find(int x){
  return ~f[x]?f[x]=find(f[x]):x;
}
int getnxt(int x){
  if(v[x>>6]>>(x&63))return x+__builtin_ctzll(v[x>>6]>>(x&63));
  else return x=find((x>>6)+1),x<<6|__builtin_ctzll(v[x]);
}
void del(int x){
  v[x>>6]-=1ull<<(x&63);
  if(!v[x>>6])f[find(x>>6)]=find((x>>6)+1);
}
int id(int x){
  return x<=n?x+n:x-n;
}
void dfs1(int pos){
  del(p[id(pos)]);
  for(int i=getnxt(l[pos]);i<r[pos];i=getnxt(i+1))if(x[i].second!=pos)dfs1(id(x[i].second));
  st[++top]=pos;
}
void dfs2(int pos){
  num[pos]=cc,del(p[pos]);
  for(int i=getnxt(l[id(pos)]);i<r[id(pos)];i=getnxt(i+1))if(x[i].second!=id(pos))dfs2(x[i].second);
}
bool check(int mid){
  memset(f,-1,sizeof(f)),memset(v,-1,sizeof(v));
  top=cc=0;
  for(int i=1,j=1,k=1;i<=2*n;i++){
    while(j<=2*n&&x[j].first<=x[i].first-mid)j++;
    while(k<=2*n&&x[k].first<x[i].first+mid)k++;
    l[x[i].second]=j,r[x[i].second]=k;
  }
  for(int i=1;i<=2*n;i++)if(p[id(i)]==getnxt(p[id(i)]))dfs1(i);
  memset(f,-1,sizeof(f)),memset(v,-1,sizeof(v));
  for(int i=top;i>=1;i--)if(p[st[i]]==getnxt(p[st[i]]))cc++,dfs2(st[i]);
  for(int i=1;i<=n;i++)if(num[i]==num[n+i])return 0;
  return 1;
}
int main(){
  cin>>n;
  for(int i=1;i<=n;i++)cin>>x[i].first>>x[n+i].first,x[i].second=i,x[n+i].second=n+i;
  sort(x+1,x+2*n+1);
  for(int i=1;i<=2*n;i++)p[x[i].second]=i;
  int l=0,r=1e9;
  while(l<r){
    int mid=(l+r+1)>>1;
    if(check(mid))l=mid;
    else r=mid-1;
  }
  return cout<<l<<'\n',0;
}
```

---

## 作者：CmsMartin (赞：0)

[更好的阅读体验](http://www.cmsblog.top/archives/arc069dflags)

## 题目描述

[题目传送门](https://www.luogu.com.cn/problem/AT2336)

## 思路

首先看到最小距离最大，果断二分答案。

然后问题就转化为第 $i$ 个标志可以放置在坐标 $x_i$ 或坐标 $y_i$ 上的最小距离是否可以比 $x$ 大。

这个问题是不是莫名熟悉，有一个变量有两种取值，并且有一定的约束关系（因为距离限制），然后找有没有可行解。于是你就想到了 2-SAT，然后开心的写了一发，TLE 了。

这里有一个问题，像这样连边的时间复杂度 $\Theta(n^2)$ 的，过不了最大的数据点，考虑优化。这时你需要用到一个 trick 叫做线段树优化建图。首先先对所有可能放旗子的点排序，然后你会发现一个点需要连的点是连续的。可以建一棵线段树，因为有父子关系，所有的父亲像儿子连边。为了方便写代码，我们可以强行要求叶子节点的下表为 $1 \sim 2n$。接下来就非常类似于区间询问了，直接递归就行了，总时间复杂度 $\Theta(n\log^2 n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 4e4 * 5 + 10;

int Head[MAXN], Next[MAXN << 2], To[MAXN << 2], ToT;
void Add(int u, int v) {
    To[++ToT] = v;
    Next[ToT] = Head[u];
    Head[u] = ToT;
}

int Dfn[MAXN], Low[MAXN];
bool In_Stack[MAXN];
int Stack[MAXN], Top;
int Index, SCC, N;
int Belong[MAXN];

void Tarjan(int u) {
    Stack[++Top] = u;
    In_Stack[u] = true;
    Dfn[u] = Low[u] = ++Index;
    for (int i = Head[u]; i; i = Next[i]) {
        int v = To[i];
        if (!Dfn[v]) {
            Tarjan(v);
            Low[u] = min(Low[u], Low[v]);
        } else if (In_Stack[v]) {
            Low[u] = min(Low[u], Dfn[v]);
        }
    }

    if (Dfn[u] == Low[u]) {
        ++SCC;
        int v;
        do {
            v = Stack[Top--];
            Belong[v] = SCC;
            In_Stack[v] = false;
        } while (v != u);
    }
}

int GetOpposite(int x) {
    if (x <= N)
        return x + N;
    else
        return x - N;
}

pair<int, int> Flags[MAXN << 1];

int SegmentTree[MAXN << 2], Cnt;
void Build(int p, int l, int r) {
    SegmentTree[p] = ++Cnt;
    if (l == r) {
        Add(SegmentTree[p], GetOpposite(Flags[l].second));
        return;
    }
    int mid = l + r >> 1;
    Build(p << 1, l, mid);
    Build(p << 1 | 1, mid + 1, r);
    Add(SegmentTree[p], SegmentTree[p << 1]);
    Add(SegmentTree[p], SegmentTree[p << 1 | 1]);
}

void Link(int p, int L, int R, int l, int r, int x) {
    if (l > r) return;
    int mid = L + R >> 1;
    if (L == l && R == r)
    	Add(x, SegmentTree[p]);
    else if (r <= mid)
        Link(p << 1, L, mid, l, r, x);
    else if (l > mid)
        Link(p << 1 | 1, mid + 1, R, l, r, x);
    else {
        Link(p << 1, L, mid, l, mid, x);
        Link(p << 1 | 1, mid + 1, R, mid + 1, r, x);
    }
}

bool Check(int x) {
    ToT = Top = Index = SCC = 0;
    memset(Head, 0, sizeof Head);
    memset(Dfn, 0, sizeof Dfn);
    memset(Low, 0, sizeof Low);
    memset(In_Stack, 0, sizeof In_Stack);
    Build(1, 1, Cnt = 2 * N);
    for (int i = 1; i <= 2 * N; i++) {
        static int l, r;
        l = upper_bound(Flags + 1, Flags + 1 + 2 * N, make_pair(Flags[i].first - x, 0x3f3f3f3f)) - Flags;
        r = upper_bound(Flags + 1, Flags + 1 + 2 * N, make_pair(Flags[i].first + x - 1, 0x3f3f3f3f)) - Flags - 1;
        Link(1, 1, 2 * N, l, i - 1, Flags[i].second);
        Link(1, 1, 2 * N, i + 1, r, Flags[i].second);
    }
    for (int i = 1;
         i <= 2 * N; i++) {
        if (!Dfn[i]) Tarjan(i);
    }
    for (int i = 1; i <= N; i++) {
        if (Belong[i] == Belong[i + N]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> Flags[i].first >> Flags[i + N].first;
        Flags[i].second = i;
        Flags[i + N].second = i + N;
    }

    sort(Flags + 1, Flags + 1 + 2 * N);

    int l = 0, r = Flags[2 * N].first - Flags[1].first + 1, mid, Ans = -1;

    while (l <= r) {
        mid = l + r >> 1;
        if (Check(mid)) {
            l = mid + 1;
            Ans = mid;
        } else {
            r = mid - 1;
        }
    }

    cout << Ans << endl;
    return 0;
}
```

---

## 作者：orz_z (赞：0)

### AT2336 [ARC069D] Flags

二分答案，`2-sat` 判定，线段树优化建边。

线段树上父亲向儿子连边。

对于每个点 $x$，连向与他距离不超过 $mid$ 的点的反点，表示选 $x$ 就只能选与他距离不超过 $mid$ 的点。

最后跑 `tarjan` 判定即可。

时间复杂度 $\mathcal O(n\log ^2n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

//#define int long long
typedef long long ll;

#define ha putchar(' ')
#define he putchar('\n')

inline int read() {
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		x = x * 10 + c - '0', c = getchar();
	return x * f;
}

inline void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}

const int _ = 8e4 + 10;

int n, cnt, idx, scc, low[_], dfn[_], id[_], Id[_];

stack<int> s;

vector<pair<int, int>> d;

vector<int> e[_];

void build(int o, int l, int r) {
	id[o] = ++cnt;
	if (o > 1) e[id[o >> 1]].emplace_back(cnt);
	if (l == r) {
		int v = d[l - 1].second;
		e[id[o]].push_back(v <= n ? v + n : v - n);
		return;
	}
	int mid = (l + r) >> 1;
	build(o << 1, l, mid), build(o << 1 | 1, mid + 1, r);
}

void upd(int o, int l, int r, int L, int R, int x) {
	if(L > R) return;
	if (L <= l && r <= R) {
		e[x].emplace_back(id[o]);
		return;
	}
	int mid = (l + r) >> 1;
	if (L <= mid) upd(o << 1, l, mid, L, R, x);
	if (R > mid) upd(o << 1 | 1, mid + 1, r, L, R, x);
}

pair<int, int> get(int i, int m) {
	pair<int, int> ret;
	int l = 1, r = i, mid;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (d[i - 1].first - d[mid - 1].first >= m) l = mid + 1;
		else r = mid - 1;
	}
	ret.first = r + 1, l = i, r = n << 1;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (d[mid - 1].first - d[i - 1].first < m) l = mid + 1;
		else r = mid - 1;
	}
	ret.second = l - 1;
	return ret;
}

void tarjan(int u) {
	low[u] = dfn[u] = ++idx;
	s.push(u);
	for (int v : e[u])
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (!Id[v]) low[u] = min(low[u], dfn[v]);
	if (low[u] == dfn[u]) {
		++scc;
		while (1) {
			int nw = s.top();
			s.pop();
			Id[nw] = scc;
			if (nw == u) break;
		}
	}
}

bool check(int lim) {
	scc = idx = 0;
	memset(low, 0, sizeof low);
	memset(dfn, 0, sizeof dfn);
	memset(Id, 0, sizeof Id);
	for (int i = 0; i < _; ++i) e[i].clear();
	build(1, 1, cnt = n << 1);
	for (int i = 1; i <= n << 1; ++i) {
		int r = d[i - 1].second;
		pair<int, int> p = get(i, lim);
		upd(1, 1, n << 1, p.first, i - 1, r);
		upd(1, 1, n << 1, i + 1, p.second, r);
	}
	for (int i = 1; i <= n << 1; ++i)
		if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; ++i)
		if (Id[i] == Id[i + n]) return 0;
	return 1;
}

signed main() {
	n = read();
	for (int i = 1, x, y; i <= n; ++i) {
		x = read(), y = read();
		d.emplace_back(make_pair(x, i));
		d.emplace_back(make_pair(y, i + n));
	}
	sort(d.begin(), d.end());
	int l = 0, r = 1e9, mid;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (check(mid)) l = mid + 1;
		else r = mid - 1;
	}
	write(l - 1), he;
	return 0;
}
```



---

## 作者：小木虫 (赞：0)

### Preface  

一道细节极其之多的恶心的 2-SAT 题目变种。蒟蒻刚 whk 回来复健不太适应。  

### [Problem](https://atcoder.jp/contests/arc069/tasks/arc069_d)

### Solution  

看到题目要求最小差间最大马上便想到了二分，验证答案的话贪心不易验证，并且不支持 $O(n^2)$ 的高复杂度验证。看到两个选一个便想到了使用 2-SAT 进行求解。显然选择一个点后周围 $d$ 距离内的点都不应被选中而应选中其的另外点。  
这个条件便可以转化为：要么这个点所代表的元素是另一个状态，要么 $d$ 距离内的其它点是另一个状态。  
便可以轻易用 2-SAT 验证。   
观察到这个题的数据范围不大不小，我们拿一个分块优化建图即可。具体来说，我们拿出两个分块，一个分出来的块和第一个状态贴贴（由块连向第一个状态） 。另一个和第二个状态（块内元素的另一个状态）贴贴（由第二个状态连向块）。然后需要进行操作的时候两个块交叉对需要连边的点的两个状态进行操作即可。 

------------

接下来针对比较恶心的几个点进行讲解：  

1. 二分到的答案为 $d$ 时，我们对于每个点 $x$ 将 $|x-y|\leq d-1$ 的 $y$ 点进行连边处理，因为刚刚好 $d$ 距离也是满足题目条件的。  

2. 最后验证答案时不应为：$in_i = in_{i+n}$，因为这个序列已被离散化了，所以应该记录每个点的另一个状态在哪记为 $oth_i$，到时候验证 $in_i=in_{oth_i}$。 

3. `upper_bound` 函数应该额外 `-1`。蒟蒻第一次用不知道它在找不到的时候会返回 `end()+1`。  

4. 时刻铭记我们连边的意义！记得初始化！

   ### code：  

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{int d,id,tpe,oth;}h[N];int a[N],b[N];
bool cmp(node a,node b){return a.d<b.d;};int c[N];
int n;node h2;int block;int p[N];int bcnt;
vector <int> edge[N];int Size;int Stack[N];
int low[N];int dfn[N];bool vis[N];int tot;
int in[N];int cnt;
void tarjan(int x){
	Stack[++Size]=x;
	vis[x]=true;++cnt;
	low[x]=dfn[x]=cnt;
	for(int i=0;i<edge[x].size();i++){
		if(!dfn[edge[x][i]]){
			tarjan(edge[x][i]);
			low[x]=min(low[x],low[edge[x][i]]);
		}else{
			if(vis[edge[x][i]])
				low[x]=min(low[x],dfn[edge[x][i]]);
		}	
	}
	if(dfn[x]==low[x]){
		++tot;int k=0;
		do{k=Stack[Size];--Size;
			vis[k]=false;
			in[k]=tot;
		}while(k!=x);
	}
}
void modify(int l,int r,int x){
	if(l>r)return;
	while(l<=r&&p[l-1]==p[l]){
		edge[x].push_back(h[l].oth);
		edge[l].push_back(h[x].oth);
		l++;
	}
	while(l+block<=r){
		edge[x].push_back(p[l]+2*n);
		edge[p[l]+bcnt+2*n].push_back(h[x].oth);
		l+=block;
	}
	while(l<=r){
		edge[x].push_back(h[l].oth);
		edge[l].push_back(h[x].oth);
		l++;
	}
}
bool check(int x){
	cnt=tot=Size=0;
	memset(dfn,0,sizeof(dfn));
	memset(vis,false,sizeof(vis));
	memset(Stack,0,sizeof(Stack));
	memset(in,0,sizeof(in));
	memset(low,0,sizeof(low));
	for(int i=1;i<=2*n+2*bcnt;i++)edge[i].clear();
	for(int i=1;i<=2*n;i++){
		edge[p[i]+2*n].push_back(h[i].oth);
	}
	for(int i=1;i<=2*n;i++){
		edge[i].push_back(p[i]+2*n+bcnt);
	}
	//cout<<x<<endl;
	for(int i=1;i<=2*n;i++){
		int l=lower_bound(c+1,c+2*n+1,h[i].d-x+1)-c;
		int r=upper_bound(c+1,c+2*n+1,h[i].d+x-1)-c-1;
	//	cout<<h[i].oth<<" "<<l<<" "<<r<<endl;
		modify(l,i-1,i);modify(i+1,r,i);
	}
	//for(int i=1;i<=2*n+2*bcnt;i++){
	//	cout<<i<<":"<<endl;
	//	for(int j=0;j<edge[i].size();j++){
	//		cout<<edge[i][j]<<" ";
	//	}
	//	cout<<endl;
	//}
	for(int i=1;i<=2*n+2*bcnt;i++){
		if(!dfn[i])tarjan(i);
	}
	//for(int i=1;i<=n;i++)cout<<in[i]<<" "<<in[i+n]<<endl;
	//cout<<endl;
	for(int i=1;i<=n;i++)
		if(in[i]==in[h[i].oth])return false;
	return true;
}
int bucket[N];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;block=sqrt(2*n);
	if((2*n)%block==0)bcnt=(2*n)/block;
	else bcnt=(2*n)/block+1;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		h[i]=(node){a[i],i,0,0};
		h[i+n]=(node){b[i],i,1,0};
		if(i%block==0)p[i]=i/block;
		else p[i]=i/block+1;
	}
	for(int i=n+1;i<=2*n;i++){
		if(i%block==0)p[i]=i/block;
		else p[i]=i/block+1;
	}
	sort(h+1,h+2*n+1,cmp);
	sort(a+1,a+1+n);sort(b+1,b+1+n);
	for(int i=1;i<=2*n;i++){
		c[i]=h[i].d;
		if(bucket[h[i].id]){
			h[i].oth=bucket[h[i].id];
			h[bucket[h[i].id]].oth=i;
		}bucket[h[i].id]=i;
	}
	int l=0;int r=1e9;
	while(l<r){
		int mid=(l+r+1)/2;
		if(check(mid))l=mid;
		else r=mid-1;
	}
	cout<<l;
	return 0;
}
```

---

