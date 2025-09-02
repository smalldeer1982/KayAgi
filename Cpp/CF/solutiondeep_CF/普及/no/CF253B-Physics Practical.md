# 题目信息

# Physics Practical

## 题目描述

One day Vasya was on a physics practical, performing the task on measuring the capacitance. He followed the teacher's advice and did as much as $ n $ measurements, and recorded the results in the notebook. After that he was about to show the results to the teacher, but he remembered that at the last lesson, the teacher had made his friend Petya redo the experiment because the largest and the smallest results differed by more than two times. Vasya is lazy, and he does not want to redo the experiment. He wants to do the task and go home play computer games. So he decided to cheat: before Vasya shows the measurements to the teacher, he will erase some of them, so as to make the largest and the smallest results of the remaining measurements differ in no more than two times. In other words, if the remaining measurements have the smallest result $ x $ , and the largest result $ y $ , then the inequality $ y<=2·x $ must fulfill. Of course, to avoid the teacher's suspicion, Vasya wants to remove as few measurement results as possible from his notes.

Help Vasya, find what minimum number of measurement results he will have to erase from his notes so that the largest and the smallest of the remaining results of the measurements differed in no more than two times.

## 说明/提示

In the first sample you can remove the fourth and the sixth measurement results (values 8 and 7). Then the maximum of the remaining values will be 5, and the minimum one will be 3. Or else, you can remove the third and fifth results (both equal 3). After that the largest remaining result will be 8, and the smallest one will be 4.

## 样例 #1

### 输入

```
6
4 5 3 8 3 7
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
4 3 2 4
```

### 输出

```
0
```

# AI分析结果



# Physics Practical

## 题目描述

某天 Vasya 在做物理实验时进行了 $n$ 次电容测量，记录结果后需要删除部分数据，使得剩余数据的最小值 $x$ 和最大值 $y$ 满足 $y \leq 2x$。求最少需要删除的测量结果数量。

## 说明/提示

样例 1 中删除第 4 和第 6 个测量值（8 和 7），剩余数据最大为 5，最小为 3，满足条件。样例 2 中所有数据已满足条件。

## 样例 #1

### 输入
```
6
4 5 3 8 3 7
```

### 输出
```
2
```

## 样例 #2

### 输入
```
4
4 3 2 4
```

### 输出
```
0
```

**算法分类**：排序 + 双指针（贪心）

---

## 题解分析与结论

所有题解均先对数组排序，核心思路是寻找满足条件的最长连续子数组。主要方法分为双指针滑动窗口和二分查找：

1. **双指针法**（最优解）：
   - 排序后维护滑动窗口 $[l,r]$，右指针 $r$ 尽可能扩展至不满足条件时，左指针 $l$ 右移
   - 时间复杂度 $O(n \log n)$（排序） + $O(n)$（双指针），总体 $O(n \log n)$

2. **二分法**：
   - 对每个元素 $a_i$，用二分查找找到第一个大于 $2a_i$ 的位置
   - 时间复杂度 $O(n \log n)$（排序） + $O(n \log n)$（二分），总体 $O(n \log n)$

---

## 精选题解

### 题解一：huangrenheluogu 的双指针法（⭐⭐⭐⭐⭐）
**核心亮点**：
- 滑动窗口实现简洁高效，时间复杂度最优
- 处理边界时巧妙添加哨兵值简化判断

```cpp
sort(a + 1, a + n + 1);
a[++n] = inf; // 哨兵处理
for (int l = 1, r = 1; r < n; l++) {
    while (r < n && a[r] <= a[l] * 2) r++;
    ans = max(ans, r - l);
}
cout << n - ans - 1;
```

### 题解二：A524 的尺取法（⭐⭐⭐⭐）
**关键思路**：
- 右指针随左指针单向移动，无需回退
- 实时维护窗口最大长度

```cpp
sort(a + 1, a + n + 1);
for (r = 1; r <= n; r++) {
    while (l <= r && a[l] * 2 < a[r]) l++;
    Max = max(Max, r - l + 1);
}
cout << n - Max;
```

### 题解三：vanueber 的二分法（⭐⭐⭐⭐）
**优化点**：
- 直接使用 STL 的 `upper_bound` 简化实现
- 指针运算计算删除数量

```cpp
sort(a + 1, a + n + 1);
for (int i = 1; i <= n; i++) {
    int* s = upper_bound(a + 1, a + n + 1, a[i] * 2);
    ans = min(ans, (int)(a + i - s + n));
}
```

---

## 关键思路总结
1. **排序预处理**：通过排序将问题转化为寻找最大连续子数组
2. **滑动窗口优化**：利用双指针单向移动特性，实现线性时间复杂度
3. **边界处理技巧**：添加哨兵值避免特殊判断

---

## 拓展练习
1. [CF977D - 倍数序列](https://codeforces.com/problemset/problem/977/D)（排序+贪心）
2. [洛谷 P1102 - 最大差值](https://www.luogu.com.cn/problem/P1102)（双指针应用）
3. [LeetCode 1498. 满足条件的子序列数目](https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/)（排序+双指针）

---

## 调试经验
- **文件输入输出**：多个题解强调必须包含 `freopen("input.txt","r",stdin)`，否则会判错
- **数值范围陷阱**：当元素值较大时，前缀和方法不可行，优先选择双指针法
- **边界条件**：例如全数组已满足条件时需特判，可提升代码鲁棒性

---
处理用时：141.70秒