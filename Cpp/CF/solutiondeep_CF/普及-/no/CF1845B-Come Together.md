# 题目信息

# Come Together

## 题目描述

Bob and Carol hanged out with Alice the whole day, but now it's time to go home. Alice, Bob and Carol live on an infinite 2D grid in cells $ A $ , $ B $ , and $ C $ respectively. Right now, all of them are in cell $ A $ .

If Bob (or Carol) is in some cell, he (she) can move to one of the neighboring cells. Two cells are called neighboring if they share a side. For example, the cell $ (3, 5) $ has four neighboring cells: $ (2, 5) $ , $ (4, 5) $ , $ (3, 6) $ and $ (3, 4) $ .

Bob wants to return to the cell $ B $ , Carol — to the cell $ C $ . Both of them want to go along the shortest path, i. e. along the path that consists of the minimum possible number of cells. But they would like to walk together as well.

What is the maximum possible number of cells that Bob and Carol can walk together if each of them walks home using one of the shortest paths?

## 说明/提示

In all pictures, red color denotes cells belonging only to Bob's path, light blue color — cells belonging only to Carol's path, and dark blue color — cells belonging to both paths.

One of the optimal routes for the first test case is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1845B/c85b53d9d1c53dba5706a67df1e77b327570237d.png)  Bob's route contains $ 5 $ cells, Carol's route — $ 7 $ cells, and they will visit $ 3 $ cells together.The optimal answer for the second test case is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1845B/50a4de29eccf387d8021b4c4d1c44c0fb0d1aede.png)  Bob's route contains $ 4 $ cells, Carol's route — $ 3 $ cells, and they will visit only $ 1 $ cell together.One of the optimal answers for the third test case is shown below:

 ![](https://espresso.codeforces.com/c353903c5672ef730d834c0e4d58e6d3554a4b1b.png)  Bob's route contains $ 6 $ cells, Carol's route — $ 9 $ cells, and they will visit $ 6 $ cells together.

## 样例 #1

### 输入

```
3
3 1
1 3
6 4
5 2
2 2
7 2
1 1
4 3
5 5```

### 输出

```
3
1
6```

# AI分析结果

### 题目内容中文重写
# 相聚同行

## 题目描述
鲍勃和卡罗尔与爱丽丝共度了一整天，现在是时候回家了。爱丽丝、鲍勃和卡罗尔分别住在无限二维网格中的单元格 $A$、$B$ 和 $C$ 里。此刻，他们都在单元格 $A$ 中。

如果鲍勃（或卡罗尔）在某个单元格中，他（她）可以移动到相邻的单元格之一。如果两个单元格共享一条边，则称它们为相邻单元格。例如，单元格 $(3, 5)$ 有四个相邻单元格：$(2, 5)$、$(4, 5)$、$(3, 6)$ 和 $(3, 4)$。

鲍勃想回到单元格 $B$，卡罗尔想回到单元格 $C$。他们都想沿着最短路径行走，即沿着包含最少单元格数量的路径行走。但他们也希望一起走一段路。

如果他们各自沿着最短路径回家，那么鲍勃和卡罗尔最多可以一起走过多少个单元格？

## 说明/提示
在所有图片中，红色表示仅属于鲍勃路径的单元格，浅蓝色表示仅属于卡罗尔路径的单元格，深蓝色表示属于两人共同路径的单元格。

第一个测试用例的一条最优路线如下所示：

![第一个测试用例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1845B/c85b53d9d1c53dba5706a67df1e77b327570237d.png) 鲍勃的路线包含 $5$ 个单元格，卡罗尔的路线包含 $7$ 个单元格，他们将一起经过 $3$ 个单元格。

第二个测试用例的最优答案如下所示：

![第二个测试用例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1845B/50a4de29eccf387d8021b4c4d1c44c0fb0d1aede.png) 鲍勃的路线包含 $4$ 个单元格，卡罗尔的路线包含 $3$ 个单元格，他们将仅一起经过 $1$ 个单元格。

第三个测试用例的一条最优答案如下所示：

![第三个测试用例](https://espresso.codeforces.com/c353903c5672ef730d834c0e4d58e6d3554a4b1b.png) 鲍勃的路线包含 $6$ 个单元格，卡罗尔的路线包含 $9$ 个单元格，他们将一起经过 $6$ 个单元格。

## 样例 #1
### 输入
```
3
3 1
1 3
6 4
5 2
2 2
7 2
1 1
4 3
5 5
```
### 输出
```
3
1
6
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是分别考虑横、纵坐标方向上两人路径的重合情况。在网格中，两点间最短路径是曼哈顿距离，所以只要判断两人在横、纵坐标方向上移动的方向是否相同，若相同则取移动距离较小值作为重合部分，最后加上起点。
- **思路对比**：部分题解通过分类讨论 $B$、$C$ 点相对于 $A$ 点的位置（如都在上方、下方等）来确定重合部分；部分题解通过判断坐标变化量的正负是否相同来确定是否能一起走。
- **算法要点**：核心是分别计算横、纵坐标方向上的重合距离，最后加上起点 $A$。
- **解决难点**：主要难点在于准确判断两人在横、纵坐标方向上是否能一起走，以及如何计算重合的距离。

### 所选题解
- **作者：cff_0102 (4星)**
  - **关键亮点**：思路清晰，将计算重合距离的逻辑封装成函数，提高了代码的可读性和可维护性。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int cal(long long db,long long dc){//计算 ans 应该加的值 
    if(db*dc<0)return 0;//相乘小于 0 则不同号
    return min(abs(db),abs(dc));//同号取更小的绝对值 
}
int main(){
    ios::sync_with_stdio(false);
    int t;cin>>t;//数据组数 
    while(t--){
        int xa,xb,xc,ya,yb,yc;
        cin>>xa>>ya>>xb>>yb>>xc>>yc;//输入三个坐标 
        int dxb=xb-xa,dyb=yb-ya,dxc=xc-xa,dyc=yc-ya;//计算 ΔxB,ΔyB,ΔxC,ΔyC
        int ans=0;
        ans+=cal(dxb,dxc);
        ans+=cal(dyb,dyc);
        cout<<ans+1<<endl;//实际上也可以将 ans 初始化为 1 
    }
    return 0;
}
```
**核心实现思想**：定义 `cal` 函数判断两个坐标变化量是否同号，若同号则返回较小的绝对值，否则返回 0。在主函数中分别计算横、纵坐标方向上的重合距离，最后加上起点。
- **作者：Night_sea_64 (4星)**
  - **关键亮点**：明确指出两点间最短路是曼哈顿距离，代码简洁，直接通过三元运算符计算结果。
  - **核心代码**：
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#define int long long
using namespace std;
signed main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int xa,ya,xb,yb,xc,yc;
        cin>>xa>>ya>>xb>>yb>>xc>>yc;
        int dx1=xb-xa,dx2=xc-xa;
        int dy1=yb-ya,dy2=yc-ya;
        cout<<(dx1*dx2>0?min(abs(dx1),abs(dx2)):0)+(dy1*dy2>0?min(abs(dy1),abs(dy2)):0)+1<<endl;
    }
    //dx1*dx2>0 求的是 dx1 和 dx2 是否同正或同负，即 x 坐标是否向同一方向移动。y 坐标同理。
    return 0;
}
```
**核心实现思想**：计算 $A$ 到 $B$、$A$ 到 $C$ 的横、纵坐标变化量，通过判断变化量乘积是否大于 0 确定是否同号，若同号则取较小绝对值，最后加上起点。
- **作者：_O_v_O_ (4星)**
  - **关键亮点**：思路清晰，通过分类讨论判断横、纵坐标方向上的重合情况，代码逻辑简单易懂。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long  //不开 long long 见祖宗。

int t,ax,ay,bx,by,cx,cy;  //后面几个代表各点坐标

signed main(){
    cin>>t;
    while(t--){
        cin>>ax>>ay>>bx>>by>>cx>>cy;
        int x=bx-ax,y=by-ay,x2=cx-ax,y2=cy-ay,ans=1;
        if(x*x2>0) ans+=min(abs(x),abs(x2));
        if(y*y2>0) ans+=min(abs(y),abs(y2));
        cout<<ans<<"\n";
    }
    return 0;
}
```
**核心实现思想**：计算各点坐标差值，判断横、纵坐标方向上的变化量是否同号，若同号则加上较小的绝对值，最后输出结果。

### 最优关键思路或技巧
- **分开考虑横、纵坐标**：由于在网格中只能横向或纵向移动，所以分别计算横、纵坐标方向上的重合距离，最后相加。
- **判断坐标变化量正负**：通过判断两人在横、纵坐标方向上坐标变化量的正负是否相同，确定是否能一起走。

### 拓展思路
同类型题目可能会改变移动规则（如增加斜向移动）、改变地图形状（如有限网格、有障碍物的网格）等。解题时仍可考虑分别分析不同方向上的移动情况，结合具体规则进行计算。

### 推荐洛谷题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：涉及组合数学和简单的数学计算。
- [P1420 最长连号](https://www.luogu.com.cn/problem/P1420)：需要分析数字之间的关系，运用数学思维。
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：可通过数学方法计算区间覆盖问题。

### 个人心得
题解中未包含个人心得内容。

---
处理用时：58.32秒