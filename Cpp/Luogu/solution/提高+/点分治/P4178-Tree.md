# Tree

## 题目描述

给定一棵 $n$ 个节点的树，每条边有边权，求出树上两点距离小于等于 $k$ 的点对数量。  

## 说明/提示

**数据规模与约定**

对于全部的测试点，保证：  

- $1\leq n\leq 4\times 10^4$。
- $1\leq u,v\leq n$。
- $0\leq w\leq 10^3$。
- $0\leq k\leq 2\times 10^4$。

## 样例 #1

### 输入

```
7
1 6 13 
6 3 9 
3 5 7 
4 1 3 
2 4 20 
4 7 2 
10```

### 输出

```
5```

# 题解

## 作者：Nemlit (赞：57)

## [原文地址](https://www.cnblogs.com/bcoier/p/10526832.html)

题面要求小于等于K的路径数目，我么很自然的想到[点分治(不会的就戳我)](https://tbr-blog.blog.luogu.org/solution-p3806)

这道题的统计答案与模板题不一样的地方是由等于K到小于等于K

那么我们可以把每一个子节点到当前根（重心）的距离排序，然后用类似双指针的方法来求小于等于K的边的数量

但是如果只是双指针统计的话，那么以下不合法的情况显然也会被算进答案：
![](https://cdn.luogu.com.cn/upload/pic/53974.png)

而我们需要的合法路径是长成这样的：
![](https://cdn.luogu.com.cn/upload/pic/53973.png)

所以我们需要减去上述不合法的路径，怎么减呢？

不难发现，对于所有不合法的路径，都是在当前跟的某一棵子树上的（没有跨越两个子树）

所以我们可以对当前跟节点的每一条边进行遍历，利用容斥的思想减去不合法的路径。

具体操作为：当遍历重心节点的每一个节点时，我们可以重新计算dis，然后把经过了从重心到新遍历的点的边两次的路径剪掉（就是上述不合法路径），最后统计答案即可
```
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define inf 123456789
il int read()
{
    re int x = 0, f = 1; re char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
#define rep(i, s, t) for(re int i = s; i <= t; ++ i)
#define drep(i, s, t) for(re int i = t; i >= s; -- i)
#define Next(i, u) for(re int i = head[u]; i; i = e[i].next)
#define mem(k, p) memset(k, p, sizeof(k))
#define maxn 40005
struct edge{int v, w, next;}e[maxn << 1];
int n, m, head[maxn], cnt, k, ans;
int dp[maxn], vis[maxn], sum, dis[maxn], rt, size[maxn], rev[maxn], tot;
il void add(int u, int v, int w)
{
    e[++ cnt] = (edge){v, w, head[u]}, head[u] = cnt;
    e[++ cnt] = (edge){u, w, head[v]}, head[v] = cnt;
}
il void getrt(int u, int fr)
{
    size[u] = 1, dp[u] = 0;
    Next(i, u)
    {
        int v = e[i].v;
        if(v == fr || vis[v]) continue;
        getrt(v, u);
        size[u] += size[v], dp[u] = max(dp[u], size[v]);
    }
    dp[u] = max(dp[u], sum - size[u]);
    if(dp[u] < dp[rt]) rt = u;
}
il void getdis(int u, int fr)
{
    rev[++ tot] = dis[u];
    Next(i, u)
    {
        int v = e[i].v;
        if(v == fr || vis[v]) continue;
        dis[v] = dis[u] + e[i].w;
        getdis(v, u);
    }
}
il int doit(int u, int w)
{
    tot = 0, dis[u] = w, getdis(u, 0);
    sort(rev + 1, rev + tot + 1);
    int l = 1, r = tot, ans = 0;
    while(l <= r) (rev[l] + rev[r] <= k) ? (ans += r - l, ++ l) : (-- r);
    return ans;
}
il void solve(int u)
{
    vis[u] = 1, ans += doit(u, 0);
    Next(i, u)
    {
        int v = e[i].v;
        if(vis[v]) continue;
        ans -= doit(v, e[i].w);
        sum = size[v], dp[0] = n, rt = 0;
        getrt(v, u), solve(rt);
    }
}
int main()
{
    n = read();
    rep(i, 1, n - 1){int u = read(), v = read(), w = read(); add(u, v, w);}
    k = read(), dp[0] = sum = n, getrt(1, 0), solve(rt);
    printf("%d", ans);
    return 0;
}
```

---

## 作者：Nickel_Angel (赞：35)

### 这里要介绍一下不依靠容斥来避免点分治统计答案重复的方法

（下面简略介绍一下点分治算法的主要思想QwQ）

这个算法主要采用分治的思想：首先在树中选取一个节点作为树根，树根将这棵树分成了几个子树，我们统计这棵树树根对答案的贡献后，我们再用同样的方法递归处理树根的每一颗子树。为了使树分治出的子树尽量平均，尽可能最小化递归层数，我们每次选取当前树的重心作为根节点递归下去，保证递归层数在 $O(\log n)$ 级别。

本题要统计的是树上的路径，考虑树上路径分为经过根节点和不经过根节点两类。

故可以考虑在分治过程中，统计当前子树经过根节点的路径中，长度小于等于 $k$ 的路径即可。而对于那些不经过当前根节点的路径，我们将它们交给当前子树的子树处理。具体一点来说，可以考虑将经过根节点设其两段点为 $(x, y)$ 的路径拆分成两部分：$(root, x)$ 和 $(root,y)$，我们可以通过树形 dp 预处理出子树内每个点到根的距离 $dis[u]$，这样我们只需统计子树内点对 $x, y$ 满足 $dis[x] + dis[y] \leq k$ 的点对数量即可。

但这样有可能会统计到一些不符合要求的点对，即 $x, y$ 可能都在 $root$ 的同一棵子树中（如下图，$x, y$ 两点均在 $root$ 的黄色子树中），若此时也满足 $dis[x] + dis[y] \leq k$，则该点对也会被计入答案。而 $x,y$ 组成的路径显然没有经过根节点，故这条路径实际上是不合法的。我们需要考虑如何去掉这些不合法的路径。

![](https://cdn.luogu.com.cn/upload/image_hosting/o6beyy07.png)



现在正题开始！qwq

看到大家一般都使用的是容斥法处理的以上情况，即每次在统计当前子树根节点的答案后，再减去根节点的各个子节点的子树中满足条件的点对。这样可能会导致常数较大， 故这里介绍另外一种常数较小但细节相对较多的方法：**染色法**。

考虑我们在一次分治一个子树过程中，我们已经找到了其根节点 $root$，每个节点到根节点的距离 $dis[u]$，每个节点在 $root$ 哪一个**子节点**的子树中 $color[u]$（特别的，$color[root] = root$） 。

有一个显然的性质是，一条路径经过 $root$，当且仅当路径的两端点 $u, v$ 满足 $color[u] \neq color[v]$ 。

我们先将树中的节点都取出放至数组中，按照它们到根节点的距离（$dis[u]$）从小到大排序。排完序后，我们只需用两个指针 $i,j$，一个从前开始，一个从后开始扫描数组就可以计算出 $dis[x] + dis[y] \leq k$ 的点对 $(x,y)$ 的个数，其中 $x, y$ 分别是指针 $i,j$ 所指向的节点。

具体计算过程如下：

1、将左指针从左向右扫描，对每个点计算合法的路径条数。不难发现，在左指针扫描过程中，恰好使得 $(x, y)$ 满足 $dis[x] + dis[y] \leq k$ 的右指针位置是单调递减的。

2、对于如何去掉不合法的点对，我们可以维护一个数组 $f[i]$ 表示在左右两指针中间的点（包括左右两指针指向的点）中，满足 $color[u] = i$ 的点的个数。不难发现只有在左右指针移动时，$f$ 数组中的值才会发生变化，故 $f$ 数组可以在指针移动时直接维护。

3、设当前左指针指向的点为 $x$，则 $x$ 对答案的贡献为**左右指针中间的点的个数**减去**在这些点中与 $x$ 在 $root$ 相同子树中点的个数（即满足 $color[u] = color[x]$ 的点 $u$ 的个数）**，即 $j - i + 1 - f[color[x]]$ 。

显然上述排序时间复杂度为 $O(n \log n)$，扫描统计答案时间复杂度为 $O(n)$ 。

综上，结合 master 定理，本算法时间复杂度为 $O(n \log^2 n)$ 。

Code：

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

namespace Primary
{

const int maxn = 40010;
int n, m, dp[maxn], size[maxn], dis[maxn], help[maxn];
int head[maxn], to[maxn << 1], next[maxn << 1], val[maxn << 1], tot = 1;
int root, sum, cnt, ans = 0, color[maxn], f[maxn];
bool vis[maxn];

bool cmp(int x, int y) {return dis[x] < dis[y];}

inline void add_edge(int u, int v, int w)
{
	to[++tot] = v;
	val[tot] = w;
	next[tot] = head[u];
	head[u] = tot;
}

void getroot(int u, int pre)//树形 dp 求树的重心
{
	size[u] = 1, dp[u] = 0;
	for (int c = head[u], v; c; c = next[c])
	{
		v = to[c];
		if (v == pre || vis[v]) continue;
		getroot(v, u);
		size[u] += size[v];
		dp[u] = max(dp[u], size[v]);
	}
	dp[u] = max(dp[u], sum - size[u]);
	if (dp[u] < dp[root]) root = u;
}

void getdis(int u, int pre)//对于当前子树预处理 dis, color, f 等数组
{
	help[++cnt] = u;//将当前子树节点编号均放入 help 数组中
	color[u] = color[pre], ++f[color[u]];
	for (int c = head[u], v; c; c = next[c])
	{
		v = to[c];
		if (v == pre || vis[v]) continue;
		dis[v] = dis[u] + val[c];
		getdis(v, u);
	}
}

inline int calc(int u)
{
	dis[u] = 0, cnt = 0;
	help[++cnt] = u;
	color[u] = u, f[color[u]] = 1;//注意预处理细节
	for (int c = head[u], v; c; c = next[c])
	{
		v = to[c];
		if (vis[v]) continue;
		color[v] = v, dis[v] = val[c];
		f[color[v]] = 0;//注意清空 f 数组
		getdis(v, v);
	}
	sort(help + 1, help + cnt + 1, cmp);//将节点按 dis 从小到大排序
	int i = 1, j = cnt, res = 0;
	while (i < j)
	{
		while (i < j && dis[help[i]] + dis[help[j]] <= m)
		{
			res += j - i + 1 - f[color[help[i]]];
			--f[color[help[i]]];//指针移动时直接维护 f 数组,有些类似于莫队
			++i;
		}
		--f[color[help[j]]];
		--j;
	}
	return res;
}

void solve(int u)//主要分治函数
{
	vis[u] = true;
	ans += calc(u);
	for (int c = head[u], v; c; c = next[c])
	{
		v = to[c];
		if (vis[v]) continue;
		sum = size[v] > size[u] ? n - size[u] : size[v];//计算下层递归子树大小
		root = 0, dp[0] = n;
		getroot(v, u);//每次求出重心后继续分治
		solve(root);
	}
}

void main()
{
	scanf("%d", &n);
	for (int i = 1, u, v, w; i < n; ++i)
	{
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w), add_edge(v, u, w);
	}
	scanf("%d", &m);
	dp[0] = sum = n;
	getroot(1, 0);
	solve(root);
	printf("%d\n", ans);
}

}

int main()
{
	Primary::main();
	return 0;
}
```

---

## 作者：stoorz (赞：21)


这道题是应该加强数据了。。。

~~当然如果这道题不打算做点分治模板题的话可以不用~~

$O(n\sqrt n\ \log \sqrt n)$分块在洛谷优秀的$O2$下过了。。。

*********

我们假设$1$为树根，$dfs$遍历一遍就可以得到每一个节点$x$到$1$的距离$dis[x]$。

然后可以暴力判断$dis$中有多少个数时小于等于$k$的。

每一个点作根跑一边，时间复杂度$O(n^2)$。

考虑优化上述算法。

考虑换根。我们把根从$1$转移到$x$时，所有$x$子树内的节点到$x$的距离减少了$dis(1,x)$，其他点到$x$距离增加了$dis(1,x)$。

用$dfs$序把每一棵子树的编号变为连续的，那么我们只要在原$dis$序列中进行区间加减操作就可以了维护出以$x$为根时，每一个点到$x$的距离。

那么我们现在需要求整个$dis$数组中有多少个是$\leq k$的，那么其实就是 [教主的魔法](https://www.luogu.com.cn/problem/P2801) 那道题了。

采用分块，区间加减容易实现，对于每一个块维护一个$Sort$数组，表示这个块的$dis$排序后的数组。那么每次修改时，$Sort$数组可以在$O(\sqrt n\ \log \sqrt n)$的时间复杂度内暴力维护。

注意如果要把一个块整体加减，那么直接在这个块的$add$数组中加减即可，在$dis$和$Sort$中都不需要修改。

询问时枚举每一个块$p$，在这个块的$Sort$中二分出第一个严格大于$k-add[p]$的数的位置$pos$，那么这个块中小于等于$k$的数字就有$pos-1$个。

这样就可以在$O(\sqrt n\ \log \sqrt n)$的时间复杂度内求出距离一个点有多少个点路径长度$\leq k$。总时间复杂度$O(n\sqrt n\ \log \sqrt n)$。常数极大。


```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N=40010,M=210;
int L[M],R[M],pos[N],add[M],Sort[M][M],head[N],dis[N],Dis[N],rk[N],dfn[N],size[N];
int n,m,T,tot,ans;

struct edge
{
	int next,to,dis;
}e[N*2];

void addedge(int from,int to,int d)
{
	e[++tot].to=to;
	e[tot].dis=d;
	e[tot].next=head[from];
	head[from]=tot;
}

void dfs1(int x,int fa)  //求出每一个点到点1的距离，同时求出dfs序
{
	dfn[x]=++tot; rk[tot]=x; size[x]=1;
	for (register int i=head[x];~i;i=e[i].next)
	{
		int v=e[i].to;
		if (v!=fa)
		{
			Dis[v]=Dis[x]+e[i].dis;
			dfs1(v,x);
			size[x]+=size[v];
		}
	}
}

void update(int l,int r,int val)  //分块区间加模板
{
	int p=pos[l],q=pos[r];
	if (q-p<=1)
	{
		for (register int i=l;i<=r;i++) dis[i]+=val;
		for (register int i=L[p];i<=R[q];i++) Sort[pos[i]][i-L[pos[i]]+1]=dis[i];  //整个块暴力修改
		sort(Sort[p]+1,Sort[p]+1+R[p]-L[p]+1);
		if (p!=q) sort(Sort[q]+1,Sort[q]+1+R[q]-L[q]+1);  //重新维护
		return;
	}
	for (register int i=l;i<=R[p];i++) dis[i]+=val;
	for (register int i=L[q];i<=r;i++) dis[i]+=val;
	for (register int i=L[p];i<=R[p];i++) Sort[p][i-L[p]+1]=dis[i];
	for (register int i=L[q];i<=R[q];i++) Sort[q][i-L[q]+1]=dis[i];  //两边暴力修
	sort(Sort[p]+1,Sort[p]+1+R[p]-L[p]+1);
	sort(Sort[q]+1,Sort[q]+1+R[q]-L[q]+1);
	for (register int i=p+1;i<q;i++)
		add[i]+=val;
}

void dfs2(int x,int fa)  //换根求答案
{
	for (register int i=1;i<=T;i++)
		ans+=upper_bound(Sort[i]+1,Sort[i]+1+R[i]-L[i]+1,m-add[i])-Sort[i]-1;
	for (register int i=head[x];~i;i=e[i].next)
	{
		int v=e[i].to;
		if (v!=fa)
		{
			update(dfn[v],dfn[v]+size[v]-1,-e[i].dis*2);
			update(1,n,e[i].dis);  //换根
			dfs2(v,x);
			update(dfn[v],dfn[v]+size[v]-1,e[i].dis*2);
			update(1,n,-e[i].dis);
		}
	}
}

int main()
{
	memset(head,-1,sizeof(head));
	scanf("%d",&n);
	for (register int i=1,x,y,z;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		addedge(x,y,z); addedge(y,x,z);
	}
	scanf("%d",&m);
	tot=0; T=sqrt(n);
	if (T*T<n) T++;
	dfs1(1,0);
	for (register int i=1;i<=T;i++)
	{
		L[i]=R[i-1]+1; R[i]=min(n,T*i);
		for (register int j=L[i];j<=R[i];j++)
			dis[j]=Sort[i][j-L[i]+1]=Dis[rk[j]],pos[j]=i;
		sort(Sort[i]+1,Sort[i]+1+R[i]-L[i]+1);
	}
	dfs2(1,0);
	printf("%d",(ans-n)/2);  //先减去n个(x,x)的点对，然后(x,y)和(y,x)只算一个，所以除以2
	return 0;
}
```


---

## 作者：玫葵之蝶 (赞：15)

## 点分治

（食用链接效果更佳哦：[我的blog](http://blog.csdn.net/stone41123/article/details/78141624)）

关于这个题，就是每次找重心，以重心为根dfs每个点到重心的距离，然后统计经过重心的路径，然后删除重心（打个标记），继续递归执行重心的每棵子树。

统计重心的答案时，可以将每个点到重心的距离排个序，左右两个指针扫，可以O(n)统计，再加上O(nlogn)的排序，总时间就是nlog2n

然后得出的答案就是错误的。

为什么呢？我们可以自己手造一组数据，画出图来，然后统计答案时我们暴力统计（就是不要拿指针扫），看看答案中都是什么路径。

然后就发现，有路径多次被统计，而且第一次统计的时间还是在这两个点在同一棵子树中时就被统计了。

为什么会出现这种情况呢？看这张图，这就是那个被重复统计的路径。

![](http://img.blog.csdn.net/20170929214137280?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvc3RvbmU0MTEyMw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

图片中数字表示路径的经过顺序，箭头表示路径方向。

很明显，如果图上这条路的总长不超过k，那么毫无疑问，一号点和五号点会被统计两次，而图上这条路径明显不符合题意，不可以被统计，那么我们只要再减去这些路径就好了，具体可以看我的代码。

然后就是要多注意细节，点分治细节比较多。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
    int x=0;char ch=' ';int f=1;
    while(ch!='-'&&(ch<'0'||ch>'9'))ch=getchar();
    if(ch=='-')f=-1,ch=getchar();
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
struct edge{
    int to,next,w;
}e[80001];
int n,tot,root;
ll k;
int head[40001];
inline void addedge(int x,int y,int l){
    e[++tot].to=y;e[tot].next=head[x];e[tot].w=l;head[x]=tot;
}
int size[40001],vis[40001],mx,sz;
ll dis[40001],q[40001],l,r;
void getroot(int x,int fa){
    size[x]=1;int num=0;
    for(int i=head[x];i;i=e[i].next){
        int u=e[i].to;
        if(u==fa||vis[u])continue;
        getroot(u,x);
        size[x]+=size[u];
        num=max(num,size[u]);
    }
    num=max(num,sz-size[x]);
    if(num<mx){
        mx=num;root=x;
    }
}
void getdis(int x,int fa){
    q[++r]=dis[x];
    for(int i=head[x];i;i=e[i].next){
        int u=e[i].to;
        if(u==fa||vis[u])continue;
        dis[u]=dis[x]+e[i].w;
        getdis(u,x);
    }
}
ll calc(int x,int v){
    r=0;
    dis[x]=v;
    getdis(x,0);
    ll sum=0;
    l=1;
    sort(q+1,q+r+1);
    while(l<r){
        if(q[l]+q[r]<=k)sum+=r-l,l++;
        else r--;
    }
    return sum;
}
ll ans;
void dfs(int x){
    ans+=calc(x,0);
    vis[x]=1;
    for(int i=head[x];i;i=e[i].next){
        int u=e[i].to;
        if(vis[u])continue;
        ans-=calc(u,e[i].w);
        sz=size[u];
        mx=0x3f3f3f3f;
        getroot(u,0);
        dfs(root);
    }
}
int main(){
    n=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read(),l=read();
        addedge(x,y,l);addedge(y,x,l);
    }
    k=read();
    sz=n;
    mx=0x3f3f3f3f;
    getroot(1,0);
    dfs(root);
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Nerovix (赞：11)

这题...怎么所有题解的做法都跟我不一样啊qwq

我的做法是DSU on tree（树上启发式合并）

启发式合并是个好东西，有许多应用，比如并查集按秩合并等 借用我在博客里读到的一句话，它有时候能帮你把一个愚蠢N^2的算法用一个套路式的优化就变成nlgn算法

现在来康康此题：

枚举两点进行统计显然不可以，妥妥的T

但是想到树上两点的距离与LCA有极大的关系 我们可以考虑枚举节点，试图求出以当前节点为LCA的答案贡献

纸上随便画画 就可以YY出一个简单的想法：

假设当前枚举到节点X，X有很多儿子，记为Y1，Y2...

那么现在我们对X的儿子Yi进行讨论：枚举Yi子树中的每一个点t,那么**X的其他儿子的子树中的一个节点s**若满足k>=dis[t]+dis[s]-2*dis[X]，即dis[s]<=k+2*dis[X]-dis[t],(k是原题目中的那个k)，那么s,t就是满足题目要求的点对

那么如果我们可以维护一个集合T，其中保存了Y1~Yi-1子树的所有点的dis值，就可以快速查询有多少个满足条件的s了 每当讨论完一个X的儿子的子树，就把子树中的所有点的dis值加入T 

然后最后，再统计上X自己到自己子树的贡献就行了

（这里剧透一下 因为这个集合T需要加入元素，查询<=一个值的元素的个数，所以这里你需要手写平衡树/动态开点线段树/离散化树状数组来搞集合T）

不过分析一下复杂度，~~该死这咋变成n^2lgn比暴力还大了~~

那这可咋整啊

~~整不起，所以这题不能这么做 全剧终~~

啊所以应该DSU一下了

你想，讨论完了X之后T集合已经包含了X中的所有点的dis值了

直接这样你就扔掉了多可惜

不如拿给X的father继续接着用 省时省力

但是这么一想，你要是father（X）的儿子们全都这么一股脑把自己的T给了自己的father（X），father（X）会很自闭。。。因为father（X）仍需枚举每个儿子，统计上面做法中的s，t个数

不过仔细一想，可以这样：father（x）只接受其中一个儿子的T，然后其他儿子往这上面合并，一边统计一边合并就可以了

不过father（X）到底要哪个儿子的呢？肯定要最大的那个嘛，这样可以少些合并

也就是选father（X）的重儿子

于是这样一步步思考下来，你就YY出了DSU on tree 这题也就可以解决了

DSU on tree的基本复杂度可以证明是nlgn

因为此题还要维护一个集合T，不管怎么样写都是log级别的

所以总时间复杂度n（lgn）^2

DSU on tree的算法就是这样，不过理解和写出来还是两码事 如果是没学过的同学珂以自己去baidu康康

这里就给康康我写的DSU on tree+动态开点线段树代码：
```cpp
#include<stdio.h>
#include<bits/stdc++.h>
#define f(a,b,c) for(register int a=(b);a<=(c);++a)
#define ff(a,b,c) for(register int a=(b);a>=(c);--a)
#define ll long long
#define max(a,b) ((a)>(b)?(a):(b))
#define int long long
char pbuf[1<<20],*pp1=pbuf;
inline void push(char c){*pp1=c;pp1=(pp1-pbuf==(1<<20)-1)?(fwrite(pbuf,1,1<<20,stdout),pbuf):(pp1+1);}
//#define pc push
#define pc putchar
#define pe pc('\n')
#define ps pc(' ')
#define wer rd()
char *p1,*p2,buf[1<<20];
#define GC (p1==p2&&(p1=buf,p2=buf+fread(buf,1,1<<20,stdin),p1==p2)?0:(*(p1++)))
//#define GC getchar()
using namespace std;
inline ll wer{
	ll ans;char t,k;
	while(((t=GC)!='-')&&(t>'9'||t<'0'));
	k=(t=='-');
	ans=k?0:(t-'0');
	while((t=GC)>='0'&&t<='9')ans=ans*10+t-'0';
	return k?-ans:ans;
}
inline void wt(ll k)
{
	if(k<0)pc('-'),wt(-k);
	else
	{
		if(k<10)pc('0'+k);
		else wt(k/10),pc('0'+k%10);
	}
	return;
}
const int N=40001;
int k[N<<5],ls[N<<5],rs[N<<5],tot,ck[N<<5];
int he[N],ne[N<<1],n,to[N<<1],cnt,le[N<<1],si[N],so[N],de[N];
#define addedge(x,y,z) ne[++cnt]=he[x],he[x]=cnt,to[cnt]=y,le[cnt]=z 
void dfs(int x,int fa,int u)
{
//	wt(x),pe;
	si[x]=1;
	de[x]=de[fa]+u;
	for(register int i=he[x];i;i=ne[i])
	{
		if(to[i]==fa)continue;
		dfs(to[i],x,le[i]);
		si[x]+=si[to[i]];
		if(so[x]==0||si[to[i]]>si[so[x]])so[x]=to[i];
	}
	return;
 } 
int maxm=100000000;
int Ans=0,K;
int RT=0;
//////////动态开点线段树//////////// 
void modify(int&now,int l,int r,int x,int kk)//单点加 
{
	if(r<x||x<l)return;
	if(!now)now=ck[tot--],ls[now]=rs[now]=k[now]=0;
	if(l==r){k[now]+=kk;return;} 
	int mid=l+r>>1;
	modify(ls[now],l,mid,x,kk);
	modify(rs[now],mid+1,r,x,kk);
	k[now]=k[ls[now]]+k[rs[now]];
}
int quary(int now,int l,int r,int x,int y)//区间求和 
{
	if(y<x)return 0;
	if(!now||r<x||y<l)return 0;
	if(x<=l&&r<=y)return k[now];
	int mid=l+r>>1;
	return quary(ls[now],l,mid,x,y)+quary(rs[now],mid+1,r,x,y);
}
void del(int&now,int l,int r)//删除一颗线段树 
{
	if(!now)return;
	if(l!=r)
	{   
	    int mid=l+r>>1;
		del(ls[now],l,mid);
		del(rs[now],mid+1,r);
	}
	k[now]=0;ck[++tot]=now;now=0;
	return;
 } 
void _count(int x,int fa,int which)//统计答案
{
	Ans+=quary(RT,1,maxm,1,K+de[which]*2-de[x]);
	for(int i=he[x];i;i=ne[i])
	{
	    if(to[i]==fa)continue;
	    _count(to[i],x,which);
	}
}
void put(int x,int fa)//加入集合T
{
	modify(RT,1,maxm,de[x],1);
	for(int i=he[x];i;i=ne[i])
	{
		if(to[i]==fa)continue;
		put(to[i],x);
	}
}
void DSU(int x,int fa,int ty)
{
	
	for(int i=he[x];i;i=ne[i])
	{
		if(to[i]==fa||to[i]==so[x])continue;
		DSU(to[i],x,0);
	}
	if(so[x])DSU(so[x],x,1);//重儿子单独拿出来
	Ans+=quary(RT,1,maxm,1,K+de[x]);
	modify(RT,1,maxm,de[x],1); 
	for(int i=he[x];i;i=ne[i])
	{
		if(to[i]==fa||to[i]==so[x])continue;
		_count(to[i],x,x);
		put(to[i],x);
	}
	if(!ty)del(RT,1,maxm);//不是重儿子，父亲不要，直接删掉
}
main()
{
    n=wer;
    f(i,1,(n<<5)-3)ck[++tot]=i;
    f(i,2,n)
    {
    	int a=wer,b=wer,c=wer;
    	addedge(a,b,c),addedge(b,a,c);
    }
	K=wer;
    dfs(1,0,1);
//    f(i,1,n)wt(de[i]),ps;pe;
    DSU(1,0,0);
    wt(Ans);
	fwrite(pbuf,1,pp1-pbuf,stdout);
    return 0;
}
```
总时间500多ms，不算太快也不算太慢吧

~~我人傻常数大啊~~


---

## 作者：xixike (赞：9)

这道题我们如果暴力枚举每一个点，去求其他的点到它的距离，时间一定会爆炸，所以我们不难想到用二分的思路来求解，而我们要找的“二分”的点，就是这棵树的重心。

所谓“**重心**”，就是当把这个点删去后（想象删去，并不是真删去），能使得**剩下的所有子树当中最大的子树子树最小**。然后我们再不断去递归寻找所有的子树的重心即可。

接下来说说有了重心之后该如何操作。我们可以发现对于这棵树上的任意两个点，它们只会有3种关系：

①两个点在同一子树上。（dfs求两个点之间的距离）

②两个点在不同的子树上。（预处理出每个子树中每个节点到重心的距离，然后  再把两个点到重心的距离加起来）

③一个点在一棵子树中，另一个点是重心。(存一个点，使这个点到重心的距离为零，再加上另一个点到重心的距离即可，与②差不多)

但实际上我们发现在计算②的时候可能会重复计算①中的情况（我没有标记两个点是否在同一子树中，计算②情况时是对于所有的点计算的）。所以利用容斥的思想，减去重复的即可。

**附代码**
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
#define MAXN 40010

using namespace std;

struct node {
	int to,len;         //to存子节点编号，len存边长
};
vector <node> G[MAXN];      //vector存边
int siz[MAXN],n,k,ans;      //siz[i]表示以i为根的树的大小
bool used[MAXN];            //存是否已经作为重心被删除

//—————————————————————————————————计算siz数组，即每棵子树的大小
int dfs(int v,int p) {
	int c=1;
	for(int i=0; i<G[v].size(); i++) {
		int w=G[v][i].to;
		if(w==p||used[w]) continue;
		c+=dfs(w,v);
	}
	siz[v]=c;
	return c;
}

//—————————————————————————————————用来找重心
//pair（最大子树的顶点个数，顶点编号）
pair<int,int> find(int v,int p,int t) {   //t表示当前子树的大小
	pair<int,int> temp=make_pair(1e9,-1);
	int s=1,m=0;                      //s为除了当前的点到该子树的根节点这一路径上其余所有子树的和。m为除了s所在的子树中，最大的子树
	for(int i=0; i<G[v].size(); i++) {
		int w=G[v][i].to;
		if(w==p||used[w]) continue;
		temp=min(temp,find(w,v,t));
		m=max(m,siz[w]);
		s+=siz[w];
	}
	m=max(m,t-s);                      //最后在m和t-s（即从改树的根到重心的这一子树上的和）中找最大值
	temp=min(temp,make_pair(m,v));
	return temp;
}

//—————————————————————————————————计算子树中所有的点到重心的距离
void dfs1(int v,int p,int d,vector<int> &ds) {
	ds.push_back(d);
	for(int i=0; i<G[v].size(); i++) {
		int w=G[v][i].to;
		if(w==p||used[w]) continue;
		dfs1(w,v,d+G[v][i].len,ds);
	}
}

//—————————————————————————————————统计子树中和不超过k的顶点对数
int count(vector<int> &ds) {
	sort(ds.begin(),ds.end());
	int j=ds.size();
	int res=0;
	for(int i=0; i<ds.size(); i++) {
		while(j>0&&ds[i]+ds[j-1]>k) j--;
		if(j-1>=i) res+=j-1;
		else res+=j;
	}
	return res/2;
}
//—————————————————————————————————对顶点v为根的子树找重心，并按上述情况分割求解
void dfs2(int v) {
	dfs(v,-1);
	int s=find(v,-1,siz[v]).second;   //找到以v为根节点的树的重心
	used[s]=1;
	for(int i=0; i<G[s].size(); i++) {
		int w=G[s][i].to;
		if(used[w]) continue;
		dfs2(w);
	}
	vector<int> ds;
	ds.push_back(0);            //加上一个到重心的距离为零的点，来求③情况
	for(int i=0; i<G[s].size(); i++) {
		int w=G[s][i].to;
		if(used[w]) continue;
		vector<int> tds;
		dfs1(w,s,G[s][i].len,tds);
		ans-=count(tds);                 //容斥，提前减去①情况中重复的点
		ds.insert(ds.end(),tds.begin(),tds.end()); //并把重复的树加到
	}
	ans+=count(ds);   //加上的所有的情况
	used[s]=0;
}

void solve() {
	ans=0;
	dfs2(1);
	printf("%d\n",ans);
}

int main() {
	scanf("%d",&n);
	for(int i=0; i<n-1; i++) {
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		G[a].push_back({b,c});
		G[b].push_back({a,c});
	}
	scanf("%d",&k);
	solve();
	return 0;
}
```


---

## 作者：MILLOPE (赞：7)

## 题目
给你一棵TREE,以及这棵树上边的距离.问有多少对点它们两者间的距离小于等于K

输入输出格式
输入格式：
N（n<=40000） 接下来n-1行边描述管道，按照题目中写的输入 接下来是k

输出格式：
一行，有多少对点之间的距离小于等于k

输入输出样例
输入样例#1： 
```cpp
7
1 6 13 
6 3 9 
3 5 7 
4 1 3 
2 4 20 
4 7 2 
10
```
输出样例#1： 
```cpp
5
```

## 题解
- ~~lrd大佬讲课时因为听不懂，翻书水时间的时候看到了点分治，就学了一下qwq~~
- 首先对于这道题一个很暴力的想法：枚举每个点对看看之间的距离是否$\leq k$，复杂度应该是$O(n^2logn)?$
- 暴力的思路显然过不了~~我这种暴力选手该怎么办啊qwq~~
- 我们考虑树上两点之间的路径有什么情况
	1. 经过根节点
	2. 不经过根节点
- 对于第一种的情况我们算两点间路径长度时可以将$dis(u,v)$转化为$dis(u,root)+dis(root,v)$ 
- 而对于第二种情况我们可以找到$u,v$路径所在的子树，将根节点变为子树的根节点，然后就变为了第一种情况
- 所以我们可以不断的递归根节点将所有情况转化为第一种情况
- 设$belong[u]$表示$u$属于哪一棵子树
- 那么$belong[u]=\not belong[v] \quad d[u]+d[v]\leq k$满足条件的第一类路径条数即为满足条件的点对数
- 下面我们来讨论如何计算满足条件的点对数：
	1. 将树中的节点到根节点的权值放入数组$len$中，并排序
	2. 用两个指针$l,r$扫描数组，每找到一个合法的答案就加上$r-l$，就让$l++$，否则让$r--
- 对于上面的计算我们发现有一些问题（如下图~~有点丑~~）：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190714185746988.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM0NDkzODQw,size_16,color_FFFFFF,t_70)

- 在指针扫描的过程中我们会出现不合法（关于合法的判断请看上面的条件）的情况
- ~~这该怎么办呢嘤嘤嘤~~
- 我们可以发现不合法的路径在当前根的一颗子树上，即没有跨越两棵子树（如果跨越了它就合法了）
- 所以们可以在遍历的时候减去不合法的情况（容斥）
- 具体的方法
	1. $all += cal(x,0)$
	2. $all  -= cal(v,dis(u,v))$
- 讲解：
- ~~一个蒟蒻的口胡~~可以求当前根节点的儿子节点的答案，统计儿子节点的答案时将各个点的距离加上儿子到根节点的距离，即把符合在一个子树条件的情况统计出来，即不合法的答案，最后用根节点算出来的总答案减去不合法的答案就行了。可以结合上面那个不合法的图理解一下（如果不合法的话两点会多了两倍到根节点的距离，在遍历儿子节点时将每个点到根节点的距离都加上儿子节点距离就和不合法的情况相同了）
- 点分治的关键之处是在递归根节点的过程，我们每次将根节点选为重心会将复杂度降低，因为最差情况也只会递归$logn$层，其余情况最差可能达到$n$层
- 点分治的复杂度为$Onlog^2n$，比较优秀qwq

```cpp
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <deque>
#include <queue>
#include <stack>
#include <cctype>
#include <string>
#include <cstdio>
#include <vector>
#include <complex>
#include <cstring>
#include <iomanip>    
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std; 
typedef long long LL; 
const int maxn = 40000 + 100; 

template <class T> 
inline void read(T &s) {
	s = 0; 
	T w = 1, ch = getchar(); 
	while (!isdigit(ch)) { if (ch == '-') w = -1; ch = getchar(); }
	while (isdigit(ch)) { s = (s << 1) + (s << 3) + (ch ^ 48); ch = getchar(); }
	s *= w; 
}

int n, m, k, tot, all_node, ans, root;
// root 为重心
// ans 为答案
// all_node 表示所有点的数目 
int lin[maxn], max_part[maxn], size[maxn], len[maxn], d[maxn]; 
// d[i] 表示i到根节点的距离
// len[i] 表示路径长度
// len[0] 中记录节点个数
// size[i] 表示以i为根的子树大小
// max_part[i] 表示i的最大的子树大小
bool vis[maxn]; 
// vis用于求重心时避免重复访问 
struct node {
	int next, to, dis; 
} edge[maxn << 1]; 
// edge 用于存边

inline void add(int from, int to, int dis) {
	edge[++tot].to = to; 
	edge[tot].dis = dis; 
	edge[tot].next = lin[from]; 
	lin[from] = tot; 
}

void get_root(int u, int fa) { // 找到树的重心
	max_part[u] = 0, size[u] = 1; 
	for (int i = lin[u]; i; i = edge[i].next) {
		int v = edge[i].to; 
		if (v == fa || vis[v]) continue;  
		get_root(v, u); 
		size[u] += size[v]; 
		max_part[u] = max(max_part[u], size[v]); 
	}
	max_part[u] = max(max_part[u], all_node - max_part[u]); 
	if (max_part[u] < max_part[root]) root = u; 
}

void get_dis(int u, int fa) { // 求出每个点到根节点的距离
	len[++len[0]] = d[u]; 
	for (int i = lin[u]; i; i = edge[i].next) {
		int v = edge[i].to; 
		if (v == fa || vis[v]) continue; 
		d[v] = d[u] + edge[i].dis; 
		get_dis(v, u); 
	}
}

int cal(int u, int now) { // 计算以u为根的所有情况的答案
	d[u] = now, len[0] = 0; 
	get_dis(u, 0); 
	sort(len + 1, len + len[0] + 1); 
	int all = 0; 
	for (int l = 1, r = len[0]; l < r; ) {
		if (len[l] + len[r] <= k) {
			all += r - l; 
			++l; 
		}
		else r--; 
	}
	return all; 
}

void solve(int u) { // 求解以u为重心的情况
	vis[u] = true; 
	ans += cal(u, 0); 
	for (int i = lin[u]; i; i = edge[i].next) {
		int v = edge[i].to; 
		if (vis[v]) continue; 
		ans -= cal(v, edge[i].dis); // 减去不合法的
		all_node = size[v]; 
		root = 0; 
		get_root(v, u); 
		solve(root); 
	}
}

int main() {
	read(n);
	for (int i = 1; i < n; ++i) {
		int u, v, w; 
		read(u), read(v), read(w); 
		add(u, v, w); 
		add(v, u, w); 
	}
	read(k); 
	all_node = n, max_part[0] = n, root = 0; 
	get_root(1, 0); 
	solve(root); 
	printf("%d\n", ans); 
	return 0; 
} 


```

---

## 作者：crashed (赞：5)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.com.cn/problem/P4178)看题目。  
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;看到树上路径的题，我们不难想到点分治。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;在我们对于一个点分治的时候，假如我们用一个桶$b[i]$，存下来当前到重心距离为$i$的点的个数，那么对于一个到重心距离为$d(d\le k)$的点来说，它的贡献就是$\sum_{i=0}^{k-d}b[i]$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;出现了前缀和的结构，所以我们需要用树状数组来维护这个桶。点分治本身$O(n\log_2n)$，树状数组$O(\log_2k)$，总时间$O(n\log_2n\log_2k)$。  
# 代码
```cpp
#include <cstdio>

typedef long long LL;

const int MAXN = 4e4 + 5, MAXK = 2e4 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

struct edge
{
	int to, nxt, w;
}Graph[MAXN << 1];

int BIT[MAXK];
int seq[MAXN], sta[MAXN], top;
int dist[MAXN];
int head[MAXN], siz[MAXN], mx[MAXN];
LL ans;
int N, K, cnt, rt;
bool visited[MAXN];

int lowbit( const int &x ) { return x & ( -x ); }
void update( const int x, const int v ) { for( int i = x ; i <= K ; i += lowbit( i ) ) BIT[i] += v; }
int getSum( int x ) { int ret = 0; while( x ) ret += BIT[x], x -= lowbit( x ); return ret; }

void addEdge( const int from, const int to, const int W ) 
{
	Graph[++ cnt].to = to, Graph[cnt].w = W, Graph[cnt].nxt = head[from];
	head[from] = cnt;
}

void DFS( const int u, const int fa )
{
	siz[u] = 1, mx[u] = 0;
	for( int i = head[u], v ; i ; i = Graph[i].nxt )
		if( ! visited[v = Graph[i].to] && v ^ fa )
			DFS( v, u ), siz[u] += siz[v], mx[u] = MAX( mx[u], siz[v] );
}

bool getCen( const int u, const int fa, const int all )
{
	if( mx[u] <= ( all >> 1 ) && all - siz[u] <= ( all >> 1 ) ) { rt = u; return true; }
	for( int i = head[u], v ; i ; i = Graph[i].nxt )
		if( ! visited[v = Graph[i].to] && v ^ fa )
			if( getCen( v, u, all ) ) return true;
	return false;
}

void getDist( const int u, const int fa )
{
	sta[++ top] = u;
	for( int i = head[u], v ; i ; i = Graph[i].nxt )
		if( ! visited[v = Graph[i].to] && v ^ fa )
			dist[v] = dist[u] + Graph[i].w, getDist( v, u ); 
}

void cal( const int u )
{
	int l = 0;
	for( int i = head[u], v ; i ; i = Graph[i].nxt )
		if( ! visited[v = Graph[i].to] )
		{
			top = 0, dist[v] = Graph[i].w, getDist( v, u );
			for( int j = 1 ; j <= top ; j ++ )
				if( dist[v = sta[j]] <= K )
					ans += getSum( K - dist[v] ) + 1;
			for( int j = 1 ; j <= top ; j ++ )
				if( dist[v = sta[j]] <= K )
					update( dist[v], 1 );
			while( top ) seq[++ l] = sta[top --];
		}
	for( int v ; l ; l -- )
	{
		if( dist[v = seq[l]] <= K ) update( dist[v], -1 );
		dist[v] = 0;
	}
}

void divide( const int u )
{
	DFS( u, 0 );
	getCen( u, 0, siz[u] );
	cal( rt );
	visited[rt] = true;
	for( int i = head[rt], v ; i ; i = Graph[i].nxt )
		if( ! visited[v = Graph[i].to] ) divide( v );
	visited[rt] = false;
}

int main()
{
	read( N );
	for( int i = 1, a, b, c ; i < N ; i ++ )
		read( a ), read( b ), read( c ), addEdge( a, b, c ), addEdge( b, a, c );
	read( K );
	divide( 1 );
	write( ans ), putchar( '\n' );
	return 0;
}
```

---

## 作者：Genius_Z (赞：5)

这题作为本蒟蒻的淀粉质入门题，在没有看过和打过板子的情况下自己$yy$了一个常数略大的做法，复杂度为$\Theta(nlog^2_2n)$

由于是求距离小于等于$k$的点对的个数，所以我们考虑把点对$(x,y)$的距离拆成$dis(x,focus)+dis(focus,y)$（$focus为当前的分治中心$)。

很自然的会想到依次枚举子树中的每个点，算出它与之前遍历过的子树的点形成的点对的贡献。

这个可以用数据结构维护，显然会想到值域树状数组。

但值域可能非常大而且不容易离散化，我们考虑其他数据结构。

每个点的贡献即为它的排名，所以考虑用平衡树维护。

由于是求小于等于$k$的点对，所以累记$size$的时候要算上自身的$cnt$。

还有就是统计子树贡献的时候不能边加点边统计，要统计完再加点，本蒟蒻这里选用了开一个栈记录子树的点的$dis$值。

然后就是码力的问题了，注意平衡树每次要把插入的点的原信息清空，每次$memset$太慢了。

Code：

```cpp
#include <algorithm>
#include <tuple>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
#define inl inline
#define re register int
#define fa(x) t[x].fa
#define ls(x) t[x].child[0]
#define rs(x) t[x].child[1]
#define ll long long
const int inf = 0x3f3f3f3f;
#define lowbit(x) ((x) & (-x))
using namespace std;
template <class Read>
inl Read read() {
	Read x = 0;
	register bool w = 0;
	register char c = getchar();
	while (c > '9' || c < '0') {
		if (c == '-') w = 1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return w ? -x : x;
}
struct edge {
	int next, to, w;
}e[200001];
int tot, head[100001], k, n, ans, cnt, root, ncnt, scnt, min_siz, focus, siz[100001], d[100001], st[100001], top;
bool vis[100001];
inl void add(int x, int y, int w) {
	e[++tot] = edge{ head[x],y,w }, head[x] = tot;
	e[++tot] = edge{ head[y],x,w }, head[y] = tot;
}
struct node {
	int fa, child[2], w, size, cnt;
}t[100001];
inl bool poi(int x) {
	return rs(fa(x)) == x;
}
inl void maintain(int x) {
	t[x].size = t[ls(x)].size + t[rs(x)].size + t[x].cnt;
}
inl void rotate(int x) {
	re f = fa(x), gf = fa(f), fs = poi(x), gfs = poi(f), s = t[x].child[fs ^ 1];
	if (gf)t[gf].child[gfs] = x;
	t[f].child[fs] = s, t[x].child[fs ^ 1] = f;
	if (s)fa(s) = f;
	fa(f) = x, fa(x) = gf;
	maintain(f);
}
inl void splay(int x, int to) {
	while (fa(x) != to) {
		if (fa(fa(x)) != to)poi(x) == poi(fa(x)) ? rotate(fa(x)) : rotate(x);
		rotate(x);
	}
	maintain(x);
	if (!to)root = x;
}
inl void destroy(int x) {
	t[x].fa = t[x].child[0] = t[x].child[1] = t[x].cnt = t[x].size = t[x].w = 0;
}
inl void insert(int w) {
	re x = root, f = 0;
	while (x&&t[x].w != w)f = x, t[x].size++, x = t[x].child[w > t[x].w];
	if (x&&t[x].w == w) {
		t[x].cnt++, t[x].size++;
		splay(x, 0);
		return;
	}
	x = ++cnt, destroy(x);
	t[x].cnt = t[x].size = 1, t[x].w = w;
	if (f)fa(x) = f, t[f].child[w > t[f].w] = x;
	splay(x, 0);
}
inl int askrank(int w) {
	re x = root, sum = 0;
	while (x) {
		if (w > t[x].w)sum += t[ls(x)].size + t[x].cnt, x = rs(x);
		else if (w == t[x].w) { sum += t[ls(x)].size + t[x].cnt, splay(x, 0); return sum; }
		else x = ls(x);
	}
	return sum;
}
inl void dfs1(int x, int fa) {
	siz[x] = 1;
	re max_sub = 0;
	for (re i = head[x]; i; i = e[i].next) {
		if (vis[e[i].to] || e[i].to == fa)continue;
		dfs1(e[i].to, x);
		siz[x] += siz[e[i].to];
		max_sub = max(max_sub, siz[e[i].to]);
	}
	max_sub = max(max_sub, ncnt - siz[x]);
	if (max_sub < min_siz) {
		min_siz = max_sub;
		focus = x;
	}
}
inl void dfs2(int x, int fa) {
	siz[x] = 1;
	for (re i = head[x]; i; i = e[i].next) {
		if (vis[e[i].to] || e[i].to == fa)continue;
		d[e[i].to] = d[x] + e[i].w;
		dfs2(e[i].to, x);
		siz[x] += siz[e[i].to];
	}
}
inl void calc(int x, int fa) {
	st[++top] = d[x];
	ans += askrank(k - d[x]);
	for (re i = head[x]; i; i = e[i].next) {
		if (!vis[e[i].to] && e[i].to != fa)calc(e[i].to, x);
	}
}
inl void divide(int x, int fa) {
	focus = 0, min_siz = inf;
	dfs1(x, fa);
	d[x = focus] = 0, root = cnt = 0, vis[x] = 1, top = 0;
	dfs2(x, fa);
	if (head[x])insert(0);
	for (re i = head[x]; i; i = e[i].next) {
		if (vis[e[i].to])continue;
		calc(e[i].to, x);
		if (e[i].next)while (top)insert(st[top--]);
	}
	for (re i = head[x]; i; i = e[i].next) {
		if (vis[e[i].to])continue;
		ncnt = siz[e[i].to];
		divide(e[i].to, x);
	}
}
signed main() {
	n = read<int>();
	for (re i = 1; i < n; i++) {
		re x = read<int>(), y = read<int>(), w = read<int>();
		add(x, y, w);
	}
	k = read<int>(), ncnt = n;
	divide(1, 0);
	printf("%d\n", ans);
}
```



---

## 作者：2018chenyu (赞：5)

## 这是一道点分治的[模板题](https://www.luogu.com.cn/problem/P4178)
~~下文输入格式略有不同别说我没提醒你~~  
### 题目描述
给定一个有 $N$ 个点（编号 $1,2,...,N$）的树，每条边都有一个权值（不超过 $1000$）。  
树上两个节点x与y之间的路径长度就是路径上各条边的权值之和。  
求长度不超过K的路径有多少条。  
### 输入格式
输入包含多组测试样例。  
每组测试样例的第一行包含两个正整数 $N$ 和 $K$。  
接下来 $N-1$ 行，每行包含三个正整数 $u,v,l$，表示节点 $u$ 与 $v$ 之间存在一条边，且边的权值为 $l$。  
当输入样例 $N=0,K=0$ 时，表示输入终止，且该样例无需处理。  
### 输出格式
每个测试样例输出一个结果。  
每个结果占一行。  
### Sample Input / Output
```
5 4
1 2 3
1 3 1
1 4 2
3 5 1
0 0 

8 
```

------------
### 进入正文
首先对于这道题一个很暴力的想法：枚举每个点对看看之间的距离是否 $ \le k$，复杂度应该是 $O(n^2logn)\ ?\ $反正绝对过不了。  

**首先我们来分析一下，树上两点之间的路径有一下两种情况**  
+ 1. 经过根节点  
+ 2. 不经过根节点（即两个点在当前根节点的同一子树内）  

**对于情况一：**  
$dis(u,v)=dis(u,root)+dis(root,v)$  
**对于情况二：**  
我们可以找到 $u,v$ 路径所在的子树，将根节点变为子树的根节点，然后就变为了第一种情况，即我们可以不断的递归到子树的根节点，将所有情况转化为第一种情况求出答案  

不难发现，这样递归下去的 **复杂度和树的深度有关**，所以我们应尽量的减小树的深度以优化复杂度，那么我们怎么办呢？  
对于每一棵树，我们都有一个**重心**，其所有的子树中最大的子树节点数最少，也就是说删去重心后生成的多棵树会尽可能平衡。  
**拿输入样例举个例子**，假如树长这样，最大深度为 $4$，极其不优秀：  
![](https://cdn.luogu.com.cn/upload/image_hosting/rmi3w6ol.png)  
但是这样就优美的多了：最大深度为 $3$，我们称此时的根节点为“树的重心”  
![](https://cdn.luogu.com.cn/upload/image_hosting/92h3c05a.png)  
**求树的重心也不难，一路扫下去就完事了：$O(n)$**  
$code:$  
```cpp
int maxx,root,smax[N],size[N];
//maxx=smax[root],root为树的重心
//smax[i]表示i的最大子树的大小
//size[i]表示以i为跟的子树大小 
void dfs(int x,int fa)
{
	smax[x]=0;size[x]=1;
	for(int k=last[x];k;k=a[k].next)
	{
		int y=a[k].y;if(y==fa) continue;
		dfs(y,x);size[x]+=size[y];
		smax[x]=mymax(smax[x],size[y]);
	}
	smax[x]=mymax(smax[x],n-size[x]);
	maxx=mymin(maxx,smax[x]);
	root=(maxx==smax[x])?x:root;
}
```
**那么如何计算点对方案数呢？** 当然是求出每个节点到树的重心的距离（记为 $dis[i]$），枚举点对 $(i,j)\ \ \ $ $if(dis[i]+dis[j]\le k)\ \ ans++$，这里有一个优化，可以把 $dis$ 数组排个序，用 $l,r$ 两个指针分别从前、后扫描 $dis$ 数组，显然随着 $l$ 从左到右扫，$r$ 是从右到左单调递减的，代码如下：  
```cpp
for(int l=1,r=dis[0];l<r;)//尝试把两条根节点到子节点（包括根节点）的路径合并成一条经过根节点的路径 
{
	if(dis[l]+dis[r]<=k) sum+=r-l/*dis[l]+dis[l+1~r-1]<=k*/,l++;
	else r--;
}
```
------------

**不过，枚举的点对 $(i,j)$ 间的路径可能属于上文提到的情况二，我们需要用容斥原理修正答案，具体细节请参考完整代码：**  

------------

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e4+10;
inline int mymin(int a,int b) {return a<b?a:b;}
inline int mymax(int a,int b) {return a>b?a:b;}
inline int read()
{
    int x=0;bool f=false;
    char ch=getchar();
    while(ch<'0' || ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
    return f?-x:x;
}
int n,k,ans,point;//point为点数 
struct node{int y,d,next;}a[N<<1];int len,last[N];
inline void ins(int x,int y,int d) {a[++len].y=y;a[len].d=d;a[len].next=last[x];last[x]=len;}
/*找到一个点，其所有的子树中最大的子树节点数最少，
那么这个点就是这棵树的重心，删去重心后，生成的多棵树尽可能平衡。*/
int maxx,root,size[N],smax[N];//size->以己为跟的子树大小  smax->最大子树的大小
bool vis[N];//求重心时避免重复访问
void get_root(int x,int fa)//找出树的重心
{
    size[x]=1;smax[x]=0;
    for(int k=last[x];k;k=a[k].next)
    {
        int y=a[k].y;
		if(y==fa || vis[y]) continue;
        get_root(y,x);size[x]+=size[y];
        smax[x]=mymax(smax[x],size[y]);
    }
    smax[x]=mymax(smax[x],point-size[x]);
    maxx=mymin(maxx,smax[x]);
    root=(maxx==smax[x])?x:root;
}
int dis[N];//记录各个点的路径长度 
void get_dis(int x,int fa,int Dis)//以x为根，求出每个点到根节点的距离
{
	dis[++dis[0]]=Dis;
	for(int k=last[x];k;k=a[k].next)
	{
		int y=a[k].y;
		if(y==fa || vis[y]) continue;
		get_dis(y,x,Dis+a[k].d);
	}
}
int calc(int x,int dst)//计算以x为根的所有情况的答案
{
	get_dis(x,dis[0]=0,dst);
	sort(dis+1,dis+dis[0]+1);
	int sum=0;
	for(int l=1,r=dis[0];l<r;)//尝试把两条根节点到子节点（包括根节点）的路径合并成一条经过根节点的路径 
	{
		if(dis[l]+dis[r]<=k) sum+=r-l/*dis[l]+dis[l+1~r-1]<=k*/,l++;
		else r--;
	}
	return sum;
}
void solve(int x)//求解以x为重心的情况
{
	vis[x]=true;
	ans+=calc(x,0);
	for(int k=last[x];k;k=a[k].next)
	{
		int y=a[k].y;
		if(vis[y]) continue;
		ans-=calc(y,a[k].d);//减去不合法的情况 
        maxx=point=size[y];
		get_root(y,x);solve(root);
	}
}
int main()
{
    n=read();k=read();
    while(n || k)
    {
        len=0;memset(last,0,sizeof(last));
        memset(vis,false,sizeof(vis));
        for(int i=1;i<n;i++)
        {
            int x=read(),y=read(),d=read();
            ins(x,y,d);ins(y,x,d);
        }
        maxx=point=n;
		get_root(1,0);
        ans=0;solve(root);
        printf("%d\n",ans);
        n=read();k=read();
    }
    return 0;
}
```
------------
------------

**updated on 2020.10.7**：可以不用容斥原理修正答案，只需要让这棵子树和前面的子树拼，即可避免两个点都在一棵子树中的情况，不过对于 dis 数组的排序要稍微注意，具体看注释：（只有 calc 函数不同）

------------
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline int mymin(int a,int b) {return a<b?a:b;}
inline int mymax(int a,int b) {return a>b?a:b;}
inline int read()
{
	int x=0;bool f=false;
	char ch=getchar();
	while(ch<'0' || ch>'9') f|=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	return f?-x:x;
}
const int N=10010;
struct edge{int y,d,next;}a[N<<1];int n,limit,len,last[N];
void ins(int x,int y,int d) {a[++len].y=y;a[len].d=d;a[len].next=last[x];last[x]=len;}

int point,root,minn;
int siz[N],smax[N];
bool vis[N];
void get_root(int x,int fa)
{
    siz[x]=1;smax[x]=0;
    for(int k=last[x];k;k=a[k].next)
    {
        int y=a[k].y;
        if(y==fa || vis[y]) continue;
        get_root(y,x);
        siz[x]+=siz[y];
        smax[x]=mymax(smax[x],siz[y]);
    }
    smax[x]=mymax(smax[x],point-siz[x]);
    minn=mymin(minn,smax[x]);
    root=minn==smax[x]?x:root;
}
int num,dis[N];
void dfs(int x,int fa,int Dis)
{
    for(int k=last[x];k;k=a[k].next)
    {
        int y=a[k].y;
        if(y==fa || vis[y]) continue;
        dis[++num]=Dis+a[k].d;
        dfs(y,x,Dis+a[k].d);
    }
}
int dd[N];
int calc(int x)
{
    int ret=0;
    dis[num=1]=0;
    for(int k=last[x];k;k=a[k].next)
    {
        int y=a[k].y;
        if(vis[y]) continue;
        dis[++num]=a[k].d;
        int st=num;
        dfs(y,x,a[k].d);
        sort(dis+st,dis+num+1);//对这棵子树进行排序，不要和之前的打乱成一坨了
        for(int l=1,r=num;l<st && r>=st;)
        {
            if(dis[l]+dis[r]<=limit) ret+=r-st+1,l++;
            else r--;
        }
	    int len=0,i=1,j=st;//因为前面子树的 dis 已经有序，所以直接归并起来即可，用 sort 会 T ！！！
	    while(i<st || j<=num)
	    {
	        if(j>num || (i<st && dis[i]<=dis[j])) dd[++len]=dis[i++];
	        else dd[++len]=dis[j++];
	    }
	    memcpy(dis,dd,sizeof(dis));
    }
    return ret;
}
int ans;
void solve(int x)
{
    vis[x]=true;
    ans+=calc(x);
    for(int k=last[x];k;k=a[k].next)
    {
        int y=a[k].y;
        if(vis[y]) continue;
        minn=point=siz[y];
        get_root(y,x);
        solve(root);
    }
}
void clear()
{
    len=0;memset(last,0,sizeof(last));
    memset(vis,false,sizeof(vis));ans=0;
}
int main()
{
    n=read();limit=read();
    while(n || limit)
    {
        clear();
        for(int i=1;i<n;i++)
        {
            int x=read(),y=read(),d=read();
            ins(x,y,d);ins(y,x,d);
        }
        minn=point=n;
        get_root(1,0);
        solve(root);
        printf("%d\n",ans);
        n=read();limit=read();
    }
	return 0;
}
```

------------
------------
### 总结
**关键的四步操作：**  
+ 1.找出树的重心  
+ 2.求出子节点到树的重心的距离  
+ 3.统计答案（注意容斥）  
+ 4.到各个子树，重复以上操作，把所有情况二转化为情况一解决问题  

点分治的复杂度为 $O(nlog^2n)$，比较优秀qwq

---

## 作者：Hydra_ (赞：3)

# 题面
**题目描述**
给一颗n个节点的树，每条边上有一个距离v（v<=1000）。
定义d(u,v)为u到v的最小距离；
给定k值，求有多少点对（u，v）使u到v的距离小于等于k。
**输入格式**
输入有多组数据，以两个0结尾
每组数据第一行两个整数n，k，n<=10000,k<2^31
接下来n-1行，每行三个整数x,y,v,表示点x到点y有一条边距离是v，v<=1000
**输出格式**
对每组数据一行一个答案。
**input**
5 4
1 2 3
1 3 1
1 4 2
3 5 1
0 0
**output**
8
# 题解
这道题目是一个树分治——点分治的典型例题。
点分治流程：
1、寻找当前[树的重心](http://blog.csdn.net/qq_39670434/article/details/79444249)。
2、处理经过根结点的路径。
3、标记根结点为已访问。
4、递归处理以根节点的儿子为根的每棵子树。
```
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int num=0;
	char c=' ';
	bool flag=true;
	for(;c>'9'||c<'0';c=getchar())
	if(c=='-')
	flag=false;
	for(;c>='0'&&c<='9';num=(num<<3)+(num<<1)+c-48,c=getchar());
	return flag ? num : -num;
}
const int maxn=10021;
int root;
int dcnt=0,ans=0;
//dcnt是存放了dis数组中数据的数量，ans存放了最终统计出来的数量
int now,vis[maxn],dis[maxn],d[maxn];
//now存放了当前子树的规模
//vis[i]代表i是否被访问
//d[i]存放了到根的距离
const int INF=2e9;
int f[maxn],size[maxn];
//这两个数组是用来求树的重心的

	int n,k;
	struct node
	{
		int dot,val,next;
	}a[maxn*2];
	int top=0,head[maxn];
	//邻接表
	void insert(int x,int y,int v)
	{
		top++;
		a[top].dot=y;
		a[top].next=head[x];
		a[top].val=v;
		head[x]=top;
	}
	//插入边


	void dfs(int u,int fa)
	{
		size[u]=1;f[u]=0; 
		for(int i=head[u];i;i=a[i].next)
		{
			int v=a[i].dot;
			if(v==fa||vis[v])continue;
			dfs(v,u);
			size[u]+=size[v];
			f[u]=max(f[u],size[v]);
		}
		f[u]=max(f[u],now-size[u]);
		if(f[u]<f[root])root=u;
	}
	//求树的重心放在变量root里


	void get_dis(int u,int fa)
	{
		if(d[u]>k)return;
		dis[++dcnt]=d[u];
		for(int i=head[u];i;i=a[i].next)
		{
			int v=a[i].dot;
			if(v==fa||vis[v])continue;
			d[v]=d[u]+a[i].val;
			get_dis(v,u);
		}
	}
	int add(int u,int w)
	//u的子树中，如果有两个点i，j
	//满足d[i]+d[j]<k-w的数量
	{
		d[u]=w;dcnt=0;
		get_dis(u,0);
		sort(dis+1,dis+dcnt+1);
		//排序一下，可以直接枚举两个端点，不用一个一个搜索过去
		int l=1,r=dcnt,sum=0;
		while(l<r)
		{
			if(dis[l]+dis[r]<=k)
			{
				sum+=r-l;
				l++;
			}
			else r--;
		}
		return sum;
	}
	void solve(int u)
	{
		ans+=add(u,0);
		vis[u]=1;
		for(int i=head[u];i;i=a[i].next)
		{
			int v=a[i].dot;
			if(vis[v])continue;
			//如果访问过了，就说明该子树已经被解决
			ans-=add(v,a[i].val);
			
			now=size[v];root=0;
			
			dfs(v,0);
			//求子树的重心
			solve(root);
			//子树继续递归解决
		}
	}



void init()
{
	now=n=read();
	k=read();
	while(n&&k)
	{
		memset(vis,0,sizeof vis);
		top=ans=root=0;
		f[0]=maxn;
		memset(head,0,sizeof head);
		for(int i=1;i<n;i++)
		{
			int x=read();
			int y=read();
			int v=read();
			insert(x,y,v);
			insert(y,x,v);
		}
		dfs(1,0);
		solve(root);
		printf("%d\n",ans);
		now=n=read();
		k=read();
	}
}
int main()
{
	init();
	return 0;
}
```

---

## 作者：密期望 (赞：2)

题目要求查询dis(i,j)<=k的点对，即以t为分治重心，访问点i时查询满足k-dis(i,t)<=dis(j,t)的j有多少个就行了，很容易想到把dis(j,t)全部插到平衡树里，然后查询k-dis(i,t)的排名即可。

关于平衡树的码量问题。我觉得一般情况下调一个平衡树并不需要很久，毕竟又不是像[维护数列](https://www.luogu.org/problemnew/show/P2042)那样极其恶心的平衡树，写一个这样的平衡树，在写熟了以后还是很快的。

所以为什么空间要给这么大？64mb足矣。虽然会跑得慢一点，常数大一点，但是访问一个点的复杂度是O(logn)，每个点会被访问O(logn)次，总的复杂度是O(nlog^2n)，跑这个数据是完全没有压力的。

顺便，写了这么久的点分治我才发现我的点分治和大多数人写的模板完全不一样，像去重这种问题我从来没有遇到过，可能我跑得慢也是因为写法原因吧。不过也许在有些情况下我的写法会简化问题，大家也可以参考参考。

代码：
```
#include<cstdio>
typedef long long ll;
typedef long double ld;
const int N=4e4+10;
const int INF=0x3f3f3f3f;
ll read(){
	ll a=0;int op=1;char ch=getchar();
	while(ch<'0'||'9'<ch){if(ch=='-')op=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){a=(a<<3)+(a<<1)+(ch^48);ch=getchar();}
	return a*op;
}
void file(const char *str){
	char in[100],out[100];
	sprintf(in,"%s.in",str),sprintf(out,"%s.out",str);
	freopen(in,"r",stdin),freopen(out,"w",stdout);
}
class set{//常规splay，请忽略。（我知道这样写常数大，我喜欢！你管我？） 
	private:
		struct node{
			int ct;
			int size;
			ll data;
			node *father;
			node *son[2];
			node(ll data_){
				data=data_;
				ct=size=1;
				father=0;
				son[0]=son[1]=0;
			}
			void refresh(){
				size=ct;
				for(int i=0;i<2;i++){
					if(son[i]){
						size+=son[i]->size;
					}
				}
			}
			bool get_relation(){
				return father->son[1]==this;
			}
			void roll(bool mod){
				if(father){
					father->son[get_relation()]=son[mod];
				}
				son[mod]->father=father;
				father=son[mod];
				son[mod]=father->son[!mod];
				if(son[mod]){
					son[mod]->father=this;
				}
				father->son[!mod]=this;
				refresh();
				father->refresh();
			}
			void splay(){
				while(father){
					father->roll(get_relation());
				}
			}
		};
		void destroy(node *p){
			if(!p){
				return;
			}
			destroy(p->son[0]);
			destroy(p->son[1]);
			delete p;
		}
		node *t;
	public:
		set(){
			t=0;
		}
		~set(){
			destroy(t);
			t=0;
		}
		void insert(ll data_){
			if(!t){
				t=new node(data_);
				return;
			}
			bool mod;
			while(1){
				if(t->data==data_){
					t->ct++;
					break;
				}
				mod=t->data<data_;
				if(t->son[mod]){
					t=t->son[mod];
				}else{
					t->son[mod]=new node(data_);
					t->son[mod]->father=t;
					break;
				}
			}
			t->splay();
		}
		int get_rank(ll data_){
			if(!t){
				return 0;
			}
			int ret=0;
			while(1){
				if(t->data<=data_){
					ret+=t->ct;
					if(t->son[0]){
						ret+=t->son[0]->size;
					}
					if(t->son[1]){
						t=t->son[1];
					}else{
						break;
					}
				}else{
					if(t->son[0]){
						t=t->son[0];
					}else{
						break;
					}
				}
			}
			t->splay();
			return ret;
		}
};
//前向星存边 
struct L{
	int to,next;
	ll len;
};
L l[N<<1];
int head[N];
int lcount;
void add(int from,int to,ll len){
	l[++lcount].to=to;
	l[lcount].len=len;
	l[lcount].next=head[from];
	head[from]=lcount;
}
#define REPL(start,i) for(int i=head[start];i;i=l[i].next)if(!vis[l[i].to])//把枚举边define一下，并去掉已经删除的点 
#define LNOF(i) if(l[i].to!=f)//把这个条件也define一下，不要问我为什么 
int root,root_size;//表示在找重心的时候目前的重心和目前重心的最大子树的大小 
int t_size;//表示当前分治的子树的大小 
int size[N];//表示每个子树的大小 
bool vis[N];//表示每个点是否已经被分治过 
set *s;//为了方便delete就使用了指针 
ll ans;//统计答案 
ll k;//见题目 
void get_size(int now,int f){//统计每个子树的大小 
	size[now]=1;
	REPL(now,i)LNOF(i){
		get_size(l[i].to,now);
		size[now]+=size[l[i].to];
	}
}
void get_root(int now,int f){//找重心 
	int maxson=0;//当前节点的子树中中最大子树的大小 
	REPL(now,i)LNOF(i){
		get_root(l[i].to,now);
		if(size[l[i].to]>maxson){
			maxson=size[l[i].to];
		}
	}
	if(t_size-size[now]>maxson){
		maxson=t_size-size[now];
	}
	if(maxson<root_size){
		root=now;
		root_size=maxson;
	}
}
void update(int now,int f,ll dis){//更新set中的信息 
	s->insert(dis);
	REPL(now,i)LNOF(i){
		update(l[i].to,now,dis+l[i].len);
	}
}
void count(int now,int f,ll dis){//统计答案，我的统计方式是没有重复的 
	ans+=s->get_rank(k-dis);
	REPL(now,i)LNOF(i){
		count(l[i].to,now,dis+l[i].len);
	}
}
void divide(int now){
	root=0;
	root_size=INF;
	get_size(now,now);//先得出每个子树的大小 
	t_size=size[now];//因为我们是一now为根dfs的，所以可以直接这样做 
	get_root(now,now);//找重心 
	now=root;
	vis[now]=1;//标记删除重心 
	s=new set();//重建set 
	s->insert(0);//把重心塞进去 
	REPL(now,i){
		count(l[i].to,l[i].to,l[i].len);//先统计答案 
		update(l[i].to,l[i].to,l[i].len);//再把这颗子树中的点加入set中，这样就没有重复 
	}
	delete s;//暴力一点的话可以直接s=0;或者去掉这句话 
	REPL(now,i){
		divide(l[i].to);
	}
}
int n;
//下面的一堆函数都没什么用，主要是考试的时候用这种模板方便调试和使用文件 
void input(){
	n=read();
	int p1,p2,p3;
	for(int i=1;i<n;i++){
		p1=read();
		p2=read();
		p3=read();
		add(p1,p2,p3);
		add(p2,p1,p3);
	}
	k=read();
}
void ini(){
}
void solve(){
	divide(1);
}
void output(){
	printf("%lld",ans);
}
void test(){
	input();
	ini();
	solve();
	output();
}
void all(){
	file("");
	test();
}
int main(){
	test();
	return 0;
}

```

---

## 作者：Jμdge (赞：1)

这道题超级水的说？（结果还是在树状数组维护桶排上面卡住了，做题做傻了）



# noteskey

我们考虑用一个树状数组维护 k-dis 的数量的前缀和就好了

注意每次点分的时候要清空 f 数组

然后就是点分板子咯？还是蛮裸的，争取一遍过

复杂度？ $O(n~ \log ~n ~\log ~k)$

树状数组常数比较小， n 比较小，完全不用担心被卡

# code


```
//by Judge
#include<cstdio>
#include<cstring>
#include<iostream>
#define fp(i,a,b) for(int i=(a),I=(b)+1;i<I;++i)
#define go(G,u) for(int i=G.head[u],v=G.e[i].to;i;v=G.e[i=G.e[i].nxt].to)
#define lowbit(x) (x&-x)
#define ll long long
using namespace std;
const int M=4e4+3;
typedef int arr[M];
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
char buf[1<<21],*p1=buf,*p2=buf;
inline bool cmax(int& a,int b){return a<b?a=b,1:0;}
inline int read(){ int x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
} char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
inline void print(int x,char chr='\n'){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]=chr;
} int n,k,tot,root,ans; arr f,siz,mx,vis;
struct Gr{ int pat,head[M];
	struct Edge{ int to,val,nxt; }e[M<<1];
	inline void add(int u,int v,int w){
		e[++pat]={v,w,head[u]},head[u]=pat;
		e[++pat]={u,w,head[v]},head[v]=pat;
	}
}G;
namespace BIT{ inline void clear(){memset(f,0,k+1<<2);}
	inline void add(int x){ for(;x<=k;x+=lowbit(x)) ++f[x]; }
	inline int ask(int x,int s=0){ for(;x>0;x^=lowbit(x)) s+=f[x]; return s; }
} using namespace BIT;
void get_root(int u,int fa){ siz[u]=1,mx[u]=0;
	go(G,u) if(v^fa&&!vis[v]) get_root(v,u),
		siz[u]+=siz[v],cmax(mx[u],siz[v]);
	cmax(mx[u],tot-siz[u]); if(mx[u]<mx[root]) root=u;
}
void dfs1(int u,int fa,int dis){ if(dis>k) return ; ans+=ask(k-dis);
	go(G,u) if(!vis[v]&&v^fa) dfs1(v,u,dis+G.e[i].val);
}
void dfs2(int u,int fa,int dis){ if(dis>k) return ; add(dis),++ans;
	go(G,u) if(!vis[v]&&v^fa) dfs2(v,u,dis+G.e[i].val);
}
void solv(int u){ clear(),get_root(u,0),u=root,vis[u]=1;
	go(G,u) if(!vis[v]) dfs1(v,u,G.e[i].val),dfs2(v,u,G.e[i].val);
	go(G,u) if(!vis[v]) tot=siz[v],root=0,solv(v);
}
int main(){ n=read(); int x,y,z;
	fp(i,1,n-1) x=read(),y=read(),z=read(),G.add(x,y,z);
	return k=read(),tot=mx[0]=n,solv(1),!printf("%d\n",ans);
}
```


# for more


然后就是考虑一下 c、k 特别大的情况怎么办

我们可以考虑归并排+二分位置（口胡？）

复杂度好像是错的？emmm...这个坑就留给读者啦~（如果想到了请 @ 我，或者私信一下哈）







---

## 作者：ysner (赞：1)

点分治模板题，大部分和模板1是一样的。

然后我天真地把我原来的代码的答案数组求了个前缀和就交了上去。。。T得不要不要的。。。

```
il void getroot(re int u,re int fa)
{
  sz[u]=1;f[u]=0;
  for(re int i=h[u];i;i=e[i].next)
    {
      re int v=e[i].to;
      if(v==fa||vis[v]) continue;
      getroot(v,u);//
      sz[u]+=sz[v];
      f[u]=max(f[u],sz[v]);//f[u]存该点以下最大子树
    }
  f[u]=max(f[u],sum-sz[u]);//肯定儿子要比爸爸多啊
  if(f[u]<f[root]) root=u;
}
il void calc(re int u,re int dd,re int add)
{
  cnt=0;d[u]=dd;
  getdeep(u,0);
  fp(i,1,cnt)
    fp(j,1,cnt)
    ans[o[i]+o[j]]+=add;//时间复杂度过高
}
il void work(re int u)
{
  calc(u,0,1);vis[u]=1;
  for(re int i=h[u];i;i=e[i].next)
    {
      re int v=e[i].to;
      if(vis[v]) continue;
      calc(v,e[i].w,-1);
      sum=sz[v];root=0;
      getroot(v,0);//
      work(root);
    }
}
```
认真分析题目，发现我们在求距离大于k的点对数上花费了大量的时间，并且点对计数用二层循环时间复杂度太高。

所以我们要在优化点对计数数过程下手。

对于根节点进行一次dfs，求出deep，并将其从小到大排序。（longn预处理省一层循环）

避免重复，只需要求出x<y的前提下deep[x]+deep[y]≤k的个数。

用i表示左指针，j表示右指针，i从左向右遍历，j从右向左。

如果deep[i]+deep[j]≤k，则点对(i,t)(i<t≤j)都符合题意，将j-i加入答案中，并且i++；否则j--。

然而这样还会重复计算在同一棵子树中的点对，所以再进行下一步dfs之前需要减去重复部分。

这样就能保证时间复杂度在O(nlog2n)以下。（而不是原来的O（n2long2n)) 

```
il void getroot(re int u,re int fa)
{
  sz[u]=1;f[u]=0;
  for(re int i=h[u];i;i=e[i].next)
    {
      re int v=e[i].to;
      if(v==fa||vis[v]) continue;
      getroot(v,u);//
      sz[u]+=sz[v];
      f[u]=max(f[u],sz[v]);
    }
  f[u]=max(f[u],sum-sz[u]);
  if(f[u]<f[root]) root=u;
}
il int calc(re int u)
{
  cnt=0;getdeep(u,0);sort(o+1,o+cnt+1);
  re int i=1,j=cnt,sum=0;
  while(i<j)
    if(o[i]+o[j]<=k) sum+=j-i,i++;
    else j--;//优化后的点对计数过程
  return sum;
}
il void work(re int u)
{
  d[u]=0;vis[u]=1;ans+=calc(u);
  for(re int i=h[u];i;i=e[i].next)
    {
      re int v=e[i].to;
      if(vis[v]) continue;
      d[v]=e[i].w;
      ans-=calc(v);//去重
      sum=sz[v];root=0;
      getroot(v,0);//重选重心
      work(root);
    }
}
```

---

## 作者：Boxxxxxx (赞：0)

博客链接：[贡献点点击量吧！](https://blog.csdn.net/qq_43804974/article/details/102553812)

这道题目是点分治的题目，与模板题不一样的是，这是要统计小于路径长度为k的点对数。我们分析下与模板题的区别，模板要求的是路径等于k的长度的路径是否存在，然后统计的方法是对于每个重心（根），求出各点与根的路径，然后重心下面的各个子树中，去计算之前非该子树的路径能否凑出k的路径，也就是吧路径分成了（当前子树的路径与非当前子树的路径），然后其实我们也可以利用这个模板题的思想，一旦当前子树的路径与非当前子树的路径能凑出小于k的路径，那么这就是一个就是符合条件的点对，就是，当前子树的距离加上非当前子树的距离一旦小于k就是我们要的一个点对，我们可以对于每种路径的数目去记录一下，就是记录有多少条路径可以达到这个路径数，（因为对于一棵树点与点的距离是一定的，所以去记录路径数是不会算少或者算多点对数目的），所以答案就是加上这个长度路径的点数。

```cpp
		for (register int x = 1; x <= cnt; x++) {
			if (temp[x] > m)continue;
			for (register int y = temp[x]; y <= m; y++)
					ans += judge[y - temp[x]];
		}

```
temp保存的就是当前子树的路径的长度，然后judge[i]就是保存的存在i这条路径的点的数目。我们去枚举[1,k]（代码是有个小优化，因为一些长度是非法的无法更新答案）所有的可能路径，然后去加起来。
这样就足够了吗？并不是，为什么？因为我们算答案只是算了当前子树与非当前子树的路径能不能凑，当前子树的路径我们没去统计，所以其实就是只要在最后，我们把所有judge数组里面[1，k]的点数都加到ans上面去就可以了，因为judge存的就是当前子树的所有路径，然后当前子树只要存在小于k的也就是一个点对。
```cpp
while (!que.empty())
	{
		ans += judge[que.front()];
		judge[que.front()] = 0;
		que.pop();
	}

```
好了如果这样子，他普通的就只有50分，（inline，register，快读乱飞可以达到7,80），因为超时；为什么？我们来看这个统计答案的代码

```cpp
		for (register int x = 1; x <= cnt; x++) {
			if (temp[x] > m)continue;
			for (register int y = temp[x]; y <= m; y++)
					ans += judge[y - temp[x]];
		}

```
这个统计答案是一个平方级别的统计答案，所以爆掉了，怎么优化？我们思考一下，这第二个for算的其实就是
judge[1]+judge[2] + judge[3]+…+judge[m-temp[x]];
这其实就是一个前缀和对不对，然后我们去每次更新judge数组的时候都是单点更新（找到一条路径， 在路径长度的judge下面++）；这里就可以用树状数组或者线段树去优化得答案了，就是一个简单的单点更新区间查询。好了这题就做好了。
（用树状数组wa了4个小数据我也不知道为什么，一改线段树就a）
看起来代码很长~~（线段树太长了！）~~ ，其实都是模板套上去然后稍稍改进下（就只是judge数组从记录边是否存在变成了存在这条边的数目）。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
const long long max_ = 100000 + 7;
const int inf = 1e9 + 7;
inline int read() {
	int s = 0, f = 1;
	char ch = getchar();
	while (ch<'0' || ch>'9') {
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0'&&ch <= '9') {
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * f;
}
int head[max_], xiann = 2, n, m, sum, root, vis[max_], size_[max_], maxpart[max_], judge[max_], temp[max_], dis[max_], cnt = 0, ask[max_], ans = 0;
struct k {
	int next, to, value;
}xian[max_ * 2];
inline void add_(int a, int b, int c) {
	xian[xiann].next = head[a];
	xian[xiann].to = b;
	xian[xiann].value = c;
	head[a] = xiann;
	xiann++;
}
inline void getroot(int now, int fa) {
	size_[now] = 1, maxpart[now] = 0;
	for (register int i = head[now]; i; i = xian[i].next) {
		int to = xian[i].to;
		if (to == fa || vis[to])continue;
		getroot(to, now);
		size_[now] += size_[to];
		maxpart[now] = max(maxpart[now], size_[to]);
	}
	maxpart[now] = max(maxpart[now], sum - size_[now]);
	if (maxpart[root] > maxpart[now])root = now;
}
inline void getdis(int now, int fa) {
	temp[++cnt] = dis[now];
	for (register int i = head[now]; i; i = xian[i].next) {
		int to = xian[i].to;
		if (vis[to] || to == fa)continue;
		dis[to] = dis[now] + xian[i].value;
		getdis(to, now);
	}
}
struct kk {
	int lazy, sum, Lson, Rson;
}tree_[max_ * 4];
void build(int L, int R, int node) {
	tree_[node].Lson = L;
	tree_[node].Rson = R;
	if (L == R) {
		tree_[node].sum = 0;
		tree_[node].lazy = 0;
		return;
	}
	int mid = L + (R - L) / 2, L_tree = node * 2, R_tree = node * 2 + 1;
	build(L, mid, L_tree);
	build(mid + 1, R, R_tree);
	tree_[node].sum = tree_[L_tree].sum + tree_[R_tree].sum;
}
void pushdown_(int node, int vv) {
	tree_[node].lazy += vv;
	tree_[node].sum += tree_[node].lazy * (tree_[node].Rson - tree_[node].Lson + 1);
	tree_[node * 2].lazy += tree_[node].lazy;
	tree_[node * 2 + 1].lazy += tree_[node].lazy;
	tree_[node].lazy = 0;
}

void update(int L, int R, int node, int aimL, int aimR, int vv) {
	if (tree_[node].lazy != 0)pushdown_(node, 0);
	if (L > aimR || R < aimL) return;
	if (L >= aimL && R <= aimR) {
		pushdown_(node, vv);
		return;
	}
	int mid = L + (R - L) / 2, L_tree = node * 2, R_tree = node * 2 + 1;
	update(L, mid, L_tree, aimL, aimR, vv);
	update(mid + 1, R, R_tree, aimL, aimR, vv);
	tree_[node].sum = tree_[L_tree].sum + tree_[R_tree].sum;
}

int askk(int L, int R, int node, int aimL, int aimR) {
	if (tree_[node].lazy != 0)pushdown_(node, 0);
	if (L > aimR || R < aimL) return 0;
	if (L >= aimL && R <= aimR) {
		return tree_[node].sum;
	}
	int mid = L + (R - L) / 2, L_tree = node * 2, R_tree = node * 2 + 1;
	int t1 = askk(L, mid, L_tree, aimL, aimR),
		t2 = askk(mid + 1, R, R_tree, aimL, aimR);
	return t1 + t2;
}
inline void solve(int now) {
	queue<int> que;
	for (register int i = head[now]; i; i = xian[i].next) {
		int to = xian[i].to;
		if (vis[to]) continue;
		dis[to] = xian[i].value;//dis数组是表示到当前根的距离;
		cnt = 0;
		getdis(to, now);
		for (register int x = 1; x <= cnt; x++) {
			if (temp[x] > m)continue;
			ans += askk(1, m, 1, 1, m - temp[x]);
		//	for (register int y = temp[x] + 1; y <= m; y++)
		//		ans += judge[y - temp[x]];
		}

		for (register int x = 1; x <= cnt; x++) {
			if (temp[x] > m)continue;
			que.push(temp[x]);
			judge[temp[x]] += 1;
			update(1, m, 1, temp[x], temp[x], 1);
		}
	}
	while (!que.empty())
	{
		if (que.front() <= m)
			ans += judge[que.front()];
		update(1, m, 1, que.front(), que.front(), -judge[que.front()]);
		judge[que.front()] = 0;
		que.pop();
	}
}
inline void divide(int now) {
	vis[now] = 1;
	solve(now);
	for (register int i = head[now]; i; i = xian[i].next) {
		int to = xian[i].to;
		if (vis[to])continue;
		maxpart[root = 0] = sum = size_[to];
		getroot(to, 0);
		getroot(root, 0);
		divide(root);
	}
}
int main() {
	n = read();
	for (register int i = 2; i <= n; i++) {
		int a = read(), b = read(), c = read();
		add_(a, b, c);
		add_(b, a, c);
	}
	m = read();
	build(1, m, 1);
	maxpart[0] = sum = n;
	root = 0;
	getroot(1, 0);
	getroot(root, 0);
	divide(root);
	printf("%d", ans);
	return 0;
}

```



---

