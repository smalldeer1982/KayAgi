# 题目信息

# [NICA #3] 星空（Easy Version）

## 题目背景

**Easy Version 和 Hard Version 差别在于数据范围。**

## 题目描述

小 R 有一个长度为 $n$ 的序列 $a$，保证序列中的每个数都是 $2$ 的整数次幂。

小 M 有一个数 $x$，她希望重新排列序列 $a$，使得不存在一个 $i\in[1,n)$ 满足 $a_i+a_{i+1}>x$。重排的方式为：选择一个 $1\sim n$ 的排列 $p$，然后令新序列 $a'$ 满足 $a'_i=a_{p_i}$。$a'$ 即为重排后的序列。

现在你想要知道有多少种重排的方式能满足小 M 的要求。两种重排方式不同当且仅当选择的排列 $p$ 不同。答案对 $10^9+7$ 取模。

## 说明/提示

数据保证，$2 \leq n \leq 61$，$1 \leq a_i \leq 2^{60}$，$1\le x< 2^{63}$。**每一个 $a_i$ 都不重复**。

## 样例 #1

### 输入

```
4 20
2 4 8 16```

### 输出

```
12```

# AI分析结果

### 综合分析与结论

本题的核心在于利用序列中每个元素都是2的整数次幂且不重复的特性，简化问题。通过分析，发现只需关注最大值与其相邻元素的和是否超过x，其他元素的排列方式对结果没有影响。因此，问题转化为如何计算最大值与其相邻元素的合法排列数。

各题解的思路基本一致，主要分为以下几步：
1. 找到序列中的最大值。
2. 统计与最大值相加不超过x的元素个数（记为cnt）。
3. 根据最大值的位置（开头、结尾或中间），计算合法的排列数。

### 所选高星题解

#### 1. 作者：起名字重要吗 (4星)
**关键亮点**：
- 思路清晰，直接利用排列组合公式计算合法排列数。
- 代码简洁，预处理阶乘，减少重复计算。
- 详细解释了最大值在不同位置时的排列数计算方式。

**核心代码**：
```cpp
long long n,x,a[70],maxa,fac[70]= {1},cnt,mod=1e9+7;
int main() {
    scanf("%lld%lld",&n,&x);
    for(int i=1; i<=n; i++) scanf("%lld",&a[i]),maxa=max(maxa,a[i]);
    for(int i=1; i<=n; fac[i]=(fac[i-1]*i)%mod,i++) if(a[i]!=maxa&&a[i]+maxa<=x) cnt++;
    printf("%lld",(2*cnt*fac[n-2]%mod+(n-2)*cnt*(cnt-1)*fac[n-3]%mod)%mod);
    return 0;
}
```
**实现思想**：预处理阶乘，统计与最大值相加不超过x的元素个数，根据最大值的位置计算合法排列数。

#### 2. 作者：a_little_carrot (4星)
**关键亮点**：
- 详细证明了任意两个非最大值的元素相加小于最大值的性质。
- 优化了阶乘计算，预处理阶乘数组，减少时间复杂度。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
#include "iostream"
using namespace std ;
#define For(i,l,r) for(int i=(l);i<=(r);++i)
typedef long long ll ;
const int mod=1e9+7,N=64 ;
ll n,x,maxn,f[N]{1,1},p[N],cnt,ans ;
ll read(ll &m) {m=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar());for(;ch>='0'&&ch<='9';ch=getchar())m=m*10+ch-'0';return m;}
void init() {For(i,2,N)f[i]=(f[i-1]*i)%mod;}
int main() {
    init();read(n),read(x) ;
    For(i,1,n) maxn=max(maxn,read(p[i])) ;
    For(i,1,n) cnt+=(p[i]!=maxn)&&(p[i]+maxn<=x) ;
    ans=(2*cnt*f[n-2])%mod;For(i,2,n-1) ans=(ans+cnt*(cnt-1)*f[n-3])%mod ;
    cout<<ans ;
    return 0 ;
}
```
**实现思想**：预处理阶乘，统计与最大值相加不超过x的元素个数，根据最大值的位置计算合法排列数。

#### 3. 作者：wyf1202 (4星)
**关键亮点**：
- 详细分析了最大值在不同位置时的排列数计算方式。
- 代码逻辑清晰，直接枚举最大值的位置并计算合法排列数。
- 预处理阶乘，减少重复计算。

**核心代码**：
```cpp
const int mod=1e9+7;
long long n,x,mx,sum,ans,a[100005],j[100005];
int main(){
    cin>>n>>x;
    for(int i=1;i<=n;++i)cin>>a[i];
    for(int i=1;i<=n;++i)if(a[i]>mx)mx=a[i];
    for(int i=1;i<=n;++i)
        if(a[i]!=mx&&a[i]+mx<=x)sum++;
    j[1]=1;
    for(int i=2;i<=n;++i)j[i]=(j[i-1]*i)%mod;
    for(int i=1;i<=n;++i){
        if(i==1||i==n)ans=(ans+sum*j[n-2])%mod;
        else ans=(ans+sum*(sum-1)*j[n-3])%mod;
    } cout<<ans;	return 0;
}
```
**实现思想**：预处理阶乘，统计与最大值相加不超过x的元素个数，根据最大值的位置计算合法排列数。

### 最优关键思路或技巧
- **预处理阶乘**：通过预处理阶乘数组，减少重复计算，优化时间复杂度。
- **排列组合**：利用排列组合公式，根据最大值的位置计算合法排列数。
- **性质利用**：利用序列中每个元素都是2的整数次幂且不重复的性质，简化问题。

### 可拓展之处
- **类似问题**：对于其他涉及排列组合且需要满足特定条件的题目，可以借鉴本题的思路，先找到关键元素，再计算合法排列数。
- **优化技巧**：预处理阶乘、利用数学性质简化问题等技巧在其他题目中也有广泛应用。

### 推荐题目
1. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
2. [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057)
3. [P1063 能量项链](https://www.luogu.com.cn/problem/P1063)

### 个人心得
- **调试经历**：在计算排列数时，注意阶乘的预处理和取模运算，避免溢出。
- **顿悟感想**：通过分析题目性质，发现只需关注最大值与其相邻元素的和，大大简化了问题。

---
处理用时：40.51秒