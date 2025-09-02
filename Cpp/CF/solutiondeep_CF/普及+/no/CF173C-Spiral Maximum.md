# 题目信息

# Spiral Maximum

## 题目描述

Let's consider a $ k×k $ square, divided into unit squares. Please note that $ k>=3 $ and is odd. We'll paint squares starting from the upper left square in the following order: first we move to the right, then down, then to the left, then up, then to the right again and so on. We finish moving in some direction in one of two cases: either we've reached the square's border or the square following after the next square is already painted. We finish painting at the moment when we cannot move in any direction and paint a square. The figure that consists of the painted squares is a spiral.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF173C/9bdc9b1befc556927df1bc6bdf8e832b185f9b78.png) The figure shows examples of spirals for $ k=3,5,7,9 $ . You have an $ n×m $ table, each of its cells contains a number. Let's consider all possible spirals, formed by the table cells. It means that we consider all spirals of any size that don't go beyond the borders of the table. Let's find the sum of the numbers of the cells that form the spiral. You have to find the maximum of those values among all spirals.

## 说明/提示

In the first sample the spiral with maximum sum will cover all 1's of the table.

In the second sample the spiral may cover only six 1's.

## 样例 #1

### 输入

```
6 5
0 0 0 0 0
1 1 1 1 1
0 0 0 0 1
1 1 1 0 1
1 0 0 0 1
1 1 1 1 1
```

### 输出

```
17```

## 样例 #2

### 输入

```
3 3
1 1 1
1 0 0
1 1 1
```

### 输出

```
6```

## 样例 #3

### 输入

```
6 6
-3 2 0 1 5 -1
4 -1 2 -3 0 1
-5 1 2 4 1 -2
0 -2 1 3 -1 2
3 1 4 -3 -2 0
-1 2 -1 3 1 2
```

### 输出

```
13```

# AI分析结果

### 题目内容
# 螺旋最大值

## 题目描述
考虑一个 $k×k$ 的正方形，它被划分为单位正方形。请注意，$k\geq3$ 且 $k$ 为奇数。我们从左上角的正方形开始按以下顺序涂色：首先向右移动，然后向下，接着向左，再向上，之后又向右移动，依此类推。我们在以下两种情况之一停止沿某个方向移动：要么到达正方形的边界，要么下一个正方形之后的那个正方形已经被涂色。当我们无法向任何方向移动并涂色时，就完成了涂色。由涂色正方形组成的图形是一个螺旋形。

![螺旋形示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF173C/9bdc9b1befc556927df1bc6bdf8e832b185f9b78.png) 该图展示了 $k = 3,5,7,9$ 时的螺旋形示例。你有一个 $n×m$ 的表格，其每个单元格都包含一个数字。让我们考虑由表格单元格形成的所有可能的螺旋形。这意味着我们考虑任何大小且不超出表格边界的螺旋形。让我们找出构成螺旋形的单元格数字之和。你必须在所有螺旋形中找到这些值中的最大值。

## 说明/提示
在第一个样例中，和最大的螺旋形将覆盖表格中的所有 1。
在第二个样例中，螺旋形可能只覆盖六个 1。

## 样例 #1
### 输入
```
6 5
0 0 0 0 0
1 1 1 1 1
0 0 0 0 1
1 1 1 0 1
1 0 0 0 1
1 1 1 1 1
```
### 输出
```
17
```

## 样例 #2
### 输入
```
3 3
1 1 1
1 0 0
1 1 1
```
### 输出
```
6
```

## 样例 #3
### 输入
```
6 6
-3 2 0 1 5 -1
4 -1 2 -3 0 1
-5 1 2 4 1 -2
0 -2 1 3 -1 2
3 1 4 -3 -2 0
-1 2 -1 3 1 2
```
### 输出
```
13
```

### 算法分类
动态规划

### 题解综合分析与结论
- **思路方面**：这几道题解都利用了螺旋形之间的规律来避免暴力枚举所有单元格，通过动态规划或递推的方式计算螺旋形的和。
- **算法要点**：都用到了前缀和优化对正方形区域和的计算，减少时间复杂度。同时利用螺旋形之间的嵌套关系，以前一个螺旋形的结果来推导当前螺旋形的结果。
- **解决难点**：关键在于发现不同边长螺旋形之间的数值关系，从而建立递推或状态转移方程。

### 所选的题解
- **作者：E1_de5truct0r（5星）**
  - **关键亮点**：通过观察图形得出状态转移方程 $dp_{l,i,j} = sqr_{i,j} - a_{i+1,j} + a_{i+2,j+1} + dp_{l-4,i+2,j+2}$，并利用 $l-4$ 与 $l-1 \bmod 3$ 同余的性质压缩空间，将时间复杂度优化到 $O(n^3)$，代码简洁高效。
  - **个人心得**：作者提到没有选择暴力找规律，而是通过观察图形得出结论，强调了观察和思考在解题中的重要性。
```cpp
#include <bits/stdc++.h>
using namespace std;
int dp[3][505][505],a[505][505],hp[505][505],lp[505][505];

int sqr(int l,int x,int y)
{
    int X=x+l-1,Y=y+l-1;
    int upr=hp[x][Y]-hp[x][y-1],
        lfl=lp[X][y]-lp[x-1][y],
        dor=hp[X][Y]-hp[X][y-1],
        ril=lp[X][Y]-lp[x-1][Y];
    return upr+lfl+dor+ril-a[x][y]-a[X][y]-a[x][Y]-a[X][Y];
}
int main()
{
    int n,m,ans=-1e9;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&a[i][j]);

    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            hp[i][j]=hp[i][j-1]+a[i][j];
            lp[i][j]=lp[i-1][j]+a[i][j];
            dp[1][i][j]=a[i][j];
        }

    for(int l=3;l<=min(n,m);l+=2)
        for(int i=1;i+l-1<=n;i++)
            for(int j=1;j+l-1<=m;j++)
            {
                dp[l%3][i][j]=sqr(l,i,j)-a[i+1][j]+dp[(l-1)%3][i+2][j+2];
                if(l!=3) dp[l%3][i][j]+=a[i+2][j+1];
                ans=max(ans,dp[l%3][i][j]);
            }
    printf("%d",ans);
    return 0;
}
```
核心代码实现思想：先预处理每行每列前缀和，通过 `sqr` 函数计算正方形周长和，根据状态转移方程更新 `dp` 数组，每次从 `dp[(l - 1) % 3][i + 2][j + 2]` 转移到 `dp[l % 3][i][j]`，并不断更新答案 `ans`。

- **作者：Allanljx（4星）**
  - **关键亮点**：以螺旋矩阵的中心格为基准，枚举中心点和边长，利用前缀和进行状态转移，思路清晰，代码简洁易懂。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans=-INT_MAX;
int a[505][505];
int h[505][505];
int qz[505][505];
void init()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            h[i][j]=h[i][j-1]+a[i][j];
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            qz[i][j]=a[i][j]+qz[i-1][j]+h[i][j-1];
        }
    }
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>a[i][j];
        }
    }
    init();
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            int sum=a[i][j];
            for(int k=3;k<=min(n,m);k+=2)
            {
                if(i+k/2>n||i-k/2<1||j+k/2>m||j-k/2<1)
                    break;
                sum=qz[i+k/2][j+k/2]-qz[i+k/2][j-k/2-1]-qz[i-k/2-1][j+k/2]+qz[i-k/2-1][j-k/2-1]-sum-a[i-k/2+1][j-k/2];
                ans=max(ans,sum);
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
```
核心代码实现思想：先通过 `init` 函数预处理前缀和，然后枚举螺旋矩阵的中心点 `(i, j)` 和边长 `k`，根据前缀和计算当前螺旋矩阵的和 `sum` 并更新答案 `ans`。

### 最优关键思路或技巧
观察螺旋形之间的关系，利用动态规划思想建立状态转移方程，同时结合前缀和优化对正方形区域和的计算，有效降低时间复杂度。在空间优化上，通过发现数据规律压缩状态数组维度。

### 可拓展之处
同类型题通常围绕具有特定形状或规律的图形，计算图形内元素的某种统计量（如和、最大值等）。类似算法套路是先观察图形规律，建立递推或状态转移关系，再利用前缀和等优化手段减少计算量。

### 洛谷相似题目推荐
- [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)：同样是在矩阵中寻找具有某种性质（面积最大）的子图形，需要通过动态规划来解决。
- [P1169 棋盘制作](https://www.luogu.com.cn/problem/P1169)：在棋盘上寻找最大的黑白交替的正方形和长方形，可通过动态规划结合前缀和思想求解。
- [P2704 [NOI2001] 炮兵阵地](https://www.luogu.com.cn/problem/P2704)：在给定地形的棋盘上放置炮兵，满足一定的放置规则求最大放置数，涉及状态压缩动态规划，与本题利用状态转移解决问题思路类似。 

---
处理用时：90.02秒