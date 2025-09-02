# 题目信息

# Games with Rectangle

## 题目描述

In this task Anna and Maria play the following game. Initially they have a checkered piece of paper with a painted $ n×m $ rectangle (only the border, no filling). Anna and Maria move in turns and Anna starts. During each move one should paint inside the last-painted rectangle a new lesser rectangle (along the grid lines). The new rectangle should have no common points with the previous one. Note that when we paint a rectangle, we always paint only the border, the rectangles aren't filled.

Nobody wins the game — Anna and Maria simply play until they have done $ k $ moves in total. Count the number of different ways to play this game.

## 说明/提示

Two ways to play the game are considered different if the final pictures are different. In other words, if one way contains a rectangle that is not contained in the other way.

In the first sample Anna, who performs her first and only move, has only one possible action plan — insert a $ 1×1 $ square inside the given $ 3×3 $ square.

In the second sample Anna has as much as 9 variants: 4 ways to paint a $ 1×1 $ square, 2 ways to insert a $ 1×2 $ rectangle vertically, 2 more ways to insert it horizontally and one more way is to insert a $ 2×2 $ square.

## 样例 #1

### 输入

```
3 3 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 4 1
```

### 输出

```
9
```

## 样例 #3

### 输入

```
6 7 2
```

### 输出

```
75
```

# AI分析结果

### 题目内容
# 矩形游戏

## 题目描述
在这个任务中，安娜和玛丽亚玩以下游戏。最初，她们有一张方格纸，上面画了一个\(n×m\)的矩形（只有边框，没有填充）。安娜和玛丽亚轮流行动，安娜先开始。在每一步中，玩家要在最后画的矩形内画一个新的更小的矩形（沿着网格线）。新矩形与前一个矩形不能有公共点。注意，当我们画矩形时，我们总是只画边框，矩形不填充。

没有人会赢得这个游戏 —— 安娜和玛丽亚只是简单地玩，直到她们总共进行了\(k\)步。计算玩这个游戏的不同方法的数量。

## 说明/提示
如果最终的图片不同，则认为两种玩游戏的方法是不同的。换句话说，如果一种方法包含一个不在另一种方法中的矩形。

在第一个样例中，安娜进行她的第一步也是唯一一步，只有一种可能的行动计划 —— 在给定的\(3×3\)正方形内插入一个\(1×1\)的正方形。

在第二个样例中，安娜有多达9种变体：4种画\(1×1\)正方形的方法，2种垂直插入\(1×2\)矩形的方法，2种水平插入它的方法，还有一种方法是插入一个\(2×2\)的正方形。

## 样例 #1
### 输入
```
3 3 1
```
### 输出
```
1
```

## 样例 #2
### 输入
```
4 4 1
```
### 输出
```
9
```

## 样例 #3
### 输入
```
6 7 2
```
### 输出
```
75
```

### 算法分类
组合数学

### 综合分析与结论
这些题解主要围绕如何计算在\(n×m\)矩形内按规则画\(k\)个矩形的不同方法数。多数题解思路基于组合数学，利用组合数计算方案数；部分题解采用动态规划方法。各题解在思路清晰度、代码实现及优化程度上存在差异。

### 所选的题解
- **作者：EnochWenzhou (5星)**
    - **关键亮点**：先提出从DP入手，给出DP状态定义与转移方程，后优化时间复杂度，又指出可利用组合数\(C_{n - 1}^{2×k}×C_{m - 1}^{2×k}\)解决问题，并给出两种方法的代码。思路清晰，解法多样且有优化过程。
    - **个人心得**：无
    - **重点代码（组合数递推求法）**：
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL n,m,k,C[2020][2020],P=1e9+7;
int main(){
    C[0][0]=1;
    for(LL i=1;i<=1000;i++){
        C[i][0]=1;
        for(LL j=1;j<=i;j++)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%P;
    }
    cin>>n>>m>>k;
    cout<<C[n-1][2*k]*C[m-1][2*k]%P;
    return 0;
}
```
核心实现思想：利用杨辉三角性质，通过递推计算组合数，最后得出总方案数。
- **作者：fanypcd (4星)**
    - **关键亮点**：先解释组合做法的原理，通过小学奥数中确定矩形顶点位置来确定矩形的方法，拓展到本题确定\(k\)个矩形顶点位置，得出方案数为\({n - 1 \choose 2 \times k} \times {m - 1 \choose 2 \times k}\)，并给出用逆元求组合数的代码，思路连贯清晰。
    - **个人心得**：指出翻译可能存在问题，做题感觉不可做时最好看英文题面。
    - **重点代码（逆元求组合数）**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline void read(int &x)
{
    x = 0;
    int f = 0;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        f |= ch == '-';
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    x = f? -x : x;
    return;
}
const int mod = 1e9 + 7;
#define N 1005
int inv[N], fac[N], ifac[N];
void init()
{
    inv[0] = inv[1] = fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
    for(int i = 2; i <= N - 5; i++)
    {
        inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
        fac[i] = 1ll * i * fac[i - 1] % mod;
        ifac[i] = 1ll * inv[i] * ifac[i - 1] % mod;
    }
    return;
}
inline int C(int n, int m)
{
    if(m > n)
    {
        return 0;
    }
    return 1ll * fac[n] * ifac[n - m] % mod * ifac[m] % mod;
}
signed main()
{
    init();
    int n, m, k;
    read(n), read(m), read(k);
    printf("%lld", 1ll * C(n - 1, 2 * k) * C(m - 1, 2 * k) % mod);
    return 0;
}
```
核心实现思想：先初始化逆元、阶乘及阶乘逆元，通过这些预处理数据计算组合数，进而得到总方案数。
- **作者：Mo_Han136 (4星)**
    - **关键亮点**：给出两种解法，先介绍\(O(n^5)\)暴力DP写法，利用滚动数组优化空间，后分析得出横纵方向方案数互不干扰，采用倒推思想优化为\(O(n^3)\)写法，有助于理解问题本质及优化过程。
    - **个人心得**：无
    - **重点代码（\(O(n^3)\) AC写法）**：
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int M=1005,P=1e9+7;
int n,m,k;
LL f[M][M];
void Add(LL &x,LL y){
    x+=y;
    if(x>=P)x-=P;
    if(x<0)x+=P;
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    if(n<m)swap(n,m);
    for(int i=1;i<=n;++i)f[0][i]=1;
    for(int i=1;i<=k;++i)
        for(int p=1;p<=n;++p)
            if(f[i-1][p])for(int q=p+2;q<=n;++q)
                Add(f[i][q],f[i-1][p]*(q-p-1)%P);
    printf("%lld\n",f[k][n]*f[k][m]%P);
    return 0;
}
```
核心实现思想：用\(f[i][j]\)表示第\(i\)步形成\(j\)行的方案数，通过倒推和状态转移计算方案数，最后将横纵方向方案数相乘得到总方案数。

### 最优关键思路或技巧
利用组合数学方法，将确定\(k\)个矩形的问题转化为在\(n - 1\)条可选横边和\(m - 1\)条可选竖边中分别选取\(2k\)条边的组合数问题，即方案数为\(C_{n - 1}^{2×k}×C_{m - 1}^{2×k}\)，这种方法直接简洁，计算效率高。

### 拓展
同类型题或类似算法套路：此类题目通常涉及在一定区域内按特定规则放置图形，可通过分析图形位置确定方式转化为组合数问题。类似套路如在网格中放置特定形状图形，通过确定图形边界或顶点位置，利用组合数计算方案数。

### 推荐洛谷题目
- [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)：考察组合数与二项式定理的应用。
- [P2822 [NOIP2016 提高组] 组合数问题](https://www.luogu.com.cn/problem/P2822)：关于组合数取模及规律探寻的题目。
- [P3807 【模板】卢卡斯定理](https://www.luogu.com.cn/problem/P3807)：涉及卢卡斯定理在组合数计算中的应用。 

---
处理用时：74.28秒