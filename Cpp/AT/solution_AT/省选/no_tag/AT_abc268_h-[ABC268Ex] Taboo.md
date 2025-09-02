# [ABC268Ex] Taboo

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc268/tasks/abc268_h

文字列 $ S $ が与えられます。また、高橋君は次の操作を $ 0 $ 回以上行うことが出来ます。

- $ 1\ \leq\ i\ \leq\ |S| $ なる整数 $ i $ を選び、$ S $ の $ i $ 文字目を `*` に変える。

高橋君の目的は、$ S $ の**部分文字列として** $ N $ 個の文字列 $ T_1,T_2,\ldots,T_N $ がいずれも現れないようにすることです。  
 これを達成するために必要な操作の回数の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ |S|\ \leq\ 5\ \times\ 10^5 $
- $ 1\ \leq\ N $
- $ N $ は整数
- $ 1\ \leq\ |T_i| $
- $ \sum{|T_i|}\ \leq\ 5\ \times\ 10^5 $
- $ i\ \neq\ j $ ならば $ T_i\ \neq\ T_j $
- $ S,\ T_i $ は英小文字のみからなる文字列

### Sample Explanation 1

$ i $ として $ 1 $ と $ 9 $ を選んで操作をすると $ S $ は `\*bcdefgh\*jklmn` となり、`abcd`、`ijk`、`ghi` がいずれも部分文字列として現れなくなります。

### Sample Explanation 2

操作をする必要がありません。

## 样例 #1

### 输入

```
abcdefghijklmn
3
abcd
ijk
ghi```

### 输出

```
2```

## 样例 #2

### 输入

```
atcoderbeginnercontest
1
abc```

### 输出

```
0```

## 样例 #3

### 输入

```
aaaaaaaaa
2
aa
xyz```

### 输出

```
4```

# 题解

## 作者：ZHR100102 (赞：1)

~~你说得对，但是我忘了在 fail 树下传标记浪费了 0.5 h。~~

# 思路

显然，当我们匹配到一个字符串后，最优的做法是在结尾设置一个星号。因为放到后面能覆盖掉更多的区间，把模式串中匹配的子串尽可能多地破坏掉。

那么我们建出 ACAM 后跑多模式串匹配，遇到匹配的直接标记为星号，然后回到 ACAM 的根节点继续匹配即可。

注意一定要在 fail 树上下传匹配标记！

时间复杂度 $O(n|\sum|)$。

# 代码

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
#define lc(x) (tr[x].ls)
#define rc(x) (tr[x].rs)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
const int N=500005;
char s[N],t[N];
int ch[N][30],idx=0,ne[N],n;
bitset<N>cnt;
void insert(char *t)
{
    int p=0;
    for(int i=1;t[i];i++)
    {
        int j=t[i]-'a';
        if(ch[p][j]==0)ch[p][j]=++idx;
        p=ch[p][j];
    }
    cnt[p]=1;
}
void build()
{
    queue<int>q;
    for(int i=0;i<26;i++)
    {
        if(ch[0][i])q.push(ch[0][i]);
    }
    while(!q.empty())
    {
        int u=q.front();q.pop();
        cnt[u]=(cnt[u]|cnt[ne[u]]);
        for(int i=0;i<26;i++)
        {
            int v=ch[u][i];
            if(v)ne[v]=ch[ne[u]][i],q.push(v);
            else ch[u][i]=ch[ne[u]][i];
        }
    }
}
void solve()
{
    int p=0,ans=0;
    for(int i=1;s[i];i++)
    {
        int j=s[i]-'a';
        p=ch[p][j];
        if(cnt[p])p=0,ans++;
    }
    cout<<ans;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>s+1;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>t+1;
        insert(t);
    }
    build();
    solve();
    return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

复习一下 AC 自动机。不过这题非常模板。

考虑把所有的 Taboo 都给标记成一个个区间。很容易发现，我们标记的 `*` 必然在某个串的末尾，不然将其往后移至第一个末尾肯定更优。

于是我们必定在恰好匹配到某个串的时候把它标记成 `*`。此时标记是最优的，而且不得不标记。这个标记后前面所有的信息都不可能再发生匹配了，因此直接从根开始继续匹配。

因此你直接跑 AC 自动机就好了。每次遇到标记就把答案加一，并且返回自动机的初始状态。

代码：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e5+10;
int n,flg[MAXN],tot,tr[MAXN][27],fail[MAXN];
string T,S[MAXN];
void insert(string S) {
	int u=0;
	for(auto ch:S) {
		if(!tr[u][ch-'a']) tr[u][ch-'a']=++tot;
		u=tr[u][ch-'a'];
	}
	flg[u]=1;
	return ;
}
void init(void) {
	queue<int> q;
	ffor(i,0,25) if(tr[0][i]) q.push(tr[0][i]);
	while(!q.empty()) {
		int u=q.front(); q.pop();
		flg[u]|=flg[fail[u]];
		ffor(i,0,25) {
			if(tr[u][i]) q.push(tr[u][i]),fail[tr[u][i]]=tr[fail[u]][i];
			else tr[u][i]=tr[fail[u]][i];
		}
	}
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T>>n;
	ffor(i,1,n) cin>>S[i],insert(S[i]);
	int ans=0,u=0; init();
	for(auto ch:T) {
		u=tr[u][ch-'a'];
		if(flg[u]) ans++,u=0;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Register_int (赞：1)

~~好水一 Ex~~  
用所有模式串建出 AC 自动机，每次与原串匹配时，添加匹配上的字符串区间 $(l,r)$，问题就转化为：选择最少的点，让每个区间中都至少包含一个点。排序贪心解决。  
然而这样的算法十分优秀，排序会导致超时。由于每次匹配的右端点都在移动，所以可以省去排序。  
但是优化过的算法依然十分优秀，因为区间个数是 $O(n^2)$ 的，这导致我们必须舍弃一些不可能匹配的区间。在建自动机过程中，可以记录匹配时的最小长度，这样在匹配原串时就可以直接取到相同右端点下的最大左端点，从而避开无用区间。由于每个右端点只可能更新最大的左端点，所以区间个数是 $O(|S|)$ 的。那么这题就做完了。
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 5e5 + 10;
const int inf = 0x3f3f3f3f;

int ch[MAXN][26], fail[MAXN], tot;

int len[MAXN], f[MAXN];

inline 
void insert(char *s) {
    int n = strlen(s), k = 0;
    for (int i = 0; i < n; i++) {
        if (!ch[k][s[i] - 'a']) ch[k][s[i] - 'a'] = ++tot;
        k = ch[k][s[i] - 'a'];
    }
    len[k] = n;
}

inline 
void build() {
    queue<int> q;
    for (int i = 0; i < 26; i++) {
        if (ch[0][i]) q.push(ch[0][i]);
    }
    f[0] = inf;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        f[u] = len[u] ? min(len[u], f[fail[u]]) : f[fail[u]];
        for (int i = 0; i < 26; i++) {
            if (ch[u][i]) fail[ch[u][i]] = ch[fail[u]][i], q.push(ch[u][i]);
            else ch[u][i] = ch[fail[u]][i];
        }
    }
}

int maxr, ans;

inline 
void find(char *s) {
    int n = strlen(s), k = 0;
    for (int i = 0; i < n; i++) {
        k = ch[k][s[i] - 'a'];
        if (i - f[k] + 2 > maxr) ans++, maxr = i + 1;
    }
}

int n, m;

char s[MAXN], t[MAXN];

int main() {
    scanf("%s%d", s, &m), n = strlen(s);
    for (int i = 1; i <= m; i++) scanf("%s", t), insert(t);
    build(), find(s);
    printf("%d", ans);
}
```

---

## 作者：copper_ingot (赞：0)

我的 2025 年的第一篇题解！

也是第一篇紫题题解，祝自己在新的一年里紫气东来捏。

~~甚至是 AC 自动机，祝自己 AC 多多。~~

[题目传送门](https://www.luogu.com.cn/problem/AT_abc268_h)

[AT](https://atcoder.jp/contests/abc268/tasks/abc268_h)

AC 自动机模板。

用所有的模式串组成一个 AC 自动机，然后把文本串放在上面跑，如果遇到一个匹配的字符串就跳回根节点，相当于把这个字符改成 `*`。

但是暴力跳 `fail` 链会超时，所以对每个节点预处理其 `fail` 树的祖先中是否有标记节点。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
    int num[26], flag, fail;
}trie[2000001];
int n, m, cnt, a[1000001], ans; string s[1000001], t;
queue<int> q;
void insert(string s, int x){//插入单个字符串
    int u = 0;
    for (int i = 0; i < s.length(); i++){
        int k = s[i] - 97;
        if (!trie[u].num[k]) trie[u].num[k] = ++cnt;
        u = trie[u].num[k];
    }
    trie[u].flag++;
}
void ac(){//建自动机（作者建了字典图）
	for (int i = 0; i < 26; i++)
		if (trie[0].num[i]) q.push(trie[0].num[i]);
	while (!q.empty()){
		int u = q.front(); q.pop();
		for (int i = 0; i < 26; i++){
			int k = trie[u].num[i], k2 = trie[u].fail;
			if (k){trie[k].fail = trie[k2].num[i]; q.push(k);}
			else trie[u].num[i] = trie[k2].num[i];
			trie[u].flag |= trie[trie[u].fail].flag;//预处理
		}
	}
}
void find(){//跑自动机
    int u = 0;
    for (int i = 0; i < t.length(); i++){
        int k = t[i] - 97;
        u = trie[u].num[k];
		if (trie[u].flag) ans++, u = 0;
    }
}
int main(){
	cin >> t;
    scanf("%d", &n);
    memset(trie, 0, sizeof(trie));
    for (int i = 1; i <= n; i++){cin >> s[i]; insert(s[i], i);}
    ac(); find();
	printf("%d\n", ans);
    return 0;
}
```

---

## 作者：Arghariza (赞：0)

提供一个不用脑子的思路。

如果已经算出每个串的每个出现位置，相当于现在有若干个区间，你要在 $1\sim n$ 上选若干个点，使得每个区间至少覆盖一个点，并最小化选的点数。

这是个典型的贪心问题。如果取了一个点，则这个点右移到 所有覆盖了它的区间的交集 的右端点不影响答案，而 这个交集的右端点 一定是 某个区间的右端点。所以我们只需要考虑在某个区间的右端点上选点。

所以我们把所有区间按照右端点从小到大排序，枚举当前右端点 $r$，假设 $[1,r-1]$ 的子区间均满足题目条件，我们想让 $[1,r]$ 的子区间均满足条件，只需要考虑所有右端点为 $r$ 的区间。

维护最后一个选了的点 $R$，则点 $r$ 要被选当且仅当存在一个区间满足右端点为 $r$，左端点 $>R$。此时选上点 $r$ 并更新 $R=r$ 即可。

于是我们只需要对于每个 $r$ 维护出最大的 $l$，使得 $[l,r]$ 与某个 $T_i$ 匹配。AC 自动机即可，复杂度线性。

```cpp
// Problem: [ABC268Ex] Taboo
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc268_h
// Memory Limit: 1 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define eb emplace_back
#define mp make_pair
#define fi first
#define se second
#define F(i, x, y) for (int i = (x); i <= (y); i++)
#define R(i, x, y) for (int i = (x); i >= (y); i--)
#define FIO(FILE) freopen(FILE".in", "r", stdin), freopen(FILE".out", "w", stdout)

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
bool Mbe;

const int N = 5e5 + 5;
const int M = 26;

int n, m, ans;
string s, t;

struct ACAM {
	
	struct T { 
		int fl, l, ch[M]; 
	} t[N];
	
	int tot;
	
	ACAM () { tot = 1; }
	
	void i(string s) {
		int u = 1, len = s.length();
		F (i, 0, len - 1) {
			int v = s[i] - 'a';
			if (!t[u].ch[v]) {
				t[u].ch[v] = ++tot;
				t[tot].l = n + 1;
			}
			u = t[u].ch[v];
		}
		t[u].l = min(t[u].l, len);
	}
	
	void g() {
		queue<int> q;
		q.push(1);
		F (i, 0, M - 1) {
			t[0].ch[i] = 1;
		}
		t[1].l = n + 1;
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			F (i, 0, M - 1) {
				int &v = t[u].ch[i], f = t[u].fl;
				if (!v) {
					v = t[f].ch[i];
				} else {
					t[v].fl = t[f].ch[i];
					t[v].l = min(t[v].l, t[t[v].fl].l);
					q.push(v);
				}
			}
		}
	}
} A;

void solve() {
	cin >> s >> m;
	n = s.length();
	F (i, 1, m) {
		cin >> t;
		A.i(t);
	}
	A.g();
	int u = 1, R = -1;
	F (r, 0, n - 1) {
		u = A.t[u].ch[s[r] - 'a'];
		if (R <= r - A.t[u].l) {
			ans++;
			R = r;
		}
	}
	cout << ans << '\n';
}

bool Med;
int main() {
	// FIO("");
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：Tsawke (赞：0)

#  [[ABC268Ex] Taboo](https://www.luogu.com.cn/problem/AT_abc268_h) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC268Ex)

## 题面

给定仅有英文小写字母的字符串 $ S $，可以对其进行若干次操作，每次将 $ S $ 中某个字符替换为 `*`。给定 $ n $ 个仅有英文小写字母的模式串，要求进行操作使得 $ S $ 中不存在任意子串与模式串相同。最小化操作次数，输出最小值。

## Solution

提供一个**理论复杂度正确**但因常数以及哈希原因**无法通过**的做法，同时略提正解。

首先我们不难想到，我们若对 $ S $ 匹配模式串 $ T $，显然若匹配到了，那么我们直接将匹配到的部分的最后一位改为 `*` 即可，贪心正确性显然，若改前面的可能会存在后面再次匹配使得不优。

然后对于所有匹配，我们也不难想到处理的顺序可以是先处理长度较小的串，然后再处理较长的。此处的贪心正确性仍显然，因为短的串处理时一定会尽量地破坏长的串，总之感性理解一下。

所以就不难想到一个做法，开一个 `map < int, unordered_set < unsigned long long > >`，对每个长度的串映射一个 `set` 存储所有该长度的模式串的哈希值，然后按序跑一遍，通过维护哈希来 $ O(n) $ 跑一遍并匹配与替换。

分析一下这个的复杂度，显然每种长度都会跑一遍 $ O(n) $，那么卡此做法的构造应使长度为等差数列，而等差数列求和是 $ O(n^2) $ 级别的，所以最多的长度种类为 $ O(\sqrt{\sum T_i}) $，也就是说最终复杂度是根号级别的。不过此时我们会发现这俩都是 `5e5` 级别的，似乎过不了？但是再看一眼时限 $ 4\texttt{s} $，又似乎刚好能过。

不过实现之后会发现，部分测试点 WA，部分 TLE，TLE 的部分大概用了 $ 10\texttt{s} $，若改为 `unsigned int` 时间可以到 $ 7\texttt{s} $，但是同时也存在问题即哈希碰撞。我们自然可可以通过手写挂链或双模数等以使得满足正确性，但是时间上理性分析一下，等差数列实际是 $ \dfrac{n^2}{2} $ 的，所以此时还有个 $ 2 $ 倍常数，所以时间两倍之后寄掉也就很合理了。如果卡的不够死的话理论上还是可以改过的，但是也只是理论上，有兴趣可以尝试一下。

这里浅提一下正解，考虑刚才提到的贪心策略之后对于将所有模式串匹配掉直接写一个 AC自动机 即可，具体实现可以考虑如果一个节点的 `fail` 存在模式串那么该节点也认为是可以匹配的，也就是按照之前的贪心，优先去匹配更短的串。

## Code

### 理论复杂度正确但无法通过的代码

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW void* Edge::operator new(size_t){static Edge* P = ed; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define BASE (31ll)
#define S(i) (S.at(i - 1))

template < typename T = int >
inline T read(void);

int N;
string S;
map < int, unordered_set < unll > > pat;
unll pow_base[510000];
int ans(0);

int main(){
    // freopen("in.txt", "r", stdin);
    pow_base[0] = 1;
    for(int i = 1; i <= 501000; ++i)pow_base[i] = pow_base[i - 1] * BASE;
    ios::sync_with_stdio(false);
    cin >> S;
    cin >> N;
    for(int i = 1; i <= N; ++i){
        string T;
        cin >> T;
        unll hashv(0);
        for(auto c : T)(hashv *= BASE) += c;
        pat[(int)T.length()].insert(hashv);
    }
    for(auto mp : pat){
        if(mp.first > (int)S.length())continue;
        unll cur(0);
        bool newStr(true);
        for(int i = 1; i <= mp.first - 1; ++i)(cur *= BASE) += S(i);
        for(int i = mp.first; i <= (int)S.length(); ++i){
            if(!newStr)cur -= S(i - mp.first) * pow_base[mp.first - 1];
            cur *= BASE; cur += S(i); newStr = false;
            if(mp.second.find(cur) != mp.second.end()){
                S(i) = '*', cur = 0, newStr = true, ++ans;
                if(i + mp.first > (int)S.length())break;
                for(int j = i + 1; j <= i + mp.first - 1; ++j)(cur *= BASE) += S(j);
                i = i + mp.first - 1;
            }
        }
    }printf("%d\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

### 正解代码

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW void* Node::operator new(size_t){static Node* P = nd; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define d(c) (c - 'a')

template < typename T = int >
inline T read(void);

struct Node{
    Node* son[26];
    Node* fail;
    int cnt;
    OPNEW;
}nd[510000];
ROPNEW;
Node* root;

int N;
int ans(0);
string S;
basic_string < Node* > tmp;

void Insert(string S){
    Node* cur = root;
    for(auto c : S){
        if(!cur->son[d(c)])cur->son[d(c)] = new Node();
        cur = cur->son[d(c)];
    }cur->cnt++;
}
void Build(void){
    queue < Node* > cur; cur.push(root);
    while(!cur.empty()){
        auto p = cur.front(); cur.pop();
        for(int i = 0; i <= 25; ++i)
            if(p->son[i]){
                cur.push(p->son[i]), tmp += p->son[i];
                if(p == root)p->son[i]->fail = root;
                else p->son[i]->fail = p->fail->son[i];
            }else{
                if(p == root)p->son[i] = root;
                else p->son[i] = p->fail->son[i];
            }
    }
}
void SetFail(void){
    for(auto p : tmp)p->cnt += p->fail->cnt;
}
void Accept(void){
    Node* cur = root;
    for(auto c : S){
        cur = cur->son[d(c)];
        if(cur->cnt)++ans, cur = root;
    }
}

int main(){
    root = new Node();
    cin >> S;
    N = read();
    for(int i = 1; i <= N; ++i){string T; cin >> T; Insert(T);}
    Build(), SetFail(), Accept();
    printf("%d\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2023_01_18 初稿

update-2023_01_23 补充了一些关于正解的思路以及正解的代码

---

## 作者：junxis (赞：0)

# Analysis
容易想到对 $T$ 建出 AC 自动机。

然后对每个结点处理一个 $\mathtt{mark}$ 标记，代表是否存在一个串是从根到此点的路径上所形成的字符串的一个后缀。

有一个显然的贪心：若有两串 $T_i, T_j$ 且 $T_i$ 是 $T_j$ 的前缀，我们在匹配上 $T_i$ 的时候就加上一个星号就能顺便解决掉 $T_j$。所以我们在自动机上跑的时候需要能加星号就加星号。

直接拿 $S$ 从根开始跑匹配，如果走到了一个 $\mathtt{mark}$ 值为真的节点，代表此时需要将此位变成星号，自然，再往下走所有的串都会被这一个星号解决掉，那么就回到根重新走，并将答案加一。

# CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b)-1; i>=(a); i--)
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef basic_string<int> BI;
typedef long long ll;
typedef pair<int, int> PII;
typedef double db;
mt19937 mrand(random_device{}());
const ll mod=1000000007;
int rnd(int x) {return mrand() % x;}
ll powmod(ll b, ll e, ll md=mod) {ll a=1; b %= md; assert(e>=0); for (;e;e>>=1, b=b*b%md) if(e&1) {a=a*b%md;} return a;}
ll gcd(ll a, ll b) {return b?gcd(b,a%b):a;}
// head

const int M = 26, N = 501000;
struct node {
    node *son[M], *go[M], *fail;
    int mark;
}pool[N], *cur = pool, *root;

node *newnode() {
    return cur++;
}

int t;
node *q[N];

void build() {
    t = 0;
    q[t++] = root;
    for (int i = 0; i < t; i++) {
        node *u = q[i];
        for (int j = 0; j < M; j++) {
            if (u->son[j]) {
                u->go[j] = u->son[j];
                if (u == root) u->son[j]->fail = root;
                else u->son[j]->fail = u->fail->go[j];
                q[t++] = u->son[j];
            } else {
                if (u == root) u->go[j] = root;
                else u->go[j] = u->fail->go[j];
            }
        }
    }
} // ACAM

char tt[N], s[N];

int main() {        
    scanf("%s", s);
    int n = strlen(s);
    root = newnode();
    int _;
    scanf("%d", &_);
    rep(i,0,_) {
        scanf("%s", tt);
        int m = strlen(tt);
        node *p = root;
        rep(j,0,m) {
            int w = tt[j] - 'a';
            if (!p->son[w]) p->son[w] = newnode();
            p = p->son[w];
        }   
        p->mark=1;
    } 
    build();
    rep(i,1,t) q[i]->mark |= q[i]->fail->mark; 
    //建自动机
    
    node *p = root;
    int ans = 0;
    rep(i,0,n) {
        int w = s[i] - 'a';
        p = p->go[w];
        if (p->mark) ans++, p = root;
    } // 跑匹配
    printf("%d\n", ans);
}   
```

---

## 作者：lingfunny (赞：0)

# ABC268 Ex - Taboo

首先，一个字符串合法的必要条件是其所有子串都合法，不难想到利用此特性进行一些操作。

设 $f_i$ 为使前缀 $i$ 合法的最小花费，枚举末尾的一段最长合法后缀，不难有转移：
$$
f_i=\min_{\substack{1\le j \le i\\(j,i]\text{ is legal}}} f_{j-1}+1
$$
意思是把 $j$ 变为 `*`。从这个 dp 式子可以看出 $f$ 应该是一个单调函数，因为可转移的 $j$ 是有单调性的。边界为 $f_0=-1$。

上面这一段的 $(j, i] \text{ is legal}$ 比较抽象，意思是子串 $(j, i]$ 合法，即其中没有出现过 $T_i$。

由于是多模式串，不难想到用 AC 自动机解决。根据此意义，可以得到一个更抽象的定义如下：

- 空串是合法的；
- 一个非空串合法当且仅当其在 AC 自动机上转移时没有经过任何一个**终止节点**；
- AC 自动机上的一个状态被称为**终止节点**当且仅当该状态为某个 $T_i$ 的结束状态或其 fail 树上的祖先为**终止节点**。

然后手模一下样例：

```plain
str: aaaaaaaaa
f:   011223344
```

模拟的过程中突然被启发贪心了。

因为 $f$ 的单调性，dp 肯定是选择一段极长区间 $(j, i]$，然后从 $f_{j-1}$ 转移过来。

但是这样逆着考虑相当难转移，复杂度是 $O(n^2)$ 的。

不妨正着考虑：一开始从 AC 自动机的原点开始行走，设遇到的下一个字符为 $s_i$。先走向目标节点，如果目标节点为**终止节点**，则把 $s_i$ 修改为 `*`，回到 AC 自动机的原点。

考虑证明贪心的正确性：如果目标节点为**终止节点**，此时肯定是要修改某个字符的，问题只是在于修改哪个字符。如果修改的是下一个字符，则可以保证修改后自己回到 AC 自动机的原点；否则假设下一个字符是 $s_i$，修改的字符是 $s_j$，则修改后的状态为子串 $(j, i]$ 的状态。子串 $(j, i]$ 的状态肯定会比原点来得更劣（**更容易**走到**终止节点**）。

这里的**更容易**指的是：假设存在这样一个输入信号 $S$，使得当起始状态是原点时，中间会经过某个**终止节点**。那么对于起始状态不为原点的情况，接受输入信号 $S$ 后，一定也会经过某个**终止节点**。~~为什么？当作课后思考题了~~

时空复杂度 $O(\lvert S\rvert + \lvert\Sigma\rvert\sum\lvert T_i\rvert)$，$\lvert\Sigma\rvert$ 为字符集大小（此处为 $26$）。

## 代码

```cpp
// Problem: Ex - Taboo
// URL: https://atcoder.jp/contests/abc268/tasks/abc268_h
// Group: AtCoder - UNIQUE VISION Programming Contest 2022 Summer (AtCoder Beginner Contest 268)
// Time: 2022-12-01 16:21
// Author: lingfunny

#include <bits/stdc++.h>
using LL = long long;
using uint = unsigned;
using namespace std;
const int mxn = 5e5 + 10;

int n, m;
char s[mxn], t[mxn];

struct ACAM {
	int ch[26][mxn], tot, mark[mxn], fail[mxn];
	ACAM() : tot(0) {}
	void ins(char s[], int n) {
		int u = 0;
		for (int i = 1; i <= n; ++i) {
			int &v = ch[s[i] - 'a'][u];
			if (!v) v = ++tot;
			u = v;
		}
		mark[u] = 1;
	}
	void build() {
		queue<int> Q;
		vector<vector<int>> G(tot + 1);
		for (int i = 0; i < 26; ++i)
			if (ch[i][0]) Q.emplace(ch[i][0]);
		while (Q.size()) {
			int u = Q.front();
			G[fail[u]].emplace_back(u), Q.pop();
			for (int i = 0; i < 26; ++i)
				if (ch[i][u]) Q.emplace(ch[i][u]), fail[ch[i][u]] = ch[i][fail[u]];
				else ch[i][u] = ch[i][fail[u]];
		}
		function<void(int)> dfs = [&](int u) {
			for (int v : G[u]) mark[v] |= mark[u], dfs(v);
		};
		dfs(0);
	}
} A;

signed main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) scanf("%s", t + 1), A.ins(t, strlen(t + 1));
	A.build();
	int cur = 0, ans = 0;
	for (int i = 1; i <= n; ++i) {
		int v = A.ch[s[i] - 'a'][cur];
		if (A.mark[v]) ++ans, cur = 0;
		else cur = v;
	}
	printf("%d\n", ans);
	return 0;
}
```



---

