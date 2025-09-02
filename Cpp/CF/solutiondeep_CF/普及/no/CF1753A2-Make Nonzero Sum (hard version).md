# 题目信息

# Make Nonzero Sum (hard version)

## 题目描述

This is the hard version of the problem. The difference is that in this version the array contains zeros. You can make hacks only if both versions of the problem are solved.

You are given an array $ [a_1, a_2, \ldots a_n] $ consisting of integers $ -1 $ , $ 0 $ and $ 1 $ . You have to build a partition of this array into the set of segments $ [l_1, r_1], [l_2, r_2], \ldots, [l_k, r_k] $ with the following property:

- Denote the alternating sum of all elements of the $ i $ -th segment as $ s_i $ : $ s_i $ = $ a_{l_i} - a_{l_i+1} + a_{l_i+2} - a_{l_i+3} + \ldots \pm a_{r_i} $ . For example, the alternating sum of elements of segment $ [2, 4] $ in array $ [1, 0, -1, 1, 1] $ equals to $ 0 - (-1) + 1 = 2 $ .
- The sum of $ s_i $ over all segments of partition should be equal to zero.

Note that each $ s_i $ does not have to be equal to zero, this property is about sum of $ s_i $ over all segments of partition.

The set of segments $ [l_1, r_1], [l_2, r_2], \ldots, [l_k, r_k] $ is called a partition of the array $ a $ of length $ n $ if $ 1 = l_1 \le r_1, l_2 \le r_2, \ldots, l_k \le r_k = n $ and $ r_i + 1 = l_{i+1} $ for all $ i = 1, 2, \ldots k-1 $ . In other words, each element of the array must belong to exactly one segment.

You have to build a partition of the given array with properties described above or determine that such partition does not exist.

Note that it is not required to minimize the number of segments in the partition.

## 说明/提示

In the first test case we can build a partition of $ 4 $ segments — each of them will contain only one element of the array equals to $ 0 $ . So the sum will be equal to $ 0 + 0 + 0 + 0 = 0 $ .

In the second test case we can build a partition of $ 4 $ segments. The alternating sum of the first segment will be equal to $ -1 $ , the alternating sum of the second segment will be equal to $ 1 $ , of the third segment — $ 0 - 1 + 0 = -1 $ , of the fourth segment — $ 1 - 0 = 1 $ . The sum will be equal to $ -1 + 1 -1 + 1 = 0 $ .

In the third test case it can be proved that the required partition does not exist.

## 样例 #1

### 输入

```
5
4
0 0 0 0
7
-1 1 0 1 0 1 0
5
0 -1 1 0 1
3
1 0 1
1
1```

### 输出

```
4
1 1
2 2
3 3
4 4
4
1 1
2 2
3 5
6 7
-1
2
1 1
2 3
-1```

# AI分析结果

### 题目重写
**题目描述**

这是该问题的困难版本。与简单版本的区别在于，此版本中的数组包含零。只有在两个版本的问题都解决的情况下，才能进行 hack。

给定一个由整数 $-1$、$0$ 和 $1$ 组成的数组 $[a_1, a_2, \ldots, a_n]$。你需要将这个数组划分为若干段 $[l_1, r_1], [l_2, r_2], \ldots, [l_k, r_k]$，满足以下条件：

- 定义第 $i$ 段的交替和为 $s_i$：$s_i = a_{l_i} - a_{l_i+1} + a_{l_i+2} - a_{l_i+3} + \ldots \pm a_{r_i}$。例如，数组 $[1, 0, -1, 1, 1]$ 中段 $[2, 4]$ 的交替和为 $0 - (-1) + 1 = 2$。
- 所有段的交替和 $s_i$ 的总和应为零。

注意，每个 $s_i$ 不必为零，此条件是关于所有段的交替和的总和。

段集 $[l_1, r_1], [l_2, r_2], \ldots, [l_k, r_k]$ 称为数组 $a$ 的划分，如果 $1 = l_1 \le r_1, l_2 \le r_2, \ldots, l_k \le r_k = n$ 且 $r_i + 1 = l_{i+1}$ 对所有 $i = 1, 2, \ldots, k-1$ 成立。换句话说，数组的每个元素必须恰好属于一个段。

你需要构建一个满足上述条件的划分，或者确定这样的划分不存在。

注意，不要求最小化划分中的段数。

### 算法分类
贪心、构造

### 题解分析与结论
该题的核心在于如何通过合理的分段使得所有段的交替和的总和为零。由于数组包含零，处理起来比简单版本更加复杂。大多数题解都采用了贪心策略，通过逐步调整分段来达到目标。

### 精选题解

#### 题解1：bsTiat (赞：7)
**星级：5**
**关键亮点：**
- 通过贪心策略，逐个元素判断是否取反，确保交替和的总和为零。
- 代码简洁，逻辑清晰，易于理解。

**核心代码：**
```cpp
for(int i=2;i<=n;++i)
    if(abs(sum-2*a[i])<abs(sum)&&!g[i-1])
        g[i]=1,--cnt,sum-=2*a[i];
```
**实现思想：**
从第二个元素开始，逐个判断是否取反，若取反后交替和的绝对值减小，则进行取反操作，并标记下一个元素不能取反。

#### 题解2：Alex_Wei (赞：5)
**星级：4**
**关键亮点：**
- 通过配对非零元素，确保每对的交替和为零。
- 处理零元素时，将其单独分段，不影响整体交替和。

**核心代码：**
```cpp
if(a_x + a_y == 0)
    ans.emplace_back(make_pair(x, y - 1));
    ans.emplace_back(make_pair(y, y));
```
**实现思想：**
将相邻的非零元素配对，若它们的和为零，则分别分段；否则，通过调整分段长度使交替和为零。

#### 题解3：SoyTony (赞：1)
**星级：4**
**关键亮点：**
- 通过将偶数位的元素取反，简化问题为反转区间的问题。
- 通过反转区间逐步调整交替和，最终使其为零。

**核心代码：**
```cpp
for(int i=2;i<=n;i+=2)
    if(a[i]<=0)
        b[i]=1;
        tot-=a[i]+a[i];
```
**实现思想：**
将偶数位的元素取反，若取反后交替和的绝对值减小，则进行取反操作，并逐步调整分段。

### 最优关键思路
1. **贪心策略**：通过逐个元素判断是否取反，确保交替和的总和为零。
2. **配对非零元素**：将相邻的非零元素配对，确保每对的交替和为零。
3. **反转区间**：通过反转区间逐步调整交替和，最终使其为零。

### 拓展思路
该题的思路可以拓展到其他需要分段处理的问题，尤其是涉及到交替和或类似条件的问题。例如，可以通过类似的方法处理数组中的其他特殊元素，或者应用于更复杂的分段条件。

### 推荐题目
1. [CF1753A1 - Make Nonzero Sum (easy version)](https://www.luogu.com.cn/problem/CF1753A1)
2. [CF1753A2 - Make Nonzero Sum (hard version)](https://www.luogu.com.cn/problem/CF1753A2)
3. [CF1753B - Make Nonzero Sum (hard version)](https://www.luogu.com.cn/problem/CF1753B)

---
处理用时：36.17秒