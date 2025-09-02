---
title: "Shrinking Tree"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1060F
tag: ['枚举']
---

# Shrinking Tree

## 题目描述

Consider a tree $ T $ (that is, a connected graph without cycles) with $ n $ vertices labelled $ 1 $ through $ n $ . We start the following process with $ T $ : while $ T $ has more than one vertex, do the following:

- choose a random edge of $ T $ equiprobably;
- shrink the chosen edge: if the edge was connecting vertices $ v $ and $ u $ , erase both $ v $ and $ u $ and create a new vertex adjacent to all vertices previously adjacent to either $ v $ or $ u $ . The new vertex is labelled either $ v $ or $ u $ equiprobably.

At the end of the process, $ T $ consists of a single vertex labelled with one of the numbers $ 1, \ldots, n $ . For each of the numbers, what is the probability of this number becoming the label of the final vertex?

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \leq n \leq 50 $ ).

The following $ n - 1 $ lines describe the tree edges. Each of these lines contains two integers $ u_i, v_i $ — labels of vertices connected by the respective edge ( $ 1 \leq u_i, v_i \leq n $ , $ u_i \neq v_i $ ). It is guaranteed that the given graph is a tree.

## 输出格式

Print $ n $ floating numbers — the desired probabilities for labels $ 1, \ldots, n $ respectively. All numbers should be correct up to $ 10^{-6} $ relative or absolute precision.

## 说明/提示

In the first sample, the resulting vertex has label 1 if and only if for all three edges the label 1 survives, hence the probability is $ 1/2^3 = 1/8 $ . All other labels have equal probability due to symmetry, hence each of them has probability $ (1 - 1/8) / 3 = 7/24 $ .

## 样例 #1

### 输入

```
4
1 2
1 3
1 4

```

### 输出

```
0.1250000000
0.2916666667
0.2916666667
0.2916666667

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
3 7

```

### 输出

```
0.0850694444
0.0664062500
0.0664062500
0.1955295139
0.1955295139
0.1955295139
0.1955295139

```



---

---
title: "Ciel and Flipboard"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF321D
tag: ['枚举']
---

# Ciel and Flipboard

## 题目描述

Fox Ciel has a board with $ n $ rows and $ n $ columns, there is one integer in each cell.

It's known that $ n $ is an odd number, so let's introduce ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF321D/6479833d305e8df8be298c6d130b2c56818252f6.png). Fox Ciel can do the following operation many times: she choose a sub-board with size $ x $ rows and $ x $ columns, then all numbers in it will be multiplied by -1.

Return the maximal sum of numbers in the board that she can get by these operations.

## 输入格式

The first line contains an integer $ n $ , ( $ 1<=n<=33 $ , and $ n $ is an odd integer) — the size of the board.

Each of the next $ n $ lines contains $ n $ integers — the numbers in the board. Each number doesn't exceed $ 1000 $ by its absolute value.

## 输出格式

Output a single integer: the maximal sum of numbers in the board that can be accomplished.

## 说明/提示

In the first test, we can apply this operation twice: first on the top left $ 2×2 $ sub-board, then on the bottom right $ 2×2 $ sub-board. Then all numbers will become positive.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF321D/bba86be06e5760920ea393fc6a496f40415e324b.png)

## 样例 #1

### 输入

```
3
-1 -1 1
-1 1 -1
1 -1 -1

```

### 输出

```
9

```

## 样例 #2

### 输入

```
5
-2 0 0 0 -2
0 -2 0 -2 0
0 0 -2 0 0
0 -2 0 -2 0
-2 0 0 0 -2

```

### 输出

```
18

```



---

---
title: "Matvey's Birthday"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF718E
tag: ['枚举', '最短路', '进制']
---

# Matvey's Birthday

## 题目描述

Today is Matvey's birthday. He never knows what to ask as a present so friends gave him a string $ s $ of length $ n $ . This string consists of only first eight English letters: 'a', 'b', $ ... $ , 'h'.

First question that comes to mind is: who might ever need some string? Matvey is a special boy so he instantly found what to do with this string. He used it to build an undirected graph where vertices correspond to position in the string and there is an edge between distinct positions $ a $ and $ b $ ( $ 1<=a,b<=n $ ) if at least one of the following conditions hold:

1. $ a $ and $ b $ are neighbouring, i.e. $ |a-b|=1 $ .
2. Positions $ a $ and $ b $ contain equal characters, i.e. $ s_{a}=s_{b} $ .

Then Matvey decided to find the diameter of this graph. Diameter is a maximum distance (length of the shortest path) among all pairs of vertices. Also, Matvey wants to find the number of pairs of vertices such that the distance between them is equal to the diameter of the graph. As he is very cool and experienced programmer he managed to solve this problem very fast. Will you do the same?

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 2<=n<=100000 $ ) — the length of the string.

The second line contains the string $ s $ itself. It's guaranteed that $ s $ consists of only first eight letters of English alphabet.

## 输出格式

Print two integers — the diameter of the graph and the number of pairs of positions with the distance equal to the diameter.

## 说明/提示

Consider the second sample.

The maximum distance is $ 2 $ . It's obtained for pairs $ (1,4) $ , $ (2,4) $ , $ (4,6) $ and $ (4,7) $ .

## 样例 #1

### 输入

```
3
abc

```

### 输出

```
2 1

```

## 样例 #2

### 输入

```
7
aaabaaa

```

### 输出

```
2 4

```



---

---
title: "New Year and Binary Tree Paths"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF750G
tag: ['动态规划 DP', '线段树', '枚举']
---

# New Year and Binary Tree Paths

## 题目描述

The New Year tree is an infinite perfect binary tree rooted in the node $ 1 $ . Each node $ v $ has two children: nodes indexed $ (2·v) $ and $ (2·v+1) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750G/5f3fba6843b56e8c74120fa68d53319463f26696.png)Polar bears love decorating the New Year tree and Limak is no exception. As he is only a little bear, he was told to decorate only one simple path between some pair of nodes. Though he was given an opportunity to pick the pair himself! Now he wants to know the number of unordered pairs of indices $ (u,v) $ ( $ u<=v $ ), such that the sum of indices of all nodes along the simple path between $ u $ and $ v $ (including endpoints) is equal to $ s $ . Can you help him and count this value?

## 输入格式

The only line of the input contains a single integer $ s $ ( $ 1<=s<=10^{15} $ ).

## 输出格式

Print one integer, denoting the number of unordered pairs of nodes indices defining simple paths with the sum of indices of vertices equal to $ s $ .

## 说明/提示

In sample test, there are $ 4 $ paths with the sum of indices equal to $ 10 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750G/c83b62a188e719702078b419fb6e934500dacd07.png)

## 样例 #1

### 输入

```
10

```

### 输出

```
4

```



---

---
title: "Rainbow Balls"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF850F
tag: ['动态规划 DP', '枚举', '期望', '标签458']
---

# Rainbow Balls

## 题目描述

You have a bag of balls of $ n $ different colors. You have $ a_{i} $ balls of the $ i $ -th color.

While there are at least two different colored balls in the bag, perform the following steps:

- Take out two random balls without replacement one by one. These balls might be the same color.
- Color the second ball to the color of the first ball. You are not allowed to switch the order of the balls in this step.
- Place both balls back in the bag.
- All these actions take exactly one second.

Let $ M=10^{9}+7 $ . It can be proven that the expected amount of time needed before you stop can be represented as a rational number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850F/2c40be71c60fe708ee9e4e80e2cd7a26163f3bd6.png), where $ P $ and $ Q $ are coprime integers and where $ Q $ is not divisible by $ M $ . Return the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850F/a816c54f8859ee12f4e38a2cc4dba0d6f8dd5c0b.png).

## 输入格式

The first line of input will contain a single integer $ n $ ( $ 1<=n<=2500 $ ) — the number of colors.

The next line of input will contain $ n $ space separated integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{5} $ ) — the number of balls of each color.

## 输出格式

Print a single integer, the answer to the problem.

## 说明/提示

In the first sample, no matter what happens, the balls will become the same color after one step.

For the second sample, we have 6 balls. Let’s label the balls from 1 to 6, and without loss of generality, let’s say balls 1,2,3 are initially color 1, balls 4,5 are color 2, and ball 6 are color 3.

Here is an example of how these steps can go:

- We choose ball 5 and ball 6. Ball 6 then becomes color 2.
- We choose ball 4 and ball 5. Ball 5 remains the same color (color 2).
- We choose ball 1 and ball 5. Ball 5 becomes color 1.
- We choose ball 6 and ball 5. Ball 5 becomes color 2.
- We choose ball 3 and ball 4. Ball 4 becomes color 1.
- We choose ball 4 and ball 6. Ball 6 becomes color 1.
- We choose ball 2 and ball 5. Ball 5 becomes color 1.

 At this point, the game ends since all the balls are the same color. This particular sequence took 7 seconds.It can be shown that the answer to this case is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850F/9f76609d2f8aa0999ab074d70f32e2692cee15a9.png).

## 样例 #1

### 输入

```
2
1 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
1 2 3

```

### 输出

```
750000026

```



---

