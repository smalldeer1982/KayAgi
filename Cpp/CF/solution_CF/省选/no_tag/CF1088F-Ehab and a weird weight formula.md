# Ehab and a weird weight formula

## 题目描述

给定一棵包含 $n$ 个节点的树。每个节点 $u$ 有一个权值 $a_u$。保证树中只有一个节点的权值最小。对于每个节点 $u$（除了权值最小的节点），它必须有一个相邻的节点 $v$，使得 $a_v < a_u$。你需要构造一棵树，使得权值 $w$ 最小，$w$ 的计算方式如下：

- 对于每个节点 $u$，将 $deg_u \cdot a_u$ 加入 $w$（$deg_u$ 表示包含节点 $u$ 的边的数量）。
- 对于每条边 $\{u,v\}$，将 $\lceil \log_2(dist(u,v)) \rceil \cdot \min(a_u, a_v)$ 加入 $w$，其中 $dist(u,v)$ 表示在给定树中从 $u$ 到 $v$ 的路径上的边数。

## 说明/提示

在第一个样例中，原树本身就能使 $w$ 最小。

在第二个样例中，最优的树结构如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1088F/8dcff1bd3592f8428b954bbf8127dd97feb4ff38.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 2 3
1 2
1 3
```

### 输出

```
7```

## 样例 #2

### 输入

```
5
4 5 3 7 8
1 2
1 3
3 4
4 5
```

### 输出

```
40```

# 题解

## 作者：凄魉 (赞：5)

相当于搬官方题解了吧……

### 题意
给你一棵树，点有点权，保证最小点权是唯一的,而且保证对于除最小值外的点$u$，都存在一个与它相连的点$v$，使得$v$的点权$a_v<a_u$。你现在可以对这棵树进行任意的$link-cut$重组出另外一棵树，换句话说你要找出点的标号相等就对应点权相等的另外一棵树的价值最小。

定义重组后的树的价值$w$，对于每个点$u$，对价值有$a_u\cdot deg_u$的贡献。$deg_i$表示新树中$i$号点的连边的数量(度数)。对于新树的每条边$\{u,v\}$，对价值有
$$\left\lceil log_2(dist[u,v])\right\rceil\cdot min(a_u,a_v)$$
的贡献。其中$dist[u,v]$表示原树上点$u$到点$v$的距离(边权为1)。

首先观察树的价值的定义，发现点权的贡献其实也与边有贡献，那我们也将这个贡献给加到边上。那么现在我们可以定义树的价值是对于每条边，有
$$(\left\lceil log_2(dist[u,v])\right\rceil)\cdot min(a_u,a_v)+a_u+a_v$$
的贡献。

首先要会利用题目中给的$a_v<a_u$的性质，可以发现这个性质在树上加上只有一个最小值的条件是可以得到这个结论的：除最小值外，每个点都有且仅有一个与他相邻的点$v$权值小于它。因为对于点$u$，如果有一个点$v$小于它，那么就要需要另外一个点去小于$v$，那这种依赖只会在最小值的时候停止，但是整棵树只有一个最小值，所以每个点也只能有且仅有一个点小于它。

于是通过这种关系，我们能建出一个以最小值为根的树，这样的话每个点有且仅有一个小于它的那个点就是他的father，并且这样树的点权分布有单调性，一个点的点权一定大于自己的儿子。


然后我们再来分析一下题目要求，不妨先从最暴力的想法开始。

你要求一棵树，边有边权，要求边权和最小。。。。。

最小生成树谁不会啊？只不过边数有点多，$O(n^2)$级别的。

那我们就要从边权与最小生成树的性质下手了，我们不妨设每一条边从$u$出发到达$v$并且有$a_v<a_u$，然后求生成树中，每个点向外只会且必须连一条边连接到生成树中。那么我们最小化的只有一个条件

$$(\left\lceil log_2(dist[u,v])\right\rceil+1)\cdot a_v$$

一个点只会向比它点权小的点连边，这样一定不会出现环，再仔细结合之前的树的性质，你发现……每个点的最优策略是向它的第$2^k$的祖先连边。（每个点到根的路径上点权是递减的，到叶子的路径是递增的）。

于是对于每个点只需要选择他$2^k$祖先中，取代价最小的连边，这就是最小生成树。

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
#define N 503000
#define M 1300000
#define INF 0x3f3f3f3f
#define ll long long
struct node{
	int to,next;
}q[M];
int head[N],ss,f[21][N],n,a[N],Rt;ll ans=0;
void addedge(int x,int y)
{
	q[++ss]=(node){y,head[x]};head[x]=ss;
	q[++ss]=(node){x,head[y]};head[y]=ss;
}
void dfs(int i,int fa)
{
	f[0][i]=fa;ll mi=a[fa];int j=1;
	for (j=1;j<=20;++j)
	{
		f[j][i]=f[j-1][f[j-1][i]];
		if (!f[j][i]) break;
		mi=min(1ll*(j+1)*a[f[j][i]],mi);
	}
	mi=min(mi,1ll*(j+1)*a[Rt]);
	if (fa) ans+=mi+a[i];
	for (int j=head[i];j;j=q[j].next)
		if (q[j].to^fa)
			dfs(q[j].to,i);
}
inline int read(){
	int n=0;char a;bool z=false;
	while(a=getchar())
	{
		if (a>'9'||a<'0')
			if (z) break;
			else continue;
		if (!z) z=true;
		n=(n<<1)+(n<<3)+(a^48);
	}
	return n;
}
int main()
{
	a[0]=INF;
	n=read();Rt=0;
	for (int i=1;i<=n;++i)
	{
		a[i]=read();
		if (a[i]<a[Rt]) Rt=i;
	}
	for (int i=1;i<n;++i) addedge(read(),read());
	dfs(Rt,0);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：OIer_Eternity (赞：3)

[更好的阅读体验 - My Blog](https://blog.csdn.net/OIer_Cosmos/article/details/134619641?spm=1001.2014.3001.5501)
# 题目来源

- [CF1088F](https://codeforces.com/contest/1088/problem/F)

- [洛谷](https://www.luogu.com.cn/problem/CF1088F)

# Description

给定一棵有 $n$ 个点的树，点有点权 $\{a_i\}$。且除了唯一的一个点权最小的点，其余的点都与一个权值比它小的点相邻。

现在需要用这 $n$ 个点重新构建一棵树，使得代价最小。一个点 $u$ 的代价为 $\deg_u\times a_u$，$\deg_u$ 表示其度数；而一条边 $(u,v)$ 的代价为 $\lceil\log_2\text{dis}(u,v)\rceil\times\min\{a_u,a_v\}$。

- $2\le n\le5\times10^5$。

# Solution

首先，对于点的代价可以很容易的转化到边上。即一条边 $(u,v)$ 的代价为 $\lceil\log_2\text{dis}(u,v)\rceil\times\min\{a_u,a_v\}+a_u+a_v$。

其次，由于除了唯一的一个点权最小的点，其余的点都与一个权值比它小的点相邻，则我们可以将这棵树的根节点设为点权最小的点，且每个节点的父亲节点的点权都小于它。

那么，对于一个点，其向自己的祖先连边一定更优于向自己的后代或兄弟连边的（若向兄弟连边，不如向 $\text{lca}$ 连边，因为距离更短且点权更小；后代则显然）。

同时，若每个点都向自己的祖先连边也就满足了连边完仍为树的条件。

接着，由于 $\lceil\log_2\text{dis}(u,v)\rceil$ 的值域只有 $O(\log n)$，可直接枚举 $k=\lceil\log_2\text{dis}(u,v)\rceil$。

而对于相同的 $k$，显然 $a_v$ 越小答案越优，而 $u$ 的 $2^k$ 级祖先即为最优的答案。因此我们只需要预处理出每个点的 $2^k$ 级祖先，并每次枚举 $k$ 取最小值，最后相加即可。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[500005],Min=1e9+1,root,Fa[500005][20],head[1000005],ver[1000005],nxt[1000005],tot;
long long ans;
void add(int u,int v){
    ver[++tot]=v;
    nxt[tot]=head[u],head[u]=tot;
}
void dfs(int u,int fa){
    Fa[u][0]=fa;
    for (int i=1;i<=19;i++) Fa[u][i]=Fa[Fa[u][i-1]][i-1];
    for (int i=head[u];i;i=nxt[i]){
        int v=ver[i];
        if (v==fa) continue;
        dfs(v,u);
    }
}
int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if (a[i]<Min) Min=a[i],root=i;
    }
    for (int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
    dfs(root,root);
    for (int i=1;i<=n;i++){
        if (i==root) continue;
        long long Minn=1e18;
        for (int j=0;j<=19;j++){
            int v=Fa[i][j];
            Minn=min(Minn,1ll*(j+1)*a[v]+a[i]);
        }
        ans+=Minn;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

结论 1：取出 $a_i$ 最小的点为根，则所有点的父亲的权值都比他小。

证明：考虑反证，不妨假设对于某个点 $x$，其父亲 $y$ 满足 $a_y\geq a_x$，那么存在一个 $x$ 的儿子 $x'$ 使得 $a_{x'}<a_x$，令 $x=x'$，即可归纳得对于某个叶子结点 $x$ 有一个儿子 $x'$ 使得 $a_{x'}<a_x$，显然这是不成立的。

结论 2：所有点都会跟某个祖先连边。

证明：考虑归纳，设对于某个 $x$，其所有父亲都跟某个祖先连边了，推这个点会跟某个祖先连边。

考虑两种调整：

* 若这个点不跟任何子树外的点连边，那么存在至少一个子树内的点跟子树外的点连边。将这条边的一个端点换到这个点一定不劣。
* 若这个点跟某个非祖先点连边，那么将这条边的另一端换为这两个点的 LCA 一定不劣。

故这个点一定会跟某个祖先连边。边界条件是根。

于是，考虑反向倍增，设 $val_{i,j}$ 表示 $i$ 子树内距离不超过 $2^j$ 的点的最小边权即可，具体可见代码。

总复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
int a[500005];
vector<int> vc[500005];
int f[500005][20],val[500005][20],cnt[1000005],rt;
void dfs(int now,int fa){
	f[now][0]=fa;
	for(int i=1;i<=19;i++) f[now][i]=f[f[now][i-1]][i-1];
	if(now!=rt){
		cnt[now]=val[fa][0];
		for(int i=0;i<=18;i++) val[now][i]=val[f[now][i]][i+1],cnt[now]=min(cnt[now],val[now][i]);
		cnt[now]+=a[now];
	}
	for(int i=0;i<=19;i++) val[now][i]=min(val[now][i],a[now]*(i+1));
	for(int i=18;i>=0;i--) val[now][i]=min(val[now][i],val[now][i+1]);
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs(v,now);
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	memset(val,1,sizeof(val));
	int n; cin>>n;
	int minv=1e9+7;
	for(int i=1;i<=n;i++) cin>>a[i],minv=min(minv,a[i]);
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	for(int i=1;i<=n;i++) if(minv==a[i]) rt=i;
	dfs(rt,0);
	int ans=0;
	for(int i=1;i<=n;i++) ans+=cnt[i];
	cout<<ans;
	return 0;
}
```

---

## 作者：Erusel (赞：1)

为了便于处理，我们把点权带来的贡献算在边权上

那么定义就是：

对于树的每条边，贡献为 

$a_u+a_v+min(a_u,a_v)*\lceil log_2(dist(u,v))\rceil$

因为题面要求

$\lceil$除了权值最小的点外，每个点至少有一个点权小于它的相邻点$\rfloor$，

所以我们建立的树应该以最小值为根

然后每个节点的父亲是唯一权值比它小的

结合之前的贡献计算，每个点向它的 $2^k$ 级祖先中权值最小的连边，

因为每一次都往小的连边，满足树的无环性质

因此，我们只需要倍增预处理出每个节点的 $2^k$ 级祖先即可，时间复杂度为 $O(nlogn)$

---

## 作者：ww3113306 (赞：1)

###CF1088F Ehab and a weird weight formula
####题意
给定一棵树，点有点权，其中这棵树满足除了权值最小的点外，每个点至少有一个点权小于它的相邻点。

要求你重新构建这棵树，使得代价最小。计算代价的方法如下：

 - 点的代价： $deg_xv_x$,其中$deg_x$表示点$x$的度
 - 边$(x, y)$的代价：$log_2(dis(x, y)) \cdot min(v_x, v_y)$,其中$dis(x, y)$表示$x$和$y$在原树中的距离。

树的代价为点的代价与边的代价之和。

####题解

首先我们来证明一个事情：为了满足每个点至少有一个点权小于它的相邻点(除了权值最小的点之外),这棵树必须满足：根为权值最小的点，对于每个点而言，父亲的权值一定小于它。

如果一个点x要依靠它的儿子y来满足这个性质，那么就意味着它的儿子y也需要依靠它的某个儿子z来满足这个性质。

那么这样的话，叶节点就无论如何都不能满足这个性质了。得证。

那么这个性质可以为我们带来什么？

首先我们考虑不断插入节点来构建出这棵树。那么一个点$x$选择$fa$作为他的父亲，带来的贡献为：

$v_x + v_{fa} + log_2(dis(x, fa)) \cdot min(v_xv_{fa})$

如果一个点$x$选中了它子树中的某个点作为父亲，那么它还不如选择距离更小的祖先，代价更小。

如果一个点$x$选中了深度小于它的非祖先节点，那么它还不如从它选择的这个节点往上走，走到一个离它最近的，是$x$的祖先的节点，那么这个新节点肯定比原来选择的节点距离$x$更近，且权值更小，所以显然更优。

因此点$x$一定会选择它的某个祖先，因为$log_2$的值可以看做是一段一段的，我们可以用倍增来维护每一段中的最小值.

而因为越往上越小，所以这个最小值刚好就是它的第$2^k$级祖先，因此对于某个点，我们只需要倍增的跳一跳，在这些可能的点中选择一个最优的就可以了。
当然如果祖先的个数不够$2^k$的话就需要取root作为father

```cpp
#include<bits/stdc++.h>
using namespace std;
#define R register int
#define LL long long
#define AC 500100
#define ac 1000100
#define inf 100000000000000000LL

int n, rot;
LL ans;
int v[AC], fa[AC][20];
int Head[AC], date[ac], Next[ac], tot;

inline int read()
{
    int x = 0;char c = getchar();
    while(c > '9' || c < '0') c = getchar();
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x;
}

inline void upmin(LL &a, LL b) {if(b < a) a = b;}
inline void upmax(LL &a, LL b) {if(b > a) a = b;}

inline void add(int f, int w)
{
    date[++ tot] = w, Next[tot] = Head[f], Head[f] = tot;
    date[++ tot] = f, Next[tot] = Head[w], Head[w] = tot;
}

void pre()
{
    n = read(), rot = 1;
    for(R i = 1; i <= n; i ++) 
    {
        v[i] = read();
        if(v[i] < v[rot]) rot = i;
    }
    for(R i = 2; i <= n; i ++) add(read(), read());
}

void dfs(int x)
{
    LL rnt = inf;
    if(x != rot)
    {	
        for(R i = 0; i <= 19; i ++) 
        {	
            if(i) fa[x][i] = fa[fa[x][i - 1]][i - 1];
            upmin(rnt, 1LL * (i + 1) * v[fa[x][i]] + v[x]);
        }
        ans += rnt;
    }
    else for(R i = 0; i <= 19; i ++) fa[x][i] = x;
    for(R i = Head[x]; i; i = Next[i])
    {
        int now = date[i];
        if(now == fa[x][0]) continue;
        fa[now][0] = x, dfs(now);
    }
}

int main()
{
//	freopen("in.in", "r", stdin);
    pre();
    dfs(rot);
    printf("%lld\n", ans);
//	fclose(stdin);
    return 0;
}
```


---

## 作者：DDF_ (赞：0)

## 题面

有一棵 $n$ 个点的树，我们要重构他，使树的代价最小。

点 $i$ 有点权 $a_{i}$，每个点除点权最小的点外，都有一个点权比它小的点与其相邻。

重构后，点 $u$ 的代价为 $deg_{u} \times a_{u}$（$deg$ 为重构后点的度数）。

边 $(u,v)$ 的代价为 $
\lceil \log_{2} dis(u,v) \rceil \times \min(a_{u},a_{v})$（$dis(u,v)$ 为点 $u$ 和点 $v$ 在原树中的距离）。

树的代价为点代价与边代价总和。

## 思路

注意到每个点都有点权比它小的点与它相邻，所以可以将点权最小的点提出来，以其为根。

这样，就有性质为**树上所有节点的点权都小于他的子孙节点**。

考虑将一个点与其祖宗连边。

可以证明：如果我们取一个节点与其 $2^{i}$ 次方级祖宗连边，是优于不与 $2^{i}$ 次方级祖宗连边的。

因为如果节点 $u$ 的祖宗 $v$ 的深度比 $2^{i}$ 级祖宗 $x$ 大且比 $2^{i-1}$ 级祖宗 $y$ 小，那么有 $\lceil \log_{2} dis(u,v) \rceil = i$。

又因为 $x$ 深度比 $v$ 小，所以 $v$ 是其 $x$ 的子孙节点，所以由上文加粗的定理可得，$a_{u} > a_{v} > a_{x}$。

将 $u$ 和 $v$ 连边，那么边代价为 $a_{v} \times i$；而如果将 $u$ 和 $x$ 连边，那么边代价为 $a_{x} \times i$。

所以将 $u$ 与 $x$ 连边优于将 $u$ 与 $v$ 连边。

还有，$u$ 与 $x$ 和 $y$ 都连边代价肯定大于 $u$ 与 $x$ 和 $y$ 其中之一连边。

所以我们可以跑一遍 `DFS`，算出节点 $u$ 的 $2^{i}$ 级祖宗 $fa_{u,i}$，然后枚举每个节点分别与其不同的 $2^{i}$ 级祖宗相连。

因为一条边会使边两个端点的度数都加 $1$，所以在连边的同时把两边端点的点权加在答案中，就可以算出答案。

时间复杂度 $O(n \log_{2} n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+2;
int n,a[N],r=1,l;
int head[N],to[2*N],nxt[2*N],idx;
int fa[N][22];
long long ans; //不开long long见祖宗
void add(int x,int y) {
	nxt[++idx]=head[x],head[x]=idx,to[idx]=y;
	return;
}
void dfs(int u,int lst) {
	fa[u][0]=lst;
	for(int i=1;i<=l;i++) fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=head[u];i;i=nxt[i]) if(to[i]!=lst) dfs(to[i],u);
	return;
} //求2^i级祖先
int main() {
	scanf("%d",&n),l=log2(n)+1;
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		if(a[i]<a[r]) r=i; //将点权最小的提出来作为根
	}
	for(int i=1,x,y;i<n;i++) scanf("%d%d",&x,&y),add(x,y),add(y,x);
	dfs(r,r);
	for(int u=1;u<=n;u++) {
		if(u!=r) {
			long long res=1e17;
			for(int i=0;i<=l;i++) {
				int v=fa[u][i];
				res=min(res,1ll*a[v]*i+a[v]+a[u]); //计算连边最小代价
			}
			ans+=res;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

