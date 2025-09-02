---
title: "Tree with Small Distances"
layout: "post"
diff: 普及+/提高
pid: CF1029E
tag: ['动态规划 DP', '贪心']
---

# Tree with Small Distances

## 题目描述

给定一颗有根树（根节点为 $1$）。要求往树中加入一些边使得从根节点到其他节点的距离至多是 $2$。 求加入边的最小数量。(边全部都是无向的)

## 输入格式

第一行一个整数 $n$，表示树中的节点个数。 接下来 $n−1$ 行，每行两个整数 $x,y$，表示 $x,y$ 之间有一条连边。

## 输出格式

一个整数，表示加入边的最小数量。

## 说明/提示

$2 \le n \le 2\times 10^5$

## 样例 #1

### 输入

```
7
1 2
2 3
2 4
4 5
4 6
5 7

```

### 输出

```
2

```

## 样例 #2

### 输入

```
7
1 2
1 3
2 4
2 5
3 6
1 7

```

### 输出

```
0

```

## 样例 #3

### 输入

```
7
1 2
2 3
3 4
3 5
3 6
3 7

```

### 输出

```
1

```



---

---
title: "Changing Array"
layout: "post"
diff: 普及+/提高
pid: CF1054D
tag: ['贪心', '前缀和', '位运算']
---

# Changing Array

## 题目描述

At a break Vanya came to the class and saw an array of $ n $ $ k $ -bit integers $ a_1, a_2, \ldots, a_n $ on the board. An integer $ x $ is called a $ k $ -bit integer if $ 0 \leq x \leq 2^k - 1 $ .

Of course, Vanya was not able to resist and started changing the numbers written on the board. To ensure that no one will note anything, Vanya allowed himself to make only one type of changes: choose an index of the array $ i $ ( $ 1 \leq i \leq n $ ) and replace the number $ a_i $ with the number $ \overline{a_i} $ . We define $ \overline{x} $ for a $ k $ -bit integer $ x $ as the $ k $ -bit integer such that all its $ k $ bits differ from the corresponding bits of $ x $ .

Vanya does not like the number $ 0 $ . Therefore, he likes such segments $ [l, r] $ ( $ 1 \leq l \leq r \leq n $ ) such that $ a_l \oplus a_{l+1} \oplus \ldots \oplus a_r \neq 0 $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). Determine the maximum number of segments he likes Vanya can get applying zero or more operations described above.

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1 \leq n \leq 200\,000 $ , $ 1 \leq k \leq 30 $ ).

The next line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i \leq 2^k - 1 $ ), separated by spaces — the array of $ k $ -bit integers.

## 输出格式

Print one integer — the maximum possible number of segments with XOR not equal to $ 0 $ that can be obtained by making several (possibly $ 0 $ ) operations described in the statement.

## 说明/提示

In the first example if Vasya does not perform any operations, he gets an array that has $ 5 $ segments that Vanya likes. If he performs the operation with $ i = 2 $ , he gets an array $ [1, 0, 0] $ , because $ \overline{3} = 0 $ when $ k = 2 $ . This array has $ 3 $ segments that Vanya likes. Also, to get an array with $ 5 $ segments that Vanya likes, he can perform two operations with $ i = 3 $ and with $ i = 2 $ . He then gets an array $ [1, 0, 3] $ . It can be proven that he can't obtain $ 6 $ or more segments that he likes.

In the second example, to get $ 19 $ segments that Vanya likes, he can perform $ 4 $ operations with $ i = 3 $ , $ i = 4 $ , $ i = 5 $ , $ i = 6 $ and get an array $ [1, 4, 3, 0, 4, 3] $ .

## 样例 #1

### 输入

```
3 2
1 3 0

```

### 输出

```
5
```

## 样例 #2

### 输入

```
6 3
1 4 4 7 3 4

```

### 输出

```
19
```



---

---
title: "Make It Equal"
layout: "post"
diff: 普及+/提高
pid: CF1065C
tag: ['模拟', '贪心', '树状数组']
---

# Make It Equal

## 题目描述

There is a toy building consisting of $ n $ towers. Each tower consists of several cubes standing on each other. The $ i $ -th tower consists of $ h_i $ cubes, so it has height $ h_i $ .

Let's define operation slice on some height $ H $ as following: for each tower $ i $ , if its height is greater than $ H $ , then remove some top cubes to make tower's height equal to $ H $ . Cost of one "slice" equals to the total number of removed cubes from all towers.

Let's name slice as good one if its cost is lower or equal to $ k $ ( $ k \ge n $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1065C/658a593f32bf5073d4f1a1a7bd7987feaeb4f838.png)Calculate the minimum number of good slices you have to do to make all towers have the same height. Of course, it is always possible to make it so.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ n \le k \le 10^9 $ ) — the number of towers and the restriction on slices, respectively.

The second line contains $ n $ space separated integers $ h_1, h_2, \dots, h_n $ ( $ 1 \le h_i \le 2 \cdot 10^5 $ ) — the initial heights of towers.

## 输出格式

Print one integer — the minimum number of good slices you have to do to make all towers have the same heigth.

## 说明/提示

In the first example it's optimal to make $ 2 $ slices. The first slice is on height $ 2 $ (its cost is $ 3 $ ), and the second one is on height $ 1 $ (its cost is $ 4 $ ).

## 样例 #1

### 输入

```
5 5
3 1 2 2 4

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 5
2 3 4 5

```

### 输出

```
2

```



---

---
title: "Heaters"
layout: "post"
diff: 普及+/提高
pid: CF1066B
tag: ['贪心']
---

# Heaters

## 题目描述

## 题意描述：
$Vova$先生的家可以看作一个$n \times 1$的矩形，寒冷的冬天来了，$Vova$先生想让他的家里变得暖和起来。现在我们给你$Vova$先生家的平面图，其中$1$表示这个地方是加热炉，0表示这个地方什么也没有。所有加热器都有一个加热半径$r$,一个位于$a_i$加热器可以加热[$a_i-r+1,a_i+r-1$]的范围。现在，$Vova$先生想让他的整个家都变得暖和，一开始所有的加热器都是关闭的，请你求出$Vova$先生最少要开几个加热器才能使整个家变得暖和

## 输入格式

第一行:两个整数$n,r(1≤n,r≤1000)$,含义如上

第二行，n个整数，表示$Vova$家的地图

## 输出格式

一个整数，表示$Vova$先生至少要打开几个加热器

## 样例 #1

### 输入

```
6 2
0 1 1 0 0 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5 3
1 0 0 0 1

```

### 输出

```
2

```

## 样例 #3

### 输入

```
5 10
0 0 0 0 0

```

### 输出

```
-1

```

## 样例 #4

### 输入

```
10 3
0 0 1 1 0 1 0 0 0 1

```

### 输出

```
3

```



---

---
title: "Lawnmower"
layout: "post"
diff: 普及+/提高
pid: CF115B
tag: ['贪心']
---

# Lawnmower

## 题目描述

你有一个完全由草和杂草组成的花园。你的花园是一个 n×m的网格。每个方格有一对坐标（r，c）表示单元格位于r行c列。每个方格可能有草或杂草。例如，一个4×5的花园可能如下（空单元格表示草）：
![](https://cdn.luogu.org/upload/vjudge_pic/CF115B/593291ddc8205e086d1d9f0caee6daf221cd4d06.png)

你有一台割草机可以割除所有的杂草。最初，你站在花园的左上角。也就是说，在方格（1,1）处。在任何时刻，你都面临着某个方向——左或右。最初，你面对右。

在一个步骤中，您可以执行以下任一操作：

1. 沿您面向的方向移动一个单元格。

- 如果你面向右：从方格（r，c ）移动到方格（r，c + 1 ） 
![](https://cdn.luogu.org/upload/vjudge_pic/CF115B/f511b6ec3d5ee7e9c4711b72b12f3f163a26b1cb.png)

- 如果你面向左：从方格（r，c ）移动到方格（r，c - 1 ） 
![](https://cdn.luogu.org/upload/vjudge_pic/CF115B/817d99d95ad6751bb75b016614c67edbc38bc05f.png)

2) 向下移动一格（即从（r，c ）移动到方格（r + 1，c ）中），并将你的方向改为相反的方向.
- 如果你面向右，你将面向左
![](https://cdn.luogu.org/upload/vjudge_pic/CF115B/eaac793c8ad146f5aa886c6e03e5682029ae2d0f.png)

- 如果你面向左，你将面对右
![](https://cdn.luogu.org/upload/vjudge_pic/CF115B/0279ba704667c612234f39ddc6d6e73ff67745d6.png)

您不得离开花园。如果你和你的割草机站在含有杂草的方格中（你的方向无关紧要），杂草就会被修剪掉。此操作不算作动作。

割除所有杂草所需的最小移动次数是多少？

------------

## 输入格式

第一行包含两个整数n和m（1<=N，M<=150）—— 分别为行数和列数。接下来n行包含每行m个字符——方格（r，c）的内容。“G”表示该方格含有草。“W”表示该方格含有杂草。

保证网格的左上角将包含草。

## 输出格式

输出一个数字——割除所有杂草所需的最小移动次数。

## 样例 #1

### 输入

```
4 5
GWGGW
GGWGG
GWGGG
WGGGG

```

### 输出

```
11

```

## 样例 #2

### 输入

```
3 3
GWW
WWW
WWG

```

### 输出

```
7

```

## 样例 #3

### 输入

```
1 1
G

```

### 输出

```
0

```



---

---
title: "Microtransactions (easy version)"
layout: "post"
diff: 普及+/提高
pid: CF1165F1
tag: ['贪心']
---

# Microtransactions (easy version)

## 题目描述

有 $n$ 种物品，对于第 $i$ $(1\le i \le n)$ 个物品，你需要买 $k_i$ 个（你每次购物是在**晚上**），每个物品在非打折日买是 $2$ 块钱，在打折日买是 $1$ 块钱，每天**早上**你可以赚 $1$ 块钱，一共有 $m$ 个打折日，在第 $d_i$ 天第 $t_i$ 种物品打折，问最少需要多少天可以买完你需要的物品。注意，你每天可以买任意多数量以及种类的商品（只要你有足够的余额）。

## 输入格式

第一行包含两个整数 $n$ 和 $m$ $(1\le n,m \le 1000)$ 中的商品类型数和打折的天数。

输入的第二行包含 $n$ 个整数 $k_i$，其中 $k_i$ 是第 $i$ 类需要的个数。$(0 \le \sum k_i \le 1000)$。

接下来的 $m$ 行，每行两个数 $(d_i,t_i$) $(1 \le d_i \le 1000, 1 \le t_i \le n)$，表示第 $t_i$ 个商品在 $d_i$ 天打特价。

## 输出格式

一个整数，表示最早在哪一天能买完所有需要的商品。

## 样例 #1

### 输入

```
5 6
1 2 0 2 0
2 4
3 3
1 5
1 2
1 5
2 3

```

### 输出

```
8

```

## 样例 #2

### 输入

```
5 3
4 2 1 3 2
3 5
4 2
2 5

```

### 输出

```
20

```



---

---
title: "Microtransactions (hard version)"
layout: "post"
diff: 普及+/提高
pid: CF1165F2
tag: ['贪心', '二分']
---

# Microtransactions (hard version)

## 题目描述

有 $n$ 种物品，对于第 $i$ $(1\le i \le n)$ 个物品，你需要买 $k_i$ 个（你每次购物是在**晚上**），每个物品在非打折日买是 $2$ 块钱，在打折日买是 $1$ 块钱，每天**早上**你可以赚 $1$ 块钱，一共有 $m$ 个打折日，在第 $d_i$ 天第 $t_i$ 种物品打折，问最少需要多少天可以买完你需要的物品。注意，你每天可以买任意多数量以及种类的商品（只要你有足够的余额）。

## 输入格式

第一行包含两个整数 $n$ 和 $m$ $(1\le n,m \le 2\times 10^5)$ 中的商品类型数和打折的天数。

输入的第二行包含 $n$ 个整数 $k_i$，其中 $k_i$ 是第 $i$ 类需要的个数。$(0 \le \sum k_i \le 2\times 10^5)$。

接下来的 $m$ 行，每行两个数 $(d_i,t_i$) $(1 \le d_i \le 2\times 10^5, 1 \le t_i \le n)$，表示第 $t_i$ 个商品在 $d_i$ 天打特价。

## 输出格式

一个整数，表示最早在哪一天能买完所有需要的商品。

## 样例 #1

### 输入

```
5 6
1 2 0 2 0
2 4
3 3
1 5
1 2
1 5
2 3

```

### 输出

```
8

```

## 样例 #2

### 输入

```
5 3
4 2 1 3 2
3 5
4 2
2 5

```

### 输出

```
20

```



---

---
title: "Nick and Array"
layout: "post"
diff: 普及+/提高
pid: CF1180B
tag: ['数学', '贪心']
---

# Nick and Array

## 题目描述

Nick had received an awesome array of integers $ a=[a_1, a_2, \dots, a_n] $ as a gift for his $ 5 $ birthday from his mother. He was already going to explore its various properties but after unpacking he was disappointed a lot because the product $ a_1 \cdot a_2 \cdot \dots a_n $ of its elements seemed to him not large enough.

He was ready to throw out the array, but his mother reassured him. She told him, that array would not be spoiled after the following operation: choose any index $ i $ ( $ 1 \le i \le n $ ) and do $ a_i := -a_i - 1 $ .

For example, he can change array $ [3, -1, -4, 1] $ to an array $ [-4, -1, 3, 1] $ after applying this operation to elements with indices $ i=1 $ and $ i=3 $ .

Kolya had immediately understood that sometimes it's possible to increase the product of integers of the array a lot. Now he has decided that he wants to get an array with the maximal possible product of integers using only this operation with its elements (possibly zero, one or more times, as many as he wants), it is not forbidden to do this operation several times for the same index.

Help Kolya and print the array with the maximal possible product of elements $ a_1 \cdot a_2 \cdot \dots a_n $ which can be received using only this operation in some order.

If there are multiple answers, print any of them.

## 输入格式

The first line contains integer $ n $ ( $ 1 \leq n \leq 10^{5} $ ) — number of integers in the array.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -10^{6} \leq a_i \leq 10^{6} $ ) — elements of the array

## 输出格式

Print $ n $ numbers — elements of the array with the maximal possible product of elements which can be received using only this operation in some order from the given array.

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
4
2 2 2 2

```

### 输出

```
-3 -3 -3 -3 
```

## 样例 #2

### 输入

```
1
0

```

### 输出

```
0 
```

## 样例 #3

### 输入

```
3
-3 -3 2

```

### 输出

```
-3 -3 2 
```



---

---
title: "The Parade"
layout: "post"
diff: 普及+/提高
pid: CF1250J
tag: ['贪心', '二分']
---

# The Parade

## 题目描述

**题意简述**

柏林军队正在准备一场大规模的阅兵式。参加的士兵将被分成人数相等的$k$行。

当然，排兵布阵是需要一定的规则的：同一排士兵的身高相差不应超过$1$且每个士兵的身高是$1$到$n$之间的整数。

已知每名士兵身高的你必须将所有参加阅兵的士兵排成$k$排，以满足上述条件。请你编写程序计算可以参加游行的士兵的最大数量。

## 输入格式

本题**有多组数据**。

第一行包含一个整数$t(1\le t\le 10000)$，表示数据组数。

每组数据都有两行。第一行包含两个整数$n$和$k$（$1≤n≤30000$，$1≤k≤10^{12}$）分别表示不同高度的士兵数量和士兵排数。

第二行包含$n$个整数$c_1,c_2,$ … $,c_n$（$0\le c_i\le 10^{12}$），其中$c_i$表示身高为$i$的士兵人数。

## 输出格式

输出每组数据中可以参加游行的士兵的最大数量。（每两个答案中间有一个换行）

## 说明/提示

第一组数据，士兵可以站成这样：$[3,3,3,3],[1,2,1,1],[1,1,1,1],[3,3,3,3]$（每个方括号表示一行）；

第二组数据，所有士兵可以全部站成一排；

第三组数据，士兵可以站成$3$排，每排$33$人；

第四组数据，所有士兵可以全部站成一排；

第五组数据，所有身高为$2$和$3$的可以站成一排。

## 样例 #1

### 输入

```
5
3 4
7 1 13
1 1
100
1 3
100
2 1
1000000000000 1000000000000
4 1
10 2 11 1

```

### 输出

```
16
100
99
2000000000000
13

```



---

---
title: "Fight with Monsters"
layout: "post"
diff: 普及+/提高
pid: CF1296D
tag: ['贪心']
---

# Fight with Monsters

## 题目描述

There are $ n $ monsters standing in a row numbered from $ 1 $ to $ n $ . The $ i $ -th monster has $ h_i $ health points (hp). You have your attack power equal to $ a $ hp and your opponent has his attack power equal to $ b $ hp.

You and your opponent are fighting these monsters. Firstly, you and your opponent go to the first monster and fight it till his death, then you and your opponent go the second monster and fight it till his death, and so on. A monster is considered dead if its hp is less than or equal to $ 0 $ .

The fight with a monster happens in turns.

1. You hit the monster by $ a $ hp. If it is dead after your hit, you gain one point and you both proceed to the next monster.
2. Your opponent hits the monster by $ b $ hp. If it is dead after his hit, nobody gains a point and you both proceed to the next monster.

You have some secret technique to force your opponent to skip his turn. You can use this technique at most $ k $ times in total (for example, if there are two monsters and $ k=4 $ , then you can use the technique $ 2 $ times on the first monster and $ 1 $ time on the second monster, but not $ 2 $ times on the first monster and $ 3 $ times on the second monster).

Your task is to determine the maximum number of points you can gain if you use the secret technique optimally.

## 输入格式

The first line of the input contains four integers $ n, a, b $ and $ k $ ( $ 1 \le n \le 2 \cdot 10^5, 1 \le a, b, k \le 10^9 $ ) — the number of monsters, your attack power, the opponent's attack power and the number of times you can use the secret technique.

The second line of the input contains $ n $ integers $ h_1, h_2, \dots, h_n $ ( $ 1 \le h_i \le 10^9 $ ), where $ h_i $ is the health points of the $ i $ -th monster.

## 输出格式

Print one integer — the maximum number of points you can gain if you use the secret technique optimally.

## 样例 #1

### 输入

```
6 2 3 3
7 10 50 12 1 8
```

### 输出

```
5
```

## 样例 #2

### 输入

```
1 1 100 99
100
```

### 输出

```
1
```

## 样例 #3

### 输入

```
7 4 2 1
1 3 5 4 2 7 6
```

### 输出

```
6
```



---

---
title: "Excitation of Atoms"
layout: "post"
diff: 普及+/提高
pid: CF1425E
tag: ['贪心']
---

# Excitation of Atoms

## 题目描述

Mr. Chanek is currently participating in a science fair that is popular in town. He finds an exciting puzzle in the fair and wants to solve it.

There are $ N $ atoms numbered from $ 1 $ to $ N $ . These atoms are especially quirky. Initially, each atom is in normal state. Each atom can be in an excited. Exciting atom $ i $ requires $ D_i $ energy. When atom $ i $ is excited, it will give $ A_i $ energy. You can excite any number of atoms (including zero).

These atoms also form a peculiar one-way bond. For each $ i $ , $ (1 \le i < N) $ , if atom $ i $ is excited, atom $ E_i $ will also be excited at no cost. Initially, $ E_i $ = $ i+1 $ . Note that atom $ N $ cannot form a bond to any atom.

Mr. Chanek must change exactly $ K $ bonds. Exactly $ K $ times, Mr. Chanek chooses an atom $ i $ , $ (1 \le i < N) $ and changes $ E_i $ to a different value other than $ i $ and the current $ E_i $ . Note that an atom's bond can remain unchanged or changed more than once. Help Mr. Chanek determine the maximum energy that he can achieve!

note: You must first change exactly $ K $ bonds before you can start exciting atoms.

## 输入格式

The first line contains two integers $ N $ $ K $ $ (4 \le N \le 10^5, 0 \le K < N) $ , the number of atoms, and the number of bonds that must be changed.

The second line contains $ N $ integers $ A_i $ $ (1 \le A_i \le 10^6) $ , which denotes the energy given by atom $ i $ when on excited state.

The third line contains $ N $ integers $ D_i $ $ (1 \le D_i \le 10^6) $ , which denotes the energy needed to excite atom $ i $ .

## 输出格式

A line with an integer that denotes the maximum number of energy that Mr. Chanek can get.

## 说明/提示

An optimal solution to change $ E_5 $ to 1 and then excite atom 5 with energy 1. It will cause atoms 1, 2, 3, 4, 5 be excited. The total energy gained by Mr. Chanek is (5 + 6 + 7 + 8 + 10) - 1 = 35.

Another possible way is to change $ E_3 $ to 1 and then exciting atom 3 (which will excite atom 1, 2, 3) and exciting atom 4 (which will excite atom 4, 5, 6). The total energy gained by Mr. Chanek is (5 + 6 + 7 + 8 + 10 + 2) - (6 + 7) = 25 which is not optimal.

## 样例 #1

### 输入

```
6 1
5 6 7 8 10 2
3 5 6 7 1 10
```

### 输出

```
35
```



---

---
title: "Maximize the Remaining String"
layout: "post"
diff: 普及+/提高
pid: CF1506G
tag: ['贪心', '单调队列']
---

# Maximize the Remaining String

## 题目描述

给你一个由小写英文字母组成的字符串 $s$，你需要去掉一部分字符，使得操作后得到的字符串 $t$ 满足在 $s$ 中出现的字母每种只保留一个并且最大化 $t$ 的字典序。

## 输入格式

多测
第一行一个正整数 $T$（$1\le T\le 10^4$）表示数据组数。  
接下来 $T$ 行，每行一个由小写字母组成的字符串 $s$（$\sum|s|\le 2\times 10^5$）。

## 输出格式

输出 $T$ 行  
对于每组输入的 $s$，输出一行一个字符串表示满足要求且字典序最大的 $t$。

## 样例 #1

### 输入

```
6
codeforces
aezakmi
abacaba
convexhull
swflldjgpaxs
myneeocktxpqjpz
```

### 输出

```
odfrces
ezakmi
cba
convexhul
wfldjgpaxs
myneocktxqjpz
```



---

---
title: "Gardener and Tree"
layout: "post"
diff: 普及+/提高
pid: CF1593E
tag: ['贪心', '树形数据结构']
---

# Gardener and Tree

## 题目描述

一棵 $n$ 个结点的树。一个人做了多次操作，在每次操作中，他删除了树的所有叶结点。叶结点指的是树中至多有一个相邻节点的结点。

![](http://61.186.173.89:2019/2021/10/15/c4f2d0e1827d5.png)

如上图中所示的树。下图显示了对树进行一次操作后的结果。
![](http://61.186.173.89:2019/2021/10/15/14602247d6f15.png)

注意特殊操作的情况:

1、对空树($0$ 个顶点)进行操作时不会改变它;

2、对于仅有一个顶点的树进行操作时会移除这个顶点(这个顶点被当作一个叶子);

3、对于仅有两个顶点的树进行操作时将删除两个顶点(两个顶点都被当作叶子处理)。

求 $k$ 次操作后还剩下多少个顶点?

## 输入格式

第一行包含一个整数 $T$。然后是 $T$ 组测试数据。

对于每组测试数据，共 $n$ 行：第一行包含两个整数 $n$和 $k$——树中的顶点数和操作次数。然后是 $n−1$ 行，每一行包含两个整数 $u$ 和 $v$ ($1\le u,v≤n，u \ne v$)，表示一条无向边。保证是一个树，且每两组测试数据中间有一个换行。

## 输出格式

共 $T$ 行，每行一个正整数 $ans$，表示每组数据的答案。

## 样例 #1

### 输入

```
6

14 1
1 2
2 3
2 4
4 5
4 6
2 7
7 8
8 9
8 10
3 11
3 12
1 13
13 14

2 200000
1 2

3 2
1 2
2 3

5 1
5 1
3 2
2 1
5 4

6 2
5 1
2 5
5 6
4 2
3 4

7 1
4 3
5 1
1 3
6 1
1 7
2 1
```

### 输出

```
7
0
0
3
1
2
```



---

---
title: "Progressions Covering"
layout: "post"
diff: 普及+/提高
pid: CF1661D
tag: ['贪心', '枚举']
---

# Progressions Covering

## 题目描述

You are given two arrays: an array $ a $ consisting of $ n $ zeros and an array $ b $ consisting of $ n $ integers.

You can apply the following operation to the array $ a $ an arbitrary number of times: choose some subsegment of $ a $ of length $ k $ and add the arithmetic progression $ 1, 2, \ldots, k $ to this subsegment — i. e. add $ 1 $ to the first element of the subsegment, $ 2 $ to the second element, and so on. The chosen subsegment should be inside the borders of the array $ a $ (i.e., if the left border of the chosen subsegment is $ l $ , then the condition $ 1 \le l \le l + k - 1 \le n $ should be satisfied). Note that the progression added is always $ 1, 2, \ldots, k $ but not the $ k, k - 1, \ldots, 1 $ or anything else (i.e., the leftmost element of the subsegment always increases by $ 1 $ , the second element always increases by $ 2 $ and so on).

Your task is to find the minimum possible number of operations required to satisfy the condition $ a_i \ge b_i $ for each $ i $ from $ 1 $ to $ n $ . Note that the condition $ a_i \ge b_i $ should be satisfied for all elements at once.

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 3 \cdot 10^5 $ ) — the number of elements in both arrays and the length of the subsegment, respectively.

The second line of the input contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \le b_i \le 10^{12} $ ), where $ b_i $ is the $ i $ -th element of the array $ b $ .

## 输出格式

Print one integer — the minimum possible number of operations required to satisfy the condition $ a_i \ge b_i $ for each $ i $ from $ 1 $ to $ n $ .

## 说明/提示

Consider the first example. In this test, we don't really have any choice, so we need to add at least five progressions to make the first element equals $ 5 $ . The array $ a $ becomes $ [5, 10, 15] $ .

Consider the second example. In this test, let's add one progression on the segment $ [1; 3] $ and two progressions on the segment $ [4; 6] $ . Then, the array $ a $ becomes $ [1, 2, 3, 2, 4, 6] $ .

## 样例 #1

### 输入

```
3 3
5 4 6
```

### 输出

```
5
```

## 样例 #2

### 输入

```
6 3
1 2 3 2 2 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
6 3
1 2 4 1 2 3
```

### 输出

```
3
```

## 样例 #4

### 输入

```
7 3
50 17 81 25 42 39 96
```

### 输出

```
92
```



---

---
title: "Tree Infection"
layout: "post"
diff: 普及+/提高
pid: CF1665C
tag: ['贪心', '二分']
---

# Tree Infection

## 题目描述

### 题意描述
一个树是一个无环连通图。一个有根树有一个被称作“根结点”的结点。对于任意一个非根结点 $v$ ，其父结点是从根结点到结点 $v$ 最短路径上的前一个结点。结点 $v$ 的子结点包括所有以 $v$ 父结点为 $v$ 的结点。

给定一个有 $n$ 个结点的有根树。结点 $1$ 即为根结点。一开始，该树上所有结点均是“健康”的。

每一秒你会进行两次操作——先是传播操作，然后是注射操作，定义如下。

- 传播操作：对于每个结点 $v$ ，若该结点至少有一个子结点被“感染”，则你可以“感染”顶点 $v$ 任意一个其他的子结点。
- 注射：你可以选择任意一个“健康”的结点并使它变为“感染”状态。

这程每秒会重复一次知道整个树的结点都处于“感染”状态。你需要找到使整个树被“感染”的最短时间（秒数）。

## 输入格式

有多个测试数据。第一行输入整数 $t$ ，代表有 $t$ 组数据。每组数据格式如下。

第一行给定整数 $n$ ，表示整个树共有 $n$ 个结点。

第二行输入 $n-1$ 个整数 $p_{2...i-1}$ ，第 $p_i$ 个整数表示 $i$ 号结点的父节点是 $p_i$ 号结点。

## 输出格式

共 $t$ 行，每行一个整数，即使整个树被“感染”的最短时间（秒数）。

## 说明/提示

- $ 1 \le t \le 10^4 $
- $ 2 \le n \le 2 \times 10^5 $
- $ 1 \le p_i \le n $
- $ \sum \limits_{i=1} ^t n_i \le 2 \times 10^5 $

## 样例 #1

### 输入

```
5
7
1 1 1 2 2 4
5
5 5 1 4
2
1
3
3 1
6
1 1 1 1 1
```

### 输出

```
4
4
2
3
4
```



---

---
title: "Vlad and Unfinished Business"
layout: "post"
diff: 普及+/提高
pid: CF1675F
tag: ['贪心', '树形数据结构']
---

# Vlad and Unfinished Business

## 题目描述

### 题意简述

有一棵 $n$ 个节点的树，从节点 $x$ 出发，需要到 $a_1,a_2\dots a_k$ 节点完成任务（任意顺序），最终到达终点 $y$。走每条边的花费为 $1$，求最小花费。

## 输入格式

第一行一个正整数 $t$ 表示数据组数。

对于每组数据，第一行两个正整数 $n,k$ 表示节点数量和任务数量；第二行两个正整数 $x,y$ 表示起点编号和终点编号；第三行 $k$ 个正整数 $a_1,a_2\dots a_k$ 表示任务所在节点编号；接下来 $n-1$ 行，每行两个正整数表示一条边的两个端点编号。

## 输出格式

对于每组数据，输出一行一个正整数表示最小花费。

### 数据规模

$t\le 10^4,1\le n,k\le 2\times 10^5,\sum n\le2\times10^5$

## 样例 #1

### 输入

```
3

3 1
1 3
2
1 3
1 2

6 4
3 5
1 6 2 1
1 3
3 4
3 5
5 6
5 2

6 2
3 2
5 3
1 3
3 4
3 5
5 6
5 2
```

### 输出

```
3
7
2
```



---

---
title: "Tokitsukaze and Two Colorful Tapes"
layout: "post"
diff: 普及+/提高
pid: CF1677C
tag: ['贪心', '并查集']
---

# Tokitsukaze and Two Colorful Tapes

## 题目描述

Tokitsukaze has two colorful tapes. There are $ n $ distinct colors, numbered $ 1 $ through $ n $ , and each color appears exactly once on each of the two tapes. Denote the color of the $ i $ -th position of the first tape as $ ca_i $ , and the color of the $ i $ -th position of the second tape as $ cb_i $ .

Now Tokitsukaze wants to select each color an integer value from $ 1 $ to $ n $ , distinct for all the colors. After that she will put down the color values in each colored position on the tapes. Denote the number of the $ i $ -th position of the first tape as $ numa_i $ , and the number of the $ i $ -th position of the second tape as $ numb_i $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/ba8639f69fd74760b5261096016619c105b9cbe6.png)For example, for the above picture, assuming that the color red has value $ x $ ( $ 1 \leq x \leq n $ ), it appears at the $ 1 $ -st position of the first tape and the $ 3 $ -rd position of the second tape, so $ numa_1=numb_3=x $ .

Note that each color $ i $ from $ 1 $ to $ n $ should have a distinct value, and the same color which appears in both tapes has the same value.

After labeling each color, the beauty of the two tapes is calculated as $ $$$\sum_{i=1}^{n}|numa_i-numb_i|. $ $$$

Please help Tokitsukaze to find the highest possible beauty.

## 输入格式

The first contains a single positive integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

For each test case, the first line contains a single integer $ n $ ( $ 1\leq n \leq 10^5 $ ) — the number of colors.

The second line contains $ n $ integers $ ca_1, ca_2, \ldots, ca_n $ ( $ 1 \leq ca_i \leq n $ ) — the color of each position of the first tape. It is guaranteed that $ ca $ is a permutation.

The third line contains $ n $ integers $ cb_1, cb_2, \ldots, cb_n $ ( $ 1 \leq cb_i \leq n $ ) — the color of each position of the second tape. It is guaranteed that $ cb $ is a permutation.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^{5} $ .

## 输出格式

For each test case, print a single integer — the highest possible beauty.

## 说明/提示

An optimal solution for the first test case is shown in the following figure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/eb5a2fd8a44a35877d106dc26e9dcf9fd0a2a486.png)The beauty is $ \left|4-3 \right|+\left|3-5 \right|+\left|2-4 \right|+\left|5-2 \right|+\left|1-6 \right|+\left|6-1 \right|=18 $ .

An optimal solution for the second test case is shown in the following figure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/ec6542f7ba45f38760ee0d113e52ba6999ceef87.png)The beauty is $ \left|2-2 \right|+\left|1-6 \right|+\left|3-3 \right|+\left|6-1 \right|+\left|4-4 \right|+\left|5-5 \right|=10 $ .

## 样例 #1

### 输入

```
3
6
1 5 4 3 2 6
5 3 1 4 6 2
6
3 5 4 6 2 1
3 6 4 5 2 1
1
1
1
```

### 输出

```
18
10
0
```



---

---
title: "Tokitsukaze and Good 01-String (hard version)"
layout: "post"
diff: 普及+/提高
pid: CF1678B2
tag: ['动态规划 DP', '贪心']
---

# Tokitsukaze and Good 01-String (hard version)

## 题目描述

This is the hard version of the problem. The only difference between the two versions is that the harder version asks additionally for a minimum number of subsegments.

Tokitsukaze has a binary string $ s $ of length $ n $ , consisting only of zeros and ones, $ n $ is even.

Now Tokitsukaze divides $ s $ into the minimum number of contiguous subsegments, and for each subsegment, all bits in each subsegment are the same. After that, $ s $ is considered good if the lengths of all subsegments are even.

For example, if $ s $ is "11001111", it will be divided into "11", "00" and "1111". Their lengths are $ 2 $ , $ 2 $ , $ 4 $ respectively, which are all even numbers, so "11001111" is good. Another example, if $ s $ is "1110011000", it will be divided into "111", "00", "11" and "000", and their lengths are $ 3 $ , $ 2 $ , $ 2 $ , $ 3 $ . Obviously, "1110011000" is not good.

Tokitsukaze wants to make $ s $ good by changing the values of some positions in $ s $ . Specifically, she can perform the operation any number of times: change the value of $ s_i $ to '0' or '1' ( $ 1 \leq i \leq n $ ). Can you tell her the minimum number of operations to make $ s $ good? Meanwhile, she also wants to know the minimum number of subsegments that $ s $ can be divided into among all solutions with the minimum number of operations.

## 输入格式

The first contains a single positive integer $ t $ ( $ 1 \leq t \leq 10\,000 $ ) — the number of test cases.

For each test case, the first line contains a single integer $ n $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ ) — the length of $ s $ , it is guaranteed that $ n $ is even.

The second line contains a binary string $ s $ of length $ n $ , consisting only of zeros and ones.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single line with two integers — the minimum number of operations to make $ s $ good, and the minimum number of subsegments that $ s $ can be divided into among all solutions with the minimum number of operations.

## 说明/提示

In the first test case, one of the ways to make $ s $ good is the following.

Change $ s_3 $ , $ s_6 $ and $ s_7 $ to '0', after that $ s $ becomes "1100000000", it can be divided into "11" and "00000000", which lengths are $ 2 $ and $ 8 $ respectively, the number of subsegments of it is $ 2 $ . There are other ways to operate $ 3 $ times to make $ s $ good, such as "1111110000", "1100001100", "1111001100", the number of subsegments of them are $ 2 $ , $ 4 $ , $ 4 $ respectively. It's easy to find that the minimum number of subsegments among all solutions with the minimum number of operations is $ 2 $ .

In the second, third and fourth test cases, $ s $ is good initially, so no operation is required.

## 样例 #1

### 输入

```
5
10
1110011000
8
11001111
2
00
2
11
6
100110
```

### 输出

```
3 2
0 3
0 1
0 1
3 1
```



---

---
title: "Moving Chips"
layout: "post"
diff: 普及+/提高
pid: CF1680E
tag: ['动态规划 DP', '贪心']
---

# Moving Chips

## 题目描述

## 题意翻译  
### 题意简述
给你一个大小为$2$×$n$的棋盘，
棋子用'*'表示，空位用'.'表示。  
在一次移动中，你可以选择任何棋子并将其移动到棋盘的任何相邻的格子，如果目的格子中有棋子则把他们合并为一个。

## 输入格式

第一行一个正整数$t$表示数据组数。  
对于每组数据，第一行一个正整数$n$表示棋盘列数，接下来两行每行输入一个字符串$s$，
表示棋盘初始状态。

## 输出格式

对于每组数据输出一个正整数表示在棋盘上正好留下一个棋子所需的最小移动数。  
### 数据规模  
$1$<=$t$<=$10^{4}$，$1$<=$n$<=$2\cdot$$10^{5}$  
所有测试案例的$n$之和不超过$2$$\cdot$$10^{5}$
($\sum_{}^{}$$n$<=$2$$\cdot$$10^{5}$)

## 样例 #1

### 输入

```
5
1
*
.
2
.*
**
3
*.*
.*.
4
**.*
**..
5
**...
...**
```

### 输出

```
0
2
3
5
5
```



---

---
title: "Traps"
layout: "post"
diff: 普及+/提高
pid: CF1684D
tag: ['贪心', '差分']
---

# Traps

## 题目描述

There are $ n $ traps numbered from $ 1 $ to $ n $ . You will go through them one by one in order. The $ i $ -th trap deals $ a_i $ base damage to you.

Instead of going through a trap, you can jump it over. You can jump over no more than $ k $ traps. If you jump over a trap, it does not deal any damage to you. But there is an additional rule: if you jump over a trap, all next traps damages increase by $ 1 $ (this is a bonus damage).

Note that if you jump over a trap, you don't get any damage (neither base damage nor bonus damage). Also, the bonus damage stacks so, for example, if you go through a trap $ i $ with base damage $ a_i $ , and you have already jumped over $ 3 $ traps, you get $ (a_i + 3) $ damage.

You have to find the minimal damage that it is possible to get if you are allowed to jump over no more than $ k $ traps.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. Description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 1 \le k \le n $ ) — the number of traps and the number of jump overs that you are allowed to make.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — base damage values of all traps.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case output a single integer — the minimal total damage that it is possible to get if you are allowed to jump over no more than $ k $ traps.

## 说明/提示

In the first test case it is allowed to jump over all traps and take $ 0 $ damage.

In the second test case there are $ 5 $ ways to jump over some traps:

1. Do not jump over any trap.Total damage: $ 5 + 10 + 11 + 5 = 31 $ .
2. Jump over the $ 1 $ -st trap.Total damage: $ \underline{0} + (10 + 1) + (11 + 1) + (5 + 1) = 29 $ .
3. Jump over the $ 2 $ -nd trap.Total damage: $ 5 + \underline{0} + (11 + 1) + (5 + 1) = 23 $ .
4. Jump over the $ 3 $ -rd trap.Total damage: $ 5 + 10 + \underline{0} + (5 + 1) = 21 $ .
5. Jump over the $ 4 $ -th trap.Total damage: $ 5 + 10 + 11 + \underline{0} = 26 $ .

To get minimal damage it is needed to jump over the $ 3 $ -rd trap, so the answer is $ 21 $ .

In the third test case it is optimal to jump over the traps $ 1 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 7 $ :

Total damage: $ 0 + (2 + 1) + 0 + 0 + 0 + (2 + 4) + 0 = 9 $ .

## 样例 #1

### 输入

```
5
4 4
8 7 1 4
4 1
5 10 11 5
7 5
8 2 5 15 11 2 8
6 3
1 2 3 4 5 6
1 1
7
```

### 输出

```
0
21
9
6
0
```



---

---
title: "The Enchanted Forest"
layout: "post"
diff: 普及+/提高
pid: CF1687A
tag: ['数学', '贪心']
---

# The Enchanted Forest

## 题目描述

> 其实这里被称为魔法森林，基本上就是因为这些有幻觉效果的蘑菇。光是接近这些蘑菇，就好像被施了魔法而产生幻觉。——《东方求闻史纪》

魔理沙来到了魔法森林采摘蘑菇。    
魔法森林可以被抽象成一条有着 $n$ 个节点，从 $1$ 到 $n$ 标号的数轴。在魔理沙出发之前，她的好友帕秋莉运用魔法去侦测了每个节点上的蘑菇数量，分别为 $a_1,a_2,\dots,a_n$。    
在第 $0$ 分钟的时候，魔理沙可以从任意一个节点出发。在每一分钟的时候，她将会做以下事情：

- 她将从节点 $x$ 移动到节点 $y$（$|x-y| \leq 1$，即 $y$ 可能等于 $x$）
- 她将会收集节点 $y$ 上的所有蘑菇。
- 魔法森林中每个节点会再生长出一个蘑菇。

注意，她不能在第 $0$ 分钟的时候收集蘑菇。    
现在魔理沙希望知道她在前 $k$ 分钟的时候，最多能收集到多少个蘑菇。请你帮帮她。

## 输入格式

第一行输入一个正整数 $t(1 \leq t \leq 10^4)$，表示输入数据组数。   
对于每一组测试数据，第一行输入两个正整数 $n,k(1 \leq n \leq 2\times 10^5, 1\leq k \leq 10^9)$，含义如题目所述。    
第二行输入 $n$ 个正整数 $a_i$，表示每个节点上起初有的蘑菇数量。

## 输出格式

对于每组测试数据输出一行，表示魔理沙最多能收集到多少个蘑菇。

## 样例 #1

### 输入

```
4
5 2
5 6 1 2 3
5 7
5 6 1 2 3
1 2
999999
5 70000
1000000000 1000000000 1000000000 1000000000 1000000000
```

### 输出

```
12
37
1000000
5000349985
```



---

---
title: "Fake Plastic Trees"
layout: "post"
diff: 普及+/提高
pid: CF1693B
tag: ['贪心', '树形数据结构']
---

# Fake Plastic Trees

## 题目描述

We are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . The root of the tree is the vertex $ 1 $ and the parent of the vertex $ v $ is $ p_v $ .

There is a number written on each vertex, initially all numbers are equal to $ 0 $ . Let's denote the number written on the vertex $ v $ as $ a_v $ .

For each $ v $ , we want $ a_v $ to be between $ l_v $ and $ r_v $ $ (l_v \leq a_v \leq r_v) $ .

In a single operation we do the following:

- Choose some vertex $ v $ . Let $ b_1, b_2, \ldots, b_k $ be vertices on the path from the vertex $ 1 $ to vertex $ v $ (meaning $ b_1 = 1 $ , $ b_k = v $ and $ b_i = p_{b_{i + 1}} $ ).
- Choose a non-decreasing array $ c $ of length $ k $ of nonnegative integers: $ 0 \leq c_1 \leq c_2 \leq \ldots \leq c_k $ .
- For each $ i $ $ (1 \leq i \leq k) $ , increase $ a_{b_i} $ by $ c_i $ .

What's the minimum number of operations needed to achieve our goal?

## 输入格式

The first line contains an integer $ t $ $ (1\le t\le 1000) $ — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ $ (2\le n\le 2 \cdot 10^5) $ — the number of the vertices in the tree.

The second line of each test case contains $ n - 1 $ integers, $ p_2, p_3, \ldots, p_n $ $ (1 \leq p_i < i) $ , where $ p_i $ denotes the parent of the vertex $ i $ .

The $ i $ -th of the following $ n $ lines contains two integers $ l_i $ and $ r_i $ $ (1 \le l_i \le r_i \le 10^9) $ .

It is guaranteed that the sum of $ n $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case output the minimum number of operations needed.

## 说明/提示

In the first test case, we can achieve the goal with a single operation: choose $ v = 2 $ and $ c = [1, 2] $ , resulting in $ a_1 = 1, a_2 = 2 $ .

In the second test case, we can achieve the goal with two operations: first, choose $ v = 2 $ and $ c = [3, 3] $ , resulting in $ a_1 = 3, a_2 = 3, a_3 = 0 $ . Then, choose $ v = 3, c = [2, 7] $ , resulting in $ a_1 = 5, a_2 = 3, a_3 = 7 $ .

## 样例 #1

### 输入

```
4
2
1
1 5
2 9
3
1 1
4 5
2 4
6 10
4
1 2 1
6 9
5 6
4 5
2 4
5
1 2 3 4
5 5
4 4
3 3
2 2
1 1
```

### 输出

```
1
2
2
5
```



---

---
title: "Permutation Restoration"
layout: "post"
diff: 普及+/提高
pid: CF1701D
tag: ['贪心']
---

# Permutation Restoration

## 题目描述

Monocarp 有一个长度为 $n$ ，由 $1$ ~ $n$ 构成的数组  $a$ ，其中每个元素在 $a$ 中出现且仅出现 $1$ 次。

现在 Monocarp 计算一个数组 $b$ ，使得 $b_i=\lfloor\frac{i}{a_i}\rfloor$ 。

现在给出 $b$ 数组，要求求出任意一组 $a$ 。

注意：保证对于所给出的 $b$ 至少有一组 $a$ 与之对应。

## 输入格式

本题为多组数据。

第一行为一个整数 $t(1 \le t \le 10^5)$ ，代表数据组数。

接下来 $t$ 组，每组的第一行为一个整数 $n(1 \le n \le 5×10^5)$ 。

每组的第二行为 $n$ 个整数 $b_1,b_2,···,b_n(0 \le b_i \le n)$ 。

## 输出格式

对于每组，输出 $n$ 对于给定数组 $b$ 的任意一组 $a$ 。

## 样例 #1

### 输入

```
4
4
0 2 0 1
2
1 1
5
0 0 1 4 1
3
0 1 3
```

### 输出

```
2 1 4 3 
1 2 
3 4 2 1 5 
3 2 1
```



---

---
title: "Mark and Lightbulbs"
layout: "post"
diff: 普及+/提高
pid: CF1705D
tag: ['贪心']
---

# Mark and Lightbulbs

## 题目描述

Mark has just purchased a rack of $ n $ lightbulbs. The state of the lightbulbs can be described with binary string $ s = s_1s_2\dots s_n $ , where $ s_i=\texttt{1} $ means that the $ i $ -th lightbulb is turned on, while $ s_i=\texttt{0} $ means that the $ i $ -th lightbulb is turned off.

Unfortunately, the lightbulbs are broken, and the only operation he can perform to change the state of the lightbulbs is the following:

- Select an index $ i $ from $ 2,3,\dots,n-1 $ such that $ s_{i-1}\ne s_{i+1} $ .
- Toggle $ s_i $ . Namely, if $ s_i $ is $ \texttt{0} $ , set $ s_i $ to $ \texttt{1} $ or vice versa.

Mark wants the state of the lightbulbs to be another binary string $ t $ . Help Mark determine the minimum number of operations to do so.

## 输入格式

The first line of the input contains a single integer $ q $ ( $ 1\leq q\leq 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 3\leq n\leq 2\cdot 10^5 $ ) — the number of lightbulbs.

The second line of each test case contains a binary string $ s $ of length $ n $ — the initial state of the lightbulbs.

The third line of each test case contains a binary string $ t $ of length $ n $ — the final state of the lightbulbs.

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, print a line containing the minimum number of operations Mark needs to perform to transform $ s $ to $ t $ . If there is no such sequence of operations, print $ -1 $ .

## 说明/提示

In the first test case, one sequence of operations that achieves the minimum number of operations is the following.

- Select $ i=3 $ , changing $ \texttt{01}\color{red}{\texttt{0}}\texttt{0} $ to $ \texttt{01}\color{red}{\texttt{1}}\texttt{0} $ .
- Select $ i=2 $ , changing $ \texttt{0}\color{red}{\texttt{1}}\texttt{10} $ to $ \texttt{0}\color{red}{\texttt{0}}\texttt{10} $ .

 In the second test case, there is no sequence of operations because one cannot change the first digit or the last digit of $ s $ .In the third test case, even though the first digits of $ s $ and $ t $ are the same and the last digits of $ s $ and $ t $ are the same, it can be shown that there is no sequence of operations that satisfies the condition.

In the fourth test case, one sequence that achieves the minimum number of operations is the following:

- Select $ i=3 $ , changing $ \texttt{00}\color{red}{\texttt{0}}\texttt{101} $ to $ \texttt{00}\color{red}{\texttt{1}}\texttt{101} $ .
- Select $ i=2 $ , changing $ \texttt{0}\color{red}{\texttt{0}}\texttt{1101} $ to $ \texttt{0}\color{red}{\texttt{1}}\texttt{1101} $ .
- Select $ i=4 $ , changing $ \texttt{011}\color{red}{\texttt{1}}\texttt{01} $ to $ \texttt{011}\color{red}{\texttt{0}}\texttt{01} $ .
- Select $ i=5 $ , changing $ \texttt{0110}\color{red}{\texttt{0}}\texttt{1} $ to $ \texttt{0110}\color{red}{\texttt{1}}\texttt{1} $ .
- Select $ i=3 $ , changing $ \texttt{01}\color{red}{\texttt{1}}\texttt{011} $ to $ \texttt{01}\color{red}{\texttt{0}}\texttt{011} $ .

## 样例 #1

### 输入

```
4
4
0100
0010
4
1010
0100
5
01001
00011
6
000101
010011
```

### 输出

```
2
-1
-1
5
```



---

---
title: "Doremy's IQ"
layout: "post"
diff: 普及+/提高
pid: CF1707A
tag: ['贪心', '二分']
---

# Doremy's IQ

## 题目描述

哆来咪·苏伊特参加了 $n$ 场比赛。 比赛 $i$ 只能在第 $i$ 天进行。比赛 $i$ 的难度为 $a_i$。最初，哆来咪的 IQ 为 $q$ 。 在第 $i$ 天，哆来咪将选择是否参加比赛 i。只有当她当前的 IQ 大于 $0$ 时，她才能参加比赛。

如果哆来咪选择在第 $i$ 天参加比赛 $i$，则会发生以下情况：
- 如果 $a_i>q$，哆来咪会觉得自己不够聪明，所以 $q$ 将会减 $1$；
- 否则，什么都不会改变。

如果她选择不参加比赛，一切都不会改变。哆来咪想参加尽可能多的比赛。请给哆来咪一个解决方案。

## 输入格式

第一行包含一个正整数 $t$ ($1\le t\le10^4$) ，表示测试数据的组数。

第二行包含两个整数 $n$ 和 $q$ ($1\le n\le10^5$, $1\le q\le10^9$)，表示比赛次数和哆来咪最开始时的 IQ。

第三行包含 $n$ 个整数 $a_1,a_2⋯a_n$($1\le a_i≤10^9$)，表示每场比赛的难度。

数据保证 $n$ 之和不超过 $10^5$。

## 输出格式

对于每组数据，输出一个二进制字符串 $s$，如果哆来咪应该选择参加比赛 $i$，则 $s_i=1$，否则 $s_i=0$。 字符串中 $1$ 的数量应该尽可能的多，并且当她的 IQ 为 $0$ 或更低时，她不应该参加比赛。

如果有多个解决方案，你可以输出任意一个。

## 说明/提示

在第一个测试用例中，哆来咪参加了唯一的比赛。她的 IQ 没有下降。

在第二个测试用例中，哆来咪参加了两个比赛。在参加比赛 $2$ 后，她的 IQ 下降了 $1$。

在第三个测试用例中，哆来咪参加了比赛 $1$ 和比赛 $2$。她的 IQ 在参加比赛 $2$ 后降至 $0$，因此她无法参加比赛 $3$。

## 样例 #1

### 输入

```
5
1 1
1
2 1
1 2
3 1
1 2 1
4 2
1 4 3 1
5 2
5 1 2 4 3
```

### 输出

```
1
11
110
1110
01111
```



---

---
title: "Recover an RBS"
layout: "post"
diff: 普及+/提高
pid: CF1709C
tag: ['贪心']
---

# Recover an RBS

## 题目描述

A bracket sequence is a string containing only characters "(" and ")". A regular bracket sequence (or, shortly, an RBS) is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example:

- bracket sequences "()()" and "(())" are regular (the resulting expressions are: "(1)+(1)" and "((1+1)+1)");
- bracket sequences ")(", "(" and ")" are not.

There was an RBS. Some brackets have been replaced with question marks. Is it true that there is a unique way to replace question marks with brackets, so that the resulting sequence is an RBS?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 5 \cdot 10^4 $ ) — the number of testcases.

The only line of each testcase contains an RBS with some brackets replaced with question marks. Each character is either '(', ')' or '?'. At least one RBS can be recovered from the given sequence.

The total length of the sequences over all testcases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each testcase, print "YES" if the way to replace question marks with brackets, so that the resulting sequence is an RBS, is unique. If there is more than one way, then print "NO".

## 说明/提示

In the first testcase, the only possible original RBS is "(())".

In the second testcase, there are multiple ways to recover an RBS.

In the third and the fourth testcases, the only possible original RBS is "()".

In the fifth testcase, the original RBS can be either "((()()))" or "(())()()".

## 样例 #1

### 输入

```
5
(?))
??????
()
??
?(?)()?)
```

### 输出

```
YES
NO
YES
YES
NO
```



---

---
title: "Empty Graph"
layout: "post"
diff: 普及+/提高
pid: CF1712D
tag: ['贪心', '二分']
---

# Empty Graph

## 题目描述

— Do you have a wish?



 — I want people to stop gifting each other arrays.

O_o and Another Young Boy



An array of $ n $ positive integers $ a_1,a_2,\ldots,a_n $ fell down on you from the skies, along with a positive integer $ k \le n $ .

You can apply the following operation at most $ k $ times:

- Choose an index $ 1 \le i \le n $ and an integer $ 1 \le x \le 10^9 $ . Then do $ a_i := x $ (assign $ x $ to $ a_i $ ).

Then build a [complete](https://en.wikipedia.org/wiki/Complete_graph) undirected weighted graph with $ n $ vertices numbered with integers from $ 1 $ to $ n $ , where edge $ (l, r) $ ( $ 1 \le l < r \le n $ ) has weight $ \min(a_{l},a_{l+1},\ldots,a_{r}) $ .

You have to find the maximum possible diameter of the resulting graph after performing at most $ k $ operations.

The diameter of a graph is equal to $ \max\limits_{1 \le u < v \le n}{\operatorname{d}(u, v)} $ , where $ \operatorname{d}(u, v) $ is the length of the shortest path between vertex $ u $ and vertex $ v $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). Description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 2 \le n \le 10^5 $ , $ 1 \le k \le n $ ).

The second line of each test case contains $ n $ positive integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \le a_i \le 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case print one integer — the maximum possible diameter of the graph after performing at most $ k $ operations.

## 说明/提示

In the first test case, one of the optimal arrays is $ [2,4,5] $ .

The graph built on this array:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1712D/6f5937a14546fd0344ab2a7ad56768b75a98a230.png) $ \operatorname{d}(1, 2) = \operatorname{d}(1, 3) = 2 $ and $ \operatorname{d}(2, 3) = 4 $ , so the diameter is equal to $ \max(2,2,4) = 4 $ .

## 样例 #1

### 输入

```
6
3 1
2 4 1
3 2
1 9 84
3 1
10 2 6
3 2
179 17 1000000000
2 1
5 9
2 2
4 2
```

### 输出

```
4
168
10
1000000000
9
1000000000
```



---

---
title: "Color with Occurrences"
layout: "post"
diff: 普及+/提高
pid: CF1714D
tag: ['动态规划 DP', '贪心']
---

# Color with Occurrences

## 题目描述

You are given some text $ t $ and a set of $ n $ strings $ s_1, s_2, \dots, s_n $ .

In one step, you can choose any occurrence of any string $ s_i $ in the text $ t $ and color the corresponding characters of the text in red. For example, if $ t=\texttt{bababa} $ and $ s_1=\texttt{ba} $ , $ s_2=\texttt{aba} $ , you can get $ t=\color{red}{\texttt{ba}}\texttt{baba} $ , $ t=\texttt{b}\color{red}{\texttt{aba}}\texttt{ba} $ or $ t=\texttt{bab}\color{red}{\texttt{aba}} $ in one step.

You want to color all the letters of the text $ t $ in red. When you color a letter in red again, it stays red.

In the example above, three steps are enough:

- Let's color $ t[2 \dots 4]=s_2=\texttt{aba} $ in red, we get $ t=\texttt{b}\color{red}{\texttt{aba}}\texttt{ba} $ ;
- Let's color $ t[1 \dots 2]=s_1=\texttt{ba} $ in red, we get $ t=\color{red}{\texttt{baba}}\texttt{ba} $ ;
- Let's color $ t[4 \dots 6]=s_2=\texttt{aba} $ in red, we get $ t=\color{red}{\texttt{bababa}} $ .

Each string $ s_i $ can be applied any number of times (or not at all). Occurrences for coloring can intersect arbitrarily.

Determine the minimum number of steps needed to color all letters $ t $ in red and how to do it. If it is impossible to color all letters of the text $ t $ in red, output -1.

## 输入格式

The first line of the input contains an integer $ q $ ( $ 1 \le q \le 100 $ ) —the number of test cases in the test.

The descriptions of the test cases follow.

The first line of each test case contains the text $ t $ ( $ 1 \le |t| \le 100 $ ), consisting only of lowercase Latin letters, where $ |t| $ is the length of the text $ t $ .

The second line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10 $ ) — the number of strings in the set.

This is followed by $ n $ lines, each containing a string $ s_i $ ( $ 1 \le |s_i| \le 10 $ ) consisting only of lowercase Latin letters, where $ |s_i| $ — the length of string $ s_i $ .

## 输出格式

For each test case, print the answer on a separate line.

If it is impossible to color all the letters of the text in red, print a single line containing the number -1.

Otherwise, on the first line, print the number $ m $ — the minimum number of steps it will take to turn all the letters $ t $ red.

Then in the next $ m $ lines print pairs of indices: $ w_j $ and $ p_j $ ( $ 1 \le j \le m $ ), which denote that the string with index $ w_j $ was used as a substring to cover the occurrences starting in the text $ t $ from position $ p_j $ . The pairs can be output in any order.

If there are several answers, output any of them.

## 说明/提示

The first test case is explained in the problem statement.

In the second test case, it is impossible to color all the letters of the text in red.

## 样例 #1

### 输入

```
6
bababa
2
ba
aba
caba
2
bac
acab
abacabaca
3
aba
bac
aca
baca
3
a
c
b
codeforces
4
def
code
efo
forces
aaaabbbbcccceeee
4
eeee
cccc
aaaa
bbbb
```

### 输出

```
3
2 2
1 1
2 4
-1
4
1 1
2 6
3 3
3 7
4
3 1
1 2
2 3
1 4
2
4 5
2 1
4
3 1
4 5
2 9
1 13
```



---

---
title: "Fibonacci Strings"
layout: "post"
diff: 普及+/提高
pid: CF1718B
tag: ['贪心', '堆']
---

# Fibonacci Strings

## 题目描述

In all schools in Buryatia, in the $ 1 $ class, everyone is told the theory of Fibonacci strings.

"A block is a subsegment of a string where all the letters are the same and are bounded on the left and right by the ends of the string or by letters other than the letters in the block. A string is called a Fibonacci string if, when it is divided into blocks, their lengths in the order they appear in the string form the Fibonacci sequence ( $ f_0 = f_1 = 1 $ , $ f_i = f_{i-2} + f_{i-1} $ ), starting from the zeroth member of this sequence. A string is called semi-Fibonacci if it possible to reorder its letters to get a Fibonacci string."

Burenka decided to enter the Buryat State University, but at the entrance exam she was given a difficult task. She was given a string consisting of the letters of the Buryat alphabet (which contains exactly $ k $ letters), and was asked if the given string is semi-Fibonacci. The string can be very long, so instead of the string, she was given the number of appearances of each letter ( $ c_i $ for the $ i $ -th letter) in that string. Unfortunately, Burenka no longer remembers the theory of Fibonacci strings, so without your help she will not pass the exam.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The following is a description of the input data sets.

The first line of each test case contains one integer $ k $ ( $ 1 \leq k \leq 100 $ ) — the number of letters in the alphabet.

The second line of each test case contains $ k $ integers $ c_1, c_2, \ldots, c_k $ ( $ 1 \leq c_i \leq 10^9 $ ) — the number of occurrences of each letter in the string.

## 输出格式

For each test case print the string "YES" if the corresponding string is semi-Fibonacci, and "NO" if it is not.

You can print "YES" and "NO" in any case (for example, the strings "yEs", "yes", "Yes" will be recognized as a positive answer).

## 说明/提示

In the first test case, a one-character string is semi-Fibonacci, being itself a Fibonacci string.

In the second test case, a string of two different characters is Fibonacci.

In the third test case, the string "abb" (let the first of the alphabet letter be a, the second letter b) is not a semi-Fibonacci string, since no permutation of its letters ("abb", "bab", and "bba") is a Fibonacci string.

In the fourth test case, two permutations of the letters of the string "abaccac" (the first letter is a, the second letter is b, the third letter is c) are Fibonacci strings — "abaaccc" and "cbccaaa".

## 样例 #1

### 输入

```
6
1
1
2
1 1
2
1 2
3
3 1 3
2
7 5
6
26 8 3 4 13 34
```

### 输出

```
YES
YES
NO
YES
NO
YES
```



---

---
title: "Maximum AND"
layout: "post"
diff: 普及+/提高
pid: CF1721D
tag: ['贪心', '位运算']
---

# Maximum AND

## 题目描述

给出两个长度为 $n$ 的数组 $a,b$ ，规定 $f(a,b)$ 表示以下操作：

1. 创建一个长度为 $n$ 的 $c$ 数组，满足 $c_i=a_i \oplus b_i$ （此处的 $\oplus$ 表示[按位异或](https://baike.baidu.com/item/%E5%BC%82%E6%88%96/10993677?fr=aladdin)）。
2. 则 $f(a, b) = c_1\space\& c_2\space\& \cdots \& c_n$。

你可以将 $b$ 数组进行任意的排列（包括保留原始情况），试求出最大的 $f(a,b)$ 。

## 输入格式

第一行一个 $t\ (1\le t \le 10^4)$ ，表示数据组数。

对于每组数据：
	
第一行一个 $n\ (1 \le n \le 10^5)$ ，表示 $a,b$ 数组的长度。

第二行 $n$ 个自然数 $a_1,a_2......a_n(1 \le a_i \lt 2^{30})$

第三行 $n$ 个自然数 $b_1,b_2......b_n(1 \le b_i \lt 2^{30})$

数据保证单个数据测试点内，所有 $n$ 之和不超过 $10^5$.

## 输出格式

对于每一个测试点，一行一个正整数表示     $f(a,b)$ 的最大值。

## 样例 #1

### 输入

```
3
5
1 0 0 3 3
2 3 2 1 0
3
1 1 1
0 0 3
8
0 1 2 3 4 5 6 7
7 6 5 4 3 2 1 0
```

### 输出

```
2
0
7
```



---

---
title: "Letter Picking"
layout: "post"
diff: 普及+/提高
pid: CF1728D
tag: ['动态规划 DP', '贪心', '区间 DP']
---

# Letter Picking

## 题目描述

Alice and Bob are playing a game. Initially, they are given a non-empty string $ s $ , consisting of lowercase Latin letters. The length of the string is even. Each player also has a string of their own, initially empty.

Alice starts, then they alternate moves. In one move, a player takes either the first or the last letter of the string $ s $ , removes it from $ s $ and prepends (adds to the beginning) it to their own string.

The game ends when the string $ s $ becomes empty. The winner is the player with a lexicographically smaller string. If the players' strings are equal, then it's a draw.

A string $ a $ is lexicographically smaller than a string $ b $ if there exists such position $ i $ that $ a_j = b_j $ for all $ j < i $ and $ a_i < b_i $ .

What is the result of the game if both players play optimally (e. g. both players try to win; if they can't, then try to draw)?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of testcases.

Each testcase consists of a single line — a non-empty string $ s $ , consisting of lowercase Latin letters. The length of the string $ s $ is even.

The total length of the strings over all testcases doesn't exceed $ 2000 $ .

## 输出格式

For each testcase, print the result of the game if both players play optimally. If Alice wins, print "Alice". If Bob wins, print "Bob". If it's a draw, print "Draw".

## 说明/提示

One of the possible games Alice and Bob can play in the first testcase:

1. Alice picks the first letter in $ s $ : $ s= $ "orces", $ a= $ "f", $ b= $ "";
2. Bob picks the last letter in $ s $ : $ s= $ "orce", $ a= $ "f", $ b= $ "s";
3. Alice picks the last letter in $ s $ : $ s= $ "orc", $ a= $ "ef", $ b= $ "s";
4. Bob picks the first letter in $ s $ : $ s= $ "rc", $ a= $ "ef", $ b= $ "os";
5. Alice picks the last letter in $ s $ : $ s= $ "r", $ a= $ "cef", $ b= $ "os";
6. Bob picks the remaining letter in $ s $ : $ s= $ "", $ a= $ "cef", $ b= $ "ros".

Alice wins because "cef" &lt; "ros". Neither of the players follows any strategy in this particular example game, so it doesn't show that Alice wins if both play optimally.

## 样例 #1

### 输入

```
2
forces
abba
```

### 输出

```
Alice
Draw
```



---

---
title: "Zero-Sum Prefixes"
layout: "post"
diff: 普及+/提高
pid: CF1748C
tag: ['贪心', '前缀和']
---

# Zero-Sum Prefixes

## 题目描述

The score of an array $ v_1,v_2,\ldots,v_n $ is defined as the number of indices $ i $ ( $ 1 \le i \le n $ ) such that $ v_1+v_2+\ldots+v_i = 0 $ .

You are given an array $ a_1,a_2,\ldots,a_n $ of length $ n $ . You can perform the following operation multiple times:

- select an index $ i $ ( $ 1 \le i \le n $ ) such that $ a_i=0 $ ;
- then replace $ a_i $ by an arbitrary integer.

What is the maximum possible score of $ a $ that can be obtained by performing a sequence of such operations?

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains one integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ -10^9 \le a_i \le 10^9 $ ) — array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print the maximum possible score of the array $ a $ after performing a sequence of operations.

## 说明/提示

In the first test case, it is optimal to change the value of $ a_2 $ to $ -2 $ in one operation.

The resulting array $ a $ will be $ [2,-2,1,-1,0] $ , with a score of $ 3 $ :

- $ a_1+a_2=2-2=0 $ ;
- $ a_1+a_2+a_3+a_4=2-2+1-1=0 $ ;
- $ a_1+a_2+a_3+a_4+a_5=2-2+1-1+0=0 $ .

In the second test case, it is optimal to change the value of $ a_3 $ to $ -2\,000\,000\,000 $ , giving us an array with a score of $ 1 $ .

In the third test case, it is not necessary to perform any operations.

## 样例 #1

### 输入

```
5
5
2 0 1 -1 0
3
1000000000 1000000000 0
4
0 0 0 0
8
3 0 2 -10 10 -30 30 0
9
1 0 0 1 -1 0 1 0 -1
```

### 输出

```
3
1
4
4
5
```



---

---
title: "Same Count One"
layout: "post"
diff: 普及+/提高
pid: CF1774D
tag: ['贪心', '构造', '双指针 two-pointer']
---

# Same Count One

## 题目描述

给定 $n$ 个长度为 $m$ 的，只包含 $0$ 和 $1$ 的数组，选择任意两个数组交换位置 $pos$ 上的数。在经过最少的操作后使得每个数组中的 $1$ 数量相等，并输出操作过程。

## 输入格式

第一行一个整数 $t$  $( 1 \leq t \leq 2\cdot 10^4 )$ 表示有 $t$ 组测试数据。

每组测试数据：第一行两个整数 $ n $ 和 $ m $ 。 $( 2 \leq n \leq 10^5 $ , $ 2 \leq m \leq 10^5 , \sum n\times m \le 10^6)$ 

接下来 $ n $ 行，每行 $ m $ 个整数（ $ 0 $ 或 $ 1 $ ）。

## 输出格式

对于每一组测试样例，若无法满足要求，输出 $ -1 $ .

否则, 第一行输出一个整数 $ k $ $ (0 \le k \le mn) $ ，即最小的操作数量。

接下来输出 $ k $ 行，每行 $ 3 $ 个整数, $ x, y, z $ $ (1 \le x, y \le n, 1 \le z \le m) $ , 表示交换 $ a_{x, z}, a_{y, z} $ : 即交换第 $ x $ 和第 $ y $ 行的第 $ z $ 个数。

## 样例 #1

### 输入

```
3
3 4
1 1 1 0
0 0 1 0
1 0 0 1
4 3
1 0 0
0 1 1
0 0 1
0 0 0
2 2
0 0
0 1
```

### 输出

```
1
2 1 1
1
4 2 2
-1
```



---

---
title: "Tree XOR"
layout: "post"
diff: 普及+/提高
pid: CF1882D
tag: ['贪心', '树形 DP', '位运算']
---

# Tree XOR

## 题目描述

You are given a tree with $ n $ vertices labeled from $ 1 $ to $ n $ . An integer $ a_{i} $ is written on vertex $ i $ for $ i = 1, 2, \ldots, n $ . You want to make all $ a_{i} $ equal by performing some (possibly, zero) spells.

Suppose you root the tree at some vertex. On each spell, you can select any vertex $ v $ and any non-negative integer $ c $ . Then for all vertices $ i $ in the subtree $ ^{\dagger} $ of $ v $ , replace $ a_{i} $ with $ a_{i} \oplus c $ . The cost of this spell is $ s \cdot c $ , where $ s $ is the number of vertices in the subtree. Here $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Let $ m_r $ be the minimum possible total cost required to make all $ a_i $ equal, if vertex $ r $ is chosen as the root of the tree. Find $ m_{1}, m_{2}, \ldots, m_{n} $ .

 $ ^{\dagger} $ Suppose vertex $ r $ is chosen as the root of the tree. Then vertex $ i $ belongs to the subtree of $ v $ if the simple path from $ i $ to $ r $ contains $ v $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^{4} $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^{5} $ ).

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i < 2^{20} $ ).

Each of the next $ n-1 $ lines contains two integers $ u $ and $ v $ ( $ 1 \le u, v \le n $ ), denoting that there is an edge connecting two vertices $ u $ and $ v $ .

It is guaranteed that the given edges form a tree.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^{5} $ .

## 输出格式

For each test case, print $ m_1, m_2, \ldots, m_n $ on a new line.

## 说明/提示

In the first test case, to find $ m_1 $ we root the tree at vertex $ 1 $ .

1. In the first spell, choose $ v=2 $ and $ c=1 $ . After performing the spell, $ a $ will become $ [3, 3, 0, 1] $ . The cost of this spell is $ 3 $ .
2. In the second spell, choose $ v=3 $ and $ c=3 $ . After performing the spell, $ a $ will become $ [3, 3, 3, 1] $ . The cost of this spell is $ 3 $ .
3. In the third spell, choose $ v=4 $ and $ c=2 $ . After performing the spell, $ a $ will become $ [3, 3, 3, 3] $ . The cost of this spell is $ 2 $ .

Now all the values in array $ a $ are equal, and the total cost is $ 3 + 3 + 2 = 8 $ .

The values $ m_2 $ , $ m_3 $ , $ m_4 $ can be found analogously.

In the second test case, the goal is already achieved because there is only one vertex.

## 样例 #1

### 输入

```
2
4
3 2 1 0
1 2
2 3
2 4
1
100
```

### 输出

```
8 6 12 10 
0
```



---

---
title: "Matching Arrays"
layout: "post"
diff: 普及+/提高
pid: CF1896C
tag: ['贪心', '排序']
---

# Matching Arrays

## 题目描述

You are given two arrays $ a $ and $ b $ of size $ n $ . The beauty of the arrays $ a $ and $ b $ is the number of indices $ i $ such that $ a_i > b_i $ .

You are also given an integer $ x $ . Determine whether it is possible to rearrange the elements of $ b $ such that the beauty of the arrays becomes $ x $ . If it is possible, output one valid rearrangement of $ b $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ x $ ( $ 1 \le n \le 2\cdot 10^5 $ , $ 0 \le x \le n $ ) — the size of arrays $ a $ and $ b $ and the desired beauty of the arrays.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 2n $ ) — the elements of array $ a $ .

The third line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \le b_i \le 2n $ ) — the elements of array $ b $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output "NO" if it is not possible to rearrange $ b $ to make the beauty of the arrays equal to $ x $ .

Otherwise, output "YES". Then, on the next line, output $ n $ integers which represent the rearrangement of $ b $ .

If there are multiple solutions, you may output any of them.

You can output "YES" and "NO" in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

In test cases 1 and 2, the beauty of the arrays has to be $ 0 $ since $ a_1 = 1 \le 2 = b_1 $ .

In test cases 3, 4, 5 and 6, the only possible beauty of the arrays is $ x = 1 $ and $ x = 2 $ . In particular, if $ b $ is rearranged to $ [2, 4, 1] $ , then $ a_3 = 3 > 1 = b_3 $ , so the beauty of the arrays is $ 1 $ . If $ b $ is kept in the same order as given the input, then $ a_2 = 4 > b_2 = 1 $ and $ a_3 = 3 > 2 = b_3 $ , so the beauty of the arrays is $ 2 $ .

## 样例 #1

### 输入

```
7
1 0
1
2
1 1
1
2
3 0
2 4 3
4 1 2
3 1
2 4 3
4 1 2
3 2
2 4 3
4 1 2
3 3
2 4 3
4 1 2
5 2
6 4 5 6 2
9 7 9 1 1
```

### 输出

```
YES
2
NO
NO
YES
2 4 1
YES
4 1 2
NO
YES
1 9 9 7 1
```



---

---
title: "Programming Competition"
layout: "post"
diff: 普及+/提高
pid: CF1914F
tag: ['贪心']
---

# Programming Competition

## 题目描述

BerSoft is the biggest IT corporation in Berland. There are $ n $ employees at BerSoft company, numbered from $ 1 $ to $ n $ .

The first employee is the head of the company, and he does not have any superiors. Every other employee $ i $ has exactly one direct superior $ p_i $ .

Employee $ x $ is considered to be a superior (direct or indirect) of employee $ y $ if one of the following conditions holds:

- employee $ x $ is the direct superior of employee $ y $ ;
- employee $ x $ is a superior of the direct superior of employee $ y $ .

The structure of BerSoft is organized in such a way that the head of the company is superior of every employee.

A programming competition is going to be held soon. Two-person teams should be created for this purpose. However, if one employee in a team is the superior of another, they are uncomfortable together. So, teams of two people should be created so that no one is the superior of the other. Note that no employee can participate in more than one team.

Your task is to calculate the maximum possible number of teams according to the aforementioned rules.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of employees.

The second line contains $ n-1 $ integers $ p_2, p_3, \dots, p_n $ ( $ 1 \le p_i \le n $ ), where $ p_i $ is the index of the direct superior of the $ i $ -th employee.

The sum of $ n $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the maximum possible number of teams according to the aforementioned rules.

## 说明/提示

In the first test case, team $ (3, 4) $ can be created.

In the second test case, no team can be created, because there are only $ 2 $ employees and one is the superior of another.

In the third test case, team $ (2, 3) $ can be created.

In the fourth test case, teams $ (2, 4) $ , $ (3, 5) $ and $ (6, 7) $ can be created.

In the fifth test case, teams $ (2, 3) $ , $ (6, 4) $ and $ (5, 7) $ can be created.

## 样例 #1

### 输入

```
6
4
1 2 1
2
1
5
5 5 5 1
7
1 2 1 1 3 3
7
1 1 3 2 2 4
7
1 2 1 1 1 3
```

### 输出

```
1
0
1
3
3
3
```



---

---
title: "Sum over all Substrings (Easy Version)"
layout: "post"
diff: 普及+/提高
pid: CF1930D1
tag: ['贪心']
---

# Sum over all Substrings (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference between the two versions is the constraint on $ t $ and $ n $ . You can make hacks only if both versions of the problem are solved.

For a binary $ ^\dagger $ pattern $ p $ and a binary string $ q $ , both of length $ m $ , $ q $ is called $ p $ -good if for every $ i $ ( $ 1 \leq i \leq m $ ), there exist indices $ l $ and $ r $ such that:

- $ 1 \leq l \leq i \leq r \leq m $ , and
- $ p_i $ is a mode $ ^\ddagger $ of the string $ q_l q_{l+1} \ldots q_{r} $ .

For a pattern $ p $ , let $ f(p) $ be the minimum possible number of $ \mathtt{1} $ s in a $ p $ -good binary string (of the same length as the pattern).

You are given a binary string $ s $ of size $ n $ . Find $ $$$\sum_{i=1}^{n} \sum_{j=i}^{n} f(s_i s_{i+1} \ldots s_j). $ $  In other words, you need to sum the values of  $ f $  over all  $ \\frac{n(n+1)}{2} $  substrings of  $ s $ .</p><p> $ ^\\dagger $  A binary <span class="tex-font-style-it">pattern</span> is a string that only consists of characters  $ \\mathtt{0} $  and  $ \\mathtt{1} $ .</p><p> $ ^\\ddagger $  Character  $ c $  is a mode of string  $ t $  of length  $ m $  if the number of occurrences of  $ c $  in  $ t $  is at least  $ \\lceil \\frac{m}{2} \\rceil $ . For example,  $ \\mathtt{0} $  is a mode of  $ \\mathtt{010} $ ,  $ \\mathtt{1} $  is not a mode of  $ \\mathtt{010} $ , and both  $ \\mathtt{0} $  and  $ \\mathtt{1} $  are modes of  $ \\mathtt{011010}$$$.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 500 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 100 $ ) — the length of the binary string $ s $ .

The second line of each test case contains a binary string $ s $ of length $ n $ consisting of only characters $ \mathtt{0} $ and $ \mathtt{1} $ .

It is guaranteed that the sum of $ n^2 $ over all test cases does not exceed $ 10^4 $ .

## 输出格式

For each test case, output the sum of values of $ f $ over all substrings of $ s $ .

## 说明/提示

In the first test case, the only $ \mathtt{1} $ -good string is $ \mathtt{1} $ . Thus, $ f(\mathtt{1})=1 $ .

In the second test case, $ f(\mathtt{10})=1 $ because $ \mathtt{01} $ is $ \mathtt{10} $ -good, and $ \mathtt{00} $ is not $ \mathtt{10} $ -good. Thus, the answer is $ f(\mathtt{1})+f(\mathtt{10})+f(\mathtt{0}) = 1 + 1 + 0 = 2 $ .

In the third test case, $ f $ equals to $ 0 $ for all $ 1 \leq i \leq j \leq 5 $ . Thus, the answer is $ 0 $ .

## 样例 #1

### 输入

```
4
1
1
2
10
5
00000
20
11110110000000111111
```

### 输出

```
1
2
0
346
```



---

---
title: "Rudolf and Imbalance"
layout: "post"
diff: 普及+/提高
pid: CF1941F
tag: ['贪心', '二分']
---

# Rudolf and Imbalance

## 题目描述

Rudolf has prepared a set of $ n $ problems with complexities $ a_1 < a_2 < a_3 < \dots < a_n $ . He is not entirely satisfied with the balance, so he wants to add at most one problem to fix it.

For this, Rudolf came up with $ m $ models of problems and $ k $ functions. The complexity of the $ i $ -th model is $ d_i $ , and the complexity of the $ j $ -th function is $ f_j $ . To create a problem, he selects values $ i $ and $ j $ ( $ 1 \le i \le m $ , $ 1 \le j \le k $ ) and by combining the $ i $ -th model with the $ j $ -th function, he obtains a new problem with complexity $ d_i + f_j $ (a new element is inserted into the array $ a $ ).

To determine the imbalance of the set, Rudolf sorts the complexities of the problems in ascending order and finds the largest value of $ a_i - a_{i - 1} $ ( $ i > 1 $ ).

What is the minimum value of imbalance that Rudolf can achieve by adding at most one problem, created according to the described rules?

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The first line of each test case contains three integers $ n $ , $ m $ , and $ k $ ( $ 2 \le n \le 10^5 $ , $ 1 \le m, k \le 2 \cdot 10^5 $ ) — the number of prepared problems, the number of models, and the number of functions, respectively.

The second line of each test case contains $ n $ integers $ a_1, a_2, a_3, \dots a_n $ ( $ 1 \le a_i \le 2 \cdot 10^9 $ , $ a_i < a_{i+1} $ ) — the complexities of the prepared problems.

The third line of each test case contains $ m $ integers $ d_1, d_2, d_3, \dots d_m $ ( $ 1 \le d_i \le 10^9 $ ) — the complexities of the models.

The fourth line of each test case contains $ k $ integers $ f_1, f_2, f_3, \dots f_k $ ( $ 1 \le f_i \le 10^9 $ ) — the complexities of the functions.

It is guaranteed that the sum of $ n $ over all testcases does not exceed $ 10^5 $ .

It is guaranteed that the sum of $ m $ over all testcases does not exceed $ 2 \cdot 10^5 $ .

It is guaranteed that the sum of $ k $ over all testcases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each testcase, output a single number — the minimum imbalance that Rudolf can achieve.

## 样例 #1

### 输入

```
7
5 5 5
5 10 15 20 26
11 14 16 13 8
16 4 5 3 1
7 6 5
1 4 7 10 18 21 22
2 3 5 7 4 2
6 8 9 3 2
7 6 5
1 4 7 10 18 21 22
2 3 5 7 4 2
6 8 13 3 2
5 6 3
2 10 13 20 25
11 6 10 16 14 5
6 17 15
4 2 2
11 12 14 15
19 14
10 6
8 4 2
3 10 16 18 21 22 29 30
9 13 16 15
4 2
2 4 7
4 21
4 15 14 5
20 1 15 1 12 5 11
```

### 输出

```
5
4
5
8
2
7
11
```



---

---
title: "Bessie's Birthday Cake (Hard Version)"
layout: "post"
diff: 普及+/提高
pid: CF1942C2
tag: ['数学', '贪心']
---

# Bessie's Birthday Cake (Hard Version)

## 题目描述

[Proof Geometric Construction Can Solve All Love Affairs - manbo-p](https://soundcloud.com/alice-law-314125270/manbo-p-proof-geometric-construction-can-solve-all-love-affairs)

⠀



This is the hard version of the problem. The only difference between the two versions is the constraint on $ y $ . In this version $ 0 \leq y \leq n - x $ . You can make hacks only if both versions are solved.

Bessie has received a birthday cake from her best friend Elsie, and it came in the form of a regular polygon with $ n $ sides. The vertices of the cake are numbered from $ 1 $ to $ n $ clockwise. You and Bessie are going to choose some of those vertices to cut non-intersecting diagonals into the cake. In other words, the endpoints of the diagonals must be part of the chosen vertices.

Bessie would only like to give out pieces of cake which result in a triangle to keep consistency. The size of the pieces doesn't matter, and the whole cake does not have to be separated into all triangles (other shapes are allowed in the cake, but those will not be counted).

Bessie has already chosen $ x $ of those vertices that can be used to form diagonals. She wants you to choose no more than $ y $ other vertices such that the number of triangular pieces of cake she can give out is maximized.

What is the maximum number of triangular pieces of cake Bessie can give out?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case consists of three integers, $ n $ , $ x $ , and $ y $ ( $ 4 \leq n \leq 10^9 $ , $ 2 \leq x \leq \min(n, 2 \cdot 10^5) $ , $ 0 \leq y \leq n - x $ ) — the number of sides of the polygon, number of vertices Bessie has chosen, and the maximum number of other vertices you can choose.

The second line consists of $ x $ distinct integers from $ 1 $ to $ n $ , representing the vertices Bessie has chosen.

It is guaranteed the sum of $ x $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer: the maximum number of non-intersecting triangular pieces of cake she can give out.

## 说明/提示

In test cases $ 1 $ , $ 2 $ and $ 3 $ , you can get $ 6 $ , $ 5 $ and $ 2 $ non-intersecting triangular pieces of cake, respectively. A possible construction is shown in the following pictures:

The green dots represent vertices that Bessie chose, the yellow dots represent vertices that you chose, the blue lines represent diagonals that are drawn, and the red numbers represent triangles that are counted.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1942C2/1d0397b12ffc5a0058affa34960ac433601c6be3.png)

## 样例 #1

### 输入

```
3
8 4 2
1 6 2 5
7 3 1
6 4 3
4 2 2
1 3
```

### 输出

```
6
5
2
```



---

---
title: "Clique Partition"
layout: "post"
diff: 普及+/提高
pid: CF1948E
tag: ['贪心', '构造']
---

# Clique Partition

## 题目描述

You are given two integers, $ n $ and $ k $ . There is a graph on $ n $ vertices, numbered from $ 1 $ to $ n $ , which initially has no edges.

You have to assign each vertex an integer; let $ a_i $ be the integer on the vertex $ i $ . All $ a_i $ should be distinct integers from $ 1 $ to $ n $ .

After assigning integers, for every pair of vertices $ (i, j) $ , you add an edge between them if $ |i - j| + |a_i - a_j| \le k $ .

Your goal is to create a graph which can be partitioned into the minimum possible (for the given values of $ n $ and $ k $ ) number of cliques. Each vertex of the graph should belong to exactly one clique. Recall that a clique is a set of vertices such that every pair of vertices in it are connected with an edge.

Since BledDest hasn't really brushed his programming skills up, he can't solve the problem "given a graph, partition it into the minimum number of cliques". So we also ask you to print the partition itself.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 1600 $ ) — the number of test cases.

Each test case consists of one line containing two integers $ n $ and $ k $ ( $ 2 \le n \le 40 $ ; $ 1 \le k \le 2n $ ).

## 输出格式

For each test case, print three lines:

- the first line should contain $ n $ distinct integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ) — the values you assign to the vertices;
- the second line should contain one integer $ q $ ( $ 1 \le q \le n $ ) — the number of cliques you partition the graph into;
- the third line should contain $ n $ integers $ c_1, c_2, \dots, c_n $ ( $ 1 \le c_i \le q $ ) — the partition of the graph into cliques. Where two vertices $ u $ and $ v $ are in the same clique if $ c_u = c_v $ .

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
3
2 3
5 4
8 16
```

### 输出

```
2 1
1
1 1
3 1 5 2 4
2
1 1 2 1 2
1 2 3 4 5 6 7 8
1
1 1 1 1 1 1 1 1
```



---

---
title: "Missing Subsequence Sum"
layout: "post"
diff: 普及+/提高
pid: CF1965B
tag: ['贪心', '构造']
---

# Missing Subsequence Sum

## 题目描述

给定两个整数 $n,k$，你需要构造出一个长度不超过 $25$ 的数组 $a$，并满足以下条件：

* $a$ 中任意子序列元素和不为 $k$。

* $a$ 中所有子序列和可以表示 $1\sim n$ 中除了 $k$ 以外的任意整数。

子序列表示一个序列中任意一些元素按顺序组成的序列，比如 $[5,2,3]$ 是 $[1,5,7,8,2,4,3]$ 的子序列。

可以证明一定存在这样的方案。

## 输入格式

第一行一个整数 $t$，表示数据组数。

接下来 $t$ 行，每行两个整数 $n,k$。

## 输出格式

共 $t$ 组数据，每组数据共两行。

第一行一个整数 $m$ 表示你构造的序列长度。

接下来一行 $m$ 个整数表示你构造的数列，其中第 $i$ 个数表示 $a_i$。

## 说明/提示

对于全部数据，满足 $1\le t\le1000$，$1\le k\le n\le10^6$，$1\le \sum n\le10^7$。

你构造的数列需要满足 $1\le m\le25$，$0\le a_i\le10^9$。

## 样例 #1

### 输入

```
5
2 2
6 1
8 8
9 3
10 7
```

### 输出

```
1
1
5
2 3 4 5 6
7
1 1 1 1 1 1 1
4
7 1 4 1
4
1 2 8 3
```



---

---
title: "Equal XOR Segments"
layout: "post"
diff: 普及+/提高
pid: CF1968F
tag: ['贪心', '位运算']
---

# Equal XOR Segments

## 题目描述

Let us call an array $ x_1,\dots,x_m $ interesting if it is possible to divide the array into $ k>1 $ parts so that [bitwise XOR](http://tiny.cc/xor_wiki_eng) of values from each part are equal.

More formally, you must split array $ x $ into $ k $ consecutive segments, each element of $ x $ must belong to exactly $ 1 $ segment. Let $ y_1,\dots,y_k $ be the XOR of elements from each part respectively. Then $ y_1=y_2=\dots=y_k $ must be fulfilled.

For example, if $ x = [1, 1, 2, 3, 0] $ , you can split it as follows: $ [\color{blue}1], [\color{green}1], [\color{red}2, \color{red}3, \color{red}0] $ . Indeed $ \color{blue}1=\color{green}1=\color{red}2 \oplus \color{red}3\oplus \color{red}0 $ .

You are given an array $ a_1,\dots,a_n $ . Your task is to answer $ q $ queries:

- For fixed $ l $ , $ r $ , determine whether the subarray $ a_l,a_{l+1},\dots,a_r $ is interesting.

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 2 \le n \le 2 \cdot 10^5 $ , $ 1 \le q \le 2 \cdot 10^5 $ ) — the number of elements in the array and the number of queries respectively.

The next line contains $ n $ integers $ a_1,\dots,a_n $ ( $ 0 \le a_i < 2^{30} $ ) — elements of the array.

Each of the next $ q $ lines contains two integers $ l $ and $ r $ ( $ 1 \le l < r \le n $ ) describing the query.

It is guaranteed that the sum of $ n $ over all testcases does not exceed $ 2 \cdot 10^5 $ .

It is guaranteed that the sum of $ q $ over all testcases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each query, output "YES" if the subarray is interesting and "NO" otherwise.

You can output "Yes" and "No" in any case (for example, the strings "yES", "yes", and "Yes" will be recognized as correct answers).

## 说明/提示

Explanation for the first test case:

The first query is described in the statement.

In the second query, we should divide $ [1,2,3] $ . A possible division is $ [1,2],[3] $ , since $ 1\oplus 2=3 $ .

It can be shown that for queries $ 3,4,5 $ , the subarrays are not interesting.

## 样例 #1

### 输入

```
4
5 5
1 1 2 3 0
1 5
2 4
3 5
1 3
3 4
5 5
1 2 3 4 5
1 5
2 4
3 5
1 3
2 3
7 4
12 9 10 9 10 11 9
1 5
1 7
2 6
2 7
11 4
0 0 1 0 0 1 0 1 1 0 1
1 2
2 5
6 9
7 11
```

### 输出

```
YES
YES
NO
NO
NO

YES
NO
NO
YES
NO

NO
NO
NO
NO

YES
NO
YES
YES
```



---

---
title: "Shop Game"
layout: "post"
diff: 普及+/提高
pid: CF1969D
tag: ['贪心', '堆']
---

# Shop Game

## 题目描述

Alice 和 Bob 正在商店里玩游戏。商店里有 $n$ 件商品；每件商品有两个参数： $a_i$（Alice 买进的物品价格）和 $b_i$（愿意出的物品价格）。

Alice 希望选择一个商品子集（可能是空）并购买它们。之后，Bob 会执行以下操作：

- 如果 Alice 购买的物品少于 $k$，Bob 可以免费拿走所有物品；
- 否则，他会免费拿走 Alice 购买的 $k$ 个物品（由 Bob 选择是哪些 $k$ 个物品），至于其他被选中的物品，Bob 会从 Alice 那里购买，并为 $i$ 号物品支付 $b_i$。

Alice 的利润等于 $\sum\limits_{i\in S}b_i-\sum\limits_{j \in T}a_j$，其中 $S$ 是 Bob 从 Alice 处购买的物品集，$T$ 是 Alice 从商店购买的物品集。换句话说，Alice 的利润就是 Bob 支付给她的金额和她购买商品所花费的金额之间的差额。

Alice 希望自己的利润最大化，而 Bob 希望 Alice 的利润最小化。您的任务是计算在 Alice 和 Bob 都采取最优行动的情况下 Alice 的利润。

## 输入格式

第一行包含一个整数 $ t $ （ $ 1 \le t \le 10^4 $ )——测试用例的数量。

每个测试用例的第一行包含两个整数 $ n $ 和 $ k $ （ $ 1 \le n \le 2 \cdot 10^5 $，$ 0 \le k \le n $ ）。

第二行包含 $ n $ 整数 $ a_1, a_2, \dots, a_n $ （ $ 1 \le a_i \le 10^9 $ ）。

第三行包含 $ n $ 整数 $ b_1, b_2, \dots, b_n $ （ $ 1 \le b_i \le 10^9 $ ）。

## 输出格式

对于每个测试用例，打印一个整数——如果Alice和Bob都采取最优行为，则Alice的利润。

## 说明/提示

在第一个测试用例中，Alice应该购买 $ 2 $ 然后把它卖给鲍勃，那么她的利润是 $ 2 - 1 = 1 $ 。

在第二个测试用例中，Alice应该购买 $ 1 $，$ 2 $ 和 $ 3 $ 项；然后鲍勃可以接受 $ 1 $ 免费，并支付 $ 2 $ 和 $ 3 $ 。Alice的利润是 $ (3+2) - (1+2+1) = 1 $ 。鲍勃也可以接受 $ 2 $ 为免费的物品，这不会改变Alice的利润。鲍勃不会接受 $ 3 $ 为免费的物品，因为这样 Alice 的利润为 $ 2 $。

## 样例 #1

### 输入

```
4
2 0
2 1
1 2
4 1
1 2 1 4
3 3 2 3
4 2
2 1 1 1
4 2 3 2
6 2
1 3 4 9 1 3
7 6 8 10 6 8
```

### 输出

```
1
1
0
7
```



---

---
title: "Money Buys Less Happiness Now"
layout: "post"
diff: 普及+/提高
pid: CF1974G
tag: ['贪心']
---

# Money Buys Less Happiness Now

## 题目描述

You can never buy enough happiness, so here we go again! In this version, you can only buy $ h_i = 1 $ unit of happiness each month, but the number of months is hugely increased. We are in the realm of quantum happiness and time dilation.

Being a physicist, Charlie likes to plan his life in simple and precise terms.

For the next $ m $ months, starting with no money, Charlie will work hard and earn $ x $ pounds per month. For the $ i $ -th month $ (1 \le i \le m) $ , there'll be a single opportunity of paying cost $ c_i $ pounds to obtain one unit of happiness. You cannot buy more than one unit each month.

Borrowing is not allowed. Money earned in the $ i $ -th month can only be spent in a later $ j $ -th month ( $ j>i $ ).

Since physicists don't code, help Charlie find the maximum reachable units of happiness.

## 输入格式

The first line of the input contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers, $ m $ and $ x $ ( $ 1 \le m \le 2 \cdot 10^5 $ , $ 1 \le x \le 10^3 $ ) — the total number of months and the monthly salary.

The second line of each test case contains $ m $ integers $ c_1, c_2, \dots, c_m $ ( $ 1 \leq c_i \leq 10^3 $ ) — the cost of one unit of happiness for each month.

It is guaranteed that sum of $ m $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output one integer — the maximal amount of happiness Charlie can get.

## 样例 #1

### 输入

```
6
3 3
2 2 2
6 5
2 2 8 2 6 8
6 4
4 10 3 8 6 10
2 1
1 1
4 1
4 1 3 1
4 2
1 3 4 3
```

### 输出

```
2
4
3
1
2
1
```



---

---
title: "Paint the Tree"
layout: "post"
diff: 普及+/提高
pid: CF1975D
tag: ['贪心', '树形数据结构']
---

# Paint the Tree

## 题目描述

378QAQ has a tree with $ n $ vertices. Initially, all vertices are white.

There are two chess pieces called $ P_A $ and $ P_B $ on the tree. $ P_A $ and $ P_B $ are initially located on vertices $ a $ and $ b $ respectively. In one step, 378QAQ will do the following in order:

1. Move $ P_A $ to a neighboring vertex. If the target vertex is white, this vertex will be painted red.
2. Move $ P_B $ to a neighboring vertex. If the target vertex is colored in red, this vertex will be painted blue.

Initially, the vertex $ a $ is painted red. If $ a=b $ , the vertex $ a $ is painted blue instead. Note that both the chess pieces must be moved in each step. Two pieces can be on the same vertex at any given time.

378QAQ wants to know the minimum number of steps to paint all vertices blue.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1\leq t\leq 10^4 $ ). The description of the test cases follows.

The first line of each test case contains one integer $ n $ ( $ 1\leq n\leq 2\cdot 10^5 $ ).

The second line of each test case contains two integers $ a $ and $ b $ ( $ 1\leq a,b\leq n $ ).

Then $ n - 1 $ lines follow, each line contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i,y_i \le n $ ), indicating an edge between vertices $ x_i $ and $ y_i $ . It is guaranteed that these edges form a tree.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output the minimum number of steps to paint all vertices blue.

## 说明/提示

In the first test case, 378QAQ can paint all vertices blue in the following order:

- Initially, $ P_A $ is located on the vertex $ 1 $ , and $ P_B $ is located on the vertex $ 2 $ . The vertex $ 1 $ is painted red and the vertex $ 2 $ is white.
- 378QAQ moves $ P_A $ to the vertex $ 2 $ and paints it red. Then 378QAQ moves $ P_B $ to the vertex $ 1 $ and paints it blue.
- 378QAQ moves $ P_A $ to the vertex $ 1 $ . Then 378QAQ moves $ P_B $ to the vertex $ 2 $ and paints it blue.

## 样例 #1

### 输入

```
3
2
1 2
1 2
5
1 2
1 2
1 3
1 4
1 5
8
5 4
7 1
1 5
1 8
8 3
7 2
8 6
3 4
```

### 输出

```
2
8
13
```



---

---
title: "Job Interview"
layout: "post"
diff: 普及+/提高
pid: CF1976C
tag: ['动态规划 DP', '贪心']
---

# Job Interview

## 题目描述

### 题意翻译
Monocarp 要开设一家 IT 公司。他想招聘 $n$ 名程序员和 $m$ 名测试员。

共有 $n+m+1$ 名候选人，第 $i$ 个人的到达时间为 $i$。

第 $i$ 名候选人的编程技能为 $a_i$ ，测试技能为 $b_i$ （保证 $a_i\not=b_i$）。

公司的能力定义为所有程序员的编程能力与所有测试员的测试能力之和。

形式化的讲，若招聘的程序员集合为 $s$，测试员集合为 $t$，则公司的能力为 $\sum\limits_{i\in s}a_i+\sum\limits_{j\in t}b_j$。

Monocarp 会按照候选人到达的时间顺序为他们分配工作。

对于第 $i$ 个人，招聘规则为：
1. 尝试将 $i$ 分配到最适合 $i$ 的职位，也就是若 $a_i>b_i$，则让他成为程序员，反之同理。
2. 如果该职位已经招满了，就把 $i$ 分配到另一职位上。

你的任务是，对于每个 $i$，输出若这个人不来的情况下，公司的能力值。

## 输入格式

先是一个数字 $t$ 表示数据组数。

对于每组数据：

先输入两个数字 $n,m$ 表示要招聘的程序员/测试员数量。

接着 $n+m+1$ 个数表示每个人的编程能力。

再是 $n+m+1$ 个数表示每个人的测试能力。

## 输出格式

对于每组数据：输出 $n+m+1$ 个数，第 $i$ 个数表示去掉第 $i$ 个人时公司的能力值。

translate by Hoks。

## 样例 #1

### 输入

```
4
1 0
2 1
1 2
0 2
4 5 5
5 4 1
1 2
2 1 5 4
5 2 3 1
3 1
4 3 3 4 1
5 5 4 5 2
```

### 输出

```
1 2 
5 6 9 
8 11 11 12 
13 13 13 12 15
```



---

---
title: "Computing Machine"
layout: "post"
diff: 普及+/提高
pid: CF1978E
tag: ['贪心']
---

# Computing Machine

## 题目描述

给定长度为 $n$ 的二进制字符串 $s,t$，串内只包含 $0$ 和 $1$，现有 $q$ 次询问，每次给出一个区间 $[l,r]$，分别记 $s,t$ 在 $[l,r]$ 上的子串为 $a,b$，进行任意次如下两种操作：
 - 若 $\exist i,i+2\in[l,r]$ 使得 $a_i=a_{i+2}=0$，则可以使 $b_{i+1}$ 的值变为 $1$。
 - 若 $\exist i,i+2\in[l,r]$ 使得 $b_i=b_{i+2}=1$，则可以使 $a_{i+1}$ 的值变为 $1$。

现求所有操作结束后，串 $a$ 内最多可以包含多少 $1$。

## 输入格式

一个测试点包含多组测试数据，第一行给出 $t(1\leq t \leq 10^4)$，表示测试数据组数。  
对于每组数据：  
第一行给出一个整数 $n(1\leq n \leq 2\times 10^5)$。  
第二、三行给出两个二进制字符串 $s,t$。  
第四行给出一个整数 $q$ 表示询问个数。  
接下来 $q$ 行，每行两个整数 $l,r$，表示询问区间为 $[l,r]$。

保证 $\sum n$ 和 $\sum q$ 均不超过 $2 \times 10 ^ 5$。

## 输出格式

$q$ 行，每行一个整数，表示对应询问的答案。

## 样例 #1

### 输入

```
3
4
1111
0000
2
1 2
2 4
4
1010
1101
2
1 3
1 4
6
010101
011010
5
2 3
1 6
2 5
4 4
3 6
```

### 输出

```
2
3
2
3
1
4
3
1
2
```



---

---
title: "Fixing a Binary String"
layout: "post"
diff: 普及+/提高
pid: CF1979D
tag: ['贪心', '哈希 hashing']
---

# Fixing a Binary String

## 题目描述

You are given a binary string $ s $ of length $ n $ , consisting of zeros and ones. You can perform the following operation exactly once:

1. Choose an integer $ p $ ( $ 1 \le p \le n $ ).
2. Reverse the substring $ s_1 s_2 \ldots s_p $ . After this step, the string $ s_1 s_2 \ldots s_n $ will become $ s_p s_{p-1} \ldots s_1 s_{p+1} s_{p+2} \ldots s_n $ .
3. Then, perform a cyclic shift of the string $ s $ to the left $ p $ times. After this step, the initial string $ s_1s_2 \ldots s_n $ will become $ s_{p+1}s_{p+2} \ldots s_n s_p s_{p-1} \ldots s_1 $ .

For example, if you apply the operation to the string 110001100110 with $ p=3 $ , after the second step, the string will become 011001100110, and after the third step, it will become 001100110011.

A string $ s $ is called  $ k $ -proper if two conditions are met:

- $ s_1=s_2=\ldots=s_k $ ;
- $ s_{i+k} \neq s_i $ for any $ i $ ( $ 1 \le i \le n - k $ ).

For example, with $ k=3 $ , the strings 000, 111000111, and 111000 are $ k $ -proper, while the strings 000000, 001100, and 1110000 are not.

You are given an integer $ k $ , which is a divisor of $ n $ . Find an integer $ p $ ( $ 1 \le p \le n $ ) such that after performing the operation, the string $ s $ becomes $ k $ -proper, or determine that it is impossible. Note that if the string is initially $ k $ -proper, you still need to apply exactly one operation to it.

## 输入格式

Each test consists of multiple test cases. The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le k \le n $ , $ 2 \le n \le 10^5 $ ) — the length of the string $ s $ and the value of $ k $ . It is guaranteed that $ k $ is a divisor of $ n $ .

The second line of each test case contains a binary string $ s $ of length $ n $ , consisting of the characters 0 and 1.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the value of $ p $ to make the string $ k $ -proper, or $ -1 $ if it is impossible.

If there are multiple solutions, output any of them.

## 说明/提示

In the first test case, if you apply the operation with $ p=3 $ , after the second step of the operation, the string becomes 11100001, and after the third step, it becomes 00001111. This string is $ 4 $ -proper.

In the second test case, it can be shown that there is no operation after which the string becomes $ 2 $ -proper.

In the third test case, if you apply the operation with $ p=7 $ , after the second step of the operation, the string becomes 100011100011, and after the third step, it becomes 000111000111. This string is $ 3 $ -proper.

In the fourth test case, after the operation with any $ p $ , the string becomes $ 5 $ -proper.

## 样例 #1

### 输入

```
7
8 4
11100001
4 2
1110
12 3
111000100011
5 5
00000
6 1
101001
8 4
01110001
12 2
110001100110
```

### 输出

```
3
-1
7
5
4
-1
3
```



---

---
title: "Turtle and an Incomplete Sequence"
layout: "post"
diff: 普及+/提高
pid: CF1981C
tag: ['贪心', '最近公共祖先 LCA']
---

# Turtle and an Incomplete Sequence

## 题目描述

Turtle was playing with a sequence $ a_1, a_2, \ldots, a_n $ consisting of positive integers. Unfortunately, some of the integers went missing while playing.

Now the sequence becomes incomplete. There may exist an arbitrary number of indices $ i $ such that $ a_i $ becomes $ -1 $ . Let the new sequence be $ a' $ .

Turtle is sad. But Turtle remembers that for every integer $ i $ from $ 1 $ to $ n - 1 $ , either $ a_i = \left\lfloor\frac{a_{i + 1}}{2}\right\rfloor $ or $ a_{i + 1} = \left\lfloor\frac{a_i}{2}\right\rfloor $ holds for the original sequence $ a $ .

Turtle wants you to help him complete the sequence. But sometimes Turtle makes mistakes, so you need to tell him if you can't complete the sequence.

Formally, you need to find another sequence $ b_1, b_2, \ldots, b_n $ consisting of positive integers such that:

- For every integer $ i $ from $ 1 $ to $ n $ , if $ a'_i \ne -1 $ , then $ b_i = a'_i $ .
- For every integer $ i $ from $ 1 $ to $ n - 1 $ , either $ b_i = \left\lfloor\frac{b_{i + 1}}{2}\right\rfloor $ or $ b_{i + 1} = \left\lfloor\frac{b_i}{2}\right\rfloor $ holds.
- For every integer $ i $ from $ 1 $ to $ n $ , $ 1 \le b_i \le 10^9 $ .

If there is no sequence $ b_1, b_2, \ldots, b_n $ that satisfies all of the conditions above, you need to report $ -1 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the length of the sequence.

The second line of each test case contains $ n $ integers $ a'_1, a'_2, \ldots, a'_n $ ( $ a'_i = -1 $ or $ 1 \le a'_i \le 10^8 $ ) — the elements of the sequence $ a' $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, if there is no sequence $ b_1, b_2, \ldots, b_n $ that satisfies all of the conditions, output a single integer $ -1 $ .

Otherwise, output $ n $ integers $ b_1, b_2, \ldots, b_n $ — the elements of the sequence $ b_1, b_2, \ldots, b_n $ you find. The sequence should satisfy that $ 1 \le b_i \le 10^9 $ for every integer $ i $ from $ 1 $ to $ n $ . If there are multiple answers, print any of them.

## 说明/提示

In the first test case, $ [4, 2, 1, 2, 1, 2, 1, 3] $ can also be the answer, while $ [4, 2, 5, 10, 5, 2, 1, 3] $ and $ [4, 2, 1, 2, 1, 2, 1, 4] $ cannot.

In the second test case, $ [1, 2, 5, 2] $ can also be the answer.

From the fourth to the sixth test cases, it can be shown that there is no answer, so you should output $ -1 $ .

## 样例 #1

### 输入

```
9
8
-1 -1 -1 2 -1 -1 1 -1
4
-1 -1 -1 -1
6
3 -1 -1 -1 9 -1
4
-1 5 -1 6
4
2 -1 -1 3
4
1 2 3 4
2
4 2
5
-1 3 -1 3 6
13
-1 -1 3 -1 -1 -1 -1 7 -1 -1 3 -1 -1
```

### 输出

```
4 9 4 2 4 2 1 2
7 3 6 13
3 1 2 4 9 18
-1
-1
-1
4 2
6 3 1 3 6
3 1 3 1 3 7 3 7 3 1 3 1 3
```



---

---
title: "Magnitude (Hard Version)"
layout: "post"
diff: 普及+/提高
pid: CF1984C2
tag: ['动态规划 DP', '贪心']
---

# Magnitude (Hard Version)

## 题目描述

**注意：** 本题的两个版本题意是有不同的，你可能需要同时阅读两个版本的题意。

给定一个长度为 $n$ 的数组 $a$。初始有 $c=0$；接下来，对每个在 $1$ 到 $n$ 范围内的 $i$（按递增的顺序） ，要执行以下两种操作中的恰好一种：

- 操作 $1$：将 $c$ 修改为 $c+a_i$。

- 操作 $2$：将 $c$ 修改为 $|c+a_i|$，这里 $|x|$ 表示 $x$ 的绝对值。

令所有操作后 $c$ 能取得的最大值为 $k$，你需要求出有多少种本质不同的方案使得 $c=k$。这里两个方案被视为不同，当且仅当存在一个 $i$ 使得其中一个方案选了操作 $1$ 而另一个选了操作 $2$，即便这步操作后两个方案对应的 $c$ 相等。

由于答案可能很大，请输出答案对 $998244353$ 取模后的结果。

## 输入格式

第一行为一个正整数 $t\;(1\leq t\leq 10^4)$，表示测试数据的组数。

接下来的每组测试数据，第一行为一个正整数 $n\;(1\leq n\leq 2\cdot10^5)$，

第二行为 $n$ 个整数 $a_1,a_2,\cdots,a_n\;(-10^9\leq a_i\leq 10^9)$。

## 输出格式

对每组测试数据，输出一个整数，表示本质不同的方案数对 $998244353$ 取模的结果。

保证所有测试数据的 $n$ 之和不超过 $3\cdot10^5$。

## 样例 #1

### 输入

```
5
4
2 -5 3 -3
8
1 4 3 4 1 4 3 4
3
-1 -2 -3
4
-1000000000 1000000000 1000000000 1000000000
4
1 9 8 4
```

### 输出

```
12
256
1
8
16
```



---

---
title: "Valuable Cards"
layout: "post"
diff: 普及+/提高
pid: CF1992F
tag: ['贪心', '数论']
---

# Valuable Cards

## 题目描述

In his favorite cafe Kmes once again wanted to try the herring under a fur coat. Previously, it would not have been difficult for him to do this, but the cafe recently introduced a new purchasing policy.

Now, in order to make a purchase, Kmes needs to solve the following problem: $ n $ cards with prices for different positions are laid out in front of him, on the $ i $ -th card there is an integer $ a_i $ , among these prices there is no whole positive integer $ x $ .

Kmes is asked to divide these cards into the minimum number of bad segments (so that each card belongs to exactly one segment). A segment is considered bad if it is impossible to select a subset of cards with a product equal to $ x $ . All segments, in which Kmes will divide the cards, must be bad.

Formally, the segment $ (l, r) $ is bad if there are no indices $ i_1 < i_2 < \ldots < i_k $ such that $ l \le i_1, i_k \le r $ , and $ a_{i_1} \cdot a_{i_2} \ldots \cdot a_{i_k} = x $ .

Help Kmes determine the minimum number of bad segments in order to enjoy his favorite dish.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^3 $ ) — the number of test cases.

The first line of each set of input data gives you $ 2 $ integers $ n $ and $ x $ ( $ 1 \le n \le 10^5, 2 \le x \le 10^5 $ ) — the number of cards and the integer, respectively.

The second line of each set of input data contains $ n $ integers $ a_i $ ( $ 1 \le a_i \le 2 \cdot 10^5, a_i \neq x $ ) — the prices on the cards.

It is guaranteed that the sum of $ n $ over all sets of test data does not exceed $ 10^5 $ .

## 输出格式

For each set of input data, output the minimum number of bad segments.

## 样例 #1

### 输入

```
8
6 4
2 3 6 2 1 2
9 100000
50000 25000 12500 6250 3125 2 4 8 16
5 2
1 1 1 1 1
8 6
4 3 4 3 4 3 4 3
7 12
6 11 1 3 11 10 2
10 5
2 4 4 2 4 4 4 3 1 1
7 8
4 6 5 1 2 4 1
8 27
3 9 17 26 2 20 9 3
```

### 输出

```
3
2
1
1
2
1
3
3
```



---

---
title: "Wooden Game"
layout: "post"
diff: 普及+/提高
pid: CF1994E
tag: ['贪心', '位运算']
---

# Wooden Game

## 题目描述

### 题目大意

给定一个有根树森林 $K=\left\{T_1,T_2,\dots,T_k\right\}$。Timofey 可以移除森林中任意树的子树，然后将其加入森林。

求 Timofey 通过任意次操作，所能得到的 
$$
\bigvee_{i=1}^{|K|}\left|T_i\right|
$$
的最大值，其中 $\bigvee$ 表示按位或。

## 输入格式

输入数据的第一行包括一个整数 $t\left(1\le t\le10^4\right)$，表示测试用例的组数。

对于每个测试用例：

第一行包括一个整数$k\left(1\le k\le10^6\right)$，表示初始状态下森林中树的数目。

接下来 $2k$ 行依次描述了 $k$ 颗树。对于每颗树：

- 第一行包括一个整数 $n\left(1\le n\le10^6\right)$，表示树中结点的数目。
- 第二行包括 $n-1$ 个整数 $p_2,p_3,\dots,p_n$ $\left(1\le p_i<i\right)$。其中，$p_i$ 表示结点 $i$ 的父亲。
- 特别地，当  $n=1$ 时，第二行为空行。

输入数据保证 $\sum n,\sum k\le10^6$

## 输出格式

对于每个测试用例，输出一行一个整数，表示能得到的最大值。

## 样例 #1

### 输入

```
3
1
1


2
4
1 2 2
6
1 1 3 1 3
1
10
1 2 2 1 1 5 7 6 4
```

### 输出

```
1
7
10
```



---

---
title: "Bouquet (Hard Version)"
layout: "post"
diff: 普及+/提高
pid: CF1995B2
tag: ['数学', '贪心']
---

# Bouquet (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference is that in this version, instead of listing the number of petals for each flower, the number of petals and the quantity of flowers in the store is set for all types of flowers.

A girl is preparing for her birthday and wants to buy the most beautiful bouquet. There are a total of $ n $ different types of flowers in the store, each of which is characterized by the number of petals and the quantity of this type of flower. A flower with $ k $ petals costs $ k $ coins. The girl has decided that the difference in the number of petals between any two flowers she will use to decorate her cake should not exceed one. At the same time, the girl wants to assemble a bouquet with the maximum possible number of petals. Unfortunately, she only has $ m $ coins, and she cannot spend more. What is the maximum total number of petals she can assemble in the bouquet?

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10\,000 $ ) — the number of test cases. This is followed by descriptions of the test cases.

The first line of each test case contains two integers $ n $ , $ m $ ( $ 1 \le n \le 2 \cdot 10^5, 1 \le m \le 10^{18} $ ) — the number of types of flowers in the store and the number of coins the girl possesses, respectively. The second line of each test case contains $ n $ different integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ), where $ a_i $ is the number of petals of the $ i $ -th flower type in the store (for different indexes $ i \neq j $ , it must be $ a_i \neq a_j $ ). The third line of each test case contains $ n $ integers $ c_1, c_2, \ldots, c_n $ ( $ 1 \le c_i \le 10^9 $ ), where $ c_i $ is the quantity of the $ i $ -th flower type in the store.

The sum of $ n $ over all test cases does not exceed $ 2 \cdot {10}^5 $ .

## 输出格式

For each test case, print one integer — the maximum possible number of petals in a bouquet that a girl can collect, observing all the conditions listed above.

## 说明/提示

In the first test case, some valid bouquets are $ (1, 1, 2, 2), (2, 2, 3), (1, 1), (2, 2) $ . The maximum over all valid bouquets not greater than $ 10 $ is $ 7 $ for $ (2, 2, 3) $ . In the second test case, you can assemble a valid bouquet with $ (206, 206, 207, 207, 207) $ with a sum of $ 1033 $ , which is the maximum number of petals the girl can buy. In the third test case, you can assemble a valid bouquet with $ (5, 5, 5, 4) $ with a sum of $ 19 $ . It can be seen that no valid bouquet can have $ 20 $ petals.

## 样例 #1

### 输入

```
7
3 10
1 2 3
2 2 1
3 1033
206 207 1000
3 4 1
6 20
4 2 7 5 6 1
1 2 1 3 1 7
8 100000
239 30 610 122 24 40 8 2
12 13123 112 1456 124 100 123 10982
6 13
2 4 11 1 3 5
2 2 1 2 2 1
8 10330
206 210 200 201 198 199 222 1000
9 10 11 12 13 14 15 16
2 10000000000
11 12
87312315 753297050
```

### 输出

```
7
1033
19
99990
13
10000
9999999999
```



---

---
title: "Perform Operations to Maximize Score"
layout: "post"
diff: 普及+/提高
pid: CF1998C
tag: ['贪心', '二分']
---

# Perform Operations to Maximize Score

## 题目描述

I see satyam343. I'm shaking. Please more median problems this time. I love those. Please satyam343 we believe in you.

— satyam343's biggest fan



You are given an array $ a $ of length $ n $ and an integer $ k $ . You are also given a binary array $ b $ of length $ n $ .

You can perform the following operation at most $ k $ times:

- Select an index $ i $ ( $ 1 \leq i \leq n $ ) such that $ b_i = 1 $ . Set $ a_i = a_i + 1 $ (i.e., increase $ a_i $ by $ 1 $ ).

Your score is defined to be $ \max\limits_{i = 1}^{n} \left( a_i + \operatorname{median}(c_i) \right) $ , where $ c_i $ denotes the array of length $ n-1 $ that you get by deleting $ a_i $ from $ a $ . In other words, your score is the maximum value of $ a_i + \operatorname{median}(c_i) $ over all $ i $ from $ 1 $ to $ n $ .

Find the maximum score that you can achieve if you perform the operations optimally.

For an arbitrary array $ p $ , $ \operatorname{median}(p) $ is defined as the $ \left\lfloor \frac{|p|+1}{2} \right\rfloor $ -th smallest element of $ p $ . For example, $ \operatorname{median} \left( [3,2,1,3] \right) = 2 $ and $ \operatorname{median} \left( [6,2,4,5,1] \right) = 4 $ .

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

Each test case begins with two integers $ n $ and $ k $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ , $ 0 \leq k \leq 10^9 $ ) — the length of the $ a $ and the number of operations you can perform.

The following line contains $ n $ space separated integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — denoting the array $ a $ .

The following line contains $ n $ space separated integers $ b_1, b_2, \ldots, b_n $ ( $ b_i $ is $ 0 $ or $ 1 $ ) — denoting the array $ b $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the maximum value of score you can get on a new line.

## 说明/提示

For the first test case, it is optimal to perform $ 5 $ operations on both elements so $ a = [8,8] $ . So, the maximum score we can achieve is $ \max(8 + \operatorname{median}[8], 8 + \operatorname{median}[8]) = 16 $ , as $ c_1 = [a_2] = [8] $ . It can be proven that you cannot get a better score.

For the second test case, you are not able to perform operations on any elements, so $ a $ remains $ [3,3,3] $ . So, the maximum score we can achieve is $ 3 + \operatorname{median}[3, 3] = 6 $ , as $ c_1 = [a_2, a_3] = [3, 3] $ . It can be proven that you cannot get a better score.

## 样例 #1

### 输入

```
8
2 10
3 3
1 1
3 10
3 3 3
0 0 0
4 4
2 1 5 1
0 1 0 1
5 4
7 5 2 5 4
0 0 1 0 1
5 1
5 15 15 2 11
1 0 0 1 1
5 2
10 11 4 10 15
1 1 0 1 0
4 4
1 1 2 5
1 1 0 0
2 1000000000
1000000000 1000000000
1 1
```

### 输出

```
16
6
8
13
21
26
8
3000000000
```



---

---
title: "Turtle and a MEX Problem (Hard Version)"
layout: "post"
diff: 普及+/提高
pid: CF2003D2
tag: ['动态规划 DP', '贪心']
---

# Turtle and a MEX Problem (Hard Version)

## 题目描述

两个版本的问题是不同的。在这个版本的问题中，你不能选择同一个整数两次或更多次。只有当两个版本都解决时，才能进行 hack。

有一天，乌龟正在玩 $n$ 个序列。设第 $i$ 个序列的长度为 $l_i$，则第 $i$ 个序列为 $a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i}$。

当乌龟在玩耍时，小猪给了他一个问题来解决。问题的陈述如下：

- 最初有一个非负整数 $x$。乌龟可以对这个整数执行任意次数（可能为零）的操作。
- 在每次操作中，乌龟可以选择一个之前未被选择过的整数 $i$（满足 $1 \le i \le n$），并将 $x$ 设为 $\text{mex}^{\dagger}(x, a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i})$。
- 乌龟被要求找到答案，即在执行任意次数操作后 $x$ 的最大值。

乌龟轻松解决了上述问题。他定义 $f(k)$ 为初始值 $x$ 为 $k$ 时上述问题的答案。

然后小猪给了乌龟一个非负整数 $m$，并要求乌龟找出 $\sum\limits_{i = 0}^m f(i)$ 的值（即 $f(0) + f(1) + \ldots + f(m)$ 的值）。不幸的是，他无法解决这个问题。请帮助他！

$\text{mex}(c_1, c_2, \ldots, c_k)$ 定义为不在序列 $c$ 中出现的最小非负整数 $x$。例如，$\text{mex}(2, 2, 0, 3)$ 是 $1$，$\text{mex}(1, 2)$ 是 $0$。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是测试用例的描述。

每个测试用例的第一行包含两个整数 $n, m$（$1 \le n \le 2 \cdot 10^5, 0 \le m \le 10^9$）。

接下来的 $n$ 行每行包含若干个整数。第一个整数 $l_i$（$1 \le l_i \le 2 \cdot 10^5$）表示第 $i$ 个序列的长度，后面跟着 $l_i$ 个整数 $a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i}$（$0 \le a_{i, j} \le 10^9$）表示第 $i$ 个序列的元素。

保证所有测试用例中的 $n$ 之和不超过 $2 \cdot 10^5$，并且所有测试用例中的 $\sum l_i$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数 —— $\sum\limits_{i = 0}^m f(i)$ 的值。

## 说明/提示

在第一个测试用例中，当 $x$ 初始值为 $2$ 时，乌龟可以选择 $i = 3$ 并将 $x$ 设为 $\text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}) = \text{mex}(2, 7, 0, 1, 5) = 3$。可以证明乌龟无法使 $x$ 的值大于 $3$，因此 $f(2) = 3$。

可以看出 $f(0) = 3$，$f(1) = 3$，$f(2) = 3$，$f(3) = 3$，$f(4) = 4$。所以 $f(0) + f(1) + f(2) + f(3) + f(4) = 3 + 3 + 3 + 3 + 4 = 16$。

在第二个测试用例中，当 $x$ 初始值为 $1$ 时，乌龟可以选择 $i = 1$ 并将 $x$ 设为 $\text{mex}(x, a_{1, 1}, a_{1, 2}, a_{1, 3}, a_{1, 4}, a_{1, 5}) = \text{mex}(1, 0, 2, 0, 4, 11) = 3$。可以证明乌龟无法使 $x$ 的值大于 $3$，因此 $f(1) = 3$。

可以看出 $f(0) = 4$，$f(1) = 3$，$f(2) = 4$，$f(3) = 3$，$f(4) = 4$。所以 $f(0) + f(1) + f(2) + f(3) + f(4) = 4 + 3 + 4 + 3 + 4 = 18$。

在第四个测试用例中，可以看出 $f(0) = 3$ 和 $f(1) = 1$。所以 $f(0) + f(1) = 3 + 1 = 4$。

## 样例 #1

### 输入

```
6
3 4
2 0 2
3 2 3 3
4 7 0 1 5
3 4
5 0 2 0 4 11
1 1
5 1 3 0 3 3
2 50
2 1 2
2 1 2
1 1
7 1 2 4 1 4 9 5
4 114514
2 2 2
5 7 3 6 0 3
3 0 1 1
5 0 9 2 1 5
5 1919810
1 2
2 324003 0
3 1416324 2 1460728
4 1312631 2 0 1415195
5 1223554 192248 2 1492515 725556
```

### 输出

```
16
18
1281
4
6556785365
1842836177961
```



---

---
title: "Iris and Game on the Tree"
layout: "post"
diff: 普及+/提高
pid: CF2006A
tag: ['贪心']
---

# Iris and Game on the Tree

## 题目描述

给定一棵根为 $1$，每个点有 $0$ 或 $1$ 的点权的有根树，对于所有叶子定义权值为：取出根到它的路径上所有点的点权形成的 $01$ 串，其中 $10$ 子串的出现次数减去 $01$ 子串的出现次数。不认为根为叶子。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006A/66d8f9cca162bbc9b7dcbbd0c66de4a705cfbe4e.png)

如图，绿点的点权为 $1$，白点的点权为 $0$，根到 $5$ 的串为 $10110$，其中有 $2$ 个 $10$，$1$ 个 $01$，故 $5$ 的权值为 $1$。

一棵树的分数被定义为：具有非零权值的叶子的数量。

有些点权尚未确定，A 与 B 在玩游戏，她们轮流将一个未确定点的点权改为 $0$ 或 $1$。先手的 A 希望最大化树的分数，后手的 B 希望最小化之，二人均采取最优策略，求最后树的分数。

## 输入格式

第一行输入一个数 $t$ 表示数据范围。

对于每组数据，第一行输入一个数 $n$ 表示树的点数，后面 $n-1$ 行每行两个数字代表树的一条边。最后一行有一个长度为 $n$ 的字符串 $s$，仅包含 `?`，`0` 和 `1`，若第 $i$ 位为 `?` 则说明点 $i$ 的权值尚未确定，否则说明点 $i$ 的权值为 $s_i$。

## 输出格式

对于每组数据，输出一行一个数，表示最后树的分数。

## 说明/提示

$1 \leq t \leq 5 \cdot 10^4$，$2 \leq \sum n \leq 2 \cdot 10^5$。

translated by uid 443664

## 样例 #1

### 输入

```
6
4
1 2
1 3
4 1
0101
4
1 2
3 2
2 4
???0
5
1 2
1 3
2 4
2 5
?1?01
6
1 2
2 3
3 4
5 3
3 6
?0????
5
1 2
1 3
1 4
1 5
11?1?
2
2 1
??
```

### 输出

```
2
1
1
2
1
0
```



---

---
title: "Cards Partition"
layout: "post"
diff: 普及+/提高
pid: CF2018A
tag: ['数学', '贪心']
---

# Cards Partition

## 题目描述

[DJ Genki vs Gram - Einherjar Joker](https://soundcloud.com/leon-hwang-368077289/einherjar-joker-dj-genki-vs-gram)

⠀



You have some cards. An integer between $ 1 $ and $ n $ is written on each card: specifically, for each $ i $ from $ 1 $ to $ n $ , you have $ a_i $ cards which have the number $ i $ written on them.

There is also a shop which contains unlimited cards of each type. You have $ k $ coins, so you can buy at most $ k $ new cards in total, and the cards you buy can contain any integer between $ \mathbf{1} $ and $ \mathbf{n} $ , inclusive.

After buying the new cards, you must partition all your cards into decks, according to the following rules:

- all the decks must have the same size;
- there are no pairs of cards with the same value in the same deck.

Find the maximum possible size of a deck after buying cards and partitioning them optimally.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ , $ k $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ , $ 0 \leq k \leq 10^{16} $ ) — the number of distinct types of cards and the number of coins.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i \leq 10^{10} $ , $ \sum a_i \geq 1 $ ) — the number of cards of type $ i $ you have at the beginning, for each $ 1 \leq i \leq n $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer: the maximum possible size of a deck if you operate optimally.

## 说明/提示

In the first test case, you can buy one card with the number $ 1 $ , and your cards become $ [1, 1, 1, 1, 2, 2, 3, 3] $ . You can partition them into the decks $ [1, 2], [1, 2], [1, 3], [1, 3] $ : they all have size $ 2 $ , and they all contain distinct values. You can show that you cannot get a partition with decks of size greater than $ 2 $ , so the answer is $ 2 $ .

In the second test case, you can buy two cards with the number $ 1 $ and one card with the number $ 3 $ , and your cards become $ [1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 5, 5, 5, 5] $ , which can be partitioned into $ [1, 2, 3], [1, 2, 4], [1, 2, 5], [1, 2, 5], [2, 3, 5], [2, 4, 5] $ . You can show that you cannot get a partition with decks of size greater than $ 3 $ , so the answer is $ 3 $ .

## 样例 #1

### 输入

```
9
3 1
3 2 2
5 4
2 6 1 2 4
2 100
1410065408 10000000000
10 8
7 4 6 6 9 3 10 2 8 7
2 12
2 2
2 70
0 1
1 0
1
3 0
2 1 2
3 1
0 3 3
```

### 输出

```
2
3
1
7
2
2
1
1
2
```



---

---
title: "Tree Pruning"
layout: "post"
diff: 普及+/提高
pid: CF2018C
tag: ['贪心', '树的遍历']
---

# Tree Pruning

## 题目描述

[t+pazolite, ginkiha, Hommarju - Paved Garden](https://soundcloud.com/fractalex-gd/ginkiha-paved-garden-little)

⠀



You are given a tree with $ n $ nodes, rooted at node $ 1 $ . In this problem, a leaf is a non-root node with degree $ 1 $ .

In one operation, you can remove a leaf and the edge adjacent to it (possibly, new leaves appear). What is the minimum number of operations that you have to perform to get a tree, also rooted at node $ 1 $ , where all the leaves are at the same distance from the root?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 3 \leq n \leq 5 \cdot 10^5 $ ) — the number of nodes.

Each of the next $ n-1 $ lines contains two integers $ u $ , $ v $ ( $ 1 \leq u, v \leq n $ , $ u \neq v $ ), describing an edge that connects $ u $ and $ v $ . It is guaranteed that the given edges form a tree.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer: the minimum number of operations needed to achieve your goal.

## 说明/提示

In the first two examples, the tree is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2018C/46789adad3b93ca642b297f7ca0ca574c7f98f60.png)In the first example, by removing edges $ (1, 3) $ and $ (2, 5) $ , the resulting tree has all leaves (nodes $ 6 $ and $ 7 $ ) at the same distance from the root (node $ 1 $ ), which is $ 3 $ . The answer is $ 2 $ , as it is the minimum number of edges that need to be removed to achieve the goal.

In the second example, removing edges $ (1, 4) $ and $ (5, 7) $ results in a tree where all leaves (nodes $ 4 $ and $ 5 $ ) are at the same distance from the root (node $ 1 $ ), which is $ 2 $ .

## 样例 #1

### 输入

```
3
7
1 2
1 3
2 4
2 5
4 6
4 7
7
1 2
1 3
1 4
2 5
3 6
5 7
15
12 9
1 6
6 14
9 11
8 7
3 5
13 5
6 10
13 15
13 6
14 12
7 2
8 1
1 4
```

### 输出

```
2
2
5
```



---

---
title: "Adjust The Presentation (Hard Version)"
layout: "post"
diff: 普及+/提高
pid: CF2021C2
tag: ['贪心', '线段树']
---

# Adjust The Presentation (Hard Version)

## 题目描述

This is the hard version of the problem. In the two versions, the constraints on $ q $ and the time limit are different. In this version, $ 0 \leq q \leq 2 \cdot 10^5 $ . You can make hacks only if all the versions of the problem are solved.

A team consisting of $ n $ members, numbered from $ 1 $ to $ n $ , is set to present a slide show at a large meeting. The slide show contains $ m $ slides.

There is an array $ a $ of length $ n $ . Initially, the members are standing in a line in the order of $ a_1, a_2, \ldots, a_n $ from front to back. The slide show will be presented in order from slide $ 1 $ to slide $ m $ . Each section will be presented by the member at the front of the line. After each slide is presented, you can move the member at the front of the line to any position in the lineup (without changing the order of the rest of the members). For example, suppose the line of members is $ [\color{red}{3},1,2,4] $ . After member $ 3 $ presents the current slide, you can change the line of members into either $ [\color{red}{3},1,2,4] $ , $ [1,\color{red}{3},2,4] $ , $ [1,2,\color{red}{3},4] $ or $ [1,2,4,\color{red}{3}] $ .

There is also an array $ b $ of length $ m $ . The slide show is considered good if it is possible to make member $ b_i $ present slide $ i $ for all $ i $ from $ 1 $ to $ m $ under these constraints.

However, your annoying boss wants to make $ q $ updates to the array $ b $ . In the $ i $ -th update, he will choose a slide $ s_i $ and a member $ t_i $ and set $ b_{s_i} := t_i $ . Note that these updates are persistent, that is changes made to the array $ b $ will apply when processing future updates.

For each of the $ q+1 $ states of array $ b $ , the initial state and after each of the $ q $ updates, determine if the slideshow is good.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains three integers $ n $ , $ m $ and $ q $ ( $ 1 \le n, m \le 2 \cdot 10^5 $ ; $ 0 \leq q \leq 2 \cdot 10^5 $ ) — the number of members and the number of sections.

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \le a_i \le n $ ) — the initial order of the members from front to back. It is guaranteed that each integer from $ 1 $ to $ n $ appears exactly once in $ a $ .

The third line of each test case contains $ m $ integers $ b_1, b_2, \ldots, b_m $ ( $ 1 \le b_i \le n $ ) — the members who should present each section.

Each of the next $ q $ lines contains two integers $ s_i $ and $ t_i $ ( $ 1 \le s_i \le m $ , $ 1 \le t_i \le n $ ) — parameters of an update.

It is guaranteed that the sum of $ n $ , the sum of $ m $ and the sum of $ q $ over all test cases do not exceed $ 2 \cdot 10^5 $ respectively.

## 输出格式

For each test case, output $ q+1 $ lines corresponding to the $ q+1 $ states of the array $ b $ . Output "YA" if the slide show is good, and "TIDAK" otherwise.

You can output the answer in any case (upper or lower). For example, the strings "yA", "Ya", "ya", and "YA" will be recognized as positive responses.

## 说明/提示

For the first test case, you do not need to move the members as both slides are presented by member $ 1 $ , who is already at the front of the line. After that, set $ b_1 := 2 $ , now slide $ 1 $ must be presented by member $ 2 $ which is impossible as member $ 1 $ will present slide $ 1 $ first. Then, set $ b_1 = 1 $ , the $ b $ is the same as the initial $ b $ , making a good presentation possible.

## 样例 #1

### 输入

```
3
4 2 2
1 2 3 4
1 1
1 2
1 1
3 6 2
1 2 3
1 1 2 3 3 2
3 3
2 2
4 6 2
3 1 4 2
3 1 1 2 3 4
3 4
4 2
```

### 输出

```
YA
TIDAK
YA
YA
TIDAK
YA
TIDAK
YA
YA
```



---

---
title: "Darius' Wisdom"
layout: "post"
diff: 普及+/提高
pid: CF2034D
tag: ['贪心']
---

# Darius' Wisdom

## 题目描述

大流士一世正在建造 $ n $ 根石柱，每根石柱由一个底座和不超过两个铭文块构成。

在每次操作中，大流士可以选择两根石柱 $ u $ 和 $ v $，只要这两根石柱的铭文数量差恰好为 $ 1 $，就可以将一个铭文从较多的一根转移到较少的一根。可以保证至少有一根石柱含有正好 $ 1 $ 个铭文。

为使得石柱看起来更美观，大流士希望这些石柱的铭文数量按不减顺序排列。为了减少工人们的辛劳，他希望你制定一个操作序列，最多使用 $ n $ 次操作实现这一目标，不需要优化操作次数。

## 输入格式

第一行是一个整数 $ t $，表示测试用例的数量。（$ 1 \leq t \leq 3000 $）

接下来每个测试用例的第一行包含一个整数 $ n $，表示石柱数目。（$ 1 \leq n \leq 2 \cdot 10^5 $）

第二行有 $ n $ 个整数 $ a_1, a_2, \ldots, a_n $，其中 $ a_i \in \{0,1,2\} $ 表示第 $ i $ 根石柱最开始的铭文数。保证至少有一根石柱有且只有一个铭文。

在所有测试用例中，$ n $ 的总和不超过 $ 2 \cdot 10^5 $。

## 输出格式

对每个测试用例，首先输出一个整数 $ k $，表示用于排序石柱的操作次数。（$ 0 \leq k \leq n $）

接着输出 $ k $ 行，每行包含两个整数 $ u_i $ 和 $ v_i $，表示第 $ i $ 次操作中转移铭文的两个石柱索引，要求转移时 $ |a_{u_i} - a_{v_i}| = 1 $。

可以证明，在这些限制下，总能找到一个可行的解。

## 说明/提示

以下是几个测试用例的样例状态：

- 第一个测试用例：
  - 初始状态：$ 0, 2, 0, 1 $
  - 第一次操作后：$ 0, 1, 0, 2 $
  - 第二次操作后：$ 0, 0, 1, 2 $

- 第二个测试用例：
  - 初始状态：$ 1, 2, 0 $
  - 第一次操作后：$ 0, 2, 1 $
  - 第二次操作后：$ 0, 1, 2 $

- 在第三个测试用例中，石柱的铭文数量已经是按升序排列的。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
4
0 2 0 1
3
1 2 0
6
0 1 1 2 2 2
```

### 输出

```
2
2 4
2 3
2
3 1
2 3
0
```



---

---
title: "Yet Another Real Number Problem"
layout: "post"
diff: 普及+/提高
pid: CF2035D
tag: ['贪心', '单调栈']
---

# Yet Another Real Number Problem

## 题目描述

# 又一个实数问题


Three r there are's in strawberry.

（“strawberry”中有三个“r”）


给定一个长度为 $m$ 的数组 $b$ 。你可以进行以下操作任意次（可能为零次）：

- 选择两个不同的下标 $i$ 和 $j$ ，其中 $\bf{1\le i<j\le m}$ 且 $b_i$ 是偶数，将 $b_i$ 除以 $2$ ，并将 $b_j$ 乘以 $2$ 。

你的任务是通过任意次数的操作来最大化数组的和。因为结果可能会非常大，你需要输出该和对 $10^9+7$ 取模的结果。

由于这个问题太简单了，所以现在你被给定了一个长度为 $n$ 的数组 $a$，需要针对数组 $a$ 的每个前缀来求解该问题。

换句话说，记经过任意次数操作后 $ b $ 的最大和为 $f(b)$ ，你需要分别输出 $f([a_1])$ , $f([a_1,a_2])$ , $\ldots$ , $f([a_1,a_2,\ldots,a_n])$ 对 $10^9+7$ 取模的结果。

## 输入格式

第一行包含一个整数 $t$ ( $1\le t\le 10^4$ ) — 测试用例数。

每个测试用例的第一行包含一个整数 $n$ ( $1\le n\le 2\cdot 10^5$ ) — $a$ 的长度。

第二行包含 $n$ 个整数 $a_1,a_2,\ldots,a_n$ ( $1\le a_i\le 10^9$ ) — 数组 $a$ 的初始值。

保证所有测试用例中 $n$ 的总和不超过 $2\cdot 10^5$ 。

## 输出格式

针对每个测试用例，输出 $n$ 个整数，表示每个前缀的答案，结果对 $10^9+7$ 取模。

## 样例 #1

### 样例输入 #1

```
3
10
1 2 3 4 5 6 7 8 9 10
11
1 6 9 4 7 4 4 10 3 2 3
4
527792568 502211460 850237282 374773208
```

### 样例输出 #1

```
1 3 8 13 46 59 126 149 1174 1311 
1 7 22 26 70 74 150 1303 1306 1308 1568 
527792568 83665723 399119771 773892979 
```

## 说明/提示

对于第一个测试用例中的每个前缀数组，操作后可能是：

- $[1]$ 和为 $1$ 
- $[1,2]$ 和为 $3$ 
- $[1,1,6]$ 和为 $8$ 
- $[1,1,3,8]$ 和为 $13$ 
- $[1,1,3,1,40]$ 和为 $46$ 
- $[1,1,3,1,5,48]$ 和为 $59$ 
- $[1,1,3,1,5,3,112]$ 和为 $126$ 
- $[1,1,3,1,5,3,7,128]$ 和为 $149$ 
- $[1,1,3,1,5,3,7,1,1152]$ 和为 $1174$
- $[1,1,3,1,5,3,7,1,9,1280]$ 和为 $ 1311 $​

## 样例 #1

### 输入

```
3
10
1 2 3 4 5 6 7 8 9 10
11
1 6 9 4 7 4 4 10 3 2 3
4
527792568 502211460 850237282 374773208
```

### 输出

```
1 3 8 13 46 59 126 149 1174 1311 
1 7 22 26 70 74 150 1303 1306 1308 1568 
527792568 83665723 399119771 773892979
```



---

---
title: "Kachina's Favorite Binary String"
layout: "post"
diff: 普及+/提高
pid: CF2037E
tag: ['贪心', '双指针 two-pointer']
---

# Kachina's Favorite Binary String

## 题目描述

这是一道交互题。

卡齐娜有一个长为 $n$ 的 01 串 $s$。她定义 $f(l,r)$ 为子段 $s_ls_{l+1}\cdots s_r$ 中等于 $\texttt{01}$ 的子序列的个数。子序列不要求连续；两个位置不同的子序列被认为是 **不同** 的，即便它们含有相同的字符序列。

你需要通过向卡齐娜提问来猜出 $s$。每次提问，你可以选择两个下标 $l,r(1\le l < r\le n)$，询问她 $f(l,r)$ 的值。你最多提问 $n$ 次。如果 $s$ 不可能在 $n$ 次询问内确定，输出 $\texttt{IMPOSSIBLE}$。

## 输入格式

第一行一个整数 $t(1\le t\le 10^3)$ — 测试数据的组数。

每组测试数据一行一个整数 $n(2\le n\le 10^4)$ — 01 串 $s$ 的长度。

保证各组测试数据 $n$ 的总和不超过 $10^4$。

## 输出格式

每次提问，按照以下格式输出一行（不含括号）：

- $\texttt{? l r}(1\le l < r\le n)$

测试程序会返回一个整数 $f(l,r)$。当你确定答案后，按照以下格式输出一行：

- 如果 $s$ 无法确定，输出 $\texttt{"! IMPOSSIBLE"}$
- 否则输出 $\texttt{"! s"}$

输出答案不算一次提问。

## 说明/提示

**第一个样例：**

第一次提问中，你询问卡齐娜 $f(1,5)$ 的值，她向输入流中返回 $4$。

第二次提问中，你询问卡齐娜 $f(2,4)$ 的值。因为在 $\texttt{100}$ 中没有等于 $\texttt{01}$ 的子序列，她向输入流中返回 $0$。

提问四次后，你输出正确答案 $\texttt{01001}$。

**第二个样例：**

第一次提问中，你询问卡齐娜 $f(1,2)$ 的值，她向输入流中返回 $0$。

注意到你除了 $\texttt{? 1 2}$ 提不出别的问题了，但 01 串 $\texttt{00}$ 和 $\texttt{11}$ 的答案都是 $0$，无法确定唯一答案，所以输出 $\texttt{IMPOSSIBLE}$。

样例仅用于展示交互格式，不代表正解方法。

## 样例 #1

### 输入

```
2
5

4

0

1

2

2

0
```

### 输出

```
? 1 5

? 2 4

? 4 5

? 3 5

! 01001

? 1 2

! IMPOSSIBLE
```



---

---
title: "Shohag Loves GCD"
layout: "post"
diff: 普及+/提高
pid: CF2039D
tag: ['贪心', '数论', '素数判断,质数,筛法', '构造', '标签475']
---

# Shohag Loves GCD

## 题目描述

Shohag 拥有一个整数 $n$ 和一个包含 $m$ 个不同整数的集合 $S$。请帮助他找到字典序最大*的整数数组 $a_1, a_2, \ldots, a_n$，使得对于每个 $1 \le i \le n$ 有 $a_i \in S$ ，并且满足对所有 $1 \le i < j \le n$ 有 $a_{\gcd(i, j)} \neq \gcd(a_i, a_j)$†，或者说明不存在这样的数组。

*一个数组 $a$ 如果在第一个不同的位置上比数组 $b$ 有更大的元素，则称其为字典序大于数组 $b$（假设两个数组长度相同）。

†$\gcd(x, y)$ 表示整数 $x$ 和 $y$ 的[最大公约数（GCD）](https://en.wikipedia.org/wiki/Greatest_common_divisor)。

## 输入格式

第一行包含一个整数 $t$ ($1 \le t \le 10^4$) — 测试用例的数量。

每个测试用例的第一行包含两个整数 $n$ 和 $m$ ($1 \le m \le n \le 10^5$)。

每个测试用例的第二行包含 $m$ 个按递增顺序排列的不同整数，表示集合 $S$ 的元素 ($1 \le x \le n$ 对于每个 $x \in S$)。

保证所有测试用例中 $n$ 的总和不超过 $3 \cdot 10^5$。

## 输出格式

对于每个测试用例，如果无解则输出 $-1$，否则输出 $n$ 个整数 —— 满足条件的字典序最大的整数数组。

## 说明/提示

在第一个测试用例中，数组中的每个元素都属于给定的集合 $S = \{3, 4, 6\}$，并且数组的所有索引对都满足必要的条件。特别是对于对 $(2, 3)$，有 $a_{\gcd(2, 3)} = a_1 = 6$ 而 $\gcd(a_2, a_3) = \gcd(4, 4) = 4$，因此它们不相等。尽管存在其他满足条件的数组，但这个是其中字典序最大的。

在第三个测试用例中，由于我们只能使用数组 $a = [2, 2]$，但对于该数组，对于对 $(1, 2)$，有 $a_{\gcd(1, 2)} = a_1 = 2$ 而 $\gcd(a_1, a_2) = \gcd(2, 2) = 2$，因此它们相等，这是不允许的！所以没有解决方案。

## 样例 #1

### 输入

```
3
6 3
3 4 6
1 1
1
2 1
2
```

### 输出

```
6 4 4 3 4 3 
1 
-1
```



---

---
title: "Ordered Permutations"
layout: "post"
diff: 普及+/提高
pid: CF2040C
tag: ['数学', '贪心', '位运算']
---

# Ordered Permutations

## 题目描述

给定一个长度为 $n$ 的整数排列 $p_1, p_2, \ldots, p_n$，其中包含从 $1$ 到 $n$ 的所有整数。我们定义一个如下的和式：

$$S(p) = \sum_{1 \le l \le r \le n} \min(p_l, p_{l+1}, \ldots, p_r)$$

我们希望找出所有能使 $S(p)$ 最大的排列，并从中按字典序选择第 $k$ 个。如果这样的排列数量少于 $k$，则输出 -1。

**解释说明：**
- 长度为 $n$ 的排列是一个由 $n$ 个不同的整数组成的序列，这些整数来源于 $1$ 到 $n$ 的一组数字。例如，$[2, 3, 1, 5, 4]$ 是一个符合要求的排列，而 $[1, 2, 2]$ 因为有重复数字 $2$ 而不符合，$[1, 3, 4]$ 也不符合要求，因为它包含了不在 $1$ 到 $n$ 范围内的数 $4$（$n = 3$）。
- 示例计算： 
  - 对于排列 $[1, 2, 3]$，$S(p)$ 计算为 $\min(1) + \min(1, 2) + \min(1, 2, 3) + \min(2) + \min(2, 3) + \min(3) = 1 + 1 + 1 + 2 + 2 + 3 = 10$。
  - 对于排列 $[2, 4, 1, 3]$，$S(p)$ 计算为 $\min(2) + \min(2, 4) + \min(2, 4, 1) + \min(2, 4, 1, 3) + \min(4) + \min(4, 1) + \min(4, 1, 3) + \min(1) + \min(1, 3) + \min(3) = 2 + 2 + 1 + 1 + 4 + 1 + 1 + 1 + 1 + 3 = 17$。
- 字典序小于：数组 $a$ 比数组 $b$ 在字典序上小的条件是：
  1. $a$ 是 $b$ 的一个前缀，且 $a \ne b$；
  2. 或者在第一个不同的位置上，$a$ 的元素小于 $b$ 的对应元素。

## 输入格式

第一行输入一个整数 $t$，表示测试用例的数量 ($1 \le t \le 10^4$)。之后的每一个测试用例由一行组成，包含两个整数 $n$ 和 $k$，分别表示排列的长度和需要找出的第 $k$ 个排列的索引 ($1 \le n \le 2 \cdot 10^5$; $1 \le k \le 10^{12}$)。

保证所有测试用例中的 $n$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每一个测试用例：
- 如果符合条件的排列少于 $k$ 个，则输出 `-1`。
- 否则，输出第 $k$ 个符合条件的排列。

## 说明/提示

以下是所有长度为 3 的排列及其对应的 $S(p)$ 值（按字典序排序）：

| 排列 | $S(p)$ 的值 |
|------|-------------|
| $[1, 2, 3]$ | $10$ |
| $[1, 3, 2]$ | $10$ |
| $[2, 1, 3]$ | $9$ |
| $[2, 3, 1]$ | $10$ |
| $[3, 1, 2]$ | $9$ |
| $[3, 2, 1]$ | $10$ |

在第一个测试用例中，需输出长度为 3 的第 2 个符合条件的排列，看表格可以知道是 $[1, 3, 2]$。

在第二个测试用例中，需输出长度为 3 的第 3 个符合条件的排列，对应的是 $[2, 3, 1]$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
6
3 2
3 3
4 11
4 6
6 39
7 34
```

### 输出

```
1 3 2 
2 3 1 
-1
2 4 3 1 
-1
2 3 4 5 7 6 1
```



---

---
title: "Selection Sort"
layout: "post"
diff: 普及+/提高
pid: CF2041M
tag: ['贪心', '优先队列']
---

# Selection Sort

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041M/d5dc69f2c95d765850bbfc6e16bfc04c742abf70.png)Every student enrolled in the algorithms course is required to submit an assignment this week. The task is to implement an $ O(n^2) $ -time algorithm to sort $ n $ given integers in non-decreasing order. Alice has already completed her assignment, and her implementation is shown below.

```
<pre class="lstlisting">```
int alice_sort(int *s, int n){<br></br>  for(int i = 0; i < n; ++i){<br></br>    for(int j = i + 1; j < n; ++j){<br></br>      if(s[i] > s[j]){<br></br>        int swap = s[i];<br></br>        s[i] = s[j];<br></br>        s[j] = swap;<br></br>      }<br></br>    }<br></br>  }<br></br>  return 0;<br></br>}<br></br>
```
```

While you have access to Alice's code, you prefer not to simply copy it. Instead, you want to use Alice's sorting function as a building block for your own solution. There are two ways as listed below you can utilize her function, but each of them can be applied at most once. The order in which these two operations are invoked can be arbitrary.

- Prefix sort: choose a length $ i \in \{1, 2, \ldots, n\} $ and call $ \texttt{alicesort(}s, i\texttt{)} $ . This sorts the first $ i $ elements in the array $ s $ .
- Suffix sort: choose a length $ i \in \{1, 2, \ldots, n\} $ and call $ \texttt{alicesort(}s+n-i, i\texttt{)} $ . This sorts the last $ i $ elements in the array $ s $ .

Due to the time complexity of the sorting algorithm, the cost of performing either a prefix or suffix sort is $ i^2 $ , where $ i $ is the length of the chosen subarray. Your goal is to determine the minimum cost to sort the input array $ s $ of $ n $ integers in non-decreasing order using Alice's function, following the rules mentioned above.

For example, Let $ s=[3,2,5,5,4,1] $ . We can first perform a suffix sort of length $ 4 $ , and the array becomes $ [3,2,1,4,5,5] $ . Then, we perform a prefix sort of length $ 3 $ , and the array becomes $ [1,2,3,4,5,5] $ , which is a sorted array. The cost is $ 4^2+3^2=25 $ . Here is another example, let $ s=[4,3,2,1] $ . We can complete the sorting by performing only a prefix sort of length $ 4 $ , and the cost is $ 4^2=16 $ .

## 输入格式

The first line contains exactly one integer $ n $ which indicates the number of integers in the array $ s $ . The second line contains the $ n $ integers in $ s=[s_0, s_1, \ldots, s_{n-1}] $ .

- $ 1 \le n \le 10^6 $
- For all $ i $ ( $ 0\le i < n $ ), $ 0\le s_i < 2^{31}-1 $ .

## 输出格式

Output an integer on a line, indicating the minimum cost to sort the input array $ s $ of $ n $ integers in non-decreasing order using Alice's function, following the rules mentioned above.

## 样例 #1

### 输入

```
6
3 2 5 5 4 1
```

### 输出

```
25
```

## 样例 #2

### 输入

```
4
4 3 2 1
```

### 输出

```
16
```



---

---
title: "Sums on Segments"
layout: "post"
diff: 普及+/提高
pid: CF2043C
tag: ['动态规划 DP', '贪心']
---

# Sums on Segments

## 题目描述

### 题目内容
给定一个长度为 $n$ 的数组 $a$，其中除了至多一个 $i \in [0,n)$ 满足 $|a_i| \neq 1$ 以外，其余全部项均满足 $|a_i|=1$。

求该数组中全部可能的子数组和，以升序输出。子数组是原数组中一段连续的数组。

## 输入格式

第一行一个整数 $t$（$ 1 \le t \le 10^4$ ），表示测试用例数。

每个测试用例包含 $2$ 行，其中：
- 第一行一个正整数 $n$（ $1 \le n \le 2 \cdot 10^5$ ），表示数组长度
- 第二行 $n$ 个整数，表示 $a$ 中元素。

保证全部测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试点，输出两行：
- 第一行一个整数，表示可能的子数组和个数。
- 第二行以升序输出所有可能的子数组和。

即便多个子数组均可求出这个和，每一个值也只需要输出一次。

## 样例 #1

### 输入

```
5
5
1 -1 10 1 1
5
-1 -1 -1 -1 -1
2
-1 2
2
7 1
3
1 4 -1
```

### 输出

```
8
-1 0 1 2 9 10 11 12 
6
-5 -4 -3 -2 -1 0 
4
-1 0 1 2 
4
0 1 7 8 
6
-1 0 1 3 4 5
```



---

---
title: "Medium Demon Problem (hard version)"
layout: "post"
diff: 普及+/提高
pid: CF2044G2
tag: ['贪心', '拓扑排序']
---

# Medium Demon Problem (hard version)

## 题目描述

这是该问题的困难版本。两个版本之间的关键区别已用粗体强调。

有一群 $n$ 只蜘蛛聚在一起交换毛绒玩具。一开始，每只蜘蛛手里都有一个毛绒玩具。每年，如果第 $i$ 只蜘蛛至少有一个毛绒玩具，它会把自己的一个毛绒玩具送给第 $r_i$ 只蜘蛛。否则，它会选择不做任何事情。注意，所有毛绒玩具的转移同时进行。在这个版本中，每只蜘蛛在任何时候都可以拥有多个毛绒玩具。

如果今年（在进行交换之前）每只蜘蛛拥有的毛绒玩具数量与去年（交换之前）相同，那么这一年就是稳定的。需要注意的是，第一年不可能是稳定的。

请找出施行直到稳定的第一个年份。

## 输入格式

第一行输入一个整数 $t$（$1 \leq t \leq 10^4$），表示测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$2 \leq n \leq 2 \cdot 10^5$），表示蜘蛛的数量。

接下来的一行包含 $n$ 个整数 $r_1, r_2, \ldots, r_n$（$1 \leq r_i \leq n, r_i \neq i$），表示每只蜘蛛所指定的收件蜘蛛编号。

保证所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数代表过程第一次变得稳定的年份。

## 说明/提示

对于第二个测试用例：

- 第一年，每只蜘蛛拥有的毛绒玩具数量为：$[1, 1, 1, 1, 1]$。接下来进行第一次交换。
- 第二年，每只蜘蛛拥有的毛绒玩具数量仍为：$[1, 1, 1, 1, 1]$。由于这个数组与去年相同，所以第二年是稳定的。

对于第三个测试用例：

- 第一年，每只蜘蛛拥有的毛绒玩具数量为：$[1, 1, 1, 1, 1]$。接下来进行第一次交换。
- 第二年，每只蜘蛛拥有的毛绒玩具数量变为：$[1, 2, 1, 1, 0]$。随后进行第二次交换。
- 第三年，每只蜘蛛拥有的毛绒玩具数量变为：$[1, 3, 0, 1, 0]$。随后进行第三次交换。
- 第四年，每只蜘蛛拥有的毛绒玩具数量变为：$[1, 4, 0, 0, 0]$。随后进行第四次交换。
- 第五年，每只蜘蛛拥有的毛绒玩具数量仍为：$[1, 4, 0, 0, 0]$。由于这个阵列与上一年相同，第五年是稳定的。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
2
2 1
5
2 3 4 5 1
5
2 1 4 2 3
5
4 1 1 5 4
10
4 3 9 1 6 7 9 10 10 3
```

### 输出

```
2
2
5
5
5
```



---

---
title: "Scrambled Scrabble"
layout: "post"
diff: 普及+/提高
pid: CF2045A
tag: ['贪心']
---

# Scrambled Scrabble

## 题目描述

你正在参与一个字母游戏，该游戏使用标准的26个大写英文字母A到Z。在这个游戏中，元音和辅音的构成规则如下：

- A, E, I, O, U 是元音。
- Y 可以作为元音或辅音。
- 除A, E, I, O, U和Y之外的其他字母只作为辅音。
- 子串NG可以作为一个整体看作辅音。

一个音节被定义为依次连接的辅音、元音和辅音。一个由一个或多个音节组成的字符串被定义为一个单词。

现在，给你一个字符串 $S$，你需要利用这个字符串中的字母构建一个单词。你可以从 $S$ 中删除任意数量的字母，并重新排列剩下的字母。请计算出可以构建的最长单词的长度，若无法构建任何单词，则返回0。

## 输入格式

输入为一行，包含一个仅由大写英文字母组成的字符串 $S$ ( $1 \leq |S| \leq 5000 $ )。

## 输出格式

如果不能构建任何单词，输出0。否则，输出一个整数，表示可以构建的最长单词的长度。

## 例子解释

- 示例1：一个可能的最长单词是JAKCARTAP，由音节JAK、CAR和TAP组成。
- 示例2：整个字符串$S$可看作一个单词，包含一个音节，这个音节由辅音NG、元音E和辅音NG构成。
- 示例3：整个字符串$S$是一个单词，由音节Y、Y、Y构成，分别作为辅音、元音和辅音。
- 示例4：整个字符串$S$为一个单词，包括音节DAN和GAN。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
ICPCJAKARTA
```

### 输出

```
9
```

## 样例 #2

### 输入

```
NGENG
```

### 输出

```
5
```

## 样例 #3

### 输入

```
YYY
```

### 输出

```
3
```

## 样例 #4

### 输入

```
DANGAN
```

### 输出

```
6
```

## 样例 #5

### 输入

```
AEIOUY
```

### 输出

```
0
```



---

---
title: "Move Back at a Cost"
layout: "post"
diff: 普及+/提高
pid: CF2046B
tag: ['贪心']
---

# Move Back at a Cost

## 题目描述

You are given an array of integers $ a $ of length $ n $ . You can perform the following operation zero or more times:

- In one operation choose an index $ i $ ( $ 1 \le i \le n $ ), assign $ a_i := a_i + 1 $ , and then move $ a_i $ to the back of the array (to the rightmost position). For example, if $ a = [3, 5, 1, 9] $ , and you choose $ i = 2 $ , the array becomes $ [3, 1, 9, 6] $ .

Find the lexicographically smallest $ ^{\text{∗}} $ array you can get by performing these operations.

 $ ^{\text{∗}} $ An array $ c $ is lexicographically smaller than an array $ d $ if and only if one of the following holds:

- $ c $ is a prefix of $ d $ , but $ c \ne d $ ; or
- in the first position where $ c $ and $ d $ differ, the array $ c $ has a smaller element than the corresponding element in $ d $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ), the length of the array.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ), the elements of the array.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, print the lexicographically smallest array you can get.

## 样例 #1

### 输入

```
3
3
2 1 3
5
1 2 2 1 4
6
1 2 3 6 5 4
```

### 输出

```
1 3 3 
1 1 3 3 5 
1 2 3 4 6 7
```



---

---
title: "Kevin and Competition Memories"
layout: "post"
diff: 普及+/提高
pid: CF2048D
tag: ['贪心', '二分', '数学']
---

# Kevin and Competition Memories

## 题目描述

Kevin 曾经进入过 Rio 的记忆。在那段记忆中，曾举办过一系列的比赛。Kevin 还记得所有参赛者和比赛的问题，但具体的比赛轮次、问题分布和排名已经模糊不清。

有 $m$ 个比赛问题，第 $i$ 个问题的难度为 $b_i$。每场比赛选择 $k$ 个问题，因此总共会有 $\lfloor \frac{m}{k} \rfloor$ 场比赛。这意味着你可以任意组合选择这些比赛问题，并挑出总共 $\lfloor \frac{m}{k} \rfloor \cdot k$ 个问题参赛，每个问题最多只能被选一次，剩余 $m \bmod k$ 个问题将未被使用。例如，如果 $m = 17$ 且 $k = 3$，你将组织 $5$ 场比赛，每场 $3$ 个问题，会剩下 $2$ 个问题没有用上。

比赛有 $n$ 位参赛者，其中 Kevin 是第 1 位。第 $i$ 位参赛者的评分是 $a_i$。在比赛中，每个参赛者能解决难度不超过其评分的问题，具体来说，第 $i$ 位参赛者能解决第 $j$ 个问题，当且仅当 $a_i \geq b_j$。在每场比赛中，Kevin 的排名定义为那些比他解掉更多题目的参赛者数量加一。

对于每个 $k = 1, 2, \ldots, m$，Kevin 想知道在所有 $\lfloor \frac{m}{k} \rfloor$ 场比赛中的排名之和的最小可能值。也就是说，对于某个 $k$，你需要优化问题的选择和分配，使得 Kevin 的排名之和最小化。

不同的 $k$ 值代表的比赛是相互独立的。换言之，你可以对每个不同的 $k$ 值分别规划问题分配。

## 输入格式

输入包含多组测试数据。第一行为测试数据的组数 $t$（$1 \le t \le 5 \cdot 10^4$）。

每组测试数据的第一行包含两个整数 $n$ 和 $m$（$1 \le n, m \le 3 \cdot 10^5$），分别表示参赛者数量和问题数量。

接下来的行中，第二行列出 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$0 \le a_i \le 10^9$）代表每个参赛者的评分。

第三行列出 $m$ 个整数 $b_1, b_2, \ldots, b_m$（$0 \le b_i \le 10^9$）代表每个问题的难度。

保证所有测试数据中的 $n$ 与 $m$ 的总和不超过 $3 \cdot 10^5$。

## 输出格式

对于每组测试数据，输出 $m$ 个整数，分别代表对于每个 $k = 1, 2, \ldots, m$，Kevin 的排名之和的最小可能值。

## 说明/提示

考虑第一个测试数据：

- 当 $k=1$ 时，每场比赛只包含一个问题，分配方式是唯一的。例如，在包含难度为 $4$ 的第三个问题的比赛中，除了第 2 位参赛者外，所有人都能解决。因为没有人比 Kevin 解出更多的问题，他在这场比赛中排名第 1。同理，在所有 $4$ 场比赛中，Kevin 的排名分别是 $1, 3, 1, 2$，总和为 $7$。

- 当 $k=2$ 时，最佳选择是将第 1 和第 3 个问题组成一场比赛，第 2 和第 4 个问题组成另一场。在前一场比赛中，4 名选手分别解决 $2, 1, 2, 2$ 个问题，Kevin 排名第 1；在后一场比赛中，选手分别解决 $0, 0, 2, 1$ 个问题，因有 2 位选手多解题，Kevin 排名第 $3$。所以总和是 $1 + 3 = 4$。这是最优解。

- 当 $k=3$ 时，可以选择第 1、3、4 个问题组成一场比赛，Kevin 的排名是 2，为最优。

- 当 $k=4$ 时，只有一场比赛，分配方式唯一，Kevin 的排名是 3。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
4 4
4 3 7 5
2 5 4 6
5 5
5 0 4 8 6
1 3 9 2 7
6 7
1 1 4 5 1 4
1 9 1 9 8 1 0
7 6
1 9 1 9 8 1 0
1 1 4 5 1 4
```

### 输出

```
7 4 2 3
6 2 1 1 2
7 3 2 1 1 1 1
15 9 5 4 4 4
```



---

---
title: "Joker"
layout: "post"
diff: 普及+/提高
pid: CF2051F
tag: ['贪心']
---

# Joker

## 题目描述

考虑一副有 $n$ 张牌的情况。牌中的位置从上到下编号为 $1$ 到 $n$。小丑位于位置 $m$ 。

$q$ 操作按顺序应用于牌组。在第 $i$ 次操作期间，您需要在位置 $a_i$ 处取出卡片并将其移动到牌堆的开头或末尾。例如，如果牌组是 [_2,1,3,5,4_] ，并且 $a_i$   =2 ，那么在操作之后牌组将是 [_1,2,3,5,4_]（从第二个位置开始的牌移动到开头）或 [_2,3,5,4,1_]（卡片从第二个位置移到最后）。

您的任务是计算每次操作后小丑可以所处的不同位置的数量。

## 输入格式

第一行包含一个整数 $t$ ( 1 ≤ $t$ ≤10000 ) — 测试用例的数量。

## 输出格式

对于每个测试用例，打印 $q$ 个整数——每次操作后小丑可以所处的不同位置的数量。

## 样例 #1

### 输入

```
5
6 5 3
1 2 3
2 1 4
2 1 1 2
5 3 1
3
3 2 4
2 1 1 1
18 15 4
13 15 1 16
```

### 输出

```
2 3 5 
2 2 2 2 
2 
2 3 3 3 
2 4 6 8
```



---

---
title: "Refined Product Optimality"
layout: "post"
diff: 普及+/提高
pid: CF2053D
tag: ['数学', '贪心', '排序', '逆元']
---

# Refined Product Optimality

## 题目描述

As a tester, when my solution has a different output from the example during testing, I suspect the author first.

— Chris, [a comment](https://codeforces.com/blog/entry/133116?#comment-1190579)



Although Iris occasionally sets a problem where the solution is possibly wrong, she still insists on creating problems with her imagination; after all, everyone has always been on the road with their stubbornness... And like ever before, Iris has set a problem to which she gave a wrong solution, but Chris is always supposed to save it! You are going to play the role of Chris now:

- Chris is given two arrays $ a $ and $ b $ , both consisting of $ n $ integers.
- Iris is interested in the largest possible value of $ P = \prod\limits_{i=1}^n \min(a_i, b_i) $ after an arbitrary rearrangement of $ b $ . Note that she only wants to know the maximum value of $ P $ , and no actual rearrangement is performed on $ b $ .
- There will be $ q $ modifications. Each modification can be denoted by two integers $ o $ and $ x $ ( $ o $ is either $ 1 $ or $ 2 $ , $ 1 \leq x \leq n $ ). If $ o = 1 $ , then Iris will increase $ a_x $ by $ 1 $ ; otherwise, she will increase $ b_x $ by $ 1 $ .
- Iris asks Chris the maximum value of $ P $ for $ q + 1 $ times: once before any modification, then after every modification.
- Since $ P $ might be huge, Chris only needs to calculate it modulo $ 998\,244\,353 $ .

Chris soon worked out this problem, but he was so tired that he fell asleep. Besides saying thanks to Chris, now it is your turn to write a program to calculate the answers for given input data.

Note: since the input and output are large, you may need to optimize them for this problem.

For example, in C++, it is enough to use the following lines at the start of the main() function:

```
<pre class="lstlisting">```
int main() {<br></br>    std::ios::sync_with_stdio(false);<br></br>    std::cin.tie(nullptr); std::cout.tie(nullptr);<br></br>}<br></br>
```
```

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 1 \leq n \leq 2\cdot 10^5 $ , $ 1 \leq q \leq 2\cdot 10^5 $ ) — the length of the array and the number of operations.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 5\cdot 10^8 $ ) — the array $ a $ .

The third line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \leq b_i \leq 5\cdot 10^8 $ ) — the array $ b $ .

Then $ q $ lines follow, each line contains two integers $ o $ and $ x $ ( $ o \in \{1, 2\} $ , $ 1 \leq x \leq n $ ), representing an operation.

It's guaranteed that the sum of $ n $ and the sum of $ q $ over all test cases does not exceed $ 4\cdot 10^5 $ , respectively.

## 输出格式

For each test case, output $ q + 1 $ integers in a line, representing the answers that Chris will calculate, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case:

- Before the modifications, Chris can rearrange $ b $ to $ [1, 2, 3] $ so that $ P = \prod\limits_{i=1}^n \min(a_i, b_i) = 1 \cdot 1 \cdot 2 = 2 $ . We can prove that this is the maximum possible value. For example, if Chris rearranges $ b = [2, 3, 1] $ , $ P $ will be equal $ 1 \cdot 1 \cdot 1 = 1 < 2 $ , which is not optimal.
- After the first modification, Chris can rearrange $ b $ to $ [1, 2, 3] $ so that $ P = 1 \cdot 1 \cdot 3 = 3 $ , which is maximized.
- After the second modification, Chris can rearrange $ b $ to $ [2, 2, 3] $ so that $ P = 1 \cdot 1 \cdot 3 = 3 $ , which is maximized.
- After the third modification, Chris can rearrange $ b $ to $ [2, 2, 3] $ so that $ P = 6 $ , which is maximized.
- After the fourth modification, Chris can rearrange $ b $ to $ [2, 2, 4] $ so that $ P = 6 $ , which is maximized.

## 样例 #1

### 输入

```
4
3 4
1 1 2
3 2 1
1 3
2 3
1 1
2 1
6 8
1 4 2 7 3 5
7 6 5 6 3 3
2 5
1 6
1 5
1 5
1 5
2 3
2 3
1 6
13 8
7 7 6 6 5 5 5 2 2 3 4 5 1
1 4 1 9 6 6 9 1 5 1 3 8 4
2 2
2 11
2 4
2 4
1 7
1 1
2 12
1 5
5 3
10000000 20000000 30000000 40000000 50000000
10000000 20000000 30000000 40000000 50000000
1 1
2 2
2 1
```

### 输出

```
2 3 3 6 6
840 840 1008 1344 1680 2016 2016 2016 2352
2116800 2646000 3528000 3528000 3528000 4233600 4838400 4838400 4838400
205272023 205272023 205272023 264129429
```



---

---
title: "Trip to the Olympiad"
layout: "post"
diff: 普及+/提高
pid: CF2057C
tag: ['贪心', '位运算']
---

# Trip to the Olympiad

## 题目描述

在新的一年中，将会有很多团队奥林匹克竞赛，因此「T-generation」的老师们需要选择三名学生组成一个团队来参加这些比赛。无论是哪三名学生，他们都能在任何团体竞赛中表现出色。然而，赢得比赛仅仅是成功的一部分；首先，他们需要获得参赛资格……

每位学生都有一个用整数表示的独立性等级。「T-generation」中，每个独立性等级从 $l$ 到 $r$（包含 $l$ 和 $r$）的数值都有且只有一名学生。对于一个由独立性等级为 $a$、$b$ 和 $c$ 的学生组成的三人团队，他们的团队独立性值定义为 $(a \oplus b) + (b \oplus c) + (a \oplus c)$，其中 $\oplus$ 表示按位异或运算。

你的任务是选择一个三人团队，使得他们的团队独立性值最大化。

## 输入格式

输入包含多个测试用例。第一行包含一个整数 $t$（$1 \le t \le 10^4$），表示测试用例的数量。接下来的每行描述一个测试用例。

每个测试用例的首行包含两个整数 $l$ 和 $r$（$0 \le l, r < 2^{30}$，$r - l > 1$），表示学生独立性等级的最小值和最大值。

## 输出格式

对于每个测试用例，输出三个不同的整数 $a, b, c$，满足 $l \le a, b, c \le r$，且使表达式 $(a \oplus b) + (b \oplus c) + (a \oplus c)$ 的值最大。在存在多个解的情况下，可以输出任意一个满足条件的三元组。

## 说明/提示

在第一个测试用例中，可以选择的唯一个合适的三元组（忽略顺序）是 $(0, 1, 2)$。

在第二个测试用例中，其中一个合适的三元组是 $(8, 7, 1)$，因为 $(8 \oplus 7) + (7 \oplus 1) + (8 \oplus 1) = 15 + 6 + 9 = 30$。经过证明，$30$ 是在 $0 \le a, b, c \le 8$ 时，$(a \oplus b) + (b \oplus c) + (a \oplus c)$ 的最大可能值。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
8
0 2
0 8
1 3
6 22
128 137
69 98
115 127
0 1073741823
```

### 输出

```
1 2 0
8 7 1
2 1 3
7 16 11
134 132 137
98 85 76
123 121 118
965321865 375544086 12551794
```



---

---
title: "White Magic"
layout: "post"
diff: 普及+/提高
pid: CF2066B
tag: ['贪心']
---

# White Magic

## 题目描述

我们称一个序列 $a_1, a_2, \ldots, a_n$ 是魔法的，如果对于所有 $1 \leq i \leq n-1$ 满足：$\operatorname{min}(a_1, \ldots, a_i) \geq \operatorname{mex}(a_{i+1}, \ldots, a_n)$。特别地，任意长度为 $1$ 的序列都被视为魔法序列。

一个整数集合 $a_1, a_2, \ldots, a_k$ 的最小未出现值（MEX）被定义为未出现在该集合中的最小非负整数 $t$。

给定一个由 $n$ 个非负整数构成的序列 $a$。请找到该序列的魔法子序列$^{\text{∗}}$ 的最大可能长度。

$^{\text{∗}}$ 若序列 $a$ 可以通过从序列 $b$ 中删除任意多个（可以是零个或全部）元素得到，则称 $a$ 是 $b$ 的子序列。


## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 10^4$）。随后为各测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \leq n \leq 2 \cdot 10^5$）——序列 $a$ 的长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$0 \leq a_i \leq 10^9$）——序列 $a$ 的元素。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——序列 $a$ 的魔法子序列的最大可能长度。

## 说明/提示

在第一个测试用例中，序列 $[4, 3, 2, 1, 0]$ 是魔法的，因为：
- $\operatorname{min}(4) = 4$，$\operatorname{mex}(3, 2, 1, 0) = 4$。满足 $4 \geq 4$。
- $\operatorname{min}(4, 3) = 3$，$\operatorname{mex}(2, 1, 0) = 3$。满足 $3 \geq 3$。
- $\operatorname{min}(4, 3, 2) = 2$，$\operatorname{mex}(1, 0) = 2$。满足 $2 \geq 2$。
- $\operatorname{min}(4, 3, 2, 1) = 1$，$\operatorname{mex}(0) = 1$。满足 $1 \geq 1$。

在第二个测试用例中，序列 $[4, 3, 3, 2, 1, 0]$ 不是魔法的，因为 $\operatorname{min}(4, 3) = 3$，$\operatorname{mex}(3, 2, 1, 0) = 4$，此时 $3 < 4$。然而该序列的子序列 $[4, 3, 2, 1, 0]$ 是魔法的，因此答案为 $5$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
8
5
4 3 2 1 0
6
4 3 3 2 1 0
4
2 0 1 2
1
777
4
1000000000 1 7 9
2
0 1
2
1 2
4
0 1 0 1
```

### 输出

```
5
5
3
1
4
2
2
3
```



---

---
title: "Palindrome Shuffle"
layout: "post"
diff: 普及+/提高
pid: CF2069D
tag: ['字符串', '贪心', '二分']
---

# Palindrome Shuffle

## 题目描述

给定一个由小写拉丁字母组成的字符串 $s$。

你可以对字符串 $s$ 执行以下操作：选择一个连续的（可能为空的）子串，并对其进行洗牌（即重新排列子串中的字符顺序）。

注意：回文是指正向和反向读取相同的字符串。例如，字符串 a、bab、acca、bcabcbacb 是回文，而 ab、abbbaa、cccb 则不是。

你的任务是确定为了将给定字符串 $s$ 转换为回文，必须进行操作的最小子串长度。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例仅包含一行字符串 $s$（$2 \le |s| \le 2 \cdot 10^5$），由小写拉丁字母组成。

输入额外约束：
- 字符串 $s$ 的长度为偶数；
- 字符串 $s$ 总能被转换为回文；
- 所有测试用例的 $s$ 长度总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——为了将字符串转换为回文必须进行操作的最小子串长度。


## 说明/提示

第一个示例中，可以按如下方式操作：baba → baab。

第二个示例中，字符串已经是回文，因此可以选择空子串进行操作。

第三个示例中，可以按如下方式操作：ddaa → adda。

第四个示例中，可以按如下方式操作：acbacddacbca → acbcaddacbca。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
baba
cc
ddaa
acbacddacbca
```

### 输出

```
2
0
3
2
```



---

---
title: "Trapmigiano Reggiano"
layout: "post"
diff: 普及+/提高
pid: CF2071C
tag: ['搜索', '贪心', '树的遍历']
---

# Trapmigiano Reggiano

## 题目描述

在一个意大利村庄中，一只饥饿的老鼠从给定树 $^{\text{∗}}$ 的顶点 $\textrm{st}$ 出发，该树包含 $n$ 个顶点。

给定一个长度为 $n$ 的排列 $p$ $^{\text{†}}$，共有 $n$ 个步骤。在第 $i$ 步时：

- 一块诱人的帕尔马干酪出现在顶点 $p_i$。若老鼠当前位于顶点 $p_i$，它将停留并享用；否则，它将沿简单路径向 $p_i$ 移动一条边。

你的任务是找到这样的排列，使得经过所有 $n$ 步后，老鼠必定到达陷阱所在的顶点 $\textrm{en}$。

注意：老鼠必须在完成所有 $n$ 步后到达 $\textrm{en}$，但在过程中可能提前经过 $\textrm{en}$。

$^{\text{∗}}$ 树是一个无环的连通图。

$^{\text{†}}$ 长度为 $n$ 的排列是由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是排列，但 $[1,2,2]$ 不是排列（数字 $2$ 重复出现），$[1,3,4]$ 也不是排列（当 $n=3$ 时出现数字 $4$）。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各个测试用例的描述。

每个测试用例的第一行包含三个整数 $n$、$\textrm{st}$ 和 $\textrm{en}$（$1 \le n \le 10^5$；$1 \le \textrm{st}, \textrm{en} \le n$）——分别表示树的顶点数、起始顶点和陷阱顶点。

接下来的 $n-1$ 行每行包含两个整数 $u$ 和 $v$（$1 \le u, v \le n$，$u \neq v$）——表示通过边连接的顶点编号。

保证输入的边构成一棵树。

保证所有测试用例的 $n$ 之和不超过 $10^5$。

## 输出格式

对于每个测试用例：

- 若无解，输出 $-1$；
- 否则，输出 $n$ 个整数 $p_1, p_2, \ldots, p_n$，表示干酪在顶点出现的顺序，确保老鼠最终落入陷阱顶点 $\textrm{en}$。

若存在多个解，输出任意一个即可。

## 说明/提示

第一个测试用例中，当 $n = 1$ 时唯一可能的排列是 $p = [1]$，成功捕获老鼠：

$$ \textrm{st} = 1 \overset{p_1 = 1}{\xrightarrow{\hspace{1.3cm}}} 1 = \textrm{en}. $$

第二个测试用例中，当 $n = 2$ 时一个可能的排列是 $p = [1, 2]$：

$$ \textrm{st} = 1 \overset{p_1 = 1}{\xrightarrow{\hspace{1.3cm}}} 1 \overset{p_2 = 2}{\xrightarrow{\hspace{1.3cm}}} 2 = \textrm{en}. $$

第三个测试用例中，当 $n = 3$ 时一个可能的排列是 $p = [3, 1, 2]$：

$$ \textrm{st} = 2 \overset{p_1 = 3}{\xrightarrow{\hspace{1.3cm}}} 3 \overset{p_2 = 1}{\xrightarrow{\hspace{1.3cm}}} 2 \overset{p_3 = 2}{\xrightarrow{\hspace{1.3cm}}} 2 = \textrm{en}. $$

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
1 1 1
2 1 2
1 2
3 2 2
1 2
2 3
6 1 4
1 2
1 3
4 5
5 6
1 4
```

### 输出

```
1 
1 2 
3 1 2 
1 4 3 2 6 5
```



---

---
title: "Scammy Game Ad"
layout: "post"
diff: 普及+/提高
pid: CF2078D
tag: ['动态规划 DP', '贪心']
---

# Scammy Game Ad

## 题目描述

考虑以下游戏。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2078D/08bde909876902ee9b6ced6653b4847e8c05fa58.png)

游戏中每个关卡包含 $n$ 对门。每对门包含一个左门和一个右门。每个门执行以下两种操作之一：
- **加法操作 (+ $a$)**：将该通道的人数增加固定值 $a$。
- **乘法操作 (× $a$)**：将该通道当前人数乘以整数 $a$。这意味着该通道人数将增加 $(a - 1)$ 倍当前值。

每个操作产生的新增人员可以分配到任意通道。但已存在于某个通道的人员不可转移到另一个通道。

初始时，每个通道各有 $1$ 人。你的任务是确定关卡结束时可达到的最大总人数。

## 输入格式

第一行输入整数 $t$（$1 \leq t \leq 10^4$）——测试用例数量。

每个测试用例的第一行包含一个整数 $n$（$1 \leq n \le 30$）——门对的数量。

接下来每个测试用例的 $n$ 行依次描述每对门的左门和右门信息。每个门的信息以 + $a$（$1 \le a \le 1000$）或 × $a$（$2 \le a \le 3$）形式给出，其中 $a$ 为整数。

## 输出格式

对于每个测试用例，输出一个整数——关卡结束时的最大总人数。

## 说明/提示

第一个测试用例的最优操作方式如下：

初始时，左通道人数 $l=1$，右通道人数 $r=1$。

通过第一对门后：
- 左门产生 $4$ 人（加法操作），右门产生 $1 \cdot (2-1) = 1$ 人（乘法操作）
- 总新增 $4+1=5$ 人，分配 $2$ 人到左通道，$3$ 人到右通道
- 结果：$l=1+2=3$，$r=1+3=4$

通过第二对门后：
- 左门产生 $3 \cdot (3-1) = 6$ 人（乘法操作），右门产生 $4 \cdot (3-1) = 8$ 人（乘法操作）
- 总新增 $6+8=14$ 人，均分 $7$ 人到两个通道
- 结果：$l=3+7=10$，$r=4+7=11$

通过最后一对门后：
- 左门产生 $7$ 人（加法操作），右门产生 $4$ 人（加法操作）
- 总新增 $7+4=11$ 人，分配 $6$ 人到左通道，$5$ 人到右通道
- 结果：$l=10+6=16$，$r=11+5=16$

最终总人数为 $16+16=32$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
3
+ 4 x 2
x 3 x 3
+ 7 + 4
4
+ 9 x 2
x 2 x 3
+ 9 + 10
x 2 + 1
4
x 2 + 1
+ 9 + 10
x 2 x 3
+ 9 x 2
5
x 3 x 3
x 2 x 2
+ 21 + 2
x 2 x 3
+ 41 x 3
```

### 输出

```
32
98
144
351
```



---

---
title: "Floor or Ceil"
layout: "post"
diff: 普及+/提高
pid: CF2082B
tag: ['贪心']
---

# Floor or Ceil

## 题目描述

Ecrade 有一个整数 $x$。存在两种操作：

1. 将 $x$ 替换为 $\left\lfloor \dfrac{x}{2}\right\rfloor$，其中 $\left\lfloor \dfrac{x}{2}\right\rfloor$ 表示不大于 $\dfrac{x}{2}$ 的最大整数。
2. 将 $x$ 替换为 $\left\lceil \dfrac{x}{2}\right\rceil$，其中 $\left\lceil \dfrac{x}{2}\right\rceil$ 表示不小于 $\dfrac{x}{2}$ 的最小整数。

Ecrade 将**恰好执行** $n$ 次操作 1 和 $m$ 次操作 2，且操作顺序任意。他想知道在 $n + m$ 次操作后 $x$ 的**最小可能值**和**最大可能值**。这个问题似乎有些困难，请帮助他！

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来每个测试用例的描述如下：

每个测试用例的唯一一行包含三个整数 $x$，$n$，$m$（$0 \le x, n, m \le 10^9$）。

## 输出格式

对于每个测试用例，在一行中输出两个整数，分别表示操作后 $x$ 的最小可能值和最大可能值。

## 说明/提示

为简化描述，我们将操作 1 称为 $\text{OPER 1}$，操作 2 称为 $\text{OPER 2}$。

在第一个测试用例中：

- 若执行 $12 \xrightarrow{\text{OPER 2}} 6 \xrightarrow{\text{OPER 2}} 3 \xrightarrow{\text{OPER 1}} 1$，可得到最小值 $1$。
- 若执行 $12 \xrightarrow{\text{OPER 2}} 6 \xrightarrow{\text{OPER 1}} 3 \xrightarrow{\text{OPER 2}} 2$，可得到最大值 $2$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
12 1 2
12 1 1
12 0 0
12 1000000000 1000000000
706636307 0 3
```

### 输出

```
1 2
3 3
12 12
0 0
88329539 88329539
```



---

---
title: "Arcology On Permafrost"
layout: "post"
diff: 普及+/提高
pid: CF2084D
tag: ['贪心', '构造']
---

# Arcology On Permafrost

## 题目描述

给定三个整数 $n$、$m$ 和 $k$，其中满足 $m \cdot k < n$。

对于一个由非负整数组成的序列 $b$，定义 $f(b)$ 如下：

- 你可以对 $b$ 进行如下操作：
  - 设 $l$ 表示当前 $b$ 的长度。选择一个正整数 $1 \leq i \leq l - k + 1$，删除从下标 $i$ 到 $i + k - 1$ 的子数组，并将剩余部分拼接。换句话说，将 $b$ 替换为：
    $$
    [b_1, b_2, \ldots, b_{i - 1}, b_{i + k}, b_{i + k + 1}, \ldots, b_l].
    $$
- $f(b)$ 定义为在进行最多 $m$ 次（可以是零次）上述操作后，$\operatorname{mex}(b)$ 的**最小**可能值 $^{\text{∗}}$。

你需要构造一个长度为 $n$ 的非负整数序列 $a$，满足以下条件：
- 对于所有 $1 \le i \le n$，$0 \le a_i \le 10^9$。
- 在所有满足条件的序列 $a$ 中，$f(a)$ 的值最大化。

$^{\text{∗}}$ 集合 $c = \{c_1, c_2, \ldots, c_k\}$ 的最小排除值（MEX）定义为不包含在 $c$ 中的最小非负整数 $x$。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含三个整数 $n$、$m$ 和 $k$（$2 \le n \le 2 \cdot 10^5$，$1 \le m < n$，$1 \le k < n$，$1 \le m \cdot k < n$）。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$0 \le a_i \le 10^9$）。

如果有多个答案，输出任意一个即可。

## 说明/提示

- 在第一个测试用例中，可以证明 $f(a) = 1$ 是最大化的结果。
- 在第二个测试用例中，可以证明 $f(a) = 1$ 是最大化的结果。$f(a) = 1$ 是因为你可以进行以下操作：
  - 选择 $i = 3$，删除下标 $3$ 到 $4$ 的子数组，剩余部分拼接后 $a$ 变为 $[0, 1, 0]$。
  - 选择 $i = 1$，删除下标 $1$ 到 $2$ 的子数组，剩余部分拼接后 $a$ 变为 $[0]$。
- 在第三个测试用例中，可以证明 $f(a) = 2$ 是最大化的结果。$f(a) = 2$ 是因为你可以进行以下操作：
  - 选择 $i = 2$，删除下标 $2$ 到 $5$ 的子数组，剩余部分拼接后 $a$ 变为 $[0, 1]$。
- 在第四个测试用例中，可以证明 $f(a) = 2$ 是最大化的结果。
- 在第五个测试用例中，可以证明 $f(a) = 3$ 是最大化的结果。
- 在第六个测试用例中，可以证明 $f(a) = 2$ 是最大化的结果。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
8
2 1 1
5 2 2
6 1 4
8 2 2
8 1 5
11 3 3
22 6 3
17 2 2
```

### 输出

```
0 0
0 1 0 0 0
0 1 2 2 0 1
0 2 1 0 1 0 8 1
0 1 2 1000000000 1 0 1 2
1 0 0 1 0 2 1 0 2 1 0
0 2 1 0 2 1 0 3 2 1 0 2 1 0 2 1 0 2 1 0 2 1
4 0 2 1 3 4 0 2 1 0 3 4 0 1 2 1 3
```



---

---
title: "Serval and Kaitenzushi Buffet"
layout: "post"
diff: 普及+/提高
pid: CF2085D
tag: ['贪心', '堆']
---

# Serval and Kaitenzushi Buffet

## 题目描述

Serval 发现了一家回转寿司自助餐厅。回转寿司意味着餐厅内有一条传送带，将寿司盘依次传送到顾客 Serval 面前。

在这家餐厅中，每盘寿司恰好包含 $k$ 块寿司，第 $i$ 盘寿司的美味值为 $d_i$。Serval 将在这家餐厅用餐 $n$ 分钟，且在这 $n$ 分钟内必须吃完他从传送带上拿取的所有寿司块。

设未食用的已拿取寿司块计数器为 $r$。初始时 $r = 0$。在第 $i$ 分钟（$1 \leq i \leq n$），只有第 $i$ 盘寿司会被传送到 Serval 面前，他可以执行以下三种操作之一：
- 从传送带上拿取第 $i$ 盘寿司（其美味值为 $d_i$），此时 $r$ 增加 $k$；
- 食用之前从传送带上拿取的 1 块未食用寿司，此时 $r$ 减少 $1$（注意仅当 $r > 0$ 时可执行此操作）；
- 或不做任何操作，此时 $r$ 保持不变。

注意在 $n$ 分钟结束后，$r$ 的值必须为 $0$。

Serval 希望最大化他拿取的所有寿司盘的美味值之和。请帮助他计算这个最大值！

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 10^4$）。接下来描述每个测试用例。

每个测试用例的第一行包含两个整数 $n$ 和 $k$（$1 \leq k < n \leq 2 \cdot 10^5$）——用餐的总分钟数及每盘寿司的块数。

第二行包含 $n$ 个整数 $d_1, d_2, \ldots, d_n$（$1 \leq d_i \leq 10^9$）——每盘寿司的美味值。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数 —— Serval 拿取的所有寿司盘美味值的最大可能和。

## 说明/提示

第一个测试案例中，可以证明 Serval 最多能吃完一盘寿司。由于第二盘寿司的美味值 $6$ 是所有盘中最大的，他会在第二分钟拿取该盘，并在接下来的 $2$ 分钟内吃完它。

| 分钟 | 1 | 2 | 3 | 4 | 5 |
|------|---|---|---|---|---|
| 操作 | — | 拿取 | 食用 | 食用 | — |
| 操作后 $r$ | 0 | 2 | 1 | 0 | 0 |
| 累计美味值 | 0 | 6 | 6 | 6 | 6 |

第二个测试案例中，可以证明最优策略是拿取第一、第三和第六盘寿司。这些盘的美味值之和为 $3 + 4 + 9 = 16$。

| 分钟 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|------|---|---|---|---|---|---|---|
| 操作 | 拿取 | 食用 | 拿取 | 食用 | — | 拿取 | 食用 |
| 操作后 $r$ | 1 | 0 | 1 | 0 | 0 | 1 | 0 |
| 累计美味值 | 3 | 3 | 7 | 7 | 7 | 16 | 16 |

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
5 2
3 6 4 1 2
7 1
3 1 4 1 5 9 2
4 3
4 3 2 1
6 2
1 3 5 2 4 6
6 1
1000000000 1 1000000000 1 1000000000 1
```

### 输出

```
6
16
4
6
3000000000
```



---

---
title: "Canteen (Easy Version)"
layout: "post"
diff: 普及+/提高
pid: CF2089B1
tag: ['贪心', '单调队列']
---

# Canteen (Easy Version)

## 题目描述

这是该问题的简单版本。两个版本的区别在于此版本中，$$k=0$$。只有当你解决了该问题的所有版本时才能进行 hack。

Ecrade 有两个由整数构成的序列 $$$a_0, a_1, \ldots, a_{n - 1}$$$ 和 $$$b_0, b_1, \ldots, b_{n - 1}$$$。保证 $$$a$$$ 中所有元素的总和不超过 $$$b$$$ 中所有元素的总和。

初始时，Ecrade 可以对序列 $$$a$$$ 进行恰好 $$$k$$$ 次修改。保证 $$$k$$$ 不超过 $$$a$$$ 的总和。每次修改操作如下：
- 选择一个整数 $$$i$$$（$$0 \le i < n$$）满足 $$$a\_i > 0$$$，并执行 $$$a_i := a_i - 1$$$。

然后，Ecrade 将对 $$$a$$$ 和 $$$b$$$ 依次执行以下三个操作，这三个操作构成一轮操作：
1. 对每个 $$$0 \le i < n$$$：$$t := \min(a_i, b_i)$$，$$a_i := a_i - t$$，$$b_i := b_i - t$$；
2. 对每个 $$$0 \le i < n$$$：$$c_i := a_{(i - 1) \bmod n}$$；
3. 对每个 $$$0 \le i < n$$$：$$a_i := c_i$$。

Ecrade 想知道，在对 $$$a$$$ 进行恰好 $$$k$$$ 次修改后，使得 $$$a$$$ 中所有元素变为 $$$0$$$ 所需的最小轮数。

然而，这似乎有些复杂，因此请帮助他！

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $$$t$$$（$$1 \le t \le 2 \cdot 10^4$$）。接下来是各测试用例的描述。

每个测试用例的第一行包含两个整数 $$$n$$$、$$k$$（$$1 \le n \le 2 \cdot 10^5$$，$$k = 0$$）。

每个测试用例的第二行包含 $$$n$$$ 个整数 $$$a\_0, a\_1, \ldots, a\_{n - 1}$$$（$$1 \le a_i \le 10^9$$）。

每个测试用例的第三行包含 $$$n$$$ 个整数 $$$b\_0, b\_1, \ldots, b\_{n - 1}$$$（$$1 \le b_i \le 10^9$$）。

保证所有测试用例的 $$$n$$$ 之和不超过 $$$2 \cdot 10^5$$$。同时保证每个测试用例中 $$$a$$$ 的总和不超过 $$$b$$$ 的总和，且 $$$k$$$ 不超过 $$$a$$$ 的总和。

## 输出格式

对于每个测试用例，输出在对 $$$a$$$ 进行恰好 $$$k$$$ 次修改后，使得 $$$a$$$ 中所有元素变为 $$0$$ 所需的最小轮数。


## 说明/提示

在此版本中，Ecrade 不能对 $$$a$$$ 进行修改。

在第一个测试用例中：
- 第一轮操作后，$$a=[0,0,0]$$，$$b=[4,0,0]$$。

在第二个测试用例中：
- 第一轮操作后，$$a=[3,0,0,1]$$，$$b=[3,1,0,0]$$；
- 第二轮操作后，$$a=[1,0,0,0]$$，$$b=[0,1,0,0]$$；
- 第三轮操作后，$$a=[0,1,0,0]$$，$$b=[0,1,0,0]$$；
- 第四轮操作后，$$a=[0,0,0,0]$$，$$b=[0,0,0,0]$$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
3 0
1 1 4
5 1 4
4 0
1 2 3 4
4 3 2 1
4 0
2 1 1 2
1 2 2 1
8 0
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
```

### 输出

```
1
4
4
8
```



---

---
title: "Dining Hall"
layout: "post"
diff: 普及+/提高
pid: CF2090C
tag: ['贪心', '堆']
---

# Dining Hall

## 题目描述

在一个庞大的王国中，有一个无限大的餐厅。

该餐厅可以表示为由单元格 $(x, y)$ 构成的集合，其中 $x, y$ 是自然数。餐厅内还有无数张桌子。每张桌子由四个单元格定义：$(3x + 1, 3y + 1)$、$(3x + 1, 3y + 2)$、$(3x + 2, 3y + 1)$、$(3x + 2, 3y + 2)$，其中 $x, y$ 是非负整数。所有不属于任何桌子的单元格被视为走廊。

客人只能在走廊中移动，且每次只能通过相邻的边移动到相邻的单元格，每次移动耗时相同。注意：客人只能在最后一次移动时坐在桌子上，且必须坐在桌子上。

在王国的一场晚宴中，共有 $n$ 位客人到来，每位客人有一个特征值 $t_i$（取值为 $0$ 或 $1$）。他们按顺序进入大厅，从单元格 $(0, 0)$ 出发走向某张桌子。若第 $i$ 位客人的 $t_i = 1$，则他会选择距离最近的仍有空位的桌子；若 $t_i = 0$，则他会选择距离最近的未被占用的桌子（即使后续可能有其他客人加入）。若存在多张桌子距离相同，则选择 $x$ 坐标最小的单元格；若仍有多个选项，则选择其中 $y$ 坐标最小的单元格。

从单元格到桌子的距离定义为到该桌子上最近的未被占用的单元格的距离。两单元格之间的距离按移动到相邻单元格的次数计算。注意：移动过程中不允许穿过属于桌子的单元格，除非是最后一步（该步骤会将你放置在桌子的最终单元格上）。

为更好理解条件，可参考说明中的图示。

你无需亲自计算所有客人的入座情况，请直接输出每位客人最终入座的单元格。

## 输入格式

第一行包含一个整数 $q$（$1 \leq q \leq 5000$）——测试用例数量。接下来是测试用例描述。

每个测试用例的第一行包含一个整数 $n$（$1 \leq n \leq 50\,000$）——客人数量。

每个测试用例的第二行包含 $n$ 个整数 $t_1, t_2, \ldots, t_n$（$t_i \in \{0, 1\}$）——每位客人的特征值。

保证所有测试用例的 $n$ 之和不超过 $50\,000$。


## 输出格式

对于每个测试用例，输出 $n$ 行——每位客人入座的单元格。

## 说明/提示

第一位客人到单元格 $(1, 1)$ 的距离为 2，因此选择该位置。

第二位客人到单元格 $(1, 2)$ 和 $(2, 1)$ 的距离均为 3，但由于 $1 < 2$，因此选择 $(1, 2)$。无额外约束。

第三位客人到单元格 $(2, 1)$ 的距离为 3，因此选择该位置。

第四位客人到单元格 $(1, 4)$ 的距离为 5，因此选择该位置。

第五位客人到单元格 $(4, 1)$ 的距离为 5。

第六位客人到单元格 $(1, 5)$ 和 $(2, 2)$ 的距离均为 6，但由于 $x$ 坐标更小，因此选择 $(1, 5)$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2090C/14307747f44bf893a0cb5c3731d43642a649f3b9.png)

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2
6
0 1 1 0 0 1
5
1 0 0 1 1
```

### 输出

```
1 1
1 2
2 1
1 4
4 1
1 5
1 1
1 4
4 1
1 2
2 1
```



---

---
title: "Mishkin Energizer"
layout: "post"
diff: 普及+/提高
pid: CF2092D
tag: ['字符串', '贪心']
---

# Mishkin Energizer

## 题目描述

为了准备与老朋友 Fernan 的决斗，Edmond 正在制作一种名为 "Mishkin Energizer" 的能量饮料。该饮料由一个长度为 $n$ 的字符串 $s$ 构成，仅包含字符 L、I 和 T，分别对应饮料中三种不同物质的含量。

当饮料中所有三种物质的数量相等时，我们称其为平衡的。为了增强气场并确保决斗胜利，Edmond 必须通过以下操作使初始字符串变为平衡状态：

1. 选择一个下标 $i$ 满足 $s_i \neq s_{i+1}$（此时 $i + 1$ 必须不超过字符串当前长度）。
2. 在它们之间插入一个字符 $x$（可以是 L、I 或 T），且满足 $x \neq s_i$ 和 $x \neq s_{i+1}$。

帮助 Edmond 通过不超过 $\textbf{2n}$ 次操作使饮料平衡并赢得决斗。若存在多种解，可输出任意一种。若不可能实现，需报告此情况。

## 输入格式

每个测试包含多个测试用例。输入数据第一行包含一个整数 $t$ ($1 \le t \le 100$) —— 测试用例数量。接下来是测试用例描述。

每个测试用例的第一行包含一个整数 $n$ ($1 \le n \le 100$) —— 字符串 $s$ 的长度。

每个测试用例的第二行包含一个长度为 $n$ 的字符串 $s$，仅由字符 L、I 和 T 组成。

## 输出格式

对于每个测试用例，若无解则输出 $-1$。否则：

- 第一行输出一个整数 $m$ ($0 \le m \le 2n$) —— 执行的操作次数。
- 接下来的 $m$ 行中，第 $l$ 行输出一个整数 $i$ ($1 \le i < n + l - 1$)，表示在第 $i$ 和 $i + 1$ 个字符之间插入新字符。该操作必须满足 $s_i \neq s_{i+1}$。

若有多种解，可输出任意一种。注意本题不要求最小化操作次数。

## 说明/提示

第一个测试案例中，可执行以下操作序列：TILII $\rightarrow$ TLILII $\rightarrow$ TLTILII $\rightarrow$ TLTLILII $\rightarrow$ TLTLTILII。

第二个测试案例中无法进行任何操作，答案为 $-1$。

第三个测试案例中初始字符串已满足三种物质数量相等。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
5
TILII
1
L
3
LIT
```

### 输出

```
4
1
2
3
4
-1
0
```



---

---
title: "Hackers and Neural Networks"
layout: "post"
diff: 普及+/提高
pid: CF2093F
tag: ['字符串', '贪心', '枚举']
---

# Hackers and Neural Networks

## 题目描述

黑客们再次尝试利用神经网络的输出来创造有趣的短语。这次，他们希望获得一个长度为 $n$ 的字符串数组 $a$。

最初，他们有一个长度为 $n$ 的数组 $c$，其中所有位置都是空白，用符号 $*$ 表示。例如，如果 $n=4$，那么初始时 $c=[*,*,*,*]$。

黑客们可以访问 $m$ 个神经网络，每个神经网络都有自己对请求的答案版本——一个长度为 $n$ 的字符串数组 $b_i$。

黑客们试图通过以下操作从数组 $c$ 得到数组 $a$：

1. 选择一个神经网络 $i$，它将执行对数组 $c$ 的下一个操作：随机选择一个空白位置（例如位置 $j$），并将 $c_j$ 替换为 $b_{i, j}$。例如，如果选择第一个神经网络且 $c = [*, \text{«like»}, *]$，而 $b_1 = [\text{«I»}, \text{«love»}, \text{«apples»}]$，那么经过第一个神经网络的操作后，$c$ 可能变为 $[\text{«I»}, \text{«like»}, *]$ 或 $[*, \text{«like»}, \text{«apples»}]$。
2. 选择一个位置 $j$，并将 $c_j$ 替换为空白。

不幸的是，由于黑客访问神经网络的方式，他们只能在所有操作完成后看到修改后的数组 $c$，因此他们必须提前指定完整的操作序列。

然而，神经网络的随机行为可能导致无法获得目标数组 $a$，或者需要过多的操作才能获得它。

因此，黑客们希望你能帮助他们选择一个操作序列，确保以最少的操作次数获得数组 $a$。

更正式地说，如果存在一个操作序列可以确保从数组 $c$ 得到数组 $a$，那么在所有这样的序列中，找出操作次数最少的序列，并输出其中的操作次数。

如果不存在将数组 $c$ 转换为数组 $a$ 的操作序列，则输出 $-1$。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 1000$）——测试用例的数量。

每个测试用例的第一行包含两个整数 $n$ 和 $m$（$1 \le n, m \le 500$）——原始数组 $a$ 的长度和神经网络的数量。

每个测试用例的第二行包含数组 $a$，由 $n$ 个字符串 $a_i$（$1 \le |a_i| \le 10$）组成，用空格分隔。

接下来的 $m$ 行，每行包含一个数组 $b_i$，由 $n$ 个字符串 $b_{i, j}$（$1 \le |b_{i,j}| \le 10$）组成，用空格分隔。

保证所有测试用例的 $|a_i|$ 和 $|b_{i, j}|$ 的总和不超过 $2 \cdot 10^5$，且所有测试用例的 $n \cdot m$ 总和也不超过 $2 \cdot 10^5$。

保证输入字符串仅由大小写拉丁字母组成。

注意，每个输入字符串的长度不超过 $10$。

## 输出格式

输出 $t$ 个数字——每个测试用例一个数字，每个数字单独占一行。

如果存在确保从第 $i$ 个测试用例的数组 $c$ 得到数组 $a$ 的操作序列，则第 $i$ 个数字是该序列的最小操作次数。

否则，对于第 $i$ 个数字，输出 $-1$。

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
3 3
I love apples
He likes apples
I love cats
They love dogs
3 2
Icy wake up
wake Icy up
wake up Icy
4 3
c o D E
c o D s
c O l S
c o m E
4 5
a s k A
d s D t
O R i A
a X b Y
b a k A
u s k J
```

### 输出

```
5
-1
6
8
```



---

---
title: "Shorten the Array"
layout: "post"
diff: 普及+/提高
pid: CF2093G
tag: ['贪心', '字典树 Trie']
---

# Shorten the Array

## 题目描述

一个长度为 $m$ 的数组 $b$ 的美观度定义为所有可能数对 $1 \le i \le j \le m$ 中 $b_i \oplus b_j$ 的最大值，其中 $x \oplus y$ 表示数字 $x$ 和 $y$ 的[按位异或](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。我们将数组 $b$ 的美观度记为 $f(b)$。

如果一个数组 $b$ 满足 $f(b) \ge k$，则称该数组是美观的。

最近，Kostya 从商店购买了一个长度为 $n$ 的数组 $a$。他认为这个数组太长了，因此计划从中截取一个美观的子数组。也就是说，他需要选择两个数字 $l$ 和 $r$（$1 \le l \le r \le n$），使得子数组 $a_{l \dots r}$ 是美观的。这样的子数组的长度为 $r - l + 1$。整个数组 $a$ 也被视为一个子数组（此时 $l = 1$ 且 $r = n$）。

你的任务是找出数组 $a$ 中最短美观子数组的长度。如果不存在美观的子数组，则输出 $-1$。

## 输入格式

第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。

接下来是 $t$ 个由两行组成的测试块：

每个测试块的第一行包含两个整数 $n$ 和 $k$（$1 \le n \le 2 \cdot 10^5$，$0 \le k \le 10^9$）。

每个测试块的第二行包含数组 $a$，由 $n$ 个整数组成（$0 \le a_i \le 10^9$）。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。


## 输出格式

对于每个测试用例，输出一个整数——满足 $f(a_{l \dots r}) \ge k$ 的最短子数组 $(l, r)$ 的长度。如果不存在这样的子数组，则输出 $-1$。


## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
6
5 0
1 2 3 4 5
5 7
1 2 3 4 5
5 8
1 2 3 4 5
5 7
3 5 1 4 2
5 3
3 5 1 4 2
6 71
26 56 12 45 60 27
```

### 输出

```
1
2
-1
4
2
-1
```



---

---
title: "四重交换"
layout: "post"
diff: 普及+/提高
pid: CF2101B
tag: ['贪心']
---

# 四重交换

## 题目描述

给定一个长度为 $n$ 的排列 $a$ $^{\text{∗}}$。你可以进行以下操作任意次数（包括零次）：

- 选择一个下标 $1 \le i \le n - 3$。然后，同时交换 $a_i$ 和 $a_{i+2}$，以及 $a_{i+1}$ 和 $a_{i+3}$。换句话说，排列 $a$ 将从 $[\ldots, a_i, a_{i+1}, a_{i+2}, a_{i+3}, \ldots]$ 变为 $[\ldots, a_{i+2}, a_{i+3}, a_i, a_{i+1}, \ldots]$。

请确定通过任意次上述操作后能得到的字典序最小的排列 $^{\text{†}}$。

$^{\text{∗}}$ 一个长度为 $n$ 的排列是由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（因为 $2$ 出现了两次），$[1,3,4]$ 也不是排列（$n=3$ 但数组中出现了 $4$）。

$^{\text{†}}$ 对于两个相同长度的数组 $x$ 和 $y$，$x$ 字典序小于 $y$ 当且仅当满足以下条件：
- 在第一个 $x$ 和 $y$ 不同的位置，$x$ 的元素小于 $y$ 的对应元素。

## 输入格式

多组数据，第一行一个整数 $t(1\le t\le 1000)$。

对于每组数据，第一行一个整数 $n(4\le n\le 2\times 10^5)$。\
第二行 $n$ 个整数 $a_1,a_2,\cdots,a_n(1\le a_i\le n)$，保证 $a$ 为 $1$ 到 $n$ 的排列。

## 输出格式

对于每组数据，输出一行 $n$ 个整数，表示可以得到的字典序最小的排列。

## 说明/提示

**样例解释**

第一组数据中，选择 $i=1$ 执行一次操作，排列变为 $[1,2,3,4]$，可以证明这是可以得到的字典序最小的排列。

第二组数据中，一种可以得到字典序最小的排列的操作如下：

- 选择 $i=2$ 执行一次操作，排列变为 $[5,1,2,4,3]$；
- 选择 $i=1$ 执行一次操作，排列变为 $[2,4,5,1,3]$；
- 选择 $i=2$ 执行一次操作，排列变为 $[2,1,3,4,5]$。

## 样例 #1

### 输入

```
3
4
3 4 1 2
5
5 4 3 1 2
10
10 9 8 7 6 5 4 3 2 1
```

### 输出

```
1 2 3 4 
2 1 3 4 5 
2 1 4 3 6 5 8 7 10 9
```



---

---
title: "Apple Tree Traversing"
layout: "post"
diff: 普及+/提高
pid: CF2107D
tag: ['贪心', '树的直径']
---

# Apple Tree Traversing

## 题目描述

有一棵 $n$ 个点的苹果树，每个结点上有一棵苹果。你有一张白纸。

你将要在苹果树上穿梭，重复做以下事情直到苹果树上没有苹果：
- 选择一条路径 $(u,v)$，满足这条路径上所有点上都有苹果。
- 拿走这条路径上的所有苹果，设你这次拿了 $d$ 个苹果，在你的纸上依次写下三个数字 $d$，$u$ 和 $v$。

称结束后你的纸上的数字构成的数列为 $a$。输出可能的字典序最大的 $a$。

## 输入格式

多组数据，第一行一个整数 $t(1\le t\le 10^4)$ 表示数据组数。

对于每组数据，第一行一个整数 $n(1\le n\le 1.5\times 10^5)$。\
接下来 $n-1$ 行，每行两个数字表示树上的一条边。

保证一个测试点中 $\sum n\le 1.5\times 10^5$。

## 输出格式

每组数据输出一行，为可能的字典序最大的 $a$。可以证明 $a$ 的长度 $\le 3\times n$。

## 说明/提示

在第一组数据中，我们进行以下操作：
- 选择路径 $(4,3)$，拿走结点 $1,3,4$ 上面的苹果，在纸上写下 $3,4,3$。
- 选择路径 $(2,2)$，拿走结点 $2$ 上面的苹果，在纸上写下 $1,2,2$。

最终形成了 $a=(3,4,3,1,2,2)$，可以证明这是字典序最大的合法结果。

By chenxi2009

## 样例 #1

### 输入

```
6
4
1 2
1 3
1 4
4
2 1
2 4
2 3
5
1 2
2 3
3 4
4 5
1
8
6 3
3 5
5 4
4 2
5 1
1 8
3 7
6
3 2
2 6
2 5
5 4
4 1
```

### 输出

```
3 4 3 1 2 2 
3 4 3 1 1 1 
5 5 1 
1 1 1 
5 8 7 2 4 2 1 6 6 
5 6 1 1 3 3
```



---

---
title: "穿越苹果树"
layout: "post"
diff: 普及+/提高
pid: CF2107D
tag: ['贪心', '树的直径']
---

# 穿越苹果树

## 题目描述

有一棵 $n$ 个点的苹果树，每个结点上有一棵苹果。你有一张白纸。

你将要在苹果树上穿梭，重复做以下事情直到苹果树上没有苹果：
- 选择一条路径 $(u,v)$，满足这条路径上所有点上都有苹果。
- 拿走这条路径上的所有苹果，设你这次拿了 $d$ 个苹果，在你的纸上依次写下三个数字 $d$，$u$ 和 $v$。

称结束后你的纸上的数字构成的数列为 $a$。输出可能的字典序最大的 $a$。

## 输入格式

多组数据，第一行一个整数 $t(1\le t\le 10^4)$ 表示数据组数。

对于每组数据，第一行一个整数 $n(1\le n\le 1.5\times 10^5)$。\
接下来 $n-1$ 行，每行两个数字表示树上的一条边。

保证一个测试点中 $\sum n\le 1.5\times 10^5$。

## 输出格式

每组数据输出一行，为可能的字典序最大的 $a$。可以证明 $a$ 的长度 $\le 3\times n$。

## 说明/提示

在第一组数据中，我们进行以下操作：
- 选择路径 $(4,3)$，拿走结点 $1,3,4$ 上面的苹果，在纸上写下 $3,4,3$。
- 选择路径 $(2,2)$，拿走结点 $2$ 上面的苹果，在纸上写下 $1,2,2$。

最终形成了 $a=(3,4,3,1,2,2)$，可以证明这是字典序最大的合法结果。

By chenxi2009

## 样例 #1

### 输入

```
6
4
1 2
1 3
1 4
4
2 1
2 4
2 3
5
1 2
2 3
3 4
4 5
1
8
6 3
3 5
5 4
4 2
5 1
1 8
3 7
6
3 2
2 6
2 5
5 4
4 1
```

### 输出

```
3 4 3 1 2 2 
3 4 3 1 1 1 
5 5 1 
1 1 1 
5 8 7 2 4 2 1 6 6 
5 6 1 1 3 3
```



---

---
title: "LCM Challenge"
layout: "post"
diff: 普及+/提高
pid: CF235A
tag: ['贪心', '枚举']
---

# LCM Challenge

## 题目描述

Some days ago, I learned the concept of LCM (least common multiple). I've played with it for several times and I want to make a big number with it.

But I also don't want to use many numbers, so I'll choose three positive integers (they don't have to be distinct) which are not greater than $ n $ . Can you help me to find the maximum possible least common multiple of these three integers?

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=10^{6} $ ) — the $ n $ mentioned in the statement.

## 输出格式

Print a single integer — the maximum possible LCM of three not necessarily distinct positive integers that are not greater than $ n $ .

## 说明/提示

The least common multiple of some positive integers is the least positive integer which is multiple for each of them.

The result may become very large, 32-bit integer won't be enough. So using 64-bit integers is recommended.

For the last example, we can chose numbers $ 7 $ , $ 6 $ , $ 5 $ and the LCM of them is $ 7·6·5=210 $ . It is the maximum value we can get.

## 样例 #1

### 输入

```
9

```

### 输出

```
504

```

## 样例 #2

### 输入

```
7

```

### 输出

```
210

```



---

---
title: "Vasily the Bear and Sequence"
layout: "post"
diff: 普及+/提高
pid: CF336C
tag: ['贪心', '枚举', '进制']
---

# Vasily the Bear and Sequence

## 题目描述

Vasily the bear has got a sequence of positive integers $ a_{1},a_{2},...,a_{n} $ . Vasily the Bear wants to write out several numbers on a piece of paper so that the beauty of the numbers he wrote out was maximum.

The beauty of the written out numbers $ b_{1},b_{2},...,b_{k} $ is such maximum non-negative integer $ v $ , that number $ b_{1} $ $ and $ $ b_{2} $ $ and $ $ ... $ $ and $ $ b_{k} $ is divisible by number $ 2^{v} $ without a remainder. If such number $ v $ doesn't exist (that is, for any non-negative integer $ v $ , number $ b_{1} $ $ and $ $ b_{2} $ $ and $ $ ... $ $ and $ $ b_{k} $ is divisible by $ 2^{v} $ without a remainder), the beauty of the written out numbers equals -1.

Tell the bear which numbers he should write out so that the beauty of the written out numbers is maximum. If there are multiple ways to write out the numbers, you need to choose the one where the bear writes out as many numbers as possible.

Here expression $ x $ $ and $ $ y $ means applying the bitwise AND operation to numbers $ x $ and $ y $ . In programming languages C++ and Java this operation is represented by "&", in Pascal — by "and".

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ). The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{1}&lt;a_{2}&lt;...&lt;a_{n}<=10^{9}) $ .

## 输出格式

In the first line print a single integer $ k $ $ (k&gt;0) $ , showing how many numbers to write out. In the second line print $ k $ integers $ b_{1},b_{2},...,b_{k} $ — the numbers to write out. You are allowed to print numbers $ b_{1},b_{2},...,b_{k} $ in any order, but all of them must be distinct. If there are multiple ways to write out the numbers, choose the one with the maximum number of numbers to write out. If there still are multiple ways, you are allowed to print any of them.

## 样例 #1

### 输入

```
5
1 2 3 4 5

```

### 输出

```
2
4 5

```

## 样例 #2

### 输入

```
3
1 2 4

```

### 输出

```
1
4

```



---

---
title: "Wonderful Randomized Sum"
layout: "post"
diff: 普及+/提高
pid: CF33C
tag: ['数学', '贪心', '前缀和']
---

# Wonderful Randomized Sum

## 题目描述

Learn, learn and learn again — Valera has to do this every day. He is studying at mathematical school, where math is the main discipline. The mathematics teacher loves her discipline very much and tries to cultivate this love in children. That's why she always gives her students large and difficult homework. Despite that Valera is one of the best students, he failed to manage with the new homework. That's why he asks for your help. He has the following task. A sequence of $ n $ numbers is given. A prefix of a sequence is the part of the sequence (possibly empty), taken from the start of the sequence. A suffix of a sequence is the part of the sequence (possibly empty), taken from the end of the sequence. It is allowed to sequentially make two operations with the sequence. The first operation is to take some prefix of the sequence and multiply all numbers in this prefix by $ -1 $ . The second operation is to take some suffix and multiply all numbers in it by $ -1 $ . The chosen prefix and suffix may intersect. What is the maximum total sum of the sequence that can be obtained by applying the described operations?

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — amount of elements in the sequence. The second line contains $ n $ integers $ a_{i} $ ( $ -10^{4}<=a_{i}<=10^{4} $ ) — the sequence itself.

## 输出格式

The first and the only line of the output should contain the answer to the problem.

## 样例 #1

### 输入

```
3
-1 -2 -3

```

### 输出

```
6

```

## 样例 #2

### 输入

```
5
-4 2 0 5 0

```

### 输出

```
11

```

## 样例 #3

### 输入

```
5
-1 10 -5 10 -2

```

### 输出

```
18

```



---

---
title: "Lorry"
layout: "post"
diff: 普及+/提高
pid: CF3B
tag: ['贪心', '背包 DP', '队列']
---

# Lorry

## 题目描述

给定整数 $n,v$。  

有一辆载重量为 $v$ 的货车，准备运送两种物品。物品 A 的重量为 $1$，物体 B 的重量为 $2$，每个物品都有一个价值 $p_i$。求货车可以运送的物品的最大价值。

## 输入格式

第一个行包含两个整数 $n$ 和 $v$，分别表示有 $n$ 个物品，货车的载重量为 $v$。（$1\le n\le10^5$，$1\le v\le10^9$）

接下来 $n$ 行，每行两个整数，分别表示物品的重量 $t_i$ 和价值 $p_i$。（$t_i=1$ 或 $2$，$1\le p_i\le10^4$）

## 输出格式

第一行，一个整数，表示价值之和的最大值。

第二行，构成最大价值的物品的编号（如果答案不唯一，请输出其中任何一个）。

## 样例 #1

### 输入

```
3 2
1 2
2 7
1 3

```

### 输出

```
7
2

```



---

---
title: "The Child and Toy"
layout: "post"
diff: 普及+/提高
pid: CF437C
tag: ['图论', '贪心']
---

# The Child and Toy

## 题目描述

On Children's Day, the child got a toy from Delayyy as a present. However, the child is so naughty that he can't wait to destroy the toy.

The toy consists of $ n $ parts and $ m $ ropes. Each rope links two parts, but every pair of parts is linked by at most one rope. To split the toy, the child must remove all its parts. The child can remove a single part at a time, and each remove consume an energy. Let's define an energy value of part $ i $ as $ v_{i} $ . The child spend $ v_{f1}+v_{f2}+...+v_{fk} $ energy for removing part $ i $ where $ f_{1},f_{2},...,f_{k} $ are the parts that are directly connected to the $ i $ -th and haven't been removed.

Help the child to find out, what is the minimum total energy he should spend to remove all $ n $ parts.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=1000 $ ; $ 0<=m<=2000 $ ). The second line contains $ n $ integers: $ v_{1},v_{2},...,v_{n} $ ( $ 0<=v_{i}<=10^{5} $ ). Then followed $ m $ lines, each line contains two integers $ x_{i} $ and $ y_{i} $ , representing a rope from part $ x_{i} $ to part $ y_{i} $ ( $ 1<=x_{i},y_{i}<=n; x_{i}≠y_{i} $ ).

Consider all the parts are numbered from $ 1 $ to $ n $ .

## 输出格式

Output the minimum total energy the child should spend to remove all $ n $ parts of the toy.

## 说明/提示

One of the optimal sequence of actions in the first sample is:

- First, remove part $ 3 $ , cost of the action is $ 20 $ .
- Then, remove part $ 2 $ , cost of the action is $ 10 $ .
- Next, remove part $ 4 $ , cost of the action is $ 10 $ .
- At last, remove part $ 1 $ , cost of the action is $ 0 $ .

So the total energy the child paid is $ 20+10+10+0=40 $ , which is the minimum.

In the second sample, the child will spend $ 400 $ no matter in what order he will remove the parts.

## 样例 #1

### 输入

```
4 3
10 20 30 40
1 4
1 2
2 3

```

### 输出

```
40

```

## 样例 #2

### 输入

```
4 4
100 100 100 100
1 2
2 3
2 4
3 4

```

### 输出

```
400

```

## 样例 #3

### 输入

```
7 10
40 10 20 10 20 80 40
1 5
4 7
4 5
5 2
5 7
6 4
1 6
1 3
4 3
1 4

```

### 输出

```
160

```



---

---
title: "Little Victor and Set"
layout: "post"
diff: 普及+/提高
pid: CF460D
tag: ['贪心', '枚举', '构造']
---

# Little Victor and Set

## 题目描述

Little Victor adores the sets theory. Let us remind you that a set is a group of numbers where all numbers are pairwise distinct. Today Victor wants to find a set of integers $ S $ that has the following properties:

- for all $ x $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF460D/26c8948a606517ebae5f50ff9b8fc7d91f76f3df.png) the following inequality holds $ l<=x<=r $ ;
- $ 1<=|S|<=k $ ;
- lets denote the $ i $ -th element of the set $ S $ as $ s_{i} $ ; value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF460D/7523823a9f324064de1df35c0e0503740f7be786.png) must be as small as possible.

Help Victor find the described set.

## 输入格式

The first line contains three space-separated integers $ l,r,k $ $ (1<=l<=r<=10^{12}; 1<=k<=min(10^{6},r-l+1)) $ .

## 输出格式

Print the minimum possible value of $ f(S) $ . Then print the cardinality of set $ |S| $ . Then print the elements of the set in any order.

If there are multiple optimal sets, you can print any of them.

## 说明/提示

Operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF460D/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) represents the operation of bitwise exclusive OR. In other words, it is the XOR operation.

## 样例 #1

### 输入

```
8 15 3

```

### 输出

```
1
2
10 11

```

## 样例 #2

### 输入

```
8 30 7

```

### 输出

```
0
5
14 9 28 11 16

```



---

---
title: "Two Sets"
layout: "post"
diff: 普及+/提高
pid: CF468B
tag: ['贪心', '并查集', '2-SAT']
---

# Two Sets

## 题目描述

> 给出 $n$ 个各不相同的数字，将它们分别放入 $A$ 和 $B$ 两个集合中，使它们满足：
> * 若数字 $x$ 在集合 $A$ 中，那么数字 $a-x$ 也在集合 $A$ 中；
> * 若数字 $x$ 在集合 $B$ 中，那么数字 $b-x$ 也在集合 $B$ 中。

## 输入格式

> 
> 输入的第一行输入三个整数 $n,a,b (1 \leq n \leq 10^{5} ; 1 \leq a,b \leq 10^{9} )$。
> 
> 输入的第二行有 $n$ 个各不相同的正整数，且每个正整数的数值大小都在 $[1,10^{9}]$ 内。

## 输出格式

> 
> 若不能能将这 $n$ 个数在满足条件的情况下全部放入 $A$ 和 $B$ 这两个集合中，则输出 `NO` 。
>
> 若这 $n$ 个数在满足条件的情况下能被全部放入 $A$ 和 $B$ 这两个集合中，则第一行输出 `YES` ，第二行输出 $n$ 个数 $0$ 或 $1$ ，第 $i$ 个数为 $0$ 表示第 $i$ 个数在集合 $A$ 中，第 $i$ 个数为 $1$ 表示第 $i$ 个数在集合 $B$ 中。

## 样例 #1

### 输入

```
4 5 9
2 3 4 5

```

### 输出

```
YES
0 0 1 1

```

## 样例 #2

### 输入

```
3 3 4
1 2 4

```

### 输出

```
NO

```



---

---
title: "Bits"
layout: "post"
diff: 普及+/提高
pid: CF484A
tag: ['贪心', '进制', '位运算']
---

# Bits

## 题目描述

Let's denote as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) the number of bits set ('1' bits) in the binary representation of the non-negative integer $ x $ .

You are given multiple queries consisting of pairs of integers $ l $ and $ r $ . For each query, find the $ x $ , such that $ l<=x<=r $ , and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) is maximum possible. If there are multiple such numbers find the smallest of them.

## 输入格式

Let's denote as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) the number of bits set ('1' bits) in the binary representation of the non-negative integer $ x $ .

You are given multiple queries consisting of pairs of integers $ l $ and $ r $ . For each query, find the $ x $ , such that $ l<=x<=r $ , and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) is maximum possible. If there are multiple such numbers find the smallest of them.

## 输出格式

For each query print the answer in a separate line.

## 说明/提示

Let's denote as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) the number of bits set ('1' bits) in the binary representation of the non-negative integer $ x $ .

You are given multiple queries consisting of pairs of integers $ l $ and $ r $ . For each query, find the $ x $ , such that $ l<=x<=r $ , and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) is maximum possible. If there are multiple such numbers find the smallest of them.

## 样例 #1

### 输入

```
3
1 2
2 4
1 10

```

### 输出

```
1
3
7

```



---

---
title: "Clique Problem"
layout: "post"
diff: 普及+/提高
pid: CF527D
tag: ['贪心', '排序', '构造']
---

# Clique Problem

## 题目描述

数轴上有 $n$ 个点，第 $i$ 个点的坐标为 $x_i$，权值为  $w_i$。两个点 $i,j$ 之间存在一条边当且仅当 $abs(x_i-x_j)\geq w_i+w_j$ 。 你需要求出这张图的最大团的点数。

团的定义：两两之间有边的顶点集合。

## 输入格式

第一行一个整数 $n$，接下来 $n$ 行每行两个整数 $x_i,w_i$ 。

## 输出格式

一行一个整数表示答案。 

感谢@Asougi_Kazuma 提供的翻译。

感谢@皎月半洒花 将翻译改成了正常人能看明白的翻译。

## 样例 #1

### 输入

```
4
2 3
3 1
6 1
0 2

```

### 输出

```
3

```



---

---
title: "Group Photo 2 (online mirror version)"
layout: "post"
diff: 普及+/提高
pid: CF529B
tag: ['贪心', '枚举', '排序']
---

# Group Photo 2 (online mirror version)

## 题目描述

Many years have passed, and $ n $ friends met at a party again. Technologies have leaped forward since the last meeting, cameras with timer appeared and now it is not obligatory for one of the friends to stand with a camera, and, thus, being absent on the photo.

Simply speaking, the process of photographing can be described as follows. Each friend occupies a rectangle of pixels on the photo: the $ i $ -th of them in a standing state occupies a $ w_{i} $ pixels wide and a $ h_{i} $ pixels high rectangle. But also, each person can lie down for the photo, and then he will occupy a $ h_{i} $ pixels wide and a $ w_{i} $ pixels high rectangle.

The total photo will have size $ W×H $ , where $ W $ is the total width of all the people rectangles, and $ H $ is the maximum of the heights. The friends want to determine what minimum area the group photo can they obtain if no more than $ n/2 $ of them can lie on the ground (it would be strange if more than $ n/2 $ gentlemen lie on the ground together, isn't it?..)

Help them to achieve this goal.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=1000 $ ) — the number of friends.

The next $ n $ lines have two integers $ w_{i},h_{i} $ ( $ 1<=w_{i},h_{i}<=1000 $ ) each, representing the size of the rectangle, corresponding to the $ i $ -th friend.

## 输出格式

Print a single integer equal to the minimum possible area of the photo containing all friends if no more than $ n/2 $ of them can lie on the ground.

## 样例 #1

### 输入

```
3
10 1
20 2
30 3

```

### 输出

```
180

```

## 样例 #2

### 输入

```
3
3 1
2 2
4 3

```

### 输出

```
21

```

## 样例 #3

### 输入

```
1
5 10

```

### 输出

```
50

```



---

---
title: "Amr and Chemistry"
layout: "post"
diff: 普及+/提高
pid: CF558C
tag: ['动态规划 DP', '贪心', '枚举', '进制', '字典树 Trie']
---

# Amr and Chemistry

## 题目描述

Amr loves Chemistry, and specially doing experiments. He is preparing for a new interesting experiment.

Amr has $ n $ different types of chemicals. Each chemical $ i $ has an initial volume of $ a_{i} $ liters. For this experiment, Amr has to mix all the chemicals together, but all the chemicals volumes must be equal first. So his task is to make all the chemicals volumes equal.

To do this, Amr can do two different kind of operations.

- Choose some chemical $ i $ and double its current volume so the new volume will be $ 2a_{i} $
- Choose some chemical $ i $ and divide its volume by two (integer division) so the new volume will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558C/2af906789c62f9845274f856d2f941f2357aa169.png)

Suppose that each chemical is contained in a vessel of infinite volume. Now Amr wonders what is the minimum number of operations required to make all the chemicals volumes equal?

## 输入格式

The first line contains one number $ n $ ( $ 1<=n<=10^{5} $ ), the number of chemicals.

The second line contains $ n $ space separated integers $ a_{i} $ ( $ 1<=a_{i}<=10^{5} $ ), representing the initial volume of the $ i $ -th chemical in liters.

## 输出格式

Output one integer the minimum number of operations required to make all the chemicals volumes equal.

## 说明/提示

In the first sample test, the optimal solution is to divide the second chemical volume by two, and multiply the third chemical volume by two to make all the volumes equal $ 4 $ .

In the second sample test, the optimal solution is to divide the first chemical volume by two, and divide the second and the third chemical volumes by two twice to make all the volumes equal $ 1 $ .

## 样例 #1

### 输入

```
3
4 8 2

```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
3 5 6

```

### 输出

```
5
```



---

---
title: "Package Delivery"
layout: "post"
diff: 普及+/提高
pid: CF627C
tag: ['贪心']
---

# Package Delivery

## 题目描述

Johnny drives a truck and must deliver a package from his hometown to the district center. His hometown is located at point $ 0 $ on a number line, and the district center is located at the point $ d $ .

Johnny's truck has a gas tank that holds exactly $ n $ liters, and his tank is initially full. As he drives, the truck consumes exactly one liter per unit distance traveled. Moreover, there are $ m $ gas stations located at various points along the way to the district center. The $ i $ -th station is located at the point $ x_{i} $ on the number line and sells an unlimited amount of fuel at a price of $ p_{i} $ dollars per liter. Find the minimum cost Johnny must pay for fuel to successfully complete the delivery.

## 输入格式

The first line of input contains three space separated integers $ d $ , $ n $ , and $ m $ ( $ 1<=n<=d<=10^{9} $ , $ 1<=m<=200\ 000 $ ) — the total distance to the district center, the volume of the gas tank, and the number of gas stations, respectively.

Each of the next $ m $ lines contains two integers $ x_{i} $ , $ p_{i} $ ( $ 1<=x_{i}<=d-1 $ , $ 1<=p_{i}<=10^{6} $ ) — the position and cost of gas at the $ i $ -th gas station. It is guaranteed that the positions of the gas stations are distinct.

## 输出格式

Print a single integer — the minimum cost to complete the delivery. If there is no way to complete the delivery, print -1.

## 说明/提示

In the first sample, Johnny's truck holds $ 4 $ liters. He can drive $ 3 $ units to the first gas station, buy $ 2 $ liters of gas there (bringing the tank to $ 3 $ liters total), drive $ 3 $ more units to the third gas station, buy $ 4 $ liters there to fill up his tank, and then drive straight to the district center. His total cost is $ 2·5+4·3=22 $ dollars.

In the second sample, there is no way for Johnny to make it to the district center, as his tank cannot hold enough gas to take him from the latest gas station to the district center.

## 样例 #1

### 输入

```
10 4 4
3 5
5 8
6 3
8 4

```

### 输出

```
22

```

## 样例 #2

### 输入

```
16 5 2
8 2
5 1

```

### 输出

```
-1

```



---

---
title: "Memory and De-Evolution"
layout: "post"
diff: 普及+/提高
pid: CF712C
tag: ['贪心', '枚举']
---

# Memory and De-Evolution

## 题目描述

Memory 对物体，尤其是三角形的变化感兴趣。 他有一个边长为 $x$ 的等边三角形，他希望通过一些操作获得一个边长为 $y$ 的等边三角形。

他一次可以修改当前三角形一边的长度，修改后也应为合法的三角形。每次修改后，每一边的长度都应该是整数。

Memory 要获得边长 $y$ 的等边三角形，所需的最小修改次数是多少？

## 输入格式

第一行包含两个整数 $x$ 和 $y$（$3\le y < x \le 100000$），分别为最开始的三角形边长与想要获得的三角形边长。

## 输出格式

输出一个整数，即为最小的修改次数。

## 样例 #1

### 输入

```
6 3

```

### 输出

```
4

```

## 样例 #2

### 输入

```
8 5

```

### 输出

```
3

```

## 样例 #3

### 输入

```
22 4

```

### 输出

```
6

```



---

---
title: "Ability To Convert"
layout: "post"
diff: 普及+/提高
pid: CF758D
tag: ['贪心', '进制']
---

# Ability To Convert

## 题目描述

亚历山大正在学习如何把十进制数字转换成其他进制，但是他不懂英文字母，所以他只是把数值按照十进制数字的方式写出来。这意味着他会用 10 代替英文字母 A。这样，他就会把十进制的 475 转换成十六进制的 11311（475=1·16^2+13·16^1+11·16^0）。亚历山大平静的生活着，直到有一天他试着把这些数字转换回十进制数字。

亚历山大记着他总是用较小的数字工作，所以他需要找到在 n 进制的基础下，用他的转换系统得出数字 k 的最小十进制数。

## 输入格式

第一行是一个正整数 n ( 2<=n<=10^9)，第二行有一个正整数 k ，满足数字 k中包含不超过 60 个数值。第二行整数中的没每一个数字都严格小于 n。

亚历山大保证答案存在且不超过 10^18，数字 k 不含前导 0.

## 输出格式

输出一个数字 x —— 问题的答案。

## 样例 #1

### 输入

```
13
12

```

### 输出

```
12
```

## 样例 #2

### 输入

```
16
11311

```

### 输出

```
475
```

## 样例 #3

### 输入

```
20
999

```

### 输出

```
3789
```

## 样例 #4

### 输入

```
17
2016

```

### 输出

```
594
```



---

---
title: "Fire"
layout: "post"
diff: 普及+/提高
pid: CF864E
tag: ['贪心', '排序', '背包 DP']
---

# Fire

## 题目描述

某人的房子着火了，他想从大火中带走价值总和尽量多的物品，每次他只能带走一个，分别给出挽救某物品需要的时间 $t$，该物品开始燃烧的时间 $d$（从 $d$ 时间开始就不能再挽救该物品了），该物品的价值 $p$。

## 输入格式

第一行为物品总数 $n$（$1\leqslant n\leqslant100$）；

接下来 $n$ 行，每行有三个整数 $t_i$（$1\leqslant t_i\leqslant20$），$di$（$1\leqslant d_i\leqslant2000$），$pi$（$1\leqslant p_i\leqslant20$）。

## 输出格式

第一行为能带走的最大的价值总和；

第二行为能带走的物品的数量；

第三行为能带走的物品的编号（按带走顺序排序）。

Translated by 凌幽

## 样例 #1

### 输入

```
3
3 7 4
2 6 5
3 7 6

```

### 输出

```
11
2
2 3 

```

## 样例 #2

### 输入

```
2
5 6 1
3 3 5

```

### 输出

```
1
1
1 

```



---

---
title: "Maximum Subsequence"
layout: "post"
diff: 普及+/提高
pid: CF888E
tag: ['搜索', '贪心', '枚举']
---

# Maximum Subsequence

## 题目描述

You are given an array $ a $ consisting of $ n $ integers, and additionally an integer $ m $ . You have to choose some sequence of indices $ b_{1},b_{2},...,b_{k} $ ( $ 1<=b_{1}&lt;b_{2}&lt;...&lt;b_{k}<=n $ ) in such a way that the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/3a3d2e76b5bca3303d7d35912be232a5cadb1203.png) is maximized. Chosen sequence can be empty.

Print the maximum possible value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/3a3d2e76b5bca3303d7d35912be232a5cadb1203.png).

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=35 $ , $ 1<=m<=10^{9} $ ).

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

## 输出格式

Print the maximum possible value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/3a3d2e76b5bca3303d7d35912be232a5cadb1203.png).

## 说明/提示

In the first example you can choose a sequence $ b={1,2} $ , so the sum ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/08d6750b1b23699a8b513ddd01c316f10e6a789c.png) is equal to $ 7 $ (and that's $ 3 $ after taking it modulo $ 4 $ ).

In the second example you can choose a sequence $ b={3} $ .

## 样例 #1

### 输入

```
4 4
5 2 4 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3 20
199 41 299

```

### 输出

```
19

```



---

---
title: "Primal Sport"
layout: "post"
diff: 普及+/提高
pid: CF923A
tag: ['贪心', '枚举', '素数判断,质数,筛法']
---

# Primal Sport

## 题目描述

Alice and Bob begin their day with a quick game. They first choose a starting number $ X_{0}>=3 $ and try to reach one million by the process described below.

Alice goes first and then they take alternating turns. In the $ i $ -th turn, the player whose turn it is selects a prime number smaller than the current number, and announces the smallest multiple of this prime number that is not smaller than the current number.

Formally, he or she selects a prime $ p&lt;X_{i-1} $ and then finds the minimum $ X_{i}>=X_{i-1} $ such that $ p $ divides $ X_{i} $ . Note that if the selected prime $ p $ already divides $ X_{i-1} $ , then the number does not change.

Eve has witnessed the state of the game after two turns. Given $ X_{2} $ , help her determine what is the smallest possible starting number $ X_{0} $ . Note that the players don't necessarily play optimally. You should consider all possible game evolutions.

## 输入格式

The input contains a single integer $ X_{2} $ ( $ 4<=X_{2}<=10^{6} $ ). It is guaranteed that the integer $ X_{2} $ is composite, that is, is not prime.

## 输出格式

Output a single integer — the minimum possible $ X_{0} $ .

## 说明/提示

In the first test, the smallest possible starting number is $ X_{0}=6 $ . One possible course of the game is as follows:

- Alice picks prime 5 and announces $ X_{1}=10 $
- Bob picks prime 7 and announces $ X_{2}=14 $ .

In the second case, let $ X_{0}=15 $ .

- Alice picks prime 2 and announces $ X_{1}=16 $
- Bob picks prime 5 and announces $ X_{2}=20 $ .

## 样例 #1

### 输入

```
14

```

### 输出

```
6

```

## 样例 #2

### 输入

```
20

```

### 输出

```
15

```

## 样例 #3

### 输入

```
8192

```

### 输出

```
8191

```



---

---
title: "Well played!"
layout: "post"
diff: 普及+/提高
pid: CF976E
tag: ['贪心', '枚举']
---

# Well played!

## 题目描述

Max 最近沉迷于一款打怪游戏《赛某号》。现在，他正在参加赛某号的春季联赛。

他有 $n$ 只精灵。每只精灵都有对应的生命值 $hp_i$ 和攻击值 $dmg_i$。在比赛过程中，Max 可以借助巴拉拉小魔仙之力，说出这两种咒语：

1. “乌卡拉！血量！加倍！“意即将当前精灵的生命值加倍。（使得 $hp_i \gets 2\times hp_i$）

2. “乌卡拉！生命之力！”意即将当前精灵的生命值赋给当前精灵的攻击值。（使得 $dmg_i\gets hp_i$）

Max 当然不能无限使用这两种咒语。在一局游戏中，他可以使用第一种咒语 $a$ 次，第二次咒语 $b$ 次。由于Max 购买了超级 Nono，所以这两种咒语都可以被多次用在同一精灵身上，且咒语的使用顺序没有限制。Max 可以不用完所有的咒语。

Max 非常希望通过使用这些咒语使得自己的精灵战斗群的攻击值达到最大。现在，Max 想知道这个最大值。


输入第 $2$ 行到第 $n+1$ 行，每行两个整数 $hp$，$dmg$。第 $i$ 行表示第 $i-1$ 个精灵的生命值和攻击值。

## 输出格式

输出一行一个整数，代表 Max 的精灵战斗群能达到的最大攻击值。

**样例 1 解释**

Max 在第二只精灵上先使用第一种魔咒将其生命值加倍，此时的生命值为 $12$。此时，再用第二种魔咒将它的攻击值赋为当前的生命值，则第二只精灵的攻击值为 $12$。可以证明，不存在其它的方案使得这两只精灵的攻击值总和更大。

## 样例 #1

### 输入

```
2 1 1
10 15
6 1

```

### 输出

```
27

```

## 样例 #2

### 输入

```
3 0 3
10 8
7 11
5 2

```

### 输出

```
26

```



---

---
title: "Bookshelves"
layout: "post"
diff: 普及+/提高
pid: CF981D
tag: ['贪心', '概率论', '位运算']
---

# Bookshelves

## 题目描述

## 题意：

$Keks$ 先生是 $Byteland$ 大陆的典型的白领。

他办公室里有一个书架，上面有几本书，每本书都有一个值为正整数的价格。

$Keks$ 先生把书架的价值定义为书价的总和。         

出乎意料地是， $Keks$ 先生升职了，现在他要去一个新的办公室。

他知道，在新的办公室里，他将有不止一个书架，而恰恰是 $K$ 个书架。

他认为 $K$ 个书架的美丽程度在于所有书架的价值的“按位与”和。 

他还决定不花时间重新整理书籍，所以他会先把几本书放在第一个书架上，下几本书放在下一个书架上，以此类推。当然，他会在每一个架子上放置至少一本书。这样，他会把所有的书放在 $K$ 个书架上，尽量使书架的美观程度越大越好。计算这个最大可能的美丽程度。

## 输入格式

两行，

第一行两个数：$n,k$ 书本数，书架数。

第二行 $n$ 个整数，每本书的价值。

## 输出格式

一个数，最大可能的美丽程度

## 样例 #1

### 输入

```
10 4
9 14 28 1 7 13 15 29 2 31

```

### 输出

```
24

```

## 样例 #2

### 输入

```
7 3
3 14 15 92 65 35 89

```

### 输出

```
64

```



---

---
title: "Knights of a Polygonal Table"
layout: "post"
diff: 普及+/提高
pid: CF994B
tag: ['贪心', '平衡树', '向量']
---

# Knights of a Polygonal Table

## 题目描述

有  $n$  个骑士想决战。每个骑士都有能力值，且身上带有一些金币。如果骑士  $A$  的能力值大于骑士  $B$ ，那么骑士  $A$  就可以杀死骑士  $B$ ，并获得骑士  $B$  身上的所有金币。但就算是骑士也不会残忍过度，他们最多只会杀死  $k$  个骑士。对于每一位骑士，请你求出在决战后他身上金币的最大值。

## 输入格式

第  $1$  行，有  $2$  个整数，分别为骑士人数  $n$  和杀人数上限  $k$ 。

（数据范围： $1 \leqslant n \leqslant 10^{5}$ , $0 \leqslant k \leqslant min(n - 1,\ 10)$ ）

第  $2$  行，有  $n$  个整数，表示每个骑士的能力值  $p_i$ 。

第  $3$  行，有  $n$  个整数，表示每个骑士原有的金币  $c_i$ 。

（数据范围： $1 \leqslant p_i \leqslant 10^{9}$ , $0 \leqslant c_i \leqslant 10^{9}$ ）

## 输出格式

$1$  行内输出  $n$  个整数，决战后每个骑士身上金币的最大值，每两个数间以单个空格隔开。

## 说明/提示

- 第  $1$  组样例的解释：

第  $1$  个骑士是最蒻的，因此他谁也不能杀，只能保留自己原有的金币。

第  $2$  个骑士只能杀死第  $1$  个骑士，因此他最多拥有  $2 + 1 = 3$  个金币。

第  $3$  个骑士是最蔃的，但他只能选择杀  $k = 2$  个骑士。显然他会杀死第  $2$  个骑士和
第  $4$  个骑士，因为他们身上的金币更多。因此他最多拥有  $11 + 2 + 33 = 46$  个金币。

第  $4$  个骑士应该杀死第  $1$  个和第  $2$  个骑士，因此他最多拥有  $33 + 1 + 2 = 36$  个金币。 

- 第  $2$  组样例的解释：

除了最蒻的第  $1$  个骑士谁也不能杀，其他骑士都能杀死前一个骑士并获得他的金币。

- 第  $3$  组样例的解释：

由于只有一个骑士在决战中，他无法杀死任何人。

感谢@Sooke 提供翻译

## 样例 #1

### 输入

```
4 2
4 5 9 7
1 2 11 33

```

### 输出

```
1 3 46 36 
```

## 样例 #2

### 输入

```
5 1
1 2 3 4 5
1 2 3 4 5

```

### 输出

```
1 3 5 7 9 
```

## 样例 #3

### 输入

```
1 0
2
3

```

### 输出

```
3 
```



---

