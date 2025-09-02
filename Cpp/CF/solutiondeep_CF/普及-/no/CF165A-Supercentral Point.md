# 题目信息

# Supercentral Point

## 题目描述

One day Vasya painted a Cartesian coordinate system on a piece of paper and marked some set of points $ (x_{1},y_{1}),(x_{2},y_{2}),...,(x_{n},y_{n}) $ . Let's define neighbors for some fixed point from the given set $ (x,y) $ :

- point $ (x',y') $ is $ (x,y) $ 's right neighbor, if $ x'&gt;x $ and $ y'=y $
- point $ (x',y') $ is $ (x,y) $ 's left neighbor, if $ x'&lt;x $ and $ y'=y $
- point $ (x',y') $ is $ (x,y) $ 's lower neighbor, if $ x'=x $ and $ y'&lt;y $
- point $ (x',y') $ is $ (x,y) $ 's upper neighbor, if $ x'=x $ and $ y'&gt;y $

We'll consider point $ (x,y) $ from the given set supercentral, if it has at least one upper, at least one lower, at least one left and at least one right neighbor among this set's points.

Vasya marked quite many points on the paper. Analyzing the picture manually is rather a challenge, so Vasya asked you to help him. Your task is to find the number of supercentral points in the given set.

## 说明/提示

In the first sample the supercentral points are only points $ (1,1) $ and $ (1,2) $ .

In the second sample there is one supercental point — point $ (0,0) $ .

## 样例 #1

### 输入

```
8
1 1
4 2
3 1
1 2
0 2
0 1
1 0
1 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
0 0
0 1
1 0
0 -1
-1 0
```

### 输出

```
1
```

# AI分析结果

### 题目内容
# 超级中心点

## 题目描述
一天，瓦夏在一张纸上画了一个笛卡尔坐标系，并标记了一些点$(x_{1},y_{1}),(x_{2},y_{2}),...,(x_{n},y_{n})$ 。对于给定集合中的某个固定点$(x,y)$，我们定义其邻居如下：
 - 点$(x',y')$是$(x,y)$的右邻居，如果$x' > x$且$y' = y$。
 - 点$(x',y')$是$(x,y)$的左邻居，如果$x' < x$且$y' = y$。
 - 点$(x',y')$是$(x,y)$的下邻居，如果$x' = x$且$y' < y$。
 - 点$(x',y')$是$(x,y)$的上邻居，如果$x' = x$且$y' > y$。

如果给定集合中的点$(x,y)$在该集合的点中至少有一个上邻居、至少有一个下邻居、至少有一个左邻居和至少有一个右邻居，我们就认为该点是超级中心点。

瓦夏在纸上标记了相当多的点。手动分析这幅图颇具挑战，所以瓦夏请你帮忙。你的任务是找出给定集合中的超级中心点的数量。

## 说明/提示
在第一个样例中，超级中心点只有点$(1,1)$和$(1,2)$。

在第二个样例中，有一个超级中心点 —— 点$(0,0)$。

## 样例 #1
### 输入
```
8
1 1
4 2
3 1
1 2
0 2
0 1
1 0
1 3
```
### 输出
```
2
```

## 样例 #2
### 输入
```
5
0 0
0 1
1 0
0 -1
-1 0
```
### 输出
```
1
```

• **算法分类**：枚举
• **综合分析与结论**：这些题解思路基本一致，由于数据范围小（$n\leq200$），都采用枚举法暴力求解。核心是对每个点，遍历其余点判断其上下左右四个方向是否都存在点，若都存在则该点为超级中心点。不同点在于部分题解对坐标处理及代码实现细节有差异。
• **所选的题解**
  - **作者：Alex_Wei (5星)**
    - **关键亮点**：思路清晰，代码简洁明了，直接暴力枚举每个点并判断其四个方向是否有点，易读性强。
    - **重点代码核心实现思想**：用两个嵌套循环，外层循环遍历每个点，内层循环遍历其余点判断方向，用四个变量标记四个方向是否有点，若四个方向都有点则答案加1。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x[202],y[202],s;
int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>x[i]>>y[i];
    for(int i=0;i<n;i++){
        int a=0,b=0,c=0,d=0;
        for(int j=0;j<n;j++){
            if(x[i]<x[j]&&y[i]==y[j])
                a=1;
            if(x[i]>x[j]&&y[i]==y[j])
                b=1;
            if(y[i]>y[j]&&x[i]==x[j])
                c=1;
            if(y[i]<y[j]&&x[i]==x[j])
                d=1;
        }
        if(a&&b&&c&&d)s++;
    }
    cout<<s;
    return 0;
}
```
  - **作者：Yaixy (4星)**
    - **关键亮点**：代码结构清晰，将判断逻辑封装成函数，使主函数更简洁，逻辑更分明。
    - **重点代码核心实现思想**：定义函数`qwq`判断一个点相对另一个点的方向，主函数中通过两层循环，外层遍历每个点，内层调用函数判断该点与其余点的方向关系，统计符合条件的点。
```cpp
#include<bits/stdc++.h>
using namespace std;
int i,j,n,x[100005],y[100005],flag,flag2,flag3,flag4,ans;
void qwq(int i,int j)
{
    if(x[i]<x[j]&&y[i]==y[j]) flag=1;
    if(x[i]>x[j]&&y[i]==y[j]) flag2=1;
    if(x[i]==x[j]&&y[i]>y[j]) flag3=1;
    if(x[i]==x[j]&&y[i]<y[j]) flag4=1;
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(i=1;i<=n;i++) cin>>x[i]>>y[i];
    for(i=1;i<=n;i++)
    {
        flag=flag2=flag3=flag4=0;
        for(j=1;j<=n;j++) qwq(i,j);
        if(flag==1&&flag2==1&&flag3==1&&flag4==1) ans++;
    }
    cout<<ans;
    return 0;
}
```
  - **作者：jxbe6666 (4星)**
    - **关键亮点**：代码简洁，对题目条件的实现直接明了，通过简单的变量标记和循环判断完成任务。
    - **重点代码核心实现思想**：与Alex_Wei思路类似，两层循环，外层遍历每个点，内层遍历其余点判断方向，标记符合条件的方向，若四个方向都符合则答案加1。
```cpp
#include <bits/stdc++.h>
using namespace std;
int x[205], y[205], n, sum;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i] >> y[i];
    }
    for (int i = 1; i <= n; i++)
    {
        int a = 0, b = 0, c = 0, d = 0;
        for (int j = 1; j <= n; j++)
        {
            if (x[i] < x[j] && y[i] == y[j])
                a = 1;
            if (x[i] > x[j] && y[i] == y[j])
                b = 1;
            if (y[i] < y[j] && x[i] == x[j])
                c = 1;
            if (y[i] > y[j] && x[i] == x[j])
                d = 1;
        }
        if (a && b && c && d)
            sum++;
    }
    cout << sum;
    return 0;
}
```
• **最优关键思路或技巧**：利用暴力枚举，通过两层循环遍历所有点对，根据坐标关系判断方向，这种简单直接的方法在数据范围小的情况下有效且易于实现。
• **拓展**：同类型题常涉及在给定数据集合中按特定规则判断元素是否满足条件。类似套路是先明确判断规则，再根据数据范围选择合适的枚举方式，注意边界条件和代码实现的简洁性。
• **推荐题目**
  - [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)
  - [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)
  - [P1219 [USACO1.5]八皇后 Checker Challenge](https://www.luogu.com.cn/problem/P1219)
• **个人心得**：作者Waaifu_D提到读题很重要，自己因读错题以为是上下左右一格内有点才算，打了DFS导致错误，强调了准确理解题意的关键。 

---
处理用时：64.39秒