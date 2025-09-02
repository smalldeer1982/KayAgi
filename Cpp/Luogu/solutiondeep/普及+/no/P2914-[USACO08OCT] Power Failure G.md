# 题目信息

# [USACO08OCT] Power Failure G

## 题目描述

A vicious thunderstorm has destroyed some of the wires of the farm's electrical power grid! Farmer John has a map of all $N$ ($2\le N \le 1000$) of the powerpoles, which are conveniently numbered $1\ldots N$ and located on integer plane coordinates $(x_i,y_i)$ ($-100000 \le x_i \le 100000, -100000 \le y_i \le 100000$).

Some $W$ ($1 \le W \le 10000$) power wires connect pairs of power poles $P_i$ and $P_j$ ($1 \le Pi \le N, 1 \le Pj \le N$).

He needs to get power from pole $1$ to pole $N$ (which means that some series of wires can traverse from pole $1$ to pole $N$, probably through some intermediate set of poles).

Given the locations of the $N$ poles and the list of remaining power wires, determine the minimum length of power wire required to restore the electrical connection so that electricity can flow from pole $1$ to pole $N$.  No wire can be longer than some real number $M$ ($0.0 < M \le 200000.0$).

As an example, below on the left is a map of the $9$ poles and $3$ wires after the storm. For this task, $M = 2.0$. The best set of wires to add would connect poles $4$ and $6$ and also poles $6$ and $9$.

```cpp
   After the storm              Optimally reconnected
3  . . . 7 9 . . . . .          3  . . . 7 9 . . . . .
                                          /
2  . . 5 6 . . . . . .          2  . . 5 6 . . . . . .
                                        /
1  2-3-4 . 8 . . . . .          1  2-3-4 . 8 . . . . .
   |                               |
0  1 . . . . . . . . .          0  1 . . . . . . . . .

   0 1 2 3 4 5 6 7 8 9             0 1 2 3 4 5 6 7 8 9
```

The total length is then $1.414213562 + 1.414213562 = 2.828427124$.

POINTS: 350


## 说明/提示

Just as in the diagram above.


As above.


## 样例 #1

### 输入

```
9 3 
2.0 
0 0 
0 1 
1 1 
2 1 
2 2 
3 2 
3 3 
4 1 
4 3 
1 2 
2 3 
3 4 
```

### 输出

```
2828 
```

# AI分析结果



**算法分类**: 最短路

---

### 综合分析与结论
题目本质是单源最短路问题，需建立包含原有电线（边权0）和可补充电线（边权为几何距离且 ≤ M）的图，求 1→n 的最短路径。所有题解均采用最短路算法，核心差异在于建图细节和算法优化：

1. **建图关键**：正确处理已有电线（权值0）和潜在电线（需判断距离 ≤ M），注意坐标距离计算时的数值溢出（使用 long long 或浮点型中间变量）。
2. **算法选择**：Dijkstra（普通或堆优化）为主，SPFA 在部分题解中出现但需注意数据规模。
3. **优化点**：堆优化 Dijkstra 更适合大规模数据，避免 O(n²) 时间；正确处理浮点精度和输出格式（×1000 后取整）。

---

### 精选题解与亮点

#### 1. 作者：伟大的王夫子（5星）
**关键亮点**：
- **堆优化 Dijkstra**，时间复杂度 O((n+m) log n)，优于普通实现。
- **显式处理浮点精度**，输出时使用 `floor` 确保正确截断。
- **代码简洁**，变量命名清晰，优先队列使用规范。

**核心代码**：
```cpp
priority_queue<pair<double, int>> q;
for (int i = 1; i <= n; ++i) d[i] = 1e18;
q.push({0.0, 1});
d[1] = 0;
while (q.size()) {
    int x = q.top().second; q.pop();
    if (v[x]) continue;
    v[x] = 1;
    for (int i = 1; i <= n; ++i) {
        double z = a[x][i];
        if (z == 1e18) continue;
        if (d[i] > d[x] + z) {
            d[i] = d[x] + z;
            q.push({-d[i], i});
        }
    }
}
```

#### 2. 作者：火车司机（4星）
**关键亮点**：
- **前向星建图**，节省空间，适合稀疏图。
- **显式处理无向边**，双重 add 操作确保双向连接。
- **SPFA 实现**，队列优化避免重复松弛。

**个人心得**：
> "注意输出格式要求乘 1000 后取整，否则会 WA 掉部分测试点。"

---

### 最优思路总结
1. **建图技巧**：将原有电线视为零权边，潜在电线按几何距离建边（需 ≤ M）。
2. **数值安全**：计算几何距离时使用 `hypot` 或显式转换类型避免溢出。
3. **算法优化**：优先选择堆优化 Dijkstra，平衡时间与代码复杂度。

---

### 拓展与相似题目
1. **P4779** [【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
2. **P1629** [邮递员送信](https://www.luogu.com.cn/problem/P1629)（反向建图技巧）
3. **P1661** [扩散](https://www.luogu.com.cn/problem/P1661)（坐标建图 + 最小生成树）

---
处理用时：52.22秒