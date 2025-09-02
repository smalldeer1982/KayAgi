# 题目信息

# Very Different Array

## 题目描述

Petya has an array $ a_i $ of $ n $ integers. His brother Vasya became envious and decided to make his own array of $ n $ integers.

To do this, he found $ m $ integers $ b_i $ ( $ m\ge n $ ), and now he wants to choose some $ n $ integers of them and arrange them in a certain order to obtain an array $ c_i $ of length $ n $ .

To avoid being similar to his brother, Vasya wants to make his array as different as possible from Petya's array. Specifically, he wants the total difference $ D = \sum_{i=1}^{n} |a_i - c_i| $ to be as large as possible.

Help Vasya find the maximum difference $ D $ he can obtain.

## 说明/提示

In the first example, Vasya can, for example, create the array $ (1, 5, 7, 2) $ . Then the total difference will be $ D = |6-1|+|1-5|+|2-7|+|4-2| = 5+4+5+2 = 16 $ .

In the second example, all the integers available to Vasya are equal to 1, so he can only create the array $ (1, 1, 1) $ , for which the difference $ D = 0 $ .

In the third example, Vasya can, for example, create the array $ (5, 4, 3, 2, 1) $ . Then the total difference will be $ D = |1-5|+|2-4|+|3-3|+|4-2|+|5-1| = 4+2+0+2+4 = 12 $ .

## 样例 #1

### 输入

```
9
4 6
6 1 2 4
3 5 1 7 2 3
3 4
1 1 1
1 1 1 1
5 5
1 2 3 4 5
1 2 3 4 5
2 6
5 8
8 7 5 8 2 10
2 2
4 1
9 6
4 6
8 10 6 4
3 10 6 1 8 9
3 5
6 5 2
1 7 9 7 2
5 5
9 10 6 3 7
5 9 2 3 9
1 6
3
2 7 10 1 1 5```

### 输出

```
16
0
12
11
10
23
15
25
7```

# AI分析结果



### 题目内容重写

# 差异最大的数组

## 题目描述

Petya 有一个长度为 $n$ 的整数数组 $a_i$。他的兄弟 Vasya 决定用 $m$ 个整数 $b_i$（$m \ge n$）中选出 $n$ 个整数，组成一个新数组 $c_i$，使得总差异 $D = \sum_{i=1}^{n} |a_i - c_i|$ 尽可能大。请帮助 Vasya 计算最大可能的 $D$。

## 样例

### 输入样例
```
9
4 6
6 1 2 4
3 5 1 7 2 3
3 4
1 1 1
1 1 1 1
5 5
1 2 3 4 5
1 2 3 4 5
...
```

### 输出样例
```
16
0
12
...
```

---

### 综合题解分析

#### 核心思路
所有题解均采用贪心策略，核心思想为：
1. **排序优化**：将 $a$ 和 $b$ 数组分别升序排序。
2. **极值配对**：对每个 $a_i$，选择 $b$ 中最大的或最小的未被选用的元素进行配对，使得每对元素的绝对差最大化。

#### 解决难点
- **贪心策略证明**：需确保每个 $a_i$ 的最优选择仅可能来自两个极端位置（$b$ 的前端最大或后端最小），避免全局最优被局部选择破坏。
- **时间复杂度控制**：需在 $O(n \log n + m \log m)$ 时间内完成排序和计算。

#### 最优解法总结
通过排序后对每个 $a_i$ 选择 $b$ 的两个可能极端位置（$b_{n-i+1}$ 或 $b_{m-i+1}$）中的最大值，累加所有绝对差。

---

### 精选题解

#### 1. 作者：foryou_（★★★★★）
- **关键亮点**：严谨的贪心策略数学证明，清晰解释了每个 $a_i$ 选择极值的必然性。
- **代码简析**：
  ```cpp
  sort(a, a + n);
  sort(b, b + m);
  long long ans = 0;
  for (int i = 0; i < n; i++) {
      ans += max(abs(a[i] - b[n - i - 1]), abs(a[i] - b[m - i - 1]));
  }
  ```

#### 2. 作者：Pump_kin（★★★★★）
- **关键亮点**：代码简洁高效，直接实现贪心策略。
- **核心代码**：
  ```cpp
  sort(a + 1, a + n + 1);
  sort(b + 1, b + m + 1);
  for (int i = 1; i <= n; i++) {
      ans += max(abs(a[i] - b[n - i + 1]), abs(a[i] - b[m - i + 1]));
  }
  ```

#### 3. 作者：FlyPancake（★★★★☆）
- **关键亮点**：代码结构清晰，强调开 long long 的细节。
- **代码片段**：
  ```cpp
  sort(a, a + n);
  sort(b, b + m);
  ll ans = 0;
  for (int i = 0; i < n; i++) {
      ans += max(abs(a[i] - b[n - i - 1]), abs(a[i] - b[m - i - 1]));
  }
  ```

---

### 关键思路与技巧
1. **排序与双指针**：排序后利用双指针快速定位极值。
2. **贪心选择**：每个元素独立选择最大可能的差值，保证全局最优。
3. **数学证明**：排序后的对称性使得极值配对最优。

---

### 类似题目推荐
1. **CF1005D**：通过贪心选择最小操作次数。
2. **洛谷P1090**：合并果子问题，贪心选择最小堆。
3. **LeetCode 561**：数组拆分使数对最小值之和最大，排序后取偶数位。

---
处理用时：173.22秒