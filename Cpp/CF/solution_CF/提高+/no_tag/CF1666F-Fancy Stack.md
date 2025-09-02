# Fancy Stack

## 题目描述

有 $n$ 块木块（$n$ 为偶数），长度依次为 $a_1,a_2,…,a_n$（可能会相同），现在想要把它们叠成一叠，且满足以下条件（令这一叠木块从上到下的长度依次为 $b_1,b_2,…,b_n$ 且 $b$ 数组为 $a$ 数组的一个排列）：

- 从上往下的第二块木块长度严格大于第一块，之后的每一块木块交替严格小于或严格大于上一个块，也就是说，满足 $b_1<b_2>b_3<b_4>…>b_{n-1}<b_n$；
- 从上往下的偶数号木块的长度严格递增，即 $b_2<b_4<b_6<…<b_n$。

两种叠法是不同的当且仅当对应的 $b_1,b_2,…,b_n$ 有至少有一项不同。

请求出满足以上两个条件的叠法的种数，对 $998244353$ 取模。

## 样例 #1

### 输入

```
2
4
1 2 3 4
8
1 1 2 3 4 4 6 7```

### 输出

```
2
4```

# 题解

## 作者：StillEmpty (赞：6)

前言：这破题我whk时放在脑子里想，但是又不是全神贯注的想，想的时候整个人也很不在状态，就这样想了三天想出来了。好像我很弱，一道蓝色的题想了三天，但是我觉得我很强，因为没人教我，我靠自己硬想完全没受到提示自学了计数dp。如果你去看 $\rm Codeforces$ 官方题解你会觉得一帆风顺，但是实际上做题的时候还是会想到大量的错误路线。

------------

我们设偶数块指一个编号为 $i$， 长为 $b_i$，其中 $i$ 为偶数的块。奇数块同理。

我们首先观察一下本题有什么性质：奇数块小于相邻的两个偶数块，然而偶数块是严格上升的，所以只要保证每一个奇数块都小于上面的相邻的一个偶数块就行了。形式化的讲，对于 $i$ 为奇数且 $i \neq 1$，只要保证 $b_i < b_{i-1}$，条件 $1$ 就满足了。

我们接着想，除了最下面的偶数块和最上面的偶数块，每个偶数块都要找一个比他小的数和他配对。最下面的偶数块不用配对。最上面的偶数块要找两个数配对。比如题目中的例子，四个偶数块是 $3$、$4$、$6$、$7$，$3$ 和 $1$、$2$ 配对，$4$ 和 $1$ 配对，$6$ 和 $4$ 配对， 7 不用配对。很显然，$b_n = \max\{a\}$，所以最下面的偶数块就确定了。我们已经把原问题转化为了一个可以用计数dp解决的问题：从 $n-1$ 个数中取出一个长为 $\frac{1}{2}n-1$ 严格上升序列，再给序列中第一个数找出两个比它小的数配对，再给序列中剩余的数每个数找出一个比它小的数配对，问你有几种方案。

虽然可能讲的有点啰嗦，但目前的推导都是十分 $\rm easy$ 的。

但凡你做过一两道 $\rm OI$ 题，你都知道要把 $a$ 排序，将元素的偏序关系转化为序列的前后关系。我们会发现 $a$ 的元素是可以相等的，而作者我根本不知道怎么处理，所以作者认为应该去重，然后记录每个元素出现的次数。作者的代码中， $m$ 就是去掉最下面的偶数块后，去重的元素个数。`cnt[i]` 就是 $\rm rank$ 为 $i$ 的数出现的次数（有点类似于离散化）。这个时候，读者应该是有点思路的。

设 $f_{i, j}$ 是去掉 $\max\{a\}$ 去重后（后面不提这个词，默认如此）前 $j$ 大的数中，取 $i$ 个做偶数块的合法方案数。合法的定义是，不会有奇数块没有比它大的数配对，但是可以有偶数块没用配对上。之所以这么设计dp状态，是因为不是前 $j$ 大的数可以作为奇数块给前 $j$ 大的偶数块配对。第 $j$ 大的数可以有一个作为偶数块，也可以一个都不作为偶数块。前 $j-1$ 大的偶数块部分已经配对好了，但是我们知道没配对好的数量：$i-(pcnt_{j-1}-i)$（$pcnt_j$ 指前 $j$ 大的数的 $cnt$ 之和）。所以dp转移式就是：
$$
f_{i, j} = {i-(pcnt_{j-1}-i) \choose cnt_j}f_{i, j-1} + {(i-1)-[pcnt_{j-1}-(i-1)] \choose cnt_j-1}f_{i-1, j-1}
$$

我们已经快做完了。需要注意的是，最上面的偶数块要找俩奇数块配对。根据做题经验，我们可能是要更改dp状态和转移式。但这个问题要通过改状态转移式解决很烦，作者可能不够聪明，花了很多时间想怎样改状态设计。我们根本没必要这么麻烦，直接枚举最上面的偶数块的 $\rm rank$ 就好了。确定最上面偶数块的 $\rm rank$ 之后，就是个“几个不同颜色的球，每个有若干个，求有多少种排列”的问题。In case of you 实在没看懂，我给个最上面偶数块的 $\rm rank$ = $i$ 时的方案数（作者我代码用的是另一写法，殊途同归）：

$$
\frac{(pcnt_{m}-pcnt_i)!}{\prod_{j=i+1}^{m}cnt_j!}{\frac{1}{2}n-2-[pcnt_{i-1}-(\frac{1}{2}n-2)] \choose cnt_i-1}f_{\frac{1}{2}n-2, i-1}
$$

当然，我们每一步操作都要有紧密的逻辑性，如果你观察一下会发现我们删除 $\max\{a\}$ 时没特判 $\max\{a\}$ 不止一个（这样的话答案显然是 $0$），也没特判 $n = 2$ 时我们上述的一切都不存在。还有你可以发现最后统计答案时可以 $O(n)$，但是作者我用了 $O(n^2)$ 的写法，反正总时间复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef const int& cint;

const int N = 5000, MOD = 998244353;
int n, m;
int a[N+1], cnt[N+1], pcnt[N+1], f[N/2][N+1];
int fac[N+1], inv[N+1], invfac[N+1];

inline int add(cint a, cint b) {
    return (a+b)%MOD;
}
inline int mul(cint a, cint b) {
    return (ll)a*b%MOD;
}
void init() {
    fac[0] = 1;
    for(int i = 1; i <= N; ++i) fac[i] = mul(fac[i-1], i);
    inv[1] = 1;
    for(int i = 2; i <= N; ++i) {
        inv[i] = mul((MOD-MOD/i), inv[MOD%i]);
    }
    invfac[1] = 1;
    for(int i = 2; i <= N; ++i) {
        invfac[i] = mul(invfac[i-1], inv[i]);
    }
}
inline int C(cint n, cint m) {
    if(m < 0 || n < 0 || m > n) return 0;
    if(m == 0 || m == n) return 1;
    return mul(fac[n], mul(invfac[m], invfac[n-m]));
}

void solve() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    sort(a+1, a+n+1, greater<int>());
    if(a[1] == a[2]) {
        printf("0\n"); return;
    }
    if(n == 2) {
        printf("1\n"); return;
    }
    m = 0; memset(cnt, 0, sizeof(cnt)); memset(f, 0, sizeof(f));
    for(int i = 2; i <= n; ++i) {
        if(a[i] != a[i-1]) ++m;
        ++cnt[m];
    }
    for(int i = 1; i <= m; ++i) {
        pcnt[i] = pcnt[i-1]+cnt[i];
    }
    f[0][0] = 1;
    for(int i = 1; i < n/2-1; ++i) {
        for(int j = i; j <= min(i*2, m-1); ++j) {
            f[i][j] = add(mul(C(i-(pcnt[j-1]-i), cnt[j]), f[i][j-1]), mul(C((i-1)-(pcnt[j-1]-(i-1)), cnt[j]-1), f[i-1][j-1]));
        }
    }
    int ans = 0;
    for(int i = n/2-1; pcnt[m]-pcnt[i] >= 2; ++i) {
        int tmp = 1;
        for(int j = i+1; j <= m; ++j) {
            tmp = mul(tmp, C(n/2-(pcnt[i]-(n/2-1))-(pcnt[j-1]-pcnt[i]), cnt[j]));
        }
        ans = add(ans, mul(mul(f[n/2-2][i-1], C(n/2-2-(pcnt[i-1]-(n/2-2)), cnt[i]-1)), tmp));
    }
    printf("%d\n", ans);
}

int main() {
    // freopen("in", "r", stdin);
    int t;
    scanf("%d", &t); init();
    while(t--) solve();
    return 0;
}
```

---

## 作者：_lfxxx_ (赞：2)

upd：补充说明了方程。

来一个和题解区两篇题解不一样的 dp 方法。

首先，两种方案不同当且仅当存在**值**不相同，显然这个是不利于我们 dp 的。一般我们希望两种方案不同当且仅当存在数在原序列的**位置**不同。因此首先我们首先将题目进行一次转换。假如按后面不同的定义算出来的结果为 $ans$，实际上的答案为 $\dfrac{ans}{\prod (cnt_i!)}$，其中 $cnt_i$ 表示 $i$ 出现的次数。

我们按顺序填这个序列，一次填一奇一偶。我们设 $dp_{i,j}$ 表示第 $i$ 个偶数位置（即位置 $2i$）放 $a_j$ 的方案数。那么转移是简单的：（注意 $dp_{1,j}$ 要特殊处理）

$$dp_{i,j}=\sum_{a_k < a_j}dp_{i-1,k} \times \max(0, scnt_{a_k-1} - (2i - 3))$$

其中 $scnt$ 是 $cnt$ 的前缀和数组，$scnt_i$ 即小于等于 $i$ 的数量。注意这里要取 $\max$ 是因为可能后面那是负数（即没有合法的数可以选择）。

可以参考下面这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/oodhu02j.png
)

直接暴力转移是 $O(n^3)$ 的，在 $n \le 5000$ 的范围下不可以接受，我们考虑优化。

由于序列有序，所以可以发现有用的（也就是后面是正数）$k$ 的取值是一段区间，并且这个区间也是有单调性的（随着 $a_j$ 增大，$k$ 能选的就越多）。

因此每次转移之前处理出 $dp_{i-1}$ 乘后面那坨的前缀和即可。

时间复杂度 $O(n ^2)$。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
constexpr int N = 5005, mod = 998244353;
int a[N], dp[N][N], cnt[N], f[N], invf[N], s[N];
inline int qpow(int b, int k)
{
	int res = 1;
	while (k) {
		if (k & 1) res = (ll) res * b % mod;
		b = (ll) b * b % mod;
		k >>= 1;
	}
	return res;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	f[0] = 1;
	for (int i = 1; i <= 5000; ++i) f[i] = (ll) f[i - 1] * i % mod;
	invf[5000] = qpow(f[5000], mod - 2);
	for (int i = 4999; i >= 0; --i) invf[i] = (ll) invf[i + 1] * (i + 1) % mod;
	int T;
	cin >> T;
	while (T--) {
		int n, ans = 0;
		cin >> n;
		for (int i = 1; i <= n; ++i) cnt[i] = 0;
		for (int i = 1; i <= n; ++i) cin >> a[i], ++cnt[a[i]];
		for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
		for (int i = 1; i <= n; ++i) {
			dp[1][i] = cnt[a[i] - 1];
		}
		for (int i = 2; i <= n / 2; ++i) {
			for (int j = 1; j <= n; ++j) {
				s[j] = (s[j - 1] + (ll) dp[i - 1][j] * (cnt[a[j] - 1] - (2 * i - 3))) % mod;
			}
			int l = 1, r = 0;
			for (int j = 1; j <= n; ++j) {
				while (a[r + 1] < a[j]) ++r;
				while (l <= r && cnt[a[l] - 1] < 2 * i - 3) ++l;
				dp[i][j] = (s[r] - s[l - 1]) % mod;
			}
		}
		for (int i = 1; i <= n; ++i) ans = (ans + dp[n / 2][i]) % mod;
		for (int i = 1; i <= n; ++i) ans = (ll) ans * invf[cnt[i] - cnt[i - 1]] % mod;
		cout << (ans + mod) % mod << '\n';
	}
	return 0;
}
```


---

## 作者：RyexAwl (赞：2)

令 $perm$ 为满足以下条件的长度为 $n$ 的排列 $p$ 的个数：

* $a_{p[1]}<a_{p[2]}>a_{p[3]}<a_{p[4]}>.....<a_{p[n]}$

* $a_{p[2]}<a_{p[4]}<a_{p[4]}<....<a_{p[n]}$

令 $cnt[i]$ 表示权值 $i$ 出现的次数，那么答案即为：

$$
\dfrac{perm}{\prod\limits_{i=1}^n(cnt[i])!}
$$

因为 $cnt[i]>1$ 的情况可能会出现相邻的元素相等的情况，所以先考虑一种更简单的情形：$a[]$ 是长度为 $n$ 的排列。

考虑按权值大小从大到小往排列中加入元素，如果 $a_i$ 在排列在偶数位，如果该位置是 $pos$，那么当前排列的 $[1,pos]$ 位都不应该有元素，并且 $pos+1$ 位也不应该有元素。并且 $>pos$ 的所有偶数位置上都应该有元素。

即如果当前将 $a_i$ 加入到排列的偶数位置中，那么其加入到的位置我们是能够唯一确定的：令当前排列中有元素的最靠左的位置为 $pos$，$pos$ 是偶数位置，那么 $a_i$ 只能被加入到位置 $pos-2$。因此我们可以得到一个基础的结论：如果当前存在偶数位置上没有元素，那么最靠左有元素的位置一定是偶数位置。并且只要确定了当前向偶数位置中加入了多少个元素就能够唯一确定该位置。

考虑如果将 $a_i$ 加入到排列的奇数位置中，那么当前与其相邻的偶数位置上都应该有元素。

不难发现，如果我们确定了当前已经有多少个偶数位置已经确定了，即可确定 $a_i$ 能放的位置个数。

因此不难想到一种 DP：令 $f[i,j]$ 表示考虑将 $a[i+1,n]$ 向排列中填，有恰好 $j$ 个元素填到偶数位置上的合法方案数。

接下来考虑有重复权值的情况。

不难发现若 $cnt[i]>1$，那么其实至多有一个 $i$ 能够往偶数位置上填。

令 $get(j)$ 表示如果有恰好 $j$ 个偶数位置上有元素，有多少个奇数位置可以填数，$sum[i]$ 表示 $cnt[i]$ 的后缀和。

因此不难写出转移方程：

$$
f[i-1,j+1]\gets cnt[i-1]\times f[i,j]\times \prod_{k=1}^{cnt[i]-1}(get(j)-(sum[i]-j+k-1))
$$

$$
f[i-1,j]\gets f[i,j]\times \prod_{k=1}^{cnt[i]}(get(j)-(sum[i]-j+k-1))
$$



---

## 作者：Wei_Han (赞：1)

好题。

回家路上想了半天，感觉差不多真了，回来一写发现看反题了。

由于答案序列状态与原序列无关，我们不妨将 dp 放到值域上来做，考虑设 $f_{i,k}$ 表示到 $i$，已经放了 $k$ 个双层了，我们将一对 $a_i < a_{i+1}$ 称为一层，记 $p_i$ 表示 $i$ 的个数，$s_i$ 表示 $\sum \limits_{j=1}^i p_i$，枚举 $j$ 表示上一个放双层的值，那么有 $f_{i,k} = \sum \limits_{j=1}^{i-1} f_{j,k-1} \times (s_{a_j-1} - 2(k-1)+1)\times p_i$，系数中间部分即去掉 $\leq a_j$ 又加回来上一个选的 $a_j$ 的选择，所以系数指 $<a_j$ 之前还未被选择的位置，再乘上这一块数字的选择方案。

朴素转移是 $O(n^3)$ 的，前缀和优化可以做到 $O(n^2)$，注意最后方案数的去重，即把所有 $p_i$ 带来的重复方案除掉。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define pr putchar('\n')
#define fi first
#define se second
#define pp putchar(' ')
#define pii pair<ll,ll>
#define pdi pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(register ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(register ll i = a ; i >= b ; -- i )
#define pb push_back
//#pragma GCC optimize(2)
using namespace std;
//typedef int ll;
typedef long long ll;
//typedef __int128 ll;
typedef double db;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
const ll N=5005,M=2e4+5,mod=998244353;
ll n,a[N],f[N][N],pre[N],cnt[N],sum[N],fac[N];
inline ll qpow(ll a,ll b){return (!b?1ll:qpow(a*a%mod,b>>1)*((b&1)?a:1ll))%mod;}
inline void solve()
{
	read(n);fo(1,i,n) read(a[i]),cnt[a[i]]++;
	ll las=0;sort(a+1,a+1+n);ll m=unique(a+1,a+1+n)-a-1;
	fo(1,i,n) sum[i]=sum[i-1]+cnt[i];
	fo(2,i,m)
	{
		f[i][1]=sum[a[i]-1]*cnt[a[i]];
		fo(2,k,n) f[i][k]=pre[k-1]*cnt[a[i]]%mod;
		fo(1,k,n) pre[k]=(pre[k]+f[i][k]*(sum[a[i]-1]-2*k+1)%mod)%mod;
	}
	fo(1,i,n) if(cnt[i]>0) f[m][n/2]=f[m][n/2]*qpow(fac[cnt[i]],mod-2)%mod;
	wr(f[m][n/2]),pr;
	fo(0,i,n+1) fo(0,j,n+1) f[i][j]=a[i]=pre[i]=cnt[i]=0;
}
signed main(){
	fac[0]=1;fo(1,i,N-5) fac[i]=fac[i-1]*i%mod;
	ll tt;read(tt);while(tt--){solve();}
	return 0;
}


``````

---

## 作者：piggy123 (赞：0)

CF难度 $2200$ 的计数，做了好久，太菜了。

做完发现题解区没有这种做法，来水一发。

考虑 DP，$dp_{i,j}$ 表示前 $i$ 个数，组合了 $2j$ 层的方案数，即选择了 $j$ 个块作为偶数层。我们枚举上一个偶数层，设为 $k$ ，很显然这里就需要 $dp_{k,j-1}\times ???\to dp_{i,j}$ 。

我们来确定系数，即夹在两个偶数层中间的奇数层的方案数：

1. 中间的奇数层必须 $\lt a_k$。
2. 中间的奇数层必须没有用过。

由此，我们令 $\leq i$ 的数的个数为 $tot_i$ ，前面用过的数的个数显然为 $2\times(j-1)-1$ ，所以系数即为 $tot_{a_k-1}-2\times(j-1)+1$ 。注意还要乘上当前这个偶数层的方案数，令 $=a_i$ 的数有 $cnt_{a_i}$ 个，即乘上 $cnt_{a_i}$ 。

然后写一下 $\Theta(n^3)$ 的代码，发现样例过不去。因为题目要求本质不同，所以每种数出现顺序无关，依次除以 $cnt_i$ 即可。

然后考虑怎么做，转移式子显然可以前缀和优化，就 $\Theta(n^2)$ 了。

记得多测清空要彻底，不然爆零退役寄。

Code：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;


ll a[5005],cnt[5005],tot[5005],fac[5005],dp[5005][5005],sm[5005],mod=998244353;

ll qkp(ll a,ll k){
	ll ans=1;
	while (k){
		if (k&1)ans*=a,ans%=mod;
		a*=a,a%=mod;
		k>>=1;
	}
	return ans;
}

int main(){
	ll t;
	cin >> t;
	while (t--){
		ll m;
		cin >> m;
		for (ll i=1;i<=m;i++){
			cin >> a[i];
			cnt[a[i]]++;
		}
		ll n=unique(a+1,a+1+m)-a-1;
		for (ll i=1;i<=m;i++)tot[i]=cnt[i]+tot[i-1];
		for (ll i=1;i<=n;i++){
			dp[i][1]=tot[a[i]-1]*cnt[a[i]]%mod;
			for(ll j=2;j<=m;j++){
				dp[i][j]+=sm[j-1]*cnt[a[i]]%mod;
				dp[i][j]%=mod;
			}
			for (ll j=1;j<=m;j++){
				sm[j]+=dp[i][j]*(tot[a[i]-1]-j*2+1)%mod;
				sm[j]%=mod;
			}
		}
		ll ans=dp[n][m/2];
		fac[0]=1;
		for (ll i=1;i<=m;i++)fac[i]=fac[i-1]*i%mod;
		
		for (ll i=1;i<=m;i++){
			ans*=qkp(fac[cnt[i]],mod-2);
			ans%=mod;
		}
		cout<<ans<< endl;
		
		for (ll i=1;i<=n;i++){
			for (ll j=1;j<=m;j++){
				dp[i][j]=sm[j]=cnt[j]=0;
			}
		}
	} 
	return 0;
}
```


---

