# 题目信息

# Schedule

## 题目描述

At the beginning of the new semester there is new schedule in the Berland State University. According to this schedule, $ n $ groups have lessons at the room 31. For each group the starting time of the lesson and the finishing time of the lesson are known. It has turned out that it is impossible to hold all lessons, because for some groups periods of their lessons intersect. If at some moment of time one groups finishes it's lesson, and the other group starts the lesson, their lessons don't intersect.

The dean wants to cancel the lesson in one group so that no two time periods of lessons of the remaining groups intersect. You are to find all ways to do that.

## 样例 #1

### 输入

```
3
3 10
20 30
1 3
```

### 输出

```
3
1 2 3 ```

## 样例 #2

### 输入

```
4
3 10
20 30
1 3
1 39
```

### 输出

```
1
4 ```

## 样例 #3

### 输入

```
3
1 5
2 6
3 7
```

### 输出

```
0
```

# AI分析结果



# Schedule

## 题目描述

新学期的开始，Berland州立大学的31号教室有$n$个小组的课程安排。已知每个小组课程的开始时间和结束时间。由于某些课程的时间段存在重叠，无法同时进行所有课程。如果在某一时刻一个小组的课程结束而另一个小组的课程开始，则这两个课程的时间段不视为重叠。

校长希望取消一个小组的课程，使得剩余小组的课程时间段互不重叠。你需要找出所有可能的取消方案。

## 样例 #1

### 输入

```
3
3 10
20 30
1 3
```

### 输出

```
3
1 2 3 
```

## 样例 #2

### 输入

```
4
3 10
20 30
1 3
1 39
```

### 输出

```
1
4 
```

## 样例 #3

### 输入

```
3
1 5
2 6
3 7
```

### 输出

```
0
```

---

**算法分类**：枚举

---

## 题解综合分析

所有题解均采用双重循环统计冲突对的思路，通过计算每个课程参与的冲突次数与总冲突次数的关系判断是否可删除。关键思路如下：

1. **冲突判断**：通过双重循环遍历所有课程对，判断区间是否相交。
2. **计数统计**：对每个课程参与的冲突次数（`sum[i]`）和总冲突对数（`s`）进行统计。
3. **筛选条件**：若某课程的冲突次数等于总冲突对数，则删除该课程可消除所有冲突。

---

## 精选题解

### 题解作者：xiaozeyu（⭐⭐⭐⭐）
**关键亮点**：
- 使用`vector`动态存储答案，简化内存管理。
- 双重循环范围设计合理，避免重复计算。
- 代码简洁且边界处理清晰。

**核心代码**：
```cpp
for(int i=0;i<n;i++)
    for(int j=0;j<i;j++) {
        if(l[i]<r[j]&&l[j]<r[i]) {
            sum[i]++; sum[j]++; s++;
        }
    }
// 筛选条件
for(int i=0;i<n;i++)
    if(sum[i]==s) ans.push_back(i+1);
```

---

### 题解作者：晨·曦（⭐⭐⭐⭐）
**关键亮点**：
- 从1开始索引，符合直觉。
- 使用数组预存答案，减少动态内存开销。
- 循环条件优化，遍历上三角矩阵避免冗余。

**核心代码**：
```cpp
for(int i=1;i<n;i++) {
    for(int j=i+1;j<=n;j++) {
        if(a[i]<b[j] && a[j]<b[i]) {
            s[i]++; s[j]++; c++;
        }
    }
}
// 筛选条件
for(int i=1;i<=n;i++)
    if(s[i]==c) ans[++l]=i;
```

---

## 最优思路总结
1. **冲突判断公式**：区间相交的判断条件`a[i]<b[j] && a[j]<b[i]`是核心。
2. **计数优化**：通过双重循环统计冲突次数，确保每对仅计算一次。
3. **筛选条件**：若某课程的冲突次数等于总冲突对数，说明该课程是唯一冲突源。

---

## 类似题目推荐
1. [P1803 线段覆盖](https://www.luogu.com.cn/problem/P1803) - 贪心选择不重叠线段。
2. [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240) - 区间选择与最优策略。
3. [P2947 [USACO09MAR] Look Up S](https://www.luogu.com.cn/problem/P2947) - 枚举与条件判断结合。

---
处理用时：169.86秒