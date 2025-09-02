---
title: "Mouse Hunt"
layout: "post"
diff: 提高+/省选-
pid: CF1027D
tag: ['模拟', '强连通分量', '概率论']
---

# Mouse Hunt

## 题目描述

伯兰州立大学的医学部刚刚结束了招生活动。和以往一样，约80%的申请人都是女生并且她们中的大多数人将在未来4年（真希望如此）住在大学宿舍里。

宿舍楼里有$n$个房间和**一只老鼠**！女孩们决定在一些房间里设置捕鼠器来除掉这只可怕的怪物。在$i$号房间设置陷阱要花费$c_i$伯兰币。房间编号从$1$到$n$。

要知道老鼠不是一直原地不动的，它不停地跑来跑去。如果$t$秒时它在$i$号房间，那么它将在$t+1$秒时跑到$a_i$号房间，但这期间不会跑到别的任何房间里($i=a_i$表示老鼠没有离开原来的房间)。时间从$0$秒开始，一旦老鼠窜到了有捕鼠器的房间里，这只老鼠就会被抓住。

如果女孩们知道老鼠一开始在哪里不就很容易吗？不幸的是，情况不是这样，老鼠在第$0$秒时可能会在从$1$到$n$的任何一个房间内。

那么女孩们最少要花多少钱设置捕鼠器，才能保证老鼠无论从哪个房间开始流窜最终都会被抓到？

## 输入格式

第1行一个整数n($1\le n \le 2*10^5$)，表示宿舍楼里的房间数。

第2行有$n$个整数，$c_1, c_2, \dots, c_n(1\le c_i \le 10^4)$，$c_i$表示在$i$号房间设置捕鼠器的花费。

第3行有$n$个整数，$a_1, a_2, \dots, a_n(1\le a_i \le n)$，$a_i$是老鼠在$i$号房间时，下一秒会窜到的房间号。

## 输出格式

输出一个整数，表示设置捕鼠器的最小花费（保证无论老鼠一开始在什么位置最终都能被抓住！）。

## 样例 #1

### 输入

```
5
1 2 3 2 10
1 3 4 3 3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4
1 10 2 10
2 4 2 2

```

### 输出

```
10

```

## 样例 #3

### 输入

```
7
1 1 1 1 1 1 1
2 2 2 3 6 7 6

```

### 输出

```
2

```



---

---
title: "Binary Numbers AND Sum"
layout: "post"
diff: 提高+/省选-
pid: CF1066E
tag: ['模拟', '进制', '前缀和']
---

# Binary Numbers AND Sum

## 题目描述

## 题目大意



现在，给你两个位数为 $n$ 和 $m$ 的两个二进制数$a$,$b$，现在，我们要进行如下操作：



* 计算$a$&$b$

* 答案累加上一个操作的值

* $b$右移一位，最后一位直接舍弃



现在,请你算出最终的答案，并输出，答案对998244353取模

## 输入格式

第一行，两个整数$n$,$m$,$(1≤n,m≤2 \times 10^5)$



第一行，一个长度为$n$的二进制数$a$



第一行，一个长度为$m$的二进制数$b$

## 输出格式

一行，一个数，表示答案

## 样例 #1

### 输入

```
4 4
1010
1101

```

### 输出

```
12

```

## 样例 #2

### 输入

```
4 5
1001
10101

```

### 输出

```
11

```



---

---
title: "Cycle"
layout: "post"
diff: 提高+/省选-
pid: CF117C
tag: ['模拟', '图论']
---

# Cycle

## 题目描述

一个 $\texttt{tournament}$ 是一个没有自环的有向图，同时，每两个点之间有一条边连接。这就是说，对于两个点 $u,v (u\neq v)$，有一条从 $u$ 到 $v$ 的边或一条从 $v$ 到 $u$ 的边。

给你一个 $\texttt{tournament}$，请找出一个长度为 $3$ 的环。

## 输入格式

第一行一个正整数 $n$。

接下来 $n$ 行：一个 $n \times n$ 的邻接矩阵 $a$，由 `0` 和 `1` 组成。

若 $a_{i,j}=1$，表示有一条路从 $i$ 通往 $j$。

数据保证 $a_{i,i}=0$ 并且 $a_{i,j} \neq a_{j,i}$。

## 输出格式

仅一行：任意一种解决方案；若没有，输出 `-1`。

## 样例 #1

### 输入

```
5
00100
10000
01001
11101
11000

```

### 输出

```
1 3 2 
```

## 样例 #2

### 输入

```
5
01111
00000
01000
01100
01110

```

### 输出

```
-1

```



---

---
title: "Letter A"
layout: "post"
diff: 提高+/省选-
pid: CF13B
tag: ['模拟', '计算几何']
---

# Letter A

## 题目描述

Little Petya learns how to write. The teacher gave pupils the task to write the letter $ A $ on the sheet of paper. It is required to check whether Petya really had written the letter $ A $ .

You are given three segments on the plane. They form the letter $ A $ if the following conditions hold:

- Two segments have common endpoint (lets call these segments first and second), while the third segment connects two points on the different segments.
- The angle between the first and the second segments is greater than $ 0 $ and do not exceed $ 90 $ degrees.
- The third segment divides each of the first two segments in proportion not less than $ 1/4 $ (i.e. the ratio of the length of the shortest part to the length of the longest part is not less than $ 1/4 $ ).

## 输入格式

The first line contains one integer $ t $ ( $ 1<=t<=10000 $ ) — the number of test cases to solve. Each case consists of three lines. Each of these three lines contains four space-separated integers — coordinates of the endpoints of one of the segments. All coordinates do not exceed $ 10^{8} $ by absolute value. All segments have positive length.

## 输出格式

Output one line for each test case. Print «YES» (without quotes), if the segments form the letter $ A $ and «NO» otherwise.

## 样例 #1

### 输入

```
3
4 4 6 0
4 1 5 2
4 0 4 4
0 0 0 6
0 6 2 -4
1 1 0 1
0 0 0 5
0 5 2 -1
1 2 0 1

```

### 输出

```
YES
NO
YES

```



---

---
title: "Doremy's Number Line"
layout: "post"
diff: 提高+/省选-
pid: CF1764E
tag: ['模拟', '贪心']
---

# Doremy's Number Line

## 题目描述

Doremy has two arrays $ a $ and $ b $ of $ n $ integers each, and an integer $ k $ .

Initially, she has a number line where no integers are colored. She chooses a permutation $ p $ of $ [1,2,\ldots,n] $ then performs $ n $ moves. On the $ i $ -th move she does the following:

- Pick an uncolored integer $ x $ on the number line such that either: 
  - $ x \leq a_{p_i} $ ; or
  - there exists a colored integer $ y $ such that $ y \leq a_{p_i} $ and $ x \leq y+b_{p_i} $ .
- Color integer $ x $ with color $ p_i $ .

Determine if the integer $ k $ can be colored with color $ 1 $ .

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line contains two integers $ n $ and $ k $ ( $ 1 \le n \le 10^5 $ , $ 1 \le k \le 10^9 $ ).

Each of the following $ n $ lines contains two integers $ a_i $ and $ b_i $ ( $ 1 \le a_i,b_i \le 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output "YES" (without quotes) if the point $ k $ can be colored with color $ 1 $ . Otherwise, output "NO" (without quotes).

You can output "YES" and "NO" in any case (for example, strings "yEs", "yes" and "Yes" will be recognized as a positive response).

## 说明/提示

For the first test case, it is impossible to color point $ 16 $ with color $ 1 $ .

For the second test case, $ p=[2,1,3,4] $ is one possible choice, the detail is shown below.

- On the first move, pick $ x=8 $ and color it with color $ 2 $ since $ x=8 $ is uncolored and $ x \le a_2 $ .
- On the second move, pick $ x=16 $ and color it with color $ 1 $ since there exists a colored point $ y=8 $ such that $ y\le a_1 $ and $ x \le y + b_1 $ .
- On the third move, pick $ x=0 $ and color it with color $ 3 $ since $ x=0 $ is uncolored and $ x \le a_3 $ .
- On the forth move, pick $ x=-2 $ and color it with color $ 4 $ since $ x=-2 $ is uncolored and $ x \le a_4 $ .
- In the end, point $ -2,0,8,16 $ are colored with color $ 4,3,2,1 $ , respectively.

For the third test case, $ p=[2,1,4,3] $ is one possible choice.

For the fourth test case, $ p=[2,3,4,1] $ is one possible choice.

## 样例 #1

### 输入

```
6
4 16
5 3
8 12
10 7
15 1
4 16
8 12
10 7
15 1
5 3
4 16
10 7
15 1
5 3
8 12
4 16
15 1
5 3
8 12
10 7
1 1000000000
500000000 500000000
2 1000000000
1 999999999
1 1
```

### 输出

```
NO
YES
YES
YES
NO
YES
```



---

---
title: "Monster"
layout: "post"
diff: 提高+/省选-
pid: CF2035E
tag: ['动态规划 DP', '模拟退火', '根号分治']
---

# Monster

## 题目描述

Man, this Genshin boss is so hard. Good thing they have a top-up of $ 6 $ coins for only $  \$4.99 $ . I should be careful and spend no more than I need to, lest my mom catches me...



You are fighting a monster with $ z $ health using a weapon with $ d $ damage. Initially, $ d=0 $ . You can perform the following operations.

- Increase $ d $ — the damage of your weapon by $ 1 $ , costing $ x $ coins.
- Attack the monster, dealing $ d $ damage and costing $ y $ coins.

You cannot perform the first operation for more than $ k $ times in a row.

Find the minimum number of coins needed to defeat the monster by dealing at least $ z $ damage.

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 100 $ ) — the number of test cases.

The only line of each test case contains 4 integers $ x $ , $ y $ , $ z $ , and $ k $ ( $ 1\leq x, y, z, k\leq 10^8 $ ) — the first operation's cost, the second operation's cost, the monster's health, and the limitation on the first operation.

## 输出格式

For each test case, output the minimum number of coins needed to defeat the monster.

## 说明/提示

In the first test case, $ x = 2 $ , $ y = 3 $ , $ z = 5 $ , and $ k = 5 $ . Here's a strategy that achieves the lowest possible cost of $ 12 $ coins:

- Increase damage by $ 1 $ , costing $ 2 $ coins.
- Increase damage by $ 1 $ , costing $ 2 $ coins.
- Increase damage by $ 1 $ , costing $ 2 $ coins.
- Attack the monster, dealing $ 3 $ damage, costing $ 3 $ coins.
- Attack the monster, dealing $ 3 $ damage, costing $ 3 $ coins.

You deal a total of $ 3 + 3 = 6 $ damage, defeating the monster who has $ 5 $ health. The total number of coins you use is $ 2 + 2 + 2 + 3 + 3 = 12 $ coins.

In the second test case, $ x = 10 $ , $ y = 20 $ , $ z = 40 $ , and $ k = 5 $ . Here's a strategy that achieves the lowest possible cost of $ 190 $ coins:

- Increase damage by $ 5 $ , costing $ 5\cdot x $ = $ 50 $ coins.
- Attack the monster once, dealing $ 5 $ damage, costing $ 20 $ coins.
- Increase damage by $ 2 $ , costing $ 2\cdot x $ = $ 20 $ coins.
- Attack the monster $ 5 $ times, dealing $ 5\cdot 7 = 35 $ damage, costing $ 5\cdot y $ = $ 100 $ coins.

You deal a total of $ 5 + 35 = 40 $ damage, defeating the monster who has exactly $ 40 $ health. The total number of coins you use is $ 50 + 20 + 20 + 100 = 190 $ coins.

## 样例 #1

### 输入

```
4
2 3 5 5
10 20 40 5
1 60 100 10
60 1 100 10
```

### 输出

```
12
190
280
160
```



---

---
title: "Commentator problem"
layout: "post"
diff: 提高+/省选-
pid: CF2C
tag: ['模拟', '搜索', '模拟退火']
---

# Commentator problem

## 题目描述

The Olympic Games in Bercouver are in full swing now. Here everyone has their own objectives: sportsmen compete for medals, and sport commentators compete for more convenient positions to give a running commentary. Today the main sport events take place at three round stadiums, and the commentator's objective is to choose the best point of observation, that is to say the point from where all the three stadiums can be observed. As all the sport competitions are of the same importance, the stadiums should be observed at the same angle. If the number of points meeting the conditions is more than one, the point with the maximum angle of observation is prefered.

Would you, please, help the famous Berland commentator G. Berniev to find the best point of observation. It should be noted, that the stadiums do not hide each other, the commentator can easily see one stadium through the other.

## 输入格式

The input data consists of three lines, each of them describes the position of one stadium. The lines have the format $ x,y,r $ , where ( $ x,y $ ) are the coordinates of the stadium's center ( $ -10^{3}<=x,y<=10^{3} $ ), and $ r $ ( $ 1<=r<=10^{3} $ ) is its radius. All the numbers in the input data are integer, stadiums do not have common points, and their centers are not on the same line.

## 输出格式

Print the coordinates of the required point with five digits after the decimal point. If there is no answer meeting the conditions, the program shouldn't print anything. The output data should be left blank.

## 样例 #1

### 输入

```
0 0 10
60 0 10
30 30 10

```

### 输出

```
30.00000 0.00000

```



---

---
title: "Propagating tree"
layout: "post"
diff: 提高+/省选-
pid: CF383C
tag: ['模拟', '线段树', '深度优先搜索 DFS']
---

# Propagating tree

## 题目描述

很久以前，有一棵神橡树(oak)，上面有$n$个节点，从$1$~$n$编号，由$n-1$条边相连。它的根是$1$号节点。  

这棵橡树每个点都有一个权值，你需要完成这两种操作：
$1$ $u$ $val$ 表示给$u$节点的权值增加$val$  
$2$ $u$ 表示查询$u$节点的权值   

但是这不是普通的橡树，它是神橡树。  
所以它还有个神奇的性质：当某个节点的权值增加$val$时，它的子节点权值都增加$-val$，它子节点的子节点权值增加$-(-val)$...... 如此一直进行到树的底部。

## 输入格式

第一行两个正整数$n,m$，表示节点数量和操作数量。  
第二行$n$个正整数$a_i$，依次表示每个节点的权值。     
接下来$n-1$行，每行两个正整数$u,v$，表示$u,v$之间有一条边相连。  
最后$m$行，每行若干个正整数，表示一次操作。

## 输出格式

对于每次询问，输出一行一个整数表示答案。

## 说明/提示

$1\le n,m \le 2\times 10^5$  
$1\le a_i,val \le 1000$  
$1\le u,v \le n$

## 样例 #1

### 输入

```
5 5
1 2 1 1 2
1 2
1 3
2 4
2 5
1 2 3
1 1 2
2 1
2 2
2 4

```

### 输出

```
3
3
0

```



---

---
title: "Bulls and Cows"
layout: "post"
diff: 提高+/省选-
pid: CF63C
tag: ['模拟', '枚举']
---

# Bulls and Cows

## 题目描述

The "Bulls and Cows" game needs two people to play. The thinker thinks of a number and the guesser tries to guess it.

The thinker thinks of a four-digit number in the decimal system. All the digits in the number are different and the number may have a leading zero. It can't have more than one leading zero, because all it's digits should be different. The guesser tries to guess the number. He makes a series of guesses, trying experimental numbers and receives answers from the first person in the format " $ x $ bulls $ y $ cows". $ x $ represents the number of digits in the experimental number that occupy the same positions as in the sought number. $ y $ represents the number of digits of the experimental number that present in the sought number, but occupy different positions. Naturally, the experimental numbers, as well as the sought number, are represented by four-digit numbers where all digits are different and a leading zero can be present.

For example, let's suppose that the thinker thought of the number 0123. Then the guessers' experimental number 1263 will receive a reply "1 bull 2 cows" (3 occupies the same positions in both numbers and 1 and 2 are present in both numbers but they occupy different positions). Also, the answer to number 8103 will be "2 bulls 1 cow" (analogically, 1 and 3 occupy the same positions and 0 occupies a different one).

When the guesser is answered "4 bulls 0 cows", the game is over.

Now the guesser has already made several guesses and wants to know whether his next guess can possibly be the last one.

## 输入格式

The first input line contains an integer $ n $ ( $ 1<=n<=10 $ ) which represents the number of already made guesses. Then follow $ n $ lines in the form of " $ a_{i} $ $ b_{i} $ $ c_{i} $ ", where $ a_{i} $ is the $ i $ -th experimental number, $ b_{i} $ is the number of bulls, $ c_{i} $ is the number of cows ( $ 1<=i<=n $ , $ 0<=b_{i},c_{i},b_{i}+c_{i}<=4 $ ). The experimental numbers are correct, i.e., each of them contains exactly four digits, in each of them all the four digits are different, and there can be a leading zero. All the experimental numbers are different. As the guesser hasn't guessed the number yet, the answer "4 bulls 0 cows" is not present.

## 输出格式

If the input data is enough to determine the sought number, print the number with four digits on a single line. If it has less than four digits, add leading zero. If the data is not enough, print "Need more data" without the quotes. If the thinker happens to have made a mistake in his replies, print "Incorrect data" without the quotes.

## 样例 #1

### 输入

```
2
1263 1 2
8103 2 1

```

### 输出

```
Need more data
```

## 样例 #2

### 输入

```
2
1234 2 2
1256 0 2

```

### 输出

```
2134
```

## 样例 #3

### 输入

```
2
0123 1 1
4567 1 2

```

### 输出

```
Incorrect data
```



---

---
title: "Xor-sequences"
layout: "post"
diff: 提高+/省选-
pid: CF691E
tag: ['模拟', '进制', '位运算']
---

# Xor-sequences

## 题目描述

You are given $ n $ integers $ a_{1},a_{2},...,a_{n} $ .

A sequence of integers $ x_{1},x_{2},...,x_{k} $ is called a "xor-sequence" if for every $ 1<=i<=k-1 $ the number of ones in the binary representation of the number $ x_{i} $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF691E/081f686069870b762728923799c454e27369af9a.png) $ x_{i+1} $ 's is a multiple of $ 3 $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF691E/187abd20483c4318d7cd71518f323b9990bcdd61.png) for all $ 1<=i<=k $ . The symbol ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF691E/081f686069870b762728923799c454e27369af9a.png) is used for the binary exclusive or operation.

How many "xor-sequences" of length $ k $ exist? Output the answer modulo $ 10^{9}+7 $ .

Note if $ a=[1,1] $ and $ k=1 $ then the answer is $ 2 $ , because you should consider the ones from $ a $ as different.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=100 $ , $ 1<=k<=10^{18} $ ) — the number of given integers and the length of the "xor-sequences".

The second line contains $ n $ integers $ a_{i} $ ( $ 0<=a_{i}<=10^{18} $ ).

## 输出格式

Print the only integer $ c $ — the number of "xor-sequences" of length $ k $ modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
5 2
15 1 2 4 8

```

### 输出

```
13

```

## 样例 #2

### 输入

```
5 1
15 1 2 4 8

```

### 输出

```
5

```



---

---
title: "Contest Balloons"
layout: "post"
diff: 提高+/省选-
pid: CF725D
tag: ['模拟', '贪心', '优先队列', '队列']
---

# Contest Balloons

## 题目描述

ACM比赛，大家都知道。AC一题会有一个气球。
现在有$n(2<=n<=300000)$ 支队伍，每支队伍的重量是$w_i$ ，拥有$t_i$ 个气球$(w_i,t_i<=10^{18})$ ，当一支队伍的气球个数比它的重量都要大时，这个队伍就会飘起来，从而被取消比赛资格。
现在你带领的是1号队，你希望你队伍的名次尽可能靠前，你是个有原则的人，不会偷气球，但你可以把气球送给别的队伍，让他们飞起来。
求最终你的队伍所获得的最好名次

## 输入格式

第一行：一个正整数$n(2<=n<=300000)$ ，队伍的总数
第二行到第$n+1$ 行：每行两个整数$t_i,w_i(0<=t_i<=w_i<=10^{18})$ ，分别表示第$i$ 个队伍气球的个数以及它的重量。你的队伍是1号队。

## 输出格式

仅有一行，输出你带领的队伍能够达到的最好名次

感谢@2016wudi 提供的翻译

## 样例 #1

### 输入

```
8
20 1000
32 37
40 1000
45 50
16 16
16 16
14 1000
2 1000

```

### 输出

```
3

```

## 样例 #2

### 输入

```
7
4 4
4 4
4 4
4 4
4 4
4 4
5 5

```

### 输出

```
2

```

## 样例 #3

### 输入

```
7
14000000003 1000000000000000000
81000000000 88000000000
5000000000 7000000000
15000000000 39000000000
46000000000 51000000000
0 1000000000
0 0

```

### 输出

```
2

```



---

---
title: "Flow Control"
layout: "post"
diff: 提高+/省选-
pid: CF990F
tag: ['模拟', '构造']
---

# Flow Control

## 题目描述

You have to handle a very complex water distribution system. The system consists of $ n $ junctions and $ m $ pipes, $ i $ -th pipe connects junctions $ x_i $ and $ y_i $ .

The only thing you can do is adjusting the pipes. You have to choose $ m $ integer numbers $ f_1 $ , $ f_2 $ , ..., $ f_m $ and use them as pipe settings. $ i $ -th pipe will distribute $ f_i $ units of water per second from junction $ x_i $ to junction $ y_i $ (if $ f_i $ is negative, then the pipe will distribute $ |f_i| $ units of water per second from junction $ y_i $ to junction $ x_i $ ). It is allowed to set $ f_i $ to any integer from $ -2 \cdot 10^9 $ to $ 2 \cdot 10^9 $ .

In order for the system to work properly, there are some constraints: for every $ i \in [1, n] $ , $ i $ -th junction has a number $ s_i $ associated with it meaning that the difference between incoming and outcoming flow for $ i $ -th junction must be exactly $ s_i $ (if $ s_i $ is not negative, then $ i $ -th junction must receive $ s_i $ units of water per second; if it is negative, then $ i $ -th junction must transfer $ |s_i| $ units of water per second to other junctions).

Can you choose the integers $ f_1 $ , $ f_2 $ , ..., $ f_m $ in such a way that all requirements on incoming and outcoming flows are satisfied?

## 输入格式

The first line contains an integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of junctions.

The second line contains $ n $ integers $ s_1, s_2, \dots, s_n $ ( $ -10^4 \le s_i \le 10^4 $ ) — constraints for the junctions.

The third line contains an integer $ m $ ( $ 0 \le m \le 2 \cdot 10^5 $ ) — the number of pipes.

 $ i $ -th of the next $ m $ lines contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i, y_i \le n $ , $ x_i \ne y_i $ ) — the description of $ i $ -th pipe. It is guaranteed that each unordered pair $ (x, y) $ will appear no more than once in the input (it means that there won't be any pairs $ (x, y) $ or $ (y, x) $ after the first occurrence of $ (x, y) $ ). It is guaranteed that for each pair of junctions there exists a path along the pipes connecting them.

## 输出格式

If you can choose such integer numbers $ f_1, f_2, \dots, f_m $ in such a way that all requirements on incoming and outcoming flows are satisfied, then output "Possible" in the first line. Then output $ m $ lines, $ i $ -th line should contain $ f_i $ — the chosen setting numbers for the pipes. Pipes are numbered in order they appear in the input.

Otherwise output "Impossible" in the only line.

## 样例 #1

### 输入

```
4
3 -10 6 1
5
1 2
3 2
2 4
3 4
3 1

```

### 输出

```
Possible
4
-6
8
-7
7

```

## 样例 #2

### 输入

```
4
3 -10 6 4
5
1 2
3 2
2 4
3 4
3 1

```

### 输出

```
Impossible

```



---

