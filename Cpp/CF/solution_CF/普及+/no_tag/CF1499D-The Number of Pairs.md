# The Number of Pairs

## 题目描述

You are given three positive (greater than zero) integers $ c $ , $ d $ and $ x $ .

You have to find the number of pairs of positive integers $ (a, b) $ such that equality $ c \cdot lcm(a, b) - d \cdot gcd(a, b) = x $ holds. Where $ lcm(a, b) $ is the least common multiple of $ a $ and $ b $ and $ gcd(a, b) $ is the greatest common divisor of $ a $ and $ b $ .

## 说明/提示

In the first example, the correct pairs are: ( $ 1, 4 $ ), ( $ 4,1 $ ), ( $ 3, 6 $ ), ( $ 6, 3 $ ).

In the second example, the correct pairs are: ( $ 1, 2 $ ), ( $ 2, 1 $ ), ( $ 3, 3 $ ).

## 样例 #1

### 输入

```
4
1 1 3
4 2 6
3 3 7
2 7 25```

### 输出

```
4
3
0
8```

# 题解

## 作者：Andy_Li (赞：11)

# CF1499D The Number of Pairs题解

### 题意

有 $t$ 组询问，每组询问给定三个整数 $c,d,x$。

问有多少对 $(a,b)$ 使得 $c \times \operatorname {lcm}(a,b) - d \times \gcd(a,b) = x$。

（$1 \le t \le 10^4$，$1 \le c,d,x \le 10^7$）

### 思路

一眼数学题。

想办法将 $\gcd(a,b)$ 消掉或者移向到同一侧。

消掉不太可能，我们想办法移到同一侧。

下面开始推公式。

设 $\gcd(a,b) \times k1 = a$，$\gcd(a,b) \times k2 = b$。 

$$c \times \operatorname{lcm}(a,b) - d \times \gcd(a,b) = x$$
$$c \times \frac{a \times b}{\gcd(a,b)} - d \times \gcd(a,b) = x$$
$$c \times \frac{\gcd(a,b) \times k1 \times \ \gcd(a,b) \times k2}{\gcd(a,b)} - d \times \gcd(a,b) = x$$
$$c \times k1 \times \gcd(a,b) \times k2 - d \times \gcd(a,b) = x$$
$$\gcd(a,b) \times (c \times k1 \times k2 - d) = x$$
$$\gcd(a,b) = \frac{x}{c \times k1 \times k2 - d}$$
${c \times k1 \times k2 - d}\ | \ x$ 时，$\gcd(a,b)$ 才有意义。

设 $y = c \times k1 \times k2 - d$，$k1 \times k2 = \frac{y+d}{c}$，

$c\ | \ (y + d)$ 时，$k1 \times k2$ 才有意义。

我们考虑枚举 $x$ 的因子 $y$。对于每个 $y$，当 $c\ | \ (y + d)$ 时，记录 $\frac{y+d}{c}$ 的值，将其分解质因数。

对于每种质因子，要么全给 $k1$，要么全给 $k2$。所以对于每种质因子，只有两种情况。

设 $\frac{y+d}{c}$ 有 $p$ 种质因子，则对答案的贡献为 $2^{p}$ 个。

注：要预处理出来每个数的质因子种类数，不然会超时。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
map<int,int> mp;
int vis[20000010];
int prime[5000010],cnt=0,N=2e7;
void oula()
{
	for(int i=2;i<=N;i++)
	{
		if(vis[i]==0)
		{
			prime[++cnt]=i;
			vis[i]=1;
		}
		for(int j=1;j<=cnt && i*prime[j]<=N;j++)
		{
			mp[i%prime[j]]=1;
			vis[i*prime[j]]=vis[i]+1;
			if(i%prime[j]==0)
			{
				vis[i*prime[j]]=vis[i];
				break;
			}
		}
	}
	return ;
}
int main()
{
	cin.tie(0);
	std::ios::sync_with_stdio(false);
// srand((unsigned)time(NULL));
//    freopen(".in","r",stdin);
//    freopen(".out","w",stdout);
	int t;
	cin>>t;
	oula();
	while(t--)
	{
		ll c,d,x,ans=0;
		cin>>c>>d>>x;
		for(int i=1;i*i<=x;i++)
			if(x%i==0)
			{
				ll y1=i,y2=x/i;
				if((y1+d)%c==0)
				{
					ll k1k2=(y1+d)/c;
					ans+=(1ll<<(1ll*vis[k1k2]));
				}
				if(y1==y2)
					continue;
				if((y2+d)%c==0)
				{
					ll k1k2=(y2+d)/c;
					ans+=(1ll<<(1ll*vis[k1k2])); 
				}
			}
		cout<<ans<<endl;
	}
	return 0;
}

```

感谢[Wf_yjqd](https://www.luogu.com.cn/user/526094)帮忙调过。

---

## 作者：H6_6Q (赞：9)

$$\large\text{Summary}$$

$t$ 组询问，每次询问给定 $c,d,n$，求有多少对不同的 $(a,b)$ 满足 $c \times \text{lcm}(a,b)-d\times\gcd(a,b)=x$

$t \le 10^4,c,d,n \le 10^7$

$$\large\text{Solution}$$

假设我们已经确定 $\gcd(a,b)$ 的值，那么就能直接算出 $\text{lcm}(a,b)=\dfrac{x+d\times\gcd(a,b)}{c}$。

一个显然的事情是，一定存在一个正整数 $r$ 满足 $\text{lcm}(a,b)=r \times \gcd(a,b)$

那么我们就可以得到 $r \times \gcd(a,b)=\dfrac{x+d\times\gcd(a,b)}{c}$

整理一下得 $\gcd(a,b)=\dfrac{x}{r \times c - d}$

那么思路就很显然了，枚举 $x$ 的所有因子，看其是否可以表示为 $r\times c -d$ 的形式，这样我们就得到了所有不同的 $\gcd(a,b)$ 与 $\text{lcm}(a,b)$。

那么问题就转化为怎么计算有多少个 $(a,b)$ 的 $\gcd(a,b)$ 与 $\text{lcm}(a,b)$ 与算出来的相等。

从质因子方面想一想就会发现，一共有 $2^{g(r)}$ 种可能，其中 $g(x)$ 表示 $x$ 的质因子个数。

所以筛出来 $g$ 函数，然后枚举 $x$ 的因子计算即可。

时间复杂度 $\text{O}(n+t \sqrt{n})$

$$\large\text{Code}$$

```cpp
const int N=2e7+5;
int t,c,d,n,m,ans,vis[N],sum[N],pri[N];

inline int work(int x);

signed main()
{
	for(int i=2;i<=20000000;++i)
	{
		if(!vis[i]) pri[++m]=i,sum[i]=1;
		for(int j=1;j<=m&&pri[j]*i<=20000000;++j)
		{
			vis[pri[j]*i]=1;
			if(i%pri[j]==0)
			{
				sum[pri[j]*i]=sum[i];
				break;
			}
			sum[pri[j]*i]=sum[i]+1;
			
		}
	}
	t=read();
	while(t--)
	{
		c=read();d=read();n=read();ans=0;
		for(int i=1;i*i<=n;++i)
			if(n%i==0)
			{
				ans+=work(i);
				if(n/i!=i) ans+=work(n/i);
			}
		printf("%lld\n",ans);
	}
	return 0;
}

inline int work(int x)
{
	if((d+x)%c!=0) return 0;
	int r=(d+x)/c;
	return 1ll<<sum[r];
}
```

---

## 作者：zjjws (赞：7)

### 题意

[题链](http://codeforces.com/contest/1499/problem/D)

$$c\cdot \operatorname {lcm}(a,b)-d\cdot \gcd(a,b)=x$$

给定 $c,d,x$，求有序二元组 $(a,b)$ 的个数。

---

### Solution

设 $\gcd(a,b)=\beta$，将式子转化为：

$$c\cdot \frac{a\cdot b}{\beta}-d\cdot \beta=x$$

$$c\cdot \frac{a}{\beta}\cdot \frac{b}{\beta}-d=\frac{x}{\beta}$$


注意到对于一个确定的 $\beta$，$\frac{a}{\beta}\cdot \frac{b}{\beta}$ 是一个确定的值，我们假设这个值为 $s$。

因为要求乘积的两部分 $\frac{a}{\beta}$ 和 $\frac{b}{\beta}$ 互质，所以只需要求出 $s$ 的质因子个数 $p$，答案就是 $2^p$。这些东西提前预处理好就行，每次询问只需要枚举 $x$ 的因数即可。

赛场上真的是脑子抽了，式子推对了都没写出来。

---

### Code


```cpp
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#define LL long long
using namespace std;
inline LL rin()
{
    LL x=0;
    char c;
    bool tag=false;
    for(c=getchar();c>'9'||c<'0';c=getchar())if(c=='-'){c=getchar();tag=true;break;}
    for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^'0');
    if(tag)x=-x;
    return x;
}
inline void jh(int &x,int &y){if(x^y)x^=y^=x^=y;return;}
inline void jh(LL &x,LL &y){if(x^y)x^=y^=x^=y;return;}

const int N=1e7+3;
bool pri[N<<1];
int tag[N<<1];
int v[N<<1];
int pw[33];
vector<int>prime;
inline void init()
{
    int ed=N<<1;
    for(int i=2;i<=ed;i++)
    {
        if(!pri[i])prime.push_back(i),tag[i]=1,v[i]=i;
        for(vector<int>::iterator j=prime.begin();j!=prime.end();j++)
        {
            int now=(*j)*i;if(now>ed)break;
            pri[now]=true;v[now]=*j;tag[now]=tag[i]+tag[*j]-(i%(*j)==0);if(i%(*j)==0)break;
        }
    }
    pw[0]=1;for(int i=1;i<=30;i++)pw[i]=pw[i-1]<<1;
    return;
}

int D[33];
int C[33];
int tail;
int ans=0;
int c,d;
inline void dfs(int x,int num)
{
    if(num>tail){if((x+d)%c==0)ans+=pw[tag[(x+d)/c]];return;}
    dfs(x,num+1);for(int i=1;i<=C[num];i++)x*=D[num],dfs(x,num+1);return;
}
inline void work()
{
    c=rin();d=rin();
    int x=rin();ans=0;for(tail=0;x!=1;){D[++tail]=v[x];for(C[tail]=0;x%D[tail]==0;x/=D[tail])C[tail]++;}
    dfs(1,1);printf("%d\n",ans);
    return;
}
int main()
{
    init();
    for(int T=rin();T;T--)work();
    return 0;
}
```

---

## 作者：Warriors_Cat (赞：6)

[洛谷题面传送门](https://www.luogu.com.cn/problem/CF1499D) & [CF 题面传送门](http://codeforces.com/problemset/problem/1499/D)。

题意：

- $t$ 组询问，$t \le 10^4$。每次询问给定整数 $c, d, x$，值域为 $[1, 10^7]$。
- 问有多少组有序数对 $(a, b)$ 满足 $c \times \operatorname{lcm}(a, b) - d \times \gcd(a, b) = x$。

~~不得不说这道 *2100 的题算是比较水的一道了（~~

---

### Solution：

以下记值域为 $N$，数据组数为 $T$。

我们令 $a = kp, b = kq$ 且 $\gcd(p, q) = 1$，那么就有 $\gcd(a, b) = k$，$\operatorname{lcm}(a, b) = kpq$。

代回原式就有：

$$ckpq - dk = x$$

$$cpq - d = \dfrac{x}{k}$$

显然等式成立时，$k$ 是 $x$ 的约数。不妨设 $x = ky$，因此有：

$$cpq - d = y$$
$$pq = \dfrac{d + y}{c}$$

那么 $c$ 就是 $d + y$ 的约数。不妨设 $d + y = cz$：

$$pq = z$$

现在我们就考虑有多少种分解方式就行了，不妨令 $z = \prod\limits_{i=1}^np_i^{\alpha_i}$，其中 $p_i$ 为互不相同的质数。那么对于每一个 $p_i$，要么它分给 $p$，要么它分给 $q$，共有 $2$ 种选择。因为一共有 $n$ 个质因数，所以这时就有 $2^n$ 种情况。

本质不同质因数个数这个函数是可以线性筛的。线性筛预处理完，然后枚举 $x$ 的约数，接着判断 $\dfrac{d + y}{c}$ 是否为整数，最后加上贡献即可。

over，总时间复杂度为 $(N + T\sqrt N)$，足以通过此题。

---

### Code：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;
#define ll long long
#define ull unsigned long long
#define fi first
#define se second
#define mpr make_pair
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1
#define y0 y_csyakioi_0
#define y1 y_csyakioi_1
#define rep(i, x, y) for(int i = x; i <= y; ++i)
#define per(i, x, y) for(int i = x; i >= y; --i)
#define repg(i, u) for(int i = head[u]; i; i = e[i].nxt)
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const int N = 20000010;
int n, m, c, d, x, a, b, y, z, p, q, pri[N], len, vis[N], cnt, fac[N];
inline void sieve(int n){
	rep(i, 2, n){
		if(!vis[i]) pri[++len] = i, vis[i] = 1; 
		for(int j = 1; j <= len && i * pri[j] <= n; ++j){
			int k = i * pri[j];
			if(i % pri[j] == 0){ vis[k] = vis[i]; break; }
			vis[k] = vis[i] + 1;
		}
	}
}
inline void mian(){
	c = read(); d = read(); x = read(); cnt = 0; ll ans = 0;
	for(int i = 1; i * i <= x; ++i){
		if(x % i) continue;
		fac[++cnt] = i;
		if(i * i != x) fac[++cnt] = x / i;
	}
	rep(i, 1, cnt){
		int k = fac[i];
		if((d + k) % c) continue;
		int num = (d + k) / c;
		ans += (1ll << vis[num]);
	}
	printf("%lld\n", ans);
}
int main(){ sieve(N - 10); int qwq = read(); while(qwq--) mian(); return 0; }
/*
c * lcm - d * gcd = x
a = kp, b = kq, gcd = k, lcm = kpq
ckpq - dk = x
--> k | x --> x / k = y
cpq - d = y
pq = (d + y) / c
--> c | (d + y) --> z = (d + y) / c
pq = z
2^w(z)
*/
```


---

## 作者：Coros_Trusds (赞：3)

# 题目大意

有 $T$ 组询问，每组询问给定三个整数 $c,d,x$

问有多少对 $(a,b)$ 使得 $c\times \operatorname{lcm}(a,b) - d\times \gcd(a , b) = x$

$c,d,x\le 10^7$。

# 题目分析

直接枚举复杂度直接爆炸，考虑化式子：

$$\operatorname{lcm}(a,b)=\dfrac{x+d\times \gcd(a,b)}{c}$$

显然 $\operatorname{lcm}(a,b)$ 一定为 $\gcd(a,b)$，所以不妨设 $\operatorname{lcm}(a,b)=r\times \gcd(a,b)$。

于是有：

$$r\times \gcd(a,b)=\dfrac{x+d\times\gcd(a,b)}{c}$$

$$r=\dfrac{\frac{x}{\gcd(a,b)}+d}{c}$$

$$r\times c-d=\dfrac{x}{\gcd(a,b)}$$

所以有：

$$\gcd(a,b)=\dfrac{x}{r\times c-d}$$

-------

$\gcd(a,b)$ 一定是正整数，所以 $(r\times c-d)|x$。

$c,d,x$ 已给出，枚举 $r$ 即可。

$c,d,x$ 的数据范围都很大，为 $1e7$，可以想到什么？

马上想到埃氏筛/欧拉筛。

欧拉筛时，我们还可以顺便处理出 $sum_i$,表示 $i$ 的质因子个数。

若 $i$ 是质数，则 $sum_i$ 一定为 $1$。

其他情况正常判断即可。

-----
考虑一下：现在知道 $i$ 是 $x$ 的一个因数，我们可以干什么？

若 $i$ 能被表示成 $r\times c-d$ 的形式，那么此时方案数为 $2^{sum_r}$；否则为 $0$。

其中，$r\gets \dfrac{d+i}{c}$。

还要考虑一点：若当前枚举的 $r$ 的平方并不等于 $x$，则再加上 $\dfrac{x}{i}$ 对答案的贡献。

可以让这一步的时间复杂度变为 $O(\sqrt{x})$。

于是这道题就做完了。

# 代码

虽然码风比较奇怪，但是感觉思路比较清晰qwq。
```cpp
const int ma=2e7+5;

int p[ma],sum[ma];//sum[i]:i 的质因子个数 

bool is[ma];

int T,c,d,x;

int idx;

inline void init(int R)
{
	is[1]=true;
	
	for(register int i=2;i<R;i++)
	{
		if(is[i]==false)
		{
			p[++idx]=i;
			
			sum[i]=1;
		}
		
		for(register int j=1;j<=idx && i*p[j]<R;j++)
		{
			is[i*p[j]]=true;
			
			sum[i*p[j]]=sum[i]+1;
			
			if(i%p[j]==0)
			{
				sum[i*p[j]]=sum[i];
				
				break;
			}
		}
	}
}

inline int calc(int now)
{
	if((d+now)%c!=0)
	{
		return 0;
	}
	
	int r=(d+now)/c;
	
	return 1ll<<sum[r];
}

#undef int

int main(void)
{
	#define int long long
	
	init(ma);
	
	T=read();
	
	while(T--)
	{
		c=read(),d=read(),x=read();
		
		int ans(0);
		
		for(register int i=1;i*i<=x;i++)
		{
			if(x%i==0)
			{
				ans+=calc(i);
				
				if(i*i!=x)
				{
					ans+=calc(x/i);
				}
			}
		}
		
		printf("%lld\n",ans);
	}
	
	return 0;
}
```

---

## 作者：__ikun__horro__ (赞：1)

## Solution

$c \times \operatorname{lcm}(a, b) - d \times \gcd(a, b) = x$

题目中给的式子既有 $\gcd$ 又有 $\operatorname{lcm}$，我们可以令 $A = \dfrac{a}{\gcd(a, b)}$，$B = \dfrac{b}{\gcd(a, b)}$。

此时 $AB = \dfrac{ab}{\gcd(a, b)^2} = \dfrac{\operatorname{lcm}(a, b) \times \gcd(a, b)}{\gcd(a, b)^2} = \dfrac{\operatorname{lcm}(a, b)}{\gcd(a, b)}$，则 $\operatorname{lcm}(a, b) = AB \times \gcd(a, b)$。

$c \times AB \times \gcd(a, b) - d \times \gcd(a, b) = x$

提取公因式 $\gcd(a, b)$：

$\gcd(a, b) \times (c \times AB - d) = x$

$c \times AB - d$ 是 $x$ 的因数。可以枚举 $x$ 的因数 $f$，则 $AB = \dfrac{f + d}{c}$。

那么 $c$ 是 $f + d$ 的因数。枚举 $c$，得到 $\dfrac{f + d}{c}$。由于 $A$ 和 $B$ 一定是互质的，不能有相同的质因子，所以对于同一种质因子，只有给 $A$ 和给 $B$ 两种情况，并不存在分多少的说法。对答案的贡献就是 $2$ 的 $\dfrac{f + d}{c}$ 因数种数次幂。

一开始，需要把所有数的因数种数预处理出来。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

bool is[20000005];
int idx, cnt[20000005], p[4444444];

void init() {
	for (int i = 2; i <= 20000000; i++) {
		if (cnt[i] == 0) {
			p[++idx] = i;
			cnt[i] = 1;
		}
		for (int j = 1; j <= idx && i * p[j] <= 20000000; j++) {
			cnt[i * p[j]] = cnt[i] + 1;
			is[i % p[j]] = 1;
			if (i % p[j] == 0) {
				cnt[i * p[j]] = cnt[i];
				break;
			}
		}
	}
}

void sol() {
	int c, d, x;
	cin >> c >> d >> x;
	int ans = 0;
	for (int i = 1; i <= x / i; i++) {
		if (x % i) continue;
		if ((i + d) % c == 0) {
			int AB = (i + d) / c;
			ans += (1 << cnt[AB]);
		}
		if (i != x / i) {
			if ((x / i + d) % c == 0) {
				int AB = (x / i + d) / c;
				ans += (1 << cnt[AB]);
			}
		}
	}
	cout << ans << "\n";
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	init();
	int T;
	cin >> T;
	while (T--) sol();
	return 0;
}
```

---

## 作者：Wf_yjqd (赞：1)

作业题，就是推推式子。。

------------

设 $a=k_1\times\gcd(a,b)$，$b=k_2\times\gcd(a,b)$，易知 $\gcd(k_1,k_2)$。

化简原式得到 $\gcd(a,b)=\frac{x}{c\times k1\times k2-d}$。

考虑枚举 $x$ 的因数 $y=c\times k_1\times k_2-d$。

移项得到 $k_1\times k_2=\frac{y+d}{c}$。

若要对答案有贡献，$c\mid(y+d)$。

考虑 $k_1$ 和 $k_2$ 的取值，由于互质，$\frac{y+d}{c}$ 的同一个质因子必须都属于 $k_1$ 或都属于 $k_2$。

考虑欧拉筛出值域内所有 $x$ 的质因子个数 $cnt_x$。

可以推出，同一个 $k_1\times k_2$ 的方案数为 $2^{cnt_{k_1\times k_2}}$。

求和即可，复杂度 $\operatorname{O}(T\times\sqrt{n})$。

------------

没啥好看的。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=2e7+84,maxm=2e7;
ll T,c,d,x,ans,prime[maxn],pcnt,cnt[maxn];
bitset<maxn> unprime;
void get_prime(){
    for(ll i=2;i<=maxm;i++){
        if(!unprime[i]){
            prime[++pcnt]=i;
            cnt[i]=1;
        }
        for(ll j=1;j<=pcnt&&i*prime[j]<=maxm;j++){
            unprime[i*prime[j]]=1;
            if(i%prime[j]==0){
                cnt[i*prime[j]]=cnt[i];
                break;
            }
            cnt[i*prime[j]]=cnt[i]+1;
        }
    }
    return ;
}
inline ll solve(ll y){
    if((y+d)%c)
        return 0;
    return 1ll<<cnt[(y+d)/c];
}
int main(){
    scanf("%lld",&T);
    get_prime();
    while(T--){
        ans=0;
        scanf("%lld%lld%lld",&c,&d,&x);
        for(ll i=1;i*i<=x;i++){
            if(x%i)
                continue;
            ans+=solve(i);
            if(i!=x/i)
                ans+=solve(x/i);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```


---

## 作者：Ivan422 (赞：1)

学校 S 组模拟题。

纪念洛谷 CF RMJ，它无了。

题面简单，不复述。

根据小学数学可得令 $\gcd(a,b)=g$，则 $\operatorname{lcm}(a,b)=gAB$，其中 $A$ 与 $B$ 互质。将其带入题面的式子，得到 $cgAB-dg=x$，提出 $g$ 就是 $(cAB-d)g=x$，两边除以 $g$ 就是 $cAB-d=\frac{x}{g}$。再根据前面 $A$ 与 $B$ 互质，可以枚举 $g$，就是 $x$ 的因数，按照计数的原理统计即可。时间复杂度主要在筛法上，线性筛或埃氏筛改装都可以。

```cpp
#include<bits/stdc++.h>
//#include<bits/extc++.h>
using namespace std;
//using namespace __gnu_pbds;
//#define arr array<int,3>
//#define int long long
//#define pb push_back
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=2e7+10,M=1010,P=1e9+7,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
int t,c,d,x,n,h[N],ans;
string FILE_NAME="pair";
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	freopen((FILE_NAME+".in").c_str(),"r",stdin);
	freopen((FILE_NAME+".out").c_str(),"w",stdout);
    cin>>t;
    for(int i=2;i<N;i++)if(!h[i]){for(int j=1;i*j<N;j++)h[i*j]++;}
    while(t--){
        cin>>c>>d>>x;ans=0;
        for(int gcd=1;gcd*gcd<=x;gcd++)if(x%gcd==0){
            if((x/gcd+d)%c==0)ans+=(1<<h[(x/gcd+d)/c]);
            if(x/gcd==x/(x/gcd))continue;
            if((x/(x/gcd)+d)%c==0)ans+=(1<<h[(x/(x/gcd)+d)/c]);
        }
        cout<<ans<<"\n";
    }
    return 0;
}
//note:cAB=x/gcd+d
//note:gcd(A,B)=1
```

---

## 作者：123zbk (赞：1)

首先设 $d_1 \times \gcd(a,b)=a,d_2 \times \gcd(a,b)=b$。

然后开始推式子。

$$c \times \frac{a \times b}{\gcd(a,b)}-d\times \gcd(a,b)=x$$

$$c \times \frac{d_1 \times \gcd(a,b) \times d_2\times \gcd(a,b)}{\gcd(a,b)}-d\times \gcd(a,b)=x$$

$$c\times d_1\times d_2\times \gcd(a,b)-d\times \gcd(a,b)=x$$

$$\gcd(a,b)\times (c\times d_1\times d_2-d)=x$$
 
所以

$$\gcd(a,b)=\frac{x}{c\times d_1\times d_2-d}$$

所以我们可以枚举 $\gcd(a,b)$，首先有 $\gcd(a,b)$ 是 $x$ 的因子。

然后可以推出 

$$d_1\times d_2=\frac{\frac{x}{\gcd(a,b)}+d}{c}$$

所以还需满足 $c$ 是 $\frac{x}{\gcd(a,b)}+d$ 的因子。

也就是说，我们枚举到了每一个 $d_1\times d_2$ 的值。

又因为现在我们相当于知道了 $\gcd(a,b)$，所以我们知道 $d_1$ 和 $d_2$ 有几种情况就知道对答案的贡献了。

将其分解质因数。

因为 $d_1=\frac{a}{\gcd(a,b)},d_2=\frac{b}{\gcd(a,b)}$，所以 $d_1$ 和 $d_2$ 一定是互质的。

那么分解质因数的结果就是，$d_1$ 和 $d_2$ 一定包含一种质因数的全部。设它有 $x$ 个质因子，因为每种质因数有两种选择，所以一共有 $2^x$ 次选择。把答案都加一起即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e7+5;
int prime[maxn],vis[maxn],T,ans,cnt;
void work()
{
    for(int i=2;i<maxn;i++)
    {
        if(not vis[i])
        {
            prime[++cnt]=i;
            vis[i]=1;
        }
        for(int j=1;j<=cnt and i*prime[j]<maxn;j++)
        {
            vis[i*prime[j]]=vis[i]+1;//质因数的个数 
            if(i%prime[j]==0)
            {
                vis[i*prime[j]]=vis[i];
                break;
            }
        }
    }
}
signed main()
{
    cin>>T;
    work();
    while(T--)
    {
        ans=0;
        int c,d,x;
        scanf("%lld%lld%lld",&c,&d,&x);
        for(int i=1;i*i<=x;i++)
        {
            if(x%i==0)//枚举 gcd 
            {
                int res1=i,res2=x/i;
                if((res1+d)%c==0)//d1*d2
                {
                    int dd=(res1+d)/c;
                    ans+=(1<<vis[dd]);
                }
                if(res1==res2)
                {
                	continue;
				}
				if((res2+d)%c==0)
                {
                    int dd=(res2+d)/c;
                    ans+=(1<<vis[dd]);
                }
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：violin_wyl (赞：1)

## The Number of Pairs

## 解析：

### 思路：

一般这中推式子的题，我们主要想到的是化简和转换之后优化枚举的复杂度，这道题也不例外。

首先可以很明显的发现，$x$ 一定是 $\gcd(a,b)$ 的倍数，考虑证明：

- $c\times lcm(a,b)=c\times \frac{a\times b}{\gcd(a,b)}=c\times a\times \frac{b}{\gcd(a,b)}$ 我们设 $p=\frac{a}{\gcd(a,b)},q=\frac{b}{\gcd(a,b)}$ ，则有原式变成 $c\times p\times q\times \gcd(a,b)-d\times \gcd(a,b)=x$ 不难发现前面是可以整除 $\gcd(a,b)$ 的。

很明显，如果我们枚举每个 $x$ 的因子，作为 $\gcd(a,b)$ 的值，我们设这个值为 $f$，则有：$p\times q = \frac{(f+d)}{c}$ ，而我们知道 $p\times q$ 实际上就是 $\frac{a}{\gcd(a,b)}\times \frac{b}{\gcd(a,b)}$ 不难发现 每一对 $p,q$ 都对应一对 $a,b$ ，而且 $\gcd(p,q)=1$ ，我们现在已知 $p\times q$  ，为了满足 $p,q$ 互质, 对于 $p\times q$ 的每一个质因子，我们都需要全部分给  $p$ 或者 $q$ ，则最终答案为 $2^{div(p\times q)}$ ，其中 $div$ 表示质因数的个数。

我们可以用线性筛求出所有数的质因子的个数，最终时间复杂度 $O(n+T\sqrt{n})$。

----------------------------------------------------

### code：

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M = 2e7;
const int mods = 998244353;
const int INF = 0x3f3f3f3f;
inline int read ( )
{
    int x = 0, f = 1;
    char ch = getchar ( );
    while (ch < '0' || ch > '9') {if (ch == '-') f = - 1; ch = getchar ( );}
    while (ch >= '0' && ch <='9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar ( );}
    return x * f;
}
int prime[M], divi[M], cnt;
bool is_prime[M];
void init ( )
{
    memset(is_prime, 1, sizeof (is_prime));
    is_prime[1] = 0;
    for (int i = 2; i <= M; i++)
    {
        if (is_prime[i]) prime[++cnt] = i, divi[i] = 1;
        for (int j = 1; j <= cnt && i * prime[j] <= M; j++)
        {
            is_prime[i * prime[j]] = 0;
            if (i % prime[j]) divi[prime[j] * i] = divi[i] + 1;
            else { divi[prime[j] * i] = divi[i]; break; }
        }
    }
}
int calc (int c, int d, int x, int f)
{
    int gcd = (f + d) / c;
    if (gcd * c != f + d) return 0;
    else return (1 << divi[gcd]);
}
int solve (int c, int d, int x)
{
    int q = sqrt (x), ans = 0;
    for (int i = 1; i <= q; i++) {
        if (x % i == 0) {
            ans += calc (c, d, x, i);
            if (x / i != i) ans += calc (c, d, x, x / i);
        }
    }
    return ans;
}
signed main()
{
    int T = read ( );
    init ( );
    while (T--)
    {
        int c, d, x;
        c = read ( ), d = read ( ), x = read ( );
        printf ("%lld\n", solve (c, d, x));
    }
    return 0;
}
```



---

## 作者：封禁用户 (赞：0)

[传送门](https://codeforces.com/problemset/problem/1499/D)

首先这个 $\operatorname{lcm}$ 肯定是要化成 $\gcd$，化掉后长这样：

$
\frac{c\ \times\ a\ \times\ b}{\gcd(a,b)}\ - d\ \times \gcd(a,b)=x
$

因为这个 $\gcd(a,b)$ 是个我们不想看到的变量，所以考虑把它化在一边，然后长这样：

$
\gcd(a,b)= \frac{x}{\frac{c\ \times\ a\ \times\ b}{\gcd^2(a,b)}\ -\ d}
$

那么由此可以看出 $\frac{c\ \times a\ \times b}{\gcd^2(a,b)}\ - d$ 是 $x$ 的因子。

于是设一下 $o=a\ \div \gcd(a,b)$，$p=b\ \div \gcd(a,b)$。

于是 $\gcd(a,b)= \frac{x}{c\ \times\ o\ \ \times\ p\ -\ d}$ 了。

然后考虑 $x$ 的每一个因子 $y$，

有 $o\times p=\frac{y+d}{c}$。

不难发现，$o$ 和 $p$ 一定互质，且只要 $o\times p$ 为整数就一定有解。

然后对于每个枚举的 $y$ 答案的贡献就是 $2$ 的 $\frac{y+d}{c}$ 的质因子个数数量。

然后用线性筛预处理一下就行了，对于每次提问枚举 $y$ 去算就完了。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,t,c,d,x,cnt;
int vis[20000001],a[20000001],pri[10000001];
long long ans;
void ycl(){
	for(int i=2;i<=20000000;i++){
		if(!vis[i]){
			pri[++cnt]=i;
			a[i]=1;
		}
		for(int j=1;j<=cnt&&pri[j]*i<=20000000;j++){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0){a[i*pri[j]]=a[i];break;}
			a[i*pri[j]]=a[i]+1;
		}
	}
}
int get(int gg){
	if((gg+d)%c) return 0;
	return 1ll<<a[(gg+d)/c];
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	ycl();
	while(t--){
		cin>>c>>d>>x;
		ans=0;
		for(int i=1;i*i<=x;i++){
			if(x%i==0){
				if(i*i!=x) ans+=get(x/i);
				ans+=get(i);
			}
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：lsj2009 (赞：0)

### Solution

小学奥数题。

考虑设 $g=\gcd(a,b),a'=\frac{a}{g},b'=\frac{b}{g}$，得：$ca'b'g+dg=x\Rightarrow a'b'=\frac{\frac{x}{g}-d}{c}$。

发现 $g$ 是 $x$ 的因数，我们可以 $\Theta(\sqrt{x})$ 去枚举他，然后由于 $a'b'$ 互质，也就是说 $y=\frac{\frac{x}{g}-d}{c}$ 的每个质因数要么属于 $a'$ 要么属于 $b'$，线性筛出其不同质因数个数 $\omega(y)$，然后答案就是 $\sum\limits_{x\equiv 0\pmod{g}} 2^{\omega(\frac{\frac{x}{g}-d}{c})}$，然后就做完了。

复杂度 $\Theta(x+T\sqrt{x})$。


### Code

```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=2e7+5,m=2e7;
bool is_prime[N];
vector<int> prime;
int f[N];
void init() {
    is_prime[1]=true;
    rep(i,2,m) {
        if(!is_prime[i])
            prime.push_back(i),f[i]=1;
        for(auto x:prime) {
            if(x*i>m)
                break;
            is_prime[i*x]=true;
            if(i%x==0) {
                f[i*x]=f[i];
                break;
            }
            f[i*x]=f[i]+1;
        }
    }
}
signed main() {
    init();
    int T;
    scanf("%d",&T);
    while(T--) {
        int c,d,x;
        scanf("%d%d%d",&c,&d,&x);
        int m=sqrt(x)+0.5,res=0;
        rep(i,1,m) {
            if(x%i==0) {
                if((x/i+d)%c==0)
                    res+=1<<f[(x/i+d)/c];
                if(x/i!=i) {
                    int t=x/i;
                    if((x/t+d)%c==0)
                        res+=1<<f[(x/t+d)/c];
                }
            }
        }
        printf("%d\n",res);
    }
    return 0;
}

```

---

## 作者：氧少Kevin (赞：0)

# CF1499D-The Number of Pairs
https://www.luogu.com.cn/problem/CF1499D

GCD、推式子

## 题意
有 $T(T\leq 10^4)$ 组用例。

给定三个整数 $c,d,x(1\leq c,d,x\leq 10^7)$。

问有多少对 $(a, b)$ 使得：
$$c\cdot \text{lcm}(a,b) - d\cdot \gcd(a , b) = x$$

## 思路

不难想到将式子化成：

$$c\cdot \frac{a\cdot b}{\gcd(a,b)} - d\cdot \gcd(a , b) = x$$

提取公因子，有：

$$ \gcd(a,b)\Big( c\cdot\frac{ a\cdot b}{\gcd^2(a,b)} - d \Big) = x $$

$$ \gcd(a,b)\Big( c\cdot\frac{a}{\gcd(a,b)}\cdot \frac{b}{\gcd(a,b)} - d \Big) = x $$

枚举 $\gcd(a,b)$，由于 $c,d,x$ 已知，所以可以求出 $\frac{a}{\gcd(a,b)}\cdot \frac{b}{\gcd(a,b)}$ 的值，设为 $x$。

不难看出，$\frac{a}{\gcd(a,b)}$ 与 $\frac{b}{\gcd(a,b)}$ 互质。

将 $x$ 分解质因数，如果 $x$ 有 $cnt$ 种质因数，那么对答案的贡献是 $2^{cnt}$。（原因：由于互质，所以 $\frac{a}{\gcd(a,b)}$ 与 $\frac{b}{\gcd(a,b)}$ 没有相同的质因子，因此对于每种质因子，有给前者和给后者两种选择）。

因此，答案 $=\sum_{} 2^{cnt\  \text{of}\ x}$。

---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF1499D](https://www.luogu.com.cn/problem/CF1499D)

* **【解题思路】**

我们令 $a'=\dfrac a{\gcd(a,b)},b'=\dfrac b{\gcd(a,b)}$。

于是

$$
\begin{aligned}
&c\operatorname{lcm}(a,b)-d\gcd(a,b)=x\\
\iff&ca'b'\gcd(a,b)-d\gcd(a,b)=x\\
\iff&ca'b'-d=\frac x{\gcd(a,b)}\\
\iff&a'b'=\frac{\dfrac x{\gcd(a,b)}+d}c
\end{aligned}
$$

枚举 $\gcd(a,b)$，问题就变为给定 $n$，求有多少种方案将 $n$ 拆成两个互质的数。显然这就是 $2^{\Omega(n)}$。线性筛预处理 $\Omega(n)$ 即可。

* **【实现细节】**

数组要开 $2\times10^7$。

* **【代码实现】**

```cpp
#include <iostream>
#include <bitset>
#include <array>

using namespace std;

array<int,20000001>	cntpfs;
array<int,2000000>	primes;
bitset<20000001>	isprime;

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int cntp=0;
	for(int i=2;i<=2e7;i++)
	{
		if(!isprime[i])
			primes[++cntp]=i,cntpfs[i]=1;
		for(int j=1;j<=cntp&&i*primes[j]<=2e7;j++)
		{
			isprime.set(i*primes[j]);
			cntpfs[i*primes[j]]=cntpfs[i];
			if(!(i%primes[j]))
				break;
			++cntpfs[i*primes[j]];
		}
	}
	int testcnt;
	cin>>testcnt;
	while(testcnt--)
	{
		int a,b,c,answer=0;
		cin>>a>>b>>c;
		for(int i=1;i*i<=c;i++)
			if(!(c%i))
			{
				if(!((c/i+b)%a))
					answer+=1<<cntpfs[(c/i+b)/a];
				if(i*i!=c&&!((i+b)%a))
					answer+=1<<cntpfs[(i+b)/a];
			}
		cout<<answer<<'\n';
	}
	return 0;
}

```

---

## 作者：kimi0705 (赞：0)

注：本文部分参考 [o1-preview](https://plus.aivvm.com/auth/login_share?token=fk-w9oTfdkPo63LbKtmr33F4kpNWYUhyzv2t1oyxB4k3bY)。

---

要高效解决这个问题，我们需要计算满足以下等式的所有整数对 $ (a, b) $ 的数量：

$$
c \times \text{lcm}(a, b) - d \times \gcd(a, b) = x
$$

**解题思路：**

**步骤1：等式变形**

利用最小公倍数和最大公约数的性质：

1. **表示 $ \text{lcm}(a, b) $ 和 $ \gcd(a, b) $：**

   $$
   \text{lcm}(a, b) = \frac{a \times b}{\gcd(a, b)}
   $$

   设 $ g = \gcd(a, b) $，则 $ a = g \times a' $，$ b = g \times b' $，其中 $ \gcd(a', b') = 1 $。

2. **将其代入原等式：**

   $$
   \begin{align}
   c \times \frac{a \times b}{\gcd(a, b)} - d \times \gcd(a, b) &= x \\
   c \times \frac{g a' \times g b'}{g} - d \times g &= x \\
   c \times g \times a' \times b' - d \times g &= x
   \end{align}
   $$

3. **化简等式：**

   $$
   \begin{align}
   g \times (c \times a' \times b' - d) &= x \\
   c \times a' \times b' - d &= \frac{x}{g}
   \end{align}
   $$

**步骤2：遍历 $ x $ 的所有正因数 $ g $**

由于 $ g $ 是 $ x $ 的因数，我们可以枚举 $ x $ 的所有正因数：

1. **对于每个因数 $ g $：**

   - 计算 $ y = \frac{x}{g} $。
   - 检查 $ \frac{y + d}{c} $ 是否为整数。
   - 如果不是整数，跳过当前 $ g $。

2. **求解 $ k = \frac{y + d}{c} $：**

   - 如果 $ k \leq 0 $，跳过当前 $ g $。
   - 因为 $ a' $ 和 $ b' $ 互质，且满足 $ a' \times b' = k $。

3. **计算互质数对 $ (a', b') $ 的数量：**

   - 对于给定的 $ k $，互质正整数对 $ (a', b') $ 的数量等于 $ 2^{t} $，其中 $ t $ 是 $ k $ 的不同质因数的个数。

**步骤3：累加结果**

对于每个满足条件的 $ g $ 和对应的 $ k $，将 $ 2^{t} $ 加入答案。

**实现细节：**

- **预处理最小质因数（SPF）：**

  - 使用埃拉托色尼筛法预处理 $ 2 \times 10^7 $ 以内的最小质因数。

- **质因数分解：**

  - 对 $ k $ 进行质因数分解，统计不同质因数的个数。

- **避免重复计算：**

  - 使用哈希或数组保存已计算的结果，减少重复计算。

**时间复杂度分析：**

- **预处理：**

  - 筛法预处理 SPF，时间复杂度为 $ O(N \log \log N) $。

- **每个测试用例：**

  - 枚举 $ x $ 的因数，数量为 $ O(\sqrt{x}) $。
  - 对于每个因数，质因数分解 $ k $，时间复杂度为 $ O(\log k) $。
  - 总体时间复杂度约为 $ O(T \times \sqrt{x} \times \log k) $。

**C++代码实现：**

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <thread>
using namespace std;

const int MAXN = 20000000;
int spf[MAXN + 1]; // 最小质因数

void sieve() {
    for (int i = 0; i <= MAXN; ++i)
        spf[i] = i;
    for (int i = 2; i * i <= MAXN; ++i) {
        if (spf[i] == i) { // i 是质数
            for (int j = i * i; j <= MAXN; j += i) {
                if (spf[j] == j)
                    spf[j] = i;
            }
        }
    }
}

vector<int> get_divisors(int n) {
    vector<int> divisors;
    for (int i = 1; 1LL * i * i <= n; ++i) {
        if (n % i == 0) {
            divisors.push_back(i);
            if (i != n / i)
                divisors.push_back(n / i);
        }
    }
    return divisors;
}

int count_distinct_prime_factors(int n) {
    unordered_map<int, int> factors;
    while (n > 1) {
        factors[spf[n]]++;
        n /= spf[n];
    }
    return factors.size();
}

void solve() {
    int T;
    cin >> T;
    sieve();
    while (T--) {
        int c, d, x;
        cin >> c >> d >> x;
        long long ans = 0;
        vector<int> divisors = get_divisors(x);
        for (int g : divisors) {
            int y = x / g;
            int numerator = y + d;
            if (numerator % c != 0)
                continue;
            int k = numerator / c;
            if (k <= 0)
                continue;
            int t = count_distinct_prime_factors(k);
            ans += 1LL << t;
        }
        cout << ans << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    thread t(solve);
    t.join();
    return 0;
}
```

**代码说明：**

- **`sieve` 函数：**

  - 使用埃拉托色尼筛法预处理每个数的最小质因数 `spf`。

- **`get_divisors` 函数：**

  - 获取整数 `n` 的所有正因数。

- **`count_distinct_prime_factors` 函数：**

  - 计算整数 `n` 的不同质因数的个数。

- **主函数 `solve`：**

  - 读取输入，对于每个测试用例，按照上述步骤计算答案。

- **多线程处理：**

  - 使用 `std::thread` 提高栈空间，防止递归过深导致栈溢出。

**注意事项：**

- **数据范围：**

  - 由于 $ x $ 最多为 $ 10^7 $，所以预处理到 $ 2 \times 10^7 $ 以确保安全。

- **64 位整数：**

  - 在计算过程中，可能涉及到大的整数，使用 `long long`。

- **性能优化：**

  - 使用 `unordered_map` 来统计质因数，效率更高。

---

