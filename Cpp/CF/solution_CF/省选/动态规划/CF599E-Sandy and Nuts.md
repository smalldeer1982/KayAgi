# Sandy and Nuts

## 题目描述

Rooted tree is a connected graph without any simple cycles with one vertex selected as a root. In this problem the vertex number $ 1 $ will always serve as a root.

Lowest common ancestor of two vertices $ u $ and $ v $ is the farthest from the root vertex that lies on both the path from $ u $ to the root and on path from $ v $ to the root. We will denote it as $ LCA(u,v) $ .

Sandy had a rooted tree consisting of $ n $ vertices that she used to store her nuts. Unfortunately, the underwater storm broke her tree and she doesn't remember all it's edges. She only managed to restore $ m $ edges of the initial tree and $ q $ triples $ a_{i} $ , $ b_{i} $ and $ c_{i} $ , for which she supposes $ LCA(a_{i},b_{i})=c_{i} $ .

Help Sandy count the number of trees of size $ n $ with vertex $ 1 $ as a root, that match all the information she remembered. If she made a mess and there are no such trees then print $ 0 $ . Two rooted trees are considered to be distinct if there exists an edge that occur in one of them and doesn't occur in the other one.

## 说明/提示

In the second sample correct answer looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599E/3a06f49f1bab15c25fa9029dff674e9bd2958cf5.png)In the third sample there are two possible trees:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599E/5bc65707292dd568a0ac7a018a2f94f9303bf3c4.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599E/bacea40f00b7ff26956d9e8aa34e3c4499c85dc6.png)In the fourth sample the answer is $ 0 $ because the information about $ LCA $ is inconsistent.

## 样例 #1

### 输入

```
4 0 0
```

### 输出

```
16
```

## 样例 #2

### 输入

```
4 0 1
3 4 2
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3 1 0
1 2
```

### 输出

```
2
```

## 样例 #4

### 输入

```
3 0 2
2 3 2
2 3 1
```

### 输出

```
0
```

## 样例 #5

### 输入

```
4 1 2
1 2
2 2 2
3 4 2
```

### 输出

```
1
```

# 题解

## 作者：AutumnKite (赞：20)

打个广告：[蒟蒻的博客](https://www.cnblogs.com/rill7747/p/9869529.html)

# 题意

有一棵$n$个节点的以1为根的树，有$m$条边已知，并且有$q$个限制$a_i,b_i,c_i$，需要满足$\mathrm{LCA}(a_i,b_i)=c_i$。求满足条件的树的数量。

$m<n\le 13,q\le 100$。

# 题解

树形状压DP。DP状态很显然，$dp_{u,mask}$表示以$u$为根，由$mask$这些点组成的子树的方案数。$mask$是一个二进制状态。

为方便讨论，以下题解和代码节点编号从$0$开始。

## 转移方程

$$dp_{u,mask}=\sum dp_{v,submask}\times dp_{u,mask\oplus submask}$$

$\oplus$表示的是异或($xor$)运算。

但是，我们直接枚举$v,submask$会有重复，例如一棵二叉树，根为$root$，左右儿子分别为$leftson,rightson$。当枚举$v=leftson$时会计算这棵树，$v=rightson$时又会计算这棵树，就会出现重复。

所以，我们规定一个点$pos\in mask\ (pos\ne u)$，强制$pos$在$submask$中才能转移。

## 转移条件

题目中有两种限制条件，分别为边和$\mathrm{LCA}$。

1. 对于$\mathrm{LCA}$的限制：
    1.1. 对于限制$(a,b,c)$，如果$c=u$，但是$a,b\in submask$，那么$\mathrm{LCA}$一定不为$c$，不满足条件。
    1.2. 对于限制$(a,b,c)$， 如果$c\in submask$，但$a,b$中有**至少**一个不在$submask$中，则$\mathrm{LCA}$一定不为$c$，不满足条件。
2. 对于边的限制：
    2.1. 对于边$(x,y)$，如果$x,y\ne u$，但是$x,y$其中一个在$submask$中，另一个不在，则这条边不可能在树上，不满足条件。
    2.2. 如果$u$与$i$有边且$i\in submask$的$i$的数量大于1，则不可能有满足条件的树，不满足条件。

在2.2中，如果这样的$i$的数量等于1，则转移时$v$不用枚举，$v$只能是那个$i$。否则$v$需要在$submask$中枚举。

## 关于复杂度

子集枚举可以用`for (register int submask = mask; submask; submask = (submask - 1) & mask)`。

此时复杂度并不是$O(4^n)$，而是$O(3^n)$，因为每次枚举到的$submask$一定是$mask$的子集。状态数为$3^n$。

因为此时$n$个数有三种状态：不在$mask$中，在$mask$但不在$submask$中，在$submask$中。所以是$3^n$。

所以复杂度为$O(3^nn(n+q+m))$。

观察代码可以发现这个复杂度非常不满，很多状态和子集是没用的。加上CF的评测机速度，还是可以过的。

# 代码

[Code](http://codeforces.com/problemset/submission/599/45029702) 实测93ms

```cpp
#include <cstdio>
#include <cstring>
int n, m, q, edge[15][15];
struct Edge{ int x, y; } E[15];
struct node{ int x, y, z; } a[105];
long long dp[15][100005];
bool in(int x, int s){ return s & (1 << x); }
long long dfs(int u, int mask){ // 用记搜实现
	long long &res = dp[u][mask];
	if (~res) return res;
	res = 0, mask -= 1 << u;
	int pos;
	for (pos = 0; pos < n; ++pos) if (in(pos, mask)) break; // 强制pos在submask中
	for (register int submask = mask; submask; submask = (submask - 1) & mask) // 枚举子集
		if (in(pos, submask)){
			int flag = 1, v, cnt = 0;
            // 条件1.1
			for (register int i = 1; i <= q; ++i)
				if (a[i].z == u && in(a[i].x, submask) && in(a[i].y, submask))
					{ flag = 0; break; }
			if (!flag) continue;
            // 条件1.2
			for (register int i = 1; i <= q; ++i) 
				if (in(a[i].z, submask) && (!in(a[i].x, submask) || !in(a[i].y, submask)))
					{ flag = 0; break; }
            if (!flag) continue;
            // 条件2.1
			for (register int i = 1; i <= m; ++i)
					if (E[i].x != u && E[i].y != u && (in(E[i].x, submask) ^ in(E[i].y, submask)))
						{ flag = 0; break; }
			if (!flag) continue;
            // 条件2.2
			for (register int i = 0; i < n; ++i)
				if (edge[u][i] && in(i, submask)){ ++cnt; v = i; }
			if (cnt > 1) continue;
			if (cnt == 1) res += dfs(v, submask) * dfs(u, mask ^ submask ^ (1 << u));
			else{
				for (v = 0; v < n; ++v)
					if (in(v, submask)) res += dfs(v, submask) * dfs(u, mask ^ submask ^ (1 << u)); // 转移方程
			}
		}
	return res;
}
int main(){
	scanf("%d%d%d", &n, &m, &q);
	for (register int i = 1; i <= m; ++i)
		scanf("%d%d", &E[i].x, &E[i].y), --E[i].x, --E[i].y, // 编号从0开始
		edge[E[i].x][E[i].y] = edge[E[i].y][E[i].x] = 1;
	for (register int i = 1; i <= q; ++i)
		scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z), --a[i].x, --a[i].y, --a[i].z; // 同上
	memset(dp, -1, sizeof dp);
	for (register int i = 0; i < n; ++i) dp[i][1 << i] = 1; // 初始化
	printf("%lld", dfs(0, (1 << n) - 1));
}
```

---

## 作者：Rorschachindark (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF599E)
# 题目大意
给出 $n,m,q$，表示树有 $n$ 个点，有 $m$ 对关系，其中关系 $x\to y$，表示树中存在 $x\leftrightarrow y$ 的边，$q$ 组关系$a,b,c$ 表示树中 $a,b$ 的最近公共祖先为 $c$。问有多少棵树满足条件。

树以 $1$ 为根，$m\le n\le 13,q\le 100$
# 思路
这篇博客主要是讲一些细节问题，一些自己在实现的时候碰到的问题，如果你想要看思路，请去别的题解观看。

首先不难想到一个想法，我们设 $f_{i,S}$ 表示以 $i$ 为根，子树状态为 $S$ 的方案数。然后我们可以得到一个类似于树形背包的转移：

$$f_{i,S}=\sum_{k=1,T}^{n}f_{i,S\otimes T}\times f_{j,T}$$

然后你发现这样做就行了，不过还有一些细节问题需要注意。

- 如何避免算重

首先我们知道如果直接按这个式子算我们肯定是会算重的，因为子树遍历顺序不一样，但树的形态相同。对于这个问题可以想到，我们可以强行钦定一个顺序，就是说我们可以强行钦定我现在新增的子树应该包含哪个点，因为一个点不可能出现在两个子树所以这样就确定了顺序。

- 如何保证边的条件

我们发现其实在每个子树判断的时候只需要判断每条边连接的两个点是否在同一个子树即可。因为不相邻的话一定会在树上某个地方被发现了不合法。

- 如何保证最近公共祖先的条件

你发现无非就两种：

1. 公共祖先为 $i$，但是两个节点都在新增子树里面

这样显然 $i$ 不是最近公共祖先。

2. 祖先都在子树里面了，但是两个节点任一一个不在

这样显然不合法。

---

然后你发现你按照这样写的东西过不掉样例，于是你发现有下面几个细节：

1. 合法性的判断

你发现实际上我们不能判断当前 $S$ 的合法性而应该去判断 $T$ 的合法性，因为 $S$ 有可能还需要和其它子树合并，你可能一开始不合法，合并后就合法了。

2. 边的合法性

实际上如果你当前节点连的点在新增子树里面为 $1$ 的话，那那个节点一定是当前节点的儿子，特判一下就好了。

这儿说明一下，因为本来你的合法性判断可以把这种情况判掉，但是因为你合法性判断只判断子树了，就不会排除掉这种情况，就需要手动判掉。

3. 记得开 $\text{long long}$

# $\text{Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define int long long
#define MAXN 14

template <typename T> inline void read (T &t){t = 0;char c = getchar();int f = 1;while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}while (c >= '0' && c <= '9'){t = (t << 3) + (t << 1) + c - '0';c = getchar();} t *= f;}
template <typename T,typename ... Args> inline void read (T &t,Args&... args){read (t);read (args...);}
template <typename T> inline void write (T x){if (x < 0){x = -x;putchar ('-');}if (x > 9) write (x / 10);putchar (x % 10 + '0');}

int n,m,q,up,dp[MAXN][1 << MAXN],Edge[MAXN][2],LCA[105][3];

bool inside (int S,int x){return (S >> x - 1 & 1);}

signed main(){
	read (n,m,q),up = 1 << n;
	for (Int i = 1;i <= m;++ i) read (Edge[i][0],Edge[i][1]);
	for (Int i = 1,a,b,c;i <= q;++ i) read (a,b,c),LCA[i][0] = a,LCA[i][1] = b,LCA[i][2] = c;
	for (Int i = 1;i <= n;++ i) dp[i][1 << i - 1] = 1;
	for (Int S = 1;S < up;++ S){
		for (Int i = 1;i <= n;++ i){
			if (!(S >> i - 1 & 1)) continue;
			int moveto;
			for (Int j = 1;j <= n;++ j) if (i != j && (S >> j - 1 & 1)){moveto = j;break;}
			int nowS = S ^ (1 << i - 1);
			for (Int T = nowS;T;T = (T - 1) & nowS){
				if (!inside (T,moveto)) continue;
				bool flag = 1;
				for (Int j = 1;j <= q;++ j){
					if (LCA[j][2] == i && inside (T,LCA[j][0]) && inside (T,LCA[j][1])){flag = 0;break;}
					if (inside (T,LCA[j][2]) && (!inside (T,LCA[j][0]) || !inside (T,LCA[j][1]))){flag = 0;break;}
				}
				for (Int j = 1;j <= m;++ j){
					if (Edge[j][0] == i || Edge[j][1] == i) continue;
					if (inside (T,Edge[j][0]) && !inside (T,Edge[j][1])){flag = 0;break;}
					if (!inside (T,Edge[j][1]) && inside (T,Edge[j][0])){flag = 0;break;}
				}
				if (!flag) continue;
				int to,cnt = 0;
				for (Int j = 1;j <= m;++ j){
					if (Edge[j][0] == i){if (inside (T,Edge[j][1])) cnt ++,to = Edge[j][1];}
					if (Edge[j][1] == i){if (inside (T,Edge[j][0])) cnt ++,to = Edge[j][0];}
				}
				if (!cnt){
					for (Int j = 1;j <= n;++ j) 
						if (inside (T,j)) dp[i][S] += dp[i][S ^ T] * dp[j][T];
				}
				else if (cnt == 1) dp[i][S] += dp[to][T] * dp[i][S ^ T];
			}
		}
	} 
	write (dp[1][up - 1]),putchar ('\n'); 
	return 0;
}
```

---

## 作者：pomelo_nene (赞：3)

根据 $n \leq 13$ 的数据范围猜测这是一个状压 dp。

于是定义 $dp_{i,S}$ 为以 $i$ 为根，其子树（包含自己）所包含的节点构成的状态为 $S$，有多少种构成一棵合法的子树的方法。考虑去转移这个东西，可以得到简单的 dp 式，即：

$$
dp_{u,S} = \sum_{T⊆S,v\in S} dp_{v,T} \times dp_{u,S \operatorname{xor} T}
$$

解释这个 dp 方程，考虑我们现在用其中的一些节点，状态为 $T$，构成一棵子树，其方案数为 $dp_{v,T}$；现在需要分完剩下的节点，发现实际上这是一个递归的过程，我们要处理以 $u$ 为根但状态更简单的情况，于是我们继续递归处理 $dp_{u,S \operatorname{xor} T}$。所以上面的 dp 是正确的。

但是仔细一下会发现我们会有算重的情况。因为子树的顺序不同，树还是同一棵树。为了除去算重的情况，钦定一个点作为特殊点 $p$，必须当 $T$ 的状态包含 $p$ 的时候才能够转移。钦定特殊点的行为实质上是钦定了子树的转移顺序，于是要保证同一个状态选择的特殊点是同一个。这份代码选的是 $S$ 的第一个。

有了这些信息考虑题目的 $\mathrm{LCA}$ 与边的限制。

- $\mathrm{LCA}$
  - 如果当前转移的 $u$ 是某一个限制的 $c_k$，那么状态 $T$ 不能同时包含 $a_k$ 和 $b_k$，因为这样会满足构成的树，$a_k$ 和 $b_k$ 的 ${c_k}'$ 会比 $c_k$ 更深，那么不合法；   
  - 如果发现 $c_k$ 在状态 $T$ 里面，然而 $a_k,b_k$ 中有一个，不存在于状态 $T$，那么不合法。

- 边
  - 如果存在一条边满足一条边的端点不在同一棵子树无法转移；   
  - 如果状态 $T$ 里面存在两个及以上的点要和 $u$ 相连，无法转移。
  
然后分情况讨论。状态 $T$ 里面不存在点要和 $u$ 相连，那我们枚举 $T$ 中的每一个点，相连判断；否则我们必须只能和一个点直接相连，直接向那个点转移即可。

细节有点多。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n,m,q,dp[14][(1<<13)],a[105],b[105],c[105],u[14],v[14];
LL dfs(LL now,LL S)
{ 
	if(~dp[now][S])	return dp[now][S];
//	printf("%d %d\n",now,S);
//	LL alive=S^(1<<(now-1));
	LL Fuck=S^(1<<(now-1));
	dp[now][S]=0;
	LL moved=1;
	while(!(Fuck&(1<<(moved-1))))	++moved;
	for(LL T=Fuck;T;T=(T-1)&Fuck)
	{
		LL cnt=0,to=0;
		if(!(T&(1<<(moved-1))))	continue;//避免重复强制规定一个点在子集中才能转移
		for(LL i=1;i<=q;++i)	if(now==c[i] && (T&(1<<(a[i]-1))) && (T&(1<<(b[i]-1))))	goto fail;//如果说当前这个点是 LCA，并且我们要转移的子树包含了另外两个点，不合法
		for(LL i=1;i<=q;++i)
		{
			if((T&(1<<(c[i]-1))))
			{
				if(!(T&(1<<(a[i]-1))) || !(T&(1<<(b[i]-1))))	goto fail;
			}
		}//如果说 LCA 在子树里面然而其他两个有任意一个不在里面无法转移
		for(LL i=1;i<=m;++i)
		{
			if(u[i]==now || v[i]==now)	continue;
			if((T&(1<<(u[i]-1))) && !(T&(1<<(v[i]-1))))	goto fail;
			if(!(T&(1<<(u[i]-1))) && (T&(1<<(v[i]-1))))	goto fail;
		}//如果存在一条边满足一条边的端点不在同一棵子树无法转移
		for(LL i=1;i<=m;++i)
		{
			if(u[i]==now)
			{
				if((T&(1<<(v[i]-1))))	++cnt,to=v[i];
			}
			else if(v[i]==now)
			{
				if((T&(1<<(u[i]-1))))	++cnt,to=u[i];
			}
		}
		if(cnt==0)
		{
			for(LL i=1;i<=n;++i)
				if((T&(1<<(i-1))))
					dp[now][S]+=dfs(i,T)*dfs(now,Fuck^T^(1<<(now-1)));
		}
		else if(cnt==1)
		{
			dp[now][S]+=dfs(to,T)*dfs(now,Fuck^T^(1<<(now-1)));
		}
		//有两条及以上直接相连的边，不合法
		fail:;
	}
//	S^=(1<<(now-1));
//	printf("%d %d:%d\n",now,S,dp[now][S]);
	return dp[now][S];
}
int main(){
	cin>>n>>m>>q;
	memset(dp,-1,sizeof dp);
	for(LL i=1;i<=n;++i)	dp[i][1<<(i-1)]=1;
	for(LL i=1;i<=m;++i)	cin>>u[i]>>v[i];
	for(LL i=1;i<=q;++i)	cin>>a[i]>>b[i]>>c[i];
	dfs(1,(1<<n)-1);
	cout<<dp[1][(1<<n)-1]<<endl;
	return 0;
}
```



---

## 作者：tzc_wk (赞：3)

> Codeforces 599E

> 题意：有一棵以 $1$ 为根的树。你忘记了它的形态，只记得 $m$ 条边 $(u_i,v_i)$，和 $k$ 条形如 " $a_i$ 和 $b_i$ 的 LCA 为 $c_i$ 的限制。求有多少棵符合要求的树。

> $1 \leq n,m \leq 13$，$1 \leq k \leq 100$

这道题分明有些毒瘤为什么 CF 上难度只有 2100？/yiw

首先看到 $1 \leq n \leq 13$ 就可以想到状压 $dp$。

设 $dp[i][j]$ 表示以 $i$ 为根的子树中，包含了状态集合为 $j$ 的合法的树的个数。$j$ 是一个二进制数，第 $0$ 位（最低位）为 $1$ 表示节点 $1$ 在状态集合中，第 $1$ 位为 $1$ 表示节点 $2$ 在状态集合中，以此类推。

状态转移方程：

- $dp[i][j]=dp[v][k] \times dp[i][j\  \operatorname{xor}\ k]$

其中 $k$ 是 $j$ 的子集。

由于题目对于边和 $lca$ 有限制，所以我们不能想怎么转移就怎么转移（废话），因此我们需要判断合法性：

那么有以下四种情况是不合法的：

1. 对于题目中给定的边，如果满足其中一个端点是 $i$，另一个端点属于状态集合 $k$ 当中，这样的边的个数 $\geq 2$，那么就是不合法的。原因是：$i$ 只能跟集合 $k$ 当中的一个点连边，那个点就是 $v$。因此我们可以枚举 $i,j$ 之后，外层枚举 $k$，再看看有几条边满足条件。如果有一条边满足条件，那么 $v$ 只能等于那条边的另一个端点。否则内层枚举 $v$ 然后转移。

2. 对于题目中给定的边 $(x,y)$，如果 $x \neq i$，$v \neq i$，但是 $u$ 在 $k$ 中，$v$ 不在 $k$ 中，这种条件也是不合法的。因为除了 $i$ 之外，集合 $k$ 中的点不能跟不在集合 $k$ 中的点之间有边。

3. 对于 LCA 的限制 $(a,b,c)$，如果 $c$ 在集合 $k$ 中，但是 $a$ 或 $b$ 不在，那么就不行。这个应该是最好理解的了。

4. 对于 LCA 的限制 $(a,b,c)$，如果 $c=i$，但是 $a,b$ 都在 $k$ 中也不行。因为这样一来 $lca(a,b)$ 一定是 $k$ 中的另外一个点而不是 $i$ 了。

边界 $dp[i+1][2^{i}]=1$

最终的答案就是 $dp[1][2^n-1]$

时间复杂度：枚举子集 $3^n$，内层枚举 $v$ 并判断最坏是 $nk$ 的，所以总复杂度是 $\mathcal O(nk3^n)$

注意事项：

1. 由于 $dp[i][j\ \operatorname{xor}\ k]$，会转移到 $dp[i][j]$，所以需要外层枚举 $j$，内层枚举 $i$

2. 对于同一棵树，我们枚举了一次它的第一棵子树，接着又枚举了它第二棵子树，这样同一棵树会被重复计算。因此我们需要任取一个 $j$ 中与 $i$ 不相等的点 $fst$，并强制它在 $msk$ 中，这样就不会重复计算了。

~~写题解不容易，给个赞呗~~

```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
#define int long long
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
int n=read(),m=read(),q=read();
int a[105],b[105],c[105],u[15],v[15];
vector<int> g[15];
int dp[14][8193];
signed main(){
	fz(i,1,m)	u[i]=read(),v[i]=read(),g[u[i]].push_back(v[i]),g[v[i]].push_back(u[i]);
	fz(i,1,q)	a[i]=read(),b[i]=read(),c[i]=read();
	for(int j=0;j<(1<<n);j++){
		for(int i=1;i<=n;i++){
			if(__builtin_popcount(j)==1&&_bit(j,i-1)){
				dp[i][j]=1;
				continue;
			}
			if(!_bit(j,i-1))	continue;
			int msk=j-mask(i-1);
			int fst=0;
			for(int t=1;t<=n;t++)
				if(_bit(msk,t-1)){
					fst=t;
					break;
				}
//			cout<<msk<<endl;
//			cout<<"fst="<<fst<<endl;
			for(int k=msk;k;k=msk&(k-1)){
				if(_bit(k,fst-1)){
					int l=k^j;
					int cnt=0,s=0;
					foreach(it,g[i]){
						int p=*it;
						if(_bit(k,p-1))	s=p,cnt++;
					}
					if(cnt>=2)	continue;
					bool flag=1;
					for(int p=1;p<=m;p++){
						if(u[p]==i||v[p]==i)	continue;
						if(_bit(k,u[p]-1)&&!_bit(k,v[p]-1))	flag=0;
						if(_bit(k,v[p]-1)&&!_bit(k,u[p]-1))	flag=0;
					}
					for(int r=1;r<=q;r++){
						if(_bit(k,c[r]-1)&&(!_bit(k,a[r]-1)||!_bit(k,b[r]-1)))	flag=0;
						if(c[r]==i&&_bit(k,a[r]-1)&&_bit(k,b[r]-1))				flag=0;
					}
					if(!flag)	continue;
//					int tmp=dp[i][j];
					if(!cnt){
						for(int o=1;o<=n;o++){
							if(i!=o&&_bit(k,o-1))	dp[i][j]+=dp[i][l]*dp[o][k];
						}
					}
					else{
						dp[i][j]+=dp[i][l]*dp[s][k];
					}
//					cout<<i<<" "<<j<<" "<<k<<" "<<dp[i][j]-tmp<<endl;
				}
			}
//			cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
		}
	}
	cout<<dp[1][(1<<n)-1]<<endl;
	return 0;
}
```

---

## 作者：crashed (赞：2)

&emsp;&emsp;**去往[原博客](https://www.cnblogs.com/crashed/p/13395632.html)食用更佳。**    
# 题目
&emsp;&emsp;[点这里](https://www.luogu.com.cn/problem/CF599E)看题目。  
# 分析
&emsp;&emsp;首先我们可以考虑不存在任何限制的时候该怎么做。   
&emsp;&emsp;~~根据 $Pr\overset{..}{u}fer$ 序列直接得出答案为 $n^{n-2}$ 。~~     
&emsp;&emsp;忽略那种做法，因为它难以处理 LCA 的限制。看到 $n$ 很小，我们可以想到一个状态压缩的 DP :    
&emsp;&emsp;$f(u,S)$：以 $u$ 为根的子树中点集为 $S$ 的方案数。   
&emsp;&emsp;为了方便，以下我们也就用 $(u,S)$ 表示一棵根为 $u$ ，点集为 $S$ 的子树。      
&emsp;&emsp;之后，边界条件为 $f(u,\{u\})=1$ ，答案就是 $f(1,V)$ 。    
&emsp;&emsp;然后存在转移：    
$$f(u,S)=\sum_{v\in T\subseteq S} f(u,S\setminus T)\times f(v,T)$$    
&emsp;&emsp;直接转移会重复计数。例如这种情况：   
> &emsp;&emsp;$(u,S)$ 有两棵子树 $(v,S_1)$ 和 $(w,S_2)$ ，满足 $S=S_1\cup S_2\cup \{u\}$ 。  

&emsp;&emsp;那么 $f(u,S\setminus S_1)\times f(v,S_1)$ 和 $f(u,S\setminus S_2)\times f(w,S_2)$ 都会计算这种情况。   
&emsp;&emsp;为了规避重复计算，我们需要钦定一个不为 $u$ 特殊点，每次**只枚举包含特殊点的 $(v,T)$ 进行转移**。     
&emsp;&emsp;这就相当于始终在**枚举特殊点所在的子树的情况**，可以发现这样可以做到不重不漏。    
&emsp;&emsp;那么考虑题目给出的限制，实际上就是在限制 DP 的转移。分开考虑：   
&emsp;&emsp;先考虑 LCA 的限制等价于：   
&emsp;&emsp;1. 对于树 $(u, S)$，如果存在 $k$ ，使得 $c_k=u$ ，那么 $a_i,b_i$ 不能在同一个子树内，即不能进行 $a_i\in T\land b_i\in T$ 的转移。   
&emsp;&emsp;2. 对于转移的子树 $(v, T)$， 如果存在 $k$ ，使得 $c_k\in T$ ，那么 $a_i,b_i$ 也应该在 $(v,T)$ 里面，即不能进行 $a_i\not\in T\lor b_i\not\in T$ 的转移。     
&emsp;&emsp;再考虑边的限制。一条边$(u,v)$同时包含了 *$u$ 是 $v$ 的父亲* 和 *$v$ 是 $u$ 的父亲* 两种情况，而前者在 $f(u,S)$ 中计算，后者在 $f(v,S)$ 中计算。故转移中我们只需要考虑 $u$ 作为父亲的情况。      
&emsp;&emsp;因而一条边等价于：    
&emsp;&emsp;3. 对于树 $(u,S)$，如果不存在 $k$ 使得 $u$ 在限制边 $E_k=(x,y)$ 上，那么转移的子树中，要么 $x\not\in T\land y\not \in T$ ，要么 $x\in T\land y\in T$ 。    
&emsp;&emsp;4. 对于树 $(u,S)$，如果存在 $k$ ，使得 $u$ 在限制边 $E_k=(u,w)$ 上，那么转移的子树**只能**是 $(w, T)$ ，而且 $T$ 里面**只能包含 $w$ 一个与 $u$ 有关的限制边端点**。      
&emsp;&emsp;在转移中途判断一下即可。同样的道理，写状压尽量记搜，因为状态的阶段通常是由 $|S|$ 划分的。   
&emsp;&emsp;时间是 $O(3^nk(n+m+q))$ 。 ~~CF 机子是出了名的快。~~   
# 代码
```cpp
#include <cstdio>
#include <cstring>

typedef long long LL;

const int MAXN = 15, MAXM = 105, MAXS = ( 1 << 13 ) + 5;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

LL f[MAXN][MAXS];
int LCARis[MAXM], LCAc[MAXM];
int Eu[MAXM], Ev[MAXM], ERis[MAXN];
int bit[MAXS], ref[MAXN];
int N, M, Q;

int mono( const int u ) { return 1 << u - 1; }
int lowbit( const int x ) { return x & ( -x ); }
int inter( const int S, const int T ) { return S & T; }
bool chk( const int S ) { return ! ( S - lowbit( S ) ); }
bool in( const int S, const int T ) { return ( S & T ) == T; }
bool onE( const int u, const int id ) { return Eu[id] == u || Ev[id] == u; }

LL DFS( const int u, const int S )
{
	LL& ret = f[u][S];

	if( ~ ret ) return ret; ret = 0;
	if( ! in( S, ref[u] ) ) return ret = 0;
	
	int pos; bool flag;
	for( pos = 1 ; pos <= N ; pos ++ ) 
		if( pos ^ u && in( S, ref[pos] ) ) break;
	for( int T = ( S - 1 ) & S ; T ; T = ( T - 1 ) & S )
		if( in( T, ref[pos] ) && ! in( T, ref[u] ) )
		{
			flag = true;
			for( int i = 1 ; i <= Q ; i ++ )
				if( LCAc[i] == u && in( T, LCARis[i] ) )
					{ flag = false; break; }
                        //处理限制 1
			if( ! flag ) continue;
			for( int i = 1 ; i <= Q ; i ++ )
				if( in( T, ref[LCAc[i]] ) && ! in( T, LCARis[i] ) )
					{ flag = false; break; }
                        //处理限制 2
			if( ! flag ) continue;
			for( int i = 1 ; i <= M ; i ++ )
				if( ! onE( u, i ) && ( in( T, ref[Eu[i]] ) ^ in( T, ref[Ev[i]] ) ) )
					{ flag = false; break; }
                        //处理限制 3
			if( ! flag ) continue;
			if( ! inter( T, ERis[u] ) )
			{
				for( int i = 1 ; i <= N ; i ++ )
					if( in( T, ref[i] ) )
						ret += DFS( u, S ^ T ) * DFS( i, T );
			}
                        //如果不包含任何限制边就枚举根进行转移
			else if( chk( T & ERis[u] ) )
				ret += DFS( u, S ^ T ) * DFS( bit[lowbit( T & ERis[u] )], T );
                        //否则需要钦定根转移  
		}
	return ret;
}

int main()
{
	read( N ), read( M ), read( Q );
	memset( f, -1, sizeof f );
	for( int i = 1 ; i <= N ; i ++ ) f[i][1 << i - 1] = 1, bit[ref[i] = ( 1 << i - 1 )] = i;
	for( int i = 1 ; i <= M ; i ++ ) 
		read( Eu[i] ), read( Ev[i] ), 
		ERis[Eu[i]] |= ref[Ev[i]], ERis[Ev[i]] |= ref[Eu[i]];
	for( int i = 1, a, b ; i <= Q ; i ++ ) 
		read( a ), read( b ), read( LCAc[i] ), 
		LCARis[i] = ref[a] | ref[b];
	write( DFS( 1, ( 1 << N ) - 1 ) ), putchar( '\n' );
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

`*2600` 的题做了一个小时？？没救了。

设 $dp_{u,S}$ 为：以 $u$ 为根的子树，子树节点集合是 $S$ 的方案数。

显然我们要将 $S/\{u\}$ 划分为若干子集 $S_1$、$S_2$、$\cdots$、$S_k$，并且钦定它们的根 $r_1$、$r_2$、$\cdots$、$r_k$。

要满足几个性质：

1. $S_i$ 中只能有 $r_i$ 与 $u$ 有连边。
2. LCA 的限制分成两种，限制祖先型（只需要保证 $v \in S$ 即可）和分属两子树型（需要两个点在不同的 $S$ 中）。
3. 不同的 $S$ 之间没有连边。

考虑直接枚举划分是不太靠谱的，因此设辅助数组 $tmp_{u,S}$ 为以 $u$ 为根的子树，已经包含了 $S$ 中的节点的方案数。

每次考虑合并 $tmp_{u,S}$ 和 $dp_{k,T}$（将 $k$ 连在 $u$ 下）。（为了防止算重，应该有 $T$ 包含 $S \cup T$ 的最小元素。）只需要枚举子集，看看是否满足上面三条性质即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=15;
int n,m,q,dp[MAXN][1<<MAXN],tmp[MAXN][1<<MAXN],son[MAXN],ed[MAXN],al[1<<MAXN];
vector<pair<int,int>> info[MAXN];
int check(int u,int s1,int s2,int v) {
	if(ed[u]&s2) if((ed[u]&s2)!=(1<<v-1)) return 0;
	if(al[s1]&s2) return 0;
	if(al[s2]&s1) return 0;	
	for(auto pr:info[u]) if(pr.first!=u&&pr.second!=u) {
		if(((s1|s2)&(1<<pr.first-1))&&((s1|s2)&(1<<pr.second-1))) {
			if(!(s1&((1<<pr.first-1)+(1<<pr.second-1)))) return 0;
		}
	}
	return 1;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>q;
	ffor(i,1,m) {int u,v;cin>>u>>v,ed[u]|=(1<<v-1),ed[v]|=(1<<u-1);}
	ffor(i,1,q) {
		int a,b,c;
		cin>>a>>b>>c;
		if(a!=c&&b!=c) info[c].push_back({a,b});
		if(a!=c) son[c]|=(1<<a-1);	
		if(b!=c) son[c]|=(1<<b-1);
	}
	ffor(i,1,(1<<n)-1) ffor(j,1,n) if(i&(1<<j-1)) al[i]|=ed[j];
	ffor(i,1,(1<<n)-1) {
		if(__builtin_popcount(i)==1) {
			int k=(log2(i)+1);
			tmp[k][i]=1;
			if(son[k]==0) dp[k][i]=1;
			continue ;
		}
		ffor(j,1,n) if(i&(1<<j-1)) {
			int ot=i-(1<<j-1),S=ot-(ot&-ot);
			ffor(k,1,n) if(ot&(1<<k-1)) if(check(j,0,ot,k)) tmp[j][i]+=dp[k][ot];
			for(int s=S;s;s=(s-1)&S) {
				ffor(k,1,n) if((ot-s)&(1<<k-1)) if(check(j,s,ot-s,k)) tmp[j][i]+=tmp[j][s+(1<<j-1)]*dp[k][ot-s];
			}
			if((son[j]&i)==son[j]) dp[j][i]=tmp[j][i];
		}
	}
	cout<<dp[1][(1<<n)-1];
	return 0;
}
```

---

## 作者：Trafford1894 (赞：0)

$n \leq 13$，显然状压。

设 $dp_{u,S}$ 表示以 $u$ 为根，这个子树的点集为 $S$ 的方案数。显然有转移：$dp_{u,S} = \sum \limits_{T \subseteq S,v\in E_u}dp_{v,T} \times dp_{u,S-T}$。（这里的减号是差集，在实操的时候要异或）

这时候我们发现会算重。具体而言，我们会在按照不同的顺序枚举同一个子树。因此，考虑限定枚举顺序。随意取出一个异于根节点的点，钦定 $T$ 必须包含此节点就能解决算重的问题。

此时，我们需考虑转移的限制。
- $\text{LCA}$ 的限制
  - 如果对于一条限制 $(a,b,c)$，满足 $c=u$ 且 $a,b \in T$，显然不合法。
  - 如果对于一条限制 $(a,b,c)$，满足 $c \in T$ 且 $a \notin T \lor b \notin T$，显然不合法。
- 边的限制
  - 如果有大于一条边 $(a,b)$，满足 $a = u \land b \in T$，显然不合法。
  - 如果有一条边 $(a,b)$，满足 $x,y \neq u \land a\in T \land b \notin T$，显然不合法。
  
把不合法的状态剪去即可。
  
代码上可用记搜实现，具体地，想要获得 $T$ 要枚举 $S$ 的子集。有经典套路可做到 $O(3^n)$ 而不是 $O(4^n)$。

还要注意一点，在搜索时先把 $u$ 的状态从 $S$ 里面扣掉，这样就能避免一坨边界讨论。往下递归的时候把 $u$ 的状态再加进去就行了。

于是做完了，时间复杂度 $O(3^n n(n+m+q))$。实际上由于无用状态极多，三秒时限完全卡不满。

[参考代码。](https://www.luogu.com.cn/paste/uzcq4eo7)

---

## 作者：Hehe_0 (赞：0)

 题目 ：  
 有一棵 $ n $ 个有标号节点的树，根节点为 1，有 $ m $ 条边已经 被确定，另有 $ q $ 限制，形式为：节点 $a_i $ 与  $ b_i $ 的 $ LCA  $ 为 $c_ i$ 你需要求出这棵树有多少种不同的可能形态 $n ≤ 13, q ≤ 100$
 
 


------------
看到 $ n $ 的范围，想状压


- 令  $ f_{rt,msk} $ 表示根节点为  $ rt $ ,子树中的点集为  $ msk $ ，这棵子树中有多少不同的方案

- 转移形式 大 致 ：  $ f_{rt,msk} =  \sum _{x\in msk} f_{rtx,x} *  f_{t,msk-x} $  

- 即每次找出 $ rt $ 的一个儿子子树，然后去掉这个子树以后剩下的还是以 $ rt $ 为根的子树。

  为了防止重复计数，我们可以强制  $ x $ 包含   $ msk $ 中最小的节点。



接下来考虑限制条件

- 对于强制连边，如果 $ rt $ 和 $ msk $ 中的一个点 $ v $ 要强制连边，那么转移时如果  $ v\in x $  ,那么 rtx必须为 $ v $

- 对于 $ lca $ 的限制，如果有一组限制要求  $ u,  v $  的 $ lca $ 为 $ rt $ ，  那么 $ u, v\in rt $ 必须满足，而且$ u, v $在上述转移中不能同 时属于 $ x $

时间复杂度 $ O(3^n ∗ poly(n, m, q)) $，其中 $ poly(n, m, q) $ 表 示只与   n, m, q  有关的多项式复杂度.  


###### 代码略



---

