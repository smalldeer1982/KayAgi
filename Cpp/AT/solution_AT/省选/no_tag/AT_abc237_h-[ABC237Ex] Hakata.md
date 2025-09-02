# [ABC237Ex] Hakata

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc237/tasks/abc237_h

英小文字からなる文字列 $ S $ があります。  
 毎日回文のことばかりを考えている高橋博多くんは、$ S $ の部分文字列のうち回文となっているものをいくつか選び、小倉楽子さんに教えることにしました。

小倉楽子さんは、教えられた回文のうち $ 2 $ つであって、一方が他方の部分文字列になっているようなものが存在すると、怒ります。

小倉楽子さんが怒らないという条件のもとで、高橋博多くんは最大でいくつの回文を選ぶことができますか？

## 说明/提示

### 注記

$ S $ の**部分文字列**とは、$ S $ の先頭から $ 0 $ 文字以上、末尾から $ 0 $ 文字以上削除して得られる文字列のことをいいます。  
 例えば、`ab` は `abc` の部分文字列ですが、`ac` は `abc` の部分文字列ではありません。

### 制約

- $ 1\ \leq\ |S|\ \leq\ 200 $
- $ S $ は英小文字からなる

### Sample Explanation 1

`aba` 、`bab` 、`bb` の $ 3 $ つの回文を選ぶことができます。

### Sample Explanation 2

`x` 、`y` 、`z` の $ 3 $ つの回文を選ぶことができます。

## 样例 #1

### 输入

```
ababb```

### 输出

```
3```

## 样例 #2

### 输入

```
xyz```

### 输出

```
3```

## 样例 #3

### 输入

```
xxxxxxxxxx```

### 输出

```
1```

# 题解

## 作者：EuphoricStar (赞：8)

下文令 $|S| = n$。

**引理：** 一个字符串中本质不同的回文串数量 $\le n$。

**证明：** 每在字符串末尾添加一个字符，本质不同回文串数量最多增加 $1$。

考虑反证，设字符串在添加 $s_n$ 后，$s_{x...n}$ 与 $s_{y...n}$（令 $x < y$）都是 **之前没有出现过** 的回文串，那么根据回文串的定义，可得 $s_x = s_n = s_y = s_{x+n-y}$，$s_{x+1} = s_{n-1} = s_{y+1} = s_{x+n-y-1}$，以此类推，我们得到 $s_{x...x+n-y}$ 与 $s_{y...n}$ 完全相同，矛盾。因此引理得证。

考虑给每个本质不同的回文串编个号，然后建一个 DAG，$x \to y$ 当且仅当 $x$ 是 $y$ 的子串。那么若选了 $x$ 就不能选所有能到达 $x$ 和所有能从 $x$ 到达的点，所以题目求的就是这个 DAG 的 **最大反链** 。

根据 Dilworth 定理，可知在 DAG 中最大反链数 = 可重叠路径的最小划分数，也就是选出若干条链（可以重复经过某点），使得每个点都被覆盖至少一次。求最小可重路径覆盖可以二分图匹配。建一个二分图，若在原 DAG 上 $x$ 可达 $y$，就从 $x$ 的左部点连向 $y$ 的右部点。感性理解，设原 DAG 结点数量为 $m$，一开始每个点形成一条路径，一个匹配意味着原来的 $m$ 条路径中有两条结合了。

建图后跑一遍 Dinic 求出二分图最大匹配，再用 $m$ 减去它就是最终答案。

由于回文串数量 $\le n$，因此总时间复杂度不超过 $O(n^3)$。

[code](https://atcoder.jp/contests/abc237/submissions/36735942)

---

## 作者：Erica_N_Contina (赞：2)

# [ABC237Ex] Hakata

## 题面

给定一个字符串, 你需要从中选出若干回文子串, 并且使得选出的串不存在某一个是另一个的子串, 问最多能选出多少子串.

- $1\ \leq\ |S|\ \leq\ 200$

## 思路

对于对称轴的字母相同的两个回文串，它们有可能存在包含关系。

最差的情况，就是字符串 $S$ 中每个不同的字母作为一个被选择的子串。

如果以字符 $i$ 为对称轴的回文串（这里指长度 $>1$ 的）的数量 $>1$，那么我们就不应该把字符 $i$ 作为一个被选择的子串。

我们将对称轴为字符 $i$ 的所有回文串处理出来，枚举哪个作为被选择的子串，然后判断其它的能否被选择。但这样时间复杂度明显过高。



补充一个性质：一个字符串中本质不同的回文串数量 $ ≤|S|$。这里就不再证明，因为 zltqwq 大佬已经证明过了。



我们很容易发现 $S$ 中的回文串之间存在一些关系，即当我们选择了回文串 $A$ 后就不能选择回文串 $B,C\dots$ 。所以我们考虑将每个回文串看成是一个节点，我们把 $A→B$ 当且仅当 $A,B$ 都是回文串并且 $B$ 是 $A$ 的子串。所以如果我们选择了 $A$，那么通过正向 $1$ 边能访问到的点我们都不可以取。通过反向边能访问到的点我们也不能取。但注意，如果 $A$ 到 $C$ 的路径上既通过了正向边，又通过了反向边，那么它们是可以同时取的，比如 $abcba$ 和 $dbcbd$。



其实这种关系与反链是一样的。让我来介绍一下反链相关的知识。

## 偏序集与反链

以下引用了百度百科的相关资料，并且进行了相关说明。

**偏序集**

设 $R$ 是集合 $A$ 上的一个关系，如果 $R$ 是自反的、反对称的和可传递的，则称 $R$ 是集合 $A$ 的偏序关系，简称[偏序](https://baike.baidu.com/item/%E5%81%8F%E5%BA%8F/2439087?fromModule=lemma_inlink)，记作“$≤$”。对于 $(a,b)∈R$，就把它表示成 $a≤b$。

若在集合 $A$ 上给定一个偏序关系 $≤$（注意这里的 $≤$ 不是比较上的小于等于号），则称集合 $A$ 按偏序关系 $≤$ 构成一个偏序集合，集合 $A$ 和偏序 $R$ 一起称为偏序集，记作 $(A,≤)$。

- 自反性：$a≤a$，$∀a∈P$；

- 反对称性：$∀a,b∈P$，若 $a≤b$ 且 $b≤a$，则 $a=b$；

- 传递性：$∀a,b$，$c∈P$，若 $a≤b$ 且 $b≤c$，则 $a≤c$；

我们也可以把小于等于看成一种偏序关系。我们也可以把一个 DAG 看成类似偏序的东西，即在一幅有向图中，$a→b,b→c$，那么 $a→c$（这里的 $→$ 代表通过若干条有向边可达），这样就满足了传递性。

**反链**

设 $A$ 是一个偏序集合，在 $A$ 的一个[子集](https://baike.baidu.com/item/%E5%AD%90%E9%9B%86/5017034?fromModule=lemma_inlink)中，如果每两个元素都是有关系的，则称这个子集为链。在 $A$ 的一个子集中，如果每两个元素都是无关的，则称这个子集为反链。

我们的关系指的就是满足传递性。即如果 $a≤b$ 且 $b≤c$，那么我们就说 $a,b,c$ 是有关系的。如果 $a≤b$ 且 $c≤b$，那么我们不知道 $a,c$ 之间的关系，我们就称 $a,c$ 之间是无关的。

## 狄尔沃斯定理 (Dilworth's theorem)

对于任意有限[偏序集](https://baike.baidu.com/item/%E5%81%8F%E5%BA%8F%E9%9B%86/4328855?fromModule=lemma_inlink)，其最大[反链](https://baike.baidu.com/item/%E5%8F%8D%E9%93%BE/2652275?fromModule=lemma_inlink)中元素的数目必等于最小链划分中链的数目。

这里我就不证明了，请读者自行搜索。

## 思路

回到本题，刚才说如果 $A$ 到 $C$ 的路径上既通过了正向边，又通过了反向边，那么它们是可以同时取的。那么我们把正向边看成是偏序中的 $≤$，那么“既通过了正向边，又通过了反向边”也就是说 $A$ 到 $C$ 的路径上有且只有要通过一个点 $B$ 满足 $A≤B,C≤B$（这里根据传递性进行了路径压缩），所以 $A$ 和 $C$ 是无关的。那么既然我们要求选出来的回文串都是两两无关的，那么这些回文串就组成了这个偏序集中的最大反链。

所以我们求最小链划分中链的数目即可。我们用二分图匹配来求解。至于二分图匹配，我们用 Dinic 算法即可。

## 代码

```C++
#include <bits/stdc++.h>

using namespace std;
#define ll long long

const int N = 1e3+5;
const int M = 5e6+5;
const int inf = 0x3f3f3f3f;

int n, m, nodecnt, S, T, h[N], idx = 1;
string s;
map<string, int> mp;
int d[N], cur[N],vis[N];

struct edge {
	int to, nxt, w, flow;
} e[M];

void adde(int u, int v, int c, int f) {
	e[++idx].to = v;e[idx].nxt = h[u];e[idx].w = c;e[idx].flow = f;
	h[u] = idx;
}

bool chk(string s) {//判断回文串
	int sz=s.size();//注意size()返回的是unsigned，如果是0那么-1就会变成INF
	for (int i = 0, j = sz - 1; i < j; i++,j--) {
		if (s[i] != s[j])return 0;
	}
	return 1;
}


void add(int u, int v, int c) {
	adde(u, v, c, 0);
	adde(v, u, 0, 0);
}
queue<int> q;

bool bfs() {
	for (int i = 1; i <= nodecnt; ++i) {
		d[i] = -1;
		vis[i] = 0;
	}

	q.push(S);
	vis[S] = 1;
	d[S] = 0;
	while (q.size()) {
		int u = q.front();
		q.pop();
		for (int i = h[u]; i; i = e[i].nxt) {
			if (!vis[e[i].to] && e[i].w > e[i].flow) {
				vis[e[i].to] = 1;
				d[e[i].to] = d[u] + 1;
				q.push(e[i].to);
			}
		}
	}
	return vis[T];
}

int dfs(int u, int a) {
	if (u == T || !a) return a;
	int flow = 0, f;
	for (int i = cur[u]; i; i = e[i].nxt) {
		if (d[e[i].to] == d[u] + 1 && (f = dfs(e[i].to, min(a, e[i].w - e[i].flow))) > 0) {
			e[i].flow += f;
			e[i ^ 1].flow -= f;
			flow += f;
			a -= f;
			if (!a) break;
		}
	}
	return flow;
}

int dinic() {
	int ans = 0;
	while (bfs()) {
		memcpy(cur,h,sizeof h); 
		ans += dfs(S, inf);
	}
	return ans;
}


int main() {
	cin >> s;
	n = s.size();
	for (int i = 0; i < n; ++i) {//找回文串
		for (int j = i; j < n; ++j) {
			string t = s.substr(i, j - i + 1);
			if (mp.find(t) == mp.end() && chk(t)) {
				m ++;
				mp[t] = m;
			}
		}
	}
	nodecnt = T = m * 2 + 2;//超级源点及汇点放在主要点之后,比较方便
	S = T - 1;
	for (int i = 1; i <= m; ++i) {
		add(S, i, 1);
		add(i + m, T, 1);
	}
	for (auto p1 : mp) {
		for (auto p2 : mp) {
			string s = p1.first, t = p2.first;
			int u = p1.second, v = p2.second;
			if (u == v) continue;
			if ((int)t.find(s) != -1) {
				add(u, v + m, 1);
			}
		}
	}
	cout << m - dinic() << endl;
	return 0;
}
```






---

## 作者：Purslane (赞：0)

# Solution

一个经典结论是：一个字符串只有 $O(n)$ 个本质不同的回文子串。可以用数学归纳法证明。

这样可以直接建出回文子串之间的包含关系，包含关系本质上是一种偏序关系。

因此问题等价于 DAG 上的最长反链。

根据 Dilworth 定理，最长反链等于最小点覆盖。跑二分图匹配即可。

---

