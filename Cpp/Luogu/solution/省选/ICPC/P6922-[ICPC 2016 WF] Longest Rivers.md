# [ICPC 2016 WF] Longest Rivers

## 题目描述

![](https://cdn.luogu.com.cn/upload/image_hosting/4ul9evsl.png)

湄南河系统是泰国的主要河流系统。按长度递减排列的六条最长的河流是：

Tha Chin（$765$ 公里）

Nan（$740$ 公里）

Yom（$700$ 公里）

Ping（$658$ 公里）

Pa Sak（$513$ 公里）

Wang（$335$ 公里）

图 1 展示了该河流系统的简化模型，其中较小的红色数字表示各河段的长度。两个或多个河流在下游汇合的点称为汇合点。汇合点用较大的黑色数字标记。在这个模型中，每条河流要么在汇合点结束，要么流入大海，流入大海的汇合点标记为特殊的汇合点编号 $0$。当两条或多条河流在汇合点（汇合点 $0$ 除外）汇合时，合并后的河流会取其中一条河流的名字。例如，Ping 和 Wang 在汇合点 $1$ 汇合，合并后的河流保留了 Ping 的名字。这样命名下，Ping 的长度为 $658$ 公里，而 Wang 只有 $335$ 公里。如果合并后的河流命名为 Wang，那么 Wang 的长度将为 $688$ 公里，而 Ping 的长度只有 $305$ 公里。

![](https://cdn.luogu.com.cn/upload/image_hosting/n8uvzv81.png)

图 1：样例输入 1 中的河流系统。同色的边表示一条河流。

对这一现象的关注引发了沿河城镇之间的激烈竞争。例如，沿 Wang 河的居民抗议说，也许通过适当的命名方案，他们的河流实际上可能是最长的，或者可能是第二长的（至少不是最后一名！）。为了结束所有的猜测，你的任务是验证所有这样的说法。

河流的排名是按长度递减排列的所有河流中的位置，最长的河流排名为 $1$。对于每条河流，确定在所有命名方案中其可能的最佳排名。在任何汇合点，任何命名方案中新、较大的河流的名称必须是该汇合点汇合的较小河流之一的名称。如果在某个命名方案中两条或多条河流长度相等，则所有并列的河流被视为具有可能的最佳排名。例如，如果一条河流是最长的，而所有其他河流相等，则这些河流的排名均为 $2$。

## 说明/提示

时间限制：9000 毫秒，内存限制：1048576 KB。

国际大学生程序设计竞赛（ACM-ICPC）世界总决赛 2016。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
6 2
PaSak 0 513
Nan 2 675
Yom 2 700
Wang 1 335
Ping 1 305
ThaChin 0 765
0 353
0 65
```

### 输出

```
PaSak 5
Nan 2
Yom 1
Wang 3
Ping 4
ThaChin 1
```

# 题解

## 作者：岸芷汀兰 (赞：5)

# 一、题目：

[洛谷原题](https://www.luogu.com.cn/problem/P6922)

[codeforces原题](https://codeforces.com/gym/101242)

# 二、思路：

这道题官方题解讲的非常好，我这里就当是简单的翻译一下官方的题解吧。

让我们从一条单独的河流 $p$ 开始。我们的目的是让这条河流的排名尽可能的靠前。显然，在从 $p$ 到根的路径上，我们都要选择 $p$ 作为汇合点的名字。假设通过这样的选择后，$p$ 的长度是 $L$。现在，问题变成了在其他汇合点上如何恰当地选择名字，使得尽可能少的河流比 $L$ 长。

如果一条河流比 $L$ 长，那我们就称这条河流是*长的*。否则，称这条河流是*短的*。我们的目标是最小化长河流的数目（等价于最小化短河流变成长河流的地点的个数）。让我们接下来考虑那些不包括 $p$ 的汇流点。

+ 如果至少有一条将要进入该汇流点的河流是长的，那么我们就可以让它继续流（从而终止其他河流）。
+ 如果所有的河流都是短的，那么我们要选择最短的河流让它继续流。

时间复杂度 $O(n^2)$——对于每个河流，我们都要执行上述过程。

现在，让我们致力于一次性计算出所有河流的答案。

对于每个河流 $p$，我们的目标是回答“如果我们在 $p$ 到根的路径上总是选择 $p$，那么我们需要至少形成多少个比 $L$ 长的河流”，这个问题等价于“我们需要至少形成多少个比 $L$ 长的河流”而不带有其他的限制。为了看到这一点，让我们采取最优策略来形成尽可能少的、比 $L$ 长的河流。然后考虑那些在 $p$ 到根的路径上、没有选择 $p$ 的汇流点，可以发现，如果我们在这些汇流点选择了 $p$，长河流的数目并不会增多。既然无论多少次选择 $p$，$p$ 的长度都不会长于 $L$，而且长河流的数目还有可能减少，那么我们当然可以在每个可以选择 $p$ 的汇流点选择 $p$。

所以我们需要对于每个 $L$，回答“至少需要形成多少个比 $L$ 长的河流”这个问题。我们将会以 $L$ 递增的顺序来一次性的回答所有问题。

假设当前处理到了长度 $L$，对于每个汇流点和每个叶子结点，它们都是以下三种状态的其中之一：

+ 至少有一条将要进入该交汇点的河流是长的（叶子结点不可能处于这种状态）。
+ 所有将要进入该交汇点的河流都是短的，但是流出该交汇点的河流将会变成长河流。
+ 所有将要进入该交汇点的河流都是短的，并且流出该交汇点的河流也是短河流。

在第二种和第三种状态，根据贪心原则，我们选择最短的河流让它流出去。

让我们以 $L=0$ 开始。所有的叶子结点都处于状态 2，所有的汇流点都处于状态 1，共有 $N$ 条长河流。

当 $L$ 增长时，可能有一些点会从状态 2 变到状态 3，也可能有一些点会从状态 1 变到状态 2。还可能有一些点会直接从状态 1 变到状态 3。比如下面这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/9jff7mev.png)

当 $L$ 从 $1$ 增长到 $5000$ 时，汇流点 2、1 都会从状态 1 变成状态 3。汇流点 3 会从状态 1 变成状态 2。

我们对于所有是状态 2 的节点维护一个小根堆，堆中保存的是二元组 $(l,x)$，表示要想把 $x$ 从状态 2 变成状态 3，$L$ 至少应该等于 $l$。每次从堆中取出最小的 $l$，把 $x$ 的状态更改为 3。再去检查 $x$ 的祖先有没有可能变状态（变成状态 2 的条件是所有儿子都是状态 3，但是别忘了特判直接从状态 1 蹦到状态 3 的情况）。由于一个点最多从状态 1 变到状态 2 一次，从状态 2 变到状态 3 一次，所以最终的时间复杂度是 $O(n\log n)$。

# 三、代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
#include <map>

using namespace std;
typedef pair<long long, int> PLI;
#define FILEIN(s) freopen(s, "r", stdin)
#define FILEOUT(s) freopen(s, "w", stdout)
#define mem(s, v) memset(s, v, sizeof s)

inline int read(void) {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return f * x;
}

const int MAXN = 1000005;
const long long INF = 1e17;

int n, m, head[MAXN], tot;
int v[MAXN], fa[MAXN], cnt[MAXN];
long long dp[MAXN], sum[MAXN];
string name[MAXN];
map<long long, int>ans;
map<long long, int>::iterator it;

struct Edge {
    int y, next;
    Edge() {}
    Edge(int _y, int _next) : y(_y), next(_next) {}
}e[MAXN];

priority_queue<PLI, vector<PLI>, greater<PLI> >q;

inline void connect(int x, int y) {
    e[++tot] = Edge(y, head[x]);
    head[x] = tot;
}

void dfs(int x, int father) {
    fa[x] = father;
    sum[x] = sum[father] + v[x];
    long long minn = INF;
    for (int i = head[x]; i; i = e[i].next) {
        int y = e[i].y;
        dfs(y, x);
        ++cnt[x];
        minn = min(minn, dp[y]);
    }
    if (minn == INF) dp[x] = v[x];
    else dp[x] = minn + v[x];
}

int main() {
    n = read(); m = read();
    for (int i = m + 1; i <= m + n; ++i) {
        cin >> name[i];
        int y = read(); v[i] = read();
        connect(y, i);
    }
    for (int i = 1; i <= m; ++i) {
        int y = read();
        v[i] = read();
        connect(y, i);
    }
    dfs(0, 0);
    int now = 0;
    long long L = 0;
    for (int i = m + 1; i <= m + n; ++i) {
        q.push({ dp[i], i });
        ++now; // 维护状态2的节点个数。
    }
    while (q.size()) {
        int x = q.top().second; long long l = q.top().first; q.pop();
        L = l;

        --now;
        --cnt[fa[x]];

        if (fa[x] && !cnt[fa[x]]) {
            x = fa[x];
            while (x && L >= dp[x]) { // 检查x的祖先们。
                --cnt[fa[x]];
                if (cnt[fa[x]] == 0) {
                    x = fa[x];
                }
                else break;
            }
            if (x && cnt[x] == 0 && L < dp[x]) {
                q.push({ dp[x], x });
                ++now;
            }
        }
        ans[L] = now + 1;
    }
    ans[INF] = 0; // 防止越界。
    for (int i = m + 1; i <= n + m; ++i) {
        it = ans.upper_bound(sum[i]); 
        --it; // 由于在求解的过程中，L的增长并不是连续的，所以我们要找最后一个小于等于sum[i]的L所对应的答案。
        cout << name[i] << " " << (*it).second << endl;
    }
    return 0;
}
```



---

## 作者：cqbzlzm (赞：0)

### Description

有 $n$ 条河和 $m$ 个交汇处和 $0$ 节点构成一棵以 $0$ 号点（即大海）为根的树。

每条河有各自的名称。对于一个交汇处，从它流出的干流的名称是流入这个交汇处的各个支流的名称之一。一条河流的长度是以它为名称的河流的长度之和。对于一个可能的命名方案，一条河流的排名等于长度大于它的河流数 +1。

对于每条河，求出它在所有命名方案中，最小的排名。

### Solution

考虑对某一条河求答案，这条河的长度一定是固定的为它到根的距离（设为 $l$）。然后转为求最少有几条河比他长。

考虑每个交汇点有三种情况：

1. 若支流中有一条河大于 $l$，则延续它。
2. 若支流中没有河大于 $l$，则延续最短的一条河。

这样对所有点跑一遍是 $O(n^2)$ 的。

观察所有节点，一定有分界线，上面的点是 1 状态，下面的点是 2 状态。身处 2 状态的点及其子树的状态可以预处理出来。

考虑优化，把所有询问的 $l$ 按从小到大排序，放在一起处理，维护 12 状态的交界点。

当 $l\rightarrow l'$，分界线可能会上移，暴力更新即可。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long

#define pii pair<int, int>

const int MAXN = 1e6;
const ll inf = 1e18;
int n, m;
vector<pii> G[MAXN + 5];
char name[MAXN + 5][11];
int father[MAXN + 5];
ll d[MAXN + 5];
ll f[MAXN + 5];
int cnt[MAXN + 5];
void dfs(int u, int fa) {
    father[u] = fa;
    ll mn = inf;
    for (auto e : G[u]) {
        int v = e.first, w = e.second;
        if (v == fa) continue;
        d[v] = d[u] + w;
        f[v] = w;
        cnt[u] ++;
        dfs(v, u);
        mn = min(mn, f[v]);
    }
    if (mn != inf) f[u] += mn;
    return ;
}
struct node {
    int x;
    ll L;
    friend bool operator < (node a, node b) {
        return a.L > b.L;
    }
} ;
map<ll, int> ans;
int main() {
    scanf("%d%d", &n, &m);
    for (int i = m + 1; i <= m + n; i ++) {
        scanf("%s", name[i]);
        int v, w; scanf("%d%d", &v, &w);
        G[v].push_back({i, w});

    }
    for (int i = 1; i <= m; i ++) {
        int v, w; scanf("%d%d", &v, &w);
        G[v].push_back({i, w});
    }
    dfs(0, 0);
    priority_queue<node> q;
    for (int i = m + 1; i <= m + n; i ++)
        q.push({i, f[i]});
    while (!q.empty()) {
        node tmp = q.top(); q.pop();
        int x = tmp.x;
        ll L = tmp.L;
        cnt[father[x]] --;
        x = father[x];
        if (x && cnt[x] == 0) {
            while (x && f[x] <= L) {
                cnt[father[x]] --;
                if (cnt[father[x]] == 0) x = father[x];
                else break;
            }
            if (cnt[x] == 0 && L < f[x])
                q.push({x, f[x]});
        }
        ans[L] = q.size() + 1;
    }
    ans[inf] = 0;
    for (int i = m + 1; i <= n + m; i ++) {
        auto it = -- ans.upper_bound(d[i]);
        printf("%s %d\n", name[i], (*it).second);
    }
    return 0;
}
```

---

