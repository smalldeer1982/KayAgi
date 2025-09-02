# Determine Winning Islands in Race

## 题目描述

MOOOOOOOOOOOOOOOOO

— Bessie the Cow, The Art of Racing on Islands



Two of Farmer John's cows, Bessie and Elsie, are planning to race on $ n $ islands. There are $ n - 1 $ main bridges, connecting island $ i $ to island $ i + 1 $ for all $ 1 \leq i \leq n - 1 $ . Additionally, there are $ m $ alternative bridges. Elsie can use both main and alternative bridges, while Bessie can only use main bridges. All bridges are one way and can only be used to travel from an island with a lower index to an island with a higher index.

Initially, Elsie starts on island $ 1 $ , and Bessie starts on island $ s $ . The cows alternate turns, with Bessie making the first turn. Suppose the cow is on island $ i $ . During a cow's turn, if there are any bridges connecting island $ i $ to island $ j $ , then the cow can move to island $ j $ . Then, island $ i $ collapses, and all bridges connecting to island $ i $ also collapse. Also, note the following:

- If there are no bridges connecting island $ i $ to another island, then island $ i $ collapses, and this cow is eliminated from the race.
- If the other cow is also on island $ i $ , then after this cow moves to another island, the island collapses, and the other cow is eliminated from the race.
- After an island or bridge collapses, no cows may use them.
- If a cow is eliminated, their turn is skipped for the rest of the race.

The race ends once either cow reaches island $ n $ . It can be shown that regardless of the cows' strategies, at least one cow reaches island $ n $ . Bessie wins if and only if she reaches island $ n $ first.

For each $ 1 \leq s \leq n - 1 $ , determine whether Bessie wins if she starts the race on island $ s $ . Assume both cows follow optimal strategies to ensure their own respective victories.

## 说明/提示

In the first test case, there are no alternative bridges for Elsie to overtake Bessie and reach island $ n $ first, so Bessie will win on all islands because she always moves first.

In the second case, Bessie will lose if she starts on island $ 3 $ because:

- Bessie's Turn: Take a main bridge from island $ 3 $ to island $ 4 $ .
- Elsie's Turn: Take a main bridge from island $ 1 $ to island $ 2 $ .
- Bessie's Turn: Take a main bridge from island $ 4 $ to island $ 5 $ .
- Elsie's Turn: Take an alternative bridge from island $ 2 $ to island $ 6 $ . Elsie reaches island $ n $ first.

## 样例 #1

### 输入

```
5
6 0
6 1
2 6
6 1
1 5
10 4
1 3
1 6
2 7
3 8
15 3
2 8
4 9
8 15```

### 输出

```
11111
11011
10011
100001111
11000111000111```

# 题解

## 作者：KarmaticEnding (赞：6)

~~有生之年第一次做到的水 D~~

我们不考虑 Bessie 怎么赢，反过来，我们来考虑 Elsie 在什么情况下会赢？

首先，如果 Elsie 跟着 Bessie 只走 "main bridge"，那么它是没有胜算的，这就是说它需要走一些 alternative bridge。

在什么情况下，Elsie 能通过走 alternative bridge 走到 Bessie 前面呢？这当然需要满足两个条件。

1. Bessie 还没有走过这个 alternative bridge 的起点，也就是说这个起点还没有 Collapse。

2. Bessie 还没有走过这个 alternative bridge 的终点，也就是说这个终点还没有 Collapse。

我们把两个条件同时考虑。

对于每一个岛（以下称作结点）$i$，如果 Bessie 选取这个结点为出发点，那么起点在点 $i$ 后的 alternative bridge 全部是不能用，或者用不着的。为什么呢？

如果某一时刻 Elsie 走到了 Bessie 前面，说明 Bessie 已经不可能再超过 Elsie 了，那么其它 alternative bridge 就不用了。

反之，如果至始至终 Elsie 都没有走到 Bessie 前面，那么从 $i$ 开始后面的结点由于被 Bessie 走过，都会 Collapse，这就是说 Elsie 不能用那些 alternative bridge 了。

那么回到正题，如果 Bessie 的起点在 $i$，那么 $i$ 以前的所有 alternative bridge 全部可以为 Elsie 所用。我们从 $1$ 到 $n$ 扫一遍每一个结点，并更新所有与这个结点相连的结点的最短路。注意，这里的最短路是对于 Elsie 而言的，用 $dis$ 数组储存。

我们想想怎么统计答案呢？这促使我们思考什么时候 Elsie 会走到 Bessie 前面。假设一个 alternative bridge，其起点为 $u$，终点为 $v$，使得 Elsie 超过了 Bessie，那么 Bessie 应该在什么点出发才会造成这种情况？

首先在 $u$ 之前或者 $u$ 出发是不可能的。前面说过。

其次，我们来想想什么情况下 Elsie 会比 Bessie 快？形象化的理解，当然是 Elsie 到达结点 $v$ 比 Bessie 早。设 Bessie 的起点为 $s$，那么当且仅当 $dis_v<v-s$ 的时候 Elsie 到达结点 $v$ 的时间比 Bessie 早。

那么你可以看到，对于每一个 alternative bridge，我们会得到一个区间的始发点 $s$ 使得 Bessie 无法获胜。具体地，这个区间为 $[u+1,v-dis_v-1]$。我们得到了所有的区间，要怎么合并区间呢？

这里有一个我某天突然想到的一个 trick：对于得到的每一个区间，把区间中每一个元素加上 $1$，这里用差分数组维护。然后对差分数组做一个前缀和，得到一个数组 $s$，这个数组里面每个点 $i$ 表示 $i$ 被几个区间覆盖。所有 $s_i>0$ 的点都是 Bessie 必输的点，其他点都是 Bessie 必胜的点。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+10;
int T,n,m;
int d[MAXN],s[MAXN],dis[MAXN];
vector<int> g[MAXN];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=0;i<=n;++i){
			d[i]=s[i]=0;
			g[i].clear();
			dis[i]=0x3f3f3f3f;
		}
		dis[1]=0;
		for(int i=0,u,v;i<m;++i){
			scanf("%d%d",&u,&v);
			g[u].push_back(v);
		}
		for(int u=1;u<=n;++u){
			dis[u]=min(dis[u],dis[u-1]+1);
			for(int v:g[u]){
				if(v-u>dis[u]+1){
					++d[u+1];
					--d[v-dis[u]-1];
				}
				dis[v]=min(dis[v],dis[u]+1);
			}
		}
		for(int i=1;i<=n;++i){
			s[i]+=s[i-1]+d[i];
		}
		for(int i=1;i<n;++i){
			if(s[i]){
				putchar('0');
			}
			else{
				putchar('1');
			}
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：Register_int (赞：4)

怎么评蓝的？怎么评蓝的？怎么评蓝的？怎么评蓝的？怎么评蓝的？

首先有一个事情：如果 Bessie 从 $i$ 出发，那么起点 $\ge i$ 的桥全部没用，因为你能走就说明你已经在 Bessie 前面了，那你走他干啥？

然后你发现这些边都在 $i$ 前面你可以随便走，所以枚举 $i$ 更新往后的最短路看能不能比 Bessie 短就好了……

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

vector<int> g[MAXN];

int T, n, m, dis[MAXN], res;

int main() {
	for (scanf("%d", &T); T--; ) {
		scanf("%d%d", &n, &m), res = n;
		for (int i = 1; i <= n; i++) dis[i] = i, g[i].clear();
		for (int i = 1, u, v; i <= m; i++) {
			scanf("%d%d", &u, &v), g[u].emplace_back(v);
		}
		for (int u = 1; u < n; u++) {
			putchar(res <= n - u ? '0' : '1');
			dis[i] = min(dis[i], dis[i - 1] + 1);
			for (int v : g[u]) {
				dis[v] = min(dis[v], dis[u] + 1);
				res = min(res, n - v + dis[v]);
			}
		}
		puts("");
	}
}
```

---

## 作者：Redshift_Shine (赞：4)

## 闲话

在题解区，故意将解法复杂化，在**明显**可以以更低时间复杂度解决且代码更**容易理解**的题目中提交时间复杂度更高的题解而凸显自己看起来更高的水平是一股客观存在的不良风气，就像这题一样。

本题难度实际上低于 C。

## 题解

线性 DP。

首先考虑 Elsie 淘汰 Bessie 的充要条件。由于 Bessie 无法使用辅助边，所以为了淘汰 Bessie，Elsie 显然需要借助辅助边先于 Bessie 到达某个点。此时，我们可以计算 Elsie 在**只使用 $s$ 位置前的边时** Elsie 走到每个位置的最小用时。

以下定义 $d_i$ 为 Elsie 走到每个位置的最小用时。初始时，定义 $d_i=i$。

首先，本题使用的**从低编号到高编号的单向边**是使用线性 DP 解决本题的重要前提，因为它保证了高编号的 $d_i$ 一定会通过低编号的 $d_i$ 唯一确定。由于题目需要对每个除了 $n$ 之外的 $s$ 都求出答案，考虑如何分步进行 DP。

对于位置 $i$，容易注意到位置 $i$ 前的所有辅助边都可以使用，而位置 $i$ 后的辅助边并没有使用的必要。为什么？由于 Bessie 从位置 $i$ 开始，所以若 Elsie 走到了 $i$ 之后的一个位置，只有两种可能：Elsie 超过了 Bessie，或这个位置已经坍塌。

也就是说，当 $s$ 从 $i$ 变为 $i+1$ 时，我们可以**额外**激活从位置 $i$ 开始的所有辅助边，更新这之后的 $d_j$。

现在考虑如何判断 Bessie 是否会赢。我们将为 Elsie 设计的距离计算方法搬到 Bessie 这里，定义 $c_i$ 为 Bessie 走到每个位置的最小用时。显然，对于 Bessie 来说，$c_i=i-s+1$。由于 Bessie 先手，所以若 Elsie 和 Bessie 在同一个时间点到达同一个位置，那么 Bessie 会离开这个位置，使 Elsie 被淘汰。实际上，对于确定的 $d_i$，我们可以方便地确定 Bessie 安全到达这个位置所需要的最小 $s$ 值，我们定义其为 $p_i$。由于 Bessie 速度固定为 $1$，那么 $p_i=i-d_i+1$。同时，由于我们可以确定每条边的位置，所以我们可以得到全局最小 $s$ 值，定义其为 $r$，则 $r=\max_{i=1}^n p_i$。

显然，若 $s\ge r$，那么 Bessie 必胜，否则 Elsie 必胜。

由于我们需要 $n$ 次计算初始化所有的 $d_i$，需要 $m$ 次计算使用每条边更新 $d_i$，所以时间复杂度为 $O(n+m)$。

## 代码

在以下的代码中，`mnp` 指代 $r-1$，因为更方便维护。

```c++
#include <iostream>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
int n, m, dp[N], mnp;
vector<int> road[N];
bool res[N];
void run()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        road[i].clear();
        dp[i] = i;
    }
    for (int i = 1, x, y; i <= m; i++)
    {
        scanf("%d%d", &x, &y);
        road[x].emplace_back(y);
    }
    mnp = 0;
    res[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        dp[i - 1] = min(dp[i - 1], dp[i - 2] + 1);
        for (auto &j : road[i - 1])
        {
            dp[j] = min(dp[j], dp[i - 1] + 1);
            mnp = max(mnp, j - dp[j]);
        }
        res[i] = (i > mnp);
    }
    for (int i = 1; i < n; i++)
    {
        printf("%d", res[i]);
    }
    putchar('\n');
}
int main()
{
    int T = 1;
    scanf("%d", &T);
    while (T--)
        run();
}

---

## 作者：__Floze3__ (赞：1)

## 思路简介

我们考虑什么时候 Bessie 不能赢下比赛：当且仅当 Elsie 能够从 Bessie 起点之前的点，通过额外的路径比 Bessie 先走到某个点。充分性显然，必要性也不难理解：假如 Elsie 无法做到这一点，她永远不可能走到 Bessie 之前，因此她不可能赢得比赛。我们设这个点为 $d$，Bessie 此时的起点为 $s$，Elsie 在当前状态下走到 $d$ 的最短时间为 $t$，那么可以列出式子 $t < d - s$，移项得到 $s < d - t$，那么我们只需要维护 $d - t$ 的最大值，而与 $s$ 无关了。我们考虑如何得到 $d - t$。我们考虑从 $1$ 到 $n - 1$ 枚举 $s$，并在此同时加入起点在 $s$ 之前的每一条边，那么每一条新加入的边我们可以得到一个新的 $d - t$。对于每一条边，$d$ 是一定的，$t$ 即为走到起点的最短时间加上 $1$。难道我们还要每次加入一条边还跑一次最短路？其实不然。令这条边的起点为 $st$，假如我们求出了在 $st$ 之前的每个点 $i$ 的最小到达时间 $ti_i$，考虑计算时间的式子 $st - i + ti_i$，$st$ 是一定的，我们只需要求出 $ti_i - i$ 的最小值就可以了，我们可以用线段树做到这一点。同时考虑到，只有新加的边可能会对时间造成影响，我们只需要在加入一条边的同时更新 $ti_i - i$ 即可。对于一组数据，时间复杂度为 $O((n + m) \log n)$。

## 代码

[提交记录](https://codeforces.com/contest/1998/submission/275629820)

---

## 作者：MrPython (赞：1)

线段树优化 dp 的好题啊！方便起见，题解中**点的编号从 $0$ 开始**。

首先，很显然易见的是，只要在某个时刻 Elsie 的位置严格大于 Bessie 所在的位置，那么 Elsie 就可以获胜。因此，我们希望求出到所有点的最短距离。这是一张 DAG，这启发我们往动态规划的方向思考。

在初始时，Bessie 可以直接破坏起点让 Elsie 掉下去，Bessie 直接获胜。

再考虑当 Bessie 从第 $i$ 个岛出发时，第 $0$ 到 $i-1$ 都是绝对不可能被 Bessie 破坏的，我们可以用 dp 直接求出从 $0$ 到这些岛屿的最小距离。但是对于 $i$ 之后的岛，我们不确定在到达时是否会被 Bessie 踩掉，所以我们只能确定到岛 $[0,p)$ 的最小距离。  
不过 Bessie 会破坏从 $i$ 开始某个长度的**连续区间**，Elsie 若想超越 Bessie，必然是从 $[0,i)$ 的某个岛屿通过备用桥直接跨过去。我们将岛 $[0,i)$ 能一步到达的所有岛屿求出最小距离来。Bessie 到达 $j(i\le j < n)$ 所用的时间为 $j-i$。记 dp 数组为 $f_i$，所有无法到达的点计为 $+\infty$。若能找到一个 $j(i\le j < n)$ 满足 $f_{i,j}<j-i$，即 Elsie 到达 $j$ 所用时间小于 Bessie，就是超过了她，可以获胜。

对于每一个 $i$ 都跑一遍 dp 即可求出答案。这样，我们有了一个 $O(n^2)$ 的做法，可喜可贺！再考虑如何优化。

下一轮，Bessie 会从第 $i+1$ 个岛屿出发。由于 DAG，更新第 $i+1$ 并不会影响 $f_{[0,i)}$ 的值，因此 $\forall j\in[0,i),f_{i+1,j}=f_{i,j}$。如果我们在前一轮（第 $i$ 轮）的时候还顺手考虑了连接 $i$ 与 $i+1$ 的主桥，那么根据 DAG，点 $i$ 的答案其实也已经计算好了，即 $f_{i+1,i}=f_{i,i}$。另外，安全的岛仅仅从 $[0,i)$ 拓展到 $[0,i+1)$，仅多出了岛 $i$，那么只有与 $i$ 直接相连的点才可能更新。综上，我们发现 $f_{i+1}$ 与 $f_i$ 相当相似，更新时可以直接压掉一维。

还有一件事：检查 Elsie 是否超过 Bessie 也是一轮 $O(n)$ 的！不过我们发现无论从哪个点开始 Bessie 到达每个点的最短路程都是斜率为 $-1$ 的一次函数，那么直接上经典技巧，给每个值都加上个偏移，就成求区间内是否有数小于定值了，用个取区间最小值的线段树维护就好了。
```cpp
#include <bits/extc++.h>
using namespace std;
namespace pbds = __gnu_pbds;
istream &fin = cin;
ostream &fout = cout;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
class SGtree {
    struct node {
        size_t invl, invr;
        uli minv;
        node *nodel, *noder;
        node(size_t l, size_t r) : invl(l), invr(r), minv() {
            if (r - l == 1)
                nodel = noder = nullptr;
            else {
                size_t mid = (r - l) / 2 + l;
                nodel = new node(l, mid), noder = new node(mid, r);
            }
        }
        bool in_interval(size_t l, size_t r) { return l <= invl && invr <= r; }
        bool no_matter(size_t l, size_t r) { return invr <= l || r <= invl; }
        uli getMin(size_t l, size_t r) {
            if (no_matter(l, r))
                return numeric_limits<uli>::max();
            if (in_interval(l, r))
                return minv;
            return min(nodel->getMin(l, r), noder->getMin(l, r));
        }
        void set(size_t p, uli v) {
            if (invl == p && invr - invl == 1)
                return void(minv = v);
            if (no_matter(p, p + 1))
                return;
            nodel->set(p, v), noder->set(p, v);
            minv = min(nodel->minv, noder->minv);
        }
    } root;
 
public:
    SGtree(size_t n) : root(0, n) {}
    uli getMin(size_t l, size_t r) { return root.getMin(l, r); }
    void set(size_t p, uli v) { return root.set(p, v); }
};
int main(void) {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    size_t T;
    fin >> T;
    while (T--) {
        size_t n, m;
        cin >> n >> m;
        vector<vector<size_t>> mp(n);
        while (m--) {
            size_t x, y;
            cin >> x >> y;
            if (y - x == 1)
                continue;
            mp[--x].emplace_back(--y);
        }
        SGtree f(n);
        for (size_t i = 0; i < n; ++i)
            f.set(i, numeric_limits<uli>::max() / 2);
        f.set(0, n);
        for (size_t p = 0; p < n - 1; ++p) {
            cout << (f.getMin(p, n) < n - p ? '0' : '1');
            ui x = f.getMin(p, p + 1) - (n - p);
            for (size_t i : mp[p])
                if (f.getMin(i, i + 1) - (n - i) > x + 1)
                    f.set(i, x + 1 + (n - i));
            if (f.getMin(p + 1, p + 2) - (n - (p + 1)) > x + 1)
                f.set(p + 1, x + 1 + (n - (p + 1)));
        }
        cout << '\n';
    }
    return 0;
}
```

---

## 作者：stswkl (赞：0)

## 题意
[题目传送门](https://codeforces.com/problemset/problem/1998/D)

## 思路
发现不是 Bessie 赢就是 Elsie 赢，所以考虑找出所有 Elsie 赢的情况，剩下的就是 Bessie 赢的情况了。因为 Elsie 后手且 Bessie 可以选择起点，所以 Elsie 走主桥没有胜算，要想超过 Bessie 必须走备用桥。

假设 Bessie 选择的起点为 $u$，可以发现只有在 $u$ 以前的备用桥才会被使用，因为在 $u$ 及后面的备用桥有的因为岛屿坍塌不能上去，而没有坍塌的桥都在 Bessie 前面，同时因为 Bessie 只能走主桥，所以要是 Elsie 走到了 Bessie 的前面，Elsie 就赢了，也就是说若 Elsie 到达了那些没有坍塌的桥，则必然可以赢，故只考虑 $u$ 以前的桥。

设 $dp_u$ 表示岛屿 $1$ 到岛屿 $u$ 的最小距离，再设以岛屿 $u$ 为起点的备用桥到达岛屿 $v$，则有如下转移方程：

$$
dp_u\gets\min(dp_u,dp_{u-1}+1)\\
dp_v\gets\min(dp_v,dp_u+1)
$$

接下来我们从小到大枚举 $u$，每次枚举都更新 $dp$ 数组，然后计算从岛屿 $1$ 到岛屿 $n$ 的最短距离，记为 $dis$，若 $dis<n-u$，即 Elsie 比 Bessie 更快到达岛屿 $u$，Elsie 赢，其他情况 Bessie 赢。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=2e5+5,INF=(int)4e18+5;
list<int>edge[N];
void build(int u,int v){edge[u].push_back(v);}
int dp[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--)
	{
		int n,m;
		cin>>n>>m;
		for(int i=1;i<=n;i++)dp[i]=INF,edge[i].clear();
		for(int i=1,u,v;i<=m;i++)cin>>u>>v,build(u,v);
		int dis=n-1;
		dp[1]=0;
		for(int u=1;u<n;u++)
		{
			dp[u]=min(dp[u],dp[u-1]+1);
			cout<<(dis<n-u?0:1);
			for(int v:edge[u])
			{
				dp[v]=min(dp[v],dp[u]+1);
				dis=min(dis,n-v+dp[v]);
			}
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：__Louis__ (赞：0)

## CF1998D Determine Winning Islands in Race 题解

### 题目描述

有两头牛，分别叫 Bessie 和 Elsie。现在有一个有向图，$n$ 个节点，分别为 $1$ 到 $n$，同时这个图拥有两种边。

- 从 $i$ 走到 $i+1$。
- $m$ 条额外的边，满足从编号较小的节点走到编号较大的节点。

Bessie 只能走第一种边，而 Elsie 可以同时走两种边。

同时，一头牛走过或者已经到达的节点，另一头牛将无法再次经过。

现在 Elsie 从 $1$ 出发，Bessie 可以从 $1$ 到 $n-1$ 出发，Bessie 先走，问最后谁先走到 $n$。

Bessie 到输出 $1$，其余输出 $0$，以字符串的形式输出。  

多组数据，每组输出一行。

### 分析

首先，因为节点不能被经过两次，所以一定存在“超车”的情况，即 Elsie 用了第二种边超过了 Bessie。

先线性dp求出 Elsie 到达每一个节点的最短时间，然后遍历每一个第二种边，找到 Elsie 到达出发点 $u$ 的时间 $t$，到达的点为$v$，那么可以超车的区间便是 $[u+1,v-t-1]$。

然后区间合并即可。

### code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
const int maxn=2e5+10;
struct node{
	int l,r;
}lin[maxn];
int dp[maxn];
vector<int> v[maxn];
bool vis[maxn];
void init(int n){
	for(int i=0;i<=n;i++){
		v[i].clear();
	}
	for(int i=0;i<=n;i++){
		dp[i]=inf;
	}
	for(int i=0;i<=n;i++){
		vis[i]=false;
	}
	for(int i=0;i<=min(n*n/2,maxn-1);i++){
		lin[i].l=lin[i].r=0;
	}
}
bool cmp(node a,node b){
	if(a.l==b.l) return a.r<b.r;
	else return a.l<b.l;
}

signed main(){
//	freopen("data.in","r",stdin);
//	freopen("d.out","w",stdout);
	int T;
	scanf("%lld",&T);
	while(T--){
		int n,m;
		scanf("%lld%lld",&n,&m);
		int a,b;
		init(n);
		for(int i=1;i<=m;i++){
			scanf("%lld%lld",&a,&b);
			v[b].push_back(a);
		}
		dp[1]=1;// 初始化是1，原因是Elsie后走。
		for(int i=2;i<=n;i++){
			dp[i]=dp[i-1]+1;
			for(int j:v[i]){
				dp[i]=min(dp[i],dp[j]+1);
			}
		}
		int cnt=0;
		for(int i=1;i<=n;i++){
			for(int k:v[i]){
				int p=dp[k];
				if(i-p-1>k){
					lin[++cnt].l=k+1,lin[cnt].r=i-p-1;
				}
			}
		}
		sort(lin+1,lin+1+cnt,cmp);
		int l=lin[1].l,r=lin[1].r;
		for(int i=2;i<=cnt;i++){
			if(lin[i].l>r){
				for(int j=l;j<=r;j++){
					vis[j]=true;
				}
				l=lin[i].l;
				r=lin[i].r;
			}
			r=max(lin[i].r,r);
		}
		for(int j=l;j<=r;j++){
			vis[j]=true;
		}
		for(int i=1;i<=n-1;i++){
			if(vis[i]) printf("0");
			else printf("1");
		}
		printf("\n");
	}
	return 0;
}

```

---

## 作者：yshpdyt (赞：0)

## 题意
一条由 $n-1$ 条形如 $i\rightarrow i+1$ 的普通有向边组成的链，有 $m$ 条形如 $x \rightarrow y (x<y)$ 的特殊有向边，通过每条边的时间都是 $1$。

`Alice` 初始位于 $1$ 号点，其可以走所有边，`Bob` 初始位于 $s$ 号点，其只能走普通边，当一个人从 $j$ 号节点走到 $i$ 号节点时，$j$ 号节点会坍塌，与之有关的所有边都会坍塌。如果一个人所在节点被摧毁，或无法到达 $n$ 号节点，那么他就输了。

求出当 `Bob` 先手时，对于所有可能的 $s$，其是否能获胜。

## Sol
由于不存在平局，所以只需要求出一个人获胜情况。

注意到 `Alice` 比较自由而 `Bob` 需要每个点都走，考虑 `Alice` 获胜条件，即其比 `Bob` 先到达某一个点，这种情况只可能是走特殊边导致的，考虑枚举其先到的点 $i$，记 $f_i$ 为 $1$ 到 $i$ 的最短路径长度，考虑 $s$ 处于什么范围时会被 `Alice` 拦截，需要满足：
$$f_i<i-s\Leftrightarrow s\le i-f_i-1$$

但是这样不够完全，如果 `Alice` 到达 $i$ 的最短路的上一个节点为 $j$，而 `Bob` 可以先比 `Alice` 到达 $j$，那么 `Alice` 会输，考虑让 $i$ 只负责 $[j+1,i]$ 这一段的 $s$，$j$ 及以前的位置会在枚举 $j$ 被统计，于是便有：

$$s\in[j+1,i-f_i-1]$$

但是这样还是没有结束，考虑存在另一个前驱 $k$ 满足有特殊边 $k\rightarrow i$，通过该路径到达 $i$ 的长度为 $x\ge f_i$，使得 $k< j,i-x-1\le i-f_i-1$，那么会漏算 $[k+1,j]$ 的情况。

于是可以在求最短路时顺带统计答案，对于每个点，其都会被其所有前驱遍历一遍，所以不会漏算，考虑当前处理 $x\rightarrow y$ 这条边时，可以使位于 $s\in[x+1,y-f_x-2] $  时无法获胜。

至于如何统计贡献，只需要标记 $s\in[x+1,y-f_x-2] $ 无法获胜，用差分数组维护即可。由于边权是 $1$，最短路其实就是 bfs，时间复杂度 $O(n)$。

## Code
```cpp
#include<bits/stdc++.h>
#define N 200005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const int mod=1e9+7;
const int inf=1e18;
const double eps=1e-6;

int n,m,f[N],sum[N];
vector<int> v[N];
bool vis[N];
queue<int>q;
void add(int l,int r){
    sum[l]++,sum[r+1]--;
}
void fc(){
	for(int i=1;i<=n;i++)f[i]=inf,vis[i]=0;
	f[1]=0;
	q.push(1);
	while(!q.empty()){
		int t=q.front();
		q.pop();
		if(vis[t]==1)continue;
		vis[t]=1;
		for(auto y:v[t]){
			if(f[y]>f[t]+1){
				f[y]=f[t]+1;
				q.push(y);
			}
            if(y-f[t]-2>=t+1)add(t+1,y-f[t]-2);
		}
	}
}
void sol(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        v[i].clear(),sum[i]=0;
        v[i].push_back(i+1);
    }
    for(int i=1,x,y;i<=m;i++){
        cin>>x>>y;
        v[x].push_back(y);
    }
    fc();
    for(int i=1;i<n;i++){
        sum[i]=sum[i-1]+sum[i];
        if(sum[i])cout<<0;
        else cout<<1;
    }
    cout<<endl;
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    int ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}

```

---

