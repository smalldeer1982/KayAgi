# 题目信息

# Asterisk-Minor Template

## 题目描述

You are given two strings $ a $ and $ b $ , consisting of lowercase Latin letters.

A template $ t $ is string, consisting of lowercase Latin letters and asterisks (character '\*'). A template is called asterisk-minor if the number of asterisks in it is less than or equal to the number of letters in it.

A string $ s $ is said to be matching a template $ t $ if you can replace each asterisk in $ t $ with a string of lowercase Latin letters (possibly, an empty string) so that it becomes equal to $ s $ .

Find an asterisk-minor template such that both $ a $ and $ b $ match it, or report that such a template doesn't exist. If there are multiple answers, print any of them.

## 说明/提示

In the first testcase, for a template "\*b", you can replace the only asterisk with "aaa" to get "aaab" (which is equal to $ a $ ) or with "zzz" to get "zzzb" (which is equal to $ b $ ).

In the third testcase, a template "\*o\*" is not asterisk-minor, as it contains more asterisks than letters. There are no asterisk-minor templates that both $ a $ and $ b $ match.

In the fourth testcase, for a template "a\*a\*a\*a", you can replace all asterisks with empty strings to get "aaaa" (which is equal to $ a $ ) or two of them with "a" and two of them with an empty string to get "aaaaaa" (which is equal to $ b $ ).

In the fifth testcase, there are no asterisks in a template "abcd", so only "abcd" can match it (which is coincidentally both $ a $ and $ b $ ).

## 样例 #1

### 输入

```
6
aaab
zzzb
codeforces
atcoder
codeforces
tokitlx
aaaa
aaaaaa
abcd
abcd
c
f```

### 输出

```
YES
*b
YES
*co*
NO
YES
a*a*a*a
YES
abcd
NO```

# AI分析结果

### 题目内容
# Asterisk-Minor Template

## 题目描述
给定两个由小写拉丁字母组成的字符串 $a$ 和 $b$ 。

模板 $t$ 是由小写拉丁字母和星号（字符 '*'）组成的字符串。如果模板中星号的数量小于或等于字母的数量，则称该模板为星号次小模板。

如果可以将模板 $t$ 中的每个星号替换为一个由小写拉丁字母组成的字符串（可能为空字符串），使得它与字符串 $s$ 相等，那么就称字符串 $s$ 与模板 $t$ 匹配。

找出一个星号次小模板，使得 $a$ 和 $b$ 都与之匹配，或者报告不存在这样的模板。如果有多个答案，输出其中任意一个。

## 说明/提示
在第一个测试用例中，对于模板 "*b"，你可以将唯一的星号替换为 "aaa" 得到 "aaab"（与 $a$ 相等），或者替换为 "zzz" 得到 "zzzb"（与 $b$ 相等）。

在第三个测试用例中，模板 "*o*" 不是星号次小模板，因为它包含的星号比字母多。不存在 $a$ 和 $b$ 都匹配的星号次小模板。

在第四个测试用例中，对于模板 "a*a*a*a"，你可以将所有星号替换为空字符串得到 "aaaa"（与 $a$ 相等），或者将其中两个替换为 "a"，另外两个替换为空字符串得到 "aaaaaa"（与 $b$ 相等）。

在第五个测试用例中，模板 "abcd" 中没有星号，所以只有 "abcd" 能与之匹配（巧合的是，$a$ 和 $b$ 都是 "abcd"）。

## 样例 #1
### 输入
```
6
aaab
zzzb
codeforces
atcoder
codeforces
tokitlx
aaaa
aaaaaa
abcd
abcd
c
f
```
### 输出
```
YES
*b
YES
*co*
NO
YES
a*a*a*a
YES
abcd
NO
```
### 算法分类
贪心

### 综合分析与结论
所有题解思路本质相同，均基于贪心策略。要点在于利用 `*` 可代表任意字符串特性，考虑三种可能的模板形式：`X*`（两字符串首字符相同）、`*X`（两字符串尾字符相同）、`*X*`（两字符串存在长度为2的公共子串）。难点在于全面考虑这三种情况并正确实现判断逻辑。

### 通用建议与扩展思路
解决此类问题时，关键在于深入理解题目对模板的定义及匹配规则，通过对样例的分析挖掘潜在规律。可拓展思路为处理多个字符串匹配同一模板的情况，或对模板的限制条件进行更复杂的设定。

### 洛谷相似题目推荐
- [P1088 火星人](https://www.luogu.com.cn/problem/P1088)
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)
- [P1502 窗口的星星](https://www.luogu.com.cn/problem/P1502) 

---
处理用时：25.74秒