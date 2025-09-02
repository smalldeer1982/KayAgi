# [AGC025B] RGB Coloring

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc025/tasks/agc025_b

高橋君はタワーを $ 1 $ つ持っており、それは $ N $ 個のブロックが縦一列に重なって構成されています。 はじめすべてのブロックは無色ですが、高橋君はいくつかのブロックを赤色、緑色、青色のいずれかの色で塗ることで、 タワーを美しくしようとしています。そこで、高橋君は *タワーの美しさ* を以下のように定義することにしました。

- 各ブロックの得点を、赤色に塗られていれば $ A $ 点、緑色に塗られていれば $ A+B $ 点、青色に塗られていれば $ B $ 点、無色ならば $ 0 $ 点として、 $ N $ 個のブロックの得点の合計をタワーの美しさとする。

ただし、$ A,B $ はあらかじめ与えられる正整数の定数であり、各マスが $ 2 $ つ以上の色で同時に塗られることがないことにも注意してください。

高橋君はタワーの美しさがちょうど $ K $ になるようにブロックを塗ろうと考えています。 そのようにタワーを塗る方法は何通りあるでしょうか。 $ 998244353 $ で割った余りを求めてください。 ただし、$ 2 $ つのタワーを塗る方法が異なるとは、あるブロックが存在し、そのブロックに塗られている色が異なること、もしくは、そのブロックが一方では塗られているが、 他方では無色であることを指します。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 3×10^5 $
- $ 1\ ≦\ A,B\ ≦\ 3×10^5 $
- $ 0\ ≦\ K\ ≦\ 18×10^{10} $
- 入力される値は全て整数である

### Sample Explanation 1

この場合、赤色 $ 1 $ つにつき $ 1 $ 点、緑色 $ 1 $ つにつき $ 3 $ 点、青色 $ 1 $ つにつき $ 2 $ 点なので、美しさが $ 5 $ になるのは、 - 緑色 $ 1 $ つ、青色 $ 1 $ つ - 赤色 $ 1 $ つ、青色 $ 2 $ つ - 赤色 $ 2 $ つ、緑色 $ 1 $ つ - 赤色 $ 3 $ つ、青色 $ 1 $ つ のいずれかの場合だけです。よって、求める答えは $ 40 $ になります。

### Sample Explanation 2

美しさが $ 0 $ であるタワーは、すべてのブロックが無色であるものだけです。よって、答えは $ 1 $ になります。

## 样例 #1

### 输入

```
4 1 2 5```

### 输出

```
40```

## 样例 #2

### 输入

```
2 5 6 0```

### 输出

```
1```

## 样例 #3

### 输入

```
90081 33447 90629 6391049189```

### 输出

```
577742975```

# 题解

## 作者：BlankAo (赞：8)

$\Large\natural$ **AT3965 [AGC025B] RGB Coloring** / **[原题链接](https://www.luogu.com.cn/problem/AT3965)** / **[更好阅读体验](https://www.cnblogs.com/BlankAo/p/14004958.html)**

---

### 思路

首先，明显地，我们可以把绿色看成同时涂上红色和蓝色。这样得分仍为 $A+B$。

所以红色和蓝色就独立了，即它们互不影响（转化前是一个格子涂了红色就不能再涂蓝色，不是独立的）。

所以我们依次枚举红色的个数 $i$，这样蓝色的个数就是 $j=\frac{(K-A\times i)}{B}$。

然后用排列组合公式来枚举会有多少种方案。即 $C^i_n*C^j_n$。

因为时间不紧，我用了快速幂求逆元。

### 代码

```c++
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define lon long long
using namespace std;
lon mo=998244353;
lon n,a,b,ned,ans,mul[312345];

lon power(lon p,lon q){
	lon tot=1;
	while(q){
		if(q&1)tot=(tot*p)%mo;
		p=(p*p)%mo;
		q=q>>1;
	}
	return tot;
}

lon inv(lon z){return power(z%mo,mo-2);}

lon Cnm(lon Cn,lon Cm){
	if(Cn<0 || Cn>n || Cm-Cn<0)return 0;
	lon upp=(mul[Cm]*inv(mul[Cm-Cn]))%mo,low=mul[Cn];
	return (upp*inv(low))%mo;
}

int main(){
	cin>>n>>a>>b>>ned;
	mul[0]=1;
	rep(i,1,n)mul[i]=(mul[i-1]*i)%mo;
	rep(i,0,n){
		if(ned-i*a<0)break;
		if((ned-i*a)%b==0)ans=(ans+Cnm(i,n)*Cnm( (ned-i*a)/b ,n)%mo)%mo;
	}
	cout<<ans;
}
```

---

## 作者：Dementor (赞：2)

## 题解 AT3965 【[AGC025B] RGB Coloring】

[AT3965 题面](https://www.luogu.com.cn/problem/AT3965)

这道题非常明显是一道计数题，那么我们来想想怎么运用计数思想。

涂成红色是 $A$ 和涂成蓝色是 $B$ 和涂成绿色是 $A + B$ ，我们想象一下：可不可以把绿色看成涂成红色之后再涂成蓝色，这样的话我们就转换成了两个互相独立的颜色，因为如果一层在考虑涂成红色的时候被涂上了颜色，又在接下来考虑涂成蓝色的时候被涂上了颜色，那么就相当于他被涂上了绿色，代价是一样的：

$$(A) + (B) = (A + B)$$

所以我们就能单独考虑红和蓝了：

看看代码？

code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3000010;
const long long mod = 998244353;
long long n, a, b, k;
long long fac[N + 10], ifac[N + 10];
long long Ans = 0LL;
long long qpow (long long a, long long b) {
	long long ans = 1LL;
	while (b) {
		if (b & 1) ans = ans * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}
long long C (int a, int b) {
	if (b > a || a < 0 || b < 0) return 0; // 这里要注意 b < 0 的情况，反正都是组合数的判断，否则会 RE 的，要在日常训练中注意这种细节
	return fac[a] * ifac[a - b] % mod * ifac[b] % mod;
}
int main () {
	scanf ("%lld %lld %lld %lld", &n, &a, &b, &k);
	fac[0] = 1LL; for (int i=1;i<=n+2;i++) fac[i] = fac[i - 1] * i * 1LL % mod;
	for (int i=0;i<=n+2;i++) ifac[i] = qpow (fac[i], mod - 2);
	for (int i=0;i<=n;i++) {
		if ((k - i * a) % b == 0) { // 这里要注意一下能不能被整除，因为“层”是整数
			Ans = (Ans + C (n, i) * C (n, (k - i * a) / b) % mod) % mod;
		}
	}
	cout << Ans << endl;
}
```

---

## 作者：zimindaada (赞：2)

[AT3965 RGB Coloring 题面](https://www.luogu.com.cn/problem/AT3965)

[博客推销](https://www.luogu.com.cn/blog/zimindaada/#)

这一道题可以做一个很好的排列组合入门题。如果您看不懂乘法逆元，排列组合的预处理，那么建议先自学一下。

这一道题很容易想到$O(n^3)$的基本做法：枚举一遍得分分别为$A$、$B$和$A+B$的个数，在满足他们的得分可行性以后，用排列组合求出每一种涂色个数情况下的所有排列方法，然而这题的数据为$O(n \log n)$以下的，所以要想一些优化

$O(n^2)$：我们可以想到，$A+B$这种得分，很明显可以看成一个格子上同时涂了分数为$A$和$B$的颜色，那么就可以优化掉$A+B$的那个循环。

$O(n)$ : 由于题目要求分数方案始终为$k$，那么我们可以只枚举价值为$A$一种颜色的数量，然后通过$k-i \times A$（$i$为$A$这种颜色的个数），求出$B$在$A$有$i$个的时候，唯一可能的数量，然后就可以通过排列组合做出来了。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
namespace ztd{
    using namespace std;
    typedef long long ll;
    //basic I/O
    template<typename T> inline T read(T& t) {//fast read
        t=0;short f=1;char ch=getchar();double d = 0.1;
        while (ch<'0'||ch>'9') {if (ch=='-') f=-f;ch=getchar();}
        while (ch>='0'&&ch<='9') t=t*10+ch-'0',ch=getchar();
        if(ch=='.'){ch=getchar();while(ch<='9'&&ch>='0') t+=d*(ch^48),d*=0.1,ch=getchar();}
        t*=f;
        return t;
    }
    inline ll ksm(ll x, ll y, ll mod){
        ll ret = 1;
        while(y){if(y & 1) ret = ret * x % mod; y >>= 1; x = x*x%mod;}
        return ret;
    }
    inline ll inv(ll x, ll mod){return ksm(x,mod-2,mod);}
}
using namespace ztd;
using namespace ztd;
const int maxn = 3e5+7;
const int mod = 998244353;
ll n, a, b, k, ans;
ll fact[maxn], finv[maxn];
inline void pre_C(){//组合数的预处理
    fact[0] = fact[1] = 1;
    for(int i = 2; i <= n; ++i) //预处理阶乘
		fact[i] = fact[i-1]*i % mod;
    finv[n] = ksm(fact[n], mod - 2, mod);
    for(int i = n-1; i >= 0; --i) //预处理阶乘的乘法逆元
		finv[i] = finv[i+1]*(i+1) % mod;
}
ll C(int mm,int nn){//组合数
    if(mm < 0 || nn < 0 || mm < nn) return 0;
    return fact[mm] * finv[nn] % mod * finv[mm - nn] % mod;
}
signed main(){
    read(n); read(a); read(b); read(k);
    pre_C();
    for(int i = 0; i <= n; ++i){
    	if((k - (i*a)) % b == 0){
    		ans = (ans + C(n, i) * C(n, (k-i*a)/b)%mod) %mod;
		}
	}
    /*
    C(n, i)代表价值为A的颜色的放法，
    C(n, (k-i*a)/b)代表价值为B的颜色的放法
    由于前面O(n^2)做法的思想，可以不判A和B是否重
    */
	printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Zkl21 (赞：1)

[题目链接](https://www.luogu.com.cn/problem/AT_agc025_b)

集训讲了这道题，于是写个题解巩固一下。

### 思路

题意转化为数学公式，就是在求
$$
\sum_{x=0}^n\sum_{y=0}^n\sum_{z=0}^n\left [ Ax+By+(A+B)z=k\wedge x+y+z\le n\right ] 
$$
如果直接暴力枚举前两种组合，判断 $k-(Ax+By)$ 是否为 $(A+B)$ 的正整数倍，时间复杂度为 $O(n^2)$，无法通过本题。

重新再看看有什么发现，不难看出，这个 $A+B$ 很独特，出题人给定 $A+B$ 一定因其有一些独特之处。考虑从这里切入。

不难发现，其实 $A+B$ 就相当于红蓝两种颜色同时涂在一个格子上，效果叠加而已。因此转化后每一种颜色就可以独立看待，求
$$
\sum_{x=0}^n\sum_{y=0}^n\left[Ax+By=k\right]
$$
这样就简单了，直接枚举 $x$，判断 $k-Ax$ 是否为 $B$ 的正整数倍即可。

线性递推求逆元和阶乘时间复杂度降为 $O(n)$。
如果用费马小定理求逆元，时间复杂度为 $O(n\log n)$，也可以通过本题。

注意开 long long。 

### 代码
```cpp
#include<iostream>
using namespace std;
const int N=3e5+10,mod=998244353;
typedef long long ll;
ll n,a,b,k,res;
ll fac[N],inv[N];
void init()//预处理阶乘和逆元
{
    fac[0]=fac[1]=inv[0]=inv[1]=1;
    for(int i=2;i>=n;i++)
    {
        fac[i]=fac[i-1]*i%mod;
        inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    }
    for(int i=2;i<=n;i++)inv[i]=inv[i]*inv[i-1]%mod;
}
ll C(ll n,ll m)
{
	if(n<m)return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int main()
{
	cin>>n>>a>>b>>k;
    init();
	for(ll i=0;i*a<=k&&i<=n;i++)
		if((k-a*i)%b==0)
			res=(res+C(n,i)*C(n,(k-a*i)/b)%mod)%mod;
	cout<<res;
	return 0;
}
```

~~不要直接 ctrl c 哦。~~

---

## 作者：wth2026 (赞：0)

# 题目大意
你有 $n$ 个格子排成一排，每个格子可以涂成红、蓝、绿或不涂色，得分分别为 $A$，$B$，$A+B$，$0$。求使总得分为 $K$ 的方案数，答案对 $998244353$ 取模。
# 思路
题目看起来眼花缭乱，其实思路很简单。从 $1$ 到 $n$ 枚举 $i$，表示涂多少个红色，将权值增加，然后求是否可以再涂整数个蓝色，使得权值为 $K$。如果可以，答案数就增加 $C_n^i \times C_n^j$。
# AC Code
```cpp
#include <bits/stdc++.h>

#define endl '\n'
#define int long long
#define inf 998244353

#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Os")
#pragma GCC optimize("Ofast")

using namespace std;

int ksm(int a, int b) {
    int ans = 1;

    while (b) {
        if (b & 1) {
            ans *= a;
            ans %= inf;
        }

        a *= a;
        a %= inf;
        b >>= 1;
    }

    return ans;
}

int ans, jc[300005], a, b, n, k;

int C(int _, int __) {
	if (_ < __) {
		return 0;
	}
	
    return jc[_] * ksm(jc[__], inf - 2) % inf * ksm(jc[_ - __], inf - 2) % inf;
}

void init() {
    jc[0] = 1;

    for (int i = 1; i < 300005; ++ i) {
        jc[i] = jc[i - 1] * i % inf;
    }
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    init();
    
    cin >> n >> a >> b >> k;
    
    if (k == 0) {
    	cout << 1;
    	return 0;
    }
    
    if (n * (a + b) < k) {
    	cout << 0;
    	return 0;
    }

    for (int i = 0; i <= n; ++ i) {
    	if (i * a > k) {
    		break;
    	}
		
		if ((k - i * a) % b == 0) {
			int j = (k - i * a) / b;
        	ans += C(n, i) * C(n, j) % inf;
        	ans %= inf;
        }
    }

    cout << ans;
    return 0;
}
```

---

## 作者：max666dong123 (赞：0)

## 题意
你有 $n$ 个格子排成一排，每个格子可以涂成红、蓝、绿或不涂色，得分分别为 $A,B,A + B,0$。求使总得分为 $K$ 的方案数，答案对 $998244353$ 取模。
## 思路
很明显 $K=a\times A+b\times B$，其中 $a$ 和 $b$ 分别为 $A$ 和 $B$ 的数量（$A,B\le n$）。

我们也可以发现 $A$ 和 $B$ 相对独立，不用枚举重叠的部分，将他们随意的放进 $n$ 个格子里，自然就有重叠的颜色了。
![](https://cdn.luogu.com.cn/upload/image_hosting/zv0xccs0.png)

如图，红色的部分即为题面中贡献为 $A+B$ 的绿色。

最终的答案即为 $res=\sum C_{n}^{a}\times C_{n}^{b}$。
## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MOD=998244353;
const int N=9e5+10;
int n,a,b,k;
int f[N];
int A[N];
int c[N]; 
int inv[N];
int qpow(int a,int b){
	if(a==1){
		return 1;
	}
	if(b==1){
		return a;
	}
	if(b==0){
		return 1;
	}
	int res=qpow(a,b/2)%MOD;
	res=res*res%MOD;
	if(b&1){
		res=res*a%MOD;
	}
	return res;
}
int C(int x){
//	ans=A[n];
	int res=A[n]%MOD;
	res=res*qpow(A[n-x],MOD-2)%MOD;
	res=res*qpow(A[x],MOD-2)%MOD;
	return res%MOD;
}
void init(int x){
	A[0]=1;
//	MA[0]=1;
//	s[0]=1;
	inv[0]=1%MOD;
	for(int i=1;i<=x;i++){
		A[i]=A[i-1]*i;
		A[i]%=MOD;
	}
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%lld%lld%lld%lld",&n,&a,&b,&k); 
	init(n*2);
	int res=0;
	if(a<b){
		swap(a,b);
	}
	for(int i=1;i<=n;i++){
		c[i]=C(i);
//		cout<<i<<"\n";
	} 
	c[0]=1;
	for(int x=0;x<=n;x++){
		int ans;
//		cout<<x<<endl;
		int i=x;
		int j=k-i*a;
		if(j%b!=0)continue;
		j/=b;
//		cout<<i<<" "<<j<<endl;
		if(j<0)break;
//		if(i+j>n){
//			my=i+j-n;
//		}  
//		i-=my;
		if(i>n||j>n){
			continue;
		}
		
		if(i*a+j*b!=k)continue;
		res=res+c[i]*c[j]%MOD;
		res%=MOD;
	}
	cout<<(res%MOD+MOD)%MOD<<endl;
	return 0;
}
/*
  300000 2 2 15000
  300000 1 1 180000000000
 */
```

---

## 作者：Chillturtle (赞：0)

# 题意

这道题的关键点在于这一句话。

- **每个格子可以涂成红、蓝、绿或不涂色，得分分别为 $A,B,A + B,0$。**

# 思路

经过分析可以发现。

- 绿的就等于一个红的和一个蓝的。

那么接下来的事情就好办了，我们可以将蓝色和红色分别独立，直接去算，有多少个蓝色，多少个红色就可以了。这个我们可以用**逆元**处理。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/42vqk6o4.png)

### [逆元模板传送门](https://www.luogu.com.cn/problem/P3811)

最后看一眼数据范围 $0 \le k \le 18 \times 10^{10}$。所以记得开 ``long long``。

## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10;
const int MOD=998244353;
int n,a,b,k,opt=0;
int cnt[N],ans[N];
void init(){
    cnt[0]=1;
	cnt[1]=1;
	ans[0]=1;
	ans[1]=1;
    for(int i=2;i<=n;i++){
        cnt[i]=cnt[i-1]*i%MOD;
        ans[i]=(MOD-MOD/i)*ans[MOD%i]%MOD;
    }
    for(int i=2;i<=n;i++){
    	ans[i]=ans[i]*ans[i-1]%MOD;
	}
}
int power(int n,int m){
	if(n<m){
		return 0;
	}
	return cnt[n]*ans[m]%MOD*ans[n-m]%MOD;
}
signed main(){
	cin>>n>>a>>b>>k;
	init();
	for(int i=0;i*a<=k&&i<=n;i++){
		if((k-a*i)%b==0){
			opt=(opt+power(n,i)*power(n,(k-a*i)/b)%MOD)%MOD;
		}
	}
	cout<<opt<<endl;
return 0;
}
```

---

## 作者：_Flame_ (赞：0)

### $\text{solution}$

绿色的权值等于红色加蓝色，所以显然可以将绿色拆成红色加蓝色，减少一个要考虑的颜色。

考虑只有红色和蓝色，即用 $a$ 和 $b$ 凑出 $k$ 的方案数，可以枚举一个 $a$ 的数量 $i$，此时因为所有 $a$ 和 $b$ 的和为 $k$，所以可以得出 $b$ 的数量为 $\frac{k-i\times a}{b}$，对于这种 $a$ 和 $b$ 的数量情况，总方案数为 $C_{n}^{i}\times C_{n}^{\frac{k-i\times a}{b}}$。

### $\text{code}$

```cpp
int n,a,b,k;

int ans=0;

int fac[maxn],inv[maxn];
int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b&1){
			ans=ans*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
	return ans%mod;
}

void init(int maxn){
	fac[0]=1;
	for(int i=1;i<=maxn;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	inv[maxn]=ksm(fac[maxn],mod-2);
	for(int i=maxn-1;i>=0;i--){
		inv[i]=inv[i+1]*(i+1)%mod;
	}
}

int C(int m,int n){
	if(n<0||m<0||m<n){
		return 0ll;
	}
	return fac[m]*inv[n]%mod*inv[m-n]%mod;
}

void solve(){
	n=read(),a=read(),b=read(),k=read();
	
	init(n+10);
	for(int i=0;i<=n;i++){
		if(k<i*a){
			break;
		}
		else{
			if((k-i*a)%b!=0){
				continue ;
			}
			else{
				int j=(k-i*a)/b;
				ans=(ans+C(n,i)*C(n,j)%mod)%mod;
//				cout<<ans<<endl;
			}
		}
	}
	write(ans);
	puts("");
	return ;
}
```

---

## 作者：Xiphi (赞：0)

### AGC025B

把绿色的格子看做一个红加一个蓝格子，则问题转化为，在红蓝格子（$A$，$B$）个数都不大于 $n$ 的前提下，能凑出多少个 $k$。

考虑枚举 $A$ 的个数，则 $B$ 的个数就是 $c_0=\frac{k-A\times {c_1}}{B}$，$c_1$ 表示 $A$ 的个数。在上式为一个正整数时，就往答案上添加 $C^{c_0}_n \times C^{c_1}_n$。

组合数直接逆元预处理即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
const int N=3e5+610;
int infact[N],m[N];
int quickpow(int a, int b){
    int res=1;
    while(b){
        if(b&1)res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
int cal(int b,int a){
    return (m[a]*infact[b]%mod)*infact[a-b]%mod;
}
int n,a,b,k;
int calc(int c1){
	return cal(c1,n)*cal((k-c1*a)/b,n)%mod;
}

signed main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>a>>b>>k;
	m[0]=infact[0]=1;
    for (int i=1;i<=3e5;i++) {
        m[i]=m[i-1]*i%mod;
        infact[i]=infact[i-1]*quickpow(i,mod-2)%mod;
    }
    int ans=0;
    for(int i=1;i<=n;++i){
    	if((k-i*a)%b!=0) continue;
    	ans+=calc(i);
		ans%=mod;
	}
	cout<<ans;
	return 0;
}
```
```

---

