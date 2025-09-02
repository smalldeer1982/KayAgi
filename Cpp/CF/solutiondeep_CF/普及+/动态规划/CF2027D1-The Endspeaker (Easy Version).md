# 题目信息

# The Endspeaker (Easy Version)

## 题目描述

This is the easy version of this problem. The only difference is that you only need to output the minimum total cost of operations in this version. You must solve both versions to be able to hack.

You're given an array $ a $ of length $ n $ , and an array $ b $ of length $ m $ ( $ b_i > b_{i+1} $ for all $ 1 \le i < m $ ). Initially, the value of $ k $ is $ 1 $ . Your aim is to make the array $ a $ empty by performing one of these two operations repeatedly:

- Type $ 1 $ — If the value of $ k $ is less than $ m $ and the array $ a $ is not empty, you can increase the value of $ k $ by $ 1 $ . This does not incur any cost.
- Type $ 2 $ — You remove a non-empty prefix of array $ a $ , such that its sum does not exceed $ b_k $ . This incurs a cost of $ m - k $ .

You need to minimize the total cost of the operations to make array $ a $ empty. If it's impossible to do this through any sequence of operations, output $ -1 $ . Otherwise, output the minimum total cost of the operations.

## 说明/提示

In the first test case, one optimal sequence of operations which yields a total cost of $ 1 $ is as follows:

- Perform an operation of type $ 2 $ . Choose the prefix to be $ [9] $ . This incurs a cost of $ 1 $ .
- Perform an operation of type $ 1 $ . The value of $ k $ is now $ 2 $ . This incurs no cost.
- Perform an operation of type $ 2 $ . Choose the prefix to be $ [3, 4] $ . This incurs a cost of $ 0 $ .
- Perform an operation of type $ 2 $ . Choose the prefix to be $ [3] $ . This incurs a cost of $ 0 $ .
- The array $ a $ is now empty, and the total cost of all operations is $ 1 $ .

In the second test case, it's impossible to remove any prefix of the array since $ a_1 > b_1 $ , so array $ a $ cannot be made empty by any sequence of operations.

## 样例 #1

### 输入

```
5
4 2
9 3 4 3
11 7
1 2
20
19 18
10 2
2 5 2 1 10 3 2 9 9 6
17 9
10 11
2 2 2 2 2 2 2 2 2 2
20 18 16 14 12 10 8 6 4 2 1
1 6
10
32 16 8 4 2 1```

### 输出

```
1
-1
2
10
4```

# AI分析结果

【题目内容】
# The Endspeaker (Easy Version)

## 题目描述

这是该问题的简单版本。唯一区别在于，此版本只需输出操作的最小总成本。你必须解决两个版本才能进行hack。

给定一个长度为 $n$ 的数组 $a$，和一个长度为 $m$ 的数组 $b$（$b_i > b_{i+1}$ 对于所有 $1 \le i < m$）。初始时，$k$ 的值为 $1$。你的目标是通过反复执行以下两种操作之一，使数组 $a$ 为空：

- 类型 $1$ — 如果 $k$ 的值小于 $m$ 且数组 $a$ 不为空，你可以将 $k$ 的值增加 $1$。此操作不产生任何成本。
- 类型 $2$ — 你可以移除数组 $a$ 的一个非空前缀，且其和不超过 $b_k$。此操作产生 $m - k$ 的成本。

你需要最小化使数组 $a$ 为空的操作总成本。如果无法通过任何操作序列使数组 $a$ 为空，则输出 $-1$。否则，输出操作的最小总成本。

## 说明/提示

在第一个测试用例中，一个最优的操作序列如下，总成本为 $1$：

- 执行类型 $2$ 操作。选择前缀 $[9]$。此操作产生 $1$ 的成本。
- 执行类型 $1$ 操作。$k$ 的值变为 $2$。此操作不产生成本。
- 执行类型 $2$ 操作。选择前缀 $[3, 4]$。此操作产生 $0$ 的成本。
- 执行类型 $2$ 操作。选择前缀 $[3]$。此操作产生 $0$ 的成本。
- 数组 $a$ 现在为空，所有操作的总成本为 $1$。

在第二个测试用例中，由于 $a_1 > b_1$，无法移除任何前缀，因此无法通过任何操作序列使数组 $a$ 为空。

## 样例 #1

### 输入

```
5
4 2
9 3 4 3
11 7
1 2
20
19 18
10 2
2 5 2 1 10 3 2 9 9 6
17 9
10 11
2 2 2 2 2 2 2 2 2 2
20 18 16 14 12 10 8 6 4 2 1
1 6
10
32 16 8 4 2 1```

### 输出

```
1
-1
2
10
4```

【题解分析与结论】
本题的核心是通过动态规划（DP）来最小化操作成本。各题解的主要思路都是通过状态转移方程来计算最小成本，但具体实现和优化方式有所不同。以下是各题解的要点总结：

1. **Yorg** 的题解通过二维DP记录当前删除的前缀长度和$k$的值，优化了状态转移方程，时间复杂度为$O(nm\log m)$。
2. **Super_Cube** 的题解同样使用二维DP，但通过二分查找来优化转移，时间复杂度为$O(nm\log n)$。
3. **灵乌路空** 的题解通过滚动数组和双指针优化，将时间复杂度降低到$O(nm)$，空间复杂度也得到优化。
4. **program_xwl** 的题解通过预处理和二分查找来优化DP转移，时间复杂度为$O(nm\log n)$。
5. **z_yq** 的题解通过二分查找和DP转移，时间复杂度为$O(nm\log n)$。
6. **limingyuan333** 的题解通过预处理和二分查找来优化DP转移，时间复杂度为$O(nm\log n)$。
7. **I_will_AKIOI** 的题解通过线段树优化DP转移，时间复杂度为$O(nm\log n)$。
8. **liugh_** 的题解通过贪心和前缀最小值优化DP转移，时间复杂度为$O(nm)$。

【评分较高的题解】
1. **灵乌路空**（5星）
   - 关键亮点：通过滚动数组和双指针优化，将时间复杂度降低到$O(nm)$，空间复杂度也得到优化。
   - 代码实现简洁，思路清晰，优化效果显著。

2. **liugh_**（4星）
   - 关键亮点：通过贪心和前缀最小值优化DP转移，时间复杂度为$O(nm)$。
   - 代码实现简洁，思路清晰，优化效果显著。

3. **Super_Cube**（4星）
   - 关键亮点：通过二分查找来优化转移，时间复杂度为$O(nm\log n)$。
   - 代码实现简洁，思路清晰，优化效果显著。

【最优关键思路或技巧】
- **滚动数组与双指针优化**：通过滚动数组减少空间复杂度，利用双指针优化转移过程，将时间复杂度降低到$O(nm)$。
- **贪心与前缀最小值优化**：通过贪心策略选择最优转移点，利用前缀最小值优化DP转移，时间复杂度为$O(nm)$。

【可拓展之处】
- 类似问题可以通过动态规划结合贪心策略来优化，尤其是在状态转移过程中存在单调性时，双指针和滚动数组是常见的优化手段。

【推荐题目】
1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
2. [P1064 金明的预算方案](https://www.luogu.com.cn/problem/P1064)
3. [P2014 选课](https://www.luogu.com.cn/problem/P2014)

【个人心得摘录】
- **灵乌路空**：通过手动模拟发现$k$的单调性，进而优化了状态转移方程，减少了重复计算。
- **liugh_**：贪心地选择$k$越小越好，利用前缀最小值优化了DP转移，减少了不必要的计算。

【核心代码片段】
```cpp
// 灵乌路空的代码片段
for (int i = 1; i <= m; ++ i, now ^= 1) {
    for (int r = 1, l = 1; r <= n; ++ r) {
        f[now][r] = f[now ^ 1][r];
        while (l <= r && sum[r] - sum[l - 1] > b[i]) ++ l;
        if (l <= r) f[now][r] = std::min(f[now][r], f[now][l - 1] + m - i);
    }
}
```
- **核心思想**：通过双指针优化转移过程，利用前缀和快速判断是否可以进行转移，减少了时间复杂度。

---
处理用时：54.87秒