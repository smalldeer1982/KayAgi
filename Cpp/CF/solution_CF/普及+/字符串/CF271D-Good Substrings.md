# Good Substrings

## 题目描述

You've got string $ s $ , consisting of small English letters. Some of the English letters are good, the rest are bad.

A substring $ s[l...r] $ ( $ 1<=l<=r<=|s| $ ) of string $ s=s_{1}s_{2}...s_{|s|} $ (where $ |s| $ is the length of string $ s $ ) is string $ s_{l}s_{l+1}...s_{r} $ .

The substring $ s[l...r] $ is good, if among the letters $ s_{l},s_{l+1},...,s_{r} $ there are at most $ k $ bad ones (look at the sample's explanation to understand it more clear).

Your task is to find the number of distinct good substrings of the given string $ s $ . Two substrings $ s[x...y] $ and $ s[p...q] $ are considered distinct if their content is different, i.e. $ s[x...y]≠s[p...q] $ .

## 说明/提示

In the first example there are following good substrings: "a", "ab", "b", "ba", "bab".

In the second example there are following good substrings: "a", "aa", "ac", "b", "ba", "c", "ca", "cb".

## 样例 #1

### 输入

```
ababab
01000000000000000000000000
1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
acbacbacaa
00000000000000000000000000
2
```

### 输出

```
8
```

# 题解

## 作者：fuqingchen (赞：8)

# 原题链接

[CF271D Good Substrings](https://www.luogu.com.cn/problem/CF271D)

# 题目简述


在 $26$ 个英文字母中有一些字母是不好的。若一个字符串中包含不超过 $k$ 个不好的字母，则这个字符串是好的。

给你一个字符串 $s$（$|s| \le 1500$），$26$个字母好坏情况和 $k$ ，求出 $s$ 的所有子串中，**本质不同**的好的子串的数量。

两个子串被称为本质不同，当且仅当它们**内容不同**

# 解题思路

首先 $n^2$ 枚举每个子串，在枚举以 $i$ 为起点的子串时，一边枚举一边计算目前是否合法，如何不合法直接退出，否则继续。使用哈希判断是否重复。


# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1510, B = 29;
typedef long long ull;
const ull mod = 1e16 + 19260816 + 10000007 + 2333667;
set<ull> st;
bool a[30];
char s[N], str[30];
int n;//字符串长度
ull pre[N], _pow[N];//B的次幂
int q, h[1510], sum;

signed main() {
	cin >> s + 1 >> str + 1 >> q;
	for(int i = 1; i <= 26; ++i)
		a[i] = str[i] - '0';
	n = strlen(s + 1);
	for (int i = 1; i <= n; ++i) {
		ull x = 0;
		for (int j = i; j <= n; ++j) {
            x = x * B + (s[j] - 96);
            x %= mod;
			if (!a[s[j] - 96]) ++h[i];
            if (h[i] > q) break;
            if (st.find(x) == st.end()) st.insert(x);
		}
    }
	printf("%d", (int)st.size());
	return 0;
}
```

---

## 作者：muyang_233 (赞：5)

[原题传送门](https://www.luogu.com.cn/problem/CF271D)  

好像题解里还没有 $\text{Trie}$ 树的做法，这里提供一个。  

令 $tot$ 为满足答案的子串个数，  
我们考虑枚举每一个子串的开始节点 $i$ ，  
令 $cnt$ 为特殊节点个数， $now$ 为当前节点，  
枚举结束节点 $j$ ，对于每个 $j$ ，首先判断该字符是否为特殊字符，如果是，```cnt++``` ，当 $cnt>k$ 时，枚举下一个 $i$ 。  
之后尝试继续建树，如果发现该子串已被打上标记（即现在所在节点已被赋值），则跳过，否则给该节点打上标记（最好为该子串的发现顺序，也即 ```++tot```）。  
最后直接输出 $tot$ 即可。  
代码：
```cpp
#include <cstdio>
#include <cstring>
using namespace std;
int n;
int k;
int tot;
char sp[29];
char ch[1505];
int TRIE[2250005][29];
//inline void output(int l,int r){
//	printf("[%d,%d]:",l,r);
//	for (int i=l;i<=r;i++){
//		printf("%c",ch[i]);
//	}
//	puts("");
//}
int main(){
	scanf("%s",ch+1);
	scanf("%s",sp+1);
	scanf("%d",&k);
	n=strlen(ch+1);
	for (int i=1;i<=n;i++){
		int now=0,cnt=0; //含义如上文所述
		for (int j=i;j<=n;j++){
			if (sp[ch[j]-'a'+1]=='0'){ //判断特殊字符
				++cnt;
			}
			if (cnt>k){ //如果特殊字符超过k，则枚举下一个i
				break;
			}
//			printf("[%d,%d]:%d\n",i,j,TRIE[now][ch[j]-'a'+1]);
			if (!TRIE[now][ch[j]-'a'+1]){ //该节点未被打上标记，所以打上新标记
				TRIE[now][ch[j]-'a'+1]=(++tot);
//				output(i,j);
			}
			now=TRIE[now][ch[j]-'a'+1]; //进入子节点
		}
	}
	printf("%d",tot); //输出
	return 0;
}

```  
~~这里有AC代码哦，但我相信你不会抄题解的！~~

---

## 作者：Trimsteanima (赞：3)

定义哈希函数 $H(c)=\sum_{i = 1} ^ m c_i*b^{m-i}$

$H(C,K+1)=H(C,K)*b+C_{K+1}$（K个坏字母）

### 用long long

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[3000010], k, x, y, cnt;
char s[3000010], s1[300010];
int main(){
    scanf("%s%s%lld", s, s1, &k);
    for (long long i = 0;s[i]; i ++) {
		x = k, y = 0;
		for (long long j = i; s[j] && (s1[s[j] - 'a'] > '0' || x --); j ++)
			a[cnt ++] = y = (y * 131) ^ s[j];
	}
	sort(a, a + cnt);
	cnt = unique(a, a + cnt) - a;
	printf("%lld\n", cnt);
	return 0;
}
```

---

## 作者：EC75 (赞：2)

### 难度

话说这道题是省选难度欸！

### 思路

首先，构建一个包含给定字符串的所有后缀树（显式后缀树），再按照索引增加的顺序遍历所有子字符串。注意，从一个子字符串移动到下一个子字符串只是将单个字符添加到结束。我们可以轻松维护坏字符的数量，以及树中的“当前”节点。如果坏字符的数量不超过 k，则子字符串是好的。如果我们以前从未这样做过，我们需要标记树的相应节点。答案将是树中标记节点的数量。

还有一个更简单的解决方案，我们使用滚动哈希算法来计算内容不同的子字符串，而不是树。只需对所有好的子字符串的哈希进行排序，然后找到唯一哈希的数量（排序后相同的哈希将位于相邻位置）。但是这些散列通常是不可靠的，所以使用精确的算法总是更好的。

我加上了一些板子，所以会显得代码特别长。不过去掉这些板子其实也可以正常运行。

### 代码

```python
import os
import sys
from io import BytesIO, IOBase
BUFSIZE = 8192
class FastIO(IOBase):
    newlines = 0
    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None
    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()
    def readline(self):
        while self.newlines == 0:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            self.newlines = b.count(b"\n") + (not b)
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines -= 1
        return self.buffer.readline()
    def flush(self):
        if self.writable:
            os.write(self._fd, self.buffer.getvalue())
            self.buffer.truncate(0), self.buffer.seek(0)
class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")
sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")
s = input()
l = [int(k) for k in input()]
bad = set()
for i in range(26):
    if l[i] == 0:
        bad.add(97+i)
k = int(input())
hashes = set()
base = 999983
s = [ord(x) for x in s]
value = 0
badcount = 0
mod = 10**16 + 11
basemod = [1]*1501
for i in range(1, 1501):
    basemod[i] = basemod[i-1] * base % mod
for length in range(1, len(s)+1):
    value = value * base % mod
    value = (value + s[length-1]) % mod
    if s[length-1] in bad:
        badcount += 1
    if badcount <= k:
        hashes.add(value)
    val, brbad = value, badcount
    for i in range(length, len(s)):
        if s[i] in bad:
            brbad += 1
        if s[i-length] in bad:
            brbad -= 1
        val = ((val - s[i-length]*(basemod[length-1]))*base + s[i]) % mod
        if brbad <= k:
            hashes.add(val)
print(len(hashes))
```

---

## 作者：天命之路 (赞：2)

题解区里好像还没有 $O(n\log{n})$ 的 $SA$ 做法，我来交一发

首先考虑限定good substring 的开头，发现如果开头确定，可行的结尾是连续的（显然）

所以可以设 $f[i]$ 表示以 $i$ 开头的最大 good substring 长度

注意到 $f[i] \ge f[i-1] - 1$ (即 good substring 的任何一个子串都是 good substring)

所以我们可以在线性时间内求出 $f$ 

接下来是怎样去重的问题
注意到在 [P2408 不同子串个数](https://www.luogu.com.cn/problem/P2408) 中，我们去重时减去 $\sum\limits_{i=2}^n height[i]$

那我们这里就减去 $\sum\limits_{i=2}^n \min \{ height[i],f[sa[i-1]],f[sa[i]] \}$ 即可

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int fir[N],sec[N],ton[N];
int sa[N];
inline bool cmp(int *r,int i,int j,int l) { return r[i] == r[j] && r[i+l] == r[j+l];}
#define For(i,a,b) for(int i = (a),end_##i = (b);i <= end_##i;i++)
#define Rof(i,a,b) for(int i = (a),end_##i = (b);i >= end_##i;i--)
inline void get_sa(char *s,int *sa,int n,int m)
{
	int *x = fir,*y = sec,*t;
	For(i,1,m) ton[i] = 0;
	For(i,1,n) ton[x[i] = s[i]]++;
	For(i,2,m) ton[i] += ton[i-1];
	Rof(i,n,1) sa[ton[x[i]]--] = i;
	for(int j = 1,p = 1;j <= n;j *= 2,m = p)
	{
		p = 0;
		For(i,n-j+1,n) y[++p] = i;
		For(i,1,n) if(sa[i] > j) y[++p] = sa[i] - j;
		For(i,1,m) ton[i] = 0;
		For(i,1,n) ton[x[i]]++;
		For(i,2,m) ton[i] += ton[i-1];
		Rof(i,n,1) sa[ton[x[y[i]]]--] = y[i];
		t=x;x=y;y=t;p=1;x[sa[1]] = 1;
		For(i,2,n)
		x[sa[i]] = cmp(y,sa[i-1],sa[i],j) ? p : (++p);
	}
}
int rk[N],height[N];
inline void get_hi(char *s,int n)
{
	For(i,1,n) rk[sa[i]] = i;
	int j = 0;
	For(i,1,n)
	{
		if(j) j--;
		while(s[i+j] == s[sa[rk[i]-1] + j]) ++j;
		height[rk[i]] = j;
	}
}
int ST[N][20],lg[N];
inline int lcp(int l,int r)
{
	l = rk[l];r = rk[r];
	if(l > r)swap(l,r);l++;
	int k = lg[r-l+1];
	return min(ST[l][k],ST[r-(1<<k)+1][k]);
}
char s[N];
int n,k;
int f[N];
bool good[26];
int sum[N];
inline int Qry(int l,int r) { return sum[r] - sum[l-1];}
int main()
{
	scanf("%s",s+1);
	string tmp;
	cin>>tmp;
	for(int i = 0;i < 26;i++) good[i] = (tmp[i] - '0');
	scanf("%d",&k);
	n = std::strlen(s+1);
	get_sa(s,sa,n,256);
	get_hi(s,n);

	lg[0] = -1;
	for(int i = 1;i <= n;i++)
		lg[i] = lg[i >> 1] + 1,
		ST[i][0] = height[i];
	for(int j = 1;j <= 19;j++)
		for(int i = 1;i + (1 << j) - 1 <= n;i++)
			ST[i][j] = min(ST[i][j-1],ST[i+(1<<j-1)][j-1]);
	for(int i = 1;i <= n;i++) sum[i] = sum[i-1] + (!good[s[i] - 'a']);
	for(int i = 1;i <= n;i++)
	{
		f[i] = max(f[i-1] - 1,0);
		while(i + f[i] <= n && Qry(i ,i+ f[i]) <= k) ++f[i];
//		printf("%d,%d\n",i,f[i]);
	}
	int ans = 0;
	for(int i = 1;i <= n;i++) ans += f[i];
	for(int i = 1;i < n;i++) ans -= min(lcp(sa[i],sa[i+1]),min(f[sa[i]],f[sa[i+1]]));
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：DennyQi (赞：1)

对于一个子串是不是合法，利用前缀和很容易判出。那么现在问题就在于如何找出每个本质不同的子串了。

考虑对字符串进行后缀排序，排名相邻的后缀有相同部分，就是$LCP$。于是我们预处理出$height$数组，每次跳过$LCP$部分对剩余部分进行统计即可。

复杂度$O(n^2)$

```cpp
/*DennyQi 2019*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int N = 1510;
inline int read(){
    int x(0),w(1); char c = getchar();
    while(c^'-' && (c<'0' || c>'9')) c = getchar();
    if(c=='-') w = -1, c = getchar();
    while(c>='0' && c<='9') x = (x<<3)+(x<<1)+c-'0', c = getchar(); 
    return x*w;
}
char s[N],gb[30];
int n,K,ans,sum[N],sa[N],x[N],y[N],c[N],h[N],rk[N];
inline void Build_SA(int m){
	int p;
	for(int i = 1; i <= m; ++i) c[i] = 0;
	for(int i = 1; i <= n; ++i) ++c[x[i] = s[i]];
	for(int i = 1; i <= m; ++i) c[i] += c[i-1];
	for(int i = n; i >= 1; --i) sa[c[x[i]]--] = i;
	for(int k = 1; k <= n; k += k){
		p = 0;
		for(int i = n-k+1; i <= n; ++i) y[++p] = i;
		for(int i = 1; i <= n; ++i) if(sa[i] > k) y[++p] = sa[i]-k;
		for(int i = 1; i <= m; ++i) c[i] = 0;
		for(int i = 1; i <= n; ++i) ++c[x[i]];
		for(int i = 1; i <= m; ++i) c[i] += c[i-1];
		for(int i = n; i >= 1; --i) sa[c[x[y[i]]]--] = y[i], y[i] = 0;
		swap(x,y);
		x[sa[1]] = 1, p = 1;
		for(int i = 2; i <= n; ++i) x[sa[i]] = (y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]) ? p : ++p;
		if(p >= n) break;
		m = p;
	}
	for(int i = 1; i <= n; ++i) rk[sa[i]] = i;
	int k = 0;
	for(int i = 1; i <= n; ++i){
		if(k) --k;
		while(s[i+k] == s[sa[rk[i]-1]+k]) ++k;
		h[rk[i]] = k;
	}
}
int main(){
	// freopen("file.in","r",stdin);
	scanf("%s\n",s+1);
	scanf("%s\n",gb);
	scanf("%d",&K);
	n = strlen(s+1);
	for(int i = 1; i <= n; ++i){
		sum[i] = sum[i-1] + ((gb[s[i]-'a'] - '0') ^ 1);
	}
	Build_SA('z'+1);
	for(int i = 1; i <= n; ++i){
		for(int j = sa[i]+h[i]; j <= n; ++j){
			if(sum[j]-sum[sa[i]-1] <= K){
				++ans;
			}
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：DarkMoon_Dragon (赞：0)

# $CF271D$ `Good Substrings`

## $Description$
+ 问满足题目包含不超过 $k$ 个不好的字母条件的，本质不同的子串有多少个。

## $Solution$
+ SAM??? LCP??? ~~我都不会~~
+ 首先子串个数是 $n^2$ 的，那么问题变成了合法子串去重。
+ ~~众所周知~~，优秀的字符串 $hash$ 是可以过掉所有字符串的题目的。
+ $Codeforces$ 比赛时可能有人对着你锁掉的程序卡你，但是对于 $CSP$ 这种数据固定的是几乎不可能卡掉你的 $hash$ 的。
+ 这样哈希冲突的概率大概是 $\frac{n^2}{mod}$，只要令 $mod$ 足够大，即保证了 $hash$ 正确性。
+ 问题再次转换成了大整数 $hash$。
+ 这里就有两种经典方法：
	1. 离线排序，或者偷懒用 $set$ 之类的数据结构维护。
    2. $hash$ $list$。还是不对着程序卡几乎卡不掉的方法。时间上比 $set$ 优秀许多。

+ set水过

![](https://cdn.luogu.com.cn/upload/image_hosting/z6q1h72t.png)

```cpp
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
#define rr int
using namespace std;
typedef long long ll;
inline ll read() {
    char i = getchar();
    ll f = 1, res = 0;
    while (i < '0' || i > '9') {
        if (i == '-') f = -1;
        i = getchar();
    }
    while (i >= '0' && i <= '9') {
        res = res * 10 + i - '0';
        i = getchar();
    }
    return f * res;
}
const int N = 1505;
bool pd[N];
char s[N], p[N];
set<ll> st;
set<ll>::iterator ite;
const ll base = 29;
const ll mod = 1e16 + 19260817 + 10000007 + 2333666;
const ll P = 3214567;
int main() {
    scanf("%s", s + 1);
    scanf("%s", p);
    for (rr i = 0; i < 26; ++i) pd[i] = int(p[i] - '0');
    int k = read();
    int n = strlen(s + 1);
    for (rr i = 1; i <= n; ++i) {
        // cout << pd[s[i] - 'a'] << ' ';
        int cnt = 0;
        ll now = 0;
        for (rr j = i; j <= n; ++j) {
            if (!pd[s[j] - 'a']) ++cnt;  //不好的字母不超过 K
            now = now * base + (s[j] - 'a' + 1);
            now %= mod;
            if (cnt <= k) {
                if (st.find(now) == st.end()) {
                    st.insert(now);
                }
            }
            if (cnt > k) break;
        }
    }
    int ans = st.size();
    cout << ans << endl;
}
```

+ hash list

![](https://cdn.luogu.com.cn/upload/image_hosting/noc02g36.png)


```cpp
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
#define rr int
using namespace std;
typedef long long ll;
inline ll read() {
    char i = getchar();
    ll f = 1, res = 0;
    while (i < '0' || i > '9') {
        if (i == '-') f = -1;
        i = getchar();
    }
    while (i >= '0' && i <= '9') {
        res = res * 10 + i - '0';
        i = getchar();
    }
    return f * res;
}
const int N = 1505;
bool pd[N];
char s[N], p[N];
const ll base = 29;
const ll mod = 1e16 + 19260817 + 10000007 + 2333666;
const ll P = 3214567;
struct H {
    int nxt[P], head[P];
    ll key[P];
    int sz;
    int size() { return sz; }
    int find(ll x) {
        int u = x % P;
        for (rr i = head[u]; i; i = nxt[i]) {
            if (key[i] == x) return 1;
        }
        return 0;
    }
    void insert(ll x) {
        ++sz;
        key[sz] = x;
        int u = x % P;
        nxt[sz] = head[u];
        head[u] = sz;
    }
} hashlist;
int main() {
    scanf("%s", s + 1);
    scanf("%s", p);
    for (rr i = 0; i < 26; ++i) pd[i] = int(p[i] - '0');
    int k = read();
    int n = strlen(s + 1);
    for (rr i = 1; i <= n; ++i) {
        // cout << pd[s[i] - 'a'] << ' ';
        int cnt = 0;
        ll now = 0;
        for (rr j = i; j <= n; ++j) {
            if (!pd[s[j] - 'a']) ++cnt;  //不好的字母不超过 K
            now = now * base + (s[j] - 'a' + 1);
            now %= mod;
            if (cnt <= k) {
                if (!hashlist.find(now)) {
                    hashlist.insert(now);
                }
            }
            if (cnt > k) break;
        }
    }
    int ans = hashlist.size();
    cout << ans << endl;
}
```

+ 据说考前发题解 RP++，祝大家CSP2019 RP+++++

---

## 作者：qiyue7 (赞：0)

由于n十分之小  

在SAM的拓扑图上暴力dfs即可，记录深搜到当前节点时已经有几个坏字符的前驱就可以统计方案了复杂度O(n^2)

存在O(nlogn)的做法，需要线段树维护。

```cpp

#define For(n) for(int i=0;i<n;++i)
using namespace std;
const int N = 200100;
struct SAM_node
{
	SAM_node *pre, *next[26];
	int next2_sum;
	int step;
	long child;
	int cnt3;
	int cnt;
	unsigned long long ans;
	int firstpos;
	void clear()
	{
		ans = 0;
		cnt = 0;
		cnt3 = 0;
		pre = 0;
		step = 0;
		firstpos = 0;
		memset(next, 0, sizeof(next));
	}
};
long d[N * 2];
SAM_node *pool[N * 2];
SAM_node SAM_Pool[N * 2];
int part2[26];
int k;
struct SAM 
{
	SAM_node *root, *last;
	SAM_node  *cur;
	void init()
	{
		cur = SAM_Pool;  
		root = last = cur++;
		root->clear();
	}
	void topo()
	{
		// 求出parent树的拓扑序
		int cnt = cur - SAM_Pool;
		int maxVal = 0;
		memset(d, 0, sizeof(d));
		for (int i = 1; i < cnt; i++)
			maxVal = max(maxVal, SAM_Pool[i].step), d[SAM_Pool[i].step]++;
		for (int i = 1; i <= maxVal; i++)
			d[i] += d[i - 1];
		for (int i = 1; i < cnt; i++)
			pool[d[SAM_Pool[i].step]--] = &SAM_Pool[i];
		pool[0] = root;
	}
	void Insert(int w)
	{
		SAM_node *p = last;
		SAM_node *np = cur++;
		np->clear();
		np->step = p->step + 1;
		np->firstpos = np->step - 1; //确定原串初始位置
		while (p && !p->next[w])
		{
			p->next[w] = np, p = p->pre;
		}
		if (p == 0)
			np->pre = root;
		else
		{
			SAM_node *q = p->next[w];
			if (p->step + 1 == q->step)
				np->pre = q;
			else
			{
				SAM_node *nq = cur++;
				nq->clear();
				memcpy(nq->next, q->next, sizeof(q->next));
				nq->firstpos = q->firstpos;
				nq->cnt = q->cnt;
				nq->step = p->step + 1;
				nq->pre = q->pre;
				q->pre = nq;
				np->pre = nq;
				while (p&&p->next[w] == q)
				{
					p->next[w] = nq, p = p->pre;
				}
			}
		}
		last = np;
	}
	void build(string &s)
	{
		init();
		for (int i = 0; i < s.size(); ++i)
			Insert(s[i] - 'a');
	}
	long dfs(SAM_node *part,int p)
	{
		if(part!=root)
		part->ans = 1;
		if (p == k)
		{
			for (int i = 0; i < 26; ++i)
				if (part->next[i] != NULL && part2[i]==1)
				{
					part->ans += dfs(part->next[i], p);
				}
		}
		else
			for (int i = 0; i < 26; ++i)
				if (part->next[i] != NULL)
				{
					if(part2[i] == 1)
					    part->ans += dfs(part->next[i], p);
					else
						part->ans += dfs(part->next[i], p+1);
				}
		return part->ans;
	}
};
int main()
{
	ios::sync_with_stdio(0);
	string a,b;
	cin >> a>>b>>k;
	for (int i = 0; i < 26; ++i)
	{
		part2[i] = b[i] - '0';
	}
	SAM part9;
	part9.build(a);
	cout << part9.dfs(part9.root,0) << endl;
	return 0;
}
```


---

## 作者：_ctz (赞：0)

[$My\ blog$](https://ctz45562.github.io/2019/04/30/洛谷-CF271D-Good-Substrings)

[传送门](https://www.luogu.org/problemnew/show/CF271D)

十分板子的$SAM$题了。

没有$SAM$题解赶紧水一发。

把不好的字母的转移边权值视为$1$，好的字母权值视为$0$，这个题就是求$SAM$上从根节点出发，有多少条路径长度$\le k$。

设$f(i,j)$表示从节点$i$出发，有多少条路径长度为$j$。

方程：$f(i,j)=\sum f(son(i,c),j-ba[c])$（$ba[c]$表示$k$是否为不好的字母）

还有一种路径是直接从$i$到它的儿子的，对于$i$的每一条存在的转移边，$++f(i,ba[c])$即可。

答案为$\sum\limits_{i=0}^{k}f(1,i)$。因为$SAM$包含的子串不重不漏，所以求出来的也就本质不同。

复杂度看起来有点假，实际上分析一波就会发现转移次数不超过边数，单次转移是$O(n)$的，总复杂度$O(n^2)$

代码：

``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

#define maxn 5005
#define inf 0x3f3f3f3f

using namespace std;

inline int read(){
	int x=0,y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}
#define son(x,y) son[x][y]
int son[maxn][26],fa[maxn],len[maxn],f[maxn][1505],n,m,k,last=1,cnt=1;
bool vis[maxn],ba[26];
char s[maxn];
void insert(int c){
	int p=last,ne=last=++cnt;
	len[ne]=len[p]+1;
	while(p&&!son(p,c))son(p,c)=ne,p=fa[p];
	if(!p)fa[ne]=1;
	else {
		int q=son(p,c);
		if(len[q]==len[p]+1)fa[ne]=q;
		else {
			int sp=++cnt;
			memcpy(son[sp],son[q],sizeof son[q]);
			fa[sp]=fa[q],len[sp]=len[p]+1,fa[q]=fa[ne]=sp;
			while(p&&son(p,c)==q)son(p,c)=sp,p=fa[p];
		}
	}
}
void dp(int node=1){
	vis[node]=1;
	int x;
	for(register int i=0;i<26;++i){
		x=son(node,i);
		if(!x)continue;
		if(!vis[x])dp(x);
		++f[node][ba[i]];
		for(register int j=0;j<=k;++j)
			if(j-ba[i]>=0)f[node][j]+=f[x][j-ba[i]];
	}
}
int main(){
	scanf("%s",s+1),n=strlen(s+1);
	for(register int i=1;i<=n;++i)insert(s[i]-'a');
	scanf("%s",s+1);
	for(register int i=0;i<26;++i)ba[i]=(s[i+1]=='0');
	k=read(),dp();
	int ans=0;
	for(register int i=0;i<=k;++i)ans+=f[1][i];
	printf("%d\n",ans);
}

```



---

