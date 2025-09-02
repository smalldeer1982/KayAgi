# Turtle and Good Strings

## 题目描述

乌龟认为一个字符串 $ s $ 是一个优良字符串，当且仅当存在一个字符串序列 $ t_1, t_2, \ldots, t_k $ （$ k $ 是任意整数）使满足以下条件：

$ k \ge 2 $ 。
$ s = t_1 + t_2 + \ldots + t_k $，其中 $ + $ 表示连接操作。例如，$\texttt{abc} =texttt{a} + \texttt{bc} $。
对于所有 $ 1 \le i < j \le k ， t_i $ 的首字符不等于 $ t_j $ 的末字符。
乌龟给定了一个由小写拉丁字母组成的字符串 $ s $。请告诉他这个字符串 $ s $ 是否是一个优良字符串！

## 说明/提示

在第一个测试用例中，字符串序列 $\texttt{a}, \texttt{a} $ 满足条件 $ s = t_1 + t_2 + \ldots + t_k $，但 $ t_1 $ 的首字符等于 $ t_2 $ 的末字符。因此可以看出不存在满足所有条件的字符串序列，答案是 “NO”。

在第三个测试用例中，字符串序列 $\texttt{ab}, \texttt{cb} $ 满足所有条件。

在第四个测试用例中，字符串序列 $\texttt{abca}, \texttt{bcab}, \texttt{cabc} $ 满足所有条件。

## 样例 #1

### 输入

```
4
2
aa
3
aba
4
abcb
12
abcabcabcabc```

### 输出

```
No
nO
Yes
YES```

