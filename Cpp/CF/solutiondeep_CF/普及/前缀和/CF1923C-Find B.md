# 题目信息

# Find B

## 题目描述

An array $ a $ of length $ m $ is considered good if there exists an integer array $ b $ of length $ m $ such that the following conditions hold:

1. $ \sum\limits_{i=1}^{m} a_i = \sum\limits_{i=1}^{m} b_i $ ;
2. $ a_i \neq b_i $ for every index $ i $ from $ 1 $ to $ m $ ;
3. $ b_i > 0 $ for every index $ i $ from $ 1 $ to $ m $ .

You are given an array $ c $ of length $ n $ . Each element of this array is greater than $ 0 $ .

You have to answer $ q $ queries. During the $ i $ -th query, you have to determine whether the subarray $ c_{l_{i}}, c_{l_{i}+1}, \dots, c_{r_{i}} $ is good.

## 样例 #1

### 输入

```
1
5 4
1 2 1 4 5
1 5
4 4
3 4
1 3```

### 输出

```
YES
NO
YES
NO```

# AI分析结果

### 题目内容重写

#### 题目描述

一个长度为 $m$ 的数组 $a$ 被认为是“好”的，如果存在一个长度为 $m$ 的整数数组 $b$，满足以下条件：

1. $\sum\limits_{i=1}^{m} a_i = \sum\limits_{i=1}^{m} b_i$；
2. 对于每个索引 $i$，$a_i \neq b_i$；
3. 对于每个索引 $i$，$b_i > 0$。

给定一个长度为 $n$ 的数组 $c$，数组中的每个元素都大于 $0$。你需要回答 $q$ 个查询。在第 $i$ 个查询中，你需要判断子数组 $c_{l_{i}}, c_{l_{i}+1}, \dots, c_{r_{i}}$ 是否是“好”的。

#### 样例输入

```
1
5 4
1 2 1 4 5
1 5
4 4
3 4
1 3
```

#### 样例输出

```
YES
NO
YES
NO
```

### 题解分析与结论

#### 综合分析

该题的核心在于判断一个子数组是否可以通过调整其元素的值，使得调整后的数组与原数组的元素和相同，且每个元素都不相同且为正整数。难点在于如何处理数组中值为 $1$ 的元素，因为 $1$ 无法减少，只能增加，这限制了调整的可能性。

大多数题解都采用了以下思路：

1. **预处理**：通过前缀和记录数组中 $1$ 的数量和每个位置可以“补给”的值（即 $a_i - 1$ 的总和）。
2. **判断条件**：对于每个查询，判断区间内 $1$ 的数量是否小于等于可以“补给”的值。如果满足，则可以通过调整构造出合法的 $b$ 数组，否则不能。

#### 最优关键思路

1. **贪心策略**：尽量将 $b_i$ 设为 $1$，这样可以最小化 $\sum b_i$。对于 $a_i = 1$ 的情况，$b_i$ 必须设为 $2$，这增加了 $\sum b_i$ 的值。
2. **前缀和优化**：通过预处理前缀和，快速计算区间内 $1$ 的数量和可以“补给”的值，从而在 $O(1)$ 时间内完成查询。

#### 推荐题解

1. **作者：YBaggio (4星)**
   - **关键亮点**：思路清晰，代码简洁，预处理部分处理得当，判断条件明确。
   - **代码片段**：
     ```cpp
     for (int i = 1; i <= n; i++) {
         cin >> a[i];
         s[i] = s[i - 1] + (a[i] == 1);
         p[i] = p[i - 1] + (a[i] - 1);
     }
     for (int i = 1; i <= m; i++) {
         int l, r; cin >> l >> r;  
         if (l == r) cout << "NO\n";
         else cout << ((s[r] - s[l - 1] <= p[r] - p[l - 1]) ? "YES" : "NO") << '\n';
     }
     ```

2. **作者：ZZZZZZZF (4星)**
   - **关键亮点**：贪心策略明确，前缀和优化得当，代码可读性高。
   - **代码片段**：
     ```cpp
     for (int i = 1; i <= n; i++) {
         cin >> sum[i];
         sum[i] += sum[i - 1];
         sum1[i] = sum1[i - 1];
         if (sum[i] - sum[i - 1] == 1)
             sum1[i]++;
     }
     while (q--) {
         int x, y;
         cin >> x >> y;
         long long len = (y - x + 1), s = sum[y] - sum[x - 1], n1 = sum1[y] - sum1[x - 1];
         if (len == 1) {
             cout << "NO\n";
         }
         else if (s - len >= n1) {
             cout << "YES\n";
         }
         else cout << "NO\n";
     }
     ```

3. **作者：Luzhuoyuan (4星)**
   - **关键亮点**：思路清晰，代码简洁，预处理部分处理得当，判断条件明确。
   - **代码片段**：
     ```cpp
     for (int i = 1; i <= n; i++) x = read(), s1[i] = s1[i - 1] + (x == 1), s[i] = s[i - 1] + x - 1;
     while (m--) x = read(), y = read(), puts(y > x && s1[y] - s1[x - 1] <= s[y] - s[x - 1] ? "YES" : "NO");
     ```

### 推荐题目

1. **洛谷 P3374 【模板】树状数组 1**（题号：P3374）
2. **洛谷 P3368 【模板】树状数组 2**（题号：P3368）
3. **洛谷 P1908 逆序对**（题号：P1908）

这些题目都涉及前缀和或树状数组的应用，与本题的预处理和查询优化思路相似，适合进一步练习。

---
处理用时：37.60秒