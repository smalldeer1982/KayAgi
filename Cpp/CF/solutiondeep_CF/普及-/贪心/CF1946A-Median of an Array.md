# 题目信息

# Median of an Array

## 题目描述

You are given an array $ a $ of $ n $ integers.

The median of an array $ q_1, q_2, \ldots, q_k $ is the number $ p_{\lceil \frac{k}{2} \rceil} $ , where $ p $ is the array $ q $ sorted in non-decreasing order. For example, the median of the array $ [9, 5, 1, 2, 6] $ is $ 5 $ , as in the sorted array $ [1, 2, 5, 6, 9] $ , the number at index $ \lceil \frac{5}{2} \rceil = 3 $ is $ 5 $ , and the median of the array $ [9, 2, 8, 3] $ is $ 3 $ , as in the sorted array $ [2, 3, 8, 9] $ , the number at index $ \lceil \frac{4}{2} \rceil = 2 $ is $ 3 $ .

You are allowed to choose an integer $ i $ ( $ 1 \le i \le n $ ) and increase $ a_i $ by $ 1 $ in one operation.

Your task is to find the minimum number of operations required to increase the median of the array.

Note that the array $ a $ may not necessarily contain distinct numbers.

## 说明/提示

In the first test case, you can apply one operation to the first number and obtain the array $ [3, 2, 8] $ , the median of this array is $ 3 $ , as it is the number at index $ \lceil \frac{3}{2} \rceil = 2 $ in the non-decreasing sorted array $ [2, 3, 8] $ . The median of the original array $ [2, 2, 8] $ is $ 2 $ , as it is the number at index $ \lceil \frac{3}{2} \rceil = 2 $ in the non-decreasing sorted array $ [2, 2, 8] $ . Thus, the median increased ( $ 3 > 2 $ ) in just one operation.

In the fourth test case, you can apply one operation to each of the numbers at indices $ 1, 2, 3 $ and obtain the array $ [6, 6, 6, 4, 5] $ , the median of this array is $ 6 $ , as it is the number at index $ \lceil \frac{5}{2} \rceil = 3 $ in the non-decreasing sorted array $ [4, 5, 6, 6, 6] $ . The median of the original array $ [5, 5, 5, 4, 5] $ is $ 5 $ , as it is the number at index $ \lceil \frac{5}{2} \rceil = 2 $ in the non-decreasing sorted array $ [4, 5, 5, 5, 5] $ . Thus, the median increased ( $ 6 > 5 $ ) in three operations. It can be shown that this is the minimum possible number of operations.

In the fifth test case, you can apply one operation to each of the numbers at indices $ 1, 3 $ and obtain the array $ [3, 1, 3, 3, 1, 4] $ , the median of this array is $ 3 $ , as it is the number at index $ \lceil \frac{6}{2} \rceil = 3 $ in the non-decreasing sorted array $ [1, 1, 3, 3, 3, 4] $ . The median of the original array $ [2, 1, 2, 3, 1, 4] $ is $ 2 $ , as it is the number at index $ \lceil \frac{6}{2} \rceil = 3 $ in the non-decreasing sorted array $ [1, 1, 2, 2, 3, 4] $ . Thus, the median increased ( $ 3 > 2 $ ) in two operations. It can be shown that this is the minimum possible number of operations.

## 样例 #1

### 输入

```
8
3
2 2 8
4
7 3 3 1
1
1000000000
5
5 5 5 4 5
6
2 1 2 3 1 4
2
1 2
2
1 1
4
5 5 5 5```

### 输出

```
1
2
1
3
2
1
2
3```

# AI分析结果



# Median of an Array（数组中位数）

## 题目描述

给定一个包含 $n$ 个整数的数组 $a$。每次操作可以选择一个元素将其加 $1$。求最少需要多少次操作使得操作后的数组中位数严格大于原数组的中位数。

**中位数定义**：将数组升序排序后，位于 $\lceil \frac{k}{2} \rceil$ 位置的数（下标从 $1$ 开始）。

## 样例解释
- 原数组 `[2, 2, 8]` 排序后中位数为 $2$。通过一次操作将第一个元素变为 $3$，新数组中位数为 $3$。
- 原数组 `[5,5,5,4,5]` 排序后中位数为 $5$。需对前三个 $5$ 各加 $1$，新数组中位数为 $6$，共需 $3$ 次操作。

---

## 题解分析与结论

### 关键思路与算法
1. **排序数组**：先对数组进行升序排序。
2. **定位中位数**：确定中位数位置 $mid = \lceil n/2 \rceil$。
3. **统计相同值**：计算从 $mid$ 开始，后续所有等于原中位数的元素个数，这些元素均需加 $1$。

### 解决难点
- **中位数更新逻辑**：若仅增加中位数位置的元素，后续相同值的元素仍会占据中位位置，必须将所有等于原中位数的后续元素一并处理。
- **时间复杂度**：通过单次遍历统计，时间复杂度为 $O(n \log n)$（排序占主导）。

---

## 高星题解推荐

### 题解 1：AK_400（★★★★★）
**亮点**：代码极简，直接统计中位数后的相同元素。
```cpp
int mid = (n + 1) / 2;
int cnt = 0;
for (int i = mid; i <= n; i++) {
    if (a[i] == a[mid]) cnt++;
}
cout << cnt << endl;
```
**核心思想**：排序后只需统计中位数位置及其右侧等于原中位数的元素数量。

### 题解 2：OJ_killer（★★★★☆）
**亮点**：从 $mid+1$ 开始遍历，统计连续相同值。
```cpp
int m = (n + 1) / 2;
int ans = 1;
for (int i = m + 1; i <= n; i++) {
    if (a[i] == a[m]) ans++;
    else break;
}
```
**注意点**：初始值 $ans=1$ 包含中位数自身，循环从 $mid+1$ 开始向后扩展。

### 题解 3：baokun（★★★★☆）
**亮点**：动态扩展统计范围，兼容非连续相同值场景。
```cpp
int now = mid;
while (a[now] == a[mid]) {
    ans++;
    now++;
}
```
**实现细节**：通过循环向后遍历，直到遇到比原中位数大的元素。

---

## 举一反三
1. **同类题目推荐**：
   - 洛谷 P1168：动态维护中位数（对顶堆）。
   - 洛谷 P1047：区间覆盖问题（贪心）。
   - CF 1005C：统计满足条件的元素对数量。

2. **优化思维**：在涉及排序后位置固定的场景（如中位数、百分位数），优先通过排序和下标计算快速定位关键元素。

---

## 个人心得摘录
- **调试教训**：当中位数后有重复值时，必须全部处理，否则新中位数仍可能不变。
- **代码技巧**：利用排序后数组的有序性，减少不必要的比较次数（如遇到更大元素即可终止遍历）。

---
处理用时：93.83秒