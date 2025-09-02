# 题目信息

# Prefix Permutation Sums

## 题目描述

Your friends have an array of $ n $ elements, calculated its array of prefix sums and passed it to you, accidentally losing one element during the transfer. Your task is to find out if the given array can matches permutation.

A permutation of $ n $ elements is an array of $ n $ numbers from $ 1 $ to $ n $ such that each number occurs exactly one times in it.

The array of prefix sums of the array $ a $ — is such an array $ b $ that $ b_i = \sum_{j=1}^i a_j, 1 \le i \le n $ .

For example, the original permutation was $ [1, 5, 2, 4, 3] $ . Its array of prefix sums — $ [1, 6, 8, 12, 15] $ . Having lost one element, you can get, for example, arrays $ [6, 8, 12, 15] $ or $ [1, 6, 8, 15] $ .

It can also be shown that the array $ [1, 2, 100] $ does not correspond to any permutation.

## 说明/提示

In the fourth example, for example, the permutation $ [1, 2, 3, 4] $ is suitable. In the fifth example, for example, the permutation $ [2, 1] $ is suitable. In the seventh example, for example, the permutation $ [1, 2, 4, 3] $ is suitable.

## 样例 #1

### 输入

```
12
5
6 8 12 15
5
1 6 8 15
4
1 2 100
4
1 3 6
2
2
3
1 2
4
3 7 10
5
5 44 46 50
4
1 9 10
5
13 21 36 42
5
1 2 3 1000000000000000000
9
9 11 12 20 25 28 30 33```

### 输出

```
YES
YES
NO
YES
YES
NO
YES
NO
NO
NO
NO
NO```

# AI分析结果

【题目内容】
# 前缀和排列

## 题目描述

你的朋友有一个包含 $n$ 个元素的数组，计算了它的前缀和数组并传递给你，但在传递过程中不小心丢失了一个元素。你的任务是判断给定的数组是否能够匹配一个排列。

一个长度为 $n$ 的排列是一个包含 $1$ 到 $n$ 的数组，且每个数字恰好出现一次。

数组 $a$ 的前缀和数组 $b$ 定义为 $b_i = \sum_{j=1}^i a_j$，其中 $1 \le i \le n$。

例如，原始排列为 $[1, 5, 2, 4, 3]$，其前缀和数组为 $[1, 6, 8, 12, 15]$。丢失一个元素后，可能会得到 $[6, 8, 12, 15]$ 或 $[1, 6, 8, 15]$。

同样可以证明，数组 $[1, 2, 100]$ 不匹配任何排列。

## 说明/提示

在第四个样例中，排列 $[1, 2, 3, 4]$ 是合适的。在第五个样例中，排列 $[2, 1]$ 是合适的。在第七个样例中，排列 $[1, 2, 4, 3]$ 是合适的。

## 样例 #1

### 输入

```
12
5
6 8 12 15
5
1 6 8 15
4
1 2 100
4
1 3 6
2
2
3
1 2
4
3 7 10
5
5 44 46 50
4
1 9 10
5
13 21 36 42
5
1 2 3 1000000000000000000
9
9 11 12 20 25 28 30 33```

### 输出

```
YES
YES
NO
YES
YES
NO
YES
NO
NO
NO
NO
NO```

【算法分类】差分

【题解分析与结论】
该题的核心思路是通过差分操作将前缀和数组还原为原数组，并通过统计缺失的数字来判断是否能够构成一个排列。大部分题解都采用了差分和哈希表（或桶）来记录数字的出现情况，并通过分类讨论来判断是否满足条件。

【评分较高的题解】

1. **作者：Otue (赞：13)**
   - **星级：5星**
   - **关键亮点：**
     - 通过差分操作还原原数组，并统计缺失的数字。
     - 通过分类讨论，判断缺失的数字是否满足条件。
     - 代码简洁，逻辑清晰。
   - **核心代码：**
     ```cpp
     for (int i = 1; i <= n - 1; i++) cin >> a[i], b[i] = a[i] - a[i - 1], num += b[i];
     int tot = 0;    
     for (int i = 1; i <= n - 1; i++) {
         vis[b[i]]++;
     }
     for (int i = 1; i <= n; i++) {
         if (!vis[i]) tot++; // tot为1~n查分数组没有出现的数字个数
     }
     int t = n * (n + 1) / 2;
     if (tot <= 2 && (((t == num) && tot == 2) || (((((t - num) >= 1 && (t - num) <= n)) && tot == 1)))) puts("Yes");
     else puts("No");
     ```

2. **作者：Wf_yjqd (赞：3)**
   - **星级：4星**
   - **关键亮点：**
     - 通过差分操作还原原数组，并使用 `set` 和 `bitset` 来记录数字的出现情况。
     - 通过分类讨论，判断缺失的数字是否满足条件。
     - 代码可读性较好，逻辑清晰。
   - **核心代码：**
     ```cpp
     for (ll i = 1; i <= n; i++)
         Set.insert(i);
     for (ll i = 1; i < n; i++) {
         scanf("%lld", &a[i]);
         if (Set.find(a[i] - a[i - 1]) == Set.end())
             vec.push_back(a[i] - a[i - 1]);
         else {
             vis[a[i] - a[i - 1]] = 1;
             Set.erase(a[i] - a[i - 1]);
         }
     }
     ```

3. **作者：xzyg (赞：2)**
   - **星级：4星**
   - **关键亮点：**
     - 通过差分操作还原原数组，并使用 `vis` 数组记录数字的出现情况。
     - 通过分类讨论，判断缺失的数字是否满足条件。
     - 代码简洁，逻辑清晰。
   - **核心代码：**
     ```cpp
     for (ll i = 1; i <= n - 1; i++) {
         b[i] = a[i] - a[i - 1];
         if (vis[b[i]] || b[i] > n) {
             if (pos) {
                 f = false;
                 break;
             }
             pos = b[i];
         }
         vis[b[i]] = true;
     }
     ```

【最优关键思路或技巧】
1. **差分操作**：通过差分操作将前缀和数组还原为原数组，这是解决该问题的核心步骤。
2. **哈希表或桶**：使用哈希表或桶来记录数字的出现情况，便于统计缺失的数字。
3. **分类讨论**：根据缺失的数字数量和位置，进行分类讨论，判断是否满足条件。

【可拓展之处】
该题的思路可以拓展到其他与差分和排列相关的问题，例如判断一个数组是否可以通过某种操作变为排列，或者通过差分操作解决其他类似的前缀和问题。

【推荐题目】
1. [P1984 [NOIP2013 提高组] 前缀和](https://www.luogu.com.cn/problem/P1984)
2. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
3. [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406)

---
处理用时：38.53秒