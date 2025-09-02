# 题目信息

# 「Wdcfr-1」Beautiful Array

## 题目描述

In this problem, we define a sequence of `(` and `)` as a "bracket sequence".

The definition of *Regular Bracket Sequence* is as follows:

1. `()` is a Regular Bracket Sequence.
1. If `A` is a Regular Bracket Sequence, then `(A)` is also a Regular Bracket Sequence.
1. If `A` and `B` are Regular Bracket Sequences, then `AB` is also a Regular Bracket Sequence.

For example: `()`, `(())`, and `()()` are all Regular Bracket Sequences, but `)(`, `()(` are not.

In particular, an empty sequence is **not** a Regular Bracket Sequence sequence in this problem.

Now ~~cute~~ Ran gives you a bracket sequence $s$ of length $n$. She wants you to construct $2\cdot m$ **strictly increasing** arrays. Let us denote them as
 $p_1,p_2,\cdots,p_{2 m}$ (you can leave any of them empty). You need to ensure that all integers between $1\sim n$ appear **exactly once** in these arrays. 
 
An array $p_i=\{r_1,r_2,\cdots,r_k\}$ is *Beautiful* if    $\{s_{r_1},s_{r_2},\cdots,s_{r_k}\}$ is a Regular Bracket Sequence.

Ran wonders whether it is possible to construct these arrays so that at least $m$ of the $2\cdot m$ arrays are "beautiful arrays". 

## 说明/提示

### Explanation

For the first test case, we can construct $p_1=\{1,2\}$ and $ p_2=\{\}$. So $p_1$ is a "beautiful array".

For the second test case, it is obvious that we cannot use two numbers to construct $99$ beautiful arrays.

### Constraints

$1\le T,n,m\le 200$.

## 样例 #1

### 输入

```
2
2 1
()
2 99
()```

### 输出

```
1
0```

# AI分析结果

### 算法分类
贪心、字符串

### 综合分析与结论
该题的核心逻辑是通过贪心策略，尽可能多地匹配括号对 `()`，从而构造出尽可能多的合法括号序列。所有题解都采用了类似的方法，即通过栈或计数器来匹配括号对，并统计匹配的数量。最终判断匹配的括号对数量是否大于等于 `m`，决定输出 `1` 或 `0`。

### 所选高星题解

#### 1. 作者：Tzs_yousa (赞：8)
- **星级**: 5星
- **关键亮点**: 代码简洁明了，使用栈进行括号匹配，逻辑清晰，易于理解。
- **核心代码**:
  ```cpp
  for (int i = 1; i <= n; i++) {
      if(s[i] == '(') {
          st[++top] = i;
      } else if(top) {
          top--;
          ans++;
      }
  }
  ```
- **个人心得**: 通过栈来匹配括号对，确保每个右括号与最近的左括号匹配，避免后续影响。

#### 2. 作者：StayAlone (赞：2)
- **星级**: 4星
- **关键亮点**: 使用变量 `p` 代替栈，简化了代码结构，优化了空间复杂度。
- **核心代码**:
  ```cpp
  rep1(i, 0, n - 1) {
      if (s[i] == '(') ++p;
      else if (p) --p, ++cnt;
  }
  ```
- **个人心得**: 通过变量 `p` 记录未匹配的左括号数量，避免了显式使用栈，代码更加简洁。

#### 3. 作者：heaksicn (赞：0)
- **星级**: 4星
- **关键亮点**: 思路清晰，代码简洁，使用计数器 `now` 记录未匹配的左括号数量，逻辑简单易懂。
- **核心代码**:
  ```cpp
  for(int i=0;i<n;i++){
      if(s[i]=='('){
          now++;
      }
      if(s[i]==')'&&now){
          now--;
          ans++;
      }
  }
  ```
- **个人心得**: 通过计数器 `now` 记录未匹配的左括号数量，避免了使用栈，代码更加简洁。

### 最优关键思路或技巧
1. **贪心策略**: 通过贪心策略，尽可能多地匹配括号对 `()`，从而构造出尽可能多的合法括号序列。
2. **栈或计数器**: 使用栈或计数器来匹配括号对，确保每个右括号与最近的左括号匹配，避免后续影响。
3. **简化代码**: 通过变量代替栈，简化了代码结构，优化了空间复杂度。

### 可拓展之处
1. **括号匹配的变种**: 可以扩展到多层括号匹配，如 `{}`、`[]` 等。
2. **动态规划**: 可以尝试使用动态规划来解决更复杂的括号匹配问题，如最长合法括号子序列。

### 推荐题目
1. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
2. [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)
3. [P1944 最长括号匹配](https://www.luogu.com.cn/problem/P1944)

---
处理用时：22.14秒