# Name

## 题目描述

Everything got unclear to us in a far away constellation Tau Ceti. Specifically, the Taucetians choose names to their children in a very peculiar manner.

Two young parents abac and bbad think what name to give to their first-born child. They decided that the name will be the permutation of letters of string $ s $ . To keep up with the neighbours, they decided to call the baby so that the name was lexicographically strictly larger than the neighbour's son's name $ t $ .

On the other hand, they suspect that a name tax will be introduced shortly. According to it, the Taucetians with lexicographically larger names will pay larger taxes. That's the reason abac and bbad want to call the newborn so that the name was lexicographically strictly larger than name $ t $ and lexicographically minimum at that.

The lexicographical order of strings is the order we are all used to, the "dictionary" order. Such comparison is used in all modern programming languages to compare strings. Formally, a string $ p $ of length $ n $ is lexicographically less than string $ q $ of length $ m $ , if one of the two statements is correct:

- $ n&lt;m $ , and $ p $ is the beginning (prefix) of string $ q $ (for example, "aba" is less than string "abaa"),
- $ p_{1}=q_{1} $ , $ p_{2}=q_{2} $ , ..., $ p_{k-1}=q_{k-1} $ , $ p_{k}&lt;q_{k} $ for some $ k $ ( $ 1<=k<=min(n,m) $ ), here characters in strings are numbered starting from 1.

Write a program that, given string $ s $ and the heighbours' child's name $ t $ determines the string that is the result of permutation of letters in $ s $ . The string should be lexicographically strictly more than $ t $ and also, lexicographically minimum.

## 说明/提示

In the first sample the given string $ s $ is the sought one, consequently, we do not need to change the letter order there.

## 样例 #1

### 输入

```
aad
aac
```

### 输出

```
aad
```

## 样例 #2

### 输入

```
abad
bob
```

### 输出

```
daab
```

## 样例 #3

### 输入

```
abc
defg
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
czaaab
abcdef
```

### 输出

```
abczaa
```

# 题解

## 作者：No_commander (赞：1)

记 $n = |s|,m = |t|$。

考虑贪心，先抵着字典序刚好相等来重排 $s$，若出现第 $i$ 位的字典序无法大于等于 $t_i$，这时循环回退上一步，上上步，上上上步，$\dots$ 的选择，一直到当前第 $j$ 位的字典序可以大于 $t_i$。

1. $j \neq 0$：

那么这时后面的字符从小到大排序一下就行。

2. $j = 0$：（即 $s$ 中没有字符的字典序比 $t_i$ 大）

输出 $-1$。

当然，记得判断最后 $s = t$ 的情况，只需要在 $i = m$ 时回退选择即可，步骤和上面一样。由于每次一定会选出一个字符（如果没选出来一定会回退，即一定会输出 $-1$ 结束程序或 break 掉），所以重排的复杂度线性，总复杂度 $\mathcal O(\max(n, m))$。

---

## 作者：drah_yrev (赞：0)

## 思路
判断需要的条件：
#### 1：
如果字符串 $t$ 的长度大于字符串 $s$，输出 $-1$。

如果字符串 $t$ 的最小字符的字典序，大于字符串 $s$ 的最大字符的字典序，输出 $-1$。

#### 2：
Step 1：排序 $s$ 数组，定义访问数组（$vis$）。

Step 2：遍历数组 $t$（变量为 $i$）。再在内存循环遍历数组 $s$（变量为 $j$）。

在 $s$ 数组中找到大于等于 $t_i$ 的最小值。如果 $vis_{j}=0$ 输出 $s_j$ 并将 $vis_{j}$ 设为 $1$。

---

