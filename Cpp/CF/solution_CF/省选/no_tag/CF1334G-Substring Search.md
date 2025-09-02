# Substring Search

## 题目描述

You are given a permutation $ p $ consisting of exactly $ 26 $ integers from $ 1 $ to $ 26 $ (since it is a permutation, each integer from $ 1 $ to $ 26 $ occurs in $ p $ exactly once) and two strings $ s $ and $ t $ consisting of lowercase Latin letters.

A substring $ t' $ of string $ t $ is an occurence of string $ s $ if the following conditions are met:

1. $ |t'| = |s| $ ;
2. for each $ i \in [1, |s|] $ , either $ s_i = t'_i $ , or $ p_{idx(s_i)} = idx(t'_i) $ , where $ idx(c) $ is the index of character $ c $ in Latin alphabet ( $ idx(\text{a}) = 1 $ , $ idx(\text{b}) = 2 $ , $ idx(\text{z}) = 26 $ ).

For example, if $ p_1 = 2 $ , $ p_2 = 3 $ , $ p_3 = 1 $ , $ s = \text{abc} $ , $ t = \text{abcaaba} $ , then three substrings of $ t $ are occurences of $ s $ (they are $ t' = \text{abc} $ , $ t' = \text{bca} $ and $ t' = \text{aba} $ ).

For each substring of $ t $ having length equal to $ |s| $ , check if it is an occurence of $ s $ .

## 样例 #1

### 输入

```
2 3 1 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26
abc
abcaaba```

### 输出

```
11001```

# 题解

## 作者：λᴉʍ (赞：8)

来说一个骚操作

题目要求就是字符串匹配，设$|s|=|t|$，如果$s$匹配$t$，那么设$s_i=a,t_i=b$，必须满足$a=b$或$p_a=b$。

一种做法是推出$a,b$的贡献为$(a-b)^2(p_a-b)^2=0$，由于它一定非负所以只需求出$s,t$对应两个字符的贡献之和，为$0$就匹配上了。

拆开这个巨大的式子，每一项都形如$ca^rp_a^sb^t$。

将$s$串反转之后就容易可以用9轮FFT求出答案。注意这里的FFT长度设为$|t|$就够了。

（这种做法和字符集大小无关，比较优秀）

另一种方法是，暴力枚举26种$b$，直接暴力计算$a=b$和$p_a=b$的$(a,b)$对数。

反转$s$，只要用两个数组$S,T$，$S_i=[s_i=b\lor p_{s_i}=b],T_i=[t_i=b]$，直接卷积即可。

但是可以将两个字符放一起做，假设一起处理字符$p,q$，设$S_i=[s_i=p\lor p_{s_i}=p]+[s_i=q\lor p_{s_i}=q]i,T_i=[t_i=p]-[t_i=q]i$（有变量重名但能看懂，$S,T$最后乘的那个$i$是虚数单位）就可以减小一半常数，比较轻松地通过这题。

---

## 作者：EternalAlexander (赞：5)

将 $S$ 做置换之后的串为 $S'$，显然可以设匹配函数 $P(x) = \sum_{i=1}^m (T_{x-m+1} - S_i)^2 (T_{x-m+1} - S'_i)^2$ 然后做卷积匹配。

然而这个东西看起来好长好长，不想写。我们稍微勇敢一点，把那个平方扔掉， $P(x) = \sum_{i=1}^m (T_{x-m+1} - S_i)(T_{x-m+1} - S'_i)$ 。 这个东西当然是不对的，但是我们对每种字符的权值在 $[1, 998244353)$ 内均匀随机之后，这个东西大概率正确，可以看作是一种哈希的思想。

这样我们只需要计算一次多项式乘法，跑得飞快。

不过虽然A了，这个东西看起来还是不是很靠谱。求问一下有没有能确定性卡掉它的办法。

```cpp
#include <bits/stdc++.h>
#define maxn 1200005
typedef long long ll;
const int mod = 998244353;
const int g = 3;
int rev[maxn],n,m,A[maxn],B[maxn],C[maxn],P[maxn],F[maxn],G[maxn],H[maxn],Prx[maxn],
p[29],w[29],sum;
char S[maxn],R[maxn];

int sqr(int x){return (ll)x*x%mod;}

int qpow(int a,int b){
	if(b==0)return 1;
	ll d=qpow(a,b>>1);d=d*d%mod;
	if(b&1)d=d*a%mod;
	return d;
}

void NTT (int *a, int lim, int flag) {
	for (int i=1;i<lim;++i) rev[i] = (rev[i>>1]>>1) | ((lim>>1) * (i&1));
	for (int i=1;i<lim;++i) if (i<rev[i]) std::swap(a[i],a[rev[i]]);
	for (int i=1;i<lim;i<<=1) {
		int wn = qpow(g,(mod-1)/(i<<1));
		if (flag == -1) wn = qpow(wn,mod-2);
		for (int j=0;j<lim;j+=(i<<1)) {
			for (int k=0,w=1;k<i;++k,w=(ll)w*wn%mod) {
				int a1 = a[j+k], a2 = (ll) w * a[j+k+i] % mod;
				a[j+k] = (a1 + a2) % mod;
				a[j+k+i] = (a1 - a2 + mod) % mod;
			}
		}
	}if (flag == -1)
		for (int i=0,inv=qpow(lim,mod-2);i<lim;++i) a[i] = (ll) a[i] * inv % mod;
}

void conv(int len){
	std::memset ( C, 0, sizeof (C));
	int lim = 1; while (lim <= len + 2) lim <<= 1;
	NTT(A,lim,1); NTT(B,lim,1);
	for (int i = 0; i < lim; ++ i) C[i] = (ll) A[i] * B[i] % mod;
	NTT(C,lim,-1);
	std::memset( A, 0, sizeof(A));
	std::memset( B, 0, sizeof(B));
}

int main(){
	for(int i=1;i<=26;++i)scanf("%d",&p[i]);
	scanf("%s%s",R+1,S+1);
	n = std::strlen(S+1); m = std::strlen(R+1);
	std::reverse(R+1,R+m+1);
	for (int i = 1; i <= 26; ++ i) 
		w[i] = (rand() * 32768 + rand())%mod;
	for (int i = 1; i <= n; ++ i) {
		F[i] = w[S[i] - 'a' + 1];
		Prx[i] = (Prx[i-1] + (ll) F[i] * F[i] % mod) % mod;
	} for (int i = 1; i <= m; ++ i) {
		G[i] = w[p[R[i] - 'a' + 1]];
		H[i] = w[R[i] - 'a' + 1];
		sum = (sum + (ll)H[i] * G[i] % mod) % mod;
	}
	for (int i = 1; i <= m; ++ i) A[i] = (H[i] + G[i]) % mod;
	for (int i = 1; i <= n; ++ i) B[i] = F[i];
	conv(n+m);
	for (int j = 1; j <= n+m; ++j) P[j] = (P[j] - C[j] + mod) % mod;
	for (int j= m+1; j <= n+1; ++j) {
		P[j] = (P[j] + (Prx[j-1] - Prx[j-m-1] + mod) % mod) % mod;
		P[j] = (P[j] + sum) % mod;
	}for (int j = m+1; j <= n+1; ++j)printf("%d",P[j]==0);
	return 0;
}





```


---

## 作者：Fuyuki (赞：1)

两个字符匹配等价于 $(s_i-t_j)^2(s_i-p_{tj})^2=0$，那么两个字符串匹配就相当于 $\sum (s_i-t_j)^2(s_i-p_{tj})^2=0$。

将这个式子拆开，可以发现转化成了一个类似卷积的形式，而如果将 $t$ 翻转的话卷积后第 $i$ 位上的结果就表示了 $s$ 中以 $i$ 结尾的这个子串是否与 $t$ 匹配，那么用 NTT 求解即可，复杂度为 $O(nlog^2n)$。

额外的，因为 NTT 可以看做是在模大质数下进行 hash，所以会被 hack 数据卡掉。解决方法有几种，一是因为 $26^4\times10^5 \approx 4\times 10^{10}$，所以取两个模数一定不会被卡。二是给每个字符赋一个随机的权值，然后拿这个随机的权值去做卷积。三是随机 NTT 模数，但我感觉不如第一种方法好。

我的实现中采用了第二种方法，并且将上面的式子拆开后 $a$ 的幂次相同的项放到一起处理。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define I inline int
#define V inline void
#define ll long long int
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ROF(i,a,b) for(int i=a;i>=b;i--)
const int N=1<<19,mod=998244353;
char st[N];
int n,m,a[N],b[N],c[N],val[N];
int lmt,l,w[N],r[N],p[N],q[N],t[N];
V input(){
	FOR(i,1,26)scanf("%d",p+i);
	scanf("%s",st+1),m=strlen(st+1);
	FOR(i,1,m)b[m-i]=st[i]-'a'+1;
	scanf("%s",st+1),n=strlen(st+1);
	FOR(i,1,n)a[i]=st[i]-'a'+1;
}
I Pow(ll t,int x){
	ll s=1;
	for(;x;x>>=1,t=t*t%mod)if(x&1)s=s*t%mod;
	return s;
}
I o(){
	static mt19937 seed(time(0));
	return abs((int)seed());
}
V init(){
	for(lmt=1,l=-1;lmt<=n+m+1;lmt<<=1)l++;
	FOR(i,1,lmt-1)r[i]=r[i>>1]>>1|(i&1)<<l;
	int wn=Pow(3,mod>>++l);w[lmt>>1]=1;
	FOR(i,lmt/2+1,lmt-1)w[i]=1ll*w[i-1]*wn%mod;
	ROF(i,lmt/2-1,1)w[i]=w[i<<1];
	FOR(i,0,m-1)c[i]=p[b[i]];
	FOR(i,1,26)val[i]=o()%mod;
	FOR(i,1,n)a[i]=val[a[i]];
	FOR(i,0,m-1)b[i]=val[b[i]],c[i]=val[c[i]];
}
V DFT(int*a){
	static unsigned long long int tmp[N];
	FOR(i,0,lmt-1)tmp[i]=a[r[i]];
	for(int i=1,x;i<lmt;i<<=1)for(int j=0,d=i<<1;j<lmt;j+=d)FOR(k,0,i-1)
		x=tmp[i|j|k]*w[i|k]%mod,tmp[i|j|k]=tmp[j|k]+mod-x,tmp[j|k]+=x;
	FOR(i,0,lmt-1)a[i]=tmp[i]%mod;
}
V IDFT(int*a){
	reverse(a+1,a+lmt),DFT(a);
	int bk(mod-mod/l);
	FOR(i,0,lmt-1)a[i]=1ll*a[i]*bk%mod;
}
V check(int&x){x-=mod,x+=x>>31&mod;}
V add(int*p,int*q,int*t){FOR(i,0,lmt-1)check(t[i]+=1ll*p[i]*q[i]%mod);}
V work(){
	FOR(i,0,lmt-1)p[i]=Pow(a[i],4),q[i]=i<m;
	DFT(p),DFT(q),add(p,q,t);
	FOR(i,0,lmt-1)p[i]=mod-2ll*Pow(a[i],3)%mod,check(q[i]=b[i]+c[i]);
	DFT(p),DFT(q),add(p,q,t);
	FOR(i,0,lmt-1)p[i]=1ll*a[i]*a[i]%mod,q[i]=(2ll*b[i]*c[i]+Pow(b[i]+c[i],2))%mod;
	DFT(p),DFT(q),add(p,q,t);
	FOR(i,0,lmt-1)p[i]=mod-2ll*a[i]%mod,q[i]=1ll*b[i]*c[i]%mod*(b[i]+c[i])%mod;
	DFT(p),DFT(q),add(p,q,t);
	FOR(i,0,lmt-1)p[i]=1<=i&&i<=n,q[i]=1ll*Pow(b[i],2)*Pow(c[i],2)%mod;
	DFT(p),DFT(q),add(p,q,t),IDFT(t);
	FOR(i,m,n)cout<<!t[i];
}
int main(){
//	freopen("test.in","r",stdin);
	input();
	init();
	work();
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

非常不牛洛谷 $\rm RMJ$，欢歌载舞，交换 $\rm C++17$ 和 $\rm C++20$，使我的代码 $\rm TLE$。

提供一种暴力的做法。考虑计算 $t$ 中从每个位置开始，有多少个位置和 $s$ 匹配。如果 $t$ 的第 $j$ 位与 $s$ 的第 $i$ 位匹配，可以对 $j-i+1$ 开始匹配的地方提供 $1$ 贡献。

所以把每个字符出现与否对应的序列的生成函数拉出来，发现实际上在求差卷积。于是使用 $\rm NTT$ 优化即可。

具体的，设 $s$ 中每个字符出现位置序列的生成函数设为 $\mathfrak{S}_i$，$t$ 设为 $\mathfrak{T}_i$。（$\mathfrak{S}$ 已经进行过翻折操作）那么求出 $\mathfrak{S}_i \mathfrak{T}_i$，如果 $p_i \neq i$ 还可以再求一个 $\mathfrak{S}_i \mathfrak{T}_{p_i}$。

注意到如果直接卷积再求和差不多要进行 $26 \times 3 = 78$ 次 $\rm NTT$。考虑到 $\rm NTT$ 有线性，所以可以优化到 $53$ 次 $\rm NTT$。通过预处理原根的幂次加上 $\rm C++20$ 的 buff 可以在 $\rm CF$ 上通过此题。

[Submission](https://codeforces.com/contest/1334/submission/252921506)

---

## 作者：SError_ (赞：0)

假设 $n=|t|$，$m=|s|$，下标从 $0$ 开始。

考虑把 $t_i$ 等于 $s_i$ 或 $p_{s_i}$ 这个条件转化为 $(t_i-s_i)^2\cdot (t_i-p_{s_i})^2=0$。

那么题目即对于每个 $j\in[0,n-m]$，判断下式是否为 $0$：

$$\sum_{j=0}^{m-1}(t_{i+j}-s_i)^2\cdot (t_{i+j}-p_{s_i})^2$$

先把下标去掉展开乘积式：

$$t^4-2t^3p+t^2p^2-2t^3s+4t^2sp-2tsp^2+t^2s^2-2ts^2p+s^2p^2$$

对于 $t$ 的次数合并同类项：

$$t^4-2t^3(s+p)+t^2(s^2+4sp+p^2)-2t(sp^2+s^2p)+s^2p^2$$

看回最开始的和式，发现是差卷积的形式。

把 $t$ 翻转，即原来的 $t_i$ 对应现在的 $t_{n-1-i}$。

那么下标 $i+j$ 会翻转至 $n-1-i-j$，有 $(n-1-i-j)+i=n-1-j$。

可以预处理 $t^4$ 和 $s^2p^2$ 的和，剩下的三项多项式即可，判断 $j$ 处的答案即判断和式在 $n-1-j$ 处的值是否为 $0$.

$\mathrm{NTT}$ 单模数会被卡，建议使用 $\mathrm{FFT}$。

```cpp
#include<bits/stdc++.h>
#define N (1<<19)
#define S 30
using namespace std;
int read(){
	int x=0,w=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*w;
}
const int P1=998244353,P2=1004535809;
struct dat{
	int p1,p2;
	dat(){p1=p2=0;}
	dat(int x){p1=p2=x;}
	dat(int _p1,int _p2):p1(_p1),p2(_p2){}
	dat operator+(const dat &t)const{
		return dat((p1+t.p1)%P1,(p2+t.p2)%P2);
	}
	dat operator-(const dat &t)const{
		return dat((p1+P1-t.p1)%P1,(p2+P2-t.p2)%P2);
	}
	dat operator*(const dat &t)const{
		return dat(1ll*p1*t.p1%P1,1ll*p2*t.p2%P2);
	}
};
int qpow(int k,int b,int P){
	int ret=1;
	while(b){
		if(b&1)ret=1ll*ret*k%P;
		k=1ll*k*k%P,b>>=1;
	}
	return ret;
}
int lim,r[N];dat gn,tp,inv;
void init_r(int n){
	lim=1;while(lim<(n<<1))lim<<=1;
	for(int i=0;i<lim;i++)
		r[i]=(r[i>>1]>>1)+(i&1)*(lim>>1);
}
void ntt(dat *x,int opt){
	for(int i=0;i<lim;i++)
		if(r[i]<i)swap(x[i],x[r[i]]);
	for(int p=2,k=1;p<=lim;p<<=1,k<<=1){
		gn=dat(qpow(3,(P1-1)/p,P1),qpow(3,(P2-1)/p,P2));
		for(int i=0;i<lim;i+=p){
			dat g(1,1);
			for(int j=0;j<k;j++,g=g*gn){
				tp=x[i+j+k]*g;
				x[i+j+k]=x[i+j]-tp;
				x[i+j]=x[i+j]+tp;
			}
		}
	}
	if(opt==-1){
		reverse(x+1,x+lim),inv=dat(qpow(lim,P1-2,P1),qpow(lim,P2-2,P2));
		for(int i=0;i<lim;i++)
			x[i]=x[i]*inv;
	}
}
dat ta[N],tb[N],f[N],g[N],h[N];
void Mul(dat *a,dat *b,dat *c,int n){
	init_r(n);
	for(int i=0;i<n;i++)ta[i]=a[i],tb[i]=b[i];
	for(int i=n;i<lim;i++)ta[i]=tb[i]=dat(0);
	ntt(ta,1),ntt(tb,1);
	for(int i=0;i<lim;i++)
		c[i]=ta[i]*tb[i];
	ntt(c,-1);
	for(int i=n;i<lim;i++)c[i]=dat(0);
}
int p[S];char _s[N],_t[N];
int m,s[N],n,t[N];
dat st[N],ssp;
dat sum[N];
void solve(){
	for(int i=0;i<n;i++)
		st[i]=(i?st[i-1]:dat(0))+dat(t[i]*t[i]*t[i]*t[i]);
	for(int i=0;i<m;i++)
		ssp=ssp+dat(s[i]*s[i]*p[s[i]]*p[s[i]]);
	//t^4+s^2p^2
	for(int i=0;i<=n-m;i++)
		sum[n-1-i]=st[i+m-1]-(i?st[i-1]:dat(0))+ssp;
	reverse(t,t+n);
	//-2t^3p-2t^3s
	for(int i=0;i<n;i++)f[i]=dat(t[i]*t[i]*t[i]);
	for(int i=0;i<m;i++)
		g[i]=dat(1ll*(P1-2)*(s[i]+p[s[i]])%P1,1ll*(P2-2)*(s[i]+p[s[i]])%P2);
	Mul(f,g,h,n);
	for(int i=0;i<n;i++)sum[i]=sum[i]+h[i];
	//t^2p^2+4t^2sp+t^2s^2
	for(int i=0;i<n;i++)f[i]=dat(t[i]*t[i]);
	for(int i=0;i<m;i++)
		g[i]=dat(p[s[i]]*p[s[i]]+4*s[i]*p[s[i]]+s[i]*s[i]);
	Mul(f,g,h,n);
	for(int i=0;i<n;i++)sum[i]=sum[i]+h[i];
	//-2tsp^2-2ts^2p
	for(int i=0;i<n;i++)f[i]=dat(t[i]);
	for(int i=0,tp;i<m;i++){
		tp=s[i]*p[s[i]]*(p[s[i]]+s[i]);
		g[i]=dat(1ll*(P1-2)*tp%P1,1ll*(P2-2)*tp%P2);
	}
	Mul(f,g,h,n);
	for(int i=0;i<n;i++)sum[i]=sum[i]+h[i];
}
int main(){
	for(int i=1;i<=26;i++)p[i]=read();
	scanf("%s%s",_s,_t);
	m=strlen(_s),n=strlen(_t);
	for(int i=0;i<n;i++)t[i]=_t[i]-'a'+1;
	for(int i=0;i<m;i++)s[i]=_s[i]-'a'+1;
	solve();
	for(int i=0;i<=n-m;i++)
		putchar((!sum[n-1-i].p1&&!sum[n-1-i].p2)?'1':'0');
	printf("\n");
	
	return 0;
}
```

---

