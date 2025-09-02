# [ABC194F] Digits Paradise in Hexadecimal

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc194/tasks/abc194_f

この問題において、十六進表記では `0` ~ `9`, `A` ~ `F` を数字として扱い、`A` ~ `F` はそれぞれ十から十五を表すものとします。  
 また、特別の記述がない限り問題文中で扱われる数は全て十進表記されているものとします。

$ 1 $ 以上 $ N $ 以下の整数のうち、先頭に $ 0 $ のない十六進表記で書くとちょうど $ K $ 種類の数字が現れるようなものはいくつあるでしょうか ?  
 $ 10^9\ +\ 7 $ で割ったあまりを出力してください。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \lt\ {16}^{2\ \times\ 10^5} $
- $ N $ は先頭が `0` でない十六進表記で与えられる
- $ 1\ \le\ K\ \le\ 16 $
- 入力に含まれる値は全て整数

### Sample Explanation 1

$ N $ は十六進表記で与えられているため、十進数に直すと $ 16 $ です。 $ 1 $ 以上 $ 16 $ 以下の整数を、先頭に $ 0 $ のない十六進表記で書くと下記のようになります。 - $ 1 $ から $ 15 $ まで : 十六進表記に直すと $ 1 $ 桁なので、出現する数字は $ 1 $ 種類である - $ 16 $ : 十六進表記に直すと $ 10 $ なので、出現する数字は $ 2 $ 種類である よって、十六進表記に直した時に出現する数字が $ 1 $ 種類なのは $ 15 $ 個です。

### Sample Explanation 2

出現する数字が $ 2 $ 種類なのは、$ 1 $ 以上 $ 255 $ 以下の $ 255 $ 個の整数のうち、十六進表記で $ 1,\ 2,\ 3,\ \dots,\ \mathrm{E},\ \mathrm{F},\ 11,\ 22,\ 33,\ \dots,\ \mathrm{EE},\ \mathrm{FF} $ と表される $ 15\ +\ 15\ =\ 30 $ 個を除いたものです。

### Sample Explanation 5

答えを $ 10^9\ +\ 7 $ で割った余りを出力してください。

## 样例 #1

### 输入

```
10 1```

### 输出

```
15```

## 样例 #2

### 输入

```
FF 2```

### 输出

```
225```

## 样例 #3

### 输入

```
100 2```

### 输出

```
226```

## 样例 #4

### 输入

```
1A8FD02 4```

### 输出

```
3784674```

## 样例 #5

### 输入

```
DEADBEEFDEADBEEEEEEEEF 16```

### 输出

```
153954073```

# 题解

## 作者：igAC (赞：5)

# $\text{Description}$

[洛谷 link](https://www.luogu.com.cn/problem/AT_abc194_f)

[ATlink](https://atcoder.jp/contests/abc194/tasks/abc194_f)

简要题意：

给定一个十六进制数 $n$，求 $[1,n]$ 中有多少个十六进制数恰好有 $k$ 个不同的数位。

# $\text{Solution}$

数位 dp 模板题。

注意到十六进制只有十六种不同的数位，于是可以把他们压缩成一个二进制数存储，方便转移。

然后就可以直接莽数位 dp，设 $f_{i,j}$ 表示枚举到第 $i$ 位，当前不同位数个数为 $j$ 的数字个数。

这里给出记忆化搜索的实现。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define N 200005
#define Mod 1000000007
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,k,a[N],f[N][20],ans;
string s;
int dfs(int now,int s,bool lim){
	if(__builtin_popcount(s)>k) return 0;
	if(now==n+1) return __builtin_popcount(s)==k;
	if(!lim && ~f[now][__builtin_popcount(s)]) return f[now][__builtin_popcount(s)];
	int res=0,t=lim?a[now]:15;
	for(int i=0;i<=t;++i) res=(res+dfs(now+1,s|(1<<i),lim && i==t)%Mod)%Mod;
	if(!lim) f[now][__builtin_popcount(s)]=res;
	return res;
}
int main(){
	cin>>s;n=s.length(),s=" "+s,k=read();
	memset(f,-1,sizeof(f));
	for(int i=1;i<=n;++i){
		if(isdigit(s[i])) a[i]=s[i]-48;
		else a[i]=s[i]-55;
	}
	for(int i=1;i<=n;++i){
		int lim=(i==1)?a[i]:15;
		for(int j=1;j<=lim;++j) ans=(ans+dfs(i+1,1<<j,i==1 && j==lim)%Mod)%Mod;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：MadokaKaname (赞：3)

## 前言

洛谷唯一的题解似乎是 $O(nk^2)$ 的，~~怎么卡过去的orz~~

这里提供一种与 AT 官方题解时间复杂度相同的 $O(nk)$ 做法。

## Solution

题意很显然，就不解释了。

一眼丁真，考虑数位 dp。

设 $dp_{i,j}$ 表示做到第 $i$ 位，不同的个数有 $j$ 种的方案数。

显然有转移方程：

$dp_{i,j}=dp_{i-1,j}\times j +dp_{i-1,j-1} \times (16-j-1)$

边界为 $dp_{1,1}=15$。

分类讨论，考虑存在前导 0 与不存在前导 0。

当前导 0 存在时，由于每种方案中最高位数字的方案数是相等的，因此显然总方案数为 $\frac{15}{16}\sum_{i=1}^{n}dp_{i,k}$。

而当不存在时，将数字分为已出现过和未出现过两种，分别计算个数。

两种唯一的区别为已钦定选择的数字个数。则在第 $i$ 位时，若前面已有 $x$ 个数已被选，方案数为 $\binom{16-x}{k-x} \times \sum_{j=k-x}^{\min(n-i,k)} \frac{dp_{n-i,j}\times\binom{x}{j-k+x}}{\binom{16}{j}}$，具体可以用组合意义推导得到。

~~应该还可以再化简，但是这样就已经能做了。~~

实际实现的时候由于组合数的上下标不超过 16，因此可以提前预处理。

## code

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
LL n,i,j,k,m,tmp1,tmp2,tmp3,ans=0;
LL mod=1000000007;
LL val[17],C[17][17],invC[17][17],dp[200005][17];
string s;
bool flag[17];
void exgcd(LL a,LL b,LL &x,LL &y,LL &val){
	if(b==0){
		val=a;
		x=1;
		y=0;
	}
	else{
		exgcd(b,a%b,y,x,val);
		y-=x*(a/b);
	}
}
LL doit(char ch){
	if(ch>='0' && ch<='9') return ch-'0';
	else return ch-'A'+10;
}
LL inv(LL x){
	tmp1=0,tmp2=0,tmp3=0;
	exgcd(x,mod,tmp1,tmp2,tmp3);
	return (tmp1+mod)%mod;
}
int main() {
    val[0]=1;
    for(i=1;i<=16;i++){
    	val[i]=val[i-1]*i%mod;
    	val[i]%=mod;
	}
	for(i=1;i<=16;i++)
	  for(j=0;j<=i;j++)
	    C[i][j]=val[i]*inv(val[i-j])%mod*inv(val[j])%mod;
	for(i=1;i<=16;i++)
	  for(j=0;j<=i;j++)
	    invC[i][j]=inv(C[i][j]);
	cin>>s>>k;
	n=s.length();
	dp[0][0]=1;
	dp[1][1]=16;
	C[0][0]=1;
	invC[0][0]=1;
	for(i=2;i<=n;i++)
	  for(j=1;j<=16;j++){
	  	dp[i][j]=(dp[i-1][j]*j%mod+dp[i-1][j-1]*(16-(j-1))%mod);
	  	dp[i][j]%=mod;
	  }
	for(i=1;i<n;i++){
		ans+=(dp[i][k]*inv(16)%mod*15ll%mod)%mod;
		ans%=mod;
	}
	ans+=((dp[n-1][k-1])*1ll*C[15][k-1]%mod*invC[16][k-1]%mod+(dp[n-1][k]*1ll*C[15][k-1]%mod*invC[16][k])%mod)%mod*(doit(s[0])-1)%mod;
	ans%=mod;
	LL sum1,sum2,now=1;
	flag[doit(s[0])]=true;
	for(i=1;i<s.length();i++){
		sum1=0,sum2=0;
	    for(j=0;j<doit(s[i]);j++){
	    	if(flag[j]==true){
	      	    sum1++;
		    }
		    else sum2++;
		}
		for(j=k-now;j<=k;j++){
			ans+=sum1*dp[n-i-1][j]%mod*C[16-now][k-now]%mod*C[now][j-(k-now)]%mod*invC[16][j]%mod;
			ans%=mod;
		}
		if(now+1<=k){
			for(j=k-now-1;j<=k;j++){
				ans+=sum2*dp[n-i-1][j]%mod*C[16-now-1][k-now-1]%mod*C[now+1][j-(k-now-1)]%mod*invC[16][j]%mod;
				ans%=mod;
			}
		}
		if(flag[doit(s[i])]==false) now++;
	    flag[doit(s[i])]=true;
	    if(now>k) break;
	}
	if(now==k) ans++;
	printf("%lld",ans%mod);
	  
	return 0;
}

```






---

## 作者：大眼仔Happy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc194_f)

感觉有紫的难度。

显然数位 dp，但是发现直接做的时间复杂度是 $O(n 2 ^ k)$，爆炸了。

注意到我们虽然要求不同的数字，但是其实并不需要具体知道是哪些数字。

然后一个 trick 就是，由于不顶格之后可以随便选择，所以应该是可以快速计算的。

> 顶格指前缀相等，或者熟悉的 ${\rm lim} = 1$。

---

考虑 $N = \rm 0xFFFF...$ 的特殊情况，这时候相当于没有限制。

我们设 $g_{i, j}$ 表示考虑了 $i$ 位，有 $j$ 个不同数位的方案数。

这是一个很简单的 dp，有 $g_{i, j} = g_{i - 1, j}\times j + g_{i - 1, j - 1}\times (16 - j + 1)$，$g_{1, 1} = 16$。

注意到这个 dp 实际上计算了前导 $0$，而不同高位的答案其实是一样的，所以答案应该为 $\frac{15}{16}\sum g_{i, k}$。

---

接着加上设 $f_i$ 表示考虑到第 $i$ 位并且前 $i - 1$ 位顶格，后面的位置随便填的答案。

然后枚举第 $i$ 位，于是我们就知道了前 $i$ 位的状态 $T$（注意这一位不顶格）。

现在我们已经知道了左边（$[1, i]$ 位）的不同位数为 $a = {\rm popcount}(T)$，可以枚举右边（$[i + 1, n]$ 位）不同的位数 $b$，那么就有重复的 $a + b - k$ 个数是同时存在于左右两边。考虑从左边选出 $a + b - k$ 个数作为两者都有的，方案数为 ${a\choose a + b - k}$，然后再从剩下的 $16 - a$ 个数选 $k - a$ 个数作为右边独有的，这样就确定了右边具有哪些数字。因为是确定的数字，所以乘上方案数 $g_{n - i, b}$ 之后还要除以组合总数 ${16\choose b}$。

个人感觉这个组合数有点难想明白，可以动手画一下。

注意到每一位情况下，$a$ 最多加一，所以只需要把 $a$ 和 $a + 1$ 的答案算出来即可。

具体看看代码，时间复杂度 $O(nk)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
#define ll long long
const ll mod = 1e9 + 7; 
#define popcnt __builtin_popcount
int inline read() {
	int num = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		num = (num << 3) + (num << 1) + (ch ^ 48);
		ch = getchar();
	}
	return num * f;
}
int n, k, S, a[N];
ll ans;
char s[N];
void binc(ll &x, const ll &y) { x += y; if(x >= mod) x -= mod; }
ll inc(const ll &x, const ll &y) {ll res = x + y; if(res >= mod) res -= mod; return res; }
ll qp(ll a, ll b) {
	ll res = 1;
	while(b) {
		if(b & 1) res *= a, res %= mod;
		a *= a, a %= mod, b >>= 1; 
	}
	return res; 
}
ll C[17][17], iC[17][17], g[N][17];
void init() {
	g[0][0] = 1;
	for(int i = 1; i <= n; i++) 
		for(int j = 1; j <= 16; j++)
			g[i][j] = (g[i - 1][j] * j + g[i - 1][j - 1] * (16 - j + 1)) % mod;
	for(int i = 0; i <= 16; i++) {
		C[i][0] = iC[i][0] = 1;
		for(int j = 1; j <= i; j++) {
			C[i][j] = inc(C[i - 1][j - 1], C[i - 1][j]);
			iC[i][j] = qp(C[i][j], mod - 2);
		}
	}
}
int main() {
	scanf("%s", s + 1), n = strlen(s + 1); 
	for(int i = 1; i <= n; i++) {
		if(s[i] >= 'A') a[i] = s[i] - 'A' + 10;
		else a[i] = s[i] ^ 48; 
	}
	k = read(), init();
	for(int i = 1; i < n; i++) binc(ans, g[i][k]);
	ans *= 15, ans *= qp(16, mod - 2), ans %= mod; 
	for(int i = 1; i <= n; i++) {
		ll s0 = 0, s1 = 0;
		int L = popcnt(S);
		if(L <= k) {
			for(int R = k - L; R <= k; R++) 
				s0 = (s0 + g[n - i][R] * C[L][L + R - k] % mod * iC[16][R]) % mod; 
			s0 *= C[16 - L][k - L], s0 %= mod; 
		} else break;
		L++;
		if(L <= k) {
			for(int R = k - L; R <= k; R++)
				s1 = (s1 + g[n - i][R] * C[L][L + R - k] % mod * iC[16][R]) % mod; 
			s1 *= C[16 - L][k - L], s1 %= mod; 
		}
		for(int j = (i == 1 ? 1 : 0); j < a[i]; j++) {
			if((S >> j) & 1) binc(ans, s0);
			else binc(ans, s1);
		}
		S |= (1 << a[i]);
	}
	if(popcnt(S) == k) binc(ans, 1);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

比较好的计数题目。

先不考虑前导 $0$。

考虑数位 dp，我们先枚举答案与上界的最长公共前缀，假若这其中出现了 $x$ 个数，我们再枚举后面填的数与前面出现的数的交集大小 $d$，假若后面还要填 $cl$ 种数，问题变成选出 $cl$ 个数填入长度为 $n - lcp$ 的数组中，且必须在给定的集合中挑选 $d$ 个必须选择，$x - d$ 个不选择的方案数。

考虑一层层的剥开我们要计数的东西的结构，首先对于一个有 $p$ 种数的数组，我们给其中出现的 $p$ 种数排序去重后依次替换为一个长度为 $p$ 的排列，并将替换后的值代入原数组，显然 $16 \choose p$ 个数组对应了一个新的数组，并且确定了新的数组的出现的数集合便可以还原出原来的数组。不妨先进行一遍 $dp$ 求出原数组个数，在除以 $16 \choose p$ 求出新的数组个数。

然后对于我们要计数的东西，考虑选取数组中出现的数的集合的方案是 ${16 \choose {16-(x-d)-d}} \times {x \choose d}$，用这个再乘上 dp 计数的结果即可得到方案数。

去除前导 $0$ 是简单的，不难发现前导 $0$ 会让出现了 $k-1$ 种不同数的方案被多算并让出现了 $k$ 种不同的数的方案被少算，考虑有前导 $0$ 时一定是若干前导 $0$ 加上一个没有填数限制的剩余数组，再做一遍值域范围为 $[1,15]$ 的 dp 即可。

一般的数位 dp 需要枚举当前考虑位填什么，但是这里注意到后面的限制只跟前面填的数的种类有关，所以只需要计算当前填的数使得填过的数种类增加或者不变的方案数作为转移的系数即可。

令 $n$ 表示位数，时间复杂度是 $O(n \times k)$，记得预处理组合数。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5+114;
const int mod = 1e9+7;
int dp[maxn][20];//i 位填 j 种数填法
int n,k;
int S[maxn];
string s;
int fac[maxn];
int inv[maxn];
int Inv[20][20],a[20][20];
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a;
    int res=qpow(a,b/2);
    res=res*res%mod;
    if(b%2==1) res=res*a%mod;
    return res;
}
int C(int n,int m){
    if(m>n) return 0;
    return fac[n]*inv[n-m]%mod*inv[m]%mod;
}
int vis[20],cnt;
int ans;
signed main(){
    fac[0]=1;
    inv[0]=1;
    for(int i=1;i<maxn;i++) fac[i]=fac[i-1]*i%mod,inv[i]=qpow(fac[i],mod-2);
    for(int i=0;i<20;i++)
        for(int j=0;j<20;j++) Inv[i][j]=qpow(C(i,j),mod-2);
    cin>>s>>k;
    n=s.size();
    for(int i=0;i<n;i++) S[i+1]=((s[i]>='A'&&s[i]<='Z')?s[i]-'A'+10:s[i]-'0');
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=16;j++){
            dp[i][j]=dp[i-1][j]*j%mod;
            dp[i][j]=(dp[i][j]+dp[i-1][j-1]*(16-j+1)%mod)%mod;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=16;j++) dp[i][j]=dp[i][j]*Inv[16][j]%mod;
    }
    //先认为前导 0 也算
    for(int i=1;i<=n;i++){
        //前 i-1 位相同 枚举第 i 位
        int cnt1=0,cnt0=0;
        for(int j=0;j<S[i];j++){
            if(cnt+(vis[j]==0?1:0)>k) continue;
            if(vis[j]==0) cnt1++;
            else cnt0++;
        }
        if(cnt1!=0){
            for(int d=0;d<=min(cnt+1,k);d++){//枚举与已经填了的部分的颜色交
                int cl=k-(cnt+1-d);//填了 cl 种颜色
                //有 d 种确定的出现过了
                int ban=(cnt+1)-d;//有 ban 种确定的颜色一定没有出现
                //再乘上 选出 d(ban) 的方案数
                //大小为 cl 的集合，其选择的颜色实际上是从 16-ban-d 种中选择 cl-d 种
                int tm=C(16-ban-d,cl-d)*C(d+ban,d)%mod;
                ans=(ans+dp[n-i][cl]*tm%mod*cnt1%mod)%mod;
            }
        }
        if(cnt0!=0){
            for(int d=0;d<=min(cnt,k);d++){//枚举与已经填了的部分的颜色交
                int cl=k-(cnt-d);//填了 cl 种颜色
                //有 d 种确定的出现过了
                int ban=(cnt)-d;//有 ban 种确定的颜色一定没有出现
                //再乘上 选出 d(ban) 的方案数
                //大小为 cl 的集合，其选择的颜色实际上是从 16-ban-d 种中选择 cl-d 种
                int tm=C(16-ban-d,cl-d)*C(d+ban,d)%mod;
                ans=(ans+dp[n-i][cl]*tm%mod*cnt0%mod)%mod;
            }
        }
        vis[S[i]]++;
        if(vis[S[i]]==1) cnt++;
    }
    if(cnt==k) ans=(ans+1)%mod;
    //下面两种情况计算时需要去除 0 需要重新 dp 一遍
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=15;j++){
            dp[i][j]=dp[i-1][j]*j%mod;
            dp[i][j]=(dp[i][j]+dp[i-1][j-1]*(15-j+1)%mod)%mod;
        }
    }
    //那么会将 k-1 种颜色算成 k 种，容斥掉
    for(int i=1;i<=n;i++){
        //有 i 个前导 0
        ans=(ans+mod-dp[n-i][k-1])%mod;
    }
    //也会将 k 种颜色算成 k+1 种，补回来
    for(int i=1;i<=n;i++){
        ans=(ans+dp[n-i][k])%mod;
    }
    cout<<ans<<'\n';
    return 0;
}
/*
AFD 2
494
*/
```

---

