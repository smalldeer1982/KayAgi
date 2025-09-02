# Prefix-Suffix Palindrome (Hard version)

## 题目描述

这是本题的困难版。 区别在于对字符串长度总和和多测数量的限制。

给你一个由小写英文字母组成的字符串 $s$。找出满足以下条件的最长字符串 $t$：

- $t$ 的长度不超过 $s$ 的长度。
- $t$ 是一个回文字符串。
- 存在两个字符串 $a$ 和 $b$（可能为空，且 $a$ 和 $b$ 不相交），使得 $t=a+b$ （加号表示连接），并且 $a$ 是 $s$ 的前缀，$b$ 是 $s$ 的后缀。

## 说明/提示

在第一个样例中，字符串 `a` 满足所有条件。

在第二个样例中，字符串 `abcdfdcba` 满足所有条件。
- 因为它的长度是 $9$，没有超过字符串 $s$ 的长度 $11$。
- 它是一个回文串。
- `abcdfdcba=abcdfdc+ba`，`abcdfdc` 是 $s$ 的前缀，而 `ba` 是 $s$ 的后缀。

可以证明，不存在满足条件的更长字符串。

在第四次样例中，字符串 `c` 是正确的，因为 `c=c +""(即空串)`，又因为 $a$ 或 $b$ 可以为空。 这个样例的另一个可能解法是 `s`。

## 样例 #1

### 输入

```
5
a
abcdfdcecba
abbaxyzyx
codeforces
acbba```

### 输出

```
a
abcdfdcba
xyzyx
c
abba```

# 题解

## 作者：xht (赞：9)

显然可以先贪心地取互为反串的最长前后缀。

取完扔掉之后，相当于要在剩下的字符串的前缀或后缀找到一个最长的回文串。

manacher 即可，时间复杂度 $\mathcal O(n)$。

```cpp
const int N = 1e6 + 7;
int n, m;
char s[N], t[N];

inline int work(char *s, int n) {
	string ss = "$#";
	vi p;
	for (int i = 1; i <= n; i++) ss += s[i], ss += "#";
	p.pb(1);
	int mx = 0, id = 0, ans = 1;
	for (int i = 1; i < (int)ss.length(); i++) {
		p.pb(mx > i ? min(p[2*id-i], mx - i) : 1);
		while (i + p[i] < (int)ss.length() && ss[i+p[i]] == ss[i-p[i]]) ++p[i];
		if (i == p[i]) ans = max(ans, p[i]);
		if (i + p[i] > mx) mx = i + p[i], id = i;
	}
	return ans - 1;
}

inline void solve() {
	rds(s, n);
	int p = 1;
	while (p <= n && s[p] == s[n+1-p]) ++p;
	if (p == n + 1) {
		for (int i = 1; i <= n; i++) putchar(s[i]);
		return puts(""), void();
	}
	m = 0;
	for (int i = p; i <= n + 1 - p; i++) t[++m] = s[i];
	int l = work(t, m);
	reverse(t + 1, t + m + 1);
	int r = work(t, m);
	reverse(t + 1, t + m + 1);
	if (l < r) reverse(t + 1, t + m + 1), swap(l, r);
	for (int i = 1; i < p; i++) putchar(s[i]);
	for (int i = 1; i <= l; i++) putchar(t[i]);
	for (int i = p - 1; i; i--) putchar(s[i]);
	puts("");
}

int main() {
	int T;
	rd(T);
	while (T--) solve();
	return 0;
}
```

---

## 作者：pmt2018 (赞：7)

给出一种简单的kmp做法。

第一步显然是将s前后相同的字符去掉，作为答案的一部分，比如``abcdba``中答案显然就是``ab``+某一回文串+``ba``

现在我们把剩下的字符串重新把它称为$s$，问题转化为求$s$的最长的回文串前缀或后缀。

我们不妨称$s$的反串为$s'$。

我们构造两个字符串$T_1=s+'\$' +s',T_2=s'+'\$' +s$。

例如对于字符串``abacc``，
$T_1=\mathbf{aba}\text{cc\$c}\mathbf{aba},$ $T_2=\mathbf{cc}\text{aba\$aba}\mathbf{cc}$ 。

不难发现最长的回文串前缀和后缀分别是$T_1,T_2$的最长border(一个border指的是一个与某个后缀相同的前缀)。

这时自然我们对$T_1,T_2$跑一遍kmp求出它们的border即能求出答案。

复杂度显然是$\Theta(|s|)$。

```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define fi first
#define se second

using namespace std;
const int  maxn=4000007;

int T;
string s,rev;
string t;
string s1,s2;
string ans;
int nxt1[maxn],nxt2[maxn];
int ans1,ans2;
bool check(string s){
	for(int i=0;i<s.size();i++){
		if(s[i]!=s[s.size()-i-1])return 0;
	}
	return 1;
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
   	scanf("%d",&T);while(T--){
    
		t="";
   		cin>>s;
   		int len=s.size();
        for(int i=0;i<=2*len;i++)nxt1[i]=nxt2[i]=0;
       	
        if(check(s)){
        	cout<<s<<endl;
        	continue;
        }
   		int p=0,q=len-1;
   		while(s[p]==s[q])p++,q--;
   		t=s.substr(0,p);
   		s=s.substr(p,q-p+1);
   		rev=s;
        reverse(rev.begin(),rev.end());
        s1=s+"$"+rev,s2=rev+"$"+s;
        int j=0;
        for(int i=2;i<=s1.size();i++){
            while(j&&s1[i-1]!=s1[j])j=nxt1[j];
            if(s1[j]==s1[i-1])j++;
            nxt1[i]=j;
        }
        j=0;
        for(int i=2;i<=s2.size();i++){
            while(j&&s2[i-1]!=s2[j])j=nxt2[j];
            if(s2[j]==s2[i-1])j++;
            nxt2[i]=j;
        }
    
        if(nxt1[s1.size()]<nxt2[s2.size()]){
        	ans=s2.substr(0,nxt2[s2.size()]);
        }else{
        	ans=s1.substr(0,nxt1[s1.size()]);
        }
        
        cout<<t<<ans;
        reverse(t.begin(),t.end());
        cout<<t<<endl;
   	}
	return 0;
}
```


---

## 作者：Meatherm (赞：5)

做法楼下的 xht 已经说的很清楚了。先选取互为反串的最长前后缀，然后在剩余字符串中选取最长回文前缀或后缀。

表示不会 manacher，于是用 hash 过了这道题。

考虑记录字符串 $s$ 本身的 hash 值前缀和以及反串的 hash 值前缀和。如果 $s$ 的一个子串 $s [l,r] $ 回文，那么原串 $[l,r]$ 的 hash 值必定和反串对应位置的 hash 值相等。

比赛的时候绝对不要像我一样写单 hash，极大概率被 hack。当然赛后就无所谓了。

```cpp
# include <bits/stdc++.h>
# define rr register
# define int long long
const int N=1000010,INF=0x3f3f3f3f;
int MOD=436522843;
int base=449;
int hash[N],fhash[N];
int n;
int p[N];
char s[N];
int T;
inline int read(void){
	int res,f=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')f=-1;
	res=c-48;
	while((c=getchar())>='0'&&c<='9')
		res=res*10+c-48;
	return res*f;
}
inline int getval(int l,int r){
	return ((hash[r]-hash[l-1]*p[r-l+1])%MOD+MOD)%MOD;
}
inline int fgetval(int l,int r){
	return ((fhash[l]-fhash[r+1]*p[r-l+1])%MOD+MOD)%MOD;
}
signed main(void){
	T=read();
	while(T--){
		scanf("%s",s+1);
		n=strlen(s+1);
		p[0]=1;
		hash[0]=fhash[n+1]=0;
		for(rr int i=1;i<=n;++i){
			p[i]=p[i-1]*base%MOD;
			hash[i]=(hash[i-1]*base+(s[i]-'a'+1))%MOD;
		}
		for(rr int i=n;i;--i){
			fhash[i]=(fhash[i+1]*base+(s[i]-'a'+1))%MOD;
		}
		int len=0;
		for(rr int i=1;i<=n&&(i<n-i+1);++i){
			if(s[i]==s[n-i+1]){
				++len;
			}else{
				break;
			}
		}
		int lans=len,rans=n-len+1;
		for(rr int i=len+1;i<=n-len;++i){
			if(getval(len+1,i)==fgetval(len+1,i)){
				lans=i;
			}
		}
		for(rr int i=n-len;i>=len+1;--i){
			if(getval(i,n-len)==fgetval(i,n-len)){
				rans=i;
			}
		}
		if((lans-(len+1)+1)>((n-len)-rans+1)){
			for(rr int i=1;i<=lans;++i){
				putchar(s[i]);
			}
			for(rr int i=n-len+1;i<=n;++i){
				putchar(s[i]);
			}
		}else{
			for(rr int i=1;i<=len;++i){
				putchar(s[i]);
			}
			for(rr int i=rans;i<=n;++i){
				putchar(s[i]);
			}
		}
		puts("");
	}
	
	return 0;
}

```

---

## 作者：AutumnKite (赞：3)

考场上看到本题的第一想法是枚举前后缀匹配的长度 $l$，然后要求从 $l+1$ 开始的最长回文串或者以 $n-l$ 结尾的最长回文串。

刚打算去隔壁 [最长双回文串](https://www.luogu.com.cn/problem/P4555) 复制一个代码，意识到了不对...

如果求出来的回文串与前后缀有重叠怎么办？

考虑上面这个想法用暴力怎么实现。在我们将原串中间插入 `#` 后，用 manacher 算法以 $i$ 为回文中心的回文半径 $d_i$。

然后我们枚举前后缀匹配长度 $l$，分两种情况：

- 对于所有 $l+1\le i\le \frac{|s|+1}{2}$ 且 $i-d_i+1\le l+1$，求出 $i$ 的最大值；
- 对于所有 $\frac{|s|+1}{2}\le i\le n-l$ 且 $i+d_i-1\ge n-l$，求出 $i$ 的最小值。

可以发现，$l$ 越大，越容易满足限制，越容易使得 $i$ 取到极值。

所以我们求出最大的 $l$ 以后用上面的暴力实现即可。

~~如果你不怕被 hack 的话~~ manacher 也可以用哈希实现。

时间复杂度 $O(n)$。

```cpp
const int N = 2000005; // 注意数组开大一倍
int n, d[N];
char s[N];
void manacher(int *d, char *s, int n){
	for (register int i = 1, m = 0, r = 0; i <= n; ++i){
		d[i] = i > r ? 0 : std::min(r - i + 1, d[m - (i - m)]);
		while (i - d[i] > 0 && i + d[i] <= n && s[i - d[i]] == s[i + d[i]]) ++d[i];
		if (i + d[i] - 1 > r) m = i, r = i + d[i] - 1;
	}
}
void solve(){
	n = reads(s + 1);
	for (register int i = n; i; --i) s[i << 1] = s[i], s[i << 1 | 1] = '#';
	s[1] = '#', n = n * 2 + 1;
	manacher(d, s, n);
	// for (register int i = 1; i <= n; ++i) debug("%d ", d[i]); debug("\n");
	int len = 0;
	for (register int i = 1; i <= n / 2; ++i)
		if (s[i] != s[n - i + 1]) break;
		else ++len;
	// debug("%d\n", len);
	int d1 = 0, d2 = 0;
	for (register int i = len + 1; i <= (n + 1) / 2; ++i)
		if (i - d[i] + 1 <= len + 1) d1 = std::max(d1, (i - len) * 2 - 1);
	for (register int i = (n + 1) / 2; i <= n - len; ++i)
		if (i + d[i] - 1 >= n - len) d2 = std::max(d2, (n - len - i + 1) * 2 - 1);
	if (d1 > d2){
		for (register int i = 1; i <= len + d1; ++i)
			if (s[i] != '#') putchar(s[i]);
		for (register int i = n - len + 1; i <= n; ++i)
			if (s[i] != '#') putchar(s[i]);
	}
	else{
		for (register int i = 1; i <= len; ++i)
			if (s[i] != '#') putchar(s[i]);
		for (register int i = n - len - d2 + 1; i <= n; ++i)
			if (s[i] != '#') putchar(s[i]);
	}
	putchar('\n');
}
```

---

## 作者：andyli (赞：3)

题意：  
给出字符串 $s$ ，找出最长的回文串 $t$ ，满足：  
- $|t| \leq |s|$，其中 $|s|$ 表示字符串 $s$ 的长度。
- 存在字符串 $a, b$（可以为空串），使得 $t = a+b$ （ `+` 表示连接），且 $a$ 为 $s$ 的前缀，$b$ 为 $s$ 的后缀。  

$1\leq |s|\leq 10^6$

### $\mathcal O(n^2)$ 解法

找出最大的 $p (1\leq p\leq \left\lfloor\dfrac{|s|}{2}\right\rfloor)$，使得 $\text{pre}(s,p)=\text{rev}(\text{suf}(s,p))$，则 $p$ 一定为 $a$ 的前缀，且 $\text{rev}(p)$ 为 $b$ 的后缀。  
在剩余的子串 $s\,[p+1,|s|-p]$ 中找出为回文串的最长前缀与最长后缀，选长度较大的那一个作为答案。  

例如，`s=abcdaaadacba`，此时 $p=3$ ，在剩余的子串 `daaada` 中找出的为回文串的最长前缀为 `daaad`，最长后缀为 `ada`，由于找出的前缀长度较大，因此选 `daaad` 作为答案，可知 `a=abcdaaad`，`b=cba`，`t=abcdaaadcba`。

代码如下（[快读模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
#include <algorithm>
#include <cstring>
#include <string>
const int maxn = 5005;

char str[maxn];
bool ispalid(const std::string& str) // 字符串 str 是否为回文串
{
    std::string t = str;
    std::reverse(t.begin(), t.end());
    return t == str;
}
int main()
{
    int q;
    io.read(q);
    while (q--) {
        io.read(str + 1);
        int n = strlen(str + 1);
        std::string s(str + 1);
        int p = 0;
        for (int i = 1; i <= n / 2; i++)
            if (str[i] == str[n - i + 1])
                p = i;
            else
                break;
        int cnt1 = 0, cnt2 = 0;
        for (int i = p + 1; i <= n - p; i++) {
            if (ispalid(s.substr(p, i - p)))
                cnt1 = i;
            if (ispalid(s.substr(n - i, i - p)))
                cnt2 = i;
        }
        for (int i = 1; i <= p; i++)
            io.write(str[i]);
        if (cnt1 > cnt2)
            for (int i = p + 1; i <= cnt1; i++)
                io.write(str[i]);
        else
            for (int i = n - cnt2 + 1; i <= n - p; i++)
                io.write(str[i]);
        for (int i = n - p + 1; i <= n; i++)
            io.write(str[i]);
        writeln();
    }
    return 0;
}
```

### $\mathcal O(n)$ 解法

把 $\mathcal O(n^2)$ 解法中判断前缀与后缀是否为回文串的朴素做法改为双模数哈希匹配即可。  

代码如下（[快读模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
#include <algorithm>
#include <cstring>
const int maxn = 1000005, MOD1 = 1e9 + 7, MOD2 = 1e9 + 9, b1 = 31, b2 = 79;

int p1[maxn], p2[maxn], hash1[maxn], hash2[maxn], hash3[maxn], hash4[maxn], n;
char str[maxn];
bool issame(int l, int r, int x, int y) // 子串 l-r 是否与 rev(x-y) 相等
{
    x = n - x + 1, y = n - y + 1;
    std::swap(x, y);
    int x1 = (hash1[r] - 1LL * hash1[l - 1] * p1[r - l + 1] % MOD1 + MOD1) % MOD1;
    int x2 = (hash2[r] - 1LL * hash2[l - 1] * p2[r - l + 1] % MOD2 + MOD2) % MOD2;
    int x3 = (hash3[y] - 1LL * hash3[x - 1] * p1[y - x + 1] % MOD1 + MOD1) % MOD1;
    int x4 = (hash4[y] - 1LL * hash4[x - 1] * p2[y - x + 1] % MOD2 + MOD2) % MOD2;
    return x1 == x3 && x2 == x4;
}
bool ispalid(int l, int r) // 子串 l-r 是否为回文串
{
    int len = r - l + 1;
    return issame(l, l + (len - 1) / 2, l + len / 2, r);
}
int main()
{
    int q;
    io.read(q);
    p1[0] = p2[0] = 1;
    for (int i = 1; i <= 1000000; i++)
        p1[i] = 1LL * p1[i - 1] * b1 % MOD1, p2[i] = 1LL * p2[i - 1] * b2 % MOD2;
    while (q--) {
        io.read(str + 1);
        n = strlen(str + 1);
        for (int i = 1; i <= n; i++)
            hash1[i] = (1LL * hash1[i - 1] * b1 + str[i]) % MOD1;
        for (int i = 1; i <= n; i++)
            hash2[i] = (1LL * hash2[i - 1] * b2 + str[i]) % MOD2;
        for (int i = n; i >= 1; i--)
            hash3[n - i + 1] = (1LL * hash3[n - i + 1 - 1] * b1 + str[i]) % MOD1;
        for (int i = n; i >= 1; i--)
            hash4[n - i + 1] = (1LL * hash4[n - i + 1 - 1] * b2 + str[i]) % MOD2;
        int p = 0;
        for (int i = 1; i <= n / 2; i++)
            if (str[i] == str[n - i + 1])
                p = i;
            else
                break;
        int cnt1 = 0, cnt2 = 0;
        for (int i = p + 1; i <= n - p; i++) {
            if (ispalid(p + 1, i))
                cnt1 = i;
            if (ispalid(n - i + 1, n - p))
                cnt2 = i;
        }
        for (int i = 1; i <= p; i++)
            io.write(str[i]);
        if (cnt1 > cnt2)
            for (int i = p + 1; i <= cnt1; i++)
                io.write(str[i]);
        else
            for (int i = n - cnt2 + 1; i <= n - p; i++)
                io.write(str[i]);
        for (int i = n - p + 1; i <= n; i++)
            io.write(str[i]);
        writeln();
    }
    return 0;
}
```

---

## 作者：Singercoder (赞：2)

本题解内容可能超出本题范围，建议浏览其他题解明确基本思路后再观看本题解，可作为kmp算法的知识扩充。

以下题解是从本人博客关于kmp多角度理解的博客中截取的**静态角度**例题分析，如需完整分析建议访问[多角度kmp详解](https://www.luogu.com.cn/blog/SingerCoder/post-zi-fu-chuan-kmp-jing-tai-jiao-du-kmp-yang-xie#)。

虽然如此，我也会尽量用最简短的语言，让大家不必看完原博客就能理解静态角度的**最长前后缀匹配**。

由于相关理论可能并不新颖，而且仅为初学kmp的作者自己总结，如和已有观点重合，还请海涵，并务必向我告知，在此感激不尽。

# kmp与最长前后缀匹配（静态角度分析）

最基础的kmp，及其静态动态两种角度的理解，本人博客中已有叙述。这道题是对kmp的**最长前后缀匹配**的应用。（注意静态动态并不冲突，而是不同层面上**相互补充**的关系）

+ 动态角度理解：

  定义i为文本串a的匹配指针，j为模式串b的匹配指针。

  j=nxt[j]相当于模式串整体向右移动j-nxt[j]
  
  如此，简洁明了。
  
+ 静态角度理解：

  具体定义i为文本串**下次将要**匹配的位置，定义j为模式串**已经匹配**了的位置（我们称其为**已匹配串**）。（因此进一步的匹配应该是匹配a[i]与b[j+1]）

  这种理解角度中最大的特点在于将**模式串的移动**（即向右移动j-nxt[j]），理解为**已匹配串的缩短**(即j缩短为nxt[j])。本质相同，只是理解方式有区别，但静态角度更方便理解如何求解**最长前后缀匹配**。

+ 定义**最长前后缀匹配**：指求出一个串的前缀与另一个串的后缀的最长匹配，在kmp算法中体现为文本串某子串的后缀与模式串前缀的最长匹配，这也是kmp算法的核心。

+ 关于kmp求**最长前后缀匹配**，就是在已知转移数组，匹配文本串和模式串的过程中，我们根据静态角度理解可知：“在kmp算法每次循环结束后，j始终保存的是文本串第i位的最长匹配。”（这句是静态角度的核心，建议反复阅读理解）细究一下存的这个匹配究竟是什么，不难发现，这个最长匹配指的是 **文本串以i结尾的后缀** 和 **模式串以j结尾的前缀** 的最长匹配，也就是我们提到的**最长前后缀匹配**。

```cpp
//本人的kmp模板，直接放出防止读者理解有偏差
for(int i=2,j=0;i<=m;++i)
{
    while(j && b[i]!=b[j+1])j=nxt[j];
    if(b[i]==b[j+1])++j;
    nxt[i]=j;
}
for(int i=1,j=0;i<=n;++i)
{
    while(j && a[i]!=b[j+1])j=nxt[j];
    if(a[i]==b[j+1])++j;
    if(j==m)
    {
        printf("%d\n",i-j+1); 
        j=nxt[j];
    }
}
```

# 题目解析

回到这道题，给定一个总串s，定义t=某个前缀+某个后缀（不重叠），使得它们组成的串回文。求出最长的回文串。

1. 不难想到最基本的贪心：先求出等长的前后缀，使得组成的串回文（我们称其为初始串）。则由贪心，初始串应该越长越好。

2. 然后得到去掉初始串后的剩余串（称为剩余子串），则我们需要分别求出剩余子串的一个前缀和一个后缀，要求这个前缀和后缀各自回文且最长，在二者中选择最长的，与初始串一同组成最终的t。

   那么问题来了，如何求出剩余子串的最大回文子串？manacher（~~本人不会~~）？注意观察性质，这里我们要求的最大回文子串必须是剩余子串的前缀或后缀，这种定下一个端点的限制给了我们可操作的空间：设a=正向剩余子串，b=反向剩余子串，并设计函数kmp(char $ * $a,char $ * $b），返回值为a串（文本串）后缀与b串（模式串）前缀的最长匹配（不理解可以见上kmp与**最长前后缀匹配**，或看下方代码）。则：

   正向（左侧）最长回文长度len1=kmp(b,a);（反向后缀和正向前缀的最大匹配）
  
   反向（右侧）最长回文长度len2=kmp(a,b);（正向后缀和反向前缀的最大匹配）
  
   由此得到剩余子串两侧各自的最大回文子串。
  
   Talk is cheap,show me the code（其实cf上给的正解，是直接把我在此理解的最长前后缀的匹配，变成了求组合出的新串的nxt数组。窃以为这样虽巧妙，却不能体现kmp求最长前后缀匹配的实质）
  
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=1000010;
int n,len,len1,len2;//初始长度，子串长度，正向回文长度，反向回文长度 
char s[MAXN],a[MAXN],b[MAXN];//初始字符串，正向子串，反向子串 

int nxt[MAXN];
int kmp(char *a,char *b)//求a的后缀和b的前缀的最长匹配 
{
	for(int i=2,j=0;i<=len;++i)
	{
		while(j && b[i]!=b[j+1])j=nxt[j];
		if(b[i]==b[j+1])++j;
		nxt[i]=j;
	}
	for(int i=1,j=0;i<=len;++i)
	{
		while(j && a[i]!=b[j+1])j=nxt[j];
		if(a[i]==b[j+1])++j;
		if(i==len)return j;//直接返回文本串第i位的最长前后缀匹配长度
	}
}
void solve()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	//初始化回文
	int p1=0,p2=n+1;
	while(p1+1<p2-1 && s[p1+1]==s[p2-1]){++p1;--p2;}//前后初始串不能重叠 
	//收集正反向子串 
	len=p2-p1-1;
	for(int i=1;i<=len;++i){a[i]=s[p1+i];b[i]=s[p2-i];}
	//双向求子串的最大回文
	len1=kmp(b,a);//正向最大回文 
	len2=kmp(a,b);//反向最大回文 
	//输出最终字符串 
	for(int i=1;i<=p1;++i)putchar(s[i]);//前初始串 
	if(len1>len2)for(int i=1;i<=len1;++i)putchar(s[p1+i]);//正反向回文中最大的 
	else for(int i=len2;i>=1;--i)putchar(s[p2-i]);
	for(int i=p2;i<=n;++i)putchar(s[i]);//后初始串 
	printf("\n");
}
int main()
{
//	freopen("in.txt","r",stdin);
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;++i)solve();
	return 0;
}
```

仅为个人理解，并非新理论，欢迎交流。

---

## 作者：StudyingFather (赞：2)

答案可以分为两部分：

1. 满足 $\forall i \in [1,k] s_i =s_{i-k+1}$ 的最大的 $k$ 对应的长度为 $k$ 的前缀和后缀；
2. 删除 1 后形成的新串的最长回文前/后缀。

对于第一部分，可以维护两个指针，从两端向中间扫。

对于第二部分，通过枚举中间点向两边扩展的时间复杂度为 $O(n^2)$，可以通过 D1。

当然可以通过 Manacher 来优化上述过程，从而将时间复杂度降到 $O(n)$，可以通过 D2。

下面是 $O(n)$ 的代码：

```cpp
// Problem : D2. Prefix-Suffix Palindrome (Hard version)
// Contest : Codeforces Global Round 7
// URL : https://codeforces.com/contest/1326/problem/D2
// Author : StudyingFather
// Site : https://studyingfather.com
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <cstring>
#include <iostream>
using namespace std;
char s[1000005],t[2000005];
int f[2000005];
void init()
{
 t[0]=t[1]='#';
 int len=strlen(s);
 for(int i=0;i<len;i++)
 {
  t[2*i+2]=s[i];
  t[2*i+3]='#';
 }
 t[2*len+2]=0;
}
int main()
{
 int T;
 cin>>T;
 while(T--)
 {
  cin>>s;
  init();
  int len=strlen(t+1),l=1,r=len;
  while(l<=r)
  {
   if(t[l]==t[r])l++,r--;
   else break;
  }
  int ans=0,nl=l,nr=l,maxr=l,mid=l;
  for(int i=l;i<=r;i++)
  {
   if(i<maxr)
    f[i]=min(f[mid]+(mid-i),f[mid*2-i]);
   else
    f[i]=1;
   while(t[i+f[i]]==t[i-f[i]]&&i+f[i]<=r&&i-f[i]>=l)
    f[i]++;
   if(f[i]+i>maxr)
   {
    maxr=f[i]+i;
    mid=i;
   }
   if((i-f[i]<l||i+f[i]>r)&&f[i]>ans)
   {
    nl=i-f[i]+1;
    nr=i+f[i]-1;
    ans=f[i];
   }
  }
  if(l>r)
  {
   cout<<s<<endl;
   continue;
  }
  for(int i=1;i<l;i++)
   if(t[i]!='#')cout<<t[i];
  for(int i=nl;i<=nr;i++)
   if(t[i]!='#')cout<<t[i];
  for(int i=r+1;i<=len;i++)
   if(t[i]!='#')cout<<t[i];
  cout<<endl;
 }
 return 0;
}

---

## 作者：Owen_codeisking (赞：2)

恭喜你发现一只数据结构学傻了的 sb……

先用字符串哈希正反求一遍，答案转换成一个位置开头/结尾，最长回文串，并且长度 $\le len$。

。。。

。。。

。。。

然后你发现你 manacher 忘了。。。

没事，还有回文树！

正反建出回文树，在回文树上倍增即可。

时间 $\mathcal{O}(n\log n)$

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1000005;
const ll base=233;
const ll mod1=998244353;
const ll mod2=1e9+7;
int n,k,ch[maxn][26],fa[maxn],len[maxn],pos[maxn],f[maxn][21],last,cnt;
char s[maxn];
struct HASH
{
	ll a,b;
	HASH(ll a_=0,ll b_=0):a(a_),b(b_) { }
	inline HASH rev() { return HASH((mod1-a)%mod1,(mod2-b)%mod2); }
	inline HASH operator * (const ll &x) { return HASH(a*x%mod1,b*x%mod2); }
	inline HASH operator * (const HASH &x) { return HASH(a*x.a%mod1,b*x.b%mod2); }
	inline HASH operator + (const HASH &x) { return HASH((a+x.a)%mod1,(b+x.b)%mod2); }
	inline bool operator == (const HASH &x) { return a==x.a && b==x.b; }
};
HASH sum[2][maxn],b[maxn];
inline HASH get1(int l,int r) { return sum[0][r]+(sum[0][l-1]*b[r-l+1].rev()); }
inline HASH get2(int l,int r) { return sum[1][l]+(sum[1][r+1]*b[r-l+1].rev()); }
inline void chkmax(int &a,int b) { a=(a>b)?a:b; }
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",s+1); n=strlen(s+1);
		b[0]=HASH(1,1);
		for(int i=1;i<=n;i++) b[i]=b[i-1]*base,sum[0][i]=(sum[0][i-1]*base)+HASH(s[i],s[i]);
		sum[1][n+1]=HASH(0,0);
		for(int i=n;i;i--) sum[1][i]=(sum[1][i+1]*base)+HASH(s[i],s[i]);
		int res=0,l_=0,r_=n+1;
		s[0]='#',len[0]=0,len[1]=-1,fa[0]=1,cnt=1,last=0;
		int p,c,r,q;
		for(int i=1;i<=n;i++)
		{
			p=last,c=s[i]-'a';
			while(s[i-len[p]-1]!=s[i]) p=fa[p];
			if(!ch[p][c])
			{
				r=++cnt,len[r]=len[p]+2,q=fa[p];
				while(s[i-len[q]-1]!=s[i]) q=fa[q];
				fa[r]=ch[q][c],ch[p][c]=r;
			}
			last=ch[p][c],pos[i]=last;
		}
		for(int i=0;i<=cnt;i++) f[i][0]=fa[i];
		for(int j=1;j<=20;j++)
			for(int i=0;i<=cnt;i++) f[i][j]=f[f[i][j-1]][j-1];
		for(int i=0;i<=n/2;i++)
			if(sum[0][i]==sum[1][n-i+1])
			{
				int x=pos[n-i];
				for(int j=20;j>=0;j--)
					if(f[x][j] && len[f[x][j]]>n-2*i) x=f[x][j];
				if(len[x]>n-2*i) x=fa[x];
				if(len[x]+2*i>res)
					res=len[x]+2*i,l_=i,r_=n-i+1-len[x];
			}
		for(int i=0;i<=cnt;i++)
		{
			fa[i]=len[i]=pos[i]=0;
			memset(ch[i],0,sizeof(ch[i]));
		}
		last=cnt=0;
		reverse(s+1,s+n+1);
		s[0]='#',len[1]=-1,fa[0]=1,cnt=1,last=0;
		for(int i=1;i<=n;i++)
		{
			p=last,c=s[i]-'a';
			while(s[i-len[p]-1]!=s[i]) p=fa[p];
			if(!ch[p][c])
			{
				r=++cnt,len[r]=len[p]+2,q=fa[p];
				while(s[i-len[q]-1]!=s[i]) q=fa[q];
				fa[r]=ch[q][c],ch[p][c]=r;
			}
			last=ch[p][c],pos[i]=last;
		}
		for(int i=0;i<=cnt;i++) f[i][0]=fa[i];
		for(int j=1;j<=20;j++)
			for(int i=0;i<=cnt;i++) f[i][j]=f[f[i][j-1]][j-1];
		for(int i=0;i<=n/2;i++)
			if(sum[0][i]==sum[1][n-i+1])
			{
				int x=pos[n-i];
				for(int j=20;j>=0;j--)
					if(f[x][j] && len[f[x][j]]>n-2*i) x=f[x][j];
				if(len[x]>n-2*i) x=fa[x];
				if(len[x]+2*i>res)
					res=len[x]+2*i,l_=i+len[x],r_=n-i+1;
			}
		reverse(s+1,s+n+1);
		for(int i=1;i<=l_;i++) putchar(s[i]);
		for(int i=r_;i<=n;i++) putchar(s[i]);
		putchar('\n');
		for(int i=0;i<=cnt;i++)
		{
			fa[i]=len[i]=0;
			memset(ch[i],0,sizeof(ch[i]));
		}
		last=cnt=0;
	}
	return 0;
}
```

---

## 作者：MVP_Harry (赞：1)

来一发KMP的题解。

首先，我们可以手玩一下样例，比如```abcdfdcecba```。不难发现，两头的```abc```和```cba```是“白取白不去”的。严格来讲，如果```ans```是满足条件的，那在其两段各添加同样的字母，```ans```就会变大。

然后，我们就可以直接删除首尾两端的回文串。比如```abcdfdcecba```就变成了```dfdce```，那么对于这个子串，我们需要找出它最长回文前缀（和后缀，但只需要reverse一下就可以转换）。

容易想出一个$O(n^2)$的算法，但这样肯定会T掉。所以，我们用KMP对问题进行转换：将这个子串reverse一下，添加到后面，并在其中间插一个任意字符。例如，```dfdce```可变成```dfdce#ecdfd```。对这个串，我们跑一遍kmp即可。

具体代码如下：

```
#include<bits/stdc++.h>
#define ll long long
#define rep(i, m, n) for (int i = m; i <= n; i++)
#define per(i, m, n) for (int i = m; i >= n; i--)
#define pb push_back
#define mp make_pair
#define all(v) v.begin(), v.end()
#define INF 0x3f3f3f3f
using namespace std;

int kmp(string s) {
    string kmprev = s;
    reverse(all(kmprev));
    string kmp = s + "#" + kmprev;
    vector<int> lps(kmp.size(), 0);
    for (int i = 1; i < (int) lps.size(); i++) {
        int prev_idx = lps[i - 1];
        while (prev_idx > 0 && kmp[i] != kmp[prev_idx]) {
            prev_idx = lps[prev_idx - 1];
        }
        lps[i] = prev_idx + (kmp[i] == kmp[prev_idx] ? 1 : 0);
    }
    return lps[lps.size() - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    // KMP O(n) to find the longest palindrome prefix
    int testcase;
    cin >> testcase;
    while (testcase--) {
        string str;
        cin >> str;
        int l = 0, r = str.length() - 1, ans = 0;
        while (l < r) {
            if (str[l] == str[r]) ans++, l++, r--;
            else break;
        }
        string s = str.substr(ans, str.length() - 2 * ans);
        string x;
        int res = kmp(s);
        x = s.substr(0, res);
        reverse(all(s));
        int res2 = kmp(s);
        if (res2 > res) x = s.substr(0, res2);
        string y = str.substr(0, ans);
        string final_answer;
        final_answer = y + x;
        reverse(all(y));
        final_answer += y;
        cout << final_answer << "\n";
    }
    return 0;
}
```

---

## 作者：OMG_wc (赞：1)

题意：给一个字符串 $s$ ，求一个不超过 $s$ 长度的回文串 $t$ 满足 $t=a+b$，其中 $a$ 为 $s$ 的前缀，$b$ 为 $s$ 后缀，要求 $t$ 的长度尽可能的长。

首先根据样例我们就知道一开始肯定是贪心地一前一后把能配对的字符都配对光，这样 $s$ 就只剩下的了 $s’$。比如`abcdfdcecba`这个字符串就直接把前后的`abc`和`cba`取出来，剩下的 $s’$ 为`dfdce`。然后在 $s’$ 里要取最大回文前缀，要么取最大回文后缀。只要会求前者，那后者用同样方法把 $s’$ 转置一下就能算出来。

求某个字符串 $S$ 的最大回文前缀方法有很多，讲一种显然的：

转置字符串 $S$ 得到字符串 $T$，那 $S$ 的回文前缀就是 $T$ 的回文后缀。假设字符串长度为 $n$，$G_i$ 为 $T$ 从第 $i$ 个字符开始的后缀串，即 $G_i=T_iT_{i+1}T_{i+2}\ldots T_n$。一个显然的结论是：如果 $LCP(G_i,S)=G_i $ ，那 $G_i$ 就是个回文串。（画个图就明白了）

要求 $T$ 的所有后缀和 $S$ 的 LCP，用 Z 算法（~~扩展KMP~~）解决即可 。我们在枚举的时候，$i$ 从小到大找到的第一个回文串就是最长的。

事实上，直接用 KMP 也一样，只要考虑 $T$ 最大的后缀和 $S$ 前缀的匹配。

时间复杂度 $O(|s|)$，代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const int N = 1000005;

char s[N], g1[N], g2[N], ans[N];

int z[N], ex[N];
// 求文本串t的z函数
void get_z(char s[], int n) {
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        int &k = z[i];
        k = i <= r ? min(z[i - l], r - i + 1) : 0;
        while (i + k < n && s[i + k] == s[k]) k++;
        if (i + k - 1 > r) r = i + k - 1, l = i;
    }
}
// 求extend，即s的每一个后缀串与t的 LCP
void get_ex(char s[], char t[], int n, int m) {
    for (int i = 0, l = 0, r = 0; i < n; i++) {
        int &k = ex[i];
        k = i <= r ? min(z[i - l], r - i + 1) : 0;
        while (i + k < n && k < m && s[i + k] == t[k]) k++;
        if (i > 0 && i + k - 1 > r) r = i + k - 1, l = i;
    }
}
int gao(char s1[], char s2[], int n) {
    get_z(s1, n);
    get_ex(s2, s1, n, n);
    for (int i = 0; i < n; i++) {
        if (ex[i] == n - i) return n - i;
    }
    return 0;
}
int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        scanf("%s", s);
        int n = strlen(s);
        int t = 0;
        while (t < n / 2 && s[t] == s[n - t - 1]) {
            t++;
        }
        int m = n - t * 2;
        for (int i = 0; i < m; i++) {
            g1[i] = s[t + i];
        }
        for (int i = 0; i < m; i++) g2[i] = g1[m - i - 1];
        int k1 = gao(g1, g2, m);
        int k2 = gao(g2, g1, m);
        int h = 0;
        for (int i = 0; i < t; i++) ans[h++] = s[i];
        if (k1 >= k2) {
            for (int i = 0; i < k1; i++) {
                ans[h++] = g1[i];
            }
        } else {
            for (int i = 0; i < k2; i++) {
                ans[h++] = g2[i];
            }
        }
        for (int i = 0; i < t; i++) ans[h++] = s[t - i - 1];
        ans[h] = 0;
        puts(ans);
    }
    return 0;
}

```

用 KMP 其实更简单，把 `gao` 函数修改成下面代码：

```cpp
int f[N];
int gao(char s1[], char s2[], int n) {
    f[0] = 0;
    for (int i = 1, j = 0; i < n; i++) {
        while (j > 0 && s1[i] != s1[j]) j = f[j - 1];
        if (s1[i] == s1[j]) j++;
        f[i] = j;
    }
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && s2[i] != s1[j]) j = f[j - 1];
        if (s2[i] == s1[j]) j++;
    }
    return j;
}
```



---

## 作者：liqiqi (赞：0)

可以先求出首尾的最大匹配长度，然后中间部分用manacher求前缀的回文和后缀的回文的最大值。
```cpp
#include<bits/stdc++.h>
using namespace std;
int nxt[3000001];
int mlc(string s)
{
	string t = "-*";
	for (int i = 0; i < s.length(); i++)
	{
		t +=s[i];
		t += "*";
	}
	int ans = 0,mx=1,mid=1;
	for (int i = 1; i < t.length(); i++)
	{
		if (i < mx)
			nxt[i] = min(mx - i, nxt[2 * mid - i]);
		else
			nxt[i] = 1;
		while (t[i + nxt[i]] == t[i - nxt[i]])
			nxt[i]++;
		if (i + nxt[i] > mx)
		{
			mx = i + nxt[i];
			mid = i;
		}
		if (i - nxt[i] == 0)
		{
			ans = i;
			
		}
			
	}
	return ans-1;
}
int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		string s;
		cin >> s;
		int l = 0;
		int r = s.length() - 1;
		while (l <= r && s[l] == s[r])
			r--, l++;
		if (l > r)
		{
			cout << s << "\n";
			continue;
		}
		else
		{
			string h1 = s.substr(l, r - l + 1);
			string h2 = h1;
			reverse(h2.begin(), h2.end());
			int len1 = mlc(h1);
			int len2 = mlc(h2);
			if (len1 >= len2)
				cout << s.substr(0, l ) + s.substr(l, len1) + s.substr(r + 1) << "\n";
			else
				cout << s.substr(0, l ) + s.substr(r - len2 + 1, len2) + s.substr(r + 1) << "\n";
		}
	}
}

```


---

