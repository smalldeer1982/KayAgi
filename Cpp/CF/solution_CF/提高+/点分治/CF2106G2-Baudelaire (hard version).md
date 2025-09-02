# Baudelaire (hard version)

## 题目描述

这是该问题的困难版本。两个版本之间的唯一区别在于，在困难版本中树的形态可以是任意的。

本题是交互题。

波德莱尔非常富有，因此他购买了一棵大小为 $n$ 的树，这棵树以某个任意节点为根。此外，每个节点的值为 $1$ 或 $-1$。

书呆子牛看到了这棵树并爱上了它。然而计算机科学的收入不足以让他买下这棵树。波德莱尔决定和书呆子牛玩一个游戏，如果他赢了，就把这棵树送给他。

书呆子牛不知道哪个节点是根，也不知道节点的值。但他可以向波德莱尔提出两种类型的查询：

1. `1 k u₁ u₂ ... uₖ`：设 $f(u)$ 为从树的根到节点 $u$ 的路径上所有节点的值之和。书呆子牛可以选择一个整数 $k$（$1 \le k \le n$）和 $k$ 个节点 $u_1, u_2, ..., u_k$，然后他会收到值 $f(u_1) + f(u_2) + ... + f(u_k)$。
2. `2 u`：波德莱尔将切换节点 $u$ 的值。具体来说，如果 $u$ 的值为 $1$，则变为 $-1$，反之亦然。

如果书呆子牛在总共 $n + 200$ 次查询内正确猜出每个节点的值（即执行查询后树的最终值），他就获胜。你能帮助他获胜吗？

## 说明/提示

在第一个示例中，树的根是节点 $4$，初始值为 $[-1, -1, -1, 1]$（第 $i$ 个值是节点 $i$ 的值）。

初始时，$f(1) = 0$，$f(2) = 0$，$f(3) = -1$，$f(4) = 1$。因此，第一个查询的答案是 $f(1) + f(2) + f(4) = 1$，第二个查询的答案是 $f(3) + f(1) = -1$。

在切换节点 $4$ 的值后，值变为 $[-1, -1, -1, -1]$。此时 $f(1) = -2$，$f(2) = -2$，$f(3) = -3$，$f(4) = -1$。因此 $f(1) + f(2) + f(4) = -5$，$f(3) + f(1) = -5$。

我们最终回答节点的值为 $[-1, -1, -1, -1]$，这是正确的。注意我们报告的是节点在变化后的值，而不是之前的值。

在第二个示例中，树的根是 $2$，初始值为 $[1, 1]$。

在最后一个示例中，树的根是 $1$，初始值为 $[-1, 1, 1, 1, 1, 1, -1]$。

注意这只是一个解释查询如何工作的示例，并不涉及具体的解题策略。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
4
1 4
4 2
2 3

1

-1


-5

-5

2
1 2

2

7
1 2
2 7
7 3
7 4
7 5
7 6

-1```

### 输出

```
? 1 3 1 2 4

? 1 2 3 1

? 2 4
? 1 3 1 2 4

? 1 2 3 1

! -1 -1 -1 -1


? 1 1 1

! 1 1






? 1 1 1

! -1 1 1 1 1 1 -1```

# 题解

## 作者：SUNCHAOYI (赞：0)

由 G1 可知，只要能确定根节点的位置，就能够用 $n$ 次操作获得答案。因此，本题就需要在不超过 $200$ 次的询问中获得根节点的位置。

设当前点为 $u$，与 $u$ 相邻的点组成集合 $S$。若当前询问集合 $Q$ 满足，$Q \subset S$，则可以进行操作：

1. 用 $1$ 操作询问 $Q$，获得答案 $sx$。
2. 进行 $2$ 操作，翻转 $u$。
3. 再次用 $1$ 操作询问 $Q$，获得答案 $sy$。

可以发现，若 $|sx - sy| = 2 \times |Q|$，则 $Q$ 中不存在 $u$ 的父亲节点。

利用这个性质，可以先找到以 $u$ 为子树的重心 $c$，然后将 $c$ 所有相邻的点加入集合中，通过二分法找到哪一个子结点与根距离最近。具体来说，分为以下情况：

- $c$ 已经不存在相邻点--此时 $c$ 即为所求。
- 询问 $c$ 所有相邻的点且符合以上条件-- $c$ 为所求。
- 剩下的情况就进行二分操作。

综上所述，至多需要约 $n + 3 \times \lceil\log (n)\rceil$ 次询问之后就能找到根节点。最后进行一次 dfs 并询问即可求出答案。

```cpp
#include <bits/stdc++.h>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define pii pair <int,int>
using namespace std;
const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int t,n;
int main ()
{
    t = read ();
    while (t--)
    {
        n = read ();
        int tot = 0,c = 0;
        vector <int> ans (n + 1),sz (n + 1),w (n + 1),vis (n + 1,0);
        vector <vector <int>> ve (n + 1);
        for (int i = 1;i < n;++i) 
        {
            int u = read (),v = read ();
            ve[u].push_back (v);ve[v].push_back (u);
        }
        auto query1 = [&] (vector <int> p) -> int
        {
            printf ("? 1 %d ",p.size ());
            for (auto v : p) printf ("%d ",v);
            puts ("");fflush (stdout);
            return read ();
        };
        auto query2 = [&] (int x) -> void {printf ("? 2 %d\n",x);fflush (stdout);};
        auto dfs1 = [&] (auto self,int u,int fa) -> void
        {
            sz[u] = 1;
            for (auto v : ve[u])
            {
                if (v == fa || vis[v]) continue;
                self (self,v,u);
                sz[u] += sz[v];
            }
        };
        auto dfs2 = [&] (auto self,int u,int fa,int pre) -> void
        {
            ans[u] = query1 ({u}) - pre;
            for (auto v : ve[u])
            {
                if (v == fa) continue;
                self (self,v,u,pre + ans[u]);
            }
        };
        auto cen = [&] (auto self,int u,int fa) -> void
        {
            sz[u] = 1;w[u] = 0;
            for (auto v : ve[u])
            {
                if (v == fa || vis[v]) continue;
                self (self,v,u);
                sz[u] += sz[v];
                w[u] = max (w[u],sz[v]);
            }
            w[u] = max (w[u],tot - sz[u]);
            if (w[u] <= tot / 2) c = u;
        };
        auto ask = [&] (vector <int> p) -> pii
        {
            int sx = query1 (p);query2 (c);int sy = query1 (p);
            return {sx,sy};
        };
        auto solve = [&] (auto self,int u) -> int // 找 rt
        {
            dfs1 (dfs1,u,u);tot = sz[u];
            cen (cen,u,u);vis[c] = 1;
            vector <int> g;
            for (auto v : ve[c])
                if (!vis[v]) g.push_back (v);
            if (g.empty ()) return c;//已经找到 rt
            int l = 0,r = g.size () - 1,res = 0;
            auto [sx,sy] = ask (g);
            if (abs (sx - sy) == 2 * g.size ()) return c;//重心即为 rt
            while (l <= r)
            {
                int mid = (l + r) >> 1;
                vector <int> tmp;
                for (int i = 0;i <= mid;++i) tmp.push_back (g[i]);
                auto [sx,sy] = ask (tmp);
                if (abs (sx - sy) == 2 * tmp.size ()) l = mid + 1;
                else res = mid,r = mid - 1;
            }
            return self (self,g[res]);
        };
        dfs2 (dfs2,solve (solve,1),0,0);
        printf ("! ");
        for (int i = 1;i <= n;++i) printf ("%d ",ans[i]);
        puts ("");fflush (stdout);
    }
    return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
    {
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

