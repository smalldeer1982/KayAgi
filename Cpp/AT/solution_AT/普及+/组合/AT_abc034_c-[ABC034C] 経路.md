# [ABC034C] 経路

## 题目描述

有一个 $W$ 行 $H$ 列的网格图（$2 \leq W,H \leq 10^5$），其中第 $i$ 行第 $j$ 列的坐标为 $(i,j)$。

现在有一个人想从起点 $(1,1)$ 走到终点 $(W,H)$，已知他每次可以从网格 $(i,j)$ 走向 $(i+1,j)$ 或 $(i,j+1)$。现在请你求出，他从起点走到终点的路线个数为多少。

由于这个数可能很大，因此你只要输出路线个数对 $10^9 + 7$ 取模的结果即可。

## 样例 #1

### 输入

```
4 3```

### 输出

```
10```

## 样例 #2

### 输入

```
123 456```

### 输出

```
210368064```

# 题解

## 作者：残阳如血 (赞：1)

### $\textbf{Description}$
给定一个 $n\times m$ 的网格，求 $(1,1)\to(n,m)$ 的方案数。

对 $10^9+7$ 取模。
### $\textbf{Solution}$

[没有学过乘法逆元的点这里](https://www.cnblogs.com/oier-wst/p/18423863/mul_inv)。

考虑从 $(1,1)\to(n,m)$，总共走了 $(n-1)+(m-1)=n+m-2$ 步。

其中，有 $n-1$ 步往下，$m-1$ 步往右。

那么，每一步向下的位置一旦确定，整条路线就确定了。

所以总方案数即从 $n+m-2$ 步中选出 $n-1$ 步的方案数，即：
$$
{n+m-2\choose n-1}
$$

---

组合数计算公式为
$$
{a\choose b}=\dfrac{a!}{b!(a-b)!}
$$

预处理出 $1\sim a$ 每个数的逆元，然后线性递推每个数的阶乘及其逆元。

可得
$$
{a\choose b}=\dfrac{a!}{b!(a-b)!}\equiv a! (b!)^{-1}\big((a-b)!\big)^{-1}
$$

最后套一下公式就行了。

---

原题中，此方法预处理复杂度为 $O(n+m)$，单次询问复杂度为 $O(1)$，故总时间复杂度为 $O(n+m)$。
### $\textbf{Code}$
[record](https://atcoder.jp/contests/abc034/submissions/62482985)。

```cpp
// C(n+m-2, n-1)
#include <bits/stdc++.h>
using lint = long long;
const int N = 2e5 + 10;
const int MOD = 1e9 + 7;

lint n, m, inv[N], fact[N], inv_fact[N];

void init() {
	inv[0] = inv[1] = 1;
	for (int i = 2; i < N; ++i)
		inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
	fact[0] = inv_fact[0] = 1;
	for (int i = 1; i < N; ++i) {
		fact[i] = fact[i - 1] * i % MOD;
		inv_fact[i] = inv_fact[i - 1] * inv[i] % MOD;
	}
}

lint C(int n, int m) {
	if (m > n) return 0;
	if (m == n) return 1;
	return fact[n] * inv_fact[m] % MOD * inv_fact[n - m] % MOD;
}

int main() {
	init();
	std::cin >> n >> m;
	std::cout << C(n + m - 2, n - 1) << std::endl;
	return 0;
}
```

---

## 作者：jzjr (赞：1)

# [ABC034C]経路

## 前置知识

* 排列组合
* 逆元

## 翻译题意

给你一个 $H\times W$ 的点阵，现在需要你计算从点 $(1,1)$ 走到 $(H,W)$ 的总方案数。

### $O(H+W)$ 排列组合

不妨把从点 $(1,1)$ 到 $(H,W)$ 的路径看作 $H+W-2$ 次操作，$W-1$ 次横着走操作和 $H-1$ 次竖着走操作的排列。

那么问题就转换成了在 $H+W-2$ 个空位中挑选 $H-1$ 个空位。

显然，这个答案是 $C_{H+W-2}^{H-1}$。

这个 $C$ 是组合数，他的计算公式是：

$$
C_n^m=\frac{n!}{m!\times(n-m)!}
$$

## 处理除法

那么我们的答案显然易见：

$$
ans\equiv\frac{(H+W-2)!}{(H-1)!\times(W-1)!}\pmod{10^9+7}
$$ 

但是我们发现如果在计算中分母不整除于分子时，取模就不能计算。

事实上，这需要逆元来帮忙。

### 什么是逆元

逆元的定义简单概述一下。

对于模数 $p$ 和正整数 $a$。

如果 $\gcd{(a,p)}=1$，那么一定存在正整数 $b$ 满足 $a\times b\equiv1\pmod p$。

此时记 $b=a^{-1}\pmod p$。

这样就实现了同余除法。

$$\frac{n}{m}\equiv n\times m^{-1}\pmod p$$

而快速求逆元有一种好方法，费马小定理。

$$
a^{p}\equiv a\pmod p
$$

（$p$ 为质数。）

那么 $a^{p-2}\equiv a^{-1}\pmod p$ 。

此时就求出了逆元，这需要利用快速幂。

## AC code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
LL jc[200005],ni[200005],mod=1e9+7;
LL H,W;
LL ksm(LL x,LL y,LL mod){
	LL ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;y=y>>1;
	}
	return ans;
}
void asd(){
	int tot=W+H;
	jc[0]=ni[0]=1;
	for(LL i=1;i<=tot;i++)jc[i]=jc[i-1]*i%mod;
	ni[tot]=ksm(jc[tot],mod-2,mod);
	for(int i=tot-1;i>0;i--)ni[i]=ni[i+1]*(i+1)%mod;
}
LL C(LL n,LL m){
	return jc[n]*ni[m]%mod*ni[n-m]%mod;
}
int main (){
	cin>>H>>W;
	H--;W--;
	asd();
	cout<<C(H+W,W)<<endl;
	return 0;
}
```

---

## 作者：zjinze (赞：1)

#### 前置知识：组合数学

#### 思路：

对于这个网格图，我们只能往下或往右边走，所以我们从 $(1,1)$ 走到 $(W,H)$，显然只能走 $W+H-2$ 步；这时我们发现我们要从 $(1,1)$ 走到 $(W,H)$ 要向下走 $W-1$ 步才可能到达终点，所以问题就转化为了在 $w+n-2$ 步中，选 $W-1$ 步向下走的方案数，这时我们直接预处理组合数即可。这里如果考虑向右走 $H-1$ 步也是可以的。

#### code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
const int N=2e5+7;
int n,m,jc[N],inv[N];
int ksm(int a,int b){
	int tmp=1;
	a%=mod;
	while(b){
		if(b&1){
			tmp=tmp*a;
			tmp%=mod;
		}
		a*=a;
		a%=mod;
		b>>=1;
	}
	return tmp;
}
int C(int m,int n){
	return (((jc[n]*inv[m])%mod)*inv[n-m])%mod;
}
signed main(){
	jc[0]=inv[0]=1;
	for(int i=1;i<N;i++){
		jc[i]=(jc[i-1]*i)%mod;
		inv[i]=ksm(jc[i],mod-2);
	}
	cin>>n>>m;
	cout<<C(n-1,(m+n-2))<<"\n";
	return 0;
}
```

---

## 作者：cheatme (赞：0)

## 题目描述
从 $(1,1)$ 走到 $(w,h)$，求一共有多少种走法。

## 题目分析:
考虑优化复杂度，分析题目得出要从 $(1,1)$ 走到 $(W,H)$ ，从上到下要走 $W-1$ 步，从左到右要走 $H-1$ 步，一共则要走 $W+H-2$ 步。考虑在总 $W+H-2$ 步下，从上到下走 $W-1$ 步的方案数。

总方案数为 $C_{W-1}^{W+H-2}$种。

## AC代码
```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int mod=1e9+7,N=1e5+7;
int n,m,sum[N*2];//n+m要开两倍
int ksm(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1) res=res*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return res;
}
//排列组合
int C(int a,int b)
{
	int res=sum[b]*ksm(sum[a],mod-2)%mod*ksm(sum[b-a],mod-2)%mod;
	return res;
}
void solve()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	//预处理
	sum[0]=1;
	for(int i=1;i<=n+m;i++) sum[i]=sum[i-1]*i%mod;
	cout<<C(n-1,m+n-2)<<'\n';
}
signed main()
{
	solve();
	return 0;
}

```
# [ $Code$ ](https://www.luogu.com.cn/record/178004720)

---

## 作者：qfy123 (赞：0)

# ABC034C
[传送门](https://www.luogu.com.cn/problem/AT_abc034_c)

考察知识：组合数学，模意义下的乘法逆元。
## 思路
注：题目中的 $W,H$ 在题解中分别用 $n,m$ 代指。

很容易想到一个 $O(nm)$ 的 DP 做法。具体地，设 $dp_{i,j}$ 为这个人走到第 $i$ 行第 $j$ 列的方案数，转移式就是 $dp_{i,j} \gets dp_{i,j-1} + dp_{i-1,j}$，即走到点 $(i,j)$ 的路径个数是左边与上边的路径个数之和。但在这题中，$O(nm)$ 显然无法通过。

不难发现：这个人一共要向右走 $n - 1$ 次，向下走 $m - 1$ 次才能到达终点，一共要走 $n+m-2$ 步。那我们用一个长度为 $n+m-2$ 的 $01$ 串代指一条路径，用 $1$ 代指向右走，$0$ 代指下走，答案就是求不同的 $01$ 串的个数。问题不难转化为，在一个长度为 $n+m-2$ 且数值全为 $0$ 的串中，任选 $n-1$ 个数赋值为 $1$ 的方案数，这显然是一个组合数学问题，答案就是 $C_{n-1}^{n+m-2}$。最后，关于取模，由于涉及分数取模，因此要求乘法逆元。

由于 $n,m$ 同阶，因此预处理时间复杂度 $O(n)$，计算组合数是 $\log$ 的，总时间复杂度 $O(n)$。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
#define ull unsigned long long
#define ri register int
#define rep(i,j,k) for(ri i=(j);i<=(k);++i) 
#define per(i,j,k) for(ri i=(j);i>=(k);--i)
#define repl(i,j,k,l) for(ri i=(j);(k);i=(l))
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define pc(x) putchar(x)
#define fir first
#define se second 
#define MP pair<int,int>
#define PB push_back
using namespace std;
char Rd[100000],*PPP(0),*TOP(0);
#define gtc() (PPP == TOP && (TOP = (PPP = Rd) + fread(Rd,1,100000,stdin)),*PPP++)
inline int R(){
    int x;char c;bool f = 0;
	while((c = gtc()) < '0') if(c == '-') f = 1;
	x = c ^ '0';
	while((c = gtc()) >= '0') x = (x << 3) + (x << 1) + (c ^ '0');
	return f?(~x + 1):x;
}
inline void O(int x){
    if(x < 0) pc('-'),x = -x;
    if(x < 10) pc(x + '0');
    else O(x / 10),pc(x % 10 + '0');
}
inline void out(int x,int type){
	if(type == 1) O(x),pc(' ');
	if(type == 2) O(x),pc('\n');
	if(type == 3) O(x);
}
const int N = 2e5 + 10;
const int mod = 1e9 + 7;
int f[N],n,m;
int ksm(int a,int b){
	int ret = 1;
	while(b){
		if(b & 1) ret = (ret * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return ret;
}
int C(int x,int y){
	return f[x] * ksm(f[y], mod - 2) % mod * ksm(f[x - y], mod - 2) % mod;
}//计算组合数 C(x,y)
signed main(){
	n = R(), m = R();
	f[0] = 1;
	rep(i, 1, n + m) f[i] = (f[i - 1] * i) % mod;
	out(C(n + m - 2, n - 1), 2); 
	return 0;
}

```

---

