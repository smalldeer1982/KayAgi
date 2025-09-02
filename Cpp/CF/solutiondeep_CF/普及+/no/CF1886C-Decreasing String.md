# 题目信息

# Decreasing String

## 题目描述

Recall that string $ a $ is lexicographically smaller than string $ b $ if $ a $ is a prefix of $ b $ (and $ a \ne b $ ), or there exists an index $ i $ ( $ 1 \le i \le \min(|a|, |b|) $ ) such that $ a_i < b_i $ , and for any index $ j $ ( $ 1 \le j < i $ ) $ a_j = b_j $ .

Consider a sequence of strings $ s_1, s_2, \dots, s_n $ , each consisting of lowercase Latin letters. String $ s_1 $ is given explicitly, and all other strings are generated according to the following rule: to obtain the string $ s_i $ , a character is removed from string $ s_{i-1} $ in such a way that string $ s_i $ is lexicographically minimal.

For example, if $ s_1 = \mathrm{dacb} $ , then string $ s_2 = \mathrm{acb} $ , string $ s_3 = \mathrm{ab} $ , string $ s_4 = \mathrm{a} $ .

After that, we obtain the string $ S = s_1 + s_2 + \dots + s_n $ ( $ S $ is the concatenation of all strings $ s_1, s_2, \dots, s_n $ ).

You need to output the character in position $ pos $ of the string $ S $ (i. e. the character $ S_{pos} $ ).

## 样例 #1

### 输入

```
3
cab
6
abcd
9
x
1```

### 输出

```
abx```

# AI分析结果

### 题目内容重写

#### 题目描述

回忆一下，字符串 $a$ 的字典序小于字符串 $b$，如果 $a$ 是 $b$ 的前缀（且 $a \ne b$），或者存在一个索引 $i$（$1 \le i \le \min(|a|, |b|)$）使得 $a_i < b_i$，并且对于任何索引 $j$（$1 \le j < i$）有 $a_j = b_j$。

考虑一个由小写拉丁字母组成的字符串序列 $s_1, s_2, \dots, s_n$。字符串 $s_1$ 是明确给定的，其他字符串根据以下规则生成：为了得到字符串 $s_i$，从字符串 $s_{i-1}$ 中删除一个字符，使得字符串 $s_i$ 的字典序最小。

例如，如果 $s_1 = \mathrm{dacb}$，那么 $s_2 = \mathrm{acb}$，$s_3 = \mathrm{ab}$，$s_4 = \mathrm{a}$。

然后，我们得到字符串 $S = s_1 + s_2 + \dots + s_n$（$S$ 是所有字符串 $s_1, s_2, \dots, s_n$ 的拼接）。

你需要输出字符串 $S$ 中位置 $pos$ 的字符（即字符 $S_{pos}$）。

#### 样例 #1

##### 输入

```
3
cab
6
abcd
9
x
1
```

##### 输出

```
abx
```

### 算法分类
贪心、字符串

### 题解分析与结论

题目要求从字符串 $s_1$ 开始，每次删除一个字符，使得新字符串的字典序最小，最终将所有字符串拼接后输出指定位置的字符。核心难点在于如何高效地找到每次删除的字符，使得字典序最小。

#### 关键思路与技巧
1. **贪心策略**：每次删除最靠前的满足 $s[i] > s[i+1]$ 的字符，这样可以保证字典序最小。
2. **单调栈优化**：使用单调栈来维护字符的删除顺序，避免每次从头扫描，时间复杂度从 $O(n^2)$ 优化到 $O(n)$。
3. **链表维护**：通过链表快速找到前驱和后继字符，优化删除操作。

#### 最优题解

##### 题解作者：LittleDrinks (赞：11)
- **星级**：★★★★★
- **关键亮点**：使用单调栈优化删除操作，时间复杂度为 $O(n)$，代码简洁清晰。
- **核心代码**：
  ```cpp
  vector <char> stk;
  bool done = (p<=n);
  for (int i = 1; i <= s.length()+1; ++i) {
      while ( (!done) && (!stk.empty()) && (stk.back() > s[i]) ) {
          stk.pop_back();
          p -= (n--);
          done = (p<=n);
      }
      stk.push_back(s[i]);
  }
  cout << stk[p-1];
  ```
- **个人心得**：通过单调栈维护字符的删除顺序，避免了每次从头扫描的低效操作，极大提升了算法效率。

##### 题解作者：Jerrycyx (赞：0)
- **星级**：★★★★
- **关键亮点**：使用链表维护字符的前驱和后继，优化删除操作，时间复杂度为 $O(n)$。
- **核心代码**：
  ```cpp
  for (int i = 1; i <= n; i++) {
      if (order[i] > part) {
          sidx++;
          if (sidx == real_pos) {
              ans = s[i];
              break;
          }
      }
  }
  ```
- **个人心得**：通过链表快速找到前驱和后继字符，优化删除操作，避免了每次从头扫描的低效操作。

##### 题解作者：caoshuchen (赞：1)
- **星级**：★★★★
- **关键亮点**：使用单调栈预处理删除顺序，时间复杂度为 $O(n)$，代码简洁清晰。
- **核心代码**：
  ```cpp
  for (int i = 1; i <= n; i++) {
      while (!st.empty() && s[st.top()] > s[i])
          w[++cur] = st.top(), st.pop();
      st.push(i);
  }
  ```
- **个人心得**：通过单调栈预处理删除顺序，避免了每次从头扫描的低效操作，极大提升了算法效率。

### 扩展思路
1. **类似题目**：可以考虑其他字符串操作问题，如字符串匹配、字符串编辑距离等。
2. **算法优化**：在字符串操作中，单调栈和链表是常用的优化手段，可以应用于其他类似问题。

### 推荐题目
1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P1040 最长公共子序列](https://www.luogu.com.cn/problem/P1040)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：38.88秒