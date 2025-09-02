# 题目信息

# Vasya and Arrays

## 题目描述

Vasya has two arrays $ A $ and $ B $ of lengths $ n $ and $ m $ , respectively.

He can perform the following operation arbitrary number of times (possibly zero): he takes some consecutive subsegment of the array and replaces it with a single element, equal to the sum of all elements on this subsegment. For example, from the array $ [1, 10, 100, 1000, 10000] $ Vasya can obtain array $ [1, 1110, 10000] $ , and from array $ [1, 2, 3] $ Vasya can obtain array $ [6] $ .

Two arrays $ A $ and $ B $ are considered equal if and only if they have the same length and for each valid $ i $ $ A_i = B_i $ .

Vasya wants to perform some of these operations on array $ A $ , some on array $ B $ , in such a way that arrays $ A $ and $ B $ become equal. Moreover, the lengths of the resulting arrays should be maximal possible.

Help Vasya to determine the maximum length of the arrays that he can achieve or output that it is impossible to make arrays $ A $ and $ B $ equal.

## 样例 #1

### 输入

```
5
11 2 3 5 7
4
11 7 3 7
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2
1 2
1
100
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3
1 2 3
3
1 2 3
```

### 输出

```
3
```

# AI分析结果

### 题目内容
Vasya有两个数组$A$和$B$，长度分别为$n$和$m$。他可以对这两个数组进行任意次数的操作：选择数组中的一个连续子段，并将其替换为这个子段中所有元素的和。例如，数组$[1, 10, 100, 1000, 10000]$可以通过操作变为$[1, 1110, 10000]$，数组$[1, 2, 3]$可以变为$[6]$。

两个数组$A$和$B$被认为是相等的，当且仅当它们的长度相同，并且对于每个有效的$i$，$A_i = B_i$。

Vasya希望对数组$A$和$B$进行一些操作，使得它们最终相等，并且最终数组的长度尽可能大。帮助Vasya确定可以达到的最大长度，或者输出无法使数组相等。

### 样例 #1
#### 输入
```
5
11 2 3 5 7
4
11 7 3 7
```
#### 输出
```
3
```

### 样例 #2
#### 输入
```
2
1 2
1
100
```
#### 输出
```
-1
```

### 样例 #3
#### 输入
```
3
1 2 3
3
1 2 3
```
#### 输出
```
3
```

### 算法分类
贪心

### 题解分析与结论
该题的核心思路是通过贪心算法，利用双指针或前缀和来匹配两个数组中的相等子段和。大多数题解都采用了双指针的方法，通过比较两个数组的前缀和来决定指针的移动方向，从而找到尽可能多的相等子段。

### 评分较高的题解
#### 1. 作者：SCAR_L (赞：4)
- **星级**：5
- **关键亮点**：使用尺取法（双指针）来匹配相等的前缀和，时间复杂度为$O(n)$，代码简洁高效。
- **核心代码**：
  ```cpp
  while(i <= n && j <= m) {
      if(a[i] == b[j]) ans++, i++, j++;
      else if(a[i] > b[j]) j++;
      else if(a[i] < b[j]) i++;
  }
  ```
- **个人心得**：通过前缀和优化，避免了暴力枚举，大大减少了时间复杂度。

#### 2. 作者：DPair (赞：2)
- **星级**：4
- **关键亮点**：使用$map$来记录前缀和，通过贪心策略找到相等的前缀和，时间复杂度为$O(n \log n)$。
- **核心代码**：
  ```cpp
  for (register int i = 1;i <= n;i ++) h[sa[i]] = 1;
  for (register int i = 1;i <= m;i ++) ans += h[sb[i]];
  ```
- **个人心得**：利用$map$的查找特性，简化了相等前缀和的匹配过程。

#### 3. 作者：lightningZ (赞：1)
- **星级**：4
- **关键亮点**：通过双指针和贪心策略，逐步匹配相等的前缀和，时间复杂度为$O(n)$。
- **核心代码**：
  ```cpp
  while(x <= n || y <= m) {
      if(sum1 > sum2) y++, sum2 += b[y];
      else if(sum1 < sum2) x++, sum1 += a[x];
      else ans++, x++, y++, sum1 = a[x], sum2 = b[y];
  }
  ```
- **个人心得**：通过逐步累加和比较，确保每次匹配的都是最小的相等子段。

### 最优关键思路与技巧
1. **双指针法**：通过两个指针分别遍历两个数组，比较当前前缀和的大小，决定指针的移动方向，从而找到相等的前缀和。
2. **前缀和优化**：通过计算数组的前缀和，可以快速比较两个数组的任意子段和，避免暴力枚举。
3. **贪心策略**：每次尽可能匹配最小的相等子段，确保最终的分段数最大。

### 可拓展之处
该题的思路可以拓展到其他需要匹配子段和的问题，例如在多个数组中寻找相等的子段和，或者在不同条件下匹配子段和。

### 推荐题目
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
3. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)

---
处理用时：32.95秒