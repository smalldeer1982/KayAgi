# [ABC358E] Alphabet Tiles

## 题目描述

> AtCoder Land 公司出售写有英文字母的瓷砖。高桥想把这些瓷砖排成一排，做成一个铭牌。

求长度在 $1$ 和 $K$ （包括 $1$ 和 $K$ ）之间的由大写英文字母组成的字符串中，满足以下条件的字符串的个数（对 $998244353$ 取模）：

- 对于满足 $1 \leq i \leq 26$ 的每个整数 $i$ ，下面的条件成立：
    - 设 $a_i$ 是按词典顺序排列的 $i$ 个大写英文字母。例如， $a_1 = $ `A`, $a_5 = $ `E`, $a_{26} = $ `Z`.
    - 字符串中 $a_i$ 的出现次数介于 $0$ 和 $C_i$ 之间（包括首尾两次）。

## 说明/提示

- $1 \leq K \leq 1000$
- $0 \leq C_i \leq 1000$
- 所有输入值均为整数。

## 样例解释1

对于第一个样例，满足条件的 $10$ 个字符串是 `A`, `B`, `C`, `AA`, `AB`, `AC`, `BA`, `BC`, `CA`, `CB`。

## 样例 #1

### 输入

```
2
2 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0```

### 输出

```
10```

## 样例 #2

### 输入

```
358
1 0 1 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0```

### 输出

```
64```

## 样例 #3

### 输入

```
1000
1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000```

### 输出

```
270274035```

# 题解

## 作者：zrl123456 (赞：12)

[[ABC358E] Alphabet Tiles](https://www.luogu.com.cn/problem/AT_abc358_e)     

题目考察：组合数学，动态规划。   
题目简述：   
给你一个数 $k$ 和一个序列 $\{c_{26}\}$，求满足以下条件的字符串的个数对 $998244353$ 取模的结果：
- $1\le |s|\le k$。   
- 设一序列 $\{p_{26}\}$ 的 $p_i$ 为在大写字母中第 $i$ 组字母，如 $p_1$ 为 A，$p_5$ 为 E 等，则 $\displaystyle \forall i\in[1,26],\sum_{j=1}^{|s|}[s_j=p_i]\le c_i$。   
数据范围：
- $1\le k\le 10^3$    
- $\forall i\in[1,26],0\le c_i\le 10^3$   
------------
我们设 $m=26$，则若直接暴力枚举，则复杂度为 $\Theta(m^k)$，根本无法接受。     

考虑 dp。   
我们设 $f_{i,j}$（$\displaystyle 1\le i\le 26,1\le j\le \min(k,\sum_{s=1}^{26}c_s)$）为在前 $i$ 组字母中选出 $j$ 个字母组成字符串的方案数对 $998244353$ 取模的结果，他可以由 $f_{i-1,l}$（$\max(0,j-c_i)\le l\le j$）转移而来，但是是如何转移的呢？    
我们的这个长度为 $j$ 的字符串 $s$ 的第 $x$ 位（$1\le x\le j$）可以分配给前 $i-1$ 组字母其中的一组，也可以分配给第 $i$ 组，由于必须分配给前 $i-1$ 组字母 $l$ 位，则分配的方式有 $\displaystyle\binom{j}{l}$ 种，由于前 $i-1$ 组字母还可以有 $f_{i-1,l}$ 种排列，那么我们就得到了状态转移方程：   
$$f_{i,j}=\sum_{l=j-c_i}^jf_{i-1,l}\times\binom{j}{l}$$
我们可以先预处理 $\displaystyle\binom{i}{j}$（$0\le i\le k,0\le j\le i$）：
$$\binom{i}{j}=\binom{i-1}{j}+\binom{i-1}{j-1}$$
再进行 dp。   

由于 $f_{i,j}$ 只与 $f_{i-1,l}$ 有关，所以我们可以将第一维压掉。     

总体复杂度为 $\Theta(mk^2)$，$mk^2\le 2.6\times 10^7$，可以接受。  

代码：
```cpp
#include<bits/stdc++.h>
#define inl inline
#define reg register
#define int long long
#define fst ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define rep(i,x,y) for(reg int i=x;i<=y;++i) 
#define per(i,x,y) for(reg int i=x;i>=y;--i)
#define endl '\n'
#define INF 1e16
#define pb push_back
#define fi first
#define se second
#define lcm(x,y) x/__gcd(x,y)*y
#define ull unsigned long long
using namespace std;
const int N=1005,M=35,MOD=998244353;
int c[M],f[N],dp[N][N];
signed main(){
	fst;
	reg int n,ans=0,ret=0;
	cin>>n;
	rep(i,1,26){
		cin>>c[i];
		ret+=c[i];
	}
	n=min(n,ret);
	f[0]=dp[1][1]=1;
	rep(i,2,n+1)
		rep(j,1,i) dp[i][j]=(dp[i-1][j]+dp[i-1][j-1])%MOD;
	rep(i,1,26)
		per(j,n,1)
			rep(k,max(0ll,j-c[i]),j-1) (f[j]+=f[k]*dp[j+1][k+1]%MOD)%=MOD;
	rep(i,1,n) (ans+=f[i])%=MOD;
	cout<<ans;
	return 0;
} 
```

---

## 作者：Milthm (赞：7)

diff：$1397$。

神奇 dp 题。

____

看到这个题，让计数，计数的题大多都是数学题和 dp 题，那我们往 dp 方面想。

设 $dp_{i,j}$ 表示前 $i$ 个字母组成长度为 $j$ 的字符串的方案数，可以得出转移方程：

$$dp_{i+1,j}=\sum_{k=0}^{\min(j,c_{i+1})}C_j^k\times dp_{i,j-k}$$

组合数可以通过杨辉三角预处理求得，时间复杂度 $O(\alpha k^2)$，其中 $\alpha$ 是字母表大小，为 $26$。

```cpp
#include<bits/stdc++.h>
#define N 1005
#define int long long
using namespace std;
const int mod=998244353;
int C[N][N],k,c[N],dp[N][N],ans;
signed main(){
	C[0][0]=1;
	for(int i=1;i<N;++i){
		C[i][0]=1;
		for(int j=1;j<=i;++j){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		}
	}
	cin>>k;
	for(int i=1;i<=26;++i)cin>>c[i];
	dp[0][0]=1;
	for(int i=0;i<26;++i){
		for(int j=0;j<=k;++j){
			for(int l=0;l<=min(j,c[i+1]);++l){
				dp[i+1][j]=(dp[i+1][j]+dp[i][j-l]*C[j][l])%mod;
			}
		}
	}
	for(int i=1;i<=k;++i)ans=(ans+dp[26][i])%mod;
	cout<<ans; 
	return 0;
}

```

---

## 作者：_determination_ (赞：4)

显然有一个简单 dp。

设 $f_{i,j}$ 表示 dp 到了第 $i$ 个字符，字符串长度为 $j$ 的方案数。

这样 dp 出来的结果显然是不对的，因为最后 dp 出的字符串的字母都是升序的，所以要乘上一个 $j!$。

这样也是不对的，因为如果有重复字符的话，假如重复出现了 $k$ 次，那么答案要除以 $k!$。这个除法的过程就在转移的时候做就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
#define endl '\n'
#define debug cout << "114514" << endl
int n;
int c[30];
int f[1010][1010];
const int mod=998244353;
int jc[1010],invj[1010];
int fp(int x,int p)
{
    int ans=1;
    while(p)
    {
        if(p&1)ans=ans*x%mod;
        x=x*x%mod;
        p>>=1;
    }
    return ans;
}
int inv(int x){return fp(x,mod-2);}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin >> n;
    for ( int i = 1 ; i <= 26 ; i++ )
    {
        cin >> c[i];
    }
    jc[0]=1;
    invj[0]=1;
    for ( int i = 1 ; i <= n ; i++ )
    {
        jc[i]=jc[i-1]*i%mod;
        invj[i]=inv(jc[i]);
    }
    f[0][0]=1;
    for ( int i = 1 ; i <= 26 ; i++ )
    {
        for ( int j = 0 ; j <= n ; j++ )
        {
            for ( int k = 0 ; k <= min(c[i],j) ; k++ )
            {
                f[i][j]+=f[i-1][j-k]*invj[k]%mod;
                f[i][j]%=mod;
            }
        }
    }
    int ans=0;
    for ( int i = 1 ; i <= n ; i++ )
    {
        ans+=f[26][i]*jc[i]%mod;
        ans%=mod;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：SpringFullGarden (赞：4)

双倍经验 AT_abc234_f。

## 题意 

给定字符串最大长度和每个字母最多出现的个数，求能组成的不同的字符串个数。

## 思路

考虑 dp。

$dp_{i, j}$ 表示只用前 $i$ 个字母，长度 $j$ 的字符串个数。

那么 $dp_{i, j}$ 就可以从只用前 $i - 1$ 个字母，长度为 $j - k$ 的状态，即 $dp_{i - 1, j - k}$ 转移过来。在长度为 $j$ 的情况下，把 $k$ 个字母放进字符串的方案数是 $C_j^k$。所以 $dp_{i, j} = \sum \limits_{k = 0} ^ {min(c_i, j)} dp_{i - 1,j - k} \times C_j^k% mod$。

最终答案是 $\sum \limits_{i = 1}^n dp_{26, i}$。

## 代码

```cpp
ll a[30], dp[30][1005], fac[100005], inv[100005];

ll pw(ll x, ll y) {
	ll ans = 1;
	while(y) {
		if(y & 1) ans = ans * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ans;
}
ll C(ll x, ll y) {
	return fac[x] * inv[x - y] % mod * inv[y] % mod;
}
signed main() {
    ll n = rd();
	fac[0] = 1;
    for(ll i = 1; i <= 100000; i++) fac[i] = fac[i - 1] * i % mod;
    inv[100000] = pw(fac[100000], mod - 2);
    for(ll i = 99999; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % mod;

    for(ll i = 1; i <= 26; i++) a[i] = rd();

	dp[0][0] = 1;
	for(ll j = 0; j <= n; j++)
		for(ll i = 1; i <= 26; i++)
			for(ll k = 0; k <= min(j, a[i]); k++)
				dp[i][j] = (dp[i][j] + dp[i - 1][j - k] * C(j, k) % mod) % mod;

	ll ans = 0;
	for(ll i = 1; i <= n; i++) ans = (ans + dp[26][i]) % mod;
	cout << ans;
	return 0;
}

```

---

## 作者：Xuan_qwq (赞：4)

### 题面大意
有 $26$ 个字母，第 $i$ 个字母有 $c_i$ 个以供选择，从中选取 $n$ 个字母排成一列，相同的字母互换位置记为同一种方法。求方法数。

### 思路
我们设 $f_{i,j}$ 为使用了前 $i$ 个字母，得到的排列长度为 $j$ 的方法数，初始条件为 $f_{0,0}=1$。

假设我们已知字母 $1$ 到 $i-1$ 所能得到的 $f_{i-1,j}$，考虑字母 $i$。

如果我们要由一个长度为 $k$ 的排列通过插入若干个个字母 $i$，得到一个长度为 $j$ 的排列，那么由插板法，我们可以知道插入方法数为 $C_j^{j-k}$。

所以转移式为：
$$f_{i,j}=f_{i-1,j}+f_{i-1,k}\times C_j^{j-k}$$

直接按照这个转移式转移即可，记得取模。

### Code

下标从 $0$ 开始，所以循环可能有点迷惑致歉。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//方便一点就直接全开long long了
const int mod=998244353;
int n;
int a[26];
int f[1005],fac[1005],inv[1005];
//可以倒序循环把f的第一维去掉
int ksm(int a,int q){
	int res=1;
	while(q){
		if(q&1)res=res*a%mod;
		a=a*a%mod;
		q>>=1; 
	}
	return res;
}
void init(){//预处理组合数
	fac[0]=fac[1]=inv[1]=inv[0]=1;
	for(int i=2;i<=1002;i++)fac[i]=fac[i-1]*i%mod;
	inv[1002]=ksm(fac[1002],mod-2);
	for(int i=1001;i>1;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int n,int m){//求组合数
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
	cin>>n;
	init();
	for(int i=0;i<26;i++)cin>>a[i];
	for(int i=0;i<=min(n,a[0]);i++)f[i]=1;//直接把第一个字母的处理去掉了
	
	
	for(int i=1;i<26;i++){//到第i个字母
		for(int j=n;j>=1;j--){//当前序列长为j 
			for(int k=max(0ll,j-a[i]);k<j;k++){//原序列长为k(这里循环是倒着的，可以把f的第一维去掉) 
				f[j]=(f[j]+f[k]*C(j,j-k)%mod)%mod;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)ans=(ans+f[i])%mod;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：PineappleSummer (赞：3)

[[ABC358E] Alphabet Tiles](https://www.luogu.com.cn/problem/AT_abc358_e)

分享一种赛时比较复杂的做法。

令 $f_i$ 表示长度为 $i$ 的字符串的方案数。那么我们考虑已知 $f_i$，如何求 $f_{i+k}$。

假设现在有 $2$ 个 `a`，$1$ 个 $b$，那么 $f_3=\dfrac{A_3^3}{A_2^2\times A_1^1}$。如果再加 $2$ 个 `c`，得到 $f_5=\dfrac{A_5^5}{A_2^2\times A_1^1\times A_2^2}=f_3\times \dfrac{A_5^5}{A_3^3\times A_2^2}$。

那么就得到了 $f_{i+k}=f_i\times \dfrac{A_{i+k}^{i+k}}{A_i^i\times A_k^k}=f_i\times \dfrac{(i+k)!}{i!\times k!}$。

为了更加高效，$\dfrac{(i+k)!}{i!\times k!}$ 可以 $O(n^2\log n)$ 进行预处理，使调用时复杂度为 $O(1)$ 的。

预处理（$x_{i,k}$ 处理后就为 $\dfrac{(i+k)!}{i!\times k!}$）：
```cpp
bs[0] = 1; f[0] = 1;
for (int i = 1; i <= n; i++) bs[i] = mul (bs[i - 1], i); // 预处理阶乘
for (int i = 0; i <= n; i++)
	for (int j = 0; j <= n - i; j++)
		x[i][j] = mul (mul (bs[i + j], inv (bs[i])), inv (bs[j]));
```

初始 $f_0$ 为 $1$。

转移：
```cpp
for (int j = 1; j <= 26; j++) { // 枚举字母
		for (int i = n; i >= 1; i--) { // 一共选 i 个
			for (int k = min (i, c[j]); k >= 1; k--) // 第 j 个字母选 k 个
				f[i] = add (f[i], mul (f[i - k], x[i - k][k])); // 转移
		}
	}
```
设 $n,c_i$ 同阶，时间复杂度为 $O(26n^2)$。

[完整代码](https://atcoder.jp/contests/abc358/submissions/54625680)

---

## 作者：TernaryTree (赞：2)

看到这样的计数形式啪一下就想到生成函数来做。考虑对于长度 $i$，答案为

$$\sum_{j_0+j_1+\dots+j_{25}=i}\dfrac{i!}{j_0!j_1!\dots j_{25}!}[j_0\le C_0][j_1\le C_1]\dots [j_{25}\le C_{25}]$$

于是一个字符的 GF 是显然的，即

$$F_i(x)=\sum_{j=0}^{C_i}\dfrac1{j!}$$

然后我们分治地把 $26$ 个多项式乘起来得到 $G(x)$，求出 $\sum_{i=1}^k i![x^i]G(x)$ 即可。

```cpp
// 省略多项式板子

int k;
int c[26];
int f[200][maxn], cnt = 25;

int solve(int l, int r) {
	if (l == r) return l;
	int x = solve(l, mid);
	int y = solve(mid + 1, r);
	++cnt;
	Mul(f[x], f[y], f[cnt], 1001 * (mid - l + 1), 1001 * (r - mid));
	return cnt;
}

void fake_main() {
	k = read(); 
	rep(i, 0, 25) {
		c[i] = read();
		rep(j, 0, c[i]) f[i][j] = ifac[j];
	}
	int p = solve(0, 25);
	int ans = 0;
	rep(i, 1, k) (ans += f[p][i] * fac[i] % mod) %= mod;
	write(ans);
}
```

---

## 作者：zhlzt (赞：2)

### 题解

一道简单的 DP 题，应该不难想到状态转移方程。

设 $dp_{i,j}$ 表示用前 $i$ 个字母组成满足条件的长度为 $j$ 的字符串的方案数，那么显然有如下状态转移方程：

$$dp_{i,j}=\sum_{k=0}^{\min\{j,cnt_i\}}\left(dp_{i-1,j-k}\times\dbinom{j}{k}\right)$$

组合数其实完全可以杨辉三角计算，可赛时我把数据范围看大了，结果用了组合数公式加乘法逆元……

代码复杂度为 $O(n^2v)$，其中 $v=26$。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxv=26;
const int maxn=1e3;
const int mod=998244353;
int dp[maxv+10][maxn+10],cnt[maxn];
int fac[maxn+10],inv[maxn+10];
int qkpow(int a,int p){
	int ans=1; 
	while(p){
		if(p&1) ans=1ll*ans*a%mod;
		a=1ll*a*a%mod; p>>=1;
	}
	return ans;
}
inline int combine(int n,int m){
	return 1ll*fac[n]*inv[n-m]%mod*inv[m]%mod;
}
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<=maxv;i++) scanf("%d",cnt+i);
	memset(dp,0,sizeof dp); 
	dp[0][0]=1; fac[0]=1; 
	for(int i=1;i<=maxn;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[maxn]=qkpow(fac[maxn],mod-2);
	for(int i=maxn;i>=1;i--) inv[i-1]=1ll*inv[i]*i%mod;
	int ans=0;
	for(int i=1;i<=maxv;i++){
		for(int j=0;j<=n;j++){
			for(int k=0;k<=min(j,cnt[i]);k++){
				int temp=dp[i-1][j-k];
				dp[i][j]=(dp[i][j]+1ll*combine(j,k)*temp%mod)%mod;
			}
		}
	}
	for(int i=1;i<=n;i++) (ans+=dp[maxv][i])%=mod; 
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Starrykiller (赞：1)

poly 大法好。

考虑枚举字符串长度 $l$，那么长度为 $l$ 的方案就是

$$
\sum_{\sum a_i=l} {l\choose a_1,a_2,\cdots,a_{26}}
$$

当然要满足 $a_i\le c_i$。注意到这是一个很显然的 EGF 卷积的形式。

具体地说，设 $\displaystyle F_i(x)=\sum_{0\le x\le c_i}\frac{x^i}{i!}$，把 $26$ 个 $F_i(x)$ 卷起来记为 $F(x)$，$\displaystyle \left[\frac{x^i}{i!}\right]F(x)$ 就是长度为 $i$ 时的答案。

顺便提一下 DP 做法。就是套路地设状态 $f(i,j)$ 为当前考虑到第 $i$ 个字符，字符串长度为 $j$ 的方案数。转移就是枚举当前字符选 $l$ 个，然后必然要从 $(j+l)$ 个位置中选 $l$ 个来放。据说大家都是从 DP 推 GF 的，怎么回事呢/yun

时间复杂度 $\Theta(|\Sigma| n\log n)$。非常好写。[代码](https://atcoder.jp/contests/abc358/submissions/54572396)。

---

## 作者：wly09 (赞：1)

纯组合或 dp 估计能做，但是生成函数挺方便的。

## 前置知识：生成函数

序列 $a$ 的普通生成函数定义为：

$$F(x)=\sum_{n}a_nx^n$$

换句话说，如果序列 $a$ 有通项公式，那么它的普通生成函数的系数就是通项公式。

例如：序列 $a=\langle1,2,3\rangle $ 的生成函数为 $F(x)=1+2x+3x^2$。

### 基本运算

#### 加减法

因为

$$F(x)\pm G(x)=\sum_{n}(a_n\pm b_n)x_n$$

因此 $F(x)\pm G(x)$ 是 $\langle a_n+b_n\rangle$ 的生成函数。

#### 乘法（卷积）

因为

$$F(x)G(x)=\sum_{n}x_n\sum_{i=0}^{n}a_ib_{n-i}$$

所以 $F(x)G(x)$ 是 $\langle\sum_{i=0}^{n}a_ib_{n-i}\rangle$ 的生成函数。

## 本题思路

先不考虑顺序，对于一种字母，我们设 $a_n$ 是选 $n$ 个这种字母的方案数，并写出其生成函数。可以发现，选两种字母共 $n$ 个的生成函数就是他们生成函数的卷积（请读者自证）。

类似地，选 $m$ 个字母就是这些所有生成函数的卷积。

再考虑变成排列，只需要知道可重集的排列数公式：

$$\dfrac{n!}{n_1!n_2!\cdots n_k!}$$

我们可以将一种字母生成函数的定义改为 $a_n=\dfrac{1}{n!}(n\le c_i)$，假设所有生成函数的卷积为 $G(x)=\sum_{n}b_nx_n$，最终的答案数就是 $\sum_{i=1}^{k}i!\cdot b_i$。

考虑到数据范围，本题的卷积 $O(n^2)$ 暴力即可。

upd：这玩意好像是指数生成函数？~~我只学了普通生成函数~~

[AC 记录](https://atcoder.jp/contests/abc358/submissions/54625170)

---

## 作者：ZhongYuLin (赞：0)

动态规划。

设：$f_{i,j}$ 表示考虑到前 $i$ 位，可以组成 $f_{i,j}$ 个长度为 $j$ 的字符串。发现前面的方案的具体形式与当前位无关，具有良好的无后效性。我们便可以枚举当前字母使用几个，再枚举从哪种长度来进行转移。这个方案数等价于 $n$ 个无标号球放入 $m$ 个有标号盒子中（可以为空）的方案数，非常经典，于是可以进行转移。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e3+3,P=998244353;
ll f[N][N],a[N],fc[N],inv[N];
int n=26,K;
ll fp(ll a,ll b=P-2){ll ans=1;for(;b;b>>=1,a=a*a%P)if(b&1)ans=ans*a%P;return ans;}
ll C(ll n,ll m){if(n<m)return 0;return fc[n]*inv[m]%P*inv[n-m]%P;}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    fc[0]=1;
    for(int i=1;i<N;++i)fc[i]=fc[i-1]*i%P;
    inv[N-1]=fp(fc[N-1]);
    for(int i=N-2;~i;--i)inv[i]=inv[i+1]*(i+1)%P;
    cin>>K;
    f[0][0]=1;
    for(int i=1;i<=n;++i)cin>>a[i];
    for(int i=1;i<=n;++i)
        for(int j=0;j<=a[i];++j)
            for(int k=K;k>=j;--k)
                f[i][k]=(f[i][k]+f[i-1][k-j]*C(k,j)%P)%P;
    int ans=0;
    for(int i=1;i<=K;++i)ans=(ans+f[n][i])%P;
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：incra (赞：0)

### Solution
考虑 DP，设 $f_{i,j}$ 表示用前 $i$ 个字符组成长度为 $j$ 的字符串的方案数。

考虑 $f_{i-1,j-k}(0\le k \le \min\{j,c_i\})$ 对 $f_{i,j}$ 有多少贡献。

考虑把 $k$ 个字符 $i$ 插入之前长度为 $k$ 的字符串中，一共有 $j - k + 1$ 个空位，要插入 $k$ 个字符，所以对 $f_{i,j}$ 的贡献即为 $f_{i-1,j-k}\times C_{k + j - k + 1 - 1,j - k + 1 - 1}$，最后一个式子不懂建议查询插板法并手推一遍。

初始状态：$f_{0,0}=1$。

目标状态：$\displaystyle\sum_{i=1}^{n}f_{26,n}$。
### Code
```cpp
#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
#define puts(s) cout << s << endl
#define IOS ios :: sync_with_stdio (false),cin.tie (0),cout.tie (0)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
int fastio = (IOS,0);
const int N = 2010,M = 30,MOD = 998244353;
int n;
int c[M];
LL f[M][N];
LL C[N][N];
LL get (int n,int m) {
	return C[n + m - 1][m - 1];
}
int main () {
	for (int i = 0;i < N;i++) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1;j < i;j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
	}
	cin >> n;
	for (int i = 1;i <= 26;i++) cin >> c[i];
	f[0][0] = 1;
	for (int i = 1;i <= 26;i++) {
		for (int j = 0;j <= n;j++) {
			for (int k = 0;k <= min (j,c[i]);k++) f[i][j] = (f[i][j] + f[i - 1][j - k] * get (k,j - k + 1) % MOD) % MOD;
		}
	}
	LL ans = 0;
	for (int i = 1;i <= n;i++) ans = (ans + f[26][i]) % MOD;
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Wei_Han (赞：0)

考虑 dp，注意到 $C_i\leq10^3$，直接记录状态不可取。但是 $K\leq10^3$ 也就是说总的字符个数很少，字符会剩余很多，从这里入手。设计 $f_{i,j}$ 表示前 $i$ 种字符，填充到 $j$ 位置的方案数，进一步考虑转移。

首先肯定要枚举 $i$ 和 $j$，然后我们还需要知道当前字符 $C_i$ 填充了多少个，换句话讲，也就是前 $i-1$ 个字符填充到哪，这个再用 $p$ 表示，那么此时插入第 $i$ 种字符的数量就为 $j-p$，这些字符可以插入到前 $p$ 个字符之间。考虑组合计数，假如现在有 $n$ 相同的小球，$m$ 个不同的盒子，那么总方案数就有 $\left (_{n+m-1}^{m-1} \right )$ 种，对应到本题中，也就是令 $m=j-p+1$，$n=p$，也就是 $\left (_{j}^{j-p}\right )$ 种方案，转移就为

$$f_{i,j}=f_{i,j}+f_{i-1,p}\times \left (_{j}^{j-p}  \right )$$

统计答案时枚举长度即可。

注意取模和预处理组合数，时间复杂度 $O(26k^2)$。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define pr printf("\n")
#define pp printf(" ")
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(ll i = a ; i >= b ; -- i )
#define bug (x>=1&&x<=n&&y>=1&&y<=m) 
using namespace std;
typedef long long ll;
typedef __int128 i128;
typedef double db;
const int N=1e6+5,M=1e7+5;
const db eps=1e-7;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
ll k,cc[N],mod=998244353,dp[27][N],pre[N],inv[N];
inline ll qpow(ll a,ll b){if(!b) return 1;ll ans=1;while(b){if(b&1) ans=ans*a%mod;a=a*a%mod;b>>=1;}return ans;}
inline void init(){pre[0]=1;fo(1,i,5000) pre[i]=pre[i-1]*i%mod;inv[5000]=qpow(pre[5000],mod-2);Fo(4999,i,0) inv[i]=inv[i+1]*(i+1)%mod;}
inline ll C(ll n,ll m){
	if(n<m) return 0;
	return pre[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
	string tt;cin>>tt;fo(0,i,tt.size()-1) cc[tt[i]-'a'+1]++;
	k=tt.size();fo(1,i,26) pre[i]=pre[i-1]+cc[i];init();dp[0][0]=1;
	fo(1,i,26) fo(0,j,k) Fo(j,p,max(0ll,j-cc[i]))
		dp[i][j]=(dp[i][j]+dp[i-1][p]*C(j,j-p))%mod;//C(n+m-1,m-1)
	ll ans=0;
	fo(1,i,k) ans+=dp[26][i]%mod,ans%=mod;
	wr(ans);
	return 0;
}
``````

---

## 作者：Pentiment (赞：0)

想了下生成函数没搞出来，还是自己太菜（

先来考虑最基础的 dp。

设 $f_{i,j}$ 为前 $i$ 个字符拼 $j$ 位的方案数，有：
$$
f_{i,j}=f_{i-1,j}+\sum_{k=1}^{\min(j,c_i)}f_{i-1,j-k}\cdot\binom jk
$$
意思就是指定 $k$ 个字符插到 $j$ 个可能的位置里。

这样就可以直接 $\mathcal O(n^2|\Sigma|)$ 做，其中 $|\Sigma|$ 为字符集大小。

这有点不牛，考虑优化。

设字符 $i$ 选 $x_i\ (x_i\leq c_i)$ 个，则拼成长度 $n$ 的方案数为：
$$
\sum_{\sum x=n}\dfrac{n!}{x_1!x_2!\dots x_{26}!}
$$
那么字符 $i$ 的生成函数为：
$$
f_i(x)=\sum_{j=0}^{c_i}\dfrac{x^j}{j!}
$$
这样就能做到 $\mathcal O(n\log n|\Sigma|)$。

---

## 作者：xixisuper (赞：0)

# AT_abc358_e [ABC358E] Alphabet Tiles 题解

最近刚刚学了生成函数，来写一下题解。

本题解采用指数生成函数解决问题。

## 思路

强烈建议有意向学生成函数的人看看下面这几个视频，绝对对你有帮助。

[普通生成函数](https://www.bilibili.com/video/BV1E24y1171z/?spm_id_from=333.788.recommend_more_video.-1)、[指数生成函数](https://www.bilibili.com/video/BV1BM411C7bU/?spm_id_from=333.337.search-card.all.click)、[生成函数的应用](https://www.bilibili.com/video/BV1fP411g7bm/?spm_id_from=333.999.0.0)。

首先，什么是**生成函数**？

- 生成函数（Generating Function），某个序列 $a$ 的生成函数是一种**形式幂级数**，其每一项的系数可以提供关于这个序列的信息。

根据问题的不同，可以构造不同形式的生成函数。

包括**普通生成函数**、**指数生成函数**、**狄利克雷生成函数**等。

听不懂？没关系，只需要记住每种生成函数能够解决的问题就够了。

我们注意到这一题是要求排列数，而与以往不同的是，**一般的排列数是 $n$ 个数各不相同**，然而这个题却把**元素分成了 $26$ 个种类，每个种类中有多个相同的元素**。

我们把这种类型的排列数问题称作**多重集排列数问题**。

**指数生成函数**就是用来解决该问题的。

### 指数生成函数

其一般形式为：
$$
F(x)=\sum_{n\geq0}a_n\frac{x^n}{n!}
$$

其中，$a_n$ 对应着的是一个数列（可有穷可无穷），所以说我们一般用**某个数列对应的生成函数**来区分不同的生成函数。

我们需要用到指数生成函数的**乘法运算（卷积运算）**，其规律如下所示：

设有，

$$
F(x)=\sum_{n\geq0}a_n\frac{x^n}{n!}\\
G(x)=\sum_{n\geq0}b_n\frac{x^n}{n!}
$$

则，

$$
\begin{aligned}
F(x)\cdot G(x)&=\sum_{i\geq0}a_i\frac{x^i}{i!} \sum_{j\geq0}b_j\frac{x^j}{j!}\\
&=\sum_{n\geq0}x^n\sum_{i=0}^{n}a_ib_{n-i}\frac{1}{i!(n-i)!}\\
&=\sum_{n\geq0}\frac{x^n}{n!}\sum_{i=0}^{n}\frac{n!}{i!(n-i)!}a_ib_{n-i}\\
&=\sum_{n\geq0}\frac{x^n}{n!}\sum_{i=0}^{n}C_n^ia_ib_{n-i}
\end{aligned}
$$

**即数列 $a_n$ 与数列 $b_n$ 对应指数生成函数的乘积，等于数列 $\sum_{i=0}^{n}C_n^ia_ib_{n-i}$ 对应指数生成函数。**

### 多重集排列数问题

**我们设从第 $i$ 个字母中取 $b_i$ 个，令 $m=\sum_{i=1}^{n} b_i$，则对每一组 $b_n$ 对应的排列数为 $\frac{m!}{\prod_{i=1}^n b_i!}$。**

为何？首先我们知道，如果 $m$ 个字母互不相同，则对应的排列数为 $m!$，再把对应的 $b_i!$ 除去，是因为 $m!$ 中包含了 $b_i!$ 种对于第 $i$ 个字母来说相同的情况，根据乘法原理，总共就会有 $\prod_{i=1}^nb_i!$ 种重复的情况，再根据乘法原理除去即可。

### 问题解决

我们设第 $i$ 个字母可用的个数为 $a_i$，构造 $26$ 个指数生成函数，并将他们做卷积运算。

**我们设从第 $i$ 个字母中取 $b_i$ 个，令 $m=\sum_{i=1}^{26} b_i$，则一组 $b_{26}$ 对应的卷积结果为：**

$$
\begin{aligned}
\frac{x^{b_1}}{b_1!}\cdot\frac{x^{b_2}}{b_2!}\cdots\frac{x^{b_{26}}}{b_{26}!}&=\frac{x^m}{\prod_{i=1}^{26}b_i!}\\\\
&=\frac{m!}{\prod_{i=1}^{26}b_i!}\cdot \frac{x^m}{m!}
\end{aligned}
$$

发现盲点了吗？

没错，**对所有指数生成函数做完卷积后，$\frac{x^m}{m!}$ 项前的系数，就是对应着取 $m$ 个字母的多重集排列数**。

所以，我们直接进行对所有指数生成函数暴力进行卷积运算，最后的结果就是 $\frac{x}{1!}$ 到 $\frac{x^K}{K!}$ 每一项的系数和了。

单次暴力卷积运算时间复杂度为 $O(n^2)$，而我们最多进行 $26$ 次卷积运算，时间复杂度绰绰有余。

当然，如果这题的 $K$ 开的再大一点，我们依然可以用 FFT 或 NTT 去优化，不过本题不需要。

## 代码

需要用到快速幂，求组合数，费马小定理求逆元的基础知识，不会的请自行学习。

蒟蒻代码，不喜勿喷。

```cpp
#include <iostream>
#include <cmath> 
#include <algorithm>
#define ll long long
#define dd double 
using namespace std;
const ll MOD=998244353;
ll cnt[100],k;
ll jie[1005];
ll ksm(ll a,ll b){
	ll ret=1;
	while(b){
		if(b&1) ret=ret*a%MOD;
		a=a*a%MOD;
		b>>=1;
	}
	return ret;
}
ll inv[1005];
void init(){
	jie[0]=1;inv[0]=1;
	for(ll i=1;i<=1000;i++){
		jie[i]=jie[i-1]*i%MOD;
		inv[i]=ksm(jie[i],MOD-2);	
	}
}
ll a[1005],b[1005],c[1005];
ll q[100],top;
ll get_C(ll n,ll m){
	ll ret=jie[n]*inv[m]%MOD;
	ret=ret*inv[n-m]%MOD;
	return ret;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	init();
	cin>>k;
	for(ll i=1;i<=26;i++){
		cin>>cnt[i];
		if(cnt[i]>0) q[++top]=i;
	}
	if(top==1){cout<<min(cnt[q[1]],k);return 0;}
	for(ll i=0;i<=cnt[q[1]];i++) a[i]=1;
	for(ll i=2;i<=top;i++){
		for(ll j=0;j<=k;j++){
			b[j]=(j<=cnt[q[i]]?1:0);
		}
		for(ll j=0;j<=k;j++){
			for(ll op=0;op<=j;op++){
				c[j]=(c[j]+get_C(j,op)*a[op]*b[j-op])%MOD;//卷积运算
			}
		}
		for(ll j=0;j<=k;j++) a[j]=c[j],c[j]=0;
	}
	ll ans=0;
	for(ll i=1;i<=k;i++) ans=(ans+a[i])%MOD;
	cout<<ans;
	return 0;
}
```

~~顺便送上双倍经验：[[ABC234F] Reordering](https://www.luogu.com.cn/problem/AT_abc234_f)。~~

---

