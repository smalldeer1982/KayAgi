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
这些题解主要围绕有向无环图（DAG）上求最长路径及字典序最小路径的问题展开。整体思路是先求出最长路径，再处理字典序最小的问题。各题解的差异在于处理字典序最小路径的方法，主要有拓扑序动态规划结合排名、倍增哈希两种思路。拓扑序动态规划结合排名通过对节点按最长路径长度分层，在每层中依据边权和后继节点排名确定最优转移；倍增哈希则利用哈希和倍增数组快速比较路径字典序。

### 所选题解
- 作者：0000pnc (赞：15)，4星
  - 关键亮点：思路清晰，先通过拓扑序 dp 求最长路，再利用拓扑序 dp 过程结合优先队列确定字典序最小路径，时间复杂度较优。
- 作者：yuanruiqi (赞：7)，4星
  - 关键亮点：将点按最长路长度分层，只保留相邻层的边，按层处理，通过排序确定字典序排名和答案，代码简洁。
- 作者：学委 (赞：2)，4星
  - 关键亮点：对出度为 0 的点优先拓扑排序，考虑后继节点深度、边权和后继节点排名确定最优路径，复杂度分析清晰。

### 重点代码及核心实现思想
#### 0000pnc 的题解
```cpp
// 拓扑排序
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

// 求最长路
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

// 求字典序最小路径
void bfs() {
    topo(); dp();
    priority_queue<res> pq;
    int mxdep = 0;
    for (int i = 1; i <= n; i++) {
        int x = id[i];
        if (dep[x] != mxdep) {
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
核心思想：先拓扑排序得到拓扑序，再根据拓扑序 dp 求出最长路，最后通过优先队列处理字典序最小路径。在处理字典序时，按最长路长度分层，每层中先确定最小边权，再选择后继节点排名最大的路径。

#### yuanruiqi 的题解
```cpp
// 求最长路
void dfs(int u) {
    for (int i=h[u];i;i=e[i].nxt) {
        int v = e[i].v;
        if (!dep[v]) dfs(v);
        dep[u] = max(dep[u], dep[v]);
    }
    ++dep[u];
}

// 求字典序最小路径
for (int t=2;t<=n&&c[t].size();++t) {
    int top = 0;
    for (int u : c[t]) {
        int mn = 0, to = 0;
        for (int i=h[u];i;i=e[i].nxt) {
            int v = e[i].v;
            if (dep[v] != dep[u] - 1) continue;
            if (!to || mn > e[i].w || (mn == e[i].w && rk[v] < rk[to])) {
                to = v;
                mn = e[i].w;
            }
        }
        ans[u] = mn + ans[to];
        sa[++top] = (ppi(mn, rk[to], u));
    }
    sort(sa+1, sa+top+1, cmp());
    for (int i=1;i<=top;++i) rk[sa[i].z] = ++tot;
}
```
核心思想：通过 dfs 求出最长路，将点按最长路长度分层，按层处理。对于每层的点，枚举其出边，选择边权最小且后继节点排名最小的路径，然后对当前层的点排序确定排名。

#### 学委的题解
```cpp
// 拓扑排序并处理最长路和字典序最小路径
vector<int> cur_len_nodes;
vector<int> nxt_len_nodes;
for (int i = 1; i <= n; i++) {
    if (!out[i]) {
        dep[i] = 1;
        cur_len_nodes.push_back(i);
        sum[i] = 0;
    }
}
int cur_len = 1;
while (!cur_len_nodes.empty()) {
    ++cur_len;
    for (int v: cur_len_nodes) {
        for (int u: own[v]) {
            if (--out[u] == 0) {
                nxt_len_nodes.push_back(u);
                dep[u] = cur_len;
                ansl[u] = 1e9 + 7;
            }
        }
    }
    for (int u: nxt_len_nodes) {
        for (int i = 0; i < e[u].size(); i++) {
            int v = e[u][i];
            int l = w[u][i];
            if (dep[v] == cur_len - 1) {
                if (l < ansl[u]) {
                    ansl[u] = l;
                    nxt[u] = v;
                    sum[u] = sum[v] + l;
                } else if (l == ansl[u] && rnk[v] < rnk[nxt[u]]) {
                    nxt[u] = v;
                    sum[u] = sum[v] + l;
                }
            }
        }
    }
    int cnt = 0;
    for (int u: nxt_len_nodes) {
        ids[++cnt] = u;
    }
    sort(ids + 1, ids + cnt + 1, [&](const int& a, const int& b) {
        if (ansl[a] != ansl[b])
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
核心思想：对出度为 0 的点优先拓扑排序，按最长路长度分层处理。对于每层的点，选择边权最小且后继节点排名最小的路径，然后对当前层的点排序确定排名。

### 最优关键思路或技巧
- **拓扑序动态规划**：利用拓扑序对 DAG 进行动态规划，可高效求出最长路。
- **分层处理**：将节点按最长路长度分层，只考虑相邻层的边，简化问题。
- **排名机制**：通过排名确定字典序最小路径，避免直接比较路径序列。
- **倍增哈希**：利用哈希和倍增数组快速比较路径字典序，降低时间复杂度。

### 可拓展之处
同类型题如在 DAG 上求最短路径且路径字典序最小，或在有环图上处理类似问题（可使用 Tarjan 算法缩点转化为 DAG）。类似算法套路可用于处理其他需要比较序列字典序的问题，如字符串匹配、树的同构判断等。

### 推荐洛谷题目
- P1137 旅行计划：DAG 上的动态规划，求最长路径。
- P2419 [USACO08JAN]Cow Contest S：DAG 上的传递闭包问题。
- P3275 [SCOI2011]糖果：DAG 上的差分约束问题。

### 个人心得
部分作者提到题目难度和出题情况，如“关于这是金组 T2，二分/三分模板是 T3 这事……谁组的题啊喂！！！”，表达了对题目难度分布的看法。但整体题解中个人调试经历、踩坑教训等心得较少。 

---
处理用时：65.58秒