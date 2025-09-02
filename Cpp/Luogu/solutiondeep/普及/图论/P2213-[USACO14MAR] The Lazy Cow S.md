# 题目信息

# [USACO14MAR] The Lazy Cow S

## 题目描述

It's a hot summer day, and Bessie the cow is feeling quite lazy.  She wants

to locate herself at a position in her field so that she can reach as much

delicious grass as possible within only a short distance.


The field Bessie inhabits is described by an N by N grid of square cells

(1 <= N <= 400).  The cell in row r and column c (1 <= r,c <= N) contains

G(r,c) units of grass (0 <= G(r,c) <= 1000).  From her initial square in

the grid, Bessie is only willing to take up to K steps (0 <= K <= 2\*N).

Each step she takes moves her to a cell that is directly north, south,

east, or west of her current location.


For example, suppose the grid is as follows, where (B) describes Bessie's

```cpp
50    5     25*   6     17    
14    3*    2*    7*    21    
99*   10*   1*(B) 2*    80*    
8     7*    5*    23*   11   
10    0     78*   1     9        
```

initial position (here, in row 3, column 3):

If K=2, then Bessie can only reach the locations marked with \*s.

Please help Bessie determine the maximum amount of grass she can reach, if

she chooses the best possible initial location in the grid.

奶牛贝茜非常懒惰，她希望在她的地盘内找到一点最佳位置居住，以便在有限的步数内可以吃到尽量多的青草。

她的地盘是一个 $N \times N(1\le N \le 400)$ 的矩阵，第 $r$ 行 $c$ 列包含 $G(r,c)$ 单位的青草 $(0 \le G(r,c) \le 1000)$。从她的居住点，她最多愿意走 $K$ 步 $(0 \le K \le 2 \times N)$，每一步她可以走到上与她相邻的某个格子。

## 说明/提示

OUTPUT DETAILS:


In the example above, Bessie can reach 342 total units of grass if she

locates herself in the middle of the grid.


Source: USACO 2014 March Contest, Silver


## 样例 #1

### 输入

```
5 2
50 5 25 6 17
14 3 2 7 21
99 10 1 2 80
8 7 5 23 11
10 0 78 1 9
```

### 输出

```
342```

# AI分析结果

### 综合分析与结论
这些题解主要围绕计算奶牛在给定步数内从不同起始位置能吃到的最大青草量展开，核心在于处理菱形区域的草量统计。算法复杂度主要有 $O(n^2)$ 和 $O(n^3)$ 两种。
- **思路对比**：
    - **旋转法（yxy666）**：将矩阵旋转 45 度，把菱形区域转化为矩形区域，利用二维前缀和计算。
    - **前缀和结合边界处理（Ajwallet 等）**：使用行前缀和，通过枚举每个点，计算以该点为中心的菱形区域内的草量总和。
    - **线性转移法（Expecto）**：每个点线性转移上个点的值，扣掉和加上相应斜行的草量。
- **算法要点**：
    - **前缀和**：多数题解使用前缀和优化计算区间和，减少重复计算。
    - **边界处理**：由于奶牛活动范围可能超出矩阵边界，需要仔细处理边界情况。
- **解决难点**：
    - **菱形区域计算**：旋转法将其转化为矩形计算，其他方法则通过数学公式确定菱形边界。
    - **边界判断**：各题解都采用了取最大最小值的方式确保不越界。

### 所选题解
- **作者：yxy666（5 星）**
    - **关键亮点**：思路独特，通过旋转矩阵将复杂的菱形区域计算转化为简单的矩形区域计算，使用二维前缀和优化，复杂度为 $O(n^2)$。
    - **核心代码**：
```cpp
for (int i=1;i<=N;i++)
    for (int j=1;j<=N;j++) mp[i+j-1][N-i+j]=read();
for (int i=1;i<2*N;i++)
    for (int j=1;j<2*N;j++) F[i][j]=F[i-1][j]+F[i][j-1]-F[i-1][j-1]+mp[i][j];
for (int i=1;i<=N;i++)
    for (int j=1;j<=N;j++){
        int now_x=i+j-1,now_y=N-i+j;
        int x_l=max(0,now_x-K-1),y_l=max(0,now_y-K-1),x_r=min(2*N-1,now_x+K),y_r=min(2*N-1,now_y+K);
        ans=max(ans,F[x_r][y_r]-F[x_l][y_r]-F[x_r][y_l]+F[x_l][y_l]);
    }
```
    - **核心思想**：先将矩阵旋转 45 度，再计算旋转后矩阵的二维前缀和，最后枚举原矩阵的每个点，计算以该点为中心的旋转后矩形区域的草量总和。

- **作者：Ajwallet（4 星）**
    - **关键亮点**：思路清晰，使用行前缀和优化，通过处理边界情况计算菱形区域草量，复杂度为 $O(n^3)$。
    - **核心代码**：
```cpp
r(i,1,n)
    r(j,1,n)
    {
        now=0;
        r(u,i-k,i+k)
        {
            if (u<1) u=1;if(u>n) break;
            int uu=i-u>0?i-u:u-i;int uuu=j+k-uu>n?n:j+k-uu;int uuuu=j-k+uu<0?1:j-k+uu;
            now+=h[u][uuu]-h[u][uuuu-1];
        }
        ans=max(ans,now);
    }
```
    - **核心思想**：先计算每行的前缀和，然后枚举每个点，对于每个点，枚举其能到达的行，根据与该点的行数差确定该行能到达的左右边界，使用前缀和计算该行草量并累加。

- **作者：一只野生蒟蒻（4 星）**
    - **关键亮点**：思路简单易懂，适合初学者，使用行前缀和计算菱形区域草量，复杂度为 $O(n^3)$。
    - **核心代码**：
```cpp
int sum(int x,int y)
{
    int t=0;
    for (int i=x-k;i<=x+k;i++)
        if (i>=1&&i<=n)
        {
            int l,r;
            if (i<=x)
            {
                l=y-(i-x+k);
                r=y+(i-x+k);
            }
            else
            {
                l=y-(x+k-i);
                r=y+(x+k-i);
            }
            if (l<1) l=1;
            if (r>n) r=n;
            t+=s[i][r]-s[i][l-1];
        }
    return t;
}
for (int i=1;i<=n;i++)
    for (int j=1;j<=n;j++)
        ans=max(ans,sum(i,j));
```
    - **核心思想**：定义 `sum` 函数计算以某点为中心的菱形区域草量，通过枚举能到达的行，根据与该点的行数差确定该行能到达的左右边界，使用前缀和计算该行草量并累加，最后枚举每个点，取最大值。

### 最优关键思路或技巧
- **旋转矩阵**：将复杂的菱形区域计算转化为矩形区域计算，简化问题。
- **前缀和优化**：减少区间和的重复计算，提高效率。
- **边界处理技巧**：使用 `max` 和 `min` 函数确保计算不越界。

### 可拓展之处
同类型题如计算特定形状（如圆形、六边形等）区域内的元素和，可借鉴本题的前缀和优化和边界处理思路。类似算法套路包括通过坐标变换简化区域计算，以及使用前缀和优化区间查询。

### 推荐题目
- [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)：考察二维前缀和与动态规划，计算矩阵中最大正方形的面积。
- [P2004 领地选择](https://www.luogu.com.cn/problem/P2004)：使用二维前缀和计算指定大小矩形区域内的元素和，找出最大值。
- [P3397 地毯](https://www.luogu.com.cn/problem/P3397)：涉及二维差分和前缀和的应用，计算矩阵中每个点被覆盖的次数。

### 个人心得摘录与总结
- **一只野生蒟蒻**：表示理解不了旋转矩阵的 $O(n^2)$ 算法，采用了简单的 $O(n^3)$ 算法，认为该算法好想好写，适合初学者。总结：对于复杂算法理解困难时，可先采用简单易懂的算法解决问题。
- **Expecto**：提到不小心被卡了一个点，注意当 $k = 2n$ 时直接输出总和。总结：做题时要仔细考虑特殊情况，避免因边界情况导致错误。

---
处理用时：44.04秒