# 题目信息

# Farmer John's Challenge

## 题目描述

[Trade Winds - Patrick Deng](https://soundcloud.com/patrick-deng-392681004/trade-winds-ft-alex-zhu)

⠀



Let's call an array $ a $ sorted if $ a_1 \leq a_2 \leq \ldots \leq a_{n - 1} \leq a_{n} $ .

You are given two of Farmer John's favorite integers, $ n $ and $ k $ . He challenges you to find any array $ a_1, a_2, \ldots, a_{n} $ satisfying the following requirements:

- $ 1 \leq a_i \leq 10^9 $ for each $ 1 \leq i \leq n $ ;
- Out of the $ n $ total cyclic shifts of $ a $ , exactly $ k $ of them are sorted. $ ^\dagger $

If there is no such array $ a $ , output $ -1 $ .

 $ ^\dagger $ The $ x $ -th ( $ 1 \leq x \leq n $ ) cyclic shift of the array $ a $ is $ a_x, a_{x+1} \ldots a_n, a_1, a_2 \ldots a_{x - 1} $ . If $ c_{x, i} $ denotes the $ i $ 'th element of the $ x $ 'th cyclic shift of $ a $ , exactly $ k $ such $ x $ should satisfy $ c_{x,1} \leq c_{x,2} \leq \ldots \leq c_{x, n - 1} \leq c_{x, n} $ .

For example, the cyclic shifts for $ a = [1, 2, 3, 3] $ are the following:

- $ x = 1 $ : $ [1, 2, 3, 3] $ (sorted);
- $ x = 2 $ : $ [2, 3, 3, 1] $ (not sorted);
- $ x = 3 $ : $ [3, 3, 1, 2] $ (not sorted);
- $ x = 4 $ : $ [3, 1, 2, 3] $ (not sorted).

## 说明/提示

In the first testcase, $ a = [1, 1] $ satisfies $ n = 2, k = 2 $ :

The two cyclic shifts of $ a $ are $ [a_1, a_2] $ and $ [a_2, a_1] $ , which are both $ [1, 1] $ and are sorted.

In the second testcase, $ a = [69\,420, 69, 420] $ satisfies $ n = 3, k = 1 $ :

The three cyclic shifts of $ a $ are $ [a_1, a_2, a_3] $ , $ [a_2, a_3, a_1] $ , $ [a_3, a_1, a_2] $ , which are $ [69\,420, 69, 420] $ , $ [69, 420, 69\,420] $ , and $ [420, 69\,420, 69] $ , respectively.

Only $ [69, 420, 69\,420] $ is sorted.

## 样例 #1

### 输入

```
3
2 2
3 1
3 2```

### 输出

```
1 1
69420 69 420
-1```

# AI分析结果

### 题目内容重写（中文）

**题目描述：**

我们称一个数组 $a$ 为有序的，如果满足 $a_1 \leq a_2 \leq \ldots \leq a_{n - 1} \leq a_{n}$。

给定农夫约翰最喜欢的两个整数 $n$ 和 $k$，他向你发起挑战，要求你找到任意一个数组 $a_1, a_2, \ldots, a_n$，满足以下要求：

- 对于每个 $1 \leq i \leq n$，$1 \leq a_i \leq 10^9$；
- 在数组 $a$ 的所有 $n$ 个循环移位中，恰好有 $k$ 个是有序的。$^\dagger$

如果不存在这样的数组 $a$，输出 $-1$。

$^\dagger$ 数组 $a$ 的第 $x$ 个（$1 \leq x \leq n$）循环移位是指 $a_x, a_{x+1} \ldots a_n, a_1, a_2 \ldots a_{x - 1}$。如果 $c_{x, i}$ 表示数组 $a$ 的第 $x$ 个循环移位的第 $i$ 个元素，那么恰好有 $k$ 个这样的 $x$ 满足 $c_{x,1} \leq c_{x,2} \leq \ldots \leq c_{x, n - 1} \leq c_{x, n}$。

例如，数组 $a = [1, 2, 3, 3]$ 的循环移位如下：

- $x = 1$ : $[1, 2, 3, 3]$（有序）；
- $x = 2$ : $[2, 3, 3, 1]$（无序）；
- $x = 3$ : $[3, 3, 1, 2]$（无序）；
- $x = 4$ : $[3, 1, 2, 3]$（无序）。

**说明/提示：**

在第一个测试用例中，$a = [1, 1]$ 满足 $n = 2, k = 2$：

数组 $a$ 的两个循环移位分别是 $[a_1, a_2]$ 和 $[a_2, a_1]$，它们都是 $[1, 1]$ 且有序。

在第二个测试用例中，$a = [69\,420, 69, 420]$ 满足 $n = 3, k = 1$：

数组 $a$ 的三个循环移位分别是 $[a_1, a_2, a_3]$、$[a_2, a_3, a_1]$、$[a_3, a_1, a_2]$，它们分别是 $[69\,420, 69, 420]$、$[69, 420, 69\,420]$、$[420, 69\,420, 69]$，其中只有 $[69, 420, 69\,420]$ 是有序的。

### 题解分析与结论

#### 综合分析
本题的核心在于理解循环移位的性质以及如何构造满足条件的数组。所有题解都提到了以下三种情况：
1. **$k=1$**：输出一个严格递增的数组，如 $1, 2, \ldots, n$。
2. **$k=n$**：输出一个所有元素相同的数组，如 $1, 1, \ldots, 1$。
3. **其他情况**：无解，输出 $-1$。

这些题解的思路基本一致，都是通过分析循环移位的性质得出结论。难点在于理解为什么只有这三种情况是可能的，以及如何通过简单的构造来满足条件。

#### 最优关键思路
- **循环移位的性质**：如果数组中有不同的元素，那么只有初始的数组可能是有序的，其他循环移位后都会破坏有序性。如果所有元素相同，那么所有循环移位都是有序的。
- **构造方法**：根据 $k$ 的值，选择输出递增数组或全等数组，其他情况无解。

#### 可拓展之处
- **类似问题**：可以拓展到其他需要构造特定性质的数组的问题，如构造满足特定排列或组合条件的数组。
- **算法优化**：本题的解法已经是 $O(n)$ 的时间复杂度，无法进一步优化。

#### 推荐题目
1. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
2. [P1068 分数线划定](https://www.luogu.com.cn/problem/P1068)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

### 精选题解

#### 题解1：作者：luobotianle (赞：3)
**星级：4星**
**关键亮点**：思路清晰，代码简洁，直接根据 $k$ 的值输出相应的数组。
**代码核心思想**：
```cpp
if(k==1)for(int i=1;i<=n;i++)cout<<i<<" ";
else if(k==n)for(int i=1;i<=n;i++)cout<<"1 ";
else cout<<"-1";
```

#### 题解2：作者：__Cyn__ (赞：2)
**星级：4星**
**关键亮点**：通过举例和分析，明确了三种情况的处理方法。
**代码核心思想**：
```cpp
if(k==1)for(int i=1;i<=n;i++)cout<<i<<" ";
else if(k==n)for(int i=1;i<=n;i++)cout<<"1 ";
else cout<<"-1";
```

#### 题解3：作者：JOE_ZengYuQiao_0928 (赞：2)
**星级：4星**
**关键亮点**：详细解释了为什么只有这三种情况是可能的，逻辑严谨。
**代码核心思想**：
```cpp
if(k==1)for(int i=1;i<=n;i++)cout<<i<<" ";
else if(k==n)for(int i=1;i<=n;i++)cout<<"1 ";
else cout<<"-1";
```

### 通用建议与扩展思路
如果所有题解都不足4星，建议读者自行分析循环移位的性质，理解为什么只有这三种情况是可能的，并通过简单的构造来满足条件。可以通过举例和打表来验证思路的正确性。

---
处理用时：50.19秒