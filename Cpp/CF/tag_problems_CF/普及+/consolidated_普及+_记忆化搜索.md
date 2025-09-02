---
title: "Bag of mice"
layout: "post"
diff: 普及+/提高
pid: CF148D
tag: ['搜索', '记忆化搜索', '期望']
---

# Bag of mice

## 题目描述

The dragon and the princess are arguing about what to do on the New Year's Eve. The dragon suggests flying to the mountains to watch fairies dancing in the moonlight, while the princess thinks they should just go to bed early. They are desperate to come to an amicable agreement, so they decide to leave this up to chance.

They take turns drawing a mouse from a bag which initially contains $ w $ white and $ b $ black mice. The person who is the first to draw a white mouse wins. After each mouse drawn by the dragon the rest of mice in the bag panic, and one of them jumps out of the bag itself (the princess draws her mice carefully and doesn't scare other mice). Princess draws first. What is the probability of the princess winning?

If there are no more mice in the bag and nobody has drawn a white mouse, the dragon wins. Mice which jump out of the bag themselves are not considered to be drawn (do not define the winner). Once a mouse has left the bag, it never returns to it. Every mouse is drawn from the bag with the same probability as every other one, and every mouse jumps out of the bag with the same probability as every other one.

## 输入格式

The only line of input data contains two integers $ w $ and $ b $ ( $ 0<=w,b<=1000 $ ).

## 输出格式

Output the probability of the princess winning. The answer is considered to be correct if its absolute or relative error does not exceed $ 10^{-9} $ .

## 说明/提示

Let's go through the first sample. The probability of the princess drawing a white mouse on her first turn and winning right away is 1/4. The probability of the dragon drawing a black mouse and not winning on his first turn is 3/4 \* 2/3 = 1/2. After this there are two mice left in the bag — one black and one white; one of them jumps out, and the other is drawn by the princess on her second turn. If the princess' mouse is white, she wins (probability is 1/2 \* 1/2 = 1/4), otherwise nobody gets the white mouse, so according to the rule the dragon wins.

## 样例 #1

### 输入

```
1 3

```

### 输出

```
0.500000000

```

## 样例 #2

### 输入

```
5 5

```

### 输出

```
0.658730159

```



---

---
title: "Small Operations"
layout: "post"
diff: 普及+/提高
pid: CF2114F
tag: ['动态规划 DP', '搜索', '数学', '记忆化搜索', '最大公约数 gcd']
---

# Small Operations

## 题目描述

给你两个正整数 $x,k$。进行以下两种变换之一称为一次操作：
- 选择一个满足 $1 \le a \le k$ 的正整数 $a$，使 $x$ 变为 $x\cdot a$；
- 选择一个满足 $1 \le a \le k$ 的正整数 $a$，使 $x$ 变为 $\frac{x}{a}$，要求操作完后 $x$ 值是整数。

你需要找出使 $x$ 变为给定正整数 $y$ 的最小操作次数，或判断无解。

## 输入格式

第一行，一个正整数 $t\ (1 \le t \le {10}^4)$，表示测试数据组数。

对于每组测试数据，一行三个正整数 $x,y,k\ (1 \le x,y,k \le {10}^6)$。

保证所有测试数据中 $x$ 的总和与 $y$ 的总和均不超过 ${10}^8$。

## 输出格式

对于每组测试数据，如果无解输出 $-1$，否则输出使 $x$ 变为 $y$ 的最小操作次数。

## 说明/提示

对于第一组测试数据，我们可以选择 $a=2$，将 $x$ 除以 $2$，然后选择 $a=3$，将 $x$ 乘上 $3$，此时 $x$ 将变为 $6$，等于 $y$。

对于第二组测试数据，可以证明其不可能。

对于第七组测试数据，我们可以分别选择 $a=7,9,10,10,12,13$，连续做 $6$ 次乘法。可以证明没有比这更少的操作次数了。

## 样例 #1

### 输入

```
8
4 6 3
4 5 3
4 6 2
10 45 3
780 23 42
11 270 23
1 982800 13
1 6 2
```

### 输出

```
2
-1
-1
3
3
3
6
-1
```



---

---
title: "Sweets Game"
layout: "post"
diff: 普及+/提高
pid: CF63E
tag: ['动态规划 DP', '搜索', '博弈论', '记忆化搜索']
---

# Sweets Game

## 题目描述

Karlsson has visited Lillebror again. They found a box of chocolates and a big whipped cream cake at Lillebror's place. Karlsson immediately suggested to divide the sweets fairly between Lillebror and himself. Specifically, to play together a game he has just invented with the chocolates. The winner will get the cake as a reward.

The box of chocolates has the form of a hexagon. It contains 19 cells for the chocolates, some of which contain a chocolate. The players move in turns. During one move it is allowed to eat one or several chocolates that lay in the neighboring cells on one line, parallel to one of the box's sides. The picture below shows the examples of allowed moves and of an unacceptable one. The player who cannot make a move loses.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF63E/d39dc87a25b4bbc8e9ef90055ec2e2d8c38df358.png)Karlsson makes the first move as he is Lillebror's guest and not vice versa. The players play optimally. Determine who will get the cake.

## 输入格式

The input data contains 5 lines, containing 19 words consisting of one symbol. The word "O" means that the cell contains a chocolate and a "." stands for an empty cell. It is guaranteed that the box contains at least one chocolate. See the examples for better understanding.

## 输出格式

If Karlsson gets the cake, print "Karlsson" (without the quotes), otherwise print "Lillebror" (yet again without the quotes).

## 样例 #1

### 输入

```
  . . .
 . . O .
. . O O .
 . . . .
  . . .

```

### 输出

```
Lillebror
```

## 样例 #2

### 输入

```
  . . .
 . . . O
. . . O .
 O . O .
  . O .

```

### 输出

```
Karlsson
```



---

