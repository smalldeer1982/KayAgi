# Palindrome pairs

## 题目描述

You are given a non-empty string $ s $ consisting of lowercase letters. Find the number of pairs of non-overlapping palindromic substrings of this string.

In a more formal way, you have to find the quantity of tuples $ (a,b,x,y) $ such that $ 1<=a<=b&lt;x<=y<=|s| $ and substrings $ s[a...\ b] $ , $ s[x...\ y] $ are palindromes.

A palindrome is a string that can be read the same way from left to right and from right to left. For example, "abacaba", "z", "abba" are palindromes.

A substring $ s[i...\ j] $ ( $ 1<=i<=j<=|s| $ ) of string $ s $ = $ s_{1}s_{2}...\ s_{|s|} $ is a string $ s_{i}s_{i+1}...\ s_{j} $ . For example, substring $ s[2...4] $ of string $ s $ = "abacaba" equals "bac".

## 样例 #1

### 输入

```
aa
```

### 输出

```
1
```

## 样例 #2

### 输入

```
aaa
```

### 输出

```
5
```

## 样例 #3

### 输入

```
abacaba
```

### 输出

```
36
```

# 题解

## 作者：BreakPlus (赞：7)

学校考试里面出了这题，发现就我一个写 $O(n^2)$ 紫菜了。

------

首先我们先考虑暴力求出每一个回文串，这个东西可以使用区间 $\text{DP}$ 。我们用 $\operatorname{check}_{i,j}$ 表示 $i \sim j$ 之间的字符是否构成一个回文字符串。得出转移方程式：

$\operatorname{check}_{i,j} =\operatorname{check}_{i+1,j-1} \& (str_i=str_j)$

注意，$\operatorname{check}_{i,i} = \operatorname{check}_{i,i-1} = \text{True}$ 。

然后我们暴力枚举一个回文串。对于每一个回文串区间 $\left[x,y\right]$ ，在区间 $[1,x-1]$ 与 $[y+1,n]$ 中的回文串都能与他配对。我们考虑推出每一个 $\operatorname{F}_{x,y}$，表示一个区间内的回文串数量（可重叠）。

这个不好搞啊？其实也可以用区间 $\text{DP}$。

不需要枚举中转点，我们可以直接推到 $[i+1,j]+[i,j-1]$ 的。然而 $[i+1,j-1]$ 的区间被重复算了，减掉。这是容斥原理的简单应用。注意：如果 $[i,j]$ 是个回文串还得加上 $1$ 。这个我们已经判断过了。

所以，对于每一个回文串都加上 $\operatorname{F}_{1,x-1} + \operatorname{F}_{y+1,n}$ ，最后答案除以 $2$ （设 $\text{A}$ 与 $\text{B}$ 是两个符合题意的回文串，那么统计答案时会被统计为 $\text{A}\&\text{B}$ 和 $\text{B}\&\text{A}$ ）。

下面给一下代码：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define Maxn 2010
char str[Maxn]; long long n,sum[Maxn][Maxn]; bool check[Maxn][Maxn];
long long answer;
int main(){
    scanf("%s",str+1);
    n=strlen(str+1);
    for(int i=1;i<=n;i++) check[i][i-1]=check[i][i]=true,sum[i][i]=1;
    for(int len=2;len<=n;len++)
        for(int i=1,j=len;j<=n;i++,j++){
            if(str[i]!=str[j]) check[i][j]=false;
            else check[i][j]=check[i+1][j-1];
        }
    for(int len=2;len<=n;len++)
        for(int i=1,j=len;j<=n;i++,j++){
            sum[i][j]=sum[i+1][j]+sum[i][j-1]-sum[i+1][j-1];
            if(str[i]==str[j]&&check[i+1][j-1]) sum[i][j]++;
        }
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            if(check[i][j]) answer+=(sum[1][i-1]+sum[j+1][n]);
    printf("%lld\n",answer/2);
    return 0; 
}
```

---

## 作者：7KByte (赞：1)

$1500$ 的题也能紫。

首先我们可以$\rm O(N^2)$预处理出 $c[i][j]$ 表示$S_{i\sim j}$是否为回文串。

然后 $\rm O(N^2)$ 预处理出 $f[i]$ 表示$1\sim i$中有多少个回文串。

最后枚举每一个回文串 $S_{l\sim r}$，将 $f[l-1]$ 累加到答案中。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 2005
using namespace std;
char s[N];int f[N],c[N][N];
int main(){
	scanf("%s",s+1);
	int n=strlen(s+1);
	rep(i,0,n+1)c[i][i]=c[i+1][i]=1;
	pre(l,n-1,1)rep(r,l+1,n)c[l][r]=c[l+1][r-1]&(s[l]==s[r]);
	long long ans=0;
	rep(r,1,n){
		pre(l,r,1)if(c[l][r])ans+=f[l-1],f[r]++;
		f[r]+=f[r-1];
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：DennyQi (赞：1)

我们考虑维护$dp_i$表示区间$[1,i]$中（字符串从1开始存）有多少个回文串（可以重叠）。那么答案就很好统计：每次找到一个回文串$[l,r]$，就给答案加上$dp_{l-1}$。

那么唯一的问题就是找回文串了。考虑同一个中心的回文串是具有连续性的。也就是一旦中断就永远中断。于是我们只需要枚举中心，然后向两边扩张，边统计$dp$边统计答案就好了。

```cpp
/*DennyQi 2019*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define ll long long
using namespace std;
const int N = 2010;
const int P = 998244353;
const int INF = 0x3f3f3f3f;
inline int mul(const int& a, const int& b){ return 1ll*a*b%P; }
inline int add(const int& a, const int& b){ return (a+b>=P)?a+b-P:a+b; }
inline int sub(const int& a, const int& b){ return (a-b<0)?a-b+P:a-b; }
inline int read(){
    int x(0),w(1); char c = getchar();
    while(c^'-' && (c<'0' || c>'9')) c = getchar();
    if(c=='-') w = -1, c = getchar();
    while(c>='0' && c<='9') x = (x<<3)+(x<<1)+c-'0', c = getchar(); 
    return x*w;
}
char s[N];
int n;
ll ans,dp[N];
int main(){
	// freopen("file.in","r",stdin);
	scanf("%s",s+1);
	n = strlen(s+1);
	for(int i = 1; i <= n; ++i){
		dp[i] += dp[i-1];
		for(int j = 0; i+j <= n && i-j >= 1; ++j){
			if(s[i+j] != s[i-j]) break;
			++dp[i+j];
			ans += dp[i-j-1];
		}
		if(i < n && s[i] == s[i+1]){
			for(int j = 0; i+1+j <= n && i-j >= 1; ++j){
				if(s[i+1+j] != s[i-j]) break;
				++dp[i+j+1];
				ans += dp[i-j-1];
			}	
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：QWQ_123 (赞：0)

来一个 Hash 加二分的做法。

先预处理每个字符串的哈希值，然后 $n^2$ 找到所有的区间范围。

然后将这些区间按照左端点从小到大排序，然后对于每一个二分第一个左端点值比他右端点值要大的第一个点，然后从这个点及以后的所有区间都满足条件，算一下即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define int ll

const ll mod = 998244353, Base = 233;

string s, b;
vector<pair<int, int>> v;
ll Hash[2010], powerB[2010], Hash1[2010];

ll get_Hash(int l, int r, ll Hash[]) {
	++l, ++r;
	return (Hash[r] - Hash[l - 1] * powerB[r - l + 1] % mod + mod) % mod;
}

signed main() {
	powerB[0] = 1;
	for (int i = 1; i < 2010; ++i) powerB[i] = powerB[i - 1] * Base % mod;

	cin >> s; b = s;
	reverse(b.begin(), b.end());

	int n = s.size();
	for (int i = 1; i <= n; ++i) Hash[i] = (Hash[i - 1] * Base % mod + s[i - 1] - 'a') % mod;
	for (int i = 1; i <= n; ++i) Hash1[i] = (Hash1[i - 1] * Base % mod + b[i - 1] - 'a') % mod;

	for (int l = 0; l < n; ++l)
		for (int r = l; r < n; ++r) {
			// printf("%d %d, [%d, %d]: [%d, %d]\n", l, r, l, l + (r - l) / 2, n - r - 1, n - r + (r - l) / 2 - 1);
			if (get_Hash(l, l + (r - l) / 2, Hash) == get_Hash(n - r - 1, n - r + (r - l) / 2 - 1, Hash1)) {
				v.push_back({l, r});
			}
		}

	sort(v.begin(), v.end());
	v.push_back({n + 1, n + 1});

	long long ans = 0;

	for (int i = 0; i < (int)v.size() - 1; ++i) {
		int t = v[i].second;

		int l = 0, r = (int)v.size() - 1;
		while (l < r) {
			int mid = (l + r) >> 1;

			if (v[mid].first > t) r = mid;
			else l = mid + 1;
		}

		ans += max(0ll, (ll)v.size() - l - 1ll);

		// cout << v[i].first << ' ' << v[i].second << ' ' << l << ' ' << ans << endl;
	}

	printf("%lld\n", ans);

	return 0;
}
```

---

## 作者：AIskeleton (赞：0)

> [CF159D](https://codeforces.com/problemset/problem/159/D) [Palindrome pairs](https://www.luogu.com.cn/problem/CF159D)

> 给定一个长度为 $n$ 的字符串 $S$，求有多少四元组 $l_1,r_1,l_2,r_2$ 满足 $1 \le l_1 \le r_1 < l_2 \le r_2 \le n$ 且 $S \left[ l_1 \dots r_1 \right],S \left[ l_2 \dots r_2 \right]$ 都是回文字符串。
> $n \le 2000$

因为 $n \le 2000$，所以时间复杂度为 $O(n^2)$ 的 DP 做法可以通过（CF 上的评分是 1500）。

蒟蒻用的是 [manacher](https://www.luogu.com.cn/problem/P3805) 和差分。
题目要求的是**不相交的回文串的对数**。

跑一遍 manacher，求出以字符串中每个字符为中心的**最长回文串的半径**。

可以发现，对于一个范围是 $\left[ l,r \right]$ 的回文串，所有范围在 $\left[ 1,l-1 \right]$ 的回文串都能够与之形成合法的四元组。

假设 $f_i$ 表示以 $i$ 开头的回文串个数，$g_i$ 表示以 $i$ 结尾的回文串个
，易得结果为：

$$\sum_{i=2}^n \sum_{j=1}^{i-1} f_i \times g_j$$

因为在初始化 $f,g$ 时用到的是区间修改,所以利用**差分**解决。对于一个以 $i$ 为中心，最长回文半径为 $l_i$ 的区间修改：
- 数组 $f$ 的修改区间是 $\left[ i-l_i+1,i \right]$，所以分别对 $f_{i-l_i+1},f_{i+1}$ 的差分数组进行修改。
- 数组 $g$ 的修改区间是 $\left[ i,i+l_i-1 \right]$，所以分别对 $g_{i},g_{i+l_i}$ 的差分数组进行修改。

在统计答案时，用一个辅助变量存 $\sum_{j=1}^{i-1} g_j$ 的值，这样就能省去枚举数组求值的过程。
```cpp
#include <bits/stdc++.h>
using namespace std;const int N=3e4;char a[N],b[N<<1];int l[N],n=1,m,p,q;long long f[N],g[N],s,ans;
int main(){
	scanf("%s",a+1);m=strlen(a+1);
	for(int i=1;i<=m;i++,n++)b[++n]=a[i];b[0]=1,b[n+1]=3;
	for(int i=1;i<=n;i++){
		l[i]=(q>i)?min(l[(p<<1)-i],q-i):1;
		while(b[i-l[i]]==b[i+l[i]])++l[i];
		if(i+l[i]>q)q=(p=i)+l[i];
	}for(int i=1;i<=n;i++)f[i-l[i]+1]++,f[i+1]--,g[i]++,g[i+l[i]]--;
	for(int i=1;i<=n;i++){f[i]+=f[i-1],g[i]+=g[i-1];if(!(i&1))ans+=s*f[i],s+=g[i];}
	cout<<ans<<endl;return 0;
}
```

---

## 作者：SunsetSamsara (赞：0)

## 前置知识
manacher 算法，差分
## 分析
首先利用 manacher 算出每个回文半径 $r_i$

为了求出不相交的回文子串个数，令 $L_i$ 表示以 $i$ 为起点的回文子串个数，$R_i$ 表示以 $i$ 为中点的回文子串个数。

接下来对于每个下标 $i$，就需要让 $L_{i-r_i}$ 至 $L_{i}$ 自增 $1$，$R_{i}$ 至 $R_{i+r_i}$ 自增 $1$。可以利用差分快速解决。

下面就可以求出不相交的回文子串个数了。

不相交的回文子串个数就是：
$$\sum \limits_{i=1}^{len(str)}(L[i]\times\sum\limits_{j=1}^i R_j)$$

这个就是答案。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define lld long long
char str1[5000001];
char str2[5000001];
int rd[5000001];
lld l[5000001];
lld r[5000001];
int len;
lld ans;
int main() {
	scanf("%s", str1);
	str2[0] = '@';
	str2[++ len] = '#';
	for(int i = 0; str1[i]; ++ i) {
		str2[++ len] = str1[i];
		str2[++ len] = '#';
	}
	int mx = 0, id = 0;
	for (int i = 1; i <= len; ++i) {
		if(i < mx)rd[i] = min(rd[id * 2 - i],mx-i);
		else rd[i] = 1;
		while(str2[i - rd[i]] == str2[i + rd[i]]) ++ rd[i];
		if(mx < i + rd[i]) {
			id = i;
			mx = i + rd[i];
		}
	}
	// Manacher
	for(int i = 1; i <= len; ++ i) {
		++ l[i - rd[i] + 1];//²î·Ö 
		-- l[i + 1];
		++ r[i];
		-- r[i+rd[i]];
	}
	for (int i = 1; i <= len; ++ i) {
		l[i] += l[i - 1];
		r[i] += r[i - 1];
	}
	lld t = 0;
	for (int i = 1; i <= len; ++ i)
		if(!(i & 1)) { // ÓÐÒâÒåµÄÏÂ±ê 
			ans = ans + t * l[i];
			t = t + r[i];
		}
	printf("%lld\n", ans);
}
```

---

## 作者：Karry5307 (赞：0)

### 题意

给定一个字符串 $S$，求出有多少对四元组 $(l_1,r_1,l_2,r_2)$ 满足 $1\leq l_1\leq r_1<l_2\leq r_2$ 且 $S[l_1\cdots r_1]$ 和 $S[l_2\cdots r_2]$ 为回文串。

$\texttt{Data Range:}\vert S\vert\leq 2000$

### 题解

为啥 CF 都有恶评啊……很明显这个题不止 $1500$ 好吗……

设 $f_i$ 表示以 $i$ 为前缀的回文串的个数，$g_i$ 表示以 $i$ 为后缀的回文串的个数，则答案很明显为

$$\sum\limits_{i=1}^{n}f_i\sum\limits_{j=1}^{i-1}g_j$$

这个可以记录 $g$ 的前缀和来 $O(n)$ 算，于是现在考虑怎么求 $f$ 和 $g$。

暴力枚举每一个子串检查是 $O(n^3)$ 的显然不行，考虑类似于 Manacher 一样的东西，枚举回文串的中点然后更新答案，这样是 $O(n^2)$ 的。

注意到对于一个固定的中点来说，对 $f_i$ 的贡献是一段区间的形式，其中区间右端点为以这个点为中心最长回文子串的长度，$g_i$ 同理，于是 Manacher 求出回文半径之后差分即可，这么做是 $O(n)$ 的。

由于写起来很方便，我这题写了个 $O(n^2)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
ll n,lx,rx;
li res;
string s;
ll h[MAXN],f[MAXN],g[MAXN];
char ch[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	cin>>s,n=s.length(),ch[0]='@',ch[n*2+1]='|';
	for(register int i=0;i<n;i++)
	{
		ch[i*2+1]='|',ch[i*2+2]=s[i];
	}
	for(register int i=1;i<=n*2+1;i++)
	{
		lx=rx=i,ch[i]!='|'?f[i>>1]++,g[i>>1]++:1;
		while(ch[lx-1]==ch[rx+1])
		{
			lx--,rx++,!(lx&1)?f[lx>>1]++,g[rx>>1]++:1;
		}
	}
	for(register int i=1;i<=n;i++)
	{
		g[i]+=g[i-1];
	}
	for(register int i=1;i<=n;i++)
	{
		res+=g[i-1]*f[i];
	}
	printf("%lld\n",res);
}
```

---

## 作者：辰星凌 (赞：0)

# **【题解】Palindrome pairs Codeforces159D**

**传送门：[$Palindrome$ $pairs$](https://www.luogu.org/problem/CF159D) [$[CF159D]$](http://codeforces.com/problemset/problem/159/D)**

## **【题目描述】**

给定一个长度为 $N$ 的字符串 $S$，求有多少四元组 $(l_1,r_1,l_2,r_2)$ 满足 $1 \leqslant l_1 \leqslant r_1 \leqslant l_2 \leqslant r_2 \leqslant N$ 且 $S[l1...r1],$ $[Sl2...r2]$ 都是回文串。

**【样例】**

```cpp
样例输入：
aa
样例输出：
1

样例输入：
aaa
样例输出：
5

样例输入：
abacaba
样例输出：
36
```

**【数据范围】**

$100\%$ $n \leqslant 2000$

-------

## **【分析】**

由于这道题数据较小，直接写暴力也可以过（见[隔壁大佬](https://www.luogu.org/blog/dennyqi/solution-cf159d)），但[$Palisection$ $[CF17E]$](https://www.luogu.org/problem/CF17E)就过不了了，这时候我们需要更高效的算法。

首先，用 $Manacher$ 求出一个 $f[i]$ 数组，用其表示以 $a[i]$ 为中心最多可以匹配的回文串半径，那么就可以递推了。

实际上是要求互不相交的回文串对数，与[$Palisection$ $[CF17E]$](https://www.luogu.org/problem/CF17E)恰恰相反。
对于每一个回文串 $[l,r]$，凡是 $[1,l-1]$ 中的回文串都可以与之形成合法四元组，可以用 $st[i],ed[i]$ 分别表示以 $a[i]$ 开头和以 $a[i]$ 结尾的回文串个数，那么 $ans=\sum_{i=2}^{n}{\sum_{j=1}^{i-1}st[j]*ed[i]}$ 。

初始化时要对 $st,ed$ 进行区间修改，查询时是单点查询，可以用线段树或者树状数组，不过有点麻烦，可以直接存差分数组，然后统计答案时用一个变量 $S$ 优化掉枚举 $st$ 求和的过程。

时间复杂度：$O(n)$ 。

## **【Code】**

```cpp
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
const int N=2003;
int n=1,m,p,q,f[N<<1];LL S,ans,st[N<<1],ed[N<<1];char a[N],b[N<<1];//记得开long long
inline int min(Re a,Re b){return a<b?a:b;}
int main(){
    scanf("%s",a+1),m=strlen(a+1);
    for(Re i=1;i<=m;++i,++n)b[++n]=a[i];//玄学填空法
    b[0]=1,b[n+1]=2;//放置首尾两边多余部分被匹配
    for(Re i=1;i<=n;++i){//Manacher
    	f[i]=q>i?min(f[(p<<1)-i],q-i):1;
    	while(b[i-f[i]]==b[i+f[i]])++f[i];
    	if(i+f[i]>q)q=(p=i)+f[i];
    }
    for(Re i=1;i<=n;++i){
    	++st[i-f[i]+1],--st[i+1];//区间修改[i-f[i]+1,i]
    	++ed[i],--ed[i+f[i]-1+1];//区间修改[i,i+f[i]-1]
    }
    for(Re i=1;i<=n;++i){
    	st[i]+=st[i-1],ed[i]+=ed[i-1];//差分求和算出单个的st,ed
    	if(!(i%2))ans+=S*st[i],S+=ed[i];
    }
    printf("%lld",ans);
}
```


---

## 作者：Paracelestia (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF159D)

## $\texttt{Solution}$

好像没有哈希题解。

考虑维护 $l_i$ 表示以 $s_i$ 为结尾的回文串个数，$r_i$ 表示以 $s_i$ 为起始的回文串个数。答案即为

$$
\sum\limits_{i = 1}^n \sum\limits_{j = i + 1}^n l_i  \times r_j
$$

。

判断回文就使用哈希。时间复杂度 $\mathcal{O}(n^2)$。

别忘了开 long long！

## $\texttt{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;

#define fi first
#define se second

template<typename T> inline T read() {
    T x = 0, f = 1; char ch = 0;
    for(; !isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch - '0');
    return x * f;
}

template<typename T> inline void write(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

template<typename T> inline void print(T x, char ed = '\n') {
    write(x), putchar(ed);
}

#define int long long

const int N = 2e3 + 10, p = 1145141;

int n, l[N], r[N], ans;
string s;

ull hsf[N], hsb[N], pn[N];

signed main() {
	cin >> s;
	n = s.length(), s = ' ' + s;
	for(int i = pn[0] = 1; i <= n; ++ i) {
		pn[i] = pn[i - 1] * p;
		hsf[i] = hsf[i - 1] * p + s[i];
		hsb[i] = hsb[i - 1] * p + s[n - i + 1];
	}
	for(int i = 1; i <= n; ++ i) {
		for(int j = 1; j <= i; ++ j) {
			ull x = hsf[i] - hsf[j - 1] * pn[i - j + 1],
				y = hsb[n - j + 1] - hsb[n - i] * pn[i - j + 1];
			if(x == y) l[i] ++;
		}
		for(int j = i; j <= n; ++ j) {
			ull x = hsf[j] - hsf[i - 1] * pn[j - i + 1],
				y = hsb[n - i + 1] - hsb[n - j] * pn[j - i + 1];
			if(x == y) r[i] ++;
		}
	}
	for(int i = 1; i <= n; ++ i)
		for(int j = i + 1; j <= n; ++ j)
			ans += l[i] * r[j];
	print(ans);
    return 0;
}
```


---

