# [CERC2013] Subway

## 题目描述

$Johny$ 准备去拜访他的朋友 $Michelle$。他的父亲允许他乘地铁独自去那里。$Johny$ 喜欢乘地铁旅行，并很愿意用这次机会在地铁里呆上半天，但是父亲要求他尽量减少换乘次数。这个城市有很多地铁车站，并有几条地铁线路连接它们。所有列车都完全同步——在每条线上的两个连续地铁站点之间地铁行驶的时间恰好需要 $1$ 分钟，而在该城市的任何一个地铁站点上更改线路是不需要花费时间的。

现在 $Johny$ 有了该城市的地铁线路图，请帮助 $Johny$ 计划行程，以便他可以尽可能长时间的在地铁里呆着，同时还要尽量减少换乘次数。

## 说明/提示

时间限制：$8s$

内存限制：$256\texttt{MB}$

## 样例 #1

### 输入

```
3

Stops: OxfordCircus, PiccadillyCircus, HydeParkCorner, King'sCross, GreenPark, Arsenal, Victoria, Highbury&Islington, LeicesterSquare
Lines: Blue, Cyan
Cyan route: Highbury&Islington, King'sCross, OxfordCircus, GreenPark, Victoria
Blue route: HydeParkCorner, GreenPark, PiccadillyCircus, LeicesterSquare, King'sCross, Arsenal
Johny lives at King'sCross
Michelle lives at GreenPark

Stops: OxfordCircus, PiccadillyCircus, HydeParkCorner, King'sCross, GreenPark, Arsenal, Victoria, Highbury&Islington, LeicesterSquare
Lines: Blue, Cyan
Cyan route: Highbury&Islington, King'sCross, OxfordCircus, GreenPark, Victoria
Blue route: HydeParkCorner, GreenPark, PiccadillyCircus, LeicesterSquare, King'sCross, Arsenal
Johny lives at PiccadillyCircus
Michelle lives at LeicesterSquare

Stops: OxfordCircus, PiccadillyCircus, HydeParkCorner, King'sCross, GreenPark, Arsenal, Victoria, Highbury&Islington, LeicesterSquare
Lines: Blue, Cyan
Cyan route: Highbury&Islington, King'sCross, OxfordCircus, GreenPark, Victoria
Blue route: HydeParkCorner, GreenPark, PiccadillyCircus, LeicesterSquare, King'sCross, Arsenal
Johny lives at Victoria
Michelle lives at HydeParkCorner
```

### 输出

```
optimal travel from King'sCross to GreenPark: 1 line, 3 minutes
optimal travel from PiccadillyCircus to LeicesterSquare: 1 line, 1 minute
optimal travel from Victoria to HydeParkCorner: 2 lines, 7 minutes
```

