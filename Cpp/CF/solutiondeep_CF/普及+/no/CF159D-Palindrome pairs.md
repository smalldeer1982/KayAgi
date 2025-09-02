# 题目信息

# Palindrome pairs

## 题目描述

You are given a non-empty string $ s $ consisting of lowercase letters. Find the number of pairs of non-overlapping palindromic substrings of this string.

In a more formal way, you have to find the quantity of tuples $ (a,b,x,y) $ such that $ 1<=a<=b&lt;x<=y<=|s| $ and substrings $ s[a...\ b] $ , $ s[x...\ y] $ are palindromes.

A palindrome is a string that can be read the same way from left to right and from right to left. For example, "abacaba", "z", "abba" are palindromes.

A substring $ s[i...\ j] $ ( $ 1<=i<=j<=|s| $ ) of string $ s $ = $ s_{1}s_{2}...\ s_{|s|} $ is a string $ s_{i}s_{i+1}...\ s_{j} $ . For example, substring $ s[2...4] $ of string $ s $ = "abacaba" equals "bac".

## 样例 #1

### 输入

```
aa
```

### 输出

```
1
```

## 样例 #2

### 输入

```
aaa
```

### 输出

```
5
```

## 样例 #3

### 输入

```
abacaba
```

### 输出

```
36
```

# AI分析结果

### 题目内容
# 回文串对

## 题目描述
给定一个由小写字母组成的非空字符串 $s$ 。找出该字符串中不重叠的回文子串对的数量。

更正式地说，你必须找出满足 $1\leq a\leq b\lt x\leq y\leq |s|$ 的元组 $(a,b,x,y)$ 的数量，其中子串 $s[a...\ b]$ 和 $s[x...\ y]$ 是回文串。

回文串是指从左到右和从右到左读都一样的字符串。例如，“abacaba”、“z”、“abba” 都是回文串。

字符串 $s = s_{1}s_{2}...\ s_{|s|}$ 的子串 $s[i...\ j]$（$1\leq i\leq j\leq |s|$）是字符串 $s_{i}s_{i + 1}...\ s_{j}$ 。例如，字符串 $s =$ “abacaba” 的子串 $s[2...4]$ 等于 “bac” 。

## 样例 #1
### 输入
```
aa
```
### 输出
```
1
```

## 样例 #2
### 输入
```
aaa
```
### 输出
```
5
```

## 样例 #3
### 输入
```
abacaba
```
### 输出
```
36
```

### 算法分类
动态规划

### 综合分析与结论
这些题解主要围绕如何高效找出不重叠的回文子串对数量展开。多数题解采用动态规划的思路，先预处理出回文串相关信息，再通过不同方式统计对数。有的利用区间DP判断回文串，有的使用Manacher算法求回文半径。部分题解还结合了差分、前缀和等技巧优化计算。不同题解在时间复杂度、空间复杂度及代码实现的简洁性上有所差异。

### 所选的题解
- **作者：BreakPlus（5星）**
  - **关键亮点**：利用区间DP判断每个子串是否为回文串，同时通过区间DP计算每个区间内的回文串数量，最后枚举每个回文串，结合容斥原理统计不重叠回文子串对的数量，思路清晰，逻辑严谨。
  - **重点代码核心实现思想**：通过两层循环枚举子串长度和起始位置，利用状态转移方程 `check[i][j] = check[i + 1][j - 1] & (str[i] == str[j])` 判断子串是否为回文串；再通过类似方式计算区间内回文串数量 `sum[i][j] = sum[i + 1][j] + sum[i][j - 1] - sum[i + 1][j - 1]`，若 `[i, j]` 是回文串则 `sum[i][j]++`；最后枚举回文串，累加符合条件的对数并除以2得到最终答案。
  ```cpp
  for(int len = 2; len <= n; len++)
      for(int i = 1, j = len; j <= n; i++, j++){
          if(str[i]!= str[j]) check[i][j] = false;
          else check[i][j] = check[i + 1][j - 1];
      }
  for(int len = 2; len <= n; len++)
      for(int i = 1, j = len; j <= n; i++, j++){
          sum[i][j] = sum[i + 1][j] + sum[i][j - 1] - sum[i + 1][j - 1];
          if(str[i] == str[j] && check[i + 1][j - 1]) sum[i][j]++;
      }
  for(int i = 1; i <= n; i++)
      for(int j = i; j <= n; j++)
          if(check[i][j]) answer += (sum[1][i - 1] + sum[j + 1][n]);
  printf("%lld\n", answer / 2);
  ```
- **作者：7KByte（4星）**
  - **关键亮点**：先 $O(N^2)$ 预处理出每个子串是否为回文串，再通过 $O(N^2)$ 预处理出以每个位置为终点的回文串数量，最后枚举每个回文串，将其左端点之前的回文串数量累加到答案中，实现较为简洁。
  - **重点代码核心实现思想**：通过两层循环枚举子串的起始和结束位置，利用状态转移方程 `c[l][r] = c[l + 1][r - 1] & (s[l] == s[r])` 判断子串是否为回文串；在枚举回文串时，若 `c[l][r]` 为真，则将 `f[l - 1]` 累加到答案 `ans` 中，并更新 `f[r]`。
  ```cpp
  pre(l, n - 1, 1)rep(r, l + 1, n)c[l][r] = c[l + 1][r - 1] & (s[l] == s[r]);
  long long ans = 0;
  rep(r, 1, n){
      pre(l, r, 1)if(c[l][r])ans += f[l - 1], f[r]++;
      f[r] += f[r - 1];
  }
  printf("%lld\n", ans);
  ```
- **作者：DennyQi（4星）**
  - **关键亮点**：维护 `dp_i` 表示区间 $[1, i]$ 中的回文串数量，通过枚举回文串中心向两边扩张的方式，在扩张过程中同时统计 `dp` 和答案，减少了预处理步骤，优化了代码实现。
  - **重点代码核心实现思想**：外层循环枚举字符串中的每个字符，对于每个字符，分别以其自身和其与下一个字符为中心向两边扩张，若字符相等则更新 `dp` 并累加答案 `ans += dp[i - j - 1]`。
  ```cpp
  for(int i = 1; i <= n; ++i){
      dp[i] += dp[i - 1];
      for(int j = 0; i + j <= n && i - j >= 1; ++j){
          if(s[i + j]!= s[i - j]) break;
          ++dp[i + j];
          ans += dp[i - j - 1];
      }
      if(i < n && s[i] == s[i + 1]){
          for(int j = 0; i + 1 + j <= n && i - j >= 1; ++j){
              if(s[i + 1 + j]!= s[i - j]) break;
              ++dp[i + j + 1];
              ans += dp[i - j - 1];
          }   
      }
  }
  printf("%lld\n", ans);
  ```

### 最优关键思路或技巧
1. **动态规划判断回文串**：利用区间DP，通过状态转移方程 `check[i][j] = check[i + 1][j - 1] & (str[i] == str[j])` 高效判断子串是否为回文串，减少暴力判断的时间复杂度。
2. **利用前缀和或区间DP统计回文串数量**：如通过 `sum[i][j]` 或 `f[i]` 记录区间内或前缀中的回文串数量，方便后续统计不重叠回文子串对。
3. **枚举回文串中心优化**：像DennyQi的题解，通过枚举回文串中心向两边扩张，在扩张过程中直接统计答案，减少了额外的预处理操作，简化了代码逻辑。

### 可拓展之处
同类型题可考虑字符串长度更长的情况，此时 $O(n^2)$ 的算法可能超时，需要进一步优化，如利用更高效的回文串判断算法（如Manacher算法结合优化）或数据结构（如线段树、树状数组）来加速统计过程。类似算法套路可应用于其他涉及字符串子串性质判断及数量统计的问题。

### 洛谷推荐题目
1. **P3805 【模板】manacher算法**：通过该题可深入理解Manacher算法求回文半径的过程，与本题部分利用Manacher算法预处理回文串信息相关。
2. **P1439 【模板】最长公共子序列**：同样是字符串相关的动态规划问题，可锻炼对字符串动态规划状态设计和转移方程推导的能力。
3. **P1501 单词接龙**：涉及字符串的拼接与匹配，可加深对字符串操作及利用动态规划解决字符串问题的理解。 

---
处理用时：64.88秒