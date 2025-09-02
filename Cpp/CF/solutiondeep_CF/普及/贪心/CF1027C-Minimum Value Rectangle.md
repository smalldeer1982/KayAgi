# 题目信息

# Minimum Value Rectangle

## 题目描述

You have $ n $ sticks of the given lengths.

Your task is to choose exactly four of them in such a way that they can form a rectangle. No sticks can be cut to pieces, each side of the rectangle must be formed by a single stick. No stick can be chosen multiple times. It is guaranteed that it is always possible to choose such sticks.

Let $ S $ be the area of the rectangle and $ P $ be the perimeter of the rectangle.

The chosen rectangle should have the value $ \frac{P^2}{S} $ minimal possible. The value is taken without any rounding.

If there are multiple answers, print any of them.

Each testcase contains several lists of sticks, for each of them you are required to solve the problem separately.

## 说明/提示

There is only one way to choose four sticks in the first list, they form a rectangle with sides $ 2 $ and $ 7 $ , its area is $ 2 \cdot 7 = 14 $ , perimeter is $ 2(2 + 7) = 18 $ . $ \frac{18^2}{14} \approx 23.143 $ .

The second list contains subsets of four sticks that can form rectangles with sides $ (1, 2) $ , $ (2, 8) $ and $ (1, 8) $ . Their values are $ \frac{6^2}{2} = 18 $ , $ \frac{20^2}{16} = 25 $ and $ \frac{18^2}{8} = 40.5 $ , respectively. The minimal one of them is the rectangle $ (1, 2) $ .

You can choose any four of the $ 5 $ given sticks from the third list, they will form a square with side $ 5 $ , which is still a rectangle with sides $ (5, 5) $ .

## 样例 #1

### 输入

```
3
4
7 2 2 7
8
2 8 1 4 8 2 1 5
5
5 5 5 5 5
```

### 输出

```
2 7 7 2
2 2 1 1
5 5 5 5
```

# AI分析结果

### 题目内容重写
# 最小值的矩形

## 题目描述

你有 $n$ 根给定长度的木棍。

你的任务是选择其中的四根，使得它们能够组成一个矩形。木棍不能被切割，矩形的每一边必须由一根木棍组成。每根木棍只能被选择一次。题目保证总是可以选出这样的四根木棍。

设 $S$ 为矩形的面积，$P$ 为矩形的周长。

所选的矩形应使得 $ \frac{P^2}{S} $ 的值尽可能小。该值不进行任何四舍五入。

如果有多个答案，输出其中任意一个即可。

每个测试用例包含多个木棍列表，你需要为每个列表分别解决这个问题。

## 说明/提示

在第一个列表中，只有一种方式选择四根木棍，它们组成的矩形边长为 $2$ 和 $7$，面积为 $2 \cdot 7 = 14$，周长为 $2(2 + 7) = 18$。$ \frac{18^2}{14} \approx 23.143 $。

第二个列表中有多个四根木棍的子集可以组成矩形，边长分别为 $ (1, 2) $、$ (2, 8) $ 和 $ (1, 8) $。它们的值分别为 $ \frac{6^2}{2} = 18 $、$ \frac{20^2}{16} = 25 $ 和 $ \frac{18^2}{8} = 40.5 $。其中最小的是边长为 $ (1, 2) $ 的矩形。

在第三个列表中，你可以从给定的 $5$ 根木棍中任意选择四根，它们将组成一个边长为 $5$ 的正方形，这也是一个边长为 $ (5, 5) $ 的矩形。

## 样例 #1

### 输入

```
3
4
7 2 2 7
8
2 8 1 4 8 2 1 5
5
5 5 5 5 5
```

### 输出

```
2 7 7 2
2 2 1 1
5 5 5 5
```

### 题解分析与结论

#### 综合分析
该题的核心在于如何选择四根木棍组成矩形，使得 $\frac{P^2}{S}$ 最小。通过数学推导，可以将问题转化为最小化 $\frac{a}{b} + \frac{b}{a}$，其中 $a$ 和 $b$ 是矩形的两条边长。进一步分析可以发现，当 $a$ 和 $b$ 越接近时，$\frac{a}{b} + \frac{b}{a}$ 越小，因此最优解是选择相邻的长度作为矩形的边长。

#### 最优思路与技巧
1. **数学转化**：将问题转化为最小化 $\frac{a}{b} + \frac{b}{a}$，简化了问题的复杂度。
2. **贪心策略**：选择相邻的长度作为矩形的边长，确保 $\frac{a}{b}$ 最接近 1。
3. **特判优化**：如果有四根相同长度的木棍，直接选择它们组成正方形，因为正方形是最优解。

#### 推荐题解
1. **Siyuan (赞：6)**  
   - **星级**：5  
   - **关键亮点**：通过数学推导将问题转化为最小化 $\frac{a}{b} + \frac{b}{a}$，并采用贪心策略选择相邻的长度。代码实现清晰，处理了精度问题。
   - **核心代码**：
     ```cpp
     FOR(i,3,m) if(x*a[i]<a[i-1]*y) x=a[i-1],y=a[i];
     printf("%d %d %d %d\n",x,x,y,y);
     ```

2. **YellowBean_Elsa (赞：2)**  
   - **星级**：4  
   - **关键亮点**：通过数学推导和对勾函数性质，选择相邻的长度作为矩形的边长。代码实现简洁，处理了特判情况。
   - **核心代码**：
     ```cpp
     fu(i,2,cnt-1)
         if(1LL*b[i]*ans2>1LL*b[i+1]*ans1) ans1=b[i],ans2=b[i+1];
     printf("%d %d %d %d\n",ans1,ans1,ans2,ans2);
     ```

3. **轻绘 (赞：1)**  
   - **星级**：4  
   - **关键亮点**：通过桶排序和贪心策略选择相邻的长度，代码实现简单，处理了特判情况。
   - **核心代码**：
     ```cpp
     if(i*1.00000000/o<b.ans){
         b.la=o;
         b.now=i;
         b.ans=b.now*1.00000000/b.la;
     }
     ```

### 扩展思路与推荐题目
1. **扩展思路**：该题的思路可以推广到其他需要选择最优组合的问题，如选择最优的三角形、四边形等。类似的数学转化和贪心策略可以应用于这类问题。
2. **推荐题目**：
   - [洛谷 P1027](https://www.luogu.com.cn/problem/P1027)：最小生成树问题，考察贪心策略。
   - [洛谷 P1048](https://www.luogu.com.cn/problem/P1048)：背包问题，考察动态规划与贪心策略的结合。
   - [洛谷 P1060](https://www.luogu.com.cn/problem/P1060)：最大子段和问题，考察贪心与动态规划的结合。

---
处理用时：43.05秒