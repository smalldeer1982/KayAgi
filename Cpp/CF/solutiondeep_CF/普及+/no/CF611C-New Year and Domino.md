# 题目信息

# New Year and Domino

## 题目描述

They say "years are like dominoes, tumbling one after the other". But would a year fit into a grid? I don't think so.

Limak is a little polar bear who loves to play. He has recently got a rectangular grid with $ h $ rows and $ w $ columns. Each cell is a square, either empty (denoted by '.') or forbidden (denoted by '\#'). Rows are numbered $ 1 $ through $ h $ from top to bottom. Columns are numbered $ 1 $ through $ w $ from left to right.

Also, Limak has a single domino. He wants to put it somewhere in a grid. A domino will occupy exactly two adjacent cells, located either in one row or in one column. Both adjacent cells must be empty and must be inside a grid.

Limak needs more fun and thus he is going to consider some queries. In each query he chooses some rectangle and wonders, how many way are there to put a single domino inside of the chosen rectangle?

## 说明/提示

A red frame below corresponds to the first query of the first sample. A domino can be placed in 4 possible ways.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF611C/f3a65ee4610730ba07c0a0557d0738988b956aa6.png)

## 样例 #1

### 输入

```
5 8
....#..#
.#......
##.#....
##..#.##
........
4
1 1 2 3
4 1 4 1
1 2 4 5
2 5 5 8
```

### 输出

```
4
0
10
15
```

## 样例 #2

### 输入

```
7 39
.......................................
.###..###..#..###.....###..###..#..###.
...#..#.#..#..#.........#..#.#..#..#...
.###..#.#..#..###.....###..#.#..#..###.
.#....#.#..#....#.....#....#.#..#..#.#.
.###..###..#..###.....###..###..#..###.
.......................................
6
1 1 3 20
2 10 6 30
2 10 7 30
2 2 7 7
1 7 7 7
1 8 7 8
```

### 输出

```
53
89
120
23
0
2
```

# AI分析结果

### 题目内容
#### New Year and Domino
#### 题目描述
人们说：“岁月就像多米诺骨牌，一个接一个地倒下。” 但是一年能放进一个网格里吗？我不这么认为。

利马克是一只可爱的小北极熊，它喜欢玩耍。最近它得到了一个有 $h$ 行和 $w$ 列的矩形网格。每个单元格都是一个正方形，要么是空的（用 '.' 表示），要么是禁止的（用 '#' 表示）。行从顶部到底部编号为 $1$ 到 $h$。列从左到右编号为 $1$ 到 $w$。

此外，利马克有一块多米诺骨牌。它想把骨牌放在网格的某个地方。一块多米诺骨牌将恰好占据两个相邻的单元格，可以在同一行或同一列。这两个相邻的单元格都必须是空的，并且必须在网格内。

利马克想要更多乐趣，所以它会考虑一些查询。在每个查询中，它选择一个矩形区域，并想知道，有多少种方法可以将一块多米诺骨牌放在所选的矩形区域内？
#### 说明/提示
下面的红色框架对应第一个样例中的第一个查询。多米诺骨牌可以有 4 种放置方法。
![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF611C/f3a65ee4610730ba07c0a0557d0738988b956aa6.png)
#### 样例 #1
##### 输入
```
5 8
....#..#
.#......
##.#....
##..#.##
........
4
1 1 2 3
4 1 4 1
1 2 4 5
2 5 5 8
```
##### 输出
```
4
0
10
15
```
#### 样例 #2
##### 输入
```
7 39
.......................................
.###..###..#..###.....###..###..#..###.
...#..#.#..#..#.........#..#.#..#..#...
.###..#.#..#..###.....###..#.#..#..###.
.#....#.#..#....#.....#....#.#..#..#.#.
.###..###..#..###.....###..###..#..###.
.......................................
6
1 1 3 20
2 10 6 30
2 10 7 30
2 2 7 7
1 7 7 7
1 8 7 8
```
##### 输出
```
53
89
120
23
0
2
```

### 算法分类
前缀和

### 题解综合分析与结论
所有题解核心思路均是利用前缀和优化计算多米诺骨牌在给定矩形区域内的放置方案数。通过对每个单元格进行分析，判断其相邻单元格是否为空，以此确定该单元格对多米诺骨牌放置方案数的贡献值，再利用二维前缀和进行预处理，从而实现快速查询。不同题解在具体实现细节上略有差异，如贡献值的计算方式、前缀和数组的处理以及查询时边界条件的处理等。

### 所选的题解
- **作者：Akoasm_X (5星)**
  - **关键亮点**：思路清晰，详细阐述了普通二维前缀和在本题中的问题，并提出将横向贡献和纵向贡献分开计算前缀和的解决方案，代码简洁明了，注释详细。
  - **个人心得**：无
  ```cpp
  int calc(int a,int b,int c,int d)
  {
      int ans = 0;
      a++;
      ans += sum1[c][d] - sum1[a - 1][d] - sum1[c][b - 1] + sum1[a - 1][b - 1];
      b++,a--;
      ans += sum2[c][d] - sum2[a - 1][d] - sum2[c][b - 1] + sum2[a - 1][b - 1];
      return ans;
  }

  int main()
  {
      scanf("%d%d",&n,&m);
      for(int i = 1;i <= n;i++)
          scanf("%s",mp[i]+1);
      for(int i = 1;i <= n;i++)
      {
          for(int j = 1;j <= m;j++)
          {
              sum1[i][j] = sum1[i][j - 1] + sum1[i - 1][j] - sum1[i - 1][j - 1];
              sum2[i][j] = sum2[i][j - 1] + sum2[i - 1][j] - sum2[i - 1][j - 1];
              if(mp[i][j]=='.')
              {
                  if(mp[i - 1][j]=='.')
                      sum1[i][j]++;//纵向贡献 
                  if(mp[i][j - 1]=='.')
                      sum2[i][j]++;//横向贡献 
              }
          }
      }
      int T;
      scanf("%d",&T);
      while(T--)
      {
          int a,b,c,d;
          scanf("%d%d%d%d",&a,&b,&c,&d);
          printf("%d\n",calc(a,b,c,d));
      }
      return 0;
  }
  ```
- **作者：lovely_hyzhuo (4星)**
  - **关键亮点**：先介绍二维前缀和的基本算法，再指出本题不能直接用普通二维前缀和的原因，通过分开计算横向和纵向贡献解决问题，代码结构清晰。
  - **个人心得**：无
  ```cpp
  void solve()
  {
      int a,b,c,d;
      cin>>a>>b>>c>>d;
      int ans = 0;
      a++;
      ans += sum1[c][d] - sum1[a - 1][d] - sum1[c][b - 1] + sum1[a - 1][b - 1];
      b++,a--;
      ans += sum2[c][d] - sum2[a - 1][d] - sum2[c][b - 1] + sum2[a - 1][b - 1];
      cout<<ans<<"\n";
  }

  int main()
  {
      int n,m;
      cin>>n>>m;
      for(int i = 1;i <= n;i++)
          for(int j = 1;j <= m;j++)
              cin>>c[i][j];
      for(int i = 1;i <= n;i++)
      {
          for(int j = 1;j <= m;j++)
          {
              if(c[i][j]==c[i - 1][j]&&c[i - 1][j]=='.')
                  sum1[i][j]++;
              if(c[i][j]==c[i][j - 1]&&c[i][j - 1]=='.')
                  sum2[i][j]++;
              sum1[i][j]+=sum1[i][j - 1]+sum1[i - 1][j] - sum1[i - 1][j - 1];
              sum2[i][j]+=sum2[i][j - 1]+sum2[i - 1][j] - sum2[i - 1][j - 1];
          }
      }
      int q;
      cin>>q;
      while(q--)
          solve();
      return 0;
  }
  ```
- **作者：_smart_stupid_ (4星)**
  - **关键亮点**：详细说明了前缀和数组的含义以及计算公式，对计算摆放方法时边界条件的处理原因解释清晰，代码逻辑连贯。
  - **个人心得**：无
  ```cpp
  for(int i = 1;i <= h;i++){
      for(int j = 1;j <= w;j++){
          sum1[i][j] = sum1[i][j - 1] + sum1[i - 1][j] - sum1[i - 1][j - 1];
          sum2[i][j] = sum2[i][j - 1] + sum2[i - 1][j] - sum2[i - 1][j - 1];
          if(a[i][j]=='.')
          {
              if(a[i - 1][j]=='.')
                  sum1[i][j]++;
              if(a[i][j - 1]=='.')
                  sum2[i][j]++;
          }
      }
  }
  scanf("%d",&q);
  for(int i = 1;i <= q;i++){
      int x1,y1,x2,y2;
      scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
      int ans = 0;
      ans += sum1[x2][y2] - sum1[x1][y2] - sum1[x2][y1 - 1] + sum1[x1][y1 - 1];
      ans += sum2[x2][y2] - sum2[x1 - 1][y2] - sum2[x2][y1] + sum2[x1 - 1][y1];
      printf("%d\n",ans);
  }
  ```

### 最优关键思路或技巧
将多米诺骨牌的横向和纵向放置情况分开处理，分别计算其贡献值并构建二维前缀和数组。在查询时，利用前缀和数组相减得到指定矩形区域内横向和纵向放置多米诺骨牌的方案数，相加即为最终结果。这种方法避免了直接使用普通二维前缀和可能出现的重复计算或漏算问题。

### 拓展思路
同类型题目通常围绕矩阵区域内特定形状（如 $2\times2$ 方块等）的放置方案数计算，或者在矩阵上进行区域和查询等。类似算法套路是根据题目条件，分析每个单元格对目标结果的贡献，利用前缀和、差分等手段优化计算。

### 推荐题目
- [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)：在给定矩阵中找最大全为1的正方形，与本题类似，需分析每个单元格对结果的贡献并利用动态规划或前缀和思想求解。
- [P2004 领地选择](https://www.luogu.com.cn/problem/P2004)：在矩形区域内找子矩形满足特定条件，同样可借助前缀和优化计算。
- [P1719 最大加权矩形](https://www.luogu.com.cn/problem/P1719)：在加权矩阵中找和最大的子矩形，也是前缀和相关应用。 

---
处理用时：75.89秒