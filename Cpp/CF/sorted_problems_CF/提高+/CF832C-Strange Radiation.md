---
title: "Strange Radiation"
layout: "post"
diff: 提高+/省选-
pid: CF832C
tag: []
---

# Strange Radiation

## 题目描述

 $ n $ people are standing on a coordinate axis in points with positive integer coordinates strictly less than $ 10^{6} $ . For each person we know in which direction (left or right) he is facing, and his maximum speed.

You can put a bomb in some point with non-negative integer coordinate, and blow it up. At this moment all people will start running with their maximum speed in the direction they are facing. Also, two strange rays will start propagating from the bomb with speed $ s $ : one to the right, and one to the left. Of course, the speed $ s $ is strictly greater than people's maximum speed.

The rays are strange because if at any moment the position and the direction of movement of some ray and some person coincide, then the speed of the person immediately increases by the speed of the ray.

You need to place the bomb is such a point that the minimum time moment in which there is a person that has run through point $ 0 $ , and there is a person that has run through point $ 10^{6} $ , is as small as possible. In other words, find the minimum time moment $ t $ such that there is a point you can place the bomb to so that at time moment $ t $ some person has run through $ 0 $ , and some person has run through point $ 10^{6} $ .

## 输入格式

The first line contains two integers $ n $ and $ s $ ( $ 2<=n<=10^{5} $ , $ 2<=s<=10^{6} $ ) — the number of people and the rays' speed.

The next $ n $ lines contain the description of people. The $ i $ -th of these lines contains three integers $ x_{i} $ , $ v_{i} $ and $ t_{i} $ ( $ 0&lt;x_{i}&lt;10^{6} $ , $ 1<=v_{i}&lt;s $ , $ 1<=t_{i}<=2 $ ) — the coordinate of the $ i $ -th person on the line, his maximum speed and the direction he will run to ( $ 1 $ is to the left, i.e. in the direction of coordinate decrease, $ 2 $ is to the right, i.e. in the direction of coordinate increase), respectively.

It is guaranteed that the points $ 0 $ and $ 10^{6} $ will be reached independently of the bomb's position.

## 输出格式

Print the minimum time needed for both points $ 0 $ and $ 10^{6} $ to be reached.

Your answer is considered correct if its absolute or relative error doesn't exceed $ 10^{-6} $ . Namely, if your answer is $ a $ , and the jury's answer is $ b $ , then your answer is accepted, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832C/67bc3119d4422d5f5d06ffa95a1fb9753f3e40d8.png).

## 说明/提示

In the first example, it is optimal to place the bomb at a point with a coordinate of $ 400000 $ . Then at time $ 0 $ , the speed of the first person becomes $ 1000 $ and he reaches the point $ 10^{6} $ at the time $ 600 $ . The bomb will not affect on the second person, and he will reach the $ 0 $ point at the time $ 500000 $ .

In the second example, it is optimal to place the bomb at the point $ 500000 $ . The rays will catch up with both people at the time $ 200 $ . At this time moment, the first is at the point with a coordinate of $ 300000 $ , and the second is at the point with a coordinate of $ 700000 $ . Their speed will become $ 1500 $ and at the time $ 400 $ they will simultaneously run through points $ 0 $ and $ 10^{6} $ .

## 样例 #1

### 输入

```
2 999
400000 1 2
500000 1 1

```

### 输出

```
500000.000000000000000000000000000000

```

## 样例 #2

### 输入

```
2 1000
400000 500 1
600000 500 2

```

### 输出

```
400.000000000000000000000000000000

```

