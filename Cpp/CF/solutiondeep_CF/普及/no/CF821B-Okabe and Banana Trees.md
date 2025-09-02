# 题目信息

# Okabe and Banana Trees

## 题目描述

Okabe needs bananas for one of his experiments for some strange reason. So he decides to go to the forest and cut banana trees.

Consider the point $ (x,y) $ in the 2D plane such that $ x $ and $ y $ are integers and $ 0<=x,y $ . There is a tree in such a point, and it has $ x+y $ bananas. There are no trees nor bananas in other points. Now, Okabe draws a line with equation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821B/943332af45ee9b24d3dd582c61cd6fb6bc9281c7.png). Okabe can select a single rectangle with axis aligned sides with all points on or under the line and cut all the trees in all points that are inside or on the border of this rectangle and take their bananas. Okabe's rectangle can be degenerate; that is, it can be a line segment or even a point.

Help Okabe and find the maximum number of bananas he can get if he chooses the rectangle wisely.

Okabe is sure that the answer does not exceed $ 10^{18} $ . You can trust him.

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821B/9062959c907537ca725899b162ca1dad63845c7e.png)The graph above corresponds to sample test 1. The optimal rectangle is shown in red and has $ 30 $ bananas.

## 样例 #1

### 输入

```
1 5
```

### 输出

```
30
```

## 样例 #2

### 输入

```
2 3
```

### 输出

```
25
```

# AI分析结果



题目内容中文重写：

# Okabe与香蕉树

## 题目描述

Okabe为了某个奇怪的实验需要香蕉，于是决定去森林砍香蕉树。

考虑二维平面上满足$x$和$y$均为非负整数的点$(x,y)$，每个这样的点都有一棵香蕉树，树上的香蕉数为$x+y$。Okabe画了一条直线$y = -\frac{x}{m} + b$，他可以选取一个边与坐标轴平行的矩形（可以是线段或点），其所有点都在直线下方或恰好在直线上。求该矩形能覆盖的所有点的香蕉总数最大值。

## 样例 #1

### 输入
```
1 5
```

### 输出
```
30
```

## 样例 #2

### 输入
```
2 3
```

### 输出
```
25
```

---

**算法分类**：数学

---

### 题解分析与结论

**核心思路**：通过数学推导将二维求和转化为闭合公式，通过枚举关键点快速计算最大值。最优解法采用枚举$y$的策略，时间复杂度为$O(b)$，显著优于枚举$x$的$O(mb)$。

#### 精选题解

**题解作者：IGA_Indigo（★★★★★）**  
**关键亮点**：  
1. 枚举$y$的取值范围（$0 \le y \le b$），通过直线方程直接计算对应的$x = m(b-y)$  
2. 推导出闭合公式$(x+1)(y+1)(x+y)/2$，实现$O(1)$计算每个候选矩形  
3. 时间复杂度优化至$O(b)$，完美处理大数据范围  

**核心代码**：  
```cpp
for(int y=0; y<=b; y++) {
    long long x = m*(b-y);
    sum = (x+1)*(y+1)*(x+y)/2;
    ans = max(ans, sum);
}
```

---

### 最优思路总结

1. **数学建模**：将二维区间求和转化为三维乘积公式，避免暴力枚举  
2. **变量选择**：通过分析直线方程特性，选择枚举$y$以减少循环次数  
3. **边界处理**：利用$y$的整数特性确保$x$始终为整数，避免浮点运算  

---

### 同类题目推荐

1. [P2241 统计方形（数据加强版）](https://www.luogu.com.cn/problem/P2241)  
   - 考察点：二维区间枚举与数学优化  
2. [P1217 棋盘覆盖](https://www.luogu.com.cn/problem/P1357)  
   - 考察点：网格覆盖问题与递推公式  
3. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)  
   - 考察点：枚举策略与数学优化的结合  

---

### 个人心得摘录

来自littleone题解的调试经验：  
> "c++中的整型除以整型是向0取整而不是向下取整，因此需要用floor函数处理除法"  
**总结**：浮点运算转换时需特别注意取整方式，避免因小数部分处理不当导致坐标计算错误。

---
处理用时：115.53秒