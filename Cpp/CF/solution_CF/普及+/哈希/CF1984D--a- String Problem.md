# "a" String Problem

## 题目描述

You are given a string $ s $ consisting of lowercase Latin characters. Count the number of nonempty strings $ t \neq $ " $ \texttt{a} $ " such that it is possible to partition $ ^{\dagger} $ $ s $ into some substrings satisfying the following conditions:

- each substring either equals $ t $ or " $ \texttt{a} $ ", and
- at least one substring equals $ t $ .

 $ ^{\dagger} $ A partition of a string $ s $ is an ordered sequence of some $ k $ strings $ t_1, t_2, \ldots, t_k $ (called substrings) such that $ t_1 + t_2 + \ldots + t_k = s $ , where $ + $ represents the concatenation operation.

## 说明/提示

In the first test case, $ t $ can be " $ \texttt{aa} $ ", " $ \texttt{aaa} $ ", " $ \texttt{aaaa} $ ", or the full string.

In the second test case, $ t $ can be " $ \texttt{b} $ ", " $ \texttt{bab} $ ", " $ \texttt{ba} $ ", or the full string.

In the third test case, the only such $ t $ is the full string.

## 样例 #1

### 输入

```
8
aaaaa
baba
cabacb
aaabaaa
bitset
ab
abbaaaabbb
yearnineteeneightyfour```

### 输出

```
4
4
1
16
1
2
3
1```

# 题解

## 作者：Lu_xZ (赞：10)

### D

设 $s$ 长度为 $n$。特判全为 `a` 的情况，共 $n - 1$ 种方案。

设 $s$ 中非 `a` 字符的数量为 $m$。

如果 $t$ 中有 $k$ 个非 `a` 字符，把 $t$ 掐头去尾忽略前后的 `a` 后，原串里一定恰好存在 $\dfrac{m}{k}$ 个 $t'$，且 $k\mid m$。

枚举 $k$。记录第 $i$ 个非 `a` 字符的位置为 $p_i$（从 $0$ 开始），如果 $s_{p_i} \ne s_{p_i - k}$ 或不在分割处的 $p_i - p_{i - 1}\ne p_{i - k} - p_{i - k - 1}$，$t'$ 不合法。

把 $t'$ 还原为 $t$，枚举左边有的 `a` 个数 $l \in [0, p_0]$。

设 $x$ 为分割处的最小间隔 $\min(p_i - p_{i - 1}),\ k \mid i$，则右边的 `a` 个数 $r \in [0, \min(x - l, n - p_{m - 1} - 1)]$。

```cpp
void solve() {
	string s;
	cin >> s;
	int n = s.length();
	if(count(s.begin(), s.end(), 'a') == n) {
		cout << n - 1 << '\n';
		return;
	}	
	vector<int> a;
	for(int i = 0; i < n; ++ i) {
		if(s[i] != 'a') {
			a.eb(i);
		}
	}
	int m = a.size();
	ll ans = 0;
	for(int i = 1; i <= m; ++ i) {
		if(m % i) {
			continue;
		}
		int ok = 1;
		for(int j = i; j < m; ++ j) {
			int o = j % i;
			if(s[a[j]] != s[a[o]] || (o && a[o] - a[o - 1] != a[j] - a[j - 1])) {
				ok = 0;
				break;
			}
		}
		if(ok) {
			int mi = n;
			for(int j = i; j < m; j += i) {
				mi = min(mi, a[j] - a[j - 1] - 1);
			}
			int r = n - a.back() - 1;
			for(int l = 0; l <= a[0]; ++ l) {
				ans += max(0, min(r + 1, mi - l + 1));
			}
		}
	}
	cout << ans << '\n';
}
```

---

## 作者：naroto2022 (赞：3)

# CF1984D 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/CF1984D)

### 题意

（翻译没给得很清楚，一开始我还差点错了。）

给定一个字符串 $s$，求有多少个子串 $t$ 满足：

1. $t\neq$ `a`。
2. $s$ 可以由若干个 $t$ 和若干个 `a` 组成。
3. 组成 $s$ 的方法至少要有一个 $t$。

数据范围：$2\leqslant|s|\leqslant2\times10^5$

### 思路

观察题目可以敏锐的感觉到 `a` 是本题中的关键。

首先先考虑特殊情况，全是 `a` 的情况，这时候由于题目有给 $t\neq$ `a`，所以答案就为 $|s|-1$，$t$ 可以是除了 `a` 以外的所有字符串。

接下来加入非 `a` 字符。由于 $s$ 是要可以由若干个 $t$ 和若干个 `a` 组成，且至少要有一个 $t$，那么就影响到 $t$ 要包含所有的非 `a` 字符，且包含得都得一样。

考虑可以记录每一个非 `a` 字母再远字符串中的位置，这样就可以根据相邻两个非 `a` 字母的位置的差值知道 `a` 的分布情况，在此基础上，我们还可以把非 `a` 字母提取出来作为 $c$，长度为 $cnt$。

拿着有什么用呢？观察发现，对于每一种有 $k$ 个非 `a` 字符的子串 $t$，由于若干个 $t$ 和 `a` 拼凑可以拼成 $s$，所以 $t$ 里得有等量的非 `a` 字符，并且每个非 `a` 字符出现的相对位置一样，即要是不考虑 $t$ 中的 `a`，则 $k\vert cnt$，于是就可以考虑暴力在 $c$ 中判断 $cnt$ 的因数长度的是否可以形成循环节（包括判断其中的 `a`），然后可以的话累加答案即可。

时间复杂度 $O(n\sqrt n)$，可以过。

### 实现方法

上面思路是讲完了，相信一些高手已经自己尝试做了，接下来就让我讲下我当时想到上面方法后的解法。

首先先不看一个子串前面的 `a` 和后面的 `a`，将 $c$ 提取出来后直接开始枚举 $cnt$ 的每一个因数。

对于每一个因数，需要判断 $c$ 能否分成 $\frac{cnt}{i}$ 个长度为 $i$ 的相同的子串（要考虑上中间插这的原串的 `a`），其实这不难，只要一个个枚举 $c$ 中的每个子串，再判断每个相邻的子串中的字符，以及子串中每个字符间 `a` 的个数是否相同即可，至于 `a` 的个数，只要两个非 `a` 字符的位置相减再减一就可以得到，而每个非 `a` 的字符也处理好了，所以这很轻松就可以判断，时间复杂度为 $O(\frac{cnt}{i}\times i)=O(cnt)$，这是加上枚举因数的 $O(\sqrt n)$ 是可以接受的。

接下来就是统计答案，这就要考虑上每个提取出来的串前面的和后面的 `a` 了，首先我们知道对于没有前后的 `a` 两个子串之间的 `a` 是共用的（就是要想在前后各加一个 `a`，则至少每个子串之间要有 $2$ 个 `a`），所以我们只要找出子串之间最少的 $a$ 的个数，统计答案即可，具体以可以根据代码理解，代码中我枚举了后一个子串前面可以带上 `a` 的个数，再加上对应情况前一个子串后面可以带上 `a` 的个数的种数，注意要考虑可以不带 `a`。

于是就写好了，具体看代码吧！

### 代码

[提交记录](https://codeforces.com/problemset/submission/1984/273994574)


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
const int MN=200005;
ll T,len,cnt,p[MN],ans,b,e,minn;
//len是s的长度，cnt是非a字符的个数，b是第一个非a字符前面的a的个数，e是最后一个非a字符后面的个数，p是统计每个非a字符在原串中的位置 
char s[MN],c[MN];
bool flag,ok;
void write(ll n){if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
void work(ll k){
	ok=false;minn=2e5;//初始化，由于len<=2e5，所以初始时直接设为2e5 
	for(ll i=2*k; i<=cnt; i+=k) if(!ok) for(int j=i-2*k+1; j<=i-k; j++) if(c[j]!=c[j+k]||(j!=i-2*k+1&&p[j]-p[j-1]!=p[j+k]-p[j+k-1]/*要考虑出第一个以外每个字符中间a的个数是否相同*/)){ok=true;break;}//判断当前长度的子串是否是一个循环节，即每个子串出现的相对顺序是否一样 
	if(!ok){
		b=p[1]-1;e=len-p[cnt];
		for(ll i=k+1; i<=cnt; i+=k) minn=min(minn,p[i]-p[i-1]-1);//统计各个子串中中间包含的a最少的个数 
		if(b+e<=minn) ans+=(b+1)*(e+1);//直接乘法原理，记得有不带a的情况 
		else for(ll i=0; i<=min(b,minn); i++/*枚举后一个字符串前面可以占几个a*/) ans+=min(minn-i,e)+1;//要加上空（不带前面的或者后面的a）的情况 
	} 
}
int main(){
	T=read();while(T--){
		flag=false;cnt=0;ans=0;//初始化 
		scanf("%s",s+1);len=strlen(s+1);
		for(ll i=1; i<=len; i++) if(s[i]!='a') flag=true,p[++cnt]=i,c[cnt]=s[i];
		if(!flag){write(len-1);putchar('\n');continue;}//特判，全是a 
		for(ll i=1; i*i<=cnt; i++) if(cnt%i==0&&i*i!=cnt) work(i),work(cnt/i);else if(i*i==cnt) work(i);//只要枚举因子即可，注意要特殊处理平方根。 
		write(ans);putchar('\n');//记得换行 
	}
	return 0;
} 
```

---

## 作者：喵仔牛奶 (赞：3)

怎么没有单 $\log$ 做法。

# Solution

先特判 $s$ 全为 `a` 的情况。去除 $s$ 的前缀 `a`，则合法的 $t$ 去除 `a` 后必为 $s$ 的前缀，因为若不是则有无法匹配的前缀。

跑出 Z 函数 $z_i$、以 $i$ 开头的连续 `a` 个数 $p_i$。枚举 $\lvert t\rvert$（即 $t$ 的长度），每次跳过连续的 `a` 之后向后跳，若 $z_i\neq\lvert t\rvert$ 则不合法（具体见下文代码）。

但是 $t$ 可能有前缀 `a`，只要在枚举过程中连续的 `a` 的最小长度的即可。

```cpp
DEP(i, n, 1) p[i] = (t[i] == 'a' ? p[i + 1] + 1 : 0); // 跑出连续 a 个数
LL rs = 0;
REP(i, 1, n) { // i=|t|，即 t 的长度
	int x = i + 1, mn = ct, chk = 1; // x 是当前匹配位置，mn 是最小前缀 a，chk 是是否合法
  // ct 是 s 的前缀 a 个数
	while (x <= n) {
		int y = x + p[x]; // 跳过连续的 a
		if (y > n) break; // 跳完了，退出
		if (z[y] < i) { chk = 0; break; } // z[y]!=|t|，说明不能匹配，不合法
		mn = min(mn, p[x]), x = y + i; // mn 对 p[x] 取 min，x 跳到下一个位置
	}
	if (chk) rs += mn + 1;
}
```

复杂度是调和级数，$\mathcal{O}(\lvert s\rvert\log\lvert s\rvert)$。

# Code

完整代码如下：
```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5;
	void EXKMP(auto s, int n, int* z) {
    	z[1] = n;
		for (int i = 2, l = 0, r = 0; i <= n; i ++) {
    		z[i] = (i <= r ? min(r - i + 1, z[i - l + 1]) : 0);
			while (s[z[i] + 1] == s[i + z[i]]) z[i] ++;
			if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
		}
	}
	string s, t; int n, ct, p[N], z[N];
	int main() {
		cin >> s, t = "#", ct = 0;
		while (ct < s.size() && s[ct] == 'a') ct ++;
		REP(i, ct, (int)s.size() - 1) t += s[i];
		n = t.size() - 1, EXKMP(t, n, z);
		if (!n) {
			cout << s.size() - 1 << '\n';
			return 0;
		}
		DEP(i, n, 1) p[i] = (t[i] == 'a' ? p[i + 1] + 1 : 0);
		LL rs = 0;
		REP(i, 1, n) {
			int x = i + 1, mn = ct, chk = 1;
			while (x <= n) {
				int y = x + p[x];
				if (y > n) break;
				if (z[y] < i) { chk = 0; break; }
				mn = min(mn, p[x]), x = y + i;
			}
			if (chk) rs += mn + 1;
		}
		cout << rs << '\n';
		return 0;
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1; cin >> T;
	while (T --) Milkcat::main();
	return 0;
}
```

---

## 作者：MrPython (赞：3)

少转一个 int128 痛失一题 ![/fn](https://t.tutu.to/img/v1Fyg)

Hint 1. 如果确定了一个正整数 $n$ 和一个从 $\texttt{b}$ 到 $\texttt{z}$ 的字符 $c$，最多有多少个符合题目要求的 $s$ 的子串 $t$ 满足 $|t|=n$ 且 $t_0=c$？

显然只有一种。假设有两个，那一个肯定会与另一个失配。这启示我们，可以按照首字母分类，对于每个 $\texttt{b}$ 到 $\texttt{z}$ 的首字母每种长度仅尝试匹配第一个即可。

---

Hint 2. 要检查一个串 $t$，可以使用哈希 $O(1)$ 地判断两个子串是否相等。那么我们最多需要匹配多少次？

我采用的做法是，维护出每个字母在串中出现的位置。假设某字符在串中第一次出现在下标 $i$，使用哈希检查 $S_{i:i+|t|}$ 与 $t$ 是否相等，若失配直接跳出，否则只需要继续检查下标 $i+|t|$ 后面的内容就好了，二分维护（注意，此处使用类似 Python 切片的语法表示的子串）。除了维护子串是否相等，也别忘了顺手判一下两个串之间的区域是否只有字母 $\texttt{a}$。

对于子串 $t$，我们最多仅需匹配 $\dfrac{|s|}{|t|}$ 次，带上二分的复杂度为 $O(\dfrac{|s|}{|t|}\log|s|)$。从 $1$ 到 $|s|$ 枚举 $|t|$，总复杂度为 $O(|s|\log^2|s|)$。

---

Hint 3. 前面我们仅处理了开头为 $\texttt{b}$ 到 $\texttt{z}$ 的串。对于 $\texttt{a}$ 打头的该怎么处理？

特殊处理全部为 $\texttt{a}$ 的子串。剩余情况下，任何一个符合要求的、以 $\texttt{a}$ 打头的子串都可以看成“若干个 $\texttt{a}$”与“以其他字母打头的合法子串”直接拼接而成。检查某个串时，顺手记录一下位置信息，最终前面可以包含的 $\texttt{a}$ 字符数量，就是 $\min(\texttt{两个串的最小间隔},\texttt{第一个串的位置})+1$。

---
~~我这是不是重工业做法~~
<https://codeforces.com/contest/1984/submission/265866366>

---

## 作者：M1saka16I72 (赞：1)

## 前言

[更可爱的阅读体验](https://misaka16172.github.io/solution-CF1984D.html)

感觉这个题跟 [P7114 [NOIP2020] 字符串匹配](https://www.luogu.com.cn/problem/P7114) 莫名有点联系啊，我如果没写过那题是肯定不会做这个题的。

## 思路

一开始先特判掉全 $\text a$ 串，显然此时答案为长度 $-1$，以下讨论全部默认给定的串不是全 $\text a$ 串。

性质 1：一个全 $\text a$ 串一定不能成为答案，证明显然。

性质 2：一个合法的答案串一定是原串的一段前缀删去前缀的若干个 $\text a$。

证明：设原串 $s$ 中第一个非 $\text a$ 的位置为 $p$，一个不满足该性质的 $s$ 的子串 $t=s_ls_{l+1}\cdots s_r$（不妨设 $l$ 为 $t$ 第一次出现的左端点），则条件等价于 $p<l$。如果 $[1,l)$ 能被合法划分，由于 $s_p≠$ $\text a$，这段字符串中必然有一段 $[l',r']=t\ (1\leq l'\leq p\leq r'<l)$，否则第 $p$ 个字符将无法被划分进任何一个子串。

性质 3：如果 $[l,r](l<p)$ 是合法的答案串，则 $[l+1,r]$ 同样是。

证明：因为 $l<p$，$s_l$ 必定为 $\text a$。于是将每个等于 $[l,r]$ 的子串开头单分出来一个 $\text a$ 就能形成一种合法的划分。

有了这些性质，我们很容易想到做法：枚举每个前缀 $[1,i]$，先验证 $[p,i]$ 这个开头没有 $\text a$ 的串是否合法，若合法则求出最多能往串左边塞几个 $\text a$。

实现上，先预处理出整串的哈希和每个下标 $i$ 右边第一个非 $\text a$ 下标 $nxt_i$，验证一个长度为 $len$ 的串时，直接用哈希查询然后每次往右跳 $len$ 个字符，若当前字符 $s_i$ 为 $\text a$ 则直接跳到 $nxt_i$ 即可。同时记录上一次查询的右端点，把每次跳到的左端点和上一个右端点之间 $\text a$ 的个数取 $\min$，即为最多能往左塞的 $\text a$ 的个数。由于每次保底跳 $len$ 个字符，时间复杂度为调和级数约 $\mathcal{O}(n\ln n)$。

记得多搞几个哈希模数，实测使用 $10^9+7,998244353$ 两个模数都会被卡。

## 代码

```cpp
constexpr int N = 2e5+5;
constexpr uint mod[3] = {1e9+7,998244353,19260817};

string s;
int n,nxt[N];
uint hs[N][3],b[N][3];

inline uint gethash(int l,int r,int m){return ((ll)hs[r][m]-(1ll*hs[l-1][m]*b[r-l+1][m]%mod[m])+mod[m])%mod[m];}

void init(){
	n = s.length();
	for(int j=0;j<=2;j++){
		for(int i=1;i<=n;i++)	hs[i][j] = (1ull*hs[i-1][j]*26+s[i-1])%mod[j];
	}
}

int check(int l,int r){
    int mn = inf;
	for(int m=0;m<=2;m++){
		uint h = gethash(l,r,m);
		int len = (r-l+1);
        int lst = r;
		for(int i=r+1;i<=n;i+=len){
            if(s[i-1]=='a'){i = nxt[i]-len;continue;}
            mn = min(mn,i-lst-1);
            lst = i+len-1;
			uint nh = gethash(i,min(i+len-1,n),m);
			if(nh!=h)	return -1;
		}
	}
	return mn;
}

void solve(){
    cin>>s;
    int cnta = 0;
    for(char c:s)	cnta+=(c=='a');
    if(cnta==s.length()){cout<<s.length()-1<<"\n";return;}
    init();
    stack<int> st;
    for(int i=1;i<=n;i++){
    	nxt[i] = n+1;
    	if(s[i-1]=='a')	st.push(i);
    	else{
    		while(!st.empty()){
	    		nxt[st.top()] = i;
	    		st.pop();
	    	}
    	}
    }
    int p = 1;
    while(s[p-1]=='a')	++p;
    ll ans = 0;
    for(int i=p;i<=n;i++)   ans+=min(check(p,i)+1,p);
    cout<<ans<<"\n";
}

void _init(){
	for(int j=0;j<=2;j++){
		b[0][j] = 1;
		for(int i=1;i<N;i++)	b[i][j] = 1ull*b[i-1][j]*26%mod[j];
	}
}
```

---

## 作者：wangyibo201026 (赞：1)

## solution

标签啥玩意，这题根本不需要哈希。

还有为啥有个 $\log$ 做法，感觉弱弱的不会。

首先，假设串长为 $n$，且 $s$ 中全为 $a$，那么答案为 $n - 1$，先特判掉。

然后我们把所有非 $a$ 字符位置从小到大拿出来，然后我们发现最后串 $t$ 的基本结构应该是以非 $a$ 字符开头，并以非 $a$ 字符结尾，并且中间所组成的字符串完全一样（这一步不需要哈希，总长度为 $n$，直接比较）。

这样，你枚举一个 $t$ 所包含的非 $a$ 字符数量 $len$，然后在所有非 $a$ 字符中，相当于每 $len$ 个非 $a$ 字符就组成一个串（包含中间的 $a$），我们算一下相不相同，如果相同我们就可以开始计数了。

至于计数的过程，我们就枚举向左拓展的个数，然后容易预处理后在 $O(1)$ 时间能求出最多能向右拓展的个数，然后加上答案即可（没有乘是因为会重）。

总时间复杂度 $O(n d(n))$，$d(n)$ 为 $n$ 的因子数，远远低于 $\sqrt n$。

## code

code（代码算好写的了）：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair < int, int > pii;

char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 3e5 + 5;

int t, n, ans;
string s;
vector < int > pos;

string query ( int l, int r ) {
	return s.substr ( l, r - l + 1 );
}

int calc ( int len ) {
	int res = 0;
	string tmp = query ( pos[0], pos[len - 1] );
	for ( int i = len; i < pos.size (); i += len ) {
		if ( query ( pos[i], pos[i + len - 1] ) != tmp ) {
			return 0;
		}
	}
	if ( len == pos.size () ) {
		res += pos.front () * ( n - pos.back () + 1 );
	}
	else {
		int r = 1e9 + 7;
		for ( int i = len; i < pos.size (); i += len ) {
			r = min ( r, pos[i] - pos[i - 1] - 1 );
		}
		for ( int l = 0; l <= min ( r, pos.front () - 1 ); l ++ ) {
			res += min ( r - l, n - pos.back () ) + 1;
		}
	}
	return res;
}

bool check () {
	for ( int i = 1; i <= n; i ++ ) {
		if ( s[i] != 'a' ) {
			return false;
		}
	}
	return true;
}

void Solve () {
	ios :: sync_with_stdio ( false );
	cin.tie ( 0 ), cout.tie ( 0 );
	cin >> t;
	while ( t -- ) {
		pos.clear ();
		ans = 0;
		cin >> s;
		n = s.size ();
		s = " " + s;
		if ( check () ) {
			cout << n - 1 << '\n';
			continue;
		}
		for ( int i = 1; i <= n; i ++ ) {
			if ( s[i] != 'a' ) {
				pos.push_back ( i );
			}
		}
		for ( int i = 1; i <= pos.size (); i ++ ) {
			if ( pos.size () % i == 0 ) {
				ans += calc ( i );
			}
		}
		cout << ans << '\n';
	}
}

signed main () {
#ifdef judge
	freopen ( "Code.in", "r", stdin );
	freopen ( "Code.out", "w", stdout );
	freopen ( "Code.err", "w", stderr );
#endif
	Solve ();
	return 0;
}
```

---

## 作者：SFlyer (赞：1)

考虑如果 $s$ 全部是 `a`，那么直接输出长度减一。否则令第一个出现但是不是 `a` 的数为 $c$，它的出现次数为 $cnt$。那么我们要求的 $t$ 中 $c$ 的个数一定是 $cnt$ 的因数。考虑确定了这个个数 $i$。

我么可以求出每一个 $t$ 的大致位置是至少从哪儿到哪儿，划分完以后必须都一样。划分完以后，中间会有若干个 `a`，令中间的 `a` 的个数最小为 $mn$。现在我们要枚举的就是 $t$ 向左延申的 `a` 的个数 $l$，和向右的 $r$。$l,r$ 本生就有限制（最左边和右边 `a` 的个数），并且 $l+r\le mn$，这个世界枚举其中一个计算即可。

一些要注意的：

- $t$ 必须包含的那些 `a` 是必须完全相同的，因为 $t$ 是连续的。

- 切分的时候要注意中间必须全部是 `a`，这个只能从后面的那个往前面伸，遇到不是 `a` 的停止。不能从前往后。

时间复杂度 $\mathcal{O}(n\cdot d(n))$。

代码不放了，太丑。

---

