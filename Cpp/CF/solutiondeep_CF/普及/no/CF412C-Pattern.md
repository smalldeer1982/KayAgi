# 题目信息

# Pattern

## 题目描述

Developers often face with regular expression patterns. A pattern is usually defined as a string consisting of characters and metacharacters that sets the rules for your search. These patterns are most often used to check whether a particular string meets the certain rules.

In this task, a pattern will be a string consisting of small English letters and question marks ('?'). The question mark in the pattern is a metacharacter that denotes an arbitrary small letter of the English alphabet. We will assume that a string matches the pattern if we can transform the string into the pattern by replacing the question marks by the appropriate characters. For example, string aba matches patterns: ???, ??a, a?a, aba.

Programmers that work for the R1 company love puzzling each other (and themselves) with riddles. One of them is as follows: you are given $ n $ patterns of the same length, you need to find a pattern that contains as few question marks as possible, and intersects with each of the given patterns. Two patterns intersect if there is a string that matches both the first and the second pattern. Can you solve this riddle?

## 说明/提示

Consider the first example. Pattern xab intersects with each of the given patterns. Pattern ??? also intersects with each of the given patterns, but it contains more question signs, hence it is not an optimal answer. Clearly, xab is the optimal answer, because it doesn't contain any question sign. There are a lot of other optimal answers, for example: aab, bab, cab, dab and so on.

## 样例 #1

### 输入

```
2
?ab
??b
```

### 输出

```
xab
```

## 样例 #2

### 输入

```
2
a
b
```

### 输出

```
?
```

## 样例 #3

### 输入

```
1
?a?b
```

### 输出

```
cacb
```

# AI分析结果



### 题目内容中文重写

**题目描述**

开发者经常使用正则表达式模式。模式通常由字符和元字符组成的字符串定义，用于设置搜索规则。这些模式常用于检查某个字符串是否符合特定规则。

在本任务中，模式为由小写字母和问号（`?`）组成的字符串。模式中的问号表示任意小写字母。若字符串能通过替换问号为适当字符得到模式，则称其匹配该模式。例如，字符串 `aba` 匹配 `???`、`??a`、`a?a`、`aba`。

R1 公司的程序员喜欢出谜题。题目如下：给定 $n$ 个长度相同的模式，找到一个包含最少问号的模式，使得该模式与所有给定模式相交。两个模式相交当且仅当存在一个字符串同时匹配这两个模式。

**说明/提示**

第一个样例中，模式 `xab` 与所有给定模式相交。虽然 `???` 也满足条件，但其包含更多问号，因此 `xab` 是最优解。

**样例 #1**

输入：
```
2
?ab
??b
```
输出：
```
xab
```

**样例 #2**

输入：
```
2
a
b
```
输出：
```
?
```

**样例 #3**

输入：
```
1
?a?b
```
输出：
```
cacb
```

---

### 算法分类
**模拟**

---

### 题解分析与结论

题目要求构造一个与所有输入模式相交且问号最少的模式。关键思路如下：
1. **逐位分析**：对每一位字符，若所有输入模式的该位存在非问号的不同字符，则目标模式该位必须为 `?`。
2. **动态维护**：逐个处理每个输入模式，维护当前答案模式的状态，避免存储所有输入数据以节省空间。

#### 最优题解亮点
1. **崔化博的题解（4星）**
   - **亮点**：使用 `!` 标记冲突位，逐行处理输入，空间复杂度低。
   - **代码**：
     ```cpp
     for (int i = 0; i < a.size(); i++) {
         if (a[i] == '?') a[i] = b[i];
         else if (a[i] != b[i] && b[i] != '?') a[i] = '!';
     }
     ```
   - **总结**：通过标记冲突位，最终将 `!` 转换为 `?`，确保高效处理大规模数据。

2. **Mysterious_Cat的题解（4星）**
   - **亮点**：简洁的冲突标记 `M`，逻辑清晰。
   - **代码**：
     ```cpp
     if (s[i] != ss[i] && ss[i] != '?') s[i] = 'M';
     ```
   - **总结**：直接标记冲突，输出时替换为 `?`，适合快速实现。

3. **蓝__的题解（4星）**
   - **亮点**：使用锁定数组标记冲突，支持随机字符填充。
   - **代码**：
     ```cpp
     if (ans[i] != a[j][i]) {
         ans[i] = '?';
         x[i] = true; // 锁定该位
     }
     ```
   - **总结**：通过锁定机制确保冲突位处理正确。

---

### 关键思路总结
1. **逐位处理**：对每一位字符独立分析，避免全局依赖。
2. **冲突标记**：通过特殊符号（如 `!` 或 `M`）记录冲突，最终统一替换为 `?`。
3. **空间优化**：逐个处理输入字符串，避免存储全部数据。

---

### 类似题目推荐
1. [CF486B OR in Matrix](https://www.luogu.com.cn/problem/CF486B)（构造问题，逐位分析）
2. [UVA1368 DNA Consensus String](https://www.luogu.com.cn/problem/UVA1368)（统计每列字符频率）
3. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)（字符串模式匹配与统计）

---
处理用时：165.87秒