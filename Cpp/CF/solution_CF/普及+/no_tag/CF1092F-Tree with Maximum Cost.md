# Tree with Maximum Cost

## 题目描述

You are given a tree consisting exactly of $ n $ vertices. Tree is a connected undirected graph with $ n-1 $ edges. Each vertex $ v $ of this tree has a value $ a_v $ assigned to it.

Let $ dist(x, y) $ be the distance between the vertices $ x $ and $ y $ . The distance between the vertices is the number of edges on the simple path between them.

Let's define the cost of the tree as the following value: firstly, let's fix some vertex of the tree. Let it be $ v $ . Then the cost of the tree is $ \sum\limits_{i = 1}^{n} dist(i, v) \cdot a_i $ .

Your task is to calculate the maximum possible cost of the tree if you can choose $ v $ arbitrarily.

## 说明/提示

Picture corresponding to the first example: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1092F/fdd33998ce4716fa490f243f16a780e7d58d0e7e.png)

You can choose the vertex $ 3 $ as a root, then the answer will be $ 2 \cdot 9 + 1 \cdot 4 + 0 \cdot 1 + 3 \cdot 7 + 3 \cdot 10 + 4 \cdot 1 + 4 \cdot 6 + 4 \cdot 5 = 18 + 4 + 0 + 21 + 30 + 4 + 24 + 20 = 121 $ .

In the second example tree consists only of one vertex so the answer is always $ 0 $ .

## 样例 #1

### 输入

```
8
9 4 1 7 10 1 6 5
1 2
2 3
1 4
1 5
5 6
5 7
5 8
```

### 输出

```
121
```

## 样例 #2

### 输入

```
1
1337
```

### 输出

```
0
```

# 题解

## 作者：CreeperK (赞：10)

## Codeforces Round 527 Div.3 F

这题真的没有F的难度。。。

_____

因为超过Div.3的Rating要求，所以这场我没有打，本来是想围观一下有没有__毒瘤数据结构__题（比如2018.12.15的E）的。。。

看到这次的F又是树据结构题（诶？我为什么说又是？），就过来膜拜两下，顺便看看评估一下难度，自己还要几年才能做出这种题。

结果竟然是道二次换根一眼题？！

准确来讲，就是数据稍大一些的[P2986 伟大的奶牛聚集](https://www.luogu.org/problemnew/show/P2986)

那道题可能还稍稍难一点，因为每条边在那道题里有长度。

_____

下面进入正题。

看到本题题意，就是给你一棵无根树，任选一个节点作根，求$\sum dep(i)\times a_i$的最大值。

P2986则是求$\sum dep(i) \times a_i$的最小值。

这有什么区别嘛！完全就是一道双倍经验题（好像说漏嘴了）！

如果把$n$放小一点，$n\le 2000$，可以怎么办？

自然，我们直接枚举每个节点作根，然后一遍$dfs$出解，$n$遍取个最大值就好了。总时间复杂度$O(n^2)$。

但是到了$n\le 200000$的时候，这就无法承受了，肯定要$O(n)$或者$O(nlogn)$。根据我们做这种不带贪心的树的题的常规套路，肯定是$O(n)$，也就是要一遍或两遍$dfs$出解。

先任选一个节点为根。我是直接用1的。

（在此抨击@Parabola使用srand(19260817)的行为）

首先是第一遍DFS。不用想太多，一般就是把子树的权值和求出来。本题还要求一个“费用”，直接一起求掉就好了。

```cpp
void dfs1(int u,int fa){
	s[u]=a[u]; s2[u]=0;
	for(int i=h[u],v;i;i=nex[i]){//链式前向星
		if((v=to[i])==fa)continue;
		dfs1(v,u);
		s[u]+=s[v];
		s2[u]+=s[v]+s2[v];
	}
}
```

其中，s2[u]表示以u为根的子树的费用，s[u]表示子树的权值和。

为什么$s2[u]=s[v]+s2[v]$呢？

因为，每个$v$的子树中的节点在通过$(u,v)$这条边的时候，就会对$u$的答案造成（$s[v]\times dist(u,v)$）的贡献，也就是$s[v]$。因此，$u$的费用比$v$额外多出一个$s[v]$。

第二次应该又如何呢？我们考虑使用父亲的费用（注意，现在开始指的是以这个点为根的整棵树的费用了）去推儿子的费用。

我们把树画成这个样子：

![](https://i.loli.net/2018/12/19/5c1a4ed12d2f6.png)

那么，在“从u走到v”的过程中，以v为根的子树代价减去$s[v]$，而其余所有节点的代价加上$sum-s[v]$。

所以可以写出第二个DFS：

```cpp
void dfs2(int u,int fa,ll sum){
	for(int i=h[u],v;i;i=nex[i]){
		if((v=to[i])==fa)continue;
		dp[v]=(sum+s[u]-s[v])+dp[u]-s[v];
		dfs2(v,u,sum+s[u]-s[v]);
	}
}
```

这里的$sum$就代表$sum-s[v]$。

然后就可以把以所有点为根的树的费用求出来了。最后取个最大值即可。

完整代码如下：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int iz=2e5+5;
typedef long long ll;
int h[iz],to[iz<<1],nex[iz<<1],tot=0;
int n;
ll dp[iz],s[iz],a[iz],s2[iz];
inline void add(int x,int y){to[++tot]=y; nex[tot]=h[x]; h[x]=tot;}
void dfs1(int u,int fa){
	s[u]=a[u]; s2[u]=0;
	for(int i=h[u],v;i;i=nex[i]){
		if((v=to[i])==fa)continue;
		dfs1(v,u);
		s[u]+=s[v];
		s2[u]+=s[v]+s2[v];
	}
}//第一次
void dfs2(int u,int fa,ll sum){
	for(int i=h[u],v;i;i=nex[i]){
		if((v=to[i])==fa)continue;
		dp[v]=(sum+s[u]-s[v])+dp[u]-s[v];
		dfs2(v,u,sum+s[u]-s[v]);
	}
}//第二次
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1,x,y;i<n;i++){
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	dfs1(1,0);
	dp[1]=s2[1];//dp[1]就是s2[1]
	dfs2(1,0,0);
	ll ans=-2e18;
	for(int i=1;i<=n;i++)ans=max(ans,dp[i]);//取最大值
	printf("%I64d",ans);
}
```

我的s2在这里是没必要的~~，我只是偷懒没改而已~~。

谢谢大家！QwQ

---

## 作者：_l_l_ (赞：5)

[题目页面](https://www.luogu.com.cn/problem/CF1092F)

[更好的阅读体验？](https://www.luogu.com.cn/blog/yinjun2024/solution-cf1092f)

这道题我们考虑树形DP中的换根法

首先，我们指定一个根 $1$， 处理出每个节点的深度以及以它为根的子树 $a$ 值的总和。

然后就可以求出 $u = 1$ 时的答案： $\sum\{depth_i*a_i\}$。

接着，我们考虑换根DP，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/0epxy6fd.png)

当根 $u$ 换到根 $v$ 时，以 $v$ 为子树的节点的贡献各减少 1，共减少$size_v$，其余部分的贡献各增加 1，共增加$\sum\{a_i\} - size_v$，因此当节点 $v$ 当根时， $ans_v = ans_u + sum - 2size_v$。

最后的答案就是 $\max\{ans_u\}$。

代码：
```cpp
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
const int MAXN = 1000001;
int depth[MAXN], size[MAXN], dp[MAXN];
int n, QwQ;
int a[MAXN];
struct edge {
	int to, nxt;
} edges[MAXN * 2];
int head[MAXN], tot;
void add(int u, int v) {
	edges[++tot].to = v;
	edges[tot].nxt = head[u];
	head[u] = tot;
}
void dfs1(int x, int fa, int dep) {
	depth[x] = dep;
	size[x] = a[x];
	for (int i = head[x]; i; i = edges[i].nxt) {
		int v = edges[i].to;
		if (v == fa) continue;
		dfs1(v, x, dep + 1);
		size[x] += size[v];
	}
}
void dfs2(int x, int fa) {
	if (x != 1) dp[x] = dp[fa] + QwQ - size[x] - size[x];
	for (int i = head[x]; i; i = edges[i].nxt) {
		int v = edges[i].to;
		if (v == fa) continue;
		dfs2(v, x);
	}
}
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		QwQ += a[i];
	}
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%lld %lld", &u, &v);
		add(u, v);
		add(v, u);
	}
	dfs1(1, 0, 0);
	for (int i = 1; i <= n; i++) {
		dp[1] += depth[i] * a[i];
	}
	dfs2(1, 0);
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		ans = max(ans, dp[i]);
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：qiyue7 (赞：2)

给个动态点分做法 优点是做法比较无脑  缺点是分类讨论细节很多。

~~静态点分没有很好的想法所以就直接离线转在线做了（~~


题目中的式子我们直接拆解，则问题转化为：给n（n<=200000）个询问  每一组询问给出一个树上点，求点到树中所有其他点的  距离 * 点权和  最后输出所有询问的最大值。 那我们先把套板子把点分树实化出来然后在线O（log n） 在线回答每组询问即可   

~~点分处理信息的过程就是大型分类讨论~~
 
总复杂度6*nlogn跑满 

AC代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 220000 + 1;
const int MAXG = MAXN * 2 + 1;
const int MAX_LOG = 19;
const int inf = 0x3f3f3f3f;
int n, q;
 
struct Edge {
    long long v, w;
 
    Edge(int v, int w) : v(v), w(w) {}
};
 
std::vector<Edge> edge[MAXN], g[MAXG];
int a[MAXN];
int tot;
 
inline void addEdge(int u, int v, int w) {
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
}
 
inline void binarize(int u, int pre)
{
    static std::vector<Edge *> now;
    now.clear();
    for (auto &p : edge[u])
        if (p.v != pre) now.push_back(&p);
    int o = u;
    for (int i = 0; i < (int)now.size(); i++) {
        addEdge(o, now[i]->v, now[i]->w);
        if (now.size() - i > 2) {
            addEdge(o, ++tot, 0);
            o = tot;
        }
    }
    for (auto &p : edge[u])
        if (p.v != pre) binarize(p.v, u);
}
 
bool vis[MAXG], vis2[MAXG];
long long sz[MAXG], idx[MAXG], dep[MAXG], fa[MAXG], weight[MAXG];
long long dis[MAXG][MAX_LOG];
long long trans[MAXG][3],sz2[MAXG][3],trans2[MAXG][3];
 
void dfsSize(int u, int pre) {
    sz[u] = 1;
    for (auto &p : g[u]) {
        if (!vis[p.v] && p.v != pre) {
            dfsSize(p.v, u);
            sz[u] += sz[p.v];
        }
    }
}
 
int get(int u, int pre, int n) {
    for (auto &p : g[u])
        if (!vis[p.v] && p.v != pre && sz[p.v] > n) return get(p.v, u, n);
    return u;
}
 
void dfs(int u, int pre, int d, int kk) {
    for (auto &p : g[u]) {
        if (!vis[p.v] && p.v != pre) {
            idx[p.v] = idx[u];
            dis[p.v][kk] = dis[u][kk] + p.w;
            if (p.v <= n)
            {
                trans[d][idx[p.v]] += dis[p.v][kk]*weight[p.v];
                trans2[d][idx[p.v]] += weight[p.v];
                sz2[d][idx[p.v]]++;
            }
            dfs(p.v, u, d, kk);
        }
    }
}
 
void build(int u, int d, int f)
{
    dfsSize(u, 0);
    vis[u = get(u, 0, sz[u] / 2)] = true;
    fa[u] = f;
    dep[u] = d;
    int c = 0;
    for (auto &p : g[u]) {
        if (!vis[p.v]) {
            dis[p.v][d] = p.w;
            idx[p.v] = c++;
            if (p.v <= n)
            {
                sz2[u][idx[p.v]]++;
                trans[u][idx[p.v]] += p.w*weight[p.v];
                trans2[u][idx[p.v]] += weight[p.v];
            }
            dfs(p.v, u, u, d);
            build(p.v, d + 1, u);
        }
    }
}
long long L, R;
long long query(int cur, int kk, int id)
{
    if (!cur)
        return 0;
    long long  cur_ans = 0;
    int p = 0;
    for (int i = 0; i < 3; ++i)
        if (id != i)
            cur_ans +=trans[cur][i]+trans2[cur][i]*dis[kk][dep[cur]],p+=sz2[cur][i];
    if (cur != kk)
    {
        if (cur <= n)
            cur_ans += dis[kk][dep[cur]] * weight[cur];
    }
    return cur_ans+query(fa[cur], kk, idx[cur]);
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int  u, v, w, a, b, q, kk;
    cin >> n;
    memset(trans, 0, sizeof(trans));
    for (int i = 1; i <= n; ++i)
        cin >> weight[i];
    for (int i = 0; i < n - 1; ++i)
    {
        cin >> u >> v;
        edge[u].push_back({ v,1 });
        edge[v].push_back({ u,1 });
    }
    int opt;
    tot = n;
    binarize(1, 0);
    build(1, 1, 0);
    long long Max = 0;    
    for (int i = 1; i <= n; ++i)
    {
        Max = max(Max, query(i, i, -1));
    }
    cout << Max << endl;
    
    return 0;
}
```



---

## 作者：Erusel (赞：1)

校内做过一道加强版，就是让你求 $min{\sum_{i=1}^{n} dist(i,v)^2*a_i}$

思路其实差不多，就是暴力换根dp，我们考虑记录每一个节点的子节点的权值总和，记作 $s_i$

用 $f_v$ 记录 $\sum_{i=1}^{n} dist(i,v)^2*a_i$

在换根的时候，假设 $u->v$ 有一条边，$f_v=f_u-s_v+sum-s_v$

其中 $sum$ 表示 $\sum_{i=1}^n a_i$，注意要先算出 $f_1$ 的值才能开始换根

**Code:**

```cpp
#include<bits/stdc++.h>

#define rd(x) x=read()

#define N 200005
#define int long long

using namespace std;

int n,m;
vector<int>e[N];
int a[N],s[N],f[N],t[N];//t[N]用来计算f[1]

inline void addEdge(int u,int v){e[u].push_back(v);}

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

inline void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}

int ans,sum;

void dfs(int u,int fa)
{
    s[u]=a[u];
    for(int i=0;i<e[u].size();i++)
    {
        int v=e[u][i];
        if(v==fa)continue;
        dfs(v,u),t[u]+=t[v]+s[v],s[u]+=s[v];
	}
}

void dfss(int u,int fa)
{
    for(int i=0;i<e[u].size();i++)
    {
        int v=e[u][i];
        if(v==fa)continue;
        f[v]=f[u]-s[v]+sum-s[v],dfss(v,u);
	}
}

signed main()
{
    rd(n);
    for(int i=1;i<=n;i++)rd(a[i]),sum+=a[i];
    for(int i=1,u,v;i<n;i++)rd(u),rd(v),addEdge(u,v),addEdge(v,u);
    dfs(1,0),f[1]=t[1],dfss(1,0);for(int i=1;i<=n;i++)ans=max(ans,f[i]);
    cout<<ans<<endl;
    
    
    return 0;
}
```

---

## 作者：lgswdn_SA (赞：0)

套路的换根，熟悉的配方……

如果没有点权 $a_i$，那么这题就是 [一道绿题](https://www.luogu.com.cn/problem/P3478)。

现在有了点权 $a_i$。第一次 dfs 我们需要维护 $s_u$ （子树点权和），$d_u$ （深度）和 $f_u$ （子树的 $\sum dist$）。第二次 dfs 我们算出 $g_u$ （$u$ 为根时的答案） 。

其中对于第二次 dfs 种计算 $ans$ 的部分，ans 从 u 转到 v，$v$ 子树内部做出的贡献减少了，$v$ 子树外部做出的贡献减少了，所以总体来说，$ans_v=ans_u-s_v+(sum-s_v)$，即 $ans_v=ans_u+sum-2s_v$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+9;
struct edge {int to,nxt;}e[N*2]; int hd[N],tot;
void add(int u,int v) {e[++tot]=(edge){v,hd[u]};hd[u]=tot;}

int n,a[N],sum;

int s[N],f[N],d[N];
void dfs1(int u,int fa){
	s[u]=a[u];
	for(int i=hd[u],v;i;i=e[i].nxt) {
		if((v=e[i].to)==fa) continue;
		d[v]=d[u]+1;
		dfs1(v,u);
		s[u]+=s[v], f[u]+=(f[v]+s[v]);
	}
} 

int ans[N],anss;
void dfs2(int u,int fa){
	if(u==1) ans[u]=f[u];
	for(int i=hd[u],v;i;i=e[i].nxt){
		if((v=e[i].to)==fa) continue;
		ans[v]=ans[u]+sum-2*s[v];
		dfs2(v,u);
	}
	anss=max(anss,ans[u]);
}

signed main() {
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]), sum+=a[i];
	for(int i=1,u,v;i<n;i++)
		scanf("%lld%lld",&u,&v),
		add(u,v), add(v,u);
	dfs1(1,0), dfs2(1,0);
	printf("%lld",anss);
	return 0;
} 
```

---

## 作者：Treaker (赞：0)

这道题呢，用换根DP来做。

我们考虑对于每个点来求出这个点的贡献是多少。

那么，分为子树内的部分和子树外的部分。

两部分大致相同。以子树内的部分为例。

我们设$sum_i$表示子树内的总贡献是多少，那么考虑从儿子转移而来，贡献就是这个儿子的sum加上子树内的$a_i$和，因为经过了一条边，所有的$a_i$应该都加一次。

那么对于每个点维护子树内的贡献和子树内的$a_i$和即可。

子树外的情况差不多类似。

详见代码：
```cpp
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
namespace IO
{
	char buf[1 << 20 | 1] , *f1 = buf , *f2 = buf , pbuf[1 << 24 | 1] , *f3 = pbuf , sta[100];
	#define gc() ((f1 == f2) && (f2 = (f1 = buf) + fread(buf,1,sizeof buf,stdin),f1 == f2) ? EOF : *f1 ++)
	#define gt() getchar()
	inline int read()
	{
		int x = 0 , f = 1; char ch = gt();
		while(ch < '0' || ch > '9')	{if(ch == '-')	f = -1; ch = gt();}
		while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = gt();}
		return x * f;
	}
	template <class T> inline void write(T x)
	{
		if(!x) return (void)(*f3 ++ = 48 , *f3 ++ = ' ');
		if(x < 0) *f3 ++ = '-' , x = ~x + 1;
		char *top = sta;
		while(x) *top ++ = x % 10 + 48 , x /= 10;
		while(top != sta) *f3 ++ = *-- top;
		*f3 ++ = ' ';
	}
	inline void put(std::string s)
	{
		int len = s.length();
		for(int i = 0;i < len;i ++) *f3 ++ = s[i];
		*f3 ++ = ' ';
	}
	inline void endline() { *f3 ++ = '\n';}
	#define flush() fwrite(pbuf,1,f3 - pbuf,stdout)
	template <class T> inline T abs(T a) { return a < 0 ? -a : a;}
	template <class T> inline T max(T a,T b) { return a > b ? a : b;}
	template <class T> inline T min(T a,T b) { return a < b ? a : b;}
	template <class T> inline void swap(T &a,T &b) { T t = a; a = b; b = t;}
}
using namespace IO;
const int N = 2e5 + 5;
int n;
ll size[N] , sum[N] , S[N] , s[N];
struct Edge
{
	int to; Edge *nxt;
	Edge(int to = 0,Edge *nxt = NULL) : to(to) , nxt(nxt) { }
} *head[N] , pool[N << 1] , *tail = pool;
inline void add(int u,int v) { head[u] = new (tail ++) Edge(v,head[u]);}
void dfs1(int x,int fa)
{
	for(Edge *i = head[x];i;i = i -> nxt)
	{
		int to = i -> to;
		if(to == fa) continue;
		dfs1(to,x);
		size[x] += size[to];
		sum[x] += sum[to] + size[to];
	}
}
void dfs2(int x,int fa)
{
	for(Edge *i = head[x];i;i = i -> nxt)
	{
		int to = i -> to;
		if(to == fa) continue;
		s[to] = s[x] + size[x] - size[to];
		S[to] = S[x] + sum[x] - sum[to] - size[to] + s[to];
		dfs2(to,x);
	}
}
int main()
{
	n = read();
	for(int i = 1;i <= n;i ++) size[i] = read();
	for(int i = 1 , u , v;i < n;i ++) u = read() , v = read() , add(u,v) , add(v,u);
	dfs1(1,0); dfs2(1,0); ll ans = 0;
	for(int i = 1;i <= n;i ++) ans = max(ans,sum[i] + S[i]);
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Kendrick_Z (赞：0)

换根DP裸题？

题解淀粉质真的神仙 orz

何谓换根DP？

摘自lyd的进阶指南：

1.第一次扫描时，任选一个点为根，再“有根树”上执行一次**树形DP**，也就是回溯时发生的 自底向上的状态转移

2.第二次扫描时，从刚才任选的根出发，对整棵树执行一次**深度优先遍历**，在，每次递归钱进行自顶向下的推导，计算出换根后的新解

套路比较明显

来看这道题 要求我们选择一个点 使得其他点的深度乘权值之和最大

我们先以一号点为根然后进行预处理 求出来子树的权值和 以及1号节点为根的DP值

考虑第二次扫描

当我们枚举到u-v这条边时 图被分成两部分 画图很显然可得 u节点所在的部分深度都+1 v节点所在深度都-1

所以DP方程呼之欲出：

f[v]=f[u]+sum-size[v]-size[v]


O(n)DFS即可

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+10;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar(); 
	}
	return x*f;
}
int n,head[N],cnt;
ll siz[N],sum,f[N],ans=0,a[N],dep[N];
struct edge{
	int nxt,to;
}e[N<<1];
inline void add(int x,int y){
	e[++cnt].nxt=head[x];
	e[cnt].to=y;
	head[x]=cnt;
}
inline void dfs1(int x,int fa){
	siz[x]=a[x];
	for(int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa) continue;
		dep[v]=dep[x]+1;
		f[1]=f[1]+(ll)(a[v]*dep[v]);
		dfs1(v,x);
		siz[x]+=siz[v];
	} 
}
inline void dfs2(int x,int fa){
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==fa) continue;
		f[y]=f[x]+sum-siz[y]-siz[y];
		dfs2(y,x);
	}
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		sum+=a[i];
	}
	for(int i=1;i<n;i++){
		int u,v;
		u=read(),v=read(); 
		add(u,v);
		add(v,u);
	}
	dfs1(1,0);
	dfs2(1,0);
	for(int i=1;i<=n;i++){
		ans=max(f[i],ans);
	}
	printf("%lld",ans);
	return 0; 
}
```

记得long long！



---

## 作者：Zechariah (赞：0)

我们考虑设x为根，现在已经求出了x为根时候的答案ans，能不能在O(1)的时间内得到k(x->k)为根的答案呢？  
当前根为x，如果根“下移”到k，那么显然根到k子树内的所有点距离都-1，答案其实就减掉了k子树内的点权和，而不是k子树内的点到根的距离都+1，答案就要加上除了k子树以外的点权和  
那做法就很明显了，先设1为根，预处理出每一个子树的点权和，然后从1开始dp推出所有答案，取最大值
```cpp
#include <bits/stdc++.h>
#define rg register
#define inl inline
typedef long long ll;
#define jh(x,y) (x^=y^=x^=y)
#define lowbit(x) (x&-x)
const double PI = 3.1415926535898, eps = 0;
const int N = 4e5 + 10, mod = 998244353;
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
    long long modread()
    {
        rg long long num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) >= '0'&&ch <= '9')
            (num = (num << 1) + (num << 3) + (ch ^ 48)) %= mod;
        if (flag)return -num; return num;
    }
    double dread()
    {
        rg double num = 0, mi = 1;
        rg char ch;
        rg bool flag = false, point = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
        {
            if (ch == '.')point = true;
            else if (point)num += (ch ^ 48)*(mi *= 0.1);
            else num = num * 10 + (ch ^ 48);
        }
        if (flag)return -num; return num;
    }
    char cread()
    {
        rg char ch;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        return ch;
    }
    int chread(rg char s[])
    {
        rg char ch;
        rg int len = 0;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        s[len++] = ch;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            s[len++] = ch;
        s[len] = 0;
        return len;
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
    int getnumd(rg int num, ...)
    {
        va_list vl;
        va_start(vl, num);
        for (rg int i = 0; i != num; ++i)
            if ((*va_arg(vl, double*) = dread()) == -1)return EOF;
        return num;
    }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
    inl ll exgcd(rg ll a, rg ll b, rg ll &x, rg ll &y)
    {
        if (b == 0)
        {
            x = 1, y = 0;
            return a;
        }
        rg ll yu = exgcd(b, a%b, x, y);
        rg ll tmp = x; x = y;
        y = tmp - a / b * y;
        return yu;
    }
    inl ll gcd(rg ll a, rg ll b) { while (b ^= a ^= b ^= a %= b); return a; }
    inl ll ksm(rg ll a, rg ll b)
    {
        rg ll ans = 1;
        while (b)
        {
            if (b & 1)(ans *= a) %= mod;
            (a *= a) %= mod;

        }
        return ans;
    }
};
ll v[N], ans, sumv[N];
int nt[N], b[N], p[N], num;
inl void add(rg int x, rg int y)
{
    b[++num] = y, nt[num] = p[x], p[x] = num;
    b[++num] = x, nt[num] = p[y], p[y] = num;
}
inl void dfs1(rg int x, rg int fa, rg ll dep)
{
    sumv[x] = v[x]; ans += dep * v[x];
    for (rg int e = p[x]; e; e = nt[e])
    {
        rg int k = b[e];
        if (k == fa)continue;
        dfs1(k, x, dep + 1);
        sumv[x] += sumv[k];
    }
}
inl void dfs2(rg int x, rg int fa, rg ll sum)
{
    ans = fast_IO::max(ans, sum);
    for (rg int e = p[x]; e; e = nt[e])
    {
        rg int k = b[e];
        if (k == fa)continue;
        dfs2(k, x, sum + sumv[1] - sumv[k] * 2);
    }
}

int main()
{
    rg int n = fast_IO::read();
    for (rg int i = 1; i <= n; ++i)v[i] = fast_IO::read();
    for (rg int i = 1; i != n; ++i)add(fast_IO::read(), fast_IO::read());
    dfs1(1, 0, 0), dfs2(1, 0, ans);
    fast_IO::write(ans);
    return 0;
}

```

---

