# [POI 2016] Nadajniki

## 题目描述

比特镇一共有 $n$ 个房子，编号依次为 $1$ 到 $n$，这些房子通过 $n-1$ 条无向道路连通在一起，形成了一棵树的结构。

Bytesear 要在比特镇实施 Wifi 搭建计划，他要让 Wifi 覆盖到比特镇的每一条道路。

Bytesear 可以安置无限多个 Wifi 发射器，但是只能安置在树上的节点上，一个房子可以安置多个 Wifi 发射器。

对于一条道路 $(a,b)$，如果它满足以下两个条件之中的至少一个，那么这条边将被 Wifi 覆盖：
- $a$ 点放置了 Wifi 发射器或者 $b$ 点放置了 Wifi 发射器。
- 与 $a$ 点或 $b$ 点直接相邻的点中，至少放置了两个 Wifi 发射器。

请帮助 Bytesear 规划一个最优的放置方案，使得 Wifi 覆盖到比特镇的每一条道路，且放置的 Wifi 发射器总数尽可能少。

## 说明/提示

对于 $100\%$ 的数据，$2\le n\le2 \times 10^5$，$1\le a,b\le n$。

----

### 样例解释：

在 $3$ 号点放置两个 Wifi 发射器。


## 样例 #1

### 输入

```
7
1 2
2 3
4 3
5 4
6 3
7 6```

### 输出

```
2```

# 题解

## 作者：QwQcOrZ (赞：7)

树形 dp。

思考转移的时候可以考虑开始只有一个点，每次加一棵子树进去，这样思考起来会清晰一点。

由于覆盖一条边的可能是相邻点或者其相邻边连向的点，所以处理时 $i$ 子树内与 $i$ 相邻的边可能未被覆盖，所以需要将其考虑到状态里。

记 $f_{i,j=0/1/2/3/4,k=0/1/2}$ 表示 $i$ 子树内，$j=0$ 表示 $i$ 与 $i$ 的儿子都没有放发射器，$j=1/2$ 分别表示 $i$ 放了 $1$、$2$ 个发射器，$j=3/4$ 分别表示 $i$ 的儿子放了 $1$、$\geq2$ 个发射器，$k$ 表示 $i$ 子树内与其相邻的边还需要的发射器数量。

不需要考虑 $i$ 和 $i$ 儿子都放了发射器的情况，因为这个时候只有 $i$ 上的发射器有用。

转移时，记当前节点为 $u$，加入的儿子为 $v$。

先考虑 $v$ 子树内与 $v$ 相邻的未覆盖边，它们需要 $u$ 放的发射器数量为 $v$ 状态中的 $k$，根据这个条件先判掉不合法的转移。

再考虑 $u$ 与 $v$ 之间的连边：

1. 如果 $u$ 或 $v$ 上有发射器，则此边已被覆盖，直接不管；

2. 否则此边相邻点上的发射器数量为 $u$ 儿子上发射器数量 $+$ $v$ 儿子上发射器数量，这两个都记在 dp 状态中了。根据这个更新 $u$ 状态的 $k$ 值。

还有就是根据 $v$ 上的发射器数量来更新 $u$ 状态 $j,k$ 的值。

具体可以自己画张图思考一下，或者直接看代码

$\texttt{Code Below}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int inf;

int read()
{
	int s=0;
	char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(int x)
{
	if (x<0) putchar('-'),x=-x;
	if (x<10) putchar(x+'0');
	else write(x/10),putchar(x%10+'0');
}
void print(int x,char c='\n')
{
	write(x);
	putchar(c);
}
struct edge
{
	int to,nxt;
}e[N*2];
int head[N],cnte=0;
void add_edge(int u,int v)
{
	e[++cnte].to=v;
	e[cnte].nxt=head[u];
	head[u]=cnte;
}
int f[N][5][3],g[5][3];
bool trans(int x,int y,int a,int b,int &c,int &d)
{
	c=x,d=y;
	if (b)
	{
		if (x>2) return 0;
		if (x<b) return 0;
	}
	if (1<=a&&a<=2) d=max(d-a,0);
	if (!((1<=a&&a<=2)||(1<=x&&x<=2)))
	{
		int tot=max(a-2,0)+max(x-2,0);
		d=max(d,2-tot);
	}
	if (1<=a&&a<=2&&!(1<=c&&c<=2)) c=min(a+max(c-2,0)+2,4);
	return 1;
}
void dfs(int now,int father)
{
	f[now][0][0]=0;
	f[now][1][0]=1;
	f[now][2][0]=2;
	for (int i=head[now];i;i=e[i].nxt)
	{
		int to=e[i].to,c,d;
		if (to==father) continue;
		dfs(to,now);
		memcpy(g,f[now],sizeof(g));
		memset(f[now],0x3f,sizeof(f[now]));
		for (int x=0;x<=4;x++)
		for (int y=0;y<=2;y++)
		if (g[x][y]<inf)
		for (int a=0;a<=4;a++)
		for (int b=0;b<=2;b++)
		if (f[to][a][b]<inf)
		if (trans(x,y,a,b,c,d))
		f[now][c][d]=min(f[now][c][d],g[x][y]+f[to][a][b]);
	}
}

signed main(signed bangumi,char *ss969[])
{
	(void)bangumi,(void)ss969;
	memset(f,0x3f,sizeof(f));
	inf=f[0][0][0];
	int n=read();
	for (int i=1;i<n;i++)
	{
		int u=read(),v=read();
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,0);
	int ans=inf;
	for (int i=0;i<=4;i++) ans=min(ans,f[1][i][0]);
	print(ans);
	
	return 0;
}
```

---

## 作者：qwer6 (赞：2)

## 1. Description

对于一个点，有三种状态：

1. 非关键点。
2. 价值为 $1$ 的关键点。
3. 价值为 $2$ 的关键点。

对于一条边 $(u,v)$，定义其合法当且仅当满足以下两个条件中的至少一个：

1. $u$ 或 $v$ 是任意价值的关键点。
2. 与 $u$ 或 $v$ 直接相连的所有点的价值之和大于等于 $2$。

现在给出一棵树，要求求出使这棵树所有边均合法的最小价值。

## 2. Solution

显然使用树形 DP 来求解，我们考虑定义状态。

首先对于 $u$ 的儿子 $v$，我们发现 $v$ 的儿子的价值之和会对 $(u,v)$ 的合法性产生影响，所以将之记入状态，然后 $v$ 和 $v$ 的儿子的连边的合法性也会被 $u$ 影响，换句话说，在只考虑 $v$ 的子树时，这条边可以暂时不合法，所以也将之记入状态。但是当 $u$ 成为关键点时，$u$ 的儿子的价值之和就没有用了，$u$ 与 $u$ 的儿子的连边也一定合法，所以我们定义 $f_{u,0/1/2,0/1/2}$ 表示 $u$ 不是关键点时，$u$ 的儿子的价值和为 $0/1/2$，$u$ 与 $u$ 的儿子的所有连边最多还差 $0/1/2$ 的价值的最小代价，注意当儿子的价值和大于 $2$ 时也视作 $2$，并定义 $g_{u,0/1}$ 表示 $u$ 的价值为 $1/2$ 时的最小代价。

那么转移时相当于加入每一棵子树，刚开始 $u$ 被视作孤点，初始化为 $f_{u,0,0}=0,g_{u,0}=1,g_{u,1}=2$，其余均为正无穷。

然后考虑加入 $v$ 这棵子树，使用刷表法来写，将 $f_u$ 和 $g_u$ 复制为 $tmpf,tmpg$，并将 $f_u,g_u$ 重设为正无穷，下文定义 $son_v$ 表示 $v$ 的儿子，$son_u$ 表示 $u$ 已经加入的儿子。

那么首先考虑 $f_{v,i,j}$ 和 $f_{u,a,b}$ 的转移情况。由于 $v$ 不放，所以 $f_u$ 的第二维不会发生变化，又因为 $(u,v)$ 这一条边同时受到 $son_u$ 和 $son_v$ 的影响，所以 $(u,v)$ 这条边就还差 $2-a-i$ 的价值，但是 $u$ 不是关键点，也就不会对 $v$ 和 $son_v$ 的连边的合法性产生任何影响，所以 $j$ 就必须等于 $0$，也就是 $f_{u,a,\max(b,2-a-i)}\leftarrow f_{v,i,0}+tmpf_{a,b}$。

然后考虑 $f_{v,i,j}$ 和 $g_{u,0}$ 的转移情况，由于 $u$ 只放了一个，所以 $j$ 就必须小于等于 $1$，也就是 $g_{u,0}\leftarrow f_{v,i,0/1}+tmpg_0$。$f_{v,i,j}$ 和 $g_{u,1}$ 的转移情况类似，但是对 $j$ 没有限制，也就是 $g_{u,1}\leftarrow f_{v,i,0/1/2}+tmpg_1$。

接着考虑 $g_{v,x}$ 和 $f_{u,a,b}$ 的转移，因为 $v$ 放了 $x+1$ 个，所以 $u$ 的儿子的价值和加 $x+1$，并且也会对 $u$ 与 $son_u$ 的连边的合法性产生影响，所以 $b$ 就会减少 $x+1$，因此得到转移 $f_{u,\min(2,a+x+1),\max(0,b-x-1)}\leftarrow g_{v,x}+tmpf_{a,b}$。

最后考虑 $g_{v,x}$ 和 $g_{u,y}$ 的转移。在转移时并没有什么限制，直接转移即可，得到转移 $g_{u,y}\leftarrow g_{v,x}+tmpg_{y}$。

那么直接进行树形 DP，求解答案即可，最后的答案就是 $\min(f_{1,0,0},f_{1,1,0},f_{1,2,0},g_{1,0},g_{1,1})$。

## 3. Code

```c++
/*by qwer6*/
/*略去缺省源与快读快写*/
const int N=2e5+5,inf=0x3f3f3f3f;
int n;
int f[N][3][3],g[N][2],tmpf[3][3],tmpg[2];
/*
f[u][0/1/2][0/1/2]
表示 u 不放,u 的儿子放了 0/1/>=2 个,u 的子树中与 u 相连的边还需要 0/1/2 个 
g[u][0/1]
表示 u 放了 1/2 个
*/
vector<int>e[N];
void dfs(int u,int fa){
	f[u][0][0]=0;
	g[u][0]=1;
	g[u][1]=2;
	for(int v:e[u]){
		if(v==fa)continue;
		dfs(v,u);
		for(int i=0;i<=2;i++)
			for(int j=0;j<=2;j++){
				tmpf[i][j]=f[u][i][j];
				f[u][i][j]=inf;
			}
		tmpg[0]=g[u][0],tmpg[1]=g[u][1];
		g[u][0]=g[u][1]=inf;
		for(int i=0;i<=2;i++){
			for(int j=0;j<=2;j++){
				if(f[v][i][j]>=inf)continue;
				//首先考虑 f[v]->f[u] 
				//由于 u 不放，所以 v->son[v] 的所有边必须合法 
				if(j==0){
					for(int a=0;a<=2;a++){
						for(int b=0;b<=2;b++){
							if(tmpf[a][b]>=inf)continue;
							//v 不放,v 的儿子放了 i 个,v 的子树中与 v 相连的边还需要 j 个
							//由于 v 不放，因此 u 的第二维不更新，考虑第三维即可 
							//由于 u,v 均不放,v 的儿子放了 i 个,u 的其他儿子放了 a 个,
							//所以 u -> v这一条边还需要 2-i-a 个 
							//那么第三维应该变为 max(b,2-i-a) 个 
							tomin(f[u][a][max(b,2-i-a)],tmpf[a][b]+f[v][i][j]);
						}
					}	
				}
				//然后考虑 f[v]->g[u][0]
				//v 不放,v 的儿子放了 i 个,v 的子树中与 v 相连的边还需要 j 个
				//u 放了一个，所以 u->v 不需要
				//如果 j>1,那么不够,也就不能转移 
				if(j<=1)
					tomin(g[u][0],tmpg[0]+f[v][i][j]);
				//最后考虑 f[v]->g[u][1]
				//v 不放,v 的儿子放了 i 个,v 的子树中与 v 相连的边还需要 j 个
				//u 放了两个，所以 u->v 不需要
				//那么 v->son[v] 一定合法
				tomin(g[u][1],tmpg[0]+f[v][i][j]); 
			}
		}
		//然后考虑 v 放了的情况 
		//g[v][0] v 放了一个
		//首先考虑 g[v][0]->f[u] 
		//v 放了一个
		//那么第二维变成 min(2,a+1)
		//第三维变成 max(0,b-1)
		for(int a=0;a<=2;a++){
			for(int b=0;b<=2;b++){
				if(tmpf[a][b]>=inf)continue;
				tomin(f[u][min(2,a+1)][max(0,b-1)],tmpf[a][b]+g[v][0]);
			}
		}	
		//然后 g[v][0] 可以直接转移到 g[u][0]/g[u][1]
		tomin(g[u][0],tmpg[0]+g[v][0]);
		tomin(g[u][1],tmpg[1]+g[v][0]);
		//g[v][1] v 放了两个
		//首先考虑 g[v][1]->f[u] 
		//v 放了两个
		//那么第二维变成 min(2,a+2)
		//第三维变成 max(0,b-2)
		for(int a=0;a<=2;a++){
			for(int b=0;b<=2;b++){
				if(tmpf[a][b]>=inf)continue;
				tomin(f[u][min(2,a+2)][max(0,b-2)],tmpf[a][b]+g[v][1]);
			}
		}
		//然后 g[v][0] 可以直接转移到 g[u][0]/g[u][1]
		tomin(g[u][0],tmpg[0]+g[v][1]);
		tomin(g[u][1],tmpg[1]+g[v][1]);
	}
}
signed main(){
	read(n);
	for(int i=2,u,v;i<=n;i++){
		read(u),read(v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	memset(f,0x3f,sizeof(f));
	memset(g,0x3f,sizeof(g));
	dfs(1,0);
	write(min({f[1][0][0],f[1][1][0],f[1][2][0],g[1][0],g[1][2]}));
}
```

---

