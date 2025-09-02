# [ABC156E] Roaming

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc156/tasks/abc156_e

$ n $ 個の部屋がある建物があります。 部屋には $ 1 $ から $ n $ までの番号が付いています。

建物の各部屋から、他の任意の部屋に移ることが可能です。

ここで、建物のある部屋 $ i $ にいる人が、別の部屋 $ j~\ (i\ \neq\ j) $ に移ることを **人の移動** と呼ぶことにします。

最初、建物の各部屋には人が $ 1 $ 人いました。

このあと現在までに、人の移動がちょうど $ k $ 回起きたことが分かっています。

現在、建物の各部屋にいる人の数の組合せとして、ありえるものは何通りでしょうか。

$ (10^9\ +\ 7) $ で割った余りを求めてください。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 3\ \leq\ n\ \leq\ 2\ \times\ 10^5 $
- $ 2\ \leq\ k\ \leq\ 10^9 $

### Sample Explanation 1

現在、部屋 $ 1 $ にいる人の数を $ c_1 $、部屋 $ 2 $ にいる人の数を $ c_2 $、部屋 $ 3 $ にいる人の数を $ c_3 $ と すると、$ (c_1,\ c_2,\ c_3) $ としてありえるものは、 - $ (0,\ 0,\ 3) $ - $ (0,\ 1,\ 2) $ - $ (0,\ 2,\ 1) $ - $ (0,\ 3,\ 0) $ - $ (1,\ 0,\ 2) $ - $ (1,\ 1,\ 1) $ - $ (1,\ 2,\ 0) $ - $ (2,\ 0,\ 1) $ - $ (2,\ 1,\ 0) $ - $ (3,\ 0,\ 0) $ の $ 10 $ 通りです。 例えば、まず部屋 $ 1 $ にいる人が部屋 $ 2 $ に移動し、 次に部屋 $ 2 $ にいる誰かが部屋 $ 3 $ に移動した場合を考えると、 $ (c_1,\ c_2,\ c_3) $ は $ (0,\ 1,\ 2) $ になります。

### Sample Explanation 2

個数を $ (10^9\ +\ 7) $ で割った余りを出力してください。

## 样例 #1

### 输入

```
3 2```

### 输出

```
10```

## 样例 #2

### 输入

```
200000 1000000000```

### 输出

```
607923868```

## 样例 #3

### 输入

```
15 6```

### 输出

```
22583772```

# 题解

## 作者：cccyyyxxx (赞：18)

 [题目传送门](https://www.luogu.com.cn/problem/AT_abc156_e)
 
##  分析：

这种容易看出是数学题。当所有人都移动完后，空房子（人数为零）的数量最少为  $0$  最多为  $min(n-1,k)$  。因此我们可以枚举最后空房子的数量。当空房子数量为  $i$  时，非空房子有  $n-i$  个，那我们就需要将  $n$  个人放入  $n-i$  个房子，运用插板法，在  $n-1$  个空中，插入  $n-i-1$  个板。那么对于每一个  $i$  ，答案为  $C_n^i \times C_{n-1}^{n-i-1}$  。最后累加答案即可。

## 注意：

因为取模，且数据范围不小，因此需要逆元。

## code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll Maxn = 2e5+10;
const ll Mod = 1e9+7;
ll fac[Maxn],n,k,ans,Max;
inline ll qsm(ll a,ll b)
{
	ll cnt=1;
	while(b)
	{
		if(b&1)
			cnt=cnt*a%Mod;
		b>>=1;
		a=a*a%Mod;
	}
	return cnt;
}
inline ll Inv(ll a)
{
	return qsm(a,Mod-2)%Mod;
}
inline void init()
{
	Max=min(n-1,k);
	fac[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=i*fac[i-1]%Mod;
}
inline ll C(ll n,ll m)
{
	ll cnt;
	cnt=((fac[n]*Inv(fac[m]))%Mod*Inv(fac[n-m]))%Mod;
	return cnt;
}
int main()
{
	cin>>n>>k;
	init();
	for(int i=0;i<=Max;i++)
		ans=(ans+(C(n,i)*C(n-1,n-i-1))%Mod+Mod*2)%Mod;
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：灰鹤在此 (赞：7)

题目简化：有 $n$ 个**不同**的盒子，每个盒子里有 $1$ 个**相同**的球。求我们必须移动 $k$ 次球之后状态的方案数。

因为题目中 $n\ge3$，所以我们不用考虑当 $n=2,k=2$ 时最终状态只可能是 $\{1,1\}$ 的情况。因为每一个球 $a$ 可以先移到 $b$ 再移到 $c$，也可以直接移到 $c$，如果 $k$ 太大的话这个球可以在两个盒子里反复移动来消耗 $k$。

也就是说明，如果 $k\ge n-1$ 的时候，所有的状态都可以达到，因为 $n-1$ 个球可以直接移到它想要达到的位置。此时的方案数是 $C_{2n-1}^{n-1}$。这个可以通过插板法来计算证明。

证明：我们先给这 $n$ 个球再加上 $n$ 个球让它成为 $2n$ 个球，然后我们要保证每一个盒子里必须有 $1$ 个球，因为我们加上了 $n$ 个球，又让这 $n$ 个盒子里面必须有 $1$ 个球，这相当于我们没有加上 $n$ 个球，然后再对于这 $2n$ 个球插 $n-1$ 个板，有 $2n-1$ 个空，所以答案就是 $C_{2n-1}^{n-1}$。

接下来考虑 $k<n-1$ 的情况。

问题又可以转换成最多有 $k$ 个盒子为空的方案数，我们先假设有 $x$ 个盒子**不**为空，那么这 $x$ 个盒子里面有球的情况就是 $C_n^x$，然后我们要在 $x$ 个盒子里面放 $n$ 个球，而且这 $x$ 个盒子里面必须有 $1$ 个球，所以这样的方案数可以通过插板法求得，是 $C_n^{x-1}$。



所以总的情况数就是 $C_n^x\times C_n^{x-1}$，然后将 $x$ 用空的盒子数 $i$ 带入可得 $C_n^{n-i}\times C_{n}^{n-i-1}=C_n^i\times C_n^{i-1}$，然后把每一个 $i$ 从 $0$ 枚举到 $k$ 累加起来就行了。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MaxN=4e5+5;
const long long mod=1e9+7;
long long n,k,fac[MaxN],inv[MaxN];
long long qpow(long long x,long long y){
	long long res=1;
	while(y){
		if(y&1){
			res=res*x%mod;
		}
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
long long C(long long a,long long b){
	return fac[a]*inv[b]%mod*inv[a-b]%mod;
}
void init(){
	fac[1]=fac[0]=inv[0]=inv[1]=1;
	for(long long i=2;i<=MaxN-5;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	inv[MaxN-5]=qpow(fac[MaxN-5],mod-2);
	for(int i=MaxN-6;i>=1;i--){
		inv[i]=inv[i+1]*(i+1)%mod;
	}
}
int main(){
	scanf("%lld%lld",&n,&k);
	init();
	if(k>=n-1){
		printf("%lld\n",C(2*n-1,n-1));
	}else{
		long long ans=0;
		for(long long i=0;i<=min(k,n-1);i++){
			ans=(ans+C(n,i)*C(n-1,i)%mod)%mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：hyxgg (赞：4)

[题目](https://www.luogu.com.cn/problem/AT_abc156_e)

### 前言
模拟赛写到，一眼秒了，但是没取模，寄。

### 思路

首先，对于这个 $k$，我们可以发现，因为可以把一步拆成两步，所以当可以走 $k$ 步的时候，也就代表我们可以走 $[0,k]$ 步。

同时可以发现当 $n\le k$ 时所有人都可以走到任意的房间，所以只要用隔板法找到所有情况就行了。

而剩下的情况就只需要从 $0$ 到 $k$ 枚举 $x$ 代表有 $x$ 个人进行了移动（有 $x$ 个空房），然后用隔板法找到有人的房间内部的情况，再找到有人房间的分布情况就行了。

最后就是：
$$\begin{cases}
     C^{n-1}_{2n-1}& n\le k \\
    \sum_{x=0}^{k} C^{n-i-1}_{n-1}\times C^{i}_{n} & n>k
\end{cases} $$

### 代码
```
#include<iostream>
#include<cstdio>
#define ll long long
#define mod 1000000007
using namespace std;
ll n,k,jc[400005];
ll ny(ll x){ //逆元
    ll dc=x,m=mod-2,re=1;
    while(m){
        if(m&1)re*=dc,re%=mod;
        dc=dc*dc;
        dc%=mod;
        m>>=1;
    }
    return re;
}
ll C(ll a,ll b){//组合数
    if(b==0)return 1;
    if(a<b)return 0;
    return jc[a]*ny(jc[a-b])%mod*ny(jc[b])%mod;
}
int main(){
    scanf("%lld%lld",&n,&k);
    jc[0]=1;
    for(ll i=1;i<=n<<1;i++){
        jc[i]=jc[i-1]*i%mod;//预处理阶乘
    }
    if(k>=n){//特判
        ll ans=C(n+n-1,n-1);
        printf("%lld",ans);
        return 0;
    }
    ll ans=0;
    for(ll i=0;i<=k;i++){
        ans+=C(n-1,n-i-1)*C(n,i)%mod;
        ans%=mod;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Rannio (赞：3)

### 前言
这哪有蓝，评分似乎有点过了。

### 思路
既然是要统计每个房间人数的排列，那我们就枚举把所有人都放到 $i$ 个房间里的方案数，这个用插板法解决，把所有人都放到 $i$ 个房间里也就是把他们分成 $i$ 份，这一部分的答案就是在 $n$ 个人的 $n-1$ 个空中插入 $i-1$ 块隔板的方案数，也就是 $C_{n-1}^{i-1}$。

我们还要考虑每个非空房间的位置，也就是在 $n$ 个房间中选出 $i$ 个房间的方案数，这个很简单，就是 $C_n^i$，所以最终答案就是 $C_n^i \times C_{n-1}^{i-1}$。

最后记得写线性逆元或者预处理一下阶乘，我因为没写这两玩意挂大分了。

```
#include<bits/stdc++.h>
#define int long long
const int mod=1e9+7;
int n,m,ans;
int jc[200005],inv[200005];
int ksm(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
int C(int x,int y){
    return jc[x]*inv[y]%mod*inv[x-y]%mod;
}
void init(){
    jc[0]=1,inv[0]=1;
    for(int i=1;i<=n;i++) jc[i]=jc[i-1]*i%mod;
    inv[n]=ksm(jc[n],mod-2);
    for(int i=n-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
signed main(){
    scanf("%lld%lld",&n,&m);
    init();
    for(int i=1;i<=n;i++){
        if(m>=n-i) ans+=C(n,i)*C(n-1,i-1);
        ans%=mod;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Zctf1088 (赞：3)

[题目链接](https://www.luogu.com.cn/problem/AT_abc156_e)

## 思路

这道题是组合数学。

我们考虑空房子。$k$ 次移动后，空房子的数量最少可能是 $0$，最多是 $\min(k,n-1)$。所以我们可以枚举空房子的数量，最后把答案相加即可。

当空房子数量为 $i$ 时，非空房子的数量就是 $n-i$，那么也就是说要求将 $n$ 个人放进 $n-i$ 个房子的方案数。

那怎么求这个数呢？我们可以运用插板法：对于 $n$ 个人，在这 $n-1$ 个空中，插入 $n-i-1$ 个板，分成 $n-i$ 段，也就是 $n-i$ 个房子。

## 答案

- 从 $n$ 个房子中选出 $i$ 个房子，方案数为 $C_n^i$。

- 从 $n-1$ 个空中选出 $n-i-1$ 个，方方案数为 $C_{n-1}^{n-i-1}$。

所以最终的答案就是 $\sum_{i=0}^{\min(k,n-1)} C_n^i \times C_{n-1}^{n-i-1}$

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
const int N = 2e5 + 10;
int n, k;
long long frac[N], ny[N];
// frac[i]表示i的阶乘，ny[i]表示1到i的每个数的逆元的乘积

long long fpow(long long a, long long x) { // 快速幂
	a %= MOD;
	long long ans = 1;
	while (x > 0) {
		if (x & 1) {
			ans = ans * a % MOD;
		}
		a = a * a % MOD;
		x >>= 1;
	}
	return ans;
}

void init() { // 初始化frac和ny
	frac[0] = ny[0] = 1;
	for (int i = 1; i < N; i++) {
		frac[i] = frac[i - 1] * i % MOD;
		ny[i] = ny[i - 1] * fpow(i, MOD - 2) % MOD;
	}
}

long long C(long long n, long long m) { // 求组合数
	if (n < m) {
		return 0;
	}
	return frac[n] * ny[m] % MOD * ny[n - m] % MOD;
}

int main() {
	scanf("%d%d", &n, &k);
	init();
	long long ans = 0;
	int mx = min(k, n - 1);
	for (int i = 0; i <= mx; i++) {
		ans = (ans + C(n, i) * C(n - 1, n - i - 1) % MOD) % MOD;
	}
	
	printf("%lld\n", ans);
	
	return 0;
}

```


---

## 作者：w33z8kqrqk8zzzx33 (赞：3)

第一个观察：如果一个状态可以在 $2\le k$ 个移动后得到，那肯定也可以在 $k+1$ 个移动得到，应为在状态图里存在2-环和3-环。

假设一个最终状态是 $v_i$，表示第 $i$ 房间有 $v_i$ 个人，已知：

$$\sum_{i=1}^{n}v_i=n$$

$$\sum_{i=1}^{n}|v_i-1|\le 2k$$

可以得到：

$$\sum_{i=1}^{n}(|v_i-1|-v_i)\le 2k-n$$

$$\sum_{i=1}^{n}[v_i=0]-\sum_{i=1}^{n}[v_i\neq0]\le 2k-n$$

$$\sum_{i=1}^{n}[v_i=0]-(n-\sum_{i=1}^{n}[v_i=0])\le 2k-n$$

$$2\sum_{i=1}^{n}[v_i=0]\le 2k$$

$$\sum_{i=1}^{n}[v_i=0]\le k$$

问题现在等价于问有多少个长度为 $n$ 的非负整数序列，使得至多有 $k$ 个0？

枚举一下0的个数和那些0的位置用组合数就好了。

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;
 
#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
 
using ll=long long;
using pii=pair<int, int>;
//#define int ll
const int MOD = 1000000007;

int qpow(int b, int e) {
    if(e == 0) return 1;
    if(!(e&1)) return qpow(1ll*b*b%MOD, e>>1);
    return 1ll*qpow(b,e-1)*b%MOD;
}

int fact[400005];

int choo(int n, int k) {
    return 1ll * fact[n] * qpow(fact[k], MOD-2) % MOD * qpow(fact[n-k], MOD-2) % MOD;
}

int N;

inline int f(int k) {
    return choo(2*N-k-1, N-k-1);
}

inline int e(int k) {
    return 1ll * choo(N-1, k) * choo(N, k) % MOD;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, k; cin >> n >> k;
    N = n;
    fact[0] = 1;
    rep1(i, 2*n) fact[i] = 1ll * fact[i-1] * i % MOD;
    if(k+1 >= n) {
        cout << f(0) << endl;
        return 0;
    }
    int ans = 0;
    rep(i, k+1) ans = (ans + e(i)) % MOD;
    cout << ans << endl;
}

```

---

## 作者：DengDuck (赞：1)

有个结论，就是对于所有满足“形成这种局面的最小步数小于等于 $k$” 的场面，都是可以在 $k$ 步中形成的。

考虑消耗（浪费）步数的两种方式：

- 置换环，就是对于位置不同的 $a_1,\cdots,a_x$，进行操作 $a_1\to a_2,a_2\to a_3,\cdots,a_{x-1}\to a_x$，可以消耗 $x(x>1)$ 步。
- 挖空，假如当前局面有空的人，且存在房间人数为 $1$，一开始走的时候将最终场面的空位置放在最终只有一个人的位置，最后再调换回去，消耗步数为 $1$。

利用这两种方式可以保证这些场面是可以形成的。

所以只需要考虑有那些合法场面。

枚举空位置的数量 $i$，然后求出对应的方案数，先求空位置的位置的方案数，为 $\text{C}_n^i$，然后求剩下的位置的人的数量，球同盒异不可空模型，为 $\text{C}_{n-1}^{n-i-1}$，乘起来就行。

```cpp
#include<bits/stdc++.h>
#define LL long long
const LL N=2e6+5;
const LL M=2e6;
using namespace std;
const LL mod=1e9+7;
LL n,k,inv[N],fac[N];
LL ksm(LL x,LL y)
{
	LL ans=1;
	while(y)
	{
		if(y&1)ans=ans*x%mod;
		x=x*x%mod,y>>=1;
	}
	return ans;
}
LL C(LL n,LL m)
{
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int main()
{
	scanf("%lld%lld",&n,&k);
	fac[0]=1;
	for(int i=1;i<=M;i++)fac[i]=fac[i-1]*i%mod;
	inv[M]=ksm(fac[M],mod-2);
	for(int i=M-1;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
	LL ans=0;
	for(int i=0;i<=k&&i<=n-1;i++)
	{
		ans=(ans+C(n,i)*C(n-1,n-i-1)%mod)%mod;
	}
	printf("%lld",ans);
}
```

---

## 作者：NASFsky (赞：1)

数学题。  
空房间数量范围为 $[0,\min(n-1,k)]$，因为最少时每个房间都有人，而最多时可能只有一个房间有人。  
假设此时空房间数量为 $m$，可以用隔板法进行解决。若不考虑板子之间的不同，相当于 $k$ 个人要用 $n-m-1$ 块相同的板子隔开，方案数显然为 $C_{n-1}^{n-m-1}$。  
但是板子的种类是有影响的。这 $m$ 个房间有 $C_n^m$ 种组合，那么就有 $C_n^m\times C_{n-1}^{n-m-1}$ 种方案。  
那么所求即为：  
$$\sum_{i=0}^{\min(n-1,k)}C_n^i\times C_{n-1}^{n-i-1}$$ 

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mod 1000000007
#define N 200200
using namespace std;
ll n,k,ans,fac[N];
ll qpow(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1)res=res*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return res;
}
ll inv(ll x){return qpow(x,mod-2)%mod;}
ll C(ll n,ll m){return ((fac[n]*inv(fac[m]))%mod*inv(fac[n-m]))%mod;}
int main()
{
	scanf("%lld%lld",&n,&k);
	fac[0]=fac[1]=1;
	for(int i=2;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=0;i<=min(n-1,k);i++)ans=(ans+C(n,i)*C(n-1,n-i-1)%mod)%mod;
	printf("%lld\n",ans);
}
```


---

## 作者：daniEl_lElE (赞：1)

## 思路

命题：对于一个序列 $\{a\}$ 他可以被变换出来，当且仅当 $\sum_{i=1}^n[a_i=0]\leq k$，$n\leq 3$。

原因：考虑有 $x$ 个地方为 $0$，则他们总共可以用 $x$ 步移到其他大于 $1$ 的位置。剩下来我们可以选取一个非 $0$ 的在他的移动路径上动手脚，在若干个位置移来移去即可。

然后考虑反着扣减即可，插板法算出总方案数，然后枚举有 $x=k+1\sim n-1$ 个 $0$，分别计算方案数即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=(1e9+7);
int fac[1000005],inv[1000005];
int qp(int a,int b){
	int ans=1,now=a;
	while(b){
		if(b&1) ans=(ans*now%mod);
		now=(now*now%mod);
		b>>=1;
	}
	return ans;
}
void init(){
	fac[0]=1;
	for(int i=1;i<=1000000;i++) fac[i]=(fac[i-1]*i%mod);
	inv[1000000]=qp(fac[1000000],mod-2);
	for(int i=999999;i>=0;i--) inv[i]=(inv[i+1]*(i+1)%mod);
}
int C(int i,int j){
	return (fac[i]*inv[i-j]%mod)*inv[j]%mod;
}
signed main(){
	int n,k;
	cin>>n>>k;
	init();
	if(k>=n-1){
		cout<<C(n+n-1,n-1);
		return 0;
	}
	int tot=C(n+n-1,n-1);
	for(int i=k+1;i<n;i++){
		int minus=C(n,i)*C(n-1,(n-i)-1)%mod;
		tot+=mod;
		tot-=minus;
		tot%=mod;
	}
	cout<<tot;
	return 0;
}
```

---

## 作者：Redamancy_Lydic (赞：1)

这道题是一道纯粹的组合数题目，难度也不大，适合数论初学者学习。
# 分析

$n$ 个房间里最初都有一个人，这些人移动了 $k$ 次，问方案数。可以分两步走：

## 第一步

由于人的动向不好确定，所以考虑枚举空房间数。移动后，容易得到空房间数量在 $0\sim\min(n-1,k)$ 之间。大循环枚举空房间数，第 $i$ 种情况相当于 $n$ 个房间里选出 $i$ 个空房间，所以方案为 $C_n^i$ 个。

## 第二步

考虑每一种空房间的排列情况，这里可以运用隔板法，由于有 $n$ 个房间，所以有 $n-1$ 个空位，又由于空房间数为 $n-i$ 个，所以有 $n-i-1$ 个板子。得出方案为 $C_{n-1}^{n-i-1}$ 个。

## 答案
将两步合并，得出第 $i$ 个房间的方案数为 $C_n^i \times C_{n-1}^{n-i-1}$ 个，随后累加即可。放个式子：

$\sum_{i=0}^{\min(n-1,k)}C_n^i \times C_{n-1}^{n-i-1}$

然后带上快速幂逆元取模这些常规操作就可以完结撒花了~

# 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=1e6+5;
const int mod=1e9+7;
inline int read()
{
	int X=0; bool flag=1; char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}
	while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}
	if(flag) return X;
	return ~(X-1);
}
ll qw(ll a,ll b)
{
	ll ans=1,t=a%mod;
	while(b>0)
	{
		if(b&1) ans=ans*(t%mod)%mod;
		b/=2;
		t=t*(t%mod)%mod;
	}
	return ans;
}
ll fac[maxn],inv[maxn];
void get_inv()
{
	fac[0]=1;
	for(int i=1;i<maxn;i++) 
	fac[i]=fac[i-1]*i%mod;
	inv[maxn-1]=qw(fac[maxn-1],mod-2);
	for(int i=maxn-2;i>=0;i--) 
	inv[i]=inv[i+1]*(i+1)%mod;
}	
ll C(ll a,ll b)
{
	return (fac[a]*(inv[b]*inv[a-b]%mod))%mod;
}//以上操作就不解释了，不懂得去学习组合数吧 
int n,k;//变量 
long long ans=0;//答案 
int main()
{
//	freopen("roaming.in","r",stdin);
//	freopen("roaming.out","w",stdout);
cin>>n>>k;//输入 
get_inv();//预处理 
for(int i=0;i<=min(n-1,k);i++)//枚举空房间个数 
ans=(ans+(C(n,i)*C(n-1,n-i-1))%mod+mod*2)%mod;//计算每种的答案 
cout<<ans<<endl;//输出 
}
```



---

## 作者：_O_v_O_ (赞：0)

前置知识：逆元求组合，插板法。

我们注意到 $k\ge 2$，那么一个人移动的过程是不重要的，因为假如我们想让 $x\le k$ 个人移动，我们就可以先进行一些“无意义”的操作在移动他们，所以我们只用在意结果就行了。

我们假设已知没有人的房子的数量 $x$，那么分配没有人的房子的方案数就有 $n\choose x$ 种方案。

那么根据插板法，假设已经知道那些房子有人，那么此时方案数为 $n-1\choose n-x-1$。

也就是说，当我们知道有几个房子没人时，总方案数为 ${n\choose x}\times{n-1\choose n-x-1}$。

然后我们发现 $n$ 并不大，所以我们直接枚举 $x$ 即可，$x$ 的取值范围为 $[0,\min\{n-1,k\}]$。

时间复杂度 $O(\min\{n,k\}\log n)$，可以通过。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=2e5+5,mod=1e9+7;
int n,k,fac[N],to,ans;

int exp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}

int inv(int x){
	return exp(x,mod-2);
}

int calc(int x,int y){
	return fac[x]*inv(fac[y])%mod*inv(fac[x-y])%mod;
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>k;
	fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
	for(int i=0;i<=min(n-1,k);i++){
		(ans+=(calc(n,i)*calc(n-1,n-i-1)%mod+mod*2))%=mod;
//		cout<<calc(n,i)<<' '<<calc(n-1,n-i-1)<<' '<<ans<<endl;
	}
	cout<<ans;
	return 0;
}
```

upd：修改了一个笔误，添加了一些证明。

---

## 作者：billtun (赞：0)

## 思路：

我们考虑空房子。

很明显，所有人总共移动 $k$ 次后，最多能得到 $k$ 个空房间。但 $k$ 有可能大于 $n$，所以此时最多有 $n-1$ 个空房间，取 $\min$ 即可。

接下来枚举空房间的数量，然后算方案数。此时非空房间的数量是 $n-i$。我们先把空房间选出来，方案数为 $C_n^i$。

此时剩下的就是非空房间，我们要把 $n$ 个人放进去。也就是把 $n$ 个人分为 $n-i$ 个非空段的数量。很明显是插板法，方案数为 $C_{n-1}^{n-i-1}$。

然后累加答案即可。

## 代码：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define maxn 200005

using namespace std;

ll n, k, ans;

ll qpow(ll a, ll b){
	ll res=1;
	while(b){
		if(b&1){ res=(res*a)%MOD; }
		a=(a*a)%MOD;
		b>>=1;
	}
	return res%MOD;
}

ll f[maxn], g[maxn];

void init(){
	f[0]=g[0]=1;
	for(ll i=1;i<maxn;i++){
		f[i]=(f[i-1]*i)%MOD;
		g[i]=(g[i-1]*qpow(i, MOD-2))%MOD;
	}
}

ll C(ll n, ll m){
	if(n<m) return 0;
	return ((f[n]*g[n-m])%MOD*g[m])%MOD;
}

signed main()
{
	cin>>n>>k;
	init();
	for(ll i=0;i<=min(n-1, k);i++){
		ans=(ans+C(n, i)*C(n-1, n-i-1)%MOD)%MOD;
	}
	
	cout<<ans;
	return 0;
}
```

---

