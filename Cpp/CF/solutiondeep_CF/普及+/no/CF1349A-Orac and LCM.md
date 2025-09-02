# 题目信息

# Orac and LCM

## 题目描述

For the multiset of positive integers $ s=\{s_1,s_2,\dots,s_k\} $ , define the Greatest Common Divisor (GCD) and Least Common Multiple (LCM) of $ s $ as follow:

- $ \gcd(s) $ is the maximum positive integer $ x $ , such that all integers in $ s $ are divisible on $ x $ .
- $ \textrm{lcm}(s) $ is the minimum positive integer $ x $ , that divisible on all integers from $ s $ .

For example, $ \gcd(\{8,12\})=4,\gcd(\{12,18,6\})=6 $ and $ \textrm{lcm}(\{4,6\})=12 $ . Note that for any positive integer $ x $ , $ \gcd(\{x\})=\textrm{lcm}(\{x\})=x $ .

Orac has a sequence $ a $ with length $ n $ . He come up with the multiset $ t=\{\textrm{lcm}(\{a_i,a_j\})\ |\ i<j\} $ , and asked you to find the value of $ \gcd(t) $ for him. In other words, you need to calculate the GCD of LCMs of all pairs of elements in the given sequence.

## 说明/提示

For the first example, $ t=\{\textrm{lcm}(\{1,1\})\}=\{1\} $ , so $ \gcd(t)=1 $ .

For the second example, $ t=\{120,40,80,120,240,80\} $ , and it's not hard to see that $ \gcd(t)=40 $ .

## 样例 #1

### 输入

```
2
1 1```

### 输出

```
1```

## 样例 #2

### 输入

```
4
10 24 40 80```

### 输出

```
40```

## 样例 #3

### 输入

```
10
540 648 810 648 720 540 594 864 972 648```

### 输出

```
54```

# AI分析结果

### 题目中文重写
# Orac 和最小公倍数

## 题目描述
对于正整数的多重集 $ s=\{s_1,s_2,\dots,s_k\} $，定义 $ s $ 的最大公约数（GCD）和最小公倍数（LCM）如下：
- $ \gcd(s) $ 是最大的正整数 $ x $，使得 $ s $ 中的所有整数都能被 $ x $ 整除。
- $ \textrm{lcm}(s) $ 是最小的正整数 $ x $，它能被 $ s $ 中的所有整数整除。

例如，$ \gcd(\{8,12\}) = 4 $，$ \gcd(\{12,18,6\}) = 6 $，$ \textrm{lcm}(\{4,6\}) = 12 $。注意，对于任何正整数 $ x $，$ \gcd(\{x\}) = \textrm{lcm}(\{x\}) = x $。

Orac 有一个长度为 $ n $ 的序列 $ a $。他构造了多重集 $ t = \{ \textrm{lcm}(\{a_i,a_j\}) \ | \ i < j \} $，并要求你为他求出 $ \gcd(t) $ 的值。换句话说，你需要计算给定序列中所有元素对的最小公倍数的最大公约数。

## 说明/提示
对于第一个样例，$ t = \{ \textrm{lcm}(\{1,1\}) \} = \{1\} $，所以 $ \gcd(t) = 1 $。
对于第二个样例，$ t = \{120,40,80,120,240,80\} $，不难看出 $ \gcd(t) = 40 $。

## 样例 #1
### 输入
```
2
1 1
```
### 输出
```
1
```

## 样例 #2
### 输入
```
4
10 24 40 80
```
### 输出
```
40
```

## 样例 #3
### 输入
```
10
540 648 810 648 720 540 594 864 972 648
```
### 输出
```
54
```

### 算法分类
数学

### 综合分析与结论
这些题解主要围绕计算给定序列中所有元素对的最小公倍数的最大公约数展开，不同题解思路和方法各有不同。
- **思路对比**：部分题解从公式变形入手，将原式转化为更易计算的形式；部分题解从质因数分解角度，考虑每个质因数对答案的贡献；还有题解通过预处理前缀和后缀 $\gcd$ 来简化计算。
- **算法要点**：涉及到 $\gcd$ 和 $\text{lcm}$ 的计算、质因数分解、前缀和后缀 $\gcd$ 的预处理、排序等操作。
- **解决难点**：主要解决如何高效计算 $\gcd\{ \text{lcm}(a_i,a_j)\;|\;i < j \}$，不同题解采用不同方法来优化计算过程，如利用公式变形减少计算量、通过剪枝提高效率等。

### 所选题解
- **作者：H6_6Q (5星)**
  - **关键亮点**：思路清晰，通过公式变形将问题转化为求 $\gcd\{ a_i\times a_j\;|\;i < j \}$ 和 $\gcd(a_1,a_2 \;...\;a_n)$，并利用后缀 $\gcd$ 预处理优化计算，代码简洁易懂，时间复杂度低。
```cpp
#include<bits/stdc++.h>
#define LL long long

using namespace std;

LL read()
{
    LL ans=0,f=1;
    char c=getchar();
    while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return ans*f;
}

const LL N=1e5+5;
LL n,a[N],b[N],ans;

int main()
{
    n=read();
    for(LL i=1;i<=n;++i)
        a[i]=read();
    for(LL i=n;i>=1;--i)
        // 预处理后缀 gcd
        b[i]=__gcd(b[i+1],a[i]);
    for(LL i=1;i<=n;++i)
        // 计算 gcd { ai , aj | i < j }
        ans=__gcd(ans,a[i]*b[i+1]);
    // 答案就是 gcd { ai , aj | i < j } / gcd ( a1 , a2 ... an )
    printf("%lld\n",ans/b[1]);
    return 0;
} 
```
核心实现思想：先预处理出后缀 $\gcd$ 数组 $b$，然后枚举 $a_i$，计算 $a_i\times b[i + 1]$ 并与当前答案取 $\gcd$，最后将结果除以所有数的 $\gcd$（即 $b[1]$）得到最终答案。

- **作者：CYJian (4星)**
  - **关键亮点**：从质因数分解角度考虑问题，思路独特，指出对于一个质数 $p$ 对答案的贡献是所有数中 $p$ 的第二大的指数，通过欧拉筛处理出每个数的最小质因子，复杂度可控。
```cpp
const int MAXN = 300010;

int f[MAXN];
int g[MAXN];

int tot;
int pri[MAXN];
int chk[MAXN];
int Min[MAXN];

inline void Sieve(int n) {
    for(int i = 2; i <= n; i++) {
        if(!chk[i]) pri[++tot] = i, Min[i] = i;
        for(int j = 1; j <= tot; j++) {
            if(i * pri[j] > n) break;
            chk[i * pri[j]] = 1;
            Min[i * pri[j]] = pri[j];
            if(i % pri[j] == 0) break;
        }
    }
}

vector<int>d[MAXN];

int main() {
    Sieve(200000);
    
    int n = ri;
    for(int i = 1; i <= n; i++) {
        int x = ri;
        while(x > 1) {
            int p = Min[x], ct = 0;
            while(x % p == 0) x /= p, ++ct;
            d[p].push_back(ct);
        }
    }
    
    ll res = 1;
    for(int i = 1; i <= 200000; i++) {
        if(d[i].size() >= n - 1) {
            sort(d[i].begin(), d[i].end());
            int pw = d[i][0];
            if(d[i].size() == n) pw = d[i][1];
            while(pw--) res *= i;
        }
    }

    cout << res << endl;
    return 0;
}
```
核心实现思想：先用欧拉筛预处理出每个数的最小质因子，然后对每个数进行质因数分解，记录每个质因数的指数，最后对于每个质因数，若其指数个数不少于 $n - 1$ 个，则取其第二小的指数作为该质因数在答案中的指数，将所有质因数的幂相乘得到最终答案。

- **作者：WeLikeStudying (4星)**
  - **关键亮点**：对顶楼大佬思路进行补充和优化，指出不需要 $O(n)$ 的后缀 $\gcd$ 和数组，提供更紧的时间界，通过推式子简化计算，代码简洁且复杂度低。
```cpp
//尊前不用翠眉颦，人生如逆旅，我亦是行人
#include<fstream>
using namespace std;
const int MAXN=1e5+1;
int n,a[MAXN],g;
long long dc=1;
long long gcd(long long a,long long b)
{
    return (a%b==0)?b:gcd(b,a%b);
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    g=a[0];
    dc=1ll*a[0]*a[1];
    for(int i=1;i<n-1;i++)
    {
        long long part=1ll*g*a[i];
        g=gcd(a[i],g);
        dc=gcd(dc,part);
    }
    dc=gcd(dc,1ll*g*a[n-1]);
    g=gcd(a[n-1],g);
    printf("%lld",dc/g);
    return 0;
}
```
核心实现思想：通过推式子将原式转化为 $\frac{\gcd\lbrace a_i\gcd\lbrace a_j|j<i\rbrace\rbrace}{\gcd\lbrace a_i\rbrace}$，在遍历数组过程中不断更新 $\gcd$ 和中间结果 $dc$，最后将 $dc$ 除以所有数的 $\gcd$ 得到最终答案。

### 最优关键思路或技巧
- **公式变形**：将 $\gcd\{ \text{lcm}(a_i,a_j)\;|\;i < j \}$ 变形为更易计算的形式，如 $\frac{\gcd\{ a_i\times a_j\;|\;i < j \}}{\gcd(a_1,a_2 \;...\;a_n)}$ 或 $\frac{\gcd\lbrace a_i\gcd\lbrace a_j|j<i\rbrace\rbrace}{\gcd\lbrace a_i\rbrace}$，减少计算量。
- **质因数分解**：考虑每个质因数对答案的贡献，将问题转化为求每个质因数的第二大指数，简化问题。
- **预处理**：预处理后缀 $\gcd$ 或前缀和后缀 $\gcd$，可以快速计算部分结果，提高效率。

### 可拓展之处
同类型题可能会涉及到更多数论相关的概念，如欧拉函数、莫比乌斯反演等。类似算法套路可以应用在其他需要计算 $\gcd$ 和 $\text{lcm}$ 的问题中，通过公式变形和质因数分解来优化计算。

### 推荐洛谷题目
- P1072 [NOIP2009 提高组] Hankson 的趣味题
- P2152 [SDOI2009] SuperGCD
- P1306 斐波那契公约数

### 个人心得摘录与总结
- **WeLikeStudying**：一开始对 $\gcd$ 运算不能将除法分离出来感到困惑，但后来明白对于每个质数 $p$，$\gcd\lbrace a_ia_j|i<j\rbrace$ 相当于求出了其指数的最小值和次小值之和，$\gcd\lbrace\gcd(a_i,a_j)|i<j\rbrace$ 则相当于求出了其指数的最小值，两者相减便是答案。总结：在处理复杂的数论问题时，要深入理解每个运算的本质，通过对质数的分析来简化问题。

---
处理用时：75.71秒