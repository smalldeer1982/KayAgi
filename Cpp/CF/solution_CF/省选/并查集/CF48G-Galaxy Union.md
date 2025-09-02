# Galaxy Union

## 题目描述

在一个遥远的星系中有 $n$ 颗有人居住的行星，编号从 $1$ 到 $n$。有一天，$n$ 颗行星上的领导人各自产生了建立同盟的想法。每个行星提出了创建星系同盟的想法，但是其他行星的人都不知道。现在他们需要与他们的星系伙伴分享这个绝妙的想法，这就是为什么每位领导人都忙于与其他领导人谈判。

某些行星之间的谈判有着双向通信通道，每个通道的都有 “拨号持续时间” $t_i$。通常，这需要几个小时并且大大超过了可供通话的时间。总的来说，银河系有 $n$ 条通信通道，它们将所有行星互相联系起来。这意味着可能从任意行星 $u$ 直接向任何行星 $v$ 打电话。或许可以使用一些中间行星 $v_1,v_2,\cdots,v_m$ 通过 $u$ 和 $v_1,v_2,\cdots,v_{m-1},v_m$ 和 $v$ 之间的现有通道。那么从 $u$ 到 $v$ 的拨号持续时间等于所使用通信通道的拨号持续时间之和。

所以，每个领导人都必须一个接一个地与所有其他 $n - 1$ 个行星的领导人交谈。谈判严格并连续进行，直到与一方的谈判结束后，另一颗行星的拨号才能开始。由于事情紧急，所以得以最快的方式与其他星球进行联络。几乎不需要时间向另一位总统保证银河联盟的重要性，这就是为什么与每个行星的谈判时间可以被视为等于这些行星的拨号持续时间。由于总统对彼此的计划一无所知，他们没有考虑到这样一种可能性：如被寻求的总统可能会自称或已经从其他来源知道银河联盟的成立。

$n$ 颗行星都要求你来制定谈判计划。你需要找出每位总统所谓的谈判需要多少时间。

## 样例 #1

### 输入

```
3
1 2 3
2 3 2
1 3 1
```

### 输出

```
4 5 3
```

## 样例 #2

### 输入

```
3
1 2 3
2 3 2
1 3 5
```

### 输出

```
8 5 7
```

## 样例 #3

### 输入

```
4
1 2 3
2 3 2
3 4 1
4 1 4
```

### 输出

```
12 8 8 8
```

# 题解

## 作者：He_Ren (赞：9)

$n$个点$n$条边，是一棵基环树

**基环树的操作一般把树和环分开做**

找环：

```cpp
bool find_c(int u,int last)
{
	vis[u]=1;
	push(u);
	for(int i=head[u]; i; i=e[i].next)
		if(e[i].to!=last)
		{
			if(vis[e[i].to])
			{
				while(top()!=e[i].to)
				{
					is[top()]=1;
					c[++ccnt]=top();
					pop();
				}
				is[e[i].to]=1;
				c[++ccnt]=e[i].to;
				return 1;
			}
			if(find_c(e[i].to,u)) return 1;
		}
	vis[u]=0;
	pop();
	return 0;
}
```


先只考虑树

不难想到树形dp

设$dp[i]$为树内点的答案

先用子节点更新父节点，这样环上点到对应树中点的$ans$就处理好了

```cpp
ll ans[MAXN*2];

int size[MAXN*2];
void dfs(int u,int fa)
{
	size[u]=1;
	for(int i=head[u]; i; i=e[i].next)
		if(e[i].to!=fa && !is[e[i].to])
		{
			int v=e[i].to;
			dfs(v,u);
			ans[u] += ans[v] + e[i].w*size[v];
			size[u]+=size[v];
		}
}
```
**环上的操作一般先断环为链**

对于环上每个点

考虑使用尺取法选到最远的，不超过环长度一半的点

这些点的最短路走左边（即 “不超过环长度一半” 的那一边）

```cpp
while(sumw[r]-sumw[l-1] <= (sumw[ccnt]>>1)) ++r;
```

另一半的点走右边

两边的操作类似，这里只说左边

设这个点为$i$,左边的点为$i,i+1,\cdots,j$

$$ans[i] = \sum_{k=i}^j (dp[k]+size[k] \times dis(i,k))$$

_这个式子很重要，想一想为什么是对的_

但是这样是$O(n^2)$的，显然会超时

考虑优化

**加和的优化（不带修改）一般使用前缀和**

但是这个式子并不能直接使用前缀和优化

**先考虑较好优化的部分，其他部分或许就会迎刃而解**

发现$\sum dp[k]$比较好求，先求了（即代码中的```tot```）

问题就是，怎么把$size[k] \times dis(i,k)$写成可以使用前缀和的形式

先用前缀和求$dis$：

$$\sum_{k=i}^j size[k] \times (sumw[k]-sumw[i-1])$$

$$= \sum_{k=i}^j size[k] \times sumw[k] - \sum_{k=i}^j size[k] \times sumw[i-1]$$

$$= \sum_{k=i}^j size[k] \times sumw[k] - sumw[i-1] \sum_{k=i}^j size[k]$$

然后$\sum_{k=i}^j size[k] \times sumw[k]$和$\sum_{k=i}^j size[k]$就也可以前缀和了

这是左边的式子，右边相似（但并不相同），这里就不赘述了

（下面的代码，用的式子和上面推导过程中用的的有不同）

```cpp
for(int l=1,r=1; l<=ccnt; ++l)
{
	while(sumw[r]-sumw[l-1] <= (sumw[ccnt]>>1)) ++r;
	ans[c[l]]
	= tot//dp值的和
	+ sums[r]*(sumw[r-1]-sumw[l-1]) - (sum[r-1]-sum[l-1])
	+ (sum[l+ccnt-1]-sum[r]) - sums[r]*(sumw[l+ccnt-1]-sumw[r]);
	dfs2(c[l],0);
}
```

然后用环上点的答案更新树上点的答案

```cpp
void dfs2(int u,int fa)
{
	for(int i=head[u]; i; i=e[i].next)
		if(e[i].to!=fa && !is[e[i].to])
		{
			int v=e[i].to;
			ans[v] = ans[u] + e[i].w*(n-size[v]) - e[i].w*size[v];
			dfs2(v,u);
		}
}
```

总体来说，这道题比较考验代码能力，我也因为细节调了好久

是练习码力的好题

完整代码：

```cpp
#include<cstdio>
const int MAXN = 2e5 + 5;
typedef long long ll;

struct Edge
{
	int next,to,w;
}e[MAXN<<1];
int head[MAXN],etot=0;
inline void add(int u,int v,int w)
{
	++etot;
	e[etot].next=head[u];
	e[etot].to=v;
	e[etot].w=w;
	head[u]=etot;
}

int n;
bool is[MAXN];

int c[MAXN*2],w[MAXN*2],ccnt=0;
bool vis[MAXN];
int st[MAXN],tp=0;
inline int top(void){ return st[tp];}
inline void push(int x){ st[++tp]=x;}
inline void pop(void){ --tp;}
bool find_c(int u,int last)
{
	vis[u]=1;
	push(u);
	for(int i=head[u]; i; i=e[i].next)
		if(e[i].to!=last)
		{
			if(vis[e[i].to])
			{
				while(top()!=e[i].to)
				{
					is[top()]=1;
					c[++ccnt]=top();
					pop();
				}
				is[e[i].to]=1;
				c[++ccnt]=e[i].to;
				return 1;
			}
			if(find_c(e[i].to,u)) return 1;
		}
	vis[u]=0;
	pop();
	return 0;
}

ll ans[MAXN*2];

int size[MAXN*2];
void dfs(int u,int fa)
{
	size[u]=1;
	for(int i=head[u]; i; i=e[i].next)
		if(e[i].to!=fa && !is[e[i].to])
		{
			int v=e[i].to;
			dfs(v,u);
			ans[u] += ans[v] + e[i].w*size[v];
			size[u]+=size[v];
		}
}

void dfs2(int u,int fa)
{
	for(int i=head[u]; i; i=e[i].next)
		if(e[i].to!=fa && !is[e[i].to])
		{
			int v=e[i].to;
			ans[v] = ans[u] + e[i].w*(n-size[v]) - e[i].w*size[v];
			dfs2(v,u);
		}
}

ll sums[MAXN*2],sumw[MAXN*2],sum[MAXN*2];
int main(void)
{
	scanf("%d",&n);
	for(int i=0; i<n; ++i)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w); add(v,u,w);
	}
	
	find_c(1,0);
	for(int i=1; i<=n ;++i)
		if(is[i]) dfs(i,0);
	
	ll tot=0;
	for(int i=1; i<=ccnt; ++i)
	{
		c[ccnt+i]=c[i];
		tot+=ans[c[i]];
		for(int j=head[c[i]]; j; j=e[j].next)
			if(e[j].to == c[i+1])
			{
				w[ccnt+i]=w[i]=e[j].w;
				break;
			}
	}
	for(int i=1; i<=ccnt*2; ++i)
	{
		sums[i] = sums[i-1]+size[c[i]];
		sumw[i] = sumw[i-1]+w[i];
		sum[i] = sum[i-1] + w[i]*sums[i];
	}
	
	for(int l=1,r=1; l<=ccnt; ++l)
	{
		while(sumw[r]-sumw[l-1] <= (sumw[ccnt]>>1)) ++r;
		ans[c[l]]
		= tot
		+ sums[r]*(sumw[r-1]-sumw[l-1]) - (sum[r-1]-sum[l-1])
		+ (sum[l+ccnt-1]-sum[r]) - sums[r]*(sumw[l+ccnt-1]-sumw[r]);
		dfs2(c[l],0);
	}
	for(int i=1; i<=n; ++i) printf("%lld ",ans[i]);
	return 0;
}
```


---

## 作者：周小涵 (赞：5)

基环树模板。

环上的点我们通过双指针求出答案。

具体的说，先对于每个环上的点，求出他子树内到他的距离和 $sm_u$ 和 子树大小 $siz_u$ ，然后断环成链，考虑双指针，显然我们发现环上每个点走到另一个点只有顺时针和逆时针两个走法，而且同一种走法的点位于连续的区间。

对于环上的第一个位置我们单独处理出一个指针 $j$ 表示 $j \to i$ 这个区间内的所有点应该顺时针走到 $i$ ,其余的是逆时针。然后枚举每个位置，计算 $dst$ 表示 $i \to j$ 的 顺时针路径长度，如果超出环上总长度 $Sm$ 的一半，则不断移动指针，统计贡献也很简单，记一下区间的 $\sum siz_i$ ，然后可以每移动一格距离造成了多少贡献。

求出环上的点后，我们去求出每个点子树内的答案。但在这之前得对于子树内部做一遍换根dp，求出子树内部点之间互相的贡献。

考虑求出子树内的点答案，我们只需向下递归的时候考虑一条边的贡献即可。
分别是子树内和子树外

想清楚后还是比较好写的。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
const int N=2e5+5;
int n,idx,len,tot,size;
int dfn[N],fa[N],lp[N],dis[N],sum[N],sm[N];
int head[N],nxt[N<<1],to[N<<1],edge[N<<1];
int dep[N],siz[N],ans[N],nt[N];
map<pii,int>mp;bool vis[N];
void add(int x,int y,int z){
	nxt[++tot]=head[x];
	head[x]=tot;to[tot]=y;
	edge[tot]=z;
}
int find(int u){
	dfn[u]=++idx;
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(!dfn[v])fa[v]=u,find(v);
		else if(dfn[v]>dfn[u]){
			lp[++len]=v;
			for(;v!=u;v=fa[v])
				lp[++len]=fa[v];
		}
	}
}
void dfs(int u,int F,int fk){
	sm[u]=fk;siz[u]=1;
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(v==F||vis[v])continue;
		dfs(v,u,fk+edge[i]);
		sm[u]+=sm[v];siz[u]+=siz[v];		
	}
}
void dfs0(int u,int F,int vl,int sz,int Val){
	if(F!=0){
		nt[u]=nt[F]+(size-siz[u]-siz[u])*vl;
		ans[u]=nt[u]+Val;
	}
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(vis[v]||v==F)continue;
		dfs0(v,u,edge[i],sz,Val+sz*edge[i]);
	}
}
signed main(){
	scanf("%lld",&n);
	for(int i=1,x,y,z;i<=n;i++){
		scanf("%lld%lld%lld",&x,&y,&z);
		add(x,y,z);add(y,x,z);
		mp[pii(x,y)]=mp[pii(y,x)]=z;
	}
	find(1);int Sm=0;
	for(int i=1;i<=len;i++)vis[lp[i]]=1;
	for(int i=1;i<=len;i++){
		lp[i+len]=lp[i];
		dfs(lp[i],0,0);
		if(i==1)Sm+=mp[pii(lp[i],lp[len])];
		else Sm+=mp[pii(lp[i],lp[i-1])]; 
	}
	len<<=1;
	for(int i=2;i<=len;i++){
		dis[i]=mp[pii(lp[i],lp[i-1])];
		sum[i]=sum[i-1]+dis[i];
	}
	int dst=0,j=0,now=0,SZ=0;
	for(int i=len/2+1;i>=2;i--){
		now+=dst*siz[lp[i]]+sm[lp[i]];
		dst+=dis[i];
		SZ+=siz[lp[i]];
		if(dst>Sm/2){j=i;break;}
	}
	int gk=dst-dis[j];
	dst=0;
	for(int i=len/2+2;i<=j+len/2-1;i++){
		dst+=dis[i];
		now+=dst*siz[lp[i]]+sm[lp[i]];
	}dst=gk;
	ans[lp[1]]=now;
	for(int i=len/2+2;i<=len;i++){
		now+=SZ*dis[i];
		now-=(n-SZ)*dis[i];
		SZ+=siz[lp[i]];dst+=dis[i];
		while(dst>Sm/2){
			SZ-=siz[lp[j]];
			now-=sm[lp[j]]+siz[lp[j]]*dst;
			now+=siz[lp[j]]*(Sm-dst)+sm[lp[j]];
			dst-=dis[j+1];
			j++;
		}
		ans[lp[i]]=now;
	}
	for(int i=1;i<=len/2;i++){
		int tmp0=ans[lp[i]]-sm[lp[i]];
		nt[lp[i]]=sm[lp[i]];size=siz[lp[i]];
		dfs0(lp[i],0,0,n-siz[lp[i]],tmp0);
	}
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
	return puts(""),0;
}
```

---

## 作者：tder (赞：4)

前面的题解对于实现讲的较为详细，这里主要补充一下思维层面。

---

约定：

- $\text{dis}(i,j)$ 表示从第 $i$ 个点到第 $j$ 个点的最短距离；
- $\text{LCA}(i,j)$ 表示从第 $i$ 个点和第 $j$ 个点的最近公共祖先；
- $\text{deep}(i)$ 表示第 $i$ 个点的深度，根的深度为 $0$；
- $\text{root}(i)$ 表示第 $i$ 个点所在子树的根；
- $\text{size}(i)$ 表示以第 $i$ 个点为根的子树的大小；
- 基环树的边权为 $1$。

本题我们希望求得每个点到其余所有点的最短距离之和，即对于 $1\le i\le n$，试求 $\sum_{1\le j\ne i\le n}\text{dis}(i,j)$。

题目给定 $n$ 点 $n$ 边的无向图，即一棵基环树，我们将他画成如下图所示的「仙人掌」形状：

![](https://cdn.luogu.com.cn/upload/image_hosting/rud14d0m.png)

一棵基环树的主体由一个环组成，且这个环上的每个点均有一棵子树。

我们先考虑对于在同一子树上的两点 $i,j$ 间的最短距离，一条显然的路径是 $i\rightsquigarrow\text{LCA}(i,j)\rightsquigarrow j$。特别的，一个点 $i$ 到 $\text{root}(i)$ 的最短距离为 $\text{deep}(i)$。

接下来考虑不在同一子树上的两个点的最短距离，如下图所示是从第 $1$ 个点到第 $2$ 个点的一条最短路径。

![](https://cdn.luogu.com.cn/upload/image_hosting/rm0bn8qc.png)

总结起来，第 $i$ 个点到第 $j$ 个点的最短路径为 $i\rightsquigarrow\text{root}(i)\rightsquigarrow\text{root}(j)\rightsquigarrow j$，其长度为 $\text{deep}(i)+\text{dis}(\text{root}(i),\text{root}(j))+\text{deep}(j)$。

那么，一个环上的子树 $t$ 对第 $k$ 个点的答案的贡献为：

$$
\left(\sum_{\text{root}(i)=t}\text{deep}(i)\right)+\text{size}(t)\times\left(\text{dis}(t,\text{root}(k))+\text{deep}(k)\right)
$$

于是，我们得到了本题的大体做法：

1. 找环；
2. 计算 $\text{size}(i)$ 和 $\text{deep}(t)$，以及 $\left(\sum_{\text{root}(i)=t}\text{deep}(i)\right)$；
3. 对于环上的两点 $u,v$，计算 $\text{dis}(u,v)$；
4. 统计答案。

---

