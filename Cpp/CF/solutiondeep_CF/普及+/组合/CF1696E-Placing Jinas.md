# 题目信息

# Placing Jinas

## 题目描述

We say an infinite sequence $ a_{0}, a_{1}, a_2, \ldots $ is non-increasing if and only if for all $ i\ge 0 $ , $ a_i \ge a_{i+1} $ .

There is an infinite right and down grid. The upper-left cell has coordinates $ (0,0) $ . Rows are numbered $ 0 $ to infinity from top to bottom, columns are numbered from $ 0 $ to infinity from left to right.

There is also a non-increasing infinite sequence $ a_{0}, a_{1}, a_2, \ldots $ . You are given $ a_0 $ , $ a_1 $ , $ \ldots $ , $ a_n $ ; for all $ i>n $ , $ a_i=0 $ . For every pair of $ x $ , $ y $ , the cell with coordinates $ (x,y) $ (which is located at the intersection of $ x $ -th row and $ y $ -th column) is white if $ y<a_x $ and black otherwise.

Initially there is one doll named Jina on $ (0,0) $ . You can do the following operation.

- Select one doll on $ (x,y) $ . Remove it and place a doll on $ (x,y+1) $ and place a doll on $ (x+1,y) $ .

Note that multiple dolls can be present at a cell at the same time; in one operation, you remove only one. Your goal is to make all white cells contain $ 0 $ dolls.

What's the minimum number of operations needed to achieve the goal? Print the answer modulo $ 10^9+7 $ .

## 说明/提示

Consider the first example. In the given grid, cells $ (0,0),(0,1),(1,0),(1,1) $ are white, and all other cells are black. Let us use triples to describe the grid: triple $ (x,y,z) $ means that there are $ z $ dolls placed on cell $ (x,y) $ . Initially the state of the grid is $ (0,0,1) $ .

One of the optimal sequence of operations is as follows:

- Do the operation with $ (0,0) $ . Now the state of the grid is $ (1,0,1),(0,1,1) $ .
- Do the operation with $ (0,1) $ . Now the state of the grid is $ (1,0,1),(1,1,1),(0,2,1) $ .
- Do the operation with $ (1,0) $ . Now the state of the grid is $ (1,1,2),(0,2,1),(2,0,1) $ .
- Do the operation with $ (1,1) $ . Now the state of the grid is $ (1,1,1),(0,2,1),(2,0,1),(1,2,1),(2,1,1) $ .
- Do the operation with $ (1,1) $ . Now the state of the grid is $ (0,2,1),(2,0,1),(1,2,2),(2,1,2) $ .

Now all white cells contain $ 0 $ dolls, so we have achieved the goal with $ 5 $ operations.

## 样例 #1

### 输入

```
2
2 2 0```

### 输出

```
5```

## 样例 #2

### 输入

```
10
12 11 8 8 6 6 6 5 3 2 1```

### 输出

```
2596```

# AI分析结果

### 题目中文重写
#### 题目描述
我们称一个无限序列 $ a_{0}, a_{1}, a_2, \ldots $ 为非递增序列，当且仅当对于所有 $ i\ge 0 $，都有 $ a_i \ge a_{i+1} $。

有一个无限向右和向下延伸的网格。左上角的单元格坐标为 $ (0,0) $。行从上到下编号为 $ 0 $ 到正无穷，列从左到右编号为 $ 0 $ 到正无穷。

同时有一个非递增的无限序列 $ a_{0}, a_{1}, a_2, \ldots $。你会得到 $ a_0 $, $ a_1 $, $ \ldots $, $ a_n $ 的值；对于所有 $ i>n $，$ a_i=0 $。对于每一对 $ x $ 和 $ y $，坐标为 $ (x,y) $ 的单元格（即位于第 $ x $ 行和第 $ y $ 列的交点处），若 $ y < a_x $ 则该单元格为白色，否则为黑色。

初始时，在 $ (0,0) $ 处有一个名为 Jina 的玩偶。你可以进行以下操作：
- 选择一个位于 $ (x,y) $ 处的玩偶，将其移除，并在 $ (x,y + 1) $ 和 $ (x + 1,y) $ 处各放置一个玩偶。

请注意，同一单元格中可以同时存在多个玩偶；在一次操作中，你仅移除一个玩偶。你的目标是使所有白色单元格中的玩偶数量都为 $ 0 $。

实现该目标所需的最少操作次数是多少？请将答案对 $ 10^9 + 7 $ 取模后输出。

#### 说明/提示
考虑第一个样例。在给定的网格中，单元格 $ (0,0) $、$ (0,1) $、$ (1,0) $、$ (1,1) $ 为白色，其他所有单元格为黑色。我们使用三元组来描述网格：三元组 $ (x,y,z) $ 表示单元格 $ (x,y) $ 上放置了 $ z $ 个玩偶。初始时，网格的状态为 $ (0,0,1) $。

一种最优的操作序列如下：
- 对 $ (0,0) $ 进行操作。此时网格的状态变为 $ (1,0,1) $、$ (0,1,1) $。
- 对 $ (0,1) $ 进行操作。此时网格的状态变为 $ (1,0,1) $、$ (1,1,1) $、$ (0,2,1) $。
- 对 $ (1,0) $ 进行操作。此时网格的状态变为 $ (1,1,2) $、$ (0,2,1) $、$ (2,0,1) $。
- 对 $ (1,1) $ 进行操作。此时网格的状态变为 $ (1,1,1) $、$ (0,2,1) $、$ (2,0,1) $、$ (1,2,1) $、$ (2,1,1) $。
- 对 $ (1,1) $ 进行操作。此时网格的状态变为 $ (0,2,1) $、$ (2,0,1) $、$ (1,2,2) $、$ (2,1,2) $。

现在所有白色单元格中的玩偶数量都为 $ 0 $，因此我们通过 $ 5 $ 次操作实现了目标。

#### 样例 #1
##### 输入
```
2
2 2 0
```
##### 输出
```
5
```

#### 样例 #2
##### 输入
```
10
12 11 8 8 6 6 6 5 3 2 1
```
##### 输出
```
2596
```

### 综合分析与结论
这些题解的核心思路都是将问题转化为杨辉三角模型，利用组合数来求解。具体步骤为：先发现操作规则与杨辉三角的递推关系，得出每个格子的操作次数对应杨辉三角中的值；再将每行的操作次数求和转化为一个组合数公式；最后通过预处理组合数的阶乘和逆元，以 $O(n)$ 的时间复杂度计算最终答案。

不同题解在推导组合数公式和代码实现细节上略有差异，但本质相同。难点在于发现杨辉三角的规律以及对组合数公式的化简和推导。

### 所选题解
- **作者：lenlen（5星）**
    - **关键亮点**：思路清晰，详细推导了从杨辉三角到最终组合数公式的过程，代码注释详细，易于理解。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=5e5+7232,mod=1e9+7;
long long n,a[N];
long long inv[N],deinv[N],ans;
long long po(long long x,long long y)
{
    long long sum=1;
    while(y) 
    {
        if(y&1) sum=sum*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return sum;
}
long long C(long long n,long long m)
{
    if(m<0) return 0;
    return inv[n]*deinv[m]%mod*deinv[n-m]%mod;
}
int main()
{
    scanf("%lld",&n);++n;
    for(long long i=1;i<=n;i++) scanf("%lld",&a[i]);
    inv[0]=1;deinv[0]=1;
    for(long long i=1;i<=N-10;i++)
    {
        inv[i]=inv[i-1]*i%mod;
        deinv[i]=po(inv[i],mod-2);
    }
    for(long long i=1;i<=n;i++) ans=(ans+C(a[i]+i-1,a[i]-1))%mod;
    printf("%lld\n",ans);
}
```
    - **核心实现思想**：通过 `po` 函数实现快速幂计算逆元，`C` 函数计算组合数。预处理阶乘和逆元后，根据公式 `C(a[i]+i-1,a[i]-1)` 累加每行的组合数得到最终答案。

- **作者：liangbowen（4星）**
    - **关键亮点**：配有图示辅助理解，推导过程详细，代码规范，有复杂度分析和优化说明。
    - **核心代码**：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
int qpow(int x, int y)
{
    int ans = 1;
    while (y)
    {
        if (y & 1) ans = (1ll * ans * x) % mod;
        x = (1ll * x * x) % mod;
        y >>= 1;
    }
    return ans;
}
int fac[N << 1], invfac[N << 1];
void init(int n)
{
    fac[0] = invfac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = (1ll * fac[i - 1] * i) % mod;
    invfac[n] = qpow(fac[n], mod - 2);
    for (int i = n - 1; i; i--) invfac[i] = 1ll * invfac[i + 1] * (i + 1) % mod;
}
int C(int a, int b)
{
    if (a < 0 || b < 0 || a - b < 0) return 0;
    return 1ll * fac[a] * invfac[a - b] % mod * invfac[b] % mod;
}
int main()
{
    int n;
    scanf("%d", &n), init(N + n);
    int ans = 0;
    for (int i = 1; i <= n + 1; i++)
    {
        int x;
        scanf("%d", &x);
        ans = (ans + C(i + x - 1, i)) % mod;
    }
    cout << ans;
    return 0;
}
```
    - **核心实现思想**：`qpow` 函数实现快速幂，`init` 函数预处理阶乘和逆元，`C` 函数计算组合数。通过 `C(i + x - 1, i)` 累加每行的组合数得到最终答案。

- **作者：Erinyes（4星）**
    - **关键亮点**：通过打表发现杨辉三角规律，思路直观，代码简洁明了。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define maxn 500005
#define int long long
#define mod 1000000007
using namespace std;
int n;
int a[maxn],fac[maxn],inv[maxn];
int power(int x,int k){
    if(!k) return 1ll;
    int res=power(x*x%mod,k>>1);
    return res*(k&1?x:1ll)%mod;
}
void init(){
    fac[0]=1; for(int i=1;i<=500000;i++) fac[i]=fac[i-1]*i%mod;
    inv[0]=1; for(int i=1;i<=500000;i++) inv[i]=power(fac[i],mod-2);
}
int C(int n,int m){return n<m?0:fac[n]*inv[m]%mod*inv[n-m]%mod;}
signed main(){
    cin>>n; init();
    for(int i=0;i<=n;i++) cin>>a[i];
    int ans=0;
    for(int i=0;i<=n;i++) ans+=C(i+a[i],i+1),ans%=mod;
    cout<<ans<<endl;
    return 0;
}
```
    - **核心实现思想**：`power` 函数实现快速幂，`init` 函数预处理阶乘和逆元，`C` 函数计算组合数。通过 `C(i+a[i],i+1)` 累加每行的组合数得到最终答案。

### 最优关键思路或技巧
- **思维方式**：通过手玩样例、打表等方法发现操作规则与杨辉三角的联系，将问题转化为组合数计算。
- **算法优化**：利用组合数的性质化简求和公式，将 $O(n^2)$ 的复杂度优化到 $O(n)$。
- **代码实现**：预处理阶乘和逆元，使用快速幂计算逆元，提高组合数计算的效率。

### 可拓展之处
同类型题可能会改变网格的形状、操作规则或限制条件，但核心思路仍可能是寻找递推关系并转化为组合数问题。类似算法套路包括利用递推公式推导通项公式、预处理数据以优化复杂度等。

### 洛谷相似题目推荐
- P1313 计算系数：考察组合数的计算和二项式定理。
- P2822 组合数问题：涉及组合数的计算和前缀和优化。
- P3197 [HNOI2008]越狱：需要运用组合数学和快速幂解决计数问题。

### 个人心得摘录与总结
- **作者：jia_shengyuan**：磕了一个小时D题不会，第二天看E题。注意到 $a_i$ 的单调性不影响暴力正确性，推测正解用公式计算。对于组合数化简，不会组合数裂项，用了小奥学的整数裂项方法。
总结：做题时可从题目条件的性质推测解题方向，当常规方法不会时，可尝试用学过的其他技巧解决问题。 

---
处理用时：63.46秒