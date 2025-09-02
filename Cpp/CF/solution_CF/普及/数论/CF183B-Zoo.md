# Zoo

## 题目描述

The Zoo in the Grid Kingdom is represented by an infinite grid. The Zoo has $ n $ observation binoculars located at the $ OX $ axis. For each $ i $ between $ 1 $ and $ n $ , inclusive, there exists a single binocular located at the point with coordinates $ (i,0) $ . There are $ m $ flamingos in the Zoo, located at points with positive coordinates. The flamingos are currently sleeping and you can assume that they don't move.

In order to get a good view over the flamingos, each of the binoculars can be independently rotated to face any angle (not necessarily integer). Then, the binocular can be used to observe all flamingos that is located at the straight line passing through the binocular at the angle it is set. In other words, you can assign each binocular a direction corresponding to any straight line passing through the binocular, and the binocular will be able to see all flamingos located on that line.

Today, some kids from the prestigious Codeforces kindergarten went on a Field Study to the Zoo. Their teacher would like to set each binocular an angle to maximize the number of flamingos that can be seen by the binocular. The teacher is very interested in the sum of these values over all binoculars. Please help him find this sum.

## 说明/提示

This picture shows the answer to the example test case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF183B/757dceb4f771edfe053738d9268c557dc412c79e.png)

## 样例 #1

### 输入

```
5 5
2 1
4 1
3 2
4 3
4 4
```

### 输出

```
11
```

