# 题目信息

# Flying Sort (Easy Version)

## 题目描述

This is an easy version of the problem. In this version, all numbers in the given array are distinct and the constraints on $ n $ are less than in the hard version of the problem.

You are given an array $ a $ of $ n $ integers (there are no equals elements in the array). You can perform the following operations on array elements:

1. choose any index $ i $ ( $ 1 \le i \le n $ ) and move the element $ a[i] $ to the begin of the array;
2. choose any index $ i $ ( $ 1 \le i \le n $ ) and move the element $ a[i] $ to the end of the array.

For example, if $ n = 5 $ , $ a = [4, 7, 2, 3, 9] $ , then the following sequence of operations can be performed:

- after performing the operation of the first type to the second element, the array $ a $ will become $ [7, 4, 2, 3, 9] $ ;
- after performing the operation of the second type to the second element, the array $ a $ will become $ [7, 2, 3, 9, 4] $ .

You can perform operations of any type any number of times in any order.

Find the minimum total number of operations of the first and second type that will make the $ a $ array sorted in non-decreasing order. In other words, what is the minimum number of operations that must be performed so the array satisfies the inequalities $ a[1] \le a[2] \le \ldots \le a[n] $ .

## 说明/提示

In the first test case, you first need to move 3, and then 2 to the beginning of the array. Therefore, the desired sequence of operations: $ [4, 7, 2, 3, 9] \rightarrow [3, 4, 7, 2, 9] \rightarrow [2, 3, 4, 7, 9] $ .

In the second test case, you need to move the 1 to the beginning of the array, and the 8 — to the end. Therefore, the desired sequence of operations: $ [3, 5, 8, 1, 7] \rightarrow [1, 3, 5, 8, 7] \rightarrow [1, 3, 5, 7, 8] $ .

In the third test case, the array is already sorted.

## 样例 #1

### 输入

```
4
5
4 7 2 3 9
5
3 5 8 1 7
5
1 4 5 7 12
4
0 2 1 3```

### 输出

```
2
2
0
2```

# AI分析结果

### 题目中文重写
# 飞行排序（简单版本）

## 题目描述
这是该问题的简单版本。在此版本中，给定数组中的所有数字都是不同的，并且 $n$ 的约束条件比问题的困难版本要小。

你将得到一个包含 $n$ 个整数的数组 $a$（数组中没有相等的元素）。你可以对数组元素执行以下操作：
1. 选择任意索引 $i$（$1 \leq i \leq n$），并将元素 $a[i]$ 移动到数组的开头；
2. 选择任意索引 $i$（$1 \leq i \leq n$），并将元素 $a[i]$ 移动到数组的末尾。

例如，如果 $n = 5$，$a = [4, 7, 2, 3, 9]$，那么可以执行以下操作序列：
- 对第二个元素执行第一种类型的操作后，数组 $a$ 将变为 $[7, 4, 2, 3, 9]$；
- 对第二个元素执行第二种类型的操作后，数组 $a$ 将变为 $[7, 2, 3, 9, 4]$。

你可以按任意顺序执行任意类型的操作任意次数。

找出使数组 $a$ 按非递减顺序排序所需的第一种和第二种类型操作的最小总数。换句话说，必须执行的最小操作数是多少，才能使数组满足不等式 $a[1] \leq a[2] \leq \ldots \leq a[n]$。

## 说明/提示
在第一个测试用例中，你首先需要将 3，然后将 2 移动到数组的开头。因此，所需的操作序列为：$[4, 7, 2, 3, 9] \rightarrow [3, 4, 7, 2, 9] \rightarrow [2, 3, 4, 7, 9]$。

在第二个测试用例中，你需要将 1 移动到数组的开头，将 8 移动到数组的末尾。因此，所需的操作序列为：$[3, 5, 8, 1, 7] \rightarrow [1, 3, 5, 8, 7] \rightarrow [1, 3, 5, 7, 8]$。

在第三个测试用例中，数组已经是有序的。

## 样例 #1
### 输入
```
4
5
4 7 2 3 9
5
3 5 8 1 7
5
1 4 5 7 12
4
0 2 1 3
```
### 输出
```
2
2
0
2
```

### 算法分类
动态规划

### 综合分析与结论
这些题解的核心思路都是先对数组进行离散化处理，将其转化为一个排列，然后通过动态规划的方法找出数组内最长的相差为 1 的子序列（即最长连续数字上升子序列），最后用数组的长度减去这个最长子序列的长度，就得到了使数组有序的最小操作次数。

各题解的思路和算法要点基本一致，主要区别在于代码实现的细节和风格。难点在于如何将原问题转化为寻找最长连续数字上升子序列的问题，以及如何通过动态规划来求解这个子序列的长度。

### 所选题解
- **F_Mu（5星）**：
    - **关键亮点**：思路清晰，代码注释详细，使用了常见的代码优化技巧，如 `#pragma GCC optimize(3, "Ofast", "inline")` 和 `ios::sync_with_stdio(false)` 来提高程序运行效率。
- **_Kenma_（4星）**：
    - **关键亮点**：代码简洁，实现了核心算法，对思路的分析较为清晰。
- **August_Light（4星）**：
    - **关键亮点**：详细介绍了离散化的实现过程，并将其封装成了一个命名空间，代码结构清晰，可读性强。

### 重点代码
#### F_Mu 的核心代码
```cpp
rep(i, 1, n) {
    dp[a[i]] = dp[a[i] - 1] + 1;
    maxx = max(maxx, dp[a[i]]);
}
cout << n - maxx << '\n';
```
**核心实现思想**：通过动态规划的方法，`dp[a[i]]` 表示以数字 `a[i]` 为结尾的最长子序列长度，状态转移方程为 `dp[a[i]] = dp[a[i] - 1] + 1`，最后找出最大的 `dp` 值，用数组长度减去它得到最小操作次数。

#### _Kenma_ 的核心代码
```cpp
for(int i=1;i<=n;i++){
    f[a[i]]=f[a[i]-1]+1;
    maxn=max(maxn,f[a[i]]);
}
cout<<n-maxn<<'\n';
```
**核心实现思想**：与 F_Mu 的思路相同，使用 `f` 数组记录以 `a[i]` 为结尾的最长子序列长度，更新最大值 `maxn`，最后输出 `n - maxn`。

#### August_Light 的核心代码
```cpp
for (int i = 1; i <= n; i++)
    pos[p[i]] = i;
for (int i = 1; i <= n; i++) {
    f[i] = 1;
    if (pos[p[i] - 1] < i)
        f[i] += f[pos[p[i] - 1]];
    ans = max(ans, f[i]);
}
write(n - ans, '\n');
```
**核心实现思想**：先记录每个数在数列中的位置，然后通过动态规划更新 `f[i]`，表示以第 `i` 个数结尾的最长满足条件的子序列长度，最后输出 `n - ans`。

### 扩展思路
同类型题或类似算法套路：这类问题通常涉及到对数组的操作和排序，关键在于找出不需要操作的最长子序列。可以通过离散化将问题简化，再利用动态规划求解。类似的题目可能会有不同的操作规则，但核心思路都是寻找最优的子结构。

### 推荐题目
1. [P1966 火柴排队](https://www.luogu.com.cn/problem/P1966)：涉及到离散化和排序的思想。
2. [P2676 [USACO07DEC]Bookshelf B](https://www.luogu.com.cn/problem/P2676)：需要对数组进行操作以满足一定条件，与本题思路有相似之处。
3. [P1090 [NOIP2004 提高组] 合并果子](https://www.luogu.com.cn/problem/P1090)：可以通过贪心和优先队列来解决，锻炼对数组操作和优化的能力。

### 个人心得
无。

---
处理用时：42.54秒