# 题目信息

# Happy Farm 5

## 题目描述

The Happy Farm 5 creators decided to invent the mechanism of cow grazing. The cows in the game are very slow and they move very slowly, it can even be considered that they stand still. However, carnivores should always be chased off them.

For that a young player Vasya decided to make the shepherd run round the cows along one and the same closed path. It is very important that the cows stayed strictly inside the area limited by the path, as otherwise some cows will sooner or later be eaten. To be absolutely sure in the cows' safety, Vasya wants the path completion time to be minimum.

The new game is launched for different devices, including mobile phones. That's why the developers decided to quit using the arithmetics with the floating decimal point and use only the arithmetics of integers. The cows and the shepherd in the game are represented as points on the plane with integer coordinates. The playing time is modeled by the turns. During every turn the shepherd can either stay where he stands or step in one of eight directions: horizontally, vertically, or diagonally. As the coordinates should always remain integer, then the length of a horizontal and vertical step is equal to $ 1 $ , and the length of a diagonal step is equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF50C/2826342a15affce70e459206e8466cd2b66552a3.png). The cows do not move. You have to minimize the number of moves the shepherd needs to run round the whole herd.

## 说明/提示

Picture for the example test: The coordinate grid is painted grey, the coordinates axes are painted black, the cows are painted red and the sought route is painted green.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF50C/8b34e942d3e45fab9f6a1a087e0ce5cc6f58c465.png)

## 样例 #1

### 输入

```
4
1 1
5 1
5 3
1 3
```

### 输出

```
16
```

# AI分析结果

### 题目内容
# 开心农场5

## 题目描述
《开心农场5》的开发者决定设计奶牛放牧机制。游戏中的奶牛行动非常迟缓，甚至可以认为它们静止不动。然而，必须时刻驱赶食肉动物远离奶牛。

为此，年轻玩家瓦夏决定让牧羊人沿着同一条封闭路径围绕奶牛奔跑。至关重要的是，奶牛必须严格处于路径所围区域内，否则迟早会有奶牛被吃掉。为确保奶牛的绝对安全，瓦夏希望路径完成时间最短。

这款新游戏面向包括手机在内的多种设备发布。因此，开发者决定不再使用浮点数运算，仅使用整数运算。游戏中的奶牛和牧羊人表示为平面上具有整数坐标的点。游戏时间通过回合来模拟。在每个回合中，牧羊人可以原地不动，或者向八个方向之一移动：水平、垂直或对角线方向。由于坐标必须始终保持为整数，水平和垂直移动的步长等于1，对角线移动的步长等于$\sqrt{2}$。奶牛不会移动。你需要最小化牧羊人围绕整个牛群奔跑所需的移动步数。

## 说明/提示
示例测试的图片：坐标网格为灰色，坐标轴为黑色，奶牛为红色，所求路线为绿色。
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF50C/8b34e942d3e45fab9f6a1a087e0ce5cc6f58c465.png)

## 样例 #1
### 输入
```
4
1 1
5 1
5 3
1 3
```
### 输出
```
16
```

### 算法分类
数学（凸包相关计算）

### 题解综合分析与结论
- **思路方面**：多数题解都想到利用凸包来解决问题，因为题目要求用最短路径包围所有点，这与凸包的性质相符。不同之处在于对如何得到严格包围点（点不在路径上）的凸包处理方式，以及后续计算凸包边长的方法。
- **算法要点**：常见的是使用Graham扫描法来计算凸包。同时要考虑如何将普通凸包转化为满足题目要求的严格包围凸包，以及准确计算凸包上相邻两点间的距离。
- **解决难点**：难点在于理解凸包与本题的联系，如何将非严格凸包转化为严格凸包，以及正确实现凸包算法和距离计算。Ag2WO4的题解另辟蹊径，不使用常规凸包算法，而是通过观察发现最终凸包的特殊形状（类似正八边形），直接找出关键端点计算周长，时间复杂度为$O(n)$，优于其他使用Graham扫描法$O(n \log n)$复杂度的题解。

### 所选的题解
- **作者：Ag2WO4 (5星)**
  - **关键亮点**：突破常规凸包算法思维，通过观察发现最终凸包类似正八边形，直接找出八个方向最外侧线段的端点，计算相邻端点距离求和，时间复杂度$O(n)$，效率高。
  - **重点代码核心实现思想**：通过循环遍历输入的点，不断更新八个方向上的关键端点坐标，最后根据这些端点坐标计算周长。
```c
#include<stdio.h>
int i,x,y,xa,ya,pa,ma,xaa,yaa,paa,maa,xia,yia,pia,mia,xi,yi,pi,mi,xai,yai,pai,mai,xii,yii,pii,mii;
int main()
{
    xa=ya=pa=ma=xaa=yaa=paa=maa=xia=yia=pia=mia=-(1<<30);xi=yi=pi=mi=xai=yai=pai=mai=xii=yii=pii=mii=1<<30;
    scanf("%d",&i);
    while(i--)
    {
        scanf("%d%d",&x,&y);
        // 一系列更新八个方向关键端点坐标的操作
    }
    printf("%d",yaa-yai+yia-yii+xaa-xai+xia-xii+(ya+mi>yai?ya+mi:yai)-(pa-ya<yaa?pa-ya:yaa)+(pi-yi>yii?pi-yi:yii)-(ma+yi<yia?ma+yi:yia)+(xa>pa-xaa?xa:pa-xaa)+(xa>xai+ma?xa:xai+ma)-(xi<mi+xia?xi:mi+xia)-(xi<pi-xii?xi:pi-xii));
}
```

### 最优关键思路或技巧
Ag2WO4题解的关键思路是通过对题目条件下最终凸包形状的深入观察，发现其类似正八边形的特点，从而直接找出关键端点计算周长，避免了常规凸包算法中的排序等操作，降低了时间复杂度。

### 拓展
此类题目属于计算几何范畴，类似套路是在处理平面点集相关问题时，先观察点集可能形成的特殊几何形状，利用形状特点简化计算。例如在一些求最小覆盖、最大包含等问题中，可以先思考能否转化为凸包问题，或者是否存在类似的特殊形状规律。

### 相似知识点洛谷题目
- [P2742 【模板】二维凸包](https://www.luogu.com.cn/problem/P2742)：经典的二维凸包模板题，可用于熟悉凸包算法。
- [P3829 [SHOI2012]信用卡凸包](https://www.luogu.com.cn/problem/P3829)：在凸包基础上结合实际场景，增加了问题的复杂性。
- [P1452 Beauty Contest](https://www.luogu.com.cn/problem/P1452)：与凸包相关，求点集中最远点对距离，可加深对凸包应用的理解。 

---
处理用时：65.19秒