# [AGC034E] Complete Compress

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc034/tasks/agc034_e

頂点に番号 $ 1,\ 2,\ ...,\ N $ がついた $ N $ 頂点の木が与えられます。$ i $ 番目の辺は頂点 $ a_i $ と頂点 $ b_i $ を結んでいます。 また長さ $ N $ の `0`, `1` からなる文字列 $ S $ が与えられ、$ S $ の $ i $ 文字目は頂点 $ i $ に置いてあるコマの個数を表しています。

すぬけ君は、以下の操作を好きなだけ行います。

- 距離が $ 2 $ 以上離れたコマ $ 2 $ 個を選び、お互いに $ 1 $ ずつ近づける。 正確に述べると、コマの置かれた頂点 $ u,\ v $ を選び、$ u,\ v $ 間の最短パスを考える。ここでパスの辺数が $ 2 $ 以上となるように選ぶことにする。パスにおいて $ u $ に隣り合う頂点にコマを $ 1 $ 個 $ u $ から動かし、$ v $ に隣り合う頂点にコマを $ 1 $ 個 $ v $ から動かす。

すぬけ君はこれを繰り返し、すべてのコマを同じ頂点に集めたいです。このようなことは可能でしょうか？ 可能な場合、それを達成するのに必要な操作の最小回数も求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2000 $
- $ |S|\ =\ N $
- $ S $ は `0`, `1`からなり、また少なくとも $ 1 $ 文字は `1` を含む
- $ 1\ \leq\ a_i,\ b_i\ \leq\ N(a_i\ \neq\ b_i) $
- 辺 $ (a_1,\ b_1),\ (a_2,\ b_2),\ ...,\ (a_{N\ -\ 1},\ b_{N\ -\ 1}) $ は木をなす

### Sample Explanation 1

\- 頂点 $ 3,\ 5 $ のコマを選ぶ - 頂点 $ 2,\ 7 $ のコマを選ぶ - 頂点 $ 4,\ 6 $ のコマを選ぶ の $ 3 $ 回の操作ですべてのコマを頂点 $ 1 $ に集めることができます。

## 样例 #1

### 输入

```
7
0010101
1 2
2 3
1 4
4 5
1 6
6 7```

### 输出

```
3```

## 样例 #2

### 输入

```
7
0010110
1 2
2 3
1 4
4 5
1 6
6 7```

### 输出

```
-1```

## 样例 #3

### 输入

```
2
01
1 2```

### 输出

```
0```

# 题解

## 作者：Scintilla (赞：26)

### $\rm I.$ 前言

听冬令营讲课，只有看到这题之后马上想出了一个大概的解法，遂没听讲解敲代码。但是当时没过，今晚再调了一下就过了。这是我 ```AC``` 的第一道集训队作业题，故写一篇题解以纪念。

### $\rm II.$ Solution

看 $n$ 的范围，像是一个 $\Theta(n ^ 2)$ 的做法。

考虑到最后的点只有一个，我们可以枚举它。假设已经固定了节点 $r$ 作为终点，不妨以它为根。

设 $g(u) = \sum\limits_{v \in S_u, col_v = 1} \text{dist}(u, v)$，这里 $S_u$ 表示以 $u$ 为根的子树，那么一次操作后 $g(r)$ 要么不变，要么减少 $2$。为了求得最少的次数，我们当然要选择后者。同时经过手玩可以发现，使 $g(r)$ 不变的操作对最后的结果是没有影响的。细想一下，使 $g(r)$ 不变的操作所选的两个点肯定在 $r$ 的同一棵子树内，而没有合法方案的原因肯定是 $g(r)$ 是奇数或者 $r$ 的子树之间的黑点数量太不平衡。

所以我们考虑递归解决这个问题。设 $f(u)$ 为以 $u$ 为根的子树内通过一系列操作 $g(u)$ 能够达到的最小值。由上讨论可知每次 $g(u)$ 减小肯定是由其两棵子树的节点相抵消的，这要求 $f(v)$ 不能太大（$v$ 是 $u$ 的一个儿子）。

具体地，设 $sz_u$ 表示以 $u$ 为根子树内棋子的个数，那么 $sz_u = [col_u = 1] + \sum sz_v$，其中 $v$ 是 $u$ 的儿子。的如果在操作之前 对于 $\forall v \in S_u, f_v + sz_v < g_u - g_v - sz_v$，这代表着任意一棵子树在一系列操作后都能不超过总和的一半，所以可以抵消至不能操作，$f_u$ 即为 $g(u)$ 的奇偶性。反之，$f_u$ 即为 $f_v + sz_v - (g_u - g_v - sz_v)$，因为 $v$ 的子树内 $g$ 最小时 $u$ 的 $g$ 才能取到最小。

枚举 $1, 2, \cdots, n$ 为终点，这个问题就被我们解决了， 时间复杂度 $\Theta(n^2)$。

### **能不能再给力一点啊？**

对于这种问题，有一种奇妙的技巧叫做换根 ```dp```，没学过的建议出门左转[换根 dp 板子题](https://www.luogu.com.cn/problem/P3478)。

我们能否把它用在这个题目上呢？

对于一个节点 $u$，设它原来的父亲为 $fa$。如果以它为根，它的子树就比第一次多了一个，那就是以 $fa$ 为根的不在 $S_u$ 中的点组成的子树，我们只需要处理出这棵树的距离的最大和最小值。而这棵树又可以看作 $S_{fa}$ 被挖去了以 $u$ 为根的子树和添上了除去 $S_{fa}$ 的其他点。所以我们还需要对于每个点 $u$ 预处理 $f_v + g_v + 2sz_v$ 的最大值和次大值。这样的话那么现在转移的方程已经比较显然了，只是细节由有亿点多，~~感兴趣的读者可以自行推导。~~ 时间复杂度 $\Theta(n)$。

我知道我讲的不清楚，所以读者可以结合代码理解。毕竟这个题目也是我目前为止调的最久的题目之一了。我相信只要你自己想出了这个题的 $\Theta(n)$ 的解法，你对换根 ```dp``` 的掌握程度会上一个新台阶。

~~代码中的变量和数组名与题解中有亿点不同~~，题解中的 $f$ 数组是代码中的 $downf$，题解中的 $g$ 是代码中的 $down$，$up_u$ 是 $\sum\limits_{v \not\in S_u, col_v = 1}\text{dist}(u, v)$，$f$ 数组变成了整棵树除去 $S_u$ 中非 $u$ 的节点以 $u$ 为根时的最小距离和，$Ans_u$ 是以 $u$ 为根时最终的答案， $sz_u$ 是初始时 $S_u$ 中棋子的数量，$g_u$ 则变成了 $\sum\limits_{col_v = 1} \text{dist}(u, v) = up_u + down_u$。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define il inline
#define re register
#define Rep(i, s, e) for (re int i = s; i <= e; ++i)
#define Dep(i, s, e) for (re int i = s; i >= e; --i)
#define file(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout)

const int N = 2000010;

il int read() {
    int x = 0; bool f = true; char c = getchar();
    while (!isdigit(c)) {if (c == '-') f = false; c = getchar();}
    while (isdigit(c)) x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return f ? x : -x;
}

int n;
char s[N];
bool hav[N];

int head[N], tot;
struct node {int nxt, to;} edge[N << 1];
il void adde(int u, int v) {edge[++tot].nxt = head[u], edge[tot].to = v, head[u] = tot;}

int dep[N], down[N], now, downf[N], sz[N], nmax[N][3], g[N], up[N], ans = 0x3f3f3f3f, f[N], Ans[N];

il int upd(int u, int x) {
	if (x > nmax[u][1]) nmax[u][2] = nmax[u][1], nmax[u][1] = x;
	else if (x > nmax[u][2]) nmax[u][2] = x;
}

il int get(int u) {
    return down[u] + downf[u] + 2 * sz[u];
}

void dfs_down(int u, int fa) {
    dep[u] = dep[fa] + 1, sz[u] = hav[u]; int nowmax = 0;
    for (re int e = head[u]; e; e = edge[e].nxt) {
        int v = edge[e].to;
        if (v == fa) continue;
        dfs_down(v, u), down[u] += down[v] + sz[v], sz[u] += sz[v], upd(u, get(v));
    }
    downf[u] = nmax[u][1] > down[u] ? nmax[u][1] - down[u] : down[u] & 1;
}

void dp(int u, int fa) {
    if (u != 1) {
        up[u] = down[fa] - down[u] - sz[u] - sz[u] + up[fa] + sz[1], g[u] = up[u] + down[u];
        int nowmax = max(get(u) == nmax[fa][1] ? nmax[fa][2] : nmax[fa][1], f[fa] + up[fa]), nowg = g[fa] - down[u] - sz[u];
        f[u] = nowmax > nowg ? nowmax - nowg : nowg & 1;
        f[u] += sz[1] - sz[u];
        nowg = g[u], nowmax = max(nmax[u][1], up[u] + f[u]);
        Ans[u] = nowmax > nowg ? nowmax - nowg : nowg & 1;
    }
    for (re int e = head[u]; e; e = edge[e].nxt) {
        int v = edge[e].to;
        if (v == fa) continue;
        dp(v, u);
    }
}

int main() {
    n = read(), dep[0] = -1;
    scanf("%s", s + 1);
    Rep(i, 1, n) hav[i] = (s[i] == '1');
    Rep(i, 2, n) {
        int u = read(), v = read();
        adde(u, v), adde(v, u);
    }
    dfs_down(1, 0);
    if (!downf[1]) ans = down[1] >> 1;
	g[1] = down[1];
    dp(1, 0);
	Rep(i, 2, n) {
		if (!Ans[i]) ans = min(ans, g[i] >> 1);
	} 
    printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
    return 0;
}
```

---

## 作者：little_sun (赞：15)

### 题目大意

有一棵有$n$个节点的树，每个节点上有$0/1$枚棋子，每次可以选择两个棋子并移动到它们的路径上的相邻节点（满足路径长度至少为$2$），求把所有棋子移到同一个节点的最小花费（无解输出$-1$）。

$n \leq 2 \times 10 ^ 3$

### 分析

枚举最后汇聚到的点$\texttt{root}$，并以$\texttt{root}$为根建树

我们可以发现，如果存在一个合法的方案，则必然是每次选择不存在祖先关系的两枚棋子，同时向着他们的$\texttt{lca}$处跳一格，重复若干步，直到所有棋子都在$\texttt{root}$

由此我们联想到一个经典模型：有$\texttt{sum}$个节点被分成了若干个集合，每次要找到不在同一集合的两个节点匹配并抵消。

设$\texttt{max}$为最大的集合的大小，则当$sum - max \geq max$时，刚好可以消去$\lfloor \frac{sum}{2} \rfloor$对节点

否则剩下$2 \times max - sum$个来自最大集合的节点，消去了$sum - max$对

现在我们回到原问题，考虑在$u$处做这个操作，设$f_u$表示在$u$的子树里最多消去了多少对。

我们把所有$u$的子树内的有棋子的节点$v$拆成$dis(v, \; u)$个节点，则我们有如下转移（仍然设$\texttt{sum}$为总结点个数，$\texttt{max}$为最大的集合的大小）

- $sum - max \geq max$ ，此时$f_u=\lfloor \frac{sum}{2} \rfloor$

- $sum - max < max$，此时需要最大子树$v$内的节点来抵消，此时$f_u=sum-max+ \min (f_v, \lfloor \frac{2 \times max - sum}{2} \rfloor )$

以$\texttt{root}$为根的情况合法当且仅当$f_{root} = \frac{\Sigma_u dis(u, root)}{2}$，同时这也是以$\texttt{root}$为根的答案

对$\texttt{root}=1 - n$重复这个$\texttt{dp}$过程，时间复杂度$\texttt{O(}n^2\texttt{)}$

### 代码

``` cpp
#include <bits/stdc++.h>

#define R register
#define ll long long
#define sum(a, b, mod) (((a) + (b)) % mod)

const int MaxN = 1e4 + 10;
const int inf = 0x3f3f3f3f;

struct edge
{
    int next, to;
};

char s[MaxN];
edge e[MaxN];
int n, ans, cnt;
int a[MaxN], head[MaxN], dis[MaxN], size[MaxN], f[MaxN];

void init()
{
    for (int i = 1; i <= n; i++)
        dis[i] = size[i] = f[i] = 0;
}

void add_edge(int u, int v)
{
    ++cnt;
    e[cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}

inline int read()
{
    int x = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0')
        ch = getchar();
    while (ch <= '9' && ch >= '0')
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return x;
}

void dfs(int u, int fa)
{
    size[u] = a[u];
    int maxp = 0;
    for (int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].to;
        if (v == fa) continue;
        dfs(v, u), size[u] += size[v], dis[v] += size[v];
        dis[u] += dis[v], maxp = ((dis[maxp] > dis[v]) ? maxp : v);
    }    
    if(!maxp) return (void) (f[u] = 0);
    if(dis[u] >= 2 * (dis[maxp])) f[u] = (dis[u] / 2);
    else f[u] = dis[u] - dis[maxp] + std::min(f[maxp], (2 * dis[maxp] - dis[u]) / 2);
}

int main()
{
    ans = inf;
    n = read(), scanf("%s", s + 1);
    for (int i = 1; i <= n; i++)
        a[i] = s[i] - '0';
    for (int i = 1; i < n; i++)
    {
        int u = read(), v = read();
        add_edge(u, v), add_edge(v, u);
    }
    for (int i = 1; i <= n; i++)
    {
        init(), dfs(i, 0);
        if(dis[i] & 1) continue;
        if (f[i] * 2 >= dis[i]) ans = std::min(ans, dis[i] / 2);
    }
    printf("%d\n", (ans == inf) ? -1 : ans);
    return 0;
}
```

---

## 作者：shinkuu (赞：8)

虽然做法大致相同，但是本篇题解将会讲述**如何想出正解**，分享我的思路。望通过。

首先看到题目，容易想到一个简单很多的情况：在一条链上，且终点确定。此时就可以把终点两边的点分开，分别计算到终点的距离之和，看是否相等即可。

没有确定终点时，枚举一个终点即可。

考虑将这种做法带入本题。先 $O(n)$ 枚举终点，然后会发现，这其实是一个判定问题：如果可以全部到终点，那么答案就是 $\dfrac{\sum_{c_i=1}dep_i}{2}$。这一点下面会证明。$c_i$ 表示点 $i$ 上是否有棋子。

此时发现没什么突破口，于是开始找性质。我们称一个棋子 $x$ 和 $y$ 向他们中心，向上移动为 $x$ 被 $y$ 拉起来。

**Lemma 1：用一个 $x$ 的祖先拉起它是没有意义的。**

Proof：首先，进行这样的操作之后 $dep$ 之和是不变的，所以不会使答案更小。那么使这个操作有意义，就只有一种可能：它让 $x$ 点被拉起来的机会增加了。

经过思考可以发现，$x$ 被拉上去是不会使机会增加的，因为这只可能会增加和他互为祖先后代关系的点的数量。而没有这种的点对很明显是更好地将两个点都拉起来的。

**Lemma 2：如果只考虑以 $x$ 为根的子树内的点能不能被拉到根，优先找子树内的两个点操作是更优的。**

Proof：如果先找一个子树外的点和一个子树内的点操作，可能子树内原有 $(x,y)$ 是有意义的操作，操作后就不是了。

再回到题目，由于 Lemma 2，我们是从一个子树再向外操作，很容易想到树形 dp。问题就在于怎样定义状态。

考虑记录经过若干次操作，子树内棋子到根 $dep$ 之和。但是此时 $dep$ 之和最小不一定是最优的，因为我们可能需要用这些点去拉起来子树外的点，所以考虑记录一个范围 $[f_u,g_u]$。容易发现，这个范围内奇偶性与端点相同的值都是可以取到的。

$g_u$ 的转移是 naive 的，~~因为写太久了~~所以不作讲解。对于 $f_u$ 的转移，我们一定是想办法尽量拉上来现在最深的点，其他就好办了。则我们要让最深的点尽可能靠近根。设 $siz_u$ 为 $u$ 子树内棋子数，$mx$ 为 $\max f_v+siz_v$。那其他点也尽可能深，但是不超过最深的，这样更有可能拉上来最深的点。则记 $s=\sum\min(g_v+siz_v,mx)$，如果 $s\ge 2\times mx$，那么显然是可以把所有点拉到根的，但是 $g_u\bmod 2=1$ 时例外，$\sum dep_i$ 最小为 $1$，否则 $f_u=2\times mx-s$。判断 $f_{rt}$ 是否为 $0$ 即可。

总复杂度 $O(n^2)$。

code：

```cpp
int n,m,c[N],siz[N];
ll f[N],g[N];
char s[N];
int tot,head[N];
struct node{int to,nxt;}e[N<<1];
il void add(int u,int v){e[++tot]={v,head[u]},head[u]=tot;}
void dfs(int u,int fa){
	siz[u]=c[u];
	ll s=0,mx=0;
	go(i,u){
		int v=e[i].to;
		if(v==fa)continue;
		dfs(v,u);
		mx=max(mx,f[v]+siz[v]);
		g[u]+=g[v]+siz[v];
		siz[u]+=siz[v];
	}
	go(i,u){
		int v=e[i].to;
		if(v==fa)continue;
		s+=min(g[v]+siz[v],mx);
	}
	if(s>=2*mx)f[u]=g[u]&1;
	else f[u]=2*mx-s;
}
void Yorushika(){
	scanf("%d%s",&n,s+1);
	rep(i,1,n-1){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	rep(i,1,n)c[i]=s[i]-'0';
	ll ans=1ll*inf*inf;
	rep(i,1,n){
		mems(f,0),mems(g,0);now=i;
		dfs(i,0);
		if(!f[i])ans=min(ans,g[i]/2);
	}
	printf("%lld\n",ans>1e15?-1:ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：justin_cao (赞：6)

首先枚举聚集点，然后考虑如何判断合法。

考虑设$mx[i]$为以$i$为根的子树内的棋子到它的距离之和，设$mn[i]$为以$i$为根的子树内的棋子到它的距离之和的最小值（就是说子树内操作后），设$size[i]$为以$i$为根的子树内的棋子数量。

$mx,size$都好求，考虑$mn$如何求。

假设当前要求$mn[x]$，现在找到了$mx$最大的一个点$p$。

那么如果$mx[p]\leq mx[x]-mx[p]$，也就是说假设所有的子树都取$mx$，最大的那个也没有超过$\frac{1}{2}$，那么显然会有一种办法使得$mn[x]=mx[x]\%2$。

那么如果$mx[p]>mx[x]-mx[p]$，就考虑调整。

因为如果$mx[p]>mx[x]-mx[p]$的话，其它的子树若取$mx$必然不会超过一半，那么只有可能是$p$点超过一半，于是考虑将$p$点由$mx$变成$mn$，那么式子就会变成$mn[p]>(mx[x]-mx[p]+mn[p])-mn[p]=mx[x]-mx[p]$，如果满足这个条件那么$p$点肯定会超过一半，于是这个时候$mn[x]=mn[p]+mx[p]-mx[x]$。

如果$mx[p]\leq mx[x]-mx[p]$，那么$mn[x]=mx[x]\%2$。

综上可知，当$mn[p]>mx[x]-mx[p]$时，$mn[x]=mn[p]+mx[p]-mx[x]$，剩下的情况$mn[x]=mx[x]\%2$。

最后只需要判断$mn[root]$是否为$0$即可。

注意转移的时候$mn$与$mx$均要加上$size$，因为要上传。

这样就做完了，复杂度$O(n^2)$。

code：
```cpp
#include<bits/stdc++.h>
#define maxn 2010
using namespace std;
typedef long long ll;
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch-'0'<0||ch-'0'>9){if(ch=='-') f=-1;ch=getchar();}
    while(ch-'0'>=0&&ch-'0'<=9){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n;
int a[maxn];
char s[maxn];
int head[maxn],nxt[maxn*2],to[maxn*2],tot;
void add(int u,int v)
{
    tot++;
    nxt[tot]=head[u];
    head[u]=tot;
    to[tot]=v;
}
ll mn[maxn],mx[maxn];
int g[maxn];
int solve(int x,int las)
{
    mx[x]=mn[x]=0;g[x]=a[x];
    int p=0;
    for(int i=head[x];i;i=nxt[i])
    {
        if(to[i]==las)  continue;
        solve(to[i],x);
        g[x]+=g[to[i]];
        mx[x]+=mx[to[i]];
        if(mx[to[i]]>mx[p])  p=to[i];
    }
    if(mn[p]>mx[x]-mx[p])  mn[x]=mn[p]+mx[p]-mx[x]+g[x];
    else                   mn[x]=(mx[x]&1)+g[x];
    mx[x]+=g[x];
    if(!las)  mn[x]-=g[x],mx[x]-=g[x];
}
ll ans=inf;
int main()
{
    n=read();
    scanf("%s",s+1);for(int i=1;i<=n;i++)  a[i]=s[i]-'0';
    for(int i=1;i<n;i++)
    {
        int q=read(),w=read();
        add(q,w);add(w,q);
    }
    for(int i=1;i<=n;i++)
    {
        solve(i,0);
        if(!mn[i])  ans=min(ans,mx[i]/2);
    }
    if(ans==inf)  puts("-1");
    else          cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Sonnety (赞：4)

## 前言

模拟赛考了这道题，但是数据范围 $n\leq 10^6$，很有趣不是吗。

看起来题解区的 $O(n)$ 做法似乎有些迷惑，所以我再写一遍。

## $O(n^2)$ 朴素做法


首先考虑 $O(n^2)$ 的做法，还是比较朴素的，如果看不懂可以看其他题解的，写的都比较清楚。。

既然不知道最后会在哪个点汇聚，那么就枚举这个点好了，把这个点作为树的根，为 $rt$。

设 $T_{now}$ 表示 $now$ 的子树，而 $col_{now}=1$ 表示这个点初始有棋子，有：

$$g_{now}=\sum_{to\in T_{now}\wedge col_{to}=1}dis(now,to)$$

这个东西，要么每次操作后不变，要么同时减 $2$，而为了其走的次数最少，一定是同时减去 $2$ 比较好，而如果操作后不变，那么被操作的点一定在 $now$ 的同一棵子树内。

所以我们考虑通过子树递归向上，设 $f_{now}$ 为 $g_{now}$ 经过一系列操作后的最小值，那么 $f_{now}$ 的贡献一定来源于不同的两个子树。

具体来说，设 $siz_{now}$ 表示 $now$ 为根的子树内有棋子的点的数量，当从 $to\to now$ 时，因为所有 $\in T_{to}$ 的棋子要多走一条边，所以 $f_{to}\to f_{to}+siz_{to}$，$g_{to}\to g_{to}+siz_{to}$。

而我们希望走到 $now$ 点的时候，如果说其他子树的点可以把 $\in T_{to}$ 的棋子“拉起来”，也就是 $g_{now}-g_{to}-siz_{to}>f_{to}+siz_{to}$，那么就都可以拉到 $now$ 点，唯一的问题在于因为是同时减去 $2$，所以如果 $g_{now}$ 为奇数，那么 $f_{now}=1$，否则为 $0$。

否则的话，我们拉不起来的点就拉不起来了，那么 $f_{now}=f_{to}+siz_{to}+g_{to}+siz_{to}-g_{now}$。

发现我们讨论的只需要是最大的 $f_{to}+siz_{to}+g_{to}+siz_{to}$ 上，所以设为 $maxv$ 维护一下。

最后总结一下式子：

$$
\begin{aligned}
&siz_{now}=\sum_{to\in T_{now}}siz_{to}+(col_{now}=1)\\
&g_{now}=\sum_{to\in T_{now}} g_{to}+siz_{to}\\
&maxv=\max_{to\in T_{now}}\{f_{to}+g_{to}+siz_{to}\times 2\}\\
\end{aligned}
$$

```
#include<bits/stdc++.h>
#define il inline
#define rg register int
#define cerr std::cerr
#define getime() cerr<<"Runtime is: "<<1.0*clock()/CLOCKS_PER_SEC<<" s"<<endl
#define endl '\n'
#define cout std::cout
#define bits(x) std::bitset<x>
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned char byte;
typedef std::pair<int,int> PII;
il int Max(int x,int y){ return x<y?y:x; }
il int Min(int x,int y){ return x<y?x:y; }
il int Abs(int x){ return x<0?-x:x; }
il void swap(int &x,int &y){ int temp=x;x=y;y=temp; }
il int read(){
    char c=getchar();int x=0,f=1;
    while(c<48){ if(c=='-')f=-1;c=getchar();}
    while(c>47){ x=(x<<3)+(x<<1)+(c^48);c=getchar(); }
    return x*f;
}const int maxn=2e3+5,inf=0x3f3f3f3f;

int n,ans,siz[maxn],f[maxn],g[maxn];
int head[maxn],t;
char s[maxn];bool col[maxn];
struct Edge{ int v;int next; };Edge e[maxn<<1];
il void add_edge(int u,int v){ e[++t].v=v;e[t].next=head[u];head[u]=t; }

il void clear(){ for(rg i=1;i<=n;++i)    f[i]=g[i]=siz[i]=0; }

void dfs(int now,int fa){
    siz[now]=(col[now]==true);int maxv=0;
    for(rg i=head[now];i;i=e[i].next){
        int to=e[i].v;
        if(to==fa)  continue;
        dfs(to,now);
        siz[now]+=siz[to];
        maxv=Max(maxv,f[to]+(siz[to]<<1)+g[to]);
        g[now]=g[now]+g[to]+siz[to];
    }
    if(maxv<g[now])   f[now]=(g[now]&1);
    else    f[now]=maxv-g[now];
}

il void input(){
    n=read();scanf("%s",s+1);int a,b;
    for(rg i=1;i<n;++i)    a=read(),b=read(),add_edge(a,b),add_edge(b,a);
    for(rg i=1;i<=n;++i)    if(s[i]=='1')   col[i]=1;
}

int main(){
freopen("charlotte.in","r",stdin);
freopen("charlotte.out","w",stdout);
    input();ans=inf;
    for(rg i=1;i<=n;++i){
        clear();
        dfs(i,0);
        if(!f[i])   ans=Min(ans,(g[i]>>1));
    }
    (ans==inf)?puts("-1"):printf("%d\n",ans);
getime();
return 0;
}
```

## $O(n)$ 换根DP

继续想 $O(n)$ 做法，考虑 up and down 换根 DP，从上往下 DP。

设以 $1$ 为根的树为原树，对其进行一遍 DFS 如上操作，得到原本的 $g$，$f$ 值。

设 $upf_u$，$upg_u$ 表示当点 $u$ 为根的时候，其原树从上往下的贡献 **（已经从 $fa$ 走到了 $u$ 并计算了贡献）**，设为已知，求 $G_u,F_u$ 为我们想要求的当 $u$ 为根的值。

对于求 $G$，是平凡的加和形式：

![](https://cdn.luogu.com.cn/upload/image_hosting/acjvguio.png)

 如上，有：

$$
\begin{aligned}
&upg_u=upg_{fa}+g_{fa}-g_{u}-siz_{u}+siz_{1}-siz_{u}\\
&G_u=upg_{u}+g_u
\end{aligned}
$$

而对于求 $F$，我们要求 $max$ 值（即上面的 $maxv$)，而当我们将 $u$ 的子树抛去计算其从上往下的贡献 $upmax$ 时，如果 $u$ 就是 $fa$ 的 $max$，那么 $upmax$ 就应该考虑次大值 $max2$，所以我们还要在第一次 $\mathtt{DFS}$ 的时候求次大值。

![](https://cdn.luogu.com.cn/upload/image_hosting/c59tybef.png)

如上，有：

$$
\begin{aligned}
maxv\in T_{u}\quad &upmax=\max(max2_{fa},upf_{fa}+upg{fa})\\
maxv\notin T_u\quad &upmax=\max(max_{fa},upf_{fa}+upg{fa})
\end{aligned}
$$

于是按照刚刚 $O(n^2)$ 的做法思路，如果 $upmax<G_{fa}-g_{u}-siz_{u}$（因为只讨论从上往下的贡献所以减去 $u$)，那么 $upf=0/1$，否则等于 $upmax-(G_{fa}-g_{u}-siz_{u})$。

然后再跳到 $u$ 点，使 $upf$ 加上 $siz_1-siz_u$。

于是有：

$$MAX=\max(max_u,upf_u+upg_u)$$

最后根据 $MAX_u$ 与 $G_u$ 形如上的关系得到了 $F_u$。

时间复杂度 $O(n)$。


```
#include<bits/stdc++.h>
#define il inline
#define rg register int
#define cerr std::cerr
#define getime() cerr<<"Runtime is: "<<1.0*clock()/CLOCKS_PER_SEC<<" s"<<endl
#define endl '\n'
#define cout std::cout
#define bits(x) std::bitset<x>
#define int long long
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned char byte;
typedef std::pair<int,int> PII;
il int Max(int x,int y){ return x<y?y:x; }
il int Min(int x,int y){ return x<y?x:y; }
il int Abs(int x){ return x<0?-x:x; }
il void swap(int &x,int &y){ int temp=x;x=y;y=temp; }
inline int read(){
	int x(0);bool f(0);char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar()) f^=ch=='-';
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
	return f?x=-x:x;
}const int maxn=1e6+5,inf=0x3f3f3f3f3f3f3f;

char s[maxn];
int n,ans,siz[maxn],g[maxn],upg[maxn],G[maxn],f[maxn],upf[maxn],F[maxn],max[maxn],max2[maxn],upmax[maxn],MAX[maxn];
int head[maxn],t;
struct Edge{ int v;int next; };Edge e[maxn<<1];
il void add_edge(int u,int v){ e[++t].v=v;e[t].next=head[u];head[u]=t; }

void dfs1(int now,int fa){
    siz[now]=(s[now]-'0');
    for(rg i=head[now];i;i=e[i].next){
        int to=e[i].v;
        if(to==fa)  continue;
        dfs1(to,now);
        siz[now]+=(siz[to]);
        g[now]+=(g[to]+siz[to]);
        int next=f[to]+g[to]+(siz[to]<<1);
        if(next>max[now])   max2[now]=max[now],max[now]=next;
        else if(next>max2[now]) max2[now]=next;
    }
    if(max[now]<g[now]) f[now]=(g[now]&1);
    else    f[now]=max[now]-g[now];
}

void dfs2(int now,int fa){
    if(now!=1){
        upg[now]=upg[fa]+g[fa]-g[now]-siz[now]+siz[1]-siz[now];
        G[now]=upg[now]+g[now];
        if(f[now]+g[now]+(siz[now]<<1)==max[fa])    upmax[now]=Max(max2[fa],upf[fa]+upg[fa]);
        else    upmax[now]=Max(max[fa],upf[fa]+upg[fa]);
        int updis=G[fa]-g[now]-siz[now];
        if(upmax[now]<updis)    upf[now]=(updis&1);
        else    upf[now]=upmax[now]-updis;
        upf[now]+=siz[1]-siz[now];
        MAX[now]=Max(max[now],upf[now]+upg[now]);
        if(MAX[now]<G[now]) F[now]=(G[now]&1);
        else    F[now]=MAX[now]-G[now];
    }
    for(rg i=head[now];i;i=e[i].next){
        int to=e[i].v;
        if(to==fa)  continue;
        dfs2(to,now);
    }
}

il void input(){
    n=read();scanf("%s",s+1);int u,v;
    for(rg i=1;i<n;++i) u=read(),v=read(),add_edge(u,v),add_edge(v,u);
}

signed main(){
freopen("charlotte.in","r",stdin);
freopen("charlotte.out","w",stdout);
    input();ans=inf;
    dfs1(1,0);F[1]=f[1],G[1]=g[1];dfs2(1,0);
    for(rg i=1;i<=n;++i)    if(!F[i])   ans=Min(ans,(G[i]>>1));
    (ans==inf)?puts("-1"):printf("%lld\n",ans);
getime();
return 0;
}
```

如有错误，请指出。

---

## 作者：GoPoux4 (赞：4)

_推销博客：https://www.cnblogs.com/syc233/p/13603919.html_

---

注意到数据范围很小，所以我们可以枚举一个根，尽量让所有点移动到这个点上。

将两颗距离至少为 $2$ 的棋子向中间移动一步，可能会出现两种情况：

* 它们的LCA为它们共同的祖先，则两颗棋子一同向LCA移动一步。
* 其中一颗棋子为LCA，则深度浅的棋子向下移动，深度深的棋子向上移动。

显然第二种情况对于寻找最优解是不利的，为了让所有点移动到根上，每个点都应向上跳。所以我们只考虑以第一种情况操作。

---

zzy：

> 这里就涉及到一个经典的模型：有若干个元素被分成了若干个集合， 每次要找两个在不同集合中的元素匹配然后消掉。

设所有集合的总大小为 $sum$ ，最大集合的大小为 $max$ ，有两种情况：

* $sum-max\geq max$ ，每次选择最大和次大的两个集合内两个元素消掉，消掉后还是这种情况。所以最多能消掉 $\lfloor\frac{sum}{2}\rfloor$ 对元素。
* $sum-max<max$ ，把其他集合的元素全部用来消最大集合中的元素，最多能消掉 $sum-max$ 对元素，最后最大集合中还剩余 $max\times 2-sum$ 个元素。

---

再回到这道题。

考虑树上的一个点 $u$ ，我们将它的子树中的点移动到 $u$ 上。对于 $u$ 子树中一个点 $v$ ，我们必须对它进行 $dis(u,v)$ 次操作才能将它移动到点 $u$ 。这相当于将 $u$ 子树中每个有棋子的点 $v$ 拆成了一个有 $dis(u,v)$ 个元素的集合，每次在两个集合中分别选择两个元素相消，则问题转化为了经典模型。

但是由于树结构的限制，有祖孙关系的两个点对应的集合不能同时选择。因此我们考虑树形DP，将问题转化为**互不相交**的子问题求解。

令 $f_u$ 表示 $u$ 的子树内最多能消去多少对元素，$dis_u$ 表示 $u$ 的子树中棋子拆成的集合的总大小，设 $max$ 表示 $u$ 的儿子对应的子树中棋子拆成的集合的最大的总大小，即 ${\rm{max}}\{dis_v|v \in son_v\}$ 。则有转移：

* $dis_u-max\geq max$ ，每次选择两个处于不同子树的两个元素相消，则 $f_u=\lfloor\frac{sum}{2}\rfloor$ 。
* $dis_u-max<max$ ，先用其他子树中的元素消最大子树中的元素，这样能消掉 $dis_u-max$ 对元素，剩下的 $max\times 2-dis_u$ 个元素全部在最大子树中。在最大子树 $v$ 内部最多能消 $f_v$ 对元素，则剩下的元素在最大子树中能消 $\lfloor\frac{{\rm{min}}(f_v\times 2,max\times 2-dis_u)}{2}\rfloor$ 对。则 $f_u=dis_u-max+\lfloor\frac{{\rm{min}}(f_v\times 2,max\times 2-dis_u)}{2}\rfloor$ 。

以 $root$ 为根时，当且仅当 $f_{root}=\frac{dis_{root}}{2}$ ，即所有元素都消完时合法。

---

$\text{Code}:$

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define maxn 2005
#define Rint register int
#define INF 0x3f3f3f3f
using namespace std;
typedef long long lxl;

template <typename T>
inline void read(T &x)
{
	x=0;T f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	x*=f;
}

struct edge
{
	int u,v,next;
}e[maxn<<1];

int head[maxn],k;

inline void add(int u,int v)
{
	e[k]=(edge){u,v,head[u]};
	head[u]=k++;
}

int n,a[maxn];
int siz[maxn],dis[maxn],f[maxn];

inline void dfs(int u,int fa)
{
	siz[u]=a[u];
	dis[u]=0;
	int son=-1;
	for(int i=head[u];~i;i=e[i].next)
	{
		int v=e[i].v;
		if(v==fa) continue;
		dfs(v,u);
		siz[u]+=siz[v];
		dis[u]+=(dis[v]+=siz[v]);
		if(!~son||dis[son]<dis[v]) son=v;
	}
	if(!~son) return void(f[u]=0);
	if(dis[u]-dis[son]>=dis[son]) f[u]=dis[u]/2;
	else f[u]=dis[u]-dis[son]+min(f[son]*2,2*dis[son]-dis[u])/2;
}

char s[maxn];

int main()
{
	// freopen("AT4995.in","r",stdin);
	read(n);
	scanf(" %s",s+1);
	for(int i=1;i<=n;++i) a[i]=s[i]-'0';
	memset(head,-1,sizeof(head));
	for(int i=1,u,v;i<n;++i)
	{
		read(u),read(v);
		add(u,v);add(v,u);
	}
	int ans=-1;
	for(int i=1;i<=n;++i)
	{
		dfs(i,0);
		if(f[i]*2==dis[i]) ans=(!~ans||ans>f[i])?f[i]:ans;
	}
	printf("%d\n",ans);
	return 0;
}

```



---

## 作者：int_R (赞：3)

[更好的阅读体验](https://www.cnblogs.com/int-R/p/AT_agc034_e.html)

[原题链接](https://www.luogu.com.cn/problem/AT_agc034_e)

这里是用 `set` 实现的换根 DP，时间复杂度 $O(n\log n)$。

记 $siz_x,g_x,f_x$ 分别为 $x$ 及其子树中有多少个关键点，所有关键点到 $x$ 的距离和，将关键点尽可能两两向上合并后到 $x$ 的距离和（我愿意理解为是将 $g_x$ 缩到最小的值）。

当你钦定最后合并到 $root$，那么是否有解等价于 $[f_{root}=0]$。

考虑朴素 DP，枚举所有根。有转移：

- $siz_x=[a_x=1]+\sum\limits_{y\in son(x)} siz_y$
- $g_x=\sum\limits_{y\in son(x)} (g_y+siz_y)$
- $f_x=\begin{cases} f_y+siz_y-(g_x-(g_y+siz_y)) & \exists y\in son(x),f_y+siz_y > g_x-(g_y+siz_y) \\ g_x\bmod 2 & \forall y\in son(x),f_y+siz_y\leq g_x-(g_y+siz_y) \end{cases}$


$\exists y\in son(x),f_y+siz_y > g_x-(g_y+siz_y)$，实际含义是如果有一个 $y$，它及其子树到 $x$ 所需的最少步数比 $x$ 其他子树所提供的最多步数还多就不能被减完，最优就是尽可能的多处理这个子树；不然就考虑每次选出所有剩余 $f_y$ 中最大的两个，一起 $-1$，这样就相当于最后只会剩 $[0,1]$ 个 $1$，就等于 $g_x$ 的奇偶性。

考虑接下来换根 DP，先考虑每个 $x,y\in son(x),f_y+siz_y > g_x-(g_y+siz_y)$ 最多只会有 $1$ 个，所以可以移项，判断 $f_y+siz_y+g_y+siz_y$ 与 $g_x$ 的大小关系。$f_x$ 的第一种转移也可以变成 $f_y+siz_y+g_y+siz_y-g_x$。

所以 $siz_x,g_x$ 正常换根，再对于每个点开一个 `set`，将所有的 $f_y+siz_y+g_y+siz_y$ 放到 $x$ 对应的 `set` 中，这样就可以换根了。

其实我们每次只用到了最大值，所以如果不用 `set` 也可以直接维护，就可以 $O(n)$ 了，但我感觉很麻烦。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
const int MAXN=1e6+10;
const long long INF=1e16+10;
int n,siz[MAXN];char a[MAXN];
long long f[MAXN],g[MAXN],ans=INF;
vector <int> v[MAXN];set <long long> s[MAXN];
inline void clear()
{
    for(int i=1;i<=n;++i) v[i].clear(),s[i].clear();
    ans=INF;return ;
}
void get_f(int x)
{
    if(s[x].empty()){f[x]=0;return ;}
    if(*s[x].rbegin()<=g[x]) f[x]=(g[x]&1?1:0);
    else f[x]=*s[x].rbegin()-g[x];return ;
}
void dfs(int x,int fa=0)
{
    siz[x]=(a[x]=='1');g[x]=0;
    for(int y:v[x])
    {
        if(y==fa) continue;dfs(y,x);
        siz[x]+=siz[y],g[x]+=g[y]+siz[y];
        s[x].insert(f[y]+siz[y]+g[y]+siz[y]);
    }
    get_f(x);return ;
}
void dp(int x,int fa=0)
{
    if(!f[x]) ans=min(ans,g[x]/2);
    for(int y:v[x])
    {
        if(y==fa) continue;
        siz[x]-=siz[y],g[x]-=g[y]+siz[y];
        s[x].erase(s[x].find(f[y]+siz[y]+g[y]+siz[y])),get_f(x);
        siz[y]+=siz[x],g[y]+=g[x]+siz[x];
        s[y].insert(f[x]+siz[x]+g[x]+siz[x]),get_f(y);
        dp(y,x);
        siz[y]-=siz[x],g[y]-=g[x]+siz[x];
        s[y].erase(s[y].find(f[x]+siz[x]+g[x]+siz[x])),get_f(y);
        siz[x]+=siz[y],g[x]+=g[y]+siz[y];
        s[x].insert(f[y]+siz[y]+g[y]+siz[y]),get_f(x);
    }
    return ;
}
int main()
{
    freopen("charlotte.in","r",stdin);
    freopen("charlotte.out","w",stdout);
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    while(cin>>n)
    {
        for(int i=1;i<=n;++i) cin>>a[i];
        for(int i=1,x,y;i<n;++i)
            cin>>x>>y,v[x].push_back(y),v[y].push_back(x);
        dfs(1),dp(1);
        cout<<(ans==INF?-1:ans)<<'\n';clear();
    }
    return 0;
}
```

---

## 作者：5k_sync_closer (赞：2)

可以发现若最终所有棋子移动到 $x$，则操作次数一定是初始时所有棋子到 $x$ 的距离和除以二，

于是只需求出哪些 $x$ 可以作为最终所有棋子移动到的位置。

设 $s_i$ 表示 $i$ 子树内初始时棋子个数，$f_i$ 表示 $i$ 子树内棋子经过若干操作后到 $i$ 距离和最小是多少，$g_i$ 表示 $i$ 子树内棋子初始时到 $i$ 距离和，

考虑 $u$ 若有一孩子 $v$ 满足 $f_v+s_v>g_u-g_v-s_v$，则 $v$ 子树内的棋子一定不能全部移动到 $u$ 上，

于是此时的最优策略为其他所有子树的棋子均选择 $v$ 子树内的棋子匹配，

这样其他所有子树的棋子均被移到 $u$ 上，而 $v$ 子树内的棋子到 $u$ 距离和还剩 $f_v+s_v-(g_u-g_v-s_v)$，

也就是 $f_u=f_v+s_v-(g_u-g_v-s_v)$。

如果 $u$ 没有这样的孩子 $v$，那最终至多剩一个棋子与 $u$ 距离为 $1$，也就是 $f_u=g_u\bmod 2$。

以 $x$ 为根跑这个 DP，若得到的 $f_x=0$，则 $x$ 可以作为最终所有棋子移动到的位置。

发现需要以每个点为根的 DP 值，换根 DP 即可。

```cpp
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
inline int R()
{
    int q = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        q = q * 10 + c - '0', c = getchar();
    return q;
}
inline int I()
{
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    return c - '0';
}
struct E
{
    int v, t;
} e[2000050];
int n, c, q = 1e18, a[1000050], s[1000050], f[1000050], g[1000050], p[1000050], z[1000050][2], o[1000050][2], h[1000050];
void A(int u, int v)
{
    e[++c] = {v, h[u]};
    h[u] = c;
}
void D1(int u, int k)
{
    s[u] = a[u];
    for (int i = h[u], v; i; i = e[i].t)
        if ((v = e[i].v) != k)
            D1(v, u), p[u] += f[v] + s[v], g[u] += g[v] + s[v], s[u] += s[v];
    for (int i = h[u], v; i; i = e[i].t)
        if ((v = e[i].v) != k)
        {
            if (f[v] + s[v] + g[v] + s[v] > o[u][0])
                z[u][1] = z[u][0], z[u][0] = v, o[u][1] = o[u][0], o[u][0] = f[v] + s[v] + g[v] + s[v];
            else if (f[v] + s[v] + g[v] + s[v] > o[u][1])
                z[u][1] = v, o[u][1] = f[v] + s[v] + g[v] + s[v];
        }
    if (o[u][0] > g[u])
        f[u] = o[u][0] - g[u];
    else
        f[u] = p[u] & 1;
}
void D2(int u, int k)
{
    int S = s[u], F = f[u], P = p[u], G = g[u], Z0 = z[u][0], Z1 = z[u][1], O0 = o[u][0], O1 = o[u][1];
    for (int i = h[u], v; i; i = e[i].t)
        if ((v = e[i].v) != k)
        {
            s[u] -= s[v];
            g[u] -= g[v] + s[v];
            p[u] -= f[v] + s[v];
            if (z[u][0] == v)
                z[u][0] = z[u][1], o[u][0] = o[u][1];
            if (o[u][0] > g[u])
                f[u] = o[u][0] - g[u];
            else
                f[u] = p[u] & 1;
            s[v] += s[u];
            g[v] += g[u] + s[u];
            p[v] += f[u] + s[u];
            if (f[u] + s[u] + g[u] + s[u] > o[v][0])
                z[v][1] = z[v][0], z[v][0] = u, o[v][1] = o[v][0], o[v][0] = f[u] + s[u] + g[u] + s[u];
            else if (f[u] + s[u] + g[u] + s[u] > o[v][1])
                z[v][1] = u, o[v][1] = f[u] + s[u] + g[u] + s[u];
            if (o[v][0] > g[v])
                f[v] = o[v][0] - g[v];
            else
                f[v] = p[v] & 1;
            D2(v, u);
            s[u] = S, f[u] = F, p[u] = P, g[u] = G, z[u][0] = Z0, z[u][1] = Z1, o[u][0] = O0, o[u][1] = O1;
        }
}
signed main()
{
    // freopen("charlotte.in", "r", stdin);
    // freopen("charlotte.out", "w", stdout);
    while (~scanf("%d", &n))
    {
        for (int i = 1; i <= n; ++i)
            a[i] = I();
        for (int i = 1, u, v; i < n; ++i)
            u = R(), v = R(), A(u, v), A(v, u);
        D1(1, 0);
        D2(1, 0);
        for (int u = 1; u <= n; ++u)
            if (!f[u])
                q = min(q, g[u] >> 1);
        printf("%lld\n", q == 1e18 ? -1 : q);
        c = 0;
        q = 1e18;
        for (int i = 1; i <= n; ++i)
            a[i] = s[i] = f[i] = g[i] = p[i] = z[i][0] = z[i][1] = o[i][0] = o[i][1] = h[i] = 0;
    }
    return 0;
}
```


---

## 作者：Caicz (赞：2)

### [在博客食用效果更佳](https://www.luogu.com.cn/blog/224229/solution-at4995)
### [Atcoder题目链接](https://atcoder.jp/contests/agc034/tasks/agc034_e)
------------
考虑到数据范围 $N<=2,000$ 我们可以直接枚举最终会汇聚到的点。同时，对于当前节点，我们可以发现，每次一定选择非同一链到当前节点的两颗棋子进行位移

此时如zzy所说

> 这里就涉及到一个经典的模型：有若干个点被分成了若干个集合，每次要找两个在不同集合中的点匹配然后消掉。当$sum-max>=max$ 时,即 $sum<=2 × max$，如果总共有偶数个点可以消完否则可以剩下恰好1个，消去了 $[\frac{sum}{2}]$ 对；否则还剩下 $max-(sum-max)$个来自最大集合的点，消去了 $sum-max$ 

我们考虑让点能够消掉，就可以直接**让每一个棋子分为 $dis(u,root)$ 个棋子**，分布在 $u$ 到 $root$ 的路径上。

那么我们就可以**设 $f[x]$ 表示:以 $x$ 为根的子树里，最多能消掉的点的对数**,同时**设 $sum$ 为树中棋子的个数，$u$ 为最大子树的编号, $maxson$ 为最大子树的 $sum$** ，那么我们可以得到
$$
f[x]=
\left\{
\begin{array}{l}
[\frac{sum}{2}](sum-maxson>=maxson)\\
sum-maxson+min(f[u],maxson-[\frac{sum}{2}])(sum-maxson<maxson)
\end{array}
\right.
$$


如果所有棋子都能被消掉，其答案即为$\frac{sum_{root}}{2}$，即只要满足 $f[root]\times2=sum_{root}$ ，即为一个合法答案。

$$
\color{red}{\text{Talk is cheap , show you the code}}
$$
```cpp
#include<touwenjian.h>\\从MMM处偷来的万能头
#define ll long long
#define maxn 2005
#define inf 0x3f3f3f3f
using namespace std;
int n,w[maxn],head[maxn],k,root;
int f[maxn],si[maxn],sum[maxn];
char s[maxn];
struct  eage
{
	int v,last;
}e[maxn<<1];

int read()
{
	int num,sign=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')sign=-1;
	num=c-'0';
	while(((c=getchar())>='0'&&c<='9'))
		num=(num<<1)+(num<<3)+c-'0';
	return num*sign;
}

inline void addeage(int u,int v)
{
	e[++k].last=head[u];
	e[k].v=v;
	head[u]=k;
}

void dfs(int u,int fa)
{
	si[u]=0;
	if(w[u])si[u]=1;
	sum[u]=0;
	int maxson=0,maxid;
	for(register int i=head[u];i;i=e[i].last)
	{
		int v=e[i].v;
		if(v==fa)continue;
		dfs(v,u);
		si[u]+=si[v];
		sum[u]+=(sum[v]+si[v]);
		if(sum[v]+si[v]>maxson)
		{
			maxson=sum[v]+si[v];
			maxid=v;
		}
	}
	if(sum[u]-maxson>=maxson)f[u]=sum[u]/2;
	else f[u]=sum[u]-maxson+min(f[maxid],maxson-sum[u]/2);
}

int main()
{
	n=read();
	for(register int i=1;i<=n;++i)
	{
		char x=getchar();
		if(x=='1')w[i]=1;
	}
	for(register int u,v,i=1;i<n;++i)
	{
		u=read(),v=read();
		addeage(u,v);
		addeage(v,u);
	}
	int ans=inf;
	for(register int i=1;i<=n;++i)
	{
		root=i;
		dfs(root,0);
		if(!(sum[root]%2)&&f[root]==sum[root]/2)ans=min(ans,f[root]);
	}
	printf("%d\n",ans==inf?ans=-1:ans);
	return 0;
}
```

---

## 作者：GavinZheng (赞：2)

首先枚举一个节点作为根，问题就变成了：每次选择不是祖先-后代关系的两个点向上跳跃，看能不能把所有点跳跃到根节点。

这里涉及到一个经典的模型：有很多个集合，每次选择两个不同的集合，各自消掉一个元素，看能不能消完。

这里有一个结论：当$T$中最大的集合为$k$时，有

- 当$size(k)\leq \sum _{i\in T, i\ne k}size(i)$，可以完全消除（和为偶数一个不剩，和为奇数只留一个）。
- 当$size(k)> \sum _{i\in T, i\ne k}size(i)$，会剩下$size(k)- \sum _{i\in T, i\ne k}size(i)$个无法消除。

这个结论可以这样证明：

- 出现第一种情况时，拿前两大的来消，消一次后依旧是第一种情况。（最大的和除最大的之外的和共同减小1）
- 出现第二种情况时，拿最大的消掉其他所有的即可。

---

那么有了这个结论，又有了根节点，那我们就可以对全树进行DP。因为这里的“消除”是带权值的（一个点要被“消”多次才会到达根节点，这个次数就是他的深度。）后文说的“点”均为虚点，一个点产生的虚点个数为他距离目标的长度。

令$F[i]$为当前树中$i$的子树中，最多能消掉多少对点。我们令$T$为$i$的儿子集合，令$sum=\sum _{j\in T, j\ne k}size(j)$。然后我们就可以根据上面那个结论得到转移的方程：

- 当$size(k)\leq sum$, $F[i]=\lfloor \frac{\sum_{j\in T}size(j)}{2}\rfloor$。
- 当$size(k)> sum$, $F[i]=sum+\lfloor \frac{min(size(k)-sum,2F[k])}{2}\rfloor$

其实这个东西可以DP，也可以搜一遍。都差不多。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
string a;
const int inf=1e9+1000;
const int maxn=2050;
int head[maxn],cnt;
struct gg {
    int u,v,next;
}side[maxn*2];
int size[maxn],sum,f[maxn],F[maxn],depth[maxn],dep_sum[maxn];
void insert(int u,int v) {
    side[++cnt]=(gg){u,v,head[u]};head[u]=cnt;
}
int ans=inf;
void init() {
    memset(F,0,sizeof(F));
    memset(size,0,sizeof(size));memset(f,0,sizeof(f));sum=0;
    memset(dep_sum,0,sizeof(dep_sum));
    for(int i=0;i<a.length();i++)size[i+1]=(a[i]=='1');
}
void dfs(int u,int fa,int d) {
    int tot=0,k=0,mx=-1;depth[u]=d;
    for(int i=head[u];i;i=side[i].next) {
        int v=side[i].v;if(v==fa)continue;
        dfs(v,u,d+1);
        dep_sum[u]+=dep_sum[v]+size[v];
        if(dep_sum[v]+size[v]>mx) {
            mx=dep_sum[v]+size[v];k=v;
        }
        size[u]+=size[v];
        tot+=dep_sum[v]+size[v];
    }
    int sum=tot-(dep_sum[k]+size[k]);
    if(mx<=sum)F[u]=tot/2;
    else F[u]=sum+min(mx-sum,2*F[k])/2;
}
int main() {
    ios::sync_with_stdio(0);
    int n;cin>>n>>a;
    for(int i=1,u,v;i<n;i++) {
        cin>>u>>v;
        insert(u,v);insert(v,u);
    }
    for(int i=1;i<=n;i++) {
        init();
        dfs(i,0,0);
        if(F[i]*2==dep_sum[i]) {
            ans=min(ans,dep_sum[i]);
        }
    }
    if(ans>=inf)printf("-1");
    else printf("%d",ans/2);
    return 0;
}
```



---

## 作者：xht (赞：1)

## [Complete Compress](https://atcoder.jp/contests/agc034/tasks/agc034_e)

### 题意

- 给定一棵 $n$ 个点的树，树上的某些节点上有一个人。
- 每次可以选择两个距离 $\ge 2$ 的人，它们将向对方移动一个点。
- 问能否使得所有人都在一个点上。
- $n \le 2 \times 10^3$。

### 题解

枚举最终的点 $rt$，以 $rt$ 为根建树。

则每一步必然是找到两个非祖先关系的人，向着它们的 $\text{lca}$ 移动一格。

若将点 $x$ 上的人视为 $\text{dist}(rt,x)$ 个，则问题等价于每次消掉两个非祖先关系的人，问是否能消完。

考虑 DP，设 $f_u$ 表示 $u$ 子树的答案，设 $d_u$ 表示 $u$ 子树内的人数，则：

- 若 $u$ 存在某个儿子 $v$，满足 $d_u < 2d_v$，则有转移 $f_u = d_u - d_v + \min(f_v, \lfloor\frac{2d_v - d_u}{2} \rfloor)$。
- 否则，$f_u = \lfloor\frac{d_u}{2} \rfloor$。

最终要求 $d_{rt}$ 为偶数，且 $2f_{rt} \ge d_{rt}$ 才能更新答案。

### 代码

```cpp
const int N = 2e3 + 7, inf = 1e9;
int n, m, d[N], s[N], f[N], ans = inf;
char a[N];
vi e[N];

void dfs(int x, int fa = 0) {
	s[x] = a[x] == '1', d[x] = 0;
	int o = 0;
	for (int y : e[x])
		if (y != fa) {
			dfs(y, x), s[x] += s[y], d[x] += d[y] += s[y];
			if (d[y] > d[o]) o = y;
		}
	if (d[x] >= 2 * d[o]) f[x] = d[x] >> 1;
	else f[x] = d[x] - d[o] + min(f[o], (d[o] * 2 - d[x]) >> 1);
}

int main() {
	rd(n), rds(a, n);
	for (int i = 1; i <= n; i++) m += a[i] == '1';
	for (int i = 1, x, y; i < n; i++)
		rd(x, y), e[x].pb(y), e[y].pb(x);
	for (int x = 1; x <= n; x++) {
		dfs(x);
		if (d[x] & 1) continue;
		if (f[x] * 2 >= d[x]) ans = min(ans, d[x]);
	}
	print(ans == inf ? -1 : ans >> 1);
	return 0;
}
```

---

## 作者：Graphcity (赞：1)

考虑枚举最终到达的结点 $x$。我们设 $g(S)$ 为黑点在位置集合 $S$ 时到根结点 $x$ 的距离之和。

如果两个黑点是祖先后代关系，$g(S)$ 不变，否则 $g(S)$ 减少二。所以祖先后代关系的收缩是无效的，不需要考虑它。我们总的收缩次数就是 $\dfrac{1}{2}g(S)$，现在仅需判断是否合法。

设 $f_i$ 表示以 $i$ 为根，且仅考虑 $i$ 子树中黑点的最小 $g$ 值。我们先假设 $i$ 所有的儿子 $j$ 的 $g$ 值都已经收缩至最优状态：$f_j$ 加上 $j$ 中的黑点个数。

每次我们都可以选择两个儿子 $x,y$，收缩这两个儿子所在的子树中的点，让 $g_x$ 和 $g_y$ 减去一。

最终儿子剩下的 $g$ 之和就是 $f_i$。根据经典贪心结论，设 $sum$ 为儿子的 $g$ 之和，$mx$ 为儿子的 $g$ 最大值，则 $f_i$ 理应等于 $sum-2\times \min(\lfloor \dfrac{sum}{2}\rfloor ,sum-mx)$。

但交上去发现不对。为什么呢？**我们可以通过撤销部分子树的操作，使得它们的 $g$ 值变大，从而弱化 $mx$ 带来的影响**。

那我们接着设 $h_i$ 表示 $i$ 子树能带来的最大 $g$ 值。显然 $i$ 子树能取到的 $g$ 范围就是 $[f_i,h_i]$ 中所有跟 $f_i,h_i$ 奇偶性相同的数。

所以我们不断抬升非最大值中的 $g$，将 $mx$ 的影响降至最低，直到 $sum-mx\ge \lfloor \dfrac{sum}{2}\rfloor$ 就行了。

时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e3,inf=1e9;

int n,ans=inf,sum=0,h[Maxn+5];
int s[Maxn+5],siz[Maxn+5],val[Maxn+5];
vector<int> v[Maxn+5];

inline void dfs(int x,int f,int d)
{
    s[x]=val[x]=0; if(h[x]) sum+=d;
    for(auto y:v[x]) if(y!=f) dfs(y,x,d+1);
}
inline void dfs2(int x,int f)
{
    int all=0,mx=0,k=0; siz[x]=h[x];
    for(auto y:v[x]) if(y!=f)
    {
        dfs2(y,x),siz[x]+=siz[y];
        assert((s[y]&1)==(val[y]&1));
        val[y]+=siz[y],val[x]+=val[y];
    }
    for(auto y:v[x]) if(y!=f) s[y]+=siz[y],all+=s[y],mx=max(mx,s[y]);
    k=min(all-mx,all/2); s[x]=all-k*2;
    if(all-mx<all/2)
    {
        int flg=0;
        for(auto y:v[x]) if(y!=f && s[y]==mx)
        {
            if(!flg) flg=y;
            else if(val[y]<val[flg]) flg=y;
        }
        for(auto y:v[x]) if(y!=f && y!=flg)
        {
            int w=all-s[y]+val[y];
            assert((all&1)==(w&1));
            if(w-mx>=w/2) {s[x]=(all&1); return;}
            all=w;
        }
        k=min(all-mx,all/2); s[x]=all-k*2;
    }
}
inline int Solve(int x)
{
    sum=0,dfs(x,0,0);
    if(sum&1) return inf;
    dfs2(x,0);
    if(s[x]) return inf; else return sum/2;
}

int main()
{
    scanf("%d",&n);
    For(i,1,n) scanf("%1d",&h[i]);
    For(i,1,n-1)
    {
        int a,b; scanf("%d%d",&a,&b);
        v[a].push_back(b),v[b].push_back(a);
    }
    For(i,1,n) ans=min(ans,Solve(i));
    if(ans==inf) cout<<-1<<endl;
    else cout<<ans<<endl;
    return 0;
}
```

---

