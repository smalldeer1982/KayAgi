# 题目信息

# Paprika and Permutation

## 题目描述

Paprika loves permutations. She has an array $ a_1, a_2, \dots, a_n $ . She wants to make the array a permutation of integers $ 1 $ to $ n $ .

In order to achieve this goal, she can perform operations on the array. In each operation she can choose two integers $ i $ ( $ 1 \le i \le n $ ) and $ x $ ( $ x > 0 $ ), then perform $ a_i := a_i \bmod x $ (that is, replace $ a_i $ by the remainder of $ a_i $ divided by $ x $ ). In different operations, the chosen $ i $ and $ x $ can be different.

Determine the minimum number of operations needed to make the array a permutation of integers $ 1 $ to $ n $ . If it is impossible, output $ -1 $ .

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

For the first test, the only possible sequence of operations which minimizes the number of operations is:

- Choose $ i=2 $ , $ x=5 $ . Perform $ a_2 := a_2 \bmod 5 = 2 $ .

For the second test, it is impossible to obtain a permutation of integers from $ 1 $ to $ n $ .

## 样例 #1

### 输入

```
4
2
1 7
3
1 5 4
4
12345678 87654321 20211218 23571113
9
1 2 3 4 18 19 5 6 7```

### 输出

```
1
-1
4
2```

# AI分析结果

### 题目内容重写

#### 题目描述

Paprika 喜欢排列。她有一个数组 $a_1, a_2, \dots, a_n$。她希望通过操作使这个数组变成一个 $1$ 到 $n$ 的排列。

为了实现这个目标，她可以对数组进行操作。每次操作中，她可以选择两个整数 $i$（$1 \le i \le n$）和 $x$（$x > 0$），然后执行 $a_i := a_i \bmod x$（即将 $a_i$ 替换为 $a_i$ 除以 $x$ 的余数）。在不同的操作中，选择的 $i$ 和 $x$ 可以不同。

请确定使数组变成 $1$ 到 $n$ 的排列所需的最少操作次数。如果不可能，输出 $-1$。

一个排列是指一个由 $1$ 到 $n$ 的 $n$ 个不同整数组成的数组，顺序任意。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（$2$ 出现了两次），$[1,3,4]$ 也不是排列（$n=3$ 但数组中有 $4$）。

#### 说明/提示

对于第一个样例，唯一能最小化操作次数的操作序列是：

- 选择 $i=2$，$x=5$。执行 $a_2 := a_2 \bmod 5 = 2$。

对于第二个样例，无法得到一个 $1$ 到 $n$ 的排列。

#### 样例 #1

##### 输入

```
4
2
1 7
3
1 5 4
4
12345678 87654321 20211218 23571113
9
1 2 3 4 18 19 5 6 7
```

##### 输出

```
1
-1
4
2
```

### 题解分析与结论

#### 综合分析

1. **核心思路**：所有题解都基于一个共同的核心思想，即通过取模操作将数组中的元素变为 $1$ 到 $n$ 的排列。关键在于如何高效地匹配需要调整的元素和目标数。
2. **算法要点**：
   - **排序**：大多数题解都首先对数组进行排序，以便更容易地匹配元素和目标数。
   - **贪心策略**：通过贪心策略，优先处理较小的元素，确保它们能够被匹配到合适的位置。
   - **取模性质**：利用取模操作的性质，即 $a_i \bmod x$ 的结果必须小于 $x$，并且 $x$ 的选择决定了 $a_i$ 可以变为哪些数。
3. **解决难点**：
   - **重复元素处理**：多个题解提到需要处理数组中的重复元素，确保每个目标数只被匹配一次。
   - **无解判断**：当无法通过取模操作将元素匹配到目标数时，输出 $-1$。

#### 最优题解

1. **作者：RevolutionBP (4星)**
   - **关键亮点**：通过双指针扫描和排序，高效地匹配需要调整的元素和目标数。特别强调了重复元素的处理，确保每个目标数只被匹配一次。
   - **代码实现**：
     ```cpp
     vector<int> v;
     memset(vis,0,sizeof(vis));
     read(n);
     for(int i=1;i<=n;i++) read(a[i]);
     sort(a+1,a+1+n);
     int pos=1,ans=0;
     while(a[pos]<=n) vis[a[pos++]]=true;
     for(int i=1;i<pos;i++)
         if(a[i]==a[i-1]) v.push_back(a[i]);
     for(int i=pos;i<=n;i++) v.push_back(a[i]);
     int siz=v.size(); pos=0;
     for(int i=1;i<=n;i++){
         if(!vis[i]){
             if(i*2<v[pos] && pos<siz) ans++,pos++;
             else{
                 write(-1,'\n');
                 return;
             }
         }
     }
     write(ans,'\n');
     ```

2. **作者：lzy120406 (4星)**
   - **关键亮点**：使用贪心策略，将需要调整的元素和目标数分别排序，并一一匹配。通过判断 $extra_j > 2 \times target_i$ 来确保匹配的可行性。
   - **代码实现**：
     ```cpp
     vector<int> extra; // 需要调整的元素
     for (int i=0;i<n;i++) {
         if (a[i] >= 1 && a[i] <= n && !used[a[i]]) {
             used[a[i]] = true;
         } else {
             extra.push_back(a[i]);
         }
     }
     vector<int> target; // 未被使用的目标数
     for (int i = 1; i <= n; ++i) {
         if (!used[i]) {
             target.push_back(i);
         }
     }
     // 如果数量不匹配，无法调整
     if (extra.size() != target.size()) {
         return -1;
     }
     // 排序后贪心匹配
     sort(extra.begin(), extra.end());
     sort(target.begin(), target.end());
     for (int i = 0; i < (int)extra.size(); ++i) {
         if (extra[i] <= 2 * target[i]) {
             return -1;
         }
     }
     return extra.size();
     ```

3. **作者：postpone (4星)**
   - **关键亮点**：使用 `std::set` 存放目标排列，通过二分查找高效地匹配需要调整的元素和目标数。特别强调了先填小的数再填大的数的贪心策略。
   - **代码实现**：
     ```cpp
     for (auto i : a) {
         if (S.contains(i)) {
             S.erase(i);
             continue;
         }
         res++;
         int t = min(i / 2 - (i % 2 == 0), n);
         auto it = S.upper_bound(t);
         if (it == S.begin()) {
             break; // 说明这个数没地方填了，那么一定不行。
         }
         S.erase(--it);
     }
     ```

#### 最优关键思路

- **排序与贪心**：通过排序和贪心策略，优先处理较小的元素，确保它们能够被匹配到合适的位置。
- **取模性质**：利用取模操作的性质，确保每个元素能够变为目标数。
- **重复元素处理**：通过标记或删除重复元素，确保每个目标数只被匹配一次。

#### 拓展思路

- **类似问题**：类似的问题可以通过排序和贪心策略来解决，例如将数组中的元素通过某种操作变为目标序列。
- **数据结构**：使用 `std::set` 或其他数据结构可以高效地匹配元素和目标数。

#### 推荐题目

1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)

#### 个人心得

- **调试经历**：多个题解提到在处理重复元素时容易出错，需要特别注意。
- **踩坑教训**：在判断无解时，需要确保所有条件都满足，否则容易漏判。
- **顿悟感想**：通过排序和贪心策略，可以大大简化问题的复杂度，提高解题效率。

---
处理用时：55.19秒