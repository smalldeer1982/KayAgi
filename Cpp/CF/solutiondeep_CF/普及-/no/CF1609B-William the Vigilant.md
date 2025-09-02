# 题目信息

# William the Vigilant

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1609B/bc27b81066321842bda936f44a55e1a8e3d4f0d8.png)Before becoming a successful trader William got a university degree. During his education an interesting situation happened, after which William started to listen to homework assignments much more attentively. What follows is the correct formal description of the homework assignment:

You are given a string $ s $ of length $ n $ only consisting of characters "a", "b" and "c". There are $ q $ queries of format ( $ pos, c $ ), meaning replacing the element of string $ s $ at position $ pos $ with character $ c $ . After each query you must output the minimal number of characters in the string, which have to be replaced, so that the string doesn't contain string "abc" as a substring. A valid replacement of a character is replacing it with "a", "b" or "c".

A string $ x $ is a substring of a string $ y $ if $ x $ can be obtained from $ y $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

## 说明/提示

Let's consider the state of the string after each query:

1. $ s = $ "abcabcabc". In this case $ 3 $ replacements can be performed to get, for instance, string $ s = $ "bbcaccabb". This string does not contain "abc" as a substring.
2. $ s = $ "bbcabcabc". In this case $ 2 $ replacements can be performed to get, for instance, string $ s = $ "bbcbbcbbc". This string does not contain "abc" as a substring.
3. $ s = $ "bccabcabc". In this case $ 2 $ replacements can be performed to get, for instance, string $ s = $ "bccbbcbbc". This string does not contain "abc" as a substring.
4. $ s = $ "bcaabcabc". In this case $ 2 $ replacements can be performed to get, for instance, string $ s = $ "bcabbcbbc". This string does not contain "abc" as a substring.
5. $ s = $ "bcabbcabc". In this case $ 1 $ replacements can be performed to get, for instance, string $ s = $ "bcabbcabb". This string does not contain "abc" as a substring.
6. $ s = $ "bcabccabc". In this case $ 2 $ replacements can be performed to get, for instance, string $ s = $ "bcabbcabb". This string does not contain "abc" as a substring.
7. $ s = $ "bcabccaac". In this case $ 1 $ replacements can be performed to get, for instance, string $ s = $ "bcabbcaac". This string does not contain "abc" as a substring.
8. $ s = $ "bcabccaab". In this case $ 1 $ replacements can be performed to get, for instance, string $ s = $ "bcabbcaab". This string does not contain "abc" as a substring.
9. $ s = $ "ccabccaab". In this case $ 1 $ replacements can be performed to get, for instance, string $ s = $ "ccabbcaab". This string does not contain "abc" as a substring.
10. $ s = $ "ccaaccaab". In this case the string does not contain "abc" as a substring and no replacements are needed.

## 样例 #1

### 输入

```
9 10
abcabcabc
1 a
1 b
2 c
3 a
4 b
5 c
8 a
9 b
1 c
4 a```

### 输出

```
3
2
2
2
1
2
1
1
1
0```

# AI分析结果

### 题目内容
# 警惕的威廉

## 题目描述
在成为一名成功的商人之前，威廉获得了大学学位。在他求学期间，发生了一件有趣的事情，从那以后，威廉开始更加专注地听作业任务。以下是作业任务的正确形式描述：

给定一个长度为 $n$ 的字符串 $s$，该字符串仅由字符 “a”、“b” 和 “c” 组成。有 $q$ 个查询，格式为 ($pos$, $c$)，表示将字符串 $s$ 中位置 $pos$ 的元素替换为字符 $c$。每次查询后，你必须输出为使字符串不包含子串 “abc” 而必须替换的最少字符数。字符的有效替换是将其替换为 “a”、“b” 或 “c”。

如果字符串 $x$ 可以通过从字符串 $y$ 的开头删除几个（可能为零个或全部）字符以及从末尾删除几个（可能为零个或全部）字符而得到，那么字符串 $x$ 就是字符串 $y$ 的子串。

## 说明/提示
让我们考虑每次查询后字符串的状态：
1. $s = $ "abcabcabc"。在这种情况下，可以进行 $3$ 次替换，例如得到字符串 $s = $ "bbcaccabb"。此字符串不包含 “abc” 作为子串。
2. $s = $ "bbcabcabc"。在这种情况下，可以进行 $2$ 次替换，例如得到字符串 $s = $ "bbcbbcbbc"。此字符串不包含 “abc” 作为子串。
3. $s = $ "bccabcabc"。在这种情况下，可以进行 $2$ 次替换，例如得到字符串 $s = $ "bccbbcbbc"。此字符串不包含 “abc” 作为子串。
4. $s = $ "bcaabcabc"。在这种情况下，可以进行 $2$ 次替换，例如得到字符串 $s = $ "bcabbcbbc"。此字符串不包含 “abc” 作为子串。
5. $s = $ "bcabbcabc"。在这种情况下，可以进行 $1$ 次替换，例如得到字符串 $s = $ "bcabbcabb"。此字符串不包含 “abc” 作为子串。
6. $s = $ "bcabccabc"。在这种情况下，可以进行 $2$ 次替换，例如得到字符串 $s = $ "bcabbcabb"。此字符串不包含 “abc” 作为子串。
7. $s = $ "bcabccaac"。在这种情况下，可以进行 $1$ 次替换，例如得到字符串 $s = $ "bcabbcaac"。此字符串不包含 “abc” 作为子串。
8. $s = $ "bcabccaab"。在这种情况下，可以进行 $1$ 次替换，例如得到字符串 $s = $ "bcabbcaab"。此字符串不包含 “abc” 作为子串。
9. $s = $ "ccabccaab"。在这种情况下，可以进行 $1$ 次替换，例如得到字符串 $s = $ "ccabbcaab"。此字符串不包含 “abc” 作为子串。
10. $s = $ "ccaaccaab"。在这种情况下，字符串不包含 “abc” 作为子串，无需替换。

## 样例 #1
### 输入
```
9 10
abcabcabc
1 a
1 b
2 c
3 a
4 b
5 c
8 a
9 b
1 c
4 a
```
### 输出
```
3
2
2
2
1
2
1
1
1
0
```

### 算法分类
字符串

### 综合分析与结论
所有题解思路本质相同，均基于以下核心思路：将求使字符串不包含子串“abc”所需的最少修改次数，转化为统计字符串中“abc”子串的数量。由于每次操作仅改变一个字符，对“abc”子串数量的影响最多为1，所以通过在初始时统计“abc”子串数量，后续每次操作时根据修改字符的情况分情况讨论，判断“abc”子串数量是增加1、减少1还是不变，从而高效维护“abc”子串数量，避免每次操作后重新遍历整个字符串带来的高时间复杂度。

### 通用建议与扩展思路
此类题目关键在于抓住每次操作对目标子串影响的规律，通过预处理和针对性的局部更新来优化时间复杂度。类似题目可能会改变目标子串，或增加操作类型，但核心思路依然是分析操作对目标子串数量的影响并高效维护。例如，可以拓展到对多个不同目标子串的处理，或者操作涉及子串的插入、删除等。

### 洛谷相似题目
- [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)：经典的字符串匹配问题，有助于深入理解字符串匹配算法原理。
- [P2406 字符串匹配问题](https://www.luogu.com.cn/problem/P2406)：同样是字符串匹配相关，可进一步巩固字符串操作技巧。
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：涉及字符串查找与统计，锻炼对字符串的处理能力。 

---
处理用时：33.23秒