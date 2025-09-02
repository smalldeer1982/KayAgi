# 题目信息

# [CERC2015] Kernel Knights

## 题目描述

Jousting is a medieval contest that involves people on horseback trying to strike each other with wooden lances while riding at high speed. A total of 2n knights have entered a jousting tournament – n knights from each of the two great rival houses. Upon arrival, each knight has challenged a single knight from the other house to a duel. 

A kernel is deﬁned as some subset S of knights with the following two properties:

• No knight in S was challenged by another knight in S. 

• Every knight not in S was challenged by some knight in S.

Given the set of the challenges issued, ﬁnd one kernel. It is guaranteed that a kernel always exists.

## 说明/提示

Central Europe Regional Contest 2015 Problem K



## 样例 #1

### 输入

```
4 
5 6 7 7 
1 3 2 3```

### 输出

```
1 2 4 8```

# AI分析结果



### 算法分类
图论（拓扑排序与基环树处理）

### 题解分析与结论
题目核心是构造满足条件的骑士集合（Kernel），所有题解均基于以下思路：
1. **入度为0的节点必选**：未被挑战的骑士必须加入集合。
2. **队列处理依赖关系**：将必选骑士的攻击对象排除，并更新其攻击目标的入度。若入度归零，则加入队列。
3. **处理剩余环结构**：题目保证解存在，剩余未被处理的环结构通过红蓝编号差异自动处理（红方默认优先加入，蓝方需显式标记）。

### 高星题解推荐
#### 1. TsH_GD（4星）
**关键亮点**：
- 明确处理重复标记问题，避免重复减少入度导致错误。
- 代码结构简洁，注释清晰。
```cpp
// 核心代码片段（处理队列逻辑）
while (!q.empty()) {
    int p = q.front(); q.pop();
    k[p] = 1;
    if (k[a[p]] == -1) continue; // 避免重复处理
    k[a[p]] = -1;
    d[a[a[p]]]--;
    if (d[a[a[p]]] == 0) q.push(a[a[p]]);
}
```
**个人心得**：通过注释强调检查重复处理是避免WA的关键。

#### 2. copper_ingot（4星）
**关键亮点**：
- 显式分析定理并处理环结构，确保解的正确性。
- 明确红蓝骑士的输出规则，逻辑更严谨。
```cpp
// 核心输出逻辑（处理剩余环）
for (int i = 1; i <= n; i++) if (ok[i] != -1) printf("%d ", i); // 红方默认加入
for (int i = n + 1; i <= n * 2; i++) if (ok[i] == 1) printf("%d ", i); // 蓝方需显式标记
```

#### 3. Lain_yc（4星）
**关键亮点**：
- 代码注释幽默且实用，强调多测清空的重要性。
- 输出条件简洁，避免冗余判断。
```cpp
// 输出逻辑简化
for (int i = 1; i <= m; i++) {
    if (i <= n && s[i] >= 0 || i > n && s[i] == 1) cout << i << " ";
}
```

### 最优关键思路
1. **拓扑排序处理入度**：用队列维护入度为0的节点，确保必选骑士优先处理。
2. **状态标记防重复**：通过标记数组避免重复操作，确保每个节点只处理一次。
3. **红蓝编号差异处理环**：剩余环结构利用红方默认加入规则构造合法解。

### 拓展与举一反三
- **类似题目**：基环树（P2661 信息传递）、拓扑排序（P1347 排序）、环结构处理（P3385 判环）。
- **算法套路**：出度为1的有向图问题，通常结合拓扑排序与环处理。

### 推荐题目
1. [P2661 信息传递](https://www.luogu.com.cn/problem/P2661)（基环树与环检测）
2. [P1347 排序](https://www.luogu.com.cn/problem/P1347)（拓扑排序应用）
3. [P3385 判负环](https://www.luogu.com.cn/problem/P3385)（环结构与BFS结合）

---
处理用时：119.25秒