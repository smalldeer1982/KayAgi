---
title: "Cats Transport"
layout: "post"
diff: 省选/NOI-
pid: CF311B
tag: ['枚举', '斜率优化', '前缀和']
---

# Cats Transport

## 题目描述

Zxr960115 is owner of a large farm. He feeds $ m $ cute cats and employs $ p $ feeders. There's a straight road across the farm and $ n $ hills along the road, numbered from 1 to $ n $ from left to right. The distance between hill $ i $ and $ (i-1) $ is $ d_{i} $ meters. The feeders live in hill 1.

One day, the cats went out to play. Cat $ i $ went on a trip to hill $ h_{i} $ , finished its trip at time $ t_{i} $ , and then waited at hill $ h_{i} $ for a feeder. The feeders must take all the cats. Each feeder goes straightly from hill 1 to $ n $ without waiting at a hill and takes all the waiting cats at each hill away. Feeders walk at a speed of 1 meter per unit time and are strong enough to take as many cats as they want.

For example, suppose we have two hills $ (d_{2}=1) $ and one cat that finished its trip at time 3 at hill 2 $ (h_{1}=2) $ . Then if the feeder leaves hill 1 at time 2 or at time 3, he can take this cat, but if he leaves hill 1 at time 1 he can't take it. If the feeder leaves hill 1 at time 2, the cat waits him for 0 time units, if the feeder leaves hill 1 at time 3, the cat waits him for 1 time units.

Your task is to schedule the time leaving from hill 1 for each feeder so that the sum of the waiting time of all cats is minimized.

## 输入格式

The first line of the input contains three integers $n,m,p$ $(2 \le n\le 10^5,1 \le m \le 10^5, 1\le p \le 100)$.

The second line contains $n-1$ positive integers $d_{2},d_{3},...,d_{n}$  $(1 \le d_{i} < 10^{4}) .$

Each of the next $m$ lines contains two integers $h_i$ and $t_i$ $(1 \le h_i \le n,0 \le t_i \le 10^9)$.

## 输出格式

Output an integer, the minimum sum of waiting time of all cats.

Please, do not write the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 样例 #1

### 输入

```
4 6 2
1 3 5
1 0
2 1
4 9
1 10
2 10
3 12

```

### 输出

```
3

```

