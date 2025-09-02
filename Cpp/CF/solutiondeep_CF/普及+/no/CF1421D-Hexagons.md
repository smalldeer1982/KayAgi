# 题目信息

# Hexagons

## 题目描述

Lindsey Buckingham told Stevie Nicks ["Go your own way"](https://www.youtube.com/watch?v=6ul-cZyuYq4). Nicks is now sad and wants to go away as quickly as possible, but she lives in a 2D hexagonal world.

Consider a hexagonal tiling of the plane as on the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1421D/d7b83f7c1945491e0c5eb4d61bc10fb5c2e2d62e.png)Nicks wishes to go from the cell marked $ (0, 0) $ to a certain cell given by the coordinates. She may go from a hexagon to any of its six neighbors you want, but there is a cost associated with each of them. The costs depend only on the direction in which you travel. Going from $ (0, 0) $ to $ (1, 1) $ will take the exact same cost as going from $ (-2, -1) $ to $ (-1, 0) $ . The costs are given in the input in the order $ c_1 $ , $ c_2 $ , $ c_3 $ , $ c_4 $ , $ c_5 $ , $ c_6 $ as in the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1421D/5520c3b497776aedfe7eabfa13d5468fdc04c261.png)Print the smallest cost of a path from the origin which has coordinates $ (0, 0) $ to the given cell.

## 说明/提示

The picture below shows the solution for the first sample. The cost $ 18 $ is reached by taking $ c_3 $ 3 times and $ c_2 $ once, amounting to $ 5+5+5+3=18 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1421D/0ec113af8e20d4052a5764c227b25383ee56e47d.png)

## 样例 #1

### 输入

```
2
-3 1
1 3 5 7 9 11
1000000000 1000000000
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
18
1000000000000000000```

# AI分析结果

### 题目内容（中文重写）
# 六边形

## 题目描述
林赛·巴克林汉姆（Lindsey Buckingham）告诉史蒂夫·尼克斯（Stevie Nicks）“走你自己的路”（["Go your own way"](https://www.youtube.com/watch?v=6ul-cZyuYq4)）。尼克斯现在很伤心，想尽快离开，但她生活在一个二维六边形世界里。

考虑如下图所示的平面六边形平铺。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1421D/d7b83f7c1945491e0c5eb4d61bc10fb5c2e2d62e.png)

尼克斯希望从标记为 $(0, 0)$ 的单元格移动到由坐标给定的某个单元格。她可以从一个六边形移动到其六个相邻单元格中的任意一个，但每个移动方向都有相关的代价。这些代价仅取决于移动的方向。从 $(0, 0)$ 移动到 $(1, 1)$ 的代价与从 $(-2, -1)$ 移动到 $(-1, 0)$ 的代价完全相同。输入中按照下图所示的顺序给出代价 $c_1$、$c_2$、$c_3$、$c_4$、$c_5$、$c_6$。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1421D/5520c3b497776aedfe7eabfa13d5468fdc04c261.png)

打印从原点（坐标为 $(0, 0)$）到给定单元格的最小路径代价。

## 说明/提示
下图显示了第一个样例的解决方案。通过走 3 次 $c_3$ 和 1 次 $c_2$ 达到代价 18，即 $5 + 5 + 5 + 3 = 18$。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1421D/0ec113af8e20d4052a5764c227b25383ee56e47d.png)

## 样例 #1
### 输入
```
2
-3 1
1 3 5 7 9 11
1000000000 1000000000
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000
```
### 输出
```
18
1000000000000000000
```

### 算法分类
最短路

### 综合分析与结论
这些题解的核心思路都是先对六个方向的代价进行优化，找到每个方向的最小代价，然后根据目标点的坐标进行分类讨论，计算从原点到目标点的最小路径代价。

- **思路对比**：不同题解在优化方向代价和分类讨论的具体方法上有所不同。有的使用最短路思想（如 Bellman - Ford 松弛操作），有的通过建图跑最短路（如 Dijkstra 算法），还有的通过列方程求解。
- **算法要点**：大部分题解都利用了最短路的思想来优化方向代价，然后根据坐标的正负情况进行分类讨论。
- **解决难点**：主要难点在于如何找到每个方向的最小代价，以及如何根据坐标情况确定最优的移动方案。

### 所选题解
- **作者：_ztyqwq (赞：5)，4星**
  - **关键亮点**：思路清晰，先利用最短路思想优化方向代价，再进行分类讨论，代码简洁易懂。
  - **个人心得**：作者提到自己是场上 8min 一血，说明对题目理解深刻，反应迅速。
- **作者：瞬间。。 (赞：4)，4星**
  - **关键亮点**：通过列二元一次方程组求解，思路独特，代码实现也较为清晰。
- **作者：Leap_Frog (赞：1)，4星**
  - **关键亮点**：将问题转化为坐标系中的方程问题，利用一次函数的性质求解，代码简洁，只有两行主要代码。

### 重点代码
#### _ztyqwq 的代码
```cpp
for(int i = 1; i <= 10; i++)
{
    c1 = min(c1, c6 + c2);
    c2 = min(c2, c1 + c3);
    c3 = min(c3, c2 + c4);
    c4 = min(c4, c3 + c5);
    c5 = min(c5, c4 + c6);
    c6 = min(c6, c5 + c1);
}
if(x >= 0 && y >= 0)
{
    if(x > y)
        printf("%lld\n", y * c1 + (x - y) * c6);
    else
        printf("%lld\n", x * c1 + (y - x) * c2);
}
// 其他分类讨论情况类似
```
**核心实现思想**：通过多次 Bellman - Ford 松弛操作优化方向代价，然后根据坐标的正负情况分类讨论，计算最小路径代价。

#### 瞬间。。的代码
```cpp
int solve(int i,int j)
{
    if(i==1 && j==4) return -1;
    if(i==2 && j==5) return -1;
    if(i==3 && j==6) return -1;
    int a1=x[i],b1=x[j],a2=y[i],b2=y[j],c1=-xx,c2=-yy;
    int a=-1,b=-1;
    if(a1==0) b=xx/b1;
    else if(a2==0) b=yy/b2;
    else
    {
        if(a1+a2!=0) b=(xx-yy)/(b1-b2);
        else b=(xx+yy)/(b1+b2);
    }
    if(a1!=0) a=(xx-b*b1)/a1;
    else a=(yy-b*b2)/a2;
    if(a<0 || b<0) return -1;
    return a*c[i]+b*c[j];
}
// 在主函数中枚举所有方向组合
for(int i=1;i<=6;i++)
    for(int j=i+1;j<=6;j++)
    {
        if(solve(i,j)<0) continue;
        ans=min(ans,solve(i,j));
    }
```
**核心实现思想**：通过列二元一次方程组求解每种方向组合的移动步数，若步数为负则舍去，最后取所有可行组合的最小代价。

#### Leap_Frog 的代码
```cpp
inline long long calc(int x) {int a1=x,a2=Y-a1,a3=a1-X;return (a1>0?c1:-c4)*a1+(a2>0?c2:-c5)*a2+(a3>0?c3:-c6)*a3;}
int main() {for(scanf("%d",&T);T--;) scanf("%lld%lld%lld%lld%lld%lld%lld%lld",&X,&Y,&c1,&c2,&c3,&c4,&c5,&c6),printf("%lld\n",min(calc(0),min(calc(X),calc(Y))));}
```
**核心实现思想**：将问题转化为坐标系中的方程问题，得到总费用关于一个变量的一次函数，根据一次函数的性质，最小值在端点取到，枚举三个端点值计算最小代价。

### 关键思路或技巧
- **最短路思想**：利用最短路的松弛操作优化每个方向的代价，确保每个方向的代价都是最小的。
- **分类讨论**：根据目标点的坐标正负情况进行分类讨论，确定最优的移动方案。
- **方程求解**：通过列方程求解移动步数，简化问题的求解过程。

### 拓展思路
同类型题或类似算法套路：
- 网格图中的最短路径问题，可能会有不同的移动规则和代价计算方式。
- 图论中的最短路问题，如 Dijkstra 算法、Bellman - Ford 算法的应用。
- 坐标平面上的路径规划问题，需要根据不同的条件进行分类讨论。

### 推荐题目
- [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)
- [P3371 单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
- [P4779 单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)

### 个人心得摘录与总结
- **_ztyqwq**：提到自己 8min 一血，说明在比赛中要快速理解题目，抓住关键思路，才能取得好成绩。
- **Chinese_zjc_**：调分类讨论调到最后一秒才调出来，结果比赛结束掉分，提醒我们在做题时要注意细节，确保分类讨论的完整性和正确性。

---
处理用时：63.58秒