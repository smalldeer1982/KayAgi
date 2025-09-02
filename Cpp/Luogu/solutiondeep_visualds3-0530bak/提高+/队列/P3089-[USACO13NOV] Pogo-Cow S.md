# 题目信息

# [USACO13NOV] Pogo-Cow S

## 题目描述

In an ill-conceived attempt to enhance the mobility of his prize cow Bessie, Farmer John has attached a pogo stick to each of Bessie's legs. Bessie can now hop around quickly throughout the farm, but she has not yet learned how to slow down.

To help train Bessie to hop with greater control, Farmer John sets up a practice course for her along a straight one-dimensional path across his farm.  At various distinct positions on the path, he places N targets on which Bessie should try to land (1 <= N <= 1000).  Target i is located at position x(i), and is worth p(i) points if Bessie lands on it.  Bessie starts at the location of any target of her choosing and is allowed to move in only one direction, hopping from target to target.  Each hop must cover at least as much distance as the previous hop, and must land on a target.

Bessie receives credit for every target she touches (including the initial target on which she starts).  Please compute the maximum number of points she can obtain.

FJ给奶牛贝西的脚安装上了弹簧，使它可以在农场里快速地跳跃，但是它还没有学会如何降低速度。


FJ觉得让贝西在一条直线的一维线路上进行练习，他在不同的目标点放置了N (1 <= N <= 1000)个目标点，目标点i在目标点x(i)，该点得分为p(i)。贝西开始时可以选择站在一个目标点上，只允许朝一个方向跳跃，从一目标点跳到另外一个目标点，每次跳跃的距离至少和上一次跳跃的距离相等，并且必须跳到一个目标点。


每跳到一个目标点，贝西可以拿到该点的得分，请计算他的最大可能得分。


## 说明/提示

There are 6 targets.  The first is at position x=5 and is worth 6 points, and so on.


Bessie hops from position x=4 (8 points) to position x=5 (6 points) to position x=7 (6 points) to position x=10 (5 points).


## 样例 #1

### 输入

```
6 
5 6 
1 1 
10 5 
7 6 
4 8 
8 10 
```

### 输出

```
25 
```

# AI分析结果



# 【算法分类】  
**动态规划（Dynamic Programming）**

---

# **题解思路、算法要点与解决难点**

## **核心思路**
1. **状态定义**：定义 `f[i][j]` 表示跳到第 `i` 个点，且最后一步是从 `j` 跳来的最大得分。
2. **方向分治**：分别处理向右跳和向左跳的情况（后者通过反转坐标转化为向右跳）。
3. **转移优化**：通过双指针维护可行区间，避免暴力枚举 `k`，将复杂度从 `O(n^3)` 优化到 `O(n^2)`。

## **算法要点**
- **排序预处理**：按坐标排序后，跳跃方向变为单侧递增，简化状态转移。
- **双指针优化**：对于每个 `i` 和 `j`，维护一个 `now` 指针记录当前可用的最大 `k`，避免重复计算。
- **分方向处理**：将向左跳转化为向右跳（通过反转坐标并重新排序）。

## **解决难点**
- **转移条件**：跳跃距离需满足非递减，需快速找到所有合法的 `k`。
- **时间复杂度**：原始暴力 `O(n^3)` 不可行，需通过双指针或单调队列优化至 `O(n^2)`。

---

# **题解评分 (≥4星)**

| 题解作者 | 评分 | 关键亮点 |
|---------|------|---------|
| **gzw2005** | ⭐⭐⭐⭐⭐ | 双指针优化清晰，代码可读性强，分方向处理逻辑巧妙 |
| **QwQcOrZ** | ⭐⭐⭐⭐ | Two-Pointers + 后缀和优化，思路简洁 |
| **asuldb** | ⭐⭐⭐⭐ | 单调队列优化实现，展示队列维护最大值技巧 |

---

# **最优思路或技巧提炼**

## **关键优化**
- **双指针维护可行区间**：在固定 `i` 和 `j` 后，`k` 的合法区间是单调递增的，可用双指针快速定位。
- **分方向处理技巧**：通过反转坐标将向左跳转化为向右跳，避免重复编码。

## **代码实现技巧**
```cpp
// 向右跳的DP核心逻辑
for (int j = 1; j <= N; j++) {
    f[j][j] = s(j); // 初始状态
    int now = j;    // 双指针维护k的上界
    for (int i = j + 1; i <= N; i++) {
        // 从i-1转移到i，利用历史最大值
        f[i][j] = f[i-1][j] - s(i-1);
        // 扩展合法k的范围，更新最大值
        while (now > 1 && x(j) - x(now-1) <= x(i) - x(j)) {
            f[i][j] = max(f[i][j], f[j][--now]);
        }
        f[i][j] += s(i); // 加上当前点得分
        Ans = max(Ans, f[i][j]);
    }
}
```

---

# **同类型题或类似算法套路**

1. **跳跃游戏类问题**：如 LeetCode 55. Jump Game（跳跃可达性判断）。
2. **序列型DP优化**：如最长递增子序列的 `O(n log n)` 优化（维护单调队列）。
3. **分方向处理问题**：如双向动态规划（如矩阵中的左上到右下和右下到左上结合）。

---

# **推荐题目**

1. **[P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)**：双向LIS问题，分方向处理。
2. **[P1280 尼克的任务](https://www.luogu.com.cn/problem/P1280)**：时间轴DP，逆向转移优化。
3. **[P1880 石子合并](https://www.luogu.com.cn/problem/P1880)**：区间DP，环形结构处理。

---

# **可视化与算法演示**

## **动画方案**
1. **网格绘制**：在Canvas中绘制排序后的坐标轴，用不同颜色方块表示目标点。
2. **跳跃高亮**：当前跳跃路径用绿色连线，历史路径用灰色，得分实时显示。
3. **双指针动态标记**：用红色箭头标记 `now` 指针移动，蓝色箭头表示当前 `i` 和 `j`。

## **复古像素风格设计**
- **8位音效**：跳跃时播放“跳跃音效”，得分更新时播放“金币音效”。
- **自动演示模式**：模拟AI自动选择最优路径，每步延迟500ms，展示得分变化。

---

# **代码片段（核心逻辑）**

```cpp
// 关键代码：向右跳的DP处理
sort(point + 1, point + 1 + N, cmp);
for (int j = 1; j <= N; j++) {
    f[j][j] = point[j].p;
    int now = j;
    for (int i = j + 1; i <= N; i++) {
        f[i][j] = f[i-1][j] - point[i-1].p;
        while (now > 1 && point[j].x - point[now-1].x <= point[i].x - point[j].x) {
            f[i][j] = max(f[i][j], f[j][--now]);
        }
        f[i][j] += point[i].p;
        Ans = max(Ans, f[i][j]);
    }
}
```

---

# **总结**
本题通过动态规划结合双指针优化，巧妙解决了跳跃距离约束下的最大得分问题，其核心在于状态转移的高效维护和方向分治技巧。可视化设计可通过复古像素风格和动态指针标记，直观展示算法流程。

---
处理用时：69.66秒