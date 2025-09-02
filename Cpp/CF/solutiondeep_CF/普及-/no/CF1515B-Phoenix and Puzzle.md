# 题目信息

# Phoenix and Puzzle

## 题目描述

Phoenix is playing with a new puzzle, which consists of $ n $ identical puzzle pieces. Each puzzle piece is a right isosceles triangle as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1515B/49a24f982b19e9535d6f30d4c91e443065d9fee9.png)A puzzle pieceThe goal of the puzzle is to create a square using the $ n $ pieces. He is allowed to rotate and move the pieces around, but none of them can overlap and all $ n $ pieces must be used (of course, the square shouldn't contain any holes as well). Can he do it?

## 说明/提示

For $ n=2 $ , Phoenix can create a square like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1515B/0fdfe011cd52355d3ad3123ce3848f97d63a78aa.png)For $ n=4 $ , Phoenix can create a square like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1515B/79f4dda31da05d0a22081f6d24d2a99d26f679bc.png)For $ n=6 $ , it is impossible for Phoenix to create a square.

## 样例 #1

### 输入

```
3
2
4
6```

### 输出

```
YES
YES
NO```

# AI分析结果

### 题目内容
Phoenix正在玩一个新的拼图游戏，该游戏由\(n\)个相同的拼图块组成。每个拼图块都是一个等腰直角三角形，如下图所示。
![等腰直角三角形](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1515B/49a24f982b19e9535d6f30d4c91e443065d9fee9.png)
拼图的目标是使用这\(n\)个拼图块拼成一个正方形。允许旋转和移动这些拼图块，但它们不能重叠，并且必须使用所有\(n\)个拼图块（当然，正方形也不应包含任何空洞）。他能做到吗？

### 说明/提示
对于\(n = 2\)，Phoenix可以像这样拼成一个正方形：
![\(n = 2\)时拼成的正方形](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1515B/0fdfe011cd52355d3ad3123ce3848f97d63a78aa.png)
对于\(n = 4\)，Phoenix可以像这样拼成一个正方形：
![\(n = 4\)时拼成的正方形](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1515B/79f4dda31da05d0a22081f6d24d2a99d26f679bc.png)
对于\(n = 6\)，Phoenix不可能拼成一个正方形。

### 样例 #1
#### 输入
```
3
2
4
6
```
#### 输出
```
YES
YES
NO
```

### 算法分类
数学

### 题解综合分析与结论
所有题解思路本质相同，均基于观察发现\(2\)个或\(4\)个等腰直角三角形可拼成小正方形，进而将问题转化为判断\(\frac{n}{2}\)或\(\frac{n}{4}\)是否为完全平方数。不同题解在表述、证明及代码实现细节上有差异。

### 所选的题解
- **作者：pitiless0514（4星）**
  - **关键亮点**：思路清晰简洁，直接点明判断条件，先判断\(n\bmod 2 = 0\)或\(n\bmod 4 = 0\) ，再判断\(\frac{n}{2}\)或\(\frac{n}{4}\)是否为完全平方数。
  - **重点代码**：
```cpp
// 假设已有判断完全平方数的函数check
int main()
{
    // 假设已有读入数据的逻辑
    for(/*读入数据循环*/)
    {
        if(check(n/2) || check(n/4)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
```
核心思想：读入\(n\)后，通过调用判断完全平方数的函数，判断\(\frac{n}{2}\)或\(\frac{n}{4}\)是否为完全平方数，输出相应结果。
- **作者：PPL_ （4星）**
  - **关键亮点**：对正方形由相同小正方形组成进行了反证法证明，逻辑严谨。
  - **重点代码**：
```cpp
bool check(double x)
{
    int t = sqrt(x);
    if(t * t == x) return 1;
    return 0;
}

int main()
{
    // 假设已有读入数据的逻辑
    for(/*读入数据循环*/)
    {
        if(check(n/2) || check(n/4)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
```
核心思想：定义判断完全平方数的函数`check`，在主函数读入\(n\)后，调用`check`函数判断\(\frac{n}{2}\)或\(\frac{n}{4}\)是否为完全平方数并输出结果。

### 最优关键思路或技巧
通过观察样例发现用\(2\)个或\(4\)个等腰直角三角形可拼成小正方形这一规律，将原问题巧妙转化为判断\(\frac{n}{2}\)或\(\frac{n}{4}\)是否为完全平方数，简化问题求解。

### 可拓展之处
此类题目属于图形拼接与数学判断结合的问题，类似套路是先观察图形拼接的基本单元，找出数量规律，转化为数学判断问题。例如判断用特定形状的小图形能否拼成大的特定图形，可从基本拼接单元出发，分析所需小图形数量的数学特征。

### 推荐题目
- [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)：考察数论中质因数分解相关知识。
- [P2615 神奇的幻方](https://www.luogu.com.cn/problem/P2615)：通过特定规则构造幻方，涉及数学规律探索与实现。
- [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：结合斐波那契数列与数论中求公约数知识。 

---
处理用时：48.34秒