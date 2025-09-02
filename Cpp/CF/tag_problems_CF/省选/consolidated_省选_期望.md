---
title: "Maze"
layout: "post"
diff: 省选/NOI-
pid: CF123E
tag: ['概率论', '期望']
---

# Maze

## 题目描述

A maze is represented by a tree (an undirected graph, where exactly one way exists between each pair of vertices). In the maze the entrance vertex and the exit vertex are chosen with some probability. The exit from the maze is sought by Deep First Search. If there are several possible ways to move, the move is chosen equiprobably. Consider the following pseudo-code:

```plain
DFS(x)
    if x == exit vertex then
        finish search
    flag[x] <- TRUE
    random shuffle the vertices' order in V(x) // here all permutations have equal probability to be chosen
    for i <- 1 to length[V] do
        if flag[V[i]] = FALSE then
            count++;
            DFS(y);
    count++;
```

$ V(x) $ is the list vertices adjacent to $ x $ . The $ flag $ array is initially filled as FALSE. $ DFS $ initially starts with a parameter of an entrance vertex. When the search is finished, variable $ count $ will contain the number of moves.

Your task is to count the mathematical expectation of the number of moves one has to do to exit the maze.

## 输入格式

The first line determines the number of vertices in the graph $ n $ ( $ 1<=n<=10^{5} $ ). The next $ n-1 $ lines contain pairs of integers $ a_{i} $ and $ b_{i} $ , which show the existence of an edge between $ a_{i} $ and $ b_{i} $ vertices ( $ 1<=a_{i},b_{i}<=n $ ). It is guaranteed that the given graph is a tree.

Next $ n $ lines contain pairs of non-negative numbers $ x_{i} $ and $ y_{i} $ , which represent the probability of choosing the $ i $ -th vertex as an entrance and exit correspondingly. The probabilities to choose vertex $ i $ as an entrance and an exit equal ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF123E/0240d8f3c959727649615a9c4b8bbbdbc401999b.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF123E/4e43637d1b15e1f62f6536d616a94de5b4b829ea.png) correspondingly. The sum of all $ x_{i} $ and the sum of all $ y_{i} $ are positive and do not exceed $ 10^{6} $ .

## 输出格式

Print the expectation of the number of moves. The absolute or relative error should not exceed $ 10^{-9} $ .

## 说明/提示

In the first sample the entrance vertex is always 1 and the exit vertex is always 2.

In the second sample the entrance vertex is always 1 and the exit vertex with the probability of 2/5 will be 2 of with the probability if 3/5 will be 3. The mathematical expectations for the exit vertices 2 and 3 will be equal (symmetrical cases). During the first move one can go to the exit vertex with the probability of 0.5 or to go to a vertex that's not the exit vertex with the probability of 0.5. In the first case the number of moves equals 1, in the second one it equals 3. The total mathematical expectation is counted as $ 2/5×(1×0.5+3×0.5)+3/5×(1×0.5+3×0.5) $

## 样例 #1

### 输入

```
2
1 2
0 1
1 0

```

### 输出

```
1.00000000000000000000

```

## 样例 #2

### 输入

```
3
1 2
1 3
1 0
0 2
0 3

```

### 输出

```
2.00000000000000000000

```

## 样例 #3

### 输入

```
7
1 2
1 3
2 4
2 5
3 6
3 7
1 1
1 1
1 1
1 1
1 1
1 1
1 1

```

### 输出

```
4.04081632653
```



---

---
title: "Koxia and Tree"
layout: "post"
diff: 省选/NOI-
pid: CF1770E
tag: ['数学', '递推', '期望']
---

# Koxia and Tree

## 题目描述

Imi has an undirected tree with $ n $ vertices where edges are numbered from $ 1 $ to $ n-1 $ . The $ i $ -th edge connects vertices $ u_i $ and $ v_i $ . There are also $ k $ butterflies on the tree. Initially, the $ i $ -th butterfly is on vertex $ a_i $ . All values of $ a $ are pairwise distinct.

Koxia plays a game as follows:

- For $ i = 1, 2, \dots, n - 1 $ , Koxia set the direction of the $ i $ -th edge as $ u_i \rightarrow v_i $ or $ v_i \rightarrow u_i $ with equal probability.
- For $ i = 1, 2, \dots, n - 1 $ , if a butterfly is on the initial vertex of $ i $ -th edge and there is no butterfly on the terminal vertex, then this butterfly flies to the terminal vertex. Note that operations are sequentially in order of $ 1, 2, \dots, n - 1 $ instead of simultaneously.
- Koxia chooses two butterflies from the $ k $ butterflies with equal probability from all possible $ \frac{k(k-1)}{2} $ ways to select two butterflies, then she takes the distance $ ^\dagger $ between the two chosen vertices as her score.

Now, Koxia wants you to find the expected value of her score, modulo $ 998\,244\,353^\ddagger $ .

 $ ^\dagger $ The distance between two vertices on a tree is the number of edges on the (unique) simple path between them.

 $ ^\ddagger $ Formally, let $ M = 998\,244\,353 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 输入格式

The first line contains two integers $ n $ , $ k $ ( $ 2 \leq k \leq n \leq 3 \cdot {10}^5 $ ) — the size of the tree and the number of butterflies.

The second line contains $ k $ integers $ a_1, a_2, \dots, a_k $ ( $ 1 \leq a_i \leq n $ ) — the initial position of butterflies. It's guaranteed that all positions are distinct.

The $ i $ -th line in following $ n − 1 $ lines contains two integers $ u_i $ , $ v_i $ ( $ 1 \leq u_i, v_i \leq n $ , $ u_i \neq v_i $ ) — the vertices the $ i $ -th edge connects.

It is guaranteed that the given edges form a tree.

## 输出格式

Output a single integer — the expected value of Koxia's score, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, the tree is shown below. Vertices containing butterflies are noted as bold.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1770E/b5933c313633856733c2f7b6fac2b7be83ed7851.png)There are only $ 2 $ butterflies so the choice of butterflies is fixed. Let's consider the following $ 4 $ cases:

- Edges are $ 1 \rightarrow 2 $ and $ 2 \rightarrow 3 $ : butterfly on vertex $ 1 $ moves to vertex $ 2 $ , but butterfly on vertex $ 3 $ doesn't move. The distance between vertices $ 2 $ and $ 3 $ is $ 1 $ .
- Edges are $ 1 \rightarrow 2 $ and $ 3 \rightarrow 2 $ : butterfly on vertex $ 1 $ moves to vertex $ 2 $ , but butterfly on vertex $ 3 $ can't move to vertex $ 2 $ because it's occupied. The distance between vertices $ 2 $ and $ 3 $ is $ 1 $ .
- Edges are $ 2 \rightarrow 1 $ and $ 2 \rightarrow 3 $ : butterflies on both vertex $ 1 $ and vertex $ 3 $ don't move. The distance between vertices $ 1 $ and $ 3 $ is $ 2 $ .
- Edges are $ 2 \rightarrow 1 $ and $ 3 \rightarrow 2 $ : butterfly on vertex $ 1 $ doesn't move, but butterfly on vertex $ 3 $ move to vertex $ 2 $ . The distance between vertices $ 1 $ and $ 2 $ is $ 1 $ .

Therefore, the expected value of Koxia's score is $ \frac {1+1+2+1} {4} = \frac {5} {4} $ , which is $ 748\,683\,266 $ after modulo $ 998\,244\,353 $ .

In the second test case, the tree is shown below. Vertices containing butterflies are noted as bold. The expected value of Koxia's score is $ \frac {11} {6} $ , which is $ 831\,870\,296 $ after modulo $ 998\,244\,353 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1770E/c99c1f065a7b394b09acc90fcc6d66aa233890d9.png)

## 样例 #1

### 输入

```
3 2
1 3
1 2
2 3
```

### 输出

```
748683266
```

## 样例 #2

### 输入

```
5 3
3 4 5
1 2
1 3
2 4
2 5
```

### 输出

```
831870296
```



---

---
title: "T-shirt"
layout: "post"
diff: 省选/NOI-
pid: CF183D
tag: ['贪心', '背包 DP', '期望']
---

# T-shirt

## 题目描述

你将在CodeForces的一个$n$人团队实习，n个工程师由1到$n$编号。你决定给每个工程师一个纪念品：一件来自你的国家的T恤（T恤在CodeForces很受欢迎）。不幸的是，你不知道$n$个工程师各自衣服的尺寸。一共有1到m共m种不同的尺寸，并且每个工程师只适合一个尺寸。

你不知道每个工程师的尺寸，所以你询问你的朋友Gerald。很遗憾，他也不知道每个工程师的尺寸，但他知道对于第$i$个工程师，适合第j种T恤的概率。

最后你带来了$n$件T恤（这$n$件T恤可以是任意组合，你也可以带多件同样尺寸的衣服），在你准备T恤的时候并不知道每个工程师的尺寸，所以你只能根据Gerald提供的概率决定你所带的T恤。

你的任务是最大化收到适合自己的衣服的工程师数量的期望值。

当你到达办公室后，你会询问每个工程师他适合的T恤的尺寸，如果你有那个尺寸的衣服，你就会给他一件，否则就不给他T恤。你会从$1$号问起，一直问到$n$号

---

## 输入格式

第一行为两个用空格分开的整数n和m（$1<=n<=3000$,$1<=m<=300$)，分别代表工程师数量和衣服尺寸数量

接下来有$n$行，每行$m$个空格分开的整数，第$i$行第$j$个数字代表第$i$个工程师适合第$j$种T恤的概率。每个整数在$1$到$1000$之间。实际上的概率应为每个整数除以1000。

保证对于每个工程师适合每种T恤的概率之和为$1$。

## 输出格式

输出一行，一个实数代表收到T恤的工程师数量的最大期望值。允许最大误差为$10^{-9}$。

感谢@LJZ_C 提供的翻译

## 样例 #1

### 输入

```
2 2
500 500
500 500

```

### 输出

```
1.500000000000

```

## 样例 #2

### 输入

```
3 3
1000 0 0
1000 0 0
0 1000 0

```

### 输出

```
3.000000000000

```

## 样例 #3

### 输入

```
1 4
100 200 300 400

```

### 输出

```
0.400000000000

```



---

---
title: "Piglet's Birthday"
layout: "post"
diff: 省选/NOI-
pid: CF248E
tag: ['动态规划 DP', '期望']
---

# Piglet's Birthday

## 题目描述

Piglet has got a birthday today. His friend Winnie the Pooh wants to make the best present for him — a honey pot. Of course Winnie realizes that he won't manage to get the full pot to Piglet. In fact, he is likely to eat all the honey from the pot. And as soon as Winnie planned a snack on is way, the pot should initially have as much honey as possible.

The day before Winnie the Pooh replenished his honey stocks. Winnie-the-Pooh has $ n $ shelves at home, each shelf contains some, perhaps zero number of honey pots. During the day Winnie came to the honey shelves $ q $ times; on the $ i $ -th time he came to some shelf $ u_{i} $ , took from it some pots $ k_{i} $ , tasted the honey from each pot and put all those pots on some shelf $ v_{i} $ . As Winnie chose the pots, he followed his intuition. And that means that among all sets of $ k_{i} $ pots on shelf $ u_{i} $ , he equiprobably chooses one.

Now Winnie remembers all actions he performed with the honey pots. He wants to take to the party the pot he didn't try the day before. For that he must know the mathematical expectation of the number $ m $ of shelves that don't have a single untasted pot. To evaluate his chances better, Winnie-the-Pooh wants to know the value $ m $ after each action he performs.

Your task is to write a program that will find those values for him.

## 输入格式

The first line of the input contains a single number $ n $ ( $ 1<=n<=10^{5} $ ) — the number of shelves at Winnie's place. The second line contains $ n $ integers $ a_{i} $ ( $ 1<=i<=n $ , $ 0<=a_{i}<=100 $ ) — the number of honey pots on a shelf number $ i $ .

The next line contains integer $ q $ ( $ 1<=q<=10^{5} $ ) — the number of actions Winnie did the day before. Then follow $ q $ lines, the $ i $ -th of them describes an event that follows chronologically; the line contains three integers $ u_{i} $ , $ v_{i} $ and $ k_{i} $ ( $ 1<=u_{i},v_{i}<=n $ , $ 1<=k_{i}<=5 $ ) — the number of the shelf from which Winnie took pots, the number of the shelf on which Winnie put the pots after he tasted each of them, and the number of the pots Winnie tasted, correspondingly.

Consider the shelves with pots numbered with integers from 1 to $ n $ . It is guaranteed that Winnie-the-Pooh Never tried taking more pots from the shelf than it has.

## 输出格式

For each Winnie's action print the value of the mathematical expectation $ m $ by the moment when this action is performed. The relative or absolute error of each value mustn't exceed $ 10^{-9} $ .

## 样例 #1

### 输入

```
3
2 2 3
5
1 2 1
2 1 2
1 2 2
3 1 1
3 2 2

```

### 输出

```
0.000000000000
0.333333333333
1.000000000000
1.000000000000
2.000000000000

```



---

---
title: "Broken robot"
layout: "post"
diff: 省选/NOI-
pid: CF24D
tag: ['动态规划 DP', '期望', '高斯消元']
---

# Broken robot

## 题目描述

## 题意翻译
$n$ 行 $m$ 列的矩阵，现在在 $(x,y)$，每次等概率向左，右，下走或原地不动，但不能走出去，问走到最后一行期望的步数。

注意，$(1,1)$ 是木板的左上角，$(n,m)$ 是木板的右下角。

## 输入格式

第一行为两个整数 $n,m$。

第二行为两个整数 $x,y$。

## 输出格式

一行，输出所需移动步数的数学期望值，至少保留 $4$ 位小数的值。

## 说明/提示

$1\le n,m\le 10^3$，$1\le x\le n$，$1\le y\le m$。

## 样例 #1

### 输入

```
10 10
10 4

```

### 输出

```
0.0000000000

```

## 样例 #2

### 输入

```
10 14
5 14

```

### 输出

```
18.0038068653

```



---

---
title: "Painting The Wall"
layout: "post"
diff: 省选/NOI-
pid: CF398B
tag: ['数学', '概率论', '期望']
---

# Painting The Wall

## 题目描述

User ainta decided to paint a wall. The wall consists of $ n^{2} $ tiles, that are arranged in an $ n×n $ table. Some tiles are painted, and the others are not. As he wants to paint it beautifully, he will follow the rules below.

1. Firstly user ainta looks at the wall. If there is at least one painted cell on each row and at least one painted cell on each column, he stops coloring. Otherwise, he goes to step 2.
2. User ainta choose any tile on the wall with uniform probability.
3. If the tile he has chosen is not painted, he paints the tile. Otherwise, he ignores it.
4. Then he takes a rest for one minute even if he doesn't paint the tile. And then ainta goes to step 1.

However ainta is worried if it would take too much time to finish this work. So he wants to calculate the expected time needed to paint the wall by the method above. Help him find the expected time. You can assume that choosing and painting any tile consumes no time at all.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=2·10^{3} $ ; $ 0<=m<=min(n^{2},2·10^{4}) $ ) — the size of the wall and the number of painted cells.

Next $ m $ lines goes, each contains two integers $ r_{i} $ and $ c_{i} $ ( $ 1<=r_{i},c_{i}<=n $ ) — the position of the painted cell. It is guaranteed that the positions are all distinct. Consider the rows of the table are numbered from $ 1 $ to $ n $ . Consider the columns of the table are numbered from $ 1 $ to $ n $ .

## 输出格式

In a single line print the expected time to paint the wall in minutes. Your answer will be considered correct if it has at most $ 10^{-4} $ absolute or relative error.

## 样例 #1

### 输入

```
5 2
2 3
4 1

```

### 输出

```
11.7669491886

```

## 样例 #2

### 输入

```
2 2
1 1
1 2

```

### 输出

```
2.0000000000

```

## 样例 #3

### 输入

```
1 1
1 1

```

### 输出

```
0.0000000000

```



---

---
title: "Game with Strings"
layout: "post"
diff: 省选/NOI-
pid: CF482C
tag: ['字符串', '状态合并', '期望']
---

# Game with Strings

## 题目描述

你和你的朋友玩一个游戏，游戏规则如下。

你的朋友创造出了 $n$ 个长度均为 $m$ 的不相同的字符串，然后他随机地选择其中一个。他选择这些字符串的概率是相等的，也就是说，他选择 $n$ 个字符串中的每一个的概率是 $\frac{1}{n}$。你想猜猜你的朋友选择了哪个字符串。

为了猜到你的朋友选择了哪个字符串，你可以问他问题，形式如下：字符串中第 $pos$ 个字符是什么？当这些问题的答案能够唯一确定一个字符串时，我们认为这个字符串被猜到了。在字符串被猜到后，你将停止提问。

你没有特殊的策略，所以你每次可能会等概率的问任何一个你从没猜过的位置。求猜到你的朋友选的字符串所需次数的期望。

## 输入格式

第一行包括一个数字 $n$（$1 \le n \le 50$）。接下来 $n$ 行，每行一个字符串，表示你朋友创造出的字符串。除此之外，所有字符的长度是相同的，在 $1\sim 20$ 之间。

## 输出格式

输出期望值，要求误差在 $10^{-9}$ 以内。

## 样例 #1

### 输入

```
2
aab
aac

```

### 输出

```
2.000000000000000

```

## 样例 #2

### 输入

```
3
aaA
aBa
Caa

```

### 输出

```
1.666666666666667

```

## 样例 #3

### 输入

```
3
aca
vac
wqq

```

### 输出

```
1.000000000000000

```



---

---
title: "Levels and Regions"
layout: "post"
diff: 省选/NOI-
pid: CF643C
tag: ['斜率优化', '前缀和', '期望']
---

# Levels and Regions

## 题目描述

Radewoosh is playing a computer game. There are $ n $ levels, numbered $ 1 $ through $ n $ . Levels are divided into $ k $ regions (groups). Each region contains some positive number of consecutive levels.

The game repeats the the following process:

1. If all regions are beaten then the game ends immediately. Otherwise, the system finds the first region with at least one non-beaten level. Let $ X $ denote this region.
2. The system creates an empty bag for tokens. Each token will represent one level and there may be many tokens representing the same level.
  - For each already beaten level $ i $ in the region $ X $ , the system adds $ t_{i} $ tokens to the bag (tokens representing the $ i $ -th level).
  - Let $ j $ denote the first non-beaten level in the region $ X $ . The system adds $ t_{j} $ tokens to the bag.
3. Finally, the system takes a uniformly random token from the bag and a player starts the level represented by the token. A player spends one hour and beats the level, even if he has already beaten it in the past.

Given $ n $ , $ k $ and values $ t_{1},t_{2},...,t_{n} $ , your task is to split levels into regions. Each level must belong to exactly one region, and each region must contain non-empty consecutive set of levels. What is the minimum possible expected number of hours required to finish the game?

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1<=n<=200000 $ , $ 1<=k<=min(50,n) $ ) — the number of levels and the number of regions, respectively.

The second line contains $ n $ integers $ t_{1},t_{2},...,t_{n} $ ( $ 1<=t_{i}<=100000 $ ).

## 输出格式

Print one real number — the minimum possible expected value of the number of hours spent to finish the game if levels are distributed between regions in the optimal way. Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-4} $ .

Namely: let's assume that your answer is $ a $ , and the answer of the jury is $ b $ . The checker program will consider your answer correct if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643C/73b7e412a182af1e0d063e02722d13792ecaced8.png).

## 说明/提示

In the first sample, we are supposed to split $ 4 $ levels into $ 2 $ regions. It's optimal to create the first region with only one level (it must be the first level). Then, the second region must contain other three levels.

In the second sample, it's optimal to split levels into two regions with $ 3 $ levels each.

## 样例 #1

### 输入

```
4 2
100 3 5 7

```

### 输出

```
5.7428571429

```

## 样例 #2

### 输入

```
6 2
1 2 4 8 16 32

```

### 输出

```
8.5000000000

```



---

---
title: "Gosha is hunting"
layout: "post"
diff: 省选/NOI-
pid: CF739E
tag: ['二分', '费用流', '期望']
---

# Gosha is hunting

## 题目描述

Gosha is hunting. His goal is to catch as many Pokemons as possible. Gosha has $ a $ Poke Balls and $ b $ Ultra Balls. There are $ n $ Pokemons. They are numbered $ 1 $ through $ n $ . Gosha knows that if he throws a Poke Ball at the $ i $ -th Pokemon he catches it with probability $ p_{i} $ . If he throws an Ultra Ball at the $ i $ -th Pokemon he catches it with probability $ u_{i} $ . He can throw at most one Ball of each type at any Pokemon.

The hunting proceeds as follows: at first, Gosha chooses no more than $ a $ Pokemons at which he will throw Poke Balls and no more than $ b $ Pokemons at which he will throw Ultra Balls. After that, he throws the chosen Balls at the chosen Pokemons. If he throws both Ultra Ball and Poke Ball at some Pokemon, he is caught if and only if he is caught by any of these Balls. The outcome of a throw doesn't depend on the other throws.

Gosha would like to know what is the expected number of the Pokemons he catches if he acts in an optimal way. In other words, he would like to know the maximum possible expected number of Pokemons can catch.

## 输入格式

The first line contains three integers $ n $ , $ a $ and $ b $ ( $ 2<=n<=2000 $ , $ 0<=a,b<=n $ ) — the number of Pokemons, the number of Poke Balls and the number of Ultra Balls.

The second line contains $ n $ real values $ p_{1},p_{2},...,p_{n} $ ( $ 0<=p_{i}<=1 $ ), where $ p_{i} $ is the probability of catching the $ i $ -th Pokemon if Gosha throws a Poke Ball to it.

The third line contains $ n $ real values $ u_{1},u_{2},...,u_{n} $ ( $ 0<=u_{i}<=1 $ ), where $ u_{i} $ is the probability of catching the $ i $ -th Pokemon if Gosha throws an Ultra Ball to it.

All the probabilities are given with exactly three digits after the decimal separator.

## 输出格式

Print the maximum possible expected number of Pokemons Gosha can catch. The answer is considered correct if it's absolute or relative error doesn't exceed $ 10^{-4} $ .

## 样例 #1

### 输入

```
3 2 2
1.000 0.000 0.500
0.000 1.000 0.500

```

### 输出

```
2.75

```

## 样例 #2

### 输入

```
4 1 3
0.100 0.500 0.500 0.600
0.100 0.500 0.900 0.400

```

### 输出

```
2.16

```

## 样例 #3

### 输入

```
3 2 0
0.412 0.198 0.599
0.612 0.987 0.443

```

### 输出

```
1.011
```



---

---
title: "Inversions After Shuffle"
layout: "post"
diff: 省选/NOI-
pid: CF749E
tag: ['树状数组', '枚举', '期望']
---

# Inversions After Shuffle

## 题目描述

You are given a permutation of integers from $ 1 $ to $ n $ . Exactly once you apply the following operation to this permutation: pick a random segment and shuffle its elements. Formally:

1. Pick a random segment (continuous subsequence) from $ l $ to $ r $ . All ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF749E/150441d31156a32e0b2da63844d600138a543898.png) segments are equiprobable.
2. Let $ k=r-l+1 $ , i.e. the length of the chosen segment. Pick a random permutation of integers from $ 1 $ to $ k $ , $ p_{1},p_{2},...,p_{k} $ . All $ k! $ permutation are equiprobable.
3. This permutation is applied to elements of the chosen segment, i.e. permutation $ a_{1},a_{2},...,a_{l-1},a_{l},a_{l+1},...,a_{r-1},a_{r},a_{r+1},...,a_{n} $ is transformed to $ a_{1},a_{2},...,a_{l-1},a_{l-1+p1},a_{l-1+p2},...,a_{l-1+pk-1},a_{l-1+pk},a_{r+1},...,a_{n} $ .

Inversion if a pair of elements (not necessary neighbouring) with the wrong relative order. In other words, the number of inversion is equal to the number of pairs $ (i,j) $ such that $ i&lt;j $ and $ a_{i}&gt;a_{j} $ . Find the expected number of inversions after we apply exactly one operation mentioned above.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=100000 $ ) — the length of the permutation.

The second line contains $ n $ distinct integers from $ 1 $ to $ n $ — elements of the permutation.

## 输出格式

Print one real value — the expected number of inversions. Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-9} $ .

Namely: let's assume that your answer is $ a $ , and the answer of the jury is $ b $ . The checker program will consider your answer correct, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF749E/d8d110e69d298146d951837cc2710d1c4cc74a7d.png).

## 样例 #1

### 输入

```
3
2 3 1

```

### 输出

```
1.916666666666666666666666666667

```



---

---
title: "Expected diameter of a tree"
layout: "post"
diff: 省选/NOI-
pid: CF804D
tag: ['树的直径', '前缀和', '期望']
---

# Expected diameter of a tree

## 题目描述

Pasha is a good student and one of MoJaK's best friends. He always have a problem to think about. Today they had a talk about the following problem.

We have a forest (acyclic undirected graph) with $ n $ vertices and $ m $ edges. There are $ q $ queries we should answer. In each query two vertices $ v $ and $ u $ are given. Let $ V $ be the set of vertices in the connected component of the graph that contains $ v $ , and $ U $ be the set of vertices in the connected component of the graph that contains $ u $ . Let's add an edge between some vertex ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/8ef01bdc02f37e886781700f62479c92154da008.png) and some vertex in ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/0479fe8afb5e9211cdac4c2d711ca0b8e2ad6e82.png) and compute the value $ d $ of the resulting component. If the resulting component is a tree, the value $ d $ is the diameter of the component, and it is equal to -1 otherwise. What is the expected value of $ d $ , if we choose vertices $ a $ and $ b $ from the sets uniformly at random?

Can you help Pasha to solve this problem?

The diameter of the component is the maximum distance among some pair of vertices in the component. The distance between two vertices is the minimum number of edges on some path between the two vertices.

Note that queries don't add edges to the initial forest.

## 输入格式

The first line contains three integers $ n $ , $ m $ and $ q $ ( $ 1<=n,m,q<=10^{5} $ ) — the number of vertices, the number of edges in the graph and the number of queries.

Each of the next $ m $ lines contains two integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ), that means there is an edge between vertices $ u_{i} $ and $ v_{i} $ .

It is guaranteed that the given graph is a forest.

Each of the next $ q $ lines contains two integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ) — the vertices given in the $ i $ -th query.

## 输出格式

For each query print the expected value of $ d $ as described in the problem statement.

Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ . Let's assume that your answer is $ a $ , and the jury's answer is $ b $ . The checker program will consider your answer correct, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/259203790d90e969d73ec841bd0673c1e8e7d69a.png).

## 说明/提示

In the first example the vertices $ 1 $ and $ 3 $ are in the same component, so the answer for the first query is -1. For the second query there are two options to add the edge: one option is to add the edge $ 1-2 $ , the other one is $ 2-3 $ . In both ways the resulting diameter is $ 2 $ , so the answer is $ 2 $ .

In the second example the answer for the first query is obviously -1. The answer for the second query is the average of three cases: for added edges $ 1-2 $ or $ 1-3 $ the diameter is $ 3 $ , and for added edge $ 1-4 $ the diameter is $ 2 $ . Thus, the answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/80f05d9f9a5abbad800eeb11e2f309500aaccabe.png).

## 样例 #1

### 输入

```
3 1 2
1 3
3 1
2 3

```

### 输出

```
-1
2.0000000000

```

## 样例 #2

### 输入

```
5 2 3
2 4
4 3
4 2
4 1
2 5

```

### 输出

```
-1
2.6666666667
2.6666666667

```



---

---
title: "Gotta Go Fast"
layout: "post"
diff: 省选/NOI-
pid: CF865C
tag: ['动态规划 DP', '二分', '期望']
---

# Gotta Go Fast

## 题目描述

You're trying to set the record on your favorite video game. The game consists of $ N $ levels, which must be completed sequentially in order to beat the game. You usually complete each level as fast as possible, but sometimes finish a level slower. Specifically, you will complete the $ i $ -th level in either $ F_{i} $ seconds or $ S_{i} $ seconds, where $ F_{i}&lt;S_{i} $ , and there's a $ P_{i} $ percent chance of completing it in $ F_{i} $ seconds. After completing a level, you may decide to either continue the game and play the next level, or reset the game and start again from the first level. Both the decision and the action are instant.

Your goal is to complete all the levels sequentially in at most $ R $ total seconds. You want to minimize the expected amount of time playing before achieving that goal. If you continue and reset optimally, how much total time can you expect to spend playing?

## 输入格式

The first line of input contains integers $ N $ and $ R $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF865C/2edb953537ce7c8db1b280cf3e041068762c4830.png), the number of levels and number of seconds you want to complete the game in, respectively. $ N $ lines follow. The $ i $ th such line contains integers $ F_{i},S_{i},P_{i} $ $ (1<=F_{i}&lt;S_{i}<=100,80<=P_{i}<=99) $ , the fast time for level $ i $ , the slow time for level $ i $ , and the probability (as a percentage) of completing level $ i $ with the fast time.

## 输出格式

Print the total expected time. Your answer must be correct within an absolute or relative error of $ 10^{-9} $ .

Formally, let your answer be $ a $ , and the jury's answer be $ b $ . Your answer will be considered correct, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF865C/cde5c1e0715ef65086b3065853dd22ee5a37eede.png).

## 说明/提示

In the first example, you never need to reset. There's an $ 81% $ chance of completing the level in $ 2 $ seconds and a $ 19% $ chance of needing $ 8 $ seconds, both of which are within the goal time. The expected time is $ 0.81·2+0.19·8=3.14 $ .

In the second example, you should reset after the first level if you complete it slowly. On average it will take $ 0.25 $ slow attempts before your first fast attempt. Then it doesn't matter whether you complete the second level fast or slow. The expected time is $ 0.25·30+20+0.85·3+0.15·9=31.4 $ .

## 样例 #1

### 输入

```
1 8
2 8 81

```

### 输出

```
3.14

```

## 样例 #2

### 输入

```
2 30
20 30 80
3 9 85

```

### 输出

```
31.4

```

## 样例 #3

### 输入

```
4 319
63 79 89
79 97 91
75 87 88
75 90 83

```

### 输出

```
314.159265358

```



---

---
title: "New Year and Arbitrary Arrangement"
layout: "post"
diff: 省选/NOI-
pid: CF908D
tag: ['动态规划 DP', '期望', '逆元']
---

# New Year and Arbitrary Arrangement

## 题目描述

You are given three integers $ k $ , $ p_{a} $ and $ p_{b} $ .

You will construct a sequence with the following algorithm: Initially, start with the empty sequence. Each second, you do the following. With probability $ p_{a}/(p_{a}+p_{b}) $ , add 'a' to the end of the sequence. Otherwise (with probability $ p_{b}/(p_{a}+p_{b}) $ ), add 'b' to the end of the sequence.

You stop once there are at least $ k $ subsequences that form 'ab'. Determine the expected number of times 'ab' is a subsequence in the resulting sequence. It can be shown that this can be represented by $ P/Q $ , where $ P $ and $ Q $ are coprime integers, and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF908D/250bff4a0d2d6149565f6e795de0dbd59e6a92a3.png). Print the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF908D/962b3e429ab173c8d460f96cc849d01fcd4a9d47.png).

## 输入格式

The first line will contain three integers integer $ k,p_{a},p_{b} $ ( $ 1<=k<=1000 $ , $ 1<=p_{a},p_{b}<=1000000 $ ).

## 输出格式

Print a single integer, the answer to the problem.

## 说明/提示

The first sample, we will keep appending to our sequence until we get the subsequence 'ab' at least once. For instance, we get the sequence 'ab' with probability 1/4, 'bbab' with probability 1/16, and 'aab' with probability 1/8. Note, it's impossible for us to end with a sequence like 'aabab', since we would have stopped our algorithm once we had the prefix 'aab'.

The expected amount of times that 'ab' will occur across all valid sequences is 2.

For the second sample, the answer is equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF908D/be8bc2d2b5b20d19237dcaabfc3c3ca4bcb22ac0.png).

## 样例 #1

### 输入

```
1 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3 1 4

```

### 输出

```
370000006

```



---

---
title: "Santa's Gift"
layout: "post"
diff: 省选/NOI-
pid: CF960H
tag: ['线段树', '树链剖分', '期望']
---

# Santa's Gift

## 题目描述

Santa has an infinite number of candies for each of $ m $ flavours. You are given a rooted tree with $ n $ vertices. The root of the tree is the vertex $ 1 $ . Each vertex contains exactly one candy. The $ i $ -th vertex has a candy of flavour $ f_i $ .

Sometimes Santa fears that candies of flavour $ k $ have melted. He chooses any vertex $ x $ randomly and sends the subtree of $ x $ to the Bakers for a replacement. In a replacement, all the candies with flavour $ k $ are replaced with a new candy of the same flavour. The candies which are not of flavour $ k $ are left unchanged. After the replacement, the tree is restored.

The actual cost of replacing one candy of flavour $ k $ is $ c_k $ (given for each $ k $ ). The Baker keeps the price fixed in order to make calculation simple. Every time when a subtree comes for a replacement, the Baker charges $ C $ , no matter which subtree it is and which flavour it is.

Suppose that for a given flavour $ k $ the probability that Santa chooses a vertex for replacement is same for all the vertices. You need to find out the expected value of error in calculating the cost of replacement of flavour $ k $ . The error in calculating the cost is defined as follows.

 $ $$$ Error\ E(k) =\ (Actual Cost\ –\ Price\ charged\ by\ the\ Bakers) ^ 2. $ $ </p><p>Note that the actual cost is the cost of replacement of one candy of the flavour  $ k $  multiplied by the number of candies in the subtree.</p><p>Also, sometimes Santa may wish to replace a candy at vertex  $ x $  with a candy of some flavour from his pocket.</p><p>You need to handle two types of operations: </p><ul> <li> Change the flavour of the candy at vertex  $ x $  to  $ w $ . </li><li> Calculate the expected value of error in calculating the cost of replacement for a given flavour  $ k$$$.

## 输入格式

The first line of the input contains four integers $ n $ ( $ 2 \leqslant n \leqslant 5 \cdot 10^4 $ ), $ m $ , $ q $ , $ C $ ( $ 1 \leqslant m, q \leqslant 5 \cdot 10^4 $ , $ 0 \leqslant C \leqslant 10^6 $ ) — the number of nodes, total number of different flavours of candies, the number of queries and the price charged by the Bakers for replacement, respectively.

The second line contains $ n $ integers $ f_1, f_2, \dots, f_n $ ( $ 1 \leqslant f_i \leqslant m $ ), where $ f_i $ is the initial flavour of the candy in the $ i $ -th node.

The third line contains $ n - 1 $ integers $ p_2, p_3, \dots, p_n $ ( $ 1 \leqslant p_i \leqslant n $ ), where $ p_i $ is the parent of the $ i $ -th node.

The next line contains $ m $ integers $ c_1, c_2, \dots c_m $ ( $ 1 \leqslant c_i \leqslant 10^2 $ ), where $ c_i $ is the cost of replacing one candy of flavour $ i $ .

The next $ q $ lines describe the queries. Each line starts with an integer $ t $ ( $ 1 \leqslant t \leqslant 2 $ ) — the type of the query.

If $ t = 1 $ , then the line describes a query of the first type. Two integers $ x $ and $ w $ follow ( $ 1 \leqslant  x \leqslant  n $ , $ 1 \leqslant  w \leqslant m $ ), it means that Santa replaces the candy at vertex $ x $ with flavour $ w $ .

Otherwise, if $ t = 2 $ , the line describes a query of the second type and an integer $ k $ ( $ 1 \leqslant k \leqslant m $ ) follows, it means that you should print the expected value of the error in calculating the cost of replacement for a given flavour $ k $ .

The vertices are indexed from $ 1 $ to $ n $ . Vertex $ 1 $ is the root.

## 输出格式

Output the answer to each query of the second type in a separate line.

Your answer is considered correct if its absolute or relative error does not exceed $ 10^{-6} $ .

Formally, let your answer be $ a $ , and the jury's answer be $ b $ . The checker program considers your answer correct if and only if $ \frac{|a-b|}{max(1,b)}\leqslant 10^{-6} $ .

## 说明/提示

For $ 1 $ -st query, the error in calculating the cost of replacement for flavour $ 1 $ if vertex $ 1 $ , $ 2 $ or $ 3 $ is chosen are $ 66^2 $ , $ 66^2 $ and $ (-7)^2 $ respectively. Since the probability of choosing any vertex is same, therefore the expected value of error is $ \frac{66^2+66^2+(-7)^2}{3} $ .

Similarly, for $ 2 $ -nd query the expected value of error is $ \frac{41^2+(-7)^2+(-7)^2}{3} $ .

After $ 3 $ -rd query, the flavour at vertex $ 2 $ changes from $ 1 $ to $ 3 $ .

For $ 4 $ -th query, the expected value of error is $ \frac{(-7)^2+(-7)^2+(-7)^2}{3} $ .

Similarly, for $ 5 $ -th query, the expected value of error is $ \frac{89^2+41^2+(-7)^2}{3} $ .

## 样例 #1

### 输入

```
3 5 5 7
3 1 4
1 1
73 1 48 85 89
2 1
2 3
1 2 3
2 1
2 3

```

### 输出

```
2920.333333333333
593.000000000000
49.000000000000
3217.000000000000

```



---

