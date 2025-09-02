# Sonya and Ice Cream

## 题目描述

Sonya 非常喜欢冰淇淋。即使在编程比赛期间，她也会吃冰淇淋。因此，她决定要开设属于自己的冰淇淋店。

Sonya 住在一个有 $n$ 个路口和 $n-1$ 条街道的城市。所有街道都是双向的，并连接两个路口。可以通过一条或多条街道从任意一个路口到达另一个路口。市政厅只允许在路口开设商店，不能在街道中间开店。

Sonya 有恰好 $k$ 个值得信任的朋友。如果她开设一家商店，必须由她的一个朋友在那里工作，防止有人不付钱就吃冰淇淋。由于 Sonya 不想错过重要的比赛，她本人不会在商店工作。

Sonya 希望她所有的冰淇淋店都位于一条长度为 $r$（$1 \le r \le k$）的简单路径上，即位于不同的路口 $f_1, f_2, \dots, f_r$，并且对于每个 $i$ 从 $1$ 到 $r-1$，$f_i$ 和 $f_{i+1}$ 之间有一条街道相连。

Sonya 也很关心潜在的顾客，因此她还希望最小化所有路口到最近冰淇淋店的最大距离。两个路口 $a$ 和 $b$ 之间的距离等于从 $a$ 到 $b$ 需要经过的所有街道长度之和。因此，Sonya 希望最小化

$$
\max_{a} \min_{1 \le i \le r} d_{a,f_i}
$$

其中 $a$ 取所有 $n$ 个路口的值，$f_i$ 表示第 $i$ 家 Sonya 的商店所在的路口，$d_{x,y}$ 表示路口 $x$ 和 $y$ 之间的距离。

Sonya 不确定自己能否找到最优的商店位置，因此她请求你帮她选择不超过 $k$ 家商店，使它们位于一条简单路径上，并且所有路口到最近商店的最大距离最小。

## 说明/提示

在第一个样例中，你可以选择路径 2-4，因此答案为 4。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1004E/8c2f15a4fd52f01b9e20de5f6f72a725ba32bbc7.png)第一个样例。

在第二个样例中，你可以选择路径 4-1-2，因此答案为 7。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1004E/473187d2fc5546701ca91ad8cfaa45bd65002a47.png)第二个样例。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 2
1 2 3
2 3 4
4 5 2
4 6 3
2 4 6
```

### 输出

```
4
```

## 样例 #2

### 输入

```
10 3
1 2 5
5 7 2
3 2 6
10 6 3
3 8 1
6 4 2
4 1 6
6 9 4
5 2 5
```

### 输出

```
7
```

# 题解

## 作者：Stay_Hungry (赞：7)

以下讲解$O(n)$做法    
如果我们首先找到了这棵树的直径上的点，那么选择的路径其中一点肯定在树的直径上   
那第二个点在哪里呢？接下来便需要开始论证   
![](https://cdn.luogu.com.cn/upload/image_hosting/gg7hx01d.png)
综上所得，选择的两点都在树的直径上，而答案就是$max(d(b, f), d(a, e))$，直接扫一遍滑动窗口求最小值， 时间复杂度$O(n)$

---

## 作者：yimuhua (赞：4)

显然最优解一定在直径上，且尽量长。

#### 证明：

若存在一个最大值更小的分支，这个分支的大小一定不比解在直径上时小。同理，我们想让这条路径尽量长。

于是尺取直径上的一条链，其到直径上所有点的最长距离一定为其到直径两端点的距离的较大值。对于不在这条直径上的点可以直接搜索，它只会被它的祖先中离它最近的、在直径上的点搜索，于是时间复杂度为 $O(n)$。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node {
    int x, w;
};
bool vis[100005];
vector<node> v[100005];
int n, s, p, ans = 1e9, fa[100005], dis[100005], dep[100005];
void dfs(int x, int fa) {
    ::fa[x] = fa, dep[x] = dep[fa] + 1;
    if(dis[x] > dis[p])
        p = x;
    for(auto i : v[x])
        if(i.x != fa && !vis[i.x])
            dis[i.x] = dis[x] + i.w, dfs(i.x, x);
    return;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> s;
    for(int i = 1, x, y, w; i < n; i++)
        cin >> x >> y >> w, v[x].push_back((node){y, w}), v[y].push_back((node){x, w});
    dfs(dis[1] = 1, 0), dis[p] = 0, dfs(p, 0);
    for(int i = p, j = p, x; i; i = fa[i]) {
        while(dep[j] - dep[i] >= s)
            j = fa[j];
        x = max(dis[p] - dis[j], dis[i]), ans = min(ans, x);
    }
    for(int i = p; i; i = fa[i])
        vis[i] = 1;
    for(int i = p; i; i = fa[i])
        dis[p = i] = 0, dfs(i, fa[i]);
    for(int i = 1; i <= n; i++)
        ans = max(ans, dis[i]);
    cout << ans;
    return 0;
}
```


---

## 作者：Sangber (赞：3)

### 题目描述
给定一个 $N$ 个点的树，要选出一条所含点的个数不超过 $K$ 的一条路径，使得路径外的点到这条路径的距离的最大值最小。  
数据范围：$1\le K \le N \le 10^5$  

### 解题思路
这道题我有两种方法。

#### 方法一
我们考虑一个性质：**选出来的链一定会是直径的一部分**。  
不然就肯定会存在可能更新最大值的一个分支，而且这个分支的大小一定会不比路径包含在直径上时小。  
同样的道理，我们发现这条路径在直径上越长越好。  
那么我们不妨先把直径抠出来，记作一个序列，那么这颗树就可以想象成一条链挂了很多子树。  
我们dfs出每一个直径上的点，它下面的子树的以根为源点的最长路，然后用 $\text{ST}$ 表维护一下它的区间最大值，再加上一点前缀和，然后在直径上移动这个序列，更新答案就好了。  
复杂度是 $O(n \log n)$ 的。  

#### 方法二
考虑一种贪心的思想。  
我们考虑不断删掉叶子，每次选择距离目标形态最近的叶子删掉，并且判断一下他的父亲是不是成了新的叶子，并将他的答案向父亲合并。  
关于正确性：  
1. 删成链之后就会继续删链的端点，这肯定没问题。  
2. 这里的最近类似与上文中的“直径上的点的子树的以根为源点的最长路”，所以是对的。  
3. 由于选择顺序的规定，所以更新父亲的一定是最后被选的一个儿子，因为它的关键字最大，所以只需要在父亲变叶子时更新。  

知道了原理后，我们可以用 `set` 存边，方便进行删边操作，用 `priority_queue` 来维护所有的叶子，然后直接模拟这个过程就好了。  

### 细节注意事项
+ 用第一种方法会稍微有一点难调。  
+ 用第二种方法就可能会出现 `STL` 的使用出错等问题。  

### 参考代码
这是方法一的代码，由于我自己没(lan)有(de)打，所以这里放的是 $\text{\color{black}{M}\color{red}{\_sea}}$ 神仙的代码  

```cpp
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#define re register
using namespace std;

inline int read() {
    int X=0,w=1; char c=getchar();
    while (c<'0'||c>'9') { if (c=='-') w=-1; c=getchar(); }
    while (c>='0'&&c<='9') X=X*10+c-'0',c=getchar();
    return X*w;
}

const int N=100000+10;

int n,k;

struct edge { int v,w,nxt; } e[N<<1];
int head[N];
inline void addEdge(int u,int v,int w) {
    static int cnt=0;
    e[++cnt]=(edge){v,w,head[u]},head[u]=cnt;
}

int rt1,rt2;
int dis[N],fa[N];
inline void dfs1(int u,int f) {
    if (dis[u]>dis[rt1]) rt1=u;
    for (re int i=head[u];i;i=e[i].nxt)
        if (e[i].v!=f) dis[e[i].v]=dis[u]+e[i].w,dfs1(e[i].v,u);
}
inline void dfs2(int u,int f) {
    fa[u]=f;
    if (dis[u]>dis[rt2]) rt2=u;
    for (re int i=head[u];i;i=e[i].nxt)
        if (e[i].v!=f) dis[e[i].v]=dis[u]+e[i].w,dfs2(e[i].v,u);
}

int cnt=0,lend=0;
int in[N],maxdis[N],w[N];
int lg[N],st[17][N],sum[N];
inline void dfs3(int u,int f) {
    for (re int i=head[u];i;i=e[i].nxt) {
        int v=e[i].v; if (v==f) continue;
        w[v]=e[i].w,dfs3(v,u);
        if (!in[v]) maxdis[u]=max(maxdis[u],maxdis[v]+e[i].w);
    }
}
inline void init_diameter() {
    for (re int i=rt2;i;i=fa[i]) in[i]=1,++cnt;
    dfs3(rt1,0);
    for (re int i=2;i<=n;++i) lg[i]=lg[i>>1]+1;
    for (re int i=rt2,j=1;i;i=fa[i],++j) st[0][j]=maxdis[i];
    for (re int i=1;i<17;++i)
        for (re int j=1;j+(1<<i)-1<=cnt;++j)
            st[i][j]=max(st[i-1][j],st[i-1][j+(1<<(i-1))]);
    for (re int i=rt2,j=1;i;i=fa[i],++j) sum[j]=w[i],lend+=w[i];
    for (re int i=1;i<=cnt;++i) sum[i]+=sum[i-1];
}
inline int query(int l,int r) {
    int t=lg[r-l+1];
    return max(st[t][l],st[t][r-(1<<t)+1]);
}

int main() {
    n=read(),k=read();
    if (n==1) { puts("0"); return 0; }
    for (re int i=1;i<n;++i) {
        int u=read(),v=read(),w=read();
        addEdge(u,v,w),addEdge(v,u,w);
    }
    dfs1(1,0),dfs2(rt1,0);
    init_diameter();
    if (k>cnt) printf("%d\n",query(1,cnt));
    else {
        int ans=2e9;
        for (re int i=1;i+k-1<=cnt;++i) {
            int tmp=max(sum[i-1],lend-sum[i+k-2]);
            ans=min(ans,max(tmp,query(i,i+k-1)));
        }
        printf("%d\n",ans);
    }
    return 0;
}
```  

下面是方法二的代码，我自己敲的。  

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <ctime>
#include <queue>
#include <set>
#define rg register
using namespace std;
template < typename T > inline void read(T& s) {
 	s = 0; int f = 0; char c = getchar();
 	while (!isdigit(c)) f |= (c == '-'), c = getchar();
 	while (isdigit(c)) s = s * 10 + (c ^ 48), c = getchar();
 	s = f ? -s : s;
}

const int _ = 100000 + 10;

int n, k, ans;
struct node{ int u, w; };
inline bool operator < (const node& x, const node& y) { return x.w > y.w; }
priority_queue < node > Q;
set < pair < int, int > > s[_];

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
#endif
	read(n), read(k);
	for (rg int u, v, d, i = 1; i < n; ++i) {
		read(u), read(v), read(d);
		s[u].insert(make_pair(v, d));
		s[v].insert(make_pair(u, d));
	}
	for (rg int i = 1; i <= n; ++i)
		if (s[i].size() == 1) Q.push((node) { i, (*s[i].begin()).second });
	while (Q.size() > 2 || k < n) {
		node x = Q.top(); Q.pop(), --n, ans = x.w;
		int u = x.u, v = (*s[u].begin()).first;
		s[v].erase(s[v].lower_bound(make_pair(u, 0)));
		if (s[v].size() == 1) Q.push((node) { v, ans + (*s[v].begin()).second });
	}
	printf("%d\n", ans);
	return 0;
}

```  

**完结撒花 $qwq$**

---

## 作者：sinsop90 (赞：3)

做完后感觉其他题解说取直径，感觉非常有道理啊，感觉我做的可能本质是一样的！但毕竟是不一样的做法，还是来写一篇题解。

考虑二分答案，判断一个答案 $X$ 是否可行。

在每一个节点 $u$ 判断是否存在一条满足条件的路径的顶点为 $u$。

这是个经典 $dp$，稍微复杂了一点，但也是记录 $dp_{u, 1}$ 代表从子树直接上升到 $u$, 且子树内满足要求的所花点数的最小值。$dp_{u, 2}$ 代表顶点为 $u$ 的满足要求的路径的点数最小值。

考虑什么时候存在合法路径，那么 $u$ 子树外离 $u$ 最远距离不超过 $X$, 且子树内可以找到一条满足要求的路径。前者可以换根预处理。

实现上可以比我写的好很多，而且我觉得我实现多少有点问题，只是没卡掉。

其他题解聪明是真的，但自己实现粪是真实，完全没有冷静有效的思考，导致输了这局和 zltqwq 的 duel，气死我了！

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 3e5 + 5, INF = 2e9;
int head[maxn], g[maxn][3], mxdep[maxn], h[maxn], tot, X, flag, K, n, res;
struct node {
	int v, pre, w;
}e[maxn << 1];
void add(int u, int v, int w) {
	e[++ tot].v = v;
	e[tot].w = w;
	e[tot].pre = head[u];
	head[u] = tot;
}
void gett(int now, int f) {
	vector<int> vec;
	for(int i = head[now];i;i = e[i].pre) {
		int v = e[i].v;
		if(v == f) continue;
		gett(v, now);
		if(mxdep[v] + e[i].w <= X) continue;
		vec.push_back(v);
	}
	if(vec.size() == 0) {
		g[now][0] = 0;
		g[now][1] = g[now][2] = 1;
	}
	else if(vec.size() == 1) {
		g[now][1] = g[vec[0]][1] + 1;
	}
	else if(vec.size() == 2) {
		g[now][2] = g[vec[0]][1] + 1 + g[vec[1]][1];
	}
	if(g[now][0] != INF && h[now] <= X) flag = 1;
	if(g[now][1] <= K && h[now] <= X) flag = 1;
	if(g[now][2] <= K && h[now] <= X) flag = 1;
	vector<int>().swap(vec);
}
void dfs1(int now, int f) {
	for(int i = head[now];i;i = e[i].pre) {
		int v = e[i].v;
		if(v == f) continue;
		dfs1(v, now);
		mxdep[now] = max(mxdep[now], mxdep[v] + e[i].w);
	}
}
void dfs2(int now, int f, int p) {
	h[now] = p;
	int t1 = 0, t2 = 0;
	for(int i = head[now];i;i = e[i].pre) {
		int v = e[i].v;
		if(v == f) continue;
		if(mxdep[v] + e[i].w > t1) t2 = t1, t1 = mxdep[v] + e[i].w;
		else t2 = max(t2, mxdep[v] + e[i].w);
	}
	for(int i = head[now];i;i = e[i].pre) {
		int v = e[i].v;
		if(v == f) continue;
		if(mxdep[v] + e[i].w == t1) dfs2(v, now, max(p, t2) + e[i].w);
		else dfs2(v, now, max(p, t1) + e[i].w);
	}
}
bool check(int x) {
	for(int i = 1;i <= n;i++) g[i][0] = g[i][1] = g[i][2] = INF;
	flag = 0;
	X = x;
	gett(1, 0);
	return flag;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> K;
	for(int i = 1, u, v, w;i < n;i++) {
		cin >> u >> v >> w;
		add(u, v, w), add(v, u, w);
	}
	dfs1(1, 0);
	dfs2(1, 0, 0);
	int l = 0, r = INF;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(mid)) r = mid - 1, res = mid;
		else l = mid + 1;
	}
	cout << res << '\n';
}
```


---

## 作者：520Enterprise (赞：1)

没人发现这个就是**树网的核**吗。。。~~普及组难度的题~~

先找出直径，在直径上每次都取k个点（显然点更多答案不会更差）

我们找的最小值肯定要么是**两端点到直径端点的贡献**，要么是**直径上的点的贡献**，前者显然可以预处理出。

而后者就是直径上一个点在不经过直径上其他的点的情况下所能到达的最远的点（其实就是它的子树里最远的点）。

# 为什么？
假如这个点A经过其他在直径上的点B到达了更远的点C，那么我们分两种情况进行讨论。

## 1

如果B在我们所选的路径上，那么显然由B出发到达C的距离更小。

## 2

如果B不在我们所选的路径上，那么C到B的距离一定不大于B到直径某端点的距离（直径的定义）。

## 综上，这两种错误的情况就会被我们过滤掉。

具体请看代码，不要直接Ctrl+C哦o(>﹏<)o

### By 520Enterprise

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=500010;
int n,k,cnt,head[maxn],dis[maxn],fa[maxn],ans=1e9,zhijing[maxn];
struct edge
{
    int to,next,quan;
}e[maxn<<1];
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
	if(ch=='-')
	    f=-1;
	ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
	x=(x<<1)+(x<<3)+(ch^48);
	ch=getchar();
    }
    return x*f;
}
inline void write(int a)
{
    if(a<0)
    {
	char a='-',b='1';
	putchar(a);
	putchar(b);
    }
    else
    {
	if(a>=10)
	    write(a/10);
	putchar(a%10+'0');
    	puts("520Enterprise");
    }
}
void add(int from,int to,int quan)
{
    e[++cnt]=(edge){to,head[from],quan};
    head[from]=cnt;
}
void dfs(int now,int father)
{
    for(int i=head[now];i;i=e[i].next)
    {
	int to=e[i].to;
	if(to==father||zhijing[to])
	    continue;
	dis[to]=dis[now]+e[i].quan;
	fa[to]=now;
	dfs(to,now);
    }
}
int main()
{
    n=read(),k=read();
    for(int i=1;i<n;i++)
    {
	int u=read(),v=read(),w=read();
	add(u,v,w),add(v,u,w);
    }
    int qidian=1,zhongdian=1;
    dis[qidian]=0;
    dfs(qidian,0);
    for(int i=1;i<=n;i++)
	if(dis[i]>dis[qidian])
	    qidian=i;
    dis[qidian]=0,fa[qidian]=0;
    dfs(qidian,0);
    for(int i=1;i<=n;i++)
	if(dis[i]>dis[zhongdian])
	    zhongdian=i;
    int j=zhongdian;
    for(int i=1;i<k&&fa[j];i++)
	j=fa[j];
    for(int i=zhongdian;i&&j;i=fa[i])
    {
	ans=min(ans,max(dis[j],dis[zhongdian]-dis[i]));
	j=fa[j];
    }
    for(int i=zhongdian;i;i=fa[i])
	zhijing[i]=1;
    for(int i=zhongdian;i;i=fa[i])
	dis[i]=0,dfs(i,0);
    for(int i=1;i<=n;i++)
	ans=max(ans,dis[i]);
    write(ans);
    return 0;
}
```

---

## 作者：ljk123 (赞：1)

## Sonya and Ice Cream题解
这道题是一位一遍A了快餐店的巨佬推荐给我的，说快餐店巨简单，不过还是先做一下简化版，就是这道题（~~照顾我太弱了~~）

好了回到这一题，

首先，这条路径一定在直径上(若有一段不是直径，一定比直径的长)


~~巨佬说随便画图理解一下就行了~~

然后我们可以二分答案x(最小的最大值)，

贪心找到离直径一端距离<=x的最远点(倍增)，

情况大概如下图：
![](https://images.cnblogs.com/cnblogs_com/ljk123-de-bo-ke/1441553/o_2019-10-16%2017-15-41%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)

其中子树挂坠，将直径看为序列用ST表预处理

左端的直径，因为从左端跑起，所以一定小于x，

右端的直径，用前缀和维护序列距离，

最后具体实现细节在代码里：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+6;
int n,k,t1,t2,t3,fr,cnt=0,head[N],v[N],f[N][21],g[N][21];
int maxp=0,maxt=0,maxdis[N],a[N],sum[N],len,deep,w[N],h[N][21];
struct edge{int nxt,to,w;}e[N<<1];
inline void add(int u,int v,int w){e[++cnt].nxt=head[u],e[cnt].to=v,e[cnt].w=w,head[u]=cnt;}
inline int read(){
   int T=0,F=1; char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-') F=-1; ch=getchar();}
   while(ch>='0'&&ch<='9') T=(T<<3)+(T<<1)+(ch-48),ch=getchar();
   return F*T; 
}
void dfs(int x,int fa,int w){
    sum[x]=w;
    for(int i=head[x];i;i=e[i].nxt) if(e[i].to!=fa) dfs(e[i].to,x,w+e[i].w);
    if(maxp<w) maxp=w,maxt=x;
}
void dfs2(int x,int fa,int d){
    maxdis[x]=0,f[x][0]=fa;
    for(int i=1;i<=20;++i) f[x][i]=f[f[x][i-1]][i-1],g[x][i]=g[x][i-1]+g[f[x][i-1]][i-1];
    for(int i=head[x];i;i=e[i].nxt) if(e[i].to!=fa) g[e[i].to][0]=e[i].w,dfs2(e[i].to,x,d+1),v[x]|=v[e[i].to],maxdis[x]=(!v[e[i].to]?max(maxdis[x],maxdis[e[i].to]+e[i].w):maxdis[x]);
    if(v[x]) a[d]=x,deep=max(deep,d);
}
bool check(int x){
    t1=maxt,t2=x,cnt=0;
    for(int i=20;i>=0;--i) if(t2>=g[t1][i]) t2-=g[t1][i],t1=f[t1][i],cnt+=(1<<i);
    //贪心求出离直径深度为deep的点距离<=x的最远点，看一看它到后面的k-1个点的路径上挂坠子树的最大距离，和路径上最后一个点到直径另一端(深度为1)的距离是否小于等于x
    t3=max(deep-cnt-k+1,1);//t3为路径上第k个点
    return max(sum[a[t3]],w[t3])<=x;
}
int ef(int l,int r){
    if(l==r) return l;
    int mid=l+r>>1;
    if(check(mid)) return ef(l,mid);
    return ef(mid+1,r);
}
int main(){
   n=read(),k=read();
   for(int i=1;i<n;++i) t1=read(),t2=read(),t3=read(),add(t1,t2,t3),add(t2,t1,t3);
   dfs(1,0,0);
   maxp=0,fr=maxt,maxt=0,dfs(fr,0,0);
   //求直径，从fr到maxt，长度为maxp,求出sum数组代表直径上深度为i的点到深度为1的点(直径端点)的距离
   v[maxt]=1,deep=0,dfs2(fr,0,1);
   //第二遍搜直径上的点，看成序列存在a里，编号即为深度，预处理倍增数组
   for(int i=deep;i>=1;--i) h[i][0]=maxdis[a[i]];
   for(int i=1;i<=20;++i) for(int j=1;j+(1<<i)-1<=deep;++j) h[j][i]=max(h[j][i-1],h[j+(1<<(i-1))][i-1]);
   for(int i=1;i<=deep;++i) len=(int)log2(min(deep-i+1,k)),w[i]=max(h[i][len],h[i+k-(1<<len)][len]);
   //ST表求直径上挂坠的子树的最大距离
   printf("%d\n",ef(0,1e9));
   //二分求解
   return 0;
}
```
最后我发现似乎可以在二分里直接$O(n)$扫一遍不要预处理(某位巨佬坑我),

我苦心追求的$O((log n)^{2})$的复杂度也因为预处理变成$O(n log n)$了

WuWuWu~~

~~这个故事告诉我们，千万不要追求优秀时间复杂度啊~~

附简单代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+6;
int n,k,t1,t2,t3,fr,cnt=0,head[N],v[N];
int maxp=0,maxt=0,maxdis[N],a[N],sum[N],deep;
struct edge{int nxt,to,w;}e[N<<1];
inline void add(int u,int v,int w){e[++cnt].nxt=head[u],e[cnt].to=v,e[cnt].w=w,head[u]=cnt;}
inline int read(){
   int T=0,F=1; char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-') F=-1; ch=getchar();}
   while(ch>='0'&&ch<='9') T=(T<<3)+(T<<1)+(ch-48),ch=getchar();
   return F*T; 
}
void dfs(int x,int fa,int w){
    sum[x]=w;
    for(int i=head[x];i;i=e[i].nxt) if(e[i].to!=fa) dfs(e[i].to,x,w+e[i].w);
    if(maxp<w) maxp=w,maxt=x;
}
void dfs2(int x,int fa,int d){
    maxdis[x]=0;
    for(int i=head[x];i;i=e[i].nxt) if(e[i].to!=fa) dfs2(e[i].to,x,d+1),v[x]|=v[e[i].to],maxdis[x]=(!v[e[i].to]?max(maxdis[x],maxdis[e[i].to]+e[i].w):maxdis[x]);
    if(v[x]) a[d]=x,deep=max(deep,d);
}
bool check(int x){
    t1=1,t3=0,t2=a[1];
    for(int i=deep;i>=1;--i) if(sum[a[deep]]-sum[a[i]]>x){t1=i+1; break;}
    for(int i=t1;i>=max(t1-k+1,1);--i) t3=max(maxdis[a[i]],t3),t2=a[i];
    return max(sum[t2],t3)<=x;
}
int ef(int l,int r){
    if(l==r) return l;
    int mid=l+r>>1;
    if(check(mid)) return ef(l,mid);
    return ef(mid+1,r);
}
int main(){
   n=read(),k=read();
   for(int i=1;i<n;++i) t1=read(),t2=read(),t3=read(),add(t1,t2,t3),add(t2,t1,t3);
   dfs(1,0,0);
   maxp=0,fr=maxt,maxt=0,dfs(fr,0,0);
   v[maxt]=1,deep=0,dfs2(fr,0,1);
   printf("%d\n",ef(0,1e9));
   return 0;
}
```

---

## 作者：Planetary_system (赞：0)

## 题面解释：
选择一条长度 $\le k$ 的链，求出除此以外的点到路径上的最大值的最小值。

## 思路分析：
首先，这条链一定在直径上。因为无论如何直径外的链分叉出去的长度一定 $\ge$ 直径上的链。那么就先找出直径，然后扫一遍求最小值。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node {int to,v;};
vector<node>g[N];
void add(int u,int v,int w) {
	g[u].push_back((node) {v,w});
	return;
}
int n,s,p,ans,f[N],l[N],d[N];
bool b[N];
void dfs(int x,int fa) {
	f[x]=fa,d[x]=d[fa]+1;
	if(l[x]>l[p])p=x;
	for(int i=0; i<g[x].size(); i++)
		if(g[x][i].to!=fa&&!b[g[x][i].to])
			l[g[x][i].to]=l[x]+g[x][i].v,dfs(g[x][i].to,x);
	return;
}
signed main() {
	scanf("%d%d",&n,&s);
	for(int i=1,u,v,w; i<n; i++)
		scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
	l[1]=1,dfs(1,0),l[p]=0,dfs(p,0);
	ans=INT_MAX;
	for(int i=p,j=p,x; i; i=f[i]) {
		while(d[j]-d[i]>=s)j=f[j];
		x=max(l[p]-l[j],l[i]),ans=min(ans,x);
	}
	for(int i=p; i; i=f[i])b[i]=1;
	for(int i=p; i; i=f[i])l[i]=0,p=i,dfs(i,f[i]);
	for(int i=1; i<=n; i++)ans=max(ans,l[i]);
	printf("%d",ans);
	return 0;
}
```

谢谢！

---

## 作者：_Cheems (赞：0)

不难猜到这条路径一定在直径上。

尝试归纳证明：如图，$dist(A,B)$ 为直径，答案路径目前在直径上，$D$ 是该路径的左端。现在让它往两端拓展一个点，讨论拓展后左端的最大值。

![](https://cdn.luogu.com.cn/upload/image_hosting/q0g6q4ma.png)

由直径性质知：假如选 $C$，那么最大值一定是 $dist(A,D)$。而选 $E$，则其最大值总是 $\le dist(A,D)$。

综上，拓展点选在直径上最优，于是这条路径会在直径上。

于是令 $dis_u$ 表示 $u$ 向非直径部分延伸出的最长链，$ls_u,rs_u$ 表示 $u$ 分别到直径两端的距离。路径 $dist(l, r)$ 的答案就是 $\max(\max(dis_i),ls_l,rs_r)$。$i$ 在该路径上。

又因为路径越长越好，因此其长度固定为 $k$，使用滑动窗口求 $\max(dis_i)$ 即可。

注意暴力算 $dis$ 不会超，因为刚好遍历整棵树，总的加起来就是 $O(n)$。

算法复杂度 $O(n)$。
### 代码
写的比较丑。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long 
const int N = 1e5 + 5;
int n, k, u, v, w, tot, head[N];
int s, t, ps, D[N], lst[N], diam[N], dis[N], dc, ls[N], rs[N], ans, mx;
int q[N], l, r;
int nonono, yfz;
struct edge{int v, w, nxt;} e[N << 1];

inline void add(int u, int v, int w) {e[++tot] = {v, w, head[u]}, head[u] = tot;}
inline void dfs(int u, int fa, int d, int &p){
	if(u == nonono) return ;
	D[u] = d, lst[u] = fa; if(d > ps) ps = d, p = u;
	for(int i = head[u]; i; i = e[i].nxt) if(e[i].v ^ fa) dfs(e[i].v, u, d + e[i].w, p);
}
signed main(){
	ans = 1145141919810;
	cin >> n >> k;
	for(int i = 1; i < n; ++i)
		scanf("%lld%lld%lld", &u, &v, &w), add(u, v, w), add(v, u, w);
	ps = 0, dfs(1, 0, 0, s), ps = 0, dfs(s, 0, 0, t);
	for(int i = t; i ^ s; i = lst[i]) diam[++dc] = i; diam[++dc] = s;
	reverse(diam + 1, diam + 1 + dc);
	for(int i = 1; i <= dc; ++i) ls[i] = D[diam[i]], rs[i] = D[t] - ls[i];
	l = 1, r = 0; 
	for(int i = 1; i <= dc; ++i){
		ps = 0, nonono = diam[i + 1], dfs(diam[i], diam[i - 1], 0, yfz);
		dis[i] = ps;
		while(l <= r && i - q[l] + 1 > k) ++l;
		while(l <= r && dis[i] >= dis[q[r]]) --r;
		q[++r] = i;
		ans = min(ans, max(max(ls[max(0ll, i - k) + 1], rs[i]), dis[q[l]]));
	}
	cout << ans;
	return 0;
}
```

---

