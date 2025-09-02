# Labyrinth

## 题目描述

In a dream, Lucy found herself in a labyrinth. This labyrinth consists of $ n $ rooms, connected by $ m $ passages ( $ i $ -th passage is $ w_i $ cm wide). Each passage can be traversed in both directions. It is guaranteed that it is possible to get from any room to any other room. But this is not an ordinary labyrinth — each room in this labyrinth contains a magic candy. When Lucy eats this magic candy, she is getting wider. Specifically, if she eats candy from room $ i $ she becomes wider by $ c_i $ cm. Note that she is not obliged to eat candy the first time she visits a particular room, but she can eat each candy only once.

Unfortunately, passages in this labyrinth are pretty narrow, so after eating some candy, Lucy can get too wide and will not be able to traverse them — her width should not be greater than the width of the corresponding passage.

Lucy starts her journey in a room number $ 1 $ . She wants to eat all the candies. After that, she will just wake up, so she does not have to be able to return to the room $ 1 $ . She realizes that with her current width, she may not be able to do so, so she plans a workout before embarking on her journey. Lucy wants to know if it is possible to start with some positive width and still eat all the candies. If yes, then what is the maximal starting width with which it is possible.

## 样例 #1

### 输入

```
3 3
1 2 3
1 2 4
1 3 4
2 3 6```

### 输出

```
3```

## 样例 #2

### 输入

```
2 1
1 1
1 2 1```

### 输出

```
-1```

# 题解

## 作者：namelessgugugu (赞：25)

#### 题意

一个无向连通图，边有宽度，点上有糖，糖吃完会使人变胖（即宽度增加）。

人从 $1$ 节点出发，任意移动，但只能走过宽度不超过自身宽度的边，走到点上可以选择吃掉该点上的糖果，每个糖果只能吃一次。

求出要吃完所有糖果，人的初始宽度的最大值，如果无论如何都吃不完，输出 $-1$。

#### 题解

首先解决这样一个问题：如果从点 $a$ 走到点 $b$，人的最大宽度可以是多少，即找到一条从 $a$ 到 $b$ 的路径，使得它所经过的边的宽度最小值最大。

这是一个经典问题（P1967 货车运输），根据题解我们知道，答案应该是建立最大生成树后，$a, b$ 两点之间边权最小值。当然你也可以用 kruskal 算法流程推出这一结论：这个算法实际上就是在用尽可能大的边让 $a, b$ 联通。

问题现在转化为一个树上问题，看上去简单了很多。

当人在不停的吃糖时，有些边就会因为人宽度的增加而断掉，这对于一颗树而言是毁灭性的，因为这样它就不再联通了，你也不可能吃完所有糖了，除非，这条边断开的时候，被割下来的那一棵子树早就被你吃完了。

第一条断掉的边一定是宽度最小的那一条，我们设它连接的是 $u,v$ 两点，宽度为 $w$。设这条边断掉之后，$u, v$所对应的那棵树（下文简称树 $u$，树 $v$）的糖果值总和分别为 $s_u, s_v$。

不妨设人先吃完了树 $u$ 的所有糖果，然后我们证明一个结论：在一开始吃完树 $u$ 的全部节点一定不劣于其他决策。考虑存在一种解法，使得吃完树 $u$，吃掉了些树 $v$ 的糖果，那么由于之后还能从 $(u, v, w)$ 返回，则当前宽度一定不超过 $w$，也就不超过树上的任意一条边的宽度，因此以什么顺序吃掉这些糖果都不会有问题，换成先吃完树 $u$ 并不会变劣。

吃完了树 $u$，我们惊讶地发现只要得到原问题在树 $v$ 上的答案 $x_v$，那么答案就是 $\min\{x_v-s_u, w-s_u\}$。先吃树 $v$ 也是同理，因此答案是 $\max\{\min\{x_v-s_u, w-s_u\}, \min\{x_u-s_v, w-s_v\}\}$，最后如果发现答案非正，则输出 $-1$。

还剩两个小问题，第一是初始节点是 $1$ 而不是 $u$ 或 $v$，能不能从 $1$ 走到它们两个呢？由于最终答案不可能大于 $w$（不然一开始树就不联通了），所以一开始是可以在整棵树上随便走的。

第二是如何在递归求解的时候快速得到那一棵子树中宽度最小的边？在建最大生成树时建立 kruskal 重构树，那么一条边的左右儿子就是它左右两棵子树的宽度最小的边的编号，这是由于 kruskal 算法先连接边权大的边，那么重构树的子树的根一定是最后连接的边，就是边权最小的。

#### 代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long ll;
const int N = 200005;
const ll inf = 0x3f3f3f3f3f3f3f3f;
int n, m, c[N];
struct Edge
{
    int x, y, w;
} E[N];
int fa[N];
inline void init(int n)
{
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
    return;
}
int find(int x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
ll f[N], sum[N];//f,x分别对应上文中的x,s
int main(void)
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", c + i);
    for (int i = 1; i <= m; ++i)
        scanf("%d%d%d", &E[i].x, &E[i].y, &E[i].w);
    std::sort(E + 1, E + 1 + m, [](Edge a, Edge b) -> bool
              { return a.w > b.w; });
    init(n + m);
    int rt = 0;
    for (int i = 1; i <= n;++i)
        f[i] = inf, sum[i] = c[i];//单个点作为树的边界情况的处理
    for (int i = 1; i <= m; ++i) //建立kruskal重构树
    {
        int x = E[i].x, y = E[i].y;
        if ((x = find(x)) != (y = find(y)))
        {
            int k = i + n;
            fa[x] = fa[y] = k;
            rt = k;//rt是最后一条被加入生成树的边，即重构树的根
            ll w = E[i].w; 
            f[k] = std::max(std::min(w - sum[x], f[y] - sum[x]),
                            std::min(w - sum[y], f[x] - sum[y]));
            sum[k] = sum[x] + sum[y];
            //这里是递归求解的过程改成了递推
            //x,y分别是k的左右儿子
        }
    }
    printf("%lld\n", f[rt] <= 0 ? -1ll : f[rt]);
    return 0;
}
```

---

## 作者：flyingfrog (赞：7)

原题链接：[Link](https://www.luogu.com.cn/problem/CF1578L)
## Description
给定 $n\in{[2, 10^5]}$，$m\in{[n - 1, 10^5]}$。

一张 $n$ 个点，$m$ 条边的无向图，每条边有一个宽度限制 $w_i$。每个点上有一个糖果，吃了第 $i$ 个点上的糖果会使身体增宽 $c_i$。你也可以**经过一个点而不吃掉它的糖果**。你能够通过一个边 $i$，当且仅当你当前身体的宽度 $\le w_i$。

你需要从点 $1$ 开始，吃掉所有点上的糖果，但**不是必须要返回点** $1$。请求出你最大的初始身体宽度，使得你能吃掉所有糖果。若无法吃完则输出 $-1$。
## Solution
首先，为了使身体宽度尽可能大，我们需要用限制尽可能小的边将所有的点连通，换句话说，**建立一棵最大生成树**。

这时我们尝试发掘原问题的一些有用性质。考虑生成树上最晚加入的边，它将不连通的两棵树连通，且这两棵树中的任意一条边的边权大于这条边。记这条边为 $e$，边权为 $w$，两棵树分别为 $a$，$b$，树上点权的和分别为 $sum_a$，$sum_b$。

考虑吃每个点的顺序。这里有个结论：**在两棵树间来回吃不会比先吃完两棵树中的一棵更优**。假设先吃完 $a$ 的糖果，因为无论在吃完 $a$ 之前有没有去过 $b$，最后都要从已经空了的 $a$ 经过 $e$ 到 $b$ 去，那么应当让最后通过 $e$ 时的身体宽度最小，显然在去 $b$ 前吃完 $a$ 会更优。

在吃完 $a$ 后，为了通过 $e$，必须有 $w_e \ge sum_a$，而为了吃完 $b$，我们可以先求出原问题在 $b$ 上的解 $ans_b$，这时又有 $ans_b \ge sum_a$，那么在先吃 $a$ 问题的解为 $\min\{w_e - sum_a, ans_b - sum_a\}$，而同理，在先吃 $b$ 时问题的解为 $\min\{w_e - sum_b, ans_a - sum_b\}$。将两者取 $\max$ 即得到最终解：
$$ \max\{\min\{w_e - sum_a, ans_b - sum_a\},\min\{w_e - sum_b, ans_a - sum_b\}\}$$
因此我们只需要在建最大生成树时递推求出子问题的解即可。kruskal 重构树维护。
## AC Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, u, v, w, val[100002], f[200002], k, sum[200002], ans[200002], cnt;
struct _edge{
	int u, v, w;
}eg[500002];
int find(int x){return (x == f[x]) ? x : (f[x] = find(f[x]));}

signed main(){
	cin >> n >> m;	k = n;
	for(int i = 1; i <= n; i ++){
		cin >> val[i];
		f[i] = i, f[i + n] = i + n, sum[i] = val[i], ans[i] = 0x3f3f3f3f;
	}
	for(int i = 1;i <= n + m;i ++) f[i] = i;
	for(int i = 1; i <= m; i ++)
		cin >> eg[i].u >> eg[i].v >> eg[i].w;
	sort(eg + 1, eg + 1 + m, [](_edge a, _edge b){return a.w > b.w;});
	for(int i = 1; i <= m; i ++){
		int fu = find(eg[i].u), fv = find(eg[i].v), w = eg[i].w;
		if(fu == fv)	continue;
		f[fu] = f[fv] = ++ k;
		sum[k] = sum[fu] + sum[fv];
		ans[k] = max(min(w - sum[fu], ans[fv] - sum[fu]),
					 min(w - sum[fv], ans[fu] - sum[fv]));
	}
	cout << (ans[k] > 0 ? ans[k] : -1);
	
	return 0;
}
```

---

## 作者：hegm (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF1578L)



------------

一眼重构树。

我们按边权总大到小建立 `Kruskal重构树` 。

那么两点的 $lca$ 就是两者的最大瓶颈路。

既然我们吃糖，那么重构树上的点会越来越少。

每次某个点消失，必须将其的一棵子树全吃完，并且能走到另一棵子树。

考虑贪心，我们二分一个初始宽度，对于当前点，我们贪心的将 $sum$ 比较小的点吃掉，再走向另一个点。

那么当前是否合法可以检查出。

```cpp
if(sum[ls]<sum[rs])to=ls;
else to=rs;
if(sum[ls]==sum[rs])
{
	if(val[ls]>val[rs])to=ls;
	else to=rs;
}
w+=sum[to];
if(w>val[now])return 0;
to=ls+rs-to;
return check(to,w);
```

在上方 $val$ 表示这条边的限制。



------------
但是遗憾的是，这种思路是错误的。

[$hack$](https://www.luogu.com.cn/discuss/523022)

我们考虑错误原因，我们的贪心只能保证先去的子树 $sum$ 最小，却不能保证另一颗子树的限制能满足。

先取了小子树，不一定能去大子树，但是可能取完大子树，还能去小子树。

那有没有什么全部情况都能考虑到的解法哪？

我们从叶子节点开始合并。

两种选择

1. 先去左儿子

2. 先去右子树

$ans_i$ 表示 $i$ 的答案，$sum_i$ 表示 $i$ 为根节点，所有糖果的 $c$ 之和 。 $val_i$ 表示第 $i$ 点的限制。

那么 

```cpp
ans[cnt]=max(min(e[i].w,ans[v])-sum[u],min(e[i].w,ans[u])-sum[v]);
sum[cnt]=sum[u]+sum[v];
```

综上，时间复杂度 $O(n\log n)$


------------

$ \texttt{CODE}$

```cpp
#include<bits/stdc++.h>
#define N 5000005
#define int long long
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,m,a[N],cnt,f[N],sum[N],ans[N];
struct edge 
{
	int u,v,w;
}e[N*2];
int find(int now)
{
	if(f[now]==now)return now;
	return f[now]=find(f[now]);
}
bool cmp(edge a,edge b){return a.w>b.w;}
signed main()
{
	n=read(),m=read();cnt=n;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)
	{
		e[i].u=read();
		e[i].v=read();
		e[i].w=read();
	}
	sort(e+1,e+1+m,cmp);
	for(int i=1;i<=2*n;i++)f[i]=i,sum[i]=a[i];
	memset(ans,0x3f,sizeof(ans));
	for(int i=1,u,v;i<=m;i++)
	{
		u=find(e[i].u);v=find(e[i].v);
		if(u!=v)
		{
			++cnt;
			f[u]=f[v]=cnt;
			ans[cnt]=max(min(e[i].w,ans[v])-sum[u],min(e[i].w,ans[u])-sum[v]);
			sum[cnt]=sum[u]+sum[v];
		}
	}
	if(ans[cnt]<=0)cout<<-1<<"\n";
	else cout<<ans[cnt]<<"\n";
	return 0;
}
```

---

## 作者：_fairytale_ (赞：2)

顺便推销我的 [kruskal 重构树 学习笔记](https://www.luogu.com.cn/blog/280999/kruskal-zhong-gou-shu-xue-xi-bi-ji)。

感觉第一篇题解在关键的地方没有讲得很清楚（应该是我太蒻了），所以这里写篇题解讲一下细节。

一个显然的贪心是我们尽量走边权大的边，于是可以想到最大生成树。然后感觉很妙的点是把自身宽度的变大转化为断掉这棵树上的一些边。最先断掉的一定是最大生成树上边权最小的边，所以必须保证这条边断掉之前至少走完这条边连接的两棵子树中的一个。

同样地，我们考虑最大生成树上边权最小的边 $(u,v,w)$，不难发现最优决策一定是先走完其中一棵子树，然后经过这条边。假设这个问题的总答案是 $ans$，$S_u,S_v$ 分别表示 $u,v$ 子树中糖果值的和，$X_u,X_v$ 分别表示单独走完以 $u,v$ 为根的子树的最小初始宽度。不妨钦定先吃完子树 $u$，则可以得到如下不等式组：
$$
\begin{cases}
S_u+ans\le w\\
S_u+ans\le X_v
\end{cases}
$$

其中第一个式子意思是必须保证你在吃完 $u$ 之后能通过这条边，第二个式子意思是必须保证吃完 $u$ 之后还能走完以 $v$ 为根的子树。

因此 $ans=min(w-S_u,X_v-S_u)$。

先吃完子树 $v$ 同理。

然后不断找到最大生成树上边权最小的边，kruskal 重构树即可。

```cpp
#include<bits/stdc++.h>
#define re register
#define il inline
#define int long long
#define rep(x,qwq,qaq) for(re int (x)=(qwq);(x)<=(qaq);++(x))
#define per(x,qwq,qaq) for(re int (x)=(qwq);(x)>=(qaq);--(x))
#define dbg(x) cerr<<#x<<":"<<x<<" "
#define cend cerr<<'\n'
using namespace std;
#define inf 0x3f3f3f3f3f3f3f3f
#define maxn 101001
int n,m;
int c[maxn];
struct edge{
	int u,v,w;
}e[maxn];
int fa[maxn<<1],tot,val[maxn<<1];
int fd(int x){return x==fa[x]?x:fa[x]=fd(fa[x]);}
vector<int>g[maxn<<1];
il void kruskal(){
	tot=n;
	rep(i,1,n+n)fa[i]=i;
	sort(e+1,e+m+1,[](const edge &x,const edge &y){
		return x.w>y.w;
	});
	rep(i,1,m){
		int fu=fd(e[i].u),fv=fd(e[i].v);
		if(fu==fv)continue;
		val[++tot]=e[i].w;
		fa[tot]=fa[fu]=fa[fv]=tot;
		g[tot].emplace_back(fu),g[tot].emplace_back(fv);
	}
}
int x[maxn<<1],s[maxn<<1];
void dfs(int u){
	if(u<=n)s[u]=c[u],x[u]=inf;
	for(int v:g[u]){
		dfs(v);
		s[u]+=s[v];
	}
	if(u>n)x[u]=max(min(val[u]-s[g[u][1]],x[g[u][0]]-s[g[u][1]]),min(val[u]-s[g[u][0]],x[g[u][1]]-s[g[u][0]]));
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin>>n>>m;
    rep(i,1,n)cin>>c[i];
    rep(i,1,m)cin>>e[i].u>>e[i].v>>e[i].w;
    kruskal();
    dfs(tot);
    cout<<(x[tot]>0?x[tot]:-1);
	return 0;
}
```

---

## 作者：Redamancy_Lydic (赞：1)

挖性质好题。

## 分析

首先注意到一个性质，最开始的时候是没有宽度的，即可以在图上随便走，所以从 $1$ 号节点开始的限制等于无。

然后根据贪心的思想，走的时候我们要尽可能的使路径上最小的边权最大，所以不难想到要在最大生成树上跑。

先把最大生成树求出来，然后为了方便建上 Kruskal 重构树，以下分析在重构树上面考虑。

现在我们考虑怎样吃是最优的。容易发现，我们一定是先吃完一颗子树再去吃另一棵子树最优。简要证明一下，如果我们还没吃完一颗子树就去吃另一棵，那么当我们回来吃这颗子树的时候时宽度一定会增大，完全不优，所以证明完毕。

性质都出来以后，我们考虑如何合并子树信息，我们设 $dp_i$ 表示吃完子树 $i$ 所需的最大初始宽度，$sum_i$ 表示子树 $i$ 的点权和。

现在我们要合并两棵子树 $a$ 和 $b$ 的信息，分两种情况，即先吃 $a$ 再吃 $b$ 和先吃 $b$ 再吃 $a$。

以第一种情况为例，设 $u$ 表示 $a$ 和 $b$ 子树的父亲节点，$w$ 为它的点权。因为我们求的是最大生成树，所以这个点的点权一定是当前所有点中最小的。吃完 $a$ 子树以后，如果我们想要走到 $b$，那么需要保证 $w\ge sum_a+dp_u$ 且 $dp_b\ge sum_a+dp_u$，所以得出 $dp_u=\min(w-sum_a,dp_b-sum_a)$。

另一种情况同理，可以得到转移方程为
$$dp_u=\max(\min(w-sum_a,dp_b-sum_a),\min(w-sum_b,dp_a-sum_b))$$

正常递归处理即可。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=(s<<3)+(s<<1)+(ch^48);ch=getchar();}
	return w*s;
}
const int maxn=5e5+10;
int n,m,k;
struct no
{
	int x,y,v;
	inline friend bool operator < (no x,no y)
	{
		return x.v>y.v;
	}
}edge[maxn];
int fa[maxn];
int gf(int x){return fa[x]==x?x:fa[x]=gf(fa[x]);}
vector<int> G[maxn];
int c[maxn];
void add(int x,int y)
{
	G[x].push_back(y);
	G[y].push_back(x);
}
int dp[maxn],sum[maxn];
void dfs(int u,int fa)
{
	int mi=1e9+7;
	int d[3],tt=0;
	for(auto y : G[u])
	{
		if(y==fa)continue;
		dfs(y,u);
		d[++tt]=y;
	}
	if(!tt)return ;
	int x=d[1],y=d[2],w=c[u];
	dp[u]=max(min(w-sum[x],dp[y]-sum[x]),min(w-sum[y],dp[x]-sum[y]));
	sum[u]=sum[x]+sum[y];
}
signed main()
{	
	cin>>n>>m;
	for(int i=1;i<=n;i++)c[i]=read();
	for(int i=1;i<=m;i++)
	{
		edge[i]={read(),read(),read()};
	}
	for(int i=1;i<=n+m+1;i++)fa[i]=i;
	for(int i=1;i<=n;i++)sum[i]=c[i],dp[i]=1e9+7;
	sort(edge+1,edge+m+1);
	int tot=0,cnt=n;
	for(int i=1;i<=m;i++)
	{
		int fx=gf(edge[i].x),fy=gf(edge[i].y);
		if(fx!=fy)
		{
			c[++cnt]=edge[i].v;
			add(fy,cnt);
			add(fx,cnt);
			fa[fx]=fa[fy]=cnt;
			if(++tot==n-1)break;
		}
	}
	dfs(cnt,-1);
	if(dp[cnt]<=0)cout<<-1;
	else cout<<dp[cnt];
	return 0;
}
```

记得点赞欧。

---

## 作者：_JF_ (赞：1)

[Link](https://www.luogu.com.cn/problem/CF1578L)

比较厉害的题。

简化问题，如果是不考虑吃能不能走的话，那很显然我们要求路径上最小边最大，这显然是重构树。

看能不能考虑建出重构树以后，往树上思考，能够发现，如果我每次吃了糖果，增加了宽度，那必然会造成一些边不能走，**换言就是重构树上一些子树，我走不进去了。** 这就把这个题转换成一个树上问题，我维护的是路径最小值最大，可以保证正确性。

如果一个子树 $u$ 的点权小于当前宽度，那说明这个子树里面的所有点就必须要被吃完。因为要尽可能不留下点没吃，这说明我们可以从限制最大的点开始考虑。（不然以后体型变大无法吃了，不符合题意。）

因为要求求初始值最大，最值嘛，考虑动归吧。考虑设 $dp_u$ 表示走完以 $u$ 为根的子树，能有的初始值最大是多少。

每个点（非叶子）有且仅有两个儿子 $x,y$。考虑转移。

发现对于两个儿子，完整走完一个，再去走另一个，相交走一部分 $x$ 去走 $y$，其实是不劣的，因为你无论怎么走，吃完全部以后，都要回到当前点 $u$，而这个点的点权是路径上的最小值，非常关键。（因为下面子树内的点权都会不小于它。）

这下就可以转移了啊，直接根据定义即可：

$$dp_u=\max(\min(dp_y-s_x,c_u-s_x),\min(dp_x-s_y,c_u-s_y))$$

本质上就是分类讨论要先走 $x$，还是先走 $y$ 的一个动态规划。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =4e5+10;
#define int long long 
struct node{
	int u,v,w;
}a[N];
int Ans[N],n,m,siz[N],v[N],F[N],c[N];
vector<int> g[N<<1];
int Find(int x){
	return x==F[x]?x:F[x]=Find(F[x]); 
}
bool cmp(node a,node b){
	return a.w>b.w;
}
void Kuskral_CG(){
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=2*n-1;i++)	F[i]=i; 
	int cnt=n;
	for(int i=1;i<=m;i++){
		int u=Find(a[i].u),v=Find(a[i].v);
		if(u==v)	continue;
		cnt++,F[u]=cnt,F[v]=cnt,g[cnt].push_back(u),g[cnt].push_back(v),c[cnt]=a[i].w;
	}
}
void dfs(int u,int fath){
	if(g[u].size()==0)	{siz[u]=v[u];return ;}
	if(c[g[u][0]]>c[g[u][1]])	dfs(g[u][1],u),dfs(g[u][0],u);
	else	dfs(g[u][0],u),dfs(g[u][1],u);
	siz[u]=siz[g[u][0]]+siz[g[u][1]]+v[u];
	Ans[u]=min(c[u]-siz[g[u][0]],Ans[g[u][1]]-siz[g[u][0]]);
	Ans[u]=max(Ans[u],min(c[u]-siz[g[u][1]],Ans[g[u][0]]-siz[g[u][1]]));
}
signed main(){
	memset(Ans,0x7f,sizeof(Ans));
	cin>>n>>m;	
	for(int i=1;i<=n;i++)	cin>>v[i];
	for(int i=1;i<=m;i++)	cin>>a[i].u>>a[i].v>>a[i].w;
	Kuskral_CG(),dfs(2*n-1,0);	
	cout<<((Ans[2*n-1]<=0)?-1:Ans[2*n-1]);
} 
```


---

## 作者：Z1qqurat (赞：1)

感觉这题的思路非常的阿妹胫骨啊！吾辈试着用一种不一样的正向思维理解一下这题。

* 首先虽然这是一个图上问题，但是吾辈的目的是在每个点都可达的前提下保证所有边的边权（也就是限制）尽量大。所以可以直接找出一棵原图最大生成树，在这棵生成树上解决肯定是最优的（可以发现很多 Kruskal 重构树的题都是这一类的思路，化图为树）。这样会影响结果吗？Non。你保证走到每个点的边都尽量大，那不肯定最优了。

* 接下来吾辈考虑怎么规划这些边的访问顺序。考虑我们求最大生成树的过程，对于边 $(u, v, w)$，假设 $root_u \ne root_v$，也就是说吾辈合并 $u, v$。设 $f(u, v)$ 表示经过了边 $(u, v, w)$ 之后的最大初始宽度。其实吾辈对真正的访问顺序并不在意，只需要知道每条边的吃糖方向。因为如果从 $x$ 转移到 $y$，选择将 $x$ 子树内的糖都吃完肯定不劣（参考榜一题解的证明），所以吾辈可以这样转移 $f(u, v)$：

  * 如果从 $u$ 吃到 $v$，那么 $f(u, v) = \min(w - sum_u, g_v - sum_u)$，其中 $g_v$ 表示吃完 $v$ 子树内的糖的最大初始宽度。这是因为从 $u$ 到 $v$ 要满足 $w$ 的限制，到了子树 $v$ 又要满足 $g_v$ 的限制。
  * 如果从 $v$ 吃到 $u$，那么 $f(u, v) = \min(w - sum_v, g_u - sum_v)$。

  所以说：
  $$
  f(u, v) = \max(\min(w - sum_u, g_v - sum_u), \min(w - sum_v, g_u - sum_v))
  $$

* 但是现在吾辈怎么求出 $g_u$ 呢？需要另外专门求吗？Non。考虑一棵子树内最强的限制来自哪里，那肯定是这棵子树内的**边权最小的边**啊，只要解决了它这整棵子树都可以顺利吃完了。所以如果吾辈构建一棵 Kruskal 重构树，这样可以直接将 $f(u, v)$ 简化为 $f_{new}$，$new$ 是这条边在重构树上对应的节点。最后想要得出整棵子树的结果就可以查询 $f_{root}$，$root$ 是最后加进去的那条边，也就是整棵树中边权最小的边。阿妹胫骨！

感觉榜一题解的实现很精细简洁，大家可以去看他的代码。

---

## 作者：elbissoPtImaerD (赞：0)

首先对于点 $u,v$，我们只需关注 $u,v$ 的所有路径中，边权最小值最大的那条即可，考虑建出小根 Kruskal 重构树。

再分析一下决策的性质，不妨考虑重构树上边权最小的边 $e(u,v,w)$。记断掉此边后的两棵树中包含 $u$ 的那颗为 $T_u$，$v$ 同理。不妨假设 $T_u$ 比 $T_v$ 先被吃光。由于 $e$ 是最小边，所以 $e$ 可以通过等价于整棵树 $T$ 连通，所以我们应保证在吃光 $T_u$ 能通过 $e$，那么在吃光 $T_u$ 前不吃 $T_v$ 能使吃光 $T_u$ 时的体重最小，显然不劣。

考虑树形 DP，$f_u$ 表示保证 $u$ 子树被吃光的最大初始体重。

考虑转移，不妨用 $l,r$ 分别表示 $u$ 在重构树上的左右儿子，$w$ 是对应边权，$s_u$ 为 $u$ 子树的 $c$ 值之和（虚点 $c$ 值为 $0$），下面用 $f_l,f_r$ 计算 $f_u$。

不妨设先吃完 $T_l$，那么 $f_u = \min(w,f_r)-s_l$，含义是吃完 $T_l,T_r$ 均能往回走，注意右子树的限制是 $f_r$ 而非 $w-s_r$，因为此时不需要再从 $T_r$ 走出来了。

```cpp
il void Solve()
{
  int n,m;rd(n),rd(m);
  const int N=n<<1;
  ve<LL>s(N);
  for(int i=0;i<n;++i) rd(s[i]);
  ve<array<int,3>>e(m);
  for(auto&[w,u,v]:e) rd(u),rd(v),--u,--v,rd(w);
  sort(rll(e));
  ve<int>fa(N);
  iota(all(fa),0);
  function<int(int)>getf=[&](int x){return fa[x]^x?fa[x]=getf(fa[x]):x;};
  int ind=n;
  const LL inf=46e17;
  ve<LL>f(N,inf);
  for(auto[w,u,v]:e) {
    int l=getf(u),r=getf(v);
    if(l!=r) {
      int t=ind++;
      fa[l]=fa[r]=t,s[t]=s[l]+s[r],f[t]=max(min<LL>(w,f[r])-s[l],min<LL>(w,f[l])-s[r]);
    }
  }
  wrt(f[ind-1]>0?f[ind-1]:-1);
  return;
}
```

[$\color{green}{\checkmark}$](https://codeforces.com/problemset/submission/1578/260931063)

---

