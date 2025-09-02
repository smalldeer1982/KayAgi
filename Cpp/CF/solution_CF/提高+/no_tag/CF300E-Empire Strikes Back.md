# Empire Strikes Back

## 题目描述

In a far away galaxy there is war again. The treacherous Republic made $ k $ precision strikes of power $ a_{i} $ on the Empire possessions. To cope with the republican threat, the Supreme Council decided to deal a decisive blow to the enemy forces.

To successfully complete the conflict, the confrontation balance after the blow should be a positive integer. The balance of confrontation is a number that looks like ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF300E/ae456f9650d5b3ca46e54c303d07fec088f6ad5e.png), where $ p=n! $ ( $ n $ is the power of the Imperial strike), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF300E/99b314c14cf87aaec7902ee9933ec2e853964496.png). After many years of war the Empire's resources are low. So to reduce the costs, $ n $ should be a minimum positive integer that is approved by the commanders.

Help the Empire, find the minimum positive integer $ n $ , where the described fraction is a positive integer.

## 样例 #1

### 输入

```
2
1000 1000
```

### 输出

```
2000```

## 样例 #2

### 输入

```
1
2
```

### 输出

```
2```

# 题解

## 作者：Owen_codeisking (赞：3)

数论好题！

首先 $\prod_{i=1}^{n}a_i=\prod_{i=1}^{tot}p_i^{e_i}$，$tot$ 为 $n$ 以内质数的个数。

那么我们可以处理一个后缀和，然后暴力算 $e_i$

现在可以二分或者在 $p$ 进制下贪心，我使用了二分。

我们对于每个质数算其出现的次数 $\lfloor \frac {mid}{p}\rfloor+\lfloor \frac {mid}{p^2}\rfloor+...$

然后二分下界为 $1$，上界为 $\sum_{i=1}^{n}a_i$，时间 

$$O(m/\text{log} _2 m\times \sum_{i=1}^{tot}\text{log}_{p_i} m)$$

$$=O(m/\text{log} _2 m\times \sum_{i=1}^{tot}\text{log}_{2} m/\text{log}_2 p_i)$$

$$=O(m\sum_{i=1}^{tot}1/\text{log}_2 p_i)$$

其中 $m=\text{max}(a_1,a_2,...,a_n)$

当然，有 $5000ms$ 的时间我们根本不用怕 $TLE$ 啦。

$Code\ Below:$

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn=10000000+10;
ll n,Max,a[maxn],cnt[maxn],pri[maxn],tot;bool vis[maxn];

inline ll read(){
	register ll x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return (f==1)?x:-x;
}

inline void sieve(ll n){
	for(ll i=2;i<=n;i++){
		if(!vis[i]) pri[++tot]=i;
		for(ll j=1;j<=tot&&i*pri[j]<=n;j++){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0) break;
		}
	}
}

inline bool check(ll mid){
	ll now;
	for(ll i=1;i<=tot;i++){
		now=0;
		for(ll j=pri[i];j<=mid;j*=pri[i]) now+=mid/j;
		if(now<cnt[i]) return 0;
	}
	return 1;
}

int main()
{
	n=read();
	ll x,l=1,r=0,mid,ans=1;
	for(ll i=1;i<=n;i++){
		x=read();a[x]++;
		Max=max(Max,x);r+=x;
	}
	for(ll i=Max;i>=1;i--) a[i]+=a[i+1];
	sieve(Max);
	for(ll i=1;i<=tot;i++){
		for(ll j=pri[i];j<=Max;j*=pri[i])
			for(ll k=j;k<=Max;k+=j) cnt[i]+=a[k];
	}
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)) r=mid-1,ans=mid;
		else l=mid+1;
	}
	printf("%I64d\n",ans);
    return 0;
}
```

---

## 作者：Priestess_SLG (赞：0)

很明显答案具有单调性，于是考虑怎么二分。首先筛法筛出 $10^7$ 以内的全部质数，然后对于二分到的数 $x$，计算 $x!$ 内有多少个质因数 $p$，比较其和原式中质因数 $p$ 的个数即可。

问题变为如何计算 $\prod\limits_{i=1}^k a_i!$ 中所有质因子 $p$ 的出现个数。首先可以发现一个质因子 $p'$ 会被 $a_i$ 计数当且仅当 $p'\le a_i$，进一步的可以发现一个数 $a_i$ 只会对 $p\in\text{prime}\cap[1,a_i]$ 集合内所有的整数产生贡献。因此可以差分然后前缀和维护每一个质因子出现的次数。然后枚举每一个质因子 $p$，枚举幂次 $k$，只需要计算出现了多少个 $p^k$ 即可。因此问题解决，卡卡常就能过。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 10000010;
int diff[N], a[N];
bitset<N> isp;
int idx, pr[N / 5];
void sieve() {
    isp[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!isp[i]) pr[++idx] = i;
        for (int j = 1; j <= idx; ++j) {
            int k = i * pr[j];
            if (k >= N) break;
            isp[k] = 1;
            if (i % pr[j] == 0) break;
        }
    }
}
int n, buc[N];
int chk(int x) {
    for (int i = 1; i <= idx; ++i) {
        int sum = 0;
        for (__int128 j = pr[i]; j <= x; j *= pr[i]) sum += x / j;
        if (sum < buc[i]) return 0;
    }
    return 1;
}
signed main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) ++diff[1], --diff[a[i] + 1];
    for (int i = 1; i < N; ++i) diff[i] += diff[i - 1];
    sieve();
    for (int i = 1; i <= idx; ++i)
        for (int j = pr[i]; j < N; j *= pr[i])
            for (int k = j; k < N; k += j)
                buc[i] += diff[k];
    int l = 1, r = 1e16, best = -1;
    while (l <= r) {
        int mid = l + r >> 1;
        if (chk(mid)) best = mid, r = mid - 1;
        else l = mid + 1;
    }
    cout << best << '\n';
    return 0;
}
```

---

## 作者：Hanx16Kira (赞：0)

# Empire Strikes Back

[Luogu CF300E](https://www.luogu.com.cn/problem/CF300E)

## Solution

考虑先对 $\displaystyle\prod\limits_{i=1}^ka_i!$ 分解质因数。假设分解出来为 $\displaystyle\prod\limits_{i=1}^tp_i^{k_i}$，那么显然可以直接二分找到 $p$，因为一定存在 $p_i\le 10^7$。这部分容易做到 $\mathcal O(n\log n)$ 的复杂度，即直接筛出 $10^7$ 之内的所有质数 $p_i$，然后枚举 $p_i$ 的所有次幂并计算其贡献。

考虑怎么对 $\displaystyle\prod\limits_{i=1}^ka_i!$ 分解质因数，直接暴力对每个数分解然后加起来显然是不行的。发现 $a_i!$ 其实可以看做是一个区间的数乘起来，那么可以使用差分与处理出每个数出现了多少次，然后使用和上面一样的做法，枚举 $p_i$ 的每一个次幂，然后遍历所有的 $p_i\mid d$，将 $d$ 出现的次数贡献进 $p_i$ 的贡献。

时间复杂度大概是比 $n\log^2 n$ 小的多的，具体多少不会算（逃。

```cpp
// Cirno is not baka!
#include <bits/stdc++.h>
#define For(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define Rof(i, a, b) for (int i = (a); i >= (int)(b); --i)
#define FILE(filename) { \
    freopen(#filename ".in", "r", stdin); \
    freopen(#filename ".out", "w", stdout); \
}
#define All(x) x.begin(), x.end()
#define rAll(x) x.rbegin(), x.rend()
#define pii pair<int, int>
#define fi first
#define se second
#define i64 long long
#define i128 __int128_t
#define mkp make_pair
// #define int long long
#define epb emplace_back
#define pb push_back
using namespace std;

const int _N = 1e6 + 5, mod = 1e9 + 7, inf = 1e9, _M = 1e7 + 5;
template<typename T> void Max(T &x, T y) {x = max(x, y);}
template<typename T> void Min(T &x, T y) {x = min(x, y);}

namespace BakaCirno {
    bitset<_M> flag;
    vector<int> prim;
    vector<i64> cnt;
    void InitPrime(int n) {
        For(i, 2, n) {
            if (!flag[i]) prim.epb(i);
            for (int j : prim) {
                if (j * i > n) break;
                flag[j * i] = 1;
                if (i % j == 0) break;
            }
        }
        cnt.resize(prim.size(), 0);
    }
    int N, A[_M];
    void _() {
        InitPrime(1e7);
        cin >> N; A[0] = N;
        int mx = 0;
        For(i, 1, N) {
            int x; cin >> x; Max(mx, x);
            A[x + 1] -= 1;
        }
        For(i, 1, mx) A[i] += A[i - 1];
        For(i, 0, prim.size() - 1) for (i64 j = prim[i]; j <= mx; j *= prim[i])
            for (int k = j; k <= mx; k += j)
                cnt[i] += A[k];
        i64 L = 1, R = 1e15;
        auto Check = [&](i64 x)->bool {
            vector<i64> tcnt(prim.size(), 0);
            For(i, 0, prim.size() - 1) for (i128 j = prim[i]; j <= x; j *= prim[i])
                tcnt[i] += x / j;
            For(i, 0, prim.size() - 1)
                if (tcnt[i] < cnt[i]) return 0;
            return 1;
        };
        while (L <= R) {
            i64 mid = (L + R) >> 1;
            if (Check(mid)) R = mid - 1;
            else L = mid + 1;
        }
        cout << L << '\n';
    }
}

signed main() {
    // FILE(test);
    cin.tie(0)->sync_with_stdio(0); int T = 1;
    // cin >> T;
    while (T--) BakaCirno::_();
    // fout.flush();
}
```

---

## 作者：Yuby (赞：0)

[题面](https://www.luogu.com.cn/problem/CF300E)

#### 分析

（看到如此长的时间和如此大的空间怎么搞不行？）

注意题目中 $k$ 的范围很大，但是 $a_i \leq 10^7$，不难想到类似质因数分解的方法。问题在于阶乘的复杂度很高，难以具体计算，取模的话会影响结果。所以选择差分（还是很好想的）。
差分之后切记不能直接分解每一个数的质因数，否则复杂度为 $O(\sum a_i \pi(a_i))$ 是一个不能接受的复杂度。

注解：$\pi(x)$ 表示 $x$ 以内的质数个数。

我们选择去枚举质数然后统计。

```cpp
for(ll i=1;i<=pcnt;i++)
		for(ll j=pr[i];j<=maxn;j*=pr[i])
			for(ll k=j;k<=maxn;k+=j)
				cnt[i]+=a[k];
```

对于第 4 行为什么不用乘以 $j$ 做一个解释（理解的可以跳过）：
对于所有含有 $j^{x+1}$ 的元素，一定含有 $j^x$ ，那么在计算 $j^{x+1}$ 的时候，含有 $j^x$ 的数都记录了贡献为 $x$，变成 $j^{x+1}$ 时对答案的贡献为 1。

这部分复杂度大致为 $O(\pi(n)\log n\log\log n)$，可以接受。

回到题目，阶乘的递推式为 $f(x)=f(x-1)\times x$。如果 $f(x)$ 满足要求，$f(x+1)$ 必然也满足要求。那就可以二分了，右边界应该为 $\sum a_i$。

总复杂度：$O(能过)$（我真的分析不出来了）。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN=1e7+7ll,MAXM=1e7+7ll;
inline ll max(ll x,ll y){return x>y?x:y;}
inline ll read(){ll read_result=0,is_below_0=0;char now_ch=0;while(!isdigit(now_ch)){is_below_0|=now_ch=='-';now_ch=getchar();}while(isdigit(now_ch)){read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);now_ch=getchar();}return is_below_0?-read_result:read_result;}
inline void write(ll x){if(x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');}
ll n,a[MAXM],pr[MAXM],pcnt=0,cnt[MAXM];
bitset<MAXM>is_prime;
void prime(ll Size)
{
	for(ll i=2;i<=Size;i++)is_prime[i]=1;
	for(ll i=2;i<=Size;i++)
		if(is_prime[i])
			for(ll j=2*i;j<=Size;j+=i)
				is_prime[j]=0;
	for(ll i=2;i<=Size;i++)if(is_prime[i])pr[++pcnt]=i;
}
bool check(ll x)
{
	for(ll i=1;i<=pcnt;i++)
	{
		ll num=0;
		for(ll j=pr[i];j<=x;j*=pr[i])
			num+=(x/j);
		if(num<cnt[i])return 0;
	}
	return 1;
}
int main()
{
	n=read();
	ll maxn=0,sum=0,x;
	for(ll i=1;i<=n;i++)
	{
		x=read();
		a[x]++;
		maxn=max(maxn,x);
		sum+=x;
	}
	prime(maxn);
	for(ll i=maxn;i>=1;i--)a[i]+=a[i+1];
	for(ll i=1;i<=pcnt;i++)
		for(ll j=pr[i];j<=maxn;j*=pr[i])
			for(ll k=j;k<=maxn;k+=j)
				cnt[i]+=a[k];
	ll l=1,r=sum,ans=1;
	while(l<=r)
	{
		ll mid=(l+r)/2;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	write(ans);
	return 0;
}
```


---

## 作者：泠小毒 (赞：0)

# Empire Strikes Back

给定k个数a1,a2...ak

求一个数n，使n!是a1!a2!...ak!的倍数

## 广告插入

在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/luogu-CF300E/)

## 解法

这是一道数论好题啊

手推了一个小时，然后没开longlong挂掉了，有点自闭

看到数据范围，k是1e6，a是1e7

阶乘的处理方式肯定是计算质因数，这里我们用了欧拉筛，这样可以每次精确定位到质因子（这是我想出来最快的方法了，大佬别怼我qwq）

计算质因数的复杂度大概就是max(a)×平均质因子个数，反正有5秒，卡一卡就过去了
上面只是简单的数论运用，接下来才是让人自闭的地方=-=

我们既然求出了n!需要含有的所有质因子，那么对于每一种质因子求能满足的最小n，在这些n里面取max

那么这个n怎么求呢，我们知道要求n!中某个质因子m的数量，需要用n除以m的1~p次方

现在将这个式子乘以m的p次方后展开，当n等于m的p次方时，我们可以得到这个质因子的数量x=(m^(p)-1)/(m-1)

对于每一段l~r的区间，i(l<=i<=r)不是x的任意次方且r-l+1是x的p次方时，该区间的累乘和中质因子x的数量是一个定量（自己思考一下为什么qwq）

那么就可以贪心来求解上面的问题了，对于每个质因子m的数量k，我们可以从大到小枚举p(0<=p<=log_p(k))，然后就能找到所需要求的n

对于这个贪心，复杂度也是log，所以总复杂度大概是(大常数(质因子数量)×max(a)+m(质数数量，远小于max(a))log(m))

## ac代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[1000010],cnt=0,v[10000010],prime[1000010],mp[10000010],g[10000010],tot[1000010];
int maxx,res,sum,x;
void init(){for(int i=1;i<=n;i++)scanf("%lld",&a[i]),mp[a[i]]++,maxx=max(maxx,1ll*a[i]);}
void get_prime()
{
	for(int i=2;i<=maxx;i++)
	{
		if(!v[i])v[i]=i,prime[++cnt]=i,g[i]=cnt;
		for(int j=1;j<=cnt;j++)
		{
			if(prime[j]>v[i]||prime[j]>maxx/i)break;
			v[i*prime[j]]=prime[j];
		}
	}
}
//欧拉筛
void calc(int k){while(k!=1)tot[g[v[k]]]+=res,k/=v[k];}
//用欧拉筛分解质因数
void work(){for(int i=1;i<=maxx;i++){calc(i);res-=mp[i];}}
//通过mp的优化可以不用对每个阶乘处理，注意！！！
int calcx(int k)
{
	res=0,sum=prime[k];
	while(sum<tot[k])sum*=prime[k];
	while(tot[k])x=(sum-1)/(prime[k]-1),res+=tot[k]/x*sum,tot[k]%=x,sum/=prime[k];
	return res;
}
//计算出最小的阶乘满足质因子的数量
void get_ans(){for(int i=1;i<=cnt;i++)maxx=max(maxx,calcx(i));}
signed main()
{
	freopen("strike.in","r",stdin),freopen("strike.out","w",stdout);
	scanf("%lld",&n),res=n,init(),get_prime(),work(),maxx=1,get_ans(),printf("%lld\n",maxx);
	return 0;
}
```

---

