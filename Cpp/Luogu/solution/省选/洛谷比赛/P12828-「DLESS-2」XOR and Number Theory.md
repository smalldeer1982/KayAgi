# 「DLESS-2」XOR and Number Theory

## 题目描述

给出 $n,m$，对于所有满足以下两个条件的二元组 $(x,y)$，求 $x^2\bmod(y^2-xy)$ 的和：
- $1\le x< y\le n$
- $x\oplus y=\gcd(x,y)\le m$

其中 $\oplus$ 表示按位异或运算。

由于结果可能很大，所以答案对 $10^9+7$ 取模。

## 说明/提示

对于所有数据，保证：

- $1\le T\le 3000$
- $2\le n\le 10^9$
- $1\le m\le n$
- $1\le \sum m\le 10^5$

**本题采用打包测试**，各测试包描述如下：

| Subtask | $n\le$ | $\sum n\le$ | $\sum m\le$ | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $1000$ | $1000$ | $1000$ | $10$ |
| $2$ | $10^4$ | $10^4$ | $10^4$ | $10$ |
| $3$ | $10^7$ | $10^7$ | $10^5$ | $10$ |
| $4$ | $5\times10^7$ | $5\times10^7$ | $10^5$ | $20$ |
| $5$ | $10^9$ | $+\infty$ | $1000$ | $10$ |
| $6$ | $10^9$ | $+\infty$ | $5000$ | $10$ |
| $7$ | $10^9$ | $+\infty$ | $3\times 10^4$ | $10$ |
| $8$ | $10^9$ | $+\infty$ | $10^5$ | $20$ |


## 样例 #1

### 输入

```
3
8 3
11 3
114514 11451```

### 输出

```
7
13
184193935```

# 题解

## 作者：luanyanjia (赞：7)

神秘复杂度水过了。

先来看这个 $x \oplus y = \gcd(x,y)$，也就是 $x \oplus \gcd(x,y) = y$，我们发现对于一个 $d$，$x \oplus d \le x + d$。但是 $y > x$ 所以 $y$ 至少是 $x + d$，因此 $y = x + d$，此时若 $d \mid x$，则一定有 $\gcd(x,y) = d$。

在看这个神秘的一看就是凑出来的条件，将 $y$ 换成 $x + d$，$x$ 换成 $a \times d$ 得到：

$$ 
x^2 \bmod (y^2 - xy) \\
= x^2 \bmod (x^2 + 2xd + d^2 - x^2 -xd) \\
= x^2 \bmod d(d+x) \\
= a^2d^2 \bmod d^2(a+1) \\
= d^2(a^2 \bmod (a+1)) \\
= d^2
$$

贡献全都是 $d^2$，问题变成对每个 $d$ 求有多少个 $x$ 使得 $d \mid x \land d \operatorname{and} x = 0$，其中 $\operatorname{and}$ 是按位与。

我想过先 $O(3^{\log_2m})$ 枚举后面几位，但是由于我不会数论，所以后面不会 $O(1)$ 求就有点寄，所以可以考虑一些神秘的暴力。

显然有直接暴力，对于一个 $d$ 是 $O(\dfrac{n}{d})$ 的。

然后 $d$ 小的时候可以发现后面几位是有周期的，就可以记一下最后几位每一个状态是否被访问过，如果出现周期直接计算即可。复杂度 $O(d)$。

合起来就是 $\sum\limits_{i=1}^m{\min(i,\dfrac{n}{i})}$。居然可以通过。虽然 $n$ 再大一点就直接死了。

```cpp
inline void Solve(){
    rd(n,m);
    int ans=0;
    for(int d=1;d<B&&d<=m;d++){
        bt.reset();
        int cnt=0;
        for(int i=d,c=1;i+d<=n;i+=d,++c){
            int k=i&(B-1);
            if(bt[k]){
                --c;
                cnt+=((n-d)/d/c-1)*s[c]+s[((n-d)/d)%c];
                break;
            }
            bt[k]=1;
            s[c]=s[c-1];
            if((i&d)==0)++cnt,++s[c];
        }
        Add(ans,1ll*cnt*d%mod*d%mod);
    }
    for(int d=B;d<=m;d++){
        int cnt=0;
        for(int i=d;i+d<=n;i+=d)
            if((i&d)==0)++cnt;
        Add(ans,1ll*cnt*d%mod*d%mod);
    }
    printf("%d\n",ans);
}
```

---

## 作者：Gold14526 (赞：7)

我操，$O(3^{\log_2m})$ 彻底怒了。$O(3^{\log_2m})$ 指出了最核心的矛盾点：如果 $n$ 开到 $10^{18}$，$m$ 开到 $2\times 10^5$，或者把时限开到 $400\text{ms}$，怎么可能 $O(\sum \min(n,m^2))$ 轻轻松松直接通过？这确实是我的严重错误。我需要彻底承认 $n,m$ 开的不够大，或者时限开的不够小，想办法把 DLESS Round 糊弄过去。

---

做一点说明：$n\le5\times10^7$ 本来就是给 $O(n\log m)$ 做法的，但是怕不敢写，所以又给了个 $10^7$。

---

首先考察 $x\oplus y=\gcd(x,y)$ 的性质。

发现当 $y>x$ 时，$y\oplus x\ge y-x\ge \gcd(y,x)$，所以当 $y\oplus x=\gcd(y,x)$ 时，上述三个东西都相等，不妨设它们等于 $d$。

接下来考察 $x^2\bmod(y^2-xy)$，设 $x=x'd$，则 $y=(x'+1)d$，则：

$$
\begin{aligned}
x^2\bmod(y^2-xy) &= x^2\bmod y(y-x) \\
                 &= x'^2d^2\bmod (x'+1)d^2 \\
                 &= (x'^2\bmod (x'+1))d^2 \\
                 &= d^2
\end{aligned}
$$

事实上，这个无论怎么推都能推出来。

接下来是难点，考虑对所有的 $(x,y)$ 求 $d^2$ 之和。

$d^2$ 貌似并没有太好的性质，不过 $d\le 10^5$，这启发我们可以枚举 $d$，并计算 $(x,y)$ 的对数，此时我们可以这样简化条件：

- $d$ 是 $y$ 的因数。
- $d$ 在二进制下是 $y$ 的真子集（即二进制下 $d$ 为 $1$ 的位 $y$ 这一位也均为 $1$）。

对于 $d$，我们只要求出满足条件的 $y$ 的个数即可，$x$ 自然满足条件。

为了方便，对于第二个条件只考虑 $d$ 是 $y$ 的子集，最后再减去 $\sum_{i=1}^mi^2=\frac{1}{6}m(m+1)(2m+1)$ 即可。

接下来尝试建立子集与因数之间的关系，这看似很难，但是在 $d\le10^5$ 的情况下我们只枚举了 $d$ 本身，貌似还要接着枚举什么。

设 $h=\operatorname{highbit}(d)$，显然 $d$ 是否是 $y$ 的子集只跟 $y$ 的最低 $h$ 位有关，不妨考虑枚举 $y$ 的最低 $h$ 位 $p$，此时我们竟能惊人地建立起子集和因数之间的关系：

- $y\equiv 0\pmod{d}$
- $y\equiv p\pmod{2^h}$

EXCRT 求解的个数即可，可能需要预处理逆元做到 $O(m\log m+3^{\log_2m})$，用神秘的 $O(1)$ 求模 $2^m$ 下的逆元可以做到 $O(3^{\log_2m})$。

```cpp
#include<bits/stdc++.h>
#define cint const int
#define uint unsigned int
#define cuint const unsigned int
#define ll long long
#define cll const long long
#define ull unsigned long long
#define cull const unsigned long long
#define sh short
#define csh const short
#define ush unsigned short
#define cush const unsigned short
using namespace std;
int read()
{
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch-'0');
		ch=getchar();
	}
	return x;
}
void print(cint x)
{
	if(x<10)
	{
		putchar(x+'0');
		return;
	}
	print(x/10);
	putchar(x%10+'0');
}
void princh(cint x,const char ch)
{
	print(x);
	putchar(ch);
}
cint p=1e9+7;
int n,m;
int ans;
int inv[1000001],hb[1<<20|1],chb[1<<20|1];
void init()
{
	cint M=(1<<30)-1;
	for(int i=1;i<=1e6;i+=2)
	{
		int a=i,b=1;
		for(int j=1;j<=22;++j)
		{
			b=((1ll*b*a)&M);
			a=((1ll*a*a)&M);
		}
		inv[i]=b;
	}
	for(int i=1;i<=1<<20;++i)
	{
		hb[i]=max(hb[i-1],i&(-i));
		chb[i]=chb[i-1]+(hb[i]!=hb[i-1]);
	}
}
int calc(cint x,cint y,cint mod)
{
	cll d=((1ll*inv[x]*y)&(mod-1))*x;
	return (d>n?0:(n-d)/(1ll*x*mod)+1);
}
int base;
void solve()
{
	cint M=(1<<chb[m])-1;
	for(int i=1;i<=M;i+=2)
	{
		cint mod=(1<<chb[i]);
		for(int j=i;;j=((j-2)&i))
		{
			if(hb[j]!=hb[i])break;
			if(j>m)continue;
			ans=(ans+1ll*base*j*base*j%p*calc(j,i,mod))%p;
			if(j==1)break;
		}
	}
}
void doit()
{
	n=read();
	m=read();
	base=1;
	ans=-1ll*m*(m+1)*(m<<1|1)/6%p;
	while(m)
	{
		solve();
		base<<=1;
		n>>=1;
		m>>=1;
	}
	princh(ans,'\n');
}
int main()
{
	init();
	int T=read();
	while(T--)doit();
	return 0;
}

```

---

## 作者：Mirasycle (赞：4)

不妨设 $y\ge x$，首先有不等式 $x\oplus y\ge y-x$，还有 $\gcd(x,y)=\gcd(x,y-x)\le y-x$，所以当 $x\oplus y=\gcd(x,y)$ 的时候，可以得到这个值为 $y-x$。

以上两个式子的取等条件分别为 $x\subset y$ 和 $y-x\mid x$，第二个条件可以得到 $ky=(k+1)x$。利用这个化简 $x^2\bmod (y^2-xy)$ 可以得到其就是 $\gcd(x,y)$。

$n$ 非常大难以入手，可以考虑直接枚举 $d=y-x=\gcd(x,y)$，再枚举 $d$ 的倍数 $kd$，这个时候可以得到 $x=kd,y=(k+1)d$，验证是否有 $kd \oplus (k+1)d=d$ 即可，统计 $k$ 的个数为 $c$。让答案累加上 $c\times d^2$ 即可。这样子可以得到 $50 \rm pts$。

注意到上一个做法，我们并没有利用到 $kd\subset (k+1)d$ 这个条件。记 $2^w$ 为 $>d$ 的最小 $2$ 的次幂数，不难发现上述条件的成立只与 $k$ 的前 $w$ 位有关，于是对于 $k\bmod 2^w$ 有周期，直接计算是 $O(m^2)$ 的，可以拿到 $80 \rm pts$。模拟赛考场上止步于此。

但是赛后伟大的字典序队长 & 韩国队长 & 省队P话队长 FS_NEO 告诉我们，这个 $O(m^2)$ 的做法其实是可以拿下满分的。因为我们打个表找到规律（一个周期内的答案是 $2$ 的次幂），就可以 $O(1)$ 计算一个完整周期内的答案，然后对于不足一个周期的部分直接枚举算。虽然理论复杂度还是 $O(m^2)$，但是之前是要完整枚举一个周期，而这次只要枚举不足一个周期的一部分，跑不满，所以可以冲过去。再次拜谢 FS_NEO 爆杀紫题。

现在讲述正解，赛场上我的 $kd\subset (k+1)d$ 还是有点难看了，其实这个就是 $d\subset (k+1)d$。

得到 $d\subset (k+1)d$ 之后，我们直接枚举 $(k+1)d \bmod 2^w$ 要求其为 $d$ 的超集。记 $k=\log_2m$，原本枚举两个二进制数是 $2^k\times 2^k=4^k$ 的（也就是 $m^2$），但是我们枚举所有二进制数的所有超集，之后复杂度变成了 $O(3^k)$ 的！

对于 $(k+1)d\bmod 2^w=z$ 的 $k$ 计数，通过 $y=(k+1)d$ 可以得到

$$\begin{cases}
y\equiv 0\pmod d\\
y\equiv z\pmod {2^w}
\end{cases}$$

使用 ExCRT 求解个数即可。时间复杂度 $O(m\log m+3^{\log m})$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+10;
const int mod=1e9+7;
int n,m; int V(int x){ return x*x%mod; }
void exgcd(int a,int b,int& x,int& y){
	if(!b){ x=1; y=0; return ; }
	exgcd(b,a%b,y,x); y-=a/b*x;
}
void solve(){
	cin>>n>>m; int ans=0; m=min(n,m);
	ans=(ans-m*(m+1)*(2*m+1)/6%mod+mod)%mod;
	for(int d=1;d<=m;d++){
		int c=0,k=0;
		while((1<<k)<=d) k++;
		int full=(1<<k)-1,w=(1<<k);
		int nd=full^d,x,y;
		int D=__gcd(d,w),zw=w/D;
		exgcd(d/D,zw,x,y); x=(x%zw+zw)%zw; int P=d*zw;
		for(int s=nd;;s=(s-1)&nd){//y<=n
			int z=full^s; if(z%D){ if(!s) break; continue; }
			z/=D; int num=x*z%zw*d%P;
			if(n>=num) c=(c+(n-num)/P+1)%mod;
			if(!s) break;
		}
		ans=(ans+c*V(d))%mod;
	}
	cout<<ans<<endl;
}
signed main(){
	freopen("six.in","r",stdin);
	freopen("six.out","w",stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int T; cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：qczrz6v4nhp6u (赞：4)

$O(m\sqrt m)$ 做法，这不神奇吗。

### Solution

考虑一对 $(x,y)$（$x<y$），一个经典结论是 $y-x=(x\oplus y)-2(x\cap\neg y)\le x\oplus y$；而 $\gcd(x,y)=\gcd(y-x,x)\le y-x$，所以 $x\oplus y=\gcd(x,y)$ 当且仅当 $x\oplus y=y-x$ 且 $(y-x)|x$。

不妨设 $d=y-x$ 与 $x=kd,y=(k+1)d$，注意到上面的条件说明了 $x\cap\neg y=0$，所以 $x\subseteq y$，于是有 $d=x\oplus y\subseteq y$。所以说 $(kd,(k+1)d)$ 合法的充要即为 $d\subseteq (k+1)d$。

然后再来看看这个 $x^2\bmod(y^2-xy)$ 是什么东西。直接代入 $x=kd,y=(k+1)d$ 后有：

$$\begin{aligned}
&x^2\bmod(y^2-xy)\\
=&~k^2d^2\bmod((k+1)d^2)\\
=&~d^2(k^2\bmod (k+1))\\
=&~d^2
\end{aligned}$$

那很好了，现在我们要算的答案就是

$$\sum_{d=1}^md^2\sum_{k=2}^{\lfloor\frac nd\rfloor}[d\subseteq kd]$$

注意到 $m$ 很小，考虑直接枚举 $d$，算后面这一部分。

设 $l=\lfloor\log_2d\rfloor+1$，一个显然的观察是 $[d\subseteq kd]$ 是具有至多 $2^l$ 的循环节的，于是我们只需要快速计算 $\sum_{k=1}^r[d\subseteq kd]$（其中 $0\le r< 2^l$）即可得知原式的值。下文为方便先将 $d$ 不断除以 $2$ 直到 $d$ 为奇数，显然不影响答案。

先考虑 $r=2^l-1$（即没有 $r$ 的限制）的情况。考虑从低到高依次确定 $k$ 的第 $i$ 位。若 $d$ 的第 $i$ 位是 $0$，则 $k$ 的这一位显然是 $0$ 是 $1$ 都可以；若 $d$ 的第 $i$ 位是 $1$，则 $k$ 的这一位取决于当前 $kd$ 的第 $i$ 位：若当前 $kd$ 的第 $i$ 位是 $1$，则 $k$ 的第 $i$ 位只能为 $0$，否则只能为 $1$。

直接这样爆搜的复杂度显然为 $O(m^2)$，不过考虑到决策到第 $i$ 位时，只有 $kd$ 的 $i$ 位及以上部分有用，对这个记忆化一下就是 $O(m\sqrt m)$ 了，为啥呢？考虑前 $\frac l2$ 位，只有 $2^{\frac l2}=O(\sqrt d)$ 个状态可以到达；而后 $\frac l2$ 位因为记忆化的缘故也只有 $2^{\frac l2}=O(\sqrt d)$ 个状态，搜索一次的复杂度即为 $O(\sqrt d)$，总复杂度即为 $O(m\sqrt m)$。

上面的讨论都是基于 $r=2^l-1$ 给出的，但是也容易拓展到一般的情况：多设一维 $0/1$ 表示当前 $k\bmod 2^i$ 是否 $\le r\bmod 2^i$ 即可，复杂度仍为 $O(m\sqrt m)$。

### Code

哎哎，怎么跑的又没有官解快。大常数选手落泪了。

```cpp
bool Mst;
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
constexpr int N=131075,mod=1e9+7;
inline ll add(ll x,ll y){return (x+=y)>=mod&&(x-=mod),x;}
inline ll Add(ll &x,ll y){return x=add(x,y);}
inline ll sub(ll x,ll y){return (x-=y)<0&&(x+=mod),x;}
inline ll Sub(ll &x,ll y){return x=sub(x,y);}
inline ll qpow(ll a,ll b){
	ll res=1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1)res=res*a%mod;
	return res;
}
int n,m,f[2][N<<1];
inline int dfs(int i,int l,int d,int r,int k,int cur){
	int o=(cur>>i)|(1<<(l-i));bool op=(k&((1<<i)-1))<=(r&((1<<i)-1));
	if(i==l)return op;
	if(~f[op][o])return f[op][o];
	int res=0,tmp=(cur+((ll)d<<i))&((1<<l)-1);
	if((d>>i&1)<=(cur>>i&1))res+=dfs(i+1,l,d,r,k,cur);
	if((d>>i&1)<=(tmp>>i&1))res+=dfs(i+1,l,d,r,k|1<<i,tmp);
	return f[op][o]=res;
}
inline void clear(int i,int l,int d,int r,int k,int cur){
	int o=(cur>>i)|(1<<(l-i));bool op=(k&((1<<i)-1))<=(r&((1<<i)-1));
	if(i==l)return;
	if(!~f[op][o])return;
	int tmp=(cur+((ll)d<<i))&((1<<l)-1);
	if((d>>i&1)<=(cur>>i&1))clear(i+1,l,d,r,k,cur);
	if((d>>i&1)<=(tmp>>i&1))clear(i+1,l,d,r,k|1<<i,tmp);
	f[op][o]=-1;
}
inline int calc(int d,int r){
	if(!r)return 0;
	int l=__lg(d)+1;
	if(r<(1<<l)){
		int res=dfs(0,l,d,r,0,0);
		return clear(0,l,d,r,0,0),res;
	}
	else
		return calc(d,(1<<l)-1)*(r/(1<<l))+calc(d,r&((1<<l)-1));
}
void Solve(){
	cin>>n>>m;
	ll ans=0;
	for(int d=1;d<=m;d++){
		int x=d;
		while(!(x&1))x>>=1;
		Add(ans,(ll)d*d%mod*(calc(x,n/d)-1)%mod);
	}
	cout<<ans<<'\n';
}
bool Med;
int main(){
	cerr<<abs(&Mst-&Med)/1048576.0<<endl;
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	memset(f,-1,sizeof f);
	int _Test;cin>>_Test;
	while(_Test--)Solve();
	return 0;
}
```

---

