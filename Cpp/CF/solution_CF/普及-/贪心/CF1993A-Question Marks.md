# Question Marks

## 题目描述

Tim 正在做一个包含 $4n$ 道题目的测试，每道题目的答案仅为 `A`、`B`、`C`、`D` 四个选项中的一个，且每道题目的正确答案是均匀分配的——也就是说，`A`、`B`、`C`、`D` 四个选项分别为其中 $n$ 道题目的正确答案。

现在，对于每道题目，Tim 已经将自己的答案填到了答题卡上。我们将其视作一个长度为 $4n$ 的字符串 $s$，字符串里面的每个字符仅有可能是 `A`、`B`、`C`、`D`、`?` 五个字符当中的一个，其中第 $i$ 个字符 $s_i$ 如果是 `?`，则表示 Tim 并不确定第 $i$ 个问题的答案，否则即表示 Tim 给出的第 $i$ 个问题的答案。

现在给出 Tim 的答案，求 Tim 最多能够答对多少道题目。

## 说明/提示

对于所有数据：

- $1\leqslant T\leqslant 1000$。
- $1\leqslant n\leqslant 100$。
- $s_i\in\{\texttt{A,B,C,D,?}\}$。

Translated by [Eason_AC](/user/112917)。

## 样例 #1

### 输入

```
6
1
ABCD
2
AAAAAAAA
2
AAAABBBB
2
????????
3
ABCABCABCABC
5
ACADC??ACAC?DCAABC?C```

### 输出

```
4
2
4
0
9
13```

