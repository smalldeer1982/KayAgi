---
title: "Spinach Pizza"
layout: "post"
diff: 省选/NOI-
pid: CF1776I
tag: []
---

# Spinach Pizza

## 题目描述

Alberto 和 Beatrice 两兄妹必须一起吃菠菜披萨。但是他们都不喜欢吃菠菜，所以都想尽量少吃。

披萨的形状是一个由 $n$ 个位于平面的整数坐标的顶点 $(x_1, y_1), \, (x_2, y_2), \, \dots, \, (x_n, y_n)$ 组成的严格凸多边形。

兄妹俩决定以下面的方式吃掉披萨：从 Alberto 开始，兄妹轮流选择披萨剩余部分的一个顶点，吃掉由其两条相邻边决定的三角形（详情请查看样例解释）。在这样的前 $n - 3$ 轮，披萨上的顶点每轮会减少一个。在第 $(n - 2)$ 轮，披萨全部被吃掉，游戏结束。

假设 Alberto 和 Beatrice 以最优策略吃披萨，那么谁会吃掉**最多一半**披萨？你应该找出谁会赢，并帮他们适当地选择披萨片。请注意，如果 Alberto 和 Beatrice 都以最有策略吃披萨，那么他们最终吃掉的面积有可能正好是一半。

## 输入格式

第一行包含一个整数 $n$ ( $4\le n \le 100$ ) 表示披萨的顶点数。

接下来的 $n$ 行分别包含两个整数 $x_i$ 和 $y_i$ ( $-10^6 \le x_i, y_i \le 10^6$ ) 代表披萨初始形状的多边形第 $i$ 个顶点的坐标。

保证该多边形是严格凸多边形，且其顶点按逆时针顺序给出。

## 输出格式

首先，您应该打印一个字符串 $\texttt{Alberto}$ 或 $\texttt{Beatrice}$ 表示您将帮助获胜的兄弟姐妹。

然后，在接下来的 $n - 2$ 个回合中，你将与交互器交替选择一片披萨并取出它，如果你选择帮助 Alberto，则从你开始；如果你选择帮助 Beatrice，则从交互器开始。

- 当轮到你的时候，打印一行包含一个之前没有选择过的整数 $p$ ( $1 \leq p \leq n$ )，表示你想吃位于 $(x_p, y_p)$ 的顶点决定的那片披萨。

- 当轮到交互器时，读取一个整数 $q$ ( $1 \leq q \leq n$ )，表示交互器想吃由位于 $(x_q, y_q)$ 的顶点决定的披萨。 保证 $q$ 之前没有被选择过。

如果你的回答之一是错误的，交互器会立即终止，你的程序会收到判决 $\texttt{WRONG-ANSWER}$。否则，如果最后你的玩家吃掉了最多一半的披萨，你就会收到 $\texttt{CORRECT}$，否则就会收到 $\texttt{WRONG-ANSWER}$。

打印完一行后，不要忘记结束该行并刷新输出。要刷新输出，请使用：

- 在 C 语言中使用： $\texttt{fflush(stdout)}$ ；
- 在 C++ 中使用： $\texttt{fflush(stdout)}$ , $\texttt{cout <}\texttt{< flush}$ 或 $\texttt{cout.flush()}$ ；
- 在 Java 和 Kotlin 中：$\texttt{System.out.flush()}$ ；
- 在 Python 中：$\texttt{sys.stdout.flush()}$ 。

### 样例解释

在第一个样例中，披萨的面积为 $15$。Alberto 可以在顶点 $2$（面积为 $6.5$）或顶点 $3$（面积为 $3.5$）吃掉少于一半的披萨。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1776I/a11c8c619d68b6a5662a71ab8e5d506280dbfa1e.png)

在第二个样例中，可以证明如果两位玩家都以最佳方式进食，他们将恰好吃掉披萨的一半。因此可以选择帮助 Alberto 或 Beatrice。

在第三个样例中，可以证明只有 Beartric 的最优策略是最多吃掉一半披萨。下面是一个有效交互的示例（读取输入后）：

$$ \begin{array}{|c|c|c|} \hline \textbf{选手} & \textbf{交互器} & \textbf{解释} \\ \hline \texttt{Beatrice} & & \text{选手会帮助 Beatrice} \\ \hline & \texttt{7} & \text{Alberto 吃掉了顶点为 $6$, $7$, $1$ 的三角形, 面积为 $1$} \\ \hline \texttt{2} & & \text{Beatrice 吃掉了顶点为 $1$, $2$, $3$ 的三角形，面积为 $2$} \\ \hline & \texttt{5} & \text{Alberto 吃掉了顶点为 $4$, $5$, $6$ 的三角形，面积为 $1.5$} \\ \hline \texttt{4} & & \text{Beatrice 吃掉了顶点为 $3$, $4$, $6$ 的三角形，面积为 $8$} \\ \hline & \texttt{6} & \text{Alberto 吃掉了顶点为 $3$, $6$, $1$ 的三角形，面积为 $11$} \\ \hline \end{array} $$  

Alberto 吃掉的总面积为 $13.5$，Beatrice 吃掉的总面积为 $10$，不到整个披萨面积的一半。在这个互动示例中，参赛者和交互库执行的操作可能不是最优的。具体过程如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1776I/6de08d54ecde090a85188cff2608644bd6cbb65d.png)

## 样例 #1

### 输入

```
4
0 0
6 1
5 3
1 4
```

### 输出

```
-
```

## 样例 #2

### 输入

```
6
0 0
2 0
3 2
2 4
0 4
-1 2
```

### 输出

```
-
```

## 样例 #3

### 输入

```
7
0 0
2 0
5 2
4 5
1 5
-1 4
-1 2
```

### 输出

```
-
```

