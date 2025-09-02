# [POI 2014] HOT-Hotels 加强版

## 题目背景

同 [[POI2014]HOT-Hotels](https://www.luogu.com.cn/problem/P3565)，数据范围加大到 $1 \le n \le 10^5$。

来源于 BZOJ4543。

## 题目描述

给出一棵有 $n$ 个点的树，求有多少组点 $(i,j,k)$ 满足 $i,j,k$ 两两之间的距离都相等。  

$(i,j,k)$ 与 $(i,k,j)$ 算作同一组。

## 说明/提示

对于 $100\%$ 的数据， $1\le n\le10^5, 1\le a\le b\le n$。

## 样例 #1

### 输入

```
7
1 2
5 7
2 5
2 3
5 6
4 5
```

### 输出

```
5
```

# 题解

## 作者：xht (赞：52)

# 请到博客中查看

先考虑简单版的 $n \le 5 \times 10^3$ 怎么做。

设 $f_{i,j}$ 为满足 $x$ 在 $i$ 的子树中且 $d(x, i) = j$ 的 $x$ 的个数，$g_{i,j}$ 为满足 $x,y$ 在 $i$ 的子树中且 $d(\operatorname{lca}(x, y), x) = d(\operatorname{lca}(x, y), y) = d(\operatorname{lca}(x, y), i) + j$ 的无序数对 $(x,y)$ 的个数。

有转移：

$$
ans \leftarrow g_{i, 0}
$$

$$
ans \leftarrow \sum_{x,y \in \operatorname{son}(i), x \ne y} f_{x,j-1} \times g_{y,j+1}
$$

$$
g_{i,j} \leftarrow \sum_{x,y \in \operatorname{son}(i), x \ne y} f_{x,j-1} \times f_{y,j-1}
$$

$$
g_{i,j} \leftarrow \sum_{x \in \operatorname{son}(i)} g_{x, j+1}
$$

$$
f_{i,j} \leftarrow \sum_{x \in \operatorname{son}(i)} f_{x, j-1}
$$

显然这可以利用前缀和，或者说是所有儿子「向 $i$ 合并」，做到 $\mathcal O(n)$ 转移，总时间复杂度 $\mathcal O(n^2)$。

注意到这里的信息都是以深度为下标的，那么可以利用长链剖分将复杂度降为均摊 $\mathcal O(1)$，总时间复杂度即可降为 $\mathcal O(n)$。

在「直接继承重儿子的信息」时，需要用指针维护，具体见代码。

```cpp
const int N = 1e5 + 7;
int n, d[N], dep[N], son[N];
vi e[N];
ll *f[N], *g[N], p[N<<2], *o = p, ans;

void dfs(int x, int fa) {
	d[x] = d[fa] + 1;
	for (auto y : e[x])
		if (y != fa) {
			dfs(y, x);
			if (dep[y] > dep[son[x]]) son[x] = y;
		}
	dep[x] = dep[son[x]] + 1;
}

void dp(int x, int fa) {
	if (son[x])
		f[son[x]] = f[x] + 1, g[son[x]] = g[x] - 1, dp(son[x], x);
	f[x][0] = 1, ans += g[x][0];
	for (auto y : e[x])
		if (y != fa && y != son[x]) {
			f[y] = o, o += dep[y] << 1, g[y] = o, o += dep[y] << 1;
			dp(y, x);
			for (int i = 0; i < dep[y]; i++) {
				if (i) ans += f[x][i-1] * g[y][i];
				ans += g[x][i+1] * f[y][i];
			}
			for (int i = 0; i < dep[y]; i++) {
				g[x][i+1] += f[x][i+1] * f[y][i];
				if (i) g[x][i-1] += g[y][i];
				f[x][i+1] += f[y][i];
			}
		}
}

int main() {
	rd(n);
	for (int i = 1, x, y; i < n; i++)
		rd(x), rd(y), e[x].pb(y), e[y].pb(x);
	dfs(1, 0), f[1] = o, o += dep[1] << 1, g[1] = o, o += dep[1] << 1;
	dp(1, 0), print(ans);
	return 0;
}
```

---

## 作者：chen_qian (赞：30)

[题目链接](https://www.luogu.com.cn/problem/P5904)

[不会长链剖分的看看这个](https://www.luogu.com.cn/blog/sldts/shu-lian-pou-fen-di-er-tan-zhang-lian-pou-fen)

本题作为长链剖分优化DP的模板。本题解主要侧重于优化DP的思想。本题具体思路可能会稍略。

假如我们已经有一个满足条件的三元组 $\left(x,y,z\right)$ 这个三元组的组成方式只会有三种：

- $\left(x,y,z\right)$ 拥有共同的**LCA**，且距离**LCA**的距离都为 $d$。


- $\left(x,y,z\right)$ 其中两个拥有共同的**LCA**，且距离**LCA**的距离都为 $d$。


我们一般在子树里面处理问题更为方便快捷，所以我们把这四个点中的最浅的那个节点视为我们用于同级的一个标志性节点。

所以我们设 $g_{x,j}$ 表示 $x$ 的子树中，满足两个点到**LCA**的距离为 $d$，**LCA**距离 $x$ 为 $d-j$ 的点对数量。那么第三个点距 $x$ 的距离为 $j$。

那么这样的点对的数量和另外的单点满足条件的数量就是满足条件的数量。

所以我们设 $f_{x,j}$ 表示子树中距离 $x$ 长度为 $j$ 的点的数量
。

那么有两种情况可以来更新 $g_{x,j}$ ：

- 一个点位于当前子树，另一个点位于之前子树：$g_{x,j+1}=\sum_{y\in son(x)}f_{x,j+1} \times f_{y,j}$ 

注意这里的 $f_{x,j+1}$ 是将 $y$ 之前的子树合并后的答案。

- 在同一子树 $g_{x,j-1}=\sum_{y\in son(x)} g_{y,j}$ 

而 $f_{i,j+1}$ 的转移相对简单。

$f_{i,j+1}= \sum_{y \in son(x)} f_{y,j} $

接下来我们如何更新总的答案呢？

- 当 $j=0$ 即 $x$ 就是第三点。 $ans=ans+g_{x,0}$ 

- 否则分为当前子树提供点对和当前子树提供单点

$ans=ans+\sum_{y\in son(x)} g_{x,j+1} \times f_{y,j} + f_{x,j+1} \times g_{y,j}$

整体思路就是这样。

那么到底怎么长链剖分来优化呢？

可以看到的是，我们每次都要将一个有关子树深度的信息并到当前节点，且对应的位置只整体往后移动了一位。那么我们可不可以采取类似[dsu on tree](https://www.luogu.com.cn/blog/sldts/dsu-on-tree-xue-xi-bi-ji)的思路，保留一部分子树信息直接当做当前节点的信息呢？

所以我们直接让一个长链上的所有节点都储存在一个数组，全局维护一个数组 $tmp$，记录一个指针 $f[x]$ 指向 $x$ 的DP数组的开头位置，然后开头位置是其父亲节点的 $f[x]$ 的后一位，这样调用计算完子节点，在计算父亲时，就直接完成后移一位的操作。但不一定总是后移，看情况而定，比如这里的 $g$ 指针就是由于方程不同要前移。

如果是新链的话，就直接预留好空间即可。

这样说还是有点云里雾里，具体来看代码吧！

```
#include<bits/stdc++.h>
#define N 100005
#define ll long long
using namespace std;
ll tmp[N<<2];//只开一个全局 
int n;
ll *f[N],*g[N],*id=tmp;
int head[N],idx,dep[N],fa[N],son[N],mx[N];
ll ans=0;
struct edge{
	int v,next;
}e[2*N];
void add(int u,int v){
	e[++idx].v=v;
	e[idx].next=head[u];
	head[u]=idx;
}
void dfs1(int x,int f){
	fa[x]=f;
	dep[x]=dep[f]+1;
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].v;
		if(y==f) continue;
		dfs1(y,x);
		if(mx[son[x]]<mx[y]) son[x]=y;
	}
	mx[x]=mx[son[x]]+1;
}
void dfs2(int x){
	if(son[x]){
		f[son[x]]=f[x]+1;//指针加一 
		g[son[x]]=g[x]-1;
		dfs2(son[x]);
	}
	f[x][0]=1;
	ans+=g[x][0];
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].v;
		if(y==fa[x]||y==son[x]) continue;
		f[y]=id;
		id+=(mx[y]<<1);
		g[y]=id;
		id+=(mx[y]<<1);
		dfs2(y);
		for(int j=0;j<mx[y];j++){//了解指针的话这里可以直接当数组用 
			if(j) ans+=(f[x][j-1]*g[y][j]);
			ans+=g[x][j+1]*f[y][j];
		}
		for(int j=0;j<mx[y];j++){
			g[x][j+1]+=f[x][j+1]*f[y][j];
            if(j) g[x][j-1]+=g[y][j];
            f[x][j+1]+=f[y][j];	
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	dfs1(1,0);
	f[1]=id;
	id+=(mx[1]<<1);//预留空间，由于可能会左移和右移，开两倍空间。 
	g[1]=id;
	id+=(mx[1]<<1);
	dfs2(1);
	cout<<ans<<endl;
	return 0;
}
```




---

## 作者：LCuter (赞：26)


## [POI2014]Hot-Hotels 题解

##### $\text{Description}$

给定一棵树，求树上存在多少个三元组 $(a,b,c)$，满足 $\operatorname{dis}(a,b)=\operatorname{dis}(a,c)=\operatorname{dis}(b,v)$。

$n\le 10^5$

##### $\text{Solution}$

为了将来优化复杂度，我们先以 $1$ 为根。考虑满足条件的三元组会呈现什么样的形态：

![](https://lcuter.gitee.io/picture/Picture/clpf1.png)

对于第一种情况，我们容易想到令 $f_{i,j}$ 表示 $i$ 的子树中到 $i$ 距离为 $j$ 的节点个数。但是直接对每个节点的每个深度进行统计会重复，我们先来考虑第二种情况。考虑令 $g_{i,j}$ 表示 $i$ 的子树中，有多少二元组 $(a,b)$ 满足 $\operatorname{dis}(\operatorname{LCA}(a,b),a)=\operatorname{dis}(\operatorname{LCA(a,b),b})=\operatorname{dis}(\operatorname{LCA}(a,b),i)+j$。那么第一种情况可以看成：

![](https://lcuter.gitee.io/picture/Picture/clpf2.png)

这样的话，只需保证左边的节点和右边两个节点不在某一个点的同一个儿子的子树内，那么就不会被重复统计。

那么，节点 $now$ 对答案的贡献应是：

$$g_{now,0}+\sum_{j}\sum_{x,y\in son(now)}f_{x,j-1}\cdot g_{y,j+1}$$

上式的主要问题在于，我们要让左节点和右二节点不在同一个儿子的子树内，所以需要枚举不同的儿子进行统计，那么深度那一维也需要发生相应的改变。

$f$ 的转移比较容易：

$$f_{now,j}=\sum_{x\in son(now)}f_{x,j-1}$$

接下来考虑 $g$ 的转移。我们发现，$g$ 可以有两种从儿子转移的方式：

![](https://lcuter.gitee.io/picture/Picture/clpf3.png)

对于第一种情况，其实就是 $j$ 少了一个。对于第二种情况，发现 $\operatorname{LCA}(a,b)=now$，那么 $\operatorname{dis}(\operatorname{LCA}(a,b),a)=\operatorname{dis}(\operatorname{LCA}(a,b),b)=j$，然后 $now$ 到它本身的距离显然为 $0$，故就差了 $j$，于是有：

$$g_{now,j}=\sum_{x,y\in son(now),x\neq y}f_{x,j-1}\cdot f_{y,j-1}+\sum_{x\in son(now)}g_{x,j+1}$$

这样的话，我们得到了一个 $O(n^2)$ 的动态规划方程，但是要想达到这个复杂度需要用到前缀和，具体参考代码。

然后发现以深度为下标的话，可以使用长链剖分优化至 $O(n)$。具体请参考代码及代码注释。

##### $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define REG register
#define MAXN 100005
#define LL long long
#define FORE(i,now) for(REG int i=head[now];i;i=ed[i].nxt)
using namespace std;
inline int read(){
    REG int x(0);
    REG char c=getchar();
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)) x=(x*10)+(c^48),c=getchar();
    return x;
}

struct Edge{
    int v,nxt;
}ed[MAXN<<1];
int head[MAXN],cnt;
inline void adde(int u,int v){ed[++cnt]=(Edge){v,head[u]},head[u]=cnt;}
inline void add(int u,int v){adde(u,v),adde(v,u);}

int n;

LL *f[MAXN],*g[MAXN],*p,G[MAXN<<2],ans;
int Son[MAXN],Len[MAXN];

void dfs1(int now,int fa){
    FORE(i,now){
        int v=ed[i].v;
        if(v==fa) continue;
        dfs1(v,now);
        if(Len[v]>Len[Son[now]]) Son[now]=v;
    }
    Len[now]=Len[Son[now]]+1;
}

inline void Assign(int now){f[now]=p,p+=Len[now]<<1,g[now]=p,p+=Len[now]<<1;}

void dfs2(int now,int fa){
    if(Son[now])
        f[Son[now]]=f[now]+1,g[Son[now]]=g[now]-1,dfs2(Son[now],now);
    f[now][0]=1,ans+=g[now][0];
    FORE(i,now){
        int v=ed[i].v;
        if(v==fa||v==Son[now]) continue;
        Assign(v),dfs2(v,now);
        for(REG int j=0;j<Len[v];++j){
            if(j) ans+=f[now][j-1]*g[v][j]; // 这里含 now 的实际上是之前遍历过的儿子的 f[son][j-2] 之和 
            ans+=g[now][j+1]*f[v][j]; // 考虑到上式的前缀和没有计算后者，这里实际上就是在计算后者 
        }
        for(REG int j=0;j<Len[v];++j){
            g[now][j+1]+=f[now][j+1]*f[v][j];
            if(j) g[now][j-1]+=g[v][j];
            f[now][j+1]+=f[v][j];
        }
    }
}

void Work(){
    n=read();
    for(REG int i=1;i<n;++i)
        add(read(),read());
    dfs1(1,0);
    p=G,Assign(1);
    dfs2(1,0);
    printf("%lld\n",ans);
}

int main(){
    Work();
}
```


---

## 作者：Little09 (赞：15)

现有 $12$ 篇题解，全是指针。贡献第一个不用指针的题解。（~~其实是因为我不会用指针~~）

先考虑那个原题，也就是 $n\le 5000$。这部分跟大家思路差不多。我们设 $f_{i,j}$ 表示 $i$ 子树内和 $i$ 距离为 $j$ 的点数，$g_{i,j}$ 表示 $i$ 子树内满足再拼上距离为 $j$ 的一个点就可以构成合法三元组的点对个数。（形式化的定义可以参考其他题解）

转移都是简单的。考虑统计答案，考虑在三个点的 LCA 处统计答案。那么对于节点 $u$，我们把它的儿子按顺序扫过去，然后每次扫到 $v$ 的时候，合并 $f_u$ 与 $g_v$，以及 $g_u$ 与 $f_v$，就是答案了。因为每个三元组都可以拆成 “1+2” 的形式。

具体代码：

```cpp
void dfs(int x,int fa)
{
	f[x][0]=1;
	for (int i:t[x])
	{
		if (i==fa) continue;
		dfs(i,x);
		for (int j=0;j<n;j++)
		{
			ans+=1ll*f[x][j]*g[i][j+1];
			ans+=1ll*g[x][j+1]*f[i][j];
		}
		for (int j=1;j<=n;j++)
		{
			g[x][j]+=f[x][j]*f[i][j-1];
			g[x][j-1]+=g[i][j];
		}
		for (int j=1;j<=n;j++) f[x][j]+=f[i][j-1];
	}
}
```

这一步是简单的。不懂的可以参考现有其他题解。现在时空复杂度均为 $O(n^2)$，连原题都过不去。

考虑由于 $f$ 和 $g$ 的第二维都与深度有关（也就是，下标不会超过长链长度）。因此考虑长链剖分。我们每次继承重儿子的信息，再暴力合并轻儿子的信息。那么现在问题就是继承重儿子。

先把刚才的暴力套上一个长剖的模型，也就是先做重儿子，再做轻儿子，那么变成了这样：

```cpp
void dfs(int x,int fa)
{
	if (!son[x])
	{
		f[x][0]=1,g[x][0]=0;
		return;
	}
	dfs(son[x],x);
	f[x][0]=1;
	for (int j=1;j<=len[x];j++) f[x][j]=f[son[x]][j-1];
	for (int j=0;j<=len[x]-2;j++) g[x][j]=g[son[x]][j+1];
	// 上面两个 for 是暴力继承重儿子
	ans+=g[x][0];
	for (int i:t[x])
	{
		if (i==fa||i==son[x]) continue;
		dfs(i,x);
		for (int j=0;j<=len[i]-1;j++) ans+=1ll*f[x][j]*g[i][j+1];
		for (int j=0;j<=len[i];j++) ans+=1ll*g[x][j+1]*f[i][j];
		for (int j=0;j<=len[i];j++) g[x][j+1]+=f[x][j+1]*f[i][j];
		for (int j=0;j<=len[i]-1;j++) g[x][j]+=g[i][j+1];
		for (int j=0;j<=len[i];j++) f[x][j+1]+=f[i][j];
	}
}
```

问题就在两个 for 上：

- 对于 $f$，其实是长剖的经典套路。观察到 $f_u$ 其实是把重儿子的 $f$ 拿过来，再在开头插入一个 $0$。因此我们用 vector 反过来维护 $f$，就是在末尾插一个 $0$ 了。
- 对于 $g$，观察到 $g_u$ 其实是把重儿子的 $g$ 拿过来，删掉开头第一个数，然后再末尾插两个 $0$。但是 vector 不支持在开头删数，我们就打删除标记就行了。具体地，维护一个 $del_u$ 表示 $u$ 的 $g$ 前面删了几个数。

关于 $f$ 的反过来维护，只要把刚才代码里每个调用 $f_{x,y}$ 的地方都改成 $f_{x,len_x-y}$ 就行了。关于 $g$ 的删数维护，只要把刚才代码里每个调用 $g_{x,y}$ 的地方都改成 $g_{x,del_x+y}$ 就行了。所以事实上挺好改的。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
const int N=1e5+5;
vector<int>t[N],f[N],g[N];
int n,del[N],son[N],len[N];
ll ans;

void dfs1(int x,int fa)
{
	son[x]=0,len[x]=0;
	for (int i:t[x])
	{
		if (i==fa) continue;
		dfs1(i,x);
		if (len[i]>=len[son[x]]) son[x]=i,len[x]=len[i]+1;
	}
}
void dfs(int x,int fa)
{
	if (!son[x])
	{
		f[x].pb(1),g[x].pb(0);
		return;
	}
	dfs(son[x],x);
	swap(f[x],f[son[x]]),swap(g[x],g[son[x]]);
	f[x].pb(1);
	g[x].pb(0),g[x].pb(0);
	del[x]=del[son[x]]+1;
	ans+=g[x][del[x]];
	for (int i:t[x])
	{
		if (i==fa||i==son[x]) continue;
		dfs(i,x);
		for (int j=0;j<=len[i]-1;j++) ans+=1ll*f[x][len[x]-j]*g[i][del[i]+j+1];
		for (int j=0;j<=len[i];j++) ans+=1ll*g[x][del[x]+j+1]*f[i][len[i]-j];
		for (int j=0;j<=len[i];j++) g[x][del[x]+j+1]+=f[x][len[x]-j-1]*f[i][len[i]-j];
		for (int j=0;j<=len[i]-1;j++) g[x][del[x]+j]+=g[i][del[i]+j+1];
		for (int j=0;j<=len[i];j++) f[x][len[x]-j-1]+=f[i][len[i]-j];
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n;
	for (int i=1;i<n;i++)
	{
		int x,y;
		cin >> x >> y;
		t[x].pb(y),t[y].pb(x);
	}
	dfs1(1,0);
	dfs(1,0);
	cout << ans;
	return 0;
}
```


---

## 作者：圣嘉然 (赞：15)

本文大致分为两部分，第一部分为本题的 dp 过程以及优化，第二部分为本题指针分配内存的简单解释，以及一种相比较目前题解中出现的分配方式，更好理解，更不容易错的方式（大概

### chapter1：dp

在图上画几组合法的三元组后，你会发现合法的三元组一定形如这样：

![](https://s3.bmp.ovh/imgs/2021/10/c68318fa3c8ea8b4.png)

那么为了不重复计数，一个自然的想法是枚举他们的那个交点，即上图中黑色点，枚举黑色点，然后计数合法的三元组个数。

因为要距离相同，可以考虑设 $f(i, j)$ 表示 $i$ 子树内，距离 $i$ 为 $j$ 的点的个数，可以 $n^2$ 的 dp 出这个东西，因为点对是无序的，我们可以枚举第一个点所处的子树，维护后缀不同子树的无序点对个数，不妨设 $g(i, j)$ 表示 $i$ 子树内，目前已经合并的那些子树里，均距离 $i$ 为 $j$ 的无序点对个数，那么有如下转移：
$$
ans \leftarrow g(i, j) \times f(son, j - 1) \\
g(i, j) \leftarrow f(son, j - 1) \times suf(i, j) \\
suf(i, j) \leftarrow f(son, j - 1)
$$
实际上 $suf$ 就是根的 $f$，只不过为了更清晰的匹配 **已合并的子树** 所以写作 $suf$。

简单总结：

1. 枚举根。
2. 做 $n^2$ dp。（注意，$suf, g$ 仅在根的时候转移，别的时候只需要求 $f$）
3. 枚举根的子树，做上述合并，统计答案。

复杂度为 $n^3$。

注意到 $suf, g$ 只需要求出子树的 $f$ 即可，所以不需要每次枚举根后做 dp，可以换根 dp 来维护 $f$，这样每条边就不会被每个根统计一次，只会在儿子贡献给父亲，父亲贡献回儿子，以及一个点扫周围点统计答案时被使用，那么每次贡献都要枚举深度，所以总复杂度为 ${\mathcal O}(n^2)$，可以通过普通版本。

~~自己没有写，上述主要为口胡，如果有错还请指出~~。

接下来优化到 ${\mathcal O}(n)$ 需要有长链剖分优化的前置知识，建议做一下 [这道题](https://www.luogu.com.cn/problem/CF1009F)。

你会发现，欸？这个 $f$ 不就是那道题中的 $f$ 么？而且 $f, g, suf$ 下标都是深度，说不定也可以用长链剖分优化？

但是这个东西只能计算子树内的点对，而一旦我要统计父亲距离为 $j$ 的点，那每条边贡献一个 $n$ 的刨除复杂度，就又超时了。

主要问题在于这个 $g$ 没法快速统计这样的点对：

![](https://s3.bmp.ovh/imgs/2021/10/3da733aa952986fb.png)

为了为 $g$ 匹配上面的点就得知道父亲，而为了知道父亲就会超时，于是我们需要抛弃一开始枚举根时的 $g$ 状态定义，转而寻求一种可以快速计算这样点对的 $g$。

这题的状态定义很是不好想，大概是这样的：

![](https://s3.bmp.ovh/imgs/2021/10/d690bf7994360f77.png)

$g(i, j)$ 表示 $i$ 的子树里，有多少个点对，满足我给出一条 $j$ 的链，就可以组成合法三元组。

这个时候就可以快速处理之前不能处理的三元组了，我们可以在一个点统计 $g(i, 0)$，这就是之前那种难以处理的三元组个数了。

那么给出状态定义后，转移是不难写出来的：
$$
ans \leftarrow g(i, j) \times f(son, j - 1) + f(i, j - 1) \times g(son, j) + g(i, 0) \\
g(i, j) \leftarrow g(son, j + 1) + f(i, j) \times f(son, j - 1) \\
f(i, j) \leftarrow f(son, j - 1)
$$
那么这道题就可以用长链剖分优化了，需要注意的是 $g(i, j)$ 从 $g(son, j + 1)$ 转移而来，所以和长儿子共用应该是 `g[son[x]] = g[x] - 1`。

那么本题可以在 ${\mathcal O}(n)$ 的时间内解决。

### chapter2：指针分配内存

本题中，除了神仙的状态设计外，还有一大难点(细节点？)，就是指针的内存分配了，各种问题层出不穷，具体可见 [加强版](https://www.luogu.com.cn/problem/P5904) 的讨论区。

你的指针分配需要满足以下几点要求：

1. 不能太浪费，否则容易 MLE。
2. 不能太少，否则很容易冲突。

由于 $g$ 的减法，判断冲突十分麻烦，我们可以考虑一下对于一条长链，$f,g$ 在内存里到底如何使用，是什么样子 ($f$ 比较简单，就是从前往后的一截，就不画图了)：

![](https://s3.bmp.ovh/imgs/2021/10/3734ca382bd029f2.png)

$g$ 应该是这么使用的，长链不断往前分配，但是使用的时候你还需要给 $g(x)$ 腾出一些空间。画出这个图后，如何给 $g(x)$ 分配位置应该就不那么难了，既要让儿子可以往前匹配，不要占用别人的空间，又要让自己有足够的空间，才可以调用 $g(i, j)$，满足这两个要求就好了。

但是对于算不清楚位置的我，总容易冲突(两页 WA)，可以考虑更稳定一点的办法，因为长链间是独立的，那为什么不动态分配呢？每次进入一个长链的时候，我们用 `new` 给它申请它需要的空间，并让链顶的 $f, g$ 指针指向应该指向的位置，不就可以了吗？

具体的，一开始给 $1$ 分配内存可以写成：

```cpp
fmemchi[1] = new i64[idep[1]];
std::fill_n(fmemchi[1], idep[1], 0);
f[1] = fmemchi[1];
gmemchi[1] = new i64[idep[1] * 2];
std::fill_n(gmemchi[1], idep[1] * 2, 0);
g[1] = gmemchi[1] + idep[1] - 1;
```

将要递归进入长链的时候可以写成：

```cpp
fmemchi[y] = new i64[idep[y]];
std::fill_n(fmemchi[y], idep[y], 0);
f[y] = fmemchi[y];
gmemchi[y] = new i64[idep[y] * 2];
std::fill_n(gmemchi[y], idep[y] * 2, 0);
g[y] = gmemchi[y] + idep[y] - 1;
```

整体如下：

```cpp
// 头文件 + 快读等模板
// There is a holiness to the heart's affections.

using i64 = long long;
const int N = 1e5 + 5;

int n, idep[N], wson[N]; i64 *fmemchi[N], *f[N]; i64 *gmemchi[N], *g[N];
std::vector<int> G[N];

void pre(int x, int fax) {
    for (int y : G[x]) {
        if (y != fax) {
            pre(y, x);
            if (idep[y] > idep[wson[x]]) wson[x] = y;
        }
    }
    idep[x] = idep[wson[x]] + 1;
}

i64 ans;
void solv(int x, int fax) {
    if (wson[x]) {
        f[wson[x]] = f[x] + 1;
        g[wson[x]] = g[x] - 1;
        solv(wson[x], x);
    }

    ++f[x][0];
    
    for (int y : G[x]) {
        if (y != fax && y != wson[x]) {
            fmemchi[y] = new i64[idep[y]];
            std::fill_n(fmemchi[y], idep[y], 0);
            f[y] = fmemchi[y];
            gmemchi[y] = new i64[idep[y] * 2];
            std::fill_n(gmemchi[y], idep[y] * 2, 0);
            g[y] = gmemchi[y] + idep[y] - 1;
            solv(y, x);
            for (int j = idep[y]; j >= 1; --j) {
                ans += g[x][j] * f[y][j - 1] + f[x][j - 1] * g[y][j];
                g[x][j] += g[y][j + 1] + f[x][j] * f[y][j - 1];
                f[x][j] += f[y][j - 1];
            }
        }
    }
    ans += g[x][0]; // 放在递归之前也无所谓？因为递归不会改变 g[x][0] 
}

signed main() {
    n = read();
    for (int i = 1; i < n; ++i) {
        int a = read(), b = read();
        G[a].push_back(b), G[b].push_back(a);
    }
    pre(1, 0);
    fmemchi[1] = new i64[idep[1]];
    std::fill_n(fmemchi[1], idep[1], 0);
    f[1] = fmemchi[1];
    gmemchi[1] = new i64[idep[1] * 2];
    std::fill_n(gmemchi[1], idep[1] * 2, 0);
    g[1] = gmemchi[1] + idep[1] - 1;
    solv(1, 0);
    write(ans);
    
    for (int i = 1; i <= n; ++i) delete fmemchi[i], delete gmemchi[i];
}
// St. JR bless you
```



---

## 作者：sprads (赞：10)

### 前言

计数 DP。主要介绍状态转移方程是怎么推出来的。（~~蒟蒻想了巨久，希望能帮助后人~~）

### 状态

首先将 $1$ 号节点拎出来作为根，再进行 DP。

定义 $f_{x,j}$ 为以 $x$ 为根的子树中，离 $x$ 的距离为 $j$ 的节点的个数。

定义 $g_{x,j}$ 为在 $x$ 的子树中，存在点对 $y,z$ 满足它们到其 LCA 的距离都为 $d$ 且 $x$ 到它们的 LCA 的距离为 $d-j$ 的数量。（其实就是希望补上一条长度为 $j$ 的链后，存在三个点满足它们之间的距离两两相等）。

大致看下图理解 $g$（虚线表示**不一定直接**相连），$g_{x,j}$ 就是满足下图关系的 $y,z$ 的对数。

![](https://cdn.luogu.com.cn/upload/image_hosting/kmf2vr9u.png)

### 转移

$f_{x,j}$ 的转移显然，注意初始化 $f_{x,0}\gets 1$。

重点和难点在 $g_{x,j}$。分两种情况考虑：

- 从子节点 $y$ 继承。从 $y$ 到 $x$ 需要的链的长度减少 $1$，则 $g_{x,j}$ 需要加上 $g_{y,j+1}$。

- 让 $x$ 作为点对的 LCA。那么选择的点对 $y,z$ 会满足：
	- 存在于两个**不同的** $x$ 的子节点为根的子树中。
	- 到点 $x$ 的距离都为 $j$。

既然到 $x$ 的距离都为 $j$，那么就可以利用 $f$ 进行转移。

通过 $g$ 和 $f$，在转移的同时计算最终的答案即可（就是再找一个离 $x$ 的距离为 $j$ 的点进行匹配）。例如上图就可以有两组匹配 $(u_1,y,z)$ 和 $(u_2,y,z)$。  
**提示**：仔细想想就会发现**不需要**特别考虑向上还是向下匹配。

根据上面的转移，再注意一些边界的细节，即可写出 $O(n^2)$ 的代码：

```cpp
void dfs(int fa,int x){
	f[x][0] = 1;
	for(int i = head[x];i;i = Next[i]){
		int y = ver[i];
		if(y == fa)continue;
		dfs(x,y);
		for(int j = 0;j < n;j++){
			if(j)ans += g[x][j] * f[y][j - 1];//在已遍历的子树中，找 两个 节点匹配新遍历的子树中的 一个 节点
			ans += f[x][j] * g[y][j + 1];//反过来，在已遍历的子树中找 一个 节点匹配新遍历的子树中的 两个 节点
		}
		for(int j = 1;j <= n;j++){
			g[x][j - 1] += g[y][j];//继承子树中的答案
			g[x][j] += f[x][j] * f[y][j - 1];//x作为新的lca
			f[x][j] += f[y][j - 1];//f的转移
		}
	}
}
```

使用长链剖分进行优化。利用指针共用空间和 $O(1)$ 继承。注意到 $g$ 的指针会向负移动，所以要注意开**两倍**空间。

**提醒**：指针共用空间更要注意 DP 的边界问题。

```cpp
void dfs2(int fa,int x){
	f[x][0] = 1;
	if(!son[x])return;
	f[son[x]] = f[x] + 1;
	g[son[x]] = g[x] - 1;
	dfs2(x,son[x]);
	ans += g[x][0];//先计算了长儿子，长儿子也有贡献，相当于 f[x][0] 匹配 g[son[x]][1]
	for(int i = head[x];i;i = Next[i]){
		int y = ver[i];
		if(y == fa || y == son[x])continue;
		f[y] = now,now += 2 * d[y];
		g[y] = now,now += 2 * d[y];
		dfs2(x,y);
		for(int j = 0;j < d[y];j++){
			if(j)ans += f[x][j - 1] * g[y][j];
			ans += g[x][j + 1] * f[y][j];
		}
		for(int j = 1;j <= d[y];j++){
			g[x][j - 1] += g[y][j];
			g[x][j] += f[x][j] * f[y][j - 1];
			f[x][j] += f[y][j - 1];
		}
	}
}
```


---

## 作者：lmgoat (赞：10)

设 $LCA(x,y)$ 表示 $x$ 与 $y$ 的最近公共祖先，$dis(x,y)$ 表示 $x$ 到 $y$ 的树上唯一简单路径的距离。

以 $1$ 为根，设 $(i,j,k)$ 中 $j$ 的深度等于 $k$ 的深度。

可以把满足条件的三元组分为两类。

第一种情况 $j$ 和 $k$ 都在 $i$ 的子树内，也就是 $i$ 是 $LCA(j,k)$ 的祖先，这样的话就要求 $dis(i,LCA(j,k))=dis(j,LCA(j,k))=dis(k,LCA(j,k))$。

第二种情况 $j$ 和 $k$ 都不在 $i$ 的子树内，显然这种情况要求满足 $dis(j,LCA(j,k))=dis(k,LCA(j,k))=dis(i,LCA(i,j))+dis(LCA(i,j),LCA(j,k))$。

所以设 $f[i][j]$ 表示 $i$ 的子树中与 $i$ 的距离为 $j$ 的点的个数，$g[i][j]$ 表示 $x,y$ 在 $i$ 的子树中，且满足 $dis(x,LCA(x,y))=dis(y,LCA(x,y))=dis(i,LCA(x,y))+j$ 的数对 $(x,y)$ 的个数。可得：

$$ans=\sum_{i=1}^n{g[i][0]+\sum_{x,y\in son(i),x\not ={y}}{f[x][j-1]\cdot g[y][j+1]}}$$

考虑 $f$ 和 $g$ 的转移。

$f$ 的转移显然，$f[i][j]=\sum_{x\in son(i)}{f[x][j-1]}$。

$g$ 的转移有两种转移，在同一个儿子的子树内，在不同儿子的子树内。

$$g[i][j]=\sum_{x\in son(i)}{g[x][j+1]}+\sum_{x,y\in son(i),x<y}{f[x][j-1]\cdot f[y][j-1]}$$

在算两个不同儿子的贡献时用前缀和的思想优化一下，大概就是边算边加，就能 $O(n^2)$。

发现 $f$ 和 $g$ 的第二维都与深度有关，也可以对于重儿子把下标平移之后直接继承，对于轻儿子暴力转移。满足这个性质就可以长链剖分优化。就可以做到 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int read() {
	int x(0),f(0);
	char ch=getchar();
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
const int N=1000005;
int n,hed[N],nxt[N<<1],to[N<<1],cur,ans,orz[N<<2],dep[N],son[N];
int *f[N],*g[N],*now=orz;
void add(int x,int y) {to[++cur]=y,nxt[cur]=hed[x],hed[x]=cur;}
void dfs1(int x,int fa) {
	for(int i=hed[x],y;i;i=nxt[i]) {
		y=to[i];
		if(y==fa) continue;
		dfs1(y,x);
		if(dep[y]>dep[son[x]]) son[x]=y;
	}
	dep[x]=dep[son[x]]+1;
}
void dfs2(int x,int fa) {
	if(son[x]) {
		f[son[x]]=f[x]+1;
		g[son[x]]=g[x]-1;
		dfs2(son[x],x);
	}
	f[x][0]=1,ans+=g[x][0];
	for(int i=hed[x],y;i;i=nxt[i]) {
		y=to[i];
		if(y==fa||y==son[x]) continue;
		f[y]=now,now+=dep[y]<<1,g[y]=now,now+=dep[y]<<1;
		dfs2(y,x);
		for(int j=0;j<dep[y];++j) {
			if(i) ans+=f[x][j-1]*g[y][j];
			ans+=f[y][j]*g[x][j+1];
		}
		for(int j=0;j<dep[y];++j) {
			g[x][j+1]+=f[x][j+1]*f[y][j];
			f[x][j+1]+=f[y][j];
			if(i) g[x][j-1]+=g[y][j];
		}
	}
}
signed main() {
	n=read();
	for(int i=1;i<n;++i) {
		int x=read(),y=read();
		add(x,y),add(y,x);
	}
	dfs1(1,0);
	f[1]=now,now+=dep[1]<<1,g[1]=now,now+=dep[1]<<1;
	dfs2(1,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：H_Kaguya (赞：6)

为什么没有人来试一试 $O(N^2)$ 过掉这个题呢（（（

题意转化：  
若 $a, b, c$ 三个节点两两距离相同，则一定存在一个点 $u$ ，使得  
$$dis(a, u) = dis(b, u) = dis(c, u)$$

算法：  
到某个点的距离相同的问题，当然先考虑广搜。  
若节点 $u$ 的度为 $d$ ，将 $u$ 看做根节点，则可以将其子树分别编号为 $1 \sim d$ 。  
对于所有到节点 $u$ 的距离为 $L$ 的点，求的是从中任意选出三个且编号不同的方案数。  
使用 DP 。记 $dp[i][j]$ 为前 $i$ 种编号，选了 $j$ 个节点的方案数， $a[i]$ 表示编号 $i$ 的点有多少个。则显然有  
$$dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1] * a[i]$$
然后枚举遍历每一个节点和每一种深度即可。 

算法复杂度：  
不严谨的分析，时间复杂度为 $O(N^2)$ ，空间复杂度为线性。  
~~然后就很简单的用暴力 DP 水过了这道题。~~  
虽然跑的很慢，但是并不卡常。  
对 bool 数组进行压位，可以获得比以前高得多的效率（因为需要 memset ）  
最后附上代码  

------------

```cpp
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define sz 100001
struct site
{
	int ed, next;
};
struct site dld[sz << 1 | 1];
struct node
{
	int poi, own;
};
struct node sta[2][sz];
int n, now;
long long ans;
unsigned int yf[3175];
int fsl[sz], ds[sz], top[2];
int tim[2][sz];
long long dp[2][3];
int read();
void net(int, int);
void ts(int);
void sol(int);
int main()
{
	int x, y;
	n = read();
	for (int i = 1; i < n; ++i)
	{
		x = read(); y = read();
		net(x, y); net(y, x);
	}
	for (int i = 1; i <= n; ++i)
		if (ds[i] >= 3)
			ts(i);
	printf ("%lld\n", ans);
	return 0;
}

int read()
{
	int x = 0;
	char c;
	while (!isdigit(c = getchar()));
	do {
		x = (x << 3) + (x << 1) + (c & 15);
	}while (isdigit(c = getchar()));
	return x;
}

void net(int a, int b)
{
	++now; ++ds[a];
	dld[now].ed = b;
	dld[now].next = fsl[a];
	fsl[a] = now;
}

void ts(int a)
{
	memset(yf, 0, (n >> 3) + 1);
	yf[a >> 5] |= 1 << (a & 31);
	top[1] = 0;
	for (int i = fsl[a]; i; i = dld[i].next)
	{
		++top[1];
		yf[dld[i].ed >> 5] |= 1 << (dld[i].ed & 31);
		tim[1][top[1]] = 1;
		sta[1][top[1]].poi = dld[i].ed;
		sta[1][top[1]].own = top[1];
	}
	tim[1][0] = top[1];
	int now = 0, last = 1;
	while (tim[last][0] >= 3)
	{
		sol(last);
		top[now] = tim[now][0] = 0;
		for (int i = 1; i <= top[last]; ++i)
		{
			if (sta[last][i].own != sta[last][i - 1].own)
			{
				if (tim[now][0] && (!tim[now][tim[now][0]]))
					--tim[now][0];
				++tim[now][0];
				tim[now][tim[now][0]] = 0;
			}
			for (int j = fsl[sta[last][i].poi]; j; j = dld[j].next)
				if (!(yf[dld[j].ed >> 5] & (1 << (dld[j].ed & 31))))
				{
					yf[dld[j].ed >> 5] |= 1 << (dld[j].ed & 31);
					++top[now]; ++tim[now][tim[now][0]];
					sta[now][top[now]].poi = dld[j].ed;
					sta[now][top[now]].own = sta[last][i].own;
				}
		}
		while (tim[now][0] && (!tim[now][tim[now][0]]))
			--tim[now][0];
		now = last;
		last ^= 1;
	}
}

void sol(int a)
{
	int now = 0, last = 1;
	dp[1][0] = dp[1][1] = dp[1][2] = 0;
	for (int i = 1; i <= tim[a][0]; ++i)
	{
		dp[now][0] = dp[last][0] + tim[a][i];
		for (int j = 1; j < 3; ++j)
			dp[now][j] = dp[last][j] + dp[last][j - 1] * tim[a][i];
		now = last; last ^= 1;
	}
	ans += dp[last][2];
}

```


---

## 作者：_13858886080 (赞：5)

（本人刚学长链剖分，如果题解有错误，请指出，谢谢。）

在做此题前，推荐先做[这道题](https://www.luogu.com.cn/problem/P3565)。

在这道题的数据弱化版（也就是上面这个链接）中，我们已经知道了 $O(n^2)$ 的做法：枚举重心，暴力统计所有答案和，然后输出（~~不过不知道为什么很多人要在可以水过的弱化数据中打正解~~）。

然而 $O(n^2)$ 的时空复杂度是明显过不了 $10^5$ 的数据范围的。

所以我们需要 $O(n \log n)$ 或者 $O(n)$ 的做法。

这是一道树上题目，似乎具有无后效性，不难猜出来这是一道 dp 题。

而且这一道题让我们求三点之间距离两两相等的组数，与点与点之间距离有关的题目，可以用深度维护。

dp，深度，于是我们想到了一个~~冷门的~~算法：长链剖分。

这道题实际上是一道 dp 加上一些特殊优化（指长链剖分）的题目。

那我们就想出了思路，时间复杂度为 $O(n)$。 

以 $1$ 作为根节点建树，进行长链剖分。

设 $m_{i,j}$ 是以i节点为根的子树内离点 $i$ 距离为 $j$ 的点的个数。

而 $n_{i,j}$ 是对于每一个以 $i$ 节点为根的子树内离点 $i$ 距离为 $j$ 的点，它们和随意两点组成的所有组中，符合三点之间距离两两相等的组数。

利用这几个数据，当根节点为 $x$ 时，枚举子节点 $son$ 和距离 $j$，我们可以得出状态转移方程与更新答案 $ans$：

```
ans+=n[x][j]*m[son][j-1]+n[son][j]*m[x][j-1];

n[x][j]+=n[son][j+1]+m[x][j]*m[son][j-1];

m[x][j]+=m[son][j-1];

```

我们已经得出了 $O(n)$ 的时间复杂度，不过空间可能仍然为 $O(n^2)$ 。此题规定空间大小十分小，直接用数组会卡死。

这时，我们发现，虽然空间要开二维，但实际上真正有用的空间却十分有限，仔细推算后发现只有长链长度之和级别，也就是大致为 $O(n)$ 级别的。

于是我们想到了一个~~馊主意~~好办法：指针。

把数值记载在一个数组内，用两个指针数组指出m数组和n数组的位置。以求把空间复杂度压缩在 $O(n)$ 以内。

于是我们时空均为 $O(n)$ 的答案出来了。

详细注释我放在代码里了。（码风很烂，请多多包涵。）

```
#include<bits/stdc++.h>
//#define int long long
//如果怕炸int可以把上面的注释去掉
using namespace std;
inline int read(){//快读
    int p=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}
    return f*p;
}
int a,ans;//a是节点个数，ans是答案
int fir[1000005],nex[1000005],son[1000005],tot;
inline void add(int z,int x){son[++tot]=x;nex[tot]=fir[z];fir[z]=tot;}
//邻接表建图（已经是基操了）
int fa[1000005],shen[1000005],daxiao[1000005],zhongson[1000005];
//fa指父亲，shen指节点深度（本能性的打上了，不过在本题似乎没用）
//daxiao指长链的长度（我是拼音党）zhongson指重儿子（重son）
int re[4000005];
int *m[1000005],*n[1000005],*mn=re;
//指针流，re记录数值，m指针和n指针的意义看讲解，mn指向当前指针更新的位置
inline void sou1(int z,int x){//寻找重儿子和长链
	fa[z]=x;shen[z]=shen[x]+1;//这行没用，请忽略
	for(int i=fir[z];i>0;i=nex[i])if(son[i]!=x){//寻找所有子节点
		sou1(son[i],z);//搜索此节点的子树
		if(daxiao[son[i]]>daxiao[zhongson[z]])zhongson[z]=son[i];//找重儿子
	}
	daxiao[z]=daxiao[zhongson[z]]+1;//记录长链长度
}
void caozuo(int z){
	m[z]=mn;mn+=daxiao[z]*2;//找到m指针后更新mn，为前后的长链留空间
	n[z]=mn;mn+=daxiao[z]*2;//找到n指针后更新mn，为前后的长链留空间
}
inline void sou2(int z,int x){//寻找m，n和答案
	if(zhongson[z]){m[zhongson[z]]=m[z]+1;n[zhongson[z]]=n[z]-1;sou2(zhongson[z],z);}//先寻找长链与重儿子的内容
	m[z][0]=1;ans+=n[z][0];//处理重儿子对指针和答案带来的影响
	for(int i=fir[z];i;i=nex[i])if(son[i]!=x&&son[i]!=zhongson[z]){//遍历所有轻儿子
		caozuo(son[i]);sou2(son[i],z);//搜索轻儿子的子树
		for(int j=1;j<=daxiao[son[i]];j++)//遍历轻儿子的长链
		ans+=n[z][j]*m[son[i]][j-1]+n[son[i]][j]*m[z][j-1],//计算，更新答案
		n[z][j]+=n[son[i]][j+1]+m[z][j]*m[son[i]][j-1];//更新n指针指向的内容
		for(int j=1;j<=daxiao[son[i]];j++)
		m[z][j]+=m[son[i]][j-1];//更新m指针指向的内容
	}
}
signed main(){
	cin>>a;
	for(int i=1;i<a;i++){int z=read(),x=read();add(z,x);add(x,z);}//输入
	sou1(1,0);//第一次搜索，寻找重儿子和长链
	caozuo(1);//对根节点进行处理
	sou2(1,0);//在dfs中寻找答案
	cout<<ans;//输出
	return 0;
}
```

---

## 作者：Leasier (赞：3)

前置芝士：[树形 dp](https://oi-wiki.org/dp/tree/)、[长链剖分](https://oi-wiki.org/graph/hld/#长链剖分)

注意到所求的 $(u, v, w)$ 可以通过重排 $u, v, w$ 的顺序表示为：

![](https://cdn.luogu.com.cn/upload/image_hosting/gz8m7cq1.png)

考虑 dp，设 $f_{u, i}$ 表示 $u$ 子树中距 $u$ 为 $i$ 的点数，$g_{y, i}$ 表示在 $y$ 子树内选取上图中的 $u, v$ 且上图中 $d - x = i$ 的方案数。

对于 $f_{u, i}$，显然有：

- $i = 0$ 时，$f_{u, i} = 1$。
- $i > 0$ 时，$f_{u, i} = \displaystyle\sum_{v \in son_u} f_{v, i - 1}$。

对于 $g_{y, i}$，有两种情况：

- 令 $y = lca(u, v)$，此时 $g_{y, i} \leftarrow g_{y, i} + \displaystyle\sum_{z \in son_y} f_{z, i - 1} \sum_{w \in son_y}^{z - 1} f_{w, i - 1}$。
- 以 $y$ 子树中某个点作为上图中 $lca(u, v)$，此时 $g_{y, i} \leftarrow g_{y, i} + \displaystyle\sum_{z \in son_y} g_{z, i + 1}$。

直接做是 $O(n^2)$ 的，显然不能接受。

$f_{u, i}$ 显然可以长链剖分优化，现在考虑 $g_{y, i}$。

对于第一种转移，考虑对轻儿子用子树前缀和转移；对于第二种转移，显然可以对重儿子内存移位、对轻儿子暴力转移实现。

现在考虑计算答案。有两种情况：

- $lca(u, v) = lca(u, v, w) = w$

此时贡献为 $g_{y, 0}$。

- 其他情况

此时贡献为 $\displaystyle\sum_{i = 1} ((\sum_{z \in son_y} f_{y, i - 1} \sum_{w \in son_y}^{z - 1} g_{w, i - 1})  + (\sum_{z \in son_y} g_{y, i - 1} \sum_{w \in son_y}^{z - 1} f_{w, i - 1}))$。

在转移时统计贡献即可。时间复杂度为 $O(n)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

typedef struct {
	int nxt;
	int end;
} Edge;

int cnt = 0;
int head[100007], fa[100007], depth[100007], max_depth[100007], hs[100007], top[100007], dp1[100007], *p1 = dp1, *dp2[100007];
ll dp3[200007], *p2 = dp3, *dp4[100007];
Edge edge[200007];

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

void dfs1(int u, int father){
	fa[u] = father;
	depth[u] = max_depth[u] = depth[father] + 1;
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != father){
			dfs1(x, u);
			if (max_depth[u] < max_depth[x]){
				max_depth[u] = max_depth[x];
				hs[u] = x;
			}
		}
	}
}

void dfs2(int u, int cur_top){
	top[u] = cur_top;
	if (hs[u] != 0){
		dfs2(hs[u], cur_top);
		for (register int i = head[u]; i != 0; i = edge[i].nxt){
			int x = edge[i].end;
			if (x != fa[u] && x != hs[u]) dfs2(x, x);
		}
	}
}

ll dfs3(int u){
	ll ans = 0;
	dp2[u][0] = 1;
	if (hs[u] != 0){
		dp2[hs[u]] = dp2[u] + 1;
		dp4[hs[u]] = dp4[u] - 1;
		ans += dfs3(hs[u]);
		ans += dp4[u][0];
		for (register int i = head[u]; i != 0; i = edge[i].nxt){
			int x = edge[i].end;
			if (x != fa[u] && x != hs[u]){
				int t = max_depth[x] - depth[x] + 1;
				dp2[x] = p1;
				p1 += t;
				p2 += t;
				dp4[x] = p2;
				p2 += t;
				ans += dfs3(x);
				for (register int j = 1; j <= t; j++){
					int jd = j - 1;
					ans += dp2[u][jd] * dp4[x][j] + dp2[x][jd] * dp4[u][j];
				}
				for (register int j = 1; j <= t; j++){
					dp4[u][j] += (ll)dp2[u][j] * dp2[x][j - 1];
					if (j < t) dp4[u][j] += dp4[x][j + 1];
				}
				for (register int j = 1; j <= t; j++){
					dp2[u][j] += dp2[x][j - 1];
				}
			}
		}
	}
	return ans;
}

int main(){
	int n;
	scanf("%d", &n);
	for (register int i = 1; i < n; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		add_edge(x, y);
		add_edge(y, x);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	dp2[1] = p1;
	p1 += max_depth[1];
	p2 += max_depth[1];
	dp4[1] = p2;
	p2 += max_depth[1];
	printf("%lld", dfs3(1));
	return 0;
}
```

---

## 作者：crs_line (赞：2)

$\large{题目描述}$
>给定一棵$n$节点的树，在树上选$3$个点，要求两两距离相等，求方案数。  
>$Ordinary\colon n\le 5000，Enhanced\colon n\le 100000$   
>$Timelimit\colon 1000ms，Memorylimit\colon 62.5MB$  

$\large{解题分析}$  

首先我们考虑满足要求的点对 $\left[x,y,z\right]$ 的特点，我们设 $x,y$ 为三者中深度较大者，$top$ 为 $x,y$ 的 $lca$，若有 $dis_{x,y}=dis_{y,z}=dis_{z,x}$，则可得出 $dis_{x,top}=dis_{y,top}=dis_{z,top}$，我们发现只会有两种结构满足此特点：$lca_{x,z}=lca_{y,z}=top$ 或 $z\in fa_{top}$，就可以设计对应解法了。  

$Solution-1$  

考虑搜索，容易发现可以通过枚举中间点的方式，从该点作为根，遍历其每棵子树，每次向外扩展一层，记录对应子树内距离中间点为 $dis_i$ 的点数，每次任选三棵子树合并统计答案即可，时间复杂度 $O(n^2)$，空间复杂度 $O(n)$，可以通过初始数据。   

$Solution-2$  

考虑 dp，我们容易发现本题结果与距离以及 $lca$ 有关，考虑分两个状态分别 dp，记 $f_{i,j}$ 为在 $i$ 节点的子树内，与 $i$ 的距离为 $j$ 的点数，$g_{i,j}$ 为在 $i$ 节点的子树内，满足有 $dis_{x,lca_{x,y}}=dis_{y,lca_{x,y}}=dis_{i,lca_{x,y}}+j$ 的点对 $\left(x,y\right)$ 数量。  

我们有以下转移： 
$$ f_{i,j}=\sum\limits_{x\in son_{i}}f_{x,j-1}$$
$$ g_{i,j}=\sum\limits_{x\in son_{i}}g_{x,j+1}+\sum\limits_{x,y\ \in son_{i}\ \land\ x \neq y}f_{x,j-1}\times f_{y,j-1}$$
同时也有类似的统计答案：

$$ ans=\sum\limits_{x,y\ \in son_{i}\ \land\ x \neq y}f_{x,j-1}\times g_{y,j+1}$$  

我们发现可现顺序枚举子树，维护 $f_{x,j-1}$ 的前缀和，钦定当前枚举的子树 $i$ 必选，每次将前者的信息与 $i$ 点合并。整个过程只有枚举距离与遍历子树，时间复杂度 $O(n^2)$。 

然而我们在 MLE 了几次后不得不重新审视 62.5MB 的有限空间，在状态数无法缩减的前提下考虑如何重复利用空间，利用 dsu on tree 的思想，我们对整棵树进行重链剖分，求出每个点的重儿子，(在这里引用重儿子的性质，由于任何一个轻儿子 $i$ 都满足 $size_i\le\frac{size_{fa}}{2}$ ，每遍历轻儿子都会使树的大小减半，故最多只会有 $\log n$ 条重链与 $\log n$ 个轻儿子)，每次我们将父节点的数组传给重儿子使用，轻儿子重新申请内存，这样整个过程最多只会同时存在 $\log n$ 个状态数组，空间复杂度优化到 $O(n\log n)$。

对于下放重儿子的操作，我们采用传指针的方式，同时对于每个轻儿子，递归返回两个数组，在父亲处合并。同时发现，传给重儿子的 $f$ 与 $g$ 数组可以通过控制位置实现信息直接覆盖，最后不要忘了释放空间。  

这时候我们已经可以完美通过初始数据，但考虑继续优化，不难发现 dp 状态本质上只与深度有关，因此我们改用长链剖分，每次只合并有限深度，类比上文所谈及的重链剖分的性质，我们不难推出，时间复杂度优化到 $O(n)$，此时本题得到完美解决。  

最后放上本题完整 code

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=100003;
inline int read()
{
    int x=0,f=1; char c;
    while(!isdigit(c=getchar())) if(c=='-') f=-1;
    do x=(x<<1)+(x<<3)+(c^48); while(isdigit(c=getchar()));
    return x*f;
}
int H,kk;
long long ans;
int head[N],son[N],dep[N];
struct node{int next,to;}edge[N<<1];
void add(int x,int y)
{
    edge[++kk].to=y;
    edge[kk].next=head[x];
    head[x]=kk;
}
void Pre_process(int nn,int fa)
{
    son[nn]=0;
    for(int i=head[nn];i;i=edge[i].next)
    {
        int cc=edge[i].to;
        if(cc==fa) continue;
        Pre_process(cc,nn);
        if(dep[son[nn]]<dep[cc]) son[nn]=cc;
    }
    if(!son[nn]) dep[nn]=1;
    else dep[nn]=dep[son[nn]]+1;
}
pair<long long*,long long*>Con_program(long long *F,long long *G,int nn,int fa)
{
    pair<long long*,long long*>now;
    if(!F) F=new long long[dep[nn]<<1]()+dep[nn];
    if(!G) G=new long long[dep[nn]<<1]()+dep[nn];
    F[0]=1;
    if(son[nn])
    {
        Con_program(F+1,G-1,son[nn],nn);
        ans+=G[0];
    }
    for(int i=head[nn];i;i=edge[i].next)
    {
        int cc=edge[i].to;
        if(cc==fa||cc==son[nn]) continue;
        now=Con_program(nullptr,nullptr,cc,nn);
        for(int j=0;j<=dep[cc]-1;j++)
        {
            if(j) ans+=F[j-1]*(now.second[j]);
            ans+=G[j+1]*(now.first[j]);
        }
        for(int j=0;j<=dep[cc]-1;j++)
        {
            G[j+1]+=F[j+1]*now.first[j];
            G[j]+=now.second[j+1];
            F[j+1]+=now.first[j];
        }
        delete[] (now.first-dep[cc]);
        delete[] (now.second-dep[cc]);
    }
    return make_pair(F,G);
}
signed main()
{
    H=read();
    for(int i=1;i<H;i++)
    {
        int x=read(),y=read();
        add(x,y); add(y,x);
    }
    Pre_process(1,0);
    Con_program(nullptr,nullptr,1,0);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Rubyonly (赞：2)

给定一棵 $n$ 个点的树，求树上满足两两距离相等的 $(x,y,z)$ 无序点对个数

长链剖分板子题

考虑一个合法的三元组，三个点在一条链上显然是不合法的，只会是下面的情况

![](https://images.cnblogs.com/cnblogs_com/Rubyonly233/1923430/o_210403121823Screenshot_2021-04-03%20Graph%20Editor.png)

我们定义两个 $dp$ 数组

$f[u][i]$ 表示以 $u$ 为根的子树内，距 $u$ 节点距离为 $i$ 的点有多少个

$g[u][i]$ 表示以 $u$ 为根的子树内，$dis(lca(x,y),x)=dis(lca(x,y),y)=dis(lca(x,y),u)+i$ 点对 $(x, y)$ 有多少个

显然我们可以利用这两个数组来统计答案

假设我们现在 $DFS$ 到了 $u$ 节点，枚举到了它的儿子 $v$，可以统计 $v$ 的子树和之前遍历过的 $u$ 的儿子造成贡献，转移如下

$$g[u][j]\times f[v][j - 1] \rightarrow ans $$

$$g[v][j]\times f[v][j + 1] \rightarrow ans $$

$$g[v][j] \rightarrow g[u][j - 1]$$

$$f[u][j]\times f[v][j - 1] \rightarrow g[u][j]$$

$$f[v][j] \rightarrow f[u][j+1]$$

注意转移顺序不能乱，然后这样转移是 $\Theta (n)$，整体复杂度是 $\Theta (n^2)$ 的

考虑如何用长剖进行优化，首先我们将二维数组开成指针，使得空间优化成 $\Theta (n)$ 的

对于重儿子我们直接用指针 $\Theta (1)$ 转移过来，轻儿子向 $\Theta (n^2)$ 的做法一样暴力转移就行了，所以总复杂度是 $\Theta (n)$

```c++
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

#define ll long long
#define rint register int 
#define rll register long long

using namespace std;

const int maxn = 1e6 + 50, INF = 0x3f3f3f3f;

inline int read () {
	rint x = 0, w = 1;
	char ch = getchar ();
	for (; ch < '0' || ch > '9'; ch = getchar ()) if (ch == '-') w = -1;
	for (; ch >= '0' && ch <= '9'; ch = getchar ()) x = x * 10 + ch - '0';
	return x * w;
}

int n;
ll *f[maxn], *g[maxn], buf[maxn << 2], *p = buf, ans;

struct Edge {
	int to, next;
} e[maxn << 1];

int tot, head[maxn];

inline void Add (rint u, rint v) {
	e[++ tot].to = v;
	e[tot].next = head[u];
	head[u] = tot;
}

int len[maxn], son[maxn];

inline void DFS0 (rint u, rint fa) {
	len[u] = 1;
	for (rint i = head[u]; i; i = e[i].next) {
		rint v = e[i].to;
		if (v == fa) continue;
		DFS0 (v, u), len[u] = max (len[u], len[v] + 1);
		if (len[v] > len[son[u]]) son[u] = v;
	}
}

inline void DFS1 (rint u, rint fa) {
	if (son[u]) {
		f[son[u]] = f[u] + 1;
		g[son[u]] = g[u] - 1;
		DFS1 (son[u], u);
	}
	f[u][0] = 1, ans += g[u][0];
	for (rint i = head[u]; i; i = e[i].next) {
		rint v = e[i].to;
		if (v == fa || v == son[u]) continue;
		f[v] = p, p += len[v] << 1;
		g[v] = p, p += len[v] << 1;
		DFS1 (v, u);
		for (rint j = 1; j <= len[v]; j ++) 
			ans += g[u][j] * f[v][j - 1] + g[v][j] * f[u][j - 1];
		for (rint j = 1; j <= len[v]; j ++) 
			g[u][j] += g[v][j + 1];
		for (rint j = 1; j <= len[v]; j ++) 
			g[u][j] += f[u][j] * f[v][j - 1];
		for (rint j = 1; j <= len[v]; j ++) 
			f[u][j] += f[v][j - 1];
	}	
}

int main () {
	n = read();
	for (rint i = 1, u, v; i <= n - 1; i ++) 
		u = read(), v = read(), Add (u, v), Add (v, u);
	DFS0 (1, 0);
	f[1] = p, p += len[1] << 1;
	g[1] = p, p += len[1] << 1;
	DFS1 (1, 0);
	printf ("%lld\n", ans);
	return 0;
}
```

---

## 作者：WrongAnswer_90 (赞：0)

自然的想法是枚举共同的交点，然后进行换根 dp，复杂度可以做到 $\mathcal O(n^2)$，可以通过简单版，但是显然过不了 $10^5$ 的数据，考虑进行优化。

![image.png](https://s2.loli.net/2023/08/25/IzrN8lZPte1UuYD.png)

记 $(x,y,z)$ 为满足要求的点，即满足 $a=b+c$，树形 dp 原则是子树内的信息无后效性，尽量把子树内的信息合并在一起。所以 $a-b=c$，在这个等式种，$a-b$ 和 $c$ 在以 $2$ 为根的两棵不同子树，所以转变统计方式，在 $2$ 号统计答案。

设计状态 $g_{i,j}$ 表示 $i$ 子树内部满足 $a-b=j$ 的点对数量，因为要统计 $z$ 的数量，所以设 $f_{i,j}$ 表示 $i$ 子树内和 $i$ 距离为 $j$ 的点的个数。

状态明确了，方程是容易设计的：

$$
\begin{aligned}
f_{i,j}&=\sum_{u \in son_i}f_{u,j-1} \\

g_{i,j}&=\sum_{u \in son_i}g_{u,j+1}+f_{i,j}\times f_{u,j-1}\\

ans&=\sum_{u \in son_i}f_{i,j-1}\times g_{u,j}+g_{i,j}\times f_{u,j-1}
\end{aligned}
$$

直接 dp 复杂度仍然是 $\mathcal O(n^2)$ 的，但是发现状态中 $j$ 只和深度有关，考虑使用长链剖分优化 dp。

观察方程，当只有一个儿子 $u$ 时，可以简化为：


$$
\begin{aligned}
f_{i,j}&=f_{u,j-1} \\

g_{i,j}&=g_{u,j+1} \\

ans&=g_{i,0}
\end{aligned}
$$

可以把重儿子的 dp 值平移一下直接给父亲用，具体实现使用指针，详见代码。

```cpp
int n,head[100005],dep[100005],to[200005],son[100001],nex[200001],a[100001],cnt;
ll ans,*g[100005],*f[100005],p[400050],*o=p;
inline void add(int x,int y){to[++cnt]=y,nex[cnt]=head[x],head[x]=cnt;}
void dfs1(int k,int fa)
{
	dep[k]=1;
	for(int i=head[k];i;i=nex[i])
	{
		if(to[i]==fa)continue;
		dfs1(to[i],k);
		if(dep[to[i]]+1>dep[k])dep[k]=dep[to[i]]+1,son[k]=to[i];
	}
}
void dfs(int k,int fa)
{
	if(son[k])f[son[k]]=f[k]+1,g[son[k]]=g[k]-1,dfs(son[k],k);
	f[k][0]=1,ans+=g[k][0];
	for(int i=head[k];i;i=nex[i])
	{
		if(to[i]==fa||to[i]==son[k])continue;
		f[to[i]]=o,o+=dep[to[i]]<<1,g[to[i]]=o,o+=dep[to[i]]<<1,dfs(to[i],k);
		for(int j=0;j<dep[to[i]];++j)
		{
			if(j)ans+=f[k][j-1]*g[to[i]][j];
			ans+=g[k][j+1]*f[to[i]][j];
		}
		for(int j=0;j<dep[to[i]];++j)
		g[k][j+1]+=f[k][j+1]*f[to[i]][j],
		f[k][j+1]+=f[to[i]][j],
		g[k][j]+=g[to[i]][j+1];
	}
}
inline void mian()
{
	read(n);int x,y;
	for(int i=1;i<n;++i)read(x,y),add(x,y),add(y,x);
	dfs1(1,0),f[1]=o,o+=dep[1]<<1,g[1]=o,o+=dep[1]<<1,dfs(1,0),write(ans);
}
```

---

