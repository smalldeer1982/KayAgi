# Similar Polynomials

## 题目描述

A polynomial $A(x)$ of degree $d$ is an expression of the form $A(x) = a_0 + a_1 x + a_2 x^2 + \dots + a_d x^d$, where $a_i$ are integers, and $a_d \neq 0$. Two polynomials $A(x)$ and $B(x)$ are called similar if there is an integer $s$ such that for any integer $x$ it holds that

$$
B(x) \equiv A(x+s) \pmod{10^9+7}.
$$

For two similar polynomials $A(x)$ and $B(x)$ of degree $d$, you're given their values in the points $x=0,1,\dots, d$ modulo $10^9+7$.

Find a value $s$ such that $B(x) \equiv A(x+s) \pmod{10^9+7}$ for all integers $x$.

## 说明/提示

**Note**

In the first example, $A(x) \equiv x-1 \pmod{10^9+7}$ and $B(x)\equiv x+2 \pmod{10^9+7}$. They're similar because

$$
B(x) \equiv A(x+3) \pmod{10^9+7}.
$$

In the second example, $A(x) \equiv (x+1)^2 \pmod{10^9+7}$ and $B(x) \equiv (x+10)^2 \pmod{10^9+7}$, hence

$$
B(x) \equiv A(x+9) \pmod{10^9+7}.
$$

## 样例 #1

### 输入

```
1
1000000006 0
2 3```

### 输出

```
3```

## 样例 #2

### 输入

```
2
1 4 9
100 121 144```

### 输出

```
9```

# 题解

## 作者：Fido_Puppy (赞：11)

## 题目链接

[CF1817C Similar Polynomials](https://codeforces.com/problemset/problem/1817/C)

## 题解

这里给出一个比较寻的做法。

我们考虑已知 $d$ 次多项式的 $d + 1$ 个点值，我们就可以将这个多项式插值出来，但是直接做是 $\Theta(d \log ^ 2 d)$，所以无法通过。

然后考虑多项式 $A$ 和 $B$ 之间的关系，设：

$$A = \sum_{i = 0} ^ d a_i x ^ i, B = \sum_{i = 0} ^ d b_i x ^ i$$

显然有：

$$B = \sum_{i = 0} ^ d b_i x ^ i = \sum_{i = 0} ^ d a_i (x + s) ^ i$$

然后推一下式子：

$$\sum_{i = 0} ^ d a_i (x + s) ^ i = \sum_{i = 0} ^ d a_i \times \sum_{j = 0} ^ i \binom{i}{j} x ^ j \cdot s ^ {i - j}$$

$$= \sum_{j = 0} ^ d \sum_{i = j} ^ d \binom{i}{j} a_i \cdot s ^ {i - j} x ^ j$$

然后我们就有：

$$b_i = \sum_{j = i} ^ d \binom{j}{i} a_j \cdot s ^ {j - i}$$

考虑一个特殊情况，当 $i$ 取到 $d - 1$ 时：

$$b_{d - 1} = a_{d - 1} \times s + a_d \times d$$

$$s = \dfrac{b_{d - 1} - a_d \times d}{a_{d - 1}}$$

所以我们并不需要知道多项式 $A$ 和 $B$ 的所有系数，只需要知道 $x ^ {d - 1}$ 项和 $x^d$ 项的系数。

然后考虑拉格朗日插值，假如已知多项式 $F$ 经过 $d + 1$ 个点 $(x_0, y_0), (x_1, y_1), \cdots, (x_d, y_d)$：

$$F(x) = \sum_{i = 0} ^ d y_i \times \prod_{j \neq i} \dfrac{x - x_j}{x_i - x_j}$$

所以多项式 $F$ 就是这个式子，然后考虑变形一下：

$$F(x) = \sum_{i = 0} ^ d \dfrac{y_i}{\prod\limits_{j \neq i} (x_i - x_j)} \times \prod_{j \neq i} (x - x_j)$$

然后求 $x ^ d$ 项系数就是：

$$[x ^ d] F(x) = \sum_{i = 0} ^ d \dfrac{y_i}{\prod\limits_{j \neq i} (x_i - x_j)}$$

可以理解成对于每个 $i$，前面的系数是固定的，然后考虑后面 $\prod\limits_{j \neq i} (x - x_j)$，只有在每一项都取 $x$ 时才能够达到 $x ^ d$，所以这部分的贡献就是 $1$，然后就加起来就行了。

求 $x ^ {d - 1}$ 项系数也类似：

$$[x ^ {d - 1}] F(x) = \sum_{i = 0} ^ d \dfrac{y_i}{\prod\limits_{j \neq i} (x_i - x_j)} \times \sum\limits_{j \neq i} (-x_j)$$

跟上面类似，前面系数固定，后面如果要取到 $x ^ {d - 1}$ 就必须恰好有一处是取到形如 $-x_k$，其余全部取到 $x$，所以贡献就是 $\sum\limits_{j \neq i} (-x_j)$，然后相乘后相加就行了。

至此，只需要预处理出阶乘逆元即可，时间复杂度 $\Theta(d)$。

## 代码链接

<https://codeforces.com/contest/1817/submission/203954733>

---

## 作者：Alex_Wei (赞：8)

#### [CF1817C Similar Polynomials](https://www.luogu.com.cn/problem/CF1817C)

多项式次数太高了，不好处理。考虑 “求导” 降次。离散意义下就是差分。

我们知道，对函数做形如 $f'(x) \gets f(x + 1) - f(x)$ 的差分，则 $\deg f' = \deg f - 1$。所以将 $d + 1$ 个点值差分 $d - 1$ 次，$A$ 从 $d$ 次变成 $1$ 次，也就是直线 $A' = kx + b$。

$A(0\sim d)$ 的 $d - 1$ 阶差分 $a_0, a_1$ 分别等于 $A'(0), A'(1)$，相当于 $kx + b$ 在 $x = 0$ 和 $x = 1$ 处的点值。

$B(0\sim d)$ 即 $A(s\sim s + d)$ 的 $d - 1$ 阶差分 $b_0, b_1$ 分别等于 $A'(s), A'(s + 1)$，相当于 $kx + b$ 在 $x = s$ 和 $x = s + 1$ 处的点值。

显然，根据 $a_0$ 和 $a_1$ 可以直接确定直线，再代入 $(s, b_0)$ 或 $(s + 1, b_1)$ 即可。答案即 $\frac {b_1 - a_1} {a_1 - a_0}$ 或 $\frac {b_0 - a_0} {a_1 - a_0}$。

至于 $k$ 阶差分怎么求：
$$
\Delta ^ k f(x) = \sum_{i = 0} ^ k \binom k i(-1) ^ {k - i} f(x +i)
$$
时间复杂度 $\mathcal{O}(d)$。[代码](https://codeforces.com/contest/1817/submission/204387186)。

---

## 作者：jiangtaizhe001 (赞：2)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/17367904.html)

[题目传送门](https://codeforces.com/contest/1817/problem/C)

Div.1 C 拉格朗日差值，赛时开香槟。

UPD：有个地方打错了，已经更正。

### 题目大意
给定 $d$ 次两个多项式 $A(x),B(x)$。求 $s$，使得 $B(x)\equiv A(x+s) \pmod {10^9+7}$ ，保证 $s$ 存在。  
给出多项式的形式为给出 $x=0,1,\cdots,d$ 模 $10^9+7$ 的值。  
$d\le 2.5 \times 10^7$。
### 题目解析
考虑 $A(x)\equiv B(x-s) \pmod {10^9+7}$，展开 $B(x-s)$。  
发现 $A(x)$ 和 $B(x)$ 最高位系数相同（记位 $k$），并且只要知道第二高位 $k_1,k_2$，那么就有  
$k_1\equiv k_2-2 s k_1\pmod {10^9+7}$。  
所以关键在于求这三个数字。  

考虑拉格朗日插值（考虑 $x_i=i$，这里直接带入）
$$f(x)=\sum_{i=0}^{d}y_i\prod_{j=1,j\not=i}^{n}\dfrac{x-j}{i-j}$$
最高项系数为
$$\sum\limits_{i=0}^d\dfrac{y_i}{(-1)^{d-i} i! (d-i)!}$$
第二高项系数为
$$-\sum\limits_{i=0}^d \dfrac{y_i }{ (-1)^{d-i} i! (d-i)!} \left(\dfrac{d(d+1)}{2}-i\right)$$

预处理 $i!$ 逆元即可，$\Theta(n)$。

```cpp
int n; ll a[maxn],b[maxn],fact[maxn],inv[maxn],k,k1,k2;
ll fpow(ll x,ll y){
	ll tmp=x,res=1;
	while(y){
		if(y&1) res=res*tmp%MOD;
		y>>=1; tmp=tmp*tmp%MOD;
	} return res;
}
ll getk(int d,ll *p){
	ll ans=0; int i;
	for(i=0;i<=d;i++){
		ll t=p[i]*inv[i]%MOD*inv[d-i]%MOD; if((d-i)&1) t=MOD-t;
		ans=(ans+t)%MOD;
	} return ans;	
}
ll getk2(int d,ll *p){
	ll ans=0; int i;
	for(i=0;i<=d;i++){
		ll t=(1ll*d*(d+1)/2-i)%MOD*p[i]%MOD*inv[i]%MOD*inv[d-i]%MOD; if((d-i)&1) t=MOD-t;
		ans=(ans+t)%MOD;
	} return MOD-ans;
}
int main(){
#ifdef LOCAL
	freopen("1.in","r",stdin);
#endif
	n=read(); int i; for(i=0;i<=n;i++) a[i]=read(); for(i=0;i<=n;i++) b[i]=read();
	fact[0]=1; for(i=1;i<=n;i++) fact[i]=fact[i-1]*i%MOD;
	inv[n]=fpow(fact[n],MOD-2); for(i=n-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
	k=getk(n,a); k1=getk2(n,a); k2=getk2(n,b);
	print((k2-k1+MOD)%MOD*fpow(k*n%MOD,MOD-2)%MOD);
	return 0;
}
```

---

## 作者：pengyule (赞：1)

不难想到做法就是将多项式差分 $d-1$ 次后对两个一次函数的横截距作差。

所谓对多项式差分，就是每次对 $y_0,y_1,\dots,y_d$ 这些点值求差分，然后丢掉首项。

如果你记得生成函数的话，就会知道对一个数组 $a_0,a_1,\dots,a_n$ 作 $k$ 次差分得到的数组可以通过以下多项式的各项系数表示：$f^k(x)=(a_0x^0+a_1x^1+a_2x^2+\dots+a_nx^{n})\cdot (1-x)^k$。

我们就是要 $f^{d-1}(x)$ 的第 $d$ 项和第 $d-1$ 项系数。

于是只需要用二项式定理展开 $(1-x)^k$ 计算各 $a_i$ 对 这两项的贡献即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2.5e6+5,mod=1e9+7;
int n,a[N],b[N],jc[N],ijc[N];
inline int C(int n,int m){
	return (ll)jc[n]*ijc[m]%mod*ijc[n-m]%mod;
}
inline int qp(int a,int b){
	int c=1;for(;b;b>>=1,a=(ll)a*a%mod)if(b&1)c=(ll)c*a%mod;
	return c;
}
int work(int a[N]){
	int ret=0;
	for(int i=0;i<n;i++)ret+=(i&1?1ll:mod-1ll)*C(n-1,i)%mod*a[n-1-i]%mod,ret>=mod&&(ret-=mod);
	int ret2=0;
	for(int i=0;i<n;i++)ret2+=(i&1?1ll:mod-1ll)*C(n-1,i)%mod*a[n-i]%mod,ret2>=mod&&(ret2-=mod);
	return mod-(ll)ret2*qp(ret2-ret+mod,mod-2)%mod;
	//y1=kx1+b y2=kx2+b (ret2-ret)=k  b=(y1-kx1)  x1-y1/k  
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	jc[0]=ijc[0]=1;for(int i=1;i<=n;i++)jc[i]=jc[i-1]*(ll)i%mod;
	ijc[n]=qp(jc[n],mod-2);for(int i=n-1;i;i--)ijc[i]=(i+1ll)*ijc[i+1]%mod;
	for(int i=0;i<=n;i++)cin>>a[i];
	for(int i=0;i<=n;i++)cin>>b[i];
	cout<<(work(a)-work(b)+mod)%mod<<'\n';
}
/*
(1-x)^{n-1}
\sum_{i=0}^{n-1} (-1)^{i}x^{i}C(n-1,i)
*/
```

---

## 作者：Little09 (赞：1)

最后 5min 才会，然后没写完。

$$B(x)= \sum_{i=0}^dx^i\cdot b_i$$

$$A(x+s)= \sum_{i=0}^d(x+s)^i\cdot a_i=\sum_{i=0}^dx^i\sum_{j=i}^da_js^{j-i}\binom ji$$

每项系数相等，可得

$$\forall i,\ b_i=\sum_{j=i}^da_js^{j-i}\binom ji$$

推到这一步之后我卡了 40min。然而直接代值进去就做完了。

令 $i=d-1$，代入得到：

$$b_{d-1}=d\cdot a_d\cdot s+a_{d-1}$$

用组合数算出 $a_{d-1},b_{d-1},a_d$ 即可计算 $s$。

---

