# Centroids

## 题目描述

**树** 是一种连通的**无环图**。假设给定一棵由 $n$ 个顶点组成的树。如果移除该顶点后，树中每个连通分量的大小均不超过 $\frac{n}{2}$，则该顶点被称为**重心**。

给定一棵大小为 $n$ 的树，你可以执行**最多一次**边的替换操作。边的替换操作指的是从树中移除一条边（不删除相邻顶点）并插入一条新边（不添加新顶点），使得图仍保持为一棵树。对于每个顶点，你需要判断是否可以通过执行最多一次边的替换操作使其成为重心。


## 说明/提示

在第一个样例中，每个顶点都可以成为重心。例如，为了将顶点 $1$ 变为重心，需要将边 $(2,3)$ 替换为边 $(1,3)$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
1 2
2 3
```

### 输出

```
1 1 1 
```

## 样例 #2

### 输入

```
5
1 2
1 3
1 4
1 5
```

### 输出

```
1 0 0 0 0 
```

# 题解

## 作者：LeavingZzz (赞：68)

# $\mathsf{Solution\space For\space CF708C}$  
Upd:非常非常不好意思，这个屑贴错了代码，现在已经更新  
~~被这个问题困扰到的欢迎私信D死这个屑~~ 


------------

$\mathcal{By\space ShadderLeave}$  
提供一种思想上和其他题解不一样（也许会更容易理解？）的解法  


------------
## $\mathsf{Description}$  
给出一棵树，你可以选择断掉其中的一条边将其重新连接到任意一个节点上，使其形成一棵新树，请问有多少个节点可以通过这种操作成为树的重心？  
输出一行 $N$ 个数，第 $i$ 个数字是 $0/1$ 表示第 $i$ 个节点 可以/不可以 成为重心  
$0\le N\le 4\times 10^5$  
## $\mathsf{Analysis}$  
重心给出的定义是所有的子树大小都小于等于 $\lfloor \dfrac{N}{2}\rfloor$ 的节点，所以说，如果一个节点不是重心，就表示这个节点有一个子树的大小超出了 $\lfloor \dfrac{N}{2}\rfloor$（而且只有一个），我们只需要在这个超出了 $\lfloor\dfrac{N}{2}\rfloor$ 的子树中挑选一个更小子树断掉他然后连到当前节点上来。  

问题是，这个大小超出 $\lfloor \dfrac{N}{2}\rfloor$ 的子树中有没有这种断掉之后可以使得其大小减小到 $\lfloor \dfrac{N}{2}\rfloor$ 以下的这种小子树呢？  

而且这是一棵无根树，形态确定不了，现在所叙述的 “子树” 可能是其父亲节点，一切都似乎变得很麻烦....  

但是现在如果我们事先就先找到一个重心作为根，似乎就会有一些美妙的性质。  

如果一个节点 $u$ 不是重心，那么一定是其父节点所在的大小为 $N-sz[u]$ 的子树超出了限制（因为以重心为根的时候所有子树的大小都不会超过 $\lfloor \dfrac{N}{2}\rfloor$，继续向下走的时候深度更深的子树大小只会更小，所以问题一定出在父节点处）  

这就启发我们记录一个信息：对于一个节点 $u$，记录一个除了子树 $u$ 以外的、大小最大但是不超出 $\lfloor \dfrac{N}{2}\rfloor$ 的子树大小，设为 $cut[u]$，因为问题一定是出在非子树 $u$ 的部分，所以当一个节点不是重心的时候我们只需要判断 $N-sz[u]-cut[u]\le\lfloor\dfrac{N}{2}\rfloor$ 是否成立即可   

简化完一圈，就是要求所有节点除了本身以外的部分中不超出 $\lfloor\dfrac{N}{2}\rfloor$ 的最大子树大小，这就是一个换根DP问题了。  

设 $Max[u]$ 为子树 $u$ 中的不超出限制的最大子树大小，在进行dfs的时候我们带一个参数，即节点 $u$ 的祖先中的最大的不超出限制的子树大小，设为 $maxx$，那么有：  
$$maxx=max(maxx,N-sz[u])\space \mathsf{if}(N-sz[u]\le\lfloor\dfrac{N}{2}\rfloor)$$  
同时 $cut$ 的转移写成
$$cut[v]=max(maxx,Max[u])\space v\in son[u]$$  
如果你这么写的话那你就太naive了（一转攻势  

因为很明显 $Max[u]$ 很有可能就是子树 $v$ 的大小，这时候应该选取子树 $u$ 中的次大值，所以要同时记录最大和次大，分别为 $Max[u][0/1]$  
$$cut[v]=max(maxx,Max[u][0])\space \mathsf{if}(sz[v]\ne Max[u][0])$$
$$cut[v]=max(maxx,Max[u][1])\space \mathsf{if}(sz[v]==Max[u][0])$$

还有啥细节就看代码吧qaq  
## $\mathsf{Code}$  
```
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=400007;
int N;
struct E{
	int u,v;
}e[maxn<<1];
int first[maxn],nt[maxn<<1],ES;
inline void addE(int u,int v)
{
	e[++ES]=(E){u,v};
	nt[ES]=first[u];
	first[u]=ES;
	return ;
}
inline int R()
{
	char c;
	int re;
	while((c=getchar())>'9'||c<'0');
	re=c-48;
	while((c=getchar())>='0'&&c<='9')
	re=re*10+c-48;
	return re;
}
int fa[maxn],sz[maxn];
int rt;//rt是找到的重心 
void dfs1(int u)
{
	int v;
	sz[u]=1;
	bool f=true;
	for(int i=first[u];i;i=nt[i])
	{
		v=e[i].v;
		if(v==fa[u]) continue;
		fa[v]=u;
		dfs1(v);
		sz[u]+=sz[v];
		if(sz[v]>N/2) f=false;
	}
	if(N-sz[u]>N/2) f=false;
	if(f) rt=u;
	return ;
}
int Max[maxn][2];//子树u中size最大的/次大的子树大小
void dfs2(int u)
{
	int v;
	sz[u]=1;
	for(int i=first[u];i;i=nt[i])
	{
		v=e[i].v;
		if(v==fa[u]) continue;
		fa[v]=u;
		dfs2(v);
		sz[u]+=sz[v];
		if(sz[v]>N/2) continue;//排除掉大于N/2的
		if(sz[v]>Max[u][0]) Max[u][1]=Max[u][0],Max[u][0]=sz[v];
		else if(sz[v]>Max[u][1]) Max[u][1]=sz[v];
	}
	return ;
}
int cut[maxn];
bool ans[maxn];
void dfs3(int u,int maxx)
{
	int v;
	cut[u]=maxx;
	for(int i=first[u];i;i=nt[i])
	{
		v=e[i].v;
		if(v==fa[u]) continue;
		if(N-sz[u]<=N/2) maxx=max(maxx,N-sz[u]);//也许父亲的部分能直接构成子树 
		if(Max[u][0]==sz[v]) dfs3(v,max(maxx,Max[u][1]));//如果v即为最大的子树那么要用次大值
		else dfs3(v,max(maxx,Max[u][0]));
	}
	if(N-sz[u]-cut[u]<=N/2||u==rt) ans[u]=true;
	return ;
}
int main()
{
	N=R();
	int u,v;
	for(int i=1;i<N;i++)
	{
		u=R();v=R();
		addE(u,v);
		addE(v,u);
	}
	dfs1(1);
	fa[rt]=0;//注意清空fa 
	dfs2(rt);
	dfs3(rt,0);
	for(int i=1;i<=N;i++)
	if(ans[i]) putchar('1'),putchar(32);
	else putchar('0'),putchar(32);
	return 0;
}
```  
$\huge \mathcal{The\space End}$  
谢谢管理大大审核^_^

---

## 作者：Polaris_Dane (赞：57)

做题的时候随手hack了两篇题解

所以我来补个题解（大雾

要让每个子树大小都小于等于$\left\lfloor\dfrac {n} {2}\right\rfloor$

如果这个子树本身就可以作为重心，就不用改变

考虑如果本身不能作为重心，说明一定有且只有一个子树大小大于$\left\lfloor\dfrac {n} {2}\right\rfloor$

我们一定是从这个子树里面选一个子树接在当前的根上面，否则不是最优的

那么就要从该子树里面找到一个小于等于$\left\lfloor\dfrac {n} {2}\right\rfloor$的最大子树

然后就可以进行判断了

考虑如何快速求出这个值

看上去就很像一个换根DP

先考虑$dp[u]$为$u$子树内该值的大小

对于一个点$v\in son_u$

$dp[u]=\begin{cases}\max(siz[v])&siz[v]<=\left\lfloor\dfrac {n} {2}\right\rfloor\\\max(dp[v])&\text{otherwise}\end{cases}$

考虑换根，那我们要得到子树外能移除最大子树的大小

考虑$dp'[v]$如何得到

考虑$dp[u]$的最佳转移点，如果$dp[u]$最佳转移点就是$v$，那么我们就需要得到一个点第二大的能够去除的子树大小

所以必须考虑维护两个个$dp$值，$dp[u][0]$表示第一大的值，$dp[u][1]$表示第二大的值

然后如果$v$是$u$最佳转移点

那么$dp'[v]$可取值为$dp[u][1]$和$n-siz[u](n-size[u]<=\left\lfloor\dfrac {n} {2}\right\rfloor)$

否则可取值为$dp[u][0]$和$n-siz[u](n-size[u]<=\left\lfloor\dfrac {n} {2}\right\rfloor)$

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<set>
#include<queue>
#define M 1000100
#define inf 0x3f3f3f3f
#define LL long long
const int mod=988244353;
using namespace std;
inline int read(){
	int f=1,x=0;char s=getchar();
	while (!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while (isdigit(s)){x=(x<<1)+(x<<3)+(s^48),s=getchar();}
	return x*f;
}
int t,n,head[M],cnt,dp[M][2],pos[M],dpp[M],ans[M],siz[M],maxsiz[M];
struct edge{int to,nxt;}e[M<<1];
inline void add_edge(int u,int v){e[++cnt].nxt=head[u],head[u]=cnt,e[cnt].to=v;} 
inline void dfs(int rt,int fa){
	siz[rt]=1;
	for (int i=head[rt];i;i=e[i].nxt){
		if (e[i].to==fa) continue;
		dfs(e[i].to,rt);int v;
		siz[rt]+=siz[e[i].to];
		if (siz[e[i].to]>siz[maxsiz[rt]]) maxsiz[rt]=e[i].to;
		if (siz[e[i].to]<=n/2) v=siz[e[i].to];
		else v=dp[e[i].to][0];
		if (dp[rt][0]<v) dp[rt][1]=dp[rt][0],dp[rt][0]=v,pos[rt]=e[i].to;
		else if (dp[rt][1]<v) dp[rt][1]=v;
	}
}
inline void redfs(int rt,int fa){
	ans[rt]=1;
	if (siz[maxsiz[rt]]>n/2) ans[rt]=(siz[maxsiz[rt]]-dp[maxsiz[rt]][0]<=n/2);
	else if (n-siz[rt]>n/2) ans[rt]=(n-siz[rt]-dpp[rt]<=n/2);
	for (int i=head[rt];i;i=e[i].nxt){
		if (e[i].to==fa) continue;int v;
		if (n-siz[rt]>n/2) v=dpp[rt];
		else v=n-siz[rt];
		dpp[e[i].to]=max(dpp[e[i].to],v);
		if (pos[rt]==e[i].to) dpp[e[i].to]=max(dpp[e[i].to],dp[rt][1]);
		else dpp[e[i].to]=max(dpp[e[i].to],dp[rt][0]);
		redfs(e[i].to,rt);
	}
}
signed main(void){
	n=read();
	for (int i=1;i<=n-1;i++){
		int u=read(),v=read();
		add_edge(u,v),add_edge(v,u);
	}
	dfs(1,0),redfs(1,0);
	for (int i=1;i<=n;i++) printf("%d ",ans[i]);
	return 0;
}

```


---

## 作者：szwyue012 (赞：38)

看到转化为重心，首先可以从重心的性质想到可以通过改造变为重心的条件。

对于一个节点 $x$ ，如果本身就是重心，就无需改造，否则就必然有且只有一个儿子的子树大于 n/2 。

如果可以从这个儿子的子树中拿出一个子树接到节点 $x$ 上，使得接上的子树大小不超过 n/2 且剩下的子树大小也不超过 n/2 ，那么节点 $x$ 就是可以改造为重心的。

一个节点作为根节点时，儿子有目前的儿子以及从父亲上去的儿子。

那么可以维护对于节点 $x$ ，从子树中可以找到的最大且不超过 n/2 的子树大小以及整棵树去除以节点 $x$ 为根的子树剩下的树里可以找到的最大且不超过 n/2 的子树大小。

第一个很好维护，如果整棵子树大小不大于 n/2 ，那么就选整棵子树，不然在儿子中找最大的。

第二个类似，如果剩下的树大小不大于 n/2 ，那么就选剩下的树的全部，不然就要在父亲向上的树的最大值和父亲的剩余儿子里的向下的最大值中选最大的。

如果设第一种是 $dp1$ ，第二种是 $dp2$ 那么有

$dp1_x=\begin{cases}sz_x&sz_x\le n/2\\max_{y\in son(x)}\{ dp1_y\}&otherwise\end{cases}$ 

$dp2_x=\begin{cases}n-sz_x&n-sz_x\le n/2\\max(dp2_{fa(x)},max_{y\in son(fa(x))\& y\neq x}\{ dp1_y\})&otherwise\end{cases}$

最后对于节点 $x$ ，找到以 $x$ 为根时有最大子树大小的儿子，减去相应的 dp 值看是否小于 n/2 就可以判断了。 

```cpp
#include<bits/stdc++.h>
using namespace std;

const int M=4e5+5;

int max(int x,int y){ return x>y?x:y; }
int min(int x,int y){ return x<y?x:y; }

int n;
int read(){
	int x=0,y=1;char ch=getchar();
	while(ch<'0'||ch>'9') y=(ch=='-')?-1:1,ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*y;
}

int tot=0,first[M];
struct Edge{
	int nxt,to;
}e[M<<1];
void add(int x,int y){
	e[++tot]=(Edge){first[x],y};
	first[x]=tot;
}

int sz[M],msz[M],msz2[M],dp1[M],dp2[M],Ans[M];
void dfs(int u,int fa){
	sz[u]=1;dp1[u]=dp2[u]=0;
	for(int i=first[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa) continue ;
		dfs(v,u);
		sz[u]+=sz[v];
		dp1[u]=max(dp1[u],dp1[v]);
		if(sz[msz[u]]<sz[v]) msz2[u]=msz[u],msz[u]=v;
		else if(sz[msz2[u]]<sz[v]) msz2[u]=v;
	}
	if(sz[u]<=n/2) dp1[u]=sz[u];
}
void dfs2(int u,int fa){
	for(int i=first[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa) continue ;
		if(n-sz[v]<=n/2) dp2[v]=n-sz[v];
		else if(v!=msz[u]) dp2[v]=max(dp2[u],dp1[msz[u]]);
		else dp2[v]=max(dp2[u],dp1[msz2[u]]);
		dfs2(v,u);
	}
	if(n-sz[u]>sz[msz[u]]) Ans[u]=(n-sz[u]-dp2[u]<=n/2);
	else Ans[u]=(sz[msz[u]]-dp1[msz[u]]<=n/2);
}

void solve(){
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		add(x,y),add(y,x);
	}
	dfs(1,0),dfs2(1,0);
	for(int i=1;i<=n;i++) printf("%d ",Ans[i]);
	printf("\n");
}

signed main(){
	solve();
}
```


---

## 作者：东厢头场雪 (赞：13)

## 前言
2021.8.16 树上问题模拟赛，老师加难度，出了这道原题作为 T1，考场写了个求重心，结果多测忘清空了（原题不是多测），听完后觉得自己可以切这道题，决定写个题解纪念一下  
[传送门](https://www.luogu.com.cn/problem/CF708C)  
## 题意  
已知有一棵 $n$ 个节点的树，定义对树的重构操作，删去树中的一条边，在两个连通块中各选取一个点连边，问对于树中的每一个点，能否通过至多一次重构使其称为树的重心。输入输出格式详见题面。  
## 数据范围  
数据有 $2\leq n\leq 400000$  
##  分析  
观察到数据范围，显然 $O(n^3)$ 的暴力算法不足以通过本题，考虑更优秀的做法。  
对于任意的一个节点 $x$，则对于任意一种重构，显然直接将不包含 $x$ 的连通块与 $x$ 直接连边最优。  
不妨以 $x$ 为根考虑，我们既要使砍下来的子树不超过 $\frac{n}{2}$，又要使剩下的点数尽可能少，所以砍下来的子树尽可能大。所以我们要求出对于每个节点能砍下的最大的大小不超过 $\frac{n}{2}$ 的真子树的大小。  
考虑维护两个数组 $f[i]$ 和 $g[i]$，当整棵树以 1 为根时，$f[i]$ 表示以 $i$ 为根的子树内能砍下的最大的大小不超过 $\frac{n}{2}$ 的真子树的大小，$g[i]$ 表示以 $i$ 为根的子树外能砍下的最大的大小不超过 $\frac{n}{2}$ 的真子树的大小。    
这就类似于换根 dp 的思想。  
显然，$f[i]$ 比较好维护，在第一次 dfs 时就可以求出：  
$f[i] = \max\limits_{v \in son[i]}\begin{cases}f[v]&siz[v] > \frac{n}{2}\cr siz[v]&siz[v]\leq\frac{n}{2}\end{cases}$  
对于 $g$ 数组，利用换根 dp，考虑由父亲节点 $i$ 向儿子 $v$ 的转移。可以是从 $g[i]$ 转移到 $g[v]$，可以父亲子树以外所有节点全部砍掉，也可是父亲的另一棵子树。这里比较麻烦，还要记录一下当前子树是否为父亲的最大子树，是的话还要维护一个次大值，类似于树形 dp 求直径。定义 $sec[i]$ 为次大值，$maxson[i]$ 为最大子树编号，则有：  
$g[v] = \max\limits_{v \in son[u]}\begin{cases}g[u]\cr n-siz[v]&n-siz[v]\leq\frac{n}{2}\cr sec[u]&v = maxson[u]\cr f[u]&v\neq maxson[u]\end{cases}$  
通过判断即可求出答案数组。  
上代码。  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 400000 + 10,M = 800000 + 10;
int T,n,tot;
int siz[N],f[N],g[N],ans[N],sec[N],maxson[N],maxn[N];
int ver[M],Next[M],head[N];
void add(int x,int y)
{
	ver[++tot] = y,Next[tot] = head[x],head[x] = tot;
}
void dfs(int u,int fa)
{
	siz[u] = 1,f[u] = 0,sec[u] = 0,maxson[u] = 0,maxn[u] = 0;
	for(int i = head[u];i;i = Next[i])
	{
		int v = ver[i];
		if(v == fa) continue;
		dfs(v,u);
		siz[u] += siz[v];
		if(siz[v] > siz[maxn[u]]) maxn[u] = v;
		if(siz[v] > n / 2)
		{
			if(f[v] > f[u]) sec[u] = f[u],f[u] = f[v],maxson[u] = v;
			else if(f[v] > sec[u]) sec[u] = f[v];
		}
		else
		{
			if(siz[v] > f[u]) sec[u] = f[u],f[u] = siz[v],maxson[u] = v;
			else if(siz[v] > sec[u]) sec[u] = siz[v];
		}
	}
}
void bdfs(int u,int fa)
{
	for(int i = head[u];i;i = Next[i])
	{
		int v = ver[i];
		if(v == fa) continue;
		g[v] = max(g[v],g[u]);
		if(n - siz[v] <= n / 2) g[v] = max(g[v],n - siz[v]);
		if(v == maxson[u]) g[v] = max(g[v],sec[u]);
		else g[v] = max(g[v],f[u]); 
		bdfs(v,u);
	}
}
bool check(int u)
{
	if(siz[maxn[u]] > n / 2) return siz[maxn[u]] - f[maxn[u]] <= n / 2;
	if(n - siz[u] > n / 2) return n - siz[u] - g[u] <= n / 2;
	return true;
}
signed main()
{
	T = 1;
	while(T--)
	{
		tot = 1;
		for(int i = 1;i <= n;i++)
		    ans[i] = f[i] = g[i] = 0;
		memset(head,0,sizeof(head));
		memset(Next,0,sizeof(Next));
		scanf("%d",&n);
		for(int i = 1;i < n;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			add(u,v);
			add(v,u);
		}
		dfs(1,0);
		g[1] = 0;
		bdfs(1,0);
		for(int i = 1;i <= n;i++)
		    if(check(i)) ans[i] = 1;
		for(int i = 1;i <= n;i++)
			printf("%d ",ans[i]);
		printf("\n");
	}
	return 0;
}
```
完结撒花！！！

---

## 作者：Clever_Jimmy (赞：10)

CF708C 【Centroids】题解

### 更新：

upd on 2020.08.04 fixed a typo

### 题意简述：

给定一棵 $n$ 个点的树，你可以删除一条边并增加一条边，形成一棵新树。

问每个点在进行这样的操作后，是否可能成为新树的重心。

$1 \le n \le 4\cdot 10^5$。

[题目链接](https://codeforces.com/problemset/problem/708/C)

### 解题思路：

一个不可否认的事实是，如果一个节点 $u$ 是原树的重心，那么它一定可以成为新树的重心。

如果一个节点 $u$ 有一棵子树 $v$ 的大小大于 $\left\lfloor\dfrac{n}{2}\right\rfloor$，我们可以尝试着将 $v$ 的子树中最大的一棵接到 $u$ 上，看能否使 $u$ 成为重心。

显然这样的子树 $v$ 对于 $u$ 而言最多只有一个。

令：

$$
\begin{aligned}
 & \textrm{siz}(u) =
 \begin{cases}
  1 & \textrm{son}(u) = \varnothing
  \\
  1 + \sum\limits_{v \in \textrm{son}(u)}\textrm{siz}(v) & \textrm{son}(u) \neq \varnothing
 \end{cases}
 \\
 & \textrm{maxson}(u) =
 \begin{cases}
  0 & \textrm{son}(u) = \varnothing
  \\
  \max\limits_{v \in \textrm{son}(u)}\textrm{siz}(v) & \textrm{son}(u) \neq \varnothing
 \end{cases}
 \\
 & f(u, 0) = \max\limits_{v \in \textrm{son}(u)}
 \begin{cases}
  \textrm{siz}(v) & \textrm{siz}(v) \le \left\lfloor\dfrac{n}{2}\right\rfloor
  \\
  f(v, 0) & \textrm{otherwise}
  \end{cases}
 \\
 & f(u, 1) = \mathop{\operatorname{second max}}\limits_{v \in \textrm{son}(u)}
 \begin{cases}
  \textrm{siz}(v) & \textrm{siz}(v) \le \left\lfloor\dfrac{n}{2}\right\rfloor
  \\
  f(v, 0) & \textrm{otherwise}
 \end{cases}
 \\
 & g(u) = \mathop{\operatorname{argmax}}\limits_{v \in \textrm{son}(u)}
 \begin{cases}
  \textrm{siz}(v) & \textrm{siz}(v) \le \left\lfloor\dfrac{n}{2}\right\rfloor
  \\
  f(v, 0) & \textrm{otherwise}
 \end{cases}
\end{aligned}
$$
至此，我们求出来了每个节点 $u$ 的重儿子 $\textrm{son}(u)$，最大的小于 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 的子树 $g(u)$ 以及其大小 $f(u, 0)$，次大的小于 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 的子树大小 $f(u, 1)$ 。

对一个节点 $u$ 求上述所有值的时间复杂度为 $O(n)$。

那么如何解决问题呢？

考虑换根dp，用 $h(u)$ 来维护不是 $u$ 的子树中，小于等于 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 的最大子树大小。

令：

$$
u = \textrm{parent}(v), h(v) = \max\{
\begin{cases}
 n - \textrm{siz}(u) & n - \textrm{siz}(u) \le \left\lfloor\dfrac{n}{2}\right\rfloor
 \\
 h(u) & n - \textrm{siz}(u) > \left\lfloor\dfrac{n}{2}\right\rfloor
 \\
 f(u, 1) & g(u) = v
 \\
 f(u, 0) & g(u) \neq v
\end{cases}
\}
$$

这样我们就可以用 $h(u)$ 来解决「原来 $v$ 是 $u$ 的孩子但现在 $u$ 是 $v$ 的孩子」的情况了。

最后，对于每个点：

- 如果 $\textrm{siz}(\textrm{maxson}(u)) > \left\lfloor\dfrac{n}{2}\right\rfloor$

  我们就只需要检查 $\textrm{siz}(\textrm{maxson}(u)) - f(\textrm{maxson}(u), 0)$ 是否小于等于 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 即可；
  
- 如果 $n - \textrm{siz}(u) > \left\lfloor\dfrac{n}{2}\right\rfloor$

  我们就只需要检查 $n - \textrm{siz}(u) - h(u)$ 是否小于等于 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 即可；

### 参考代码：

```cpp
#include <bits/stdc++.h>
#define LL long long

const int N = 4e5 + 5;
const int M = 8e5 + 5;

int n, cnt, first[N], siz[N], maxson[N], f[N][2], g[N], h[N], ans[N];

struct EDGE {
    int to, _next;
} e[M];

void add(int u, int v) {
    e[cnt].to = v, e[cnt]._next = first[u];
    first[u] = cnt++;
}

void dfs1(int x, int p) {
    siz[x] = 1;
    for(int i = first[x]; ~i; i = e[i]._next) {
        int y = e[i].to;
        if(y == p)
            continue;
        dfs1(y, x);
        siz[x] += siz[y];
        if(siz[y] > siz[maxson[x]])
            maxson[x] = y;
        
        int cur = (siz[y] <= n / 2) ? siz[y] : f[y][0];
        
        if(cur > f[x][0]) {
            f[x][1] = f[x][0];
            f[x][0] = cur;
            g[x] = y;
        }
        else if(cur > f[x][1])
            f[x][1] = cur;
    }
}

void dfs2(int x, int p) {
    ans[x] = 1;
    if(siz[maxson[x]] > n / 2)
        ans[x] = (siz[maxson[x]] - f[maxson[x]][0] <= n / 2);
    else if(n - siz[x] > n / 2)
        ans[x] = (n - siz[x] - h[x] <= n / 2);
    
    for(int i = first[x]; ~i; i = e[i]._next) {
        int y = e[i].to;
        if(y == p)
            continue;
        
        int cur = (n - siz[x] <= n / 2) ? (n - siz[x]) : h[x];
        
        h[y] = std::max(h[y], cur);
        h[y] = std::max(h[y], f[x][g[x] == y]);
        
        dfs2(y, x);
    }
}

int32_t main() {
    scanf("%d", &n);
    memset(first, -1, sizeof(first));
    for(int i = 1; i <= n - 1; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        add(u, v), add(v, u);
    }
    dfs1(1, 0), dfs2(1, 0);
    for(int i = 1; i <= n; ++i)
        printf("%d ", ans[i]);
    return 0;
}
```


---

## 作者：RyexAwl (赞：8)

考虑当我们已经确定了一棵树的重心并以重心为根，有一个显然的结论，对于任一子节点为根的子树大小一定不超过$\lfloor\frac{n}{2} \rfloor$。

因为去掉重心，树所剩下的每个部分一定不超过$\lfloor\frac{n}{2} \rfloor$，对于每个部分的每棵子树的大小只能更小。

因此如果我们以树的重心为根，如果一个点$x$不能成为重心，一定是$n-size(x)>\lfloor\frac{n}{2} \rfloor$。

例如下面这棵树：

![](https://cdn.luogu.com.cn/upload/image_hosting/ljn19og2.png)

以重心$2$为根，点$3$显然不能成为重心，其原因是$n-size(3)=8>5$即$B$部分的大小大于$\lfloor\frac{n}{2} \rfloor$

接下来考虑对这棵树进行改造：

我们要在$Part_A$中选一条边删除，将其分裂成两个不连续的部分，再将其中一部分与$3$连接。

下面是一种改造过程：

1.删除边$<1,2>$，使其$Part_A$分裂成两部分
![](https://cdn.luogu.com.cn/upload/image_hosting/jrqpl91p.png)

2.添加边$<2,3>$，将分裂出去的部分接成点$3$的子树
![](https://cdn.luogu.com.cn/upload/image_hosting/61kkk3vo.png)

这样，经过改造点$3$可以成为树的重心。

那么，为了令我们当前的点$x$尽可能的成为重心，我们就需要使得分裂出去的部分尽可能地大，并直接接在点$x$上。

即我们要在$n-size(x)$的部分找最大的且大小不超过$\lfloor\frac{n}{2} \rfloor$连续的一部分，记其大小为$f(x)$。

如果$n-size(x)-f(x)\le \lfloor\frac{n}{2} \rfloor$，那么这个点就可以成为重心，反之则不可以。

那么接下来我们要考虑如何计算出$f(x)$

记$fa(x)$为$x$的父节点。

![](https://cdn.luogu.com.cn/upload/image_hosting/785049kb.png)


考虑$f(2)$的所有决策:


$1.$ $n-size(2)\le\lfloor\frac{n}{2} \rfloor$时：$n-size(2)$

$2.$其兄弟$3$的子树内，大小不超过$\lfloor\frac{n}{2} \rfloor$的最大子树大小。

再来考虑$2$的儿子的决策。

![](https://cdn.luogu.com.cn/upload/image_hosting/4gi5vvry.png)

$n-size(x)$大体分成两部分：$x$的兄弟，和除了$x$与$x$兄弟的部分。

并且这两部分互不干扰：

首先，如果$n-size(x)>\lfloor\frac{n}{2} \rfloor$，其断开的边不可能是与其父节点相连的边$<fa(x),x>$。

那么所删的一条边只能是其兄弟子树与父节点相连的一条边或不包括$fa(x)$的部分的一条边。

设$d(x)$为以$x$为根的子树中大小不超过$\lfloor\frac{n}{2} \rfloor$的最大子树，设$B(x)$为$x$的兄弟节点集合。

那么有转移方程
$$
f(x)=\max\left\{ 
\begin{aligned}
&n-size(x)\ (n-size(x) \le \lfloor \frac{n}{2}\rfloor)\\
&\max\limits_{j\in B(x),j\not=x}\{d(j)\} \\
&f(fa(x))
\end{aligned}
\right.
$$
这里有一个常用技巧：令$d(x,0)$为最大，$d(x,1)$为次大
那么有转移方程：
$$

f(x)=\max\left\{ 
\begin{aligned}
&n-size(x)\ \ \ (n-size(x) \le \lfloor \frac{n}{2}\rfloor)\\
& d(fa(x),0)\ \ \ (d(x,0)\not=d(fa(x),0))\\ 
& d(fa(x),1)\ \ \ (d(x,0)=d(fa(x),0))\\
&f(fa(x))
\end{aligned}
\right.
$$
接下来考虑计算$d(x)$

因为我们以重心为根，因此$d(x,0)$即为以$x$的子节点为根的最大的子树的大小。在更新$d(x,0)$时顺便更新$d(x,1)$:
$$
\begin{aligned}
&event:size(son)>d(x,0): \\
&do:d(x,1)=d(x,0),d(x,0)=size(son)\\
&envet:d(x,0)\ge size(son)>d(x,1):\\
&do:d(x,1)=size(son)
\end{aligned}
$$

这样的复杂度是$O(n)$的。

代码:
```cpp
#include <iostream>
#include <cstring>

namespace wxy{
    const int N = 4e5 + 10;
    int size[N],head[N],fail[N << 1],edge[N << 1],tot = 0;
    int n,root = 1,ans = 1e9;
    bool vis[N];
    int d[N][3],f[N];
    inline void add(int x,int y){
        edge[++tot] = y;
        fail[tot] = head[x];
        head[x] = tot;
    }
    inline void insert(int x,int y){add(x,y);add(y,x);}
    void dfs_root(int u){
        int max_part = 0;
        size[u] = 1;
        vis[u] = true;
        for (int i = head[u];i;i = fail[i]){
            int v = edge[i];
            if (vis[v]) continue;
            dfs_root(v);
            size[u] += size[v];
            max_part = std::max(max_part,size[v]);
        }
        max_part = std::max(max_part,n - size[u]);
        if (max_part < ans){
            ans = max_part;
            root = u;
        }
    }
    void dfs_d(int u){
        vis[u] = true;
        size[u] = 1;
        for (int i = head[u];i;i = fail[i]){
            int v = edge[i];
            if (vis[v]) continue;
            dfs_d(v);
            size[u] += size[v];
            if (size[v] > d[u][0]){
                d[u][1] = d[u][0];
                d[u][0] = size[v];
            }else if (size[v] > d[u][1]){
                d[u][1] = size[v];
            }
        }
    }
    void dfs_f(int u,int fa){
        vis[u] = true;
        if (d[fa][0] == size[u]) f[u] = std::max(d[fa][1],f[fa]);
        else f[u] = std::max(d[fa][0],f[fa]);
        if (n - size[u] <= n / 2) f[u] = std::max(f[u],n - size[u]);
        if (u == root) f[u] = 0;
        for (int i = head[u];i;i = fail[i]){
            int v = edge[i];
            if (vis[v]) continue;
            dfs_f(v,u);
        }
    }
    void main(){
        std::cin >> n;
        for (int i = 1; i < n; i++){
            int x,y;
            std::cin >> x >> y;
            insert(x,y);
        }
        dfs_root(1);
        
        memset(vis,false,sizeof vis);
        memset(size,0,sizeof size);
        dfs_d(root);
        memset(vis,false,sizeof vis);
        dfs_f(root,0);
        //for (int i = 1; i <= n; i++) std::cout << f[i] << " ";
        //std::cout << std::endl;
        for (int i = 1; i <= n; i++){
            if (size[i] >= n / 2) std::cout << 1 << " ";
            else if (n - size[i] - f[i] <= n / 2) std::cout << 1 << " ";
            else std::cout << 0 << " ";
        }
        
    }
}signed main(){wxy::main();return 0;}
```






---

## 作者：meizhuhe (赞：7)

## 前置芝士
**不用换根dp！！！**（~~因为我不会~~）
~~只用~~线段树、队列、二分、dfs序、贪心、简单的树形“递推”（因为几乎称不上dp）
## step1:贪心理解
设节点1为原树的根。
首先，考虑在没有进行操作时把节点 $x$ 删除，分出的若干棵子树中**最多只有**一棵子树的大小 $>\frac{n}{2}$。(如果一棵都没有，那么这个点就是原树的质心，肯定 $ans_x=1$）那么考虑通过操作来分裂这颗不满足的子树 $T_s$。方法就是将某个节点 $y \in T_s$ 到其父亲节点的边删除，然后将这个以 $y$ 为根的 $T_s$ 子树挂到这个 $y$ 上（如图1）。但是，哪里有点不对。如果 $y$ 在从 $x$ 的到根路径上，那么这样在原树上操作后原树就不是树了（如图2）
![](https://cdn.luogu.com.cn/upload/image_hosting/yua9uehe.png)(图1)
![](https://cdn.luogu.com.cn/upload/image_hosting/jmu2yjmk.png)(图2）

难道 $y$ 就真的不能在 $x$ 到根节点的路径上吗？不是的！除了将 $y$ 挂到 $x$ 上，还可以将 $y$ 的补集挂到 $x$ 上去。具体地，删除操作相同，但是这回是将根节点挂到 $x$ 上去（如图3）(而且这么一搞 $x$ 就变成了根节点）。
![](https://cdn.luogu.com.cn/upload/image_hosting/ket3rnmu.png)

根据**贪心**思想，我们希望分裂出来的以 $y$ 为根的子树在不大于 $\frac{n}{2}$ 的条件下越大越好。(1)
## step2:简单树形“递推”
对不满足的子树 $T_s$ 只有两种情况，一种是 $Ts$ 包含 $x$ 的父亲，另一种是不包含（即 $T_s$ 是 $x$ 的一棵子树）

先考虑较为简单的第二种，那么根据结论(1),我们需要求出一颗子树的最大的子树大小，且这个大小需要不大于 $\frac{n}{2}$ 。这十分的容易，设 $f(x)$为这个最大值，那么可得：
$$f(x)=
\begin{cases}
 size_x & size_x \leq \frac{n}{2}\\
\max\{y \in child(x)|f(y)\}&size_x>\frac{n}{2}
\end{cases}
$$
## step3:dfs序配合线段树（或树状数组）
再考虑较为困难的第一种，这种情形下，对于分裂节点 $y$ 又有两种情况（其实上文讲过了），一是在从 $x$ 到根的路径上，另一种不是。

对于第二种情形，较为简单。在dfs的过程中维护一个参数 $tmp$,表示所有符合条件的分裂节点  $y$ 的子树大小的最大值。设当前所在的节点为 $u$ ,将要 dfs 的孩子 $v$ ，易见，$tmp$ 向下递归传递的过程中，只需用 $u$ 所有非 $v$ 的孩子 $w$ 的 $f(w)$更新 $tmp$ 即可。当然，要先保存个副本，dfs完了需要再把 $tmp$ 还原回去。

However, 怎么更新呢？暴力肯定是不行的。我们想到了线段树！线段树处理树上问题肯定是要用 dfs 序的。用线段树维护节点的 $dp$ 值，即如果大小符合 $n/2$ 的条件，$dp_x=size_x$ ; 否则  $dp_x=0$
## step4:队列思想
现在只剩下第一种情形了，即 $y$ 在从 $x$ 到根的路径上。在 dfs 的过程中，维护一个队列，从根到当前节点 $u$ 路径上所有的节点的 $size$ 值。那么，当每当即将 dfs 孩子节点 $v$ 时，就不断地从队首弹出元素，直到 $Q[top]-size[v]\leq \frac{n}{2}$ (注意，队列要用数组维护而不能使用 STL ，因为使用数组只需还原 top 的值即可还原队列）
## step5:二分优化
到目前为止，已经可以写出一份不会 WA 的代码了，甚至对于大多数情形都是可以 AC 的。（实测：至少能通过前 86 个测试点）。对于第87个测试点，让我们来看一棵树（图4）：
![](https://cdn.luogu.com.cn/upload/image_hosting/w70gmb3m.png)
(图4)

在这种极端情形下，队列弹出会变得十分低效，重复很多次，浪费时间，TLE

如何解决？其实也 easy 。注意到队列的元素都**单调递减**，因此我们只需二分 top ,可以使用 lower_bound函数轻松解决。

## 代码
$\text{Now,the difficult problem has been solved!}$
```cpp
#include <bits/stdc++.h>
#define MAXN 400009
using namespace std;

int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], cnt;
int size[MAXN], dp[MAXN], f[MAXN], id[MAXN], fa[MAXN], exc[MAXN], ans[MAXN];
int a[MAXN], T[MAXN<<2];
int Q[MAXN], top = 1, tail;
int n;
void match(int u, int v)
{
    ++cnt;
    to[cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
void build(int l, int r, int p)
{
    if (l == r)
    {
        T[p] = a[l];
        return;
    }
    int m = l + r >> 1;
    build(l, m, p << 1);
    build(m + 1, r, p << 1 | 1);
    T[p] = max(T[p << 1], T[p << 1 | 1]);
}
int __query(int l, int r, int p, int ll, int rr)
{
    if (ll <= l && r <= rr)
        return T[p];
    if (rr < l || ll > r)
        return 0;
    int m = l + r >> 1;
    return max(__query(l, m, p << 1, ll, rr), __query(m + 1, r, p << 1 | 1, ll, rr));
}
inline int query(int l, int r)
{
    return __query(1, n, 1, l, r);
}
inline int except(int x)
{
    return max(query(id[fa[x]] + 1, id[x] - 1), query(id[x] + size[x], id[fa[x]] + size[fa[x]] - 1));
}
void dfs1(int u, int fat, int &dfstime)
{
    size[u] = 1;
    fa[u] = fat;
    id[u] = ++dfstime;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa[u])
            continue;
        dfs1(v, u, dfstime);
        size[u] += size[v];
        f[u] = max(f[u], f[v]);
    }
    if (size[u] <= n / 2)
        dp[u] = f[u] = size[u];
    a[id[u]] = dp[u];
}
void dfs2(int u, int greedy, int tmp)
{
    ans[u] = 1;
    if (n - size[u] >= n / 2)
    {
        if (n - size[u] - greedy > n / 2)
            ans[u] = 0;
        else
            ans[u] = 1;
    }
    else
    {
        for (int i = head[u]; i; i = nxt[i])
        {
            int v = to[i];
            if (v == fa[u])
                continue;
            if (size[v] >= n / 2)
            {
                if (size[v] - f[v] > n / 2)
                    ans[u] = 0;
                else
                    ans[u] = 1;
                break;
            }
        }
    }
    int ttop = top, ttmp = tmp, tgreedy = greedy;
    Q[++tail] = size[u];
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa[u])
            continue;
        /*
        while (tail - top + 1 >= 1 && Q[top] - size[v] > n / 2)
            top++;
        */
        top=lower_bound(Q+top,Q+tail+1,n/2+size[v],greater<int>())-Q;
        int data;
        if (tail - top + 1 == 0)
            data = 0;
        else
            data = Q[top];
        tmp = max(tmp, exc[v]);
        greedy = max(data - size[v], tmp);
        dfs2(v, greedy, tmp);
        greedy = tgreedy;
        tmp = ttmp;
        top = ttop;
    }
    --tail;
}
int main()
{
    //freopen("read.in","r",stdin);
    //freopen("write.out","w",stdout);

    int t = 0;
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        match(u, v);
        match(v, u);
    }
    dfs1(1, 0, t);
    build(1, n, 1);
    for (int i = 1; i <= n; i++)
        exc[i] = except(i);
    dfs2(1, 0, 0);
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    return 0;
}
```
## 结束语
写完翻一眼题解，发现竟没什么人跟我的做法一样。这也说明，题解永远只是一种辅助，不能让题解限制了你的思维。当然，我们也应懂得取其精华去其糟粕，吸收题解有益的部分（比如我马上要去学习一波换根dp）

最后的最后推荐一个非官方的 codeforces 镜像网站，不禁速度飞起，爽不已，遂分享此站于君
[https://codeforces.ml/](https://codeforces.ml/)
以及一个辅助我画树的软件 Graphviz（这个自行dfs）

---

## 作者：pyqpyq (赞：5)

~~人生第一个最优解（目前）赶紧写篇题解庆祝一下。~~

当然你得先看完[这个](https://www.luogu.com.cn/blog/150384/shu-di-zhong-xin-xiang-guan-gai-nian-yu-zheng-ming)。

证明看不懂也没关系。~~我都不知道我当年怎么口胡的。~~ 但性质三一定要看一看，后面有用。

其实是一道挺值得想的问题，分五个步骤。建议在看每个步骤前先思考，想不出了再看。
# Step 1
改造？把一条边拆下来再装上去？怎么弄？

首先这是一个无根树，我们把它变成有根树更好处理。然后一步一步来看。

先是拆边，发现每条边对应一对父子关系，拆掉之后就会把儿子所对应的子树与外界隔绝。

然后加边。为了使加完后还是一棵树，我们需要将加入的边的一头接到这个子树的某个节点上，另一头接到外界的某个节点上。

然而这个外界的节点已经有父亲了，所以这个子树就只能当它的一棵子树了。

~~总而言之砍一块树下来再补上去。~~
# Step 2
题目问我们那些点可以通过改造变成重心，那我们一个一个看。

对于本来就是重心的节点，我们不用管它。

对于本来非重心的节点，它和重心的区别就在于有一棵子树~~生长激素分泌过多导致~~过于庞大。

那我们的任务就是把这个~~病变的~~子树通过改造砍成正常的也就是小于等于全树的一半就行了。

不过砍下来的部分还要接到一棵子树上去，我们同时不能让这个子树变得过大。

那么设 $a$ 是被砍的子树的大小，$b$ 是要被接上去的子树的大小，$s$ 是全树的大小，$l$ 是砍下来的树的大小。

列不等式，得：
$$\begin{cases}
a-l\le\frac{s}{2}\\
b+l\le\frac{s}{2}\\
\end{cases}$$

解得：
$$a-\frac{s}{2}\le l\le\frac{s}{2}-b$$
# Step 3
直接拿这个东西和平衡树上是会发生 TLE/MLE 悲剧的。我们需要分析它。

由于 $l$ 的取值范围的左边界是固定的，我们处理右边界。先处理子树截下来要接到谁上面的问题。

当然，为了使 $l$ 有更多取值，$\frac{s}{2}-b$ 越大越好。而 $\frac{s}{2}$ 是固定的，那么要让 $b$ 尽可能的小。

那什么时候 $b$ 最小呢？直接接到根上面，那样 $b$ 就为 0 了。

所以这个式子变成了这样：
$$a-\frac{s}{2}\le l\le\frac{s}{2}$$
# Step 4
好像思路遇到死胡同了？考虑一下重心。

我们会发现被砍的子树一定是包含重心的子树，而且砍的时候**只要不把重心砍下来，一定可以满足右边界的条件**。

为何加粗呢？因为想通了这个，这题就差不多了。至于为什么，自己思考。~~我不会告诉你我是懒得画图的。~~

那么既然这样，我们就砍重心的各个子树。我们从中选取最大的子树以尽量满足左边界条件。如果仍然不能满足就无能为力了，说明当前询问的点本身就不行。
# Step 5
然而你直接这么干还是会 WA on test 3 的，死因是没有考虑有两个重心的情况。

遇到这种情况可以换个重心跑两遍，当然也可以直接输出全 1，原因自己思考吧（~~再次偷懒~~）。
# Code
按上面搞完就你谷最优解了，再换个语言卡个常就 CF 第二解了。

~~在线膜 CF 最优解。~~

注意：代码放给你是用来对拍、查错的，不是用来抄袭的。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 400011
int n,u,v,firs[MAXN],neig[MAXN<<1],arri[MAXN<<1],size[MAXN],cent,ncen,rans[MAXN],smax=INT_MIN,nmax=INT_MIN;
int read()
{
    register int re(0),ch;
    do
        ch=getchar();
    while('9'<ch||ch<'0');
    do
        re=re*10+ch-'0';
    while('0'<=(ch=getchar())&&ch<='9');
    return re;
}
int dfs1(int at,int fa)
{
    register int ce(1);
    size[at]=1;
    for(int i=firs[at]; i; i=neig[i])
        if(arri[i]!=fa)
        {
            size[at]+=dfs1(arri[i],at);
            if(size[arri[i]]*2>n)
                ce=0;
        }
    if(ce&&size[at]*2>=n)
    {
        if(cent)
            ncen=at;
        else
            cent=at;
        rans[at]=1;
    }
    return size[at];
}
int dfs2(int at,int fa)
{
    size[at]=1;
    for(int i=firs[at]; i; i=neig[i])
        if(arri[i]!=fa)
            size[at]+=dfs2(arri[i],at);
    return size[at];
}
void dfs3(int at,int fa,int si)
{
    if(size[at]*2+si*2>=n)
        rans[at]=1;
    for(int i=firs[at]; i; i=neig[i])
        if(arri[i]!=fa)
            dfs3(arri[i],at,si);
}
int main()
{
    n=read();
    for(int i=1; i<n; ++i)
    {
        u=read();
        v=read();
        neig[i<<1]=firs[u];
        firs[u]=i<<1;
        arri[i<<1]=v;
        neig[i<<1|1]=firs[v];
        firs[v]=i<<1|1;
        arri[i<<1|1]=u;
    }
    dfs1(1,0);
    if(ncen)
    {
        for(int i=1;i<=n;++i)
        {
            putchar('1');
            putchar(' ');
        }
        return 0;
    }
    dfs2(cent,0);
    for(int i=firs[cent]; i; i=neig[i])
    {
        if(size[arri[i]]>=smax)
        {
            nmax=smax;
            smax=size[arri[i]];
        }
        else if(size[arri[i]]>=nmax)
            nmax=size[arri[i]];
    }
    for(int i=firs[cent]; i; i=neig[i])
        dfs3(arri[i],cent,size[arri[i]]==smax?nmax:smax);
    for(int i=1; i<=n; ++i)
    {
        putchar('0'+rans[i]);
        putchar(' ');
    }
    return 0;
}
```

---

## 作者：MoonPie (赞：4)

[CF708C Centroids](http://codeforces.com/problemset/problem/708/C)

考虑一种和CSP 2019 Day T3 ~~一样~~ 很像的做法

The Solution
------------

如果一个结点 $u$ 不是重心，那么它有且仅有一个$siz_v \ge n/2$ （重儿子）

则要在重儿子找一棵大小为 $S$ 的树，满足

$$
\left\{\begin{matrix}
 2 \times (siz_v - S) \le n\\
 2\times S \le n\\

\end{matrix}\right.
$$

化简后得到 $siz_v - n/2 \le S \le n/2$



------------
进一步地，

假设是一棵以重心为根的有根树，则对于结点 $u \ne root$ 

其重儿子大小为 $n - siz_u$ ，及断掉 $u$ 与其 $fa$ 的连边后的另一棵树

问题转化为，对于每一个 $u$ 判断上边有无一棵大小

满足 **不在 $u$ 的子树内**( _~~Obviosly~~_ ) 且 $n/2-siz_u \le S \le n/2$  的树

------------

具体实现就是维护两个**权值树状数组**，记 $t1$ 和 $t2$

$t1[i]$ 维护全局的大小小于 $i$ 的个数

$t2[i]$ 维护  **当前扫过点的子树中**  大小小于 $i$ 的个数

那么对于一个 $u$ ，其子树内满足条件的数量就是扫完 $u$ 之后，$t2$ 的**变化量**，是需要减去的

The Code
------------
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=400005;
int n,E,root,siz[N],ans[N],t1[N],t2[N];
int pnt[N*2],nxt[N*2],head[N];
void add_e(int u,int v) {pnt[++E]=v,nxt[E]=head[u],head[u]=E;}
void prp(int u,int f) {
	siz[u]=1;
	bool ok=1;
	for(int i=head[u];i;i=nxt[i]) {
		int v = pnt[i];
		if(v == f) continue;
		prp(v,u);
		siz[u] += siz[v];
		if(siz[v] > n/2) ok=0;
	}
	if(n-siz[u] > n/2) ok=0;
	if(ok) root=u, ans[u]=1;
}
void add(int a[],int x,int v) {if(x<=0) return;for(++x;x<=n+1;x+=x&-x) a[x]+=v;}
int ask(int a[],int x) {
	if(x <= 0) return 0;
	int res = 0;
	for(++x;x;x-=x&-x) res += a[x];
	return res;
}
void solve(int u,int fa) {	
	int t=0;
	add(t1,siz[fa],-1);
	add(t1,n-siz[u],1);
	if(ans[u] == 0) {
		t += ask(t1,n/2);
		t -= ask(t1,(n-2*siz[u]+1)/2-1);
		t += ask(t2,n/2);
		t -= ask(t2,(n-2*siz[u]+1)/2-1);
	}
	add(t2,siz[u],1);
	for(int i=head[u];i;i=nxt[i]) {
		int v = pnt[i];
		if(v==fa) continue;
		solve(v,u);
	}
	add(t1,siz[fa],1);
	add(t1,n-siz[u],-1);
	if(ans[u] == 0) {
		t -= ask(t2,n/2);
		t += ask(t2,(n-2*siz[u]+1)/2-1);
		if(t > 0) ans[u]=1;
	}
}
int main(){
	scanf("%d",&n);
	for(int u,v,i=1;i<n;i++) {
		scanf("%d%d",&u,&v);
		add_e(u,v), add_e(v,u);
	}
	prp(1,0);
	prp(root,0);
	for(int i=0;i<=n;i++) add(t1,siz[i],1);
	solve(root,0);
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
	return printf("\n"),0;
}
```

---

## 作者：TEoS (赞：4)

本文同步发表在[我的blog](https://www.cnblogs.com/TEoS/p/13597264.html)

------------
**题意分析**

给出一棵树，求有多少个节点满足在树上删去一条边再加入一条边后可以成为树的重心。

**思路分析**

设当前节点为 $x$ 。经过分析后很容易发现，题目中要求的操作一定是在以当前节点为根时，将其中一棵子树接到根节点上，设这棵子树的根节点为 $p_x$。则若 $x$ 已经是重心，则不用操作；若 $x$ 不是重心，则有且只有一棵 $x$ 的直接子树（即以 $x$ 的儿子节点为根的子树）的大小 $>\left \lfloor  \frac{n}{2}\right \rfloor$，因此一定要把这棵直接子树中的一棵子树接到 $x$ 上。显然，这棵被移动的子树应该是这棵直接子树中的最大的大小不超过 $\frac{n}{2}$ 的子树。可以证明这个移动策略一定是最优的。然后判断移动后 $x$ 是否为重心即可。

对于每个节点都重新计算显然复杂度太高，发现很多信息可以重复利用，考虑换根。对于一个普通节点 $x$ ， $p_x$ 可能位于以 $x$ 为根的子树当中，也有可能不位于。对这两种情况，可以分两路进行递推。

1. $p_x$ 在以 $x$ 为根的子树当中

找到 $x$ 的最大直接子树，若该子树的大小 $>\left \lfloor  \frac{n}{2}\right \rfloor$ ，那么就从这棵子树中找出最大的不超过 $\frac{n}{2}$ 的子树，这棵子树的根节点即为 $p_x$ 。若没有，说明 $p_x$ 不在这或者 $x$ 原本就是重心。

2. $p_x$ 不在以 $x$ 为根的子树当中

有两种情况：

-  $p_x$ 在以 $x$  的父亲为根的子树当中

这种情况下，可以通过记录每个节点的最大的满足大小 $\leq\left \lfloor  \frac{n}{2}\right \rfloor$ 的子树。注意，如果 $x$ 恰好在该子树当中，则需要选择第二大的合法子树，因此需要存储最大的和第二大的两个信息。

-  $p_x$ 不在以 $x$  的父亲为根的子树当中

这种情况下，直接将整棵树去掉以 $x$ 的父亲为根的部分看作一个子树，用类似于“ $p_x$ 在以 $x$ 为根的子树当中”的方法去处理即可。

**具体实现**

根据上面的分析，需要对于每个节点，需要存储以下信息：

- $son_{x,0},son_{x,1}$ 分别存储以 $x$ 为根的子树中最大的和次大的大小 $\leq\left \lfloor  \frac{n}{2}\right \rfloor$ 的子树的大小；
- $fa_x$ 存储整棵树除去以 $x$ 为根的子树外最大的大小 $\leq\left \lfloor  \frac{n}{2}\right \rfloor$ 的子树的大小；
- $siz_x$ 存储以 $x$ 为根的子树的大小；
- $ansp_x$ 存储 $p_x$；
- $maxson_x$ 存储 $x$ 的重儿子，即子树最大的儿子；
- $ans_x$ 存储 $x$ 的答案。

1. 预处理

预处理出 $siz,maxson,son,ansp$ 四个数组的值。前两个数组的处理很简单，就不赘述了； $son$ 数组，对于当前扫描到的子节点，若以该子节点为根的子树大小 $\leq\left \lfloor  \frac{n}{2}\right \rfloor$ ，则用其更新 $son$ 数组，否则用该子节点的 $son_0$ 进行更新。处理 $son$ 数组时，若决策更优，则更新 $ansp$ 数组。

```c++
void check(int x,int y,int p)
{
	if(y>son[x][0] && y<=n/2)//与最大的比较
		son[x][1]=son[x][0],son[x][0]=y,ansp[x]=p;
	else
		if(y>son[x][1] && y<=n/2)//比最大的小，则与次大的比较
			son[x][1]=y;
}//判断决策是否更优

void pre(int x,int f)
{
	siz[x]=1;
	for(int i=head[x];i;i=Next[i])
	{
		int y=ver[i];
		if(y==f)
			continue;
		pre(y,x);
		siz[x]+=siz[y];
		if(siz[y]>siz[maxson[x]])
			maxson[x]=y;//找重儿子
		check(x,siz[y]<=n/2?siz[y]:son[y][0],y);//注意不能让同一子节点贡献两个决策
	}
}
```

2. 处理 $fa$ 同时求解

用类似于处理 $son$ 数组的方法处理 $fa$ 数组，这里就不赘述了。然后分别判断父节点方向和子树方向的两种情况是否合法，以及其本身是否就是重心，从而求解。

```c++
void checkfa(int x,int y)
{
	if(y>fa[x] && y<=n/2)
		fa[x]=y;
}//判断决策是否更优

void solve(int x,int f)
{
	checkfa(x,n-siz[f]<=n/2?n-siz[f]:fa[f]);
	if(ansp[f]==x)//本身在最大子树，则采用次大作为决策
		checkfa(x,son[f][1]);
	else//否则采用最大
		checkfa(x,son[f][0]);
	if(siz[maxson[x]]>n/2)//在子树内
		ans[x]=(siz[maxson[x]]-son[maxson[x]][0]<=n/2);
	else
		if(n-siz[x]>n/2)//在父节点方向
			ans[x]=(n-siz[x]-fa[x]<=n/2);
		else
			ans[x]=1;//原本就是重心
	for(int i=head[x];i;i=Next[i])
	{
		int y=ver[i];
		if(y==f)
			continue;
		solve(y,x);
	}
}
```

**图例解释**

![](https://cdn.luogu.com.cn/upload/image_hosting/anvhwp9h.png)

以上图为例（默认节点 $1$ 作为根节点）：（为了方便，以下的最大子树均指 $\leq\left \lfloor  \frac{n}{2}\right \rfloor$ 的子树）

- 最大子树位于子树方向且为直接子树：9
- 最大子树位于子树方向且不为直接子树：1、2、6、10
- 最大子树位于父亲方向且为直接子树：7
- 最大子树位于父亲方向且不为直接子树：3、4、5、8

```c++
#include<iostream>
#include<cstdio>
using namespace std;
const int N=1e6+100;
int n,tot;
int head[N],ver[2*N],Next[2*N];
int siz[N],ans[N],ansp[N],maxson[N],fa[N],son[N][2];
void add(int x,int y)
{
	ver[++tot]=y,Next[tot]=head[x],head[x]=tot;
	ver[++tot]=x,Next[tot]=head[y],head[y]=tot;
}//邻接表
void check(int x,int y,int p)
{
	if(y>son[x][0] && y<=n/2)
		son[x][1]=son[x][0],son[x][0]=y,ansp[x]=p;
	else
		if(y>son[x][1] && y<=n/2)
			son[x][1]=y;
}//子树方向更新
void checkfa(int x,int y)
{
	if(y>fa[x] && y<=n/2)
		fa[x]=y;
}//父亲方向更新
void pre(int x,int f)
{
	siz[x]=1;
	for(int i=head[x];i;i=Next[i])
	{
		int y=ver[i];
		if(y==f)
			continue;
		pre(y,x);
		siz[x]+=siz[y];
		if(siz[y]>siz[maxson[x]])
			maxson[x]=y;
		check(x,siz[y]<=n/2?siz[y]:son[y][0],y);
	}
}//预处理
void solve(int x,int f)
{
	checkfa(x,n-siz[f]<=n/2?n-siz[f]:fa[f]);
	if(ansp[f]==x)
		checkfa(x,son[f][1]);
	else
		checkfa(x,son[f][0]);
	if(siz[maxson[x]]>n/2)
		ans[x]=(siz[maxson[x]]-son[maxson[x]][0]<=n/2);
	else
		if(n-siz[x]>n/2)
			ans[x]=(n-siz[x]-fa[x]<=n/2);
		else
			ans[x]=1;
	for(int i=head[x];i;i=Next[i])
	{
		int y=ver[i];
		if(y==f)
			continue;
		solve(y,x);
	}
}//处理 fa 同时求解
int main()
{
	scanf("%d",&n);
	for(int i=1,x,y;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	pre(1,0),solve(1,0);
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
	return 0;
}
```



---

## 作者：Vocalise (赞：2)

一个暴力大常数，但是好理解的做法。也有适用性。

先进行分析：

一个点，如果它在原树上就是重心，那么随便找一条边删了再连即可。

如果不是，那么它一定有惟一一个子树大小大于 $\lfloor \dfrac n 2 \rfloor$，我们称为不合法子树（反之为合法子树）。我们考虑将它之中的一个合法子树提出，然后接到该点下。如果可以让剩下的子树合法，该点就可以成为重心。

为方便处理，我们先认为 $1$ 号点为根。

也就是说，我们需要求出每个子树中最大的合法子树大小，还要求出每个点子树补树中最大的合法子树大小。

两者都包含整棵树合法的情况。

记前者为 $f_i$，后者为 $g_i$。

$f_i$ 可以直接 dp；考虑子树和自身合法的情况。略了。

$g_i$ 就有些麻烦了。如何统计到反方向的所有子树？

我们采用这样一种做法：考虑所有祖先（包括自己）整棵树的补树，和祖先的所有兄弟子树的子树。

画个图就明白了。

然后，我们需要考虑一个点兄弟的 $f_u$ 值 $\max$。

这个可以对所有兄弟指定顺序后求前缀后缀 $\max$ 得到。

然后，从根结点向下递推，即可推出 $g_v$。

时空复杂度 $\mathcal O(n)$。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <vector>
#include <ctime>

const int N = 400001;
typedef std::vector <int>::iterator it;

char buf[1 << 25] ,*p1 = buf ,*p2 = buf;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf ,1 ,1 << 21 ,stdin) ,p1 == p2) ? EOF : *p1++)
inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while(ch > '9' || ch < '0') { if(ch == '-') f = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

int n,f[N],sz[N],p[N],q[N],mx[N],mxt[N],g[N];
std::vector <int> vec[N];

void Dfs(int v,int fa) {
    sz[v] = 1;
    int l = vec[v].size();
    for(it i = vec[v].begin();i != vec[v].end();i++)
        if(*i == fa) { vec[v].erase(i); break; }
    l = vec[v].size();
    for(int i = 0;i < l;i++) {
        int u = vec[v][i];
        Dfs(u,v), sz[v] += sz[u];
    }
    for(int i = 0;i < l;i++) p[i] = q[i] = 0;
    for(int i = 0;i < l;i++) {
        int u = vec[v][i];
        if(mx[v] < sz[u]) mx[v] = sz[u], mxt[v] = u;
        if(i > 0) p[i] = p[i - 1];
        p[i] = std::max(p[i],f[u]);
    }
    if(mx[v] < n - sz[v]) mx[v] = n - sz[v], mxt[v] = -1;
    
    for(int i = l - 1;i >= 0;i--) {
        int u = vec[v][i];
        if(i < l - 1) q[i] = q[i + 1];
        q[i] = std::max(q[i],f[u]);
    }
    for(int i = 0;i < l;i++) {
        int u = vec[v][i];
        if(i > 0) g[u] = std::max(g[u],p[i - 1]);
        if(i < l - 1) g[u] = std::max(g[u],q[i + 1]);
    }
    if(n - sz[v] <= n / 2) g[v] = std::max(g[v],n - sz[v]);
    f[v] = l ? q[0] : 0;
    if(sz[v] <= n / 2) f[v] = std::max(f[v],sz[v]);
    return;
}

int ans[N];

void Dfs1(int v) {
    if(mxt[v] == -1) { if(mx[v] - g[v] <= n / 2) ans[v] = true; }
    else if(mx[v] - f[mxt[v]] <= n / 2) ans[v] = true;
    for(int i = 0;i < (int)vec[v].size();i++) {
        int u = vec[v][i];
        g[u] = std::max(g[u],g[v]);
        Dfs1(u);
    }
    return;
}

int main() {
    n = read();
    for(int i = 1;i < n;i++) {
        int v = read(), u = read();
        vec[v].push_back(u);
        vec[u].push_back(v);
    }
    Dfs(1,0);
    Dfs1(1);
    for(int i = 1;i <= n;i++) std::printf("%d ",ans[i]);
    std::puts("");
    return 0;
}

```

---

## 作者：devout (赞：1)

这里提供一种3次（5次）$dfs$的方法

首先考虑我们切开一刀的情况

显然，对于一个点，我们令这个点为根的时候，我们就要在这个点的所有连边中$siz$最大的地方切，切到这个$siz\leq\frac{n}{2}$，那么切下来的部分呢？直接接到这个点显然更优

那切下来多少呢？我们考虑切下来的大小只要$\leq\frac{n}{2}$随便怎么切都可以

所以思路就是维护每个点为根的时候，能够切下来的最大的大小不超过$\frac{n}{2}$的子树是多少

那么就是一个换根$dp$问题了，但是在我们任意指定根节点的时候，$dfs$到某个点，我们要求的既可能在他子树中，也可能在另一部分

有一种解决方案就是楼上的分类讨论

不想分类讨论怎么办？

我们求一下树的重心，那么这样的话我们要求的部分一定都不在他的子树当中，这个时候我们再维护就很好维护了

我们首先维护$f_i$表示在以$i$为根节点子树中的最大值，$g_i$表示在以$i$为根节点子树中的次大值（换根$dp$套路了）

那么怎么计算能够切下来的最大的大小不超过$\frac{n}{2}$的子树这个东西$h_i$呢？

我们可以列出这样一个转移方程

$$h_v=
\begin{cases}
\max(h_u,f_i),siz_v\neq f_i \\
\max(h_u,g_i),siz_v=f_i
\end{cases}$$

然后对于每一个点$i$，如果$n-siz_i-h_i\leq \frac{n}{2}$，就是$true$，否则是$false$

但是注意一棵树最多可能拥有两个重心，所以在有两个重心时我们需要分别令这两个重心为根，最后把答案或以下就好了

****

也就是说，我们需要进行三次$dfs$,$dfs1$求出重心，对于每一个重心，我们再进行两次$dfs$,$dfs2$预处理出当前重心为根时的$siz,f,g$，$dfs3$进行换根$dp$，然后把两个重心为根的答案或起来

复杂度$O(n)$

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=4e5+5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n;
int head[N],cnt;
int f[N],g[N],h[N],siz[N];
int cen1,cen2,sizmin=1e9;
bool out[N];

struct Edge{
    int to,next;
}e[N<<1];

void add(int x,int y){
    e[++cnt]=(Edge){y,head[x]},head[x]=cnt;
}

void dfs1(int u,int fa){
    siz[u]=1;
    RepG(i,u){
        int v=e[i].to;
        if(v==fa)continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        f[u]=max(f[u],siz[v]);
    }
    f[u]=max(f[u],n-siz[u]);
}

void dfs2(int u,int fa){
    siz[u]=1;
    RepG(i,u){
        int v=e[i].to;
        if(v==fa)continue;
        dfs2(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[f[u]])g[u]=f[u],f[u]=v;
        else if(siz[v]>siz[g[u]])g[u]=v;
    }
}

void dfs3(int u,int fa){
    out[u]|=(n-siz[u]-h[u]<=n/2);
    RepG(i,u){
        int v=e[i].to;
        if(v==fa)continue;
        if(v==f[u])h[v]=max(h[u],siz[g[u]]);
        else h[v]=max(h[u],siz[f[u]]);
        dfs3(v,u);
    }
}

int main()
{
    memset(head,-1,sizeof(head));
    read(n);
    Rep(i,1,n-1){
        int x,y;
        read(x),read(y);
        add(x,y),add(y,x);
    }
    if(n==1)return puts("1 1"),0;
    dfs1(1,0);
    Rep(i,1,n)
        if(f[i]<sizmin){
            sizmin=f[i];
            cen1=i,cen2=0;
        }
        else if(f[i]==sizmin)cen2=i;
    memset(f,0,sizeof(f));
    dfs2(cen1,0);
    out[cen1]=true;
    RepG(i,cen1){
        int v=e[i].to;
        if(v==f[cen1])h[v]=max(h[cen1],siz[g[cen1]]);
        else h[v]=max(h[cen1],siz[f[cen1]]);
        dfs3(v,cen1);
    }
    if(cen2){
        memset(f,0,sizeof(f));
        memset(g,0,sizeof(g));
        memset(h,0,sizeof(h));
        dfs2(cen2,0);
        out[cen2]=true;
        RepG(i,cen2){
            int v=e[i].to;
            if(v==f[cen2])h[v]=max(h[cen2],siz[g[cen2]]);
            else h[v]=max(h[cen2],siz[f[cen2]]);
            dfs3(v,cen2);
        }
    }
    Rep(i,1,n)printf("%d ",out[i]);
    puts("");
    return 0;
}
```


---

