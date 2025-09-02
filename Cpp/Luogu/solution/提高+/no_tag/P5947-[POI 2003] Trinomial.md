# [POI 2003] Trinomial

## 题目描述

求 $(x^2+x+1)^n$ 的第 $i$ 项系数。

## 说明/提示

对于 $100\%$ 的数据，$1 \le k \le 10000$，$0\le n\le 10^{15}$，$0\le i\le 2\times n$。

## 样例 #1

### 输入

```
5
2 0
7 4
4 5
5 3
8 15```

### 输出

```
1
2
1
0
2```

# 题解

## 作者：明月夜 (赞：5)

前置芝士：

**二项式定理**：  

$$ (x+y)^n=\sum_{i=1}^nC_n^ix^iy^{n-i}  $$
               

**卢卡斯定理**： 

$$ Lucas(n,m,p)=C_{n \bmod p}^{m \bmod p}Lucas(n/p,m/p,p) $$


颓一下柿子

$$ (x^2+x+1)^n=((x-1)^2+3x)^n=\sum_{i=1}^nC_n^i(x-1)^{2i}(3x)^{n-i}  $$

可以发现除了 $ C_n^n(x-1)^{2n} $ 这一项，其他项系数的因子都有 $ 3 $

显然是没有意义的

所以只要考虑 $ (x-1)^{2n} $ 中第 $ i $ 项的系数

 $$ (x-1)^{2n}=\sum_{i=1}^{2n}C_{2n}^ix^{i}(-1)^{2n-i} $$

第 $ i $ 项系数即 $ C_{2n}^{i}(-1)^{2n-i} $

**卢卡斯定理**求一下就好了

 *★,°*:.☆(￣▽￣)/$:*.°★* 。

~~码风毒瘤莫喷~~

```cpp
#include<bits/stdc++.h>
#define R register
#define LL long long
using namespace std;
inline long long read(){
	long long x=0,d=1; char y=getchar();
	while(y<'0'||y>'9'){if(y=='-')d=-1;y=getchar();}
	while(y>='0'&&y<='9'){x=(x<<3)+(x<<1)+(y^'0');y=getchar();}
	return x*d;
}
int k;
LL n,i,fact[4],ny[4];
int Cn(int a,int b){return a>b?0:fact[b]*ny[a]*ny[b-a]%3;}
int lucas(LL a,LL b){return b?lucas(a/3,b/3)*Cn(a%3,b%3)%3:1;}
int main(){
	k=read();
	fact[0]=fact[1]=ny[0]=ny[1]=1;
	fact[2]=ny[2]=2;
	while(k--){
		n=read(); i=read();
		printf("%d\n",(lucas(i,n<<1)*(i%2?-1:1)+3)%3);
	}
	return 0;
}
```


---

## 作者：LightningUZ (赞：1)

### 题意简述

$T$组数据。给定$n,m$，求$(x^2+x+1)^n$中，$x^m$项的系数是多少。答案对$3$取膜。
（这个膜数很神奇！注意！突破点就在这！）

$T<=1e4$，$n<=1e15$，$m<=2n$。

### 思路框架

答案是$C_{2n}^m\times (m\% 2+1)$，对$3$取膜（写个$Lucas$即可）

### 具体思路

首先，我们分括号讨论。因为是$(x^2+x+1)^n$，所以有$n$个括号，并且每个括号可以出$x^2,x,1$。然后我们要求，有多少种方案使得每个括号中出的数积为$x^m$。

我们开始打草稿：我们把$n$个括号从$1$到$n$顺序编号，每个括号上面有两个复选框。打了几个勾，就是代表出$x$的多少次方。具体来说就是：
一个都没打勾，代表出$x^0$（$x^0$就是$1$）；其中一个打了勾，代表出$x$；两个都打了勾，代表出$x^2$。

如图所示是$n=4$的情况：
![blog1.jpg](https://i.loli.net/2020/02/04/DsbuTYf5nrc3mRk.jpg)

我们这样勾选：
![blog2.jpg](https://i.loli.net/2020/02/04/4E2JqIRoXkTnzha.jpg)

那就相当于：
第一个括号出$x$
第二个括号出$x^2$
第三个括号出$x$
第四个括号出$x$
那它就会给$x^5$那一项贡献一种情况。

那么我们现在考虑$x^m$项的系数，换句话说就是有多少种方法凑出$x^m$。

显然，上面的复选框中，我们每打一个勾，乘出来就多一个$x$。（上面打了$5$个勾，乘起来就是$x^5$）然后一共有$2n$个复选框，所以答案就是$C_{2n}^m$。

这就完了？不！这样考虑有重复的！

假如第$i$个括号出的是$x$，那就相当于在$i$上面两个复选框中，**其中一个**要打勾。而我们**只在意数量**，具体打勾打上面那个框还是下面的那个，**是一样的**。那就会把一个答案算两遍，所以要除以$2$。

假设我们有$k$个括号出的是$x$，那么我们的答案就要除以一个$2^k$。

首先，$k$和$m$肯定是同奇偶的。

> 稍微证一下（会证跳过）： 有$k$个括号出$x$，那剩下$x^{m-k}$都是由出$1$或$x^2$组成的。$m-k$由若干个$0$和$2$相加而成，所以$m-k$是偶数。所以$m$和$k$同奇偶。

然后，在模三意义下，**2的逆元就是其本身**！所以，除以一个$2^k$，就相当于乘以一个$2^k$。

还没完，我们继续化。我们发现，$2$的幂除以$3$的余数是：$2,1,2,1,2,1...$。具体点说，$2^k\% 3=(k\% 2)+1$。而$k$和$m$又同奇偶，所以，所有的$k\% 2+1$都等于$m\% 2+1$。

综上，我们的答案就是$C_{2n}^m\times (m\% 2+1)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Flandre_Scarlet
{
    #define int long long 
    #define F(i,l,r) for(int i=l;i<=r;++i)
    #define D(i,r,l) for(int i=r;i>=l;--i)
    #define Fs(i,l,r,c) for(int i=l;i<=r;c)
    #define Ds(i,r,l,c) for(int i=r;i>=l;c)
    #define MEM(x,a) memset(x,a,sizeof(x))
    #define FK(x) MEM(x,0)
    #define Tra(i,u) for(int i=G.Start(u),__v=G.To(i);~i;i=G.Next(i),__v=G.To(i))
    #define p_b push_back
    #define sz(a) ((int)a.size())
    #define iter(a,p) (a.begin()+p)
    void R1(int &x)
    {
        x=0;char c=getchar();int f=1;
        while(c<'0' or c>'9') f=(c=='-')?-1:1,c=getchar();
        while(c>='0' and c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
        x=(f==1)?x:-x;
    }
    void Rd(int cnt,...)
    {
        va_list args;
        va_start(args,cnt);
        F(i,1,cnt) 
        {
            int* x=va_arg(args,int*);R1(*x);
        }
        va_end(args);
    }

    int n,m;
    void Input()
    {
        Rd(2,&n,&m);
    }

    int c[4][4];
    int C(int n,int m) //卢卡斯定理求C(n,m)%3
    {
        if (n==0 and m==0) return 1;
        return C(n/3,m/3)*c[n%3][m%3]%3;
    }
    void Soviet()
    {
        c[0][0]=1;
        c[1][1]=c[1][0]=1;
        c[2][0]=c[2][2]=1;c[2][1]=2; //预处理<3的组合数
        printf("%lld\n",C(2*n,m)*(m%2+1)%3); //用上面的式子
    }

    #define Flan void
    Flan IsMyWife()
    {
        int t;R1(t);
        F(i,1,t)
        {
            Input();
            Soviet();
        }
    }
    #undef int //long long 
}
int main(){
    Flandre_Scarlet::IsMyWife();
    getchar();getchar();
    return 0;
}
```

---

## 作者：Expert_Dream (赞：0)

首先，前置知识：二项式定理：$(x+y)^n = \sum_1^{n} C_n^ix^iy^{n-i}$。

我们将题目式子展开：$(x^2+x+1)^n = ((x-1)^2+3x)^n = \sum_{i=1}^n C_n^i(x-1)^{2i}(3x)^{n-i}$。

而题目要求，答案取模 $3$。所以只有在 $n-i =0$ 时，$3x^{n-i}$ 项为 $0$。此时才对答案有贡献。

于是只需要求 $i=n$ 时的贡献。即 $(x-1)^{2n}$。

此时再用一次二项式定理。

得到 $(x-1)^{2n} = \sum_i^{2n} C_{2n}^ix^i(-1)^{2n-i}$。

于是可以用 lucas 定理求出答案。

---

## 作者：可爱的小棉羊 (赞：0)

注意到：

$(x^2+x+1)^n=(x^2-x+3x+1)^n$

注意到 $3x$ 在模 $3$ 意义下对答案无贡献。

$$(x^2-2x+1)^n=(x-1)^{2n}=\sum_{i=0}^{2n}\binom{2n}i(-1)^{2n-i}x^i$$

大力卢卡斯定理，做完了。

代码如下：

```
#include <bits/stdc++.h>
using namespace std;
long long n,A,t,C[5][5];
int lucas(long long a,long long b){
	if(b==0)return 1;
	return (lucas(a/3,b/3))*C[a%3][b%3]%3;
}
signed main() {
//	ios::sync_with_stdio(false);
//	ios_base::sync_with_stdio(false);
//	cin.tie(0), cout.tie(0);
	C[0][0]=1;
	C[1][0]=1;
	C[2][0]=1;
	C[1][1]=1;
	C[2][1]=2;
	C[2][2]=1;
	cin>>t;
	while(t--){
		cin>>n>>A;
		cout<<(lucas(2*n,A)*(((2*n-A)&1)? 2:1)%3)%3<<"\n"; 
	}
	return 0;
}

```

---

## 作者：wimg6_ (赞：0)

规定本文中所有等式为在模 $3$ 意义下的等式。

$$(x^2+x+1)^n=(x^2+x-3x+1)^n=(x^2-2x+1)^n=(x-1)^{2n}$$

根据二项式定理，得：

$$(x-1)^{2n}=\sum_{i=1}^{2n}(-1)^{2n-i}C_{2n}^ix^i$$

那么第 $i$ 项系数就是 $(-1)^{2n-i}C_{2n}^i$ 了。

但是由于 $i$ 和 $n$ 都很大，所以再用一次卢卡斯定理就行了。


```cpp
#include<bits/stdc++.h>
using namespace std;
long long k,n,i,f[10];
long long read(){
    long long x=0,p=1;char ac=getchar();
    while(ac!='-' && (ac<'0' || ac>'9')) ac=getchar();
    if(ac=='-') p=-1,ac=getchar();
    while(ac>='0' && ac<='9') x=x*10+ac-'0',ac=getchar();
    return x*p;
}
long long calc(long long n,long long m){
    if(n>m) return 0;
    return f[n]*f[m]*f[m-n]%3;
}
long long Lucas(long long n,long long m){
    if(m==0) return 1;
    return Lucas(n/3,m/3)*calc(n%3,m%3)%3;
}
int main(){
    // freopen("test.out","w",stdout);
    k=read();
    f[0]=1,f[1]=1,f[2]=2;
    while(k--){
        n=read(),i=read();
        if(i%2) printf("%lld\n",(3-Lucas(i,n*2))%3);
        else printf("%lld\n",(Lucas(i,n*2))%3);
    }
    return 0;
}
```


本题还有其他类似做法，但最后都能得到相同式子，比如：

$$(x^2+x+1)^n=(x^2+x+3x+1+3)^n=(x+2)^{2n}$$

那么根据二项式定理，第 $i$ 项就是 $2^{2n-i}C_{2n}^i=(2-3)^{2n-i}C_{2n}^i=(-1)^{2n-i}C_{2n}^i$。

进一步观察，发现本题只要将原式子配成任意完全平方式，再用完全平方公式将其转变为二项式，最后用二项式展开做就行了。

那么根据本题可得出一个小技巧，即把对应多项式转换为二项式，再进行处理。

---

## 作者：Fzrcy (赞：0)

考虑到模数为 $3$，我们可以将原式变形，凑出和 $3$ 有关的项并消去。
$$
(x^2+x+1)^n\equiv ((x-1)^2+3x)^n\equiv (x-1)^{2n}\pmod3
$$
将 $(x-1)^{2n}$ 展开：
$$
(x-1)^{2n}=\sum_{i=0}^{2n}\tbinom{2n}{i}x^i(-1)^{2n-i}
$$
所以答案为 $\binom{2n}{m}(-1)^{2n-m}$，组合数可以用卢卡斯定理计算，时间复杂度为 $O(k\log_3n)$。

```cpp
// qwq
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int fac[]={1,1,2};
constexpr int inv[]={1,1,2};
int C(int n,int m){
    if(n<m||n<0||m<0)return 0;
    return fac[n]*inv[m]*inv[n-m]%3;
}
ll Lucas(ll n,ll m){
    return !m?1:C(n%3,m%3)*Lucas(n/3,m/3)%3;
}
int main(){
    ll T,n,m,ret;
    cin>>T;
    while(T--){
        cin>>n>>m,ret=Lucas(2*n,m);
        if((2*n-m)&1)ret=(3-ret)%3;
        cout<<ret<<'\n';
    }
    return 0;
}
```



---

## 作者：A_Đark_Horcrux (赞：0)

看起来没有头绪的题目，其实关键在于：__输出 $x_i\bmod3$ 的结果。__

考虑把原式转化成一个系数带 3 的式子：

$$(x^2+x+1)^n$$

$$=[(x-1)^2+3x]^n$$

二项式定理展开得

$$=(x-1)^{2n}-C^{1}_{n}(x-1)^{2(n-1)}\times3x+C^{2}_{n}(x-1)^{2(n-2)}\times(3x)^2+...+(3x)^n$$

发现后面的所有项中都包含了 3，也就是说系数模三以后都没有了 qwq

因此输出 $(x-1)^{2n}$ 中的系数即可。

```cpp
#include<cstdio>
using namespace std;
typedef long long ll;
const ll mod=3;
inline ll read()
{
	ll s=0; char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') s=(s<<3)+(s<<1)+(c&15),c=getchar();
	return s;
}
ll T,x,y,a[1000010];
ll pow(ll x,ll y)
{
	ll l=1;
	while(y)
	{
		if(y&1) l=l*x%mod;
		x=x*x%mod; y>>=1;
	}
	return l;
}//快速幂
ll C(ll n,ll m) {return m>n?0:(a[n]*pow(a[m],mod-2))%mod*pow(a[n-m],mod-2)%mod;}//组合数
ll lucas(ll n,ll m) {return !m?1:C(n%mod,m%mod)*lucas(n/mod,m/mod)%mod;}//卢卡斯
int main()
{
	a[0]=a[1]=1;
	for(int i=2;i<100010;i++) a[i]=a[i-1]*i%mod;
	T=read();
	while(T--)
	{
		x=read(),y=read();
		printf("%lld\n",(lucas(x*2,y)*pow(-1,2*x-y)+mod)%mod);
	}
	return 0;
}
```


---

