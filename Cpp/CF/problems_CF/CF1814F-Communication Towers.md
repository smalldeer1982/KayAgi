---
title: "Communication Towers"
layout: "post"
diff: 省选/NOI-
pid: CF1814F
tag: []
---

# Communication Towers

## 题目描述

There are $ n $ communication towers, numbered from $ 1 $ to $ n $ , and $ m $ bidirectional wires between them. Each tower has a certain set of frequencies that it accepts, the $ i $ -th of them accepts frequencies from $ l_i $ to $ r_i $ .

Let's say that a tower $ b $ is accessible from a tower $ a $ , if there exists a frequency $ x $ and a sequence of towers $ a=v_1, v_2, \dots, v_k=b $ , where consecutive towers in the sequence are directly connected by a wire, and each of them accepts frequency $ x $ . Note that accessibility is not transitive, i. e if $ b $ is accessible from $ a $ and $ c $ is accessible from $ b $ , then $ c $ may not be accessible from $ a $ .

Your task is to determine the towers that are accessible from the $ 1 $ -st tower.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n \le 2 \cdot 10^5 $ ; $ 0 \le m \le 4 \cdot 10^5 $ ) — the number of communication towers and the number of wires, respectively.

Then $ n $ lines follows, the $ i $ -th of them contains two integers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le 2 \cdot 10^5 $ ) — the boundaries of the acceptable frequencies for the $ i $ -th tower.

Then $ m $ lines follows, the $ i $ -th of them contains two integers $ v_i $ and $ u_i $ ( $ 1 \le v_i, u_i \le n $ ; $ v_i \ne u_i $ ) — the $ i $ -th wire that connects towers $ v_i $ and $ u_i $ . There are no two wires connecting the same pair of towers.

## 输出格式

In a single line, print distinct integers from $ 1 $ to $ n $ in ascending order — the indices of the communication towers that are accessible from the $ 1 $ -st tower.

## 样例 #1

### 输入

```
6 5
3 5
1 2
2 4
2 3
3 3
4 6
1 3
6 1
3 5
3 6
2 3
```

### 输出

```
1 3 5 6
```

## 样例 #2

### 输入

```
3 1
2 3
1 4
1 1
1 3
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5 5
1 3
2 3
2 2
3 5
2 4
1 2
2 3
3 4
4 1
4 5
```

### 输出

```
1 2 3 4 5
```

