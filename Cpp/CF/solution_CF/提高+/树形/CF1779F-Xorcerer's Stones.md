# Xorcerer's Stones

## 题目描述

Misha had been banned from playing chess for good since he was accused of cheating with an engine. Therefore, he retired and decided to become a xorcerer.

One day, while taking a walk in a park, Misha came across a rooted tree with nodes numbered from $ 1 $ to $ n $ . The root of the tree is node $ 1 $ .

For each $ 1\le i\le n $ , node $ i $ contains $ a_i $ stones in it. Misha has recently learned a new spell in his xorcery class and wants to test it out. A spell consists of:

- Choose some node $ i $ ( $ 1 \leq i \leq n $ ).
- Calculate the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) $ x $ of all $ a_j $ such that node $ j $ is in the subtree of $ i $ ( $ i $ belongs to its own subtree).
- Set $ a_j $ equal to $ x $ for all nodes $ j $ in the subtree of $ i $ .

Misha can perform at most $ 2n $ spells and he wants to remove all stones from the tree. More formally, he wants $ a_i=0 $ to hold for each $ 1\leq i \leq n $ . Can you help him perform the spells?

A tree with $ n $ nodes is a connected acyclic graph which contains $ n-1 $ edges. The subtree of node $ i $ is the set of all nodes $ j $ such that $ i $ lies on the simple path from $ 1 $ (the root) to $ j $ . We consider $ i $ to be contained in its own subtree.

## 说明/提示

Please refer to the following pictures for an explanation of the third test. Only the first $ 4 $ spells are shown since the last $ 2 $ do nothing. The first picture represents the tree initially with the number of stones for each node written above it in green. Changes applied by the current spell are highlighted in red.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1779F/87049d0f1cff376d7b36c99b33f175c4877519fa.png)

## 样例 #1

### 输入

```
2
13 13
1```

### 输出

```
1
1```

## 样例 #2

### 输入

```
7
5 2 8 3 4 1 31
1 1 2 2 3 3```

### 输出

```
-1```

## 样例 #3

### 输入

```
9
3 31 1 2 7 30 7 3 1
1 1 1 2 5 5 3 4```

### 输出

```
6
3 2 3 1 2 2```

# 题解

## 作者：namelessgugugu (赞：8)

提供一个复杂度 $O(nV)$ 的解法。

#### 题面

给定一棵 $n$ 个点的以 $1$ 为根的树，第 $i$ 个点有点权 $a_i$，令 $b_i$ 为 $i$ 的子树的 $a_i$ 异或和，对节点 $x$ 操作一次可以使得 $x$ 子树中所有节点的 $a_i$ 变成 $b_x$，求一组长度不超过 $2n$ 的操作序列使得最后所有 $a_i = 0$，或判断无解。

$2 \leqslant n \leqslant 2 \times 10^5, 0 \leqslant a_i < 32$。

#### 题解

先说明几个事实：

1. 如果 $b_1 = 0$，那么对 $1$ 进行一次操作就做完了。

2. 如果单独对一个节点 $x$ 做一次操作，如果 $siz_x$ 是奇数，则 $b_1$ 不变，如果是偶数，则 $b_1$ 变为 $b_i \oplus b_x$。

3. 如果一个合法操作序列中有 $x$，则删去操作序列中所有，位于 $x$ 之后的其他的 $x$ 子树中的节点不会改变其合法性。由于操作过一次 $x$ ，所以 $x$ 子树里面全是相同的 $a_i$，此时发现无论怎么操作 $y$，都相当于把偶数个 $a_i$ 变成了 $0$，并不会改变 $b_1$ 的值，所以它们本身就是无用的。

4. 由于有第三条事实，现在我们认为真正的合法序列一定满足不存在 $(x, y)$ 使得 $x$ 是 $y$ 的祖先且 $x$ 在 $y$ 的前面。那实际上就算存在 $(y, x)$ 这样的对，我们也可以把 $y$ 删掉。假设 $y, x$ 在操作序列中相邻，那考虑到操作 $y$ 之后 $b_x$ 变为 $b_x \oplus b_y$（此处 $b_x, b_y$ 指的是这两次操作前的值），再操作 $x$ 之后 $b_1$ 最终会变为 $b_1 \oplus b_x \oplus b_y \oplus b_x = b_1 \oplus b_x$，和单独操作一次 $b_x$ 效果相同。不相邻的情况也是类似的。

在上述事实的帮助下，我们发现原问题等价于找到若干个子树大小为偶数且两两之间不存在祖先关系的一些点，满足它们的 $b_i$ 异或和恰为 $b_1$。

因此可以使用 dfs 序 dp。将点根据 dfs 序重标号，设 $f_{i, j}$ 表示考虑了 $[1, i - 1]$ 是否被选，当前选定的节点 $b_i$ 异或和为 $j$ 是否存在方案。如果点 $i$ 被选（前提是 $siz_i$ 为偶数），则可以转移到 $f_{i + siz_i, j \oplus b_i}$，如果不选就转移到 $f_{i + 1, j}$。

复杂度 $O(nV)$，其中 $V = \max\{a_i\}$。

另外这样似乎可以求出最短的操作序列，但是我代码里没写。

#### 代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
const int N = 200005;
int n, a[N];
struct Edge
{
    int to, nxt;
} E[N << 1];
int head[N], tot;
inline void add(int f, int t)
{
    E[++tot] = {t, head[f]}, head[f] = tot;
    return;
}
int siz[N], val[N];
int dfn[N], tt;
void dfs(int x, int from)
{
    dfn[++tt] = x, siz[x] = 1, val[x] = a[x];
    for (int i = head[x]; i;i = E[i].nxt)
    {
        int y = E[i].to;
        if(y == from)
            continue;
        dfs(y, x), siz[x] += siz[y], val[x] ^= val[y];
    }
    return;
}
std::pair<int, int> f[N][32];
std::vector<int> ans;
int main(void)
{
    scanf("%d", &n);
    for (int i = 1; i <= n;++i)
        scanf("%d", a + i);
    for (int i = 2, p;i <= n;++i)
        scanf("%d", &p), add(p, i);
    dfs(1, 0);
    for (int i = 1;i <= n + 1;++i)
        for (int j = 0; j < 32;++j)
            f[i][j] = {-1, -1};
    f[1][val[1]] = {0, 0};
    for (int i = 1;i <= n;++i)
        for (int j = 0; j < 32;++j)
            if(f[i][j].first != -1)
            {
                int v = (siz[dfn[i]] & 1) ? 0 : val[dfn[i]];
                f[i + 1][j] = {i, j};
                f[i + siz[dfn[i]]][j ^ v] = {i, j};
            }
    if(f[n + 1][0].first == -1)
        return puts("-1"), 0;
    int u = n + 1, v = 0;
    while(u != 0)
    {
        int tu = f[u][v].first, tv = f[u][v].second;
        if(u - tu == siz[dfn[tu]])
            ans.push_back(dfn[tu]);
        u = tu, v = tv;
    }
    ans.push_back(1);
    printf("%d\n", (int)ans.size());
    for(int x : ans)
        printf("%d ", x);
    return 0;
}
```

---

## 作者：Mars_Dingdang (赞：5)

翻译是我给的，但题解是翻译通过之后几天才写的，原因是口胡完了不想动代码。

## 题目大意
给定一棵 $n(n\le 2\times 10^5)$ 个节点的树，第 $i$ 个节点有非负权值 $a_i\le 31$。定义一次操作为：

- 选择一个节点 $i$，$1\le i\le n$。
- 计算以 $i$ 为根的子树（包括 $i$ 本身）内的所有节点权值的异或和 $x$。
- 将以 $i$ 为根的子树（包括 $i$ 本身）内的所有节点权值赋值为 $x$。

已知这一操作最多可以执行 $2n$ 次。Mars 想知道是否可以通过执行若干次这一操作使得树上所有节点权值均为 $0$。

如果可以，输出第一行一个非负整数 $q$ 表示操作次数，第二行为 $q$ 个正整数，表示每次操作选择的节点编号 $i$；如果不可以，输出一行一个整数 $-1$。

你不需要最小化 $q$，输出任意一组解即可。

## 大体思路 
记 $sz_u$ 表示 $u$ 为根的子树大小，$son_u$ 表示 $u$ 的儿子个数。

这题口胡之所以容易，是因为很快能够发现两个结论。

1. $sz_u$ 为偶数的子树，只需要对 $u$ 操作一次即可使得子树内所有点权异或和为 $0$。

2. $sz_u$ 为奇数的子树，无论对 $u$ 操作多少次，子树内点权异或和不变。

因此，对奇数大小的子树的根操作是无意义的，对偶数大小的子树的根节点最多操作两次（而且只有最后全部清零时才会操作两次），因此操作次数不超过 $2n$ 是必然的。

然后，我们可以使用树形 DP 求解这一问题。这很明显是一个背包。

记 $F(u,x,i)$ 表示考虑 $u$ 的前 $i$ 个儿子节点，能否是的以 $u$ 为根的子树的点权异或和为 $x$。转移时枚举儿子节点 $v_i$ 以及异或和即可，时间复杂度 $O(n\omega^2)$，其中 $\omega\le 31$ 表示值域。

至于输出方案，把原先 DP 的 $01$ 状态改为记录转移来的异或和即可，初始全部设为 $-1$，对于 $sz_u$ 为偶数的情况，令 $F(u,0,son_u)=-2$ 做特殊标记。

由于 $\sum son_u$ 是 $O(n)$ 的，直接开 DP 数组会 MLE，采用 $\texttt{std::vector}
$ 即可。

## 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 2e5 + 5;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
int n, val[maxn], sz[maxn], son[maxn];
vector <int> e[maxn];
vector <int> f[maxn][35]; // 一开始脑子糊涂了，其实值域<=31
inline void dfs(int u, int fa) {
	sz[u] = 1;
	rep(j, 0, 32) rep(t, 0, son[u]) f[u][j][t] = -1;
	f[u][val[u]][0] = 0;
	rep(i, 1, son[u]) {
		int v = e[u][i - 1];
		dfs(v, u);
		sz[u] += sz[v];
		rep(j, 0, 32) if(f[u][j][i - 1] != -1)
			rep(k, 0, 32) if(f[v][k][son[v]] != -1) 
				f[u][j ^ k][i] = k;
	}
	if(!(sz[u] & 1)) f[u][0][son[u]] = -2;
}
vector <int> ans;
inline void output(int u, int x) {
	if(f[u][x][son[u]] == -2) {
		ans.push_back(u);
		return;
	}
	Rep(i, son[u], 1) {
		int v = e[u][i - 1];
		output(v, f[u][x][i]);
		x ^= f[u][x][i];
	}
}
int main () {
	read(n);
	rep(i, 1, n) read(val[i]);
	
	rep(i, 2, n) {
		int p; read(p);
		e[p].push_back(i);
		son[p] ++;
	}
//	rep(i, 1, n) printf("%d %d\n", son[i], e[i].size());
	rep(i, 1, n) 
		rep(j, 0, 32) f[i][j].resize(son[i] + 1);
	dfs(1, 0);
	if(f[1][0][son[1]] == -1) return writeln(-1), 0;
	output(1, 0);
	ans.push_back(1);
	writeln(ans.size());
	for(auto x : ans) write(x), putchar(' ');
	return 0;
}
```

## 后记
过年前开题的，回老家一路上口胡的，大年三十写完的。

希望今年春晚好看，祝大家新年快乐！

---

## 作者：Rushroom (赞：3)

## 题意

给定一个树，节点 $i$ 权值为 $a_i$。你可以执行至多 $2n$ 次操作，每次操作可以将一个子树内所有点变成它们的异或和。求一种可行方案使得所有数变成 $0$。无解输出 $-1$。

$n\le 2\cdot 10^5,0\le a_i \le 31$

## 题解

可以发现，如果对大小为奇数的子树执行操作，所有权值的异或和不变；如果对大小为偶数的子树执行操作，则子树内异或和变为 $0$。而当我们将整棵树的异或和变为 $0$ 后，只需要再对整棵树进行一次操作即可全部清零。

设 $f_{i,j}=0/1$ 表示能否使以 $i$ 为根的子树内异或和为 $j$。从子节点转移上来即可。如果以 $i$ 为根的子树大小为偶数，则 $f_{i,0}=1$ ，即对这棵树执行一次操作。

恶心的是居然要输出方案！写个路径还原，同时如果是执行操作的地方要打上标记。

这样做好像只要 $n$ 次操作？

时间复杂度 $O(nw^2)$，其中 $w=32$。$2\cdot 10^5 \times 32^2\approx 2\cdot 10^8$。给了 4s，能过。

## Code

赛时写的代码操作次数有点多。这里放下优化后的。

```cpp
const int N = 200005;
int n, a[N], fa, son[N], siz[N];
vector<int>g[N];
vector<int>dp[N][32];
void dfs(int x) {
    rep(i, 32)rep(j, son[x] + 1)dp[x][i][j] = -1;
    dp[x][a[x]][0] = 0;
    siz[x] = 1;
    rep(i, son[x]) {
        int y = g[x][i];
        dfs(y);
        siz[x] += siz[y];
        rep(m1, 32)rep(m2, 32) {
            if (dp[x][m1][i] != -1 && dp[y][m2][son[y]] != -1) {
                dp[x][m1 ^ m2][i + 1] = m2;
            }
        }
    }
    if (siz[x] % 2 == 0)dp[x][0][son[x]] = -2;
}
vector<int>ans;
void getans(int x, int val) {
    if (dp[x][val][son[x]] == -2) {
        ans.pb(x + 1);
        return;
    }
    for (int i = son[x] - 1;i >= 0;i--) {
        int y = g[x][i];
        getans(y, dp[x][val][i + 1]);
        val ^= dp[x][val][i + 1];
    }
}
void solve() {
    cin >> n;
    rep(i, n)cin >> a[i];
    rep(i, n - 1) cin >> fa, fa--, son[fa]++, g[fa].pb(i + 1);
    rep(i, n)rep(j, 32)dp[i][j].resize(son[i] + 1);
    dfs(0);
    if (dp[0][0][son[0]] == -1)cout << -1;
    else {
        getans(0, 0);
        ans.pb(1);
        cout << ans.size() << endl;
        for (int x : ans)cout << x << ' ';
    }
}
```



---

## 作者：happybob (赞：0)

当 $n$ 是偶数时显然，只需要对根操作两次即可。

$n$ 是奇数时，观察到最后一步必然操作根，且操作前所有数异或为 $0$。

又发现对于每个 $u$，如果 $u$ 子树大小是偶数，两次操作就可以把 $u$ 子树内的所有值变为 $0$。

问题转化为选若干互不为祖先的点，使得每个点子树大小是偶数，且每个点的子树异或值异或后等于原树所有数异或。

注意到值域很小，考虑背包。$f_{u,i}$ 表示以 $u$ 为根是否可以凑出异或为 $i$。转移很朴素。由于要输出构造所以记录一下方案即可。每个点至多操作 $2$ 次，总共不超过 $2n$ 次。时间复杂度 $O(nV^2)$。

---

