---
title: "Rap God"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF786D
tag: []
---

# Rap God

## 题目描述

Rick is in love with Unity. But Mr. Meeseeks also love Unity, so Rick and Mr. Meeseeks are "love rivals".

Unity loves rap, so it decided that they have to compete in a rap game (battle) in order to choose the best. Rick is too nerds, so instead he's gonna make his verse with running his original algorithm on lyrics "Rap God" song.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF786D/0c3909af1e63fd9a5fef7f69a57533a5eed83b16.png)His algorithm is a little bit complicated. He's made a tree with $ n $ vertices numbered from $ 1 $ to $ n $ and there's a lowercase english letter written on each edge. He denotes $ str(a,b) $ to be the string made by writing characters on edges on the shortest path from $ a $ to $ b $ one by one (a string of length equal to distance of $ a $ to $ b $ ). Note that $ str(a,b) $ is reverse of $ str(b,a) $ and $ str(a,a) $ is empty.

 In order to make the best verse he can, he needs to answer some queries, but he's not a computer scientist and is not able to answer those queries, so he asked you to help him. Each query is characterized by two vertices $ x $ and $ y $ ( $ x≠y $ ). Answer to this query is the number of vertices like $ z $ such that $ z≠x,z≠y $ and $ str(x,y) $ is lexicographically larger than $ str(x,z) $ .

String $ x=x_{1}x_{2}...x_{|x|} $ is lexicographically larger than string $ y=y_{1}y_{2}...y_{|y|} $ , if either $ |x|&gt;|y| $ and $ x_{1}=y_{1},x_{2}=y_{2},...,x_{|y|}=y_{|y|} $ , or exists such number $ r\ (r&lt;|x|,r&lt;|y|) $ , that $ x_{1}=y_{1},x_{2}=y_{2},...,x_{r}=y_{r} $ and $ x_{r+1}&gt;y_{r+1} $ . Characters are compared like their ASCII codes (or alphabetic order).

Help Rick get the girl (or whatever gender Unity has).

## 输入格式

The first line of input contain two integers $ n $ and $ q $ ( $ 2<=n<=20000 $ , $ 1<=q<=20000 $ ) — number of vertices in tree and number of queries respectively.

The next $ n-1 $ lines contain the edges. Each line contains two integers $ v $ and $ u $ (endpoints of the edge) followed by an English lowercase letter $ c $ ( $ 1<=v,u<=n,v≠u $ ).

The next $ q $ line contain the queries. Each line contains two integers $ x $ and $ y $ ( $ 1<=x,y<=n,x≠y $ ).

## 输出格式

Print the answer for each query in one line.

## 说明/提示

Here's the tree of first sample testcase:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF786D/556c830929878cf9348a46db315ed84746cb25cb.png)Here's the tree of second sample testcase:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF786D/19caf00086caad61e82461e99aecc961350a281b.png)In this test:

- $ str(8,1) $ = poo
- $ str(8,2) $ = poe
- $ str(8,3) $ = po
- $ str(8,4) $ = pop
- $ str(8,5) $ = popd
- $ str(8,6) $ = popp
- $ str(8,7) $ = p

So, for the first query, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF786D/6ae458c12a452f36bda90be4a422e1282ce31513.png) and for the third query ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF786D/756a55dbbfcf01cb4ad242f78607666c9100bf6f.png) is the answer.

## 样例 #1

### 输入

```
4 3
4 1 t
3 2 p
1 2 s
3 2
1 3
2 1

```

### 输出

```
0
1
1

```

## 样例 #2

### 输入

```
8 4
4 6 p
3 7 o
7 8 p
4 5 d
1 3 o
4 3 p
3 2 e
8 6
3 7
8 1
4 3

```

### 输出

```
6
1
3
1

```

