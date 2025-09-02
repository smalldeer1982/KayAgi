# 题目信息

# [USACO18JAN] Blocked Billboard II B

## 题目描述

Bessie the cow used to have such a nice view from her barn, looking across road at a set of two billboards advertising delicious looking cow feed. Unfortunately, one of these billboards has recently been updated so it now advertises "Farmer Larry's Lawnmowers". Bessie is not a fan of lawnmowers since their only purpose, as far as she can tell, is cutting back the grass in her field that she finds so tasty (if you haven't noticed, much of Bessie's thought process revolves around food).

Fortunately, the remaining cow feed billboard is situated in front of the lawnmower billboard, potentially obscuring it.

Bessie, determined to remove the offensive lawnmower billboard completely from her view, hatches a risky plan. She plans to steal a large rectangular tarp from the barn and sneak out late at night to cover the remaining portion of the lawnmower billboard, so that she can no longer see any part of it.

Given the locations of the two billboards, please help Bessie compute the minimum area of the tarp she will need. Since the only tarps available in the barn are rectangular in size, Bessie observes that she may conceivably need a tarp whose area is slightly larger than the exposed area of the lawnmower billboard, as illustrated in the example below. The tarp may only be placed such that its sides are parallel to those of the other billboards (i.e., it cannot be "tilted"). 

## 说明/提示

### Sample Explanation 1

Here, the cow feed billboard obscures the lower right corner of the lawnmower billboard, but this doesn't really help, since Bessie still needs to use a tarp whose size is as large as the entire lawnmower billboard. 

## 样例 #1

### 输入

```
2 1 7 4
5 -1 10 3```

### 输出

```
15```

# AI分析结果

• 综合分析与结论：
    - 思路方面，多数题解采用暴力解法，利用二维数组标记两个矩形覆盖区域，通过遍历找到未被覆盖部分的坐标最值，从而计算出所需矩形面积。而“cff_0102”的题解通过分类讨论两个矩形的位置关系，以$O(1)$时间复杂度直接得出结果。
    - 算法要点，暴力解法关键在于合理利用二维数组标记和遍历寻找坐标最值；分类讨论则需准确分析不同位置关系下的面积计算方式。
    - 解决难点上，暴力解法需注意坐标可能为负导致数组越界问题；分类讨论则要全面且准确地分析各种位置情况。
    - 总体而言，暴力解法直观但时间复杂度较高，分类讨论虽思路复杂但效率更高。

所选的题解：
  - 作者：cff_0102 (5星)
    - 关键亮点：采用分类讨论的方式，将两个矩形的位置关系分为三种主要情况，每种情况再细分，以$O(1)$时间复杂度高效解决问题，避免了暴力解法的高复杂度。代码简洁，逻辑清晰。
    - 个人心得：提到要注意题目是否默认坐标有序，避免变量名与头文件函数冲突。
    - 核心代码：
```cpp
#include<iostream>
using namespace std;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int x1,y1,x2,y2,x1_,y1_,x2_,y2_;
    cin>>x1>>y1>>x2>>y2>>x1_>>y1_>>x2_>>y2_;
    if(x1_<=x1 && x2<=x2_ && y1_<=y1 && y2<=y2_)cout<<0,exit(0);
    if(x1<x1_ && x1_<x2 && x2<=x2_ && y1_<=y1 && y2<=y2_)cout<<(x1_-x1)*(y2-y1),exit(0);
    if(x1_<=x1 && x2<=x2_ && y1<y1_ && y1_<y2 && y2<=y2_)cout<<(x2-x1)*(y1_-y1),exit(0);
    if(x1_<=x1 && x1<x2_ && x2_<x2 && y1_<=y1 && y2<=y2_)cout<<(x2-x2_)*(y2-y1),exit(0);
    if(x1_<=x1 && x2<=x2_ && y1_<=y1 && y1<y2_ && y2_<y2)cout<<(x2-x1)*(y2-y2_),exit(0);
    cout<<(x2-x1)*(y2-y1);
    return 0;
}
```
核心实现思想：先判断第二个矩形是否完全包含第一个矩形，若是则输出0；再依次判断第二个矩形是否能完全包含第一个矩形的一条边，若满足相应条件则按对应公式输出面积；若以上情况都不满足，则输出第一个矩形的面积。

  - 作者：Silent1019 (4星)
    - 关键亮点：暴力解法思路清晰，代码实现简洁明了。通过二维数组`vis`标记割草机广告牌暴露在外的点，然后暴力找到最左上角点和最右下角点，从而计算出防水布最小面积。
    - 核心代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a1,a2,b1,b2,c1,c2,d1,d2;
bool vis[2005][2005];
int mx1,my1,mx2,my2;
int main()
{
    scanf("%d%d%d%d",&a1,&b1,&c1,&d1);
    scanf("%d%d%d%d",&a2,&b2,&c2,&d2);
    for(int i=a1+1;i<=c1;i++)
        for(int j=b1+1;j<=d1;j++)
            vis[i+1000][j+1000]=true;
    for(int i=a2+1;i<=c2;i++)
        for(int j=b2+1;j<=d2;j++)
            vis[i+1000][j+1000]=false;
    mx1=2001; my1=2001; mx2=-1; my2=-1;
    for(int i=0;i<=2000;i++)
        for(int j=0;j<=2000;j++)
            if(vis[i][j]) mx1=min(mx1,i),my1=min(my1,j);
    for(int i=0;i<=2000;i++)
        for(int j=0;j<=2000;j++)
            if(vis[i][j]) mx2=max(mx2,i),my2=max(my2,j);
    if(mx1==2001&&my1==2001&&mx2==-1&&my2==-1) printf("0\n");
    else printf("%d\n",(mx2-mx1+1)*(my2-my1+1));
    return 0;
}
```
核心实现思想：先将割草机广告牌覆盖区域标记为`true`，奶牛饲料广告牌覆盖区域标记为`false`，然后通过两次遍历找到标记为`true`的点中的横纵坐标的最值，最后根据最值计算并输出面积，若没有找到标记为`true`的点则输出0。

  - 作者：wei2013 (4星)
    - 关键亮点：同样是暴力解法，代码简洁易懂。通过二维数组`flag`标记两个广告牌覆盖区域，然后分别找到未被覆盖区域的左上角和右下角坐标，计算出所需矩形面积，同时注意到坐标可能为负的问题并进行处理。
    - 核心代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
bool flag[2005][2005];
int main(){
    int x1,x2,y1,y2,x3,y3,x4,y4;
    cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
    for(int i=x1+1;i<=x2;i++){
        for(int j=y1+1;j<=y2;j++){
            flag[i+1000][j+1000]=1;
        }
    }
    for(int i=x3+1;i<=x4;i++){
        for(int j=y3+1;j<=y4;j++){
            flag[i+1000][j+1000]=0;
        }
    }
    int sx1=2000,sy1=2000,sx2=0,sy2=0;
    for(int i=0;i<=2000;i++){
        for(int j=0;j<=2000;j++){
            if(flag[i][j]){
                sx1=min(sx1,i);
                sy1=min(sy1,j);
            }
        }
    }
    for(int i=0;i<=2000;i++){
        for(int j=0;j<=2000;j++){
            if(flag[i][j]){
                sx2=max(sx2,i);
                sy2=max(sy2,j);
            }
        }
    }
    if(sx1==2000 && sy1==2000 && sx2==0 && sy2==0){
        cout<<0;
        return 0;
    }
    cout<<(sx2-sx1+1)*(sy2-sy1+1);
    return 0;
}
```
核心实现思想：先将割草机广告牌覆盖区域标记为`1`，奶牛饲料广告牌覆盖区域标记为`0`，通过两次遍历找到标记为`1`的点中的横纵坐标的最值，即未被覆盖区域的左上角和右下角坐标，根据坐标计算并输出面积，若未找到标记为`1`的点则输出0。

• 最优关键思路或技巧：分类讨论不同矩形位置关系的方式，能在$O(1)$时间复杂度内解决问题，相比暴力解法大大提高了效率。在处理坐标可能为负的问题上，将坐标整体加上一个值（如1000），使数组下标为正，避免数组越界。

• 可拓展之处：此类题目属于几何图形面积计算与位置关系分析类型，类似套路有对多个矩形重叠情况进行分析，或结合动态规划思想解决随时间变化的矩形覆盖问题等。

• 相似知识点洛谷题目：
    - P1314 聪明的质检员：涉及区间统计和二分查找，与本题在处理数据范围和逻辑判断上有相似之处。
    - P1169 棋盘制作：同样是在矩形区域内进行分析，不过涉及到最大子矩形的查找，锻炼对图形区域的分析能力。
    - P2774 方格取数问题：需要考虑矩阵中元素的选取和最值计算，与本题在处理二维数据和逻辑推导方面有一定联系。 

---
处理用时：82.56秒