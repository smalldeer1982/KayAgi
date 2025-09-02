# [ABC293Ex] Optimal Path Decomposition

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc293/tasks/abc293_h

$ N $ 頂点の木が与えられます。頂点には $ 1 $ から $ N $ までの番号がついており、$ i $ 番目の辺は頂点 $ A_i $ と頂点 $ B_i $ を結んでいます。

各頂点に以下の条件を満たすように色を塗ることができる整数 $ K $ の最小値を求めてください。ただし、使える色の種類数に制限はありません。

- 各色について、その色で塗られた頂点の集合は連結で単純パスをなす
- 任意の木上の単純パスについて、そのパス内に含まれる頂点に塗られた色の種類数は $ K $ 以下

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ N $
- 与えられるグラフは木
- 入力はすべて整数

### Sample Explanation 1

$ K\ =\ 3 $ のとき、頂点 $ 1,2,3,4,5 $ を色 $ 1 $、頂点 $ 6 $ を色 $ 2 $、頂点 $ 7 $ を色 $ 3 $ で塗るなどの方法で条件を満たすことができます。 $ K\ \leq\ 2 $ とすると条件を満たす色の塗り方は存在しないので答えは $ 3 $ です。

## 样例 #1

### 输入

```
7
3 4
1 5
4 5
1 2
7 4
1 6```

### 输出

```
3```

## 样例 #2

### 输入

```
6
3 5
6 4
6 3
4 2
1 5```

### 输出

```
1```

## 样例 #3

### 输入

```
9
1 3
9 5
8 7
2 1
5 2
5 8
4 8
6 1```

### 输出

```
3```

# 题解

## 作者：hegm (赞：10)

### [Optimal Path Decomposition](https://www.luogu.com.cn/problem/AT_abc293_h)

$\text{Upd:}2024/12/12$ 修改了部分笔误，更新了 $\LaTeX$。 

考虑 `dp` ：

$dp_{i,0/1}$ 表示解决完 $i$ 的子树后经过 $i$ 的路径的最多颜色数，其中 $i$ 是/不是拐角。

但是感觉这样不是很好转移，简单来说，对于某个节点 $i$ 有两种决策，让自己子树中的最长段最短，或者让在父亲位置的最长段最短。即，它是有后效性的。

然而直接 `dp` 是无法平衡这两种情况的。

所以我们可以在 `dp` 开始的时候二分一个答案，以此来限制 $i$ 节点的决策。

具体的，对于 $i$ （以下，写为 $u$）号节点，有以下两种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/e36snk50.png)

1. $u$ 染成和某个孩子相同的颜色。

![](https://cdn.luogu.com.cn/upload/image_hosting/mdg5tnlr.png)

2. $u$ 的某两个孩子颜色相同，同时为了保证简单路径性质， $u$ 必须和两者颜色相同。

![](https://cdn.luogu.com.cn/upload/image_hosting/br829ulo.png)

那么考虑两种情况中，$u$ 分别应该取什么颜色：

在此之前，我们要明确一件事情，对于情况 $2$，$u$ 能作为哪些连接点的媒介。

![](https://cdn.luogu.com.cn/upload/image_hosting/gisr6vx4.png)

看看如上的情况，我们的 $u$ 是不能作为两点的媒介的，因为红色孩子已经是媒介点了，又因为我们要保证简单路径的性质，所以 $u$ 号节点是不能作为红色节点的。

设 $dp_i$ 表示以 $i$ 为根的子树中，终止节点为 $i$ 的路径中，颜色数最多的为多少。

$id_i$ 表示的是 $i$ 点满足上述值的时候是否是媒介点。

那么现在能大致理清思路了，对于 $u$ 号节点，需要根据他孩子的情况以及二分的值来判断他是否为媒介点。具体如何判断，等我们分析完贡献再进行阐述。

现在分讨每种情况的贡献：

>一些变量：$a$ 为 $dp$ 最大的子节点，$b$ 为次大，$c$ 为次次大，$d$ 为次次次大，他们的 $id=0$。$e$ $dp$ 最大的子节点，$f$ 为次大，他们的 $id=1$。

~~别急着吐槽变量~~

1. $u$ 不作为媒介点：

![](https://cdn.luogu.com.cn/upload/image_hosting/h0a4ay7t.png)

如果先不考虑 $u$ 的颜色，那么 $u$ 的 $dp$ 应该是所有 $v\in son_i$ 的 $dp$ 最大值，换句话说 $dp_u=\max(dp_a,dp_e)$。

考虑加上 $u$ 的颜色，那么 $u$ 可以和 $a$ 颜色相同，其余的和 $u$ 颜色不同，所以 $dp_u=\max(dp_a,dp_b+1,dp_e+1)$，容易证明 $u$ 为其他颜色是不优或者不合法的。

那么 $u$ 对最大值的贡献又是什么？其实就是将孩子的最长链拼在一起的同时加上 $u$ 的贡献。

由于此情况下保证 $u$ 不作为转折点，所以答案也很简单：

![](https://cdn.luogu.com.cn/upload/image_hosting/n38cr579.png)
（设 $ans_i$ 为 $i$ 子树中的最长颜色段数）
$ans_i=\max(dp_a+dp_b,dp_a+dp_e,dp_b+dp_e+1,dp_b+dp_c+1,dp_f+dp_e+1)$

2. $u$ 作为媒介点：

![](https://cdn.luogu.com.cn/upload/image_hosting/h0a4ay7t.png)

不考虑 $u$ 的颜色：$ans_i=\max(dp_a+dp_b,dp_e+dp_f,dp_e+dp_a)$

现在考虑加入 $u$ 的颜色，因为要让 $ans_i$ 变小，同时又无法修改 $e,f$ 所以我们只能修改 $a,b$。也就是让 $a,b$ 颜色相同。

![](https://cdn.luogu.com.cn/upload/image_hosting/gztlrw1a.png)

那么答案就是 $ans_i=\max(dp_a+dp_b-1,dp_a+dp_c,dp_a+dp_e,dp_e+dp_f+1,dp_c+dp_d+1,dp_e+dp_c+1)$

$dp_i=\max(dp_a,dp_c+1,dp_e+1)$

现在分讨完成，需要考虑如何判断 $i$ 是否应该作为媒介点了。

依然要大力分讨。同时，我们在 $ans_i$ 后面加一维 $0/1$ 表示不是 $/$ 是媒介点的答案。

1. 容易发现 $ans_{i,1}$ 是肯定比 $ans_{i,0}$ 优的。所以$ans_{i,1}>lim$（二分的限制）的时候，返回无解即可。

2. $ans_{i,0}>lim\ge ans_{i,1}$，所以不得不选择作为媒介点，如果不这样做是不合法的。

3. $lim>ans_{i,0},ans_{i,1}$ 这是需要进一步讨论选哪一个更优秀：

	- 观察 $dp_{i,0/1}$ 可以发现，$dp_{i,1}$ 是不劣于 $dp_{i,0}$ 的，因此，如果两者相等，$i$ 作为媒介点的情况对父亲的贡献一定为 $dp_{i,1}+1$，而不作为媒介点的贡献最劣为 $dp_{i,0}+1$，$1$ 的唯一和 $0$ 的最劣相等，因此选择 $0$ 情况一定最优。
    - 否则的话 $dp_{i,1}<dp_{i,0}$，依然考虑上升到父亲，$dp_{i,1}$ 肯定会对父亲产生 $dp_{i,1}+1$ 的贡献。而 $dp_{i,0}$ 的贡献最优即为 $dp_{i,0}$，但是上述条件有 $dp_{i,1}<dp_{i,0}$ 也就是说 $dp_{i,1}+1\le dp_{i,0}$，所以此时 $dp_{i,1}$ 的唯一情况和 $dp_{i,0}$ 的最优情况等价，所以可以保证不会更劣。
    
一些问题：
- 如果真的想对上面一堆数值求和也可以，当然你可以使用另一种方法，容易发现对于 $u$ 的颜色，和 $u$ 颜色相同的和别的点组合时答案会减一，那么我们把所有的点进行排序，由于只有常数个，所以复杂度不变。

- 上面证明可以证明到父亲的时候不劣，但是到更远祖先的地方会如何？考虑到了父亲之后，$dp_{i,0}$ 对父亲的贡献是相同的，然后再到更远的父亲，此时祖先是否能是父亲的媒介是不受 $u$ 影响的，所以 $u$ 的贡献不会因为变远而改变。

### $\text{CODE}$

```cpp
#include<bits/stdc++.h>
#define N 1000005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
struct fig
{
	int to,next;
}k[N*2];int tot,head[N];
int n,lim;
bool fail;
void add(int from,int to)
{
	k[++tot].to=to;
	k[tot].next=head[from];
	head[from]=tot;
}
int dp[N],id[N];
bool cmp(int a,int b){return a>b;}
void dfs(int now,int fa)
{
	if(fail)return;
	int a=0,b=0,c=0,d=0,e=0,f=0,x=0,y=0,z=0,m=0;
	for(int i=head[now];i;i=k[i].next)
	{
		if(k[i].to==fa)continue;
		dfs(k[i].to,now);
	}
	for(int i=head[now];i;i=k[i].next)if(id[k[i].to]==0&&a<dp[k[i].to]&&k[i].to!=fa)a=dp[k[i].to],x=k[i].to;
	for(int i=head[now];i;i=k[i].next)if(id[k[i].to]==0&&b<dp[k[i].to]&&k[i].to!=fa&&k[i].to!=x)b=dp[k[i].to],y=k[i].to;
	for(int i=head[now];i;i=k[i].next)if(id[k[i].to]==0&&c<dp[k[i].to]&&k[i].to!=fa&&k[i].to!=x&&k[i].to!=y)c=dp[k[i].to],z=k[i].to;
	for(int i=head[now];i;i=k[i].next)if(id[k[i].to]==0&&d<dp[k[i].to]&&k[i].to!=fa&&k[i].to!=x&&k[i].to!=y&&k[i].to!=z)d=dp[k[i].to];
	for(int i=head[now];i;i=k[i].next)if(id[k[i].to]==1&&e<dp[k[i].to]&&k[i].to!=fa)e=dp[k[i].to],m=k[i].to;
	for(int i=head[now];i;i=k[i].next)if(id[k[i].to]==1&&f<dp[k[i].to]&&k[i].to!=fa&&k[i].to!=m)f=dp[k[i].to];
	vector<int> v1,v2;
	v1.push_back(a-1);v1.push_back(b-1);v1.push_back(c);v1.push_back(d);v1.push_back(e);v1.push_back(f);
	v2.push_back(a-1);v2.push_back(b);v2.push_back(c);v2.push_back(d);v2.push_back(e);v2.push_back(f);
	sort(v1.begin(),v1.end(),cmp);
	sort(v2.begin(),v2.end(),cmp);
	if(v1[0]+v1[1]+1>lim)
	{
		fail=1;
		return;
	}
	if(v2[0]+v2[1]+1<=lim&&max({a,b+1,e+1})==max({a,b,c+1,e+1}))
	{
		dp[now]=max({a,b+1,e+1});
		id[now]=0;
	}
	else
	{
		dp[now]=max({a,c+1,e+1});
		id[now]=1;
	}
}
int main()
{
	n=read();
	for(int i=1,u,v;i<n;i++)
	{
		u=read();v=read();
		add(u,v);add(v,u);
	}
	int l=1,r=n;
	while(l<=r)
	{
		lim=(l+r)>>1;
		fail=0;
		dfs(1,0);
		if(fail)l=lim+1;
		else r=lim-1;
	}
	cout<<r+1<<"\n";
	return 0;
}
```

---

## 作者：K8He (赞：8)

# [「题解报告」[ABC293Ex] Optimal Path Decomposition ](https://www.luogu.com.cn/problem/AT_abc293_h)

这个题一看就挺二分答案的。

设 $f_{i, j}$ 表示以 $i$ 为根的子树中，$i$ 有不超过 $j$ 个儿子与自己颜色相同时，从 $i$ 出发的一条路径上的**与自己颜色不同的**颜色数量最大值。显然 $0\le j\le2$。（直接表示颜色数量最大值，不排除自己应该也行，但转移好像不太方便。）

然后二分查找 $k$，每次用 $O(n)$ 的时间算一下 $f$ 数组，总复杂度 $O(n\log_2n)$。

如何转移？设当前枚举到了 $u$ 的叶子结点 $v$，那么当且仅当 $f_{u,j_1} + f_{v, j_2} + [j_2 = 2] \le k$ 时可以转移。如果 $f_{v, j_2}$ 完全没机会转移上去说明这棵子树已经不满足条件了，直接令 $f_{u,0} = f_{u,1} = f_{u,2} = +\infty$，转移到根上后即可毙掉这种情况。

确实有点抽象，但是代码很短很好写。

Code:

```cpp
const ll N = 2e5 + 10, inf = 1ll << 40;
namespace SOLVE {
	ll n, f[N][3], ans;
	std::vector<ll> tu[N];
	inline ll rnt () {
		ll x = 0, w = 1; char c = getchar ();
		while (!isdigit (c)) { if (c == '-') w = -1; c = getchar (); }
		while (isdigit (c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar ();
		return x * w;
	}
	inline void Dfs (ll u, ll fa, ll k) {
		f[u][0] = f[u][1] = f[u][2] = 0;
		far (v, tu[u]) {
			if (v == fa) continue;
			Dfs (v, u, k);
			ll g[3] = {inf, inf, inf};
			if (f[u][0] + f[v][1]     < k) g[1] = std::min (g[1], std::max (f[u][0], f[v][1]));
			if (f[u][1] + f[v][1]     < k) g[2] = std::min (g[2], std::max (f[u][1], f[v][1]));
			if (f[u][0] + f[v][2] + 1 < k) g[0] = std::min (g[0], std::max (f[u][0], f[v][2] + 1));
			if (f[u][1] + f[v][2] + 1 < k) g[1] = std::min (g[1], std::max (f[u][1], f[v][2] + 1));
			if (f[u][2] + f[v][2] + 1 < k) g[2] = std::min (g[2], std::max (f[u][2], f[v][2] + 1));
			f[u][0] = g[0], f[u][1] = std::min(f[u][0], g[1]), f[u][2] = std::min(f[u][1], g[2]);
		}
		return;
	}
	inline void In () {
		ans = n = rnt ();
		_for (i, 1, n - 1) {
			ll u = rnt (), v = rnt ();
			tu[u].push_back (v), tu[v].push_back (u);
		}
		return;
	}
	inline void Solve () {
		ll l = 1, r = n;
		while (l <= r) {
			bdmd;
			Dfs (1, 0, mid);
			if (f[1][2] < inf) ans = mid, r = mid - 1;
			else l = mid + 1;
		}
		return;
	}
	inline void Out () {
		printf ("%lld\n", ans);
		return;
	}
}
```

---

## 作者：Umbrella_Leaf (赞：6)

### 题意简述

洛谷之前的翻译好像有点问题。

> 给定一个 $n$ 个点的树，你可以将树划分为若干条不交的路径，每条路径染一种颜色。

> 找到最小的 $K$ 满足：对于任意一条原树上的路径，其经过的颜色数不超过 $K$。

### 思路分析

答案的单调性显然，考虑二分答案。二分之后要 `check` 一个答案是否合法。

树形 DP。设 $dp_{i,j}$ 表示只考虑以 $i$ 为根的子树，其中 $i$ 有 $j$ 个和它颜色相同的儿子。由于每种颜色都是一条路径，所以 $j$ 不会超过 $2$。

转移时依次加入 $x$ 的所有儿子，具体的转移方程较复杂可以参考代码。

### 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
vector<int> edge[200005];
int lim;
int dp[200005][3];
void dfs(int x,int f){
	dp[x][0]=dp[x][1]=dp[x][2]=0;
	for(int y:edge[x])if(y!=f){
		dfs(y,x);
		int nxt[3]={0x3f3f3f3f,0x3f3f3f3f,0x3f3f3f3f};
		if(dp[x][0]+dp[y][1]<=lim)nxt[1]=min(nxt[1],max(dp[x][0],dp[y][1]));
		if(dp[x][0]+dp[y][2]+1<=lim)nxt[0]=min(nxt[0],max(dp[x][0],dp[y][2]+1));
		if(dp[x][1]+dp[y][1]<=lim)nxt[2]=min(nxt[2],max(dp[x][1],dp[y][1]));
		if(dp[x][1]+dp[y][2]+1<=lim)nxt[1]=min(nxt[1],max(dp[x][1],dp[y][2]+1));
		if(dp[x][2]+dp[y][2]+1<=lim)nxt[2]=min(nxt[2],max(dp[x][2],dp[y][2]+1));
		dp[x][0]=nxt[0],dp[x][1]=nxt[1],dp[x][2]=nxt[2];
		dp[x][1]=min(dp[x][1],dp[x][0]);
		dp[x][2]=min(dp[x][2],dp[x][1]);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int x,y;scanf("%d%d",&x,&y);
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	int l=0,r=n-1;
	while(l<r){
		lim=l+r>>1;
		dfs(1,0);
		if(dp[1][2]<=lim)r=lim;
		else l=lim+1;
	}
	printf("%d\n",l+1);
	return 0;
}
```

---

## 作者：yszs (赞：5)

很神仙的一道 $DP$。

首先染成一种颜色的点集是一条链，~~根据套路~~发现一个点和它颜色相同的点的子树个数只能是 $\text{0,1,2}$。

那考虑设树形 $\text{dp[i][0/1/2]}$ 表示以i为根，根节点的颜色与 $0,1,2$ 个子树相同后从 $i$ 点向下延伸的路径颜色种类中的最大值的最小值，$\text{f[i][0/1/2]}$ 则是经过 $i$ 点的路径颜色种类中的最大值的最小值。

$\text{dp}$ 转移就是考虑要不要把这个点染成和自己一样的颜色。

不染就是取 $max$。

染就是少一费后取 $max$，且两个状态不能有一个是 $2$。 

~~转移很像林克卡特树~~。

$\text{f}$ 的转移就是选两个值最大的子树加起来。

发现有问题，没有办法统计答案。

感性理解就是答案显然是每个点的 $\texttt{f}$ 值取最大值，但是你这个状态只能保证一个点的值是最小值，但是不能保证别的点的值最小。

那我们换一种思路考虑，一个点的决策只有三种情况：

1. 这个点的颜色和子树根的颜色都不同

2. 这个点的颜色和一个子树根的颜色相同

3. 这个点的颜色和两个子树根的颜色相同

除了叶子情况 $1$ 显然劣于情况 $2$，所以不考虑情况 $1$。

对于有情况 $3 $ 的发现情况 $2$ 很团队，有可能帮父亲减一费，但是情况 $3$ 很贪对当前的决策是比情况 $2$ 更优的。

所以我们就二分一个答案的上界，这样决策其实就确定了，能团队就团队，不能团队就贪，贪不行就寄。

形式化来说，令 $X$ 表示儿子的决策是 $2$ 的答案降序集合，$Y$ 是儿子决策是 $3$ 的答案降序集合。

当前点情况 $2$ 的 $\text{dp}$ 值就是 $\text{max}\{X_0,X_1+1,Y_0+1\}$，情况 $3$ 的 $\text{dp}$ 值就是 $\text{max}\{X_0,X_1,X_2+1,Y_0+1 \}$。

令 $C$ 表示降序集合 $\{X_0-1,X_1,...X_x,Y_0,...,Y_y\}$，令 $D$ 表示降序集合 $\{X_0-1,X_1-1,X_2,...X_x,Y_0,...,Y_y\}$。

那么情况 $2$ 的 $\text{f}$ 就是 $C_0+C_1+1$。情况 $3$ 的 $\text{f}$ 就是 $D_0+D_1+1$。

然后考虑什么时候选择情况 $2$，什么时候选择情况 $3$，什么情况寄。

令二分的上界称为 $k$。

如果 $D_0+D_1+1 > k$ 那么寄。 

如果 $C_0+C_1+1 > k$ 那么选 $3$。

如果 $\text{max}\{X_0,X_1+1,Y_0+1\} > \{X_0-1,X_1-1,X_2,...X_x,Y_0,...,Y_y\}$ 选 $3$，因为减完费了都不如贪，而且父亲的减费名额有限，所以不如不减。

其他都选 $2$。

因为只需要维护常数个值，所以不需要 $sort$。

套上二分复杂度 $O(nlogn)$。

代码写的两个 $log$ 暴力排序做法

[code](https://atcoder.jp/contests/abc293/submissions/39721857)

---

## 作者：Miraik (赞：3)

起手先二分一个 $K$，把问题转换为判定。

考虑一个点 $u$ 的决策，发现它只会和其一或两个儿子的颜色相同。

那么你发现双儿子对 $u$ 子树内的路径更优，单儿子可能对 $fa_u$ 的决策更优。特别的，叶子视为单儿子决策（因为它可以继续向上传递）。

这时我们二分 $K$ 的用处就体现出来了：如果可以选单儿子且对 $fa_u$ 的决策更优的话我们就选单儿子，否则能选双儿子就双儿子，否则判定失败。

设 $f_i$ 表示最优决策下 $i$ 的子树内，从 $i$ 开始的链的最多颜色个数，
$g_i$ 表示最优决策下 $i$ 的子树内，一条链的最多颜色个数。

那么合法就等价于 $\forall i \in \{1,2,\cdots,n\},g_i\le K$。

然后进行转移。考虑 $u$ 的儿子中两种决策的 $f$ 形成的降序集合 $\{x_1,x_2,\cdots,x_X\}$，$\{y_1,y_2,\cdots,x_Y\}$，其中 $x$ 为单儿子决策集合，$y$ 为双儿子决策集合（注意这里的决策是对儿子而言的）。

定义 $s2\{S\}$ 表示集合 $S$ 中前两大的数之和。

那么如果 $u$ 选择双儿子，就有：

$f_u'=\max\{x_1,x_2,x_3+1,\cdots,x_X+1,y_1+1,y_2+1,\cdots,y_Y+1\}$

$g_u'=s2\{x_1,x_2,x_3+1,\cdots,x_X+1,y_1+1,y_2+1,\cdots,y_Y+1\}$

如果选择单儿子，则有：

$f_u''=\max\{x_1,x_2+1,x_3+1,\cdots,x_X+1,y_1+1,y_2+1,\cdots,y_Y+1\}$

$g_u''=s2\{x_1,x_2+1,x_3+1,\cdots,x_X+1,y_1+1,y_2+1,\cdots,y_Y+1\}$

那么：

若 $g_u'>K$ 直接判定失败。

若 $g_u'\le K,g_u''>K$ 选择双儿子，因为不得不选。

若 $f_u''=f_u'+1$ 选择双儿子，这是一定不劣的（$f_u'$ 传给父亲可能可以减 $1$ 费贡献，但是依然不会比选择 $f_u''$ 更优）。

否则选择单儿子。

注意到上述的转移中 $x$ 只需要用到前四大值，$y$ 只需要用到前两大值，于是一轮 dp 判定的复杂度就是 $O(n)$ 的了。

加上外面的二分，时间复杂度 $O(n \log n)$。

实际上依据形如重剖的分析可以得出 $K$ 是 $O(\log n)$ 级的，因此甚至可以做到 $O(n \log \log n)$。

```cpp
struct Dp{ int op,val; }f[N];
inline bool dfs(int u,int fa){
	if(deg[u]==1 && fa!=-1){
		f[u]={1,1};
		return 1;
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa) continue;
		if(!dfs(v,u)) return 0;
	}
	pn=qn=cn=dn=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa) continue;
		if(f[v].op){
			int j=1;
			while(j<=pn&&p[j]>=f[v].val) j++;
			if(j>4) continue;
			if(pn<4) pn++;
			for(int k=pn;k>j;k--) p[k]=p[k-1];
			p[j]=f[v].val;
		}
		else{
			int j=1;
			while(j<=qn&&q[j]>=f[v].val) j++;
			if(j>2) continue;
			if(qn<2) qn++;
			for(int k=qn;k>j;k--) q[k]=q[k-1];
			q[j]=f[v].val;
		}
	}
	p[++pn]=0; q[++qn]=0;
	if(pn){
		for(int i=1;i<=pn;i++)
			c[++cn]=p[i]+(i>1),d[++dn]=p[i]+(i>2);
	}
	if(qn){
		for(int i=1;i<=qn;i++)
			c[++cn]=d[++dn]=q[i]+1;
	}
	sort(c+1,c+cn+1,greater<int>());
	sort(d+1,d+dn+1,greater<int>());
	if(d[1]+d[2]-1>K) return 0;
	if(c[1]+c[2]-1>K||c[1]>d[1]){
		f[u]={0,d[1]};
		return 1;
	}
	f[u]={1,c[1]};
	return 1;
}
```


---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_abc293_h)

**题目大意**

> 把 $n$ 个点的树进行树链剖分，每个链染一个颜色，最小化路径颜色数的最大值。
>
> 数据范围：$n\le 2\times 10^5$。

**思路分析**

根据重链剖分的结论，答案不可能超过 $2\log_2n$，然后可以二分答案 $k$。

check 的时候设 $f_{u,0/1/2}$ 表示当前和 $u$ 颜色相同的儿子有至多$0/1/2$ 个，此时合法情况中最小的最大深度（深度指到 $u$ 路径颜色数）。

对于一条边 $u,v$：

- $f_{u,i}+f_{v,2}\le k$ 时 $f_{u,i}\gets \max(f_{u,i},f_{v,2}+1)$ 表示选不同颜色。
- $f_{u,i}+f_{v,1}-1\le k$ 时 $f_{u,i+1}\gets \max(f_{u,i},f_{v,1})$ 表示选同颜色。

直接转移即可。

时间复杂度 $\mathcal O(n\log\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5,inf=1e9;
int n,f[MAXN][3];
vector <int> G[MAXN];
void dfs(int u,int fz,int k) {
	f[u][0]=f[u][1]=f[u][2]=1;
	for(int v:G[u]) if(v^fz) {
		dfs(v,u,k);
		array<int,3> g{inf,inf,inf};
		for(int i:{0,1,2}) {
			if(i<2&&f[u][i]+f[v][1]-1<=k) g[i+1]=min(g[i+1],max(f[u][i],f[v][1]));
			if(f[u][i]+f[v][2]<=k) g[i]=min(g[i],max(f[u][i],f[v][2]+1));
		}
		f[u][0]=g[0],f[u][1]=min(g[0],g[1]),f[u][2]=min({g[0],g[1],g[2]});
	}
}
signed main() {
	scanf("%d",&n);
	for(int i=1,u,v;i<n;++i) scanf("%d%d",&u,&v),G[u].push_back(v),G[v].push_back(u);
	int l=1,r=40,res=40;
	while(l<=r) {
		int mid=(l+r)>>1;
		dfs(1,0,mid);
		if(f[1][2]<=mid) res=mid,r=mid-1;
		else l=mid+1; 
	}
	printf("%d\n",res);
	return 0;
}
```

---

## 作者：dengchengyu (赞：0)

## [AT_abc293_h [ABC293Ex] Optimal Path Decomposition](https://www.luogu.com.cn/problem/AT_abc293_h)

考虑二分答案，然后就变成了判断可行性。

设 $f_{i,0/1/2}$ 表示点 $i$ 已经与其 $0/1/2$ 个儿子颜色相同时，要使子树合法的，从 $i$ 出发的最小路径颜色数。

那么转移枚举儿子，然后看是否与儿子颜色相同，对于儿子 $v$，只有 $f_{v,0/1}$ 能参与转移。

那么有转移：

* 选为不同颜色，当 $f_{x,i}+f_{v,j}\le K$ 时，$f'_{x,i}\gets\max(f_{x,i},f_{v,j}+1)$。
* 选为相同颜色，当 $f_{x,i}+f_{v,j}-1\le K$ 时，$f'_{x,i+1}\gets \max(f_{x,i},f_{v,j})$。

最后判断根节点是否合法即可。

复杂度 $O(n\log n)$。

---

## 作者：jucason_xu (赞：0)

首先，考虑小规模的做法。

对于一个位置，如果它的颜色可以继续向上延申，我们称之为打开的，否则就是闭合的。容易发现唯一的闭合的可能是当前的节点颜色和某两个儿子都相同。

那么 $f_{i,j}$ 表示当前子树 $i$ 闭合，从 $i$ 向下走最多遇到 $j$ 种颜色，子树中颜色最多的路径最少有多少种颜色。$g_{i,j}$ 表示当前子树 $i$ 打开，从 $i$ 向下走最多遇到 $j$ 种颜色，子树中颜色最多的路径最少有多少种颜色。

我们考虑 $j$ 和 $f_{i,j}$ 是否具有单调性，但是很明显是没有的。那么我们就必须考虑优化掉一维。我们发现，如果我们只是验证某个 $k$ 是否可行，就只需要记录当前下方已经不能再拓展的的路径颜色个数是否小于等于 $k$ 就可以了。而这个状态和 $j$ 是有单调性的。而且对于大于 $k$ 的答案就可以直接忽略为不可能。

所以我们考虑二分答案 $k$，每次验证 $k$ 是否可行。这样我们就可以把状态优化到一维。

+ $f_i$ 表示闭合或者打开的最小深入颜色。

+ $g_i$ 表示打开的最小深入颜色。

为什么 $f_i$ 是“打开或闭合”呢？是为了有性质 $f_i\le g_i$。

对于没有儿子的点，直接建立新颜色，打开。

对于一个儿子的点，枚举是“儿子闭合，建立新颜色”还是“儿子打开，开创新颜色”。

对于两个及以上儿子的点，我们有三种选择：

1. 把当前节点涂成和所有儿子都不一样的颜色。打开。

2. 把当前节点涂成和某一个儿子一样的颜色。

3. 把当前节点作为连接点，连接某两个儿子为同一种颜色。

对于情况 $1$：

令所有儿子中 $f$ 的最大值为 $\max_1 f$，次大值为 $\max_2 f$。

在满足 $\max_1 f+\max_2 f+1\le k$ 的条件下，有转移 $g_i=\max_1 f +1$。

对于情况 $2$：

我们枚举当前颜色和哪一个儿子一样，设它是 $a$。然后令 $a$ 以外的儿子中，$f$ 的最大值为 $\max_1 f$，次大值为 $\max_2 f$，若只有两个儿子则为 $0$。

在 $\max_1 f+\max_2 f+1\le k$ 并且 $g_a+\max f\le k$ 的条件下，有转移 $g_i=\max(\max_1 f+1,g_a)$。

我们可以处理出所有的儿子，按照 $f_i$ 排序。枚举 $a$，取前 $3$ 个，如果有 $a$ 就排除掉，保证至少能选到两个。得到 $\max_1 f$ 和 $\max_2 f$。

对于情况 $3$：

先考虑暴力转移，尝试枚举当前节点和哪两个儿子一样，设为 $a,b(g_a\ge g_b)$。$a$ 和 $b$ 以外的儿子中，$f$ 的最大值为 $\max_1 f$，次大值为 $\max_2 f$，若不足则为 $0$。

则在 $\max_1 f+\max_2 f+1\le k$，$g_a+g_b-1\le k$，$\max_1 f+g_a\le k$ 三个条件都满足的情况下，有转移 $f_i=\max\{\max_1 f,g_a)\}$。

我们发现，所有的转移条件中，用到 $g_b$ 的只有一个，就是 $g_a+g_b-1\le k$，就可以贪心的选取 $g_b$ 最小的位置作为 $b$。

则先用前面的手段 $O(1)$ 处理出 $a$ 以外 $f$ 的前三大，然后：

1. 如果 $b$ 是 $\max_1 f$，则转移中的 $\max_1 f$ 和 $\max_2 f$ 对应处理出的 $\max_2 f$ 和 $\max_3 f$，直接转移。

1. 如果 $b$ 是 $\max_2 f$，则转移中的 $\max_1 f$ 和 $\max_2 f$ 对应处理出的 $\max_1 f$ 和 $\max_3 f$，直接转移。

1. 如果 $b$ 是 $\max_3 f$ 以及其他的数，转移中的 $\max_1 f$ 和 $\max_2 f$ 就是处理出的 $\max_1 f$ 和 $\max_2 f$。然后我们发现这个转移根本不需要考虑，因为前面的“和某一个儿子相同向上打开”的转移是严格覆盖了这个转移的。转移条件更宽，可以同时转移到 $f_i$ 和 $g_i$，所以根本不需要考虑。

最后还有 $f_i=\min(f_i,g_i)$。

然后就可以解决这道题。

```cpp
#define int long long
int n,a,b,f[200005],g[200005];
vt<int>vv[200005];int res=0,k=0;
inline void dfs(int x,int p){
	f[x]=1e9,g[x]=1e9;vt<pii>vp;
	for(auto j:vv[x])if(j!=p)dfs(j,x);
	for(auto j:vv[x])if(j!=p)vp.pb({f[j],j});
	if(vp.size()==0)return(void)(g[x]=f[x]=1);
	if(vp.size()==1)return(void)(g[x]=min(g[vp[0].second],f[vp[0].second]+1),f[x]=g[x]);
	sort(vp.begin(),vp.end(),[](pii a,pii b){
		return a.first>b.first;
	});
	if(vp[0].first+vp[1].first+1<=k)g[x]=min(g[x],vp[0].first+1);
	for(auto a:vv[x])if(a!=p){
		vt<pii>vs;
		for(int j=0;j<min(3ll,(int)vp.size());j++)if(vp[j].second!=a)vs.pb(vp[j]);
		if(((int)vs.size()<2||vs[0].first+vs[1].first+1<=k)&&g[a]+vs[0].first<=k){
			g[x]=min(g[x],max(vs[0].first+1,g[a]));
		}
	}
	for(auto a:vv[x])if(a!=p){
		vt<pii>vs;
		for(int j=0;j<min(4ll,(int)vp.size());j++)if(vp[j].second!=a)vs.pb(vp[j]);
		if(g[vs[0].second]<=g[a]){
			if((int)vs.size()<3||vs[1].first+vs[2].first+1<=k){
				if((int)vs.size()<2||vs[1].first+g[a]<=k){
					if(g[vs[0].second]+g[a]-1<=k){
						f[x]=min(f[x],max(vs[1].first+1,g[a]));
					}
				}
			}
		}
		if((int)vs.size()>1&&g[vs[1].second]<=g[a]){
			if((int)vs.size()<3||vs[0].first+vs[2].first+1<=k){
				if(vs[0].first+g[a]<=k){
					if(g[vs[1].second]+g[a]-1<=k){
						f[x]=min(f[x],max(vs[0].first+1,g[a]));
					}
				}
			}
		}
	}
	f[x]=min(f[x],g[x]);
}
inline bool valid(int x){
	k=x;
	dfs(1,0);
	return (f[1]<=k);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	rp(i,n-1){
		cin>>a>>b;
		vv[a].pb(b);
		vv[b].pb(a);
	}
	int l=1,r=n,mid,ans=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(valid(mid))r=mid-1,ans=mid;
		else l=mid+1;
	}cout<<ans<<endl;
	return 0;
}
//Crayan_r
```


---

