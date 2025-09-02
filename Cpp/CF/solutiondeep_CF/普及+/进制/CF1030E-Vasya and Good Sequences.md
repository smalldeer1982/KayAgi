# 题目信息

# Vasya and Good Sequences

## 题目描述

Vasya has a sequence $ a $ consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ . Vasya may pefrom the following operation: choose some number from the sequence and swap any pair of bits in its binary representation. For example, Vasya can transform number $ 6 $ $ (\dots 00000000110_2) $ into $ 3 $ $ (\dots 00000000011_2) $ , $ 12 $ $ (\dots 000000001100_2) $ , $ 1026 $ $ (\dots 10000000010_2) $ and many others. Vasya can use this operation any (possibly zero) number of times on any number from the sequence.

Vasya names a sequence as good one, if, using operation mentioned above, he can obtain the sequence with [bitwise exclusive or](https://en.wikipedia.org/wiki/Exclusive_or) of all elements equal to $ 0 $ .

For the given sequence $ a_1, a_2, \ldots, a_n $ Vasya'd like to calculate number of integer pairs $ (l, r) $ such that $ 1 \le l \le r \le n $ and sequence $ a_l, a_{l + 1}, \dots, a_r $ is good.

## 说明/提示

In the first example pairs $ (2, 3) $ and $ (1, 3) $ are valid. Pair $ (2, 3) $ is valid since $ a_2 = 7 \rightarrow 11 $ , $ a_3 = 14 \rightarrow 11 $ and $ 11 \oplus 11 = 0 $ , where $ \oplus $ — bitwise exclusive or. Pair $ (1, 3) $ is valid since $ a_1 = 6 \rightarrow 3 $ , $ a_2 = 7 \rightarrow 13 $ , $ a_3 = 14 \rightarrow 14 $ and $ 3 \oplus 13 \oplus 14 = 0 $ .

In the second example pairs $ (1, 2) $ , $ (2, 3) $ , $ (3, 4) $ and $ (1, 4) $ are valid.

## 样例 #1

### 输入

```
3
6 7 14
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
1 2 1 16
```

### 输出

```
4
```

# AI分析结果

### 题目中文重写
# 瓦西亚和良好序列

## 题目描述
瓦西亚有一个由 $n$ 个整数 $a_1, a_2, \dots, a_n$ 组成的序列 $a$。瓦西亚可以进行以下操作：从序列中选择一个数，并交换其二进制表示中的任意一对位。例如，瓦西亚可以将数字 $6$（二进制表示为 $\dots 00000000110_2$）转换为 $3$（二进制表示为 $\dots 00000000011_2$）、$12$（二进制表示为 $\dots 000000001100_2$）、$1026$（二进制表示为 $\dots 10000000010_2$）等等。瓦西亚可以对序列中的任何数字使用此操作任意次数（可能为零次）。

瓦西亚将一个序列称为良好序列，如果使用上述操作，他可以得到一个所有元素的按位异或和等于 $0$ 的序列。

对于给定的序列 $a_1, a_2, \ldots, a_n$，瓦西亚想要计算整数对 $(l, r)$ 的数量，使得 $1 \le l \le r \le n$ 且序列 $a_l, a_{l + 1}, \dots, a_r$ 是良好序列。

## 说明/提示
在第一个样例中，数对 $(2, 3)$ 和 $(1, 3)$ 是有效的。数对 $(2, 3)$ 有效是因为 $a_2 = 7 \rightarrow 11$，$a_3 = 14 \rightarrow 11$，且 $11 \oplus 11 = 0$，其中 $\oplus$ 表示按位异或。数对 $(1, 3)$ 有效是因为 $a_1 = 6 \rightarrow 3$，$a_2 = 7 \rightarrow 13$，$a_3 = 14 \rightarrow 14$，且 $3 \oplus 13 \oplus 14 = 0$。

在第二个样例中，数对 $(1, 2)$、$(2, 3)$、$(3, 4)$ 和 $(1, 4)$ 是有效的。

## 样例 #1
### 输入
```
3
6 7 14
```
### 输出
```
2
```

## 样例 #2
### 输入
```
4
1 2 1 16
```
### 输出
```
4
```

### 综合分析与结论
这些题解的核心思路都是先明确一个区间成为良好序列的条件：区间内所有数二进制中 $1$ 的个数之和为偶数，且区间内二进制中 $1$ 个数最多的数不超过总数的一半。在此基础上，各题解采用不同方法进行求解。
- **思路对比**：部分题解采用前缀和结合暴力枚举短区间的方法，部分使用分治、笛卡尔树等数据结构和算法优化。
- **算法要点**：多数题解利用前缀和快速计算区间内 $1$ 的个数之和，对于最大值的处理，有的直接枚举短区间，有的使用数据结构优化。
- **解决难点**：主要难点在于处理最大值超过一半的情况，不同题解通过不同方式解决，如限制区间长度、分治、笛卡尔树等。

### 所选题解
- **作者：开始新的记忆 (赞：16) - 4星**
  - **关键亮点**：思路清晰，代码简洁，利用前缀和维护区间内 $1$ 的个数，通过枚举短区间处理最大值问题。
  - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,anss[300010],num[300010],cnt[2]={1};
long long ans=0;

int main() 
{
    cin>>n;
    for(int i=1;i<=n;++i)
    {
        long long x;
        cin>>x;
        while(x>0)
        {
            num[i]+=(x%2);
            x/=2;
        }
        anss[i]=anss[i-1]+num[i];
        ans+=cnt[anss[i]%2];
        for(int j=i,k=i+1,maxn=0;j>=1 && j>=i-64;--j)
        {
            while(k>j) 
                maxn=max(maxn,num[--k]);
            if(maxn*2>anss[i]-anss[j-1] && anss[i]%2==anss[j-1]%2) 
                --ans;
        }
        ++cnt[anss[i]%2];
    }
    cout<<ans<<endl;
    return 0;
}
```
  - **核心实现思想**：先计算每个数二进制中 $1$ 的个数，再计算前缀和。利用前缀和判断区间内 $1$ 的个数之和是否为偶数，通过枚举短区间找出最大值，判断是否满足条件。

- **作者：蒟酱 (赞：6) - 4星**
  - **关键亮点**：代码简短，利用 `__builtin_popcountll` 函数快速计算二进制中 $1$ 的个数，同样采用前缀和结合枚举短区间的方法。
  - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cassert>
#define siz(x) int((x).size())
#define cauto const auto
#define all(x) (x).begin(),(x).end()
using std::cin;using std::cout;
using loli=long long;
using venti=__int128_t;
using pii=std::pair<int,int>;
constexpr int kN=3e5+1;
int n,a[kN],cnt[]={1,0},sum;
loli ans;
signed main(){
    std::ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++){loli x;cin>>x;a[i]=__builtin_popcountll(x);}
    for(int l=1;l<=n;l++){
        ans+=cnt[(sum+=a[l])&1]++;
        for(int r=l,max=0,num=0;r<=std::min(n,l+58);r++)
            max=std::max(max,a[r]),
            ans-=(num+=a[r])%2==0&&2*max>num;
    }
    cout<<ans;
    return 0;
}
```
  - **核心实现思想**：使用 `__builtin_popcountll` 计算每个数二进制中 $1$ 的个数，通过前缀和判断区间内 $1$ 的个数之和是否为偶数，枚举短区间判断最大值是否满足条件。

- **作者：Graphcity (赞：0) - 4星**
  - **关键亮点**：通过贪心证明一个序列能够匹配完的条件，根据序列长度采用不同的计算方法，时间复杂度为 $O(n)$。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=3e5;

inline ll read()
{
    char ch=getchar();
    ll f=1,x=0;
    while(ch>'9' || ch<'0')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,pop[Maxn+5],all[Maxn+5][2];
ll val[Maxn+5],ans;

int main()
{
    n=read();
    For(i,1,n)
    {
        val[i]=read();
        For(j,0,61) if(val[i]&(1ll<<j)) pop[i]++;
    }
    int res=0;
    For(i,1,n) res+=pop[i],all[i][res&1]++;
    For(i,1,n) For(j,0,1) all[i][j]+=all[i-1][j]; 
    For(i,1,n)
    {
        int sum=0,mx=0;
        For(j,1,128)
        {
            if(i+j-1>n) break;
            sum+=pop[i+j-1],mx=max(mx,pop[i+j-1]);
            if(sum%2==0 && mx*2<=sum) ans++;
        }
    }
    res=0;
    For(i,1,n-128)
    {
        ans+=(all[n][res]-all[i+127][res]);
        res=(res+pop[i])&1;
    }
    printf("%lld\n",ans);
    return 0;
}
```
  - **核心实现思想**：先计算每个数二进制中 $1$ 的个数，再计算前缀和。对于长度小于等于 $128$ 的区间，直接暴力计算；对于长度大于 $128$ 的区间，利用前缀和计算。

### 最优关键思路或技巧
- **前缀和优化**：利用前缀和可以快速计算区间内 $1$ 的个数之和，将时间复杂度从 $O(n^2)$ 优化到 $O(n)$。
- **枚举短区间**：由于每个数二进制中 $1$ 的个数最多为 $64$，当区间长度超过一定值时，无需考虑最大值的影响，因此可以只枚举短区间处理最大值问题。

### 可拓展之处
同类型题或类似算法套路：
- 涉及区间异或和、区间和的问题，可以考虑使用前缀和优化。
- 对于区间最大值的处理，可以使用分治、笛卡尔树等数据结构和算法优化。

### 推荐洛谷题目
- P1115 最大子段和
- P1719 最大加权矩形
- P2671 [NOIP2015 普及组] 求和

### 个人心得摘录与总结
- **作者：Itst**：提到自己整天想着奇奇怪怪的算法把简单的题目搞得很难，强行安慰自己分治做法的优越性在于可以做 $a_i = 0$ 的情况。总结：在解题时不要过度追求复杂算法，应先考虑简单有效的方法，但也要了解复杂算法的适用场景。

---
处理用时：63.87秒