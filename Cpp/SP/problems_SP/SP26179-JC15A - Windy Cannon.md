---
title: "JC15A - Windy Cannon"
layout: "post"
diff: 难度0
pid: SP26179
tag: []
---

# JC15A - Windy Cannon

## 题目描述

**Windy Cannon**

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP26179/94dd8338cbf2f153de5f19f5c696e7ebe1918f41.png)

This day is very windy, the wind blow very fast that it may be faster than the speed of cannon ball. On this windy day, Gunawan want to test his new prototype cannon, he want to shoot the target at specific location. But before doing that, he wonder how long it take for the cannon ball to hit the target. He know percisely the position of his cannon, the location of the target, the speed of his cannon ball, the speed of wind blows, and the direction of the wind, but unfortunately he forgot to bring the calculator so he ask you for help to calculate the minimum time needed for the cannon ball to hit the target or specify if it's impossible. Can you help him? You can assume that the speed of cannon ball relative to the wind is constant, all other physical effect such as gravity, air friction, temperature, magnus effect are ignored.

**Input**

The first line there are 4 integers and 1 character CP, TP, CBS, WS, WD denoting cannon position (m), target position (m), cannon ball speed (m/s), wind speed (m/s), and wind direction respectively.

**Output**

Print how many seconds the minimum time needed for cannon ball to hit the target rounded to 6 digits after decimal point.

If it's impossible for the cannon ball to hit the target, print "Impossible" without quotes.

**Constraint**

0

0

0

0

if WD = 'L', it means that the wind blow into negative direction (left in catesian plane).

if WD = 'R' it means that the wind blow into positive direction (right in cartesian plane).

**Sample 1**

Input

 `2 10 2 1 L`Output

 `8.000000`**Sample 2**

Input

 `2 10 2 1 R`Output

 `2.666667`**Sample 3**

Input

 `2 10 2 3 L`Output

 `Impossible`**Sample 4**

Input

 `10 2 2 3 L`Output

 `1.600000`**Sample 5**

Input

 `50 50 12 34 R`Output

 `0.000000`**Sample 4 Explanation**

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP26179/00e6f277d4b20c213930e56df619eafec2cae86a.png)

The cannon ball move at speed 2 m/s relative to the wind, so if it shoot to the right, because of the wind blowing 3 m/s to the left relative to the ground, the cannon ball move (3-2=1) m/s to the left relative to the ground and will eventually hit the target in 8 seconds, but this is not optimal, it's faster to shoot the cannon ball to the left, because the wind blowing 3 m/s to the left relative to the ground (and the same direction as the cannon ball move relative to the wind), so the cannon ball will move (3+2=5) m/s to the left relative to the ground and will eventually hit the target at (10-2)/5 = 8/5 = 1.6 seconds. We need to print the result rounded to 6 digit after decimal places, so the minimum time needed for the cannon ball to reach the target is 1.600000 seconds.

