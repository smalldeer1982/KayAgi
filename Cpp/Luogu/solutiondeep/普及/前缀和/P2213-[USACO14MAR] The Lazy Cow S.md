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

本题的核心在于如何在给定的网格中找到最佳位置，使得在有限的步数内能够覆盖最多的青草。由于网格大小和步数的限制，直接暴力枚举的复杂度较高，因此需要借助前缀和等优化手段来减少计算量。

从题解中可以看出，主要有以下几种思路：
1. **旋转矩阵法**：通过将矩阵旋转45度，将问题转化为更容易处理的形式，利用二维前缀和快速计算区域和。
2. **前缀和法**：利用行前缀和或二维前缀和，快速计算任意矩形区域的和，结合菱形区域的边界处理，实现高效计算。
3. **暴力枚举法**：直接枚举每个点，计算其周围菱形区域的和，虽然复杂度较高，但由于数据范围较小，仍能通过。

### 所选高星题解

#### 1. 作者：yxy666 (★★★★★)
- **关键亮点**：通过旋转矩阵将问题转化为更易处理的形式，利用二维前缀和快速计算区域和，思路新颖且高效。
- **代码核心思想**：
  ```cpp
  for (int i=1;i<=N;i++)
  for (int j=1;j<=N;j++) mp[i+j-1][N-i+j]=read();
  for (int i=1;i<2*N;i++)
  for (int j=1;j<2*N;j++) F[i][j]=F[i-1][j]+F[i][j-1]-F[i-1][j-1]+mp[i][j];
  ```
  通过旋转矩阵后，使用二维前缀和快速计算任意矩形区域的和。

#### 2. 作者：Ajwallet (★★★★☆)
- **关键亮点**：利用行前缀和的思想，结合边界处理，实现高效计算，代码简洁易懂。
- **代码核心思想**：
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
  通过行前缀和快速计算每一行的区域和，结合边界处理，实现高效计算。

#### 3. 作者：moosssi (★★★★☆)
- **关键亮点**：利用行前缀和，分别处理正三角形和倒三角形的区域和，思路清晰且代码简洁。
- **代码核心思想**：
  ```cpp
  for(int i=1;i<=n;i++){
      for(int j=1;j<=n;j++){
          int sum=0,d=0;
          for(int l=i-k;l<=i;l++,d++){
              if(l<1)continue;
              int r2=min(n,j+d);
              int r1=max(1,j-d);
              sum+=h[l][r2]-h[l][r1-1];
          }
          d-=2;
          for(int l=i+1;l<=min(i+k,n);l++,d--){
              int r2=min(n,j+d);
              int r1=max(1,j-d);
              sum+=h[l][r2]-h[l][r1-1];			
          }
          ans=max(ans,sum);
      }
  }
  ```
  通过行前缀和分别处理正三角形和倒三角形的区域和，结合边界处理，实现高效计算。

### 最优关键思路与技巧
- **旋转矩阵法**：通过旋转矩阵将问题转化为更易处理的形式，利用二维前缀和快速计算区域和，思路新颖且高效。
- **前缀和法**：利用行前缀和或二维前缀和，快速计算任意矩形区域的和，结合菱形区域的边界处理，实现高效计算。

### 可拓展之处
- **类似问题**：可以拓展到其他形状的区域和计算，如圆形、三角形等。
- **算法套路**：前缀和、二维前缀和、矩阵旋转等技巧在处理区域和问题时非常有用，可以举一反三。

### 推荐题目
1. [P1719 最大加权矩形](https://www.luogu.com.cn/problem/P1719)
2. [P1880 [NOI1995]石子合并](https://www.luogu.com.cn/problem/P1880)
3. [P2280 [HNOI2003]激光炸弹](https://www.luogu.com.cn/problem/P2280)

### 个人心得摘录
- **yxy666**：通过旋转矩阵将问题转化为更易处理的形式，思路新颖且高效。
- **Ajwallet**：利用行前缀和的思想，结合边界处理，实现高效计算，代码简洁易懂。
- **moosssi**：利用行前缀和，分别处理正三角形和倒三角形的区域和，思路清晰且代码简洁。

---
处理用时：28.97秒