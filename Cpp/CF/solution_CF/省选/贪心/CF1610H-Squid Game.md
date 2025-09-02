# Squid Game

## 题目描述

After watching the new over-rated series Squid Game, Mashtali and Soroush decided to hold their own Squid Games! Soroush agreed to be the host and will provide money for the winner's prize, and Mashtali became the Front Man!

 $ m $ players registered to play in the games to win the great prize, but when Mashtali found out how huge the winner's prize is going to be, he decided to kill eliminate all the players so he could take the money for himself!

Here is how evil Mashtali is going to eliminate players:

There is an unrooted tree with $ n $ vertices. Every player has $ 2 $ special vertices $ x_i $ and $ y_i $ .

In one operation, Mashtali can choose any vertex $ v $ of the tree. Then, for each remaining player $ i $ he finds a vertex $ w $ on the simple path from $ x_i $ to $ y_i $ , which is the closest to $ v $ . If $ w\ne x_i $ and $ w\ne y_i $ , player $ i $ will be eliminated.

Now Mashtali wondered: "What is the minimum number of operations I should perform so that I can remove every player from the game and take the money for myself?"

Since he was only thinking about the money, he couldn't solve the problem by himself and asked for your help!

## 说明/提示

Explanation for the first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1610H/2f92b74ef3689103fc27552fedd0869997b9492b.png)In the first operation, Mashtali can choose vertex $ 1 $ and eliminate players with colors red and blue. In the second operation, he can choose vertex $ 6 $ and eliminate the player with orange color.In the second sample, Mashtali can't eliminate the first player.

## 样例 #1

### 输入

```
6 3
1 1 1 4 4
1 5
3 4
2 6```

### 输出

```
2```

## 样例 #2

### 输入

```
5 3
1 1 3 3
1 2
1 4
1 5```

### 输出

```
-1```

# 题解

## 作者：tzc_wk (赞：23)

看出来是个贪心。但是想错贪心方法了导致很快就把自己做法叉了。

以 $1$ 为根。显然如果存在路径上面只有两个点，那么答案就是 $-1$。否则，注意到一个性质，如果我们选了 $1$，那么所有非祖先-后代链就都会消失。因此我们先考虑处理只有祖先-后代链的情况，那么剩余的非祖先-后代链可以用 $\le 1$ 次操作搞掉。考虑如何处理祖先-后代链，假设 $dep_u<dep_v$，记 $w$ 为 $u\to v$ 路径上第一个点，那么我们只要操作 $w$ 子树内 $-$ $v$ 子树内任何一个点就可以搞掉这条路径。那么如何贪心呢？我们考虑找到当前时刻没有被覆盖的路径中 $w$ 深度最大的那一个，显然对于这样的路径，覆盖 $w$ 是最优的，选择了 $w$，就会进一步覆盖掉更多的路径，以此类推。使用 BIT 维护这个贪心即可。这样我们就解决了只有祖先-后代链的情况。

接下来考虑有非祖先-后代链的情况。有一个结论：此时如果所有非祖先-后代链都被覆盖，那么此时选的点的个数就是答案，否则直接令答案加一即可。我们考虑将所有祖先-后代链按 $w$ 的深度从小到大排序，那么我们选择的 $w$ 一定是字典序最小的组，即，如果在这个条件下，还存在一个非祖先-后代链，满足我们选择的点都在这个非祖先-后代链的端点的子树内，那么我们也无法通过将某些点调整为深度更小的点使其覆盖这个祖先-后代链。因此这个结论是正确的。

时间复杂度 $n\log n$。

---

## 作者：chlchl (赞：11)

嗯，好题，妙题。

题解区中唯一一篇 dp 的题解讲的不太清楚，并没有说明 dp 怎么来的，这里做一个比较详细的补充。

# Solution
这题是我们模拟赛中的一道题，它的数据分配如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/epqxrngx.png?x-oss-process=image/resize,m_lfit,h_600,w_700)

这个数据起到了很好的引导作用，我们先从其中两档部分分说起。

**本文默认以 $1$ 为根。**

## Subtask 1：数据点 11-12：$fa_i=1$
显然这是个菊花图。

这很显然，除了 $(1,u)$ 的形式，其它都是 $u\rightarrow 1\rightarrow v$ 的路径形式。

结论（1）：如果没有 $(1,u)$，我们选 $1$ 就好了，它到 $u,v$ 的路径最近点肯定是 $1$。


结论（2）：如果有形如 $(1,u)$ 的，直接就无解，自己画画图就行。

## Subtask 2：数据点 13-15：$fa_i=i-1$
这档部分分是个链。

显然一条路径 $u\rightarrow v$ 对应了连续的一段 $dfn$ 序区间，而这条路径上除了 $u,v$ 两点，其它点都可以选。

问题转化为一个经典的贪心问题：$m$ 个区间，选若干个点，要求每个区间至少包含一个点，问最少选多少个点。

结论（3）：对于上面的问题，将区间按右端点排序，每次若当前区间无点，则选右端点，否则跳过。

这个结论到处都有证明，故省略。

## 正解
假设点对 $(u,v)$ 总是满足 $dep_u<dep_v$。

首先判断无解。

结论（2）引导我们，将菊花图放大，其实你会发现，如果出现了 $u,v$ 之间只隔了一条边，那么肯定是无解的（这个显然）。

然后考虑先从 Subtask 1 下手。

Subtask 1 中，所有的路径都是有折点的，深度并不递增（我们称为**曲链**，深度递增的成为**直链**）。而 结论（1）为直接选择根节点即可满足菊花图。

事实上，稍微推敲可以发现，直接选择根节点，可以满足所有曲链的情况。因为 $u,v$ 两点若同时在一条直链上，那它们必然是直链，不满足条件；而如果不在一条直链上，那么 $u,v$ 之间必然存在一个点 $p$，可以满足 $u\rightarrow p\rightarrow 1$ 和 $v\rightarrow p\rightarrow 1$ 都是直链。

![](https://cdn.luogu.com.cn/upload/image_hosting/sc9huoe5.png?x-oss-process=image/resize,m_lfit,h_600,w_700)

这个 $p$ 就是根节点到 $u\rightarrow v$ 这条路径的最近点，并且显然它不会等于 $u$ 或 $v$。

也就是说，对于所有曲链，直接选一个根节点即可。

所以我们只需要搞定直链的选点情况即可。

------------
下面讨论直链。

考虑到 Subtask 2 全都是直链，所以我们考虑借助结论（3），用贪心解决问题。

实际上，如果我们将 Subtask 2 中区间的右端点设为深度最小的那个点，那么我们就会发现，其实每次选点，都是选 $u$ 下面的那个点（也就是能选的点中深度最小的那个）。

更具体地，如果有一条直链需要被选，我们一定选的是这条直链上除 $u$ 之外深度最小的点，就是下面的黄点（下文统一以“黄点”称这一类点）。

但问题是，如果有两条直链相互拼接并且分叉开，这时选的方式就有选择了。

![](https://cdn.luogu.com.cn/upload/image_hosting/0z27jf4a.png?x-oss-process=image/resize,m_lfit,h_600,w_700)

画个图可以发现，我们选的一定是深度较大的那条直链（蓝色直链）的黄点。

这个时候直接贪心不太可行，但是它提供给我们一个非常好的思路。

尝试用杀伤力更大的方法——dp 解决问题。

设 $dp_u$ 为当（所有满足黄点在 $u$ 子树内的直链）都能被选时，选择的最小点数。

看 $dp_u$ 怎么更新。

既然我们设计的状态与黄点有关，那我们就找当 $u$ 作为黄点时的情况。

当 $u$ 作为路径 $x\rightarrow y$（还是默认 $dep_x<dep_y$）的黄点时， $dp_u=\max\{dp_y\}+1$。

$u$ 的子树内，除了选 $dp_y$ 中应该选的点，$u$ 自己作为黄点时，其本身也应该被选，并且也只需要选 $u$，就能解决所有以 $u$ 为黄点的路径。

但是，如果 $u$ 不作为任何一条路径的黄点，上面的式子就会更新个寂寞。

所以我们还有一个累加式 $dp_u=\sum\limits_{v\in son_u}dp_v$。

求出来这个式子之后，我们需要加上曲链，统计答案。

一眼看上去像是 $f_1+1$，即根节点处理完所有直链之后，再把自己选上，搞定曲链。

问题是，我们不知道当前已选的点是否能覆盖所有曲链。

所以我们需要枚举所有曲链 $(u,v)$，看看会出现什么情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/g7xyk94s.png?x-oss-process=image/resize,m_lfit,h_600,w_700)

图中红色为直链。

1. 直链与其相交于 $u$ 或 $v$，此时 $dp_v$ 或 $dp_u$（与其相交的那个）选的点一定包含这个端点（子树包含其本身）。
2. 直链与其相交于路径上任意一点或多点。此时选的点是深度第二小的那个点。这个点到 $u\rightarrow v$ 的最近点一定是该直链与 $u,v$ 相交的点（一定不是 $u$ 或 $v$），且这个选点方案一定包含在 $dp_1$ 中。
3. 直链与其没有相交。显然其要么在 $u,v$ 子树内，要么就如上图“完全不相交”的那种情况一样。
- 在子树内，显然 $dp_u$ 或 $dp_v$ 已经包含这条链的选点情况。
- 不在子树内，无论如何 $dp_1$ 一定包含它。

尝试理解 $dp_u+dp_v+1$ 的意思，其实就是解决 $u,v$ 子树之后再选个根节点解决 $(u,v)$ 这条曲链。

令 $ans$ 初始为 $dp_1$。那么，如果 $dp_u+dp_v+1>ans$，那么其实说明 $u,v$ 能包含所有区间的选点，但是还需要加上一个根节点（因为 $dp_u,dp_v$ 根本覆盖不到 $(u,v)$ 这条曲链）来覆盖它。

其余情况一定是 $dp_1$ 一定不会小于 $dp_u+dp_v+1$，因为其它 $u,v$ 的子树中仍然有黄点，$dp_1$ 除了 $dp_u$ 和 $dp_v$ 之外还至少会加上这个黄点。

而这里有个很关键的点：**这个黄点已经覆盖了 $(u,v)$ 这条曲链！！！！！**

因为只要这条直链不在 $u$ 或 $v$ 子树内，它与 $(u,v)$ 的交点一定不会在 $u,v$，那么到曲链的最近点一定是那个相交的点而不是 $u,v$！

综上，我们枚举每条曲链 $(u,v)$，尝试用 $\max\{dp_u+dp_v+1\}$ 更新 $ans$ 即可。

容易发现 dp 的时间复杂度是线性的。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 10;
int n, m;
int id, head[N << 1], to[N << 1], nxt[N << 1];
int f[N][20], dep[N], dp[N];
struct node{
	int u, v;
};
vector<int> zhi[N]; 
vector<node> qu;

void add(int u, int v){
	to[++id] = v;
	nxt[id] = head[u], head[u] = id;
}

void dfs(int u, int fa){
	f[u][0] = fa;
	for(int i=1;i<20;i++)
		f[u][i] = f[f[u][i - 1]][i - 1];
	for(int i=head[u];i;i=nxt[i]){
		int v = to[i];
		if(v == fa)
			continue;
		dep[v] = dep[u] + 1;
		dfs(v, u);
	}
}

int LCA(int u, int v){
	if(dep[u] < dep[v])
		swap(u, v);
	for(int i=19;i>=0;i--)
		if(dep[f[u][i]] >= dep[v])
			u = f[u][i];
	if(u == v)
		return u;
	for(int i=19;i>=0;i--)
		if(f[u][i] != f[v][i])
			u = f[u][i], v = f[v][i];
	return f[u][0];
}

int find(int u, int v){
	if(dep[u] < dep[v])
		swap(u, v);
	for(int i=19;i>=0;i--)
		if(dep[f[u][i]] > dep[v])//找到直链中 v 下方的那个点，所以是深度 > v 
			u = f[u][i];
	return u;
}

int getdis(int u, int v){
	return dep[u] + dep[v] - 2 * dep[LCA(u, v)];
}

void DP(int u, int fa){
	for(int i=head[u];i;i=nxt[i]){
		int v = to[i];
		if(v == fa)
			continue;
		DP(v, u);
		dp[u] += dp[v];
	}
	for(int y: zhi[u])//对于以 u 作为黄点的（处于直链下方的）点，f[u] 有一个与它们的递推式 
		dp[u] = max(dp[u], dp[y] + 1);
}

int main(){
	scanf("%d%d", &n, &m);
	for(int u=2,v;u<=n;u++){
		scanf("%d", &v);
		add(u, v);
		add(v, u);
	}
	dfs(1, 1);
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d", &u, &v);
		if(getdis(u, v) == 1)
			return printf("-1\n"), 0;
		if(dep[u] < dep[v])
			swap(u, v);
		int l = LCA(u, v);
		if(l == v)//这是条直链 
			zhi[find(u, v)].push_back(u);//为 dp 做铺垫，注意传的是直链下方的点 
		else
			qu.push_back((node){u, v});
	}
	DP(1, 1);
	int ans = dp[1];
	for(auto now: qu)
		ans = max(ans, dp[now.u] + dp[now.v] + 1);
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：AbioAg (赞：5)

关于贪心做法的一些思路。

无解显然是两个点之间有父子关系，直接判了。

和其他题解一样的 key observation 是对于所有链分成直链和曲链来讨论。

如果只有曲链的情况，发现选根节点即可满足所有链的要求。

考虑只有直链的情况，我们如果先解决更特殊的情况，假设树是一条链，发现问题转化成了序列上的问题：

给定若干线段（这些线段就是链去掉两个端点，以下说的线段与链均默认去掉两个端点），选择若干点使得所有线段都包含至少一个点。

这是一个经典贪心问题，我们传统的做法是对于右端点排序，每次如果一个线段不包含点，就覆盖他的右端点，证明这里略去，网上已经有很多了。

回到树上，我们发现我们要解决的就是这个问题的 on tree 版本。

但是注意到树上的关系是：**一个点有多个儿子**。

所以我们类似于刚才那样从根向下贪显然是假的，因为我们贪的时候没有综合考虑让所有儿子链最优化。

这时候我们想到与此相对的：**一个点的父亲唯一**。

所以我们可以倒着做这样一个过程，考虑如果在原序列上，相当于按左端点排序，每次如果没包含点，就覆盖左端点，那么到树上也是类似的，我们按所有链最浅点排序，如果它没被覆盖，就放一个点在左端点上，不然跳过就好了，至此我们成功解决了只有直链的版本。

考虑加入曲链，我们发现曲链对于放置点的喜好都是越浅越好，我们的放点策略恰好符合了曲链的偏好，同样的策略对于加入曲链也没问题，不会产生更劣情况，因此可以直接检查已放点能否覆盖所有曲链，不能的话说明需要多放一个在根节点，把直链答案 +1 就好了。

---

## 作者：Delusions_grandeur (赞：4)

> 补充自 [@Famiglistmo](https://www.cnblogs.com/wyb-sen/p/15869847.html) 的题解。

首先发现一个贪心：对一条曲链来说，直接选最浅的节点也就是根节点最优，但选根节点一定不能处理到直链；对于一条直链，选它浅深度的端点的儿子最优，因为这样可以尽可能解决掉下面的曲链，我们姑且把这个点叫做要害点。但并不一定非要选要害点最优，因为当一条直链上挂了其他直链时，用这条直链的要害点就已经可以解决掉这条链了。

糟了，那这个贪心没法搞了，情况比较复杂。暴力分类讨论？发现到只有当处理完直链后还有曲链没处理才会选根节点，且答案至多增加 $1$。考虑先用 DP 解决直链选点。设 $dp_u$ 表示处理完所有**要害点**包含在 $u$ 子树中的直链需要选的最少点数，则显然有：$dp_u=\sum\limits_{v\in son_u} dp_v$，若直链 $(u,v)$ 的要害点为 $w$ ,则 : $dp_w=\max(dp_w,dp_v+1)$。这个 DP 式很特殊，值得好好推敲。

令 $ans=dp_1$ ，对每条曲链$(u,v)$有 $ans=\max(ans,dp_u+dp_v+1)$ 。容易发现当根节点未选且 $(u,v)$ 没被处理掉时，$dp_u+dp_v+1$ 会比 $ans$ 大 $1$ 。

贴个很丑的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int N=3e5;
int n,m,ans,head[N+5],to[N+5],nxt[N+5],ecnt=1;
int dep[N+5],f[N+5][25],dp[N+5];
vector<int> line[N+5];
vector<pii> arc;
void add(int u,int v) {to[++ecnt]=v;nxt[ecnt]=head[u];head[u]=ecnt;}
void pre(int u)
{
	for(int i=0; i<20; i++) f[u][i+1]=f[f[u][i]][i];
	for(int i=head[u],v; v=to[i],i; i=nxt[i]) dep[v]=dep[f[v][0]=u]+1,pre(v);
}
int jump(int u,int v)
{
	for(int i=20; ~i; i--) if(dep[f[u][i]]>dep[v]) u=f[u][i];
	return u;
}
void dfs(int u)
{
	for(int i=head[u],v; v=to[i],i; i=nxt[i]) dfs(v),dp[u]+=dp[v];
	for(int v: line[u]) dp[u]=max(dp[u],dp[v]+1);
}
int main()
{
	scanf("%d%d",&n,&m);for(int i=2,x; i<=n; i++) scanf("%d",&x),add(x,i);pre(1);
	for(int i=1,u,v; i<=m; i++)
	{
		scanf("%d%d",&u,&v);
		if(dep[u]<dep[v]) swap(u,v);
		int w=jump(u,v);
		if(f[w][0]==v)
			if(u==w) return puts("-1"),0;
			else line[w].emplace_back(u);
		else arc.emplace_back(pii(u,v));
	}
	dfs(1),ans=dp[1];for(auto v: arc) ans=max(ans,dp[v.first]+dp[v.second]+1);
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：5k_sync_closer (赞：3)

考虑链怎么做。问题变为给一些区间 $[l_i,r_i]$，选最少的点使得每个 $(l_i,r_i)$ 内都有至少一个点，

这个是贪心经典题，按右端点排序即可，考虑在树上类似地贪心。

钦定 $1$ 为根。可以发现选 $1$ 可以解决所有曲链，不妨先考虑只有直链的情况。

设 $d_u$ 表示 $u$ 的深度。对直链 $u\to v$（钦定 $d_u<d_v$），设 $w$ 为 $v$ 的 $d_v-d_u-1$ 级祖先，

则其要求 $\text{subtree}(w)-\text{subtree}(v)$ 内至少有一个点。

把所有直链按 $d_w$ 从大到小排序，每次若一条链还没有满足要求，选择它的 $w$ 即可，这个贪心容易用数据结构维护。

考虑有曲链的情况。显然若此时所有曲链已经满足要求，答案不变。

否则，此时已选的所有点都无法上移，只能再选一个 $1$ 满足剩下的曲链。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
struct E
{
    int v, t;
} e[1000050];
struct S
{
    int u, v;
} a[1000050], z[1000050];
int n, m, k, r, c, o, q, b[1000050], d[1000050], s[1000050], h[1000050], f[1000050][20], C[1000050];
bool O(S a, S b) { return d[a.u] > d[b.u]; }
void M(int x, int k)
{
    for (; x <= n; x += x & -x)
        ++C[x];
}
int Q(int x, int y)
{
    int q = 0;
    for (--x; y > x; y &= y - 1)
        q += C[y];
    for (; x > y; x &= x - 1)
        q -= C[x];
    return q;
}
void A(int u, int v) { e[++c] = {v, h[u]}, h[u] = c; }
void D(int u, int k)
{
    s[u] = 1;
    b[u] = ++o;
    for (int i = h[u], v; i; i = e[i].t)
        if ((v = e[i].v) != k)
        {
            d[v] = d[f[v][0] = u] + 1;
            for (int j = 1; f[v][j - 1]; ++j)
                f[v][j] = f[f[v][j - 1]][j - 1];
            D(v, u);
            s[u] += s[v];
        }
}
int K(int u, int v)
{
    for (int i = 19; i >= 0; --i)
        if (d[f[v][i]] > d[u])
            v = f[v][i];
    return v;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 2, x; i <= n; ++i)
        scanf("%d", &x), A(x, i);
    D(1, 0);
    for (int i = 0, u, v; i < m; ++i)
    {
        scanf("%d%d", &u, &v);
        if (d[u] > d[v])
            swap(u, v);
        if (b[v] >= b[u] && b[v] < b[u] + s[u])
        {
            if (d[v] - d[u] <= 1)
            {
                puts("-1");
                return 0;
            }
            a[++k] = {u, v};
        }
        else
            z[++r] = {u, v};
    }
    sort(a + 1, a + k + 1, O);
    for (int i = 1, o; i <= k; ++i)
    {
        o = K(a[i].u, a[i].v);
        if (!Q(b[o], b[a[i].v] - 1) && !Q(b[a[i].v] + s[a[i].v], b[o] + s[o] - 1))
            M(b[o], 1), ++q;
    }
    for (int i = 1; i <= r; ++i)
    {
        if (b[z[i].u] > b[z[i].v])
            swap(z[i].u, z[i].v);
        if (!Q(1, b[z[i].u] - 1) && !Q(b[z[i].u] + s[z[i].u], b[z[i].v] - 1) && !Q(b[z[i].v] + s[z[i].v], n))
        {
            ++q;
            break;
        }
    }
    printf("%d", q);
    return 0;
}
```


---

## 作者：H_W_Y (赞：3)

> 给定㇐个 $n$ 个点的树，以及 $m$ 条链。

> 你需要选取尽可能少的点，使得对于每㇐条链 $(x_i , y_i)$，都存在㇐个被选的 $z$ 点，使得链上到 $z$ 距离最短的点既不是 $x_i$ 也不是 $y_i$。

> $n, m \le 3 \times 10^5$。

首先可以知道树上的链分成了两种：**直链** 和 **曲链**，也就是说对于一条链 $(u,v)$，如果其中一点是另一点的祖先，我们就把它叫做直链。

那么我们先来考虑一棵树是一条链的情况。

发现这个东西可以直接被转移到区间上面，那么每一条链就是这个样子：

![1](https://cdn.luogu.com.cn/upload/image_hosting/vvt3yqpd.png?x-oss-process=image)

于是对于一个当前枚举到的点 $i$，也就是图中红色的点，它被选当且仅当下一个点是一条链的端点并且这条链没有被选过（这里我们称红色的点为这条链的关键点）。

我们现在把问题放到树上面，容易发现对于曲链，只要有一个点在它的 $lca$ 上面就满足条件，那么我们最后再选一个根节点就一定满足条件，这样对答案的贡献只有 $1$，所以其实我们只需要考虑直链的情况。

和上面分析的方法类似，对于直链，我们也是尽可能让选的点深度更浅。

也就是说如果当前的节点 $u$ 不是一条链的关键点（它上面的点不是一条链的上端点），那么 $u$ 也是一定不会选的；而如果是，也不一定被选，因为有这样一种情况：

![2](https://cdn.luogu.com.cn/upload/image_hosting/te1rrh6x.png?x-oss-process=image)

其中黄色是我们已经选的点，而蓝色和红色分别是链。

再这种情况中对于节点 $u$ 而言，虽然它是蓝色链的关键点，但是我们也是不会选的，因为黄色点一定是可以满足条件的。

那么现在问题来了，到底什么时候才会去选 $u$ 呢？

分析一下我们可以发现，有一条以 $u$ 为关键点的链 $(x,y)$（$x$ 在 $y$ 上面），它满足在 $u$ 的子树中选的所有点都在 $y$ 的子树中时，我们才会选 $u$。因为这个时候已选的所有点到链距离最小的点都是 $y$，反之在 $y$ 子树外的一个选上的点是满足条件的。

于是现在我们考虑树形 dp，设 $dp_u$ 表示只考虑关键点在 $u$ 子树中的链，所需要选的点的最小值。

不考虑 $u$ 这个点的贡献，很轻松可以得到 $dp_u=\sum_{v \in son_u} dp_v$。

而算上 $u$ 的贡献就是：$dp_u = \max(dp_u,dp_y+1)$，其中 $y$ 和前面的 $y$ 意思一样。

这样为什么是对的？

很明显可以发现当 $dp_u$ 变大的时候当且仅当 $dp_y$ 与此时的 $dp_u$ 相等，也就是说所有选的点都在 $y$ 的子树中，这和我们上面分析的一致。

于是现在直链都解决了，剩下的就是曲链了。

发现这也是很好做的，如果有曲链不满足条件我们就直接选上 $1$ 号节点即可。

而判断是否要选的思路和上面是类似的，对于一条曲链 $(x,y)$，它需要再选上 $1$ 当前仅当所有选的点都在 $x$ 和 $y$ 的子树中，也就是 $dp_x+dp_y =dp_1$。

于是统计答案的时候我们先令 $ans=dp_1$，那么就变成了 $ans=\max(ans,dp_x+dp_y+1)$。

于是这道题就做完了，代码也是好写的。

```cpp

#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back

const int N=5e5+5;
int n,m,head[N],tot=0,dp[N],ans=0,f[N][22],dep[N];
vector<int> g[N];
vector<pii> p;
struct edge{int v,nxt;}e[N<<1];

void add(int u,int v){
  e[++tot]=(edge){v,head[u]};head[u]=tot;
  e[++tot]=(edge){u,head[v]};head[v]=tot;
}

void init(int u,int fa){
  f[u][0]=fa;dep[u]=dep[fa]+1;
  for(int i=1;f[f[u][i-1]][i-1];i++) f[u][i]=f[f[u][i-1]][i-1];
  for(int i=head[u];i;i=e[i].nxt){
  	int v=e[i].v;
  	if(v==fa) continue;
  	init(v,u);
  }
}

int lca(int u,int v){
  if(dep[u]<dep[v]) swap(u,v);
  for(int i=19;i>=0;i--)
  	if(dep[f[u][i]]>dep[v]) u=f[u][i];
  return (f[u][0]==v)?u:-1; 
}

void dfs(int u,int fa){
  dp[u]=0;
  for(int i=head[u];i;i=e[i].nxt){
  	int v=e[i].v;
  	if(v==fa) continue;
  	dfs(v,u);dp[u]+=dp[v];
  }
  for(auto i:g[u]) dp[u]=max(dp[u],dp[i]+1);
}

int main(){
  /*2023.12.13 H_W_Y CF1610H Squid Game 树形dp*/
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>n>>m;
  for(int i=2,x;i<=n;i++) cin>>x,add(i,x);
  init(1,0);
  for(int i=1,u,v;i<=m;i++){
  	cin>>u>>v;
  	int nw=lca(u,v);
  	if(nw==-1) p.pb({u,v});
  	else{
  	  if(abs(dep[u]-dep[v])==1) cout<<"-1",exit(0);
  	  g[nw].pb(dep[u]>dep[v]?u:v);
  	}
  }
  dfs(1,0);ans=dp[1];
  for(auto i:p) ans=max(ans,dp[i.fi]+dp[i.se]+1);
  cout<<ans<<'\n';
  return 0;
}

```

---

## 作者：hyzhutao (赞：3)

此题清新雅致，难度不知是否有紫，但品味足够。

此题解精确细致，含证明，不简短，不喜勿喷。

由于我是没有智力打 oi，现在只会一点点数学，所以先给一些记号，方便后面形式化的表述，建议速通一下。设 $T=(V,E)$ 为原题给的树，并令根为 $1$。下文中 $u, v$ 等都是 $T$ 节点。记 $T_v$ 为以 $v$ 为根节点的子树中所有点构成的集合。若 $u$ 是 $v$ 的父亲，记 $\mathrm{fa}(v)=u$。若 $u$ 是 $v$ 的祖先，记 $u \succ v$。连接 $u$ 和 $v$ 的路径 **内部** 的节点构成的集合记作 $p(u,v)$。若 $p(u,v) \neq \varnothing$，记 $p(u,v)$ 中最靠近 $u$ 的节点为 $(u\rightharpoonup v)$。另外，$\wedge$ 表示“且”。

下面分析问题。显然选出点的顺序不影响结果，一个点选两次也没有意义，因此就是求选出的点构成的集合 $S \subseteq V$ 的最小元素个数 $|S|_{\min} $。

$S$的约束条件主要由每对 $(x, y)$ 给出。形象地说，对于每对 $(x,y)$，$S$ 必须包含 $p(x,y)$ 及其所连枝杈中的点。形式化地，$\exists v\in S- \{x,y\}$ 使得 $x\not\in p(v,y)$ 且 $y\not\in p(v,x)$。显然，若 $\{x,y\}\in E$，则 $p(x,y)=\varnothing$，直接无解。下文将不再对此情形讨论。

虽然约束条件在无根树的视角下看似优美，但无根树不便于处理，因此我们从有根树的视角再来看一下这些约束。这里要分两种情形。

情形1. $x\succ y$。（$y\succ x$ 同理。）只要 $S\cap (T_z-T_y)\neq \varnothing$，其中 $z=x\rightharpoonup y$。

情形2. $x\not\succ y$ 且 $y\not\succ x$。此情形下，只要 $S \cap (V-(T_x\cup T_y)) \neq \varnothing$。这个可以写成和上面几乎完全统一的形式：$S \cap (T_1-(T_x\cup T_y))\neq\varnothing$。

于是不难想到，这题与子树和相关。令 $f_v=|S\cap T_v|$。则若 $x \succ y$，就有 $f_z-f_y\geq 1$；否则就有 $f_1-f_x-f_y\geq 1$ （注意到此情形下 $1\succ x, 1\succ y, T_x\cap T_y=\varnothing$）。此外还有一个限制，来自于每个节点只能选至多一次，即 $f_u-\sum_{v:\mathrm{fa}(v)=u}f_v\in\{0,1\}$。

根据这些约束条件，不难构建以下 dp /贪心算法。对于每个节点 $u$，先将子树中的节点处理完，然后令
$$f_u=\max\left(\sum_{v:\mathrm{fa}(v)=u}f_v,\max_{z = u}(f_y+1)\right)$$

两点声明：其一，上式第二项仅考虑符合情形1的 $(x,y)$；其二，最后还要做一步

$$f_1\leftarrow \max\left(f_1,\max_{x\nsucc y \wedge y\nsucc x}(f_x+f_y+1)\right)$$

由于每个节点和每对 $(x,y)$ 均访问了 $\Theta(1)$，故算法总复杂度为 $\Theta(n+m)$。

至此，认真阅读的你已经可以 AC 了，但你不像我，是一个努力上进的 oier，因此还应当想想为何第三个限制自动满足。

首先，$f_{\mathrm{fa}(v)}\geq f_v$，于是对于 $u\succ v$，一定有 $f_u\geq f_v$。假设计算完毕后，$\exists u$ s.t. $f_u - 1 > \sum_{v:\mathrm{fa}(v)=u}f_v$，则要么
$$\max_{z=u}f_y > \sum_{v:\mathrm{fa}(v)=u}f_v$$
要么
$$u=1 \wedge \max_{x\nsucc y \wedge y\nsucc x}(f_x+f_y) > \sum_{v:\mathrm{fa}(v)=1}f_v$$
前者显然不可能，因为
$$u=z\succ y, \mathrm{fa}(u\rightharpoonup y)=u$$
$$\Rightarrow f_y \leq f_{u\rightharpoonup y}\leq \sum_{v:\mathrm{fa}(v)=u}f_v$$
实际上后者也不可能。设 $w=\mathrm{lca}(x,y)$，则 $(w\rightharpoonup x)\neq (w\rightharpoonup y)$，进而
$$f_x+f_y\leq f_{w\rightharpoonup x}+f_{w\rightharpoonup y}\leq \sum_{v:\mathrm{fa}(v)=w}f_v$$
由假设，$w\neq 1$，故而 $1\succ w$。于是
$$f_x+f_y\leq \sum_{v:\mathrm{fa}(v)=w}f_v \leq f_w \leq f_{1\rightharpoonup w} \leq \sum_{v:\mathrm{fa}(v)=1}f_v,$$
也矛盾。得证！

本人代码丑陋，不贴了。

**bb两句。** 所以我不确定这是贪心还是 dp。如果某位天才早早看透一切，那这就是 dp，子树为最优子结构；如果是像我这样的菜鸡，猜完结论再证，那就是贪心，每次取局部最优，最后恰好得到一个合法解。欢迎评论！

---

## 作者：CarroT1212 (赞：1)

近期做到最奇妙的题之一。

> 有一种也许可行的思路是，枚举其中一个被选的点，那么所有非祖先后代链都解决了，而祖先后代链部分明显和序列上的问题一样有一个贪心（即，从下往上遍历，过程中如果再往上走一步就有一条链不符合条件了就把当前这个点选上）。尝试换根维护这个贪心过程理论上就可以了。不过具体怎么实现这个换根我不太拿得准。

把 $1$ 作根，将链分成祖先后代链（直链）和非祖先后代链（曲链）两种。

如果只有直链就是直接做上面那个贪心。可以得出满足直链限制至少需要的点数 $dp_1$。

再把弯链带上。你发现，如果我们先只考虑直链做完贪心，再额外把根 $1$ 选上，所有弯链的限制也全部直接满足了，所以答案 $ans$ 一定满足，$dp_1\le ans \le dp_1+1$。

我们只需要判断 $ans$ 是否必须取到 $dp_1+1$ 即可。换句话说就是要知道，为了满足直链限制选的那些点，是不是一定没有办法同时把弯链的限制全都满足。

然后有一个策略上的事实：为了满足弯链的限制，把一个选的点在“合理”范围内尽量往根靠近，是不劣的。

诶，这不就是直链做法吗？

所以，直链部分的最优选点策略，正好对上了弯链部分的最优选点策略！不会出现任何，为了更优地满足直链限制，导致某些弯链限制从符合变得不符合的情况。

于是只要贪心做完直链之后，看一下有没有弯链不符合条件。如果有，那根就一定要选上，因为我们已经尽力了。

每个想到这里的人，脑子里一定已经有了一个千真万确的可以通过的写法。正常地写就可以了。

---

但题解区的实现把我震撼到了，说一下。

对于贪心部分，可以记 $dp_i$ 表示 $i$ 子树里选的最小点数。每次先做一个儿子累加，然后如果 $i$ 作为某条链 $(u,v)$ 的极限点，就让 $dp_i$ 和 $dp_v+1$ 取 $\max$。就可以了。

因为如果 $dp_i$ 里除了 $dp_v$ 之外的部分还有值，那么 $(u,v)$ 的限制就已经符合了。取 $\max$ 就只是在没有出现这种情况的时候确保把 $i$ 选上而已。

然后算上弯链的最终答案其实就是，$dp_1$，和所有弯链 $(u,v)$ 的 $dp_u+dp_v+1$，的 $\max$。

如果有一条直链不在 $u$ 或 $v$ 的子树里，那么为了满足它的限制，我们一定会选一个点，这个点一定可以同时解决 $(u,v)$ 的限制。所以这不是我们期望遇到的，直链满足不了所有弯链，导致 $ans=dp_1+1$ 的情况。而这时 $dp_u+dp_v$ 一定是不超过 $dp_1-1$ 的，$\max$ 取不到它，没有问题。而要是超过了，所有直链肯定都在 $u,v$ 子树里被解决了，但是 $(u,v)$ 弯链还没解决，所以答案确实就需要取到 $dp_u+dp_v+1=dp_1+1$，没有问题。

其实这个做法可以写得非常简单。于是你可以看到一个神秘人士拿着 750B 的精悍代码通过这道题。

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
using namespace std;
using pii=pair<int,int>;
const int N=3e5+7;
int n,m,fa[N],dp[N],vis[N],now[N];
vector<int> ano[N],e[N],e1[N]; vector<pii> v;
void dfs(int p) {
	vis[p]=1;
	for (int i:ano[p]) {
		if (vis[i]==1) {
			if (now[i]==p) cout<<"-1",exit(0);
			e1[now[i]].pb(p);
		}
		else if (vis[i]==2) v.pb({p,i});
	}
	for (int i:e[p]) dfs(now[p]=i),dp[p]+=dp[i];
	for (int i:e1[p]) dp[p]=max(dp[p],dp[i]+1);
	vis[p]=2;
}
int main() {
	scanf("%d%d",&n,&m);
	for (int i=2;i<=n;i++) scanf("%d",&fa[i]),e[fa[i]].pb(i);
	for (int i=1,x,y;i<=m;i++) scanf("%d%d",&x,&y),ano[x].pb(y),ano[y].pb(x);
	dfs(1);
	for (pii i:v) dp[1]=max(dp[1],dp[i.fi]+dp[i.se]+1);
	cout<<dp[1];
	return 0;
}
```

好像是 CF 最短解耶耶耶。

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/CF1610H)

**题目大意**

> 给定一棵 $n$ 个点的无根树，$q$ 条路径 $(u,v)$，每次选取一个点 $w$，如果 $u,v,w$ 的中心不等于 $u$ 或 $v$，那么删除 $(u,v)$，求至少几次操作能删除所有路径。
>
> 数据范围：$n\le 3\times 10^5$。

**思路分析**

以 $1$ 为根，用 $T_u$ 表示 $u$ 子树。

分类讨论，对于一条路径 $u,v$，考虑是不是祖先-后代链。

- 如果是祖先后代链，不妨设 $u$ 是 $v$ 的祖先，且 $v$ 在 $w$ 子树中，其中 $w\in\mathrm{son}(u)$，那么说明在 $T_w\setminus T_v$ 中至少选一个点。
- 如果不是祖先后代链，说明在 $T_1\setminus (T_u\cup T_v)$ 中至少选一个点。

设 $f_u$ 表示 $u$ 子树内至少选多少点，那么转移就是 $f_u\gets f_w+1,f_1\gets f_u+f_v+1$，初始值是 $f_u=\sum_{v\in \mathrm{son}(u)} f_v$。

倍增处理路径。

时间复杂度 $\mathcal O((n+q)\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=3e5+5;
vector <int> G[MAXN],Q[MAXN];
vector <array<int,2>> P;
int n,q,fa[MAXN][20],dep[MAXN],dp[MAXN];
int LCA(int x,int y) {
	if(dep[x]<dep[y]) swap(x,y);
	for(int k=19;~k;--k) if(dep[fa[x][k]]>=dep[y]) x=fa[x][k];
	if(x==y) return x;
	for(int k=19;~k;--k) if(fa[x][k]^fa[y][k]) x=fa[x][k],y=fa[y][k];
	return fa[x][0];
}
void dfs(int u) {
	for(int v:G[u]) dfs(v),dp[u]+=dp[v];
	for(int v:Q[u]) dp[u]=max(dp[u],dp[v]+1);
}
signed main() {
	scanf("%d%d",&n,&q),dep[1]=1;
	for(int i=2,f;i<=n;++i) {
		scanf("%d",&f),dep[i]=dep[f]+1,G[fa[i][0]=f].push_back(i);
		for(int k=1;k<20;++k) fa[i][k]=fa[fa[i][k-1]][k-1];
	}
	for(int u,v,w;q--;) {
		scanf("%d%d",&u,&v),w=LCA(u,v);
		if(v==w) swap(u,v);
		if(u==w) {
			if(fa[v][0]==u) return puts("-1"),0;
			w=v;
			for(int k=19;~k;--k) if(dep[fa[w][k]]>dep[u]) w=fa[w][k];
			Q[w].push_back(v);
		} else P.push_back({u,v});
	}
	dfs(1);
	for(auto it:P) dp[1]=max(dp[1],dp[it[0]]+dp[it[1]]+1);
	printf("%d\n",dp[1]);
	return 0;
}
```

---

## 作者：masonpop (赞：1)

大部分题解都没有详细说明 $f_x$ 对 $f_y+1$ 取 $\max$ 这一步的含义，而想透彻理解此题，这一步属于难点。

显然当且仅当存在一条链为树边时无解，先判掉。

首先可以将链分为两种，即大多数题解里面说的直链和曲链。在这里定义直链为两端点有祖先关系的链，曲链反之。并且约定描述直链 $(x,y)$ 时，$x$ 深度更小。

曲链的处理是平凡的，显然取根节点就可以一步解决。接下来考虑直链。定义 $(x,y)$ 的关键点 $w$ 为 $x$ 到 $y$ 的路径上深度最小的点，即 $w$ 既是 $x$ 的儿子，又是 $y$ 的祖先。那么若想消去直链 $(x,y)$，选取的点必定在 $w$ 子树内，但不在 $y$ 子树内。

考虑 DP。设 $f_x$ 表示处理完所有**关键点在 $x$ 子树内的直链**，至少选多少个点。首先子树内不能互相影响，所以 $f_x=\sum\limits_{y\in son(x)}f_y$ 是第一步。

但是这样的话，关键点为 $x$ 的直链可能不会被处理完。考虑这样的一条链 $(u,v)$ 何时不会被处理。看图。

![](https://cdn.luogu.com.cn/upload/image_hosting/73f21gya.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

由于 $(u,v)$ 没有被处理，因此最优方案中，红色部分肯定一个点都不需要选，即此时 $f_x$ 的答案应该为 $f_v+1$。而当红色部分选了点时，当前 $f_x$ 一定超过 $f_v+1$，同时无需更新。因此直接让 $f_x$ 对 $f_v+1$ 取 $\max$ 就是正确的。大多数题解都略过了这一步，但是我认为这一步分析是比较重要的。

再考虑曲链，我们不能直接给 $f_1$ 加 $1$，因为处理直链的过程可能顺带料理了所有曲链。考虑曲链 $(u,v)$ 何时不会被处理。看图。

![](https://cdn.luogu.com.cn/upload/image_hosting/558d3u8q.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

此时 $u,v$ 子树外的部分一个点都没选，我们需要选上根节点来处理它，即答案应该为 $f_u+f_v+1$。而当外面选了点时，$f_1$ 肯定大于 $f_u+f_v+1$。因此让答案对 $f_u+f_v+1$ 取 $\max$ 也是正确的。

综上，用 $O(n)$ 的复杂度完成了本题。个人认为从链入手比较好分析。[代码](https://codeforces.com/contest/1610/submission/236845112)。

---

## 作者：phil071128 (赞：0)

### CF1610H Squid Game 【贪心】

> 给你一棵树和 $m$ 条路径，每次可以选择一个点 $x$若一条路径上离 $x$ 最近的点不是左右两端点，那么可以删掉这条路径。求最少操作次数或判断无解。$n\le 3\times 10^5$。

无解好判断，路径长度为 $2$ 无解。

令第一次操作的节点为根，第一次操作后只会保留那些直上直下的路径。于是转换成了类似若干条链的问题。

这个问题搬到链上是普及组贪心，即去掉左右两端点的最小覆盖线段。类似的，我们将所有链看做 $(x_i,y_i)$ 其中 $x_i$ 更浅。按照 $x_i$ 深度从大到小排序，如果这条路径未被删除，则选择 $x_i$ 后面的一个节点。而判断一条路径是否被删除可以用树状数组维护子树实现。复杂度 $O(n^2\log n)$。

问题在于需要枚举第一次操作的根，可不可以不用？结论：设此时答案为 $A$，则真正答案一定为 $A$ 或 $A+1$。答案为 $A$ 当且仅当在不选择 $rt$ 时，仅执行上述操作可以覆盖所有非祖先-儿子链。

我们随便钦定 $1$ 作为根，根据上述贪心，我们得到了一个**最浅**的，能够满足 **至少** 覆盖所有祖先-后代链的答案集合 $S$。答案显然不能小于 $|S|$，而且不会超过 $|S|+1$。

我们只需证明任意选择根都可得到答案：因为 **最浅** 的性质，使得此时对所有 **非祖先-后代链** 的影响是最大的，也就是说，如果最终答案中有一个点是用来删除非祖先-后代链的，那么我们把他移到树根一定不劣。时间复杂度 $O(n\log n)$。

能评 *3100的原因大概在如何在做到 H 时自信地肯定贪心的做法与结论。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int read(){
	char c=getchar();int h=0,tag=1;
	while(!isdigit(c)) tag=(c=='-'?-1:1),c=getchar();
	while(isdigit(c)) h=(h<<1)+(h<<3)+(c^48),c=getchar();
	return h*tag;
}
void fil(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
}
const int N=3e5+505;
int n,m;
int dep[N],siz[N],son[N],top[N],f[N],cnt,id[N];
vector<int>s[N];
void dfs1(int x,int fa) {
	siz[x]=1;
	dep[x]=dep[fa]+1;	
	id[x]=++cnt; f[x]=fa;
	int maxson=-1;
	for(int y:s[x]) {
		if(y==fa) continue;
		dfs1(y,x);
		siz[x]+=siz[y];
		if(siz[y]>maxson) {
			maxson=siz[y];
			son[x]=y;
		}
	}
}
void dfs2(int x,int topf) {
	top[x]=topf;
	if(!son[x]) return ;
	dfs2(son[x],topf);
	for(int y:s[x]) {
		if(y==f[x]||y==son[x]) continue;
		dfs2(y,y);
	}
}
int lca(int x,int y) {
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=f[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	return x;
} 
bool cmp(pii a,pii b) {
	if(dep[a.fi]==dep[b.fi]) return dep[a.se]>dep[b.se];
	return dep[a.fi]>dep[b.fi];
}
struct bit{
	#define lowbit(x) (x&-x)
	int t[N];
	void update(int x,int k) {
		while(x<=n) {
			t[x]+=k;x+=lowbit(x);
		}
	}
	int ask(int x) {
		int ans=0;while(x) ans+=t[x],x-=lowbit(x); 
		return ans;
	}
}g;
void upd(int x,int k) {
	g.update(id[x],k);
}
int query_tree(int x) {
	return g.ask(id[x]+siz[x]-1)-g.ask(id[x]-1);
}
int main(){
	//fil();
	n=read(),m=read();
	for(int i=2;i<=n;i++) {
		int x=read();s[x].push_back(i);s[i].push_back(x);		
	}
	dfs1(1,0);
	dfs2(1,1);
	vector<pii>l1,l2;
	for(int i=1;i<=m;i++) {
		int u=read(),v=read();
		if(dep[u]>dep[v]) swap(u,v);
		if(u==f[v]||v==f[u]) return puts("-1"),0;
		int l=lca(u,v);
		if(l==u||l==v) {
			l1.push_back(pii(u,v));			
		}else{
			l2.push_back(pii(u,v));
		}
	}
	sort(l1.begin(),l1.end(),cmp);
	int ans=0;
	for(int i=0;i<l1.size();i++) {
		int l=l1[i].fi,r=l1[i].se,_son; //l<r
		for(int y:s[l]) {
			if(y==f[l]) continue;
			if(id[y]<=id[r]&&id[r]+siz[r]-1<=id[y]+siz[y]-1) {
				_son=y;
				break;
			}
		}
		if(-query_tree(r)+query_tree(_son)==0) {
			ans++;
			upd(_son,1);
		}
	}	
	int tag=0;
	for(pii a:l2) {
		int l=f[a.fi],r=f[a.se];
		if(query_tree(a.fi)+query_tree(a.se)==ans) {
			tag=1;
		}
	}
	cout<<ans+tag<<endl;
	return 0;
}
```

---

