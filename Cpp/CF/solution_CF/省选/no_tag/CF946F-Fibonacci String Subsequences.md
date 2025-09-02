# Fibonacci String Subsequences

## 题目描述

You are given a binary string $ s $ (each character of this string is either 0 or 1).

Let's denote the cost of string $ t $ as the number of occurences of $ s $ in $ t $ . For example, if $ s $ is 11 and $ t $ is 111011, then the cost of $ t $ is $ 3 $ .

Let's also denote the Fibonacci strings sequence as follows:

- $ F(0) $ is 0;
- $ F(1) $ is 1;
- $ F(i)=F(i-1)+F(i-2) $ if $ i&gt;1 $ , where $ + $ means the concatenation of two strings.

Your task is to calculate the sum of costs of all subsequences of the string $ F(x) $ . Since answer may be large, calculate it modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
2 4
11
```

### 输出

```
14
```

## 样例 #2

### 输入

```
10 100
1010101010
```

### 输出

```
553403224
```

# 题解

## 作者：GIFBMP (赞：5)

#### 正题

容易想到设 $f_{i,j,k}$ 表示在串 $F(i)$ 的子序列中，原串中区间 $[j,k]$ 作为子串出现的次数之和。

则 $f_{i,j,k}$ 可能包含两种情况：一种是子序列全部在 $F(i-1)$ 或 $F(i-2)$ 中，一种是子序列跨越两端。

先讨论后一种情况，可以得出转移：

$$f_{i,j,k}=\sum_{l=j}^{k-1}f_{i-1,j,l}\times f_{i-2,l+1,k}$$

然后讨论前一种情况。先讨论子序列全部位于 $F(i-1)$ 中的情况，我们发现当 $k=n$ 时由于 $[j,n]$ 已经被全部包含，因此在 $F(i-2)$ 中的字符可以随便选。否则不能选，不然可能会算重。设 $len_i$ 表示 $F(i)$ 的长度，则有：

$$f_{i,j,k}=
\begin{cases} 
f_{i-1,j,k}\times 2^{len_{i-2}}&k=n\\
f_{i-1,j,k}&k\ne n
\end{cases}$$

对于子序列全部位于 $F(i-2)$ 的情况，同理可得：

$$f_{i,j,k}=
\begin{cases} 
f_{i-2,j,k}\times 2^{len_{i-1}}&j=1\\
f_{i-2,j,k}&j\ne 1
\end{cases}$$

初值：$f_{0,i,i}=[s_i=0]$，$f_{1,i,i}=[s_i=1]$。

最终答案即为 $f_{x,1,n}$。

时间复杂度：$O(xn^3)$。

Code：
```cpp
#include <cstdio>
#include <cstring>
using namespace std ;
const int MAXN = 110 , mod = 1e9 + 7 ;
typedef long long ll ;
ll f[MAXN][MAXN][MAXN] , fib[MAXN] , pw[MAXN] ;
int n , m ;
char s[MAXN] ;
ll qpow (ll x , ll p) {
	ll ret = 1 ;
	for (; p ; p >>= 1 , x = x * x % mod)
		if (p & 1) ret = ret * x % mod ;
	return ret ;
}
int main () {
	scanf ("%d%d" , &n , &m) ;
	scanf ("%s" , s + 1) ;
	fib[0] = fib[1] = 1 ; pw[0] = pw[1] = 2 ;
	for (int i = 2 ; i <= m ; i++)
		fib[i] = (fib[i - 1] + fib[i - 2]) % (mod - 1) , pw[i] = qpow (2 , fib[i]) ;
	for (int i = 1 ; i <= n ; i++)
		f[0][i][i] = (s[i] == '0') , f[1][i][i] = (s[i] == '1') ;
	for (int i = 2 ; i <= m ; i++) {
		for (int j = 1 ; j <= n ; j++)
			for (int k = j ; k <= n ; k++) {
				f[i][j][k] = (f[i][j][k] + f[i - 1][j][k] * ((k == n) ? pw[i - 2] : 1) % mod) % mod ;
				f[i][j][k] = (f[i][j][k] + f[i - 2][j][k] * ((j == 1) ? pw[i - 1] : 1) % mod) % mod ;
				for (int l = j ; l < k ; l++)
					f[i][j][k] = (f[i][j][k] + f[i - 1][j][l] * f[i - 2][l + 1][k] % mod) % mod ;
			}
	}
	printf ("%lld\n" , f[m][1][n]) ;
	return 0 ;
}
```

---

## 作者：wwldx (赞：2)

分析题意，询问字符串s出现在F(X)次数，而我们都知道子序列可以是不连续的，所以我们可以通过拼接串串来做

设dp[i][l][r]，i代表是F(i)，l和r分别是字符串的子串S1 l~r
那么易得dp[i][l][r]肯定有一部分可以dp[i-1][l][r]和dp[i-2][l][r]中获得
正常直接dp[i][l][r]+=dp[i-1][l][r]以及dp[i-2][l][r]即可
但需要特判2种情况，第一种l==1，也就是在dp[i-2][l][r]包含的就是子串S1 l~r的全部了，前面的随便取多少个都不影响后面的

所以这个时候就是dp[i] [l] [r]+= dp[i-2] [l] [r] * (2 ^ lenth[i-1])，同理，假如r==n，也就是在dp[i-1]阶段就已经有子串S1 l~r的全部了，后面的随便取
dp[i][l][r]+=dp[i-1] [l] [r] * (2^lenth[i-2])

2^lenth这步每次都要乘，并且lenth不短，假如每次都重新算，要用快速幂优化
所以我们完全可以预处理一下，把2^lenth放在len数组里，用的时候直接拿

然后就是可以把一个子串拆分成2个分子串

所以dp[i][l][r]+=dp[i-1][l][k]+dp[i-1][k+1][r]，k的范围是[ l , r )，记得取余
这题就做完了，具体的可以看代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<n;i++)
#define per(i,a,n) for(int i=n-1;i>=a;i--)
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef vector<int> VI;
const ll mod=1000000007;
const int maxn=200;
const int inf=0x3f3f3f3f;
const int INF=0x7f7f7f7f;
ll gcd(ll a,ll b){ return b?gcd(b,a%b):a;}
#define ms(a) memset(a,0,sizeof(a))
#define mss(a) memset(a,-1,sizeof(a))
#define msi(a) memset(a,inf,sizeof(a))
#define iossync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
// head
ll pow_(ll x,ll y)
{
    ll rt=1;
    while (y){
        if (y&1) rt=rt*x%mod;
        x=x*x%mod; y>>=1;
    }
    return rt;
}
//unsigned 
ll dp[maxn][maxn][maxn],n,m,len[maxn];
string s1;
void init()
{
	#define num len
	num[0]=2;
	num[1]=2;
	rep(i,2,m+1)
	num[i]=num[i-1]*num[i-2]%mod;
	#undef num
}
int main()
{
	
	cin>>n>>m;
	init();//预处理2^len 
	cin>>s1;
	rep(i,1,n+1)
	{//l==r
		dp[s1[i-1]-'0'][i][i]=1;
		//先确定1和0的位置 
	}
	rep(i,2,m+1)
	{
		rep(l,1,n+1)
		{
			rep(r,l,n+1)
			{
				//一般情况直接加就好 
//				dp[i][l][r]+=dp[i-1][l][r]+dp[i-2][l][r];
				if(r==n)//特判r 
				(dp[i][l][r]+=dp[i-1][l][r]*len[i-2]%mod)%=mod;
				else
				(dp[i][l][r]+=dp[i-1][l][r])%=mod;
				if(l==1)//特判l 
				(dp[i][l][r]+=dp[i-2][l][r]*len[i-1])%=mod;
				else
				(dp[i][l][r]+=dp[i-2][l][r])%=mod;
				rep(k,l,r)
				{
					(dp[i][l][r]+=dp[i-1][l][k]*dp[i-2][k+1][r])%=mod;
				 } 
			}
		}
	}
	cout<<dp[m][1][n]<<"\n";
	return 0;
}
```


---

## 作者：Drind (赞：1)

### 题目解析

求 $s$ 在斐波那契串 $f_i$ 的每个子序列中的出现次数。

首先我们想到一个 dp 就是设 $g_{i,l,r}$ 为 $s_{[l,r]}$ 在 $f_i$ 所有子序列中的出现次数。

然后转移很简单，就是左边的加右边的加中间合并的。

如果在中间合并，就是：

$$g_{i,l,r}\gets \sum_{j=l}^{r-1}g_{i-1,l,j}\times g_{i-2,j+1,r}$$

如果只在左边，那么如果已经匹配完了，即 $r=n$，就能在右边随便选，否则不行。

$$g_{i,l,r}\gets \begin{cases}g_{i-1,l,r}\times 2^{len_{i-2}} & [r=n]\\g_{i-1,l,r} & [r\neq n]\end{cases}$$

如果只在右边同理。

$$g_{i,l,r}\gets \begin{cases}g_{i-2,l,r}\times 2^{len_{i-1}} & [l=1]\\g_{i-2,l,r} & [l\neq 1]\end{cases}$$

答案就是 $g_{x,1,n}$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e2+10;
const int p=1e9+7;
inline int _abs(int x){if(x>0) return x;return -x;}

int qpow(int a,int index){
	int ans=1;
	while(index){
		if(index&1) ans=ans*a%p;
		a=a*a%p; index>>=1;
	}
	return ans;
}

int len[N],base[N];
int f[N][N][N];

void fake_main(){
	int n,x; cin>>n>>x; string s; cin>>s;
	len[0]=len[1]=1; base[0]=base[1]=2;
	for(int i=2;i<=x;i++){
		len[i]=(len[i-1]+len[i-2])%(p-1);
		base[i]=qpow(2,len[i]);
	}
	
	for(int i=1;i<=n;i++){//初始状态，就是匹配 f0 和 f1，注意这两个斐波那契串长度为 1 所以匹配上的 s 的子串长度也只能是 1.
		f[0][i][i]=(s[i-1]=='0');
		f[1][i][i]=(s[i-1]=='1');
	}
	
	for(int i=2;i<=x;i++){
		for(int j=1;j<=n;j++){
			for(int k=j;k<=n;k++){
				f[i][j][k]=(f[i][j][k]+f[i-1][j][k]*((k==n)?base[i-2]:1)%p)%p;
				f[i][j][k]=(f[i][j][k]+f[i-2][j][k]*((j==1)?base[i-1]:1)%p)%p;
				for(int r=j;r<k;r++){
					f[i][j][k]=(f[i][j][k]+f[i-1][j][r]*f[i-2][r+1][k]%p)%p;
				}
			}
		}
	}
	
	cout<<f[x][1][n]<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}
```

---

## 作者：EuphoricStar (赞：0)

duel 的时候差点不会 2400 了。

套路地，考虑每个 $F(x)$ 中与 $s$ 相同的子序列的贡献。设这个子序列为 $F(x)_{p_1}, F(x)_{p_2}, F(x)_{p_3}, \ldots, F(x)_{p_n}$。

我们想要它成为一个子序列的子串，那么 $F(x)_{[p_1, p_n]}$ 中除了 $p_1 \sim p_n$ 就不能有别的字符被选。而 $[1, p_1 - 1] \cup [p_n + 1, |F(x)|]$ 中的每个字符都可以选或不选，相当于每个字符产生 $2$ 的贡献。

如果我们设 $f_{i, j}$ 为考虑到 $F(x)$ 的第 $i$ 位，匹配到 $s$ 的第 $j$ 位的答案，那么相当于 $f_{i + 1, 0} \gets 2 f_{i, 0}, f_{i + 1, n} \gets 2 f_{i, n}, \forall j \in [1, n - 1], f_{i + 1, j} \gets f_{i, j}, \forall j \in [1, n] \land F(x)_i = s_j, f_{i + 1, j} \gets f_{i, j - 1}$。答案即为 $f_{|F(x)|, n}$。

可以用矩阵刻画这个转移过程。设 $F_i$ 为 $F(i)$ 的转移矩阵，那么 $F_i = F_{i - 1} F_{i - 2}$。

时间复杂度 $O(n^3x)$。

[code](https://codeforces.com/contest/946/submission/229525363)

---

## 作者：linyihdfj (赞：0)

## CF946F Fibonacci String Subsequences
想要更优质的阅读体验，就来[这里](https://www.cnblogs.com/linyihdfj/p/16893607.html)吧。
### 题目分析：
可以发现，我们其实可以使用合并的思想去看这个题，就是啥意思呢。

我们在 $F(i)$ 内的方案数，其实就是在 $F(i-1)$ 里的方案数加在 $F(i-2)$ 里的方案数加横跨 $F(i-1)$ 和 $F(i-2)$ 的方案数。
就考虑怎么做可以做到处理横跨的这种情况。

显然可以想到一个 $dp$，就是设 $f[i][j][k]$ 表示在 $F(i)$ 中 $[j,k]$ 这个子串作为其某一个子序列的子串的次数。

讨论转移也是上面这个想法。

考虑全在 $F(i-1)$ 中的怎么算，直接就是 $f[i-1][j][k]$ 吗？显然不是。

因为多加了一个 $F(i-2)$，所以其实对于这里面的数我们可以随便选，所以是 $f[i-1][j][k] \times 2^{len_{i-2}}$（这里设 $len_i$ 代表 $F(i)$ 的长度）吗？

因为只有当 $k=n$ 的时候我们对于 $F(i-2)$ 才没有什么限制，否则是有限制，所以综合就是这个式子：

$$
f[i][j][k] = 
\begin{cases}
f[i-1][j][k] \times 2^{len_{i-2}} &k = n \\
f[i-1][j][k] & k \not= n
\end{cases}
$$

而对于全部在 $F(i-2)$ 中也是同理，就不多分析了，直接给出结论：

$$
f[i][j][k] = 
\begin{cases}
f[i-2][j][k] \times 2^{len_{i-1}} &j = 1\\
f[i-1][j][k] &j \not= 1
\end{cases}
$$

然后就是考虑跨区间的情况，其实也是很简单的：

$$
f[i][j][k] = \sum_{p = j}^{k-1} f[i-1][j][p] \times f[i-2][p+1][k]
$$

初值也非常简单啦，$f[0][i][i] = [s[i] = 0],f[1][i][i] = [s[i] = 1]$
### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 1e9+7;
const int N = 205;
int f[N][N][N],len[N],pw[N];
char s[N];
int mod(int x){
	return x % MOD;
}
void add(int &x,int y){
	y = mod(y);
	x = mod(x + y);
}
int power(int a,int b){
	int res = 1;
	while(b){
		if(b & 1)	res = mod(res * a);
		a = mod(a * a);
		b >>= 1;
	}
	return res;
}
signed main(){
	int n,x;
	scanf("%lld%lld",&n,&x);
	scanf("%s",s+1);
	len[0] = len[1] = 1;
	pw[0] = 2,pw[1] = 2;   //pw 直接记录对应的答案 
	for(int i=2; i<=x; i++){
		len[i] = (len[i-1] + len[i-2]) % (MOD - 1);   //卧槽？？欧拉定理 
		pw[i] = power(2,len[i]);
	}
	for(int i=1; i<=n; i++){
		f[0][i][i] = (s[i] == '0');
		f[1][i][i] = (s[i] == '1');
	}
	for(int i=2; i<=x; i++){
		for(int j=1; j<=n; j++){
			for(int k=j; k<=n; k++){
				add(f[i][j][k],f[i-1][j][k] * (k == n ? pw[i-2] : 1));
				add(f[i][j][k],f[i-2][j][k] * (j == 1 ? pw[i-1] : 1));
				for(int p = j; p < k; p++){
					add(f[i][j][k],f[i-1][j][p] * f[i-2][p+1][k]);
				}
			}
		}
	}
	printf("%lld\n",f[x][1][n]);
	return 0;
}
```

---

