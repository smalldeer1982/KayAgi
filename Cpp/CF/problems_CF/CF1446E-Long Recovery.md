---
title: "Long Recovery"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1446E
tag: []
---

# Long Recovery

## 题目描述

A patient has been infected with an unknown disease. His body can be seen as an infinite grid of triangular cells which looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1446E/9c898646773ed79dd57a73be638a89ee9bb75744.png)Two cells are neighboring if they share a side. Therefore, each cell ( $ x $ , $ y $ ) has exactly three neighbors:

- ( $ x+1 $ , $ y $ )
- ( $ x-1 $ , $ y $ )
- ( $ x+1 $ , $ y-1 $ ) if $ x $ is even and ( $ x-1 $ , $ y+1 $ ) otherwise.

Initially some cells are infected, all the others are healthy. The process of recovery begins. Each second, for exactly one cell (even though there might be multiple cells that could change its state) one of the following happens:

- A healthy cell with at least $ 2 $ infected neighbors also becomes infected.
- An infected cell with at least $ 2 $ healthy neighbors also becomes healthy.

If no such cell exists, the process of recovery stops. Patient is considered recovered if the process of recovery has stopped and all the cells are healthy.

We're interested in a worst-case scenario: is it possible that the patient never recovers, or if it's not possible, what is the maximum possible duration of the recovery process?

## 输入格式

The first line contains one integer $ n $ $ (1 \leq n \leq 250000) $ — the number of infected cells.

The $ i $ -th of the next $ n $ lines contains two space-separated integers $ x_i $ and $ y_i $ $ (0 \leq x_i, y_i < 500) $ , meaning that cell $ (x_i, y_i) $ is infected. All cells $ (x_i, y_i) $ are distinct, and all other cells are considered healthy.

## 输出格式

If it is possible that the organism never fully recovers from the disease, print SICK. Otherwise, you should print RECOVERED and in the next line an integer $ k $ — the longest possible recovery period, modulo $ 998244353 $ .

## 说明/提示

For the first testcase, the following drawings describe the longest possible recovery process. It can be proven that there are no recovery periods of length $ 5 $ or longer, and the organism always recovers in this testcase.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1446E/71aee1454e792835e0fca5a5d1e66c7a30fa9432.png) $ \hspace{40pt} \downarrow $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1446E/06082fafadaa041becb082b7b3a4221204efb3ce.png) $ \hspace{40pt} \downarrow $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1446E/1882a0e38bbc4eca78c2e20b9510c634073b598d.png) $ \hspace{40pt} \downarrow $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1446E/33016576a53fffce956bbfa80492e3695fae491a.png) $ \hspace{40pt} \downarrow $

 $ \hspace{15pt} $ RECOVERED

For the second testcase, it is possible for the cells $ (2, 0) $ , $ (2, 1) $ , $ (0, 1) $ to become infected. After that, no cell can change its state, so the answer is SICK, as not all of the cells are healthy.

## 样例 #1

### 输入

```
4
0 0
1 0
2 0
0 1
```

### 输出

```
RECOVERED
4
```

## 样例 #2

### 输入

```
3
1 0
3 0
1 1
```

### 输出

```
SICK
```

