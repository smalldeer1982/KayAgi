# 题目信息

# [USACO23DEC] Minimum Longest Trip G

## 题目描述

Bessie 正在奶牛大陆上旅行。奶牛大陆由从 $1$ 到 $N$ 编号的 $N$（$2 \le N \le 2\cdot 10^5$）座城市和 $M$（$1 \le M \le 4\cdot 10^5$）条单向道路组成。第 $i$ 条路从城市 $a_i$ 通向城市 $b_i$，标签为 $l_i$。

由城市 $x_0$ 开始的长度为 $k$ 的旅程被定义为一个城市序列 $x_0,x_1,\ldots,x_k$，对于所有的 $0 \le i < k$，存在由城市 $x_i$ 到 $x_{i+1}$ 的路。保证在奶牛大路上不存在长度无限的旅程，不存在两条路连接一对相同的城市。

对于每座城市，Bessie 想知道从它开始的最长旅程。对于一些城市，从它们开始的最长旅程不唯一，Bessie 将选择其中道路标签序列字典序更小的旅程。一个序列比等长的另一个序列字典序更小，当且仅当在它们不同的第一个位置，前者比后者的元素更小。

输出 Bessie 在每座城市选择的旅途的长度和道路标签之和。

## 说明/提示

### 样例解释 2

在下面的解释中，我们用 $a_i\xrightarrow{l_i} b_i$ 表示由城市 $a_i$ 通往 $b_i$，标签为 $l_i$ 的单向道路。

从城市 $4$ 出发有多条旅程，包含 $4\xrightarrow{4} 3\xrightarrow 5 1$，$4\xrightarrow 1 1$ 和 $4\xrightarrow 2 2\xrightarrow{10} 1$。在这些旅程中，$4\xrightarrow{4} 3\xrightarrow 5 1$ 和 $4\xrightarrow 2 2\xrightarrow{10} 1$ 是最长的。它们的长度均为 $2$，道路标签序列分别为 $[4,5]$ 和 $[2,10]$。$[2,10]$ 是字典序更小的那一个，它的和为 $12$。

### 测试点性质

- 测试点 $5-6$ 满足所有道路的标签相同。
- 测试点 $7-8$ 满足所有道路的标签不相同。
- 测试点 $9-10$ 满足 $N,M \le 5000$。
- 测试点 $11-20$ 没有额外限制。

## 样例 #1

### 输入

```
4 5
4 3 10
4 2 10
3 1 10
2 1 10
4 1 10```

### 输出

```
0 0
1 10
1 10
2 20```

## 样例 #2

### 输入

```
4 5
4 3 4
4 2 2
3 1 5
2 1 10
4 1 1```

### 输出

```
0 0
1 10
1 5
2 12```

## 样例 #3

### 输入

```
4 5
4 3 2
4 2 2
3 1 5
2 1 10
4 1 1```

### 输出

```
0 0
1 10
1 5
2 7```

## 样例 #4

### 输入

```
4 5
4 3 2
4 2 2
3 1 10
2 1 5
4 1 1```

### 输出

```
0 0
1 5
1 10
2 7```

# AI分析结果

### 综合分析与结论
这些题解主要围绕在有向无环图（DAG）上求从每个点出发的最长路径，且在最长路径不唯一时选择边标签序列字典序更小的路径，并输出路径长度和边标签之和。
1. **思路与算法要点**：
    - 多数题解先通过拓扑排序确定图中节点的拓扑序，在此基础上进行动态规划（DP）来求解最长路径长度，这是解决本题的基础步骤。
    - 对于求字典序最小的路径，主要有两种思路：
        - **倍增哈希法**：通过倍增记录路径信息（如前驱节点、哈希值等），利用哈希快速比较路径字典序。在比较两条路径时，通过在倍增数组上跳来找到最长公共前缀，之后比较不同位置的哈希值确定字典序。
        - **分层排名法**：按最长路长度将点分层，只保留相邻层的边。从最小层级开始，对每个层级的点，枚举出边，按照边权和下一层点的排名来确定最佳转移，从而得到当前层点的排名和答案。
2. **解决难点**：
    - 难点在于高效地处理字典序最小路径的求解。朴素比较字典序的方法时间复杂度高，难以通过本题。倍增哈希法通过预处理和快速比较优化了字典序比较过程；分层排名法通过巧妙的分层和排名策略，避免了复杂的字典序比较操作。
3. **评分情况**：整体来看，0000pnc、yuanruiqi、学委的题解在思路清晰度、代码可读性和优化程度上表现较好，可评为4星及以上。

### 所选4星及以上题解
1. **0000pnc题解（4星）**：
    - **关键亮点**：采用拓扑序DP求最长路径长度，通过维护不同最长路长度的点的排名来处理字典序问题，使用优先队列简化操作，时间复杂度为 $\mathcal{O}(m + n\log n)$，思路清晰且实现简洁。
    - **重点代码（核心实现思想：拓扑排序、DP及字典序处理）**：
```cpp
void topo() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!siz[i]) q.push(i);
    }
    while (!q.empty()) {
        int x = q.front(); q.pop();
        tp[++tot] = x;
        for (auto tmp : v2[x]) {
            if (siz[tmp.to]) {
                siz[tmp.to]--;
                if (!siz[tmp.to]) q.push(tmp.to);
            }
        }
    }
}

void dp() {
    for (int i = 1; i <= n; i++) {
        int x = tp[i];
        for (auto tmp : v2[x]) {
            dep[tmp.to] = max(dep[tmp.to], dep[x] + 1);
        }
    }
    for (int i = 1; i <= n; i++) id[i] = i;
    sort(id + 1, id + n + 1, cmp);
}

void bfs() {
    topo(); dp();
    priority_queue<res> pq;
    int mxdep = 0;
    for (int i = 1; i <= n; i++) {
        int x = id[i];
        if (dep[x]!= mxdep) {
            mxdep = dep[x];
            while (!pq.empty()) {
                auto tmp = pq.top(); pq.pop();
                rk[tmp.to] = ++cnt;
            }
        }
        if (dep[x]) {
            int mn = 0x3f3f3f3f, mx = 0;
            for (auto tmp : v[x]) {
                if (dep[tmp.to] == dep[x] - 1) mn = min(mn, tmp.w);
            }
            for (auto tmp : v[x]) {
                if (dep[tmp.to] == dep[x] - 1 && tmp.w == mn) mx = max(mx, rk[tmp.to]);
            }
            for (auto tmp : v[x]) {
                if (dep[tmp.to] == dep[x] - 1 && tmp.w == mn && rk[tmp.to] == mx) {
                    ans[x] = ans[tmp.to] + tmp.w;
                    pq.push({tmp.w, rk[tmp.to], x});
                    break;
                }
            }
        }
        else pq.push({0, 0, x});
    }
}
```
2. **yuanruiqi题解（4星）**：
    - **关键亮点**：同样先拓扑排序求最长路径，再按最长路长度分层，通过归纳的方式，在每层中根据边权和下层点的排名来确定字典序最小的路径，逻辑清晰，代码简洁明了。
    - **重点代码（核心实现思想：DFS求最长路径、分层处理字典序）**：
```cpp
void dfs(int u) {
    for (int i = h[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (!dep[v]) dfs(v);
        dep[u] = max(dep[u], dep[v]);
    }
    ++dep[u];
}

//...

for (int i = 1; i <= n; i++)
    if (!dep[i]) dfs(i);
for (int i = 1; i <= n; i++)
    c[dep[i]].emplace_back(i);
for (int t = 2; t <= n && c[t].size(); ++t) {
    int top = 0;
    for (int u : c[t]) {
        int mn = 0, to = 0;
        for (int i = h[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if (dep[v]!= dep[u] - 1) continue;
            if (!to || mn > e[i].w || (mn == e[i].w && rk[v] < rk[to])) {
                to = v;
                mn = e[i].w;
            }
        }
        ans[u] = mn + ans[to];
        sa[++top] = (ppi(mn, rk[to], u));
    }
    sort(sa + 1, sa + top + 1, cmp());
    for (int i = 1; i <= top; i++) rk[sa[i].z] = ++tot;
}
```
3. **学委题解（4星）**：
    - **关键亮点**：对出度为0的点优先做拓扑排序，在处理每个点的后继时，通过对相同深度的后继点依据边权和排名进行比较，从而确定字典序最小的路径，复杂度分析清晰，代码可读性好。
    - **重点代码（核心实现思想：拓扑排序、按后继排名确定字典序）**：
```cpp
//...
while (!cur_len_nodes.empty()) {
    ++cur_len;
    for (int v : cur_len_nodes) {
        for (int u : own[v]) {
            if (--out[u] == 0) {
                nxt_len_nodes.push_back(u);
                dep[u] = cur_len;
                ansl[u] = 1e9 + 7;
            }
        }
    }
    for (int u : nxt_len_nodes) {
        for (int i = 0; i < e[u].size(); i++) {
            int v = e[u][i];
            int l = w[u][i];
            if (dep[v] == cur_len - 1) {
                if (l < ansl[u]) {
                    ansl[u] = l;
                    nxt[u] = v;
                    sum[u] = sum[v] + l;
                }
                else if (l == ansl[u] && rnk[v] < rnk[nxt[u]]) {
                    nxt[u] = v;
                    sum[u] = sum[v] + l;
                }
            }
        }
    }
    int cnt = 0;
    for (int u : nxt_len_nodes) {
        ids[++cnt] = u;
    }
    sort(ids + 1, ids + cnt + 1, [&](const int& a, const int& b) {
        if (ansl[a]!= ansl[b])
            return ansl[a] < ansl[b];
        return rnk[nxt[a]] < rnk[nxt[b]];
    });
    for (int i = 1; i <= cnt; i++) {
        rnk[ids[i]] = i;
    }
    swap(cur_len_nodes, nxt_len_nodes);
    nxt_len_nodes.clear();
}
```

### 最优关键思路或技巧
1. **分层处理**：按最长路长度将点分层，在每层内处理字典序问题，使得问题规模减小且逻辑清晰。如yuanruiqi和学委的题解，通过在层内根据边权和下层点的排名确定最优转移，避免了复杂的全局字典序比较。
2. **排名维护**：0000pnc和学委的题解中，通过维护不同层级点的排名，利用排名信息快速确定字典序最小的路径，优化了字典序比较的时间复杂度。

### 可拓展思路
1. **同类型题**：此类问题可拓展到更复杂的图结构或路径限制条件下，如带权有向图中求满足特定条件（如字典序、路径长度限制等）的最优路径。
2. **类似算法套路**：在处理涉及字典序比较的路径问题时，可考虑分层、排名维护等策略简化比较过程；对于高效比较序列字典序，倍增哈希是一种常用且有效的方法。

### 洛谷相似题目推荐
1. **P3387 【模板】缩点**：涉及有向图的处理，通过缩点将复杂有向图转化为DAG，之后可在DAG上进行类似的路径问题求解，与本题在图处理和路径分析上有相似思路。
2. **P2831 [NOIP2016 提高组] 愤怒的小鸟**：虽然不是传统的图论路径问题，但在状态转移和最优解选择上与本题有相似之处，都需要在多种可能中选择最优的情况，可锻炼类似的思维方式。
3. **P1807 最长路**：经典的DAG最长路问题，在此基础上可进一步思考如何加入字典序等限制条件，与本题的解题思路有延续性。

### 个人心得摘录与总结
暂未发现题解中有个人心得相关内容。 

---
处理用时：73.00秒