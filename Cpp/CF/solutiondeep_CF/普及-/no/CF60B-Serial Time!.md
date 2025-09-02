# 题目信息

# Serial Time!

## 题目描述

The Cereal Guy's friend Serial Guy likes to watch soap operas. An episode is about to start, and he hasn't washed his plate yet. But he decided to at least put in under the tap to be filled with water. The plate can be represented by a parallelepiped $ k×n×m $ , that is, it has $ k $ layers (the first layer is the upper one), each of which is a rectangle $ n×m $ with empty squares ('.') and obstacles ('#'). The water can only be present in the empty squares. The tap is positioned above the square $ (x,y) $ of the first layer, it is guaranteed that this square is empty. Every minute a cubical unit of water falls into the plate. Find out in how many minutes the Serial Guy should unglue himself from the soap opera and turn the water off for it not to overfill the plate. That is, you should find the moment of time when the plate is absolutely full and is going to be overfilled in the next moment.

Note: the water fills all the area within reach (see sample 4). Water flows in each of the 6 directions, through faces of $ 1×1×1 $ cubes.

## 样例 #1

### 输入

```
1 1 1

.

1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 1 1

.

#

1 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
2 2 2

.#
##

..
..

1 1
```

### 输出

```
5
```

## 样例 #4

### 输入

```
3 2 2

#.
##

#.
.#

..
..

1 2
```

### 输出

```
7
```

## 样例 #5

### 输入

```
3 3 3

.#.
###
##.

.##
###
##.

...
...
...

1 1
```

### 输出

```
13
```

# AI分析结果

【题目内容（中文重写）】
# 注水时刻！

## 题目描述
谷物男孩（Cereal Guy）的朋友连续剧男孩（Serial Guy）喜欢看肥皂剧。一集电视剧即将开播，而他还没洗盘子。但他决定至少把盘子放在水龙头下让水注满。盘子可以用一个 $k×n×m$ 的长方体来表示，即它有 $k$ 层（第一层在最上面），每层都是一个 $n×m$ 的矩形，其中包含空方块（用 '.' 表示）和障碍物（用 '#' 表示）。水只能存在于空方块中。水龙头位于第一层的 $(x,y)$ 方块上方，保证该方块是空的。每分钟有一个单位体积的水落入盘子中。请找出连续剧男孩应该在几分钟后从肥皂剧中抽身并关掉水龙头，以免水溢出盘子。也就是说，你需要找出盘子刚好被完全注满，且下一刻就会溢出的时刻。

注意：水会填满所有可达的区域（见样例 4）。水会通过 $1×1×1$ 立方体的面，向六个方向流动。

## 样例 #1
### 输入
```
1 1 1
.
1 1
```
### 输出
```
1
```

## 样例 #2
### 输入
```
2 1 1
.
#
1 1
```
### 输出
```
1
```

## 样例 #3
### 输入
```
2 2 2
.#
##
..
..
1 1
```
### 输出
```
5
```

## 样例 #4
### 输入
```
3 2 2
#.
##
#.
.#
..
..
1 2
```
### 输出
```
7
```

## 样例 #5
### 输入
```
3 3 3
.#.
###
##.
.##
###
##.
...
...
...
1 1
```
### 输出
```
13
```

【算法分类】
深度优先搜索 DFS、广度优先搜索 BFS

【综合分析与结论】
这些题解的核心思路都是通过搜索算法来计算从水龙头位置开始，水能够到达的所有空方块的数量。大部分题解使用深度优先搜索（DFS），也有一题使用广度优先搜索（BFS）。

### 思路对比
- **DFS 题解**：通过递归的方式，从起始点开始向六个方向（上、下、前、后、左、右）进行搜索，标记已访问的方块，直到所有可达的方块都被访问。
- **BFS 题解**：使用队列来实现广度优先搜索，从起始点开始，将可达的方块加入队列，依次处理队列中的元素，直到队列为空。

### 算法要点
- **方向数组**：为了方便向六个方向进行搜索，所有题解都使用了方向数组来表示六个方向的偏移量。
- **标记访问**：为了避免重复访问同一个方块，所有题解都对已访问的方块进行了标记。

### 解决难点
- **三维空间处理**：与普通的二维搜索问题不同，本题需要处理三维空间，需要注意坐标的范围和边界条件。
- **方向控制**：水可以向六个方向流动，需要正确处理这六个方向的搜索。

### 评分
- Tune_：4星。思路清晰，代码简洁易懂，对洪水算法的解释有助于理解。
- Fearliciz：3星。思路正确，但代码中使用了 `vis` 数组标记访问，相对复杂。
- HyGeoIceFairy：3星。代码实现基本正确，但边界处理和输入输出的细节需要注意。
- 天亮codekiller：3星。使用 BFS 实现，对输入输出进行了优化，但代码结构稍显复杂。
- WinterRain208：3星。代码简洁，但对边界的处理使用了 `memset` 初始化，可能会增加不必要的开销。
- ahawzlc：3星。思路清晰，对搜索过程的解释详细，但代码中使用了 `check` 函数，增加了代码的复杂度。

【所选题解】
- Tune_（4星）
  - 关键亮点：思路清晰，代码简洁，使用 DFS 实现，对洪水算法的解释有助于理解。
  - 个人心得：第一次看到这题蒙了，仔细一看发现是洪水算法的扩展，只是多了一个层的参数和两个方向。

【重点代码】
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,ans=0;
int dx[6]={0,0,0,0,1,-1};//方向数组
int dy[6]={0,0,1,-1,0,0};
int dh[6]={1,-1,0,0,0,0}; 
char a[15][15][15];
void dfs(int h,int x,int y)//发洪水啦~
{
    ans++;//更新答案
    a[h][x][y]='#';//标记一下
    for(int i=0;i<6;i++)
    {
        int hh=h+dh[i],xx=x+dx[i],yy=y+dy[i];
        if(hh<=k&&hh>=1&&xx>=1&&xx<=n&&yy>=1&&yy<=m&&a[hh][xx][yy]=='.')//不能超界，且走得通
            dfs(hh,xx,yy);
    }
}
int main()
{
    cin>>k>>n>>m;
    for(int i=1;i<=k;i++)
        for(int j=1;j<=n;j++)
            for(int k=1;k<=m;k++)
                cin>>a[i][j][k];//输入
    int xs,ys;
    cin>>xs>>ys;
    dfs(1,xs,ys);//从起始点开始
    cout<<ans;//输出答案
    return 0;
}
```
【核心实现思想】
1. 定义方向数组 `dx`, `dy`, `dh` 来表示六个方向的偏移量。
2. 使用 DFS 函数 `dfs` 从起始点开始搜索，将可达的方块标记为已访问，并更新答案。
3. 在 `main` 函数中，读入输入数据，调用 `dfs` 函数进行搜索，最后输出答案。

【可拓展之处】
同类型题或类似算法套路：
- 二维或三维的连通块问题，如计算岛屿数量、最大岛屿面积等。
- 迷宫问题，求从起点到终点的最短路径或所有路径。

【推荐题目】
1. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
2. [P1451 求细胞数量](https://www.luogu.com.cn/problem/P1451)
3. [P1746 离开中山路](https://www.luogu.com.cn/problem/P1746)

【个人心得】
- Tune_：第一次看到这题蒙了，仔细一看发现是洪水算法的扩展，只是多了一个层的参数和两个方向。
- 天亮codekiller：使用 BFS 时，在入队时标记可避免 TLE 和 MLE，这是血泪的教训。 

---
处理用时：41.67秒