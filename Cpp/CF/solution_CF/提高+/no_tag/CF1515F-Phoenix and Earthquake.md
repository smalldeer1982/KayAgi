# Phoenix and Earthquake

## 题目描述

Phoenix's homeland, the Fire Nation had $ n $ cities that were connected by $ m $ roads, but the roads were all destroyed by an earthquake. The Fire Nation wishes to repair $ n-1 $ of these roads so that all the cities are connected again.

The $ i $ -th city has $ a_i $ tons of asphalt. $ x $ tons of asphalt are used up when repairing a road, and to repair a road between $ i $ and $ j $ , cities $ i $ and $ j $ must have at least $ x $ tons of asphalt between them. In other words, if city $ i $ had $ a_i $ tons of asphalt and city $ j $ had $ a_j $ tons, there would remain $ a_i+a_j-x $ tons after repairing the road between them. Asphalt can be moved between cities if the road between them is already repaired.

Please determine if it is possible to connect all the cities, and if so, output any sequence of roads to repair.

## 说明/提示

In the first example, the roads are repaired in the following order:

- Road $ 3 $ is repaired, connecting cities $ 3 $ and $ 4 $ . City $ 4 $ originally had $ 4 $ tons of asphalt. After this road is constructed, $ 3 $ tons remain.
- Road $ 2 $ is repaired, connecting cities $ 2 $ and $ 3 $ . The asphalt from city $ 4 $ can be transported to city $ 3 $ and used for the road. $ 2 $ tons remain.
- Road $ 1 $ is repaired, connecting cities $ 1 $ and $ 2 $ . The asphalt is transported to city $ 2 $ and used for the road. $ 1 $ ton remain.
- Road $ 4 $ is repaired, connecting cities $ 4 $ and $ 5 $ . The asphalt is transported to city $ 4 $ and used for the road. No asphalt remains.

 All the cities are now connected.In the second example, cities $ 1 $ and $ 2 $ use all their asphalt together to build the road. They each have $ 1 $ ton, so together they have $ 2 $ tons, which is enough.

In the third example, there isn't enough asphalt to connect cities $ 1 $ and $ 2 $ .

## 样例 #1

### 输入

```
5 4 1
0 0 0 4 0
1 2
2 3
3 4
4 5```

### 输出

```
YES
3
2
1
4```

## 样例 #2

### 输入

```
2 1 2
1 1
1 2```

### 输出

```
YES
1```

## 样例 #3

### 输入

```
2 1 2
0 1
1 2```

### 输出

```
NO```

## 样例 #4

### 输入

```
5 6 5
0 9 4 0 10
1 2
1 3
2 3
3 4
1 4
4 5```

### 输出

```
YES
6
4
1
2```

# 题解

## 作者：ix35 (赞：36)

题意：

有 $n$ 个点，每个点有点权，另有 $m$ 条边和定值 $x$，你需要选择一个生成树和一个树边的顺序，使得按照这个顺序建树，建每条边时两边连通块的点权和不小于 $x$；建立一条边后新连通块的点权和要减少 $x$。

---

题解：

个人觉得是这场 CGR 最有趣（可能也是唯一有趣的）的题目！

首先，如果图不连通，或者所有点权和不到 $(n-1)\times x$，那么无解。

否则，我们证明：

**对于任意一棵生成树，都存在一种合法的修建方案。**

证明是归纳的：

在 $n$ 个点的树中，我们先随便选出一个叶子，考虑其点权 $a_u$：

1. $a_u\ge x$，那么我们最早修建 $u$ 和其父亲的边，将它们缩成一点，然后转化成 $n-1$ 个点的树，仍然满足条件。

2. $a_u<x$，那么我们如果从树中删除这个叶子和其父边，因为 $(n-1)\times x$ 减少了 $x$ 而点权减少了 $a_u$，所以剩余树仍然满足条件，所以我们把这条边最后修建即可。

所以做法就很简单了！

我们先随便选出一个生成树，进行一次 DFS，如果一个点 $u$ 的父亲为 $v$，当前 $u$ 的子树访问完毕，那么分类讨论：

- 如果当前 $a_u\ge x$，那么令 $a_v\leftarrow a_v+a_u-x$，将 $(v,u)$ 加入一个队列中。

- 如果当前 $a_u<x$，那么将 $(v,u)$ 加入一个栈中。

- 最后先按序输出队列中的边，再按序输出栈中的边，即可。

---

## 作者：pigstd (赞：9)

[宣传博客。](https://www.cnblogs.com/juruo-pigstd/p/14663958.html)

先考虑无解。

一个显然的事实是：如果 $\displaystyle \sum_{i=1}^n a_i < x\times (n-1)$ 或者这个图不连通，那就是无解。

手玩一下发现除此之外没有无解的情况了。尝试证明一个非常强的结论：每一个生成树，只要满足 $\displaystyle \sum_{i=1}^n a_i \ge x\times (n-1)$，那就是有解的。

考虑归纳的证明：对于叶子节点 $u$：

- $a_u \ge x$，那么连上 $u \to fa_u$ 的边就可以了。
- $a_u < x$，那么删去点 $u$ 后剩下的 $n-1$ 个节点的树，根据归纳假设，命题得证。

那么构造也很好构造了，按照上述方法构造就行了：先找一个生成树，对于每个节点，先遍历他所有儿子，然后对于这个点 $u$，如果 $a_u \ge x$ 那么就把这个点以及其父亲的边选上，否则就放在最后选。非常好写。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define mp make_pair
#define x first
#define y second
using namespace std;

inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}

const int M=3e5+10;
int n,m,x,a[M],f[M],ans[M],cnt,cnt2;
struct edge{int u,v;}e[M];
vector<pair<int,int> >v[M];

int find(int x){return f[x]==x?x:f[x]=find(f[x]);}

void dfs(int u,int fa,int id)
{
	for (int i=0;i<v[u].size();i++)
	{
		int to=v[u][i].x,p=v[u][i].y;
		if (to==fa)continue;
		dfs(to,u,p);
	}
	if (u==1)return;
	if (a[u]>=x)a[fa]+=a[u]-x,ans[++cnt]=id;
	else ans[--cnt2]=id;
}

signed main()
{
	cnt2=n=read(),m=read(),x=read();int sum=0;
	for (int i=1;i<=n;i++)a[i]=read(),f[i]=i,sum+=a[i];
	for (int i=1;i<=m;i++)
	{
		e[i].u=read(),e[i].v=read();
		if (find(e[i].u)==find(e[i].v))continue;
		f[find(e[i].u)]=find(e[i].v);
		v[e[i].u].pb(mp(e[i].v,i)),v[e[i].v].pb(mp(e[i].u,i));
	}
	for (int i=1;i<=n;i++)
		if (find(i)!=find(1))return puts("NO"),0;
	if (sum<(n-1)*x)return puts("NO"),0;
	puts("YES");dfs(1,0,0);
	for (int i=1;i<n;i++)
		cout<<ans[i]<<endl;
	return 0;
}
```

然而有没有别的方法呢？

我口胡了一个方法，但是可能时间复杂度有点假，供君一笑，同时也算是这类构造题的一类启发吧。

还是先弄一颗生成树然后考虑归纳的构造：

因为有 $n$ 个点，而 $\displaystyle \sum a_i \ge (n-1)\times x$。先随便找两个相邻的点 $u,v$，令 $y = a_u+a_v$，那么 $\displaystyle y + \sum_{i\ne u,i \ne v} a_i \ge (n-1) \times x$。根据鸽巢原理，要么存在一个点 $p$ 满足 $a_p \ge x$，或者 $a_u+a_v \ge x$，前者就随便找一个点缩起来，后者就把 $u,v$ 缩起来。这样就能够证明必然有解了。

然而时间复杂度可能比较大，而且我不太会优化，写起来也比较麻烦，还是前面那种方法好。~~如果有神仙实现并且过了请叫我一声qwq。~~

---

## 作者：platelett (赞：8)

> [题目链接](https://codeforces.com/problemset/problem/1515/F)
>
> 给定一张 $n$ 个点 $m$ 条边的无向连通图和正整数 $x$，点有非负权值 $a_i$。
>
> 如果一条边 $(u,v)$ 满足 $a_u+a_v \ge x$，可以将 $u,v$ 缩起来，新点的点权为 $a_u+a_v-x$。
>
> 判断这张图是否可以缩成一个点并给出方案。
>
> $n,m \le 3 \cdot 10^5,x,a_i \le 10^9$

首先将每个点的点权减去 $x$，则合并条件变为 $a_u + a_v \ge -x$，每次合并后新点的点权为 $a_u + a_v$。

> 结论：这张图可以缩成一个点的充要条件是点权和大于等于 $-x$。

必要性显然，充分性可以考虑这个构造：每次选择点权最大的点 $u$ 的任意一条边。

构造的正确性可以考虑反证法，设这条边为 $(u,v)$，假设这条边不行，即 $a_u+a_v<-x$。

进一步 $\because a_v \ge -x,\therefore a_u < 0$

由于 $a_u$ 是最大值，因此所有点的点权都是负数，那么 $a_u+a_v \ge \sum a_i \ge -x$，推出矛盾！

至此，已经得到一个做法。

但还有更简单的做法，根据上面结论，任意求一棵生成树都有可行方案。

先从叶子向根依次考虑每个结点，如果这个结点权值非负，则选择它和它父亲的连边，再从根向叶子依次考虑每个结点，如果它和它父亲的连边还没选，则选择这条边。

证明可以考虑这课树的任何可行方案都可以调整成以上方案。

在实现中不必 ```DFS``` 两遍，```DFS``` 过程中把没选的边压栈即可。

复杂度 $O(n)$。

代码：

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define eb emplace_back

using namespace std;

const int N = 3e5 + 5;

int n, m, x, vis[N], as[N], L, R;
long long a[N], su;
vector <pair <int, int>> G[N];

void dfs(int u) {
	vis[u] = 1;
	for(auto [v, i] : G[u]) if(!vis[v])
		dfs(v), a[v] >= 0 ? a[u] += a[v], as[L++] = i : as[R--] = i;
}
int main() {
	cin >> n >> m >> x;
	rep(i, 1, n) scanf("%lld", &a[i]), su += a[i] -= x;
	int u, v;
	rep(i, 1, m) scanf("%d%d", &u, &v), G[u].eb(v, i), G[v].eb(u, i);
	if(su + x < 0) puts("NO"), exit(0);
	puts("YES"), L = 2, R = n, dfs(1);
	rep(i, 2, n) printf("%d\n", as[i]);
	return 0;
}
```

---

## 作者：Pengzt (赞：6)

[CF1515F](https://www.luogu.com.cn/problem/CF1515F)

简单题。

先猜个结论，当且仅当 $\sum\limits_{i=1}^{n}a_i<(n-1)x$ 时无解，这是好想的。因为每次合并减少一个点，总点权减少 $x$。

它为什么是对的呢？考虑反证法。令 $u$ 为当前的点权最大的点。若不能合并，则有 $a_u<x-a_v$，则 $\sum a_i\le ca_u<c(x-a_v)$，其中 $c$ 为当前点的数量，将括号拆开后显然与和  $\ge (c-1)x$ 相矛盾。原命题得证。

那我们就可以每次选择点权最大的点随便与一条相连的边合并即可。这个可以使用并查集加启发式合并实现，查询全局 $\max$ 可以使用 set 或 线段树。这里的时间复杂度是 $\mathcal{O}(m\log m+n\log n)$，因为这里的启发式合并是用在边集上的。

这样实现起来有点麻烦，考虑能不能简化，即对任意一棵生成树有一个普适的做法。

可以先在叶子节点向上贪心，即 dfs 后的 $v$ 的权值若 $\ge 0$，则与 $u$ 合并。然后再从根向叶子的贪心一遍，从上到下的合并所有未被选择的树边。

贪心的正确性是显然的，在第一次 dfs 时将每个节点的 $a$ 值会变为不能再增加，然后又因为最后一定有解，所以这时再让它不断减少也不会出现负数。想到这个贪心也是容易的，因为最后的总值是非负的，又不能再计算过程中出现负数，肯定就是考虑把能加的先加上，最后统一执行减法操作，这样就一定能保证非负。

实现上，如果第一次 dfs 时不选这条边，是可以直接求出答案的位置的。于是就只需要一次 dfs 了。注意 $a$ 数组合并后有可能会爆 int。

[评测记录](https://codeforces.com/contest/1515/submission/227821491)

---

## 作者：Mr_Wu (赞：5)

考虑取出一棵生成树，观察它是否合法。首先要满足一个条件就是 $\sum a_i\ge (n-1)x$，不然最后合并不起来

然后貌似没啥想法了，不如直接猜测这就是充要条件，事实上这是正确的。如果做过 [NOI2020 制作菜品](https://www.luogu.com.cn/problem/P6775) 就会知道一个结论：当 $n\ge 2$ 时最大数加最小数 $\ge x$。可以证一下：

- 设为 $a_1\le a_2\le \cdots\le a_n$，假设 $a_1+a_n<x$，则 $a_2\le a_3\le\cdots\le a_n<x-a_1$，根据这得出 $\sum a_i< (n-1)x-(n-2)a_1$，导出了矛盾

所以可以考虑第一次选最大的点，然后任选与它相邻的一个点，将它们合并即可。合并之后成为一个新点 $a_i+a_j-x$，$n$ 减去 1，此时仍有 $\sum a_i\ge (n-1)x$，所以归纳就完成了。

那既然充要条件是 $\sum a_i\ge (n-1)x$，所以判完后任选一个生成树即可。

我的实现是并查集与边表的启发式合并，以及用线段树查找全局最大值

```cpp
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;

typedef long long ll;
const int MAXN=3e5+5;
const ll INF=1e18;

int fa[MAXN],siz[MAXN];
int get(int x){
	if(fa[x]!=x)fa[x]=get(fa[x]);
	return fa[x];
}

int N,M,X;ll sum,a[MAXN];
struct edge{
	int v,i;
	edge(){}
	edge(int v,int i):v(v),i(i){}
};
vector<edge> V[MAXN];

struct data{
	ll mx;int pos;
	data(){}
	data(ll mx,int pos):mx(mx),pos(pos){}
	friend data operator+(const data& l,const data& r){
		return l.mx>r.mx?l:r;
	}
}T[MAXN<<2];
#define ls (o<<1)
#define rs (o<<1|1)
#define mid ((l+r)>>1)
void build(int o,int l,int r){
	if(l==r)T[o]=data(a[l],l);
	else build(ls,l,mid),build(rs,mid+1,r),T[o]=T[ls]+T[rs];
}
void ins(int o,int l,int r,int p,ll k){
	if(l==r)T[o].mx=k;
	else{
		if(p<=mid)ins(ls,l,mid,p,k);
		else ins(rs,mid+1,r,p,k);
		T[o]=T[ls]+T[rs];
	}
}

int main(){
	scanf("%d%d%d",&N,&M,&X);
	for(int i=1;i<=N;++i)scanf("%lld",&a[i]),sum+=a[i];
	if(sum<1ll*(N-1)*X){puts("NO");return 0;}
	puts("YES");
	for(int i=1;i<=N;++i)fa[i]=i;
	int u,v;
	for(int i=1;i<=M;++i){
		scanf("%d%d",&u,&v);
		if(get(u)!=get(v))fa[get(u)]=get(v),V[u].push_back(edge(v,i)),V[v].push_back(edge(u,i));
	}
	for(int i=1;i<=N;++i)fa[i]=i,siz[i]=1;
	build(1,1,N);
	for(int i=1;i<N;++i){
		int u=T[1].pos;
		while(1){
			int v=V[u].back().v;
			if(get(v)==u)V[u].pop_back();
			else{
				printf("%d\n",V[u].back().i);
				int x=get(v);
				if(siz[u]>siz[x]){
					fa[x]=u,siz[u]+=siz[x],a[u]=a[u]+a[x]-X;
					for(int k=0;k<V[x].size();++k)V[u].push_back(V[x][k]);
					ins(1,1,N,x,-INF),ins(1,1,N,u,a[u]);
				}else{
					fa[u]=x,siz[x]+=siz[u],a[x]=a[x]+a[u]-X;
					for(int k=0;k<V[u].size();++k)V[x].push_back(V[u][k]);
					ins(1,1,N,u,-INF),ins(1,1,N,x,a[x]);
				}
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：whiteqwq (赞：2)

[CF1515F Phoenix and Earthquake](https://www.luogu.com.cn/problem/CF1515F)

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1793815)

下分场/ll

这道题其实很简单，考场降智想复杂写了个类似Brovuka的算法，然后被自己hack了/kk。

## 题意
给定一个$n$个点$m$条边的无向联通图，在一次地震中边都被摧毁了。

位置$i$有$a_i$吨沥青，修建一条边需要$X$吨沥青，因此连边的两个连通块的沥青吨数之和要大于等于$X$，你需要修建$n-1$条边使得图联通，求是否能做到，如果能，请输出任意一种方案。

$1\leqslant n,m\leqslant 3\times 10^5$

## 分析

考虑猜一个结论：只要沥青总吨数$total$大于等于$(n-1)X$，那么一定可以使图联通。

> 证明：考虑不断找到一条连接两个沥青总吨数大于等于$X$的边进行修建。
若已经修建了$e$条边后无法找到下一条边，那么可知$total-eX<X+(n-e-2)X$（左边是当前沥青总吨数，右边是考虑任意一条边两端的沥青总吨数加上其他连通块的沥青总吨数）。
因此$taotal<(n-1)X$，推出矛盾。

不难发现取该图的任意一个$\text{dfs}$树仍然满足条件，因此我们将图上的问题转换到了树上，而且易知树上每条边都要用到。

我们在树上进行$\text{dfs}$，$x$遍历完儿子$y$后，讨论连接$(x,y)$的边什么时候加入答案序列：如果$x$所在的连通块与$y$所在的连通块沥青总吨数大于等于$X$，那么可以直接连，否则可以放在最后连，用一个类似双端队列的东西就可以维护了。

由于每次可以直接把连接后儿子的沥青总吨数加到父亲上（没有连接的儿子不会影响父亲向上的连边），因此并不需要用并查集维护连通块的沥青总数。

时间复杂度：$O(n+m)$。

## 代码
```
#include<stdio.h>
const int maxn=300005,maxm=maxn<<1;
int n,m,X,e,cnt1,cnt2;
int start[maxn],to[maxm],then[maxm],id[maxm],ans[maxn],a[maxn],vis[maxn];
long long sum;
inline void add(int x,int y,int i){
    then[++e]=start[x],start[x]=e,to[e]=y,id[e]=i;
}
void dfs(int x){
    vis[x]=1;
    for(int i=start[x];i;i=then[i]){
        int y=to[i];
        if(vis[y])
            continue;
        dfs(y);
        if(a[x]+a[y]>=X)
            a[x]+=a[y]-X,ans[++cnt1]=id[i];
        else ans[--cnt2]=id[i];
    }
}
int main(){
    scanf("%d%d%d",&n,&m,&X);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]),sum+=a[i];
    for(int i=1;i<=m;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y,i),add(y,x,i);
    }
    if(sum<1ll*(n-1)*X){
        puts("NO");
        return 0;
    }
    puts("YES");
    cnt1=0,cnt2=n;
    dfs(1);
    for(int i=1;i<=n-1;i++)
        printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：Creeper_l (赞：1)

## 题意

给定一个 $n$ 个点 $m$ 条边的无向图和一个数 $x$，每个点有点权 $a_{i}$。对于一条边 $u\to v$，如果满足 $a_{u}+a_{v}\ge x$，则可以将 $u$ 和 $v$ 合并为一个点，新点的权值为 $a_{u}+a_{v}-x$，问最终能否缩成一个点。

## 思路

首先考虑一个结论：如果有 $\sum a_{i}\ge x \times(n-1)$，那么一定有解。

证明：必要性显然，因为要合并 $n-1$ 次，每次产生的代价是 $-x$，所以总代价是 $-x \times(n-1)$，所以要满足上述不等式。然后考虑证明充分性，考虑反证。假设 $u$ 点为所有点中点权最大的一个，对于 $u$ 的一条出边 $u\to v$，假设 $a_{u}+a_{v}<x$，转化得 $a_{u}<x-a_{v}$，又因为 $a_{u}$ 是点权最大的点，所以 $a_{1},a_{2},\dots,a_{n}<x-a_{v}$，那么 $\sum a_{i}-a_{v}<(n-1)x-(n-1)a_{v}$，两边同时加上 $a_{v}$ 得不等式：$\sum a_{i}<(n-1)x-(n-2)a_{v}$，很明显与原不等式不符，故当原不等式满足时，一定有解。

最后的问题就是如何构造合法解的答案了，我们可以深度优先遍历整个无向图，并且用两个数组来维护最终的答案。具体来讲，如果当前边满足 $a_{u}+a_{v}\ge x$ 的话，将当前边的编号放入第一个数组中，表示先操作的点，并且将 $a_{u}$ 加上 $a_{v}-x$；否则的话就将当前边加到第二个数组中去，表示最后操作的点，因为每个点之会被遍历一次，所以边数一定为 $n-1$，这两个数组可以优化为一个数组，一种加在数组前面，一种加在数组后面即可，时间复杂度 $O(n+m)$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f
#define inf_db 127
#define ls id << 1
#define rs id << 1 | 1
#define re register
#define endl '\n'
typedef pair <int,int> pii;
const int MAXN= 3e5 + 10;
int n,m,a[MAXN],X,y,ans[MAXN],cnt,tot,sum,head[MAXN],q[MAXN],h,tail,x;
bool vis[MAXN];
struct Node{int u,v,nxt,id;}e[MAXN << 1];
inline void Add(int u,int v,int id){e[++cnt] = {u,v,head[u],id};head[u] = cnt;}
inline void dfs(int u)
{
	vis[u] = true;
	for(int i = head[u]; ~ i;i = e[i].nxt)
	{
		int now = e[i].v;
		if(vis[now] == true) continue;
		dfs(now);
		if(a[u] + a[now] >= X) ans[h++] = e[i].id,a[u] = a[u] + a[now] - X;
		else ans[tail--] = e[i].id;
	}
}
signed main() 
{
	memset(head,-1,sizeof head);
	cin >> n >> m >> X;
	for(int i = 1;i <= n;i++) cin >> a[i],sum += a[i];
	for(int i = 1;i <= m;i++) cin >> x >> y,Add(x,y,i),Add(y,x,i);
	if(sum < (n - 1) * X){puts("NO");return 0;}
	else puts("YES");
	h = 1,tail = n - 1,dfs(1);
	for(int i = 1;i < n;i++) cout << ans[i] << endl;
	return 0;
}
```






---

## 作者：7KByte (赞：1)

众所周知猜结论才是 CF 最重要的技巧。

这道题需要构造有解的方案，考虑什么情况下有解。

观察一下四个样例，只有样例三在 $\sum a_i<(n-1)x$ 的情况下无解。

猜测当且仅当 $\sum a_i<(n-1)x$ 时无解。

考虑证明 $\sum a_i\ge (n-1)x$ 时一定有解。

当 $n=1$ 时一定有解。

当 $n>1$ 时，我们合并两端之和最大的点，使之变为 $n-1$ 的情况。

因此我们只需要证明一定存在一条边两端之和 $\ge x$ 。

反证法，假设所有边两端之和 $<x$，任意生成一棵树一共 $n-1$ 条边，总和 $<(n-1)x$ ，由于树是联通的，所以每个节点的$a_i$至少在总和出现一次，所以与$\sum a_i\ge (n-1)x$违背。因此一定存在一条边两端之和$\ge x$。

由此可以归纳证明一定有解。

所以任何一个生成树都是等价的。

我们先任意生成一个树。对于每个节点预处理出 $sz[],c[]$ 分别表示子树大小和 $\sum a_i$。

递归处理每个节点。考虑当前节点为 $x$，把所有子节点按 $c[son]-(sz[son]-1)x$ 从大到小排序，然后依次考虑每个子节点。如果父子之间的边能连则连，否则先递归子树再连。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 300005
#define int long long
using namespace std;
int n,m,k,u[N],h[N],v[N],tot,sum,sz[N],c[N],fa[N];
struct edge{int to,nxt,val;}e[N<<1];
void add(int x,int y,int z){e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;e[tot].val=z;}
vector<pair<int,int> >a[N];vector<int>ans;
void calc(int x){
	sz[x]=1;c[x]=u[x];v[x]=1;
	for(int i=h[x];i;i=e[i].nxt)if(!v[e[i].to])
		calc(e[i].to),sz[x]+=sz[e[i].to],c[x]+=c[e[i].to],fa[e[i].to]=e[i].val,
			a[x].push_back(make_pair(k*(sz[e[i].to]-1)-c[e[i].to],e[i].to));
}
void dfs(int x){
	if(!a[x].size())return;
	sort(a[x].begin(),a[x].end());
	for(int i=0;i<(int)a[x].size();i++){
		int y=a[x][i].second;
		if(c[y]>=(sz[y]-1)*k){
			dfs(y);ans.push_back(fa[y]);
			u[x]=u[x]+c[y]-k*sz[y];
		}
		else{
			ans.push_back(fa[y]);
			u[y]+=u[x]-k;u[x]=u[x]+c[y]-k*sz[y];
			dfs(y);
		}
	}
}
signed main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	rep(i,1,n)scanf("%lld",&u[i]),sum+=u[i];
	rep(i,1,m){
		int x,y;scanf("%lld%lld",&x,&y);
		add(x,y,i);add(y,x,i);
	}
	if(sum<(n-1)*k){puts("NO");return 0;}
	puts("YES");
	calc(1);dfs(1);
	for(int i=0;i<(int)ans.size();i++)printf("%lld \n",ans[i]);
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：0)

结论：如果 $\sum a < (n - 1) \times x$ 或图不联通则必定无解，否则必定有解。

我们给出图的任意一个生成树都存在有解，递归证明如下：

- 对于 $n = 2$ 会初始状态，则必定存在解，这个显然来源于题目本身的定义；

- 对于 $n > 2$ 的情况，随机考虑一个节点 $u$，若 $a_u \geq x$ 则我们直接合并它和它的父亲，变成子问题即可得证；否则我们先不管这个点将原图一分为二变成两个子问题，由于这是一个带权的鸽巢原理，不管你怎么分配权值总会使得其中一个子图必定满足条件，该子图可以被合并成一个点，将 $u$ 重新加上使两个子图重新合在一起变成新图，新图也是一个子图，归为子问题，故得证。

所以我们可以直接拿一棵生成树出来，若 $a_u \geq x$ 就直接将边插入队列里表示外层按顺序合并的边，并将 $u$ 合并到父亲；否则就将当前边插入一个栈中，表示一个递归的过程。两种情况分别对应上述分讨的情况 $1,2$。

最后先按顺序输出队列里的边然后再输出栈里的边即可，时间复杂度线性。

```cpp
#include "bits/stdc++.h"
using namespace std;
#define ll long long
#define int ll
const int Len = 3e5 + 5;
int n,m,a[Len],X;int stk[Len],top;queue<int> Q;
ll sum;int fa[Len];
void makeSet(int x){for(int i = 1 ; i <= x ; i ++) fa[i] = i;}
int findSet(int x){return fa[x] == x ? fa[x] : fa[x] = findSet(fa[x]);}
void unionSet(int x,int y)
{
	int u = findSet(x) , v = findSet(y);
	if(u == v) return;
	fa[v] = u;
}
struct node
{
	int next,to,id;
}edge[Len << 1];
int head[Len],cnt;
void add(int from,int to,int ID)
{
	edge[++ cnt].to = to;
	edge[cnt].id = ID;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
bool vis[Len];
void dfs(int x)
{
	vis[x] = 1;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(vis[to]) continue;
		dfs(to);
		if(a[to] >= X){a[x] = (a[x] + a[to] - X);Q.push(edge[e].id);}
		else{stk[++ top] = edge[e].id;}
	}
}
signed main()
{
	scanf("%lld %lld %lld",&n,&m,&X);
	for(int i = 1 ; i <= n ; i ++) 
	{
		scanf("%lld",&a[i]); 
		sum += a[i];
	}
	makeSet(n);
	for(int i = 1 ; i <= m ; i ++)
	{
		int x,y;scanf("%lld %lld",&x,&y);
		unionSet(x , y);
		add(x , y , i) , add(y , x , i);
	}if(sum < 1ll * (n - 1) * X) return puts("NO") & 0;
	for(int i = 1 ; i <= n ; i ++) if(findSet(i) != findSet(1)) return puts("NO") & 0;;
	dfs(1);puts("YES");
	while(!Q.empty()){int t = Q.front();Q.pop();printf("%lld\n",t);}
	for(int i = top ; i >= 1 ; i --) printf("%lld\n",stk[i]);
	return 0;
}
```

---

## 作者：ListenSnow (赞：0)

### 思路

不难发现，本题有解的必要条件为：$\sum_{i=1}^{n} a_i \geq (n-1) \times x$。

利用归纳法可以证明此条件为充分条件。

任意给出原图的一棵生成树，考虑生成树上的一条边 $(u,v)$。

若 $a_u+a_v\geq x$，那么直接合并，将原问题转化为规模为 $n-1$ 的子问题。根据归纳假设，结论成立；

若 $a_u+a_v < x$。将这条边断开，根据抽屉原理，两棵新生成的子树中必然有一棵满足上述条件。根据归纳假设，这棵树可以合并成一个节点。此时必然可以合并这条边。那么就可以转化为一个规模更小的子问题，根据归纳假设，结论成立。

于是就可以直接对原图 dfs，若当前节点连接的两条边可以合并，则直接合并，否则放在最后合并。

### code：

```
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define LL long long
const int N=3e5+10,M=6e5+10;
int ans[N],hh,tt,h[N],idx,n,m,x;LL a[N],sum;bool vis[N];
struct edge{int v,id,nex;}e[M];
void add(int u,int v,int id){e[++idx]=edge{v,id,h[u]};h[u]=idx;}
void dfs(int u)
{
	vis[u]=true;
	for(int i=h[u];i;i=e[i].nex)
	{
		int v=e[i].v;if(vis[v]) continue;dfs(v);
		if(a[u]+a[v]>=x) a[u]+=a[v]-x,ans[hh++]=e[i].id;
		else ans[tt--]=e[i].id;
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&x);for(int i=1;i<=n;i++) scanf("%lld",&a[i]),sum+=a[i];
	for(int u,v,i=1;i<=m;i++) scanf("%d%d",&u,&v),add(u,v,i),add(v,u,i);
	if(sum<1ll*(n-1)*x) return puts("NO"),0;puts("YES");hh=1,tt=n-1;dfs(1);
	for(int i=1;i<n;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

