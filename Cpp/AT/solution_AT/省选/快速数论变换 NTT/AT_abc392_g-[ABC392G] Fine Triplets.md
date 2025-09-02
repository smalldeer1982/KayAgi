# [ABC392G] Fine Triplets

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc392/tasks/abc392_g

当三个整数 $A,B,C$（满足 $A < B < C$）满足 $B - A = C - B$ 时，称 $(A,B,C)$ 为**好的三元组**。  
给定一个包含 $N$ 个元素的正整数集合 $S = \{\ S_1, S_2, \dots, S_N\ \}$，求满足 $A,B,C \in S$ 的好的三元组的个数。

## 说明/提示

### 约束条件

- 输入均为整数
- $1 \leq N \leq 10^6$
- $1 \leq S_i \leq 10^6$
- $S$ 中的元素互不相同

### 样例解释 1

$S = \{8,3,1,5,2\}$。符合条件的好的三元组有以下 $3$ 个：
- $(1,2,3)$
- $(1,3,5)$
- $(2,5,8)$

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
8 3 1 5 2```

### 输出

```
3```

## 样例 #2

### 输入

```
7
300000 100000 499998 499999 200000 400000 500000```

### 输出

```
5```

## 样例 #3

### 输入

```
10
13 1 16 15 12 4 7 10 2 19```

### 输出

```
10```

# 题解

## 作者：冷却心 (赞：6)

你是一名信息学竞赛选手，你精通网络，这一天，你打开 AtCoder，却发现加载一个页面需要一分钟，于是你开始打 ABC。

> 给定 $n$ 个不同的正整数 $A_1,A_2,\cdots,A_n$。一个三元组 $(x,y,z)$ 是好的，当且仅当 $x<y<z$ 且 $y-x=z-y$。你可以任意选出三个数组成三元组，问有多少种方法能组成一个好的三元组。两种方法不同仅当你选择的数下标至少一个不同。
> 
> $n\leq 10^6,A_i\leq10^6$。

你开始瞪眼法。你注意力惊人，发现 $y-x=z-y$ 等价于 $2y=x+z$。于是你决定枚举 $y$ 统计合法的 $(x,z)$ 个数：

$$\text{Answer}=\sum_{i=1}^n\sum_{1\leq a<b\leq n}[A_a+A_b=2A_i].$$

于是你把这个放进有关值域 $V$ 的桶中，$c_i$ 表示等于 $i$ 的数个数：

$$\text{Answer}=\sum_{i=1}^V c_i\sum_{j=1}^{i-1} c_jc_{2i-j}.$$

你发现，后面这个求和像极了一个卷积。于是你使用了多项式，得到了数组 $C$：

$$C_i=\sum_{j=1}^{i-1}c_jc_{i-j}.$$

你发现对于一个合法的 $(x,y,z)$，$(x,y,z)$ 和 $(z,y,x)$ 在卷积中都被统计，同时 $(y,y,y)$ 也被统计，所以你去掉了重复和非法的方案。那么答案就是：

$$\text{Answer}=\sum_{i=1}^n\frac{C_{2A_i}-1}{2}.$$

你愉快地敲完了 FFT。交了一发。你的网速将你罚时一分钟，并在这一分钟之后成功提交了你的代码。通过了。你成功 AK 了 ABC392。

你愉快地打开榜单，却发现你打不开榜单，榜单保持在 Loading 状态。

赛后，你发现你在 AtCoder 打 ABC 时糟糕的网络状况。你关闭了它，然后成功打开榜单，却发现你是 rk 204，并且每题的罚时都比往常多五分钟，包含了开题的加载时间，提交的加载时间。

祝大家在打比赛的时候都有一个优良的网络环境。


```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;

namespace COMPLEX {
struct Complex {
	long double real, imag;
	Complex() { real = 0; imag = 0; return ; }
	Complex(long double a, long double b) { real = a, imag = b; return ; }
	const void operator = (const Complex& b) {
		real = b.real, imag = b.imag; return ;
	}
};
const Complex operator + (const Complex& a, const Complex& b) {
	return Complex(a.real + b.real, a.imag + b.imag);
}
const Complex operator - (const Complex& a, const Complex& b) {
	return Complex(a.real - b.real, a.imag - b.imag);
}
const Complex operator * (const Complex& a, const Complex& b) {
	return Complex(a.real * b.real - a.imag * b.imag, 
				   a.real * b.imag + a.imag * b.real);
}
const void operator += (Complex& a, const Complex& b) {
	a.real = a.real + b.real; a.imag = a.imag + b.imag; return ;
}
const void operator -= (Complex& a, const Complex& b) {
	a.real = a.real - b.real; a.imag = a.imag - b.imag; return ;
}
const void operator *= (Complex& a, const Complex& b) {
	a = Complex(a.real * b.real - a.imag * b.imag, 
				   a.real * b.imag + a.imag * b.real); return ;
}
} using namespace COMPLEX;

using comp = Complex;
const int N = 5e6 + 10;
int n, m; comp F[N], G[N];
namespace FFT {
const long double PI = acosl(-1);
void arrange(comp* F, int n) {
	for (int i = 0; i < n; i ++) {
		int x = 0;
		for (int j = 0; (1 << j) < n; j ++) 
			x = (x << 1) | ((i >> j) & 1);
		if (i > x) continue;
		swap(F[i], F[x]);
	} return ;
}
void DFT(comp* F, int n, int inv) {
	arrange(F, n); 
	for (int h = 2; h <= n; h <<= 1) {
		comp omega(cosl(2 * PI / h), sinl(inv * 2 * PI / h));
		for (int j = 0; j < n; j += h) {
			comp cur(1, 0);
			for (int k = j; k < j + h / 2; k ++) {
				comp a = F[k], b = F[k + h / 2] * cur;
				F[k] = a + b, F[k + h / 2] = a - b; cur *= omega;
			}
		}
	}
	if (inv == -1) {
		for (int i = 0; i < n; i ++) 
			F[i].real /= n, F[i].imag /= n;
	} return ;
}

} using FFT :: DFT;
using namespace FFT;
int trans(int x) {
	int t = 1;
	while (x) t <<= 1, x >>= 1;
	return t;
}
int A[N], cnt[N];
int main() {
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n; int m = 2e6 + 2;
	for (int i = 1; i <= n; i ++) { cin >> A[i]; cnt[A[i]] ++; }
	for (int i = 1; i <= m; i ++) F[i].real = F[i].imag = cnt[i];
	int len = 1; while (len < m) len <<= 1;
	DFT(F, len, 1);
	for (int i = 0; i < len; i ++) F[i] = F[i] * F[i];
	DFT(F, len, -1); LL Ans = 0;
	for (int i = 1; i <= n; i ++) Ans += (LL)(F[A[i] * 2].imag / 2 + 0.5) - 1;
	cout << Ans / 2 << "\n";
	return 0;
}
```

---

## 作者：SunburstFan (赞：3)

### G - Fine Triplets

**题目难度**：[clist 1773](https://clist.by/problems/?search=g&resource=93)

#### 大意

给定一个包含 $N$ 个不同正整数的集合 $S$。

如果三个整数 $A, B, C (A < B < C)$ 满足 $B - A = C - B$，则称 $(A, B, C)$ 为一个“好三元组”。

求集合 $S$ 中有多少个好三元组。

#### 做法

利用 FFT 加速卷积运算，快速统计。

使用 FFT 计算数组 $f$ 与自身的卷积，得到数组 $conv$。数组 $conv$ 的第 $i$ 个元素表示集合 $S$ 中有多少对数字 $(x, y)$ 满足 $x + y = i$。

遍历集合 $S$ 中的每个元素 $b$。

对于每个元素 $b$，计算 $2 \times b$ 的值。

如果 $2\times b$ 小于数组 $conv$ 的大小，则 $conv_{2\times b}$ 表示集合 $S$ 中有多少对数字 $(x, y)$ 满足 $x + y = 2\times b$。

由于 $x$ 和 $y$ 可以相同，因此需要减去 $1$（即 $x = y = b$ 的情况）。

由于 $(x, y)$ 和 $(y, x)$ 算作同一种情况，因此需要除以 $2$。

每次计算完之后将结果累加到 `ans` 中。

时间复杂度 $O(m \times \log m)$。

**核心代码**

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define db complex<double>
const double PI=acos(-1);

void FFT(vector<db>&a,bool invert){
    int n=a.size();

    for(int i=1,j=0;i<n;i++){
        int bit=n>>1;
        for(;j&bit;bit>>=1)j-=bit;
        j+=bit;
        if(i<j)swap(a[i],a[j]);
    }

    for(int len=2;len<=n;len<<=1){
        double ang=2*PI/len*(invert?-1:1);
        db wlen(cos(ang),sin(ang));

        for(int i=0;i<n;i+=len){
            db w=1;

            for(int j=0;j<len/2;j++){
                db u=a[i+j],v=a[i+j+len/2]*w;

                a[i+j]=u+v;
                a[i+j+len/2]=u-v;
                w*=wlen;
            }
        }
    }
    if(invert)for(db&x:a)x/=n;
}

vector<ll> calc(vector<int>&a,vector<int>&b){
    vector<db> fa(a.begin(),a.end()),fb(b.begin(),b.end());

    int n=1;
    while(n<(int)(a.size()+b.size()-1))n<<=1;

    fa.resize(n);fb.resize(n);

    FFT(fa,0);FFT(fb,0);
    for(int i=0;i<n;i++)fa[i]*=fb[i];
    FFT(fa,1);

    vector<ll> res(n);
    for(int i=0;i<n;i++)res[i]=(ll)round(fa[i].real());

    return res;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    
    int n;cin>>n;

    vector<int>s;
    s.reserve(n);

    for(int i=0;i<n;i++){
        int x;cin>>x;
        s.push_back(x);
    }
    
    int m=*max_element(s.begin(),s.end());

    vector<int>f(m+1,0);
    for(int x:s)f[x]=1;
    
    vector<ll>conv=calc(f,f);
    
    ll ans=0;
    for(int b:s){
        int idx=2*b;
        if(idx<conv.size())ans+=(conv[idx]-1)/2;
    }
    
    cout<<ans<<"\n";
    return 0;
}
```

---

## 作者：OneLeft (赞：2)

## 题意
给你一个大小为 $N$ 的集合 $S$，求满足 $A<B<C$ 且 $B-A=C-B$ 且 $A,B,C\in S$ 的三元组 $(A,B,C)$ 个数。
## 思路
设集合中某个数 $x$ 出现的次数为 $cnt_x$，考虑枚举 $B$ 和 $B-A$，则答案为：
$$
\sum_{i=1}^n\sum_{j=1}^{s_i}cnt_{s_i-j}cnt_{s_i+j}
$$
其中 $i=A$，$j=B-A$。

设 $f_x=\sum_{i=1}^xcnt_{x-i}cnt_{x+i}$，则原式可以转化为
$$
\sum_{i=1}^nf_{s_i}
$$
我们规定 $cnt_0=0$，然后考虑化简 $f_x$，有
$$
\begin{aligned}
f_x&=\sum_{i=1}^{x-1}cnt_icnt_{2x-i}\\
&=\left(\sum_{i=0}^xcnt_icnt_{2x-i}\right)-cnt_x^2\\
&=\frac{\sum_{i=0}^{2x}cnt_icnt_{2x-i}}{2}-cnt_x^2
\end{aligned}
$$
不难发现 $\sum_{i=0}^{2x}cnt_icnt_{2x-i}$ 是一个卷积的形式，带入原式得
$$
\left(\frac{1}{2}\sum_{i=1}^n\sum_{j=0}^{2a_i}cnt_jcnt_{2a_i-j}\right)-n
$$
因为任意一个在集合中出现的元素 $x$ 都有 $cnt_x=1$，故 $cnt_x^2=1$，所以最终算出来再统一减去 $n$ 即可。

设 $f(x)=\sum_{i=0}^{10^6}x^icnt_x$，$g(x)=\sum_{i=0}^{10^6}x^icnt_x$，计算出 $f*g$ 的系数再统计答案即可。这里使用NTT来达到 $O(n\log n)$ 的时间复杂度。
## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+5,mod=998244353,g=3;//998244353=(2^23)*7*17
int fpow(int n,int k=mod-2)//快速幂
{
    int res=1,base=n;
    for(;k>0;k>>=1)
    {
        if((k&1)==1)res=1ll*res*base%mod;
        base=1ll*base*base%mod;
    }
    return res;
}
const int invg=fpow(g);
int rev[N<<2];
void NTT(int*a,int len,bool inv) //NTT
{
    for(int i=0;i<len;i++)
        if(i<rev[i])swap(a[i],a[rev[i]]);
    for(int mid=1;mid<len;mid<<=1)
    {
        int wn=fpow(inv?invg:g,(mod-1)/(mid<<1));
        for(int i=0;i<len;i+=mid<<1)
        {
            int wk=1;
            for(int j=i;j<i+mid;j++,wk=1ll*wk*wn%mod)
            {
                int x=a[j],y=1ll*wk*a[j+mid]%mod;
                a[j]=(x+y)%mod,a[j+mid]=(x-y+mod)%mod;
            }
        }
    }
}
void times(int n,int m,int*a,int*b) //计算多项式相乘的系数
{
    int len=1,cnt=0;
    while(len<=n+m)len<<=1,cnt++;
    for(int i=1;i<len;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<cnt-1);
    NTT(a,len,false),NTT(b,len,false);
    for(int i=0;i<len;i++)a[i]=1ll*a[i]*b[i]%mod;
    NTT(a,len,true);
    for(int i=0;i<len;i++)a[i]=1ll*a[i]*fpow(len)%mod;
}
int a[N<<2],b[N<<2],x[N];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>x[i],a[x[i]]++,b[x[i]]++;
    times(1e6,1e6,a,b);
    ll ans=0;
    for(int i=1;i<=n;i++)ans+=a[2*x[i]]; //统计答案
    cout<<(ans-n)/2;
    return 0;
}
```

---

## 作者：CuFeO4 (赞：1)

打过最水的 G 题。

先变式子，变成 $A+C=2\times B$，发现这是一个卷积的形式，而且值域 $\le 10^6$，直接上 NTT 或者 FFT 即可。

假设卷积后的结果为 $F$，枚举 $s_i$，那么答案就是 $\frac{F_{2\times s_i}-1}{2}$，减 $1$ 是因为 $s_i+s_i=2\times s_i$，除以 $2$ 是因为顺序无关。

[AC Link](https://www.luogu.com.cn/record/203236657)。

---

## 作者：lovely_nst (赞：1)

# [ABC392G] Fine Triplets

## 前言

赛后才知道有官方库。

## 正文

题意就是问有多少三元组 $(i,j,k)$ 满足 $a_j-a_i=a_k-a_j(a_i<a_j<a_k)$。

移位后得 $a_i+a_k=2a_j$，将 $a_i$ 看成 $x^{a_i}$，因为 $x^ix^j=x^{i+j}$，于是就可以直接用[快速傅里叶变换（多项式乘法）](https://www.luogu.com.cn/problem/P3803)做。$2a_i$ 次项的系数为 $v$，那么 $\frac{v-1}{2}$ 就是 $B=a_i$ 时的方案数（因为 $a_i\ge a_j\ge a_k$ 的情况要剪掉），加起来即可。

提示：FFT 卷积在官方库中有。

## AC Code


```cpp
#include <atcoder/convolution>
#include <bits/stdc++.h>
#define int long long
using namespace std;
using namespace atcoder;
int a[1000005];
vector <int> s , c , s2;
signed main ()
{
	ios::sync_with_stdio (0) , cin.tie (0) , cout.tie (0);
	int n;
	cin >> n;
	s.resize (1e6 + 5); 
	for (int i = 1;i <= n;i ++)
		cin >> a[i] , s[a[i]] = 1;
	s2 = s;
	c = convolution (s2 , s2);
	int ans = 0;
	for (int i = 1;i <= n;i ++)
		ans += (c[a[i] << 1] - 1) >> 1;
	cout << ans;
	return 0;
}
```

---

## 作者：lilong (赞：0)

比较经典的生成函数题目。

不难发现题目中 $B-A=C-B$ 可以化为 $A+C=2B$。于是问题转化为：对于一个给定的数 $k$，在 $S$ 中选两个数使它们的和为 $k$（这个 $k$ 即是原来的 $2B$）。

接着读题可以发现，$S$ 是集合（即 $S_i$ 互异），$1 \le S_i \le 10^6$，也就是和不会超过 $2\times 10^6$。那么接下来就不难了，可以直接转化为生成函数了。把原来的元素视为 $x$ 的指数，得到一个多项式：

$$x^{S_1}+x^{S_2}+\cdots+x^{S_n}$$

将这个多项式平方，幂的乘法相当于指数的加法，所以平方后和为 $k$ 的方案数即为 $x^k$ 的系数。直接 FFT 优化即可。

需要注意最后统计总方案时需要去重，设当前系数为 $g$：

- $B+B=2B$，方案数减 $1$。

- 当 $A<C$ 时，$A+C=2B,C+A=2B$ 都被计算，故要将剩余方案除以 $2$。

综上，最终合法的方案数 $\dfrac{g-1}{2}$。

设 $S_i$ 的最大值为 $m$，则时间复杂度 $O(m\log m)$。


```cpp
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

const double PI = acos( -1.0 );

struct complex
{
	double x,y;
	complex ( double x0 = 0 , double y0 = 0 )
	{
		x = x0,y = y0;
	}
}a[4000001];

int n,Li,s[4000001],c[4000001];
long long ans;

complex operator +( complex x , complex y )
{
	return complex( x.x + y.x , x.y + y.y );
}

complex operator -( complex x , complex y )
{
	return complex( x.x - y.x , x.y - y.y );
}

complex operator *( complex x , complex y )
{
	return complex( x.x * y.x - x.y * y.y , x.x * y.y + x.y * y.x );
}

void FFT( complex *A , int flag )
{
	for( int i = 0 ; i < Li ; i ++ )
		if( i < c[i] )
			swap( A[i] , A[c[i]] );
	for( int mid = 1 ; mid < Li ; mid <<= 1 )
	{
		complex Wn;
		Wn.x = cos( PI / mid ),Wn.y = flag * sin( PI / mid );
		for( int j = 0 ; j < Li ; j += ( mid << 1 ) )
		{
			complex W;
			W.x = 1,W.y = 0;
			for( int k = 0 ; k < mid ; k ++ , W = W * Wn )
			{
				complex x = A[j + k],y = W * A[j + k + mid];
				A[j + k] = x + y;
				A[j + k + mid] = x - y;
			}
		}
	}
	return;
}

int main()
{
    cin >> n;
    for( int i = 1 ; i <= n ; i ++ )
        cin >> s[i],a[s[i]].x = 1;
    Li = 1 << 21;
    for( int i = 0 ; i < Li ; i ++ )
		c[i] = ( c[i >> 1] >> 1 ) | ( ( i & 1 ) << 20 );
    FFT( a , 1 );
    for( int i = 0 ; i < Li ; i ++ )
        a[i] = a[i] * a[i];
    FFT( a , -1 );
    for( int i = 0 ; i < Li ; i ++ )
        a[i].x = int( a[i].x / ( Li * 1.0 ) + 0.5 );
    for( int i = 1 ; i <= n ; i ++ )
        ans += ( a[s[i] * 2].x - 1 ) / 2;
    cout << ans;
    return 0;
}
```

---

## 作者：Walrus (赞：0)

rt，大概 21:25 开的比赛，看了 G 发现是 FFT 板子。

## Solution

比较一眼，先构造多项式 $f(x)=\sum\limits_{i=1}^n x^{S_i}$。

**注意这里的 $n=\max\limits_{1\leq i \leq N}S_i$，这里的 $N=\vert S \vert$**。

你发现把这个 $f(x)$ 平方后会得到

$$f^2(x)=\sum\limits_{i=1}^N\sum\limits_{j=1}^N x^{S_i+S_j}$$

然后你就会发现这个 $f^2(x)$ 的系数其实就是在求 $S_i+S_j=x$ 的方案数。

答案比较显然是（$p_u$ 是 $f^2(u)$ 的系数）

$$\sum\limits_{u\in S} \dfrac{p_{u\times 2}-1}{2} $$

为啥要减一呢？因为要排除 $B+B=B\times 2$ 这个愚蠢的情况，然后除二是因为 $A$ 和 $C$ 有相对位置关系不能交换。

然后用 FFT 求个多项式平方就可以了。

解释一下这个题为啥可以这么做，因为**值域是不存在负数和 $0$ 的**，这样的话根据多项式的运算法则， $f^2(x)$ 的系数一定是 $S_i+S_j=x$ 的方案数。

然后聪明的我因为混用了上述的 $n$ 和 $N$ 调了 20 min。

## 拓展

然后我记得有个题是有负数和 $0$ 的，那道题的做法是先给所有数单独加上一个大数然后再构造这样的多项式，但是因为有 $0$ 所以要单独算它的贡献。

题目大意是给定一个长度为 $n$ 的数列，让你求 $a_i+a_j=a_k$ 的数对 $(i,j,k)$ 的个数，值域 $-50000\leq a_i \leq 50000$，可以自行思考，其实跟这个题差不多。

---

## 作者：BLX32M_10 (赞：0)

## 题意

给你一个 $n$ 个数的集合 $S$，求集合中满足 $A<B<C$ 且 $B-A=C-B$ 的三元组 $\left(A,B,C\right)$ 数量。数据范围都是 $10^6$。

## 题解

先介绍一下卷积。对于两个离散序列 $f(n)$ 和 $g(n)$，我们定义它们的卷积 $f(n)*g(n)=\sum\limits_{m=-\infty}^{\infty}f(m)g(n-m)$，也可以理解为两个多项式相乘后的系数。

首先，我们变形一下式子得到 $A+C=2B$。而我们要算出集合中所有两数之和有些困难。

但是我们可以考虑开桶，这样的话桶和桶自己做卷积就能得到所有两数相加的桶了！

我们设卷积得到的桶为 $B$，这样一来，我们只需要遍历每一个数 $S_i$，然后将答案加上 $\frac{B_{S_i} - 1}2$。减一是因为 $S_i+S_i=2S_i$，不满足要求。除以二是因为每一个二元组都会交换计算两次。

至于卷积，可以使用 Atcoder 库自带的卷积，也可以手写  NTT。由于精度要求不高，也可以 FFT。

FFT：

```cpp
// LUOGU_RID: 203047108
#include <bits/stdc++.h>
#define int long long
using namespace std;
using comp = complex <double>;
const double pi = acos(-1);
int n, nbuc[(1 << 21) + 5];
int a[1000005];
comp buc[(1 << 21) + 5], tmp[(1 << 21) + 5];
inline void FFT(comp *a, int n, int rev)
{
    if (n == 1)
        return ;
    for (int i = 0; i < n; i++)
        tmp[i] = a[i];
    for (int i = 0; i < n; i++)
        a[(n >> 1) * (i & 1) + (i >> 1)] = tmp[i];
    comp *g = a, *h = a + (n >> 1);
    FFT(g, n >> 1, rev), FFT(h, n >> 1, rev);
    comp omega_n(1, 0), stp(cos(2 * pi / n), sin(2 * rev * pi / n));
    for (int i = 0; i < (n >> 1); i++)
    {
        tmp[i] = g[i] + omega_n * h[i];
        tmp[i + (n >> 1)] = g[i] - omega_n * h[i];
        omega_n *= stp;
    }
    for (int i = 0; i < n; i++)
        a[i] = tmp[i];
}
signed main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%lld", &x);
        a[i] = x;
        buc[x] = comp(1, 0);
    }
    FFT(buc, 1ll << 21, 1);
    for (int i = 0; i < (1ll << 21); i++)
        buc[i] = buc[i] * buc[i];
    FFT(buc, 1ll << 21, -1);
    for (int i = 0; i < (1ll << 21); i++)
    {
        nbuc[i] = buc[i].real() / (1ll << 21) + 0.01;
        // if (i < 20)
        //     printf("%lld:%lld\n", i, nbuc[i]);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        // printf("%lld\n", a[i]);
        ans += ((nbuc[a[i] * 2] - 1) >> 1);
    }
    printf("%lld", ans);
    return 0;
}
```

Atcoder 库卷积：

```cpp
#include <bits/stdc++.h>
#include <atcoder/convolution>
#define int long long
using namespace std;
using namespace atcoder;
int n;
vector <int> buc;
signed main()                                              
{
    buc.resize(1000005);
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%lld", &x);
        buc[x] = 1;
    }
    vector <int> prod = convolution(buc, buc);
    int res = 0;
    for (int i = 1; i <= 1000000; i++)
        if (buc[i])
            res += (prod[i << 1] - 1) >> 1;
    printf("%lld", res);
    return 0;
}
```

---

