# [AGC047C] Product Modulo

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc047/tasks/agc047_c

$ P $ を素数 $ 200\,003 $ とします。$ N $ 個の整数 $ A_1,\ A_2,\ \ldots,\ A_N $ が与えられるので、$ N\ \cdot\ (N-1)\ /\ 2 $ 個すべての非順序対 $ (A_i,\ A_j) $ ($ i\ <\ j $) に対する $ ((A_i\ \cdot\ A_j)\ \bmod\ P) $ の和を求めてください。

和を $ P $ で割った余りを求めるのではないことに注意してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 200\,000 $
- $ 0\ \leq\ A_i\ <\ P\ =\ 200\,003 $
- 入力中のすべての値は整数である。

### Sample Explanation 1

$ 0 $ でない積は以下の通りです。 - $ 2019\ \cdot\ 2020\ \bmod\ P\ =\ 78320 $ - $ 2019\ \cdot\ 200002\ \bmod\ P\ =\ 197984 $ - $ 2020\ \cdot\ 200002\ \bmod\ P\ =\ 197983 $ よって、答えは $ 0\ +\ 78320\ +\ 197984\ +\ 0\ +\ 0\ +\ 197983\ =\ 474287 $ となります。

## 样例 #1

### 输入

```
4
2019 0 2020 200002```

### 输出

```
474287```

## 样例 #2

### 输入

```
5
1 1 2 2 100000```

### 输出

```
600013```

# 题解

## 作者：rui_er (赞：6)

显然不能暴力算两两的乘积，而积取模而结果不取模提示我们模数肯定有用。

所有为 $0$ 的 $a_i$ 对答案不会产生任何贡献，可以直接删除，下文不再考虑这种情况。同时我们约定，下文的运算（除特殊说明外）均为模 $P$ 意义下的结果。

设 $g$ 为 $P$ 的原根，则每个 $a_i$ 都可以表示为 $g^{c_i}$ 的形式，而 $a_ia_j=g^{c_i+c_j}$。因此设 $a$ 中等于 $g^{i}$ 的数有 $A_i$ 个，则乘积为 $g^k$ 的有序数对有 $\sum\limits_{i+j=k}A_iA_j$ 个，是卷积形式，用 FFT 优化之。

注意根据题意，答案需要去掉所有 $a_i^2$ 的贡献。

时间复杂度为 $\Theta(P\log P)$。

我的代码中 $g=114513$，当然你也可以用 $2$ 或者其他原根。

```cpp
// Problem: C - Product Modulo
// Contest: AtCoder - AtCoder Grand Contest 047
// URL: https://atcoder.jp/contests/agc047/tasks/agc047_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(ll x=(y);x<=(z);x++)
#define per(x,y,z) for(ll x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
typedef complex<double> cp;
const ll N = 2e6+5, P = 200003, g = 114513;
const double pi = acos(-1);

ll n, a[N], pw[N], pos[N], cnt[N], rev[N], ans;
cp A[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
void change(cp* a, ll n) {
	rep(i, 0, n-1) {
		rev[i] = rev[i >> 1] >> 1;
		if(i & 1) rev[i] |= n >> 1;
	}
	rep(i, 0, n-1) if(i < rev[i]) swap(a[i], a[rev[i]]);
}
void FFT(cp* a, ll n, ll sgn) {
	change(a, n);
	for(ll l = 2, o = 1; l <= n; l <<= 1, o <<= 1) {
		cp w(cos(2.0*pi/l), sgn*sin(2.0*pi/l));
		for(ll i = 0; i < n; i += l) {
			cp now = 1;
			rep(j, i, i+o-1) {
				cp u = a[j], v = a[j + o];
				a[j] = u + v * now;
				a[j + o] = u - v * now;
				now *= w;
			}
		}
	}
	if(sgn == -1) rep(i, 0, n-1) a[i] /= n;
}

int main() {
	pw[0] = 1;
	pos[1] = 0;
	rep(i, 1, P-2) {
		pw[i] = g * pw[i-1] % P;
		pos[pw[i]] = i;
	}
	scanf("%lld", &n);
	rep(i, 1, n) scanf("%lld", &a[i]);
	rep(i, 1, n) if(a[i]) ++cnt[pos[a[i]]];
	rep(i, 0, P-2) A[i] = cnt[i];
	ll m = 1;
	for(; m <= P + P; m <<= 1);
	FFT(A, m, 1);
	rep(i, 0, m-1) A[i] *= A[i];
	FFT(A, m, -1);
	rep(i, 0, 2*(P-2)) ans += (ll)(A[i].real() + .5) * pw[i%(P-1)];
	rep(i, 0, P-2) ans -= cnt[i] * pw[2*i%(P-1)];
	printf("%lld\n", ans / 2);
	return 0;
}
```

---

## 作者：Amidst (赞：4)

感觉几乎是 FFT 裸题。这个套路好像在场上见过一次，但是我只会暴力 FFT 卷积，值域大一点就废了，喜提 50。

## 思路

注意到题目让我们求出

$$\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{i-1}(a_i\times a_j)\bmod P$$

观察到我们要求的结果是先取模再相加，不妨考虑一种形式，使之能够将积转化为和的形式。

然后就是经典套路。用原根将 $(a_i\times a_j)\bmod P$ 转化为 $g_P^{c_i+c_j} \bmod P$。

注意到原根的性质，所以 $1,g_P,g_P^2,g_P^3,\cdots,g_P^{P-2}$ 一定是 $P$ 的一个完全剩余系，这样我们就可以把所有的 $a_i$ 表示为 $g_P^{c_i}$。

于是就有了一个很明显的卷积形式，注意到求和以后没有再模，用 FFT 即可。

观察到题面中的条件是 $1\le i < j \le n$，所以要另外减去 $(a_i \times a_i)\bmod P$ 的贡献。

现在我们就算出了

$$\sum\limits_{i=1}^{n}\sum\limits_{j=1}^n(a_i\times a_j)\bmod P[i\ne j]$$

然后将得到的结果除以 $2$ 即可。

## 代码

~~感谢 @[fzs06](https://www.luogu.com.cn/user/367663) 提供的没用的超高精度圆周率。~~

```cpp
#include <bits/stdc++.h>
#define int long long
#define mod 200003
#define pi 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
using namespace std;
namespace fft
{
	template<typename _Tp=double>
	class fcomplex
	{
		public:
			_Tp x,y;
			fcomplex(_Tp X=0,_Tp Y=0) : x(X),y(Y) {}
			inline fcomplex<_Tp> operator+(const fcomplex<_Tp> b) const {return fcomplex(this->x+b.x,this->y+b.y);}
			inline fcomplex<_Tp> operator-(const fcomplex<_Tp> b) const {return fcomplex(this->x-b.x,this->y-b.y);}
			inline fcomplex<_Tp> operator*(const fcomplex<_Tp> b) const {return fcomplex(this->x*b.x-this->y*b.y,this->x*b.y+this->y*b.x);}
			inline fcomplex<_Tp> operator*(const _Tp b) const {return fcomplex(this->x*b,this->y*b);} 
			inline fcomplex<_Tp> operator/(const _Tp b) const {return fcomplex(this->x/b,this->y/b);} 
			inline fcomplex<_Tp>& operator+=(const fcomplex<_Tp> b) {this->x+=b.x;this->y+=b.y;return *this;}
			inline fcomplex<_Tp>& operator-=(const fcomplex<_Tp> b) {this->x-=b.x;this->y-=b.y;return *this;}
			inline fcomplex<_Tp>& operator*=(const fcomplex<_Tp> b) {fcomplex<_Tp> tmp=(*this)*b;this->x=tmp.x;this->y=tmp.y;return *this;}
			inline fcomplex<_Tp>& operator*=(const _Tp b) {this->x*=b;this->y*=b;return *this;} 
			inline fcomplex<_Tp>& operator/=(const _Tp b) {this->x/=b;this->y/=b;return *this;} 
	};
	template<typename _Tp=double>
	void Fast_Fourier_Transform(fcomplex<> a[],int rv[],_Tp type,int lim)
	{
		for(int i=1;i<=lim;i++)
			if(i<rv[i])
				swap(a[i],a[rv[i]]);
		fcomplex<> k,x,y,tmp;
		for(int mid=1;mid<lim;mid<<=1)
		{
			int r=(mid<<1);
			k=fcomplex<>(cos(pi/mid),type*sin(pi/mid));
			for(int j=0;j<lim;j+=r)
			{
				tmp=fcomplex<>(1,0);
				for(int t=0;t<mid;t++)
				{
					x=a[j|t];
					y=tmp*a[j|t|mid];
					a[j|t]=x+y;
					a[j|t|mid]=x-y;
					tmp*=k;
				}
			}
		}
		if(type==1)
			return;
		for(int i=0;i<=lim;i++)
			a[i]/=1.0*lim;
	}
	#define FFT Fast_Fourier_Transform
};
int n,m,lim=1,l=-1;
int rev[800005],pw[800005],pos[800005],a[800005],cnt[800005];
fft::fcomplex<> f[800005];
signed main()
{
	pw[0]=1;
	pos[1]=0;
	for(int i=1;i<mod-1;i++)
	{
		pw[i]=pw[i-1]*2%mod;
		pos[pw[i]]=i;
	}
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		if(a[i])
			cnt[pos[a[i]]]++;
	}
	for(int i=0;i<mod-1;i++)
		f[i].x=cnt[i];
	while(lim<=(mod<<1))
	{
		lim<<=1;
		l++;
	}
	for(int i=1;i<=lim;i++)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<l);
	FFT(f,rev,1,lim);
	for(int i=0;i<=lim;i++)
		f[i]*=f[i];
	FFT(f,rev,-1,lim);
	int ans=0;
	for(int i=0;i<=(mod-2<<1);i++)
		ans+=(int)(f[i].x+0.5)*pw[i%(mod-1)];
	for(int i=0;i<mod-1;i++)
		ans-=cnt[i]*pw[(i<<1)%(mod-1)];
	printf("%lld\n",ans/2);
	return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：0)

由于 $P$ 不大，不妨枚举 $w$ 计算满足 $a_i \times a_j \bmod P = w$ 的 $i,j$ 数量。注意到这一个类似卷积但是是乘法的形式，而由于 $P$ 是质数，立马可以想到原根，不妨 $a_i = g^{A_i},w = g^{W}$，问题变为求解 $A_i + A_j \bmod (P-1) = W$ 的 $i,j$ 数量，直接跑一遍 FFT 做卷积即可做到 $O(P \log P)$。

[代码](https://atcoder.jp/contests/agc047/submissions/60123038)

---

## 作者：songhongyi (赞：0)

设 $f_i$ 为 $i$ 在 $a$ 中出现的次数。设 $g_i$ 表示满足乘积在模意义下为 $i$ 的**无序且允许相等**的二元组数量。

不难发现有：
$$
g_i = \sum_{ab\bmod P = i} f_a\cdot f_b
$$
注意到答案为：
$$
\frac 1 2\left(\sum _{i=0}^{P-1} i \cdot g_i -\sum_{i=0}^{P-1} \left(i^2\bmod p\right)\cdot f_i\right)
$$
其中减去的部分为计算过程中 $a,b$ 为同位置数的情况，而除以二的系数是处理有序。

卷积的形式和 P3321 很像，考虑类似的解决办法。我们取 $P$ 的原根 $G$，设 $f'_i = f_{G^i}$，$g'_i = g_{G^i}$。对于 $f_0$ 与 $g_0$ 不难单独处理。其他部分的式子可改为：
$$
g'_i = \sum_{a+b\bmod \left(P-1\right) = i} f'_a\cdot f'_b
$$
这就是一个循环卷积的形式了，可以使用 FFT 处理。复杂度 $O(n+P \log P)$。

因为不可取模，不要使用 NTT。

```cpp
//
// Problem: [AGC047C] Product Modulo
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc047_c
// Memory Limit: 1 MB
// Time Limit: 2000 ms

#include <cmath>
#include <iostream>
using namespace std;
struct Complex
{
    long double x, y;
    Complex( long double x = 0, long double y = 0 )
    {
        this->x = x;
        this->y = y;
    }
    Complex operator-( const Complex& b ) const
    {
        return Complex( x - b.x, y - b.y );
    }

    Complex operator+( const Complex& b ) const
    {
        return Complex( x + b.x, y + b.y );
    }

    Complex operator*( const Complex& b ) const
    {
        return Complex( x * b.x - y * b.y, x * b.y + y * b.x );
    }
};
const int N = 800010, P = 200003;
int rev[ N ];
const long double PI = acos( -1 );
void change( Complex y[], int len )
{
    for ( int i = 0; i < len; i++ )
    {
        rev[ i ] = rev[ i >> 1 ] >> 1;
        if ( i & 1 )
        {
            rev[ i ] |= len >> 1;
        }
    }
    for ( int i = 0; i < len; i++ )
    {
        if ( i < rev[ i ] )
        {
            swap( y[ i ], y[ rev[ i ] ] );
        }
    }
}
void ntt( Complex y[], int len, int flag )
{
    change( y, len );
    for ( int l = 2; l <= len; l *= 2 )
    {
        Complex wn( cos( 2 * PI / l ), sin( flag * 2 * PI / l ) );
        for ( int i = 0; i < len; i += l )
        {
            Complex w( 1, 0 );
            for ( int j = i; j < i + l / 2; j++ )
            {
                Complex yl = y[ j ];
                Complex yr = w * y[ j + l / 2 ];
                y[ j ] = yl + yr;
                y[ j + l / 2 ] = yl - yr;
                w = w * wn;
            }
        }
    }
    if ( flag == -1 )
    {
        for ( int i = 0; i < len; i++ )
        {
            y[ i ].x /= len;
        }
    }
}
Complex x1[ N ], x2[ N ];
long long int res[ N ];
void time( int* a, int* b, long long int* ans, int n )
{
    int len = 1;
    while ( len < n * 2 )
    {
        len <<= 1;
    }
    for ( int i = 0; i < len; i++ )
    {
        x1[ i ] = x2[ i ] = Complex();
    }
    for ( int i = 0; i < n; i++ )
    {
        x1[ i ].x = a[ i ];
    }
    for ( int i = 0; i < n; i++ )
    {
        x2[ i ].x = b[ i ];
    }
    ntt( x1, len, 1 );
    ntt( x2, len, 1 );
    for ( int i = 0; i < len; i++ )
    {
        x1[ i ] = x1[ i ] * x2[ i ];
    }
    ntt( x1, len, -1 );
    for ( int i = 0; i < len; i++ )
    {
        ans[ i ] = x1[ i ].x + 0.5;
    }
    for ( int i = 0; i < n; i++ )
    {
        ans[ i ] = ans[ i ] + ans[ i + n ];
        ans[ i + n ] = 0;
    }
}
int pw[ N ], pos[ N ], cnt[ N ];
int main()
{
    pw[ 0 ] = 1;
    pos[ 1 ] = 0;
    for ( int i = 1; i < P - 1; i++ )
    {
        pw[ i ] = 2 * pw[ i - 1 ] % P;
        pos[ pw[ i ] ] = i;
    }
    int n;
    cin >> n;
    for ( int i = 1; i <= n; i++ )
    {
        int t;
        cin >> t;
        if ( t )
        {
            cnt[ pos[ t ] ]++;
        }
    }
    time( cnt, cnt, res, P - 1 );
    long long int ans = 0;
    for ( int i = 0; i < P - 1; i++ )
    {
        ans += 1ll * pw[ i ] * res[ i ];
        ans -= 1ll * cnt[ i ] * pw[ ( i + i ) % ( P - 1 ) ];
    }
    cout << ans / 2 << endl;
}
```

---

