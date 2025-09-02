---
title: "Tourist"
layout: "post"
diff: 省选/NOI-
pid: CF76F
tag: []
---

# Tourist

## 题目描述

Tourist walks along the $ X $ axis. He can choose either of two directions and any speed not exceeding $ V $ . He can also stand without moving anywhere. He knows from newspapers that at time $ t_{1} $ in the point with coordinate $ x_{1} $ an interesting event will occur, at time $ t_{2} $ in the point with coordinate $ x_{2} $ — another one, and so on up to ( $ x_{n},t_{n} $ ). Interesting events are short so we can assume they are immediate. Event $ i $ counts visited if at time $ t_{i} $ tourist was at point with coordinate $ x_{i} $ .

Write program tourist that will find maximum number of events tourist if:

- at the beginning (when time is equal to 0) tourist appears at point 0,
- tourist can choose initial point for himself.

Yes, you should answer on two similar but different questions.

## 输入格式

The first line of input contains single integer number $ N $ ( $ 1<=N<=100000 $ ) — number of interesting events. The following $ N $ lines contain two integers $ x_{i} $ and $ t_{i} $ — coordinate and time of the $ i $ -th event. The last line of the input contains integer $ V $ — maximum speed of the tourist. All $ x_{i} $ will be within range $ -2·10^{8}<=x_{i}<=2·10^{8} $ , all $ t_{i} $ will be between $ 1 $ and $ 2·10^{6} $ inclusive. $ V $ will be positive and will not exceed 1000. The input may contain events that happen at the same time or in the same place but not in the same place at the same time.

## 输出格式

The only line of the output should contain two space-sepatated integers — maximum number of events tourist can visit in he starts moving from point 0 at time 0, and maximum number of events tourist can visit if he chooses the initial point for himself.

## 样例 #1

### 输入

```
3
-1 1
42 7
40 8
2

```

### 输出

```
1 2

```

