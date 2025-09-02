# [CEOI 2023] Balance

## 题目背景

翻译自 CEOI2023 Day1 T3 [Balance](https://www.ceoi2023.de/wp-content/uploads/2023/09/3-balance.pdf)。

## 题目描述

由于黑客对评测机的攻击，组委会决定重测所有提交记录。

有 $N$ 台评测机，$T$ 个题目（编号为 $1, 2, \cdots, T$）。组委会已经确定，每台评测机要评测哪些提交（数目相同，都是 $S$ 个提交，保证 $S$ 是 $2$ 的整数次幂）。在接下来的 $S$ 分钟内，每分钟每台评测机会评测一个提交。

每个提交都会提交至某个题目。由于存数据的机器太脆弱了，所以要求，对于所有题目和任意两个时刻，在这两个时刻，这个题的被评测的提交的数量之差不超过 $1$。

请构造一组方案，使得满足上面的条件。

## 说明/提示

保证存在正整数 $k$ 使得 $S = 2 ^ k$，$1 \le N, S, T \le 10 ^ 5$，$NS \le 5 \times 10 ^ 5$。

- Subtask 1（$10$ 分）：$S = 2$ 且 $N, T \le 20$。
- Subtask 2（$15 + 5 + 5$ 分）：$S = 2$。
- Subtask 3（$15 + 5 + 5$ 分）：$NS \le 10 ^ 4$。
- Subtask 4（$20 + 10 + 10$ 分）：没有其它限制。

对于后三个子任务，存在部分分（对应括号中的分数）：

- 第一个数表示如果能解决满足 $T \le N$ 且对于每个题目的提交数量均整除 $S$ 时的所有测试点能得到的分数。
- 第二个数表示如果能解决满足 $T \le N$ 时的所有测试点能多得到的分数。
- 第三个数表示如果解决了整个 Subtask 时能多得到的分数。

在洛谷上，本题分为 $10$ 个子任务。对于原来的后三个 Subtask，在本题中分别按顺序分为三个子任务（如原 Subtask 3 就是子任务 $5, 6, 7$），有依赖关系。

## 样例 #1

### 输入

```
3 2 3
1 2
2 3
2 3```

### 输出

```
2 1
3 2
2 3```

## 样例 #2

### 输入

```
3 4 3
2 3 2 2
2 3 3 2
2 2 3 2```

### 输出

```
2 2 2 3
3 2 3 2
2 3 2 2```

# 题解

## 作者：Katyusha_01 (赞：44)

**不用欧拉回路的做法来了，轻松拿下最优解。**

模拟赛考了，赛时想到一个巧妙的二染色做法，可惜没想到分治。

考虑 $S=2$ 怎么做，不同行的相同颜色（相同题目，下同）两两一组，要求一个出现在第一列，另一个出现在第二列，这样组内贡献抵消，就能保证两列出现次数之差不超过 $1$（最后最多剩下一个，随便怎么分组都行），实现就是组内两个点（也就是对应的两行）之间连一条有权边（$0/1$ 表示翻转情况相同或只翻转一个）。然后跑一遍染色就做完了。

是不是听起来很厉害，考虑证明($*,*$ 表示一行数，$a,b,x,y$ 互不相同)：

- $a,b$ 和 $x,y$ 肯定没有连边，一定没有问题。
- $x,y$ 和 $x,y$ 连一条边就消没了。
- $x,a$ 和 $x,b$ 连一条边，其实就相当于合并成了一个 $a,b$。

就分讨完了，不会出现奇环的。

然后分治一下，把每行两两一对拆开，跑前面的染色，使得同色在第一列和第二列出现的次数之差不超过 $1$，然后把第一列的都放到原来那一行的前面一半，第二列的放到后面一半，分治下去就行了。证明类似线段树同一层的节点长度只差不超过 $1$。

染色可以手写队列跑 BFS，目前还是最优解。

---

## 作者：XiaoQuQu (赞：6)

才发现洛谷有这道题/oh

因为我们有 $S=2^k$，所以我们先考虑 $k=1$ 即 $S=2$ 的时候应该怎么做。

发现如果我们对于每一个核心从 $t_1$ 向 $t_2$ 连一条无向边，如果我们把 「不交换 $t_1,t_2$」 看成将这条边定向为 $t_1\to t_2$，否则如果「交换 $t_1,t_2$」看成将这条边定向为 $t_2\to t_1$，我们会发现对于一个数 $x$ 在左边出现的次数相当于 $x$ 的出度，$x$ 在右边出现的次数相当于 $x$ 的入度，我们要找到一种定向方法使得这个图上每个点的入度和出度相差不超过 $1$。

于是我们想到了欧拉回路，欧拉回路上每个点的出度和入度相等（因为每个点出去一次进来一次），但问题是我们的这个无向图不一定有欧拉回路，且我们只需要入度和出度相差不超过 $1$。

考虑到一个无向图有欧拉回路当且仅当这个图上的每一个点的度数都为偶数，于是我们想到建立一个源点，从这个源点向每个度数为奇数的点连一条边，然后在这个新的图上跑欧拉回路，最后只用关注那些原先就在这个图上的边，这样就可以保证每个点的出度和入度相差不超过 $1$ 了。

接下来考虑 $S>2$ 应该怎么做，由于 $S=2^k$，我们可以先将前 $2^{k-1}$ 个评测看成一个整体，将后 $2^{k-1}$ 个评测看成一个整体，我们要使得对于任意一个数 $x$，其在前 $2^{k-1}$ 个中出现的次数与其在后 $2^{k-1}$ 个评测中出现的次数相等，于是我们发现只需要将 $t_i$ 与 $t_{n-i}$ 连边，然后跑一遍欧拉回路，然后分治地处理 $[1,2^{k-1}]$ 与 $[2^{k-1}+1,2^{k}]$ 即可。

因为我们可能会建重边，所以可以在每条边中插入一个点，以记录重边的编号（当然可能不记录也是对的，但是我没验证过）。

时间复杂度 $O((nS + T)\log S)$。

```cpp
const int MAXN = 5e6 + 5;
int ecnt, n, s, t, d[MAXN], hd[MAXN], st[MAXN], top;
vector<vector<int>> a;
struct _node {
	int v, ex, rev;
};
vector<_node> G[MAXN];
bool vis[MAXN];
struct _edge {
	int u, v, i, j;
	bool operator < (const _edge b) const {
		return u == b.u ? v < b.v : u < b.u;
	}
};

void Hierholzer(int x) {
	vis[x] = true;
	for (int &i = hd[x]; i < (int)G[x].size();) {
		if (G[x][i].ex) {
			G[x][i].ex = G[G[x][i].v][G[x][i].rev].ex = 0;
			i++;
			Hierholzer(G[x][i - 1].v);
		} else ++i;
	}
	st[++top] = x;
}

void add(int x, int y) {
	G[x].push_back({y, 1, G[y].size()});
	G[y].push_back({x, 1, G[x].size() - 1});
}

void solve(int l, int r) {
	int len = (r - l + 1);
	ecnt = top = 0;	
	int x = t;
	unordered_map<int, pair<int, int>> emap;
	for (int i = 0; i < len / 2; ++i) {
		for (int j = 1; j <= n; ++j) {
			const int u = a[j][l + i], v = a[j][r - i];
			if (u == v) continue;
			add(u, ++x); add(v, x);
			emap[x] = make_pair(i, j);
			d[u]++; d[v]++; d[x] += 2;
		}
	}
	for (int i = 1; i <= t; ++i) {
		if (d[i] % 2 == 1) {
			add(0, ++x);
			add(i, x);
		}
	}
	for (int i = 0; i <= t; ++i) {
		if (vis[i]) continue;
		top = 0;
		Hierholzer(i);
		reverse(st + 1, st + top + 1);
		for (int j = 3; j <= top; j += 2) {
			if (!st[j] || !st[j - 2] || st[j] == st[j - 2]) continue;
			const auto _ = emap[st[j - 1]];
			int &u = a[_.second][l + _.first], &v = a[_.second][r - _.first];
			if (u != st[j - 2]) {
				swap(u, v);
			}
		}
	}
	for (int i = 0; i <= t + x; ++i) G[i].clear(), vis[i] = false, d[i] = hd[i] = 0;
	if (len != 2) {
		solve(l, mid); solve(mid + 1, r);
	}
}

void work() {
	cin >> n >> s >> t;
	a.resize(n + 1);
	for (int i = 1; i <= n; ++i) {
		a[i].resize(s + 1);
		for (int j = 1; j <= s; ++j)
			cin >> a[i][j];
	}
	solve(1, s);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= s; ++j) cout << a[i][j] << ' ';
		cout << endl;
	}
}
```



---

## 作者：2huk (赞：4)

MX-WF-C 8.14 最难题。

## 题意

给定一个 $n \times s$ 的矩阵。保证 $s$ 是 $2$ 的幂。你需要给出一种将矩阵的每一行重排的方案，使得对于每个矩阵中出现的数而言，在所有列中的出现次数的极差 $\le 1$。

## 做法

首先考虑 $s = 2$。不妨设这个矩阵形如 $[[u_1,v_1],[u_2,v_2]\dots[u_n,v_n]]$。

我们考虑将每个 $u_i, v_i$ 连无向边。我们断言，答案为给所有边定向，使得每个点的入度与出度的差的绝对值都 $\le 1$ 的方案数。

我们考虑一组答案与上述构造的映射关系。对于一条边而言，如果形如 $u_i \to v_i$，则将这一行的两个数交换（即 $[v_i, u_i]$）。否则如果 $u_i \gets v_i$，则这一行保持不变（即 $[u_i,v_i]$）。那么一个数被放在左边的行数即这个点的入度，右边的行数即出度。所以我们需要保证任意一个点的入度与出度的差的绝对值都 $\le 1$。


对于新问题，不难想到欧拉路的一系列东西。

若图中任意一点的度数均为偶数，那么我们对于每个连通块都求一遍**欧拉回路**。可以证明这样的情况下欧拉回路一定存在。那么我们可以根据这条欧拉回路轻易的构造出边的定向方案，且每个点的出度均等于入度。

若图中存在若干个点的度数为奇数。我们建一个 super 点与这些度数为奇数的点连边。可以证明度数为奇数的点的数量一定为偶数（因为所有点的度数和是边数的两倍，是个偶数，所以去除掉所有度数为偶数的点后，剩下的度数为奇数点的度数和也是偶数），即这个 super 点的度数为偶数。

所以这张新图就满足了上一种情况（即所有点的度数均为偶数）。跑一边欧拉回路，再将 super 点去掉即答案。这是因为原来的所有度数为奇数的点，在新图中满足了入度等于出度，所以去掉它的一个度之后，入度出度差至多为 $1$。

至此我们解决了 $s = 2$ 的情况。考虑更一般的问题。

分而治之好！设 $s = 2^k$。我们考虑将矩阵的**每一行**变形：

$$\begin{bmatrix}
a_{i,1}&a_{i,2}&\cdots&a_{i,2^{k-1}}&a_{i,2^{k-1} +1 }&\cdots&a_{i,2^k}
\end{bmatrix}

\longrightarrow

\begin{bmatrix}
a_{i,1} & a_{i,2^{k-1}+1} \\
a_{i,2} & a_{i,2^{k-1}+2} \\
\vdots & \vdots \\
a_{i,2^{k-1}} & a_{i,2^k}
\end{bmatrix}
$$

然后对于这个新矩阵执行上面的算法。换言之我们连边所有 $a_{i,j}, a_{i,j+2^{k-1}}$ 然后跑欧拉回路。

发现这样做我们能保证每个数字在 $a_{1\sim n,1 \sim 2^{k-1}}$ 中的出现次数与在 $a_{1\sim n, 2^{k-1}+1\sim 2^k}$ 中的出现次数相差至多 $1$。然后递归处理 $[1,2^{k-1}]$ 和 $[2^{k-1}+1, 2^k]$ 即可。

---

## 作者：HYXLE (赞：2)

## P9731 [CEOI 2023] Balance

[题目传送门](https://www.luogu.com.cn/problem/P9731)

发现题目限制中有 $S = 2^k$，考虑分治。

发现**若把当前分治的序列分成两半，使得这两边的同种颜色的数量的差不超过 $1$，则可以满足要求**。

证明类似线段树中同一层的区间长度差不会超过 $1$。

那么重点就在于如何分颜色了。

有一种做法是：对于每一行开一个虚点，每一种颜色开一种虚点，然后跑欧拉回路给这些边定向即可，然后对于某一行，将定向为连向颜色的边，将颜色归入左边，否则归入右边。

为什么是对的呢？

​	因为若能走出欧拉回路，说明这个点的入度和出度不超过 $1$，根据上文的构造方式，恰好符合题目要求。

但是有可能会有一些点的奇数度数的，那么只需再建一个虚点，把所有奇数度数的点与这个点相连，易证这个点的度数是偶数。

注意数组一定要开大。

## code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register
using namespace std;
const int N=5e5+5;
struct edge{int u,v;}e[N<<3];
int head[N<<3],tot;
inline void add(int u,int v){e[++tot]={v,head[u]},head[u]=tot;}
int n,s,t,col[N],id,in[N],idx[N],posl[N],posr[N],used[N<<2];
vector<int> mp[N];bool vis[N];
inline void clear(){
	for(R int i=1;i<=id;++i)head[i]=vis[i]=in[i]=0,idx[col[i]]=0,col[i]=posl[i]=posr[i]=0;
	for(R int i=1;i<=tot;++i)used[i]=0;
}
inline void dfs(int u){
	vis[u]=1;
	for(R int i=head[u];i;i=head[u]){
		int v=e[i].u;head[u]=e[i].v;
		if(used[i^1])continue;
		used[i^1]=used[i]=1;
		dfs(v);
		if(u<=n)mp[u][posr[u]--]=col[v];
		if(v<=n)mp[v][posl[v]++]=col[u];
	}
}
inline void solve(int l,int r){
	if(l>=r)return;
	id=n,tot=1;
	for(R int i=1;i<=n;++i)posl[i]=l,posr[i]=r;
	for(R int i=1;i<=n;++i){
		for(R int j=l;j<=r;++j){
			if(!idx[mp[i][j]])idx[mp[i][j]]=++id,col[id]=mp[i][j];
			add(i,idx[mp[i][j]]),add(idx[mp[i][j]],i);
			++in[i],++in[idx[mp[i][j]]];
		}
	}
	++id;
	for(R int i=1+n;i<id;++i)if(in[i]&1)add(i,id),add(id,i);
	for(R int i=1;i<=id;++i)if(!vis[i])dfs(i);
	int mid=l+r>>1;
	clear();solve(l,mid);solve(mid+1,r);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	cin>>n>>s>>t;
	for(R int i=1;i<=n;++i)mp[i].resize(s+1);
	for(R int i=1;i<=n;++i){
		for(R int j=1;j<=s;++j)cin>>mp[i][j];
	}
	solve(1,s);
	for(R int i=1;i<=n;++i){
		for(R int j=1;j<=s;++j)cout<<mp[i][j]<<' ';
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Creeper_l (赞：2)

首先考虑 $S=2$ 怎么做，我们把它转化为图论问题。对于每一行的两个点的颜色连一条无向边，那我们相当于要给这些边定向。最后要求 $|in_u-out_u| \le 1$。会发现这个要求很像欧拉回路。

但是欧拉回路是要求每个点的入度和出度相等，怎么办呢？我们再建一个超级源点，向每个奇数度数的点连边。这样跑一遍欧拉回路，最后忽略和超级源点相连的边即可。

问题变为了 $S > 2$ 怎么做。因为题目说 $S$ 是 $2$ 的次幂，这让我们想到分治。每一次只需要要求每种颜色在左一半的出现次数和在右一半的出现次数差不超过 $1$。但是题目要求我们只能在行内交换，所以假设我们现在分治到 $[l,r]$，我们就连边 $(a_{i,j},a_{i,mid+1+j-l})$。会发现这样一定有解。

时间复杂度 $O(nS \log S)$。

```
//dzzfjldyqqwsxdhrdhcyxll
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 4e6 + 10;
int n,s,t,head[MAXN],cnt,vis[MAXN << 1],ans[MAXN << 1],tot,d[MAXN << 1];
struct Node {int u,v,nxt;}e[MAXN << 1];
inline void Add(int u,int v) {
//	cout << "u = " << u << " v = " << v << endl; 
	e[cnt] = {u,v,head[u]};
	head[u] = cnt++;
}
vector <int> a[MAXN];
inline int Get(int i,int j) {
	return max(t,n * s) + (i - 1) * s + j; 
}
inline void dfs(int u) {
	for(int &i = head[u]; ~ i;i = e[i].nxt) {
		if(vis[i]) continue;
		int now = e[i].v;
		vis[i] = vis[i ^ 1] = 1;
		dfs(now);
		if(i==-1){
			break;
		}
	}
	ans[++tot] = u;
//	cout << u << " ";
}
inline void solve(int l,int r) {
	int mid = (l + r) >> 1;
	for(int i = 1;i <= n;i++) {
		for(int j = l;j <= mid;j++) {
			if(a[i][j] == a[i][mid + 1 + j - l]) continue;
			Add(a[i][j],Get(i,j));
			Add(Get(i,j),a[i][j]);
			Add(Get(i,j),a[i][mid + 1 + j - l]);
			Add(a[i][mid + 1 + j - l],Get(i,j));
			d[a[i][j]]++;
			d[a[i][mid + 1 + j - l]]++;
		}
	}
	if(l == 3 && r == 4) {
//		cout << "dddd = " << d[3] << endl;
	}
	for(int i = 1;i <= n;i++) {
		for(int j = l;j <= r;j++) {
			if(d[a[i][j]] % 2 == 1) {
				d[a[i][j]]++;
				Add(0,a[i][j]);
				Add(a[i][j],0);
			}
		}
	}
	tot = 0;
//	dfs(0);
	for(int i = 1;i <= n;i++) {
		for(int j = l;j <= r;j++) {
//			cout << endl << endl << endl;
			dfs(a[i][j]);
		}
	}
	for(int i = 1;i <= tot;i++) {
		if(l == 3 && r == 4) {
//			cout << "ans = " << ans[i] << endl;
		}
		if(ans[i] > max(t,n * s)) {
			int val = ans[i] - max(t,n * s);
			int x = (val - 1) / s + 1;
			int y = (val % s == 0 ? s : val % s);
			if(ans[i - 1] == a[x][y]);
			else swap(a[x][y],a[x][mid + 1 + y - l]);
		}
	}
	d[0] = 0;
	head[0] = -1;
	for(int i = 1;i <= n;i++) {
		for(int j = l;j <= r;j++) {
			d[a[i][j]] = 0;
			head[a[i][j]] = -1;
			d[Get(i,j)] = 0;
			head[Get(i,j)] = -1;
		}
	}
	for(int i = 0;i < cnt;i++) {
		vis[i] = 0;
		d[e[i].u] = 0;
		d[e[i].v] = 0;
		head[e[i].u] = -1;
		head[e[i].v] = -1;
	}
//	memset(d,0,sizeof d);
//	memset(vis,0,sizeof vis);
//	memset(head,-1,sizeof head);
	cnt = 0;
//	cout << "l = " << l << " r = " << r << endl;
//	for(int i = 1;i <= n;i++,puts(""))
//		for(int j = 1;j <= s;j++) cout << a[i][j] << " ";
	if(r - l == 1) return; 
	solve(l,mid),solve(mid + 1,r);
	return; 
} 
signed main() { 
//	freopen("P9731_23.in","r",stdin);
	memset(head,-1,sizeof head);
	cin >> n >> s >> t;
	for(int i = 1;i <= n;i++) {
		a[i].resize(s + 5); 
	}
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= s;j++) {
			cin >> a[i][j];
		}
	}
	solve(1,s);
	for(int i = 1;i <= n;i++,puts("")) {
		for(int j = 1;j <= s;j++) {
			cout << a[i][j] << " ";
		}
	}	
	return 0;
}
/*
3 8 5
2 3 5 1 5 5 4 4
3 5 1 1 2 3 2 2
1 3 3 2 2 5 3 4
3 2 5
4 1 
3 5
2 3
*/
```

---

## 作者：liyixin0514 (赞：2)

# [P9731 [CEOI2023] Balance](https://www.luogu.com.cn/problem/P9731)

## 题意转化

对每一行任意排序，使得每种颜色任意两列出现这种颜色的次数差不超过 $1$。

## solution

本题是一个分治的思想。

考虑 $s=2$ 的情况应该怎么做。直接做不是很好做，考虑转成图论来做。对于某一行 $(a_{i,1},a_{i,2})$，我们连无向边 $(a_{i,1},a_{i,2})$。交换操作可以看成给所有边定向。起点放在第一列，终点放在第二列。要求每种颜色在两列的出现次数的差不超过 $1$，可以转化为要求设计一种定向方式，使得每个点的入度和出度的差不超过 $1$。对于度数是偶数的点，显然入度和出度一定是度数的一半。对于度数是奇数的点，一个非常巧妙的方法是，建一个超级源点，和每一个度数为奇数的点连上一条边。因此要求转化成钦定一种定向方式，使得除了超级源点之外的所有点的入度等于出度。

如果你足够聪明，你会觉得这个很像欧拉回路。（由于不可能存在只有一个点的度数为奇数的情况，因此超级源点的度数也是偶数）欧拉回路可以满足所有点入度等于出度（包括超级源点）。~~其实我没有学过欧拉回路~~，假装我会了欧拉回路，那么直接跑一遍欧拉回路，给边定向，然后每条边起点放第一列，终点放第二列即可。

扩展到 $s=2$ 的幂的情况，其实 $2$ 的幂也许可以提示我们分治。

由上面的欧拉回路做法可以发现，我们随便搞一个图，连上超级源点后总是能跑出合法回路的，也就是说随便涂颜色都可以构造出合法方案。

于是正解来了。我们把矩形分成两部分，$1 \sim \frac{s}{2},\frac{s}{2}+1 \sim s$，然后把它们看做左右两部，类似与两列的情况连边跑欧拉回路，构造出满足所有颜色在左部的数量和在右部的数量之差 $\le 1$。连边就每一行之间随便连，满足一个左部的点连着一个右部的点就行了，因为你目前只需要关心这个点被构造到左部还是右部，并不关心它实际上在哪一列，这个是细分后才需要关心的事情。然后我们再分治左右。

这样做是正确的。因为你每一次都一定能构造出满足左右数量差 $\le 1$ 的方案。类似于线段树每一层节点长度差不超过 $1$，因此最后你构造出的方案也满足每一列数量差不超过 $1$。

时间复杂度：分治 $\log s$ 次，每次 $ns$ 的时间连边以及跑欧拉回路构造方案，一共 $O(ns \log s)$。

## code

```cpp
#include<bits/stdc++.h>
// #define LOCAL
#define sf scanf
#define pf printf
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
using namespace std;
typedef long long ll;
#define isdigit(x) (x>='0'&&x<='9')
template <typename T>
void read(T &x) {
	x=0;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) ;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
}
template <typename T>
void write(T x,char ch) {
	static int st[20];
	int top=0;
	do {
		st[top++]=x%10;
		x/=10;
	}while(x);
	while(top) putchar(st[--top]+'0');
	putchar(ch);
}
const int N=5e5+7;
int n,s,T;
int a[N];
struct edge {
	int to,ne;
}e[N<<1];
int vi[N<<1];
int head[N],cnt;
int du[N];
int f(int i,int j) { return i*s+j; }
void addedge(int u,int v) { e[++cnt]={v,head[u]}; head[u]=cnt; }
void _addedge(int u,int v) { du[u]++,du[v]++; addedge(u,v),addedge(v,u); }
void init(int l,int r) {
	memset(vi,0,sizeof(int)*(cnt+3));
	cnt=1;
	head[0]=0,du[0]=0;
	rep(i,l,r) rep(j,0,n-1) head[a[f(j,i)]]=0,du[a[f(j,i)]]=0;
	int mid=(l+r)>>1;
	rep(i,l,mid) rep(j,0,n-1) _addedge(a[f(j,i)],a[f(j,i+mid-l+1)]);
	rep(i,l,r) rep(j,0,n-1) if(du[a[f(j,i)]]&1) _addedge(0,a[f(j,i)]);
}
void dfs(int u) {
	for(int &i=head[u];i;) {
		if(vi[i]) { i=e[i].ne; continue; }
		int v=e[i].to;
		vi[i]=1;vi[i^1]=2;
		i=e[i].ne;dfs(v);
	}
}
void work(int l,int r) {
	int c=1;
	int mid=(l+r)>>1;
	rep(i,l,mid) rep(j,0,n-1) { ++c; if(vi[++c]==1) swap(a[f(j,i)],a[f(j,i+mid-l+1)]); }
}
void oula(int l,int r) {
	init(l,r);
	dfs(0);
	rep(i,l,r) rep(j,0,n-1) dfs(a[f(j,i)]);
	work(l,r);
}
void solve(int l,int r) {
	if(l==r) return;
	oula(l,r);
	int mid=(l+r)>>1;
	solve(l,mid),solve(mid+1,r);
}
int main() {
	#ifdef LOCAL
	// freopen("in.txt","r",stdin);
	freopen("my.out","w",stdout);
	#endif
	read(n),read(s),read(T);
	rep(i,0,n*s-1) read(a[i]);
	solve(0,s-1);
	rep(i,0,n-1) { rep(j,0,s-1) write(a[f(i,j)],' '); putchar('\n'); }
} 
```

---

## 作者：RedreamMer (赞：2)

  敢松敢过！不知道我的做法是不是正解。

  题目首先很友善地告诉了我们，对于任意 $N, S, T$ 以及任意得到的矩阵都是有解的，那么考虑分治。

  将 $S \gets \frac S 2$ 后，若一个颜色原本是 $kS + p$ 个，因为最终是需要 $S - p$ 列次数是 $k$，$p$ 列次数是 $k + 1$，那么构造的划分只需要满足较小的一边颜色个数大于等于 $\frac {kS} 2$，这是充要条件。

  然而这并不好构造，但是我们敢放缩限制，尝试构造一个解满足对于所有颜色，左侧数量和右侧数量差不大于 $1$。

  还是不好做，但感觉还是有 xjb 尝试的空间，考虑同一行的所有元素先将同色的一左一右两两配对，用剩下的元素得到 $n$ 行关于颜色的 01 矩阵，那么问题转化成需要给每个 $1$ 赋值 $\pm 1$，使得每一列的和为 $[-1, 1]$。

  考虑用图论解决这个问题，对于每一行，将每相邻两个 $1$ 的颜色两两配对连边，需要给所有边上的两个颜色分配 $\pm 1$ 的贡献。

  发现对于一个环是可以直接删去，那么可以删除若干个简单环，使得最后剩下森林，而森林的做法是简单的。

  现在就能做了，每轮分治处理建边，找环可以类似无向图 tarjan 的那套理论在 dfs 树上操作，注意复杂度不要写假以及清空就行了。

---

## 作者：CommandSR (赞：1)

## 题意

[link](https://www.luogu.com.cn/problem/P9731)

## 题解

首先考虑 $S=2$ 怎么做，每道题两个时刻评测数之差不超过 $1$ 让我们联想到欧拉路径入度和出度之差不超过 $1$。考虑跑欧拉路径对某两个评测进行定向，连一条 $A$ 和 $B$ 的无向边，若欧拉路径中方向为 $A \rightarrow B$，则先跑 $A$ 再跑 $B$。

所以我们给每一行开一个大点，每一种颜色（每一道题）也开一个大点，但是跑欧拉路径的前提是每个点度数为偶数，所以再开一个超级源点，和每一个奇数度数的点连边。

接下来考虑推广到 $S=2^k$，考虑分治，每一次分治确定了两个部分评测数之差不超过 $1$，然后继续分治，这样就确保了每一列都满足条件。

## Code

```cpp
// Problem: P9731
#include <bits/stdc++.h>
#define ll long long
#define sz(x) (int)x.size()
#define F(i, a, b) for (int i = (a); i <= (b); ++i)
#define D(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
inline ll rd() {
	ll x = 0; bool f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = 0; ch = getchar(); }
	while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return (f ? x : (-x));
}
// 先 a 后 b => a -> b, 入度和出度的差不超过 1 <=> 在这两个时刻，这个题的被评测的提交的数量之差不超过 1
const int N = 5e5 + 5;
int n, s, carl;
vector<int> a[N];
struct E { int to, nxt; } e[N<<3];
int hd[N], ec = 1, id, idx[N], col[N], deg[N], pl[N], pr[N];
bool vis[N], used[N<<2];
void Ae(int u, int v) { e[++ec] = (E){v, hd[u]}, hd[u] = ec; }
void Init() {
	F(i, 1, id) deg[i] = col[i] = hd[i] = vis[i] = pl[i] = pr[i] = 0;
	memset(idx, 0, sizeof idx);
	F(i, 1, ec) used[i] = 0;
}
void Dfs(int u) { // dfs 欧拉路径并根据欧拉路径对点的先后顺序定向
	vis[u] = 1;
	for (int i = hd[u]; i; i = hd[u]) {
		int v = e[i].to;
		hd[u] = e[i].nxt;
		if (used[i ^ 1]) continue;
		used[i] = used[i ^ 1] = 1;
		Dfs(v);
		// 这里的 u, v 一定不都是每一行对应的"大点"，if 判断是否为大点，如果是 则另外一方是颜色对应点，一定被染色，再根据指向方向判断放在左还是右
		if (u <= n) a[u][pr[u]--] = col[v];
		if (v <= n) a[v][pl[v]++] = col[u];
	}
}
void Solve(int l, int r) {
	if (l >= r) return;
	int mid = (l + r) >> 1;
	id = n, ec = 1; // 每一行开一个大点，一开始有 n 个大点
	F(i, 1, n) pl[i] = l, pr[i] = r;
	F(i, 1, n) {
		F(j, l, r) {
			if (!idx[a[i][j]]) idx[a[i][j]] = ++id, col[id] = a[i][j]; // 对每个颜色开一个点
			Ae(i, idx[a[i][j]]), Ae(idx[a[i][j]], i);
			++deg[i], ++deg[idx[a[i][j]]];
		}
	}
	++id; // 再建一个大点和所有奇数度数的点连边
	F(i, n + 1, id - 1) if (deg[i] & 1) Ae(i, id), Ae(id, i);
	F(i, 1, id) if (!vis[i]) Dfs(i);
	Init();
	Solve(l, mid), Solve(mid + 1, r);
}
int main() {
	n = rd(), s = rd(), carl = rd();
	F(i, 1, n) {
		a[i].resize(s + 1);
		F(j, 1, s) a[i][j] = rd();
	}
	Solve(1, s);
	F(i, 1, n) {
		F(j, 1, s) cout << a[i][j] << ' ';
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：Petit_Souris (赞：1)

very cool problem。

部分分这么多，从部分分开始做肯定是有道理的。

$S = 2$ 是个有道理的部分分。我们要对于每个评测机 $(A, B)$ 决定是先测 $A$ 还是先测 $B$。

一个方案是合法的当且仅当一个题在两个时刻评测次数相差不超过 $1$。这让我们联想到欧拉路径：入度出度之差不超过 $1$。因此我们重新刻画问题：在 $A, B$ 间连一条无向边，找出一条欧拉路径。那么沿着欧拉路径的方向定向，如果 $A$ 指向 $B$ 就把 $A$ 排在前面，否则 $B$ 排在前面。

现在考虑 $S = 2 ^ k$。这样可以想到分治：我们可以把所有时刻分成两半 $L, R$。我们能得到两个相差 $\le 1$ 的部分，继续递归下去，显然不会出现新的差距 $\ge 2$ 的两个时刻。因此就做完了。

```cpp
#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using namespace std;
template <class T>
using Ve = vector<T>;
#define pii pair<ll, ll>
#define rep(i, a, b) for(ll i = (a); i <= (b); ++i)
#define per(i, a, b) for(ll i = (a); i >= (b); --i)
#define pb push_back
bool Mbe;
ll read() {
    ll x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}
void write(ll x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const ll N = 5e5 + 9;
ll n, S, T;
Ve<Ve<ll> > a;
Ve<pii> to[N];
pii e[N];
ll tote, path[N], plen, top[N];
bool vis[N], go[N];
ll cL, cM;
void dfs(ll x) {
    go[x] = 1;
    while(top[x] < (ll)to[x].size()) {
        auto [y, w] = to[x][top[x]];
        ll id = abs(w);
        ++top[x];
        if(vis[id]) continue;
        vis[id] = 1;
        dfs(y);
        if(~e[id].first) {
            if(w < 0) {
                swap(a[e[id].first][cL + e[id].second], a[e[id].first][cM + 1 + e[id].second]); 
            }
        }
    }
}
void solve(ll l, ll r) {
    if(l == r) return ;
    ll mid = (l + r) >> 1, len = mid - l + 1;
    cL = l, cM = mid;
    Ve<ll> pt;
    rep(i, 0, n - 1) {
        rep(j, l, r) pt.pb(a[i][j]);
    }
    pt.pb(0);
    sort(pt.begin(), pt.end());
    pt.resize(unique(pt.begin(), pt.end()) - pt.begin());
    rep(i, 0, tote) vis[i] = 0;
    tote = 0, plen = 0;
    for(ll x : pt) to[x].clear(), top[x] = 0, go[x] = 0;
    rep(i, 0, n - 1) {
        rep(j, 0, len - 1) {
            ll x = a[i][l + j], y = a[i][mid + 1 + j];
            ++tote, e[tote] = {i, j};
            to[x].pb({y, tote}), to[y].pb({x, -tote});
        }
    }
    for(ll x : pt) {
        if(!x) continue;
        if(to[x].size() & 1) {
            ++tote, e[tote] = {-1, -1};
            to[0].pb({x, tote}), to[x].pb({0, -tote});
        }
    }
    for(ll x : pt) {
        if(!go[x]) dfs(x);
    }
    solve(l, mid), solve(mid + 1, r);
}
bool Med;
int main() {
    cerr << fabs(&Med - &Mbe) / 1048576.0 << "MB\n";
    n = read(), S = read(), T = read();
    a = Ve<Ve<ll> > (n, Ve<ll>(S));
    rep(i, 0, n - 1) {
        rep(j, 0, S - 1) a[i][j] = read();
    }
    solve(0, S - 1);
    rep(i, 0, n - 1) {
        rep(j, 0, S - 1) write(a[i][j]), putchar(' ');
        putchar('\n');
    }
    cerr << "\n" << clock() * 1.0 / CLOCKS_PER_SEC * 1000 << "ms\n";
    return 0;
}
```

---

## 作者：Composite_Function (赞：1)

做了 2h，还是太菜了。

怎么有人把这么难的题放 T2 啊。

---

注意到 $k$ 是 $2$ 的幂。所以肯定是往分治上面想。$k=2$ 是一个入手点。

然后有一个非常典的 trick。把 $n$ 行看成 $n$ 条边。交换相当于给边定向，需要最终满足点的入度和出度差不超过 $1$。

出度和入度相差非常小，这很欧拉回路。所以我们考虑跑欧拉回路，但是这个图不一定满足它能跑欧拉回路，因为会有度数是奇数的点。

关键解决点是把所有奇数点向一个新点连边，然后跑欧拉回路。最终定向结果只需要保留原来图上的边，其余边去除，这样每个点最多会被去掉 $1$ 条边，出度和入度差便不会超过 $1$。

接下来考虑一般的 $k$。考虑将当前区间左右两半处理好，使得左右两半每个数出现次数相差不超过 $1$。再分治处理两半。只需要在上述操作中改成每一行列 $i$ 和 $l+r-i$ 的连边即可。

正确性：只需要保证相差不超过 $1$ 的两个数分别分成若干相差不超过 $1$ 的数后相差还是不超过 $1$。不妨两个数本来是 $k$ 和 $k+1$，都分成 $l$ 个数。只需要验证 $\lceil \frac{k+1}{l} \rceil - \lfloor \frac{k}{l} \rfloor \le 1$。这是肯定的，因为 $\lceil \frac{k+1}{l} \rceil = \lfloor \frac{k+1+l-1}{l} \rfloor=\lfloor \frac{k}{l} \rfloor+1$。

那么接下来只需要 dirty work 了。一个简便的写法是在连两个点建立出一个新点并储存这个点是对应哪几个点连起来，最后得到回路的时候把这个点对应的信息交换即可。写了 4k 的依托就不好意思端上来了。

---

## 作者：tribool4_in (赞：1)

首先考虑 $S=2$ 的部分分。考虑将此时给定的点对直接作为无向边建图。此时发现原问题相当于给无向边定向，使得每个点的入度与出度至多相差 $1$。发现这和欧拉路径相似，但是奇度点的个数可能大于 $2$。不过这些奇度点的最后一个所在位置并不重要，可以让奇度点之间两两连边或创造一个虚电与之连边。这样跑一遍欧拉回路即可。

对于 $S=2^k$，考虑对 $S$ 大力分治。将当前的 $S=2^k$ 划成两部分，每部分有 $2^{k-1}$ 个。这个划分过程需要使得每种数字在两部分的出现次数相差至多 $1$。此时沿用 $S=2$ 的做法，考虑如何建图。考虑对于每行建立一个点，将每个数字向其所在行连边，对于奇度点一样处理。此时同样相当于需要使每个数字点的入度与出度相等（因为处理了奇度点）。直接跑欧拉回路，每个数与行点的边方向即决定其分在哪边。划分完后分治下去继续做即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int n, s, t;
vector<int> v[N];
vector<pair<int, int>> G[N];
pair<int, int> ans[N];
bool vis[N << 1];
void dfs(int u) {
    while (!G[u].empty()) {
        auto [v, e] = G[u].back();
        G[u].pop_back();
        if (vis[e]) continue;
        vis[e] = 1;
        ans[e] = {u, v};
        dfs(v);
    }
}
void add_edge(int u, int v, int id) { G[u].emplace_back(v, id), G[v].emplace_back(u, id); }
int deg[N], id[N], ls[N], lp[N], rp[N];
void solve(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1, cnt = 0, eid = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = l; j <= r; j++) {
            if (!id[v[i][j]]) ls[id[v[i][j]] = ++cnt] = v[i][j];
            deg[v[i][j]] += 1;
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = l; j <= r; j++) add_edge(id[v[i][j]], i + cnt, ++eid);
    int tmp = eid;
    for (int i = 1; i <= cnt; i++)
        if (deg[ls[i]] & 1) add_edge(i, n + cnt + 1, ++eid);
    for (int i = 1; i <= n + cnt + 1; i++) dfs(i);
    for (int i = 1; i <= n; i++) lp[i] = l, rp[i] = r;
    for (int i = 1; i <= tmp; i++) {
        auto [iu, iv] = ans[i];
        if (iu <= cnt) v[iv - cnt][lp[iv - cnt]++] = ls[iu];
        if (iv <= cnt) v[iu - cnt][rp[iu - cnt]--] = ls[iv];
    }
    memset(vis, 0, sizeof(bool) * (eid + 1));
    for (int i = 1; i <= n + cnt + 1; i++) G[i].clear(), deg[ls[i]] = id[ls[i]] = 0;
    solve(l, mid), solve(mid + 1, r);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> s >> t;
    for (int i = 1; i <= n; i++) {
        for (int j = 1, x; j <= s; j++) {
            cin >> x;
            v[i].push_back(x);
        }
    }
    solve(0, s - 1);
    for (int i = 1; i <= n; i++) {
        for (auto u : v[i]) cout << u << ' ';
        cout << '\n';
    }
    return 0;
}
```

---

## 作者：Felix72 (赞：0)

解这道题的关键在于注意到题目给出的条件意味着什么。

如果不管某些性质直接做这道题的话，那这就是形如 [	[AGC037D] Sorting a Grid](https://www.luogu.com.cn/problem/AT_agc037_d) 的问题，多半要用到网络流模型，是很难做到较低的复杂度的。

于是考虑题目给出的两个不同于一般题目的性质：

- $S = 2^k$；
- 所有此类问题均存在解法。

那么出题人或许是在提示我们分治。揣摩一下，如果先把所有元素尽量均匀地分到两边，再对这两边继续递归地分下去，那么确实可以归纳证明，每个部分中的同种元素个数极差 $\leq 1$。那么分析如何尽量均匀地分配即可。

我们进一步发现，存在 $S = 2$ 的部分分，而上面这个问题是严格弱于这档部分分的（这是因为两个问题都形如把若干行，每行 $x$ 个元素均分到两边，显然 $x$ 越小越难做）。于是我们转而考虑 $S = 2$ 的部分分。

这档部分分给出若干二元组，要求两个元素必须一左一右地分配。这是 p2p 限制，考虑图论建模，其图论意义就是给无向边定向，使得出入度数之间相差不超过 $1$。

这个问题并不难，提取若干条极长欧拉路径就可以了。当然，为了方便实现，也可以像其他题解说的那样加一个虚点，然后跑欧拉回路。

```cpp
/* Good Game, Well Play. */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 100010, SZ = 500010;
int n, m, k; vector < int > mp[N];

struct Table
{
	int state[N]; bool vis[N]; queue < int > q;
	inline void ref(int pos) {if(!vis[pos]) {vis[pos] = true, q.push(pos);}}
	inline void modify(int pos, int x) {ref(pos); state[pos] = x;}
	inline int query(int pos) {return state[pos];}
	inline void clear()
	{
		while(!q.empty())
		{
			vis[q.front()] = false;
			state[q.front()] = 0; q.pop();
		}
	}
}; Table tb;

namespace Solve
{
	struct Edge {int to, id;}; vector < Edge > tr[N];
	struct Posi {int x, y;}; Posi ps_mp[SZ];
	bool tag[SZ], vis[N]; int eid, deg[N];
	inline void find_path(int pos, int len)
	{
		vis[pos] = true;
		while(!tr[pos].empty())
		{
			Edge li = tr[pos].back(); tr[pos].pop_back();
			if(tag[li.id]) continue;
			tag[li.id] = true;
			find_path(li.to, len);
			if(ps_mp[li.id].x)
			{
				int x = ps_mp[li.id].x, y = ps_mp[li.id].y;
				mp[x][y] = li.to, mp[x][y + len] = pos;
			}
		}
	}
	inline void work(int l, int mid, int r)
	{
		int len = mid - l + 1; vector < int > rec; tb.clear();
		for(int i = 1; i <= n; ++i)
			for(int j = l; j <= r; ++j)
				if(!tb.query(mp[i][j]))
					tb.modify(mp[i][j], 1), rec.push_back(mp[i][j]);
		for(int x : rec) deg[x] = 0, tr[x].clear(), vis[x] = false;
		eid = 0;
		for(int i = 1; i <= n; ++i)
		{
			for(int j = l; j <= mid; ++j)
			{
				++eid; tag[eid] = false; ps_mp[eid] = {i, j};
				++deg[mp[i][j]], ++deg[mp[i][j + len]];
				tr[mp[i][j]].push_back({mp[i][j + len], eid});
				tr[mp[i][j + len]].push_back({mp[i][j], eid});
			}
		}
		for(int x : rec)
		{
			if(deg[x] % 2 == 1)
			{
				++eid; tag[eid] = false; ps_mp[eid] = {0, 0};
				++deg[x], ++deg[k + 1];
				tr[x].push_back({k + 1, eid});
				tr[k + 1].push_back({x, eid});
			}
		}
		for(int x : rec) if(!vis[x]) find_path(x, len);
	}
	inline void solve(int l, int r)
	{
		if(l == r) return ;
		int mid = (l + r) >> 1;
		work(l, mid, r);
		solve(l, mid), solve(mid + 1, r);
	}
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m >> k;
	for(int i = 1; i <= n; ++i)
	{
		mp[i].resize(m + 1);
		for(int j = 1; j <= m; ++j)
			cin >> mp[i][j];
	}
	Solve::solve(1, m);
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 1; j <= m; ++j)
			cout << mp[i][j] << " ";
		cout << '\n';
	}
	return 0;
}
/*

*/
```

---

