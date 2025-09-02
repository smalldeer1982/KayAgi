# [USACO06MAR] Milk Team Select G

## 题目描述

Farmer John 的 $N(1 \le N \le 500)$ 头奶牛打算参加一场世界级的产奶比赛 （Multistate Milking Match-up，MMM），他们已经摸清了其他队的实力。他们的总产奶量只要大于等于 $X$ 加仑（$1 \leq X \leq 10^6$），就能赢得胜利。

每头奶牛都能为全队贡献一定量的牛奶，数值在 $-10^4$ 到 $10^4$ 加仑之间（为啥有负数？因为有些奶牛会打翻其他奶牛产的牛奶）。

MMM 的目标是通过合作，增进家庭成员间的默契。为了支持比赛精神，奶牛们希望在赢得比赛的前提下，有尽可能多对奶牛间存在直系血缘关系。当然，所有奶牛都是女性，因此这里的直系血缘关系就是母女关系。

现在 FJ 摸清了所有奶牛间的血缘关系，希望算出一个团队在赢得胜利的前提下，最多有多少对奶牛存在血缘关系。注意：如果一个团队由某头奶牛和她的母亲和外祖母组成的话，这个团队只有两对血缘关系（她和她的母亲，她的母亲和外祖母）。

## 说明/提示

最优的队伍包含 $1,2,3,5$ 这四头奶牛，总产奶量为 $9$ 加仑，共有两对血缘关系（$1,2$ 和 $1,3$）。

虽然 $2,3,5$ 这个组合产奶量更大，但是这个组合里没有血缘关系。

## 样例 #1

### 输入

```
5 8
-1 0
3 1
5 1
-3 3
2 0```

### 输出

```
2```

# 题解

## 作者：Zjl37 (赞：20)

### 本篇题解的目的
[Click here](https://www.luogu.com.cn/paste/4eciw62i)

### 树形动规
注意到一头奶牛最多只有一个母亲，且不存在环，因此可以用树来储存；母女关系又具有明显的方向性，可以单向存边。所有奶牛及其关系构成一片森林。   
如果一头奶牛的母亲不是候选奶牛，不妨将其母亲编号为 0，这样一片森林就变成了一棵以0为根的树，方便我们读入和操作。

这是一张样例的图：
![](https://cdn.luogu.com.cn/upload/image_hosting/ddri44ga.png)
### 设计状态
设计一个三维数组 f：   
$ f(i,j,0) $ 表示牛 i 不参赛，以 i 为根的家庭树下有 j 对血缘关系时最大的产奶量。   
$ f(i,j,1) $ 表示牛 i 参赛，以 i 为根的家庭树中有 j 对血缘关系时最大的产奶量。   

另外，维护一个一维数组 cnt：$ cnt(i) $ 表示以 i 为根的家庭树中的边数。这也表示树中最多可能的血缘关系数，可以用来确定枚举边界。

最后的答案是一个最大的数 m，满足 $ f(0,m,0)\geq x $。因为牛 0 不是候选奶牛，它不能参赛，所以第三维只能是 0.

### 状态转移与初始值
考虑一头奶牛 x：   
很显然，初始时 $ f(x,0,0) = 0,\; f(x,0,1) = c(x) $，其中 $ c(i) $ 表示牛 i 能为全队贡献的牛奶体积。其他的值，到目前为止都是无穷小。

接下来，将 x 的女儿的信息合并到 x 中。考虑母亲 x 的女儿 y，假定在 y 之前枚举的所有女儿的信息都已经合并到了 x 中。在 x 中选 j 对关系，在 y 中选 k 对关系，那么 j, k 的取值范围：$ 0\leq j\leq cnt(x),\; 0\leq k\leq cnt(y) $   
（ ~~啊，如果你觉得这段话读起来怪怪的，换成父节点、子节点之类不影响理解~~ ）

- 如果 x 参赛，y 也参赛，那么 x 与 y 形成一对新的血缘关系，一共有 j + k + 1 对关系。   
$ f(x,j+k+1,1)=\max\lbrace f(x,j+k+1,1),f(x,j,1)+f(y,k,1)\rbrace $

其他情况下不形成新关系，也就只有 j + k 对关系。

- 如果 x 参赛，y 不参赛：   
$ f(x,j+k,1)=\max\lbrace f(x,j+k,1),f(x,j,1)+f(y,k,0)\rbrace $
- 如果 x 不参赛，那么取 y 参赛和不参赛中较大的产奶量：   
$ f(x,j+k,0)=\max\lbrace f(x,j+k,0),f(x,j,0)+\max\lbrace f(y,k,0),f(y,k,1) \rbrace \rbrace $

### 代码（AC 100）

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,x,c[501],mo,es,hd[501],f[501][501][2],cnt[501];
// mo: mother, es: 邻接表中已经存的边数, hd[i]: 邻接表中从i出发的最后一条边。其他变量的含义同题面和题解。
pair<int,int> e[501]; // <daughter,next>
// 使用邻接表存边。
// STL之pair真好用，使用时建议将first、second代表的含义记在旁边，避免忘记。

void add(int x, int y) {
	// add函数用于向邻接表中添加一条从x到y的边，表示x是y的母亲。
	e[++es]=make_pair(y,hd[x]);
	hd[x]=es;
}

void dfs(int x) {
	// dfs函数进行树形动规，x为当前的牛
	f[x][0][0]=0;
	f[x][0][1]=c[x];
	// 初始值
	for(int i=hd[x]; i; i=e[i].second) {
		int y=e[i].first;
		// 因为是有向边，不必判断y是否等于母亲
		dfs(y);
		// 先搜女儿
		for(int j=cnt[x]; j>=0; j--) {
			for(int k=cnt[y]; k>=0; k--) {
				if(f[x][j][0]+max(f[y][k][0],f[y][k][1])>f[x][j+k][0])
					f[x][j+k][0]=f[x][j][0]+max(f[y][k][0],f[y][k][1]);
				// x不参赛
				if(f[x][j][1]+f[y][k][1]>f[x][j+k+1][1])
					f[x][j+k+1][1]=f[x][j][1]+f[y][k][1];
				// x参赛，y参赛
				if(f[x][j][1]+f[y][k][0]>f[x][j+k][1])
					f[x][j+k][1]=f[x][j][1]+f[y][k][0];
				// x参赛，y不参赛
			}
		}
		cnt[x]+=cnt[y]+1;
		// 维护边数。x的边数是它所有女儿的边数，加上它女儿的数量。
	}
}

int main() {
//	freopen("XPtselect.in","r",stdin);
//	freopen("XPtselect.out","w",stdout);
	scanf("%d%d",&n,&x);
	for(int i=1; i<=n; i++) {
		scanf("%d%d",&c[i],&mo);
		add(mo,i);
		// 存有向边
	}
	memset(f,0xc0,sizeof f);
	// 将f数组中的所有值初始化为(int)0xc0c0c0c0=-1061109568，可看做无穷小。
	dfs(0);
	while(n>=0&&f[0][n][0]<x)
		n--;
	// 从大到小查找答案。当然也可以写二分查找，不过意义不大。
	printf("%d\n",n);
	return 0;
}
```

---

## 作者：Purslane (赞：5)

## Solution

我是【】. ( 请自行填补 )

这个母女关系显然会形成森林 , 如果把 $0$ 节点带上就是一棵树 . 树形 DP 走起 .

考虑以关系数量作为状态 . 转移时 , 我们的节点可能和他的子节点形成了母女关系 , 这取决于他和子节点有没有选上 . 那么再开一维 $0/1$ 表示有没有选 .

那么 $dp_{i,j,0/1}$ 表示以第 $i$ 个为根 , 共有 $j$ 对母女关系 , 最大的产量 .

转移时 , 枚举分给这个子节点的关系数量 .

```cpp
roff(k,n-1,0) {
	roff(kk,k,0) dp[u][k][0]=max(dp[u][k][0],dp[u][kk][0]+max(dp[to][k-kk][0],dp[to][k-kk][1]));
	roff(kk,k,0) dp[u][k][1]=max(dp[u][k][1],dp[u][kk][1]+dp[to][k-kk][0]);
	roff(kk,k-1,0) dp[u][k][1]=max(dp[u][k][1],dp[u][kk][1]+dp[to][k-kk-1][1]);
}
```

这里的 `roff` 表示反方向枚举 .

1. 如果这个根节点不选 , 那么它显然不会和子节点产生贡献 , 那么只需要子节点选不选是无所谓的 ;
2. 如果这个根节点选 , 那么当子节点选的时候 , 它会产生 $1$ 的贡献 ; 如果不选 , 不会产生贡献 , 应该分开来看 .

注意到这里的转移实质上将用了几个子节点这一维给压缩掉了 , 所以为了防止重复 , 还是倒着枚举好 .

然后由于 $0$ 是一个虚拟的节点 , 所以它不应当选 . 寻找答案时从大到小枚举 $dp_{0,i,0}$ , 若不少于 $x$ , 那么 $i$ 就满足要求 .

时间复杂度 : $\text{O(n} ^ \text{3} \text{)}$ .

code :

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=500+10;
int n,x,dp[MAXN][MAXN][2],val[MAXN],fa[MAXN];
vector<int> G[MAXN];
void dfs(int u) {
	dp[u][0][1]=val[u],dp[u][0][0]=0;
	for(auto to:G[u]) {
		dfs(to);
		roff(k,n-1,0) {
			roff(kk,k,0) dp[u][k][0]=max(dp[u][k][0],dp[u][kk][0]+max(dp[to][k-kk][0],dp[to][k-kk][1]));
			roff(kk,k,0) dp[u][k][1]=max(dp[u][k][1],dp[u][kk][1]+dp[to][k-kk][0]);
			roff(kk,k-1,0) dp[u][k][1]=max(dp[u][k][1],dp[u][kk][1]+dp[to][k-kk-1][1]);
		}
	}
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>x;
	ffor(i,1,n) {
		cin>>val[i]>>fa[i];
		G[fa[i]].push_back(i);
	}
    memset(dp,-0x3f,sizeof(dp));
	dfs(0);
	roff(i,n-1,0) if(dp[0][i][0]>=x) {cout<<i;return 0;}
	cout<<-1;
	return 0;
}
```

---

## 作者：CYZZ (赞：1)

# [Milk Team Select G](https://www.luogu.com.cn/problem/P6079)
校内模拟赛的唯一一道树上问题，写个题解纪念一下~~比赛的时候因为一行代码挂了 64 分，我%…*&…》￥@！~~。
# 题意简明
把母女关系用一个森林表示出来。如果我们选出的点之间有直接连边的话，就会存在一个血缘关系。求出在选出的节点权值之和不小于 $x$ 的情况下，选出的节点中最多有多少对点在树上有连边。

# 思路分析
如果是森林的话不太好处理，可以把所有没有母亲的节点连向一个编号为 0 的源点，此时树形 DP 的思路其实已经很明显了。

## 状态
直接猜状态，由于最多的血缘关系数不好直接求，所以我们设 $dp_{i,j}$ 为以 $i$ 为根的子树中恰好有 $j$ 对血缘关系时的最大产奶量。为了方便，我们多加一维，记录 $i$ 有没有被选中。即 $dp_{i,j,0/1}$ 表示 $i$ 被选中或没被选中时分别的最大产奶量。

## 答案
我们发现这个状态刚好和根节点 0 不能选对接上了。所以最终答案就是使 $dp_{0,j,0} \ge x$ 的 $j$ 的最大值。

## 方程
先贴代码~~懒得写公式了~~：
```cpp
dp[u][j][0]=max(dp[u][j][0],dp[u][k][0]+max(dp[v][j-k][1],dp[v][j-k][0]));//u不选
dp[u][j][1]=max(dp[u][j][1],dp[u][k][1]+dp[v][j-k][0]);//u选v不选
if(j-k-1>=0)
	dp[u][j][1]=max(dp[u][j][1],dp[u][k][1]+dp[v][j-k-1][1]);//u选v选
```
稍微解释下：$u$ 是当前遍历到的节点，$v$ 是 $u$ 的其中一个子节点，$k$ 是一个血缘关系数，把以 $u$ 为根的子树中 $k$ 个关系时的最大值和以 $v$ 为根的子树中 $j-k$ 个关系时的最大值合并，以达到状态转移的效果。分别对应的情况是：

- $u$ 不选 $v$ 不选和 $u$ 不选 $v$ 选。（可以直接取 $\max$）
- $u$ 选 $v$ 不选。
- $u$ 选 $v$ 选。这个需要特殊注意：如果都选的话，$u$ 和 $v$ 之间会多产生一条边，则给 $v$ 的子树只留下了 $j-k-1$ 条关系供选择，才能满足总数为 $j$。

## 初始值
- $dp_{i,0,0}=0$
- $dp_{i,0,1}=a_i$

# 一些细节
- 因为产奶量可能为负数，所以 $dp$ 数组赋为 $-inf$。
- 状态转移中的 $j$ 和 $k$ 本应该从 $i$ 的子树大小开始枚举，这里我偷一下懒直接从 $n-1$ 枚举到 0。
- 在第三类转移的时候要特判 $j-k-1 \ge 0$。

然后就是快乐的代码时间！
# 代码实现
```
#include <bits/stdc++.h>
using namespace std;
int n,m,tot,a[505],head[505],dp[505][505][2];
struct edge
{
	int next,to;
}e[250005];
void add_edge(int u,int v)
{
	e[++tot].next=head[u];
	e[tot].to=v;
	head[u]=tot;
}
void dfs(int u)
{
	dp[u][0][1]=a[u];
	dp[u][0][0]=0;
	for(int i=head[u];i;i=e[i].next)
	{
		int v=e[i].to;
		dfs(v);
		for(int j=n-1;j>=0;j--)
		{
			for(int k=j;k>=0;k--)
			{
				dp[u][j][0]=max(dp[u][j][0],dp[u][k][0]+max(dp[v][j-k][1],dp[v][j-k][0]));
				dp[u][j][1]=max(dp[u][j][1],dp[u][k][1]+dp[v][j-k][0]);
				if(j-k-1>=0)
					dp[u][j][1]=max(dp[u][j][1],dp[u][k][1]+dp[v][j-k-1][1]);
			}
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d%d",&a[i],&x);
		add_edge(x,i);
	}
	memset(dp,-0x3f,sizeof dp);
	dfs(0);
	for(int i=n-1;i>=0;i--)
	{
		if(dp[0][i][0]>=m)
		{
			printf("%d",i);
			return 0;
		}
	}
	printf("-1");
}
```
制作不易，希望本片题解可以帮到大家！

---

## 作者：内拉组里 (赞：0)

树形 **dp**。

# Thoughts：

显然根据题意，$ n $ 头牛最多只能产生 $ n - 1 $ 对血缘关系，由此想到树形结构。

但是题目没有明确表明只有一头牛的母亲不在牛群中，所以实际上产生的是一片森林。

故考虑构造超级源点 $ s = 0 $ 连接所有~~没母~~的牛。

此时的血缘关系就形成了一棵树。

考虑 **dp**。

令 $ dp[u][i] $ 表示在以 $ u $ 为根的当前扫过的子树中，产生了 $ i $ 对血缘关系，

其中没有一对与 $ u $ 有关，最大加仑数。

同样地，令 $ pd[u][i] $ 表示其中至少有一对与 $ u $ 有关，最大加仑数。

转移。

- 显然当没有一对血缘关系与 $ u $ 有关时，无论子节点与剩余的血缘关系是否有关，

  都不会产生额外的血缘关系，直接从子节点中取 $ max $ 继承即可。

- 而当存在与 $ u $ 有关的血缘关系，并且子节点 $ v $ 也与一些血缘关系有关时，

  $ u $ 和 $ v $ 才会产生了新的血缘关系。

故得出转移方程：

- $ dp[u][i] = \max\{ dp[u][j] + \max\{ dp[v][i - j],pd[v][i - j] \} \} $ 
- $ pd[u][i] = \max\{ pd[u][j] + \max\{ dp[v][i - j],pd[v][i - j - 1] \} \} $ 

第二条转移可能会造成下标越界，但在声明时调换一下顺序即可，不会 **RE**。

输出答案是由于超级源点 $ s = 0 $ 是虚构的，故只能取 $ dp[0][i] $，

从大到小枚举 $ i $，找到第一个 $ dp[0][i] \ge x $ 的 $ i $ 即为答案。

找不到则无解。

# Analyses：

> 总时间复杂度 $ \Theta (N^3) $。
>
> 总空间复杂度 $ \Theta (N^2) $。

# Code：

```cpp
/* reference : @Luogu.Purslane (120947) */
#include	<iostream>
#include	<cstring>
#include	<vector>
using namespace std;
constexpr int maxn = 504;

int n, x;
int a[maxn];
int rt[maxn];
int dp[maxn][maxn];
int pd[maxn][maxn];
/* pd/dp[i][j] means the maximal gallons in the subtree with the root of [i],there exist [j] relationship(s),while u is/isn't selected */
vector<int> G[maxn];

void dfs (int u)
{
	dp[u][0] = 0;
	pd[u][0] = a[u];
	for (auto v : G[u])
	{
		dfs (v);
		for (int i = n - 1; ~i; i--)
		{
			for (int j = i; ~j; j--)
				dp[u][i] = max (dp[u][i], dp[u][j] + max (dp[v][i - j], pd[v][i - j]));
			for (int j = i; ~j; j--)
				pd[u][i] = max (pd[u][i], pd[u][j] + max (dp[v][i - j], pd[v][i - j - 1]));
		}
	}
}

signed main (void)
{
	cin >> n >> x;
	for (int rt, i = 1; i <= n; i++)
	{
		cin >> a[i] >> rt;
		G[rt].push_back(i);
	}
	memset (dp, 0xf3, sizeof dp);
	memset (pd, 0xf3, sizeof pd);
	dfs (0);
	for (int i = n - 1; ~i; i--) if (dp[0][i] >= x)
	{
		cout << i << endl;
		return 0;
	}
	cout << -1 << endl;
	return 0;
}
```

---

