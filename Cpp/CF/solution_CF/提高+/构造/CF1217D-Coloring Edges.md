# Coloring Edges

## 题目描述

给定一个有 $n$ 个顶点和 $m$ 条有向边的有向图，图中没有自环和重边。

我们定义有向图的 $k$ 染色如下：你需要将每条边染成 $k$ 种颜色中的一种。如果不存在由同一种颜色的边组成的环，则称该 $k$ 染色是好的。

请你找到该有向图的一个好的 $k$ 染色，并且使 $k$ 尽可能小。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 5
1 2
1 3
3 4
2 4
1 4
```

### 输出

```
1
1 1 1 1 1 
```

## 样例 #2

### 输入

```
3 3
1 2
2 3
3 1
```

### 输出

```
2
1 1 2 
```

# 题解

## 作者：fishing_cat (赞：10)

### 题意
  [原题](https://codeforces.com/problemset/problem/1217/D)   
  给你一个有向图，给图染色，要求每个环至少有两种颜色，求最少使用颜色的数量。

  ### 分析  
* **情况一**     
  没有环，那最少使用颜色的数量就是 $1$。

* **情况二**      
  有环，那一种颜色就不行了。通过观察可以发现，一个环必须包含两种路径：由小编号点到大编号点的，由大编号点到小编号点的。不然就无法连成环，因为编号一直递减或递增只能构成链。所以有环时最少使用颜色的数量为 $2$。


 题目到这就已经做出一半了，~纯纯诈骗题~，判环我用的是[拓扑排序](https://oi-wiki.org/graph/topo/)。

剩下的就是要输出染色方案，可用方法就很多了。这就说一下我认为最好理解的~~最好写的~~。

**情况一**就全输出 $1$ 就好了；  
**情况二**按照前面提到的<一个环必须包含两种路径>的理解，将由小编号点到大编号点的路径染色 $1$，由大编号点到小编号点的路径染色 $2$，既可以保证每个环至少有两种颜色。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
void read(int &x){//快读
	x = 0;
	char c = getchar();
	int f = 0;
	for(;!isdigit(c);c = getchar())
		f |= c == '-';
	for(;isdigit(c);c = getchar())
		x = x*10 + (c ^ '0');
	if(f) x = -x;
}
vector<int>edge[10001];
int n,m,u,v,d[10001],ans[10001];
queue<int>q;
bool TopoSort(){//拓扑排序 判环
	int cnt = 0;
	for(int i=1;i<=n;i++){
		if(!d[i]){
			q.push(i);
			++cnt;
		}
	}
	while(!q.empty()){
		int x = q.front();
		q.pop();
		for(auto y:edge[x])
			if(--d[y]==0){
				q.push(y);
				++cnt;
			}
	}
	if(cnt==n)return 0;// 无环
	else return 1;// 有环
}
int main(){
	read(n); read(m);
	for(int i=1;i<=m;i++){
		read(u); read(v);
		if(u<v) 
			ans[i] = 1;// 由小编号点到大编号点的路径染色 1
		else ans[i] = 2;// 由大编号点到小编号点的路径染色 2
		edge[u].push_back(v);
		++d[v];
	}
	if(TopoSort() == 1){// 情况二
		puts("2");
		for(int i=1;i<=m;i++)
			printf("%d ",ans[i]);// 输出在读入时已经预处理好的染色方案
	}else {// 情况一
		puts("1");
		for(int i=1;i<=m;i++)
			printf("%d ",1); // 全输出 1
	}
	return 0;
}
```

**完结撒花！！！**

---

## 作者：vme50xiex2 (赞：9)

诈骗题。

首先如果图本身无环答案就是 $1$。

否则考虑如下构造：若 $u < v$ 则染黑色，否则染白色。

发现任意一个环必同时有黑色和白色，因为如果只有一种颜色则所有边都是从小到大或者所有边都是从大到小，根本不能构成环。

时间复杂度 $\mathcal{O(n)}$，$n$ 只开到 $5000$ 大概是诈骗。

$\mathcal{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e3 + 10;
struct Edge {
	int u, v;
} e[N];
int n, m, ind[N];
vector<int> G[N];
bool TopSort() {
	static int q[N], head = 0, tail = -1, cnt = 0;
	for(int i = 1; i <= n; ++i) if(!ind[i]) q[++tail] = i;
	while(head <= tail) {
		int u = q[head++]; ++cnt;
		for(int v : G[u]) if(--ind[v] == 0) q[++tail] = v;
	}
	return cnt == n;
}
int main() {
	//freopen("data.in", "r", stdin);
	//freopen("code.out", "w", stdout);
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	for(int i = 1; i <= m; ++i) {
		int u, v; cin >> u >> v; 
		++ind[v]; e[i] = {u, v}; G[u].push_back(v);
	}
	if(TopSort()) {
		cout << 1 << '\n';
		for(int i = 1; i <= m; ++i) cout << 1 << ' ';
	}
	else {
		cout << 2 << '\n';
		for(int i = 1; i <= m; ++i) cout << (e[i].u < e[i].v ? 1 : 2) << ' ';
	}
	return 0;
}
```

---

## 作者：Schwarzkopf_Henkal (赞：8)

这篇题解主要是来介绍知识点的。

主要是有向图中的DFS树和DFS森林。关于如何用DFS树证明只需要（最多）用两种颜色染色已经有题解证明过了，末尾可能会提一下。

在有向图从某个未进入过的点开始DFS时，会产生一个一个以该点为根的DFS“树”，这个树并不是严格意义上的树，因为它不仅有可能拥有超过n-1条边，而且可能出现环。树边，返祖边（前向边），横叉边，后向边是这棵树进行DFS时对具有不同性质的边进行分类时产生的概念。

树边的定义是：它是一条最平常的边，与普通树的边相类似（也就是，不指向一个兄弟，不指向一个祖先，不越级指向一个儿子）。

返祖边的定义是：从子孙节点指向祖先节点的边。

横叉边的定义是：指向兄弟节点，或其子树内的点的边。

后向边的定义是：指向一个子孙节点的边。（后向边确切定义其实不太重要，重要的是这些边的实现。）

《算法导论》中的实现包括：对于每个节点有一个编号vis[i]，其可能的值有0，1，2，分别对应“尚未被访问到”，“已经被访问到，但是其子树（儿子节点）尚未被访问完”，“已经被访问到，整棵子树都被访问完了”。对于一条边(u,v)，如果vis[v]==0，那么这条边是一条树边，显然的；如果vis[v]==1，那么说明，v在以u为根的子树内，这条边指向一个祖先节点，那么这条边是一条返祖边（前向边）；如果vis[v]==2，那么v已经在u的子树内了，这条边是一条后向边。

![](https://cdn.luogu.com.cn/upload/image_hosting/6vgjsjl5.png)

>树边和后向边有时可以互换，如图中3-7和1-7。

应用：一个有向图可以被划分为多棵DFS树组成的DFS森林（非严格意义，树之间仍然有可能相互指向），而其中的每一个环，它必然由至少一条的返祖边与至少一条的树边组成（在没有自环的情况下）并且，一个返祖边边至少被包含在一个环里面。一条边只会是这四种边中的一种，不会出现某一条边同时是树边还是返祖边，当然，互换不算。横叉边和后向边都不能组成一个环，也就是，横叉边和后向边不会被包含在任意一个环里面。

相比拓扑排序，用DFS树找环实现更加方便，代码更加简短，不容易出错。同时还可以实现环的遍历，后面会稍微提一下（有什么用啊）。

这样，如果能使所有的树边染同一个颜色，所有的返祖边染另一个颜色，由于一个环至少包含一个树边一个返祖边，则所有的环都不会是相同颜色的。横叉边和后向边随便染一个颜色，反正它们不在任何一个环里面，但是默认染和树边一样的颜色（树边肯定存在，但是返祖边不一定存在。）

对于一个节点保存其所有的父亲节点的信息，对于一个返祖边，从它的起始点开始回溯，有多个父亲节点的边就分叉，直到终点。

就这样咯。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,vis[5005],ans[5005];
vector<pair<int,int> >to[5005];
void dfs(int p){
    vis[p]=1;
    for(int i=0;i<to[p].size();i++){
        if(vis[to[p][i].first]==0){//树边为1.
            dfs(to[p][i].first);
            ans[to[p][i].second]=1;
        }else if(vis[to[p][i].first]==1){//返祖边和横叉边，后向边为2
            ans[to[p][i].second]=2;
        }else ans[to[p][i].second]=1;
    }
    vis[p]=2;
}
int main(){
    cin>>n>>m;
    for(int i=1,x,y;i<=m;i++){
        cin>>x>>y;
        to[x].push_back(make_pair(y,i));
    }
    for(int i=1;i<=n;i++)
        if(vis[i]==0)dfs(i);
    bool flag=0;
    for(int i=1;i<m;i++)
        if(ans[i]!=ans[i+1])
            flag=1;
    if(flag){
        cout<<"2\n";
        for(int i=1;i<=m;i++)
            cout<<ans[i]<<" ";
    }else {
        cout<<"1\n";
        for(int i=1;i<=m;i++)
            cout<<"1 ";
    }
}
```

I'm Schwarzkopf Henkal.

---

## 作者：installb (赞：7)

挺有意思的一道题。  

首先如果没有环，那么一种颜色染完所有边，答案为 $1$。  
这里我直接用拓扑排序判断有没有环了。  

如果有环，一种颜色肯定是不行了。我们发现对于每一个环，可以视为从一个点出发，经过另一些点，再回到这个点的路径。  
这里我们给每一个点**任意赋予一个高度**（就是赋予一个权值..吧），同时保证所有点高度不同，这时候我们发现从一个点 $x$ 出发，走完第一步之后，要么是**到达了高度比原来更高的点**，要么**到达了高度比原来更低的点**，而最后我们要回到 $x$，如果第一步往高处走了，环上**总有至少一步需要往低处走**，不然一定无法回到 $x$。另一种情况同理。  

总而言之，每一个环**必定同时包含**走向更高高度的边和走向更低高度的边。

所以把高往低走的边染色为 $1$，低往高走的染色为 $2$。  

然后这题就做完了。  

高度怎么赋？随便怎么搞都可以，只要两两不同就行了。  
这里我为了方便直接用了**点的编号**。  

代码：  

```cpp
// 头文件省略了
using namespace std;
typedef long long LL;

vector <LL> G[200005];
LL vis[200005],in[200005] = {0};
LL cnt = 0,n,m;

void tp_sort(){
	queue <LL> q;
	for(LL i = 1;i <= n;i ++){
		if(!in[i]){
			cnt --;
			q.push(i);
		}
	}
	while(!q.empty()){
		LL u = q.front(); q.pop();
		for(LL i = 0;i < G[u].size();i ++){
			LL v = G[u][i]; in[v] --;
			if(!in[v]){
				cnt --;
				q.push(v);
			}
		}
	}
} // 拓扑排序

LL u[200005],v[200005],col[200005];

int main(){
	cin >> n >> m;
	for(LL i = 1;i <= m;i ++){
		cin >> u[i] >> v[i];
		G[u[i]].push_back(v[i]); in[v[i]] ++;
	}
	cnt = n; tp_sort();
	if(!cnt){
		cout << 1 << endl;
		for(LL i = 1;i <= m;i ++) cout << 1 << (i == m ? '\n' : ' ');
		return 0; // 判断无环的情况
	}
	
	for(LL i = 1;i <= m;i ++){
		if(v[i] < u[i]) col[i] = 2;
		if(v[i] > u[i]) col[i] = 1;
	} // 有环，直接根据点编号大小关系给边染色
	cout << 2 << endl;
	for(LL i = 1;i <= m;i ++) cout << col[i] << (i == m ? '\n' : ' ');
	return 0;
}
//
```

---

## 作者：luchenxi2012 (赞：3)

# CF1217D Coloring Edges 题解
### 题意
[题目传送门](https://www.luogu.com.cn/problem/CF1217D)

把一个有向图的边染色，使得它的每个环均包含至少两种颜色。
### 思路
可以证明，最多只需要两种颜色。

如果这个图无环，则只需要一种颜色。

否则，一种颜色肯定不行。

我们考虑任意一条边 $a\to b$。

若 $a\lt b$，我们把这条边染颜色 $1$。

否则，染颜色 $2$。

很显然，一个环是不可能只有 $1$ 颜色边或 $2$ 颜色边的。

所以只需要两种颜色。
### 代码
```cpp
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
struct edge {
	int l, r;
} e[5001]; // 存边1
vector <int> v[5001]; // 存边2
bool vis[5001];
int cnt[5001];
int main() {
	int n, m, x, y;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
		scanf("%d%d", &x, &y),
		v[x].push_back(y),
		e[i] = {x, y};
	queue <int> q; bool f = 1;
	for (int i = 1; i <= n; i++)
		q.push(i), vis[i] = 1;
	while (!q.empty()) { // 拓扑
		int x = q.front();
		q.pop(); vis[x] = 0;
		for (auto y : v[x])
			if (!vis[y]) {
				if (++cnt[y] >= n) // 有环
					{f = 0; break;}
				else
					q.push(y),
					vis[y] = 1;
			}
	}
	if (f) { // DAG图
		printf("1\n");
		while (m--)
			printf("1 ");
	} else {
		printf("2\n");
		for (int i = 1; i <= m; i++)
			if (e[i].l < e[i].r)
				printf("1 "); // 1型边
			else printf("2 "); // 2型边
	}
	return 0;
}
```

---

## 作者：Rty123 (赞：3)


[题目传送门](https://www.luogu.com.cn/problem/CF1217D)

### 题目大意
1. 给定一个有向图,给每一条边染色，对于任意一个环，使得这个环中至少有两种颜色
1. 使用最少的颜色完成目标，并给出一种方案

### 解题思路

看到这题我们可以考虑用 dfs 树。在 dfs 树中，一般有四种边：**树边**，就是普通树上的边；**返祖边**，指向自己祖先节点的边；**横叉边**指向自己兄弟节点的边；**前向边**，指向自己祖孙节点的边。

![](https://cdn.luogu.com.cn/upload/image_hosting/7d0zhzqx.png)

通过观察我们可以发现，在 dfs 树中，环中一定存在**树边**和**返祖边**，否则无法构成环。所以我们就可以把树边染成一种颜色，返祖边染成另一种颜色，其余的边随意染成一种颜色（一般是染成与树边相同的颜色），这样对于每一个环，其颜色都有两种。

现在的问题就是如何判断一条边是否为返祖边。这里我们可以借鉴 tarjan 中的思想，我们在 dfs 遍历的时候，用标记数组记录**走到这个点的路径经过的点**。遍历到 $\mathcal x$ 时，给 $\mathcal x$ 打上标记，遍历完 $\mathcal x$ 的子树后把标记取消。

遍历到 $\mathcal u$ 时，若 $\mathcal u$ 指向的点 $\mathcal v$ **从未被遍历过**，则这条边为树边，继续遍历 $\mathcal v$ 的子树；若 $\mathcal v$ **打过标记**，则 $\mathcal v$ 为走到 $\mathcal u$ 路径上的点，这条边为**返祖边**。

### 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,u,v,cnt,ans[10005],f[10005];
bool vis[10005],book[10005],ff;
struct P{
	int v,nxt,id;
}e[5005];
void insert(int u,int v,int k){
	cnt++;
	e[cnt].v=v;
	e[cnt].nxt=f[u];
	e[cnt].id=k;
	f[u]=cnt;
}
stack<int> q;
void dfs(int u){
	book[u]=1;
	vis[u]=1;
	for(int i=f[u];i;i=e[i].nxt){
		if(!book[e[i].v]){//若v从未被遍历过，则这条边为树边 
			ans[e[i].id]=1;
			dfs(e[i].v);
		}
		else if(vis[e[i].v]){//若v为到u路径上的点，则这条边为返祖边 
			ans[e[i].id]=2;
			ff=1;
		}
		else{//其余的边染成与树边相同的颜色 
			ans[e[i].id]=1;
		}
	}
	vis[u]=0;//u的子树遍历完成，取消标记 
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u>>v;
		insert(u,v,i);
	}
	for(int i=1;i<=n;i++){
		if(!book[i]){
			dfs(i);
		} 
	}
	if(ff==0){
		cout<<"1"<<endl;
		for(int i=1;i<=m;i++){
			cout<<"1 ";
		}
	}
	else{
		cout<<"2"<<endl;
		for(int i=1;i<=m;i++){
			cout<<ans[i]<<' ';
		}
	}
	return 0;
} 
```



---

## 作者：bsdsdb (赞：1)

题意：给一个有向图，对边染 $[1,k]$ 中的一种颜色，使得没有一个环上面的边全部同色。

如果没有环，$k=1$，否则 $k=2$，对于边 $(u,v)$，染颜色 $[u<v]+1$ 就行了。

写代码的时候想的比较复杂，写的是 $[\mathrm{dfn}_u<\mathrm{dfn}_v]+1$。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
// using namespace __gnu_pbds;
// tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>T;
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ldb;
//#define umap unordered_map
#define umap __gnu_pbds::cc_hash_table
#define mkp make_pair
#define prque priority_queue
#define emp emplace
#define empb emplace_back
#define empf emplace_front
#define invarg invalid_argument
#define cus_throw(msg) throw invarg(string(msg) + " at " + __FILE__ + ":" + to_string(__LINE__))
random_device rndv;
mt19937 rd(rndv());
const ll inf = 0x3f3f3f3f3f3f3f3fll;
const vector<ll> millerrabin = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
const double eps = 1e-8;
inline void enter(){putchar('\n');}
inline void space(){putchar(' ');}
inline ll readll(){ll ret=0,k=1;char c;do{c=getchar();if(c=='-'){k=-1;}}while(('0'>c)|('9'<c));do{ret=(ret<<3)+(ret<<1)+c-48;c=getchar();}while(('0'<=c)&(c<='9'));return ret*k;}
inline void read(ll&x){x=readll();}
inline char readchar(){char ret;do{ret=getchar();}while(ret<=32);return ret;}
inline void read(char&x){x=readchar();}
inline string readstr(){string ret;char c;do{c=getchar();}while(c<=32);do{ret+=c;c=getchar();}while((c>32)&(c!=EOF));return ret;}
inline void read(string&x){x=readstr();}
inline void write(ll x){if(!x){putchar('0');return;}if(x<0){putchar('-');x*=-1;}char op[20]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){putchar(op[cur--]);}}
//inline ostream& operator<<(ostream& out, __int128 x){if(!x){out<<"0";return out;}if(x<0){out<<"-";x*=-1;}char op[40]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){out<<op[cur--];}return out;}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const ll MAXN = 1e6 + 5;

ll n, m, ans[MAXN], k = 1, ind[MAXN], p[MAXN], dfn[MAXN], dfc = 0;
vector<pll> e[MAXN];
bool instk[MAXN], tp[MAXN];

ll fnd(ll x) {
	if (p[x] == x) {
		return x;
	}
	return p[x] = fnd(p[x]);
}
void srh(ll x) {
	dfn[x] = ++dfc;
	p[dfn[x]] = dfn[x];
	instk[dfn[x]] = 1;
	for (pll i : e[x]) {
		ll to = i.first;
		if (!dfn[to] || dfn[to] > dfn[x]) {
			ans[i.second] = 1;
			if (!dfn[to]) srh(to);
			p[dfn[x]] = min(p[dfn[x]], fnd(dfn[to]));
		} else if (/*instk[fnd(dfn[to])]*/1) {
			k = 2;
			ans[i.second] = 2;
			p[dfn[x]] = min(p[dfn[x]], fnd(dfn[to]));
		}
	}
}

int main() {
	read(n), read(m);
	for (ll i = 1; i <= m; ++i) {
		ll u, v;
		read(u), read(v);
		e[u].empb(v, i);
		++ind[v];
	}
	queue<ll> q;
	for (ll i = 1; i <= n; ++i) {
		if (!ind[i]) {
			q.emp(i);
		}
	}
	while (!q.empty()) {
		ll h = q.front();
		q.pop();
		tp[h] = 1;
		for (pll i : e[h]) {
			ll to = i.first;
			if (--ind[to] == 0) {
				q.emp(to);
			}
		}
	}
	for (ll i = 1; i <= n; ++i) {
		if (!tp[i]) {
			for (ll i = 1; i <= n; ++i) {
				if (!dfn[i]) {
					srh(i);
				}
			}
			write(k), enter();
			for (ll i = 1; i <= m; ++i) {
				write(ans[i]), space();
			}
			enter();
			return 0;
		}
	}
	write(1), enter();
	for (ll i = 1; i <= m; ++i) {
		write(1), space();
	}
	enter();
	return 0;
}

;             ;;;;;;;;          ;
;                   ;          ; ;
;                  ;          ;   ;
;                 ;          ;     ;
;                ;          ;;;;;;;;;
;               ;          ;         ;
;              ;          ;           ;
;;;;;;;;;;;   ;;;;;;;;   ;             ;

   ;                        ;
  ;                          ;
 ;                            ;
;                              ;
;                              ;
;                              ;
 ;                            ;
  ;         ;;          ;;   ;
   ;        ;;          ;;  ;
```

---

## 作者：Melo_DDD (赞：1)

我们考虑这样一件事：一个环中一定有由编号小的点连向编号大的点的边，同时一定有由编号大的点连向编号小的点的边，这样才可能构成环，不然整个图的整体方向就会是一定的。

所以要是有环，那么两种边染不同的颜色即可。

要是没环，那整张图染一个颜色即可。

判环使用拓扑排序，考虑到要是无环所有点一定会入队，但是有环环上的点一定不可能入队，所以统计入队个数是否等于点的总个数即可。
## 代码：

```cpp
#include <bits/stdc++.h>
#define f(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using namespace std ;
template < typename T > inline void read ( T &x ) {
	x = 0 ;
	bool flag (0) ;
	register char ch = getchar () ;
	while (! isdigit (ch)) {
		flag = ch  == '-' ;
		ch = getchar () ;
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48) ;
		ch = getchar () ;
	}
	flag ? x = -x : 0 ;
} 
const int N = 5007 ;
int n ,m ,head[N << 1] ,tot ,in[N] ,u[N] ,v[N] ;
struct edge {
	int to ,nxt ;
} e[N << 1] ;
bool flag (0) ;
namespace shin {
	inline void add (int u ,int v) {
		e[++ tot].nxt = head[u] ;
		head[u] = tot ;
		e[tot].to = v ;
		in[v] ++ ;
	}
	inline void topo () {
		queue < int > q ;
		int cnt (0) ;
		f (i ,1 ,n ,1) {
			if (! in[i]) {
				q.push (i) ;
				cnt ++ ;
			} 
		}
		while (! q.empty ()) {
			int cur = q.front () ;
			q.pop () ;
			for (int i = head[cur] ;i ;i = e[i].nxt) {
				int nex = e[i].to ;
				if (-- in[nex] == 0) {
					q.push (nex) ;
					cnt ++ ;
				}
			}
		}
		cnt == n ? flag = 1 : 0 ;
	}
}
int main () {
	read (n) ,read (m) ;
	f (i ,1 ,m ,1) {
		read (u[i]) ,read (v[i]) ;
		shin :: add (u[i] ,v[i]) ;
	}
	shin :: topo () ;
	if (flag) {
		puts ("1") ;
		f (i ,1 ,m ,1) {
			cout << "1 " ;
		}
	} 
	else {
		puts ("2") ;
		f (i ,1 ,m ,1) {
			if (u[i] < v[i]) {
				cout << "1 " ;
			} 
			else cout << "2 " ;
		}
	}
	cout << '\n' ;
	return 0 ;
}
```

---

## 作者：残阳如血 (赞：1)

### $\textbf{Description}$

给定一个 $n$ 个点，$m$ 条边的简单有向图。

要求给每一条边染色，使得没有一个环只有一个颜色。

最小化使用颜色的数量，并输出方案。

$n,m\le5000$。

### $\textbf{Soluiton 1}$

迷惑构造题。

考虑原图的 [`dfs` 树](https://oi-wiki.org/graph/scc/#dfs-%E7%94%9F%E6%88%90%E6%A0%91)。

![dfs 树示意图](https://oi-wiki.org/graph/images/dfs-tree.svg)

容易发现，在 `dfs` 树中，只有返祖边会构成一个环，如 $1\to2\to7\to1$。

故可以将返祖边的颜色设置为 $2$，其余边的颜色设置为 $1$。

> 细节：由于题目要求得到每条边的编号，所以邻接表中存储的应该是 `std::pair<int,int>`，第一维是 $v$，第二维是 $id$。

---

### $\textbf{Other Solution}$

- 给所有点标号，设编号小的点为 $a,b$，编号大的点为 $c,d$，则 $a\to c$ 和 $d\to b$ 的颜色不同。

- 拓扑排序，取出的所有边标颜色 $1$。

  当不存在入度为 $0$ 的点时，任取一个入度为 $1$ 的点，将其入边颜色标为 $2$。

### $\textbf{Code}$

```cpp
#include <vector>
#include <iostream>
const int N = 5e3 + 10;

int n, m, ans[N];
int vis[N], b;
/*
vis 的表示:
	0：没有访问过
	1：已经访问过了，且在处理其子树
	2：这个点及其子树都访问过了
*/
std::vector<std::pair<int, int>> g[N];
// first:v second:id

void dfs(int u) {
	vis[u] = 1;
	for (auto [v, id] : g[u]) {
		if (vis[v] == 0) ans[id] = 1, dfs(v);
		else if (vis[v] == 1) ans[id] = 2, b = true;
		else ans[id] = 1;
	}
	vis[u] = 2;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> n >> m;
	for (int i = 0, u, v; i < m; ++i) {
		std::cin >> u >> v;
		g[u].push_back({v, i});
	}
	
	for (int i = 1; i <= n; ++i)
		if (vis[i] == 0) dfs(i);

	std::cout << b + 1 << std::endl;
	for (int i = 0; i < m; ++i)
		std::cout << ans[i] << ' ';
	std::cout << std::endl;

	return 0;
}
```

---

## 作者：sgl654321 (赞：1)

### 题目大意
- 给定一个有向图，对边染色，使得对于任意一个环，都至少有两种颜色。
- 询问颜色至少需要几种，并给出染色方案。

### 解题思路
一开始想的是 Tarjan 缩点算法，后来发现假掉了。原因是把强连通分量缩成一个点之后，该强连通分量内部仍然难以处理。

我们从头开始考虑。考虑一个有向图的 dfs 树。
![](https://cdn.luogu.com.cn/upload/image_hosting/a4e90efg.png)


这里的黑色边被称之为**树边**，因为这些边组成了 dfs 树。红色的边是**返祖边**，因为这种边是从一个节点指向它的祖先节点的。而绿色的边称之为**前向边**，蓝色的边称之为**横叉边**，这两种边跟解这一题关系不大。

考虑有向图的环是如何产生的。

容易发现，一个环一定是由**几条非返祖边**和**一条返祖边**构成的。

我们考虑把返祖边染成颜色 $2$，其他边染成颜色 $1$。这样对于每一个环，都一定有 $1,2$ 两种颜色了。

### 代码实现细节

如何判断一条边是不是返祖边？（学过 Tarjan 的同学可以跳过这一部分）

我们在 dfs 遍历的时候，记录下走到这个点的路径经过的点。遍历到点 $x$ 时，我们可以把 $x$ 放入一个栈内，直至 $x$ 的子树遍历完毕，就把 $x$ 从栈中弹出。

这时，如果 $x$ 指向了一个点 $y$，$y$ 在栈中。由于栈中的点就是到达 $x$ 的路径上的点，所以这条边 $(x,y)$ 就一定是一条返祖边。

另外，由于不一定一次遍历就遍历完整张图，我们需要在遍历时，记录下该点是否遍历过。
### 参考代码
```cpp
#include<bits/stdc++.h>
#define maxn 5010
#define maxm 5010
using namespace std;
long long n,m,x,y,kk,poi[maxn],nex[maxm],v[maxm];
long long ans[maxm],dfn[maxn],cnt;
bool insta[maxn];
bool flag;
void add_edge(long long x,long long y){
	kk++;v[kk]=y;nex[kk]=poi[x];poi[x]=kk;
}
void dfs(long long x){
	cnt++;dfn[x]=cnt;//dfn 表示该点是否遍历过
	insta[x]=1;
	long long save=poi[x];
	while(save>0){
		if(!dfn[v[save]]){//未遍历过，树边
			dfs(v[save]);
			ans[save]=1;
		}else if(insta[v[save]]){//返祖边
			flag=1;
			ans[save]=2;	
		}else ans[save]=1;//其他的边，不管他
		save=nex[save];
	}
	insta[x]=0;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>x>>y;
		add_edge(x,y);
	} 
	for(int i=1;i<=n;i++)
		if(!dfn[i])dfs(i);
	if(!flag){
		cout<<1<<endl;
		for(int i=1;i<=m;i++)
			cout<<ans[i]<<" ";
		cout<<endl;
	}else{
		cout<<2<<endl;
		for(int i=1;i<=m;i++)
			cout<<ans[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：_soul_ (赞：1)

之前的题解中都没有解释过本题为什么所需要染得颜色不是1种就是2种这个结论。

我在这里给出证明：
  首先我们可以考虑dfs树，在有向图中，只存在三种边，返祖边，树边，横叉边， 然而横叉边在有向图中并不能构成一个环，所以在有向图中，一个环必然同时包含返祖边和树边两种边，那么我们只需要将所有的返祖边染成1，树边染成2，那么一个换中就肯定不止一种颜色了。
  
  证明完了这个结论，这题就十分简单了，只需要判断原图中是否存在环，如果有环则需要两种颜色，再将树边染1，返祖边染2，横叉边无所谓，如果没环，则直接输出1，并且将所有边染1即可。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define MAX_N 5010
using namespace std;
struct edge {
	int v,w,next;
} e[MAX_N<<1];
int eid,p[MAX_N<<1];
void insert(int u,int v,int w) {
	e[++eid]= {v,w,p[u]};
	p[u]=eid;
}
int ans[MAX_N];
bool vis[MAX_N],fa[MAX_N];
void dfs(int u) {
	vis[u]=1,fa[u]=1;
	for(register int i=p[u]; i; i=e[i].next) {
		int v=e[i].v;
		if(fa[v])
			ans[e[i].w]=2;
		else {
			ans[e[i].w]=1;
			if(!vis[v])
				dfs(v);
		}
	}
	fa[u]=0;
}
int n,m;
int main() {
	scanf("%d%d",&n,&m);
	for(register int i=1; i<=m; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		insert(u,v,i);
	}
	for(register int i=1; i<=n; ++i)
		if(!vis[i])dfs(i);
	bool flag=0;
	for(register int i=2; i<=m; ++i)if(ans[i]!=ans[i-1])flag=1;
	cout<<flag+1<<endl;
	if(flag)
		for(register int i=1; i<=m; ++i)printf("%d ",ans[i]);
	else for(register int i=1; i<=m; ++i)printf("1 ");
	return 0;
}
```


---

## 作者：Fa_Nanf1204 (赞：0)

### 分析：
考虑通过 dfs 树找环，这里 dfs 树的基础知识就不介绍了，详见第一篇题解。

我们知道如果一棵 dfs 树有返祖边，那么说明就一定有环，根据题目的要求，我们需要给返祖边染上不同的颜色，同时也可以发现，只要给返祖边染上一种颜色其他边染上不同颜色，即可满足要求，即最多只需要 $2$ 种颜色，并且返祖边染不同颜色。
### Code:
```cpp
#include<bits/stdc++.h>
#define N 1000005 
using namespace std; 
int n,k,a[N];
int q_max[N],t_max,h_max=1;
int q_min[N],t_min,h_min=1;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<k;i++){
		while(t_min>=h_min and a[q_min[t_min]]>a[i]) t_min--;
		q_min[++t_min]=i;
	}
	for(int i=k;i<=n;i++){
		while(t_min>=h_min and a[q_min[t_min]]>a[i]) t_min--;
		q_min[++t_min]=i;
		while(t_min>=h_min and q_min[h_min]<=i-k) h_min++;
		cout<<a[q_min[h_min]]<<' '; 
	}
	cout<<'\n';
	for(int i=1;i<k;i++){
		while(t_max>=h_max and a[q_max[t_max]]<a[i]) t_max--;
		q_max[++t_max]=i;
	}
	for(int i=k;i<=n;i++){
		while(t_max>=h_max and a[q_max[t_max]]<a[i]) t_max--;
		q_max[++t_max]=i;
		while(t_max>=h_max and q_max[h_max]<=i-k) h_max++;
		cout<<a[q_max[h_max]]<<' '; 
	}
 	return 0;
} 
```

---

## 作者：Svemit (赞：0)

# Solution

[link](https://www.luogu.com.cn/problem/CF1217D)

一个经典结论是有向图中的任意一个环总能由一条生成树上的从祖先到儿子的链以及一条返祖边组成，正确性显然。

不妨将所有树边和横插边都染成黑色，返祖边染成白色，这样就可以保证任意一个环都有两种颜色了。

判断横插边和返祖边可以用栈来维护。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int N = 5e3 + 5;

int n, m;
vector<PII> e[N];
int ans[N];
bool st[N], ins[N];

void dfs(int u) {
	st[u] = true;
	ins[u] = true;
	for (auto [v, id] : e[u]) {
		if (!st[v]) {
			ans[id] = 1;
			dfs(v);
		}
		else {
			if (ins[v]) ans[id] = 2;
			else ans[id] = 1;
		}
	}
	ins[u] = false;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i ++) {
    	int u, v;
    	cin >> u >> v;
    	e[u].emplace_back(v, i);
    }
    for (int i = 1; i <= n; i ++) {
    	if (!st[i]) {
    		dfs(i);
    	}
    }
    cout << *max_element(ans + 1, ans + 1 + m) << '\n';
    for (int i = 1; i <= m; i ++) {
    	cout << ans[i] << ' ';
    }
    return 0;
}
```

---

## 作者：kingho11 (赞：0)

一道很有意思的构造题。

整理题意可得：

$1$、有一幅有 $n$ 个点，$m$ 条边的有向图。

$2$、我们需要对每一个边染色，要求一个环内的边的颜色不能相同。

接下来，我们来看一下样例。

### 样例 $1$

样例 $1$ 的图如图所示

![](https://cdn.luogu.com.cn/upload/image_hosting/5dz2jdqq.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

观察可得，这个样例中没有环，所以可以全部染同一个颜色。

### 样例 $2$

样例 $2$ 的图如图所示

![](https://cdn.luogu.com.cn/upload/image_hosting/kaqpreg4.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这个图中只有 $1$ 个环，所以只用染两种颜色就可以了。

解决完样例后，我们来讲讲怎么染色。

$1$、对于任意 $1$ 个环，至少会有一条从小到大的边和一条从大到小的边，例如样例 $2$ 点 $1$ 到点 $2$ 就是从小到大的边，点 $3$ 到点 $1$ 就是从大到小的边。

$2$、由此可得，一个环中的边只会有两种情况（从小到大和从大到小），所以我们可以分别给这两种情况的边染上不同的颜色，所以可以证明只需要两种颜色就可以把所有边染完。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5005;
vector <long long> v[N];
bool b1[N],flag=false;
struct uuu{
	long long u,v;
}a[N];
void dfs(long long u,long long o)
{
	if(flag==true)
	{
		return ;
	}
	for(long long i=0;i<v[u].size();i++)
	{
		long long x=v[u][i];
		if(x==o)
		{
			flag=true;
			return ;
		}
		if(b1[x]==false)
		{
			b1[x]=true;
			dfs(x,o);
		}
	}
}
int main()
{
	long long n,m;
	cin>>n>>m;
	long long u,v2;
	for(long long i=1;i<=m;i++)//存图
	{
		cin>>u>>v2;
		a[i].u=u,a[i].v=v2;
		v[u].push_back(v2);
	}
	for(long long i=1;i<=n;i++)//判是否有环
	{
		memset(b1,false,sizeof(b1));
		b1[i]=true;
		dfs(i,i);
		if(flag==true)
		{
			break; 
		}
	}
	if(flag==false)//没有环就可以只用1中颜色，全部输出1
	{
		cout<<"1\n";
		for(long long i=1;i<=m;i++)
		{
			cout<<1<<" ";
		}
		return 0;
	}
	cout<<"2\n";//否则就要用两种颜色
	for(long long i=1;i<=m;i++)
	{
		if(a[i].u<a[i].v)//从小到大的边染成2
		{
			cout<<2;
		}else//从大到小的边染成1，其实这个顺序是无所谓的，也可以从小到大然1，从大到小然2
		{
			cout<<1;
		}
		cout<<" ";
	}
}
```

---

## 作者：youngk (赞：0)

这道题首先有一个结论，就是有环的时候要两种色染色，无环时只要一种色染色，这个证明不妨讨论一下极限情况，所有的边都是无向边，呢么每两个点之间就可以形成一个环，也就必然这对单向边要染色成1和2，但是在这个图的情况下，即使都是被染成1和2两种颜色，其实因为1和2染色的方向不同，也可以分成两种边，呢么不妨考虑最小边覆盖，呢么一张图可以出现两种边，所以只需要两种颜色就可以构造完成要求

染色可以依靠dfs，当出现环的时候，就染成2，反之染成1

代码:

```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<set>
#define _USE_MATH_DEFINES
#include<math.h>
#include<queue>
#include<vector>
#include<limits.h>
#include<functional>
#include<stack>
typedef long long ll;
#pragma GCC optimize(2)
using namespace std;
inline void write(int x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
const int maxn = 2e5 + 10;
int color, deep, head[maxn], to[maxn], Next[maxn], col[maxn];
int cnt;
int n, m, ans;
int vis[maxn];
void add(int u, int v)
{
	to[++cnt] = v;
	Next[cnt] = head[u];
	head[u] = cnt;
}
void dfs(int u)
{
	vis[u] = 1;
	for (int i = head[u]; i; i = Next[i])
	{
		if (col[i])
			continue;
		int v = to[i];
		if (!vis[v])
			dfs(v);
		col[i] = 1;
		if (vis[v] == 1)
			col[i] = ans = 2;
	}
	vis[u] = 2;
}
signed main()
{
	n = read(), m = read();
	ans = 1;
	while (m--)
	{
		int x = read(), y = read();
		add(x, y);
	}
	for (int i = 1; i <= n; i++)
		if (!vis[i])
			dfs(i);
	write(ans);
	puts("");
	for (int i = 1; i <= cnt; i++)
		write(col[i]), putchar(' ');
	return 0;
}
```


---

