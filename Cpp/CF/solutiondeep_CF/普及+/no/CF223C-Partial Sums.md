# 题目信息

# Partial Sums

## 题目描述

You've got an array $ a $ , consisting of $ n $ integers. The array elements are indexed from 1 to $ n $ . Let's determine a two step operation like that:

1. First we build by the array $ a $ an array $ s $ of partial sums, consisting of $ n $ elements. Element number $ i $ ( $ 1<=i<=n $ ) of array $ s $ equals ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF223C/c051478f9fc3965030766767424a5562a646a777.png). The operation $ x mod y $ means that we take the remainder of the division of number $ x $ by number $ y $ .
2. Then we write the contents of the array $ s $ to the array $ a $ . Element number $ i $ ( $ 1<=i<=n $ ) of the array $ s $ becomes the $ i $ -th element of the array $ a $ ( $ a_{i}=s_{i} $ ).

You task is to find array $ a $ after exactly $ k $ described operations are applied.

## 样例 #1

### 输入

```
3 1
1 2 3
```

### 输出

```
1 3 6
```

## 样例 #2

### 输入

```
5 0
3 14 15 92 6
```

### 输出

```
3 14 15 92 6
```

# AI分析结果

### 题目内容
# 部分和

## 题目描述
你有一个由 $n$ 个整数组成的数组 $a$ ，数组元素的索引从1到 $n$ 。让我们定义一个两步操作如下：
1. 首先，我们根据数组 $a$ 构建一个部分和数组 $s$ ，该数组也由 $n$ 个元素组成。数组 $s$ 的第 $i$ 个元素（$1\leq i\leq n$）等于 $\sum_{j = 1}^{i}a_j\bmod{10^9 + 7}$ 。操作 $x\bmod y$ 表示我们取 $x$ 除以 $y$ 的余数。
2. 然后，我们将数组 $s$ 的内容写入数组 $a$ 。数组 $s$ 的第 $i$ 个元素（$1\leq i\leq n$）成为数组 $a$ 的第 $i$ 个元素（$a_i = s_i$）。

你的任务是找出在恰好应用 $k$ 次上述操作之后的数组 $a$ 。

## 样例 #1
### 输入
```
3 1
1 2 3
```
### 输出
```
1 3 6
```

## 样例 #2
### 输入
```
5 0
3 14 15 92 6
```
### 输出
```
3 14 15 92 6
```

### 算法分类
数学（组合数学）

### 题解综合分析与结论
这几道题解都围绕求数组经过 $k$ 次前缀和操作后的结果展开。核心难点在于 $k$ 很大（$k\leq 10^9$），不能简单暴力计算前缀和或预处理组合数。各题解都通过寻找系数规律，利用组合数来解决问题，但在具体思路和实现细节上有差异。

### 所选的题解
- **作者：ql12345（5星）**
  - **关键亮点**：通过手动推导小范围数据得出系数为组合数 $C(j + k - i - 1, j - i)$ 的规律。在计算组合数时，利用 $j - i$ 差值固定的特点递推计算，优化了组合数的计算，时间复杂度降为 $O(N)$，思路清晰，代码简洁高效。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,k,a[2020],inv[2020],c[2020];
signed main(){
    cin>>n>>k; for(int i=1;i<=n;++i)cin>>a[i];
    if(!k){for(int i=1;i<=n;++i)cout<<a[i]<<' ';return 0;}
    inv[0]=inv[1]=1; for(int i=2;i<=n;++i)inv[i]=inv[mod%i]*(mod-mod/i)%mod;
    c[0]=1; for(int i=1;i<=n;++i)c[i]=c[i-1]*inv[i]%mod*(i+k-1)%mod;
    for(int i=1,ans=0;i<=n;++i,ans=0){
        for(int j=1;j<=i;++j)(ans+=a[j]*c[i-j]%mod)%=mod;
        cout<<ans<<' ';
    }
}
```
  - **核心实现思想**：先特判 $k = 0$ 的情况直接输出原数组。然后计算逆元 `inv`，利用逆元递推计算所需的组合数 `c`，最后通过双重循环，根据组合数计算每个位置的最终值。

- **作者：johnsmith0x3f（4星）**
  - **关键亮点**：通过定义 $k$ 阶前缀和的递推式，结合杨辉三角得出系数 $c_j = C_{k + i - j}^{i - j}$ 。针对 $k$ 大无法预处理阶乘的问题，利用 $i - j$ 的范围进行暴力预处理组合数，思路较为常规但清晰易懂。
  - **核心代码**：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int read(){
    int x = 0, f = 1; char c = getchar();
    while(isdigit(c)^1) f &= (c!=45), c = getchar();
    while(isdigit(c)) x = (x<<1) + (x<<3) + (c^48), c = getchar();
    return f? x : -x;
}

const int maxn = 2005;
const int mod = 1000000007;
int n, m, a[maxn], inv[maxn], C[maxn];

inline void init(){
    inv[1] = 1;
    for(int i=2; i<=n; ++i) inv[i] = (mod-mod/i) * inv[mod%i] % mod;
}

signed main(){
    n = read(), m = read(), init(), C[0] = C[1] = 1;
    for(int i=1; i<=n; C[++i]=1)
        for(int j=1; j<=i; ++j) C[i] = C[i] * (m+j-1) % mod * inv[j] % mod;
    for(int i=1, ans=0; i<=n; ++i, ans=0){
        for(int j=1; j<=i; ++j) ans = (ans+C[i-j]*a[j]%mod) % mod;
        printf("%lld ", ans);
    }
    return 0;
}
```
  - **核心实现思想**：先定义读入函数 `read` 和初始化逆元函数 `init`。在主函数中读入数据并初始化组合数 `C`，通过双重循环预处理组合数，最后同样通过双重循环根据组合数计算每个位置的最终值。

### 最优关键思路或技巧
通过手动推导小范围数据找到系数与组合数的关系，利用组合数性质和 $i - j$ 的范围优化组合数计算，避免了因 $k$ 过大导致的预处理阶乘的困难。

### 可拓展之处
此类题目属于组合数学与数组操作结合的类型，类似套路是通过找规律得出系数与组合数的联系，进而解决问题。对于其他类似多次数组变换操作求最终结果的题目，都可以尝试从找规律、利用数学性质方面入手。

### 洛谷相似题目推荐
- [P3807 【模板】卢卡斯定理](https://www.luogu.com.cn/problem/P3807)：同样涉及组合数计算，不过重点考察卢卡斯定理，与本题利用组合数解决多次前缀和问题类似，都需要对组合数有深入理解。
- [P2822 [NOIP2016 提高组] 组合数问题](https://www.luogu.com.cn/problem/P2822)：该题在组合数计算基础上结合了取模运算和动态规划思想，与本题在组合数运用和对结果取模方面有相似点。
- [P6669 [清华集训2016] 组合数问题](https://www.luogu.com.cn/problem/P6669)：同样围绕组合数展开，需要运用数学知识优化组合数计算，与本题在解决组合数相关问题上思路类似。 

---
处理用时：53.09秒