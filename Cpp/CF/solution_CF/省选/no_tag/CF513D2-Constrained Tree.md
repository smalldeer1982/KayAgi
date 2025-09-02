# Constrained Tree

## 题目描述

给定一个大小为 $n$ 的二叉树，你需要找到这样一棵树，使其满足 $c$ 个给定的约束。二叉树的节点按照前序遍历进行编号，从 $1$ 开始。对于第 $i$ 个约束，我们有两个编号 $a_i$ 和 $b_i$，以及一个方向（“左”或“右”）。如果方向是“左”，那么节点 $b_i$ 必须在节点 $a_i$ 的左子树中。同样，如果方向是“右”，那么节点 $b_i$ 必须在节点 $a_i$ 的右子树中。

## 说明/提示

考虑一个例子：找一棵有 3 个节点的树，满足两个条件：节点 2 要在节点 1 的左子树中，节点 3 要在节点 1 的右子树中。唯一符合条件的树的中序遍历结果是 $(2, 1, 3)$。

前序遍历顺序是“根-左子树-右子树”，中序遍历是“左子树-根-右子树”。

想了解更多关于遍历的信息，可以访问 [Tree Traversal on Wikipedia](http://en.wikipedia.org/wiki/Tree_traversal)。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3 2
1 2 LEFT
1 3 RIGHT
```

### 输出

```
2 1 3
```

## 样例 #2

### 输入

```
3 2
1 2 RIGHT
1 3 LEFT
```

### 输出

```
IMPOSSIBLE
```

# 题解

## 作者：紊莫 (赞：0)

官方做法。

题目给出的要求是构造一个 $n$ 个点的树，使得满足若干个限制，那么根据中序遍历的性质，我们可以知道若 $i, j$ 在同一子树中，那么所有 $i < k < j$ 也一定在这个子树中，我们需要维护的实际上只是一个最大最小值构成的区间。

我们可以将题目的要求转化为构造一棵树，点数尽可能的少，同时要满足 $n$ 在树内，同时满足上述限制。

尝试解决这个问题，首先按照题目的要求，建立出若干个父子关系，维护出每个点的左右儿子的最大值，最小值。

然后我们进行一次 ``dfs(n)``，表示要求 $n$ 在子树内的，返回值就是是否可行。

我们在外层记录一个当前节点编号 $cnt$，递归一次就新建一个点（题目要求的先序遍历），然后先遍历左儿子，记录中序遍历的顺序，然后遍历右儿子。

若有左儿子，那么考虑何时非法。

如果左边的最小值小于等于当前节点，那显然无解，否则我们递归的下去判断左边，要求左边的最大值在左儿子内，若不可行，也无解。

然后是右儿子，递归的时候需要改变一下，要求 $\max (n, Rmax)$ 在右儿子。

如果没有右儿子，那么需要判断 $cnt < u$ 这是无解的，因为子树中不可能有 $u$ 了（没地方放了），然后递归求解即可。

参考代码：

```cpp
#include <bits/stdc++.h>
#define int long long

#define F(i, a, b) for (int i = (a); i <= (b); i++)
#define dF(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int N = 1000005, M = (N << 1), inf = 1e16, mod = 1e9 + 7;
int n, m, cnt, mn[N][2], mx[N][2];
vector<int> g[N][2], an;
int dfs(int u) {
    int now = ++ cnt;
    if (g[now][0].size())
        if (mn[now][0] <= cnt || !dfs(mx[now][0]))
            return 0;
    an.push_back(now);
    if (g[now][1].size()) {
        if (mn[now][1] <= cnt || !dfs(max(u, mx[now][1])))
            return 0;
    } else if (cnt < u && !dfs(u)) return 0;
    return 1;
}
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    F(i, 1, m) {
        int x, y;
        string s;
        cin >> x >> y >> s;
        g[x][s[0] == 'R'].push_back(y);
    }
    F(i, 1, n) {
        sort(g[i][0].begin(), g[i][0].end());
        if (g[i][0].size()) 
            mn[i][0] = g[i][0][0], mx[i][0] = g[i][0].back();
        sort(g[i][1].begin(), g[i][1].end());
        if (g[i][1].size()) 
            mn[i][1] = g[i][1][0], mx[i][1] = g[i][1].back();
    }
    if (dfs(n)) {
        for (auto i : an) cout << i << ' ';
    } else cout << "IMPOSSIBLE";
    return 0;
}

```

---

