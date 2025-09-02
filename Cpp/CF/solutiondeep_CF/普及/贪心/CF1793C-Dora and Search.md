# 题目信息

# Dora and Search

## 题目描述

As you know, the girl Dora is always looking for something. This time she was given a permutation, and she wants to find such a subsegment of it that none of the elements at its ends is either the minimum or the maximum of the entire subsegment. More formally, you are asked to find the numbers $ l $ and $ r $ $ (1 \leq l \leq r \leq n) $ such that $ a_l \neq \min(a_l, a_{l + 1}, \ldots, a_r) $ , $ a_l \neq \max(a_l, a_{l + 1}, \ldots, a_r) $ and $ a_r \neq \min(a_l, a_{l + 1}, \ldots, a_r) $ , $ a_r \neq \max(a_l, a_{l + 1}, \ldots, a_r) $ .

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ occurs twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ , but $ 4 $ is present in the array).

Help Dora find such a subsegment, or tell her that such a subsegment does not exist.

## 说明/提示

In the first and fourth test cases, it can be shown that there are no desired subsegments.

In the second test case, the subsegment $ [1, 4] $ satisfies all the conditions, because $ \max(a_1, a_2, a_3, a_4) = 4, \min(a_1, a_2, a_3, a_4) = 1 $ , as we see, all the conditions are met.

In the third test case, the subsegment $ [2, 6] $ also satisfies all the conditions described.

## 样例 #1

### 输入

```
4
3
1 2 3
4
2 1 4 3
7
1 3 2 4 6 5 7
6
2 3 6 5 4 1```

### 输出

```
-1
1 4
2 6
-1```

# AI分析结果

### 题目内容重写

# Dora 和搜索

## 题目描述

众所周知，女孩 Dora 总是在寻找某些东西。这次，她得到了一个排列，她想找到它的一个子段，使得该子段的两个端点都不是整个子段的最小值或最大值。更正式地说，你需要找到两个数 $l$ 和 $r$ $ (1 \leq l \leq r \leq n) $，使得 $a_l \neq \min(a_l, a_{l + 1}, \ldots, a_r)$，$a_l \neq \max(a_l, a_{l + 1}, \ldots, a_r)$，并且 $a_r \neq \min(a_l, a_{l + 1}, \ldots, a_r)$，$a_r \neq \max(a_l, a_{l + 1}, \ldots, a_r)$。

一个长度为 $n$ 的排列是一个由 $1$ 到 $n$ 的 $n$ 个不同整数组成的数组，顺序任意。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（$2$ 在数组中出现了两次），$[1,3,4]$ 也不是排列（$n=3$，但数组中出现了 $4$）。

帮助 Dora 找到这样的子段，或者告诉她这样的子段不存在。

## 说明/提示

在第一个和第四个测试用例中，可以证明不存在满足条件的子段。

在第二个测试用例中，子段 $[1, 4]$ 满足所有条件，因为 $\max(a_1, a_2, a_3, a_4) = 4$，$\min(a_1, a_2, a_3, a_4) = 1$，我们可以看到所有条件都满足。

在第三个测试用例中，子段 $[2, 6]$ 也满足所有描述的条件。

## 样例 #1

### 输入

```
4
3
1 2 3
4
2 1 4 3
7
1 3 2 4 6 5 7
6
2 3 6 5 4 1```

### 输出

```
-1
1 4
2 6
-1```

### 题解分析与结论

#### 综合分析
本题的核心是找到一个子段，使得该子段的两个端点都不是该子段的最小值或最大值。多个题解都采用了双指针的方法，通过不断缩小区间来寻找符合条件的子段。双指针的优点是时间复杂度较低，通常为 $O(n)$，适合处理大规模数据。

#### 最优关键思路
1. **双指针法**：从整个数组的两端开始，逐步缩小区间，直到找到符合条件的子段或确定无解。
2. **维护当前区间的最小值和最大值**：通过不断更新当前区间的最小值和最大值，判断端点是否满足条件。
3. **线性时间复杂度**：通过双指针的移动，确保算法的时间复杂度为 $O(n)$。

#### 可拓展之处
- **类似问题**：类似的双指针法可以用于解决其他需要寻找满足特定条件的子段的问题，如寻找最长不重复子串、寻找和为特定值的子段等。
- **数据结构优化**：在某些情况下，可以使用单调栈或RMQ（区间最值查询）来进一步优化算法的效率。

### 推荐题目
1. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
2. [P1638 逛画展](https://www.luogu.com.cn/problem/P1638)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

### 所选高星题解

#### 题解1：作者：TernaryTree (赞：8)
- **星级**：5星
- **关键亮点**：简洁高效的双指针实现，代码清晰易懂，时间复杂度为 $O(n)$。
- **核心代码**：
```cpp
while (l <= r) {
    if (a[l] == mn) {
        ++l, ++mn;
    } else if (a[l] == mx) {
        ++l, --mx;
    } else if (a[r] == mn) {
        --r, ++mn;
    } else if (a[r] == mx) {
        --r, --mx;
    } else {
        break;
    }
}
if (l > r) puts("-1");
else cout << l << " " << r << endl;
```
- **核心思想**：通过双指针不断缩小区间，同时更新当前区间的最小值和最大值，直到找到符合条件的子段或确定无解。

#### 题解2：作者：hswfwkj_ (赞：6)
- **星级**：4星
- **关键亮点**：详细解释了双指针的正确性，代码实现简洁，时间复杂度为 $O(n)$。
- **核心代码**：
```cpp
while (1) {
    if (l > r) {cout << -1 << '\n'; goto here;}
    if (a[l] == maxn) {l++, maxn--; continue;}
    if (a[l] == minn) {l++, minn++; continue;}
    if (a[r] == maxn) {r--, maxn--; continue;}
    if (a[r] == minn) {r--, minn++; continue;}           
    break;
}
cout << l << ' ' << r << '\n';
```
- **核心思想**：通过双指针不断缩小区间，同时更新当前区间的最小值和最大值，直到找到符合条件的子段或确定无解。

#### 题解3：作者：zhuweiqi (赞：1)
- **星级**：4星
- **关键亮点**：使用双端队列实现双指针，代码实现较为独特，时间复杂度为 $O(n)$。
- **核心代码**：
```cpp
while (q.size()) {
    int flag = 0;
    if (q.size() && q.front() == mins) {
        mins++;
        q.pop_front();
        book.pop_front();
        flag = 1;
    } else if (q.size() && q.front() == maxs) {
        maxs--;
        q.pop_front();
        book.pop_front();
        flag = 1;
    }
    if (q.size() && q.back() == mins) {
        mins++;
        q.pop_back();
        book.pop_back();
        flag = 1;
    } else if (q.size() && q.back() == maxs) {
        maxs--;
        q.pop_back();
        book.pop_back();
        flag = 1;
    }
    if (flag == 0) break;
}
if (q.size()) printf("%d %d\n", book.front(), book.back());
else printf("%d\n", -1);
```
- **核心思想**：通过双端队列模拟双指针的移动，同时更新当前区间的最小值和最大值，直到找到符合条件的子段或确定无解。

### 个人心得总结
- **调试经历**：在实现双指针时，需要注意指针的移动顺序和条件判断，避免遗漏某些情况。
- **踩坑教训**：在更新最小值和最大值时，需要确保更新的顺序正确，否则可能导致错误的结果。
- **顿悟感想**：双指针法在处理区间问题时非常高效，通过不断缩小区间可以快速找到符合条件的解。

---
处理用时：54.22秒