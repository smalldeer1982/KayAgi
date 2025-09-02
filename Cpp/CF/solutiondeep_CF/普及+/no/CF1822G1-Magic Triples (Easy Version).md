# 题目信息

# Magic Triples (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference is that in this version, $ a_i \le 10^6 $ .

For a given sequence of $ n $ integers $ a $ , a triple $ (i, j, k) $ is called magic if:

- $ 1 \le i, j, k \le n $ .
- $ i $ , $ j $ , $ k $ are pairwise distinct.
- there exists a positive integer $ b $ such that $ a_i \cdot b = a_j $ and $ a_j \cdot b = a_k $ .

Kolya received a sequence of integers $ a $ as a gift and now wants to count the number of magic triples for it. Help him with this task!

Note that there are no constraints on the order of integers $ i $ , $ j $ and $ k $ .

## 说明/提示

In the first example, there are $ 6 $ magic triples for the sequence $ a $ — $ (2, 3, 5) $ , $ (2, 5, 3) $ , $ (3, 2, 5) $ , $ (3, 5, 2) $ , $ (5, 2, 3) $ , $ (5, 3, 2) $ .

In the second example, there is a single magic triple for the sequence $ a $ — $ (2, 1, 3) $ .

## 样例 #1

### 输入

```
7
5
1 7 7 2 7
3
6 2 18
9
1 2 3 4 5 6 7 8 9
4
1000 993 986 179
7
1 10 100 1000 10000 100000 1000000
8
1 1 2 2 4 4 8 8
9
1 1 1 2 2 2 4 4 4```

### 输出

```
6
1
3
0
9
16
45```

# AI分析结果

### 题目内容重写

#### 魔法三元组（简单版）

**题目描述**

这是该问题的简单版本。唯一的不同在于此版本中，$ a_i \le 10^6 $。

给定一个包含 $ n $ 个整数的序列 $ a $，三元组 $ (i, j, k) $ 被称为魔法三元组，如果满足以下条件：

- $ 1 \le i, j, k \le n $。
- $ i $, $ j $, $ k $ 两两不同。
- 存在一个正整数 $ b $，使得 $ a_i \cdot b = a_j $ 且 $ a_j \cdot b = a_k $。

Kolya 收到了一个整数序列 $ a $ 作为礼物，现在他想计算其中的魔法三元组的数量。请帮助他完成这个任务！

注意，整数 $ i $, $ j $ 和 $ k $ 的顺序没有限制。

**说明/提示**

在第一个示例中，序列 $ a $ 有 $ 6 $ 个魔法三元组 — $ (2, 3, 5) $, $ (2, 5, 3) $, $ (3, 2, 5) $, $ (3, 5, 2) $, $ (5, 2, 3) $, $ (5, 3, 2) $。

在第二个示例中，序列 $ a $ 有一个魔法三元组 — $ (2, 1, 3) $。

**样例 #1**

### 输入

```
7
5
1 7 7 2 7
3
6 2 18
9
1 2 3 4 5 6 7 8 9
4
1000 993 986 179
7
1 10 100 1000 10000 100000 1000000
8
1 1 2 2 4 4 8 8
9
1 1 1 2 2 2 4 4 4
```

### 输出

```
6
1
3
0
9
16
45
```

### 算法分类

枚举、数学

### 题解分析与结论

1. **FFTotoro 的题解**（4星）
   - **关键亮点**：使用 `std::map` 统计每个数的出现次数，枚举最大的数 $x$ 和公比 $b$，通过乘法原理计算三元组数量。时间复杂度为 $O(n\sqrt{\max\{a_i\}})$。
   - **代码实现**：
     ```cpp
     for(auto [a,f]:m){
         for(int i=2;i<=1000;i++)
             if(!(a%(i*i)))c+=m[a]*m[a/i]*m[a/(i*i)];
         c+=f*(f-1)*(f-2); // 记得相同的情况
     }
     ```

2. **Special_Tony 的题解**（4星）
   - **关键亮点**：使用 `map` 记录每个数的出现次数，枚举 $b$ 并计算三元组数量，特别处理 $b=1$ 的情况。时间复杂度为 $O(n\sqrt{\max\{a_i\}})$。
   - **代码实现**：
     ```cpp
     for (auto i = mp.begin (); i != mp.end (); ++ i) {
         sum += i->second * (i->second - 1) * (i->second - 2); // b=1 的情况
         for (int j = 2; j * j <= i->first; ++ j)
             if (! (i->first % (j * j)))
                 sum += i->second * mp[i->first / j] * mp[i->first / j / j];
     }
     ```

3. **Erica_N_Contina 的题解**（3星）
   - **关键亮点**：使用 `map` 记录每个数的出现次数，枚举 $a_j$ 和其因子 $b$，计算三元组数量。时间复杂度为 $O(n\sqrt{V})$。
   - **代码实现**：
     ```cpp
     for(auto &t : cnt){
         int val=t.first,cntt=t.second;
         for(j=1; j*j<val; ++j){
             if(j!=1 && val%j==0 && cnt.count(val/j) && cnt.count(val*j))
                 ans+=cnt[val/j]*cntt*cnt[val*j];
             if(val%j==0 && cnt.count(j) && cnt.count(val/j*val))
                 ans+=cnt[j]*cntt*cnt[val/j*val];
         }
         if(j!=1 && j*j==val && cnt.count(j) && cnt.count(val*j)) ans+=cnt[j]*cntt*cnt[val*j];
     }
     ```

### 最优关键思路与技巧

1. **使用 `map` 统计每个数的出现次数**：这是所有题解的共同点，通过 `map` 可以快速查询每个数的出现次数，方便后续计算。
2. **枚举公比 $b$**：通过枚举公比 $b$，可以快速找到满足条件的三元组，时间复杂度为 $O(\sqrt{\max\{a_i\}})$。
3. **处理 $b=1$ 的情况**：当 $b=1$ 时，三元组中的三个数相等，需要特别处理。

### 可拓展之处

1. **扩展到更大值域**：如果 $a_i$ 的值域更大，可以考虑使用更高效的因子枚举方法，如 Pollard's Rho 算法。
2. **扩展到更多元组**：类似的问题可以扩展到四元组、五元组等，通过枚举更多的公比和因子来计算。

### 推荐题目

1. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)
2. [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)
3. [P1075 [NOIP2012 普及组] 质因数分解](https://www.luogu.com.cn/problem/P1075)

### 个人心得摘录

- **FFTotoro**：注意到 Easy Version 中 $a_i$ 的值域很小，只有 $[1,10^6]$；所以 $b$ 的大小是 $\sqrt{\max\{a_i\}}$ 级别的，最大仅有 $10^3$，该做法可以通过题目。
- **Special_Tony**：记得开 long long！这是为了避免在计算过程中出现溢出问题。

---
处理用时：52.80秒