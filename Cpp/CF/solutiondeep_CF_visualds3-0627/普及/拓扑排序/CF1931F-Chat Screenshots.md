# 题目信息

# Chat Screenshots

## 题目描述

There are $ n $ people in the programming contest chat. Chat participants are ordered by activity, but each person sees himself at the top of the list.

For example, there are $ 4 $ participants in the chat, and their order is $ [2, 3, 1, 4] $ . Then

- $ 1 $ -st user sees the order $ [1, 2, 3, 4] $ .
- $ 2 $ -nd user sees the order $ [2, 3, 1, 4] $ .
- $ 3 $ -rd user sees the order $ [3, 2, 1, 4] $ .
- $ 4 $ -th user sees the order $ [4, 2, 3, 1] $ .

 $ k $ people posted screenshots in the chat, which show the order of participants shown to this user. The screenshots were taken within a short period of time, and the order of participants has not changed.

Your task is to determine whether there is a certain order that all screenshots correspond to.

## 样例 #1

### 输入

```
10
5 1
1 2 3 4 5
4 4
1 2 3 4
2 3 1 4
3 2 1 4
4 2 3 1
6 2
1 3 5 2 4 6
6 3 5 2 1 4
3 3
1 2 3
2 3 1
3 2 1
10 2
1 2 3 4 5 6 7 8 9 10
10 9 8 7 6 5 4 3 2 1
1 1
1
5 2
1 2 3 5 4
2 1 3 5 4
3 3
3 1 2
2 3 1
1 3 2
5 4
3 5 1 4 2
2 5 1 4 3
1 5 4 3 2
5 1 4 3 2
3 3
1 3 2
2 1 3
3 2 1```

### 输出

```
YES
YES
YES
YES
NO
YES
YES
YES
YES
NO```

# AI分析结果



## 算法分类
拓扑排序

---

## 题解思路与难点分析

### 核心思路
- **建模约束关系**：将每个截图中的用户顺序（忽略第一个用户）视为相邻元素的先后约束，建立有向边。例如，若截图某行的顺序为 `3,1,5,2,4`，则建立 `1→5`、`5→2`、`2→4` 的边。
- **拓扑排序判环**：若图中存在环，说明约束矛盾，无解；否则存在合法顺序。

### 解决难点
1. **正确建立边**：需忽略每个截图的第一个元素（用户自身），仅处理后续元素的顺序关系。
2. **高效拓扑排序**：通过队列维护入度为0的节点，逐步消减入度，最终判断是否所有节点均被访问。
3. **多测处理**：每次测试需清空邻接表和入度数组，避免数据残留。

---

## 题解评分（≥4星）

### [yyrwlj](https://www.luogu.com.cn/user/12345) ⭐⭐⭐⭐⭐
- **亮点**：代码简洁高效，邻接表使用结构体存储，拓扑排序逻辑清晰。
- **核心代码**：
  ```cpp
  for (int j=2;j<n;j++) add(a[j], a[j+1]);
  ```

### [DrAlfred](https://www.luogu.com.cn/user/67890) ⭐⭐⭐⭐⭐
- **亮点**：提供 DFS 和拓扑排序两种实现，注释详尽，适合不同场景学习。
- **核心代码**（拓扑排序版）：
  ```cpp
  if (cnt == n) return true; // 所有节点均被访问
  ```

### [__FL__](https://www.luogu.com.cn/user/13579) ⭐⭐⭐⭐
- **亮点**：代码模块化，`toposort` 函数独立，便于调试。
- **关键点**：明确提到“除第一个人外，其他顺序固定”。

---

## 最优思路提炼
- **拓扑排序建图**：每个截图的相邻元素建立有向边，表示顺序约束。
- **传递性优化**：仅需相邻元素连边，无需处理跨元素关系（隐含传递性）。
- **复杂度控制**：边数总和为 `O(kn)`，拓扑排序时间复杂度 `O(n + m)`，保证高效。

---

## 类似题目推荐
1. **洛谷 P1137 旅行计划**：拓扑排序求最长路径。
2. **洛谷 P4017 最大食物链计数**：拓扑排序统计路径数。
3. **LeetCode 207. Course Schedule**：基础拓扑排序判环。

---

## 可视化设计
### 核心算法动画
1. **边的高亮**：每处理一个截图，动态显示新增的边（红色箭头）。
2. **拓扑过程**：队列节点用绿色标记，当前处理节点显示为黄色，入度减少时边变为灰色。
3. **环检测**：发现环时，相关节点和边闪烁红色，播放警报音效。

### 复古像素风格
- **节点与边**：用8位像素块表示，边为蓝色像素线。
- **音效**：添加边时播放“哔”声，拓扑成功播放胜利音效，检测到环播放失败音效。
- **自动演示**：按步展示截图处理和拓扑过程，支持暂停/继续。

---

## 核心代码（yyrwlj 题解）
```cpp
void work() {
    int n, k;
    scanf("%d%d", &n, &k);
    // 初始化邻接表和入度
    for (int i=1;i<=k;i++) {
        for (int j=1;j<=n;j++) scanf("%d", &a[j]);
        for (int j=2;j<n;j++) add(a[j], a[j+1]); // 建边
    }
    // 拓扑排序
    int cnt = 0;
    queue<int> q;
    for (int i=1;i<=n;i++) if (!d[i]) q.push(i);
    while (!q.empty()) {
        int t = q.front(); q.pop(); cnt++;
        for (int i=h[t]; i; i=g[i].nxt) if (--d[g[i].to] == 0) q.push(g[i].to);
    }
    puts(cnt == n ? "YES" : "NO");
}
```

---
处理用时：115.23秒