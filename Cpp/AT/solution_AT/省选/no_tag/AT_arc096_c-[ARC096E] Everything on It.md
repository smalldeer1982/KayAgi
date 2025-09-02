# [ARC096E] Everything on It

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc096/tasks/arc096_c

ラーメン店「高橋屋」のメニューは基本的には「ラーメン」の一つだけですが、$ N $ 種類のトッピングも提供されています。客がラーメンを注文するとき、それぞれの種類のトッピングを「乗せる」か「乗せない」かを選ぶことができます。乗せるトッピングの数に制限はなく、すべてのトッピングを乗せることも、トッピングを一つも乗せないこともできます。つまり、トッピングの組み合わせを考慮すると $ 2^N $ 通りのラーメンを注文できます。

赤木さんが高橋屋に入店しました。彼女は、次の二つの条件をともに満たすようにラーメンを何杯か注文しようと考えています。

- トッピングの組み合わせがまったく同じラーメンを複数杯注文しない。
- $ N $ 種類のトッピングそれぞれが、注文したラーメンのうち $ 2 $ 杯以上に乗っている。

$ N $ と素数 $ M $ が与えられます。これらの条件を満たすようなラーメンの組み合わせの数を $ M $ で割ったあまりを求めてください。ラーメンの順番は考慮しません。また、赤木さんは極限の空腹状態にあるため、ラーメンを何杯注文しても問題ありません。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 3000 $
- $ 10^8\ \leq\ M\ \leq\ 10^9\ +\ 9 $
- $ N $ は整数である。
- $ M $ は素数である。

### 部分点

- $ N\ <\ =\ 50 $ を満たすテストセットに正解すると、$ 600 $ 点が与えられる。

### Sample Explanation 1

$ 2 $ 種類のトッピングを A, B とします。注文できるラーメンは「トッピングなし」「A 乗せ」「B 乗せ」「A, B 乗せ」の $ 4 $ 通りです。条件を満たすラーメンの組み合わせは次の $ 2 $ 通りです。 - 「A 乗せ」「B 乗せ」「A, B 乗せ」の $ 3 $ 杯 - 全通りのラーメン $ 1 $ 杯ずつ、合計 $ 4 $ 杯

### Sample Explanation 2

$ 3 $ 種類のトッピングを A, B, C とします。入出力例 1 で述べた $ 4 $ 通りのラーメンに加えて、それらに C を付け足した $ 4 $ 通りのラーメンも注文できます。条件を満たすラーメンの組み合わせは $ 118 $ 通りありますが、そのうちのいくつかを挙げます。 - 「A, B 乗せ」「A, C 乗せ」「B, C 乗せ」の $ 3 $ 杯 - 「トッピングなし」「A 乗せ」「A, B 乗せ」「B, C 乗せ」「A, B, C 乗せ」の $ 5 $ 杯 - 全通りのラーメン $ 1 $ 杯ずつ、合計 $ 8 $ 杯 なお、「『A 乗せ』『B 乗せ』『A, B 乗せ』の $ 3 $ 杯」は条件を満たしません。C がどのラーメンにも乗っていないためです。

### Sample Explanation 3

組み合わせの数を $ M $ で割ったあまりを出力することをお忘れなく。なお、以上の三つの入力例は、部分点のためのテストセットに含まれます。

### Sample Explanation 4

この入力例は、部分点のためのテストセットに含まれません。

## 样例 #1

### 输入

```
2 1000000007```

### 输出

```
2```

## 样例 #2

### 输入

```
3 1000000009```

### 输出

```
118```

## 样例 #3

### 输入

```
50 111111113```

### 输出

```
1456748```

## 样例 #4

### 输入

```
3000 123456791```

### 输出

```
16369789```

# 题解

## 作者：81179332_ (赞：23)

考虑容斥。

设 $F(i)$ 表示至少有 $i$ 个数的出现次数不多于 $1$ 次。

则答案为：
$$\sum\limits_{i=0}^n(-1)^iF(i)$$
枚举 $j$,表示将这 $i$ 个数划分到 $j$ 个非空集合中。但是由于限制是不多于一次，意味着可能存在一些数没有出现过。

如何解决呢？我们考虑新加入一个集合当做“垃圾堆”，该集合中的数即为没有出现的数。但是还有一个问题：“垃圾堆”可能为空。所以我们新加入一个数字 $0$，$0$ 所在集合即为垃圾堆。

于是将 $i$ 个数划分到 $j$ 个非空集合的方案数为 $\begin{Bmatrix}
i+1\\j+1
\end{Bmatrix}$。

然后考虑剩下来的 $n-i$ 个数可以形成 $2^{n-i}$ 个集合。我们可以枚举这些集合有没有被选择，那么方案数就是 $2^{2^{n-i}}$。最后，剩下的 $n-i$ 个数还可以往之前的 $j$ 个集合里面放，所以再乘上 $(2^{n-i})^j$。

于是答案为：
$$\sum\limits_{i=0}^n(-1)^iF(i)$$
$$=\sum\limits_{i=0}^n(-1)^i\begin{pmatrix}n\\i\end{pmatrix}\sum\limits_{j=0}^i\begin{Bmatrix}i+1\\j+1\end{Bmatrix}\cdot 2^{2^{n-i}}\cdot (2^{n-i})^j$$
$$=\sum\limits_{i=0}^n(-1)^i\cdot 2^{2^{n-i}}\begin{pmatrix}n\\i\end{pmatrix}\sum\limits_{j=0}^i\begin{Bmatrix}i+1\\j+1\end{Bmatrix}\cdot (2^{n-i})^j$$

```cpp
#include<cctype>
#include<cstdio>
using namespace std;
#define getchar() (SS == TT && (TT = (SS = BB) + fread(BB,1,1 << 15,stdin),TT == SS) ? EOF : *SS++)
char BB[1 << 15],*SS = BB,*TT = BB;
inline int read()
{
	register int x = 0;
	register char ch = getchar();
	for(;!isdigit(ch);ch = getchar());
	for(;isdigit(ch);ch = getchar())
		x = x * 10 + (ch ^ 48);
	return x;
}
inline void print(int x)
{
	char ch = x % 10 + '0';
	if(x > 9)
		print(x / 10);
	putchar(ch);
}

int mod;
inline int add(int a,int b)
{
	a += b;
	return a >= mod ? a - mod : a;
}
inline int qpow(long long a,int b,int p = mod)
{
	register long long ans = 1;
	while(b)
	{
		if(b & 1) ans = ans * a % p;
		a = a * a % p,b >>= 1;
	}
	return ans;
}

const int N = 3010;
int n;
long long s[N][N],c[N][N],ans;

inline void init()
{
	c[0][0] = s[0][0] = 1;
	for(register int i = 1;i <= n + 1;i++)
	{
		c[i][0] = 1;
		for(register int j = 1;j <= i;j++)
			s[i][j] = (s[i - 1][j - 1] + s[i - 1][j] * j) % mod,
			c[i][j] = add(c[i - 1][j - 1],c[i - 1][j]);
	}
}

int main()
{
	n = read(),mod = read();
	init();

	for(register int i = 0;i <= n;i++)
	{
		register long long _2 = qpow(2,n - i);

		long long mul = i & 1 ? mod - 1 : 1,res = 0;
		mul = mul * c[n][i] % mod * qpow(2,qpow(2,n - i,mod - 1)) % mod;

		register long long _2j = 1;
		for(register int j = 0;j <= i;j++)
			res = (res + s[i + 1][j + 1] * _2j) % mod,
			_2j = _2j * _2 % mod;

		ans = (ans + res * mul) % mod;
	}
	print(ans);
}
```

---

## 作者：bikuhiku (赞：7)


看到这种计数题，觉得很难正推的，多半是反推，还多半沾点容斥。

***

我们考虑 $dp_i$ 表示有已确定的 $i$ 种元素不合法，其它 $n-i$ 种元素不确定（任意）的方案数，那么可以容斥一下，答案即为：

$$ans = \sum\limits_{i = 0}^{n}(-1)^n \times \binom{n}{i} \times dp_i$$

其中 $\binom{n}{i}$ 就表示从 $n$ 碗面中选择了 $i$ 种。

***

既然 $dp_i$ 中的元素被鲜明地分为了两类，设 $f_i$ 表示确定的 $i$ 种不合法元素的方案数，则有：

$$dp_i = f_i \times 2^{2^{n-i}}$$

其中 $2^{2^{n-i}}$ 意即：$n-i$ 种元素构成了 $2^{n-i}$ 个集合，而这些集合又作为元素构成了 $2^{2^{n-i}}$ 个集合。

注意一下求解 $2^{2^{n-i}}\bmod p$ 请用欧拉定理，变为求解 $2^{2^{n-i}\bmod \varphi(p)}\bmod p$。

***

压力来到了求 $f_i$ 上。我们考虑这 $i$ 个元素分别放到了哪些集合里，设 $g_{i,j}$ 表示 $i$ 个元素放到了 $j$ 个集合里的方案数，则又有：

$$f_i = \sum\limits_{j = 0}^{n}\left(2^{n-i}\right)^{j}\times g_{i,j}$$

即先枚举这 $i$ 个元素放到哪些集合里。

***

怎么求 $g_{i,j}$？可以考虑递推：

$$g_{i,j} = g_{i-1,j-1}+(j+1)\times g_{i-1,j}$$

1. 从 $g_{i-1,j-1}$ 转移：剩下的一种元素必须加到一个新的集合里；

2. 从 $g_{i-1,j}$ 转移：无论把这种元素加到那个集合里、甚至不加入任一个集合都可以。

似乎推组合数、斯特林数时也有类似的式子，也可以说是递推的一个技巧吧。

***

那就开始码代码吧。

```cpp
#include <iostream>
const int N = 3005;
int n, mod;
int C[N][N], g[N][N], ans;
int quick_pow(int _a,int _n,int _p = mod) {
	int _res = 1;
	while(_n) {
		if(_n&1) 
			_res = 1ll*_res*_a%_p;
		_a = 1ll*_a*_a%_p;
		_n >>= 1;
	}
	return _res;
}
int main() {
	scanf("%d %d",&n,&mod);
	for(int i = 0;i <= n;++i) {
		g[i][0] = C[i][0] = 1;
		for(int j = 1;j <= i;++j) {
			g[i][j] = (g[i-1][j-1]+(j+1LL)*g[i-1][j])%mod;
			C[i][j] = (C[i-1][j]+C[i-1][j-1])%mod;
		}
	}
	for(int i = 0;i <= n;++i) {
		int f = 0, pass = 1;
		int t_n = quick_pow(2,n-i);
		for(int j = 0;j <= i;++j) {
			f = (f+1ll*g[i][j]*pass)%mod;
			pass = 1ll*pass*t_n%mod;
		}
		ans = (ans+1ll*f*(i&1 ? mod-C[n][i] : C[n][i])%mod*quick_pow(2,quick_pow(2,n-i,mod-1)))%mod;
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：Celtic (赞：4)

发现这个所有数出现次数都大于等于 $2$ 非常的不好搞。

考虑容斥，设 $f_i$ 表示钦定 $i$ 个数出现次数不大于 $1$ ，其他数随意的方案数。

那么答案就是 $\sum_{i=0}^{n} (-1)^{i} f_i$。

考虑 $f_i$ 怎么求，首先是选出 $i$ 个数的方案数 $\binom n i $。

然后可以发现只有其他数的集合的方案非常算，就是 $2^{2^{n-i}}$ ，这个考虑 $n-i$ 个数形成的集合一共有 $2^{n-i}$ 个，每个集合有出现和不出现两种状态，乘法原理很容易得出。

考虑怎么计算包含被钦定的数的集合的方案数，发现假如所有数都必须出现就是第二类斯特林数，所以可以考虑类似于斯特林数的 DP 。

具体就是设 $g_{i,j}$ 表示 $i$ 个最多出现 $1$ 次的数放入恰好 $j$ 个集合（不能为空）的方案数。

有转移方程 $g_{i,j}=g_{i-1,j-1}+(j+1)g_{i-1,j}$ （其实就是每个数比第二类斯特林数多一种情况就是不放到任何集合，直接加上一个 $g_{i-1,j}$ 即可）。

然后就能得出 $f_i=\sum_{j=0}^{i} 2^{j(n-i)}g_{i,j}$，其中 $2^{j(n-i)}$ 表示这 $j$ 个集合中还可以有没被钦定的数，每个有 $2^{n-i}$ 种选择。

预处理 $2^k$ ，复杂度 $O(n^2)$。

注意 $2^{2^{n-i}}$ 要用欧拉定理求。

$\sf{Code}$

```cpp
#include<bits/stdc++.h>
#define N 2001001
#define MAX 5005
#define infe 1e18
using namespace std;
typedef long long ll;
typedef double db;
inline void read(ll &ret)
{
    ret=0;char c=getchar();bool pd=false;
    while(!isdigit(c)){pd|=c=='-';c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
    ret=pd?-ret:ret;
    return;
}
ll n,g[MAX][MAX],f[MAX],val1[N],val[N],c[MAX][MAX],ans;
int p;
inline ll qpow(ll a,ll b)
{
	ll ret=1;
	while(b)
	{
		if(b&1)
			ret*=a,ret%=p;
		b>>=1;
		a*=a;
		a%=p;
	}
	return ret;
}
signed main()
{
	read(n);
	cin>>p;
	val1[0]=val[0]=1;
	c[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		c[i][0]=1;
		for(int j=1;j<=i;j++)
		{
			c[i][j]=c[i-1][j-1]+c[i-1][j];
			if(c[i][j]>=p)
				c[i][j]-=p;
		}
	}
	for(int i=1;i<=n;i++)
	{
		val1[i]=val1[i-1]<<1;
		if(val1[i]>=p-1)
			val1[i]-=p-1;
	}
	for(int i=1;i<=n;i++)
	{
		val[i]=val[i-1]<<1;
		if(val[i]>=p)
			val[i]-=p;
	}
	g[0][0]=1;
	f[0]=1;
	for(int i=1;i<=n;i++)
	{
		g[i][0]=f[i]=1;
		ll now=val[n-i];
		for(int j=1;j<=n;j++)
		{
			g[i][j]=g[i-1][j-1]+g[i-1][j]*(j+1)%p;
			if(g[i][j]>=p)
				g[i][j]-=p;
			f[i]+=g[i][j]*now%p;
			if(f[i]>=p)
				f[i]-=p;
			now*=val[n-i];
			now%=p;
		}
	}
		
	for(int i=0;i<=n;i++)
	{
		if(i&1)
		{
			ans-=f[i]*qpow(2,val1[n-i])%p*c[n][i]%p;
			if(ans<0)
				ans+=p;
		}
		else
		{
			ans+=f[i]*qpow(2,val1[n-i])%p*c[n][i]%p;
			if(ans>=p)
				ans-=p;
		}
	}
	printf("%lld\n",ans);
	exit(0);
}
```

---

## 作者：TempestMiku (赞：4)

# [题目传送门](https://www.luogu.com.cn/problem/AT_arc096_c)

今天模拟赛考了这道题，然后保龄了。

## 思路

- 首先可以对第二个限制做**二项式反演**：

设 $f[i]$ 为钦定 $i$ 种配料出现次数小于等于 $1$ 的方案数。

那么就有 $ans=\sum_{i=0}^{n}{(-1)^{i}}{C_n^i}{f[i]}$。

- 考虑计算 $f[i]$：

首先枚举出现次数小于等于 $1$ 次的配料中有几个配料出现了和有几碗面中出现了这些配料，设有 $j$ 个配料出现在了 $k$ 碗面中。

那么容易想到**第二类斯特林数**。



>第二类斯特林数 $\operatorname{S2}(n,m)$ 表示的是把 $n$ 个不同元素划分到 $m$ 个集合的方案数。表示为 $n \brace m$。


将 $j$ 个不同元素划分到 $k$ 个集合中，即为 $k \brace j$。

斯特林数处理的是只能是非空集合，所以先考虑所有数都加入集合的情况，即为$k \brace j $，然后考虑有数没有加入集合的情况，我们可以加入一个第 $k+1$ 集合，把 $1$ 到 $k$ 都不放元素的元素加入这个集合中，然后每个集合都可以是第 $k+1$ 个集合，所以方案数为 ${(j+1)}\times {{k+1} \brace j }$。

另外，这 $k$ 种面的其他配料可以随便加而不用担心出现重复的碗，方案数即为 $2^{{n-i}^{k}}$。


题目中说有 $n$ 种元素,总共有 $2^{n}$ 种集合，去掉已经钦定的 $i$ 种元素之后，剩下 $2^{n-i}$ 种集合。对于 $i$ 个元素之外的 $n-i$ 个数组成的 $2^{n-i}$ 个集合可以选也可以不选，所以是 $2^{2^{n-i}}$ 种方案。 这里有一个细节就是幂次的处理需要用费马小定理。

- 所以答案表达式即为：

$$Ans=\sum_{i=0}^{n}{(-1)^i}{ \operatorname{C}_n^i}\times 2^{2^{n-i}} \sum_{j=0}^i( {i \brace j} + (j+1)\times {{j+1} \brace {i}} )\times(2^{n-i})^j$$

预处理出斯特林数后 $O(n^2+logP)$ 计算即可。


- 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace Testify{
    inline int read(){
        int f(1),x(0);
        char ch=getchar();
        for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
        for(;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
        return f*x;
    }
    inline void Write(int x){
        if(x>9) Write(x/10);
        putchar(x%10+'0');
    }
    inline void write(int x){
        if(x<0) putchar('-'),x=-x;
        Write(x);
        putchar('\n');
    }
}
using namespace Testify;
// const int mod=1e9+7;
int mod;
const int N=5555;
int n,m,fac[N],inv[N],S[N][N];
inline int qpow(int a,int b,int mod){
    int res=1;
    while(b){
        if(b&1) res=res*a%mod;
        b>>=1;
        a=a*a%mod;
    }
    return res;
}
inline int C(int n,int m){
    if(n<m) return 0;
    return ((fac[n]%mod*inv[n-m]%mod)%mod*inv[m]%mod)%mod;
}
signed main(void){
    n=read(),mod=read();
    fac[0]=inv[0]=1;
    for(register int i=1;i<=n;i++){
        fac[i]=fac[i-1]*i%mod;
        inv[i]=inv[i-1]*qpow(i,mod-2,mod)%mod;
    }
    S[0][0]=1;
    for(register int i=1;i<=n+1;i++){//加一是因为下面可能用到j+1
        for(register int j=1;j<=i;j++){
            S[i][j]=(S[i-1][j-1]+S[i-1][j]*j%mod)%mod;
        }
    }
    int Tempestissimo(0);
    for(register int i=0;i<=n;i++){//枚举第i个元素
        int tmp(0);
        for(register int j=0;j<=i;j++){//枚举划分k个集合
            tmp=((tmp+(S[i][j+1]*(j+1)+S[i][j])%mod*(qpow(2,(n-i)*j,mod))%mod))%mod;
        }
        tmp=(tmp*qpow(2,qpow(2,n-i,mod-1),mod)%mod*C(n,i)%mod)%mod;//注意费马小定理
        Tempestissimo=(Tempestissimo+qpow(-1,i,mod-1)*tmp)%mod;
    }
    write((Tempestissimo%mod+mod)%mod);
    return 0;
}
```



---

## 作者：do_while_true (赞：2)

考虑将第二个容斥掉，枚举有 $1\sim i$ 出现次数 $\leq 1$ 次，剩余的无限制，假设其方案为 $f(i)$．

那么答案就是 $\sum f(i)(-1)^i\binom{n}{i}$．

考虑 $f(x)$ 怎么算，令 $y=n-x$，首先考虑不包含 $1\sim x$ 的子集一共有 $2^{2^y}$ 个，然后再考虑包含 $1\sim x$ 的子集，相当于将 $1\sim x$ 分成若干个不同的集合，每个集合从 $2^y$ 个集合中找一个集合，与其的并集构成一个新的集合。

令 $s_{i,j}$ 为将 $1\sim i$ 分成若 $j$ 个不同的集合的方案数（第二类斯特林数），枚举有 $1\sim x$ 中出现了的有 $i$ 个，一共分成 $j$ 个集合，那么就有：

$$
\begin{aligned}
f(x)&=\sum_i\sum_j s_{i,j}({2^y})^j2^{2^y}\binom{x}{i}
\\
&=2^{2^y}\sum_j (2^y)^j\sum_i \binom{x}{i}s_{i,j}
\end{aligned}
$$

考虑后面那个求和号的组合意义，就是从 $x$ 个元素中选出 $i$ 个元素，再将这 $i$ 个元素划分成 $j$ 个集合。如果把没有选出的元素也看成一个集合，那么其就是 $x$ 个元素划分成 $(j+1)$ 个集合，其中有一个集合有标号且可空。所以：

$$
f(x)=2^{2^y}\sum_j (2^y)^j((j+1)s_{x,j+1}+s_{x,j})
$$

要注意 $2^{2^y}$ 计算时要将指数模 $M-1$．

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n';
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n';
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
int mod;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
int qpow(int x,int y,int mod=mod){
	int s=1;
	while(y){
		if(y&1)s=1ll*s*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return s;
}
const int N=3010;
int n;
int S[N][N],C[N][N];
int solve(int x){
	int y=n-x,t=qpow(2,y),tmp=1;
	int s=0;
	for(int j=0;j<=x;j++){
		cadd(s,1ll*tmp*add(1ll*(j+1)*S[x][j+1]%mod,S[x][j])%mod);
		tmp=1ll*tmp*t%mod;
	}
	return 1ll*s*qpow(2,qpow(2,y,mod-1))%mod;
}
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	read(n,mod);
	S[0][0]=C[0][0]=1;
	for(int i=1;i<=n+1;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++){
			C[i][j]=add(C[i-1][j-1],C[i-1][j]);
			S[i][j]=add(S[i-1][j-1],1ll*j*S[i-1][j]%mod);
		}
	}
	int ans=0;
	for(int i=0;i<=n;i++){
		if(i&1)cdel(ans,1ll*C[n][i]*solve(i)%mod);
		else cadd(ans,1ll*C[n][i]*solve(i)%mod);
	}
	cout << ans << '\n';
    #ifdef do_while_true
		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：_SeeleVollerei_ (赞：2)

为啥因为这场 ARC 没有 AB 洛谷就直接平移这题搬成 C 了啊。

第一反应是直接上 dp ，然后发现假了。

第一个限制和没有一样，直接忽略，考虑怎么处理第二个限制。

考虑容斥，设至少有 $i$ 个数出现了少于 2 次的方案数为 $g_i$ ，则答案为 $\sum\limits_{i=0}^n(-1)^ig_i$ ，考虑怎么求 $g_i$ 。

对于这 $i$ 个数以外的 $n-i$ 个数所构成的 $2^{n-i}$ 个集合可以随意选或不选，所以这部分的贡献为 $2^{2^{n-i}}$ ，一个细节是幂的幂要用费马小定理解决。选 $i$ 个数的方案为 $\binom{n}{i}$ 。

设 $f_{i,j}$ 表示把 $i$ 个不同的数分成 $j$ 组，同时有的数可以扔掉的方案数，然后对于每一组，可以随意加减其他的 $n-i$ 个数，所以这部分的贡献为 $\sum\limits_{j=0}^if_{i,j}\times(2^{n-i})^j$ 。问题变成了求 $f_{i,j}$ 。

这个 $f_{i,j}$ 还是蛮好求的，有点像斯特林数，~~哪一类我忘了。~~

考虑如何从 $f_{i-1}$ 转移，一种是第 $i$ 个数自己新开一组，所以 $f_{i,j}\leftarrow f_{i-1,j-1}$ 。

一种是把第 $i$ 个数直接扔掉，也就是一个都不选，所以 $f_{i,j}\leftarrow f_{i-1,j}$ 。

还有一种是把第 $i$ 个数在之前的组里仍选一个放进去，所以 $f_{i,j}\leftarrow f_{i-1,j}\times j$ 。

然后就做完了。

https://atcoder.jp/contests/arc096/submissions/32318901

---

## 作者：tzc_wk (赞：2)

[Atcoder 题面传送门](https://atcoder.jp/contests/arc096/tasks/arc096_c) & [洛谷题面传送门](https://www.luogu.com.cn/problem/AT4119)

简单题，由于这场 arc 的 F 是 jxd 作业而我不会做，所以只好来把这场的 E ~~水~~掉了。

我们记 $f(i)$ 为钦定 $i$ 个元素出现次数不超过一次，剩余放任自流（cmd_blk 内味）的方案数，再记 $g(i)$ 为恰好 $i$ 个元素出现次数不超过一次的方案数，那么有 $f(i)=\sum\limits_{j=i}^ng(j)\dbinom{j}{i}$，二项式反演一下可得 $g(i)=\sum\limits_{j=i}^nf(j)\dbinom{j}{i}(-1)^{j-i}$，我们要求的答案即为 $g(0)=\sum\limits_{i=0}^n(-1)^if(i)$。

考虑怎样求 $f(i)$，首先我们需钦定 $i$ 个元素出现不超过一次，方案数为 $\dbinom{n}{i}$，我们枚举这 $i$ 个元素划分入多少个集合，设为 $j$，根据组合意义，可能会有一些元素出现了一次，那我们就新建一个集合 $S_0$ 表示出现 $0$ 次的数的集合，并新建一个 $0$ 号元素，强制令 $0\in S_0$，这样等价于将 $i+1$ 个元素放入 $j+1$ 个非空集合，其中与 $0$ 号元素被划分在一个集合的元素就是出现一次的元素，这样可得方案数为 $\begin{Bmatrix}i+1\\j+1\end{Bmatrix}$。

接下来考虑剩下 $n-i$ 个元素，它们可以形成 $2^{n-i}$ 个集合，由于剩下的元素放任自流，这 $2^{n-i}$ 个集合每个又有选或者不选两种方案，方案数为 $2^{2^{n-i}}$，另外剩余 $n-i$ 个元素每个又可以放入原来 $j$ 个非空集合中，每个元素是否放入每个集合都有 $2$ 种选择，因此每个元素可选择的方案数为 $2^j$，总贡献为 $2^{j\times(n-i)}$。

因此 $f(i)=\sum\limits_{j=0}^i\dbinom{n}{i}\begin{Bmatrix}i+1\\j+1\end{Bmatrix}·2^{2^{n-i}}·2^{j\times(n-i)}$，简单算一下就好了，$n^2\log n$ 的做法显然，不过似乎过不去？稍微有点脑子的人也能优化到 $n^2$ 罢……

```cpp
const int MAXN=3e3;
int n,mod,s[MAXN+5][MAXN+5],c[MAXN+5][MAXN+5];
void init(int n){
	s[0][0]=c[0][0]=1;
	for(int i=1;i<=n;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
			s[i][j]=(s[i-1][j-1]+1ll*s[i-1][j]*j)%mod;
		}
	}
}
int qpow(int x,int e,int mod){
	int ret=1;
	for(;e;e>>=1,x=1ll*x*x%mod) if(e&1) ret=1ll*ret*x%mod;
	return ret;
}
int main(){
	scanf("%d%d",&n,&mod);init(n+1);int ans=0;
	for(int i=0;i<=n;i++){
		int sum=0,pww=qpow(2,qpow(2,n-i,mod-1),mod),bs=qpow(2,n-i,mod),pw=1;
		for(int j=0;j<=i;j++,pw=1ll*pw*bs%mod){
			sum=(sum+1ll*s[i+1][j+1]*c[n][i]%mod*pww%mod*pw%mod)%mod;
		}
		if(i&1) ans=(ans-sum+mod)%mod;
		else ans=(ans+sum)%mod;
	} printf("%d\n",ans);
	return 0;
}
```



---

## 作者：Arghariza (赞：1)

~~为啥这ARC这么毒瘤。~~

题目答案无法简单统计，于是考虑容斥，令 $f(x)$ 为 $x$ 个数不合法的方案数，那么答案就是 $\sum\limits_{x=0}^{n}(-1)^xf(x)$。

接下来计算 $f(x)$：

首先选出这 $x$ 个不合法的数，总共 $\dbinom{n}{x}$ 种方案。

然后设把这些数选出来后扔到 $y$ 个集合里，因为不合法，所以每个 $x$ 至多出现一次。每个集合互不相同，不难想到**斯特林数**。

但是斯特林数是必须扔进 $y$ 集合，而根据刚刚的分析，对于每个 $x$，我们可以选择扔或不扔。我们创建一个集合 $y+1$ 表示所有不扔到 $1$ 到 $y$ 集合的 $x$，这样对于每一个 $x$，都必须扔到 $1$ 到 $y+1$ 中。又因为斯特林数要求集合非空，所以对应地创建一个 $x+1$ 的数扔进集合 $y+1$ 中。

于是由斯特林数的组合意义我们知道 **$x$ 个数，扔进 $y$ 个集合，每个 $x$ 至多出现一次，每个集合互不相同**的方案数即 $\begin{Bmatrix}x+1\\y+1\end{Bmatrix}$ 种。

剩下 $n-x$ 个数，每个数选或不选可以组成 $2^{n-x}$ 个集合，往前面的 $y$ 个集合加有 ${(2^{n-k})}^y$ 种方案，每个集合出不出现又可以有 $2^{2^{n-x}}$ 种方案。

所以 $f(x)=\dbinom{n}{x}2^{2^{n-x}}\sum\limits_{y=0}^{i}(2^{n-x})^y\begin{Bmatrix}x+1\\y+1\end{Bmatrix}$。

带入最初的式子，得到：
$$ans=\sum\limits_{x=0}^{n}(-1)^x\dbinom{n}{x}2^{2^{n-x}}\sum\limits_{y=0}^{i}(2^{n-x})^y\begin{Bmatrix}x+1\\y+1\end{Bmatrix}$$

$O(n^2)$ 预处理 $\mathtt{Stirling\ Number}$，$O(n)$ 预处理阶乘、逆元、阶乘逆元，然后就可以 $O(n^2)$ 计算答案啦！

```cpp
// fac为阶乘，inv为逆元，ifac为阶乘的逆元，s为斯特林数
void init(int lim) {
	fac[0] = inv[1] = ifac[0] = s[0][0] = 1;
	for (int i = 2; i <= lim; i++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	for (int i = 1; i <= lim; i++) fac[i] = fac[i - 1] * i % mod, ifac[i] = ifac[i - 1] * inv[i] % mod;
	for (int i = 1; i <= lim; i++) {
		for (int j = 1; j <= i; j++) {
			s[i][j] = (s[i - 1][j - 1] + j * s[i - 1][j]) % mod;
		}
	}
}
// 求组合数
int C(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }
// 快速幂
int ksm(int p, int q, int m) {
	int res = 1;
	while (q) {
		if (q & 1) res = res * p % m;
		p = p * p % m;
		q >>= 1;
	}
	return res;
}

signed main() {
	n = read(), mod = read();
	init(n + 1);
	for (int x = 0; x <= n; x++) {
		int tp = 0, pw = 1, p = ksm(2, n - x, mod);
		for (int y = 0; y <= x; y++) {
			tp = (tp + s[x + 1][y + 1] * pw % mod) % mod;
			pw = pw * p % mod;
		}
		res = ((res + ksm(-1, x, mod) * C(n, x) % mod * ksm(2, ksm(2, n - x, mod - 1), mod) % mod * tp % mod) % mod + mod) % mod;
	}
	write(res);
	return 0;
}
```

P.S:谁说 $O(n^2\log n)$ 过不去...害得我打了一遍 $O(n^2)$。打完才发现竟然能过。

[$\mathtt{Code\ O(n^2\log n)}$](https://www.luogu.com.cn/paste/isdroq26)

---

## 作者：Leasier (赞：1)

前置芝士：[斯特林数](https://oi-wiki.org/math/combinatorics/stirling/)、[欧拉定理](https://oi-wiki.org/math/number-theory/fermat/#_3)

刚刚复习时看到了这道题，就顺便来写一篇题解。

直接算 $\geq 2$ 比较困难，考虑容斥后将其转为 $\leq 1$。

考虑钦定 $i$ 个元素不合法，首先有容斥系数 $(-1)^i C_n^i 2^{2^{n - i}}$。

接下来考虑把这 $i$ 个不合法的元素扔到 $j$ 个集合里去。首先，由于另外 $n - i$ 个元素已经被放任自流，我们可以把它们的子集扔到任意一个集合中，即 $(2^{n - i})^j$；其次，由于我们要做集合划分，容易想到第二类斯特林数，注意到可以有元素不被选择，我们将其扔到一个专用的集合中即可，即 $\{^{i + 1}_{j + 1}\}$（$i + 1$ 是因为第二类斯特林数要求集合非空）。

综上，答案为 $\displaystyle\sum_{i = 0}^n (-1)^i C_n^i 2^{2^{n - i}} \sum_{j = 1}^i (2^{n - i})^j \{^{i + 1}_{j + 1}\}$。

注意 $2^{2^{n - i}}$ 需要使用欧拉定理。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

int c[3007][3007];
ll s2[3007][3007];

inline void init(int n, int mod){
	c[0][0] = 1;
	for (register int i = 1; i <= n; i++){
		c[i][0] = 1;
		for (register int j = 1; j <= i; j++){
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
		}
	}
	s2[0][0] = 1;
	for (register int i = 1; i <= n; i++){;
		for (register int j = 1; j <= i; j++){
			s2[i][j] = (s2[i - 1][j - 1] + j * s2[i - 1][j] % mod) % mod;
		}
	}
}

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

int main(){
	int n, m;
	ll ans = 0;
	scanf("%d %d", &n, &m);
	init(n + 1, m);
	for (register int i = 0; i <= n; i++){
		int j = 0;
		ll x = 0, y = quick_pow(2, n - i, m);
		for (register ll k = 1; j <= i; j++, k = k * y % m){
			x = (x + k * s2[i + 1][j + 1] % m) % m;
		}
		ans = ((ans + (ll)(i % 2 == 0 ? 1 : -1) * x % m * c[n][i] % m * quick_pow(2, quick_pow(2, n - i, m - 1), m) % m) % m + m) % m;
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：xht (赞：0)

> [ARC096E Everything on It](https://atcoder.jp/contests/arc096/tasks/arc096_c)

## 题意

- 有一个包含 $n$ 个元素的集合 $S$。
- 你要选择若干个互不相同的 $S$ 的子集，使得每个元素至少出现两次，求方案数。
- $n \le 3 \times 10^3$，答案对 $M$ 取模。

## 题解

考虑容斥，设 $f(i)$ 表示有至少 $i$ 个数出现了最多一次，则答案为 $\sum_{i=0}^n (-1)^i\binom ni f(i)$。

枚举这 $i$ 个数被划分到 $j$ 个集合中。由于可能有一些数没有出现过，因此我们可以新增一个数 $0$，将这 $i+1$ 个数划分到 $j+1$ 个集合中，与 $0$ 在同一集合的数没有出现过，这部分方案数为 $S_2(i+1, j+1)$。

考虑剩下 $n-i$ 个数，首先存在 $2^{n-i}$ 个集合可选可不选，方案数为 $2^{2^{n-i}}$，然后之前的 $j$ 个中每个集合又可以与这 $2^{n-i}$ 个集合并起来，方案数为 $(2^{n-i})^j$。

因此 $f(i) = \sum_{j=0}^i S_2(i+1,j+1) \cdot 2^{2^{n-i}} \cdot (2^{n-i})^j$，最终的答案可以 $\mathcal O(n^2)$ 计算。

## 代码

```cpp
const int N = 3e3 + 7;
int n;
modint s[N][N], ans;

inline modint f(int i) {
	modint w = (modint)2 ^ (n - i), o = 1, ret = 0;
	for (int j = 0; j <= i; j++, o *= w)
		ret += s[i+1][j+1] * o;
	--P, w = (modint)2 ^ (n - i), ++P;
	return ret * ((modint)2 ^ w.x);
}

int main() {
	rd(n, P);
	init(n);
	s[0][0] = 1;
	for (int i = 1; i <= n + 1; i++)
		for (int j = 0; j <= i; j++)
			s[i][j] = (j ? s[i-1][j-1] : 0) + j * s[i-1][j];
	for (int i = 0; i <= n; i++)
		if (i & 1) ans -= binom(n, i) * f(i);
		else ans += binom(n, i) * f(i);
	print(ans);
	return 0;
}
```

---

## 作者：User_Unauthorized (赞：0)

## 题意
对于集合 ${1,2,\cdots,n}$，求它的子集族中，有多少个满足：

1. 任意两个子集互不相同；
2. $1,2,\cdots,n$ 都在其中至少出现了 $2$ 次。



$n \le 3000$，答案对 $M$ 取模。

## 题解
第一个限制形同虚设，下面着重考虑第二个限制。考虑到第二个限制集合的每个元素都是等价的，考虑二项式反演。设 $f_i$ 为钦定 $i$ 个元素在子集族中出现次数小于等于 $1$ 的方案数，$g_i$ 为有且仅有 $i$ 个元素在子集族中出现次数小于等于 $1$ 的方案数。那么可得 

$$\begin{aligned}
f_i &= \sum\limits_{j = i}^n \dbinom{j}{i} g_j \\
g_i &= \sum\limits_{j = i}^n \left(-1\right)^{j - i}\dbinom{j}{i}f_j
\end{aligned}$$

发现题目要求的其实就是 $g_0$，即

$$\sum\limits_{i = 0}^{n} \left(-1\right)^{i}f_i$$

下面考虑如何计算 $f_i$。

我们考虑钦定的过程，显然这部分有 $\dbinom{n}{i}$ 种方案。对于钦定的 $i$ 个元素，可以分为两类：出现一次的和没有出现的。对于没有出现过的元素可以不考虑，对于只出现一次的元素，设其个数为 $j$，可以考虑将其划分为若干集合，然后再与未钦定的元素进行搭配。将相互区分的 $n$ 个元素划分为 $k$ 个不互相区分的非空集合方案数为 $\displaystyle{n \brace k}$，即第二类斯特林数。所以将钦定的 $i$ 个元素选取 $j$ 个并划分为 $k$ 个集合的方案数为 $\displaystyle \dbinom{i}{j} {j \brace k}$。接下来我们考虑剩余的元素，这些元素没有被限制，可以出现一次、多次或不出现，所以剩余的 $n - i$ 个元素在一个含有钦定元素的集合中共有 $2^{n - i}$ 种分配方式，因为含有钦定元素的共有 $k$ 个子集，所以根据乘法原理可得使得在已钦定 $i$ 个元素的情况下，均含有钦定元素且钦定元素最多出现一次的子集族有 $\displaystyle\sum\limits_k 2^{\left(n - i\right)k} \sum\limits_j \dbinom{i}{j} {j \brace k}$ 种。接下来考虑不含有钦定的 $i$ 个元素的子集族，可以发现共有 $\displaystyle 2^{n - i}$ 种子集，均在子集族中可以独立地出现或不出现，这部分的方案数为 $\displaystyle2^{2^{n - i}}$。根据乘法原理，将钦定 $i$ 个元素的方案数、含有钦定元素且钦定元素最多出现一次的子集族数、不含有钦定元素的子集族数相乘即可得到 $f_i$ 的表达式。

$$\displaystyle f_i = \dbinom{n}{i}\sum\limits_k 2^{\left(n - i\right)k}\sum\limits_j\dbinom{i}{j}{j \brace k} 2^{2^{n - i}}$$

代入我们上面的式子中，可以得到答案的表达式

$$\begin{aligned}
Ans &= \sum\limits_{i = 0}^{n} \left(-1\right)^{i}\dbinom{n}{i}\sum\limits_{k = 0}^{i} 2^{\left(n - i\right)k}\sum\limits_{j = k}^{i}\dbinom{i}{j}{j \brace k} 2^{2^{n - i}} \\
&= \sum\limits_{i = 0}^{n} \left(-1\right)^{i}\dbinom{n}{i}2^{2^{n - i}}\sum\limits_{k = 0}^{i} 2^{\left(n - i\right)k}\sum\limits_{j = k}^{i}\dbinom{i}{j}{j \brace k}
\end{aligned}$$

我们设 $\displaystyle g_{i,k} = \sum\limits_{j = k}^{i}\dbinom{i}{j}{j \brace k}$，考虑如何处理出这个算式，考虑其组合意义，可以发现为在 $i$ 个元素中选取若干个元素划分为 $k$ 个非空集合的方案数。我们在这 $i$ 个元素中再添加一个元素，将没有被选取的元素和这个添加的元素划分到一个新的集合，所以可得总方案数为 $\displaystyle{i + 1 \brace k + 1}$，不难看出其递推式为 $\displaystyle g_{i, k} = g_{i - 1, k - 1} + \left(k + 1\right)g_{i - 1, k}$。递推地计算出所有需要的 $g_{i, k}$ 值再按照表达式计算即可以 $\mathcal{O}(n^2)$ 的复杂度通过本题。

## Code
```cpp
//AT_agc096_c
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;

valueType MOD_;
valueType const &MOD = MOD_;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, const T2 &b, const T3 &mod = MOD) {
    a = a + b;

    if (a > mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Dec(T1 &a, const T2 &b, const T3 &mod = MOD) {
    a = a - b;

    if (a < 0)
        a += mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sum(const T1 &a, const T2 &b, const T3 &mod = MOD) {
    return a + b >= mod ? a + b - mod : a + b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sub(const T1 &a, const T2 &b, const T3 &mod = MOD) {
    return a - b < 0 ? a - b + mod : a - b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(const T1 &a, const T2 &b, const T3 &mod = MOD) {
    return (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Mul(T1 &a, const T2 &b, const T3 &mod = MOD) {
    a = (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 Pow(T1 a, T2 b, const T3 &mod = MOD) {
    T1 result = 1;

    while (b > 0) {
        if (b & 1)
            Mul(result, a, mod);

        Mul(a, a, mod);
        b = b >> 1;
    }

    return result;
}

class Inverse {
public:
    typedef ValueVector container;

private:
    valueType size;
    container data;
public:
    explicit Inverse(valueType n) : size(n), data(size + 1, 0) {
        data[1] = 1;

        for (valueType i = 2; i <= size; ++i)
            data[i] = mul((MOD - MOD / i), data[MOD % i]);
    }

    valueType operator()(valueType n) const {
        return data[n];
    }
};

int main() {
    valueType N;

    std::cin >> N >> MOD_;

    Inverse Inv(N);

    ValueVector Fact(N + 1, 1), InvFact(N + 1, 1);

    Fact[0] = 1;
    InvFact[0] = 1;
    for (valueType i = 1; i <= N; ++i) {
        Fact[i] = mul(Fact[i - 1], i);
        InvFact[i] = mul(InvFact[i - 1], Inv(i));
    }

    typedef std::function<valueType(valueType, valueType)> CalcFunction;

    CalcFunction C = [&Fact, &InvFact](valueType n, valueType m) -> valueType {
        if (n < 0 || m < 0 || n < m)
            return 0;

        return mul(Fact[n], mul(InvFact[m], InvFact[n - m]));
    };

    ValueMatrix G(N + 1, ValueVector(N + 1, 0));

    G[0][0] = 1;
    for (valueType i = 1; i <= N; ++i) {
        G[i][0] = 1;

        for (valueType j = 1; j <= N; ++j)
            G[i][j] = sum(mul(j + 1, G[i - 1][j]), G[i - 1][j - 1]);

    }

    valueType ans = 0;

    for (valueType i = 0; i <= N; ++i) {
        valueType const Pow2 = mul(Pow(2, Pow(2, N - i, MOD - 1), MOD), C(N, i));

        valueType const pre = (i & 1 ? MOD - Pow2 : Pow2);

        valueType const PowN = Pow(2, N - i, MOD);
        valueType PowJ = 1;

        for (valueType j = 0; j <= i; ++j, Mul(PowJ, PowN))
            Inc(ans, mul(pre, mul(PowJ, G[i][j])));
    }

    std::cout << ans << std::endl;

    return 0;
}
```

---

## 作者：Terac (赞：0)

考虑容斥，令 $f(k)$ 表示至少有 $k$ 个物品在**少于**两个子集中出现的方案数，这是组合容斥，$ans=\sum\limits_{k=0}^n (-1)^kf(k)$。

考虑如何求 $f(k)$，首先要钦定选的 $k$ 个物品，即 $\dbinom{n}{k}$。发现无论如何这都与所选的集合数量有关，且这也是 $O(n)$ 级别的，因为每个物品至多被一个集合包含（我开始以为所选集合数量是 $O(2^n)$ 的，觉得很困难），令 $g(k,i)$ 表示这 $k$ 个物品所在的集合恰有 $i$ 个的方案数，则 $f(k)=\dbinom{n}{k}\sum\limits_{i=0}^kg(k,i)$。

考虑 $g(k,i)$ 如何求，将 $k$ 个数放进 $i$ 个集合，允许不放，这很像第二类斯特林数，但是允许不放，可以让集合数量 $+1$，不放的全放进该集合内，但也可以全都不放，这与第二类斯特林数的非空集合条件矛盾，所以让划分的数 $+1$，与最后一个数在同一个集合的就是不放的数，即 $\begin{Bmatrix}k+1\\ i+1\end{Bmatrix}$，这 $i$ 个集合剩下的 $n-k$ 个数均是可放可不放的，同时其余不含这 $k$ 个数的子集都是可取可不取的，所以 $g(k,i)=\begin{Bmatrix}k+1\\ i+1\end{Bmatrix}2^{(n-k)i}2^{2^{n-k}}$，$O(n^2)$ 做即可。

---

## 作者：DaiRuiChen007 (赞：0)

# ARC096E 题解



[Problem Link](https://www.luogu.com.cn/problem/AT_arc096_c)



## 题目大意

> 在 $\{1,2,\dots ,n\}$ 的幂集中选出若干个子集，使得每个元素至少出现过 $2$ 次，求方案数。
>
> 数据范围：$n\le 3000$。



## 思路分析

显然考虑容斥，枚举出现次数 $\le 1$ 次的数的个数 $k$，枚举划分成的集合数 $j$ 对应方案数为：
$$
f(k)=\sum_{j=1}^k g(j,k)\times 2^{2^{n-k}}\times (2^{n-k})^j
$$
其中 $g(j,k)$ 表示 $k$ 个数划分成 $j$ 个集合，可以有一些数不再任何集合中出现过的方案数，显然可以通过一个魔改的斯特林数递推公式求出，考虑一种直接用斯特林数表示的方法：

先考虑所有数都出现过的情况，此时方案为 $\begin{Bmatrix}k\\j\end{Bmatrix}$，接下来考虑至少一个数不出现的情况，容易发现把不出现的数单独形成一个集合即可构造双射，先把 $k$ 个数划分成 $j+1$ 个集合再选一个集合作为不出现的数对应的集合，方案数为 $(j+1)\begin{Bmatrix}k\\j+1\end{Bmatrix}$。

综上 $g(j,k)=\begin{Bmatrix}k\\j\end{Bmatrix}+(j+1)\times \begin{Bmatrix}k\\j+1\end{Bmatrix}$，最终带入容斥表达式得到：
$$
\mathrm{Answer}=\sum_{k=0}^n (-1)^k\binom nk\sum_{j=1}^n\left(\begin{Bmatrix}k\\j\end{Bmatrix}+(j+1)\times \begin{Bmatrix}k\\j+1\end{Bmatrix}\right)\times 2^{2^{n-k}}\times (2^{n-k})^j
$$


预处理出斯特林数后暴力计算即可。

时间复杂度 $\mathcal O(n^2\log P)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
const int MAXN=3005;
inline int ksm(int a,int b,int p) {
	int ret=1;
	while(b) ret=(b&1?ret*a%p:ret),a=a*a%p,b=b>>1;
	return ret;
}
int n,P,fac[MAXN],inv[MAXN],S[MAXN][MAXN];
inline int binom(int n,int m) { return fac[n]*inv[m]%P*inv[n-m]%P; }
signed main() {
	scanf("%lld%lld",&n,&P);
 	for(int i=S[0][0]=inv[0]=fac[0]=1;i<=n;++i) {
		inv[i]=ksm(fac[i]=fac[i-1]*i%P,P-2,P);
		for(int j=1;j<=i;++j) S[i][j]=(S[i-1][j-1]+S[i-1][j]*j)%P;
	}
	int ans=0;
	for(int i=0;i<=n;++i) {
		int tmp=0;
		for(int k=0;k<=i;++k) tmp=(tmp+(S[i][k+1]*(k+1)+S[i][k])%P*ksm(2,k*(n-i),P))%P;
		tmp=tmp*ksm(2,ksm(2,n-i,P-1),P)%P*binom(n,i)%P;
		ans=(ans+((i&1)?(P-tmp):tmp))%P;
	}
	printf("%lld\n",ans);
	return 0;
}
```



---

