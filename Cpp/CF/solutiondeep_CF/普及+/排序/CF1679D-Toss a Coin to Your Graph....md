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

## 题目描述

某天Masha在公园的树下发现了一个有向图...惊讶吗？你以为这题会有逻辑严谨的背景故事？不可能！所以问题来了...

Masha有一个有向图，第i个顶点上写有正整数a_i。她可以选择任意顶点放置硬币，每次操作可将硬币从顶点u沿有向边u→v移动到v。每当硬币停留在顶点i时，Masha会在笔记本记录a_i（初始放置时也会记录）。她希望进行恰好k-1次操作，使得笔记本中记录的最大数值尽可能小。

## 输入格式

输入包含若干测试用例，每个用例包含：
- 第一行三个整数n、m、k（顶点数、边数、要求操作次数+1）
- 第二行n个整数表示各顶点权值a_i
- 后续m行每行两个整数描述有向边

## 输出格式

输出最小可能的最大值，若无法完成k-1次操作输出-1。

## 样例说明
样例1说明：可通过路径1→3→4→5得到最大值4  
样例2说明：在顶点2与5、6构成的环中循环  
样例3说明：边数不足以完成4次操作  
样例4说明：单顶点无需移动即可满足条件

---

# 题解综合分析

## 算法共性
所有题解均采用**二分答案+拓扑排序**框架：
1. **二分查找**确定阈值X
2. 构建权值≤X的**子图**
3. 检查子图是否存在**环**（可无限循环）
4. 若无环则计算**最长路径**

## 核心难点
1. **环检测与最长路计算的统一处理**：通过拓扑排序入队节点数判断是否有环
2. **动态维护最长路径**：在拓扑排序过程中进行DP
3. **边界条件处理**：k=1、空图等特殊情况

---

# 精选题解（评分≥4⭐）

## 1. Hovery（5⭐）
**亮点**：
- 拓扑排序同时处理环检测和最长路
- 用vis数组统计有效节点数
- 代码结构清晰，变量命名规范

**关键代码**：
```cpp
bool check(int need) {
    // 初始化邻接表、度数数组等
    for (边处理) {
        if (两端点权值均<=need) 建边并标记顶点
    }
    
    queue<int> q;
    // 拓扑排序处理
    while (!q.empty()) {
        int x = q.front();
        // 动态更新最长路径
        for (邻接节点) {
            dis[i] = max(dis[i], dis[x] + 1);
        }
    }
    // 判断环或最长路是否达标
    return cnt != sum || max(dis) >= k;
}
```

## 2. Komorebi_03（4.5⭐）
**亮点**：
- 独立init函数处理初始化
- 显式处理空图情况
- 详细注释提升可读性

**调试心得**：
> "注意开long long，拓扑排序时初始dis[i]=1的处理容易遗漏"

## 3. Anguei（4⭐）
**亮点**：
- 使用lambda表达式封装检查函数
- 显式分离环检测与最长路计算
- 处理k=1的特殊情况

**代码片段**：
```cpp
auto check = [&](int x) {
    // 构建子图
    auto hasCycle = [&](){ /* 拓扑判环 */ };
    if (hasCycle()) return true;
    
    // DAG最长路DP
    vector<int> dp(n+1, -1);
    auto dfs = [&](auto self, int u) { /* 记忆化搜索 */ };
    return 存在长度≥k的路径;
};
```

---

# 关键技巧总结

1. **二分答案的转化**：将最优化问题转化为判定问题，通过log次检查解决问题
2. **拓扑排序的多功能应用**：
   - 入队节点数 < 有效节点数 → 存在环
   - 拓扑序中动态规划求最长路径
3. **子图构建优化**：不实际删除节点，通过权值判断动态处理边
4. **初始化技巧**：每次check前清空邻接表、度数数组等

---

# 拓展训练

1. **环形依赖检测**：[P3385 【模板】负环](https://www.luogu.com.cn/problem/P3385)
2. **DAG最长路径**：[P1113 杂务](https://www.luogu.com.cn/problem/P1113) 
3. **二分答案+图论**：[P3199 [HNOI2009] 最小圈](https://www.luogu.com.cn/problem/P3199)

---
处理用时：58.34秒