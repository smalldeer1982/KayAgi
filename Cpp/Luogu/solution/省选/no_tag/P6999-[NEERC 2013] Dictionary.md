# [NEERC 2013] Dictionary

## 题目描述

Petr和Dmitry正在研究一种新的数据压缩方案。他们的任务是压缩一组给定的单词。为了压缩给定的一组单词，他们必须建立一个有根的树。这棵树的每一个边缘都有一个字母。

让我们定义一个由这种树生成的字典，它是一组单词，可以通过在树的任何顶点（不一定是根节点）的任何路径上的边上连接字母，从根向下到叶子（但不一定在叶节点上完成）来构造。

男孩们必须用字典来构造这样一棵树，字典是一组单词的超集，他们被给予压缩。满足上述条件的树之间的顶点数应该最小。任何具有相同顶点数的树都可以。你的任务是帮助他们。

例如，上图中的一棵树的根标记为1，从7到5的路径表示north，从16到12的路径表示eastern，从29到22的路径表示european，从3到25的路径表示regional，从1到31的路径表示contest。

## 样例 #1

### 输入

```
5
north
eastern
european
regional
contest
```

### 输出

```
31
0
7 n
2 o
18 t
4 h
29 e
17 a
7 s
8 t
9 e
10 r
11 n
6 u
13 r
14 o
15 p
16 e
3 r
18 e
19 g
20 i
21 o
22 n
23 a
24 l
1 c
26 o
27 n
28 t
6 s
30 t
```

# 题解

## 作者：JoshAlMan (赞：3)

## Description

给一些单词，要求建一棵节点最少的字典树，使字典序中包含给定所有的单词（单词路径在树上出现过）。

## Solution

若 $a$ 是 $b$ 的子串，那么 $b$ 的限制强于 $a$，$a$ 可以删去。

接下来我们就得到了两两不包含的单词集。

考虑如果要把单词 $x$ 插入到当前字典序，可以找一个包含 $x$ 最长前缀的位置，这样可以添加尽量少的后缀凑满整个单词，并且这步并不影响后续单词加入，因为字典树能表示的串还是一样，因此是独立的。并且 $x$ 最长前缀一定仅属于一个字符串，否则即跨越了两个字符串，即 $x$ 包含那个字符串，这种情况已经去掉了。

因此对于两个单词 $a, b$，可以设 $w(a, b)$ 为把 $b$ 接在 $a$ 后面的最小花费，即 $len_b - $ $b$ 的前缀与 $a$ 能匹配的最长长度，这个东西可以 KMP 快速求，不过此题没有必要。

把这个东西看成一个有向图，这样构成一个联通的字典树 $\Leftrightarrow$ 该图联通。

枚举根，求最小树形图即可。 

这题还要记录方案，考虑朱刘算法的定义，缩点的新边选择的意义是选择这条边，去掉原来的入边。每一层每种新边的选择对应选1杀1，因此每次新边可以新开一个编号，在最终状态，考虑每个选择编号对应上一层选择不选哪两条边即可。把边弄出来之后，需要构造字典树，这里注意每个点可能代表若干串的某个下标，而边的含义是某点要在某点的某处往伸，我是把边预处理成最靠近根的点的位置。

时间复杂度 $O(n^4)$。



---

## 作者：zhylj (赞：1)

构造一张 $n+1$ 个点的图，其中第 $n + 1$ 个点表示空串 $s_{i+1}=\epsilon$，使得 $w(i,j)$ 表示 $s_j$ 接在 $s_i$ 所在的链上的最小花费。即 $|s_j|$ 减去 $s_j$ 的前缀中为 $s_i$ 子串的最长长度。注意到我们总是能对串两两拼接组成想要的树，证明考虑最小的方案为 $T$，我们对所有串找到其在 $T$ 中对应的串的起点从浅到深加入点，那么要么它为根，要么必然可以找到一条覆盖了它前缀的串。

于是可以发现我们要求的实际上是这张图以空串为根的最小树形图，暴力跑朱刘算法即可。

然后这里我们需要构造方案，我的实现是：记录选取每条环边互斥的边的集合 $\operatorname {eRep}_i$，然后按照被缩起来的时间顺序倒序加边，若一条环边的一个互斥的边以及被加了，那么它就不用加了。

时间复杂度 $\mathcal O(n^3)$。

```cpp
const int N = 50 + 5, M = 3000 + 5;

struct Edge {
	int u, v, w;
} E[M];
std::vector <int> T, e_rep[M];
bool e_chs[M];
int n, m, W[N][N];
std::string s[N];

int CheckSubstr(std::string t, std::string str) {
	if(t.empty()) return 0;
	int t_len = t.size(), str_len = str.size();
	for(int i = 0; i + t_len <= str_len; ++i)
		if(str.substr(i, t_len) == t) return i;
	return -1;
}

int idx[N], n_idx[N], in_id[N], pre[N], vis[N];
int Choose(int i) {
	T.push_back(i);
	return E[i].w;
}
int DMST(int r) {
	int res = 0, cur_n = n + 1;
	for(int i = 1; i <= cur_n; ++i) idx[i] = i;
	while(true) {
		int v_cnt = 0;
		for(int i = 1; i <= cur_n; ++i)
			pre[i] = vis[i] = n_idx[i] = 0;
		for(int i = 1; i <= m; ++i) {
			int u = idx[E[i].u], v = idx[E[i].v], w = E[i].w;
			if(v != idx[r] && u != v && (!pre[v] || w < E[in_id[v]].w))
				in_id[v] = i, pre[v] = u;
		}
		for(int i = 1; i <= cur_n; ++i) {
			int u = i;
			for(; u && !vis[u]; u = pre[u]) vis[u] = i;
			if(u != idx[r] && vis[u] == i) {
				n_idx[u] = ++v_cnt;
				res += Choose(in_id[u]);
				for(int v = pre[u]; v != u; v = pre[v]) {
					n_idx[v] = v_cnt;
					res += Choose(in_id[v]);
				}
			}
		}
		for(int i = 1; i <= m; ++i) {
			int u = idx[E[i].u], v = idx[E[i].v];
			if(n_idx[u] != n_idx[v] && n_idx[v]) {
				E[i].w -= E[in_id[v]].w;
				e_rep[in_id[v]].push_back(i);
			}
		}
		for(int i = 1; i <= cur_n; ++i)
			if(!n_idx[i]) n_idx[i] = ++v_cnt;
		for(int i = 1; i <= n + 1; ++i) idx[i] = n_idx[idx[i]];
		if(v_cnt == cur_n) {
			for(int i = 1; i <= cur_n; ++i)
				if(i != idx[r]) res += Choose(in_id[i]);
			break;
		}
		cur_n = v_cnt;
	}
	std::reverse(T.begin(), T.end());
	for(int i : T) {
		e_chs[i] = true;
		for(int j : e_rep[i])
			if(e_chs[j]) {
				e_chs[i] = false;
				break;
			}
	}
	return res;
}

int tr_cnt;
std::vector <int> nxt[N], pos_id[N];
void Dfs(int u, int p) {
	if(p) {
		int su_siz = s[u].size(), k = su_siz - W[p][u],
			x = CheckSubstr(s[u].substr(0, k), s[p]);
		for(int i = 0; i <= k; ++i)
			pos_id[u].push_back(pos_id[p][x + i]);
		for(int i = k + 1, j = pos_id[p][x + k]; i <= su_siz; ++i) {
			printf("%d %c\n", j, s[u][i - 1]);
			pos_id[u].push_back(j = ++tr_cnt);
		}
	} else {
		pos_id[u].push_back(++tr_cnt);
		printf("0\n");
	}
	for(int v : nxt[u]) {
		Dfs(v, u);
	}
}
void Construct() {
	for(int i : T) {
		if(!e_chs[i]) continue;
		int u = E[i].u, v = E[i].v;
		nxt[u].push_back(v);
	}
	Dfs(n + 1, 0);
}

int main() {
    std::cin >> n;
    for(int i = 1; i <= n; ++i)
        std::cin >> s[i];
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) {
            int k = 0, sj_siz = s[j].size();
            for(; k + 1 <= sj_siz && ~CheckSubstr(s[j].substr(0, k + 1), s[i]); ++k);
            k = sj_siz - k;
            W[i][j] = k;
            E[++m] = (Edge) { i, j, k };
        }
    for(int i = 1; i <= n; ++i) {
        int si_siz = s[i].size();
        E[++m] = (Edge) { n + 1, i, si_siz };
        W[n + 1][i] = si_siz;
    }
    printf("%d\n", DMST(n + 1) + 1);
    Construct();
	return 0;
}
```


---

## 作者：enucai (赞：0)

最近出的牛客挑战赛出了和这个题题意相同的题，当时的版本是 $n,\sum |S_i|\le 10^6$ 的。后来被 rainbow 爆了原题，但好像把原题的标爆了。

考虑对所有的串建出 AC 自动机，求出 Fail 树。走一条 Trie 树上的边相当于在表式树上增加一条边，跳一条 Fail 边相当于截取现在表示树上的一段后缀，用这一段后缀继续去匹配其他字符串。

因此对于每一条 Trie 树上的边，令其边权为 $1$，对于 Fail 边，边权为 $0$，求一个最小树形图即可。令所有串的长度之和为 $m$，则点数与边数均为 $O(m)$，计算最小树形图复杂度 $O(m\log m)$，足以通过本题。由于这张图只有 $01$ 边权，可以用一些技巧优化到 $O(m\alpha(m))$。

考虑该算法的正确性。

考虑对于子串表示树上的任意一条边，在 ACAM 的 trie 树上都能找到对应的边，且边权为 $1$，因此对于任意一个合法的子串表示树，均存在一种在上述图上的树形图表示。

而对于任意一个求出的树形图，我们可以按照在 trie 树上选择的边来构造一棵子串表示树，而对于任意一个字符串 $s_i$，只需要沿着求出的树形图上的边，即可在表示树上找到一条从祖先到儿子的路径与之匹配。具体来说，我们找到树形图上 $s_i$ 串结尾对应的点 $u$，向上一直跳 $u$ 在树形图上的父亲直到根节点，我们提取出这条路径上的所有边构成的字符串，走一条 trie 树上的边相当于在字符串后面加一个字符，走一条 fail 边相当于截取当前字符串的一个后缀，走到 $u$ 时的字符串就必然为 $s_i$。因此在对应表示树上，必然存在一条从根开始的路径，使得 $s_i$ 是这条路径的一个后缀，也就是说 $s_i$ 在表示树上出现。

因此在这张图上求出最小树形图即为答案。构造方案是容易的。

牛客题目（加强版）链接：<https://ac.nowcoder.com/acm/contest/84888/F>。

---

