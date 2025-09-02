---
title: "The Tree"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1017G
tag: ['动态树 LCT']
---

# The Tree

## 题目描述

Abendsen assigned a mission to Juliana. In this mission, Juliana has a rooted tree with $ n $ vertices. Vertex number $ 1 $ is the root of this tree. Each vertex can be either black or white. At first, all vertices are white. Juliana is asked to process $ q $ queries. Each query is one of three types:

1. If vertex $ v $ is white, mark it as black; otherwise, perform this operation on all direct sons of $ v $ instead.
2. Mark all vertices in the subtree of $ v $ (including $ v $ ) as white.
3. Find the color of the $ i $ -th vertex.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017G/e1bfda7a1b03fca247e99f6625980764a1349b36.png)An example of operation "1 1" (corresponds to the first example test). The vertices $ 1 $ and $ 2 $ are already black, so the operation goes to their sons instead.Can you help Juliana to process all these queries?

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 2\leq n\leq 10^5 $ , $ 1\leq q\leq 10^5 $ ) — the number of vertices and the number of queries.

The second line contains $ n-1 $ integers $ p_2, p_3, \ldots, p_n $ ( $ 1\leq p_i<i $ ), where $ p_i $ means that there is an edge between vertices $ i $ and $ p_i $ .

Each of the next $ q $ lines contains two integers $ t_i $ and $ v_i $ ( $ 1\leq t_i\leq 3 $ , $ 1\leq v_i\leq n $ ) — the type of the $ i $ -th query and the vertex of the $ i $ -th query.

It is guaranteed that the given graph is a tree.

## 输出格式

For each query of type $ 3 $ , print "black" if the vertex is black; otherwise, print "white".

## 说明/提示

The first example is shown on the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017G/cc16931f19a766fcc45c465ac34ccd83cbd711fb.png)The second example is shown on the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017G/f4ed5ffcf5834fcc15d2af9cfb118e0f9239a3e6.png)

## 样例 #1

### 输入

```
8 10
1 2 1 2 5 4 5
1 2
3 2
3 1
1 1
1 1
3 5
3 7
3 4
2 2
3 5

```

### 输出

```
black
white
black
white
black
white

```

## 样例 #2

### 输入

```
8 11
1 1 2 3 3 6 6
1 1
1 1
1 3
3 2
3 4
3 6
3 7
2 3
1 6
3 7
3 6

```

### 输出

```
black
white
black
white
white
black

```



---

---
title: "Sasha and Algorithm of Silence's Sounds"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1109F
tag: ['动态树 LCT']
---

# Sasha and Algorithm of Silence's Sounds

## 题目描述

One fine day Sasha went to the park for a walk. In the park, he saw that his favorite bench is occupied, and he had to sit down on the neighboring one. He sat down and began to listen to the silence. Suddenly, he got a question: what if in different parts of the park, the silence sounds in different ways? So it was. Let's divide the park into $ 1 \times 1 $ meter squares and call them cells, and numerate rows from $ 1 $ to $ n $ from up to down, and columns from $ 1 $ to $ m $ from left to right. And now, every cell can be described with a pair of two integers $ (x, y) $ , where $ x $ — the number of the row, and $ y $ — the number of the column. Sasha knows that the level of silence in the cell $ (i, j) $ equals to $ f_{i,j} $ , and all $ f_{i,j} $ form a permutation of numbers from $ 1 $ to $ n \cdot m $ . Sasha decided to count, how many are there pleasant segments of silence?

Let's take some segment $ [l \ldots r] $ . Denote $ S $ as the set of cells $ (i, j) $ that $ l \le f_{i,j} \le r $ . Then, the segment of silence $ [l \ldots r] $ is pleasant if there is only one simple path between every pair of cells from $ S $ (path can't contain cells, which are not in $ S $ ). In other words, set $ S $ should look like a tree on a plain. Sasha has done this task pretty quickly, and called the algorithm — "algorithm of silence's sounds".

Time passed, and the only thing left from the algorithm is a legend. To prove the truthfulness of this story, you have to help Sasha and to find the number of different pleasant segments of silence. Two segments $ [l_1 \ldots r_1] $ , $ [l_2 \ldots r_2] $ are different, if $ l_1 \neq l_2 $ or $ r_1 \neq r_2 $ or both at the same time.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 1000 $ , $ 1 \le n \cdot m \le 2 \cdot 10^5 $ ) — the size of the park.

Each from next $ n $ lines contains $ m $ integers $ f_{i,j} $ ( $ 1 \le f_{i,j} \le n \cdot m $ ) — the level of silence in the cell with number $ (i, j) $ .

It is guaranteed, that all $ f_{i,j} $ are different.

## 输出格式

Print one integer — the number of pleasant segments of silence.

## 说明/提示

In the first example, all segments of silence are pleasant.

In the second example, pleasant segments of silence are the following:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1109F/05bdf79fe44d303126c6f8f19b3d48a216188486.png)

## 样例 #1

### 输入

```
1 5
1 2 3 4 5

```

### 输出

```
15
```

## 样例 #2

### 输入

```
2 3
1 2 3
4 5 6

```

### 输出

```
15
```

## 样例 #3

### 输入

```
4 4
4 3 2 16
1 13 14 15
5 7 8 12
6 11 9 10

```

### 输出

```
50
```



---

