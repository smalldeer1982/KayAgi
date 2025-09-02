# Collapsing Strings

## 题目描述

You are given $ n $ strings $ s_1, s_2, \dots, s_n $ , consisting of lowercase Latin letters. Let $ |x| $ be the length of string $ x $ .

Let a collapse $ C(a, b) $ of two strings $ a $ and $ b $ be the following operation:

- if $ a $ is empty, $ C(a, b) = b $ ;
- if $ b $ is empty, $ C(a, b) = a $ ;
- if the last letter of $ a $ is equal to the first letter of $ b $ , then $ C(a, b) = C(a_{1,|a|-1}, b_{2,|b|}) $ , where $ s_{l,r} $ is the substring of $ s $ from the $ l $ -th letter to the $ r $ -th one;
- otherwise, $ C(a, b) = a + b $ , i. e. the concatenation of two strings.

Calculate $ \sum\limits_{i=1}^n \sum\limits_{j=1}^n |C(s_i, s_j)| $ .

## 样例 #1

### 输入

```
3
aba
ab
ba```

### 输出

```
20```

## 样例 #2

### 输入

```
5
abab
babx
xab
xba
bab```

### 输出

```
126```

# 题解

## 作者：__Floze3__ (赞：5)

## 思路

通过观察，我们不难得到，这个 $C$ 函数的值，即为两个字符串的长度之和，减去第一个字符串的后缀与第二个字符串的前缀最长重合部分的长度（注意 $C$ 是个递归函数）。  
那么不难想到，我们可以用一个 Trie 来存贮每个字符串，并且用一个 $cnt$ 数组来存储每个节点被经过的次数。操作完成之后，我们可以将每一个字符串翻转之后在这个 Trie 中查询，那么这个字符串的长度乘以 $2$，再减去经过节点的 $cnt$ 之和，就是这个字符串作为第一个字符串的 $C$ 函数值之和。

## 代码

```cpp
#include <bits/stdc++.h>
#define PII pair<int, int>
#define PLL pair<ll, ll>
#define lowbit(x) x & (-x)
#define fs(x) fixed << setprecision(x)
using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
#define int long long

const int maxn = 1e6 + 5;

int n, trie[maxn][26], cnt[maxn], idx, sum;
vector<string> word;

inline void insert(string w){
    int p = 0, len = w.length();
    for (int i = 0; i < len; i++){
        int c = w[i] - 'a';
        if (!trie[p][c])
            trie[p][c] = ++idx;
        p = trie[p][c];
        ++cnt[p];
    }
    return ;
}

inline int query(string w){
    int p = 0, len = w.length(), res = sum + len * n;
    for (int i = len - 1; i >= 0; i--){
        int c = w[i] - 'a';
        if (!trie[p][c])
            return res;
        p = trie[p][c];
        res -= 2 * cnt[p];
    }
    return res;
}

signed main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        string a;
        cin >> a;
        word.push_back(a);
        sum += a.length();
        insert(a);
    }
    int ans = 0;
    for (int i = 0; i < n; i++){
        ans += query(word[i]);
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：under_the_time (赞：4)

## 题意

> 给定 $n$ 个由小写字符组成的字符串 $S$。对于两个字符串 $s,t$，定义 $C(s,t)=|s|+|t|-X(s,t)\times 2$，其中 $X(s,t)$ 为最大的 $x$ 使得 $s_{|s|-x+1,x}=t_{1,x}$。求 
> $$
> \sum^{i=1}_{n}\sum^{j=1}_{n}|C(S_i,S_j)|
> $$
> 的值。

## 思路

我们将 $C$ 这个递归函数转化成了上述的形式。其中 $X(s,t)$ 的本质为：对 $s$ 进行反转后 $|\operatorname{lcp}(s,t)|$。对于第 $i$ 个串，其对答案的贡献即为
$$
\begin{aligned}\sum^n_{j=1}|C(S_j,S_i)|&=\sum^n_{j=1}(|S_j|+|S_i|-2\times X(S_j,S_i))\\&=\bigg(n|S_i|+\sum^n_{j=1}|S_j|\bigg)-2\times\bigg(\sum^n_{j=1}X(S_j,S_i)\bigg)\end{aligned}
$$
而求出 $\sum^n_{j=1}X(S_j,S_i)$，我们将 $S$ 中的每个字符串反转后插到 Trie 树上，记录每个结点的经过次数 $tot$；然后拿着 $S_i$ 到 Trie 树上查询，答案为经过的结点 $tot$ 之和。复杂度 $O(\sum^n_{i=1} |S_i|)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 1e6 + 5;
vector<string> S; ll n;
ll ans, sum;
int tr[maxn][30]; ll tot[maxn], cnt = 1;
void insert(string s) {
    int len = s.size(), now = 1;
    for (int i = len - 1;i >= 0;i --) { // 反串
        if (!tr[now][s[i] - 'a'])  
            tr[now][s[i] - 'a'] = ++ cnt;
        now = tr[now][s[i] - 'a'], tot[now] ++;
    }
}
ll query(string s) {
    int len = s.size(), now = 1; ll res = 0;
    for (int i = 0;i < len;i ++) {
        if (!tr[now][s[i] - 'a'])
            return res;
        now = tr[now][s[i] - 'a'], res += tot[now];
    }
    return res;
}
string c;
int main() {
    cin >> n;
    for (int i = 1;i <= n;i ++) {
        cin >> c; sum += c.size();
        S.push_back(c);
        insert(c);
    }
    for (int i = 0;i < n;i ++) {
        ans += S[i].size() * n + sum - query(S[i]) * 2ll;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：wxzzzz (赞：4)

### 题意

给定 $n$ 个字符串 $s_1,s_2,s_3...s_n$，求 $\displaystyle\sum_{i=1}^n\sum_{j=1}^n |C(s_i,s_j)|$。

定义 $C(a,b)=\begin{cases}a\ (b=\varnothing)\\
b\ (a=\varnothing)\\
C(a_{[1,|a|-1]},b_{[2,|b|]})\ (otherwise)\end{cases}$

### 思路

$C(a,b)$ 相当于 $|a|+|b|-x\times 2$。

其中，$x$ 表示最大的 $a_{|a|-i+1}=b_i\ (i\in[1,x])$。

记 $cnt(k)$ 所有 $n$ 个字符串中，有多少个 $s_i$ 出现了为 $k$ 的前缀。

$s_i$ 对答案的贡献为 $|s_i|\times n-\displaystyle\sum_{j=1}^{|s|}cnt(s[|s_i|,1])\times 2$。

判断两段字符是否相同可以用哈希。

最后注意，这题卡自然溢出，要自定义模数。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, m, ans;
unsigned long long hs, mod = 1000000000000000007;
string s[1000005];
map<unsigned long long, long long> cnt;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        hs = 0;

        for (int j = 0; j < s[i].length(); j++) {
            hs = ((hs * 131) % mod + s[i][j]) % mod;
            cnt[hs]++;
        }

        ans += s[i].length() * n * 2;
    }

    for (int i = 1; i <= n; i++) {
        hs = 0;

        for (int j = s[i].length() - 1; j >= 0; j--) {
            hs = ((hs * 131) % mod + s[i][j]) % mod;
            ans -= cnt[hs] * 2;
        }
    }

    cout << ans;
    return 0;
}
```

---

## 作者：Iniaugoty (赞：4)

简单题，建议评黄或绿。

这个 $C$ 函数，显然就是，两串长度之和，再减去二倍的，前一个字符串倒序之后，与后一个串的最长公共前缀。

考率枚举第一个字符串，将其倒序，那么需要一个数据结构，在 $\mathcal O (\vert s \vert)$ 的时间内维护每一个串和它的最长公共前缀。Trie 很适合这种事情。具体地，对于树上每个结点，记录有多少个字符串经过它，设为 $cnt$。对某个深度为 $dep$ 的结点，将它的 $cnt$ 与一个子结点的 $cnt$ 做差，就是最长公共前缀为 $dep$ 的字符串个数。那么答案很容易搞。

时间复杂度 $\mathcal O (\sum \vert s _ i \vert)$，空间复杂度在此基础上乘一个字符集大小。

代码很简单，反正我是 10min 写完就过了。~~比 B 和 C 还快。~~

~~然后被 FST 了。~~

注意要多开 `long long`。

```cpp
#include <bits/stdc++.h>

#define F(i, a, b) for(int i = (a); i <= (b); ++i)
#define dF(i, a, b) for(int i = (a); i >= (b); --i)

using namespace std;
typedef long long LL;
typedef unsigned long long ull;
const int N = 1e6 + 5;

int n; LL sum, ans;
string s[N];

int tot;
struct Trie { int s[26]; LL cnt; } t[N * 2];
void Insert(string s) {
	int u = 0;
	for (auto ch : s) {
		++t[u].cnt;
		if (!t[u].s[ch - 'a'])
			t[u].s[ch - 'a'] = ++tot;
		u = t[u].s[ch - 'a'];
	}
	++t[u].cnt;
	return ;
}
LL Query(string s) {
	LL res = sum + n * (LL) s.size(), len = 0, u = 0;
	for (auto ch : s) {
		if (!t[u].s[ch - 'a'])
			t[u].s[ch - 'a'] = ++tot;
		LL cnt = t[u].cnt - t[t[u].s[ch - 'a']].cnt;
		res -= cnt * len * 2;
		u = t[u].s[ch - 'a'];
		++len;
	}
	res -= t[u].cnt * len * 2;
	return res;
}

int main() {
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	F(i, 1, n) cin >> s[i], sum += (LL) s[i].size(), Insert(s[i]);
	F(i, 1, n)
		reverse(s[i].begin(), s[i].end()),
		ans += Query(s[i]);
	cout << ans << "\n";
	return 0;
}
```

---

## 作者：SXqwq (赞：3)

### Description

题面描述已经非常清晰，不再赘述。

### Analysis

记 $a^R$ 为 $a$ 的反串，$\text{lcp}$ 为最长公共前缀。

显然 $|C(a,b)|=|a|+|b|-2|\text{lcp}(a^R,b)|$。

我们将反串 $s_1^R,s_2^R\dots s_n^R$ 插入字典树。考虑每个正串 $s_i$ 对答案的贡献。

$$\sum\limits_{j=1}^n|C(s_j,s_i)|=\sum\limits_{j=1}^n(|s_j|+|s_i|-2(|\text{lcp}(s_j^R,s_i)|)$$

$$=(n|s_i|+\sum\limits_{j=1}^n|s_j|)-2(\sum\limits_{j=1}^n|\text{lcp}(s_j^R,s_i)|)$$

我们考虑如何计算 $\sum\limits_{j=1}^n|\text{lcp}(s_j^R,s_i)|$。 

对反串的字典树与处理各节点子树内有多少个反串的终止位置。即有多少个反串以根到该节点表示的串为前缀，记作 $f$。

$\sum\limits_{j=1}^n|\text{lcp}(s_j^R,s_i)|$ 即为以 $s_i$ 从左到右字符顺序依次从根往下走，途径的所有非根节点的 $f$ 总和。

时间复杂度 $O(\sum |s_i|)$。

---

## 作者：FFTotoro (赞：2)

字典树板子题。

正难则反，考虑所有字符串对的长度和之和减去重叠部分长度之和得到答案。

重叠部分的长度只需将所有字符串正着插入字典树中，令每个结点的权值为经过的次数。

查询时反着询问经过所有结点的权值和即可。

因为空间限制 $256\mathrm{MiB}$，所以开 $2.6\times 10^7$ 的 `int` 数组不会爆。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t[1000001][26],w[1000001],o;
void insert(string s){
  int p=0;
  for(char i:s)
    if(!t[p][i-97])w[p=t[p][i-97]=++o]=1;
    else w[p=t[p][i-97]]++;
} // 插入
int f(string s){
  int p=0; long long c=0;
  for(char i:s)
    if(!t[p][i-97])break;
    else c+=w[p=t[p][i-97]];
  return c;
} // 查询
int main(){
  ios::sync_with_stdio(false);
  int n; long long l=0,c=0; cin>>n;
  vector<string> a(n);
  for(auto &i:a)cin>>i,l+=i.length(),insert(i);
  for(auto &i:a)reverse(i.begin(),i.end()),c+=f(i);
  cout<<(l*n-c<<1)<<endl; // 答案
  return 0;
}
```

---

## 作者：bluewindde (赞：1)

由题意：$C(a,b)=|a|+|b|-|c|$，$c$ 串表示 $a$ 串的后缀和 $b$ 串的前缀的最长公共部分。

设 $d_x$ 表示有多少个串 $s_i$ 出现了为 $x$ 的前缀，用 Trie 树容易维护 $d$。

用容斥的思想，先算出没有公共前后缀的长度，再减去公共前后缀的长度，即为答案。

代码

```cpp
#include <iostream>
#include <string>

#define int long long

using namespace std;

int n;
string s[1000005];

struct trie {
    int son[26];
    int val;
} d[1000005];
int cnt = 0;
static inline void insert(const string &s) { // Trie 树模板
    int p = 0;
    for (auto ch : s) {
        if (!d[p].son[ch - 'a']) {
            d[p].son[ch - 'a'] = ++cnt;
        }
        p = d[p].son[ch - 'a'];
        ++d[p].val;
    }
}
static inline int query(const string &s) {
    int p = 0;
    int ret = 0;
    for (int i = s.size() - 1; i >= 0; --i) {
        char ch = s[i];
        if (!d[p].son[ch - 'a']) {
            break;
        }
        p = d[p].son[ch - 'a'];
        ret += d[p].val;
    }
    return ret * 2;
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("CF1902E.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        insert(s[i]);
        ans += (s[i].size() * n) << 1; // 假设没有重复的前后缀
    }
    for (int i = 1; i <= n; ++i) {
        ans -= query(s[i]); // 容斥 减掉重复答案
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Melo_DDD (赞：0)

~~得玉玉症后的第一篇题解。~~

首先发现瓶颈在于枚举字符串，如果选择 $\Theta(n^2)$ 枚举的话，你需要一个 $\Theta(10^{-3})$ 级别的算法。

这显然是不科学的，发现好像没有 $n\log n$ 级别的枚举方法，于是直接往线性想。那肯定就是枚举每一个串，然后快速算出这一个串和其他（包括它自己）的答案。

看题中给出的函数，发现 $C(a,b)$ 其实就是把 $a$ 的后缀和 $b$ 的前缀中最长的相同部分删了，再把他俩接到了一起，设相同部分长度为 $len$，那他俩的贡献就是 $|a|+|b|-2\times len$。

那么对于一个 $s_i$，我们只需要求出 $\displaystyle\sum_{j=1}^{n}|C(s_i,s_j)|$ 即可，设为 $len$。那么 $s_i$ 的贡献就是 $n\times |s_i|+sum-2\times len$，其中 $sum=\displaystyle\sum_{i=1}^{n}|s_i|$。

这个时候可以想到 trie 了，首先把所有串插进去，然后我们发现 trie 搞前缀是方便的，但是后缀不行啊。解决办法比较简单，对于当前枚举的串，把它反过来，找最长的公共前缀就可以了。

如何在遍历一遍 trie 的时候求得所说的 $len$？考虑对于树上的每个节点（除了根），打一个标记，每次到达将标记加 $1$，沿路统计标记和即可。

很好理解，假如一个串和当前串的最长公共前缀长度是 $len$，那么在遍历 trie 的时候我们最开始经过的除了根的 $len$ 个点一定是被那个串经过的，后面的点则不然，由于每到一个点当前标记加一，那么那个串对答案的贡献自然就是 $len$，符合题意。

代码：


```cpp
#include <bits/stdc++.h>
#define f(i ,m ,n ,x) for (int i = (m) ; i <= (n) ; i += (x))
using std :: string ;

template < typename T > inline void read ( T &x ) {
	x = 0 ;
	bool flag (0) ; char ch = getchar () ;
	while (! isdigit (ch))
	{ flag = ch == '-' ; ch = getchar () ;}
	while (isdigit (ch))
	{ x = (x << 1) + (x << 3) + (ch ^ 48) ; ch = getchar () ;}
	flag ? x = - x : 0 ;
}

#define con const 
con int N = 1e6 + 7 ; using ll = long long ;
int n ,lon ; string s[N] ; ll ans ;

class trie {
private :
	int son[N][30] ,tot ; ll sum[N] ;
	inline int map (char ch) { return ch - 'a' ;}
public :
	inline void insert (string s) {
		int len = (int) s.length () ,cur = 0 ;
		lon += len ;
		f (i ,0 ,len - 1 ,1) {
			int ch = map (s[i]) ;
			if (! son[cur][ch]) son[cur][ch] = ++ tot ;
			sum[cur = son[cur][ch]] ++ ;
		}
	}
	inline ll query (string s) {
		int len = (int) s.length () ,cur = 0 ,ans = 0 ;
		f (i ,0 ,len - 1 ,1) {
			int ch = map (s[i]) ;
			if (! son[cur][ch]) return ans ;
			ans += sum[cur = son[cur][ch]] ;
		} return ans ;
	}
} tr ;

int main () {
	read (n) ; f (i ,1 ,n ,1) {
		std :: cin >> s[i] ;
		tr.insert (s[i]) ;
	}
	
	f (i ,1 ,n ,1) {
		ll len = (ll) s[i].length () ;
		std :: reverse (s[i].begin () ,s[i].end ()) ;
		ans += lon + (ll) n * len - (tr.query (s[i]) << 1ll) ;
	} std :: cout << ans << '\n' ;
	return 0 ;
}
```

---

## 作者：liuhl_weifang (赞：0)

## 题目链接

[link](https://www.luogu.com.cn/problem/CF1902E)

## 解题思路

令 $\text{rev}(x)$ 表示 $x$ 翻转后的字符串，$\text{LCP}(a,b)$ 表示 $a$ 与 $b$ 的最长公共前缀。则 $C(i,j)=(|s_i|+|s_j|)-2 \times \text{LCP}(s_i,\text{rev}(s_j))$。

显然这两部分可以单独计算，第一部分是平凡的，关键是第二部分，我们可以建一棵 `Trie` 来计算。

```cpp
#include <bits/stdc++.h>
#define int long long
#define FAST ios::sync_with_stdio(false);cin.tie(0)
using namespace std;
struct Node{
	int c[26];
	int cnt;
};
Node t[1000010];
int idx;
int n;
string s[1000010];

signed main()
{
	cin >> n;
	int ans = 0;
	for (int i=1;i<=n;i++){
		cin >> s[i];
		reverse(s[i].begin(),s[i].end());
		int now = 0;
		for (auto j : s[i]){
			if(t[now].c[j-'a']==0) t[now].c[j-'a'] = ++idx;
			now = t[now].c[j-'a'];
			++t[now].cnt;
		}
		reverse(s[i].begin(),s[i].end());
		ans += s[i].length();
	}
	ans = ans*2*n;//第一部分计算完成
	for (int i=1;i<=n;i++){
		int now = 0;
		for (auto j : s[i]){
			if(t[now].c[j-'a']==0) break;
			now = t[now].c[j-'a'];
			ans -= 2*t[now].cnt;
		}
	}
	cout << ans << "\n";
	return 0;
}
```

---

## 作者：UnfortunatelyDead (赞：0)

考虑 $a,b$ 满足 $C(a,b)=C(a_{1,|a|-1},b_{2,|b|})$ 的时候，$a,b$ 的最终形态是 $a$ 的末尾与 $b$ 开头是不同的，递归的次数即翻转后 $a$ 和 $b$ 的最长前缀长度，记为 $cnt$，那么 $|C(a,b)| = |a| + |b| - 2 \times cnt$。因为每次都是删除了 $a$ 的末尾字符和 $b$ 的开头字符。

由于  $n=10^6$ 的原因，那么暴力枚举 $n$ 显然是行不通的，但是我们如果枚举 $a$ 呢，思考一下，你能在一个不大的复杂度内求出 $\sum_{i=1}^n |C(a,s_i)|$ 吗？

因为 $C(a,b)$ 的特殊性，同一个 $a$ 其实是可以和不同的 $b$ 同时进行求最大前缀的，具体可以上一棵 Trie 树，树上记录和 $a$ 前缀为 $d$ 的数量有几个，那么让总量减去这么多的两倍即可，当 $a$ 倒序遍历完了之后其实再有 $|s_i| > |a|$ 的也没用了，因为再怎么相同答案也只剩下了 $|s_i| - |a|$。

于是 Trie 树预处理做到了 $O(n)$，可以通过。

注意 `long long ` 问题。

```cpp
const int N = 1e6 + 19;
int trie[N][27], cnt[N], len = 1;
void insert(string s) {
	int p = 1;
	for (auto i : s) {
		if (!trie[p][i - 'a']) trie[p][i - 'a'] = ++len;
		p = trie[p][i - 'a'];
		cnt[p]++;
	}
}
string s[N];
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	int n, tot = 0; cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> s[i];
		insert(s[i]);
		tot += s[i].size();
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans += tot + s[i].size() * n;
		int p = 1;
		for (int j = s[i].size() - 1; ~j; --j) {
			if (!trie[p][s[i][j] - 'a']) break;
			p = trie[p][s[i][j] - 'a'];
			ans -= cnt[p] * 2;
		}
	} write(ans, '\n');
	return 0;
}
```

---

## 作者：AnicoderAndy (赞：0)

[题目传送门](https://codeforces.com/contest/1902/problem/E)

## 分析

要求 $\sum_i^n\sum_j^n C(i,j)$，直接计算至少需要 $O(n^2)$ 的时间复杂度，所以考虑使用某种数据结构维护所有字符串的相关信息，使得遍历每个字符串都能计算它对答案的贡献。既然是 $n$ 个字符串，那么不妨使用 Trie 来维护。

对于每个字符串，不妨考虑它对答案的贡献取决于它的前缀和其他字符串后缀，故考虑建立一个由所有字符串的**逆序**串组成的 Trie。

对于 Trie 上的每个点，记录该点包含的字符串个数 $cnt$ 以及该点记录的所有字符串长度之和 $sz$。遍历每个字符串，用 Trie 尝试将所有逆序字符串与当前字符串的正序进行匹配，对于当前字符串的某一位，如果匹配到的字符串个数减少，也就说明存在某些字符串**不再能与当前字符串首尾抵消**，我们可以利用当前匹配到的位数、这些字符串的长度、当前字符串的长度计算当前字符串与它们产生的贡献。具体地，当前匹配的字符串长度为 $len$，匹配到第 $j$ 位时从 Trie 上的 $u$ 节点转移到 $v$ 节点，产生的贡献值为 

$$
(len - j) \times (cnt[u] - cnt[v]) + (sz[u] - sz[v]) - (cnt[u] - cnt[v]) \times j
$$

其中 $cnt[u] - cnt[v]$ 即为前文提到的“某些字符串”的个数，$sz[u] - sz[v]$ 即为“某些字符串”的总长度。时间复杂度 $O(\sum_i^n\lvert s_i\rvert)$。

## C++20 实现
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <ranges>
#include <string>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll read() {
    ll x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
// trie[i][x]记录了节点i转移至字母x对应的节点编号
int n, trie[N][26], tot = 1, cnt[N], sz[N];
string s[N];

void sol() {
    n = read();
    for (int i = 1; i <= n; i++) cin >> s[i];
    for (int i = 1; i <= n; i++) {
        int pos = 1, len = s[i].size();
        sz[1] += len, cnt[1]++;
        // 逆序遍历
        for (auto j : s[i] | views::reverse) {
            if (!trie[pos][j - 'a']) trie[pos][j - 'a'] = ++tot;
            pos = trie[pos][j - 'a'];
            cnt[pos]++;
            sz[pos] += len;
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        int from, to = 1;
        for (int j = 0; j < s[i].size(); j++) {
            from = to, to = trie[from][s[i][j] - 'a'];
            ans += 1ll * (cnt[from] - cnt[to]) * (s[i].size() - j * 2) + (sz[from] - sz[to]);
        }
        // 特别考虑匹配完当前字符串所有字符之后的情况
        ans += sz[to] - 1ll * cnt[to] * s[i].size();
    }
    printf("%lld\n", ans);
}

int main() {
    sol();
    return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

记 $s_1,s_2$ 的长度分别为 $a,b$，而 $s_1$ 末尾，$s_2$ 开头的重合部分长度为 $c$，那么 $C(s_1,s_2)=a+b-c$。

但是一个后缀和一个前缀不好维护，所以考虑把 $s_2$ 翻转，那么就是求 $s_2$ 翻转后得到的 $s_2'$ 和 $s_1$ 的公共前缀的长度，用 Trie 树容易解决。

考虑先把每一个字符串 $s$ 翻转之后放到 Trie 树里。

考虑找到 $s_1$，求所有 $s_2$ 之和。

用 Trie 树容易维护前缀的长度总和，记为 $res$，那么总共的贡献就是 $n\times|s_1|+(L-res\times2)$，其中 $L$ 是所有字符串的总长度。

首先，$res$ 是公共的部分，$L-res$ 就是 $s_2$ 合并的时候的总长度，对于每一个字符串，都有一个 $res_i$，$res=\sum res_i$，那么一个字符串，$s_1$ 合并的时候长度为 $|s_1|-res_i$，总共有 $n$ 个，就是 $n\times|s_1|-res$。

所以 $s_1$ 贡献就是 $n\times|s_1|+(L-res\times2)$。

[code](https://codeforces.com/contest/1902/submission/237310189)

---

## 作者：abensyl (赞：0)

原题：[CF1902E Collapsing Strings](https://www.luogu.com.cn/problem/CF1902E)。

## 思路

由于要找的是前后缀相同的地方，很容易想到前缀 trie 树，在前缀 trie 树上，再 trie 树上，把两个字符串同源的部分减去即可。

由于是前后缀匹配，所以只需将其中一个字符串倒序之后再放到 trie 树里查找即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define i128 __int128
using namespace std;
const int N = 1e6 + 3, M = 1e6 + 3;
i128 tot,res;
void read(__int128 &x) {
	x=0; int f=1; char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	x*=f;
}
inline void print(__int128 x) {
	if(x<0) putchar('-'),x=-x;
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
struct node {
	int ch[N][26],ed[N],tot=0;
	void insert(string s) {
		int cur=0;
		for(auto c:s) {
			if(!ch[cur][c-'a']) ch[cur][c-'a']=++tot;
			cur=ch[cur][c-'a'];
			ed[cur]++;
		}
	}
	void query(string s) {
		int cur=0;
		for(auto c:s) {
			if(!ch[cur][c-'a']) return;
			cur=ch[cur][c-'a'];
			res-=i128(ed[cur])*i128(2);
		}
	}
} tr;
string s[M];
signed main() {
	i128 n; read(n);
	for(int i=1;i<=n;++i)
		cin>>s[i],
		tr.insert(s[i]),
		tot+=i128(s[i].size());
	for(int i=1;i<=n;++i) {
		reverse(s[i].begin(),s[i].end());
		res+=tot+(i128)(s[i].size())*i128(n);
		tr.query(s[i]);
	} //cout<<int(res)<<'\n';
	print(res);
	return 0;
}
```

[我的 AC 记录](https://codeforces.com/contest/1902/submission/235599963)。

---

## 作者：Fire_flame (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1902E)

## $\mathtt{Solution1}$

可以考虑哈希。

使用一个 map 统计每一个字符串从前往后扫和从后往前扫的哈希值，再统计答案即可。

我这里写的是自然溢出，带模哈希过不了 pretest。

当然，这样容易被 hack，例如我。

```cpp
#include<bits/stdc++.h>//此为赛时被hack代码
#define ULL unsigned long long
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 1e6 + 5, E = 1907;
int n;
ULL ans;
string s[MAXN];
unordered_map<ULL, int>mp;
signed main(){
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1;i <= n;i ++)cin >> s[i];
	for(int i = 1;i <= n;i ++){
		int len = s[i].length();
		ULL h = 0;
		ans += len * n;
		for(int j = 0;j < len;j ++){
			h = h * E + s[i][j] - 'a' + 1;
			mp[h] ++;
		}
	}
	for(int i = 1;i <= n;i ++){
		int len = s[i].length();
		ULL h = 0;
//		cout << len << endl;
		for(int j = len - 1;j >= 0;j --){
//			cout << j << endl;
			h = h * E + s[i][j] - 'a' + 1;
			ans -= mp[h];
		}
	}
	cout << ans * 2;
	return 0;
}
```

## $\mathtt{Solution2}$

我们可以把哈希替换成字典树。

对于树上每个结点，记录有多少个字符串经过它，然后统计答案就行了。

---

