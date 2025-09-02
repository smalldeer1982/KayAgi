# [ARC059F] バイナリハック

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc059/tasks/arc059_d

しぐはキーボードを製作しました。シンプルさを極限まで追求したこのキーボードには、`0` キー、`1` キー、バックスペースキーの $ 3 $ つしかキーがありません。

手始めに、しぐはこのキーボードで簡単なテキストエディタを操作してみることにしました。このエディタには常に一つの文字列が表示されます（文字列が空のこともあります）。エディタを起動した直後では、文字列は空です。キーボードの各キーを押すと、文字列が次のように変化します。

- `0` キー: 文字列の右端に文字 `0` が挿入される。
- `1` キー: 文字列の右端に文字 `1` が挿入される。
- バックスペースキー: 文字列が空なら、何も起こらない。そうでなければ、文字列の右端の $ 1 $ 文字が削除される。

しぐはエディタを起動し、これらのキーを合計で $ N $ 回押しました。その結果、いまエディタに文字列 $ s $ が表示されています。このようなキーの押し方の個数を $ 10^9\ +\ 7 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 5000 $
- $ 1\ ≦\ |s|\ ≦\ N $
- $ s $ は文字 `0`, `1` のみからなる。

### 部分点

- $ 1\ ≦\ N\ ≦\ 300 $ を満たすデータセットに正解すると、$ 400 $ 点が与えられる。

### Sample Explanation 1

バックスペースキーを `B` と表記すると、次の $ 5 $ 通りの押し方で最終的に表示される文字列が `0` となります: `00B`, `01B`, `0B0`, `1B0`, `BB0`。最後の押し方では、バックスペースキーを押すときに何も起こりません。

## 样例 #1

### 输入

```
3
0```

### 输出

```
5```

## 样例 #2

### 输入

```
300
1100100```

### 输出

```
519054663```

## 样例 #3

### 输入

```
5000
01000001011101000100001101101111011001000110010101110010000```

### 输出

```
500886057```

# 题解

## 作者：dd_d (赞：25)

[更好的阅读体验](https://www.cnblogs.com/dd-d/p/15251884.html)
### Sol  
考虑 dp。  
设 $dp_{i,j}$ 表示敲击了键盘 $i$ 次，匹配了 $j$ 个字符的方案数。  
考虑如何转移。  
分以下两种情况进行讨论。  

- 敲了退格。那么 $dp_{i,j}$ 可以由 $dp_{i-1,j+1}$ 转移。由于我们不关心第 $j+1$ 位的字符是 $0$ 还是 $1$，所以 $dp_{i,j}=dp_{i,j}+2 \times dp_{i-1,j+1}$。  
- 敲了 $0$ 或 $1$。那么 $dp_{i,j}$ 可以从 $dp_{i-1,j-1}$ 转移而来。但要注意，此处 $j-1$ 需 $\geq 0$。  

边界 $dp_{0,0}=1$。  
### Code  
``` cpp
cin>>n>>st;
dp[0][0]=1;
for (int i=1;i<=n;i++)
	for (int j=0;j<=i;j++)
		dp[i][j]=(dp[i-1][max(j-1,0)]+dp[i-1][j+1]*2%mod)%mod;
cout<<dp[n][st.size()]<<endl;
```

---

## 作者：dead_X (赞：10)

## 前言
好像是新做法。
## 思路
一眼发现字符串是什么并不影响答案，只和串长 $m$ 有关。

考虑分成 $m$ 步，每步包含一些没有意义的操作（若干次操作之后字符串内容不变），然后做了一一个有意义的操作（增加一个有意义的字符）。

我们强制钦定第 $n+1$ 步必须做有意义的操作，因此我们将 $n,m$ 都增加 $1$，就可以分步了。 

考虑 $i$ 次操作没有意义的方案数：

- 必须恰好 $\frac{i}{2}$ 次插入和删除。
- 不能删掉原有的数。

这就是卡特兰数嘛，然后每次插入有两种方案，因此 $2i$ 次操作没有意义的方案数即为 $\frac{2^i\binom{2i}{i}}{i+1}$，可以直接多项式快速幂了……吗？

注意到样例 $1$ 中 ``BB0`` 也是合法的操作，也就是说第一次合法操作之前可以删空，需要将这些方案也计算上，这里同样也可以将“一定长度的卡特兰数加一个无效操作”进行打包，通过求逆做到 $O(n\log n)$。

于是我们在 $O(n\log n)$ 的时间复杂度内解决了此题！

唯一 ↑↓ 的地方在于出题人给的模数不是 NTT 模数，幸好数据范围是 $n,m\leq 5000$，多项式快速幂可以写整数快速幂的 $O(n\log^2 n)$ 的写法，而第一次合法操作之前删空的方案数可以直接写 $O(n^2)$。

到时候就改成 NTT 模数然后搬模拟赛里。
## 代码
```cpp
// Problem: F - Unhappy Hacking
// Contest: AtCoder - AtCoder Regular Contest 059
// URL: https://atcoder.jp/contests/arc059/tasks/arc059_d
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//回家？我没有家可以回，我没有退路。
#include<bits/stdc++.h>
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=1e9+7;
int qp(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=t*t%p) if(y&1) res=res*t%p;
	return res;
}
char s[5003];
int f[5003][5003],g[5003],pw[5003],h[5003],fac[5003],ifac[5003];
int C_(int n,int m){return fac[n]*ifac[m]%p*ifac[n-m]%p;}
const long double pi=acos(-1);
struct cp
{
    long double r,i;
    cp operator+(const cp &x)const{return (cp){x.r+r,x.i+i};}
    cp operator-(const cp &x)const{return (cp){r-x.r,i-x.i};}
    cp operator*(const cp &x)const{return (cp){r*x.r-i*x.i,r*x.i+i*x.r};}
}A[600003],B[600003],C[600003],D[600003],E[600003];
int rev[6000003],N=1;
void init()
{
    int d=N>>2;
    rev[0]=0,rev[1]=N>>1;
    for(int i=2; i<N; i<<=1,d>>=1)
        for(int j=0; j<i; ++j) 
        	rev[i+j]=rev[j]|d;
    return ;
}
void FFT(cp* F,int op)
{
    for(int i=0; i<N; ++i) if(rev[i]>i) swap(F[i],F[rev[i]]);
    for(int len=2,M=1; len<=N; len<<=1,M<<=1)
    {
        cp w=(cp){cos(pi/M*op),sin(pi/M*op)};
        for(int l=0,r=len-1; l<N; l+=len,r+=len)
        {
            cp w0=(cp){1,0};
            for(int i=l; i<l+M; ++i)
            {
                cp x=F[i],y=w0*F[i+M];
                F[i]=x+y,F[i+M]=x-y,w0=w0*w;
            }
        }
    }
}
int n=read()+1;
void mul(int *a,int *b,int *c)
{
    for(int i=0; i<N; ++i) A[i]=(cp){0,0};
    for(int i=0; i<N; ++i) B[i]=(cp){0,0};
    for(int i=0; i<N; ++i) C[i]=(cp){0,0};
    for(int i=0; i<N; ++i) D[i]=(cp){0,0};
    for(int i=0; i<=n; ++i) A[i].r=a[i]&32767,B[i].r=a[i]>>15;
    for(int i=0; i<=n; ++i) C[i].r=b[i]&32767,D[i].r=b[i]>>15;
    
    FFT(A,1),FFT(B,1),FFT(C,1),FFT(D,1);
    for(int i=0; i<N; ++i) E[i]=A[i]*D[i]+B[i]*C[i],A[i]=A[i]*C[i],B[i]=B[i]*D[i];
    FFT(A,-1),FFT(B,-1),FFT(E,-1);
    for(int i=0; i<=n; ++i) 
    {
        long long ans1=(A[i].r/N+0.5),ans2=(E[i].r/N+0.5),ans3=(B[i].r/N+0.5);
        ans2%=p,ans2=(ans2<<15)%p,ans3%=p,ans3=(ans3<<30)%p;
        c[i]=(ans1+ans2+ans3)%p;
    }
    return ;
}
signed main()
{
	for(N=1;N<=(n<<1);N<<=1);
	init(),scanf("%s",s+1);
	int m=strlen(s+1);
	fac[0]=ifac[0]=pw[0]=f[0][0]=h[0]=1;
	for(int i=1; i<=n; ++i) 
		fac[i]=fac[i-1]*i%p,ifac[i]=qp(fac[i],p-2),pw[i]=(pw[i-1]<<1)%p;
	for(int i=0; (i<<1)<n; ++i) 
		g[(i<<1)+1]=C_(i<<1,i)*qp(i+1,p-2)%p*pw[i]%p;
	int ans=0;
	for(int i=0; i<n; ++i)
	{
		f[i+1][0]=f[i][0];
		for(int j=1; j<=i; ++j)
			f[i+1][j-1]=(f[i+1][j-1]+f[i][j])%p;
		for(int j=0; j<=i; ++j)
			f[i+1][j+1]=(f[i+1][j+1]+(f[i][j]<<1))%p;
	}
	while(m)
	{
		if(m&1) mul(g,h,h);
		mul(g,g,g),m>>=1;
	}
	for(int i=0; i<n; ++i) 
		ans=(ans+f[i][0]*h[n-i-1])%p;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：zhylj (赞：6)

这里给一个不依赖于乘法逆元的做法。

考虑把键盘分为两类，一类是退格，一类是普通的字符，考虑显然我们只关心敲的字符最终有哪些最后留在了屏幕上，而这些方案显然是确定的（从左到右一一匹配），而不存在于屏幕上的键是谁我们并不关心（即可以任取），设任取的位数是 $r$，则这样一个敲键盘的方案对应了 $2^r$ 种方案。

于是考虑记 $f_{i,j}$ 表示敲了 $i$ 次，最后匹配了一个长度为 $j$ 的串（我们并不关心它匹配了哪个串，因为所有长度一样的串都是等价的）的方案数。

然后转移考虑两种情况：

- 敲了 $0$ 或 $1$：那么将会多匹配一个位置，且不会导致可以任取的位增加，即 $f_{i,j}\to f_{i+1,j+1}$.
- 敲了退格，且的确退了一格，此时我们上一次敲得字符变为了可以任取的位，即 $2\cdot f_{i,j}\to f_{i+1,j-1}$，此处要求 $j > 0$.
- 敲了退格，但并未退格，即 $f_{i,0}\to f_{i+1,0}$.

然后我们就做完了，时间复杂度 $\mathcal O(n|s|)$.

```cpp
const int N = 5e3 + 5, Mod = 1e9 + 7;

int n, m, f[N][N];
char s[N];

void Get(int &x, int y) {
	x = (x + y) % Mod;
}

int main() {
	rd(n); scanf("%s", s + 1);
	m = strlen(s + 1);
	f[0][0] = 1;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j <= i; ++j) {
			if(j) Get(f[i + 1][j - 1], 2 * f[i][j] % Mod);
			else Get(f[i + 1][0], f[i][j]);
			Get(f[i + 1][j + 1], f[i][j]);
		}
	printf("%d\n", f[n][m]);
	return 0;
}
```

---

## 作者：是个汉子 (赞：4)

[洛谷传送门](https://www.luogu.com.cn/problem/AT2022)	[AT传送门](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/2022)

### Solution

对于一个长度为 $len$ 的01字符串，总共有 $2^{len}$ 种不一样的情况。

在题目给定的输入方式下，得到这 $2^{len}$ 种不一样的情况的方案数是相等的。

那么我们只需要求出操作 $n$ 次长度为 $|S|$ 的方案数即可。

设 $f_{i,j}$ 表示操作 $i$ 次，当前长度为 $j$ 的方案数。因为能处很多状态转移过来，所以考虑用 $f_{i}$ 来转移 $f_{i+1}$ 。

则状态转移方程是：
$$
f_{i+1,j+1}+=2\times f_{i,j},f_{i+1,\max(j-1,0)}=+=f_{i,j}
$$
分别代表着输入 $0,1$ 和删除。

则答案就是 $\dfrac {f_{n,len}}{2^{len}}$ 

小细节：因为有模数，所以可以用乘法逆元。

### Code

```c++
#include<bits/stdc++.h>
#define ll long long

using namespace std;
const int N=5010,mod=1e9+7;
char str[N];
int f[N][N],len,n;

ll fpow(ll p,int q){
    ll res=1;
    while(q){
        if(q&1) res=res*p%mod;
        p=p*p%mod;
        q>>=1;
    }
    return res;
}

inline int max(int a,int b){
    return a>b?a:b;
}

inline void init(){
    len=int(strlen(str)),f[0][0]=1;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=i;j++){
            f[i+1][j+1]=int((1ll*f[i][j]*2%mod+f[i+1][j+1])%mod);
            f[i+1][max(j-1,0)]=(f[i][j]+f[i+1][max(j-1,0)])%mod;
        }
}

int main(){
    scanf("%d%s",&n,str);
    init();
    printf("%d\n",f[n][len]*fpow(fpow(2,len),mod-2)%mod);
    return 0;
}
```



---

## 作者：Natori (赞：3)

打了一个月的线段树，好像应该打打 $\text{DP}$ 换换脑子。

# 状态设计

容易想到与 $\text{DP}$ 状态相关的量有下面 $3$ 个：

- 已经操作的次数

- 已经打出的 $0/1$ 串的状态

- 方案数

由于已经打出的 $0/1$ 串的状态**表示起来太大**，

倒是可以考虑用 ```bitset``` 或者字符串表示当前 $0/1$ 串，

作为关键字放入 ```std::map``` 中查询。

但是这样做比较复杂，效率也不高，

因为要 ```std::map``` 查询，单次转移的时间复杂度在 $O(\log_2{n})$ 级别。

## 但是

实际上不需要记录处理已经打出的 $0/1$ 串的状态，

只需记录**与原串匹配上的子串长度**即可。

因此我们更改一下与 $\text{DP}$ 状态相关的量：

- 已经操作的次数

- 已经打出的 $0/1$ 串与原串匹配上的子串长度

- 方案数

前两个量比较小，考虑把它们作为 $\text{DP}$ 数组下标。

**状态设计**也就出来了：

设 $f_{i,j}$ 表示操作 $i$ 次后与原串匹配上 $j$ 个位置的方案数。

# 状态转移

显然，$f_{0,0}=1$，目标状态是 $f_{n,m}$。

根据题意，每个状态可以由两种方式得到：**打出字符和删除字符**。

那么可以分别调用两种情况对应的状态，然后用**加法原理**合并即可。

- 打出字符

打出字符使匹配长度增加了一位，即 $j-1 \Rightarrow j$，

同时操作次数也增加了 $1$ 次，即 $i-1 \Rightarrow i$。

所以，$f_{i,j}=f_{i-1,j-1}$。

- 删除字符

删除字符使匹配长度减少了一位，即 $j+1 \Rightarrow j$，

操作次数同打出字符，

由于之前打出的字符可能是 $0$ 或 $1$，所以方案数要乘 $2$。

$f_{i,j}=f_{i,j}+2 \times f_{i-1,j+1}$。

至此状态转移也出来了：

$$f_{i,j}=f_{i-1,j-1}+2 \times f_{i-1,j+1}$$

# 进一步的优化

上述 $\text{DP}$ 的空间复杂度是 $O(n^2)$ 的，会到 $100 \text{Mb}$ 以上。

~~虽然ML是250Mb~~

发现**状态 $f_{i,j}$ 只会从 $f_{i-1}$ 转移而来**，

所以我们可以使用**滚动数组**压缩内存。可以压到 $2Mb$以内。

~~不知道为什么运行时间也少了好多~~

代码（注意开 $\text{long long}$）：

```cpp
#include<cstdio>																																																				请勿抄袭                      
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
ll read(){
	ll f=1,x=0;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=x*10+c-'0';
		c=getchar();
	}
	return f*x;
}
void write(ll x){
	if(x<0)x=-x,putchar('-');
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
const int N=5010;
const ll mod=1e9+7;
int n,m;
char str[N];
ll f[2][N];
int main(){
	n=read();
	scanf("%s",str);
	m=strlen(str);
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i;j++){
			f[i&1][j]=(f[i&1^1][max(j-1,0)]+2ll*f[i&1^1][j+1])%mod;
		}
	}
	write(f[n&1][m]);
	return o;
}
```

希望对大家有所帮助。

---

## 作者：Kevin_Zhen (赞：2)

题目链接 [$\mathfrak{AT2022}$](https://www.luogu.com.cn/problem/AT2022)。  
[可能更好的阅读体验](https://www.luogu.com.cn/blog/150cm/solution-at2022)。

### 解题思路
一个长度为 $len$ 的 $01$ 串有 $2^{len}$ 种不同的情况，发现凑出每种情况的方案数是相等的。所以只要求得 $n$ 次操作后字符串长度为 $\left\vert S\right\vert$ 的总方案数，然后除以 $2^{len}$，即为凑出其中一种情况的方案数。

设 $f_{i,j}$ 表示 $i$ 次操作后，字符串长度为 $j$ 的方案数。  
那么第 $i+1$ 次操作有两种可能：向原字符串末尾添加一个数，或删去一个数。  
注意到添加的数有 $0$ 和 $1$ 两种可能，所以一共会给 $f_{i+1,j+1}$ 贡献 $f_{i,j}\times 2$ 种方案；而删去一个数只会给 $f_{i+1,j-1}$ 贡献 $f_{i,j}$ 种方案。  
但仍有一种**极端情况**：在当前字符串为空串时，如果持续按退格键，仍会增加操作次数，但字符串长度为 $0$ 保持不变。考虑到这种特殊情况，应向 $f_{i+1,\max(j-1,0)}$ 转移。  
转移方程如下：
$$f_{i+1,j+1}=f_{i+1,j+1}+f_{i,j}\times 2$$
$$f_{i+1,\max(j-1,0)}=f_{i+1,\max(j-1,0)}+f_{i,j}$$

为什么要从 $f_i$ 推向 $f_{i+1}$，而非从 $f_{i-1}$ 推向 $f_i$？  
注意到对于当前状态，先前状态进行的操作是未知的，所以我们无法得知当前字符串是由哪个字符串转移而来，从而无法确定上个状态的字符串长度。但当前字符串是啥样我们是知道的，所以可以用当前状态更新可以扩展到的状态。  
或者可以感性理解：如果是用 $f_i$ 更新 $f_{i+1}$，显然 $f_{i+1}$ 是可能被多次更新的。而由 $f_{i-1}$ 推向 $f_i$ 却要求一次求出 $f_i$，那么剩余的复杂度就在确定 $f_{i-1}$ 的字符串状态上了。

输出答案时因为要对大质数取模，需要用到乘法逆元。具体地，当 $p$ 为质数时，$a^{p-2}\equiv \dfrac{1}{a}\pmod{m}$。

### AC CODE
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long ll;

const int maxn = 5010;
const int Mod = 1e9 + 7;

int n, len; char s[maxn];
ll f[maxn][maxn];

inline ll qpow(ll base, int p) {
	ll res = base; --p;
	while (p) {
		if (p & 1) res = res * base % Mod;
		base = base * base % Mod;
		p >>= 1;
	}
	return res;
}

int main() {
	scanf("%d%s", &n, s); len = strlen(s);
	f[0][0] = 1;
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= i; ++j) {
			f[i + 1][j + 1] += f[i][j] << 1; f[i + 1][j + 1] %= Mod;
			f[i + 1][max(j - 1, 0)] += f[i][j]; f[i + 1][max(j - 1, 0)] %= Mod;
		}
	}
	printf("%lld", f[n][len] * qpow(qpow(2, len), Mod - 2) % Mod);
	return 0;
}
```


---

## 作者：henry_y (赞：2)

[可以选择在我的博客观看](https://www.cnblogs.com/henry-1202/p/atcoder_training.html)

## 做法 ： dp+乘法逆元

这个F题是假的吧...感觉没有F题难度

就设$f[i][j]$表示按了$i$次键盘，然后一共出现了$j$个字母的情况

刚开始愣是想不到怎么转移，因为可以$f[i][j]$可以从好几个状态转移过来...

秒了一眼题解发现可以用$f[i][j]$去更新别人...所以就转移两次就行了

$f[i+1][j+1]+=2*f[i][j]$（因为可以按0或者1，所以要乘2）

$f[i+1][min(j-1,0)]+=f[i][j]$（这里是按后退键的情况，因为0也是合法状态所以要算进去，取个$min$）

但是这样子算出来的$f[n][len]$是能够用$n$次操作拼出长度为$len$的字符串的方法总数（一共可以评出$2^{len}$个串），所以要除一下$2^{len}$

但是因为有取模所以要用一下乘法逆元，这里用快速幂来求乘法逆元

```
#include <bits/stdc++.h>

using namespace std ;

#define N 5010
#define ll long long
const int mod = 1e9+7 ;

int n ;
char s[ N ] ;
int f[ N ][ N ] ;
//f[ i ][ j ] 表示按了i次键盘，出现了j个字母 

ll power( ll a , ll b ) {
	ll ans = 1 , base = a ;
	while( b ) {
		if( b&1 ) ans = ( ans * base ) % mod ;
		base = ( base * base ) % mod ;
		b >>= 1 ;
	}
	return ans % mod ;
}

int main() {
	scanf( "%d%s" , &n , s+1 ) ;
	int len = strlen( s + 1 ) ;
	f[ 0 ][ 0 ] = 1 ;
	for( int i = 0 ; i <= n ; i ++  ) {
		for( int j = 0 ; j <= i ; j ++ ) {
			f[ i + 1 ][ j + 1 ] += 2 * f[ i ][ j ] ;
			f[ i + 1 ][ j + 1 ] %= mod ;
			f[ i + 1 ][ max( j - 1 , 0 ) ] += f[ i ][ j ] ;
			f[ i + 1 ][ max( j - 1 , 0 ) ] %= mod ;
		}
	}
	ll ans =1ll*power( power( 2 , len ) , mod - 2 ) % mod * f[ n ][ len ] ;
	ans %= mod ;
	printf( "%lld" , ans ) ;
	return 0 ;
} 
```

---

## 作者：daniEl_lElE (赞：1)

一道很有意思的 $dp$。

## 思路

一个比较显然的思路就是考虑 $dp_{i,j}$ 表示看到 $i$ 次目前匹配了 $j$ 次的方案。

这样设计状态，很容易递推到 $dp_{i+1,j+1}$。问题在于怎么添加一个撤回键。

由于上次已经成功匹配到了第 $j$ 位，那么第 $j-1$ 到 $j$ 必须选了 $s_j$ 这个键。但是撤回的时候并不必要选的一样。你可能可以加入新的一维，$dp_{i,j,k}$ 表示看到第 $i$ 位目前有 $j$ 位且确定了前 $k$ 位，转移会很方便，可惜复杂度 $O(n^3)$ 只能通过部分分。

事实上，我们在转移的时候，可以只考虑 $j-1$ 到 $j$ 这里对应的一个，他也可以不选择 $s_j$，其实就是方案数变成了两倍而已。然后我们就可以递推了。复杂度 $O(n^2)$。注意 $dp_{i,0}$ 可以推到 $dp_{i+1,0}$ 且方案数不能乘 $2$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define ls i*2
#define rs i*2+1
#define Ls ls,l,mid
#define Rs rs,mid+1,r
using namespace std;
const int mod=1e9+7;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans;
}
int fac[100005],inv[100005];
void init(){
	fac[0]=1;
	for(int i=1;i<=100000;i++) fac[i]=fac[i-1]*i%mod;
	inv[100000]=qp(fac[100000],mod-2);
	for(int i=99999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int i,int j){
	if(i<j||i<0||j<0) return 0;
	return fac[i]*inv[j]%mod*inv[i-j]%mod;
}
int dp[5005][5005];
signed main(){
	init();
	int n;
	cin>>n;
	string s;
	cin>>s;
	int m=s.size();
	dp[0][0]=1;
	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++){
			if(j==0) dp[i+1][j]=(dp[i+1][j]+dp[i][j])%mod;
			else dp[i+1][j-1]=(dp[i+1][j-1]+2*dp[i][j])%mod;
			dp[i+1][j+1]=(dp[i+1][j+1]+dp[i][j])%mod;
		}
	}
	cout<<dp[n][m];
	return 0;
}
```

---

## 作者：OIerBoy (赞：1)

# Sol
一道非常水的 dp 题。

先看数据 $N\le 5000$，考虑 $O(n^2)$ dp。

对于题目的三个操作中，我们唯一需要仔细思考的就是对于退格的操作，因为退格操作是不需要去保证退掉的字符 $0/1$ 的，但需要保证退掉之后剩下的字符是我们想要的。那么我们就需要将 dp 的一维状态设计为可以去处理退格的。

记 $f_{i,j}$ 表示当前进行了 $i$ 次操作，当前已经匹配了 $j$ 个字符。（这里使用刷表法转移）

那么我们对于输入 $0/1$ 的操作转移就非常轻松：$f_{i+1,j+1}\gets f_{i,j}$。

那如何很好的处理退格呢，前面说了不需要去知道被退的字符，那么我们退掉的字符就会有两种可能，而我们 dp 的第二位有保证了前 $j$ 个字符匹配的，我们就可以直接进行转移了：

$$\begin{cases}f_{i+1,j-1}\gets f_{i,j}\times 2 & (j>0)\\f_{i+1,j-1}\gets f_{i,j} & (j=0)\end{cases}$$

然后这道紫题就通过了。

# Code
```cpp
#include<bits/stdc++.h>
#define db doub
#define inf LONG_LONG_MAX
#define fir first
#define sec second
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
#define Pr(i,j) pair<i,j>
#define PB(i) push_back(i)
#define MP(i,j) make_pair(i,j)
#define Fo(i,j) for(auto i:j)
#define mem(i,j) memset(i,j,sizeof(i))
#define FO(i,j,k) for(int i=j;i;i=k)
#define FFF(i,j,k) for(auto i=j;i!=k;++i)
#define For(i,j,k) for(int i=j;i<=k;++i)
#define FoR(i,j,k) for(int i=j;i^k;++i)
#define FOR(i,j,k) for(int i=j;i>=k;--i)
using namespace std;
template <typename _Tp>void read(_Tp& first) {
    _Tp x = 0, f = 1; char c = getchar();
    while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ '0'), c = getchar();
    first = x * f;
}
#define N 5005
#define Mod 1000000007
#define int long long
int n,m;
int f[N][N];
string s;
signed main(){
    read(n);
    cin>>s;
    s=' '+s;
    m=s.size()-1;
    f[0][0]=1;
    For(i,0,n)
    For(j,0,n){
        f[i+1][j+1]+=f[i][j];
        f[i+1][max(j-1,0ll)]+=f[i][j]*(1+(j>0));
        f[i+1][j+1]%=Mod;
        f[i+1][max(j-1,0ll)]%=Mod;
    }
    cout<<f[n][m];
}
```

---

## 作者：hjqhs (赞：0)

这题只跟 $n$ 有关系，，，  
设 $f_{i,j}$ 代表敲了键盘 $i$ 次，已经匹配了 $j$ 个字符的方案数量。  
边界为 $f_{0,0}=1$。答案是 $f_{n,len_{st}}$。  
如果没有敲退格键，则 $f_{i,j} \gets f_{i-1,j-1}(j \ge 1)$。  
如果敲了退格键，则 $f_{i,j} \gets f_{i,j}+f_{i-1,j+1}\times 2$。  
然后做完了。
```cpp
#include<bits/stdc++.h>
// #define int long long
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define per(i,a,b) for(int i=b;i>=a;--i)
#define pv(i,p) for(int i=0;i<p.size();++i)
#define ptc putchar
#define il inline
#define reg register
// #define push_back pb
#define mp make_pair
#define eb emplace_back
// #define ret; return 0;
using namespace std;
const int N=5005;
const int MOD=1000000007;
const int INF=0x3f3f3f3f;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
int Max(int a,int b){return a>b?a:b;}
int MAX(int a,int b,int c){return Max(a,Max(b,c));}
int Min(int a,int b){return a<b?a:b;}
int MIN(int a,int b,int c){return Min(a,Min(b,c));}
void Swap(int&a,int&b){int tmp=a;a=b;b=tmp;}
int read(){
  int x=0,f=1;
  char ch=getchar();
  while(ch<'0'||ch>'9'){
    if(ch=='-')f=-1;
    ch=getchar();
  }
  while(ch>='0'&&ch<='9'){
    x=(x<<3)+(x<<1)+(ch^48);
    ch=getchar();
  }
  return x*f;
}
int n,f[N][N],sl;
string s;
void solve(){
  cin>>n>>s;
  sl=s.size();
  f[0][0]=1;
  for(int i=1;i<=n;++i){
    for(int j=0;j<=i;++j){
      f[i][j]=(f[i-1][Max(j-1,0)]%MOD+f[i-1][j+1]*2%MOD)%MOD;
    }
  }
  cout<<f[n][sl];
}
signed main(){
  // freopen(,,stdin);
  // freopen(,,stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  solve();
  return 0;
}
```

---

## 作者：DPseud (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc059_d)

这是一道动态规划题。

首先确定状态，我们知道题目中有两个量：$n$ 和 $s$，因此，我们会有一个初步思想：$dp(i,j)$ 表示修改 $i$ 个数后匹配了 $s$ 中的 $j$ 个数时的方案数。

然后有两点显然：

1. $s$ 的内容是无关紧要的，因为每个数位是 $\verb!0!$ 或者 $\verb!1!$ 其实都不过是字符，真正与方程挂钩的仅仅是存在字符和删除字符。

2. 既然是方案数，就不要像本人刚开始一样蠢到用 $\max$ 了，应为加起来。

知道了以上两点后，我们能根据打 $\verb!0!$ 或 $\verb!1!$ 或退格的情况，把两种情况加起来。

1. 打数字时，无论是哪种数字，都可以直接从 $dp(i-1,j-1)$ 转移过来，这点显然。

2. 打退格时，很明显从 $dp(i-1,j+1)$ 转移，但是我们这样想：删掉的字符可能是 $\verb!0!$ 或 $\verb!1!$，并且删除什么字符都不影响接下来的匹配，所以要使用 $dp(i-1,j+1)\times 2$。

但是第一种情况中 $j-1$ 是可能出现越界的，这是因为我们遍历时 $0\leq j\leq i$，需要特判一下，但是不能没有从 $j=0$ 的转移过来，否则样例都过不了。

代码：

```cpp
#include<bits/stdc++.h>
#define mod 1000000007 
using namespace std;
int main()
{
	static long long n,dp[6666][6666];
	cin>>n;
	string s;
	cin>>s;
	dp[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=i;j++)
		{
			dp[i][j]=dp[i-1][j+1]*2%mod;
			dp[i][j]=(dp[i][j]+dp[i-1][max(j-1,0)])%mod;
		}
	}
	cout<<dp[n][s.length()];
	return 0;
}
```


---

## 作者：比利♂海灵顿 (赞：0)

# ARC059F Unhappy Hacking

看到这里的题解都是二维 DP，我是从卡特兰数的方面考虑的此题。

如果这个题的模数换成 $998244343$ 或是别的 NTT 模数，那么复杂度就可以通过分治 FFT 做到 $O(n\log^2 n)$。可惜换不得。但是貌似存在某神奇的多项式科技任意模数 NTT，那么理论上还是可以 $O(n\log^2 n)$ 的。

但是本题解只对 $O(n^2)$ 的做法进行实现。

[AtCoder 传送门](https://atcoder.jp/contests/arc059/tasks/arc059_d)

前置知识: 可以在[这里](https://www.luogu.com.cn/blog/Wild-Donkey/zroi-day11-day20-bi-ji) Day19 的 C 题笔记中找到卡特兰数的推导和变形，也可以查看 [Wiki](https://zh.wikipedia.org/zh-hans/%E5%8D%A1%E5%A1%94%E5%85%B0%E6%95%B0)。

## 简要题意

给一个 0/1 串 $S$，每次可以选择在末尾插入一个 `0` 或 `1`，或删除最后一个字符。求进行 $n$ 次操作之后得到 $S$ 的方案数。

## 无效退格

注意到一个比较头疼的事情是在没有字符的时候按退格，这样的退格不会删除任何东西，且一旦出现无效退格，一定不存在任何字符。(废话) 所以可以认为是一个新的子问题。

设操作 $i$ 次，操作 $i$ 是无效退格的方案数为 $f_i$。

为了求这个 $f$，我们需要计算从 $0$ 个字符开始，不断进行操作，但是禁止无效退格。进行 $2i$ 次操作的方案数为 $g_i$。这样会打出 $i$ 个字符，并且这 $i$ 个字符会被 $i$ 个有效退格删掉。这个问题等价于将 `0` 和 `1` 压入栈并且弹出。可以看出 $g_i$ 等于卡特兰数第 $i$ 项乘 $2^i$。$2^i$ 枚举了每个插入的字符是 `0` 还是 `1`，卡特兰数第 $1$ 项枚举了每个退格的时刻。

求出了 $g$，我们枚举倒数第二次无效空格的时刻 $i - 1 - 2j$，则 $f_i$ 可以表示为:

$$
f_i = \sum_{j = 0}^{\lfloor \frac {i - 1}2 \rfloor} f_{i - 1 - 2j}g_j
$$

这是卷积的形式，我们可以使得 $g'_{2i + 1} = g_i$，然后让 $g'$ 其余项为 $0$，那么式子就变成:

$$
f_i = \sum_{j = 1}^{i} f_{i - j}g'_{j}
$$

可以用分治 FFT 优化到 $O(n\log^2 n)$，所以这个题理论上是可以 $O(n \log^2 n)$ 的。有需要的人可以拿去出个加强版，把模数换成 $998244353$ 然后把 $n$ 开到 $10^5$ 什么的。

我们枚举最后一个无效退格的时刻 $x$。那么相当于是在禁止无效退格的情况下用 $n - x$ 次操作得到目标串。所以我们枚举 $x$，对不同的 $x$ 算 $n - x$ 答案即可。

## 退格有效的情况

接下来考虑禁止无效退格，用 $x$ 次操作凑出目标串的方案数。

设 $S$ 的长度为 $m$，那么我们知道会有 $\dfrac{x + m}2$ 次插入操作，剩下的是删除操作。所以需要 $x$，$m$ 奇偶性相同。否则方案数为 $0$。

我们先不管 $x$ 次操作后的串是什么，求出只存在 `0` 的情况下，$x$ 次操作后留下 $m$ 个 `0` 的方案数。显然是卡特兰数的变形，也就是 $\dbinom x{\frac {x + m}2} - \dbinom x{\frac {x + m}2 + 1}$。

最后我们考虑既有 `0` 也有 `1` 的情况。对于被删除了的 $\dfrac {x - m}{2}$ 次插入，我们允许它们是任何数字，剩下的 $m$ 个未被删除的插入，它们必须是目标位置的数字。因此只要在原来只有 `0` 的方案数的基础上乘以 $2^{\frac{x - m}2}$ 即可。

## 代码实现

这里没有对分治 FFT 进行任意模数 NTT 的实现。只写了暴力卷积:

```cpp
const unsigned long long Mod(1000000007);
unsigned long long Fac[5005], Inv[5005], Two[5005], g[5005], f[5005], Ans(0);
unsigned m, n;
inline unsigned long long Inver(unsigned long long x) {
  unsigned long long Rt(1);
  unsigned y(1000000005);
  while (y) { if(y & 1) Rt = Rt * x % Mod; x = x * x % Mod, y >>= 1;}
  return Rt;
}
inline unsigned long long Solve(unsigned x) {
  unsigned Typ((x + m) >> 1);
  unsigned long long A(Two[Typ - m]), B(Inv[Typ] * Inv[x - Typ] % Mod);
  A = A * Fac[x] % Mod;
  B = B * A % Mod, Typ = x - Typ;
  if(Typ) --Typ, A = A * Inv[Typ] % Mod, A = A * Inv[x - Typ] % Mod;
  else A = 0;
  return Mod + B - A;
}
signed main() {
  n = RD(), f[0] = g[0] = Fac[0] = Two[0] = 1;
  while (getchar() >= '0') ++m;
  for (unsigned i(1); i <= n; ++i) Fac[i] = Fac[i - 1] * i % Mod;
  Inv[n] = Inver(Fac[n]);
  for (unsigned i(n); i; --i) Inv[i - 1] = Inv[i] * i % Mod;
  for (unsigned i(1); i <= n; ++i) Two[i] = (Two[i - 1] << 1), Two[i] -= (Two[i] >= Mod) ? Mod : 0;
  for (unsigned i(n >> 1); i; --i)
    g[i] = (((Fac[i << 1] * Inv[i + 1] % Mod) * Inv[i] % Mod) * Two[i]) % Mod;
  for (unsigned i(1); i <= n; ++i) for (unsigned j((i - 1) >> 1); ~j; --j)
    f[i] = (f[i] + f[i - 1 - (j << 1)] * g[j]) % Mod;
  for (unsigned i(n - m); ~i; --i) if(!(((n - i) ^ m) & 1))
    Ans = (Ans + f[i] * Solve(n - i)) % Mod;
  printf("%llu\n", Ans);
  return Wild_Donkey;
}
```

---

