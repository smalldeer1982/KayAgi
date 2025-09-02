---
title: "STC02 - Antisymmetry"
layout: "post"
diff: 提高+/省选-
pid: SP15569
tag: ['二分', '枚举', '哈希 hashing', 'Manacher 算法']
---

# STC02 - Antisymmetry

## 题目描述

对于一个 01 字符串，如果将这个字符串 0 和 1 取反后，再将整个串反过来和原串一样，就称作「反对称」字符串。比如 00001111 和 010101 就是反对称的，而 1001 就不是。 现在给出一个长度为 n 的 01 字符串，求它有多少个子串是反对称的，注意这里相同的子串出现在不同的位置会被重复计算。

## 输出格式

Translated by @xzjds



---

---
title: "TLE - Time Limit Exceeded"
layout: "post"
diff: 提高+/省选-
pid: SP2829
tag: ['枚举', '状态合并', '前缀和']
---

# TLE - Time Limit Exceeded

## 题目描述

Given integers N (1 ≤ N ≤ 50) and M (1 ≤ M ≤ 15), compute the number of sequences a $ _{1} $ , ..., a $ _{N} $ such that:

- 0 ≤ a $ _{i} $ < 2 $ ^{M} $
- a $ _{i} $ is not divisible by c $ _{i} $ (0 < c $ _{i} $ ≤ 2 $ ^{M} $ )
- a $ _{i} $ & a $ _{i+1} $ = 0 (that is, a $ _{i} $ and a $ _{i+1} $ have no common bits in their binary representation)

## 输入格式

The first line contains the number of test cases, T (1 ≤ T ≤ 10). For each test case, the first line contains the integers N and M, and the second line contains the integers c $ _{1} $ , ..., c $ _{N} $ .

## 输出格式

For each test case, output a single integer: the number of sequences described above, modulo 1,000,000,000.

## 样例 #1

### 输入

```
1

2 2

3 2
```

### 输出

```
1
```



---

---
title: "RACETIME - Race Against Time"
layout: "post"
diff: 提高+/省选-
pid: SP3261
tag: ['枚举', '排序', '分块']
---

# RACETIME - Race Against Time

## 题目描述

现在有$n(1<=n<=1e5)$只奶牛站成一排，每只奶牛手中都拿着一个数字$A_i(0<=A_i<=1e9)$

现在$FJ$要执行$Q(1<=Q<=50000)$个操作，每个操作可能是下面两种操作之一：

$1.$ $M$ $i$ $X$ ：将第$i$只奶牛手上的数字$A_i$替换为$X$

$2.$ $C$ $l$ $r$ $K$：询问区间$[l,r]$内有多少只奶牛手上拿的数字$A_i\le K$

作为$FJ$的好朋友，请你对每一个$2$操作输出答案

由于$FJ$非常蕉♂躁，所以他只允许你在$1s$内回答这些问题

## 输入格式

第一行输入两个正整数$n,Q$，含义如上

接下来$n$行，每一行输入一个正整数$A_i$，表示初始时第$i$只奶牛手上拿的数字$A_i$

接下来有$Q$行输入，代表$FJ$接下来要进行的$Q$个操作，格式如上文

## 输出格式

对于每一个$2$操作，请你输出满足条件的奶牛个数。每个答案占一行

## 样例 #1

### 输入

```
4 6

3

4

1

7

C 2 4 4

M 4 1

C 2 4 4

C 1 4 5

M 2 10

C 1 3 9
```

### 输出

```
2

3

4

2
```



---

---
title: "TRIP - Trip"
layout: "post"
diff: 提高+/省选-
pid: SP33
tag: ['字符串', '递归', '枚举']
---

# TRIP - Trip

## 题目描述

Alice and Bob want to go on holiday. Each of them has drawn up a list of cities to be visited in turn. A list may contain a city more than once. As they want to travel together, they have to agree upon a common route. No one wants to change the order of the cities on his list or add other cities. Therefore they have no choice but to remove some cities from the list. Of course the common route is to involve as much sight-seeing in cities as possible. There are exactly 26 cities in the region. Therefore they are encoded on the lists as lower case letters from 'a' to 'z'.

## 输入格式

The first line of input contains a number T <= 10 that indicates the number of test cases to follow. Each test case consists of two lines; the first line is the list of Alice, the second line is the list of Bob. Each list consists of 1 to 80 lower case letters.

## 输出格式

The output for each test case should contain all different trips exactly once that meet the conditions described above. There is at least one such trip, but never more than 1000 different ones. You should order the trips in lexicographic order. Print one blank line between the output of different test cases.

## 样例 #1

### 输入

```
1
abcabcaa
acbacba
```

### 输出

```
ababa
abaca
abcba
acaba
acaca
acbaa
acbca
```



---

---
title: "ROADS - Roads"
layout: "post"
diff: 提高+/省选-
pid: SP338
tag: ['枚举', '剪枝']
---

# ROADS - Roads

## 题目描述

题面描述  
有标号为1……n的城市与单行道相连。对于每条道路有两个与之相关的参数：道路的长度以及需要支付的费用（用硬币的数量表示）  
鲍勃和爱丽丝曾经生活在城市1。在注意到爱丽丝在他们喜欢玩的卡牌游戏中作弊后，鲍勃决定与爱丽丝分手并搬走——去城市n。他希望尽快到达那里——越快越好，然而他现在有些现金短缺。
我们希望帮助鲍勃找到从城市1到城市n的一条最短路径——但他必须用他现有的钱支付得起。

## 输入格式

输入的第一行含有一个整数t代表测试样例的组数。下面是t组测试样例。  
对于每组测试数据，第一行含有一个整数K（0<=K<=10000)，代表鲍勃所能支付得起的最大费用。  
第二行含有一个整数N（2<=N<=100)，代表城市总数。  
第三行含有一个整数R（1<=R<=10000)，代表道路的总数。  
接下来R行每行用四个整数S,D,L,T，以单个空格分隔：  
S表示出发点城市标号（1<=S<=N)；  
D表示目的地城市标号（1<=D<=N)；  
L是该道路的长度（1<=L<=100)；
T表示经过该道路的费用(0<=T<=100)。  
注意不同的道路可能拥有相同的起点和终点。

## 输出格式

对于每组测试样例，输出单独的一行表示当花费小于等于K时最短路径的长度。如果不存在这样的路径，输出-1。

## 样例 #1

### 输入

```
2

5

6

7

1 2 2 3

2 4 3 3

3 4 2 4

1 3 4 1

4 6 2 1

3 5 2 0

5 4 3 2

0

4

4

1 4 5 2

1 2 1 0

2 3 1 1

3 4 1 0
```

### 输出

```
11

-1
```



---

---
title: "FENCE3 - Electric Fences"
layout: "post"
diff: 提高+/省选-
pid: SP4587
tag: ['模拟', '枚举', '模拟退火']
---

# FENCE3 - Electric Fences

## 题目描述

　　农夫约翰已经决定建造电网。他已经把他的农田围成一些奇怪的形状，现在必须找出安放电源的最佳位置。
  
　　对于段电网都必须从电源拉出一条电线。电线可以穿过其他电网或者跨过其他电线。电线能够以任意角度铺设，从电源连接到一段电网的任意一点上（也就是，这段电网的端点上或者在其之间的任意一点上）。这里所说的“一段电网”指的是呈一条线段状的电网，并不是连在一起的几段电网。若几段电网连在一起，那么也要分别给这些电网提供电力。
  
　　已知所有的 F（1 <= F <= 150）段电网的位置（电网总是和坐标轴平行，并且端点的坐标总是整数，0 <= X,Y <= 100）。你的程序要计算连接电源和每段电网所需的电线的最小总长度，还有电源的最佳坐标。
  
　　电源的最佳坐标可能在农夫约翰的农田中的任何一个位置，并不一是整数。

## 输入格式

　　第一行包括 F ——电网的数量。
　　下面的 F 行每行包括两个 X，Y 对，表示这段电网的两个端点。

## 输出格式

只有一行，输出三个浮点数，相邻两个之间留一个空格。

假定你的电脑的输出库会正确地对小数进行四舍五入。
这三个数是： 电源最佳坐标的 X 值，
电源最佳坐标的 Y 值，和
需要的电线的总长度（要最小）。

## 样例 #1

### 输入

```
3

0 0 0 1

2 0 2 1

0 3 2 3
```

### 输出

```
1.0 1.6 3.7
```



---

---
title: "SAM - Toy Cars"
layout: "post"
diff: 提高+/省选-
pid: SP688
tag: ['贪心', '枚举']
---

# SAM - Toy Cars

## 题目描述

Jasio 是一个只有三岁的小男孩，他喜欢玩玩具车。他有 $n$ 辆玩具车被保存在书架上。

架子上的玩具车 Jasio 拿不到，但地板上的他可以拿到。Jasio 的母亲会帮 Jasio 拿架子上的玩具车到地板上。

地板最多只能放 $k$ 辆玩具车。

当地板已经放了 $k$ 辆玩具车时，Jasio 的母亲都会从地板上先拿走一个玩具车放回书架，再拿来 Jasio 想要的玩具车。

现在 Jasio 一共想依次玩 $p$ 个玩具车，问 Jasio 的母亲最少需要拿几次玩具车。（只算拿下来的，不算拿上去的）

## 输入格式

第一行一个整数 $t$，表示有 $t$ 组数据。

接下来一行有三个整数 $n,k$ 和 $p$。

接下来 $p$ 行，每一行有且仅有一个整数 $a_i$，表示 Jasio 想玩的玩具玩家车编号。

## 输出格式

输出一行一个整数，表示最少 Jasio 的母亲最少需要拿玩家车的次数。

## 说明/提示

对于 $100\%$ 的数据：$1\le t\le 16$，$1\le k\le n\le 10^5$，$1\le p\le 5\times 10^5$，$1\le a_i\le n$。

感谢 @Utilokasteinn 提供的翻译。

## 样例 #1

### 输入

```
1
3 2 7
1
2
3
1
3
1
2
```

### 输出

```
4
```



---

---
title: "CF25E - Test"
layout: "post"
diff: 提高+/省选-
pid: SP7155
tag: ['字符串', '枚举', 'KMP 算法']
---

# CF25E - Test

## 题目描述

### 题目翻译

Bob 出了一道字符串题，题目的输入是一个字符串。

毒瘤的 Bob 写了 $3$ 个程序，但他发现了一个悲剧：

1. 当输入的字符串有子串 $s_1$ 时，程序 $1$ 会 WA；

1. 当输入的字符串有子串 $s_2$ 时，程序 $2$ 会死循环；

1. 当输入的字符串有子串 $s_3$ 时，程序 $3$ 会 MLE。

当然，可以假定其他情况下程序不会出锅。

Bob 非常毒瘤，他想找一个最短的输入字符串 $ss$，使得 $3$ 个程序都过不了。请输出最小的长度。

## 输入格式

**多组数据**，每组数据 $3$ 行，每行一个字符串，分别代表 $s_1,s_2,s_3$，只含小写字母。

## 输出格式

对于每组数据，输出一个整数代表最小长度，然后换行。

#### 数据规模与约定

对于 $100\%$ 的数据， $1\leq |s_1|,|s_2|,|s_3|\leq 10^5$。

## 样例 #1

### 输入

```
ab
bc
cd
abacaba
abaaba
x

```

### 输出

```
4
11

```



---

