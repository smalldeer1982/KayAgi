# 题目信息

# Boboniu Plays Chess

## 题目描述

Boboniu likes playing chess with his employees. As we know, no employee can beat the boss in the chess game, so Boboniu has never lost in any round.

You are a new applicant for his company. Boboniu will test you with the following chess question:

Consider a $ n\times m $ grid (rows are numbered from $ 1 $ to $ n $ , and columns are numbered from $ 1 $ to $ m $ ). You have a chess piece, and it stands at some cell $ (S_x,S_y) $ which is not on the border (i.e. $ 2 \le S_x \le n-1 $ and $ 2       \le S_y \le m-1 $ ).

From the cell $ (x,y) $ , you can move your chess piece to $ (x,y') $ ( $ 1\le y'\le m, y' \neq y $ ) or $ (x',y) $ ( $ 1\le x'\le n, x'\neq x $ ). In other words, the chess piece moves as a rook. From the cell, you can move to any cell on the same row or column.

Your goal is to visit each cell exactly once. Can you find a solution?

Note that cells on the path between two adjacent cells in your route are not counted as visited, and it is not required to return to the starting point.

## 说明/提示

Possible routes for two examples:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1395B/c064004f0504fcb32a549da42e8ef5b0adb837cd.png)

## 样例 #1

### 输入

```
3 3 2 2```

### 输出

```
2 2
1 2
1 3
2 3
3 3
3 2
3 1
2 1
1 1```

## 样例 #2

### 输入

```
3 4 2 2```

### 输出

```
2 2
2 1
2 3
2 4
1 4
3 4
3 3
3 2
3 1
1 1
1 2
1 3```

# AI分析结果

### 题目内容
# Boboniu下象棋

## 题目描述
Boboniu喜欢和他的员工下象棋。如我们所知，没有员工能在象棋比赛中打败老板，所以Boboniu在任何一轮比赛中都从未输过。

你是他公司的一名新申请者。Boboniu将用以下象棋问题来测试你：

考虑一个$n×m$的网格（行从1到$n$编号，列从1到$m$编号）。你有一个棋子，它位于某个不在边界上的单元格$(S_x,S_y)$（即$2 \leq S_x \leq n - 1$且$2 \leq S_y \leq m - 1$）。

从单元格$(x,y)$，你可以将你的棋子移动到$(x,y')$（$1\leq y'\leq m$，$y' \neq y$）或$(x',y)$（$1\leq x'\leq n$，$x'\neq x$）。换句话说，这个棋子的移动方式像国际象棋中的车。从这个单元格，你可以移动到同一行或同一列的任何单元格。

你的目标是恰好访问每个单元格一次。你能找到一种解决方案吗？

注意，你路线中两个相邻单元格之间路径上的单元格不被视为已访问，并且不要求回到起始点。

## 说明/提示
两个示例的可能路线：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1395B/c064004f0504fcb32a549da42e8ef5b0adb837cd.png)

## 样例 #1
### 输入
```
3 3 2 2
```
### 输出
```
2 2
1 2
1 3
2 3
3 3
3 2
3 1
2 1
1 1
```

## 样例 #2
### 输入
```
3 4 2 2
```
### 输出
```
2 2
2 1
2 3
2 4
1 4
3 4
3 3
3 2
3 1
1 1
1 2
1 3
```

### 算法分类
构造

### 题解综合分析与结论
这些题解主要分为构造法和搜索法两类思路。构造法通过设计特定的行走顺序来遍历棋盘，如蛇形走位、按行遍历等；搜索法则是利用深度优先搜索（DFS），从起始点出发，向四个方向探索，标记已访问的单元格，直到遍历完所有单元格。构造法的优点在于代码简洁高效，时间复杂度低；搜索法相对直观，但可能在效率上稍逊一筹，尤其是在数据规模较大时。

### 所选的题解
 - **作者：—维尼— (5星)**
    - **关键亮点**：提出按奇偶行交替从左往右和从右往左遍历的构造方法，思路清晰，代码简洁高效。
    - **重点代码**：
```cpp
for(int i=1;i<=n;i++)
{
    if(i%2){
        for(int j=1;j<=m;j++)
        cout<<(i+x1-2)%n+1<<" "<<(j+y1-2)%m+1<<endl;
    }
    else{
        for(int j=m;j>=1;j--){
            cout<<(i+x1-2)%n+1<<" "<<(j+y1-2)%m+1<<endl;
        }
    }   
}
```
    - **核心实现思想**：根据行号的奇偶性，决定该行是从左往右还是从右往左遍历，通过取模运算将坐标转换为符合题目要求的形式输出。
 - **作者：引领天下 (4星)**
    - **关键亮点**：先处理起始行，然后对上下部分的行采用蛇形走位的构造方式，逻辑清晰，易于理解。
    - **重点代码**：
```cpp
printf("%d %d\n",sx,sy);
for(register int i=sx;i<=n;i++)if(!last){
    for(register int j=1;j<=m;j++)if(i!=sx||j!=sy)printf("%d %d\n",i,j),last=1;
}
else for(register int j=m;j>=1;j--)if(i!=sx||j!=sy)printf("%d %d\n",i,j),last=0;
for(int i=1;i<sx;i++){
    if(!last)for(register int j=1;j<=m;j++)printf("%d %d\n",i,j),last=1;
    else for(register int j=m;j>=1;j--)printf("%d %d\n",i,j),last=0;
}
```
    - **核心实现思想**：先输出起始点，然后对起始行及上下部分的行，通过一个布尔变量`last`控制是从左往右还是从右往左遍历，并跳过起始点。
 - **作者：KSToki (4星)**
    - **关键亮点**：先走完起始行，再对其他行按特定顺序遍历，通过变量记录行走方向，代码简洁明了。
    - **重点代码**：
```cpp
cout<<x<<" "<<y<<endl;
for(register int i=1;i<=m;++i)
    if(i!=y)
        cout<<x<<" "<<i<<endl;
int op=1;
for(register int i=1;i<x;++i,op^=1)
{
    if(op)
        for(register int j=m;j>0;--j)
            cout<<i<<" "<<j<<endl;
    else
        for(register int j=1;j<=m;++j)
            cout<<i<<" "<<j<<endl;
}
for(register int i=x+1;i<=n;++i,op^=1)
{
    if(op)
        for(register int j=m;j>0;--j)
            cout<<i<<" "<<j<<endl;
    else
        for(register int j=1;j<=m;++j)
            cout<<i<<" "<<j<<endl;
}
```
    - **核心实现思想**：先输出起始点并遍历完起始行，然后通过`op`变量异或操作切换每行的遍历方向，实现对整个棋盘的遍历。

### 最优关键思路或技巧
构造法中，通过合理设计行走顺序，利用奇偶行或特定的蛇形走位方式，能高效地遍历整个棋盘，避免了复杂的搜索过程，降低了时间复杂度。这种构造思维在解决此类遍历问题时非常有效，通过对问题特性的分析，找到一种固定的、可重复的模式来完成任务。

### 拓展与同类型题
此类题目属于构造类问题，通常需要根据给定的规则和条件，设计出满足要求的方案。类似的算法套路还包括根据题目条件找规律、利用数学性质进行构造等。同类型题可参考：
 - [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)
 - [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
 - [P1339 热浪](https://www.luogu.com.cn/problem/P1339)

### 个人心得摘录与总结
部分作者提到这道题相对简单，在读懂题意后，根据数据范围能快速确定解法。有的通过尝试不同思路，如一开始误以为是一笔画问题，最终找到正确解法，这提示在解题时要准确理解题意，灵活调整思路。 

---
处理用时：49.46秒