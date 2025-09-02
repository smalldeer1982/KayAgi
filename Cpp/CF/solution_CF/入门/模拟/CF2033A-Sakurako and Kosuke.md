# Sakurako and Kosuke

## 题目描述

Sakurako 和 Kosuke 在数轴上用一个点玩游戏。这个点初始在数轴原点。二人轮流操作，Sakurako 先。

在第 $i$ 次移动，玩家将这个点向某个方向移动 $2 \times i - 1$ 个单位长度。Sakurako 向负方向移动点，而 Kosuke 向正方向。

设该点坐标为 $x$。

所以游戏开始后就会发生：
1. Sakurako 将点沿负方向移动 $1$ 个单位长度，此时 $x = -1$；
2. Kosuke 将点沿正方向移动 $3$ 个单位长度，此时 $x = 2$；
3. Sakurako 将点沿负方向移动 $5$ 个单位长度，此时 $x = -3$；
4. $\cdot \cdot \cdot$

直到 $|x| > n$ 时，他们才会停下。可以证明游戏一定会结束的。

定义赢家是在游戏结束前最后一个移动点的人。

你的任务是找到赢家。

## 样例 #1

### 输入

```
4
1
6
3
98```

### 输出

```
Kosuke
Sakurako
Kosuke
Sakurako```

