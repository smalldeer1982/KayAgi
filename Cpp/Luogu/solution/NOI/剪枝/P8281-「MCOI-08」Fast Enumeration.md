# 「MCOI-08」Fast Enumeration

## 题目描述

Technoblade 将 Skyblock 抽象为一张 $n$（$n\le 50$）节点 $m$ 条边的简单有向图。他需要求出该图 **所有** 哈密尔顿回路，即所有排列 $p_1,p_2,\dots,p_n$ 使得 $p_1=1$ 并且 $p_1\to p_2\to \dots\to p_{n-1}\to p_n\to p_1$ 为一个合法路径。

**数据保证哈密尔顿回路数量非零并小于 $10^4$**。

**数据从所有合法数据随机采样。**

## 说明/提示

#### 样例 1 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/lth4lrb1.png)

有 $1$ 个哈密尔顿回路：

 - $1\to2\to3\to1$。

#### 样例 2 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/if0vz8gm.png)

有 $1$ 个哈密尔顿回路：

 - $1\to3\to4\to2\to1$。

#### 样例 3 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/dv1tul62.png)

有 $2$ 个哈密尔顿回路：

 - $1\to2\to3\to4\to5\to1$；
 - $1\to2\to5\to3\to4\to1$。

#### 样例 4 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/wggv2mfd.png)

有 $2$ 个哈密尔顿回路：

 - $1\to2\to3\to4\to5\to1$；
 - $1\to3\to5\to2\to4\to1$。

#### 样例 5 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/cfi80wob.png)

有 $3$ 个哈密尔顿回路：

 - $1\to5\to2\to3\to4\to6\to1$；
 - $1\to5\to2\to4\to6\to3\to1$；
 - $1\to5\to3\to4\to6\to2\to1$。

#### 样例 6 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/wqd9tpl8.png)

有 $2$ 个哈密尔顿回路：

 - $1\to3\to2\to4\to6\to5\to1$；
 - $1\to5\to4\to6\to3\to2\to1$。

#### 样例 7 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/jff0k373.png)

有 $1$ 个哈密尔顿回路：

 - $1\to6\to5\to2\to4\to3\to1$。

#### 样例 8 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/x2j19zoc.png)

有 $12$ 个哈密尔顿回路：

 - $1\to2\to5\to4\to6\to3\to1$；
 - $1\to2\to5\to6\to3\to4\to1$；
 - $1\to5\to2\to3\to6\to4\to1$；
 - $1\to5\to2\to4\to6\to3\to1$；
 - $1\to5\to4\to6\to2\to3\to1$；
 - $1\to5\to4\to6\to3\to2\to1$；
 - $1\to5\to6\to2\to3\to4\to1$；
 - $1\to5\to6\to3\to2\to4\to1$；
 - $1\to5\to6\to3\to4\to2\to1$；
 - $1\to5\to6\to4\to2\to3\to1$；
 - $1\to6\to3\to2\to5\to4\to1$；
 - $1\to6\to3\to4\to2\to5\to1$。

#### 数据规模与约定

对于固定 $n$ 和 $P$，任意一张 $m$ 条边的图权重为 $\left(\frac{1}{P}\right)^m\left(\frac{P-1}{P}\right)^{n^2-n-m}$。

 - Subtask 1（1 pts）：为样例。
 - Subtask 2（16 pts）：$n=15$。
 - Subtask 3（20 pts）：$n=30$。
 - Subtask 4（26 pts）：$n=40$。
 - Subtask 5（37 pts）：$n=50$。


## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1```

### 输出

```
1 2 3```

## 样例 #2

### 输入

```
4 6
1 3
1 4
2 1
2 3
3 4
4 2```

### 输出

```
1 3 4 2```

## 样例 #3

### 输入

```
5 8
1 2
2 3
3 4
4 1
2 5
4 5
5 1
5 3```

### 输出

```
1 2 3 4 5
1 2 5 3 4```

## 样例 #4

### 输入

```
5 10
1 2
1 3
2 3
2 4
3 4
3 5
4 1
4 5
5 1
5 2```

### 输出

```
1 2 3 4 5
1 3 5 2 4```

## 样例 #5

### 输入

```
6 15
1 3
1 4
1 5
2 1
2 3
2 4
3 1
3 4
4 2
4 6
5 2
5 3
6 1
6 2
6 3```

### 输出

```
1 5 2 3 4 6
1 5 2 4 6 3
1 5 3 4 6 2```

## 样例 #6

### 输入

```
6 15
1 3
1 5
2 1
2 4
3 1
3 2
3 4
3 5
3 6
4 6
5 1
5 4
5 6
6 3
6 5```

### 输出

```
1 3 2 4 6 5
1 5 4 6 3 2```

## 样例 #7

### 输入

```
6 16
1 3
1 6
2 3
2 4
2 6
3 1
3 6
4 2
4 3
4 5
4 6
5 2
5 6
6 1
6 3
6 5```

### 输出

```
1 6 5 2 4 3```

## 样例 #8

### 输入

```
6 21
1 2
1 5
1 6
2 1
2 3
2 4
2 5
3 1
3 2
3 4
3 6
4 1
4 2
4 6
5 1
5 2
5 4
5 6
6 2
6 3
6 4```

### 输出

```
1 2 5 4 6 3
1 2 5 6 3 4
1 5 2 3 6 4
1 5 2 4 6 3
1 5 4 6 2 3
1 5 4 6 3 2
1 5 6 2 3 4
1 5 6 3 2 4
1 5 6 3 4 2
1 5 6 4 2 3
1 6 3 2 5 4
1 6 3 4 2 5```

# 题解

## 作者：w33z8kqrqk8zzzx33 (赞：6)

本题非 DLX 做法时间复杂度可以证明。

将 dfs 搜索空间抽象为一棵树，节点个数 $n!$，深度 $n$。每一个节点对应原图中固定回路。如果对于任何节点可以 $O(T(n,m))$ 判断子树内是否有解，可以 $O(T(n,m)Kn^2)$ 找出所有回路。

确定子树内是否有解就是钦定某些点在最终回路中的出边，判断可否完成回路。通过 deletion-contraction 删掉不可能选的边，缩掉钦定选的边，将问题转化成判断 D-C 后的图是否存在回路。

判断回路是否存在可以用一些启发式，比如调整法，最后时间复杂度 $O(Kn^4)$。当然用更弱得出可能有解而不是肯定有解也可以剪掉足够多的节点，这样的时间复杂度相对难证。

---

## 作者：OrangeRED (赞：4)

求所有哈密顿回路，这玩意是个 $ O(n!) $ 啊，有点吓人。

注意到一条特殊性质：

**对于一条哈密顿回路，每一个点的入度与出度都为 $ 1 $。**

有了这一条性质，我们可以直接马上立刻把问题转化为一个精确覆盖问题，并使用舞蹈链（Dancing Links X）解决掉。

什么，你还不会舞蹈链，建议看一下其他大佬的博客。

或者[我的](https://www.cnblogs.com/OrangeRED/p/18714847)也行（逃。

模型构建：

每一行为一条边 $ (x,y) $，插入两个点 $ (i,x) $ 与 $ (i,y+n) $，分别表示 $ x $ 只能入度为 $ 1 $，$ y $ 只能出度为 $ 1 $。

在舞蹈链上面跑出要选择的边，在统计所有答案就行啦！吗？最后一点，这样跑出来的方案只能保证入度出度为 $ 1 $，所以有可能是几个环而不是一个，验证一下即可。

时间复杂度：玄学，一共大概有 $ n^2 $ 条边，$ O(C^{2n^2})(C \approx 1) $，能过， 因为舞蹈链 nb。

空间复杂度：$ O(n^2) $。

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
int n, m, id, ans;
int L[N], R[N], U[N], D[N], first[N], rec[N];
int colcnt[N], col[N], row[N];
struct node {
	int x, y;
}dat[N]; //边的记录
inline void build(int c) {
	for (int i = 0; i <= c; i++) {
		L[i] = i - 1, R[i] = i + 1;
		U[i] = i, D[i] = i;
	}
	L[0] = c, R[c] = 0, id = c + 1;
}
inline void remove(int x) {
	R[L[x]] = R[x], L[R[x]] = L[x];
	for (int y = U[x]; y != x; y = U[y]) {
		for (int z = R[y]; z != y; z = R[z]) {
			U[D[z]] = U[z], D[U[z]] = D[z];
			colcnt[col[z]]--;
		}
	}
}
inline void recover(int x) {
	R[L[x]] = x, L[R[x]] = x;
	for (int y = U[x]; y != x; y = U[y]) {
		for (int z = R[y]; z != y; z = R[z]) {
			U[D[z]] = z, D[U[z]] = z;
			colcnt[col[z]]++;
		}
	}
}
inline void insert(int r, int c) {
	id++;
	row[id] = r, col[id] = c;
	colcnt[c]++;
	U[id] = c, D[id] = D[c], U[D[c]] = id, D[c] = id;
	if (!first[r]) first[r] = L[id] = R[id] = id;
	else {
		L[id] = first[r], R[id] = R[first[r]];
		L[R[first[r]]] = id, R[first[r]] = id;
	}
}
int nxt[60], resnum, vis[60]; //vis别开大啦，不然会TLE
std::vector<int> res[N];
inline void dance(int depth) {
	if (!R[0]) {
		memset(vis, 0, sizeof vis);
		for (int i = 0; i < depth; i++) nxt[dat[rec[i]].x] = dat[rec[i]].y;
		for (int now = 1; !vis[now]; now = nxt[now]) vis[now] = 1;
		for (int i = 1; i <= n; i++) if (!vis[i]) return; //验证是否为一个环
		res[++resnum].push_back(1);
		for (int i = nxt[1]; i != 1; i = nxt[i]) res[resnum].push_back(i);
		return;
	}
	int y = R[0];
	for (int i = R[0]; i; i = R[i]) {
		if (colcnt[i] < colcnt[y]) y = i;
	}
	remove(y);
	for (int i = D[y]; i != y; i = D[i]) {
		rec[depth] = row[i];
		for (int j = R[i]; j != i; j = R[j]) remove(col[j]);
		dance(depth + 1);
		for (int j = L[i]; j != i; j = L[j]) recover(col[j]);
	}
	recover(y);
}
inline bool cmp(std::vector<int> x, std::vector<int> y) {
	for (int i = 1; i < n; i++) {
		if (x[i] == y[i]) continue;
		return x[i] < y[i];
	}
}
int main() {
	cin >> n >> m;
	build(n * 2);
	for (int i = 1; i <= m; i++) {
		cin >> dat[i].x >> dat[i].y;
		insert(i, dat[i].x), insert(i, dat[i].y + n);
	}
	dance(0);
	sort(res + 1, res + resnum + 1, cmp);
	for (int i = 1; i <= resnum; i++) {
		for (int j = 0; j < n; j++) cout << res[i][j] << ' ';
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：Register_int (赞：3)

直接求哈密顿路径显然会炸掉，但是这玩意是个 NPC……  
真的没办法了吗？显然不是。  
首先讲一句废话：哈密尔顿路径是一个环。有什么用呢？可以考虑从原图中找出 $n$ 条边，将其拼接成一个环，那么我们就获得了一个 $O(m^n)$ 的算法。但好像比原来更垃圾了呢……  
这时就要考虑丢掉一些东西了。我们可以只要求这 $n$ 条边构成一个环，即每个点的入度及出度均为 $1$，具体是不是一个环最后再判断。接着，每个点入度及出度必须为 $1$，每一条边 $u,v$ 会给 $u$ 的出度、$v$ 的入度分别加 $1$。有没有想到一个常数巨小的数据结构呢？  
没错，就是舞蹈链。转化为精确覆盖问题后求解，将所有符合要求的组合记录下来，最后按字典序排序即可。  
时间复杂度是惊人的 $O(m^n)$，但是能过，因为舞蹈链 nb。代码看一乐就好，写的太丑了。
```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 4e5;

struct edge {
	int u, v;
	bool operator < (const edge &rhs) const { return u == rhs.u ? v < rhs.v : u < rhs.u; }
} a[60];

int n, m, nxt[60];

vector<int> res[10010]; int num;

bool vis[60];

struct DancingLinksX {
	
	int n, m, cnt;
	
	int l[MAXN], r[MAXN], u[MAXN], d[MAXN], row[MAXN], col[MAXN];
	int head[MAXN], size[MAXN];
	int ans[MAXN];
	
	inline 
	void init(int _n = 0, int _m = 0) {
		n = _n, m = _m;
		for (int i = 0; i <= m; i++) r[i] = i + 1, l[i] = i - 1, u[i] = d[i] = i;
		r[m] = 0, l[0] = m;
		memset(head, 255, sizeof head);
		memset(size, 0, sizeof size);
		cnt = m + 1;
	}
	
	inline 
	void link(int x, int y) {
		size[y]++;
		row[cnt] = x, col[cnt] = y;
		u[cnt] = y, d[cnt] = d[y], u[d[y]] = cnt, d[y] = cnt;
		if (head[x] == -1) head[x] = r[cnt] = l[cnt] = cnt;
		else {
			r[cnt] = head[x], l[cnt] = l[head[x]];
			r[l[head[x]]] = cnt, l[head[x]] = cnt;
		}
		cnt++;
	}
	
	inline 
	void remove(int p) {
		r[l[p]] = r[p], l[r[p]] = l[p];
		for (int i = d[p]; i != p; i = d[i]) {
			for (int j = r[i]; j != i; j = r[j]) u[d[j]] = u[j], d[u[j]] = d[j], size[col[j]]--;
		}
	}
	
	inline 
	void resume(int p) {
		for (int i = u[p]; i != p; i = u[i]) {
			for (int j = l[i]; j != i; j = l[j]) u[d[j]] = j, d[u[j]] = j, size[col[j]]++;
		}
		r[l[p]] = p, l[r[p]] = p;
	}
	
	void dance(int step) {
		if (r[0] == 0) {
			memset(vis, 0, sizeof vis);
			for (int i = 0; i < step; i++) nxt[a[ans[i]].u] = a[ans[i]].v;
			for (int p = 1; !vis[p]; p = nxt[p]) vis[p] = 1;
			for (int i = 1; i <= ::n; i++) if (!vis[i]) return ;
			res[++num].push_back(1);
			for (int p = nxt[1], i = 2; p != 1; p = nxt[p], i++) res[num].push_back(p);
			return ;
		}
		int p = r[0];
		for (int i = r[0]; i; i = r[i]) {
			if (size[i] < size[p]) p = i;
		}
		remove(p);
		for (int i = d[p]; i != p; i = d[i]) {
			ans[step] = row[i];
			for (int j = r[i]; j != i; j = r[j]) remove(col[j]);
			dance(step + 1);
			for (int j = l[i]; j != i; j = l[j]) resume(col[j]);
		}
		resume(p);
	}
	
} DLX;

inline 
bool cmp(vector<int> x, vector<int> y) {
	for (int i = 1; i < n; i++) {
		if (x[i] < y[i]) return 1;
		if (x[i] > y[i]) return 0;
	}
}

int main() {
	scanf("%d%d", &n, &m), DLX.init(m, n * 2);
	for (int i = 1; i <= m; i++) scanf("%d%d", &a[i].u, &a[i].v), DLX.link(i, a[i].u), DLX.link(i, n + a[i].v);
	DLX.dance(0);
	sort(res + 1, res + num + 1, cmp);
	for (int i = 1; i <= num; i++) {
		for (int j = 0; j < n; j++) printf("%d ", res[i][j]); puts("");
	}
}
```

---

## 作者：黑影洞人 (赞：1)

>求一个图（ $n\le 50$ 个点，$m$ 条边）所有哈密尔顿回路，递增排列字典序输出，起点默认为 $1$。

这道题很容易想到一个爆搜，每个点暴力往下选连接的点，直到找到所有回路，复杂度为 $O(n!)$，但是这样显然复杂度过大，会超时。

也可以进行全排列枚举，不过复杂度也是 $O(n!)$。

我们需要一个高效的做法。

发现题目问题可以转化，一个哈密尔顿回路上一定有 $n$ 个点。因此问题转化为：

>总共有 $m$ 条边，从 $m$ 条边里选出 $k$ 条边，使得形成一个哈密尔顿回路(这些边链接的点的集合包含所有点)

这很像是一个精准覆盖问题，但是点会被多次覆盖，这样子显然是不满足精准覆盖问题的。

但是如果形成哈密尔顿回路，那么每个点正好会被覆盖两次（出边一次，入边一次），于是我们把入点和出点的编号重新编一下，每条边对应的两个覆盖点分别是一个入点和一个出点，出点指向入点。

只需要将出点的编号全部 $+n$，这样就可以完美地对应哈密尔顿回路的条件。

然后建立 Dancing Links，跑一遍 DLX 算法就可以解决。

值得注意的是，可能会处于一些路径覆盖的点数不足 $n$ 个，这些路径不能参与输出。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#define N 466660
using namespace std;
int n,m;
struct edge{
	int u,v;
}a[N];
int nxt[N];
bool vis[62];
int cnt;
vector<int>v[N];
struct dancing_links_x{
	int m;
	int left[N],right[N];
	int up[N],down[N];
	int col[N],row[N],siz[N],head[N],tot;
	int ans[N];
	void csh(int m){
		this->m=m;
		for(int i=0;i<=m;i++)left[i]=i-1,right[i]=i+1,up[i]=down[i]=i;
		left[0]=m,right[m]=0;tot=m;
		memset(head,0,sizeof(head));
		memset(siz,0,sizeof(siz));
	}
	void insert(int r,int c){
		col[++tot]=c,row[tot]=r,siz[c]++;
		down[tot]=down[c],up[down[c]]=tot,up[tot]=c,down[c]=tot;
		if(!head[r])head[r]=left[tot]=right[tot]=tot;
		else{
			right[tot]=right[head[r]];
			left[right[head[r]]]=tot;
			left[tot]=head[r],right[head[r]]=tot;
		}
	}
	void del(int c){
		left[right[c]]=left[c];
		right[left[c]]=right[c];
		for(int i=down[c];i!=c;i=down[i]){
			for(int j=right[i];j!=i;j=right[j]){
				up[down[j]]=up[j];
				down[up[j]]=down[j];
				siz[col[j]]--;
			}
		}
	}
	void add(int c){
		for(int i=up[c];i!=c;i=up[i]){
			for(int j=left[i];j!=i;j=left[j]){
				up[down[j]]=down[up[j]]=j;
				siz[col[j]]++;
			}
		}
		left[right[c]]=right[left[c]]=c;
	}
	void dfs(int dep){
		if(!right[0]){
			memset(vis,0,sizeof(vis));
			for(int i=1;i<dep;i++)nxt[a[ans[i]].u]=a[ans[i]].v;
			for(int i=1;!vis[i];i=nxt[i])vis[i]=1;
			for(int i=1;i<=n;i++)if(!vis[i])return;
			cnt++;
			v[cnt].push_back(1);
			for(int i=nxt[1];i!=1;i=nxt[i])v[cnt].push_back(i);
			return;
		}
		int c=right[0];
		for(int i=right[0];i;i=right[i])if(siz[i]<siz[c])c=i;
		del(c);
		for(int i=down[c];i!=c;i=down[i]){
			ans[dep]=row[i];
			for(int j=right[i];j!=i;j=right[j])del(col[j]);
			dfs(dep+1);
			for(int j=left[i];j!=i;j=left[j])add(col[j]);
		}
		add(c);
		return;
	}
}dlx; 
bool cmp(vector<int> a,vector<int> b){
	for(int i=1;i<n;i++){
		if(a[i]<b[i])return 1;
		if(a[i]>b[i])return 0;
	}
	return 1;
}
signed main(){
	scanf("%d%d",&n,&m);
	dlx.csh(n*2);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a[i].u,&a[i].v);
		dlx.insert(i,a[i].u+n);
		dlx.insert(i,a[i].v);
	}
	dlx.dfs(1);
	sort(v+1,v+cnt+1,cmp);
	for(int i=1;i<=cnt;i++){
		for(int j=0;j<n;j++)printf("%d ",v[i][j]);
		puts("");
	}
	return 0;
}

```

---

