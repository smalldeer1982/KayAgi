# [ABC171F] Strivore

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc171/tasks/abc171_f

「好きな英小文字 $ 1 $ 文字を好きな位置に挿入する」という操作を文字列 $ S $ にちょうど $ K $ 回繰り返してできる文字列は何通りあるでしょう？

答えは非常に大きくなる可能性があるので、$ (10^9+7) $ で割ったあまりを出力してください。

## 说明/提示

### 制約

- $ K $ は $ 1 $ 以上 $ 10^6 $ 以下の整数
- $ S $ は英小文字からなる長さ $ 1 $ 以上 $ 10^6 $ 以下の文字列

### Sample Explanation 1

たとえば、`proofend`、`moonwolf`、`onionpuf` などが条件を満たします。 それに対し、`oofsix`、`oofelevennn`、`voxafolt`、`fooooooo` などは条件を満たしません。

## 样例 #1

### 输入

```
5
oof```

### 输出

```
575111451```

## 样例 #2

### 输入

```
37564
whydidyoudesertme```

### 输出

```
318008117```

# 题解

## 作者：CarroT1212 (赞：9)

### 题目大意

给定整数 $K$ 和一个仅含小写字母的字符串 $S$，你要执行“在 $S$ 中任意位置插入一个小写字母”的操作 $K$ 次，问最后可以得到多少个不同的字符串。答案对 $(10^9+7)$ 取模。

数据范围：$1 \le K,|S|\le 10^6$。

------------

### 解法分析

题目可以转化为：

> 问有多少个长度为 $(K+|S|)$ 的仅含小写字母的字符串含有子序列 $S$。

然后就比较好做了。

设 $N=|S|$，这个长度为 $(K+N)$ 的字符串为 $T$。为了防止算重，规定如果 $S$ 中的某个字母在 $T$ 中出现了多次，就尽量匹配到 $T$ 中靠后的位置。比如当 $S$ 为 `abcab`，$T$ 为 `abccbcaaaba` 时，$S$ 的五个位置就会分别匹配到 $T_1,T_5,T_6,T_9,T_{10}$。

枚举 $S$ 的第一位匹配到的位置 $i\,(1 \le i \le K+1)$。$i$ 前面的位置匹配不到，可以随便填，总共有 $26^{i-1}$ 种填法；$i$ 位已经确定；$S$ 的剩下 $(N-1)$ 位匹配的位置共有 $C^{N-1}_{N+K-i}$ 种可能；$T$ 中第 $i$ 位后剩下的还没有被匹配的 $(K-i+1)$ 个位置，每位只有 $25$ 种填法，因为前面去重的方法规定每一个未匹配的位置上填的字符都不能和前一个匹配到的位置上的字符相同。比如 $S$ 为 `abc`，在 $T$ 中匹配得 `ab_c`，其中 `_` 为未匹配上的位置。这一位不能填 `b`，否则 $S$ 中的 `b` 匹配到的就是 $T_3$ 了，不符合条件。但这一位可以填 `a`，因为这时 $S$ 匹配的位置仍然没变，其它字母也一样。所以去掉一种之后就是每位 $25$ 种填法，总共 $25^{K-i+1}$ 种。

于是最后输出的答案就是：

$$\sum\limits_{i=1}^{K+1}26^{i-1}\cdot C^{N-1}_{N+K-i}\cdot 25^{K-i+1}$$

好像跟 $S$ 里面的字母是咋填的也没啥关系啊。

------------

### 代码

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
using namespace std;
const ll N=2e6+7,MOD=1e9+7;
ll n,k,m,fac[N],ans;
char str[N];
ll qpow(ll x,ll y) { return y?(y&1?x:1)*qpow(x*x%MOD,y>>1)%MOD:1; }
ll inv(ll x) { return qpow(x,MOD-2); }
ll C(ll x,ll y) { return x<y?0:fac[x]*inv(fac[x-y])%MOD*inv(fac[y])%MOD; }
void init() { fac[0]=1; for (ll i=1;i<=2e6;i++) fac[i]=fac[i-1]*i%MOD; }
int main() {
	init();
	scanf("%lld%s",&k,str+1),n=strlen(str+1),m=n+k;
	for (ll i=1;i<=k+1;i++)
		ans=(ans+qpow(26,i-1)*C(m-i,n-1)%MOD*qpow(25,k-i+1)%MOD)%MOD;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：SmileMask (赞：2)

~~模拟赛题，赛时没写出来。~~

~~根据手模小样例~~，我们可以发现一个性质：

###  **在空位插入新字母时，插入的字符必然与这个空位后的原来字母不同，才能保证字符串不重复。**

但在最后一个空位插入我们就不用考虑该性质，考虑枚举在最后一个空位插入多少数，其他空位考虑插板法处理。

则答案为：

$$
\sum_{i=0}^k C_{n+k-i-1}^{n-1} \times 26^i \times 25^{k-i}
$$

### Code
```
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
inline int rd(){
	int num=0,sign=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') sign=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') num=(num<<3)+(num<<1)+(ch^48),ch=getchar();
	return num*sign;
}

const int mod=1e9+7;
const int MAXN=5e6+10;
int f[MAXN],inv[MAXN],n,k,ans;
int p25[MAXN],p26[MAXN];

int qmi(int x,int y){
	int res=1;
	x%=mod;
	while(y){
		if(y&1) res=res*x%mod;
		x=x*x%mod;y>>=1;
	}
	return res;
}
int C(int n,int m){
	if(n<m) return 0;
	return f[n]%mod*inv[m]%mod*qmi(f[n-m],mod-2)%mod;
}
void init(int N){
	f[0]=inv[0]=inv[1]=p25[0]=p26[0]=1;
	for(int i=1;i<=N;i++)
		f[i]=f[i-1]*i%mod;
	inv[N]=qmi(f[N],mod-2);
	for(int i=N-1;i>1;i--)
		inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=1;i<=N;i++)
		p25[i]=p25[i-1]*25%mod,p26[i]=p26[i-1]*26%mod;
}

string s;
signed main(){
	k=rd();
	cin>>s;
	n=s.size();
	init(n+k);
	for(int i=0;i<=k;i++){
		int x=C(n+k-i-1,n-1);
		ans=(ans+p26[i]*p25[k-i]%mod*x%mod)%mod;
	}
	cout<<ans<<endl;
	return 0;
}
/**
*　　┏┓　　　┏┓+ +
*　┏┛┻━━━┛┻┓ + +
*　┃　　　　　　　┃
*　┃　　　━　　　┃ ++ + + +
*  ████━████+
*  ◥██◤　◥██◤ +
*　┃　　　┻　　　┃
*　┃　　　　　　　┃ + +
*　┗━┓　　　┏━┛
*　　　┃　　　┃ + + + +Code is far away from 　
*　　　┃　　　┃ + bug with the animal protecting
*　　　┃　 　 ┗━━━┓ 神兽保佑,代码无bug　
*　　　┃ 　　　　　　 ┣┓
*　　  ┃ 　　　　　 　┏┛
*　    ┗┓┓┏━┳┓┏┛ + + + +
*　　　　┃┫┫　┃┫┫
*　　　　┗┻┛　┗┻┛+ + + +
*/
```

---

## 作者：makeinu (赞：1)

现有 $5$ 篇题解全是正推的，我不会。提供一种容斥的做法。

操作完的串长度为 $K + \lvert S \rvert$，每个位置任意填时，总方案数为 $26^{K + \lvert S \rvert}$。

一个合法的串中显然包含一个 $S$ 的子序列，考虑一下朴素的合法串判定过程，一个不合法的串肯定是在匹配到 $S$ 的第 $\lvert S \rvert$ 位之前的任意一位失败了，人话说就是不合法的串一定包含一个最长的不等于 $S$ 的 $S$ 的前缀。

理解了上面这段绕口令，考虑计算不合法的方案数，即为：

$$
\sum_{i = 0}^{\lvert S \rvert -1} 25^{K + \lvert S \rvert - i} \times C_{K + \lvert S \rvert}^{i}
$$

解释一下，$i$ 为不合法的串最长的匹配前缀子序列的长度，即匹配到 $S$ 的第 $i$ 位置合法，$i+1$ 位置不匹配了。所以就是在 $K + \lvert S \rvert$ 中钦定 $i$ 个位置为前缀子序列，剩下 $K + \lvert S \rvert - i$ 个位置显然不能对钦定子序列产生干扰，即 $[L,R]$ 若在 $s_i$ 到 $s_{i+1}$ 匹配位置中间这一段，显然 $[L,R]$ 任意字符不能等于 $s_{i+1}$，否则将不会按照我们钦定的匹配失败顺序进行了，所以钦定位置外任意位置都有 $25$ 种填法。

最后答案为：

$$
26^{K + \lvert S \rvert} - \sum_{i = 0}^{\lvert S \rvert -1} 25^{K + \lvert S \rvert - i} \times C_{K + \lvert S \rvert}^{i}
$$

[Code.](https://atcoder.jp/contests/abc171/submissions/57699131)

---

## 作者：weisongze (赞：0)

# 思路

这道题~~瞪眼法~~易证可以使用组合数计算（费马小定理），正面去想如何计算插入字母的方案数很难，所以我们**正难则反**，去思考有多少个**长度为 $|S|+k$ 的序列其中不包含子序列 $S$**，也就是只包含 $S-1{\ ,\ }S-2 \cdots 0$ 的和。

那么让我们思考只包含 $S-1$ 时：也就是有 $k+1$ 个位置供我们选择，得出 $C_{k+|S|}^{k+1}$ 种位置选择。 

那么对于每个位置我们能选择几种字母呢？首先，我们有 $26$ 种字母的选择，但这里要注意，因为我们不能提前在这个位置放下下一个本该放在前面位置的 $S_{i}$ 所以我们只有 $25$ 种选择，$k+1$ 个位置也就是 $25^{k+1}$。

两式相乘得此时有 $C_{k+|S|}^{k+1}\cdot25^{k+1}$ 种方案。

因此易证所有方案数和为 $\sum_{i=1}^{i\leq|S|}C_{k+|S|}^{k+i}\cdot25^{k+i}$。

那么由于是正难则反所以用总方案数减一下，即 $26^{k+|s|}-\sum_{i=1}^{i\leq|S|} C_{k+|S|}^{k+i}\cdot25^{k+i}$。

# Code

（需要掌握费马小定理）
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define F(i,x,y) for(i=x;i<=y;i++)
#define rF(i,x,y) for(i=x;i>=y;i--)
const int N=2e6+5,MOD=1e9+7; 
int fs(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%MOD;
		a=a*a%MOD,b>>=1;
	}
	return ans;
}
int fact[N+10],inf[N+10];
int C(int n,int k) {return n==k?1:fact[n]*inf[k]%MOD*inf[n-k]%MOD;}
signed main()
{
	int ans=0,k;
	string s;
	cin>>k>>s;
	int len=s.size(),i;
	fact[0]=1;
	F(i,1,N) fact[i]=fact[i-1]*i%MOD;
	inf[N]=fs(fact[N],MOD-2)%MOD;
	rF(i,N-1,1) inf[i]=inf[i+1]*(i+1)%MOD;
	F(i,1,len) ans=(ans+(C(k+len,k+i)*fs(25,k+i))%MOD)%MOD;
	cout<<(fs(26,len+k)-ans+MOD)%MOD;
	return 0;
}
```

---

## 作者：junee (赞：0)

# AT_abc171_f [ABC171F] Strivore 题解

## 前置知识

组合数学。

## 题目分析

正难则反，考虑把所有方案算出来，然后减去不合法的方案。

我们记 $n=|S|$，则我们最后会形成一个长度 $n+k$ 的字符串，考虑现在我们随便填，总方案数为 $26^{n+k}$。

那么考虑什么时候不合法，我们思考最后形成的合法串一定有一个子序列为 $S$，那么如果一个最后形成的串不合法那么他就不存在一个子序列为 $S$，则说明如果把 $S$ 拿去匹配，则会在某一个位置失配。

我们不妨枚举这个失配的位置 $i$，表示前 $i$ 个位置都能在最后的串找到，$i+1$ 找不到，则我们需要在 $n+k$ 个位置放 $i$ 个数，剩下的不能放 $S_{i+1}$，所以剩下的位置有 25 种方法，则所有不合法的方案数为：

$$\sum\limits_{i=0}^{n-1}25^{n+k-i}\binom{n+k}{i}$$

时间复杂度为 $O(n+k)$。

## Code

```
#include<iostream>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<random>
#include<chrono>
using namespace std;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef long long LL;
const int N=2e6+10,p=1e9+7;
int n,k;
string s;
LL fac[N],ifac[N],ans=0;
LL qmi(LL a,int k){
	a%=p;
	LL res=1;
	while(k){
		if(k&1)res=res*a%p;
		k>>=1;
		a=a*a%p;
	}
	return res;
}
void init(int m){
	fac[0]=ifac[0]=1;
	for(int i=1;i<=m;i++)fac[i]=fac[i-1]*i%p;
	ifac[m]=qmi(fac[m],p-2);
	for(int i=m-1;i;i--)ifac[i]=ifac[i+1]*(i+1)%p;
}
LL C(int n,int m){
	if(m>n)return 0;
	return fac[n]*ifac[m]%p*ifac[n-m]%p;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>k>>s;
	n=s.length();
	init(n+k+1);
	ans=qmi(26,n+k);
	for(int i=0;i<n;i++){
		ans=(ans-qmi(25,k+n-i)*C(k+n,i)%p+p)%p;
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：std_qwq (赞：0)

### 题意转化
$K$ 次操作后会产生一个长度为 $K+\left | S \right | $ 的字符串 $T$，要求 $S$ 是一个子序列。
### 思路
设 $f_{i,j}$ 为**考虑 $T$ 的前 $i$ 位，匹配 $S$ 的前 $j$ 位的方案数**。特别地，如果 $j > \left | S \right |$,可以用 `a` 补齐。

$ {\textstyle \sum_{i=n}^{n+k}f_{n+k,i}} $ 即为答案。
### 初始化
$f_{0,0}=1$。
### 转移
$f_{i,j}=25 \times f_{i-1,j}+f_{i-1,j-1}\times[j>0],i>0$。

以上 DP 显然不能通过本题，考虑其数学性质。
### 进一步转化
通过找规律，或者以下给出的方法可以得到 $f_{i}$ 实际上是 $(25+1)^{i}$ 的展开，即：
$$
\begin{aligned}   f_{i,j} & = C_{i}^{j}\times25^{i-j}       \end{aligned}。
$$

考虑从 $(0,0)$ 走到 $(i,j)$，往下走要 $\times 25$，往右下则 $\times 1$，那么要走 $j$ 次右下，$i-j$ 次下，一共 $C_{i}^{j}$ 种走法。

通过预处理乘法逆元和阶乘，计算：
$$
\begin{aligned}   {\textstyle \sum_{i=n}^{n+k}25^{n+k-i}\times C_{n+k}^{i}}    \end{aligned}。
$$
### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+10,M=1e9+7;
typedef long long ll;
ll f[N],iv[N];
ll qmi(ll a,ll b,ll p){
    ll res=1;
    while(b){
        if(b&1)res=res*a%p;
        a=a*a%p;
        b>>=1;
    }
    return res;
}
void init(int n){
    f[1]=iv[1]=1;
    f[0]=iv[0]=1;
    for(int i=2;i<=n;i++)f[i]=f[i-1]*i%M;
    iv[n]=qmi(f[n],M-2,M);
    for(int i=n-1;i>0;i--)iv[i]=iv[i+1]*(i+1)%M;
}
ll C(ll a,ll b){
    return f[b]*iv[a]%M*iv[b-a]%M;
}
int n,k;
int main(){
    string s;
    cin>>k>>s;
    n=s.size();
    init(n+k);
    ll ans=0;
    for(int i=n;i<=n+k;i++)ans=(ans+qmi(25,n+k-i,M)*C(i,n+k)%M)%M;
    cout<<ans<<endl;
}
```

---

## 作者：_Flame_ (赞：0)

### $\text{solution}$

可以发现拼在最后的字符无论如何都会使得字符串不同，而插在中间的要与插入位置后面的不同才不会重复，考虑枚举有多少个字符被拼在最后，设为 $i$ 个，则这种情况产生的贡献为 $C_{n+k-i-1}^{n-1}\times 26^i\times 25^{k-i}$，累加即可。

### $\text{code}$

```cpp
int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b&1){
			ans=ans*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
	return ans%mod;
}

int fac[maxn],inv[maxn];

void init(int maxn){
	fac[0]=1;
	for(int i=1;i<=maxn;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	inv[maxn]=ksm(fac[maxn],mod-2);
	for(int i=maxn-1;i>=0;i--){
		inv[i]=inv[i+1]*(i+1)%mod;
	}
}

int C(int m,int n){
	if(n<0||m<0||m<n){
		return 0;
	}
	return fac[m]*inv[n]%mod*inv[m-n]%mod;
}

int k,n;
string s;

void solve(){
	init(maxn-1);
	k=read();
	cin>>s;
	n=s.size();
	s=" "+s;
	int ans=0;
	for(int i=0;i<=k;i++){
		int cnt=ksm(26,i)*ksm(25,k-i)%mod;
		ans=(ans+C(n+k-i-1,n-1)*cnt%mod)%mod;
	}
	write(ans);
	puts("");
	return ;
}
```

---

## 作者：TLE_Automat (赞：0)

[Read in My Blog](https://tle-automat.top/2023/12/15/ABC171F/)

## 题目链接

[https://atcoder.jp/contests/abc171/tasks/abc171_f](https://atcoder.jp/contests/abc171/tasks/abc171_f)

## 题目大意

给定一个长度为 $n$ 的由小写字母组成的字符串 $s$ ，每次操作任选一个位置插入任意一个小写字母，问进行恰好 $k$ 次操作之后能得到多少种本质不同的字符串，答案对 $10^{9} + 7$ 取模。

两个字符串本质不同，当且仅当长度不同或者至少有一个位置上的字母不同。

## 数据范围

- $1\le n, k \le 10^{6}$

<!--more-->

## 解题思路

不难想到，问题等价于有 $n + k$ 个位置，我们先找出 $n$ 个位置依次放上字符串 $s$ 的每一位，然后剩下的 $k$ 个位置每个随便选一个字母，能得到多少种本质不同的字符串。

很显然，这样简单粗暴的计算会导致答案统计重复。

如果从反向考虑，假设存在一个答案，我们如何通过一一映射的方法让它统计且恰好被统计一次。

考虑到，一个合法的方案，最终得到的长度为 $n + k$ 的字符串，$s$ 一定是它的一个子序列，假设最靠前出现的那个子序列对应的位置为 $p_1, p_2, \cdots, p_n$ 。考虑枚举 $p_1, p_2, \cdots, p_n$ ，钦定这些位置为最靠前出现的那个子序列， 选取剩下位置的小写字母时不破坏前面的性质，这样我们每个合法的答案只会被最靠前出现的那个子序列统计一次，这样就能不重不漏地统计了。

那么如何保证不破坏前面那条性质呢？

显然，只要在区间 $(0, p_1)$ 上不要选取字母 $s_{p_1}$ ，区间 $(p_1, p_2)$ 上不要选取字母 $s_{p_2}$ ，在区间 $(p_2, p_3)$ 上不要选取字母 $s_{p_3}$ ，在区间 $(p_{i - 1}, p_{i})$ 上不要选取字母 $s_{p_i}$ 即可。 

考虑枚举最后一个放置字母的位置 $i$ ，根据上面的分析，在 $i$ 之前的每个空位，都只能选取 $25$ 个不同的小写字母，在 $i$ 之后的每个空位，可以选取 $26$ 个不同的小写字母，所以容易得到最终答案是

$$
\begin{aligned}

\sum\limits_{i = n} ^ {n + k} \binom{i - 1}{n - 1} 25^{i - n} 26^{n + k - i} 

\end{aligned}
$$

## 参考代码

[https://atcoder.jp/contests/abc171/submissions/48405143](https://atcoder.jp/contests/abc171/submissions/48405143)

---

