# 题目信息

# [ARC071E] TrBBnsformBBtion

## 题目描述

考虑对一个只含 `A`，`B` 的字符串的如下操作：

1. 将一个 `A` 替换成 `BB`，或将一个 `B` 替换成 `AA`

2. 将三个连续相同的字符（`AAA` 或 `BBB`）消掉

例如说，串 `ABA` 可以通过第一个操作变成 `BBBA`，串 `BBBAAAA` 可以通过第二个操作变成 `BBBA`.

这些操作可以以任意顺序，不限次数地进行。

给出两个串 $S$ 和 $T$，以及 $q$ 次询问 $a_i, b_i, c_i, d_i$，每次询问你需要回答 $S_{a_i...b_i}$ 这一子串是否能通过这两个操作变成 $T_{c_i...d_i}$.

## 样例 #1

### 输入

```
BBBAAAABA

BBBBA

4

7 9 2 5

7 9 1 4

1 7 2 5

1 7 2 4```

### 输出

```
YES

NO

YES

NO```

## 样例 #2

### 输入

```
AAAAABBBBAAABBBBAAAA

BBBBAAABBBBBBAAAAABB

10

2 15 2 13

2 13 6 16

1 13 2 20

4 20 3 20

1 18 9 19

2 14 1 11

3 20 3 15

6 16 1 17

4 18 8 20

7 20 3 14```

### 输出

```
YES

YES

YES

YES

YES

YES

NO

NO

NO

NO```

# AI分析结果



---
处理用时：53.51秒