# 题目信息

# [USACO09NOV] Cow Rescue G

## 题目描述

Bessie is trapped in a triangular maze with N rows (1 <= N <= 1,000,000). A three row maze is shown below:

The i'th row of the maze contains 2\*i-1 triangles. Numbering from the left, the triangles are named (i,1), (i,2), and so on.

Bessie can travel to the (often three) triangles which share an edge with her current triangle. For example, if she is at (3, 3), she can travel to (3, 2), (3, 4) and (4, 4). Bessie takes one minute to travel from one triangle to the next.

FJ has learned the Bessie is trapped and knows by tracking her iPhone that she starts her exit trek at triangle (Si,Sj). FJ's love for Bessie knows no bounds so he wants her back in the minimum possible time.

The maze has M (1 <= M <= 10,000) exits found in locations throughout the set of triangles. Any one of these will enable Bessie to escape. Once she enters an exit triangle, she leaves the maze in just one more minute.

Find the minimum time in minutes, T, required for Bessie to exit the maze and report the optimal exit location she uses, (OUTi, OUTj). If more than one location requires only T minutes, output the location with the smallest row. If two optimal rows are the same, output the one with smaller column.

贝希被困在一个三角形的迷宫之中。这个迷宫有 $N$ 行（$1 \le N \le 1000000$）。比如下图是一个 $3$ 行的迷宫。  迷宫的第 $i$ 行有 $2i-1$ 个三角形，从左到右分别编号为 $(i, 1)$、$(i, 2)$ 等等。

贝希每次可以从一个三角形走到任意一个一个跟当前的三角形有邻边的三角形。

比如说，如果她目前处于三角形 $(3, 3)$，那么，她可以走到三角形 $(3, 2)$、$(3, 4)$ 和 $(4, 4)$。贝希每次需要一分钟的时间来移动到下一个三角形。

农夫约翰发现贝希被困了！于是她跟踪贝希的iPhone手机（可怜的触摸屏～），得知贝希目前处于三角形 $(S_i, S_j)$。

因为约翰对贝希有著无穷无尽的浓浓爱意，所以他希望贝希能尽可能快地回到他的身边。 在迷宫的三角形之中，有 $M$（$1 \le M \le 10000$）个是出口。在任何一个出口都可以让贝希逃离迷宫。一旦贝希进入一个作为出口的三角形，她用多一分钟就可以逃离这个迷宫。 找到一个可以让贝希逃离迷宫最小时间 $T$，并输出她应该从哪一个出口逃离迷宫，这个出口记为 $(\text{OUT}_i, \text{OUT}_j)$。

如果有多个出口同时需要时间 $T$，输出那个行的编号小的出口，如果仍然有多个出口，输出那个列的编号小的。


## 样例 #1

### 输入

```
4 2 
2 1 
3 5 
4 4 
```

### 输出

```
4 4 
4 
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕在三角形迷宫中计算起点到出口的最短距离展开。各题解思路各有特色，有的借助单源最短路算法，有的通过找规律、坐标变换或图形转换来实现 $O(1)$ 计算距离，从而降低时间复杂度。其中，chenly8128 的题解思路清晰，对计算距离的方法阐述详细；Tracy_Loght 的题解通过找规律来计算距离；zjo_2001 的题解采用图形转换和贪心策略；_Weslie_ 的题解通过坐标重新标号和区域划分来求解。

### 所选题解
- **chenly8128（4星）**
  - **关键亮点**：思路清晰，详细阐述了计算两点距离的方法，包括垂直和非垂直方向的移动分析，代码实现简洁。
  - **个人心得**：提醒注意贝希离开迷宫还需一分钟，避免遗漏。
- **zjo_2001（4星）**
  - **关键亮点**：通过将三角形迷宫转换为新图，使得点的移动规则更清晰，便于贪心计算距离。
- **_Weslie_（4星）**
  - **关键亮点**：采用坐标重新标号和区域划分的方法，将复杂的三角形迷宫问题转化为规则图形中的距离计算问题，并给出了详细的证明。

### 重点代码与核心实现思想
#### chenly8128
```cpp
sum = -1;
if ((ey[j] & 1) ^ (ex[j] <= sx)) sum++;
if (flag ^ (ex[j] >= sx)) sum++; // 计算需要量的总增加量
sum += abs(ex[j] - sx);		// 纵坐标的差
sum = max(sum,abs(-ex[j] + ey[j] + sx - sy)) + abs(ex[j]-sx)+1;			// 总距离计算
```
**核心思想**：先计算非垂直移动需要量的总增加量，再加上纵坐标的差，最后取非垂直移动的最大值与纵坐标差的和，得到总距离。

#### zjo_2001
```cpp
if(y1&1) x1=2*x1-1;else x1=2*x1-2;
y1=(y1+1)/2;
if(x1>x2) swap(x1,x2),swap(y1,y2);
tmp=x2-x1;int can=(x2-x1+(bool)(x2&1))/2;
if(y1>=y2) tmp+=(y1-y2)*2;
else{
  y2-=can;
  if(y2>y1)tmp+=(y2-y1)*2;
}
```
**核心思想**：将三角形迷宫转换为新图，根据起点和终点的位置关系，先计算垂直移动的步数，再根据列的关系计算非垂直移动的步数。

#### _Weslie_
```cpp
if(hc<=zc){
  nans=hc+zc;
}
else{
  if((x[i]-y[i])%2==0){
    c=y[i]-x[i];
    d=c+1;
  }
  else{
    d=y[i]-x[i];
    c=d-1;
  }
  int jx,jy;
  jx=(a-d)/2;
  jy=a-jx;
  nans=abss(jx-x[i])+abss(jx-sx)+abss(jy-y[i])+abss(jy-sy);
}
```
**核心思想**：根据坐标重新标号后的点的位置关系，判断点所在的区域，对于不同区域采用不同的距离计算方法。

### 最优关键思路或技巧
- 多种题解都致力于实现 $O(1)$ 计算两点间距离，从而将总复杂度降低到 $O(m)$，避免了 $O(n^2+m)$ 的高复杂度。
- 通过图形转换（如将三角形迷宫转换为新图）、坐标重新标号和区域划分等方法，将复杂的三角形迷宫问题转化为更规则、易处理的问题。

### 可拓展之处
同类型题可能涉及不同形状的迷宫或地图，解题思路可以借鉴这些题解中的图形转换、坐标变换和找规律的方法。类似算法套路包括在复杂图形中通过规则转换来简化问题，以及利用几何性质计算距离。

### 推荐题目
- P1135 奇怪的电梯
- P1605 迷宫
- P1036 选数

### 个人心得总结
chenly8128 提醒在计算总时间时要注意贝希离开迷宫还需一分钟，避免遗漏这个关键信息。 

---
处理用时：35.32秒