# [ABC293E] Geometric Progression

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc293/tasks/abc293_e

整数 $ A,\ X,\ M $ が与えられます。$ \displaystyle\ \sum_{i\ =\ 0}^{X-1}\ A^i $ を $ M $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ A,\ M\ \leq\ 10^9 $
- $ 1\ \leq\ X\ \leq\ 10^{12} $
- 入力はすべて整数

### Sample Explanation 1

$ 3^0\ +\ 3^1\ +\ 3^2\ +\ 3^3\ =\ 40 $ です。$ 40 $ を $ 7 $ で割った余りは $ 5 $ であるため、$ 5 $ を出力します。

## 样例 #1

### 输入

```
3 4 7```

### 输出

```
5```

## 样例 #2

### 输入

```
8 10 9```

### 输出

```
0```

## 样例 #3

### 输入

```
1000000000 1000000000000 998244353```

### 输出

```
919667211```

# 题解

## 作者：zajasi (赞：12)

## 题意
给定 $a,x,m$，求出 $ \displaystyle\ \sum_{i\ =\ 0}^{x-1}\ a^i \bmod m$ 的值。
## 解题思路 1
用小学奥数学过的方法——等比数列求值。

令 $S=a^0+a^1+a^2+\cdots+a^{x-1}$。

则 $a\times S=a^1+a^2+a^3+\cdots+a^x$。

等式 $2$ 减等式 $1$ 得，$(a-1)\times S=a^x-1$。

则 $S=\frac{a^x-1}{a-1}$。

也就是快速幂和乘法逆元了。
## AC 代码 1
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef __int128 LL;
typedef long long ll;
ll a,x,m;
LL p;
LL qpow(LL x,LL y)
	LL re=1;
	for(;y>0;y>>=1){
		if(y&1)re=re*x%p;
		x=x*x%p;
	}
	return !re?p:re;
}
int main(){
    cin>>a>>x>>m;
    if(a==1){
        cout<<x%m;
        return 0;
    }
    p=m*(a-1);
    cout<<(ll)(qpow(a,x)-1)/(a-1);
    return 0;
}
```
## 解题思路 2
但要是像本蒟蒻一样，不会乘法逆元怎么办呢？用递归！

定义 $S(n)=a^0+a^1+\cdots+a^n$，分类讨论：

![](https://cdn.luogu.com.cn/upload/image_hosting/taegs5qt.png)

然后边界条件：当 $n=0$ 时，$S=a^0=1$；当 $n=1$ 时，$S=a^1+a^0=(a+1)\bmod m$。

也需要快速幂，但不用乘法逆元。适用于像我这样不会乘法逆元的蒟蒻。
## AC 代码 2
```cpp
/*
written by : zjs123
*/
#include<bits/stdc++.h>
using namespace std;
#define int __int128
inline int read(){
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int a,x,m;
int ksm(int a,int b,int c){
    int re=1;
    while(b){
        if(b&1)re=re*a%c;
        a=a*a%c;
        b/=2;
    }
    return re;
}
int S(int x){
    if(x==0)return 1;
    if(x==1)return (a+1)%m;
    if(x&1){
        return (1+ksm(a,x/2+1,m))*S(x/2)%m;
    }
    else{
        return ((1+ksm(a,x/2,m))*S(x/2-1)%m+ksm(a,x,m))%m;
    }
}
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    a=read();
    x=read();
    m=read();
    write(S(x-1)%m);
    return 0;
}

```
## 修改
2023.9.24 一张图炸了，修好了。

---

## 作者：FFTotoro (赞：6)

本题可以使用**分治**思想。

令 $S_n$ 为 $\sum\limits_{i=1}^n A^i$，则我们可以分类讨论：

1. 当 $n$ 为偶数时，

$$
\begin{aligned}
S_n
&=\sum_{i=1}^n A^i\\
&=\sum_{i=1}^{n/2} A^i+A^{n/2}\sum_{i=1}^{n/2} A^i\\
&=\left(\sum_{i=1}^{n/2}A^i\right)\left(A^{n/2}+1\right)\\
&=S_{n/2}\left(A^{n/2}+1\right)
\end{aligned}
$$

2. 当 $n$ 为奇数时，

$$
\begin{aligned}
S_n
&=\sum_{i=1}^n A^i\\
&=\sum_{i=1}^{n-1} A^i+A^n\\
&=S_{(n-1)/2}\left(A^{(n-1)/2}+1\right)+A^n
\end{aligned}
$$

上述二式可以递归求解，答案最后加上 $A^0=1$ 即可。

注意 $x=1$ 和 $m=1$ 的情况，需要特判。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int m;
int qpow(int a,int b){
  int r=1;
  while(b){
    if(b&1)r=r%m*a%m;
    a=a%m*a%m; b>>=1;
  }
  return r;
} // 快速幂
int f(int a,int x){
  if(!x)return 0; // x=1 时如果不加这行会 RE
  if(x==1)return a%m;
  if(x&1)return (f(a,x>>1)*(qpow(a,x>>1)+1)%m+qpow(a,x))%m;
  else return f(a,x>>1)*(qpow(a,x>>1)+1)%m;
  // 套公式
} // f(a,x) 表示解法描述中的 S[x]
main(){
  ios::sync_with_stdio(false);
  int a,x; cin>>a>>x>>m;
  cout<<(f(a,x-1)+1)%m<<endl;
  return 0;
}
```

---

## 作者：快乐的大童 (赞：5)

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc293_e)

[Atcoder 传送门](https://atcoder.jp/contests/abc293/tasks/abc293_e)
### 题目大意
求 $\sum^{X-1}_{i=0} A^i\bmod M$ 的值。

不保证 $M$ 是质数。
### 思路
首先，根据初中数学老师教给我们的知识，我们应该使用错位相减法（~~是叫这个名吧？~~）：

令 $S=\sum^{X-1}_{i=0} A^i$。

我们将等式两边同乘 $A$，可以得到 $AS=\sum^{X}_{i=1} A^i$。

两式相减，得 $(A-1)S=A^X-A^0$。

将 $A-1$ 除过去得 $S=\dfrac{A^X-1}{A-1}$。

>当然将 $A-1$ 除过去有一个重要前提：$A-1\not=0$，即 $A\not=1$。**但题目没有保证，所以我们要特判这种情况，输出 $X\bmod M$。**

然后我们发现 $M$ 不一定有逆元，于是我们没法直接解决它。

------------

这时我们引入一个公式：

>若 $b|a$，则 $\dfrac{a}{b}\bmod m=\dfrac{a \bmod (m\cdot b)}{b}$

根据这个，我们只需要输出 $\dfrac{(A^X-1)\bmod (M\times(A-1))}{A-1}$ 的值。

注意要开 `__int128`。

**UPD：计算快速幂时要特判整除的情况，因为此时可能会计算出负数，具体见代码（官方赛后加的数据点）。**
### 代码
```cpp
#include<bits/stdc++.h>
#define int __int128 
using namespace std;
inline int R(){
	int x=0,f=1;int ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}return x*f;
}
inline void write(int x){
	if(x<0){x=-x;putchar('-');}
	int y=0;char z[70];
	while(x||!y){z[y++]=x%10+48;x/=10;}
	while(y--)putchar(z[y]);
}
int a,x,m,mod;
int ksm(int x,int y){
	int res=1;
	while(y){
		if(y&1) res=(res*x)%mod;
		x=(x*x)%mod;
		y>>=1;
	}
	return !res?mod:res;//快速幂特判整除
}
signed main(){
	a=R(),x=R(),m=R();
	if(a==1) return write(x%m),0;//特判A=1
	mod=m*(a-1);
	write((ksm(a,x)-1)/(a-1));
}
```


---

## 作者：spider_oyster (赞：4)

一眼丁真：等比公式 + 快速幂 + 逆元，然而不互质。

有大佬用了逆元，然而我不是。

于是我考虑矩阵乘法，还是很好推的。设 $f_{i}$ 为第 $i$ 项的答案，则有 $f_{i}=f_{i-1}\times a +1 \times 1$，然后我们随便凑一个 $1=f_{i-1}\times 0+1\times 1$。

于是 $\begin{pmatrix} f_{i}\\1 \end{pmatrix}=\begin{pmatrix} a &1 \\ 0  & 1\end{pmatrix} \times \begin{pmatrix}f_{i-1}\\1 \end{pmatrix}$。

$\begin{pmatrix} f_{x}\\1 \end{pmatrix}=\begin{pmatrix} a &1 \\ 0  & 1\end{pmatrix} ^x \times \begin{pmatrix}f_{0}\\1 \end{pmatrix}$。

然后初始 $f_{0}=0$。

如果您用了结构体，请一定初始化，不然像我这啥一样赛场卡半天（主要还是太久没写矩乘了）。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n,k,p;

struct node{
	ll a[4][4];
	node(){memset(a,0,sizeof(a));}//不初始化卡半天的滋味请谨慎品尝 
	node operator*(const node &b)const{
		node c;
		for(int i=1;i<=2;i++)
			for(int j=1;j<=2;j++)
				for(int k=1;k<=2;k++)
					c.a[i][j]=(c.a[i][j]+a[i][k]*b.a[k][j]%p)%p;
		return c;
	}
}x,res;

void power(node x,ll b)
{
	res.a[1][1]=res.a[2][2]=1;
	while(b)
	{
		if(b&1) res=res*x;
		x=x*x;
		b>>=1;
	}
}

int main()
{
	cin>>n>>k>>p;
	x.a[1][1]=n,x.a[1][2]=1;
	x.a[2][1]=0,x.a[2][2]=1;
	power(x,k);
	cout<<res.a[1][2];//矩阵res*(0 1)，res[1][1]无了，输出res[1][2]即可。 
	return 0;
}
```


---

## 作者：sunzz3183 (赞：3)

# [ABC293E] Geometric Progression 题解

## 题意

给定 $a,n,m$，求

$$ \sum\limits_{i=1}^{n-1}a^i\bmod{m} $$

## 分析

我们每次运用乘法分配律，每次提取公因式，下面以 $n=5$ 来举例

$$
\begin{aligned}
\\&1+a^1+a^2+a^3+a^4
\\&=1+a(1+a^1+a^2+a^3)
\\&=1+a(1+a(1+a^1+a^2))
\\&=1+a(1+a(1+a(1+a)))
\end{aligned}
$$

显然，就是做 $n-1$ 次 $\times a+1$。

但是,$1\leq n\leq 10^{12}$，会 TLE。

我们考虑：

把 $f_0=1$，

则 $f_i=f_{i-1}\times a+1$，

所以答案为 $f_{n-1}$。

而第二个式子可以用矩阵快速幂来求，所以时间为 $O(\log{n})$，可过。

矩阵为：

$$

\begin{bmatrix}
1,1
\end{bmatrix}\times
\begin{bmatrix}
a,0
\\1,1
\end{bmatrix}^{n-1}

$$

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||'9'<c){if(c=='-')f=-1;c=getchar();}
	while('0'<=c&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
const int N=3;
int x,n,mod;
struct qwq{
	int n,m,num[N][N];
}ans,a;
void print(qwq x){
	for(int i=1;i<=x.n;puts(""),i++)
		for(int j=1;j<=x.m;j++)
			printf("%lld ",x.num[i][j]);
	return;
}
qwq operator*(const qwq &x,const qwq &y){
	qwq c;c.n=x.n;c.m=y.m;
	for(int i=1;i<=c.n;i++)
		for(int j=1;j<=c.m;j++)
			c.num[i][j]=0;
	for(int i=1;i<=x.n;i++)
		for(int j=1;j<=y.m;j++)
			for(int k=1;k<=x.m;k++) 
				(c.num[i][j]+=x.num[i][k]*y.num[k][j]%mod)%=mod;
	return c;
}
qwq ksm(qwq a,int b){
	qwq t;t.n=t.m=2;
	t.num[1][1]=t.num[2][2]=1;
	t.num[1][2]=t.num[2][1]=0;
	for(;b;b>>=1,a=a*a)if(b&1)t=t*a;
	return t;
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	x=read();n=read()-1;mod=read();
	ans.n=1,ans.m=2;
	ans.num[1][1]=ans.num[1][2]=1;
	a.n=a.m=2;
	a.num[1][1]=x;a.num[2][1]=a.num[2][2]=1;
	a.num[1][2]=0;
	qwq t=ksm(a,n);
	ans=ans*t;
	printf("%lld\n",ans.num[1][1]);
	return 0;
}

```


---

## 作者：Arghariza (赞：3)

不太会乘法逆元……不过我们可以分块。

每 $b=\sqrt{X-1}+1$ 分一块（加一是为了避免出现 $0$ 的情况），两个块之间和的转移直接乘 $A^b$ 即可。

如果有最后剩下的散块，直接暴力快速幂计算即可。复杂度 $O(\sqrt X\log X)$。

```cpp
int a, x, mod; 

int qpow(int p, int q) {
	int res = 1;
	while (q) {
		if (q & 1) res = res * p % mod;
		p = p * p % mod, q >>= 1;
	}
	return res;
}

signed main() {
	a = read(), x = read() - 1, mod = read();
	int b = sqrt(x) + 1, res = 0, ans = 0;
	for (int i = 1; i <= b; i++) (res += qpow(a, i)) %= mod;
	for (int i = 1, tp = 1; i <= x / b; i++) {
		ans = (ans + res * tp % mod) % mod;
		tp = tp * qpow(a, b) % mod;
	}
	for (int i = x / b * b + 1; i <= x; i++) {
		ans = (ans + qpow(a, i)) % mod;
	}
	write((ans + 1) % mod);
	return 0;
}

```

---

## 作者：incra (赞：3)

### 题意
给定 $A,X,M$，求 $(\sum\limits_{i=0}^{X-1}A^i)\bmod M$。

- $A,M\le 10^9$
- $M\le 10^{12}$

### 题解
由于看到 $X$ 很大，又和 $A^i$ 有关，所以很自然的就会想到快速幂。

考虑把 $X$ 二进制分解，如果 $X$ 的二进制表示从右往左数第 $i$ 位是 $1$，那么答案 $ans$ 就要变为 $ans\times a^{2^i}+1+a+\cdots+a^{2^i-1}$ 。而 $a^{2^i}$ 和 $1+a+\cdots+a^{2^i-1}$ 可以在类快速幂算法中进行计算。
### 代码
```cpp
#include <iostream>
using namespace std;
typedef long long LL;
LL a,x,m;
LL get_ans (LL a,LL b,LL m) {
	LL ans = 0,aa = a,bb = 1;
	while (b) {
		if (b & 1) ans = (ans * aa + bb) % m;
		bb = (bb * aa + bb) % m,aa = aa * aa % m;
		b >>= 1;
	}
	return ans;
}
int main () {
	cin >> a >> x >> m;
	cout << get_ans (a,x,m) << endl;
    return 0;
}
```

---

## 作者：六楼溜刘 (赞：2)

# 核心思路：递推
适合数学不好的选手参考

## 题意

- 给你三个正整数 $A,X,M$ 你要求 $\sum\limits_{i=0}^{X-1}A^i \bmod m$。
- $1 \leq A,m \leq10^9, 1 \leq X \leq 10^{12}$

## 题解

这道题明显可以用等比数列求和公式，但是我不会这个公式（属于是小学奥数没学好的伏笔了）所以我们考虑用算法求解。

由于这道题 $X$ 非常大，$O(n)$ 都不可能过，所以我们考虑复杂度小于 $O(n)$ 的方法，很自然地会想到对数型递推。

令 $f(p)=\sum\limits_{i=0}^{p}A^i$，容易发现以下性质：

$$p=0,f(p)=1$$
$$\forall p > 0,f(p)=f(p-1) \times A + 1$$
$$\forall p \equiv 1 \pmod 2,f(p)=f(\frac{p}{2}) \times (A^{\frac{p}{2}+1}+1)$$

证明：
- 对于性质 $1$，

	$f(0)= \sum\limits_{i=0}^{0}A^i =A^0 =1$。
    
- 对于性质 $2$，

	$f(p)$
    
   $= \sum\limits_{i=0}^{p}A^i $
   
   $= A^0 + \sum\limits_{i=1}^{p}A^i $
   
   $= 1 + A\times\sum\limits_{i=0}^{p-1}A^i $
   
   $=f(p-1) \times A +1$
    
- 对于性质 $3$，

	$f(p)$
    
   $= \sum\limits_{i=0}^{p}A^i$
   
   $ = \sum\limits_{i=0}^{\frac{p}{2}}A^i + \sum\limits_{i=\frac{p}{2}+1}^{p}A^i $
   
   $=\sum\limits_{i=0}^{\frac{p}{2}}A^i +A^{\frac{p}{2}+1} \times \sum\limits_{i=0}^{\frac{p}{2}}A^i$
   
   $=f(\frac{p}{2})+A^{\frac{p}{2}+1} \times f(\frac{p}{2})$
   
   $=f(\frac{p}{2}) \times (A^{\frac{p}{2}+1}+1)$
   
那么我们就可以用这个性质来分治，由于快速幂的复杂度是 $O(\log n)$ 每一层至多算一次快速幂，且层数是 $O(\log n)$ 级别的，故整体复杂度为 $O(\log^2 n)$。

## code
```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
#define gc getchar()
inline int read(){//快读
    int x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
int a,x,m;
inline int ksm(int x,int k){//快速幂
	int res=1;
	while(k>0){
		if(k&1) res=(res*x)%m;
		x=(x*x)%m;
		k>>=1;
	}
	return res;
}
inline int sum(int p){
//需要注意，所有的表达式后面都要模 m，还要当心会不会爆 long long。
	if(p==0) return 1%m;
	if(!(p&1)){
		return (sum(p-1)*a%m+1)%m;
	}else{
		return (sum(p/2)%m*(ksm(a,p/2+1)+1)%m)%m;
	}
}
signed main(){
	a=read();x=read();m=read();
	printf("%lld",sum(x-1));
}
```

---

## 作者：LJ07 (赞：1)

给出显然的单 log 想法。

$1+A+\cdots+A^{l-1}=\frac{A^l-1}{A-1}$

容易发现在 $l=2^{p}$ 时通过平方差 $A-1$ 被约去。

$1+A+\cdots+A^{2^{p}-1}=(A+1)(A^{2}+1)\cdots(A^{2^{p-1}}+1)$

然后就将 $x$ 二进制拆分，时间复杂度 $O(\log X)$

然而并没打 ABC，也没有想到根号/ll

```cpp
Rd(a, x, P), a %= P;
pw[0] = a;
for (int i(1); i <= T; ++i) pw[i] = 1ll * pw[i - 1] * pw[i - 1] % P;
f[0] = (a + 1) % P;
for (int i(1); i <= T; ++i) f[i] = 1ll * f[i - 1] * (pw[i] + 1) % P;
for (int i(T), base(1); ~i; --i) if (x >> i & 1) {
  ans = (ans + 1ll * base * (i ? f[i - 1] : 1) % P) % P;
  base = 1ll * base * pw[i] % P;
}
printf("%d", ans);
```

---

## 作者：FyFive (赞：1)

>做法来自 @寻逍遥2006

#### 题意

求 $\displaystyle \sum_{i=0}^{X-1}A^{i} \operatorname{mod} M$，不保证 $M$ 为质数。

#### 做法

维护一个 $f_i(K)= \sum\limits_{i=0}^{2^K-1}A^i$，

那么可得 $f_i(K)=f_{i-1}(K) \times (A^{2^{K-1}}+1)$。

这样一来，就可以直接对 $X$ 进行二进制拆分，维护答案即可。

#### 核心代码

```cpp
while(x)
{
    f[k]=f[k-1]*(qpow(a,aqpow(2,k-1))+1)%mo;
    x>>=1;++k;
}
for(int i=mxs;i>=0;--i)
{
    if(xs[i])
    {
        ans+=f[i]*qpow(a,ard)%mo;
        ars+=aqpow(2,i);
        ans%=mo;
    }
}
```

---

## 作者：ForgotDream_CHN (赞：1)

# ATABC293E Geometric Progression

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17208266.html)

感觉自己写了一个神秘做法。

### 题意

给你三个整数 $A$，$M$ 与 $X$，求：

$$
\sum_{i = 0}^{X - 1} A^i
$$

对 $M$ 取模后的值。

$1 \le A, m \le 10^9$，$1 \le X \le 10^{12}$。

### 思路

考场上第一眼看这个题想到的是用这个式子：

$$
\sum_{i = 0}^{X - 1} A^i = \frac{A^{X} - 1}{A - 1}
$$

然后除法用逆元做一下。结果忽略了一个很重要的事实，就是题目没有保证 $A - 1$ 与 $M$ 互质，连续 WA 了 3 次才发觉不对劲。

这道题的官方题解是矩阵快速幂？我偏不用~~其实是不会~~！

下面是我做这道题的思路。

由于我们有 $\sqrt{10^{12}} = 10^6$，所以我们可以从这方面找找思路（谁会这么想啊喂），考虑将原式分成 $\sqrt{X}$ 块后再做前缀和，设 $B = \lfloor\sqrt{X}\rfloor$，记第一块的值为 $sum$，有：

$$
sum= \sum_{i = 0}^{B - 1} A^i
$$

然后通过一个小小的递推得到每一块的值。具体地，有第 $i$ 块的值为 $sum \times A^{(i - 1)B}$。最后剩一个散块暴力累加一下就好了。

那么最终的答案就为：

$$
ans = \sum_{i = 1}^{B} sum \times A^{(i - 1)B} + \sum_{i = B^2}^{X - 1} A^i
$$


由于我太傻了，是直接在循环中用快速幂计算幂次的，所以我的时间复杂度为 $O(\sqrt{X}\log{X})$ 级别的，但事实上我们可以预处理出 $\sqrt{X}$ 内的 $A$ 的幂次，这样时间复杂度为 $O(\sqrt{X})$。虽然不如其他的神仙做法，不过已经足够好了。

### 代码

代码其实非常好写，毕竟是优雅的暴力。

我在一些奇怪的地方用了 `__int128`，不过事实上完全不用，只是我赛时发癫。

```cpp
#include <bits/stdc++.h>

using i64 = long long;
using i128 = __int128;

i64 fastPow(i64 base, i64 pow, i64 mod) {
  i64 res = 1;
  while (pow) {
    if (pow & 1) {
      (res *= base) %= mod;
    }
    (base *= base) %= mod;
    pow >>= 1;
  }
  return res;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  i64 a, m, x;
  std::cin >> a >> x >> m;

  i64 powNum = 0;
  int block = std::sqrt(x);
  for (int i = 0; i < block; i++) {
    (powNum += fastPow(a, i, m)) %= m;
  }

  i64 ans = 0;
  for (int i = 1; i <= block; i++) {
    (ans += fastPow(a, ((i64) (i - 1) * block), m) * i128(powNum)) %= m;
  }

  if ((i64) block * block != x) {
    for (i64 i = (i64) block * block; i < x; i++) {
      (ans += fastPow(a, i, m)) %= m;
    }
  }

  std::cout << ans << "\n";

  return 0;
}
```


---

## 作者：Neil_Qian (赞：1)

# [ABC293E] Geometric Progression 题解

## 题目描述

给定 $a,x,m$，求 $\sum_{i=0}^{x-1}a^i$ 对 $m$ 取模的值。注意没有保证 $m$ 为质数。

## 解决方案

数学题。

如果 $m$ 为质数，那么全国人民都会做，一个逆元即可。

然而，这里并没有保证，所以我们得在想个办法。

### 快速幂

这个工具简单说一下，$a^x=(a^{x/2})^2\times (a)[x\mod2=1]$。

### 分块

我们将所求分成长度为 $len=\sqrt x$ 块，并且有 $num$ 个整块。对于每一个整块，可以很快求出它们的左右端点，记为 $l,r$，则这一块的答案为 $a^l+a^{l+1}+\dots+a^r$，提取 $a^l$ 得 $a^l\times(a^0+a^1+\dots+a^{r-l=len-1})$。每一块的后半部分都一样，可预处理，时间复杂度 $O(\sqrt x\times\log(x))$，可以接受。每一块要再算一遍 $a^l$，时间复杂度 $O(\sqrt x\times\log(x))$，可以接受。最后剩的一小块暴力计算每一项即可，时间复杂度 $O(\sqrt x\times\log(x))$，可以接受。综上，时间复杂度 $O(\sqrt x\times\log(x))$，可以通过。本题得解。

### 代码

其实根据上述解法很好实现。

```cpp
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
ll a,x,MOD,len,num,per,res,l,r,ans,i;
inline ll qpow(ll x,ll y){//快速幂，数论必备
	res=1;
	while(y){
		if(y&1)(res*=x)%=MOD;
		(x*=x)%=MOD,y>>=1;
	}
	return res;
}
int main(){
	scanf("%lld%lld%lld",&a,&x,&MOD),len=sqrt(x),num=x/len;
	for(i=0;i<len;i++)(per+=qpow(a,i))%=MOD;//计算后半部分
	for(i=1;i<=num;i++)
		l=(i-1)*len,r=i*len-1,(ans+=qpow(a,l)*per)%=MOD;//计算每一块
	if(x%len)for(i=r+1;i<x;i++)(ans+=qpow(a,i))%=MOD;//最后剩下的
	return printf("%lld\n",ans),0;
}
```

---

## 作者：rui_er (赞：1)

由于模数不一定是大质数，我们不能直接套等比数列求和公式。

换一种思路，数列 $\langle1,A,A^2,\cdots,A^{X-1}\rangle$ 可以看做线性递推，因此设计矩阵：

$$
\boldsymbol T=
\begin{bmatrix}
A & 0 \\
1 & 1 \\
\end{bmatrix}
$$

显然有：

$$
\begin{bmatrix}
A^i \\
S_{i-1} \\
\end{bmatrix}
\boldsymbol T
=
\begin{bmatrix}
A^{i+1}\\
S_i \\
\end{bmatrix}
$$

因此 $\boldsymbol T^X$ 的左下角元素即为答案。

时间复杂度 $\mathcal O(\log X)$。

```cpp
// Problem: E - Geometric Progression
// Contest: AtCoder - AtCoder Beginner Contest 293
// URL: https://atcoder.jp/contests/abc293/tasks/abc293_e
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
#define likely(exp) __builtin_expect(!!(exp), 1)
#define unlikely(exp) __builtin_expect(!!(exp), 0)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
ll randint(ll L, ll R) {
	uniform_int_distribution<ll> dist(L, R);
	return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

ll a, x, m;

struct Matrix {
	ll a[2][2];
	Matrix() {memset(a, 0, sizeof(a));}
	friend Matrix operator*(const Matrix& a, const Matrix& b) {
		Matrix c;
		rep(i, 0, 1) rep(j, 0, 1) rep(k, 0, 1) (c.a[i][j] += a.a[i][k] * b.a[k][j] % m) %= m;
		return c;
	}
	friend Matrix operator^(Matrix a, ll k) {
		Matrix c;
		c.a[0][0] = c.a[1][1] = 1;
		for(; k; k >>= 1, a = a * a) if(k & 1) c = c * a;
		return c;
	}
}mat;

/*
u * a 0 = a*u
s   1 1   s+u
*/

int main() {
	scanf("%lld%lld%lld", &a, &x, &m);
	mat.a[0][0] = a % m;
	mat.a[1][0] = mat.a[1][1] = 1;
	mat = mat ^ x;
	printf("%lld\n", mat.a[1][0]);
	return 0;
}
```

---

## 作者：chengning0909 (赞：0)

# abc 293 E

[题目传送门（洛谷）](https://www.luogu.com.cn/problem/AT_abc293_e)

[题目传送门（AtCoder）](https://atcoder.jp/contests/abc293/tasks/abc293_e)

## 题意

给定 $A, X, M$，请你求出 $\sum \limits _{i = 0} ^ {X - 1} A ^ i \mod m$。

$1 \le X \le 10 ^ {12}, 1 \le A, M \le 10 ^ 9$

## 思路

首先，这题有一个很明显的暴力：枚举所有的 $i$，将所有 $A ^ i$ 累加起来。

但是这样的话，时间复杂度为 $O(X)$，妥妥的超时。

所以我们可以考虑一种递归分治的做法。

令 $S(n) = A ^ 1 + A ^ 2 + \dots A ^ n$。

- 若 $n$ 为偶数：

$S(n) = S(n / 2) + A ^ {n / 2 + 1} + \dots A ^ n$

$ = S(n / 2) + (A ^ 1 \times A ^ {n / 2}) + \dots + (A ^ {n / 2} \times A ^ {n / 2})$

$ = S(n / 2) + (A ^ 1 + A ^ 2 + \dots A ^ {n / 2}) \times A ^ {n / 2}$

$ = S(n / 2) + S(n / 2) \times A ^ {n / 2}$

实际上，$n$ 为奇数的情况与偶数并没有什么不同，只是要在求和的时候多加上一个 $A ^ n$ 而已。

- 若 $n$ 为奇数：

$S(n) = S(\lfloor n / 2 \rfloor) + A ^ {\lfloor n / 2 \rfloor + 1} + \dots A ^ n$

$ = S(\lfloor n / 2 \rfloor) + (A ^ 1 \times A ^ {\lfloor n / 2 \rfloor}) + \dots + (A ^ {\lfloor n / 2 \rfloor} \times A ^ {\lfloor n / 2 \rfloor}) + A ^ n$

$ = S(\lfloor n / 2 \rfloor) + (A ^ 1 + A ^ 2 + \dots A ^ {\lfloor n / 2 \rfloor}) \times A ^ {\lfloor n / 2 \rfloor} + A ^ n$

$ = S(\lfloor n / 2 \rfloor) + S(\lfloor n / 2 \rfloor) \times A ^ {\lfloor n / 2 \rfloor} + A ^ n$

由于这里我定义的是 $S(n) = A ^ 1 + \dots + A ^ n$，所以要将 $A ^ 0$ 再最后单独计算一下。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int a, m;
long long w;

struct Node {
  long long x, y; 
};

Node P(long long t) {
  if (t <= 1) {
    /*
    这里有一个问题，之所以要写成 t <= 1，是因为 w 有可能为 1
    若 w = 1，那么传进来的 t 就会是 0，如果只判断 t == 1，会无限递归，RE
    */
    return {t * a % m, t * a % m};
  }
  Node x = P(t / 2);
  long long p = x.x * x.x % m;
  // x.x 为 A ^ (t / 2)，x.y 为 A ^ 1 + ... + A ^ (t / 2)
  x.y = (x.y + x.y * x.x % m) % m;  // 求和
  if (t % 2 == 1) {  // 若 n 为奇数 
    p = p * a % m, x.y = (x.y + p) % m;
  }
  x.x = p;
  return x;
}

int main() {
  cin >> a >> w >> m;
  // P(w - 1) 求 A ^ 1 + ... + A ^ (w - 1)
  cout << (P(w - 1).y + 1) % m;
  return 0;
}
```

---

## 作者：__vector__ (赞：0)

说一个很简单的分治做法。  
先把式子写下来：  
$A^0 + A^1 + A^2 + A^3 + \cdots + A^{X-1}$  
如果将式子的前 $\lfloor \frac{X}{2} \rfloor$ 项与后面的项分开，可以发现，前半部分计算出来后可以快速计算得到后半部分。  

设前半部分 $res_1 = A^0 + A^1 + A^2 + \cdots + A^{\lfloor \frac{x}{2} \rfloor -1}$。  

假设 $X$ 是偶数，那么后半部分即 $A^{\lfloor \frac{X}{2}\rfloor} + \cdots + A^{X-1} = A^{\lfloor \frac{X}{2}\rfloor} \cdot res_1$。  

若 $X$ 是奇数，那就先按 $X$ 是偶数的式子计算，最后在原来的答案的基础上加上 $A^{X-1}$ 即可。  

现在就找出了已知前半部分，$O(1)$ 得知后半部分的方法。  

分治即可。  

[Atcoder 提交记录](https://atcoder.jp/contests/abc293/submissions/39636293)

---

