# [ARC143B] Counting Grids

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc143/tasks/arc143_b

$ N\ \times\ N $ のマス目の各マスに $ 1 $ から $ N^2 $ までの整数を $ 1 $ つずつ書き込む方法であって， どのマスも以下の条件のうち少なくとも一方を満たすようなものの個数を $ 998244353 $ で割ったあまりを求めてください．

- そのマスに書かれている数より大きい数が書かれているマスが同じ列に存在する．
- そのマスに書かれている数より小さい数が書かれているマスが同じ行に存在する．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 500 $

### Sample Explanation 1

例えば，以下のような書き込み方は条件を満たします． ``` 13 42 ``` この場合，左上のマスは左下のマスに書かれている数より小さい数が書かれているので， $ 1 $ つ目の条件を満たします．ただし，$ 2 $ つ目の条件は満たしません．

## 样例 #1

### 输入

```
2```

### 输出

```
8```

## 样例 #2

### 输入

```
5```

### 输出

```
704332752```

## 样例 #3

### 输入

```
100```

### 输出

```
927703658```

# 题解

## 作者：luogu_gza (赞：4)

做法来自 @minstdfx。

注意到至多有一个不合法的数，证明在其他题解中已经有人说明了。

我们计数不合法方案数，注意到想要构造出一行一列的交点为不合法格子，不合法数字一定是 $2n-1$ 个数的中位数。

不合法状态不难表述为 $n^2\binom{n^2}{2n-1}(n^2-2n+1)!((n-1)!)^2$。

注意到这其实是若干个阶乘相乘相除的结果，我们运用 P5282 的方法即可将本题做到 $O(n \log n)$ 的复杂度。

---

## 作者：lg1058428 (赞：2)

# 解题思路
对于每个不满足条件的网格，有且仅有一个点不满足条件。
证明如下：
反证法，假如有 $>1$ 个点不满足条件，令其中两个点的坐标分别为 $i1,j1$ 和 $i2,j2$，根据题意，显然有 $a_{i1,j1}>a_{i2,j1}>a_{i2,j2}$，也就是 $a_{i1,j1}>a_{i2,j2}$，也显然有 $a_{i1,j1}<a_{i1,j2}<a_{i2,j2}$，也就是 $a_{i1,j1}<a_{i2,j2}$，矛盾。

所以我们仅需枚举每个点，计算当该点不满足条件时的方案数，再用所有排列数减去它即可。

---
假设第 $i$ 个点不满足条件，注意到大于 $i$ 的数共有 $n^2-i$ 个，所以共有 $n^2-i$ 个数可以填入行内，小于 $i$ 的数共有 $i-1$ 个，所以共有 $i-1$ 个数可以填入列内。
每行每列都有 $n-1$ 个空位可填，所以对于 $i$ 不满足条件的情况，该行该列共有 $A_{n^2-i}^{n-1}A_{i-1}^{n-1}$ 种组合。

---
求出了对于每个 $i$ 的组合方案数，只需将其加在一起即可。除去每行每列，剩余有 $(i-1)^2!$ 个空位，直接乘上即可。$i$ 有 $n^2$ 中选择方案，将其乘上答案可得最终结果。
另外当 $i<n$ 或 $i\ge n^2-n+1$ 时式子不合法，所以仅需枚举 $n$ 至 $n^2-n+1$ 即可。
最终的式子为 $(n-1)^2!\times n^2\times \sum\limits_{i=n}^{n^2-n+1}A_{n^2-i}^{n-1}A_{i-1}^{n-1}$。
# 代码实现
注意线性预处理逆元。
若不预处理，则时间复杂度为 $O(n^4)$，无法通过本题。
核心代码如下：
```cpp
for(int i=n;i<=n*n-n+1;i++) ans=(ans+A(n*n-i,n-1)%mod*A(i-1,n-1)%mod)%mod;
ans=(fac[n*n]-n*n*fac[(n-1)*(n-1)]%mod*ans%mod+mod)%mod;
```
如有问题欢迎指出。

---

## 作者：TKXZ133 (赞：2)

[Counting Grids](https://www.luogu.com.cn/problem/AT_arc143_b)

### 题目大意

将 $1\sim n^2$ 填入 $n\times n$ 的网格 $A$ 中，对于每个格子满足以下条件之一：

- 该列中存在大于它的数。

- 该行中存在小于它的数。

求方案数。

### 思路分析

首先有一个比较显然的结论：**对于一个不合法的方案，有且仅有一个数不满足任何一个条件。**

考虑反证法，假设有两个数都不满足任何一个条件，设这两个数分别位于 $(x_1,y_1),(x_2,y_2)$，则有：$A_{x_1,y_1}>A_{x_1,y_2}>A_{x_2,y_2}$，$A_{x_2,y_2}>A_{x_2,y_1}>A_{x_1,y_1}$，存在矛盾，而多个数的情况可以归纳为两个数的情况，故结论成立。

正难则反，考虑计算不合法的方案数：

设不满足任何条件的数为 $i$，考虑到 $i$ 是所在列中最大的数，且是所在行中最小的数，故所在行的填法为 $A_{n^2-i}^{n-1}$，所在列的填法为 $A_{i-1}^{n-1}$，其他的地方随便填，一定满足条件，填法为 $(n-1)^2!$，再考虑 $i$ 的位置，故得出不合法的方案数的计算式为：

$$n^2\times (n-1)^2!\times\sum_{i=n}^{n^2-n+1}A_{n^2-i}^{n-1}A_{i-1}^{n-1}$$

那么合法的方案数只需要用 $n^2!$ 减一下就可以了。

如果预处理阶乘和阶乘逆元，那么计算的时间复杂度为 $O(n^2)$。

### 代码

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;
const int N=250100,V=250000,mod=998244353;
#define int long long

int fac[N],inv[N];
int n,ans;

int q_pow(int a,int b){
    int res=1;
    while(b){
        if(b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}

int A(int n,int m){
    if(n<m) return 0;
    return fac[n]*inv[n-m]%mod;
}

signed main(){
    scanf("%lld",&n);
    int n2=n*n;
    fac[0]=1;
    for(int i=1;i<=n2;i++) fac[i]=fac[i-1]*i%mod;
    inv[n2]=q_pow(fac[n2],mod-2);
    for(int i=n2;i>=1;i--) inv[i-1]=inv[i]*i%mod;
    for(int i=n;i<=n2-n+1;i++) 
        ans=(ans+A(n2-i,n-1)*A(i-1,n-1)%mod)%mod;
    ans=(ans*fac[(n-1)*(n-1)]%mod)*n2%mod;
    ans=(fac[n*n]-ans+mod)%mod;
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：copper_ingot (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc143_b)

设网格中第 $i$ 行第 $j$ 列的数为 $a_{i,j}$。

首先网格中至多存在一个不满足条件的数，证明如下：

如果有两个不满足条件的数，设两个数分别为 $a_{i_1,j_1}$ 和 $a_{i_2,j_2}$，则根据要求有 $a_{i_1,j_1} < a{i_1,j_2} < a{i_2,j_2}$ 和 $a_{i_1,j_1} > a{i_2,j_1} > a{i_2,j_2}$，矛盾。

所以我们钦定一个数不满足条件，那么其他的数无论怎么填都满足。

设不满足条件的数为 $i$，有 $n^2-i$ 个数比 $i$ 大，$i-1$ 个数比 $i$ 小。在 $i$ 所处行上有 $n-1$ 个数比 $i$ 大，填行的方案数为 $A_{n^2-i}^{n-1}$；同理填列的方案数为 $A_{i-1}^{n-1}$。剩下的数随便填，有 $(n-1)^2!$ 个方案。$i$ 又有 $n^2$ 个不同位置，所以存在不满足条件的数的方案数为

$$n^2\times (n-1)^2!\times\sum_{i=n}^{n^2-n+1}A_{n^2-i}^{n-1}A_{i-1}^{n-1}$$

最后拿 $n^2!$ 减去这个东西就是最终的答案。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
int n, fac[300001] = {1}, inv[300001], invf[300001] = {1}, ans;
int A(int n, int m){return fac[n] * invf[n - m] % mod;}
signed main(){
	scanf("%lld", &n);
	for (int i = 1; i <= n * n; i++){
		fac[i] = fac[i - 1] * i % mod;
		inv[i] = (i == 1 ? i : (mod - mod / i) * inv[mod % i] % mod);//求逆元
		invf[i] = invf[i - 1] * inv[i] % mod;
	}
	for (int i = n; i <= n * n - n + 1; i++)
		ans = (ans + A(n * n - i, n - 1) * A(i - 1, n - 1) % mod) % mod;
	ans = (ans * fac[(n - 1) * (n - 1)] % mod * n * n % mod);
	printf("%lld\n", (fac[n * n] - ans + mod) % mod);
    return 0;
}
```

---

## 作者：Phartial (赞：1)

对于一种方案，我们把不符合条件的格子称为“坏格子”。

设其中一个坏格子的坐标为 $(i_1,j_1)$，另一个坏格子的坐标为 $(i_2,j_2)$。方案中第 $i$ 行第 $j$ 列的数为 $a_{i,j}$。

有 $a_{i_1,j_1}<a_{i_1,j_2}<a_{i_2,j_2}$，但同时也有 $a_{i_1,j_1}>a_{i_2,j_1}>a_{i_2,j_2}$，矛盾。所以一种方案最多只有一个坏格子。

考虑枚举这个坏格子填哪个数，不妨设这个格子填的是 $v$。那么同一行的其他格子必须比 $v$ 大，方案数为 $A_{n^2-i}^{n-1}$。同一列的其他格子必须比 $v$ 小，方案数为 $A_{i-1}^{n-1}$。而剩下的格子能随便填，方案数为 $(n-1)^2!$。最后还要乘上坏格子的位置的方案数 $n^2$。我们就得到了**不合法**的方案数，用所有方案减去不合法的方案就是答案了。

```cpp
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 501;
const LL kM = 998244353;

int n, l;
LL f[kN * kN], iv[kN * kN], ans;

LL P(LL b, int e) {
  LL s = 1;
  for (; e; e >>= 1, b = b * b % kM) {
    (e & 1) && (s = s * b % kM);
  }
  return s;
}
LL A(int n, int m) { return f[n] * iv[n - m] % kM; }

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  l = n * n;
  for (int i = f[0] = 1; i <= l; ++i) {
    f[i] = f[i - 1] * i % kM;
  }
  iv[l] = P(f[l], kM - 2);
  for (int i = l; i >= 1; --i) {
    iv[i - 1] = iv[i] * i % kM;
  }
  for (int i = n; i <= l - n + 1; ++i) {
    ans = (ans + A(i - 1, n - 1) * A(l - i, n - 1) % kM) % kM;
  }
  ans = ans * f[(n - 1) * (n - 1)] % kM * l % kM;
  cout << (f[l] - ans + kM) % kM;
  return 0;
}
```

---

## 作者：CCX_CoolMint (赞：1)

非常好计数题。
### 题目大意

使用 $1\sim N^2$ 的每一个整数填充一个 $N\times N$ 的表格，每个格子至少满足以下条件之一：
 - 在同一列中，有一个方块里面的数字比该方块的数字大。
 - 在同一行中，有一个方块里面的数字比该方块的数字小。

求填充表格的方案数。

###  思路
对于一个合法的方案可能有很多种，重要的是我们不知道从何处下手解决，所里这里采用正难则反的方法，考虑不合法的方案有多少种，再用总的方案数减去不合法方案数即可。

该题有一个特殊的结论，需要简单思考一下，也很显然：一个不合法方案中有且仅有一个数对于上述条件都不满足。
假设有两个格子不满足条件，设其坐标为 $(x_1,y_1)$ 和 $(x_2,y_2)$。那么它们需要满足：

 - $A_{{x_1},{y_1}}>A_{{x_2},{y_1}}$，$A_{{x_1},{y_1}}<A_{{x_1},{y_2}}$
 - $A_{{x_2},{y_2}}>A_{{x_1},{y_2}}$，$A_{{x_2},{y_2}}<A_{{x_2},{y_1}}$
 - 联立后得到 $A_{{x_2},{y_1}}>A_{{x_1},{y_2}}$ 且 $A_{{x_2},{y_1}}<A_{{x_1},{y_2}}$，自相矛盾，反证法可以证明结论成立。

接下来考虑不合法的方案数：
若这个不合法的格子内填的数是 $i$，它是该行中最小的数，可选方案数为 $A_{n^2-i}^{n-1}$；它也是该列中最大的数，可选方案数为 $A_{i-1}^{n-1}$。
有多少数是可以填进这个不合法的格子的呢？考虑到该行该列都还需要填 $n-1$ 个数，所以 $i$ 的范围是 $n \sim n^2-n+1$。对于其他的格子，由结论可知，无论怎么填都是合法的，由于已经填了 $2n-1$ 个数，所以此时方案数为 $(n^2-2n+1)!$ 即 $(n-1)^2!$。
再考虑到这个不合法格子有 $n^2$ 个位置可选，可以得到以下不合法方案的计算式子：

$$ 
\displaystyle\sum_{i=n}^{n^2-n+1} A_{n^2-i}^{n-1}A_{i-1}^{n-1} \times (n-1)^2! \times n^2
$$

对于总的方案数，显然有 $n^2!$ 种方案，拿总方案数减去不合法方案数即可，式子：

$$
n^2!- \sum_{i=n}^{n^2-n+1} A_{n^2-i}^{n-1}A_{i-1}^{n-1}\times(n-1)^2!\times n^2
$$

注意到 $A_n^m= \dfrac{n!}{(n-m)!}$，用费马小定理解决逆元即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 998244353
ll n,fac[1001000],ans;
ll ksm(ll a,ll b)
{
    ll res=1;
    while(b)
    {
        if(b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
ll A(ll x,ll y)
{
    return fac[x]*ksm(fac[x-y],mod-2)%mod;
}
int main()
{
    cin>>n;
    fac[0]=1;
    for(int i=1;i<=n*n;i++) fac[i]=fac[i-1]*i,fac[i]%=mod;
    for(int i=n;i<=n*n-n+1;i++)
    {
        ans+=A(n*n-i,n-1)*A(i-1,n-1)%mod;
        ans%=mod;
    }
    ans=ans*fac[(n-1)*(n-1)]%mod*n%mod*n%mod;
    ans=(fac[n*n]-ans+mod)%mod;
    cout<<ans;
    return 0;
}
```

---

## 作者：OrinLoong (赞：0)

## ATR143B Counting Grids 学习笔记
[Luogu Link](https://www.luogu.com.cn/problem/AT_arc143_b)

### 题意简述
现在需要将 $1\sim n^2$ 共 $n^2$ 个整数填进网格 $S$。定义一种方案合法当且仅当不存在 $S_{i,j}$ 满足：
$$\max_{k=1}^n S_{i,k}=\min_{k=1}^n S_{k,j}=S_{i,j}$$
。问合法方案数，答案对 $998244353$ 取模。

$n\le 500$。

### 做法解析
看起来就正难则反，不合法方案大概率比合法方案少且好算。

我们设不满足合法要求的元素为特殊元素，自然而然地我们要考虑其可能存在的数量，这关系到题目难度和是否使用容斥等工具。万幸地，这种特殊元素最多一个~~不然为什么洛谷只评了绿~~——如果有两个的话会相互矛盾（原因见图）：

![pE3C39g.png](https://s21.ax1x.com/2025/02/26/pE3C39g.png)

开始计算不合法方案数。首先特殊元素可以放在任何地方，是为 $n^2$；如果特殊元素值为 $i$ 的话，那么它所在列有 $A_{i-1}^{n-1}$ 种填法，所在行有 $A_{n^2-i}^{n-1}$ 种填法，其它元素随便填，方案为 $(n-1)^2!$。总不合法方案数就是：
$$n^2(n-1)^2!\sum_{i=n}^{n^2-n+1}A_{i-1}^{n-1}A_{n^2-i}^{n-1}$$
。合法方案数就是 $n^2!$ 减去这玩意。

### 代码实现
最后一步别忘了取模！
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace obasic{
    typedef long long lolo;
    template <typename _T>
    void readi(_T &x){
        _T k=1;x=0;char ch=getchar();
        for(;!isdigit(ch);ch=getchar())if(ch=='-')k=-1;
        for(;isdigit(ch);ch=getchar())x=(x<<3)+(x<<1)+ch-'0';
        x*=k;return;
    }
    template <typename _T>
    void writi(_T x){
        if(x<0)putchar('-'),x=-x;
        if(x>9)writi(x/10);
        putchar(x%10+'0');
    }
};
using namespace obasic;
const int MaxNs=2.5e5,Mod=998244353;
lolo facr[MaxNs],finv[MaxNs];
namespace omathe{
    lolo fastpow(lolo a,lolo b,lolo p){
        lolo res=1;
        for(;b;(a*=a)%=p,b>>=1)if(b&1)(res*=a)%=p;
        return res;
    }
    lolo getinv(lolo a,lolo p){
        return fastpow(a,p-2,p);
    }
    lolo Aran(lolo n,lolo m,lolo p){
        return facr[n]*finv[n-m]%Mod;
    }
};
using namespace omathe;
void prework(int n){
    facr[0]=finv[0]=1;
    for(int i=1;i<=n;i++)facr[i]=facr[i-1]*i%Mod;
    finv[n]=getinv(facr[n],Mod);
    for(int i=n-1;~i;i--)finv[i]=finv[i+1]*(i+1)%Mod;
}
int N;lolo ans;
int main(){
    readi(N);prework(N*N);
    for(int i=N;i<=N*N-N+1;i++)(ans+=Aran(i-1,N-1,Mod)*Aran(N*N-i,N-1,Mod)%Mod)%=Mod;
    (ans*=N*N*facr[(N-1)*(N-1)]%Mod)%=Mod;ans=(facr[N*N]+Mod-ans)%Mod;
    writi(ans);
    return 0;
}
```

### 反思总结
简单组合题，如果题目形如“不合法当且仅当有元素满足……”，而且这种元素数量大概不多，那就考虑它能有几个。
如果确认只有一个的话，难度可能就骤减了。

---

