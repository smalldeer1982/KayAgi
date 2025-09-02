# 题目信息

# The Hard Work of Paparazzi

## 题目描述

You are a paparazzi working in Manhattan.

Manhattan has $ r $ south-to-north streets, denoted by numbers $ 1, 2,\ldots, r $ in order from west to east, and $ r $ west-to-east streets, denoted by numbers $ 1,2,\ldots,r $ in order from south to north. Each of the $ r $ south-to-north streets intersects each of the $ r $ west-to-east streets; the intersection between the $ x $ -th south-to-north street and the $ y $ -th west-to-east street is denoted by $ (x, y) $ . In order to move from the intersection $ (x,y) $ to the intersection $ (x', y') $ you need $ |x-x'|+|y-y'| $ minutes.

You know about the presence of $ n $ celebrities in the city and you want to take photos of as many of them as possible. More precisely, for each $ i=1,\dots, n $ , you know that the $ i $ -th celebrity will be at the intersection $ (x_i, y_i) $ in exactly $ t_i $ minutes from now (and he will stay there for a very short time, so you may take a photo of him only if at the $ t_i $ -th minute from now you are at the intersection $ (x_i, y_i) $ ). You are very good at your job, so you are able to take photos instantaneously. You know that $ t_i < t_{i+1} $ for any $ i=1,2,\ldots, n-1 $ .

Currently you are at your office, which is located at the intersection $ (1, 1) $ . If you plan your working day optimally, what is the maximum number of celebrities you can take a photo of?

## 说明/提示

Explanation of the first testcase: There is only one celebrity in the city, and he will be at intersection $ (6,8) $ exactly $ 11 $ minutes after the beginning of the working day. Since you are initially at $ (1,1) $ and you need $ |1-6|+|1-8|=5+7=12 $ minutes to reach $ (6,8) $ you cannot take a photo of the celebrity. Thus you cannot get any photo and the answer is $ 0 $ .

Explanation of the second testcase: One way to take $ 4 $ photos (which is the maximum possible) is to take photos of celebrities with indexes $ 3, 5, 7, 9 $ (see the image for a visualization of the strategy):

- To move from the office at $ (1,1) $ to the intersection $ (5,5) $ you need $ |1-5|+|1-5|=4+4=8 $ minutes, so you arrive at minute $ 8 $ and you are just in time to take a photo of celebrity $ 3 $ .
- Then, just after you have taken a photo of celebrity $ 3 $ , you move toward the intersection $ (4,4) $ . You need $ |5-4|+|5-4|=1+1=2 $ minutes to go there, so you arrive at minute $ 8+2=10 $ and you wait until minute $ 12 $ , when celebrity $ 5 $ appears.
- Then, just after you have taken a photo of celebrity $ 5 $ , you go to the intersection $ (6,6) $ . You need $ |4-6|+|4-6|=2+2=4 $ minutes to go there, so you arrive at minute $ 12+4=16 $ and you wait until minute $ 17 $ , when celebrity $ 7 $ appears.
- Then, just after you have taken a photo of celebrity $ 7 $ , you go to the intersection $ (5,4) $ . You need $ |6-5|+|6-4|=1+2=3 $ minutes to go there, so you arrive at minute $ 17+3=20 $ and you wait until minute $ 21 $ to take a photo of celebrity $ 9 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1427C/cf9dde842b4a7da217c75d840d0291c96e32acfa.png)Explanation of the third testcase: The only way to take $ 1 $ photo (which is the maximum possible) is to take a photo of the celebrity with index $ 1 $ (since $ |2-1|+|1-1|=1 $ , you can be at intersection $ (2,1) $ after exactly one minute, hence you are just in time to take a photo of celebrity $ 1 $ ).

Explanation of the fourth testcase: One way to take $ 3 $ photos (which is the maximum possible) is to take photos of celebrities with indexes $ 3, 8, 10 $ :

- To move from the office at $ (1,1) $ to the intersection $ (101,145) $ you need $ |1-101|+|1-145|=100+144=244 $ minutes, so you can manage to be there when the celebrity $ 3 $ appears (at minute $ 341 $ ).
- Then, just after you have taken a photo of celebrity $ 3 $ , you move toward the intersection $ (149,379) $ . You need $ |101-149|+|145-379|=282 $ minutes to go there, so you arrive at minute $ 341+282=623 $ and you wait until minute $ 682 $ , when celebrity $ 8 $ appears.
- Then, just after you have taken a photo of celebrity $ 8 $ , you go to the intersection $ (157,386) $ . You need $ |149-157|+|379-386|=8+7=15 $ minutes to go there, so you arrive at minute $ 682+15=697 $ and you wait until minute $ 855 $ to take a photo of celebrity $ 10 $ .

## 样例 #1

### 输入

```
10 1
11 6 8```

### 输出

```
0```

## 样例 #2

### 输入

```
6 9
1 2 6
7 5 1
8 5 5
10 3 1
12 4 4
13 6 2
17 6 6
20 1 4
21 5 4```

### 输出

```
4```

## 样例 #3

### 输入

```
10 4
1 2 1
5 10 9
13 8 8
15 9 9```

### 输出

```
1```

## 样例 #4

### 输入

```
500 10
69 477 122
73 186 235
341 101 145
372 77 497
390 117 440
494 471 37
522 300 498
682 149 379
821 486 359
855 157 386```

### 输出

```
3```

# AI分析结果

### 题目翻译
# 狗仔队的艰辛工作

## 题目描述
你是一名在曼哈顿工作的狗仔队队员。

曼哈顿有 $r$ 条南北走向的街道，从西到东依次用数字 $1, 2, \ldots, r$ 表示，还有 $r$ 条东西走向的街道，从南到北依次用数字 $1, 2, \ldots, r$ 表示。$r$ 条南北走向的街道与 $r$ 条东西走向的街道两两相交；第 $x$ 条南北走向的街道与第 $y$ 条东西走向的街道的交点记为 $(x, y)$。从交点 $(x, y)$ 移动到交点 $(x', y')$ 需要 $|x - x'| + |y - y'|$ 分钟。

你知道城市中有 $n$ 位名人的行踪，你想尽可能多地给他们拍照。更准确地说，对于每个 $i = 1, \ldots, n$，你知道第 $i$ 位名人将在从现在起恰好 $t_i$ 分钟后出现在交点 $(x_i, y_i)$（并且他只会在那里停留很短的时间，所以只有在从现在起的第 $t_i$ 分钟你恰好位于交点 $(x_i, y_i)$ 时，你才能给他拍照）。你非常擅长你的工作，所以你可以瞬间拍照。你知道对于任何 $i = 1, 2, \ldots, n - 1$，都有 $t_i < t_{i + 1}$。

目前你在位于交点 $(1, 1)$ 的办公室。如果你最优地规划你的工作日，你最多可以给多少位名人拍照？

## 说明/提示
第一个测试用例的解释：城市中只有一位名人，他将在工作日开始后的 $11$ 分钟后恰好出现在交点 $(6, 8)$。由于你最初位于 $(1, 1)$，到达 $(6, 8)$ 需要 $|1 - 6| + |1 - 8| = 5 + 7 = 12$ 分钟，所以你无法给这位名人拍照。因此你无法拍到任何照片，答案是 $0$。

第二个测试用例的解释：一种拍到 $4$ 张照片（这是最大可能数量）的方法是给索引为 $3, 5, 7, 9$ 的名人拍照（见下图以查看该策略的可视化）：
- 从位于 $(1, 1)$ 的办公室移动到交点 $(5, 5)$ 需要 $|1 - 5| + |1 - 5| = 4 + 4 = 8$ 分钟，所以你在第 $8$ 分钟到达，刚好来得及给名人 $3$ 拍照。
- 然后，在你给名人 $3$ 拍完照后，你向交点 $(4, 4)$ 移动。到达那里需要 $|5 - 4| + |5 - 4| = 1 + 1 = 2$ 分钟，所以你在第 $8 + 2 = 10$ 分钟到达，并等待到第 $12$ 分钟，此时名人 $5$ 出现。
- 然后，在你给名人 $5$ 拍完照后，你前往交点 $(6, 6)$。到达那里需要 $|4 - 6| + |4 - 6| = 2 + 2 = 4$ 分钟，所以你在第 $12 + 4 = 16$ 分钟到达，并等待到第 $17$ 分钟，此时名人 $7$ 出现。
- 然后，在你给名人 $7$ 拍完照后，你前往交点 $(5, 4)$。到达那里需要 $|6 - 5| + |6 - 4| = 1 + 2 = 3$ 分钟，所以你在第 $17 + 3 = 20$ 分钟到达，并等待到第 $21$ 分钟给名人 $9$ 拍照。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1427C/cf9dde842b4a7da217c75d840d0291c96e32acfa.png)

第三个测试用例的解释：拍到 $1$ 张照片（这是最大可能数量）的唯一方法是给索引为 $1$ 的名人拍照（因为 $|2 - 1| + |1 - 1| = 1$，你可以在恰好一分钟后到达交点 $(2, 1)$，因此刚好来得及给名人 $1$ 拍照）。

第四个测试用例的解释：一种拍到 $3$ 张照片（这是最大可能数量）的方法是给索引为 $3, 8, 10$ 的名人拍照：
- 从位于 $(1, 1)$ 的办公室移动到交点 $(101, 145)$ 需要 $|1 - 101| + |1 - 145| = 100 + 144 = 244$ 分钟，所以你可以设法在名人 $3$ 出现时（第 $341$ 分钟）到达那里。
- 然后，在你给名人 $3$ 拍完照后，你向交点 $(149, 379)$ 移动。到达那里需要 $|101 - 149| + |145 - 379| = 282$ 分钟，所以你在第 $341 + 282 = 623$ 分钟到达，并等待到第 $682$ 分钟，此时名人 $8$ 出现。
- 然后，在你给名人 $8$ 拍完照后，你前往交点 $(157, 386)$。到达那里需要 $|149 - 157| + |379 - 386| = 8 + 7 = 15$ 分钟，所以你在第 $682 + 15 = 697$ 分钟到达，并等待到第 $855$ 分钟给名人 $10$ 拍照。

## 样例 #1
### 输入
```
10 1
11 6 8
```
### 输出
```
0
```

## 样例 #2
### 输入
```
6 9
1 2 6
7 5 1
8 5 5
10 3 1
12 4 4
13 6 2
17 6 6
20 1 4
21 5 4
```
### 输出
```
4
```

## 样例 #3
### 输入
```
10 4
1 2 1
5 10 9
13 8 8
15 9 9
```
### 输出
```
1
```

## 样例 #4
### 输入
```
500 10
69 477 122
73 186 235
341 101 145
372 77 497
390 117 440
494 471 37
522 300 498
682 149 379
821 486 359
855 157 386
```
### 输出
```
3
```

### 算法分类
动态规划

### 综合分析与结论
这些题解的核心思路都是使用动态规划来解决问题。首先定义状态 $f[i]$ 表示以第 $i$ 个点为终点，最多经过的点的个数。朴素的动态规划是 $O(n^2)$ 的，通过观察发现，由于曼哈顿距离的限制，两个点之间的距离最大为 $2r$，所以对于每个状态，只需要枚举前面 $2r$ 个点进行转移，前面更远的点可以用一个变量记录最大值，这样就将时间复杂度优化到了 $O(nr)$。

### 所选题解
- **作者：7KByte (赞：5)，4星**
  - **关键亮点**：思路清晰，代码简洁，对动态规划的状态转移和优化过程有明确的注释和解释。
  - **个人心得**：无
- **作者：zztqwq (赞：2)，4星**
  - **关键亮点**：对动态规划的状态转移方程和优化思路有详细的数学推导和文字说明，便于理解。
  - **个人心得**：无
- **作者：wizardMarshall (赞：1)，4星**
  - **关键亮点**：对题意和思路的分析详细，代码结构清晰，对每个步骤的作用有注释。
  - **个人心得**：无

### 重点代码
#### 作者：7KByte
```cpp
rep(i,1,m){
    f[i]=max(f[i],mx+1);
    rep(j,max(0,i-2*n),i-1)if(t[i]-t[j]>=abs(X[i]-X[j])+abs(Y[i]-Y[j]))f[i]=max(f[i],f[j]+1);
    if(i>=2*n)mx=max(mx,f[i-2*n]);
    ans=max(ans,f[i]);
}
```
**核心实现思想**：遍历每个点，先尝试用前面更远点的最大值更新当前点的状态，然后枚举前面 $2n$ 个点，若满足时间和距离条件，则更新当前点的状态，同时更新更远点的最大值，最后更新答案。

#### 作者：zztqwq
```cpp
for(int i=1;i<=n;i++)
{
    for(int j=max(0,i-2*r+1);j<i;j++)
    {
        if(t[i]-t[j]>=abs(x[i]-x[j])+abs(y[i]-y[j]))
            dp[i]=max(dp[i],dp[j]+1);
    }
    dp[i]=max(dp[i],mx+1);
    if(i>=r*2) mx=max(mx,dp[i-r*2]);
}
```
**核心实现思想**：与 7KByte 的思路类似，通过两层循环进行状态转移，内层循环枚举前面 $2r$ 个点，外层循环更新更远点的最大值。

#### 作者：wizardMarshall
```cpp
for (int i = 1; i <= n; i++) {
    if (i > 2 * r) {
        e = max(e, dp[i - 2 * r - 1]);
    }
    dp[i] = e + 1;
    for (int j = i - 1; j >= max(0, i - 2 * r); j--) {
        if (abs(node[i].x - node[j].x) + abs(node[i].y - node[j].y) <= node[i].t - node[j].t) {
            dp[i] = max(dp[i], dp[j] + 1);
        }
    }
    ans = max(ans, dp[i]);
}
```
**核心实现思想**：同样是动态规划的状态转移，先更新前面更远点的最大值，然后尝试用该最大值更新当前点，再枚举前面 $2r$ 个点进行状态转移，最后更新答案。

### 最优关键思路或技巧
- **动态规划状态定义**：定义 $f[i]$ 表示以第 $i$ 个点为终点，最多经过的点的个数，通过状态转移方程 $f[i]=\max\{f[j]+1\}$ （满足转移条件）来求解。
- **优化思路**：利用曼哈顿距离的性质，两个点之间的距离最大为 $2r$，所以只需要枚举前面 $2r$ 个点进行转移，更远的点用一个变量记录最大值，将时间复杂度从 $O(n^2)$ 优化到 $O(nr)$。

### 拓展思路
同类型题或类似算法套路：
- 其他涉及时间和空间限制的动态规划问题，例如在规定时间内完成多个任务，每个任务有不同的时间和地点要求，求最大完成任务数。
- 带有条件限制的路径规划问题，例如在地图中移动，每个位置有不同的到达时间要求，求最多能到达的位置数。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的 0 - 1 背包问题，与本题的动态规划思想类似。
- [P1802 5 倍经验日](https://www.luogu.com.cn/problem/P1802)：也是动态规划问题，需要根据不同的选择进行状态转移。
- [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：简单的动态规划入门题，通过状态转移求解最大路径和。

### 个人心得摘录与总结
- **ykzzldz**：提到翻译未说明初始位置在 $(1, 1)$，以及要将初值赋成负无穷，防止由不合法的状态转移而来。总结就是在做题时要仔细阅读题目条件，对于动态规划问题要注意初始状态的设置。

---
处理用时：84.81秒