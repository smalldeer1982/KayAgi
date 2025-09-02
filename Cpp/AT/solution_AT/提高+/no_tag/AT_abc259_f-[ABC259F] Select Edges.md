# [ABC259F] Select Edges

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc259/tasks/abc259_f

$ N $ 頂点の木が与えられます。 $ i\ =\ 1,\ 2,\ \ldots,\ N-1 $ について、$ i $ 番目の辺は頂点 $ u_i $ と頂点 $ v_i $ を結ぶ重み $ w_i $ の辺です。

$ N-1 $ 本の辺のうちのいくつか（ $ 0 $ 本または $ N-1 $ 本すべてでも良い）を選ぶことを考えます。 ただし、$ i\ =\ 1,\ 2,\ \ldots,\ N $ について、頂点 $ i $ に接続する辺は $ d_i $ 本までしか選べません。 選ぶ辺の重みの総和としてあり得る最大値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 3\ \times\ 10^5 $
- $ 1\ \leq\ u_i,\ v_i\ \leq\ N $
- $ -10^9\ \leq\ w_i\ \leq\ 10^9 $
- $ d_i $ は頂点 $ i $ の次数以下の非負整数
- 与えられるグラフは木である
- 入力はすべて整数

### Sample Explanation 1

$ 1,\ 2,\ 5,\ 6 $ 番目の辺を選ぶと、選ぶ辺の重みは $ 8\ +\ 9\ +\ 8\ +\ 3\ =\ 28 $ となります。これがあり得る最大値です。

## 样例 #1

### 输入

```
7
1 2 1 0 2 1 1
1 2 8
2 3 9
2 4 10
2 5 -3
5 6 8
5 7 3```

### 输出

```
28```

## 样例 #2

### 输入

```
20
0 2 0 1 2 1 0 0 3 0 1 1 1 1 0 0 3 0 1 2
4 9 583
4 6 -431
5 9 325
17 6 131
17 2 -520
2 16 696
5 7 662
17 15 845
7 8 307
13 7 849
9 19 242
20 6 909
7 11 -775
17 18 557
14 20 95
18 10 646
4 3 -168
1 3 -917
11 12 30```

### 输出

```
2184```

# 题解

## 作者：SSER_ZRQ (赞：6)

树形 dp:

$dp_{x,0}$ 选择 $x$ 与其父节点的边时其子树最大价值。

$dp_{x,1}$ 不选择 $x$ 与其父节点的边时其子树最大价值。

考虑怎么转移：

1. 背包：DP 选哪些边使得价值最大，复杂度 $O(n^2)$。
2. 贪心：先假设边都选，筛出删掉那些边使得损失最小。
- 对于儿子 $u$，他从选到不选价值变化为 $dp_{u,0}+w-dp_{u,1}$。
- 那么，我们将每个儿子价值变化度处理出来，排序后取最大的 $d$ 个即可。
- 复杂度 $O(n\log n)$。

---

## 作者：white_tiger_yyyy (赞：3)

很容易想到树形 dp。

考虑在有根树内，每个点都有两种状态：

1. 不选自己和父亲的边；
2. 要选自己和父亲的边。

那么单独对于子树内部而言，就要分两种情况：

1. 最多可以向 $d_i$ 个孩子连边，对应上述第一种情况，我们称之为 $f_i$；
2. 最多可以向 $d_i-1$ 个孩子连边，对应上述第二种情况，我们称之为 $dp_i$。

最基本的状态是不选自己和子树的连边，答案即为 $\sum\limits_{j\in ison} f_j$。

然后发现每次连 $(i,j)$ 这条边，答案会加上 $mx_j=dp_j+w_{(i,j)}-f_j$。

那么对于 $f_i$，就可以挑选前 $d_i$ 大的 $mx_j$，答案加上所有 $>0$ 的 $mx$ 值。$dp_i$ 同理。

时间复杂度 $O(n\log n)$。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=3e5+5;
int n,k,u[N],v[N],d[N],r[N];
int m,h[N],to[N*2],nxt[N*2];
ll w[N*2],mx[N],f[N],dp[N];
int cmp(ll x,ll y){return x>y;}
void add(int x,int y,ll z){
    to[++m]=y;
    w[m]=z;
    nxt[m]=h[x];
    h[x]=m;
}void dfs(int x,int fa){
    for(int i=h[x];i;i=nxt[i]){
        int y=to[i];
        if(y==fa) continue;
        dfs(y,x);
        dp[x]+=f[y];
    }int k=0;
    for(int i=h[x];i;i=nxt[i])
        if(to[i]!=fa)
            mx[++k]=dp[to[i]]+w[i]-f[to[i]];
    sort(mx+1,mx+k+1,cmp);
    for(int i=1;i<d[x];i++){
        if(mx[i]<=0) break;
        dp[x]+=mx[i];
    }f[x]=dp[x];
    if(mx[d[x]]>0) f[x]+=mx[d[x]];
    if(!d[x]) dp[x]=-1e9;
    for(int i=1;i<=k;i++) mx[i]=0;
}int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>d[i];
    for(int i=1;i<n;i++){
        int x,y,z;
        cin>>x>>y>>z;
        add(x,y,z);
        add(y,x,z);
    }dfs(1,0);
    cout<<f[1];
    return 0;
}
```

---

## 作者：LJQ0808 (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT_abc259_f)

# 题解

## 错误想法
我们可以发现直接将边排序来选是错的。

hack:

input:
```
4
1 1 1 1
1 2 2
2 3 3
3 4 2
```
output:
```
4
```

我们可以将每个点都遍历一下求最大值，所以可以用 DP 来求解。

## 定义状态

设 $dp_{i,0}$ 为不选择 $i$ 与其父节点的连边时，以 $i$ 为根所得子树的最大价值。$dp_{i,1}$ 为选择 $i$ 与其父节点的连边时，以 $i$ 为根所得子树的最大价值。

我们可以发现最后的答案为 $dp_{1,0}$，不输出 $dp_{1,1}$ 是因为 $1$ 无父亲。

## 转移状态
令 $v$ 为属于 $u$ 的子树的节点，$w$ 为 $u$ 到 $v$ 的路径之和。

对于 $dp_{u,0}$ 相当于 $dp_{v,0}$ 的和。

从 $dp_{v,0}$ 变为 $dp_{v,1}$ 多了 $w$。

可以用 vector 存 $dp_{v,1} + w - dp_{v,0}$，然后 vector 从小到大排序贪心取最大，如果 $dp_{v,1} + w - dp_{v,0} < 0$，我们可以舍掉。

当 $d[u] = 0$ 时，因为 $dp[u][1]$ 是为选择 $i$ 与其父节点的连边时，以 $i$ 为根所得子树的最大价值。所以 $dp[u][1]$ 是不可能的，可以设极小值。

$dp_{u,0}$ 没与父亲连边了，所以最多入 $d_u$ 条边。

$dp_{u,1}$ 已经与父亲连边了，所以最多入 $d_u - 1$ 条边。

AC code:

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define print(x) cout<<#x<<"="<<x<<"\n"
#define pii pair<int,int>
const ll LINF=1e18;
const int N=3e5+5;
int n;
vector<pii> g[N<<1];
void add_edge(int u,int v,int w){
	g[u].push_back({v,w});
}
void add_und_edge(int u,int v,int w){
	add_edge(u,v,w);add_edge(v,u,w);
}
ll dp[N][2];
//dp[i][0]：不选择 i 与其父节点的连边时，以 i 为根所得子树的最大价值。 
//dp[i][1]：选择 i 与其父节点的连边时，以 i 为根所得子树的最大价值。 
int d[N];
void dfs(int u,int fa){
	vector<ll> pq;
	for(pii P:g[u]){
		int v=P.first,w=P.second;
		if(v!=fa){
			dfs(v,u); 
			dp[u][0]+=dp[v][0];//所有的不连儿子边时，为《不选择 i 与其父节点的连边》。 
			pq.push_back(dp[v][1]+w-dp[v][0]);//增加量。 
		}
	}
	sort(pq.begin(),pq.end(),greater<ll>());//从大到小排序,求前 d[i] 和 d[i-1] 大。 
	int len=pq.size();
	dp[u][1]=(d[u]==0)?(-LINF):(dp[u][0]);//当 d[u] = 0 时：dp[u][1] 是不可能的。否则跟 dp[u][0] 相等。 
	for(int i=0;i<len;i++){
		if(i<d[u] && pq[i]>0){//dp[u][0] 没与父亲连边了，所以最多为 d[u]。 
			dp[u][0]+=pq[i];
		}
		if(i<d[u]-1 && pq[i]>0){//dp[u][1] 已经与父亲连边了，所以最多为 d[u]-1。 
			dp[u][1]+=pq[i];
		}
	}
}
signed main(){
	//HAPPY!
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);
	cin>>n; 
	for(int i=1;i<=n;i++){
		cin>>d[i];
	}
	for(int i=1;i<n;i++){
		int x,y,z;
		cin>>x>>y>>z;
		add_und_edge(x,y,z);
	}
	dfs(1,0);
	cout<<dp[1][0];//不输出 dp[1][1] 因为 1 无父亲。  
	return 0;
}

```

---

## 作者：returnzheng (赞：1)

题目大概意思是有一棵树，第 $i$ 个节点有一个数字 $d_i$，求在每个点选的边不超过 $d_i$ 条的情况下的最大边权和。由于是棵树，所以可以想到树形dp。而每个节点又有要不要连接父亲节点的边的区别。由此可以想到 $f_{i, 0}$ 表示不要父亲节点的边，而 $f_{i, 1}$ 表示选中连接父亲节点的边。先让 $f_{i, 0}$ 和 $f_{i, 1}$ 初始化为 $\sum f_{son, 0}$,再用优先队列存储 $f_{son, 1} + w - f_{son, 1}$ 最后让 $f_{i, 0}$ 加上堆中前 $d_i$ 个，让 $f_{i, 1}$ 加上队中前 $d_i - 1$ 个。答案就是 $f_{i, 0}$。


```cpp
#include <bits/stdc++.h>
using namespace std;
struct edge{
	long long to;
	long long w = 0;
	long long nxt = -1;
};
long long tot = -1;
long long head[310000];
edge e[610000];
void add(long long x, long long y, long long w){
	e[++tot].nxt = head[x];
	head[x] = tot;
	e[tot].to = y;
	e[tot].w = w;
}
long long d[310000];
long long f[310000][2];
void dfs(long long p = 1, long long fa = 0){
	priority_queue<long long> q;
	for (long long i = head[p]; i != -1; i = e[i].nxt){
		if (e[i].to == fa){
			continue;
		}
		long long x = e[i].to;
		dfs(x, p);
		f[p][0] += f[x][0];
		q.push(f[x][1] + e[i].w - f[x][0]);
	}
	f[p][1] = (d[p] == 0) ? (-1e9) : (f[p][0]);     
	for (long long i = 1; i <= d[p]; i++){
		if (q.empty() || q.top() <= 0){
			break;
		}
		if (i < d[p]){
			f[p][1] += q.top();
		}
		if (i <= d[p]){
			f[p][0] += q.top();
		}
		q.pop();
	}
}
int main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	long long n;
	cin >> n;
	memset(head, 0xff, sizeof(head));
	for (long long i = 1; i <= n; i++){
		cin >> d[i];
	}
	for (long long i = 1; i < n; i++){
		long long x, y, w;
		cin >> x >> y >> w;
		add(x, y, w);
		add(y, x, w);
	}
	dfs();
	cout << f[1][0] << '\n';
	return 0;
}
```

---

## 作者：wqc2011 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc259_f)
### 错误的贪心
若对节点 $i$ 的所有边进行排序，再选取之中前 $d_i$ 条大于 $0$ 的边求和统计答案，则会被以下样例 hack 掉：

```cpp
6
1 1 1 1 1 1
1 2 3 
2 3 4
3 4 3
4 5 4
5 6 3
//正确输出
9
//错误输出
8
```
### 考虑 DP
- #### 状态定义
$dp_{i,0}$ 为节点 $i$ 不接与其父亲 $f_i$ 的答案。

$dp_{i,1}$ 为节点 $i$ 连接与其父亲 $f_i$ 的答案。
- #### 状态转移
因为 $d_i$ 限制了从 $i$ 连出的边数，即限制了加入 $dp_{to,1}$ 的数量，所以我们需优先考虑 $dp_{to,1}$ 的值，$dp_{to,1}$ 的值越大越好，但若 $dp_{to,0} > dp_{to,1}$ 则我们会加上 $dp_{to,0}$ 的值。

因此，我们先用优先队列存下 $dp_{to,1} - dp_{to,0}$ 的值（其中 $to$ 为$i$ 的儿子）。在 $dp_{to,0} > dp_{to,1}$ 时此值为负，所以我们会优先考虑能连的边中更大且 $dp_{to,1} \ge dp_{to,0}$ 的 $dp_{to,1}$，若已经选择了 $d_i$ 个 $dp_{to,1}$ 我们只需把剩下所有大于 $0$ 的 $dp_{to,0}$ 加入答案中即可。

要注意的是，由于 $dp_{i,1}$ 已经选择了到它父亲的这一条边，所以 $dp_{i,1}$ 最多加 $d_i - 1$ 个 $dp_{to,1}$。

- #### 初始状态和答案
在 $d_i > 0$ 时，$dp_{i,1} = w$，其中 $w$ 为 $i$ 走到它父亲 $f_i$ 的边权。

答案为 $ \max(dp_{1,0},dp_{1,1})$。
### 代码附上——

```cpp
#include<bits/stdc++.h>
#define int long long
#pragma GCC optimize(3)
using namespace std;
const int maxn = 300010;
const int inf = 1e9;
//unsigned long long 
//cout << fixed << setprecision(3)
//cout << setw(5) << 
//continue
int d[maxn], dp[maxn][2];
struct S{
    int to, w;
};
struct S1{
    int w, id;
    bool operator < (const S1 &a) const{
        return w < a.w;
    }
};
vector<S> v[maxn];
void dfs(int x, int f, int w){
    if(d[x] > 0) dp[x][1] = w;
    priority_queue<S1> q;
    for(auto i : v[x]){
        if(i.to == f) continue;
        dfs(i.to, x, i.w);
        q.push({dp[i.to][1] - dp[i.to][0], i.to});
    }
    while(!q.empty()){
    	S1 now = q.top();
    	q.pop();
        if(now.w < 0 || d[x] <= 0){
            dp[x][0] += dp[now.id][0];
            dp[x][1] += dp[now.id][0];
        	continue;
		} 
        d[x]--;
        dp[x][0] += dp[now.id][1];
        if(d[x] == 0 && dp[now.id][0] > 0){
        	dp[x][1] += dp[now.id][0];
		}
        if(d[x] == 0) continue;
        dp[x][1] += dp[now.id][1];
	}
}
signed main(){
    //freopen("a.in", "r", stdin);
    //freopen("a.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for(int i = 1;i <= n;i++){
        cin >> d[i];
    }
    for(int i = 1;i < n;i++){
        int x, y, w;
        cin >> x >> y >> w;
        v[x].push_back(S{y, w});
        v[y].push_back(S{x, w});
    }
    dfs(1, 0, 0);
    cout << max(dp[1][0], dp[1][1]);
    return 0;
}
```
### 感谢观看！

---

## 作者：Leaper_lyc (赞：1)

树形 DP 的好题。

设 $f_{u,0/1}$ 表示是否选与父亲相连的边，以 $u$ 为子树的根时的方案数。

显然可以一条边都不选，那么答案就是所有非负的 $f_{v,1}$ 的和，其中 $v$ 是 $u$ 的儿子，用 $total$ 统计。也就是说初始值：$f_{u,0/1}=total$。

现在考虑如何转移。

若算这条边选了比没选的贡献要大，也就是说 $f_{v,0}+w>f_{i,1}$ 那么 $f_{i,0}+w-f_{i,1}$ 就是二者的差值，那么相当于要选这样的差值 $d_u$ 个。

我们可以把这些差值排序，然后选 $d_u$ 个最大的。

时间复杂度 $O(n\log n)$。

于是快乐地 AC 了。

有些细节见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int _ = 3e5 + 10;

int n, d[_];
// 记得要开 long long 
long long f[_][2];

vector < pair <int, long long> > g[_];

void dfs(int u, int fa) {
	priority_queue <long long> q;
	long long tot = 0, tot2 = 0;
	for (int i = 0; i < (int)g[u].size(); i++) {
		int v = g[u][i].first;
		long long w = g[u][i].second;
		if (v == fa) continue; dfs(v, u);
		if (f[v][1] > 0) tot += f[v][1]; 
		if (d[v]) // 要 v 能够选边才能转移。 
			if (f[v][0] + w > f[v][1])
				q.push(f[v][0] + w - f[v][1]);
	}
	f[u][0] = f[u][1] = tot;
	for (int i = 1; i <= d[u]; i++) {
		if (!q.empty()) tot2 += q.top(), q.pop();
		if (i == d[u] - 1) f[u][0] += tot2;
		if (i == d[u]) f[u][1] += tot2;
	}
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> d[i];
	for (int i = 1, x, y, z; i < n; i++) {
		cin >> x >> y >> z;
		g[x].push_back(make_pair(y, z));
		g[y].push_back(make_pair(x, z));
	}
	dfs(1, 0);
	cout << max(f[1][1], f[1][0]);
}
```

---

## 作者：dd_d (赞：1)

[更好的阅读体验](https://www.cnblogs.com/dd-d/p/16823696.html)
## Sol  
考虑 dp。  
记 $dp_{u,0/1}$ 表示 $u$ 点是否向上连边的最大值。  
转移的话相当于是找若干个 $dp_{v,1}+w(u,v)$ 进行转移。  
其中 $w(u,v)$ 表示 $(u,v)$ 这条边的权值。  
那么每次开个 vector 把 $dp_{v,1}+w(u,v)$ 存下来然后排个序，找最大的 $d_u$ 个节点即可。  
时间复杂度 $O(n \log n)$。  
## Code  
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0)
#define lowbit(x) (x&(-x))
#define int long long
using namespace std;
inline char gc()
{
	static char buf[1000000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int N=3e5+10;
vector<pair<int,int> > G[N];
int n,a[N],dp[N][2];
void dfs(int u,int fa)
{
	int s=0; vector<int> g;
	for (auto [v,w]:G[u])
	{
		if (v==fa) continue;
		dfs(v,u); s+=dp[v][0];
		g.emplace_back(dp[v][1]-dp[v][0]+w);
	}
	sort(g.begin(),g.end(),greater<int>());
	for (int i=0;i<min((int)g.size(),a[u]-1);i++)
		s+=max(0ll,g[i]);
	dp[u][0]=s+(g.size()>a[u]-1?max(0ll,g[a[u]-1]):0);
	if (!a[u]) dp[u][1]=-0x3f3f3f3f3f3f3f3f;
	else dp[u][1]=s;
}
signed main()
{
	n=read();
	for (int i=1;i<=n;i++)
		a[i]=read();
	for (int i=1;i<n;i++)
	{
		int u=read(),v=read(),w=read();
		G[u].emplace_back(v,w); G[v].emplace_back(u,w);
	}
	dfs(1,0);
	writeln(max(dp[1][0],dp[1][1]));
}





```

---

## 作者：CQ_Bob (赞：1)

## 前言

[这](https://www.luogu.com.cn/user/1025854)是哪个【】啊，复制我题解，我原来的还不见了。啊，[证据](https://blog.csdn.net/m0_66603329/article/details/131615039)。

## 分析

一眼贪心。

定义状态函数 $\mathit{f}_{i,0/1}$ 表示在以 $i$ 为根的子树中，选取与 $i$ 连边的不超过 $d_i$ 或 $d_i-1$ 时的最大价值和。很显然，第二种情况是留了一条边给它和它的父亲。

可以先算出来 $i$ 的儿子不和 $i$ 连边时的最大价值总和。可以看出，$f_{i,0/1}$ 的值都是在这个价值总和的基础上只增不减的。可以贪心地去求增加量，对于一个儿子 $j$，若 $w_{i\to j}+f_{j,1} \ge f_{j,0}+1$，则可以考虑取 $i\to j$ 这条边。因为最多有 $d_i$ 条边让 $i$ 选，开个大根堆取前 $\min(size,d_i)$ 和前 $\min(size,d_i-1)$ 增量即可。其中 $size$ 是可以考虑选取的数量。

答案就是 $\max(f_{root,0},f_{root,1})$。但是，由于 $root$ 没有父亲，少取不如多取，所以直接是 $f_{root,0}$ 就行了。

小细节：在求增量的时候，需要先判断儿子 $j$ 是否能取和它的连边，即 $d_i \ge 1$。

## 代码


[Link](https://atcoder.jp/contests/abc259/submissions/47640254).

---

## 作者：I_will_AKIOI (赞：0)

校内模拟赛题。

容易想到 $f_{k,i}$ 表示在以 $k$ 为根的子树内，点 $k$ 连了 $i$ 条边的最大收益。我们发现处理完 $k$ 的子树后，接下来 $k$ 只会和他的父亲连一条边，因此只需要记录 $k$ 连的边数是小于 $d_k$  还是等于 $d_k$ 就可以了。因此状态就变为了 $f_{k,0/1}$ 表示以 $k$ 为根的子树连了小于 $d_k$ 或者等于 $d_k$ 条边的最大收益。

接着考虑转移。枚举 $k$ 的孩子 $son$，要么选择 $k$ 和 $son$ 之间的边 $val$，要么不选。就是可以选择 $a_i=f_{son,0}+val$ 或者是 $b_i=f_{son,1}$ 两种。其中选第一种的数量必须小于 $d_k$ 或者等于 $d_k$。（视当前求解的是 $f_{k,0}$ 还是 $f_{k,1}$ 而定）

我们把转移的问题再转换一下，变为了有 $n$ 个物品，每个物品有 $1/0$ 两种代价，还有对应的收益 $a_i,b_i$，$a_i$ 的代价为 $1$，$b_i$ 的代价为 $0$，求最大收益。

那么我们可以运用类似反悔贪心的思想，首先选择代价为 $0$ 的物品 $b_i$，接着考虑把 $b_i$ 换成 $a_i$，那么肯定是要 $a_i-b_i$ 越大越好。因此把 $a_i-b_i$ 从大到小排序，选择前 $d_k-1$ 个就得到了 $f_{k,0}$，$f_{k,1}$ 同理，选择前 $d_k$ 个。

注意特判边界情况，若 $d_k=0$，那么 $f_{k,0}$ 是不可能达成的，需要设置为负无穷防止出现错误。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 300005
using namespace std;
int n,d[N],f[N][2];
vector<pair<int,int> >v[N];
void dfs(int k,int fa)
{
	if(k!=1&&v[k].size()==1)
	{
		if(d[k]==0) f[k][1]=0;
		else f[k][0]=f[k][1]=0;
		return;
	}
	vector<int>tmp;
	int sum0=0,sum1=0;
	for(auto now:v[k])
	{
		if(now.first==fa) continue;
		dfs(now.first,k);
		sum0+=f[now.first][1];
		sum1+=f[now.first][1];
		tmp.push_back(max(0ll,f[now.first][0]+now.second-f[now.first][1]));
	}
	sort(tmp.begin(),tmp.end(),greater<int >());
	for(int i=0;i<min((int)tmp.size(),d[k]-1);i++) sum0+=tmp[i];
	for(int i=0;i<min((int)tmp.size(),d[k]);i++) sum1+=tmp[i];
	f[k][0]=sum0;
	f[k][1]=sum1;
	if(d[k]==0) f[k][0]=-1e18;
	return;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>d[i],f[i][0]=f[i][1]=-1e18;
	for(int i=1;i<n;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		v[x].push_back({y,z});
		v[y].push_back({x,z});
	}
	dfs(1,0);
	cout<<max(f[1][0],f[1][1]);
	return 0;
}
```

---

## 作者：CmsMartin (赞：0)

考虑树形 dp。

$f_{u, 0/1}$ 表示 $u$ 是否有连满的边的最大值。

转移的话先让 $f_{u, 0} = \sum_{v \in \operatorname{subtree}(u)} f_{v, 1}$，然后考虑把连上 $(v, u)$ 的贡献算上。这样的贡献显然是 $f_{v, 0} + w - f_{u, 0}$。在子树中取前 $d_u$ 大加到 $f_{u,1}$ 中，取前 $d_{u} - 1$ 大加到 $f_{u, 0}$ 中。 注意，这里要求的前多少大有前提，要这个东西大于 $0$，不然还不如不连满。

时间复杂度瓶颈在排序。 $\mathcal O(n \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
using ll = long long;
int n, d[N];
vector<pair<int, ll> > G[N];
ll f[N][2], mx[N];

void dfs(int u, int fa) {
    int tot = 0;
    for (auto [v, w] : G[u]) if (v != fa) {
        dfs(v, u);
        f[u][0] += f[v][1];   
    }
    for (auto [v, w] : G[u]) if (v != fa)
        mx[++tot] = f[v][0] + w - f[v][1];
    sort(mx + 1, mx + 1 + tot, greater<ll>());
    for (int i = 1; i < d[u]; i++) if (mx[i] > 0) {
        f[u][0] += mx[i];
    } else break;
    f[u][1] = f[u][0];
    if (mx[d[u]] > 0) f[u][1] += mx[d[u]];
    if (!d[u]) f[u][0] = -1e9;
    for (int i = 1; i <= tot; i++) mx[i] = 0;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> d[i];
    for (int i = 1; i < n; i++) {
        static int u, v, w;
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    dfs(1, 0);
    cout << max(f[1][0], f[1][1]);
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 分析

考虑树形 DP。

我们可以以节点 $1$ 为根，从叶子节点往上推。注意到，任意一个除根节点外的节点，其与其父节点都必有一条连边。所以在定义 DP 数组时，我们需要将其分成两类：

1. $f_{i,1}$：不选择 $i$ 与其父节点的连边时，以 $i$ 为根所得子树的最大价值。

2. $f_{i,0}$：选择 $i$ 与其父节点的连边时，以 $i$ 为根所得子树的最大价值。


这样，我们在往上推的时候，$f_{i,0}$ 与 $f_{i,1}$ 的区别就在与取不取 $d_i$ 条连向子节点的边。而 $f_{i,0}$ 与 $f_{i,1}$ 的最初价值，一定是在 $i$ 的任意子节点 $j$，满足：$f_{j,1}>0$ 时的总和。如果有一个子节点 $j$，它有：$f_{j,0}+w>f_{j,1}$（$w$ 是 $i$ 与 $j$ 的连边边权），那么我们一定是把原来的 $f_{j,1}$ 换成 $f_{j,0}+w$。这个增加量是可以求的，即：$f_{j,0}+w-f_{j,1}$。我们求出所有的增加量，从大到小排序后，使用前 $\min(d_i,k)$（$k$ 为增加量的数量）个增加量，当做修改值对 $f_{i,0}$ 与 $f_{i,1}$ 进行调整即可。

最后的答案就是：$\max(f_{1,0},f_{1,1})$。

注：为什么我们的最初价值可以是上面的那个和呢？因为我们的最初价值就相当于不取节点 $i$ 的任意连边的最大价值，而 $f_{j,1}$ 正好就不能取 $i$ 与 $j$ 的连边。又因为得到的最大价值可能为**负数**，所以我们还要看一下是不是利于求最大值的。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
int n,x[N];
int d[N],w[N],ne[N],e[N],h[N],idx;
void add(int a,int b,int c){
	ne[idx]=h[a],w[idx]=c,e[idx]=b,h[a]=idx++;
}
int f[N][2];
void dfs(int now,int fa){
	int now_ans=0,ans=0;
	priority_queue<int> qu;//大根堆，取价值大的
	for(int i=h[now];~i;i=ne[i]){
		int j=e[i];
		if(j==fa) continue;
		dfs(j,now);
		if(f[j][1]>0) now_ans+=f[j][1];
		if(d[j]){//子节点能连边
			if(f[j][0]+w[i]>f[j][1]){//更优
				qu.push(f[j][0]+w[i]-f[j][1]);//增加量
			}
		}
	}
	f[now][0]=f[now][1]=now_ans;//最初价值
	for(int i=1;i<=d[now];i++){
		if(!qu.empty()){
			ans+=qu.top();qu.pop();
		}
		if(i==d[now]-1){//留一条边给now->fa
			f[now][0]+=ans;
		}
		else if(i==d[now]){//不留
			f[now][1]+=ans;
		}
	}
}
int ans;
signed main(){
	memset(h,-1,sizeof(h));
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>d[i];
	}
	for(int i=1;i<n;i++){
		int a,b,c;cin>>a>>b>>c;
		add(a,b,c),add(b,a,c);
	}
	dfs(1,-1);
	ans=max(f[1][0],f[1][1]);
	return cout<<ans,0;
}
```


---

