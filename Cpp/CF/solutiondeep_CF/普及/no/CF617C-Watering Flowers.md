# 题目信息

# Watering Flowers

## 题目描述

A flowerbed has many flowers and two fountains.

You can adjust the water pressure and set any values $ r_{1}(r_{1}>=0) $ and $ r_{2}(r_{2}>=0) $ , giving the distances at which the water is spread from the first and second fountain respectively. You have to set such $ r_{1} $ and $ r_{2} $ that all the flowers are watered, that is, for each flower, the distance between the flower and the first fountain doesn't exceed $ r_{1} $ , or the distance to the second fountain doesn't exceed $ r_{2} $ . It's OK if some flowers are watered by both fountains.

You need to decrease the amount of water you need, that is set such $ r_{1} $ and $ r_{2} $ that all the flowers are watered and the $ r_{1}^{2}+r_{2}^{2} $ is minimum possible. Find this minimum value.

## 说明/提示

The first sample is ( $ r_{1}^{2}=5 $ , $ r_{2}^{2}=1 $ ): ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF617C/2d8d9a04106e184829b587a5ec1ff5859c519f17.png) The second sample is ( $ r_{1}^{2}=1 $ , $ r_{2}^{2}=32 $ ): ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF617C/3a67f8e9001d1413dc94db849ab2167229f3fb78.png)

## 样例 #1

### 输入

```
2 -1 0 5 3
0 2
5 2
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4 0 0 5 0
9 4
8 3
-1 0
1 4
```

### 输出

```
33
```

# AI分析结果



# 中文题目重写

## 题目描述

花坛中有许多花和两个喷泉。

你可以调整水压并设置任意值 $ r_1(r_1 \geq 0) $ 和 $ r_2(r_2 \geq 0) $，分别表示从第一个和第二个喷泉喷水覆盖的距离。你需要设置这样的 $ r_1 $ 和 $ r_2 $，使得所有花都被浇灌，即每朵花到第一个喷泉的距离不超过 $ r_1 $，或者到第二个喷泉的距离不超过 $ r_2 $。允许部分花被两个喷泉同时浇灌。

你需要最小化用水量，即找到满足条件且 $ r_1^2 + r_2^2 $ 最小的方案。求这个最小值。

## 样例 #1

### 输入
```
2 -1 0 5 3
0 2
5 2
```

### 输出
```
6
```

## 样例 #2

### 输入
```
4 0 0 5 0
9 4
8 3
-1 0
1 4
```

### 输出
```
33
```

---

**算法分类**：贪心

---

## 题解综合分析

### 关键思路
1. **排序预处理**：将所有花朵按到第一个喷泉的距离升序排序。
2. **后缀最大值预处理**：预处理每个位置之后所有花朵到第二个喷泉的最大距离。
3. **枚举优化**：枚举第一个喷泉覆盖前 $i$ 朵花时，第二个喷泉只需覆盖剩余花朵的最大距离。

### 最优题解（评分：5星）

#### 作者：jch123
**关键亮点**：
- 利用排序和后缀数组预处理将时间复杂度优化至 $O(n \log n + n)$
- 正确处理边界情况（全由第一个或第二个喷泉覆盖）
- 代码结构清晰，逻辑严谨

**核心代码**：
```cpp
sort(a+1,a+1+n,cmp); // 按到第一个喷泉的距离排序
for(int i=n;i>=1;i--) // 预处理后缀最大值
    dis[i] = max(dis[i+1], d(x2,y2,a[i].x,a[i].y));
for(int i=0;i<=n;i++) // 枚举分界点
    ans = min(ans, a[i].d + dis[i+1]);
```

### 扩展技巧
- **预处理技巧**：在处理分段问题时，预处理后缀信息可以避免重复计算。
- **贪心排序**：通过排序将问题转化为可枚举的边界问题，是处理覆盖类问题的常用手段。

---

## 类似题目推荐
1. [P2884 - [USACO07MAR]Monthly Expense](https://www.luogu.com.cn/problem/P2884)  
   **相似点**：二分答案+贪心验证的分段处理思想
2. [P5547 - [POI2013]BAJ-Bytecomputer](https://www.luogu.com.cn/problem/P5547)  
   **相似点**：基于排序的贪心决策
3. [P2218 - [HAOI2007] 覆盖问题](https://www.luogu.com.cn/problem/P2218)  
   **相似点**：多覆盖源的优化布局问题

---

## 题解个人心得摘录
- **预处理的重要性**："直接枚举会TLE，预处理后缀最大值才能优化时间"（作者jch123）
- **边界处理**："特别注意全由第二个喷泉覆盖的情况，初始值要设为0"（作者QWQ_SenLin）
- **贪心验证**："排序后枚举分界点时，要确保剩余部分的最大值被正确计算"（作者封禁用户）

---
处理用时：134.79秒