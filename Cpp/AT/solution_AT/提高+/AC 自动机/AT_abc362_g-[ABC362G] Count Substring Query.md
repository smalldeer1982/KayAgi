# [ABC362G] Count Substring Query

## 题目描述

### 题意
给你一个字符串 $S$ 和 $Q$ 个字符串， $T_1$ ~ $T_q$ ,问每一个 $T_i$ 分别在 $S$ 中出现多少次。

## 样例 #1

### 输入

```
missisippi
5
i
s
a
is
missisippi```

### 输出

```
4
3
0
2
1```

## 样例 #2

### 输入

```
aaaaaa
6
a
aa
aaa
aaaa
aaaaa
aaaaaa```

### 输出

```
6
5
4
3
2
1```

# 题解

## 作者：ivyjiao (赞：6)

前置知识：

- [P8306 【模板】字典树](https://www.luogu.com.cn/problem/P8306)
- [B3644 【模板】拓扑排序 / 家谱树](https://www.luogu.com.cn/problem/B3644)

- 什么是 AC 自动机？

AC 自动机，~~又称自动 AC 机~~，全称 Aho-Corasick automaton。

- AC 自动机的步骤？

1. 构造一棵 Trie 树。
2. 构造 Fail 指针。
3. 匹配。

- 怎么建 Trie 树？

这是你的前置知识，在此不做讲解。

代码：

```cpp
void insert(string s,int now){
    int u=0;
    for(int i=0;i<s.size();i++){
        int c=s[i]-'a';
        if(!trie[u][c]) trie[u][c]=++cnt;
        u=trie[u][c];
    }
	if(!vis[u]) vis[u]=now;//记录每个字符串都在哪个位置。
    //因为可能有重复的字符串，所以把所有相同的字符串指向第一次出现的位置。
    rev[now]=vis[u];//反向的vis，方便最后输出。
}
```

- 什么是 Fail 指针？

Fail 指针指向 Trie 树中该路径的最长后缀。

![](https://cdn.luogu.com.cn/upload/image_hosting/cvzvbd7s.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

如图，红色指针即为一些 Fail 指针，`b_` 和 `_a` 就是 `b` 和 `a`。

在本文我们不把 Fail 指针与 Kmp 数组作比较。

- 如何构造 Fail 指针？

设当前节点为 $u$，$trie[f][c]=u$。

设深度小于 $u$ 的所有结点的 Fail 指针都已求得。

1. 如果 $trie[fail[f]][c]$ 存在，则 $fail[trie[f][c]]=trie[fail[f]][c]$。

证明：因为 $fail[f]$ 是 $f$ 的后缀，所以 $trie[fail[f]][c]$ 是 $trie[f][c]$，即 $u$ 的后缀。

2. 如果 $trie[fail[f]][c]$ 不存在，那么我们继续找到 $trie[fail[fail[f]]][c]$。重复 1 的判断过程，一直跳 Fail 指针直到根结点。

证明：因为 $fail[f]$ 是 $f$ 的后缀，$fail[fail[f]]$ 
是 $fail[f]$ 的后缀，所以 $fail[fail[f]]$ 是 $f$ 的后缀，所以 $trie[fail[fail[f]]][c]$ 是 $trie[f][c]$，即 $u$ 的后缀。

3. 如果跳到最后都没有，指向根节点。

代码细节：

1. 求 Fail 要用 BFS。

证明：由于我们假设**深度小于 $u$ 的所有结点**的 Fail 指针都已求得，跳 Fail 时节点深度也只会越来越小，所以求 Fail 要用 BFS。

2. 若 $u$，即 $trie[f][c]$ 不存在，令 $trie[f][c]=trie[fail[f]][c]$。

证明：因为 $fail[f]$ 是 $f$ 的后缀，所以 $trie[fail[f]][c]$ 是 $trie[f][c]$ 的后缀。由于我们 $trie[f][c]$ 路径肯定比 $trie[fail[f]][c]$ 路径要长，匹配了 $trie[f][c]$ 路径一定能匹配 $trie[fail[f]][c]$ 路径，所以不会影响答案。

好处：直接记录下一个能匹配的位置，压缩了跳 Fail 的路径，把 $O(\log n)$ 的复杂度压缩到 $O(1)$，不会被卡掉。

![](https://cdn.luogu.com.cn/upload/image_hosting/8l67wsuq.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

当然，如果 $trie[fail[f]][c]$ 也不存在，那就无事发生了（即连回根节点）。

![](https://cdn.luogu.com.cn/upload/image_hosting/q3tnq6i9.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

这个东西也是可以自指的。

![](https://cdn.luogu.com.cn/upload/image_hosting/zvrqrzsd.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

代码：

```cpp
void getfail(){
    queue<int>q;
    for(int i=0;i<26;i++){
        if(trie[0][i]) q.push(trie[0][i]);
    }
    while(q.size()){
        int u=q.front();
        q.pop();
        for(int i=0;i<26;i++){
            if(trie[u][i]){
				fail[trie[u][i]]=trie[fail[u]][i];
				q.push(trie[u][i]);
                ins[trie[fail[u]][i]]++;//为后面的拓扑排序做准备。
			}
            else trie[u][i]=trie[fail[u]][i];//路径压缩。
        }
    }
}
```

- 如何匹配？

$u$ 在字典树上跟踪当前字符，利用 Fail 指针找出所有匹配的模式串。

```cpp
void query(string t){
    int u=0;
    for(int i=0;i<t.size();i++){
        u=trie[u][t[i]-'a'];//此时的trie树已经被修改了，该步骤一定成立。
        for(int j=u;j;j=fail[j]) ans[vis[j]]++;
    }
}
```

我们也可以只标记找到的节点，再用拓扑排序求出答案。

此部分代码需要结合拓扑排序部分代码理解。

代码：

```cpp
void query(string t){
    int u=0;
    for(int i=0;i<t.size();i++){
        u=trie[u][t[i]-'a'];//此时的trie树已经被修改了，该步骤一定成立。
        ans[u]++;
    }
}
```

- Fail 树

又称失配树。

所有的 Fail 边构成一棵树。

证明：

1. Fail 边不会成环。
2. Fail 边的深度比当前节点的深度要小。

- 拓扑排序优化

由于所有的 Fail 边构成一棵树，所以可以对其进行拓扑排序，从而求得答案。

```cpp
void topu(){
    queue<int>q;
    for(int i=1;i<=cnt;i++){
        if(!ins[i]) q.push(i);
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        flag[vis[u]]=ans[u];
        //统计每个字符串出现的次数，若vis[u]=0则代表该位置不是字符串的结尾。
        int v=fail[u];//遍历失配树。
        ans[v]+=ans[u];//下传答案。
        //能够这样做的原因是：如果一个字符串出现了n次，那么它的后缀也会出现至少n次。
        if(!(--ins[v])) q.push(v);//拓扑排序流程
    }
}
```

到这里我们的答案就求出来了。

- 输出答案

很显然，输出 $flag[rev[i]]$。

```cpp
for(int i=1;i<=n;i++) cout<<flag[rev[i]]<<endl;
```

- 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,trie[5000001][27],fail[5000001],flag[5000001],rev[5000001],cnt,vis[5000001],ins[5000001],l,maxn,ans[500001];
string s[500001],t;
void insert(string s,int now){
    int u=0;
    for(int i=0;i<s.size();i++){
        int c=s[i]-'a';
        if(!trie[u][c]) trie[u][c]=++cnt;
        u=trie[u][c];
    }
	if(!vis[u]) vis[u]=now;
    rev[now]=vis[u];
}
void getfail(){
    queue<int>q;
    for(int i=0;i<26;i++){
        if(trie[0][i]) q.push(trie[0][i]);
    }
    while(q.size()){
        int u=q.front();
        q.pop();
        for(int i=0;i<26;i++){
            if(trie[u][i]){
				fail[trie[u][i]]=trie[fail[u]][i];
				q.push(trie[u][i]);
                ins[trie[fail[u]][i]]++;
			}
            else trie[u][i]=trie[fail[u]][i];
        }
    }
}
void query(string t){
    int u=0;
    for(int i=0;i<t.size();i++){
        u=trie[u][t[i]-'a'];
        ans[u]++;
    }
}
void topu(){
    queue<int>q;
    for(int i=1;i<=cnt;i++){
        if(!ins[i]) q.push(i);
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        flag[vis[u]]=ans[u];
        int v=fail[u];
        ans[v]+=ans[u];
        if(!(--ins[v])) q.push(v);
    }
}
int main(){
    cin>>t;
    while(cin>>n&&n){
        memset(trie,0,sizeof trie);
        memset(ans,0,sizeof ans);
        memset(fail,0,sizeof fail);
        memset(vis,0,sizeof vis);
        memset(flag,0,sizeof flag);
        cnt=0;
        l=0;
        for(int i=1;i<=n;i++){
            cin>>s[i];
            insert(s[i],i);
        }
        getfail();
        query(t);
        topu();
        for(int i=1;i<=n;i++) cout<<flag[rev[i]]<<endl;
    }
}
```

---

## 作者：M1saka16I72 (赞：6)

## 前言

[更可爱的阅读体验](https://misaka16172.github.io/solution-abc362-g.html)

ABC 出题人喜欢出板子是吧，像这种出题人就应该好好用乱搞拷打一下。

拜谢 [@RailgunZzzz](https://www.luogu.com.cn/user/586905) 以及其他 HL 群群友在卡常和卡哈希时给予的若干帮助。

## 思路

先处理出整串哈希，然后我们考虑根号分治。

设根号分治的阈值为 $T$，则有两种算法可以用来回答询问：

1. 对长度 $>T$ 的串暴力。求出被询问的串的哈希，从左到右枚举被匹配的子串的右端点，把两个哈希 $\mathcal{O}(1)$ 进行比较，单次询问复杂度 $\mathcal{O}(n)$。设 $sum=\sum |t|$（$t$ 为被询问的串），长度 $>T$ 的串最多被询问 $\mathcal{O}(\frac{sum}{T})$ 次，所以这部分时间复杂度为 $\mathcal{O}(n\frac{sum}{T})$。
2. 对长度 $\leq T$ 的串预处理。预处理原串所有长度 $\leq T$ 的子串的哈希值，扔到 $T$ 个 vector 里进行排序，类似于离散化，每次回答时二分询问串的哈希在 vector 里的位置即可得知它出现了几次。这部分预处理的时间复杂度为 $\mathcal{O}(Tn\log n)$，单次回答复杂度 $\mathcal{O}(\log n)$。

对以上两种算法进行根号平衡，列均值等式解得 $T≈\sqrt{\frac{sum}{\log n}}$，算法总复杂度为 $\mathcal{O}(n\sqrt{sum\log n})$，理论可过，但常数巨大，需要进一步优化。

## 卡常 & 卡哈希

### 调整阈值

我们的阈值里面带了一个 $sum$，而求出 $sum$ 的唯一办法就是将询问离线，可是开一个大小为 $q$ 的 `string` 数组无疑会带来巨大的常数开支，于是考虑多尝试几种阈值。

经过测试，取 $T=\frac{\sqrt q}{\log n}$ 时，是所有阈值里运行速度最快的，推测：显然这个 $T$ 值比计算的 $T$ 值小，会让更多的串去跑暴力，而暴力解法常数较小。

### 自然溢出

尝试了无数种卡常方式之后，发现尽管是无法保证正确性的单模哈希，在题目时限下都无法通过。在这种情况下，我们只能使用 `unsigned int` 自然溢出处理哈希（连 `unsigned long long` 自然溢出都会 TLE）。

裸的自然溢出交上去是[这样](https://atcoder.jp/contests/abc362/submissions/55596211)的，使用 BingFS 搜索卡自然溢出的方法，发现哈希 base 为偶数时极其容易被卡掉，而奇数 base 相对难卡很多。于是引出下一种乱搞：随机 base。

### 随机奇数 base

使用一个 `mt19937` 在预处理时生成随机 base 即可，这部分比较简单，加上之后虽然还是无法通过，但 WA 的测试点数量已经大幅降至了 $1$ 至 $4$ 个。

### 小串使用双模哈希，大串使用自然溢出

我们充分利用人类智慧，发现询问的串长度越小，是出题人故意造出来 hack 自然溢出的概率就越高。于是我们在算法的第二部分放弃自然溢出，换用准确度接近 $100\%$ 的双模哈希来处理长度 $\leq T$ 的串，而在第一部分的暴力解法中仍然使用自然溢出，最大限度发挥暴力常数小的优势。

经过上述所有优化之后的代码平均提交 $6$ 次就可以取得一次 AC。

## 代码

[link](https://atcoder.jp/contests/abc362/submissions/55600110)

---

## 作者：Engulf (赞：1)

注意本篇题解不是 AC 自动机讲解，是非拓扑排序的查询讲解。

本题是 AC 自动机模板题，与 [P5357](https://www.luogu.com.cn/problem/P5357) 完全一样。

我看题解区都写的啥拓扑排序优化我看不懂啊，给个另解吧。

建出 $T_i$ 的 AC 自动机后，对于每个节点 $u$，从它的失配指针向它连一条边，具体地，对于每个 $u$ 都连一条 $\textrm{fail}_u \to u$ 的边。这样就形成一棵树，叫它 fail 树。

fail 树有个显然的性质：$u$ 在它的子树中都会出现。

因为 fail 的定义是最长的和当前后缀匹配的前缀的位置，所以 fail 所代表的字符串一定在以它为 fail 的地方都出现了一遍。

直接把 $S$ 扔进去匹配，对于经过的节点 $p$，只要不停地跳 fail，说明 $S$ 的这个前缀在 fail 树上 $p$ 到根的路径上都出现过，就是一个路径加。因为是最后再查询，直接树上差分维护即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 5e5 + 5;

int tr[N][26], idx;
int bel[N];
int fail[N];

void insert(int id, string s) {
    int p = 0;
    for (auto c: s) {
        if (!tr[p][c - 'a']) tr[p][c - 'a'] = ++idx;
        p = tr[p][c - 'a'];
    }
    bel[id] = p;
}

vector<int> g[N];
int siz[N];

void getfail() {
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (tr[0][i])
            q.push(tr[0][i]);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        g[fail[u]].emplace_back(u);
        for (int i = 0; i < 26; i++)
            if (tr[u][i]) {
                fail[tr[u][i]] = tr[fail[u]][i];
                q.push(tr[u][i]);
            } else tr[u][i] = tr[fail[u]][i];
    }
}

void dfs(int u) {
    for (auto v: g[u]) {
        dfs(v);
        siz[u] += siz[v];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; int n;
    cin >> s >> n;
    for (int i = 1; i <= n; i++) {
        string t;
        cin >> t;
        insert(i, t);
    }

    getfail();

    int p = 0;
    for (auto c: s) {
        p = tr[p][c - 'a'];
        siz[p]++;
    }

    dfs(0);

    for (int i = 1; i <= n; i++)
        cout << siz[bel[i]] << "\n";
    return 0;
}
```

---

## 作者：joe_zxq (赞：1)

# Part 1 - 算法思路

~~欢迎参加 AtCoder Template Contest！~~ 

这里是 AC 自动机模板题，题意与 P5537 相同。

本题要求查询字符串 $S$ 中，有多少个不同的子串与给定的查询字符串 $T_i$ 相等。由于直接对每个查询进行暴力匹配会超时，我们需要使用更高效的数据结构或算法。考虑到题目中字符串和查询的数量级，AC 自动机是处理这类多模式匹配问题的理想选择。

AC 自动机是一个有限状态机，用于处理字符串的集合（即字典）中的多模式匹配问题。它基于 Trie 树构建，并在 Trie 树的每个节点上增加了指向 Trie 树中其他节点的失败指针，这些失败指针用于在 Trie 树中模拟 KMP 算法中的部分匹配表，以便在搜索过程中快速跳过不匹配的路径。

算法步骤如下：

1. **构建 Trie 树**：首先，将所有查询字符串 $T_i$ 插入到 Trie 树中。

2. **构建 AC 自动机**：在 Trie 树的基础上，为每个节点添加失败指针。失败指针的构建通常使用 BFS 来实现。

3. **统计结果**：遍历字符串 $S$，对于 $S$ 中的每个字符，从 Trie 树的根节点开始，沿着当前字符对应的边向下走，同时利用失败指针进行跳转，以覆盖所有可能的匹配。在遍历过程中，统计每个查询字符串的匹配次数。

# Part 2 - 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll n, tot, fail[514514], t[514514][30], sz[514514];
string ss, s[514514];
vector<ll> g[514514];
queue<ll> q;

void insert(string ss) {
	ll now = 0;
	for (char c : ss) {
		c -= 'a';
		if (!t[now][c]) {
			t[now][c] = ++tot;
		}
		now = t[now][c];
	}
}

ll query(string ss) {
	ll now = 0;
	for (char c : ss) {
		c -= 'a';
		now = t[now][c];
	}
	return now;
}

void topu() {
	for (char c = 0; c < 26; c++) {
		if (t[0][c]) {
			q.push(t[0][c]);
		}
	}
	while (!q.empty()) {
		ll now = q.front();
		q.pop();
		for (char c = 0; c < 26; c++) {
			if (t[now][c]) {
				fail[t[now][c]] = t[fail[now]][c];
				q.push(t[now][c]);
			} else {
				t[now][c] = t[fail[now]][c];
			}
		}
	}
	for (ll i = 1; i <= tot; i++) {
		g[fail[i]].push_back(i);
	}
}

void dfs(ll u) {
	for (ll v : g[u]) {
		dfs(v);
		sz[u] += sz[v];
	}
}

int main() {

	cin >> ss >> n;
	for (ll i = 1; i <= n; i++) {
		cin >> s[i];
		insert(s[i]);
	}
	topu();
	ll now = 0;
	for (char c : ss) {
		c -= 'a';
		now = t[now][c];
		sz[now]++;
	}
	dfs(0);
	for (ll i = 1; i <= n; i++) {
		cout << sz[query(s[i])] << '\n';
	}
 
	return 0;
}
```

---

## 作者：stripe_python (赞：0)

本文旨在帮助一个 pj 组选手理解 AC 自动机。

# KMP

## 引入

给你两个串 $s_1,s_2$，求出 $s_2$ 在 $s_1$ 中的出现位置。

你略微思考，写出了如下代码：

```cpp
int n = s1.size(), m = s2.size();
for (int i = 0; i + m - 1 < n; i++) {
	if (s1.substr(i, m) == s2) cout << i << ' ';
}
```

这样一共要做 $n(n-m)$ 次操作，复杂度为 $O(n^2)$ 级别。

你经过思考，发现没有必要每次都暴力 `substr`，只需要设定一个匹配指针，如果不匹配就不用再判断了。

但是，字符串不是随机的，比如：

```plain
s1: 000000000...0000000000000000000000001
s2: 000000000...0000000001
```

这会使这个匹配算法退化到 $O(n^2)$ 级别。

## 优化思路

针对字符串匹配，有两种优化思路：

1. 优化比较的复杂度；
2. 优化指针扫描。

第一种优化引出了字符串哈希，而 KMP 属于第二种优化。

## KMP 基本思想

对于这样一个字符串 `ababc`，如果我们已经匹配过 `ab` 并失配，还有必要把指针退回去匹配吗？这时候，我们已经知道模式串的下一位是 `b` 不是 `a`，直接跳过去即可。

跳过去多少呢？我们引入 KMP 中的 `next` 数组。`next` 数组就记录了你要跳多少。这个东西在稍后的 AC 自动机中称作**失配指针**。

假设我们已经求出了 `next`，就可以容易地解决上面的问题：

```cpp
vector<int> kmp(const string& text, const string& patt) {
  int n = (int) text.size(), m = (int) patt.size();
  int j = -1;
  vector<int> pos;
  for (int i = 0; i < n; i++) {
    for (; j >= 0 && text[i] != patt[j + 1]; j = nxt[j]);  // 跳 next
    if (text[i] == patt[j + 1]) j++;
    if (j == m - 1) pos.push_back(i - m + 1);
  }
  return pos;
}
```

由于指针只会向前移动，KMP 算法的复杂度是 $O(n+m)$ 的。

## 求解 next

如果直接暴力求 `next`，复杂度将退化到 $O(m^3)$。

先给 `next` 一个严谨的定义：$next_i$ 代表在第 $1$ 到第 $i-1$ 位中的前缀与后缀相同的部分最长是多长。

显然 `next` 具有如下性质：

1. $next_i \le i$。
2. $next_{i+1} \le next_{i}+1$。

你会发现，`next` 实际上是串自己与自己匹配的过程。做法也是很类似的：

```cpp
int nxt[N];
	
inline void get_next(const string& patt) {
  memset(nxt, 0, sizeof(nxt));
  int n = (int) patt.size();
  nxt[0] = -1;
  int j = -1;
  for (int i = 1; i < n; i++) {
    for (; j >= 0 && patt[i] != patt[j + 1]; j = nxt[j]);
    if (patt[i] == patt[j + 1]) j++;
    nxt[i] = j;
  }
}
```

# 字典树

字典树（Trie）是通过把一些字符串的相同前缀压缩在一起，达到节省时间 / 空间的目的。

字典树是维护字符串集合的主要工具，下图展示了一棵字典树：

![](https://cdn.luogu.com.cn/upload/image_hosting/3gd99cpg.png)

# AC 自动机

## 引入

AC 自动机的本质是在字典树上做 KMP。

对于本题，如果我们对每个 $T$ 都做 KMP，其复杂度为 $O(nm)$，这是无法接受的。

考虑用一棵字典树把 $T$ 压缩起来，字典树上做 KMP。

## fail 指针

字典树上的 fail 指针对应了 KMP 的 next 数组。

采用 BFS 层次遍历，对于节点 $u$，设其父亲为 $f$，$f$ 到 $u$ 的边上字符为 $c$。

若存在 $fail_{f,c}$，对应 next 数组，令 $fail_{u,c} \gets fail_{f,c}$ 即可。

若不存在，就暴力向上跳，一直跳到有为止。反之，指向根。

## 匹配过程

从起点开始匹配，若失配，就跳到 fail 指针所在节点再次匹配。

## 拓扑排序优化

暴力构建 fail 的复杂度是 $O(m^2)$ 的，需要优化。

我们把所有 fail 单独拿出来构成一棵树，直接拓扑排序即可。

## 代码

最后放个这题的代码吧：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define N 2000005

int n;
string s, t;

int cnt = 1, mp[N];
struct node {
	int son[26], fail, flag, res;
	void clear() {memset(son, 0, sizeof(son)), fail = flag = res = 0;}
} trie[N];

inline void insert(const string& s, int num) {
	int u = 1, n = s.size();
	for (int i = 0; i < n; i++) {
		int v = s[i] - 'a';
		if (!trie[u].son[v]) trie[u].son[v] = ++cnt;
		u = trie[u].son[v];
	}
	if (!trie[u].flag) trie[u].flag = num;
	mp[num] = trie[u].flag;
}

queue<int> q;
int indeg[N];

inline void build() {
	for (int i = 0; i < 26; i++) trie[0].son[i] = 1;
	q.emplace(1);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		int fail = trie[u].fail;
		for (int i = 0; i < 26; i++) {
			int v = trie[u].son[i];
			if (!v) {
				trie[u].son[i] = trie[fail].son[i];
				continue;
			}
			trie[v].fail = trie[fail].son[i];
			indeg[trie[v].fail]++;
			q.emplace(v);
		}
	}
}

void query(const string& s) {
	int u = 1, n = s.size();
	for (int i = 0; i < n; i++) {
		u = trie[u].son[s[i] - 'a'];
		trie[u].res++;
	}
}

int vis[N];
inline void toposort() {
	for (int i = 1; i <= cnt; i++) {
		if (indeg[i] == 0) q.emplace(i);
	}
	while (!q.empty()) {
		int u = q.front(); q.pop();
		vis[trie[u].flag] = trie[u].res;
		int v = trie[u].fail; 
		trie[v].res += trie[u].res;
		if (--indeg[v] == 0) q.emplace(v);
	}
}

void _main() {
	cin >> t;
	cin >> n;
	cnt = 1;
	for (int i = 1; i <= n; i++) {
		cin >> s;
		insert(s, i);
	}
	build();
	
	query(t);
	toposort();
	for (int i = 1; i <= n; i++) cout << vis[mp[i]] << '\n';
} signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	_main();
	return 0;
}
```

---

## 作者：Leo11 (赞：0)

## 观前提醒

在观看前，先需要学习一下三个算法：

- [字典树](https://oiwiki.org/string/trie/)

- [KMP](https://oiwiki.org/string/kmp/)

- [拓扑排序](https://oiwiki.org/graph/topo/)

以及通过以下习题：

- [P8306 【模板】字典树](https://www.luogu.com.cn/problem/P8306)

- [P3375 【模板】KMP](https://www.luogu.com.cn/problem/P3375)

- [B3644 【模板】拓扑排序 / 家谱树](https://www.luogu.com.cn/problem/B3644)

## 前言
在前面的学习中，我们认识到了用于做单模匹配的算法 KMP 。但是， KMP 的效率还不足以使得我们进行多模匹配。对于 $k$ 个模式串的匹配， KMP 算法的复杂度将会达到 $O((n+m)k)$ ，效率并不高。从而想到了字典树用于进行多模式匹配的操作。但是，字典树的效率也似乎不够。那么我们该如何优化字典树的操作呢？

## 算法详解
显然，字典树的插入操作不需要做什么优化。而在查找时，我们就要使用 KMP 的**思想**了。对于失配节点，设置一个失配指针，使得对于 $i$ 点的失配指针指向 $j$ ，则 $root$ 至 $j$ 的字符串为 $root$ 至 $i$ 的后缀。对于每一个构建的失配指针，应使其深度**尽量地大**。

### 插入操作

和字典树一样，作为**学习该算法的必要知识**不需要讲。


```cpp
void insert(string s, int x)
{
	int u = 1, len = s.size();
	for(int i = 0; i < len; i++)
	{
		int v = s[i] - 'a';
		if(!trie[u].son[v])
		{
			trie[u].son[v] = ++cnt;
		}
		u = trie[u].son[v];
	}
	if(!trie[u].f)
	{
		trie[u].f = x;
	}
	mp[x] = trie[u].f;
}
```

### 求失配指针
那么我们该如何求得每个节点的失配指针呢？首先，第一层节点的失配指针**一定指向** $root$ ，而对于其他节点来说，由于失配指针指向后缀，所以每一个点 $i$ 的失配指针一定比 $i$ **深度更小**。

一般来说，我们使用 BFS 来求得失配指针。

我们设点 $i$ 的父亲为 $fa$ ，若 $fa$ 的失配指针有与 $i$ 相同的儿子 $j$  ，那么就使得 $i$ 的失配指针指向 $j$ 。

下面是求失配指针的代码：


```cpp
void getFail()
{
	for(int i = 0; i < 26; i++)
	{
		trie[0].son[i] = 1;
	}
	q.push(1);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		int Fail = trie[u].Fail;
		for(int i = 0; i < 26; i++)
		{
			int v = trie[u].son[i];
			if(!v)
			{
				trie[u].son[i] = trie[Fail].son[i];
				continue;
			}
			trie[v].Fail = trie[Fail].son[i];
			q.push(v);
		}
	}
}
```

### 拓扑排序优化&查询

对于多模式串匹配中，如果需要寻找字符串作为子串在另一个字符串中出现的次数，则需要 $O(nm)$ 的时间复杂度，在数据范围较大的情况下速度及其感人。

其实我们可以在找到的点里面打个标记，等到最后再上传并累计答案。由于我们打了标记后肯定是从**更深**的点开始更新的，所以我们可以使用拓扑排序确定更新顺序。


在找失配指针时要加上一句代码
```cpp
in[trie[v].Fail]++;
```
以确定入度的值。

而拓扑排序可以这么写：


```cpp
for(int i = 1; i <= cnt; i++)
	{
		if(in[i] == 0)
		{
			q.push(i);
		}
	}
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		ans[trie[u].f] = trie[u].ans;
		int v = trie[u].Fail;
		in[v]--;
		trie[v].ans += trie[u].ans;
		if(in[v] == 0)
		{
			q.push(v);
		}
	}
```

对于查询操作，我们原本的想法是暴力去跳指针，现在我们拥有了标记，反而更简单了：


```cpp
int u = 1, len = S.size();
for(int i = 0; i < len; i++)
{
  u = trie[u].son[S[i] - 'a'];
  trie[u].ans++;
}
```

使用拓扑排序优化后时间复杂度为 $O(n+m)$ 。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 6e5 + 1, M = 31;
string s, S;
int n, cnt = 1, ans[N], in[N], mp[N];
struct node
{
	int son[M], Fail, f, ans;
}trie[N];
class Queue
{
    public:
        int q[10000001], head = 0, tail = 0;
    void init()
	{
        tail = -1;
    }
    void push(int x)
	{
        q[++tail] = x;
    }
    void pop()
	{
        head++;
    }
    bool empty()
    {
    	if(tail - head + 1 == 0)
    	{
    		return 1;
		}
		else
		{
			return 0;
		}
	}
    int front()
	{
        return q[head];
    }
};
Queue q;
void insert(int x)
{
	int u = 1, len = s.size();
	for(int i = 0; i < len; i++)
	{
		int v = s[i] - 'a';
		if(!trie[u].son[v])
		{
			trie[u].son[v] = ++cnt;
		}
		u = trie[u].son[v];
	}
	if(!trie[u].f)
	{
		trie[u].f = x;
	}
	mp[x] = trie[u].f;
}
void getFail()
{
	for(int i = 0; i < 26; i++)
	{
		trie[0].son[i] = 1;
	}
	q.push(1);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		int Fail = trie[u].Fail;
		for(int i = 0; i < 26; i++)
		{
			int v = trie[u].son[i];
			if(!v)
			{
				trie[u].son[i] = trie[Fail].son[i];
				continue;
			}
			trie[v].Fail = trie[Fail].son[i];
			in[trie[v].Fail]++;
			q.push(v);
		}
	}
}
void qsort()
{
	for(int i = 1; i <= cnt; i++)
	{
		if(in[i] == 0)
		{
			q.push(i);
		}
	}
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		ans[trie[u].f] = trie[u].ans;
		int v = trie[u].Fail;
		in[v]--;
		trie[v].ans += trie[u].ans;
		if(in[v] == 0)
		{
			q.push(v);
		}
	}
}
void query()
{
	int u = 1, len = S.size();
	for(int i = 0; i < len; i++)
	{
		u = trie[u].son[S[i] - 'a'];
		trie[u].ans++;
	}
}
void solve()
{
	getFail();
	query();
	qsort();
}
int main()
{
	q.init();
	cin >> S >> n;
	cnt = 1;
	for(int i = 1; i <= n; i++)
	{
		cin >> s;
		insert(i);
	}
	solve();
	for(int i = 1; i <= n; i++)
	{
		cout << ans[mp[i]] << "\n";
	}
}
```

---

## 作者：caoshuchen (赞：0)

看了一下其他四位的题解。好像没有提到**后缀自动机**的做法。那我就来补充一下吧。

## 题意

 > 给定字符串 $S$，对每个 $i\in [1,m]$ 求 $T_i$ 在 $S$ 中出现的次数。
 
## 思路

首先，我们把 $S$ 的字符依次加进自动机里，然后我们记一个 $endpos$ 表示每个独特字串出现的次数。加字符时，我们在当前后缀的位置的 $endpos$ 增加 $1$ 即可。

所有字符串加好后，我们建立后缀链树，然后我们发现，如果一个串出现了一次，那么它的所有前缀都会出现一次。而我们只记录了所有后缀，那么所有后缀的前缀就恰好构成了所有子串。我们进行深度优先搜索，把 $endpos$ 求一个后缀和就行了。

最后访问的时候，从自动机空串状态开始，然后按照字符串依次更新当前状态，如果发现在此状态下，没有给定字符的边，则表明没有这样的字符串，返回 $0$ 即可。

## 代码

后缀自动机结构比较复杂，只可意会不可言传，所以还是看代码理解吧。

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;


struct SufNode {
    int e[26] = {};
    int lnk = 1, len = 0;
    int endpos = 0;
};
template <typename Node>
struct SufAuto {
	int cnt = 1, sz = 1, last = 1;
	vector<Node> a = vector<Node>(2);
	
	vector<int> e[2000005];
    int srh(int x) {
        for (int i = 0; i < e[x].size(); i++)
            a[x].endpos += srh(e[x][i]);
        return a[x].endpos;
    }
    void set_endpos() {
        for (int i = 2; i <= cnt; i++)
            e[a[i].lnk].push_back(i);
        srh(1);
    }
	
	int cd(char c) {
		return c - 'a';
	}
	int get_endpos(string &s) {
		int x = 1;
        for (auto i : s) {
        	if (a[x].e[cd(i)] == 0)
        		return 0;
        	else
        		x = a[x].e[cd(i)];
		}
		return a[x].endpos;
    }
	void add(char c) {
		int x = cd(c), p = last;
		a.push_back(Node()), a[last = ++cnt].len = ++sz;
		a[last].endpos = 1;
		while (a[p].e[x] == 0 && p != 1)
			a[p].e[x] = last, p = a[p].lnk;
		if (p == 1 && a[p].e[x] == 0)
			a[p].e[x] = last, a[last].lnk = p;
		else {
			int q = a[p].e[x];  
            if (a[q].len == a[p].len + 1)
                a[last].lnk = q;
            else {
                int q_new = ++cnt;
                a.push_back(a[q]), a[q_new].len = a[p].len + 1, a[q_new].endpos = 0;
                a[last].lnk = a[q].lnk = q_new;
                while (a[p].e[x] == q)
                    a[p].e[x] = q_new, p = a[p].lnk;
            }
		}
	}
};

SufAuto<SufNode> t;

string s;
int m;
int main()
{
    cin >> s >> m;
    for (int i = 0; i < s.size(); i++)
        t.add(s[i]);
    t.set_endpos();
    ll ans = 0;
    for (int i = 1; i <= m; i++) {
        cin >> s;
        cout << t.get_endpos(s) << endl;
    }
    return 0;
}
```

---

## 作者：L_zaa_L (赞：0)

后缀自动机板子题，不会后缀自动机的可以看看我的[学习笔记](https://zhuanlan.zhihu.com/p/665086302)。

关于求后缀自动机中某个节点中的元素出现了多少次，我们可以，先将每次加入后的节点出现次数设为一，然后一个节点 $i$ 的出现次数，是所有 $lnk_j=i$ 的点出现次数之和。

最后对于每个串，从初始节点开始在 SAM 上面走总能走到对应的节点（这个串肯定是属于这个节点的），直接输出出现次数即可。 

```cpp
int n;
char s[N];
int len[N],lnk[N],siz[N],cnt=1,last=1;
int ch[N][26];
inline void insert(int c){
	int cur=++cnt,p=last;last=cur;
	len[cur]=len[p]+1;
	while(p&&!ch[p][c]) ch[p][c]=cur,p=lnk[p];
	if(!p) lnk[cur]=1;
	else{
		int q=ch[p][c];
		if(len[p]+1==len[q]) lnk[cur]=q;
		else{
			int copy=++cnt;
			lnk[copy]=lnk[q];len[copy]=len[p]+1;
			For(i,0,25) ch[copy][i]=ch[q][i];
			lnk[q]=lnk[cur]=copy;
			while(ch[p][c]==q){
				ch[p][c]=copy;
				p=lnk[p];
			}
		}
	}
	siz[cur]=1;
}
int a[N],tag[N];
inline void work(){
	For(i,1,cnt) tag[len[i]]++;
	For(i,1,cnt) tag[i]+=tag[i-1];
	For(i,1,cnt) a[tag[len[i]]--]=i;
	Rof(i,cnt,1){
		siz[lnk[a[i]]]+=siz[a[i]];
	}
}
string t;
inline void solve(){
	scanf("%s",s+1);
	n=strlen(s+1);
	For(i,1,n) insert(s[i]-'a');
	work();
	int Q=read();
	while(Q--){
		cin>>t;
		int len=t.size();
		int p=1;
		For(i,0,len-1){
			int c=t[i]-'a';
			p=ch[p][c];
		}
		if(p==0) puts("0");
		else 
		printf("%lld\n",siz[p]);
	}
}
```

---

## 作者：Lele_Programmer (赞：0)

# AT_abc362_g 题解

## 思路

AC 自动机模板题，在 Trie 树上做 KMP，如果不会 Trie 的出门左转 [P8306](https://www.luogu.com.cn/problem/P8306)，如果不会 KMP 的出门右转 [P3375](https://www.luogu.com.cn/problem/P3375)。

本题与 AC 自动机模板题雷同，但还是把 AC 自动机的模板讲一讲吧。

用 KMP 进行字符串匹配的时候，遇到匹配失败的时候，就会根据失配指针跳到前面的某一个位置，AC 自动机也一样，只不过换成了在 Trie 上初始化失配指针，由 $a$ 指向 $b$ 的失配指针，就是由 $a$ 指向 $a$ 的最长后缀，当然，如果不存在，就指向根节点。

## 代码

首先是 Trie 树的插入操作。

```cpp
void insert(char str[],int idx) {
    int u=0;
    for (int i=0;str[i];++i) {
        int c=str[i]-'a';
        if (!tr[u][c]) tr[u][c]=++tot;
        u=tr[u][c];
    }
    if (!st[u]) st[u]=idx;
    to[idx]=st[u];
}
```

接下来是 AC 自动机的构造失配指针的操作：

```cpp
void build() {
    while (!q.empty()) q.pop();
    for (int i=0;i<=25;++i) {
        if (tr[0][i]) q.push(tr[0][i]);
    }
    while (!q.empty()) {
        int u=q.front(); q.pop();
        for (int i=0;i<=25;++i) {
            if (!tr[u][i]) tr[u][i]=tr[ne[u]][i];
            else {
                ne[tr[u][i]]=tr[ne[u]][i];
                in[tr[ne[u]][i]]++;
                q.push(tr[u][i]);
            }
        }
    }
}
```

这里解释一下上面的代码，采用广搜进行初始化，先把根节点所连接的节点插入队列，然后每一次取出队首，枚举所有情况（即 a 到 z 的 $26$ 个字母），如果当前这个节点不存在一条指向下一个字母的边，则需要根据失配指针跳回去，然后从那个点进行连边。当然，如果存在一条走向某一个字母的边，则直接走过去，然后更新一下下一个点的失配指针，即当前点的失配指针指向的同一个字母的点。

显然很绕，这里形式化地说一下，假设现在有一个点 $u$，它的下一个字母是 $k$，设 $g_{i,j}$ 为从 $i$ 这个点走向字母 $j$ 后所到达的点，用 $next_i$ 表示点 $i$ 的失配指针。如果 $g_{u,k}$ 不存在，则 $g_{u,k}=g_{next_u,k}$，如果存在，则 $next_{g_{u,k}}=g_{next_u,k}$。

如果你还不理解，那么直接举个例子说说，假设以当前点 $u$ 结束所形成的字符串是 $s$，它的下一个点将是 $v$，如果不存在一个从 $u$ 走向 $v$ 的点，那么，就从字符串 $s$ 的最长后缀结束的节点，向它这个节点走向的 $v$ 连边，有可能也不存在这条边，但是根据广搜的层序遍历，它前面的点都已经处理完了，也就是说如果这条边还不存在的话，它已经被初始为它自己对应的另外的失配指针了。

当然，为了防止超时，这里添加了拓扑排序优化，所以将入度计入 $in$ 数组。

其余拓扑排序的代码：

```cpp
void topu() {
    while (!q.empty()) q.pop();
    for (int i=1;i<=tot;++i) {
        if (!in[i]) q.push(i);
    }
    while (!q.empty()) {
        int u=q.front(); q.pop();
        ans[st[u]]=f[u];
        f[ne[u]]+=f[u];
        in[ne[u]]--;
        if (!in[ne[u]]) q.push(ne[u]);
    }
}
```

剩下的主函数：

```cpp
int main() {
    scanf("%s",S);
    scanf("%d",&n);
    for (int i=1;i<=n;++i) {
        scanf("%s",str);
        insert(str,i);
    }
    build();
    for (int i=0,j=0;S[i];++i) {
        int c=S[i]-'a';
        j=tr[j][c];
        f[j]++;
    }
    topu();
    for (int i=1;i<=n;++i) {
        printf("%d\n",ans[to[i]]);
    }
    return 0;
}
```

## 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=500005;
const int M=2000005;
const int K=35;

int n;
int tr[N][K],tot;
int ne[N];
char S[M];
char str[N];
int st[N];
int to[N];
queue<int> q;
int in[N];
int f[N];
int ans[N];

void insert(char str[],int idx) {
    int u=0;
    for (int i=0;str[i];++i) {
        int c=str[i]-'a';
        if (!tr[u][c]) tr[u][c]=++tot;
        u=tr[u][c];
    }
    if (!st[u]) st[u]=idx;
    to[idx]=st[u];
}

void build() {
    while (!q.empty()) q.pop();
    for (int i=0;i<=25;++i) {
        if (tr[0][i]) q.push(tr[0][i]);
    }
    while (!q.empty()) {
        int u=q.front(); q.pop();
        for (int i=0;i<=25;++i) {
            if (!tr[u][i]) tr[u][i]=tr[ne[u]][i];
            else {
                ne[tr[u][i]]=tr[ne[u]][i];
                in[tr[ne[u]][i]]++;
                q.push(tr[u][i]);
            }
        }
    }
}

void topu() {
    while (!q.empty()) q.pop();
    for (int i=1;i<=tot;++i) {
        if (!in[i]) q.push(i);
    }
    while (!q.empty()) {
        int u=q.front(); q.pop();
        ans[st[u]]=f[u];
        f[ne[u]]+=f[u];
        in[ne[u]]--;
        if (!in[ne[u]]) q.push(ne[u]);
    }
}

int main() {
    scanf("%s",S);
    scanf("%d",&n);
    for (int i=1;i<=n;++i) {
        scanf("%s",str);
        insert(str,i);
    }
    build();
    for (int i=0,j=0;S[i];++i) {
        int c=S[i]-'a';
        j=tr[j][c];
        f[j]++;
    }
    topu();
    for (int i=1;i<=n;++i) {
        printf("%d\n",ans[to[i]]);
    }
    return 0;
}
```

在这里再补充几句，防止字符串 $T$ 出现重复，在构建字典树的时候利用 $st$ 数组和 $to$ 数组进行配合。

---

## 作者：N_Position (赞：0)

## AT_abc362_g
### 前置知识
- KMP 算法；
- 字典树。
### 分析
显然本题为 AC 自动机的模板题，所以本题解只讲解 AC 自动机的原理。
### AC 自动机
AC 自动机与 KMP 类似，不同的是，AC 自动机是在字典树上的。

我们先将所有的字符串 $T_i$ 加入到字典树中（我这里默认你会这个操作，不会的建议先去学习字典树）。

与 KMP 中的 nxt 数组类似的，AC 自动机中有 fail 指针，即失配指针，作为匹配失败时的跳转指针。AC 自动机的失配指针指向当前状态的最长后缀状态即可。

fail 指针的构建方法如下，我们可以直接对照代码理解，其中 `ch` 数组为字典树，`in` 数组为入度，在接下来的优化中会用到：
```cpp
void build(){
	for(int i=0;i<26;i++){
		if(ch[0][i]){
			q.push(ch[0][i]);
		}
	}
	while(!q.empty()){
		int x = q.front();
		q.pop();
		for(int i=0;i<26;i++){
			if(ch[x][i]){
				q.push(ch[x][i]);
				fail[ch[x][i]] = ch[fail[x]][i];//关键
				in[ch[fail[x]][i]] ++;
			}else{
				ch[x][i] = ch[fail[x]][i];//关键
			}
		}
	}
}
```

这样，fail 指针构建好后，便可以在 $O(|S|)$ 求得每一个字符串 $T_i$ 是否出现，这对应着 [P3808](https://www.luogu.com.cn/problem/P3808)。你可以先去做这个题。

然后再利用拓扑序优化：
```cpp
void topu(){
	for(int i=1;i<=tot;i++){
		if(in[i] == 0){
			q.push(i);
		}
	}
	while(!q.empty()){
		int x = q.front();
		q.pop();
		vis[flag[x]] = ans[x];
		int y = fail[x];
		ans[y] += ans[x];
		in[y] --;
		if(in[y] == 0){
			q.push(y);
		}
	}
}
```
即可在 $O(|S|+\sum|T_i|)$ 的时间复杂度内通过本题。

[完整代码](https://atcoder.jp/contests/abc362/tasks/abc362_g)

---

