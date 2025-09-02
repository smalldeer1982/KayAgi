# 题目信息

# Data Structures Fan

## 题目描述

You are given an array of integers $ a_1, a_2, \ldots, a_n $ , as well as a binary string $ ^{\dagger} $ $ s $ consisting of $ n $ characters.

Augustin is a big fan of data structures. Therefore, he asked you to implement a data structure that can answer $ q $ queries. There are two types of queries:

- "1 $ l $ $ r $ " ( $ 1\le l \le r \le n $ ) — replace each character $ s_i $ for $ l \le i \le r $ with its opposite. That is, replace all $ \texttt{0} $ with $ \texttt{1} $ and all $ \texttt{1} $ with $ \texttt{0} $ .
- "2 $ g $ " ( $ g \in \{0, 1\} $ ) — calculate the value of the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of the numbers $ a_i $ for all indices $ i $ such that $ s_i = g $ . Note that the $ \operatorname{XOR} $ of an empty set of numbers is considered to be equal to $ 0 $ .

Please help Augustin to answer all the queries!

For example, if $ n = 4 $ , $ a = [1, 2, 3, 6] $ , $ s = \texttt{1001} $ , consider the following series of queries:

1. "2 $ 0 $ " — we are interested in the indices $ i $ for which $ s_i = \tt{0} $ , since $ s = \tt{1001} $ , these are the indices $ 2 $ and $ 3 $ , so the answer to the query will be $ a_2 \oplus a_3 = 2 \oplus 3 = 1 $ .
2. "1 $ 1 $ $ 3 $ " — we need to replace the characters $ s_1, s_2, s_3 $ with their opposites, so before the query $ s = \tt{1001} $ , and after the query: $ s = \tt{0111} $ .
3. "2 $ 1 $ " — we are interested in the indices $ i $ for which $ s_i = \tt{1} $ , since $ s = \tt{0111} $ , these are the indices $ 2 $ , $ 3 $ , and $ 4 $ , so the answer to the query will be $ a_2 \oplus a_3 \oplus a_4 = 2 \oplus 3 \oplus 6 = 7 $ .
4. "1 $ 2 $ $ 4 $ " — $ s = \tt{0111} $ $ \to $ $ s = \tt{0000} $ .
5. "2 $ 1 $ " — $ s = \tt{0000} $ , there are no indices with $ s_i = \tt{1} $ , so since the $ \operatorname{XOR} $ of an empty set of numbers is considered to be equal to $ 0 $ , the answer to this query is $ 0 $ .

 $ ^{\dagger} $ A binary string is a string containing only characters $ \texttt{0} $ or $ \texttt{1} $ .

## 说明/提示

Let's analyze the first test case:

1. "2 $ 0 $ " — we are interested in the indices $ i $ for which $ s_i = \tt{0} $ , since $ s = \tt{01000} $ , these are the indices $ 1, 3, 4 $ , and $ 5 $ , so the answer to the query will be $ a_1 \oplus a_3 \oplus a_4 \oplus a_5 = 1 \oplus 3 \oplus 4 \oplus 5 = 3 $ .
2. "2 $ 1 $ " — we are interested in the indices $ i $ for which $ s_i = \tt{1} $ , since $ s = \tt{01000} $ , the only suitable index is $ 2 $ , so the answer to the query will be $ a_2 = 2 $ .
3. "1 $ 2 $ $ 4 $ " — we need to replace the characters $ s_2, s_3, s_4 $ with their opposites, so before the query $ s = \tt{01000} $ , and after the query: $ s = \tt{00110} $ .
4. "2 $ 0 $ " — we are interested in the indices $ i $ for which $ s_i = \tt{0} $ , since $ s = \tt{00110} $ , these are the indices $ 1, 2 $ , and $ 5 $ , so the answer to the query will be $ a_1 \oplus a_2 \oplus a_5 = 1 \oplus 2 \oplus 5 = 6 $ .
5. "2 $ 1 $ " — we are interested in the indices $ i $ for which $ s_i = \tt{1} $ , since $ s = \tt{00110} $ , these are the indices $ 3 $ and $ 4 $ , so the answer to the query will be $ a_3 \oplus a_4 = 3 \oplus 4 = 7 $ .
6. "1 $ 1 $ $ 3 $ " — $ s = \tt{00110} $ $ \to $ $ s = \tt{11010} $ .
7. "2 $ 1 $ " — we are interested in the indices $ i $ for which $ s_i = \tt{1} $ , since $ s = \tt{11010} $ , these are the indices $ 1, 2 $ , and $ 4 $ , so the answer to the query will be $ a_1 \oplus a_2 \oplus a_4 = 1 \oplus 2 \oplus 4 = 7 $ .

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
01000
7
2 0
2 1
1 2 4
2 0
2 1
1 1 3
2 1
6
12 12 14 14 5 5
001001
3
2 1
1 2 4
2 1
4
7 7 7 777
1111
3
2 0
1 2 3
2 0
2
1000000000 996179179
11
1
2 1
5
1 42 20 47 7
00011
5
1 3 4
1 1 1
1 3 4
1 2 4
2 0```

### 输出

```
3 2 6 7 7 
11 7 
0 0 
16430827 
47```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一个整数数组 $a_1, a_2, \ldots, a_n$ 和一个长度为 $n$ 的二进制字符串 $s$。

Augustin 是一个数据结构爱好者，因此他请你实现一个数据结构，能够回答 $q$ 个查询。查询有两种类型：

1. "1 $l$ $r$"（$1 \le l \le r \le n$）——将 $s$ 中从 $l$ 到 $r$ 的每个字符取反，即所有 $\texttt{0}$ 变为 $\texttt{1}$，所有 $\texttt{1}$ 变为 $\texttt{0}$。
2. "2 $g$"（$g \in \{0, 1\}$）——计算所有满足 $s_i = g$ 的 $a_i$ 的异或和。注意，空集的异或和被认为是 $0$。

请帮助 Augustin 回答所有查询！

#### 样例

**输入：**

```
5
5
1 2 3 4 5
01000
7
2 0
2 1
1 2 4
2 0
2 1
1 1 3
2 1
```

**输出：**

```
3 2 6 7 7
```

### 算法分类

**前缀和**、**位运算**

### 题解分析与结论

本题的核心在于高效处理区间取反和查询操作。大多数题解都利用了异或运算的性质，通过维护前缀异或和来优化查询和修改操作。以下是各题解的要点对比：

1. **BINYU** 的题解通过维护一个变量 `ans` 来记录所有 $s_i = 1$ 的 $a_i$ 的异或和，利用前缀异或和快速处理区间取反操作，时间复杂度为 $O(n)$。
2. **LCat90** 的题解与 BINYU 的思路类似，同样利用前缀异或和优化操作，代码简洁明了。
3. **One_JuRuo** 的题解使用了线段树，虽然时间复杂度为 $O(n \log n)$，但代码较为复杂，适合需要更复杂操作的场景。

### 精选题解

#### 题解1：BINYU（★★★★★）

**关键亮点：**
- 利用异或性质，通过维护 `ans` 和前缀异或和，实现了 $O(1)$ 的查询和修改操作。
- 代码简洁，思路清晰，适合快速实现。

**核心代码：**

```cpp
int ans = 0;
for(int i = 1; i <= n; sum[i] = sum[i - 1] ^ a[i], i++)
    if(s[i] == '1') ans ^= a[i];
while(q--) {
    scanf("%d", &op);
    if(op == 2) {
        scanf("%d", &x);
        if(x == 1) printf("%d ", ans);
        else printf("%d ", sum[n] ^ ans);
    } else {
        scanf("%d %d", &l, &r);
        ans ^= sum[r] ^ sum[l - 1];
    }
}
```

#### 题解2：LCat90（★★★★☆）

**关键亮点：**
- 与 BINYU 的思路一致，代码实现简洁，适合快速理解。
- 通过异或前缀和优化操作，时间复杂度为 $O(n)$。

**核心代码：**

```cpp
int ans = 0;
for(int i = 1; i <= n; ++i) if(c[i - 1] == '1') ans ^= a[i];
int sb = pre[n];
while(q--) {
    int op, l, r;
    cin >> op >> l;
    if(op == 2) {
        if(l == 1) cout << ans << " ";
        else cout << (sb ^ ans) << " ";
    } else {
        cin >> r;
        ans ^= (pre[r] ^ pre[l - 1]);
    }
}
```

### 最优关键思路

利用异或运算的性质，通过维护前缀异或和，可以在 $O(1)$ 时间内完成区间取反和查询操作。这种方法不仅高效，而且代码实现简洁，适合处理大规模数据。

### 拓展思路

类似的问题可以通过维护前缀和或其他数据结构来优化操作。例如，区间求和、区间最大值等问题都可以通过类似的方法进行优化。

### 推荐题目

1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

这些题目都涉及到区间操作和查询，可以通过前缀和或树状数组等数据结构进行优化。

---
处理用时：32.28秒