# 题目信息

# Petya and Exam

## 题目描述

It's hard times now. Today Petya needs to score 100 points on Informatics exam. The tasks seem easy to Petya, but he thinks he lacks time to finish them all, so he asks you to help with one..

There is a glob pattern in the statements (a string consisting of lowercase English letters, characters "?" and "\*"). It is known that character "\*" occurs no more than once in the pattern.

Also, $ n $ query strings are given, it is required to determine for each of them if the pattern matches it or not.

Everything seemed easy to Petya, but then he discovered that the special pattern characters differ from their usual meaning.

A pattern matches a string if it is possible to replace each character "?" with one good lowercase English letter, and the character "\*" (if there is one) with any, including empty, string of bad lowercase English letters, so that the resulting string is the same as the given string.

The good letters are given to Petya. All the others are bad.

## 说明/提示

In the first example we can replace "?" with good letters "a" and "b", so we can see that the answer for the first query is "YES", and the answer for the second query is "NO", because we can't match the third letter.

Explanation of the second example.

- The first query: "NO", because character "\*" can be replaced with a string of bad letters only, but the only way to match the query string is to replace it with the string "ba", in which both letters are good.
- The second query: "YES", because characters "?" can be replaced with corresponding good letters, and character "\*" can be replaced with empty string, and the strings will coincide.
- The third query: "NO", because characters "?" can't be replaced with bad letters.
- The fourth query: "YES", because characters "?" can be replaced with good letters "a", and character "\*" can be replaced with a string of bad letters "x".

## 样例 #1

### 输入

```
ab
a?a
2
aaa
aab
```

### 输出

```
YES
NO
```

## 样例 #2

### 输入

```
abc
a?a?a*
4
abacaba
abaca
apapa
aaaaax
```

### 输出

```
NO
YES
NO
YES
```

# AI分析结果



# 题目翻译

# Petya 与考试

## 题目描述

现在是困难时期。今天 Petya 需要在信息学考试中获得 100 分。题目对 Petya 来说似乎不难，但他觉得自己没有足够的时间完成所有题目，所以他请你帮忙解决其中一个。

题目中给出一个全局模式（由小写英文字母、字符 "?" 和 "*" 组成的字符串）。已知字符 "*" 在模式中最多出现一次。

同时给出 $n$ 个查询字符串，需要判断每个字符串是否与模式匹配。

Petya 原本以为很简单，但后来发现特殊字符的含义与常规不同。

模式匹配字符串的条件是：可以替换每个 "?" 为一个好的小写英文字母，将 "*"（如果存在）替换为任意（包括空字符串）由坏的小写英文字母组成的字符串，使得结果字符串与给定字符串完全相同。

好的字母已经给 Petya，其余字母都是坏的。

## 说明/提示

第一个示例中，"?" 可以替换为好的字母 "a" 和 "b"，因此第一个查询的答案是 "YES"，第二个查询的答案是 "NO"，因为无法匹配第三个字母。

第二个示例的解释：
- 第一个查询："NO"，因为 "*" 只能替换为坏字母组成的字符串，但唯一匹配的方式是替换为 "ba"，其中两个字母都是好的。
- 第二个查询："YES"，因为 "?" 替换为对应的好字母，且 "*" 替换为空字符串。
- 第三个查询："NO"，因为 "?" 不能替换为坏字母。
- 第四个查询："YES"，因为 "?" 替换为 "a"，且 "*" 替换为坏字母 "x"。

## 样例 #1

### 输入

```
ab
a?a
2
aaa
aab
```

### 输出

```
YES
NO
```

## 样例 #2

### 输入

```
abc
a?a?a*
4
abacaba
abaca
apapa
aaaaax
```

### 输出

```
NO
YES
NO
YES
```

---

**算法分类**：字符串处理/模拟

---

### 题解分析与结论

#### 核心思路
1. **长度验证**：
   - 若模式不含星号，目标串长度必须与模式长度相等。
   - 若模式含星号，目标串长度至少为模式长度减一（`m ≥ n-1`）。
   
2. **分段匹配**：
   - 将模式分为星号前段、星号后段和星号替换段。
   - 前段和后段需严格匹配（处理问号和普通字符）。
   - 星号替换段必须全为坏字母。

3. **字符检查**：
   - 遇到 "?" 时，目标字符必须是好字母。
   - 星号替换段的每个字符必须是坏字母。

#### 最优题解

##### 题解作者：伟大的王夫子（★★★★☆）
**关键亮点**：
- 紧凑的字符遍历逻辑，通过双指针逐字符匹配。
- 实时计算星号替换段的长度 `m-n`，并直接检查该区间字符。
```cpp
// 核心代码段
for ( ; p1 <= n && p2 <= m; ++p1, ++p2) {
    if (a[p1] == '?' && v[b[p2] - 'a']) continue;
    if (a[p1] == b[p2]) continue;
    if (a[p1] == '*') {
        int tmp = p2 + m - n;
        for (int j = p2; j <= tmp; ++j)
            if (v[b[j] - 'a']) flag = 0;
        p2 = tmp;
    } else {
        flag = 0;
        break;
    }
}
```

##### 题解作者：Bai_R_X（★★★★☆）
**关键亮点**：
- 分三段处理：星号前、星号替换段、星号后。
- 显式处理字符串前后缀匹配，逻辑模块化。
```cpp
// 核心分段检查逻辑
for (i=0; i<star; i++) { /* 检查前段 */ }
for (i=t.size()-1, j=x.size()-1; i>star; i--, j--) { /* 检查后段 */ }
for (; j>=star; j--) { /* 检查替换段 */ }
```

---

### 关键技巧总结
1. **长度剪枝**：优先排除明显无法匹配的长度条件。
2. **分段处理**：将字符串分为星号前、替换段、星号后三部分独立验证。
3. **坏字母检查**：通过预存好字母集合快速判断字符合法性。

---

### 拓展与相似题目
1. **通配符匹配**（LeetCode 44）：更复杂的星号和问号规则。
2. **正则表达式匹配**（LeetCode 10）：包含更多元字符的动态规划解法。

### 推荐练习
1. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)（字符串精确匹配）
2. [P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098)（规则驱动的字符串替换）
3. [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)（模拟与规则验证）

---
处理用时：173.26秒