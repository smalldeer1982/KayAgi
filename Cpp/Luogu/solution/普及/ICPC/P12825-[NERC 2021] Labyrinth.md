# [NERC 2021] Labyrinth

## 题目描述

Leslie 和 Leon 进入了一个迷宫。这个迷宫由 $n$ 个大厅和 $m$ 条单向通道组成，大厅编号为 $1$ 到 $n$。

Leslie 和 Leon 从大厅 $s$ 开始他们的探险。很快他们发生了争吵，决定分开探索迷宫。不过，他们希望在旅程结束时能够再次相遇。

为了帮助 Leslie 和 Leon，你的任务是找到从给定大厅 $s$ 到另一个大厅 $t$ 的两条不同路径，且这两条路径除了起点 $s$ 和终点 $t$ 外不共享任何其他大厅。终点 $t$ 尚未确定，因此你可以选择迷宫中除 $s$ 外的任意大厅作为 $t$。

Leslie 和 Leon 的路径不必是最短路径，但必须是简单路径（即不重复访问任何大厅）。此外，在旅程中除了 $s$ 和 $t$ 外，他们不能访问任何共同的大厅，即使是在不同时间访问也不行。


## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5 5 1
1 2
2 3
1 4
4 3
3 5```

### 输出

```
Possible
3
1 2 3
3
1 4 3```

## 样例 #2

### 输入

```
5 5 1
1 2
2 3
3 4
2 5
5 4```

### 输出

```
Impossible```

## 样例 #3

### 输入

```
3 3 2
1 2
2 3
3 1```

### 输出

```
Impossible```

# 题解

## 作者：封禁用户 (赞：3)

# 洛谷P12825 [NERC 2021] Labyrinth 题解

## 题外话
~~看到简单路径就有了大大滴思路，没想到调了两年半。。。~~

## 算法分析&介绍
### ~~不完全~~错误算法
千万别看到“路径”就只想到“最短路径”。首先题目说了 **Leslie 和 Leon 的路径不必是最短路径，但必须是简单路径（即不重复访问任何大厅）**，就是说只要不怕麻烦，打个最短路径也是可以的 ~~（能不能AC就不知道了）~~。
### 正确算法
由于是单向通道且没有环，我们可以考虑 BFS 树+祖先标记。
### 正确算法的步骤
1. **BFS 遍历与祖先标记**：从起点 $s$ 开始进行 BFS 遍历，记录每个节点的深度、父节点和祖先节点（从 $s$ 出发的第一条边指向的节点）。

2. **寻找汇合点**：在 BFS 遍历过程中，对于每条边 $(u, v)$
- 如果 $v$ 未被访问，则正常入队，并记录其深度、父节点和祖先节点。
- 如果 $v$ 已被访问，且当前节点 $u$ 的祖先节点与 $v$ 的祖先节点不同，则找到满足条件的终点 $t = v$。

3. **路径重建**：找到汇合点 t 后：
- 第一条路径：沿 BFS 树中 $t$ 到 $s$ 的路径重建。
- 第二条路径：沿 $t \to u \to s$ 的路径重建（$u$ 是发现汇合点时的当前节点）。

4. **无解情况**：若 BFS 结束后未找到满足条件的汇合点，则输出 `Impossible`。

## 时间复杂度
$O(n+m)$，包过的。

## AC Code

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0)，cout.tie(0);

    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    vector<int> d(n + 1, -1);
    vector<int> p(n + 1, -1);
    vector<int> anc(n + 1, -1);
    queue<int> q;
    d[s] = 0;
    q.push(s);

    int t = -1, u_ = -1;

    while (!q.empty() && t == -1) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (v == s) continue;

            if (d[v] == -1) {
                d[v] = d[u] + 1;
                p[v] = u;
                if (u == s) anc[v] = v;
                else anc[v] = anc[u];
                q.push(v);
            } else {
                if (u == s) {
                    if (anc[v] != v) {
                        t = v;
                        u_ = u;
                        break;
                    }
                } else {
                    if (anc[u] != anc[v]) {
                        t = v;
                        u_ = u;
                        break;
                    }
                }
            }
        }
    }

    if (t == -1) {
        cout << "Impossible" << endl;
    } else {
        vector<int> p1;
        int cur = t;
        while (cur != s) {
            p1.push_back(cur);
            cur = p[cur];
        }
        p1.push_back(s);
        reverse(p1.begin(), p1.end());

        vector<int> p2;
        p2.push_back(t);
        if (u_ != s) {
            p2.push_back(u_);
            cur = u_;
            while (cur != s) {
                cur = p[cur];
                p2.push_back(cur);
            }
        } else {
            p2.push_back(s);
        }
        reverse(p2.begin(), p2.end());

        cout << "Possible" << endl;
        cout << p1.size() << endl;
        for (int i = 0; i < p1.size(); ++i) {
            if (i > 0) cout << " ";
            cout << p1[i];
        }
        cout << endl;

        cout << p2.size() << endl;
        for (int i = 0; i < p2.size(); ++i) {
            if (i > 0) cout << " ";
            cout << p2[i];
        }
        cout << endl;
    }

    return 0;
}
```
撒花！

---

