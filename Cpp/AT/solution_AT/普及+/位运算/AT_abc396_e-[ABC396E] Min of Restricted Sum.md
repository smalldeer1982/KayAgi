# [ABC396E] Min of Restricted Sum

## 题目描述

给定整数 $N, M$ 和长度为 $M$ 的整数序列 $X=(X_1,X_2,\ldots,X_M)$、$Y=(Y_1,Y_2,\ldots,Y_M)$、$Z=(Z_1,Z_2,\ldots,Z_M)$。其中，保证 $X$ 和 $Y$ 的所有元素均在 $1$ 至 $N$ 的范围内。

定义长度为 $N$ 的非负整数序列 $A=(A_1,A_2,\ldots,A_N)$ 为 **好的整数序列**，当且仅当满足以下条件：
- 对于所有满足 $1 \leq i \leq M$ 的整数 $i$，有 $A_{X_i} \oplus A_{Y_i} = Z_i$，其中 $\oplus$ 表示异或运算。

请判断是否存在这样的好的整数序列。若存在，请找出使得元素总和 $\displaystyle \sum_{i=1}^N A_i$ 最小的好的整数序列，并输出该序列。

关于异或（XOR）的定义：  
对于非负整数 $A$ 和 $B$，它们的异或 $A \oplus B$ 定义如下：
- $A \oplus B$ 的二进制表示中，$2^k$ 位（$k \geq 0$）的值为 $1$，当且仅当 $A$ 和 $B$ 在 $2^k$ 位上的值不同；否则为 $0$。

例如，$3 \oplus 5 = 6$（二进制表示为 $011 \oplus 101 = 110$）。

## 说明/提示

### 约束条件

- $1 \leq N \leq 2 \times 10^5$
- $0 \leq M \leq 10^5$
- $1 \leq X_i, Y_i \leq N$
- $0 \leq Z_i \leq 10^9$
- 输入中的所有值均为整数

### 样例解释 1

序列 $A=(0, 3, 4)$ 满足 $A_1 \oplus A_2 = 3$ 和 $A_1 \oplus A_3 = 4$，因此是好的整数序列。其他可能的序列如 $A=(1, 2, 5)$ 或 $A=(7, 4, 3)$ 也满足条件，但总和最小的序列是 $A=(0, 3, 4)$。

### 样例解释 2

不存在满足条件的好的整数序列，因此输出 $-1$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3 2
1 3 4
1 2 3```

### 输出

```
0 3 4```

## 样例 #2

### 输入

```
3 3
1 3 4
1 2 3
2 3 5```

### 输出

```
-1```

## 样例 #3

### 输入

```
5 8
4 2 4
2 3 11
3 4 15
4 5 6
3 2 11
3 3 0
3 1 9
3 4 15```

### 输出

```
0 2 9 6 0```

# 题解

## 作者：gesong (赞：10)

题目传送门：[[ABC396E] Min of Restricted Sum](https://www.luogu.com.cn/problem/AT_abc396_e)。
# 思路

容易发现，异或操作在二进制下只影响自己这一位，不会影响到其他的位置，考虑对每一个限制拆位，我们可以将题目转化成 $30$ 个这样的问题。

> 给定一个 $n$ 个点 $m$ 条边权只为 $0,1$ 的边，对这个图赋点权满足点权只能为 $0,1$ 且每一条边的相邻节点的点权的异或和为边权的最小点权为 $1$ 的个数。

我们考虑解决这 $30$ 个问题。

对于一个连通块，我们这需要知道这里的其中一个点，我们就可以推出整个连通块的赋值，我们这需要随机找一个点然后赋值 $0,1$ 然后贪心取 $1$ 的个数最小的方案即可。

记得判断无解的情况。

# 代码

赛时写的，略丑，见谅。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n,m;
struct nord{
	#define pii pair<int,int>
	vector<pii >a[N];
	int vis[N],anss[N];
	vector<int>b;
	bool flag=0;
	void dfs(int u){
		if (vis[u]) return ;
		vis[u]=1;
		b.push_back(u);
		for (auto i:a[u]){
			int v=i.first,w=i.second;
			if (anss[v]==-1) anss[v]=(w^anss[u]);
			else if (anss[v]^anss[u]^w) flag=1;
			dfs(v);
		} 
	}
	inline void solve(){
		for (int i=1;i<=n;i++) if (!vis[i]){
			anss[i]=1;
			b.clear();
			flag=0;
			dfs(i);
			bool flag1=flag;
			int sum1=0;
			for (auto i:b) sum1+=anss[i],anss[i]=-1,vis[i]=0;
			anss[i]=0;
			b.clear();
			flag=0;
			dfs(i);
			bool flag2=flag;
			int sum2=0;
			for (auto i:b) sum2+=anss[i];
			if (flag1&&flag2){
				puts("-1");
				exit(0);
			}
			if (sum2<sum1) continue;
			else{
				for (auto i:b) vis[i]=0,anss[i]=-1;
				anss[i]=1;
				b.clear();
				flag=0;
				dfs(i);
			}
		}
	}
}t[31];
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
main(){
	n=read(),m=read();
	for (int i=0;i<=30;i++)
		for (int j=1;j<=n;j++) t[i].anss[j]=-1,t[i].vis[j]=0;
	while(m--){
		int u=read(),v=read(),w=read();
		if (u==v){
			if (w) return 0&puts("-1");
			continue;
		}
		for (int i=0;i<=30;i++)
			t[i].a[u].push_back({v,((w>>i)&1)}),
			t[i].a[v].push_back({u,((w>>i)&1)});
	}
	for (int i=0;i<=30;i++) t[i].solve();
	for (int i=1;i<=n;i++){
		int ans=0;
		for (int j=0;j<=30;j++) ans=(ans+t[j].anss[i]*(1ll<<j));
		cout <<ans<<" ";
	} 
    return 0;
}
```

---

## 作者：Inzaghi_Luo (赞：3)

先来考虑无解的情况。可以发现，如果把条件抽象到图上，即从 $x_i$ 到 $y_i$ 连一条边权为 $z_i$ 的边，那么会形成一些连通块，而每一个连通块是独立的。我们只需要每一个连通块里面随便选一个点，随便赋一个初值去把整个连通块遍历一遍，只要没有出现矛盾的情况就是合法的。现在考虑如何让 $a$ 数组的和最小。我们可以每一位分开考虑。记录每一个连通块每一个二进制位取值的个数，如果 $1$ 比 $0$ 多，那么只需要整个连通块这一位取反就好了。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
int x[MAXN], y[MAXN], z[MAXN];
int head[MAXN], CNT;
struct edge{
	int next, to, val;
}ed[MAXN << 1];
void add_edge(int u, int v, int w){
	ed[++CNT] = (edge){head[u], v, w};
	head[u] = CNT;
} 
int q[MAXN], l, r;
int vis[MAXN], num, val[MAXN], sz[MAXN];
int bits[MAXN][30], mor[MAXN];
void bfs(int num){
	while(l < r){
		int u = q[++l];
		sz[num]++;
		for(int i = head[u];i;i = ed[i].next){
			int v = ed[i].to;
			if(vis[v]){
//					printf("%d %d %d %d %d\n", u, v, val[u], val[v], ed[i].val);
				if((val[u] ^ ed[i].val) != val[v]){
					printf("-1");
					exit(0);
				}
				continue;
			}
			vis[v] = num;
			val[v] = val[u] ^ ed[i].val;
			q[++r] = v;
		}
	}
}
int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= m;i++){
		scanf("%d%d%d", &x[i], &y[i], &z[i]);
		add_edge(x[i], y[i], z[i]);
		add_edge(y[i], x[i], z[i]);
	}
	for(int i = 1;i <= n;i++){
		if(!vis[i]){
			num++;
			vis[i] = num;
			val[i] = 0;
			l = r = 0;
			q[++r] = i;
			bfs(num);
		}
	}
	for(int i = 1;i <= n;i++){
		for(int j = 0;j < 30;j++){
			bits[vis[i]][j] += (val[i] >> j) & 1;
		}
	}
	for(int i = 1;i <= num;i++){
		for(int j = 0;j < 30;j++){
			if(bits[i][j] > sz[i] - bits[i][j]){
				mor[i] ^= (1 << j);
			}
		}
	}
	for(int i = 1;i <= n;i++){
		printf("%d ", val[i] ^ mor[vis[i]]);
	}
	return 0;
}
```

---

## 作者：dingxiongyue (赞：2)

# 题解：AT_abc396_e [ABC396E] Min of Restricted Sum

## Description：
给定长度均为 $M$ 的序列 $X$，$Y$，$Z$，要求在最小化 $\sum _ {i = 1} ^ {N} A_i$ 的前提下构造一个长度为 $N$ 的数组 $A$，满足 $A_{X_i} \operatorname{xor} A_{Y_i} = Z_i$。

## Analysis：
考虑转化为**图论**。  

连接一条 $X_i$ 与 $Y_i$ 之间权值为 $Z_i$ 的无向边。钦定起点点权为 $0$ 遍历整张图。遍历过程中：

* 若一点已被遍历过，则判断两点点权异或值是否等于该边边权，若不相等，则说明该情况无解。  
* 若一点未被遍历过，则更新该点点权为该边权值与另一点点权的异或值。

最后枚举二进制位数，遍历所有点，统计所有点权在二进制下第 $k$ 位的 $1$ 的个数，根据 $1$ 的个数讨论该位是否填 $0$。

时间复杂度 $O(N + M + \log \max _ {i = 1} ^ {N} A_i)$。 

## Code:
[AC记录](https://www.luogu.com.cn/record/207662200)  
```cpp
#include <iostream>
#include <cstring>
#include <vector>
#define int long long
const int N = 2e5 + 10;
int n, m;
int a, b, c;
int ans[N];
int num[N];
int e[N], h[N], ne[N], w[N], idx;
bool vis[N];
std::vector<int> res;
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

inline void write(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

void add(int a, int b, int c) {
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u) {
	res.push_back(u); 
	for (int i = h[u]; ~i; i = ne[i]) {
		int j = e[i];
		if (vis[j]) {
			if ((num[j] ^ num[u]) != w[i]) {
				puts("-1");
				exit(0);
			}
			continue;
		}
		vis[j] = true;
		num[j] = w[i] ^ num[u];
		dfs(j);
	}
}

signed main() {
	memset(h, -1, sizeof h);
	n = read(), m = read();
	while(m--) {
		a = read(), b = read(), c = read();
		add(a, b, c), add(b, a, c);
	}
	for (int i = 1; i <= n; i++) {
		if (vis[i]) continue;
		vis[i] = true;
		num[i] = 0;
		res.clear();
		dfs(i);
		for (int k = 0; k <= 30; k++) {
			int cnt = 0;
			for (auto j : res) 
				if (num[j] & (1 << k)) cnt++;
			if (cnt < res.size() - cnt) {
				for (auto j : res) 
					if (num[j] & (1 << k)) 
						ans[j] |= (1 << k);
			} else {
				for (auto j : res) 
					if (!(num[j] & (1 << k))) 
						ans[j] |= (1 << k);
			}
		}
	}
	for (int i = 1; i <= n; i++) 
		write(ans[i]), putchar(' ');
	printf("\n");
	return 0;
}
```

---

## 作者：_zhangcx (赞：2)

# 题解：[E - Min of Restricted Sum](https://atcoder.jp/contests/abc396/tasks/abc396_e)

提供一个非常容易想的思路，~~但是赛时没调出来。~~

一个显然的操作就是把每个数二进制拆分一下，对于每个数位求出其对答案的贡献。

我们设一个数 $x$ 的第 $i$ 个二进制位为 $f_i(x)$（显然 $f_i(x) \in \{0,1\}$），只考虑所有数第 $i$ 个二进制位可以得到：对于所有的 $j \in [1,N]$ 满足 $f_i(A_{X_j}) \oplus f_i(A_{Y_j}) = f_i(Z_j)$。

我们根据以上分析建图，分两种情况：

1. 若 $f_i(Z_j) = 0$，则 $f_i(A_{X_j})$ 与 $f_i(A_{Y_j})$ 相同，所以只要使用并查集把 $X_j$ 和 $Y_j$ 合并到一联通块中；
2. 若 $f_i(Z_j) = 1$，则 $f_i(A_{X_j})$ 与 $f_i(A_{Y_j})$ 不同，**就把 $X_j$ 所在的联通块和 $Y_j$ 所在的联通块连边**（注意我是把联通块当成点建边的），代表它们所在的两个联通块在数值上不同。

在新建的图上染一下色，由于要使 $\sum_{j=1}^N A_j$ 最小化，即 $\sum_{j=1}^N f_i(A_j)$ 最小化，肯定是染尽量多的 $0$ 是较优的，所以就尝试染起始的联通块为 $0$ 或 $1$，找出较优的方案更新；而如果图中染色出现相邻两个联通块染的色是一样的话就说明无解。

实现细节：

* 由于新建的图不一定联通，记得要跑多遍 `dfs`（就因为这个没在赛时调出来）；
* 我们是用联通块缩成点建的边，但其实显然只要把并查集中每个联通块的根节点连边就行了，此外记得计算染 $0$ 的个数时要乘上联通块大小；
* 至于你问我联通块大小怎么求，我是在并查集中顺带计算的大小，此时不适合用路径压缩，所以就用的启发式合并优化并查集的时间复杂度；
* 记得每一个二进制位都要跑一遍染色，记得清空 `vector` 和数组!

我的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, m, x[N], y[N], z[N];

// 并查集封装版
struct dsu {
    int fa[N], siz[N], n;
    void init(int n) {for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1; }
    int find(int x) { return x == fa[x] ? x : find(fa[x]); }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (siz[x] > siz[y]) swap(x, y);
        siz[y] += siz[x], fa[x] = y;
    }
} same[35]; 
// 把边先存下来以便之后操作
vector<pair<int, int>> diff[36];
// 在图上跑染色
vector<int> G[N];
int col[N], res;
vector<int> sta; // 记录这一次有哪些点被染的色，如果不优需要把这些点染的色取反
void dfs(int u, int c, int j, int b) {
    col[u] = c; sta.push_back(u);
    if (c) res += same[j].siz[u];
    for (int v : G[u]) {
        if (col[v] == -1) dfs(v, !c, j, b);
        else if (col[v] == c) {
            cout << -1;
            exit(0);
        }
    }
}
int a[N];
int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> x[i] >> y[i] >> z[i];
    for (int j = 0; j <= 30; j++) same[j].init(n);
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= 30; j++) {
            int cur = z[i] >> j & 1;
            if (cur == 0) same[j].unite(x[i], y[i]);
            else diff[j].push_back({x[i], y[i]});
        }
    }
    for (int j = 0; j <= 30; j++) {
        memset(G, 0, sizeof(G));
        for (auto [u, v] : diff[j]) {
            u = same[j].find(u), v = same[j].find(v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        int ans = 0;
        memset(col, -1, sizeof(col));
        for (int i = 1; i <= n; i++) {
            if (same[j].fa[i] != i) continue;
            if (col[i] == -1) {
                sta.clear();
                res = 0, dfs(i, 0, j, i);
                int siz = 0;
                for (int i : sta) siz += same[j].siz[i];
                if (res < siz - res) { // i染0更优
                    ans += res;
                } else { // i染1更优
                    for (int x : sta) col[x] = !col[x];
                    ans += siz - res;
                }
            }
        }
        for (int i = 1; i <= n; i++)
            a[i] += col[same[j].find(i)] << j; // 统计答案
    }
    for (int i = 1; i <= n; i++)
        cout << a[i] << " \n"[i == n];
    return 0;
}
```

由于是赛时代码改过的，实现免不了有些难看，常数也有点大。我尽量改的通俗易懂一些，如果还有不懂的可以找我解答。

---

## 作者：littlebug (赞：2)

## Solution

这种题做多了，就能一眼发现是个图论题。

那么建图 $x_i \xleftrightarrow {z_i} y_i$，其中 $z_i$ 表示 $x_i$ 和 $y_i$ 上填的数需要构成的的异或和。

考虑确定一个源点 $u$，然后从点 $u$ 开始 bfs 算出每个点需要和 $u$ 异或的数 $b_i$，顺便可以判当一个点对应两个值的时候就无解。然后把每个 $b_i$ 按照二进制位拆开，每个位统计一下 $0$ 和 $1$ 的个数，于是贪心地，考虑异或的性质，如果一个位上 $1$ 多就在 $u$ 上填 $1$，反之亦然，设这样得到的数为 $x$，答案 $a_i$ 就为 $x \oplus b_i$。

注意判图不连通，也不知道谁因为这个次了一发罚时，且被硬控 10min+。

## Code

```cpp
int n,m,a[MAXN],c[100];
vector <pii> p[MAXN];
bitset <MAXN> vis;
vector <int> scc;

il bool bfs(int s)
{
    queue <int> q;
    q.emplace(s),vis[s]=1,scc.pb(s);

    int u;
    while(!q.empty())
    {
        u=q.front(),q.pop();
        for(auto [v,w]:p[u])
        {
            if(!vis[v]) a[v]=a[u]^w,vis[v]=1,scc.pb(v),q.emplace(v);
            else if(a[v]!=(a[u]^w)) return 0;
        }
    }

    return 1;
}

signed main()
{
    read(n,m);
    {
        int u,v,w;
        rep(i,1,m) read(u,v,w),p[u].pb(v,w),p[v].pb(u,w);
    }

	rep(s,1,n) if(!vis[s])
	{
		clr(scc);
		rep(i,0,60) c[i]=0;
		
	    if(!bfs(s)) return cout<<-1,0;
	
	    int n2=scc.size();
	    for(auto i:scc) rep(j,0,60) a[i]>>j&1 && (++c[j]);
	    
	    int qwq=0;
	    rep(i,0,60) qwq|=(c[i]>n2-c[i])*1ll<<i;
	    for(auto i:scc) a[i]^=qwq;
	}
    
    _::w(a,n);

    return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：wuzebang2009 (赞：2)

[AT_abc396_e [ABC396E] Min of Restricted Sum](https://www.luogu.com.cn/problem/AT_abc396_e)

我们在点 $A_{X_i}$ 和 $A_{Y_i}$ 建一条边权为 $Z_i$ 的边，$A_{Y_i}=A_{X_i} \oplus Z_i $，我们知道在一个联通块中确定一个点的值所有点的值都是确定的，那么如果其中有冲突，那么就直接输出 `-1`，否则我们知道变动联通块的第一个值在二进制下某一为的值，所有的的其他在联通快中的值都会翻转，那么如果这一位为 $1$ 的点超过半数那么可以翻转，这样可以使最终值最小。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m,ans[N];
int h[N],nxt[N<<1],ver[N<<1],edge[N<<1],tot=0;
bool vis[N];
vector<int> path;

void add(int a,int b,int c){
	ver[++tot]=b,edge[tot]=c,nxt[tot]=h[a],h[a]=tot;
}

void dfs(int x,int val){
	if(vis[x]){
		if(ans[x]!=val) {cout<<-1;exit(0);}
		return;
	}
	ans[x]=val,vis[x]=1,path.push_back(x);
	for(int i=h[x];i;i=nxt[i]){
		int v=ver[i],e=edge[i];
		dfs(v,val^e);
	}
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int a,b,c;
		cin>>a>>b>>c;
		add(a,b,c),add(b,a,c);
	}
	
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			dfs(i,0);
			for(int j=0;j<=30;j++){
				int cnt=0;
				for(int x=0;x<path.size();x++){
					if(ans[path[x]]&(1<<j)) cnt++;
				}
				if(cnt*2>path.size()){
					for(int x=0;x<path.size();x++){
						ans[path[x]]^=(1<<j);
					}
				}
			}
			path.clear();
		}
	}
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<" ";
	}
	
	return 0;
} 
```

---

## 作者：chenzhiyou2009 (赞：1)

看到异或，那么大概率需要拆位，我们不妨说对于限制 $(x,y,z)$，其实就是要求：在二进制下，若 $z$ 的某一位是 $1$，那么 $x,y$ 的这一位需要不同，否则 $x,y$ 的一位应该相同。

这样的话，我们可以想到初步的思路：对于互相有限制的一些数，对于每一位，我们可以先将其中一个数的这一位设为 $0$，随后得出其它所有数的这一位。

如果在计算的过程中出现了矛盾（之前填过的数被填上了其它的数），那么就不存在填法，输出 $-1$ 然后结束即可。

我们在过程中统计使用了几个 $1$，如果使用 $1$ 的数量超过了总数的一半，那么就意味着我们可以最开始填 $1$，然后让所有的 $1$ 都变成 $0$，$0$ 都变成 $1$，从而获得更小的总和。

之后我们发现，可以对于限制建无向带权图，使得对于 $x,y,z$，创建 $(x \to y),(y \to x)$ 两条边权为 $z$ 的边。

对于一个连通块，我们任取一个起点，将最初的权值设为 $0$，然后在 dfs 的过程中按照边权异或不断处理，如果出现矛盾直接判无解。这相当于对于所有位都先填上能满足限制的解。

在 dfs 过程中判无解是：如果已经访问过这个节点，并且现在异或出来的结果与它之前钦定的结果不一样，那么就不行。代码上就是访问过的节点我们先让他再走过来一次，方便判断无解。

随后为了满足总和最小，要用上文提到的方式，对于一个连通块内的每一位贪心。

感觉这道题就是思路简单但是实现比较精妙，建议上位绿。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define For(i, j, k) for (int i = j; i <= k; ++ i)
#define Rof(i, j, k) for (int i = j; i >= k; -- i)
#define ll long long
#define db double
#define vi vector<int>
#define pb push_back
#define pii pair<int, int>
#define mkp make_pair

const int N = 2e5 + 10;

int n, m, a[N];
bool vis[N] = {false}, flg = false;
vector<pii > g[N];
vi vec;

void dfs(int now, int val) {
    if (vis[now] && a[now] != val) {
        flg = true;
    }
    if (vis[now]) {
        return ;
    }
    vis[now] = true, a[now] = val, vec.pb(now);
    for (auto v : g[now]) {
        dfs(v.first, val ^ v.second);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    cin >> n >> m;
    For (i, 1, m) {
        int x, y, z;
        cin >> x >> y >> z;
        g[x].pb({y, z});
        g[y].pb({x, z});
    }
    For (i, 1, n) {
        if (!vis[i]) {
            vec.clear();
            dfs(i, 0);
            For (j, 0, 30) {
                int cnt = 0;
                for (auto u : vec) {
                    cnt += bool(a[u] & (1 << j));
                }
                if (cnt > vec.size() - cnt) {
                    for (auto u : vec) {
                        a[u] ^= (1 << j);
                    }
                }
            }
        }
    }
    if (flg) {
        cout << -1 << '\n';
        return 0;
    }
    For (i, 1, n) {
        cout << a[i] << ' ';
    }
    cout << '\n';

    return 0;
}
```

---

## 作者：HirasawaYuii (赞：1)

# [ABC396E] Min of Restricted Sum 题解

[原题链接](https://atcoder.jp/contests/abc396/tasks/abc396_e)

## 思路

将每对 $x_i,y_i,z_i$ 建为无向图。设 $a_i$ 为节点 $i$ 的值，对于每个连通块预设根节点值为 $0$，进行BFS。对于一条从 $x$ 连向 $y$ 的边，若 $a_y$ 有值，则判断 $x_i\oplus y_i$ 是否等于 $z_i$，若不等于则无解。若 $a_y$ 无值，则设 $y_i=x_i\oplus z_i$。

得出一组解后，对于每个连通块，按位看，因为所有值按位取反后结果不变，所以若这个连通块中的所有解中，当前位为 $1$ 的数量比 $0$ 多，则能使答案和变小。

```c++
// Problem: E - Min of Restricted Sum
// Contest: AtCoder - AtCoder Beginner Contest 396
// URL: https://atcoder.jp/contests/abc396/tasks/abc396_e
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// Date: 2025-03-08 20:15:02
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define mst(x, y) memset(x, y, sizeof(x))
#define pii pair<int, int>
#define fi first
#define se second
#define mp(x, y) make_pair(x, y)
#define pb(x) push_back(x)

int read(){int x = 0, f = 1;char c = getchar();while(c < '0' || c > '9'){if(c == '-') f = -1;c = getchar();}while(c >= '0' && c <= '9'){x = 10*x+c-'0';c = getchar();}return f*x;}
void writ(int x){if(x < 0){putchar('-');x = -x;}if(x > 9) writ(x/10);putchar(x%10 | 0x30);return;}
void write(int x){writ(x);puts("");}
void wr(int x){writ(x);putchar(' ');}
const int N = 2000005, inf = 0x3f3f3f3f;

int n, m, d[N], idx;
int hd[N], ver[N], nxt[N], val[N];
queue <int> q;

void add(int x, int y, int w){
	nxt[++idx] = hd[x];
	ver[idx] = y;
	val[idx] = w;
	hd[x] = idx;
}
int bfs(){
	mst(d, -1);
	for(int x = 1;x <= n;x++){
		vector <pii> v;
		if(d[x] == -1){
			while(q.size()) q.pop();
			q.push(x);
			d[x] = 0;
			while(q.size()){
				int t = q.front();
				q.pop();
				v.push_back(mp(d[t], t));
				for(int i = hd[t];i;i = nxt[i]){
					int y = ver[i];
					if(d[y] == -1){
						d[y] = d[t]^val[i];
						q.push(y);
					}
					else if(d[y] != (d[t]^val[i])){
						write(-1);
						return 1;
					}
				}
			}
			int xorr = 0;
			for(int j = 31;j >= 0;j--){
				int mod = (1<<j), cnt1 = 0, cnt2 = 0;
				for(int i = 0;i < v.size();i++){
					if(d[v[i].se]&mod) cnt1++;
					else cnt2++;
				}
				if(cnt1 >= cnt2){
					xorr |= mod;
				}
			}
			for(int i = 0;i < v.size();i++){
				d[v[i].se] ^= xorr;
			}
		}
	}
	return 0;
}
void init(){
	n = read(), m = read();
	for(int i = 1;i <= m;i++){
		int x = read(), y = read(), w = read();
		add(x, y, w); add(y, x, w);
	}
}
void solve(){	
	if(bfs()) return;
	for(int i = 1;i <= n;i++) wr(d[i]);
}

signed main(){
	init();
	solve();
	return 0; 
}
```

---

## 作者：Dream_poetry (赞：1)

### 思路：

既然是异或，所以每位答案互不干涉。

考虑枚举边权每一位，进行并查集合并，若异或为 $1$，则合并 $(x,y+n)$，$(x+n,y)$，否则合并 $(x,y)$，$(x+n,y+n)$。

我们把 $n+1$ 到 $n+n$ 权值记为 $1$，$1$ 到 $n$ 记为 $0$，每次合并再把权值合并，最后对于每个点，判断它这一位取 $0$ 和 $1$ 哪个更优。

注意，若此时权值相同，注意对选择了哪个集合打上标记，否则可能很容易被卡死。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;

int ans[5000005];


int fa[5000005];
int v[5000005];
int x[5000005];
int y[1000005];
int z[1000005];

inline int find(int x){
    if (fa[x]!=x) fa[x]=find(fa[x]);
    return fa[x];
}
int ok[1000005];


signed main(){
	cin>>n>>m;
	for (int i=1;i<=m;i++){
		cin>>x[i]>>y[i]>>z[i];
	}	
	for (int T=30;~T;T--){
		for (int i=1;i<=n;i++){
			ok[i]=0;
			fa[i]=i;
			v[i]=0;
		}
		for (int i=n+1;i<=n+n;i++){
			fa[i]=i;
			ok[i]=0;
			v[i]=1;
		}
		for (int i=1;i<=m;i++){
			int u1=find(x[i]);
			int u2=find(x[i]+n);
			int v1=find(y[i]);
			int v2=find(y[i]+n); 
			if ((z[i]>>T)&1ll){
				if (u1==v2) continue;
				v[u1]+=v[v2];				
				fa[v2]=fa[u1];
				v[u2]+=v[v1];
				fa[v1]=fa[u2];
			}
			else{
				if (u1==v1) continue;
				v[u1]+=v[v1];				
				fa[v1]=fa[u1];
				v[u2]+=v[v2];
				fa[v2]=fa[u2];
			}
		}
		for (int i=1;i<=n;i++){
			int a=find(i);
			int b=find(i+n);
			if (a==b){
				cout<<-1;
				return 0;
			}
			if (ok[a]){
				continue;
			}
			else if (ok[b]){
				ans[i]+=(1<<T);
			}
			else if (v[a]>v[b]){
				ans[i]+=(1<<T);
				ok[b]=1;
			}
			else{
				ok[a]=1;
			}
		}
	}
	for (int i=1;i<=n;i++){
		cout<<ans[i]<<' ';
	}
	return 0;
}
```

---

## 作者：lfxxx_ (赞：1)

~~AT 怎么做到一场比赛三道 DFS 的？~~

我们可以对 $Z_i$ 按位差分，对 $Z_i$ 的第 $j$ 位记为 $C_{j,i}$。

我们考虑对于每一位进行处理，假设现在处理到第 $k$ 位，则我们让 $X_i$ 和 $Y_i$ 连一条无向边，边权位 $C_{k,i}$。

然后我们对每一个联通块搜索，我们发现定下一个值以后就可以定下这个联通块的值，于是我们考虑对联通块中的任意一个点分类讨论，这个点的权值为 $0$ 还是 $1$，统计出 $1$ 数量最少得情况。

最后把现在答案赋值到原数组上。

时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m;
int a[N],b[N],c[31][N],d[N];
vector<pair<int,int> >edge[N];
int cnt;
bool vis[N][3];
int ans[N],tmp[N];
void dfs(int k,int u,int d)
{
    if(vis[u][k])
        return ;
    vis[u][k]=1;
    tmp[u]=d;
    cnt+=d;
    for(auto &[v,w]:edge[u])
        dfs(k,v,d^w);
}
void solve(int k)
{
    memset(tmp,0,sizeof tmp);
    memset(vis,0,sizeof vis);
    for(int i=1;i<=n;++i)
        edge[i].clear();
    for(int i=1;i<=m;++i)
        edge[a[i]].emplace_back(b[i],c[k][i]),edge[b[i]].emplace_back(a[i],c[k][i]);
    for(int i=1;i<=n;++i)
        if(!vis[i][0])
        {
            cnt=0;
            dfs(0,i,0);
            int temp=cnt;cnt=0;
            dfs(1,i,1);
            if(temp<cnt)
                cnt=0,dfs(2,i,0);
        }
    for(int i=1;i<=n;++i)
    {
        
        ans[i]|=(tmp[i]<<k);
        // cout<<tmp[i]<<' ';
    }
    // cout<<'\n';
}
signed main()
{
    cin>>n>>m;
    for(int i=1;i<=m;++i)
    {
        int x;
        cin>>a[i]>>b[i]>>x;d[i]=x;
        for(int j=0;j<=30;++j)
            c[j][i]=((x>>j)&1);
    }
    for(int i=0;i<=30;++i)
        solve(i);
    for(int i=1;i<=m;++i)
        if((ans[a[i]]^ans[b[i]])!=d[i])
        {
            cout<<-1;
            return 0;
        }

    for(int i=1;i<=n;++i)
        cout<<ans[i]<<' ';
}
```

---

## 作者：AstaVenti_ (赞：1)

# $\mathbf{0x00}$ 启

蒟蒻的第 $\color{red}\mathbf{51}$ 篇题解。

# $\mathbf{0x01}$ 承

给定序列 $X,Y,Z$，构造一个有 $m$ 项的序列 $A$ 使得 $\forall A_{X_i}\oplus A_{Y_i}=Z_i$ 且序列中元素总和最小。

# $\mathbf{0x02}$ 转

我们可以把每一个 $X_i$ 到 $Y_i$ 的约束看成一条边权为 $Z_i$ 的边，建图，其中每一个节点对应一个 $A_i$。这样的话只需要知道图中一个节点的值就可以推导出所有元素的值。

$\mathbf{Q:}$ 如何判断是否有解？

$\mathbf{A:}$ 如果建出的图中出现环，且从某一个节点遍历完这个环再次回到这个节点时，每个边权的异或结果不为 $0$，则推出矛盾，无解。此外，如果图中的环异或的结果为 $0$ 或图中根本不存在环，则一定有解。

$\mathbf{Q:}$ 如何使结果最小？

$\mathbf{A:}$ 考虑某一个节点。由于 $A\oplus B = (A\oplus x)\oplus (B\oplus x)$，因此若原始数组中元素满足所有异或约束，则对所有元素的某一位**同时**取反后，约束仍然成立。于是我们可以统计这个节点点权中 $0$ 和 $1$ 的数量，如果 $1$ 的数量更多，就可以将这个数的每一个二进制位都取反，且在能保证结果最小的前提下依然满足要求。

$\mathbf{Q:}$ 如果 $0$ 的数量等于 $1$ 的数量呢？

$\mathbf{A:}$ 可以取反，不会有影响的。



# $\mathbf{0x03}$ 合


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m;
vector<pair<ll,ll>>g[200005];
int main(){
	cin>>n>>m;
	for(ll i=1,u,v,w;i<=m;i++){
		cin>>u>>v>>w;
		g[u].push_back({v,w});
		g[v].push_back({u,w}); 
	}
	vector<ll>ans(n+1,-1);
	for(ll i=1;i<=n;i++){
		if(ans[i]!=-1)continue;
		ans[i]=0;
		vector<ll>ltk={i};
		for(ll j=0;j<ltk.size();j++){
			ll val=ans[ltk[j]];
			for(auto&[v,nw]:g[ltk[j]]){
				if(ans[v]==-1){
					ltk.push_back(v);
					ans[v]=nw^val;
				}else if(ans[v]!=(nw^val)){
					cout<<-1;
					return 0;
				}
			}
		}
		for(ll j=0;j<=30;j++){
			ll num=0;
			for(auto &k:ltk){
				if(ans[k]&(1<<j))num++;
			}
			if(num>ltk.size()-num){
				for(auto &k:ltk){
					ans[k]^=(1<<j);
				}
			}
		}
	}
	for(ll i=1;i<=n;i++){
		cout<<ans[i]<<" ";
	}
}
```

---

## 作者：yyrwlj (赞：0)

不要把这题想难，其实随便做应该都可以。

发现可以拆位，那么限制就转化成了两个点的值必须相等或不相等。

先考虑相等，我们用并查集把每个相等点的极大联通块缩成一点，那么不等直接在这些点上连边即可（显然出现自环就无解）。

得出的图上每两个相邻点的权值都不能相同，可以联想到二分图，我们把这张图进行二分图染色（无法染色就无解）。

发现对于图上每个联通块，我们把它的颜色全部翻转也是可行的染色方案，且这两种染色方案是这个联通块唯二的两个可行方案。

我们让每个联通块的两种选择方案取权值更小的那种就可以了。

```cpp
#define pb push_back
using namespace std;
const int N = 200005;
int fa[N], siz[N], color[N], all, cnt;
vector<int> g[N], node;
struct Node{
	int a, b, c;
}q[N];
bool st[N];
int ed[N];
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
bool dfs(int u,int op)
{
    color[u] = op;
    for (int i : g[u])
    {
        if (!color[i])
        {
            if (!dfs(i, op ^ 3))
                return false;
        }
        else if (color[i] == op)
            return false;
    }
    return true;
}
void dfs2(int u)
{
	node.pb(u);
	st[u] = true;
	all += siz[u];
	if (color[u] == 1)
		cnt += siz[u];
	for (int i : g[u])
		if (!st[i])
			dfs2(i);
}
void work()
{
	int n, m;
	cin >> n >> m;
	for (int i=1;i<=m;i++)
		cin >> q[i].a >> q[i].b >> q[i].c;
	for (int k=0;k<=30;k++)
	{
		for (int i=1;i<=n;i++)
		{
			fa[i] = i;
			g[i].clear();
			siz[i] = color[i] = 0;
			st[i] = false;
		}
		for (int i=1;i<=m;i++)
		{
			int a = q[i].a, b = q[i].b, c = q[i].c>>k&1;
			if (!c)
				fa[find(a)] = find(b);
		}
		for (int i=1;i<=n;i++)
			siz[find(i)] ++;
		for (int i=1;i<=m;i++)
		{
			int a = find(q[i].a), b = find(q[i].b), c = q[i].c >> k & 1;
			if (c)
			{
				if (a == b)
				{
					cout << -1;
					return;
				}
				g[a].pb(b),g[b].pb(a);
			}
		}
		for (int i=1;i<=n;i++)
		{
			if (find(i) != i || color[i])
				continue;
			if (!dfs(i,1))
			{
				cout << -1;
				return;
			}
		}
		for (int i=1;i<=n;i++)
		{
			if (find(i) != i || st[i])
				continue;
			all = cnt = 0;
			node.clear();
			dfs2(i);
			if (all - cnt < cnt)
				for (int j : node)
					color[j] ^= 3;
			cnt = min(cnt, all - cnt);
		}
		for (int i=1;i<=n;i++)
			if (color[find(i)] == 1)
				ed[i] |= 1 << k;
	}
	for (int i=1;i<=n;i++)
		cout << ed[i] << ' ';
}
```

---

## 作者：LionBlaze (赞：0)

首先维护异或是带权并查集模版题。

使用带权并查集维护所有异或信息，判断是否矛盾，然后分组。

对于每一组，显然确定一个值后所有的值也就都确定了。于是我们要确定一个 $x$，使得这一组中所有值异或 $x$ 的结果最小。

注意到每一位选择各自独立，考虑贪心。

对于每一个二进制位，如果这一组中这个二进制位是 $1$ 的更多，则 $x$ 的这一位是 $1$，否则是 $0$。

这样对于每一组求出各自的 $x$ 之后，把每一组中的数字都异或上 $x$，再输出即可。

---

## 作者：zengziqvan (赞：0)

~~赛时并查集没初始化 38 个点能过 20 个也是糖丸了。~~

考虑转化为图论模型。

我们对于每个形如 $a_x\oplus a_y=z$ 的等式，在 $x$ 与 $y$ 中间连一条权值为 $z$ 的无向边。那么最后得到的一定是有若干个联通块的无向图。

判断无解直接看是否存在边权异或和不为 $0$ 的环即可。

再考虑如何求和最小的解。

对于每个联通块，我们考虑让其中一个点的权值强制赋值为 $0$，再根据这个东西做 dfs 求其余点的权值。

发现如果联通块其中一个点的点权异或上了一个值 $p$，那么该联通块的其余所有点的点权也必须异或上 $p$。

因此不妨按位考虑：如果这一位统一异或上 $1$ 比不异或更优就异或，否则不处理。最后的点权即为所求。

复杂度 $O(n\log V)$，其中 $V$ 为值域。

---

## 作者：wmrqwq (赞：0)

这是一篇视频题解。

![](bilibili:BV1xBRsYxE6S?t=406)

[代码链接](https://atcoder.jp/contests/abc396/submissions/63536263)

---

## 作者：Alexxtl (赞：0)

## 题目链接

[**Luogu**](https://www.luogu.com.cn/problem/AT_abc396_e)

[**Atcoder**](https://atcoder.jp/contests/abc396/tasks/abc396_e)

## 题意简述

#### 问题陈述

给你整数 $N, M$ 和长度为 $M$ 的三个整数序列： $X = (X_1, X_2, \ldots, X_M)$ 、 $Y = (Y_1, Y_2, \ldots, Y_M)$ 和 $Z = (Z_1, Z_2, \ldots, Z_M)$ 。保证 $X$ 和 $Y$ 中的所有元素都在 $1$ 和 $N$ 之间。

我们称长度为 $N$ 的非负整数序列 $A = (A_1, A_2, \ldots, A_N)$ 为**好序列**，当且仅当它满足以下条件时：

- 对于 $i$ 与 $1 \le i \le M$ 的每一个整数， $A_{X_i}$ 与 $A_{Y_i}$ 的 XOR 为 $Z_i$ 。

确定是否存在一个好序列 $A=(A_1,A_2,\ldots,A_N)$ ，如果存在，找出一个使其元素之和 $\displaystyle \sum_{i=1}^N A_i$ 最小的好序列。

## 解法说明

首先考虑如何判断是否存在好序列。注意到题目中给了许多约束，可以将这些约束关系转化为边，然后在图上进行维护。

容易发现，此时图中被分割成了很多个连通块。对于每个连通块，可以将其中一个节点的权值设为 $0$，并通过约束关系推导出其他节点的权值。这样，在处理新的约束时，如果发现已有的点权与推出的结果相悖，则无解。

这显然可以用带权并查集维护。具体地，每个节点的权值设置为到其父节点的异或值。对于每个约束中的两个点 $x,y$，设其权值为 $a_x$ 和 $a_y$，检查其是否位于同一集合内，分成两种情况进行讨论：

1. $x$ 与 $y$ 在同一集合内时。由于路径压缩，二者会拥有相同的父节点。由于点权维护的是到父节点的异或值，故可将两点权值异或后判断是否与约束中的 $z$ 相等，如果不相等则无解。

2. $x$ 和 $y$ 不在同一个集合内。此时需要合并两个集合。具体地，当合并两个集合时，分别记 $x$ 与 $y$ 所在集合的根节点为 $rx$ 和 $ry$。如合并后令 $rx$ 为根，则由约束关系推得合并后 $a_{rx} = a_x \oplus a_y \oplus z$。

接下来处理和最小的好序列。对于每个连通块的根 $r$，则该连通块的和为块内所有点的权值分别与 $a_r$ 相异或后的和。可以分别处理每个二进制位，统计该连通块中每个 $a_x$ 该位上为 $1$ 的个数，记为 $cnt$。设 $k$ 为该连通块内节点的总个数，则如果 $k-cnt > cnt$ 则根的该位为 $0$，否则为 $1$。

## 通过代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N=2e5+10;

namespace IO{
	inline int read(){ int x=0,f=1;char ch=getchar(); while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); } while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar(); return x*f; }
	inline void write(int x){ if(x<0) putchar('-'),x=-x; if(x>9) write(x/10); putchar(x%10+'0'); }
}using namespace IO;

namespace code{
	int n,m,a[N],fa[N],cnt[31],ans[N],num;
	vector<int> v[N];
	
	int getfa(int x){
		if(fa[x]==x) return x;
		int r=getfa(fa[x]);
		a[x]^=a[fa[x]],fa[x]=r;
		return r;
	}

	void solve(){
		n=read(),m=read();
		for(int i=1;i<=n;++i) fa[i]=i;
		for(int i=1;i<=m;++i){
			int x=read(),y=read(),z=read();
			int rx=getfa(x),ry=getfa(y);
			if(rx==ry) if((a[x]^a[y])!=z) return write(-1),void();
			if(rx!=ry) fa[ry]=rx,a[ry]=a[x]^a[y]^z;
		}
		for(int i=1,j;i<=n;++i) j=getfa(i),v[j].push_back(i),ans[i]=a[i];
		for(int i=1;i<=n;++i){
			if(fa[i]!=i||v[i].empty()) continue;
			memset(cnt,0,sizeof(cnt)),num=0;
			for(auto it=v[i].begin();it<v[i].end();++it){
				int x=*it;
				for(int j=0;j<=30;++j) cnt[j]+=a[x]&(1<<j)?1:0;
			}
			for(int j=0;j<=30;++j) if(cnt[j]>v[i].size()-cnt[j]) num|=(1<<j);
			for(auto it=v[i].begin();it<v[i].end();++it){
				int x=*it;
				ans[x]^=num;
			}
		}
		for(int i=1;i<=n;++i) write(ans[i]),putchar(' ');
	}
}

signed main(){
	code::solve();
	return 0;
}
```

---

## 作者：UniGravity (赞：0)

每一位的取值互不影响，所以我们按位考虑。

假设现在在第 $k$ 位，若 $z_i$ 的第 $k$ 位为 $1$ 则可以看做 $a_{x_i}\neq a_{y_i}$，否则 $a_{x_i}= a_{y_i}$（这里 $a_i$ 指的是实际上 $a_i$ 的第 $k$ 位）。

把相等的限制用并查集缩起来，此时不相等的限制相当于给图染色使得相邻两个点颜色不同。

我们对每个连通块分别考虑，如果染色中出现冲突直接无解，否则选择出现次数较小的颜色将其赋为 $1$。

时间复杂度 $O(n\log V)$。

```cpp
const int N=200005;
int n,m,x[N],y[N],z[N],a[N];
int fa[N];il int find(int x){return (x==fa[x])?x:(fa[x]=find(fa[x]));}
il void merge(int x,int y){x=find(x),y=find(y);if(x!=y)fa[y]=x;}
vector<int>e[N];

int col[N],ans[N];bool fg;
vector<int>v,vc[N];
il void dfs(int x,int c){
    // cerr<<x<<' '<<c<<'\n';
    if(col[x]){
        if(col[x]!=c)fg=0;
        return;
    }
    col[x]=c,v.eb(x);
    for(int y:e[x])dfs(y,-c);
}

signed main(){
    n=read(),m=read();
    forto(i,1,m)x[i]=read(),y[i]=read(),z[i]=read();
    forto(k,0,31){
        forto(i,1,n)fa[i]=i,e[i].clear(),col[i]=0,vc[i].clear();
        forto(i,1,m)if(!((z[i]>>k)&1))merge(x[i],y[i]);
        forto(i,1,m)if((z[i]>>k)&1)e[find(x[i])].eb(find(y[i])),e[find(y[i])].eb(find(x[i]));
        fg=1;
        forto(i,1,n)vc[find(i)].eb(i);
        forto(i,1,n)if(find(i)==i&&!col[i]){
            v.clear(),dfs(i,1);
            if(!fg)return puts("-1"),0;
            int c1=0,c2=0;
            for(int x:v)for(int j:vc[x])if(col[find(j)]==-1)c1++;else c2++;
            if(c1<c2){for(int x:v)for(int j:vc[x])if(col[find(j)]==-1)ans[j]|=1<<k;}
            else{for(int x:v)for(int j:vc[x])if(col[find(j)]==1)ans[j]|=1<<k;}
        }
    }
    forto(i,1,n)printf("%d ",ans[i]);puts("");
    return 0;
}
```

---

## 作者：xukehg (赞：0)

考虑图论建模。将每个条件转换为 $x_i$ 到 $y_i$ 之间有一条边权为 $w_i$ 的边，无解即为存在异或和不为 $0$ 的环。

取出这张图的 dfs 森林，对于每一个树，记 $dep_i$ 表示从根到 $i$ 的异或和。因为 dfs 树中没有横叉边
，因此对于一个合法的图中的每一条返祖边均满足 $dep_{u_i} \oplus dep_{v_i} \oplus w_i = 0$。

考虑如何求出 $\sum^{i = 1}_{n}a_i$ 的最小值。对于一棵树，假设我们知道了 $a_1$ 的值，就可以求出其他的点的值。而 $a_i$ 显然等于 $a_1 \oplus dep_i$。我们可以按位贪心，从大到小确定 $a_i$ 二进制中每一位的值。具体的，当前到了第 $x$ 位，看所有的 $dep_i$ 中有多少个数第 $x$ 位是 $1$ 即可。

[记录。](https://atcoder.jp/contests/abc396/submissions/63558190)

---

## 作者：Statax (赞：0)

## 前言

蒟蒻第一次不看题解切掉 ABCDEF，写几篇题解庆祝。

## 思路

（注：以下说的数的第 $i$ 位都指从低到高的第 $i$ 位。）

一般看到这种位运算题都是拆开来做的。

我们知道异或的特性：相同为 $0$，不同为 $1$。

那我们只需把 $Z$ 每一位都拆出来，$Z$ 的第 $i$ 位如果为 $0$ 就代表这两个点第 $i$ 位应该相同，边权就为 $0$，反之亦然，共建 $32$ 个无向带权图即可。

然后分别跑这 $32$ 个图，每个图可能会遍历多次，总之每次遍历要把点所在整个连通块都找到。

记与初始点相同的个数为 $x$，不同的个数为 $y$，如果 $x > y$，那就给所有不同的点对应位赋值 $1$，反之如此，原因是题目要求 $\sum A$ 要尽可能小，贪心即可。

## 代码

时间复杂度 $O(nV + mV)$，其中 $V = 32$。

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <vector>
#include <algorithm> 
using namespace std;

#define x first
#define y second
#define db double
#define pb push_back
#define ll long long
#define i128 __int128
#define ull unsigned ll
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

const int MAXN = 2e5 + 5;
const int inf = 2147483627;
const int mod = 998244353;
const db eps = 1e-9;

template <typename T> inline void read (T &x) {
	x = 0; T f = 1; char ch = getchar ();
	while (!isdigit (ch)) { if (ch == '-') f = -1; ch = getchar (); }
	while (isdigit (ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar ();
	x *= f;
}

template <typename T, typename... Arp> inline void read (T &x, Arp &...arp) {
	read(x), read(arp...);
}

int n, m, a[MAXN], vis[MAXN];
vector <pair <int, int> > g[32][MAXN];

// 0 表示相同， 1 表示不同

int l1, l2;
int node1[MAXN], node2[MAXN];

void dfs (int f, int u, int w) {
    if (vis[u] != -1) {
        if (vis[u] != w)    
            puts ("-1"), exit (0);
        return ;
    }
        
    if (w & 1) {
        node2[++l2] = u;
    } else {
        node1[++l1] = u;
    } vis[u] = w;
        
    
    for (const auto & v : g[f][u]) {
        dfs (f, v.x, w ^ v.y);  
    }
}

signed main () {
//	freopen (".in", "r", stdin);
//	freopen (".out", "w", stdout);
    read (n, m);
    for (int i = 1; i <= m; ++i) {
        int x, y, z;
        read (x, y, z);
        if (x > y) swap (x, y);
        for (int j = 0; j < 32; ++j) 
            g[j][x].pb ({y, (z >> j) & 1}),
            g[j][y].pb ({x, (z >> j) & 1});
    }
    
    for (int i = 0; i < 32; ++i) {
        for (int i = 1; i <= n; ++i)
            vis[i] = -1;
        
        for (int j = 1; j <= n; ++j) {
            if (vis[j] == -1) {
                l1 = 0, l2 = 0;
                dfs (i, j, 0);
                if (l1 > l2) {
                    for (int k = 1; k <= l2; ++k) 
                        a[node2[k]] += (1 << i);
                } else {
                    for (int k = 1; k <= l1; ++k) 
                        a[node1[k]] += (1 << i);
                }
            }
        }
            
    }
    
    for (int i = 1; i <= n; ++i) printf ("%d ", a[i]);
	return 0;
}
```

---

## 作者：WuMin4 (赞：0)

## [[ABC396E] Min of Restricted Sum](https://atcoder.jp/contests/abc396/tasks/abc396_e)

## 题意

构造一个和最小的长度为 $n$ 的非负整数序列 $a$，使得该序列满足 $m$ 个条件 $x_i,y_i,z_i$，表示 $a_{x_i}\text{xor }a_{y_i}=z_i$。

## 思路

首先我们将 $x_i,y_i,z_i$ 的限制转化为一个无向图，在图上考虑问题。

发现当 $a_{x_i}$ 确定时，$a_{y_i}$ 也一定确定，则对于图中的一个连通块，只需要确定其中的一个值，其它的值也会一起被确定。

对于一个连通块中合法的一种方案 $a_{id_1},a_{id_2},\cdots,a_{id_{len}}$，将所有数异或一个值 $x$ 仍然满足限制条件，因为相同的数字异或值为 $0$。

于是可以对每个连通块将其中的一个初值设为 $0$ 进行 dfs 算出剩余的 $a_i$，顺便判一下无解，再通过将所有数异或一个值 $x$ 使得 $a_i$ 之和最小。

对于所有 $a_i$ 在二进制下的第 $k$ 位若的 $1$ 的数量大于 $0$ 的数量，则可以通过异或 $2^{k-1}$ 反转 $0$ 和 $1$，也就使得整体的和减小，对每一位计算即可求出 $x$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
	int x,d;
};
int n,m,a[200005],ans[200005];
bool has=true;
vector<node> t[200005];
vector<int> to;
void dfs(int x){
	to.push_back(x);
	for(node v:t[x]){
		if(ans[v.x]!=-1){
			if((ans[x]^v.d)!=ans[v.x]){
				has=false;
				return;
			}
		}
		else{
			ans[v.x]=ans[x]^v.d;
			dfs(v.x);
			if(!has) return;
		}
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		ans[i]=-1;
	for(int x,y,d,i=1;i<=m;i++){
		cin>>x>>y>>d;
		t[x].push_back({y,d});
		t[y].push_back({x,d});
	}
	for(int i=1;i<=n;i++){
		if(ans[i]==-1){
			ans[i]=0,to.clear();
			dfs(i);
			int xr=0;
			for(int j=0;j<32;j++){
				int cc=0;
				for(int v:to)
					if(ans[v]&(1<<j)) cc++;
				if(cc>(int)to.size()/2)
					xr|=(1<<j);
			}
			for(int v:to)
				ans[v]^=xr;
		}
	}
	if(!has)
		cout<<-1;
	else
		for(int i=1;i<=n;i++)
			cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：yzljy (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc396_e)  
[AT传送门](https://atcoder.jp/contests/abc396/tasks/abc396_e)

### 题意

给定三个长度为 $M$ 的序列 $X,Y,Z$，问是否存在一个长度为 $N$ 的序列 $A$，满足 $\forall1\le i\le M,A_{X_{i}}\oplus A_{Y_{i}}=Z_{i}$。输出 $\sum\limits_{i=1}^{n}A_{i}$ 最小的任意一种方案，若不存在合法的 $A$，则输出 $-1$。

### 数据范围

$2\le N\le 2\times10^{5}$  
$2\le M\le 10^{5}$  
$1\le X_{i},Y_{i}\le N$  
$0\le Z_{i}<10^{9}$

### 思路

首先，异或是存在交换律的，也就是 $x\oplus y=y\oplus x$。  
因此我们考虑将 $X_{i}$ 和 $Y_{i}$ 之间连一条边，边权为 $Z_{i}$，那么问题就转化成了：对于任意一条边，都需要满足它的两个端点的权值的异或和，等于这条边的权值。若存在一条边出现矛盾，那么就不存在合法的方案。  

我们知道，若 $x=y$，那么有 $x\oplus z=y\oplus z$，因此我们找出一种合法的方案后，对该连通块的所有点的权值都异或上一个相同的数，依然是合法的方案。

找任意一个合法的方案是容易的，我们 DFS 一下，对未访问过的点赋值，对访问过的点进行检查，出现矛盾直接为无解。

找出一种方案后，我们统计一下当前这个连通块下，每个点的权值在二进制下每一位的 $0$ 的数量和 $1$ 的数量。假如 $1$ 的数量大于 $0$ 的数量，那么显然对于这一位，把 $1$ 异或成 $0$，$0$ 异或成 $1$ 是更优的。

最后再跑一次 DFS，把这个连通块内每个点的权值都改一下就行了。

注意：图不一定全联通。

### 代码

```cpp
// Problem: E - Min of Restricted Sum
// Contest: AtCoder - AtCoder Beginner Contest 396
// URL: https://atcoder.jp/contests/abc396/tasks/abc396_e
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=4e5+10;
const int mod1=1e9+7;
const int mod2=998244353;
const int inf_int=0x7f7f7f7f;
const long long inf_long=0x7f7f7f7f7f7f7f7f;
const double eps=1e-9;
char Buf[1<<23],*P1=Buf,*P2=Buf;
#define getchar() (P1==P2&&(P2=(P1=Buf)+fread(Buf,1,1<<23,stdin),P1==P2)?EOF:*P1++)
template<typename type>
inline void read(type &x){
	x=0;
	bool f=false;
	char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	if(f) x=-x;
}
template<typename type,typename... args>
inline void read(type &x,args&... y){
	read(x),read(y...);
}

int n,m,k,num,head[MAXN],t[MAXN][40][2],z[MAXN];
bool vis[MAXN],vis2[MAXN];
struct node{
	int to,next,val;
}edge[MAXN<<1];

void build(int u,int v,int w){
	edge[++k].to=v;
	edge[k].next=head[u];
	edge[k].val=w;
	head[u]=k;
}

void dfs(int f,int fa,int u){
	vis[u]=true;
	for(int i=0;i<=35;i++){
		if(z[u]&(1ll<<i)) t[f][i][1]++;
		else t[f][i][0]++;
	}
	for(int i=head[u];i;i=edge[i].next){
		int v=edge[i].to;
		if(vis[v]){
			if(z[v]!=(z[u]^edge[i].val)){
				cout<<-1;
				exit(0);
			}
			continue;
		}
		z[v]=z[u]^edge[i].val;
		dfs(f,u,v);
	}
}

void work(int u){
	vis2[u]=true;
	z[u]^=num;
	for(int i=head[u];i;i=edge[i].next){
		int v=edge[i].to;
		if(vis2[v]) continue;
		work(v);
	}
}

signed main(){
	read(n,m);
	memset(z,-1,sizeof(z));
	for(int i=1;i<=m;i++){
		int x,y,z;
		read(x,y,z);
		build(x,y,z);
		build(y,x,z);
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			z[i]=0;
			dfs(i,i,i);
			num=0;
			for(int j=0;j<=35;j++) if(t[i][j][1]>t[i][j][0]) num|=(1ll<<j);
			work(i);
		}
	}
	for(int i=1;i<=n;i++) cout<<z[i]<<" ";
	return 0;
}
```

此题在 AtCoder 上评分为 $1358$，转化为图上问题，思路较为容易，建议评绿。

---

## 作者：cyq32ent (赞：0)

各个位是独立的，所以考虑按位计算。假如现在我们在第 $k$ 位，那么我们在第 $k$ 位有 $A_{X_i}\operatorname{xor} A_{Y_i}=Z^{(k)}_i$（其中 $n^{(k)}$ 代表 $n$ 的第 $k$ 位）。我们发现，如果这一位上的 $Z$ 为 $0$，则 $X$ 与 $Y$ 对应的 $A$ 相同。否则不同。所以从 $X_i$ 到 $Y_i$ 连边，并记录每条边代表两个节点相同还是不同，跑一遍类似二分图染色的算法即可。注意到我们需要让结果尽量小，所以我们还需要记录连通块内有多少值为 $1$ 的节点和值为 $0$ 的节点。如果 $1$ 较多，那么就反转。容易证明反转后约束条件仍然满足。

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int>>G[202503];
int color[202503],x[202503],y[202503],z[202503],a[202503],n,m;
int t1,t2;vector<int>T;
int dfs(int u,int c){
	color[u]=c;
	if(c==1)t1++;
	else t2++;
	T.push_back(u);
	for(auto [v,t]:G[u]){
		if(color[v]==0){if(!dfs(v,c*t))return 0;}
		else if(color[v]!=c*t)return 0;
	}return 1;
}
inline int gt(int N,int b){
	return (N>>b)&1;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>x[i]>>y[i]>>z[i];
	for(int k=0;k<=30;k++){
		memset(color,0,sizeof color);
		for(int i=1;i<=n;i++)G[i].clear();
		for(int i=1;i<=m;i++){
			G[x[i]].push_back({y[i],-2*gt(z[i],k)+1});
			G[y[i]].push_back({x[i],-2*gt(z[i],k)+1});
		}for(int i=1;i<=n;i++){
			if(!color[i]){
				t1=t2=0;T.clear();
				if(!dfs(i,1))return cout<<"-1",0;
				if(t1>t2)for(auto u:T)color[u]=-color[u];
			}
		}for(int i=1;i<=n;i++)if(~color[i])a[i]+=(1<<k);
	}for(int i=1;i<=n;i++)cout<<a[i]<<' ';
	return 0;
}
```

---

