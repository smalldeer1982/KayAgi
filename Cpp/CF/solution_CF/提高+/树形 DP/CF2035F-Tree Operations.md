# Tree Operations

## 题目描述

这确实反映了我们的社会。

有一天，一只乌龟给了你一棵树，共 $n$ 个节点，其中节点 $x$ 是根节点。每个节点有一个初始非负值：第 $i$ 个节点的起始值为 $a_i$ 。

要使所有节点的值都等于 $0$ 。为此，您将在树上执行一系列操作，其中每个操作将在某个节点上执行。定义节点 $u$ 上的操作，在 $u$ 的子树 $^{\text{∗}}$ 中选择一个节点，并将其值递增或递减 $1$ 。在节点上执行操作的顺序如下：

- 对于 $1 \le i \le n$ ， 第 $i$ 次操作将在节点 $i$ 上执行。
- 对于 $i > n$ ，第 $i$ 次操作将与操作 $i - n$ 在同一节点上执行。

更正式地说，第 $i$ 次操作将在第 $(((i - 1) \bmod n) + 1)$ 次节点上执行。 $^{\text{†}}$

注意，不能跳过操作；也就是说，如果不先执行 $1, 2, \ldots, i - 1$ 操作，就不能执行 $i$ 第1次操作。

假设您选择了最优的操作，找到在使所有节点的值等于 $0$ 之前必须执行的最小操作数。如果经过有限次运算，不可能使所有节点的值都等于 $0$ ，则输出 $-1$ 。

$^{\text{∗}}$ 节点 $u$ 的子树是 $u$ 位于从该节点到根节点的最短路径上的节点集合，包括 $u$ 本身。

$^{\text{†}}$ 这里， $a \bmod b$ 表示 $a$ 除以 $b$ 的余数。

## 说明/提示

在第一个测试用例中，您可以执行以下有效的操作顺序：

- 对于操作 $1$，减少节点 $1$ 的值。这是有效的，因为 $(((1 - 1) \bmod n) + 1) = 1$ ，节点 $1$ 在节点 $1$ 的子树中。
- 对于操作 $2$ ，减少节点 $2$ 的值。这是有效的，因为 $(((2 - 1) \bmod n) + 1) = 2$ ，节点 $2$ 在节点 $2$ 的子树中。
- 对于操作 $3$ ，减少节点 $2$ 的值。这是有效的，因为 $(((3 - 1) \bmod n) + 1) = 1$ ，节点 $2$ 在节点 $1$ 的子树中。

翻译者 [wjbbssb250](https://www.luogu.com.cn/user/778527)；[WangBX](/user/305522) 修缮一些细节。

## 样例 #1

### 输入

```
5
2 1
1 2
1 2
3 2
2 1 3
2 1
3 2
4 1
1 1 0 1
1 2
2 3
1 4
12 6
14 4 5 6 12 9 5 11 6 2 1 12
3 9
10 6
6 12
4 3
3 1
5 11
9 7
5 6
1 8
2 8
5 1
1 1
0```

### 输出

```
3
6
5
145
0```

# 题解

## 作者：PosVII (赞：9)

## 前言

$O(n \log^2 n)$ 做法。

本来想藏起来出成题的，但是发现题目越来越简化最后变成唐题了。

## 思路

考虑不枚举 $k \bmod n$ 的余数，而是把它们直接甩到线段树上处理，而 $\lfloor \frac{k}{n} \rfloor$ 是单调的，可以二分。

考虑在确定每个点取的次数 $b_i$ 后，可以轻松地以一个 dp 来验证：

$f_u = \max(\sum_{v \in son_u} f_v + a_i - b_i,(\sum_{v \in son_u} f_v + a_i - b_i)\bmod 2)$

发现每个点的奇偶性已知，并且可以轻松证明在 $(\sum_{v \in son_u} f_v + a_i - b_i)\bmod 2$ 一定时，$f_u$ 随着 $k \bmod n$ 单调不降。

于是考虑线段树合并，每次合并后对于某个 $< 0$ 的前缀把它设为 $0/1$ 即可，因为是前缀修改所以复杂度不变。

此时复杂度为 $O(n \log n \log V)$，再套用官方题解的后半段做法即可做到 $n \log^2 n + n \log V$ 了。

---

## 作者：Milmon (赞：8)

## Statement

给定一棵以 $x$ 为根的 $n$ 个结点的树，结点 $i$ 的初始值为 $a_i$。

若第 $i$ 次操作的目标是 $u$，则你需要在 $u$ 的子树中选择一个节点 $v$，并令 $v$ 的权值增加或减少 $1$。你需要操作 $m$ 次，$i \leq n$ 时第 $i$ 次操作的目标是结点 $i$，否则第 $i$ 次操作的目标与第 $i - n$ 次相同。

求出 $m$ 的最小值，使得存在一种操作方案把所有结点的值都变为 $0$ 或报告无解。

数据范围：数据组数 $T \leq 100$，$n \leq 2 \times 10^3$，$\sum n \leq 2 \times 10^3$，$0 \leq a_i \leq 10^9$。

## Solution

首先，如果存在 $m$ 次操作的方案，那么一定存在 $m + 2n$ 次操作的方案（这是因为可以再进行 $2n$ 次操作，每个结点先增加 $1$ 再减少 $1$）。于是当操作次数除以 $2n$ 得到的余数固定时，一个操作次数是否可行是具有单调性的，可以使用二分解决。

问题变为如何判定一个操作次数 $m$ 是否可行。首先可以对每个结点计算出以其作为目标操作了几次，记为 $g(i)$。考虑树形 dp，设 $f(i)$ 表示以结点 $i$ 为根的子树中，还需要多少次操作才可以全部变为 $0$。计算 $f$ 只需要初始令 $f(i) = a_i$，设 $i$ 的父亲为 $u$，那么当 $f(i) > g(i)$，会对 $f(u)$ 产生 $f(i) - g(i)$ 的贡献，否则子树内有 $g(i) - f(i)$ 次操作多余，每两次可以使用两次反转操作消除，但是当其为奇数时，需要向 $f(u)$ 贡献 $1$ 次操作。

这样我们可以在 $\Theta(n)$ 的时间复杂度内判断，总时间复杂度为 $O(n^2 \log V)$，其中 $V$ 表示操作次数上限。

给出结论：一定存在一种有限次操作方案完成题目的要求。注意可以使用 $n$ 次操作让所有结点值在 $0, 1$ 之间切换，下面直接构造方案：

- 首先可以进行若干次操作，将所有位置都变为 $0$ 或 $1$。
- 取一个非根结点的结点 $y$，考虑让除了根结点 $x$ 之外所有结点的值都变得与 $y$ 相同。每次取一个与 $y$ 不同的结点 $z$，可以使用 $n$ 次操作：操作目标为 $x, z$ 时令结点 $z$ 取反，操作其余结点时令其自身取反。这样可以在 $O(n^2)$ 次操作内让除了根结点之外的所有结点的值全变为 $0$ 或全变为 $1$。
- 若 $x$ 的值与其余结点不同并且 $x \neq 1$，那么再使用上面的 $n$ 次操作让结点 $1$ 和 $x$ 之外的所有结点取反，此时只有结点 $1$ 与其他结点不同。
- 如果结点 $1$ 之外的点的值为 $1$，那么用 $n$ 次操作全局取反。
- 最后若结点 $1$ 的值为 $1$，用一次操作将 $1$ 变为 $0$。

故不存在无解的情况。

## Solution (English)

First, if there exists a plan with $m$ operations, then there must exist a plan with $m + 2n$ operations (this is because we can perform an additional $2n$ operations, where each node is first incremented by $1$ and then decremented by $1$). Thus, when the remainder of the number of operations divided by $2n$ is fixed, the feasibility of a given number of operations exhibits monotonicity, allowing for a binary search approach.

The problem then becomes how to determine if a number of operations $m$ is feasible. First, we can calculate how many times each node has been targeted as a goal, denoted as $g(i)$. Consider a tree dynamic programming approach, where $f(i)$ represents how many more operations are needed to make all nodes in the subtree rooted at node $i$ equal to $0$. To calculate $f$, we can initialize with $f(i) = a_i$. Let $i$'s parent be $u$. If $f(i) > g(i)$, it contributes $f(i) - g(i)$ to $f(u)$; otherwise, there are $g(i) - f(i)$ excess operations in the subtree. Every two excess operations can be eliminated by using two flip operations, but if the excess is odd, we need to contribute $1$ operation to $f(u)$.

This allows us to determine feasibility in $\Theta(n)$ time complexity, resulting in a total time complexity of $O(n^2 \log V)$, where $V$ represents the upper limit on the number of operations.

In conclusion, there definitely exists a finite sequence of operations to meet the problem's requirements. Note that we can use $n$ operations to toggle all node values between $0$ and $1$. Here is the construction of the solution:

- First, we can perform several operations to make all positions either $0$ or $1$.
- Choose a non-root node $y$ and consider making all nodes except for the root node $x$ have the same value as $y$. Each time, take a node $z$ that has a different value than $y$; we can use $n$ operations: when the targets are $x$ and $z$, flip node $z$, and for the remaining nodes, flip themselves. This way, within $O(n^2)$ operations, all nodes except for the root can be made either $0$ or $1$.
- If the value of $x$ is different from the other nodes and $x \neq 1$, then use the previous $n$ operations to flip all nodes except for node $1$ and $x$; at this point, only node $1$ will differ from the others.
- If the values of the nodes except for node $1$ are all $1$, then perform a global flip using $n$ operations.
- Finally, if the value of node $1$ is $1$, perform one operation to change it to $0$.

Thus, there are no cases with no solution.

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,root,a[2001];
vector<int> E[2001];
long long f[2001],g[2001];

int dfn[2001],rnk[2001],fa[2001],cntdfn;
void init(int u,int father){
    fa[u]=father,dfn[u]=++cntdfn,rnk[cntdfn]=u;
    for(int v :E[u])if(v!=father)init(v,u);
}
inline bool check(long long val){
    for(int i=1;i<=n;i++)f[i]=val/n+(i<=val%n),g[i]=a[i];
    f[0]=g[0]=0;
    for(int i=n;i>=1;i--){
        int u=rnk[i];
        g[fa[u]]+=f[u]<g[u]?g[u]-f[u]:((f[u]-g[u])&1);
    }
    return g[0]==0;
}

int main(){
    int T; scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&root);
        for(int i=1;i<=n;i++)E[i].clear();
        for(int i=1;i<=n;i++)scanf("%d",a+i);
        for(int i=1;i<n;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            E[u].push_back(v);
            E[v].push_back(u);
        }
        cntdfn=0;
        init(root,0);
        long long answer=1e18;
        for(int i=0;i<n*2;i++){
            int l=0,r=1e9;
            while(l<r){
                int mid=(l+r)>>1;
                if(check(1ll*mid*n*2+i))r=mid;
                else l=mid+1;
            }
            answer=min(answer,1ll*l*n*2+i);
        }
        printf("%lld\n",answer);
    }
    return 0;
}
```

---

## 作者：Find_NICK (赞：2)

首先观察样例，我们发现样例中没有 $-1$，因此我们猜测一定有解。\
我们考虑将最优化问题转为可行性问题。

观察 1：如果对于 $x$ 有解，则对于 $x+2n$ 也一定有解。\
证明：我们可以在原来的基础上先使用 $n$ 次加 $1$ 操作，然后再使用 $n$ 次减一操作。

现在我们可以枚举 $x = t+2nk$，其中 $t \in [0,2n)$，然后二分 $k$。\
现在问题变为，给定操作次数 $x$，如何判定是否有解？

观察 2：每个操作的顺序是不重要的，重要的是每个点被操作的次数。

观察 3：我们发现，子树大小更小的节点受到的限制比子树大小大的节点受到的限制多。

考虑从低往上贪心，如果当前节点不能承受修改的成本就把成本留给父亲，最后判断根节点是不是欠下一些成本。

具体地，我们记 $g_i$ 为 $i$ 节点被修改的次数，$f_i$ 为目前 $i$ 节点的成本。

我们记 $i$ 的父亲为 $u$。

如果 $f_i>g_i$，则我们需要从父节点处得到一些修改次数，因此 $f_u \leftarrow f_u+f_i-g_i$。

否则，$f_i\leq g_i$，注意到每两次多余的修改能够相互抵消，因此若 $g_i-f_i$ 为奇数，$f_u\leftarrow f_u+1$。

至于如何构造方案，可以参考别的题解。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
constexpr int N = 2005;
int n, r, a[N], fa[N];
ll f[N], g[N];
vector<int> G[N];
vector<int> dfn;
void dfs(int u, int fa) {
  ::fa[u] = fa;
  for (int v : G[u])
    if (v != fa)
      dfs(v, u);
  dfn.push_back(u);
}
int check(ll x) {
  f[0] = g[0] = 0;
  for (int i = 1; i <= n; i++)
    g[i] = x / n + (i <= x % n), f[i] = a[i];
  for (int i : dfn)
    f[fa[i]] += (f[i] > g[i]) ? (f[i] - g[i]) : ((g[i] - f[i]) % 2);
  return f[0] == 0;
}
void solve() {
  cin >> n >> r;
  for (int i = 1; i <= n; i++)
    G[i].clear();
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int u, v, i = 1; i < n; i++) {
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  dfn.clear();
  dfs(r, 0);
  ll ans = 1e18;
  for (int i = 0; i < 2 * n; i++) {
    ll l = 0, r = 1e9;
    while (l < r) {
      ll mid = (l + r) / 2;
      if (check(mid * 2 * n + i))
        r = mid;
      else
        l = mid + 1;
    }
    ans = min(ans, l * 2 * n + i);
  }
  cout << ans << "\n";
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T;
  for (cin >> T; T--;)
    solve();
  return 0;
}
```

---

## 作者：FRZ_29 (赞：2)

[更不好的阅读体验！](https://www.cnblogs.com/FRZ29/p/18512802)

可以说是官解的中文翻译了。

目标是使所有节点的权值变为 $0$。
      
最重要的是想到，如果 $m$ 次操作可以达到目标，那么 $2n + m$ 次操作也可行。
      
证明：在 $m$ 次操作的基础上先用 $n$ 次操作将所有节点变为 $1$，再用 $n$ 次操作把所有节点都变为 $0$。
      
这说明 $\forall i \in [0, 2n - 1],x \in\{x|x \bmod 2n = i\}$，$x$ 次操作对达到目标具有单调性。（后面将证明总是有解的）。
      
容易得到做法：遍历 $i\in[0,2n - 1]$，对集合 $\{x|x \bmod 2n = i\}$ 二分最小的能达到目标的 $x$（之后会证明二分的上下界，感性上来讲上界不会太大，上界到 $1\times10^{13}$ 次可过）。
      
对于二分的检查函数，可以通过 $\mathcal{O}(n)$ 的树型 dp 来完成。
      
- 假设当前的检查的操作数为 $x$。$\mathcal{O}(n)$ 地计算所有节点的操作数，定义节点 $u$ 的操作数为 $f_u$。
- 定义使以 $u$ 为根节点的子树变为 $0$ 的额外操作数为 $h_u$。使以 $u$ 为根节点的子树变为 $0$ 的总操作数为 $need = \sum\limits_{v \in son(u)} h_v + a_i$。
- $need \ge f_u$，$h_u = need - f_u$。
        - $need \lt f_u$，必然会有多余的操作，两次多余的操作间可以抵消，所以 $h_u = (f_u - need) \bmod 2$。
      - 检查 $h_u$ 是否等于 $0$，等于 $0$ 说明操作次数为 $x$ 可行。
      
时间复杂度为 $\mathcal{O}(n^2\log V)$，$V$ 为二分上界。[代码](https://codeforces.com/contest/2035/submission/303221949)。
      
本题可以通过确定二分上下界优化成 $\mathcal{O}(n\log na_i+n^2\log n)$。同时能证明总是有解。
      
先解决一个更为简单的问题。使树上所有节点的权值不大于 $0$ 的最小操作数。与上述树形 dp 的流程大致相同，只是当 $need \lt f_u$ 时令 $h_u = 0$。
      
可以二分出一个下界 $t$。同时对于原问题，$t$ 次操作后可以令原树的节点的权值全部变为 $0$ 或 $1$，原问题的下界肯定不小于 $t$，这很显然。且上界不大于 $t + n^2 + 2n + 1$。接下来仅考虑最坏情况。考虑将所有节点的权值变为同一个数。
      
- 定义所有节点的权值和的奇偶性为树的奇偶性。每 $n$ 次操作可以令整棵树的节点翻转。如果每 $n$ 次操作，除了根节点 $R$ 以外的节点全部翻转，那么会多出一次操作能用来使另一个节点保持原状，从而改变奇偶性，从而可以接近所有节点权值相同的情况。那么，此处最多为**大致** $n^2$ 次操作。
- 而如果此时 $R$ 与其他值都不同。可以通过最差 $n + 1$ 次操作改变：不改变 $R$，改变一个节点 $2$ 次。如果全部是 $1$，再通过 $n$ 次操作变为 $0$。
      
确定上下界后和原来一样二分就好。
      
二分区间长为 $(n + 1)^2$，找出 $t$ 的时间复杂度为 $\mathcal{O}(n\log (n\max\limits_{i = 1}^{n}(a_i)))$，最后二分的时间复杂度为 $\mathcal{O}(n\log n^2)$。总复杂度为 $\mathcal{O}(n\log (na_i) + n\log n)$。[代码](https://codeforces.com/contest/2035/submission/303061603)。

---

