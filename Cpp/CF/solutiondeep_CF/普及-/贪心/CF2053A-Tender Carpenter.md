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



### 中文重写题目
# 温柔的伐木工

## 题目描述

我将用烟花宣告，用浪花告别，用鞠躬致谢：往事如烟，未来的路我将悠然自得地前行，脚步永不停歇，因为明年我们还会再见。

—— Cocoly1990，《再见2022》

在梦中，Cocoly将开启无忧无虑的长假。他尝试了许多新事物，比如...成为一名木匠。为了学好手艺，Cocoly决定拜师学艺，但面前摆着一个难题等待解决。

给定数组 $a_1, a_2,\ldots, a_n$。称一个整数集合 $S$ 是稳定的，当且仅当对于集合中的任意三个元素 $u, v, w$（允许重复），长度分别为 $u, v, w$ 的木棍能构成非退化三角形。

请帮助Cocoly判断能否将数组分割为若干连续非空子段，使得每个子段的元素集合稳定，并且至少存在两种不同的分割方式。

## 输入格式

输入包含多组测试数据。每组数据第一行为整数 $n$，表示数组长度。第二行为数组元素。

## 输出格式

每组数据输出一行，若存在至少两种不同分割方式则输出 "YES"，否则输出 "NO"。

## 样例解释

样例1中，存在两种分法，例如将数组分为 [2,3] 和 [5,7]，或分为 [2]、[3,5]、[7]。样例2中所有元素只能单独成段，仅一种分法。

---

### 关键思路与算法分析

#### 稳定集合的充要条件
- **单元素集合**：必然稳定
- **双元素集合**：较大元素严格小于较小元素的2倍
- **多元素集合**：必须满足所有元素相同

#### 滑动窗口预处理
1. 维护当前窗口的最大值、最小值及元素种类
2. 当窗口内元素种类超过2，或双元素不满足倍数条件时，收缩左边界

#### 动态规划计数
- `dp[i]` 表示前i个元素的分割方式数
- 前缀和优化转移方程，快速计算区间和

### 代码实现要点
```python
from collections import defaultdict

n = int(input())
a = list(map(int, input().split()))

# 预处理每个右端点的最左边界
l = [0] * n
freq = defaultdict(int)
cnt = 0
left = 0
for right in range(n):
    x = a[right]
    if freq[x] == 0:
        cnt += 1
    freq[x] += 1
    
    while True:
        keys = sorted(freq)
        need_shrink = False
        if cnt > 2:
            need_shrink = True
        elif cnt == 2:
            min_k, max_k = keys[0], keys[-1]
            if max_k >= 2 * min_k:
                need_shrink = True
        
        if not need_shrink:
            break
        
        y = a[left]
        freq[y] -= 1
        if freq[y] == 0:
            cnt -= 1
            del freq[y]
        left += 1
    
    l[right] = left

# 动态规划计算分割方案数
dp = [0] * (n + 1)
dp[0] = 1
pre = [0] * (n + 2)
pre[1] = 1

for i in range(1, n + 1):
    r = i - 1
    if r < 0:
        continue
    current_left = l[r]
    start = current_left - 1
    end = r
    if start < 0:
        start = 0
    if start > end:
        dp[i] = 0
    else:
        dp[i] = pre[end + 1] - pre[start]
    
    if dp[i] >= 2 and i == n:
        print("YES")
        exit()
    pre[i + 1] = pre[i] + dp[i]

print("NO")
```

### 举一反三
1. **类似滑动窗口条件判断**：CF1009D（区间约束条件）
2. **动态规划分割计数**：LeetCode 139（单词拆分）
3. **集合性质分析**：洛谷P1969（积木覆盖问题）

### 总结
本题巧妙地将数学性质与滑动窗口结合，通过动态规划快速计数。核心在于发现稳定集合的充要条件，并设计线性预处理方法。该思路适用于需要快速判断子区间性质并统计方案数的场景。

---
处理用时：465.24秒