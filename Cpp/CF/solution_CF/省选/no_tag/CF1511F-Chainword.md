# Chainword

## 题目描述

A chainword is a special type of crossword. As most of the crosswords do, it has cells that you put the letters in and some sort of hints to what these letters should be.

The letter cells in a chainword are put in a single row. We will consider chainwords of length $ m $ in this task.

A hint to a chainword is a sequence of segments such that the segments don't intersect with each other and cover all $ m $ letter cells. Each segment contains a description of the word in the corresponding cells.

The twist is that there are actually two hints: one sequence is the row above the letter cells and the other sequence is the row below the letter cells. When the sequences are different, they provide a way to resolve the ambiguity in the answers.

You are provided with a dictionary of $ n $ words, each word consists of lowercase Latin letters. All words are pairwise distinct.

An instance of a chainword is the following triple:

- a string of $ m $ lowercase Latin letters;
- the first hint: a sequence of segments such that the letters that correspond to each segment spell a word from the dictionary;
- the second hint: another sequence of segments such that the letters that correspond to each segment spell a word from the dictionary.

Note that the sequences of segments don't necessarily have to be distinct.

Two instances of chainwords are considered different if they have different strings, different first hints or different second hints.

Count the number of different instances of chainwords. Since the number might be pretty large, output it modulo $ 998\,244\,353 $ .

## 说明/提示

Here are all the instances of the valid chainwords for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1511F/d1d06be7b986742ae6183318512e8441f22bced3.png)The red lines above the letters denote the segments of the first hint, the blue lines below the letters denote the segments of the second hint.

In the second example the possible strings are: "abab", "abcd", "cdab" and "cdcd". All the hints are segments that cover the first two letters and the last two letters.

## 样例 #1

### 输入

```
3 5
ababa
ab
a```

### 输出

```
11```

## 样例 #2

### 输入

```
2 4
ab
cd```

### 输出

```
4```

## 样例 #3

### 输入

```
5 100
a
aa
aaa
aaaa
aaaaa```

### 输出

```
142528942```

# 题解

## 作者：syksykCCC (赞：8)

如何判定一个字符串 $s$ 能否被拆为若干段字典中的单词呢？

考虑对字典建立 trie 树，当在 $s$ 的末尾增加一个字符的时候，就相当于是在 trie 树上从一个结点 $u$ 沿着某一条转移边走到另外一个结点 $v$。当然，你也可以在某个字符串的结束位置不继续往下走，而是回到根节点。

假如只有一道提示线，那么根据套路，可以用 $f_{i, u}$ 表示 $s$ 加入了 $i$ 个字符，当前在 trie 的结点 $u$ 上，这种情况下的方案数。转移是显然的。

但现在有两道提示线，仿照这样的思路，使用 $f_{i, u, v}$ 表示 $s$ 加入了 $i$ 个字符，上方的线在 trie 的结点 $u$ 上，下方的线在 trie 的结点 $v$ 上，这种情况下的方案数。

很容易发现这个 DP 与 $i$ 其实没什么关系，可以使用矩阵快速幂优化。但是总状态数是至多约 $1600$ 的。很显然，矩阵快速幂并不能跑得动。

现在考虑删减有效状态：

1. 记 $root \to u$ 的路径的字符串为 $S$，$root \to v$ 的路径的字符串为 $T$，显然有 $S$ 是 $T$ 的后缀，或者 $T$ 是 $S$ 的后缀。
2. $f_{i, u, v} = f_{i, v, u}$，所以 $(u, v)$ 和 $(v, u)$ 可以视作同一个状态。

加入这两个限制后，状态数就被删减到了约 $l = 160$，这时候套用矩阵快速幂优化即可。

一个实现上的细节是，如何找到满足第一种要求的状态呢？其实从 $(0,0)$ 开始 BFS / DFS，每次转移的时候枚举最后一个字符，所有能访问到的结点就是我们想要的结点。

时间复杂度 $O(l^3 \log m)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 50, M = 161, MOD = 998244353;
struct matrix
{
	int val[M][M];
	matrix() { memset(val, 0, sizeof(val)); }
	matrix operator * (const matrix &oth) const
	{
		matrix res;
		for(int i = 0; i < M; i++)
			for(int j = 0; j < M; j++)
				for(int k = 0; k < M; k++)
					res.val[i][j] = (res.val[i][j] + 1LL * val[i][k] * oth.val[k][j] % MOD) % MOD;
		return res;
	}
} trans; 
matrix Qpow(matrix a, long long power)
{
	matrix res;
	for(int i = 0; i < M; i++) res.val[i][i] = 1;
	while(power)
	{
		if(power & 1) res = res * a;
		a = a * a;
		power >>= 1;
	}
	return res;
}
struct trie
{
	int siz;
	struct node
	{
		bool ext;
		int ch[26];
		node() { ext = false; memset(ch, -1, sizeof(ch)); }
	} o[N];
	trie() { siz = 0; } 
	void Insert(char *str)
	{
		int cur = 0;
		for(int i = 1; str[i]; i++)
		{
			if(o[cur].ch[str[i] - 'a'] == -1) o[cur].ch[str[i] - 'a'] = ++siz;
			cur = o[cur].ch[str[i] - 'a'];
		}
		o[cur].ext = true;
	}
} tr;
int n;
long long m;
char s[N];
queue<pair<int, int>> que;
map<pair<int, int>, int> idx;
int GetID(pair<int, int> p)
{
	if(p.first > p.second) swap(p.first, p.second);
	if(!idx.count(p))
	{
		int k = idx.size();
		idx[p] = k;
		que.push(p);
	}
	return idx[p];
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
	{
		cin >> (s + 1);
		tr.Insert(s); 
	}
	que.push(make_pair(0, 0));
	idx[make_pair(0, 0)] = 0;
	while(!que.empty())
	{
		pair<int, int> cur = que.front();
		que.pop();
		int x = GetID(cur);
		for(int c = 0; c < 26; c++)
		{
			pair<int, int> nxt = make_pair(tr.o[cur.first].ch[c], tr.o[cur.second].ch[c]);
			if(nxt.first == -1 || nxt.second == -1) continue;
			trans.val[x][GetID(nxt)]++;
			if(tr.o[nxt.first].ext) trans.val[x][GetID(make_pair(0, nxt.second))]++;
			if(tr.o[nxt.second].ext) trans.val[x][GetID(make_pair(nxt.first, 0))]++;
			if(tr.o[nxt.first].ext && tr.o[nxt.second].ext) trans.val[x][0]++;
		}
	}
	cout << Qpow(trans, m).val[0][0] << endl; 
	return 0;
}
```

---

## 作者：feecle6418 (赞：7)

有一个 dp：$f(x,i,j)$ 表示前 $x$ 位，第一个串匹配到 Trie 树上 $i$ 号点，第二个串匹配到 Trie 树上 $j$ 号点，的方案数，这样是 $O((\sum len)^2n)$ 的。

显然答案是不超过 $(\sum len)^2$ 阶的常系数齐次线性递推数列，进一步分析发现有用的状态其实不超过 $\sum len^2$ 个（一定有 $i,j$ 有一个是另一个的后缀），因此暴力算出前 $2\sum len^2$ 个答案，然后用 BM+多项式取模算即可。

复杂度：$O((\sum len^2)\times (\sum len^2)\times |\Sigma|+(\sum len^2)\log (\sum len^2)\log n)$。截止 2021.10.15 是洛谷最优解。

~~所以可以出到 $\sum len^2\le 2000$~~

---

## 作者：Alex_Eon (赞：1)

### Change log
- 2023.12.1 修改杂题集链接。

#### [$\color{blueviolet}\text{CF 杂题集（点我）}$](https://www.cnblogs.com/Eon-Sky/p/17763683.html)
#### [$\color{red}\text{博客内食用效果更佳（点我）}$](https://www.luogu.com.cn/blog/Ksy/solution-cf1511f)

### 复杂度：$O(st^3 \log m)$ （$st$ 为状态数）
### 完整思路

先建 Trie 树，设 $f_{i, u, v}$ 到第 $i$ 个字符，两个分割分别处在 $u$ 节点与 $v$ 节点的方案数。

暴力转移是简单的，数据范围提醒我们要用矩阵优化，对于一个状态（有序数对）$(u, v)$ 建立一个点，若状态 $(u, v)$ 可以向 $(u', v')$ 转移，则在代表两个状态的点之间连边。

特殊地，若 $u'$ 是终止节点，则 $(u', v')$ 同时具有 $(0, v')$ 的转移，$v'$ 也同理；若 $u', v'$ 都是终止节点，状态 $(u', v')$ 同时具有 $(0, 0)$ 的转移。

所以对于上述情况，$(u, v)$ 也可以向 $(u', v')$ 的等价状态连一条边，于是我们得到了一个有向图，等价于让我们求长度为 $m$ 的从 $(0, 0)$ 到 $(0, 0)$ 路径条数，但此时状态数是 $1600$ 左右的，显然我们不能接受，考虑优化方式。

首先对于状态 $u, v$ 它可能是不存在的，因为 $u, v$ 在 Trie 树上的形态必然是祖先和子代的关系，状态数来到 $320$ 左右，再考虑 $(u, v)$ 和 $(v, u)$ 在上述图中是对称的存在，考虑在矩阵中所成一个状态即可。


### 参考代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned UN;
typedef double DB;
//--------------------//
const int N = 50 + 5, M = 1e9 + 5, L = 50 + 5, ML = 160 + 5;
const int Mod = 998244353;

int n, m, tot, len;

const int TN = 50 + 5;

struct Mat { // 矩阵，为了方便重载了一些运算
    int mat[ML][ML];
    int* operator [](int x) {return mat[x];}
    Mat() {memset(mat, 0, sizeof(mat));}
    void init() {
        for (int i = 0; i <= len; i++)
            mat[i][i] = 1;
    }
    void print() {
        printf("size : %d\n", len);
        for (int i = 0; i <= len; i++, printf("\n"))
            for (int j = 0; j <= len; j++)
                printf("%d ", mat[i][j]);
    }
}base;

Mat operator *(Mat &a, Mat &b) {
    Mat c;
    for(int i = 0; i <= len; i++)
        for(int j = 0; j <= len; j++)
            for(int k = 0; k <= len; k++)
                c[i][j] = (c[i][j] + 1LL * a[i][k] * b[k][j] % Mod) % Mod;
    return c;
}

Mat operator ^(Mat a, int b) { // 矩阵快速幂
    Mat res; res.init();
    // res.print();
    while (b) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

const int Ch = 26 + 5;

struct Trie {
    struct Trie_Node {
        int nex[Ch];
        bool fl;
    } t[N];

    void insert(char *s) {
        int len = strlen(s + 1), now = 0;
        for (int it, i = 1; i <= len; i++) {
            it = s[i] - 'a' + 1;
            if (!t[now].nex[it])
                t[now].nex[it] = ++tot;
            now = t[now].nex[it];
        }
        t[now].fl = true; // 终止标记
    }
} T;

pair<int, int> pt[ML];
map<pair<int, int>, int> id;
map<pair<int, int>, bool> vis;

int idx(pair<int, int> x) {
    // printf("len : %d\n", len);
    if (x.first > x.second)
        swap(x.first, x.second);
    if (id.find(x) == id.end()) {
        id[x] = ++ len;
        pt[len] = x;
    }
    return id[x];
}

void BFS() {
    // base.print();
    queue<pair<int, int>> q;
    id[{0, 0}] = 0, pt[0] = {0, 0}, q.push({0, 0});
    while (!q.empty()) {
        pair<int, int> now = q.front(); q.pop();
        if (now.first > now.second) // 保证状态第一关键字更小
            swap(now.first, now.second);
        if (vis.find(now) != vis.end()) // 每个节点只需要被搜索一遍
            continue;
        vis[now] = true;
        int u = now.first, v = now.second;
        for (int tou, tov, it = 1; it <= 26; it++) {
            if (!T.t[u].nex[it] || !T.t[v].nex[it]) // 如果没有可以转移的节点就停止
                continue;
            tou = T.t[u].nex[it], tov = T.t[v].nex[it];
            pair<int, int> to = {tou, tov};
            q.push({to}), base[idx(now)][idx(to)]++;
            if (T.t[tou].fl) // 对于可以转移到 0 节点的状态特判
                q.push({0, T.t[v].nex[it]}), base[idx(now)][idx({0,tov})]++;
            if (T.t[tov].fl)
                q.push({0, T.t[u].nex[it]}), base[idx(now)][idx({0, tou})]++;
            if (T.t[tou].fl && T.t[tov].fl)
                base[idx(now)][0]++;
        }
    }
    // base.print();
}
//--------------------//
int main() {
    scanf("%d%d", &n, &m);
    char tem[L];
    for (int i = 1; i <= n; i++)
        scanf("%s", tem + 1), T.insert(tem);
    BFS();
    // printf("len : %d\n", len);
    Mat temp = (base ^ m);
    // temp.print();
    printf("%d\n", temp[0][0]);
    return 0;
}
```

---

## 作者：happybob (赞：0)

首先对所有字符串建立字典树。设根节点为 $0$。字典树节点大小量级为 $O(n \left| s \right|)$。

首先有一个朴素的类似数位 DP 的做法，记 $f_{i,x,y}$ 表示长度为 $i$，目前未匹配的末尾中 $P$ 沿着字典树走到了 $x$，$Q$ 沿着字典树走到了 $y$ 时的方案数。转移的时候直接枚举选什么然后转移即可。复杂度 $O(mn^2\left| s\right|^2\left| \sum \right|)$，显然不对。

注意到这个东西可以直接使用矩阵快速幂优化，这个转移矩阵是一个 $(n\left|s\right|)^2\times(n\left|s\right|)^2$ 的矩阵，直接矩阵快速幂复杂度是 $O((n\left|s\right|)^6\log m)$，还是不太对。

分析一下可知复杂度瓶颈在于矩阵状态数。事实上我们发现 $f_{i,x,y}=f_{i,y,x}$，所以通过限制 $x\leq y$ 可以使得矩阵大小至少可以减半。同时我们可以发现存在大量无用状态 $f_{i,x,y}=0$，真正有用的状态数不多。可以先进行一次 DFS 或 BFS，从 $(0,0)$ 开始，每次选下一个字符然后在字典树上面走，搜出所有有效状态。现在状态数不会很大，事实上写一下就能过了。

[Submission Link](https://codeforces.com/problemset/submission/1511/264800877)。

---

