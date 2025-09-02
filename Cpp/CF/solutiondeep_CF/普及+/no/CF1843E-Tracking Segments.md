# 题目信息

# Tracking Segments

## 题目描述

You are given an array $ a $ consisting of $ n $ zeros. You are also given a set of $ m $ not necessarily different segments. Each segment is defined by two numbers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le n $ ) and represents a subarray $ a_{l_i}, a_{l_i+1}, \dots, a_{r_i} $ of the array $ a $ .

Let's call the segment $ l_i, r_i $ beautiful if the number of ones on this segment is strictly greater than the number of zeros. For example, if $ a = [1, 0, 1, 0, 1] $ , then the segment $ [1, 5] $ is beautiful (the number of ones is $ 3 $ , the number of zeros is $ 2 $ ), but the segment $ [3, 4] $ is not is beautiful (the number of ones is $ 1 $ , the number of zeros is $ 1 $ ).

You also have $ q $ changes. For each change you are given the number $ 1 \le x \le n $ , which means that you must assign an element $ a_x $ the value $ 1 $ .

You have to find the first change after which at least one of $ m $ given segments becomes beautiful, or report that none of them is beautiful after processing all $ q $ changes.

## 说明/提示

In the first case, after first 2 changes we won't have any beautiful segments, but after the third one on a segment $ [1; 5] $ there will be 3 ones and only 2 zeros, so the answer is 3.

In the second case, there won't be any beautiful segments.

## 样例 #1

### 输入

```
6
5 5
1 2
4 5
1 5
1 3
2 4
5
5
3
1
2
4
4 2
1 1
4 4
2
2
3
5 2
1 5
1 5
4
2
1
3
4
5 2
1 5
1 3
5
4
1
2
3
5
5 5
1 5
1 5
1 5
1 5
1 4
3
1
4
3
3 2
2 2
1 3
3
2
3
1```

### 输出

```
3
-1
3
3
3
1```

# AI分析结果

### 题目内容重写
给定一个由 $n$ 个零组成的数组 $a$。同时给定 $m$ 个不一定不同的区间，每个区间由两个数 $l_i$ 和 $r_i$（$1 \le l_i \le r_i \le n$）定义，表示数组 $a$ 的子数组 $a_{l_i}, a_{l_i+1}, \dots, a_{r_i}$。

定义一个区间 $[l_i, r_i]$ 为“美丽的”，如果该区间内 $1$ 的数量严格大于 $0$ 的数量。例如，如果 $a = [1, 0, 1, 0, 1]$，那么区间 $[1, 5]$ 是美丽的（$1$ 的数量为 $3$，$0$ 的数量为 $2$），但区间 $[3, 4]$ 不是美丽的（$1$ 的数量为 $1$，$0$ 的数量为 $1$）。

你还有 $q$ 次修改操作。每次修改操作给定一个数 $1 \le x \le n$，表示将 $a_x$ 的值赋为 $1$。

你需要找到第一个修改操作，使得在完成该操作后，至少有一个给定的区间是美丽的。如果所有修改操作完成后仍没有区间是美丽的，则输出 $-1$。

### 算法分类
二分、前缀和

### 题解分析与结论
本题的核心在于找到第一个使得至少一个区间变得美丽的修改操作。由于每次操作都是将 $0$ 变为 $1$，因此区间的美丽性具有单调性，即随着操作次数的增加，区间的美丽性不会减少。这使得二分查找成为解决该问题的有效方法。

### 所选高分题解
#### 1. 作者：Xy_top (赞：12)
**星级：5星**
**关键亮点：**
- 使用二分查找来确定第一个满足条件的操作。
- 通过前缀和快速计算区间内 $1$ 的数量。
- 代码简洁，时间复杂度为 $O(\max(n, m) \times \log n)$。

**核心代码：**
```cpp
bool check(int x) {
    for (int i = 1; i <= n; i++) s[i] = 0;
    for (int i = 1; i <= x; i++) ++s[upd[i]];
    for (int i = 1; i <= n; i++) s[i] += s[i - 1];
    for (int i = 1; i <= m; i++) 
        if (2 * (s[a[i].r] - s[a[i].l - 1]) > a[i].r - a[i].l + 1) return true;
    return false;
}
```
**代码思想：**
- `check` 函数用于判断前 `x` 次操作后是否有区间变得美丽。
- 使用前缀和数组 `s` 来快速计算区间内 $1$ 的数量。

#### 2. 作者：Wf_yjqd (赞：6)
**星级：4星**
**关键亮点：**
- 使用分块思想，每 $\sqrt{q}$ 次操作进行一次检查。
- 通过排序区间长度优化检查顺序。
- 时间复杂度为 $O(m \times \sqrt{q})$。

**核心代码：**
```cpp
inline bool check() {
    for (int i = 1; i <= n; i++) b[i] = b[i - 1] + (a[i] == 1 ? 1 : -1);
    for (int i = 1; i <= m; i++)
        if (b[s[i].r] - b[s[i].l - 1] > 0) return 1;
    return 0;
}
```
**代码思想：**
- `check` 函数用于检查当前操作后是否有区间变得美丽。
- 使用前缀和数组 `b` 来计算区间内 $1$ 的数量。

#### 3. 作者：Auto_Accepted (赞：3)
**星级：4星**
**关键亮点：**
- 使用二分查找和排序来优化区间检查。
- 通过二分查找快速确定满足条件的操作。
- 时间复杂度为 $O(\log q \times (q + n + m))$。

**核心代码：**
```cpp
inline bool check(int mid) {
    for (int i = 1; i <= mid; i++) tmp[i] = a[i];
    sort(tmp + 1, tmp + mid + 1);
    for (int i = 1; i <= m; i++) {
        int tl = lower_bound(tmp + 1, tmp + mid + 1, l[i]) - tmp;
        int tr = upper_bound(tmp + 1, tmp + mid + 1, r[i]) - tmp - 1;
        if (tr - tl + 1 >= (r[i] - l[i] + 1) / 2 + 1) return 1;
    }
    return 0;
}
```
**代码思想：**
- `check` 函数用于判断前 `mid` 次操作后是否有区间变得美丽。
- 使用排序和二分查找来快速计算区间内 $1$ 的数量。

### 最优关键思路与技巧
1. **二分查找**：利用单调性，通过二分查找快速确定第一个满足条件的操作。
2. **前缀和**：通过前缀和数组快速计算区间内 $1$ 的数量，避免重复计算。
3. **分块思想**：通过分块减少检查次数，优化时间复杂度。

### 可拓展之处
- 类似的问题可以扩展到多维数组或更复杂的区间查询。
- 可以结合其他数据结构如线段树或树状数组来进一步优化查询效率。

### 推荐题目
1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

### 个人心得摘录
- **Xy_top**：通过二分查找和前缀和的结合，能够高效地解决问题，代码简洁且易于理解。
- **Wf_yjqd**：分块思想虽然不如二分查找直观，但在某些情况下能够有效减少检查次数，提升性能。

---
处理用时：49.17秒