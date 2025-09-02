---
title: "Disks"
layout: "post"
diff: 提高+/省选-
pid: CF1949I
tag: ['二分图']
---

# Disks

## 题目描述

# 圆盘


你在平面上有 $ n $ 个圆盘。每个圆盘的中心具有整数坐标，每个圆盘的半径为正整数。没有两个圆盘在一个正面积的区域重叠，但圆盘之间可能相切。

你的任务是确定是否可以改变圆盘的半径，使得：

- 原来相切的圆盘仍然相切。
- 没有两个圆盘在一个正面积的区域重叠。
- 所有半径的总和严格减小。

新的半径可以是任意正实数。不能改变圆盘的中心。

## 输入格式

第一行包含一个整数 $ n $ （ $ 1\le n \le 1000 $ ）— 圆盘的数量。

接下来的 $ n $ 行，每行包含三个整数。第 $ i $ 行包含 $ x_i $ ， $ y_i $ （ $ -10^9 \leq x_i, y_i \le 10^9 $ ），以及 $ r_i $ （ $ 1 \leq r_i \le 10^9 $ ）— 第 $ i $ 个圆盘的中心坐标和半径。

## 输出格式

如果可以按照要求改变半径，则打印 $ \texttt{YES} $ 。否则，打印 $ \texttt{NO} $ 。

## 样例 #1

### 样例输入 #1

```
5
0 2 1
0 0 1
4 -3 4
11 0 3
11 5 2
```

### 样例输出 #1

```
YES
```

## 样例 #2

### 样例输入 #2

```
4
2 2 2
7 2 3
7 7 2
2 7 3
```

### 样例输出 #2

```
NO
```

## 说明/提示

在第一个样例中，可以将第一个和第三个圆盘的半径减小 $ 0.5 $ ，将第二个圆盘的半径增加 $ 0.5 $ 。这样，所有半径的总和减小了 $ 0.5 $ 。改变半径前后的情况如下图所示。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1949I/1f564e55d56b152b57e25e4b9913f6abfe12e4f8.png) 第一个样例（左）和改变圆盘半径的有效方法（右）。在第二个样例中，如下图所示，无法按照要求改变圆盘的半径。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1949I/160a9b50ca0114a94aa27312025cf229be0abcc8.png) 第二个样例。

## 样例 #1

### 输入

```
5
0 2 1
0 0 1
4 -3 4
11 0 3
11 5 2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
2 2 2
7 2 3
7 7 2
2 7 3
```

### 输出

```
NO
```



---

---
title: "Coloring Game"
layout: "post"
diff: 提高+/省选-
pid: CF1991E
tag: ['二分图']
---

# Coloring Game

## 题目描述

This is an interactive problem.

Consider an undirected connected graph consisting of $ n $ vertices and $ m $ edges. Each vertex can be colored with one of three colors: $ 1 $ , $ 2 $ , or $ 3 $ . Initially, all vertices are uncolored.

Alice and Bob are playing a game consisting of $ n $ rounds. In each round, the following two-step process happens:

1. Alice chooses two different colors.
2. Bob chooses an uncolored vertex and colors it with one of the two colors chosen by Alice.

Alice wins if there exists an edge connecting two vertices of the same color. Otherwise, Bob wins.

You are given the graph. Your task is to decide which player you wish to play as and win the game.

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains two integers $ n $ , $ m $ ( $ 1 \le n \le 10^4 $ , $ n - 1 \le m \le \min(\frac{n \cdot (n - 1)}{2}, 10^4) $ ) — the number of vertices and the number of edges in the graph, respectively.

Each of the next $ m $ lines of each test case contains two integers $ u_i $ , $ v_i $ ( $ 1 \le u_i, v_i \le n $ ) — the edges of the graph. It is guaranteed that the graph is connected and there are no multiple edges or self-loops.

It is guaranteed that the sum of $ n $ and the sum of $ m $ over all test cases does not exceed $ 10^4 $ .

## 输出格式

For each test case, you need to output a single line containing either "Alice" or "Bob", representing the player you choose.

Then for each of the following $ n $ rounds, the following two-step process happens:

1. Alice (either you or the interactor) will output two integers $ a $ and $ b $ ( $ 1 \le a, b \le 3 $ , $ a \neq b $ ) — the colors chosen by Alice.
2. Bob (either you or the interactor) will output two integers $ i $ and $ c $ ( $ 1 \le i \le n $ , $ c = a $ or $ c = b $ ) — the vertex and the color chosen by Bob. Vertex $ i $ must be a previously uncolored vertex.

If any of your outputs are invalid, the jury will output "-1" and you will receive a Wrong Answer verdict.

At the end of all $ n $ turns, if you have lost the game, the jury will output "-1" and you will receive a Wrong Answer verdict.

If your program has received a $ -1 $ instead of a valid value, it must terminate immediately. Otherwise, you may receive an arbitrary verdict because your solution might be reading from a closed stream.

Note that if you are playing as Alice, and there already exists an edge connected two vertices of the same color, the interactor will not terminate early and you will keep playing all $ n $ rounds.

After outputting, do not forget to output end of line and flush the output. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see documentation for other languages.

In this problem, hacks are disabled.

## 说明/提示

Note that the sample test cases are example games and do not necessarily represent the optimal strategy for both players.

In the first test case, you choose to play as Alice.

1. Alice chooses two colors: $ 3 $ and $ 1 $ . Bob chooses vertex $ 3 $ and colors it with color $ 1 $ .
2. Alice chooses two colors: $ 1 $ and $ 2 $ . Bob chooses vertex $ 2 $ and colors it with color $ 2 $ .
3. Alice chooses two colors: $ 2 $ and $ 1 $ . Bob chooses vertex $ 1 $ and colors it with color $ 1 $ .

Alice wins because the edge $ (3, 1) $ connects two vertices of the same color.

In the second test case, you choose to play as Bob.

1. Alice chooses two colors: $ 2 $ and $ 3 $ . Bob chooses vertex $ 1 $ and colors it with color $ 2 $ .
2. Alice chooses two colors: $ 1 $ and $ 2 $ . Bob chooses vertex $ 2 $ and colors it with color $ 1 $ .
3. Alice chooses two colors: $ 2 $ and $ 1 $ . Bob chooses vertex $ 4 $ and colors it with color $ 1 $ .
4. Alice chooses two colors: $ 3 $ and $ 1 $ . Bob chooses vertex $ 3 $ and colors it with color $ 3 $ .

Bob wins because there are no edges with vertices of the same color.

## 样例 #1

### 输入

```
2
3 3
1 2
2 3
3 1


3 1

2 2

1 1
4 4
1 2
2 3
3 4
4 1

2 3

1 2

2 1

3 1
```

### 输出

```
Alice
3 1

1 2

2 1






Bob

1 2

2 1

4 1

3 3
```



---

---
title: "Fairy"
layout: "post"
diff: 提高+/省选-
pid: CF19E
tag: ['二分图', '最近公共祖先 LCA', '差分']
---

# Fairy

## 题目描述

Once upon a time there lived a good fairy A. One day a fine young man B came to her and asked to predict his future. The fairy looked into her magic ball and said that soon the fine young man will meet the most beautiful princess ever and will marry her. Then she drew on a sheet of paper $ n $ points and joined some of them with segments, each of the segments starts in some point and ends in some other point. Having drawn that picture, she asked the young man to erase one of the segments from the sheet. Then she tries to colour each point red or blue so, that there is no segment having points of the same colour as its ends. If she manages to do so, the prediction will come true. B wants to meet the most beautiful princess, that's why he asks you to help him. Find all the segments that will help him to meet the princess.

## 输入格式

The first input line contains two integer numbers: $ n $ — amount of the drawn points and $ m $ — amount of the drawn segments ( $ 1<=n<=10^{4},0<=m<=10^{4} $ ). The following $ m $ lines contain the descriptions of the segments. Each description contains two different space-separated integer numbers $ v $ , $ u $ ( $ 1<=v<=n,1<=u<=n $ ) — indexes of the points, joined by this segment. No segment is met in the description twice.

## 输出格式

In the first line output number $ k $ — amount of the segments in the answer. In the second line output $ k $ space-separated numbers — indexes of these segments in ascending order. Each index should be output only once. Segments are numbered from 1 in the input order.

## 样例 #1

### 输入

```
4 4
1 2
1 3
2 4
3 4

```

### 输出

```
4
1 2 3 4 
```

## 样例 #2

### 输入

```
4 5
1 2
2 3
3 4
4 1
1 3

```

### 输出

```
1
5 
```



---

---
title: "Best Subsequence"
layout: "post"
diff: 提高+/省选-
pid: CF2026E
tag: ['网络流', '二分图']
---

# Best Subsequence

## 题目描述

Given an integer array $ a $ of size $ n $ .

Let's define the value of the array as its size minus the number of set bits in the bitwise OR of all elements of the array.

For example, for the array $ [1, 0, 1, 2] $ , the bitwise OR is $ 3 $ (which contains $ 2 $ set bits), and the value of the array is $ 4-2=2 $ .

Your task is to calculate the maximum possible value of some subsequence of the given array.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 100 $ ).

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i < 2^{60} $ ).

## 输出格式

For each test case, print the maximum possible value of some subsequence of the given array.

## 样例 #1

### 输入

```
4
3
0 0 0
4
1 0 1 2
1
5
8
7 1 48 14 13 8 7 6
```

### 输出

```
3
2
0
3
```



---

---
title: "George and Interesting Graph"
layout: "post"
diff: 提高+/省选-
pid: CF387D
tag: ['网络流', '二分图']
---

# George and Interesting Graph

## 题目描述

- 没有重边；
- 存在结点 $v$（称为中心），使得对于图中的任意结点 $u$，都有边 $(u,v)$ 和 $(v,u)$，注意自环 $(v,v)$ 也应该存在；
- 除去中心外，每个点的入度和出度都恰好为 $2$； 

显然很少有图有趣，但 George 可以把图变得有趣：每次他可以增加一条边或者删除一条已经存在的边。

现在给出图 $G$，George 想知道他最少做多少次操作可以使它变得有趣。

## 输出格式

Translated by @Harry_bh

## 样例 #1

### 输入

```
3 7
1 1
2 2
3 1
1 3
3 2
2 3
3 3

```

### 输出

```
0

```

## 样例 #2

### 输入

```
3 6
1 1
2 2
3 1
3 2
2 3
3 3

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3 1
2 2

```

### 输出

```
6

```



---

---
title: "Love Triangles"
layout: "post"
diff: 提高+/省选-
pid: CF553C
tag: ['二分图']
---

# Love Triangles

## 题目描述

There are many anime that are about "love triangles": Alice loves Bob, and Charlie loves Bob as well, but Alice hates Charlie. You are thinking about an anime which has $ n $ characters. The characters are labeled from $ 1 $ to $ n $ . Every pair of two characters can either mutually love each other or mutually hate each other (there is no neutral state).

You hate love triangles (A-B are in love and B-C are in love, but A-C hate each other), and you also hate it when nobody is in love. So, considering any three characters, you will be happy if exactly one pair is in love (A and B love each other, and C hates both A and B), or if all three pairs are in love (A loves B, B loves C, C loves A).

You are given a list of $ m $ known relationships in the anime. You know for sure that certain pairs love each other, and certain pairs hate each other. You're wondering how many ways you can fill in the remaining relationships so you are happy with every triangle. Two ways are considered different if two characters are in love in one way but hate each other in the other. Print this count modulo $ 1000000007 $ .

## 输入格式

The first line of input will contain two integers $ n,m $ ( $ 3<=n<=100000 $ , $ 0<=m<=100000 $ ).

The next $ m $ lines will contain the description of the known relationships. The $ i $ -th line will contain three integers $ a_{i},b_{i},c_{i} $ . If $ c_{i} $ is 1, then $ a_{i} $ and $ b_{i} $ are in love, otherwise, they hate each other ( $ 1<=a_{i},b_{i}<=n $ , $ a_{i}≠b_{i} $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF553C/26e54e6b3b9751cc71b106d519c04019ef62f5b4.png)).

Each pair of people will be described no more than once.

## 输出格式

Print a single integer equal to the number of ways to fill in the remaining pairs so that you are happy with every triangle modulo $ 1000000007 $ .

## 说明/提示

In the first sample, the four ways are to:

- Make everyone love each other
- Make 1 and 2 love each other, and 3 hate 1 and 2 (symmetrically, we get 3 ways from this).

In the second sample, the only possible solution is to make 1 and 3 love each other and 2 and 4 hate each other.

## 样例 #1

### 输入

```
3 0

```

### 输出

```
4

```

## 样例 #2

### 输入

```
4 4
1 2 1
2 3 1
3 4 0
4 1 0

```

### 输出

```
1

```

## 样例 #3

### 输入

```
4 4
1 2 1
2 3 1
3 4 0
4 1 1

```

### 输出

```
0

```



---

