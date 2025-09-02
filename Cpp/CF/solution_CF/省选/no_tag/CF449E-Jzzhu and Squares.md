# Jzzhu and Squares

## 题目描述

Jzzhu has two integers, $ n $ and $ m $ . He calls an integer point $ (x,y) $ of a plane special if $ 0<=x<=n $ and $ 0<=y<=m $ . Jzzhu defines a unit square as a square with corners at points $ (x,y) $ , $ (x+1,y) $ , $ (x+1,y+1) $ , $ (x,y+1) $ , where $ x $ and $ y $ are some integers.

Let's look at all the squares (their sides not necessarily parallel to the coordinate axes) with corners at the special points. For each such square Jzzhu paints a dot in every unit square that is fully inside it. After that some unit squares can contain several dots. Now Jzzhu wonders, how many dots he has painted on the plane. Find this number modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
4
1 3
2 2
2 5
3 4
```

### 输出

```
3
8
26
58
```

# 题解

## 作者：Memory_of_winter (赞：6)

[我的博客](https://www.cnblogs.com/Memory-of-winter/p/11209128.html)

**题目大意：** 有一个$n\times m$的方格图，求其中所有的格点正方形完整包含的小方格个数，多组询问。$n,m\leqslant 10^6$

**题解：** 令$n\leqslant m$。有一个显然的式子：
$$ans=\sum\limits_{i=1}^n(n-i+1)(m-i+1)f(i)$$
$f(i)$表示可以完整包含在$i\times i$的正方形中且顶点在这个正方形边上的正方形所包含的小方格总数。可以分选的正方形和$i\times i$正方形重合和边转动$j$格来计算
$$f(n)=n^2+\sum\limits_{i=1}^{n-1}[(n-2\max\{i,n-1\})^2+g(i,n-i)]$$
其中$(n-2\max\{i,n-1\})^2$是转动$i$格后正中间的完整小方格，$g(i,n-i)$表示四周的$4$个小直角三角形中包含的完整小方格个数。

比如计算左上角的直角三角形，发现完整的小方格的左上角满足在直角三角形的斜边上或三角形内。三角形内的点可以用皮克定理来解决，令三角形两直角边为$n,m$，则三角形内的点个数为$\dfrac{nm-n-m+2-\gcd(n,m)}2$，再加上在斜边上的点，则一个直角三角形内的方格数为$\dfrac{nm-m-n+gcd(n,m)}2$。

把$n=i,m=n-i$带入式子
$$\begin{aligned}f(n)=&n^2+\sum\limits_{i=1}^{n-1}[(n-2\max\{i,n-1\})^2+g(i,n-i)]\\=&n^2+\sum\limits_{i=1}^{n-1}(n-2\max\{i,n-1\})^2+\sum\limits_{i=1}^{n-1}g(i,n-i)\\=&n^2+\sum\limits_{i=1}^{\left\lfloor\frac{n-1}2\right\rfloor}(n-2i)^2+\sum\limits_{i=\left\lfloor\frac{n-1}2\right\rfloor+1}^{n-1}(2i-n)^2\\&+\sum\limits_{i=1}^{n-1}\dfrac{i(n-i)-(n-i)-i+\gcd(i,n-i)}2\\=&n^2+2\sum\limits_{i=1}^{\left\lfloor\frac{n-1}2\right\rfloor}(n-2i)^2+\sum\limits_{i=1}^{n-1}\dfrac{in-i^2-n+\gcd(i,n)}2\end{aligned}$$
其中$n^2$可以快速计算，$\sum\limits_{i=1}^{\left\lfloor\frac{n-1}2\right\rfloor}(n-2i)^2$可以前缀和解决，问题在$\sum\limits_{i=1}^{n-1}\dfrac{in-i^2-n+\gcd(i,n)}2$部分。令$h(n)=\sum\limits_{i=1}^{n-1}\dfrac{in-i^2-n+\gcd(i,n)}2$，$sgcd(n)=\sum\limits_{i=1}^{n-1}\gcd(i,n)$
$$h(n)=\dfrac12[\sum\limits_{i=1}^{n-1}(in-i^2-n)+sgcd(n)]$$
$$\begin{aligned}h(n-1)&=\dfrac12[\sum\limits_{i=1}^{n-2}(i(n-1)-i^2-(n-1))+sgcd(n-1)]\\&=\dfrac12[\sum\limits_{i=1}^{n-2}(in-i^2-n-i+1)+sgcd(n-1)]\\\end{aligned}$$

$$\begin{aligned}h(n)=&h(n-1)+\dfrac12[\sum\limits_{i=1}^{n-2}(i-1)+(n-1)n-(n-1)^2-n\\&-sgcd(n-1)+sgcd(n)]\\=&h(n-1)+\dfrac12[\left(\sum\limits_{i=0}^{n-3}i\right)-1-sgcd(n-1)+sgcd(n)]\\=&h(n-1)+\dfrac12[\left(\dfrac{(n-2)(n-3)}2\right)-1-sgcd(n-1)+sgcd(n)]\end{aligned}$$

其他部分都可以快速求出，问题在求$sgcd(n)$
$$\begin{aligned}sgcd(n)&=\sum\limits_{i=1}^{n-1}\gcd(i,n)\\&=\left(\sum\limits_{d|n}\dfrac nd\varphi(d)\right)-n\end{aligned}$$
全部预处理出来即可。



**C++ Code：**

```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
#define mul(a, b) (static_cast<long long> (a) * (b) % mod)
const int mod = 1e9 + 7, maxn = 1e6 + 10, half = (mod + 1) / 2;
inline void reduce(int &x) { x += x >> 31 & mod; }

int gcd(int a, int b) {
	if (!b) return a;
	return gcd(b, a % b);
}
inline int sqr(int x) { return mul(x, x); }

int g[maxn], sumgcd[maxn], phi[maxn], plist[maxn / 2], ptot;
int pre[maxn], R[maxn], T[maxn], preF[maxn];
bool notp[maxn];
int Q;

int F(int n) {
	int ans = g[n];
	reduce(ans += sqr(n) - mod);
	reduce(ans += pre[n - 2] - mod);
	reduce(ans += pre[n - 2] - mod);
	return ans;
}
void sieve(int N) {
	phi[1] = 1;
	for (int i = 2; i <= N; i++) {
		if (!notp[i]) phi[plist[ptot++] = i] = i - 1;
		for (int j = 0, t; j < ptot && (t = i * plist[j]) <= N; j++) {
			notp[t] = true;
			if (i % plist[j] == 0) {
				phi[t] = phi[i] * plist[j];
				break;
			}
			phi[t] = phi[i] * phi[plist[j]];
		}
	}
	for (int i = 1; i <= N; ++i) {
		for (int j = i + i; j <= N; j += i) reduce(sumgcd[j] += mul(phi[j / i], i));
	}
	for (int i = 4; i <= N; ++i) {
		g[i] = (1ll * (i - 3) * (i - 2) / 2 - 1 - sumgcd[i - 1] + sumgcd[i]) % mod;
		reduce(g[i]);
		g[i] = mul(g[i], half);
		reduce(g[i] += g[i - 1] - mod);
	}
	for (int i = 1; i <= N; ++i) g[i] = mul(g[i], 4);
	pre[1] = 1;
	for (int i = 2; i <= N; ++i) reduce(pre[i] = pre[i - 2] + sqr(i) - mod);
	for (int i = 1; i <= N; ++i) reduce(preF[i] = preF[i - 1] + F(i) - mod);
	for (int i = 1; i <= N; ++i) {
		reduce(R[i] = R[i - 1] + preF[i - 1] - mod);
		reduce(R[i] += F(i) - mod);
	}
	for (int i = 1; i <= N; ++i) {
		reduce(T[i] = T[i - 1] + preF[i - 1] - mod);
		reduce(T[i] += R[i - 1] - mod);
		reduce(T[i] += R[i - 1] - mod);
		reduce(T[i] += F(i) - mod);
	}
}
int solve(int n, int m) {
	int ans = T[n];
	reduce(ans += mul(R[n], m - n) - mod);
	return ans;
}

int main() {
	std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
	sieve(1000005);
	std::cin >> Q;
	while (Q --> 0) {
		static int n, m;
		std::cin >> n >> m;
		if (n > m) std::swap(n, m);
		std::cout << solve(n, m) << '\n';
	}
	return 0;
}

```





---

## 作者：tzc_wk (赞：2)

显然任意一个顶点是关键点的正方形都可以用两个量来刻画：以其任意一条边对应的直角边平行于坐标轴的直角三角形的两直角边的长度 $i,j$（在下文中记这样的正方形为正方形 $(i,j)$）。对于 $i+j$ 相同的两种正方形，显然一个 $n\times m$ 的点阵中这样的两正方形个数是相同。因此考虑预处理出 $f_x$ 表示对于所有 $i+j=x$ 的正方形 $(i,j)$，该正方形中小方格个数之和。处理出 $f_x$ 后，答案就是 $\sum\limits_{i=1}^{\min(n,m)}(n-i+1)(m-i+1)f_i$，可以 $O(1)$ 回答询问，于是这样任务变为求 $f_x$。

考虑怎么等价地表达正方形 $(i,j)$ 中包含的方格个数，将正方形用类似于弦图的方式进行划分，里面有个边长为 $|i-j|$ 的正方形，其中包含 $(i-j)^2$ 个小方格，四周的四个直角三角形包含的方格数是一样的，那么如果我们记 $g(i,j)$ 表示两边长分别为 $i,j$ 的直角三角形中包含的小方格的数量。那么正方形 $(i,j)$ 中包含的方格数就是 $(i-j)^2+4g(i,j)$。

直接计算 $g(i,j)$ 看着需要什么类欧几里得之类的东西处理下取整，如果你往这个方向想就大错特错了。一种等价的表达是，三角形中除了两直角边的格点个数（即，内部格点数量 $+$ 斜边上的格点数量）。而内部格点数量是可以用 picks 定理直接计算即可，可以表达为 $i,j,\gcd(i,j)$ 的线性组合。斜边上格点数量为 $\gcd(i,j)-1$，因此 $g(i,j)$ 就可以表示为 $i,j,\gcd(i,j)$ 的线性组合。这样求 $f_x$ 只需要求一个类似于 $\sum\limits_{i+j=x}Ai+Bj+C\gcd(i,j)+D+(i-j)^2$ 的东西，其中 $A,B,C,D$ 为可以手算求得的常数。求 $\sum\limits_{i+j=x}\gcd(i,j)$ 直接莫反即可。这部分是 trivial 了，时间复杂度 $O(n\log n)$。

式子就不细推了，相信如果看懂了自然可以推出来。

```cpp
const int MAXN=1e6;
const int MOD=1e9+7;
int f[MAXN+5],sf2[MAXN+5],sf1[MAXN+5],sf0[MAXN+5];
int getsum1(int x){return 1ll*x*(x+1)/2%MOD;}
int getsum2(int x){return 1ll*x*(x+1)*(2*x+1)/6%MOD;}
int pr[MAXN+5],prcnt,phi[MAXN+5],vis[MAXN+5];
void init(int n){
	phi[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i])pr[++prcnt]=i,phi[i]=i-1;
		for(int j=1;j<=prcnt&&pr[j]*i<=n;j++){
			vis[pr[j]*i]=1;
			if(i%pr[j]==0){
				phi[pr[j]*i]=phi[i]*pr[j];
				break;
			}
			phi[pr[j]*i]=phi[pr[j]]*phi[i];
		}
	}
	for(int i=1;i<=n;i++){
		f[i]=1ll*i*i%MOD;
		f[i]=(f[i]+2ll*getsum2(i-1))%MOD;
		f[i]=(f[i]-2ll*i*(i-1)%MOD+MOD)%MOD;
	}
	for(int i=1;i<=n;i++)for(int j=i+i;j<=n;j+=i)
		f[j]=(f[j]+2ll*i*phi[j/i])%MOD;
	for(int i=1;i<=n;i++){
		sf2[i]=(sf2[i-1]+1ll*f[i]*i%MOD*i)%MOD;
		sf1[i]=(sf1[i-1]+1ll*f[i]*i)%MOD;
		sf0[i]=(sf0[i-1]+f[i])%MOD;
	}
}
int main(){
	init(MAXN);int qu;scanf("%d",&qu);
	while(qu--){
		int n,m,res=0;scanf("%d%d",&n,&m);
		printf("%d\n",(1ll*(n+1)*(m+1)%MOD*sf0[min(n,m)]+1ll*(MOD-sf1[min(n,m)])*(n+1+m+1)+sf2[min(n,m)])%MOD);
	}
	return 0;
}
```





---

## 作者：sry_ (赞：2)

小学奥数题。

设 $f(i)$ 表示四个点可以划分到一个 $i\cdot i$ 的矩形内的包含小方格的总个数。

我们令 $n\leq m$ 则 $Ans=\sum_{i=1}^n(n-i+1)\cdot (m-i+1)\cdot f(i)$ 。

而 
$$
f(n)=n^2+\sum_{i=1}^{n-1} (n-2\cdot i)^2+4\cdot g(i,n-i)
$$
$g(i,j)$ 表示在一个 $i,j$ 为底的直角三角形中包含的小方格个数。

由于皮克定理可得
$$
g(i,j)=\dfrac{nm-n-m+\gcd(n,m)}{2}
$$
通过化简式子那么可以快速求得 $f(i)$ 。

则现在只要快速求
$$
\sum_i\sum_j (n-i+1)\cdot (m-i+1)\cdot f_i
$$

再拆开维护即可。

时间复杂度 $O(n\log n)$ 。
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#include<climits>
#define int long long
#define mod 1000000007
#define pii pair<int,int>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return f*ans;
}
const int MAXN=1e6+11;
const int inv2=500000004;
const int inv6=166666668;
const int Lim=1e6;
int N,M,F[MAXN],W[MAXN],v[MAXN],pri[MAXN],phi[MAXN];
int ksm(int a,int b){int ans=1;while(b){if(b&1) ans*=a,ans%=mod;a*=a,a%=mod;b>>=1;}return ans;}
int gcd(int a,int b){return !b?a:gcd(b,a%b);}
int g(int a,int b){return (a*b-a-b+gcd(a,b))/2;}
int Q1(int a){return a*(a+1)%mod*inv2%mod;}
int Q2(int a){return a*(a+1)%mod*(2*a+1)%mod*inv6%mod;}
void Init(){
    phi[1]=1;
    for(int i=2;i<=Lim;i++){
        if(!v[i]){v[i]=i;pri[++pri[0]]=i;phi[i]=i-1;}
        for(int j=1;pri[j]*i<=Lim&&j<=pri[0];j++){
            v[pri[j]*i]=pri[j];
            if(!(i%pri[j])){phi[i*pri[j]]=phi[i]*pri[j];break;}
            phi[pri[j]*i]=phi[i]*(pri[j]-1);
        }
    }return;
}
int G[MAXN],S1[MAXN],S2[MAXN];
signed main(){
    //freopen("5.in","r",stdin);
    Init();
    for(int i=1;i<=Lim;i++){
        for(int j=1;i*j<=Lim;j++) W[i*j]+=phi[i]*j%mod,W[i*j]%=mod;
        W[i]-=i,W[i]=((W[i]%mod)+mod)%mod;
    }
    int cas=read();
    for(int i=1;i<=Lim;i++){
        int res=0; res=i*i*i; res%=mod;
        res-=2*i*Q1(i-1);res%=mod; res+=2*Q2(i-1); res%=mod;
        res-=2*(i-1)*i; res%=mod;res+=2*W[i],res%=mod;
        res=(res%mod+mod)%mod;
        F[i]=res;
    }
    for(int i=1;i<=Lim;i++){
        G[i]=G[i-1]+F[i]+(2*i+1)*S1[i-1]-2*S2[i-1];
        G[i]=((G[i]%mod)+mod)%mod;
        S1[i]=(S1[i-1]+F[i])%mod,S2[i]=(S2[i-1]+F[i]*i)%mod;
    }
    
    while(cas--){
        N=read(),M=read(); if(N>M) swap(N,M);
        /*int Ans=0;
        for(int i=1;i<=N;i++) Ans+=(N-i+1)*(M-i+1)%mod*F[i]%mod,Ans%=mod;*/
        int del=M-N,Ans=G[N],res=0;
        res=del*((N+1)*S1[N]%mod-S2[N])%mod,res=((res%mod)+mod)%mod;
        printf("%lld\n",(Ans+res)%mod);
    }
}

```


---

## 作者：RainWetPeopleStart (赞：0)

无脑推式子题。

先不考虑边与坐标轴不平行的情况，答案为 $\sum\limits_{i=1}^{\min(n,m)}(n+1-i)(m+1-i)i^2$。

## 处理贡献

对于不平行的情况，考虑把贡献放在最小的，能包裹住该矩形的，且平行于坐标轴的矩形上。

同时，我们只要得知它最左面的点与包裹它的矩形左下方的点的距离 $a$，和包裹它的矩形的边长 $i$ 即可唯一确定这一个矩形。

![](https://cdn.luogu.com.cn/upload/image_hosting/7mgxfx57.png)

这样，我们就可以让 $f(a,i)$ 表示 $a,i$ 确定的矩形围住的小正方形个数（这里设 $a=0$ 表示 $i\times i$ 的与坐标轴平行的矩形）。

如何求 $f(a,i)$ 呢，把矩形分成 $4$ 个三角形和中间的正方形（具体见上图蓝线）。

### 三角形

对三角形而言，由于对称性，考虑阴影部分所代表的矩形，正难则反，我们计算里面矩形的边（黑色的线）穿过了多少个方格即可。

记 $g=\gcd(a,i-a)$，穿过的方格数为 $c$。

若 $g=1$，则矩形的边只会经过两个整点，即边的两个端点，可得 $c=(i-a)+a-1$。

否则，就拆成 $g=1$ 的情况，可得 $c=g(\frac{i-a}{g}+\frac{a}{g}-1)$。

综上，$c=i-g$。

则一个三角形对 $f$ 的贡献就是 $\frac{1}{2}(a(i-a)-(i-g))$。

### 正方形

贡献是 $((i-a)-a)^2$。

综上 $f(a,i)=((i-a)-a)^2+4\times \frac{1}{2}(a(i-a)-(i-g))$。

化简得 $f(a,i)=i^2+2a^2-2ai-2i+2g$。

## 计算答案

此时，可以考虑维护 $val(i)$ 表示 $i\times i$ 的，与坐标轴平行的矩形对答案造成的总贡献，并用其替代上文的 $i^2$ 来计算答案。

由上文知 $val(i)=\sum\limits_{a=0}^{i-1}f(a,i)$。

考虑分别计算 $f$ 的每一项对 $val$ 造成的贡献。

前面 $4$ 项的贡献是好算的，只需要平方和公式和等差数列求和公式即可。

最后一项要计算 $\sum\limits_{a=0}^{i-1}\gcd(a,i-a)$。

推式子，同时使用欧拉反演可得：

$$\begin{aligned}
\sum\limits_{a=0}^{i-1}\gcd(a,i-a)= &\sum\limits_{a=0}^{i-1}\gcd(a,i)
\\= &\sum\limits_{a=0}^{i-1}\sum\limits_{d|\gcd(a,i)}\varphi(d)
\\= &\sum\limits_{d|n}\varphi(d)\frac{n}{d}
\end{aligned}$$

直接算是 $O(n\log n)$。

计算答案可以把前面拆掉，拆成 $(n+1)(m+1)val(i)-i(n+m+2)val(i)+i^2val(i)$，然后求 $val(i)$，$val(i)\times i$，$val(i)\times i^2$ 即可。

## 代码


```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define ll long long
#define ull unsigned long long
#define uint unsigned int
#define bi __int128_t
#define lb(x) ((x)&(-(x)))
#define gp(i,j) (((i)>>(j-1))&1)
#define ppc __builtin_popcount
#define ctz __builtin_ctz
using namespace std;
const int N=1e6+10,mod=1e9+7;
void Add(int &a,int b){a+=b;if(a>=mod) a-=mod;}
void Sub(int &a,int b){a-=b;if(a<0) a+=mod;}
void Mul(int &a,int b){a=1ll*a*b%mod;}
int qp(int a,int b){
    int x=1;
    while(b){
        if(b&1) Mul(x,a);
        Mul(a,a);b>>=1;
    }return x;
}
int n,m;
int val[N],val1[N],val2[N],g[N];
const int LM=1e6+5;
bool isp[N];int phi[N];
vector<int> p;
int fac[N],inv[N],invp[N];
void init(){
    for(int i=2;i<=LM;i++){
        if(!isp[i]){
            p.push_back(i);
            phi[i]=i-1;
        }
        for(auto j:p){
            if(i*j>LM) break;
            isp[i*j]=1;phi[i*j]=phi[i]*(j-1);
            if(i%j==0){
                phi[i*j]=phi[i]*j;
                break;
            }
        }
    }phi[1]=1;
    fac[0]=1;for(int i=1;i<=LM;i++) fac[i]=1ll*i*fac[i-1]%mod;
    inv[LM]=qp(fac[LM],mod-2);for(int i=LM-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
    for(int i=1;i<=LM;i++) invp[i]=1ll*inv[i]*fac[i-1]%mod;
}
int main(){
    init();
    for(int i=1;i<=LM;i++){
        int vl=1ll*phi[i]*invp[i]%mod;
        //if(i<=5) cout<<phi[i]<<endl;
        for(int j=i;j<=LM;j+=i){
            Add(g[j],1ll*vl*j%mod);
        }
    }
    for(int i=1;i<=LM;i++){
        val[i]=0;
        Add(val[i],1ll*i*i*i%mod);
        Sub(val[i],2ll*i*i%mod);
        Add(val[i],2ll*g[i]%mod);
        Add(val[i],1ll*i*(i+1)*(2*i+1)%mod*invp[3]%mod);
        //if(i<=3) cout<<i<<' '<<val[i]<<' '<<6ll*inv[3]%mod<<endl;
        Sub(val[i],1ll*i*i*(i+1)%mod);
        //if(i%2==0) Add(val[i],1ll*(i/2)*(i-2)%mod);
        //if(i<=3) cout<<i<<' '<<val[i]<<endl;
        //Mul(val[i],invp[2]);
        val1[i]=1ll*val[i]*i%mod;
        val2[i]=1ll*val1[i]*i%mod;
        //if(i<=5) cout<<i<<' '<<val[i]<<' '<<g[i]<<endl;
    }
    for(int i=1;i<=LM;i++){
        Add(val[i],val[i-1]);
        Add(val1[i],val1[i-1]);
        Add(val2[i],val2[i-1]);
    }
    int t;cin>>t;
    while(t--){
        int n,m;cin>>n>>m;
        int cnt=min(n,m);
        int ans=0;
        Add(ans,val2[cnt]);
        Sub(ans,1ll*(n+m+2)*val1[cnt]%mod);
        Add(ans,1ll*(n+1)*(m+1)%mod*val[cnt]%mod);
        cout<<ans<<endl;
    }//cerr<<clock()*1.0/CLOCKS_PER_SEC<<endl;
    return 0;
}
```

---

## 作者：紊莫 (赞：0)

来一发欧拉反演的题解。

---

一个正方形用两条边 $a,b$ 来表示，对应的边长是 $\sqrt{a^2+b^2}$。

首先设 $f_i$ 表示 $a + b = i$ 的正方形内含有的小正方形数量。

根据皮克定理的推广可以得到：$f_i=\sum\limits_{j=1}^{i}j^2+(i-j)^2-2i+2\gcd(i,j)$。

和式内前面三部分都可以直接算，最后一个部分这样算：

$$\begin{aligned}
&\sum_{i=1}^{n}\gcd(i,n) \\
=& \sum_{i=1}^{n}\sum_{d | \gcd(i,n)}\varphi(d) \\
=& \sum_{d | n}\varphi(d)\sum_{i=1}^{n}[d|i] \\
=& \sum_{d | n}\varphi(d)\frac{n}{d}  \\
\end{aligned}$$

最后贡献一拆，做完了。

---

