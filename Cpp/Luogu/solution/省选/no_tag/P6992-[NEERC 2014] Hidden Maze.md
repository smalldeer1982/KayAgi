# [NEERC 2014] Hidden Maze

## 题目描述

这是一个交互式问题。

五子棋是一种在二维网格上进行的双人游戏。网格的每个单元格可以是空的，包含第一位玩家的标记（黑色），或者包含第二位玩家的标记（白色），但不能同时包含两者。最初整个网格是空的。两位玩家轮流下棋，从第一位玩家开始。每次移动时，玩家可以在一个空单元格中放置她的标记。第一个在一行中有五个相邻标记的玩家获胜。获胜的行可以是垂直的、水平的或对角线的。

![](https://upload.acmicpc.net/23c94254-2783-405a-907b-7b66bea5514b/-/preview/)

第二位玩家（白色标记）获胜的位置。

在这个问题中，玩家使用一个 $19 \times 19$ 的网格。如果整个网格被标记填满但没有玩家获胜，游戏被判为平局。

第一位玩家使用以下策略：作为第一次移动，她将她的标记放在网格的中心单元格。在每次其他移动中，她选择一个能最大化结果位置得分的移动。

为了找到一个位置的得分，第一位玩家考虑所有可能最终形成获胜组合的位置——换句话说，棋盘上所有水平、垂直和对角线的五个连续单元格的行（当然，它们可能相互重叠）。如果这样的行同时包含第一位玩家和第二位玩家的标记，则不予考虑。如果这样的行不包含任何标记，也不予考虑。对于每个只包含第一位玩家的标记且没有第二位玩家标记的行，添加 $50^{2k-1}$ 到位置的得分，其中 $k$ 是第一位玩家的标记数量（$1 \le k \le 5$）。对于每个只包含第二位玩家的标记且没有第一位玩家标记的行，从位置的得分中减去 $50^{2k}$。最后，随机添加一个介于 $0$ 和 $50^{2} - 1$ 之间的整数到得分中。这个随机数是均匀选择的。

在第一位玩家的几个移动得分相等的情况下（由于上述随机加法，这种平局很少见），第一位玩家选择 x 坐标最小的移动，如果 x 坐标相同，则选择 y 坐标最小的移动。

你的任务是编写一个程序，扮演第二位玩家并击败这种策略。

你的程序将与上述策略进行 100 场比赛，使用不同的随机生成器种子。你的程序必须赢得所有这些比赛。

## 说明/提示

时间限制：2 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
2 1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
2 4 4
1 2 5
5 4 2
5 3 3
```

### 输出

```
3.50
```

## 样例 #3

### 输入

```
5
4 1 2
5 3 2
4 2 3
5 4 7
```

### 输出

```
3.1666666667
```

# 题解

## 作者：Reunite (赞：1)

经典题。

我们称边上的原权为边的值，后面赋的权为边的权。考虑弱化一下，如何求中位数恰为 $k$ 的路径数，显然可以把 $\le k$ 的边设为 $-1$，$\ge k$ 的设为 $1$，如果一条路径边权和为 $1$ 且恰经过某条值为 $k$ 的边，那显然恰好中位数为 $k$。

路径和这种东西可以点分，但不好扩展和处理恰经过的条件，考虑 dp，设 $f_{u,i}$ 为 $u$ 子树内所有点到 $u$ 边权和为 $i$ 的点数，转移 $O(\sum dep_i)$ 是简单的。对于计算答案，只需要枚举所有值为 $k$ 的边 $(u,v,k),dep_u<dep_v$，枚举 $u$ 祖先 $U$ 和 $U$ 往 $u$ 方向的儿子 $V$，撤销 $V$ 子树对 $dp_U$ 的贡献，然后枚举 $U$ 子树内 $V$ 子树外的边权和计算一下即可。实现只需要开一个栈维护到根链然后倒着扫。就是经典撤销子树内贡献的方法。

怎么扩展呢，如果我们按边的值顺次加入边，那么每次只会影响祖先的 $dp$ 值，先倒着撤销，再暴跳修改即可，本质上是动态 dp。

时间复杂度考虑一个点被重构的次数和单次复杂度，为 $O(\sum sz_i(maxdep_i-dep_i))$，另一篇题解说这个在树按照本题的方式随机生成的情况下复杂度为 $O(n\sqrt n)$。

---

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define P 250
#define ll long long
using namespace std;

int n,m;
int stk[P+5];
int ww[30005];
int fa[30005];
int mde[30005];
int dep[30005];
int f[30005][P*2+5];
vector <int> g[30005];
struct node{int u,v,w;}e[30005];
ll all;

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline pair <int,int> dfs(int u,int fath){
	fa[u]=fath;
	dep[u]=dep[fa[u]]+1;
	mde[u]=0;
	f[u][P]=1;
	int s1=0,s2=0;
	if(dep[u]&1) s1++;
	else s2++;
	for(int v:g[u]){
		if(v==fath) continue;
		ww[v]=-1;
		auto tmp=dfs(v,u);
		mde[u]=max(mde[u],mde[v]+1);
		all+=s1*tmp.second+s2*tmp.first;
		s1+=tmp.first,s2+=tmp.second;
		for(int i=-mde[u];i<=mde[u];i++) f[u][i+P]+=f[v][i+1+P];
	}
	return {s1,s2};
}

signed main(){
	in(n);
	for(int i=1;i<n;i++){
		in(e[i].u),in(e[i].v),in(e[i].w);
		g[e[i].u].emplace_back(e[i].v);
		g[e[i].v].emplace_back(e[i].u);
	}
	dfs(1,0);
	sort(e+1,e+n,[](node p,node q){return p.w<q.w;});
	ll ans=0,S=0;
	for(int i=1;i<n;i++){
		int u=e[i].u,v=e[i].v;
		if(dep[u]<dep[v]) swap(u,v);
		ans=0;
		int top=0,uu=fa[u],s=1;
		stk[0]=u;
		while(uu) stk[++top]=uu,s+=ww[uu],uu=fa[uu];
		for(int d=top;d>=1;d--){
			int U=stk[d],V=stk[d-1];
			for(int j=-mde[U];j<=mde[U];j++) f[U][j+P]-=f[V][j-ww[V]+P];
			for(int j=-mde[U];j<=mde[U];j++){
				int x=1-j-s;
				if(x<-P||x>P) continue;
				ans+=f[U][j+P]*f[u][x+P];
			}
			s-=ww[V];
		}
		S+=e[i].w*ans;
		ww[u]=1;
		int U=fa[u],V=u;
		while(U){
			for(int j=-mde[U];j<=mde[U];j++) f[U][j+P]+=f[V][j-ww[V]+P];
			U=fa[U],V=fa[V];
		}
	}
	printf("%.9lf\n",1.0*S/all);

	return 0;
}
```

---

## 作者：a___ (赞：1)

分别钦定每一条边为中位数，计算这种情况的方案数。  

我们先把边权从小到大排序，然后从小往大遍历每一条边 $i$，让这条边及之前的边权为 $1$；这条边之后的边权为 $-1$，则问题转化为求经过边 $i$ 且边权和为 $1$ 的路径的数量。   

由于树是随机生成的，所以树高不会很高。考虑直接暴力 dp。设 $g_{i,j}$ 表示点 $i$ 的子树中到 $i$ 权值和为 $j$ 的点数。每将一条边的边权由 $-1$ 为 $1$，就枚举这条边的祖先，暴力修改转移。   

设 $d_i$ 表示深度，$dr_i$ 表示由 $i$ 向下的距离，由于数据随机，则复杂度为 $\mathbf O (\sum d_idr_i)=\mathbf O(n\sqrt n)$。   

具体转移方程参见代码实现。   

```cpp
#include<cstdio>
#include<algorithm>
const int N=30010,M=510;
int n,las[N],nxt[N<<1],to[N<<1],cnt,fa[N],w[N],g[N][M<<1],dep[N],depr[N];
inline void add(int u,int v){++cnt;to[cnt]=v;nxt[cnt]=las[u];las[u]=cnt;}
struct edge
{
	int u,v,w;
	inline void read(){scanf("%d%d%d",&u,&v,&w);add(u,v);add(v,u);}
	bool operator < (const edge &x) const {return w<x.w;}
}e[N];
inline int max(int a,int b){return a>b?a:b;}
inline void swap(int &x,int &y){int t=x;x=y;y=t;}
void dfs(int u,int f)
{
	dep[u]=dep[fa[u]=f]+1;g[u][M]=1;w[u]=-1;
	for(int i=las[u];i;i=nxt[i])
	if(to[i]!=f)
	{
		dfs(to[i],u);
		depr[u]=max(depr[u],depr[to[i]]+1);
		for(int j=-depr[to[i]];j<=depr[to[i]];j++)
		g[u][j+w[to[i]]+M]+=g[to[i]][j+M];
	}
}
long long now,ans,tot;
int main()
{
	int i,j,x,sum;scanf("%d",&n);
	for(i=1;i<n;i++)e[i].read();
	dfs(1,0);std::sort(e+1,e+n);
	for(i=1;i<n;i++)
	{
		if(dep[e[i].u]<dep[e[i].v])swap(e[i].u,e[i].v);
		for(sum=w[x=e[i].u];fa[x];sum+=w[x=fa[x]])
		for(j=-depr[e[i].u];j<=depr[e[i].u];j++)
		g[fa[x]][j+sum+M]-=g[e[i].u][j+M];
		for(sum=w[x=e[i].u]=1;fa[x];sum+=w[x=fa[x]])
		for(j=-depr[e[i].u];j<=depr[e[i].u];j++)
		g[fa[x]][j+sum+M]+=g[e[i].u][j+M];
		for(sum=w[x=e[i].u],now=0;fa[x];sum+=w[x=fa[x]])
		for(j=-depr[e[i].u];j<=depr[e[i].u];j++)
		now+=(long long)(g[fa[x]][1-j-sum+M]-g[x][1-j-sum-w[x]+M])*g[e[i].u][j+M];
		ans+=now*e[i].w;tot+=now;
	}
	printf("%.15lf\n",(double)ans/tot);return 0;
}
```

---

