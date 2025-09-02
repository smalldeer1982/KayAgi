# 题目信息

# Umka and a Long Flight

## 题目描述

The girl Umka loves to travel and participate in math olympiads. One day she was flying by plane to the next olympiad and out of boredom explored a huge checkered sheet of paper.

Denote the $ n $ -th Fibonacci number as $ F_n = \begin{cases} 1, & n = 0; \\ 1, & n = 1; \\ F_{n-2} + F_{n-1}, & n \ge 2. \end{cases} $

A checkered rectangle with a height of $ F_n $ and a width of $ F_{n+1} $ is called a Fibonacci rectangle of order $ n $ .

Umka has a Fibonacci rectangle of order $ n $ . Someone colored a cell in it at the intersection of the row $ x $ and the column $ y $ .

It is necessary to cut this rectangle exactly into $ n+1 $ squares in such way that

- the painted cell was in a square with a side of $ 1 $ ;
- there was at most one pair of squares with equal sides;
- the side of each square was equal to a Fibonacci number.

Will Umka be able to cut this rectangle in that way?

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1811D/e5f4a8a6969129eb7406262bfa57aeda28c2a7af.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1811D/f9a9f5019cb436c08d516ca2337b43e44d86aeca.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1811D/b75cbdcea405d71b913c844c613b79782c601576.png) The first, third and fourth test cases.

## 样例 #1

### 输入

```
12
1 1 1
2 1 2
3 1 4
3 3 2
4 4 6
4 3 3
5 6 5
5 4 12
5 2 12
4 2 1
1 1 2
44 758465880 1277583853```

### 输出

```
YES
NO
YES
YES
YES
NO
YES
NO
NO
YES
YES
NO```

# AI分析结果

### 题目内容重写（中文）

女孩Umka喜欢旅行和参加数学竞赛。一天，她乘飞机去参加下一个竞赛，无聊时研究了一张巨大的方格纸。

定义第$n$个斐波那契数为$F_n = \begin{cases} 1, & n = 0; \\ 1, & n = 1; \\ F_{n-2} + F_{n-1}, & n \ge 2. \end{cases}$

一个高度为$F_n$，宽度为$F_{n+1}$的方格矩形被称为$n$阶斐波那契矩形。

Umka有一个$n$阶斐波那契矩形。有人在其中第$x$行和第$y$列的交点处涂了一个格子。

需要将这个矩形恰好切割成$n+1$个正方形，使得：

- 被涂色的格子位于一个边长为$1$的正方形中；
- 最多有一对正方形的边长相等；
- 每个正方形的边长等于一个斐波那契数。

Umka能否以这种方式切割这个矩形？

### 算法分类
递归、数学

### 题解分析与结论

该题的核心在于利用斐波那契数列的性质，将矩形逐步分割为斐波那契数边长的正方形。难点在于如何判断被涂色的格子是否可以被单独分割，并且确保整个矩形的分割满足题目条件。大多数题解采用了递归的方法，逐步缩小矩形范围，判断是否能够继续分割。

### 精选题解

#### 1. 作者：Coffee_zzz (赞：8)
**星级：5星**
**关键亮点：**
- 通过递归逐步缩小矩形范围，判断是否能够继续分割。
- 利用对称性简化判断条件，只判断最左端的分割情况。
- 代码简洁且高效，预处理斐波那契数列，避免重复计算。

**核心代码：**
```cpp
bool dfs(int n,int a,int b,int x,int y){
    if(n==1) return 1;
    int p=b/2;
    if(y<=p) y=b+1-y; //对称
    if(y<=a) return 0; //判断是否可以分割
    return dfs(n-1,b-a,a,y-a,x); //旋转长方形并递归
}
```

#### 2. 作者：Happy_14 (赞：5)
**星级：4星**
**关键亮点：**
- 利用贪心策略，每次放置最大的正方形，逐步缩小问题规模。
- 通过数学归纳法证明斐波那契数列的平方和等于矩形面积，确保分割的可行性。
- 代码逻辑清晰，易于理解。

**核心代码：**
```cpp
for (int i = n; i >= 2; --i) {
    if (r - l + 1 > u - d + 1) { 
        if (y > l + fib[i] - 1) {
            l += fib[i];
        }
        else if (y < r - fib[i] + 1) {
            r -= fib[i];
        }
        else {
            flag = false;
            break;
        }
    }
}
```

#### 3. 作者：ncwzdlsd (赞：4)
**星级：4星**
**关键亮点：**
- 通过递归不断拆分矩形，判断是否能够继续分割。
- 利用斐波那契数列的性质，确保分割的正方形边长符合要求。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
bool cut(int siz,int x,int y){
    if(siz==1) return 1;
    if(y<=F[siz-1]) return cut(siz-1,y,x);//(x,y)在左
    else if(y>F[siz]) return cut(siz-1,y-F[siz],x);//(x,y)在右
    return 0;
}
```

### 最优关键思路或技巧
- **递归分割**：通过递归逐步缩小矩形范围，判断是否能够继续分割。
- **对称性简化**：利用对称性简化判断条件，只判断最左端的分割情况。
- **斐波那契数列性质**：利用斐波那契数列的平方和等于矩形面积，确保分割的可行性。

### 可拓展之处
- 类似的问题可以扩展到其他数列或几何形状的分割问题。
- 递归和数学归纳法在其他组合数学问题中也有广泛应用。

### 推荐题目
1. [P1255 数楼梯](https://www.luogu.com.cn/problem/P1255)
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
3. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)

### 个人心得摘录
- **调试经历**：在递归过程中，初始条件设置错误导致无限递归，通过调试发现并修正。
- **踩坑教训**：未预处理斐波那契数列，导致计算超时，预处理后问题解决。
- **顿悟感想**：利用对称性简化判断条件，大大减少了代码复杂度。

---
处理用时：41.08秒