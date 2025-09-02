# 题目信息

# Iris and the Tree

## 题目描述

Given a rooted tree with the root at vertex $ 1 $ . For any vertex $ i $ ( $ 1 < i \leq n $ ) in the tree, there is an edge connecting vertices $ i $ and $ p_i $ ( $ 1 \leq p_i < i $ ), with a weight equal to $ t_i $ .

Iris does not know the values of $ t_i $ , but she knows that $ \displaystyle\sum_{i=2}^n t_i = w $ and each of the $ t_i $ is a non-negative integer.

The vertices of the tree are numbered in a special way: the numbers of the vertices in each subtree are consecutive integers. In other words, the vertices of the tree are numbered in the order of a depth-first search.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006B/ed42d3ad002b849b19e2cab01dc8c80b05d343e1.png) The tree in this picture satisfies the condition. For example, in the subtree of vertex $ 2 $ , the vertex numbers are $ 2, 3, 4, 5 $ , which are consecutive integers.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006B/fbbdad2f1a4867f5d12408bb700e0a02f6731145.png) The tree in this picture does not satisfy the condition, as in the subtree of vertex $ 2 $ , the vertex numbers $ 2 $ and $ 4 $ are not consecutive integers.We define $ \operatorname{dist}(u, v) $ as the length of the simple path between vertices $ u $ and $ v $ in the tree.

Next, there will be $ n - 1 $ events:

- Iris is given integers $ x $ and $ y $ , indicating that $ t_x = y $ .

After each event, Iris wants to know the maximum possible value of $ \operatorname{dist}(i, i \bmod n + 1) $ independently for each $ i $ ( $ 1\le i\le n $ ). She only needs to know the sum of these $ n $ values. Please help Iris quickly get the answers.

Note that when calculating the maximum possible values of $ \operatorname{dist}(i, i \bmod n + 1) $ and $ \operatorname{dist}(j, j \bmod n + 1) $ for $ i \ne j $ , the unknown edge weights may be different.

## 说明/提示

In the first test case, $ \operatorname{dist}(1, 2) = \operatorname{dist}(2, 1) = t_2 = w = 10^{12} $ , so $ \operatorname{dist}(1, 2) + \operatorname{dist}(2, 1) = 2 \cdot 10^{12} $ .

In the second test case, the tree after Iris found out all $ t_x $ is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006B/cb4bc8b1d32fd5015d0673154cd358fe4ee772d9.png) $ \operatorname{dist}(1, 2) = t_2 $ , $ \operatorname{dist}(2, 3) = t_2 + t_3 $ , $ \operatorname{dist}(3, 4) = t_3 + t_4 $ , $ \operatorname{dist}(4, 1) = t_4 $ . After the first event, she found out that $ t_2 = 2 $ , so $ \operatorname{dist}(1, 2) = 2 $ . At the same time:

- $ \operatorname{dist}(2, 3) $ is maximized if $ t_3 = 7 $ , $ t_4 = 0 $ . Then $ \operatorname{dist}(2, 3) = 9 $ .
- $ \operatorname{dist}(3, 4) $ and $ \operatorname{dist}(4, 1) $ are maximized if $ t_3 = 0 $ , $ t_4 = 7 $ . Then $ \operatorname{dist}(3, 4) = \operatorname{dist}(4, 1) = 7 $ .

Thus, the answer is $ 2 + 9 + 7 + 7 = 25 $ .

After the second event, she found out that $ t_4 = 4 $ , then $ t_3 = w - t_2 - t_4 = 4 $ . $ \operatorname{dist}(1, 2) = 2 $ , $ \operatorname{dist}(2, 3) = 2 + 3 = 5 $ , $ \operatorname{dist}(3, 4) = 3 + 4 = 7 $ , $ \operatorname{dist}(4, 1) = 4 $ . Thus, the answer is $ 2 + 5 + 7 + 4 = 18 $ .

## 样例 #1

### 输入

```
4
2 1000000000000
1
2 1000000000000
4 9
1 1 1
2 2
4 4
3 3
6 100
1 2 3 2 1
6 17
3 32
2 4
4 26
5 21
10 511
1 2 2 4 2 1 1 8 8
3 2
6 16
10 256
9 128
2 1
5 8
8 64
4 4
7 32```

### 输出

```
2000000000000
25 18 18
449 302 247 200 200
4585 4473 2681 1567 1454 1322 1094 1022 1022```

# AI分析结果



# 算法分类  
树遍历与动态维护路径信息  

## 题解思路与难点分析  
**核心思路**：  
1. **DFS序特性**：树的顶点编号为DFS序，每条边在遍历时会被访问两次（进入和退出子树）。  
2. **路径贡献计算**：每个路径 `i → (i mod n)+1` 的权值最大可能值由两部分组成：已确定的边权和，以及未确定边的最优分配（将剩余权值全部分配给未确定的边）。  
3. **动态维护**：通过预处理记录每条边所属的路径集合，事件处理时快速更新路径状态（已确定边权和、未确定边数）。  

**关键数据结构与变量**：  
- `ocr[x]`：记录边 `x` 影响的所有路径。  
- `sum[u]`：路径 `u` 已确定的边权和。  
- `cnt[u]`：路径 `u` 中未确定的边数。  
- `ans`：所有完全确定路径的总和。  
- `tmp`：未完全确定路径的已确定部分之和。  
- `tot`：未完全确定的路径数量。  

**难点与解决**：  
- **路径覆盖关系**：通过DFS预处理确定每条边影响的路径集合。  
- **动态更新效率**：每次事件仅遍历受影响的路径，时间复杂度与边的影响路径数相关。  

## 最优思路提炼  
1. **预处理路径覆盖关系**：利用DFS记录每条边在哪些路径中出现。  
2. **动态维护路径状态**：事件触发时更新受影响的路径的 `sum` 和 `cnt`，分类处理完全确定与未完全确定的路径。  
3. **总和快速计算**：利用公式 `ans + tmp + tot * w` 快速得出结果。  

## 题解评分（≥4星）  
1. **Missa（5星）**：  
   - **亮点**：利用DFS序特性高效预处理，动态维护变量简洁清晰。  
   - **代码可读性**：结构清晰，变量命名合理，核心逻辑紧凑。  

## 核心代码实现  
```cpp
#include <bits/stdc++.h>
using LL = long long;

void solve() {
    int n; LL w; scanf("%d %lld", &n, &w);
    std::vector<std::vector<int>> ocr(n); // 边x影响的路径集合
    std::vector<std::vector<int>> e(n);   // 树的邻接表
    std::vector<int> cur, cnt(n);
    std::vector<LL> sum(n);
    
    // 建树
    for (int i = 1, p; i < n; i++) {
        scanf("%d", &p), --p;
        e[p].push_back(i);
    }
    
    // DFS预处理ocr
    std::function<void(int)> dfs = [&](int u) {
        for (auto x : cur) ocr[x].push_back(u), ++cnt[u]; // 记录当前边影响的路径
        cur.clear();
        for (auto v : e[u]) {
            cur.push_back(v);  // 进入子节点v
            dfs(v);
            cur.push_back(v);  // 退出子节点v
        }
    };
    dfs(0);
    
    // 处理初始未记录的边（根节点的剩余边）
    for (auto x : cur) ocr[x].push_back(0), ++cnt[0];
    
    LL ans = 0, tmp = 0, tot = n; // 初始化变量
    for (int i = 1; i < n; i++) {
        int x; LL y; scanf("%d %lld", &x, &y), --x;
        w -= y;
        // 更新受影响的路径
        for (auto u : ocr[x]) {
            tmp -= sum[u];     // 移除旧的已确定部分
            sum[u] += y;       // 更新当前路径的已确定和
            if (!--cnt[u]) {   // 路径完全确定
                ans += sum[u];
                tot--;
            } else {
                tmp += sum[u]; // 更新未确定路径的已确定部分和
            }
        }
        printf("%lld ", ans + tot * w + tmp);
    }
    printf("\n");
}
```

## 可视化设计  
**动画方案**：  
1. **树结构可视化**：用Canvas绘制树形结构，节点按DFS序排列。  
2. **路径高亮**：当处理事件时，高亮受影响的边及其关联路径。  
3. **动态数值更新**：实时显示 `ans`、`tmp`、`tot` 和 `w` 的变化。  

**复古像素风格**：  
- **颜色方案**：绿色表示确定路径，红色表示未确定路径，黄色高亮当前操作边。  
- **音效**：每次更新播放“哔”声，路径完全确定时播放上扬音效。  

**交互设计**：  
- **步进控制**：允许单步执行事件，观察变量和树结构变化。  
- **自动演示**：模拟事件触发流程，按时间顺序展示处理过程。  

## 相似题目  
1. **P3384 【模板】树链剖分**：维护树上路径信息。  
2. **P3258 松鼠的新家**：路径覆盖与动态更新。  
3. **P2680 运输计划**：树上路径最大值与二分答案结合。

---
处理用时：185.83秒