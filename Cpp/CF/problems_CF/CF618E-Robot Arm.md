---
title: "Robot Arm"
layout: "post"
diff: 省选/NOI-
pid: CF618E
tag: []
---

# Robot Arm

## 题目描述

Roger is a robot. He has an arm that is a series of $ n $ segments connected to each other. The endpoints of the $ i $ -th segment are initially located at points $ (i-1,0) $ and $ (i,0) $ . The endpoint at $ (i-1,0) $ is colored red and the endpoint at $ (i,0) $ is colored blue for all segments. Thus, the blue endpoint of the $ i $ -th segment is touching the red endpoint of the $ (i+1) $ -th segment for all valid $ i $ .

Roger can move his arm in two different ways:

1. He can choose some segment and some value. This is denoted as choosing the segment number $ i $ and picking some positive $ l $ . This change happens as follows: the red endpoint of segment number $ i $ and segments from $ 1 $ to $ i-1 $ are all fixed in place. Imagine a ray from the red endpoint to the blue endpoint. The blue endpoint and segments $ i+1 $ through $ n $ are translated $ l $ units in the direction of this ray. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618E/608a2bb2be5a1a38d31c7259ed31650fdc831466.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618E/8dcd266eaca289d2a51d6d607be6e49d38248853.png)In this picture, the red point labeled $ A $ and segments before $ A $ stay in place, while the blue point labeled $ B $ and segments after $ B $ gets translated.
2. He can choose a segment and rotate it. This is denoted as choosing the segment number $ i $ , and an angle $ a $ . The red endpoint of the $ i $ -th segment will stay fixed in place. The blue endpoint of that segment and segments $ i+1 $ to $ n $ will rotate clockwise by an angle of $ a $ degrees around the red endpoint. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618E/4eef0bf50f3454a86a62f402644b9a2c3d461358.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618E/ec84d464b2638b0a9a24702941e18140a91c9b78.png)In this picture, the red point labeled $ A $ and segments before $ A $ stay in place, while the blue point labeled $ B $ and segments after $ B $ get rotated around point $ A $ .

Roger will move his arm $ m $ times. These transformations are a bit complicated, and Roger easily loses track of where the blue endpoint of the last segment is. Help him compute the coordinates of the blue endpoint of the last segment after applying each operation. Note that these operations are cumulative, and Roger's arm may intersect itself arbitrarily during the moves.

## 输入格式

The first line of the input will contain two integers $ n $ and $ m $ ( $ 1<=n,m<=300000 $ ) — the number of segments and the number of operations to perform.

Each of the next $ m $ lines contains three integers $ x_{i} $ , $ y_{i} $ and $ z_{i} $ describing a move. If $ x_{i}=1 $ , this line describes a move of type $ 1 $ , where $ y_{i} $ denotes the segment number and $ z_{i} $ denotes the increase in the length. If $ x_{i}=2 $ , this describes a move of type 2, where $ y_{i} $ denotes the segment number, and $ z_{i} $ denotes the angle in degrees. ( $ 1<=x_{i}<=2,1<=y_{i}<=n,1<=z_{i}<=359 $ )

## 输出格式

Print $ m $ lines. The $ i $ -th line should contain two real values, denoting the coordinates of the blue endpoint of the last segment after applying operations $ 1,...,i $ . Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-4} $ .

Namely, let's assume that your answer for a particular value of a coordinate is $ a $ and the answer of the jury is $ b $ . The checker program will consider your answer correct if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618E/52c84cb27b50fce8b08f35fa39c1f083ebd1a014.png) for all coordinates.

## 说明/提示

The following pictures shows the state of the arm after each operation. The coordinates of point $ F $ are printed after applying each operation. For simplicity, we only show the blue endpoints of a segment (with the exception for the red endpoint of the first segment). For instance, the point labeled $ B $ is the blue endpoint for segment $ 1 $ and also the red endpoint for segment $ 2 $ .

Initial state:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618E/5dd94d4d99cfac21befb7a93befbed9aa8e53f84.png) Extend segment $ 1 $ by $ 3 $ .  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618E/5ab40d21a3128a7477f5fe60ed97f6335e1f7d0b.png) Rotate segment $ 3 $ by $ 90 $ degrees clockwise.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618E/3cc04dffc9e337d6a8b726a86dfd69075b16a531.png) Rotate segment $ 5 $ by $ 48 $ degrees clockwise.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618E/31b256905ebb7f9c64425dd492e0dea1a58b3d40.png) Extend segment $ 4 $ by $ 1 $ .  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618E/2ca643cd80863149bbc87b72a007522a1a3c680f.png)

## 样例 #1

### 输入

```
5 4
1 1 3
2 3 90
2 5 48
1 4 1

```

### 输出

```
8.0000000000 0.0000000000
5.0000000000 -3.0000000000
4.2568551745 -2.6691306064
4.2568551745 -3.6691306064

```

