# lgdAKIOI

## 题目背景

本题中出现的神犇：[_lgswdn](https://www.luogu.com.cn/user/180652)

AK 完 NOI 后，lgd 一路势不可挡，不久便进入了国家队，来到了 IOI 赛场。

## 题目描述

6ms 后，lgd 写对了最后一题的

```plain
可持久化非确定状态AC自动分块维护线段平衡仙人掌优化最小费用最大流预处理混合图上莫比乌斯反演莫队带花舞蹈链并查集树状数组套主席树预处理动态DP分治FFT求多项式逆元对数函数的指数函数用可持久化并查集合并最小费用循环流上插头DP
```
算法，AK 了 IOI。于是他闲着无聊，开始给自己出题。

有一题是这样的：

$n$ 个同学站成一个圆圈，其中的一个同学手里拿着一个球。每一次，手里有球的同学可以把球传给自己左右的两个同学中的一个（左右任意）。那么有多少种不同的传球方法可以使得从 lgd 手里开始传的球，传了 $m$ 次以后，又回到 lgd 自己手里呢？两种传球方法被视作不同的方法，当且仅当这两种方法中，接到球的同学按接球顺序组成的序列是不同的。

你听说这道题之后，希望把它做出来，以不遭到 lgd 的鄙视。由于 lgd 比较仁慈，他允许你只告诉他答案取模 $720000054000001$ 的余数就好了。

## 说明/提示

**本题采用捆绑测试。**

**本题有多组数据。**

**请注意常数因子带来的程序效率及空间占用上的影响。**

数据范围如下表所示。

|数据点编号|$n$|$m$|数据组数|分值|特殊性质|子任务编号|
|----|----|----|----|----|----|----|
|$1\sim6$|$=100$|$\le100$|$\le5$|$5$|A|0|
|$7\sim12$|$=10^5$|$\le10^6$|$\le5$|$15$|A|1|
|$13\sim18$|$=10^6$|$\le2\times10^6$|$\le5$|$10$|A|2|
|$19\sim24$|$=2\times10^5$|$\le10^{1000}$|$\le5$|$20$|A|3|
|$25\sim30$|$\le6\times10^6$|$\le10^{30}$|$\le50$|$20$||4|
|$31\sim36$|$\le6\times10^6$|$\le10^{10^4}$|$\le2500$|$30$||5|

特殊性质 A：所有输入的 $n$ 全部相同。

对于 $100\%$ 的数据，$n\in\{10,13,100,10^3,10^4,10^5,2\times10^5,6\times10^5,10^6,6\times10^6\}$。

---

lgd 把这题交给你的时候同时给了你另外一段代码，不过有什么用就不知道了。

```cpp
typedef long long i64;
typedef unsigned long long u64;
typedef __uint128_t u128;
struct Mod64 {
  Mod64() : n(0) {}
  Mod64(u64 n) : n(init(n)) {}
  static u64 modulus() { return mod; }
  static u64 init(u64 w) { return reduce(u128(w) * r2); }
  static void setmod(u64 m) {
    mod = m;
    inv = 1;
    for (int i = 0; i < 6; ++i) inv *= 2 + inv * m;
    r2 = -u128(m) % m;
  }
  static u64 reduce(u128 x) {
    u64 y = (x + u128(u64(x) * inv) * mod) >> 64;
    return i64(y) > mod ? y - mod : y;
  }
  Mod64& operator+=(Mod64 rhs) {
    n += rhs.n - mod;
    if (i64(n) < 0) n += mod;
    return *this;
  }
  Mod64& operator-=(Mod64 rhs) {
    if (n < rhs.n)
      n += mod - rhs.n;
    else
      n -= rhs.n;
    return *this;
  }
  Mod64 operator-() const {
    if (!n) return *this;
    Mod64 rhs;
    rhs.n = mod - n;
    return rhs;
  }
  Mod64 operator+(Mod64 rhs) const { return Mod64(*this) += rhs; }
  Mod64 operator-(Mod64 rhs) const { return Mod64(*this) -= rhs; }
  Mod64& operator*=(Mod64 rhs) {
    n = reduce(u128(n) * rhs.n);
    return *this;
  }
  Mod64 operator*(Mod64 rhs) const { return Mod64(*this) *= rhs; }
  u64 get() const { return reduce(n); }
  static u64 mod, inv, r2;
  u64 n;
};
u64 Mod64::mod, Mod64::inv, Mod64::r2;
```

## 样例 #1

### 输入

```
5 7
5 5
5 4
5 5
5 9```

### 输出

```
14
2
6
2
72```

## 样例 #2

### 输入

```
100000 998684
100000 998671
100000 998110```

### 输出

```
513030267786335
0
570065615362699```

# 题解

## 作者：NaCly_Fish (赞：8)

[题目链接](https://www.luogu.com.cn/problem/P8442)

今天比赛快结束时，听说有人阿克了这场，就进来看了看 F，这不是典题吗，，

首先这个模数是个合数，可以分解为 $24000001\times 30000001$，分别设为 $p_1$ 和 $p_2$。那么只要分别对 $p_1$ 和 $p_2$ 求解后用 crt 合并即可。

可以发现给出的 $n$ 除了 $13$ 都可以整除 $p_1-1$ 和 $p_2-1$，这些情况下 $\omega_n$ 在模 $p_1$ 和 $p_2$ 下都存在，直接用
$$\frac 1n\sum_{i=0}^{n-1}(\omega_n^i+\omega_n^{-i})^m \ \ \texttt{(1)}$$
计算，时间复杂度是 $\Theta(n \log p)$ 的。

还有另外一种做法是进行二项式展开，单位根反演即得
$$\sum_{k=0}^m \binom mk \frac 1n\sum_{i=0}^{n-1}\omega_n^{(2k-m)i}=\sum_{k=0}^m\binom mk[n|(2k-m)] \ \ \texttt{(2)}$$
用这种方法计算一组数据的时间复杂度是 $\Theta(p/n)$，需要 $\Theta(p)$ 预处理阶乘。

综合一下这两种算法，解方程 $n \log p = p/n$ 可以得到 $n=1000$ 时为临界数据，小于 $1000$ 的用方法 $\texttt{(1)}$，大于 $1000$ 的用方法 $\texttt{(2)}$ 即可。

对于 $n=13$ 这个特别数据可以发现，在模 $p=30000001$ 意义下有：
$$(x+x^{12})^p \equiv x^5+x^8 \pmod{(x^n-1)}$$
$$(x^5+x^8)^p\equiv 2+x^2+x^{11}\equiv (x+x^{12})^2 \pmod{(x^n-1)}$$
故直接将 $m$ 对 $p^2-1$ 取模即可。特别地，对于 $p=24000001$ 时循环节长度只有 $p-1$。

最后就是常数优化，主要有五点：

1. 对于题目中限定的 $n \neq 13$ 的数据，$m$ 为奇数时答案为零。

2. 由单位根的性质，若 $m$ 为偶数，在利用方法 $\texttt{(1)}$ 时 $i$ 只用取到一半，之后取二倍即可。

3. 对于 $n=1000$ 的情况，若使用方法 $\texttt{(1)}$，可以对快速幂做优化，做预处理。这里我选用 $8$ 进制快速幂。

4. 在使用方法 $\texttt{(2)}$ 时，可以发现答案也是对称的，也可以只算一半。

5. 使用无符号整数运算，效率会明显提升。

参考代码：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#define ll unsigned long long
#define int unsigned int
#define N 30000003
#define P 720000054000001
#define i128 __int128_t
using namespace std;

const int pr[2] = {24000001,30000001};
const int g[2] = {23,14};
int ifac[N],sw[503][9][8];
int p,inv1k;

inline int power(int a,int t,int m){
    int res = 1;
    while(t){
        if(t&1) res = (ll)res*a%m;
        a = (ll)a*a%m;
        t >>= 1;
    }
    return res;
}

void init(int id){
    inv1k = power(1000,p-2,p);
    ifac[0] = 1,ifac[p-1] = p-1;
    for(int i=p-2;i;--i) ifac[i] = (ll)ifac[i+1]*(i+1)%p;
    int r = power(g[id],(p-1)/1000,p),w = 1,iw = 1;
    int ir = power(r,p-2,p);
    for(int i=0;i<500;++i){ 
        sw[i][0][0] = 1,sw[i][0][1] = w+iw;
        for(int k=2;k<8;++k) sw[i][0][k] = (ll)sw[i][0][k-1]*sw[i][0][1]%p;
        for(int j=1;j<9;++j){
            sw[i][j][0] = 1,sw[i][j][1] =  (ll)sw[i][j-1][7]*sw[i][j-1][1]%p;
            for(int k=2;k<8;++k) sw[i][j][k] = (ll)sw[i][j][k-1]*sw[i][j][1]%p;
        }
        w = (ll)w*r%p,iw = (ll)iw*ir%p;
    }
}

inline void multiply(const int *f,const int *g,int n,int *r){
    static int h[28];
    memset(h,0,sizeof(h));
    for(int i=0;i<n;++i)
    for(int j=0;j<n;++j)
        h[i+j] = (h[i+j]+(ll)f[i]*g[j])%p;
    for(int i=0;i<n;++i) r[i] = (h[i]+h[i+n])%p;
}

inline int solve(int n,ll m,int rt){
    int pw,t;
    ll res = 0;
    if(n==13){
        static int f[28],g[28];
        memset(f,0,sizeof(f));
        memset(g,0,sizeof(g));
        f[1] = f[n-1] = g[0] = 1;
        while(1){
            if(m&1) multiply(f,g,n,g);
            m >>= 1;
            if(m==0) break;
            multiply(f,f,n,f);
        }
        return g[0];
    }
    if(m&1) return 0;
    if(n==1000){
        for(int i=0;i<500;++i){
            pw = 1,t = m;
            for(int j=0;t;++j){
                if(t&7) pw = (ll)pw*sw[i][j][t&7]%p;
                t >>= 3;
            }
            res += pw;
        }
        return (res<<1)%p*inv1k%p;
    }
    if(n<=100){
        int r = power(rt,(p-1)/n,p);
        int ir = power(r,p-2,p),w = 1,iw = 1;
        n >>= 1;
        for(int i=0;i<n;++i){
            res += power(w+iw,m,p);
            w = (ll)w*r%p,iw = (ll)iw*ir%p;
        }
        return (res<<1)%p*power(n<<1,p-2,p)%p;
    }
    int st = (m>>1)%(n>>1),len = n>>1;
    for(int k=st;(k<<1)<m;k+=len) res += (ll)ifac[k]*ifac[m-k]%p;
    return ((res<<1)+(ll)ifac[m>>1]*ifac[m>>1])%p*power(ifac[m],p-2,p)%p;
}

inline ll crt(int x,int y){
    return ((i128)x*pr[1]*power(pr[1],pr[0]-2,pr[0])+(i128)y*pr[0]*power(pr[0],pr[1]-2,pr[1]))%P;
}

struct query{
    int n,m0,m1,x,y;
    ll m13;
    inline query(int _n=0,int _m0=0,int _m1=0,int _x=0,int _y=0):n(_n),m0(_m0),m1(_m1),x(_x),y(_y){}
}a[2503];

char str[10003];
int m0,m1,x,y,l,cnt;
ll m13;

signed main(){
    int n;
    p = pr[0];
    init(0);
    while(scanf("%d%s",&n,str)==2){
        l = strlen(str);
        m1 = m0 = m13 = 0;
        for(int i=0;i<l;++i) m0 = (m0*10+str[i]-'0')%(pr[0]-1);
        if(n==13){
            for(int i=0;i<l;++i) 
                m13 = (m13*10+str[i]-'0')%((ll)pr[1]*pr[1]-1);
        }else{
            for(int i=0;i<l;++i)
                m1 = (m1*10+str[i]-'0')%(pr[1]-1);
        }
        x = solve(n,m0,g[0]);
        a[++cnt] = (query(n,m0,m1,x));
        a[cnt].m13 = m13;
    }
    p = pr[1];
    init(1);
    for(int i=1;i<=cnt;++i){
        x = a[i].x;
        y = solve(a[i].n,a[i].n==13?a[i].m13:a[i].m1,g[1]);
        printf("%lld\n",crt(x,y));
    }
    return 0;
} 
```

后记：我没看比赛奖评，但这个出题人咋跑那么快啊？更神必的是代码量达到了惊人的 $29.49\text {KB}$，不知道是牛逼科技还是打表优化常数。 

---

## 作者：Prean (赞：3)

这个模数可以变成两个数的乘积，即 $2.4\times 10^7+1$ 和 $3\times 10^7+1$。

不难发现 $n$ 的范围中除了 $13$ 都是这两个数减去 $1$ 的因数。

而题目要求的是 $(x+x^{n-1})^m\pmod{x^n-1}$，循环卷积的长度是 p-1 的因数当然非常快乐。

于是我们收获了一个单次 $O(n\log n)$ 的做法。

并且注意到其实你只需要求零次项，idft的时候直接暴力带入 $\omega_n^0$ 或者直接拉格朗日插值即可，复杂度 $O(n+n\log mod)$。

但是呢，快速幂是没有必要的。我们使用原根做乘法，直接预处理原根的幂，加法的时候用 $\ln$ 转移下即可做到 $O(n)$。~~实际上会被卡空间，不建议~~

$m$ 显然是可以对 $mod-1$ 取模的。

然后考虑把传球的那颗树画出来，不难发现到达这棵树最底部的方案数是组合数，而你只需要求 $O(\frac{m}{n})$ 个位置的组合数。

于是又收获了一个 $O(\frac{mod}{n})$ 的做法。

根号分治一下，能够得到单次 $O(\sqrt{mod})$ 的做法。虽然有 2500 次询问但是一定能跑。

出题人原本认为 $n=13$ 是最难的部分。

于是我贺了一个 Berlekamp–Massey，很快啊，递推式直接扒出来了。
$$f_n=f_{n-1}+7\times f_{n-2}-6\times f_{n-3}-14\times f_{n-4}+9\times f_{n-5}+7\times f_{n-6}-2\times f_{n-7}$$
然后跑一个常系数齐次线性递推直接单次 $O(7^2\sum\log m)$ 随便乱草。

如果觉得不够过瘾可以写成矩阵乘法，然后用特征多项式优化矩快来一个 $O(13^4+13^2\sum\log m)$ 狂暴轰入。

但是实际上 $\sum\log m$ 有 2.5e7，跑个锤子啊！

只能考虑循环节了。对于 $p=3\times 10^7+1$，有 $(x+x^{12})^p\equiv\sum_{i=0}^{p}\binom{p}{i}x^ix^{12i}\equiv x^{12p}+x^p\equiv x^5+x^8\pmod{x^{13}-1}$。

然后能发现 $(x^5+x^8)^p\equiv x^{5p}+x^{8p}\equiv x+x^{12}\pmod{x^{13}-1}$。

也就是说 $p^2$ 一定是模 $3\times 10^7+1$ 的循环节。

同理模 $2.4\times 10^7+1$ 的循环节是 $2.4\times 10^7$。

做一个 lcm 可以发现循环节为 $1800000120000000ll$，可以薄纱了。
```cpp
#include<cstring>
#include<cstdio>
typedef unsigned long long ull;
typedef __uint128_t LL;
typedef unsigned ui;
const ui M=3e7+5,mod1=2.4e7+1,mod2=3e7+1,MOD1=mod1-1,MOD2=mod2-1;
const ull MOD=720000054000001ll,MD=1800000120000000ll;
ui n,m,m1,m2,a[M];char s[10005];
template<const ui mod,const ui g>
struct SolveP{
	ui fac[mod/3000],ifac[mod];
	inline ui pow(ui a,ui b=mod-2){
		ui ans(1);for(;b;b>>=1,a=1ull*a*a%mod)if(b&1)ans=1ull*ans*a%mod;return ans;
	}
	inline void init(){
		ui c(1);fac[0]=1;for(ui i=2;i<mod;++i)if(c=1ull*c*i%mod,!(i%3000))fac[i/3000]=c;
		c=pow(c);for(ui i=mod-1;i<mod;--i)ifac[i]=c,c=1ull*c*i%mod;
	}
	inline ui S(const ui&n,const ui&m){
		return 1ull*ifac[m]*ifac[n-m]%mod;
	}
	inline ui Solve1(const ui&n,const ui&m){
		ui sum(0);const ui&c=pow(g,(mod-1)/n),&ic=pow(g,mod-1-(mod-1)/n);
		for(ui x(c),y(ic),i=1;(i<<1)<n;++i)sum=(sum+pow((x+y)%mod,m))%mod,x=1ull*x*c%mod,y=1ull*y*ic%mod;
		return(2ull*sum+pow(2,m)+pow(mod-2,m))%mod*pow(n)%mod;
	}
	inline ui Solve2(const ui&n,const ui&m){
		const int&lim=m/n;ui sum(0),Fac(fac[m/3000]);for(ui i=ui(m/3000)*3000+1;i<=m;++i)Fac=1ull*Fac*i%mod;
		for(int i=-lim;i<=lim;++i)if(!(m+i*n&1))sum=(sum+1ull*Fac*S(m,m+i*n>>1))%mod;return sum;
	}
};SolveP<mod1,23>T1;SolveP<mod2,14>T2;
namespace Solve13{
	const ull mod=720000054000001ll,p[8]={mod-1,1,7,mod-6,mod-14,9,7,mod-2},q[7]={1,0,2,0,6,0,20};
	struct Poly{
		ull f[7];
		Poly(){f[0]=f[1]=f[2]=f[3]=f[4]=f[5]=f[6]=0;}
		inline ull&operator[](const ui&x){
			return f[x];
		}
		inline Poly operator*(Poly g){
			static ull tmp[13];static Poly ans;
			for(ui i=0;i^7;++i)for(ui j=0;j^7;++j)tmp[i+j]=(tmp[i+j]+(LL)f[i]*g[j])%mod;
			for(ui i=12;i>=7;--i)if(const ull c=tmp[i])for(ui j=0;j^8;++j)tmp[i-j]=(tmp[i-j]+(LL)c*p[j])%mod;
			for(ui i=0;i^7;++i)ans[i]=tmp[i],tmp[i]=0;return ans;
		}
	};
	inline ull Qry(ull m){
		Poly ans,base;ans[0]=base[1]=1;for(;m;m>>=1,base=base*base)if(m&1)ans=ans*base;
		ull sum(0);for(ui i=0;i^7;++i)sum=(sum+ans[i]*q[i])%mod;return sum;
	}
}
inline ull CRT(ui a,ui b){
	return((LL)23999997ll*mod2*a+(LL)5ll*mod1*b)%MOD;
}
signed main(){
	T1.init();T2.init();
	while(~scanf("%u%s",&n,s+1)){
		m=strlen(s+1);for(ui i=1;i<=m;++i)a[i]=s[i]-48,s[i]='\0';m1=m2=0;
		if(n==13){
			ull x=0;for(ui i=1;i<=m;++i)x=(10*x+a[i])%MD;
			printf("%llu\n",Solve13::Qry(x));
		}
		else{
			for(ui i=1;i<=m;++i)m1=(10*m1+a[i])%MOD1,m2=(10*m2+a[i])%MOD2;
			printf("%llu\n",n<=1000?CRT(T1.Solve1(n,m1),T2.Solve1(n,m2)):CRT(T1.Solve2(n,m1),T2.Solve2(n,m2)));
		}
	}
}
```

---

