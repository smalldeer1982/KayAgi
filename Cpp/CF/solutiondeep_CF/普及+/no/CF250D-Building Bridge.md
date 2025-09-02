# 题目信息

# Building Bridge

## 题目描述

Two villages are separated by a river that flows from the north to the south. The villagers want to build a bridge across the river to make it easier to move across the villages.

The river banks can be assumed to be vertical straight lines $ x=a $ and $ x=b $ ( $ 0&lt;a&lt;b $ ).

The west village lies in a steppe at point $ O=(0,0) $ . There are $ n $ pathways leading from the village to the river, they end at points $ A_{i}=(a,y_{i}) $ . The villagers there are plain and simple, so their pathways are straight segments as well.

The east village has reserved and cunning people. Their village is in the forest on the east bank of the river, but its exact position is not clear. There are $ m $ twisted paths leading from this village to the river and ending at points $ B_{i}=(b,y'_{i}) $ . The lengths of all these paths are known, the length of the path that leads from the eastern village to point $ B_{i} $ , equals $ l_{i} $ .

The villagers want to choose exactly one point on the left bank of river $ A_{i} $ , exactly one point on the right bank $ B_{j} $ and connect them by a straight-line bridge so as to make the total distance between the villages (the sum of $ |OA_{i}|+|A_{i}B_{j}|+l_{j} $ , where $ |XY| $ is the Euclidean distance between points $ X $ and $ Y $ ) were minimum. The Euclidean distance between points $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ equals ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF250D/db1ba0d5909a3b47109b2e5f65fe13400ae1bd9a.png).

Help them and find the required pair of points.

## 样例 #1

### 输入

```
3 2 3 5
-2 -1 4
-1 2
7 3
```

### 输出

```
2 2```

# AI分析结果

### 题目重写
# 搭建桥梁

## 题目描述
两个村庄被一条自北向南流淌的河流隔开。村民们想要在河上建一座桥，以便更便捷地往来于两个村庄之间。

可以将河岸看作垂直的直线 $x = a$ 和 $x = b$（$0 < a < b$）。

西村位于草原上的点 $O = (0, 0)$ 处。有 $n$ 条小路从西村通向河流，这些小路的终点为点 $A_i = (a, y_i)$。西村的村民淳朴简单，所以他们的小路也都是直线段。

东村的村民含蓄且狡黠。他们的村庄位于河东岸的森林中，但其确切位置并不明确。有 $m$ 条蜿蜒的小路从东村通向河流，终点为点 $B_i = (b, y'_i)$。所有这些小路的长度都是已知的，从东村到点 $B_i$ 的小路长度为 $l_i$。

村民们想要在左岸准确选择一个点 $A_i$，在右岸准确选择一个点 $B_j$，并用一座直线桥将它们连接起来，使得两个村庄之间的总距离（即 $|OA_i| + |A_iB_j| + l_j$ 的和，其中 $|XY|$ 是点 $X$ 和点 $Y$ 之间的欧几里得距离）最小。点 $(x_1, y_1)$ 和 $(x_2, y_2)$ 之间的欧几里得距离为 $\sqrt{(x_1 - x_2)^2 + (y_1 - y_2)^2}$。

请帮助他们找出所需的点对。

## 样例 #1
### 输入
```
3 2 3 5
-2 -1 4
-1 2
7 3
```
### 输出
```
2 2
```

### 算法分类
二分

### 综合分析与结论
两题解核心思路都是通过枚举一个点来确定另一个点以求解最小值。
 - **共同点**：都意识到由于 $l$ 的无序性，选择枚举 $B$ 点来找最优的 $A$ 点。
 - **不同点**：
    - **mountain_climber**：认为函数 $f(x)=|OA_x|+|A_xB_j|+l_j$ 是单峰函数，采用三分法求其最小值。
    - **Kazdale**：通过证明关于 $|OA| + |AB|$ 与 $y_A$ 和 $y_G$ 关系的命题，利用二分查找结合 $OB$ 解析式求出 $G$ 点坐标，进而找到最优的 $A$ 点。

两题解在思路清晰度和代码实现上都有一定提升空间，均未达到4星标准，故不单独列出具体题解。

### 通用建议与扩展思路
 - **思路优化**：对于此类求距离和最小值问题，可深入分析几何性质，挖掘更多隐藏条件，优化枚举与查找策略。如本题可进一步思考如何利用几何关系减少计算量。
 - **代码优化**：题解代码在变量命名和注释方面可进一步完善，增强可读性。如适当增加注释说明关键步骤，采用更具描述性的变量名。
 - **拓展**：同类型题多为几何与算法结合，涉及距离计算与最值求解。类似算法套路包括利用几何性质简化问题、通过特定搜索或优化算法求解。例如在其他几何场景中，通过证明几何命题，利用二分、三分等算法解决最值问题。

### 相似知识点洛谷题目
 - [P2249 【深基13.例1】查找](https://www.luogu.com.cn/problem/P2249)
 - [P2678 [NOIP2015 普及组] 跳石头](https://www.luogu.com.cn/problem/P2678)
 - [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853) 

---
处理用时：37.79秒