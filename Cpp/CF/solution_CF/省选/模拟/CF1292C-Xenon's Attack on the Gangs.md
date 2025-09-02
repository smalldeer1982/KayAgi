# Xenon's Attack on the Gangs

## 题目描述

[INSPION FullBand Master - INSPION](https://www.youtube.com/watch?v=kwsciXm_7sA)



[INSPION - IOLITE-SUNSTONE](https://www.youtube.com/watch?v=kwsciXm_7sA)



On another floor of the A.R.C. Markland-N, the young man Simon "Xenon" Jackson, takes a break after finishing his project early (as always). Having a lot of free time, he decides to put on his legendary hacker "X" instinct and fight against the gangs of the cyber world.

His target is a network of $ n $ small gangs. This network contains exactly $ n - 1 $ direct links, each of them connecting two gangs together. The links are placed in such a way that every pair of gangs is connected through a sequence of direct links.

By mining data, Xenon figured out that the gangs used a form of cross-encryption to avoid being busted: every link was assigned an integer from $ 0 $ to $ n - 2 $ such that all assigned integers are distinct and every integer was assigned to some link. If an intruder tries to access the encrypted data, they will have to surpass $ S $ password layers, with $ S $ being defined by the following formula:

 $ $$$S = \sum_{1 \leq u < v \leq n} mex(u, v) $ $ </p><p>Here,  $ mex(u, v) $  denotes the smallest non-negative integer that does not appear on any link on the unique simple path from gang  $ u $  to gang  $ v $ .</p><p>Xenon doesn't know the way the integers are assigned, but it's not a problem. He decides to let his AI's instances try all the passwords on his behalf, but before that, he needs to know the maximum possible value of  $ S $ , so that the AIs can be deployed efficiently.</p><p>Now, Xenon is out to write the AI scripts, and he is expected to finish them in two hours. Can you find the maximum possible  $ S$$$ before he returns?

## 说明/提示

In the first example, one can achieve the maximum $ S $ with the following assignment:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1292C/0f9f2baa435ba687ee4d32b6435c04b03bd650e3.png)With this assignment, $ mex(1, 2) = 0 $ , $ mex(1, 3) = 2 $ and $ mex(2, 3) = 1 $ . Therefore, $ S = 0 + 2 + 1 = 3 $ .

In the second example, one can achieve the maximum $ S $ with the following assignment:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1292C/4e86fe7c73ce5613cf34e53621032aa8d877caf3.png)With this assignment, all non-zero mex value are listed below:

- $ mex(1, 3) = 1 $
- $ mex(1, 5) = 2 $
- $ mex(2, 3) = 1 $
- $ mex(2, 5) = 2 $
- $ mex(3, 4) = 1 $
- $ mex(4, 5) = 3 $

Therefore, $ S = 1 + 2 + 1 + 2 + 1 + 3 = 10 $ .

## 样例 #1

### 输入

```
3
1 2
2 3```

### 输出

```
3```

## 样例 #2

### 输入

```
5
1 2
1 3
1 4
3 5```

### 输出

```
10```

# 题解

## 作者：syksykCCC (赞：22)

**UPD:** 修了题解界面 $\LaTeX$ 不兼容的锅。

**UPD2:** 感谢 @[一扶苏一](https://www.luogu.com.cn/user/65363)，修了一个表述不严谨的锅。

---

观察一下答案式子：

$$ \large \begin{array}{rl} S = & \!\! \sum\limits_{1\le u<v \le n} \operatorname{mex}(u, v) \\ = & \!\! \sum\limits_{x = 1}^{n} \left( \sum\limits_{\operatorname{mex}(u, v) = x} x \right) \cdots\cdots(1)\\ = & \!\! \sum\limits_{x = 1}^{n} \left( \sum\limits_{\operatorname{mex}(u, v) \ge x} 1 \right)\cdots\cdots(2)\end{array}$$

$(1) \Rightarrow (2)$ 是怎么推的呢？

考虑一个 $\operatorname{mex}(u, v)$，比如它等于 $y$，原本它对答案只产生一次为 $y$ 的贡献；现在，它对于 $\forall 1\le x\le y$ 都会产生 $1$ 的贡献，正好和还是 $y$。

于是我们定义一个函数 $\operatorname{F}()$，$\operatorname{F}(x) = \sum_{1 \le u < v \le n}[\operatorname{mex}(u, v)  \ge x]$。那么答案式子又可以化为：

$$ \large \begin{array}{rl} S = & \!\! \sum\limits_{x = 1}^{n} \left( \sum\limits_{\operatorname{mex}(u, v) \ge x} 1 \right)\cdots\cdots(2) \\ = & \!\! \sum\limits_{x = 1}^{n} \operatorname{F}(x) \end{array} $$

$\operatorname{F}(x)$ 说通俗一点，就是 $< \! u \to v \! >$ 至少包含了 $0 \sim x - 1$ 的所有数的路径数量。

现在我们从 $0$ 开始，依次放每一个数。比如现在我们要放 $x$，$0 \sim x - 1$ 已经放好了，那么我们一定会把 $x$ 和它们放在同一条路径上，要不然 $x$ 放了以后对答案没有影响。这是因为，放在同一条路径上的话，这里的 $\operatorname{mex}$ 就要变成 $x+ 1$ 了；否则 $0 \sim x - 1$ 已经有数字缺失，那就保持那个缺失的最小数字不变。

那么我们就可以找一个 $<\!u \to v\!>$，它的长度为 $l$，我们要把 $0 \sim l - 1$ 都放在这一条路上。$l \sim n - 2$ 放的位置我们不管，因为它们不会使得答案变劣，更优的方法在后面也一定能枚举到。

想一想，一个最佳的方案一定不仅是完整的一段，而且它的一部分也要是完整的。

比如我们现在选了 $<\!u \to v\!>$：

![image.png](https://i.loli.net/2020/01/21/Ygt7zOCuJNPwH1q.png)

然后 $0$ 我们随便放一下：

![image.png](https://i.loli.net/2020/01/21/kyvAagU46938oQx.png)

下面我们要放 $1$，为了利益最大化，显然，$1$ 和 $0$ 要在一起（这样我们在构造 $0 \sim l - 1$ 的同时也顺便构造了一个 $0 \sim 1$ 的路径）。

比如 $1$ 放在左边：

![image.png](https://i.loli.net/2020/01/21/4f7yTXrL2JlWgP9.png)

然后我们放 $2$，这时我们不管放在 $1$ 的左边还是 $0$ 的右边，都可以顺便构成 $0 \sim 2$ 的路径。

依次类推放完：

![image.png](https://i.loli.net/2020/01/21/BJ3A6wGnbI51LuV.png)

发现了什么？从 $u$ 到 $v$ 依次写下来，正好是一个 **单谷序列**，也就是比如把这个序列叫做 $a$，则有一个位置 $p$，使得 $a_1 > a_2 > \cdots > a_p < \cdots < a_{l-1} <a_l$。

* 用 $dp(u, v)$ 表示把 $0 \sim l - 1$ 放在 $<\!u \to v\!>$ 上，$\sum_{i =1}^{l} \operatorname{F}(i)$ 的最大可能值；
* 用 $s_{root, u}$ 表示以 $root$ 为根时，$u$ 为根的子树大小；
* 用 $p_{root, u}$ 表示以 $root$ 为根时，$u$ 的父亲。

现在我们要计算 $dp(u, v)$，根据单谷序列的性质，$l - 1$ 要么在最左边，要么在最右边，那我们分类讨论一下：

![image.png](https://i.loli.net/2020/01/21/8XOJD2TfW4zreK6.png)

* 如果 $l - 1$ 放在最左边，那么剩下的部分就是 $dp(p_{v, u}, v)$ 的答案，而享受到 $0 \sim l - 1$ 的路径的个数就是 $\operatorname{F}(l) = s_{u, v} \times s_{v,u}$，所以 $dp(u, v) = dp(p_{v, u}, v) + s_{u, v} \times s_{v,u}$；
* 如果 $l - 1$ 放在最右边，那么剩下的部分就是 $dp(u, p_{u, v})$ 的答案，而享受到 $0 \sim l - 1$ 的路径的个数依然是 $\operatorname{F}(l) = s_{u, v} \times s_{v,u}$，所以 $dp(u, v) = dp(u, p_{u, v}) + s_{u, v} \times s_{v,u}$。

综上所述：

$$ \large dp(u, v) = \max(dp(u, p_{u, v}), dp(p_{v, u}, v)) + s_{u, v} \times s_{v,u} $$

我们可以记忆化搜索，$dp(u, v)$ 就可以 $\mathcal O(1)$ 求了，总时间复杂度就是枚举 $u, v$ 的 $\mathcal O(n^2)$。至于 $p_{root, u}$ 和 $s_{root, u}$，可以在之前通过枚举 $root$，每次 $\mathcal O(n)$ 预处理出来。总时间复杂度 $\mathcal O(n^2)$。

代码贴出，仅供参考：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 3005;
int n, rt, p[N][N], s[N][N];
LL f[N][N], ans;
vector<int> G[N];
void build(int u)
{
	s[rt][u] = 1;
	for(int v : G[u]) if(v ^ p[rt][u])
	{
		p[rt][v] = u;
		build(v);
		s[rt][u] += s[rt][v];
	}
}
LL dp(int u, int v)
{
	if(u == v) return 0;
	if(f[u][v]) return f[u][v];
	return f[u][v] = max(dp(u, p[u][v]), dp(v, p[v][u])) + s[u][v] * s[v][u];
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	for(int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i = 1; i <= n; i++) { rt = i; build(i); }
	for(int u = 1; u <= n; u++) 
        for(int v = 1; v <= n; v++)
            ans = max(ans, dp(u, v));
	cout << ans << endl;
	return 0;
}
```

---
参考文献
* [Akikaze.Codeforces Round #614 Editorial.CodeForces](https://codeforces.com/blog/entry/73051)

---

## 作者：Mr_Wu (赞：5)

### 题意

[题目链接](https://codeforces.com/contest/1293/problem/E)

给定一棵树，试将 $[0,n-2]$ 内的每个整数不重不漏填到每条边上，使得 $\sum\limits_{1\le u<v\le n} \text{mex}(u,v)$ 最小，其中 $\text{mex}(u,v)$ 表示从节点 $u$ 到节点 $v$ 经过的边集合 $A_{u,v}$ 中最小的未出现的非负整数。

数据范围：$2\le n\le 3000$

### 题解

考虑我们选定了一条边 $(u,v)$ 是 0，删掉这条边后树变成两部分，则答案加上两部分的大小乘积对吧。

然后我们考虑选定一条边是 1，理性分析一下可以发现应该放在 $u$ 或 $v$ 的邻边上，不然同时经过 0,1 的路径肯定会少，对答案能贡献 2 的路径也会变少，并且接下来填 2 能获得的贡献也不会多 ...

如图，总之我们一定会将 0 填在 1 旁边，然后就会对答案加上 $A\times B$，这样算是因为端点分别在 $A,B$ 中的已经被算过一次贡献了。

![](https://cdn.luogu.com.cn/upload/image_hosting/azfw2ee8.png)

然后我们会继续将 2 填在这条路径（0,1构成的路径）的端点，以此类推 ... 是“沿一条路径向外扩散的”。

因此我们就转化成了个这样的问题：首先定义 $u$ 左边的 $\text{siz}$ 为以 $u$ 为根的，$v$ 右边的 $\text{siz}$ 为以 $v$ 为根的，选定一条边 $(u,v)$，填 0，对答案贡献 $\text{siz}_u\times \text{siz}_v$，然后每次选择 $u$ 或 $v$，比如 $u$，将其走到任意一个儿子上，然后对答案贡献 $\text{siz}_u\times \text{siz}_v$，如此一直操作直到不能操作，答案的最大值。

于是我们有了一个 $O(n^3)$ 的想法：枚举边 $(u,v)$，设 $f_{i,j}$ 为 $u$ 操作到 $i$，$v$ 操作到 $j$，继续向下操作能得到的最大收益，可得如下转移方程：

$$ f_{i,j}=\text{siz}_i\times \text{siz}_j+\max\{ \max_{k\in \text{son}_i} f_{k,j}, \max_{k\in \text{son}_j} f_{i,k} \} $$

那么我们思考如何将其优化成 $O(n^2)$，这个算法枚举 0 的复杂度应该省不了，考虑 dp 的复杂度，每次 $O(n^2)$ dp 确实很慢，这是因为换一条边后点的 $\text{siz}$ 会变。

但实际上很多点的 $\text{siz}$ 都没变！如果我们一开始让 $\text{siz}$ 定义为以 1 为根的，当我们选定点 $(\text{fa}_u,u)$ 时，在下图中只有红色部分的 $\text{siz}$ 变了：

![](https://cdn.luogu.com.cn/upload/image_hosting/17pyyuv9.png)

因此，我们深搜寻找答案，搜到 $u$ 时处理 $(\text{fa}_u,u)$ 这条边为 0 的答案，我们将 $\text{fa}_u$ 的 $\text{siz}$ 变为 $N-\text{siz}_u$，然后只更新 $\forall i\in T(u),f_{\text{fa}_u,i}$，最后将 $f_{\text{fa}_u,u}$ 作为答案。

时间复杂度 $O(n^2)$。

### 代码

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
ll read() {
    ll ret = 0; char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') ret = ret * 10 + c - '0', c = getchar();
    return ret;
}

const int MAXN = 3005;

int N;
struct node { int v, next; }  E[MAXN << 1]; int head[MAXN], Elen;
void add(int u, int v) { ++Elen, E[Elen].v = v, E[Elen].next = head[u], head[u] = Elen; }

ll siz[MAXN], Siz[MAXN], Dp[MAXN][MAXN]; int fa[MAXN], dfn[MAXN], dfncnt, redfn[MAXN];
void dfs(int u, int ff) {
    siz[u] = 1, fa[u] = ff, dfn[u] = ++dfncnt, redfn[dfncnt] = u;
    for (int i = head[u]; i; i = E[i].next) if (E[i].v != ff) dfs(E[i].v, u), siz[u] += siz[E[i].v];
}
ll getdp(ll dp[][MAXN], int u, int v, int del = 0, int add = 0) {
    if (dp[u][v]) return dp[u][v];
    int i; ll ret = 0;
    for (i = head[u]; i; i = E[i].next) if (E[i].v != fa[u] && E[i].v != del) ret = max(ret, getdp(dp, E[i].v, v, del, add));
    if (add) ret = max(ret, getdp(dp, add, v, del, add));
    for (i = head[v]; i; i = E[i].next) if (E[i].v != fa[v]) ret = max(ret, getdp(dp, u, E[i].v, del, add));
    dp[u][v] = siz[u] * siz[v] + ret; return dp[u][v];
}

ll f[MAXN][MAXN], ans;
void dfs2(int u, int ff) {
    int i;
    if (u != 1) {
        for (i = dfn[u]; i <= dfn[u] + siz[u] - 1; ++i) f[fa[u]][redfn[i]] = 0;
        siz[fa[u]] = N - Siz[u];
        for (i = dfn[u]; i <= dfn[u] + siz[u] - 1; ++i) getdp(f, fa[u], redfn[i], u, fa[fa[u]]);
        ans = max(ans, f[fa[u]][u]);
        for (i = head[u]; i; i = E[i].next) if (E[i].v != ff) dfs2(E[i].v, u);
        for (i = dfn[u]; i <= dfn[u] + siz[u] - 1; ++i) f[fa[u]][redfn[i]] = Dp[fa[u]][redfn[i]];
        siz[fa[u]] = Siz[fa[u]];
    } else {
        for (i = head[u]; i; i = E[i].next) if (E[i].v != ff) dfs2(E[i].v, u);
    }
}

int main() {
    scanf("%d", &N); int i, j, u, v;
    for (i = 1; i < N; ++i) scanf("%d%d", &u, &v), add(u, v), add(v, u);
    dfs(1, 0);
    for (i = 1; i <= N; ++i) Siz[i] = siz[i];
    for (i = 1; i <= N; ++i) for (j = 1; j <= N; ++j) f[i][j] = getdp(Dp, i, j);
    dfs2(1, 0);
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：hzoi_liuchang (赞：2)

 我们先随便找一条边，将它的价值赋值成0

那么只要有一个路径经过这条边，那么这个路径的最小价值就一定不会为0

我们举一个例子
![](https://cdn.luogu.com.cn/upload/image_hosting/cdl1sbo4.png)
 此时u到v的价值为0，那么这一条路径不经过的最小非负整数就是1

一条路径只要经过(u,v)这条边，那么它们不经过的最小非负整数就至少为1（因为它们已经经过了0）

我们用f[i][j]表示从i开始，从j结束，将i到j之间所有的m条边赋值成0到m-1所得到的最大价值

用g[i][j]表示在i号节点作为根节点的情况下，以j为根节点的子树的大小

用pa[i][j]表示在i号节点作为根节点的情况下，j节点的父亲节点
!

我们再来看上面这幅图，只要经过（u,v）这条边，那么它们没有经过的最小非负整数的价值就至少为1

此时总价值为g[u][v]*g[v][u]

那么我们再添加价值为1的边，为了使总的价值最大，这条边显然要和价值为0的边放在一起

为什么呢？因为如果放在别的地方，那么价值为1的路程会增多，而价值为2的路程会减少

换一句话说，价值为1的这条边对其它路程的贡献减少了

我们来举一个例子
![](https://cdn.luogu.com.cn/upload/image_hosting/5ht56oyl.png)
在左边这幅图中，我们没有把价值为1的边放在价值为0的边的旁边，这时(u,B)这条边永远会缺失1，我们从v向下遍历，同时经过0和1的路径的个数会减少，会有很多路径的价值为1，以后也不会再改变

 在右边这幅图中，我们有把价值为1的边放在价值为0的边的旁边，这时(u,B)这条边的边权1，它的价值也就为1，我们从v向下遍历，同时经过0和1的路径的个数显然要比上面的多，路径的价值一定会大于1
![](https://cdn.luogu.com.cn/upload/image_hosting/bjyqp7oj.png)
f[u][v]=max(f[u,pa[u][v]],f[v,pa[v][u]])+g[u][v]*g[v][u]

什么意思呢，我们还是拿图来说
![](https://cdn.luogu.com.cn/upload/image_hosting/dab5txp8.png)
  我们假设u和v之间的边权都已经从小到大加完，那么其中最大的一个权值我们不是加在（u,pa[v][u]）上，就是加在（v,pa[u][v]）上

 如果加在（u,pa[v][u]）上，那么增大的价值就是g[u][v]*g[v][u]，还要加上原来就有的f[u,pa[u][v]]

 如果加在（v,pa[u][v]）上，那么增大的价值就是g[u][v]*g[v][u]，还要加上原来就有的f[v,pa[v][u]]

实际上这两种情况增大的价值都是一样的，我们只需要在f[u,pa[u][v]]和f[v,pa[v][u]]中取最大值就可以了

最后我们再看一下最后的决策是什么情况

根据我们一开始的推论，边权从小到大一定会加在同一条链上，但是这一条链不一定会包含n-1条边，就像下面这样![](https://cdn.luogu.com.cn/upload/image_hosting/cs415d39.png)
 标红色的是我们已经选好边权的边

这时我们会发现（2，3）（4，7）这两条边并没有被赋上相应的价值，这时该怎么办呢，最后的价值还是f[8][9]吗？

答案是肯定的，此时边权只剩下了最大的两个，无论加到那一条边上都不会对结果产生影响

那么3、7节点贡献的价值呢，实际上，在我们决策2、1、4这三个点时，3、7作为子树价值已经被确定了，无论你加多大的边权也不会改变路程没有经过的最小非负整数

代码的话，g、pa数组我们可以预处理得到，f数组我们枚举取最大值就可以了

这道题也要开long long否则会爆掉
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;
const int maxd=3010;
typedef long long ll;
struct asd{
    ll from,to,next;
}b[maxd*2];
ll head[maxd],tot=1;
void ad(ll aa,ll bb){
    b[tot].from=aa;
    b[tot].to=bb;
    b[tot].next=head[aa];
    head[aa]=tot++;
}
ll pa[maxd][maxd],f[maxd][maxd],g[maxd][maxd];
ll rt=1;
void dfs(ll now,ll fa){
    g[rt][now]=1;
    for(ll i=head[now];i!=-1;i=b[i].next){
        ll u=b[i].to;
        if(u==fa) continue;
        pa[rt][u]=now;
        dfs(u,now);
        g[rt][now]+=g[rt][u];
    }
}
ll solve(ll u,ll v){
    if(u==v) return 0;
    if(f[u][v]) return f[u][v];
    return f[u][v]=max(solve(u,pa[u][v]),solve(v,pa[v][u]))+g[u][v]*g[v][u];
}
int main(){
    memset(head,-1,sizeof(head));
    ll n;
    scanf("%lld",&n);
    for(ll i=1;i<n;i++){
        ll aa,bb;
        scanf("%lld%lld",&aa,&bb);
        ad(aa,bb);
        ad(bb,aa);
    }
    for(ll i=1;i<=n;i++){
        rt=i;
        dfs(i,-1);//递归，预处理s数组和pa数组
    }
    ll ans=-1;
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=n;j++){
            ans=max(solve(i,j),ans);//取最大值
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：YLWang (赞：2)

自从做过树上的数之后心里就埋下了对这种树上排列的题深深的恐惧。

但其实这题难度并不是特别高。

首先，我们观察出这是一个计算路径属性和的问题。做这类问题有一个普遍的方法，就是把所有路径的和转化为所有边对答案贡献的和。

这个时候就可以枚举边了。从特殊到一般来考虑。

对于边权为$0$的边，设其两端的点分别为$u$, $v$。那么显然，这条边把整棵树分成了两棵树$tr_u, tr_v$。对于任意一对$tr_u$中的点和$tr_v$中的点，他们之间的$mex$从$0$变为了$1$（因为经过了边权为$0$的边）。所以这条边对答案的贡献就是$siz_{tr_u} \cdot siz_{tr_v}$。

那么边权为$1$的边放哪儿？

我们手玩一下可以发现，放在$0$旁边一定是最优的。这很好理解。再往下，把新的边放在已经选择的边构成的链两端一定是最优的。一直到最后，放新边已经对答案没有贡献了。这时候可以随便放

但是我们不知道新边应该放哪端怎么办？

$dp$.

先枚举一手$u$, $v$。设这条边把整棵树分成了两棵树$tr_u, tr_v$。$siz[i]$为以点$i$为根构成的**子子**树的大小。$dp[i][j]$表示$u$这棵子树下的链长到了$i$，$v$这棵子树下的链长到了$j$是**还能**得到的最大和。则有$dp[i][j] = siz[i] \cdot siz[j] + max(dp[son[i]][j], dp[son[j]][i]) $

再之后类似换根DP地做就可以实现$n^2$的复杂度了。

---

## 作者：AK_400 (赞：1)

首先考虑链，从小到大加数，新加入的数一定和已加入的数相邻，不妨设我们要加的数是 $1$，已经加入了 $0$。那么和 $0$ 相邻时 mex 等于二的路径个数一定不比不相邻时少。

于是我们可以令 $dp_{l,r}$ 表示已经放入的数的区间为 $[l,r]$，转移就是考虑最后一个数放在左边还是右边。

也就是 $dp_{l,r}=\max(dp_{l+1,r},dp_{l,r-1})+l\cdot (n-r+1)$。右边的式子表示有几个区间包含 $[l,r]$，只算一次的原因是这些区间的贡献在我们计算 $\max(dp_{l+1,r},dp_{l,r-1})$ 时已经被算过了 $r-l$ 次，实际贡献为 $r-l+1$。

考虑树上怎么做。

因为要求路径，所以我们希望放进去的数构成一条链，并且不包含这条链的路径没有更多贡献（没有当前放的数）。

所以记 $dp_{u,v}$ 表示已经放入的数构成的链为 $(u,v)$，那么转移和链上是同理的。

记 $u',v'$ 为链上距离 $u,v$ 为 $1$ 的点，那么有 $dp_{u,v}=\max(dp_{u',v},dp_{u,v'})+sz_{u,v}\times sz_{v,u}$。其中 $sz_{u,v}$ 表示以 $u$ 为根，$v$ 的子树大小，可以记搜。答案就是所有 $dp$ 值的最大值。

$sz_{u,v}$ 可以对每个点预处理，或者固定一个根写个 LCA 分讨一下也行。


```
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int n;
vector<int>e[3005];
int fa[3005],sz[3005],son[3005],tp[3005],dep[3005];
void dfs(int p){
    sz[p]=1;
    for(int x:e[p]){
        if(x==fa[p])continue;
        fa[x]=p;
        dep[x]=dep[p]+1;
        dfs(x);
        sz[p]+=sz[x];
        if(!son[p]||sz[x]>sz[son[p]])son[p]=x;
    }
}
void dfs1(int p,int top){
    tp[p]=top;
    if(son[p])dfs1(son[p],top);
    for(int x:e[p]){
        if(x==son[p]||x==fa[p])continue;
        dfs1(x,x);
    }
}
int lca(int x,int y){//树剖，也可以用倍增
    while(tp[x]!=tp[y]){
        if(dep[tp[x]]<dep[tp[y]])swap(x,y);
        x=fa[tp[x]];
    }
    return (dep[x]>dep[y]?y:x);
}
int getson(int x,int y){//找到 x 为 y 的祖先时，(x,y) 这条链上与 x 的距离为1的点
    while(tp[x]!=tp[y]){
        if(fa[tp[y]]==x)return tp[y];
        y=fa[tp[y]];
    }
    return son[x];

}
bool vis[100005];
int dp[3005][3005];
int dfs(int u,int v){
    if(u>v)swap(u,v);
    if(dp[u][v])return dp[u][v];
    if(u==fa[v])return dp[u][v]=sz[v]*(n-sz[v]);
    if(v==fa[u])return dp[u][v]=sz[u]*(n-sz[u]);//只有一条边，填0
    int l=lca(u,v);
    if(l!=u&&l!=v){//互不为祖先，
        dp[u][v]=max(dfs(fa[u],v),dfs(u,fa[v]))+sz[u]*sz[v];
    }
    if(l==u){//u 是 v 的祖先，那么 u' 为 u 的儿子
        int so=getson(u,v);
        dp[u][v]=max(dfs(so,v),dfs(u,fa[v]))+sz[v]*(n-sz[so]);
    }
    if(l==v){//v 是 u 的祖先，那么 v' 为 v 的儿子
        int so=getson(v,u);
        dp[u][v]=max(dfs(fa[u],v),dfs(u,so))+sz[u]*(n-sz[so]);
    }
    return dp[u][v];
}
void slv(){
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j)continue;
            ans=max(dfs(i,j),ans);
        }
    }
    cout<<ans<<endl;
}
signed main(){
    cin>>n;
    if(n==1){
        cout<<0;
        return 0;
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1);
    dfs1(1,1);
    slv();
    return 0;
}
```

---

## 作者：fmj_123 (赞：1)

题目大意：

给一棵$n$个节点的树，将$[0,n-2]$分配到每一条边，定义$s(s,t)$为$s$到$t$路径边权的$mex$，求$s(s,t)$和的最大值

名词解释：$mex$：没有出现的最小**自然数**（即$[0,+\infty]$）

题目思路：

emm，感觉假如这棵树变为**一条链**的情况可以讨论一下，对本题有启发。（其实就是链上方案推广到树上，两者是相通的。但链的情况显然更好想）

先考虑 $0$ 的放置，根据定义，若 $0$ 放置在一条左边有 $x$ 节点，右边有 $y$ 节点的边，则贡献为 $x\times y$，最大化该值即可。

再考虑 $1$ 的放置，若 $1$ 不在 $0$ 边的左或右，方案将**不会更优**。证明如下。

现有两个方案
```
A:.... 2 1 0 ..... B: .... 1 2 0 ....
```
假设`...`并没有差别，那么

0. 按照题意，不考虑 $0$ 左右的内部答案，因为都是 $0$

1. 左边的...到右边的...答案没有差别

2. $1$ 到右边的...，B答案>A答案（全是 $2$）

3. $2$ 到右边的...，A答案>B答案（全是 $1$）

显然，$2$ 中的B答案等于 $3$ 中的A答案，即两方案的答案事实上是**相同**的，若考虑将上文方案中的 $2$ 换为大于 $2$ 的数，则B显然会比A**劣**。因此，$1$ 须放在 $0$ 的左右。具体的说，若 $0$ 左边有 $x$ 个节点，右边有 $y$ 个节点，那么需比较 $(x-1)\times y$ 和 $x \times (y-1)$。

接着往下考虑，可以证明对于每个数，使该数在已编号的序列的左、右将不会更劣。方案亦与上文类似。

其实，我们可以看到，每个边对答案的贡献是**经过该边的次数 $\times 1  /0$** 。即只有两种情况。因此，我们在按照上面的构造方案的情况下无需再考虑编号问题。

按上面的方法，一条链的方案便可构造出来。

==分割线==

回到正文，现在我们考虑的是树，但可以视为**若干条链**。如上文所说，链和树的做法里某些东西是相通的。

仿照链的做法，此时放置方案应使 $0$ 到一个尽量大的数都放在**一条特定的链**上。其他方案不会更优。至于证明，可仿照链的证明方式。

那么现在我们要找到这条特定的链。通过贪心来找到这条特定的链不大可行。考虑每一条链都求出该链为特定链时，这棵树的总答案。

这里可以通过记忆化搜索求解，通过 $(u,v)$ 的答案可求 $u$,$v$ 的子节点的答案。

记 $f(u,v)$ 为将 $u$ 到 $v$ 作为上文的特定的链的答案。则
$f(u,v)=max(f(fa_u,v),f(i,fa_v))+siz_u \times siz_v$。

但是，随着 $(u,v)$ 的改变，树的形态可能会发生一定改变，这意味着 $fa_x$ 和 $siz_x$ 会发生改变，解决方案是将每个节点作根时的$fa$和$siz$状况都预处理下来，在 $(u,v)$ 状况下，$fa_u$ 和 $siz_u$ 分别是 $v$ 作为根时的 $fa$ 和 $siz$，这个画图可以理解。

至此，本题基本完成，以下是本题代码。
```
#include<bits/stdc++.h>
using namespace std;
int cc,to[6000],net[6000],fr[6000];bool vis[6000];
int rot,fa[3005][3005];
int n,u,v;long long ans,f[3005][3005],siz[3005][3005];
void addedge(int u,int v)
{
	cc++;
	to[cc]=v;net[cc]=fr[u];fr[u]=cc;
}
void dfs(int x)
{
	vis[x]=true;
	for (int i=fr[x];i;i=net[i])
	{
		if (!vis[to[i]])
		{
			fa[rot][to[i]]=x;
			siz[rot][to[i]]=1;
			dfs(to[i]);
			siz[rot][x]+=siz[rot][to[i]];
		}
	}
}
long long dp(int u,int v)
{
	if (f[u][v]) return f[u][v];
	if (u==v) return 0;
	f[u][v]=max(dp(fa[v][u],v)+siz[v][u]*siz[u][v],
	dp(u,fa[u][v])+siz[v][u]*siz[u][v]);
	return f[u][v];
}
int main()
{
	cin>>n;
	for (int i=1;i<n;i++)
	{
		cin>>u>>v;
		addedge(u,v);
		addedge(v,u);
	}
	for ( rot=1;rot<=n;rot++)
	{
		for (int j=1;j<=n;j++)
		  vis[j]=false;
		siz[rot][rot]=1;fa[rot][rot]=0;dfs(rot);
	}//预处理每个节点为根时的fa和siz
	for (int i=1;i<=n;i++)
	  for (int j=1;j<n;j++)
	  {
	  	dp(i,j);ans=max(ans,f[i][j]);
	  }//记搜
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Su_Zipei (赞：1)

## 题意
在一颗有n个节点的树上，给每个边赋值，所有的值都在$[0,n-2]$内并且不重复，也就是一条边一个权值，令$mex(u,v)$表示从$u$到$v$这条简单路径上没有出现过的最小自然数，要求使所有路径的$mex$之和最大。

## 分析
最开始我一看这个题，统计答案的时候好像就需要$O(N^2)$,那这个题好像统计个答案就可能会T？当我看见时限是$3s$的时候我就知道我想多了，分析时间复杂度的时候提前看一下时限，防止因看错时限分析错时间复杂度。
首先这个边的权值肯定有规律，不然枚举权值时间复杂度会很高，最开始我想的是从每个边开始$dfs$一下把经过次数最多的边设成0，然后依次类推，每次$dfs$不访问重复经过的点，发现存在一个什么问题呢，就是从不同的点开始$dfs$造成的结果不一样，所以这样不可行，不妨先画一条链来看看。

![](https://cdn.luogu.com.cn/upload/image_hosting/lmwv3zx8.png?x-oss-process=image/resize,m_lfit,h_00,w_500)

如果已经放好了$0$到$x-1$，考虑$x$放哪个位置，如果我把$x$放到$5-v$上，那么$mex(u,5)$就会是$x$，然后只有$mex(u,v)$会等于$x+1$，但要是把$x$放到$u-1$或$4-5$上，$mex$等于$x+1$的就不会只是$mex(u,v)$了。链上是这样，树上当然也是，所以$x$放到链的两端会使结果更优。

![](https://cdn.luogu.com.cn/upload/image_hosting/qlrym8tk.png?x-oss-process=image/resize,m_lfit,h_00,w_500)

也就是这样，对于$u-v$的路径，4和5放在最两端时结果会更优，然后对最大值5的位置进行分类讨论，就可以求解出答案。
还有一个问题，如果我真的去把每个$mex$相加，的确很不现实，根据之前做过的一些类似的题，直接加上$x$相当于在$0~x-1$各加1，转化成对答案的贡献，也就是$size_u*size_v$,这样求解起来就会相对简单。
之前已经讲过，从不同的点开始$dfs$的结果是不同的，所以不能像平常那样统计$size$,而是应该在加一维表示根，这样才能保证得到我们想要的$size$，因为要枚举最大权值所在的地方，所以还要记录每个节点的父亲，同样也要记录根。
不妨用$dp_{u,v}$表示把$0~x-1$放到$u-v$的最大答案，$s_{u,v}$表示$v$以$u$为根时的子树大小，$fa_{u,v}$表示$v$以$u$为根时的父亲。于是有
$$dp_{u,v}=max(dp_{fa_{u,v},u},dp_{fa_{v,u},v})+s_{u,v}*s_{v,u}$$
然后此题就能得解，注意开long long
```
#include<iostream>
#define ll long long
using namespace std;
const int N=3e3+10;
struct Edge{
    int to,nxt;
}e[N<<1];
int Head[N],len;
void Ins(int a,int b){
    e[++len].to=b;e[len].nxt=Head[a];Head[a]=len;
}
int rt;ll s[N][N],dp[N][N],f[N][N];
void dfs(int u){
    s[rt][u]=1;
    for(int i=Head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==f[rt][u])continue;
        f[rt][v]=u;
        dfs(v);
        s[rt][u]+=s[rt][v];
    }
}
ll calc(int u,int v){
    if(u==v)return 0;
    if(dp[u][v])return dp[u][v];
    return (dp[u][v]=max(calc(f[u][v],u),calc(f[v][u],v))+s[u][v]*s[v][u]);
}
int main(){
    int n;
    cin>>n;
    for(int i=1;i<n;i++){
        int a,b;
        cin>>a>>b;
        Ins(a,b);Ins(b,a);
    }
    for(int i=1;i<=n;i++)rt=i,dfs(i);
    ll ans=0;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
        ans=max(ans,calc(i,j));
    cout<<ans;
}
```

---

## 作者：ax_by_c (赞：0)

首先可以发现不经过 0 的路径贡献都是 0，经过 0 的路径至少产生 1 的贡献。

然后在经过 0 的基础上再经过 1 的路径又会产生 1 的贡献。

以此类推，一条路径每经过一个值域上的前缀就会产生 1 的贡献。

考虑确定边权后的计算，枚举值域前缀，构建出对应边的虚树，如果是一条链的话就加上两边节点个数之积。

不难发现让尽量多的值在一条链上更优，同时每次向两边加值更优。（调整法易证）

于是考虑 DP，设 $f_{u,v}$ 表示当前链的两端分别是 $u,v$ 时的最大答案，转移考虑哪一边是新加的，预处理任意两点路径长度和后继即可。

时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
typedef long long ll;
const int N=3005;
int n;
vector<int>g[N];
int dis[N][N],nxt[N][N];
void dfs(int st,int u){
	for(auto v:g[u]){
		if(v==nxt[st][u])continue;
		dis[st][v]=dis[st][u]+1;
		nxt[st][v]=u;
		dfs(st,v);
	}
}
int fa[N],sz[N];
void ddfs(int u){
	sz[u]=1;
	for(auto v:g[u]){
		if(v==fa[u])continue;
		fa[v]=u;
		ddfs(v);
		sz[u]+=sz[v];
	}
}
int getsz(int u,int v){
	if(v==fa[u])return sz[u];
	return n-sz[v];
}
ll f[N][N];
ll dp(int u,int v){
	if(u==v)return 0;
	if(f[u][v]!=-1)return f[u][v];
	return f[u][v]=max(dp(nxt[v][u],v),dp(u,nxt[u][v]))+(ll)getsz(u,nxt[v][u])*getsz(v,nxt[u][v]);
}
void main(){
	scanf("%d",&n);
	for(int i=1,x,y;i<n;i++){
		scanf("%d %d",&x,&y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for(int i=1;i<=n;i++)dfs(i,i);
	ddfs(1);
	for(int x=1;x<=n;x++){
		for(int y=1;y<=n;y++)f[x][y]=-1;
	}
	ll ans=0;
	for(int x=1;x<=n;x++){
		for(int y=1;y<=n;y++)ans=max(ans,dp(x,y));
	}
	printf("%lld\n",ans);
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：lizihan250 (赞：0)

# Codeforces Round 614 Div 2 E & Div 1 C. Xenon's Attack on the Gangs

## 题意简述

给定一棵 $n(1 \le n \le 3000)$ 个节点的树。定义 $path(u,v)$ 为树上从 $u$ 到 $v$ 经过边数最少的路径上所有边的权值的集合，$mex(u,v)$ 为没有在 $path(u,v)$ 中出现的最小自然数。试给每条边赋予 $[0,n-2]$ 之间的互不相同的整数权值，使得 $\sum\limits_{1 \le u \le v \le n} mex(u,v)$ 最大。

## 解题思路

这类题目的常规解法是考虑每个点权或边权对答案的贡献。

我们先考虑 $0$ 对于答案的贡献。不难发现，若把边权为 $0$ 的这条边删掉后，会产生两个子树，两个子树内的节点都必须经过删掉的边才能到另一棵子树。因此，若两棵子树内的节点数分别为 $s,t$，则把这条边的权值设为 $0$ 对全局的贡献为 $s \times t$。

再考虑 $1$ 对于答案的贡献。$1$ 只能在含有边权为 $0$ 的路径上产生贡献。为了使贡献最大化，边权为 $1$ 的边与边权为 $0$ 的边必然紧密相连。若边权为 $0$ 的边的连接节点 $x,y$，边权为 $1$ 的边连接节点 $y,z$，则边权为 $1$ 的边的额外贡献为删去这两条边后，形成的两子树的节点数的乘积。

再接下来，考虑边权为 $i(1 \le i \le n-2)$ 的边对答案的贡献时，我们可以把边权为 $0$ 至 $i-1$ 的边构成的链类似的看成一条“边”，进行类似的讨论。

考虑使用动态规划解决该题。设 $dp(i,j)$ 为 $i$ 至 $j$ 的路径上均已标有从 $0$ 开始的连续自然数的边权时，目前总贡献的最大值。若这个路径可以被写为 $u \to x \to \cdot \cdot \cdot \to y \to v$ 的形式，那么，它可以从 $dp(x,v)$ 或 $dp(u,y)$ 转移而来。对于直接相连的边，直接计算贡献即可。

关键在于求出从某个点出发，删去一条边，能抵达的节点数量。我们可以记录以每个点 $u$ 为根的子树的大小（记为 $s_u$）。若从该点出发到父亲的边被删除，则答案为 $s_u$，否则若其到子树 $v$ 的边被删除，则答案为 $s_u$，减去以 $v$ 为根的字数大小 $s_v$，再加上不在 $u$ 中的节点数量 $n-s_u$（简单理解为“向上走”）。通过从每个顶点 DFS 一次，我们就可以预处理上述内容，进而求出把任意一对点对赋完权值后对全局的贡献，接着按前文所述转移即可。

预处理时间复杂度 $O(n^2)$。由于每个状态只能从两种状态转移过来，而状态数也为 $n^2$ 个，因此时间复杂度为 $O(n^2)$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=3000;
int n,u,v;
long long ans=0;
vector<vector<int> > adj;
struct node
{
    int fa,p,size;
}nums[Maxn+20];
struct pp
{
    int x,y,dis;
    long long ans;
}path[Maxn+20][Maxn+20];
vector<pair<int,int> > sta[Maxn+20];
void dfs(int nw,int fa)
{
    nums[nw].size=1;
    for(int i=0;i<adj[nw].size();i++)
    {
        if(adj[nw][i]==fa)
        {
            nums[nw].fa=adj[nw][i];
            continue;
        }
        dfs(adj[nw][i],nw);
        nums[nw].size+=nums[adj[nw][i]].size;
    }
    return;
}
void dfs2(int from,int nt,int nw,int fa,int len)
{
    path[from][nw].x=nt;
    path[from][nw].y=fa;
    int sz1=nums[from].size,sz2=nums[nw].size;
    if(nt!=nums[from].fa) sz1+=n-nums[from].size-nums[nt].size;
    if(fa!=nums[nw].fa) sz2+=n-nums[nw].size-nums[fa].size;
    path[from][nw].dis=sz1*sz2;
    sta[len].emplace_back(make_pair(from,nw));
    for(int i=0;i<adj[nw].size();i++)
    {
        if(adj[nw][i]==fa) continue;
        dfs2(from,nt,adj[nw][i],nw,len+1);
    }
    return;
}
int main()
{
    scanf("%d",&n);
    adj.resize(n+5);
    for(int i=1;i<n;i++)
    {
        scanf("%d %d",&u,&v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    //cout<<"DFS 1 complete!"<<endl;
    for(int i=1;i<=n;i++)
    {
        path[i][i].ans=0;
        for(int j=0;j<adj[i].size();j++)
        {
            dfs2(i,adj[i][j],adj[i][j],i,1);
        }
    }
    //cout<<"DFS 2 complete!"<<endl;
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<sta[i].size();j++)
        {
            u=sta[i][j].first,v=sta[i][j].second;
            path[u][v].ans=max(path[u][path[u][v].y].ans,path[path[u][v].x][v].ans)+path[u][v].dis;
            ans=max(path[u][v].ans,ans);
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：UperFicial (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1292C)。

[$\text{cnblogs}$](https://www.cnblogs.com/UperFicial/p/16657535.html)。

考虑增量法，枚举一个答案 $x$，它的贡献为路径 $\operatorname{mex}$ 不小于 $x$ 的路径数量。

那么我们顺次放入边权 $w=[0,1,\cdots,n-2]$。

考虑边权 $1$ 的放置，它的贡献为与边权 $0$ 形成的路径左右两侧子树大小的乘积。

我们想让收益最大，所以我们把 $1$ 放到 $0$ 相邻的位置。

而对于 $2$ 呢？要想收益最大，必须与 $1$ 和 $0$ 构成一条连续的简单路径。

这样我们以此类推。

考虑一条路径 $u\to v$，中间经过的边权形成了一个单谷序列，这个可以反证。

也就是说，对于一条路径 $u\to v$，我们在这条路径上填入一段单谷序列，最大值一定处于路径的左端点或右端点。

这样的话就可以暴力 DP 了，分讨一下最大值放在右端还是左端，之后往剩余路径上 DP。

[代码](https://codeforc.es/contest/1292/submission/170907212)。

---

## 作者：MCAdam (赞：0)

考虑链的情况对正解有很大的启发性

一开始想着直接从小到大放就行了，这样答案就是$\dfrac{n(n-1)}{2}$

但发现其实这样是很不优的，因为只有选取的区间的一端是$0$时才会对答案有贡献

也就是说，如果希望答案尽量大，就要尽可能把小的值尽量填充

考虑从小到大放置数字：

首先是$0$，如果它左端点位置为$pos$，那么经过这条边的路径有$pos\times (n-pos)$条

然后可以证明：$1$边一定是放在$0$边旁边的，分类讨论一下就行了

两种情况：$\text{xxxx1xxx0xxxx}$和$\text{xxxxx10xxxxx}$

对于跨越了$0,1$的区间，答案就和$0,1$的位置“无关”，但是显然右边的这样的区间更多

对于没有跨越$0,1$的区间，只有左边这种情况有，答案只能是$0/1$

这里并没有非常严谨的证明，只是从整体上认知。同理可以推出：**每一个数字肯定是放在已知数字的左边或者右边**

根据上面的分析，我们从小到大放数值，就是希望它们能覆盖的区间越多越好。所以$0$边肯定是放在中间，每次新增加一个数字，就判断左边更优还是右边更优来放就好了

链的情况解决了，想办法把链的情况搬到树上就行了

因为经过$0$边的答案，至少会是$1$，不妨考虑费用提前计算，这样就不需要考虑到底经过了哪些边，那么贡献就是$size[x]\times size[y]$

当经过$1$边时，同样贡献为$size[x]\times size[y]$，这样就把$0$边时少了的$1$的答案补回来了

所以只要确定了$0$边的位置，就可以按照这个DP下去就行了

因为$n$比较小，所以可以直接枚举$0$边，然后记忆化搜索就能做到$O(n^2)$了

```cpp
#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
const int N=3010;
int tot;
ll f[N][N];
int fir[N],size[N][N],fa[N][N];
struct edge
{
	int to;
	int nxt;
}e[2*N];
inline void add(int x,int y)
{
	e[++tot].to=y; e[tot].nxt=fir[x]; fir[x]=tot;
	e[++tot].to=x; e[tot].nxt=fir[y]; fir[y]=tot;
}
inline void dfs(int rt,int p)
{
	size[rt][p]=1;
	for(int i=fir[p];i;i=e[i].nxt)
	{
		int q=e[i].to;
		if(q==fa[rt][p]) continue;
		fa[rt][q]=p;
		dfs(rt,q),size[rt][p]+=size[rt][q];
	}
}
inline ll cal(int p,int q)
{
	if(p==q) return 0;
	if(f[p][q]) return f[p][q];
	return f[p][q]=max(cal(fa[q][p],q),cal(p,fa[p][q]))+size[q][p]*size[p][q];
}
int main()
{
	int n,a,b; ll ans=0;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
	}
	for(int i=1;i<=n;i++) dfs(i,i);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			ans=max(ans,cal(i,j));
	printf("%lld\n",ans);
	return 0;
}
```


---

