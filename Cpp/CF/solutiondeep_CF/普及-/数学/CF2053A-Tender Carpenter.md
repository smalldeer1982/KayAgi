# 题目信息

# Tender Carpenter

## 题目描述

I would use a firework to announce, a wave to bid farewell, and a bow to say thanks: bygones are bygones; not only on the following path will I be walking leisurely and joyfully, but also the footsteps won't halt as time never leaves out flowing; for in the next year, we will meet again.

— Cocoly1990, [Goodbye 2022](https://www.luogu.com.cn/problem/P8941)



In his dream, Cocoly would go on a long holiday with no worries around him. So he would try out for many new things, such as... being a carpenter. To learn it well, Cocoly decides to become an apprentice of Master, but in front of him lies a hard task waiting for him to solve.

Cocoly is given an array $ a_1, a_2,\ldots, a_n $ . Master calls a set of integers $ S $ stable if and only if, for any possible $ u $ , $ v $ , and $ w $ from the set $ S $ (note that $ u $ , $ v $ , and $ w $ do not necessarily have to be pairwise distinct), sticks of length $ u $ , $ v $ , and $ w $ can form a non-degenerate triangle $ ^{\text{∗}} $ .

Cocoly is asked to partition the array $ a $ into several (possibly, $ 1 $ or $ n $ ) non-empty continuous subsegments $ ^{\text{†}} $ , such that: for each of the subsegments, the set containing all the elements in it is stable.

Master wants Cocoly to partition $ a $ in at least two different $ ^{\text{‡}} $ ways. You have to help him determine whether it is possible.

 $ ^{\text{∗}} $ A triangle with side lengths $ x $ , $ y $ , and $ z $ is called non-degenerate if and only if:

- $ x + y > z $ ,
- $ y + z > x $ , and
- $ z + x > y $ .

 $ ^{\text{†}} $ A sequence $ b $ is a subsegment of a sequence $ c $ if $ b $ can be obtained from $ c $ by the deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

 $ ^{\text{‡}} $ Two partitions are considered different if and only if at least one of the following holds:

- the numbers of continuous subsegments split in two partitions are different;
- there is an integer $ k $ such that the lengths of the $ k $ -th subsegment in two partitions are different.

## 说明/提示

In the first test case, here are two possible partitions:

- $ [2, 3], [5, 7] $ , since 
  - $ [2, 3] $ is stable because sticks of lengths $ (2, 2, 2), (2, 2, 3), (2, 3, 3), (3, 3, 3) $ respectively can all form non-degenerate triangles.
  - $ [5, 7] $ is stable because sticks of lengths $ (5, 5, 5), (5, 5, 7), (5, 7, 7), (7, 7, 7) $ respectively can all form non-degenerate triangles.
- and $ [2], [3, 5], [7] $ , since 
  - $ [2] $ is stable because sticks of lengths $ (2, 2, 2) $ respectively can form a non-degenerate triangle.
  - $ [3, 5] $ is stable because sticks of lengths $ (3, 3, 3), (3, 3, 5), (3, 5, 5), (5, 5, 5) $ respectively can all form non-degenerate triangles.
  - $ [7] $ is stable because sticks of lengths $ (7, 7, 7) $ respectively can form a non-degenerate triangle.

Note that some other partitions also satisfy the constraints, such as $ [2], [3], [5], [7] $ and $ [2], [3], [5, 7] $ .

In the second test case, Cocoly can only partition each element as a single subsegment, resulting in $ [115], [9], [2], [28] $ . Since we only have one possible partition, the answer is $ \texttt{NO} $ .

In the third test case, please note that the partition $ [8, 4], [1], [6], [2] $ does not satisfy the constraints, because $ \{8, 4\} $ is not a stable set: sticks of lengths $ 4 $ , $ 4 $ , and $ 8 $ cannot form a non-degenerate triangle.

## 样例 #1

### 输入

```
5
4
2 3 5 7
4
115 9 2 28
5
8 4 1 6 2
6
1 5 4 1 4 7
2
100000 100000```

### 输出

```
YES
NO
NO
YES
YES```

# AI分析结果

### 题目内容重写（中文）

# 温柔的木匠

## 题目描述

我会用烟花来宣告，用波浪来告别，用鞠躬来表达感谢：往事如烟；不仅在这条路上我会悠闲而愉快地行走，而且脚步不会停止，因为时间永远不会停止流逝；在明年，我们还会再见。

— Cocoly1990, [告别2022](https://www.luogu.com.cn/problem/P8941)

在梦中，Cocoly将度过一个无忧无虑的长假。因此，他决定尝试许多新事物，比如……成为一名木匠。为了学好木匠，Cocoly决定成为大师的学徒，但在他面前有一个艰巨的任务等待着他去解决。

Cocoly被给定一个数组 $ a_1, a_2,\ldots, a_n $ 。大师称一个整数集合 $ S $ 是稳定的，当且仅当对于集合 $ S $ 中的任意可能的 $ u $ , $ v $ , 和 $ w $ （注意 $ u $ , $ v $ , 和 $ w $ 不一定两两不同），长度为 $ u $ , $ v $ , 和 $ w $ 的木棍可以形成一个非退化三角形 $ ^{\text{∗}} $ 。

Cocoly被要求将数组 $ a $ 分割成若干个（可能是 $ 1 $ 或 $ n $ ）非空的连续子段 $ ^{\text{†}} $ ，使得：对于每个子段，包含其中所有元素的集合是稳定的。

大师希望Cocoly以至少两种不同的 $ ^{\text{‡}} $ 方式分割 $ a $ 。你需要帮助他确定是否可能。

 $ ^{\text{∗}} $ 一个边长为 $ x $ , $ y $ , 和 $ z $ 的三角形被称为非退化的，当且仅当：

- $ x + y > z $ ,
- $ y + z > x $ , 并且
- $ z + x > y $ 。

 $ ^{\text{†}} $ 一个序列 $ b $ 是序列 $ c $ 的子段，如果 $ b $ 可以通过从 $ c $ 的开头删除若干个（可能是零个或全部）元素，并从 $ c $ 的末尾删除若干个（可能是零个或全部）元素得到。

 $ ^{\text{‡}} $ 两个分割被认为是不同的，当且仅当至少满足以下条件之一：

- 两个分割中连续子段的数量不同；
- 存在一个整数 $ k $ ，使得两个分割中第 $ k $ 个子段的长度不同。

## 说明/提示

在第一个测试用例中，以下是两种可能的分割：

- $ [2, 3], [5, 7] $ ，因为 
  - $ [2, 3] $ 是稳定的，因为长度为 $ (2, 2, 2), (2, 2, 3), (2, 3, 3), (3, 3, 3) $ 的木棍分别可以形成非退化三角形。
  - $ [5, 7] $ 是稳定的，因为长度为 $ (5, 5, 5), (5, 5, 7), (5, 7, 7), (7, 7, 7) $ 的木棍分别可以形成非退化三角形。
- 以及 $ [2], [3, 5], [7] $ ，因为 
  - $ [2] $ 是稳定的，因为长度为 $ (2, 2, 2) $ 的木棍可以形成非退化三角形。
  - $ [3, 5] $ 是稳定的，因为长度为 $ (3, 3, 3), (3, 3, 5), (3, 5, 5), (5, 5, 5) $ 的木棍分别可以形成非退化三角形。
  - $ [7] $ 是稳定的，因为长度为 $ (7, 7, 7) $ 的木棍可以形成非退化三角形。

注意，其他一些分割也满足约束条件，例如 $ [2], [3], [5], [7] $ 和 $ [2], [3], [5, 7] $ 。

在第二个测试用例中，Cocoly只能将每个元素作为一个单独的子段分割，结果为 $ [115], [9], [2], [28] $ 。由于我们只有一种可能的分割，答案是 $ \texttt{NO} $ 。

在第三个测试用例中，请注意分割 $ [8, 4], [1], [6], [2] $ 不满足约束条件，因为 $ \{8, 4\} $ 不是一个稳定的集合：长度为 $ 4 $ , $ 4 $ , 和 $ 8 $ 的木棍不能形成非退化三角形。

## 样例 #1

### 输入

```
5
4
2 3 5 7
4
115 9 2 28
5
8 4 1 6 2
6
1 5 4 1 4 7
2
100000 100000```

### 输出

```
YES
NO
NO
YES
YES```

### 综合分析与结论

由于目前暂无题解，以下是一些通用建议与扩展思路：

1. **关键思路**：要解决这个问题，首先需要理解“稳定集合”的定义，即集合中的任意三个元素都能形成非退化三角形。这意味着集合中的元素不能存在较大的差异，特别是不能有元素大于或等于其他两个元素的和。

2. **算法要点**：
   - **稳定性判断**：对于每个子段，需要检查其中所有可能的三个元素是否满足三角形不等式。
   - **分割策略**：需要找到至少两种不同的分割方式，使得每个子段都是稳定的。

3. **难点**：
   - **高效判断稳定性**：直接枚举所有可能的三个元素组合会非常耗时，需要优化判断方法。
   - **多种分割方式**：需要找到至少两种不同的分割方式，这可能需要遍历所有可能的分割组合。

4. **优化建议**：
   - **排序**：对数组进行排序后，可以更容易地判断子段是否稳定。
   - **动态规划**：可以使用动态规划来记录子段的稳定性，避免重复计算。

### 推荐题目

1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115) - 考察子段分割与优化。
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886) - 涉及子段处理与滑动窗口技巧。
3. [P1045 数字三角形](https://www.luogu.com.cn/problem/P1045) - 与三角形相关的动态规划问题。

### 通用建议

- **调试与优化**：在实现过程中，注意边界条件的处理，特别是当子段长度为1或2时的情况。
- **思维拓展**：可以尝试将问题转化为图论问题，利用图的性质来优化判断稳定性。

希望这些建议能帮助你更好地理解和解决这个问题。

---
处理用时：52.43秒