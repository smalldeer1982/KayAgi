# 题目信息

# 2^Sort

## 题目描述

Given an array $ a $ of length $ n $ and an integer $ k $ , find the number of indices $ 1 \leq i \leq n - k $ such that the subarray $ [a_i, \dots, a_{i+k}] $ with length $ k+1 $ (not with length $ k $ ) has the following property:

- If you multiply the first element by $ 2^0 $ , the second element by $ 2^1 $ , ..., and the ( $ k+1 $ )-st element by $ 2^k $ , then this subarray is sorted in strictly increasing order.

 More formally, count the number of indices $ 1 \leq i \leq n - k $ such that $ $$$2^0 \cdot a_i < 2^1 \cdot a_{i+1} < 2^2 \cdot a_{i+2} < \dots < 2^k \cdot a_{i+k}. $ $$$

## 说明/提示

In the first test case, both subarrays satisfy the condition:

- $ i=1 $ : the subarray $ [a_1,a_2,a_3] = [20,22,19] $ , and $ 1 \cdot 20 < 2 \cdot 22 < 4 \cdot 19 $ .
- $ i=2 $ : the subarray $ [a_2,a_3,a_4] = [22,19,84] $ , and $ 1 \cdot 22 < 2 \cdot 19 < 4 \cdot 84 $ .

 In the second test case, three subarrays satisfy the condition: - $ i=1 $ : the subarray $ [a_1,a_2] = [9,5] $ , and $ 1 \cdot 9 < 2 \cdot 5 $ .
- $ i=2 $ : the subarray $ [a_2,a_3] = [5,3] $ , and $ 1 \cdot 5 < 2 \cdot 3 $ .
- $ i=3 $ : the subarray $ [a_3,a_4] = [3,2] $ , and $ 1 \cdot 3 < 2 \cdot 2 $ .
- $ i=4 $ : the subarray $ [a_4,a_5] = [2,1] $ , but $ 1 \cdot 2 = 2 \cdot 1 $ , so this subarray doesn't satisfy the condition.

## 样例 #1

### 输入

```
6
4 2
20 22 19 84
5 1
9 5 3 2 1
5 2
9 5 3 2 1
7 2
22 12 16 4 3 22 12
7 3
22 12 16 4 3 22 12
9 3
3 9 12 3 9 12 3 9 12```

### 输出

```
2
3
2
3
1
0```

# AI分析结果

### 题目内容
# 2^Sort

## 题目描述
给定一个长度为 $n$ 的数组 $a$ 以及一个整数 $k$ ，找出满足 $1 \leq i \leq n - k$ 的索引 $i$ 的数量，使得长度为 $k + 1$（并非长度为 $k$）的子数组 $[a_i, \dots, a_{i + k}]$ 具有以下性质：
- 如果你将第一个元素乘以 $2^0$ ，第二个元素乘以 $2^1$ ，……，第 $(k + 1)$ 个元素乘以 $2^k$ ，那么这个子数组是严格递增排序的。
更正式地说，计算满足 $1 \leq i \leq n - k$ 的索引 $i$ 的数量，使得 $2^0 \cdot a_i < 2^1 \cdot a_{i + 1} < 2^2 \cdot a_{i + 2} < \dots < 2^k \cdot a_{i + k}$ 。

## 说明/提示
在第一个测试用例中，两个子数组都满足条件：
- $i = 1$ ：子数组 $[a_1, a_2, a_3] = [20, 22, 19]$ ，且 $1 \cdot 20 < 2 \cdot 22 < 4 \cdot 19$ 。
- $i = 2$ ：子数组 $[a_2, a_3, a_4] = [22, 19, 84]$ ，且 $1 \cdot 22 < 2 \cdot 19 < 4 \cdot 84$ 。

在第二个测试用例中，三个子数组满足条件：
- $i = 1$ ：子数组 $[a_1, a_2] = [9, 5]$ ，且 $1 \cdot 9 < 2 \cdot 5$ 。
- $i = 2$ ：子数组 $[a_2, a_3] = [5, 3]$ ，且 $1 \cdot 5 < 2 \cdot 3$ 。
- $i = 3$ ：子数组 $[a_3, a_4] = [3, 2]$ ，且 $1 \cdot 3 < 2 \cdot 2$ 。
- $i = 4$ ：子数组 $[a_4, a_5] = [2, 1]$ ，但 $1 \cdot 2 = 2 \cdot 1$ ，所以这个子数组不满足条件。

## 样例 #1
### 输入
```
6
4 2
20 22 19 84
5 1
9 5 3 2 1
5 2
9 5 3 2 1
7 2
22 12 16 4 3 22 12
7 3
22 12 16 4 3 22 12
9 3
3 9 12 3 9 12 3 9 12
```

### 输出
```
2
3
2
3
1
0
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是将原不等式 $2^0 \cdot a_i < 2^1 \cdot a_{i + 1} < 2^2 \cdot a_{i + 2} < \dots < 2^k \cdot a_{i + k}$ 转化为 $a_i < 2 \cdot a_{i + 1}$ ，然后通过不同方式统计满足条件的区间数量。
- **思路方面**：多数题解通过遍历数组判断相邻元素关系，确定满足条件的区间。如Hovery、Withers、cyrxdzj、hanzhang666、Shunpower等题解通过维护满足条件的区间长度，根据长度与 $k$ 的关系计算贡献；Otue、tzyt、duchengjun则通过记录相邻元素关系到数组，再用不同方法统计符合条件的区间。
- **算法要点**：关键在于高效判断和统计满足 $a_i < 2 \cdot a_{i + 1}$ 的区间。不同题解采用了不同的数据处理方式，如直接遍历判断、用数组记录关系后处理等。
- **解决难点**：难点在于发现不等式的等价转化，将原复杂条件简化为相邻元素的简单比较关系，从而降低问题复杂度。

### 所选的题解
- **作者：Hovery (5星)**
  - **关键亮点**：思路清晰，将问题转化为最长平台问题，通过预处理出满足条件的区间，根据区间长度与 $k$ 的关系分类讨论计算答案，代码简洁明了，优化程度高。
  - **重点代码核心实现思想**：遍历数组，当 $a[i] * 2 <= a[i - 1]$ 时，说明当前满足条件的区间结束，若区间长度大于等于 $k$ ，则计算其对答案的贡献，最后处理最后一段区间。
  ```cpp
  for (int i = 2;i <= n;i++)
  if (a[i] * 2 <= a[i - 1])
  {
      if (i - now >= k)
      {
          ans += i - now - k;
      }
      now = i;
  }
  if (n - now + 1 >= k && a[n] * 2 > a[n - 1])
  ans += n - now + 1 - k;
  ```
- **作者：Otue (4星)**
  - **关键亮点**：将不等式成立情况转化为 `bool` 数组，通过统计数组中连续为 $1$ 的方案数来求解，思路独特，代码实现简单直观。
  - **重点代码核心实现思想**：先遍历数组标记不等式不成立的位置，然后遍历标记数组，统计连续为 $0$ 的长度，若长度大于等于 $k$ ，则计算其对答案的贡献。
  ```cpp
  for (int i = 1; i < n; i++) {
      if (a[i] >= a[i + 1] * 2) {
          b[i] = 1;
      }
  } 
  b[n] = 1;
  int res = 0, ans = 0;
  for (int i = 1; i <= n; i++) {
      if (b[i] == 0) res++;
      if (b[i] == 1) {
          if (res >= x) ans += res - x + 1;
          res = 0;
      }
  }
  ```
- **作者：tzyt (4星)**
  - **关键亮点**：通过前缀和数组统计满足条件的数对数量，利用前缀和在 $O(1)$ 时间内查询区间内满足条件的数对数量，从而高效统计符合条件的区间，思路巧妙。
  - **重点代码核心实现思想**：先遍历数组判断相邻元素是否满足条件并记录到 `valid` 数组，同时更新前缀和数组 `valid_sum` ，最后通过遍历前缀和数组判断长度为 $k$ 的区间内满足条件的数对数量是否为 $k$ ，若是则答案加一。
  ```cpp
  for(int i = 1; i < n; i++){
      if(a[i] < 2 * a[i + 1]){
          valid[i] = true;
      }
      valid_sum[i] = valid_sum[i - 1] + valid[i];
  }
  int ans = 0;
  for(int i = 1; i <= n - k; i++){
      if(valid_sum[i + k - 1] - valid_sum[i - 1] == k){
          ans++;
      }
  }
  ```

### 最优关键思路或技巧
发现原不等式可转化为相邻元素的简单比较关系 $a_i < 2 \cdot a_{i + 1}$ ，大大简化问题。不同题解采用了不同的数据结构和统计方式来优化计算满足条件区间的过程，如利用前缀和数组、维护区间长度等。

### 可拓展之处
同类型题通常会给出一些复杂的序列条件，通过数学变换简化条件，再利用数组、前缀和、滑动窗口等工具统计符合条件的子序列或子数组数量。类似算法套路是先对复杂条件进行化简，转化为更易处理的形式，再选择合适的数据结构和方法进行统计。

### 洛谷相似题目推荐
- [P1990 覆盖墙壁](https://www.luogu.com.cn/problem/P1990)：通过分析小问题间关系，利用递推求解方案数，与本题化简条件后统计方案数思路类似。
- [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)：通过数学推导将问题转化为更易求解的形式，和本题化简不等式思路相似。
- [P2241 统计方形（数据加强版）](https://www.luogu.com.cn/problem/P2241)：通过分析几何图形关系，利用数学方法统计满足条件的图形数量，与本题统计满足条件区间数量思路类似。

### 个人心得摘录与总结
tzyt提到该题想到关键转化点就简单，没想到就容易失败，强调了发现不等式等价转化这一关键思路的重要性。 

---
处理用时：60.23秒