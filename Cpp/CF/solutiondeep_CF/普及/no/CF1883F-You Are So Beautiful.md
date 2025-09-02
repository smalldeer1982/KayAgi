# 题目信息

# You Are So Beautiful

## 题目描述

You are given an array of integers $ a_1, a_2, \ldots, a_n $ . Calculate the number of subarrays of this array $ 1 \leq l \leq r \leq n $ , such that:

- The array $ b = [a_l, a_{l+1}, \ldots, a_r] $ occurs in the array $ a $ as a subsequence exactly once. In other words, there is exactly one way to select a set of indices $ 1 \leq i_1 < i_2 < \ldots < i_{r - l + 1} \leq n $ , such that $ b_j = a_{i_j} $ for all $ 1 \leq j \leq r - l + 1 $ .

## 说明/提示

In the first test case, there is exactly one subarray $ (1, 1) $ that suits us.

In the second test case, there is exactly one subarray $ (1, 2) $ that suits us. Subarrays $ (1, 1) $ and $ (2, 2) $ do not suit us, as the subsequence $ [1] $ occurs twice in the array.

In the third test case, all subarrays except $ (1, 1) $ and $ (3, 3) $ are suitable.

## 样例 #1

### 输入

```
6
1
1
2
1 1
3
1 2 1
4
2 3 2 1
5
4 5 4 5 4
10
1 7 7 2 3 4 3 2 1 100```

### 输出

```
1
1
4
7
4
28```

# AI分析结果

【题目内容】
# You Are So Beautiful

## 题目描述

给定一个整数数组 $a_1, a_2, \ldots, a_n$，计算满足以下条件的子数组的数量 $1 \leq l \leq r \leq n$：

- 数组 $b = [a_l, a_{l+1}, \ldots, a_r]$ 在数组 $a$ 中作为子序列恰好出现一次。换句话说，恰好存在一种方式选择一组索引 $1 \leq i_1 < i_2 < \ldots < i_{r - l + 1} \leq n$，使得 $b_j = a_{i_j}$ 对所有 $1 \leq j \leq r - l + 1$ 成立。

## 说明/提示

在第一个测试用例中，恰好有一个子数组 $(1, 1)$ 满足条件。

在第二个测试用例中，恰好有一个子数组 $(1, 2)$ 满足条件。子数组 $(1, 1)$ 和 $(2, 2)$ 不满足条件，因为子序列 $[1]$ 在数组中出现了两次。

在第三个测试用例中，除了 $(1, 1)$ 和 $(3, 3)$ 之外的所有子数组都满足条件。

## 样例 #1

### 输入

```
6
1
1
2
1 1
3
1 2 1
4
2 3 2 1
5
4 5 4 5 4
10
1 7 7 2 3 4 3 2 1 100```

### 输出

```
1
1
4
7
4
28```

【算法分类】
前缀和

【题解分析与结论】
本题的核心思路是通过预处理来确定哪些子数组满足条件。具体来说，一个子数组 $[l, r]$ 满足条件的充要条件是：$a_l$ 是数组中第一个出现的 $a_l$，且 $a_r$ 是数组中最后一个出现的 $a_r$。基于这一条件，我们可以通过预处理每个元素第一次和最后一次出现的位置，然后利用前缀和或后缀和来快速计算满足条件的子数组数量。

【高星题解】
1. **作者：One_JuRuo (5星)**
   - **关键亮点**：通过预处理每个元素最后一次出现的位置，并使用后缀和来快速计算满足条件的子数组数量。思路清晰，代码简洁。
   - **代码核心**：
     ```cpp
     map<long long,long long>m;
     for(long long i=n;i>=1;--i) if(!m.count(a[i])) r[i]=r[i+1]+1,m[a[i]]=1;else r[i]=r[i+1];
     map<long long,long long>m1;
     for(long long i=1;i<=n;++i) if(!m1.count(a[i])) ans+=r[i],m1[a[i]]=1;
     ```

2. **作者：FFTotoro (4星)**
   - **关键亮点**：使用 `map` 预处理所有可能的左端点和右端点，并通过 `lower_bound` 来匹配可用的右端点。思路清晰，代码可读性高。
   - **代码核心**：
     ```cpp
     map<int,bool> m,m2;
     for(int i=0;i<n;i++)
       if(!m[a[i]])m[a[i]]=true,l.emplace_back(i);
     for(int i=n-1;~i;i--)
       if(!m2[a[i]])m2[a[i]]=true,r.emplace_back(i);
     reverse(r.begin(),r.end());
     for(int i:l)c+=r.size()-(lower_bound(r.begin(),r.end(),i)-r.begin());
     ```

3. **作者：Gapple (4星)**
   - **关键亮点**：通过维护 $f_i$ 和 $l_i$ 分别记录 $a_i$ 是否是第一个和最后一个出现的，并使用前缀和来计算答案。思路清晰，代码简洁。
   - **代码核心**：
     ```cpp
     vector<int> suff(n, lst[n - 1]);
     for (int i = n - 2; i >= 0; --i)
         suff[i] = suff[i + 1] + (int)lst[i];
     i64 ans = 0;
     for (int i = 0; i < n; ++i)
         ans += (i64)fst[i] * suff[i];
     ```

【最优关键思路】
- **预处理**：通过预处理每个元素第一次和最后一次出现的位置，可以快速判断一个子数组是否满足条件。
- **前缀和/后缀和**：利用前缀和或后缀和来快速计算满足条件的子数组数量，避免重复计算。

【可拓展之处】
- 类似的问题可以通过预处理和前缀和/后缀和来优化计算，例如统计满足某些条件的子数组或子序列的数量。

【推荐题目】
1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

【个人心得】
- **调试经历**：在预处理时，确保每个元素第一次和最后一次出现的位置正确，避免遗漏或重复计算。
- **顿悟感想**：通过预处理和前缀和/后缀和的结合，可以大大简化问题的复杂度，提高代码的效率。

---
处理用时：28.30秒