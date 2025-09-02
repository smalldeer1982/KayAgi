---
title: "RC Kaboom Show"
layout: "post"
diff: 省选/NOI-
pid: CF1359F
tag: []
---

# RC Kaboom Show

## 题目描述

You know, it's hard to conduct a show with lots of participants and spectators at the same place nowadays. Still, you are not giving up on your dream to make a car crash showcase! You decided to replace the real cars with remote controlled ones, call the event "Remote Control Kaboom Show" and stream everything online.

For the preparation you arranged an arena — an infinite 2D-field. You also bought $ n $ remote controlled cars and set them up on the arena. Unfortunately, the cars you bought can only go forward without turning left, right or around. So you additionally put the cars in the direction you want them to go.

To be formal, for each car $ i $ ( $ 1 \le i \le n $ ) you chose its initial position ( $ x_i, y_i $ ) and a direction vector ( $ dx_i, dy_i $ ). Moreover, each car has a constant speed $ s_i $ units per second. So after car $ i $ is launched, it stars moving from ( $ x_i, y_i $ ) in the direction ( $ dx_i, dy_i $ ) with constant speed $ s_i $ .

The goal of the show is to create a car collision as fast as possible! You noted that launching every car at the beginning of the show often fails to produce any collisions at all. Thus, you plan to launch the $ i $ -th car at some moment $ t_i $ . You haven't chosen $ t_i $ , that's yet to be decided. Note that it's not necessary for $ t_i $ to be integer and $ t_i $ is allowed to be equal to $ t_j $ for any $ i, j $ .

The show starts at time $ 0 $ . The show ends when two cars $ i $ and $ j $ ( $ i \ne j $ ) collide (i. e. come to the same coordinate at the same time). The duration of the show is the time between the start and the end.

What's the fastest crash you can arrange by choosing all $ t_i $ ? If it's possible to arrange a crash then print the shortest possible duration of the show. Otherwise, report that it's impossible.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 25000 $ ) — the number of cars.

Each of the next $ n $ lines contains five integers $ x_i $ , $ y_i $ , $ dx_i $ , $ dy_i $ , $ s_i $ ( $ -10^3 \le x_i, y_i \le 10^3 $ ; $ 1 \le |dx_i| \le 10^3 $ ; $ 1 \le |dy_i| \le 10^3 $ ; $ 1 \le s_i \le 10^3 $ ) — the initial position of the $ i $ -th car, its direction vector and its speed, respectively.

It's guaranteed that all cars start at distinct positions (i. e. $ (x_i, y_i) \neq (x_j, y_j) $ for $ i \neq j $ ).

## 输出格式

Print the shortest possible duration of the show if it's possible to arrange a crash by choosing all $ t_i $ . Otherwise, print "No show :(".

Your answer is considered correct if its absolute or relative error does not exceed $ 10^{-6} $ .

Formally, let your answer be $ a $ , and the jury's answer be $ b $ . Your answer is accepted if and only if $ \frac{|a - b|}{\max{(1, |b|)}} \le 10^{-6} $ .

## 说明/提示

Here is the picture for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1359F/d2ecf70507b59a587066a94bf192c2aaf876732b.png)The fastest cars to crash are cars $ 2 $ and $ 4 $ . Let's launch car $ 2 $ at $ 0 $ , car $ 4 $ at about $ 0.096762 $ and cars $ 1 $ and $ 3 $ at arbitrary time. That way cars $ 2 $ and $ 4 $ will crash into each other at about $ 0.585902 $ . So here's what it looks like at the moment of the collision:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1359F/7eb93988ebce321ea184467bf5782ea0b56ef6ba.png)Here's the picture for the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1359F/8ba1cf46328b0ac8eb2a7e79c52a4646f39b1d74.png)

## 样例 #1

### 输入

```
4
3 -1 -1 1 2
2 3 -3 -2 10
-4 2 1 -2 1
-2 -2 -1 2 4
```

### 输出

```
0.585902082262898
```

## 样例 #2

### 输入

```
2
-1 1 -1 1 200
1 1 1 5 200
```

### 输出

```
No show :(
```

