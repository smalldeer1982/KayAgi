# 题目信息

# Surrounded

## 题目描述

So, the Berland is at war with its eternal enemy Flatland again, and Vasya, an accountant, was assigned to fulfil his duty to the nation.

Right now the situation in Berland is dismal — their both cities are surrounded! The armies of flatlanders stand on the borders of circles, the circles' centers are in the surrounded cities. At any moment all points of the flatland ring can begin to move quickly in the direction of the city — that's the strategy the flatlanders usually follow when they besiege cities.

The berlanders are sure that they can repel the enemy's attack if they learn the exact time the attack starts. For that they need to construct a radar that would register any movement at the distance of at most $ r $ from it. Thus, we can install a radar at such point, that at least one point of the enemy ring will be in its detecting range (that is, at a distance of at most $ r $ ). Then the radar can immediately inform about the enemy's attack.

Due to the newest technologies, we can place a radar at any point without any problems. But the problem is that the berlanders have the time to make only one radar. Besides, the larger the detection radius $ (r) $ is, the more the radar costs.

That's why Vasya's task (that is, your task) is to find the minimum possible detection radius for the radar. In other words, your task is to find the minimum radius $ r $ $ (r>=0) $ such, that a radar with radius $ r $ can be installed at some point and it can register the start of the movements of both flatland rings from that point.

In this problem you can consider the cities as material points, the attacking enemy rings - as circles with centers in the cities, the radar's detection range — as a disk (including the border) with the center at the point where the radar is placed.

## 说明/提示

The figure below shows the answer to the first sample. In this sample the best decision is to put the radar at point with coordinates $ (2,0) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF190B/d8b028b093bb3a5b506b76e0b869d1e14653f9f5.png)The figure below shows the answer for the second sample. In this sample the best decision is to put the radar at point with coordinates $ (0,0) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF190B/621697dde00296bbf818d1a40e69e6ac2914a652.png)

## 样例 #1

### 输入

```
0 0 1
6 0 3
```

### 输出

```
1.000000000000000```

## 样例 #2

### 输入

```
-10 10 3
10 -10 3
```

### 输出

```
11.142135623730951```

# AI分析结果

### 题目内容
# 被包围

## 题目描述
所以，伯兰又和它的宿敌弗拉特兰开战了，会计瓦夏被派去履行他对国家的职责。

此刻，伯兰的形势很严峻——它的两座城市都被包围了！弗拉特兰的军队驻扎在圆圈的边界上，圆圈的中心就在被包围的城市里。在任何时刻，弗拉特兰包围圈上的所有点都可能迅速朝着城市的方向移动——这是弗拉特兰人围攻城市时通常采用的策略。

伯兰人确信，如果他们知道敌人进攻开始的确切时间，他们就能击退敌人的进攻。为此，他们需要建造一个雷达，该雷达能够探测到距离它最多为 $r$ 的任何移动。因此，我们可以在这样一个点上安装雷达，使得敌人包围圈上至少有一个点在其探测范围内（即距离最多为 $r$ ）。这样，雷达就能立即通知敌人的进攻。

由于有最新的技术，我们可以毫无问题地将雷达放置在任何点上。但问题是，伯兰人只有时间制造一个雷达。此外，探测半径 $r$ 越大，雷达的成本就越高。

这就是为什么瓦夏的任务（也就是你的任务）是找到雷达最小可能的探测半径。换句话说，你的任务是找到最小半径 $r$ （$r\geq0$ ），使得一个半径为 $r$ 的雷达可以安装在某个点上，并且它能够从该点探测到两个弗拉特兰包围圈的移动开始。

在这个问题中，你可以将城市视为质点，进攻的敌人包围圈视为以城市为中心的圆，雷达的探测范围视为以雷达所在点为中心的圆盘（包括边界）。

## 说明/提示
下图展示了第一个样例的答案。在这个样例中，最佳决策是将雷达放置在坐标为 $(2,0)$ 的点上。

![第一个样例图示](https://cdn.luogu.com.cn/upload/vjudge_pic/CF190B/d8b028b093bb3a5b506b76e0b869d1e14653f9f5.png)
下图展示了第二个样例的答案。在这个样例中，最佳决策是将雷达放置在坐标为 $(0,0)$ 的点上。

![第二个样例图示](https://cdn.luogu.com.cn/upload/vjudge_pic/CF190B/621697dde00296bbf818d1a40e69e6ac2914a652.png)

## 样例 #1
### 输入
```
0 0 1
6 0 3
```
### 输出
```
1.000000000000000
```
## 样例 #2
### 输入
```
-10 10 3
10 -10 3
```
### 输出
```
11.142135623730951
```

### 算法分类
数学

### 题解综合分析与结论
所有题解思路本质一致，均是先通过两点间距离公式求出两圆圆心距离，再根据两圆不同位置关系（相离、包含、相交或相切）来计算能连接两圆的最小圆半径。各题解对位置关系的分类表述略有差异，但核心计算相同。

### 所选的题解
- **作者：王梓涵 (赞：1) - 4星**
    - **关键亮点**：思路清晰，对三种位置关系分类明确，代码简洁明了，直接根据不同位置关系套用对应公式计算并输出结果。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int x1, y1, r1, x2, y2, r2;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
    double di1 = pow(x1 - x2, 2);
    double di2 = pow(y1 - y2, 2);
    double di = sqrt(di1 + di2); //求两圆最短距离
    if (di > r1 + r2)
    {
        cout << fixed << setprecision(10) << (di - r1 - r2) / 2 << endl; 
    }
    else if (di < abs(r1 - r2))
    {
        cout << fixed << setprecision(10) << (abs(r1 - r2) - di) / 2 << endl;
    }
    else
    {
        cout << "0" << endl;
    }
    return 0; 
}
```
核心实现思想：先输入两圆的圆心坐标和半径，计算圆心距离 `di` ，然后根据 `di` 与两圆半径和、半径差绝对值的大小关系，分三种情况计算并输出结果。

- **作者：neil021110 (赞：0) - 4星**
    - **关键亮点**：代码简洁紧凑，逻辑清晰，直接根据两圆位置关系的判断条件计算最小半径并输出，对公式的运用熟练。
    - **核心代码**：
```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
int main(){
    int x1,y1,r1,x2,y2,r2;
    cin>>x1>>y1>>r1>>x2>>y2>>r2;
    double d=sqrt(pow(x1-x2,2)+pow(y1-y2,2));
    if(d>r1+r2){
        printf("%.15lf",(d-r1-r2)/2);
    }else if(d<abs(r1-r2)){
        printf("%.15lf",(abs(r1-r2)-d)/2);
    }else{
        printf("%.15lf",0);
    }
} 
```
核心实现思想：输入两圆信息后计算圆心距离 `d` ，通过 `d` 与两圆半径和、半径差绝对值比较，按不同情况输出最小半径。

### 最优关键思路或技巧
通过运用两点间距离公式确定两圆圆心距离，再依据圆心距离与两圆半径的大小比较，分情况确定能连接两圆的最小圆半径，关键在于对两圆不同位置关系的准确判断和相应公式的正确运用。

### 拓展
同类型题通常围绕几何图形位置关系及相关度量计算，类似算法套路是先确定图形间关键参数（如本题圆心距），再依据几何性质分情况讨论计算。

### 洛谷相似题目推荐
- [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：涉及简单数学计算与条件判断。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：通过不同方案价格计算选择最优方案，考查数学运算和逻辑判断。
- [P2670 扫雷游戏](https://www.luogu.com.cn/problem/P2670)：结合数学逻辑与二维数组操作，判断扫雷游戏中各位置状态。 

---
处理用时：71.33秒