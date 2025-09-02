# 题目信息

# [USACO12FEB] Nearby Cows G

## 题目描述

Farmer John has noticed that his cows often move between nearby fields. Taking this into account, he wants to plant enough grass in each of his fields not only for the cows situated initially in that field, but also for cows visiting from nearby fields.

Specifically, FJ's farm consists of N fields (1 <= N <= 100,000), where some pairs of fields are connected with bi-directional trails (N-1 of them in total).  FJ has designed the farm so that between any two fields i and j, there is a unique path made up of trails connecting between i and j. Field i is home to C(i) cows, although cows sometimes move to a different field by crossing up to K trails (1 <= K <= 20).

FJ wants to plant enough grass in each field i to feed the maximum number of cows, M(i), that could possibly end up in that field -- that is, the number of cows that can potentially reach field i by following at most K trails.  Given the structure of FJ's farm and the value of C(i) for each field i, please help FJ compute M(i) for every field i.

给你一棵 $n$ 个点的树，点带权，对于每个节点求出距离它不超过 $k$ 的所有节点权值和 $m_i$。

## 说明/提示

There are 6 fields, with trails connecting (5,1), (3,6), (2,4), (2,1), and (3,2).  Field i has C(i) = i cows.


Field 1 has M(1) = 15 cows within a distance of 2 trails, etc.

【数据范围】  
对于 $100\%$ 的数据：$1 \le n \le 10^5$，$1 \le k \le 20$，$0 \le c_i \le 1000$

## 样例 #1

### 输入

```
6 2 
5 1 
3 6 
2 4 
2 1 
3 2 
1 
2 
3 
4 
5 
6 
```

### 输出

```
15 
21 
16 
10 
8 
11 
```

# AI分析结果



### 综合分析
所有题解均围绕树形DP展开，核心思路为两次DFS处理子树贡献与父链贡献，通过容斥消除重复计算。关键优化点在于利用「k≤20」的约束，将复杂度控制在O(nk)。多数解法采用f[i][j]表示节点i的j步内权值和，通过两次遍历分别处理子树内和跨父节点的贡献。

---

### 精选题解

#### 1. asuldb（★★★★☆）
**核心思路**：两次DFS + 动态容斥  
- 第一次DFS计算子树内贡献：`f[i][j] += ∑f[son][j-1]`  
- 第二次DFS利用父节点更新，并倒序消除重复：`f[son][j] += f[fa][j-1] - f[son][j-2]`  
**亮点**：  
- 清晰解释重复来源（子树被父节点重复统计）  
- 倒序循环防止覆盖中间状态  
- 代码注释明确，变量命名规范  

**关键代码**：
```cpp
void build(int r) { // 第一次DFS统计子树
    for(re int j=1;j<=k;j++)
        f[r][j] += f[son][j-1];
}
void dfs(int r) { // 第二次DFS处理父链贡献
    for(re int j=k;j>=2;j--)
        f[son][j] -= f[son][j-2]; // 倒序容斥
    for(re int j=1;j<=k;j++)
        f[son][j] += f[r][j-1];
}
```

#### 2. Yuyuanqi（★★★★☆）
**核心思路**：双数组分离子树与父链贡献  
- 定义`d[i][j]`为纯子树贡献，`f[i][j]`为总贡献  
- 父链转移公式：`f[v][j] += f[u][j-1] - d[v][j-2]`  
**亮点**：  
- 分离子树与总贡献更易理解  
- 预处理子树后统一合并结果  

**代码亮点**：
```cpp
void dfs2(int u) { // 父链贡献转移
    f[v][j] = d[v][j] + (f[u][j-1] - d[v][j-2]);
}
```

#### 3. 换根法（★★★☆☆）
**核心思路**：动态换根计算全局贡献  
- 预处理子树后，通过`cut/link`操作动态调整根节点  
- 复杂度相同但实现稍复杂  
**价值**：展示了换根DP的通用解法，适用于更复杂的树统计问题  

---

### 关键技巧总结
1. **两次遍历结构**：先子树后父链的遍历顺序是树形DP的经典模式  
2. **容斥优化**：通过`f[son][j-2]`消除父链转移中的重复子树贡献  
3. **倒序更新**：在父链更新时倒序处理j，防止状态覆盖  
4. **空间压缩**：利用k≤20的特性，使用二维数组而非邻接表存储中间结果  

---

### 推荐习题
1. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)  
   - 树形DP基础，处理节点选/不选的最优解  
2. [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)  
   - 树形DP+背包，维护子树保留边数  
3. [P1273 有线电视网](https://www.luogu.com.cn/problem/P1273)  
   - 树形DP结合收益计算，适合练习复杂状态转移  

---

### 个人心得摘录
> "调试时发现，父节点转移必须倒序处理j，否则会先覆盖j-2的状态" —— asuldb  
> **启示**：树形DP的状态更新顺序对正确性至关重要，需通过模拟小样例验证  
>  
> "多次WA后发现，根节点的父链贡献需要特殊处理" —— Yuyuanqi  
> **启示**：边界条件（如根节点、叶子节点）需单独验证，避免默认逻辑错误

---
处理用时：55.09秒