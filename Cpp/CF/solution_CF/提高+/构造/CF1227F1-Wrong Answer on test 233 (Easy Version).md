# Wrong Answer on test 233 (Easy Version)

## 题目描述

你的程序又出错了。这一次它在第 233 个测试点上得到了“答案错误”。

这是这个问题的简单版本。在本版本中，$1 \le n \le 2000$。只有在你解决并锁定了两个问题后，才能对本题进行 Hack。

本题描述如下：有一份包含 $n$ 个单选题的测试。每道题有 $k$ 个选项，且只有一个选项是正确的。第 $i$ 道题的正确答案是 $h_i$，如果你对第 $i$ 道题的回答是 $h_i$，你可以获得 $1$ 分，否则该题得 $0$ 分。$h_1, h_2, \dots, h_n$ 的值在本题中已知。

然而，你的程序有一个错误。它会将答案顺时针移动一位！假设所有 $n$ 个答案排成一个环。由于程序的错误，它们会循环右移一位。

具体来说，这个错误会把第 $i$ 题的答案移动到第 $(i \bmod n) + 1$ 题。因此，第 $1$ 题的答案被移动到第 $2$ 题，第 $2$ 题的答案被移动到第 $3$ 题，……，第 $n$ 题的答案被移动到第 $1$ 题。

我们把所有 $n$ 个答案合起来称为一个“答案序列”。一共有 $k^n$ 种可能的答案序列。

你想知道，有多少个答案序列满足如下条件：顺时针移动 $1$ 位后，新答案序列的总得分严格大于原来的得分。你需要输出满足条件的答案序列数量，答案对 $998\,244\,353$ 取模。

例如，如果 $n=5$，你的答案序列为 $a=[1,2,3,4,5]$，由于程序错误，提交的答案序列为 $a'=[5,1,2,3,4]$。如果正确答案序列为 $h=[5,2,2,3,4]$，则 $a$ 得 $1$ 分，$a'$ 得 $4$ 分。由于 $4>1$，所以 $a=[1,2,3,4,5]$ 应被计入答案。

## 说明/提示

对于第一个样例，满足条件的答案序列有 $[2,1,1], [2,1,2], [2,1,3], [3,1,1], [3,1,2], [3,1,3], [3,2,1], [3,2,2], [3,2,3]$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3
1 3 1
```

### 输出

```
9
```

## 样例 #2

### 输入

```
5 5
1 1 4 2 2
```

### 输出

```
1000
```

# 题解

## 作者：liuChF (赞：1)

## CF1227F1.Wrong Answer on test 233 (Easy Version)

排列组合的做法，比较简单的观察。

### 思路

先考虑每个选择题的答案对最后得分变化的影响，这个影响分 $2$ 部分：和原答案相比的影响、和后面一个答案相比的影响。拿第 $2$ 个样例 `1 1 4 2 2` 举例：第一个选项选 $1$ 时，原来可以拿分，所以右移之后就**减**了一分；右移后和第二个选项的答案相同，可以多**加**一分，所以第一个答案选 $1$ 的影响是 $-1+1=0$ 分。同样的，选 $2,3,4,5$ 时，影响是 $-0+0=0$ 分。所以不管它选什么，对得分变化的影响都是 $0$。

再看第二个选择，选 $1$ 时的影响为 $-1+0=-1$，选 $2,3,5$ 的影响为 $-0+0=0$，选 $4$ 的影响为 $-0+1=1$。

可以在手模一下剩下的数据，不难得到：

| 原选项\答案 | 1    | 1    | 4    | 2    | 2    |
| ----------- | ---- | ---- | ---- | ---- | ---- |
| 1           | 0    | -1   | 0    | 0    | 1    |
| 2           | 0    | 0    | 1    | 0    | -1   |
| 3           | 0    | 0    | 0    | 0    | 0    |
| 4           | 0    | 0    | -1   | 0    | 0    |
| 5           | 0    | 0    | 0    | 0    | 0    |

不难发现对于每一个选择题，影响只有两种：

1. $h_i=h_{i+1}$ 时，全为 $0$。
2. $h_i\neq h_{i+1}$ 时，一个 $-1$，一个 $1$，其他全为 $0$。

一共 $n$ 个选择题，每个题 $k$ 个选项，在全部的 $k^n$ 的答案序列中，我们要找的是 $\sum_{i=1}^nh_i>0$ 的序列数。注意到这是个答案的排列，也就是说这些 $-1,0,1$ 的影响在同一个选择题的顺序并不重要。再注意到每个选择题的影响只在 $-1,0,1$ 之间，且具有对称性，我们可以求出 $\sum_{i=1}^nh_i=0$ 的排列数，记其为 $t$，所以和大于零的个数和小于零的个数相同，都是 $\dfrac{k^n-t}{2}$。

现在问题转化为求 $t$，这个比较好求，考虑将影响按照上面说的分成两组，记第一组有 $p$ 个选择题，第二组有 $q$ 个，显然有 $p+q=n$。对于第一种的和只能是 $0$，其排列数量为 $k^p$。第二组的和为 $0$ 的排列数怎么求呢？只要选的 $1$ 和 $-1$ 数一样，其它选 $0$ 就行了，所以其排列数量为：
$$
\sum_{i=0}^{\left \lfloor \frac{q}{2} \right \rfloor}C_{q}^{i}\times C_{q-i}^i\times (h-2)^{q-2\times i}
$$
 其中，$C_{q}^{i}$ 表示选 $q$ 个 $1$ 的排列数，$C_{q-i}^{i}$ 表示在剩下的 $q-i$ 个选择题中选 $i$ 个 $-1$ 的排列数，$(h-2)^{q-2\times i}$ 表示在剩下的 $q-2\times i$ 的选择题中选 $0$ 的排列数（因为要剔除 $-1,1$ 所以是 $h-2$），因为 $1$ 的个数和 $-1$ 的个数要相同，所以求和的范围为 $0\sim \left \lfloor \frac{q}{2} \right \rfloor$。

### 做法

讲的比较清楚了，$p$ 和 $q$ 的个数判一下 $h_i$ 和 $h_{i+1}$ 是否相等就行了，排列数可以预处理阶乘，乘方可以用快速幂。

注意：最后的 $k^n-t$ 除以 $2$，不能直接右移 $1$ 位，要用逆元（别问我怎么知道的）。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define fq(i,d,u) for(int i(d); i <= u; ++i)
#define fr(i,u,d) for(int i(u); i >= d; --i)
using namespace std;
const int N = 2e5, mod = 998244353;
int n, h, a[N + 10], cnt, mul[N + 10];
int ksm(int a, int b) {
	int ans = 1, base = a;
	while (b) {
		if (b & 1) (ans *= base) %= mod;
		b >>= 1;
		(base *= base) %= mod;
	}
	return ans;
}
int C(int n, int m) {
	return mul[n] * ksm(mul[m] * mul[n - m] % mod, mod - 2) % mod;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

	cin >> n >> h;
	mul[0] = 1;
	fq(i, 1, n) mul[i] = mul[i - 1] * i % mod;
	fq(i, 1, n) cin >> a[i];
	a[n + 1] = a[1];
	fq(i, 1, n) if (a[i] == a[i + 1]) cnt++;
	int ans = 0, m = n - cnt;
	fq(i, 0, m >> 1) {
		(ans += C(m, i) * C(m - i, i) % mod * ksm(h - 2, m - 2 * i) % mod) %= mod;
	}
	ans = (ksm(h, m) + mod - ans) % mod * ksm(2, mod - 2) % mod;
	cout << ans * ksm(h, cnt) % mod;
	return 0;
}
```

因为习惯问题，代码和上文字符不相同。

写的这么好，点个赞吧。

---

## 作者：sylqwq (赞：1)

简单 dp，还是比较好做的 qwq。

我们关心的状态有当前准备放答案的位置以及当前对错的个数。但是这样是个三次方的，不大能过。但是仔细一想，我们没有必要关心具体的对错数量，我们只用关心对错的差值即可，于是设 $f_{i,j}$ 表示填完前 $i$ 个位置，提交答案错位后比原来多对了 $j$ 个题的方案数。

如果 $a_i=a_{(i \bmod n) +1}$，那么第 $i$ 位不论填什么，错不错位都一样，要不然都对，要不然都错，也就是说，对错数量作差的值不会变化，于是有：

$$
f_{i,j}=f_{i-1,j}\times k
$$

再考虑一般情况。如果第 $i$ 位填 $a_i$，则原本对的错位之后就错了。如果填 $a_{(i \bmod n)+1}$，则原本错的就对了。填其余的 $k-2$ 种数，这一位错不错位都是错的。容易得到转移：

$$
f_{i,j}=f_{i-1,j+1}+f_{i-1,j-1}+f_{i-1,j}\times(k-2)
$$

答案就是

$$
\sum_{i=1}^nf_{n,i}
$$

注意 $f$ 第二维会是负数炸掉，所以实现的时候第二维整体加一个值（至少得大于等于 $n$）。

然后就做完啦。

---

## 作者：wind_whisper (赞：1)

## $\text{Description}$
有 $n$ 道题，你的程序在上交答案时把答案交串了，第 $i$ 个答案变成了第 $i\bmod n+1$ 个.  
给出 $n$ 道题的正确答案以及选项数 $k$ ，求有多少中初始上交的答案，能使交串后正确的题目数变多.  
## $\text{Solution}$
### easy version
$n\le2000,k\le10^9$  
设计 $dp_{i,j}$ 表示填到第 $i$ 题，多填对了 $j$ 道题的方案数.  
暴力转移即可.  
### hard version
$n\le2\times10^5,k\le10^9$  
原来 dp 的做法行不通了，我们需要另辟蹊径.  
设 $f_i$ 表示多对了 $i$ 道题的方案数，由于对称性，有 $f_i=f_{-i}$.  
所以我们的答案其实就是：
$$\dfrac{k^n-f_0}{2}$$
所以我们只需要求出 $f_0$ 就行了.  
连续两个答案相同无法产生差异，我们扫一遍求出有 $m$ 个位置可以产生差异.  
枚举答对（答错）的题目数，则有：
$$f_0=\sum_{i=0}^{\lfloor\frac{m}{2}\rfloor}k^{n-m}\times C_m^i\times C_{m-i}^i\times (k-2)^{m-2i}$$
直接求解即可.
## $\text{Code}$
dp:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2050;
const int mod=998244353;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m,k;
ll dp[2][N<<1];
int now,nxt,o=2000,a[N];
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();k=read();
  for(int i=1;i<=n;i++) a[i]=read();
  dp[nxt=1][0+o]=1;
  for(int i=1;i<=n;i++){
    swap(now,nxt);
    memset(dp[nxt],0,sizeof(dp[nxt]));
    for(int j=-i;j<=i;j++){
      if(a[i]==a[i%n+1]) (dp[nxt][j+o]+=dp[now][j+o]*k)%=mod;
      else{
	(dp[nxt][j+1+o]+=dp[now][j+o])%=mod;
	(dp[nxt][j-1+o]+=dp[now][j+o])%=mod;
	(dp[nxt][j+o]+=(k-2)*dp[now][j+o])%=mod;
      }
    }
  }
  ll res(0);
  for(int i=1;i<=n;i++) (res+=dp[nxt][i+o])%=mod;
  printf("%lld\n",res);
  return 0;
}
/*
*/

```
组合数：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2e5+100;
const int mod=998244353;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m,k;
int a[N];
ll ans;
ll ksm(ll x,ll k){
  ll res=1;
  while(k){
    if(k&1) res=res*x%mod;
    x=x*x%mod;
    k>>=1;
  }
  return res;
}
ll jc[N],ni[N],mi[N];
inline ll C(int n,int m){
  return jc[n]*ni[m]%mod*ni[n-m]%mod;
}
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();k=read();
  if(k==1){
    printf("0");return 0;
  }
  for(int i=1;i<=n;i++) a[i]=read();
  for(int i=1;i<=n;i++) m+=(a[i]!=a[i%n+1]);
  jc[0]=1;
  for(int i=1;i<=m;i++) jc[i]=jc[i-1]*i%mod;
  ni[m]=ksm(jc[m],mod-2);
  for(int i=m-1;i>=0;i--) ni[i]=ni[i+1]*(i+1)%mod;
  mi[0]=1;
  for(int i=1;i<=n;i++) mi[i]=mi[i-1]*(k-2)%mod;
  ans=ksm(k,n);ll w=ksm(k,n-m);
  for(int i=0;i<=m/2;i++) ans=(ans+mod-w*C(m,i)%mod*C(m-i,i)%mod*mi[m-2*i]%mod)%mod;
  ans*=ksm(2,mod-2);ans%=mod;
  printf("%lld\n",ans);
  return 0;
}
/*
*/

```


---

## 作者：1234567890sjx (赞：0)

upd：修改了转移的公式。

前置：定义 $\text{NXT}(a_i)$ 表示 $a_i$ 循环下一个位置所对应的元素。

设 $f_{i,j}$ 表示当前切到了第 $i$ 道题目，比原来多对了 $j$ 道的方案数。那么显然有转移：

+ $a_i=\text{NXT}(a_i)$，则此时不管选什么填都和原来没有任何区别，则有转移 $f_{i,j}\leftarrow f_{i-1,j}\times k$。
+ $a_i\neq\text{NXT}(a_i)$，则此时如果本来选对了那么现在选错了，$f_{i,j}\leftarrow f_{i-1,j+1}$。如果本来选错了但是现在可能选对了，$f_{i,j}\leftarrow f_{i-1,j-1}$，否则就是不管怎么着都选错了，$f_{i,j}\leftarrow 
(k-2)\times f_{i-1,j}$。

因为 $n$ 很小所以暴力转移即可，时间复杂度为 $O(n^2)$。

---

## 作者：Hoks (赞：0)

## 前言
不算很难的 dp 题。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
考虑使用计数 dp 来解决这个问题。

设计 $dp_{i,j}$ 表示填了 $i$ 道题在涂串后会多 $j$ 分的方案数。

分类讨论下：
1. $a_i$ 和 $a_{i\bmod n+1}$ 相同：

   那么不管我填了什么，要么都对要么都错，直接转移过来乘 $k$ 即可。
2. $a_i$ 和 $a_{i\bmod n+1}$ 不同：

   那么若填了 $a_i$ 就会多错一个，$a_{i\bmod n+1}$ 则多对一个。
   
   其他情况则是不变，乘上得到个数加一起即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+10,V=2e3,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,k,ans,a[N],f[N][N<<1];
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
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='#'||c=='.'); }
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
signed main()
{
    n=read();k=read();for(int i=1;i<=n;i++) a[i]=read();
    f[0][V]=1;
    for(int i=1;i<=n;i++)
        for(int j=-n;j<=n;j++)
            if(a[i]==a[i%n+1]) f[i][j+V]=f[i-1][j+V]*k%mod;
            else f[i][j+V]=((f[i-1][j-1+V]+f[i-1][j+1+V])%mod+f[i-1][j+V]*(k-2)%mod+mod)%mod;
    for(int i=1;i<=n;i++) ans=(ans+f[n][i+V])%mod;
    print(ans);genshin:;flush();return 0;
}
```

---

## 作者：LCat90 (赞：0)

这是不需要 dp 的 $n^2$ 做法。  

对于两次的值都相同的点显然随便取对最终的 $\Delta$ 都是没有影响的，所以 $k$ 个值随便选。下面记不同的位置有 $m$ 个。

枚举 $i$ 个位置 $a_i=h_i$，$j$ 个位置 $a_i=h_{i\bmod n+1}$，那么根据题意有 $i<j$。

剩余的 $m-i-j$ 个位置不选 $h_i$ 和 $h_{i\bmod n+1}$ 共有 $(k-2)^{m-i-j}$ 种方案。在 $m$ 个位置中选 $i+j$ 个位置并且分成 $i$ 和 $j$ 个的方案是 $C_{m}^{i+j}\cdot C_{i+j}^i$。  

最终的式子：

$$k^{n-m}\cdot\sum_{i=0}^{m}\sum_{j=i+1}^{m-i} (k-2)^{m-i-j}\cdot C_{m}^{i+j}\cdot C_{i+j}^i$$

提供 Hard 的优化思路：（感谢 tzl）

我们枚举 $i+j=T$。

$$\sum_{T=1}^m (k-2)^{m-T} \cdot C_m^T \cdot \sum_{i=0}^{\lceil \frac{T}{2} \rceil -1} C_T^i $$

然后分类讨论 $T$ 的奇偶性，就可以 $O(n)$ 了。

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N = 2e5 + 5, Mod = 998244353, M = 2e3;
int qkpow(int a, int b) {
    if(a < 0) return 0;
	if(b == 0) return 1;
	if(b & 1) return a * qkpow(a, b - 1) % Mod;
	int t = qkpow(a, b >> 1);
	return t * t % Mod;
} 
int n, k, a[N], b[N], ans, ifac[N], fac[N];
int C(int n, int m) { if(n < 0 or m > n or m < 0) return 0; return fac[n] * ifac[m] % Mod * ifac[n - m] % Mod; }
signed main() {
	cin >> n >> k;
	fac[0] = 1;
	for(int i = 1;i <= M; ++i) fac[i] = fac[i - 1] * i % Mod; 
	ifac[M] = qkpow(fac[M], Mod - 2);
	for(int i = M - 1;i >= 0; --i) ifac[i] =  ifac[i + 1] * (i + 1) % Mod;
    int sam = 0;
    for(int i = 1;i <= n; ++i) cin >> a[i]; for(int i = 1;i <= n; ++i) b[i] = a[i % n + 1], sam += (a[i] == b[i]);
    // 枚举多少个等于 a，多少个等于 b，而且 a < b
    int mul = qkpow(k, sam); // same 的随便选
    int m = n - sam; //cout << n << " " << m << "\n";
    for(int i = 0;i <= m; ++i) // =a
        for(int j = i + 1;i + j <= m; ++j) { // =b 
            int tmp = C(m, i + j) * C(i + j, i) % Mod; //tmp = (tmp % Mod + Mod) % Mod;
            tmp = tmp * qkpow(k - 2, m - i - j) % Mod; 
            // cout << i << " " << j << " " << tmp << " " << tmp * mul << "\n";
            ans = (ans + tmp * mul % Mod) % Mod;
        }
    cout << ans;    
	return 0;
}
```

---

## 作者：xiezheyuan (赞：0)

[也许有更好的阅读体验](https://www.cnblogs.com/zheyuanxie/p/cf1227f1.html)

## 简要题意

给定 $n$，$k$ 和值域 $[1,k]$ 的 $n$ 个整数 $h_i$，求有多少个长为 $n$ 的整数序列 $a$ 满足值域 $[1,k]$，且 $\sum\limits_{i=1}^n[a_i=h_i]<\sum\limits_{i=1}^n[a_i=h_{(i\bmod{n})+1}]$。答案对 $998244353$ 取模。

$1 \leq n \leq 2\times 10^3,1 \leq k \leq 10^9$

## 思路

小清新二维 DP 题。

令 $f_{i,j}$ 为截止到第 $i$ 位，比原来的少错 $j$ 个数的方案数。

则动态转移方程为：

$$
f_{i,j}=\begin{cases}
& kf_{i-1,j} & h_i=h_{i\bmod{n}+1}\\
& f_{i-1,j-1}+f_{i-1,j+1},(k-2)f_{i-1,j} & \text{otherwise}
\end{cases}
$$

方程解释：

- 对于第一种情况，由于变换后对结果没有影响，所以只能从 $f_{i-1,j}$ 转移而来， 乘上值域。
- 对于第二种情况 $f_{i-1,j-1}$ 是多对了一题，$f_{i-1,j+1}$ 是少对了一题。这两种情况占了 $2$ 个值，所以剩下的没变的 $f_{i-1,j}$ 就只有 $k-2$ 种了。

我们要求的是比原来多的方案数，就是 $\sum_{i=1}^{n}{f_{n,i}}$。

边界：$f_{0,0}=1$。

时间复杂度 $O(n^2)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 4000+5;
const int mod = 998244353;

int F[N][N];
int n,k,h[N];

int& f(int i,int j){
    return F[i][j+n];
}
int M(const int &x){
    return (x%mod+mod)%mod;
}

signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>h[i];
    }
    f(0,0)=1;
    for(int i=1;i<=n;i++){
        for(int j=-n;j<=n;j++){
            if(h[i]==h[i%n+1]){
                f(i,j)=M(f(i-1,j)*k);
            }
            else{
                f(i,j)=M(M(f(i-1,j-1)+f(i-1,j+1))+M(f(i-1,j)*((k-2))));
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        ans+=f(n,i);
        ans=M(ans);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

模拟赛的时候这个数据范围的做法只有 40 分呢。/oh/hsh

本题有 $O(n \log k)$ 做法，可以去 F2 查看捏qwq。

## 思路

显然可以 $dp$ 做。最暴力的状态就是 $dp_{i,j,k}$ 表示前 $i$ 个，第一个人参加了 $j$ 个，第二个人参加了 $k$ 个的方案数。

显然复杂度 $O(n^3)$ 没法做。考虑一个经典的优化，即 $j,k$ 我们不关心他们具体多大，只关心 $j-k$ 的值。所以设 $dp_{i,j}$ 表示前 $i$ 个，第一个人比第二个人少参加了 $j$ 个的时候的方案数。

显然有转移：

$$dp_{i,j}=\begin{cases}dp_{i-1,j} \times (k-2)+dp_{i-1,j-1}+dp_{i-1,j+1}\;[a_i \neq b_i]\\dp_{i-1,j } \times k\;[a_i=b_i]\end{cases}$$

第一个式子的意思就是，如果 $a_i \neq b_i$，则：

- 有 $k-2$ 种方案让两个人都看不到（即选除了 $a_i$ 和 $b_i$ 以外的）；

- 有一种方案是选 $a_i$，那么从 $dp_{i-1,j+1}$ 转移。

- 有一种方案是选 $b_i$，那么从 $dp_{i-1,j-1}$ 转移。

第二个式子显然，当 $a_i=b_j$ 的时候不管怎么选都不会改变差值。

注意这里的 $j$ 可以是负数，所以我们给他们都加上 $n$，避免负数情况。剩下的就是暴力转移，复杂度 $O(n^2)$。

## Code

```cpp
#include <bits/stdc++.h>
inline int qr(){
	char ch=getchar(); bool f=1; int w=0;
	for(;ch<'0' || ch>'9';ch=getchar()) if(ch=='-')f=0;
	for(;ch>='0' && ch<='9';ch=getchar()) w=w*10+ch-'0';
	return f?w:-w;
}
void write(int x){
	if(x>9) write(x/10);
	putchar(x%10+48);
}
using namespace std;
const int MAXN=2005,mod=998244353;
 
int a[MAXN],b[MAXN];
int dp[MAXN][MAXN<<1];

int main(){
	int n=qr(),k=qr();
	for(int i=1;i<=n;i++) a[i]=qr();
	for(int i=1;i<=n;i++) b[i]=a[i%n+1];
	
	int ans=0; dp[0][n]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=(n<<1);j++){
			if(a[i]==b[i]) dp[i][j]=1ll*dp[i-1][j]*k%mod;
			else dp[i][j]=(dp[i-1][j+1]+dp[i-1][j-1]+1ll*dp[i-1][j]*(k-2))%mod;
		}
	}
	for(int i=n+1;i<=(n<<1);i++) ans=(ans+dp[n][i])%mod;
	write(ans);
	return 0;
}
```

---

