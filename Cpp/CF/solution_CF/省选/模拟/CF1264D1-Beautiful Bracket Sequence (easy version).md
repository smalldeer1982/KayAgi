# Beautiful Bracket Sequence (easy version)

## 题目描述

This is the easy version of this problem. The only difference is the limit of $ n $ - the length of the input string. In this version, $ 1 \leq n \leq 2000 $ . The hard version of this challenge is not offered in the round for the second division.

Let's define a correct bracket sequence and its depth as follow:

- An empty string is a correct bracket sequence with depth $ 0 $ .
- If "s" is a correct bracket sequence with depth $ d $ then "(s)" is a correct bracket sequence with depth $ d + 1 $ .
- If "s" and "t" are both correct bracket sequences then their concatenation "st" is a correct bracket sequence with depth equal to the maximum depth of $ s $ and $ t $ .

For a (not necessarily correct) bracket sequence $ s $ , we define its depth as the maximum depth of any correct bracket sequence induced by removing some characters from $ s $ (possibly zero). For example: the bracket sequence $ s =  $ "())(())" has depth $ 2 $ , because by removing the third character we obtain a correct bracket sequence "()(())" with depth $ 2 $ .

Given a string $ a $ consists of only characters '(', ')' and '?'. Consider all (not necessarily correct) bracket sequences obtained by replacing all characters '?' in $ a $ by either '(' or ')'. Calculate the sum of all the depths of all these bracket sequences. As this number can be large, find it modulo $ 998244353 $ .

Hacks in this problem in the first division can be done only if easy and hard versions of this problem was solved.

## 说明/提示

In the first test case, we can obtain $ 4 $ bracket sequences by replacing all characters '?' with either '(' or ')':

- "((". Its depth is $ 0 $ ;
- "))". Its depth is $ 0 $ ;
- ")(". Its depth is $ 0 $ ;
- "()". Its depth is $ 1 $ .

So, the answer is $ 1 = 0 + 0 + 0 + 1 $ .

In the second test case, we can obtain $ 4 $ bracket sequences by replacing all characters '?' with either '(' or ')':

- "(((())". Its depth is $ 2 $ ;
- "()()))". Its depth is $ 2 $ ;
- "((()))". Its depth is $ 3 $ ;
- "()(())". Its depth is $ 2 $ .

So, the answer is $ 9 = 2 + 2 + 3 + 2 $ .

## 样例 #1

### 输入

```
??
```

### 输出

```
1
```

## 样例 #2

### 输入

```
(?(?))
```

### 输出

```
9
```

# 题解

## 作者：Soulist (赞：11)

考虑如何统计一个确定的序列的深度

显然应该是考虑最右边的右括号，和最左边的左括号，然后看是否匹配（即满足偏序关系），然后考虑下一个，如此往复。

接下来考虑如果有问号如何统计，我们考虑从一个较小长度的括号序列拓展成为较长的

考虑 dp，设 $dp_{i,j}$ 表示区间 $[i,j]$ 得到的深度和，那么我们需要的答案应该为 $[ 1, n ]$

我们考虑如何从区间$[i,j]$拓展成为区间$[i,j+1]$而同时保证不重复

接下来又是这个套路：

假设区间$[1,n]$中最右的括号为 ```)``` ，只要序列中存在 ```(``` 那么其必然为发生了匹配的括号。

那么对应匹配的括号为 ```(``` ，这两个括号发生了匹配，产生的贡献为$1$，所有我们需要找到第一个 ```(``` ，然后将这两个括号一起删除，假设他们的位置分别为$[u,v]$，则区间$[i,j]$的答案应该为$[u,v]$内部的方案数+$[u,v]$内部的答案

反之如果为 ```(``` 则不用考虑，问题等价于$[1,n-1]$的版本

否则如果为$'?'$就对两种同时进行转移即可

这样就得到了一个$O(n^3)$的 dp 了，因为我们需要枚举```(``` 是谁...主要是因为对于 ? 需要固定其形态

考虑优化，事实上，之前的 dp 我们只利用了一边满足约束的性质，可以这样考虑：假设对于$[i,j]$有$i= ')'$，则答案为$[i+1,j]$，若$j= '('$，则答案为$[i,j-1]$，若$i,j$为$'('$和$')'$，则答案为$[i+1,j-1]+2^{...}$次幂，再否则，答案为$[i+1,j-1]$

事实上，对于有一边为$'?'$的形式，我们只需要如此判断即可，对于$'?'$枚举其形态然后按照此$dp$转移即可

然而这样会出现一个问题那就是大概形如：$?...?$你会惊喜的发现拿两边判是无法转移的，大概是因为$?...?$会枚举得到大概这样的一种形如$)...)$的形式，这个时候直接拿$dp$值加上$[i+1,j]$则是不准确的，因为其涵盖了$j=?$即其为$'(/)'$两种情况同时的 dp 值

于是我们换着考虑，不妨假设 $i$ 处问号变为 $($，则 $j$ 处问号两种情况均可以直接加进去

此时若 $j$ 处问好变成 $($，则 $i$ 处问号可变为$)/($，此时被重复计算的状态为$)....($，于是我们减去其即可

这样就有一个又臭又长的分类讨论来计算dp了

假定两边固定为$')/('$我们进行上述转移即可

否则假定某一个为$'?'$，我们假定另外一个非法（比如右边的左括号），则仍然是上述转移，否则为两种转移

再假定两个均为$'?'$，则按照上述转移，通过大量的分类讨论，我们发现其实$dp$转移可以被缩到一起= =

就有了下面这个转移：

```cpp
	if( s[i] != '(' ) inc( dp[i][j], dp[i + 1][j] ) ;
	if( s[j] != ')' ) inc( dp[i][j], dp[i][j - 1] ) ;
	if( s[i] != '(' && s[j] != ')' ) dec( dp[i][j], dp[i + 1][j - 1] ) ;
	if( s[i] != ')' && s[j] != '(' ) inc( dp[i][j], ( fpow( 2, sum[j - 1] - sum[i] ) + dp[i + 1][j - 1] ) % P ) ; 
```

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int P = 998244353 ; 
const int N = 2000 + 5 ; 
char s[N] ; 
int n, dp[N][N], sum[N], a[N] ;
int fpow( int x, int k ) {
	int ans = 1, base = x ; 
	while( k ) {
		if( k & 1 ) ans = ans * base % P ;
		base = base * base % P, k >>= 1 ;
	} return ans % P ; 
}
void inc( int &x, int y ) {
	( ( x += y ) > P ) && ( x -= P ) ;
}
void dec( int &x, int y ) {
	( ( x -= y ) < 0 ) && ( x += P ) ;
}
signed main()
{
	scanf("%s", s + 1 ), n = strlen( s + 1 ) ;
	rep( i, 1, n ) a[i] = ( s[i] == '(' ? 1 : ( s[i] == ')' ? -1 : 0 ) ), sum[i] = sum[i - 1] + ( a[i] == 0 ) ;
	memset( dp, 0, sizeof(dp) ) ;
	for( re int k = 2; k <= n; ++ k ) {
		for( re int i = 1; i <= n - k + 1; ++ i ) { 
			int j = i + k - 1 ;
			if( s[i] != '(' ) inc( dp[i][j], dp[i + 1][j] ) ;
			if( s[j] != ')' ) inc( dp[i][j], dp[i][j - 1] ) ;
			if( s[i] != '(' && s[j] != ')' ) dec( dp[i][j], dp[i + 1][j - 1] ) ; 
			if( s[i] != ')' && s[j] != '(' ) inc( dp[i][j], ( fpow( 2, sum[j - 1] - sum[i] ) + dp[i + 1][j - 1] ) % P ) ; 
		}
	}
	printf("%lld\n", dp[1][n] ) ;
	return 0 ;
}
```

---

## 作者：letitdown (赞：4)

[双倍经验](https://www.luogu.com.cn/problem/CF1264D2)

我们枚举每两个字符的空档，统计一个空档左边有 $l$ 个左括号，
右边有 $r$ 个右括号，左边有 $u$ 个问号，右边有 $v$ 个括号。

则对于 $p$ 的答案 $ans_p$ 有：

$$ans_p=\sum\limits_{i=0}^{u}(l+i)\dbinom{u}{i}\dbinom{v}{l+i-r}$$

解释：
对于每个左边的问号枚举有几个变成左括号，则左边有 $l+i$ 个左括号，方案数为 $C_{u}^{i}$ ，右边的问号显然有 $l+i-r$ 个变成右括号，则方案数为 $C_{v}^{l+i-r}$ 相乘后求和即可。

弱化版直接暴力加和即可。

对于加强版显然 $n<=1e6$ 直接枚举会 $TLE$ ，于是考虑化简。

$$ans_p=\sum\limits_{i=0}^{u}l\dbinom{u}{i}\dbinom{v}{l+i-r}+\sum\limits_{i=0}^{u}i\dbinom{u}{i}\dbinom{v}{l+i-r}$$

$$ans_p=l\sum\limits_{i=0}^{u}\dbinom{u}{i}\dbinom{v}{v+r-l-i}+\sum\limits_{i=0}^{u}u\dbinom{u-1}{i-1}\dbinom{v}{v+r-l-i}$$

利用范德蒙恒等式得：

$$ans_p=l\dbinom{u+v}{v-l+r}+u\dbinom{u+v-1}{r+v-l-1}$$

于是将所有 $ans$ 相加即可。

## Code
```cpp
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
namespace EMT{
	typedef long long ll;typedef double db;//(double)clock() / (double)CLOCKS_PER_SEC;
	#define pf printf
	#define F(i,a,b) for(register int i=a;i<=b;i++)
	#define D(i,a,b) for(register int i=a;i>=b;i--)
	inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
	inline void file(){freopen("in.in","r",stdin);freopen("my.out","w",stdout);}
	inline int max(int a,int b){return a>b?a:b;}inline int min(int a,int b){return a<b?a:b;}
	inline void pi(int x){pf("%d ",x);}inline void pn(){pf("\n");}
	const int mod=998244353,N=1e6+100;int n,a[N],b[N],c[N],ans,jc[N];char s[N];
	inline int ksm(int a,int b){
		int ans=1;
		while(b){
			if(b&1)ans=1ll*ans*a%mod;
			a=1ll*a*a%mod;
			b>>=1;
		}return ans;
	}
	inline int C(int n,int m){
		if(n<m||m<0)return 0;
		if(!m)return 1;
		return (1ll*jc[n]*ksm(jc[m],mod-2)%mod)*ksm(jc[n-m],mod-2)%mod;
	}
	inline short main(){
		scanf("%s",s+1);n=strlen(s+1);
		F(i,1,n){
			a[i]=a[i-1],b[i]=b[i-1],c[i]=c[i-1];
			if(s[i]=='(')a[i]++;
			if(s[i]==')')b[i]++;
			if(s[i]=='?')c[i]++;
		}jc[0]=1;
		F(i,1,n)jc[i]=1ll*jc[i-1]*i%mod;
		F(i,1,n-1){
			int l=a[i],r=b[n]-b[i],u=c[i],v=c[n]-c[i];
			(ans+=(1ll*l*C(u+v,v-l+r)%mod+1ll*u*C(u+v-1,r+v-l-1)%mod)%mod)%=mod;
		}pi(ans);
		return 0;
	}
}
signed main(){return EMT::main();}
```

---

## 作者：Genius_Star (赞：3)

[或许更好的阅读体验。](https://www.cnblogs.com/rgw2010/p/18371824)

**这篇题解相对于其它题解对小白要友好一些。**

模拟赛题，赛时 sb 了，$n^2$ 都不会。

### 思路：

考虑什么情况下深度最大，容易发现 `(((...)))` 是肯定不劣的。

那么考虑枚举中心点的位置，设左边有 $a$ 个左括号和 $x$ 个问号，右边有 $b$ 个右括号和 $y$ 个问号，然后我们来枚举深度 $i$，求 $i$ 的贡献次数。

要使得深度为 $i$，则要左边新添 $i-a$ 个左括号，右边新添 $i-b$ 个右括号，直接组合数计算贡献：

$$\sum_{i=\min(a,b)}^{\min(a+x,b+y)} \binom{x}{i-a} \binom{y}{i-b} i$$

这样直接算是 $O(N^2)$ 的，可以通过弱化版。

```cpp
int main(){
    init();
    scanf("%s",s+1);
    n=strlen(s+1);
    For(i,1,n){
        if(s[i]==')')
          b++;
        if(s[i]=='?')
          y++;
    }
    For(i,1,n){
        if(s[i]=='(')
          a++;
        if(s[i]=='?')
          x++,y--;
        if(s[i]==')')
          b--;
        l=min(a,b),r=min(a+x,b+y);
        For(j,l,r)
          ans=Add(ans,C(x,j-a)*C(y,j-b)%mod*j%mod);
    }
    write(ans);
	return 0;
}
```

考虑拆式子为：

$$\Big(\sum_{i=0}^{n} \binom{x}{i-a} \binom{y}{i-b} (i-b) \Big)+ \Big(\sum_{i=0}^{n} \binom{x}{i-a} \binom{y}{i-b} b \Big)$$

先看右边的式子，可以用**范德蒙德卷积**。

> **范德蒙德卷积**基本形式：
> $$\binom{n+m}{k} = \sum_{i=0}^k \binom{m}{i} \binom{n}{k-i} $$
> 证明：
> 考虑**组合意义**，在 $n+m$ 个物品中选 $k$ 的方案数，是等价于在 $n$ 个物品中选 $i$ 个且在 $m$ 个物品中选 $k-i$ 个的总方案和的。

现在对于右边的式子：

$$b \sum_{i=0}^{n} \binom{x}{i-a} \binom{y}{i-b} = b \sum_{i=0}^{n} \binom{x}{x+a-i} \binom{y}{i-b}$$

考虑组合意义后可化为：

$$b \binom{x+y}{x+a-b}$$

现在看左边的式子：

$$\sum_{i=0}^{n} \binom{x}{i-a} \binom{y}{i-b} (i-b)$$

注意到：

$$\begin{aligned} \binom{n}{m} m &= \frac{n!m}{m!(n-m)!} \\ &= \frac{n!}{(m-1)!(n-m)!} \\ &= \frac{(n-1)!}{(m-1)!(n-m)!} n \\ &= \binom{n-1}{m-1} n \end{aligned}$$

那么左边式子可以化为：

$$\sum_{i=0}^{n} \binom{x}{i-a} \binom{y-1}{i-b-1} y = y \sum_{i=0}^{n} \binom{x}{x+a-i} \binom{y-1}{i-b-1} $$

后面一串也可以考虑组合意义化简后得：

$$y \binom{x+y-1}{x+a-b-1}$$

则对于 $i$ 这个位置的总贡献为：

$$b \binom{x+y}{x+a-b} + y \binom{x+y-1}{x+a-b-1}$$

现在时间复杂度优化为 $O(N + \log P)$。

**需要提前预处理阶乘和阶乘逆元。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
#define For(i,l,r) for(int i=l;i<=r;i++)
#define _For(i,l,r) for(int i=r;i>=l;i--)
using namespace std;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const ll N=1e6+10,mod=998244353;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll ans;
ll n,l,r,a,b,x,y;
ll f[N],inv[N];
char s[N];
ll qpow(ll a,ll b){
    ll ans=1;
    while(b){
        if(b&1ll)
          ans=(ans*a)%mod;
        a=(a*a)%mod;
        b>>=1ll;
    }
    return ans;
}
void init(){
    f[0]=f[1]=1;
    For(i,2,n)
      f[i]=(f[i-1]*i)%mod;
    inv[n]=qpow(f[n],mod-2);
    _For(i,0,n-1)
      inv[i]=inv[i+1]*(i+1)%mod;
}
ll C(ll n,ll m){
    if(m>n||m<0||n<0)
      return 0;
    if(!m||m==n)
      return 1;
    return f[n]*inv[m]%mod*inv[n-m]%mod;
}
bool End;
int main(){
    scanf("%s",s+1);
    n=strlen(s+1);
    init();
    For(i,1,n){
        if(s[i]==')')
          b++;
        if(s[i]=='?')
          y++;
    }
    For(i,1,n){
        if(s[i]=='(')
          a++;
        if(s[i]=='?')
          x++,y--;
        if(s[i]==')')
          b--;
        ans=Add(ans,(b*C(x+y,x+a-b)%mod+y*C(x+y-1,x+a-b-1)%mod)%mod);
    }
    write(ans);
	return 0;
}
```

---

## 作者：Purslane (赞：2)

# Solution

先看 Easy Version。感觉很唐啊，放在现在的评分体系里面差不多是黄~绿？

把这个括号串删成 `(((...()...)))` 是不劣的（因为你发现并列的结构删掉较劣的肯定问题不大），所以你只需要考虑能找到多长的这种形态的序列。

由于 $\sum_{u \in S} f(u) = \sum_{l=1} \sum_{u \in S} [f(u) \ge l]$，我们就可以把问题转化为判定能不能找到一个长度为 $2len$ 的这种结构。非常贪心的思考，我们找到从左到右的第 $len$ 个左括号，只需要满足他的右边还有 $len$ 个或更多的右括号即可。

于是只需要枚举 $len$ 和第 $len$ 的左括号的位置，记录一下组合数的后缀和即可。复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2000+10,MOD=998244353;
int n,ans,pre[MAXN][3],suf[MAXN][3],C[MAXN][MAXN]; string S;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>S,n=S.size(),S="&"+S;
	ffor(i,0,n) {C[i][0]=1;ffor(j,1,i) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;}
	ffor(i,0,n) roff(j,n,0) C[i][j]=(C[i][j]+C[i][j+1])%MOD;
	ffor(i,1,n) {
		pre[i][0]=pre[i-1][0],pre[i][1]=pre[i-1][1],pre[i][2]=pre[i-1][2];
		if(S[i]=='(') pre[i][0]++; if(S[i]==')') pre[i][1]++; if(S[i]=='?') pre[i][2]++;	
	}
	roff(i,n,1) {
		suf[i][0]=suf[i+1][0],suf[i][1]=suf[i+1][1],suf[i][2]=suf[i+1][2];
		if(S[i]=='(') suf[i][0]++; if(S[i]==')') suf[i][1]++; if(S[i]=='?') suf[i][2]++;	
	}
	ffor(len,1,n/2) ffor(st,1,n) if(S[st]!=')'&&len-1-pre[st-1][0]>=0) {
		int pr=len-1-pre[st-1][0],nx=max(0ll,len-suf[st+1][1]);
		ans=(ans+(C[pre[st-1][2]][pr]-C[pre[st-1][2]][pr+1])%MOD*C[suf[st+1][2]][nx])%MOD;
	}
	cout<<(ans+MOD)%MOD;
	return 0;
}
```

顺便考虑一下 Hard Version 怎么做。

其实也非常简单。考虑我们枚举的那个位置是 $p$，它前面有 $a$ 个左括号和 $b$ 个未确定的位置。它的后面有 $c$ 个右括号和 $d$ 个未确定的位置。

那么枚举 $len$。

$$
\begin{aligned}
& \sum_{len=a+1} \binom{b}{len-1-a} \sum_{t=len-c} \binom{d}{t} \\
= &\sum_{len=a+1} \binom{b}{len-1-a} \sum_{t=len-c} \binom{d}{d-t} \\
= &\sum_{k \le c} \binom{b+d}{k+d-a-1}
\end{aligned}
$$

然后容易发现 $b+d$ 只有两种可能的取值，真的预处理一下就行了。

难度在绿~蓝之间。不知道评分怎么打上去的。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1000000+10,MOD=998244353;
int n,ans,pre[MAXN][3],Suf[MAXN][2],tot,suf[MAXN][3],frac[MAXN],inv[MAXN]; string S;
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
int C(int u,int d) {
	if(u>d) return 0;
	return frac[d]*inv[u]%MOD*inv[d-u]%MOD;	
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>S,n=S.size(),S="&"+S;
	frac[0]=1; ffor(i,1,n) frac[i]=frac[i-1]*i%MOD;
	inv[n]=qpow(frac[n],MOD-2); roff(i,n-1,0) inv[i]=inv[i+1]*(i+1)%MOD;
	ffor(i,1,n) {
		pre[i][0]=pre[i-1][0],pre[i][1]=pre[i-1][1],pre[i][2]=pre[i-1][2];
		if(S[i]=='(') pre[i][0]++;
		if(S[i]==')') pre[i][1]++;
		if(S[i]=='?') pre[i][2]++,tot++;	
	}
	roff(i,n,1) {
		suf[i][0]=suf[i+1][0],suf[i][1]=suf[i+1][1],suf[i][2]=suf[i+1][2];
		if(S[i]=='(') suf[i][0]++;
		if(S[i]==')') suf[i][1]++;
		if(S[i]=='?') suf[i][2]++;	
	}
	Suf[0][0]=Suf[0][1]=1;
	ffor(i,1,n) Suf[i][1]=(Suf[i-1][1]+C(i,tot))%MOD;
	if(tot) ffor(i,1,n) Suf[i][0]=(Suf[i-1][0]+C(i,tot-1))%MOD;
	ffor(i,1,n) if(S[i]!=')') {
		int a=pre[i-1][0],b=pre[i-1][2],c=suf[i+1][1],d=suf[i+1][2],st=max(-1ll,c+d-a-1);
		if(st>=0) ans=(ans+Suf[st][(b+d)-(tot-1)])%MOD;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Link_Cut_Y (赞：2)

可以发现最后任何合法的括号序列都可以删成形如 $\texttt{(((...)))}$ 的形式而最大深度不变（也即每个合法括号序列要想变成最大深度，一定要删成一段 $\texttt{(}$ 拼上一段 $\texttt{)}$ 的形式）。

因此可以 dp。设 $f_{i, j}$ 表示前 $i$ 个字符有 $j$ 个左括号的方案数，$g_{i, j}$ 表示 $i \sim n$ 有 $j$ 个 $)$ 的方案数。$O(n ^ 2)$ 转移即可。

```cpp
f[0][0] = 1;
rep(i, 1, n) rep(j, 0, i) {
	if (s[i] == '(') (f[i][j] += f[i - 1][j - 1]) %= mod;
	if (s[i] == ')') (f[i][j] += f[i - 1][j]) %= mod;
	if (s[i] == '?') (f[i][j] += (j ? f[i - 1][j - 1] : 0) + f[i - 1][j]) %= mod;
}
g[n + 1][0] = 1;
dep(i, n, 1) rep(j, 0, n) {
	if (s[i] == ')') (g[i][j] += (j ? g[i + 1][j - 1] : 0)) %= mod;
	if (s[i] == '(') (g[i][j] += g[i + 1][j]) %= mod;
	if (s[i] == '?') (g[i][j] += (j ? g[i + 1][j - 1] : 0) + g[i + 1][j]) %= mod;
}
rop(i, 1, n) rep(j, 1, n)
	(ans += f[i][j] * g[i + 1][j] % mod * j % mod) %= mod;
```

bonus：本题的组合做法：

枚举最终左右括号的分界位置。设 $[1, i]$ 中有 $s_1$ 个 $\texttt{(}$，$s_2$ 个 $\texttt{?}$；$[i + 1, n]$ 中有 $s_3$ 个 $\texttt{)}$，$s_4$ 个 $\texttt{?}$。那么对于这个分界点，方案数就是：

$$\sum_j \dbinom{s_2}{j - s_1} \dbinom{s_4}{j - s_3} j$$

其中 $j$ 表示枚举的左右括号的数量，$s_1, s_2, s_3$ 可以前缀和。时间复杂度 $O(n ^ 2)$。

```cpp
rep(i, 1, n) s1[i] = s1[i - 1] + (s[i] == '(');
dep(i, n, 1) s2[i] = s2[i + 1] + (s[i] == ')');
rep(i, 1, n) s3[i] = s3[i - 1] + (s[i] == '?');
rep(i, 1, n) fac[i] = fac[i - 1] * i % mod; inv[n] = qpow(fac[n]);
dep(i, n - 1, 1) inv[i] = inv[i + 1] * (i + 1) % mod;

rep(i, 1, n) rep(j, 1, n) {
	int S1 = s1[i], S2 = s3[i];
	int S3 = s2[i + 1], S4 = s3[n] - s3[i];
	ans += C(S2, j - S1) * C(S4, j - S3) % mod * j; ans %= mod;
} write('\n', ans); return 0;
```

---

## 作者：liangbowen (赞：1)

[blog](https://www.cnblogs.com/liangbowen/p/18371843)。写一个题解区没有的蠢做法，不依赖 dp 但是很难转到 Hard Version（

---

对于已经确定的序列，深度有单调性。就是如果答案为 $x$，那么肯定能选出深度为 $1\sim x$ 的子序列。

记 $\operatorname{check}_s(x)$ 表示 check 序列 $s$ 能否选出深度为 $x$ 的子序列。考虑如何 check：

+ 发现形如 $\texttt{((}\cdots\texttt{(())}\cdots\texttt{))}$ 的结构最优。
+ 记 $pre_i$ 表示 $[1,i]$ 中 `(` 的数量，$suf_i$ 表示 $[i,n]$ 中 `)` 的数量，只需满足：$\exists\min(pre_i,suf_{i+1})\ge x$。
+ 找到序列第一个 $pre_i=x$ 的位置，检验是否有 $suf_{i+1}\ge x$ 即可。

显然，对于确定序列有 $\text{ans}_s=\sum\limits_{x=1}^n \operatorname{check}_s(x)$。

回到原问题，枚举 $x=1\sim n$，**权值和转为了计数**：只需计数 $\operatorname{check}_s(x)=1$ 的 $s$ 数量，所有 $x$ 的方案数加起来就行！

最后将上述 $\operatorname{check}_s(x)$ 的过程放到计数上就行：

+ 枚举 $i$，这个 $i$ 需要满足：是序列第一个 $pre_i=x$ 的位置，且有 $suf_{i+1}\ge x$。
+ 若 $s_i=\texttt{(}$，前半段在 $\texttt{?}$ 中凑够左括号数就行，后半段在 $\texttt{?}$ 中凑到 $\ge x$ 就行。有贡献：
$$\binom{\text{前缀 }\texttt{?}\text{ 的数量}}{x-\text{前缀 }\texttt{(}\text{ 的数量}}\times\sum\limits_{x-\text{后缀 }\texttt{)}\text{ 的数量}}^{\text{后缀 }\texttt{?}\text{ 的数量}}\binom{\text{后缀 }\texttt{?}\text{ 的数量}}{i}$$

+ 若 $s_i=\texttt{?}$，前半段稍微改改就行，有贡献

$$\binom{\text{前缀 }\texttt{?}\text{ 的数量}-1}{x-\text{前缀 }\texttt{(}\text{ 的数量}-1}\times\sum\limits_{x-\text{后缀 }\texttt{)}\text{ 的数量}}^{\text{后缀 }\texttt{?}\text{ 的数量}}\binom{\text{后缀 }\texttt{?}\text{ 的数量}}{i}$$

后面 Sigma 的部分可以预处理，然后枚举 $x,i$ 后就能 $O(1)$ 计算。

[code](https://codeforces.com/contest/1264/submission/277466843)，时间复杂度 $O(n^2)$。

---

## 作者：djh0314 (赞：1)

[**传送门**](https://www.luogu.com.cn/problem/CF1264D1)。

## 题意

一个含未知字符的括号序列，一个括号序列的权值是这个括号序列的最大深度。问所有可能的括号序列的权值和为多少。

## 分析

我们寻找一下深度的快速计算方式。

可以发现两个巧妙的性质。

1. 以某一个位置分割，左边的左括号数量和右边的右括号数量的较小值就是这个位置的最大延伸深度。
2. 由于我们的全局最大深度就是所有位置的最大延伸深度的最大值，此时，我们可以发现，此时，我们左边的左括号数应当等于右边右括号的数量。

证明：
1. 将左边的右括号全删，右边的左括号全删，显然最优。
2. 首先，左侧左括号的数量是一个单调递增的函数，右侧右括号的数量是一个单调递减的函数，我们的最大延伸深度就是两个函数的较下的那条线，并且总有一边会变化，且只变化 1，因此，相等处即为最大值。

然后处理问号，我们从性质 2 出手，枚举最大值的分割点，然后再枚举深度，于是就知道了左边的问号有多少个变成左括号，简单的组合就好了。

时间复杂度：$O(n^2)$。

~~~cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6+5;
const int MOD = 998244353;
inline int poww(int x,int y) {
	int res=1;
	while(y) {
		if(y&1) res=res*x%MOD;
		x=x*x%MOD;
		y>>=1;
	}
	return res;
}
int n, m,ans;
char s[N];
int L[N],R[N],qz[N],hz[N],fac[N],inv[N],inf[N];
inline void ADD(int &u,int v) {u=(u+=v)>=MOD?u-MOD:u;}
inline int C(int n,int m) {
	if(n<m) return 0;
	return fac[n]*inv[m]%MOD*inv[n-m]%MOD;
}
signed main() {
	scanf("%s",s+1),n=strlen(s+1);
	fac[0]=inf[1]=inv[1]=inv[0]=1;
	for(int i=1; i<N; ++i) fac[i]=fac[i-1]*i%MOD;
	for(int i=2; i<N; ++i) inf[i]=(MOD-(int)(MOD/i))*inf[MOD%i]%MOD;
	for(int i=2; i<N; ++i) inv[i]=inv[i-1]*inf[i]%MOD;
	for(int i=1; i<=n; ++i) L[i]=L[i-1]+(s[i]=='('),qz[i]=qz[i-1]+(s[i]=='?');
	for(int i=n; i>=1; --i) R[i]=R[i+1]+(s[i]==')'),hz[i]=hz[i+1]+(s[i]=='?');
	for(int i=1; i<n; ++i) {
		int cntl=L[i],cntr=R[i+1],yl=qz[i],yr=hz[i+1];
		for(int j=max(cntl,cntr); j<=min(i,n-i); ++j) ADD(ans,j*C(yl,j-cntl)%MOD*C(yr,j-cntr)%MOD);
	}
	cout<<ans;
	return 0;
}
~~~

---

## 作者：Lates (赞：1)

深度即合法括号匹配子序列中左括号的数目的最大值。

考虑如何计算一个序列的深度。

容易发现，是每次找最左的 $($ 和最右 $)$ 贪心地匹配。

证明我再想想？感觉挺好猜的。

感性理解一下，就是说最左边不和最右边匹配的话，可能导致最右边匹配不上其他的左括号，而且区间大小更小，更难搞到更多匹配。。。比如 $(())$。感觉挺玄乎的。官方题解也没有理性的证明。

---

这样引导一种区间dp的做法。 设 $f_{l,r}$ 表示答案。

- $s_l = ) \ or\  ? $ 或者 $s_r=( \ or \ ?$，那么就是有机会 $l$ 或者 $r$ 对答案没有贡献。

然后注意都满足的时候需要去掉 $f_{l+1,r-1}$。因为多算了一次。

- $s_l = (\ or \ ?$ 且 $s_r = ) \ or \ ?$

如果左端点匹配 $[l+1,r-1]$ 的 $)$，那么违反了贪心策略。

因为时刻取的是最左或者最右的匹配掉。

考虑这样一个匹配，对 $[l+1,r-1]$ 中所有的情况都 $+1$。这个数目是 $2^{t}$，$t$ 是区间 $[l+1,r-1]$ 的 $?$ 数目，这表示每个 $?$ 两种取值。

时间复杂度 $\mathcal{O(n^2)}$。

```cpp
signed main() { 
	cin >> s; n = s.length(); s = ' ' + s;
	for(int i=1;i<=n;++i) p[i] = p[i-1] + (s[i] == '?');
	for(int l=2;l<=n;++l) {
		for(int i=1,j=l;j<=n;++i,++j) {
			if(s[i] != '(') inc(f[i][j], f[i+1][j]);
			if(s[j] != ')') inc(f[i][j], f[i][j-1]);
			if(s[i] != '(' && s[j] != ')') inc(f[i][j], P - f[i+1][j-1]);
			if(s[i] != ')' && s[j] != '(') {
				int v = p[j-1]-p[i];
				inc(f[i][j], f[i+1][j-1]);
				inc(f[i][j], qpow(2, v));
			}
		}
	}
	printf("%d\n", f[1][n]);
	return 0;
}
```

---

## 作者：kcn999 (赞：1)

这里给一个比较简单的 $O(n^2)$ 做法。

假设我们确定了一个只包含 $\texttt(,\texttt)$ 的字符串，那么就相当于要在字符串中找一个位置，该位置左边只保留 $\texttt($，数量为 $x$，该位置右边只保留 $\texttt)$，数量为 $y$，则括号匹配深度为 $\min(x,y)$。

每一个确定的 $\texttt(,\texttt)$ 串对答案的贡献即为最大的 $\min(x,y)$。也就是我们要令 $x=y$。

设 $f(i,j)$ 表示第 $1$ 到 $i$ 位中有 $j$ 个 $\texttt($ 时的方案数，$g(i,j)$ 表示第 $i$ 到 $n$ 位中有 $j$ 个 $\texttt)$ 的方案数。

显然有转移

$$f(i,j)=\begin{cases}f(i-1,j-1) & s_i=\texttt(\\f(i-1,j)&s_i=\texttt)\\f(i-1,j-1)+f(i-1,j) & s_i=\texttt?\end{cases}$$

$$g(i,j)=\begin{cases}g(i+1,j-1) & s_i=\texttt)\\g(i+1,j)&s_i=\texttt(\\g(i+1,j-1)+g(i+1,j) & s_i=\texttt?\end{cases}$$

则答案为 $\sum\limits_{i=2}^n\sum\limits_{j=1}^nf(i-1,j)\times g(i,j)\times j$。


```cpp
#include <bits/stdc++.h>
#define MAX_N (2000 + 5)
using namespace std;
const int mod = 998244353;	
int n;
char str[MAX_N];
int f[MAX_N][MAX_N], g[MAX_N][MAX_N];
int ans;
int main() {
	scanf("%s", str + 1);
	n = strlen(str + 1);
	f[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		if (str[i] == '(' || str[i] == '?')
			for (int j = 1; j <= n; ++j) 
				f[i][j] = (f[i][j] + f[i - 1][j - 1]) % mod;
		if (str[i] == ')' || str[i] == '?')
			for (int j = 0; j <= n; ++j)
				f[i][j] = (f[i][j] + f[i - 1][j]) % mod;
	}
	g[n + 1][0] = 1;
	for (int i = n; i; --i) {
		if (str[i] == ')' || str[i] == '?')
			for (int j = 1; j <= n; ++j) 
				g[i][j] = (g[i][j] + g[i + 1][j - 1]) % mod;
		if (str[i] == '(' || str[i] == '?')
			for (int j = 0; j <= n; ++j)
				g[i][j] = (g[i][j] + g[i + 1][j]) % mod;	
	}
	for (int i = 2; i <= n; ++i)
		for (int j = 1; j <= n; ++j) 
			ans = (ans + (long long)f[i - 1][j] * g[i][j] % mod * j) % mod;
	printf("%d", ans);
	return 0;
}
```

---

## 作者：可爱的小棉羊 (赞：0)

~~哪有黑题放NOIP模拟赛T2，草~~

好的如你所见，这是一道关于括号匹配的题，我们假设已经确定这个括号序列，那么该如何匹配出他的子序列的权值呢？

显然我们要找到一个位置，使得左边的左括号个数，等于右边的右括号个数，注意是相等，可以用 $1$ 分钟想想为什么？

继续思考那么枚举这个位置，考虑左右两边的左右括号个数为 $a,b$，`?` 个数为 $x,y$。

那么答案贡献为：

$$\begin{aligned}\sum_i\binom{x}{i-a}\binom{y}{i-b}i&=\sum_i\binom{x}{i-a}\binom{y}{y-i+b}b+\sum_i \binom{x}{i-a}\binom{y}{i-b}(i-b)\\
&=b\binom{x+y}{y+b-a}+\sum_i \binom{x}{i-a}\binom{y-1}{i-b-1}y\\
&=b\binom{x+y}{y+b-a}+\sum_i \binom{x}{i-a}\binom{y-1}{y-i+b}y\\
&=b\binom{x+y}{y+b-a}+y\binom{x+y-1}{y+b-a}\\
\end{aligned}
$$

我们就有了个 $O(n)$ 的做法。


```cpp
#include<bits/stdc++.h>
using namespace std;
string str;
long long mod=998244353;
long long fpow(long long a,long long b){
	long long ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
long long fac[2000006],n;
long long C(int n,int m){
	if(n<m)return 0;
	if(m<0)return 0; 
	return fac[n]*fpow(fac[m]*fac[n-m]%mod,mod-2)%mod;
}
int cnt1[1000005],cnt2[1000005],cnt3[1000006];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>str;
	n=str.size();
	str=" "+str;
	for(int i=1;i<=n;i++){
		cnt1[i]=cnt1[i-1]+(str[i]=='(');
		cnt2[i]=cnt2[i-1]+(str[i]==')');
		cnt3[i]=cnt3[i-1]+(str[i]=='?');
	}
	long long ans=0;
	fac[0]=1;
	for(int i=1;i<=2*n;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=1;i<n;i++){
		long long a=cnt1[i],b=cnt2[n]-cnt2[i],x=cnt3[i],y=cnt3[n]-cnt3[i];
		
		ans=(ans+b*C(x+y,y+b-a)%mod+y*C(x+y-1,y+b-a)%mod)%mod;
//		cout<<a<<" "<<b<<" "<<x<<" "<<y<<"\n";
	} 

	cout<<ans<<"\n";
	return 0;
}

```

---

## 作者：Larry76 (赞：0)

## 前言

### 数学符号约定：

$\dbinom{n}{m}$：表示 $n$ 选 $m$。

如非特殊说明，将会按照上述约定书写符号。

## 题目分析：

考虑题目的问题弱一点的版本，假设此时我们的括号序列是确定的如何求其括号匹配的最深深度。

如果你有些许 `dp` 基础的话，不难想到如下做法：

> 考虑位置 $i$，将区间 $[1,i]$ 内的 `(` 数量设为 $a_i$，区间 $[i+1,n]$ 内的 `)` 设为 $b_i$，此时答案应该是 $\max_{i\in [1,n]}(\min(a_i,b_i))$。

经过观察，我们发现：$a_i$ 是不断增加的，$b_i$ 是不断减少的。

证明的话考虑 $a_i$ 的区间在不断的扩展，而 $b_i$ 的区间在不断缩小，设扩展前的值为 $a$，则当 $a$ 向外扩展一格的时候只会遇到 `(` 或 `)`，故 $a$ 扩展后的值 $a'$ 只会等于 $a$ 或 $a+1$，故显然 $a_i$ 在过程中是不断增加的。

对于 $b_i$ 的证明同上，在这里不多赘述。

考虑答案式子 $\max_{i\in [1,n]}(\min(a_i,b_i))$，我们可以肯定**当 $a_i = b_i$ 的时候一定会取到最大值**，注意这个条件不是必要的，即最大值的情况不一定是 $a_i = b_i$，但当 $a_i = b_i$ 时一定可以取到最大值，证明可以考虑木桶效应。

让我们继续考虑 $a_i=b_i$ 对应的 $i$ 的情况数量，发现我们有且仅有一种 $i$ 能使得 $a_i = b_i$，证明如下：

假设我们已经到了第一次出现 $a_i = b_i$ 的点了，考虑 $i$ 向下扩展一格会遇到什么，它肯定只会碰到 `(` 或 `)`，如果碰到的是 `(`，则此时 $b_i$ 的值一定不变，因为它对 $b_i$ 没有贡献，但是因为 $a_i$ 多了一个 `(` 所以值会加一。如果碰到的是 `)`，则此时 $b_i$ 的值必定会发生改变。故我们可以的得出，我们的每一次扩展都会必然导致 $a_i$ 或 $b_i$ 产生变化，不存在扩展之后 $a_i$ 和 $b_i$ 都不产生变化的情况。故只有一种 $i$ 能使得 $a_i = b_i$。

现在有了上述的条件我们就能保证我们不会出现算重或算漏的情况了，考虑具体做法：

>枚举 $i$，记 $[1,i]$ 上 `(` 的数量为 $s_1$，记 $[1,i]$ 上 `?` 的数量为 $s_2$，记 $[i+1,n]$ 上 `)` 的数量为 $s_3$，记 $[i+1,n]$ 上 `?` 的数量为 $s_4$，枚举答案 $j$，则当答案为 $j$ 时的贡献就是 $j \dbinom {s_2}{j-s_1} \dbinom {s_4}{j-s_3}$。

那么为什么贡献是这样的呢？或者说 $\dbinom {s_2}{j-s_1}$ 和 $\dbinom {s_4}{j-s_3}$ 的意义是什么呢？根据我们推出的 $a_i = b_i$ 的情况是最大值，考虑我们离当前答案 $j$ 还差多少 `(` 和 `)`，然后将差的数量个问号变成 `(` 和 `)`，然后差的数量显然就是 $j-s_1$ 和 $j - s_3$，而 $\dbinom {s_2}{j-s_1}$ 和 $\dbinom {s_4}{j-s_3}$ 则表示的是 $s_2$ 和 $s_4$ 个问号中选择 $j-s_1$ 和 $j - s_3$ 的方案数（毕竟括号是无标号的）。

考虑预处理一下阶乘和 $s_{1 \cdots 4}$，然后我们就能 $\mathcal O (n^2)$ 的复杂度做完了这个题。

**注意：**

- 你会发现我似乎没有讨论为什么这么扫为什么是合法的，即为什么我们能够保证我们有那么多的 `?` 可选，实际上我们确实无法保证有那么多的 `?` 可选，但是我们可以保证的是，如果没有那么多 `?` 可选，则此时一定不会产生贡献，这一点在我们的组合数中也是有体现的。

  换言之，就是求组合数的时候需要判断一下它会不会是 $0$。

- $0! = 1$。

## 代码实现

这里只给出了关键部分的代码实现，其余部分还恳请读者自己实现：

```cpp
// sum1 表示 `(` 数量的前缀和
// sum2 表示 `)` 数量的前缀和
// sum3 表示 `?` 数量的前缀和
int ans = 0;
for (int i = 1; i <= n; i++) {
    int s1 = sum1[i];
    int s2 = sum3[i];
    int s3 = sum2[n] - sum2[i];
    int s4 = sum3[n] - sum3[i];
    for (int j = 0; j <= n; ++j) {
        ans = add(ans, mul(mul(C(s2, j - s1), C(s4, j - s3)), j));
    }
}
cout << ans << endl;
```

---

## 作者：_OMA_ (赞：0)

对于一个已知的括号序列，发现从头到尾选取匹配的括号删掉，知道不可删为止，删掉的对数便是最终的答案。

考虑从左侧开始选取 $($ 一个个和右侧的 $)$ 开始匹配，最后得到的答案一定是最优。

每种情况删完后，必然是一个合法的括号序列，所以考虑枚举中心点 $p$ ，设 $p$ 左侧的 $($ 数量为 $a$ ，右侧的 $($ 数量为 $b$，$p$ 左侧的 $?$ 数量为 $c$ ，右侧的 $?$ 数量为 $d$ 。

则对于当前中心点 $p$ ，考虑枚举左侧的 $?$ 有 $i$ 个变成了 $($ ，则此时 $($ 有$a+i$ ，选择方案数为 $\tbinom{c}{i}$，右侧则有 $a+i-b$ 个 $?$ 变成了 $)$ ，方案数为 $\tbinom{d}{a+i-b}$ ，相乘求和即是当前点的答案，即为：

$$
ans_{p} = \sum_{i=0}^{c} (a+i) \tbinom{c}{i} \tbinom{d}{a+i-b} 
$$

然而 对于D2强化版 $n\le10^{6}$ ，显然会T。

对式子进行一波化简则有，

$$
\begin{aligned}

ans_{p}&=\sum_{i=0}^{c}a\tbinom{c}{i} \tbinom{d}{a+i-b}+\sum_{i=0}^{c}i\tbinom{c}{i} \tbinom{d}{a+i-b} \\
 &= \sum_{i=0}^{c}a\tbinom{c}{i} \tbinom{d}{d-a-i+b}+\sum_{i=0}^{c}i\tbinom{c}{i} \tbinom{d}{d-a-i+b} \\
&=a\tbinom{c+d}{d-a+b}+\sum_{i=0}^{c} c\tbinom{c-1}{i-1} \tbinom{d}{d-a-i+b}
\end{aligned}
$$

最后用范德蒙恒等式进行化简，

$$
ans_{p}=a\tbinom{c+d}{d-a+b} +c\tbinom{c+d-1}{d-a+b-1}
$$

之后枚举每个中心点 $p$ 累加答案即可。

Code：

``` cpp
#include<cstdio>
#include<cstring>
#define MAX 1000010
#define re register
#define int long long
namespace OMA
{
   int n,ans;
   char s[MAX];
   int jc[MAX],inv[MAX];
   int a[MAX],b[MAX],c[MAX],d[MAX];
   const int p = 998244353;
   inline int quickpow(int a,int b)
   {
     int ans = 1;
     while(b)
     {
       if(b&1)
       { ans = ans*a%p; }
       a = a*a%p;
       b >>= 1;
     }
     return ans;
   }
   inline int C(int n,int m)
   { return m>n||m<0||n<0?0:jc[n]*inv[n-m]%p*inv[m]%p; }
   signed main()
   {
     scanf("%s",s+1);
     n = strlen(s+1);
     jc[0] = inv[0] = 1;
     for(re int i=1; i<=n; i++)
     { jc[i] = i*jc[i-1]%p; }
     inv[n] = quickpow(jc[n],p-2);
     for(re int i=n-1; i; i--)
     { inv[i] = (i+1)*inv[i+1]%p; }
     for(re int i=1; i<=n; i++)
     { a[i] = a[i-1]; if(s[i]=='('){ a[i]++; } c[i] = c[i-1]; if(s[i]=='?'){ c[i]++; } }
     for(re int i=n; i; i--)
     { b[i] = b[i+1]; if(s[i]==')'){ b[i]++; } d[i] = d[i+1]; if(s[i]=='?'){ d[i]++; } }
     for(re int i=1; i<=n-1; i++)
     { (ans += (a[i]*C(c[i]+d[i+1],d[i+1]-a[i]+b[i+1])%p+c[i]*C(c[i]+d[i+1]-1,d[i+1]-a[i]+b[i+1]-1)%p)%p) %= p; }
     printf("%lld\n",ans);
     return 0;
   }
}
signed main()
{ return OMA::main(); }
```


---

