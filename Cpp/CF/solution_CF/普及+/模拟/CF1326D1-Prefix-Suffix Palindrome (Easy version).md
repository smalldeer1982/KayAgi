# Prefix-Suffix Palindrome (Easy version)

## 题目描述

This is the easy version of the problem. The difference is the constraint on the sum of lengths of strings and the number of test cases. You can make hacks only if you solve all versions of this task.

You are given a string $ s $ , consisting of lowercase English letters. Find the longest string, $ t $ , which satisfies the following conditions:

- The length of $ t $ does not exceed the length of $ s $ .
- $ t $ is a palindrome.
- There exists two strings $ a $ and $ b $ (possibly empty), such that $ t = a + b $ ( " $ + $ " represents concatenation), and $ a $ is prefix of $ s $ while $ b $ is suffix of $ s $ .

## 说明/提示

In the first test, the string $ s =  $ "a" satisfies all conditions.

In the second test, the string "abcdfdcba" satisfies all conditions, because:

- Its length is $ 9 $ , which does not exceed the length of the string $ s $ , which equals $ 11 $ .
- It is a palindrome.
- "abcdfdcba" $ = $ "abcdfdc" $ + $ "ba", and "abcdfdc" is a prefix of $ s $ while "ba" is a suffix of $ s $ .

It can be proven that there does not exist a longer string which satisfies the conditions.

In the fourth test, the string "c" is correct, because "c" $ = $ "c" $ + $ "" and $ a $ or $ b $ can be empty. The other possible solution for this test is "s".

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

## 作者：StudyingFather (赞：3)

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

## 作者：xht (赞：3)

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

## 作者：AutumnKite (赞：3)

考场上看到本题的第一想法是枚举前后缀匹配的长度 $l$，然后要求从 $l+1$ 开始的最长回文串或者以 $n-l$ 结尾的最长回文串。

刚打算去隔壁 [最长双回文串](https://www.luogu.com.cn/problem/P4555) 复制一个代码，意识到了不对...

如果求出来的回文串与前后缀有重叠怎么办？

考虑上面这个想法用暴力怎么实现。在我们将原串中间插入 `#` 后，用 manacher 算法以 $i$ 为回文中心的回文半径 $d_i$。

然后我们枚举前后缀匹配长度 $l$，分两种情况：

- 对于所有 $l+1\le i\le \frac{|s|+1}{2}$ 且 $i-d_i+1\le l+1$，求出 $i$ 的最大值；
- 对于所有 $\frac{|s|+1}{2}\le i\le n-l$ 且 $i+d_i-1\ge n-l$，求出 $i$ 的最小值。

直接按上面的暴力实现，复杂度 $O(n^2)$，可以通过 Easy version。

---

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

## 作者：andyli (赞：1)

题意：  
给出字符串 $s$ ，找出最长的回文串 $t$ ，满足：  
- $|t| \leq |s|$，其中 $|s|$ 表示字符串 $s$ 的长度。
- 存在字符串 $a, b$（可以为空串），使得 $t = a+b$ （ `+` 表示连接），且 $a$ 为 $s$ 的前缀，$b$ 为 $s$ 的后缀。  

$1\leq |s|\leq 5000$

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

## 作者：oimaster (赞：1)

在我的[博客](https://oi-master.github.io/post/codeforces-contest-1322-d1-ti-jie/)阅读体验更好哦！

本人太菜，不会 D2 的优化，大佬们自己写吧，欢迎发邮件到 <tianyuzhou123@foxmail.com> 填坑。
## 思路
这道题看看数据范围，发现 $S$ 长度总和才为 $5000$ ，感觉这是一道偏暴力的题目。

然后本蒟蒻就想到一个暴力的算法：枚举开头选几个，同时枚举最后选几个，然后取出这个枚举出来的字符串，判断它是否回文。枚举开头时有 $N+1$ 种可能，结尾也有 $N+1$ 种，然后判断回文也要检查 $\lfloor N \div 2 \rfloor$ 个字符，所以这个算法是 $O(N^3)$ 的，过不了，得想想更好的算法。

但是想这个算法，而没有目标，是不方便的。我们知道，目标算法至少得达到 $O(N^2)$ ，否则一定超时。我们可以这么想：枚举前缀，在枚举后缀，两个是同时的，写两重循环显然不妥。我们可以想办法写一冲循环。也许你会问，这样怎可以？你问的原因是，这个“前”与“后”是同时存在的，如果我们只让它们一个存在，那么是不是我们就可以把三重循环改成两个两重循环了？是的，当然可以。但是让一个存在不是题目的意思，我们还得把这个字符串加工加工。我们把开头、结尾已经成功配对的字符删除，当然，不是真的删除，要不你怎么打印？删除所有的配对字符后，开头与结尾只可能有一个还要继续选，那么你处理一下，选一选判断一下是否回文即可，纯属练坐标控制，没什么难度。
## 代码
工作量有点多，我给个参考代码，请自律不要复制。
```cpp
/*
 * Author: OI_Master
 * Time: 2020-03-20 10:26:42
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
bool huiwen(string s){
	for(int i=0;i<s.size()/2;++i)
		if(s[i]!=s[s.size()-1-i])
			return false;
	return true;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin>>t;
	while(t--){
		string s;
		cin>>s;
		int k=0;
		while(k<s.size()/2&&s[k]==s[s.size()-1-k])
			++k;
		int i=k;
		while(i<s.size()-1-k&&!huiwen(s.substr(i,s.size()-k-i)))
			++i;
		int j=s.size()-1-k;
		while(j>=k&&!huiwen(s.substr(k,j+1-k)))
			--j;
		cout<<s.substr(0,k);
		if(s.size()-k-i<=j+1-k)
			cout<<s.substr(k,j+1-k);
		else
			cout<<s.substr(i,s.size()-k-i);
		cout<<s.substr(s.size()-1-k+1)<<endl;
	}
	return 0;
}
```
本文到此结束，谢谢您的观看。

---

## 作者：devout (赞：0)

这里提供一种使用$kmp$来实现的做法

我们可以把原来的串拆成这种形式$(A)+(B)+(C)+(-A)$

$(A)$和$(-A)$互为反串，$(B)$和$(C)$里面有一个是回文串（假设是$(B)$），那么答案就是$(A)+(B)+(-A)$

那么我们就可以先把最长的$(A)$和$(-A)$找出来

然后看中间那一段，我们要把$(B)$找出来，考虑一个回文串，如果把他反过来，那么还是和原来一样的，所以我们把原串中的$(A)$和$(-A)$切掉之后得到$(B)+(C)$，再把这个串反转一下接到后面，变成$(B)+(C)+(-C)+(B)$，然后跑一遍$kmp$就能够得到最长的$(B)$了

如果在右半部分就反过来再跑一遍就可以

但是注意我们最后的$(B)$不能比$(B)+(C)$还要长，所以我们要找到第一个长度$\leq|(B)+(C)|$的$Border$，最后更新一下就好

记得数组要开两倍

```cpp
# include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=2e6+5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

char s[N],t[N],tt[N];
int T,ls,lt,ltt;
int nxt[N],ans;

void kmp(){
    nxt[1]=0;
    for(int i=2,j=0;i<=lt;i++){
        while(j&&t[i]!=t[j+1])j=nxt[j];
        if(t[j+1]==t[i])j++;
        nxt[i]=j;
    }
    int j=nxt[lt];
    while(j>lt/2){//找到第一个不到一半的Border
        j=nxt[j];
        nxt[lt]=j;
    }
}

int main()
{
    read(T);
    while(T--){
        ls=lt=ltt=0;
        scanf("%s",s+1);
        ls=strlen(s+1);
        int p1=ls;
        Rep(i,1,ls)
            if(s[i]!=s[ls-i+1]){
                p1=i-1;
                break;
            }
        if(p1==ls){printf("%s\n",s+1);continue;}
        for(int i=p1+1;i<=ls-p1;i++)
            t[++lt]=s[i];
        Rep(i,1,lt)t[lt+lt-i+1]=t[i];
        lt=lt+lt;
        kmp();
        Rep(i,lt-nxt[lt]+1,lt)tt[++ltt]=t[i];
        // cout<<nxt[lt]<<endl;
        Rep(i,1,lt/2)swap(t[i],t[i+lt/2]);
        kmp();
        Rep(i,1,p1)printf("%c",s[i]);
        if(nxt[lt]>ltt)
            Rep(i,lt-nxt[lt]+1,lt)printf("%c",t[i]);
        else Rep(i,1,ltt)printf("%c",tt[i]);
        _Rep(i,p1,1)printf("%c",s[i]);
        puts("");
    }
    return 0;
}
```


---

