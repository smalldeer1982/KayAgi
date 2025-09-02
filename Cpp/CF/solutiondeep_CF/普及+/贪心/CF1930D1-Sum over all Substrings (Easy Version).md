# 题目信息

# Sum over all Substrings (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference between the two versions is the constraint on $ t $ and $ n $ . You can make hacks only if both versions of the problem are solved.

For a binary $ ^\dagger $ pattern $ p $ and a binary string $ q $ , both of length $ m $ , $ q $ is called $ p $ -good if for every $ i $ ( $ 1 \leq i \leq m $ ), there exist indices $ l $ and $ r $ such that:

- $ 1 \leq l \leq i \leq r \leq m $ , and
- $ p_i $ is a mode $ ^\ddagger $ of the string $ q_l q_{l+1} \ldots q_{r} $ .

For a pattern $ p $ , let $ f(p) $ be the minimum possible number of $ \mathtt{1} $ s in a $ p $ -good binary string (of the same length as the pattern).

You are given a binary string $ s $ of size $ n $ . Find $ $$$\sum_{i=1}^{n} \sum_{j=i}^{n} f(s_i s_{i+1} \ldots s_j). $ $  In other words, you need to sum the values of  $ f $  over all  $ \\frac{n(n+1)}{2} $  substrings of  $ s $ .</p><p> $ ^\\dagger $  A binary <span class="tex-font-style-it">pattern</span> is a string that only consists of characters  $ \\mathtt{0} $  and  $ \\mathtt{1} $ .</p><p> $ ^\\ddagger $  Character  $ c $  is a mode of string  $ t $  of length  $ m $  if the number of occurrences of  $ c $  in  $ t $  is at least  $ \\lceil \\frac{m}{2} \\rceil $ . For example,  $ \\mathtt{0} $  is a mode of  $ \\mathtt{010} $ ,  $ \\mathtt{1} $  is not a mode of  $ \\mathtt{010} $ , and both  $ \\mathtt{0} $  and  $ \\mathtt{1} $  are modes of  $ \\mathtt{011010}$$$.

## 说明/提示

In the first test case, the only $ \mathtt{1} $ -good string is $ \mathtt{1} $ . Thus, $ f(\mathtt{1})=1 $ .

In the second test case, $ f(\mathtt{10})=1 $ because $ \mathtt{01} $ is $ \mathtt{10} $ -good, and $ \mathtt{00} $ is not $ \mathtt{10} $ -good. Thus, the answer is $ f(\mathtt{1})+f(\mathtt{10})+f(\mathtt{0}) = 1 + 1 + 0 = 2 $ .

In the third test case, $ f $ equals to $ 0 $ for all $ 1 \leq i \leq j \leq 5 $ . Thus, the answer is $ 0 $ .

## 样例 #1

### 输入

```
4
1
1
2
10
5
00000
20
11110110000000111111```

### 输出

```
1
2
0
346```

# AI分析结果



【题目翻译】

# 所有子串的和（简单版）

## 题目描述

这是该问题的简单版。两个版本的唯一区别在于对 $ t $ 和 $ n $ 的限制。只有当两个版本均被解决时，你才能进行 hack。

对于长度为 $ m $ 的二进制模式 $ p $ 和二进制字符串 $ q $，若对于每个 $ i $（$ 1 \leq i \leq m $），存在下标 $ l $ 和 $ r $ 满足以下条件，则称 $ q $ 是 $ p $-好的：
- $ 1 \leq l \leq i \leq r \leq m $，且
- $ p_i $ 是子串 $ q_l q_{l+1} \ldots q_r $ 的众数 $ ^\ddagger $。

对于模式 $ p $，定义 $ f(p) $ 为满足 $ p $-好的二进制字符串 $ q $（与模式长度相同）中最少的 $ \mathtt{1} $ 的数量。

给定长度为 $ n $ 的二进制字符串 $ s $，计算所有子串的 $ f $ 值之和。即，对所有 $ \frac{n(n+1)}{2} $ 个 $ s $ 的子串，求 $ f $ 值的总和。

$ ^\dagger $ 二进制模式指仅由 $ \mathtt{0} $ 和 $ \mathtt{1} $ 组成的字符串。

$ ^\ddagger $ 字符 $ c $ 是长度为 $ m $ 的字符串 $ t $ 的众数，当且仅当 $ c $ 在 $ t $ 中的出现次数至少为 $ \lceil \frac{m}{2} \rceil $。例如，$ \mathtt{0} $ 是 $ \mathtt{010} $ 的众数，而 $ \mathtt{1} $ 不是；$ \mathtt{011010} $ 中 $ \mathtt{0} $ 和 $ \mathtt{1} $ 均为众数。

---

【题解对比与结论】

**关键思路总结**：
1. **贪心覆盖策略**：每个 `q` 中的 `1` 可以覆盖 `p` 中连续三个位置的 `1` 的需求。具体来说，在遍历子串时，若遇到未被覆盖的 `1`，则在 `q` 的下一个位置放置 `1`，并跳过后续两位。
2. **高效枚举子串**：通过维护距离上一个 `1` 的位置变量 `x`，将时间复杂度优化至 $O(n^2)$，适用于较大数据范围。

**最优题解分析**：

#### 题解作者：IGA_Indigo（★★★★★）
**关键亮点**：
- **贪心策略优化**：通过维护变量 `x` 记录距离上一个 `1` 的位置，实现 $O(n^2)$ 时间复杂度。
- **代码简洁高效**：外层循环枚举子串起点，内层循环动态计算每个子串的 `f(p)` 值，巧妙累加总和。
- **核心代码思想**：
  ```cpp
  for (int i = 1; i <= n; i++) {
      int sum = 0, x = 2; // x 初始设为2以确保首次触发条件
      for (int j = i; j <= n; j++) {
          x++;
          if (s[j] == '1' && x > 2) {
              sum++;  // 放置1并覆盖后续两位
              x = 0;  // 重置距离计数器
          }
          ans += sum; // 累加当前子串的贡献
      }
  }
  ```
**个人心得**：
- **变量初始值设定**：将 `x` 初始设为 `2` 确保首个字符满足触发条件，避免边界处理。
- **动态累加技巧**：在遍历子串结束位置时直接累加 `sum`，避免重复计算。

---

【相似题目推荐】
1. [CF1930D2](https://codeforces.com/contest/1930/problem/D2)（Hard 版本，需结合动态规划优化）
2. [洛谷 P2679](https://www.luogu.com.cn/problem/P2679)（子串覆盖与动态规划）
3. [洛谷 P1351](https://www.luogu.com.cn/problem/P1351)（贪心策略与区间覆盖）

---
处理用时：342.18秒