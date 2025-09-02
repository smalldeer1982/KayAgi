---
title: "Creative Snap"
layout: "post"
diff: 普及+/提高
pid: CF1111C
tag: ['二分', '递归', '剪枝']
---

# Creative Snap

## 题目描述

灭霸要摧毁复仇者们的基地！  

我们可以将复仇者的基地看成一个序列，每个位置都有可能有多个复仇者；但是每个复仇者只能占据一个位置。  
他们基地的长度刚好是$2$的整数幂，灭霸想要用最少的能量摧毁它们。他在摧毁过程中，可以选择：  
- 如果这段基地长度$\ge 2$，他可以将其分为相等长度的两半。  
- 烧掉这段基地。如果这段基地中没有复仇者，他需要消耗$A$的能量；如果有，则需要消耗$B*x*l$的能量。其中$l$是这段基地长度，$x$是这段中的复仇者数量。  

输出一个整数，表示他摧毁全部基地需要的最少能量。  
接下来一行$k$个整数，$a_i$表示第$i$个复仇者所在的位置

## 输出格式

一个整数，表示摧毁基地所需要的最少能量。

## 说明/提示

### 样例解释  
对于样例1，直接烧区间$[1,4]$需要能量为$4*2*2=16$。  
但是，如果将其分为$4$段，分别烧掉，所需能量只有$2+1+2+1=6$。  
可以证明没有更优的方案，所以输出`6`。 
对于全部数据：  
$1\le n \le 30$  
$1\le k \le 10^5$  
$1\le A,B \le 10^4$  
$1\le a_i \le 2^n$

## 样例 #1

### 输入

```
2 2 1 2
1 3

```

### 输出

```
6

```

## 样例 #2

### 输入

```
3 2 1 2
1 7

```

### 输出

```
8

```



---

---
title: "A Lot of Games"
layout: "post"
diff: 普及+/提高
pid: CF455B
tag: ['博弈论', '递归', '进制']
---

# A Lot of Games

## 题目描述

Andrew, Fedor and Alex are inventive guys. Now they invent the game with strings for two players.

Given a group of $ n $ non-empty strings. During the game two players build the word together, initially the word is empty. The players move in turns. On his step player must add a single letter in the end of the word, the resulting word must be prefix of at least one string from the group. A player loses if he cannot move.

Andrew and Alex decided to play this game $ k $ times. The player who is the loser of the $ i $ -th game makes the first move in the $ (i+1) $ -th game. Guys decided that the winner of all games is the player who wins the last ( $ k $ -th) game. Andrew and Alex already started the game. Fedor wants to know who wins the game if both players will play optimally. Help him.

## 输入格式

The first line contains two integers, $ n $ and $ k $ ( $ 1<=n<=10^{5} $ ; $ 1<=k<=10^{9} $ ).

Each of the next $ n $ lines contains a single non-empty string from the given group. The total length of all strings from the group doesn't exceed $ 10^{5} $ . Each string of the group consists only of lowercase English letters.

## 输出格式

If the player who moves first wins, print "First", otherwise print "Second" (without the quotes).

## 样例 #1

### 输入

```
2 3
a
b

```

### 输出

```
First

```

## 样例 #2

### 输入

```
3 1
a
b
c

```

### 输出

```
First

```

## 样例 #3

### 输入

```
1 2
ab

```

### 输出

```
Second

```



---

---
title: "Nephren gives a riddle"
layout: "post"
diff: 普及+/提高
pid: CF896A
tag: ['字符串', '递归']
---

# Nephren gives a riddle

## 题目描述

奈芙莲有一个字符串数组 $f_{0\dots\infty}$。

$f_0$ 为 `What are you doing at the end of the world? Are you busy? Will you save us?`。

她想让更多人了解这个数组，所以她定义：

$$
\forall i\ge 1,f_i=\texttt{What are you doing while sending "}+f_{i-1}\\
+\texttt{"? Are you busy? Will you send "}+f_{i-1}+\texttt{"?}
$$

**注意其中的引号。**

奈芙莲会询问 $q$ 次，第 $i$ 次给定 $n,k$，你需要求出 $f_{n,k}$ 的值。**注意字符串从 $1$ 开始。**

## 输入格式

第一行一个正整数 $q$，表示询问的次数。

接下来 $q$ 行，每行两个整数 $n,k$。

## 输出格式

输出一行 $q$ 个字符。第 $i$ 个字符表示第 $i$ 组询问时 $f_{n,k}$ 的值。如果第 $i$ 组询问时 $\lvert f_n\rvert<k$，则第 $i$ 个字符输出 `.`。

## 说明/提示

对于所有数据，$1\le q\le 10,1\le n\le 10^5,1\le k\le 10^{18}$。

## 样例 #1

### 输入

```
3
1 1
1 2
1 111111111111

```

### 输出

```
Wh.
```

## 样例 #2

### 输入

```
5
0 69
1 194
1 139
0 47
1 66

```

### 输出

```
abdef
```

## 样例 #3

### 输入

```
10
4 1825
3 75
3 530
4 1829
4 1651
3 187
4 584
4 255
4 774
2 474

```

### 输出

```
Areyoubusy
```



---

