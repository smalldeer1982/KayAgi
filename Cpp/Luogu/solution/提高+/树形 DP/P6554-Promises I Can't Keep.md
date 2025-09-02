# Promises I Can't Keep

## 题目背景

>I had so much certainty  
Til that moment I lost control  
And I've tried but it never was up to me  
I've got no worse enemy  
Than the fear of what's still unknown  
And the time's come to realize there will be  
Promises I can't keep

## 题目描述

RFMC 给了你一个电路，一个电源，他希望你能把电源接在电路的某一个节点上，让电流流通，并答应给你电路显示屏上的数那么多钱。

这个电路有 $n$ 个节点，每个节点有一个权值 $val_i$，以 $n-1$ 条导线互相连通。你可以把电源接在任意一个起点上。接着，电流从这个节点开始流。若当前电源接到了一个节点 $u$，则接下来电流会**等概率**且**不重复经过一个点地**流向**一个叶子节点**，电流流过的所有节点的权值即为电路显示屏上的数（叶子节点即为 **除了 $u$** 的度数为 1 的节点）。

现在你有 $n$ 种接电源的选择，你希望接上电源以后期望得分越高越好，所以你现在就要在规定的时间内求出这 $n$ 种期望值中最大的的一个。

## 说明/提示

样例一的解释：

电源接在 5 号节点时有两种情况：$5\rightarrow 1\rightarrow 2\rightarrow 3$ 或 $5\rightarrow 1\rightarrow 2\rightarrow 4$，两种情况得分分别为 8 和 6，期望值即为 7，可以证明没有其他节点接通电源的期望值比 7 大。

---

**本题采用捆绑测试，每一档部分分对应一个 subtask。**

对于 $30\%$ 的数据，保证 $2<n\le 10^3$。  
对于另外 $20\%$ 的数据，保证是一条链。  
对于所有的数据，保证 $2<n\le 5\times10^5,\  |val_i|\le10^4$。

本题的 special judge 代码已经在附件中给出。

附：本题数据量较大，可以采用更快的读入方法。（标程在用 ```scanf``` 的情况下可以通过）

~~后记：按照题目名称，RFMC 是不会遵守诺言的（大雾~~

题目名其实是一首歌名啦。

## 样例 #1

### 输入

```
5
1 2
1 5
2 3
2 4
2 3 1 -1 2```

### 输出

```
7.0000```

# 题解

## 作者：UltiMadow (赞：6)

~~本来T2是个DS题的，但是发现撞题之后就换上了这一道~~

先来看部分分吧

#### subtask 0
简单暴力，以每个点为根做一遍dp

#### subtask 1
链的情况大概可以前缀和乱搞，不多说了

#### 正解
换根dp（个人感觉不难想吧）

令 $cnt_u$ 为以 $u$ 为根节点的子树中叶子节点的个数

设 $g_u$ 为以 $u$ 为根节点的期望值 $\times cnt_u$，这里乘是为了精度不要有误差

设 $f_u$ 为以 $u$ 为根节点的整个树的期望值乘以 $u$ 为根节点的整棵树中的叶子节点个数

第一次dfs预处理出 $g$ 和 $cnt$

显然有：  
当 $u$ 为叶子节点时 $cnt_u=1$，$g_u=val_u$  
当 $u$ 为非叶子节点时 $cnt_u=\sum_{v\in son_u}cnt_v$，$g_u=val_u\times cnt_u+\sum_{v\in son_u}g_v$

第二次dfs计算 $f$

显然有：  
当 $u$ 为根节点时 $f_{u}=g_{u}$  
当 $u$ 为叶子节点时 $f_u=f_{fa}-val_u-val_{fa}+(cnt_{root}-1)\times val_u$  
整理得：$f_u=f_{fa}-val_{fa}+(cnt_{root}-2)\times val_u$  
当 $u$ 为非叶子节点时 $f_u=f_{fa}-g_u-cnt_u\times val_{fa}+g_u+(cnt_{root}-cnt_u)\times val_u$  
整理得：$f_u=f_{fa}-cnt_u\times val_{fa}+(cnt_{root}-cnt_u)\times val_u$

code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 500010
using namespace std;
int n,rt;
double val[MAXN];
double f[MAXN],g[MAXN];
int cnt[MAXN],lef[MAXN];
struct Node{int to,next;}Edge[MAXN<<1];
int Head[MAXN],cnt_Edge;
void Add_Edge(int u,int v){Edge[++cnt_Edge]=(Node){v,Head[u]};Head[u]=cnt_Edge;}
void dp1(int u,int fa)
{//第一次dfs
	for(int i=Head[u];i;i=Edge[i].next)
	{
		int v=Edge[i].to;
		if(v==fa)continue;
		dp1(v,u);cnt[u]+=cnt[v];
		g[u]+=g[v];
	}
	g[u]+=val[u]*cnt[u];
	if(!cnt[u])g[u]=val[u],cnt[u]=1,lef[u]=1;
}
void dp2(int u,int fa)
{//第二次dfs
	for(int i=Head[u];i;i=Edge[i].next)
	{
		int v=Edge[i].to;
		if(v==fa)continue;
		if(lef[v])f[v]=f[u]-val[u]+val[v]*(cnt[rt]-2);
		else f[v]=f[u]-val[u]*cnt[v]+val[v]*(cnt[rt]-cnt[v]);
		dp2(v,u);
	}
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;scanf("%lld%lld",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}
	for(int i=1;i<=n;i++)scanf("%lf",&val[i]);
	for(int i=1;i<=n;i++)
		if(Edge[Head[i]].next!=0){rt=i;break;}//找非叶子节点为根
	dp1(rt,0);f[rt]=g[rt];dp2(rt,0);
	double ans=-99999999999;
	for(int i=1;i<=n;i++)ans=max(ans,f[i]/(cnt[rt]-lef[i]));//计算期望
	printf("%.4lf",ans);
	return 0;
}
```

---

## 作者：pomelo_nene (赞：4)

UM 的神题！ /qq

比赛没多少时间只打了 20 多分钟，一发 WA 掉了（

因为不会 T6 所以来看这道了。。。

---

思路是找到一个 **不是叶子节点** 的节点当做整棵树的根，将整棵树转换成有根树进行 dp。

目标是求出这个节点子树有多少个叶子节点以及根节点的答案。

设当前节点 $i$ 的答案乘上 $leaf_i$ 为 $val_i$，有 $leaf_i$ 个叶子节点。

- 如果当前节点 $i$ 为叶子节点，$val_i$ 显然为 $a_i$；   
- 否则，计算所有儿子的答案并加上所有的贡献，$val_i = a_i \times leaf_i +\sum_{j \in \texttt{以i为父亲的节点}} val_j$。

得到了根节点的答案。再次计算 $dp$，$dp_i$ 意为以 $i$ 为根节点的整棵树的答案乘上以 $i$ 为根节点后整棵树的叶子数，设节点 $i$ 的父亲为 $fa_i$，整棵树有 $lev$ 个叶子节点。

现在可以看成无根树，通过以前计算出的答案进行计算。也就是 换根 dp。

- 根节点跳过，$dp_i=val_i$；   
- 叶子节点，要通过父亲节点及原设根节点计算，则 $dp_i=dp_{fa_i}-a_{fa_i}+(lev-2) \times a_i$；   
- 非叶子节点，则 $dp_i=dp_{fa_i}-a_{fa_i} \times leaf_i + a_i \times (lev-leaf_i)$。

代码中与讲解和方程中的字母含义可能不同。

常数较大，请打开 `O2` 开关，否则会超时。

另外，去掉 `SpecialSolve` 之后会挂掉链的点（因为 UM 数据出的毒瘤），所以说要加特判，也就是如果树是链，答案为 $\max(sum,\dfrac{sum+\max\{a_i\}}{2})$。其中 $sum = \sum_{i=1}^n a_i$。

欢迎 hack。

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<long long> G[500005];
long double maxsss=-9999999999;
long long root=0;
long long n,depth[500005],apart[500005],leaf[500005];
long double val[500005],dp[500005],a[500005],sum;
namespace SpecialSolve
{
	void Main(int root){
		printf("%.4Lf",(sum+maxsss)/2);
	}
}
void Check()
{
	int one=0,two=0,roots=0;
	for(int i=1;i<=n;++i)
	{
		if(G[i].size()==1)	++one,roots=i;
		if(G[i].size()==2)	++two;
	}
	if(one==2 && two==n-2)
	{
		SpecialSolve::Main(roots);
		exit(0);
	}
}
void dfs1(long long now,long long pre)
{
	for(unsigned long long i=0;i<G[now].size();++i)
	{
		long long to=G[now][i];
		if(to==pre)	continue;
		dfs1(to,now);
		leaf[now]+=leaf[to];
		val[now]+=val[to];
	}
	val[now]+=a[now]*leaf[now];
	if(leaf[now]==0)	val[now]=a[now],leaf[now]=1;
}
void dfs2(long long now,long long pre)
{
//	if(now!=1)	val[now]+=(val[pre]-val[now]*leaf[now])*(leaf[pre]-leaf[now]);
	for(unsigned long long i=0;i<G[now].size();++i)
	{
		long long to=G[now][i];
		if(to==pre)	continue;
		if(G[to].size()==1u)	dp[to]=dp[now]-a[now]+a[to]*(leaf[root]-2);
		else	dp[to]=dp[now]-a[now]*leaf[to]+a[to]*(leaf[root]-leaf[to]);
		dfs2(to,now);
	}
}
int main(){
	scanf("%lld",&n);
	for(long long i=2;i<=n;++i)
	{
		long long u,v;
		scanf("%lld %lld",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	bool flag=true;
	for(long long i=1;i<=n;++i)	scanf("%Lf",&a[i]),sum+=a[i],flag&=(a[i]>0),maxsss=max(maxsss,a[i]);
	Check();
	long long leaves=0;
	for(long long i=1;i<=n;++i)	if(G[i].size()==1u)	++leaves;
	for(long long i=1;i<=n;++i)
	{
		if(G[i].size()==1u)	apart[i]=leaves-1;
		else	apart[i]=leaves,root=i;
	}
	dfs1(root,0);
	dp[root]=val[root];
//	for(long long i=1;i<=n;++i)	printf("%lld\n",val[i]);
	dfs2(root,0);
	long double ans=-998244353000;
	for(long long i=1;i<=n;++i)	ans=max(ans,dp[i]/(long double)(leaf[root]-(leaf[i]==1?1:0)));
	printf("%.4Lf",ans);
	return 0;
}
```

真的很慢，我也不知道为什么真的很慢。

---

## 作者：BzhH (赞：3)

刚开始理解错题意了，以为是电流会等概率的流向它的儿子节点，恰好样例又可以过，结果就一直WA，所以说语文还是很重要的.

------------
总结一下题意，求的是所有以$u$为根的叶子节点到$u$的路径和除以$u$为根的叶子节点数量的最大值,很明显可以用换根DP来做.

假设第一遍dfs时的根为$root,f_u$表示路径和,$w_u$表示该点的权值,$cnt_u$表示以$u$为根的子树中叶子节点的数量.

对于任意一个节点作为根
若当前节点$v$为之前的叶子节点

$f_v=f_u-w_u-w_v-(cnt_{root}-1)*w_v$

若不是

$f_v=f_u-w_u*cnt_v+(cnt_{root}-cnt_v)*w_v$

显然,只需要第一遍dfs是求出$f_{root},cnt$就可以了.

代码
```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N = 1e6 + 5;

int head[N], ver[N], net[N], idx;
int cnt[N], dg[N], root;
bool is[N];
double sum[N], f[N], w[N];

void add(int a, int b)
{
    net[idx] = head[a];
    ver[idx] = b;
    head[a] = idx++;
}

void dfs1(int u, int fa)
{
    for (int i = head[u]; ~i; i = net[i])
    {
        int v = ver[i];
        if (v == fa)
            continue;
        dfs1(v, u);
        cnt[u] += cnt[v];
        sum[u] += sum[v] + w[u] * cnt[v];
    }    
    if (!cnt[u])
        sum[u] = w[u], cnt[u] = 1, is[u] = true;
}

void dfs2(int u, int fa)
{
    for (int i = head[u]; ~i; i = net[i])
    {
        int v = ver[i];
        if (v == fa)
            continue;
        if (is[v])
            f[v] = f[u] - w[u] + (cnt[root] - 2) * w[v];
        else
            f[v] = f[u] - w[u] * cnt[v] + (cnt[root] - cnt[v]) * w[v];
        dfs2(v, u);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
        dg[u]++, dg[v]++;
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%lf", &w[i]);      
        if (dg[i] > 1)
            root = i;//找出根节点
    }
    dfs1(root, 0);
    f[root] = sum[root];
    dfs2(root, 0);
    double ans = -1e13;
    for (int i = 1; i <= n; i++)
        ans = max(ans, (double)f[i] / (cnt[root] - is[i]));//计算期望
    printf("%.4lf", ans);
    return 0;
}
```



---

## 作者：lgswdn_SA (赞：2)

# Promises I Can't Keep

验题人过来写一发题解。

简化一下：一棵树，选择一个节点为根，等概率选择一个儿子，然后这样下去得到一条链。求出应该选择哪个根，才能让链的期望权值和最大。

## $\texttt{Subtask 0}$

一开始想到的树形 $dp$，暴力枚举根，然后 $f_{u}$ 表示以 $u$ 为根的子树，得到的期望权值和。$cnt_u$ 指字数内叶节点数量。

$f_u=\frac{\sum f_v\times cnt_v}{cnt_u}+a_u$

最后遍历所有根即可。

```cpp
int a[N],cnt[N]; double f[N];
void dfs(int u,int fa){
	f[u]=0; cnt[u]=0;
	for(int i=hd[u],v;i;i=e[i].nxt)
		if((v=e[i].to)!=fa){
			dfs(v,u);
			f[u]+=f[v]*cnt[v],cnt[u]+=cnt[v];
		}
	if(!cnt[u]) f[u]=a[u],cnt[u]=1;
	else f[u]=f[u]*1./cnt[u]+a[u];
}
signed main(){
	int n; scanf("%lld",&n); double ans=-1e18;
	for(int i=1,u,v;i<n;i++) scanf("%lld%lld",&u,&v),add(u,v),add(v,u);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++){dfs(i,0); ans=max(ans,f[i]);}
	printf("%.4lf",ans);
	return 0;
}
```


## $\texttt{Subtask 1}$

对于一条链，我们可以用前缀和优化计算 $f$，即在 $O(1)$ 的时间算出以 $i$ 为根的期望权值和。

即枚举 $x$，求$\max {(sum_{(1,x-1)}+sum_{(x+1,n)})/2+ax}$

```cpp
for(int x=2;x<n;x++) ans=max(ans,(s[n]-a[x])/2.+a[x]);
ans=max(ans,s[n]*1.);
```

## $\texttt{Subtask 2}$

我们还是看 $\texttt{Subtask 1}$，我们可以用换根 $dp$ 的思想（被出烂的qwq），总体进行两次 $dfs$，然后便可求得每一个点为根的时候的期望值。

```cpp
int n,root,cnt[N]; double a[N],f[N],g[N],ans=-2e18; bool isLeaf[N];
void dfs(int u,int fa){
	for(int i=hd[u],v;i;i=e[i].nxt)
		if((v=e[i].to)!=fa){
			dfs(v,u);
			cnt[u]+=cnt[v], f[u]+=f[v]; //cnt为子树内叶子节点，f为子树中的总答案 
		}
	if(isLeaf[u]) cnt[u]=1;
	f[u]+=a[u]*cnt[u];
}
void dfs2(int u,int fa){
	if(u==root) g[u]=f[u];
	for(int i=hd[u],v;i;i=e[i].nxt)
		if((v=e[i].to)!=fa){
			if(isLeaf[v]) g[v]=g[u]-a[u]+a[v]*(cnt[root]-2);
			else g[v]=g[u]-a[u]*cnt[v]+a[v]*(cnt[root]-cnt[v]);
			dfs2(v,u);
		}
}
signed main(){
	scanf("%lld",&n);
	for(int i=1,u,v;i<n;i++)
		scanf("%lld%lld",&u,&v), add(u,v), add(v,u);
	for(int i=1;i<=n;i++){
		scanf("%lf",&a[i]);
		if(ecnt[i]>1) root=i;
		else isLeaf[i]=1;
	}
	dfs(root,0), dfs2(root,0);
	for(int i=1;i<=n;i++) ans=max(ans,g[i]/(cnt[root]-isLeaf[i]));
	printf("%.4lf",ans);
	return 0;
}
```

补充一下：对于错了 $\texttt{Subtask 1}$ 的人，你们的错误原因应该是 $ans$ 初始化太大（需要是一个很小的负数）或者没有考虑到负数的情况。因为验题的时候我强烈要求加强这个 Subtask 防止有人直接输出 $\sum a$ 水过去。

---

## 作者：a1co0av5ce5az1cz0ap_ (赞：1)

为什么题解区都在写一坨坨的式子。。

考虑直接换根 dp，记 $f_i$ 表示在 $i$ 的位置到所有叶子节点（可以包括自己）的距离（这里指路径的点权和）之和。

那么对于一条边 $a\rightarrow b$，假设我们已经算出了 $f_a$，我们要计算 $f_b$。

假设有 $x$ 个叶子节点在 $a$ 那一侧，$y$ 个叶子节点在 $b$ 那一侧，那么就有 $f_b=f_a+val_b\cdot x-val_a\cdot y$。

这个很容易理解，当我们从 $a$ 移动到 $b$ 之后，$a$ 那一侧的叶子节点距离就都会增加 $val_b$，$b$ 那一侧的叶子节点距离就都会减少 $val_a$。

如何计算一条边两侧有多少个叶子节点呢？我们选择一个点作为根，并算出这个情况下每个点的子树中的叶子节点个数，这样用总叶子节点个数减去某一个子树的叶子节点个数就是这一条边另外一侧的叶子节点个数了。

另外为了避免各种细节情况，选择根的时候不要选度数为 $1$ 的点。由于 $n>2$，所以一定存在度数不为 $1$ 的点。

这样我们就只需要顺着进行换根 dp（走到一个点之后依次走他的所有儿子并修改当前的 $f$）即可。

统计答案也非常简单。记 $L$ 为整棵树的叶子个数，如果 $x$ 是叶子那么 $x$ 处的答案为 $\dfrac{f_x-val_x}{L-1}$，否则为 $\dfrac{f_x}{L}$。对每个节点的结果取 $\max$ 即可。

```cpp
int n;
ll a[500005];
vector<int>v[500005];
int l[500005],L;
double ans=-1e18;
ll cur;
void dfs1(int now,int fa,ll d){// 算出每个点子树的叶子节点个数以及最开始在根处的答案
	if(v[now].size()==1)l[now]=1,cur+=d;
	for(auto i:v[now])if(i^fa)dfs1(i,now,d+a[i]),l[now]+=l[i];
}
void dfs2(int now,int fa){// 换根 dp
	if(v[now].size()==1)ans=max(ans,(cur-a[now])*1.0/(L-1));
	else ans=max(ans,cur*1.0/L);
	for(auto i:v[now])if(i^fa){
		int y=l[i],x=L-y;
		cur=cur+a[i]*x-a[now]*y;// 移过去
		dfs2(i,now);
		cur=cur-a[i]*x+a[now]*y;// 移回来
	}
}

void __INIT__(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
void __SOLVE__(int _case){
	cin>>n;
	for(int i=1,x,y;i<n;i++)cin>>x>>y,v[x].push_back(y),v[y].push_back(x);
	for(int i=1;i<=n;i++)cin>>a[i];
	int st=1;
	while(v[st].size()==1)st++;// 找非叶子节点作为根
	dfs1(st,st,a[st]),L=l[st];
	dfs2(st,st);
	printf("%.4lf\n",ans);
}
```

---

## 作者：liugh_ (赞：1)

## [Promises I Can't Keep](https://www.luogu.com.cn/problem/P6554)

> 给定一 $n$ 个点的无根树，每个点有一个权值。对于一个根，等概率地从所有叶子节点中选一个，花费为根到这个点的路径上点权之和。现要选取一个点作为根，使得期望花费最大，求这个最大值。
>
> $n\le 5\cdot 10^5$。

考虑树形 dp。记 $lea_i$ 为 $i$ 子树内的叶子个数，$d_i$ 为 $i$ 的度数。对于一个根 $rt$ 以及一个点 $u$，经过点 $u$ 的路径共有 $lea_u$ 条，而总路径数为 $lea_{rt}$，所以在 $u$ 上获得的期望花费为 $\dfrac{val_u\cdot lea_u}{lea_{rt}}$。为了方便转移，我们设 $f(u)$ 为 $u$ 子树的期望花费乘上 $lea_{rt}$ 后的值，在统计答案时一并除以 $lea_{rt}$，这样能避免讨论精度问题。显然转移有
$$
f(u)=val_u\cdot lea_u+\sum_{v\in son_u} f(v)
$$
于是以 $rt$ 为根的答案为 $\dfrac{f(rt)}{lea_{rt}}$。至此，我们得到一个时间复杂度 $O(n^2)$ 的做法。瓶颈在于对于每一个根都要重新枚举整棵树计算答案，于是考虑是否能换根 dp。考虑对于边 $(u,v)$，由 $u$ 推得 $v$ 的答案。

先考虑 $lea$ 的变化。$u$ 少了 $v$ 这个儿子，注意若 $u$ 度数为 $1$，换根后 $u$ 会成为叶子；$v$ 多了 $u$ 这个儿子，注意若 $v$ 度数为 $1$，换根后 $v$ 不再是叶子。即
$$
lea_u'=lea_u-lea_v+[d_u=1]
$$
$$
lea_v'=lea_v+lea_u'-[d_v=1]
$$
接着考虑 $f$ 的变化，注意 $lea$ 变化后会对点上的期望造成影响，即 
$$
f'(u)=f(u)-f(v)-(lea_u-lea_u')val_u
$$
$$
f'(v)=f(v)+f'(u)+(lea_v'-lea_v)val_v
$$
统计答案，换根时对于每一个根 $rt$，令 $ans\gets \max\{ans,f(rt)\}$。时间复杂度 $O(n)$。

```cpp
#include<iostream>
#ifdef ONLINE_JUDGE
// #define getchar() (p_==q_&&(q_=(p_=b_)+fread(b_,1,s_,stdin),p_==q_)?-1:*p_++)
// #define putchar(x_) ((r_-o_<s_)?(*r_++=x_):(flush(),r_=o_,*r_++=x_))
#endif
#define inline inline __attribute__((__always_inline__))
#define flush() fwrite(o_,r_-o_,1,stdout),fflush(stdout)
using namespace std;constexpr int s_=1<<20;char b_[s_],o_[s_],*p_=b_,*q_=b_,*r_=o_;template<class T>inline bool fr(T&x_){x_=0;char c_=0,f_=0;do{if(c_=='-')f_=1;if((c_=getchar())==-1)return 0;}while(c_<48||c_>57);do {x_=x_*10+c_-48;if((c_=getchar())==-1)break;}while(c_>47&&c_<58);if(f_)x_=-x_;return 1;}template<class T>inline void fw(T x_){char d_[40],l_=-1;if(x_<0)x_=-x_,putchar('-');do d_[++l_]=x_%10+48;while(x_/=10);do putchar(d_[l_]);while(~--l_);}

#define int long long
constexpr int maxn=5e5+5;

struct _eg{int pre,v;}eg[maxn*2];int ei=1,eh[maxn];
inline void ea(int u,int v){eg[++ei]={eh[u],v};eh[u]=ei;}

int n,val[maxn];

int lea[maxn],d[maxn];
int f[maxn];
void dfs1(int u,int lst){
    bool islea=1;
    for(int e=eh[u];e;e=eg[e].pre){
        int v=eg[e].v;if(v==lst)continue;
        islea=0;
        dfs1(v,u);
        lea[u]+=lea[v];
        f[u]+=f[v];
    }
    if(islea)lea[u]++;
    f[u]+=val[u]*lea[u];
}

double ans=-1e18;
void dfs2(int u,int lst){
    ans=max(ans,1.0*f[u]/lea[u]);
    for(int e=eh[u];e;e=eg[e].pre){
        int v=eg[e].v;if(v==lst)continue;
        int fu=f[u],fv=f[v],lu=lea[u],lv=lea[v];
        
        f[u]-=val[u]*lea[u];
        lea[u]-=lea[v];
        if(d[u]==1)lea[u]++;
        f[u]+=val[u]*lea[u];
        f[u]-=f[v];

        f[v]-=val[v]*lea[v];
        lea[v]+=lea[u];
        if(d[v]==1)lea[v]--;
        f[v]+=val[v]*lea[v];
        f[v]+=f[u];

        dfs2(v,u);
        f[u]=fu,f[v]=fv,lea[u]=lu,lea[v]=lv;
    }
}

signed main(){
    // ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    // freopen("1.in","r",stdin);
    // freopen("1.out","w",stdout);
    
    fr(n);
    for(int i=2;i<=n;i++){
        int u,v;fr(u),fr(v);
        ea(u,v),ea(v,u);
        d[u]++,d[v]++;
    }
    for(int i=1;i<=n;i++)fr(val[i]);
    dfs1(1,0);
    dfs2(1,0);
    printf("%.04lf",ans);
    exit((flush(),0));
}
```

---

## 作者：破忆 (赞：1)

## 【题意】
路径长度定义为连接树上两点的链上的节点的权值和

某个点的期望得分是连接这个点到叶子节点的链的期望长度

求最大的期望得分
## 【分析】
把$x$的期望得分展开

从$x$出发到所有叶子节点的路径长度之和/以$x$为端点的路径数

路径长度和通过**换根DP**求，路径数直接统计

首先需要计算根节点的路径长度和

根节点不能选择叶节点

$g[x]$表示以$x$为根的子树中，$x$到所有叶节点的路径长度和

$siz[x]$表示以$x$为根的子树中，叶节点的数量

$a[x]$表示

* $x$是叶子

	$g[x]=a[x]$
   
   便于之后转移
* $x$不是叶子
	
   $g[x]=siz[x]*a[x]+\sum_{y|son[x]}{g[y]}$
   
   表示所有子树的路径长度和都增加了$a[x]$
   
于是得到了$g[rt]$，即根节点的路径长度和

接下来往下转移

$f[x]$表示在整棵树中，$x$到到所有叶子节点的路径长度和

* $x$是根

	$f[x]=g[x]$
* $x$是叶子

   从$fa$转移到$x$，有$siz[rt]-1$条路径长度会增加$a[x]$，并且会失去一条从$fa$到$x$的路径，长度是$a[x]+a[fa]$

	$f[x]=f[fa]+(siz[rt]-1)* a[x]-a[fa]-a[x]=f[x]+(siz[rt]-2)* a[x]-a[fa]$

* $x$不是根也不是叶子

	从$fa$转移到$x$，有$siz[rt]-siz[x]$条路径长度会增加$a[x]$，有$siz[x]$条路径长度会减少$a[fa]$
    
   $f[x]=f[fa]+(siz[rt]-siz[x])* a[x]-siz[x]* a[fa]$

至此，此题便解完了
## 【算法】
换根DP
## 【坑点】
* 权值有负数，答案初始应设置为极小值

* $5* 10^5* 10^4=5*10^9$，不能完全用int

* 只有一个点不能成为路径，统计答案时应避开

## 【代码】
```cpp
#include<bits/stdc++.h>
#define DB double
using namespace std;
const int maxn=5e5+5,maxe=maxn<<1;
const DB INF=1e15;
int n;
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int tot,lnk[maxn],du[maxn];
struct edge{
	int to,nxt;
}e[maxe];
DB g[maxn],f[maxn],a[maxn],siz[maxn];
bool lef[maxn];
void add_e(int x,int y){
	e[++tot]=(edge){y,lnk[x]};
	lnk[x]=tot;
	du[x]++;
}
int rt;
void DFS1(int x,int fa){
	int son=0;
	for(int j=lnk[x];j;j=e[j].nxt){
		int y=e[j].to;
		if(y==fa) continue;
		DFS1(y,x);
		g[x]+=g[y];
		siz[x]+=siz[y];
		son++;
	}
	if(!son) siz[x]=1,lef[x]=1,g[x]=a[x];
	else g[x]+=siz[x]*a[x];
}
void DFS2(int x,int fa){
	for(int j=lnk[x];j;j=e[j].nxt){
		int y=e[j].to;
		if(y==fa) continue;
		if(!lef[y]) f[y]=f[x]+(siz[rt]-siz[y])*a[y]-siz[y]*a[x];
		else f[y]=f[x]+(siz[rt]-2)*a[y]-a[x];
		DFS2(y,x);
	}
}
DB ans=-INF;
int main(){
	freopen("P6554.in","r",stdin);
	freopen("P6554.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		add_e(x,y),add_e(y,x);
	}
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) if(du[i]>=2){rt=i;break;}
	DFS1(rt,0);
	f[rt]=g[rt];
	DFS2(rt,0);
	for(int i=1;i<=n;i++) ans=max(ans,f[i]/(siz[rt]-lef[i]));
	printf("%.4lf\n",ans);
	return 0;
}
```


---

## 作者：DDF_ (赞：0)

~~可以写题解了，好耶！~~

## 题面

给定一棵无根树，以任意一点为根，求由根到各个叶子节点简单路径上权值和的算数平均数的最大值。

## 题解

一眼丁真，鉴定为树形 DP。

然后就可以开开心心设计状态了，先定义一个 $f_{x}$ 为以 $x$ 为根的子树中，到各个叶子节点简单路径上权值和的平均数。

可以想到 $f_{x}$ 的值与以 $x$ 为根子树中的叶子节点数量相关。

所以再定义一个 $g_{x}$ 为 $x$ 的子树中叶子节点的数量。

容易得到：
$$
g_{x} = \begin{cases}
1 & x \text{ is leaf}\\
\sum_{y = son_{x}} g_{y} & x \text{ is not leaf}
\end{cases}
$$

那么 $f_{x}$ 就是对所有的子节点的 $f$ 取个加权平均数，再加上自己的贡献：
$$
f_{x} = \frac{\sum_{y = son_{x}} f_{y} \times g_{y}}{g_{x}}+a_{x} 
$$

好的，现在处理的只是一般树形 DP 下的问题，接下来就的问题令人头疼了：要换根。

所以还需根据原先的 $f_{x}$ 和 $g_{x}$ 定义可以从父节点继承过来的 $F_{x}$ 和 $G_{x}$。

由于每一条路径都要连到根节点，所以如果只判断不在 $x$ 的子树中的节点，便还有一个根节点的答案没有算进去，导致计算答案的时候又要再加进去，产生多多少少的小细节与小问题，所以可以直接把不在子树中的其余节点连到 $x$ 上，然后把 $x$ 的答案算进去。

$F_{x}$ 和 $G_{x}$ 定义为：以 $x$ 为根，不在 $x$ 的子树中所有节点，加上 $x$ 节点的答案与其的叶子数量。

先想 $G_{x}$，可以想到 $G_{x}$ 肯定与 $G_{fa}$ 有关，因此先从其父节点的 $G_{fa}$ 继承下来，然后再加入父节点本身的贡献，因为 $x$ 为根肯定不能是叶子，所以答案也就是不在 $x$ 的子树中，在 $fa$ 的子树中的叶子数量，得到 $g_{fa}-g_{x}$。

所以 $G_{x}=G_{fa}+g_{fa}-g_{x}$。

$F_{x}$ 肯定也要从父节点继承，类似于 $f$ 的状态转移，可以想到先切断 $fa$ 与 $x$ 之间的边，从父节点的所有出边枚举计算平均数，然后再连回去计算。

然而这个转移并不用枚举，我直接把转移方程放在这里：
$$F_{x}=\frac{F_{fa}*G_{fa}+f_{fa}*g_{fa}-(f_{x}+a_{fa})*g_{x}}{G_{x}}+a_{x}$$

这个转移看似很复杂，其实就是上面一段话转变一下，首先已知从 $fa$ 到 $fa$ 的父节点的这条边的贡献为 $F_{fa}$，所以一条出边的贡献已经被统计了；其次，可以发现 $f_{fa}$ 存着所有子节点的贡献，因此只用在 $f_{fa}$ 中去除掉 $x$ 的贡献，在 $f_{u}$ 的方程中，可以看做每个子节点向其 $u$ 连边时，都贡献了自己的答案加上父节点的权值，所以可以得到 $f_{x}$ 对 $f_{fa}$ 的贡献为 $(f_{x}+a_{fa})*g_{x}$。

最后计算答案时只需要计算 $f_{x}$ 与 $F_{x}$ 的加权平均数，取最大值。

时间复杂度 $O(n)$。

**Details You Can Notice**

注意特判节点 $1$ 的度数为 $1$，也就是节点 $1$ 为叶子的情况。

注意统计答案时，除了节点 $1$ 以外的叶子节点不需要算加权平均数，因为它的贡献只有 $F_{x}$。

注意把答案初始化为负无穷，因为点权能取负值。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+2;
int n;
int head[N],to[2*N],nxt[2*N],d[N],idx;
double f[N],g[N],F[N],G[N],a[N],ans=-5e9;
void add(int x,int y) {
	nxt[++idx]=head[x],head[x]=idx,to[idx]=y,d[x]++;
	return;
}
void dfs1(int x,int fa) {
	if(d[x]==1&&x!=1) {f[x]=a[x],g[x]=1;return;}
	for(int i=head[x];i;i=nxt[i]) {
		int y=to[i];
		if(y!=fa) {
			dfs1(y,x);
			g[x]+=g[y];
			f[x]+=g[y]*f[y];
		}
	}
	f[x]=f[x]/g[x]+a[x];
	return;
}
void dfs2(int x,int fa) {
	if(d[fa]==1) {
		G[x]=1;
		F[x]=a[fa]+a[x];
	}
	else {
		G[x]=G[fa]+g[fa]-g[x];
		F[x]=(F[fa]*G[fa]+f[fa]*g[fa]-(f[x]+a[fa])*g[x])/G[x]+a[x];
	}
	for(int i=head[x];i;i=nxt[i]) {
		int y=to[i];
		if(y!=fa) {
			dfs2(y,x);
		}
	}
	return;
}
int main() {
	scanf("%d",&n);
	for(int i=1,x,y;i<n;i++) scanf("%d%d",&x,&y),add(x,y),add(y,x);
	for(int i=1;i<=n;i++) scanf("%lf",&a[i]);
	dfs1(1,0);
	for(int i=head[1];i;i=nxt[i]) dfs2(to[i],1);
//	for(int i=1;i<=n;i++) printf("%.4lf %.4lf %.4lf %.4lf\n",F[i],G[i],f[i],g[i]);
	for(int i=1;i<=n;i++) {
		if(d[i]==1&&i!=1) ans=max(ans,F[i]);
		else ans=max(ans,(f[i]*g[i]+F[i]*G[i])/(g[i]+G[i]));
	}
	printf("%.4lf",ans);
	return 0;
}
```
完结撒花。

---

## 作者：CQ_Bab (赞：0)

# 前言
~~一眼题~~。

提供一种与其他题解不同的方法。
# 思路
首先我们考虑 $n^2$ 做法，我们考虑每一哪一个点为根然后去树形 dp，我们定义 $f_i$ 表示所有方案的点权之和，$cnt_i$ 表示 $i$ 子树下的链的方案数，而转移也很简单 $cnt_{x}=\sum cnt_{son},f_x=\max(1,cnt_x)\times a_x+\sum f_{to}$ 这里之所以 $cnt_x$ 要与 $1$ 取最大值是因为叶子节点的贡献为 $a_x$，最后的答案就是 $\max(f_{rt}\div cnt_{rt})$。

然后我们考虑如何优化，我们考虑当根从 $x\to to$ 时有哪些点的值出现了改变我们发现有且仅有 $x,to$ 的值会改，我们考虑如何改变。

- 首先 $cnt_x$ 会减小 $cnt_{to}$ 然后我们要用 $cnt_x$ 与 $1$ 取最大值。
- 然后将 $cnt_{to}$ 的值加 $cnt_x$。
- 我们再考虑 $f_x$ 如何变化发现 $f_x$ 会减去 $f_{to}+cnt_{to}\times a_x$，这里需要特判如果 $cnt_{x}$ 为 $0$ 要将 $f_x$ 更新为 $a_x$。
- 最后我们考虑 $f_{to}$，其实和 $cnt_{to}$ 的变化差不多，首先加上 $f_{x}$ 然后再加上 $cnt_x\times a_x$，但是有一个问题就是如果这个点之前就是叶子节点要先将 $cnt_{to}$ 减 $1$ 再将 $f_{to}$ 减 $a_{to}$。

最后回溯即可。
# 代码
也是很好写的。
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define int long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
const int bufsize = 230005;
char buf[bufsize], *f1, *f2;
#define getchar() (f1 == f2 && (f2 = buf + fread(f1 = buf, 1, bufsize, stdin)) == buf? EOF: *f1++)
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
const int N=5e5+10;
vector<int>v[N];
int a[N],n;
int f[N],cnt[N];
double ans=-1e18;
void dfs(int x,int fa) {
	f[x]=false;
	cnt[x]=false;
	for(auto to:v[x]) {
		if(to==fa) continue;
		dfs(to,x);
		f[x]+=f[to];
		cnt[x]+=cnt[to];
	}
	cnt[x]=max(cnt[x],1ll);
	f[x]+=cnt[x]*a[x];
}
void dfs1(int x,int fa) {
	ans=max(ans,f[x]*1.0/cnt[x]);
	for(auto to:v[x]) {
		if(to==fa) continue;
		int lst=cnt[x],lst1=cnt[to];
		int Lst=f[x],Lst1=f[to];
		cnt[x]-=lst1;
		f[x]-=Lst1;
		f[x]-=cnt[to]*a[x];
		if(cnt[x]==0) f[x]=a[x];
		cnt[x]=max(1ll,cnt[x]);
		cnt[to]+=cnt[x]; 
		if(v[to].size()==1) cnt[to]--,f[to]-=a[to];
		f[to]+=f[x];
		f[to]+=max(1ll,cnt[x])*a[to];
		dfs1(to,x);
		cnt[x]=lst,cnt[to]=lst1;
		f[x]=Lst,Lst1=f[to];
	} 
}
void solve() {
	in(n);
	rep(i,1,n-1) {
		int x,y;
		in(x),in(y);
		v[x].pb(y);
		v[y].pb(x);
	}
	rep(i,1,n) in(a[i]);
	dfs(1,0);
	ans=f[1]*1.0/cnt[1];
	dfs1(1,0);
	printf("%.4lf",ans);
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：SamHJD (赞：0)

### Description

给出一棵带点权的树，找出树上的一个节点为根使得其到每个叶子的期望路径点权和最大。

### Solution

尝试换根，动态维护到每个叶子的路径点权和。

设 $u,v$ 两点，其中 $u$ 是 $v$ 的父亲，则根从 $u$ 变到 $v$ 时：

* $v$ 子树内的叶子的贡献都会减少 $a_u$（以 $1$ 为根下的子树）。

* $v$ 子树以外的叶子的贡献都会增加 $a_v$（以 $1$ 为根下的子树）。

预处理每个节点以 $1$ 为根时子树中的叶子个数即可。

注意若当前根的度数为 $1$，不将其视为一个叶子，需要将贡献和叶子个数减去后更新答案。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define rep(i,k,n) for(int i=k;i<=n;++i)
#define per(i,n,k) for(int i=n;i>=k;--i)
using namespace std;
template<typename T>
inline void read(T &x){
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(c-'0');
	x*=f;
}
const int N=5e5+10;
int n,siz[N],now,a[N],leaf[N];
vector<int> g[N];
void init(int u,int fa){
    siz[u]=1;
    for(auto v:g[u]){
        if(v==fa) continue;
        init(v,u);
        siz[u]+=siz[v];
    }
}
int get(int u,int fa){
    if(g[u].size()==1&&u!=1){now+=a[u];return leaf[u]=1;}
    for(auto v:g[u]){
        if(v==fa) continue;
        leaf[u]+=get(v,u);
    }
    now+=leaf[u]*a[u];
    return leaf[u];
}
double ans=-1000000000000000;
void dfs(int u,int fa){
    int f=(g[u].size()==1);
    double y=1.0;
    ans=max(ans,y*(now-f*a[u])/(leaf[1]-f));
    for(auto v:g[u]){
        if(v==fa) continue;
        int tmp=now;
        now+=(leaf[1]-leaf[v])*a[v];
        now-=leaf[v]*a[u];
        dfs(v,u);
        now=tmp;
    }
}
signed main(){
    read(n);
    rep(i,1,n-1){
        int u,v;read(u);read(v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    rep(i,1,n) read(a[i]);
    init(1,0);
    get(1,0);
    if(g[1].size()==1) now+=a[1],leaf[1]++;
    dfs(1,0);
    printf("%.4Lf",ans);
	return 0;
}
```

---

## 作者：operator_ (赞：0)

# P6554 Promises I Can't Keep

[题目传送门](https://www.luogu.com.cn/problem/P6554)

## 题解

看题解都有些做烦了，就来发一篇。

换根 dp。第一遍 dfs 处理出 $Lef_u$ 表示 $u$ 子树内的叶子个数（**包含自己**），然后求出以 $1$ 为根时的答案 $\sum Lef_u\times val_u$，注意特判根为叶子的情况。

第二遍 dfs 大力换根就好了，从根 $u$ 换到根 $v$ 时真正有变化的只有 $Lef_u$ 和 $Lef_v$，于是可以直接修改再回溯，同步更新**从根到所有叶子的权值和**，然后对于每一个根，答案就是好计算的。

代码：

```cpp
/*
 * @Author: operator_ 
 * @Date: 2023-11-23 08:55:31 
 * @Last Modified by: operator_
 * @Last Modified time: 2023-11-23 09:34:33
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int rd() {
    int s=0,m=0;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')m=1;ch=getchar();}
    while( isdigit(ch)) s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return m?-s:s;
}
int n,a[500005],d[500005],Lef[500005],Sl,f[500005],Sum;
double Ans=-1e12;
int h[500005],Cnt;
struct Graph {int u,v,Nxt;} e[1000005];
void Add(int u,int v) {e[++Cnt]={u,v,h[u]},h[u]=Cnt;}
void Dfs1(int u,int p) {
    if(d[u]==1) Lef[u]=1;
    for(int i=h[u];i;i=e[i].Nxt) {
        int v=e[i].v;
        if(v==p) continue;
        Dfs1(v,u);
        Lef[u]+=Lef[v];
    }
    Sum+=Lef[u]*a[u];
}
void Dfs2(int u,int p) {
    if(d[u]==1) Ans=max(Ans,(Sum-a[u])*1.0/(Sl-1));
    else Ans=max(Ans,Sum*1.0/Sl);
    for(int i=h[u];i;i=e[i].Nxt) {
        int v=e[i].v;
        if(v==p) continue;
        Sum-=Lef[u]*a[u]+Lef[v]*a[v];
        Lef[u]=Sl-Lef[v];
        Lef[v]=Sl;
        Sum+=Lef[u]*a[u]+Lef[v]*a[v];
        Dfs2(v,u);
        Sum-=Lef[u]*a[u]+Lef[v]*a[v];
        Lef[v]=Sl-Lef[u];
        Lef[u]=Sl;
        Sum+=Lef[u]*a[u]+Lef[v]*a[v];
    }
}
signed main(){
    cin>>n;
    for(int i=1;i<n;i++) {
        int u=rd(),v=rd();
        Add(u,v),Add(v,u);
        d[u]++,d[v]++;
    }
    for(int i=1;i<=n;i++)
        a[i]=rd();
    Dfs1(1,0);
    Sl=Lef[1];
    Dfs2(1,0);
    printf("%.4lf",Ans);
    return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

**十年 OI 一场空，瞎读题意见祖宗。**

如果是等概率流向儿子的，请回去重新做！！！

剩余的电流会**等概率**且不重复经过一个点地**流向叶子节点**。

~~我就是这样，样例过了，死活 WA。~~

树形 dp 加上换根，应该很好想到。

树形 dp 地第一遍 dfs 显然很简单，就是统计出以 $1$ 为根，一个节点地子树有多少个叶子节点，这些叶子节流流过来时多少？

```cpp
//f[x]:叶子节点流向该节点的值
//sz[x]:有多少叶子节点
inline void dfs(int x, int ff){
	for(int i = fir[x]; i ; i = nxt[i]){
		if(son[i] == ff) continue ;
		dfs(son[i], x);
		deg[x]++;
		f[x] += f[son[i]];
		sz[x] += sz[son[i]];
	}
	if(deg[x] == 0) sz[x] = 1;
	f[x] += val[x] * sz[x];
}
```

好，然后我们开始换根。

注：在下文中，都是从 $x$ 换到 $y$。

记 $ans$ 为答案，$tot$ 为叶子节点到该点的距离，$sz_{leaves}$ 表示叶子节点的数量。

换根之后 $ans=\dfrac{tot}{sz_{leaves}}$。

什么节点是叶子节点？

只和 $fa$ 有一条边。

那我们发现，之和 $fa$ 有一条边的就是我们处理出来的 $sz_1$，不过需要注意一点（特别是链的情况），**$1$ 也可能是叶子节点**（其他点作为根的时候），我们下文再说。

其他情况下，叶子节点的个数就是 $sz_1$，不过注意，当此时的节点 $x$ 是根节点的时候它同时是 $1$ 为根时的叶子节点，**那一定要特判**。

对于有至少两条边连接的点，最多一进（或者自己为根），必然可以出去，**所以不可能是叶子节点**。

换根的时候我统计出叶子节点总共距离该节点多少（记为 $tot$）。

- $y$ 不是叶子节点

![](https://cdn.luogu.com.cn/upload/image_hosting/37hsbcf0.png)

我们发现，$x$ 的非 $y$ 节点需要多走到 $y$，$y$ 的节点不需要走到 $x$。就是说，$tot$ 的总值会减少一个 $val_x \times sz_y$，而会加上一个 $val_y \times (sz_x-sz_y)$。写成代码就是：

```cpp
tot - sz[son[i]] * val[x] + (sz[1] - sz[son[i]]) * val[son[i]]
```
- $y$ 是叶子节点

此时，我们发现，因为 $y$ 到自己还算了一个 $val_y$，但是我们计算的时候显然根节点不会被当成叶子节点，所以在上面的基础上减掉 $val_y$ 即可。

```cpp
tot - sz[son[i]] * val[x] + (sz[1] - sz[son[i]]) * val[son[i]] - val[son[i]]
```
这同时也告诉我们，在开始更新 $ans$ 的时候，不要忘记总共的叶子节点的个数不再是 $sz_1$，而是 $sz_1-1$。

- 一个节点是出度为 $1$ 的 $1$ 号点。

这个分类不要忘记。而且判断的时候注意写上，因为对于这一种情况，再其他的节点时，**叶子节点还会有一个 $1$。**

![](https://cdn.luogu.com.cn/upload/image_hosting/4mq5q1hf.png)

原来是方框里的东西到 $y$ 再到 $1$，现在是方框里的东西到 $y$，$1$ 到 $y$。相比较原来而言，加了两次，所以我们就可以写出代码：

```cpp
//deg[x]是儿子的数量
if(x == 1 && deg[x] == 1) dfs2(son[i], x, tot + val[son[i]]);
```

最后提醒大家一点，就是当 $deg_1$ 等于 $1$ 的时候，我们把 $sz_1$ 加上 $1$，这样可以减少计算时的特判。

完整代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 5;
double inf = 10000000000000000000.00;
int n, fir[N << 1], nxt[N << 1], son[N << 1], tot, val[N], u, v, deg[N], sz[N];
int f[N], g[N];
double ans = -inf;
double dmax(double x, double y){return x > y ? x : y;}
inline void add(int x, int y){
	nxt[++tot] = fir[x];
	fir[x] = tot;
	son[tot] = y; 
} 
inline void dfs(int x, int ff){
	for(int i = fir[x]; i ; i = nxt[i]){
		if(son[i] == ff) continue ;
		dfs(son[i], x);
		deg[x]++;
		f[x] += f[son[i]];
		sz[x] += sz[son[i]];
	}
	if(deg[x] == 0) sz[x] = 1;
	f[x] += val[x] * sz[x];
}
inline void dfs2(int x, int ff, int tot){
	if(deg[x] && (x != 1 || deg[1] != 1)) ans = dmax(ans, tot * 1.0 / sz[1]);//如果这个点不是叶子节点，那就有sz[1]个叶子
	else ans = dmax(ans, tot * 1.0 / (sz[1] - 1));//如果是叶子节点，就有sz[1]-1个叶子
	for(int i = fir[x]; i ; i = nxt[i]){
		if(son[i] == ff) continue;
		if(x == 1 && deg[x] == 1) dfs2(son[i], x, tot + val[son[i]]);
		else if(deg[son[i]]) dfs2(son[i], x, tot - sz[son[i]] * val[x] + (sz[1] - sz[son[i]]) * val[son[i]]);
		else dfs2(son[i], x, tot - sz[son[i]] * val[x] + (sz[1] - sz[son[i]]) * val[son[i]] - val[son[i]]);
	}
}
signed main(){
	scanf("%lld", &n);
	for(int i = 1; i < n; i++){
		scanf("%lld%lld", &u, &v);
		add(u, v), add(v, u);
	}
	for(int i = 1; i <= n; i++) scanf("%lld", &val[i]);
	dfs(1, 0);
	if(deg[1] == 1) sz[1]++;//对1作为叶子的特判
	dfs2(1, 0, f[1]);
	printf("%.6lf", ans);
	return 0;
}
```

---

## 作者：stupid_collie (赞：0)

**为了这一题，我专门去学了期望 DP（~~结果发现这题的期望根本就是拿来唬人的~~）。**

题目描述说，求出所有路径的期望，其实就是求出当以某一个点为根节点的时候，它到每一个叶子节点的距离除以其叶子节点的数量。

那么我们不难考虑到换根 DP，第一次 DFS，我们先从编号为 $1$ 的节点开始扫描，并且记录每一个节点到 **其子树上** 的每一个叶子节点的距离之和及其子树中叶子节点的数量。

```cpp
void init(int u,int fa){
  for(int i = 0;i<g[u].size();i++){
    int v = g[u][i];
    if(v==fa)continue;

    init(v,u);
    len[u] += val[u]*cnt[v] + len[v];//记录该节点出发所有路径距离之和
    cnt[u] += cnt[v];//记录该节点出发的路径数量
  }

  //如果该点是子节点，就将其标记，设置初始数量为1，路径长度为val[u]
  if(g[u].size()==1&&u!=1)cnt[u] = ed[u] = 1,len[u] = val[u];
}
```

然后，在我们第二次 DFS 的时候，我们就可以开始记录当以每一个子节点为根的时候，其路径数和路径长度总和分别是多少了。

这里要注意一件事情：如果我们有两个点 $i$ 和 $j$，而其中 $i$ 是一个度数为 $1$ 的点，那么，当根节点由 $i$ 转移到 $j$ 的时候，$i$ 节点将会成为一个新的叶子节点，反之，如果 $j$ 本身是一个叶子节点，转移之后它将不再作为一个叶子节点存在。

由转移过后，我们的新根节的叶子节点数其实就是我们原本根节点的叶子节点数加上 **上述特判** ，于是我们有转移方程：

$cnt_v=cnt_u+ed_u-ed_v$

*（ed 表示该点的度数是否为 $1$，即是否有可能成为叶子节点）。*

类似的，长度的转移方程也是类似的思路。原本再该节点子树以外的叶子路径都会分别多经过这个节点一次，于是乎就有转移方程：

$len_v=val_v*(cnt_u-cnt_v+ed_u-ed_v)+len_u$

特别的，当两个节点的叶子节点数量相同的时候，我们可以直接继承：

$len_v=val_v*(cnt_u-cnt_v+ed_u-ed_v)+len_u-cnt_v*val_u (cnt_u=cnt_v)$

于是乎就有了第二次 DFS 的函数：

```cpp
void dfs(int u,int fa){
  for(int i = 0;i<g[u].size();i++){
    int v = g[u][i];
    if(v==fa)continue;
    if(cnt[u]==cnt[v])len[v] = val[v]*(cnt[u]-cnt[v] + ed[u] - ed[v]) + len[u];
    else len[v] = val[v]*(cnt[u]-cnt[v] + ed[u] - ed[v]) + len[u] - cnt[v]*val[u];
    dfs(v,u);
  }
}
```

完整代码如下：

```cpp
#include<bits/stdc++.h>
const int maxn = 5e5 + 9;
#define int long long
using namespace std;

int read(){
  int x=0,f=1;
  char ch = getchar();
  while(ch<'0'||ch>'9'){if(ch=='-')f = -f;ch = getchar();}
  while(ch>='0'&&ch<='9'){x = (x<<3)+(x<<1)+(ch^48);ch = getchar();}
  return x*f;
}

vector<int> g[maxn];
int val[maxn],n,len[maxn],cnt[maxn],ed[maxn];

long double ans;

void init(int u,int fa){
  for(int i = 0;i<g[u].size();i++){
    int v = g[u][i];
    if(v==fa)continue;

    init(v,u);
    len[u] += val[u]*cnt[v] + len[v];
    cnt[u] += cnt[v];
  }

  if(g[u].size()==1&&u!=1)cnt[u] = ed[u] = 1,len[u] = val[u];
}

void dfs(int u,int fa){
  for(int i = 0;i<g[u].size();i++){
    int v = g[u][i];
    if(v==fa)continue;

    if(cnt[u]==cnt[v])len[v] = val[v]*(cnt[u]-cnt[v] + ed[u] - ed[v]) + len[u];
    else len[v] = val[v]*(cnt[u]-cnt[v] + ed[u] - ed[v]) + len[u] - cnt[v]*val[u];

    cnt[v] = cnt[u] + ed[u] - ed[v];
    dfs(v,u);
  }
}

signed main(){
  n = read();
  for(int i = 1,u,v;i<n;i++){
    u = read(),v = read();
    g[u].push_back(v),g[v].push_back(u);
  }

  for(int i = 1;i<=n;i++)val[i] = read();
  init(1,1);
  if(g[1].size()==1)ed[1] = 1;
  dfs(1,1);

  ans = -1e32;
  for(int i = 1;i<=n;i++)
    ans = max(ans,(long double)1.0*len[i]/(1.0*cnt[i]));
  printf("%.4Lf",ans);
}

```

---

## 作者：王江睿 (赞：0)

提交理由：自信不会有第二个自底向上搜的。

思路：   
1. 用堆找到度为 1 的点，并将其的权值上传（沿着唯一邻边）；删除该点，并修改其父节点的度数。父节点存贮期望和子树「叶子节点」数的积。
2. 堆为空时，跳出循环。沿删除序的倒序（发现顺序）重新下载值至子节点，并传递值至子节点。通过计算，子节点获得期望和另一方面子树的「叶子节点」的积。
3. 通过将二子树的「叶子节点」和期望的积除以总「叶子节点」数，计算每个节点的期望。更加之以该节点的权值，取最大值即可。


```cpp
#include <bits/extc++.h>
using namespace std;
constexpr int32_t MAXN = 500032;
basic_string<int32_t> E[MAXN];
__gnu_pbds::priority_queue<pair<int32_t, int32_t>, greater<pair<int32_t, int32_t>>> V;
decltype(V)::point_const_iterator H[MAXN];
bitset<MAXN> instk;
basic_string<int32_t> ef;
long double b[MAXN], c[MAXN], d[MAXN], g[MAXN], w[MAXN];
int main()
{
	// ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int32_t a, o, p, q;
	cin >> q;
	for (int32_t i = 1; i < q; ++i) {
		cin >> o >> p;
		E[o].push_back(p);
		E[p].push_back(o);
	}
	for (int32_t i = 1; i <= q; ++i) {
		cin >> w[i];
		H[i] = V.push({ E[i].size(), i });
		if (E[i].size() == 1)
			++a, b[i] = 1;
	}
	int32_t r, u;
	long double t;
	while (!V.empty()) {
		r = V.top().second;
		V.pop();
		u = t = 0;
		instk.set(r);
		for (const auto& s : E[r]) {
			if (instk[s])
				t += d[s], b[r] += b[s];
			else {
				u = s;
				V.modify(H[s], { H[s]->first - 1, H[s]->second });
			}
		}
		if (u) {
			d[r] = w[r] * b[r] + t;
			g[r] = u;
		} else
			g[r] = r;
		ef.push_back(r);
	}
	for (decltype(ef)::const_iterator i = ef.end(); t = 0, i != ef.begin();) {
		for (const auto& s : E[*--i])
			if (s != g[*i])
				c[*i] += d[s];
		for (const auto& s : E[*i])
			if (s != g[*i])
				c[s] = w[*i] * (a - b[s]) + c[*i] - d[s];
	}
	for (int32_t i = 1; i <= q; ++i)
		c[i] = w[i] + c[i] / (a - (E[i].size() == 1));
	printf("%.4Lf", *max_element(c + 1, c + q + 1));
	return 0;
}
```


---

## 作者：Purslane (赞：0)

## Solution

最近水平下降 , 发题解 .

首先 , 题面可能有一点歧义 : 它实际上就是想让你求出每个点为根时到所有叶子节点路径和的和 .

首先如果让你求每个点到它原树上的子树中的叶子结点 , 直接树形 dp .

$$dp_u=val_u \times sum_u + \sum dp_v$$

其中 $sum_u$ 是 $u$ 的子树内叶子结点的个数 .

但是可能考虑子树外的 , 这时候就考虑换根 .

画个图就知道 , 当根从 $u$ 换成 $v$ 的时候 , 有 $sum_v$ 个点的路径和 $-val_u$ , 有 $tot-sum_v$ ( $tot$ 是度数为 $1$ 的节点总数 ) 个点的路径和 $+val_v$ . 就可以写出换根的 dp 方程 .

每次比较 $\frac{ans_u}{tot}$ 的值就可以了 .

如果 $u$ 的度数是 $1$ , 那么 $u$ 自己不能被算进去 , 还要单独处理 .

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e5+10;
int n,tot,val[MAXN],sum[MAXN],ans[MAXN]; vector<int> G[MAXN];
int dfs(int u,int f) {
	if(G[u].size()==1) sum[u]++;
	int ans=(G[u].size()==1)*val[u],cnt=0;
	for(auto v:G[u]) {
		if(v==f) continue;
		ans+=dfs(v,u);
		ans+=sum[v]*val[u];
		sum[u]+=sum[v];
	}
	return ans;
}
void calc(int u,int f) {
	if(f) {
		ans[u]=ans[f]-val[f]*sum[u]+(tot-sum[u])*val[u];
	}
	for(auto v:G[u]) {
		if(v==f) continue;
		calc(v,u);	
	}
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n-1) {
		int u,v; cin>>u>>v;
		G[u].push_back(v),G[v].push_back(u);
	}
	ffor(i,1,n) cin>>val[i];
	ffor(i,1,n) if(G[i].size()==1) tot++;
	ans[1]=dfs(1,0);
	calc(1,0);
	double Ans=-99824435311451419;
	ffor(i,1,n) {
		int sum=tot;
		if(G[i].size()==1) ans[i]-=val[i],sum--;
		Ans=max(Ans,ans[i]*1.0/sum);	
	}
	cout<<fixed<<setprecision(6)<<Ans;
	return 0;
}
```

---

