# 题目信息

# Rarity and New Dress

## 题目描述

Carousel Boutique is busy again! Rarity has decided to visit the pony ball and she surely needs a new dress, because going out in the same dress several times is a sign of bad manners. First of all, she needs a dress pattern, which she is going to cut out from the rectangular piece of the multicolored fabric.

The piece of the multicolored fabric consists of $ n \times m $ separate square scraps. Since Rarity likes dresses in style, a dress pattern must only include scraps sharing the same color. A dress pattern must be the square, and since Rarity is fond of rhombuses, the sides of a pattern must form a $ 45^{\circ} $ angle with sides of a piece of fabric (that way it will be resembling the traditional picture of a rhombus).

Examples of proper dress patterns: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1393D/1313c2f6e2e4ec2b50b9f433196c0f6817a45d78.png) Examples of improper dress patterns: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1393D/53b6557287b6852020c7bea84c9bc4969c632d30.png) The first one consists of multi-colored scraps, the second one goes beyond the bounds of the piece of fabric, the third one is not a square with sides forming a $ 45^{\circ} $ angle with sides of the piece of fabric.

Rarity wonders how many ways to cut out a dress pattern that satisfies all the conditions that do exist. Please help her and satisfy her curiosity so she can continue working on her new masterpiece!

## 说明/提示

In the first example, all the dress patterns of size $ 1 $ and one of size $ 2 $ are satisfactory.

In the second example, only the dress patterns of size $ 1 $ are satisfactory.

## 样例 #1

### 输入

```
3 3
aaa
aaa
aaa```

### 输出

```
10```

## 样例 #2

### 输入

```
3 4
abab
baba
abab```

### 输出

```
12```

## 样例 #3

### 输入

```
5 5
zbacg
baaac
aaaaa
eaaad
weadd```

### 输出

```
31```

# AI分析结果

### 题目翻译
# 瑞瑞与新裙子

## 题目描述
旋转木马精品店又忙碌起来了！瑞瑞决定去参加小马舞会，她肯定需要一条新裙子，因为多次穿着同一条裙子出门是不礼貌的表现。首先，她需要一个裙子的图案，她打算从一块彩色的长方形布料上裁剪下来。

这块彩色布料由 $n \times m$ 个单独的方形碎片组成。由于瑞瑞喜欢时尚的裙子，裙子的图案必须只包含颜色相同的碎片。裙子的图案必须是正方形，而且因为瑞瑞喜欢菱形，图案的边必须与布料的边成 $45^{\circ}$ 角（这样它就会像传统的菱形图案）。

合适的裙子图案示例：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1393D/1313c2f6e2e4ec2b50b9f433196c0f6817a45d78.png) 不合适的裙子图案示例：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1393D/53b6557287b6852020c7bea84c9bc4969c632d30.png) 第一个图案由多种颜色的碎片组成，第二个图案超出了布料的范围，第三个图案不是一个边与布料边成 $45^{\circ}$ 角的正方形。

瑞瑞想知道有多少种方法可以裁剪出满足所有条件的裙子图案。请帮助她，满足她的好奇心，这样她就可以继续创作她的新杰作了！

## 说明/提示
在第一个示例中，所有尺寸为 $1$ 的裙子图案和一个尺寸为 $2$ 的裙子图案都是符合要求的。

在第二个示例中，只有尺寸为 $1$ 的裙子图案是符合要求的。

## 样例 #1
### 输入
```
3 3
aaa
aaa
aaa
```
### 输出
```
10
```

## 样例 #2
### 输入
```
3 4
abab
baba
abab
```
### 输出
```
12
```

## 样例 #3
### 输入
```
5 5
zbacg
baaac
aaaaa
eaaad
weadd
```
### 输出
```
31
```

### 算法分类
动态规划

### 综合分析与结论
本题的题干是在一个 $n\times m$ 的矩形彩色布料中，裁剪出边与布料边成 $45^{\circ}$ 角且颜色相同的菱形裙子图案，求满足条件的裁剪方法数。

各题解的思路大多围绕动态规划展开，通过不同的方式计算每个点能构成的最大菱形图案，进而统计所有可能的图案数量。主要难点在于如何准确地确定每个点向各个方向扩展的最大距离，以及如何保证菱形图案的颜色一致性和形状要求。

### 所选题解
- **引领天下（5星）**
    - **亮点**：思路清晰，通过预处理每个点向上、向下、向左、向右能扩展的最远区域，然后综合这些信息计算每个点能构成的菱形图案数量，代码实现简洁明了。
    - **关键代码**：
```cpp
for(register int i=1;i<=n;i++)
for(register int j=1;j<=m;j++)up[i][j]=(c[i][j]==c[i-1][j])?up[i-1][j]+1:1;//处理向上的最远区域
for(register int i=n;i;i--)
for(register int j=1;j<=m;j++)down[i][j]=(c[i][j]==c[i+1][j])?down[i+1][j]+1:1;//处理向下的最远距离
for(register int i=1;i<=n;i++){
    for(register int j=1;j<=m;j++)if(c[i][j]!=c[i][j-1])le[i][j]=1;
    else le[i][j]=min(min(up[i][j],down[i][j]),le[i][j-1]+1);
    for(register int j=m;j>=1;j--)if(c[i][j]!=c[i][j+1])ri[i][j]=1;
    else ri[i][j]=min(min(up[i][j],down[i][j]),ri[i][j+1]+1);
    for(register int j=1;j<=m;j++)ans+=min(le[i][j],ri[i][j]);
}
```
    - **核心思想**：先分别处理每个点向上、向下能扩展的最远区域，再在左右扩展时考虑上下方向的限制，最后取左右扩展中较小的值作为当前点能构成的菱形图案的限制，累加所有点的结果得到答案。

- **stoorz（4星）**
    - **亮点**：通过将原图逆时针旋转 $45^{\circ}$ 的思路，将菱形问题转化为类似正方形的问题，利用经典的动态规划方法求解，具有创新性。
    - **关键代码**：
```cpp
for (int i=1;i<=n;i++)
    for (int j=1;j<=m;j++)
    {
        if (i==1) f[i][j]=1LL;
        else if (a[i][j]!=a[i-1][j-1] || a[i][j]!=a[i-1][j+1] || a[i][j]!=a[i-2][j]) f[i][j]=1LL;
        else f[i][j]=1LL+min(f[i-1][j-1],min(f[i-1][j+1],f[i-2][j]));
    }
for (int i=1;i<=n;i++)
    for (int j=1;j<=m;j++)
    {
        if (a[i][j]==a[i-1][j])
            ans+=min(f[i][j],f[i-1][j]+1);
        else ans++;
    }
```
    - **核心思想**：先根据相邻点的颜色关系计算每个点能构成的最大“正方形”（旋转后的菱形）的边长，再根据相邻点的颜色一致性计算以该点为最下方格子的菱形图案数量，累加得到答案。

- **K_Madoka（4星）**
    - **亮点**：通过设置四个方向的动态规划数组，分别表示每个点向上下左右四个方向延伸的最长长度，最后综合这四个方向的信息计算答案，逻辑清晰。
    - **关键代码**：
```cpp
for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
        if(s[i][j]==s[i-1][j]&&s[i][j]==s[i][j-1])
            dp[0][i][j]=min(dp[0][i-1][j],dp[0][i][j-1])+1;
    }
}
// 其他三个方向类似处理
ll ans=0;
for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
        ans+=min(min(dp[0][i][j],dp[1][i][j]),min(dp[2][i][j],dp[3][i][j]))+1;
    }
}
```
    - **核心思想**：分别计算每个点向四个方向延伸的最长长度，取四个方向中最小的值加 1 作为该点能构成的菱形图案数量，累加所有点的结果得到答案。

### 最优关键思路或技巧
- **方向预处理**：通过预处理每个点向各个方向扩展的最大距离，能有效简化后续的计算过程。
- **状态转化**：如将菱形问题转化为类似正方形的问题，或者将复杂的状态通过合理的数组表示，降低问题的复杂度。

### 可拓展之处
同类型题可能会改变图案的形状或限制条件，如要求裁剪出其他形状的图案，或者对图案的颜色、大小有更复杂的限制。类似的算法套路包括通过预处理方向信息、状态转化、动态规划等方法来解决几何图形的计数问题。

### 推荐题目
- [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)
- [P2701 [USACO5.3]巨大的牛棚Big Barn](https://www.luogu.com.cn/problem/P2701)
- [P1169 [ZJOI2007]棋盘制作](https://www.luogu.com.cn/problem/P1169)

### 个人心得摘录与总结
- **huayucaiji**：提到用 `getchar()` 读取输入，否则会被卡常，提醒在处理输入输出时要注意效率问题。
- **StupidSeven**：分享了自己在比赛中多次提交才通过的经历，说明在做题时可能会因为思路不清晰或细节处理不当而出现问题，需要仔细思考和调试。

---
处理用时：55.74秒