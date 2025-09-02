# 题目信息

# Tetrahedron

## 题目描述

You are given a tetrahedron. Let's mark its vertices with letters $ A $ , $ B $ , $ C $ and $ D $ correspondingly.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF166E/40dcfda00eddce9e7e8701e13b2759e732ca40f3.png)An ant is standing in the vertex $ D $ of the tetrahedron. The ant is quite active and he wouldn't stay idle. At each moment of time he makes a step from one vertex to another one along some edge of the tetrahedron. The ant just can't stand on one place.

You do not have to do much to solve the problem: your task is to count the number of ways in which the ant can go from the initial vertex $ D $ to itself in exactly $ n $ steps. In other words, you are asked to find out the number of different cyclic paths with the length of $ n $ from vertex $ D $ to itself. As the number can be quite large, you should print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

The required paths in the first sample are:

- $ D-A-D $
- $ D-B-D $
- $ D-C-D $

## 样例 #1

### 输入

```
2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
```

### 输出

```
21
```

# AI分析结果

### 题目中文重写
# 四面体

## 题目描述
给定一个四面体，用字母 $A$、$B$、$C$ 和 $D$ 分别标记它的顶点。

![四面体](https://cdn.luogu.com.cn/upload/vjudge_pic/CF166E/40dcfda00eddce9e7e8701e13b2759e732ca40f3.png)

一只蚂蚁站在四面体的顶点 $D$ 上。这只蚂蚁非常活跃，不会闲着。在每一时刻，它都会沿着四面体的某条边从一个顶点移动到另一个顶点，不会停留在原地。

你要做的事情并不复杂：任务是计算蚂蚁恰好经过 $n$ 步从初始顶点 $D$ 回到自身的路径数量。换句话说，就是要找出从顶点 $D$ 到自身的长度为 $n$ 的不同循环路径的数量。由于这个数字可能非常大，你需要将结果对 $1000000007$（$10^{9}+7$）取模。

## 说明/提示
第一个样例中所需的路径如下：
- $D - A - D$
- $D - B - D$
- $D - C - D$

## 样例 #1
### 输入
```
2
```
### 输出
```
3
```

## 样例 #2
### 输入
```
4
```
### 输出
```
21
```

### 综合分析与结论
这些题解主要围绕动态规划（DP）展开，通过不同的状态定义和转移方程来解决蚂蚁在四面体上移动并回到起点的方案数问题。各题解的思路和实现方式有所不同，但核心都是利用递推关系求解。

- **思路对比**：部分题解将状态分为在起点和不在起点两种，通过两个数组或变量来记录方案数；部分题解则直接定义多维数组记录每一步到达每个顶点的方案数；还有题解通过找规律得出递推公式。
- **算法要点**：多数题解采用动态规划，通过状态转移方程递推求解；部分题解使用矩阵快速幂优化时间复杂度；还有题解利用特征方程求解线性递推数列。
- **解决难点**：主要难点在于状态的定义和转移方程的推导，以及处理结果的取模和可能出现的溢出问题。部分题解还需要考虑空间复杂度的优化，如使用滚动数组。

### 所选题解
- **作者：ModestCoder_ (赞：23)，4星**
  - **关键亮点**：思路清晰，使用滚动数组优化空间复杂度，代码简洁易懂。
  - **核心代码**：
```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const LL qy = 1000000007;

int main(){
    int n;
    scanf("%d", &n);
    LL f = 0, g = 1;
    for (int i = 2; i <= n; ++i){
        LL tmp = f;
        f = 3 * g % qy, g = (tmp + 2 * g) % qy;
    }
    printf("%lld\n", f);
    return 0;
}
```
  - **核心实现思想**：定义 $f_i$ 表示走了 $i$ 步目前在顶端的方案数，$g_i$ 表示走了 $i$ 步目前不在顶端的方案数，通过状态转移方程 $f_i = 3g_{i - 1}$ 和 $g_i = f_{i - 1} + 2g_{i - 1}$ 递推求解。

- **作者：Flokirie (赞：12)，4星**
  - **关键亮点**：不仅给出了常规的 DP 思路，还通过数学推导将问题转化为线性递推数列，使用特征方程求解，最后用快速幂和逆元优化，时间复杂度为 $O(\log n)$。
  - **核心代码**：
```cpp
#include <iostream>
#include <cstdio>
#define int long long
#define mos (1000000007ll)

using namespace std;

int ksm(int a,int n,int mod){
    int ret=1;
    for(;n;n>>=1){
        if (n&1) ret=(ret*a)%mod;
        a=(a*a)%mod;
    }
    return ret;
}

signed main(){
    int n;
    cin>>n;
    return !printf("%I64d",(750000006ll*(10000000070ll+ksm(3ll,n-1,mos)-ksm(1000000006ll,n-1,mos)))%mos);
}
```
  - **核心实现思想**：将 DP 方程代入化简得到线性递推数列，通过特征方程求出通项公式，再用快速幂计算幂次，最后乘以逆元得到结果。

- **作者：千秋星辰 (赞：3)，4星**
  - **关键亮点**：通过画图找规律得出递推公式 $f[i] = 3^{i - 1} - f[i - 1]$，思路独特，代码实现简单。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
#include<algorithm>
#define int long long
#define out(x) write(x),putchar(' ')
#define writen(x) write(x),putchar('\n')
#define forever() while(true)
using namespace std;

inline int read() {
    int x=0,y=1;char c=getchar();
    for(;c<'0'||c>'9';c=getchar()) if(c=='-') y=-y;
    for(;c>='0'&&c<='9';c=getchar()) x=(x<<3)+(x<<1)+(c^'0');
    return x*y;
}

inline void write(int x) {
    if(x<0) x=-x,putchar('-');
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

int n,base,ans;
const int mod=1e9+7;

signed main()
{
    n=read();
    base=3;
    for(int i=2;i<=n;i++)
    {
        ans=base-ans;
        ans=(ans%mod+mod)%mod;
        base=base*3%mod;
    }
    write(ans);
    return 0;
}
```
  - **核心实现思想**：通过观察路径图，找出每一层起点个数的规律，得到递推公式，然后通过循环递推求解。

### 最优关键思路或技巧
- **状态压缩**：使用滚动数组将二维数组优化为几个变量，降低空间复杂度。
- **数学推导**：通过数学方法将动态规划问题转化为线性递推数列，使用特征方程求解通项公式，再用快速幂和逆元优化时间复杂度。
- **找规律**：通过画图或打表找规律，得出简单的递推公式，简化问题求解。

### 拓展思路
同类型题通常涉及状态转移和递推关系的求解，如其他图上的路径计数问题、棋盘上的走法问题等。类似算法套路包括动态规划、矩阵快速幂、找规律等。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的 0 - 1 背包问题，考察动态规划的基本思想。
- [P1176 路径计数2](https://www.luogu.com.cn/problem/P1176)：图上的路径计数问题，需要考虑障碍物和取模。
- [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：简单的动态规划问题，通过状态转移求解最大路径和。

### 个人心得摘录与总结
- **wz20201136**：最初代码 $WA$ 是因为三个 $\leq 1e9 + 7$ 的数加起来爆精度，开 $long long$ 后 $MLE$，最后使用滚动数组才 $AC$。总结：在处理大数相加时要注意精度问题，当数据范围较大时要考虑空间复杂度的优化。
- **huangruiheng0217**：以为简单实现就能解决问题，结果空间炸了，最后用滚动数组解决。总结：在设计状态时要考虑空间复杂度，避免出现空间溢出的问题。

---
处理用时：54.11秒