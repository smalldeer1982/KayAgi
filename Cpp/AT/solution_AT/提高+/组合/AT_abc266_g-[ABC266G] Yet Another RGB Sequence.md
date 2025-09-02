# [ABC266G] Yet Another RGB Sequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc266/tasks/abc266_g

整数 $ R,G,B,K $ が与えられます。`R`, `G`, `B` からなる文字列 $ S $ であって、以下の条件をすべて満たすものの個数を $ 998244353 $ で割った余りを求めてください。

- $ S $ に含まれる `R`, `G`, `B` の個数はそれぞれ $ R,G,B $ 個である。
- $ S $ に（連続する）部分文字列として含まれる `RG` の個数は $ K $ 個である。

## 说明/提示

### 制約

- $ 1\ \leq\ R,G,B\leq\ 10^6 $
- $ 0\ \leq\ K\ \leq\ \mathrm{min}(R,G) $
- 入力は全て整数

### Sample Explanation 1

条件を満たす文字列は以下の $ 6 $ 個です。 - `RRGB` - `RGRB` - `RGBR` - `RBRG` - `BRRG` - `BRGR`

### Sample Explanation 2

個数を $ 998244353 $ で割った余りを求めてください。

## 样例 #1

### 输入

```
2 1 1 1```

### 输出

```
6```

## 样例 #2

### 输入

```
1000000 1000000 1000000 1000000```

### 输出

```
80957240```

# 题解

## 作者：听取T声一片 (赞：16)

题解全是反演？我来一发组合意义的题解吧。

首先我们考虑把 $\texttt{rg}$ 算成字符 $\texttt{\#}$。

题面即变为：**求 $R - k$ 个 $\texttt{r}$，$G-k$ 个 $\texttt{g}$，$B$ 个 $\texttt{b}$，$k$ 个 $\texttt{\#}$ 组成不含 $\texttt{rg}$ 的序列的方案数。**

此时，我们先把 $\texttt{g},\texttt{b}$ 和 $\texttt{\#}$ 排好，方案即为 $C_{G-k +B+k}^{G-k} \times C_{B+k}^k$。

再考虑把 $R-k$ 个 $\texttt{r}$ 加入，此时不能将 $\texttt{r}$ 放在 $\texttt{g}$ 前面，所以这一步有 $C_{R-k+B+k}^{R-k}$ 种方案。

故共有 $C_{G+B}^{G-k} \times C_{B+k}^k \times C_{R+B}^{R-k}$ 种方案。

贴一下代码（本人在实现中先将 $R$ 和 $G$ 减去了 $k$ ，但化简后与文字叙述中的式子相同）：
```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int a,b,c,d,ans;
int ksm(int x,int y)
{
	int ret=1;
	while(y)
	{
		if(y%2) ret*=x,ret%=mod;
		x*=x,x%=mod,y/=2;
	}
	return ret;
}
int C(int n,int m)
{
	if(m>n/2) m=n-m;
	if(m==0) return 1;
	int ret=1;
	for(int i=n;i>=n-m+1;i--)
		ret*=i,ret%=mod;
	for(int j=1;j<=m;j++)
		ret*=ksm(j,mod-2),ret%=mod;
	return ret;
}
signed main()
{
	scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
	a-=d,b-=d;
	ans=C(c+d+b,b)*C(d+c,d)%mod*C(c+d+a,a)%mod;
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：daniEl_lElE (赞：6)

基本算容斥板子。

## 思路

令 $f(i)$ 为钦定 $i$ 个连续的 `rg` 其余随便选的方案数，我们的目标是正好 $k$ 个的方案。

首先不难发现 $f(i)$ 可以先从 $n$ 个位置中选出 $i$ 组放 `rg`，然后再选择 $r-i,g-i$ 个放 `r` 和 `g` 即可，比较容易计算，答案为 $\binom{n-i}{i}\times\binom{n-i\times 2}{r-i}\times \binom{n-i-r}{g-i}$。

然后显然正好 $k$ 的方案可以使用二项式反演得到，即令 $g(i)$ 为正好 $i$ 个的方案，$g(i)=\sum_{j=i}^nf(j)\times \binom{j}{i}\times (-1)^{j-i}$。

求 $g(k)$ 就可以在 $\Theta(n)$ 时间复杂度内计算。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans;
}
int fac[10000005],inv[10000005];
void init(){
	fac[0]=1;
	for(int i=1;i<=10000000;i++) fac[i]=fac[i-1]*i%mod;
	inv[10000000]=qp(fac[10000000],mod-2);
	for(int i=9999999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int i,int j){
	if(i<0||j<0||i<j) return 0;
	return fac[i]*inv[i-j]%mod*inv[j]%mod;
}
int ans[10000005];
signed main(){
	init();
	int r,g,b,k;
	cin>>r>>g>>b>>k;
	int n=r+g+b;
	for(int i=0;i<=min(r,g);i++){
		ans[i]=C(n-i,i)*C(n-i*2,r-i)%mod*C(n-i-r,g-i)%mod;
	}
	int tot=0;
	for(int i=k;i<=min(r,g);i++){
		if((i-k)%2==0){
			tot=(tot+ans[i]*C(i,k))%mod;
		}
		else{
			tot=(tot+mod-ans[i]*C(i,k)%mod)%mod;
		}
	}
	cout<<tot;
	return 0;
} 
```

---

## 作者：Saint_ying_xtf (赞：3)

[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)。

记录一下吧，虽然是 VP，但是我第一次想出 G 题！！

这个题目可能会想成一个 Dp，但是发现，这其实用组合数学求解即可。正好，教练刚讲了卢卡斯定理求解组合数，立马派上用场！！

我们可以稍微的转换一下题面：

一个 $s$ 字符，你要构造出 $R-k$ 个字符 ```r```，$G-k$ 个字符 ```g```，$B$ 个字符 ```b```，$k$ 个字符 ```k```，因为 ```rg``` 肯定是单独出现的。

那我们现在就考虑如何用组合数来求解。

下文和代码默认将 $R$ 和 $G$ 减去 $k$。方便处理。

显然对于 $R+G+B+k$ 个空给你填，```r``` 肯定不能填到 ```g``` 前面，所以组合数是 $C_{R+B+k}^R$。

对于 ```g```，```g``` 肯定不能填到 ```r``` 后面，就是 $C_{G+B+k}^G$。

然后剩下只剩下 $B+k$ 个空了，于是贡献是 $C_{B+k}^B$。剩下的都是 $k$ 的了。

于是乘法原理得到答案是：$C_{R+B+k}^R \times C_{G+B+k}^G \times C_{B+k}^B$。

但是蒟蒻却调了一个多小时。

可能你也会有以下错误：

- $R$ 和 $G$ 没有减 $k$。
- 没有考虑到 ```g``` 肯定不能填到 ```r``` 或 ```r``` 肯定不能填到 ```g``` 前面。

于是，你就轻松的过了一道蓝题！

[link](https://atcoder.jp/contests/abc266/submissions/49393670)。

---

## 作者：RAND_MAX (赞：2)

一道组合计数简单题。

由于题目限制了 `rg` 的出现次数，那我们考虑将 `rg` 绑在一起考虑，那么题面就变为有 $R-k$ 个 `r`，$G-k$ 个 `g`，$B$ 个 `b`，$k$ 个 `rg`。注意此时序列不能含有除了这 $k$ 个以外的 `rg`。

我们先考虑计算不包含 `r` 的方案数，有 $B+G$ 个空位，故方案数为 $\dbinom{B+G}{B}\times \dbinom{G}{G-k}$。

再考虑插入 $R-k$ 个 `r`。由于不能再产生新的 `rg`，所以 `r` 不能放在 `g` 前面。那么有 $B+k$ 个空位可以让若干个 `r` 放在前面。考虑插板法，允许有空位前面不放 `r`。那么有 $\dbinom{B+k+R-k}{R-k}$ 种方案。

将两部分结合起来就能得到答案：共有 $\dbinom{B+G}{B}\times \dbinom{G}{G-k}\times \dbinom{B+R}{R-k}$ 种方案。


```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define R read()
using namespace std;
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0')
	{
		if(c=='-')
		{
			f=-1;
		}
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+c-48;
		c=getchar();
	}
	return x*f;
}
void write(int x)
{
	static int st[35],top=0;
	if(x<0)
	{
		x=-x;
		putchar('-');
	}
	do
	{
		st[top++]=x%10;
		x/=10;
	}while(x);
	while(top)
	{
		putchar(st[--top]+48);
	}
	putchar('\n');
}
int r,g,b,k,jc[2000010];
int qpow(int x,int y)
{
	int num=1;
	while(y)
	{
		if(y&1) 
		{
			num=num*x%mod;
		}
		x=x*x%mod;
        y>>=1;
    }
    return num%mod;
}
int c(int n,int m)
{
	return jc[n]*qpow(jc[n-m]*jc[m]%mod,mod-2)%mod;
}
signed main()
{
	r=R,g=R,b=R,k=R;
	jc[0]=1;
	for(int i=1;i<=2000000;i++)
	{
		jc[i]=jc[i-1]*i%mod;
		jc[i]%=mod;
	}
	write((c(g,g-k)%mod*c(g+b,b)%mod*c(r+b,r-k)%mod)%mod);
 	return 0;
}

```

---

## 作者：Empty_Dream (赞：2)

## 题意

求符合要求的字符串个数，对 $998244353$ 取余。

满足要求的字符串 $s$ 具备以下特性：

- $s$ 由 `r`、`g`、`b` 构成。

- $s$ 中有 $R$ 个 `r`，$G$ 个 `g`，$B$ 个 `b`，$k$ 个 `rg`。

## 分析

很明显发现是一道排列组合的题，~~恰好本蒟蒻刚学了卢卡斯定理~~。

开始推式子，我们发现 `r` 和 `g` 的排列会影响到 `rg` 的个数，不妨先把 `r` 提出来，先去算剩下有多少种排列，再把 `r` 加进去计算总排列数。而 `rg` 中包含了一个 `r` 和一个 `g`，所以之后排列的 `r` 和  `g` 的个数为 $R-k$ 和 $G - k$。

至于式子，考虑简化版的，只有 `r`，`g`，`b` 的限制，那么 `r` 就有 $C_{R+G+B}^R \times C_{G+B}^{G}$ 种情况（先填 `r` 后填 `g` 最后 `b` 的位置也就确定了，$R+G+B$ 表示字符串总长度）。那么原题中把 `r` 提出来后同理有 $C_{G-k+B+k}^{G-k} \times C_{B+k}^k$ 种情况。

再考虑加了 `r` 之后的情况，因为前面的操作使得我们不能在之后的操作中形成 `rg`，所以之后 `r` 能选择的位置就只剩下了总数减去 `r` 的个数。

最后得到式子 $C_{G-k+B+k}^{G-k} \times C_{B+k}^k \times C_{R-k+B+k}^{R-k}=C_{G+B}^{G-k} \times C_{B+k}^k \times C_{R+B}^{R-k}$。

很明显这题不能暴力求组合数，必须通过卢卡斯定理，~~不会的自行百度~~。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 998244353;
int r, g, b, k;

int ksm(int a, int b, int p){
	int res = 1;
	while (b){
		if (b & 1) res = res * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return res;
}

int C(int a, int b, int p){
	if (b > a) return 0;
	int res = 1;
	for (int i = a, j = 1; j <= b; i--, j++){
		res = res * i % p;
		res = res * ksm(j, p - 2, p) % p;
	}
	return res;
}

int lucas(int a, int b, int p){
	if (a < p && b < p) return C(a, b, p);
	return C(a % p, b % p, p) * lucas(a / p, b / p, p) % p; 
}

signed main(){
	cin >> r >> g >> b >> k;
	cout << lucas(g + b, g - k, mod) * lucas(b + k, k, mod) % mod * lucas(r + b, r - k, mod) % mod << endl;//lucas套公式
	return 0;
}
```

---

## 作者：TillTheEnd (赞：1)

能评到空心黄是不是只是因为位置原因啊。

真心只有 *1800 左右罢。

--------

题意：对满足以下要求的序列计数：
-  由 `R`,`G`,`B` 组成，其中恰 $R$ 个 `R`，$G$ 个 `G`，$B$ 个 `B`。
- 连续的 `RG` 作为子串恰出现 $K$ 次” 。
- 膜 $998244353$ 输出。

--------------

这里的连续 `RG` 好突兀啊，能不能直接枚举？

但是恰好怎么做，反演还是容斥？

先想想钦定 $k$ 个 `RG` 怎么做罢：把 `RG` 和 `B` 分别看成分隔符，然后试着往里插剩余 `R`，`G`。

令 $n=R-K,m=G-K,k=C+K$，则我们要统计 $n$ 个 `R` $m$ 个 `G` 分成 $k+1$ 段的方案数。无重复自然最好，有重复再想方法。

不能形成连续 `RG`，一个被分隔符分隔的区间必须是前面一段 `R` 连后面一段 `G` 的形式。

那么，只要知道一个区间内 `R` 和 `G` 的个数，就能唯一确定区间的排列方式。

对 `R` 和 `G` 分别计算，这不就是一个小组合问题。

这时看回要求，开头的 `R` 显然不会参与与分隔符凑成 `RG`，等等结尾的 `G` 好像也不会？

每个符合要求的序列忽略分隔符排列后都能唯一对应到 `R` 和 `G` 分配到不同区间的个数，而后者一定合法，那么前后一一对应，直接计不就完了！

分隔符有 $\binom{k}{C}$ 种排法，`R` 有 $\binom{n+k}{k}$ 种排法，`G` 有 $\binom{m+k}{k}$ 种排法，乘一起就是答案。

代码不给了，很好写。注意组合数预处理要处理两倍数据范围。

事实上，前面那句“先想想钦定 $k$ 个 `RG` 怎么做”的缘由是我开始往二项式反演想了一段。

---

## 作者：syysongyuyang (赞：1)

二项式反演萌萌题。

注意到最后要求需要 $k$ 个 `rg`，考虑钦定有 $k$ 个位置有 `rg`，则方案数为在 $n-1$ 个位置中选 $m$ 个且两两不相邻。这是个经典问题，先得到 $m$ 个位置，再在每个间隔插 $1$ 个位置，再将剩下 $n-2m$ 个位置插板法插进 $m+1$ 组内，每组可空。这是经典的可空插板法，答案为 $\binom {n-m} {m}$。剩下的 `r`，`g`，`b` 随意放置即可。

定义上面的式子为 $f(i)$，注意到 $f(i)$ 只保证至少有 $i$ 个 `rg`，剩下的 `r`，`g` 随意排列仍然能产生 `rg`。考虑如何求出 $g(i)$ 表示恰好有 $i$ 个 `rg` 的方案数。注意到至少与恰好的转化，套路地考虑二项式反演，则有 $g(i) = \sum\limits_{j=i}^{n} (-1)^{i-j} \binom {i} {j} f(j)$。

预处理阶乘，阶乘逆元，$\Theta(n)$ 计算即可。

---

## 作者：Super_Cube (赞：1)

# Solution

钦定有 $i$ 个 `rg` 的我认为是好想的，先要从 $R+G+B-i$ 个位置中选出 $i$ 个位置放 `rg`，再从剩下的 $R+G+B-2i$ 个位置中任选 $R-i$ 个位置放剩下的 `r`，然后从剩下的 $G+B-i$ 个位置中任选 $G-i$ 个位置放剩下的 `g`，最后还没填的位置就是放 `b`。

钦定会算了，就可以用二项式反演算恰好为 $k$ 个 `rg` 的方案了，答案为：

$$
\sum_{i=k}^{\min(R,G)}(-1)^{i-k}\binom{i}{k}\binom{R+G+B-i}{i}\binom{R+G+B-2i}{R-i}\binom{G+B-i}{G-i}
$$

---

## 作者：Rnfmabj (赞：1)

## ABC266G

*2045


### 题意

给你四个整数 $R,G,B,K$。

你需要求出有多少个由 `R`，`G`，`B` 组成的字符串满足以下条件：

1. `R`，`G`，`B` 的个数恰好分别为 $R,G,B$。

2. 子串 `RG` 的出现次数恰好为 $K$。

答案对 $998244353$ 取模。

$R,G,B \le 10^6,K \le \min(R,G)$


### 题解

看到 “出现次数恰好为 $K$”，考虑二项式反演。

设 $f(x)$ 表示“钦定子串 `RG` 出现了 $x$ 次的方案数”，$g(x)$ 表示“恰好子串 `RG` 出现了 $x$ 次的方案数”。

那么 $f(x)$ 是很好计算的，将 `RG` 看做第四个字符然后计算排列最后对四个字符消序即可。

即：设 $n=R+G+B$ ，则
$$
f(x)=\frac{n!}{x!\ · \ (R-x)!\ ·\ (G-x)!\ · \ B!}
$$
然而 $g(x)$ 就不那么便于直接计算了，需要通过 $f(x)$ 计算。

首先考虑 $f,g$ 的关系。

由于一个是 “钦定（至少）”，一个是 “恰好”，所以对于任意的 $n \le i$，$g(i)$ 在 $f(n)$ 中被计算了 $\binom{i}{n}$ 次。

也就是 $f(x)=\sum_{i=x}^{lim}\binom{i}{x}g(i)$，其中 $lim=\min(R,G)$。

运用 [二项式反演](https://www.cnblogs.com/GXZlegend/p/11407185.html) 的常用形式，可以得到：

（↑上面这个博客讲得超级好诶，真的不去看看嘛）
$$
g(x)=\sum_{i=x}^{lim}(-1)^{i-x}\binom{i}{n}f(i)
$$
用这个式子就可以计算出 $g(k)$ 也就是答案啦~

时间复杂度可以做到 $O(N)$，我的代码在预处理环节没有选择线性做，所以是 $O(N \log V)$ 的，其中 $V$ 为模数。

### 代码

```cpp
const ll maxn=3e6+5,mod=998244353;
ll ksm(ll x,ll k){ll res=1;for(;k;k>>=1,x=x*x%mod)if(k&1)res=res*x%mod;return res;}
ll a,b,c,k;
ll fac[maxn],inv[maxn];
ll n;
ll C(ll x,ll y){return fac[x]*inv[y]%mod*inv[x-y]%mod;}
void init(){
	n=a+b+c;
	fac[0]=inv[0]=1;
	for(ll i=1;i<=n;i++){
		fac[i]=fac[i-1]*i%mod;
		inv[i]=ksm(fac[i],mod-2);
	}
}
ll f[maxn],g[maxn];
void solve(){
	a=R,b=R,c=R,k=R;
	init();
	ll lim=min(a,b);
	for(ll i=k;i<=lim;i++){
		f[i]=fac[n-i]*inv[i]%mod*inv[a-i]%mod*inv[b-i]%mod*inv[c]%mod;
	}
	ll ans=0;
	for(ll i=k;i<=lim;i++){
		ans=(ans+((i-k)%2==1?mod-1:1)*C(i,k)%mod*f[i]%mod)%mod;
	}
	we(ans);
	return ;
}
```



---

## 作者：luuia (赞：0)

### Question

求满足其中有 $R$ 个 $\texttt{r}$，$B$ 个 $\texttt{b}$，$G$ 个 $\texttt{g}$，$K$ 个 $\texttt{rg}$ 的字符串数量。

### Solution

记 $\texttt{rg} = \texttt{s}$，那么限制中的 $K$ 个 $\texttt{rg}$ 实际上就变成了用 $R-K$ 个 $\texttt{r}$，$G-K$ 个 $\texttt{g}$，$K$ 个 $\texttt{s}$，$B$ 个 $\texttt{b}$ 所形成的不包含 $\texttt{rg}$ 字串的字符串数。

我们先填 $R-K$ 个 $\texttt{r}$，$K$ 个 $\texttt{s}$，$B$ 个 $\texttt{b}$，答案为 $\binom{B+R}{R-K}\binom{B+K}{K}$。

还剩下 $B+R+1$ 个空可以填 $\texttt{g}$，又因为 $\texttt{g}$ 不能在 $\texttt{r}$ 后面，所以只有 $B+K+1$ 个空来填，这是一个可重排列，因此这部分答案为 $\binom{B+G}{G-K}$，最终答案将两部分乘起来即可。

注意预处理上界要开到 $2\times10^6$。

### Code


```cpp
#include<bits/stdc++.h>
using namespace std;

long long read()
{
    long long s = 0,w = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') w = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        s = (s << 1) + (s << 3) + (ch ^ 48);
        ch = getchar();
    }
    return s * w;
}

void write(long long a)
{
    if(a < 0) putchar('-'),a = -a;
    if(a > 9) write(a / 10);
    putchar(a % 10 + '0');
}

const int N = 2e6 + 10,p = 998244353;
long long r,g,b,k,fac[N],inv[N];

long long quickpow(long long c,long long n,long long m)
{
    long long res = 1;
    while(n)
    {
        if(n & 1) res = res * c % m;
        c = c * c % m;
        n >>= 1;
    }
    return res;
}

void init(long long n)
{
    fac[0] = inv[0] = 1;
    for(int i = 1;i <= n;i++) fac[i] = fac[i - 1] * i % p;
    inv[n] = quickpow(fac[n],p - 2,p);
    for(int i = n - 1;i >= 1;i--) inv[i] = inv[i + 1] * (i + 1) % p;
}

long long C(long long n,long long m)
{
    if(n < 0 || m < 0) return 0;
    if(m == 0) return 1;
    return fac[n] * inv[m] % p * inv[n - m] % p;
}

int main()
{
    // freopen("input.in","r",stdin);
    r = read(),g = read(),b = read(),k = read(),init(N - 5);
    cout << C(b + r,b) * C(r,k) % p * C(b + g,g - k) % p << endl;
    return 0;
}
```

---

## 作者：Iniaugoty (赞：0)

[ABC266G Yet Another RGB Sequence](/problem/AT_abc266_g)

将 $K$ 个 `RG` 捆绑，问题转化成排好 $R - K$ 个 `R`，$G - K$ 个 `G`，$B$ 个 `B`， $K$ 个 `RG`，并且不存在第一种的 `R` 后跟第二种的 `G`。

考虑先排好 `R`，`B`，`RG`，方案数为多重集的排列 $\frac {(R + B)!} {(R - K)! B! K!}$。

再将 `G` 插进去，共 $R + B + 1$ 个空位，除去 $R - K$ 个 `R` 后面的，还有 $B + K + 1$ 个，即相当于用 $B + K$ 个板来分隔 $G - K$ 个 `G`，于是方案数为 $\binom {B + K + G - K} {G - K} = \binom {B + G} {G - K}$。

综上答案为 $\frac {(R + B)!} {(R - K)! B! K!} \times \binom {B + G} {G - K}$。

[code](https://atcoder.jp/contests/abc266/submissions/59223952)。

---

## 作者：DengDuck (赞：0)

这题我啥时候做过啊？我咋没印象？

之前写的是第一篇题解的组合法，于是现在想了一种不一样的做法。

我们设 $F(i)$ 表示序列中至少有 $i$ 个 `rg` 的方案数。

那么可以理解为有 $R-i$ 个 `r`，有 $G-i$ 个 `g`，有 $B$ 个 `b`，有 $i$ 个 `rg`，一共四种字母，这个的排列很好求。

$$
F(i)=\binom{n-i}{i}\binom{n-2i}{R-i}\binom{n-i-R}{G-i}
$$

然后我们设正好为 $i$ 个 `rg` 的函数 $G(i)$。

显然：

$$
F(n)=\sum_{i=n}^{\min(R,G)}\binom {i}{n}G(i)\Leftrightarrow G(n)=\sum_{i=n}^{\min(R,G)}(-1)^{i-n}\binom {i}{n}F(i)
$$

这个结论叫二项式反演，这里就不证明了。

$$
G(k)=\sum_{i=k}^{\min(R,G)}(-1)^{i-k}\binom {i}{k}\binom{n-i}{i}\binom{n-2i}{R-i}\binom{n-i-R}{G-i}
$$

然后直接算就行。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
#define LowBound lower_bound
#define UpBound upper_bound
//#define Fi first
//#define Se second
//#define Ls(x) (x<<1)
//#define Rs(x) (x<<1|1)
//#define Ls(x) t[x].Lson
//#define Rs(x) t[x].Rson
using namespace std;
//const LL Inf;
const LL N=3e6+5;
const LL M=3e6;
const LL Mod=998244353;
//const LF eps;
//const LL P;
LL R,G,B,K,Fac[N],Inv[N];
LL Ksm(LL x,LL y)
{
	LL Ans=1;
	while(y)
	{
		if(y&1)Ans=Ans*x%Mod;
		x=x*x%Mod,y>>=1;
	}
	return Ans;
}
void Init()
{
	Fac[0]=1;
	for(LL i=1;i<=M;i++)Fac[i]=Fac[i-1]*i%Mod;
	Inv[M]=Ksm(Fac[M],Mod-2);
	for(LL i=M-1;i>=0;i--)Inv[i]=Inv[i+1]*(i+1)%Mod;
}
LL C(LL n,LL m)
{
	if(n<0||m<0||n<m)return 0;
	return Fac[n]*Inv[m]%Mod*Inv[n-m]%Mod;
}
void Add(LL &x,LL y){x=(x+y+Mod)%Mod;}
int main()
{
	Init();
	LL Ans=0;
	scanf("%lld%lld%lld%lld",&R,&G,&B,&K);
	LL n=R+G+B;
	LL k=1;
	for(int i=K;i<=R&&i<=G;i++,k=-k)
	{
		LL Cnt=C(n-i,i)%Mod*C(n-2*i,R-i)%Mod*C(n-i-R,G-i)%Mod;
		Add(Ans,k*C(i,K)%Mod*Cnt%Mod);
	}
	printf("%lld\n",Ans);
	return 0;
}
//RP++
```

---

## 作者：escapist404 (赞：0)

求字符串的个数，满足其恰有 $r$ 个 `r`，$g$ 个 `g`，$b$ 个 `b` 和 $k$ 个 `rg`。

$1 \le r, g, b, k \le 10^6$，$k \le \min(r, g)$。

---

显然字符串的长度 $r + g + b = n$。

首先考虑至少有 $k$ 个怎么做。

考虑将 `rg` 当成板插进原序列中。由于这里的板会相邻，我们先放入 $k$ 个球，这一部分的方案是 $\binom{n - k}{k}$。

再考虑放剩下的 `r` 和 `g`，这一部分的方案是 $\binom{n - 2k}{r - k} \cdot \binom{n - k - r}{g - k}$。

所以至少放 $k$ 个 `rg` 的方案数是 $\binom{n - k}{k} \cdot \binom{n - 2k}{r - k} \cdot \binom{n - k - r}{g - k}$。

然后由二项式反演，知道恰好放 $k$ 个的方案数为：

$$\sum_{j=0}^{\min(r, g)-k} \binom{n - j}{j} \cdot \binom{n - 2j}{r - j} \cdot \binom{n - j - r}{g - j} \cdot \binom{k + j}{k} \cdot \left( -1\right)^j$$

时间复杂度为 $O(n)$。

---

```cpp
#include <bits/stdc++.h>

int main() {
  int r, g, b, k;
  std::cin >> r >> g >> b >> k;

  int n = r + g + b;
  using i64 = long long;
  std::vector<i64> fac(n + 1), inv(n + 1);

  const i64 p = 998'244'353;
  auto pow = [](i64 x, i64 y) {
    i64 res = 1, cur = x;
    while (y) {
      if (y & 1) (res *= cur) %= p;
      (cur *= cur) %= p;
      y >>= 1;
    }
    return res;
  };

  fac[0] = 1;
  for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % p;
  inv[n] = pow(fac[n], p - 2);
  for (int i = n - 1; i >= 0; --i) inv[i] = inv[i + 1] * (i + 1) % p;

  auto comb = [&inv, &fac](int upp, int dwn) {
    if (upp < 0 || dwn < 0) return 0ll;
    if (upp < dwn) return 0ll;
    return fac[upp] * inv[dwn] % p * inv[upp - dwn] % p;
  };

  auto func = [&](int k, int r, int g) {
    return comb(n - k, k) * comb(n - 2 * k, r - k) % p * comb(n - k - r, g - k) % p;
  };

  i64 answer = 0;
  for (int i = k, fix = 1; i <= std::min(r, g); ++i) (((answer += comb(i, k) * fix * func(i, r, g)) %= p) += p) %= p, fix = -fix;

  std::cout << (answer + p) % p << '\n';

  return 0;
}

```

---

