---
title: "Bear and Bowling"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF573E
tag: []
---

# Bear and Bowling

## 题目描述

Limak is an old brown bear. He often goes bowling with his friends. Today he feels really good and tries to beat his own record!

For rolling a ball one gets a score — an integer (maybe negative) number of points. Score for $ i $ -th roll is multiplied by $ i $ and scores are summed up. So, for $ k $ rolls with scores $ s_{1},s_{2},...,s_{k} $ , total score is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF573E/dc22606298d977fae92bc67b7a4815c447193831.png). Total score is $ 0 $ if there were no rolls.

Limak made $ n $ rolls and got score $ a_{i} $ for $ i $ -th of them. He wants to maximize his total score and he came up with an interesting idea. He will cancel some rolls, saying that something distracted him or there was a strong wind.

Limak is able to cancel any number of rolls, maybe even all or none of them. Total score is calculated as if there were only non-canceled rolls. Look at the sample tests for clarification. What maximum total score can Limak get?

## 输入格式

The first line contains single integer $ n $ ( $ 1<=n<=10^{5} $ ).

The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ ( $ |a_{i}|<=10^{7}) $ - scores for Limak's rolls.

## 输出格式

Print the maximum possible total score after choosing rolls to cancel.

## 说明/提示

In first sample Limak should cancel rolls with scores $ -8 $ and $ -3 $ . Then he is left with three rolls with scores $ -2,0,5 $ . Total score is $ 1·(-2)+2·0+3·5=13 $ .

In second sample Limak should cancel roll with score $ -50 $ . Total score is $ 1·(-10)+2·20+3·(-30)+4·40+5·60=400 $ .

## 样例 #1

### 输入

```
5
-2 -8 0 5 -3

```

### 输出

```
13

```

## 样例 #2

### 输入

```
6
-10 20 -30 40 -50 60

```

### 输出

```
400

```

