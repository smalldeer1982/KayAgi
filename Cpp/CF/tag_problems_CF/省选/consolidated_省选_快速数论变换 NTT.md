---
title: "Lucky Tickets"
layout: "post"
diff: 省选/NOI-
pid: CF1096G
tag: ['组合数学', '快速数论变换 NTT']
---

# Lucky Tickets

## 题目描述

All bus tickets in Berland have their numbers. A number consists of $ n $ digits ( $ n $ is even). Only $ k $ decimal digits $ d_1, d_2, \dots, d_k $ can be used to form ticket numbers. If $ 0 $ is among these digits, then numbers may have leading zeroes. For example, if $ n = 4 $ and only digits $ 0 $ and $ 4 $ can be used, then $ 0000 $ , $ 4004 $ , $ 4440 $ are valid ticket numbers, and $ 0002 $ , $ 00 $ , $ 44443 $ are not.

A ticket is lucky if the sum of first $ n / 2 $ digits is equal to the sum of remaining $ n / 2 $ digits.

Calculate the number of different lucky tickets in Berland. Since the answer may be big, print it modulo $ 998244353 $ .

## 输入格式

The first line contains two integers $ n $ and $ k $ $ (2 \le n \le 2 \cdot 10^5, 1 \le k \le 10) $ — the number of digits in each ticket number, and the number of different decimal digits that may be used. $ n $ is even.

The second line contains a sequence of pairwise distinct integers $ d_1, d_2, \dots, d_k $ $ (0 \le d_i \le 9) $ — the digits that may be used in ticket numbers. The digits are given in arbitrary order.

## 输出格式

Print the number of lucky ticket numbers, taken modulo $ 998244353 $ .

## 说明/提示

In the first example there are $ 6 $ lucky ticket numbers: $ 1111 $ , $ 1818 $ , $ 1881 $ , $ 8118 $ , $ 8181 $ and $ 8888 $ .

There is only one ticket number in the second example, it consists of $ 20 $ digits $ 6 $ . This ticket number is lucky, so the answer is $ 1 $ .

## 样例 #1

### 输入

```
4 2
1 8

```

### 输出

```
6

```

## 样例 #2

### 输入

```
20 1
6

```

### 输出

```
1

```

## 样例 #3

### 输入

```
10 5
6 1 4 0 3

```

### 输出

```
569725

```

## 样例 #4

### 输入

```
1000 7
5 4 0 1 8 3 2

```

### 输出

```
460571165

```



---

---
title: "Red-White Fence"
layout: "post"
diff: 省选/NOI-
pid: CF1251F
tag: ['数学', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---

# Red-White Fence

## 题目描述

Polycarp想在他家附近建一道栅栏。他有$n$个白板和$k$个红板去建造它。每一块板都有一个整数长度。

一个好的栅栏应由一块红板和几块（可能是零块）白板组成。红色的板应该在这道栅栏中是**最长的**，而且红板前的板子长度应为递增，而红板之后的板子长度为递减。如果用了$m$块板子，它们的长度从左到右依次是$l_1,l_2,…,l_m$，那么应该符合以下条件

①栅栏上应**有且只有一块**红板，设其序号为$j$

②对于所有的$i∈[1,j-1]$有$l_i<l_{i+1}$

③对于所有的$i∈[j,m-1]$有$l_i>l_{i+1}$

在Polycarp建造他的栅栏时，他会从左向右在$0$高度上放置所有板，没有间隙，所以这些板将会组成一个多边形

例图：一个栅栏的板长数组为$[1,2,3,4,5]$，第二个板是红板。栅栏的周长是$20$。Polycrp对一些特殊周长的栅栏感兴趣。他有喜欢的$q$个偶整数$[Q_1,Q_2,…,Q_q]$，对于每个这样的整数$Q_i$，他想计算有几种不同的周长是$Q_i$的篱笆可以被造出来（如果两个篱笆的板长排列不同，那么就认为这两个篱笆是不同的）你可以帮他计算这些数值吗？

## 输入格式

输入第一行是两个正整数$n,k(1≤n≤3*10^5,1≤k≤5)$，表示Polycarp拥有的白板和红板的数量

第二行有$n$个正整数$[a_1,a_2,...,a_n](1≤a_i≤3*10^5)$，表示Polycarp拥有的$n$块白板的长度

第三行有$k$个正整数$[b_1,b_2,...,b_k](1≤b_i≤3*10^5)$，表示Polycarp拥有的$k$块红板的长度，所有$b_i$都是不相同的

第四行是一个正整数$q(1≤q≤3*10^5)$，表示特殊周长的数量

第五行有$q$个正整数$[Q_1,Q_2,...,Q_q](4≤Q_i≤12*10^5)$，每个$Q_i$都是偶数，表示Polycarp喜欢的特殊整数（即特殊周长）

## 输出格式

对于每个$Q_i$，输出一个整数，表示有多少种符合约束条件的周长为$Q_i$的栅栏，由于数量可能很大，结果请对$998244353$取模，每个输出占一行

## 说明/提示

对于第一个样例，可能的长度序列有（红板加粗）

·周长为$6$：$[$**2**$]$

·周长为$8$：$[1,$ **2**$]$,$[$**2**$,1]$

·周长为$10$：$[1,$ **2**$,1]$,$[$**4**$]$

·周长为$12$：$[1,$ **4**$]$,$[3,$ **4**$]$,$[$**4**$,1]$,$[$**4**$,3]$

·周长为$14$：$[1,$ **4**$,1]$,$[1,$ **4**$,3]$,$[3,$ **4**$,1]$,$[3,$ **4**$,3]$,$[1,3,$ **4**$]$,$[$**4**$,3,1]$

·周长为$16$：$[1,$ **4**$,3,1]$,$[3,$ **4**$,3,1]$,$[1,3,$ **4**$,1]$,$[1,3,$ **4**$,3]$

·周长为$18$：$[1,3,$ **4**$,3,1]$

## 样例 #1

### 输入

```
5 2
3 3 1 1 1
2 4
7
6 8 10 12 14 16 18

```

### 输出

```
1
2
2
4
6
4
1

```

## 样例 #2

### 输入

```
5 5
1 2 3 4 5
1 2 3 4 5
4
4 8 10 14

```

### 输出

```
1
3
5
20

```



---

---
title: "Wooden Spoon"
layout: "post"
diff: 省选/NOI-
pid: CF1784D
tag: ['数学', '组合数学', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---

# Wooden Spoon

## 题目描述

$ 2^n $ people, numbered with distinct integers from $ 1 $ to $ 2^n $ , are playing in a single elimination tournament. The bracket of the tournament is a full binary tree of height $ n $ with $ 2^n $ leaves.

When two players meet each other in a match, a player with the smaller number always wins. The winner of the tournament is the player who wins all $ n $ their matches.

A virtual consolation prize "Wooden Spoon" is awarded to a player who satisfies the following $ n $ conditions:

- they lost their first match;
- the player who beat them lost their second match;
- the player who beat that player lost their third match;
- $ \ldots $ ;
- the player who beat the player from the previous condition lost the final match of the tournament.

It can be shown that there is always exactly one player who satisfies these conditions.

Consider all possible $ (2^n)! $ arrangements of players into the tournament bracket. For each player, find the number of these arrangements in which they will be awarded the "Wooden Spoon", and print these numbers modulo $ 998\,244\,353 $ .

## 输入格式

The only line contains a single integer $ n $ ( $ 1 \le n \le 20 $ ) — the size of the tournament.

There are $ 20 $ tests in the problem: in the first test, $ n = 1 $ ; in the second test, $ n = 2 $ ; $ \ldots $ ; in the $ 20 $ -th test, $ n = 20 $ .

## 输出格式

Print $ 2^n $ integers — the number of arrangements in which the "Wooden Spoon" is awarded to players $ 1, 2, \ldots, 2^n $ , modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, the "Wooden Spoon" is always awarded to player $ 2 $ .

In the second example, there are $ 8 $ arrangements where players $ 1 $ and $ 4 $ meet each other in the first match, and in these cases, the "Wooden Spoon" is awarded to player $ 3 $ . In the remaining $ 16 $ arrangements, the "Wooden Spoon" is awarded to player $ 4 $ .

## 样例 #1

### 输入

```
1
```

### 输出

```
0
2
```

## 样例 #2

### 输入

```
2
```

### 输出

```
0
0
8
16
```

## 样例 #3

### 输入

```
3
```

### 输出

```
0
0
0
1536
4224
7680
11520
15360
```



---

---
title: "Alternative Platforms"
layout: "post"
diff: 省选/NOI-
pid: CF2038F
tag: ['数学', '快速数论变换 NTT']
---

# Alternative Platforms

## 题目描述

Suppose you are working in the Ministry of Digital Development of Berland, and your task is to monitor the industry of video blogging.

There are $ n $ bloggers in Berland. Recently, due to the poor state of the main video platform in Berland, two alternative platforms were introduced. That's why bloggers started to reupload their videos to these alternative platforms. You've got the statistics that the $ i $ -th blogger uploaded $ v_i $ videos to the first alternative platform and $ r_i $ videos to the second alternative platform.

You think that a potential user will be upset if even at least one of his favorite bloggers doesn't upload anything. However, if a blogger uploads videos to both platforms, the user will watch that blogger on the platform where more videos are available. So, you've come up with the following function to estimate user experience. Suppose a user watches $ k $ bloggers $ b_1, b_2, \dots, b_k $ ; then, let user experience be  $E(b_1, \dots, b_k) = \max\left(\min_{i=1..k}{v[b_i]}, \min_{i=1..k}{r[b_i]}\right).$ 

In order to get some statistics, you want to calculate the value  $ \mathit{avg}\_k $  that is equal to an average experience among all subsets of bloggers of size  $ k $ . Also, you have to calculate  $ \mathit{avg}\_k $  for each  $ k $  from  $ 1 $  to  $ n $. 

Since answers may be too large, print them modulo  $ 998\,244\,353$.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of bloggers.

The second line contains $ n $ integers $ v_1, v_2, \dots, v_n $ ( $ 0 \le v_i \le 10^6 $ ), where $ v_i $ is the number of videos of the $ i $ -th blogger on the first alternative platform.

The third line contains $ n $ integers $ r_1, r_2, \dots, r_n $ ( $ 0 \le r_i \le 10^6 $ ), where $ r_i $ is the number of videos of the $ i $ -th blogger on the second alternative platform.

## 输出格式

Print $ n $ integers $ \mathit{avg}_1, \mathit{avg}_2, \dots, \mathit{avg}_n $ .

It can be proven that $ \mathit{avg}_k $ may be represented as an irreducible fraction $ \dfrac{x}{y} $ where $ y \not\equiv 0 \pmod{998\,244\,353} $ . So, print $ \mathit{avg}_k $ in a form $ x \cdot y^{-1} \bmod 998\,244\,353 $ .

## 说明/提示

In the first example, $ 332748119 $ is $ \frac{4}{3} $ . In the third example, $ 199648873 $ is $ \frac{12}{5} $ .

## 样例 #1

### 输入

```
3
2 1 2
1 2 1
```

### 输出

```
2 332748119 1
```

## 样例 #2

### 输入

```
4
5 5 5 5
0 0 0 0
```

### 输出

```
5 5 5 5
```

## 样例 #3

### 输入

```
5
1 9 3 7 5
2 4 6 8 5
```

### 输出

```
6 4 3 199648873 2
```



---

