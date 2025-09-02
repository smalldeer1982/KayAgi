# [BalticOI 2024] Jobs

## 题目背景

翻译自 [BalticOI 2024 Day1 T1](https://boi2024.lmio.lt/tasks/d1-jobs-statement.pdf)。

## 题目描述

目前，你可以选择从 $1$ 到 $N$ 编号的 $N$ 个一次性工作。

完成第 $i$ 个工作将给你带来 $x$ 欧元的利润，当然，利润也可能是负的。

有些工作依赖于另一个工作。也就是说，可能有一个编号为 $p$ 的工作必须在第 $i$ 个工作开始之前完成。因此，一个利润较大的工作如果依赖于一个利润为负的工作，看起来收益可能会比较小。

如果 $p = 0$，则第 $i$ 个工作没有依赖。

你目前有 $s$ 欧元，可以决定做哪些工作以及以什么顺序去做，只要尊重依赖关系。此外，你所拥有的钱数在任何时候都不能变成负数。

请计算通过选择按照某种顺序完成（也可能某些选择不完成）这 $N$ 个工作所能获得的最大利润。

## 说明/提示

分别选择 $1,4,3,5$ 号工作即可，总利润为 $3+2-5+6 = 6$。

| 子任务编号 | 特殊性质 | 分值 |
| :-----------: | :-----------: | :-----------: |
| $1$ | $s = 10^{18}$ | $11$ |
| $2$ | $N \leq 2000$ 且满足性质 A | $14$ |
| $3$ | 满足性质 A | $15$ |
| $4$ | $N \leq 2000$ | $29$ |
| $5$ | 无特殊性质 | $31$ |

* 性质 A：每个 $p_i$ 要么是 $0$，要么是 $i-1$。

对于所有的数据，$1 \leq N \leq 3 \times 10^5$，$0 \leq s \leq 10^{18}$，$-10^9 \leq x_i \leq 10^9$，$0 \leq p_i < i$。

## 样例 #1

### 输入

```
6 1
3 0
-3 1
-5 0
2 1
6 3
-4 5```

### 输出

```
6```

# 题解

## 作者：_saltFish_ (赞：10)

看到这一题我就想到了另一个题目，对比之下发现，这不就是 P7925 的加强版吗。~~怪不得那么眼熟~~。

## 思路

回归正题，我们考虑如何解决本题。题面很明显给出了一个森林，但并不妨碍，我们建出一个虚根 $0$ 然后当有根树做就行。

首先，根据一个正常人的思维，我们只会在保证能够赚到钱的时候才会进入某个子树内，否则进去只会亏本，还不如不进去。

有了这个前提，我们希望对于每个点求出一个值 $f_{u}$ 表示进入以 $u$ 为根的子树时，我的手上至少要有 $f_{u}$ 的钱数才能赚到钱，如果不可能赚到那么 $f_{u}=+\infty$。

假设我们已经求出了 $f_{u}$，对于一个拓展出的确定局面，我们一定是先取用能拓展到的 $f_{u}$ 最小的点（这个可以考虑反证法证明，并不难）。这个事情可以交给堆来完成。考虑如何求答案，我们从根开始拓展，同时维护一个 $now$ 表示当前钱数，一开始将根加入堆中，每次取出一个点，将它的贡献加入当前钱数，然后拓展出它的儿子，将它的儿子加入堆中。重复上述操作直至取出的点有 $f_{u}>now$，这表明现在不论如何拓展都不可能赚到到更多的钱，那么此时的 $now$ 就是最大**钱数**，注意到题目要求的是**利润**，所以要减去 $s$ 才是我们要求的答案。

上述过程为 $O(n\log{n})$，没有问题。

接下来介绍本题的重点，如何求出 $f_{u}$。

一个朴素的想法是，我们对于每一个点，采用与求答案类似的方法，从子树的根开始拓展整棵子树，并动态地维护我们的投入钱数 $f_{u}$，在 $now>f_{u}$ 时，我们可以放心离开，否则就还要拓展下去，因为现在还是亏本的，但是不同的是，如果取出的点 $cur$ 有 $f_{cur}>now$，由于现在还没有赚到足够的钱，我们必须进入 $cur$ 这个子树，但是又无法在 $u$ 的子树内赚到更多钱了。那么为了赚到更多的钱，我们只有一个办法，**加大投资**。也就是我们更新 $f_{u}$，既然现在的 $now$ 不够，那我们就加大投入让它够。具体的，我们将 $f_{u}$ 加上 $f_{cur}-now$ 这样我们就可以将 $now$ 提升至刚好能够到 $f_{cur}$，能够放心赚钱了。如果自始至终都没有赚到，说明这个子树不可能赚到，令 $f_{u}=+\infty$ 即可。

~~现在我们就切掉了 P7925~~。这个过程明显是 $O(n^2\log{n})$ 的，能够通过我们前面提到的弱化版，但是难以通过本题（实测 TLE 两个点）。

考虑优化，我们发现，在求 $f_{u}$ 时，我们反复拓展了同一个子树，导致了极大的浪费，一个点的子树可能会被这个点的所有祖先扫个遍，所以优化这个过程是我们解题的关键。

我们发现，在求 $f_{u}$ 拓展到一个点 $cur$ 时，我们**一定会按照求 $f_{cur}$ 的顺序拓展 $cur$ 的子树**，并且这个过程是**必要**的。否则进入 $cur$ 的子树就是无意义的（赚不到钱啊），不会选择进入它。

为了方便表述，我们将求完一个点的 $f$ 之后堆中剩下点的点集称为边界弧。因为在这个点的子树内，边界弧之上的点都被拓展过了，而边界弧之下的点都还没被拓展。至于为什么是弧，~~只是我在画图的时候画成了一条弧线~~。

这样就好办了，我们在求完一个点的 $f$ 之后，将它的边界弧存好，在祖先拓展到它的时候我们直接调用，将拓展至边界弧的过程直接跳过。具体的，我们把存好的边界弧直接合并到现在维护的堆中即可。这个过程需要一个可并堆。由于跳过了这个过程，所以我们还要对每个点维护一个 $got_{u}$ 表示 $u$ 节点拓展到边界弧所赚到的钱数，以此来更新我们维护的 $now$。

至于可并堆的合并，我们可以采用启发式合并。

简单分析一下复杂度，边界弧只会向下推不会向上推，所以每个点只会被边界弧扫到一次，这个过程是 $O(n\log{n})$ 的，复杂度瓶颈在于可并堆合并，理论上界为 $O(n\log^{2}{n})$ 而且似乎不怎么能跑满，通过本题毫无压力。

那么我们就愉快地做完了这一题。本人比较懒，所以从 xiezheyuan 巨佬那要到了 pbds 可并堆来用。

```cpp
#include <iostream>
#include <bits/extc++.h>

using namespace std;

#define LL long long
#define heap __gnu_pbds::priority_queue<int, cmp, __gnu_pbds::pairing_heap_tag>

const int N = 3e5 + 5;

int n;
int h[N], to[N], nxt[N], tot;
LL f[N], got[N], p[N], s;

struct cmp {
    bool operator () (int x, int y) {
        return f[x] > f[y];
    }
};

heap q[N];

void add(int u, int v) {
    nxt[++tot] = h[u], to[h[u] = tot] = v;
}

void push(int u) {
    LL now = 0;

    f[u] = 0;
    q[u].push(u);

    while(!q[u].empty()) {
        int cur = q[u].top();

        q[u].pop();

        if(f[cur] == 2e18) {
            break;
        }

        if(now < f[cur]) {
            f[u] += f[cur] - now;
            now = f[cur];
        }

        if(cur == u) {
            now += p[cur];
            for(int i = h[cur]; i; i = nxt[i]) {
                int v = to[i];
                q[u].push(v);
            }
        } else {
            now += got[cur];
            
            if(q[u].size() < q[cur].size()) {
                q[u].swap(q[cur]);
            }

            q[u].join(q[cur]);
        }

        if(now > f[u]) {
            got[u] = now - f[u];
            return ;
        }
    }

    f[u] = 2e18;
}

void dfs(int u) {
    for(int i = h[u]; i; i = nxt[i]) {
        int v = to[i];

        dfs(v);
    }

    push(u);
}

void work() {
    LL now = s;
    heap node;

    node.push(1);

    while(!node.empty()) {
        int u = node.top();

        node.pop();

        if(now < f[u]) {
            break;
        }

        now += p[u];

        for(int i = h[u]; i; i = nxt[i]) {
            int v = to[i];
            node.push(v);
        }
    }

    cout << now - s << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> s;

    for(int i = 1; i <= n; i++) {
        int fa;
        
        cin >> p[i + 1] >> fa;
        add(fa + 1, i + 1);
    }

    dfs(1);
    work();
}
```

---

## 作者：wh__ (赞：3)

## solution:

设 $f[u]$ 为：若进入以 $u$ 为根的子树有正收益 ( 负收益定为 $\inf$ )，在考虑完能尽可能获取收益的结点后，进入的最低以 $u$ 为根的子树最低收益门槛。

当我们在从下往上跑出 $f[u]$，遍历 $u$ 子树时，设 $now$ 为当前收益(不包括起点 $0$)。

**1.** 若 $now \ge f[u]$，就可以不用继续拓展 $f[u]$。

**2.** 若 $now < f[u]$，则要维护一个堆，存已扩展的子树中的 $f[v]$。

若堆顶的 $f[top] > now$ 代表我目前的 $now$ 在 $u$ 子树中拓展不动了，并且此时在 $u$ 子树中收益仍为负，所以我就要更新进入 $u$ 的门槛 $f[u]=f[u]+f[top]-now$，并且 $now=f[top]$。

但我们发现，当我们在更新 $f[u]$ 时，会反复拓展相同子树。

所以思考发现：更新每一个 $f[cur]$ 后，都会存在一个剩下的点堆 $Q _ {cur}$，所以要遍历子树 $cur$ 时，可以直接跳过一大堆节点，并取 $Q _ {cur}$ 更新 $f$。

因此还要定义一个 $earn[cur]$ 表示：从 $cur$ 拓展到边界 $Q _ {cur}$ 所赚得的收益，来维护 $now$。

更新 $u$ 时，我们可以将子树 $Q$ 合并入堆，再维护 $now$，这里很明显采用启发式合并，把小的塞入大的堆中，整体复杂度是 $O(n\log^2n)$ 的。

**PS:** 新学了一个很好用的 pbds 可并堆，来进行启发式合并---[教程](https://oiwiki.org/lang/pb-ds/pq/)。

感谢 @binbin_200811 的提醒，此题用 pbds 对配堆合并的时间复杂度为 $O(1)$，可不用启发式合并。

### code：

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>//pbds
#define inf 2e18
#define heap __gnu_pbds::priority_queue<int,cmp,__gnu_pbds::pairing_heap_tag>
typedef long long LL;//要开long long
typedef double D;
using namespace std;
const int SIZE=1e6+10,N=1e4+10;
LL id,T;
LL n,s;
LL val[SIZE];
int tot;
LL f[SIZE],earn[SIZE];
struct cmp
{
    bool operator () (const int &A,const int &B)
    {
        return f[A]>f[B];
    }
};
heap q[SIZE];
struct edge
{
    int to,nxt,id;
}e[SIZE];
int h[SIZE],cnt;
void add(int u,int v,int id)
{
    e[++cnt].to=v;
    e[cnt].id=id;
    e[cnt].nxt=h[u];
    h[u]=cnt;
}
LL read()
{
    LL res=0,x=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')x=-1;ch=getchar();}
    while(isdigit(ch)){res=(res<<3)+(res<<1)+(ch^48);ch=getchar();}
    return x*res;
}
void solve(int u)
{
    LL now=0;
    f[u]=0;
    q[u].push(u);
    while(!q[u].empty())
    {
        int cur=q[u].top();
        q[u].pop();
        if(f[cur]==inf) break;
        if(now<f[cur])
        {
            f[u]+=f[cur]-now;
            now=f[cur];
        }
        if(cur==u)
        {
            now+=val[u];
            for(int i=h[cur];i;i=e[i].nxt)
            {
                int v=e[i].to;
                q[u].push(v);
            }
        }
        else
        {
            now+=earn[cur];
            if(q[u].size()<q[cur].size()) q[u].swap(q[cur]);
            q[u].join(q[cur]);
        }
        if(now>f[u])
        {
            earn[u]=now-f[u];
            return ;
        }
    }
    f[u]=inf;
}
void dfs(int u)
{
    for(int i=h[u];i;i=e[i].nxt)
    {
        int v=e[i].to;
        dfs(v);
    }
    solve(u);
}
void work(LL x)
{
    LL now=s;
    heap q1;
    q1.push(0);
    while(!q1.empty())
    {
        int u=q1.top();
        q1.pop();
        if(now<f[u]) break;
        now+=val[u];
        for(int i=h[u];i;i=e[i].nxt)
        {
            int v=e[i].to;
            q1.push(v);
        }
    }
    printf("%lld\n",now-x);
}
signed main()
{
    n=read(),s=read();
    for(int i=1;i<=n;i++)
    {
        val[i]=read();
        int fa=read();
        add(fa,i,++tot);
    }
    dfs(0);
    work(s);
    return 0;
}
```

---

## 作者：xiezheyuan (赞：3)

先 %%% \_saltfish\_。\_saltfish\_太强了想出了正解。

## 思路

首先本题有一个弱化版 P7925。那道题 $O(n^2)$ 是可以做的。

我们在这里简要说一下 P7925 的做法。对于每一个点 $i$，引入一个估价函数 $f(i)$ 表示要想在以 $i$ 为根的子树中获益，则进入子树前至少需要有的钱 / 苹果。

假如我们已经求得了 $f(i)$，那么就好做了。从根节点开始，将子节点丢进一个小根堆中。每次取出 $f(i)$ 最小的，那么这个点可以去完成的。于是我们就加上这个点的贡献，并且将这个点的儿子全部踹进堆中（此处原话引用 \_saltfish\_ 名言）。

所以问题是如何求出 $f(i)$？一个朴素的想法是，我们维护一个堆，将子节点塞到堆中，每次还是走 $f(i)$ 最小的，如果我们获益了（当前钱数大于投入钱数），也就是当前的钱数已经可以满足需求了，那么我们就可以走人了（满足了求 $f(i)$ 的条件），如果这个点的 $f$ 比现在投入钱数大，那么我们就需要抬高投入钱数。

容易发现这个做法是 $O(n^2\log n)$ 的。难以通过本题。

为了优化，我们将求 $f(i)$ 的过程称为对 $i$ 的扩展，将最终扩展到的点集称为边界弧。为什么叫边界弧呢，因为弧上面均被扩展，下面均未被扩展，并且长得像弧（bushi）。

然后每一次扩展的时候，都求了一遍它的子树中某一个点的这个边界弧，十分浪费。于是一个直观的想法就是将边界弧存起来。

还是沿用以前的思路，将边界弧用堆存起来。然后考虑拓展的时候不再重复遍历子树了，而是转而直接使用原本边界弧方式。这一部分需要可并堆。我比较懒，所以就用 pbds 了。

但是这样子，我们很难求出当前的钱数了。这个时候，我们再引入一个 $g(i)$ 表示第 $i$ 个点我们拓展到边界弧可以赚的钱数。那么合并堆的时候，需要加上这一部分的贡献，同时我们在走人之前也需要更新这个 $g(i)$。

合并堆用启发式合并的方法，复杂度就变成了 $O(n\log^2 n)$。可以通过本题。

注意：

1. 要求的是利润，所以需要减去本金。
2. 给出的本金有 $10^{18}$ 级别，经过累加后即使使用 `long long` 也很难承受，建议使用 `__int128`。


## 代码

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;

const int N = 3e5 + 5;
int n, s;

struct edge{
    int nxt, to;
} g[N << 1];
int head[N], ec, p[N];
__int128 f[N], got[N];

void add(int u, int v){
    g[++ec].nxt = head[u];
    g[ec].to = v;
    head[u] = ec;
}

struct cmp{
    bool operator()(const int &x, const int &y) const {
        return f[x] > f[y];
    }
};

using heap = __gnu_pbds::priority_queue<int, cmp, __gnu_pbds::pairing_heap_tag>;
heap hp[N];

void ytxy(int u){// 拓展 u 节点
    hp[u].push(u);
    int now = 0;
    while(!hp[u].empty()){
        int v = hp[u].top();
        hp[u].pop();
        if(now < f[v]) {
            f[u] += f[v] - now;
            now = f[v];
        }
        if(v == u) {
            now += p[v];
            for(int i=head[v];i;i=g[i].nxt){
                int to = g[i].to;
                hp[u].push(to);
            }
        } else {
            now += got[v];
            if(hp[u].size() < hp[v].size()) hp[u].swap(hp[v]);
            if(u != v) hp[u].join(hp[v]);
        }
        if(now > f[u]) {
            got[u] = now - f[u];
            return;
        }

    }
    f[u] = LLONG_MAX;
}

void dfs(int u, int fa){
    for(int i=head[u];i;i=g[i].nxt){
        int v = g[i].to;
        if(v == fa) continue;
        dfs(v, u);
    }
    ytxy(u);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> s;
    for(int i=1,u;i<=n;i++){
        cin >> p[i + 1] >> u;
        add(u + 1, i + 1);
    }
    dfs(1, 0);
    // for(int i=1;i<=(n + 1);i++) cout << (i - 1) << ' ' << f[i] << '\n';
    heap q;
    __int128 now = s;
    q.push(1);
    while(!q.empty()){
        int u = q.top();
        q.pop();
        if(now < f[u]) break;
        now += p[u];
        // cout << (u - 1) << ' ' << now << '\n';
        for(int i=head[u];i;i=g[i].nxt){
            int v = g[i].to;
            q.push(v);
        }
    }
    cout << (long long)(now - s);
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：Helloworldwuyuze (赞：2)

## P10759 [BalticOI 2024] Jobs

### Des

给定一个森林，点有点权，你有初始权值，每次进入一个点可以让权值加上点权，一个点能被到达当且仅当所有的父亲都被到达，问拓展完子树后的最大价值是多少。

### Sol

~~模拟赛场上看成了 $\text{DAG}$，导致连 $n^2$ 都不会/kk~~。

首先想想 $n^2$ 暴力。

贪心的考虑这个问题。如果进入一个点在当前持有的权值下是可以盈利的，那么我们就可以进入这个点。因此我们想知道所有的点当你持有多少权值的时候它才能盈利。

设 $f_u$ 代表上述含义。首先，如果 $a_u\ge 0$，那么显然不需要任何代价就可以让他盈利，因此此时 $f_u = 0$。

现在假设所有的 $f_v, v\in son_u$ 已经求出来了，考虑通过儿子处理父亲。显然，进入 $u$ 的入场费就必须是 $-a_u$，因此设 $f_u$ 的初值是 $-a_u$，然后现在可以扩展所有的儿子了，因此把儿子以 $f_v$ 为第一关键字，$v$ 为第二关键字进入优先队列。

设 $cur$ 表示你持有的权值，初始为 $0$。如果此时队首的第一关键字，也就是此时的 $f_v$ 要小于 $cur$，表示你可以扩展该点，直接把 $v$ 扩展即可。注意，此时不需要管 $v$ 的子树内情况，因为贪心策略会自动地让你访问 $v$ 的儿子直到你盈利。当 $cur \ge f_u$ 时即可退出循环。

于是，你每次都有可能把所有的儿子都遍历一遍，复杂度 $O(n^2\log n)$。

我们考虑一个很重要的事实：对于 $f_v$ 已经处理过一遍直到盈利的点了，那么我们是不是可以记录一下 $f_v$ 内的点那些没有被扩展过。也就是将剩余的 `priority_queue` 数组不丢掉而是存下来。当 $f_u$ 扩展 $f_v$ 的时候直接把 $v$ 内已经扩展的都扩展掉并让 $cur$ 加上这一些带来的贡献，然后合并当前节点的队列和 $v$ 的队列。这里使用启发式合并可以做到 $O(n\log^2 n)$。

```
#define endl '\n'

using namespace std;

#define int long long
const int INF = 0x3f3f3f3f3f3f3f3f;
typedef pair<int,int> PII;
typedef pair<int,PII> PIII;
const int N = 3e5 + 10;
const int MOD = 1e9 + 7;
inline int max(int x,int y){ return x<y ? y:x; }
inline int min(int x,int y){ return x<y ? x:y; }

int val[N], f[N], fa[N], root[N], a[N];
int n, s;
vector<int> g[N];
priority_queue<PII, vector<PII>, greater<PII> > q[N];

inline int merge(int x,int y){
	if(q[x].size() < q[y].size())	swap(x, y);
	while(q[y].size())	q[x].push(q[y].top()), q[y].pop();
	return x;
}

void dfs(int x){
	for(int y:g[x])	dfs(y);
	q[root[x]].push(mk(f[x], x));
	int cur = 0;
	while(q[root[x]].size()){
		int p = q[root[x]].top().se, cost = q[root[x]].top().fi; q[root[x]].pop();
		if(cur < cost)	f[x] += cost - cur, cur = cost;
		if(x == p){
			cur += val[x];
			for(int y:g[x])	q[root[x]].push(mk(f[y], y));
		}else{
			cur += val[p];
			root[x] = merge(root[x], root[p]);	
		}
		if(cur >= f[x])	return val[x] = cur - f[x], void();
	}
	f[x] = INF;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>n>>s;
	for(int i=1;i<=n;++i)	cin>>val[i]>>fa[i], g[fa[i]].pb(i), a[i] = val[i], root[i] = i;
	dfs(0);
	static priority_queue<PII, vector<PII>, greater<PII> > Q;
	priority_queue<PII, vector<PII>, greater<PII> >().swap(Q);
	Q.push(mk(f[0], 0)); int cur = s;
	while(Q.size()){
		int p = Q.top().se; Q.pop();
		if(cur < f[p])	break;
		cur += a[p];
		for(int y:g[p])	Q.push(mk(f[y], y));
	}
	cout<<cur-s<<endl;
	return 0;
}
```

---

