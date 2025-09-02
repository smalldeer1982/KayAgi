# [USACO23JAN] Find and Replace G

## 题目描述

你有一个字符串 $S$，最开始里面只有一个字符 $\text{a}$，之后你要对这个字符串进行若干次操作，每次将其中每一个字符 $c$ 替换成某个字符串 $s$（例如对于字符串 $\text{ball}$，将其中的 $\text{l}$ 替换为 $\text{na}$ 后将会变为 $\text{banana}$）。现在给定 $l,r$，你需要输出 $S_{l\ldots r}$（也就是 $S$ 的第 $l$ 个字符到第 $r$ 个字符对应的子串）是什么。

## 说明/提示

$l,r\le\min(\left | S \right |,10^{18})$；

$r-l+1\le2\times10^5$；

$\sum\left | s \right | \le 2\times 10^5$。

所有的字符串都只包含小写字母 $\text{a}-\text{z}$。

其中对于测试点 $2-7$，满足：

$r-l+1\le2000$，$\sum\left | s \right | \le 2000$。

## 样例 #1

### 输入

```
3 8 4
a ab
a bc
c de
b bbb```

### 输出

```
bdebbb```

# 题解

## 作者：OMG_wc (赞：21)

从后往前考虑每次替换，同时用 $26$ 棵二叉树，来维护当前每个字符  $c$ 最终形成的字符串。

在建树的时候，同样的子树不用再复制一份，而是直接建边，这样虽然总点数**可能**高达 $2^{114514}$ 次，实际建的边却只是 $O(\sum|s|)$ 条。

具体来说，当前考虑的是第 $[k,n]$ 轮替换后的结果，第 $k$ 轮替换规则为 $c_k \rightarrow s_k$。对字符串 $s_k$ 的每个字符在 $[k+1,n]$ 轮替换后的结果按从左到右的顺序两两合并，然后合并后的二叉树作为字符 $c_k$ 当前的结果。合并时保证所有非叶结点都有两个孩子，最终字符都存在于叶结点上。

结点信息要维护树的大小，为防止溢出不要超过 $10^{18}$。

因为是二叉树，可以像线段树这样查询：途径的结点中是 $[l,r]$  内部的点有 $O(r-l)$ 个，其他包含一部分的途径点只在每层的两端出现，这样每层只有常数个这样的点，而树高是 $O(n)$ 的，所以总的途经点是 $O(n+r-l)$ 级别的。

总时间复杂度 $O(r-l+\sum|s|)$，代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL INF = 1e18;
const int N = 200105;

struct Node {
    char v;
    int lc, rc;
    LL sz;
} tr[N];
int root[26], ck;
char c[N];
string s[N];
void query(int u, LL l, LL r) {
    if (r <= 0 || l > tr[u].sz) return;
    if (tr[u].v == '#') {
        query(tr[u].lc, l, r);
        query(tr[u].rc, l - tr[tr[u].lc].sz, r - tr[tr[u].lc].sz);
    } else {
        putchar(tr[u].v);
    }
}
int main() {
    LL l, r, n;
    cin >> l >> r >> n;
    for (int i = 1; i <= n; i++) cin >> c[i] >> s[i];
    for (int i = 0; i < 26; i++) {
        tr[++ck] = {char('a' + i), 0, 0, 1};
        root[i] = ck;
    }
    for (int i = n; i >= 1; i--) {
        int now = 0;
        for (auto x : s[i]) {
            x -= 'a';
            if (now == 0)
                now = root[x];
            else {
                tr[++ck] = {'#', now, root[x], min(INF, tr[now].sz + tr[root[x]].sz)};
                now = ck;
            }
        }
        root[c[i] - 'a'] = now;
    }
    query(root[0], l, r);
    putchar('\n');
    return 0;
}
```



---

## 作者：Creeper_l (赞：7)

可以把从每个字符开始的操作过程看成是一棵树，对于每一个字符我们都维护一颗树（表示从这个字符开始操作的过程）。因为后面的操作会覆盖掉前面的，所以我们考虑从最后面的操作开始往上建树。首先 $a-z$ 都指向自己（因为自己如果不变的话值还是自己），对于每一次操作 $(x,s)$。我们可以依次合并 $s_{i-1},s_i$。合并的过程为：建立一个新点（这个点不代表一个字符，可以设为任意字符），左儿子是 $s_{i-1}$ 这个字符所表示的树，左儿子是 $s_{i}$ 这个字符所表示的树。一直合并到 $s_n$ 为止。最后将字符 $x$ 所代表的树变为这颗合并完的树。

考虑如何查询答案，我们可以用类似于线段树的方式。对于每一个节点记录一个 $size$ 表示这个子树内有多少个字符。然后通过 $size$ 和 $l,r$ 的大小关系判断应该遍历左区间还是右区间即可。

时间复杂度：因为 $\sum s \le 200000$，所以建树的时间复杂度是 $O(n)$ 的。又因为这是一颗二叉树，且最后查询的区间大小（叶子节点个数）是 $r-l+1=O(n)$ 的，所以查询的时间复杂度也是 $O(n)$ 的，总时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 8e5 + 10;
const int inf = 1000000000000000000;
int l,r,q,root[MAXN],tot;
char a[MAXN],x;
string b[MAXN],s;
struct Node{int ls,rs,size;char c;}tree[MAXN]; 
inline void solve(int id,int l,int r)
{
	if(r <= 0 || l > tree[id].size) return;
	if(tree[id].c == '#') 
	{
		solve(tree[id].ls,l,r);
		solve(tree[id].rs,l - tree[tree[id].ls].size,r - tree[tree[id].ls].size);	
	}
	else cout << tree[id].c;
}
signed main()
{
	cin >> l >> r >> q;
	for(int i = 0;i < 26;i++) tree[i] = {i,i,1,char(i + 'a')},root[i] = i;
	tot = 25;
	for(int i = 1;i <= q;i++) cin >> a[i] >> b[i];
	for(int i = q;i >= 1;i--)
	{
		x = a[i],s = b[i];
		int p = root[s[0] - 'a'];
		for(int i = 1;i < s.length();i++)
		{
			int F = s[i] - 'a';
			tree[++tot] = {p,root[F],min(inf,tree[p].size + tree[root[F]].size),'#'}; 
			p = tot;
		}
		root[x - 'a'] = p; 
	}
	solve(root[0],l,r);
	return 0;
}

```


---

## 作者：Rushroom (赞：7)

# 题意
有一个字符串 $S$，初始为单个字符 $a$。有 $n$ 次操作，每次给定字符 $c$ 和字符串 $s$，将 $S$ 中所有 $c$ 替换为 $s$。操作结束后给定 $l$，$r$，询问  $S_{l\dots r}$。

$\sum \lvert s \rvert \le 2\cdot 10^5$, $r-l+1\le 2\cdot 10^5$。


# 题解
设 $f_{i,j}$ 表示字符 $i$ 经过操作 $j,j+1\dots n$ 后会变为多少个字符。则可以根据 $f$ 的值 DFS（类似线段树查询，一层层拆分区间，$f$ 的值即为区间大小）。

这样会遇到一个问题：如果存在大量 $\lvert s \rvert =1$，即一个字符变为一个字符，那么 DFS 中操作次数可能达到 $O(n^2)$ 次。对此，可以预处理出字符 $i$ 在操作 $j$ 后第一个 $\lvert s \rvert >1$ 的操作 $nxt_{i,j}$，以及在操作 $nxt_{i,j}$ 时字符 $i$ 变成了字符 $to_{i,j}$。这样可以快速跳转至下一个增加 $S$ 长度的操作。

由于每次有效操作都会将 $S$ 长度至少 $+1$，而 $r-l+1\le 2\cdot 10^5$，所以需要处理的操作也不会超过这个数。

# Code

```cpp
char c[N];
string s[N];
ll dp[26][N], nxt[26][N], to[26][N];
ll L, R, n;
void dfs(ll x, ll d, ll p, ll l, ll r) {
    // cout << x << ' ' << d << endl;
    if (d == n) {
        cout << char('a' + x);
        return;
    }
    rep(i, s[d].size()) {
        int y = s[d][i] - 'a';
        ll w = dp[y][d + 1];
        if (p <= r && p + w - 1 >= l)dfs(to[y][d + 1], nxt[y][d + 1], p, max(p, l), min(p + w - 1, r));
        p += w;
        if (p > r)break;
    }
}
void solve() {
    cin >> L >> R >> n;
    rep(i, n)cin >> c[i] >> s[i];
    rep(i, 26)dp[i][n] = 1, nxt[i][n] = n, to[i][n] = i;
    for (int j = n - 1;j >= 0;--j) rep(i, 26) {
        if (c[j] - 'a' != i) {
            dp[i][j] = dp[i][j + 1];
            nxt[i][j] = nxt[i][j + 1];
            to[i][j] = to[i][j + 1];
        }
        else if (s[j].size() == 1) {
            dp[i][j] = dp[s[j][0] - 'a'][j + 1];
            nxt[i][j] = nxt[s[j][0] - 'a'][j + 1];
            to[i][j] = to[s[j][0] - 'a'][j + 1];
        }
        else {
            dp[i][j] = 0, nxt[i][j] = j, to[i][j] = i;
            rep(k, s[j].size()) {
                dp[i][j] += dp[s[j][k] - 'a'][j + 1];
                dp[i][j] = min(dp[i][j], (ll)MAXN * MAXN);
            }
        }
    }
    dfs(0, 0, 1, L, R);
}
```

---

## 作者：hh__hh (赞：3)

个人思路：从后往前做，每次修改，替换前一个修改里面的字母，显然是错的，因为没替换更前面的字母。

~~然后就想不出来了。~~

-----------------------------------------------------

正片开始：

第 $i$ 次修改 $c,s$，相当于 $c$ 被替换成 $s$ 中每个字母在 $\left[i+1,n \right]$ 次操作后对应的字符串之和。

于是我们从后往前做，对于每个字母建一个二叉树用来计算每个字母变成的字符串。

具体而言，我们先建立一些节点表示 字母 $a \sim z$，然后对于每个字母建立一个指针，表示这个字母被替换为指向节点的子树内所有字母，显然，在没有修改时，每个字母指向它本身对应的节点。

从后往前做，每次修改 $c,s$，从左到右遍历 $s$ 中每一个字母：

1. 对于前两个字母，新建一个节点，两个儿子指向这两个字母的指针指向的节点。

2. 对于剩余字母，每个字母新建一个节点，左儿子指向上一个新建节点，右儿子指向当前字母。

每个结点记录一下子树内的字母数，以供查询，记得对 $10^{18}$ 次方取  $\text{min}$。

遍历完成后，$c$ 的指针指向新建的节点。

因为对于一个字符串 $s$，新建节点数为 $\left | n \right | - 1 $，所以总共新建节点数 $<\left | s \right | \le 2 \times 10^{5}$。

查询时，我们从 $a$ 指向的节点开始查询。

当我们遍历到一个节点时，其左儿子子树内的字母数为 $\text{cnt}$：

1. 当 $\text{cnt} > r$，查询左儿子 $\left[l,r \right]$。

2. 当 $\text{cnt} \le l$，查询右儿子 $\left[l-cnt,r-cnt \right]$。

3. 否则先查询左儿子 $\left[l,cnt \right]$，再查询右儿子 $\left[1,r-cnt  \right]$。

---

## 作者：违规用户名720023 (赞：2)

# P9016 [USACO23JAN] Find and Replace G

原题很清晰，直接进入分析。

## 题目分析

看到一个东西向另一个东西对应，很容易想到建图。

我们从字符串 $s$ 里面的每一个字符向字符 $c$ 连边。这里我们建一个虚点，向每一个当前没有入度的字符为 $c$ 的点连边（可以使用一个 `vector` 记录此类点的编号，使用一个数组记录每个点对应的字符用于输出答案），然后再把所有字符串中的字符 `s[i]` 向这个点连边。

建完图后，我们在这个图上跑拓扑排序，同时使用一个数组记录每个字符最后转化成几个字符。

最后我们进行类似线段树区间查询的一个操作，详见代码。

但这样是过不了的，于是我们进行优化。注意到图中有很多链式结构，我们考虑将其使用类似并查集的操作，缩成一条边。详见下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/oqk1477u.png)

## Code

```cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <cstring>
#include <cstdio>
#define int long long
#define rd() read128()
#define pr(a) print128(a)
#define pc(b) putchar(b)
#define pel(c) pr(c), pc('\n')
#define psp(d) pr(d), pc(' ')
using namespace std;
int read128()
{
	int ttpttp = 0, flgflg = 1;
	char chrchr = getchar();
	if(chrchr == '-') flgflg = -1;
	while((chrchr < '0' || chrchr > '9') && chrchr != '-') chrchr = getchar();
	if(chrchr == '-') flgflg = -1, chrchr = getchar();
	while(chrchr >= '0' && chrchr <= '9') ttpttp = ttpttp * 10 + chrchr - '0', chrchr = getchar();
	return ttpttp * flgflg;
}
void print128(int ttpttp)
{
	char char_inserted_list[38];
	if(ttpttp < 0) putchar('-'), ttpttp *= -1;
	int iiiiii = 0;
	while(ttpttp > 0)
	{
		char_inserted_list[++iiiiii] = (char)(ttpttp % 10 + '0');
		ttpttp /= 10;
	}
    if(iiiiii == 0) putchar('0');
    else
    {
    	for(int i = iiiiii; i >= 1; i--) putchar(char_inserted_list[i]);
	}
}// 快读
vector<int> cnt[26];
vector<int> a[1000010];
vector<int> bb[1000010];
char mp[1000010];// 字符表
int cur, l, r, n;
int dp[1000010];// 记录转化
int lst[1000010];
int ind[1000010];
void dfs(int p, __int128 sm)
{
	//psp(p), psp(sm), pel(dp[p]);
	if(dp[p] == 1)// 找到 dp[i] = 1 即返回
	{
		pc(mp[p]);
		return;
	}
	__int128 ssm = sm;
	for(int i = 0; i < bb[p].size(); i++)
	{
		if(dp[bb[p][i]] == 2e18 && ssm < r) //此时这部分一定包含答案且后面没有包含答案的部分，自证不难
		{
			dfs(bb[p][i], ssm);
			break;
		}
		if((ssm < l && ssm + dp[bb[p][i]] >= l) || (ssm >= l && ssm < r))
			dfs(bb[p][i], ssm);
		ssm += dp[bb[p][i]];
	}
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> l >> r >> n;
	cnt[0].push_back(1);
	mp[1] = 'a';
	cur = 1;
	for(int i = 1; i <= n; i++)
	{
		char b;
		cin >> b;
		string s;
		cin >> s;
		if(cnt[b - 'a'].empty()) continue;
		int p;
		if(cnt[b - 'a'].size() > 1)// 建图
		{
			cur++;
			mp[cur] = b;
			for(int j = 0; j < cnt[b - 'a'].size(); j++)
				a[cur].push_back(cnt[b - 'a'][j]), ind[cnt[b - 'a'][j]]++;
			p = cur;
		}
		else p = cnt[b - 'a'][0];
		cnt[b - 'a'].clear();
		for(int j = 0; j < s.size(); j++)
		{
			a[++cur].push_back(p);
			mp[cur] = (char)s[j];
			ind[p]++;
			cnt[s[j] - 'a'].push_back(cur);
		}
	}
	queue<int> q;
	for(int i = 1; i <= cur; i++) if(ind[i] == 0) q.push(i), dp[i] = 1, lst[i] = i;
	while(!q.empty())// 拓扑
	{
		int t = q.front();
		q.pop();
		if(dp[t] == 1) mp[t] = mp[lst[t]];// 上传字符
        // lst 记录它下面一个点的编号
		for(int i = 0; i < a[t].size(); i++)
		{
			ind[a[t][i]]--;
			dp[a[t][i]] += dp[t];
			lst[a[t][i]] = t;
			if(dp[a[t][i]] > 1e18) dp[a[t][i]] = 2e18;
            // 这里使用这个操作避免出现__int128减少常数
			if(ind[a[t][i]] == 0) q.push(a[t][i]);
		}
	};
	for(int i = 1; i <= cur; i++)
		for(int j = 0; j < a[i].size(); j++)
			bb[a[i][j]].push_back(i);
	dfs(1, 0);
	return 0;
}
```

## 后记

感谢[wangzhilin_lg](https://www.luogu.com.cn/user/814556)大佬提供的指点。

有人说这个算法复杂度是假的，如果已经有 hack，请 hack 掉我并且在此题讨论版中 at 我。

另：我的做法没有完全优化，过一段时间会写一版完全优化的版本，请在那之后 hack 或者 hack 使用我的想法的人。

---

## 作者：Cxny (赞：2)

初始有一个字符串 s="a"。接下来 $n$ 次操作，每次操作形如将字符串中所有字符 $c$ 替换为字符串 $s$。

最后输出 $[l,r]$ 对应的子串。$n,r-l\le2\times10^5,\ \ l\le r\le10^{18}$。

---

最简单的想法是先 dp 出每个字符在后 $i$ 次操作后会变成几个字符，处理时丢弃区间外的。但很容易被卡到 $O(n\cdot len)$。

考虑构建一棵类似于线段树的树，第 $i$ 层形成了第 $i$ 次操作前的字符串，并向下一层中它所对应的若干字符连边。

与线段树的相似之处在于，每个节点对应最终序列的一段区间。不同之处在于每个节点可以有 $1$ 个或者多个儿子。

对于查询操作，受到普通线段树区间查询的启发，可以对包含在询问区间内的直接输出，不完全包含的递归下去。整棵树深度为 $n+1$，两侧递归复杂度不超过 $O(n+\sum|s|)$。

输出部分总长度不超过 $r-l+1$，但非叶节点数量可能很大。

但是，如果每个节点都有至少两个子节点，则非叶节点数量不会超过 $r-l$。而只有一个子节点所对应的操作一定形如 某个字符 $\to$ 某个字符，大可以预处理每个节点最终会变成什么字符。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define int long long
const int maxn = 2e5 + 10;
struct Option{
    int c; string s;
}q[maxn];
int n, dp[26][maxn], tar[26][maxn], td[26][maxn], nxt[26][maxn];
string s = "a";
vector<int> pos[26];
void print(int p, int dep){
    if(dep > n) return putchar(p + 'a'), void();
    if(td[p][dep] != dep) return print(tar[p][dep], td[p][dep]);
    if(nxt[p][dep] != dep) return print(p, nxt[p][dep]);
    assert(q[dep].c == p);
    for(auto j : q[dep].s) print(j - 'a', dep + 1);
}
void solve(int l, int r, int p, int ql, int qr, int dep){
    if(ql > qr || r < ql || qr < l) return;
    if(dep > n || (ql <= l && r <= qr)) return print(p, dep);
    if(td[p][dep] != dep) return solve(l, r, tar[p][dep], ql, qr, td[p][dep]);
    if(nxt[p][dep] != dep) return solve(l, r, p, ql, qr, nxt[p][dep]);
    int sum = l - 1;
    assert(q[dep].c == p);
    for(auto j : q[dep].s) solve(sum + 1, sum + dp[j - 'a'][dep + 1], j - 'a', ql, qr, dep + 1), sum += dp[j - 'a'][dep + 1], sum = min(sum, (int)1e18 + 1);
}
int l, r;
signed main(){
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> l >> r >> n;
    for(int i = 1; i <= n; i++){
        string c; cin >> c >> q[i].s;
        q[i].c = c[0] - 'a';
    }
    for(int i = 0; i < 26; i++) dp[i][n + 1] = 1, tar[i][n + 1] = i, nxt[i][n + 1] = td[i][n + 1] = n + 1;
    for(int i = n; i >= 1; i--){
        for(int j = 0; j < 26; j++) dp[j][i] = dp[j][i + 1];
        dp[q[i].c][i] = 0;
        for(auto j : q[i].s) dp[q[i].c][i] += dp[j - 'a'][i + 1], dp[q[i].c][i] = min(dp[q[i].c][i], (int)1e18 + 1);
        for(int j = 0; j < 26; j++) tar[j][i] = tar[j][i + 1], td[j][i] = td[j][i + 1], nxt[j][i] = nxt[j][i + 1];
        if(q[i].s.size() == 1){
            tar[q[i].c][i] = tar[q[i].s[0] - 'a'][i + 1];
            td[q[i].c][i] = td[q[i].s[0] - 'a'][i + 1];
        }else tar[q[i].c][i] = q[i].c, td[q[i].c][i] = i, nxt[q[i].c][i] = i;
    }
    solve(1, dp[0][1], 0, l, r, 1);
    return 0;
}
```

---

## 作者：MCRS_lizi (赞：2)

思维上难度还行，代码细节比较恶心（

[题目意思](https://www.luogu.com.cn/paste/ztz77lf5)

## 题目分析
暴力是不可能的，所以我们要考虑怎么去优化。

很显然，整个字符串的替换过程会构成一棵字符树，要准确定位到要求的子串，我们只需处理每一层某个字符对应转换后的字符串大小，然后 $\text{dfs}$ 输出答案即可。

~~好的题解写完了。~~

怎么可能！

说说简单写起来很恶心，况且这样做有一个很大的问题。原本 $O(\sum{|s|})$ 级别的算法，可能会由于反复将一个字符替换为另一个字符，而在树中形成一条长链，$\text{dfs}$ 的过程中会反复遍历这条长链而导致复杂度退化为 $O((\sum{|s|})^2)$。

所以，我们可以使出一个大法宝——并查集来进行路径压缩。考虑到我个人特殊的记录信息的方式，所有的并查集以及信息处理都是二维的。

下面就是~~你们最喜欢的~~代码啦~

## CODE

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200010,L=1e18;
int l,r,n,sz[30][N],num[30][N],len[30],slen[30],m[N],fa[30][N],fb[30][N];
bool flag=0;
string s[N];
char c[N];
vector<int> lev[N];
inline pair<int,int> find(int x,int y)
{
	if(fa[x][y]==x&&fb[x][y]==y)
	{
		return make_pair(x,y);
	}
	pair<int,int> res=find(fa[x][y],fb[x][y]);
	fa[x][y]=res.first,fb[x][y]=res.second;
	return res;
}
inline void merge(int x1,int y1,int x2,int y2)
{
	pair<int,int>res1=find(x1,y1),res2=find(x2,y2);
	if(res1.first==res2.first&&res1.second==res2.second)
	{
		return;
	}
	fa[res1.first][res1.second]=res2.first;
	fb[res1.first][res1.second]=res2.second;
}
inline void dfs(int x,int sum,int xh)
{
	if(!xh)
	{
		putchar(x+'a');
		return;
	}
	int op=num[x][xh];
	if(m[op]==1)
	{
		merge(x,xh,s[op][0]-'a',lev[op][0]);
		pair<int,int>res=find(x,xh);
		dfs(res.first,sum,res.second);
		return;
	}
	for(int i=0;i<m[op];i++)
	{
		if(sum+sz[s[op][i]-'a'][lev[op][i]]>=l||sz[s[op][i]-'a'][lev[op][i]]==-1)
		{
			dfs(s[op][i]-'a',sum,lev[op][i]);
			if(sum+sz[s[op][i]-'a'][lev[op][i]]>=r||sz[s[op][i]-'a'][lev[op][i]]==-1)return;
		}
		sum+=sz[s[op][i]-'a'][lev[op][i]];
	}
}
signed main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	cin>>l>>r>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>c[i]>>s[i];
	}
	for(int i=0;i<26;i++)
	{
      		fa[i][0]=i;
		sz[i][0]=1;
	}
	for(int i=n;i;i--)
	{
		int lens=s[i].size(),lenc=len[c[i]-'a']+1;
		m[i]=lens;
		num[c[i]-'a'][lenc]=i;
		fa[c[i]-'a'][lenc]=c[i]-'a';
		fb[c[i]-'a'][lenc]=lenc;
		for(int j=0;j<lens;j++)
		{
			sz[c[i]-'a'][lenc]+=sz[s[i][j]-'a'][len[s[i][j]-'a']];
			lev[i].push_back(len[s[i][j]-'a']);
			if(sz[c[i]-'a'][lenc]>L||sz[s[i][j]-'a'][len[s[i][j]-'a']]==-1)
			{
				sz[c[i]-'a'][lenc]=-1;
				break;
			}
		}
		len[c[i]-'a']++;
	}
	dfs(0,0,len[0]);
 	return 0;
}

```


---

## 作者：reinforest (赞：1)

这种方法**不保证复杂度正确**，正解请移步第一篇题解。

对于这种有复杂关系的题目，我们当然想到用图啦！

对于每次询问，记 $p$ 为替换前的字符，记 $len$ 为字符串的长度，对于字符串的每一个字符 $c_i$，都新建一个点，并从 $p$ 所代表的点向 $c_i$ 所代表的点连一条有向边；并且找到在 $p$ 后第一个与 $c_i$ 相等的（替换前的）字符 $p_j$，并从 $c_i$ 所代表的点向 $p_j$ 所代表的点连一条有向边。

这样就形成了一个有向无环图，令 $S_i$ 表示点 $i$ 所代表的字符最后会变成的字符个数。

我们可以在反图上操作，明显度数为 $0$ 的点 $S_i = 1$，度数不为 $0$ 的点的 $S_i=\sum S_v$，其中 $v$ 是经过一条边能够到达点 $i$ 的点。

因此我们可以用拓扑排序计算 $S_i$。在实际操作上，因为 $S_i$ 会很大，所以应该与至少 $10^{18}$ 的数取最小值。

计算出 $S_i$ 以后，我们可以在正图使用类似线段树的方式输出答案。

但是这可能被卡成 $O(n^2)$，因此我们需要优化。

我们充分发扬人类智慧，可以发现，在图上有很多条边 $(u,v)$ 满足 $S_u=S_v$，因此如果存在这样的边，可以开开心心地跳过这条边。

具体地，如果 $S_{u_0}=S_{u_1}=S_{u_2}= \cdots =S_{u_n} $，可以删除边 $(u_0,u_1),(u_1,u_2),\cdots,(u_{n-1},u_n)$，并添加边 $(u_0,u_n)$。

这样做跑得飞快，$2\times 10^5$ 的数据都可以最多用 `236.88MB` 在 `212ms` 内卡过。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll LL,RR,q,pcnt;
const ll maxn=2e5+5;
string req[maxn];
char optt[maxn];
vector<ll> G[maxn<<4],fG[maxn<<4];
struct point{
	char ch;
	ll id,nxt;
}pp[maxn<<4];
ll du[maxn<<4],siz[maxn<<4],cur[27][maxn],lent[27];
queue<ll> qu;
void tuo(){//拓扑排序
	for(int i=1;i<=pcnt;i++){
		if(du[i]==0){
			siz[i]=1;
			qu.push(i);
		}
	}
	while(!qu.empty()){
		ll fa=qu.front();
		qu.pop();
		for(auto v:fG[fa]){
			siz[v]=min(2000000000000000000ll,siz[fa]+siz[v]);
			du[v]--;
			if(du[v]==0)qu.push(v);
		}
	}
}
bool vis[maxn<<2];
void push_up(ll u){//删边
	vis[u]=true;
	pp[u].nxt=u;
	for(auto v:G[u]){
		if(!vis[v]){
			vis[v]=true;
			push_up(v);
		}
		if(siz[u]==siz[v]){
			if(siz[v]==2000000000000000000ll)break;
			//用 nxt 表示在 v 下且第一个与 S_v 不相等的点
			//这样就可以删边了
			pp[u].nxt=pp[v].nxt;
		}
	}
	
}
void out(ll L,ll R,ll l,ll r,ll u){
	//用线段树的方式查询
	ll sum=0,vl=-1,vr=-1;
	if(r<l)return;
	for(auto v:G[u]){
		vl=l+sum;
		vr=min(2000000000000000000ll,l+sum+siz[v]-1);
		if((L<=vl && vl<=R)||(L<=vr && vr<=R)||(vl<=L && vr>=R)){//如果线段有包含
			out(L,R,vl,vr,pp[v].nxt);//nxt的作用在这里
		}
		sum+=siz[v];
		if(vr==2000000000000000000ll)break;
		if(vl>RR)break;
	}
	if(vl==-1 && vr==-1 && L<=l && r<=R){
		printf("%c",pp[u].ch);
		return;		
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>LL>>RR>>q;
	for(int i=1;i<=q;i++){
		cin>>optt[i]>>req[i];
		cur[optt[i]-'a'][++lent[optt[i]-'a']]=i;
		pp[++pcnt]={optt[i],pcnt};
	}
	for(int i=1;i<=q;i++){
		ll len=req[i].length();
		for(int j=0;j<len;j++){//建图
			if(req[i][j]<'a' || req[i][j]>'z')continue;
			pp[++pcnt]={req[i][j],pcnt};
			G[i].push_back(pcnt);
			fG[pcnt].push_back(i);
			du[i]++;
			//用 upper_bound 找到第一个与 c_i 相等的（替换前的）字符 p_j
			//用 cur 存替换前与 c_i 相等的字符下标。
			ll up=upper_bound(cur[req[i][j]-'a']+1,cur[req[i][j]-'a']+lent[req[i][j]-'a']+1,i)-cur[req[i][j]-'a'];
			if(up==lent[req[i][j]-'a']+1)continue;
			G[pcnt].push_back(cur[req[i][j]-'a'][up]);
			fG[cur[req[i][j]-'a'][up]].push_back(pcnt);
			du[pcnt]++;
		}
	}
	tuo();
	push_up(1);
	out(LL,RR,1,siz[1],1);
	return 0;
}
```

---

## 作者：wind_seeker (赞：1)

~~讲一个比较烦的做法~~

### 思路
考虑到每一次操作后改变后的字符，也会被后面的操作而改变，既然我们可以预知其被改变成什么样子，不如直接记录，对其进行连边。  

例如：
```
a ab
a abc

```
对于这两个操作，第二个操作会更改第一个操作中改完后的 $a$，我们就连一条边为 $a\rightarrow abc$。

连边的过程中，我们将 $size$ 由儿子向付清传递，$sz_{i,j}$ 即表示第 $i$ 次操作中，第 $j$ 个字符在经过后面所有更新后会变为长度为 $sz_{i,j}$ 大小的字符串。

最后我们只需要根据 $l,r$ 以及 $sz$ 搜索一遍，按顺序找到不能再更新的满足在范围内的字符，并输出即可。

然而，这样子，最坏复杂度是 $O(|s|\times (R-L+1))$ 的，所以我们需要对一些好记录的情况进行记忆化，就可以~~卡过去了~~。

### code
```cpp
/* let life be like summer flowers	*/
/* by wind_seeker					*/
/* 2023-03-11 08:49	*/
#include<bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N=2e5+1e3,Max=1e18;

int L,R,M;
int lst[30],size[N];
char ch[N];
string s[N];
vector<int> nxt[N],sz[N];

int read(){
	int res=0,f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) res=(res<<1)+(res<<3)+(c^48);
	return res*f;
}

char mre[N];
char dfs(int x,int y,int l,int r){
	if(mre[x]&&s[x].size()==1&&sz[x][0]==1) return printf("%c",mre[x]),mre[x];
	int tar=nxt[x][y];
	if(tar==-1) return printf("%c",s[x][y]),s[x][y];
	int len=s[tar].size();char res;
	for(int i=0;i<len;i++){
		if(sz[tar][i]<l) l-=sz[tar][i],r-=sz[tar][i];
		else if(sz[tar][i]>=r){
			res=dfs(tar,i,l,r);
			break;
		}
		else res=dfs(tar,i,l,sz[tar][i]),l=0,r-=sz[tar][i];
	}
	if(s[x].size()==1&&sz[x][0]==1) mre[x]=res;
	return res;
}

signed main(){
	L=read(),R=read(),M=read();
	for(int i=1;i<=M;i++) cin>>ch[i]>>s[i];
	size[M]=s[M].size();
	for(int i=0;i<size[M];i++) nxt[M].pb(-1),sz[M].pb(1);
	lst[ch[M]-'a'+1]=M;
	for(int i=M-1;i>=1;i--){
		int len=s[i].size();
		for(int j=0;j<len;j++){
			int c=s[i][j]-'a'+1;
			if(lst[c]) nxt[i].pb(lst[c]),sz[i].pb(size[lst[c]]);
			else nxt[i].pb(-1),sz[i].pb(1);
			size[i]=min(Max,size[i]+sz[i][j]);
		}
		lst[ch[i]-'a'+1]=i;
	}
	s[0]="a";nxt[0].pb(lst[1]);sz[0].pb(size[lst[1]]);size[0]=sz[0][0];
	dfs(0,0,L,R);
	return 0;
}


```

---

## 作者：StillEmpty (赞：0)

oi 复健后的第一题，感觉水平回到亲爱的普及组：

一读题，意识到整个过程是树状结构，每个字母都是节点，可以理解为 `replace` 的时候把 `s` 作为 `c` 的儿子们。这个时候，发现本题数据特征：可能整串很长，但求的串只有 $2 \times 10^5$ 规模。所以，我们的任务就是**在 `replace` 的过程中不断锁定包含 `[l, r]` 的节点串**。

考虑到每个字母都可能最终扩展成很长一串，所以 `[l, r]` 的开头和结尾可能属于某个字母节点的一部分。因此我们还需记录当前维护的节点串在完成所有操作后的完整字符串中所在位置 `[st, en]`。由于更新字符串只会变长不会变短，而最终长度为 $r-l+1$，易知复杂度为 $O(r-l+\sum s)$。但有两个问题：

1. 如果 `str.size() == 1`，更新并不会增长节点串，从而导致复杂度爆炸。为此，我完全没有往优雅的标答考虑，设计了一种奇葩的优化方案：我们不用字母记录节点串，而是用“编号”。每一个编号唯一对应和表示一个字母，而可能有多个编号对应同一个字母。这个方案的好处是，**`str.size() == 1` 的更新可以通过更改编号对应的字母 $O(1)$ 解决**。

2. `en` 可能巨大，`long long` 溢出。解决方案是，转而记录节点串最后一个字母完全展开后的字符串的第一个字母在完整串中的下标，因为它在 `r` 之前，而 `r` 范围给定。

3. 这时却引发了一个新的问题：如果一个字母在节点串中没有，而 `str` 中出现了它，就必须给它分配新的编号。如果不断清空一个字母又不断新增它，编号的规模是常数极小的 $O(\sum s)$。为了从数学上根本严谨地解决这个几乎 hack 不出来的 bug，我增加了一个编号合并机制，定期将一个字母的所有编号统一。原理十分接近分块，理论时间复杂度是 $O((r-l+\sum s)(\sqrt{r-l}+\sqrt{\sum s}))$。跟分块一样，实际 coding 时可以合并次数规定在 $10^2$ 规模以内。

令人感慨的是，常数极小+瞎搞方法没人 hack，导致我注释掉 3. 的优化都以极短的时间通过了。

用链表维护的，递推而非 dfs 的，改了多次写的巨丑的代码：
```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 2e5, T = 200;
char ch[N+1]; string str[N+1];
int m; ll l, r, st = 1, las = 1, len[N+1][26], chlen[26];
list<int> s; vector<int> mp, dmp[26]; vector<vector<list<int>::iterator> > pos;

int main() {
	ios::sync_with_stdio(false);
	// freopen("in.txt", "r", stdin);
	// freopen("out.txt", "w", stdout);
	cin >> l >> r >> m;
	for(int i = 1; i <= m; ++i) {
		cin >> ch[i] >> str[i];
	}
	for(int i = 0; i < 26; ++i) chlen[i] = 1;
	for(int i = m; i >= 1; --i) {
		ll leni = 0;
		for(int j = 0; j < 26; ++j) len[i][j] = chlen[j];
		for(int j = 0; j < str[i].size(); ++j) {
			leni += chlen[str[i][j]-'a'];
			if(leni > 3e18) {
				leni = 3e18; break;
			}
		}
		chlen[ch[i]-'a'] = leni;
	}
	s.push_back(0);
	for(int i = 0; i < 26; ++i) mp.push_back(i);
	for(int i = 0; i < 26; ++i) dmp[i].push_back(i);
	pos.push_back(vector<list<int>::iterator>(1, s.begin()));
	for(int i = 1; i < 26; ++i) pos.push_back(vector<list<int>::iterator>());
	for(int i = 1; i <= m; ++i) {
		/*if(m >= T && i%(m/T) == 0) {
			pos.clear();
			for(int j = 0; j < 26; ++j) pos.push_back(vector<list<int>::iterator>());
			for(auto j = s.begin(); j != s.end(); ++j) {
				*j = mp[*j]; pos[*j].push_back(j);
			}
			mp.clear();
			for(int j = 0; j < 26; ++j) mp.push_back(j);
			for(int j = 0; j < 26; ++j) {
				dmp[j].clear(); dmp[j].push_back(j);
			}
		}*/
		bool fl = 0;
		for(int j = 0; j < dmp[ch[i]-'a'].size(); ++j) {
			if(pos[dmp[ch[i]-'a'][j]].size() != 0) {
				fl = 1; break;
			}
		}
		if(!fl) continue;
		if(str[i].size() == 1) {
			if(ch[i] == str[i][0]) continue;
			for(int j = 0; j < dmp[ch[i]-'a'].size(); ++j) {
				dmp[str[i][0]-'a'].push_back(dmp[ch[i]-'a'][j]);
				mp[dmp[ch[i]-'a'][j]] = str[i][0]-'a';
			}
			dmp[ch[i]-'a'].clear();
			continue;
		}
		vector<int> dmpcp = dmp[ch[i]-'a']; dmp[ch[i]-'a'].clear();
		vector<int> strcp;
		for(int j = 0; j < str[i].size(); ++j) {
			if(dmp[str[i][j]-'a'].size() != 0) {
				strcp.push_back(dmp[str[i][j]-'a'][0]);
			}
			else {
				mp.push_back(str[i][j]-'a');
				strcp.push_back(mp.size()-1);
				dmp[str[i][j]-'a'].push_back(mp.size()-1);
				pos.push_back(vector<list<int>::iterator>());
			}
		}
		if(s.size() == 1) {
			int q = 0; ll cnt;
			for(; st+len[i][str[i][q]-'a']-1 < l; st += len[i][str[i][q++]-'a']);
			cnt = st;
			for(; cnt <= r && q < str[i].size(); cnt += len[i][str[i][q++]-'a']) {
				s.insert(s.end(), strcp[q]);
				pos[strcp[q]].push_back(prev(s.end()));
			}
			cnt -= len[i][str[i][--q]-'a'];
			las = cnt;
			s.erase(s.begin());
			continue;
		}
		for(int j = 0; j < dmpcp.size(); ++j) {
			for(int k = 0; k < pos[dmpcp[j]].size(); ++k) {
				auto it = pos[dmpcp[j]][k];
				if(it == s.begin()) {
					int q = 0;
					for(; st+len[i][str[i][q]-'a']-1 < l; st += len[i][str[i][q++]-'a']);
					for(; q < str[i].size(); ++q) {
						s.insert(it, strcp[q]); pos[strcp[q]].push_back(prev(it));
					}
					s.erase(it); continue;
				}
				++it;
				if(it == s.end()) {
					int q = 0;
					for(; q < str[i].size() && las <= r; las += len[i][str[i][q++]-'a']) {
						s.insert(it, strcp[q]); pos[strcp[q]].push_back(prev(it));
					}
					las -= len[i][str[i][--q]-'a'];
					s.erase(pos[dmpcp[j]][k]);
					continue;
				}
				for(int q = 0; q < strcp.size(); ++q) {
					s.insert(it, strcp[q]); pos[strcp[q]].push_back(prev(it));
				}
				s.erase(pos[dmpcp[j]][k]);
			}
			pos[dmpcp[j]].clear();
		}
		continue;
	}
	for(auto it = s.begin(); it != s.end(); ++it) {
		cout << char(mp[*it]+'a');
	}
	cout << endl;
	return 0;
}
```

---

