# 题目信息

# Sequence Master

## 题目描述

For some positive integer $ m $ , YunQian considers an array $ q $ of $ 2m $ (possibly negative) integers good, if and only if for every possible subsequence of $ q $ that has length $ m $ , the product of the $ m $ elements in the subsequence is equal to the sum of the $ m $ elements that are not in the subsequence. Formally, let $ U=\{1,2,\ldots,2m\} $ . For all sets $ S \subseteq U $ such that $ |S|=m $ , $ \prod\limits_{i \in S} q_i = \sum\limits_{i \in U \setminus S} q_i $ .

Define the distance between two arrays $ a $ and $ b $ both of length $ k $ to be $ \sum\limits_{i=1}^k|a_i-b_i| $ .

You are given a positive integer $ n $ and an array $ p $ of $ 2n $ integers.

Find the minimum distance between $ p $ and $ q $ over all good arrays $ q $ of length $ 2n $ . It can be shown for all positive integers $ n $ , at least one good array exists. Note that you are not required to construct the array $ q $ that achieves this minimum distance.

## 说明/提示

In the first test case, it is optimal to let $ q=[6,6] $ .

In the second test case, it is optimal to let $ q=[2,2,2,2] $ .

## 样例 #1

### 输入

```
4
1
6 9
2
1 2 2 1
2
-2 -2 2 2
4
-3 -2 -1 0 1 2 3 4```

### 输出

```
3
2
5
13```

# AI分析结果

### 题目内容重写（中文）

#### 题目描述

对于某个正整数 $m$，YunQian 认为一个长度为 $2m$ 的数组 $q$（元素可能为负数）是“好”的，当且仅当对于 $q$ 的每一个长度为 $m$ 的子序列，子序列中 $m$ 个元素的乘积等于不在该子序列中的 $m$ 个元素的和。形式化地，设 $U=\{1,2,\ldots,2m\}$，对于所有满足 $|S|=m$ 的集合 $S \subseteq U$，有 $\prod\limits_{i \in S} q_i = \sum\limits_{i \in U \setminus S} q_i$。

定义两个长度为 $k$ 的数组 $a$ 和 $b$ 的距离为 $\sum\limits_{i=1}^k|a_i-b_i|$。

给定一个正整数 $n$ 和一个长度为 $2n$ 的整数数组 $p$，请找到所有长度为 $2n$ 的“好”数组 $q$ 中与 $p$ 的最小距离。可以证明对于所有正整数 $n$，至少存在一个“好”数组。注意，你不需要构造出达到最小距离的数组 $q$。

#### 说明/提示

在第一个测试用例中，最优解是 $q=[6,6]$。

在第二个测试用例中，最优解是 $q=[2,2,2,2]$。

#### 样例 #1

##### 输入

```
4
1
6 9
2
1 2 2 1
2
-2 -2 2 2
4
-3 -2 -1 0 1 2 3 4
```

##### 输出

```
3
2
5
13
```

### 算法分类
**构造**

### 题解分析与结论

本题的核心是通过构造满足特定条件的“好”数组，并计算其与给定数组的最小距离。题解中主要讨论了“好”数组的构造方式，并在此基础上计算最小距离。以下是各题解的分析与对比：

1. **六楼溜刘的题解**：
   - **思路**：通过数学推导，证明了“好”数组的构造方式，并讨论了不同情况下的最小距离计算。
   - **亮点**：详细证明了“好”数组的构造条件，特别是对于 $n$ 为偶数时，构造了 $2n-1$ 个 $-1$ 和一个 $n$ 的数组。
   - **评分**：4星
   - **关键代码**：
     ```cpp
     forup(i,1,n<<1){
         ans=min(ans,s2-abs(a[i]+1)+abs(a[i]-n));
     }
     ```
     **核心思想**：通过枚举每个元素，计算将其替换为 $n$ 后的距离，取最小值。

2. **Xy_top的题解**：
   - **思路**：通过枚举和排序，找到最优的“好”数组，并计算最小距离。
   - **亮点**：通过排序和枚举，简化了计算过程，特别是在 $n$ 为偶数时，构造了 $2n-1$ 个 $-1$ 和一个 $n$ 的数组。
   - **评分**：4星
   - **关键代码**：
     ```cpp
     for (int i = 1; i <= 2 * n - 1; i ++) tmp += abs (a[i] + 1);
     cout << min (ans, tmp + abs (a[2 * n] - n) ) << "\n";
     ```
     **核心思想**：通过排序后计算替换后的距离，取最小值。

3. **Citnaris的题解**：
   - **思路**：通过数学推导和构造，讨论了“好”数组的构造方式，并计算最小距离。
   - **亮点**：详细讨论了不同情况下的“好”数组构造，特别是对于 $n$ 为偶数时，构造了 $2n-1$ 个 $-1$ 和一个 $n$ 的数组。
   - **评分**：4星
   - **关键代码**：
     ```cpp
     for (int i = 1; i <= m; ++i) {
         int tmpp = tmp - abs(a[i] + 1) + abs(a[i] - n);
         ans = min(ans, tmpp);
     }
     ```
     **核心思想**：通过枚举每个元素，计算将其替换为 $n$ 后的距离，取最小值。

### 最优关键思路或技巧
1. **构造“好”数组**：通过数学推导，发现“好”数组的构造方式，特别是对于 $n$ 为偶数时，构造 $2n-1$ 个 $-1$ 和一个 $n$ 的数组。
2. **最小距离计算**：通过枚举每个元素，计算将其替换为 $n$ 后的距离，取最小值。

### 可拓展之处
1. **类似构造问题**：可以拓展到其他需要构造满足特定条件的数组或序列的问题，如构造满足特定和的数组。
2. **距离计算优化**：可以进一步优化距离计算的过程，减少枚举的次数。

### 推荐题目
1. [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)
2. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

### 个人心得摘录
- **六楼溜刘**：通过数学推导，发现“好”数组的构造方式，特别是对于 $n$ 为偶数时，构造 $2n-1$ 个 $-1$ 和一个 $n$ 的数组。
- **Xy_top**：通过排序和枚举，简化了计算过程，特别是在 $n$ 为偶数时，构造了 $2n-1$ 个 $-1$ 和一个 $n$ 的数组。
- **Citnaris**：详细讨论了不同情况下的“好”数组构造，特别是对于 $n$ 为偶数时，构造了 $2n-1$ 个 $-1$ 和一个 $n$ 的数组。

---
处理用时：50.41秒