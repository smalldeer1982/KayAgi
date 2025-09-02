# 题目信息

# Even Positions

## 题目描述

Monocarp had a regular bracket sequence $ s $ of length $ n $ ( $ n $ is even). He even came up with his own way to calculate its cost.

He knows that in a regular bracket sequence (RBS), each opening bracket is paired up with the corresponding closing bracket. So he decided to calculate the cost of RBS as the sum of distances between pairs of corresponding bracket pairs.

For example, let's look at RBS (())(). It has three pairs of brackets:

- (\_\_)\_\_: the distance between brackets at position $ 1 $ and at $ 4 $ is $ 4 - 1 = 3 $ ;
- \_()\_\_\_: the distance is $ 3 - 2 = 1 $ ;
- \_\_\_\_(): the distance is $ 6 - 5 = 1 $ .

 So the cost of (())() is $ 3 + 1 + 1 = 5 $ .Unfortunately, due to data corruption, Monocarp lost all characters on odd positions $ s_1, s_3, \dots, s_{n-1} $ . Only characters on even positions ( $ s_2, s_4, \dots, s_{n} $ ) remain. For example, (())() turned to \_(\_)\_).

Monocarp wants to restore his RBS by placing brackets on the odd positions. But since the restored RBS may not be unique, he wants to choose one with minimum cost. It's too hard to do for Monocarp alone, so can you help him?

Reminder: A regular bracket sequence is a string consisting of only brackets, such that this sequence, when inserted 1-s and +-s, gives a valid mathematical expression. For example, (), (()) or (()())() are RBS, while ), ()( or ())(() are not.

## 说明/提示

In the first test case, it's optimal to make $ s $ equal to (())(). The cost of $ s $ will be equal to $ 3 + 1 + 1 = 5 $ .

In the second test case, the only option is to make $ s $ equal to () with cost $ 1 $ .

In the third test case, the only possible RBS is ()()()() with cost $ 1 + 1 + 1 + 1 = 4 $ .

In the fourth test case, it's optimal to make $ s $ equal to (())(()) with cost $ 3 + 1 + 3 + 1 = 8 $ .

## 样例 #1

### 输入

```
4
6
_(_)_)
2
_)
8
_)_)_)_)
8
_(_)_(_)```

### 输出

```
5
1
4
8```

# AI分析结果



# Even Positions

## 题目描述

Monocarp 有一个长度为 $n$（$n$ 为偶数）的合法括号序列 $s$。他定义该序列的“成本”为所有匹配括号对的位置距离之和。例如，序列 `(())()` 的成本为 $3+1+1=5$。

由于数据损坏，Monocarp 丢失了所有奇数位置的字符（即 $s_1, s_3, \dots, s_{n-1}$），仅保留偶数位置的字符。现在需要填补这些缺失的奇数位置，使得恢复后的序列是合法括号序列，且成本最小。求最小成本。

## 样例输入/输出
见原题描述。

---

### 综合分析与结论

题目要求填补缺失的奇数位置，构造合法括号序列，并最小化所有括号对的间距总和。关键点在于**贪心策略**：尽可能让右括号尽早闭合最近的左括号，以减少总距离。

#### 最优题解对比

1. **Alexander 的解法（★★★★★）**
   - **核心思路**：用栈维护未匹配的左括号。遍历字符串时：
     - 遇到可填补的下划线（奇数位）时，若栈非空则填右括号，否则填左括号。
     - 直接处理确定的括号（左括号入栈，右括号匹配栈顶）。
   - **代码亮点**：
     ```cpp
     for (int i = 1; i <= n; i++) {
         c = getchar();
         if (c == '_') {
             if (!st.empty()) {  // 贪心填右括号
                 res += i - st.top();
                 st.pop();
             } else {            // 必须填左括号
                 st.push(i);
             }
         } else if (c == '(') {
             st.push(i);
         } else {               // 确定是右括号
             res += i - st.top();
             st.pop();
         }
     }
     ```
   - **实现要点**：单次遍历，时间复杂度 $O(n)$，空间复杂度 $O(n)$。

2. **CashCollectFactory 的解法（★★★★）**
   - **核心思路**：先填补字符串，再统计总成本。填补规则与 Alexander 一致。
   - **优化点**：通过先构造完整序列，再计算左右括号位置差之和。
   - **代码亮点**：
     ```cpp
     for (int i=0; i<n; i++) {
         if (s[i]=='_') {
             if (cnt==0) s[i] = '(', cnt++;
             else s[i] = ')', cnt--;
         }
         // 更新 cnt...
     }
     // 计算总成本
     for (int i=0; i<n; i++) {
         if (s[i]=='(') ans -= i;
         else ans += i;
     }
     ```
   - **缺点**：需要两次遍历，但时间复杂度仍为 $O(n)$。

#### 最优思路总结
- **贪心策略**：遇到可填补位置时，优先填右括号以尽早闭合左括号。
- **数据结构**：使用栈维护未匹配的左括号位置。
- **实现技巧**：直接维护当前总成本，无需构造完整序列。

---

### 拓展与同类题目
- **类似题型**：括号匹配问题常结合贪心或动态规划。例如：
  - **洛谷 P1241**（括号序列修复）：要求修复非法括号序列。
  - **洛谷 P7915**（合法括号对计数）：统计合法子序列数目。
  - **洛谷 P1944**（最长合法括号子串）：求最长合法子串长度。

---

### 个人心得摘录
- **调试教训**：需注意输入格式（例如字符位置与遍历顺序的对应）。
- **顿悟点**：贪心的正确性基于“尽早闭合左括号能最小化后续可能的更大距离”。

---
处理用时：260.14秒