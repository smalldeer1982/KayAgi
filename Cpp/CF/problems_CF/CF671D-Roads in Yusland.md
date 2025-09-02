---
title: "Roads in Yusland"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF671D
tag: []
---

# Roads in Yusland

## 题目描述

Mayor of Yusland just won the lottery and decided to spent money on something good for town. For example, repair all the roads in the town.

Yusland consists of $ n $ intersections connected by $ n-1 $ bidirectional roads. One can travel from any intersection to any other intersection using only these roads.

There is only one road repairing company in town, named "RC company". Company's center is located at the intersection $ 1 $ . RC company doesn't repair roads you tell them. Instead, they have workers at some intersections, who can repair only some specific paths. The $ i $ -th worker can be paid $ c_{i} $ coins and then he repairs all roads on a path from $ u_{i} $ to some $ v_{i} $ that lies on the path from $ u_{i} $ to intersection $ 1 $ .

Mayor asks you to choose the cheapest way to hire some subset of workers in order to repair all the roads in Yusland. It's allowed that some roads will be repaired more than once.

If it's impossible to repair all roads print $ -1 $ .

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 1 \le n,m \le 300000 $ ) — the number of cities in Yusland and the number of workers respectively.

Then follow $ n−1 $ line, each of them contains two integers $ x_{i} $ and $ y_{i} $ ( $ 1 \le x_{i},y_{i} \le n $ ) — indices of intersections connected by the $ i $ -th road.

Last $ m $ lines provide the description of workers, each line containing three integers $ u_{i} $ , $ v_{i} $ and $ c_{i} $ ( $ 1 \le u_{i},v_{i} \le n $ , $ 1 \le c_{i} \le 10^{9} $ ). This means that the $ i $ -th worker can repair all roads on the path from $ v_{i} $ to $ u_{i} $ for $ c_{i} $ coins. It's guaranteed that $ v_{i} $ lies on the path from $ u_{i} $ to $ 1 $ . Note that $ v_{i} $ and $ u_{i} $ may coincide.

## 输出格式

If it's impossible to repair all roads then print $ -1 $ . Otherwise print a single integer — minimum cost required to repair all roads using "RC company" workers.

## 说明/提示

In the first sample, we should choose workers with indices $ 1 $ , $ 3 $ , $ 4 $ and $ 5 $ , some roads will be repaired more than once but it is OK. The cost will be equal to $ 2+3+1+2=8 $ coins.

## 样例 #1

### 输入

```
6 5
1 2
1 3
3 4
4 5
4 6
2 1 2
3 1 4
4 1 3
5 3 1
6 3 2

```

### 输出

```
8

```

