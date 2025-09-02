# 题目信息

# [ABC223D] Restricted Permutation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc223/tasks/abc223_d

$ (1,\ 2,\ \dots,\ N) $ を並び替えて得られる数列 $ P $ であって以下の条件を満たすもののうち、辞書順で最小のものを求めてください。

- $ i\ =\ 1,\ \dots,\ M $ に対し、$ P $ において $ A_i $ は $ B_i $ よりも先に現れる。

ただし、そのような $ P $ が存在しない場合は `-1` と出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ N $
- $ A_i\ \neq\ B_i $
- 入力は全て整数である。

### Sample Explanation 1

条件を満たす $ P $ は $ (2,\ 1,\ 3,\ 4),\ (2,\ 3,\ 1,\ 4),\ (2,\ 3,\ 4,\ 1),\ (3,\ 2,\ 1,\ 4),\ (3,\ 2,\ 4,\ 1) $ の $ 5 $ つです。これらのうち辞書順で最小のものは $ (2,\ 1,\ 3,\ 4) $ です。

### Sample Explanation 2

条件を満たす $ P $ は存在しません。

## 样例 #1

### 输入

```
4 3

2 1

3 4

2 4```

### 输出

```
2 1 3 4```

## 样例 #2

### 输入

```
2 3

1 2

1 2

2 1```

### 输出

```
-1```

# AI分析结果



# [ABC223D] Restricted Permutation 的题解翻译与解析

## 题目翻译
**题目描述**  
给定 $N$ 个元素的排列 $P$，需满足 $M$ 组约束条件，其中每组条件要求 $A_i$ 必须出现在 $B_i$ 之前。求满足所有条件且字典序最小的排列，若不存在则输出 `-1`。

**输入格式**  
第一行包含两个整数 $N$ 和 $M$，接下来 $M$ 行每行给出两个整数 $A_i$ 和 $B_i$。

**输出格式**  
输出满足条件的字典序最小排列，若无解输出 `-1`。

**样例解释**  
当存在多个可行解时，选择字典序最小的排列。例如样例1中满足条件的排列有5种，其中字典序最小的是 `2 1 3 4`。

## 算法分类
**图论（拓扑排序）**

---

## 题解分析与对比

### 核心思路
所有题解均采用拓扑排序的变种算法：
1. **建模为图**：将每个约束条件 $A_i \rightarrow B_i$ 转化为有向边。
2. **Kahn算法**：通过维护入度数组，逐步选择入度为0的节点。
3. **字典序优化**：使用小根堆（优先队列）维护当前可选的入度为0的节点，保证每次选择最小的元素。

### 题解评分与亮点
1. **ZnHF的题解（4星）**  
   - 亮点：代码结构清晰，变量命名规范，直接使用STL的小根堆实现。
   - 关键代码：
     ```cpp
     priority_queue<int, vector<int>, greater<int>> q;
     for (int i=1; i<=n; i++) if (!deg[i]) q.push(i);
     while (!q.empty()) {
         int u = q.top(); q.pop();
         ans.push_back(u);
         for (int v : g[u]) if (--deg[v] == 0) q.push(v);
     }
     ```
   
2. **xwh_hh的题解（4星）**  
   - 亮点：代码简洁高效，采用优先队列直接处理拓扑顺序。
   - 关键代码：
     ```cpp
     priority_queue<int, vector<int>, greater<int>> que;
     for (int i=1; i<=n; i++) if (!in[i]) que.push(i);
     while (!que.empty()) {
         int u = que.top(); que.pop();
         ans.push_back(u);
         for (int v : g[u]) if (--in[v] == 0) que.push(v);
     }
     ```

3. **___w的题解（4星）**  
   - 亮点：通过重载运算符实现小根堆，逻辑清晰但稍显复杂。
   - 关键代码：
     ```cpp
     struct node { int num; };
     bool operator<(node x, node y) { return x.num > y.num; }
     priority_queue<node> q;
     ```

### 最优思路总结
- **数据结构选择**：使用优先队列（小根堆）动态维护当前可选的节点。
- **环检测**：通过最终结果长度判断是否存在环。
- **时间复杂度**：$O((N+M)\log N)$，适用于大规模数据（$N \leq 2 \times 10^5$）。

---

## 拓展与同类题目
1. **同类型题目推荐**  
   - [P1137 旅行计划](https://www.luogu.com.cn/problem/P1137)（拓扑排序+DP）  
   - [P1983 车站分级](https://www.luogu.com.cn/problem/P1983)（拓扑排序处理层次关系）  
   - [P3243 [HNOI2015]菜肴制作](https://www.luogu.com.cn/problem/P3243)（反向拓扑求最大字典序）

2. **调试心得**  
   - **易错点**：建图时误将边设为双向（如某题解中的错误代码 `g[v].push_back(u)`）。
   - **优化技巧**：优先队列的初始化需遍历所有节点，确保初始入度为0的节点全部入队。

---

## 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5+5;
vector<int> g[N];
int in[N], n, m;

vector<int> topological_sort() {
    vector<int> res;
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i=1; i<=n; i++) 
        if (in[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.top(); q.pop();
        res.push_back(u);
        for (int v : g[u]) 
            if (--in[v] == 0) q.push(v);
    }
    return res.size() == n ? res : vector<int>();
}

int main() {
    cin >> n >> m;
    for (int i=0; i<m; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        in[b]++;
    }
    vector<int> ans = topological_sort();
    if (ans.empty()) cout << -1;
    else for (int x : ans) cout << x << ' ';
}
```

---
处理用时：58.33秒