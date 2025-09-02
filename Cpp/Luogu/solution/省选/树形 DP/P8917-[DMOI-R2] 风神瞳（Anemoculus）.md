# [DMOI-R2] 风神瞳（Anemoculus）

## 题目背景

![](https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fi1.hdslb.com%2Fbfs%2Farchive%2F778e646138c05348a05fc8a5d646201c0be048b0.jpg&refer=http%3A%2F%2Fi1.hdslb.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1665222406&t=01eff8edc99fbecc5e2e94e6e4b8fd01)

$$\pmb{\color{Aquamarine}『传说，飞鸟啄去了神像的眼瞳，然后散落到世界各地』}$$

$$\pmb{\color{Aquamarine}『当然了，这只是传说而已』}$$

$$\pmb{\color{Aquamarine}『不过，据说把散失的神瞳献给神像，会有好事发生呢』}$$

## 题目描述

风起地有一颗大树，它有 $n$ 个节点，以 $1$ 号节点为根。

树上有 $m$ 个风神瞳，第 $i$ 个风神瞳位于节点 $a_i$ 上。

你想要收集这些风神瞳。于是请来了~~在大树旁边摸鱼的~~温迪帮忙。

一开始，你在树的根部的节点，也就是 $1$ 号节点上，每一秒钟，你可以从当前节点走到相邻的节点。或者，你可以请温迪帮忙，他会生成一个风场，你可以通过这个风场直接一次性向上走正好 $k$ 步（我们定义根节点到叶子结点的方向为『上』，即从深度较小的节点到深度较大的节点，换句话说，你可以从当前节点朝着深度更大的节点连续走 $k$ 步）。当你到达某个有风神瞳的节点上时，你就可以收集那个节点的风神瞳，收集不耗费时间。由于从树上跳下来会摔伤，你最后必须回到根节点。现在你有 $q$ 个问题，第 $i$ 个问题是你在 $t_i$ 秒内你最多可以收集到几个风神瞳。

## 说明/提示

---
### 样例解释
#### 样例一
![](https://cdn.luogu.com.cn/upload/image_hosting/mz5mcnuo.png)

如图，其中加粗的点是有风神瞳的点。温迪~~很懒~~有事所以不准备帮你。
#### 样例二
这个样例除了温迪能让你一次性向上走两步和样例一没有区别。

---
### 数据范围

本题采用捆绑测试。

对于 $5\%$ 的数据，$m = 10$。

对于另外 $15\%$ 的数据，$m = 17$。

对于另外 $20\%$ 的数据，$k=1$。

对于 $100\%$ 的数据，$n \leq 2000$，$m \leq 500$，$q \le 1000$，$1\leq t_i \leq 2\times n$，$1\le a_i,u,v \le n$，$1 \leq k\le \min(dep-1,100)$，其中 $dep$ 表示树的深度，定义根节点的深度为 $1$。

## 样例 #1

### 输入

```
8 3 1 6
1 2
1 3
1 6
2 4
2 5
3 7
3 8
6 7 8
1
3
5
6
7
8```

### 输出

```
0
1
1
2
2
3```

## 样例 #2

### 输入

```
8 3 2 6
1 2
1 3
1 6
2 4
2 5
3 7
3 8
6 7 8
1
3
5
6
7
8```

### 输出

```
0
1
2
2
3
3```

# 题解

## 作者：andychen_2012 (赞：9)

# 风神瞳（Aeolus Hitomi）官方题解
## PART 0：一些闲话
这道题目是出题人在数学课上想出来的。

当时老师在讲函数换元的解题思想。

看我开小差就叫我起来回答问题。

然后我直接说成换根……

~~世界，遗忘了我。~~

## PART 1：题目大意
给定一棵以 $1$ 为根的，$n$ 个结点的树，其中有 $m$ 个特殊结点。初始时你在 $1$ 号结点，每一秒钟你可以走到一个与当前结点相邻的结点或者是连续向深度更大的结点走 $k$ 步，要求在 $t$ 秒钟之内，你最多能够到达多少个特殊结点（同一个特殊结点只在第一次到达时会被计算），并在 $t$ 秒时回到 $1$ 号结点。**多组询问。**

## PART 2：解题思路

数据范围非常壮观，出题人这样做一定有他的~~大病~~道理的。

### Solution 1, 20 pts
$k \le 1$，说明第二种操作是用不到的。那么就变成了一个较为简单的树上背包问题。

我们设 $dp_{i,j}$ 表示从 $i$ 出发，只管 $i$ 的子树，并最后回到 $i$，总共经过了 $j$ 个特殊结点的最短时间。

那么有方程：

$$
dp_{u,j} = \min_{v \in son(u)}\{dp_{v,k} + dp_{u,j - k} + 2\}
$$

其中 $son(u)$ 代表 $u$ 结点的儿子的集合。其中比较难以理解的可能是加上的 $2$，其实也很简单，就是先从 $u$ 走到 $v$，接着在 $v$ 的子树上走并回到 $v$，最后再从 $v$ 回到 $u$。其中“在 $v$ 的子树上走”所需要的时间就是 $dp_{v,k}$，而加上的 $2$ 就是从 $u$ 走到 $v$ 再从 $v$ 回到 $u$ 这里消耗的两秒。

由于答案显然具有单调性，即 $u$ 一定时，若 $j$ 增加，$dp_{u,j}$ 的值单调不减。所以询问时直接在 $dp_{1,i}$ 上二分。

**以上来自出题人。**

### Solution 2, 20 pts

设 $f_{u,i,j}$ 表示在节点 $u$ 去除掉子树 $j$ 的子树中选择 $i$ 个关键点所花费的最短时间，$j=0$ 则表示不去除。设 $g_{u,i}$ 表示在节点 $u$ 的父亲到根节点 $1$ 的路径上任取一个点及其子树剖去 $u$ 的子树部分中选择 $i$ 个关键点所花费的最短时间。设 $w_u$ 表示 $u$ 到根节点 $1$ 路径上的关键点个数，用于前缀和计算。设 $ans_{u,i}$ 表示上下两部分都取，一共取到 $i$ 个关键点，所花费的最短时间。

第一次 dfs 先处理出 $f$ 和 $w$ 的所有信息，第二次 dfs 利用 $f$ 和 $w$ 求解 $g$，最后综合 $f_{u,i,0}$ 和 $g_{u,i}$ 求解 $ans$。

时间复杂度 $O(n^2m)$。

**以上来自 Cidoai(andychen_2012)。**

### Solution 3, 100 pts

我们将风神瞳所在的节点称为关键点，用 $tg$ 记录，如果 $tg_u=1$，则 $u$ 为关键点。

$dep_x$ 表示 $x$ 到 $1$ 的距离，也可以说是 $1$ 深度为 $0$ 时 $x$ 的深度，$tot_x$ 表示 $x$ 的子树内现有的关键点数量。

$tran$ 和 $tmp$ 是两个辅助 dp 转移的数组。

$dp_{i,j,w}$ 表示在 $i$ 号点，选择了子树内 $j$ 个关键点，在风中还有 $w$ 步落地的子树内最优方案的时间。注意如果 $w=0$ 则目前正在目标上。

我们可以很明显地得出当 $u$ 为关键点时，$dp_{u,1,0}=0$，否则 $dp_{u,0,0}=0$。$dp$ 中其余所有值全部赋为 $\inf$。

我们的想法是从下往上 dp，逐个合并子树。

我们的 dfs 主要转移的是当前节点 $u$，然后对当前枚举的儿子节点设为 $v$。

我们的 $tran$ 主要是用来借助判断借风场起飞所能缩短的时间，在每次合并一个新的子树时，对于子树中的 $tot_v$ 个关键点都要重新存储一遍，也即
$$
\text{for i=0 to tot[v]:}\\
\ \ \ \ \text{for j=1 to k-1:}\\
\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ tran_j=dp_{v,i,j-1}
$$
注意到 $tran_0=dp_{v,j,0}+2$，因为这时处理的是已经落地的情况，因此还需要算上从 $u$ 到 $v$ 走的 $1s$，再从 $v$ 走 $dp_{v,j,0}$ 回到 $v$，再从 $v$ 走回 $u$ 花费 $1s$。

我们要处理从 $u$ 节点起飞的情况。注意其实如果往上爬一段起飞也包含在这个情况里。$k+1$ 是总代价，因为你要爬上去，飞过 $k$ 个点再爬回来。爬回来的费用提前计算了。那么这样所花费的时间为 $dp_{v,j,k-1-w}+k+1$，其中 $j=0 \sim tot_v,w=0 \sim \min(dep_u,k-1)$。

注意到如果此刻 $j=0$，则说明没有选择子树 $v$ 中的任何关键点，因此此时 $tran_0$ 要被重新赋值为 $0$。

我们接下来考虑子树合并的转移方程。因为你考虑当前 $dp_{i,j,w}$ 的 $w$ 这个飞行距离只能用于一个子树，所以可以像下面这样转移：$tmp_{j+w,t}=\min(tmp_{j+w,t},dp_{u,w,t}+tran_0,dp_{u,w,0}+tran_t)$

$dp_{u,w,t}+tran_0$ 是以前的子树用掉了飞行距离。$dp_{u,w,0}+tran_t$ 是现在的子树用掉了。$t$ 要从 $0$ 枚举到 $k-1$。

最后将 $tmp$ 里的东西赋值回 $dp$，然后将子树 $v$ 的关键点数加入 $u$ 的子树中即可。

时间复杂度 $O(nmk)$。

**以上来自 LHQing**。

## PART 3：解题代码

```cpp
#include<cstdio>
typedef long long ll;
inline ll read(){
	ll x=0;
	int ch=getchar(),f=0;
	while(ch<48||ch>57) f=(ch=='-'),ch=getchar();
	while(ch>47&&ch<58) x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return f?-x:x;
}
inline void write(int x,char end='\n'){
	if(x==0){
		putchar('0');
		putchar(end);
		return;
	}
	if(x<0) putchar('-'),x=-x;
	int st[70],sr=0;
	while(x){
		st[sr++]=x%10;
		x/=10;
	}
	while(sr--) putchar(st[sr]+48);
	putchar(end);
	return;
}
struct node{
	int to,nxt;
}e[4005];
int head[2005],cnt;
inline void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
int n,m,k,q;
int tg[2005],ans[4005];
int dep[2005];
int dp[2005][505][105];
int tot[2005],tran[105];
int tmp[505][105];
inline int min(int x,int y){return x<y?x:y;}
inline void dfs(int u,int f){
	if(tg[u]){
		tot[u]=1;
		dp[u][1][0]=0;
	}
	else{
		tot[u]=0;
		dp[u][0][0]=0;
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==f) continue;
		dep[v]=dep[u]+1;
		dfs(v,u);
		for(int j=0;j<=tot[u]+tot[v];++j)
			for(int w=0;w<=k;++w)
				tmp[j][w]=1000000;
		for(int j=0;j<=tot[v];++j){
			for(int w=0;w<=k;++w) tran[w]=1000000;
			tran[0]=dp[v][j][0]+2;
			for(int w=1;w<=k-1;++w) tran[w]=dp[v][j][w-1];
			for(int w=0;w<=dep[u]&&w<=k-1;++w)
				tran[0]=min(tran[0],dp[v][j][k-1-w]+k+1);
			if(j==0) tran[0]=0;
			for(int w=0;w<=tot[u];++w)
				for(int t=0;t<k;++t)
					tmp[j+w][t]=min(tmp[j+w][t],min(dp[u][w][t]+tran[0],dp[u][w][0]+tran[t]));
		}
		for(int j=0;j<=tot[u]+tot[v];++j)
			for(int w=0;w<k;++w)
				dp[u][j][w]=tmp[j][w];
		tot[u]+=tot[v];
	}
}
int main(){
	n=read(),m=read(),k=read(),q=read();
	for(int i=1,u,v;i<n;++i){
		u=read(),v=read();
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=m;++i){
		int u=read();
		tg[u]=1;
	}
	for(int i=1;i<=n;++i)
		for(int j=0;j<=m;++j)
			for(int w=0;w<=k;++w)
				dp[i][j][w]=1000000;
	dfs(1,0);
	for(int i=1;i<=m;++i)
		for(int j=dp[1][i][0];j<=2*n;++j)
			ans[j]=i;
	while(q--){
		ll x=read();
		if(x>=2*n){
			write(m);
			continue;
		}
		write(ans[x]);
	}
	return 0;
}
```



---

## 作者：Liveddd (赞：7)

~~比较裸的树上背包~~。

最需要处理的就是向叶子节点连续跳 $k$ 步。设计状态 $f_{x,t,i}$ 为从 $x$ 还需要向叶子节点跳 $t$ 步并且收集 $i$ 个风神瞳最少花费。

考虑如何转移。因为这 $t$ 步只能跳一次，转移过程中我们令 $f_{x,t,i}$ 已经使用了这 $t$ 步。而对于子节点 $y$：

1.在 $y$ 上跳这 $t$ 步，那么相当于 $x$ 在之前的子树上需要跳 $0$ 步：$f_{x,t,i}\gets f_{x,0,i-j}+f_{y,t-1,j}+1$。

2.在之前的子树上跳了这 $t$ 步，那么相当 $x$ 在 $y$ 上需要跳 $0$ 步。而我们可以选择直接走到 $y$，或者先向上走 $\le \min \{dep_x-1,k\}$ 步，再向叶子结点跳 $k$ 步：

$f_{x,t,i}\gets f_{x,t,i-j}+ \min \{f_{y,0,j}+2,\min_{p=\max \{k-dep_x+1,1\}}^{k}{k-p+1+f_{y,p-1,j}+1 \}}$。

后面的式子是一个整体，拿出来单独计算即可。

对于 $t=0$ 单独处理，类似上面的转移。时间复杂度 $\mathcal O(nmk)$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=2e3+10,M=5e2+10,K=1e2+10,INF=1e9;
template<class T>
inline void read(T &x)
{
    x=0;int f=0; 
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    if(f)x=~x+1;
}
template<class T,class ...T1>
inline void read(T &x,T1 &...x1)
{
    read(x),read(x1...);
}
int n,m,p,q;
int tot,head[N],ver[N<<1],ne[N<<1];
int a[N],si[N],d[N];
int f[N][K][M],ans[N<<1];
inline void add(int u,int v)
{
    ver[++tot]=v;
    ne[tot]=head[u];
    head[u]=tot;
}
void dfs(int x,int fa)
{
    si[x]=a[x];
    f[x][0][a[x]]=0;
    for(int i=head[x];i;i=ne[i])
    {
        int y=ver[i];
        if(y==fa)continue;
        d[y]=d[x]+1;
        dfs(y,x);
        for(int j=si[x]+si[y];~j;j--)
            for(int k=max(j-si[x],0);k<=si[y];k++)
            {
                int res=INF;
                for(int t=max(p-d[x],1);t<=p;t++)
                    res=min(res,(p-t+1)+f[y][t-1][k]+1);
                res=min(res,f[y][0][k]+2);
                for(int t=1;t<=p-1;t++)
                    f[x][t][j]=min({f[x][t][j],f[x][0][j-k]+1+f[y][t-1][k],f[x][t][j-k]+res});
                f[x][0][j]=min(f[x][0][j],f[x][0][j-k]+res);
            }
        si[x]+=si[y];
    }
}
int main()
{
    read(n,m,p,q);
    for(int i=1;i<n;i++)
    {
        int u,v;
        read(u,v);
        add(u,v),add(v,u);
    }
    for(int i=1;i<=m;i++)
    {
        int x;
        read(x);
        a[x]=1;
    }
    memset(f,0x3f,sizeof(f));    
    dfs(1,0);
    f[1][0][m+1]=2*n;
    for(int i=0;i<=m;i++)
        for(int j=f[1][0][i];j<f[1][0][i+1];j++)
            ans[j]=i;
    while(q--)
    {
        int x;
        read(x);
        if(x>=2*n)
        {
            printf("%d\n",m);
            continue;
        }
        printf("%d\n",ans[x]);
    }
    return 0;
}
```

---

