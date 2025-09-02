# Placing Rooks

## 题目描述

$\mathsf E \color{red}\mathsf{ntropyIncreaser}$ 是国际象棋大师。

有这样一个问题：

在 $n \times n$ 的国际象棋棋盘上放 $n$ 个车，要求满足两个条件：

- 所有的空格子都能被至少一个车攻击到。
- **恰好**有 $k$ 对车可以互相攻击到。

答案对 $998244353$ 取模。

$\mathsf E \color{red}\mathsf{ntropyIncreaser}$ 一眼就会了；但 NaCly\_Fish 太菜，并不会做，请你帮帮她吧。

## 说明/提示

$1\le n \le 2\times 10^5$，$0 \le k \le  \frac{n(n-1)}{2}$。

## 样例 #1

### 输入

```
3 2```

### 输出

```
6```

## 样例 #2

### 输入

```
3 3```

### 输出

```
0```

## 样例 #3

### 输入

```
4 0```

### 输出

```
24```

## 样例 #4

### 输入

```
1337 42```

### 输出

```
807905441```

# 题解

## 作者：optimize_2 (赞：21)

感觉其他题解都没说清楚怎么转化为斯特林数的 这里放一下我场上思路。

首先，要保证每行每列都能被攻击到，必须每行或者每列都有一辆车，假设每行都有一辆车，然后最终答案乘二。（$k = n$ 的时候每行和每列都有一辆车，特判一下）

证明：

假设第 $i$ 列没有车，因为每一个格子都要被攻击到，所以第 $i$ 列上的每一个格子都要被攻击到，因为第 $i$ 列上没有车，所以应该被同行的车攻击到，所以此时每一行都有车。

好所以我们钦定这个是行，就是说每一行都有车，然后求答案。

设 $cnt_i$ 为第 $i$ 列上车的数量。

总共有 $n$ 辆车，所以有 $\sum_{i = 1}^n cnt_i = n$。

因为每行都有一辆车，而且总共有 $n$ 辆车，所以每行有且仅有一辆车。

那么互相攻击的车对，一定是在同一列的。

这个就是植树问题了，第 $i$ 列上互相攻击的车有 $\max(cnt_i - 1, 0)$ 对。

所以 $k = \sum_{i = 1}^n \max(cnt_i - 1, 0)$。

我们发现 $n$ 和 $k$ 就差了一个 $\max$！

所以简单推导一下：

$$k + n = \sum_{i = 1}^n \max(cnt_i - 1, 0) + \sum_{i = 1}^n 1$$

$$= \sum_{i = 1}^n \max(cnt_i, 1)$$

然后再减去 $n$ ，得到

$$k + n - n = \sum_{i = 1}^n \max(cnt_i, 1) - \sum_{i = 1}^n cnt_i$$

$$ = \sum_{i = 1}^n [cnt_i = 0]$$

然后就发现 $k$ 就是 $cnt$ 中等于 $0$ 的个数。

所以 $n - k$ 就是 $cnt$ 中不为 $0$ 的个数，问题转化为在 $n - k$ 个有标号的盒子放 $n$ 个球球且每个盒子都要有球球的方案数，就是第二类斯特林数了。

---

## 作者：Yansuan_HCl (赞：15)

大家好，我不会斯特林数，于是我用容斥通过了本题。

手玩可以发现：

- 要想覆盖满整个棋盘，只可能是以下两种情况之一：
	- 每一列都有一个棋子；
    - 每一行都有一个棋子。
    - 显然这两种情况是旋转等价的。可以只算一种。

> 可以形象地理解。先构造出每一列都有棋子的情况，再把其中一列的棋子移动到另一列。
>
> 这时候，新增一列无法被攻击。当移动前不同时满足情况 1、2 时（即每行、每列都有一个棋子），总存在一行没有棋子。该行该列即无法被攻击。

其次，可以暂且把棋子按行的顺序开摆。

- 直接 $O(nk$) 进行 dp 是显然的。
- 相邻的、行相同的棋子可以互相攻击，行不同的则不能。任意重新排列，这些行相同的棋子仍然可以互相攻击。
- 那么要使恰好 $k$ 对互相攻击，则有 $n-k$ 个“间隔”，即 $n-k$ 种行。
- 由此可得 $k \ge n$ 时无解。

于是问题转化为：**把 $n$ 个不同棋子放入 $n-k$ 个不同盒子，每个盒子至少放一个**。

大力容斥，枚举有多少个空的，并把这些空的选出来，即可：

$$\sum_{i=0}^{n-k}\binom{n-k}{i}(-1)^i(n-k-i)^n$$

最后乘上 $\binom{n}{n-k}$ 选出哪些行即可。

当 $k=0$，情况 1、2 相同。否则答案需要乘 $2$。

```cpp
int main() {
    genFac();
    rd(n, k);
    if (k >= n) return puts("0"), 0;
    ll p = n - k;
    
    ll v = 0;
    U (i, 0, p) 
        (v += C(p, i) * qpow(p - i, n) % P * ((i & 1) ? (P - 1) : 1)) %= P;
    (v *= C(n, p)) %= P;
    if (k) (v *= 2) %= P;
    printf("%lld", v);
}
```

时间复杂度 $O(n \log n)$，瓶颈是快速幂。把 $i^n$ 用线性筛筛出来可以做到 $O(n)$，谔谔。

---

## 作者：NaCly_Fish (赞：12)

大眼观察可以发现：

>要攻击到每个格子，必须「每行都有棋子」或「每列都有棋子」。

简单反证一下就行，这里就不写了（

进一步可以推出：

> 当 $k \ge n$ 时，答案为 $0$。

根据第一条推论，想要能互相攻击到的棋子对数最多，就是把它们放在同行/同列，此时也只有 $n-1$ 对，于是得证。

那么假设每一行都有棋子，有 $m$ 列有棋子，则会产生 $n-m$ 对互相攻击（显然只有同列的可以互攻击到），直接得到 $m=n-k$。

这 $n$ 个不同行的棋子，放进 $n-k$ 个不同的列中，方案数显然是

$$\binom{n}{n-k}(n-k)! \begin{Bmatrix} n \\ n-k \end{Bmatrix}$$
在 $k \neq0$ 时，「每行都有棋子」和「每列都有棋子」一定不等价，所以答案就是上面的数 $\times 2$。

时间复杂度 $\text O( \max (n-k,1))$。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 200003
#define ll long long
#define reg register
#define p 998244353
using namespace std;

inline int power(int a,int t){
    int res = 1;
    while(t){
        if(t&1) res = (ll)res*a%p;
        a = (ll)a*a%p;
        t >>= 1;
    }
    return res;
}

int fac[N],ifac[N];

void init(int n){
    fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
    for(reg int i=2;i<=n;++i) fac[i] = (ll)fac[i-1]*i%p;
    ifac[n] = power(fac[n],p-2);
    for(reg int i=n-1;i;--i) ifac[i] = (ll)ifac[i+1]*(i+1)%p;
}

int pw[N],pr[N>>1];

void sieve(int n,int k){
    int cnt = 0;
    pw[1] = 1;
    for(reg int i=2;i<=n;++i){
        if(!pw[i]){
            pr[++cnt] = i;
            pw[i] = power(i,k);
        }
        for(reg int j=1;j<=cnt&&i*pr[j]<=n;++j){
            pw[i*pr[j]] = (ll)pw[i]*pw[pr[j]]%p;
            if(i%pr[j]==0) break;
        }
    }
}

int S(int n,int m){
    sieve(m,n);
    ll res = 0;
    for(reg int i=1;i<=m;++i){
        int g = (ll)pw[i]*ifac[i]%p*ifac[m-i]%p;
        res += (m-i)&1?p-g:g;
    }
    return res%p;
}

int n,k;

int main(){ // ans = 2 * \binom{n}{n-k} * S(n,n-k) * (n-k)!
    ll _k;
    scanf("%d%lld",&n,&_k);
    if(_k>=n){
        putchar('0');
        return 0;
    }
    k = _k;
    init(n-k);
    if(k==0){
        printf("%d",fac[n]);
        return 0;
    }
    int ans = 2ll*S(n,n-k)%p;
    for(reg int i=n;i>k;--i) ans = (ll)ans*i%p;
    printf("%d",ans);
}
```

---

## 作者：出言不逊王子 (赞：10)

好题。

首先我们考虑第一个条件：“所有的空格都能被至少一个车攻击到”。

也就是说，对于每个点，他所在的列或者他所在的行一定有一辆车控制着。

如果 $k$ 等于 $0$，那么这等价于这些车不会被相互攻击的方案数，对于第 $i$ 行有 $n-i+1$ 种选择的可能，最终的答案就是 $\prod_{i=1}^n n-i+1=\prod_{i=1}^n i$，即 $n$ 的阶乘。

如果 $k$ 不等于 $0$ 呢？

题目告诉我们有 $k$ 对车可以相互攻击，也就是说有一些车在同一行或者同一列，说明**肯定有空行或者空列**的存在。

那么剩下的一个维度必须是满的，要不然就会有点所在的行与所在的列都没有车控制着了。

因为行列等价，所以我们默认**每一行都有**车，在最终记算答案时将答案乘上 $2$ 即可。

接下来，考虑能相互攻击的对数是怎么来的。

我们发现，如果一个车和另一个车在同一行或者同一列，他们就能相互攻击。但是如果这两个车当中还有个兵呢？

那么这两个车要想攻击到对方，就必须先把这个兵给吃了，然后才能攻击到对方。

把兵换成车，道理是一样的。所以对于每一个非空列，它对答案的贡献就是列上车的数量 $cnt-1$，我们要让最终的答案等于 $k$。

一开始我们的 $k$ 是 $0$，所以整个答案都是 $0$。当 $k$ 变成 $1$ 时，我们要让一个棋子到任意一个其他列去让答案增加 $1$。

当 $k$ 变成 $2$ 时呢？我们要让一个棋子到任意一个其他列去让答案增加 $1$。

但是这时有两个细节：

- 这个棋子可以从当前棋子个数大于 $1$ 的列中来吗？不可以。否则的话，当他出来的那一刻答案又减少了 $1$。
- 这个棋子可以到空列中去吗？不可以。否则的话，他进去只会让空列减少 $1$，而我们把棋子拎出来已经让空列增加了 $1$，这一来一去等于说啥都没干。

以此类推，最终我们会取 $k$ 个棋子，与其他 $n-k$ 个棋子放在 $n-k$ 个非空列里，这里的方案数是第二类斯特林数取 $n=n,m=n-k$ 的方案数。

但是这 $n-k$ 个非空列要选出来，方案数是 $C_n^{n-k}$，而具体到每一列这个还能再转（因为斯特林数规定的是**相同**容器，而每一列是不同的），所以答案还要再乘上 $n-k$的阶乘。

哦对了，如果 $k\ge n$，说明就算掏空所有列还是没法满足条件，输出 $0$ 即可。

代码：
```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define int long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=2000000,inf=998244353ll;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
int ksm(int a,int b){
	int ans=1;while(b){if(b&1) ans=ans*a%inf;a=a*a%inf;b=b>>1;}
	return ans;
}
int n,m,ans,fac[N+1],inv[N+1],k,dnip;
int c(int d,int u){return fac[d]%inf*inv[u]%inf*inv[d-u]%inf;}
int stlin2(int n,int m){//n不同放m相同 
	int res=0,op=1;
	fs(i,0,m,1) res=(res+op*c(m,i)%inf*ksm(m-i,n)%inf+inf)%inf,op*=-1;
	return res*inv[m]%inf;
}
signed main(){
	fac[0]=inv[0]=1;
	fs(i,1,N,1) fac[i]=fac[i-1]*i%inf;
	inv[N]=ksm(fac[N],inf-2); 
	ft(i,N-1,1,-1) inv[i]=inv[i+1]*(i+1)%inf;
	n=read(),k=read();if(k>=n) return puts("0"),0;
	if(k==0) return printf("%lld",fac[n]),0;
	//dnip=inv[n-k];
	printf("%lld",2*stlin2(n,n-k)%inf*c(n,n-k)%inf*fac[n-k]%inf);
	return 0;
}
//假设每一行都有棋子 
//有k辆车放在第一列上，有k个可能，这k辆车可以相互攻击，那么要空出来几列
//如果一开始k=1，那么一个棋子要润走把ans+1，k=2那么另一个人还要润走 
//所以k+1，空的数量+1 
//那么n-k就是不为0的个数，这些球要搁到这n-k个列当中
//这n-k个列还能轮换 
```

---

## 作者：caidzh (赞：5)

$k\ge n$答案显然为$0$

首先考虑转化“恰好有$k$对车互相攻击”

如果要满足攻击到全部格的条件，那么必须满足每一行上或者每一列上都存在一个车

这时候有两个选择，一个是填满所有行，一个是填满所有列

$k=0$特判掉，接下来只考虑$k>0$的情况

由于$k>0$，所以上面两种选择只能满足一个，因此这两种情况是没有重叠的，而且一种填满行的情况对应着一种填满列的情况

这时只考虑填满行的情况是没有问题的，而这必须要满足的条件是：每行只能填一个车

发现一个重要性质，填了$i$个车但只有$j$列上存在车时，有恰好$i-j$对车互相攻击

然后就有一个十分 naive 的 dp，设$f_{i,j}$为填到第$i$行，只有$j$列存在车的方案数，转移：

$$f_{i,j}=jf_{i-1,j}+(n-j+1)f_{i-1,j-1}$$

答案为$2f_{n,n-k}$，无法通过此题

考虑这个问题的本质是：放$n$个车，使得这$n$个车恰好出现在$n-k$列上

此时不妨考虑先选出$n-k$个列去填，然后设$g_i$为出现列集合$i$的所有子集的答案，显然$g_i=|i|^n$

然后利用容斥原理可以简单地得到一个式子

注意到$|i|$大小固定的时候所有$g_i$及容斥系数一致，可以放到一起计算，最终答案为：

$$2\dbinom{n}{k}\sum_{j=0}^{n-k}(-1)^j\dbinom{n-k}{j}(n-k-j)^n$$

---

## 作者：wwlw (赞：5)

[Link](https://www.luogu.com.cn/problem/CF1342E)
--------------

### Solution

一共只有 $n$ 辆车，如果两两之间不攻击又要使所有空格子被攻击到，那么就是一个排列 $n!$。现在我们想使其中一对能互相攻击到，就需要将其中一辆车移到另一行或另一列，那么这辆车原来所在的行或列就会空出来，又要使每个空格子被攻击到，那么就要保证每一列或每一行都至少要有一辆车，所以计数的时候让每辆车对应一列或一行。

而且考虑一个很显然的性质，如果恰有 $k$ 对车能相互攻击，当且仅当有 $k$ 行没有车或者 $k$ 列没有车。那么问题就转换为了有恰好 $k$ 行或 $k$ 列没有车的方案数。很显然，这两个问题是等价的，所以只考虑行的情况，答案就是其的两倍。注意：若 $k=0$，则只能计算一次。而 $n$ 辆车最多有 $n-1$ 对能相互攻击，所以对于 $k\geq n$ 的，方案为 $0$.

剩下的就比较套路了，计数将 $n$ 个元素划分到 $k$ 个非空集合的方案数，容易发现这就是斯特林数。

```cpp
#include<stdio.h>
#define N 200007
#define ll long long

const int Mod = 998244353 ;

ll fac[N],inv[N];

ll qpow(ll x,ll y){
    ll ret=1,cnt=0;
    while(y>=(1LL<<cnt)){
        if(y&(1LL<<cnt)) ret=(ret*x)%Mod;
        x=(x*x)%Mod,cnt++;
    }
    return ret;
}

ll C(ll x,ll y){return x<y? 0:fac[x]*inv[y]%Mod*inv[x-y]%Mod;}

ll n,K;
int main(){
    //freopen("Data.in","r",stdin);
    fac[0]=1;
    for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
    inv[N-1]=qpow(fac[N-1],Mod-2);
    for(int i=N-2;~i;i--) inv[i]=inv[i+1]*(i+1)%Mod;
    scanf("%lld%lld",&n,&K);
    if(K>=n) printf("0");
    else{
        ll ans=0;
        for(int i=K,op=1;i<=n;i++,op=-op)
            ans=(ans+op*C(i,K)*C(n,i)%Mod*qpow(n-i,n)%Mod+Mod)%Mod;
        printf("%lld",!K? ans:ans*2%Mod);
    }
}
```

---

## 作者：Fuyuki (赞：5)

~~来看看我考场上的迷惑解法。~~

因为攻击范围要覆盖所有格子，所以可以假定每一行都有一个棋子，算出答案再乘上 $2$。注意特判 $k=0$ 的情况。

加上第 $i$ 列有 $a_i$ 个棋子，那么互相攻击的对数即为 $k=\sum \max\{0,a_i-1\}$，即如果有 $m$ 列有棋子，那么有 $k=n-m$。

那么就是把 $n$ 不同的球放到 $m$ 个不同的盒子里，每个盒子至少一个球。

这不就是生成函数吗？

单个盒子的生成函数 $F(x)=\sum_{i=1}^{\infty} \frac{1}{i!}x^i$，答案即为 $\binom{n}{m}[x^n]F(x)^m$。

那么多项式快速幂直接带走，复杂度 $O(nlogn)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define I inline int
#define V inline void
#define cint const int
#define ll long long int
#define isnum(ch) ('0'<=ch&&ch<='9')
#define FOF(i,a,b) for(int i=a;i<b;i++)
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ROF(i,a,b) for(int i=a;i>=b;i--)
#define gc (_op==_ed&&(_ed=(_op=_buf)+fread(_buf,1,100000,stdin),_op==_ed)?EOF:*_op++)
char _buf[100000],*_op(_buf),*_ed(_buf);
const int N=1<<20|1,mod=998244353;
V check(int&x){x-=mod,x+=x>>31&mod;}
I getint(){
	int _s=0;char _ch=gc;
	while(!isnum(_ch))_ch=gc;
	while(isnum(_ch))_s=_s*10+_ch-48,_ch=gc;
	return _s;
}
I Pow(ll t,int x){
	ll s=1;
	for(;x;x>>=1,t=t*t%mod)if(x&1)s=s*t%mod;
	return s;
}
namespace poly{
	int lmt(1),r[N],w[N],inv[N];
	V cl(int*op,int*ed){memset(op,0,ed-op<<2);}
	I getLen(int n){return 1<<32-__builtin_clz(n);}
	V rev(int*a,int n){FOF(i,0,n)if(a[i])a[i]=mod-a[i];}
	V mul(cint*a,int n,int x,int*c){FOF(i,0,n)c[i]=1ll*a[i]*x%mod;}
	V add(cint*a,cint*b,int n,int*c){FOF(i,0,n)check(c[i]=a[i]+b[i]);}
	V del(cint*a,cint*b,int n,int*c){FOF(i,0,n)check(c[i]=a[i]+mod-b[i]);}
	V dot(cint*a,cint*b,int n,int*c){FOF(i,0,n)c[i]=1ll*a[i]*b[i]%mod;}
	V init(int n){
		int l=-1,wn;inv[0]=inv[1]=1;
		while(lmt<=n)lmt<<=1,l++;
		FOF(i,0,lmt)r[i]=(r[i>>1]>>1)|((i&1)<<l);
		FOR(i,2,n)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
		wn=Pow(3,mod>>++l),w[lmt>>1]=1;
		FOF(i,(lmt>>1)+1,lmt)w[i]=1ll*w[i-1]*wn%mod;
		ROF(i,(lmt>>1)-1,1)w[i]=w[i<<1];
		lmt=__builtin_ctz(lmt);
	}
	V DFT(int*a,int l){
		static unsigned long long tmp[N];
		int u=lmt-__builtin_ctz(l),t;
		FOF(i,0,l)tmp[i]=a[r[i]>>u];
		for(int i=1;i<l;i<<=1)for(int j=0,d=i<<1;j<l;j+=d)FOF(k,0,i)
			t=tmp[i|j|k]*w[i|k]%mod,tmp[i|j|k]=tmp[j|k]+mod-t,tmp[j|k]+=t;
		FOF(i,0,l)a[i]=tmp[i]%mod;
	}
	V IDFT(int*a,int l){reverse(a+1,a+l),DFT(a,l),mul(a,l,mod-mod/l,a);}
	V mul(cint*a,cint*b,int l,int*c){
		static int X[N],Y[N];
		copy(a,a+l,X),copy(b,b+l,Y);
		DFT(X,l),DFT(Y,l),dot(X,Y,l,c),IDFT(c,l);
	}
	V Inv(cint*a,int n,int*b){
		static int tmp[N],d,l;
		for(d=1,l=2,b[0]=Pow(a[0],mod-2);d<n;d<<=1,l<<=1){
			copy(a,a+l,tmp),mul(tmp,b,l,tmp),cl(tmp,tmp+d);
			mul(tmp,b,l,tmp),copy(tmp+d,tmp+l,b+d),rev(b+d,d);
		}
		cl(b+n,b+d),cl(tmp,tmp+d);
	}
	V inte(int*a,int n){ROF(i,n-1,1)a[i]=1ll*inv[i]*a[i-1]%mod;a[0]=0;}
	V deri(int*a,int n){FOR(i,0,n-2)a[i]=1ll*(i+1)*a[i+1]%mod;a[n-1]=0;}
	V Ln(cint*a,int n,int*b){
		static int tmp[N],l;
		copy(a,a+n,tmp),deri(tmp,n),Inv(a,n,b);
		l=getLen(n+n-1),mul(tmp,b,l,b),inte(b,n);
		cl(tmp,tmp+n),cl(b+n,b+l);
	}
	V Exp(cint*a,int n,int*b){
		static int tmp[N],d,l;
		for(d=2,l=4,b[0]=1;d<n<<1;d<<=1,l<<=1){
			Ln(b,d,tmp),tmp[0]--,del(a,tmp,d,tmp);
			mul(b,tmp,l,b),cl(b+d,b+l),cl(tmp,tmp+d);
		}
		cl(b+n,b+d);
	}
}
int A[N],C[N],n,m,k;
int fac[N],inv[N];
I calc(int x,int y){
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
int main(){
// 	freopen("test.in","r",stdin);
	cin>>n>>k,poly::init(n+1<<1);
	inv[0]=inv[1]=1,fac[0]=1;
	FOR(i,2,n)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	FOR(i,1,n)fac[i]=1ll*fac[i-1]*i%mod,inv[i]=1ll*inv[i-1]*inv[i]%mod;
	if(k==0)return cout<<fac[n],0;
	if(k>=n)return cout<<0,0;
	m=n-k;
	FOR(i,0,n-1)A[i]=inv[i+1];
	poly::Ln(A,n+1,C);
	FOR(i,0,n)C[i]=1ll*C[i]*m%mod;
	FOR(i,n+1,n*2+1)C[i]=0;
	memset(A,0,sizeof(A));
	poly::Exp(C,n+1,A);
	cout<<1ll*A[n-m]*fac[n]%mod*calc(n,m)%mod*2%mod;
	return 0;
}
```

$O(n)$ 解法：因为 $F(x)=\frac{e^x-1}{x}$，所以：

$$F(x)^m=\frac{\sum_i \binom{m}{i}(-1)^ie^{ix}}{x^m}$$

因为 $[x^n]e^{kx}=\frac{n^k}{k!}$，那么就可以 $O(n)$ 计算了答案了。

---

## 作者：_zdc_ (赞：4)

第二个条件不好满足，所以可以选择从第一个条件入手。

画几张图可以发现，第一个条件满足当且仅当每一行都有车或每一列都有车。

证明：考虑反证法，假设有一行和一列没有车，那么它们的交点不会被攻击，与题意矛盾。

当 $k\ne0$ 时，我们假定每一行都有车，最后把答案 $\times2$。

令 $a_i$ 为第 $i$ 列上车的数量，有以下两个等式：

+ $\sum\limits_{i=1}^{n}a_i=n$
+ $\sum\limits_{i=1}^{n}\max(a_i-1,0)=k$

可以得出有且仅有 $n-k$ 个 $a_i\not=0$，选出这些列的方案数为 $C_n^k$。

于是问题转化为：$1\sim n$ 行每行有 $1$ 个车，车两两不同，将这些车放入 $n-k$ 个不同的集合里的方案数。当集合相同时，答案为 $\begin{Bmatrix}{n}\\{}n-k\end{Bmatrix}$，不同再乘 $(n-k)!$ 即可。

于是可以得出答案式子：
$$2\times C_n^k\times\begin{Bmatrix}{n}\\{}n-k\end{Bmatrix}\times(n-k)!$$

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define fir first
#define sec second
#define pii pair<int,int>
#define Mp make_pair
#define pb emplace_back
#define all(x) begin(x),end(x)
#define pli pair<ll,int>
using namespace std;
typedef long long ll;
typedef unsigned int ui;
const int N=2e5+5,inf=1e9,mod=998244353;
int n,k,mul[N],inv[N];
int qp(int x,int y){
    int base=x,res=1;
    for(;y;base=1ll*base*base%mod,y>>=1)
        if(y&1) res=1ll*res*base%mod;
    return res;
}
int getinv(int x){
    return qp(x,mod-2);
}
int C(int n,int m){
    return 1ll*mul[n]*inv[m]%mod*inv[n-m]%mod;
}
int getst(int n,int k){//得出斯特林数
    int res=0;
    for(int i=0;i<k;i++){
        int val=1ll*C(k,i)*qp(k-i,n)%mod;
        if(i&1) res=(res-val+mod)%mod;
        else res=(res+val)%mod;
    }
    return 1ll*res*inv[k]%mod;
}
void sol(){
    scanf("%d%d",&n,&k);
    if(k>n) return puts("0"),void();
    if(!k) return printf("%d\n",mul[n]),void();
    int res=1ll*C(n,k)*mul[n-k]%mod*getst(n,n-k)%mod;
    printf("%lld\n",2ll*res%mod);
    return;
}
int main(){
    mul[0]=1;
    for(int i=1;i<=N-5;i++) mul[i]=1ll*mul[i-1]*i%mod;
    inv[N-5]=getinv(mul[N-5]);
    for(int i=N-6;~i;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
    int T=1;
    // scanf("%d",&T);
    while(T--) sol();
    return 0;
}
```


---

## 作者：1saunoya (赞：4)

这个问题可以直接转化成，空出来 $k$ 列，只放在 $n-k$ 列上，这就等价于第二类斯特林数，然后空出来的k列是可以选的，所以再乘上一个组合数。

答案就是 $S2(n,n-k) \times \binom{n-k}{n}$。

然后注意到可以横着放竖着放，根据 k 的大小判断一下就好了...
```cpp
#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr int P = 998244353;
std::vector<int> fac, ifac;
int power(int x, int y) {
	int res = 1;
	while (y) {
		if (y & 1) {
			res = (i64)res * x % P;
		}
		x = (i64)x * x % P;
		y /= 2;
	}
	return res;
}
void initial() {
	constexpr int _ = 262144;
	fac.resize(_), ifac.resize(_);
	fac[0] = ifac[0] = 1;
	for (int i = 1; i < _; i++) {
		fac[i] = (i64)fac[i - 1] * i % P;
		ifac[i] = power(fac[i], P - 2);
	}
}
int binom(int x, int y) {
	if (x < y || y < 0) {
		return 0;
	} else {
		return (i64)fac[x] * ifac[x - y] % P * ifac[y] % P;
	}
}
int s2(int n, int m) {
	constexpr int sgn[2] = {1, -1};
	int res = 0;
	for (int k = 0; k <= m; k++) {
		res += (i64)sgn[k & 1] * binom(m, k) * power(m - k, n) % P;
		if (res >= P) {
			res -= P;
		}
		if (res < 0) {
			res += P;
		}
	}
	return res;
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	initial();
	int n, k;
	std::cin >> n >> k;
	if (k >= n) {
		std::cout << 0 << "\n";
	} else {
		int ans = s2(n, n - k);
		ans = (i64)ans * binom(n, n - k) % P;
		if (k == 0) {
			ans += 0;
		} else {
			ans *= 2;
			if (ans >= P) {
				ans -= P;
			}
		}
		std::cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：7KByte (赞：3)

容斥题。

前面的题解已经将问题转换为

>在$[1,n-k]$中选$n$个数，可以重复选，每种数至少选一次的方案数。



这里在解题的同时，总结一下容斥的模型。

第一种，集合求并模型。

给定$N$个集合，求这些集合的补集的元素个数。

标准的容斥模板。首先对于对每个集合的元素个数求和，然后减去所有两个集合的交集的元素个数，然后加上所有三个集合的交集的元素个数。


第二种，集合求补模型。

给定全集$U$和$N$个集合。求$N$个集合的并集对与$U$的补集。

在第一种模型下求出并集，一次简单容斥即可得到补集。

第三种，集合求交模型。

给定$N$个集合，求这些集合的交集的元素个数。

这里有两种做法。

第一种比较套路。首先我们确定一个合适的全集，然后对$N$个集合取一个补集。显然交集就是全集减去补集的并集。而补集的并集可以用第一种模型求出来。

第二种比较灵活。

第一种模型的公式为

$\large\left|\bigcup\right|=\sum\limits_{i}|S_i|-\sum\limits_{i<j}|S_i\cap S_j|+\cdots+(-1)^{n-1}\left|\bigcap S\right|$。

移项后只剩$|\bigcap S|$，如果我们提前知道并集的元素个数，就可以快速求出。

对于本题，我们划分集合$i$为选择了数$i$的方案构成的集合。

那么并集为$(n-k)^n$，而我们要每个数都至少选一次，就是集合求交集。知道了补集和集合，就可以用第三种模型求出交集的元素个数。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 500005
#define P 998244353
#define int long long
using namespace std;
int fac[N],inv[N];
int Pow(int x,int y){
	int now=1;
	for(;y;y>>=1,x=x*x%P)if(y&1)now=now*x%P;
	return now;
}
int C(int n,int m){return fac[n]*inv[m]%P*inv[n-m]%P;}
signed main(){
	fac[0]=inv[0]=1;
	rep(i,1,N-5)fac[i]=fac[i-1]*i%P,inv[i]=Pow(fac[i],P-2);
	int n,k;scanf("%lld%lld",&n,&k);
	int ans=0;
	if(k>=n){printf("%lld\n",0LL);return 0;}
	rep(i,0,n-k)ans+=C(n-k,i)*Pow(-1,i)%P*Pow(n-k-i,n)%P;
	printf("%lld\n",(ans%P+P)%P*C(n,k)%P*(k?2:1)%P);
	return 0;
}
```

---

## 作者：yimuhua (赞：3)

首先可以发现，若要满足条件一，则每一行或每一列都有车。

可以反证：若有一行一列没有车，则它们存在一个交点不会被攻击到。

可以发现行和列的情况是等价的，所以假设每一行都有车，最后答案再 $\times 2$。

设第 $i$ 列有 $a_i$ 个车，则第 $i$ 列有 $a_i-1$ 对可以互相攻击到的车。

所以有：

$\sum\limits_{i=1}^na_i=n$

$k=\sum\limits_{i=1}^n\max(a_i-1,0)$

观察第二个式子可以发现当 $a_i>0$ 时相较第一个式子减了 $1$，所以有 $n-k$ 个 $a_i>0$。

于是问题转化为将 $n$ 行每行一个、两两不同的车放入 $n-k$ 个不同的列。

就是第二类斯特林数乘上 $n-k$ 的阶乘。于是答案为：

$2\dbinom{n}{k}\begin{Bmatrix}n\\n-k\end{Bmatrix}(n-k)!$

用通项公式，时间复杂度为 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
int n, k, fac[200005] = {1}, inv[200005];
int fpow(long long x, int y) {
	long long s = 1;
	while(y) {
		if(y & 1)
			s = s * x % mod;
		x = x * x % mod, y >>= 1;
	}
	return s;
}
int c(int n, int m) {
	return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}
int S(int n, int m) {
	long long s = 0;
	for(int i = 0; i < m; i++)
		if(i & 1)
			s = (s - 1ll * c(m, i) * fpow(m - i, n) % mod + mod) % mod;
		else
			s = (s + 1ll * c(m, i) * fpow(m - i, n) % mod) % mod;
	return s * inv[m] % mod;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	for(int i = 1; i < 200001; i++)
		fac[i] = 1ll * fac[i - 1] * i % mod;
	cin >> n >> k, inv[200000] = fpow(fac[200000], mod - 2);
	if(k > n) {
		cout << 0;
		return 0;
	}
	if(!k) {
		cout << fac[n];
		return 0;
	}
	for(int i = 199999; ~i; i--)
		inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;
	cout << 2ll * c(n, k) % mod * S(n, n - k) % mod * fac[n - k] % mod;
	return 0;
}
```


---

## 作者：ThisIsLu (赞：2)

当 $k=0$ 时，答案显然为 $n!$。

考虑第一个条件，不难发现要么每一行有一辆车，要么每一列有一辆车，当 $k>0$ 时，必然只满足其中一个，所以可以分开计数。

不妨令第 $i$ 辆车位于 $(i,a_i)$。

那么可以互相可以攻击到车的数量为 $n$ 减去不同的 $a_i$ 数量。

所以不同的 $a_i$ 数量为 $n-k$。

这显然就是第二类斯特林数，最后乘上 $2\binom{n}{k}m!$ 即可。

关于第二类斯特林数：

定义 $m!{n \brace m}$ 为长度为 $n$ 的序列 $a$ ，使得 $a_i \in [1,m]$，且对于任意 $1 \le j \le m$，存在 $k$ 使得 $a_k=j$的数量。

则有

$$m^n=\sum_{i=1}^{m}\binom{m}{i}m!{n\brace i}$$

根据二项式反演，就有

$$m!{n \brace m}=\sum_{i=1}^{m}(-1)^{m-i}\binom{m}{i}i^n$$

code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
long long k;
const int N=2e5,P=998244353;
long long fac[N+5],inv[N+5];
int C(int x,int y){
    if(y<0||x<y) return 0;
    return fac[x]*inv[y]%P*inv[x-y]%P;
}
int fpow(long long p,int q){
    long long res=1;
    while(q){
        if(q&1) res=res*p%P;
        p=p*p%P;
        q>>=1;
    }
    return res;
}
signed main(){
    cin>>n>>k;
    fac[0]=fac[1]=inv[0]=inv[1]=1;
    for(int i=2;i<=n;i++){
        fac[i]=fac[i-1]*i%P;
        inv[i]=(P-P/i)*inv[P%i]%P;
    }
    for(int i=3;i<=n;i++) inv[i]=inv[i]*inv[i-1]%P;
    if(k>=n){
        cout<<0;
        return 0;
    }
    if(k==0){
        cout<<fac[n];
        return 0;
    }
    int ans=0;
    for(int i=1;i<=n-k;i++){
        ans+=C(n-k,i)*fpow(i,n)%P*(((n-k-i)&1)?-1:1);
        if(ans<0) ans+=P;
        if(ans>=P) ans-=P;
    }
    cout<<ans*2ll*C(n,k)%P;
    return 0;
}
```

update: 修改了关于第二类斯特林数的内容

---

## 作者：Aiopr_2378 (赞：2)

### 解题思路

发现问题的要求其实十分严格。注意到如果只放 $n$ 个车，并且要将 $n$ 行 $n$ 列全部覆盖，可能有一些性质。

由于一辆车只能横向和纵向攻击所在行列，如果对于一种方案，既有能够横向互相攻击的车，又有能有纵向互相攻击的车，那这样的方案一定不能覆盖整个棋盘。

感性证明：出现这种情况时，一定存在一行和一列，使得行列交点处有车，并且行和列还各有另外一辆车。发现交点处放的车对于覆盖情况产生不了任何贡献，而这样用了至少 $3$ 辆车只覆盖了 $2$ 行 $2$ 列，则欲覆盖满剩下的行列一定会少一辆车。

发现这个性质，进一步考虑只可能有两种合法的情况：

1. 每行各有一辆车，在 $i$ 列有车；
1. 每列各有一辆车，在 $i$ 行有车。

两种情况是相通的，只考虑一种情况，最后答案乘 $2$ 即可。但注意，如果 $k=0$，上述情况是对称的，答案不用乘 $2$。

考虑第一种情况。设 $g_i$ 表示**钦定**有 $i$ 对攻击车的方案数，容易发现，此时会在 $n-i$ 列放车（多放一列会少一对攻击车，思考不难）。对于放车的那些列，共有 $\binom n {n-i}$ 中选定情况，每种情况考虑 $n$ 行车放哪一列，有 $(n-i)^n$，故

$$
g_i=\binom n {n-i}(n-i)^n
$$

但是我们这样没有保证选定的 $n-i$ 列每列都有车，所计算的 $g_i$ 可能包含大于等于 $i$ 对攻击车的情况，考虑对其进行二项式反演。令 $f_i$ 表示**恰好**有 $i$ 对攻击车的方案数，显然有

$$
g_i=\sum_{k=i}^n\binom k i f_k
$$

有反演

$$
f_i=\sum_{k=i}^n\binom k i (-1)^{k-i}g_k
$$

所求的就是 $f_k$，如果 $k\not=0$ 则答案为 $2f_k$。

时间复杂度 $O(n\log n)$。

### 参考代码

```cpp
#include<iostream>
using namespace std;
#define MAXN 200005
#define mod 998244353
typedef long long ll;
int n,k;
ll g[MAXN],fac[MAXN],inv[MAXN],ans;
ll qpow(ll a,ll b){
    ll w=1;
    while(b){
        if(b&1) w=w*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return w;
}
inline ll C(ll n,ll m){
    if(m>n) return 0;
    if(!m||n==m) return 1;
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int main(){
    cin>>n>>k;
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    inv[n]=qpow(fac[n],mod-2);
    for(int i=n-1;i;i--) inv[i]=inv[i+1]*(i+1)%mod;
    for(int i=0;i<=n;i++) g[i]=C(n,n-i)*qpow(n-i,n)%mod;
    for(int i=k;i<=n;i++){
        if((i-k)&1) ans=(ans-C(i,k)*g[i]%mod)%mod;
        else ans=(ans+C(i,k)*g[i]%mod)%mod;
    }
    ans=(ans%mod+mod)%mod;
    if(k) ans=ans*2%mod;
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：睿智的憨憨 (赞：1)

# CF1342E Placing Rooks 解题报告

## 解法分析

若有一行无车，则所有列都要有一辆车才能使这行每一个格子都被覆盖。也就是说，要么每行一辆车，要么每列一辆车。

$k=0$ 时的答案就是 $n!$。

现在 $k>0$，考虑每行一辆车的情况：

若非空列有 $i$ 列，则会有 $n-i$ 辆车互相攻击，因此非空列有 $n-k$ 列。将 $n$ 辆车分给 $n-k$ 列，每列区分，并且每列非空，这不就是第二类斯特林数再乘上 $(n-k)!$ 吗，做完了。

给出 $k>0$ 时的答案，乘以 $2$ 是因为考虑行和考虑列等价：

$$2\binom{n}{n-k}(n-k)!{n \brace n-k}$$

时间复杂度 $O(n)$。

## 参考代码

```
#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define lowbit(x) (x&(-x))
using namespace std;
const int mod = 998244353;

int n;
ll K, fac[200010] = {1};

ll fpow(ll x, ll k){
	if (!k)
		return 1;
	ll t = fpow(x, k / 2);
	if (k & 1)
		return t * t % mod * x % mod;
	return t * t % mod;
}
ll mmi(ll x){
	return fpow(x, mod - 2);
}
ll C(int n, int m){
	ll res = 1;
	for (int i = n; i > n - m; i--)
		(res *= i) %= mod;
	for (int i = m; i >= 2; i--)
		(res *= mmi(i)) %= mod;
	return res;
}

int main(){
	scanf("%d %lld", &n, &K);
	if (K >= n){
		printf("0\n");
		return 0;
	}
	ll S = 0;
	for (int i = 1; i <= n - K; i++)
		fac[i] = fac[i - 1] * i % mod;
	for (int i = 1; i <= n - K; i++){
		if ((n - K - i) & 1)
			S -= fpow(i, n) * mmi(fac[i]) % mod * mmi(fac[n - K - i]) % mod;
		else
			S += fpow(i, n) * mmi(fac[i]) % mod * mmi(fac[n - K - i]) % mod;
		S = (S % mod + mod) % mod;
	}
	if (!K)
		printf("%lld\n", fac[n]);
	else
		printf("%lld\n", 2 * C(n, n - K) % mod * S % mod * fac[n - K] % mod);
	return 0;
}
```

---

## 作者：CaoXian (赞：1)

看了半天题始终看不明白为什么 `3 3` 的样例输出 `0`，后来才发现车不能穿过别的车/lh

教练布置的二项式反演练习题，做完之后发现原来这个东西叫斯特林数？

---

先特判 $k = 0$ 或 $k \geqslant n$ 的情况，分别输出 $n!$ 和 $0$，一个是全排列一个是无解。

每一行或者每一列肯定都有一个车，并且**如果有车能互相攻击到，那么要么都是攻击到同一列的车，要么都是攻击到同一行的车**，这一点可以随便举几个例子感受一下。

具体证明的话：假设存在三个车，它们的坐标分别为 $(x_0, y_0)$，$(x_1, y_1)$，$(x_1, y_0)$，现在有两行/两列被覆盖到了，所以可以直接不考虑这两行/两列，把剩下的格子看成大小 $(n - 2) \times (n - 2)$ 的棋盘，我们要用 $n - 3$ 个车覆盖 $(n - 2) \times (n - 2)$ 的棋盘，这是不可能的。

有更多的车的情况也肯定不可能了。

所以**要么每一行有且仅有一个车，某些车处于同一列从而产生互相攻击的关系；要么每一列有且仅有一个车，某些车处于同一行从而产生互相攻击的关系**。

下面讨论**每一行有且仅有一个车**的情况，因为棋盘是正方形的所以旋转一下就可以得到列的情况，最终答案乘 $2$ 即可。

令 $f(k)$ 表示**钦定/至少**有 $k$ 对可以互相攻击的车，令 $g(k)$ 表示**恰好**有 $k$ 对可以互相攻击的车。答案即为 $g(k)$。

由二项式反演（或者广义容斥原理）可以得到：

$$
f(k) = \sum\limits_{i = k}^{n}\binom{i}{k}g(i) \Leftrightarrow g(k) = \sum\limits_{i = k}^{n}(-1)^{i - k}\binom{i}{k}f(i)
$$

考虑如何计算 $f(i)$。

因为我们讨论的是每一行都有车的情况，所以车能互相攻击到一定是因为在同一列里。如果同一列有 $cnt$ 个车，那么会贡献 $cnt - 1$ 对能够互相攻击的车，**车的攻击判定是不能穿过别的车的**。

所以如果有 $i$ 对能够互相攻击到的车，那么肯定只有 $n - i$ 列上会有车。可以先选出是哪些列可以放车，再给每一行上的车分配它所在的列。所以 $f(i) = \binom{n}{n - i}(n - i)^{n}$。

直接计算 $g(k)$ 即可，时间复杂度 $\mathcal{O}(n \log n)$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 998244353;
ll n, k, ans, fct[200005], inv[200005];
ll ksm(ll x, ll y) {
	ll ret = 1;
	while(y) {
		if(y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}
ll c(ll n, ll m) {
	return fct[n] * inv[m] % mod * inv[n - m] % mod;
}
int gsm(int x) {return ((~x & 1) << 1) - 1;}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	fct[0] = 1;
	for(int i = 1; i <= 200000; ++i) fct[i] = fct[i - 1] * i % mod;
	inv[200000] = ksm(fct[200000], mod - 2);
	for(int i = 200000; i >= 1; --i) inv[i - 1] = inv[i] * i % mod;
	cin >> n >> k;
	if(k >= n) {
		cout << "0";
		return 0;
	}
	if(!k) {
		cout << fct[n];
		return 0;
	}
	for(int i = k; i <= n; ++i) {
		ans += gsm(i - k) * c(i, k) * c(n, n - i) % mod * ksm(n - i, n) % mod;
	}
	cout << (ans * 2 % mod + mod) % mod;
	return 0;
}
```

---

## 作者：happybob (赞：0)

如果 $k=0$，答案为 $n!$。

考虑 $k\neq 0$。

由于有彼此攻击的车，所以必然存在某行或者某列，其车的个数大于等于 $2$，或者说存在某行或者某列没有车。

但事实上如果同时存在至少一行和一列没有车，那么这行和列的交点是无法被任何车攻击到的，不满足限制 $1$。

所以答案必然形如行全满但有列空或者列全满但有行空。容易发现这两种答案相等，钦定行满列空，然后答案乘以 $2$ 就好。

考虑一列中可以互相攻击的车对数，设这列有 $c$ 个车，则对数是 $\max\{c-1,0\}$。设有 $x$ 列空，我们发现这 $n$ 个车互相攻击的对数是 $n-(n-x)$，又 $x<n$，所以当 $k\geq n$ 时无解，否则有 $x=k$ 列是空的。

直接把这 $k$ 列选出来，还剩 $n-k$ 列填，要求每列至少一个，本质等价于第二类斯特林数，容斥算下就好。

最终答案：$2 \times \dbinom{n}{k} \times ((n-k)^n+\sum \limits_{i=1}^{n-k} (-1)^i (n-k-i)^n \dbinom{n-k}{i})$。复杂度 $O(n \log n)$。

[Submission Link](https://codeforces.com/problemset/submission/1342/265972214)。

---

