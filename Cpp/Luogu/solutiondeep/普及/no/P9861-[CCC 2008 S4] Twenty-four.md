# 题目信息

# [CCC 2008 S4] Twenty-four

## 题目描述

Twenty-four is a popular card game designed to be played by four players. Each player is dealt a deck of cards, which are kept face down. On every turn, each of the four players turns over the top card of his or her deck, so that it is visible to all. The goal is to find an arithmetic expression using the values of the cards (with $A$ meaning $1$, $J$ meaning $11$, $Q$ meaning $12$, and K meaning $13$) that evaluates to the number $24$. For example, for the example in the illustration, one possible expression would be:

$((A \times K) - J) \times Q$

$((1 \times 13) - 11) \times 12$

The first player to find such an expression wins the turn, and adds all four cards to the bottom of his or her deck.

Each valid arithmetic expression must use all four cards, and must combine their values using addition, subtraction, multiplication, or division. Parentheses are allowed to specify precedence of operations. Juxtaposing cards to make multiple-digit decimal numbers is not allowed (e.g. you cannot place the cards $2$ and $4$ beside each other to make $24$). Non-integer quotients of division are also not allowed, even as a partial result (of a subexpression of the overall expression).

In some cases, the players may take a very long time to find an expression evaluating to $24$. In fact, in some cases, no such expression exists. Your task is to determine, given four cards, an expression that evaluates to the largest number less than or equal to $24$.

## 样例 #1

### 输入

```
3
3
3
3
3
1
1
1
1
12
5
13
1```

### 输出

```
24
4
21```

# AI分析结果



### 算法分类
**枚举**

### 题解分析与结论
题目要求用四个数通过加减乘除和括号组合出不超过24的最大值，核心难点在于覆盖所有可能的运算顺序和括号结构，并正确处理除法整除条件。各题解主要围绕暴力枚举和DFS展开：

---

#### 精选题解
1. **Milthm的题解（★★★★☆）**
   - **核心思路**：全排列枚举所有数的顺序，枚举运算符组合，覆盖五种运算结构（不同括号组合）确保所有可能情况被计算。
   - **关键亮点**：
     - 使用`next_permutation`生成全排列。
     - 通过五种固定运算结构（如`((a⊕b)⊕c)⊕d`）覆盖所有可能的括号组合。
     - 除法严格判断整除，避免非法操作。
   - **代码核心**：
     ```cpp
     do {
         for (int i=0; i<4; ++i) // 枚举运算符组合
             for (int j=0; j<4; ++j)
                 for (int k=0; k<4; ++k) {
                     // 五种运算结构计算
                     int x = calc(calc(calc(a[1],a[2],i),a[3],j),a[4],k);
                     // 其他四种结构同理...
                     if (x <=24) ans = max(ans, x);
                 }
     } while (next_permutation(a+1, a+5)); // 全排列
     ```

2. **xiangyanhao的题解（★★★★☆）**
   - **核心思路**：递归DFS每次选两个数运算，合并结果后递归处理剩余数，自然覆盖所有括号组合。
   - **关键亮点**：
     - 利用`multiset`动态维护剩余数，避免重复计算。
     - 递归终止条件为只剩一个数时更新答案。
   - **代码核心**：
     ```cpp
     void dfs(multiset<double> s) {
         if (s.size() == 1) {
             if (结果合法) ans = max(ans, ...);
             return;
         }
         for (选两个数u, v) {
             // 生成新集合并插入运算结果
             multiset<double> tmp = ...;
             tmp.insert(u + v); // 加减乘除同理
             dfs(tmp);
         }
     }
     ```

---

### 最优思路总结
1. **全排列与运算符枚举**：通过排列所有数的顺序和运算符组合，确保覆盖所有可能的表达式形式。
2. **运算结构覆盖**：通过固定运算结构（如题解一的五种）或递归DFS（如题解三）覆盖所有括号组合。
3. **除法合法性判断**：在运算过程中严格检查除法是否整除，避免非法中间结果。

### 拓展与相似题目
- **P1236** 算24点（基础版，需输出具体表达式）
- **P1834** 疯狂の算24（类似优化问题）
- **P2719** 整数拼接问题（类似枚举组合思路）

### 个人心得摘录
- **Milthm**：通过固定五种运算结构覆盖所有括号组合，强调全排列的必要性。
- **xiangyanhao**：DFS递归的简洁性，但需注意集合拷贝带来的性能影响。
- **ivyjiao（教训）**：随机贪心虽快，但无法保证正确性，需谨慎使用。

---
处理用时：160.10秒