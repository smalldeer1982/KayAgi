# Twin Friends

## 题目描述

You meet two new friends who are twins. The name of the elder twin is $ A $ , which consists of $ N $ characters. While the name of the younger twin is $ B $ , which consists of $ M $ characters. It is known that $ N \leq M $ .

You want to call each of them with a nickname. For the elder twin, you want to pick any permutation of $ A $ as the nickname. For the younger twin, you want to remove exactly $ M - N $ characters from any permutation of $ B $ . Denote the nicknames of the elder twin and the younger twin as $ A' $ and $ B' $ , respectively.

You want the nicknames to satisfy the following requirement. For each $ i $ that satisfies $ 1 \leq i \leq N $ , $ B'_i $ must be equal to either $ A'_i $ or the next letter that follows alphabetically after $ A'_i $ (if such a next letter exists).

Determine the number of different pairs of nicknames $ (A', B') $ that satisfy the requirement. Two pairs of nicknames are considered different if at least one of the nicknames are different. As the result might be large, find the answer modulo $ 998\,244\,353 $ .

## 说明/提示

Explanation for the sample input/output #1

The $ 9 $ pairs are:

- (AAM, AAN),
- (AAM, ABN),
- (AAM, BAN),
- (AMA, ANA),
- (AMA, ANB),
- (AMA, BNA),
- (MAA, NAA),
- (MAA, NAB), and
- (MAA, NBA).

Explanation for the sample input/output #2

The $ 120 $ pairs are the pairs where $ A' $ is a permutation of BINUS and $ B' = A' $ .

## 样例 #1

### 输入

```
3 4
AMA
ANAB```

### 输出

```
9```

## 样例 #2

### 输入

```
5 8
BINUS
BINANUSA```

### 输出

```
120```

## 样例 #3

### 输入

```
15 30
BINUSUNIVERSITY
BINANUSANTARAUNIVERSITYJAKARTA```

### 输出

```
151362308```

## 样例 #4

### 输入

```
4 4
UDIN
ASEP```

### 输出

```
0```

# 题解

## 作者：Register_int (赞：5)

小脑已经萎缩了所以做点计数。

要求所有不同的 $(A',B')$ 很困难，我们不妨先固定住 $A$ 有序再往里面填 $B$。设 $dp_{i,j}$ 为 $A'$ 已经放完了前 $i$ 个字母，还有 $j$ 个 $i+1$ 没被配对的方案数。有转移：

$$dp_{i+1,a_i-j}=\dbinom{a_i}j\sum^{b_i-j}_kdp_{i,k}$$

其中，$a_i,b_i$ 分别表示第 $i$ 个字母在 $A,B$ 之中的个数。本式的含义是，将 $a_i$ 个 $i$ 全部插入 $A'$ 末尾，枚举其中 $k$ 个用来匹配上一次 $B$ 剩下的 $i$。朴素转移是 $O(n^2)$ 的，用前缀和优化可以做到 $O(n)$。

然后来统计答案。我们有了 $A'$ 有序的方案数，那么直接乘上 $A$ 的所有不同排列的方案数即可。答案为：

$$dp_{26,0}\times\dfrac{n!}{\prod_ia_i!}$$

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;
const int mod = 998244353;

inline 
ll qpow(ll b, ll p) {
	ll res = 1;
	for (; p; p >>= 1, b = b * b % mod) if (p & 1) res = res * b % mod;
	return res;
}

ll fac[MAXN], ifac[MAXN];

inline 
void init(int n) {
	*fac = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	for (int i = n; i; i--) ifac[i - 1] = ifac[i] * i % mod;
}

inline 
ll c(int n, int m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int n, m; char s[MAXN], t[MAXN];

int a[27], b[27]; ll dp[27][MAXN], sum[27][MAXN], ans;

int main() {
	scanf("%d%d%s%s", &n, &m, s, t), init(n), **dp = 1;
	for (int i = 0; i < n; i++) a[s[i] - 'A']++;
	for (int i = 0; i < m; i++) b[t[i] - 'A']++;
	for (int i = 0; i < 26; i++) {
		sum[i][0] = dp[i][0];
		for (int j = 1; j <= b[i]; j++) sum[i][j] = (sum[i][j - 1] + dp[i][j]) % mod;
		for (int j = 0; j <= a[i] && j <= b[i]; j++) {
			dp[i + 1][a[i] - j] = sum[i][b[i] - j] * c(a[i], j) % mod;
		}
	}
	ans = dp[26][0] * fac[n] % mod;
	for (int i = 0; i < 26; i++) ans = ans * ifac[a[i]] % mod;
	printf("%lld", ans);
}
```

---

## 作者：Hoks (赞：4)

## 前言
比较有意思的技术 dp 题~~差点没想到~~。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842#information)。
## 思路分析
首先注意题意，排序是**随便怎么排**都可以的，所以我们考虑直接把每位字母个数剥下来排列组合算。

那么这样就可以得到两个数组 $cnta,cntb$ 分别表示字符串 $A,B$ 中字母的出现次数。

但题目又有一个特殊的条件：$b_i'$ 可以与 $a_i'$ 的下一位字母相等。

考虑设计 $f_{i,j}$ 表示用到了第 $i$ 个字母并且用了 $j$ 个下一位字母的方案数。

这样就可以得到转移方程 $f_{i,j}=\sum\limits_{k=0}^{cntb_i-cnta_i+j}f_{i-1,k}\times\tbinom{cnta_i}j$。

具体原因即为对于 $A$ 中的第 $i$ 个字符，考虑用 $j$ 个他后一位的字符和他匹配，剩下的用 $B$ 中的第 $i$ 个字符匹配。

但这样复杂度是 $O(n^2)$ 的，稳稳挂飞。

不难发现当 $j\rightarrow j+1$ 时，$k$ 的枚举范围 $cntb_i-cnta_i+j\rightarrow cntb_i-cnta_i+j+1$，也就是我们重复计算了大量相同的 $f_{i-1,k}$，前缀和优化即可。

令 $s_{i,j}=\sum\limits_{k=0}^j f_{i,k}$，新的转移方程式即为：$f_{i,j}=s_{i-1.cntb_i-cnta_i+j}\times\tbinom{cnta_i}j$。

对于组合数，预处理阶乘即可~~当然预处理逆元后会跑的更快~~。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,mod=998244353,INF=0x3f3f3f3f3f3f3f3f,lim=20;
int n,l,ans,cnta[27],cntb[27],fac[N],f[N],s[N];char t[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='A'&&c<='Z'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline int ksm(int x,int y,int mod)
{
    int res=1;
    while(y){if(y&1) res=res*x%mod;x=x*x%mod;y>>=1;}
    return res;
}
inline int c(int x,int y){return fac[y]*ksm(fac[y-x],mod-2,mod)%mod*ksm(fac[x],mod-2,mod)%mod;}
signed main()
{
    read();read();rd(t,n);for(int i=1;i<=n;i++) cnta[t[i]-'A'+1]++;
    rd(t,l);for(int i=fac[0]=1;i<=l;i++) cntb[t[i]-'A'+1]++,fac[i]=fac[i-1]*i%mod;
    for(int j=0;j<=cntb[1];j++) s[j]=1;ans=fac[n];
    for(int i=1;i<=26;i++)
    {
        for(int j=max(0ll,cnta[i]-cntb[i]);j<=min(cnta[i],cntb[i+1]);j++) f[j]=s[cntb[i]-(cnta[i]-j)]*c(j,cnta[i])%mod;
        s[0]=f[0];for(int j=1;j<=cntb[i+1];j++) s[j]=s[j-1]+f[j],s[j]%=mod;
        for(int j=max(0ll,cnta[i]-cntb[i]);j<=min(cnta[i],cntb[i+1]);j++) f[j]=0;
        ans=ans*ksm(fac[cnta[i]],mod-2,mod)%mod;
    }
    print((s[0]*ans)%mod);
    genshin:;flush();return 0;
}
```

---

## 作者：qiuzijin2026 (赞：4)

# CF1906H Twin Friends

[题面](https://www.luogu.com.cn/problem/CF1906H)

## 思路

首先我们可以发现 $A$ 的顺序其实无关紧要，只需要把 $A$ 固定后算出方案数后乘上 $A$ 的不同排列数就是最后的答案了。

于是，问题就变成了固定 $A$ 求满足要求的 $B$ 的数量。

为了方便我们把 $A$ 从小到大排序，并且统计 $A$ 与 $B$ 中每个字母的出现次数，令 $a_{i}$ 表示 $A$ 中从大写字母 `A` 开始第 $i$ 个字母出现的次数，$b_{i}$ 同理。

我们令 $f_{i,j}$ 表示满足 $A$ 中从大写字母 `A` 开始第 $i$ 个字母时用了 $j$ 个下一个字母的方案数。

有转移：
$$
f_{i,j}=

\sum_{k=0}^{b_{i}-a_{i}+j} f_{i-1,k} 

\times 

\begin{pmatrix}
a_{i}\\
j\\
\end{pmatrix}

$$

但是这样的时间复杂度为 $O(n^{2})$，但是我们可以发现转移可以用前缀和优化，时间复杂度为 $O(n)$。

令 $s_{i,j}=\sum_{k=0}^{j} f_{i,k}$，新转移方程为：
$$
f_{i,j}=

s_{i-1,b_{i}-a_{i}+j} 

\times 

\begin{pmatrix}
a_{i}\\
j\\
\end{pmatrix}
$$

最后答案为 $s_{26,0} $ 乘上 $A$ 的不同排列数。

我的代码中的 $f$ 数组与 $s$ 数组都用了滚动数组优化，并且预处理了阶乘与逆元。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long md=998244353;
int n,m;
string str;
int sla[30];
int slb[30];
long long jc[200005];
long long jcs[200005];
long long ny[200005];
long long f[200005];
long long s[200005];
long long cnt;
long long ksm(long long a,long long x){
	long long ans=1;
	while(x){
		if(x&1){
			ans*=a;
			ans%=md;
		}
		a*=a;
		a%=md;
		x>>=1;
	}
	return ans;
}
long long c(long long x,long long y){
	return (((jc[y]*ny[y-x])%md)*ny[x])%md;
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%d%d",&n,&m);
	cin>>str;
	for(int i=0;i<n;i++)
		sla[str[i]-'A'+1]++;
	cin>>str;
	for(int i=0;i<m;i++)
		slb[str[i]-'A'+1]++;
	jc[0]=1;
	jcs[0]=1;
	for(int i=1;i<=n;i++){
		jc[i]=jc[i-1]*i%md;
		jcs[i]=jcs[i-1]*jc[i]%md;
	}
	long long tmp=ksm(jcs[n],md-2);
	for(int i=n;i>=1;i--){
		ny[i]=tmp*jcs[i-1]%md;
		tmp=tmp*jc[i]%md;
	}
	ny[0]=1;
	cnt=jc[n];
	s[0]=1;
	for(int j=1;j<=slb[1];j++){
		s[j]=s[j-1];
		s[j]%=md;
	}
	for(int i=1;i<=26;i++){
		for(int j=max(0,sla[i]-slb[i]);j<=min(sla[i],slb[i+1]);j++)
			f[j]=s[slb[i]-(sla[i]-j)]*c(j,sla[i])%md;
		s[0]=f[0];
		for(int j=1;j<=slb[i+1];j++){
			s[j]=s[j-1]+f[j];
			s[j]%=md;
		}
		for(int j=max(0,sla[i]-slb[i]);j<=min(sla[i],slb[i+1]);j++)
			f[j]=0;
		cnt=cnt*ny[sla[i]]%md;
	}
	printf("%lld",(s[0]*cnt)%md);
	return 0;
}
```

---

## 作者：lyhqwq (赞：3)

# Solution
计数/kk。

注意到 A 的顺序不影响答案，考虑钦定 A 有序，最后乘上 A 的排列数。

令 $f_{i,j}$ 表示考虑到第 $i$ 个字母，用了 $j$ 个 $i+1$ 来匹配。

有 $f_{i,j}=\sum\limits_{k=0}^{cntb_i-cnta_i+j} f_{i-1,k}\times \binom{cnta_i}{j}$。

前缀和优化可以做到 $O(n)$。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
const int Mod=998244353;
int n,m,ans=1;
char a[N],b[N];
int cnta[30],cntb[30];
int fac[N],inv[N];
int f[30][N],g[30][N];
int qpow(int a,int b){
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%Mod) if(b&1) ans=1ll*ans*a%Mod;
	return ans;
}
int C(int n,int m){
	return 1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d%d",&n,&m);
	scanf("%s%s",a+1,b+1);
	fac[0]=1;
	for(int i=1;i<N;i++) fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=0;i<N;i++) inv[i]=qpow(fac[i],Mod-2);
	for(int i=1;i<=n;i++) cnta[a[i]-'A'+1]++;
	for(int i=1;i<=m;i++) cntb[b[i]-'A'+1]++;
	f[0][0]=1;
	for(int j=0;j<=cntb[1];j++) g[0][j]=1;
	for(int i=1;i<=26;i++){
		for(int j=max(0,cnta[i]-cntb[i]);j<=min(cnta[i],cntb[i+1]);j++){
			f[i][j]=1ll*g[i-1][cntb[i]-cnta[i]+j]*C(cnta[i],j)%Mod;
		}
		g[i][0]=f[i][0];
		for(int j=1;j<=cntb[i+1];j++) g[i][j]=(g[i][j-1]+f[i][j])%Mod;
		ans=1ll*ans*inv[cnta[i]]%Mod;
	}
	printf("%d\n",1ll*g[26][0]*ans%Mod*fac[n]%Mod);
	return 0;
}

```

---

