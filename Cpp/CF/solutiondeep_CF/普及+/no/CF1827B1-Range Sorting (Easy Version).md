# 题目信息

# Range Sorting (Easy Version)

## 题目描述

The only difference between this problem and the hard version is the constraints on $ t $ and $ n $ .

You are given an array $ a $ , consisting of $ n $ distinct integers $ a_1, a_2, \ldots, a_n $ .

Define the beauty of an array $ p_1, p_2, \ldots p_k $ as the minimum amount of time needed to sort this array using an arbitrary number of range-sort operations. In each range-sort operation, you will do the following:

- Choose two integers $ l $ and $ r $ ( $ 1 \le l < r \le k $ ).
- Sort the subarray $ p_l, p_{l + 1}, \ldots, p_r $ in $ r - l $ seconds.

Please calculate the sum of beauty over all subarrays of array $ a $ .

A subarray of an array is defined as a sequence of consecutive elements of the array.

## 说明/提示

In the first test case:

- The subarray $ [6] $ is already sorted, so its beauty is $ 0 $ .
- The subarray $ [4] $ is already sorted, so its beauty is $ 0 $ .
- You can sort the subarray $ [6, 4] $ in one operation by choosing $ l = 1 $ and $ r = 2 $ . Its beauty is equal to $ 1 $ .

 The sum of beauty over all subarrays of the given array is equal to $ 0 + 0 + 1 = 1 $ .In the second test case:

- The subarray $ [3] $ is already sorted, so its beauty is $ 0 $ .
- The subarray $ [10] $ is already sorted, so its beauty is $ 0 $ .
- The subarray $ [6] $ is already sorted, so its beauty is $ 0 $ .
- The subarray $ [3, 10] $ is already sorted, so its beauty is $ 0 $ .
- You can sort the subarray $ [10, 6] $ in one operation by choosing $ l = 1 $ and $ r = 2 $ . Its beauty is equal to $ 2 - 1 = 1 $ .
- You can sort the subarray $ [3, 10, 6] $ in one operation by choosing $ l = 2 $ and $ r = 3 $ . Its beauty is equal to $ 3 - 2 = 1 $ .

 The sum of beauty over all subarrays of the given array is equal to $ 0 + 0 + 0 + 0 + 1 + 1 = 2 $ .

## 样例 #1

### 输入

```
5
2
6 4
3
3 10 6
4
4 8 7 2
5
9 8 2 4 6
12
2 6 13 3 15 5 10 8 16 9 11 18```

### 输出

```
1
2
8
16
232```

# AI分析结果

【题目内容】
# Range Sorting (Easy Version)

## 题目描述

该问题与困难版本的区别仅在于对 $ t $ 和 $ n $ 的限制。

给定一个数组 $ a $，由 $ n $ 个不同的整数 $ a_1, a_2, \ldots, a_n $ 组成。

定义一个数组 $ p_1, p_2, \ldots p_k $ 的美观度为使用任意数量的区间排序操作对该数组进行排序所需的最少时间。在每次区间排序操作中，你需要执行以下操作：

- 选择两个整数 $ l $ 和 $ r $（$ 1 \le l < r \le k $）。
- 对子数组 $ p_l, p_{l + 1}, \ldots, p_r $ 进行排序，耗时 $ r - l $ 秒。

请计算数组 $ a $ 的所有子数组的美观度之和。

一个数组的子数组定义为该数组中连续元素的序列。

## 说明/提示

在第一个测试用例中：

- 子数组 $ [6] $ 已经是有序的，因此其美观度为 $ 0 $。
- 子数组 $ [4] $ 已经是有序的，因此其美观度为 $ 0 $。
- 你可以通过选择 $ l = 1 $ 和 $ r = 2 $ 对子数组 $ [6, 4] $ 进行一次排序操作。其美观度为 $ 1 $。

给定数组的所有子数组的美观度之和为 $ 0 + 0 + 1 = 1 $。

在第二个测试用例中：

- 子数组 $ [3] $ 已经是有序的，因此其美观度为 $ 0 $。
- 子数组 $ [10] $ 已经是有序的，因此其美观度为 $ 0 $。
- 子数组 $ [6] $ 已经是有序的，因此其美观度为 $ 0 $。
- 子数组 $ [3, 10] $ 已经是有序的，因此其美观度为 $ 0 $。
- 你可以通过选择 $ l = 1 $ 和 $ r = 2 $ 对子数组 $ [10, 6] $ 进行一次排序操作。其美观度为 $ 2 - 1 = 1 $。
- 你可以通过选择 $ l = 2 $ 和 $ r = 3 $ 对子数组 $ [3, 10, 6] $ 进行一次排序操作。其美观度为 $ 3 - 2 = 1 $。

给定数组的所有子数组的美观度之和为 $ 0 + 0 + 0 + 0 + 1 + 1 = 2 $。

## 样例 #1

### 输入

```
5
2
6 4
3
3 10 6
4
4 8 7 2
5
9 8 2 4 6
12
2 6 13 3 15 5 10 8 16 9 11 18```

### 输出

```
1
2
8
16
232```

【算法分类】
贪心

【题解分析与结论】
本题的核心在于如何高效计算所有子数组的美观度之和。多个题解都采用了贪心策略，通过枚举区间或断点来减少计算复杂度。以下是几个关键思路：

1. **区间分割优化**：通过将区间分割为多个不重叠的子区间，减少排序操作的代价。多个题解都提到了如果左边的最大值小于右边的最小值，则可以分割区间，从而减少代价。

2. **枚举断点**：通过枚举每个可能的断点，计算其能减少的代价，从而优化总代价的计算。

3. **单调栈与二分查找**：部分题解使用了单调栈和二分查找来优化查找区间最大值和最小值的过程，进一步降低时间复杂度。

【所选高星题解】
1. **作者：_sunkuangzheng_ (5星)**
   - **关键亮点**：通过枚举每个元素作为区间的最小值，利用贪心策略找到极大范围，并通过预处理减少时间复杂度。
   - **代码核心思想**：枚举每个元素，找到其左边和右边的边界，计算贡献并累加。

```cpp
for(int i = 1;k = l = r = i,i <= n;ans -= (r - i) * (k - l),i ++){
    while(k > 0 && a[k] >= a[i]) k --;l = k;
    while(l > 0 && a[l] <= a[i]) l --;
    while(r <= n && a[r] >= a[i]) r ++;
}
```

2. **作者：Engulf (4星)**
   - **关键亮点**：通过容斥原理，先计算所有区间的最大代价，然后通过查找满足条件的断点来减少代价。
   - **代码核心思想**：使用ST表和二分查找来快速找到满足条件的边界，减少时间复杂度。

```cpp
auto rless = [=](int pos, int val) {
    int l = pos + 1, r = n - 1, res = n;
    while (l <= r) {
        int mid = l + r >> 1;
        if (queryMin(pos + 1, mid) < val) res = mid, r = mid - 1;
        else l = mid + 1;
    }
    return res;
};
```

3. **作者：huangrenheluogu (4星)**
   - **关键亮点**：通过枚举间隔，利用双指针和预处理的最小值数组来优化计算。
   - **代码核心思想**：枚举每个间隔，找到满足条件的区间范围，计算贡献并累加。

```cpp
for(int i = 1; i < n; i++){
    int k = i + 1;
    mm[i] = inf;
    while(k <= n && a[k] > a[i]){
        mm[k] = min(mm[k - 1], a[k]);
        k++;
    }
    k--;
    maxn = a[i];
    for(int j = i; j; j--){
        if(a[j] > maxn) maxn = a[j];
        while(k >= i + 1 && mm[k] < maxn) k--;
        ans -= k - i;
    }
}
```

【最优关键思路】
通过枚举每个元素作为区间的最小值，利用贪心策略找到极大范围，并通过预处理减少时间复杂度。这种方法的核心在于通过预处理和边界查找，将时间复杂度从 $O(n^3)$ 优化到 $O(n^2)$。

【拓展思路】
类似的问题可以通过贪心策略和区间分割来优化，尤其是在需要计算所有子数组的某些属性时。可以考虑使用单调栈、二分查找等数据结构来进一步优化时间复杂度。

【推荐题目】
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
3. [P3372 线段树 1](https://www.luogu.com.cn/problem/P3372)

---
处理用时：59.41秒