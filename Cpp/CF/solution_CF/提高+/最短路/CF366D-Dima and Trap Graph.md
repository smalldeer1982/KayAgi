# Dima and Trap Graph

## 题目描述

Dima and Inna love spending time together. The problem is, Seryozha isn't too enthusiastic to leave his room for some reason. But Dima and Inna love each other so much that they decided to get criminal...

Dima constructed a trap graph. He shouted: "Hey Seryozha, have a look at my cool graph!" to get his roommate interested and kicked him into the first node.

A trap graph is an undirected graph consisting of $ n $ nodes and $ m $ edges. For edge number $ k $ , Dima denoted a range of integers from $ l_{k} $ to $ r_{k} $ $ (l_{k}<=r_{k}) $ . In order to get out of the trap graph, Seryozha initially (before starting his movements) should pick some integer (let's call it $ x $ ), then Seryozha must go some way from the starting node with number $ 1 $ to the final node with number $ n $ . At that, Seryozha can go along edge $ k $ only if $ l_{k}<=x<=r_{k} $ .

Seryozha is a mathematician. He defined the loyalty of some path from the $ 1 $ -st node to the $ n $ -th one as the number of integers $ x $ , such that if he initially chooses one of them, he passes the whole path. Help Seryozha find the path of maximum loyalty and return to his room as quickly as possible!

## 说明/提示

Explanation of the first example.

Overall, we have 2 ways to get from node 1 to node 4: first you must go along the edge 1-2 with range \[1-10\], then along one of the two edges 2-4.

One of them contains range \[3-5\], that is, we can pass through with numbers 3, 4, 5. So the loyalty of such path is 3.

If we go along edge 2-4 with range \[2-7\], then we can pass through with numbers 2, 3, 4, 5, 6, 7. The loyalty is 6. That is the answer.

The edge 1-2 have no influence on the answer because its range includes both ranges of the following edges.

## 样例 #1

### 输入

```
4 4
1 2 1 10
2 4 3 5
1 3 1 5
2 4 2 7
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5 6
1 2 1 10
2 5 11 20
1 4 2 5
1 3 10 11
3 4 12 10000
4 5 6 6
```

### 输出

```
Nice work, Dima!
```

# 题解

## 作者：50lty12 (赞：4)

来一种与其他题解不一样的解法，但本人无法证明其时间复杂度的正确性（可能会被 hack），希望各位大佬多多指导。

看到此题，显然可以写出一种爆搜代码（纯暴力，不加任何优化）：
```cpp
void dfs(int u,int l,int r){
	if(l>r || r-l+1<=ans) return;
	if(u==n){
		ans=max(ans,r-l+1);
		return;
	}
	for(int i=head[u]; i; i=d[i].n){
		int v=d[i].b;
		dfs(v,max(d[i].l,l),min(d[i].r,r));
	}
}
```
这样交上去肯定会 TLE。

再加以思考，容易发现，从点 $1$ 出发，跑到一个固定的点 $u$ 时，如果两次的 $l,r$ 相等时，那么后面那一次就没必要再跑下去了。因此可以对其加个记忆化。搜索部分代码如下：
```cpp
void dfs(int u,int l,int r){
	if(l>r || r-l+1<=ans) return;
	if(s[u].count({l,r})) return;
	s[u].insert({l,r});
	if(u==n){
		ans=max(ans,r-l+1);
		return;
	}
	for(int i=head[u]; i; i=d[i].n){
		int v=d[i].b;
		dfs(v,max(d[i].l,l),min(d[i].r,r));
	}
}
```
只是加了个记忆化。

本来想着加了这个优化能提高对拍的效率，结果没想到交到 CF 上竟然 AC 了，```map``` 也可 AC！这给了我们一个启示：在考场上，一个不起眼的优化，可能能带来意想不到的结果。当然优化一定要以正确性为前提。

---

## 作者：Erotate (赞：3)

### Solution

考虑二分满足答案区间，但是发现这个区间并不具有单调性。于是我们考虑固定一个端点（不妨固定左端点），然后二分右端点，此时右端点是有单调性的。

然后思考如何判断是否联通。这题可以直接使用并查集，把在当前判断的区间内的边并起来，最后看看 1 节点和 $n$ 节点是否联通即可。

这个算法的时间复杂度是 $O(m^2 \log n)$，可以通过。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5,M=3e4+5;
struct edge{
    int u,v,l,r;
}e[M];
int n,m,st[N],f[N],ans,ansl,ansr;
int find(int x){
    return x==f[x]?x:f[x]=find(f[x]);
}
void merge(int x,int y){
    int fx=find(x),fy=find(y);
    if(fx!=fy) f[fx]=fy;
}
bool check(int l,int r){
    for(int i=1;i<=n;++i) f[i]=i;
    for(int i=1;i<=m;++i)
        if(l>=e[i].l && r<=e[i].r) merge(e[i].u,e[i].v);
    if(find(1)==find(n)){
        if(r-l+1>ans || r-l+1==ans && l<ansl){
            ans=r-l+1;
            ansl=l,ansr=r;
        }
        return 1;
    }
    return 0;
}
signed main(){
    scanf("%d%d",&n,&m);
    for(int i=1,x,y,l,r;i<=m;++i){
        scanf("%d%d%d%d",&x,&y,&l,&r);
        e[i]=((edge){x,y,l,r});
        st[i]=l;
    }
    sort(st+1,st+m+1);//要先把边排序。
    for(int i=1;i<=m;++i){//从小到大枚举每一条边的左端点。
        int l=st[i],r=1e6;
        while(l<=r){
            int mid=l+r>>1;
            if(check(st[i],mid)) l=mid+1;
            else r=mid-1;
        }
    }
    if(!ans) printf("Nice work, Dima!\n");
    else printf("%d\n",ans);
    return 0;
}
```


---

## 作者：山田リョウ (赞：2)

首先注意到 $m$ 很小，所以考虑枚举答案区间的左端点 $l$，再把所有边按照区间右端点降序排序，按顺序依次选中所有区间左端点小于等于 $l$ 的边，直到 $1$ 能通过选中的边到达 $n$ 为止，这时最后选中的那条边的区间的右端点就是答案区间的左端点取 $l$ 时能搞出的最大的 $r$，然后把所有求出的 $r-l+1$ 取个 $\max$ 就行了。

具体的，连边和判连通用并查集就行，只不过记得清空哦。

code:
```cpp
// Problem: CF366D Dima and Trap Graph
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF366D
// Memory Limit: 250 MB
// Time Limit: 3000 ms

#include<stdio.h>
#include<algorithm>
int n,m,f[1001],sz[1001];
struct EDGE{
	int u,v,l,r;
	bool operator <(const EDGE&o)const{return r>o.r;}
}edge[3001];
int find(int a){return f[a]==a?a:f[a]=find(f[a]);}
void combine(int a,int b){
	int x=find(a),y=find(b);
	if(x!=y){
		if(sz[x]>sz[y])f[y]=x,sz[x]+=sz[y];
		else f[x]=y,sz[y]+=sz[x];
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)scanf("%d%d%d%d",&edge[i].u,&edge[i].v,&edge[i].l,&edge[i].r);
	std::sort(edge+1,edge+m+1);
	int len=0;
	for(int j=1;j<=m;++j){
		for(int i=1;i<=n;++i)f[i]=i;//记得要清空
		for(int i=1;i<=m;++i)
			if(edge[i].l<=edge[j].l){
				combine(edge[i].u,edge[i].v);
				if(find(1)==find(n)){len=std::max(len,edge[i].r-edge[j].l+1);break;}
			}
	}
	if(len)printf("%d",len);
	else puts("Nice work, Dima!");
	return 0;
}
```

---

## 作者：Terac (赞：0)

[$\texttt{link}$](https://www.luogu.com.cn/problem/CF366D)

## 题意

给出一个 $n$ 个点，$m$ 条边的无向图，每条边有区间 $\left[l_i,r_i\right]$，求某条 $1$ 到 $n$ 路径组成的边集，使该边集中所有区间的交内的正整数元素个数最多。

$n\le10^3,m\le3\times10^3$

## 题解

萌萌题。

显然最后区间交的左右端点为某两条边的区间的左右端点。

当左端点固定时，右端点的取法是有单调性的，即比最大区间小的区间肯定可以全部到 $n$。

于是可以枚举每条边，当这条边的区间左端点即最终区间的左端点时，二分右端点的边，判断 $1$ 到 $n$ 是否连通即可。

判断联通并查集或直接搜都可以，但前者常数大概会小些，跑的快很多。

没啥细节，也挺好写。

复杂度即 $O(nm\log m)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IO {
	//read and write
} using namespace IO;
const int N = 1e3 + 10, M = 6e3 + 10;
int n, m, ans;
struct edge {
	int to, l, r, nxt;
} e[M];
int head[N], cnt;
vector<int> tmp;
bool vis[N];
void add(int u, int v, int l, int r) {
	e[++cnt] = (edge){v, l, r, head[u]};
	head[u] = cnt;
}
bool dfs(int u, int l, int r) {
	if(u == n) return 1;
	vis[u] = 1;
	for(int i = head[u], v; i; i = e[i].nxt) {
		v = e[i].to;
		if(vis[v] || e[i].l > l || e[i].r < r) continue;
		if(dfs(v, l, r)) return 1;
	}
	return 0;
}
int main() {
	n = read(), m = read();
	for(int i = 1, u, v, l, r; i <= m; i++) {
		u = read(), v = read(), l = read(), r = read();
		add(u, v, l, r), add(v, u, l, r), tmp.push_back(r);
	}
	sort(tmp.begin(), tmp.end());
	for(int i = 1; i <= m; i++) {
		int l = lower_bound(tmp.begin(), tmp.end(), e[i << 1].l) - tmp.begin(), r = m - 1, mid = l + r >> 1, res = -1;
		while(l <= r) {
			memset(vis, 0, sizeof(vis));
			mid = l + r >> 1;
			if(dfs(1, e[i << 1].l, tmp[mid])) res = mid, l = mid + 1;
			else r = mid - 1;
		}
		if(!~res) continue;
		ans = max(ans, tmp[res] - e[i << 1].l + 1);
	}
	if(!ans) printf("Nice work, Dima!");
	else printf("%d", ans);
	return 0;
}
```


---

## 作者：SunsetSamsara (赞：0)

## 思路
最小生成树，枚举
## 分析
我在模拟赛时，本来想着是魔改最短路，看着数据范围我陷入了沉思。

$$n\le 1000, m \le 3000$$

这明显复杂度 $O(nm)$ **左右**的离散化+暴力都过得去啊？！

### 暴力思路

枚举左端点，跑最小生成树寻找右端点，复杂度 $O(u\times mlogm)$ ($u$ 是数据范围)，复杂度爆表，显然会 TLE。

### 优化

现在复杂度瓶颈就在枚举左端点上面了。

关键问题：左端点可以取到什么值呢？

+ 所有值？显然不是。如果左端点全是 $1$，有必要枚举所有值吗？

+ 发现要枚举的左端点和每个区间左端点有关，与右端点无关。

+ 于是只需枚举每个区间的左端点作为当前需枚举的左端点即可。

### 优化后性能

复杂度：

枚举每条边的权值乘最小生成树，即 $O(m^2logm)$
## 代码
（目前是最优解 $rank2$）

（但显然我只会放常数最大的代码）

```cpp
#include <bits/stdc++.h>
#define lld long long
using namespace std;
namespace IO {
	//by xhj2415
	template<class T>
	void read(register T * cstr) {
		register int top = 0;
		for (register char ch = getchar(); ch != ' ' && ch != '\n' && ch != '\r' && ch != EOF; ch = getchar())
			cstr[top ++] = ch;
		cstr[top] = '\0';
	}
	template<class T>
	void read(register T & x) {
		x = 0;
		register T f = 1;
		register char ch;
		for (ch = getchar(); '0' > ch || ch > '9'; ch = getchar())
			if (ch == '-')
				f = -1;
		for (; '0' <= ch && ch <= '9'; ch = getchar())
			x = (x << 3) + (x << 1) + (ch ^ '0');
		x *= f;
	}
	template<typename T>
	void print(register T * cstr) {
		for (register T * i = cstr; *i; ++ i)
			putchar(*i);
	}
	template<typename T>
	void print(register T x) {
		if (x < 0) {
			putchar('-');
			x = -x;
		}
		if (x > 9) print(x / 10);
		putchar((x % 10) ^ '0');
	}
}

struct edge {
    int fr, to;
    int l, r;
} e[10001];
int ecnt;
struct node {
    int l;
    int r;
} a[10001];
void addedge(int fr, int to, int l, int r) {
    e[++ ecnt].l = l;
    e[ecnt].r = r;
    e[ecnt].fr = fr;
    e[ecnt].to = to;
}
bool cmp (const edge & a, const edge & b) {
    if (a.r != b.r) return a.r > b.r;
    return a.l < b.l;
}
bool cmp1 (const node & a, const node & b) {
    if (a.l != b.l) return a.l < b.l;
    return a.r < b.r;
}
int n, m;
int dis[1001];
int srt[10001];
int len;
int fa[10001];
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
int main() {
	IO::read(n);
	IO::read(m);
    for (int i = 1, x, y, l, r; i <= m; ++ i) {
    	IO::read(x);
    	IO::read(y);
    	IO::read(l);
    	IO::read(r);
        addedge(x, y, l, r);
        srt[++ len] = l;
        srt[++ len] = r;
        a[i].l = l;
        a[i].r = r;
    }
    sort(e + 1, e + m + 1, cmp);
    sort(a + 1, a + m + 1, cmp1);
    int ans = 0, ansl = 1, ansr = 0;
    int nowr, fx, fy;
    for (int i = 1; i <= m; ++ i) {
        nowr = 2147483647;
        for (int j = 1; j <= n; ++ j)
            fa[j] = j;
        for (int j = 1; j <= m; ++ j)
            if (e[j].l <= a[i].l) {
                fx = find(e[j].fr);
                fy = find(e[j].to);
                if (fx != fy) {
                    fa[fx] = fy;
                    nowr = min(nowr, e[j].r);
                    if (find(1) == find(n))
                        break;
                }
            }
        if (find(1) == find(n))
            if (ans < nowr - a[i].l + 1) {
                ansl = a[i].l;
                ansr = nowr;
                ans = ansr - ansl + 1;
            }
    }
	if (ansr - ansl + 1 == 0)
		puts("Nice work, Dima!");
	else printf("%d\n", ansr - ansl + 1);
}
```

---

## 作者：pldzy (赞：0)

## 题意

给定一张有 $n$ 个节点，$m$ 条边的无向图（可能有环或重边），对于每个节点 $i$，有 $l_i$ 和 $r_i$，定义在经过该节点后，只能携带于 $l_i$ 和 $r_i$ 之间的数。

从编号为 1 的节点出发（初始时携带了所有自然数），到达编号为 $n$ 的节点，求最后能携带最多的节点。

若节点数相同，输出字典序小的那一组。

若节点数为 0，输出 `Nice work, Dima!`。

## 题解

模拟赛的一道题。

二分 + 图。

二分本质：

在数轴上找到一个临界点，即点的左边都可以满足条件，右边都不可以满足条件（或左边不可以，右边可以）。

在这道题中，**r 值是有单调性的**。即有一临界点，使得比它小的 r 值无法满足，比它大的 r 值可以满足。

但是，**l 不具有单调性**。例如，当 l 值为 1 时可以满足，l 值为 5 时可以满足，但是 l 值为 3 时能否满足是无法直接断定的。

所以，r 的值可以通过二分得到，l 的值只能枚举而得。

以上是思路。

但实现的时候我们可以用并查集优化：

我们从小到大枚举 l 的值，在此基础上，我们按 r 的值从大到小枚举每一条边。

保证每一条使用了的边的 $e_i.l$ 的值比当前枚举的 l 的值小。

这里就运用了二分的思想。

每用一条边，就用并查集维护，如果 $f_1 = f_n$，就记录答案，最终输出最佳答案即可。

## 代码

````cpp
#include<bits/stdc++.h>
using namespace std;

#define rint register int
const int inf = 1e6 + 5, maxn = 1005;
int n, m;
int cnt, hd[maxn];
struct node{
	int s, t;
	int l, r;
}e[maxn * 4];
int f[maxn];
int ansl, num;
int recl[maxn * 4];

inline int read ()
{
	int x = 1, s = 0;
	char ch = getchar ();
	while (ch < '0' or ch > '9'){if (ch == '-') x = -1; ch = getchar ();}
	while (ch >= '0' and ch <= '9') s = s * 10 + ch - '0', ch = getchar ();
	return x * s;
}

inline bool cmp (node a, node b)
{
	return a.r == b.r ? a.l < b.l : a.r > b.r;
}

inline void init ()
{
	for (rint i (1); i <= n; ++i) f[i] = i;
}

inline int find (int x)
{
	return f[x] == x ? x : find (f[x]);
}

int main ()
{
	n = read (), m = read ();
	for (rint i (1); i <= m; ++i) e[i].s = read (), e[i].t = read (), e[i].l = read (), e[i].r = read (), recl[i] = e[i].l;
	sort (e + 1, e + m + 1, cmp);
	sort (recl + 1, recl + m + 1);
	for (rint i (1); i <= m; ++i)
	{
		init ();
		bool flag = 0;
		int tl = recl[i], tr = inf;
		for (rint j (1); j <= m; ++j)
		{
			if (e[j].l > tl) continue;
			int u = find (e[j].s), v = find (e[j].t);
			if (u != v)
			{
				f[u] = v;
				tr = min (tr, e[j].r);
				if (find (1) == find (n)) 
				{
					flag = 1;
					break;
				}
			}
		}
		if (flag and num < tr - tl + 1) ansl = tl, num = tr - tl + 1;
	}
	if (num == 0)
	{
		printf ("Nice work, Dima!");
		return 0;
	}
	printf ("%d\n", num);
	return 0;
}
````


---

## 作者：EDqwq (赞：0)

模拟赛题。

$m$ 只有 3000 ，所以 $l,r$ 最多只有6000种，这意味着什么？

意味着我们可以枚举。枚举左端点，然后在左端点范围内（也就是比枚举的小）的边可以选入，然后在这个基础上，右端点从大到小选择（满足区间最大），然后并茶几判断起点终点是否相连。

如果相连更新答案，取最大的即可

发现了吗，这个东西很类似 kruskal 算法。

```cpp
#include<bits/stdc++.h>

#define int long long
#define mem(x,y) memset(x,y,sizeof(x))
#define frein freopen("in.in","r",stdin)
#define freout freopen("out.out","w",stdout)

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

struct node{
	int x;
	int y;
	int l;
	int r;
}e[1000010];

struct nodee{
	int l;
	int r;
}a[1000010];

int cnt,head[1000010];
int n,m;
int tot;
int b[1000010];
int tt;
int ll[1000010],rr[1000010];
int nowl,nowr;
int ans,ansl,ansr;
int pre[1000010];

bool cmp(node x,node y){
	if(x.r != y.r)return x.r > y.r;
	else return x.l < y.l;
}

bool cmpp(nodee x,nodee y){
	if(x.l != y.l)return x.l < y.l;
	else return x.r < y.r;
}

void init(){
	for(int i = 1;i <= n;i ++)pre[i] = i;
}

int find(int x){
	if(pre[x] == x)return x;
	return pre[x] = find(pre[x]);
}

signed main(){
	cin>>n>>m;
	for(int i = 1;i <= m;i ++){
		int x,y,l,r;
		x = read(),y = read(),l = read(),r = read();
		e[i].x = x,e[i].y = y,e[i].l = l,e[i].r = r;
		b[++ tt] = l;
		b[++ tt] = r;
		a[i].l = l;
		a[i].r = r;
	}
	sort(e + 1,e + m + 1,cmp);
	sort(a + 1,a + m + 1,cmpp);
	for(int i = 1;i <= m;i ++){
		nowl = a[i].l;
		nowr = 2147483647;
		init();
		for(int j = 1;j <= m;j ++){
			if(e[j].l <= nowl){
				int xx = find(e[j].x);
				int yy = find(e[j].y);
				if(xx != yy){
					pre[xx] = yy;
					nowr = min(nowr,e[j].r);
					if(find(1) == find(n))break;
				}
			}
		}
		if(find(1) == find(n)){
			if(ans < nowr - nowl + 1){
				ansl = nowl;
				ansr = nowr;
				ans = nowr - nowl + 1;
			}
		}
	}
	if(ans)cout<<ans<<endl;
	else puts("Nice work, Dima!");
}
```

---

## 作者：xfrvq (赞：0)

[$\texttt{CF366D Dima and Trap Graph}$](/problem/CF366D)

[$\texttt{My blog}$](/blog/368107/solution-cf366d)

---

首先考虑暴力。由于边只有 $3\times10^3$ 条，而答案的 $l,r$ 一定出自其中。可以考虑枚举 $l,r$，然后使用并查集加边，如果可行，则 `find(1)=find(n)`。

我们可以使用二分来优化方案。枚举 $l$，二分 $r$，然后二分 $\rm check$ 的时候把所有 `e.l<=l` 且 `e.r>=r` 的边连接的点都用并查集 $\rm merge$ 一下，最后如果 $1$ 与 $n$ 是联通的，二分中 `L=mid+1`，否则 `R=mid`。

别忘了最后得到的 $l,r$ 相同时输出 `Nice work, Dima!`。

## Code

```cpp
#include<stdio.h>
#include<algorithm>

#ifndef USE_SYS_IO
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#endif

inline int read(){
    register int x = 0;
    register char c = getchar();
    for(;c < '0' || c > '9';c = getchar());
    for(;c >= '0' && c <= '9';c = getchar())
        x = x * 10 + (c ^ '0');
    return x;
}

const int maxn = 1e3 + 1;
const int maxm = 3e3 + 1;

int n,m;

int fa[maxn];

inline int fnd(register int x){
	return x == fa[x] ? x : fa[x] = fnd(fa[x]);
}

inline void merge(register int x,register int y){
	fa[fnd(x)] = fnd(y);
}

struct edge{
	int u,v,l,r;
	bool operator<(const edge& E) const {
		return l != E.l ? l < E.l : r < E.r;
	}
} e[maxm];

bool chk(int l,int r){
	for(int i = 1;i <= n;++i) fa[i] = i;
	for(int i = 1;i <= m;++i){
		if(e[i].l <= l){
			if(e[i].r >= r) merge(e[i].u,e[i].v);
		} else break;
	}
	return fnd(1) == fnd(n);
}
  
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;++i)
		scanf("%d%d%d%d",&e[i].u,&e[i].v,&e[i].l,&e[i].r);
	std::sort(e + 1,e + m + 1);
	int ans = 0;
	for(int i = 1;i <= m;++i){
		int L = e[i].l;
		int l = 0,r = 3e6,R;
		while(l < r){
			int mid = l + r >> 1;
			if(chk(L,mid)) l = mid + 1;
			else r = mid;
		}
		R = l - 1;
		if(R - L + 1 > ans) ans = R - L + 1;
	}
	if(ans == 0) printf("Nice work, Dima!");
	else printf("%d",ans);
    return 0;
}
```

---

## 作者：mango09 (赞：0)

### $\text{Description}$

[CF366D Dima and Trap Graph](https://www.luogu.com.cn/problem/CF366D)

在一张无向图上有 $N$ 个点和 $M$ 条边，每条边连接着点 $a$ 和点 $b$，有无数个人编号为 $1,2,\dots,+\infty$。通过某条边是要一定的条件的，对于每条边，有两个值 $l$ 和 $r$，表示该条边只允许编号在 $[l,r]$ 区间内的人通过，从 $1$ 号点到达 $N$ 号点，请求出最多有多少人可以通过，并求出这些人的编号（若有多组解取字典序最小的一组 )

- 可能有重边和自环。
- 如果没有人能通过只要输出 `Nice work, Dima!` 就可以了。
- 对于 $30\%$ 的数据，$1\le N,M\le10$；
- 对于 $100\%$ 的数据，$2\le N\le1000,0\le M\le3000,1\le a,b\le N,1\le l\le r\le10^6$。

### $\text{Solution}$

有两种思路（注意字典序最小的判断）：

#### $1.$ 最长路

遍历每一条边，对于第 $i$ 条边，选取边权 $\ge l_i$ 的边，从 $1$ 到 $N$ 跑最长路，让 $r$ 最大，在 $l$ 固定的情况下，肯定是 $r$ 越大越好。

时间复杂度 $\mathcal{O}(M\cdot M\log N)=\mathcal{O}(M^2\log N)$。

#### $2.$ 并查集

同样是遍历每一条边 $i$，将所有满足 $l_j\le l_i$ 的 $j$，都把 $a_j$ 和 $b_j$ 并入一个集合。

那么最终的 $l$ 一定是 $l_i$，所以把所有的 $r_i$ 取个 $\min$ 作为最终的 $r$，当点 $1$ 和点 $N$ 在同一个集合内说明可以尝试去更新答案。

因为是并查集实现，结合路径压缩和按秩合并可以做到 $\mathcal{O}(M^2\alpha(N))$，不过因为 $N\le1000$ 所以优化不大，主要优化在于常数（

时间复杂度 $\mathcal{O}(M^2\alpha(N))$。

### $\text{Code}$

#### $1.$

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 1005;
const int MAXM = 3005;
const int INF = 0x3f3f3f3f;

int cnt;
int head[MAXN];

struct edge
{
	int to, l, r, nxt;
}e[MAXM << 1];

void add(int u, int v, int l, int r)
{
	e[++cnt] = edge{v, l, r, head[u]};
	head[u] = cnt;
}

int dis[MAXN];
bool vis[MAXN];

struct node
{
	int u, r;
	bool operator <(const node &x)const
	{
		if (x.r == r)
		{
			return x.u < u;
		}
		return x.r > r;
	}
};

void init()
{
	memset(dis, -INF, sizeof(dis));
	memset(vis, false, sizeof(vis));
}

void dijkstra(int l)
{
	init();
	dis[1] = INF;
	priority_queue<node> pq;
	pq.push(node{1, dis[1]});
	while (!pq.empty())
	{
		int u = pq.top().u;
		pq.pop();
		if (vis[u])
		{
			continue;
		}
		vis[u] = true;
		for (int i = head[u]; i; i = e[i].nxt)
		{
			if (e[i].l > l) //取在区间内的
			{
				continue;
			}
			int v = e[i].to;
			if (dis[v] < min(dis[u], e[i].r)) //r要取min
			{
				dis[v] = min(dis[u], e[i].r);
				pq.push(node{v, dis[v]});
			}
		}
	}
}

int l[MAXM], r[MAXM];

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d%d%d", &u, &v, l + i, r + i);
		add(u, v, l[i], r[i]);
		add(v, u, l[i], r[i]);
	}
	int ansk = 0, ansl = 0, ansr = 0;
	for (int i = 1; i <= m; i++)
	{
		dijkstra(l[i]);
		int res = dis[n] - l[i] + 1;
		if (ansk < res || (ansk == res && ansl > l[i]))
		{
			ansk = res;
			ansl = l[i];
			ansr = dis[n];
		}
	}
	if (ansk)
	{
		printf("%d\n", ansk);
		for (int i = ansl; i <= ansr; i++)
		{
			printf("%d ", i);
		}
	}
	else
	{
		puts("Nice work, Dima!");
	}
	return 0;
}
```

#### $2.$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1005;
const int MAXM = 3005;
const int INF = 0x3f3f3f3f;

struct edge
{
	int u, v, l, r;
}e[MAXM];

bool cmp(edge x, edge y)
{
	if (x.r == y.r)
	{
		return x.l < y.l;
	}
	return x.r > y.r;
}

int n, m, r, ansk, ansl, ansr;
int fa[MAXN], siz[MAXN];

void init()
{
	for (int i = 1; i <= n; i++)
	{
		fa[i] = i;
		siz[i] = 1;
	}
}

int find(int x)
{
	if (x == fa[x])
	{
		return x;
	}
	return fa[x] = find(fa[x]); //路径压缩
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].l, &e[i].r);
	}
	sort(e + 1, e + m + 1, cmp);
	for (int i = 1; i <= m; i++)
	{
		init();
		r = INF;
		for (int j = 1; j <= m; j++)
		{
			if (e[j].l <= e[i].l)
			{
				int x = find(e[j].u), y = find(e[j].v);
				if (x != y)
				{
					if (siz[x] > siz[y]) //按秩合并
					{
						fa[y] = x;
						siz[x] += siz[y];
					}
					else
					{
						fa[x] = y;
						siz[y] += siz[x];
					}
					r = min(r, e[j].r);
					if (find(1) == find(n))
					{
						break;
					}
				}
			}
		}
		if (find(1) == find(n) && (ansk < r - e[i].l + 1 || (ansk == r - e[i].l + 1 && ansl > e[i].l)))
		{
			ansk = r - e[i].l + 1;
			ansl = e[i].l;
			ansr = r;
		}
	}
	if (ansk)
	{
		printf("%d\n", ansk);
		for (int i = ansl; i <= ansr; i++)
		{
			printf("%d ", i);
		}
	}
	else
	{
		puts("0");
	}
	return 0;
}
```

---

