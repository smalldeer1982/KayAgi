# Club of Young Aircraft Builders (easy version)

## 题目描述

这是该问题的简单版本。各版本间的区别在于此版本中所有 $a_i = 0$。只有当您解决了该问题的所有版本时才能进行 hack。

有一栋 $n$ 层的建筑物，楼层从下到上编号为 $1$ 至 $n$。每层恰好住着一位居民。

今天全体居民有一个重要目标：共同发射至少 $c$ 架纸飞机。居民们将依次发射飞机。当第 $i$ 层的居民发射一架飞机时，从第 $1$ 层到第 $i$ 层的所有居民都能看到它降落到地面的过程。

如果从第 $i$ 层居民的视角看，已有至少 $c$ 架飞机被发射，则该居民自己不会再发射更多飞机。已知到当天结束时，从每位居民的视角看至少发射了 $c$ 架飞机，且总共发射了 $m$ 架飞机。

您仔细记录了这次快闪活动，记录了每位发射飞机的居民所在楼层。遗憾的是，关于具体是谁发射了某些飞机的信息已经丢失。请找出填补空缺信息使其可信的方案数。由于答案可能很大，请输出其对 $10^9 + 7$ 取模的结果。

在此版本的问题中，所有信息均已丢失，整个数组全由空缺构成。

也可能您的记录存在错误，导致无法恢复任何有效信息。此时答案视为 $0$。

## 说明/提示

第一个测试样例中，所有六种可能的填补方案如下：
1. $[1, 1, 3, 3]$
2. $[1, 2, 3, 3]$
3. $[1, 3, 2, 3]$
4. $[2, 1, 3, 3]$
5. $[2, 2, 3, 3]$
6. $[3, 1, 2, 3]$

注意数组 $[2, 3, 1, 3]$ 不是有效方案，因为第三架飞机不可能由第 $1$ 层的居民发射——从他们的视角看，当时已有 $c = 2$ 架飞机被发射。

同样地，数组 $[1, 1, 2, 3]$ 也不是有效方案，因为从第 $3$ 层居民的视角看，仅发射了 $1$ 架飞机，而 $c = 2$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2
3 2 4
0 0 0 0
5 5 7
0 0 0 0 0 0 0```

### 输出

```
6
190```

# 题解

## 作者：_Kamisato_Ayaka_ (赞：4)

## Statement

有一栋 $n$ 层的楼，居民们要共同发射至少 $c$ 架纸飞机，楼层高的居民看不到楼层低的居民发射的纸飞机，每位居民会在自己看到的纸飞机数量至少 $c$ 后停止，实际上它们总共发射了 $m$ 个纸飞机，现在你有一个 $a$ 数组记录了每层楼居民发射的飞机数量，部分 $a_i$ 缺失了即 $a_i = 0$，你需要找出填补这些 $a_i$ 的总方案数，答案对 $10^9 + 7$ 取模。

**在当前问题版本中，所有 $a_i$ 均为 $0$**。

## Solution

记 $dp_{i,j}$ 表示第 $i$ 层楼发射飞机 $j$ 架，枚举发射的飞机数量，转移方程有：

$$
dp_{i,j} \leftarrow dp_{i,j} + \sum\limits_{k=0}^{\min(j,c)}dp_{i-1,j-k}
$$

当然你会发现方程缺了什么，注意到我们是从 $c$ 次发射中选择 $k$ 次，所以还需要一个系数 $\binom{c}{k}$，得到最终的柿子：

$$
dp_{i,j} \leftarrow dp_{i,j} + \sum\limits_{k=0}^{\min(j,c)}{dp_{i-1,j-k} \times \binom{c}{k}}
$$

最后答案即为 $dp_{n,m}$。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 1e9 + 7;
int T, n, C, m, A[10005], dp[105][10005], fac[1000005], invfac[1000005];

inline int qpow (int x, int k) {
    int ret = 1;
    while (k) {
        if (k & 1) ret = ret * x % MOD;
        x = x * x % MOD;
        k >>= 1;
    }
    return ret;
}

inline void prefac() {
    fac[0] = invfac[0] = 1;
    for (int i = 1; i <= 1000000; i ++)
        fac[i] = fac[i - 1] * i % MOD;
    invfac[1000000] = qpow (fac[1000000], MOD - 2);
    for (int i = 999999; i; i --)
        invfac[i] = invfac[i + 1] * (i + 1) % MOD;
}

inline int Com (int n, int m) {
    if (m < 0 || m > n) return 0;
    return fac[n] * invfac[m] % MOD * invfac[n - m] % MOD;  
}

inline void Dp() {
    cin >> n >> C >> m;
    for (int i = 1; i <= m; i ++)
        cin >> A[i];
    dp[1][C] = 1;
    for (int i = 2; i <= n; i ++) {
        for (int j = C; j <= m; j ++) {
            for (int k = 0; k <= min (j, C); k ++) {
                dp[i][j] = (dp[i][j] + Com (C, k) * dp[i - 1][j - k] % MOD) % MOD;
            }
        }
    }
    cout << dp[n][m] << '\n';
    for (int i = 1; i <= n; i ++) {
        for (int j = C; j <= m; j ++) {
            for (int k = 0; k <= min (j, C); k ++) dp[i][j] = 0;
        }
    }
}

signed main() {
    cin.tie (0) -> sync_with_stdio (0);
    cout.tie (0) -> sync_with_stdio (0);    
    cin >> T, prefac();
    while (T --) Dp();
    return 0;
}
```

---

## 作者：rubbishZZZ (赞：1)

## CF2066D1 Bitwise Slides



 #### 题意：

- 有一个 $n$ 层的建筑，楼层编号从 1 到 $n$，从底到顶。每层楼上有一个人。

  建筑中的所有居民今天有一个非常重要的目标：集体发射至少 $c$ 架纸飞机。居民们将轮流发射飞机。当第 $i$ 层的居民发射一架飞机时，所有从 $1$ 到 $i$ 层的居民都能看到它降落到地面。

  如果从第 $i$ 层居民的角度来看，已经发射了至少 $c$ 架飞机，那么他们就不会再发射飞机了。已知到一天结束时，从每个居民的角度来看，至少已经发射了 $c$ 架飞机，并且总共发射了 $m$ 架飞机。

  你仔细监控了这场集体行动并记录下了每架飞机是由哪个楼层的居民发射的。不幸的是，关于哪些居民发射了哪些飞机的信息丢失了。找出有多少种方式可以填补这些空缺，使得信息是可信的。由于答案可能非常大，请对 $10^9 + 7$ 取模。

  在这个版本的问题中，所有信息都丢失了，整个数组由空缺组成。

  也有可能你在记录时犯了错误，无法恢复这些空缺。在这种情况下，答案应视为 $0$。



#### 解法：

- 观察一层的人：如果他没扔则不考虑，若扔了 $k$ 个则说明在扔第 $k$ 个之前，上面往下扔的个数 $\leq c-k$。更直接的，$a_i$ 可以为 $1$ 的充分条件是 $i\leq c$。

  我们做一个 DP，设 $f_{i,j}$ 表示对于总共 $i$ 层，满足题目条件，且总共扔了 $j$ 个纸飞机的方案数。

  我们枚举最下面一层扔的个数 $k$，由上述分析有 $\dbinom{c}{k}$ 种情况，并转移到了 $f_{i-1,j-k}$。

  具体细节上需要考虑剩余的与 $c$ 的关系，总复杂度 $O(nmc)$。

- 组合做法：

  我们设 $x_i$ 为第 $i$ 层扔的飞机个数。则有：$\sum\limits_{i=1}^nx_i=m,x_n=c$。

  那么对于一组合法的 $x$，方案数为：$\prod\limits_{i=1}^{n-1}\dbinom{c}{x_i}$。

  考虑组合意义，有 $n-1$ 种物品，每种有 $c$ 个，总共要选 $m-c$ 个，即 $\dbinom{c(n-1)}{m-c}$。



#### 代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <ctime>
#include <random>
#include <cassert>
#include <numeric>
#include <cmath>
#include <bitset>
#include <ext/pb_ds/assoc_container.hpp>
#define pii pair<int, int>
#define fi first
#define se second
#define MP make_pair
#define ep emplace
#define eb emplace_back
#define int long long
#define rep(i, j, k) for (int i = (j); i <= (k); i++)
#define per(i, j, k) for (int i = (j); i >= (k); i--)
typedef double db;
typedef long double ldb;
typedef long long ll;
//typedef __int128 lll;
typedef unsigned long long ull;
typedef unsigned int ui;
using namespace std;
using namespace __gnu_pbds;
bool Mbe;

//char buf[1<<20],*p1,*p2;
//#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin), p1 == p2) ? 0 : *p1++)
int read() {
	int s = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') f ^= (c == '-'), c = getchar();
	while (c >= '0' && c <= '9') s = s * 10 + c - '0', c = getchar();
	return f ? s : -s;
}
template<typename T>void chkmax(T&x,const T&y){if(x<y)x=y;}
template<typename T>void chkmin(T&x,const T&y){if(x>y)x=y;}

const int mod=1e9+7,N=205;
int fplus(int x,int y){return x+y>=mod?x+y-mod:x+y;}
void Fplus(int&x,int y){x=fplus(x,y);}
int fminus(int x,int y){return x-y<0?x+mod-y:x-y;}
void Fminus(int&x,int y){x=fminus(x,y);}
int fpow(int x,int k=mod-2){
	int res=1;
	for(;k;k>>=1){
		if(k&1)res=res*x%mod;
		x=x*x%mod;
	}
	return res;
}
int fac[N],ifac[N],n,c,m,f[N][N*N],a[N];
int C(int x,int y){return fac[x]*ifac[y]%mod*ifac[x-y]%mod;}

bool Med;
signed main() {
	fprintf(stderr,"%.3lfMb\n",(&Mbe-&Med)/1024./1024.);
	fac[0]=1;
	rep(i,1,200)fac[i]=fac[i-1]*i%mod;
	ifac[200]=fpow(fac[200]);
	per(i,200,1)ifac[i-1]=ifac[i]*i%mod;
	for(int T=read();T--;){
		n=read(),c=read(),m=read();
		rep(i,1,m)a[i]=read();
		rep(i,0,n)memset(f[i],0,(m+1)<<3);
		f[0][0]=1;
		rep(i,1,n)rep(j,0,m)rep(k,0,min(j,c)){
			if(i==n&&m==j&&k!=c)continue;
			if(m-j+k>=c)Fplus(f[i][j],f[i-1][j-k]*C(c,k)%mod);
			else Fplus(f[i][j],f[i-1][j-k]*C(m-j+k,k)%mod);
		}
		printf("%lld\n",f[n][m]);
	}
	return 0;
}

```

---

## 作者：CReatiQ (赞：1)

### 组合意义

首先，顶层必须扔 $c$ 只飞机。

对于下面的每一层，需要决定它们看到的前 $c$ 只飞机分别是自己丢出去的还是楼上丢下来的。

而楼下总共丢出 $m-c$ 只飞机。

故答案为 $\large \binom{(n-1) c}{m-c}$。

---

### dp

记 $dp_{i,j}$ 为 $n=i,m=j$ 时原问题的答案，有：

$$
dp_{i,j}=\sum_{0 \leq k \leq c} \binom{c}{k} dp_{i-1,j-k}
$$

时间复杂度为 $\mathcal{O}(n \cdot c \cdot m)$。

---

## 作者：lfxxx (赞：0)

限制很多，我们一个个来看，首先是最后所有楼层全部看到了至少 $c$ 个纸飞机，由于楼层看到的纸飞机是单调的，所以只需要第 $n$ 层满足这个限制即可，又因为第 $n$ 层的特殊性，所以这个限制实际上等价于 $a_m=n$ 并且 $n$ 在序列 $a$ 中出现了恰好 $c$ 次。

剩下的限制就只有一个数前面至多 $c-1$ 个大于等于其的数，这是一个偏序关系有关的限制，我们考虑对着这个偏序关系也就是值域看问题，考虑从大往小依次把数加入序列中，由于固定了最终的序列结构去填数不方便，所以我们去用一个动态的序列描述这个过程，也就是每次把一些数插入原来的序列的空之中形成新的序列。

那么限制就很好处理了，假若当前处理的是值等于 $x$ 的数，枚举其加了 $k$ 个，那显然将这些数插入序列后这些数全部位于序列的前 $c$ 项，那么容易得知，假若序列原来长度为 $j$，加数方案就是 ${\min(c-k,j)+k} \choose k$。

最后用 dp 来计数，设计 $dp_{i,j}$ 表示考虑到值等于 $i$ 的数并形成了长度为 $j$ 的序列，按照上面的办法转移即可，时间复杂度 $O(n \times m \times c)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9+7;
const int maxm = 1e4+114;
const int maxn = 214;
int dp[maxm],g[maxm];
int a[maxm];
int n,m,c;
int C[maxn][maxn];
void init(){
    C[0][0]=1;
    for(int i=1;i<maxn;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    }
}
void work(){
    cin>>n>>c>>m;
    for(int i=1;i<=m;i++) cin>>a[i];
    dp[c]=1;//a[i]=n 必须放 c 个
    for(int i=n-1;i>=1;i--){
        for(int j=0;j<=m;j++){
            for(int k=0;k<=c;k++){
                if(j+k<=m){
                    int f=c-k;
                    f=min(f,j);
                    g[j+k]=(g[j+k]+dp[j]*C[f+k][f]%mod)%mod;
                }
            }
        }
        for(int j=0;j<=m;j++) dp[j]=g[j],g[j]=0;
    }
    cout<<dp[m]<<"\n";
    for(int i=0;i<=m;i++) dp[i]=0;
    return ;
}
signed main(){
    init();
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
 
```

---

## 作者：2022dyx (赞：0)

先分析题目性质，由于从最底下的人开始最后看到的纸飞机数量一定不增，所以只要最高的人发射的纸飞机到了 $c$ 个，其他人看到的一定不小于 $c$ 个，于是其他人的这个约束就不用管了。

对于任何一个人来说，自己发射的纸飞机只可能出现在自己看到的前 $c$ 个纸飞机中。对于除了最高层的那个人以外，其余 $n-1$ 个人总共的 $(n-1)c$ 个位置都可以任意选择是自己发射的还是看到的，由于最高层的人一定要自己发射 $c$ 个纸飞机，那么其余的人自己发射的纸飞机总数就是 $m-c$。若每种可能性与一种合法发射方案一一对应，那么答案就是 $\binom{(n-1)c}{m-c}$，下面来证明这一点。

若从最底下的人开始，不断把每个人的第一个位置删掉，直到删到自己发射的纸飞机为止，这意味着这个人发射了第一个纸飞机，下面的人都看到。容易发现只要这样持续不断进行下去，最终一定与一个发射纸飞机的顺序对应，又因为每一个发射纸飞机的顺序肯定都对应着一个排列的可能性，因此答案确实就是 $\binom{(n-1)c}{m-c}$。

下面是代码。

```
#include <bits/stdc++.h>
#define int long long freopen(#x ".out", "w", stdout);
using namespace std;
constexpr int N = 1e4 + 5;
constexpr int mod = 1e9 + 7;
int t, n, c, m, x, fac[N], inv[N];
int pw(int x, int y) { return !y ? 1 : (y & 1 ? x : 1) * pw(x * x % mod, y >> 1) % mod; }
signed main() {
    cin.tie(0) -> sync_with_stdio(false); 
    cin >> t;
    while(t--) {
        cin >> n >> c >> m;
        for (int i = 1; i <= m; ++i) cin >> x;
        fac[0] = inv[0] = 1;
        for (int i = 1; i <= n * c; ++i) fac[i] = fac[i - 1] * i % mod, inv[i] = pw(fac[i], mod -2 );
        cout << fac[(n - 1) * c] * inv[m - c] % mod * inv[n * c - m] % mod << '\n';
    }
}
```

---

## 作者：xyvsvg (赞：0)

按楼层从高到低依次考虑。顶层特殊考虑（因为他只能扔恰好 $c$ 个纸飞机）

不妨设第 $i$ 个人扔了 $a_i$ 个纸飞机，则答案为：
$$\sum\limits_{\sum a_i=m-c}{\prod {c\choose a_i}}$$
根据范德蒙德卷积，答案为：
$$nc-c\choose {m-c}$$

直接预处理阶乘与逆元，则复杂度为 $O(T+\max(m))$，代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7,N=1e4;
int fac[N+10],inv[N+10],finv[N+10];
void solve()
{
    auto C=[&](int n,int m)
    {
        return 1LL*fac[n]*finv[m]%mod*finv[n-m]%mod;
    };
    int n,c,m;
    cin>>n>>c>>m;
    cout<<C(n*c-c,m-c)<<endl;
    while(m--)
    {
        int trash;
        cin>>trash;
    }
}
int main()
{
    fac[0]=inv[1]=finv[0]=1;
    for(int i=2;i<=N;++i)
        inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod;
    for(int i=1;i<=N;++i)
        fac[i]=1LL*fac[i-1]*i%mod,
        finv[i]=1LL*finv[i-1]*inv[i]%mod;
    int t;
    cin>>t;
    while(t--)
        solve();
    return 0;
}

```

---

## 作者：233zhang (赞：0)

# 题意：

有一栋 $n$ 层的建筑物，楼层从下到上编号为 $1$ 至 $n$。每层居住着一个居民。

现要使得每个居民各自看到至少发射了 $c$ 架飞机（若居民看到已经至少有 $c$ 架飞机，那么该居民不会再发射飞机），总共发射了 $m$ 架飞机。

$m$ 架飞机的信息全部丢失，你可以任意填写，使其满足条件，给出方案数，答案对 $10^9+7$ 取模。



# 思路：

我们首先注意到，每个居民至少得看到发射了 $c$ 架飞机，那么处于第 $n$ 层的人，他只能看到由自己发射的飞机，也就是说，第 $n$ 个人必定发射了 $c$ 架飞机。那么第 $n-1$ 个人呢？我们发现，由于，由于第 $n$ 个人飞飞机顺序不同的影响，第 $n-1$ 个人所能飞的飞机数量也会随之改变，这并不好求。于是，如何消除后面的人对前面的人的影响成为了目前迫切需要解决的问题。

一个很符合直观感受的办法是，我们可以先处理前面的人。因为前面的人并不会干扰到后面的人，所以前面飞机顺序改变并不会产生上述影响。经过一些思考后，我们不难发现一个有趣的性质，当我们做到第 $i$ 层时，他能够在目前空缺的前 $c$ 个位置任意飞若干个。我们可以证明：由于前 $i-1$ 个位置已经放完，且并不会影响到后续，我们可以忽略他们，也就是说，第 $i$ 层其实可以视作为 第 $1$ 层；由于后续层数均会对其产生影响，那么前 $c$ 个空缺位置，其都能观测到，那么，如果他想要发射飞机，就必须在 前 $c$ 个位置发射。

因此，我们可以暴力枚举前 $c$ 个位置选取 $k$ 个放置，这显然组合数学即可算出，其为 $C_{c}^{k}$。

我们定义 $dp_{i,j}$ 为总共 $i$ 层楼，发射 $j$ 架飞机的方案数。我们只需要枚举第一层楼发射了 $k$ 架飞机，那么剩下的 $i-1$ 层楼发射了 $j-k$ 架飞机，其方案数显然为 $dp_{i-1,j-k}$。

不难得出转移方程为：

$$dp_{i,j}=\displaystyle\sum_{k=0}^cC_{c}^k \times dp_{i-1,j-k}$$

并且，当只有 $1$ 层时，由上述所述，最后一层一定发射了 $c$ 架飞机，那么只有 $dp_{1,c}=1$。

最后答案即为 $dp_{n,m}$，代码如下：

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N=1e4+5;
const int inf=0x3f3f3f;
const int mod=1e9+7;

ll n,c,m,a[N],dp[105][N],frc[N],inv[N];

int qpow(ll a,int b) {
    ll ans=1;
    a=(a%mod+mod)%mod;
    for (;b;b>>=1) {
        if (b&1) ans=(a*ans)%mod;
        a=(a*a)%mod;
    }
    return ans;
}

void work() {
    inv[0]=frc[0]=1;
    for (int i=1;i<=10000;i++) frc[i]=frc[i-1]*i%mod;
    inv[10000]=qpow(frc[10000],mod-2);
    for (int i=9999;i;i--) inv[i]=inv[i+1]*(i+1)%mod;
}

ll C(int n,int m) {
    if (m<0||m>n) return 0;
    return frc[n]*inv[m]%mod*inv[n-m]%mod;
}

void solve() {
    cin>>n>>c>>m;
    for (int i=1;i<=m;i++) cin>>a[i];
    for (int i=1;i<=n;i++)
        for (int j=0;j<=m;j++) dp[i][j]=0;
    dp[0][0]=1;
    for (int i=1;i<=n;i++) 
        for (int j=c;j<=m;j++)
            for (int k=0;k<=c;k++)
             dp[i][j]=(dp[i][j]+C(c,k)*dp[i-1][j-k]%mod)%mod;
    cout<<dp[n][m]<<"\n";
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    work();
    int qt = 1;cin >> qt;while (qt--) 
    solve();

    return 0;
}
```

---

