# The Fox and the Complete Tree Traversal

## 题目描述

给定整数 $n$ 和一棵包含 $n$ 个节点的树。  
记 $\text{Dist}(x,y)$ 表示树上节点 $x,y$ 之间最短路径的边数。  
你需要判断是否存在一个 $1\sim n$ 的排列 $p$，满足：

- $\text{Dist}(p_i,p_{i+1})\leq 2$ 对任意整数 $i(1\leq i<n)$ 成立。
- $\text{Dist}(p_1,p_n)\leq2$。

存在则输出 `Yes` 然后输出任意一个满足要求的 $p$，不存在则输出 `No`。

## 样例 #1

### 输入

```
5
1 2
1 3
3 4
3 5```

### 输出

```
Yes
4 5 1 2 3```

## 样例 #2

### 输入

```
3
1 2
1 3```

### 输出

```
Yes
1 2 3```

## 样例 #3

### 输入

```
15
1 2
1 3
2 4
2 5
3 6
3 7
4 8
4 9
5 10
5 11
6 12
6 13
7 14
7 15```

### 输出

```
No```

# 题解

## 作者：devans (赞：11)

感谢这题联合 1D 送我 $2782$ performance。  
如果你做过 [这个](https://www.luogu.com.cn/problem/P3549) 或者 [这个](https://www.luogu.com.cn/problem/P8173)，那么你将在场上绝杀这题。  

---



构造题以手玩小数据找规律为先。  
首先发现一条很长的链是好做的：你黑白染色一下绕一圈就行了。  
接下来尝试在这条长链的中间上挂支链：

- 发现挂长度为 $1$ 的支链的时候非常好做，依旧可以黑白染色然后绕一圈。  

![](https://cdn.luogu.com.cn/upload/image_hosting/34h5g1di.png)

- 发现挂长度大于等于 $2$ 的支链的时候，无解。  
_下面两张图对走法进行了分类讨论，展示了为什么找不到回环。_

![](https://cdn.luogu.com.cn/upload/image_hosting/292zx1vr.png)  
![](https://cdn.luogu.com.cn/upload/image_hosting/od23dza8.png)  

于是做完了。  

因此我们本质上就是在判断这棵树是不是个 [毛毛虫](https://www.luogu.com.cn/problem/P3174)，然后把中心链提出来。

```cpp
const int N=200020;
struct Edge{int p,next;}edge[N<<1];
int n,head[N],cnt=0,cmt=0,h[N],vis[N],s1,s2,s3,s4;
vector<int>ans,g[N];
void add(int u,int v){
	cnt++;
	edge[cnt]=(Edge){v,head[u]};	
	head[u]=cnt;	
}
void dfs(int cur,int fa,int dep,int ti){
	if(ti==0) if(dep>s1) s1=dep,s2=cur;
	if(ti==1) if(dep>s1) s1=dep,s3=cur;
	for(int i=head[cur];i;i=edge[i].next)
		if(edge[i].p!=fa) dfs(edge[i].p,cur,dep+1,ti);
}
void dfs2(int cur,int fa,int t){
	if(cur==t) s4=1;
	for(int i=head[cur];i;i=edge[i].next)
		if(edge[i].p!=fa and !s4) dfs2(edge[i].p,cur,t);
	if(s4){
		cmt++,vis[cur]=2,h[cmt]=cur;
		return;
	}
}
signed main(){
	read(n);
	for(int i=1;i<n;i++) read(s1),read(s2),add(s1,s2),add(s2,s1);
	s1=0,dfs(1,0,0,0);
	s1=0,dfs(s2,0,0,1);
	s4=0,dfs2(s3,0,s2);
	for(int i=1;i<=cmt;i++){
		for(int j=head[h[i]];j;j=edge[j].next)
			if(vis[edge[j].p]!=2) g[i].push_back(edge[j].p),vis[edge[j].p]=1;	
	}
	s4=0;
	for(int i=1;i<=n;i++) if(vis[i]==0) s4=1;
	if(s4){cout<<"No\n";return 0;}
	cout<<"Yes\n";
	for(int i=1;i<=cmt;i++){
		if(i%2==1) ans.push_back(h[i]);	
		else for(int j=0;j<g[i].size();j++) ans.push_back(g[i][j]);	
	}
	for(int i=cmt-(cmt%2);i>=2;i--){
		if(i%2==0) ans.push_back(h[i]);	
		else for(int j=0;j<g[i].size();j++) ans.push_back(g[i][j]);	
	}
	for(int i=0;i<ans.size();i++) cout<<ans[i]<<' ';cout<<"\n";
	return 0;
}
```

---

## 作者：Jeefy (赞：2)


这种方法是 VP 的时候想出来的，分讨比较严重：

先考虑状态 $f_{x, 0/1}$ 表示走完其子树后是否可以在其子节点或者本身上。

发现叶子节点对于其可行性没有影响，考虑非叶节点的影响。

不难分类讨论，设当且节点为 $x$：

- 如果没有非叶节点，那么不难发现最后无论在哪里都可以。![](https://gitlab.com/jeefies/image-repo/uploads/23e67864c46091024d841de979bba71d/202309112135715.png)

- 如果只有一个非叶节点 $y$，那么发现 $f_{x, 0}$ 满足当且仅当 $f_{y, 1}$ 满足，同理，$f_{x, 1}$ 满足当 $f_{y, 1}$ 满足。![](https://gitlab.com/jeefies/image-repo/uploads/108be89cfa595934ef4d3999cfa353e2/202309112135559.png)

- 如果有两个非叶节点，发现除非这个点是根，或者父节点为根且根没有其他子树，否则绝对无法满足。而如果满足上述条件，那么最开始无论是从 $x$ 出发，还是最终到达 $x$ 本质相同。![](https://gitlab.com/jeefies/image-repo/uploads/b40099392bf16c1815113660b490276f/202309112135139.png)

所以我们可以愉快的 DP 了，但是考虑父节点为根且根没有其他子树的情况不太好判断，所以任意找一个度数 $\ge 2$ 的点作为根，那么自然这个条件就无法满足，如果没有找到……这还是能一颗树？

```cpp
int rt = 1;
void dfs(int x, int p) {
	dep[x] = dep[p] + 1;
	
	int son = 0;
	vector<int> nonleaf; 
	for (int y : G[x]) {
		if (y == p) continue;
		++son;
		dfs(y, x);
		if (!leaf[y]) nonleaf.push_back(y);
	}
	
	if (son == 0)
		leaf[x] = 1, f[x][1] = 1;
	else if (nonleaf.size() == 0) 
		f[x][0] = f[x][1] = 1;
	else if (nonleaf.size() == 1) {
		int y = nonleaf[0];
		f[x][0] = f[y][1], f[x][1] = f[y][0];
	} else if (x == rt && nonleaf.size() == 2) {
		int y = nonleaf[0], z = nonleaf[1];
		if ((f[y][0] && f[z][1]) || (f[y][1] && f[z][0])) f[x][1] = true;
	}
}
```

这样，从根开始，依据 DP 转移的过程构造即可。

```cpp
vector<int> v;
void construct(int x, int t, int p) {
	vector<int> nonleaf;
	for (int y : G[x]) {
		if (y != p && !leaf[y]) nonleaf.push_back(y);
	}
	
	#define pushLeaf() { for (int u : G[x]) if (u != p && leaf[u]) v.push_back(u); }
	if (nonleaf.size() == 0) {
		if (t == 0) v.push_back(x);
		for (int y : G[x]) {
			if (y != p) v.push_back(y);
		} if (t == 1) v.push_back(x);
	} else if (nonleaf.size() == 1) {
		int y = nonleaf[0];
		if (t == 0) {
			v.push_back(x);
			construct(y, 1, x);
			pushLeaf();
		} else {
			pushLeaf(); 
			construct(y, 0, x);
			v.push_back(x);
		}
	} else if (nonleaf.size() == 2) {
		int y = nonleaf[0], z = nonleaf[1];
		v.push_back(x);
		if (f[y][1] && f[z][0]) {
			construct(y, 1, x);
			pushLeaf();
			construct(z, 0, x);
		} else if (f[y][0] && f[z][1]) {
			construct(z, 1, x);
			pushLeaf();
			construct(y, 0, x);
		} else assert(nonleaf.size() == 2);
	}
}
```

虽然是说稍微复杂了一点，但是分讨很简单，代码依据分讨就可以直接模拟出来，十分的 `naive`，这比正解要更 `brute force` 一点（CF优良传统）。

CF 提交：<https://codeforces.com/contest/1819/submission/222844150>

---

## 作者：plank_black (赞：2)

&emsp;&emsp;审核大大幸苦了~~

# 思路
&emsp;&emsp;构造题当然要先模拟几组小样例看一下规律。

&emsp;&emsp;玩了几组后我们发现其实合法的情况挺少的，比如下面这一组就是合法的方案：

![](https://cdn.luogu.com.cn/upload/image_hosting/iosgorpk.png)

&emsp;&emsp;下面这种就不行：

![](https://cdn.luogu.com.cn/upload/image_hosting/58lwocr9.png)

&emsp;&emsp;大家可以再自己随便造一些数据试试（也不能太随便），最后可以发现其实只有第一个图这种情况符合条件，也就是只有当能在这颗树中找到一条链，使得删去这条链剩下的所有子树都只有一个点时才有解。

&emsp;&emsp;要证明其实也不难，我们参考下图进行证明，箭头表示所指方向还有若干点，且有一种方案可以将这些点跳完。

![](https://cdn.luogu.com.cn/upload/image_hosting/xxtwnkdc.png)

&emsp;&emsp;假定我们从左边跳来，当我们跳到了这个子图上时，有第一个点两种情况，在 $A$ 点和在 $B$ 点上，进行一个分类讨论。

---

&emsp;&emsp;初始在 $A$ 点上。
- 若刚开始不跳到支链上，那么回来时就必须先跳到 $B$ 上再跳完支链再返回，但实际上想要跳完支链就必须经过一个先 $E$ 再 $D$ 的过程或者是先 $D$ 再 $E$ 的过程，但无论哪种都是无法跳到 $A$ 的左边，所以这个方案不行。

- 第一次跳到 $D$ 点，然后向 $C$ 点右跳，回来时先到 $B$ 点，再把 $E$ 点和下面的点跳完，这时候 $B,D,E$ 已经把路堵死了，所以这个方案不行。

- 第一次就把支链跳完，必然先 $D$ 再 $E$，然后再跳到 $B$ 上，再向右跳，可以发现回来的路已经堵死了，所以这个方案不行。

---

&emsp;&emsp;初始在 $B$ 上。

- 若刚开始不跳到支链上，那么回来时就必须由 $C$ 点到 $D$ 点上，然后跳完 $E$ 下面的点之后再回到 $E$ 就发现跳不动了，所以这个方案不行。

- 若刚开始跳一个 $D$，再到 $C$，会发现回来的路已经堵死了，所以这个方案不行。

- 若刚开始完支链，那么必然会先到先跳到 $E$ 点，然后再回到 $D$ 点，再到 $C$ 点，然后你发现回来的路又堵死了，所以这个方案也不行。

---

&emsp;&emsp;有点啰嗦的证明就这样写完了（

&emsp;&emsp;然后我们就只需要判断这颗树中是否有一条链使得去掉它之后剩下的子树都是单个节点。

&emsp;&emsp;这里还有一个结论，就是我们要找的这条链就是当前树的最长链。如果这条链与最长链不一样，那么用最长链替换这条链肯定会更优，这在当前链与最长链有重合与没有重合的情况下都是可证明的。证明比较简单这里就省去了。

&emsp;&emsp;现在就已知了主链，以及挂在主链上的只能是一个个单独的点，然后就只用构造一种方案输出就行。方案就是从最长链一个端点开始向另一个端点走，偶数步就输出当前链上的这个点，奇数步就输出所有连在这个点上的非主链上的点。然后倒着输出一遍差不多的操作。

&emsp;&emsp;于是我们就只需要愉快地 DFS 就可以 A 掉这道题了（

## 代码

&emsp;&emsp;为了让代码思路更清晰，我把代码细分成了 $7$ 个 DFS（

```cpp
#include<iostream>
#include<cstring>
using namespace std;

const int N = 2e5 + 10;
int n, p1, p2, Max;
int head[N], to[N * 2], Next[N * 2], Index;
int size[N], dep[N];
bool in[N], flag = true;

void add(int a, int b);
void dfs1(int u, int p);
void dfs2(int u, int p);
void dfs3(int u, int p);
void dfs4(int u, int p);
void dfs5(int u, int p);
void output1(int u, int p);
void output2(int u, int p);

int main( ) {
	memset(head, -1, sizeof head); 
	
	cin >> n;
	for(int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		add(a, b), add(b, a);
	}
	
	dfs1(1, 0);
	
	Max = 0;
	dfs2(p1, 0);
	
	in[p2] = true;
	dfs3(p1, 0);
	
	memset(dep, 0, sizeof dep);
	dfs4(p1, 0);
	
	dfs5(p1, 0);
	
	if(flag) {
		cout << "Yes" << endl;
		output1(p1, 0);
		output2(p1, 0);
	}
	else cout << "No" << endl;
	return 0;
}

void add(int a, int b) {
	to[Index] = b;
	Next[Index] = head[a], head[a] = Index++;
}

void dfs1(int u, int p) { // dfs1 和 dfs2 都是用来找最长链的
	dep[u] = dep[p] + 1;
	if(Max < dep[u]) {
		Max = dep[u];
		p1 = u;
	}
	
	for(int i = head[u]; ~i; i = Next[i]) {
		int j = to[i];
		if(j != p) dfs1(j, u);
	}
}

void dfs2(int u, int p) {
	dep[u] = dep[p] + 1;
	if(Max < dep[u]) {
		Max = dep[u];
		p2 = u;
	}
	
	for(int i = head[u]; ~i; i = Next[i]) {
		int j = to[i];
		if(j != p) dfs2(j, u);
	}
}

void dfs3(int u, int p) { // 记录主链
	for(int i = head[u]; ~i; i = Next[i]) {
		int j = to[i];
		if(j != p) {
			dfs3(j, u);
			in[u] |= in[j];
		}
	}
}

void dfs4(int u, int p) { // 初始化 size 和深度
	size[u] = 1;
	dep[u] = dep[p] + 1;
	for(int i = head[u]; ~i; i = Next[i]) {
		int j = to[i];
		if(j != p) {
			dfs4(j, u);
			size[u] += size[p];
		}
	}
}

void dfs5(int u, int p) { // 判断是不是挂在主链上的都是单个点，用flag记录
	for(int i = head[u]; ~i; i = Next[i]) {
		int j = to[i];
		if(j != p) {
			dfs5(j, u);
			if(size[j] >= 2 && !in[j]) flag = false;
		}
	}
}

void output1(int u, int p) { //正着输
	if(dep[u] % 2) {
		for(int t = head[u]; ~t; t = Next[t]) 
			if(!in[to[t]]) cout << to[t] << ' ';
	} else cout << u << ' ';
	
	for(int i = head[u]; ~i; i = Next[i]) {
		int j = to[i];
		if(j != p && in[j]) output1(j, u);
	}
}

void output2(int u, int p) { // 倒着输
	for(int i = head[u]; ~i; i = Next[i]) {
		int j = to[i];
		if(j != p && in[j]) output2(j, u);
	}
	
	if(dep[u] % 2 == 0) {
		for(int t = head[u]; ~t; t = Next[t]) 
			if(!in[to[t]]) cout << to[t] << ' ';
	} else cout << u << ' ';
}
```


---

## 作者：Alex_Wei (赞：2)

### [CF1819C The Fox and the Complete Tree Traversal](https://www.luogu.com.cn/problem/CF1819C)

先把 $n = 2$ 的平凡情况特判掉，否则选一个非叶子作为根。

对点 $i$，考虑环在 $i$ 子树内的部分，发现必然是一段，因为进去再出来再进去再出来是不可能的。因此，设 $i$ 子树的插头为 $x, y$，其中必然有一个是 $i$，另一个是 $i$ 的儿子，设为 $f_i$。当 $i$ 为叶子时 $f$ 不存在。

合并 $i$ 的所有儿子时，若 $i$ 有两个儿子 $f_u$ 非空，因为 $f_u$ 只能跳到 $i$，所以当且仅当 $i$ 为根时合法：若 $i$ 非根，因为根不是叶子，所以则 $i$ 子树外必然有一个距离 $i$ 为 $2$ 的插头，这个插头只能跳到 $i$。

对于非叶子：

- 若所有儿子 $f$ 为空，则连接 $i$ 和任意儿子，并将剩下所有儿子串起来，令 $f_i$ 为最后一个儿子。
- 若存在一个儿子 $f$ 非空，则从该儿子开始将剩下所有儿子串起来，令 $f_i$ 为最后一个儿子。
- 若存在两个儿子 $f$ 非空，若非根则无解，否则从其中一个儿子开始，另一个儿子结束将所有儿子串起来。
- 若存在大于两个儿子 $f$ 非空，无解。
- 特别地，将所有 $f$ 非空的儿子的 $f$ 和 $i$ 直接相连。

最终得到以根为端点的链或一条环。从根开始在环上遍历即可。

细节较多。时间复杂度 $\mathcal{O}(n)$。

实际上，一棵树合法当且仅当它是毛毛虫，将度数为 $1$ 的点处理掉，剩下一条链，处理一下即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int mod = 1e9 + 7;
void add(int &x, int y) {
  x += y, x >= mod && (x -= mod);
}
int ksm(int a, int b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}

constexpr int N = 2e5 + 5;

int n, c[N];
vector<int> e[N], g[N];
void dfs(int id, int ff) {
  int t = 0, leaf = 1;
  vector<int> S;
  for(int it : e[id]) {
    if(it == ff) continue;
    S.push_back(it), dfs(it, id);
    leaf = 0, t += c[it] > 0;
  }
  if(leaf) return;
  if(t > 2 || t == 2 && ff) cout << "No\n", exit(0);
  sort(S.begin(), S.end(), [&](int x, int y) {return c[x] > c[y];});
  if(!ff && c[S[1]]) swap(S[1], S.back());
  int pre = 0;
  for(int it : S) {
    if(pre) {
      g[it].push_back(pre);
      g[pre].push_back(it);
    }
    else if(!t) {
      g[it].push_back(id);
      g[id].push_back(it);
    }
    pre = it;
    if(c[it]) {
      g[id].push_back(c[it]);
      g[c[it]].push_back(id);
    }
  }
  c[id] = pre;
}
void solve() {
  cin >> n;
  for(int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  if(n == 2) {
    cout << "Yes\n";
    cout << "1 2\n";
    exit(0);
  }
  for(int i = 1; i <= n; i++)
    if(e[i].size() > 1) {
      dfs(i, 0);
      cout << "Yes\n";
      int lst = 0, cur = i, rest = n;
      while(rest) {
        cout << cur << " ";
        int nxt = -1;
        for(int it : g[cur]) if(it != lst) nxt = it;
        if(nxt == -1) break;
        lst = cur, cur = nxt, rest--;
      }
      cout << "\n";
      exit(0);
    }
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  while(T--) solve();
  return 0;
}
```

---

## 作者：ttq012 (赞：1)

### 前言

[柠檬姐姐](https://www.luogu.com.cn/user/610335) 在语文课课前三分钟演讲讲的神题/bx，一定要补完！

### 题解

先考虑一个很 simple 的情况，即树退化成了一条链的形式。

对链按照下表奇偶染色，尽量跳 $2$ 的长度，如果 $n\bmod 2=1$ 那么特殊判断一下，第一步跳 $1$ 的长度即可。

然后考虑本题。

Lemma $1$：一棵树可以被这样染色，当且仅当这棵树是一个毛毛虫树。

如果图不是毛毛虫树，那么就至少存在一条长度为 $2$ 的非直径链挂在直径的中间。

容易证明如果选择从距离直径远的点跳到距离直径近的点，那么直径就必然存在连续的两个点被染色，回去的时候就会不存在这样长度的点。反过来，就无法从直径远的点跳回到直径上的点。画图即可发现。

问题就是怎么在毛毛虫树构造一组合法的方案。

从树上任意一条直径的任意一个端点开始执行程序，优先走距离为 $2$ 的树上没有被走过的直径距离 $1$ 的节点的叶子节点，其次走树的直径上距离为 $2$ 的点，最后再走剩下距离的点回来即可。

时间复杂度是 $O(n)$ 的。

描述很不优美，建议参考代码。

### 代码

```cpp
// lemon sister shines, thanks lemon sister!
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2e5 + 10;
int n;
vector<int> z[N], res;
bool vis[N];
int dis[N];

bool cap() {
    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        for (auto &j : z[i]) {
            if (z[j].size() != 1) {
                cnt++;
            }
        }
        if (cnt > 2) {
            return false;
        }
    }
    return true;
}

void bfs() {
    queue<int> q;
    q.push(1);
    vis[1] = false;
    memset(dis, 0x3f, sizeof dis);
    dis[1] = 0;
    while (q.size()) {
        int f = q.front();
        q.pop();
        vis[f] = false;
        for (auto &g : z[f]) {
            if (dis[g] > dis[f] + 1) {
                dis[g] = dis[f] + 1;
                if (!vis[g]) {
                    vis[g] = true;
                    q.push(g);
                }
            }
        }
    }
}

void dfs(int u, int fa) {
    vector<int> foot;
    for (auto &v : z[u]) {
        if (v != fa) {
            if (z[v].size() > 1) {
                // 直径上的节点
                for (auto &w : z[v]) {
                    if (w != u) {
                        if (z[w].size() == 1) {
                            res.push_back(w);
                        }
                    }
                }
                for (auto &w : z[v]) {
                    if (w != u) {
                        if (z[w].size() > 1) {
                            res.push_back(w);
                            dfs(w, v);
                        }
                    }
                }
                res.push_back(v);
            } else {
                // 毛毛虫脚上的节点
                foot.push_back(v);
            }
        }
    }
    for (auto &x : foot) {
        res.push_back(x);
    }
}

signed main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        z[x].push_back(y);
        z[y].push_back(x);
    }
    if (cap()) {
        cout << "Yes\n";
        bfs();
        int best = max_element(dis + 1, dis + n + 1) - dis;
        res.push_back(best);
        // best 是毛毛虫直径的一端点
        dfs(best, 0);
        for (auto &x : res) {
            cout << x << ' ';
        }
        cout << '\n';
    } else {
        cout << "No\n";
    }
}

```

### 总结

在语文课上讲 OI 的柠檬姐姐好闪，拜谢柠檬姐姐！


---

## 作者：Hoks (赞：0)

## 前言
祭鸽了两个月的题目。

重新看自己整个错完的思路居然一下就秒了，挺神奇的。

看了眼题解感觉都不太能看懂写法？

那就补一篇好了喵。

摘自[交互、构造、博弈](https://www.luogu.com.cn/training/676672)。
## 思路分析
先考虑来判断 `No` 的情况。

我们假设选定了一个点 $x$ 为根。

如果 $x$ 有多个分支挂的是叶子结点，那我们发现可以绕着叶子跳一圈。

然后来考虑挂出来的分支是非叶子的情况。

此时显然的是，因为最后走完之后要回来，所以第一步必然要走距离为 $2$ 的，因为这样才能空出一个最后回来的位置。

那么我们考虑设这个点是 $y$，在走完 $y$ 子树假设可以走回来的话，最后会停在 $y$ 点上。

此时如果结束那么就是可行的。

但倘若 $x$ 还有一个非叶子分支 $y'$，因为 $y'$ 和 $y$ 是等价的，所以走进他们的子树里时必然不能经过 $y'$ 或者是 $y$（这样才能走回来嘛）。

但我们知道的是 $\text{Dist}(y,y')=2$，在走完 $y$ 的子树回到 $y$ 后，我们最远只能一步跨到 $y'$，所以在走 $y'$ 子树回来时与根节点 $x$ 的距离最小只能为 $2$。

这就意味着要是根节点再挂出去一个非叶子分支 $w$，走完 $y'$ 子树回来后就够不到了。

也就是无解。

那这样操作是不是就是最优了呢？

不难发现是这样的，三叉的情况不然不可能存在。

可以考虑手玩一下从 $y$ 开始情况。

此时走完 $y$ 的子树回来必然要经过点 $x$。

然后走 $y'$ 子树回来最多也只能停在 $y'$ 点上。

所以再走到子树 $w$ 里就要经过点 $w$，而 $\text{Dist}(w,y)=2$，所以我们回来的时候的距离一定会超过 $2$。

也就是不符合题目条件。

经过上述论述我们得出了一个结论：
- 对于任意一个点 $x$，如果他存在三个非叶子分支，那么必然无解。

接着我们来考虑有解的时候怎么构造方案。

不能存在大于等于三个非叶子分支还是太抽象了，尝试具象化。

其实一条链的时候就是两个非叶子分支嘛。

所以说有解的情况就是**一条链上挂了若干个叶子**上去。

这种如何构造呢？

其实还是比较容易的，我们考虑先把主链（也就是直径）抽出来。

那么树大概会长成这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/94ccwg8v.png)

我们不妨考虑从 $1$ 开始走。

那么不考虑叶子的时候我们的走法就是：$1\rightarrow3\rightarrow5\rightarrow7\rightarrow6\rightarrow4\rightarrow2$。

然后我们考虑把叶子加上去。

因为有步长的限制，所以在 $1\rightarrow3$ 时，我们要去走 $2$ 所拥有的叶子，也就是 $1\rightarrow8\rightarrow3$ 这样。

在这样的策略下，叶子被巧妙插入了刚刚的遍历顺序之中且符合题目要求。

然后是 $1,3,5,7,\dots$ 上面挂的叶子。

考虑在后面 $6\rightarrow4\rightarrow2$ 回来的时候类似的遍历就可以了。

注意判断下链长为偶数的情况，掉头的时候要多判一下。
## 代码
感觉挺好写的，应该也挺好懂的。

```cpp
#include <bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=2e6+10,V=60,M=1e3+10,mod=998244353,INF=1e18,lim=19,p=13331;
int n,m,k,mx,x,y,mp[N];char s[N],t[N];vector<int>e[N],a;
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(long long x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c=='?'||c=='@'||c=='#'||c=='.'||c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='+'||c=='-'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline void dfs(int u,int ff,int d,int&p,int&mx)
{
	if(d>mx) mx=d,p=u;
	for(auto v:e[u]) if(v!=ff)
		dfs(v,u,d+1,p,mx);
}
inline void dfs1(int u,int ff,int ed)
{
	for(auto v:e[u]) if(v!=ff)
	{
		if(v==ed) return a.emplace_back(v),a.emplace_back(u),void();
		dfs1(v,u,ed);if(a.size()) return a.emplace_back(u),void();
	}
}
inline void solve()
{
	n=read();for(int i=1,u,v;i<n;i++) u=read(),v=read(),e[u].emplace_back(v),e[v].emplace_back(u);
	if(n==2) return put("Yes\n1 2\n");
	for(int i=1;i<=n;i++)
	{
		int cnt=0;
		for(auto v:e[i]) cnt+=(e[v].size()!=1);
		if(cnt>2) return put("No\n");
	}put("Yes\n");dfs(1,0,0,x,mx);mx=0;dfs(x,0,0,y,mx);//找直径
	dfs1(x,0,y);for(auto x:a) mp[x]=1;//标记主链
	for(int i=0;i<a.size();i+=2)//从直径一头开始走到另一头
	{
		print(a[i]);put(' ');
		if(i==a.size()-1) break;
		for(auto v:e[a[i+1]]) if(!mp[v])//遍历中间跳过点的叶子
			print(v),put(' ');
	}if(a.size()%2==0)//注意偶数的时候的特判
	{
		print(a.back()),put(' ');
		for(auto v:e[a[a.size()-2]]) if(!mp[v])
			print(v),put(' ');
	}
	for(int i=a.size()-2-(a.size()%2==0);i>=0;i-=2)//走回来，起始点要特判一下
	{
		print(a[i]);put(' ');if(!i) break;
		for(auto v:e[a[i-1]]) if(!mp[v])//类似上文
			print(v),put(' ');
	}
}
signed main()
{
	int T=1;
	// T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}
```

---

## 作者：Leasier (赞：0)

手玩样例可以得出一个简单的结论：

- 若有一个点 $u$，使得以其为根时非叶子的儿子数量 $\geq 3$，则无解。

证明：

- 我们只能至多一次从某个子树跳到 $u$，也只能至多一次从 $u$ 跳到某个子树，其他时候只能从一个儿子跳到另一个儿子。
- 当非叶子的儿子数量 $\geq 3$，有 $\geq 2$ 的儿子需要从其内部跳到 $u$，不符合条件。

于是去掉叶子后，树变为一条**链**。或者说得更直白一点，原树为一棵**毛毛虫**。

首先特判 $n = 2$。对于 $n > 2$，若有解，抓出那条链，分链长奇偶构造即可。

时间复杂度为 $O(n)$。

代码：
```cpp
#include <iostream>
#include <vector>

using namespace std;

typedef struct {
	int nxt;
	int end;
} Edge;

int cnt = 0;
int u[200007], v[200007], deg[200007], head[200007], chain[200007];
bool vis1[200007], vis2[200007];
Edge edge[400007];
vector<int> vec[200007];

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

int main(){
	int n;
	cin >> n;
	if (n == 2){
		cout << "Yes" << endl;
		cout << 1 << " " << 2;
		return 0;
	}
	int pos = 0;
	for (int i = 1; i < n; i++){
		cin >> u[i] >> v[i];
		deg[u[i]]++;
		deg[v[i]]++;
	}
	for (int i = 1; i < n; i++){
		if (deg[u[i]] == 1){
			vis1[i] = vis2[u[i]] = true;
			vec[v[i]].push_back(u[i]);
		} else if (deg[v[i]] == 1){
			vis1[i] = vis2[v[i]] = true;
			vec[u[i]].push_back(v[i]);
		} else {
			add_edge(u[i], v[i]);
			add_edge(v[i], u[i]);
		}
	}
	for (int i = 1; i < n; i++){
		if (vis1[i]){
			deg[u[i]]--;
			deg[v[i]]--;
		}
	}
	for (int i = 1; i <= n; i++){
		if (deg[i] > 2){
			cout << "No";
			return 0;
		}
		if (!vis2[i] && deg[i] <= 1) pos = i;
	}
	int cnt = 0;
	for (int i = 1; ; i++){
		bool flag = false;
		chain[++cnt] = pos;
		for (int j = head[pos]; j != 0; j = edge[j].nxt){
			int x = edge[j].end;
			if (x != chain[cnt - 1]){
				flag = true;
				pos = x;
				break;
			}
		}
		if (!flag) break;
	}
	cout << "Yes" << endl;
	if (cnt % 2 == 0){
		for (int i = 1; i < cnt; i += 2){
			int size = vec[chain[i + 1]].size();
			cout << chain[i] << " ";
			for (int j = 0; j < size; j++){
				cout << vec[chain[i + 1]][j] << " ";
			}
		}
		for (int i = cnt; i >= 2; i -= 2){
			int size = vec[chain[i - 1]].size();
			cout << chain[i] << " ";
			for (int j = 0; j < size; j++){
				cout << vec[chain[i - 1]][j] << " ";
			}
		}
	} else {
		int size;
		for (int i = 1; i <= cnt; i += 2){
			size = vec[chain[i + 1]].size();
			cout << chain[i] << " ";
			for (int j = 0; j < size; j++){
				cout << vec[chain[i + 1]][j] << " ";
			}
		}
		for (int i = cnt - 1; i >= 2; i -= 2){
			size = vec[chain[i + 1]].size();
			for (int j = 0; j < size; j++){
				cout << vec[chain[i + 1]][j] << " ";
			}
			cout << chain[i] << " ";
		}
		size = vec[chain[1]].size();
		for (int i = 0; i < size; i++){
			cout << vec[chain[1]][i] << " ";
		}
	}
	return 0;
}
```

---

## 作者：Nuisdete (赞：0)

手玩几个例子，发现普通的树都是无解的，而有解的树似乎都有着某种特殊的性质。

直接说结论了，可以自己感受一下，有解的树一定是一条链上面挂着一些叶子，其它情况都是无解的，因为会发现跳到岔路口里就跳不回去父亲了。

当然，在给出的树中，我们链肯定是选直径，这样显然最优。

然后 check 一下是否合法，构造的话就是先往下两个两个跳，跳的过程中把没跳到的点的叶子跳一下，回来也是两个两个往上跳，跳的过程中把往下跳的时候跳到的点的叶子跳一下，然后就完事了。

注意直径长为偶数和直径长为奇数的构造方式有一点点不同。

Code：[https://codeforces.com/problemset/submission/1819/202678434](https://codeforces.com/problemset/submission/1819/202678434)。

---

## 作者：AlicX (赞：0)

很好的一道构造题和找规律题。

从链开始分析，你会发现每一条链都可以通过一些方法得到答案，然后你尝试加入几个点，发现只要遇到有分叉地方，就先走分叉点。继续手玩可以发现，只有层数为 $1$ 的点才会被记入答案，而之前的链就是树的直径，然后思路也就出来了。

本题最大的特点是难写。记录树的直径时，可以试着用打标记的方法，最后再多跑一遍 `bfs` 求路径。判断无解时，可以把直径上的点的周围一圈的点都打上标记，最后判断是否有点没有标记即可。至于记录答案，先正着跑一遍，每次跳两步，遇到分叉就走分叉就可以了，然后倒着跑一遍，注意判重。

然后就是不知道为什么，本题需使用 C++20，不然就会 RE，不知道是我写得太丑了还是我降智了。

```cpp
#include<bits/stdc++.h> 
#define pb(x) push_back(x) 
using namespace std;
const int N=2e5+10; 
int n,m; 
int d[N]; 
int Max=0; 
int h[N],idx=0; 
vector<int> rd; 
vector<int> ans; 
bool sp[N],ps[N];
bool st[N],vis[N]; 
struct Node{ 
	int to,ne; 
}tr[N<<1]; 
void add(int u,int v){ 
	tr[idx].to=v,tr[idx].ne=h[u],h[u]=idx++; 
} 
void dfs1(int u,int fa){ 
	for(int i=h[u];i!=-1;i=tr[i].ne){ 
		int to=tr[i].to; 
		if(to==fa) continue; 
		d[to]=max(d[to],d[u]+1); dfs1(to,u); 
	} 
} 
void dfs2(int u,int fa){ 
	for(int i=h[u];i!=-1;i=tr[i].ne){ 
		int to=tr[i].to; 
		if(to==fa) continue; 
		if(d[to]<d[u]+1) d[to]=d[u]+1; dfs2(to,u); 
	} 
} 
void dfs3(int u,int fa){ 
	for(int i=h[u];i!=-1;i=tr[i].ne){
		int to=tr[i].to; 
		if(to==fa) continue; 
		dfs3(to,u); sp[u]|=sp[to];  
	}
} 
int main(){ 
	memset(h,-1,sizeof h); 
	cin>>n; 
	for(int i=1;i<n;i++){ 
		int u,v; cin>>u>>v; 
		add(u,v),add(v,u); 
	} dfs1(1,0); int Max=0,id=0; 
	for(int i=1;i<=n;i++) if(Max<d[i]) Max=d[i],id=i; 
	memset(d,0,sizeof d); 
	dfs2(id,0); int Max1=0,id1=0; 
	for(int i=1;i<=n;i++) if(Max1<d[i]) Max1=d[i],id1=i; 
	sp[id1]=true; dfs3(id,0); queue<int> q; q.push(id1); 
	while(!q.empty()){
		int u=q.front(); q.pop(); 
		if(ps[u]) continue; ps[u]=true; rd.pb(u); 
		for(int i=h[u];i!=-1;i=tr[i].ne){
			int to=tr[i].to; 
			if(sp[to]) q.push(to); 
		} 
	} for(int i=0;i<rd.size();i++){ 
		int u=rd[i]; st[u]=vis[u]=true; 
		for(int j=h[u];j!=-1;j=tr[j].ne) vis[tr[j].to]=true; 
	} for(int i=1;i<=n;i++){ if(!vis[i]){ puts("No"); return 0; } } 
	puts("Yes"); memset(vis,false,sizeof vis); 
	for(int i=0;i<rd.size();i+=2){ 
		int u=rd[i],v=rd[i+1]; vis[u]=true; ans.pb(u); 
		for(int j=h[v];j!=-1;j=tr[j].ne){ 
			int to=tr[j].to; if(st[to]) continue; 
			ans.pb(to),vis[to]=true; 
		} 
	} int now=rd.size()-1; if(vis[rd[now]]) now--; 
	for(int i=now;i>=1;i-=2){ 
		int u=rd[i],v=rd[i-1]; if(!vis[u]) ans.pb(u),vis[u]=true; 
		for(int j=h[v];j!=-1;j=tr[j].ne){ 
			int to=tr[j].to; if(st[to]) continue; 
			if(!vis[to]) ans.pb(to),vis[to]=true; 
		} 
	} for(int i=0;i<ans.size();i++) printf("%d ",ans[i]); puts(""); 
	return 0;
} /* */ 
```



---

