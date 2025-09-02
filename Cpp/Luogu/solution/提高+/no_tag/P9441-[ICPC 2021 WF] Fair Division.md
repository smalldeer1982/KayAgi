# [ICPC 2021 WF] Fair Division

## 题目描述

$n$ 个人按如下的方式分 $m$ 块钱：先指定一个分数 $f$，$n$ 个人围成一圈，第一个人先拿走总钱数的 $f$，把剩下的钱给第二个人，然后第二个人拿走剩余钱数的 $f$，把剩下的钱交给第三个人...每一个人都从剩余的钱中拿走剩余钱数的 $f$，然后把钱交给下一个人。这种操作可以无限进行下去。

现在给定 $n,m$，你需要构造 $f=\dfrac{p}{q}$，使得 $0<f<1$，并且在分钱无限进行下去之后，最终每个人拿到的钱都是整数。如果有多解，你构造的解需要在 $q$ 尽可能小的情况下 $p$ 尽可能小。如果无解，输出 `impossible`。

$6\le n\le 10^6$，$1\le m\le 10^{18}$。

## 样例 #1

### 输入

```
8 51000
```

### 输出

```
1 2```

## 样例 #2

### 输入

```
6 91000
```

### 输出

```
2 3
```

## 样例 #3

### 输入

```
10 1000000000000000000
```

### 输出

```
impossible
```

# 题解

## 作者：sintle (赞：1)

## 题目链接

- [洛谷 P9441 [ICPC2021 WF] Fair Division](https://www.luogu.com.cn/problem/P9441)

## 解题思路

### 推导公式

设第 $x$ 个人拿到的钱为 $F(x)$ 。

注意到 $\displaystyle F(x)=m\sum_{i=0}^{\infty}(1-f)^{in+x}f$ ，设 $\displaystyle\sum_{i=0}^{\infty}(1-f)^{in+x}$ 为 $S$。

则 $S-(1-f)^nS=(1-f)^x$，可得 $S=\dfrac{(1-f)^x}{1-(1-f)^n}$。

所以 $F(x)=\dfrac{(1-f)^x}{1-(1-f)^n}fm$。

设 $t=(1-f)=\dfrac{r}{q}$。

则 $F(x)=\dfrac{t^x}{1-t^n}(1-t)m=\dfrac{(\dfrac{r}{q})^x(\dfrac{q-r}{q})m}{1-(\dfrac{r}{q})^n}$。

上下同乘以 $q^n$ 并化简得到 $F(x)=\dfrac{r^xq^{n-x-1}(q-r)m}{q^n-r^n}$。

### 证明互质

对于 $q$ 的任何一个因数 $a$，可得 $a$ 也是 $q^n$ 的因数，而 $r$ 与 $q$ 互质，故 $a$ 不是 $r$ 的因数，所以 $a$ 不是 $q^n-r^n$ 的因数，但因为 $a$ 是 $r^xq^{n-x-1}$ 的因数，所以 $r^xq^{n-x-1}$ 与 $q^n-r^n$ 互质。证毕。

### 继续推导

因此，若要使 $F(x)$ 为整数，$q^n-r^n$ 必须能够整除 $(q-r)m$。

所以将 $q^n-r^n$ 展开，得到 $\displaystyle(q-r)\sum_{i=0}^{n}{r^{i}q^{n-i-1}}$。

注意到 $(q-r)$ 已经出现了两次，所以不做考虑，只需要验证 $\displaystyle\sum_{i=0}^{n}{r^{i}q^{n-i-1}}$ 能否整除 $m$ 即可。

因为 $n\ge6$，所以可以直接枚举 $r$ 和 $q$ 的值。

同时 $q^{n-1}$ 需要不大于 $m$，数据范围实际上并不大，只需要用 `__int128` 确保在运算过程中不会超出范围即可。

## 参考代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

static const int INF = 2e18;
int n , m;

int mul(int a , int b)
{
    return min(((__int128_t)a) * b , (__int128_t)INF);
}

int fpow(__int128 a , int b)
{
    int res = 1;
    while(b)
    {
        if(b & 1)
        {
            res = mul(res , a);
        }
        a = mul(a , a);
        b >>= 1;
    }
    return res;
}


signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int q = 2 ; fpow(q , n - 1) <= m && fpow(q , n - 1) != 2147483647 ; q++)
    {
        for(int r = 1 ; r < q ; r++)
        {
            int num = 0;
            for(int i = 0 ; i < n ; i++)
            {
                num = min(num + mul(fpow(r , i) , fpow(q , n - i - 1)) , INF);
            }
            if(m % num == 0)
            {
                cout << q - r << " " << q << '\n';
                return 0;
            }
        }
    }
    cout << "impossible" << '\n';
    return 0;
}
```

---

## 作者：iyaang (赞：1)

[神秘的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17587194.html)

[题目链接](https://www.luogu.com.cn/problem/P9441)

记 $g = 1 - f$，即传递下去的宝藏有多少。如果一个海盗在第一轮得到了 $x$，则第二轮将得到 $g^n x$，第 $T$ 轮得到 $g^{Tn} x$，于是在极限情况下总共得到的宝藏为 $\dfrac{x}{1 - g^n}$。对于第 $i$ 个海盗（取 $i \in [0,n - 1]$），显然 $x_i = g^i (1 - g) m$，于是第 $i$ 个海盗获得的总宝藏数为 $\dfrac{g^i (1 - g) m}{1 - g^n}$。

取 $g$ 为最简分数 $\dfrac{a}{b}$，有上式为 $\dfrac{\frac{a^i}{b^i} \frac{b - a}{b} m}{1 - \frac{a^n}{b^n}}$，上下同乘 $b^n$ 得到 $\dfrac{a^i b^{n - i - 1} (b - a) m}{b^n - a^n}$，我们要做的是使得这个式子为整数。假如说 $b$ 存在因子 $p$，则 $p \mid b^n$，注意到 $a,b$ 互质，所以 $p \nmid a$，$p \nmid a^n$，自然 $p \nmid b^n - a^n$。也就是说 $a^i b^{n - i -1}$ 和 $b^n - a^n$ 是互质的，所以这要求 $b^n - a^n \mid (b - a)m$。化简一下这个东西，$b^n - a^n = (a - b) \times [a^{n - 1} + a^{n - 2} \times b + a^{n - 3} \times b^2 + \cdots + b^{n - 1}]$，然后直接判 $m$ 是否被中括号里头那一坨东西整除即可。

这也就是为什么 $n \geq 6$ 的原因，我们可以使用枚举的方法来尝试出 $a,b$，因为指数的范围限制了 $b$ 的大小，使得枚举答案的上界并不大。不过计算判边界还是要拿 `__int128` 转一下，防止结果炸了。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define int long long
#define eb emplace_back
#define pb pop_back
#define ins insert
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define power(x) ((x)*(x))
#define gcd(x,y) (__gcd((x),(y)))
#define lcm(x,y) ((x)*(y)/gcd((x),(y)))
#define lg(x,y)  (__lg((x),(y)))
using namespace std;
 
namespace FastIO
{
    template<typename T=int> inline T read()
    {
        T s=0,w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        return s*w;
    }
    template<typename T> inline void read(T &s)
    {
        s=0; int w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        s=s*w;
    }
    template<typename T,typename... Args> inline void read(T &x,Args &...args)
    {
        read(x),read(args...);
    }
    template<typename T> inline void write(T x,char ch)
    {
        if(x<0) x=-x,putchar('-');
        static char stk[25]; int top=0;
        do {stk[top++]=x%10+'0',x/=10;} while(x);
        while(top) putchar(stk[--top]);
        putchar(ch);
        return;
    }
}
using namespace FastIO;
 
namespace MTool
{   
    #define TA template<typename T,typename... Args>
    #define TT template<typename T>
    static const int Mod=998244353;
    TT inline void Swp(T &a,T &b) {T t=a;a=b;b=t;}
    TT inline void cmax(T &a,T b) {a=a>b?a:b;}
    TT inline void cmin(T &a,T b) {a=a<b?a:b;}
    TT inline void Madd(T &a,T b) {a=a+b>Mod?a+b-Mod:a+b;}
    TT inline void Mdel(T &a,T b) {a=a-b<0?a-b+Mod:a-b;}
    TT inline void Mmul(T &a,T b) {a=a*b%Mod;}
    TT inline void Mmod(T &a) {a=(a%Mod+Mod)%Mod;}
    TT inline T Cadd(T a,T b) {return a+b>=Mod?a+b-Mod:a+b;}
    TT inline T Cdel(T a,T b) {return a-b<0?a-b+Mod:a-b;}
    TT inline T Cmul(T a,T b) {return a*b%Mod;}
    TT inline T Cmod(T a) {return (a%Mod+Mod)%Mod;}
    TA inline void Madd(T &a,T b,Args... args) {Madd(a,Cadd(b,args...));}
    TA inline void Mdel(T &a,T b,Args... args) {Mdel(a,Cadd(b,args...));}
    TA inline void Mmul(T &a,T b,Args... args) {Mmul(a,Cmul(b,args...));}
    TA inline T Cadd(T a,T b,Args... args) {return Cadd(Cadd(a,b),args...);}
    TA inline T Cdel(T a,T b,Args... args) {return Cdel(Cdel(a,b),args...);}
    TA inline T Cmul(T a,T b,Args... args) {return Cmul(Cmul(a,b),args...);}
    TT inline T qpow(T a,T b) {int res=1; while(b) {if(b&1) Mmul(res,a); Mmul(a,a); b>>=1;} return res;}
    TT inline T qmul(T a,T b) {int res=0; while(b) {if(b&1) Madd(res,a); Madd(a,a); b>>=1;} return res;}
    TT inline T spow(T a,T b) {int res=1; while(b) {if(b&1) res=qmul(res,a); a=qmul(a,a); b>>=1;} return res;}
    TT inline void exgcd(T A,T B,T &X,T &Y) {if(!B) return X=1,Y=0,void(); exgcd(B,A%B,Y,X),Y-=X*(A/B);}
    TT inline T Ginv(T x) {T A=0,B=0; exgcd(x,Mod,A,B); return Cmod(A);}
    #undef TT
    #undef TA
}
using namespace MTool;
 
inline void file()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    return;
}
 
bool Mbe;
 
namespace LgxTpre
{
    static const int MAX=200010;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    static const int mod=1e9+7;
    static const int bas=131;
    
    int n,m;
    static const int infty=2e18;
    
    inline void lmy_forever()
    {
    	auto mul128=[&](int a,int b)->int
    	{
    		return min(((__int128_t)a)*b,(__int128_t)infty);
		};
		auto pow128=[&](int a,int b)->int
		{
			int res=1;
			while(b) {if(b&1) res=mul128(res,a); a=mul128(a,a),b>>=1;}
			return res;
		};
		
    	read(n,m);
    	for(int b=2;pow128(b,n-1)<=m;++b) for(int a=1;a<b;++a)
    	{
    		int sum=0;
    		for(int i=0;i<n;++i) sum=min(sum+mul128(pow128(a,i),pow128(b,n-1-i)),infty);
    		if(m%sum==0) return write(b-a,' '),write(b,'\n');
		}
		puts("impossible");
    }
}

bool Med;

signed main()
{
//  file();
    fprintf(stderr,"%.3lf MB\n",abs(&Med-&Mbe)/1048576.0);
    int Tbe=clock();
    LgxTpre::lmy_forever();
    int Ted=clock();
    cerr<<1e3*(Ted-Tbe)/CLOCKS_PER_SEC<<" ms\n";
    return (0-0);
}
```

---

