# Disappearing Permutation

## 题目描述

一个从 $1$ 到 $n$ 的整数排列是指一个大小为 $n$ 的数组，其中每个从 $1$ 到 $n$ 的整数恰好出现一次。

给定一个从 $1$ 到 $n$ 的排列 $p$。你需要处理 $n$ 个查询。在第 $i$ 次查询中，你将 $p_{d_i}$ 替换为 $0$。每个元素恰好会被替换为 $0$ 一次。查询中的修改会被保留，也就是说，在第 $i$ 次查询后，所有整数 $p_{d_1}, p_{d_2}, \dots, p_{d_i}$ 都会变为 $0$。

在每次查询后，你需要找到修复数组所需的最少操作次数；换句话说，将当前数组转换为从 $1$ 到 $n$ 的任意排列（可能是原始排列 $p$，也可能是其他排列）。

修复数组的操作如下：
- 选择一个从 $1$ 到 $n$ 的整数 $i$，将数组的第 $i$ 个元素替换为 $i$。

注意，每个查询的答案是独立计算的，这意味着你实际上不会执行任何操作，只是计算最少操作次数。

## 说明/提示

- 在第一个测试用例中，每次查询后，每个被替换为 $0$ 的整数都可以通过一次操作恢复。
- 在第二个测试用例中，可以按以下方式操作：
  - 查询 $1$：$p = [4, 5, 3, 0, 2]$，可以转换为 $[{\color{red}1}, 5, 3, {\color{red}4}, 2]$。
  - 查询 $2$：$p = [4, 5, 3, 0, 0]$，可以转换为 $[{\color{red}1}, {\color{red}2}, 3, {\color{red}4}, {\color{red}5}]$。
  - 查询 $3$：$p = [0, 5, 3, 0, 0]$，可以转换为 $[{\color{red}1}, {\color{red}2}, 3, {\color{red}4}, {\color{red}5}]$。
  - 查询 $4$：$p = [0, 5, 0, 0, 0]$，可以转换为 $[{\color{red}1}, {\color{red}2}, {\color{red}3}, {\color{red}4}, {\color{red}5}]$。
  - 查询 $5$：$p = [0, 0, 0, 0, 0]$，可以转换为 $[{\color{red}1}, {\color{red}2}, {\color{red}3}, {\color{red}4}, {\color{red}5}]$。

标红的数字表示被修改的元素。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
3
1 2 3
3 2 1
5
4 5 3 1 2
4 5 1 3 2
7
4 3 1 2 7 5 6
1 2 3 4 5 6 7```

### 输出

```
1 2 3 
2 4 4 5 5 
4 4 4 4 7 7 7```

# 题解

## 作者：wangboyue (赞：2)

# 题意
给定排列 $p$ 和 $n$ 次修改，每次修改将 $p$ 中的一个数修改为 $0$。现在可以通过多次令 $p_i\gets i$ 来将 $p$ 转为一个排列（可不与原排列相同）。
# 思路
对应每次对 $i$ 的修改，明显一定要进行一次操作 $p_i\gets i$。此时：
1. 在原排列中，$p_i=i$：无需进一步操作；
2. 在原排列中，$p_i\neq i$：继续操作 $p_i$ 使得 $p_{p_i}\gets p_i$。此时可能还需要进一步操作，直到当前操作的数 $x$ 满足在原排列中 $p_x=x$。

容易发现，对于确定的 $p$ 和 $i$，其需要进行的操作是确定的。

考虑将“对 $x$ 的操作导致必须对 $y$ 进行操作”视为一条有向边，那么原问题可以转换为一张有向图，且每个点都在一个环上。

此时修改 $i$ 时的操作次数即为其所在连通块的大小（如果这个连通块没有被操作过）。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=1e5+5;
int p[N],d[N],fa[N],siz[N];
bool vis[N];
int find(int x){
	if(fa[x]==x){
		return x;
	}
	return fa[x]=find(fa[x]);
}
void add(int x,int y){
	x=find(x);
	y=find(y);
	if(x!=y){
		fa[x]=y;
		siz[y]+=siz[x];
	}
	return;
}
void help(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		vis[i]=false;
		fa[i]=i;
		siz[i]=1;
	}
	for(int i=1;i<=n;i++){
		cin>>p[i];
		add(p[i],i);
	}
	for(int i=1;i<=n;i++){
		cin>>d[i];
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(vis[find(d[i])]){
			cout<<ans<<" ";
			continue;
		}
		vis[find(d[i])]=true;
		ans+=siz[find(d[i])];
		cout<<ans<<" ";
	}
	return;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		help();
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：zhang_kevin (赞：1)

首先我们要知道关于一个 $1 \sim n$ 的排列有一个性质。

考虑一个 $n$ 个点的有向图，如果第 $i$ 个位置的值是 $x$，就连一条 $i$ 到 $x$ 的有向边。

这个时候构成的图一定是许多不相交的环组成的，因为每个点的入度和出度都为 $1$。

那么，我们考虑对给定排列按照如上方式建图，每次操作则相当于删除一条边。

由于刚才所说的性质，在某次删边操作后，如果一个点在环上，这个位置就不需要改变（因为这些位置正好对应了这些数）。反之，如果一个点不在环上，则一定需要改变（否则就不是排列了）。

因此，我们得到了一个 $\mathcal{O}(n^2)$ 的做法。

注意到每次操作只改变一条边，所以可以把所有操作反过来进行。具体的，初始时这个图中没有边（因为所有值都是 $0$），答案就是 $n$。每次操作变成了加一条边，这个时候可以使用并查集维护每个环的大小和边数。刚开始大小一定比边数少 $1$，但在构成环的那一刻相等了。

所以，我们可以反过来计算，每次操作后如果并查集的大小与边数相等了，就把答案相对于上一次减小环的大小即可。

并查集复杂度很小，忽略后算法的单次询问复杂度为 $\mathcal{O}(n)$，可以通过。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x<<1) + (x<<3) + (ch^48);
		ch = getchar();
	}
	return x * f;
}
const int N = 2e5 + 1;
int n, p[N], d[N], ans[N], f[N], sz[N], edge[N];
inline int find(int k){
	if(f[k] == k) return k;
	return f[k] = find(f[k]);
}
inline void Solve(){
	n = read();
	for(int i = 1; i <= n; i++) f[i] = i, sz[i] = 1, edge[i] = 0;
	for(int i = 1; i <= n; i++) p[i] = read();
	for(int i = 1; i <= n; i++) d[i] = read();
	ans[n] = n;
	for(int i = n - 1; i >= 0; i--){
		int pos = d[i+1];
		int u = pos, v = p[pos];
		u = find(u); v = find(v);
		if(u != v){
			f[v] = u;
			sz[u] += sz[v];
			edge[u] += edge[v] + 1;
		}else{
			edge[u]++;
		}
		ans[i] = ans[i+1] - sz[u] * (sz[u]==edge[u]);
	}
	for(int i = 1; i <= n; i++) cout << ans[i] << " ";
	cout << '\n';
	return;
}
signed main(){
	int T = read();
	while(T--){
		Solve();
	}
	return 0;
}
```

---

## 作者：zhangzirui66 (赞：1)

## 闲话
本文同步发布在 [cnblogs](https://www.cnblogs.com/zhangzirui66)。

---

## 题意

给定两个排列 $p$ 和 $d$，$n$ 次操作，第 $i$ 次将 $p_{d_i}$ 设为 $0$。然后可以进行操作，一次操作定义为指定一个 $k$，将 $a_k$ 设为 $k$，问最少多少次操作能将它复原为一个排列。

---

大致方向为少哪个数填上哪个数，但由于我们只能在指定的地方替换，因此会弄乱别的数，不断循环替换即可，最多全部替换，因此一定有解且复杂度为 $O(\sum n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, a[1000005], d[10000005], vis[10000005], ans;// 使用 vis 来保证复杂度不会假掉，每个数只会访问一遍
int main(){
	cin >> t;
	while(t --){
		ans = 0;
		cin >> n;
		for(int i = 1; i <= n; i ++){
			cin >> a[i];
			vis[i] = 0;
		}
		for(int i = 1; i <= n; i ++){
			cin >> d[i];
		}
		for(int i = 1; i <= n; i ++){
			int j = d[i];
			while(!vis[j]){
				vis[j] = 1;// 不要重复走
				ans ++;
				j = a[j];
				if(j == a[j]) break;
			}
			cout << ans << " ";
		}
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：_xdd_ (赞：0)

提供一个无需并查集的简单解法。

---

### 题意简述：

有一个从 $1$ 到 $n$ 的排列 $p$，做 $n$ 次永久性修改，把排列里第 $d_i$ 个数改为 $0$，对于每次修改，问需要多少次修复操作，才可以把这个更改过的数列重新修复为一个 $1$ 到 $n$ 的排列。

修复操作：$p_i \leftarrow i$。

### 解法：

如果第 $i$ 个数 $p_i$ 被修改了，那么为了我们就要修复第 $i$ 个数。

但是有可能 $p_i$ 这个数因为修复被删去了（也就是 $i\ne p_i$），所以还要继续修复第 $p_i$ 个数。

然后第 $p_i$ 个数也有可能因为刚才的修复被删去了，所以还要继续修复。

……

一直循环下去直到回到第 $i$ 个数。

在图上表示出来，就是一个环。

所以重新修复所用的修复次数就是这个环的节点数。

以上算法可以用并查集解决，我本来是想用并查集解决的，但是写了一半发现不需要。

直接把节点用 `vector` 存起来，用 $vis$ 数组记录这个点是否已经在某个环里（$0$ 为否，$1$ 为是）。

对于每个 $d_i$：

- 如果 $vis_i=0$，按照上述算法把节点连成环，然后把环里每个节点 $j$ 标记 $vis_j=1$，答案加上节点数量。
- 如果 $vis_i=1$，没有新节点出现，所以直接输出答案。

### code

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define r0 return 0
#define inf (0x7fffffff)
#define maxn ( 200000 +5)
#define int long long
using namespace std;
inline int read(){int x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
int t,n,a[maxn];
bool vis[maxn];
vector<int>edge[maxn];
int len[maxn],cnt;
signed main(){
    cin >> t;
    while(t--){
        cin >> n;
        for(int i=1;i<=n;i++){
            cin >> a[i];
            vis[i]=0;
            len[i]=1;
            edge[i].clear();
            cnt=0;
        }
        for(int i=1;i<=n;i++){
            int x,l,r;
            cin >> x;
            if(vis[x]){cout << cnt << ' ';continue;}
            l=x,r=x;
            cnt++;
            vis[x]=1;
            edge[x].push_back(a[x]);
            x=a[x];
            while(!vis[x]){
                cnt++;
                vis[x]=1;
                edge[x].push_back(a[x]);
                l=min(l,x);
                r=max(r,x);
                x=a[x];
            }
            edge[x].push_back(a[x]);
            cout << cnt << ' ';
        }
        cout << endl;
    }
}
```

---

## 作者：zzldd (赞：0)

显然，当 $p_i$ 被更新为 $i$ 时，需要更新 $p_{p_i}$ 使得 $p_i$ 存在于数组中，所以只需要进行 `DFS`，搜到已经被更新过的点时终止，并记录更新的点的数量即可。\
代码如下。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct nd{
	int u,v,nxt;
}e[200005];
int h[200005],vis[200005],cnt=0,ans;
void dfs(int u){
	if(vis[u]) return;
	vis[u]=1;
	ans++;
	dfs(h[u]);
}
void sol(){
	int n;
	cin>>n;
	ans=0;cnt=0;
	for(int i=1;i<=n;i++) {
		cin>>h[i];
	}for(int i=1;i<=n;i++) {
		int x;
		cin>>x;
		dfs(x);
		cout<<ans<<" ";
	}cout<<"\n";
	for(int i=0;i<=n;i++) vis[i]=0;
}
signed main(){
	int T;
	cin>>T;
	memset(vis,0,sizeof(vis));
	while(T--) sol();
}

```

---

## 作者：reinforest (赞：0)

有些排列的题目都和图论中的环相关，可以把这道题作为一个例题。

对于每一步的 $cur$，我们令下一步的 $cur=p_{cur}$，那么你最后都会走出若干个环。这是一个关于排列的小性质吧。

比如说，给你一个排列 $p=[3,1,2,4,5]$。

如果 $cur=1$，那么我们会走到 $cur=3,2$，然后回到 $1$。

如果 $cur=5$，那么我们会走到 $cur=4$，然后回到 $5$。

这个性质反过来也是成立的。

现在我们排列中有些数字是空缺的，补全的方式只能是令 $p_i \leftarrow i$。

如果有些数字是空缺的，那么这个数字**所在的环**都会受到影响，那么需要把这个环上的所有数字都需要进行以上操作。如果不是，那么这个排列是不满足以上性质的。

那么这道题的做法就一目了然了。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
constexpr ll maxn=1e5+5;
bool vis[maxn];
ll T,n,p[maxn],d[maxn];
void work(){
	cin>>n;
	for(int i=1;i<=n;i++){
		vis[i]=0;
	}
	for(int i=1;i<=n;i++){
		cin>>p[i];
	}
	ll tot=0;
	for(int i=1;i<=n;i++){
		cin>>d[i];
		ll cur=p[d[i]];
		while(!vis[cur]){
			vis[cur]=true;
			tot++;
			cur=p[cur];
		}
		cout<<tot<<" ";
	}
	cout<<"\n";
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		work();
	}
	return 0;
}
```

---

## 作者：AstaVenti_ (赞：0)

# $\mathbf{0x00}$ 启

蒟蒻的第 $\color{red}\mathbf{57}$ 篇题解。

# $\mathbf{0x01}$ 承

按照 $d$ 数组的顺序，依次将一个 $n$ 的排列中的 $p_{d_1},p_{d_2},\cdots,p_{d_n}$ 变成 $0$。每有一个数变成 $0$，计算为了让它重新变成一个排列所需要把 $p_i$ 变成 $i$ 的最小次数。

# $\mathbf{0x02}$ 转

我们简单模拟一下，可以发现如果数组中的一个数变成了 $i$ 且 $i$ 原先就在数组的第 $j$ 个数出现过，则一定要把 $p_j$ 变成 $j$。

因此我们可以考虑建图。对于每一个 $i\in\{1,2,\cdots,n\}$，看 $d_i$ 是否被标记过。如果没有。则从 $i$ 开始一次搜索 $p_i,p_{p_i},p_{p_{p_i}}\cdots$ 直到有一个数被标记过，最后输出访问了几个数即可。

# $\mathbf{0x03}$ 合


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,n,ans;
vector<ll>a,d;
vector<bool>vis;
void f(ll x){
	ans++,vis[x]=1;
	if(!vis[a[x]])f(a[x]);
}
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		a.resize(n+1),d.resize(n+1),vis.resize(n+1);
		vis.clear();
		for(ll i=1;i<=n;i++)cin>>a[i];
		for(ll i=1;i<=n;i++)cin>>d[i];
		ans=0;
		for(ll i=1;i<=n;i++){
			if(!vis[d[i]])f(d[i]);
			cout<<ans<<" ";
		}
		cout<<endl;	
	}
}
```

---

## 作者：lgzbgz (赞：0)

## 解法
不难看出这个问题可以很轻松的转化为图上问题，于是按照样例把图建出来就可以发现如果一个位置上的数被删了，与这个数在同一个连通块内的数都要调整，因此我们把所有的连通块求出来，然后再对于每一个 $d_i$ 找出 $d_i$ 所在的连通块，如果这个连通块没有被加过就把他加到答案上，否则就不加（很显然，如果一个连通块内的多个数都被删去了，这个连通块也只会对答案有一次贡献）。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 0x3f3f3f3f;
const int mod = 998244353;
const int mxn = 2e5+10;

#define read(xx) {\
	xx = 0;\
	long long ff = 1;\
	char cc = getchar();\
	while(cc < '0' || cc > '9'){\
		if(cc == '-') ff = -1;\
		cc = getchar();\
	}\
	while(cc >= '0' && cc <= '9'){\
		xx = (xx<<1) + (xx<<3) + (cc^48);\
		cc = getchar();\
	}\
	xx *= ff;\
}
inline void print(int x);
inline void write(int x, int opt = 3);

int n;
int p[mxn];
int d[mxn];

struct merry {
	int nxt, to;
} umy[mxn];
int head[mxn], cnt;
int sta[mxn], insta[mxn], top;
int dfn[mxn], low[mxn], inde;
int belong[mxn];
int out[mxn], tot[mxn];
int num;

inline void add(int nxt, int to){
	umy[++cnt].nxt = head[nxt];
	head[nxt] = cnt;
	umy[cnt].to = to;
}

inline void tarjan(int u){
	int to;
	dfn[u] = low[u] = ++inde;
	sta[++top] = u;
	insta[u] = 1;
	for(int i = head[u]; i; i = umy[i].nxt){
		to = umy[i].to;
		if(!dfn[to]){
			tarjan(to);
			low[u] = min(low[u], low[to]);
		}
		else if(insta[to]){
			low[u] = min(dfn[to], low[u]);
		}
	}
	if(dfn[u] == low[u]){
		num++; 
		do{
			to = sta[top--];
			belong[to] = num;
			insta[to] = 0;
			tot[num]++;
		}while (u != to);
	}
}

void init(){
	cnt = inde = top = num = 0;
	for(int i = 1; i <= n; i++){
		umy[i] = {0, 0};
		head[i] = insta[i] = dfn[i] = low[i] = belong[i] = out[i] = tot[i] = 0;
	}
}

void solve(){
	init();
	read(n);
	for(int i = 1; i <= n; i++){
		read(p[i]);
		if(p[i] != i){
			add(i, p[i]);
		}
	}
	for(int i = 1; i <= n; i++){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	bitset<mxn> check;
	int ans = 0; 
	for(int i = 1; i <= n; i++){
		read(d[i]);
		if(!check[belong[d[i]]]){
			ans += tot[belong[d[i]]];
			check[belong[d[i]]] = 1;
		}
		write(ans, 2);
	}
	putchar('\n');
}

/*
1 4
2 5
3 3
4 1
5 2
*/

signed main() {
//	freopen("1.in", "r", stdin);
//	freopen("1.out", "w", stdout);

	cin.tie(0);
	int T = 1;
	read(T);
	while(T--){
		solve();
	}
	
	return 0;
}


inline void print(int x){
	if(x < 0) x = -x, putchar('-');
	if(x < 10) putchar(x + '0');
	else print(x/10), putchar((x%10)+'0'); 
}
inline void write(int x, int opt){
	print(x);
	if(opt == 1){
		putchar('\n');
	}
	else if(opt == 2){
		putchar(' ');
	}
}
```

---

## 作者：Zskioaert1106 (赞：0)

题目传送门：[CF2086C Disappearing Permutation](https://www.luogu.com.cn/problem/CF2086C)

本题考察~~瞪眼~~ dfs。

当 $p_i$ 变为 $0$ 时，我们需要修改它为 $i$。此时如果原先值为 $i$ 的仍然存在，则需继续替换它。因而考虑深度优先搜索。

如果一个数组被替换了，则让 $ans$ 加 $1$。如果它已经被别的替换过了，那说明它和它接下来的所有应替换的 $p_i$ 都已经换过了，因而不用再次搜索。

于是我们使用 $f$ 数组记录是否搜索过每个值，如果有新遍历到的就说明这个地方在新的 $d_i$ 消失后开始需要被修改，则 $ans$ 加 $1$。

至于为什么可以这样剪枝呢？因为每个位置被修改后都是同一结果（$p_i \leftarrow i$）而且不会被什么操作还原，所以多次修改和一次修改并不会有什么区别。

```cpp
#include<iostream>
using namespace std;
const int N=100005;
int t,n,p[N],d[N],ans;
bool f[N];
void dfs(int i){
    if(!f[i]){//剪枝
        f[i]=1;
        ans++;
        dfs(p[i]);
    }
}
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++)f[i]=0;
    for(int i=1;i<=n;i++)cin>>p[i];
    for(int i=1;i<=n;i++){
        cin>>d[i];
        dfs(d[i]);
        cout<<ans<<' ';
    }
    cout<<'\n';
    ans=0;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
    while(t--)solve();
	return 0;
}
```

[AC on CF](https://codeforces.com/contest/2086/submission/314467097)。

---

