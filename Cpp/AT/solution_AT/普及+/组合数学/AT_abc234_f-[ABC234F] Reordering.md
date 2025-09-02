# [ABC234F] Reordering

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc234/tasks/abc234_f

文字列 $ S $ が与えられます。$ S $ の空でない、**連続するとは限らない**部分列を並び替えて得られる文字列は何種類ありますか？

答えは非常に大きくなる場合があるので、$ 998244353 $ で割ったあまりを出力してください。

## 说明/提示

### 制約

- $ S $ は英小文字のみからなる長さ $ 1 $ 以上 $ 5000 $ 以下の文字列

### Sample Explanation 1

$ S $ の部分列を並び替えて得られる文字列は、`a`, `b`, `aa`, `ab`, `ba`, `aab`, `aba`, `baa` の $ 8 $ 種類です。

### Sample Explanation 3

$ 998244353 $ で割ったあまりを出力することに注意してください。

## 样例 #1

### 输入

```
aab```

### 输出

```
8```

## 样例 #2

### 输入

```
aaa```

### 输出

```
3```

## 样例 #3

### 输入

```
abcdefghijklmnopqrstuvwxyz```

### 输出

```
149621752```

# 题解

## 作者：gesong (赞：5)

题目传送门：[[ABC234F] Reordering](https://www.luogu.com.cn/problem/AT_abc234_f)。
# 思路
看到这类计数类问题，我们可以考虑使用 **dp** 做法。

由于题目可以任意选择一个子序列并且可以任意方法排序，因此题目可以转化为：
> 给定每一个字母的出现次数 $a_i$，求用这些字母随意拼接的方案数。

对于上述问题，我们设 $f_{i,j}$ 表示用字母表的前 $i$ 个字母拼出长度为 $j$ 的字符串的方案数。

转移可以枚举当前字母的所用次数 $k$，即 $f_{i,j}=\sum_{k=0}^{\min(a_i,j)} f_{i-1,j-k}\times C_{j}^k$。

最后的答案即为 $\sum_{i=1}^n f_{26,i}$。

这样我们就得到了一个 $O(26n^2)$ 的做法，可以通过。

记得取模。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5010,mod=998244353;
int f[27][N],a[27],c[N][N];
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
main(){
	string s;cin>>s;int n=s.size();s=" "+s;
	for (int i=1;i<=n;i++) a[s[i]-'a'+1]++;
	c[0][0]=1;
	for (int i=1;i<=n;i++){
		c[i][0]=1;
		for (int j=1;j<=i;j++)
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	}
	f[0][0]=1;
	for (int i=1;i<=26;i++)
		for (int j=0;j<=n;j++)
			for (int k=0;k<=min(j,a[i]);k++)
				f[i][j]=(f[i][j]+f[i-1][j-k]*c[j][k]%mod)%mod;
	int ans=0;
	for (int i=1;i<=n;i++) ans=(ans+f[26][i])%mod;
	cout <<ans;
    return 0;
}

```

---

## 作者：2huk (赞：4)

> 给定一个仅有小写字母的字符串 $S$，你需要求出对于 $S$ 的所有非空子序列，将其任意重排后得到的本质不同的字符串的数量是多少。答案对 $998244353$ 取模。
> 
> $n \le 5000$。

- 一眼丁真，鉴定为 DP。

- 可以发现题目中的“本质不同”不好做，那么就不要用 $S$ 的位置作状态。

- 我们可以换一种角度思考问题：需要构造一个字符串，使得将其重排后是 $s$ 的子序列，求构造的方案数。很显然这两个问题是等价的。

- 可以设状态 $f_{i, j}$ 表示如果只有前 $i$ 种字符，构成的长度为 $j$ 的本质不同字符串有多少。其中这里的字符指的是 $\texttt{a},\texttt{b}, \texttt{c},\texttt{d},\dots$。

- 转移极易。枚举第 $i$ 种字符的出现次数 $k$，然后通过 $f_{i - 1, j - k}$ 转移过来。很显然从总共的 $j$ 个位置中选择 $k$ 个位置填 $i$ 字符的方案数为 $\dbinom jk$，所以转移为：

$$
f_{i, j} = \sum_{k = 0}^{\min(t_i, j)} f_{i -1, j - k} \times \dbinom  jk
$$

- 其中 $t_i$ 表示 $i$ 字符在 $s$ 中出现的次数。

- 答案显然为 $\sum_{i = 1}^n f_{26, i}$，表示长度在 $1 \sim n$ 的子序列的个数。

- 注意取模。[代码](https://www.luogu.com.cn/paste/q9k7p32y)。

---

## 作者：zhanglh (赞：3)

这是 ABC358E 的原题。

考虑 dp。定义 $f_{i,j}$ 表示考虑前 $i$ 种字母，可以组成的长度为 $j$ 的字符串的数量。

对于第 $i$ 种字母，设 $i$ 的最多出现次数为 $t_i$。枚举第 $i$ 个字母的出现次数 $k$，则转移为

$$f_{i,j} = \sum_{k=0}^{\min(t_i,j)} f_{i - 1, j - k} \times \begin{pmatrix} j \\ k \\ \end{pmatrix}$$

答案就是 $\sum_{i=1}^{n} f_{26,i}$。设 $m=26$，时间复杂度 $O(mn^2)$。

```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 5010;
const ll P = 998244353;

char s[N];
int n, t[N];
ll f[27][N], c[N][N];

inline void C() {
    c[0][0] = 1;
    for (int i = 1; i < N; i ++ ) {
        c[i][0] = 1;
        for (int j = 1; j < i; j ++ ) {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % P;
        }
        c[i][i] = 1;
    }
}

int main() {
    cin >> s;
    n = strlen(s);
    for (int i = 0; i < n; i ++ ) t[s[i] - 'a' + 1] ++ ;
    C();
    f[0][0] = 1;
    for (int i = 1; i <= 26; i ++ ) {
        for (int j = 0; j <= n; j ++ ) {
            for (int k = 0; k <= min(t[i], j); k ++ ) {
                f[i][j] = (f[i][j] + f[i - 1][j - k] * c[j][k]) % P;
            }
        }
    }
    ll res = 0;
    for (int i = 1; i <= n; i ++ ) res = (res + f[26][i]) % P;
    cout << res << endl;
    return 0;
}
```

---

## 作者：LengthCheng (赞：2)

# **蒟蒻的第四篇题解**

## [>> ABC234F Reordering](https://www.luogu.com.cn/problem/AT_abc234_f)

## **题目分析**

注意到题目要求的是子序列的重排，不难发现字符的顺序并不重要。那么可先用桶统计每个字符出现的次数，然后考虑 DP。

设 $ num[i] $ 表示第 $ i $ 种字符的个数，$ sum[i] $ 表示前 $ i $ 种字符的个数之和，$ dp[i][j] $ 表示从前 $ i $ 种字符中选出长度为 $ j $ 的排列的数量，得到转移方程 ：

$$

dp[i][j+k] = \sum_{j = 0}^{sum[i-1]} 

             \sum_{k = 0}^{num[i]}

             dp[i-1][j]

             \times

             \begin{pmatrix}
               j+k \\
                 j \\
             \end{pmatrix}

$$

对于这个转移方程，实际上是分别枚举从前 $ i - 1 $ 种字符中选出的字符个数（个数为 $ j $）以及从第 $ i $ 种字符中选出的字符个数（个数为 $ k $），接下来考虑计算选出的两个字符集合并后的排列的数量：

+ 对于合并后长度为 $ j + k $ 的排列，若选出 $ j $ 个位置给大小为 $ j $ 的集合，那么剩下 $ k $ 个位置必然属于大小为 $ j $ 的集合，此时可以用组合数计算，即 
$
\begin{pmatrix}
    j+k \\
      j \\
\end{pmatrix}
$

+ 对于大小为 $ j $ 的集合,其内部可以进行排列，排列数量即为 $ dp[i-1][j] $，而对于大小为 $ k $ 的集合，由于其内部元素都相同，排列数量为一。

+ 将上述式子合并，可得到转移方程。

## **代码实现**

由于转移方程中需要使用组合数，则应先预处理阶乘及阶乘逆元。

计算 $ dp $ 数组时使用三层循环：

+ 第一层循环枚举字符种类，即当前计算到第 $ i $ 种字符。

+ 第二层循环枚举从前 $ i - 1 $ 种字符中选出的字符个数 $ j $。

+ 第三层循环枚举从第 $ i $ 种字符中选出的字符个数 $ k $。

需要注意的时，应先将 $ dp[1][i] $ 初始化为 $ 1 $，即无论从第一种字符中选出几个字符，由于都字符相同，则排列数量都为一。

设 $ S $ 表示原字符串的长度，$ tot $ 表示字符种类的数量，则最后答案即为：

$$ \sum_{i = 1}^{S} dp[tot][i] $$

### **code**

```cpp

#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
map<char,int> mp;
int num[30],tot;
int sum[30];
long long dp[30][5010];
long long fac[5010],fac_inv[5010]; 
int inv(long long a,long long b)
{
	long long ans=1;
	for(;b;b>>=1)
	{
		if(b&1)
		{
			ans=ans*a%mod;
		}
		a=a*a%mod;
	}
	return ans;
}
void init()
{
	fac[0]=fac_inv[0]=1;
	for(int i=1;i<=5000;++i)
	{
		fac[i]=fac[i-1]*i%mod;
		fac_inv[i]=inv(fac[i], mod-2);
	}
}
int main(){
	string s;
	cin>>s;
	init();
	for(int i=0;i<s.size();++i)
	{
		if(!mp[s[i]])
		{
			mp[s[i]]=++tot;
			num[tot]++;
		}
		else
		{
			num[mp[s[i]]]++;
		}
	}
	for(int i=1;i<=tot;++i)
	{
		sum[i]+=sum[i-1]+num[i];
	}
	for(int i=0;i<=num[1];++i)
	{
		dp[1][i]=1;
	}
	for(int i=2;i<=tot;++i)
    {
    	for(int j=0;j<=sum[i-1];++j)
    	{
            for(int k=0;k<=num[i];++k)
            {
			    dp[i][j+k]+=dp[i-1][j]*fac[j+k]%mod*fac_inv[j]%mod*fac_inv[k]%mod;
				dp[i][j+k]%=mod;	
			}
		}
    }
    long long ans=0;
    for(int i=1;i<=s.size();++i)
    {
    	ans+=dp[tot][i];
    	ans%=mod;
	}
    cout<<ans;
}

```


---

## 作者：EastPorridge (赞：2)

昨天深夜从 $\texttt {FFT}$ 学到生成函数，今天深夜刚好碰到可以用 $\texttt {EGF + NTT}$ 做出来的题，激动的眼泪射了出来，写篇题解。

### 题目分析：

$\texttt {做法：生成函数 + NTT}$

原序列长度为 $n$，一个字母在序列中出现了 $m$ 次，则这个字母的生成函数为

$$g(x)=1+x+ \frac {1}{2} x^{2} + \cdots + \frac {1}{(m-1)!}x^{m-1}+ \frac {1}{m!}x^{m}$$

则所有的方案就是 $26$ 个字母的生成函数 $g(x)$ 连乘，记这个多项式的第 $x$ 次项为 $f(x)$，因为题目让求的是子序列的排列方案，所以就是对应的方案的长度再乘上一个对应长度的阶乘，表达出来就是

$$\sum \limits_{i=1}^n i! \times f(i)$$

显然 $26$ 个字母的的生成函数连乘操作可以直接 $\texttt {NTT}$，这个自增的感觉应该可以再分治一下，但我不好说它在这个数据范围下跑得过硬乘的 $\texttt {NTT}$。

### Code.

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int p=998244353,G=3,Gi=332748118,N=5e4+10,M=5000;
inline ll ksm(ll a,ll b) {ll res=1; while(b) {if(b&1ll) res=(res*a)%p; a=(a*a)%p; b>>=1ll;} return res;}
int r[N],cnt[30],lim,l; string s; ll fin[N],ifin[N],sum; vector<ll> pl,tmp,yl;
void ntt(vector<ll> &A,int op)
{
	for(int i=0;i<lim;i++) if(i < r[i]) swap(A[i],A[r[i]]);
	for(int mid=1;mid<lim;mid<<=1)
	{
		ll wn=ksm(~op ? G : Gi,(p-1)/(mid<<1));
		for(int R=mid<<1,j=0;j<lim;j+=R)
		{
			ll w=1;
			for(int k=0;k<mid;k++,w=(w*wn)%p)
			{
				int x=A[j+k],y=w*A[j+mid+k]%p;
				A[j+k]=(x+y)%p; A[j+mid+k]=(x-y+p)%p;
			}
		}
	}
}
void NTT()
{
	int kl=pl.size()+tmp.size()-1;
	lim=1; l=0; while(lim < kl) lim<<=1,l++; ll inv=ksm(lim,p-2);
	for(int i=0;i<lim;i++) r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	pl.resize(lim); tmp.resize(lim);
	ntt(pl,1); ntt(tmp,1); for(int i=0;i<lim;i++) pl[i]=(pl[i]*tmp[i])%p; ntt(pl,-1);
	for(int i=0;i<=kl;i++) pl[i]=(pl[i]*inv)%p; pl.resize(kl);
}
int main()
{
	cin>>s; 
	yl.resize(M+1); fin[0]=1; for(int i=1;i<=M;i++) fin[i]=(fin[i-1]*i)%p;
	ifin[M]=ksm(fin[M],p-2); for(int i=M;i>=1;i--) ifin[i-1]=(ifin[i]*i)%p;
	for(int i=0;i<=M;i++) yl[i]=ifin[i];
	for(auto it : s) cnt[it-'a']++; pl=yl; pl.resize(cnt[0]+1);
	for(int i=1;i<26;i++)
	{
		if(! cnt[i]) continue ; 
		tmp.resize(M+1); tmp=yl; tmp.resize(cnt[i]+1);
		NTT();
	}
	for(int i=1;i<(int)pl.size();i++) sum=(sum+pl[i]*fin[i]%p)%p;
	printf("%lld",sum);
	return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

# 思路
一眼 Dp，我们定义状态 $f_{i,j}$ 为用了前 $i$ 个字符，组成的长度为 $j$ 的方案数，这里的 $i$ 个字符是指 a，b，c，d，e 这样的字符。那么我们对于一个字符 $c$ 我们自然有 $j-1$ 个空可以插入然后我们一共需要插入 $k$ 个 $c$ 所以我们可得状态转移方程 $f_{i,j
}=f_{i-1,j-k}\times \binom{j}{k}$ 这里我们只需要预处理出来组合技术即可。
# 代码
```cpp
#include <bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(fasle);cin.tie(NULL);cout.tie(NULL)
#define int long long
#define ri register int
#define rep(i,x,y) for(ri i=x;i<=y;i++)
#define rep1(i,x,y) for(ri i=x;i>=y;i--)
#define il inline
#define fire signed
#define pai(a,x,y) sort(a+x,a+y+1)
using namespace std ;
const int N=5e3+10,mod=998244353;
il int qmi(int a,int b) {
	int res=1;
	while(b) {
		if(b&1) res=(res*a)%mod;
		a=a*a;
		a%=mod;
		b>>=1;
	}
	return res;
}
void read(int &x) {
	x=false;
	ri f=1;
	char c=getchar();
	while(c>'9'||c<'0') {
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c-'0'<=9&&c>='0') {
		x=x*10+c-'0';
		c=getchar();
	}
	x*=f;
}
void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
#define gcd(x,y) __gcd(x,y)
#define lcm(x,y) x*y/gcd(x,y)
int inv[1000000+11],fac[1000011];
string s;
int f[N][30];
int C(int j,int k) {
	if(j<k) return 0;
	return ((fac[j]*inv[k])%mod*inv[j-k])%mod;
}
int t[30];
fire main() {
	cin>>s;
	int l=s.size();
	fac[0]=1;
	rep(i,1,1000000) fac[i]=(fac[i-1]*i)%mod;
	inv[1000000]=qmi(fac[1000000],mod-2);
	rep1(i,1000000-1,0) inv[i]=inv[i+1]*(i+1)%mod;
	rep(i,0,l-1) t[s[i]-'a'+1]++;
	f[0][0]=1;
	rep(j,0,l) rep(i,1,26) rep(k,0,min(t[i],j)) (f[j][i]+=(f[j-k][i-1]*C(j,k)%mod))%=mod;
	int res=0;
	rep(i,1,l) {
		res=(res+f[i][26])%mod;
	}
	print(res);
	return false;
}

```

---

## 作者：yr409892525 (赞：0)

### 题解：AT_abc234_f [ABC234F] Reordering
可以转换成 [AT_abc358_e [ABC358E] Alphabet Tiles](https://www.luogu.com.cn/problem/AT_abc358_e) 这题。               
每个字符可以选取 $0\sim C_i$ 个，可以使用背包 DP。                           
定义 $f_{i,j}$ 代表在前 $i$ 个字符中选取 $j$ 个字符的方案数。                             
由于长度不固定，所以答案 $\sum_{i=1}^n f_{n,i}$。                         
枚举第 $i$ 个字符选取的个数 $0\le k\le C_i$，得到 $f_{i,j}$ 从 $f_{i-1,j-k}$ 转移。                   
将 $k$ 个字符插入 $j$ 个字符中，方案数为 $C_j^k$，所以 $f_{i,j}=\sum_{k=0}^{\min(j,C_i)} f_{i-1,j-k}\times C_j^k$。                              
初始将 $dp_{0,0}=1$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5005,mod=998244353;
string s;
int n,a[N];
int dp[N],f[N][N];
signed main(){
	cin>>s;
	n=s.size();
	for(int i=0;i<n;i++){
		a[s[i]-'a'+1]++;
	}
	dp[0]=f[1][1]=1;
	for(int i=2;i<=n+1;i++){
		for(int j=1;j<=i;j++){
			f[i][j]=(f[i-1][j]+f[i-1][j-1])%mod;
		}
	}
	for(int i=1;i<=26;i++){
		for(int j=n;j>=1;j--){
			for(int k=max(0ll,j-a[i]);k<j;k++){
				dp[j]=(dp[j]+dp[k]*f[j+1][k+1])%mod;
			}
		}
	}
	int sum=0;
	for(int i=1;i<=n;i++){
		sum=(sum+dp[i])%mod;
	}
	cout<<sum<<"\n";
	return 0;
}
```

---

## 作者：Ak_hjc_using (赞：0)

dp 加上组合数做法，很好写，双倍经验：AT_abc358_e（一个需要自己求出 $c_i$，另一个给定了 $c_i$）。

简化题意，给定每一个字符的出现次数，求出其可以组成的字符串总数（相同字符交换算做同一种方案），设计状态为 $f_{i,j}$，表示使用前 $i$ 个字符拼成的字符串长度为 $j$ 的方案总数，由于 $|s| \le 5000$，所以可以使用 $O(n^2)$ 加上一个字符总数的常数的时间复杂度通过本题，转移就是使用组合数的方法，先枚举当前 $i$ 这个字符的使用个数 $k$，然后的转移为 $f_{i,j} = \sum_{k = 0}^{min(a, j)} f_{i-1,j-k}\times C_ {j}^{k}$（即从上一个字符表中拼成的长度为 $j-k$ （因为当前的长度为 $j$）乘上从 $j$ 个位置中选择出 $k$ 个字符变成当前字符）。

组合数可以通过逆元求出（当然由于数据范围原因也可以使用杨辉三角）。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 5001, kM = 998244353;

int a[27], n;
long long f[27][kMaxN], c[kMaxN][kMaxN], ans;
string s;

int main() {
  cin >> s, n = s.size();
  for (int i = 0; i < n; i++) {  // 统计字符个数
    a[s[i] - 'a' + 1]++;
  }
  c[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    c[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % kM;
    }
  }
  f[0][0] = 1;
  for (int i = 1; i <= 26; i++) {                                   // 当前字符
    for (int j = 0; j <= s.size(); j++) {                           // 当前拼出的字符串长度
      for (int k = 0; k <= min(j, a[i]); k++) {                     // 当前字符使用的个数
        f[i][j] = (f[i][j] + f[i - 1][j - k] * c[j][k] % kM) % kM;  // 转移
      }
    }
  }
  for (int i = 1; i <= n; i++) {  // 拼成的长度
    ans = (ans + f[26][i] % kM) % kM;
  }
  cout << ans << '\n';
  return 0;
}
```

---

## 作者：WorldMachine (赞：0)

既然要重排，设字符 $i$ 出现次数为 $c_i$，那么所得到的子串就是第 $i$ 个字符选择不超过 $c_i$ 个排列所得到的不同子串个数。

想了下生成函数没搞出来，还是自己太菜（

先来考虑最基础的 dp。

设 $f_{i,j}$ 为前 $i$ 个字符拼 $j$ 位的方案数，有：
$$
f_{i,j}=f_{i-1,j}+\sum_{k=1}^{\min(j,c_i)}f_{i-1,j-k}\cdot\binom jk
$$
意思就是指定 $k$ 个字符插到 $j$ 个可能的位置里。

这样就可以直接 $\mathcal O(n^2|\Sigma|)$ 做，其中 $|\Sigma|$ 为字符集大小。

这有点不牛，考虑优化。

设字符 $i$ 选 $x_i\ (x_i\leq c_i)$ 个，则拼成长度 $n$ 的方案数为：
$$
\sum_{\sum x=n}\dfrac{n!}{x_1!x_2!\dots x_{26}!}
$$
那么字符 $i$ 的生成函数为：
$$
f_i(x)=\sum_{j=0}^{c_i}\dfrac{x^j}{j!}
$$
这样就能做到 $\mathcal O(n\log n|\Sigma|)$。

---

## 作者：Saint_ying_xtf (赞：0)

[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)。

第一步：想到 Dp，毕竟方案数，百分之九十九都是 Dp。

第二步：思考一些问题，首先 $s$ 这个字符串的顺序肯定不重要，毕竟重排和子序列，想到与随机取几个。所以说我们可以分类取，相当于就是计算这个字符取几个，另一个字符去几个，按顺序取，这么想会更好做。

第三步：先用桶存储出来每一个字符的数量。

第四步：考虑什么 Dp？想到计数 Dp。转移方程为 $dp_{i,j}$ 代表选了前 $i$ 个字母，长度为 $j$。

第五步：如何转移？$dp_{i,j} = dp_{i,j} + dp_{i-1,j-k} \times C_j^k$。此处的 $C$ 为组合数。$k$ 为这个字母取了多少个。理解一下为啥是这样：你如果不选这种字母，那么就是原来本身的贡献，如果选了，就是 $dp_{i-1,j-k} \times C_j^k$，在之前的贡献转移过来要乘一个组合数，相当于要把这个 $k$ 个字母放到最后对应的位置上，相当于是一个组合数来计算。

组合数我们可以通过 $C_n^m = C_{n-1}^{m} + C_{n-1}^{m-1}$ 来转移，其实就是杨辉三角。因为 $n \le 5000$ 所以 $O(n^2)$ 时间复杂度可以通过，~~之所以我为什么不想题解区里人一样都用逆元啥的来搞，因为我数论菜的要死。。。~~

[link](https://atcoder.jp/contests/abc234/submissions/49198575)。

---

## 作者：gxp123 (赞：0)

# abc234 F - Reordering  题解

[atcoder 链接](https://atcoder.jp/contests/abc234/tasks/abc234_f)

[luogu 链接](https://www.luogu.com.cn/problem/AT_abc234_f)

## 题意

给定一个仅有小写字母的字符串 $S$，你需要求出对于 $S$ 的所有**非空子序列**。

将其任意重排后得到的本质不同的字符串的数量是多少。

$|S|\le 5000$

## 题解

因为是任意重排，我们只关心每个字符的数量。

所以我们记录一下每个字符的数量。

对于当前字符 $i$ 假设我们已经求出了只用前 $i-1$ 种字符的所有方案数。

假设我们当前枚举用第 $k$ 个字符，和已经凑出的长度为 $j$ 的方案组合，可以获得那些新方案的数量。

因为只有小写字母，所以只有 $26$ 种。

显然就是从我们拼凑出来的 $j + k$ 个位置中，选出 $k$ 个来放上我们的字符，剩下的按照按照原来长度为 $j$ 的字符串中的顺序放上。

所以我们可以获得以下 $dp$。

我们记 $f_{i,j}$ 表示当前在用第 $i$ 种，总长度为 $j$ 。

则

$$
f_{i,j + k} = \sum\limits_{j=0}^{sumh_i}\sum\limits_{k=0}^{a_i} f_{i-1,j} \times C_{j + k}^k
$$

其中 $sumh_i$ 表示前 $i$ 个字符的总和，$a_i$ 表示第 $i$ 种字符的数量。

对于组合数，我们预处理一下即可。

初始状态 $f_{0,0} = 0$ 。

**注：第一种字符代表小写字母 `a`。**

答案就是 $\sum\limits_{j=0}^{|S|} \ f_{26,j}$  。

时间复杂度：$O(|S|^2)$

## code

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

typedef long long ll;
const int maxN = 5000 + 10;
const int mod = 998244353;
int qpow(int a,int k){
    int res = 1;
    while(k){
        if(k & 1)   res = 1ll * res * a % mod;
        a = 1ll * a * a % mod;
        k = k >> 1;
    }
    return res;
}
char s[maxN];
int n,a[27],f[27][maxN],sumh[27];   
int jc[maxN],jcv[maxN];

int C(int n,int m){
    if(n < m)   return 0;
    return 1ll * jc[n] * jcv[m] % mod * jcv[n - m] % mod;
}

int main(){
    jc[0] = 1;
    for(int i = 1 ; i <= 5000 ; ++i)    jc[i] = 1ll * jc[i - 1] * i % mod;
    jcv[5000] = qpow(jc[5000],mod - 2);
    for(int i = 4999 ; i >= 0 ; --i)    jcv[i] = 1ll * jcv[i + 1] * (i + 1) % mod;
    scanf("%s",s + 1);
    n = strlen(s + 1);
    for(int i = 1 ; i <= n ; ++i){
        a[s[i] - 'a' + 1] ++;
    }
    for(int i = 1 ; i <= 26 ; ++i)
        sumh[i] = sumh[i - 1] + a[i];
    ll ans = 0;
    f[0][0] = 1;
    for(int i = 1 ; i <= 26 ; ++i){
        for(int j = 0 ; j <= sumh[i - 1] ; ++j){
            for(int k = 0 ; k <= a[i] ; ++k){
                f[i][j + k] = (1ll * f[i - 1][j] * C(j + k,k) % mod + f[i][j + k]) % mod;
            }
        }
    
    for(int i = 1 ; i <= n ; ++i)
        ans = (ans + f[26][i]) % mod;
    cout << ans << endl;
    return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

## 思路

考虑 $dp_{i,j}$ 表示看了前 $i$ 个字母，目前总共选出长度为 $j$ 的方案数。

考虑转移，枚举第 $i$ 个字母选 $k$ 个，则 $dp_{i,j+k}+=dp_{i-1,j}\times\binom{j+k}{k}$，意义就是从总共的 $j+k$ 个位置中选择 $k$ 个放置第 $i$ 号字母，剩余按原来顺序摆放 $dp_{i-1,j}$ 的状态。

那么总复杂度就是 $O(26|S|^2)$，可以通过。

具体实现方面，我们可以先预处理出组合数，然后计算原串每个字母出现的次数，进行上述 $dp$ 即可，注意及时取模

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
const int maxn=1000000;
int fact[maxn+5];
int inv[maxn+5];
int power(int a,int b){
	int now=a,ans=1;
	while(b){
		if(b%2==1){
			ans*=now;
			ans%=mod;
		}
		now*=now;
		now%=mod;
		b/=2; 
	}
	return ans;
}
void init(){
	fact[0]=1;
	for(int i=1;i<=maxn;i++){
		fact[i]=fact[i-1]*i;
		fact[i]%=mod;
	}
	inv[maxn]=power(fact[maxn],mod-2);
	for(int i=maxn-1;i>=0;i--){
		inv[i]=inv[i+1]*(i+1);
		inv[i]%=mod;
	}
}
int C(int i,int j){
	if(i<j){
		return 0;
	}
	return ((fact[i]*inv[j])%mod*inv[i-j])%mod;
}
int C2(int i,int j){
	if(i<j){
		return 0;
	}
	return ((inv[i]*fact[j])%mod*fact[i-j])%mod;
}
int dp[5005][28];
signed main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	init();
	string s;
	cin>>s;
	int a[27];
	for(int i=0;i<=26;i++){
		a[i]=0;
	}
	for(int i=0;i<s.size();i++){
		a[s[i]-'a'+1]++;
	} 
	dp[0][0]=1;
	for(int i=1;i<=26;i++){
		for(int j=0;j<=s.size();j++){
			for(int k=0;k<=a[i]&&k<=j;k++){
				dp[j][i]+=((dp[j-k][i-1]*C(j,k))%mod);
				dp[j][i]%=mod;
			}
		}
	}
	int sum=0;
	for(int i=1;i<=s.size();i++){
		sum+=(dp[i][26]%mod);
		sum%=mod;
	}
	cout<<sum;
	return 0;
}
```

---

