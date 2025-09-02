---
title: "CNHARD - CN Tower (Hard)"
layout: "post"
diff: 难度0
pid: SP1269
tag: []
---

# CNHARD - CN Tower (Hard)

## 题目描述

Christy C. Coder is traveling to Waterloo for a programming competition. On the way, she stops in Toronto to do some sightseeing. The unfortunate thing about travelling is that everyone back home expects her to bring back pictures of everything. Christy hates taking pictures: it makes her look like such a tourist! Fortunately, Christy has a plan to make her picture-taking quite painless.

At 553 m tall, CN Tower is the world's tallest free-standing building. 351 m up the tower is the "360" rotating restaurant, which rotates a full 360 degrees every 72 minutes. From there, Christy can see the whole city, and take close-up pictures of all the landmarks using her fancy new 100x optical zoom camera. Since the restaurant itself rotates, she only needs to stand in one place to take pictures in all directions.

The elevator normally takes 61 seconds to get from the ground up to the rotating restaurant. Unfortunately, when Christy arrives at the CN Tower, she learns that the elevator is out of service, so she has to take the stairs, which takes somewhat longer. Christy arrives at the top at 9:36 pm, by which time it is dark. She can only take pictures with a very powerful flash, which takes a long time to recharge between pictures. While the flash is charging, she cannot take any pictures. Thus, Christy needs a new program to calculate the minimum time that she must spend in the restaurant in order for it to rotate enough to bring all the landmarks in view, and taking into consideration the charging time of the flash. In addition to these difficulties, the restaurant closes at midnight. Thus, Christy may not have enough time to take pictures of all the landmarks.

As before, assume that Christy does not move around in the restaurant after choosing her initial position, but waits for it to rotate to the angle required to take each picture. As with the daytime problem (CNEASY), Christy can (very quickly) pick her initial position, since the restaurant is not that big. Christy always points her camera exactly perpendicular to the window to minimize distortion due to the glass. After taking the last picture, Christy must stay in the restaurant until her flash recharges. Since it is dark outside, if more than one landmark occupies an angular position, Christy can capture **only one one landmark per photo** (in order to keep the desired landmark in focus, blurring all others).

## 输入格式

The first line of input consists of the number of test cases. For each test case, the first line is an integer _n_ (1 n n lines specify a landmark. Each landmark specification consists of the landmark name (a string of uppercase and lowercase letters), a space, and the compass angle, in degrees (specified with a maximum of 2 decimal places), to the landmark from the CN Tower (0 = north, 90 = east, 180 = south, 270 = west). Finally, the last line contains the amount of time, in seconds, required for the flash to charge.

## 输出格式

For each test case, output a single integer, the minimum number of seconds that Christy must remain in the restaurant. If the time is not an integer number of seconds, round it up to the nearest second. If it is not possible for Christy to take all the pictures before closing, instead output "not possible".

## 样例 #1

### 输入

```
1
5
CasaLoma 231.0
OntarioParliament 123.0
SkyDome 75.0
RoyalYorkHotel 340.0
PearsonAirport 165.0
10
```

### 输出

```
3022
```

