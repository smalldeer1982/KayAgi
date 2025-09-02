# Assimilation IV

## 题目描述

Monocarp is playing a game "Assimilation IV". In this game he manages a great empire: builds cities and conquers new lands.

Monocarp's empire has $ n $ cities. In order to conquer new lands he plans to build one Monument in each city. The game is turn-based and, since Monocarp is still amateur, he builds exactly one Monument per turn.

Monocarp has $ m $ points on the map he'd like to control using the constructed Monuments. For each point he knows the distance between it and each city. Monuments work in the following way: when built in some city, a Monument controls all points at distance at most $ 1 $ to this city. Next turn, the Monument controls all points at distance at most $ 2 $ , the turn after — at distance at most $ 3 $ , and so on. Monocarp will build $ n $ Monuments in $ n $ turns and his empire will conquer all points that are controlled by at least one Monument.

Monocarp can't figure out any strategy, so during each turn he will choose a city for a Monument randomly among all remaining cities (cities without Monuments). Monocarp wants to know how many points (among $ m $ of them) he will conquer at the end of turn number $ n $ . Help him to calculate the expected number of conquered points!

## 说明/提示

Let's look at all possible orders of cities Monuments will be build in:

- $ [1, 2, 3] $ : 
  - the first city controls all points at distance at most $ 3 $ , in other words, points $ 1 $ and $ 4 $ ;
  - the second city controls all points at distance at most $ 2 $ , or points $ 1 $ , $ 3 $ and $ 5 $ ;
  - the third city controls all points at distance at most $ 1 $ , or point $ 1 $ .
  
   In total, $ 4 $ points are controlled.
- $ [1, 3, 2] $ : the first city controls points $ 1 $ and $ 4 $ ; the second city — points $ 1 $ and $ 3 $ ; the third city — point $ 1 $ . In total, $ 3 $ points.
- $ [2, 1, 3] $ : the first city controls point $ 1 $ ; the second city — points $ 1 $ , $ 3 $ and $ 5 $ ; the third city — point $ 1 $ . In total, $ 3 $ points.
- $ [2, 3, 1] $ : the first city controls point $ 1 $ ; the second city — points $ 1 $ , $ 3 $ and $ 5 $ ; the third city — point $ 1 $ . In total, $ 3 $ points.
- $ [3, 1, 2] $ : the first city controls point $ 1 $ ; the second city — points $ 1 $ and $ 3 $ ; the third city — points $ 1 $ and $ 5 $ . In total, $ 3 $ points.
- $ [3, 2, 1] $ : the first city controls point $ 1 $ ; the second city — points $ 1 $ , $ 3 $ and $ 5 $ ; the third city — points $ 1 $ and $ 5 $ . In total, $ 3 $ points.

 The expected number of controlled points is $ \frac{4 + 3 + 3 + 3 + 3 + 3}{6} $ $ = $ $ \frac{19}{6} $ or $ 19 \cdot 6^{-1} $ $ \equiv $ $ 19 \cdot 166374059 $ $ \equiv $ $ 166374062 $ $ \pmod{998244353} $

## 样例 #1

### 输入

```
3 5
1 4 4 3 4
1 4 1 4 2
1 4 4 4 3```

### 输出

```
166374062```

# 题解

## 作者：7KByte (赞：3)

期望题。

由于要求点数的期望，考虑将每个点的期望分开计算。

不难发现一种情况和一个长度为 $n$ 的排列一一对应，所以考虑当前点在多少个排列种被覆盖。

直接计算不好求，很套路的做法是求补集，考虑计算没有覆盖当前点。

如果没有覆盖当前点，那么排列的最后一位一定是距离 $\ge n+1$ 的点，倒数第二位一定是距离 $\ge n$ 的节点，依次类推。如果存在一个距离为 $1$ 的节点，则当前点一定被点亮。

这直接乘法原理计算即可。

时间复杂度 $\rm O(nm+m\log P)$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 50005
#define P 998244353
using namespace std;
int n,m,c[N][22];
int Pow(int x,int y){
	int now=1;
	for(;y;y>>=1,x=1LL*x*x%P)if(y&1)now=1LL*now*x%P;
	return now;
}
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n){
		rep(j,1,m){
			int x;scanf("%d",&x);
			c[j][x]++;
		}
	}
	int ed=0,fac=1;
	rep(i,1,n)fac=1LL*fac*i%P;
	rep(i,1,m){
		int sum=0,ans=1;
		pre(j,n,1)sum+=c[i][j+1],ans=1LL*ans*sum%P,sum--;
		ed=(ed+1-1LL*Pow(fac,P-2)*ans%P+P)%P;
	}
	printf("%d\n",ed);
	return 0;
} 
```

---

## 作者：monstersqwq (赞：3)

upd 2021.5.26:修复了评论区提出的小错

首先显然考虑每个点被是否被覆盖的期望，显然期望等于概率。

对于每个点，需要求出被覆盖的方案数除以总的方案数，后面的显然是 $n!$，它的逆元可以预处理。

发现需要求的是至少有一个纪念碑覆盖它的方案数，实际上，设当前点为 $u$，相当于考虑构造满足至少存在一个 $k$ 使得 $d_{p_k,u}\le n-k+1$ 的排列 $\{ p_1,p_2,p_3\cdots p_n\}$ 的个数，发现这个存在不好求，可以换成补集，即所有 $k$ 都满足 $d_{p_k,u}> n-k+1$ 的方案数，可以考虑从 $d_{p_k,u}$ 小的地方开始插入，这样前面插入的数一定会减少后面的一个方案数，直接乘法原理即可。

代码里加了点特判，都比较显然，比如存在距离该点为 $1$ 的纪念碑的话，那么该点就必然被覆盖。

没明白的话看代码：

```cpp
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<iostream>
#include<queue>
#include<map>
#include<cmath>
#include<ctime>
#define mod 998244353
using namespace std;
typedef long long ll;
ll qpow(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1) res=(res*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return res;
}
ll inv(ll a)
{
	return qpow(a,mod-2);
}
ll fac(int a)
{
	ll res=1;
	for(int i=1;i<=a;i++) res=(res*i)%mod;
	return res;
}
int n,m;
int d[25][50005];
ll ans=0;
bool vis[50005];
int pos[25];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&d[i][j]);
			if(d[i][j]==1) vis[j]=true;
		}
	}
	ll tmp=inv(fac(n));
	for(int i=1;i<=m;i++)
	{
		if(vis[i])
		{
			ans=(ans+1)%mod;continue;
		}
		ll res=1;
		for(int j=1;j<=n;j++)
		{
			pos[j]=d[j][i]-1;
		}
		sort(pos+1,pos+n+1);
		bool flag=false;
		for(int j=1;j<=n;j++)
		{
			if(pos[j]-j+1<=0)
			{
				flag=true;break;
			}
			res=res*(pos[j]-j+1)%mod;
		}
		if(flag)
		{
			ans=(ans+1)%mod;continue;
		}
		res=(res*tmp)%mod;
		ans=(ans+1-res+mod)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Little_RMQ (赞：2)

# CF1525E题解

这里介绍一种与其他题解不同的做法。

首先我们将贡献拆开，**对于每个点我们单独计算它被选中的概率在求和即为答案**。

## 那么如何求每个点被选中的概率呢？

我们考虑每轮每个点被选中的概率，我们可以把每个点**恰好**在第 $i$ 轮被选中的概率算出来，最后累加即为答案，于是我们先预处理出每个点在第 $i$ 轮能被几个城市覆盖到记为 $cnt_i$。然后对于 恰好在第 $i$ 轮选中即可表示为前 $i-1$ 轮都未选中的概率乘以第 $i$ 轮选中的概率。复杂度 $O(mn^2)$ 也可被前缀和处理 $cnt$ 数组优化为 $O(mn)$。

## 代码
```cpp
#include"bits/stdc++.h"
#define int long long
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define fir first
#define sec second
#define bp __builtin_popcount
using namespace std;
ll read() {
	ll x = 0, fff = 1;
	char c;
	while ((c = getchar()) < '0' || c > '9')
		if (c == '-')
			fff = -1;
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * fff;
}
const double eps = 1e-7;
const int N = 25;
const int M = 5e4 + 5;
const int V = 3e6;
const int mod = 998244353;
const int bse = 19260817;
const int inf = 1e18;
const double pi = acos(-1);
int n, m;
int d[N][M];
int cnt[N];
int qpow(int a, int b) {
	int res = 1;
	while(b) {
		if(b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}
int inv(int x) {
	return qpow(x, mod - 2);
}
signed main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) d[i][j] = read();
	int ans = 0;
	for(int i = 1; i <= m; i++) {
		memset(cnt, 0, sizeof(cnt));
		for(int j = 1; j <= n; j++)
			for(int k = 1; k <= n; k++) if(d[j][i] <= k) cnt[k]++;
		int res = 0, sum = 1;
		for(int j = 1; j <= n; j++) {
			int k = n - j + 1;
			res = (res + sum * cnt[k] % mod * inv(k) % mod) % mod;
			sum = sum * max(0ll, k - cnt[k]) % mod * inv(k) % mod;
		}
		ans = (ans + res) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：zimujun (赞：2)

题目中要求的是在控制操作序列完全随机的情况下，期望控制的点的个数。

由于每个点被控制之后对答案的贡献都是 $1$，因此答案可以转化为每个点被控制的概率之和，这些概率的计算相互独立，因此可以把每个点分开计算。

操作序列完全随机可以理解为控制操作序列可能为 $n$ 的全排列，每一个排列的出现概率相等，这个城市被控制的概率即为所有合法排列数与 $n!$ 的比值。

对于每个点 $u$ 计算合法排列数，一个合法排列 $\left\{p_1, p_2, \cdots, p_n\right\}$ 需要满足的条件是至少存在一个在 $[1, n]$ 内的整数 $k$，满足 $n - k + 1 \ge G_{p_k, u}$，其中 $G_{p_k, u}$ 表示城市 $p_k$ 到点 $u$ 的距离。

这个显然可以状压/容斥计算，但是这样的复杂度是 $\mathcal O\left(2^nm\right)$ 级别的，因为“至少存在” 的限制不是很好满足。

考虑补集转化，计算对于每个待控制点不合法的排列数。这样的限制条件就转变成了求对于任意的 $k$，$n - k + 1 < G_{p_k, u}$ 的排列数。

这样就可以通过往排列中逐渐插入新的元素的方式把这个排列构造出来。

因为距离为 $n + 1$ 的城市可以放在任何位置，距离为 $n$ 的城市不可以放在第一个位置，可以插入的位置逐渐减少而且可以插入的左端点右移。这样我们可以按照距离从大到小的顺序，从一个空排列开始向这个排列中逐渐插入元素，因为插入一个新的元素后，只有后面的元素会右移，这样不会影响排列的合法性。最后将所有元素的可插入位置总数相乘即得所有不合法排列数。这样计算的复杂度对于每个点都是 $\mathcal O\left(n\right)$ 的，总的复杂度为 $\mathcal O\left(nm\right)$。

用这种方法求得不合法的排列数，计算出合法排列数，再来计算概率即可。

如果计算逆元直接使用费马小定理，最后统计答案的复杂度和 $\mathcal O\left(nm\right)$ 同阶。

---

## 作者：Durancer (赞：1)

### 前言

需要基础期望知识的计数题目。

### 思路

题目中的比值直接看成边的长度即可，每秒钟一束光可以走 $1$ 个距离单位。

我们可以选择两个量进行计算，一个是 $n$ 即城市数，现在想到的最好方法是运用排列知识计算符合某条件的排列个数，但是要是进行计算相当困难。

题目中询问的是：在第 $n$ 秒时被瞬间点亮的点的个数的期望，那么可以换一个角度，从每一个点的角度求贡献。

对于每一个点，能够在第 $n$ 秒被点亮的情况有很多，并且循环查找的话会很麻烦，这里就需要一个计数的套路了，如果正面计数过于麻烦，那么我们可以从反面来考虑，也就是求在第 $n$ 秒不会被点亮的方案数。

如何来做？我们可以发现，对于一个点是否被点亮，可以通过点亮城市的顺序（$1-n$ 的一个排列，代表依次点亮哪一个城市）确定。

设 $dis_{i,j}$ 表示距离第 $i$ 个点 $j$ 个距离单位的点的个数。

第一个被点亮的城市，从这里出发的光束会走 $n$ 个距离单位，所以如果不想要被光束点亮，这个位置只能放距离当前枚举的点的距离单位为 $n+1$ 的城市，那么这里放上一个城市，第二个位置除了可以放 距离单位为 $n$ 的城市之外，还可以放 $dis_{i,n+1}-1$ 个城市。因此用计数器记录可以放的数目，乘法原理求出方案数来。

对于每一个点，求出的不能到达的方案数为 $\text{mul}$ ，对答案的贡献即为：

$$1-\frac{\text{mul}\times 1}{n!}\ \left(\bmod\ \  998244353 \right)$$


### 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define int long long 
using namespace std;
const int mod=998244353;
const int N=29;
const int M=5e4+9;
int dis[M][N+1];
int n,m;//城市数，点数
int ans;
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f-=1;s=getchar(); }
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
	return f*x;
}
int quick(int x,int p)
{
	int ret=1;
	while(p)
	{
		if(p&1) ret=ret*x%mod;
		x=x*x%mod;	
		p>>=1;
	}	
	return ret;
}
void get_ans()
{
	int fac=1;
	int sum=0,mul=1;
	for(int i=1;i<=n;i++)
		fac=fac*i%mod;
	for(int i=1;i<=m;i++)
	{
		sum=0;
		mul=1;
		for(int j=1;j<=n;j++)
		{
			sum+=dis[i][n+2-j];
			mul=1ll*mul*sum%mod;//累计不出现的个数。 
			sum--;//减去使用过的那个 
		}
		ans=(ans+1ll-(1ll*quick(fac,mod-2)%mod*mul%mod)%mod+mod)%mod; 
	}
}
signed main()
{
	n=read();
	m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			dis[j][read()]++;
	get_ans();
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：喵仔牛奶 (赞：0)

*2100 做了一万年 /oh

# Solution

显然每个点是独立的，每个点被同化的概率之和就是答案。

设城市 $i$ 被选择的时间是 $t_i$。点 $i$ 被同化的条件是「至少有一个城市 $j$ 满足 $c_j+p_i-1\le n$」。变为 $p_i\le n-c_j+1$，把 $c_j$ 变成 $n-c_j+1$，条件就成了「至少有一个城市 $j$ 满足 $p_i\le c_j$」。

“至少”难做，考虑求不合法的概率，即满足「所有有一个城市 $j$ 满足 $c_j<p_i$」。枚举 $i$，城市 $j$ 可以选的 $c_j$ 是一段前缀。从前往后扫，维护剩下能选的位置数 $x_t$，不合法概率即为 $d_i=\frac{1}{n!}\prod x_t$。而答案是 $m-\sum d_i$。

时间复杂度 $\mathcal{O}(nm)$。

# Code

```cpp
const int N = 22, M = 4e5 + 5, mod = 998244353;
typedef Math::Mint<mod> MI;
int n, m, ct[N], a[N][M]; MI rs;
int main() {
	cin >> n >> m;
	REP(i, 1, n) REP(j, 1, m) cin >> a[i][j];
	REP(i, 1, m) {
		MI d = 1; int x = 0;
		REP(j, 1, n) ct[a[j][i]] ++;
		REP(j, 1, n) {
			REP(t, 1, ct[j]) d *= x, x --;
			x ++, ct[j] = 0;
		}
		while (x) d *= x, x --;
		rs += d;
	}
	REP(i, 1, n) rs /= i;
	cout << (MI)m - rs << '\n';
	return 0;
}
```

---

## 作者：lsj2009 (赞：0)

### Solution

这种随机排列顺序的题一般考虑贡献。

我们考虑第 $i$ 个点在第 $n$ 秒被点亮的概率是多少；正难则反，考虑第 $i$ 个点在第 $n$ 秒不被点亮的概率是多少。

由于不被点亮，显然排列第 $n$ 个位置是距离第 $i$ 个点大于 $n$ 的点，第 $n-1$ 个位置是距离第 $i$ 个点大于 $n-1$ 的点，那么易得答案为：

$$\sum\limits_{i=1}^n 1-\frac{1}{\prod\limits_{j=1}^n ((\sum\limits_{k=1}^n [a_{i,k}> j])-(n-j))}$$

其中 $-(n-j)$ 表示我们倒序钦定点的顺序，然后后面已经被选了 $(n-j)$ 个，里面那个 $\sum$ 用后缀和易 $\Theta(1)$ 计算。

然后就做完了。

考虑到要计算逆元，复杂度为 $\Theta(nm+m\log{V})$，可以用线性逆元做到 $\Theta(nm)$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
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
const int N=5e4+5,M=25,MOD=998244353;
int cnt[N][M];
int qpow(int a,int b) {
	int res=1,base=a;
	while(b) {
		if(b&1)
			res=res*base%MOD;
		base=base*base%MOD; b>>=1;
	}
	return res;
}
signed main() {
	int n,m;
	scanf("%lld%lld",&n,&m);
	rep(i,1,n) {
		rep(j,1,m) {
			int val;
			scanf("%lld",&val);
			++cnt[j][val];
		}
	}
	int ans=0,tot=1;
	rep(i,1,n)
		tot=tot*i%MOD;
	rep(i,1,m) {
		int res=1,s=0;
		per(j,n,1) {
			s+=cnt[i][j+1];
			res=1ll*res*(s-n+j)%MOD;
		}
		ans=(ans+1-res*qpow(tot,MOD-2)%MOD+MOD)%MOD;
	}
	printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

## 大意

给出光从每一座城市到每一个点的用时，从第零秒开始，每隔一秒可以点亮一个未被点亮的城市，城市发出的光可以点亮点，求第 $n$ 秒的瞬间被点亮的点数的期望值。

## 思路

是一道不擅长的期望题！

首先我们对于每个点单独计算它被选中的概率，再求和即为答案。

我们发现一种情况和一个长度为 $n $ 的排列（即点亮城市的顺序)一一对应，所以考虑当前点在多少个排列中被覆盖。

如果有某座城市的光覆盖当前点，那么一定存在排列的第 $i$ 位是距离 $≤i $ 的城市。那么 $i$ 可能有很多个，我们要计算这种情况的情况数，我们很容易想到排列组合里的一个技巧——计算不成立的情况。

正难则反。直接计算不好求，那我们就考虑计算没有覆盖当前点。

如果没有覆盖当前点，那么排列的最后一位一定是距离 $>n$ 的城市，倒数第二位一定是距离 $>n-1$ 的城市，依次类推，我们直接乘法原理计算即可。注意，因为我们每座城市都会被点亮，所以如果有一个城市距离当前点的距离为 $1$，那么这个点一定会被点亮。

按照这种方法暴力，我们的复杂度为 $O(m\times n^2)$ 大概是 $2\times 10^7$，经过优化和桶计数，我们可以优化为 $O(nm)$。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Code  by  Ntsc .
       . Earn knowledge .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define int long long
#define db double
#define rtn return
using namespace std;

const int N=1e5+5;
const int M=1e5;
const int MOD=998244353;
const int INF=1e5;

int n,m,p,q,T,fac[N],ans;
int c[N][22];

int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%MOD;
		a=a*a%MOD;
		b>>=1;
	}
	return res;
}

int rd(){
	int t;
	cin>>t;
	return t;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		c[j][rd()]++;//c[j][k]表示离点j距离为k的点的个数
	}
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=(i*fac[i-1])%MOD;
	int inv=ksm(fac[n],MOD-2);
	for(int i=1;i<=m;i++){
		int sum=0,tmp=1;
		for(int j=n;j;j--){
			sum+=c[i][j+1];
			tmp=tmp*sum%MOD;
			sum--;
		}
		ans=(ans+1-inv*tmp%MOD+MOD)%MOD;//1为总方案的概率，inv*tmp为不合法的概率
	}
	cout<<ans<<endl;               
}
```




---

