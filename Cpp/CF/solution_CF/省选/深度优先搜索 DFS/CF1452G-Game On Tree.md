# Game On Tree

## 题目描述

### 题意描述

Alice 和 Bob 在玩一个游戏。他们有一棵由 $n$ 个结点组成的树。一开始，Bob 有 $k$ 个卡片，其中第 $i$ 个卡片位于结点 $a_i$（这些结点不重复）。在游戏开始之前，Alice 将在这棵树的一个结点上放置一个卡片。

这个游戏由一些回合组成。每个回合都将有以下事件发生（完全按照以下顺序）：
1. Alice 可以把她的卡片移到相邻的结点，或者不移动；
2. 对于 Bob 的每一张卡片，他可以把这张卡片移到相邻的结点，或者不移动。注意：每个卡片的选择都是独立的。

当 Alice 的卡片与 Bob 的任意一张（或多张）卡片在同一结点时，游戏结束。（Bob 自己的多张卡片可以置于同一结点上）  
Alice 希望游戏回合越多越好，Bob 则相反。  
如果某回合中间游戏结束（即 Alice 把卡片移到了有 Bob 卡片的结点上），这回合依然算入总回合数。\
对于每个结点，计算 Alice 一开始将卡片放在该结点时游戏将持续的回合数。

## 样例 #1

### 输入

```
5
2 4
3 1
3 4
3 5
2
4 5```

### 输出

```
2 1 2 0 0```

## 样例 #2

### 输入

```
8
4 1
8 4
4 5
6 4
2 5
4 3
1 7
3
2 8 3```

### 输出

```
3 0 0 3 1 2 3 0```

## 样例 #3

### 输入

```
10
2 5
4 3
7 3
7 2
5 8
3 6
8 10
7 9
7 1
4
10 6 9 1```

### 输出

```
0 2 2 2 2 0 2 2 0 0```

# 题解

## 作者：xzggzh1 (赞：5)

@duyi 巨佬的做法好麻烦啊，这里给出一个更容易的做法，代码难度，算法难度，和算法时间复杂度更加优秀。

---

题意：

$a$ 被 $b$ 的好多点在树上追（每回合 $a$ 先动，然后 $b$ 的所有点都单独动），$b$ 的点固定，问每一个 $a$ 的位置，$a$ 最多能保持多久不被追。

$n\leq 10^{5}$。

---

先考虑 $a$ 的逃跑路径，其中设 $dist[u]$ 表示 $u $ 到最近的 $b$ 的距离，$dis(a,b)$ 表示 $a,b$ 的距离。


考虑 $u$ 要到 $v$ 只有当 $dist[v]>dist[u] $ 时，最后的答案是$dist[v]$（跑到 $v$ 然后等死），前提是 $u \to v$ 时不被 $b$ 抓 。

反着思考，即 $u $ 可以让所有 $(dis(u,v)<dist[u])$ 的 $v$ 使 $ans[v]=\max(ans[v],dist[u])$，若只是朴素的用 $\rm bfs$ 来更新，时间肯定不够，所以我们考虑剪枝。

我们按 $dist[u]$ 降序排列，易知我们更新的时候不用取 $max$ 而是直接覆盖没被覆盖过的即可，为了避免额外的遍历，我们只需开一个数组 $now[u]$ 纪录当前遍历到 $u$ 的时候 $u$ 又去更新了与 $u$ 相距多少的节点。

注：这里这个 $now$ 比较难懂，下面放一个例子。

```
10
10 9
7 6
5 3
3 8
2 7
8 1
9 3
8 4
7 8
1
2

```

![](https://cdn.luogu.com.cn/upload/image_hosting/9x3os348.png)

当我们以 $10 $ 为 $u$ 来更新其他 $v$ 的 $ans[v]$ 时，这里的 $now[1]=1,now[8]=2,now[3]=3,now[10]=5……$

---

当我们$\rm bfs $ 到一个点时，若此时的 $u$ 给予下一个点的更新距离小于 原有的更新过的距离，那么就可以剪掉这个枝。

这部分的代码：

```cpp
for (int i = maxDist; i > 0; i--)
{
    for (auto u:P[i])//取出dist[u]=i的u 
    if (now[u]<dist[u])
    {
        if (!ans[u]) ans[u] = i;
        now[u]=i;
        Q.push({i, u});
    }
    while (!Q.empty())
    {
        int d = Q.front().first;
        int u = Q.front().second;
        Q.pop();
        if (--d==0)continue;
        for (auto v:E[u])
        {
            if (now[v] < d)
            {
                if (!ans[v]) ans[v] = i;
                now[v] = d;
                Q.push({d, v});
            }
        }
    }
}
```

复杂度总体来说是 $O(n\log n)$ 的，至少排序带一个 $\log $，后面部分也是 带$\log $的。

但后面部分复杂度证明我不太会，但是可以感性理解，比如说第一次 $u$ 离最近的 $b$ 那部分的 $now[v]$ 是不会被更新的，而 $u$ 并非随便取的，而是取相对所有 $b$ 最远。大概最终效果和启发式合并或者点分治差不多，真要严谨证明可以去看官方题解。








---

## 作者：b6e0_ (赞：4)

@[xzggzh1](/user/288460) 的[题解](/article/jxia1dmj)中提出了一种做法，并声称它的时间复杂度为 $O(n\log n)$，而本人给出了 $O(n^{\frac53})$ 的上界分析和 $\Theta(n^{\frac53})$ 的数据，所以实际上算法的最坏时间复杂度为 $\Theta(n^{\frac53})$。本文给出了我的分析和最坏情况下数据的构造。

说实话，这样一个看上去暴力而简洁的算法，复杂度是对的，并且能分析出 $\frac53$ 这种鬼东西，还是很神奇的。

将 xzggzh1 题解中的 $\text{now}$ 称为 $r$，我们尝试证明，每个点的 $r_i$ 最多变化 $O(n^{\frac23})$ 次，这样总时间复杂度就有 $O(\sum\deg_in^{\frac23})=O(n^{\frac53})$ 的上界。

以下将 Bob 的点称为黑点，黑点个数记为 $k$。

不妨分析 $r_1$ 的变化次数，将整颗树以 $1$ 为根。将点 $x$ 的深度记为 $d_x$，离点 $x$ 最近的黑点记为 $b_x$。在点 $x$ 开始 bfs 更新其他点时，令 $y=\text{LCA}(x,b_x)$，$r_1$ 将会变为 $\max(r_1,d_{b_x}-2d_y)$，并且显然 $b_y=b_x$，所以同一个 $y$ 最多只会对 $r_1$ 产生一次变化。称这里的点 $y$ 为“这次 bfs 的 $y$ 点”。

对于黑点 $x$，令 $f_x$ 为满足 $y$ 是 $x$ 的祖先且 $b_y=x$ 的 $d_y$ 最小的 $y$，称 $x$ 到 $f_x$ 为一条黑链，则树被分成了 $k$ 条不交的黑链，还有一些不属于任何黑链的点。

显然只有黑链上的点会成为一次 bfs 的 $y$ 点，并且同一条黑链上从浅到深的点对 $r_1$ 的贡献逐渐变小，所以想要一条黑链对 $r_1$ 产生多次变化，更深的点要比更浅的点先进行 bfs。

根据以上分析，如果想要一条黑链对 $r_1$ 产生 $t$ 次变化，最少额外添加的节点数是 $\Omega(t^2)$ 的。具体来说，记黑链顶部为 $x$，对于黑链上的点 $y(d_x<d_y\le d_x+t)$，在 $y$ 上面挂一条长度为 $d_y-d_x$ 的链，这样这条链的端点就有可能比 $y$ 的祖先（以及它们挂的链的端点）先 bfs 到，并且容易证明不存在点数更小的方案。

注意：我们正在进行的是上界分析，所以尽管挂的 $\Omega(t^2)$ 个点要满足一些别的限制，比如不能有别的黑点离它们更近，但是在 $r_1$ 的变化次数固定的情况下，加上这些限制只会让 $n$ 变大，换句话说，忽略它们分析出来的仍然是一个正确的上界。下面的分析中会忽略掉很多限制（只需要在构造卡满上界的数据的时候管它们，分析上界的时候不用管），不再一一说明。

考虑如果 $r_1$ 变化 $m$ 次至少需要多少个节点的树。我们将这 $m$ 次 bfs 按照 距离它们的起点最近的黑点 分类，这样我们只需要考虑对于一个黑点 $b$，它上面有 $t$ 次 bfs 对 $r_1$ 产生变化，半径分别为 $R_1\sim R_t$，$r_1$ 的值按顺序分别为 $a_1\sim a_t$，此时最小的节点数。

对于黑链上的点 $y$，$d_y$ 每增加 $1$，$y$ 对 $r_1$ 的贡献减小 $2$。设 $b$ 的黑链长度为 $l$，为了最小化黑链外的点数，我们不妨令 $b$ 上第一次 bfs 的点 $y$ 为黑链链顶，第 $i$ 次 bfs 的 $y$ 与链顶的距离为 $\frac{a_i-a_1}2$，这样对于第 $i$ 次 bfs，对应的点 $y$ 外面至少要挂 $R_i-l+\frac{a_i-a_1}2$，容易发现 $l$ 取 $R_1$ 时最优，则最小的节点数为：

$$R_1+\sum_{i=1}^tR_i-R_1+\frac{a_i-a_1}2$$

通过这个式子可以看出，在全部 $m$ 次变化的半径（记为 $R_1\sim R_m$）、值（记为 $a_1\sim a_m$）固定时，最优情况下，每个黑点分配到的变化是一段区间。

有了这个结论就好办了，我们可以抛弃更多的限制，进行进一步的简化。具体来说，因为有 $R_i\ge a_i\ge i$，不妨取 $R_i=\Theta(i),a_i=\Theta(i)$。记按时间顺序第 $i$ 个黑点分配到了 $x_i$ 个变化，记 $s_i$ 为 $x_i$ 的前缀和，则节点数有 $\Omega(\sum s_i+x_i^2)$ 的下界（$s_i$ 对应上面式子中的 $R_1$，$x_i^2$ 对应上面式子中的 $\sum R_i-R_1+\frac{a_i-a_1}2$）。于是，接下来我们要解决的问题是：在 $\sum x_i=m$ 的情况下求 $\sum s_i+x_i^2$ 的最小值。不妨允许 $x_i$ 取任意实数，这对渐进值没有影响。

考虑相邻两项 $x_i,x_{i+1}$，在其他数固定（这蕴含着 $x_i+x_{i+1}$ 固定）的情况下，它们如何取值使得式子最小。不妨令 $t=x_i+x_{i+1}$，则要最小化的式子为 $x_i^2+(t-x_i)^2+x_i$，求导或配方可得出最小值在 $x_i=\frac{2t-1}4$ 处取到，这意味着 $x_{i+1}-x_i=\frac14$ 是个常数，即 $\{x_i\}$ 为等差数列。

我们可以取 $x_i=i$，由于公差是常数，这不影响渐进值。此时 $x_i$ 有 $\Theta(\sqrt m)$ 项，$\sum s_i+x_i^2=\Theta(m\sqrt m)$。

$n=\Omega(m\sqrt m)$，即 $m=O(n^{\frac23})$，即 $r_1$ 最多变化 $O(n^{\frac23})$ 次。至此，时间复杂度的 $O(n^{\frac53})$ 上界得证。

关于 $\Theta(n^{\frac53})$ 的数据构造，具体阐述要画图，比较麻烦，所以这里放上生成器，代码应该挺清晰，对着它模拟一下就知道如何构造且为什么对了，大致思路和上界分析是一样的。原算法中没有任何数据结构，并且分析过程也能看出，原算法的常数很小，所以即使卡满的情况下通过这道题也是毫无压力的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,B,cnt=1,v[200005];
inline int add(int x,int l)
{
	while(l--)
	{
		printf("%d %d\n",x,++cnt);
		x=cnt;
	}
	return x;
}
int main()
{
	freopen("1.in","w",stdout);
	cin>>n;
	printf("%d\n",n);
	B=ceil(cbrt(n/9.));
	cerr<<"B: "<<B<<endl;
	for(int i=0;i<2*B*B;i++)
	{
		printf("%d %d\n",cnt,cnt+1);
		cnt++;
	}
	v[++*v]=cnt;
	for(int i=1+B*B-B;i>=1;i-=B)
	{
		int a=add(i,i-1),b=add(a,B*(i/B)+2);
		v[++*v]=add(b,B*(i/B)+2+2*B*B);
		for(int j=1;j<=B-5;j++)
			add(b+j,j*2);
	}
	for(int i=cnt+1;i<=n;i++)
		printf("1 %d\n",i);
	printf("%d\n",*v);
	for(int i=1;i<=*v;i++)
		printf("%d ",v[i]);
	putchar('\n');
	return 0;
}
```

---

## 作者：duyi (赞：2)

[噜啦噜啦咧噜啦噜啦咧的阅读体验~芜湖~~~](https://www.cnblogs.com/dysyn1314/p/14038709.html)

# CF1452G Game On Tree

## 题目大意

[题目链接](https://codeforces.com/contest/1452/problem/G)

Alice 和 Bob 在玩一个游戏。他们有一棵由 $n$ 个结点组成的树。一开始，Bob 有 $k$ 个卡片，其中第 $i$ 个卡片位于结点 $a_i$（注意：所有的结点都是唯一的）。在游戏开始之前，Alice 将在这棵树的一个结点上放置一个卡片。

这个游戏由一些回合组成。每个回合都将有以下事件发生（完全按照以下顺序）：

1. Alice 可以把她的卡片移到相邻的结点，或者不移动；
2. 对于 Bob 的每一张卡片，他可以把这张卡片移到相邻的结点，或者不移动。注意：每个卡片的选择都是独立的。

当 Alice 的卡片与 Bob 的任意一张（或多张）卡片在同一结点时，游戏结束。（Bob自己的多张卡片可以置于同一结点上，即使它们的初始位置一定是不同的）。

Alice希望游戏回合越多越好，Bob则相反。如果某回合中间游戏结束（即 Alice 把卡片移到了有 Bob 卡片的结点上），这回合依然算入总回合数。

对于每个结点，计算 Alice 一开始将卡片放在该结点时游戏将持续的回合数。

数据范围：$2\leq n\leq 2\times 10^5$，$1\leq k < n$。

## 本题题解

设树上两点 $u,v$ 间的距离为 $\text{dis}(u,v)$。

考虑对某个 Alice 的起点 $a$ 求答案。先把 $a$ 提作树根。

设 Bob 的所有起点中，离 $u$ 最近的点与 $u$ 的距离为 $\text{disBob}(u)$。

考虑 Bob 的移动策略，显然他一定让所有点同时向当前 Alice 所在的位置走。

与此同时 Alice 要避免被 Bob 追到，她会向她能到达的点里，$\text{disBob}(u)$ 最大的点走。“她能到达的点”指的是在 Alice 从起点 $a$ 走到这个点的过程中，不会被 Bob 逮到。具体来说，一个点 $u$ 是“能到达的”，当且仅当 $\text{dis}(a,u)\leq\text{disBob}(u)$ 且对于 $a$ 到 $u$ 路径上除 $u$ 外所有点 $v$，$\text{dis}(a,v) < \text{disBob}(v)$。

对所有点 $u\in[1,n]$ 预处理出 $\text{disBob}(u)$，可以通过树形 DP + 换根预处理，时间复杂度 $O(n)$。

然后对每个 $a$ 求答案，只需要从 $a$ 出发 dfs 一遍，求出所有“能到达的点” $u$ 的 $\text{disBob}(u)$ 的最大值。总时间复杂度 $O(n^2)$。无法通过本题。

考虑优化上述过程。将点按 $\text{disBob}(u)$ 从小到大排成一个序列 $p_1,p_2,\dots,p_n$（$p$ 是一个 $1\dots n$ 的排列且 $\text{disBob}(p_1)\leq \text{disBob}(p_2)\leq \dots\leq \text{disBob}(p_n)$。对每个点 $a$，在这个序列上二分答案。问题转化为求 $p_{\text{mid}+1},\dots ,p_{r}$ 中，是否存在点 $p_i$ 是 $a$ “能到达”的。

单独二分似乎难以操作。我们对所有 $a$ 整体二分。具体来说，我们定义一个递归的函数 $\text{solve}(Q,l,r)$ 表示 $Q$ 集合里的这些 $a$，答案都在 $l,r$ 之间。若 $l=r$，则直接记下答案，然后返回。否则设 $\text{mid} = \lfloor\frac{l+r}{2}\rfloor$。我们对 $Q$ 集合里的所有 $a$，判断：集合 $P = \{p_{\text{mid}+1},\dots,p_{r}\}$ 中，是否存在点 $p_i$ 是 $a$ “能到达”的。

要一次性判断所有 $a$，可以对 $Q\cup P$ 这些点，建出虚树。然后做树形 DP。设 $f(u)$ 表示 $u$ 子树里所有 $P$ 集合里的点 $v$ 中，$\text{dis}(v,u) - \text{disBob}(v)$ 的最小值。

对于根节点 $\text{root}$，如果 $f(\text{root}) < 0$，则 $\text{root}$ 的答案在 $[\text{mid}+1,r]$ 中；如果 $f(\text{root}) > 0$ 则它的答案在 $[l,\text{mid}]$ 中。换根后，即可对所有点分别做出这样的判断。然后将 $Q$ 划分为两个集合 $Q_L,Q_R$，分别递归调用：$\text{solve}(Q_L,l,\text{mid})$，$\text{solve}(Q_R,\text{mid} + 1, r)$ 即可。

需要注意的是，$f(\text{root}) = 0$ 的情况是比较特殊的。它能放在 $Q_R$，当且仅当存在一个点 $u\in P$，满足 $\text{dis}(u,\text{root}) = \text{disBob}(u)$，且 $u$ 向 $\text{root}$ 方向的儿子子树里（也就是以 $\text{root}$ 为根时，$u$ 子树以外的所有点），不存在一个 Bob 的起点 $b$ 使得 $\text{dis}(b,u) = \text{disBob}(u)$。这也可以通过做一个类似的树形 DP：只要 $u$ 的子树外，存在到 $u$ 距离等于 $\text{disBob}(u)$ 的 Bob 的起点，我们就不让 $u$ 对父亲的 DP 值产生贡献（假装 $u$ 不在 $P$ 集合里）。然后再换根一次即可。

发现在递归的过程中，每个节点只会递归 $O(\log n)$ 层（因为是个二分），每层里要建虚树，所以总时间复杂度 $O(n\log^2n)$。

## 参考代码


[勇敢向前进，前进有奖品！！！](https://www.cnblogs.com/dysyn1314/p/14038709.html)

---

## 作者：ppip (赞：1)

点分治做法。

Alice 在每个点的最终路径一定是不停顿的走到一个点然后停下来等。此时答案就是该点被 Bob 碰到的最短时间。考虑哪些最终点会产生贡献。

令 $f_u$ 为 Bob 走到 $u$ 的最短时间。注意到 $u$ 能走到 $v$ 当且仅当 $dis(u,v)<f_v$。所以可以认为每个点 $v$ 对到自己距离 $<f_v$ 的点贡献 $f_v$ 的答案。

这是个邻域取 $\max$ 的操作，可以直接用点分治维护。复杂度为 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int Spp{1<<20};
char buf[Spp],*p1,*p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,Spp,stdin),p1==p2)?EOF:*p1++)
template <typename T>
void read(T &x) {
	char c;int f{1};
	do x=(c=getchar())^48;
	while (!isdigit(c)&&c!='-');
	if (x==29) f=-1,x=0;
	while (isdigit(c=getchar()))
		x=(x<<3)+(x<<1)+(c^48);
	x*=f;
}
template <typename T,typename ...Args>
void read(T& x,Args&... args) {read(x);read(args...);}
constexpr int N(2e5);
int f[N+5];
vector<int> e[N+5];
void init(int u,int fa) {
	for (auto v:e[u])
		if (v!=fa) {
			init(v,u);
			f[u]=min(f[u],f[v]+1);
		}
}
void init2(int u,int fa) {
	f[u]=min(f[u],f[fa]+1);
	for (auto v:e[u])
		if (v!=fa) init2(v,u);
}
int sz[N+5],son[N+5];
bool vis[N+5];
int g,qwq;
void findg(int u,int fa) {
	sz[u]=1;son[u]=0;
	for (auto v:e[u])
		if (!vis[v]&&v!=fa) {
			findg(v,u);
			sz[u]+=sz[v];
			son[u]=max(son[u],sz[v]);
		}
	son[u]=max(son[u],qwq-sz[u]);
	if (son[u]<son[g]) g=u;
}
int c[N+5],ans[N+5];
void add(int u,int fa,int dis) {
	if (dis<f[u]) c[min(qwq,f[u]-dis-1)]=max(c[min(qwq,f[u]-dis-1)],f[u]);
	for (auto v:e[u])
		if (v!=fa&&!vis[v])
			add(v,u,dis+1);
}
void give(int u,int fa,int dis) {
	ans[u]=max(ans[u],c[dis]);
	for (auto v:e[u])
		if (v!=fa&&!vis[v])
			give(v,u,dis+1);
}
void solve(int u,int n) {
	g=0;qwq=n;findg(u,0);
	u=g;
	for (int i{0};i<=n;++i) c[i]=0;
	add(u,0,0);
	for (int i{n-1};i>=0;--i) c[i]=max(c[i],c[i+1]);
	give(u,0,0);
	vis[u]=true;
	for (auto v:e[u])
		if (!vis[v]) solve(v,n-son[v]);
}
int main() {
	int n;read(n);
	memset(f,0x3f,sizeof f);
	for (int i{1};i<n;++i) {
		int u,v;read(u,v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	int k;read(k);
	while (k--) {
		int x;read(x);
		f[x]=0;
	}
	init(1,0);init2(1,0);
	son[0]=n;solve(1,n);
	for (int i{1};i<=n;++i) cout<<(f[i]==0?f[i]:ans[i])<<" ";
	cout<<endl;
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

记录我思考的过程，。

先考虑 Bob 的策略。显然，他只会让自己的卡片**朝向 Alice 的卡片移动**，而且一定会这么做。

Alice 的策略为：选定一条链 $u \to v$，将卡片放在 $u$ 上。先不断向 $v$ 移动。到达 $v$ 之后，她会选择停在 $v$ 不动，等着 Bob 来。

这样需要满足：

1. 对于链上任何一点 $w$ 和任何一个 Bob 起始点 $s$，都有 $\text{dis}(u,w) < \text{dis}(s,w)$；
2. 最大化 $\min_i \text{dis}(s_i,v)$。

显然对于每个 $v$，都可以算出 $t_v=\min_{i} \text{dis}(s_i,v)$ 的值。

那么问题转化为：给定 $u$，找到满足下列要求的 $v$ 对应的 $t_v$ 的最大值——$u$ 到 $v$ 路径上所有点 $p$ 的 $t_p$ 都大于 $\text{dis}(u,p)$。 

-------

关键性质：下面证明，路径 $(u,v)$ 上任何一个点 $p$ 满足 $t_p > \text{dis}(u,p)$，等价于 $t_v > \text{dis}(u,v)$。其实是显然的，因为我们将 $p$ 从 $u$ 往 $v$ 移动时，$t_v$ 最多增加 $1$，而 $\text{dis}(u,v)$ 会减少 $1$，即 $t_v - \text{dis}(u,v)$ 在减小。这样已经可以用一些分块乱做了，能做到 $O(n \sqrt{n \log n})$，不清楚能不能过。

大规模点对统计考虑点分治。每个点显然会对 $dep_u \le k$ 的所有点产生贡献（不在同一子树内毫无影响，这样会更劣）。直接前缀和即可，复杂度 $O(n \log n)$。

这是代码：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,k,flg[MAXN],t[MAXN],ans[MAXN],din[MAXN],dout[MAXN],pre[MAXN];
vector<int> G[MAXN];
void dfs1(int u,int f) {for(auto v:G[u]) if(v!=f) dfs1(v,u),din[u]=min(din[u],din[v]+1);return ;}
void dfs2(int u,int f) {for(auto v:G[u]) if(v!=f) dout[v]=min(din[u],dout[u])+1,dfs2(v,u);return ;}
int cut[MAXN],dep[MAXN],sze[MAXN],mx[MAXN],mdep;
void dfs(int u,int f) {
	sze[u]=1,mx[u]=0;
	for(auto v:G[u]) if(v!=f&&!cut[v]) dfs(v,u),sze[u]+=sze[v],mx[u]=max(mx[u],sze[v]);
	return ;	
}
int find_core(int u,int f,int al) {
	if(max(mx[u],al-sze[u])<=al/2) return u;
	for(auto v:G[u]) if(v!=f&&!cut[v]) {
		int ans=find_core(v,u,al);
		if(ans!=-1) return ans;
	}
	return -1;
}
void get_dep(int u,int f,int& md) {
	if(f) dep[u]=dep[f]+1;
	else dep[u]=0;
	md=max(md,dep[u]+1);
	for(auto v:G[u]) if(v!=f&&!cut[v]) get_dep(v,u,md);
	return ;	
}
void add_imp(int u,int f) {
	if(t[u]-dep[u]-1>=0) pre[min(mdep,t[u]-dep[u]-1)]=max(pre[min(mdep,t[u]-dep[u]-1)],t[u]);
	for(auto v:G[u]) if(v!=f&&!cut[v]) add_imp(v,u);
	return ;
}
void add_ans(int u,int f) {
	ans[u]=max(ans[u],pre[dep[u]]);
	for(auto v:G[u]) if(v!=f&&!cut[v]) add_ans(v,u);
	return ;	
}
void solve(int u) {
	dfs(u,0),u=find_core(u,0,sze[u]);
	mdep=0,get_dep(u,0,mdep);
	ffor(i,0,mdep) pre[i]=-0x3f3f3f3f3f3f3f3f;
	add_imp(u,0);roff(i,mdep-1,0) pre[i]=max(pre[i],pre[i+1]);add_ans(u,0);
	cut[u]=1;for(auto v:G[u]) if(!cut[v]) solve(v);
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n-1) {int u,v;cin>>u>>v,G[u].push_back(v),G[v].push_back(u);}
	cin>>k;
	memset(din,0x3f,sizeof(din)),memset(dout,0x3f,sizeof(dout));
	ffor(i,1,k) {int id;cin>>id,flg[id]=1,din[id]=dout[id]=0;}
	dfs1(1,0),dfs2(1,0);
	ffor(i,1,n) t[i]=min(din[i],dout[i]);
	solve(1);
	ffor(i,1,n) cout<<ans[i]<<' ';
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

首先感觉起来好像可以把整个树按照 $k$ 个点划分成连通块，每个连通块里的点都可以跑到这个连通块中距离 $k$ 个点距离最大的点，这也是他能存活的轮数。

然而这是错的，因为对方可以在半路拦截，同时该点也无法去到很远的点。

考虑换一个思路，当我们枚举出路径上的一个点时，我们可以从该点向起始点 dfs，判断起始点是否可达这个点，然后向终止点 dfs，判断想要到达终止点，那么到达这个路径上的点的时间最晚是多少。

然而我们希望对于所有路径都求出来这个的答案。点分治恰好能树上高效覆盖所有路径。考虑将原树点分，每次从根 dfs 求出每个点是否能到达根，再求出想要到每个点从根出发的时间至少是多少，使用双指针统计即可。

总复杂度 $O(n\log^2n)$，瓶颈在于点分治中的排序。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
vector<int> vc[200005]; 
int f[200005],siz[200005],totsiz,minv,rt,vis[200005],ans[200005];
void getsiz(int now,int fa){
	siz[now]=1;
	for(auto v:vc[now]){
		if(v==fa||vis[v]) continue;
		getsiz(v,now);
		siz[now]+=siz[v];
	}
}
void findrt(int now,int fa){
	int maxv=0;
	for(auto v:vc[now]){
		if(v==fa||vis[v]) continue;
		findrt(v,now);
		maxv=max(maxv,siz[v]);
	}
	maxv=max(maxv,totsiz-siz[now]);
	if(maxv<minv){
		minv=maxv;
		rt=now;
	}
}
vector<pair<int,int>> to;
vector<pair<int,int>> frm;
void addto(int now,int fa,int dist,int dep){
	if(f[now]<=dep) return ;
	dist=min(dist,f[now]-dep);
	to.push_back(make_pair(dist-1,now));
	for(auto v:vc[now]){
		if(vis[v]||v==fa) continue;
		addto(v,now,dist,dep+1);
	}
}
void addfrm(int now,int fa,int dist,int dep){
	dist=min(dist,f[now]-1);
	frm.push_back(make_pair(dep,now));
	if(dist==0) return ;
	for(auto v:vc[now]){
		if(vis[v]||v==fa) continue;
		addfrm(v,now,dist-1,dep+1);
	}
}
void dvq(int now){
	if(f[now]!=0){
		to.clear();
		frm.clear();
		addto(now,0,f[now],0);
		addfrm(now,0,f[now]-1,0);
		sort(to.begin(),to.end()),reverse(to.begin(),to.end());
		sort(frm.begin(),frm.end()),reverse(frm.begin(),frm.end());
		int it=0,tmpans=0;
		for(int i=0;i<to.size();i++){
			auto v=to[i];
			while(it!=frm.size()&&frm[it].first>v.first){
				ans[frm[it].second]=max(ans[frm[it].second],tmpans);
				it++;
			}
			tmpans=max(tmpans,f[v.second]);
		}
		while(it!=frm.size()){
			ans[frm[it].second]=max(ans[frm[it].second],tmpans);
			it++;
		}
	}
	vis[now]=1;
	for(auto v:vc[now]){
		if(vis[v]) continue;
		getsiz(v,now);
		totsiz=siz[v],minv=1e18;
		findrt(v,now);
		dvq(rt);
	}
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	int n; cin>>n;
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	memset(f,-1,sizeof(f));
	int k; cin>>k;
	queue<int> q;
	for(int j=1;j<=k;j++){
		int x; cin>>x; f[x]=0; q.push(x);
	}
	while(!q.empty()){
		int t=q.front(); q.pop();
		for(auto v:vc[t]){
			if(f[v]==-1){
				f[v]=f[t]+1;
				q.push(v);
			} 
		}
	}
	getsiz(1,0);
	totsiz=siz[1],minv=1e18;
	findrt(1,0);
	dvq(rt); 
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	return 0;
}
```

---

