---
title: "Minimum Ternary String"
layout: "post"
diff: 普及/提高-
pid: CF1009B
tag: ['字符串', '贪心', '概率论']
---

# Minimum Ternary String

## 题目描述

给定一个由 '0', '1', '2' 组成的字符串  $S$ 。可以交换相邻'0', '1'或'1', '2'的位置（例如：'12' - '21'  $\;$  '01' - '10'）请输出原字符串经过任意转换后字典序最小的字符串。原字符串长度不超过  $10^5$ 。

## 输入格式

字符串  $S$

## 输出格式

转化后字典序最小的字符串

Translated by @ZCDHJ

## 样例 #1

### 输入

```
100210

```

### 输出

```
001120

```

## 样例 #2

### 输入

```
11222121

```

### 输出

```
11112222

```

## 样例 #3

### 输入

```
20

```

### 输出

```
20

```



---

---
title: "Planning The Expedition"
layout: "post"
diff: 普及/提高-
pid: CF1011B
tag: ['模拟', '枚举', '概率论']
---

# Planning The Expedition

## 题目描述

Natasha is planning an expedition to Mars for $ n $ people. One of the important tasks is to provide food for each participant.

The warehouse has $ m $ daily food packages. Each package has some food type $ a_i $ .

Each participant must eat exactly one food package each day. Due to extreme loads, each participant must eat the same food type throughout the expedition. Different participants may eat different (or the same) types of food.

Formally, for each participant $ j $ Natasha should select his food type $ b_j $ and each day $ j $ -th participant will eat one food package of type $ b_j $ . The values $ b_j $ for different participants may be different.

What is the maximum possible number of days the expedition can last, following the requirements above?

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n \le 100 $ , $ 1 \le m \le 100 $ ) — the number of the expedition participants and the number of the daily food packages available.

The second line contains sequence of integers $ a_1, a_2, \dots, a_m $ ( $ 1 \le a_i \le 100 $ ), where $ a_i $ is the type of $ i $ -th food package.

## 输出格式

Print the single integer — the number of days the expedition can last. If it is not possible to plan the expedition for even one day, print 0.

## 说明/提示

In the first example, Natasha can assign type $ 1 $ food to the first participant, the same type $ 1 $ to the second, type $ 5 $ to the third and type $ 2 $ to the fourth. In this case, the expedition can last for $ 2 $ days, since each participant can get two food packages of his food type (there will be used $ 4 $ packages of type $ 1 $ , two packages of type $ 2 $ and two packages of type $ 5 $ ).

In the second example, there are $ 100 $ participants and only $ 1 $ food package. In this case, the expedition can't last even $ 1 $ day.

## 样例 #1

### 输入

```
4 10
1 5 2 1 1 1 2 5 7 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
100 1
1

```

### 输出

```
0

```

## 样例 #3

### 输入

```
2 5
5 4 3 2 1

```

### 输出

```
1

```

## 样例 #4

### 输入

```
3 9
42 42 42 42 42 42 42 42 42

```

### 输出

```
3

```



---

---
title: "The Bits"
layout: "post"
diff: 普及/提高-
pid: CF1017B
tag: ['数学', '概率论', '构造']
---

# The Bits

## 题目描述

手工翻译qwq，可能掺杂个人情感，但保证题目含义不变。

Rudolf正在去城堡的路上。在大门前，保安问了他一个问题：

已知两个长度为$n$的二进制数$a,b$。你可以任意选择$a$中的两个二进制位，然后把上面的数字调换位置。问题是，有多少中不同的操作，可以生成一个与原来不同的$a\;|\;b$？

换句话说，令$c=a\;|\;b$，你能找到多少种操作，使得更改后的$a$满足$a'\;|\;b \ne c$？

其中$|$表示“按位或”运算。如$(01010)_2\;|\;(10011)_2=(11011)_2$

## 输入格式

输入的第一行包含一个整数$n$。其中$2\leqslant n \leqslant 10^5$

后两行分别描述$a, b$。

## 输出格式

输出包含一个整数，表示交换的方案数。

## 样例 #1

### 输入

```
5
01011
11001

```

### 输出

```
4

```

## 样例 #2

### 输入

```
6
011000
010011

```

### 输出

```
6

```



---

---
title: "Winner"
layout: "post"
diff: 普及/提高-
pid: CF2A
tag: ['模拟', '字符串', '概率论', '栈']
---

# Winner

## 题目描述

在 Berland 流行着纸牌游戏 `Berlogging`，这个游戏的赢家是根据以下规则确定的：

1. 在每一轮中，玩家获得或失去一定数量的分数，在游戏过程中，分数被记录在 `名称和得分` 行中，其中名字是玩家的名字，得分是在这一轮中获得的分数。得分是负值意味着玩家失去了相应的分数。
2. 如果在比赛结束时只有一名玩家分数最多，他就是获胜者。
3. 如果两名或两名以上的玩家在比赛结束时都有最大的分数 $m$ ，那么其中首先获得至少 $m$ 分的玩家胜利。开始时，每个玩家都是 $0$ 分。


保证在比赛结束时至少有一个玩家的分数为正。

## 输入格式

第一行包含整数 $n$，表示是游戏进行的的回合数。

第 $2 \sim n + 1$ 行，按照时间顺序输入 `名称和得分` 行的信息，其中名称是长度不大于 $32$ 的小写字母组成的字符串，分数的绝对值不大于 $1000$。

## 输出格式

输出获胜者的名称。

## 样例 #1

### 输入

```
3
mike 3
andrew 5
mike 2

```

### 输出

```
andrew

```

## 样例 #2

### 输入

```
3
andrew 3
andrew 2
mike 5

```

### 输出

```
andrew

```



---

---
title: "Milking cows"
layout: "post"
diff: 普及/提高-
pid: CF383A
tag: ['贪心', '前缀和', '概率论']
---

# Milking cows

## 题目描述

Iahub在农场帮助他的祖父，今天他必须挤牛奶。农场里有$n$只牛左成一排，从左到右编号$1$到$n$。每只牛不是面向左边就是面向右边。当Iahub挤某一只牛的牛奶时，所有看得到这当前只牛的牛都会因为受到惊吓而损失一单位量的牛奶。面向左边的牛可以看到它左边的所有牛（不包括自己），面向右边的牛可以看到它右边的所有牛（不包括自己）。被惊吓过的牛可以再次被惊吓。被挤过奶的牛不会再被惊吓。我们假定每一头牛可以生产无限量的牛奶。

Iahub可以决定挤牛奶的顺序，但他必须每头牛都要挤。Iahub想损失尽可能少的牛奶。请输出最少的牛奶损失量。

## 输入格式

第一行包括一个整数$n(1<=n<=200000)$. 第二行包括n个整数$a_1,a_2...,a_n$。$a_i$是$0$表示牛面向左边，$1$则表示面向右边。

## 输出格式

输出一个整数，即最少的牛奶损失量

在C++中，请不要用%lld分类符来读入或输出64位整型。最好用输出输出流或者%I64D分类符

## 说明/提示

在第一个样例中,Iahub按照下面的顺序可以使得牛奶损失最少：$3,4,2,1$。当他挤牛$3$时，牛$4$会损失$1$单位牛奶。在此之后，没有牛奶损失。

Translated by @Imakf

## 样例 #1

### 输入

```
4
0 0 1 0

```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
1 0 1 0 1

```

### 输出

```
3
```



---

---
title: "Tic-tac-toe"
layout: "post"
diff: 普及/提高-
pid: CF3C
tag: ['模拟', '枚举', '概率论']
---

# Tic-tac-toe

## 题目描述

Certainly, everyone is familiar with tic-tac-toe game. The rules are very simple indeed. Two players take turns marking the cells in a $ 3×3 $ grid (one player always draws crosses, the other — noughts). The player who succeeds first in placing three of his marks in a horizontal, vertical or diagonal line wins, and the game is finished. The player who draws crosses goes first. If the grid is filled, but neither Xs, nor 0s form the required line, a draw is announced.

You are given a $ 3×3 $ grid, each grid cell is empty, or occupied by a cross or a nought. You have to find the player (first or second), whose turn is next, or print one of the verdicts below:

- illegal — if the given board layout can't appear during a valid game;
- the first player won — if in the given board layout the first player has just won;
- the second player won — if in the given board layout the second player has just won;
- draw — if the given board layout has just let to a draw.

## 输入格式

The input consists of three lines, each of the lines contains characters ".", "X" or "0" (a period, a capital letter X, or a digit zero).

## 输出格式

Print one of the six verdicts: first, second, illegal, the first player won, the second player won or draw.

## 样例 #1

### 输入

```
X0X
.0.
.X.

```

### 输出

```
second

```



---

---
title: "Bash's Big Day"
layout: "post"
diff: 普及/提高-
pid: CF757B
tag: ['枚举', '素数判断,质数,筛法', '概率论']
---

# Bash's Big Day

## 题目描述

Bash 已经踏上了成为最伟大的口袋妖怪大师的旅程。为了得到他的第一个口袋妖怪，他去了 Zulu 教授的实验室。由于 Bash 是 Zulu 教授最喜欢的学生，Zulu 允许他从实验室里取出任意数量的口袋妖怪。

但是 Zulu 警告他，每个小精灵都有一个力量值，例如 $k(k>1)$ 个小精灵在一起，它们的力量值为 $s_1,s_2,\dots,s_k$，如果 $\gcd(s_1,s_2,\dots s_k)=1$（见 $\gcd$ 的定义注释），它们之间就会互相打架。

Bash 作为一个聪明的人，不希望他的口袋妖怪互相斗争。然而，他也想最大化他从实验室里带走的神奇宝贝的数量。你能帮 Bash 找出他能带走的最大数量的口袋妖怪吗？

**注意：口袋妖怪不能与自己战斗。**

## 输入格式

输入包含两行。

第一行一个整数 $n(1\le n \le 10^5)$，表示实验室中的小精灵总数。

第二行 $n$ 个用空格隔开的整数，第 $i$ 个整数代表第 $i$ 个小精灵的力量值 $s_i(1 \le s_i \le 10^5)$。

## 输出格式

一行包含一个整数，表示能拿走的小精灵数量最大值。

## 样例 #1

### 输入

```
3
2 3 4

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5
2 3 4 6 7

```

### 输出

```
3

```



---

---
title: "Journey"
layout: "post"
diff: 普及/提高-
pid: CF839C
tag: ['数学', '概率论', '期望']
---

# Journey

## 题目描述

## 问题描述

在七大王国里有 $n$ 个城市和 $n-1$ 条道路，每条道路连接两个城市，并且通过这些道路我们可以从任何一个城市到达任何一个城市。

席恩和阿莎在第一个城市骑上马，他们要通过这些路开始一次旅行。但是有雾，所以他们看不见他们的马带他们去了哪里。当马抵达一个城市的时候（包括第一个城市），它会去跟当前这个城市相连的城市。但是这是一匹奇怪的马，它只去他们以前没有去过的城市。在每个城市，马以相同的概率移动去上述符合要求的城市，并且当没有这样的城市（可走）时，马就停下了。

每条路的长度都是 $1$，旅行从城市 $1$ 开始，问这次旅行的期望长度（旅行长度的期望值）是多少？你可以通过[这个链接](https://en.wikipedia.org/wiki/Expected\_value)来阅读一些关于期望（平均）值的文字。

## 输入格式

第一行包含一个整数 $n$（$1 \leq n \leq 100000$）——城市的数量。

下来是 $n-1$ 行，这些行中的第 $i$ 行包含两个整数 $u_i$ 和 $v_i$（$1 \leq u_i, v_i \leq n$，$u_i \not = v_i$）——第 $i$ 条边连接的城市。

保证通过这些道路可以从任何一个城市到达任何一个城市。

## 输出格式

输出一个数——这次旅行长度的期望值。旅行从城市 $1$ 开始。

当你的答案的绝对或相对误差不超过 $10^{-6}$ 时你的答案将会被接受。

换句话说，假定你的答案是 $a$，标准答案是 $b$，当 $\frac{|a-b|}{max(1,b)} \leq 10^{-6}$ 时你的答案将会被接受。

## 说明/提示

在第一个例子中，他们的旅行可能以同等的概率停止于城市 $3$ 或城市 $4$。去城市 $3$ 的距离是 $1$，去城市 $4$ 的距离是 $2$，所以期望是 $1.5$。

在第二个例子中，他们的旅行可能停止于城市 $4$ 或城市 $5$。去这些城市的距离都是 $2$，所以期望是 $2$。

## 样例 #1

### 输入

```
4
1 2
1 3
2 4

```

### 输出

```
1.500000000000000

```

## 样例 #2

### 输入

```
5
1 2
1 3
3 4
2 5

```

### 输出

```
2.000000000000000

```



---

---
title: "Equator"
layout: "post"
diff: 普及/提高-
pid: CF962A
tag: ['模拟', '概率论']
---

# Equator

## 题目描述

已知 Polycarp 共有 $n$ 天准备编程竞赛，他每天预计做的题数为 $a_i$，请问直到第几天能做完所有题目的一半或更多。

## 输入格式

第一行，一个整数 $n$。

第二行，$n$ 个整数，表示 $a_i$。

## 输出格式

一个整数，表示答案。

## 样例 #1

### 输入

```
4
1 3 2 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
6
2 2 2 2 2 2

```

### 输出

```
3

```



---

---
title: "Make a Square"
layout: "post"
diff: 普及/提高-
pid: CF962C
tag: ['递归', '枚举', '概率论']
---

# Make a Square

## 题目描述

You are given a positive integer $ n $ , written without leading zeroes (for example, the number 04 is incorrect).

In one operation you can delete any digit of the given integer so that the result remains a positive integer without leading zeros.

Determine the minimum number of operations that you need to consistently apply to the given integer $ n $ to make from it the square of some positive integer or report that it is impossible.

An integer $ x $ is the square of some positive integer if and only if $ x=y^2 $ for some positive integer $ y $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^{9} $ ). The number is given without leading zeroes.

## 输出格式

If it is impossible to make the square of some positive integer from $ n $ , print -1. In the other case, print the minimal number of operations required to do it.

## 说明/提示

In the first example we should delete from $ 8314 $ the digits $ 3 $ and $ 4 $ . After that $ 8314 $ become equals to $ 81 $ , which is the square of the integer $ 9 $ .

In the second example the given $ 625 $ is the square of the integer $ 25 $ , so you should not delete anything.

In the third example it is impossible to make the square from $ 333 $ , so the answer is -1.

## 样例 #1

### 输入

```
8314

```

### 输出

```
2

```

## 样例 #2

### 输入

```
625

```

### 输出

```
0

```

## 样例 #3

### 输入

```
333

```

### 输出

```
-1

```



---

