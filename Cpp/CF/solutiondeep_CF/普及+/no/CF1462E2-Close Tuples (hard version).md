# 题目信息

# Close Tuples (hard version)

## 题目描述

This is the hard version of this problem. The only difference between the easy and hard versions is the constraints on $ k $ and $ m $ . In this version of the problem, you need to output the answer by modulo $ 10^9+7 $ .

You are given a sequence $ a $ of length $ n $ consisting of integers from $ 1 $ to $ n $ . The sequence may contain duplicates (i.e. some elements can be equal).

Find the number of tuples of $ m $ elements such that the maximum number in the tuple differs from the minimum by no more than $ k $ . Formally, you need to find the number of tuples of $ m $ indices $ i_1 < i_2 < \ldots < i_m $ , such that

 $ $$$\max(a_{i_1}, a_{i_2}, \ldots, a_{i_m}) - \min(a_{i_1}, a_{i_2}, \ldots, a_{i_m}) \le k. $ $ </p><p>For example, if  $ n=4 $ ,  $ m=3 $ ,  $ k=2 $ ,  $ a=\[1,2,4,3\] $ , then there are two such triples ( $ i=1, j=2, z=4 $  and  $ i=2, j=3, z=4 $ ). If  $ n=4 $ ,  $ m=2 $ ,  $ k=1 $ ,  $ a=\[1,1,1,1\] $ , then all six possible pairs are suitable.</p><p><span class="tex-font-style-bf">As the result can be very large, you should print the value modulo  $ 10^9 + 7 $  (the remainder when divided by  $ 10^9 + 7$$$).

## 样例 #1

### 输入

```
4
4 3 2
1 2 4 3
4 2 1
1 1 1 1
1 1 1
1
10 4 3
5 6 1 3 2 9 8 1 2 4```

### 输出

```
2
6
1
20```

# AI分析结果

### 题目中文重写
# 紧密元组（困难版本）

## 题目描述
这是该问题的困难版本。简单版本和困难版本之间的唯一区别在于 $k$ 和 $m$ 的约束条件。在这个版本的问题中，你需要输出答案对 $10^9 + 7$ 取模的结果。

给定一个长度为 $n$ 的序列 $a$，其元素为 $1$ 到 $n$ 之间的整数。该序列可能包含重复元素（即某些元素可能相等）。

找出元素个数为 $m$ 的元组的数量，使得元组中的最大值与最小值之差不超过 $k$。形式上，你需要找出 $m$ 个索引 $i_1 < i_2 < \ldots < i_m$ 的元组数量，满足：

$$\max(a_{i_1}, a_{i_2}, \ldots, a_{i_m}) - \min(a_{i_1}, a_{i_2}, \ldots, a_{i_m}) \leq k$$

例如，如果 $n = 4$，$m = 3$，$k = 2$，$a = [1, 2, 4, 3]$，那么有两个这样的三元组（$i = 1, j = 2, z = 4$ 和 $i = 2, j = 3, z = 4$）。如果 $n = 4$，$m = 2$，$k = 1$，$a = [1, 1, 1, 1]$，那么所有六个可能的二元组都是合适的。

由于结果可能非常大，你应该输出该值对 $10^9 + 7$ 取模的结果（即除以 $10^9 + 7$ 的余数）。

## 样例 #1
### 输入
```
4
4 3 2
1 2 4 3
4 2 1
1 1 1 1
1 1 1
1
10 4 3
5 6 1 3 2 9 8 1 2 4
```

### 输出
```
2
6
1
20
```

### 算法分类
组合数学

### 综合分析与结论
这些题解的核心思路都是先对数组进行排序，然后通过枚举最小值，找出满足最大值与最小值之差不超过 $k$ 的元素范围，最后利用组合数计算满足条件的元组数量。不同题解的主要区别在于查找满足条件元素范围的方法以及组合数的计算方式。

### 所选题解
- **light_ght（4星）**
    - **关键亮点**：思路清晰，详细阐述了避免重复计算的方法，代码实现规范，有快速幂和组合数计算的完整实现。
    - **个人心得**：提到最初想直接排序后求区间组合，但因数据可能重复遇到问题，后经学长点拨找到避免重复的方法，还强调了开 `long long` 的重要性。
- **shenmadongdong（4星）**
    - **关键亮点**：思路简洁明了，通过前缀和统计元素个数，方便计算满足条件的元素数量，代码结构清晰。
    - **个人心得**：调侃题目简单，实际思路清晰，实现简洁。
- **ncwzdlsd（4星）**
    - **关键亮点**：思路直接，代码实现简洁，通过双指针查找满足条件的元素范围，计算组合数得出结果。
    - **个人心得**：指出答案与序列顺序无关，这是解题的关键思路。

### 重点代码
#### light_ght 的核心代码
```cpp
const int N = 200005;
const int md = 1000000007;

int a[N];
ll f[N];
ll qpow(ll a, ll b) {  //快速幂
    ll ans = 1, base = a;
    while(b){
        if(b&1)ans=ans*base%md;
        base=base*base%md;
        b>>=1;
    }
    return ans;
}
ll ght(ll n, ll m) {
    if (n<m) return 0;
    return 1ll*f[n]*qpow(f[m],md-2)%md*qpow(f[n-m],md-2)%md;
}
int t,n,m,k;

int main(){
    f[0]=1;
    for(int i=1;i<=200000;i++)
        f[i]=f[i-1]*i%md;	
    
    read(t);
    while(t--){
        read(n,m,k);
        for (int i=0; i<n;i++) 
            read(a[i]);
        sort(a,a+n);
        int p=0;
        ll ans=0;
        for (int i=0;i<n;i++){
            p=(int)(upper_bound(a,a+n,a[i]+k)-a);
            if(p-i>=m) {
                ans+=ght(p-i-1,m-1);
                ans%=md;
            }
        }
        wrti(ans);
    }
    flush();
    return 0;
}
```
**核心实现思想**：先预处理阶乘数组 `f`，然后通过快速幂计算逆元，实现组合数的计算。排序后枚举最小值，利用 `upper_bound` 找到满足条件的最大元素位置，计算组合数并累加结果。

#### shenmadongdong 的核心代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const unsigned mod=1e9+7;
ll ksm(ll x,ll y){ll ret=1;while(y){if(y&1ll)ret=ret*x%mod;y>>=1ll;x=x*x%mod;}return ret;}
ll n,m,k,a[200010],cnt[200010],fac[200010],inv[200010];
ll C(ll n,ll m){if(m>n||m<0)return 0;return fac[n]*inv[m]%mod*inv[n-m]%mod;}

int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    fac[0]=inv[0]=1;
    for(int i=1;i<=200000;i++) fac[i]=fac[i-1]*i%mod;
    for(int i=1;i<=200000;i++) inv[i]=ksm(fac[i],mod-2);
    int T;cin>>T;
    while(T--)
    {
        cin>>n>>m>>k;
        for(int i=1;i<=n;i++) cin>>a[i],cnt[a[i]]++;
        for(int i=1;i<=n;i++) cnt[i]+=cnt[i-1];
        sort(a+1,a+n+1);
        ll ans=0;
        for(int i=n;i>=1;i--)
        {
            if (a[i]>k) ans+=C(i-cnt[a[i]-k-1]-1,m-1),ans%=mod;
            else ans+=C(i-1,m-1),ans%=mod;
        }
        cout<<ans<<'\n';
        for(int i=1;i<=n;i++) cnt[i]=0;
    }
    return 0;
}
```
**核心实现思想**：预处理阶乘和逆元，通过前缀和数组 `cnt` 统计元素个数。排序后枚举最大值，根据前缀和计算满足条件的元素数量，计算组合数并累加结果。

#### ncwzdlsd 的核心代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int mod=1e9+7,maxn=2e5+5;
int fac[maxn],inv[maxn],a[maxn];

int quickpow(int a,int b)
{
    int res=1;
    while(b)
    {
        if(b&1) res=res*a%mod;
        a=a*a%mod,b>>=1;
    }
    return res;
}

void init()
{
    fac[0]=1;
    for(int i=1;i<=2e5;i++) fac[i]=fac[i-1]*i%mod;
    inv[200000]=quickpow(fac[200000],mod-2);
    for(int i=199999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}

int C(int n,int m){return fac[n]*inv[m]%mod*inv[n-m]%mod;}

void solve()
{
    int n,m,k;cin>>n>>m>>k;
    int ans=0;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    int j=1;
    for(int i=1;i<=n;i++)
    {
        while(a[j+1]-a[i]<=k&&j+1<=n) j++;
        if((j-i+1)>=m) ans+=C(j-i,m-1),ans%=mod;
    }
    cout<<ans<<"\n";
}

signed main()
{
    int t;cin>>t;
    init();
    while(t--) solve();
    return 0;
}
```
**核心实现思想**：预处理阶乘和逆元，排序后使用双指针 `i` 和 `j` 找到满足条件的元素范围，计算组合数并累加结果。

### 最优关键思路或技巧
- 利用排序将无序序列转化为有序序列，方便枚举最小值并确定满足条件的元素范围。
- 使用组合数计算满足条件的元组数量，通过快速幂计算逆元避免阶乘运算的溢出。
- 采用双指针或二分查找提高查找满足条件元素范围的效率。

### 可拓展之处
同类型题或类似算法套路：
- 其他组合数学问题，如计算满足特定条件的排列组合数量。
- 涉及区间统计和计算的问题，可使用双指针、二分查找等方法优化。

### 推荐洛谷题目
- [P1833 樱花](https://www.luogu.com.cn/problem/P1833)
- [P2822 组合数问题](https://www.luogu.com.cn/problem/P2822)
- [P3197 [HNOI2008]越狱](https://www.luogu.com.cn/problem/P3197)

### 个人心得总结
- **light_ght**：在处理数据重复问题时遇到困难，通过他人点拨找到避免重复计算的方法，强调了开 `long long` 的重要性，避免数据溢出。
- **shenmadongdong**：调侃题目简单，实际思路清晰，实现简洁，体现了对题目的准确理解和熟练的代码实现能力。
- **ncwzdlsd**：指出答案与序列顺序无关，这是解题的关键思路，提醒我们在解题时要善于发现问题的本质特征。

---
处理用时：68.73秒