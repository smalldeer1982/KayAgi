# 题目信息

# Acacius and String

## 题目描述

Acacius is studying strings theory. Today he came with the following problem.

You are given a string $ s $ of length $ n $ consisting of lowercase English letters and question marks. It is possible to replace question marks with lowercase English letters in such a way that a string "abacaba" occurs as a substring in a resulting string exactly once?

Each question mark should be replaced with exactly one lowercase English letter. For example, string "a?b?c" can be transformed into strings "aabbc" and "azbzc", but can't be transformed into strings "aabc", "a?bbc" and "babbc".

Occurrence of a string $ t $ of length $ m $ in the string $ s $ of length $ n $ as a substring is a index $ i $ ( $ 1       \leq i \leq n - m + 1 $ ) such that string $ s[i..i+m-1] $ consisting of $ m $ consecutive symbols of $ s $ starting from $ i $ -th equals to string $ t $ . For example string "ababa" has two occurrences of a string "aba" as a substring with $ i = 1 $ and $ i = 3 $ , but there are no occurrences of a string "aba" in the string "acba" as a substring.

Please help Acacius to check if it is possible to replace all question marks with lowercase English letters in such a way that a string "abacaba" occurs as a substring in a resulting string exactly once.

## 说明/提示

In first example there is exactly one occurrence of a string "abacaba" in the string "abacaba" as a substring.

In second example seven question marks can be replaced with any seven lowercase English letters and with "abacaba" in particular.

In sixth example there are two occurrences of a string "abacaba" as a substring.

## 样例 #1

### 输入

```
6
7
abacaba
7
???????
11
aba?abacaba
11
abacaba?aba
15
asdf???f???qwer
11
abacabacaba```

### 输出

```
Yes
abacaba
Yes
abacaba
Yes
abadabacaba
Yes
abacabadaba
No
No```

# AI分析结果

### 题目内容重写

#### 题目描述

Acacius正在研究字符串理论。今天他遇到了以下问题。

给定一个长度为 $n$ 的字符串 $s$，由小写英文字母和问号组成。是否可以通过将问号替换为小写英文字母，使得生成的字符串中恰好包含一个子串 "abacaba"？

每个问号必须替换为一个小写英文字母。例如，字符串 "a?b?c" 可以转换为 "aabbc" 和 "azbzc"，但不能转换为 "aabc"、"a?bbc" 和 "babbc"。

字符串 $t$ 在字符串 $s$ 中作为子串出现的位置是索引 $i$（$1 \leq i \leq n - m + 1$），使得从第 $i$ 个字符开始的连续 $m$ 个字符组成的子串等于字符串 $t$。例如，字符串 "ababa" 中有两个子串 "aba" 出现的位置，分别是 $i = 1$ 和 $i = 3$，但字符串 "acba" 中没有子串 "aba"。

请帮助Acacius判断是否可以通过替换所有问号，使得生成的字符串中恰好包含一个子串 "abacaba"。

#### 说明/提示

在第一个样例中，字符串 "abacaba" 中恰好包含一个子串 "abacaba"。

在第二个样例中，七个问号可以替换为任意七个小写英文字母，特别是可以替换为 "abacaba"。

在第六个样例中，字符串 "abacabacaba" 中包含两个子串 "abacaba"。

### 算法分类

枚举、字符串

### 题解分析与结论

这道题的核心在于通过枚举所有可能的子串位置，判断是否可以通过替换问号使得生成的字符串中恰好包含一个子串 "abacaba"。题解中大多采用了暴力枚举的方法，时间复杂度为 $O(t \times n^2)$，由于字符串长度较短，能够通过题目要求。

### 评分较高的题解

#### 题解1：作者：Theophania (赞：3)

**星级：4星**

**关键亮点：**
- 思路清晰，代码简洁。
- 通过逐个检查每个可能的子串位置，判断是否可以通过替换问号生成目标子串。
- 使用 `check` 函数进行子串匹配和问号替换，逻辑清晰。

**核心代码：**
```cpp
bool check(string s, int k) {
    int cnt = 0;
    for (int i = 0; i < 7; ++i) {
        if (s[k + i] == '?') s[k + i] = match[i];
        else if (s[k + i] != match[i]) return false;
    }
    for (int i = 0; i < s.size(); ++i) if (s[i] == '?') s[i] = 'z';
    for (int i = 0; i < s.size(); ++i) if (s.substr(i, 7) == match) cnt++;
    if (cnt == 1) {
        cout << "Yes\n" << s << '\n';
        return true;
    }
    return false;
}
```

#### 题解2：作者：lzy120406 (赞：1)

**星级：4星**

**关键亮点：**
- 代码结构清晰，逻辑严谨。
- 通过逐个检查每个可能的子串位置，构造临时字符串并统计目标子串的出现次数。
- 使用 `valid` 变量判断当前位置是否可行，减少不必要的计算。

**核心代码：**
```cpp
bool valid = true;
for (int k = 0; k < 7; ++k) {
    if (s[i + k] != '?' && s[i + k] != target[k]) {
        valid = false;
        break;
    }
}
if (!valid) continue;
```

### 最优关键思路或技巧

1. **暴力枚举**：由于字符串长度较短，可以通过暴力枚举所有可能的子串位置，判断是否可以通过替换问号生成目标子串。
2. **问号替换**：在构造临时字符串时，将问号替换为目标子串中的对应字符或其他不影响结果的字符（如 'z'）。
3. **子串匹配**：通过逐个字符匹配，判断是否可以通过替换问号生成目标子串。

### 可拓展之处

类似的问题可以扩展到其他子串匹配问题，例如判断是否可以通过替换问号生成多个目标子串，或者生成不同长度的目标子串。

### 推荐题目

1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P3805 【模板】Manacher算法](https://www.luogu.com.cn/problem/P3805)
3. [P4551 【模板】AC自动机（简单版）](https://www.luogu.com.cn/problem/P4551)

### 个人心得摘录

- **调试经历**：在构造临时字符串时，需要确保所有问号都被替换，否则可能导致子串匹配失败。
- **踩坑教训**：在统计子串出现次数时，需要确保只统计一次，否则可能导致错误的结果。

---
处理用时：32.88秒