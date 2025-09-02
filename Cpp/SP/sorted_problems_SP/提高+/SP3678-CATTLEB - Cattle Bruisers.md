---
title: "CATTLEB - Cattle Bruisers"
layout: "post"
diff: 提高+/省选-
pid: SP3678
tag: []
---

# CATTLEB - Cattle Bruisers

## 题目描述

Canmuu 在彩弹比赛中被 Bessie 打得落花流水，如今决定在电子游戏中找回场子。

在这个游戏里，Bessie 从坐标网格的点 (BX, BY) 开始逃亡，起始时间记为 0。她以每秒 (BVX, BVY) 的速度匀速移动。例如，在时间 1 时，她的位置会是 (BX + BVX, BY + BVY)；在时间 1.5 时，她会移动到 (BX + 1.5 \* BVX, BY + 1.5 \* BVY)。

然而，Canmuu 派出了 N (1 ≤ N ≤ 50,000) 个牛战士来追赶 Bessie。在时间 t = 0 时，第 i 个牛战士位于位置 (X_i, Y_i)，以每秒 (VX_i, VY_i) 的速度移动。

每个牛战士都配备了“近战”武器，可以在距离不超过 R 的范围内攻击 Bessie。

Bessie 有一个护盾来护身，但她希望尽量节省护盾的能量。因此，她想知道在任意时刻（可能是非整数时间）内，有多少个牛战士会进入她的攻击范围。

题目保证，为了避免浮点数精度误差，无论将攻击范围缩小到 R-0.0001 还是扩大到 R+0.0001，结果都是相同的。

## 输入格式

* 第一行：输入六个用空格分隔的整数，分别是 N, R, BX, BY, BVX 和 BVY。
* 接下来第 2 到 N+1 行：每行输入四个用空格分隔的整数，分别为第 i 个牛战士的 X_i, Y_i, VX_i 和 VY_i。

## 输出格式

* 输出一个整数，表示在任意时刻攻击范围内的牛战士最大数量。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3 1 0 0 0 2
0 -3 0 4
1 2 -1 1
1 -2 2 -1


Input details:

Bessie starts at point (0, 0) and is moving at 2 units per second in the (positive) y-direction. There are 3 cattle bruisers, the first of which starts at point (0, -3) and travels 4 units per second in the y-direction. The maximum distance for a cattle bruiser to be in range of Bessie is 1 unit.
```

### 输出

```
2
```

