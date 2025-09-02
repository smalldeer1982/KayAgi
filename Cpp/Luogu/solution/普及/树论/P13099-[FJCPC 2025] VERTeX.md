# [FJCPC 2025] VERTeX

## 题目描述

给定一棵有 $n$ 个结点的树，结点依次以 $1, 2, \dots, n$ 标号。第 $i$（$1\leq i\leq n$）个结点有**正整数**权值 $b_i > 0$。对于连接结点 $u$ 与 $v$ 的树边，其边权为 $w_{uv} = b_u + b_v$。

现在给定树的形态与每条树边的边权，你需要判断是否存在满足条件的一组结点权值。若存在，则求出任意一组结点权值。

## 说明/提示

对于第一组样例，可以验证给出的权值满足条件。注意到 $w_{34} = b_3 + b_4 = 2$，因此 $b_3$ 与 $b_4$ 只能取 $1$，继而可以确定其他结点的权值。

对于第二组样例，注意到 $b_2 + b_3 = w_{23} = 9 = w_{12} + w_{34} = b_1 + b_2 + b_3 + b_4$，从而 $b_1 + b_4 = 0$，而这与 $b_1 > 0$ 且 $b_4 > 0$ 矛盾，因此不存在满足条件的结点权值。

## 样例 #1

### 输入

```
5
1 2 5
1 3 4
2 5 7
3 4 2```

### 输出

```
YES
3 2 1 1 5```

## 样例 #2

### 输入

```
4
1 2 5
2 3 9
3 4 4```

### 输出

```
NO```

# 题解

## 作者：WuMin4 (赞：4)

## 思路

![](https://cdn.luogu.com.cn/upload/image_hosting/d7iajdn5.png)

该图片与题目没有任何关系。

我们可以发现这是一道 $\text{Master} \ 14.7$ 的题目。因为边权 $w_{uv}=b_u+b_v$，所以当**确定了这棵树上一个点的权值后，整棵树的权值都将确定**，即所有其他点的权值都可以用这个点表示出来。点 $i$ 的权值 $b_i$ 一定是一个正整数，即 $b_i>0$，因此我们可以求出 $n$ 个不等式，从而确定这个点的取值范围。如果不等式组无解，则不存在合法权值，否则不等式组的任意一个合法解都可以作为该点权值。

假设点 $u$ 的权值被确认，$u$ 与 $v$ 有连边，则 $b_v=w_{uv}-b_u$，得出 $w_{uv}-b_u>0$，即 $b_u<w_{uv}$。若 $v$ 与 $x$ 有连边，则 $b_x=w_{vx}-b_v$，带入得到 $b_x=w_{vx}-w_{uv}+b_u$，即 $b_u>-(w_{vx}-w_{uv})$。以此类推通过 dfs 我们便可以得到所有的取值范围并求出一个解。

根据以上思路写出代码，点击提交按钮，初见便获得了 $101.0000\%$ 的理论值，但是我在机房，而不是在机厅。

至此，一锤定音。\
尘埃，已然落定。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
	int x,d;
};
int n,l,r,ans[200005];
vector<node> t[200005];
void dfs(int x,int fa,int nw,bool np){
	for(node v:t[x]){
		if(v.x==fa) continue;
		if(np==0) r=min(r,v.d-nw-1);
		else l=max(l,-(v.d-nw)+1);
		dfs(v.x,x,v.d-nw,!np);
	}
}
void qu(int x,int fa){
	for(node v:t[x]){
		if(v.x==fa) continue;
		ans[v.x]=v.d-ans[x];
		qu(v.x,x);
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(int x,y,d,i=1;i<n;i++){
		cin>>x>>y>>d;
		t[x].push_back({y,d});
		t[y].push_back({x,d});
	}
	l=1,r=1e9;
	dfs(1,0,0,0);
	if(l>r) cout<<"NO";
	else{
		ans[1]=l;
		qu(1,0);
		cout<<"YES"<<endl;
		for(int i=1;i<=n;i++)
			cout<<ans[i]<<" ";
	}
	return 0; 
}
```

---

## 作者：封禁用户 (赞：2)

队伍中第二道 AC 的题，第一道非签到题，由我提供。

### 题意
  给定一棵树，树边权为 $w_{u,v}$ 表示 $u$ 到 $v$ 之间的树边权。定义点权 $b_u$ 表示 $u$ 的点权，对于每个 $w_{u,v}$，都需满足 $w_{u,v} = b_u + b_v$。现给出所有的 $w_{u,v}$，要求构造一组 $b_u$ 满足上述的约束条件，若无论如何都无法满足，输出 ```NO```。

### 思路
显然，只要知道了一个点的点权，就可以递推出所有点的点权，即：已知 $b_u$，可得 $b_v=w_{u,v}-b_u$。那么只需要求出每个点权的取值范围就可以了，怎么做？树形 DP。

定义 $l_u$ 和 $r_u$ 表示点权的左右边界，即 $l_u \le b_u \le r_u$。由于 $b_u+b_v=w_{u,v}$，很显然，$b_u$ 越大，$b_v$ 越小，反过来亦是如此。那么就可以得到：
$$l_u=w_{u,v}-r_v$$
$$r_u=w_{u,v}-l_v$$

对于叶子结点，由于其没有子节点，故 $l_u=1,r_u=w_{u,v}-1$。

对于非叶子节点，由于有多条树边，可以得到多个取值范围，因此需要求重合的区间。得转换方程：
$$l_u \gets \max(l_u,w_{u,v}-r_v)$$
$$r_u \gets \min(r_u,w_{u,v}-l_v)$$

随后就得出了每个点权的取值范围，之后就就是判断是否无解。显然，对于取值范围，若要有解，就必须满足 $l_u\le r_u$，对于树边权，必须满足 $w_{u,v} \le r_u + r_v$，若不满足，就是无解。

若有解，则直接令一个节点的点权为取值范围的任意值然后遍历一下图，由 $b_v=w_{u,v}-b_u$ 递推出其余所有节点的点权就行了，深搜广搜都可以。

总复杂度是 $O(n)$，可以通过。

这道题就做完了。

### 代码

```cpp
#include<bits/stdc++.h>
//#define int long long
#define in(a) a = read_int()
using namespace std;
const int N = 2e5 + 5;
const int inf = INT_MAX;
inline int read_int() {
	int x = 0;
	char ch = getchar();
	bool f = 0;
	while('9' < ch || ch < '0') f |= ch == '-' , ch = getchar();
	while('0' <= ch && ch <= '9') x = (x << 3) + (x << 1) + ch - '0' , ch = getchar();
	return f ? -x : x;
}
struct Edge {
	int n , v , w;
} edge[N << 1];
int head[N] , eid;
void eadd(int u , int v , int w) {
	edge[++ eid].n = head[u] , edge[eid].v = v , edge[head[u] = eid].w = w;
}
int n;
int l[N] , r[N] , ans[N];
void dfs(int u , int fa) { // 树形 DP 部分 
	l[u] = 1; // 初始化左边界 
	for(int i = head[u] ; i ; i = edge[i].n) {
		int v = edge[i].v , w = edge[i].w;
		if(v != fa) {
			r[v] = w - 1; // 初始化右边界 
			dfs(v , u);
			r[u] = min(r[u] , w - l[v]); // 转移过程 
			l[u] = max(l[u] , w - r[v]);
		}
	}
}
queue<int>q;
signed main() {
	in(n);
	for(int i = 1 ; i < n ; i ++) {
		int u , v , w;
		in(u) , in(v) , in(w);
		eadd(u , v , w) , eadd(v , u , w);
	}
	r[1] = 1e9; // 初始化根节点的右边界 
	dfs(1 , 0); // 求每个点权的取值范围 
	for(int i = 1 ; i <= eid ; i += 2) { // 判无解部分 
		int u = edge[i].v , v = edge[i + 1].v , w = edge[i].w;
		if(r[u] + r[v] < w || l[u] > r[u] || l[v] > r[v]) { 
            cout<<"NO";
			return 0;
		}
	}
	ans[1] = l[1]; // 若有解，根节点点权取左边界 
	q.push(1);
	while(!q.empty()) { // 广搜部分 
		int u = q.front();
		q.pop();
		for(int i = head[u] ; i ; i = edge[i].n) {
			int v = edge[i].v , w = edge[i].w;
			if(ans[v]) continue;
			ans[v] = w - ans[u]; // 递推求解 
			q.push(v);
		}
	}
	cout<<"YES\n"; // 打印答案 
	for(int i = 1 ; i <= n ; i ++) cout<<ans[i]<<' ';
	return 0;
}
```

---

## 作者：StormWhip (赞：2)

## 思路
显然所有结点都和 $1$ 号结点联通，那么不妨设 $1$ 号结点的权值为 $x$。那么若一条边权为 $w$ 的边连接了两个结点 $u$ 和 $v$，且 $u$ 的权值为 $k+px$，则可得出 $v$ 的权值为 $w-k-px$。  
综上，用一个结构体维护以 $k+px$ 的形式维护每个结点的权值，再根据点权值域为 $(0,1\times 10^9]$ 解不等式，算出 $x$ 的取值范围。若有合法的值则任选一个计算所有结点的权值，没有则输出 `NO` 即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
struct edge
{
	int v,w;
};
struct node
{
	int k,p; 
}d[N];
int n,l=0,r=1e9+1,x;
bool vis[N];
vector <edge> G[N];
void Dfs(int u)
{
	vis[u]=1;
	for(int i=0;i<G[u].size();i++)
	{
		int v=G[u][i].v,w=G[u][i].w;
		if(vis[v]) continue;
		d[v].p=-d[u].p;
		d[v].k=w-d[u].k;
		Dfs(v);
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++) 
	{
		int u,v,w;
		cin>>u>>v>>w;
		G[u].push_back({v,w});
		G[v].push_back({u,w});
	}
	d[1]={0,1};
	Dfs(1);
	for(int i=1;i<=n;i++)
	{
		if(d[i].p==1) l=max(l,-d[i].k);
		else r=min(r,d[i].k);
	}
	if(r-l<=1) {cout<<"NO\n";return 0;}
	x=l+1;
	cout<<"YES\n";
	for(int i=1;i<=n;i++) cout<<d[i].p*x+d[i].k<<" ";
	cout<<"\n";
	return 0;
}
```

---

## 作者：hlb44 (赞：1)

口胡一下：

我们可以使用邻接表来存储本题的树，记录每个节点的邻居及对应边权。

我们用 BFS 来遍历树，节点 $1$ 为起点，设其权值为 $x$，推导出其他节点的权值表达式 $b_i=k_i \times x + d_i$。

我们在 BFS 过程中，若发现同一节点的权值表达式不一致，判定为无解，直接输出返回。

后面我们可以根据权值表达式，计算 $x$ 的上下界，若存在有效 $x$，输出对应的节点权值；否则，输出 NO。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define fo(i,begin,end) for(int i=begin;i<=end;++i)
#define of(i,begin,end) for(int i=begin;i>=end;--i)
#define fos(i,begin,end,ADD) for(int i=min(begin,end);i<=max(begin,end);i+=ADD)
#define ofs(i,begin,end,ADD) for(int i=max(begin,end);i>=min(begin,end);i-=ADD)
#define debug(val) cout<<#val<<':'<<(val)<<'\n'
#define debug_1(name,i,x) cout<<#name<<"["<<i<<"]:"<<x<<'\n';
#define debug_2(name,i,j,x) cout<<#name<<"["<<i<<"]["<<j<<"]:"<<x<<"\n";
#define ll long long
#define ull unsigned long long
const ll INF=1e18;
const ll MAX_B=1e9;
int n;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	if(n==1) {
		cout<<"YES\n1\n";
		return 0;
	}
	// 构建邻接表存储树：adj[u]存储与u相连的(节点,边权)对
	vector<vector<pair<int, int>>> adj(n + 1);
	fo(i,0,n-2) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].emplace_back(v, w);
		adj[v].emplace_back(u, w);
	}
	vector<ll> k(n+1);               // 存储节点权值表达式中x的系数(1或-1)
	vector<ll> d(n+1);               // 存储节点权值表达式中的常数项
	vector<bool> visited(n+1,false); // 标记节点是否已访问
	queue<int> q;                    // 遍历树
	q.push(1);                       // 从节点1开始遍历
	visited[1] = true;
	k[1] = 1;                        // 节点1的权值表达式：b1 = 1*x + 0
	d[1] = 0;
	bool possible = true;            // 是否存在合法权值
	while (!q.empty() && possible) {
		int u = q.front();
		q.pop();
		// 遍历u的所有邻边
		for (auto& edge : adj[u]) {
			int v = edge.first;  // 邻接节点
			int w = edge.second; // 边权
			// 根据u的表达式推导v的表达式：b_u + b_v = w → b_v = w - b_u
			ll expected_k = -k[u];  // v的系数为u系数的相反数
			ll expected_d = w - d[u];// v的常数项为边权减u的常数项
			if (!visited[v]) {      // 若v未访问，记录其表达式并加入队列
				visited[v] = true;
				k[v] = expected_k;
				d[v] = expected_d;
				q.push(v);
			} else {                // 若v已访问，检查表达式是否矛盾
				if (k[v] != expected_k || d[v] != expected_d) {
					possible = false; // 表达式矛盾，标记为不可能
					break;
				}
			}
		}
	}
	if (!possible) {
		cout << "NO\n";
		return 0;
	}
	// 检查所有节点是否都被访问
	fo(i,1,n) {
		if (!visited[i]) {
			cout << "NO\n";
			return 0;
		}
	}
	ll lower = -INF;              // x的下界
	ll upper = INF;               // x的上界
	fo(i,1,n) {                   // 每个节点对x的约束范围
		ll cl, cu;
		if (k[i] == 1) {           // 若节点i的权值为b_i = x + d[i]
			cl = (-d[i]) + 1;      // 保证b_i > 0 → x + d[i] ≥ 1 → x ≥ -d[i] + 1
			cu = MAX_B - d[i];     // 保证b_i ≤ MAX_B → x + d[i] ≤ MAX_B → x ≤ MAX_B - d[i]
		} else {                   // 若节点i的权值为b_i = -x + d[i]
			cl = d[i] - MAX_B;     // 保证b_i ≤ MAX_B → -x + d[i] ≤ MAX_B → x ≥ d[i] - MAX_B
			cu = d[i] - 1;         // 保证b_i > 0 → -x + d[i] ≥ 1 → x ≤ d[i] - 1
		}
		lower = max(lower, cl);    // 更新x的下界（取最严格约束）
		upper = min(upper, cu);    // 更新x的上界（取最严格约束）
	}
	lower = max(lower, 1LL);      // x本身需为正整数（因b1 = x > 0）
	upper = min(upper, MAX_B);    // x不能超过MAX_B（避免b1超出范围）
	if (lower > upper) {          // 若上下界矛盾，输出NO
		cout << "NO\n";
		return 0;
	}
	ll x = lower;                 // 取最小合法x值
	vector<ll> b(n + 1);          // 计算所有节点的权值
	fo(i,1,n) {
		b[i] = k[i] * x + d[i];
	}
	// 输出结果
	cout << "YES\n";
	fo(i,1,n) {
		cout << b[i] << " ";
	}
	cout << "\n";
	return 0;
}
```

---

## 作者：meihua (赞：1)

# 题目传送门[P13099](https://www.luogu.com.cn/problem/P13099)  
## 思路  
在我们测试数据时，容易发现：  
1. 一边 $w_{uv}$ 的两端点 $u , v$，满足 $w_{uv} = b_u + b_v$。如果 $b_u$ 加 $k$，则 $b_v$ 减 $k$。  
2. 如果只满足 $w_{uv} = b_u + b_v$ 的情况下，只需确定一个点的点权，即可推出整张图的点权。
  
基于第 **1** 点，我们可以把整张图的点分为黑白两种，使得相连两点的颜色不同。  

易得结论 **A**，满足 $w_{uv} = b_u + b_v$ 的情况下，如果有一点 $u$ 的点权 $b_u$ 加整数 $k$，则与 $u$ 同色的点的点权都加 $k$，异色的点的点权都减 $k$。

基于第 **2** 点，我们可以取任意一点（如第 $1$ 个点），使它的点权为任意值（如 $1$），推出整张图的点权，记录黑白两种点各自点权的最小值 $mn_0,mn_1$。  

由结论 **A** 可得， $mn_0 + mn_1$ 为定值。若可以使 $mn_0,mn_1$ 都为正数，则存在其方案，否则则不存在其方案。  

最后构造可以让 $mn_0 + x = 1$，所有黑点都加 $x$，所有白点都减 $x$。 
## 代码实现:

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int u,v,w;
int mn0=INT_MAX,mn1=INT_MAX;
vector<pair<int,int> >e[200005];
int dian[200005];
bool flag[200005],_01[200005];

void dfs(int k,int wi,bool is01){
	if(flag[k]) return ;
	flag[k]=1;
	dian[k]=wi;
	_01[k]=is01;
	if(!is01) mn0=min(mn0,wi);
	else mn1=min(mn1,wi);
	int len=e[k].size(); 
	for(int i=0;i<len;++i){
		if(flag[e[k][i].first]) continue;
		dfs(e[k][i].first,e[k][i].second-wi,!is01); 
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<n;++i){
		cin>>u>>v>>w;
		e[u].push_back(make_pair(v,w));
		e[v].push_back(make_pair(u,w));
	}
	dfs(1,1,0);
	if(mn0+mn1>=2){
		cout<<"YES\n";
		for(int i=1;i<=n;++i){
			if(!_01[i]){
				cout<<dian[i]+(1-mn0)<<" ";
			}else{
				cout<<dian[i]-(1-mn0)<<" ";
			}
		}
	}else{
		cout<<"NO";
	}
	return 0;
} 
```
点个赞吧(づ￣ 3￣)づ

---

## 作者：NTT__int128 (赞：1)

很简单吧。

令 $1$ 号结点的 $b_1$ 为 $x$，则每个结点 $i$ 的 $b_i$ 都可以表示为 $ax+b$（显然，$a=\pm1$）。

由于每个 $b_i$ 为正整数，可以求出 $x$ 的范围。

如果 $x$ 没有整数解，输出 `NO`。

否则，在区间内随便取一个 $x$，带入即可。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,x,y,z;
struct node{
	int a,b;// ax+b
}a[N];
vector<pair<int,int>>v[N];
int up,lw=1e9;
void dfs(int u,int f){
	if(a[u].a==1)up=max(up,-a[u].b);
	else lw=min(lw,a[u].b);
	for(pair<int,int>to:v[u])
		if(to.first!=f){
			a[to.first]={-a[u].a,to.second-a[u].b};
			dfs(to.first,u);
		}
}
signed main(){
	cin>>n;
	for(int i=1;i<n;++i)cin>>x>>y>>z,v[x].push_back({y,z}),v[y].push_back({x,z});
	a[1]={1,0};
	dfs(1,0);
	if(up+1>=lw){
		cout<<"NO";
		return 0;
	}
	cout<<"YES\n";
	for(int i=1;i<=n;i++)cout<<a[i].a*(up+1)+a[i].b<<' ';
	return 0;
}
```

---

## 作者：nbhs23a28 (赞：1)

省流：简单图上代数（一元一次不等式）水题。

由于本题约束构成一棵树，故不存在相互矛盾的，唯一总约束便是正整数。不妨设 $b_1$ 为 $a$，则可导得其他数的关于 $a$ 的代数式，形成这代数式 $>0$ 的不等式，解这由 $n-1$ 个一元一次不等式构成的不等式组即可。

---

## 作者：swate114514 (赞：1)

我们从结点 $1$ 开始，设 $b_1 = x$，其中 $x$ 是一个待定的变量。由于树是连通的，我们可以通过边的关系逐步表示其他结点的权值 $b_i$ 为关于 $x$ 的线性表达式 $a_i x + c_i$，其中 $a_i$ 和 $c_i$ 是常数。具体来说，对于每条边 $(u, v)$，有 $b_u + b_v = w_{uv}$。如果 $b_u$ 已经表示为 $a_u x + c_u$，那么 $b_v$ 可以表示为 $w_{uv} - b_u = -a_u x + (w_{uv} - c_u)$。因此，$a_v = -a_u$，$c_v = w_{uv} - c_u$。

在遍历树的过程中，可能会遇到以下两种情况：

1. 如果某个结点 $v$ 已经被表示为 $a_v' x + c_v'$，而现在又需要表示为 $-a_u x + (w_{uv} - c_u)$，那么必须满足 $-a_u = a_v'$ 且 $w_{uv} - c_u = c_v'$。如果不满足，则说明无解。

2. 如果在某个时刻，我们得到两个关于 $x$ 的线性方程 $a_i x + c_i = a_j x + c_j$ 且 $a_i \neq a_j$，那么可以解出 $x = \frac{c_j - c_i}{a_i - a_j}$。此时需要验证 $x$ 是否为整数，并且代入后所有 $b_i$ 是否为正整数。

如果遍历完整棵树后没有发现矛盾且没有解出具体的 $x$，那么我们需要找到 $x$ 的取值范围，使得所有 $b_i = a_i x + c_i > 0$。具体来说，如果 $a_i = 1$，则 $x > -c_i$；如果 $a_i = -1$，则 $x < c_i$。

综合所有不等式，可以得到 $x$ 的取值范围 $[L, R]$，其中 $L$ 是所有 $-c_i$（对应 $a_i = 1$）的最大值，$R$ 是所有 $c_i$（对应 $a_i = -1$）的最小值。如果 $L \leq R$，则可以选择 $x = L$（或其他合法值）作为解；否则无解。

---

代码不放了。

---

## 作者：Gon_Tata (赞：0)

# P13099 [FJCPC 2025] VERTeX 题解
[题目传送门](https://www.luogu.com.cn/problem/P13099)\
这里提供一种~~大常数~~无脑做法。\
我们注意到每一条边限定其相邻两个节点。
在 $N-1$ 条边全都给出后，各节点间的代数关系应都能确定下来。\
此时我们可以设 $1$ 号节点的权值为 $k$，即可用 $k$ 表示出所有节点的权值。\
对于样例 $2$ 即有如下图的表示：

![alt text](https://cdn.luogu.com.cn/upload/image_hosting/gbx3cavs.png)

我们注意到所有节点的权值可分为 $k+b (b \in \mathbb{R})$ 与 $-k+b (b \in \mathbb{R})$ 两种表示，因此我们将其分为两个集合 $S_0=\{x \mid x=-k+b\}$ 与 $S_1=\{x \mid x=k+b\}$ 
并定义：

$$
\begin{cases}
l_0=\min \limits_{x \in S_0} (x+k)\\
l_1=\min \limits_{x \in S_1} (x-k)\\
r_0=\max \limits_{x \in S_0} (x+k)\\
r_1=\max \limits_{x \in S_1} (x-k)
\end{cases}
$$
~~（其实就是取了常数部分）~~
易得 $k$ 的取值合法当且仅当满足：

$$
\begin{cases}
l_0-k>0\\
l_1+k>0\\
r_0-k<inf\\
r_1+k<inf
\end{cases}
$$

化简后即为：
$$ \max(-l_1,r_0-inf) < k < \min(l_0,inf-r_1) $$
最后输出时钦定一个合法的 $k$ 值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
const int inf=1e9;
int n,k[2][N],l0=0x3f3f3f3f,l1=0x3f3f3f3f,r0=-0x3f3f3f3f,r1=-0x3f3f3f3f,kl,kr,kk;
vector<pair<int,int>> s[N];
pair<bool,int> o[N];
void dfs(int x,int fa){
	for(auto p:s[x]){
		if(p.first==fa) continue;
		bool opt=o[x].first^1;
		o[p.first].first=opt;
		o[p.first].second=p.second-o[x].second;
		k[opt][++k[opt][0]]=o[p.first].second;
		dfs(p.first,x);
	}
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
	cin>>n;
	for(int i=1,u,v,w;i<n;i++){
		cin>>u>>v>>w;
		s[u].push_back(make_pair(v,w));
		s[v].push_back(make_pair(u,w));
	}
	o[1].first=1;
	dfs(1,0);
	for(int i=1;i<=k[0][0];i++) l0=min(l0,k[0][i]);
	for(int i=1;i<=k[1][0];i++) l1=min(l1,k[1][i]);
	for(int i=1;i<=k[0][0];i++) r0=max(r0,k[0][i]);
	for(int i=1;i<=k[1][0];i++) r1=max(r1,k[1][i]);
	kl=max(-l1,r0-inf);
	kr=min(l0,inf-r1);
	if((kl>=kr)||kr-1<=0){
		cout<<"NO";
		return 0;
	}
	cout<<"YES"<<'\n';
	kk=kr-1;
	for(int i=1;i<=n;i++) cout<<kk*(o[i].first ? 1 : -1)+o[i].second<<' ';
}
```

---

## 作者：Yumi_Anaxa_ (赞：0)

[**题面链接**](https://www.luogu.com.cn/problem/P13099)\
好像没人用 bfs 遍历……
## 思路
在这道题的树中，每条边的权值是其连接的两个结点的权值之和。\
所以这样就可以从任意结点开始，就可以通过边的权值来推出其他结点的权值了。
### 推导
#### 如果根的权值为 $x$：
- $b_1=x$。
- 在一条边 $u,v$ 中，结点 $u,v$ 权值的和就是边 $u,v$ 的边权。
- 再用 bfs 遍历整棵树即可。

结点的权值通过边权递推时，所有节点的权值必须为正整数，通过约束，题目就转化为解 $x$ 的不等式。\
**值得注意的是**，如果结点的深度是偶数，权值是 $x+b_i$；奇数情况下权值是 $b_i-x$。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll d[200005],c[200005];
int par[200005];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);cout.tie(0);
  int n;
  cin >> n;
  vector<pair<int, ll>> G[200005];
  for (int i = 0; i < n-1; i++){
    int u, v;
    ll w;
    cin >> u >> v >> w;
    G[u].push_back({v, w});
    G[v].push_back({u, w});
  }
  queue<int> q;
  d[1] = 0;
  q.push(1);
  while (!q.empty()){
    int u=q.front();
    q.pop();
    for (const pair<int,ll>&i:G[u]){
      int v = i.first;
      ll w = i.second;
      if (v == par[u])continue;
      par[v] = u;
      d[v] = d[u] + 1;
      c[v] = w - c[u];
      q.push(v);
    }
  }
  ll L0 = 1,R0=1e9;
  for (int i = 1; i <= n; i++){
    if (d[i] == -1){cout << "NO\n";return 0;}
    if (d[i] % 2 == 0){//深度为偶
      L0 = max(L0,1ll-c[i]);
      R0 = min(R0,1000000000ll-c[i]);
    }else{//深度为奇
      L0=max(L0,c[i]-1000000000ll);
      R0=min(R0,c[i]-1ll);
    }
  }
  if (L0 <= R0){
    cout<<"YES\n";
    for (int i = 1; i <= n; i++){
      ll bb;
      if (d[i] % 2 == 0)bb = L0 + c[i];
      else bb = c[i] - L0;
      cout << bb;
      if (i == n) cout << '\n';
      else cout << " ";
    }
  }
  else cout<<"NO\n";
  return 0;
}
```

---

## 作者：Arc0_FishyFool (赞：0)

一道不错的搜索题。

# 一、从常识出发

**这段显然的证明可以跳过。**\
我们显然知道：\
$a+b=(a-k)+(b+k)$\
这启示我们，**对于相邻的节点** $u$，$v$ 满足 $b_u+b_v=w_{uv}$，那么每当 $b_u$ 增加 $k$ 时，就会发生 $b_v$ 减少 $k$，其中 $k$ 为任意常数。\
同时，我们知道，在树上有时存在点 $u$ 同时为两条及以上的边的端点，对于这样的点 $u$，我们假设其与 $v_1$，$v_2$ 相连，且 $w_{uv_1}-w_{uv_2}=k$，那么：\
$(w_{uv_1}-b_u)-(w_{uv_2}-b_u)=k$\
即：\
$b_{v_1}-b_{v_2}=k$\
因此，我们发现**存在最多两组点组内两两之间相差不变，并且一组点增加一定值时，另一组点减少相同值**。这有什么用呢？

# 二、算法设计

我们将树上的点染成两种颜色，相邻的点不同颜色，并不妨设根节点为 $1$ 号节点，令其点权 $b_1$ 为 $1$。我们从根节点进行搜索，每次对节点 $u$ 的相邻节点染色并根据边权推导出其点权。\
同时，我们认为条件 $b_i\le 10^9$ 是**幽默**的，因为如果满足 $b_i\ge 1$ 与 $w_{uv}\le 10^9$，我们推出的点权一定满足 $b_i\le 10^9$。（什\
因此，我们只需考虑让解满足 $b_i\ge 1$。具体地，我们**存储每种颜色的最小点权值**，分别记为 $\min n_0$ 和 $\min n_1$，然后：

1. 如果 $1-\min( \min n_0, \min n_1)>\max( \min n_0, \min n_1)$，此时显然无解。
2. 如果 $\min n_0\ge 1$ 并且 $\min n_1\ge 1$，此时不需要特殊处理，直接输出所有点权值。
3. 否则 $\min n_0$ 和 $\min n_1$ 之间有且仅有一个小于 $1$，不妨令小于 $1$ 的为 $\min n_0$，记 $k=1- \min n_0$，将所有染为 $0$ 的点的权值加上 $k$，其余的减去 $k$，然后输出即可。

# 代码时间：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,head[229028],cnt;
struct edge{
	int to,nxt,wei;
}e[400040];
void adde(int u,int v,int w){
	e[++cnt].to=v;
	e[cnt].wei=w;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
bool col[229028];
int b[229028],minn[2];
void dfs(int u,int fa){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa) continue;
		col[v]=!col[u];
		b[v]=e[i].wei-b[u];
		minn[col[v]]=min(minn[col[v]],b[v]);
		dfs(v,u);
	}
}
int main(){
	memset(minn,0x3f,sizeof(minn));
	cin>>n;
	for(int i=1;i<n;++i){
		int u,v,w;
		cin>>u>>v>>w;
		adde(u,v,w);
		adde(v,u,w);
	}
	col[1]=false;
	b[1]=1;
	minn[0]=1;
	dfs(1,0);
	if(1-min(minn[0],minn[1])>max(minn[0],minn[1])-1){
		cout<<"NO";
		return 0;
	}
	cout<<"YES\n";
	int k=1-min(minn[0],minn[1]);
	if(minn[0]>1&&minn[1]>1){
		for(int i=1;i<=n;++i) cout<<b[i]<<" ";
		return 0;
	}
	bool flag=minn[1]<1;
	for(int i=1;i<=n;++i){
		if(flag==col[i]){
			cout<<b[i]+k<<" ";
		}
		else{
			cout<<b[i]-k<<" ";
		}
	}
	return 0;
}
```

---

## 作者：HPXXZYY (赞：0)

$\color{blue}{\texttt{[Analysis]}}$

如果可以知道一个点的点权的话，那么 $O(n)$ 的时间内我们可以把所有点的点权均求出来。

我们先考虑随机给点 $1$ 赋上一个权值，那么可以把所有的 $b_{u}^{1}$ 求出来。当然这未必是一个合法的方案。

显然，可能会存在某个或某些点 $v$，使得 $b_{v}^{1}\leq 0$。考虑换根，将其中一个 $v$ 作为新的根，把它的点权取值为 $1$，然后求出 $b_{u}^{2}$。当然 $b^{2}$ 中可能仍然存在小于等于 $0$ 的点，把它作为根继续迭代。

可以预见，如果无解，那么无论谁作为根都求不出合法解出来；如果有解，可以在有限次数的换根中得到合法的解。

由于 $n \leq 2 \times 10^{5}$，可以考虑进行 $100$ 次换根，如果都无法求出合法解，就认为不存在合法解。

$\color{blue}{\texttt{[Solution]}}$

1. 将 $1$ 作为原树的根节点。
2. 将根节点的点权赋值为 $1$。
3. 迭代求出所有点的点权。
4. 检查点权方案是否合法。如果合法，则跳转至步骤 $6$；否则找到一个点权小于等于 $0$ 的点 $v$。
5. 将 $v$ 作为新树的根。如果迭代次数超过限制，跳转至步骤 $7$；否则回到步骤 $2$。
6. 输出合法方案，跳至步骤 $8$。
7. 输出无解，跳至步骤 $8$。
8. 程序结束。

$\color{blue}{\text{Code}}$

```cpp
int val[N],n;
void dfs(int u,int Fa,int point){
	val[u]=point;
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==Fa) continue;
		
		dfs(v,u,e[i].val-point);
	}
}
int check(int rt){
	dfs(rt,0,1);
	for(int i=1;i<=n;i++)
		if (val[i]<=0) return i;
	return 0;
}

int main(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),val=read();
		add(u,v,val);add(v,u,val);
	}
	
	int rt=1;
	for(int i=1;i<=100;i++){
		int rec=check(rt);
		if (!rec){
			printf("YES\n");
			for(int i=1;i<=n;i++)
				printf("%d ",val[i]);
			return 0;
		}
		rt=rec;
	}
	
	printf("NO");
	
	return 0;
}
```

---

