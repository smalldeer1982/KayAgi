# 题目信息

# Circular Mirror

## 题目描述

Pak Chanek has a mirror in the shape of a circle. There are $ N $ lamps on the circumference numbered from $ 1 $ to $ N $ in clockwise order. The length of the arc from lamp $ i $ to lamp $ i+1 $ is $ D_i $ for $ 1 \leq i \leq N-1 $ . Meanwhile, the length of the arc between lamp $ N $ and lamp $ 1 $ is $ D_N $ .

Pak Chanek wants to colour the lamps with $ M $ different colours. Each lamp can be coloured with one of the $ M $ colours. However, there cannot be three different lamps such that the colours of the three lamps are the same and the triangle made by considering the three lamps as vertices is a right triangle (triangle with one of its angles being exactly $ 90 $ degrees).

The following are examples of lamp colouring configurations on the circular mirror.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1725C/f662b018d5c25548ad3c12ebf7297c4fe9cddb27.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1725C/d15118feff1296e48df6066dea2761fdbf3bbba3.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1725C/904b8c54d18751fcd9444e012c7c141ddaf812b7.png)Figure 1. an example of an incorrect colouring because lamps $ 1 $ , $ 2 $ , and $ 3 $ form a right triangleFigure 2. an example of a correct colouringFigure 3. an example of a correct colouringBefore colouring the lamps, Pak Chanek wants to know the number of distinct colouring configurations he can make. Count the number of distinct possible lamp colouring configurations, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, all correct lamp colouring configurations are $ [1, 1, 2, 1] $ , $ [1, 1, 2, 2] $ , $ [1, 2, 1, 2] $ , $ [1, 2, 2, 1] $ , $ [1, 2, 2, 2] $ , $ [2, 1, 1, 1] $ , $ [2, 1, 1, 2] $ , $ [2, 1, 2, 1] $ , $ [2, 2, 1, 1] $ , and $ [2, 2, 1, 2] $ .

## 样例 #1

### 输入

```
4 2
10 10 6 14```

### 输出

```
10```

## 样例 #2

### 输入

```
1 2
10```

### 输出

```
2```

# AI分析结果

### 题目中文重写
# 圆形镜子

## 题目描述
Pak Chanek 有一面圆形镜子。圆周上有 $N$ 盏灯，按顺时针顺序从 $1$ 到 $N$ 编号。从灯 $i$ 到灯 $i + 1$ 的弧长为 $D_i$（$1 \leq i \leq N - 1$）。同时，灯 $N$ 到灯 $1$ 的弧长为 $D_N$。

Pak Chanek 想用 $M$ 种不同的颜色给这些灯染色。每盏灯可以染成 $M$ 种颜色中的一种。然而，不能存在三盏不同的灯，使得这三盏灯颜色相同，并且以这三盏灯为顶点构成的三角形是直角三角形（即其中一个角恰好为 $90$ 度的三角形）。

以下是圆形镜子上灯染色配置的示例。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1725C/f662b018d5c25548ad3c12ebf7297c4fe9cddb27.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1725C/d15118feff1296e48df6066dea2761fdbf3bbba3.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1725C/904b8c54d18751fcd9444e012c7c141ddaf812b7.png)
图 1. 一个错误染色的例子，因为灯 $1$、$2$ 和 $3$ 构成了一个直角三角形
图 2. 一个正确染色的例子
图 3. 一个正确染色的例子

在给灯染色之前，Pak Chanek 想知道他可以做出的不同染色配置的数量。计算不同的可能灯染色配置的数量，并对 $998\,244\,353$ 取模。

## 说明/提示
在第一个示例中，所有正确的灯染色配置为 $[1, 1, 2, 1]$、$[1, 1, 2, 2]$、$[1, 2, 1, 2]$、$[1, 2, 2, 1]$、$[1, 2, 2, 2]$、$[2, 1, 1, 1]$、$[2, 1, 1, 2]$、$[2, 1, 2, 1]$、$[2, 2, 1, 1]$ 和 $[2, 2, 1, 2]$。

## 样例 #1
### 输入
```
4 2
10 10 6 14
```
### 输出
```
10
```

## 样例 #2
### 输入
```
1 2
10
```
### 输出
```
2
```

### 综合分析与结论
- **思路对比**：四位作者均利用圆内接直角三角形斜边为直径这一性质，将问题转化为考虑直径两端点颜色情况。通过枚举同色直径的数量，分别计算不同部分的染色方案数，最后求和得到总方案数。
- **算法要点**：都用到组合数和排列数计算方案数，同时使用快速幂计算幂次。在统计直径数量时，有的用 `map` 记录前缀和，有的用双指针。
- **解决难点**：关键在于准确分类点（同色直径点、异色直径点、非直径点），并正确计算每类点的染色方案数，同时处理好取模运算。

### 所选题解
- **作者：yingkeqian9217（5星）**
    - **关键亮点**：思路清晰，公式推导详细，代码注释简洁明了，对 $i$ 的取值范围有明确说明。
    - **个人心得**：作者表示这是简单数学题，但自己调试了很久。
    - **核心代码**：
```cpp
#define maxn 2900001
#define A(x,y) fac[x]%Mod*inv[x-y]%Mod
#define C(x,y) fac[x]%Mod*inv[x-y]%Mod*inv[y]%Mod
#define len a[n]
const int Mod=998244353;
//...
Calc:for(int i=0;i<=min(m,cnt);i++)
    ans=(ans+qpow(m-i,n-cnt-i)*qpow(m-i-1,cnt-i)%Mod*C(cnt,i)*A(m,i))%Mod;
```
核心思想：枚举同色直径的数量 $i$，根据组合数、排列数和快速幂计算每种情况下的方案数并累加。

### 最优关键思路或技巧
- **思维方式**：利用圆内接直角三角形性质简化问题，通过枚举同色直径数量进行分类讨论。
- **数据结构**：使用 `map` 记录前缀和，方便统计直径数量。
- **代码实现**：定义宏来简化组合数和排列数的计算。

### 可拓展之处
同类型题可能会改变图形（如椭圆、多边形等）或增加染色限制条件。类似算法套路是先分析图形的特殊性质，将问题转化为可分类讨论的情况，再分别计算方案数。

### 推荐洛谷题目
- P1044 [栈](https://www.luogu.com.cn/problem/P1044)：涉及组合数学和递推。
- P1865 [A % B Problem](https://www.luogu.com.cn/problem/P1865)：需要处理质数和取模运算。
- P2671 [求和](https://www.luogu.com.cn/problem/P2671)：结合了数学计算和组合思想。 

---
处理用时：32.27秒