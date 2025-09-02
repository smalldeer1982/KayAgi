# Alice and Recoloring 2

## 题目描述

给定一个 $n$ 行 $m$ 列的目标矩阵，矩阵元素只有 W 或 B ，并且你有一个初始矩阵，元素全为 W 。

现在你可以矩阵实施以下操作：

使用一块钱，选定一个包含 $(1,1)$ 的子矩阵，把矩阵中的元素全部反转（ W 变 B ， B 变 W ）。

使用三块钱，选定一个包含 $(n,1)$ 的子矩阵，把矩阵中的元素全部反转。

使用四块钱，选定一个包含 $(1,m)$ 的子矩阵，把矩阵中的元素全部反转。

使用两块钱，选定一个包含 $(n,m)$ 的子矩阵，把矩阵中的元素全部反转。

现在需要你求出把初始矩阵变为目标矩阵最少需要几块钱。

## 样例 #1

### 输入

```
3 3
WWW
WBB
WBB```

### 输出

```
2```

## 样例 #2

### 输入

```
10 15
WWWBBBWBBBBBWWW
BBBBWWWBBWWWBBB
BBBWWBWBBBWWWBB
BBWBWBBWWWBBWBW
BBBBWWWBBBWWWBB
BWBBWWBBBBBBWWW
WBWWBBBBWWBBBWW
WWBWWWWBBWWBWWW
BWBWWBWWWWWWBWB
BBBWBWBWBBBWWBW```

### 输出

```
68```

# 题解

## 作者：syksykCCC (赞：17)

有一张 $n \times m$ 的方格图，初始全白，目标状态给定。

有 4 种操作（反转的意思是黑 $\to$ 白，白 $\to$ 黑）：

* 反转一个包含 $(1, 1)$ 的子矩形，花费 $1$。
* 反转一个包含 $(n, 1)$ 的子矩形，花费 $3$。
* 反转一个包含 $(1, m)$ 的子矩形，花费 $4$。
* 反转一个包含 $(n, m)$ 的子矩形，花费 $2$。

求达成目标状态的最小花费。

$1 \le n, m \le 500$。

2s, 256MB

---

**引理 1**：第 2 和第 3 种操作不会用到。

> **证明**：考虑到不管是第 2 种还是第 3 种操作，都可以用两次第 1 种操作代替，而且代价显然更优。所以永远不会使用第 2 和第 3 种操作。

现在的问题就转化为了只存在第 1 和第 4 种操作的情况了。

将目标状态与初始状态对换，即给定一个初始有黑白两色的方格图，花最小的代价使得全部变成白色。

矩形反转显然是不好处理的，考虑弄一个类似前缀和的东西来优化掉。

将黑色视为 $1$，白色视为 $0$。构造一个数组 $a$，其中 $a_{i, j} = s_{i, j} \oplus s_{i + 1, j} \oplus s_{i, j + 1} \oplus s_{i + 1, j + 1}$（超出网格的部分默认是白色）。

非常显然，当 $a$ 数组全部变为 $0$ 时，$s$ 数组也就全部变为了 $0$。

观察 1, 4 两种操作对 $a$ 数组的影响，发现是：

* 对于第 1 种操作，只会有 1 个格子的 $a$ 发生了反转。
* 对于第 4 种操作，会有 4 个格子的 $a$ 发生反转，且这 4 个格子形如 $(x, y)$，$(n, y)$，$(x, m)$，$(n, m)$。记这样的操作为 $op(x, y)$。

**引理 2**：不会同时使用 $op(x, y_1)$ 和 $op(x, y_2)$。同理不会同时使用 $op(x_1, y)$ 和 $op(x_2, y)$。

> **证明**：以前一种为例，$(n, m)$ 和 $(x, m)$ 都被反转了两次，所以不会发生改变。那么也就是花费了 $4$ 的代价来反转了 $2\times 2=4$ 个格子。这显然可以被第 1 种操作代替。

**引理 3**：除非 $(x, y)$，$(n, y)$ 和 $(x, m)$ 都为 $1$，才会使用 $op(x, y)$。

> **证明**：如果这中间有一个不为 $1$，那么这次操作就产生了一个错误的反转。为了达成最终目标，显然会使用一次第 1 种操作把它反转回来（注：不会是另一个第 4 种操作，根据引理 2 可以得知）。那么仅仅是反转了另外 3 个格子，代价都至少为 $1 + 2 = 3$，完全可以使用第 1 种操作代替。

于是就可以做题了，建立一个二分图，左部有 $n - 1$ 个点代表行，右部有 $m - 1$ 个点代表列。

对于 $(x, y)$，如果它满足引理 3 的条件，则把左部的 $x$ 和右部的 $y$ 连边。

求这个二分图的最大匹配数 $k$ 即可。答案为 $\textit{rem} - k$。$\textit{rem}$ 表示剩下的 $1$ 的个数。

我使用的是 dinic 求二分图最大匹配，时间复杂度为 $O(n^2 \sqrt{n})$。

```cpp
#include <bits/stdc++.h>
const int N = 505;
char str[N][N];
int n, m, cnt = -1, a[N][N], h[N << 1], S, T;

struct edge {
	int v, w, nxt;
} e[N * N * 2];

void add_edge(int u, int v) {
	e[++cnt] = (edge){v, 1, h[u]}; h[u] = cnt;
	e[++cnt] = (edge){u, 0, h[v]}; h[v] = cnt;
}

int que[N << 1], hd, tl, lev[N << 1];
 
bool bfs() {	 
	memset(lev, 0, sizeof(lev));
	hd = tl = lev[S] = 1; que[1] = S;
	while(hd <= tl) {
		int u = que[hd++];
		for(int i = h[u]; ~i; i = e[i].nxt) {
			int v = e[i].v;
			if(!lev[v] && e[i].w > 0) {
				que[++tl] = v;
				lev[v] = lev[u] + 1;
			}
		}
	}
	return lev[T];
}

int cur[N << 1];
 
int dfs(int u, int can_flow) {
	if(u == T) return can_flow;
	int res_flow = 0;
	for(int &i = cur[u]; ~i; i = e[i].nxt) {
		int v = e[i].v;
		if(lev[v] == lev[u] + 1 && e[i].w > 0) {
			int will_flow = dfs(v, std::min(can_flow, e[i].w));
			res_flow += will_flow;
			can_flow -= will_flow;
			e[i ^ 1].w += will_flow;
			e[i].w -= will_flow;
			if(!can_flow) break;
		}
	}
	if(!res_flow) lev[u] = 0;
	return res_flow;
}
 
int dinic() {
	int res = 0; 
	while(bfs()) {
		memcpy(cur, h, sizeof(h));
		res += dfs(S, INT_MAX);
	}
	return res;
}

int main() {
	memset(h, -1, sizeof(h));

	scanf("%d %d", &n, &m); 
	S = n + m + 1; T = n + m + 2;
	for(int i = 1; i <= n; i++) {
		scanf("%s", str[i] + 1);
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			a[i][j] = (str[i][j] == 'B') ^ (str[i][j + 1] == 'B') ^ (str[i + 1][j] == 'B') ^ (str[i + 1][j + 1] == 'B');
		}
	}
	for(int i = 1; i < n; i++) {
		for(int j = 1; j < m; j++) {
			if(a[i][j] && a[n][j] && a[i][m]) {
				add_edge(i, j + n);
			}
		}
	}
	for(int i = 1; i < n; i++) add_edge(S, i);
	for(int j = 1; j < m; j++) add_edge(j + n, T);

	int k = dinic(), ans = 0;
	
	a[n][m] ^= (k & 1);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			ans += a[i][j];
		}
	}
	ans -= k;
	printf("%d\n", ans);
	return 0;
}
```



---

## 作者：fishing_cat (赞：8)

[传送门](https://codeforces.com/problemset/problem/1592/F2)

### 题意

有四种操作，要求将全白的一个矩形通过操作转化为给定的矩形。最小化花费。

### 做法

为了方便操作，考虑用类似前缀和的思想，对于给定矩阵 $a$，构造一个新矩阵 $c$，满足 $c_{i,j} = (a_{i,j} + a_{i+1, j} + a_{i,j+1} + a_{i+1,j+1}) \bmod 2$，也可以直接看作是这四个格的异或和。自然，多出来的 $a_{x,m}$ 这列和 $a_{n,x}$ 这行，默认为 $0$。

逆向操作，看成将给定矩阵转化成初始矩阵的最小花费。将 $a$ 矩阵转化为初始矩阵即将 $c$ 矩阵准化为全白的一个矩阵。

分别观察四种操作，对于操作一，在构造后的 $c$ 中，就是只将 $c_{i,j}$ 反转。     
对于操作二，发现可以用两次操作一代替，并且两次操作一花费更小。   
对于操作三，发现也可以用两次操作一代替，并且两次操作一花费更小。  
对于操作四，就是将 $c_{n,m}$，$c_{i,m}$，$c_{n,j}$ 和 $c_{i,j}$ 都反转。与这道题的[弱化版](https://www.luogu.com.cn/problem/CF1592F1)不一样的就是这里，可以发现只有在 $c_{i,m}$，$c_{n,j}$ 和 $c_{i,j}$ 都为黑时，操作四才是优的。    
以及，在进行操作四时，同一行或同一列最多使用一次，不然重复操作是可以用操作一直接代替的，所以只用在符合条件 $c_{i,m}$，$c_{n,j}$ 和 $c_{i,j}$ 都为黑的行和列连边，跑二分图最大匹配即可。

所以，只需要考虑操作一和操作四，并且用匈牙利跑出操作四的最大匹配，就可以保证是最优的。

具体实现，对于构造出的 $c$，记录出现的黑的个数为 $ans$；对于没有一个匹配，既可以优化掉一个花费，计这个总数为 $res$；然后对于 $c_{n,m}$ 这个点单独计算，发现 $res$ 其实也是这个点反转的次数，就可以计算出这个点是否还会有一次单独花费。      
最后得到的 $ans - c_{n,m} - res + (c_{n,m} \oplus  (res\bmod 2))$ 就是最优花费。

时间复杂度 $O(n^3)$。

### code

[link](https://codeforces.com/contest/1592/submission/288660837)

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define il inline
using namespace std;
/*快读省了*/
ll n, m, a[510][510], c[510][510], ans, res;
ll vis[1510], col[1510]; 
char s;
vector<ll> eg[510];

bool dfs(ll u, ll tag) { // 匈牙利
	if (vis[u] == tag) return 0;
	vis[u] = tag;
	for (auto v : eg[u]) {
		if ((col[v] == 0) || dfs(col[v] , tag)) {
			col[v] = u;	
			return 1;
		}
	}	
	return 0;
}


int main() {
	read(n); read(m);
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j++) {
			cin >> s;
			if (s == 'B') 
				a[i][j] = 1;
		}

	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j ++) {
			c[i][j] = (a[i][j] + a[i+1][j] + a[i][j+1] + a[i+1][j+1]) % 2;
			if (c[i][j] == 1) ans++;
		}
	for (int i = 1; i <= n-1; i++) // 注意不要超了，对于最后一列不需要连边
		for (int j = 1; j <= m-1; j++) // 同上 ！！！
			if (c[i][j] == 1 && c[n][j] == 1 && c[i][m] == 1) 
				eg[i].push_back(j + 1000);

	for (int i = 1; i <= n; i++) {
		res += dfs(i, i);
	}
	ans -= c[n][m];
	cout << ans - res + (c[n][m] ^ (res & 1)) << "\n";
	return 0;
}
```

---

## 作者：Alex_Wei (赞：6)

> ### *1592F2. [Alice and Recoloring 2](https://www.luogu.com.cn/problem/CF1592F2) 2800
> 
> 摘自 [CF 比赛记录](https://www.cnblogs.com/alex-wei/p/codeforces_compete_upsolve_virtual_participation_record.html)（密码可以私我 qwq）。

一些约定见 [F1 题解](https://www.luogu.com.cn/blog/AlexWei/solution-cf1592f1)。

---

仍然是神仙题。操作 $2$ 的代价从 $3$ 减小到了 $2$。虽然 F1 操作 $2$ 最多使用 $1$ 次的结论不再适用，但我们仍可以发掘一些结论：

**observation 1：对于所有操作 $2$ 的格子 $(x_i,y_i)$，一定满足 $x_i$ 互不相同且 $y_i$ 互不相同**。证明是容易的，反证说明若存在则只改变 $4$ 个格子状态不优于四次操作 $1$。

**observation 2：我们只会操作 $p_{x,y}=p_{x,m}=p_{n,y}=1$ 的格子**。这是显然的，因为若上述三个格子至少有一个为 $0$，则不如花 $2$ 的代价进行两次操作 $1$ instead of 花 $2+1=3$ 的代价进行一次操作 $2$ 和至少一次操作 $1$（根据 observation 1 易得因操作 $2$ 由 $0$ 变成 $1$ 的格子必须用操作 $1$ 而不是操作 $2$ 弥补）。

第一个结论给予了我们很清晰的**二分图匹配**思路，第二个结论说明两部点之间连边的条件。因此根据上述结论建出左部点个数为 $n-1$，右部点个数为 $m-1$ 的二分图，跑一遍二分图匹配即可。时间复杂度 $\mathcal{O}(n^{1.5}m)$。

```cpp
const int N = 1e3 + 5;
const int M = N * N;

int n, m, T, ans, flow, a[N][N], p[N][N];
char mp[N][N];

int cnt = 1, hd[N], to[M], nxt[M], lim[M];
void add(int u, int v, int w) {
	nxt[++cnt] = hd[u], hd[u] = cnt, to[cnt] = v, lim[cnt] = w;
	nxt[++cnt] = hd[v], hd[v] = cnt, to[cnt] = u, lim[cnt] = 0;
}

int dis[N], cur[N];
bool BFS() {
	queue <int> q;
	mem(dis, 0x3f, N), cpy(cur, hd, N);
	dis[0] = 1, q.push(0);
	while(!q.empty()) {
		int t = q.front(); q.pop();
		if(t == T) return 1;
		for(int i = hd[t]; i; i = nxt[i]) {
			int it = to[i];
			if(lim[i] > 0 && dis[it] > 1e9)
				dis[it] = dis[t] + 1, q.push(it);
		}
	} return 0;
}
int Dinic(int id, int rest) {
	if(id == T || !rest) return rest;
	int flow = 0;
	for(int i = cur[id]; i && rest; i = nxt[i]) {
		cur[id] = i;
		int c = min(rest, lim[i]), it = to[i];
		if(c && dis[id] + 1 == dis[it]) {
			int k = Dinic(it, c);
			if(k == 0) dis[it] = 0;
			lim[i] -= k, lim[i ^ 1] += k;
			rest -= k, flow += k;
		}
	} return flow;
}

int main(){
	cin >> n >> m, T = n + m;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			cin >> mp[i][j], p[i][j] = mp[i][j] == 'B';
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			a[i][j] = p[i][j] ^ p[i][j + 1] ^ p[i + 1][j] ^ p[i + 1][j + 1];
	for(int i = 1; i < n; i++)
		for(int j = 1; j < m; j++)
			if(a[i][j] && a[i][m] && a[n][j])
				add(i, n + j, 1);
	for(int i = 1; i < n; i++) add(0, i, 1);
	for(int i = 1; i < m; i++) add(n + i, T, 1);
	while(BFS()) flow += Dinic(0, n + m);
    a[n][m] ^= flow & 1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) ans += a[i][j];
	cout << ans - flow << endl;
    return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：4)

管理辛苦了！

反复发现性质，然后逐步转化的普通题，但是我为什么不会？？？
# 
一个很容易看到的事情是，$(n,1)$ 操作和 $(1,m)$ 操作都是可以使用两次 $(1,1)$ 操作解决的。

那么我们只需要考虑 $(1,1)$ 操作和 $(n,m)$ 操作即可。

将前者记为操作一，后者为操作二。

# 

使用操作题的常规考虑手段：考察每次操作中的不变量。

如果让输入的字符串记为 $s$，$a_{i,j}=[s_{i,j}=\texttt{W}]$，不难想到记录 $b_{i,j}=a_{i,j}\operatorname{xor} a_{i+1,j}\operatorname{xor}a_{i+1,j}\operatorname{xor} a_{i+1,j+1}$。

那么操作一相当于使一个 $b_{i,j}$ 取反，操作二相当于使 $b_{i,j},b_{i,m},b_{n,j},b_{n,m}$ 取反。

目标便是让 $b$ 全为 $0$。

# 
贪心地，考虑充分利用操作二。

但是还不能直接贪心。

考虑如果对 $(x,y_1),(x,y_2)$ 分别使用了一次操作二，此时花费了 $4$，但是只改变了 $4$ 个点，弗若直接对四个点分别操作一，所以操作二更优的必要条件是每一行使用的操作二不超过一次。

每一列同理。

所以我们得出一个结论：对每行/列至多执行一次操作二。

这里已经隐隐有点最大匹配的影子了。

# 
但是还没结束。

我们发现：如果 $b_{x,y}+b_{n,m}+b_{n,y}+b_{m,x}\le 2$，操作二不执行也罢。

所以操作二执行的另一必要条件是 $b_{x,y}+b_{n,y}+b_{m,x}=3$。

所以只需要对符合上述条件的点对 $(x,y)$ 连边，以行为左部，列为右部跑最大匹配即可。

最后记得处理 $b_{n,m}$ 的状态。

# 
细节看代码：

```cpp
const int N=503,NN=N<<1;
int n,m,mc[NN],vis[NN],res,ans;
bool a[N][N];
sd vector<int>G[NN];
bool dfs(int u,int tg)
{
  if(vis[u]==tg) return false;
	vis[u]=tg;
	for(int v:G[u]) if(!mc[v]||dfs(mc[v],tg)) return mc[v]=u,true;
	return false;
}
void Solve()
{
  rd(n,m);
  for(int i=1;i<=n;++i)
  {
    char s[N];
    rd(s);
    for(int j=0;j<m;++j) a[i][j+1]=s[j]=='B';
  }
  for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) a[i][j]^=a[i+1][j]^a[i][j+1]^a[i+1][j+1],ans+=a[i][j];
  for(int i=1;i<n;++i) for(int j=1;j<m;++j) if(a[i][j]&&a[i][m]&&a[n][j]) G[i].push_back(j+n);
  for(int i=1;i<=n;++i) res+=dfs(i,i);
  ans-=a[n][m],wrt(ans-res+(a[n][m]^res&1));
  return;
}
```

[$\color{green}{\checkmark}$](https://codeforces.com/contest/1592/submission/214581732)。

---

## 作者：dead_X (赞：3)

## 思路
首先，略微观察之后可以得到一个结论：翻转包含 $(n,1),(1,m)$ 的矩形必定不优，因为它们可以用 $2$ 个包含 $(1,1)$ 的矩形构造出来。

于是题目变成了只能翻转包含 $(1,1)$ 或 $(n,m)$ 的矩形。

将矩形做一个二阶差分，我们发现翻转包含 $(n,m)$ 的矩形相当于在差分矩阵上修改一个点（注意修改的点一定不在第一行第一列），而在这些位置翻转包含 $(1,1)$ 的矩形会修改 $(1,1),(x,1),(1,y),(x,y)$。

在反转完 $x,y>1$ 的位置后，我们会接着回去翻转 $x=1$ 或 $y=1$ 的矩形，就完成了整个过程。

也就是说，我们记 $f_i$ 为第 $i$ 行是否翻转，$g_j$ 为第 $j$ 行是否翻转，$h$ 为 $(1,1)$ 是否需要最后翻转。一次 $(1,1)$ 的操作等价于翻转 $f_i,g_j,h$，消耗 $1$；而一次 $(n,m)$ 的操作什么都不翻转，消耗 $2$。

也就是说，如果我们翻转 $(n,m)$ 的矩形，可能会比翻转 $(1,1)$ 的矩形多花 $+2,0,-2$ 的费用。

这次我们发现可能 $+2,0,-2$ 都会用到一些，怎么办呢？

于是我们反过来考虑，直接全选了，最后撤销一些。

所以问题转化成了我们可以对于每个为 $1$ 的格子选或者不选，选一个格子如果 $f_x,g_y,c$ 为 $0$ 答案加 $2$，然后答案 $-1$。

这样我们就发现显然 $f_x,g_y$ 只会从 $1$ 变成 $0$ 至多一次，而 $c$ 在每次答案 $-1$ 的时候显然严格不劣。

于是直接上二分图匹配，时间复杂度 $O(n^3)$。
## 代码
```cpp
char s[503][503];
bool a[503][503];
bool b[503][503];
bool f[503],g[503];
bool ovo[503];
signed main()
{
	int n=read(),m=read();
	for(int i=1; i<=n; ++i) scanf("%s",s[i]+1);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) a[i][j]=(s[i][j]=='B');
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) b[i][j]=(a[i][j]!=a[i][j-1]);
	for(int i=n; i>=1; --i)
		for(int j=1; j<=m; ++j) b[i][j]=(b[i][j]!=b[i-1][j]); 
	int c=b[1][1];
	int ans=0;
	for(int i=2; i<=n; ++i)
		for(int j=2; j<=m; ++j)
			ans+=2*b[i][j];
	for(int i=2; i<=n; ++i) f[i]^=b[i][1],c^=b[i][1];
	for(int j=2; j<=m; ++j) g[j]^=b[1][j],c^=b[1][j];
	
	// for(int i=1; i<=n; ++i,puts(""))
		// for(int j=1; j<=m; ++j) printf("%d",b[i][j]);
	// printf("%d\n",c);
	// for(int i=1; i<=n; ++i) printf("%d",f[i]);
	// puts("");
	// for(int i=1; i<=m; ++i) printf("%d",g[i]);
	// puts("");
	int A=0,B=0;
	for(int i=2; i<=n; ++i)
	{
		bool tag=0;
		for(int j=2; j<=m; ++j) if(b[i][j])
			--ans,g[j]^=1,f[i]^=1,c^=1;
		if(f[i]) ++ans;
	}
	for(int j=1; j<=m; ++j) ans+=g[j];
	for(int i=2; i<=n; ++i)
		for(int j=2; j<=m; ++j)
			if(f[i]&&g[j]&&b[i][j]) F.addedge(i,j);
	int C=F.main(n,m);
	ans+=min(c,(c^(C&1))-C);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：james1BadCreeper (赞：2)

不难发现 $2,3$ 操作是小丑，我们都可以使用 $1$ 操作来代替。
 
先考虑 F1。将 `W` 看成 $0$，`B` 看成 $1$，然后考虑什么东西要被翻转。如果它自己是 $1$ 需要翻吗？不一定！$(i,j)$ 是 $1$ 需要翻，当且仅当 $(i+1,j),(i,j+1),(i+1,j+1)$ 当中有 $0$ 或 $2$ 个是 $1$。如果它自己不是 $1$ 就不需要翻吗？也不是，同样是那三个位置，如果当中有 $1,3$ 个 $1$ 就需要翻。

令 $a_{i,j}=s_{i,j}\oplus s_{i,j+1}\oplus s_{i+1,j}\oplus s_{i+1,j+1}$，只考虑 $1$ 操作，答案就是 $\sum a_{i,j}$。

$4$ 干了什么？相当于翻了 $a_{i,j},a_{i,m},a_{n,j},a_{n,m}$，显然，它只能使用 $1$ 次。[代码](https://codeforces.com/contest/1592/submission/214605318)。

再考虑 F2。我们考虑在刚才的基础上加一些限制。

首先，基于之前说过的 $4$ 干的事情，我们只会操作 $a_{i,j},a_{i,m},a_{n,j}$ 均为 $1$ 的，否则不如来 $1$ 操作。然后这样就发现了一个事情，一次操作 $a_{i,j}$ 之后会将 $a_{i,m}$ 和$a_{n,j}$ 废掉，也就是说，同行同列最多进行一次 $4$ 操作。

这看上去很像一个二分图匹配问题了！将每行抽象为左部点，每列抽象为右部点（前提是 $1$），然后根据 $a_{i,j}$ 进行连边。

```cpp
#include <bits/stdc++.h>
using namespace std; 

int n, m, a[505][505]; 
char s[505][505]; 

struct Graph {
	struct edge {
    	int v, w; 
    	edge(int v = 0, int w = 0) : v(v), w(w) {}
	};
    int S, T, cur[1005], d[1005]; 
    vector<edge> edges; 
    vector<int> G[1005]; 
    inline void addedge(int u, int v, int w) {
        edges.emplace_back(edge(v, w));
        G[u].emplace_back(edges.size() - 1);
        edges.emplace_back(edge(u, 0));
        G[v].emplace_back(edges.size() - 1);  
    }
    bool bfs(void) {
        memset(cur, 0, sizeof cur); memset(d, -1, sizeof d);
        queue<int> q; q.push(S); d[S] = 1; 
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = 0; i < G[u].size(); ++i) {
                edge &e = edges[G[u][i]];
                if (e.w && d[e.v] == -1) {
                    d[e.v] = d[u] + 1; q.push(e.v); 
                    if (e.v == T) return true; 
                }
            }
        }
        return false; 
    }
    int dinic(int x, int res) {
        if (x == T) return res; 
        int flow = 0; 
        for (int i = cur[x]; i < G[x].size() && res; ++i) {
            edge &e = edges[G[x][i]]; cur[x] = i; 
            int c = min(res, e.w); 
            if (d[e.v] == d[x] + 1 && c) {
                int k = dinic(e.v, c); flow += k; res -= k; 
                edges[G[x][i]].w -= k; edges[G[x][i] ^ 1].w += k; 
            }
        }
        if (!flow) d[x] = -1;
        return flow; 
    }
    int maxFlow(int s, int t) {
        S = s, T = t; 
        int flow, maxflow = 0; 
        while (bfs()) while (flow = dinic(S, 1e9)) maxflow += flow; 
        return maxflow;
    }
} G;

int main(void) {
	ios::sync_with_stdio(0); 
	cin >> n >> m; int ans = 0; 
	for (int i = 1; i <= n; ++i) cin >> s[i] + 1;
  	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) a[i][j] = (s[i][j] != 'W');
  	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) a[i][j] ^= a[i + 1][j] ^ a[i][j + 1] ^ a[i + 1][j + 1];
  	for (int i = 1; i < n; ++i) for (int j = 1; j < m; ++j) if (a[i][j] && a[i][m] && a[n][j]) G.addedge(i, n + j, 1); 
  	for (int i = 1; i < n; ++i) if (a[i][m]) G.addedge(0, i, 1); 
  	for (int i = 1; i < m; ++i) if (a[n][i]) G.addedge(i + n, n + m + 1, 1); 
	int flow = G.maxFlow(0, n + m + 1); a[n][m] ^= (flow & 1); 
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) ans += a[i][j];
	return cout << ans - flow << "\n", 0; 
}
```

---

## 作者：tzl_Dedicatus545 (赞：1)

注意到 $2,3$ 操作是纯扯淡的。因为你可以用 $2$ 的代价使用 $1$ 操作模拟这些操作。

现在相当于是你只有 $1,4$ 操作。 

神秘的，我们对原矩形做二维差分，然后操作一就是单点翻转 $(x,y)$，操作四就是翻转 $(x,m),(n,y),(n,m),(x,y)$。

不难发现对于每行每列都只用一次操作四是不劣的，要不然你直接用操作一来模拟不会让代价更大，更进一步的，我们发现只有除了 $(n,m)$ 以外的数都是 $1$ 才优，于是我们直接跑一下二分图最大匹配即可。

---

## 作者：toolong114514 (赞：1)

# CF1592F2 Alice and Recoloring 2 题解
神奇的题目，~~要长脑子了~~。
## 题面大意
[传送门。](https://www.luogu.com.cn/problem/CF1592F2)
## 解题思路
题面给定了 4 种操作，看上去太多了，能不能消掉一些呢？

我们发现，操作 2 和 操作 3 是没有必要的，因为可以用类似差分的思想，将其转化为两次 1 操作，花费 2 元，显然更优。

接下来考虑操作 1 和操作 4 的性质。

规定 ```W``` 为 $0$，```B``` 为 $1$，原矩阵为 $A$。

我们可以将题目的过程到过来，让目标矩阵变回全 $0$ 矩阵。

这样做是与原问题等价的。

定义一个 $n\times m$ 的新矩阵 $B$，其中 $B_{i,j}=A_{i,j}\operatorname{xor}A_{i+1,j}\operatorname{xor}A_{i,j+1}\operatorname{xor}A_{i+1,j+1}$。

特别地，若式子中 $A$ 超出了合法范围 $n\times m$，那么默认其为 $0$。

容易发现矩阵 $A$ 与矩阵 $B$ 等价，因为由 $A$ 推 $B$ 之后，可以从 $B$ 的右下角开始，由外到内一圈一圈倒推回 $A$。

当 $A$ 全为 $0$ 时，$B$ 也全为 $0$。

接下来，我们可以在 $B$ 上考察操作的影响。

对于操作 1，可以想象矩阵 $A$，发现只有一个 $B$ 中元素的表达式被异或了奇数次，即右下角 $(x,y)$。

对于操作 4，就是把形如 $(x,y),(x,m),(n,y),(n,m)$ 的格子异或了一次 $1$。

~~没什么用的补充~~：这样看来，我们认为对 $B$ 的单个元素的操作尽可能少，就会更优。


由于操作 4 涉及的格子较多，就考虑操作 4 的限制。

- 不会同时对 $(x,y_1)$ 和 $(x,y_2)$ 用操作 4，对 $(x_1,y)$ 和 $(x_2,y)$ 同理。两次操作中，有两个格子被重复异或了两次 $1$，影响被抵消，实际上只有 $4$ 个格子被异或 $1$，代价为 $4$，可以用操作 1 替代。
- 至少要让 $(x,y),(x,m),(n,y)$ 都为 $1$，才对 $(x,y)$ 用操作 4。否则产生错误的格子要用操作 1 变回来，代价至少为 $3$，一定不优（为什么不考虑操作 4？显然更劣）。

接下来，由于第一条限制的特点，我们将问题转化到二分图上，左部为行，右部为列，枚举一系列点，满足第二条限制就连边，最后跑二分图最大匹配即可。

算答案前，处理一下 $B_{n,m}$ 的状态，并将 $B$ 中 $1$ 的数量减去匹配数即可。

对算答案的方式有疑问？我们先特判 $B_{n,m}$ 的情况，放到最后算，然后操作 4 以 $2$ 的代价处理了 $3$ 个格子，可以看作在全部用操作 1 的基础上，少了 4 的操作数个操作 1，就是上述计算的方法了。

用匈牙利算法跑最大匹配的话，时间复杂度约为 $O(n^2m)$，可以通过本题。

机房里某同学听完讲题后的灵魂发问：为什么这题能和二分图扯上关系，怎么想到的？

## 参考代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N=1e5+10;
struct node{
	int to,nxt;
}edge[N];
int head[N];
int cnt;
void add(int u,int v){
	edge[++cnt]={v,head[u]};
	head[u]=cnt;
}
bool vst[N];
char mp[505][505];
int tr[505][505],match[505];
int n,m,op2,lst;
bool dfs(int x){
	for(int i=head[x];i!=-1;i=edge[i].nxt){
		if(!vst[edge[i].to]){
			vst[edge[i].to]=true;
			if(!match[edge[i].to]||dfs(match[edge[i].to])){
				match[edge[i].to]=x;
				return true;
			}
		}
	}
	return false;
}
int main(){
	memset(head,-1,sizeof(head));
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>mp[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			tr[i][j]=(mp[i][j]=='B')^(mp[i+1][j]=='B')^(mp[i][j+1]=='B')^(mp[i+1][j+1]=='B');
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<m;j++){
			if(tr[i][j]&&tr[n][j]&&tr[i][m]) add(i,j+n);
		}
	}
	for(int i=1;i<n;i++){
		memset(vst,0,sizeof(vst));
		if(dfs(i)) op2++;
	}
	tr[n][m]^=(op2&1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			lst+=tr[i][j];
		}
	}
	cout<<lst-op2;
	return 0;
}
```
[本代码可以通过 CF 的评测。](https://www.luogu.com.cn/record/168032465)

Written by [toolong114514](https://www.luogu.com/user/477821) on 2024/7/29.

---

## 作者：honglan0301 (赞：1)

## 题目分析

首先，可以发现操作 $2,3,4$ 分别能用 $2,2,4$ 次操作 $1$替代，且由此可见操作 $2,3$ 总比操作 $1$ 劣，那么我们不妨先考虑仅用操作 $1$ 翻转矩阵。

根据题目条件，我们以 $\text{W}$ 为 $0$, $\text{B}$ 为 $1$ 的规则对目标矩阵构造数组 $a$。显然，点 $(i,j)$ 被翻转的次数 $f(i,j)\equiv a(i,j)\pmod 2$。那么用二维前缀和，以点 $(i,j)$ 为矩形右下角的操作数 $g(i,j)=f(i,j)-f(i+1,j)-f(i,j+1)+f(i+1,j+1)$, 即只需满足 $g(i,j)\equiv (a(i,j)\text{ xor } a(i+1,j)\text{ xor }a(i,j+1)\text{ xor } a(i+1,j+1))\pmod 2$。

于是我们构造数组 $b(i,j)$ 为上面的异或式子，当且仅当 $b(i,j)=1$ 时对 $(i,j)$ 进行操作 $1$ 即可构成一组合法操作。接下来我们考虑如何使用操作 $4$ 使得花费更优。

显然对 $(i,j)$ 进行操作 $4$ 等价于对 $(i-1,j-1),(i-1,m),(n,j-1),(m,n)$ 分别进行操作 $1$, 于是可以推出对每一行和每一列都最多只进行 $1$ 次操作 $4$ 总是不劣的。于是对行列进行二分图匹配，当 $b(i,j)=b(i,m)=b(n,j)=1$ 时连左部 $i$ 到右部 $j$ 的边（否则该操作不优），匈牙利算法求二分图最大匹配，之后判断是否还需对 $(n,m)$ 进行操作 $1$, 时间复杂度 $O(n^2m)$, 可以通过本题。

## 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>
#include <map>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
using namespace std;

int n,m,a[505][505],b[505][505],match[505],edge[505][505],vis[505],anss,ans;
char s[505];

bool dfs(int now)
{
	for(int i=1;i<=m-1;i++)
	{
		if(edge[now][i]&&!vis[i])
		{
			vis[i]=1;
			if(!match[i]||dfs(match[i]))
			{
				match[i]=now; return 1;
			}
		}
	}
	return 0;
}
void ed()
{
	for(int i=1;i<=n-1;i++)
	{
		memset(vis,0,sizeof(vis));
		anss+=dfs(i);
	}
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>s;
		for(int j=1;j<=m;j++) a[i][j]=s[j-1]=='B';
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			b[i][j]=(a[i][j]^a[i+1][j]^a[i][j+1]^a[i+1][j+1]);
			ans+=b[i][j];
		}
	}
	ans-=b[n][m];
	for(int i=2;i<=n;i++)
	{
		for(int j=2;j<=m;j++)
		{
			if(b[i-1][j-1]&&b[i-1][m]&&b[n][j-1])
			{
				edge[i-1][j-1]=1;
			}
		}
	}
	ed(); b[n][m]^=(anss&1);
	ans-=anss; ans+=b[n][m];
	cout<<ans<<endl;
}
```

---

## 作者：UperFicial (赞：1)

> [**CF1592F2 Alice and Recoloring 2**](https://www.luogu.com.cn/problem/CF1592F2) 解题报告。

> [**不一定更好的阅读体验**](https://www.cnblogs.com/UperFicial/p/16945329.html)。

> 摘自我的 [**构造题目选做**](https://www.cnblogs.com/UperFicial/p/16938533.html) 例题 IV。

CF 2800 的构造就这？/cf/cf/cf（

首先，操作 2 和操作 3 都是没有用的，因为都可以表示成两次操作 1 的形式，而且花费都不比两次操作 1 要优。

考虑将字符 `B` 看成 $1$，字符 `W` 看成 `0`，那么目标就是要将给定的矩阵通过翻转变成全 $0$ 矩阵。

但是矩形的翻转是不好做的，自然的想法是通过二维差分转成单点修改。即我们令 $c_{i,j}=(a_{i,j}+a_{i+1,j}+a_{i,j+1}+a_{i+1,j+1})\bmod 2$，那么令 $A$ 每一项变成 $0$ 其实就是令 $C$ 每一项变成 $0$。

考虑操作的影响。以 $(x,y)$ 为右下角进行操作 1，实际上只会改变 $c_{x,y}$ 的奇偶性；以 $(x,y)$ 为左上角进行操作 2，实际上只会改变 $c_{x-1,y-1}$，$c_{x-1,m}$，$c_{n,y-1}$，$c_{n,m}$ 这四项的奇偶性。

**这里先讲一下 F1 的做法**，如果对 $(x,y)$ 进行操作 $2$，必须要满足上述四个点的 $c$ 都为 $1$。原因很简单，如果有至少一个为 $0$，那么反转之后还需要再进行一次操作 $1$ 反转回来，总花费为 $3+1=4$，实际上只需要 $3$ 次 $1$ 操作就可以搞定，花费为 $3$。注意到每次都会翻转 $(n,m)$ 这个点，所以说操作 4 只会进行一次。那么我们只要枚举一下是否有能够进行操作 4 的 $(x,y)$ 即可。时间复杂度 $O(n^2)$，可以通过本题。

**接下来讲得是 F2 的做法**，注意到操作 $4$ 的花费变成 $2$，显然是操作的四个点中可以存在一个 $0$，那么我们就不用管 $(n,m)$ 这个点的取值了，因为每次都会更改它，最后一个 $1$ 操作改回来就行，所以剩下那三个点必须都为 $1$，且操作 4 是可以进行多次的。考虑 $(x,y)$，$(x,m)$，$(n,y)$ 这三个点有什么性质，如果我们对 $(x,y)$ 这个点翻转了，那么就意味着 $x$ 这一行再也不能对任何一个点进行操作，因为 $(x,m)$ 被翻转成了 $0$，同理，$y$ 这一列也不能对任何一点进行操作。这不就很网络流了吗，每一行，每一列，每一个点都只能选一次，所以将 $x\to y$ 连一条流量为 $1$ 的边，$S\le x$ 连一条流量为 $1$ 的边，$y\to T$ 连一条流量为 $1$ 的边，跑 dinic 即可，其实本质上就是一个二分图最大匹配。最坏情况边数为 $O(n^2)$，点数为 $O(n)$，所以复杂度 $O(n^2\sqrt{n})$，可以通过本题。


```cpp
int main()
{
    n=read(),m=read();
    rep(i,1,n)
    {
    	scanf("%s",s+1);
    	rep(j,1,m) if(s[j]=='B') a[i][j]=true;
    }
    rep(i,1,n) rep(j,1,m) a[i][j]=a[i][j] xor a[i+1][j] xor a[i][j+1] xor a[i+1][j+1];
    S=0,T=n+m+1;
    rep(i,1,n-1) add_edge(S,i,1);
    rep(i,1,m-1) add_edge(i+n,T,1);
    rep(i,1,n-1) rep(j,1,m-1) if(a[i][j]&&a[i][m]&&a[n][j]) add_edge(i,j+n,1);
    int ans=0;
    while(bfs()) ans-=dfs(S,INF);
    if(ans&1) a[n][m]^=1;
    rep(i,1,n) rep(j,1,m) if(a[i][j]) ++ans;
    printf("%d\n",ans); 
    return 0;
}
```

---

## 作者：Priestess_SLG (赞：0)

**「感觉能独立想出这题的人，脑子和蛇一样聪明」**

一眼看上去这题十分神秘不可做，因此考虑逐步挖掘其性质。

性质：有用的操作其实只有 $1,4$ 两种。

证明：

对于 $2$ 操作：则可以先用一次 $1$ 操作操作掉整个左侧，然后再把不包含于她的左上角操作。这样花费的代价为 $2$，优于 $1$ 次 $2$ 操作的 $3$ 代价。$4$ 操作同理，用 $1$ 操作操作掉整个上侧然后容斥把不包含于她的左上角操作，花费的代价为 $2$，优于 $1$ 次 $3$ 操作花费的 $4$ 代价。

---

然后发现一次操作操作的是一个矩阵，看上去很麻烦，要将其变为对单点做操作。因此考虑对矩阵做二阶差分。这里重定义颜色之间的按位异或：

+ 相同颜色异或，得到的颜色为 $\texttt{W}$。
+ 不同颜色异或，得到的颜色为 $\texttt{B}$。

考虑将其转化为实际的数字意义，即 $\texttt{W}$ 代表 $0$，$\texttt{B}$ 代表 $1$。此时令这个差分的二维数组为 $a$，则考虑一次操作会对新的二维数组 $a$ 做怎样的修改。

+ 对于一次 $1$ 操作 $(x,y)$，则只有 $(x,y)$ 一个点会取反。
+ 对于一次 $4$ 操作 $(x,y)$，那么 $(x-1,y-1)$，$(x-1,m)$，$(n,y-1)$，$(n,m)$ 四个点都会被取反。

看上去一次 $4$ 操作修改的位置更多，性质或许也会更强一些？于是对其做分析。考虑同时对在同一行上的两个坐标 $(x,y_1)$ 和 $(x,y_2)$ 做一次 $4$ 操作，则此时 $(x,y_1),(n,y_1),(x,y_2),(n,y_2)$ 四个格子被取反了一次，而 $(x,m),(n,m)$ 被取反了两次（等于没变）。一共取反了 $4$ 个格子，和做 $4$ 次 $1$ 操作效果等价，花费均为 $4$。因此其实这种情况可以规避开较为复杂的 $4$ 操作去使用较为简单的 $1$ 操作替代。同一列上的两个坐标 $(x_1,y)$ 和 $(x_2,y)$ 的情况也同理。换句话说：$4$ 操作操作的任意两个位置横纵坐标必须都不相同。

可以通过类似的手段分析，得到另一个性质更为强大的结论：使用 $4$ 操作对 $(x,y)$ 做操作比用 $1$ 操作严格好，当且仅当 $(x,y),(x,m),(n,y)$ 三个格子的值都为 $1$。证明类似于上面一个步骤，如果这三个格子中存在一个格子不为 $1$ 则需要容斥一次翻转操作，即执行两次翻转，花费的代价为 $4$。而若用 $1$ 操作则只需要不超过 $3$ 的代价就可以达成目标。

分析了这么一大通，那么这个题有应该如何解决呢？考虑到（忘了哪个题）的套路，建一张二分图，把横坐标建在图的左侧，纵坐标建在图的右侧。那么做一次可能合法 $4$ 操作 $(x,y)$ 就是把左侧点 $x$ 向右侧点 $y$ 连一条边。用匈牙利算法对该图跑最大匹配，或者建立源汇用 Dinic 算法求解其网络最大流均可。时间复杂度为 $O(n^3)$ 或 $O(n^{2.5})$（$n,m$ 同阶），而且远远跑不满，所以可以通过。

代码：

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#define int long long
using namespace std;
const int N = 500010;
vector<int> adj[N];
char s[1010][1010];
int used[N], mat[N];
int dfs(int u) {
    for (int &v : adj[u])
        if (!used[v]) {
            used[v] = 1;
            if (!mat[v] || dfs(mat[v])) {
                mat[v] = u;
                return 1;
            }
        }
    return 0;
}
char mp[2010][2010];
signed main() {
    // cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) cin >> s[i][j];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            mp[i][j] = (s[i][j] == 'B') ^ (s[i + 1][j] == 'B') ^ (s[i][j + 1] == 'B') ^ (s[i + 1][j + 1] == 'B');
        }
    for (int i = 1; i < n; ++i)
        for (int j = 1; j < m; ++j)
            if (mp[i][j] && mp[i][m] && mp[n][j]) {
                adj[i].emplace_back(j + n);
                adj[j + n].emplace_back(i);
            }
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= n + m; ++j) used[j] = 0;
        cnt += dfs(i);
    }
    if (cnt & 1) mp[n][m] ^= 1;
    int all = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) all += mp[i][j];
    cout << all - cnt << '\n';
    return 0;
}
```

---

## 作者：Mashu77 (赞：0)

首先 
$2,3$
 操作是无用的，只需考虑 
$1
,
4$
 操作。

整个矩阵取反很难搞，做个简单的变形：
$s_{i,j}=a_{i,j}⊕a_{
i
,
j
+
1}
⊕
a_{
i
+
1
,
j}
⊕
a_{
i
+
1
,
j
+
1}$，则操作 
$1$
 是单点取反，操作 
$4$
 是同时取反 
$(
x
,
y
)
,
(
x
,
m
)
,
(
n
,
y
)
,
(
n
,
m
)$。倒着考虑，目标态是全为 
$0$。称操作 
$4$
 为 
$op
(
x
,
y
)$。

接下来是两个重要结论：

- $op
(
x
,
y
)$
 的必要条件是 
$s_{
x
,
y}
=
s_{
x
,
m}
=
s_{
n
,
y}
=
1$。因为如果不是，操作后至少还需要 
$1$
 的代价使这三位都归零。不如直接三次操作 
$1$。
- 不存在 
$op
(
x_
1
,
y_
1
)
,
op
(
x_
2
,
y_
2
)$，有 
$x_
1
=
x_
2$
 或 
$y_
1
=
y_
2$。因为如果存在，不妨设为 
$y_
1
=
y_
2$，则 
$(
n
,
y_
1
)
,
(
n
,
m
)$
 两位是不动的，另外 
$4$
 位直接操作 
$1$
 即可。
第二个结论提供了很好的二分图模型。再稍加推导，易知答案为 
$r
e
m
−
k$，其中 
$r
e
m$
 为矩阵变换后 
$1$
 的数目，$k$
 为最大匹配。
$(
n
,
m
)$
 处需特殊判断。

---

## 作者：Purslane (赞：0)

# Solution

唐题。和 $\rm F1$ 一样，还是发现本质上只有从 $(1,1)$ 开头的矩阵和从 $(n,m)$ 开头的矩阵有实际作用。

设 $b_{i,j} = a_{i,j} \oplus a_{i+1,j} \oplus a_{i,j+1} \oplus a_{i+1,j+1}$，则只用从 $(1,1)$ 开始的矩阵的答案是 $\sum_{i=1}^n \sum_{j=1}^m b_{i,j}$。

考虑我们加入一个 $(x,y)$ 到 $(n,m)$ 的矩阵，会对 $(x-1,m)$、$(n,y-1)$、$(x-1,y-1)$、$(n,m)$ 四个格子产生影响——这四个位置的 $b$ 会异或 $1$。

由于 $(n,m)$ 比较统一，所以我们先不管它。考虑前三个格子，我们花了 $2$ 的代价，最多能换来 $3$ 代价的折扣——由此观之，一个操作是划得来的，只能将三个操作都顶满。

> 有一个小问题在于，会不会出现一种类似“蓄势”的操作，也就是我们当前一次操作并不能有优惠，但是可以让下一次有优惠。

> 我们将证明这是不优的。首先，如果这一次操作亏损了，那么就算蓄势，也并无法获得净利润。我们只需要考虑这一次操作打成了平手。额然而你发现并没有这样的情况，因为你的净获利是奇数。

于是你发现：每一行和每一列都最多能有一个 $(x,y)$。转变成了一个二分图匹配问题。

这时候考虑 $(n,m)$ 格子。注意到我们如果要顾及这个格子的利润，可能要在已经求出的最大匹配中进行微调——但是微调的结果就是要舍弃一个匹配，最终还是没有净获利。所以我们被动的计算这个格子的答案即可。

代码：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1000+10,MAXE=1000000+10;
int cnt,ans,tmp,psl,n,m,s,t,b[MAXN][MAXN],a[MAXN][MAXN],hd[MAXE],cur[MAXE],dis[MAXE],tot=1;
struct Node {int to,nxt,w;}edge[MAXE];
void add_edge(int u,int v,int w) {
	edge[++tot]={v,hd[u],w},hd[u]=tot;
	edge[++tot]={u,hd[v],0},hd[v]=tot;
	return ;	
}
int bfs(void) {
	memset(dis,-1,sizeof(dis));
	dis[s]=0; queue<int> q; q.push(s);
	while(!q.empty()) {	
		int u=q.front(); q.pop();
		cur[u]=hd[u];
		for(int i=hd[u];i;i=edge[i].nxt) {
			int to=edge[i].to,w=edge[i].w;
			if(dis[to]!=-1||!w) continue ;
			dis[to]=dis[u]+1,q.push(to);	
		}
	}
	return dis[t]!=-1;
}
int dinic(int u,int mx) {
	if(u==t) return mx;
	int ans=0;
	for(int i=cur[u];i;i=edge[i].nxt) {
		cur[u]=i;
		int to=edge[i].to,w=edge[i].w;
		if(!w||dis[to]!=dis[u]+1) continue ;
		int tmp=dinic(to,min(w,mx));
		if(tmp) {
			ans+=tmp,mx-=tmp,edge[i].w-=tmp,edge[i^1].w+=tmp;
			if(mx==0) break ;
		}
		else dis[to]=-1;
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	s=0,t=n+m+1;
	ffor(i,1,n) {
		string S; cin>>S;
		ffor(j,1,m) a[i][j]=(S[j-1]=='B');	
	}
	ffor(i,1,n) ffor(j,1,m) ans+=(b[i][j]=a[i][j]^a[i+1][j]^a[i][j+1]^a[i+1][j+1]);
	ffor(i,1,n-1) if(b[i][m]) add_edge(s,i,1);
	ffor(i,1,m-1) if(b[n][i]) add_edge(i+n,t,1);
	ffor(i,1,n-1) ffor(j,1,m-1) if(b[i][j]) add_edge(i,j+n,1);
	while(bfs()) while(tmp=dinic(s,0x3f3f3f3f)) psl+=tmp;
	if(psl&1) {
		if(b[n][m]) ans--;
		else ans++;	
	}
	ans-=psl;
	cout<<ans;
	return 0;
}
//我送你离开 千里之外 你无声黑白 
```

---

## 作者：封禁用户 (赞：0)

对于矩阵取反非常不好做。这时候我们可以联想到差分，将它转化为单点取反。

所以我们构造广义差分数组 $a_{i,j} = s_{i,j}\oplus s_{i+1,j}\oplus s_{i,j + 1}\oplus s_{i+1,j + 1}$，原矩阵 $s$ 全 $0$ 等价于矩阵 $a$ 全 $0$。发现 $1,2,3$ 操作对应单点取反，$4$ 操作对应 $4$ 个点取反。

所以 $4$ 操作最多只会进行一次，枚举以下即可。

一个位置除了 $(n,m)$ 只会翻转一次，且尽量先用 $4$ 操作，所以直接套二分图模型即可。

```
#define N 505
int n, m, u[N][N], a[N][N], s, t; char w[N];
int h[N << 1], tot = 1, d[N << 1], cur[N << 1];
struct edge{int to, nxt, cap;}e[N * N * 4];
void add(int x,int y,int z){
	e[++tot].nxt = h[x], h[x] = tot, e[tot].to = y, e[tot].cap = z;
	e[++tot].nxt = h[y], h[y] = tot, e[tot].to = x, e[tot].cap = 0;
}
queue<int>q;
bool bfs(){
	memset(d, 0, sizeof(d));
	d[s] = 1, q.push(s);
	while(!q.empty()){
		int x = q.front(); q.pop(); cur[x] = h[x];
		for(int i = h[x]; i; i = e[i].nxt)if(e[i].cap && !d[e[i].to])
			d[e[i].to] = d[x] + 1, q.push(e[i].to);
	}
	return d[t] ? 1 : 0;
}
int dfs(int x,int flow){
	if(t == x)return flow;
	int res = flow;
	for(int &i = cur[x]; i; i = e[i].nxt) if(e[i].cap && d[x] + 1 == d[e[i].to]){
		int now = dfs(e[i].to, min(res, e[i].cap));
		if(!now)d[e[i].to] = 0;
		else e[i].cap -= now, e[i ^ 1].cap += now, res -= now;
		if(!res)return flow;
	}
	return flow - res;
}
int main() {
	//int T = read();while(T--)solve();
	n = read(), m = read();
	rep(i, 1, n){
		scanf("%s", w + 1);
		rep(j, 1, m)a[i][j] = w[j] == 'B';
	}
	int ans = 0;
	rep(i, 1, n)rep(j, 1, m)ans += (u[i][j] = a[i][j] ^ a[i + 1][j] ^ a[i][j + 1] ^ a[i + 1][j + 1]);
	rep(i, 1, n - 1)rep(j, 1, m - 1)if(u[i][j])add(i, j + n - 1, 1);
	s = n + m - 1, t = s + 1;
	rep(i, 1, n - 1)if(u[i][m])add(s, i, 1);
	rep(i, 1, m - 1)if(u[n][i])add(i + n - 1, t, 1);
	int sum = 0;
	while(bfs())sum += dfs(s, n + m);
	if(sum)printf("%d\n", ans - sum + ((sum & 1) ^ u[n][m]) - u[n][m]);
	else printf("%d\n", ans);
	return 0;
}

```

---

## 作者：D2T1 (赞：0)

简单 *2800。

观察操作，发现操作二、操作三都是没有用的。因为我们可以通过 $2$ 次操作一实现翻转任何一个包含 $(1,m)$ 或 $(n,1)$ 的子矩阵；又发现操作四不可能操作两次长或宽相同的矩阵。

![](https://cdn.luogu.com.cn/upload/image_hosting/0ilq7dgm.png)

如图，若操作了两次长或宽相同的矩阵（绿色和蓝色），相当于翻转了红色部分。而显然这可以通过 $4$ 次操作一实现，使用操作一肯定不劣。

那么现在题目变成了：使用操作一、以及长宽均不同的操作四实现目标。

如果 $(i,j)$ 位置是 `B`，我们令 $a_{i,j},a_{i-1,j},a_{i,j-1},a_{i-1,j-1}$ 取反，那么仅使用操作一的操作次数就是 $\sum_{i=1}^n\sum_{j=1}^ma_{i,j}$。

考虑一次操作三。若选择了 $(x,y)$，相当于对 $a_{n,m},a_{x-1,m},a_{n,y-1},a_{x-1,y-1}$ 取反。抛开 $a_{n,m}$，若其它三项均为 $1$，那么这样进行一次操作三会使答案减一，是更优的。

那么就可以建图跑匹配。若 $a_{i,j},a_{i,m},a_{n,j}$ 均为 $1$，则建一条左部点 $i$ 连右部点 $j$ 的边。

最后考虑 $a_{n,m}$。设跑出来的最大匹配为 $k$，若 $k$ 与 $a_{n,m}$ 奇偶性相同，那么可以在这 $k$ 次操作的同时将 $a_{n,m}$ 变为 $0$，很优；若不同，则 $k$ 次操作过后 $a_{n,m}$ 为 $1$。是否需要考虑增加或删除一些匹配呢？可以发现不用，因为一组匹配的贡献是 $-1$，而 $a_{n,m}$ 变为 $1$ 的贡献是 $1$，可以抵消；如果新增一个匹配，新增匹配的贡献为 $1,3,5$，不优于 $a_{n,m}$ 变为 $1$。所以不用考虑这些情况。

```cpp
const int N = 510;
int n, m, a[N][N], e[N][N], mch[N], vis[N];
string s[N];

int dfs(int x){
	for(int i = 1; i <= m; ++ i){
		if(!vis[i] && e[x][i]){
			vis[i] = 1;
			if(!mch[i] || dfs(mch[i])){
				mch[i] = x;
				return 1;
			}
		}
	}
	return 0;
}

void solve(){
	read(n, m);
	for(int i = 1; i <= n; ++ i){
		read(s[i]);
		s[i] = ' ' + s[i];
		for(int j = 1; j <= m; ++ j){
			if(s[i][j] == 'B'){
				a[i][j] ^= 1;
				a[i-1][j] ^= 1;
				a[i][j-1] ^= 1;
				a[i-1][j-1] ^= 1;
			}
		}
	}
	int sm = 0, ans = 0;
	for(int i = 1; i <= n; ++ i){
		for(int j = 1; j <= m; ++ j){
			sm += a[i][j];
		}
	}
	ans = sm;
	for(int i = 1; i < n; ++ i){
		for(int j = 1; j < m; ++ j){
			if(a[i][j] && a[i][m] && a[n][j]){
				e[i][j] = 1;
			}
		}
	}
	int mc = 0;
	for(int i = 1; i <= n; ++ i){
		memset(vis, 0, sizeof(vis));
		mc += dfs(i);
	}
	sm -= a[n][m];
	a[n][m] ^= (mc & 1);
	ans = min(ans, sm - mc + a[n][m]);
	println(ans);
}
```

---

## 作者：5k_sync_closer (赞：0)

操作 $2,3$ 可以用 $1,4$ 容斥，所以没用。

设 $b_{i,j}=a_{i,j}\oplus a_{i+1,j}\oplus a_{i,j+1}\oplus a_{i+1,j+1}$，

则操作 $1$ 翻转 $(1,1)$ 到 $(i,j)$ 的矩阵等价于 $b_{i,j}\gets b_{i,j}\oplus 1$，

操作 $4$ 翻转 $(i,j)$ 到 $(n,m)$ 的矩阵等价于 $b_{n,m}\gets b_{n,m}\oplus 1,b_{i-1,m}\gets b_{i-1,m}\oplus 1,b_{n,j-1}\gets b_{n.j-1}\oplus 1,b_{i-1,j-1}\gets b_{i-1,j-1}\oplus 1$。

注意到所有操作 $4$ 的 $i$ 一定互不相同且 $j$ 一定互不相同，否则不如操作 $1$。

则问题转化为求最多能找出多少 $(i,j)$ 满足 $i$ 互不相同，$j$ 互不相同且 $b_{i,j}=b_{i,m}=b_{n,j}=1$。

以 $i\in[1,n)$ 为左半部，$j\in[1,m)$ 为右半部建二分图，存在 $i\to j$ 当且仅当 $b_{i,j}=b_{i,m}=b_{n,j}=1$，则该图的最大匹配即为操作 $4$ 的个数 $p$。

一次操作 $4$ 可以省一次操作 $1$，所以这些操作 $4$ 的贡献是 $-p$。

注意 $p$ 为奇数时要特判 $b_{n,m}$ 的值，

若 $b_{n,m}=0$ 则经过这些操作 $4$ 后 $b_{n,m}$ 变为 $1$，需要一个额外的操作 $1$。

若 $b_{n,m}=1$ 则经过这些操作 $4$ 后 $b_{n,m}$ 变为 $0$，可以省一个操作 $1$。

```cpp
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
struct E{int v, w, t;}e[250050];
int n, m, r, p, c = 1, s, t, d[1050], g[1050], h[1050];
bool a[550][550], b[550][550];char z;queue<int> q;
void A(int u, int v, int w) {e[++c] = {v, w, h[u]};h[u] = c;}
bool B()
{
	memset(d, 0, sizeof d);d[s] = 1;q.push(s);while(!q.empty())
	{
		int u = q.front();q.pop();g[u] = h[u];for(int i = h[u], v;i;i =
		e[i].t) if(e[i].w && !d[v = e[i].v]) d[v] = d[u] + 1, q.push(v);
	}
	return d[t];
}
int D(int u, int f)
{
	if(u == t) return f;
	int k, q = 0;
	for(int i = g[u], v;i && f;i = e[i].t)
	{
		g[u] = i;
		if(e[i].w && d[v = e[i].v] == d[u] + 1)
			k = D(v, min(e[i].w, f)), e[i].w -= k, e[i ^ 1].w += k, q += k, f -= k;
	}
	return q;
}
int main()
{
	scanf("%d%d", &n, &m);t = n + m;
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= m;++j)
			scanf(" %c", &z), a[i][j] = z == 'B';
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= m;++j)
			b[i][j] = a[i][j] ^ a[i + 1][j] ^ a[i][j + 1] ^ a[i + 1][j + 1];
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= m;++j)
			r += b[i][j];
	for(int i = 1;i < n;++i)
		for(int j = 1;j < m;++j)
			if(b[i][j] && b[i][m] && b[n][j])
				A(i, j + n, 1), A(j + n, i, 0);
	for(int i = 1;i < n;++i) A(0, i, 1), A(i, 0, 0);
	for(int i = 1;i < m;++i) A(i + n, t, 1), A(t, i + n, 0);
	while(B()) p += D(0, 1e9);r -= p;
	r -= b[n][m] && p & 1;
	r += !b[n][m] && p & 1;
	return !printf("%d", r);
}
```


---

## 作者：orz_z (赞：0)

### CF1592F1

发现操作 $2$ 和操作 $3$ 的等效于执行 $2$ 次操作 $1$，更优。

记 $a_{x,y}$ 表示 $(x,y)$ 是否为黑色，再记 $b_{x,y}=a_{x,y}\oplus a_{x,y+1}\oplus a_{x+1,y}\oplus a_{x+1,y+1}$，可以发现操作 $1$ 等价于翻转 $b_{x,y}$，而操作 $4$ 等价于翻转 $b_{x-1,y-1},b_{x-1,m},b_{n,y-1},b_{n, m}$。

注意到我们使用 $4$ 操作的次数不会超过 $1$，因为两次操作 $4$ 可用六次操作 $1$ 代替，代价相等不会更劣。

这样统计有多少个 $b_{x,y}=1$再统计一下是否存在一组 $(x,y)$，满足 $b_{x-1,y-1},b_{x-1,m},b_{n,y-1},b_{n,m}$ 均为 $1$，若存在，答案减少 $1$。

时间复杂度 $\mathcal O(nm)$。

### CF1592F2

与上题相似。

发现要尽可能多得使用操作 $4$。

二分图匹配即可。

时间复杂度 $\mathcal O(n^2\sqrt n)$。

---

## 作者：cmll02 (赞：0)

qwq。

前置知识：把 F1 过了（

首先显然这个地方只有 $(1,1)$ 和 $(n,m)$ 是有用的。

然后记 $b_{i,j}=a_{i,j}\operatorname{xor}a_{i+1,j}\operatorname{xor}a_{i,j+1}\operatorname{xor}a_{i+1,j+1}$，那么操作 $1$ 就是单点修改，另一个就是 $b_{i,j},b_{i,m},b_{n,j},b_{n,m}$。

先不考虑 $b_{n,m}$，然后你发现如果这里面剩下的三个全是 $1$ 才是好的。

然后每个点只会被动一次，不然也不优。

这样直接对行和列抽成点网络流即可。

最后再判断一下 $b_{n,m}$ 的情况即可。

具体建图挺显然的，建出来发现其实就是二分图最大匹配（）

[Code link](https://codeforces.com/contest/1592/submission/137309998)

---

## 作者：happybob (赞：0)

建议先阅读 [F1 题解](https://www.luogu.com.cn/article/vxeknufr)。

虽然题意与 F1 不同，但是 F1 的做法能给予我们很明确的思考方向。比较容易注意到仍然只有左上和右下操作有效，但是可能存在大量右下操作都是有效的。不过还是可以从一些特殊情况入手。

首先可以发现右下操作如果顶到了左边界或上边界，那么可以直接被左上操作替代。同时可以发现不可能存在两次的右下操作互相包含且存在某条边重合。

其次，考虑差分数组 $c_{i,j} = b_{i,j} \oplus b_{i+1,j} \oplus b_{i,j+1} \oplus b_{i+1,j+1}$，发现左上操作是差分数组的单点取反，右下操作是将包含 $(n,m)$ 在内的四个位置单点取反。目标是将除了 $(n,m)$ 之外的点的差分值改为 $0$，$(n,m)$ 为 $1$。

进一步，考察什么样的右下操作有意义。事实上当且仅当除了 $(n,m)$ 的余下 $3$ 个取反的位置都是 $1$ 时才会进行操作。否则可以直接改为左上操作。

根据这样的条件，建立二分图，左侧 $n-1$ 个点，右侧 $m-1$ 个点。在 $(i,j)$ 进行右下操作优，就将 $(i-1,j-1)$ 连边。在二分图上跑最大匹配，剩下的还没被改的点只能用左上，直接计算即可。

如果使用朴素的最大匹配做法复杂度为 $O(n^3)$，使用 Dinic 可以做到 $O(n^{2.5})$，均可通过。

代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <queue>
#include <vector>
using namespace std;

constexpr int N = 505, M = 1005;

int n, m;
array<array<bool, N>, N> b, c;

array<int, M> match, pre;
array<bool, M> vis;
array<vector<int>, M> G;

bool bfs()
{
	queue<int> q;
	for (int i = 1; i <= n + m; i++)
	{
		pre[i] = vis[i] = 0;
	}
	for (int i = 1; i < n; i++)
	{
		if (!match[i]) q.emplace(i), vis[i] = 1;
	}
	while (q.size())
	{
		int u = q.front();
		q.pop();
		for (auto& j : G[u])
		{
			if (pre[j]) continue;
			if (match[j] ^ u)
			{
				pre[j] = u;
				if (match[j] && !vis[match[j]])
				{
					vis[match[j]] = 1, q.emplace(match[j]);
				}
			}
		}
	}
	for (int i = n; i <= n - 1 + m - 1; i++)
	{
		if (!match[i] && pre[i])
		{
			int y = i;
			while (y)
			{
				int x = pre[y];
				int ny = match[x];
				match[x] = y, match[y] = x;
				y = ny;
			}
			return 1;
		}
	}
	return 0;
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			char x;
			cin >> x;
			b[i][j] = (x == 'W' ? 1 : 0);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			c[i][j] = b[i][j] ^ b[i + 1][j] ^ b[i][j + 1] ^ b[i + 1][j + 1];
		}
	}
	for (int i = 2; i <= n; i++)
	{
		for (int j = 2; j <= m; j++)
		{
			if (c[n][j - 1] + c[i - 1][m] + c[i - 1][j - 1] == 3)
			{
				G[i - 1].emplace_back(j - 1 + n - 1);
			}
		}
	}
	while (bfs());
	int ans = 0;
	for (int i = 1; i < n; i++)
	{
		if (match[i])
		{
			int ni = i + 1, nj = match[i] + 1 - (n - 1);
			c[n][nj - 1] = c[ni - 1][m] = c[ni - 1][nj - 1] = 0;
			c[n][m] ^= 1;
			ans += 2;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (i == n && j == m)
			{
				if (c[n][m] == 0) ans++;
			}
			else if (c[i][j]) ans++;
		}
	}
	cout << ans << "\n";
	return 0;
}
```

---

