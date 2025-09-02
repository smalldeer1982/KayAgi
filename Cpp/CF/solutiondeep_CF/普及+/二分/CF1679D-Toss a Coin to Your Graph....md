# 题目信息

# Toss a Coin to Your Graph...

## 题目描述

One day Masha was walking in the park and found a graph under a tree... Surprised? Did you think that this problem would have some logical and reasoned story? No way! So, the problem...

Masha has an oriented graph which $ i $ -th vertex contains some positive integer $ a_i $ . Initially Masha can put a coin at some vertex. In one operation she can move a coin placed in some vertex $ u $ to any other vertex $ v $ such that there is an oriented edge $ u \to v $ in the graph. Each time when the coin is placed in some vertex $ i $ , Masha write down an integer $ a_i $ in her notebook (in particular, when Masha initially puts a coin at some vertex, she writes an integer written at this vertex in her notebook). Masha wants to make exactly $ k - 1 $ operations in such way that the maximum number written in her notebook is as small as possible.

## 说明/提示

Graph described in the first and the second examples is illustrated below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679D/f21a10b2a32ca5315b6d3233f4e3f1d967d3f865.png)In the first example Masha can initially put a coin at vertex $ 1 $ . After that she can perform three operations: $ 1 \to 3 $ , $ 3 \to 4 $ and $ 4 \to 5 $ . Integers $ 1, 2, 3 $ and $ 4 $ will be written in the notepad.

In the second example Masha can initially put a coin at vertex $ 2 $ . After that she can perform $ 99 $ operations: $ 2 \to 5 $ , $ 5 \to 6 $ , $ 6 \to 2 $ , $ 2 \to 5 $ , and so on. Integers $ 10, 4, 5, 10, 4, 5, \ldots, 10, 4, 5, 10 $ will be written in the notepad.

In the third example Masha won't be able to perform $ 4 $ operations.

## 样例 #1

### 输入

```
6 7 4
1 10 2 3 4 5
1 2
1 3
3 4
4 5
5 6
6 2
2 5```

### 输出

```
4```

## 样例 #2

### 输入

```
6 7 100
1 10 2 3 4 5
1 2
1 3
3 4
4 5
5 6
6 2
2 5```

### 输出

```
10```

## 样例 #3

### 输入

```
2 1 5
1 1
1 2```

### 输出

```
-1```

## 样例 #4

### 输入

```
1 0 1
1000000000```

### 输出

```
1000000000```

# AI分析结果



# 题目中文翻译

## 题目名称：向你的图抛硬币...

## 题目描述

有一天Masha在公园散步时，在树下发现了一个有向图...感到惊讶吗？你以为这道题会有什么合逻辑的故事吗？不可能！所以问题是...

Masha有一个有向图，第$i$个顶点有一个正整数$a_i$。初始时Masha可以将硬币放在某个顶点。每次操作她可以将硬币从顶点$u$移动到顶点$v$（只要存在有向边$u \to v$）。每次硬币放在顶点$i$时，Masha会在笔记本中记录$a_i$（初始放置硬币时也会记录该顶点的值）。Masha希望在恰好$k-1$次操作后，使得笔记本中的最大值尽可能小。

## 输入输出样例
（样例与提示内容与原文一致，此处省略）

---

# 题解综合分析

## 算法核心
所有题解均采用二分答案+图论判定的框架：
1. **二分答案**：在值域范围内二分最大权值
2. **子图构建**：仅保留权值≤mid的顶点和边
3. **环检测**：存在环时可无限循环必合法
4. **最长路计算**：DAG上拓扑排序时动态维护最长路径

## 最优题解推荐

### 1. Hovery（4星）
**核心亮点**：
- 拓扑排序同时处理环检测和最长路计算
- 入队节点计数法高效判断环存在性
- 代码结构清晰，变量命名规范

**关键代码**：
```cpp
bool check(int need) {
    // 初始化图和入度
    for (int i = 1; i <= m; i++) {
        if (a[x[i]] <= need && a[y[i]] <= need) {
            du[y[i]]++;
            G[x[i]].pb(y[i]);
            vis[x[i]] = vis[y[i]] = 1;
        }
    }
    
    // 拓扑排序与最长路计算
    queue<int> q;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (auto i : G[x]) {
            du[i]--;
            dis[i] = max(dis[i], dis[x] + 1);
            if (!du[i]) q.push(i);
        }
    }
    
    // 判断合法条件
    return (cnt != sum) || (max_dis >= k);
}
```

### 2. Komorebi_03（4星）
**核心亮点**：
- 独立初始化模块增强可读性
- 显式处理权值边界情况
- 队列操作与状态更新分离

**调试心得**：
> "注意开long long，拓扑排序时需重置入度数组，在二分边界处理时特别注意k=1的特殊情况"

---

# 关键思路总结

1. **二分框架**：将极值问题转化为判定问题
```cpp
int l=1, r=1e9;
while(l <= r) {
    int mid = (l+r)>>1;
    if(check(mid)) r=mid-1;
    else l=mid+1;
}
```

2. **复合判定技巧**：
- 入度数组双重用途：既用于拓扑排序，又用于环检测
- 动态维护dis数组：在拓扑排序过程中同步计算最长路径

3. **优化点**：
- 避免重复建图：通过vis数组标记有效节点
- 提前终止条件：当发现环或路径长度≥k时立即返回

---

# 相似题目推荐
1. [P3385 判断负环](https://www.luogu.com.cn/problem/P3385) - 环检测基础
2. [P1137 旅行计划](https://www.luogu.com.cn/problem/P1137) - DAG最长路应用
3. [P1113 杂务](https://www.luogu.com.cn/problem/P1113) - 拓扑排序与动态规划结合

---

# 心得摘录
**starrylasky**：
> "记忆化搜索时注意回溯标记，遇到已访问节点立即返回环存在，这个判定条件调试了3小时才正确"

**intel_core**：
> "特判k=1且没有边的情况，此时直接取最小节点值，这个边界情况导致WA了两次"

---
处理用时：54.65秒