---
title: "Doodle Jump"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF346E
tag: []
---

# Doodle Jump

## 题目描述

 In Doodle Jump the aim is to guide a four-legged creature called "The Doodler" up a never-ending series of platforms without falling. — Wikipedia.

It is a very popular game and xiaodao likes it very much. One day when playing the game she wondered whether there exists a platform that the doodler couldn't reach due to the limits of its jumping ability. Consider the following problem.

There are $ n $ platforms. The height of the $ x $ -th ( $ 1<=x<=n $ ) platform is $ a·x $ mod $ p $ , where $ a $ and $ p $ are positive co-prime integers. The maximum possible height of a Doodler's jump is $ h $ . That is, it can jump from height $ h_{1} $ to height $ h_{2} $ ( $ h_{1}&lt;h_{2} $ ) if $ h_{2}-h_{1}<=h $ . Initially, the Doodler is on the ground, the height of which is 0. The question is whether it can reach the highest platform or not.

For example, when $ a=7 $ , $ n=4 $ , $ p=12 $ , $ h=2 $ , the heights of the platforms are $ 7 $ , $ 2 $ , $ 9 $ , $ 4 $ as in the picture below. With the first jump the Doodler can jump to the platform at height $ 2 $ , with the second one the Doodler can jump to the platform at height $ 4 $ , but then it can't jump to any of the higher platforms. So, it can't reach the highest platform.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF346E/eac4a985e004e32325c04bd865762a38ac4e9205.png)User xiaodao thought about the problem for a long time but didn't solve it, so she asks you for help. Also, she has a lot of instances of the problem. Your task is solve all of these instances.

## 输入格式

The first line contains an integer $ t $ $ (1<=t<=10^{4}) $ — the number of problem instances. Each of the next $ t $ lines contains four integers $ a $ , $ n $ , $ p $ and $ h $ ( $ 1<=a<=10^{9} $ , $ 1<=n&lt;p<=10^{9} $ , $ 0<=h<=10^{9} $ ). It's guaranteed that $ a $ and $ p $ are co-prime.

## 输出格式

For each problem instance, if the Doodler can reach the highest platform, output "YES", otherwise output "NO".

## 样例 #1

### 输入

```
3
7 4 12 2
7 1 9 4
7 4 12 3

```

### 输出

```
NO
NO
YES

```

