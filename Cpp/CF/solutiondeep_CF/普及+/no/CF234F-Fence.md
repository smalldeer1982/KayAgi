# 题目信息

# Fence

## 题目描述

Vasya should paint a fence in front of his own cottage. The fence is a sequence of $ n $ wooden boards arranged in a single row. Each board is a $ 1 $ centimeter wide rectangle. Let's number the board fence using numbers $ 1,2,...,n $ from left to right. The height of the $ i $ -th board is $ h_{i} $ centimeters.

Vasya has a $ 1 $ centimeter wide brush and the paint of two colors, red and green. Of course, the amount of the paint is limited. Vasya counted the area he can paint each of the colors. It turned out that he can not paint over $ a $ square centimeters of the fence red, and he can not paint over $ b $ square centimeters green. Each board of the fence should be painted exactly one of the two colors. Perhaps Vasya won't need one of the colors.

In addition, Vasya wants his fence to look smart. To do this, he should paint the fence so as to minimize the value that Vasya called the fence unattractiveness value. Vasya believes that two consecutive fence boards, painted different colors, look unattractive. The unattractiveness value of a fence is the total length of contact between the neighboring boards of various colors. To make the fence look nice, you need to minimize the value as low as possible. Your task is to find what is the minimum unattractiveness Vasya can get, if he paints his fence completely.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234F/a14b673dce5ebb55793e288f9c6ca9cf6b548bb3.png)The picture shows the fence, where the heights of boards (from left to right) are 2,3,2,4,3,1. The first and the fifth boards are painted red, the others are painted green. The first and the second boards have contact length 2, the fourth and fifth boards have contact length 3, the fifth and the sixth have contact length 1. Therefore, the unattractiveness of the given painted fence is 2+3+1=6.

## 样例 #1

### 输入

```
4
5 7
3 3 4 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
2 3
1 3 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3
3 3
2 2 2
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# Fence

## 题目描述
Vasya需要给自家小屋前的栅栏刷漆。栅栏是由n块木板排成的一行。每块木板都是宽1厘米的矩形。我们从左到右用数字1, 2,..., n给栅栏的木板编号。第i块木板的高度是hi厘米。

Vasya有一把宽1厘米的刷子和两种颜色的油漆，红色和绿色。当然，油漆的量是有限的。Vasya计算了他能用每种颜色刷漆的面积。结果发现，他不能用红色刷超过a平方厘米的栅栏，不能用绿色刷超过b平方厘米的栅栏。栅栏的每块木板都必须恰好刷上两种颜色中的一种。也许Vasya不需要用到其中一种颜色。

此外，Vasya希望他的栅栏看起来美观。为此，他刷栅栏时应尽量使他所谓的栅栏不美观值最小。Vasya认为，相邻两块刷不同颜色的栅栏木板看起来不美观。栅栏的不美观值是相邻不同颜色木板之间接触部分的总长度。为了使栅栏看起来好看，需要将这个值尽可能地降低。你的任务是找出，如果Vasya完全刷完他的栅栏，他能得到的最小不美观值是多少。

![栅栏示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234F/a14b673dce5ebb55793e288f9c6ca9cf6b548bb3.png)
该图展示了栅栏，其中木板的高度（从左到右）为2, 3, 2, 4, 3, 1。第一块和第五块木板刷成红色，其他的刷成绿色。第一块和第二块木板的接触长度为2，第四块和第五块木板的接触长度为3，第五块和第六块木板的接触长度为1。因此，给定刷漆栅栏的不美观值为2 + 3 + 1 = 6。

## 样例 #1
### 输入
```
4
5 7
3 3 4 1
```
### 输出
```
3
```

## 样例 #2
### 输入
```
3
2 3
1 3 1
```
### 输出
```
2
```

## 样例 #3
### 输入
```
3
3 3
2 2 2
```
### 输出
```
-1
```

### 算法分类
动态规划

### 题解综合分析与结论
所有题解都采用动态规划算法解决该问题，核心思路均是通过定义状态来表示处理到前i个栅栏时的情况，并依据当前栅栏颜色与前一个栅栏颜色的关系得出状态转移方程。各题解的主要区别在于状态定义的维度优化以及边界条件处理方式的细节差异。难点在于如何优化状态表示以适应较大的数据范围，多个题解都通过利用前i个栅栏总面积固定这一特性，只枚举一种颜色的面积，从而将原本可能的高维状态压缩，避免超时。

### 所选的题解
- **作者ListenSnow（5星）**
    - **关键亮点**：思路清晰，先给出朴素的四维状态定义，分析其因数据范围无法通过后，提出利用前i个栅栏总面积固定，只枚举红色栅栏面积来优化为三维状态，状态转移方程解释详细，代码简洁明了。
    - **重点代码**：
```cpp
for(int i=1;i<=n;i++)
    for(int j=max(0,s[i]-b);j<=min(a,s[i]);j++)
    {
        if(j>=h[i]) f[i][j][0]=min(f[i-1][j-h[i]][1]+min(h[i],h[i-1]),f[i-1][j-h[i]][0]);
        f[i][j][1]=min(f[i-1][j][1],f[i-1][j][0]+min(h[i],h[i-1]));
    }
```
核心实现思想：外层循环遍历栅栏木板，内层循环枚举当前红色栅栏面积，根据当前木板颜色（0代表红色，1代表绿色）分别进行状态转移，若当前涂红色且红色面积足够，则从之前状态转移并考虑与前一块木板颜色不同时增加的不美观值；若涂绿色，同样从之前状态转移并处理不美观值。
- **作者ran_qwq（4星）**
    - **关键亮点**：简洁地阐述了状态定义和状态转移方程，直接给出优化后的三维状态定义，对边界情况有所提及。
    - **重点代码**：无详细代码，状态转移方程如下：
如果该列涂的是红色，则 \(dp_{i,j,0}=\min(dp_{i - 1,j - h_i,0},dp_{i - 1,j - h_i,1}+\min(h_{i - 1},h_i))\)。
如果该列涂的是绿色，则 \(dp_{i,j,1}=\min(dp_{i - 1,j,1},dp_{i - 1,j,0}+\min(h_{i - 1},h_i))\)。
核心实现思想：与其他题解类似，根据当前木板颜色进行状态转移，考虑前一块木板颜色不同时增加的不美观值。
- **作者Clover_BY（4星）**
    - **关键亮点**：对题目分析详细，在状态转移时通过预先处理绿色部分面积，依据a和b的限制分别考虑给当前栅栏涂两种颜色的情况，代码注释详细。
    - **重点代码**：
```cpp
for(register int i = 1; i <= n; ++i)
{
    for(register int j = sum[i - 1]; j >= 0; --j)
    {
        for(register int k = 0; k <= 1; ++k)
        {
            int l1 = j + sz[i], l2 = sum[i - 1] - j + sz[i];
            if(l1 <= a) dp[i][l1][0] = min(dp[i - 1][j][0], dp[i - 1][j][1] + min(sz[i], sz[i - 1]));
            if(l2 <= b) dp[i][j][1] = min(dp[i - 1][j][1], dp[i - 1][j][0] + min(sz[i - 1], sz[i]));
        }
    }
}
```
核心实现思想：三层循环，最外层遍历木板，中间层枚举之前红色面积，最内层考虑当前木板颜色，根据假设涂不同颜色后总面积是否满足限制条件进行状态转移，并处理不美观值。

### 最优关键思路或技巧
利用前i个栅栏总面积固定这一特性，将原本可能需要枚举两种颜色面积的高维状态优化为只枚举一种颜色面积的三维状态，从而减少时间复杂度，避免因数据范围过大导致超时。同时，在状态转移时，根据当前木板与前一块木板颜色不同的情况，合理增加不美观值，准确构建状态转移方程。

### 可拓展思路
此类题目属于动态规划中多限制条件下的最优解问题。类似套路是在遇到多个限制条件时，分析条件之间的关系，看是否能通过某些固定值减少状态维度。同类型题通常会在限制条件和状态转移的复杂性上进行变化，例如改变限制条件的形式，或者状态转移不仅依赖前一个状态，还依赖更前面的多个状态等。

### 推荐题目
 - [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：经典的二维动态规划问题，通过分析棋子移动规则构建状态转移方程。
 - [P1216 数字三角形](https://www.luogu.com.cn/problem/P1216)：从顶部到底部的路径和最大问题，通过动态规划从下往上或从上往下推导最优解。
 - [P1434 [SHOI2002]滑雪](https://www.luogu.com.cn/problem/P1434)：结合记忆化搜索的动态规划，通过记录每个位置的最优解避免重复计算。

### 个人心得摘录
无

---
处理用时：71.50秒