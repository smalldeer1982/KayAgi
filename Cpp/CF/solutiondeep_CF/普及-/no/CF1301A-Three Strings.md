# 题目信息

# Three Strings

## 题目描述

You are given three strings $ a $ , $ b $ and $ c $ of the same length $ n $ . The strings consist of lowercase English letters only. The $ i $ -th letter of $ a $ is $ a_i $ , the $ i $ -th letter of $ b $ is $ b_i $ , the $ i $ -th letter of $ c $ is $ c_i $ .

For every $ i $ ( $ 1 \leq i \leq n $ ) you must swap (i.e. exchange) $ c_i $ with either $ a_i $ or $ b_i $ . So in total you'll perform exactly $ n $ swap operations, each of them either $ c_i \leftrightarrow a_i $ or $ c_i \leftrightarrow b_i $ ( $ i $ iterates over all integers between $ 1 $ and $ n $ , inclusive).

For example, if $ a $ is "code", $ b $ is "true", and $ c $ is "help", you can make $ c $ equal to "crue" taking the $ 1 $ -st and the $ 4 $ -th letters from $ a $ and the others from $ b $ . In this way $ a $ becomes "hodp" and $ b $ becomes "tele".

Is it possible that after these swaps the string $ a $ becomes exactly the same as the string $ b $ ?

## 说明/提示

In the first test case, it is impossible to do the swaps so that string $ a $ becomes exactly the same as string $ b $ .

In the second test case, you should swap $ c_i $ with $ a_i $ for all possible $ i $ . After the swaps $ a $ becomes "bca", $ b $ becomes "bca" and $ c $ becomes "abc". Here the strings $ a $ and $ b $ are equal.

In the third test case, you should swap $ c_1 $ with $ a_1 $ , $ c_2 $ with $ b_2 $ , $ c_3 $ with $ b_3 $ and $ c_4 $ with $ a_4 $ . Then string $ a $ becomes "baba", string $ b $ becomes "baba" and string $ c $ becomes "abab". Here the strings $ a $ and $ b $ are equal.

In the fourth test case, it is impossible to do the swaps so that string $ a $ becomes exactly the same as string $ b $ .

## 样例 #1

### 输入

```
4
aaa
bbb
ccc
abc
bca
bca
aabb
bbaa
baba
imi
mii
iim```

### 输出

```
NO
YES
YES
NO```

# AI分析结果

### 题目内容
# 三个字符串

## 题目描述
给定三个长度相同为 $n$ 的字符串 $a$、$b$ 和 $c$ 。这些字符串仅由小写英文字母组成。$a$ 的第 $i$ 个字母为 $a_i$，$b$ 的第 $i$ 个字母为 $b_i$，$c$ 的第 $i$ 个字母为 $c_i$ 。

对于每个 $i$（$1 \leq i \leq n$），你必须将 $c_i$ 与 $a_i$ 或 $b_i$ 进行交换（即互换）。所以总共你要执行恰好 $n$ 次交换操作，每次操作要么是 $c_i \leftrightarrow a_i$ ，要么是 $c_i \leftrightarrow b_i$（$i$ 遍历从 $1$ 到 $n$ 的所有整数，包括 $1$ 和 $n$ ）。

例如，如果 $a$ 是 “code”，$b$ 是 “true”，$c$ 是 “help”，你可以通过从 $a$ 中取第 $1$ 个和第 $4$ 个字母，从 $b$ 中取其他字母，使 $c$ 变为 “crue” 。这样 $a$ 变为 “hodp”，$b$ 变为 “tele” 。

问经过这些交换后，字符串 $a$ 是否有可能变得与字符串 $b$ 完全相同？

## 说明/提示
在第一个测试用例中，不可能通过交换使字符串 $a$ 变得与字符串 $b$ 完全相同。

在第二个测试用例中，对于所有可能的 $i$ ，你应该将 $c_i$ 与 $a_i$ 交换。交换后 $a$ 变为 “bca”，$b$ 变为 “bca”，$c$ 变为 “abc” 。此时字符串 $a$ 和 $b$ 相等。

在第三个测试用例中，你应该将 $c_1$ 与 $a_1$ 交换，$c_2$ 与 $b_2$ 交换，$c_3$ 与 $b_3$ 交换，$c_4$ 与 $a_4$ 交换。然后字符串 $a$ 变为 “baba”，字符串 $b$ 变为 “baba”，字符串 $c$ 变为 “abab” 。此时字符串 $a$ 和 $b$ 相等。

在第四个测试用例中，不可能通过交换使字符串 $a$ 变得与字符串 $b$ 完全相同。

## 样例 #1
### 输入
```
4
aaa
bbb
ccc
abc
bca
bca
aabb
bbaa
baba
imi
mii
iim
```
### 输出
```
NO
YES
YES
NO
```
### 算法分类
无算法分类

### 综合分析与结论
所有题解的核心思路都是判断对于每一位 $i$，是否满足 $a_i = c_i$ 或者 $b_i = c_i$ 。若所有位置都满足该条件，则可以通过交换使 $a$ 和 $b$ 相同，输出 “YES”；只要有一个位置不满足，即存在某一位 $a_i \neq c_i$ 且 $b_i \neq c_i$，则无法使 $a$ 和 $b$ 相同，输出 “NO” 。各题解在思路上基本一致，主要差异在于代码实现细节和表述清晰度。

### 通用建议与扩展思路
对于此类字符串操作判断问题，关键在于仔细分析题目给定的操作规则，找出满足目标结果的必要条件。在实现代码时，注意字符串索引通常从0开始，避免因循环起始位置错误导致错误结果。可拓展的方向有增加字符串的长度限制、字符集范围，或者改变交换规则，例如允许特定次数的不交换操作等，以增加题目的复杂度。

### 洛谷相似题目推荐
- [P1055 ISBN号码](https://www.luogu.com.cn/problem/P1055)
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)
- [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)

### 个人心得摘录与总结
借我昔日热忱提到，很多人习惯写从1开始循环到字符串长度末尾，但字符串读入是从0开始，循环应从0开始，否则可能样例全过但提交WA，强调了注意字符串索引起始位置的重要性。 

---
处理用时：44.72秒