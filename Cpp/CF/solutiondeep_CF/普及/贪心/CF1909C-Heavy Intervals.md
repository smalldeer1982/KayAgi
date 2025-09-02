# 题目信息

# Heavy Intervals

## 题目描述

[Shiki - Pure Ruby](https://soundcloud.com/shiki-8/pure-rubyversoundcloud)

⠀



You have $ n $ intervals $ [l_1, r_1], [l_2, r_2], \dots, [l_n, r_n] $ , such that $ l_i < r_i $ for each $ i $ , and all the endpoints of the intervals are distinct.

The $ i $ -th interval has weight $ c_i $ per unit length. Therefore, the weight of the $ i $ -th interval is $ c_i \cdot (r_i - l_i) $ .

You don't like large weights, so you want to make the sum of weights of the intervals as small as possible. It turns out you can perform all the following three operations:

- rearrange the elements in the array $ l $ in any order;
- rearrange the elements in the array $ r $ in any order;
- rearrange the elements in the array $ c $ in any order.

However, after performing all of the operations, the intervals must still be valid (i.e., for each $ i $ , $ l_i < r_i $ must hold).

What's the minimum possible sum of weights of the intervals after performing the operations?

## 说明/提示

In the first test case, you can make

- $ l = [8, 3] $ ;
- $ r = [23, 12] $ ;
- $ c = [100, 100] $ .

In that case, there are two intervals:

- interval $ [8, 23] $ with weight $ 100 $ per unit length, and $ 100 \cdot (23-8) = 1500 $ in total;
- interval $ [3, 12] $ with weight $ 100 $ per unit length, and $ 100 \cdot (12-3) = 900 $ in total.

The sum of the weights is $ 2400 $ . It can be shown that there is no configuration of final intervals whose sum of weights is less than $ 2400 $ .

In the second test case, you can make

- $ l = [1, 2, 5, 20] $ ;
- $ r = [3, 4, 10, 30] $ ;
- $ c = [3, 3, 2, 2] $ .

In that case, there are four intervals:

- interval $ [1, 3] $ with weight $ 3 $ per unit length, and $ 3 \cdot (3-1) = 6 $ in total;
- interval $ [2, 4] $ with weight $ 3 $ per unit length, and $ 3 \cdot (4-2) = 6 $ in total;
- interval $ [5, 10] $ with weight $ 2 $ per unit length, and $ 2 \cdot (10-5) = 10 $ in total;
- interval $ [20, 30] $ with weight $ 2 $ per unit length, and $ 2 \cdot (30-20) = 20 $ in total.

The sum of the weights is $ 42 $ . It can be shown that there is no configuration of final intervals whose sum of weights is less than $ 42 $ .

## 样例 #1

### 输入

```
2
2
8 3
12 23
100 100
4
20 1 2 5
30 4 3 10
2 3 2 3```

### 输出

```
2400
42```

# AI分析结果

### 题目内容重写（中文）

#### 题目描述

你有 $n$ 个区间 $[l_1, r_1], [l_2, r_2], \dots, [l_n, r_n]$，其中每个区间满足 $l_i < r_i$，且所有区间的端点都是唯一的。

第 $i$ 个区间的单位长度权重为 $c_i$。因此，第 $i$ 个区间的总权重为 $c_i \cdot (r_i - l_i)$。

你不喜欢大的权重，因此你希望使所有区间的权重之和尽可能小。你可以执行以下三种操作：

- 重新排列数组 $l$ 中的元素；
- 重新排列数组 $r$ 中的元素；
- 重新排列数组 $c$ 中的元素。

然而，在执行所有操作后，区间仍然必须是有效的（即对于每个 $i$，$l_i < r_i$ 必须成立）。

在执行操作后，区间权重之和的最小可能值是多少？

#### 说明/提示

在第一个测试用例中，你可以将：

- $l = [8, 3]$；
- $r = [23, 12]$；
- $c = [100, 100]$。

在这种情况下，有两个区间：

- 区间 $[8, 23]$，单位长度权重为 $100$，总权重为 $100 \cdot (23-8) = 1500$；
- 区间 $[3, 12]$，单位长度权重为 $100$，总权重为 $100 \cdot (12-3) = 900$。

权重之和为 $2400$。可以证明，没有其他配置可以使权重之和小于 $2400$。

在第二个测试用例中，你可以将：

- $l = [1, 2, 5, 20]$；
- $r = [3, 4, 10, 30]$；
- $c = [3, 3, 2, 2]$。

在这种情况下，有四个区间：

- 区间 $[1, 3]$，单位长度权重为 $3$，总权重为 $3 \cdot (3-1) = 6$；
- 区间 $[2, 4]$，单位长度权重为 $3$，总权重为 $3 \cdot (4-2) = 6$；
- 区间 $[5, 10]$，单位长度权重为 $2$，总权重为 $2 \cdot (10-5) = 10$；
- 区间 $[20, 30]$，单位长度权重为 $2$，总权重为 $2 \cdot (30-20) = 20$。

权重之和为 $42$。可以证明，没有其他配置可以使权重之和小于 $42$。

#### 样例 #1

##### 输入

```
2
2
8 3
12 23
100 100
4
20 1 2 5
30 4 3 10
2 3 2 3
```

##### 输出

```
2400
42
```

---

### 题解分析与结论

#### 综合分析

该题的核心思想是通过贪心算法，使得区间长度 $r_i - l_i$ 尽可能小，并且将这些小的区间长度与较大的权重 $c_i$ 匹配，从而最小化总权重。大多数题解都采用了类似的思路，即先对 $l$ 和 $r$ 进行排序，然后通过栈或平衡树等数据结构来匹配最小的 $r_i - l_i$，最后将 $r_i - l_i$ 与 $c_i$ 进行匹配。

#### 最优关键思路

1. **贪心匹配**：将最小的 $r_i - l_i$ 与最大的 $c_i$ 匹配，从而最小化总权重。
2. **排序与栈**：对 $l$ 和 $r$ 进行排序，使用栈来匹配每个 $r_i$ 与比它小的最大 $l_i$，从而得到最小的 $r_i - l_i$。
3. **平衡树优化**：使用平衡树（如 `pb_ds` 中的 `tree`）来高效地找到比 $r_i$ 小的最大 $l_i$，进一步优化匹配过程。

#### 推荐题解

1. **作者：Sikiru (赞：5)**  
   - **星级：4.5**  
   - **关键亮点**：使用栈来匹配 $l$ 和 $r$，思路清晰，代码简洁，易于理解。
   - **核心代码**：
     ```cpp
     sort(l, l + n);
     sort(r, r + n);
     stack<int> s;
     for (int i = 0; i < n; ++i) {
         while (l[p] < r[i] && p < n) {
             s.push(l[p]);
             ++p;
         }
         diff[i] = r[i] - s.top();
         s.pop();
     }
     ```

2. **作者：Withershine (赞：2)**  
   - **星级：4**  
   - **关键亮点**：使用平衡树来优化匹配过程，虽然代码复杂，但效率较高。
   - **核心代码**：
     ```cpp
     tree<ll , null_type , std::less<ll> , rb_tree_tag , tree_order_statistics_node_update> L , R;
     tree<pair<ll , ll> , null_type , std::less<pair<ll , ll>> , rb_tree_tag , tree_order_statistics_node_update> RL;
     ```

3. **作者：zcxnb (赞：1)**  
   - **星级：4**  
   - **关键亮点**：使用栈和排序，思路清晰，代码简洁，易于实现。
   - **核心代码**：
     ```cpp
     for (int i = 1, j = 1; i <= n; i++) {
         while (l[j] < r[i] && j <= n) {
             s[++cnt] = l[j];
             j++;
         }
         ans[i] = r[i] - s[cnt--];
     }
     ```

#### 个人心得

- **调试经历**：部分题解提到使用 `vector` 时遇到性能问题，改用并查集或平衡树后解决了问题。
- **顿悟感想**：贪心算法的关键在于如何合理地匹配元素，排序和栈的结合是解决此类问题的有效方法。

#### 推荐题目

1. **P1880 [NOI1995] 石子合并**（贪心、区间DP）
2. **P1090 [NOIP2004 提高组] 合并果子**（贪心、优先队列）
3. **P1048 [NOIP2005 普及组] 采药**（背包问题、贪心）

---
处理用时：47.02秒