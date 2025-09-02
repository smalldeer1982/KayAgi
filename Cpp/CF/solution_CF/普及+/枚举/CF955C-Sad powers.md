# Sad powers

## 题目描述

You're given $ Q $ queries of the form $ (L,R) $ .

For each query you have to find the number of such $ x $ that $ L<=x<=R $ and there exist integer numbers $ a&gt;0 $ , $ p&gt;1 $ such that $ x=a^{p} $ .

## 说明/提示

In query one the suitable numbers are $ 1 $ and $ 4 $ .

## 样例 #1

### 输入

```
6
1 4
9 9
5 7
12 29
137 591
1 1000000
```

### 输出

```
2
1
0
3
17
1111
```

# 题解

## 作者：Eason_AC (赞：7)

## Content
给你 $q$ 个询问，每次询问 $[l,r]$ 这个区间内满足 $x=a^p(a>0,p>1)$ 的 $x$ 的数量。

数据范围：$1\leqslant q\leqslant 10^5$，$1\leqslant l\leqslant r\leqslant 10^{18}$。
## Solution
第一次自己独立做出了紫题，特此发篇题解纪念一下。

首先，我们看到数据范围是 $10^{18}$ 级别的，看到次幂，然后联想到 $\sqrt{10^{18}}=10^9$，$\sqrt[3]{10^{18}}=10^6$。然后我们发现，如果 $p\geqslant 3$ 的话，貌似可以直接预处理出所有的满足题目要求的 $x$，询问时直接二分其位置即可。至于 $p=2$ 的情况（事实上就是完全平方数），由于 $x$ 以内的完全平方数个数为 $\sqrt{x}$，因此利用类似前缀和的思想就可以求出这一部分的答案为 $\sqrt{r}-\sqrt{l-1}$。两个部分综合在一起即可求出答案。

具体实现的时候要注意答案的边界问题以及直接开根带来的精度问题。
## Code
请注意，以下代码仅可在 C++14 语言下通过。原因可能是 `sqrt` 容易掉精度。
```cpp
namespace Solution {
	const int N = 3e6 + 7;
	const ll MX = 1e18;
	int q, cnt;
	ll l, r, num[N];
	
	ill solve(ll x) {
		ll idx = lower_bound(num + 1, num + cnt + 1, x) - num;
		if((idx <= cnt && num[idx] > x) || idx > cnt) idx--;
		return idx + (ll)sqrt(x);
	}
	
	iv Main() {
		F(ll, i, 2, 1000000) {
			long long k = i * i;
			for(; k <= MX / i; ) {
				k *= i;
				ll sqrtk = sqrt(k);
				if(sqrtk * sqrtk != k) num[++cnt] = k;
			}
		}
		sort(num + 1, num + cnt + 1), cnt = unique(num + 1, num + cnt + 1) - num - 1;
		read(q); while(q--) read(l, r), print(solve(r) - solve(l - 1), '\n');
		return;
	}
}
```

---

## 作者：max0810follower (赞：6)

注意到，本题是容斥，很显然看出来和唯一分解有关系。稍微思考一下，其实本题就是莫比乌斯函数板子题。每次二分小于 $n$ 的所有 $a^k$ 最大的 $a$ 来计算个数即可。

然后你就喜提 `TLE` 了，显然这个题略微有点卡常。这里给一个比较简单的卡常方法，在二分时，发现随着 $k$ 的增大 $a$ 的最大值是会以一个及其快的速度衰减的。所以，可以把对于每个 $k$ 时 $a$ 的最大值存下来作为二分。写完后发现跑得飞快。

然后就是代码了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mu[74]={0,0,1,1,0,1,-1,1,0,0,-1,1,0,1,-1,-1,0,1,0,1,0,-1,-1,1,0,0,-1,0,0,1,1,1,0,-1,-1,-1,0,1,-1,-1,0,1,1,1,0,0,-1,1,0,0,0,-1,0,1,0,-1,0,-1,-1,1,0,1,-1,0,0};
const int maxx[74]={0,0,1000000000,1000000,31622,3981,1000,372,177,100,63,43,31,24,19,15,13,11,10,8,7,7,6,6,5,5,4,4,4,4,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1};
bool check(ll a,int b,ll n)
{
	ll sum=1;
	while(b)
	{
		if(b&1)
		{
			if((__int128)sum*a>n)
				return false;
			sum*=a;
		}
		b>>=1;
		if((__int128)a*a>n&&b)
			return false;
		a*=a;
	}
	return true;
}
ll calc(ll n)
{
	if(!n)
		return 0;
	ll ans=1;
	for(int i=2;i<=64;i++)
	{
		int l=1,r=maxx[i];
		while(l<r)
		{
			int mid=l+(r-l+1)/2;
			if(check(mid,i,n))
				l=mid;
			else
				r=mid-1;
		}
		ans+=mu[i]*(l-1);
	}
	return ans;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		ll l,r;
		scanf("%lld%lld",&l,&r);
		printf("%lld\n",calc(r)-calc(l-1));
	}
	return 0;
}
```

---

## 作者：XL4453 (赞：5)

### 解题思路：

显然具有区间可减性，那么就只需要算出 $[1,r]$ 和 $[1,l-1]$ 中满足条件的数就行了。

注意到从三次开始符合条件的数就很小了（$n^{\frac{1}{3}}$ 数量级，也就是 $10^6$ 级别的），考虑将二次和三次即以上分开处理。

对于二次，考虑直接计算，答案就是 $\sqrt{n}$。

可以用一个数组预处理出所有的形式为 $a^p$ 的数，其中满足这里的 $a^p$ 不能写成 $x^2$ 的形式，否则就重复计算了。
每一次询问用二分法找出可以取到的最大值就行了。

---

本质上就是一个容斥原理。

这里要注意，如果将二次和三次都直接计算，这两个的重复部分并不能很快求出，如果不直接计算二次，那么需要预处理的数就太多了（$10^9$ 级别）。

---
### 代码：

```cpp
#include<cmath>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
long long T,l,r;
vector <long long> p;
long long pow_(long long x,long long y){
	long long ans=1;
	while(y){
		if(y&1)ans*=x;
		x*=x;
		y=y>>1;
	}
	return ans;
}
void init(){
	for(int i=3;i<=59;i+=2)
	for(int j=1;j<=pow(1e18,1.0/i);j++){
		long long now=pow_(j,i);
		long long sq=sqrt(now);
		if(sq*sq==now)continue;
		p.push_back(now);
	}
	sort(p.begin(),p.end());
	p.erase(unique(p.begin(),p.end()),p.end());
}
long long work(long long now){
	long long ans=sqrt(now);
	long long now_=lower_bound(p.begin(),p.end(),now)-p.begin();
	if(now_==p.size())now_--;
	else if(p[now_]>now)now_--;
	return ans+now_;
}
int main(){
	init();
	scanf("%I64d",&T);
	while(T--){
		scanf("%I64d%I64d",&l,&r);
		printf("%I64d\n",work(r)-work(l-1));
	}
	return 0;
}
```


---

## 作者：开始新的记忆 (赞：4)

题目大意：q组询问，每组询问给你一个区间l~r，让你求有多少数x，满足x=a^p。

大致思路：上界为1e18 那么p最大不会超过61.
现在计算出f[1,n]有多少个数x 满足x=a^p .那么答案就是f[r]-f[l-1]
枚举p,二分此时a^p<=n的最大a为多少 然后发现重复的处理不来....wa...

可以先暴力预处理出1e18内,p>=3的所有Perfect Number. O(1e6).
然后对于给定的n,p==2的有sqrt(n)个.然后p>=3时,在vector中二分中最后一个<=n的位置即可.

code：
```
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
vector<long long> v;
void init()
{
	long long n=1e18;
	for(long long i=2;i*i*i<=n;i++) 
	{
		long long s=i*i;
		while(s<=n/i)
		{
			s*=i;
			long long t=sqrt(s);
			if(t*t!=s) 
				v.push_back(s);
		}
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
}
long long calc(long long n)
{
	long long idx=lower_bound(v.begin(),v.end(),n)-v.begin();	
	if(idx<v.size() && v[idx]>n)
		idx--;
	if(idx==v.size())
		idx--;
	return (long long)sqrt(n)+idx;
} 
int main()
{	long long Q,l,r;
	init(); 
	cin>>Q;
	while(Q--)
	{
		cin>>l>>r;
		cout<<calc(r)-calc(l-1)<<endl;
	}
	return 0;
}
```


---

## 作者：ncwzdlsd (赞：3)

春季测原题为什么没有人来写题解啊/kk。

考虑 $p$ 的几种取值可能，显然当 $p\geq 3$ 时，可以被表示的数的数量会减少很多，于是乎我们对于 $p=2$ 和 $p>2$ 的情况进行分类讨论：

当 $p>2$ 时，我们考虑用一个 `vector` 来存储不能表示为 $a^p$ 的数的集合，注意这里存储的数不能有可以表示为 $2$ 的次幂的数，否则会重复计算，注意统计过程中需要 `unique` 去重；对于 $p=2$ 的情况，直接计算累加即可。

注意 `sqrt` 操作的精度。

最终统计答案时，由于询问区间有可减性，所以把 $[1,r]$ 与 $[1,l-1]$ 的答案相减即可。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> v;

int qpow(int a,int b)
{
	int res=1;
	for(;b;a*=a,b>>=1)
		if(b&1) res=res*a;
	return res;
}

void init()
{
	for(int i=3;i<60;i+=2)
		for(int j=1;j<=1000000;j++)
		{
			int tmp=qpow(j,i);
			if(tmp==1||(int)sqrt(tmp)*(int)sqrt(tmp)==tmp) continue;
			if(tmp>1e18||tmp<0) break;
			v.push_back(tmp);
		}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());	
}

int work(int n)
{
	int ans=(int)sqrt(n),p=lower_bound(v.begin(),v.end(),n)-v.begin();
	if(p<=v.size()&&v[p]>n||p==v.size()) p--;//卡线
	ans+=p;
	return ans; 
}

signed main()
{
	int Q;cin>>Q;
	init();
	while(Q--)
	{
		int l,r;cin>>l>>r;
		cout<<work(r)-work(l-1)<<endl;
	}
	return 0;
}
```

---

## 作者：VenusM1nT (赞：3)

先考虑 $\leq n$ 有多少个满足的，考虑 $p=2$ 的情况，显然对于 $n$，有 $\lfloor \sqrt{n}\rfloor$ 个满足条件的。然后考虑 $p>2$，若 $p=3$，有 $\lfloor \sqrt[3]{n} \rfloor$ 种，但这两种情况必然有重复的，比如 $64$，$p>3$ 同理，因此考虑对于 $p>2$ 单独计算。注意到 $\sqrt[3]{10^{18}}=10^6$，因此可以考虑对于 $x\in[2,10^6]$，$3\leq p\leq 59$，将**不为平方数**的 $x^p$ 加到一个 vector 里面，排序去重之后，只需要二分出 $n$ 在 vector 中的位置就可以得到 $p>2$ 时满足条件的。最后搞个容斥就出来了。  
![](https://t1.picb.cc/uploads/2020/10/26/tYMToc.png)
```cpp
#include<bits/stdc++.h>
#define N 100
#define reg register
#define inl inline
#define int long long
#define inf 1e18
using namespace std;
int Q;
vector <int> g;
inl int Pow(reg int x,reg int y)
{
	reg int res=1;
	for(;y;y>>=1,x=x*x) if(y&1) res=res*x;
	return res;
}
inl void Init()
{
	for(reg int i=3;i<=59;i+=2)
	{
		for(reg int j=1;j<=1000000;j++)
		{
			reg int cnt=Pow(j,i);
			if(!cnt || cnt==1 || (int)sqrt(cnt)*(int)sqrt(cnt)==cnt) continue;
			if(cnt>inf || cnt<0) break;
			g.push_back(cnt);
		}
	}
	sort(g.begin(),g.end());
	g.erase(unique(g.begin(),g.end()),g.end());
}
inl int Calc(reg int n)
{
	reg int res=(int)sqrt(n);
	reg int pos=lower_bound(g.begin(),g.end(),n)-g.begin();
	if(pos<(int)g.size() && g[pos]>n) pos--;
	else if(pos==(int)g.size()) pos--;
	res+=pos;
	return res;
}
signed main()
{
	Init();
	scanf("%lld",&Q);
	while(Q--)
	{
		reg int l,r;
		scanf("%lld %lld",&l,&r);
		printf("%lld\n",Calc(r)-Calc(l-1));
	}
	return 0;
}
```

---

## 作者：Hanx16Kira (赞：3)

# CF955C Sad powers

[Luogu CF955C](https://www.luogu.com.cn/problem/CF955C)


## Solution

~~2023 春赛观光团。~~

对于一个询问 $[l,r]$，显然可以拆成 $[1,r]-[1,l-1]$ 两部分计算。

考虑 $[1,n]$ 如何计算。由于指数的值域很小，因此可以考虑枚举指数来计算答案。

记 $f_i$ 表示满足 $a_i\le n$ 的数量（不考虑与其他指数重复的情况），那么显然可以得知 $f_i=\sqrt[i]{n}$。考虑如何容斥掉重复的部分，直接容斥貌似不好做，因此考虑钦定一个数的唯一指数表示方式。

对于一个数 $t$，假设 $t=a_1^{p_1}=a_2^{p_2}(p_1>p_2)$，那么将 $t$ 的表示方法钦定为 $t=a_1^{p_1}$，即指数最大的一个。容易发现，对于所有可以组成 $t$ 的指数 $p$ 都有 $p_i \mid p_1$。那么按照这种钦定方法下，记每个指数对答案的贡献是 $\text{ans}_i$，那么有 $\text{ans}_i=f_i-\displaystyle \sum\limits_{i\mid j}\text{ans}_j$。从大到小计算即可。时间复杂度是 $\mathcal O(\log^2 n)$ 级别的。

代码实现的时候有一个很麻烦的东西，就是 $\sqrt[i]{n}$ 如何计算。如果使用 $n^{1/i}$ 计算会出现很大的精度问题；如果用二分计算的话时间会超时。因此有一个折中的办法，就是先用 $n^{1/i}$ 计算，然后再暴力判断计算出来的这个值 $v$ 接近的值是否满足答案，即判断一下 $v+1,v-1,v+2,v-2,\dots$ 是否符合条件，然后卡一下精度就过了。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

int l, r;
int a[100005];

inline long double Qpow(int x, int y) {
	long double res = 1, base = x;
	
	for (; y; y >>= 1, base *= base) {
		if (y & 1) {
			res *= base;
		}
	}
	
	return res;
}

inline int GetRoot(int x, int y) {
	int v = powl(x, (long double)1.0 / y + 1e-9);
	
	if (Qpow(v + 1, y) < x) 
		for (++v; Qpow(v + 1, y) < x; ++v);
		
	if (Qpow(v, y) > x)
		for (--v; Qpow(v, y) > x; --v);
	
	return v;
}

int Calc(int n) {
	if (n == 0) return 0;
	
	int res = 1;
	int lim = 0;
	
	for (int i = 2; ; ++i) {
		int v = GetRoot(n, i);
		lim = i;
		
		if (v <= 1) break;
		
		a[i] = v - 1;
	}
	
	for (int i = lim - 1; i >= 2; --i) {
		for (int j = i + i; j < lim; j += i) {
			a[i] -= a[j];
		}
	}
	
	for (int i = 2; i < lim; ++i) {
		res += a[i];
	}
	
	return res;
}

void Solve() {
	cin >> l >> r;
	cout << Calc(r) - Calc(l - 1) << '\n';
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int T; cin >> T;
	
	while (T--) Solve();
}
```

---

## 作者：zesqwq (赞：2)

春测的原题。

形如 $a^b$ 的数会随着 $b$ 的增大而迅速减少，当 $b = 64$ 时就没有除了 $a = 1$ 之外的解了。

因此考虑特判 $a^2$，这是容易的，其他的形如 $a^b,b \ge 3$ 的数个数很少，只有 $\sum_{i=3}\sqrt[i]V = O(\sqrt[3]V)$ 个，暴力存下来，回答的时候二分即可。

---

## 作者：murder_drones (赞：0)

题解区清一色暴力找数做法，要分讨两种情况感觉不够优雅。

考虑容斥，将形如 $a^2$，$a^3$ 的数加上，$a^4$ 在 $a^2$ 里算过了就不加，但是这样会算重 $a^6$，于是减去......。注意到这个是一个经典容斥，系数为莫比乌斯函数。那么这题就只需要一个开根和线筛莫比乌斯函数即可。时间复杂度 $O(T\log V)$。

小心 powl 的精度问题。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=70;
typedef __int128 ll;
const long long INF=1e18+10;
ll qpow(ll a,int b){
	ll res=1;
	for(;b;a=a*a,b>>=1)
		if(b&1) res=res*a;
	return res;
}

int isp[maxn],pr[maxn],pcnt;
int mu[maxn];
void prepare(){
	int n=65;
	for(int i=1;i<=n;i++) isp[i]=1;
	isp[1]=0;mu[1]=1;
	for(int i=2;i<=n;i++){
		if(isp[i]){
			mu[i]=-1;
			pr[++pcnt]=i;
		}for(int j=1;j<=pcnt&&i*pr[j]<=n;j++){
			isp[i*pr[j]]=0;
			if(i%pr[j]==0){
				mu[i*pr[j]]=0;
				break;
			}mu[i*pr[j]]=mu[i]*mu[pr[j]];
		}
	}
}

long long get_rt(long long a,int b){
	if(mu[b]==0) return 0;
	long long st=(long long)powl(a,(long double)1.0/b)+1e-10;
	st-=2;st=max(0ll,st);
	while(qpow(st,b)<=a) st++;st--;
	return st-1;
}
long long calc(long long n){
	if(n==0) return 0;
	long long ans=0;
	for(int i=2;i<=__lg(n);i++) ans+=-mu[i]*get_rt(n,i);
	return ans+1;
}

void solve(){
	long long l,r;
	scanf("%lld%lld",&l,&r);
	printf("%lld\n",calc(r)-calc(l-1));
}

int main(){
	prepare();
	int T;scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：xiaofu15191 (赞：0)

[ABC361F](https://atcoder.jp/contests/abc361/tasks/abc361_f) 原题时代考古。

很难想象我 ABC 赛时为什么有了正解思路没打。伤心。

参照 [ABC361F](https://atcoder.jp/contests/abc361/tasks/abc361_f)，在 $[1,10^{18}]$ 范围内，虽然 $a^2$ 的个数是 $10^9$ 级别的，但是除去 $a^2$，剩余的 $a^b$ 个数大约只有 $10^6$ 个！

我们从 $3$ 到 $59$ 枚举指数 $b$，因为 $2^{59} < 10^{18} < 2^{60}$；再枚举底数 $a$，只要 $a^b$ 超过 $10^{18}$ 就跳出枚举 $a$ 的这层循环。

注意到使用 `cmath` 库中的 `pow` 函数或快速幂可能会超出 `long long` 的值域，由于 $b$ 的值不大，所以可以手写一个 `pow` 函数，一次一次的乘。还有一个技巧就是 `double` 可以在丢失低位精度的情况下存储大数，这样就不用担心值域问题了。

剩下的 $a^2$ 可以使用 `sqrt` 算出，**但是一定要自己写，`cmath` 库中的 `sqrt` 有精度误差。**

对于这道 CF955C 来说，我们只需要将 $a^b(b>2)$ 的值存入数组，排序、去重，在数组中二分求解即可。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
long long x[100010],y[100010],n;
vector<long long>z;
long long pow(long long a,long long b)
{
	long long ans=1;
	for(long long i=1;i<=b;i++)
	{
		double tmp=ans;
		tmp*=a;
		if(tmp>2e18) return 2e18;
		ans*=a;
	}
	return ans;
}
long long sqrt(long long x)
{
	long long l=1,r=1e9,ans=0;
	while(l<=r)
	{
		long long mid=(l+r)/2;
		if(mid*mid>x) r=mid-1;
		else
		{
			ans=mid;
			l=mid+1;
		}
	}
	return ans;
}
long long work(long long x)
{
	auto it=upper_bound(z.begin(),z.end(),x)-1;
	return it-z.begin()+1;
}
int main()
{
	scanf("%lld",&n);
	long long origin_n=n;
	for(long long i=1;i<=n;i++)
		scanf("%lld%lld",&x[i],&y[i]);
	for(long long i=3;i<=59;i++)
	{
		for(long long j=2;;j++)
		{
			long long tmp=pow(j,i);
			if(tmp>1e18) break;
			long long tmp2=sqrt(tmp);
			if(tmp2*tmp2==tmp) continue;
			z.push_back(tmp);
		}
	}
	sort(z.begin(),z.end());
	z.resize(unique(z.begin(),z.end())-z.begin());
	for(long long i=1;i<=origin_n;i++)
	{
		long long res=work(y[i])-work(x[i]-1);
		res+=sqrt(y[i])-sqrt(x[i]-1);
		printf("%lld\n",res);
	}
}
```

---

## 作者：OIer_ACMer (赞：0)

~~数学真是个“奇妙”的学科！~~

------------
注：本题的数学推理比较简单，所以笔者在这里不多赘述原理以及证明，望周知！

------------
## 大致思路：
根据数学推理，我们可以知道：$\sqrt{10^{18}} = 10^9$，$\sqrt[3]{10^{18}} = 10^6$，$\sqrt[18]{10^{18}} = 10$。根据这些规律，我们发现：**能组成平方数的数十分的少**，并且区间内 $[l,r]$ 的指数为偶数的个数有 $\sqrt{r} - \sqrt{l - 1}$，也叫**完全平方数的个数**，且之后会用到（这个数学推导请读者自行下去查阅资料或证明）。

综上所述，我们可以在程序一开始就预处理出 $x$ 为 $2$ 到 $10^6$，$y$ 为 $3$ 到 $10^6$（注意是 $3$），且为所有满足 $x^y$ 不是平方数的个数（如果你预处理是平方数的个数那就等着 MLE 吧），同时要运用**前缀和的思想**优化时间复杂度。

最终，在计算答案之前有两个重要的步骤不能忘：

1. 要给预处理出来的不满足序列**去重**，因为有的平方数算出来的结果是相同的（例如 $2^4=4^2=16$）。

2. 再计算出答案后，要给答案加上 $\sqrt{r} - \sqrt{l - 1}$，因为我们的二分搜索的时候没有考虑到完全平方数，因此加上 $\sqrt{r} - \sqrt{l - 1}$ 能够将完全平方数的个数也加进去（反正我们已经通过公式知道了完全平方数的个数）。

------------
## 代码如下：

```c+
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int N = 3e6 + 7;
const int M = 1e18;
int q, cnt;
int l, r, num[N];
inline int solve(int x)
{
    int idx = lower_bound(num + 1, num + cnt + 1, x) - num;
    if ((idx <= cnt && num[idx] > x) || idx > cnt)
    {
        idx--;
    }
    return idx + (int)sqrt(x);// 计算有多少种不符合的
}
signed main()
{
    for (int i = 2; i <= 1000000; ++i)
    {
        long long k = i * i;
        for (; k <= M / i;)
        {
            k *= i;
            int sqrtk = sqrt(k);
            if (sqrtk * sqrtk != k)
            {
                num[++cnt] = k;
            }
        }
    }// 一个个枚举
    sort(num + 1, num + cnt + 1);
    cnt = unique(num + 1, num + cnt + 1) - num - 1;
    q = read();
    while (q--)
    {
        l = read();
        r = read();
        cout << solve(r) - solve(l - 1) << "\n";
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/122579297)

---

## 作者：zhang_kevin (赞：0)

# Solution

首先，我们可以知道，这道题的答案类似于前缀和，因此 $[l,r] = [1,r] - [1,l-1]$。

数据范围最大是 $10^{18}$，发现 $\sqrt{10^{18}}$ 是 $10^9$ 级别的，而 $\sqrt[3]{10^{18}}$ 是 $10^6$ 级别的。所以，$p \geq 3$ 的情况可以使用预处理与二分的方法解决。

对于剩下的 $p=2$ 的情况，可以特殊处理。$p=2$ 意味着找平方数，则 $p=2$ 这一部分的答案为 $\sqrt{r} - \sqrt{l-1}$。

最后加在一起即可。

# Code

要注意一些细节，否则很有可能出错。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<ll> f;
inline void init(){
	ll n = 1e18;
	for(ll i = 2; i * i * i <= n; i++) {
		ll k = i * i;
		while(k <= n / i){
			k *= i;
			ll g = sqrtl(k);
			if(g * g != k){    // 不是平方数 
				f.push_back(k);
			}
		}
	}
	sort(f.begin(), f.end());
	f.erase(unique(f.begin(), f.end()), f.end());
	return;
}
inline ll getSum(ll x){
	ll temp = lower_bound(f.begin(), f.end(), x) - f.begin();
	if((temp<=(int)f.size()&&f[temp]>x) || temp == (int)f.size()) temp--; //正好卡线的不要
	return temp + (ll)sqrtl(x);
}
int main(){
	init();
	int T;
	cin >> T;
	while(T--){
		ll l, r;
		cin >> l >> r;
		cout << getSum(r) - getSum(l-1) << endl; 
	} 
	return 0;
}
```


---

