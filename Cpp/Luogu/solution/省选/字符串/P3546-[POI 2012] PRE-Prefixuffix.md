# [POI 2012] PRE-Prefixuffix

## 题目描述

We consider strings consisting of lowercase letters of the English alphabet in this problem.

An initial fragment of a given string is called its prefix.

A final (terminal) fragment of a given string is called its suffix.

In particular, the empty string is both a prefix and a suffix of any string.

Two strings are cyclically equivalent if one of them can be obtained from another by    moving its certain suffix from the end of the string to its beginning.

For example, the strings ![](http://main.edu.pl/images/OI19/pre-en-tex.1.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.2.png) are cyclically equivalent, whereas the strings ![](http://main.edu.pl/images/OI19/pre-en-tex.3.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.4.png) are not.

In particular, every string is cyclically equivalent to itself.

A string ![](http://main.edu.pl/images/OI19/pre-en-tex.5.png) consisting of ![](http://main.edu.pl/images/OI19/pre-en-tex.6.png) letters is given.

We are looking for its prefix ![](http://main.edu.pl/images/OI19/pre-en-tex.7.png) and suffix ![](http://main.edu.pl/images/OI19/pre-en-tex.8.png) of equal length such that:

![](http://main.edu.pl/images/OI19/pre-en-tex.9.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.10.png) are cyclically equivalent,                  the common length of ![](http://main.edu.pl/images/OI19/pre-en-tex.11.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.12.png) does not exceed ![](http://main.edu.pl/images/OI19/pre-en-tex.13.png)        (i.e., the prefix ![](http://main.edu.pl/images/OI19/pre-en-tex.14.png) and the suffix ![](http://main.edu.pl/images/OI19/pre-en-tex.15.png) do not overlap in ![](http://main.edu.pl/images/OI19/pre-en-tex.16.png)), and                  the common length of ![](http://main.edu.pl/images/OI19/pre-en-tex.17.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.18.png) is maximized.

对于两个串 $S_1, S_2$，如果能够将 $S_1$ 的一个后缀移动到开头后变成 $S_2$，就称 $S_1$ 和 $S_2$ 循环相同。例如串 ababba 和串 abbaab 是循环相同的。

给出一个长度为 $n$ 的串 $S$，求满足下面条件的最大的 $L(L\leq \frac n 2)$：$S$ 的 $L$ 前缀和 $S$ 的 $L$ 后缀是循环相同的。

## 说明/提示

数据范围：

- 对于 $30\%$ 的数据，保证 $n\le 500$；
- 对于 $50\%$ 的数据，保证 $n\le 5000$；
- 对于 $100\%$ 数据，保证 $1\le n\le 10^6$。

## 样例 #1

### 输入

```
15
ababbabababbaab```

### 输出

```
6```

# 题解

## 作者：Alex_Wei (赞：38)

Upd on 2022.9.4：修改表述。

> *[P3546 [POI2012] PRE-Prefixuffix](https://www.luogu.com.cn/problem/P3546)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/POI.html)。

好题。

若 $S, T$ 循环相同，则它们可以被写成 $AB$ 和 $BA$ 的形式。因此，对 $s$ 的每个 border 长 $i (2i\leq S)$，求 $s[i + 1, n - i]$ 最长的不重叠 border 长 $f_i$，则 $\max i + f_i$ 即答案。

考虑所有 $s_i = s[i + 1, n - i]$，$s_i$ 的 border 掐头去尾后变成了 $s_{i + 1}$ 的 border，因此 $|B_{\max} (s_i)| \leq |B_{\max} (s_{i + 1})| + 2$。

根据这一性质，我们从大到小枚举所有 $i (1\leq i\leq n / 2)$，维护长度 $p$ 表示 $s_i$ 的最长 **不重叠** border 长。当 $i\to i - 1$ 时，令 $p\gets p + 2$，并不断减小 $p$ 直到 $p$ 是 $s_i$ 的不重叠 border 长。势能分析，$p$ 的移动距离不超过 $2n$。

判断字符串是否相等使用哈希，自然溢出哈希会被卡。求 $s$ 的所有 border 直接 KMP 即可。时间复杂度线性。[双倍经验](https://www.luogu.com.cn/problem/CF961F)。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
inline int read() {
  int x = 0;
  char s = getchar();
  while(!isdigit(s)) s = getchar();
  while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
  return x;
}
inline void print(int x) {
  if(x < 0) return putchar('-'), print(-x);
  if(x >= 10) print(x / 10);
  putchar(x % 10 + '0');
}
bool Mbe;
constexpr int N = 1e6 + 5;
constexpr int mod = 1e9 + 7;
int n, ans, f[N], nxt[N], hsh[N], pw[N];
int calc(int l, int r) {return l--, (hsh[r] - 1ll * hsh[l] * pw[r - l] % mod + mod) % mod;}
char s[N];
bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0);
  cin >> n >> s + 1;
  for(int i = pw[0] = 1; i <= n; i++) pw[i] = 1ll * pw[i - 1] * 131 % mod;
  for(int i = 2, j = 0; i <= n; i++) {
    while(j && s[j + 1] != s[i]) j = nxt[j];
    nxt[i] = j += s[j + 1] == s[i];
  }
  for(int i = 1; i <= n; i++) hsh[i] = (1ll * hsh[i - 1] * 131 + s[i]) % mod;
  for(int i = n / 2; i; i--) {
    f[i] = f[i + 1] + 2;
    while(f[i]) {
      if((i + f[i]) * 2 > n) f[i]--;
      else if(calc(i + 1, i + f[i]) != calc(n - i - f[i] + 1, n - i)) f[i]--;
      else break;
    }
  }
  for(int i = nxt[n]; i; i = nxt[i]) if(i * 2 <= n) ans = max(ans, f[i] + i);
  cout << ans << "\n";
  cerr << TIME << " ms\n";
  return 0;
}
/*
2022/9/4
author: Alex_Wei
start coding at 8:40
finish debugging at 8:50
*/
```

---

## 作者：一只绝帆 (赞：27)

与所有题解不同的无需哈希线性做法。

首先瞪出来题目让你求的是两个 $\rm border$。

考虑一个非常智慧的转化：把原串按照 $s_1s_ns_2s_{n-1}\cdots$ 这个顺序重排成一个串，你发现两个 $\rm border$ 变成了挤在前面的两个回文串。

考虑套用 	[P4555 \[国家集训队\] 最长双回文串](https://www.luogu.com.cn/problem/P4555) 的做法，直接 manacher 求回文半径，然后对能顶到序列开头的回文串标记一下末尾，再利用并查集覆盖对每个点求出最靠后的能覆盖它的回文中心，枚举回文串交界处拼一下就好。

```cpp
char s[N],t[N];
int p[N],n,f[N],vis[N],res[N];
int find(int x) {return f[x]^x?f[x]=find(f[x]):x;}
int main() {
	F(i,1,n=read()) while(isspace(s[i]=gc()));
	for(int i=1,j=1;j<=n;i++,j+=2) t[j]=s[i];
	for(int i=n,j=2;j<=n;i--,j+=2) t[j]=s[i];
	t[0]='&'; 
	int mr=0,mid2=0;
	F(i,1,n-1) {//[i,i+1]
		if(mid2-i-1>0&&mr-i-1>0) p[i]=min(p[mid2-i-1],mr-i-1);
		while(t[i-p[i]]==t[i+1+p[i]]) ++p[i];
		if(i+1+p[i]>mr) mr=i+1+p[i],mid2=2*i+1;
		if(i==p[i]) vis[i+p[i]]=1; 
	}
	F(i,1,n+1) f[i]=i;
	UF(i,n-1,1) {
		for(int j=find(i-p[i]+1);j<=i;j=f[j]=find(j+1)) res[j]=i;
	}
	int ans=0;
	F(i,1,n) if(vis[i]&&res[i+1]) ans=max(ans,(res[i+1]+res[i+1]+1-(i+1))/2);
	F(i,1,n) if(vis[i]) ans=max(ans,i/2);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：maruize (赞：24)

- 循环同构怎么处理？

$\quad$ 对于一个串 $AB$ ，则 $BA$ 与它循环同构。

- 设输入的字符串为 $S$ , 那么题目就是让我们把 $S$ 写成 $ABCBA$ 的形式，最大化子串 $AB$ 的长度。

- 枚举 $A$ 的长度，发现就是对首尾割掉 $A$ 的中间一部分求 kmp 的 border 。

- 设 $f_i$ 为去掉首尾 $i$ 个字符子串的 border 。(需要小于串长的 $\frac{1}{2}$ )

![](https://cdn.luogu.com.cn/upload/image_hosting/4p94zerk.png)

- 根据上图，可以发现 $f_{i+1}\ge f_i -2$ (绿色为 $f_i$ 的 border )

不过 $f_1$ 直接求是不特别好求，$f_{n/2}$ 很好求 ($=0$) 。

所以移一下项 $f_i\le f_{i+1} +2$ 倒着用 hash 求一下即可。

因为 $f_{i+1} \rightarrow f_i $转移中 dp 值每次 $-2$ or $+k$ 所以复杂度 $O(n)$。

```cpp
int m=n/2+(n&1);
f[m]=0;
for(int i=m-1;i>=0;i--){
	int&x=f[i]=min(f[i+1]+2,(n-2*i)/2);//不要忘了取个min
	while(x>0&&!cmp(i+1,i+x,n-i-x+1,n-i))x--;
	//cmp(a,b,c,d)表示子串[a..b]和[c..d]是否相等
}
int ans=0;
for(int i=0;i<m;i++)
	if(cmp(1,i,n-i+1,n))ans=max(ans,i+f[i]);
```

---

## 作者：Leasier (赞：5)

前置芝士：[字符串哈希](https://oi-wiki.org/string/hash/)

首先来考虑一下循环同构怎么处理。

当 $[1, k]$ 与 $[n - k + 1, n]$ 循环同构且满足题述条件，则存在一个 $k'$，使得：

- $0 \leq k' \leq k \leq \lfloor \frac{n}{2} \rfloor$。
- $[1, k']$ 为原串 border。
- $[k' + 1, k]$ 为 $[k' + 1, n - k']$ 的 border。

有一个没有脑子的做法：KMP 求原串 border，再每次求一个区间 border。时间复杂度为 $O(n \log n)$ 且巨难写，不知道能不能过（

这里我们不妨来考虑一下 $[i, n - i + 1]$ 与 $[i + 1, n - i]$ 的 border 的关系。

你后者向前者转移时，相当于两边各添加一个字符，若此时不是 border 了还会再缩短，但感性理解一定不会再增长。

所以说前者 border 长度 $\leq$ 后者 border 长度加上 $2$。

于是我们从 $\lfloor \frac{n}{2} \rfloor$ 向 $0$ 循环，记录当前 border 长度 $L$，每次先令 $L \leftarrow L + 2$，如果此时不再是 border 就减小 $L$ 直到其为 border，最后在所有 border $i$ 处统计 $i + L$ 的最大值即可。

时间复杂度为 $O(n)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int seed = 998244353, mod = 1e9 + 7;
ll power[1000007], hash[1000007];
char t[1000007];

inline void init(int n){
	power[0] = 1;
	for (int i = 1; i <= n; i++){
		power[i] = power[i - 1] * seed % mod;
	}
}

inline int min(int a, int b){
	return a < b ? a : b;
}

inline ll get_hash(int l, int r){
	return ((hash[r] - hash[l - 1] * power[r - l + 1] % mod) % mod + mod) % mod;
}

inline int max(int a, int b){
	return a > b ? a : b;
}

int main(){
	int n, m, len = 0, ans = 0;
	scanf("%d", &n);
	scanf("%s", &t[1]);
	m = n / 2;
	init(n);
	for (int i = 1; i <= n; i++){
		hash[i] = (hash[i - 1] * seed % mod + t[i]) % mod;
	}
	for (int i = m; i >= 0; i--){
		len = min(len + 2, m - i);
		while (len > 0 && get_hash(i + 1, i + len) != get_hash(n - i - len + 1, n - i)) len--;
		if (get_hash(1, i) == get_hash(n - i + 1, n)) ans = max(ans, i + len);
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：氧少Kevin (赞：3)

## 洛谷3546 - PRE-Prefixuffix
>- 链接：https://www.luogu.com.cn/problem/P3546
>- 难度：紫
### 题意
- 给出一个长度为 $n$ $(n\leq 10^6)$ 字符串 $S$，需要从中选出它的一个前缀 $A$ 和后缀 $B$
- 满足：$|A|=|B|$，$|A|\leq \frac{|n|}{2}$，$A+B = B+A$
- 输出 $|A|$ 即可。

### 错误思路
- 先求出 $S$ 的最长 $\text{Border}$，记为 $a$
- 去掉 $S$ 的长度为 $|a|$ 的前缀和后缀，再求出 $S$ 的最长 $\text{Border}$，记为 $b$
- 答案就是 $|a|+|b|$
- 错误原因：$a$ 取 $S$ 的最长 $\text{Border}$ 不一定最优（可能是次长的或更短的），因为还有 $b$ 的影响。

### 正确思路
- 用 KMP 求出 $S$ 的所有 $\text{Border}$
- 对于每个 $\text{Border}$，设当前 $\text{Border}$ 为 $a$
    - (1) 设 $S$ 的前后去掉 $a$ 的字符串为 $T$
    - (2) 求出 $T$ 的最长 $\text{Border}$，设为 $b$
    - (3) $ans = \max(ans, |a|+|b|)$
- 复杂度 $O(n^2)$，考虑优化。重点优化第(2)步。
#### 如何求区间 $\text{Border}$ ？
- 不难发现，这里的 区间 $\text{Border}$ 并不是求任意的区间，
- 而是从 $S$ 的中心开始，同时向左向右扩张 $k$ 的长度的区间。
- 可以从 $S$ 的中心开始，进行递推
- 设 $dp[i]$ 为从 $S$ 的中心开始，同时向左向右扩张 $i$ 的长度的区间，此时的最长 $\text{Border}$。
- 可以发现： $dp[i+1] \in [ 0,dp[i]+2 ]$
- 具体实现：转移时，先令 $dp[i+1] = dp[i]+2$，如果验证哈希不合要求，就 $dp[i+1]-=1$，直到符合要求。
- 语句 `dp[i+1]-=1` 最多执行 $2n$ 次。
- 时间复杂度 $O(n\log n)$。

---

## 作者：MikukuOvO (赞：3)

考虑暴力怎么做，我们枚举在字符串的首位删去等量字符，然后求出剩余部分的最长相等前后缀，如果删去的两段相等，那么就对于答案有贡献。

定义$f[i]$表示删去$i$个字符后剩余部分的最长相等前后缀，那么就有这个限制：

$f[i+1]+2 \geq f[i]$

这个画个图就可以证明了，有了这个限制，我们就可以$O(n)$的求出$f$数组，对于判断相等就$hash$一下就好了。

```cpp
const int N=1e6+5;
const int base=131;
const ll mod=998244353;

int n;
int f[N];
ll h[N],fac[N];
char s[N];

bool check(int lx,int rx,int ly,int ry)
{
    ll a=(h[rx]-h[lx-1]*fac[rx-lx+1]%mod+mod)%mod,b=(h[ry]-h[ly-1]*fac[ry-ly+1]%mod+mod)%mod;
    return a==b;
}
int main()
{
    fio();
    gi(n);
    scanf("%s",s+1);
    int ans=0;
    fac[0]=1;
    for(int i=1;i<=n;++i) h[i]=(h[i-1]*base%mod+s[i]-'a')%mod;
    for(int i=1;i<=n;++i) fac[i]=fac[i-1]*base%mod;
    for(int i=(n>>1);i;--i)
    {
        f[i]=f[i+1]+2;
        while(f[i]+i>(n>>1)) --f[i];
        while(f[i]&&!check(i+1,i+f[i],n-i-f[i]+1,n-i)) --f[i];
    }
    for(int i=1;i<=(n>>1);++i) if(check(1,i,n-i+1,n)) ans=max(ans,f[i]+i);
    print(ans);
    end();
}
```

---

## 作者：kczno1 (赞：3)

由于s1是移了一个后缀到前面和s2相同,所以类似ab..ba

我们枚举a的长度，就是求b。

也就是求最长相同的前缀后缀。

观察变化一个的情形，类似asb..asb->sb..as，所以有f[i]>=f[i-1]-2。

但可行性不是单调的，仍然不能递推。

f[i-1]<=f[i]+2。

i从大到小枚举，f[i]也可以从大到小一直枚举到第一个可行位置。

事实证明，取模hash比自然溢出的hash不容易被卡。。

```cpp
#include<bits/stdc++.h>
using std::min;

void chmax(int &x,int y) { if(x<y)x=y; }
#define ll long long
#define N 1000100
char ch[N];int n;
struct Hash
{
  ll s[N],mi[N],p;
  void init(int w,int _p)
  {
        mi[0]=1;p=_p;
       for (int i=1;i<=n;++i) {s[i]=(s[i-1]*w+ch[i]-'a')%p;mi[i]=mi[i-1]*w%p;}
  }
  int get(int l,int r)
  {
        return ((s[r]-s[l-1]*mi[r-l+1])%p+p)%p;
  }
}h1,h2;

bool same(int l1,int r1,int l2,int r2)
{
    return h1.get(l1,r1)==h1.get(l2,r2)&&h2.get(l1,r1)==h2.get(l2,r2);
}

int main()
{
    freopen("1.in","r",stdin);
    int i;
    scanf("%d",&n);
    scanf("%s",ch+1);
    h1.init(29,100000009);h2.init(37,1000000007);
    int ans=0,len=n>>1,f=0;
    for (i=len;i;--i,f=min(f+2,len-i))
    if (same(1,i,n-i+1,n))
    {
        while (f&&!same(i+1,i+f,n-i-f+1,n-i)) --f;
        chmax(ans,i+f);
    }
    printf("%d",ans);
}
```

---

## 作者：nr0728 (赞：1)

### 前言

模拟赛有这道题，写篇题解纪念一下。

### 思路

题目等价于求当字符串为 $ABSBA$ 形式时，$AB$ 的长度。

考虑枚举 $A$ 和 $B$ 的长度，用哈希判断是否循环重构，代码如下，很好写：（注意，自然溢出哈希会被卡）

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
#define mod 998244353
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define req(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
#define re register
template <typename T> inline T read(T &x) { // 快读
    x = 0; re char ch = getchar(); re int f = 1;
    while (!isdigit(ch) && ch ^ '-') ch = getchar();
    if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar(); x *= f;
    return x;
}
int n,Pow[10000001],Hash[10000001],ans;
string s; 
bool same(int l1,int r1,int l2,int r2) // 判循环重构
{
	return (Hash[r1]-Hash[l1-1]*Pow[r1-l1+1]%mod+mod)%mod==(Hash[r2]-Hash[l2-1]*Pow[r2-l2+1]%mod+mod)%mod;
}
main()
{
	read(n);cin>>s;
	Pow[0]=1;
	rep(i,1,n) Pow[i]=Pow[i-1]*13331%mod,(Hash[i]=Hash[i-1]*13331+s[i-1])%=mod;
	rep(i,1,n>>1) if(same(1,i,n-i+1,n)) // 枚举
	{
		ans=max(ans,i);
		req(j,(n>>1)-i,1) if(same(i+1,i+j,n-i-j+1,n-i)) {ans=max(ans,i+j);break;} 
	}
	cout<<ans;
	return 0;
}
```

于是测试点 #45、#50、#55 得到了 TLE，最终得分：70。

考虑进行优化：

令 $B=aB'c$，那么原字符串也可以写成 $AaB'cSaB'cA$，将其分段为 $\{Aa\},\{B'\},\{cSa\},\{B'\},\{cA\}$。

记 $dp_i$ 表示 $A$ 为 $S$ 前 $i$ 个字符时 $B$ 的最大长度，则不难发现 $dp_{i+1}\geq dp_{i}-2$，是存在单调性的（类似于后缀数组求 $height$）。我们可以知道初值 $dp_{\lfloor\frac n 2\rfloor}$，所以考虑 $\forall 1\leq i\lt\lfloor\frac n 2\rfloor$，先计算 $dp_{i+1}$ 后计算 $dp_{i}$。

又因为我们前面发现的 $dp_{i+1}\geq dp_{i}-2$（即 $dp_i\leq dp_{i+1}+2$），所以计算 $dp_i$ 时，先令其初值为 $dp_{i+1}+2$，不合法就减小，总判断次数一定不超过 $2\times n$。

求出 $dp$ 数组后，判断 $A$ 是否合法并更新答案即可。

总时间复杂度为 $\mathcal O(n)$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244853
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define req(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
#define re register
template <typename T> inline T read(T &x) { // 快读
    x = 0; re char ch = getchar(); re int f = 1;
    while (!isdigit(ch) && ch ^ '-') ch = getchar();
    if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar(); x *= f;
    return x;
}
int n,Pow[10000001],Hash[10000001],dp[10000001],ans;
string s; 
bool same(int l1,int r1,int l2,int r2) // 判断循环重构
{
	return (Hash[r1]-Hash[l1-1]*Pow[r1-l1+1]%mod+mod)%mod==(Hash[r2]-Hash[l2-1]*Pow[r2-l2+1]%mod+mod)%mod;
}
main()
{
	read(n);cin>>s;
	Pow[0]=1;
	rep(i,1,n) Pow[i]=Pow[i-1]*233%mod,(Hash[i]=Hash[i-1]*233+s[i-1])%=mod;
	req(i,n>>1,1) // 优化
	{
	    dp[i]=dp[i+1]+2;
	    if(dp[i]+i>(n>>1)) dp[i]=(n>>1)-i;
        while(dp[i]&&!same(i+1,i+dp[i],n-i-dp[i]+1,n-i)) --dp[i];
	}
    rep(i,1,n>>1) // 判断 A 是否合法
        if(same(1,i,n-i+1,n)) ans=max(ans,dp[i]+i);
	cout<<ans;
	return 0;
}
```


---

## 作者：small_john (赞：0)

## 题目大意

给出字符串 $s$，求 $s$ 的前缀和 $s$ 的后缀循环同构的最大长度。

## 解题思路

按照题目的定义，两个循环同构的字符串可以表示成 $\texttt{AB,BA}$。

那么 $s$ 可以表示为 $\texttt{ABSBA}$。

设 $f_i$ 表示 $\texttt{A}$ 为 $s_1\sim s_i$ 时 $\texttt{B}$ 的最大长度。那么就有 $f_i\le f_{i+1}+2$。

所以每次先把 $f_i$ 赋值为 $f_{i+1}+2$，如果 $f_i+i>\lfloor \frac{n}2\rfloor$，那么 $f_i$ 就赋值为 $\lfloor \frac{n}2\rfloor-i$。

接下来一点一点减小 $f_i$，直到两边相同。

最后统计答案，枚举 $\texttt{A}$ 的长度，如果两边 $\texttt{A}$ 相同，那么 $ans = \max\{ans,f_i+i\}$。最后输出即可。

**注**：判断两段字符串是否相同用哈希即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e7+5,base = 13331,mod = 1e9+7;
int n,h[N],p[N],f[N],ans;
string s;
int get(int l,int r)
{
	return (h[r]-h[l-1]*p[r-l+1]%mod+mod)%mod;
}
bool ok(int l1,int r1,int l2,int r2)
{
	return get(l1,r1)==get(l2,r2);
}
signed main()
{
	cin>>n>>s;
	s = ' '+s;
	for(int i = 1;i<=n;i++)
		h[i] = (h[i-1]*base+s[i])%mod;
	p[0] = 1;
	for(int i = 1;i<=n;i++)
		p[i] = p[i-1]*base%mod;
	for(int i = n/2;i;i--)
	{
		f[i] = f[i+1]+2;
		if(f[i]+i>n/2) f[i] = n/2-i;
		while(f[i]&&(!ok(i+1,i+f[i],n-i-f[i]+1,n-i))) f[i]--;
	}
	for(int i = 1;i<=n/2;i++)
		if(ok(1,i,n-i+1,n))
			ans = max(ans,f[i]+i);
	cout<<ans;
	return 0;
}
```

---

## 作者：喵の耳 (赞：0)

我是个菜鸡我不会哈希QwQ


------------
 

转化题意：求最长的相同前缀后缀

发现对于一个循环同构串类似于
$abcdxxxxabcd > bcdxxxxabc$

有$f[i]>=f[i-1]-2$

也就是$f[i-1]<=f[i]-2$

满足单调性，倒序枚举$i$同时判断可行性

这题好像必须双哈希

## 取模一定要$+mod%mod+mod%mod$！！！



### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int base1=233;
const int base2=2333;
const int mod1=1e8+9;
const int mod2=1e8+7;
const int N=1e6+10;
ll h1[N],h2[N],p1[N],p2[N];
char s[N];
int n;
inline ll H1(int l,int r){
    return ((h1[r]-h1[l-1]*p1[r-l+1]+mod1)%mod1+mod1)%mod1;
}
inline ll H2(int l,int r){
    return ((h2[r]-h2[l-1]*p2[r-l+1]+mod2)%mod2+mod2)%mod2;
}
inline bool check(int l1,int r1,int l2,int r2){
    return H1(l1,r1)==H1(l2,r2)&&H2(l1,r1)==H2(l2,r2);
}
int main(){
	scanf("%d%s",&n,s+1);
	p1[0]=p2[0]=1;
	for(int i=1;i<=n;i++){
		p1[i]=p1[i-1]*base1%mod1;
		p2[i]=p2[i-1]*base2%mod2;
		h1[i]=(h1[i-1]*base1+s[i])%mod1;
		h2[i]=(h2[i-1]*base2+s[i])%mod2;
	}
	int len=n>>1,pos=0,ans=0;
	for(int i=len;i;i--,pos=min(len-i,pos+2)){
		if(check(1,i,n-i+1,n)){
			while(pos && !check(i+1,i+pos,n-i-pos+1,n-i))pos--;
			ans=max(ans,pos+i);
		}
	}
	printf("%d\n",ans);
	return 0;
}
```


---

