# The Game (Hard Version)

## 题目描述

这是该问题的困难版本。与简单版本的区别在于，此版本需要找到 Cirno 在第一轮可能选择的所有节点。仅当解决所有版本的问题时方可进行 hack。

Cirno 和 Daiyousei 正在玩一个以节点 $1$ 为根的 $n$ 节点树 $^{\text{∗}}$ 游戏，其中第 $i$ 个节点的权值为 $w_i$。她们轮流行动，Cirno 先手。

每一轮中，假设对手在上轮选择了节点 $j$，当前玩家必须选择一个未被删除的节点 $i$ 满足 $w_i > w_j$，并删除节点 $i$ 的子树 $^{\text{†}}$。特别地，在第一轮中 Cirno 可以选择任意节点并删除其子树。

无法操作的玩家获胜，双方都希望自己获胜。请找出 Cirno 在第一轮可能选择的所有节点，使得在双方都采取最优策略时她能获胜。

$^{\text{∗}}$ 树是一个无环的连通图。

$^{\text{†}}$ 若从根节点 $1$ 到节点 $u$ 的所有路径都必须经过节点 $i$，则称节点 $u$ 属于节点 $i$ 的子树。

## 说明/提示

第一个测试用例：
1. 若 Cirno 在第一轮选择节点 $1$ 或 $3$，Daiyousei 无法操作，因此 Daiyousei 获胜。
2. 若 Cirno 在第一轮选择节点 $2$ 或 $4$，Daiyousei 只能选择节点 $3$，操作后 Cirno 无法行动，因此 Cirno 获胜。

因此 Cirno 可能选择的节点为 $2$ 和 $4$。

第二个测试用例中，无论 Cirno 选择哪个节点，Daiyousei 都无法操作，因此 Daiyousei 获胜。

第三和第四个测试用例中，Cirno 唯一可能选择的节点是 $2$。

第五个测试用例中，Cirno 可能选择的节点为 $3,4,6,7$ 和 $10$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
4
2 2 4 3
1 2
1 3
2 4
5
1 2 3 4 5
1 2
2 3
3 4
4 5
3
1 2 3
1 2
1 3
5
3 1 3 4 5
1 2
2 3
3 4
4 5
10
1 2 3 2 4 3 3 4 4 3
1 4
4 6
7 4
6 9
6 5
7 8
1 2
2 3
2 10```

### 输出

```
2 2 4
0
1 2
1 2
5 3 4 6 7 10```

# 题解

## 作者：_abcd_ (赞：4)

## [[CF2062E2] The Game (Hard Version)](https://codeforces.com/problemset/problem/2062/E2)

$ \rm E1 $ 的简单扩展，但是赛时在 $ \rm F $ 上唐了一个多小时导致最后遗憾离场。

再阅读这篇题解前，请保证你已经会 $ \rm E1 $ 的解法，否则可以移步至 [这里](https://www.luogu.com.cn/article/u1cq5304)。

假设你第一步删除了 $ x $，然后对手按照 $ \rm E1 $ 的做法找到了比 $ x $ 权值大的且先手必胜的点 $ y $，那你就炸了。因此我们需要保证：再删除 $ x $ 后，所有权值比 $ x $ 大的 $ y $，要么 $ y $ 在 $ x $ 的子树内，要么所有权值比 $ y $ 大的且不在 $ y $ 子树内的点 $ z $ 都在 $ x $ 的子树内。

那么当扫到 $ y $ 时，只需要找到所有 $ z $ 的 $ \rm LCA $，设为点 $ a $。那么 $ x $ 要么是 $ y $ 的祖先，要么是 $ a $ 的祖先。可以再用一个 $ \rm BIT $ 来判断这个条件。

关于如何找到 $ a $，只需要用一个 $ \rm set $ 维护所有权值比 $ y $ 大的点的 $ \rm dfs $ 序，然后找到不在 $ y $ 的子树内的 $ \rm dfs $ 序最小的点 $ l $ 和最大的点 $ r $，则 $ a $ 就是 $ l $ 和 $ r $ 的 $ \rm LCA $。

最后复杂度是 $ O(n \log n) $。

---

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pn putchar('\n')
#define mset(a,x) memset(a,x,sizeof a)
#define mcpy(a,b) memcpy(a,b,sizeof a)
#define all(a) a.begin(),a.end()
#define fls() fflush(stdout)
using namespace std;
int re()
{
    int x=0;
    bool t=1;
    char ch=getchar();
    while(ch>'9'||ch<'0')
        t=ch=='-'?0:t,ch=getchar();
    while(ch>='0'&&ch<='9')
        x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return t?x:-x;
}
const int maxn=1e6+5;
int n,m;
int dep[maxn];
int id[maxn],rid[maxn];
vector<int>a[maxn];
vector<int>e[maxn];
vector<int>ans;
set<int>b;
struct BIT
{
    int tree[maxn];
    void add(int x,int ad)
    {
        for(int i=x;i<=m;i+=i&-i)
            tree[i]+=ad;
    }
    int qry(int x)
    {
        int ret=0;
        for(int i=x;i;i-=i&-i)
            ret+=tree[i];
        return ret;
    }
    int qry(int l,int r)
    {
        return qry(r)-qry(l-1);
    }
}bit1,bit2;
int st[20][maxn];
int min2(int u,int v)
{
    return dep[u]<dep[v]?u:v;
}
int lca(int l,int r)
{
    if(!l||!r)
        return st[0][l|r];
    if(l>r)
        swap(l,r);
    int k=__lg(r-l+1);
    return min2(st[k][l],st[k][r-(1<<k)+1]);
}
void dfs(int pos,int fa)
{
    m++;
    id[pos]=m;
    st[0][m]=pos;
    for(int v:e[pos])
    {
        if(v==fa)
            continue;
        dep[v]=dep[pos]+1;
        dfs(v,pos);
        m++;
        st[0][m]=pos;
    }
    rid[pos]=m;
}
void solve()
{
    n=re();
    for(int i=1;i<=n;i++)
    {
        a[i].clear();
        e[i].clear();
    }
    for(int i=1;i<=n;i++)
        a[re()].push_back(i);
    for(int i=1;i<n;i++)
    {
        int u=re(),v=re();
        e[u].push_back(v);
        e[v].push_back(u);
    }
    m=0;
    dfs(1,0);
    for(int j=1;j<=19;j++)
    {
        for(int i=1;i+(1<<j)-1<=m;i++)
            st[j][i]=min2(st[j-1][i],st[j-1][i+(1<<j-1)]);
    }
    for(int i=1;i<=m;i++)
        bit1.tree[i]=bit2.tree[i]=0;
    int cnt1=0,cnt2=0;
    b.clear();
    ans.clear();
    for(int k=n;k;k--)
    {
        for(int i:a[k])
        {
            if(bit1.qry(id[i],rid[i])<cnt1&&bit2.qry(id[i],rid[i])==cnt2)
                ans.push_back(i);
        }
        for(int i:a[k])
        {
            if(bit1.qry(id[i],rid[i])<cnt1)
            {
                auto l=b.lower_bound(id[i]),r=b.lower_bound(rid[i]);
                int t1=0,t2=0;
                if(l!=b.begin())
                {
                    l--;
                    t1=lca(*b.begin(),*l);
                }
                if(r!=b.end())
                    t2=lca(*r,*b.rbegin());
                int t=lca(id[t1],id[t2]);
                bit2.add(id[t],1);
                bit2.add(id[i],1);
                bit2.add(id[lca(id[t],id[i])],-1);
                cnt2++;
            }
        }
        for(int i:a[k])
        {
            cnt1++;
            b.insert(id[i]);
            bit1.add(id[i],1);
        }
    }
    sort(all(ans));
    printf("%d ",ans.size());
    for(int i:ans)
        printf("%d ",i);
    pn;
}
signed main()
{
    int T=re();
    while(T--)
        solve();
    return 0;
}
```

---

## 作者：Purslane (赞：3)

# Solution

我觉得 E1 和 E2 差不多难啊，为啥一个是绿一个是紫。

考虑判定什么时候先手必输。显然，先手不能选择最大值点，这样后手一定输。

如果存在一个次大值点使得它不包含所有的最大值点，那么也可以直接选择它，这样后手被迫选择最大值点，先手赢。

否则，所有次大值点构成祖孙关系，且最深的那个点的子树内包含所有的最大值点。

然后考虑第三大值。如果存在一个第三大值点，子树内没有包含所有的次大和最大值点，那么选择它，后手必定只能选择次大值或最大值点——这样先手下一步无法操作，胜出。

因此从大到小扫描，找到第一个没有包含所有比他大的节点即可。

[这是 E1。](https://codeforces.com/contest/2062/submission/303105793)

对于 E2 来说，我们要确定删掉哪个节点之后转为先手必输。这里删节点指的是，只保留权值比该节点大的点，且将这个点的子树删除。这样后手的操作和先手的操作完全无关，可以使用 E1 的方法进行判定。

我们得到了 $O(n^2 \log n)$ 的做法（如果使用 DFS 序就是 $O(n^2)$ 的了），考虑优化。

给先手必败态找一个好看的充要条件——

1. 删掉这个点之后，只剩若干权值相同的点。这样后手只能被迫选择“最大值”。
2. 删掉这个点之后，其他点构成一个“扫帚”——每个点都包含权值比他大的所有点。

我们首先要求出，**权值最大的、不全在 $u$ 子树内的点的权值**。这个可以二分求出。

对于条件 $1$，我们只需要用树状数组和静态二分求出剩下点的个数以及剩下权值最大点的个数，如果相等显然满足要求。

然后再给“扫帚”一个等价条件。显然，$u$ 子树必须包含所有**存在祖先权值比他大的点**；其次，我们可以找到权值最大的、不在 $u$ 子树内的点中 DFS 序最小的那一个，它的第一个祖先必定是扫帚杆的“末端”。找到末端，我们可以利用“点数 = 杆（链）的长度”进行判断。

我选择使用树上倍增求扫帚的末端。

代码略显复杂，但是场上调出来了。

[这是 E2。](https://codeforces.com/contest/2062/submission/303129609)

---

## 作者：Petit_Souris (赞：2)

感觉这题很难，就是不知道为什么不会做。接着点开题解看第一句话，发现先手必胜 = 后手没有合法策略，于是就会做了。原来一个常识性结论 = *2000 -> *3000，绷不住了。

先做 E1。想要简单解决问题显然是一步杀，也就是选一个点 $u$，满足下一步选的 $v$ 都没法继续拓展。

我们发现直接选所有存在可以转移的 $v$ 的所有 $u$ 中，$a_u$ 最大的一个就行了，因为如果 $v$ 还能转移我们就会选 $v$ 了。如果不存在这样的点就必败。显然只需要处理出 dfs 序前后缀最大值，容易做到 $\mathcal O(n)$。（说起来也真是神人了，E1 题解区全是 $\mathcal O(n\log n)$）

接下来考虑 E2。**最难的一步：一个点 $u$ 先手必胜，等价于删掉 $u$ 子树之后先手必败，即对剩下的树做 E1，得到的答案 $=0$。** 我也不明白为什么就是没想到这件事情。

接下来就是幼儿园级别的数据结构题了。我们相当于要维护每个 $u$ 是否存在一个二元组 $(v,w)$，使得 $v$ 不在 $u$ 子树内，$w$ 不在 $u,v$ 子树内，且 $a_u<a_v<a_w$。

按照值域倒过来做扫描线，扫到一个点的时候处理以这个点为 $v$ 的 $(v,w)$，相当于所有 $a_w>a_v$ 的 $w$，不在 $v$ 子树内的部分至少得取到一个。也就是说，能贡献到的 $u$ 就是整棵树，扣掉所有 $w$ 的 LCA 以及祖先的部分，以及 $v$ 的祖先的部分。LCA 可以通过区间查询 dfs 序最小最大点来时限，贡献到 $u$ 可以把链并拆掉，变成路径加单点查询。

最后查询到 $u$ 的时候还必须满足 $u$ 至少能跳到一个点，和 E1 一样额外判断一下就好了。

时间复杂度 $\mathcal O(n\log n)$。

---

## 作者：masonpop (赞：2)

参考 official editorial。不明白为啥有人喷官解，感觉挺清晰的啊。

先考虑如何通过 E1。

首先，先手选的点 $u$ 必须满足，其子树外存在点 $v$ 使得 $w_v>w_u$，称这样的 $u$ 是好点。那么当一个人选中坏点时显然就输了。于是先手直接选 $w$ 最大的好点即可强制让后手选中坏点，从而胜利。具体的在 dfs 序上维护一个前缀后缀 $\max$ 即可。

对于 E2，稍加分析可以得出，先手要获胜必须是两步杀，即删去点 $u$ 后，剩余的点全部是坏点，否则后手直接采取 E1 中先手的策略即可获胜。枚举后手的决策点 $v$，则条件等价于，对所有满足 $w_x>w_v$ 的点 $x$，$x$ 必须在 $u$ 或 $v$ 的子树中（即已被删去）。分离一下两种可能，设 $g(v)$ 表示 **$v$ 子树外所有值大于 $w_v$ 的点的 LCA**。那么条件即等价于 $u$ 是 $g(v)$ 的祖先。

当然还需要满足 $v$ 是可以选取的，综合一下即可得出 $u$ 合法的条件：对所有 $w_v>w_u$ 的点 $v$，要么 $v$ 在 $u$ 的子树内，要么 $g(v)$ 在 $u$ 的子树内。

接下来的东西都非常套路，没啥难点。

先考虑如何处理 $g$。把点按 $w$ 从大到小加入后就相当于查询区间 LCA，使用线段树维护即可。然后对于求解答案，相当于要做的事情是对两个点到根的路径并上的点 $+1$。树上差分一下，拿个树状数组维护子树和即可。

使用 $O(n\log n)-O(1)$ LCA 即可做到单 log。

代码比较长但是没啥细节，不放了。

---

## 作者：喵仔牛奶 (赞：2)

这个题真的太困难了，我 E1 都不会。/ll

## Solution

考虑 E1 怎么做。记子树外不存在 $j$ 使得 $w_j>w_i$ 的点 $i$ 是坏点，反之为好点。可以发现取坏点的人就输了，先手取 $w_i$ 最大的好点可以是后手必取坏点，输出这个点即可。

考虑 E2。根据 E1，如果先手操作完后还有好点，后手模仿 E1 中先手的策略，先手就输了。所以我们需要保证取完后后手不能取好点。考虑取了 $x$ 后，满足以下三条中至少一条的好点 $y$ 不能再被取：
1. $w_y\le w_x$。
1. $y$ 在 $x$ 子树内。
1. 所有 $y$ 子树外满足 $w_z>w_y$ 的 $z$ 在 $x$ 子树内。

因此 $x$ 只收到 $w_y>w_x$ 的 $y$ 的约束。按 $w_y$ 从大到小枚举**好点** $y$，设所有 $y$ 子树外满足 $w_z>w_y$ 的 $z$ 的 LCA 为 $p$，满足第二、三条的 $x$ 分别在 $y\to 1$ 和 $p\to 1$ 的路径上，故所有 $y\to 1$ 和 $p\to 1$ 路径外的点先手不能取，打上不合法标签。

同步枚举 $x$，如果枚举到 $x$ 时它没有不合法标签，且 $x$ 是好点，那么先手可以取 $x$。注意相同权值的要一起枚举。

具体实现的时候，可以给 $y\to 1$ 和 $p\to 1$ 加一，$\text{lca}(y,p)\to 1$ 减一，没有不合法标签就是 $x$ 的权值等于加的次数。关于求 LCA，子树的 dfs 序是区间，可以使用 set 维护当前加入的点的 dfs 序，取出子树外 dfs 序最大最小的求 LCA 即可。

## Code

```cpp
namespace Milkcat {
	using namespace DS;
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5;
	int n, x, y, ct, tot, w[N], dfn[N], ot[N], id[N], pr[N], sf[N], st[20][N];
	vector<int> rs, G[N], s[N]; set<int> t; fenwick<int> fw;
	void dfs(int x, int fa) {
		dfn[x] = ++ tot, id[tot] = x, st[0][tot] = dfn[fa];
		for (int y : G[x]) if (y != fa) dfs(y, x);	
		ot[x] = tot;
	}
	int lca(int x, int y) {
		if (!x || !y || x == y) return x | y;
		if ((x = dfn[x]) > (y = dfn[y])) swap(x, y);
		int d = __lg(y - x ++);
		return id[min(st[d][x], st[d][y - (1 << d) + 1])];
	}
	int main() {
		cin >> n, tot = ct = sf[n + 1] = 0; 
		REP(i, 1, n) cin >> w[i], s[w[i]].pb(i);
		REP(i, 2, n) cin >> x >> y, G[x].pb(y), G[y].pb(x);
		dfs(1, 0);
		REP(i, 1, __lg(n)) REP(j, 1, n - (1 << i) + 1)
			st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
		REP(i, 1, n) pr[i] = max(pr[i - 1], w[id[i]]);
		DEP(i, n, 1) sf[i] = max(sf[i + 1], w[id[i]]);
		t.clear(), fw.clear(), fw.resize(n), rs.clear();
		DEP(i, n, 1) {
			for (int x : s[i]) {
				if (fw.ask(ot[x]) - fw.ask(dfn[x] - 1) != ct) continue;
				if (max(pr[dfn[x] - 1], sf[ot[x] + 1]) <= i) continue;
				rs.pb(x);
			}
			for (int x : s[i]) {
				int p = 0;
				auto itl = t.lower_bound(dfn[x]), itr = t.upper_bound(ot[x]);
				if (itl != t.begin()) p = lca(p, lca(id[*t.begin()], id[*prev(itl)]));
				if (itr != t.end()) p = lca(p, lca(id[*t.rbegin()], id[*itr]));
				if (p > 0) {
					fw.upd(dfn[x], 1), fw.upd(dfn[p], 1);
					fw.upd(dfn[lca(x, p)], -1), ct ++;
				}
			}
			for (int x : s[i]) t.insert(dfn[x]);
		}
		sort(ALL(rs));
		cout << SZ(rs) << ' ';
		for (int x : rs) cout << x << ' ';
		cout << '\n';
		REP(i, 1, n) G[i].clear(), s[i].clear();
		return 0;
	}
}
```

---

## 作者：Chenhaoxuan (赞：1)

给一种题解区没有的 **不用考虑 LCA 的单 log 做法**。

---

定义一个点 $x$ 是“好的”，当且仅当至少存在一个 $x$ 子树外的点 $y$，满足 $w_x<w_y$。

E1 告诉我们，一种情况先手必败，当且仅当不存在一个点 $x$ 是“好的”。

---

在 E2 中，我们假设先手第一步移去了 $u$ 子树，且后手仍能操作。在当前情况下去做 E1，如果后手存在必胜策略，则先手必败。

所以我们要求后手不存在必胜策略，即对于「**当前树上** 的所有满足 $w_u<w_v$ 的点 $v$」，所有「满足 $w_v<w_x$ 的点 $x$」要么出现在 $u$ 子树中，要么出现在 $v$ 子树中。

于是问题转化为：对于每个 $u$ 点，判断是否存在两点 $v,x$，使得 $w_u<w_v<w_x$，且 $v$ 不在 $u$ 子树中，$x$ 不在 $u,v$ 子树中。

---

对于该问题，考虑如下算法，我姑且称之为 min-max trick。

首先将所有点按照 $w$ 从大到小的顺序扫描，对于每一个点 $v$，找出是否存在 $v$ 子树外的点 $x$ 满足 $w_v<w_x$。若存在，我们仅记录其中 $\text{dfn}_x$ 的 **最大值 $\text{maxx}_v$ 和最小值 $\text{minx}_v$**。其中 $\text{dfn}_x$ 表示 $x$ 的 dfs 序。

然后再次对所有点按照 $w$ 从大到小扫描，对于每一个点 $u$，找出所有「不在 $u$ 子树中、且满足 $w_u<w_v$ 的点 $v$」中，对应的 $\text{maxx}_v$ 的最大值 $\text{mx}$ 以及 $\text{minx}_v$ 的最小值 $\text{mn}$。

如果 $\text{mx}$ 和 $\text{mn}$ 所表示的节点 **至少有一个不在 $u$ 的子树中**，我们显然找到了一组合法的解。否则，$\text{mx}$ 和 $\text{mn}$ 所表示的节点必然 **全部位于 $u$ 的子树中**，根据 dfs 序的性质，对于每一个「不在 $u$ 子树中、且满足 $w_u<w_v$ 的点 $v$」，所有「dfs 序在区间 $[\text{minx}_v,\text{maxx}_v]$ 中的、满足 $w_v<w_x$ 的点 $x$」，它们也一定在 $u$ 的子树中，是不合法的。这样我们就证明了只记录最小、最大值的正确性。

具体实现上，我们维护两棵支持单点修改，区间查询最大最小值的线段树即可。

代码需要注意若干细节，比如特判掉 $u$ 不是“好的”的情况。

```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 4e5 + 10, inf = 0x3f3f3f3f;
struct segment_tree{
	int maxx[maxn * 4], minx[maxn * 4];
	void pushup(int rt) {
		maxx[rt] = max(maxx[rt << 1], maxx[rt << 1 | 1]);
		minx[rt] = min(minx[rt << 1], minx[rt << 1 | 1]);
	}
	void build(int rt, int l, int r) {
		if (l == r) {
			maxx[rt] = 0;
			minx[rt] = inf;
			return ;
		}
		int mid = l + r >> 1;
		build(rt << 1, l, mid);
		build(rt << 1 | 1, mid + 1, r);
		pushup(rt);
	}
	void update(int rt, int l, int r, int x, int y) {
		if (l == r) {
			maxx[rt] = max(maxx[rt], y);
			minx[rt] = min(minx[rt], y);
			return ;
		}
		int mid = l + r >> 1;
		if (x <= mid) update(rt << 1, l, mid, x, y);
		else update(rt << 1 | 1, mid + 1, r, x, y);
		pushup(rt);
	}
	int query_max(int rt, int l, int r, int x, int y) {
		if (x <= l && r <= y) {
			return maxx[rt];
		}
		int mid = l + r >> 1, res = 0;
		if (x <= mid) res = max(res, query_max(rt << 1, l, mid, x, y));
		if (y > mid) res = max(res, query_max(rt << 1 | 1, mid + 1, r, x, y));
		return res;
	}
	int query_min(int rt, int l, int r, int x, int y) {
		if (x <= l && r <= y) {
			return minx[rt];
		}
		int mid = l + r >> 1, res = inf;
		if (x <= mid) res = min(res, query_min(rt << 1, l, mid, x, y));
		if (y > mid) res = min(res, query_min(rt << 1 | 1, mid + 1, r, x, y));
		return res;
	}
} T1, T2;
int T, n;
int a[maxn], dfn[maxn], siz[maxn], timer;
vector<int> vec[maxn], t[maxn], ans;
void dfs(int x, int fa) {
	dfn[x] = ++timer;
	siz[x] = 1;
	for (int i = 0; i < vec[x].size(); i++) {
		int v = vec[x][i];
		if (v == fa) continue;
		dfs(v, x);
		siz[x] += siz[v];
	}
};
int maxx[maxn], minx[maxn];
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			t[a[i]].push_back(i);
		}
		for (int i = 1; i < n; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			vec[u].push_back(v);
			vec[v].push_back(u);
		}
		dfs(1, 0);
		for (int i = 1; i <= n; i++) {
			maxx[i] = 0, minx[i] = inf;
		}
		T1.build(1, 1, n);
		for (int i = n; i >= 1; i--) {
			if (!t[i].size()) continue; 
			for (int j = 0; j < t[i].size(); j++) {
				int x = t[i][j];
				if (dfn[x] + siz[x] <= n) {
					maxx[x] = T1.query_max(1, 1, n, dfn[x] + siz[x], n);
					minx[x] = T1.query_min(1, 1, n, dfn[x] + siz[x], n);
				}
				if (dfn[x] > 1) {
					maxx[x] = max(maxx[x], T1.query_max(1, 1, n, 1, dfn[x] - 1));
					minx[x] = min(minx[x], T1.query_min(1, 1, n, 1, dfn[x] - 1));
				}
			}
			for (int j = 0; j < t[i].size(); j++) {
				int x = t[i][j];
				T1.update(1, 1, n, dfn[x], dfn[x]);
			}
		}
		T2.build(1, 1, n);
		for (int i = n; i >= 1; i--) {
			if (!t[i].size()) continue;
			for (int j = 0; j < t[i].size(); j++) {
				int x = t[i][j];
				if (minx[x] == inf && maxx[x] == 0) continue;
				if (dfn[x] + siz[x] <= n) {
					int res = T2.query_max(1, 1, n, dfn[x] + siz[x], n);
					if (res && (res < dfn[x] || res >= dfn[x] + siz[x])) continue;
					res = T2.query_min(1, 1, n, dfn[x] + siz[x], n);
					if (res != inf && (res < dfn[x] || res >= dfn[x] + siz[x])) continue;
				}
				if (dfn[x] > 1) {
					int res = T2.query_max(1, 1, n, 1, dfn[x] - 1);
					if (res && (res < dfn[x] || res >= dfn[x] + siz[x])) continue;				
					res = T2.query_min(1, 1, n, 1, dfn[x] - 1);
					if (res != inf && (res < dfn[x] || res >= dfn[x] + siz[x])) continue;
				}
				ans.push_back(x);
			}
			for (int j = 0; j < t[i].size(); j++) {
				int x = t[i][j];
				if (maxx[x]) T2.update(1, 1, n, dfn[x], maxx[x]);
				if (minx[x] != inf) T2.update(1, 1, n, dfn[x], minx[x]);
			}
		}
		printf("%d ", (int)ans.size());
		std::sort(ans.begin(), ans.end());
		for (int i = 0; i < ans.size(); i++) printf("%d ", ans[i]);
		puts("");
		for (int i = 1; i <= n; i++) {
			vec[i].clear(), t[i].clear();
		}
		ans.clear(); timer = 0;
	} 
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

[接着 E1 的做法](https://www.luogu.com.cn/article/9gv5n4k4)，考虑怎么对于一个点判断先手选完是否还能胜利，由对称性可得如果选完某个点还存在 E1 中的必胜条件那么选了就必输，否则必胜。

考核一对满足 $y \not \in sub_x,w_y>w_x$ 的 $(x,y)$ 可以贡献到哪些第一次选择的点 $u$，发现只要 $u$ 不在 $x \to root,y \to root$ 的交上就行，那么枚举 $x$ 后对于多个满足条件的 $y$，只要 $u$ 不在所有满足条件的 $y$ 的 lca 到根与自己到根的链交上就行，贡献形如一次 chkmax，最后判断每个点的权值是否小于等于其的 $w$ 即可，考虑到着扫描值域，线段树维护区间 lca 信息，树剖线段树维护 chkmax 即可做到 $O(n \log^2 n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 4e5+114;
vector<int> E[maxn];
int ans[maxn];
int w[maxn];
vector<int> P[maxn];
vector<int> Ans;
int sz[maxn],son[maxn];
int Fa[maxn],dep[maxn];
void dfs1(int u,int fa){
    dep[u]=dep[fa]+1;
    sz[u]=1;
    Fa[u]=fa;
    for(int v:E[u]){
        if(v!=fa){
            dfs1(v,u);
            if(sz[v]>sz[son[u]]) son[u]=v;
            sz[u]+=sz[v];
        }
    }
}
int top[maxn],dfn[maxn],R[maxn],dfncnt,node[maxn];
void dfs2(int u,int tp){
    top[u]=tp;
    dfn[u]=++dfncnt;
    node[dfncnt]=u;
    if(son[u]!=0) dfs2(son[u],tp);
    for(int v:E[u]){
        if(v!=Fa[u]&&v!=son[u]) dfs2(v,v);
    }
    R[u]=dfncnt;
}
int LCA(int u,int v){
    if(u==0||v==0) return u+v;
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        u=Fa[top[u]];
    }
    if(dep[u]<dep[v]) swap(u,v);
    return v;
}
vector< pair<int,int> > vec;
void ask(int u,int v){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        vec.push_back(make_pair(dfn[top[u]],dfn[u]));
        u=Fa[top[u]];
    }
    if(dep[u]<dep[v]) swap(u,v);
    while(u!=0){
        vec.push_back(make_pair(dfn[top[u]],dfn[u]));
        u=Fa[top[u]];
    }
}
int tag[maxn<<2];
int n;
void chkmax(int cur,int lt,int rt,int l,int r,int v){
    if(rt<l||r<lt||r<l) return ;
    if(l<=lt&&rt<=r){
        tag[cur]=max(tag[cur],v);
        return ;
    }
    int mid=(lt+rt)>>1;
    chkmax(cur<<1,lt,mid,l,r,v);
    chkmax(cur<<1|1,mid+1,rt,l,r,v);
}
int mx,cntmx;
int ban[maxn];
void down(int cur,int lt,int rt){
    if(lt==rt){
        if(tag[cur]<=w[node[lt]]&&lt!=1&&(w[node[lt]]!=mx||cntmx>1)&&ban[node[lt]]==0) Ans.push_back(node[lt]);
        return ;
    }
    int mid=(lt+rt)>>1;
    tag[cur<<1]=max(tag[cur<<1],tag[cur]);
    tag[cur<<1|1]=max(tag[cur<<1|1],tag[cur]);
    down(cur<<1,lt,mid);
    down(cur<<1|1,mid+1,rt);
}
int tr[maxn<<2];
void ins(int cur,int lt,int rt,int pos){
    if(lt==rt){
        tr[cur]=node[lt];
        return ;
    }
    int mid=(lt+rt)>>1;
    if(pos<=mid) ins(cur<<1,lt,mid,pos);
    else ins(cur<<1|1,mid+1,rt,pos);
    tr[cur]=LCA(tr[cur<<1],tr[cur<<1|1]);
}
int query(int cur,int lt,int rt,int l,int r){
    if(rt<l||r<lt||r<l) return 0;
    if(l<=lt&&rt<=r) return tr[cur];
    int mid=(lt+rt)>>1;
    return LCA(query(cur<<1,lt,mid,l,r),query(cur<<1|1,mid+1,rt,l,r));
}
void work(){
    cin>>n;
    mx=cntmx=0;
    for(int i=1;i<=n;i++) cin>>w[i],P[w[i]].push_back(i),mx=max(mx,w[i]);
    for(int i=1;i<=n;i++) cntmx+=(w[i]==mx);
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,1);
    for(int i=n;i>=1;i--){
        for(int x:P[i]){
            int e=LCA(query(1,1,n,1,dfn[x]-1),query(1,1,n,R[x]+1,n));
            if(e==0) ban[x]=1;
            if(e!=0){
                ask(x,e);
                sort(vec.begin(),vec.end());
                chkmax(1,1,n,1,vec[0].first-1,i);
                for(int j=0;j+1<vec.size();j++) chkmax(1,1,n,vec[j].second+1,vec[j+1].first-1,i);
                chkmax(1,1,n,vec.back().second+1,n,i);
                vec.clear();
            }
        }
        for(int x:P[i]){
            ins(1,1,n,dfn[x]);
        }
    }
    down(1,1,n);
    sort(Ans.begin(),Ans.end());
    cout<<Ans.size()<<" ";
    for(int x:Ans) cout<<x<<" ";
    cout<<"\n";
    Ans.clear();
    for(int i=0;i<=n;i++) P[i].clear(),E[i].clear(),ban[i]=son[i]=0;
    for(int i=0;i<=(n<<2);i++) tr[i]=tag[i]=0;
    dfncnt=0;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
```

---

## 作者：_Kenma_ (赞：0)

## 前言

推销博客：[here.](https://www.cnblogs.com/Kenma/p/18697012)

## 正文

草感觉是一个题，会 E1 就会 E2。

如果你还不会 E1，请右转先去看 E1。

根据 E1 的结论，当前局面是必败局面当且仅当****不****存在一个点 $x$，使得 $x$ 子树外的点 $y$ 满足 $w_x<w_y$。

所以，对于先手来说，他只能一步取胜，也就是一步将局面变成必败局面。

然后，考虑哪些 $x$ 满足在操作完它之后，当前局面是必败局面。

不难发现，这样的 $x$，对于任意 $w_y>w_x$，应当满足：

1. $x$ 是 $y$ 的祖先；

2. 令 $z$ 表示满足点权 $>w_y$ 且不在 $y$ 子树内的点的共同 lca，$x$ 是 $z$ 的祖先。

两条满足任意一个即可。也很好理解，要么 $y$ 不存在，要么让后手选 $y$ 之后必输。

然后按点权从大到小加入点，用 dfs 序线段树维护每个 $y$ 对应的 $z$，再用一个树状数组做树上差分即可。

总体复杂度 $O(n \log^2 n)$，常数很小，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,x,y,a[400005],num,tmp1,tmp2;
vector<int> ans,v[400005];
int head[400005],nxt[800005],target[800005],tot;
void add(int x,int y){
	tot++;
	nxt[tot]=head[x];
	head[x]=tot;
	target[tot]=y;
}
int siz[400005],dfn[400005],rnk[400005],hson[400005],top[400005],dep[400005],f[400005],cnt;
void dfs1(int x,int fa){
	siz[x]=1;
	for(int i=head[x];i;i=nxt[i]){
		int y=target[i];
		if(y==fa) continue;
		dep[y]=dep[x]+1;
		f[y]=x;
		dfs1(y,x);
		siz[x]+=siz[y];
		if(siz[hson[x]]<siz[y]) hson[x]=y;
	}
}
void dfs2(int x,int t){
	cnt++;
	dfn[x]=cnt;
	rnk[cnt]=x;
	top[x]=t;
	if(!hson[x]) return;
	dfs2(hson[x],t);
	for(int i=head[x];i;i=nxt[i]){
		int y=target[i];
		if(y==f[x] || y==hson[x]) continue;
		dfs2(y,y);
	}
}
int lca(int x,int y){
	if(!x) return y;
	if(!y) return x;
	while(top[x]^top[y]){
		if(dep[top[x]]>dep[top[y]]) x=f[top[x]];
		else y=f[top[y]];
	}
	if(dfn[x]<dfn[y]) return x;
	else return y;
}
int val[800005],ls[800005],rs[800005],dcnt,rt;
void build(int l,int r,int &x){
	x=++dcnt;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(l,mid,ls[x]);
	build(mid+1,r,rs[x]);
}
void modify(int l,int r,int pos,int x){
	if(l==r){
		val[x]=rnk[l];
		return;
	} 
	int mid=(l+r)>>1;
	if(pos<=mid) modify(l,mid,pos,ls[x]);
	else modify(mid+1,r,pos,rs[x]);
	val[x]=lca(val[ls[x]],val[rs[x]]);
}
int query(int l,int r,int ql,int qr,int x){
	if(ql<=l && r<=qr) return val[x];
	int mid=(l+r)>>1,ans=0;
	if(ql<=mid) ans=lca(ans,query(l,mid,ql,qr,ls[x]));
	if(qr>=mid+1) ans=lca(ans,query(mid+1,r,ql,qr,rs[x]));
	return ans;
}
int c[400005];
#define lowbit(i) (i&(-i))
void chg(int x,int k){
	if(!x) return;
	for(int i=x;i<=n;i+=lowbit(i)){
		c[i]+=k; 
	}
}
int get(int x){
	int ans=0;
	for(int i=x;i;i-=lowbit(i)){
		ans+=c[i];
	}
	return ans;
}
void init(){
	for(int i=1;i<=n;i++){
		v[i].clear();
		head[i]=dfn[i]=rnk[i]=siz[i]=hson[i]=top[i]=c[i]=0;
	}
	for(int i=1;i<=dcnt;i++){
		val[i]=ls[i]=rs[i]=0;
	}
	ans.clear();
	cnt=tot=num=dcnt=rt=0;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		init();
		for(int i=1;i<=n;i++){
			cin>>a[i];
			v[a[i]].push_back(i);
		}
		for(int i=1;i<n;i++){
			cin>>x>>y;
			add(x,y);
			add(y,x);
		}
		dfs1(1,0);
		dfs2(1,1);
		build(1,n,rt);
		for(int i=n;i>=1;i--){
			for(int j=0;j<v[i].size();j++){
				x=v[i][j];
				if(dfn[x]==1) tmp1=0;
				else tmp1=query(1,n,1,dfn[x],rt);
				if(dfn[x]+siz[x]-1==n) tmp2=0;
				else tmp2=query(1,n,dfn[x]+siz[x],n,rt);
				y=lca(tmp1,tmp2);
				if(!y) continue;
				//cout<<"qq"<<x<<' '<<get(dfn[x]+siz[x]-1)<<' '<<get(dfn[x]-1)<<'\n';
				if(get(dfn[x]+siz[x]-1)-get(dfn[x]-1)==num) ans.push_back(x);
			}
			for(int j=0;j<v[i].size();j++){
				x=v[i][j];
				if(dfn[x]==1) tmp1=0;
				else tmp1=query(1,n,1,dfn[x],rt);
				if(dfn[x]+siz[x]-1==n) tmp2=0;
				else tmp2=query(1,n,dfn[x]+siz[x],n,rt);
				y=lca(tmp1,tmp2);
				//cout<<"qwq"<<x<<' '<<y<<'\n';
				if(y){
					num++;
					if(x==y){
						chg(dfn[x],1);
					}else{
						chg(dfn[x],1);
					    chg(dfn[y],1);
					    chg(dfn[lca(x,y)],-1);
					} 
				}
			}
			for(int j=0;j<v[i].size();j++){
				x=v[i][j];
				modify(1,n,dfn[x],rt);
			}
		}
		sort(ans.begin(),ans.end());
		cout<<ans.size()<<' ';
		for(int i=0;i<ans.size();i++){
			cout<<ans[i]<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：CReatiQ (赞：0)

若对任意 $w_v>w_u$，总有 $v \in \text{subtree}_u$，选 $u$ 者必败，我们称 $u$ 为**坏点**。

对于 E1，选 $w$ 最大的不坏点即可，此时对手只能选坏点。

E1 策略告诉我们，只要对方可以选不坏点，我们必败。

所以 E2 策略是：选择迫使对手只能选坏点的点。

假设这样的点为点 $u$，则对任意 $w_v>w_u$：

- 要么 $v$ 在 $u$ 子树内。

- 要么对任意 $w_t>w_v$：

  1. $t$ 在 $u$ 子树内。
  2. $t$ 在 $v$ 子树内。

我们可以将第二点重写为：

- 对任意 $w_t>w_v$ 且 $t$ 不在 $v$ 子树内：$t$ 在 $u$ 子树内。

记 $g=\text{lca}(t)$，便可进一步重写为：

- $g$ 在 $u$ 子树内。

（顺便提一嘴，求 $g$ 就是求树上点集的 $\text{lca}$，直接找点集里 $dfn$ 最小最大的两个点，取 $\text{lca}$ 即可。）

于是**一个点满足 E2 策略**可以写成下面的形式：

$$
\begin{aligned}
&(v_1 \in \text{subtree}_u \text{ or } g_1 \in \text{subtree}_u) \\
\text{ and } &(v_2 \in \text{subtree}_u \text{ or } g_2 \in \text{subtree}_u) \\
\text{ and } &\dots
\end{aligned}
$$

上面的式子可以进行这样的合并：

$$
\begin{aligned}
&(v_1 \in \text{subtree}_u \text{ or } g_1 \in \text{subtree}_u) \\
\text{ and } &(v_2 \in \text{subtree}_u \text{ or } g_2 \in \text{subtree}_u) \\
\end{aligned}
\Leftrightarrow
\begin{aligned}
&\text{deeper}(\text{lca}(v_1,v_2),\text{lca}(v_1,g_2)) \in \text{subtree}_u\\
\text{ or } &\text{deeper}(\text{lca}(g_1,v_2),\text{lca}(g_1,g_2)) \in \text{subtree}_u
\end{aligned}
$$

其中 $\text{deeper}(u.v)$ 代表 $u,v$ 中深度更大的点。

这样所有 $v$ 对 $u$ 产生的约束最后都会合并为 $(a \in \text{subtree}_u \text{ or } b \in \text{subtree}_u)$ 的形状。

实现上，将点按 $w$ 分组，从大到小扫过每个组，考虑当前点是否满足约束以及当前点对后续点带来的约束即可。

---

## 作者：wrkwrkwrk (赞：0)

**请先通过 E1 再来看本题解。**

先讲个人话：

> 如果对手在下一步存在至少一个必胜策略，则你失败。若你成功，则下一步对手不存在必胜策略。

如果你通过了 E1，你可以知道存在至少一个必胜策略的充要条件是：

> 存在一个点，使得选中后至少存在一个比他大的点不在其子树下。

那么不存在必胜策略的充要条件是：

> 不存在一个点，使得选中后至少存在一个比他大的点不在其子树下。

根据第一步选到的子树被删除，那么该操作能导致获胜的充要条件是：

> 选中这个点之后存在下一步操作，且对于所有比它大的点，满足以下条件之一：
>
> - 其在该子树下
> - 对所有比它大的点，或者在第一步子树下，或者在第二步子树下。或者其为最大点。

做过 E1 则前面的条件易于判断，考虑不同的第二步会导致哪些比它小的起点失败：

> **不**满足以下条件之一：
>
> - 为其祖先
> - 能包含不在其子树下的比它大的所有点，不存在则该点无效。

“包含一个点集的所有点集合” 为根到点集所有点的 $\text{lca}$ 所在路径，形式上同“为其祖先”。

可以用 $\text{dfs}$ 序描述不在其子树内的点区间。用线段树按照上述顺序处理区间被记录到点的 $\text{lca}$，可以加上幺元 $0$。

显然上述存在天然顺序：按照 $w$ 大到小来处理，每次计算该层的答案，处理，赋值。注意存在一次容斥。用 $\text{bit}$ 处理不满足条件的个数，查询时不满足所有条件认为合法。

时间复杂度 $O(n \log^2 n)$，使用 $O(1)~ \text{lca}$ 可以做到 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
vector<int>g[1000006];
int w[1000006];
int l[1000006],r[1000006];
int dep[1000006]; 
int f[1000006][21];
int cnt;
void dfs(int now,int fa){
	dep[now]=dep[fa]+1;
	f[now][0]=fa;
	for(int i=1;i<=20;i++){
		f[now][i]=f[f[now][i-1]][i-1];
	}
	l[now]=cnt;
	cnt++;
	for(auto x:g[now])if(x!=fa){
		dfs(x,now);
	}
	r[now]=cnt-1;
}
int lca(int a,int b){
	if(!a||!b)return a|b;
	if(dep[a]<dep[b])swap(a,b);
	int delta=dep[a]-dep[b];
	for(int i=20;i>=0;i--){
		if(((delta>>i)&1))a=f[a][i];
	}
	if(a==b)return a;
	for(int i=20;i>=0;i--){
		if(f[a][i]!=f[b][i]){
			a=f[a][i];
			b=f[b][i];
		}
	}
	return f[a][0];
}
bool sat1[1000006],sat2[1000006];
struct bit{
	int a[1000006];
	int maxn;
	void clear(int man){
		for(int i=0;i<=man+1;i++)a[i]=0;
		maxn=man;
	}
	int lowbit(int x){
		return x&(-x);
	}
	void fz(int p,int w){
		for(;p<=maxn;p+=lowbit(p)){
			a[p]+=w;
		}
	}
	int ge(int l,int r){
		if(l!=1){
			return ge(1,r)-ge(1,l-1);
		}
		int ans=0;
		for(;r;r-=lowbit(r)){
			ans+=a[r];
		}
		return ans;
	}
}bb;
struct seg{
	int a[1000006<<2];
	void pushup(int now){
		a[now]=lca(a[now<<1],a[now<<1|1]);
	} 
	void build(int now,int l,int r){
		if(l+1==r){
			a[now]=0;
			return;
		}
		int mid=(l+r)>>1;
		build(now<<1,l,mid);
		build(now<<1|1,mid,r);
		pushup(now); 
	}
	void fz(int now,int l,int r,int p,int c){
		if(l+1==r){
			a[now]=c;
			return;
		}
		int mid=(l+r)>>1;
		if(p<mid)fz(now<<1,l,mid,p,c);
		else fz(now<<1|1,mid,r,p,c);
		pushup(now);
	}
	int ge(int now,int l,int r,int L,int R){
		if(r<=L||R<=l)return 0;
		if(L<=l&&r<=R)return a[now];
		int mid=(l+r)>>1;
		return lca(ge(now<<1,l,mid,L,R),ge(now<<1|1,mid,r,L,R));
	}
}ss; 
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		cnt=1;
		int n;
		cin>>n;
		map<int,vector<int>,greater<int>>p;
		for(int i=1;i<=n;i++){
			cin>>w[i]; 
			p[w[i]].push_back(i);
		}
		for(int i=1;i<=n;i++)g[i].clear();
		for(int i=1;i<n;i++){
			int a,b;
			cin>>a>>b;
			g[a].push_back(b);
			g[b].push_back(a);
		} 
		dfs(1,0);
		bb.clear(n);
		int tot=0;
		for(const auto &f:p){
			for(const auto &z:f.second){
				sat1[z]=bb.ge(l[z],r[z])!=tot;
			}
			for(const auto &z:f.second){
				bb.fz(l[z],1);
				tot++;
			}
		}
		ss.build(1,1,n+1);
		bb.clear(n); 
		tot=0;
		for(const auto &f:p){
			for(const auto &z:f.second){
				sat2[z]=bb.ge(l[z],r[z])==tot;
			}
			vector<pair<int,int>>x;
			for(const auto &z:f.second){
				auto c=lca(ss.ge(1,1,n+1,1,l[z]),ss.ge(1,1,n+1,r[z]+1,n+1));
				if(c)x.push_back({z,c});
			}
			for(auto c:x){
				bb.fz(l[c.first],1);
				bb.fz(l[c.second],1);
				bb.fz(l[lca(c.first,c.second)],-1);
				tot++;
			}
			for(const auto &z:f.second){
				ss.fz(1,1,n+1,l[z],z); 
			}
		}
		set<int>ans;
		for(int i=1;i<=n;i++){
			if(sat1[i]&&sat2[i])ans.insert(i);
		}
		cout<<ans.size()<<' ';
		for(auto p:ans)cout<<p<<' ';
		cout<<'\n';
		
		
	}
	return 0;
}
```

[AC](https://codeforces.com/problemset/submission/2062/303332433) 记录

---

