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



---

## **算法分类**
动态规划 (状态转移优化)

---

## **题解思路、算法要点与解决难点**

### **核心思路**
1. **动态规划状态定义**：定义 `f[i][j]` 表示从 `j` 跳到 `i` 的最大得分，初始化为 `f[j][j] = s(j)`（起点）。
2. **方向分治**：分别处理向右跳和向左跳两种情况。通过排序后正序和倒序两次 DP 处理。
3. **状态转移优化**：利用双指针维护满足跳跃条件的最远 `k`，避免暴力枚举，时间复杂度从 O(n³) 优化为 O(n²)。

### **关键优化**
- **双指针维护单调性**：对于每个 `j`，维护一个 `now` 指针，表示满足 `x[j] - x[k] <= x[i] - x[j]` 的最大 `k`。随着 `i` 增大，`now` 指针左移，确保每个 `k` 只被访问一次。
- **方向复用**：处理向左跳时，将坐标反转并取负数，复用向右跳的代码逻辑。

### **解决难点**
- **跳跃条件判断**：通过排序确保坐标有序，将跳跃距离的不递减条件转化为双指针的单调区间。
- **高效状态转移**：通过预处理和后缀最大值优化，避免重复计算。

---

## **题解评分 (≥4星)**

| 作者       | 评分 | 亮点                                                                 |
|------------|------|----------------------------------------------------------------------|
| gzw2005    | ★★★★☆ | 双指针优化思路清晰，代码结构简洁，逻辑复用方向处理。                 |
| QwQcOrZ    | ★★★★☆ | 双指针与后缀最大值结合，预处理思路巧妙，代码可读性高。               |
| linaonao   | ★★★★☆ | 单调队列优化实现完整，代码注释详细，适合深入理解优化细节。           |

---

## **最优思路与技巧提炼**

### **核心技巧**
1. **双指针维护状态转移区间**：通过 `now` 指针动态维护满足条件的 `k` 的范围，避免无效枚举。
2. **方向分治与坐标反转**：正序处理向右跳，反转数组后复用来处理向左跳，减少代码冗余。
3. **后缀最大值优化**：预处理 `f[j][k]` 的最大值，快速查询区间极值。

### **代码片段**
```cpp
// 向右跳的 DP 核心逻辑
for (int j = 1; j <= N; j++) {
    f[j][j] = s(j);
    for (int i = j + 1, now = j; i <= N; i++) {
        // 维护 now 指针找到最大 k
        while (now > 0 && x(j) - x(now - 1) <= x(i) - x(j)) {
            f[i][j] = max(f[i][j], f[j][--now]);
        }
        f[i][j] += s(i);
    }
}
```

---

## **同类型题与类似算法**

### **相似题目**
1. **最长递增子序列**（单调性优化 DP）。
2. **跳跃游戏**（LeetCode 55）：跳跃条件动态规划。
3. **青蛙过河**（LeetCode 403）：状态转移中的跳跃步长限制。

### **通用套路**
- **双指针优化 DP**：当状态转移条件具有单调性时，用指针维护区间边界。
- **方向分治**：通过反转输入或对称处理简化代码。

---

## **推荐题目**
1. **P1091 合唱队形**（双向 LIS）。
2. **P1280 尼克的任务**（状态转移优化）。
3. **P1886 滑动窗口**（单调队列模板）。

---

## **可视化与算法演示**

### **动画设计**
1. **像素风格 Canvas**：用网格表示坐标点，跳跃路径用高亮线段动态绘制。
2. **双指针动态标记**：红色标记当前 `i` 和 `j`，绿色标记 `now` 指针位置。
3. **音效提示**：跳跃成功播放短音效，更新最大值时播放上扬音调。

### **交互功能**
- **步进控制**：允许单步执行观察指针移动和状态更新。
- **速度调节**：滑动条控制动画速度（慢/正常/快）。

![可视化示意图](https://i.imgur.com/5X5gGQq.gif)

---

## **个人心得摘录**
- **缓存机制优化**：枚举顺序影响内存访问效率，优先访问连续内存提升性能。
- **方向反转技巧**：通过坐标取反和反转数组复用代码，减少重复逻辑。

---
处理用时：88.20秒