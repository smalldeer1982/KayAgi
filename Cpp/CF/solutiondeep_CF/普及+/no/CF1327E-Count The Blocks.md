# 题目信息

# Count The Blocks

## 题目描述

You wrote down all integers from $ 0 $ to $ 10^n - 1 $ , padding them with leading zeroes so their lengths are exactly $ n $ . For example, if $ n = 3 $ then you wrote out 000, 001, ..., 998, 999.

A block in an integer $ x $ is a consecutive segment of equal digits that cannot be extended to the left or to the right.

For example, in the integer $ 00027734000 $ there are three blocks of length $ 1 $ , one block of length $ 2 $ and two blocks of length $ 3 $ .

For all integers $ i $ from $ 1 $ to $ n $ count the number of blocks of length $ i $ among the written down integers.

Since these integers may be too large, print them modulo $ 998244353 $ .

## 样例 #1

### 输入

```
1```

### 输出

```
10```

## 样例 #2

### 输入

```
2```

### 输出

```
180 10```

# AI分析结果

### 题目翻译
## 统计块的数量

### 题目描述
你写下了从 $0$ 到 $10^n - 1$ 的所有整数，并在前面补零，使它们的长度恰好为 $n$。例如，如果 $n = 3$，那么你写下的数是 000, 001, ..., 998, 999。

整数 $x$ 中的一个块是指一段连续的相同数字，且不能再向左或向右扩展。

例如，在整数 $00027734000$ 中，有三个长度为 $1$ 的块，一个长度为 $2$ 的块和两个长度为 $3$ 的块。

对于从 $1$ 到 $n$ 的所有整数 $i$，统计写下的整数中长度为 $i$ 的块的数量。

由于这些整数可能非常大，请将结果对 $998244353$ 取模。

### 样例 #1
#### 输入
```
1
```
#### 输出
```
10
```

### 样例 #2
#### 输入
```
2
```
#### 输出
```
180 10
```

### 算法分类
数学

### 综合分析与结论
这些题解主要围绕计算所有 $n$ 位十进制整数中不同长度的极大连续数字块的数量展开。不同题解采用了不同的思路和方法，大致可分为以下几类：
1. **分类讨论法**：根据连续块的位置（边界或中间）和长度进行分类讨论，利用乘法原理计算每种情况下的方案数，最后汇总得到结果。
2. **找规律法**：通过手动找规律或编写爆搜程序找出规律，进而得到递推公式或通项公式来计算结果。
3. **容斥原理法**：先计算不要求不可拓展的长度为 $i$ 的块的方案数，再通过容斥原理去掉可拓展的部分。

### 所选题解
- **Alex_Wei（4星）**
  - **关键亮点**：思路清晰，通过分类讨论不同长度连续块的位置，利用乘法原理计算贡献，代码简洁易读。
  - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
 
const ll mod=998244353;
const int N=2e5+5;
 
ll n,pw[N];

int main(){
    cin>>n,pw[0]=1;
    for(int i=1;i<=n;i++)pw[i]=pw[i-1]*10%mod;
    for(int i=1;i<=n;i++){
        if(i==n)puts("10");
        else cout<<(pw[n-i]*18+(n-i-1)*pw[n-i-1]*81)%mod<<" ";
    }
    return 0;
}
```
  - **核心实现思想**：先预处理 $10$ 的幂次方，然后对于每个长度 $i$ 进行分类讨论。当 $i = n$ 时，答案为 $10$；当 $i < n$ 时，分别计算连续块在边界和中间的贡献，最后将结果相加并对 $998244353$ 取模。

- **WYXkk（4星）**
  - **关键亮点**：通过编写爆搜程序找出规律，进而推导出通项公式，方法独特。
  - **核心代码**：
```cpp
#include<cstdio>
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define Set(a) memset(a,0,sizeof(a))
#define F(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
#define UF(i,a,b) for(register int i=a,i##end=b;i>=i##end;--i)
#define openf(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define re register
#define ri re int
#define il inline
typedef long long ll;
typedef unsigned long long ull;
template<typename T> inline T rd(T& x)
{
    T f=1;x=0;char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
    for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(T)(c-'0');
    x*=f;
    return x;
}
ll rd(){ll x;rd(x);return x;}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int inf=1<<30;

const ll p=998244353;
ll qp(ll x){if(!x) return 1;ll w=qp(x>>1);w=w*w%p;return x&1?w*10%p:w;}
int main()
{
    ll n=rd();
    UF(i,n,2) printf("%lld ",(81*i+18)*qp(i-2)%p);
    cout<<10<<endl;
    return 0;
}
```
  - **核心实现思想**：先编写爆搜程序找出规律，发现 $n$ 的答案是 $n - 1$ 的答案在前面加一个数，进而推导出通项公式 $a_n = 10^{n - 2}(81n + 18)\ (n \geq 2)$，最后根据通项公式计算结果并输出。

### 关键思路或技巧
- **分类讨论**：将连续块的位置分为边界和中间，分别计算不同位置的贡献，最后汇总。
- **找规律**：通过手动计算或编写爆搜程序找出规律，进而得到递推公式或通项公式。
- **预处理幂次方**：为了避免重复计算，预处理 $10$ 的幂次方，提高效率。

### 拓展思路
同类型题目可能会改变数字的进制、块的定义或限制条件，解题时仍可采用分类讨论、找规律等方法。类似的算法套路包括组合数学中的计数问题、容斥原理的应用等。

### 推荐题目
1. [P1088 火星人](https://www.luogu.com.cn/problem/P1088)：考察组合数学和全排列的知识。
2. [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)：涉及二项式定理和组合数的计算。
3. [P2671 [NOIP2015 普及组] 求和](https://www.luogu.com.cn/problem/P2671)：需要运用数学推导和前缀和优化。

### 个人心得
- **WYXkk**：通过编写爆搜程序找出规律，强调了找规律在解题中的重要性，即“找 规 律 t x d y！！！”。

---
处理用时：51.72秒