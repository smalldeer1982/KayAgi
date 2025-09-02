# Bipartite Array

## 题目描述

You are given a permutation $ p $ consisting of $ n $ integers $ 1, 2, \dots, n $ (a permutation is an array where each element from $ 1 $ to $ n $ occurs exactly once).

Let's call an array $ a $ bipartite if the following undirected graph is bipartite:

- the graph consists of $ n $ vertices;
- two vertices $ i $ and $ j $ are connected by an edge if $ i < j $ and $ a_i > a_j $ .

Your task is to find a bipartite array of integers $ a $ of size $ n $ , such that $ a_i = p_i $ or $ a_i = -p_i $ , or report that no such array exists. If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
4
3
1 2 3
6
1 3 2 6 5 4
4
4 1 3 2
8
3 2 1 6 7 8 5 4```

### 输出

```
YES
1 2 3
NO
YES
-4 -1 -3 -2
YES
-3 -2 1 6 7 -8 -5 -4```

# 题解

## 作者：GaryH (赞：17)

# CF1620F 题解

**题意**：

给定排列 $p$，要求拟定一个新序列 $p'$，满足：

1. $\forall i \in [1,n],p'_i=\pm p_i$；
2. 构造无向图 $G$，其中 $(i,j)$ 有边当且仅当 $i<j,p'_i>p'_j$，要求 $G$ 是二分图。

请给出方案或报告没有方案。

**做法**：

首先注意到，一张图不是二分图，当且仅当其存在至少一个奇环，

故考虑什么情况图中存在奇环。

直接想似乎没什么思路，我们考虑这种特殊图的一个性质，即：

若图中存在奇环，当且仅当图中存在一个长为 $3$ 的奇环。

怎么证明？我们考虑反证法，但我们先要说明一些东西。

虽然题意是无向图，但我们在接下来考虑问题的时候，可以将边定向，即：

若 $i<j$ 且 $p'_i>p'_j$，则连一条 $i\rightarrow j$ 的有向边。

我们先考虑三个点 $i,j,k$，若同时存在两条有向边 $i\rightarrow j,j\rightarrow k$，则等价于：

$i<j<k,p'_i>p'_j>p'_k$，则图中也存在一条 $i\rightarrow k$ 的有向边。

那么，我们开始反证，即若图中存在一个长度大于 $3$ 的奇环但不存在长度为 $3$ 的奇环，

那此时在奇环中，连接任意一点的两条边，

两条边要么同时是这个点的出边，要么同时是这个点的入边。

这样的话，任意点 $u$ 的出度减入度之差 $d_u$ 不是 $2$ 就是 $-2$，

则一个奇环上所有点的 $d$ 值之和必然不为零，因为有奇数个点，

而实际上一个奇环上的点的 $d$ 值之和显然必须为零，故产生矛盾。

故我们让图中不存在长为 $3$ 的奇环，就可以满足条件。

而一张图中不存在长为 $3$ 的奇环，当且仅当原序列 $p'$ 中不存在 $i<j<k$ 且 $p'_i>p'_j>p'_k$。

此时，我们考虑一个简单的 DP，即：

$f_{i,x,y}$ 为填了序列 $p'$ 的前 $i$ 个，此时序列所有数最大为 $x$，所有逆序对末尾数最大为 $y$，

这样能否不存在长为 $3$ 的奇环，若能则 $f_{i,x,y}=1$，否则 $f_{i,x,y}=0$。

这样是 $O(n^3)$ 的，显然过不去，而转移已经是 $O(1)$ 的，无法优化，故我们考虑优化状态。

我们发现，对于两个都已经构造前了 $i$ 位的序列 $p1,p2$，若两者前 $i$ 位的最大数都为 $x$，

设两者的逆序对末尾数最大值分别为 $y1,y2$，显然，在 $y1$ 和 $y2$ 中取小者对应的序列更有潜力，

或者，形式化的：不妨设 $y1>y2$，则任意一个长为 $n$ 的合法序列，

若其长为 $i$ 的前缀由 $p1$ 构成，则我们将前缀换成 $p2$ 后也一定合法。

同样的，对于一对固定的 $(i,y)$，显然 $x$ 越小序列越容易合法，就不过多赘述了。

那么，对于状态中一对固定的 $(i,x)$，我们只需要存储一个最小的可能 $y$ 即可，即 $f_{i,x}=y$。

当然，如果对于状态中一对固定的 $(i,x)$，其不存在任何一个可能的 $y$，我们就令 $f_{i,x}=INF$。

于是我们就将复杂度优化到了 $O(n^2)$，但还是过不去。

看上去似乎这个无法再进一步优化状态，我们尝试写下状态转移方程：

设 $z=\pm p_{i+1},f_{i,x}=y(z\geq y)$，则我们有：

1. $z<x\rightarrow f_{i+1,x}=z$；
2. $z\ge x\rightarrow f_{i+1,z}=y$。

我们惊讶地发现，转移后新的 $(x,y)$ 中至少有一个值等于 $z=\pm p_{i+1}$。

那么，我们就只需要记 $f_{i,0/1,0/1}$ 代表前 $i$ 位，第 $i$ 位填的值是正/负，其中 $x/y$ 等于 $\pm p_{i+1}$。

状态的转移和前面本质相同，我就不写了，不会可以看代码。

这样的复杂度就是 $O(n)$ 的了，也足以通过本题。

注意题中要求给出方案，故我们需要记录前驱。

**code**：

```
#define pb push_back
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)

using namespace std;
const int N (1e6 + 10);

vector < int > ans;
int n, p[N], f[N][2][2];
struct Node { int i, j, k; } pre[N][2][2];

void work() {
	cin >> n;
	rep (i, 1, n) cin >> p[i];
	rep (i, 0, n + 1) rep (j, 0, 1) 
	  rep (k, 0, 1) f[i][j][k] = 2e9;
	f[1][0][0] = f[1][1][0] = -2e9;
	rep (i, 1, n - 1) rep (j, 0, 1) rep (k, 0, 1) {
		int x, y, t = f[i][j][k];
		if (!j && !k) x = -p[i], y = t;
		if (!j && k)  x = t, y = -p[i];
		if (j && !k)   x = p[i], y = t;
		if (j && k)    x = t, y = p[i];
		Node nw = (Node) {i, j, k};
		rep (sgn, 0, 1) {
			int z = (sgn ? 1 : -1) * p[i + 1];
			if (z < y) continue;
			if (z < x) if (f[i + 1][sgn][1] > x) 
			  f[i + 1][sgn][1] = x, pre[i + 1][sgn][1] = nw;
			if (z >= x) if (f[i + 1][sgn][0] > y) 
			  f[i + 1][sgn][0] = y, pre[i + 1][sgn][0] = nw;
		}
	}
	rep (fj, 0, 1) rep (fk, 0, 1) {
		int i = n, j = fj, k = fk;
		if (f[i][j][k] < 2e9) {
			ans.clear(), puts ("YES");
			while (i >= 1) {
				ans.pb (j ? p[i] : -p[i]);
				Node nw = pre[i][j][k];
				i = nw.i, j = nw.j, k = nw.k;
			}
			reverse (ans.begin(), ans.end());
			for (int x : ans) printf ("%d ", x);
			return puts (""), void();
		}
	}
	puts ("NO");
}

int main() {
	int tasks; cin >> tasks;
	while (tasks--) work();
	return 0;
}
```



---

## 作者：Sol1 (赞：12)

这题显然答案很多，比如样例第三组数据也可以是 $-4,1,-3,2$、$-4,1,-3,-2$ 等等。 

那么显然这题需要 spj，考虑他的 spj 是咋写的。发现好像没有那么好写：图的边数可以达到 $10^{12}$ 量级，而且不太好优化建图，可能需要一个主席树。但是主席树跑 $10^6$ 时空压力都很大，同时这是 CF 题，万一这题 hack 巨大多，评测机就直接寄了。

**这实际上提示我们可能存在一个 bipartite array 的不直接的判定方式，考虑这个判定方式是什么。**

考虑这个图，它可以被分成两个点集，点集之间没有边。回到序列，一个序列对应一个空图，显然这个序列必须递增。

**所以一个 bipartite array 必然可以被拆成两个上升子序列。**

但是这题可以把元素改成负的。考虑到每一个子序列肯定都是它的一段前缀被改成负的，那么肯定原始序列上这个前缀需要递减。

**所以这个问题实际上是要求我们把原始序列拆成两个单谷子序列。**

然后就是套路前缀 DP。因为我们只关心拆出来的子序列的最后一个元素，同时两个最后一个元素中必然有一个肯定是整个序列的最后一个元素，所以设 $f_{i,j,k}$ 表示前 $i$ 个元素，包含第 $i$ 个元素的子序列当前在上升/下降（对应 $j$ 取 $0/1$），不包含第 $i$ 个元素的子序列当前在上升/下降（对应 $k$ 取 $0/1$），不包含第 $i$ 个元素的子序列的最后一个元素最大/最小是什么。其中当 $k=0$ 时找最大的来给递减留出尽量大空间，$k=1$ 时找最小的来给递增留出尽量大空间。

然后就是暴力分类讨论转移，考虑每一个状态下新的元素接到哪个子序列后面以及改变递增/递减状态就可以了。具体过程较简单，不赘述。

最后是输出方案，记三个值，分别表示转移点的 $j,k$（$i$ 一定是当前状态的 $i$ 减去 1），以及最后一个数是否与上一个数在同一个子序列里面。可以压成一个 $0\sim 7$ 中的整数来存储。从 $n,1,1$ 反着搜一遍就可以得到两个单谷子序列，分别把前面递减的部分反过去就可以了。

于是这题就做完了，复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

const int N = 1000005;
int n, f[N][2][2], path[N][2][2], a[N], ans[N];

inline void Read() {
	n = qread();
	for (int i = 1;i <= n;i++) a[i] = qread();
}

inline void UpdMax(int i, int j, int k, int val, int pth) {
	if (val > f[i][j][k]) {
		f[i][j][k] = val;
		path[i][j][k] = pth;
	}
}

inline void UpdMin(int i, int j, int k, int val, int pth) {
	if (val < f[i][j][k]) {
		f[i][j][k] = val;
		path[i][j][k] = pth;
	}
}

inline void Solve() {
	f[1][0][0] = 0x3f3f3f3f;
	f[1][1][0] = 0x3f3f3f3f;
	f[1][0][1] = 0xf3f3f3f3;
	f[1][1][1] = 0xf3f3f3f3;
	for (int i = 2;i <= n;i++) {
		f[i][0][0] = f[i][1][0] = 0xf3f3f3f3;
		f[i][0][1] = f[i][1][1] = 0x3f3f3f3f;
	}
	for (int i = 2;i <= n;i++) {
		if (f[i - 1][0][0] >= 1) {
			if (a[i] < a[i - 1]) UpdMax(i, 0, 0, f[i - 1][0][0], 0);
			UpdMax(i, 1, 0, f[i - 1][0][0], 0);
			if (a[i] < f[i - 1][0][0]) UpdMax(i, 0, 0, a[i - 1], 1);
			UpdMax(i, 1, 0, a[i - 1], 1);
		}
		if (f[i - 1][1][0] >= 1) {
			if (a[i - 1] < a[i]) UpdMax(i, 1, 0, f[i - 1][1][0], 4);
			if (f[i - 1][1][0] > a[i]) UpdMin(i, 0, 1, a[i - 1], 5);
			UpdMin(i, 1, 1, a[i - 1], 5);
		}
		if (f[i - 1][0][1] <= n) {
			if (a[i - 1] > a[i]) UpdMin(i, 0, 1, f[i - 1][0][1], 2);
			UpdMin(i, 1, 1, f[i - 1][0][1], 2);
			if (f[i - 1][0][1] < a[i]) UpdMax(i, 1, 0, a[i - 1], 3);
		}
		if (f[i - 1][1][1] <= n) {
			if (a[i - 1] < a[i]) UpdMin(i, 1, 1, f[i - 1][1][1], 6);
			if (f[i - 1][1][1] < a[i]) UpdMin(i, 1, 1, a[i - 1], 7);
		}
	}
	if (f[n][1][1] > n) cout << "NO\n";
	else {
		cout << "YES\n";
		vector <int> seq[2];
		int j = 1, k = 1, cur = 0;
		for (int i = n;i >= 1;i--) {
			ans[i] = a[i];
			int nxt = path[i][j][k];
			seq[cur].push_back(i);
			cur ^= (nxt & 1);
			j = (nxt >> 2) & 1;
			k = (nxt >> 1) & 1;
		}
		for (int k = 0;k < 2;k++) {
			reverse(seq[k].begin(), seq[k].end());
			int siz = seq[k].size();
			for (int i = 0;i < siz - 1;i++) {
				if (a[seq[k][i]] > a[seq[k][i + 1]]) ans[seq[k][i]] = -ans[seq[k][i]];
				else break;
			}
		}
		for (int i = 1;i <= n;i++) cout << ans[i] << " ";
		cout << '\n';
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	int t = qread();
	while (t--) {
		Read();
		Solve();
	}
	cout.flush();
	#ifdef CFA_44
	while (1);
	#endif
	return 0;
}
```



---

## 作者：dottle (赞：10)

考虑怎么样的图是不二分的，那么有一个比较令人注意的情况：`3 2 1` 这样的一个长为 $3$ 的下降子序列，互相有连边。那么没有长为 $3$ 的下降序列这一条件是必要的，其实这也是充分的，因为根据狄尔沃什这个东西等价于数列可以分为两个上升子序列。上升子序列内部不会有连边，那么就二分了。这样充分和必要就都有了。

然后考虑怎么判断能否划分为两个上升子序列。依次考虑每个数，前面的数构成的子序列只有末尾的两个数是重要的，并且其中有一个要么是 $a_{i-1}$，要么是 $-a_{i-1}$，那么我们当然是希望另一个数越小越好。就可以记录 $A$ 为两个子序列其中有一个以 $a_{i-1}$ 结尾时，另一个的最小结尾；$B$ 代表 $-a_{i-1}$。然后转移就考虑这个数接在哪个子序列后面，贪心地来说我们会接在能接的中较大的那个的后面。然后记一下是从哪里转移来的就可以输出方案了，此部分的细节不再赘述。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
const int N=1000050;
using namespace std;

int n,a[N];
int ty[2][N];

int calc(int a,int b,int c){
	if(a>b)swap(a,b);
	if(c>=b)return a;
	if(c>=a)return b;
	return n+1;
}// 结尾为 a 和 b，求出把 c 接上去以后另一段的结尾最小是多少

void print(int k,int p){
	if(p>1)print(ty[k][p],p-1);
	cout<<(k?-a[p]:a[p])<<' ';
}

void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int A=-n,B=-n;
	for(int i=2;i<=n;i++){
		int x=A,y=B;
		if(calc(x,a[i-1],a[i])<calc(y,-a[i-1],a[i]))
			A=calc(x,a[i-1],a[i]),ty[0][i]=0;
		else 
			A=calc(y,-a[i-1],a[i]),ty[0][i]=1;
		if(calc(x,a[i-1],-a[i])<calc(y,-a[i-1],-a[i]))
			B=calc(x,a[i-1],-a[i]),ty[1][i]=0;
		else 
			B=calc(y,-a[i-1],-a[i]),ty[1][i]=1;
	}
	if(min(A,B)==n+1){
		cout<<"NO"<<endl;
		return;
	}
	else cout<<"YES"<<endl;
	if(A!=n+1)print(0,n);
	else print(1,n); 
	cout<<endl;
}

main(){
	ios::sync_with_stdio(false);
	int _T=1;cin>>_T;
	while(_T--)solve();
	
}

```



---

## 作者：cjZYZtcl (赞：5)

提供一种 $n \log{n}$ 的做法。

考虑先转化一下限制的形式。

- 在第一个正的位置后面，所有负的位置构成上升序列。
- 在最后一个负的位置前面，所有正的位置构成上升序列。
- 对于所有负的元素，不存在长度 $\ge 3$ 的下降序列。
- 对于所有正的元素，不存在长度 $\ge 3$ 的下降序列。

把这个限制移到原序列上，相当于：

- 确定一个 $l, r$（$l < r$），即 $l$ 为第一个正的位置，$r$ 为最后一个负的位置。
- 对于下标位于区间 $[1, l - 1]$ 内的元素，不存在长度 $\ge 3$ 的上升序列，记 $minl = \min\limits_{1 \le x < y < l, a_x < a_y}{a_y}$。
- 对于下标位于区间 $[r + 1, n]$ 内的元素，不存在长度 $\ge 3$ 的下降序列，记 $minr = \min\limits_{r < x < y \le n, a_x > a_y}{a_x}$。
- 对于下标位于区间 $[l, r]$ 的元素，能将其分成两个子序列满足一个为上升序列，一个为下降序列，且下降序列开头 $< minr$，上升序列结尾 $< minl$。

暴力做法是枚举 $l, r$，然后维护 DP。

设已确定 $l, r$，记 $f_i$ 表示 $i$ 位置存在于上升序列中时，下降序列最后一个元素的最大值。

发现可以转移的位置要满足一些偏序关系，用指针加线段树优化可以做到 $O(n \log{n})$，总复杂度 $O(n^3 \log{n})$，最后查询答案可以考虑从前往后做一遍，从后往前做一遍，找个位置合并即可（似乎可以直接从前往后做？）。

但是观察最后合并答案的形式可以注意到 DP 过程可以将不同的 $l$ 的答案一起考虑，并且不会改变 DP 的复杂度，对 $r$ 也是同理。

所以直接 DP 即可，复杂度 $O(\sum n \log{n})$。

[Code](https://codeforces.com/contest/1620/submission/231541367)

---

## 作者：Missa (赞：1)

给个很好写的方法。

- 二分图等价于没有奇环。
- 题目给出的连边方式是具有偏序关系的，若有 $a \to b, b \to c$，就有 $a \to c$，此时 $a, b, c$ 构成三元环。
- 最长链的长度仅为 $2$。
- $i \neq j, p_i \neq p_j$，其反图也有偏序关系。
- 最长反链等于最小点覆盖，因此其反图（$i \to j \iff i < j, p_i < p_j$）可以用两条链覆盖。
- 只要能用两条上升的链覆盖原序列，它就是一个“二分序列”。
- 原序列是排列时，这个条件一定成立，至于不是排列是否满足我没多想。
- dp。
- 朴素的 dp：$f_{i, j, k}$ 表示考虑到 $i$，两个序列的结尾分别是 $j, k$ 是否可行。
- $a_i$ 或 $-a_i$ 是某一个序列的结尾。$f_{i, j, 0/1}$：考虑到 $i$，两个序列的结尾是 $j$ 和 $a_i / -a_i$ 是否可行。
- 值域定义域互换。（要求 dp 是最优性 dp，且交换的维度上的状态的后继状态有包含关系）
- 在 $f_{i, *}$ 上，如果对于 $x < y$（大概是需要全序关系的，一般是大于小于），$f_{i, x}$ 能转移到的所有状态 $f_{i, y}$ 都能转移到，且 $f_{i, x} = f_{i, y}$，则 $x$ 不优，则可以记录每个 $f_{i, x}$ 对应的最优的 $x$。（全序是为了保证这样的 $x$ 唯一。）
- $f_{i, 0/1}$：考虑到 $i$，某个序列的结尾是 $a_{i} / -a_{i}$ 时，另一个序列的结尾的最小值。
- 考虑如何记录路径。发现只要知道是从上一个状态的 $0/1$ 转移过来就行了，因此路径数组的值取 `bool` 就行。（然而我实现时把这一位的状态压进去了，很没必要）
- 枚举当前点取正 / 负，接在哪一个序列后面。贡献式 dp 转移很方便。
- 可以用返回值为 `bool` 的 `cmin` 减小代码量。

```cpp
#include <bits/stdc++.h>

const int inf = 1e9;

bool cmin(int &x, int y) { return y < x ? x = y, 1 : 0; }

void solve() {
  int n; scanf("%d", &n);
  std::vector<int> a(n);
  for (int &x : a) scanf("%d", &x);
  std::vector<std::vector<int>> f(n + 1, std::vector<int> (2, inf)), path = f;
  f[0][0] = f[0][1] = -inf;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 2; j++) {
      int cur = i ? a[i - 1] * (2 * j - 1) : -inf;
      if (a[i] >= cur && cmin(f[i + 1][1], f[i][j])) path[i + 1][1] = 2 + j;
      if (-a[i] >= cur && cmin(f[i + 1][0], f[i][j])) path[i + 1][0] = j;
      if (a[i] >= f[i][j] && cmin(f[i + 1][1], cur)) path[i + 1][1] = 2 + j;
      if (-a[i] >= f[i][j] && cmin(f[i + 1][0], cur)) path[i + 1][0] = j;
    }
  }
  if (f[n][0] == inf && f[n][1] == inf) return printf("NO\n"), void();
  int x = n, y = f[n][0] == inf ? 1 : 0;
  std::vector<int> ans(n);
  for (; x > 0; --x) {
    ans[x - 1] = a[x - 1] * (path[x][y] / 2 * 2 - 1);
    y = path[x][y] & 1;
  }
  printf("YES\n");
  for (auto &u : ans) printf("%d ", u);
  printf("\n");
}

int main() {
  int T; scanf("%d", &T); while (T--) {
    solve();
  }
}
```

---

## 作者：BreakPlus (赞：0)

+ 题目条件可以等价于不存在长度为 $3$ 的下降子序列。因为存在任意大小为 $2k+1$ 的环，其实也就存在 $3$ 元环。

+ 由 Dilworth 定理，又可以等价于原序列可以划分为 $2$ 个不交上升子序列。

+ 然后判定是否存在合法的划分方案是经典题。尝试设计 DP。

+ 可以先设 $f_{i,j}$ 表示 DP 到第 $i$ 个数，$a_i$ 所**不**在的上升子序列的最后一个元素为 $j$，时间复杂度 $\mathcal{O}(n^2)$。

+ 发现 $j$ 越小越好，就可以改成设 $f_i = \min j$ 再进行转移。时间复杂度 $\mathcal{O}(n)$。

```cpp
ll n,a[1000005],f[1000005][2],prv[1000005][2],iff[1000005][2],ans[1000005];
void solve(){
	n=read();
	for(ll i=1;i<=n;i++) a[i]=read();
	for(ll i=0;i<=n+1;i++){
		f[i][0] = f[i][1] = 1e18;
		prv[i][0] = prv[i][1] = iff[i][0] = iff[i][1] = 0;
	} 
	f[1][0] = -1e18, f[1][1] = -1e18;
	for(ll i=1;i<n;i++){
		for(ll j=0; j<=1; j++){
			for(ll k=0; k<=1; k++){
				ll A = a[i] * (j?-1:1), B = a[i+1] * (k?-1:1);
				if(A < B) {
					chkmin(f[i+1][k], f[i][j]);
					if(f[i+1][k] == f[i][j]) {
						prv[i+1][k] = j; 
					}
				}
				if(f[i][j] < B){
					chkmin(f[i+1][k], A);
					if(f[i+1][k] == A) {
						prv[i+1][k] = j; 
					}
				}
			}
		}
	}
	ll nown = n, nowx = 0;
	if(f[n][0] > n && f[n][1] > 0) {
		puts("NO");
		return;
	}
	if(f[n][1] <= n) nowx = 1;
	while(nown >= 1){
		ans[nown] = nowx?-1:1;
		if(nown==1) break;
		nowx = prv[nown][nowx];
		--nown;
	}
	puts("YES");
	for(ll i=1;i<=n;i++) printf("%lld ", a[i] * ans[i]);
	puts("");
}
```

---

## 作者：Hypercube (赞：0)

趣题。

首先题面中给出的限制有点抽象，不方便直接做。于是不难想到找一种方式刻画 “二分的” 排列。

充要条件 $1$

>一个排列是 “二分的”，当且仅当不存在一个长度超过 $3$ 的下降子序列。

充分性：如果不存在长度超过 $3$ 的下降子序列，那么原图必然不存在环。考虑一个环是由两个首尾相同、中间元素不交的下降子序列拼接而成的，而下降子序列长度不超过 $2$，那么必然不存在环，更不可能存在奇环。故原图为二分图。

必要性：考虑反证。假设一个排列是二分的，且存在长度超过 $3$ 的下降子序列，那么必然存在长度恰好为 $3$ 的下降子序列。于是便形成了一个长度为 $3$ 的奇环，原图显然不是二分图。

充要条件 $2$

>一个排列不存在长度超过 $3$ 的下降子序列，当且仅当原排列可以划分为两个上升子序列。

充分性：考虑反证，假设我们在原序列能划分为两个上升子序列且存在长度超过 $3$ 的子序列，那么下降子序列中的三个数必定有两个来自同一上升子序列，显然矛盾。

必要性：我们画出排列的折线图，发现结构必然如下，满足蓝点、红点分别单调递增，且蓝点和红点见必然没有其他的点。于是我们只需要将排列划分为黑色折线和黄色折线对应的点集即可。

![image-20230626185409483](https://cdn.luogu.com.cn/upload/image_hosting/ud5cn7au.png)

把原问题转化到这里基本也就可以做了。考虑从前向后 dp，设到当前位置时，两个子序列最后的元素组成二元组 $(x,y)$，且满足 $x<y$ (因为两个序列并不需要区分)。不难发现二元组其中一个元素必然为 $\pm a_i$，另一个元素自然越小越优。所以合法状态其实只有两个。每一步记录一下转移，倒着输出即可。

---

## 作者：Lgx_Q (赞：0)

~~CF的DP真的很畸形~~

题意：

[orz](https://www.luogu.com.cn/problem/CF1620F)

给出 $1...n$ 的一个排列 $a_1,a_2,...,a_n$，可以给若干个数取相反数，然后对于满足以下条件的 $i,j$ 连一条边

* $i<j$

* $a_i>a_j$

使得这张图是二分图，求一种取相反数的方案。

分析：

首先要知道什么是二分图。

二分图有一个重要的判定方法，就是染色 BFS。而染色为什么是对的？

很显然，一张二分图不存在奇环。

所以这张图应不存在奇环。

观察什么时候才能不存在奇环。发现对于一个三元组 $(i,j,k)$ 满足：

* $i<j<k$

* $a_i>a_j>a_k$

此时 $i,j,k$ 形成一个奇环：$i→j,j→k,k→i$

如果超出 $3$ 个元满足类似的关系，都会形成奇环。

因此序列的最长下降子序列应不超过 $2$。

从《导弹拦截》一题得知，序列的最长下降子序列```=```序列的最长上升子序列个数

因此整个序列如果要满足二分图，其最长上升子序列个数不超过 $2$。

尝试把这个序列拆成 $2$ 个子序列。

设 $f_{i,j,p,q}$ 表示考虑了 $a_1...a_i$，第一个子序列接到了 $a_i$，第二个子序列接到了 $a_j$，其中 $p=0/1$ 表示 $a_i$ 取/不取相反数，$q$ 同理，在此情况下是否能分成两个子序列。

转移：枚举 $a_{i+1}$ 取/不取相反数，接到 $a_i/a_j$ 。

为了方便表示，令 $a_{i,0}$ 为原来 $a_i$ 的值， $a_{i,1}$ 为相反数。 

1. $a_{i,p}<a_{i+1,k}$ ：$f_{i,j,p,q}→f_{i+1,j,k,q}$

2. $a_{j,q}<a_{i+1,k}$ ：$f_{i,j,p,q}→f_{i+1,i,k,p}$

显然状态数为 $O(n^2)$ 级别。

我们这里的 DP 中 $f$ 的值只是“是否能”，并没有充分利用。

利用贪心思想，显然第一个子序列接到了 $a_i$，第二个子序列最后一个数越小越好（能接更多的数）。

改进状态：

设 $f_{i,p}$ 为第一个子序列接到了 $a_i$，$p=0/1$ 表示 $a_i$ 是否取相反数，第二个子序列最后一个数（取完相反数之后）的最小值。

枚举 $k=0/1$ 表示 $a_{i+1}$ 是否取相反数。

1. $a_{i,p}<a_{i+1,k}$ ：$f_{i,p}→f_{i+1,p}$

2. $f_{i,p}<a_{i+1,k}$ ：$a_{i,p}→f_{i+1,p}$

由于要打印方案，因此在转移的同时记录路径。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+10;
int w,n,a[maxn],f[maxn][2],g[2]={1,-1},s[maxn][2];
void upd(int i,int x,int p,int b)
{
	if(f[i][x]>p)
		f[i][x]=p,s[i][x]=b;
}
void print(int i,int x)
{
	if(i-1) print(i-1,s[i][x]);
	printf("%d ",g[x]*a[i]);
}
int main()
{
	scanf("%d",&w);
	while(w--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]),f[i][0]=f[i][1]=1e9;
		f[1][0]=-1e9; f[1][1]=-1e9;
		for(int i=1;i<n;i++)
		{
			for(int b=0;b<2;b++)
			{
				for(int c=0;c<2;c++)
				{
					int p=f[i][b];
					if(a[i]*g[b]<a[i+1]*g[c])
					{
						upd(i+1,c,p,b);
					}
					if(p<a[i+1]*g[c])
					{
						upd(i+1,c,a[i]*g[b],b);
					}
				}
			}
		}
		if(f[n][0]<1e9||f[n][1]<1e9) printf("YES\n");
		else printf("NO");
		if(f[n][0]<1e9) print(n,0);
		else if(f[n][1]<1e9) print(n,1);
		printf("\n");
	}
	return 0;
}
```


---

