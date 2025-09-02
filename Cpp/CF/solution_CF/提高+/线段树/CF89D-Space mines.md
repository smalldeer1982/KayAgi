# Space mines

## 题目描述

Once upon a time in the galaxy of far, far away...

Darth Wader found out the location of a rebels' base. Now he is going to destroy the base (and the whole planet that the base is located at), using the Death Star.

When the rebels learnt that the Death Star was coming, they decided to use their new secret weapon — space mines. Let's describe a space mine's build.

Each space mine is shaped like a ball (we'll call it the mine body) of a certain radius $ r $ with the center in the point $ O $ . Several spikes protrude from the center. Each spike can be represented as a segment, connecting the center of the mine with some point $ P $ , such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF89D/260097c7a43ccaae894b47162bab71c5ba9400fd.png) (transporting long-spiked mines is problematic), where $ |OP| $ is the length of the segment connecting $ O $ and $ P $ . It is convenient to describe the point $ P $ by a vector $ p $ such that $ P=O+p $ .

The Death Star is shaped like a ball with the radius of $ R $ ( $ R $ exceeds any mine's radius). It moves at a constant speed along the $ v $ vector at the speed equal to $ |v| $ . At the moment the rebels noticed the Star of Death, it was located in the point $ A $ .

The rebels located $ n $ space mines along the Death Star's way. You may regard the mines as being idle. The Death Star does not know about the mines' existence and cannot notice them, which is why it doesn't change the direction of its movement. As soon as the Star of Death touched the mine (its body or one of the spikes), the mine bursts and destroys the Star of Death. A touching is the situation when there is a point in space which belongs both to the mine and to the Death Star. It is considered that Death Star will not be destroyed if it can move infinitely long time without touching the mines.

Help the rebels determine whether they will succeed in destroying the Death Star using space mines or not. If they will succeed, determine the moment of time when it will happen (starting from the moment the Death Star was noticed).

## 样例 #1

### 输入

```
0 0 0 1 0 0 5
2
10 8 0 2 2
0 -3 0
2 2 0
20 0 0 4 3
2 4 0
-4 3 0
1 -5 0
```

### 输出

```
10.0000000000```

## 样例 #2

### 输入

```
8 8 4 4 4 2 6
1
-2 -2 -1 3 0
```

### 输出

```
-1```

## 样例 #3

### 输入

```
30 30 2 1 2 1 20
3
0 0 40 5 1
1 4 4
-10 -40 -5 7 0
100 200 95 8 1
-10 0 0
```

### 输出

```
74.6757620881```

