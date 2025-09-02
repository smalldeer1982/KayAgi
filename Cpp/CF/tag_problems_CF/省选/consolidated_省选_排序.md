---
title: "Relatively Prime Powers"
layout: "post"
diff: 省选/NOI-
pid: CF1036F
tag: ['排序', '构造']
---

# Relatively Prime Powers

## 题目描述

Consider some positive integer $ x $ . Its prime factorization will be of form $ x = 2^{k_1} \cdot 3^{k_2} \cdot 5^{k_3} \cdot \dots $

Let's call $ x $ elegant if the greatest common divisor of the sequence $ k_1, k_2, \dots $ is equal to $ 1 $ . For example, numbers $ 5 = 5^1 $ , $ 12 = 2^2 \cdot 3 $ , $ 72 = 2^3 \cdot 3^2 $ are elegant and numbers $ 8 = 2^3 $ ( $ GCD = 3 $ ), $ 2500 = 2^2 \cdot 5^4 $ ( $ GCD = 2 $ ) are not.

Count the number of elegant integers from $ 2 $ to $ n $ .

Each testcase contains several values of $ n $ , for each of them you are required to solve the problem separately.

## 输入格式

The first line contains a single integer $ T $ ( $ 1 \le T \le 10^5 $ ) — the number of values of $ n $ in the testcase.

Each of the next $ T $ lines contains a single integer $ n_i $ ( $ 2 \le n_i \le 10^{18} $ ).

## 输出格式

Print $ T $ lines — the $ i $ -th line should contain the number of elegant numbers from $ 2 $ to $ n_i $ .

## 说明/提示

Here is the list of non-elegant numbers up to $ 10 $ :

- $ 4 = 2^2, GCD = 2 $ ;
- $ 8 = 2^3, GCD = 3 $ ;
- $ 9 = 3^2, GCD = 2 $ .

The rest have $ GCD = 1 $ .

## 样例 #1

### 输入

```
4
4
2
72
10

```

### 输出

```
2
1
61
6

```



---

---
title: "String"
layout: "post"
diff: 省选/NOI-
pid: CF123D
tag: ['线段树', '排序', '后缀数组 SA']
---

# String

## 题目描述

You are given a string $ s $ . Each pair of numbers $ l $ and $ r $ that fulfill the condition $ 1<=l<=r<=|s| $ , correspond to a substring of the string $ s $ , starting in the position $ l $ and ending in the position $ r $ (inclusive).

Let's define the function of two strings $ F(x,y) $ like this. We'll find a list of such pairs of numbers for which the corresponding substrings of string $ x $ are equal to string $ y $ . Let's sort this list of pairs according to the pair's first number's increasing. The value of function $ F(x,y) $ equals the number of non-empty continuous sequences in the list.

For example: $ F(babbabbababbab,babb)=6 $ . The list of pairs is as follows:

 $ (1,4),(4,7),(9,12) $

Its continuous sequences are:

- $ (1,4) $
- $ (4,7) $
- $ (9,12) $
- $ (1,4),(4,7) $
- $ (4,7),(9,12) $
- $ (1,4),(4,7),(9,12) $

Your task is to calculate for the given string $ s $ the sum $ F(s,x) $ for all $ x $ , that $ x $ belongs to the set of all substrings of a string $ s $ .

## 输入格式

The only line contains the given string $ s $ , consisting only of small Latin letters ( $ 1<=|s|<=10^{5} $ ).

## 输出格式

Print the single number — the sought sum.

Please do not use the %lld specificator to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specificator.

## 说明/提示

In the first sample the function values at $ x $ equal to "a", "aa", "aaa" and "aaaa" equal 10, 6, 3 and 1 correspondingly.

In the second sample for any satisfying $ x $ the function value is 1.

## 样例 #1

### 输入

```
aaaa

```

### 输出

```
20

```

## 样例 #2

### 输入

```
abcdef

```

### 输出

```
21

```

## 样例 #3

### 输入

```
abacabadabacaba

```

### 输出

```
188

```



---

---
title: "Cow Tennis Tournament"
layout: "post"
diff: 省选/NOI-
pid: CF283E
tag: ['线段树', '离散化', '排序']
---

# Cow Tennis Tournament

## 题目描述

Farmer John is hosting a tennis tournament with his $ n $ cows. Each cow has a skill level $ s_{i} $ , and no two cows having the same skill level. Every cow plays every other cow exactly once in the tournament, and each cow beats every cow with skill level lower than its own.

However, Farmer John thinks the tournament will be demoralizing for the weakest cows who lose most or all of their matches, so he wants to flip some of the results. In particular, at $ k $ different instances, he will take two integers $ a_{i},b_{i} $ $ (a_{i}<b_{i}) $ and flip all the results between cows with skill level between $ a_{i} $ and $ b_{i} $ inclusive. That is, for any pair $ x,y $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF283E/7acc269d103239529ceb47c1b525554954b93d55.png) he will change the result of the match on the final scoreboard (so if $ x $ won the match, the scoreboard will now display that $ y $ won the match, and vice versa). It is possible that Farmer John will change the result of a match multiple times. It is not guaranteed that $ a_{i} $ and $ b_{i} $ are equal to some cow's skill level.

Farmer John wants to determine how balanced he made the tournament results look. In particular, he wants to count the number of triples of cows $ (p,q,r) $ for which the final leaderboard shows that cow $ p $ beats cow $ q $ , cow $ q $ beats cow $ r $ , and cow $ r $ beats cow $ p $ . Help him determine this number.

Note that two triples are considered different if they do not contain the same set of cows (i.e. if there is a cow in one triple that is not in the other).

## 输入格式

On the first line are two space-separated integers, $ n $ and $ k $ $ (3<=n<=10^{5}; 0<=k<=10^{5}) $ . On the next line are $ n $ space-separated distinct integers, $ s_{1},s_{2},...,s_{n} $ $ (1<=s_{i}<=10^{9}) $ , denoting the skill levels of the cows. On the next $ k $ lines are two space separated integers, $ a_{i} $ and $ b_{i} $ $ (1<=a_{i}<b_{i}<=10^{9}) $ representing the changes Farmer John made to the scoreboard in the order he makes it.

## 输出格式

A single integer, containing the number of triples of cows $ (p,q,r) $ for which the final leaderboard shows that cow $ p $ beats cow $ q $ , cow $ q $ beats cow $ r $ , and cow $ r $ beats cow $ p $ .

Please do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

In the first sample, cow 3 > cow 1, cow 3 > cow 2, and cow 2 > cow 1. However, the results between cows 1 and 2 and cows 2 and 3 are flipped, so now FJ's results show that cow 1 > cow 2, cow 2 > cow 3, and cow 3 > cow 1, so cows 1, 2, and 3 form a balanced triple.

## 样例 #1

### 输入

```
3 2
1 2 3
1 2
2 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5 3
5 9 4 1 7
1 7
2 8
3 9

```

### 输出

```
3

```



---

---
title: "Strange Sorting"
layout: "post"
diff: 省选/NOI-
pid: CF484C
tag: ['字符串', '递推', '排序']
---

# Strange Sorting

## 题目描述

How many specific orders do you know? Ascending order, descending order, order of ascending length, order of ascending polar angle... Let's have a look at another specific order:  $ d $ -sorting. This sorting is applied to the strings of length at least $ d $ , where $ d $ is some positive integer. The characters of the string are sorted in following manner: first come all the 0-th characters of the initial string, then the 1-st ones, then the 2-nd ones and so on, in the end go all the $ (d-1) $ -th characters of the initial string. By the $ i $ -th characters we mean all the character whose positions are exactly $ i $ modulo $ d $ . If two characters stand on the positions with the same remainder of integer division by $ d $ , their relative order after the sorting shouldn't be changed. The string is zero-indexed. For example, for string 'qwerty':

Its 1-sorting is the string 'qwerty' (all characters stand on 0 positions),

Its 2-sorting is the string 'qetwry' (characters 'q', 'e' and 't' stand on 0 positions and characters 'w', 'r' and 'y' are on 1 positions),

Its 3-sorting is the string 'qrwtey' (characters 'q' and 'r' stand on 0 positions, characters 'w' and 't' stand on 1 positions and characters 'e' and 'y' stand on 2 positions),

Its 4-sorting is the string 'qtwyer',

Its 5-sorting is the string 'qywert'.

You are given string $ S $ of length $ n $ and $ m $ shuffling operations of this string. Each shuffling operation accepts two integer arguments $ k $ and $ d $ and transforms string $ S $ as follows. For each $ i $ from $ 0 $ to $ n-k $ in the increasing order we apply the operation of $ d $ -sorting to the substring $ S\[i..i+k-1\] $ . Here $ S\[a..b\] $ represents a substring that consists of characters on positions from $ a $ to $ b $ inclusive.

After each shuffling operation you need to print string $ S $ .

## 输入格式

The first line of the input contains a non-empty string $ S $ of length $ n $ , consisting of lowercase and uppercase English letters and digits from 0 to 9.

The second line of the input contains integer $ m $ – the number of shuffling operations ( $ 1<=m·n<=10^{6} $ ).

Following $ m $ lines contain the descriptions of the operations consisting of two integers $ k $ and $ d $ ( $ 1<=d<=k<=n $ ).

## 输出格式

After each operation print the current state of string $ S $ .

## 说明/提示

Here is detailed explanation of the sample. The first modification is executed with arguments $ k=4 $ , $ d=2 $ . That means that you need to apply 2-sorting for each substring of length 4 one by one moving from the left to the right. The string will transform in the following manner:

qwerty $ → $ qewrty $ → $ qerwty $ → $ qertwy

Thus, string $ S $ equals 'qertwy' at the end of first query.

The second modification is executed with arguments $ k=6 $ , $ d=3 $ . As a result of this operation the whole string $ S $ is replaced by its 3-sorting:

qertwy $ → $ qtewry

The third modification is executed with arguments $ k=5 $ , $ d=2 $ .

qtewry $ → $ qertwy $ → $ qetyrw

## 样例 #1

### 输入

```
qwerty
3
4 2
6 3
5 2

```

### 输出

```
qertwy
qtewry
qetyrw

```



---

---
title: "Mr. Kitayuta's Technology"
layout: "post"
diff: 省选/NOI-
pid: CF505D
tag: ['排序', '拓扑排序', '连通块']
---

# Mr. Kitayuta's Technology

## 题目描述

Shuseki Kingdom在创新和技术方面是世界领先的国家。在Shuseki Kingdom中有编号1到n的n个城市。

Kitayuta先生的研究使Shuseki Kingdom会在两个城市之间建造传送管道。连接两个城市的传送管道是单向的，即从城市x到城市y的传送管道不能用来从城市y前往城市x。由于每个城市内的交通极为发达，因此如果从城市x到城市y的传送管道和从城市y到城市z的传送管道都已建造好，人们就可以直接从城市x前往城市z。

Kitayuta先生同时也是一个政客。他认为有m对“重要城市对”(ai,bi) ( 1<=i<=m )之间的交通很重要。他计划建造传送管道时，要使得对于每对“重要城市对”(ai,bi)，都可以通过使用一个或多个传送管道，从城市ai前往城市bi。请你计算出，最少需要建造几条传送管道，才能满足Kitayuta先生的需求。到目前为止，还没有建造任何传送管道，城市之间也没有任何其他有效的交通工具。

## 输入格式

输入共m+1行

第一行，两个以空格分隔的整数n和m（2 <= n<= 10 ^ 5，1 <= m<= 10 ^ 5），分别表示Shuseki王国的城市数量和重要城市对的数量。

接下来的m行中，每行有两个数字ai和bi，( 1<=ai,bi<=n,ai≠bi )，表示从城市ai必须能通过一个或多个传送管道到达城市bi（但不必保证能从城市bi前往城市ai）。保证每对重要城市对都是不同的。

## 输出格式

输出共1行，一个整数，表示能使得Kitayuta先生的需求满足的传送管道的数量的最小值。

## 说明/提示

对于第一个样例，构建管道的最佳方法之一如下图所示：

![](https://cdn.luogu.org/upload/vjudge_pic/CF505D/41d1e53a1057dea3b2f50b9af3dc7c7c17995877.png)

对于第二个样例，构建管道的最佳方法之一如下图所示：

![](https://cdn.luogu.org/upload/vjudge_pic/CF505D/3fd4624f001628b234de5055b8104860cf1c833c.png)

## 样例 #1

### 输入

```
4 5
1 2
1 3
1 4
2 3
2 4

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4 6
1 2
1 4
2 3
2 4
3 2
3 4

```

### 输出

```
4

```



---

---
title: "Tavas and Pashmaks"
layout: "post"
diff: 省选/NOI-
pid: CF535E
tag: ['排序', '栈', '凸包']
---

# Tavas and Pashmaks

## 题目描述

现在有两个比赛项目:跑步和游泳.每一个人在这两个项目都有一个正整数的值,第i个人分别为$a_i,b_i$,表示他在这个项目上的速度.
我们假定游泳的距离为$S_1$,跑步的距离为$S_2$(都是**正实数**),知道每一个人的值,如果对于第i个人,存在这样子的$S_1$和$S_2$使得$S_1/a_i+S_2/b_i<=S_1/a_j+S_2/b_j(1<=j<=n)$,那么就称这个人可以夺冠.
求出有多少个人可以夺冠.

## 输入格式

第$1$行一个正整数$n$,表示有$n$个人.
第$2$~$n+1$,每行有$2$个正整数分别表示每一个人在跑步和游泳上的速度.

## 输出格式

一行,输出所有可以夺冠的人.

## 样例 #1

### 输入

```
3
1 3
2 2
3 1

```

### 输出

```
1 2 3 

```

## 样例 #2

### 输入

```
3
1 2
1 1
2 1

```

### 输出

```
1 3 

```



---

---
title: "Thief in a Shop"
layout: "post"
diff: 省选/NOI-
pid: CF632E
tag: ['枚举', '排序', '背包 DP']
---

# Thief in a Shop

## 题目描述

A thief made his way to a shop.

As usual he has his lucky knapsack with him. The knapsack can contain $ k $ objects. There are $ n $ kinds of products in the shop and an infinite number of products of each kind. The cost of one product of kind $ i $ is $ a_{i} $ .

The thief is greedy, so he will take exactly $ k $ products (it's possible for some kinds to take several products of that kind).

Find all the possible total costs of products the thief can nick into his knapsack.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n,k<=1000 $ ) — the number of kinds of products and the number of products the thief will take.

The second line contains $ n $ integers $ a_{i} $ ( $ 1<=a_{i}<=1000 $ ) — the costs of products for kinds from $ 1 $ to $ n $ .

## 输出格式

Print the only line with all the possible total costs of stolen products, separated by a space. The numbers should be printed in the ascending order.

## 样例 #1

### 输入

```
3 2
1 2 3

```

### 输出

```
2 3 4 5 6

```

## 样例 #2

### 输入

```
5 5
1 1 1 1 1

```

### 输出

```
5

```

## 样例 #3

### 输入

```
3 3
3 5 11

```

### 输出

```
9 11 13 15 17 19 21 25 27 33

```



---

---
title: "Professor's task"
layout: "post"
diff: 省选/NOI-
pid: CF70D
tag: ['计算几何', '排序', '凸包', '叉积']
---

# Professor's task

## 题目描述

Once a walrus professor Plato asked his programming students to perform the following practical task.

The students had to implement such a data structure that would support a convex hull on some set of points $ S $ . The input to the program had $ q $ queries of two types:

1\. Add a point with coordinates $ (x,y) $ into the set $ S $ . Note that in this case the convex hull of $ S $ could have changed, and could have remained the same.

2\. Say whether a point with coordinates $ (x,y) $ belongs to an area limited by the convex hull, including the border.

All the students coped with the task. What about you?

## 输入格式

The first line contains an integer $ q $ ( $ 4<=q<=10^{5} $ ).

Then follow $ q $ lines in the following way: " $ t $ $ x $ $ y $ ", where $ t $ is the query type (1 or 2), and $ (x,y) $ are the coordinates of the point ( $ -10^{6}<=x,y<=10^{6} $ , $ x $ and $ y $ are integers).

There is at least one query of type 2.

It is guaranteed that the three queries of the first type follow first and the points given in the queries form a non-degenerative triangle. Also all the points added in $ S $ are distinct.

## 输出格式

For each query of the second type print one string containing "YES", if the point lies inside the convex hull or on its border. Otherwise, print "NO".

## 样例 #1

### 输入

```
8
1 0 0
1 2 0
1 2 2
2 1 0
1 0 2
2 1 1
2 2 1
2 20 -1

```

### 输出

```
YES
YES
YES
NO

```



---

---
title: "Family Photos"
layout: "post"
diff: 省选/NOI-
pid: CF725F
tag: ['贪心', '排序']
---

# Family Photos

## 题目描述

Alice and Bonnie are sisters, but they don't like each other very much. So when some old family photos were found in the attic, they started to argue about who should receive which photos. In the end, they decided that they would take turns picking photos. Alice goes first.

There are $ n $ stacks of photos. Each stack contains exactly two photos. In each turn, a player may take only a photo from the top of one of the stacks.

Each photo is described by two non-negative integers $ a $ and $ b $ , indicating that it is worth $ a $ units of happiness to Alice and $ b $ units of happiness to Bonnie. Values of $ a $ and $ b $ might differ for different photos.

It's allowed to pass instead of taking a photo. The game ends when all photos are taken or both players pass consecutively.

The players don't act to maximize their own happiness. Instead, each player acts to maximize the amount by which her happiness exceeds her sister's. Assuming both players play optimal, find the difference between Alice's and Bonnie's happiness. That is, if there's a perfectly-played game such that Alice has $ x $ happiness and Bonnie has $ y $ happiness at the end, you should print $ x-y $ .

## 输入格式

The first line of input contains a single integer $ n $ ( $ 1<=n<=100000 $ ) — the number of two-photo stacks. Then follow $ n $ lines, each describing one of the stacks. A stack is described by four space-separated non-negative integers $ a_{1} $ , $ b_{1} $ , $ a_{2} $ and $ b_{2} $ , each not exceeding $ 10^{9} $ . $ a_{1} $ and $ b_{1} $ describe the top photo in the stack, while $ a_{2} $ and $ b_{2} $ describe the bottom photo in the stack.

## 输出格式

Output a single integer: the difference between Alice's and Bonnie's happiness if both play optimally.

## 样例 #1

### 输入

```
2
12 3 4 7
1 15 9 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2
5 4 8 8
4 12 14 0

```

### 输出

```
4

```

## 样例 #3

### 输入

```
1
0 10 0 10

```

### 输出

```
-10

```



---

---
title: "Gift"
layout: "post"
diff: 省选/NOI-
pid: CF76A
tag: ['排序', '生成树', '栈']
---

# Gift

## 题目描述

The kingdom of Olympia consists of $ N $ cities and $ M $ bidirectional roads. Each road connects exactly two cities and two cities can be connected with more than one road. Also it possible that some roads connect city with itself making a loop.

All roads are constantly plundered with bandits. After a while bandits became bored of wasting time in road robberies, so they suggested the king of Olympia to pay off. According to the offer, bandits want to get a gift consisted of gold and silver coins. Offer also contains a list of restrictions: for each road it is known $ g_{i} $ — the smallest amount of gold and $ s_{i} $ — the smallest amount of silver coins that should be in the gift to stop robberies on the road. That is, if the gift contains $ a $ gold and $ b $ silver coins, then bandits will stop robberies on all the roads that $ g_{i}<=a $ and $ s_{i}<=b $ .

Unfortunately kingdom treasury doesn't contain neither gold nor silver coins, but there are Olympian tugriks in it. The cost of one gold coin in tugriks is $ G $ , and the cost of one silver coin in tugriks is $ S $ . King really wants to send bandits such gift that for any two cities there will exist a safe path between them. Your task is to find the minimal cost in Olympian tugriks of the required gift.

## 输入格式

The first line of the input contains two integers $ N $ and $ M $ ( $ 2<=N<=200 $ , $ 1<=M<=50000 $ ) — the number of cities and the number of roads, respectively. The second line contains two integers $ G $ and $ S $ ( $ 1<=G,S<=10^{9} $ ) — the prices of gold and silver coins in tugriks. The following $ M $ lines contain information about the offer. Each of the records in list is given as four integers $ x_{i},y_{i},g_{i},s_{i} $ , where $ x_{i} $ and $ y_{i} $ are the numbers of cities that the road connects and $ g_{i} $ , $ s_{i} $ are minimal gold and silver coins requirements for the $ i $ -th road ( $ 1<=x_{i},y_{i}<=N $ , $ 1<=g_{i},s_{i}<=10^{9} $ ). Cities are numbered from $ 1 $ to $ N $ . It is possible that there are more than one road between a pair of cities. It is possible that a road connects the city with itself.

## 输出格式

The output should contain the minimal cost of the gift in Olympian tugriks. If there is no gift that satisfies the given requirements output ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF76A/843ffcb025f9d699cf4e412e21508ca44c9ae26c.png).

## 样例 #1

### 输入

```
3 3
2 1
1 2 10 15
1 2 4 20
1 3 5 1

```

### 输出

```
30

```



---

---
title: "Willem, Chtholly and Seniorious"
layout: "post"
diff: 省选/NOI-
pid: CF896C
tag: ['暴力数据结构', '颜色段均摊（珂朵莉树 ODT）', '枚举', '排序', '构造']
---

# Willem, Chtholly and Seniorious

## 题目描述

【题面】
请你写一种奇怪的数据结构，支持：
- $1$  $l$  $r$  $x$ ：将$[l,r]$ 区间所有数加上$x$ 
- $2$  $l$  $r$  $x$ ：将$[l,r]$ 区间所有数改成$x$ 
- $3$  $l$  $r$  $x$ ：输出将$[l,r]$ 区间从小到大排序后的第$x$ 个数是的多少(即区间第$x$ 小，数字大小相同算多次，保证 $1\leq$  $x$  $\leq$  $r-l+1$  )
- $4$  $l$  $r$  $x$  $y$ ：输出$[l,r]$ 区间每个数字的$x$ 次方的和模$y$ 的值(即($\sum^r_{i=l}a_i^x$ ) $\mod y$ )

## 输入格式

输入一行四个整数$n,m,seed,v_{max}$ （$1\leq $  $n,m\leq 10^{5}$  ,$0\leq seed \leq 10^{9}+7$  $,1\leq vmax \leq 10^{9} $ ）
其中$n$ 表示数列长度，$m$ 表示操作次数，后面两个用于生成输入数据。
数据生成的伪代码如下
![](https://cdn.luogu.org/upload/pic/13887.png )

其中上面的op指题面中提到的四个操作。

## 输出格式

对于每个操作3和4，输出一行仅一个数。

## 样例 #1

### 输入

```
10 10 7 9

```

### 输出

```
2
1
0
3

```

## 样例 #2

### 输入

```
10 10 9 9

```

### 输出

```
1
1
3
3

```



---

---
title: "Coins Exhibition"
layout: "post"
diff: 省选/NOI-
pid: CF930E
tag: ['动态规划 DP', '离散化', '排序']
---

# Coins Exhibition

## 题目描述

Arkady and Kirill visited an exhibition of rare coins. The coins were located in a row and enumerated from left to right from $ 1 $ to $ k $ , each coin either was laid with its obverse (front) side up, or with its reverse (back) side up.

Arkady and Kirill made some photos of the coins, each photo contained a segment of neighboring coins. Akrady is interested in obverses, so on each photo made by him there is at least one coin with obverse side up. On the contrary, Kirill is interested in reverses, so on each photo made by him there is at least one coin with its reverse side up.

The photos are lost now, but Arkady and Kirill still remember the bounds of the segments of coins each photo contained. Given this information, compute the remainder of division by $ 10^{9}+7 $ of the number of ways to choose the upper side of each coin in such a way, that on each Arkady's photo there is at least one coin with obverse side up, and on each Kirill's photo there is at least one coin with reverse side up.

## 输入格式

The first line contains three integers $ k $ , $ n $ and $ m $ ( $ 1<=k<=10^{9} $ , $ 0<=n,m<=10^{5} $ ) — the total number of coins, the number of photos made by Arkady, and the number of photos made by Kirill, respectively.

The next $ n $ lines contain the descriptions of Arkady's photos, one per line. Each of these lines contains two integers $ l $ and $ r $ ( $ 1<=l<=r<=k $ ), meaning that among coins from the $ l $ -th to the $ r $ -th there should be at least one with obverse side up.

The next $ m $ lines contain the descriptions of Kirill's photos, one per line. Each of these lines contains two integers $ l $ and $ r $ ( $ 1<=l<=r<=k $ ), meaning that among coins from the $ l $ -th to the $ r $ -th there should be at least one with reverse side up.

## 输出格式

Print the only line — the number of ways to choose the side for each coin modulo $ 10^{9}+7=1000000007 $ .

## 说明/提示

In the first example the following ways are possible ('O' — obverse, 'R' — reverse side):

- OROOR,
- ORORO,
- ORORR,
- RROOR,
- RRORO,
- RRORR,
- ORROR,
- ORRRO.

In the second example the information is contradictory: the second coin should have obverse and reverse sides up at the same time, that is impossible. So, the answer is $ 0 $ .

## 样例 #1

### 输入

```
5 2 2
1 3
3 5
2 2
4 5

```

### 输出

```
8

```

## 样例 #2

### 输入

```
5 3 2
1 3
2 2
3 5
2 2
4 5

```

### 输出

```
0

```

## 样例 #3

### 输入

```
60 5 7
1 3
50 60
1 60
30 45
20 40
4 5
6 37
5 18
50 55
22 27
25 31
44 45

```

### 输出

```
732658600

```



---

---
title: "Good Subsegments"
layout: "post"
diff: 省选/NOI-
pid: CF997E
tag: ['线段树', '排序', '栈']
---

# Good Subsegments

## 题目描述

A permutation $ p $ of length $ n $ is a sequence $ p_1, p_2, \ldots, p_n $ consisting of $ n $ distinct integers, each of which from $ 1 $ to $ n $ ( $ 1 \leq p_i \leq n $ ) .

Let's call the subsegment $ [l,r] $ of the permutation good if all numbers from the minimum on it to the maximum on this subsegment occur among the numbers $ p_l, p_{l+1}, \dots, p_r $ .

For example, good segments of permutation $ [1, 3, 2, 5, 4] $ are:

- $ [1, 1] $ ,
- $ [1, 3] $ ,
- $ [1, 5] $ ,
- $ [2, 2] $ ,
- $ [2, 3] $ ,
- $ [2, 5] $ ,
- $ [3, 3] $ ,
- $ [4, 4] $ ,
- $ [4, 5] $ ,
- $ [5, 5] $ .

You are given a permutation $ p_1, p_2, \ldots, p_n $ .

You need to answer $ q $ queries of the form: find the number of good subsegments of the given segment of permutation.

In other words, to answer one query, you need to calculate the number of good subsegments $ [x \dots y] $ for some given segment $ [l \dots r] $ , such that $ l \leq x \leq y \leq r $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \leq n \leq 120000 $ ) — the number of elements in the permutation.

The second line contains $ n $ distinct integers $ p_1, p_2, \ldots, p_n $ separated by spaces ( $ 1 \leq p_i \leq n $ ).

The third line contains an integer $ q $ ( $ 1 \leq q \leq 120000 $ ) — number of queries.

The following $ q $ lines describe queries, each line contains a pair of integers $ l $ , $ r $ separated by space ( $ 1 \leq l \leq r \leq n $ ).

## 输出格式

Print a $ q $ lines, $ i $ -th of them should contain a number of good subsegments of a segment, given in the $ i $ -th query.

## 样例 #1

### 输入

```
5
1 3 2 5 4
15
1 1
1 2
1 3
1 4
1 5
2 2
2 3
2 4
2 5
3 3
3 4
3 5
4 4
4 5
5 5

```

### 输出

```
1
2
5
6
10
1
3
4
7
1
2
4
1
3
1

```



---

