# [CEOI 2017] Chase

## 题目描述

在逃亡者的面前有一个迷宫，这个迷宫由 $n$ 个房间和 $n-1$ 条双向走廊构成，每条走廊会链接不同的两个房间，所有的房间都可以通过走廊互相到达。换句话说，这是一棵树。

逃亡者会选择一个房间进入迷宫，走过若干条走廊并走出迷宫，但他永远不会走重复的走廊。

在第 $i$ 个房间里，有 $F_i$​​ 个铁球，每当一个人经过这个房间时，他就会受到铁球的阻挡。逃亡者手里有 $V$ 个磁铁，当他到达一个房间时，他可以选择丢下一个磁铁（也可以不丢），将与这个房间相邻的所有房间里的铁球吸引到这个房间。这个过程如下：

1.    逃亡者进入房间。
2.    逃亡者丢下磁铁。
3.    逃亡者走出房间。
4.    铁球被吸引到这个房间。

注意逃亡者只会受到这个房间原有的铁球的阻拦，而不会受到被吸引的铁球的阻挡。

在逃亡者走出迷宫后，追逐者将会沿着逃亡者走过的路径穿过迷宫，他会碰到这条路径上所有的铁球。

请帮助逃亡者选择一条路径，使得追逐者遇到的铁球数量减去逃亡者遇到的铁球数量最大化。


## 说明/提示

**样例解释**

有一个最优方案如下：

-    从 $6$ 号房间进入迷宫并丢下第一个磁铁，他遇到了 $5$ 个铁球，这个时候 $6$ 号房间会有 $27$ 个铁球，而 $5$ 号，$7$ 号，$8$ 号，$9$ 号房间都没有铁球。
-    走到 $7$ 号房间丢下第二个磁铁并走出迷宫，他遇到了 $0$ 个铁球，这个时候 $7$ 号房间会有 $41$ 个铁球，而 $2$ 号，$4$ 号，$6$ 号，$10$ 号房间会没有铁球。

在这个过程中，逃亡者会遇到 $5$ 个铁球而追逐者会遇到 $41$ 个铁球。

**数据范围**

对于 $100\%$ 的数据，有 $1\le n\le 10^5;0\le V\le 100;0\le F_i\le 10^9$​​。

## 样例 #1

### 输入

```
12 2
2 3 3 8 1 5 6 7 8 3 5 4
2 1
2 7
3 4
4 7
7 6
5 6
6 8
6 9
7 10
10 11
10 12```

### 输出

```
36```

# 题解

## 作者：zero4338 (赞：44)

## Solution
当我们固定一个起点后 , 把起点作为整个树的根 , 那么这时每个节点选不选的价值就是它所有儿子的铁球数量加和 .  
那么设 $f_{i,j}$ 表示在 $i$ 子树里选择了 $j$ 个点所能得到的最大贡献 , 转移时考虑这个节点是否选择 .  
设 $son_i$ 表示 $i$ 节点的儿子 , $v_i$ 表示 $i$ 节点的所有儿子铁球数量和 .
$f_{i,j}=\max(f_{son_i,j},f_{son_i,j-1}+v_i)$
枚举起点作为根 , 复杂度 $O(n^2v)$.  
不能通过本题 ,  
考虑沿用上面对价值的定义 , 设计新的 dp,  
设 $f_{i,j,0/1},g_{i,j,0/1}$ 分别表示从 $i$($i$的子树)走到 $i$ 的子树($i$)中 , $i$ 被/不被)选 , 选了 $j$ 个的最大贡献 .  
设当前节点为 $u$ , 儿子为 $son$, 父亲为 $fa$ , 当前节点儿子权值和为 $v$ , 点 $i$ 的铁球数量为 $p_i$.  
那么有转移  
$f_{u,j,0}=\max(f_{son,j,0},f_{son,j,1})$  
$f_{u,j,1}=\max(\max(f_{son,j-1,0},f_{son,j-1,1})+v)$  
$g_{u,j,0}=\max(g_{son,j,0},g_{son,j,1})$  
$g_{u,j,1}=\max(\max(g_{son,j-1,0},g_{son,j-1,1})+v+p_{fa}-p_{son})$  
注意路径方向的不同导致的价值变化 .  
还要考虑 $u$  自己作为起点 ,  
即 $g_{u,1,1}=\max(v+p_{fa})$  
但直接使用一个点的 $f$ 和 $g$ 去更新答案 , 无法保证路径不重复 ,  
那么考虑在合并子树时更新答案 ,
$ans=\max(\max(f_{son,j,0},f_{son,j,1})+\max(g_{u,k,0},g_{u,k,1}))$  
$ans=\max(\max(g_{son,j,0},g_{son,j,1})+\max(f_{u,k,0},f_{u,k,1}+p_{fa}-p_{son}))$  
注意这里 $f,g$ 是由之前的全部儿子转移而来 , 所以能够保证路径不重复 .
注意由于 $f_{u,0,1},g_{u,0,1}$ 不合法 , 强制赋值负无穷 .  
上式的 $j+k\leq v$ , 如果枚举 $j,k$ 会有 $O(v^2)$ 的复杂度 , 实际上只需维护前缀最大值就可做到 $O(v)$ 转移 .  
时间复杂度 $O(nv)$
## Code
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#define ll long long
using namespace std;
int read()
{
    int ret=0;char c=getchar();
    while(c>'9'||c<'0')c=getchar();
    while(c>='0'&&c<='9')ret=(ret<<3)+(ret<<1)+(c^48),c=getchar();
    return ret;
}
const int maxn=1e5+5;
const int maxm=105;
const ll inf=1e15;
int n,v;
ll ans;
struct graph
{
    int p[maxn];ll val[maxn];
    int head[maxn],ver[maxn<<1],nxt[maxn<<1],tot;
    void add(int x,int y){ver[++tot]=y;nxt[tot]=head[x];head[x]=tot;}
    void link(int x,int y){add(x,y);add(y,x);}
    ll f[maxn][maxm][2],g[maxn][maxm][2];
    void dfs(int u,int fa)
    {
        val[u]=0;
        for(int i=head[u];i;i=nxt[i])
        {
            if(ver[i]==fa)continue;
            dfs(ver[i],u);val[u]+=p[ver[i]];
        }
        f[u][0][1]=g[u][0][1]=-inf;
        g[u][1][1]=max(g[u][1][1],val[u]+p[fa]);
        for(int i=head[u];i;i=nxt[i])
        {
            if(ver[i]==fa)continue;
            ll mx1=0,mx2=0;
            for(int j=v;j>=0;j--)
            {
                mx1=max(mx1,max(g[u][v-j][0],g[u][v-j][1]));
                mx2=max(mx2,max(f[u][v-j][0],f[u][v-j][1]+p[fa]-p[ver[i]]));
                ans=max(ans,max(f[ver[i]][j][0],f[ver[i]][j][1])+mx1);
                ans=max(ans,max(g[ver[i]][j][0],g[ver[i]][j][1])+mx2);
            }
            for(int j=1;j<=v;j++)
                f[u][j][0]=max(f[u][j][0],max(f[ver[i]][j][0],f[ver[i]][j][1])),f[u][j][1]=max(f[u][j][1],max(f[ver[i]][j-1][0],f[ver[i]][j-1][1])+val[u]);
            for(int j=1;j<=v;j++)
                g[u][j][0]=max(g[u][j][0],max(g[ver[i]][j][0],g[ver[i]][j][1])),g[u][j][1]=max(g[u][j][1],max(g[ver[i]][j-1][0],g[ver[i]][j-1][1])+val[u]+p[fa]-p[ver[i]]);
        }
    }
}o;
int main()
{
    n=read();v=read();
    for(int i=1;i<=n;i++)o.p[i]=read();
    for(int i=1;i<=n-1;i++)o.link(read(),read());
    o.dfs(1,0);
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Chen_jr (赞：20)

比较经典的树形 $DP$

如果我们确定了起点，那么每个点被选中他的贡献就是 $\sum_{v \in son} f_v$

于是我们就有了 $n^2$ 爆力

$dp_{i, j, 1 / 0}$ 表示以 $i$ 为根的子树中的链，使用了 $j$ 个磁铁， $i$ 放 / 没放磁铁

转移的话对其子树的贡献取 $max$ 贡献到 $dp_{i, j, 0}$

由 $dp_{i, j , 0}$ 贡献到 $dp_{i, j + 1, 1}$

考虑优化这个过程，考场上我有两种思路

1. 考虑 $dp$ 出一条向上的链， 在 $lca$ 处拼接

但是这样做的话比较麻烦，需要记录的状态比较多，合并时比较难搞

于是有了另一种思路

2. 换根 $dp$

这个就比较好搞了

换根时只会影响到 $x , fa_x$

考虑在 $fa_x$ 位置修改他的 $dp$ 值，使他作为 $x$ 的子树进行贡献

这个其实比较套路，因为发现其实就是扣掉 $x$ 作为他的儿子的贡献，那么我们对转移过程维护一个最大值， 一个与最大值不同子树的次大值，那么只要不取到最大值来源的子树, 其 $dp$ 值仍然为最大值，否则为次大值


```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
inline int read(){
    int x = 0; char c = getchar();
    while(c < '0' || c > '9')c = getchar();
	do{x = (x << 3) + (x << 1) + (c ^ 48); c = getchar();}while(c <= '9' && c >= '0');
	return x;   
}
const int maxn = 1e5 + 55;
int n, sum, f[maxn], head[maxn], tot, root;
struct edge{
	int to, net;
}e[maxn << 1 | 1];
void add(int u, int v){
	e[++tot].net = head[u];
	head[u] = tot;
	e[tot].to = v;
}
ll ans;
ll tmp[maxn][105][2], g[maxn];
void solve(int x, int fa){
	g[x] = 0;
	for(int i = 1; i <= sum; ++i)tmp[x][i][0] = 0;
	for(int i = head[x]; i; i = e[i].net){
		int v = e[i].to;
		if(v == fa)continue;
		g[x] += f[v];
		solve(v, x);
		for(int j = 1; j <= sum; ++j)tmp[x][j][0] = max(tmp[x][j][0], max(tmp[v][j][1], tmp[v][j][0]));
	}
	for(int i = sum; i >= 1; --i)tmp[x][i][1] = tmp[x][i - 1][0] + g[x];
}
int rmx[maxn][105];
ll  rval[maxn][105], rcm[maxn][105];
void ch(int x, int fa){
	for(int j = 1; j <= sum; ++j)tmp[x][j][0] = max(tmp[x][j][0] ,max(tmp[fa][j][0], tmp[fa][j][1]));
	for(int j = 1; j <= sum; ++j)tmp[x][j][1] = tmp[x][j - 1][0] + g[x] + f[fa];
	ans = max(ans, max(tmp[x][sum][0], tmp[x][sum][1]));
	for(int j = 1; j <= sum; ++j)tmp[x][j][0] = max(tmp[fa][j][0], tmp[fa][j][1]);
	for(int j = head[x]; j; j = e[j].net){
		int v = e[j].to;
		for(int k = 1; k <= sum; ++k){
			ll val = 0;
			if(v == fa)val = max(tmp[fa][k][0], tmp[fa][k][1]);
			else val = max(tmp[v][k][0], tmp[v][k][1]);
			if(val > rval[x][k]){
				rcm[x][k] = rval[x][k];
				rval[x][k] = val;
				rmx[x][k] = v;
			}else rcm[x][k] = max(rcm[x][k], val);
		}
	}
	for(int i = head[x]; i; i = e[i].net){
		int v = e[i].to;
		if(v == fa)continue;
		for(int j = 1; j <= sum; ++j)tmp[x][j][0] = rmx[x][j] == v ? rcm[x][j] : rval[x][j];
		for(int j = 1; j <= sum; ++j)tmp[x][j][1] = tmp[x][j - 1][0] + g[x] - f[v] + f[fa];
		ch(v, x);	
	}
}
int main(){
	n = read(), sum = read();
	for(int i = 1; i <= n; ++i)f[i] = read();
	for(int i = 1; i < n; ++i){
		int u = read(), v = read();
		add(u, v); add(v, u);
	}
	if(n == 1 || sum == 0){
		printf("0\n");
		return 0;
	}
	if(n == 2){
		printf("%d\n",max(f[1], f[2]));
		return 0;
	}
	solve(1, 0);
	ch(1, 0);
	printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：ModestCoder_ (赞：19)

扔磁铁得到的收益有两种情况

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201130084550629.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01vZGVzdENvZGVyXw==,size_16,color_FFFFFF,t_70)

1. 我在起点，扔一个磁铁，周围的权值是收益，因为周围的那些铁块我肯定不会遇到，而追逐者肯定会遇到
2. 我从某一个点走过来，假设上一个点是红点，现在我在绿点，然后我扔了一个磁铁，我获得的收益是周围点的权值和减去红点的权值，因为我是经过了红点的，遇到过红点的铁块，而且追逐者也肯定会遇到

所以一条路径上，扔磁铁获得的收益有两种情况

而且我们可以发现，假如我从某一个点出发，一定要扔一个磁铁。或者说，**我扔第一个磁铁的地方，一定是出发点**

思考树形dp，遍历到某个点$u$的时候，计算如下图的最优值
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201130085304813.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01vZGVzdENvZGVyXw==,size_16,color_FFFFFF,t_70)

从$u$的子树中某点出发，往上走经过$u$，再走向子树中的某点

保证了**不重不漏**

所以我是钦定了从起点走到终点是先往上走再往下走，而这道题目，起点扔磁铁的贡献与中途某一点扔磁铁的贡献的计算方式是不同的。所以我设计状态的时候需要**着重考虑**

令

$a[u]$为该点权值

$s[u]$为与该点相邻的所有点权值和

$f[u][i]$表示从$u$的子树中出发往上走到$u$，共扔了$i$个磁铁的最优值

$g[u][i]$表示从$u$往下走到子树中某一点，共扔了$i$个磁铁的最优值

初始化$f[u][1]=s[u](u为起点)$

$g[u][1]=s[u]-a[pre](u为往下走的过程中的一个点)$

以$u$为中转点的答案统计

$ans=max(ans,f[u][i]+g[v][m-i])$

转移


$f[u][i]=max(f[u][i],f[v][i],f[v][i-1]+s[u]-a[v])$

$g[u][i]=max(g[u][i],g[v][i],g[v][i-1]+s[u]-a[pre])$

还发现其实我是从子树中选了两个方向，一个是来时的方向，一个是去向

因为方向不同，起点的贡献就不同，所以我还有倒着枚举儿子枚举一遍

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 100010
#define maxm 110
#define LL long long
using namespace std;
struct Edge{
	int to, next;
}edge[maxn << 1];
int num, head[maxn], n, m, stk[maxn];
LL a[maxn], s[maxn], f[maxn][maxm], g[maxn][maxm], ans;

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

void addedge(int x, int y){
	edge[++num] = (Edge){y, head[x]}, head[x] = num;
}

void dfs(int u, int pre){
	for (int i = 1; i <= m; ++i)
		f[u][i] = s[u], g[u][i] = s[u] - a[pre];
	for (int i = head[u]; i; i = edge[i].next){
		int v = edge[i].to;
		if (v == pre) continue;
		dfs(v, u);
		for (int j = 0; j <= m; ++j) ans = max(ans, f[u][j] + g[v][m - j]);
		for (int j = 1; j <= m; ++j){
			f[u][j] = max(f[u][j], max(f[v][j], f[v][j - 1] + s[u] - a[v]));
			g[u][j] = max(g[u][j], max(g[v][j], g[v][j - 1] + s[u] - a[pre]));
		}
	}
	for (int i = 1; i <= m; ++i)
		f[u][i] = s[u], g[u][i] = s[u] - a[pre];
	int top = 0;
	for (int i = head[u]; i; i = edge[i].next){
		int v = edge[i].to;
		if (v == pre) continue;
		stk[++top] = v;
	}
	while (top){
		int v = stk[top--];
		for (int j = 0; j <= m; ++j) ans = max(ans, f[u][j] + g[v][m - j]);
		for (int j = 1; j <= m; ++j){
			f[u][j] = max(f[u][j], max(f[v][j], f[v][j - 1] + s[u] - a[v]));
			g[u][j] = max(g[u][j], max(g[v][j], g[v][j - 1] + s[u] - a[pre]));
		}
	}
}

int main(){
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i < n; ++i){
		int x = read(), y = read();
		addedge(x, y), addedge(y, x);
		s[x] += a[y], s[y] += a[x];
	}
	dfs(1, 0);
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：ZZ作者 (赞：17)

一个比较直接的方法是直接换根 dp，题解里似乎没有……

朴素的 dp 设 $f[u][i]$ 为从根向 u 子树里走的最大贡献

转移时对两种情况取 max：

$$ f[v][i]\rightarrow f[u][i] $$
$$ f[v][i]+sum_v\rightarrow f[u][i+1] $$

其中 $sum_v$ 表示在确定根的前提下 v 的所有儿子权值之和

因为转移是取 max，所以换根时不能简单加减，而应对当前根算出每种转移所需值的最大/次大值，换根时判断所需值是否来自要换到的儿子，然后按方程转移即可，因为儿子变为根后当前根变为儿子，所以还需要算出当前根新的 dp 值

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){
	int f=0,s=0; char c=getchar();
	while(c>'9'||c<'0')f=(c=='-'),c=getchar();
	while(c>='0'&&c<='9')s=(s<<3)+(s<<1)+(c^'0'),c=getchar();
	return f?-s:s;
}

const int N=100005;
const int M=105;
int n,V;
int a[N];
int t1,t2;

const int E=200005;
int to[E],nx[E],h[N],tot=0;
inline void add(int a,int b){ to[++tot]=b; nx[tot]=h[a]; h[a]=tot; }
inline void link(int a,int b){ add(a,b); add(b,a); }
int f[N][M][2];
int ans=0;

const int inf=1e18;
int w[N];
void dfs1(int u,int fa){
	w[u]=0;
	for(int i=h[u];i;i=nx[i])if(to[i]!=fa&&to[i])dfs1(to[i],u),w[u]+=a[to[i]];
	for(int i=0;i<=V;i++)for(int j=0;j<2;j++)f[u][i][j]=-inf;
	f[u][0][0]=0; f[u][1][1]=w[u];
	for(int i=h[u];i;i=nx[i])if(to[i]!=fa&&to[i]){
		for(int j=0;j<=V;j++){
			int tmp=max(f[to[i]][j][0],f[to[i]][j][1]);
			f[u][j][0]=max(f[u][j][0],tmp);
			f[u][j+1][1]=max(f[u][j+1][1],tmp+w[u]);
		}
	}
}
int t[N][M][2][2];
void dfs2(int u,int fa){
	for(int i=0;i<=V;i++)ans=max(ans,max(f[u][i][0],f[u][i][1]));
	for(int i=0;i<=V;i++)for(int j=0;j<2;j++)t[u][i][j][0]=t[u][i][j][1]=-inf;
	for(int i=h[u];i;i=nx[i]){
		for(int j=0;j<=V;j++)for(int k=0;k<2;k++){
			if(f[to[i]][j][k]>t[u][j][k][0])swap(t[u][j][k][1],t[u][j][k][0]),t[u][j][k][0]=f[to[i]][j][k];
			else if(f[to[i]][j][k]>t[u][j][k][1])t[u][j][k][1]=f[to[i]][j][k];
		}
	}
	for(int i=h[u];i;i=nx[i])if(to[i]!=fa){
		w[to[i]]+=a[u];
		for(int j=V;j>=0;j--){
			int g0=-inf,g1=-inf;
			if(f[to[i]][j][0]==t[u][j][0][0])g0=max(g0,t[u][j][0][1]);
			else g0=max(g0,t[u][j][0][0]);
			if(f[to[i]][j][1]==t[u][j][1][0])g0=max(g0,t[u][j][1][1]);
			else g0=max(g0,t[u][j][1][0]);
			if(j){
				if(f[to[i]][j-1][0]==t[u][j-1][0][0])g1=max(g1,t[u][j-1][0][1]+w[u]-a[to[i]]);
				else g1=max(g1,t[u][j-1][0][0]+w[u]-a[to[i]]);
				if(f[to[i]][j-1][1]==t[u][j-1][1][0])g1=max(g1,t[u][j-1][1][1]+w[u]-a[to[i]]);
				else g1=max(g1,t[u][j-1][1][0]+w[u]-a[to[i]]);
			}
			if(j==1)g1=max(g1,w[u]-a[to[i]]);
			f[u][j][0]=g0; f[u][j][1]=g1;
			int tmp=max(g0,g1);
			f[to[i]][j][0]=max(f[to[i]][j][0],tmp);
			f[to[i]][j][1]+=a[u];
			if(j==0)f[to[i]][j][1]=-inf;
			f[to[i]][j+1][1]=max(f[to[i]][j+1][1],tmp+w[to[i]]);
		}
		dfs2(to[i],u);
	}
}

signed main(){
	n=read(); V=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++)t1=read(),t2=read(),link(t1,t2);
	dfs1(1,0); dfs2(1,0);
	printf("%lld",ans);
	return 0;
}
```

~~关于考场对原题用新做法写3.5h这事~~

---

## 作者：楠枫 (赞：9)

## 题解

首先，分析一下这个答案：本质上是求在一条路径上，选择了一些点，这些点的贡献是它周围的点权和 - 它上一步的点权

对于一棵树，可以先确定一个根，然后每条路径就可以分成向上和向下的两部分

那么定状态 $dp_{i,j,0}$ 表示由 $i$ 向 $i$ 的子树走，选了 $j$ 个点放磁铁，$dp_{i,j,1}$ 则表示向上走

那么转移方程就很好想
$$
dp_{i,j,0}=\max\{dp_{son\in son_i,j,0},dp_{son\in son_i,j-1,0}+sum_x-num_{son}\}
$$

$$
dp_{i,j,1}=\max\{dp_{son\in son_i,j,1},dp_{son\in son_i,j-1,1}+sum_x-num_{fa}\}
$$

这个方程就是由下往上转移，且对于一个放了的点，它上一个经过的点无法被它管到。

初始化时要把 $dp_{x,i,0}$ 都初始化为 $sum_x$，因为转移时可以是一个点加上一条向下的路径。

转移答案时要注意：对于一个节点的所有儿子要从前往后转移一遍，同时从后往前转移一遍，这样才能保证所有分支都有可能向下或向上。

还要在逆向转移之前恢复 $dp$ 数组原有状态。

```cpp
#include<bits/stdc++.h>
#define ri register signed
#define p(i) ++i
using namespace std;
namespace IO{
    char buf[1<<21],*p1=buf,*p2=buf;
    #define gc() p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++
    template<typename T>inline void read(T &x) {
        ri f=1;x=0;register char ch=gc();
        while(ch<'0'||ch>'9') {if (ch=='-') f=0;ch=gc();}
        while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+(ch^48);ch=gc();}
        x=f?x:-x;
    }
}
using IO::read;
namespace nanfeng{
    #define FI FILE *IN
    #define FO FILE *OUT
    template<typename T>inline T cmax(T x,T y) {return x>y?x:y;}
    template<typename T>inline T cmin(T x,T y) {return x>y?y:x;}
    typedef long long ll;
    static const int N=1e5+7;
    int first[N],nm[N],tmp[N],cnt,t=1,n,vn;
    struct edge{int v,nxt;}e[N<<1];
    inline void add(int u,int v) {
        e[t].v=v,e[t].nxt=first[u],first[u]=t++;
        e[t].v=u,e[t].nxt=first[v],first[v]=t++;
    }
    ll dp[N][107][2],ans,sum[N];
    inline void update(int x,int v,int fa) {
        for (ri i(1);i<vn;p(i)) ans=cmax(ans,dp[x][i][0]+dp[v][vn-i][1]);
        for (ri i(1);i<=vn;p(i)) {
            dp[x][i][0]=cmax(dp[x][i][0],cmax(dp[v][i][0],dp[v][i-1][0]+sum[x]-nm[v]));
            dp[x][i][1]=cmax(dp[x][i][1],cmax(dp[v][i][1],dp[v][i-1][1]+sum[x]-nm[fa]));
        }
    }
    void dfs(int x,int fa) {
        for (ri i(first[x]),v;i;i=e[i].nxt) {
            if ((v=e[i].v)==fa) continue;
            dfs(v,x);
        }
        for (ri i(1);i<=vn;p(i)) dp[x][i][0]=sum[x];
        cnt=0;
        for (ri i(first[x]);i;i=e[i].nxt) update(x,tmp[p(cnt)]=e[i].v,fa);
        for (ri i(1);i<=vn;p(i)) dp[x][i][0]=sum[x],dp[x][i][1]=0;
        for (ri i(cnt);i;--i) update(x,tmp[i],fa);
        ans=cmax(ans,cmax(dp[x][vn][1],dp[x][vn][0]));
    }
    inline int main() {
        // FI=freopen("nanfeng.in","r",stdin);
        // FO=freopen("nanfeng.out","w",stdout);
        // printf("cost = %d\n",sizeof(dp)>>20);
        read(n),read(vn);
        for (ri i(1);i<=n;p(i)) read(nm[i]);
        for (ri i(1),u,v;i<n;p(i)) {
            read(u),read(v);
            add(u,v);
        } 
        for (ri i(1);i<=n;p(i)) {
            for (ri j(first[i]),v;j;j=e[j].nxt) sum[i]+=nm[e[j].v];
        }
        dfs(1,0);
        printf("%lld\n",ans); 
        return 0;
    }  
}
int main() {return nanfeng::main();} 
```

---

## 作者：antiquality (赞：9)

本题主要有四种思路：

1.爆搜，时间复杂度$O(n^22^n)$；期望得分20pts。

2.贪心，时间复杂度$O(n^2vlogv)$；期望得分70pts。

3.浅层的动态规划，时间复杂度$O(n^2v)$；期望得分70pts。

4.深入地动态规划，时间复杂度$O(nv)$；期望得分100。

emm……既然你点进了题解大概是不会做吧。

本题挺好的还是自己多思考一下吧。

这里提供一句话题解帮助你大概明确一个思考的方向。

如果实在想不出来，[【动态规划】loj#2485. 「CEOI2017」Chase](https://www.cnblogs.com/antiquality/p/9503630.html)这里有详细的题解（我的博客）。



---

## 作者：pengyule (赞：6)

![image.png](https://i.loli.net/2021/11/17/45WTelN9C6LwyxK.png)

且看上图（示意图，不妨将 1 看成树根）。我们会发现在这条路径上，会有三种不同身份的点，分别如上图红、绿、蓝所示：绿点是起点，它的收益是 4,13,14,15 四个点上的铁球数；红点是往上走的点，它的收益是所有与它连接的点上的铁球数减去它的前一个点 3 上的铁球数，为什么要减去呢，因为 3 这个点上的铁球是两个人都会遇到的；蓝点是向下走的点，它的收益是它的儿子的铁球数总和，其实本质和红点是一样的，但是没有办法，一条路径上可能有向上走的也可能向下走，我们都需要考虑；那么 7 为什么要打阴影，就是 7 这个既可以算向上走又可以算向下走的点来把两段路径合并计入答案。

有了以上的分析，我们大致能想到这是一个树形 DP。

状态：$f_{i,j,0/1}(g_{i,j,0/1})$，$f(g)$ 表示从 $i$（$i$ 的儿子） 走到 $i$ 的儿子（$i$），把以 $i$ 为根的子树看成世界，半条路径的最大收益，$j$ 表示放多少个磁铁，$0/1$ 表示在 $i$ 放不放磁铁。

设儿子为 $son$，$i$ 的所有儿子铁球数之和为 $v$，$i$ 的父亲为 $p$，某点 $x$ 的父亲铁球数为 $a_x$。

最简单的：${f_{i,j,0}}^{\max}_{\longleftarrow}\max(f_{son,j,0},f_{son,j,1}),{g_{i,j,0}}^{\max}_{\longleftarrow}\max(g_{son,j,0},g_{son,j,1})$

第二简单的（是起点的情况）：$f_{i,1,1}=v+a_p$

继续得出

$$
{f_{i,j,1}}^{\max}_{\longleftarrow}\max(f_{son,j-1,0},f_{son,j-1,1})+v\\
{g_{i,j,1}}^{\max}_{\longleftarrow}\max(g_{son,j-1,1},g_{son,j-1,1})+v-a_{son}+a_p
$$

解释：$v$ 和 $v-a_{son}+a_p$ 都是表达”$i$ 周围的铁球数和减前一个点的铁球数“，只是由于路径方向不同而表达形式不同。



DP 一难点是边界，注意 $f_{i,0,1},g_{i,0,1}$ 是违法的，设成 $-\infin$。

知道如何递推，那怎么计算答案。为了保证不重复经过一条边我们考虑这样计算，对于将要用来更新 $f_{i,×,×}$的这个 $son$，我们在用它更新*之前*来计算一下由*当前的* $f(g)_{i,j_1,0/1}$ 和 $f(g)_{son,j_2,0/1}$（$\forall j_1+j_2\le v$）能不能更新答案 $ans$。

那么
$$
ans^{\max}_{\longleftarrow}\max(f_{i,j_1,0},f_{i,j_1,1}+a_p-a_{son})+\max(g_{son,j_2,0},g_{son,j_2,1}),\forall j_1+j_2\le v\\
ans^{\max}_{\longleftarrow}\max(g_{i,j_1,0},g_{i,j_1,1})+\max(f_{son,j_2,0},f_{son,j_2,1}),\forall j_1+j_2\le v
$$
解释：

1. 为什么要 $+a_p-a_{son}$。因为我们当初算 $f$ 的是候是当向下走来算的，默认了是从一个父亲节点走下来，那么现在这条路是↑到 $i$ 又↓，所以需要加上没有算完整的 $i$ 的收益 $a_p$，再减去原来算多的 $a_{son}$（因为现在是从 $son$ 走过来）。
2. 第一个式子是 $\swarrow i\nwarrow son$ 的情况，第二个式子是 $\nearrow i\searrow son$ 的情况。
3. 这一部分如果通过 $\forall0\le j_1\le v,0\le j_2\le v$ 的枚举实现复杂度 $O(v^2)$，难以承受。考虑倒序（从 $v$ 到 $0$）枚举 $j_2$，*实时*用 $f(g)_{i,j_1=v-j_2,×}$ 来更新记录 $\max f(g)_{i,j_1=0\to j_2,×}$ 的前缀最大值变量，既可以只通过 $O(v)$ 来解决。具体见代码。

据此已经解决了此题，总复杂度 $O(nv)$，是一道思维难度较大的树形 DP。

---

本篇题解参考 @zero4338 的题解，鸣谢

---

```cpp
#include <bits/stdc++.h>
#define int long long
//typedef long long ll;
using namespace std;
inline int read(){
	register char ch=getchar();register int x=0;
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
const int N=1e5+5,V=105;
int n,v,ans,a[N],f[N][V][2],g[N][V][2];
vector<int>G[N];
void dfs(int x,int p){
	f[x][0][1]=g[x][0][1]=-1e16;
	int sum=0;
	for(int i=0;i<G[x].size();i++){
		int y=G[x][i];
		if(y==p)continue;
		dfs(y,x);
		sum+=a[y];
	}
	g[x][1][1]=sum+a[p];
	for(int i=0;i<G[x].size();i++){
		int y=G[x][i];
		if(y==p)continue;
		int mxf=-1e16,mxg=-1e16;
		for(int j=v;j>=0;j--){
			mxf=max(mxf,max(f[x][v-j][0],f[x][v-j][1]+a[p]-a[y])),
			mxg=max(mxg,max(g[x][v-j][0],g[x][v-j][1]));
			ans=max(ans,mxg+max(f[y][j][0],f[y][j][1]));
			ans=max(ans,mxf+max(g[y][j][0],g[y][j][1]));
		}
		for(int j=1;j<=v;j++){
			f[x][j][0]=max(f[x][j][0],max(f[y][j][0],f[y][j][1])),
			g[x][j][0]=max(g[x][j][0],max(g[y][j][0],g[y][j][1]));
			f[x][j][1]=max(f[x][j][1],max(f[y][j-1][0],f[y][j-1][1])+sum),
			g[x][j][1]=max(g[x][j][1],max(g[y][j-1][0],g[y][j-1][1])+sum-a[y]+a[p]);
		}
	}
}
signed main(){
	n=read(),v=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1,u,v;i<n;i++){
		u=read(),v=read();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,0);
	cout<<ans;
}
```



---

## 作者：ZZXB (赞：6)

[官方题解](http://ceoi.inf.elte.hu/probarch/17/ceoi2017-solutions-day2.pdf)
### 题意

给出一棵树，求一条路径，选择路上的V个点，使得被选择的点的**相邻且不在路径上的点**的权值和最大。

### 思路

#### 定义：
$c[i][j]$为从$i$点的子树中走到i，选择j个点的权值和。

$b[i][j]$为从$i$点开始，向子树中走，选择j个点的权值和。

$g[i]$为$i$的相邻节点的权值和。

$fa[i]$为$i$的父节点。

$F[i]$为$i$的权值。

#### 初始值：

$c[x][0]=0,c[x][i]=g[x]$

$b[x][0]=0,b[x][i]=g[x]-F[fa[x]]$

#### 转移方程：

$c[x][i]=max(c[y][i],c[y][i-1]+g[x]-F[y])$

$b[x][i]=max(b[y][i],b[y][i-1]+g[x]-F[fa[x]])$

### 代码

``` c
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
const int maxn=1e5+5;
int N,V,x,y,tot,top,F[maxn],sta[maxn];
int son[maxn<<1],nxt[maxn<<1],lnk[maxn];
long long g[maxn],c[maxn][105],b[maxn][105],ans;
inline int read() {
	int ret=0,f=1,ch=getchar();
	for (; !isdigit(ch); ch=getchar()) if (ch=='-') f=-f;
	for (; isdigit(ch); ch=getchar()) ret=ret*10+ch-48;
	return ret*f;
}
inline void add_edge(int x,int y) {
	son[++tot]=y,nxt[tot]=lnk[x],lnk[x]=tot;
	son[++tot]=x,nxt[tot]=lnk[y],lnk[y]=tot;
}
inline void DP(int x,int y,int f) {
//  ans一定要在前面赋值，这样可以避免从y走到x又走回y
	for (int i=1; i<=V; ++i) ans=max(ans,c[x][i]+b[y][V-i]);
	for (int i=1; i<=V; ++i)
		c[x][i]=max(c[x][i],max(c[y][i],c[y][i-1]+g[x]-F[y])),
		b[x][i]=max(b[x][i],max(b[y][i],b[y][i-1]+g[x]-F[f]));
}
void dfs(int x,int pre) {
	for (int i=1; i<=V; ++i) c[x][i]=g[x],b[x][i]=g[x]-F[pre];
	for (int k=lnk[x]; k; k=nxt[k]) if (son[k]^pre) dfs(son[k],x),DP(x,son[k],pre);
//  对于节点x，y和z是它的子节点并且，y先于z遍历。
//  上面的方法，无法计算z->x->y所以要倒着做一遍
	for (int i=1; i<=V; ++i) c[x][i]=g[x],b[x][i]=g[x]-F[pre];
	top=0;for (int k=lnk[x]; k; k=nxt[k]) if (son[k]^pre) sta[++top]=son[k];
	for (int i=top; i; --i) DP(x,sta[i],pre);
	ans=max(ans,max(c[x][V],b[x][V]));
}
int main() {
	N=read(),V=read();
	for (int i=1; i<=N; ++i) F[i]=read();
	for (int i=1; i<N; ++i) add_edge(x=read(),y=read()),g[x]+=F[y],g[y]+=F[x];
	return dfs(1,0),printf("%lld",ans),0;
}
```

---

## 作者：zJx_Lm (赞：4)

### 基本思路 ：

 * 首先令 a 数组表示该点的权值，c 数组表示该点所连接的所有点的权值和。
 
 * 如果我们知道了该点的前驱，那该点的权值就为 $ c_{now}-a_{pre} $。
 
---------
### 递进 ：

  问题在于这是一棵无根树，那我们可以任意定义一点为根，
  然后设两个数组 $ s_{i,j} $,$ d_{i,j} $ 分别表示从子树 $ i $ 中某个点走到 $ i $ 和从 $ i $ 走到子树 $ i $ 中某个点，放置了 $ j $ 次的最大收益。那问题就变成求树的直径了。

---------
### 注意 ：

因为我们需要知道一个点的前驱，所以 $ s $ 数组 是记录该子树的根节点的，$ d $ 数组 是不记录该子树的根节点的。

另外，起始点一定会放置磁铁，因为如果逃亡者降落一个点后再跑到其他点放置磁铁，那显然不如直接降落在该点放置磁铁更优。

最后一点，如果是起始点，因为其没有前驱，所以该点的贡献为 $ c_{now} $。 

--------
### 树的直径 ：

因为树的路径不能重复，所以我们可以枚举完一个 $ to $ 节点后先与 $ now $ 的 $ d $ 数组和 $ s $ 数组更新一边答案，再将 $ to $ 节点的答案合并到 $ now $ 的答案中。

--------

时间复杂度 ：$ O(nv) $
* code  

```cpp
/* 念往昔 */
#include<bits/stdc++.h>
#define re register
#define int long long
#define lls long long
#define fr first
#define sc second
#define pb push_back
using namespace std;
const int mol=1e9+7;
const int maxn=1e5+10;
const int INF=1e9+10;
inline int qpow(int a,int b) { int ans=1; while(b) { if(b&1) (ans*=a)%=mol; (a*=a)%=mol; b>>=1; } return ans; }
inline int read() {
    int w=1,s=0; char ch=getchar();
    while(ch<'0'||ch>'9') { if(ch=='-') w=-1; ch=getchar(); }
    while(ch>='0'&&ch<='9') { s=s*10+ch-'0'; ch=getchar(); }
    return s*w;
}

int n,m,w[maxn],f[110][maxn],g[110][maxn],ans,maxf[110],maxg[110],as[maxn];
struct EDGE { int var,nxt; } edge[maxn<<1];
int head[maxn],cnt;
inline void add(int a,int b) { edge[++cnt]=(EDGE){ b,head[a] }; head[a]=cnt; }
inline void dfs(int now,int fa) {
    f[1][now]=as[now];
    for(re int i=head[now],to;i;i=edge[i].nxt) if((to=edge[i].var)!=fa) {
        dfs(to,now);
        for(re int j=1;j<=m;j++) maxf[j]=max(maxf[j-1],f[j][now]); 
        for(re int j=1;j<=m;j++) maxg[j]=max(maxg[j-1],g[j][now]); 
        ans=max(ans,f[1][to]+maxg[m-1]); 
        for(re int k=2;k<=m;k++) ans=max(ans,max(f[k][to],f[k-1][to]+as[now]-w[to])+maxg[m-k]);
        for(re int k=1;k<=m;k++) ans=max(ans,g[k][to]+maxf[m-k]);
        for(re int k=m;k>=1;k--) {
            f[k][now]=max(f[k][now],f[k][to]); 
            g[k][now]=max(g[k][now],g[k][to]); 
        }
        for(re int k=m-1;k>=1;k--) if(f[k][to]) f[k+1][now]=max(f[k+1][now],f[k][to]+as[now]-w[to]);
    }
    for(re int i=1;i<=m;i++) ans=max(ans,f[i][now]);
    for(re int i=m-1;i>=1;i--) if(g[i][now]) g[i+1][now]=max(g[i+1][now],g[i][now]+as[now]-w[fa]); 
    g[1][now]=max(g[1][now],as[now]-w[fa]); 
}
signed main(void) {
    n=read(); m=read(); if(!m) { puts("0"); return 0; }
    for(re int i=1;i<=n;i++) w[i]=read();
    for(re int i=1,a,b;i<n;i++) { a=read(); b=read(); add(a,b); add(b,a); as[b]+=w[a]; as[a]+=w[b]; } 
    dfs(1,0);
    printf("%lld\n",ans);
}
```



---

## 作者：Super_Cube (赞：3)

# Solution

显然逃亡者走到 $i$ 号房间并放下磁铁，对答案的贡献为 $\displaystyle\sum_{j \in \operatorname{son_i}} F_j$。

无根树，所以换根 dp。

$dp_{i,j,0/1}$ 表示当前在 $i$，剩余 $j$ 个磁铁，是否在当前节点上放磁铁。

对于 $\forall k \in \operatorname{son_i}, s_i=\sum F_k$ ，有转移式：

+ $dp_{i,j,0}=\max\{ dp_{k,j,0},dp_{k,j,1} \}$

$i$ 不放磁铁，那么 $k$ 也会拥有 $j$ 个磁铁，放或不放都可以。

+ $dp_{i,j,1}=dp_{i,j-1,0}+s_i$

$i$ 放磁铁，~~为了偷懒，~~ 直接取 **少一个磁铁并且当前位置不放磁铁 的状态**，再加上当前房间磁铁的贡献。

接下来写换根 dp。

$i$ 往 $k$ 换根时，如果 $k$ 的贡献正好是 $dp_{i,j,0}$ 中取到 $\max$ 的那个儿子，这个时候因为 $i$ 已经是 $k$ 的子节点了，所以 $dp_{i,j,0}$ 的那一坨要重新选个值来取。

套路，记录最大值和次大值，如果最大值在换根时寄了，就改用次大值计算 dp 值。

对于写换根的技巧，就是把 $i$ 当作 $k$ 的一个儿子，~~然后将前面的转移复制下来，调换 $i$ 与 $k$ 的位置，~~ 到处修修补补，把 $i$ 中 $k$ 存在的贡献消除掉就好了。

# Code

```cpp
//val[0/1]: 最大值 / 次大值
void dfs(const int& p, const int& dad) {
	for (const int& i : v[p]) {
		if (i == dad)
			continue;
		dfs(i, p);
		s[p] += a[i];
		for (int j = 1; j <= m; ++j) {
			if (val[p][j][0] < std::max(dp[i][j][0], dp[i][j][1]))
				val[p][j][1] = val[p][j][0], val[p][j][0] = std::max(dp[i][j][0], dp[i][j][1]);
			else
				val[p][j][1] = std::max(val[p][j][1], std::max(dp[i][j][0], dp[i][j][1]));
		}//记录最大值与次大值
	}
	for (int i = 1; i <= m; ++i) dp[p][i][0] = val[p][i][0];
	for (int i = 1; i <= m; ++i) dp[p][i][1] = dp[p][i - 1][0] + s[p];
}
void change(const int& p, const int& dad) {
	for (const int& i : v[p]) {
		if (i == dad)
			continue;
		long long _dp[105][2];//dp[0/1] 除去当前儿子节点贡献后的值
		for (int j = 1; j <= m; ++j) {
			if (val[p][j][0] != std::max(dp[i][j][0], dp[i][j][1]))//最大值与当前儿子节点无关
				_dp[j][0] = val[p][j][0];//可以继续沿用最大值
			else
				_dp[j][0] = val[p][j][1];//否则使用次大值更新
		}
		_dp[0][0] = 0;
		for (int j = 1; j <= m; ++j) _dp[j][1] = _dp[j - 1][0] + s[p] - a[i];
		for (int j = 1; j <= m; ++j) {
			if (val[i][j][0] < std::max(_dp[j][0], _dp[j][1]))
				val[i][j][1] = val[i][j][0], val[i][j][0] = std::max(_dp[j][0], _dp[j][1]);
			else
				val[i][j][1] = std::max(val[i][j][1], std::max(_dp[j][0], _dp[j][1]));
		}//更新换根后当前儿子节点的 val
		s[i] += a[p];//因为新多了个儿子 p
		for (int j = 1; j <= m; ++j) dp[i][j][0] = val[i][j][0];
		for (int j = 1; j <= m; ++j) dp[i][j][1] = dp[i][j - 1][0] + s[i];
		change(i, p);
		s[i] -= a[p];//回溯
	}
}
```

---

## 作者：pomelo_nene (赞：3)

一个很显然的结论，将磁铁用完之后还要走显然不会更优秀，所以用完了 $v$ 个磁铁就不用走了。

于是考虑一个朴素的 dp 想法。定义 $dp_{u,i}$ 为以 $u$ 为根，用 $i$ 块磁铁的最大答案是多少。当然在此之前，我们需要枚举每个点作为整棵树的根。

在 dp 过程中，一个点只有用或者不用两种状态，枚举相连的每个节点找到最大的转移，写法和思路比较显然。时间复杂度 $O(n^2v)$。

哦不这样还拿不到满分。我们该怎么办？

对于一般的套路，我们的时间复杂度问题过大是因为我们枚举了每个根。那要是我们不枚举根呢？

考虑最终答案，可以把其看为一条在以 $1$ 为根的树上的链。假设现在我们到了遍历到这条链上的某一个点，有哪些情况呢？

- 在不存在点的深度比这个点深度大的点上，链一直往下延伸；   
- 在不存在点的深度比这个点深度小的点上，链一直往上延伸；   
- 在某个点上，使得存在点的深度比这个点深度大，同时存在点的深度比这个点深度小，链有往上延伸的，也有往下延伸的。

我们发现上面两种情况比较好处理，差不多跟我们开始想的 $O(n^2v)$ 的 dp 差不多的（这部分是 $O(nv)$ 算！）。但是第三种情况怎么处理？

将答案上的链上的一个点 $s$ 删去，现在就变成了两条链，刚好是 $s$ 往下延伸的链和 $s$ 往上延伸的链。

而我们之前的两个东西已经可以算出来了，于是两条链的贡献合并起来就能得到最终答案。

综上，定义 $dp_{u,i,x=0 \operatorname{or} 1}$ 为若 $x=0$，则是从 $u$ 的子树的某个点向上用了 $i$ 个磁铁走到 $u$；否则则是从某个节点向下走了若干步用了 $i$ 个磁铁走到 $u$ 的答案。每次加入一棵子树，先更新两条链合并起来的答案，再更新 dp 数组。

实际代码并不是很难写。代码带注释。至少在 2020/8/23 10:55 之前是最优解吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
LL read()
{
	LL x=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9')
	{
		if(c=='-')	f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9')	x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x*f;
}
void write(LL x)
{
	if(x<0)	putchar('-'),x=-x;
	if(x>9)	write(x/10);
	putchar(x%10+'0');
}
vector<LL> G[100005];
LL n,v,a[100005],dp[100005][105][2],sum[100005],ans;
void dfs(LL now,LL pre)
{
	for(LL i=1;i<=v;++i)	dp[now][i][0]=sum[now],dp[now][i][1]=sum[now]-a[pre];
	for(unsigned int i=0;i<G[now].size();++i)
	{
		LL to=G[now][i];
		if(to==pre)	continue;
		dfs(to,now);
		for(LL i=1;i<v;++i)	ans=max(ans,dp[now][i][0]+dp[to][v-i][1]);//合并两条链，更新答案。
		for(LL i=1;i<=v;++i)
		{
			dp[now][i][0]=max(dp[now][i][0],max(dp[to][i][0],dp[to][i-1][0]+sum[now]-a[to]));
			dp[now][i][1]=max(dp[now][i][1],max(dp[to][i][1],dp[to][i-1][1]+sum[now]-a[pre]));
		}
		//合并子树，更新 dp 值。
	}
	for(LL i=1;i<=v;++i)	dp[now][i][0]=sum[now],dp[now][i][1]=sum[now]-a[pre];
	for(unsigned int i=G[now].size()-1;~i;--i)//遍历顺序可能会影响答案，于是再倒着加入子树计算。
	{
		LL to=G[now][i];
		if(to==pre)	continue;
		for(LL i=1;i<v;++i)	ans=max(ans,dp[now][i][0]+dp[to][v-i][1]);
		for(LL i=1;i<=v;++i)
		{
			dp[now][i][0]=max(dp[now][i][0],max(dp[to][i][0],dp[to][i-1][0]+sum[now]-a[to]));
			dp[now][i][1]=max(dp[now][i][1],max(dp[to][i][1],dp[to][i-1][1]+sum[now]-a[pre]));
		}
	}
	ans=max(ans,max(dp[now][v][0],dp[now][v][1]));//统计一直往上用 v 个磁铁和往下用 v 个磁铁的答案。
}
int main(){
	n=read(),v=read();
	for(LL i=1;i<=n;++i)	a[i]=read();
	for(LL i=1;i<n;++i)
	{
		LL p=read(),q=read();
		G[p].push_back(q);
		G[q].push_back(p);
		sum[p]+=a[q];
		sum[q]+=a[p];
	}
	dfs(1,0);
	write(ans);
	return 0;
}
```

---

## 作者：XUCHENGHUI (赞：2)

首先非常显然的就是，这些房间连成一棵树，而且是一棵无根树。假定点x
是根，那么逃亡者的路径就是从x
的子树里选一个点，往这个点走。然后重复上述过程，直到他选择一个点离开迷宫。
所以一个显然的树形DP就是枚举每一个点做根，然后以这个根向下DP，求出扔下v
个磁铁所能获得的最大铁球差异值。
当然我们需要明确，铁球的差异是如何产生的。当我们在树上x
点扔下一个磁铁，那么差异是这个点的所有儿子的权值和（为什么没有它自己和它父亲？因为这些点都是先走的，或者这些点被之前的点吸引了，并不可能增加当前点的贡献）。
所以这个树形DP很简单，然而复杂度是过不去的。只能拿70分。
```cpp
#include<bits/stdc++.h>
#define MAXN 100005
#define ll long long
using namespace std;
char tc(){
    static char fl[100000],*A=fl,*B=fl;
    return A==B&&(B=(A=fl)+fread(fl,1,100000,stdin),A==B)?EOF:*A++;
}
ll read(){
    char c;ll x=0,y=1;while(c=tc(),(c<'0'||c>'9')&&c!='-');
    if(c=='-') y=-1;else x=c-'0';while(c=tc(),c>='0'&&c<='9')
    x=x*10+c-'0';return x;
}
ll ans,f[MAXN][105];
int n,v,cnt,val[MAXN],head[MAXN<<1],nxt[MAXN<<1],go[MAXN<<1],vis[MAXN];
void add(ll x,ll y){
    go[cnt]=y;nxt[cnt]=head[x];head[x]=cnt;cnt++;
    go[cnt]=x;nxt[cnt]=head[y];head[y]=cnt;cnt++;
}
ll rise(int x,int v){
    if(v==0) return 0;
    if(f[x][v]) return f[x][v];
    ll res=0,out=0;vis[x]=1;
    register int i;
    for(i=head[x];i!=-1;i=nxt[i]){
        int to=go[i];
        if(vis[to]) continue;
        res+=val[to];
    }
    for(i=head[x];i!=-1;i=nxt[i]){
        int to=go[i];
        if(vis[to]) continue;
        out=max(out,res+rise(to,v-1));
    }
    for(i=head[x];i!=-1;i=nxt[i]){
        int to=go[i];
        if(vis[to]) continue;
        out=max(out,rise(to,v));
    }
    vis[x]=0;f[x][v]=out;
    return f[x][v];
}
int main()
{
    n=read();v=read();
    register int i,j,k;
    memset(head,-1,sizeof(head));
    for(i=1;i<=n;i++) val[i]=read();
    for(i=1;i<n;i++){
        ll x=read(),y=read();
        add(x,y);
    }
    if(n<=1000){  //这个是根据数据特判
        for(i=1;i<=n;i++){
            for(j=1;j<=n;j++) vis[j]=0;
            for(j=1;j<=n;j++)
             for(k=1;k<=v;k++) f[j][k]=0;
            ans=max(ans,rise(i,v));
        }
        printf("%lld\n",ans);
        return 0;
    }
    printf("%lld",rise(1,v));  //由于保证有30分从1开始，所以直接以1为根做
    return 0;
}```


既然我们要以每一个点为根，那么我们可以考虑定1为假根，然后用一种类似点分治的思路，去计算它的儿子的答案。（实际上就是以儿子为根的答案），我们设up[x][i]表示从某点出发，扔出i个磁铁，最终到达x的最大差异值，而down[x][i]表示从x出发，扔下i个磁铁所能获得的最大差异值。
那么我们显然可以写出转移：

```cpp
for(int j=1;j<=v;j++) up[x][j]=max(up[x][j],up[to][j]),down[x][j]=max(down[x][j],down[to][j]);
for(int j=1;j<=v;j++){
    up[x][j]=max(up[x][j],up[to][j-1]+deg[x]-val[to]);  //up从下往上，所以应该减去下面的点。
    down[x][j]=max(down[x][j],down[to][j-1]+deg[x]-val[fa[x]]);  //down从上往下，所以减去父亲
}
```
但是我们要去重，因为如果不去重，可能up和down走的是同一个儿子，那么这样就违反了题目每条边只能走一次的规定。于是我们在循环的时候先更新答案，再更新up和down，代码如下：
```cpp
for(int i=head[x];i!=-1;i=nxt[i]){
    int to=go[i];
    if(fa[x]==to) continue;sta[++top]=to;  //sta这句话和目前无关，可以无视
    for(int j=1;j<v;j++) ans=max(ans,up[x][j]+down[to][v-j]);  //先更新，就能保证不会重复
    for(int j=1;j<=v;j++) up[x][j]=max(up[x][j],up[to][j]),down[x][j]=max(down[x][j],down[to][j]);
    for(int j=1;j<=v;j++){
        up[x][j]=max(up[x][j],up[to][j-1]+deg[x]-val[to]);
        down[x][j]=max(down[x][j],down[to][j-1]+deg[x]-val[fa[x]]);
    }
}
ans=max(ans,max(down[x][v],up[x][v]));
```
但是我们还得考虑一个问题，就是比如我们从u
走上x
,再从x
走下v
，这样的答案和从v
走上x
，再从x
走下u
的大答案是不一样的。而我们上面的统计由于为了去重，就会导致我们匹配up和down时up走的子树肯定在down左边。但如果在右边怎么办？我们把x
的子树顺序前后翻转一下，就可以使匹配时up走的子树在down右边。这样操作就可以统计所有的答案。
我们在代码里用一个栈来操作。上文的sta就是将所有儿子放在栈里。最后统计右边的时候就倒着枚举栈即可。
```cpp
while(top){
    int to=sta[top--];
    for(int j=1;j<v;j++) ans=max(ans,up[x][j]+down[to][v-j]);
    for(int j=1;j<=v;j++) up[x][j]=max(up[x][j],up[to][j]),down[x][j]=max(down[x][j],down[to][j]);
    for(int j=1;j<=v;j++){
        up[x][j]=max(up[x][j],up[to][j-1]+deg[x]-val[to]);
        down[x][j]=max(down[x][j],down[to][j-1]+deg[x]-val[fa[x]]);
    }
}
ans=max(ans,max(down[x][v],up[x][v]));
```
下面是完整的代码：
```cpp
#include<bits/stdc++.h>
#define MAXN 100005
#define ll long long
using namespace std;
int read(){
    char c;int x;while(c=getchar(),c<'0'||c>'9');x=c-'0';
    while(c=getchar(),c>='0'&&c<='9') x=x*10+c-'0';return x;
}
int n,v,cnt,val[MAXN],head[MAXN<<1],nxt[MAXN<<1],go[MAXN<<1],fa[MAXN],sta[MAXN],top;
ll up[MAXN][105],down[MAXN][105],ans,deg[MAXN];
void add(int x,int y){
    go[cnt]=y;nxt[cnt]=head[x];head[x]=cnt;cnt++;
    go[cnt]=x;nxt[cnt]=head[y];head[y]=cnt;cnt++;
}
void dfs(int x){
    for(int i=1;i<=v;i++) up[x][i]=deg[x],down[x][i]=deg[x]-val[fa[x]];
    for(int i=head[x];i!=-1;i=nxt[i]){
        int to=go[i];
        if(fa[x]==to) continue;
        fa[to]=x;dfs(to);
    }
    for(int i=head[x];i!=-1;i=nxt[i]){
        int to=go[i];
        if(fa[x]==to) continue;sta[++top]=to;
        for(int j=1;j<v;j++) ans=max(ans,up[x][j]+down[to][v-j]);
        for(int j=1;j<=v;j++) up[x][j]=max(up[x][j],up[to][j]),down[x][j]=max(down[x][j],down[to][j]);
        for(int j=1;j<=v;j++){
            up[x][j]=max(up[x][j],up[to][j-1]+deg[x]-val[to]);
            down[x][j]=max(down[x][j],down[to][j-1]+deg[x]-val[fa[x]]);
        }
    }
    ans=max(ans,max(down[x][v],up[x][v]));
    for(int i=1;i<=v;i++) up[x][i]=deg[x],down[x][i]=deg[x]-val[fa[x]];
    while(top){
        int to=sta[top--];
        for(int j=1;j<v;j++) ans=max(ans,up[x][j]+down[to][v-j]);
        for(int j=1;j<=v;j++) up[x][j]=max(up[x][j],up[to][j]),down[x][j]=max(down[x][j],down[to][j]);
        for(int j=1;j<=v;j++){
            up[x][j]=max(up[x][j],up[to][j-1]+deg[x]-val[to]);
            down[x][j]=max(down[x][j],down[to][j-1]+deg[x]-val[fa[x]]);
        }
    }
    ans=max(ans,max(down[x][v],up[x][v]));
}
int main()
{
    n=read();v=read();
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++) val[i]=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        add(x,y);deg[x]+=val[y];deg[y]+=val[x];
    }
    dfs(1);
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Pekac (赞：1)

[P4657](https://www.luogu.com.cn/problem/P4657)

###### Sol

树形 dp。

首先，追逐者遇到的铁球的数量显然不会少于逃亡者遇到的铁球数量。

令 $ss_i$ 表示与 $i$ 相邻的点的权值之和。$\mathcal{O}(n^2v)$ 的 dp 是很简单的。

令 $dp_{i,j,0/1}$ 表示根节点到 $i$ 的路径上，用了 $j$ 次磁铁，当前节点选 / 不选的最大值。转移是简单的。

加上 $\mathcal{O}(n)$ 的枚举根节点，时间复杂度就是 $\mathcal{O}(n^2v)$ 的了。

参考暴力 dp 的定义方式，对其进行优化。令 $f_{i,j,0/1}$ 表示从 $i$ 走到 $i$ 的子树中，用了 $j$ 次磁铁，在 $i$ 处用 / 没用。$g_{i,j,0/1}$ 则表示 $i$ 的子树走到 $i$ 的答案。

则有转移方程：

$f_{u,i,0}=\max\limits_{v\in \{son_u\}}\{f_{v,i,0},f_{v,i,1}\}$，$f_{u,i,1} = \max\limits_{v\in \{son_u\}}\{f_{v,i-1,0},f_{v,i-1,1}\}+ss_u-a_{fa}$。

$g_{u,i,0}=\max\limits_{v\in \{son_u\}}\{g_{v,i,0},g_{v,i,1}\}$，$g_{u,i,1}=\max\limits_{v\in \{son_u\}}\{g_{v,i-1,0}-a_v,g_{v,i-1,1}-a_v\}+ss_u$。

然后考虑怎么统计答案。

由于直接统计可能会导致路径重复，可以在转移时统计答案。具体地，可以使 $ans$ 对 $\max(f_{v,i,0},f_{v,i,1})+\max(g_{u,j,0},g_{u,j,1})$ 和 $\max(g_{v,i,0},g_{v,i,1})+\max(f_{u,j,0},f_{u,j,1}+a_{fa}-a_v)$ 取 $\max$，在统计了答案后再转移，就可以使每条路径不重复统计，因为是对儿子 $v_i$ 之前的所有满足 $j<i$ 的 $v_j$ 做统计。但是如果直接枚举 $i, j$ 的话，是有 $\mathcal{O}(v^2)$ 的复杂度的，在递推时做一个前缀 $\max$ 即可。

###### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include<bits/stdc++.h>
using namespace std;
static char buf[50000],*paa=buf,*pd=buf;
static char buf2[50000],*pp=buf2;
#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,50000,stdin),paa==pd)?EOF:*paa++
inline void pc(const char &ch){
	if(pp-buf2==50000) fwrite(buf2,1,50000,stdout),pp=buf2;
	*pp++=ch;
}
inline void pcc(){
	fwrite(buf2,1,pp-buf2,stdout);
	pp=buf2;
}
inline int read(){
	int w=1;
	register int x=0;register char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return w*x;
}
inline void write(ll x){
	if(x<0) pc('-'),x=-x;
	static int sta[20];register int top=0;
	do{sta[top++]=x%10,x/=10;}while(x);
	while(top) pc(sta[--top]+48);
}
inline void we(register ll x){
	write(x);
	pc('\n');
}
void gmx(ll &x,ll y){if(x<y)x=y;}
const int N=1e5+10;const ll inf=0x3f3f3f3f3f3f3f3f;
int n,V;ll ans;
int a[N];
ll ss[N],f[N][110][2],g[N][110][2];
int head[N],cnt_e;
struct edge{ int v,nxt; } e[N<<1];
void adde(int u,int v){
	e[++cnt_e]=(edge){v,head[u]};
	head[u]=cnt_e;
}
int rt;
void dfs(int u,int fath){
	for(int i=head[u],v;i;i=e[i].nxt)if((v=e[i].v)!=fath)dfs(v,u);
	f[u][0][0]=g[u][0][0]=0;f[u][0][1]=g[u][0][1]=-inf;
	g[u][1][1]=ss[u];f[u][1][1]=ss[u]-a[fath];
	for(int i=head[u],v;i;i=e[i].nxt)if((v=e[i].v)!=fath){
		ll mx1=0,mx2=0;
		for(int j=0;j<=V;j++){
			gmx(mx1,g[u][j][0]),gmx(mx1,g[u][j][1]);
			gmx(mx2,f[u][j][0]),gmx(mx2,f[u][j][1]+a[fath]-a[v]);
			gmx(ans,max(f[v][V-j][0],f[v][V-j][1])+mx1);
			gmx(ans,max(g[v][V-j][0],g[v][V-j][1])+mx2);
		}
		for(int j=1;j<=V;j++)gmx(f[u][j][0],max(f[v][j][0],f[v][j][1])),gmx(f[u][j][1],max(f[v][j-1][0],f[v][j-1][1])+ss[u]-a[fath]);
		for(int j=1;j<=V;j++)gmx(g[u][j][0],max(g[v][j][0],g[v][j][1])),gmx(g[u][j][1],max(g[v][j-1][0],g[v][j-1][1])+ss[u]-a[v]);
	}
}
int main(){
	n=read(),V=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1,u,v;i<n;i++)u=read(),v=read(),adde(u,v),adde(v,u),ss[u]+=a[v],ss[v]+=a[u];
	dfs(1,0);
	we(ans);pcc();
	return 0;
}
```

---

## 作者：_ZSR_ (赞：1)

### [P4657 [CEOI2017] Chase](https://www.luogu.com.cn/problem/P4657)

暴力很好想，令 $dp_{i,j}$ 表示以某个点为根，到 $i$ 的路途中放了 $j$ 个磁铁的最大差值。显然在一个节点放一个磁铁可以获得它所有儿子的 $f$ 之和的差值。那么转移方程为 $dp_{i,j}=\max (dp_{fa,j},dp_{fa,j-1}+s_{i})$，其中 $s_{i}$ 表示 $i$ 的所有儿子的 $f$ 之和。但是这样的复杂度是 $O(n^2v)$ 的，不能接受。

转移的 $O(nv)$ 不太好优化，只能优化枚举的复杂度，因此我们只能固定一个根节点，不妨令它为 $1$ 号节点。既然不能枚举起点，那么我们只能去考虑路径。显然，最终答案的路径要么是一直向上或者一直向下，要么就在一个节点拐弯，套路地，我们考虑这个拐点。这样的话我们就要知道向下的最大值和从下面上来的最大值。于是令 $f_{i,j,0/1}$ 表示从 $i$ 到 $i$ 的子树中的某个点，放了 $j$ 个磁铁的最大差值。这里默认 $i$ 是从一个节点走过来的，即它不是起点。令 $g_{i,j,0/1}$ 表示从 $i$ 的子树中的某个点到 $i$，放了 $j$ 个磁铁的最大差值。

转移就是: 

$$f_{i,j,0}=\max(f_{son,j,0},f_{son,j,1})$$

$$g_{i,j,0}=\max(g_{son,j,0},g_{son,j,1})$$

这两个和好理解，因为 $i$ 不放磁铁，所以直接继承就可以。

$$f_{i,j,1}=\max(f_{son,j-1,0},f_{son,j-1,1})+s_{i}$$

$$g_{i,j,1}=\max(g_{son,j-1,0},g_{son,j-1,1})+s_{i}-a_{son}+a_{fa}$$

这里的 $a$ 就是铁球个数。这两个也很好理解。因为 $i$ 要放，所以加上在 $i$ 放的贡献。从 $i$ 下去贡献还是 $s_{i}$，但是从下面上来贡献就要稍微改变一下。

初始的时候把 $g_{i,1,1}$ 赋成 $s_{i}+a_{fa}$，表示从 $i$ 走到 $i$。那为什么不把 $f_{i,1,1}$ 也赋成这个呢？因为前面说了，默认 $i$ 不是起点。并且，我们还要把 $f_{i,0,1}$ 和 $g_{i,0,1}$ 赋成负无穷，因为这是不合法的状态。

下面考虑更新答案。前面说了，我们考虑道路的拐点，因此我们在合并子节点的时候去更新答案。更新答案的方式有两种：

$$ans=\max(f_{i,x,0},f_{i,x,1}+a_{fa}-a_{son})+\max(g_{son,y,0},g_{son,y,1}),\forall x+y \leq v$$

$$ans=\max(g_{i,x,0},g_{i,x,1})+\max(f_{son,y,0},f_{son,y,1}),\forall x+y \leq v$$

第一种是从当前这个儿子的子树里上来，然后下到之前的某个儿子的子树中。因为是从儿子上来的，所以放磁铁的收益要变一下。第二种是从之前的某个儿子的子树里上来，然后下到当前的儿子的子树里。但是我们会发现，这样需要枚举 $x,y$，时间复杂度就变成 $O(v^2)$ 的了，无法接受。于是我们可以倒序枚举 $y$，这样的话就可以不断更新关于 $x$ 的前缀最大值，复杂度变为 $O(v)$。

code
```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+10,M=110;
int n,m;
ll ans;
int a[N];
ll f[N][M][2],g[N][M][2];
vector<int> to[N];
void dfs(int x,int fa)
{
	f[x][0][1]=g[x][0][1]=-1e16;
	ll sum=0;
	for (int y:to[x])
    {
		if (y==fa) continue;
		dfs(y,x);
		sum+=a[y];
	}
	g[x][1][1]=sum+a[fa];
	for (int y:to[x])
    {
		if (y==fa) continue;
		ll maxf=-1e16,maxg=-1e16;
		for (int j=m;j>=0;--j)
        {
			maxf=max(maxf,max(f[x][m-j][0],f[x][m-j][1]+a[fa]-a[y]));
			maxg=max(maxg,max(g[x][m-j][0],g[x][m-j][1]));
			ans=max(ans,maxg+max(f[y][j][0],f[y][j][1]));
			ans=max(ans,maxf+max(g[y][j][0],g[y][j][1]));
		}
		for (int j=1;j<=m;++j)
        {
			f[x][j][0]=max(f[x][j][0],max(f[y][j][0],f[y][j][1]));
			g[x][j][0]=max(g[x][j][0],max(g[y][j][0],g[y][j][1]));
			f[x][j][1]=max(f[x][j][1],max(f[y][j-1][0],f[y][j-1][1])+sum);
			g[x][j][1]=max(g[x][j][1],max(g[y][j-1][0],g[y][j-1][1])+sum-a[y]+a[fa]);
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) scanf("%d",&a[i]);
	for (int i=1;i<n;++i)
    {
        int u,v;
		scanf("%d%d",&u,&v);
		to[u].push_back(v);
		to[v].push_back(u);
	}
	dfs(1,0);
	printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：lyxeason (赞：1)

首先可以先把 1 号节点钦定为根节点，这样后面好计算。

那么考虑设计动态规划状态，可以想到应该使用树形 DP，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/yuql054c.png)

一条经过 $i$ 的路径肯定能够分为从子树到 $i$ (在图中箭头向上) 和从 $i$ 到子树 (在图中箭头向下) 的两部分。且可以在 $i$ 点放置磁铁也可以不放，这两种情况是不同的。并且还需要限制路径上的磁铁个数。

那么我们就可以从这几个因素中得到状态 $f_{i,j,0/1}$，表示从 $i$ 到 $i$ 的子树，放 $j$ 个磁铁，$i$ 点放/不放磁铁的最优答案。同时需要一个对应的状态 $g_{i,j,0/1}$，表示从 $i$ 的子树到 $i$，放 $j$ 个磁铁，$i$ 点放/不放磁铁的最优答案。 

状态转移，先考虑 $f$ 的转移：

$$f_{i,j,0}=\max_{\text{v是i的子节点}}\max(f_{v,j,0},f_{v,j,1})$$
$$f_{i,j,1}=\max_{\text{v是i的子节点}}\max(f_{v,j-1,0},f_{v,j-1,1})+s_i+a_{fa_i}-a_v$$

其中，$s_i$ 表示 $i$ 的所有子节点的铁球数量之和，$a_i$ 表示 $i$ 点的铁球数。

解析：首先 $f_{i,j,0}$ 中 $i$ 没有放上磁铁，所以子节点处的 $j$ 不变，对子节点选不选都没有要求，所以直接取 $\max$ 就可以。$f_{i,j,1}$ 中 $i$ 点放上了磁铁，则再往下的子节点处只能放 $j-1$ 个磁铁。在 $i$ 点放磁铁取得的价值就是所有和 $i$ 点有边相连的点的铁球数 (即 $s_i+a_{fa_i}$)，但是这里枚举的是 $i$ 点刚刚从 $v$ 点移动过来，那么就需要减去 $v$ 点的铁球数量 (即 $-a_v$)，就是取得的价值。

$g$ 的转移：

$$g_{i,j,0}=\max_{\text{v是i的子节点}}\max(g_{v,j,0},g_{v,j,1})$$
$$g_{i,j,1}=\max_{\text{v是i的子节点}}\max(g_{v,j-1,0},g_{v,j-1,1})+s_i$$

这里 $g$ 的转移和 $f$ 同理，就不再解释。

初始化：
- $g_{i,1,1}=s_i+a_{fa_i}$，即 $i$ 是起点
- $f_{i,0,1}$ 与 $g_{i,0,1}$ 非法，初始化为负无穷

但是要算出答案需要保证路径不重合，不反复经过同一条边。那么可以考虑在子树内,用这个子节点更新 $i$ 点的动态规划值之前计算答案。

$res=\max({res,\max{(f_{i,j_1,0},f_{i,j_1,1})+\max{(g_{v,j_2,0},g_{v,j_2,1})}}})$

$res=\max({res,\max{(f_{v,j_1,0},f_{v,j_1,1})+\max{(g_{i,j_2,0},g_{i,j_2,1}+a_{fa_i}-a_v)}}})$

这样枚举 $j_1,j_2$ 会超时，但是可以用前缀最大值来解决。具体见代码。

------------
### 代码
###### 代码里有注释
```cpp


#include <cstdio>
#include <cstring>
#define ll long long

using namespace std;

int N;
int V;
ll F[100009];
int h[100009];
int nxt[200009];
int to[200009];
int idx;
ll f[100009][109][2]; //这里的f和g代表的意义与题解中相反(
ll g[100009][109][2];
ll res;

inline void Add (int a, int b) {
    nxt[idx] = h[a], to[idx] = b, h[a] = idx++;
}

void In () {
    int a;
    int b;

    memset(h, -1, sizeof(h));
    scanf("%d%d", &N, &V);
    for (int i = 1; i <= N; i++) scanf("%lld", &F[i]);
    for (int i = 1; i < N; i++) {
        scanf("%d%d", &a, &b);
        Add(a, b), Add(b, a);
    }
}

inline ll Max (ll a, ll b) {
    return a > b ? a : b;
}

void Get_Res (int x, int p) {
    ll s = 0;
    int v;
    ll sf; //前缀最大值
    ll sg;

    f[x][0][1] = g[x][0][1] = -1e18; //初始化
    for (int e = h[x]; ~e; e = nxt[e]) {
        v = to[e];
        if (v == p) continue;
        Get_Res(v, x);
        s += F[v]; //计算子节点的铁球数量和
    }
    g[x][1][1] = s + F[p];
    for (int e = h[x]; ~e; e = nxt[e]) {
        v = to[e];
        if (v == p) continue;
        sf = sg = -1e18;
        for (int j = V; j >= 0; j--) {
            sf = Max(sf, Max(f[x][V - j][0], f[x][V - j][1] + F[p] - F[v])); //更新前缀最大值
            sg = Max(sg, Max(g[x][V - j][0], g[x][V - j][1]));
            res = Max(res, sf + Max(g[v][j][0], g[v][j][1]));
            res = Max(res, sg + Max(f[v][j][0], f[v][j][1]));
        }
        for (int j = 1; j <= V; j++) {
            f[x][j][0] = Max(f[x][j][0], Max(f[v][j][0], f[v][j][1]));
            f[x][j][1] = Max(f[x][j][1], Max(f[v][j - 1][0], f[v][j - 1][1]) + s);
            g[x][j][0] = Max(g[x][j][0], Max(g[v][j][0], g[v][j][1]));
            g[x][j][1] = Max(g[x][j][1], Max(g[v][j - 1][0], g[v][j - 1][1]) + s + F[p] - F[v]);
        }
    }
}

void Solve () {
    Get_Res(1, 0);
}

void Out () {
    printf("%lld\n", res);
}

int main () {

    In();
    Solve();
    Out();

    return 0;
}
```

---

## 作者：chenzida (赞：1)

恶心的树形 dp。。。wtcl

考虑枚举中转点，也就是逃亡者走的路径深度最浅的点 LCA。分别用 $dp[x][i]$ 和 $f[x][i]$ 表示从 $x$ 点向下和从某个点向上到 $x$ 点，且用了 $i$ 块磁铁最多能对答案有多少贡献。

转移的话就直接对于一个中转点的每个儿子，正序一遍逆序一遍即可。

具体就是先考虑儿子从考左边上到 $x$ 点，然后再从 $x$ 走到靠右边的点下去，也就是左上右下或者右上左下。

转移的话直接树上背包一下即可

```
dp[x][j]=max(dp[x][j],max(dp[y][j],dp[y][j-1]+s[x]-a[y]));

f[x][j]=max(f[x][j],max(f[y][j],f[y][j-1]+s[x]-a[fa_]));
```

完整代码如下

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int NR=1e5+10;
const int MR=105;
void Min(int& x,int y){x=min(x,y);}
void Max(int& x,int y){x=max(x,y);}
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,v;
int a[NR];
ll s[NR],ans;
int to[NR<<1],nxt[NR<<1],head[NR],tot=1;
void add(int x,int y){
	to[tot]=y,nxt[tot]=head[x],head[x]=tot++;
}
int st[NR];
ll dp[NR][MR],f[NR][MR];
void dfs(int x,int fa_)
{
	for(int i=1;i<=v;i++)dp[x][i]=s[x],f[x][i]=s[x]-a[fa_];
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];if(y==fa_)continue;dfs(y,x);
		for(int j=0;j<=v;j++)ans=max(ans,dp[x][j]+f[y][v-j]);
		for(int j=1;j<=v;j++){
			dp[x][j]=max(dp[x][j],max(dp[y][j],dp[y][j-1]+s[x]-a[y]));
			f[x][j]=max(f[x][j],max(f[y][j],f[y][j-1]+s[x]-a[fa_]));
		}
	}int tt=0;
	for(int i=1;i<=v;i++)dp[x][i]=s[x],f[x][i]=s[x]-a[fa_];
	for(int i=head[x];i;i=nxt[i])if(to[i]!=fa_)st[++tt]=to[i];
	for(int i=tt;i>=1;i--)
	{
		int y=st[i];
		for(int j=0;j<=v;j++)ans=max(ans,dp[x][j]+f[y][v-j]);
		for(int j=1;j<=v;j++){
			dp[x][j]=max(dp[x][j],max(dp[y][j],dp[y][j-1]+s[x]-a[y]));
			f[x][j]=max(f[x][j],max(f[y][j],f[y][j-1]+s[x]-a[fa_]));
		}
	}
}
int main()
{
	n=read(),v=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		s[x]+=a[y],s[y]+=a[x],add(x,y),add(y,x);
	}
	dfs(1,0);
	printf("%lld\n",ans);
	return 0;
}

```

---

