# Expected Power

## 题目描述

给定一个长度为 $n$ 的整数数组 $a_1,a_2,\ldots,a_n$，以及一个数组 $p_1, p_2, \ldots, p_n$。

定义随机多重集 $S$（即 $S$ 可以包含相同元素），其构造方式如下：

- 初始时，$S$ 为空集。
- 对于每个 $i$ 从 $1$ 到 $n$，以概率 $\frac{p_i}{10^4}$ 将 $a_i$ 插入 $S$。注意，每个元素是否被插入是独立的。

记 $f(S)$ 为 $S$ 中所有元素的按位异或（[bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)）结果。请计算 $\mathbb{E}[(f(S))^2]$ 的期望值，并将答案对 $10^9 + 7$ 取模输出。

形式化地，设 $M = 10^9 + 7$。可以证明答案可以表示为最简分数 $\frac{p}{q}$，其中 $p$ 和 $q$ 是整数且 $q \not\equiv 0 \pmod{M}$。请输出满足 $0 \le x < M$ 且 $x \cdot q \equiv p \pmod{M}$ 的整数 $x$。

## 说明/提示

在第一个测试用例中，$a = [1, 2]$，每个元素被插入 $S$ 的概率为 $\frac{1}{2}$，因为 $p_1 = p_2 = 5000$，$\frac{p_i}{10^4} = \frac{1}{2}$。因此，$S$ 有 $4$ 种可能：

- $S = \varnothing$，此时 $f(S) = 0$，$(f(S))^2 = 0$。
- $S = \{1\}$，此时 $f(S) = 1$，$(f(S))^2 = 1$。
- $S = \{2\}$，此时 $f(S) = 2$，$(f(S))^2 = 4$。
- $S = \{1,2\}$，此时 $f(S) = 1 \oplus 2 = 3$，$(f(S))^2 = 9$。

因此，答案为 $0 \cdot \frac{1}{4} + 1 \cdot \frac{1}{4} + 4\cdot \frac{1}{4} + 9 \cdot \frac{1}{4} = \frac{14}{4} = \frac{7}{2} \equiv 500\,000\,007 \pmod{10^9 + 7}$。

在第二个测试用例中，$a = [1, 1]$，$a_1$ 以概率 $0.1$ 被插入 $S$，$a_2$ 以概率 $0.2$ 被插入 $S$。$S$ 有 $3$ 种可能：

- $S = \varnothing$，此时 $f(S) = 0$，$(f(S))^2 = 0$，概率为 $(1-0.1) \cdot (1-0.2) = 0.72$。
- $S = \{1\}$，此时 $f(S) = 1$，$(f(S))^2 = 1$，概率为 $(1-0.1) \cdot 0.2 + 0.1 \cdot (1-0.2) = 0.26$。
- $S = \{1, 1\}$，此时 $f(S) = 0$，$(f(S))^2 = 0$，概率为 $0.1 \cdot 0.2 = 0.02$。

因此，答案为 $0 \cdot 0.72 + 1 \cdot 0.26 + 0 \cdot 0.02 = 0.26 = \frac{26}{100} \equiv 820\,000\,006 \pmod{10^9 + 7}$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
2
1 2
5000 5000
2
1 1
1000 2000
6
343 624 675 451 902 820
6536 5326 7648 2165 9430 5428
1
1
10000```

### 输出

```
500000007
820000006
280120536
1```

# 题解

## 作者：Zeoykkk (赞：11)

## CF926 E. Expected Power

>给定 $n$ 个元素 $a[i]$，有一个多重集 $S$，起初为空，然后按照 $1 \sim n$ 的顺序试图将 $a[i]$ 插入到 $S$ 中，$a[i]$ 成功插入进 $S$ 的概率为 $\frac{p[i]}{10^4}$，定义 $f(S)$ 为 $S$ 中所有元素的异或和，求 $f(S)^2$ 的期望值。
>
>$n \leq 2\times 10^5, a[i] \leq 1023$

### Sol 1

由于 $a[i]$ 值域很小，考虑这样的一个 DP，定义 $dp[i][j]$ 代表试图将 $a[1, i]$ 中的元素插入 $S$ 中，$f(S) = j$ 的概率。令 $p[i] = \frac{p[i]}{10^4}, q[i] = 1 - p[i]$。

转移也是显然的，$dp[i][j] = p[i] \times dp[i - 1][j \oplus a[i]] + q[i] \times dp[i - 1][j]$。

显然 $E[f(S)^2] = \sum_{x = 0}^{1023} dp[n][x] x^2$。

时间复杂度：$O(Vn)$。

### Sol 2

根据异或的性质，考虑每一位的贡献，即 $E[f(S)] = \sum_{i = 0}^{9}P(i)\times 2^i$，其中 $P(i)$ 代表试图将 $n$ 个元素插入 $S$ 中，$f(S)$ 在二进制下第 $i$ 位为 $1$ 的概率。

显然 DP 可以求 $P(i)$，定义 $dp[i][j][0/1]$ 代表试图将前 $i$ 个元素插入 $S$ 中，$f(S)$ 在二进制下第 $j$ 位为 $0 / 1$ 的概率。

转移也是显然的，令 $x$ 代表 $a[i]$ 在二进制第 $j$ 位上的值，则有 $dp[i][j][k] = p[i] \times dp[i - 1][j][k \oplus x] + q[i] \times dp[i - 1][j][k]$。

那么现在要求 $f(S)^2$，令 $f(S) = \sum_{i = 0}^{9} b[i] 2^i$，则有 $f(S)^2 = \sum_i \sum_j b[i]b[j]2^{i + j}$，所以 $E[f(S)^2] = \sum_{i = 0}^{9} \sum_{j = 0}^9 P(i, j)\times 2^{i + j}$，其中 $P(i, j)$ 代表试图将 $n$ 个元素插入 $S$ 中，$f(S)$ 在二进制下第 $i$ 位和第 $j$ 位上都为 $1$ 的概率。

所以不妨定义 $dp[i][j][k][0/1][0/1]$ 试图将前 $i$ 个元素插入 $S$ 中，$f(S)$ 在二进制下第 $j$ 位为 $0 / 1$ 并且第 $k$ 位为 $0 / 1$ 的概率。

转移也是类似的，不再赘述，可以将第一维通过滚动数组优化掉。

时间复杂度：$O(n \log^2n)$。

---

## 作者：__3E24AC7002AD9292__ (赞：7)

VP 赛切了五题，但是这题敢放 E？

异或期望值，似乎根本不能搞，但是 $a_i<2^{10}$，那么异或的结果也 $<2^{10}$，考虑状压 dp。

记录 $f_{i,j}$ 表示当前已经遍历完前 $i$ 个数的选择情况，且选择后的异或和为 $j$ 的概率，显然有以下转移：

- $f_{i,j}=(f_{i,j}+\frac{10^4-p_i}{10^4}f_{i-1,j})\bmod 10^9+7$。
- $f_{i,j}=(f_{i,j}+\frac{p_i}{10^4}f_{i-1,j\oplus a_i})\bmod 10^9+7$。

可以使用滚动数组优化空间，时间复杂度 $\Theta(Vn)$。

```cpp
f[0][0]=1;
for (int i=1;i<=n;i++){
	for (int j=0;j<=1023;j++){
		f[1][j]+=f[0][j]*(10000-p[i])%M*INV%M;
		f[1][j]=(f[1][j]>=M?f[1][j]-M:f[1][j]);
		f[1][j]+=f[0][j^a[i]]*p[i]%M*INV%M;
		f[1][j]=(f[1][j]>=M?f[1][j]-M:f[1][j]);
	}
	for (int j=0;j<=1023;j++)
		f[0][j]=f[1][j],f[1][j]=0;
}
for (int i=0;i<=1023;i++){
	ans+=f[0][i]*i%M*i%M;
	ans%=M;
}
```

---

## 作者：xyvsvg (赞：0)

这里提供一种与众不同的做法，复杂度为 $O(n+V^2)$。

~虽然当测试数据较多时不如暴力~，不过在单测试数据下复杂度是最优的。

注意到 $a_i\leq1023$，因此当 $n$ 较大时，一定有许多 $a_i$ 是重复的，于是我们可以把相同的 $a_i$ 合并。具体地，若 $a_i=a_j$，则可以将他们的概率合并为 $p_k=(1-p_i)\cdot p_j+(1-p_j)\cdot p_i$，正确性显然。这样的话，最终只有至多 $V$ 个状态，然后我们仿照 $O(Vn)$ 的做法转移即可。

~不过直接这样做的话会在第二个点超时~，因此我们可以将 $a_i$ 离散化再做，具体实现如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define endl '\n'
void solve()
{
    const int mod=1e9+7;
    auto inv=[&](int a)
    {
        int ret=1,b=mod-2;
        for(;b;b>>=1,a=1LL*a*a%mod)
            if(b&1)
                ret=1LL*ret*a%mod;
        return ret;
    };
    int k=inv(10000),n;
    cin>>n;
    vector<int>a(n+10),p(1024);
    vector<int>disc;
    for(int i=1;i<=n;++i)
        cin>>a[i],disc.push_back(a[i]);
    for(int i=1;i<=n;++i)
    {
        int x;
        cin>>x;
        double d=x/10000.0;
        x=1LL*x*k%mod;
        int&prob=p[a[i]];
        prob=((1LL-prob)*x+(1LL-x)*prob)%mod;
    }
    sort(disc.begin(),disc.end());
    disc.erase(unique(disc.begin(),disc.end()),disc.end());
    vector<int>dp(1024);
    dp[0]=1;
//    cout<<p2[1]<<' '<<p2[2]<<endl;
    for(int i:disc)
    {
        vector<int>nxt(1024);
        vector<double>nxt2(1024);
        for(int j=0;j<1024;++j)
            nxt[j]=((1LL-p[i])*dp[j]+1LL*p[i]*dp[j^i])%mod;
        swap(dp,nxt);
    }
    int ans=0;
    for(int i=0;i<1024;++i)
        ans=(1LL*i*i*dp[i]+ans)%mod;
    cout<<(ans+mod)%mod<<endl;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--)
        solve();
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

> What's the point of allowing $O(n \cdot 1024)$ solutions in E?

注意到可以算出每个 f 值的概率最后再求期望。

因此可以定义 $f_{i,j}$ 表示前 $i$ 个数中，选出来的数异或和为 $j$ 的概率。

转移是平凡的，此处不再赘述。

第一维打滚就行了。

---

