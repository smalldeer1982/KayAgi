# [SDOI/SXOI2022] 进制转换

## 题目描述

小 D 两岁的时候就学会了进制转换。

所以他想问你，对于所有 $1\sim n$ 之间的数，这个数在二进制和三进制下的数位和分别是多少。

对于 $i$，记二进制和三进制的数位和分别为 $a(i)$ 和 $b(i)$。比如对于一个数 $i=114$，那么它二进制表示为 $(1110010)_2$，三进制表示为$(11020)_3$，那么 $a(i)$ 和 $b(i)$ 分别为 $4$ 和 $4$。

小 D 想知道你是不是真的能算对 $1$ 到 $n$ 里面所有数进制转换，所以想问你 $\sum\limits_{i = 1}^n x^i y^{a(i)} z^{b(i)}$ 是多少，由于答案很大，请输出答案对 $998244353$ 取模的结果。

## 说明/提示

### 数据规模与约定

本题共 $20$ 个测试点。

- 对于测试点 $1,2,3$，$n \le 10^7$。
- 对于测试点 $4,5$，$x=y=1$。
- 对于测试点 $6,7$，$y=1$。
- 对于测试点 $8,9,10$，$n<10^{10}$。
- 对于测试点 $11,12,13,14$，$n \le 5 \times 10^{11}$。

对于所有测试点，$1 \le n \le 10^{13}$，$1 \le x,y,z <998244353$。

## 样例 #1

### 输入

```
123456 12345 234567 3456789
```

### 输出

```
664963464
```

## 样例 #2

### 输入

```
1234567891 123 1 12345
```

### 输出

```
517823355
```

## 样例 #3

### 输入

```
9876543210987 1284916 83759265 128478129
```

### 输出

```
115945104
```

# 题解

## 作者：xtx1092515503 (赞：18)

考虑一个暴力的 DP：关于三进制 DP，令 $f_{i,j}$ 表示三进制意义下高于 $i$ 的信息已经确定，且已确定的数的二进制表达为 $j$，所有满足上述条件的数 $i$ 的 $x^iz^{b(i)}$ 之和。$y^{a(i)}$ 的系数可以在 $f_{-1,j}$ 处统计。

这个做法是 $O(n)$ 的，不可承受。

注意到三进制下填入后 $i$ 位时，只会影响二进制下最低的 $l_i$ 位，其中 $l_i$ 是满足 $2^{l_i}>3^{i+1}$ 的最小自然数。对于更高位的影响，其至多进一位。

于是我们可以把状态更新成 $f_{i,j,0/1}$，表示已确定的数的二进制表达的后 $l_i$ 位（也即模 $2^{l_i}$ 的结果）是 $j$，且向更高位无/有进位时的答案。

但是这个 DP 并没有任何实质性的改变……吗？

考虑 **根号分治**。高 $3^{m/2}$ 位一共只会访问根号个态；低 $3^{m/2}$ 位的状态总数是根号的；故只对低 $3^{m/2}$ 位记忆化，复杂度就是正确的根号。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;
int ksm(int x,ll y){int z=1;for(;y;y>>=1,x=1ll*x*x%mod)if(y&1)z=1ll*z*x%mod;return z;}
const int LG=28;
const int HF=14;
ll n;int X,Y,Z,py[1010],pz[1010];
ll tri[30];
int px[30][3],l[30],bd[30],sum[30],pc[1<<10];
int f[1<<25][2];
int dfs(int pos,ll num,bool car,bool lim){
	if(pos==-1){return !car?py[pc[num]]:0;}
	if(!lim&&pos<HF&&f[sum[pos]+num][car]!=-1)return f[sum[pos]+num][car];
	int res=0;
	for(int i=0;i<=(lim?bd[pos]:2);i++)for(int CAR=0;CAR<2;CAR++){
		ll NUM=num+tri[pos]*i+((ll)CAR<<l[pos]);
		if((NUM>=(1ll<<l[pos+1]))!=car)continue;
		NUM&=(1ll<<l[pos+1])-1;
		int PX=px[pos][i],PY=py[pc[NUM>>l[pos]]],PZ=pz[i];
		res=(1ll*dfs(pos-1,NUM&((1ll<<l[pos])-1),CAR,lim&&(i==bd[pos]))*PX%mod*PY%mod*PZ+res)%mod;
	}
	// printf("%d %d %d %d:%d\n",pos,num,car,lim,res);
	if(!lim&&pos<HF)f[sum[pos]+num][car]=res;
	return res;
}
int main(){
	freopen("conversion.in","r",stdin);
	freopen("conversion.out","w",stdout);
	scanf("%lld%d%d%d",&n,&X,&Y,&Z);
	for(int i=0;i<(1<<10);i++)pc[i]=pc[i>>1]+(i&1);
	py[0]=pz[0]=1;for(int i=1;i<=1000;i++)py[i]=1ll*py[i-1]*Y%mod,pz[i]=1ll*pz[i-1]*Z%mod;
	tri[0]=1;for(int i=1;i<=LG+1;i++)tri[i]=tri[i-1]*3;
	for(int i=0;i<LG;i++)px[i][0]=1,px[i][1]=ksm(X,tri[i]),px[i][2]=1ll*px[i][1]*px[i][1]%mod;
	for(int i=0;i<=LG;i++)while((1ll<<l[i])<=tri[i])l[i]++;
	// for(int i=0;i<=LG;i++)printf("%d ",l[i]);puts("");
	for(int i=0;i<HF;i++)sum[i+1]=sum[i]+(1<<l[i+1]);
	for(int i=0;i<LG;i++)bd[i]=(n/tri[i])%3;
	memset(f,-1,sizeof(f));
	printf("%d\n",(dfs(LG-1,0,false,true)+mod-1)%mod);
	return 0;
}
```

---

## 作者：dottle (赞：14)

提供一个波特思维的写法。

首先一个大体的思路应该是对于 $a(i),b(i)$ 都相同的我们一起计算答案。但是一个数在三进制和二进制下的数位几乎是没有什么关联的。也就是说我们必须要“暴力”地找这个对应关系。然后发现这个数据范围看起来就很根号，所以考虑折半法优化暴力。

考虑对三进制这边进行折半，分成了高位和低位。低位的数 $p$ 会对应一个 $
\sqrt n $ 级别的二进制数，高位的数 $q\times 3^B$ 会对应一个 $n$ 级别的二进制数。这时候 $x$ 和 $z$ 的次数很好算了，现在我们的目的是求出这个数的二进制数位数。注意到这个数的二进制高位与 $q\times 3^B$ 的要么相同，要么大一。因此可以做一个分类讨论，这样可以把二进制高位的位数算出来。然后把 $p$ 与 $q\times 3^B$ 合并的时候，二进制低位是卷积的形式，那直接 NTT 暴力卷就可以了。

那么可以调整 $B$ 的值，使得这个 $\log$ 带在根号下面。时间复杂度 $O(\sqrt {n\log n})$。

可以参考代码理解上述过程。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=531441,M=14348907,P=1<<20,mod=998244353;

void add(int&x,int y){
	x+=y;x%=mod;
}
int gsc(int x,int y){
    int ans=1;
    for(int i=1;i<=y;i<<=1,x=x*x%mod)
        if(y&i)
            ans=ans*x%mod;
    return ans;
}int inv(int k){return gsc(k,mod-2);}
int lim,r[P<<1];
const int G=3;
void initntt(int n){
	lim=1;while(lim<n)lim<<=1;
	for(int i=0;i<lim;i++)
		r[i]=(r[i>>1]>>1)|((i&1)*(lim>>1));
}
void ntt(int*a,int ty=1){
	for(int i=0;i<lim;i++)if(r[i]<=i)swap(a[i],a[r[i]]);
	int x,y;
	for(int i=1;i<lim;i<<=1){
		int o=gsc(ty==1?G:inv(G),mod/(i*2)),x,y;
		for(int j=0;j<lim;j+=i<<1)
			for(int k=0,w=1;k<i;k++,w=w*o%mod)
				x=a[j+k],y=a[j+k+i]*w,a[j+k]=(x+y)%mod,a[j+k+i]=(x-y)%mod;
	}
	if(ty==-1){
		int iv=inv(lim);
		for(int i=0;i<lim;i++)a[i]=(a[i]*iv%mod+mod)%mod;
	}
}

int n,x,y,z;
int py[M];
int a[P<<1],b[P<<1],c[P<<1];

int c2(int k){int res=0;while(k)res++,k-=k&-k;return res;}
int c3(int k){int res=0;while(k)res+=k%3,k/=3;return res;}

int calc(int k){
	return gsc(x,k)*gsc(y,c2(k))%mod*gsc(z,c3(k))%mod;
}

int res=0;

void solve(){
	cin>>n>>x>>y>>z;
	for(int i=n/N*N;i<=n;i++)res+=calc(i);//为了方便，把零散的部分暴力算好
	py[0]=1;for(int i=1;i<M;i++)py[i]=py[i-(i&-i)]*y%mod;
	n=n/N;res-=!!n;//会统计到 0，手动扣掉
	int X=1,_x=gsc(x,N),iz=inv(z);
	for(int i=0;i<N;i++)add(a[i],gsc(x,i)*gsc(z,c3(i)));
	for(int i=0;i<n;i++){
		int t=i*N;
		add(b[t&(P-1)],X*py[t/P]);//预设低位不进位
		add(c[t&(P-1)],X*py[t/P+1]);//预设低位进位
		X=X*_x%mod*z%mod;
		for(int j=i+1;j%3==0;j/=3)X=X*iz%mod*iz%mod;//线性地维护 x^t * z^b(i)
	}
	initntt(P<<1);
	ntt(a,1),ntt(b,1),ntt(c,1);
	for(int i=0;i<lim;i++){
		b[i]=b[i]*a[i]%mod;
		c[i]=c[i]*a[i]%mod;
	}
	ntt(b,-1),ntt(c,-1);
	for(int i=0;i<P;i++){
		res+=b[i]*gsc(y,c2(i))%mod;//没进位的用 b 算
		res+=c[i+P]*gsc(y,c2(i))%mod;//进位的用 c 算
	}
	cout<<(res%mod+mod)%mod<<endl;
}

main(){
	ios::sync_with_stdio(0);
	solve();
}

```

---

## 作者：玄燕本燕 (赞：10)

来描述一下 EI 做法。如有意会错误之处，望海涵。

不妨将题面中的 $1\le i\le n$ 改为 $0\le i\le n$。

为描述方便，提前声明最终时间复杂度为 $O(\sqrt n)$。

并设二阈值 $B_1=2^{c_1},B_2=3^{c_2}$ 使 $c_1,c_2\in \mathbf{N}^*,B_1=\Theta(\sqrt n),B_2=\Theta(\sqrt n)$。

对于原题面中的 $i$，分别枚举其在两个进制下的低位、高位，将所求转写为如下和式：
$$\sum_{i_1+B_1j_1=i_2+B_2j_2}a_1(i_1)a_2(j_1)b_1(i_2)b_2(j_2)$$
其中 $0\le i_1<B_1,0\le i_2<B_2$ 为所枚举低位。

而$a_1(i)=a_2(i)=y^{a(i)},b_1(i)=x^iz^{b(i)},b_2(i)=x^{iB_2}z^{b(i)}$。

为使求和不超过题面所述上界 $n$，可考虑对 $j_1$ 作限制 $0\le j_1<\left\lfloor\frac{n}{B_1}\right\rfloor$。此时 $i_1+B_1j_1$ 会恰取遍 $[0,\left\lfloor\frac{n}{B_1}\right\rfloor B_1)$ 中的每一个数。因此若在此条件下计算出上述和式，则我们只需枚举剩余不超过 $B_1$ 项即可得到最终答案。

计算和式的关键在于将和式中的限制移项为：
$$i_1-i_2=B_2j_2-B_1j_1$$
我们可以考虑分别计算
$$f_n=\sum_{i_1-i_2=n}a_1(i_1)b_1(i_2)$$
$$g_n=\sum_{B_2j_2-B_1j_1=n}a_2(j_1)b_2(j_2)$$
而 $-B_2<i_1-i_2<B_1$。因此分别计算两数列下标在**此区间**内的值即可。

先考虑算 $g$。先枚举 $j_2$，则由于 $B_1,B_2$ 同阶，使 $B_2j_2-B_1j_1$ 落在**此区间**内的 $j_1$ 仅有 $O(1)$ 个，因此暴力枚举即可做到 $O(\sqrt n)$ 的复杂度。

至于算 $f$，可以考虑逐位倍增计算：设我们当前计算出的 $f$ 是在 $0\le i_1<2^{d_1},0\le i_2<3^{d_2}$ 的限制下，欲将之倍增至 $0\le i_1<2^{d_1+1}$。由于函数 $a_1$ 具有良好的按位独立性质，可以得到如下递推式：
$$f'_n=f_n+a_1(2^{d_1})\times f_{n-2^{d_1}}$$
将 $3^{d_2}$ 倍增至 $3^{d_2+1}$ 方法类似。每次取 $2^{d_1}$ 与 $3^{d_2}$ 之较小者倍增，可保持 $2^{d_1}$ 与 $3^{d_2}$ 同阶，而使总复杂度做到 $O(\sqrt n)$。

注意在计算 $a_1$ 等函数时，不要由于快速幂或求各数位之和而使复杂度多带 $\log$，具体实现可见代码。由于算法常数很小，目前是最优解。
```cpp
#include<cstdio>
#include<numeric>
#include<cassert>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cstdlib>
using namespace std;

int read();
typedef long long ll;
#define fr(i,l,r) for(int i=(l);i<=(r);++i)
#define rf(i,l,r) for(int i=(l);i>=(r);--i)
#define fo(i,l,r) for(int i=(l);i<(r);++i)
#define foredge(i,u,v) for(int i=fir[u],v;v=to[i],i;i=nxt[i])
#define filein(File) freopen(File".in","r",stdin)
#define fileout(File) freopen(File".out","w",stdout)

const int N1=(1<<22)+5,N2=4782969+5,MOD=998244353;
ll qpow(ll a,int x) {
	ll z=1;
	for(;x;x>>=1,a=a*a%MOD)
		if(x&1) z=z*a%MOD;
	return z;
}
ll n,lim1,lim2,B1,B2;
int x,y,z,s1,s2,c1,c2;
ll f[N1+N2],g[N1+N2],tf[N1+N2];
void calcf() {
	ll len1=1,len2=1;
	f[N2]=1;
	while(len1<B1||len2<B2) if(len1<len2) {
		rf(i,len1-1,-len2+1) (f[i+len1+N2]+=f[i+N2]*y)%=MOD;
		len1*=2;
	} else {
		ll val=qpow(x,len2)*z%MOD;
		fr(i,-len2+1,len1-1) {
			ll tmp=f[i+N2]*val%MOD;
			(f[i-len2+N2]+=tmp)%=MOD;
			(f[i-len2*2+N2]+=tmp*val)%=MOD;
		}
		len2*=3;
	}
}
int d2[50],d3[30],cnt2,cnt3;
void init(ll x) {
	cnt2=cnt3=0; ll i;
	i=x; fo(j,0,44) cnt2+=d2[j]=i%2,i/=2;
	i=x; fo(j,0,28) cnt3+=d3[j]=i%3,i/=3;
}
void inc() {
	++d2[0]; ++d3[0]; ++cnt2; ++cnt3;
	fo(j,0,44) if(d2[j]>=2) d2[j]=0,++d2[j+1],cnt2-=1;
	else break;
	fo(j,0,28) if(d3[j]>=3) d3[j]=0,++d3[j+1],cnt3-=2;
	else break;
}
static ll pw2[50],pw3[60];
void calcg() {
	init(0);
	ll xB2=qpow(x,B2),xi=1;
	for(ll i=0;i<lim2;++i) {
		for(ll j=i*B2/B1;j<lim1&&i*B2-j*B1>-B2;++j)
			(g[i*B2-j*B1+N2]+=xi*pw3[cnt3]%MOD*pw2[__builtin_popcountll(j)])%=MOD;
		xi=xi*xB2%MOD;
		inc();
	}
}


int main() {
	cin>>n>>x>>y>>z;
	*pw2=1; fr(i,1,45) pw2[i]=pw2[i-1]*y%MOD;
	*pw3=1; fr(i,1,56) pw3[i]=pw3[i-1]*z%MOD;
	for(ll p1=1;p1<n;p1*=2) ++s1;
	for(ll p2=1;p2<n;p2*=3) ++s2;
	c1=s1+1>>1,c2=s2+1>>1;
	B1=1; fr(i,1,c1) B1*=2;
	B2=1; fr(i,1,c2) B2*=3;

	lim1=n/B1; lim2=n/B2;
	calcf(); calcg();
	ll ans=0;
	fr(i,-B2+1,B1-1) (ans+=f[i+N2]*g[i+N2])%=MOD;
	ll lim=min(lim1*B1,lim2*B2);
	init(lim);
	ll pw=qpow(x,lim%(MOD-1));
	for(ll i=lim;i<=n;++i) {
		(ans+=pw*pw2[cnt2]%MOD*pw3[cnt3])%=MOD;
		pw=pw*x%MOD; inc();
	}
	printf("%lld\n",(ans-1+MOD)%MOD);
	return 0;
}

const int S=1<<21;
char p0[S],*p1,*p2;
#define getchar() (p2==p1&&(p2=(p1=p0)+fread(p0,1,S,stdin))==p1?EOF:*p1++)
inline int read() {
	static int x,c,f;x=0;f=1;
	do c=getchar(),c=='-'&&(f=-1); while(!isdigit(c));
	do x=x*10+(c&15),c=getchar(); while(isdigit(c));
	return x*f;
}
```

---

## 作者：Leasier (赞：6)

$y = 1$ 可以直接数位 dp。

对于 $y$ 一般的情况，注意到我们很难同时维护两种进制的数，考虑一个更加暴力的想法。

设 $dp_{i, j, k = 0/1}$ 表示从高到低考虑到三进制下的第 $i$ 位，目前的值为 $j$，是否已经碰到上界的低位贡献之和。在 $i = -1$ 的边界处处理 $y$ 的贡献即可。

但这样做的时间复杂度为 $O(n \log_3 n)$。~~甚至跑不过暴力。~~

注意到当我们只需处理 $\leq i$ 位的贡献，这部分的和至多为 $3^{i + 1} - 1$，也就是说，除非向高位的后缀 $1$ 连续进位，其对 $j$ 的影响是很有限的。

令 $\operatorname{effect}_i = 2^{\lceil (i + 1) \log_2 3 \rceil}$，则在**已知是否进位**的情况下，我们可以将 $j$ 对 $\operatorname{effect}_i$ 取模。

改设 $dp_{i, j = 0/1, k, l = 0/1}$ 表示从高到低考虑到三进制下的第 $i$ 位，$j$ 表示是否对 $\operatorname{effect}_i$ 进位，目前的值模 $\operatorname{effect}_i$ 之后为 $k$，是否已经碰到上界的低位贡献之和。

转移时除了枚举当前这一位填啥，还需枚举接下来是否对 $\operatorname{effect}_{i - 1}$ 进位。

但直接从低到高位 dp 的时间复杂度为 $O(n)$。~~还是跑不过暴力。~~

考虑一个经典的分层优化：

- 设定阈值 $S \in [0, \lfloor \log_3 n \rfloor]$。
- 对于 $i \leq S$，我们直接从低到高位 dp，时间复杂度为 $O(\displaystyle\sum_{i = 0}^S \operatorname{effect}_i) = O(3^S)$。
- 对于 $i > S$，我们直接暴力 dfs，时间复杂度为 $O(3^{\log_3 n - S}) = O(\dfrac{n}{3^S})$。

令 $S = \frac{\log_3 n}{2}$ 取得最优时间复杂度为 $O(\sqrt{n})$。

我的代码中取 $S = 12$。实现时可以直接对小的部分记忆化。

代码：
```cpp
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef long long ll;

const int mod = 998244353;
const double log23 = 1.584962500721156;
int x, y, z;
int bit[37], f[37], powery[47], *dp[13][2];
ll effect[37], power3[37];
bool *vis[13][2];

inline int log(ll n, int m){
	return log(n) / log(m);
}

inline void init(ll n){
	int m = log(n, 3), k = log2(n) + 1;
	for (register int i = 0; i <= m; i++){
		bit[i] = (int)(n % 3);
		n /= 3;
	}
	for (register int i = 0; i <= m; i++){
		effect[i] = 1ll << (int)ceil((i + 1) * log23);
	}
	power3[0] = 1;
	for (register int i = 1; i <= m; i++){
		power3[i] = power3[i - 1] * 3;
	}
	f[0] = x;
	for (register int i = 1; i <= m; i++){
		f[i] = 1ll * f[i - 1] * f[i - 1] % mod * f[i - 1] % mod;
	}
	powery[0] = 1;
	for (register int i = 1; i <= k; i++){
		powery[i] = 1ll * powery[i - 1] * y % mod;
	}
	for (register int i = 0; i <= 12; i++){
		for (register int j = 0; j <= 1; j++){
			dp[i][j] = new int[effect[i]];
			vis[i][j] = new bool[effect[i]];
			memset(vis[i][j], 0, effect[i]);
		}
	}
}

inline int quick_pow(int x, ll p){
	int ans = 1;
	while (p){
		if (p & 1) ans = 1ll * ans * x % mod;
		x = 1ll * x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void add(int &x, int y){
	if ((x += y) >= mod) x -= mod;
}

int dfs(int cur, int go, ll rem, int limit){
	if (cur == -1) return go == 0 ? 1 : 0;
	if (cur <= 12 && limit == 0 && vis[cur][go][rem]) return dp[cur][go][rem];
	int up = limit == 0 ? 2 : bit[cur], coef = 1;
	ll nxt = cur == 0 ? 1 : effect[cur - 1], ans = 0;
	for (register int i = 0; i <= up; i++){
		int nlimit = limit & (i == up ? 1 : 0);
		ll p = rem + i * power3[cur], sum = 0;
		if (i > 0) coef = 1ll * coef * f[cur] % mod * z % mod;
		for (register int j = 0; j <= 1; j++){
			ll q = p + j * nxt;
			if ((q >= effect[cur] ? 1 : 0) == go){
				ll r;
				if (go == 1) q -= effect[cur];
				r = q & (nxt - 1);
				sum += 1ll * powery[__builtin_popcountll(q ^ r)] * dfs(cur - 1, j, r, nlimit);
			}
		}
		ans += sum % mod * coef;
	}
	ans %= mod;
	if (cur <= 12 && limit == 0){
		vis[cur][go][rem] = true;
		dp[cur][go][rem] = ans;
	}
	return ans;
}

inline int sub(int x, int y){
	return x - y < 0 ? x - y + mod : x - y;
}

int main(){
	int m;
	ll n;
	scanf("%lld %d %d %d", &n, &x, &y, &z);
	m = log(n, 3);
	init(n);
	printf("%d", sub(dfs(m, 0, 0, 1), 1));
	return 0;
}
```

---

## 作者：xay5421 (赞：4)

我们只考虑当前数字的的二进制低 w1 位和三进制低 w2 位，用一个二元组 $(a,b)$ 表示，其中 $0\le a<2^{w1},0\le b<3^{w2}$。

我们定义一个二元组是好的，当且仅当 $a$ 和 $b$ 之中有一个是 $0$。

我们定义一次 $+1$ 操作会让 $(a,b)$ 变成 $((a+1)\bmod 2^{w1},(b+1)\bmod 3^{w2})$。

我们定义一个好的二元组的后继二元组为重复执行 $+1$ 操作直到第一次变成好的二元组时的二元组，并记录经过的二元组的权值和。

我们找一对合适的 $w1,w2$ 使得 $2^{w1}$ 和 $3^{w2}$ 近可能接近 $\sqrt n$，然后不停跳后继二元组，每次直接把两个好的二元组之间的二元组的贡献算入答案，跳的过程中高位的贡献不变，低位的贡献已经预处理，跳一次复杂度是 $O(1)$ 的，总共跳 $O(\sqrt n)$ 次。

现在问题在与怎么找后继二元组和算经过的二元组的权值和。

容易发现，对于一个 $w1,w2$，好的二元组数量是 $2^{w1}+3^{w2}-1$， 因为 $a$ 和 $b$ 中有一个是 $0$。

途径的二元组的贡献不能暴力算，但是我们可以递归的从 $w1-1,w2$ 或者 $w1,w2-1$ 得到，我们每次取 $2^{w1}$ 和 $3^{w2}$ 中大的那个将指数减去 $1$，递归算。

总的复杂度差不多是 $O(\sqrt n)$

```cpp
#include<bits/stdc++.h>
#ifdef xay5421
#define D(...) fprintf(stderr,__VA_ARGS__)
#define DD(...) D(#__VA_ARGS__ "="),debug_helper::debug(__VA_ARGS__),D("\n")
#include"/home/xay5421/debug.hpp"
#else
#define D(...) ((void)0)
#define DD(...) ((void)0)
#endif
#define pb push_back
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define each(x,v) for(auto&x:v)
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
template<class T>void rd(T&x){int f=0,c;while(!isdigit(c=getchar()))f^=!(c^45);x=(c&15);while(isdigit(c=getchar()))x=x*10+(c&15);if(f)x=-x;}
template<class T>void pt(T x,int c=-1){if(x<0)putchar('-'),x=-x;if(x>9)pt(x/10);putchar(x%10+48);if(c!=-1)putchar(c);}
using namespace std;
using LL=long long;
using ULL=unsigned long long;
const int P=998244353;
int ad(int k1,int k2){return k1+=k2-P,k1+=k1>>31&P;}
int su(int k1,int k2){return k1-=k2,k1+=k1>>31&P;}
int mu(int k1,int k2){return 1LL*k1*k2%P;}
void uad(int&k1,int k2){k1+=k2-P,k1+=k1>>31&P;}
void usu(int&k1,int k2){k1-=k2,k1+=k1>>31&P;}
template<class... T>int ad(int k1,T... k2){return ad(k1,ad(k2...));}
template<class... T>int su(int k1,T... k2){return su(k1,ad(k2...));}
template<class... T>int mu(int k1,T... k2){return mu(k1,mu(k2...));}
template<class... T>void uad(int&k1,T... k2){return uad(k1,ad(k2...));}
template<class... T>void usu(int&k1,T... k2){return usu(k1,ad(k2...));}
int po(int k1,int k2){
	int k3=1;
	for(;k2;k2>>=1,k1=mu(k1,k1))if(k2&1)k3=mu(k3,k1);
	return k3;
}
const int N=5000005;
LL n;
int x,y,z;
LL pw2[50],pw3[30];
int pwx[N],pwy[50],pwz[60],cnt3[4782969];
inline int calc2(LL x){
	return __builtin_popcountll(x);
}
inline int calc3(LL x){
	return cnt3[x%4782969]+cnt3[x/4782969];
}
int get_sz(int w1,int w2){
	return pw2[w1]+pw3[w2]-1;
}
int get_id(int w1,int w2,int x,int y){
	assert(x==0||y==0);
	assert(x<pw2[w1]);
	assert(y<pw3[w2]);
	if(x==0)return y;
	return pw3[w2]+x-1;
}
void get_xy(int w1,int w2,int id,int&x,int&y){
	if(id<pw3[w2])x=0,y=id;
	else x=id-pw3[w2]+1,y=0;
}
vector<pair<int,int> >sol(int w1,int w2){ // 2:[0,2^{w1}) 3:[0,3^{w2})
	DD(w1,w2);
	if(w1==1&&w2==1){
		vector<pair<int,int> >ret(get_sz(w1,w2));
		rep(u,0,pw2[w1]-1){
			rep(v,0,pw3[w2]-1){
				if(u&&v)break;
				int u_=u,v_=v,step=0,sum=0;
				while(1){
					uad(sum,mu(pwx[step++],pwy[calc2(u_)],pwz[calc3(v_)]));
					++u_,++v_;
					if(u_==pw2[w1]||v_==pw3[w2])break;
				}
				if(u_==pw2[w1])u_=0;
				if(v_==pw3[w2])v_=0;
				ret[get_id(w1,w2,u,v)]=make_pair(get_id(w1,w2,u_,v_),sum);
			}
		}
		return ret;
	}
	if(pw2[w1]>pw3[w2]){
		vector<pair<int,int> >ret(get_sz(w1,w2));
		vector<pair<int,int> >old(sol(w1-1,w2));
		DD(w1,w2);
		rep(u,0,pw2[w1]-1){
			rep(v,0,pw3[w2]-1){
				if(u&&v)break;
				int u_=u,v_=v,step=0,sum=0;
				while(1){
					int cur=get_id(w1-1,w2,u_%pw2[w1-1],v_);
					int nex=old[cur].first;
					int u__,v__;
					get_xy(w1-1,w2,nex,u__,v__);
					
					uad(sum,mu(pwx[step],pwy[u_/pw2[w1-1]&1],old[cur].second));
					
					if(u__==0){
						step+=pw2[w1-1]-(u_%pw2[w1-1]);
						u_+=pw2[w1-1]-(u_%pw2[w1-1]);
					}else{
						step+=u__-(u_%pw2[w1-1]);
						u_+=u__-(u_%pw2[w1-1]);
					}
					if(v__==0){
						ret[get_id(w1,w2,u,v)]=make_pair(get_id(w1,w2,u_%pw2[w1],0),sum);
						break;
					}
					v_=v__;
					if(u_==pw2[w1]){
						ret[get_id(w1,w2,u,v)]=make_pair(get_id(w1,w2,0,v_),sum);
						break;
					}
				}
			}
		}
		return ret;
	}else{
		vector<pair<int,int> >ret(get_sz(w1,w2));
		vector<pair<int,int> >old(sol(w1,w2-1));
		DD(w1,w2);
		rep(u,0,pw2[w1]-1){
			rep(v,0,pw3[w2]-1){
				if(u&&v)break;
				int u_=u,v_=v,step=0,sum=0;
				while(1){
					int cur=get_id(w1,w2-1,u_,v_%pw3[w2-1]);
					int nex=old[cur].first;
					int u__,v__;
					get_xy(w1,w2-1,nex,u__,v__);
					
					uad(sum,mu(pwx[step],pwz[v_/pw3[w2-1]%3],old[cur].second));
					
					if(v__==0){
						step+=pw3[w2-1]-(v_%pw3[w2-1]);
						v_+=pw3[w2-1]-(v_%pw3[w2-1]);
					}else{
						step+=v__-(v_%pw3[w2-1]);
						v_+=v__-(v_%pw3[w2-1]);
					}
					
					if(u__==0){
						ret[get_id(w1,w2,u,v)]=make_pair(get_id(w1,w2,0,v_%pw3[w2]),sum);
						break;
					}
					u_=u__;
					if(v_==pw3[w2]){
						ret[get_id(w1,w2,u,v)]=make_pair(get_id(w1,w2,u_,0),sum);
						break;
					}
				}
			}
		}
		return ret;
	}
}
int main(){
#ifdef xay5421
	freopen("a.in","r",stdin);
#endif
	rep(i,1,4782968){
		cnt3[i]=cnt3[i/3]+i%3;
	}
	pw2[0]=1;
	rep(i,1,49)pw2[i]=pw2[i-1]+pw2[i-1];
	pw3[0]=1;
	rep(i,1,29)pw3[i]=pw3[i-1]*3;
	rd(n),rd(x),rd(y),rd(z);
	pwx[0]=1;
	rep(i,1,N-1)pwx[i]=mu(pwx[i-1],x);
	pwy[0]=1;
	rep(i,1,49)pwy[i]=mu(pwy[i-1],y);
	pwz[0]=1;
	rep(i,1,59)pwz[i]=mu(pwz[i-1],z);
	const int w1=21,w2=13;
	vector<pair<int,int> >ret(sol(w1,w2));
	LL val=0;
	int base=1;
	int ans=P-1;
	while(1){
		int u=val%pw2[w1];
		int v=val%pw3[w2];
		pair<int,int>now=ret[get_id(w1,w2,u,v)];
		int u_,v_;
		get_xy(w1,w2,now.first,u_,v_);
		LL val_;
		if(u_==0){
			val_=val+pw2[w1]-u;
		}else{
			val_=val+u_-u;
		}
		if(val_<=n){
			uad(ans,mu(base,now.second,pwy[calc2(val/pw2[w1])],pwz[calc3(val/pw3[w2])]));
		}else{
			while(val<=n){
				uad(ans,mu(base,pwy[calc2(val)],pwz[calc3(val)]));
				base=mu(base,x);
				++val;
			}
			break;
		}
		base=mu(base,pwx[val_-val]);
		val=val_;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Renshey (赞：3)

#### 题解

考虑拆位计算贡献，按 $3^B$ 将 $m=1 \sim n$ 拆为 $m=i+j\times 3^B$，则 $m$ 的贡献为 $x^my^{a(m)}z^{b(i)+b(j)}$。对于 $i,j$，可以限制 $i\in[0,3^B),j\in[0,\frac{n}{3^B})$，然后暴力计算 $[\lfloor\frac{n}{3^B}\rfloor]\times 3^B,n]$ 范围内的贡献。

容易发现上式是一个卷积形式的式子，问题在于 $m$ 的范围仍然是 $[0,n]$ 无法处理。考虑计算答案的过程，$x^m$ 可以拆为 $x^i\times x^{j\times 3^B}$，只有 $y^{a(m)}$ 还无法快速计算。由于 $a(m)=a(\lfloor \frac{m}{2^S}\rfloor)+a(m \bmod {2^S})$，前一部分只需要考虑是否进位，后一部分可以暴力循环卷积。因此对 $i$ 与 $j\times 3^B$ 做一次 $\operatorname{mod} 2^S$ 意义下的循环卷积即可。实际上可以通过 $\operatorname{mod} 2^{S+1}$ 意义下的循环卷积同时计算进位的答案。

时间复杂度 $O(B+\frac{n}{B}+S2^S)$，空间复杂度 $O(2^S)$，具体实现时可以取 $B=13,S=21$。

#### 代码

```cpp
#include <bits/stdc++.h>
const int mod = 998244353;
struct Power
{
	int x, BS[(1 << 15) + 1], GS[(1 << 15) + 1];
	inline int operator [] (long long x) {x %= mod - 1; return 1LL * GS[x >> 15] * BS[x & ((1 << 15) - 1)] % mod;}
	inline void init (int w)
	{
		BS[0] = 1; for (int i = 1; i <= (1 << 15); i++) BS[i] = 1LL * BS[i - 1] * w % mod;
		GS[0] = 1; for (int i = 1; i <= (1 << 15); i++) GS[i] = 1LL * GS[i - 1] * BS[1 << 15] % mod;
	}
} powx, powy, powz;
struct Bit {inline int operator [] (int x) {return __builtin_popcount(x);}} bit2;
const int S = 1 << 21, L = 21, B = 1594323, t = 1 << 22;
long long n; int x, y, z, ans, bit3[1 << 24], f[1 << 22], g[1 << 22], rev[1 << 22];
inline int power (int x, int y)
{
	int z = 1;
	for (; y; y >>= 1, x = 1LL * x * x % mod) if (y & 1) z = 1LL * z * x % mod;
	return z;
}
inline void NTT (int *a, int f)
{
	for (int i = 0; i < t; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	for (int i = 2; i <= t; i <<= 1)
	{
		int wn = power(~f ? 3 : 332748118, (mod - 1) / i);
		for (int j = 0; j < t; j += i) for (int k = 0, w = 1; k < i / 2; k++, w = 1LL * w * wn % mod)
		{
			int x = a[j + k], y = 1LL * w * a[j + k + i / 2] % mod;
			a[j + k] = (x + y) % mod; a[j + k + i / 2] = (x - y + mod) % mod;
		}
	}
	if (!~f) for (int i = 0, invt = power(t, mod - 2); i < t; i++) a[i] = 1LL * a[i] * invt % mod;
}
signed main()
{
	std::cin >> n >> x >> y >> z; powx.init(x); powy.init(y); powz.init(z);
	for (int i = 0; i < t; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (t >> 1) : 0);
	for (int i = 1; i < (1 << 24); i++) bit3[i] = bit3[i / 3] + i % 3;
	for (int i = 0; i < B; i++) f[i] = 1LL * powx[i] * powz[bit3[i]] % mod;
	for (int i = 0; i < n / B; i++)
	{
		long long w = 1LL * i * B; int w0 = w & (S - 1), w1 = w >> L;
		g[w0] = (g[w0] + 1LL * powx[w] * powy[bit2[w1]] % mod * powz[bit3[i]]) % mod;
		g[w0 + S] = (g[w0 + S] + 1LL * powx[w] * powy[bit2[w1 + 1]] % mod * powz[bit3[i]]) % mod;
	}
	NTT(f, 1); NTT(g, 1);
	for (int i = 0; i < t; i++) f[i] = 1LL * f[i] * g[i] % mod;
	NTT(f, -1);
	for (int i = 0; i < S; i++) ans = (ans + 1LL * f[i] * powy[bit2[i]]) % mod;
	for (long long i = n / B * B; i <= n; i++)
		ans = (ans + 1LL * powx[i] * powy[bit2[i & (S - 1)] + bit2[i >> L]] % mod * powz[bit3[i / B] + bit3[i % B]]) % mod;
	std::cout << (ans - 1 + mod) % mod << std::endl;
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

比较综合的题目。

考虑数位 DP。显然二进制和三进制之间关系比较复杂，所以我们对着三进制进行数位 DP。

我们一般处理的数位 DP 实际上是，考虑建一个 Trie 树，能够快速计算子树内的答案（因为往往子树内只有某个后缀是统一变化的），如图所示：

![](https://s21.ax1x.com/2025/03/15/pEacNYq.png)

将 $[1,k]$ 进行拆分。

也就是，我们确定了 $i$ 在三进制下的一段前缀，要对所有的后缀求和。

而对于不同的子树来说，他们有什么区别，什么共性呢？

1. $i$ 和 $b_i$ 是相同的。也就是我们要拼上 $[0,3^t)$ 的所有自然数作为后缀，这样根据前缀传进去的信息可以把 $x^i z^{b(i)}$ 给搞定了。
2. 二进制下 $\text{popcount}$ 是不同的。因为我们定好的前缀对每个二进制位都有贡献。那么实际上有 $O(V)$ 种本质不同的情况。

考虑后缀在二进制下有 $len$ 位。那么我们只需要按照前缀在二进制下的表示的后 $len$ 位划分等价类即可。因此在 $len$ 不是很离谱的情况下，我们可以进行一定的预处理：设 $dp_{len,ad,0/1}$ 表示，考虑长度为 $len$ 的所有三进制后缀，如果给他们加上 $ad$，影响到的贡献（他们在 $i$、$a(i)$、$b(i)$ 上贡献的部分。显然我们可以把上标拆成加法，那么最终是乘法就可以直接处理贡献了）。

预处理是不困难的，很容易给他们找到子问题的形式。

不过问题在于，假设三进制长度为 $k$，你大概就有 $O(3^k)$ 种状态。按照传统的子树划分方式，显然 $\le \log V$ 的每个 $k$ 都可能被使用。

这时候考虑**根号分治**，减少 $k$ 的上限，将子树划分的更加稠密一些。这样就可以做到 $O(\sqrt V)$ 复杂度了。

众所周知我的素质很低下，因此没有预处理一些东西，复杂度实际上变为了 $O(\sqrt V \log V)$，不过随便过。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=15,MAXM=2.1e6+10,MOD=998244353;
int n,x,y,z,ans,dp[MAXN][MAXM][2],hb[MAXN],pp[100];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}	
	return ans;
}
int f(int n) {int s2=0,s3=0,u=n;while(u) s3+=(u%3),u/=3;s2=__builtin_popcountll(n);return qpow(x,n)*qpow(y,s2)%MOD*qpow(z,s3)%MOD;}
void dfs(int mul,int len,int pre,int s3,int mx) {
	if(mul==1) {
		ffor(j,pre,pre+2) if(j<=n) ans=(ans+f(j))%MOD;
		return ;
	}
	if(n/(3*mul)*(3*mul)!=pre) {
		if(len<=13) {
			int ad=(pre&((1<<hb[len])-1)),ot=pre-ad;
			ffor(o,0,1) ans=(ans+dp[len][ad][o]*mx%MOD*qpow(z,s3)%MOD*qpow(y,__builtin_popcountll(ot+o*(1<<hb[len]))))%MOD;
			return ;
		}
		ffor(i,0,2) dfs(mul/3,len-1,pre+i*mul,s3+i,mx),mx=mx*pp[len-1]%MOD;
	}
	else {
		int v=(n/mul)%3;
		ffor(i,0,v) dfs(mul/3,len-1,pre+i*mul,s3+i,mx),mx=mx*pp[len-1]%MOD;
	}
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>x>>y>>z;
	ffor(i,1,13) {
		int mul=1;
		ffor(j,1,i) mul=mul*3%MOD;
		ffor(j,1,30) if((1<<j)>mul) {hb[i]=j;break ;}
	}
	ffor(i,0,30) pp[i]=qpow(x,pow(3,i));
	ffor(ad,0,3) ffor(j,0,2) dp[1][ad][(ad+j)>=4]=(dp[1][ad][(ad+j)>=4]+qpow(x,j)*qpow(z,j)%MOD*qpow(y,__builtin_popcount((ad+j)&3)))%MOD;
	ffor(len,2,13) {
		int pw=qpow(3,len-1),xx=qpow(x,pw);
		ffor(ad,0,(1<<hb[len])-1) {
			ffor(nw,0,2) {
				int nad=ad+nw*pw,gad=nad&((1<<hb[len-1])-1);
				ffor(o,0,1) {
					int tmp=dp[len-1][gad][o]*qpow(xx,nw)%MOD*qpow(z,nw)%MOD;
					int ot=((nad-gad)+(o<<hb[len-1]));
					dp[len][ad][ot>=(1<<hb[len])]=(dp[len][ad][ot>=(1<<hb[len])]+tmp*qpow(y,__builtin_popcount(ot&((1<<hb[len])-1))))%MOD;
				}
			}
		}
	}
	dfs(7625597484987,28,0,0,1);
	ans--;
	cout<<(ans%MOD+MOD)%MOD;
	return 0;
}
```

---

