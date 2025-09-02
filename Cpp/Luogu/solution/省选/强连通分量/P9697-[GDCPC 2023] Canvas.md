# [GDCPC 2023] Canvas

## 题目描述

有一个长度为 $n$ 的序列，一开始序列中的所有元素均为 $0$。另外还有 $m$ 个操作，其中第 $i$ 个操作会将序列中第 $l_i$ 个元素的值改为 $x_i$，以及将序列中第 $r_i$ 个元素的值改为 $y_i$。每个操作必须恰好执行一次。

求执行操作的最优顺序，使得所有操作执行完成后，序列中所有元素之和最大。

## 样例 #1

### 输入

```
2
4 4
1 1 2 2
3 2 4 1
1 2 3 2
2 1 4 1
4 2
3 2 4 1
1 2 3 1```

### 输出

```
7
4 1 3 2
5
2 1```

# 题解

## 作者：rui_er (赞：10)

好题。

后面的操作会覆盖前面的操作，这东西不好处理，我们不妨时光倒流，将问题转化为一个位置一旦被填了数，就再也不会变了。如果解决了这个问题，只需将操作序列倒过来，就得到了原问题的解。

显然，所有 $x_i=y_i=2$ 的操作会最先被执行，所有 $x_i=y_i=1$ 的操作会最后被执行。只需要给所有 $x_i\ne y_i$ 的操作确定顺序即可，不妨设所有这样的操作都满足 $x_i=1,y_i=2$。

一旦操作 $(u,1,v,2)$ 被执行，则所有形如 $(v,1,w,2)$ 的操作都可以被执行。在这一系列操作涉及到的位置中，除了 $u$ 被填成了 $1$，其他位置都被填成了 $2$。我们称 $(u,1,v,2)$ 为**启动操作**，称启动操作引发出的一系列操作为**连锁操作**。这种传递关系使我们想到图论建模。

对于每个形如 $(u,1,v,2)$ 的操作，连接一条从 $u$ 指向 $v$ 的有向边。将图缩点，显然我们只会在入度为 $0$ 的强连通分量中选择恰好一条边作为启动操作，这条边的启动会导致它所在的强连通分量以及在它下游的所有强连通分量中的边成为连锁操作。我们不需要付出任何代价就可以把入度不为 $0$ 的强连通分量全部填成 $2$，而对于入度为 $0$ 的强连通分量，我们**最多**只会将一个点填为 $1$。

关于启动操作的选择还有一点要注意。如果一个入度为 $0$ 的强连通分量中，已经有点被形如 $(u,2,v,2)$ 的操作钦定填 $2$ 了，则以这个点的一条出边作为启动操作，就可以少将一个点填为 $1$（这就是上面说“最多”的原因）。

时间复杂度 $O(n+m)$。

```cpp
// Problem: T368340 [GDCPC2023] H-Canvas
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T368340?contestId=135929
// Memory Limit: 1 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const int N = 5e5 + 5;

int T, n, m, l[N], x[N], r[N], y[N], deg[N], vis[N], res[N], two[N];
vector<tuple<int, int>> e[N];
vector<int> ans, aft;

int dfn[N], low[N], tms, ins[N], col[N], scc;
stack<int> stk;

void tarjan(int u) {
    dfn[u] = low[u] = ++tms;
    stk.push(u);
    ins[u] = 1;
    for(auto [v, id] : e[u]) {
        if(!dfn[v]) {
            tarjan(v);
            chkmin(low[u], low[v]);
        }
        else if(ins[v]) {
            chkmin(low[u], dfn[v]);
        }
    }
    if(dfn[u] == low[u]) {
        ++scc;
        while(true) {
            int v = stk.top();
            stk.pop();
            ins[v] = 0;
            col[v] = scc;
            if(u == v) break;
        }
    }
}

void dfs(int u) {
    vis[u] = 1;
    for(auto [v, id] : e[u]) {
        ans.push_back(id);
        if(!vis[v]) dfs(v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for(cin >> T; T; --T) {
        cin >> n >> m;
        rep(i, 1, m) {
            cin >> l[i] >> x[i] >> r[i] >> y[i];
            if(x[i] == 2 && y[i] == 2) {
                ans.push_back(i);
                two[l[i]] = two[r[i]] = 1;
            }
            else if(x[i] == 1 && y[i] == 1) {
                aft.push_back(i);
            }
            else {
                if(x[i] > y[i]) {
                    swap(l[i], r[i]);
                    swap(x[i], y[i]);
                }
                e[l[i]].emplace_back(r[i], i);
            }
        }
        rep(u, 1, n) if(!dfn[u]) tarjan(u);
        rep(u, 1, n) for(auto [v, id] : e[u]) if(col[u] != col[v]) ++deg[col[v]];
        rep(u, 1, n) if(!deg[col[u]] && !vis[u] && two[u]) dfs(u);
        rep(u, 1, n) if(!deg[col[u]] && !vis[u]) dfs(u);
        for(int i : aft) ans.push_back(i);
        reverse(ans.begin(), ans.end());
        for(int i : ans) {
            res[l[i]] = x[i];
            res[r[i]] = y[i];
        }
        cout << accumulate(res + 1, res + 1 + n, 0) << endl;
        for(int i : ans) cout << i << " "; cout << endl;
        rep(i, 1, n) {
            deg[i] = vis[i] = res[i] = dfn[i] = low[i] = col[i] = two[i] = 0;
            e[i].clear();
        }
        ans.clear();
        aft.clear();
        tms = scc = 0;
    }
    return 0;
}
```

---

## 作者：Zelotz (赞：8)

因为后面的操作会覆盖前面的操作，思考起来较为复杂，所以不妨把操作顺序倒过来，这样某一个点被确定之后，该点的值不会改变。后续的所说的先后顺序都是倒过来的。

很明显，$(1,1)$ 操作一定该最后做，$(2,2)$ 操作一定最先做。

现在需要确定的只有形如 $(1,2)$ 操作的顺序。

考虑对 $(u,v)$ 做 $(1,2)$ 操作，即 $u$ 变成 $1$，$v$ 变成 $2$。再对 $(v, w)$ 做 $(1,2)$ 操作，此时相当于将 $v$ 变成 $1$ 的操作无效，答案更优了。这启示了建图操作。对所有变成 $1$ 的点向变成 $2$ 的点连边。

连完之后，可以发现在同一个强连通分量里的点，从任意一点开始按顺序遍历，只有起始点是 $1$，其他都是 $2$。于是缩点，图变为一个 DAG，从任意入度为 $0$ 的强连通分量开始 `dfs`，这样一定最优。不用在缩点后重新建图，直接在原图上 `dfs` 即可，因为边 $(u,v)$ 仅仅代表 $u$ 需要在 $v$ 之前选。

注意在入度为零的强连通分量中，要优先选择有 $(2,2)$ 操作的点，这样可以让整个强连通分量都是 $2$。

注意 $l,r,x,y$ 不要弄混，多测清空。

```
const int N = 5e5 + 5;
int n, m, l[N], r[N], x[N], y[N];
int low[N], dfn[N], idx, belong[N], num;
vector<PII> E[N];
bool vis[N];
stack <int> sk;
void tarjan(int x)
{
    low[x] = dfn[x] = ++idx;
    sk.push(x);
    vis[x] = 1;
    for (auto t : E[x])
    {
        int v = t.first;
        if (dfn[v])
        {
            if (vis[v]) low[x] = min(low[x], low[v]);
        }
        else
        {
            tarjan(v);
            if (vis[v]) low[x] = min(low[x], low[v]);
        }
    }
    if (low[x] == dfn[x])
    {
        int top; ++num;
        do
        {
            top = sk.top();
            vis[top] = 0; belong[top] = num;
            sk.pop();
        } while (top ^ x);
        
    }
}
vector <int> ans;
int ind[N], a[N];
void dfs(int x)
{
    if (vis[x]) return ;
    vis[x] = 1;
    for (auto t : E[x]) 
    {
        ans.pb(t.second);
        int v = t.first;
        if (vis[v]) continue;
        dfs(v);
    }
}
int Case = 0;
void solve()
{
    read(n, m);
    R(i, 1, m)
    {
        read(l[i], x[i], r[i], y[i]);
        if (x[i] == 1 && y[i] == 2) E[l[i]].pb({r[i], i});
        else if (x[i] == 2 && y[i] == 1) E[r[i]].pb({l[i], i});
    } 
    R(i, 1, n) if (!dfn[i]) tarjan(i);
    R(i, 1, n) vis[i] = 0;
    R(i, 1, m) if (x[i] == 2 && y[i] == 2) ans.pb(i); 
    R(i, 1, m)
    {  
        if (x[i] == 1 && y[i] == 2)
        {
            if (belong[l[i]] ^ belong[r[i]]) ++ind[belong[r[i]]];
        }
        if (x[i] == 2 && y[i] == 1)
        {
            if (belong[l[i]] ^ belong[r[i]]) ++ind[belong[l[i]]];
        }
    }
    R(i, 1, m)
    {
        if (x[i] != 2 || y[i] != 2) continue;
        if (!ind[belong[l[i]]]) dfs(l[i]);
        if (!ind[belong[r[i]]]) dfs(r[i]);
    }
    R(i, 1, n) if (!ind[belong[i]]) dfs(i);
    R(i, 1, m) if (x[i] == 1 && y[i] == 1) ans.pb(i);
    reverse(ans.begin(), ans.end());
    for (auto v : ans) a[l[v]] = x[v], a[r[v]] = y[v];
    int sum = 0;
    R(i, 1, n) sum += a[i];
    write(sum), ptc('\n');
    for (auto v : ans) write(v), ptc(' '); ptc('\n'); 
	ans.clear();
    idx = 0, num = 0;
    R(i, 0, n) belong[i] = 0, E[i].clear(), vis[i] = 0, low[i] = dfn[i] = a[i] = ind[i] = 0;
}
signed main() 
{
    int T = 1; 
    read(T); 
    while (T--) solve();
    return 0;
}
```

---

## 作者：Lyrella (赞：3)

# 前言

为数不多想出来的题。

# 题解

注意到有私人覆盖操作，于是倒序考虑。考虑一组 $(1,1)$ 一定最后放，$(2,2)$ 一定最先放。所以我们需要确定的东西其实是形如 $(1,2)$ 的二元组的顺序。考虑如果一个位置 $x$ 已经放了 $2$，那么后面在 $x$ 放 $1$ 一定不会对其造成影响，于是就可以操作在 $x$ 的 $(1,2)$，这样的操作方式有一定的传递性。所以我们进行图论建模，考虑把每个操作看成一条边，然后拓扑排序解决此题。

具体的，我们对于每个 $(u,1,v,2)$ 的操作，当成 $u$ 向 $v$ 连边，对原图缩点。对于所有 $(u,2,v,2)$ 的 $u$ 和 $v$ 如果其入度为零那么我们就可以从这个点作为起点开始做，可以发现一个位置可以操作只需要这个点已经为 $2$ 即可，所以从一个点作为起点我们直接 $\text{dfs}$ 即可，并不需要拓扑排序。

# 代码

```cpp
signed main(){
    int T = rd();
    while(T--){
        n = rd(), m = rd();
        for(int i = 1; i <= m; ++i){
            l[i] = rd(), x[i] = rd(), r[i] = rd(), y[i] = rd();
            if(x[i] + y[i] == 3){
                if(x[i] ^ 1)swap(l[i], r[i]), swap(x[i], y[i]);
                e[l[i]].push_back(make_pair(r[i], i));
            }
            if(x[i] + y[i] == 4)bg[++bcnt] = l[i], bg[++bcnt] = r[i], ans[++cnt] = i;
        }
        for(int i = 1; i <= n; ++i)if(! dfn[i])tar(i);
        for(int u = 1, v; u <= n; ++u)for(pii j : e[u])if(col[u] ^ col[v = j.first])++in[col[v]];
        for(int i = 1; i <= bcnt; ++i)if(! in[col[bg[i]]] and ! vs[bg[i]])dfs(bg[i]);
        for(int i = 1; i <= n; ++i)if(! in[col[i]] and ! vs[i])dfs(i);
        for(int i = 1; i <= m; ++i)if(x[i] + y[i] == 2)ans[++cnt] = i;
        for(int i = cnt; i; --i)sum[l[ans[i]]] = x[ans[i]], sum[r[ans[i]]] = y[ans[i]];
        for(int i = 1; i <= n; ++i)res += sum[i]; printf("%d\n", res);
        for(int i = cnt; i; --i)printf("%d%c", ans[i], i ^ 1 ? ' ' : '\n');
        init();
    }
    return 0;
}
```

---

## 作者：OccDreamer (赞：3)

首先观察到有一个关键性质是 $1 \leq x_i,y_i \leq 2$。

那么我们贪心的考虑我们肯定会将 $(x,y)=(1,1)$ 的在一开始操作，$(x,y)=(2,2)$ 的最后操作。

也就是说现在没有固定的是 $(x,y)=(1,2)$ 和 $(x,y)=(2,1)$ 的。

我们不妨令 $(x,y)=(1,2)$，然后连边 $(l,r)$。

然后我们需要依次选择每一条边 $(u,v)$，这个操作相当于赋值 $a_v =2$ 和赋值 $a_u=1$。

然后我们可以容易构造出来一个强联通分量中经过一系列操作至多有一个 $a=1$ 的节点，并且一定有一个 $a=1$ 的节点，具体的随便搜出一个这个分量中的 dfs 树然后从叶子开始操作即可。

那么缩强联通分量使图变成 DAG 之后如果一个点没有前驱那么意味着这一个强联通分量有一个点 $a=1$，如果有前驱那么我们可以将这一个强联通分量内的点全操作成 $2$。

建出图跑一个 tarjan 然后跑一个拓扑排序即可。

对于 $(x,y)=(2,2)$ 的限制，我连了边 $(0,x)$ 和 $(0,y)$，似乎更好考虑一些。

代码写的有点丑和冗余。

```cpp
 //code by Emissary
#include<bits/stdc++.h>

#define fi first
#define se second
#define vc vector
#define db double
#define ll long long
#define mk make_pair
#define pb push_back
#define PI pair<int,int>
#define ull unsigned long long
#define err cerr << "   -_-   " << endl
#define debug cerr << " ------------------- " << endl

#define input(x) freopen(#x".in","r",stdin)
#define output(x) freopen(#x".out","w",stdout)

#define NO puts("No")
#define YES puts("Yes")

//#define int long long

using namespace std;

namespace IO{
	inline int read(){
		int X=0, W=0; char ch=getchar();
		while(!isdigit(ch)) W|=ch=='-', ch=getchar();
		while(isdigit(ch)) X=(X<<1)+(X<<3)+(ch^48), ch=getchar();
		return W?-X:X;
	}
	inline void write(int x){
		if(x<0) x=-x, putchar('-');
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
	inline void sprint(int x){write(x), putchar(32);}
	inline void eprint(int x){write(x), putchar(10);}
}using namespace IO;

const int MAXN = 5e5+5;

vc<PI> G[MAXN];
vc<int> P[MAXN];

int hd, tl, Q[MAXN], res[MAXN];
int bel[MAXN], du[MAXN], node[MAXN], colcnt;
int n, m, topf, stk[MAXN], dfn[MAXN], low[MAXN], tot;
int head[MAXN], ne[MAXN<<1], to[MAXN<<1], weight[MAXN<<1], cnt;

bool mark[MAXN], ins[MAXN], vis[MAXN], ind[MAXN];

inline void add(int x, int y, int w){++cnt;to[cnt]=y;ne[cnt]=head[x];head[x]=cnt;weight[cnt]=w;}

inline void tarjan(int x){
	stk[++topf]=x; dfn[x]=low[x]=++tot; ins[x]=1;
	for(int i=head[x];i;i=ne[i]){
		if(dfn[to[i]]){
			if(ins[to[i]]) low[x]=min(low[x],dfn[to[i]]);
		}
		else tarjan(to[i]), low[x]=min(low[x],low[to[i]]);
	}	
	if(low[x]==dfn[x]){
		int t; stk[topf+1]=-1; ++colcnt;
		while(stk[topf+1]!=x){
			t=stk[topf];
			ins[t]=0; bel[t]=colcnt; node[colcnt]=t;
			--topf;
		}
	}
	return ;
}

inline void DFS(int x){//这一部分是搜出一个强联通分量内的 dfs 树
	vis[x]=1;
	for(int i=head[x];i;i=ne[i]){
		if(vis[to[i]] || bel[to[i]]!=bel[x]) continue;
		DFS(to[i]); P[bel[x]].pb(weight[i]); ind[weight[i]]=1;
	}
	return ;
}

inline void solve(){
	int a, b, c, d; vc<int> A, B;
	n=read(), m=read(); cnt=0; tot=0; colcnt=0;
	for(int i=0;i<=n;++i) vis[i]=0, dfn[i]=0, du[i]=0, res[i]=0;
	for(int i=0;i<=n;++i) mark[i]=0, head[i]=0, G[i].clear();
	for(int i=1;i<=m;++i){
		a=read(), b=read();
		c=read(), d=read(); ind[i]=0;
		mark[a]=mark[c]=1;
		if(b+d==2) A.pb(i), ind[i]=1;
		if(b+d==3){
			if(d==1) swap(a,c);
			add(a,c,i);
		}
		if(b+d==4) add(0,a,0), add(0,c,0), B.pb(i), ind[i]=1;
	}
	int ans=0; mark[0]=1;
	for(int i=1;i<=n;++i) ans+=mark[i];
	for(int i=0;i<=n;++i){
		if(dfn[i] || !mark[i]) continue;
		tarjan(i);
	}
	for(int i=0;i<=n;++i)
		for(int j=head[i];j;j=ne[j]){
			if(bel[i]!=bel[to[j]]){
				node[bel[to[j]]]=to[j];
				G[bel[to[j]]].pb(mk(bel[i],weight[j]));  du[bel[i]]++; ind[weight[j]]=1; res[bel[to[j]]]++;
			}
		}
	hd=1, tl=0;
	for(int i=1;i<=colcnt;++i) if(du[i]==0) Q[++tl]=i; (ans<<=1);
	for(int i=1;i<=colcnt;++i) if(res[i]==0) ans--; ans++;
	eprint(ans); for(auto i:A) sprint(i);
	for(int i=1;i<=colcnt;++i) P[i].clear(), DFS(node[i]);
	for(int i=1;i<=m;++i) if(ind[i]==0) sprint(i);
	while(hd<=tl){
		int t=Q[hd++];
		for(auto i:P[t]) if(i) sprint(i);//强联通分量内部的边
		for(auto ver:G[t]){
			if(ver.se) sprint(ver.se);//不同强联通分量之间的边
			if((--du[ver.fi])==0) Q[++tl]=ver.fi;
		}
	}
	for(auto i:B) sprint(i); putchar(10);
}

signed main(){
	int t=read();
	while(t--) solve();
	return 0;
}





































































```

---

## 作者：james1BadCreeper (赞：2)

由于第二次染色是无意义操作，因此考虑逆时旅人，这样变成了只有第一次会影响。

所有的 $x=y=2$ 操作优先执行，所有的 $x=y=1$ 最后执行，然后考虑剩下的填在中间。每有一个 $x+y=3$ 执行就意味着有一个数被定死为 $1$，那么 $(l,1,r,2)$ 相当于“用 $l$ 变成 $1$ 的代价换来 $r$ 变成 $2$”，这个关系可以用有向边 $l\rightarrow r$ 刻画，发现图上的一条链只有链首是 $1$。

SCC 缩点之后只有入度为 $0$ 的点涂一个 $1$ 即可。

```cpp
#include <bits/stdc++.h>
#define FN(A) fill(A + 1, A + n + 1, 0)
using namespace std; 

int n, m, arr[500005]; 
struct Node {
    int l, x, r, y; 
} a[500005]; 
vector<int> ans, gab; 
vector<pair<int, int>> G[500005];  

int dfn[500005], low[500005], num, st[500005], tot;
int cnt, col[500005], deg[500005]; 
bool ins[500005], vis[500005], tag[500005];  
void tarjan(int x) {
    dfn[x] = low[x] = ++num; ins[st[++tot] = x] = 1; 
    for (auto [y, i] : G[x]) 
        if (!dfn[y]) tarjan(y), low[x] = min(low[x], low[y]); 
        else if (ins[y]) low[x] = min(low[x], dfn[y]); 
    if (dfn[x] == low[x]) {
        ++cnt; int y; 
        do ins[y = st[tot--]] = 0, col[y] = cnt; while (x != y); 
    }
}

void dfs(int x) {
    if (vis[x]) return; vis[x] = 1; 
    for (auto [y, i] : G[x]) ans.emplace_back(i), dfs(y); 
}

void solve(void) {
    cin >> n >> m;
    ans.clear(); gab.clear(); num = tot = cnt = 0; 
    for (int i = 1; i <= n; ++i) {
        G[i].clear(); 
        dfn[i] = low[i] = st[i] = col[i] = deg[i] = ins[i] = vis[i] = tag[i] = arr[i] = 0; 
    }
    for (int i = 1; i <= m; ++i) {
        cin >> a[i].l >> a[i].x >> a[i].r >> a[i].y; 
        if (a[i].x + a[i].y == 2) gab.emplace_back(i); 
        else if (a[i].x + a[i].y == 3) {
            if (a[i].x > a[i].y) swap(a[i].l, a[i].r), swap(a[i].x, a[i].y); 
            G[a[i].l].emplace_back(a[i].r, i); 
        } else ans.emplace_back(i), tag[a[i].l] = tag[a[i].r] = 1; 
    }
    for (int i = 1; i <= n; ++i) if (!dfn[i]) tarjan(i); 
    for (int u = 1; u <= n; ++u) for (auto [v, i] : G[u]) if (col[u] != col[v]) ++deg[col[v]]; 
    for (int i = 1; i <= n; ++i) if (!deg[col[i]] && tag[i]) dfs(i); 
    for (int i = 1; i <= n; ++i) if (!deg[col[i]]) dfs(i); 
    for (int i : gab) ans.emplace_back(i); 
    reverse(ans.begin(), ans.end()); 

    for (int i : ans) arr[a[i].l] = a[i].x, arr[a[i].r] = a[i].y; 
    int ptr = 0; 
    for (int i = 1; i <= n; ++i) ptr += arr[i]; 
    cout << ptr << "\n"; 
    for (int i : ans) cout << i << " "; cout << "\n"; 
    assert(ans.size() == m); 
}

int main(void) {
    ios::sync_with_stdio(0); 
    int T; cin >> T; 
    while (T--) solve(); 
    return 0; 
}
```

---

## 作者：MaxBlazeResFire (赞：2)

考虑一个最终的操作序列，由于后面的操作会覆盖前面的操作，于是我们考虑把这个操作序列倒置，那么每个位置最终的数取决于第一个对它进行操作的位置。

于是，我们直接把原题的题意改为一个数被操作之后就不会变，不影响最终答案。

那么，先把所有 $(2,2)$ 的操作做掉，然后优先做 $(1,2)$ 或 $(2,1)$ 的操作。

现在每做一次，就至少有一个点变为 $1$，那么我们考虑将操作 $(x,1,y,2)$ 看作 $x\rightarrow y$ 的有向边，$(x,2,y,1)$ 看作 $y\rightarrow x$ 的有向边。这样做有什么用呢？我们发现，如果存在一条 $u\rightarrow v\rightarrow w$ 的链，我们可以先涂上 $u(1),v(2)$，再涂上 $v(1),w(2)$，以此类推，整条链上只有一个位置为 $1$，其它位置全都可以是 $2$.

于是我们对它缩点。对于缩点后的 $\rm DAG$，只有那些入度为 $0$ 的位置需要涂一个 $1$。这里需要注意，如果这个入度为 $0$ 的连通分量里有 $(2,2)$ 的操作，可以从这个操作开始从而使答案更优。

最终判掉所有 $(1,1)$ 的位置即可。复杂度 $O(n+m)$。

~~这能是个紫？~~

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 500005

int n,m,Vis[MAXN];

struct node{
	int u,x,v,y;
	node(){}
	node( int a , int b , int c , int d ): u(a),x(b),v(c),y(d){}
}N[MAXN];

vector< pair<int,int> > E[MAXN],P;
vector<int> Ans,Scc[MAXN];

int dfn[MAXN],low[MAXN],idx,st[MAXN],top,inst[MAXN];
int Scnt,bel[MAXN],deg[MAXN],vis[MAXN],col[MAXN];
int sta[MAXN];

void tarjan( int x ){
	dfn[x] = low[x] = ++idx,inst[x] = 1,st[++top] = x;
	for( pair<int,int> p : E[x] ){
		int v = p.first;
		if( !dfn[v] ) tarjan( v ),low[x] = min( low[x] , low[v] );
		else if( inst[v] ) low[x] = min( low[x] , dfn[v] );
	}
	if( dfn[x] == low[x] ){
		Scnt ++;
		while( st[top] != x ){
			int v = st[top];
			bel[v] = Scnt,inst[v] = 0,Scc[Scnt].emplace_back( v );
			top --;
		}
		bel[x] = Scnt,inst[x] = 0,Scc[Scnt].emplace_back( x );
		top --;
	}
}

int Ansvis[MAXN];
void get_ans( int x ){
	for( pair<int,int> p : E[x] ){
		int v = p.first,w = p.second;
		if( !Ansvis[w] ) Ansvis[w] = 1,Ans.emplace_back( w ),get_ans( v );
	}
}

int cc[MAXN];
inline void solve(){
	scanf("%lld%lld",&n,&m);
	for( int i = 1 ; i <= m ; i ++ ){
		int u,x,v,y; scanf("%lld%lld%lld%lld",&u,&x,&v,&y);
		N[i] = node( u , x , v , y );
		if( x == 2 && y == 2 ) P.emplace_back( make_pair( u , v ) ),Ans.emplace_back( i );
		if( x == 1 && y == 2 ) E[u].emplace_back( make_pair( v , i ) ),Vis[u] = Vis[v] = 1;
		if( y == 1 && x == 2 ) E[v].emplace_back( make_pair( u , i ) ),Vis[v] = Vis[u] = 1;
	}
	for( int i = 1 ; i <= n ; i ++ ) if( !dfn[i] && Vis[i] ) tarjan( i );
	for( int u = 1 ; u <= n ; u ++ ){
		for( pair<int,int> p : E[u] ){
			int v = p.first;
			if( bel[u] != bel[v] ) if( !vis[bel[v]] ) deg[bel[v]] ++,vis[bel[v]] = 1;
		}
		for( pair<int,int> p : E[u] ){
			int v = p.first;
			vis[bel[v]] = 0;
		}
	}
	for( pair<int,int> ele : P ){
		int u = ele.first,v = ele.second;
		col[bel[u]] = col[bel[v]] = 1;
		sta[bel[u]] = u,sta[bel[v]] = v;
	}
	int Ansc = 0;
	for( int i = 1 ; i <= Scnt ; i ++ )
		if( !deg[i] && !col[i] ) sta[i] = Scc[i][0];
	for( int i = 1 ; i <= Scnt ; i ++ ) if( !deg[i] ) get_ans( sta[i] );
	for( int i = 1 ; i <= m ; i ++ )
		if( N[i].x == 1 && N[i].y == 1 ) Ans.emplace_back( i );
	reverse( Ans.begin() , Ans.end() );
	for( int r : Ans ){
		int u = N[r].u,v = N[r].v;
		Ansc -= cc[u],Ansc -= cc[v];
		cc[u] = N[r].x,cc[v] = N[r].y;
		Ansc += cc[u],Ansc += cc[v];
	}
	printf("%lld\n",Ansc);
	for( int ele : Ans ) printf("%lld ",ele); puts("");
	for( int i = 1 ; i <= n ; i ++ ) dfn[i] = low[i] = st[i] = inst[i] = cc[i] = bel[i] = vis[i] = Vis[i] = col[i] = deg[i] = sta[i] = Ansvis[i] = 0;
	for( int i = 1 ; i <= m ; i ++ ) Ansvis[i] = 0;
	for( int i = 1 ; i <= n ; i ++ ) E[i].clear(); P.clear(); Ans.clear();
	for( int i = 1 ; i <= Scnt ; i ++ ) Scc[i].clear();
	idx = top = Scnt = 0;
}

signed main(){
	int testcase; scanf("%lld",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：NahX_ (赞：1)

## 题意

给定一个长为 $n$ 的序列以及 $m$ 个操作，初始序列中每个元素均为 0，每个操作形如 $(l,x,r,y),x\in[1,2],y\in[1,2]$ 表示将序列第 $l$ 个数修改为 $x$，第 $r$ 个数修改为 $y$，求最优顺序进行 $m$ 个操作使最终序列元素和最大值。

---

一个元素被赋值多次最终取到的只是对此元素最后一次操作的赋值，不妨考虑对每个元素只记录对其最后一次操作的赋值，也就是把操作顺序倒序来看，这样每个元素被赋值后就无法被覆盖。

看完题目很容易注意到 $x,y$ 的取值，于是可以考虑对操作的每一种 $x,y$ 分开讨论。

**注：以下操作序列均指原题目所求的操作序列的倒序。**

最终序列元素和最大就是尽量使最终序列中 1 的个数尽量少，即 2 的个数尽量多。

对于操作 $(l,x,r,y)$：

1. $x=2,y=2$，显然这种操作优先操作一定能保证 2 的个数尽量多。

2. $x=1,y=1$，显然这种操作最后操作一定能保证 1 的个数尽量少。

剩下两种情况 $x=1,y=2$ 与 $x=2,y=1$ 无法直接确定顺序，发现对于 $x=1,y=2$ 若 $x$ 已经被赋值，那么直接操作一定不劣，$x=2,y=1$ 同理。

这是发现对于一元素 $p$，若其被赋值，则会使所有操作形如 $(p,x,r,y)$ 随后执行，又会使所有操作形如 $(r,x,v,y)$ 随后执行，类似于连锁反应。到这里就容易想到建图了，对于操作 $(l,x,r,y),x=1,y=2$ 连一条 $(l,r)$ 的有向边，$x=2,y=1$ 交换 $l,r$ 同理，建完图发现对于一个强连通分量，只要其中有一个点被赋值，那么只要包含这个强连通分量中的元素的操作都可以随后执行。发现对入度为 0 的强连通分量只能通过包含此强连通分量内元素的 $x=2,y=2$ 的操作或是以最终序列中一个元素为 1 的代价任意进行一个包含强连通分量中包含元素的操作才能使所有包含此强连通分量中包含元素的操作进行"连锁反应"。而不包含入度为 0 的强连通分量包含元素的操作 $(l,x,r,y)$ 可以保证有操作执行过使 $l$ 被赋值过，那么直接在所有连向此强连通分量的强连通分量的所有操作执行完后执行即可。

总的来说，按以上方式建图后缩点对每个入度为 0 的强连通分量判断是否有包含此强连通分量内元素的 $x=2,y=2$ 的操作，如果没有就要以最终序列中一个元素为 1 的代任意进行一个包含强连通分量中包含元素的操作才能去进行之后的操作，最后将 $x=1,y=1$ 的操作全部执行，再将操作序列反转得到答案，最终序列元素最大值直接在所有操作结束后计算即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
#define mp make_pair
#define intz(x,a) memset(x,a,sizeof(x))
int head[N],cnt,rt[N],z[N],tp,dfn[N],low[N],ct,bl[N],tot,rd[N],fl[N];bool vis[N],in[N],as[N];
struct edge{int to,nxt;}e[N<<1];vector<pair<int,pair<int,int>>>q,g;vector<int>ass;vector<pair<int,int>>w[N];
void add(int u,int v){e[++cnt]={v,head[u]},head[u]=cnt;}
void dfs(int u){dfn[u]=low[u]=++ct,z[++tp]=u,in[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
		if(!dfn[e[i].to])dfs(e[i].to),low[u]=min(low[u],low[e[i].to]);
		else if(in[e[i].to])low[u]=min(low[u],dfn[e[i].to]);
	if(dfn[u]==low[u]){rt[++tot]=u;do bl[z[tp]]=tot,in[z[tp]]=0;while(z[tp--]!=u);}
}
int main(){int T;cin>>T;
	while(T--){
		intz(head,0);intz(vis,0);intz(rd,0);intz(dfn,0);intz(fl,0);intz(as,0);intz(rt,0);intz(in,0);cnt=ct=0;q.clear(),g.clear(),ass.clear();
		int n,m,ans=0;cin>>n>>m;for(int i=1;i<=n;i++)w[i].clear();
		for(int i=1,u,v,x,y;i<=m;i++){cin>>u>>x>>v>>y;
			if(x==1&&y==2)add(u,v),w[u].push_back(mp(v,i));else if(x==2&&y==1)add(v,u),w[v].push_back(mp(u,i));
			else if(x==2&&y==2)q.push_back(mp(u,mp(v,i)));else g.push_back(mp(u,mp(v,i)));
		}
		for(int i=1;i<=n;i++)if(!dfn[i])dfs(i);
		for(int t=0;t<q.size();t++)vis[bl[q[t].first]]=vis[bl[q[t].second.first]]=1;
		for(int i=1;i<=n;i++)for(pair<int,int>t:w[i])if(bl[i]!=bl[t.first])++rd[bl[t.first]];queue<int>dl;
		for(int i=1;i<=tot;i++)if(!rd[i]&&!vis[i]&&w[rt[i]].size())fl[rt[i]]=in[rt[i]]=1,dl.push(rt[i]);
		for(pair<int,pair<int,int>>t:q){if(!fl[t.first])fl[t.first]=2;if(!fl[t.second.first])fl[t.second.first]=2;ass.push_back(t.second.second);
			if(!in[t.first])dl.push(t.first),in[t.first]=1;if(!in[t.second.first])dl.push(t.second.first),in[t.second.first]=1;
		}
		while(!dl.empty()){int u=dl.front();dl.pop();
			for(pair<int,int>t:w[u]){ass.push_back(t.second);if(!fl[t.first])fl[t.first]=2;
				if(!in[t.first])dl.push(t.first),in[t.first]=1;
			}
		}
		for(pair<int,pair<int,int>>t:g){if(!fl[t.first])fl[t.first]=1;if(!fl[t.second.first])fl[t.second.first]=1;ass.push_back(t.second.second);}
		for(int i=1;i<=n;i++)ans+=fl[i];cout<<ans<<endl;
		reverse(ass.begin(),ass.end());for(int i:ass)cout<<i<<' ';cout<<endl;
	}
	return 0;
}
```

---

## 作者：快乐的大童 (赞：1)

### 题意简述
有一个长度为 $n$ 的数组 $a$ 和 $m$ 次操作，$a_i$ 初始为 $0$。每次操作形如 $l_i,x_i,r_i,y_i$ 表示执行 $a_{l_i}\leftarrow x_i,a_{r_i}\leftarrow y_i$，你可以改变 $m$ 次操作的执行顺序，求最终 $\sum_{i=1}^n a_i$ 的最大值，并给出执行操作的顺序。

多组数据，$\sum n,\sum m\le 5\times10^5,1\le x_i,y_i\le 2$。

### 分析
由于操作有覆盖性质，正着考虑不方便，所以倒着考虑执行顺序。

我们可以将每种操作分为四个类别：$(+2,+2),(+1,+1),(+1,+2),(+2,+1)$。

显然把 $(+2,+2)$ 的操作放在最前面执行、将 $(+1,+1)$ 的操作放在最后面执行是最优的，问题在于如何决定 $(+1,+2),(+2,+1)$ 两种操作之间的顺序。为了方便将 $(+2,+1)$ 操作的 $l_i,r_i$ 交换一下转变为 $(+1,+2)$ 操作来考虑。

考虑有两个 $(+1,+2)$ 操作，设它们分别对 $(x_i,y_i),(z_i,w_i)$ 执行。

如果出现 $x_i,y_i,z_i,w_i$ 两两不同或者 $x_i=z_i$ 或者 $y_i=w_i$ 的情况，那么这两个操作之间顺序是什么都不会影响最终结果。换句话说，这两个操作之间没有什么关系。

但如果出现 $y_i=z_i$ 或者 $x_i=w_i$ 的情况，我们就需要讨论一下两个操作的先后顺序了。不妨设 $y_i=z_i$，此时若先执行 $(x_i,y_i)$，$a_{y_i}$ 会变成 $2$，然后执行 $(z_i,w_i)$，由于 $a_{y_i}$ 已经被赋值，所以 $a_{z_i}\leftarrow 1$ 操作无效，此时答案更优。

考虑构建图论模型，将 $x_i\rightarrow y_i$ 连边，那么以上执行顺序在图中就可以表述为 $x_i\rightarrow y_i(=z_i)\rightarrow w_i$，这样，一条路径中除了起点会被赋值为 $1$，剩下的点都会被赋值为 $2$。

将原图缩点，那么在一个 SCC 中的点，只要随便令其中一个点为起点，就可以让整个 SCC 的所有其他点都被赋值为 $2$，而且还可以传到其他的它所连接的 SCC 中。

那我们令哪些点为起点呢？

首先，对于一个有入边的 SCC，只要任意一个直接或间接连接它的 SCC 中有一个起点，那么该 SCC 就能完全被 $2$ 覆盖。所以我们一定在没有入边的 SCC 中选点。

由于我们最先执行了 $(+2,+2)$ 操作，而若将已经赋好值的点设为起点，该点的值不会被改变，所以我们要尽可能选择已经执行过 $(+2,+2)$ 操作的点。如果没有，那只能任选一个点作为起点了。注意特判不会执行任何操作的点，让它们的值保持为 $0$。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<map>
#include<unordered_map>
#include<vector>
#include<queue>
#include<bitset>
#include<set>
#include<ctime>
#include<random>
#define P__ puts("")
#define pb emplace_back
#define rep(a,b,c) for(int a=(b);a<=(c);a++)
#define graph(i,j,k,l) for(int i=k[j];i;i=l[i].nxt)
using namespace std;
inline int rd(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;
}
inline void write(int x,char ch='\0'){
	if(x<0){x=-x;putchar('-');}
	int y=0;char z[40];
	while(x||!y){z[y++]=x%10+48;x/=10;}
	while(y--)putchar(z[y]);if(ch!='\0')putchar(ch);
}
bool Mbg;
const int maxn=5e5+5,maxm=4e5+5,inf=0x3f3f3f3f;
const long long llinf=0x3f3f3f3f3f3f3f3f;
int n,m;
struct edge{
	int to,nxt,id;
}a[maxn];
int head[maxn],edges;
int u[maxn],v[maxn],tot;
void add_edge(int x,int y,int z){
	u[++tot]=x,v[tot]=y;
	a[++edges]=(edge){y,head[x],z};
	head[x]=edges;
}
int col[maxn];
vector<int>ve[maxn];
vector<int>a22,a11;
int dfn[maxn],low[maxn],sta[maxn],tp,dfncnt;
int scc[maxn],sc;
bool in[maxn];
bool vis[maxn];
void tarjan(int x){
	dfn[x]=low[x]=++dfncnt,sta[++tp]=x,vis[x]=1;
	graph(i,x,head,a){
		int u=a[i].to;
		if(!dfn[u])tarjan(u),low[x]=min(low[x],low[u]);
		else if(vis[u])low[x]=min(low[x],dfn[u]);
	}
	if(dfn[x]==low[x]){
		++sc;int y;
		do{y=sta[tp--];vis[y]=0,scc[y]=sc,ve[sc].pb(y);}while(x^y);
	}
}
void dfs(int x,int c){
	col[x]=max(col[x],c),vis[x]=1;
	graph(i,x,head,a){
		int u=a[i].to;a22.pb(a[i].id);
		if(!vis[u])dfs(u,2);
	}
}
void init(){
	edges=dfncnt=tp=tot=sc=0;
	rep(i,1,n)head[i]=dfn[i]=low[i]=vis[i]=col[i]=scc[i]=in[i]=0;
	rep(i,1,n)ve[i].clear();a22.clear(),a11.clear();
}
void solve_the_problem(){
	n=rd(),m=rd();init();
	rep(i,1,m){
		int x=rd(),y=rd(),z=rd(),w=rd();
		col[x]=max(col[x],1),col[z]=max(col[z],1);
		if(y==1&&w==1)a11.pb(i);
		else if(y==2&&w==2)a22.pb(i),col[x]=2,col[z]=2;
		else{if(y>w)swap(x,z);add_edge(x,z,i);}
	}
	rep(i,1,n)if(!dfn[i])tarjan(i);
	rep(i,1,n)vis[i]=0;
	rep(i,1,tot)if(scc[u[i]]^scc[v[i]])in[scc[v[i]]]=1;
	rep(i,1,n)if(!in[scc[i]]&&col[i]==2&&!vis[i])dfs(i,2);
	rep(i,1,n)if(!in[scc[i]]&&col[i]==1&&!vis[i])dfs(i,1);
	int ans=0;rep(i,1,n)ans+=col[i];
	for(int u:a11)a22.pb(u);
	write(ans,10);
	reverse(a22.begin(),a22.end());
	for(int i:a22)write(i,32);P__;
}
bool Med;
signed main(){
	int _=rd();while(_--)solve_the_problem();
}
/*
1
6 10
1 1 2 1
1 1 1 1
5 1 1 2
2 2 5 1
3 1 4 2
3 2 1 2
6 1 2 2
1 1 2 2
3 2 2 1
3 2 4 2
answer:10
貌似能卡掉某篇题解
*/
```


---

## 作者：Graphcity (赞：1)

考虑倒序操作，这样在一次操作中确定的数到后面就不会再改变了。

我们把一组操作 $(l,r,x,y)$ 设为 $l,r$ 之间权值为 $(x,y)$ 的一条边。

对于权值为 $(2,2)$ 的边，肯定能选则选。对于权值为 $(1,2)$ 或 $(2,1)$ 的边，我们给它定向，方向为权值为 1 的一端连向权值为 2 的一端。对于权值为 $(1,1)$ 的边，肯定最后再选，可以先把它们删掉。

我们给当前已经确定点权为 2 的点打上标记。如果一条 $(1,2)$ 的边 1 那一端打上了标记，这条边连了肯定最优，同时给 2 那一端的点打上标记。依次类推，可以用类似 dfs 的方式把所有权值能够为 2 的点都打上标记。

接下来把这些点删掉。剩下的边肯定只有 $(1,2)$ 组成的有向边。我们可以以 **让一个点权值为 1 的代价** 使得从它出去能够到达的点权值都变成 2。将这张图缩点，我们肯定选择所有入度为 0 的点最优。

至于剩下的边，想怎么连怎么连。根据操作序列可以推出最终的答案。时间复杂度 $O(n+m)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=5e5;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int T,n,m,vis[Maxn+5],col[Maxn+5],deg[Maxn+5],tmp,cur,all;
int dfn[Maxn+5],low[Maxn+5],st[Maxn+5],a[Maxn+5],chk[Maxn+5],top;
struct Link{int l,x,r,y;} h[Maxn+5];
vector<pair<int,int>> v[Maxn+5];
vector<int> ans;

inline void dfs0(int x)
{
    for(auto [y,id]:v[x]) if(!vis[y])
        vis[y]=1,ans.push_back(id),dfs0(y);
}
inline void Tarjan(int x)
{
    dfn[x]=low[x]=++cur,chk[x]=1,st[++top]=x;
    for(auto [y,id]:v[x])
    {
        if(!dfn[y]) Tarjan(y),low[x]=min(low[x],low[y]);
        else if(chk[y]) low[x]=min(low[x],dfn[y]);
    }
    if(dfn[x]==low[x]) {++tmp; while(1) {int y=st[top--];
        chk[y]=0,col[y]=tmp; if(x==y) break;}}
}
inline void Clear()
{
    vector<int>().swap(ans);
    For(i,1,n) vector<pair<int,int>>().swap(v[i]);
    For(i,1,n) dfn[i]=low[i]=a[i]=vis[i]=col[i]=deg[i]=0;
    For(i,1,m) chk[i]=0;
    tmp=cur=all=top=0;
}
inline void Solve()
{
    n=read(),m=read();
    For(i,1,m) h[i].l=read(),h[i].x=read(),h[i].r=read(),h[i].y=read();
    For(i,1,m)
    {
        int l=h[i].l,r=h[i].r,x=h[i].x,y=h[i].y;
        if(x==1 && y==2) v[l].emplace_back(r,i);
        if(x==2 && y==1) v[r].emplace_back(l,i);
    }
    For(i,1,m) if(h[i].x==2 && h[i].y==2)
    {
        ans.push_back(i); int x=h[i].l,y=h[i].r;
        if(!vis[x]) vis[x]=1,dfs0(x);
        if(!vis[y]) vis[y]=1,dfs0(y);
    }
    For(i,1,n) vector<pair<int,int>>().swap(v[i]);
    For(i,1,m)
    {
        int l=h[i].l,r=h[i].r,x=h[i].x,y=h[i].y;
        if(vis[l] || vis[r]) continue;
        if(x==1 && y==2) v[l].emplace_back(r,i);
        if(x==2 && y==1) v[r].emplace_back(l,i);
    }
    For(i,1,n) if(!vis[i] && !dfn[i]) Tarjan(i);
    For(i,1,n) for(auto [j,id]:v[i]) if(col[i]!=col[j]) deg[col[j]]++;
    For(i,1,n) if(!vis[i] && deg[col[i]]==0) vis[i]=1,dfs0(i);
    For(i,1,n) chk[i]=0;
    for(auto i:ans) chk[i]=1;
    For(i,1,m) if(!chk[i]) ans.push_back(i);
    reverse(ans.begin(),ans.end());
    for(auto id:ans)
    {
        int x=h[id].x,y=h[id].y,l=h[id].l,r=h[id].r;
        a[l]=x,a[r]=y;
    }
    For(i,1,n) all+=a[i]; printf("%d\n",all);
    for(auto i:ans) printf("%d ",i); printf("\n");
    Clear();
}

int main()
{
    T=read();
    while(T--) Solve();
    return 0;
}
```



---

## 作者：Ydoc770 (赞：0)

### [Luogu P9697 [GDCPC 2023] Canvas](https://www.luogu.com.cn/problem/P9697)
图论建模好题。

注意值域 $x,y\in\{1,2\}$。

正向考虑，后面的操作会覆盖前面的，意味着后面的操作为 $2$，前面的操作为 $1$ 一定是不劣的。那么 $(l=1,r=1)$ 操作和 $(l=2,r=2)$ 操作的顺序就搞定了。现在考虑怎么执行 $(l=1,r=2)$ 与 $(l=2,r=1)$ 使得答案最优。

对于考虑执行 $(u=2,v=1)$ 和 $(v=2,w=1)$ 操作的顺序，明显先执行前者更优，因为后者 $v=2$ 覆盖了 $v=1$。 

这意味着，我们以选定的一个操作 $(s=2,t=1)$ 作为开始，后面的一系列操作顺序都是确定好的，一定是上一次操作 $t=1$，下一次操作 $t=2$ 更优。这种单向确定的关系可以直接用有向边 $(s,t)$ 来表示，一条有向路径就是最优的操作顺序。

但是操作的最优顺序所构成的不仅仅只是有向路径，而是构成了一个一般的有向图。这个有向图由若干强连通分量构成，每个强连通分量都蕴含其中任何一个操作作为开始都可以让除了最后一个点的每个点被赋值为 $2$。这时候最优的操作顺序就是使最后一个点存在 $(l=2,r=2)$ 操作将其赋值为 $2$ 的。

但是最后一个点不好维护，所以将前面所有的建边反向，认为所有 $(l=1,r=2)$ 操作表示 $l$ 向 $r$ 连了一条有向边，就转换为找到一个存在操作 $(l=2,r=2)$ 覆盖的点作为开始，按顺序将这个强连通分量的每个点加入操作序列中。记得加完之后对操作序列进行翻转还原。

最后一个问题是强连通分量彼此之间以什么样的顺序遍历？这个有向图由若干 DAG 构成，对于每个 DAG，由一个点开始要可以遍历整个 DAG，这个点显然应该属于 DAG 中入度为 $0$ 的强连通分量。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 10;
int T, n, m, a[maxn]; int cnt1, now, sum, pre[maxn], ord[maxn]; bool is2[maxn];
struct OPT{int l, x, r, y;} opt[maxn];

int d[maxn];
int tot, h[maxn];
struct edge{int u, v, nxt, id;} e[maxn];
void add(int u, int v, int id) {e[++tot].id = id, e[tot].u = u, e[tot].v = v, e[tot].nxt = h[u], h[u] = tot; return;}

int cnts, bl[maxn];
int cnt, dfn[maxn], low[maxn]; bool ins[maxn]; stack<int> s;
void tarjan(int u) {
	dfn[u] = low[u] = cnt++, s.push(u), ins[u] = true;
	for(int i = h[u], v; i; i = e[i].nxt) {
		v = e[i].v;
		if(!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if(ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if(low[u] == dfn[u]) {
		cnts++;
		for(int v = 0; v != u; ins[v] = false) v = s.top(), s.pop(), bl[v] = cnts;
	} return;
}

bool vis[maxn];
void dfs(int u) {
	vis[u] = true;
	for(int i = h[u], v, id; i; i = e[i].nxt) {
		v = e[i].v, id = e[i].id;
		ord[++now] = id; if(!vis[v]) dfs(v);
	} return;
}

void solve() {
	cin >> n >> m;
	for(int i = 1, l, x, r, y; i <= m; i++) {
		cin >> l >> x >> r >> y;
		if((x + y) == 4) is2[l] = is2[r] = true, ord[++now] = i;
		if((x + y) == 3) (x == 1) ? add(l, r, i) : add(r, l, i);
		opt[i].l = l, opt[i].x = x, opt[i].r = r, opt[i].y = y;
	}

	for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(i);
	for(int i = 1, u, v; i <= tot; i++) {u = e[i].u, v = e[i].v; if(bl[u] != bl[v]) d[bl[v]]++;}
	for(int i = 1; i <= n; i++) if(!d[bl[i]] && !vis[i] && is2[i]) dfs(i);
	for(int i = 1; i <= n; i++) if(!d[bl[i]] && !vis[i]) dfs(i);
	
	for(int i = 1; i <= m; i++) if((opt[i].x + opt[i].y) == 2) ord[++now] = i;
	for(int i = now; i >= 1; i--) a[opt[ord[i]].l] = opt[ord[i]].x, a[opt[ord[i]].r] = opt[ord[i]].y;
	
	for(int i = 1; i <= n; i++) sum += a[i];
	cout << sum << endl;
	for(int i = now; i >= 1; i--) cout << ord[i] << ((i ^ 1) ? " " : "\n");
	return;
}

void clean() {
	for(int i = 1; i <= n; i++) h[i] = dfn[i] = low[i] = d[i] = bl[i] = ord[i] = pre[i] = a[i] = is2[i] = vis[i] = 0;
	sum = cnt = cnts = tot = now = cnt1 = 0;
	return;
}

int main() {
	ios :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
	
	cin >> T;
	while(T--) solve(), clean();
	
	return 0;
} 
```

---

## 作者：JPGOJCZX (赞：0)

节选自：[图论做题记录（三）（2025.5.24 - 2025.31）](https://www.luogu.com.cn/article/2xi85b8k)

[安利一下我的博客](https://www.cnblogs.com/JPGOJCZX/p/18904011)

首先，后面的操作可能会覆盖掉前面的操作，这很不好做，于是我们考虑倒着来考虑，一旦一个操作执行了，那么对应的 $l_i$ 和 $r_i$ 位置的数就一定是 $x_i$ 和 $y_i$ 了，后续所有操作均是在倒序下的，最终把答案倒着数出来就可以了。

一个显然的贪心就是，最开始执行所有 $(l_i, 2, r_i, 2)$ 操作，最后执行所有 $(l_i, 1, r_i, 1)$ 操作。那么现在我们需要处理的就是 $(l_i, 1, r_i, 2)$ 操作和 $(l_i, 2, r_i, 1)$ 操作的顺序。其实这两种操作是一样的，对于 $(l_i, 2, r_i, 1)$ 操作，我们交换 $l_i$ 和 $r_i$，此时就只有 $(l_i, 1, r_i, 2)$ 操作了。我们考虑到，如果若干个修改长成如图所示的样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/9v14z5ku.png)

也就是每个操作的 $l_i$ 节点正好是某个操作的 $r_i$ 节点，那么除了 $l_1$ 这个点，其它所有点都可以被赋值成 $2$，因此，我们从 $l_i$ 向 $r_i$ 连一条有向边，然后将这个图缩点，那么每个强连通分量中，除了入度为 $0$ 的这个点，其它所有点都会被赋值成 $2$。我们在建图时，直接把边权赋值成操作编号，然后 DFS 一遍就可以确定顺序了。

最后还有一点，如果某个强连通分量中有一个点 $u$ 被包含在了某个 $(u, 2, v, 2)$ 中，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/6ncg7rig.png)

（图中红色的就是 $(u, 2, v, 2)$ 操作）

那么从 $u$ 点开始一定更优，因为这样就可以使整个强连通分量中的点都变成 $2$。那么现在所有情况都讨论完了，于是我们用 $O(n)$ 的时间复杂度解决了这道题目。

完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 9;
struct Edge{
	int v, w, nex;
} e[N << 1];
int head[N], ecnt;
void addEdge(int u, int v, int w){
	e[++ecnt] = Edge{v, w, head[u]};
	head[u] = ecnt;
}
struct edge{
	int u, v;
} E[N];
int l[N], r[N], x[N], y[N], beg[N], deg[N], a[N], cnt, tot, n, m, T;
int low[N], dfn[N], scc[N], sc, dfncnt;
stack <int> s;
bool ins[N], vis[N];
vector <int> ans;
void tarjan(int u){
	low[u] = dfn[u] = ++dfncnt;
	s.push(u);
	ins[u] = true;
	for(int i = head[u]; i; i = e[i].nex){
		int &v = e[i].v;
		if(!dfn[v]){
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if(ins[v])
			low[u] = min(low[u], dfn[v]);
	}
	if(low[u] == dfn[u]){
		++sc;
		while(s.top() != u){
			scc[s.top()] = sc;
			ins[s.top()] = 0;
			s.pop();
		}
		scc[s.top()] = sc;
		ins[s.top()] = 0;
		s.pop();
	}
}
void dfs(int u){
    vis[u] = true;
    for(int i = head[u]; i; i = e[i].nex){
        int v = e[i].v;
        ans.push_back(e[i].w);
        if(vis[v])
            continue;
        dfs(v);
    }
}
void init(){
    memset(head, 0, sizeof(head));
    memset(beg, 0, sizeof(beg));
    memset(deg, 0, sizeof(deg));
    memset(low, 0, sizeof(low));
    memset(dfn, 0, sizeof(dfn));
    memset(scc, 0, sizeof(scc));
    memset(vis, 0, sizeof(vis));
    memset(a, 0, sizeof(a));
    ans.clear();
    ecnt = cnt = tot = sc = dfncnt = 0;
}
int main(){
    scanf("%d", &T);
    while(T--){
        init();
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= m; i++){
            scanf("%d%d%d%d", &l[i], &x[i], &r[i], &y[i]);
            if(x[i] == 2 && y[i] == 1){
                swap(x[i], y[i]);
                swap(l[i], r[i]);
                E[++tot] = edge{l[i], r[i]};
                addEdge(l[i], r[i], i);
            } else if(x[i] == 1 && y[i] == 2){
                E[++tot] = edge{l[i], r[i]};
                addEdge(l[i], r[i], i);
            } else if(x[i] == 2 && y[i] == 2){
                beg[++cnt] = l[i], beg[++cnt] = r[i];
                ans.push_back(i);
            }
        }
        for(int i = 1; i <= n; i++){
            if(!dfn[i]){
                dfncnt = 0;
                tarjan(i);
            }
        }
        for(int i = 1; i <= tot; i++){
            int u = E[i].u, v = E[i].v;
            if(scc[u] != scc[v])
                deg[scc[v]]++;
        }
        for(int i = 1; i <= cnt; i++)
            if(!deg[scc[beg[i]]] && !vis[beg[i]])
                dfs(beg[i]);
        for(int i = 1; i <= n; i++)
            if(!deg[scc[i]] && !vis[i])
                dfs(i);
        for(int i = 1; i <= m; i++)
            if(x[i] == 1 && y[i] == 1)
                ans.push_back(i);
        for(int i = ans.size() - 1; i >= 0; i--)
            a[l[ans[i]]] = x[ans[i]], a[r[ans[i]]] = y[ans[i]];
        int res = 0;
        for(int i = 1; i <= n; i++)
            res += a[i];
        printf("%d\n", res);
        for(int i = ans.size() - 1; i >= 0; i--)
            printf("%d ", ans[i]);
        printf("\n");
    }
	return 0;
}
```

---

## 作者：all_for_god (赞：0)

[P9697 \[GDCPC 2023\] Canvas](https://www.luogu.com.cn/problem/P9697)

## 思路

考虑后面的操作会覆盖掉前面的操作，因此我们考虑倒序来做。这样被操作过的点就一定不会再改变了。
注意接下来的叙述都是倒过来了的，“前” 变成了后，“后” 变成了前。

考虑形如 $(x,2,y,2)$ 的操作一定最先做，$(x,1,y,1)$ 的操作一定最后做。因此只需要判断形如 $(x,1,y,2)$ 的操作的顺序。
发现如果有两个操作形如 $(x,1,y,2),(y,1,z,2)$，那么前一个操作一定先做。（再次注意是倒序考虑，被赋值过的点一定不会变了）

那这个就形成了一个类似于有向边的关系。
我们将序列上的位置看做点，赋值的操作看成边，那么走边就代表操作。如操作 $(x,1,y,2)$ 就会使 $x$ 向 $y$ 连边。
由于图上只有形如 $(x,1,y,2)$ 的操作，因此入度为 0 的点的最终答案会是 1，其他所有有入度的点的答案都会是 2。

因此我们考虑将强联通分量给缩起来，从入度为 0 的点开始 dfs 即可。每走过一条边就将这条边所对应的操作压入栈中。
但是由于还有形如 $(x,2,y,2)$ 的操作，因此我们优先从被这种操作标记过的点且入度为 0 的点开始 dfs。

最后统计答案是简单的模拟即可。

## code

注意建出来的图不一定连通。
在代码实现上，我们并不需要真正将缩点后的图建出来。具体而言，扫两遍序列。第一次只从被标记一定为 2 且入度为 0 的点开始 dfs。第二次从任意入度为 0 的点开始 dfs。

而统计答案并不需要在 dfs 的时候统计。由于我们已经得到了操作的顺序，因此我们可以直接暴力模拟操作的过程统计答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+7;
#define pii pair <int,int>
#define mp make_pair
int n,m,ans=0,sign[N],tot[N],top,stk[N],dfn[N],low[N],vis[N],dfncnt=0,blockcnt=0,bel[N],du[N],t[N],cnt=0,a[N];
vector <pii> q[N];vector <int> scc[N];
struct node{int u,x,v,y;}que[N];
void init(){
	for(int i=1;i<=n;i++) sign[i]=tot[i]=vis[i]=dfn[i]=bel[i]=a[i]=0,q[i].clear();
	for(int i=1;i<=blockcnt;i++)scc[i].clear(),du[i]=0;
	top=dfncnt=blockcnt=cnt=0;
}
void tar(int u){
	dfn[u]=low[u]=++dfncnt;vis[u]=1;stk[++top]=u;
	for(int i=0;i<tot[u];i++){
		int v=q[u][i].first; //注意由于是无向图不应该考虑父亲 
		if(!dfn[v]){tar(v);low[u]=min(low[v],low[u]);}
		else if(vis[v])low[u]=min(dfn[v],low[u]);
	}
	if(dfn[u]==low[u]){
		++blockcnt;
		do{
			scc[blockcnt].push_back(stk[top]);vis[stk[top]]=0;
			bel[stk[top]]=blockcnt;
		}
		while(stk[top--]!=u);
	}
}
void dfs(int u){
	vis[u]=1;
	for(int i=0;i<tot[u];i++){
		int v=q[u][i].first,id=q[u][i].second;
		t[++cnt]=id;if(!vis[v])dfs(v);
	}
}
void solve(){
	cin>>n>>m;
	for(int i=1,u,v,x,y;i<=m;i++){
		cin>>u>>x>>v>>y;if(x>y)swap(u,v),swap(x,y);que[i]={u,x,v,y};
		if(x==1&&y==2) q[u].push_back(mp(v,i)),tot[u]++;
		if(x==2) sign[u]=sign[v]=1,t[++cnt]=i;
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tar(i);
	for(int u=1;u<=n;u++){for(int i=0;i<tot[u];i++){int v=q[u][i].first;if(bel[v]!=bel[u])du[bel[v]]++;}}
	for(int i=1;i<=n;i++){if((!du[bel[i]])&&sign[i]&&(!vis[i]))dfs(i);}           //优先考虑有被形如 (x,2,y,2) 操作的点的强联通分量
	for(int i=1;i<=n;i++){if((!vis[i])&&(!du[bel[i]]))dfs(i);}
	for(int i=1;i<=m;i++) if(que[i].x+que[i].y==2)t[++cnt]=i;
	for(int i=cnt;i>=1;i--) a[que[t[i]].u]=que[t[i]].x,a[que[t[i]].v]=que[t[i]].y;//模拟操作
	int ans=0;
	for(int i=1;i<=n;i++) ans+=a[i];
	cout<<ans<<'\n';
	for(int i=cnt;i>=1;i--){cout<<t[i]<<' ';}cout<<'\n';
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int T;cin>>T;while(T--) init(),solve();
	return 0;
} 
```

---

## 作者：zhanglh (赞：0)

可以发现，之后进行的操作会将之前的操作覆盖，不好处理。假设时光倒流：一个位置一旦被覆盖后，就不会再改变了。最后倒序输出操作序列就是答案了。

$1 \le x_i, y_i \le 2$。显然有 $x_i = y_i = 2$ 的操作要先于 $x_i = y_i = 1$ 的。下面考虑 $x_i \not= y_i$ 的操作。

假设有操作 $(a, 1, b, 2)$ 和 $(b, 1, c, 2)$，则会先操作 $(a, 1, b, 2)$，这样 $b$ 的值就固定为 $2$，更优。由此想到建图，从变为 $1$ 的点向变为 $2$ 的点连有向边。

建图之后缩点。不难发现，入度为 $0$ 的 SCC 最多有一个点的最终取值为 $1$，其余均为 $2$。注意，对于入度为 $0$ 且包含 $x_i = y_i = 2$ 的 SCC，要优先选择 $x_i = y_i = 2$ 的操作，以使得全部点的取值均为 $2$。此为最优解。

```
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int N = 500010;

int n, m, a[N], l[N], x[N], r[N], y[N];
vector<pii> e[N];
int dfn[N], low[N], scc[N], stk[N], in[N], cnt, top, tot;
bool vis[N];
vector<int> ans;

void init() {
    for (int i = 1; i <= n; i++) {
        a[i] = 0;
        dfn[i] = 0;
        low[i] = 0;
        scc[i] = 0;
        in[i] = 0;
        vis[i] = 0;
        e[i].clear();
    }
    cnt = 0;
    top = 0;
    tot = 0;
    ans.clear();
}

void tarjan(int u) {
    dfn[u] = low[u] = ++tot;
    stk[++top] = u;

    for (pii i : e[u]) {
        int v = i.first;
        if (dfn[v] == 0) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (scc[v] == 0) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        cnt++;
        int node;
        do {
            node = stk[top--];
            scc[node] = cnt;
        } while (u != node);
    }
}

void dfs(int u) {
    if (vis[u] == true) return;
    vis[u] = true;
    for (pii i : e[u]) {
        ans.push_back(i.second);
        dfs(i.first);
    }
}

void solve() {
    cin >> n >> m;
    init();

    for (int i = 1; i <= m; i++) {
        cin >> l[i] >> x[i] >> r[i] >> y[i];
        if (x[i] == 1 && y[i] == 2) {
            e[l[i]].push_back({r[i], i});
        } else if (x[i] == 2 && y[i] == 1) {
            swap(x[i], y[i]);
            swap(l[i], r[i]);
            e[l[i]].push_back({r[i], i});
        }
    }

    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) tarjan(i);
    }

    for (int i = 1; i <= m; i++) {
        if (x[i] == 2 && y[i] == 2) ans.push_back(i);
    }

    for (int i = 1; i <= m; i++) {
        if (x[i] == 1 && y[i] == 2) {
            if (scc[l[i]] ^ scc[r[i]]) in[scc[r[i]]]++;
        }
    }

    for (int i = 1; i <= m; i++) {
        if (x[i] == 2 && y[i] == 2) {
            if (in[scc[l[i]]] == 0) dfs(l[i]);
            if (in[scc[r[i]]] == 0) dfs(r[i]);
        }
    }
    
    for (int i = 1; i <= n; i++) {
        if (in[scc[i]] == 0) dfs(i);
    }

    for (int i = 1; i <= m; i++) {
        if (x[i] == 1 && y[i] == 1) ans.push_back(i);
    }

    reverse(ans.begin(), ans.end());
    for (int i : ans) {
        a[l[i]] = x[i];
        a[r[i]] = y[i];
    }

    ll sum = 0;
    for (int i = 1; i <= n; i++) sum += a[i];
    
    cout << sum << "\n";
    for (int i : ans) cout << i << " ";
    cout << "\n";
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--) solve();

    return 0;
}

```

---

## 作者：_fairytale_ (赞：0)

>深净的蓝色天空 一切明丽得悲恸
>
>热烈的太阳与风 心脏都隐隐作痛
>
>直似透明的梧桐 光斑泼洒在地 有热气浮动
>
>在约定好地点 你挥手 背后草木葱茏

发现操作是覆盖，所以考虑时光倒流，一个点被赋值之后就不会变了。

$x=y$ 的情况是简单的。$x=y=1$ 都放在最后，$x=y=2$ 都放在最前面。

又因为 $l,r$ 是可以 swap 的，所以只需考虑 $x=1,y=2$ 的情况。

从 $x$ 向 $y$ 连边，考察这个图中一个 SCC 的性质。你发现对于一个 SCC，选定一个起点，可以把除它以外的所有点的权值全部变成 $2$！所以我们缩点，权值可能为 $1$ 的点只有入度为 $0$ 的 SCC 中的一个点，且这个点可以在 SCC 中任取。所以我们优先取被 $x=y=2$ 的操作提前覆盖好的点，没有就任取一个。

```cpp
#include<bits/stdc++.h>
bool Mst;
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define rep(x,qwq,qaq) for(int x=(qwq);x<=(qaq);++x)
#define per(x,qwq,qaq) for(int x=(qwq);x>=(qaq);--x)
using namespace std;
template<class _T>
void ckmax(_T &x,_T y){
	x=max(x,y);
}
template<class _T>
void ckmin(_T &x,_T y){
	x=min(x,y);
}
#define maxn 501000
int n,m,k;
int ans[maxn];
vector<pii>g[maxn];
int stac[maxn],top;
int low[maxn],dfn[maxn],tim;
bool ins[maxn],vis[maxn];
int scc[maxn],tot;
bool zr[maxn];
int val[maxn];
int l,r;
void clr(){
	l=0,r=m+1;
	rep(i,1,n)g[i].clear();
	tim=top=tot=0;
	rep(i,1,n)zr[i]=1;
	rep(i,1,n)val[i]=0;
	rep(i,1,n)vis[i]=0;
	rep(i,1,n)dfn[i]=0;
}
void tarjan(int u){
	dfn[u]=low[u]=++tim;
	stac[++top]=u;
	ins[u]=1;
	for(pii t:g[u]){
		int v=t.fi;
		if(!dfn[v]){
			tarjan(v);
			ckmin(low[u],low[v]);
		}
		else if(ins[v])ckmin(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
	    ++tot;
	    while(1){
	    	int x=stac[top--];
	    	ins[x]=0,scc[x]=tot;
	    	if(x==u)break;
		}
	}
}
void dfs(int u){
	if(vis[u]==1)return;
    vis[u]=1;
	if(g[u].size()==0)return;
	ckmax(val[u],1);
	for(pii t:g[u]){
    	int v=t.fi,i=t.se;
    	ans[--r]=i;
    	if(!vis[v])val[v]=2;
    	dfs(v);
	}
}
void Solve_(){
    cin>>n>>m;
    clr();
    for(int i=1,u,v,x,y;i<=m;++i){
    	cin>>u>>x>>v>>y;
    	if(x==2&&y==2)ans[--r]=i,val[u]=val[v]=2;
    	else if(x==1&&y==1)ans[++l]=i,ckmax(val[u],1),ckmax(val[v],1);
    	else{
    		if(x==2)swap(u,v);
    		g[u].pb({v,i});
		}
	}
	rep(i,1,n)if(!dfn[i])tarjan(i);
	rep(i,1,n){
		for(pii t:g[i]){
			int j=t.fi;
			if(scc[i]!=scc[j])zr[scc[j]]=0;
		}
	}
	rep(i,1,n)if(zr[scc[i]]==1&&val[i]==2)dfs(i);
	rep(i,1,n)if(zr[scc[i]]==1)dfs(i);
    cout<<accumulate(val+1,val+n+1,0)<<'\n';
    assert(l+1==r);
    rep(i,1,m)cout<<ans[i]<<" \n"[i==m];
}
bool Med;
signed main() {
	cerr<<(&Mst-&Med)/1024.0/1024.0<<" MB\n";
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    int Testcases=1;
    cin>>Testcases;
    while(Testcases--)Solve_();
	return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

题解摘自[做题记录](https://www.luogu.com.cn/article/7iw3x35p)。

### 分析

注意到 $1 \le x_i,y_i \le 2$，说明只会有：$(1,1),(2,2),(1,2),(2,1)$ 这 $4$ 种覆盖情况。

考虑时光倒流，那么对于 $(2,2)$ 这种覆盖，优先操作是不劣的；对于 $(1,1)$ 这种覆盖，优先操作是不优的。那么我们可以先把所有的 $(2,2)$ 操作做了，再在解决 $(1,2)$ 和 $(2,1)$ 操作后做 $(1,1)$ 操作。

现在考虑解决 $(1,2)$ 和 $(2,1)$ 两个操作。不难发现这俩是等价的，因为我们可以通过交换 $(2,1)$ 操作的 $l,r$ 得到 $(1,2)$ 操作。所以只需要求 $(1,2)$ 操作的最优方案了。注意到，当我们有：$l_i=x,r_i=y,l_j=y,r_j=z$，先操作 $i$ 再操作 $j$ 可以得到 $y$ 必定是 $2$。那么我们将所有的 $l_i$ 连向 $r_i$，得到一个有向图。则在这个图上的任意一个强连通分量，都能满足其**最多**只有 $1$ 个点为 $1$。缩点之后跑拓扑就行了。时间复杂度 $O(n+m)$。

### 代码

```cpp
il void solve(){
	n=rd,m=rd,clear();
	for(re int i=1;i<=m;++i){
		c[i]={rd,rd,rd,rd};
		if(c[i].x==2&&c[i].y==2) ans.push_back(i),flag[c[i].l]=flag[c[i].r]=1;
		else if(c[i].x==1&&c[i].y==1) ans_.push_back(i);
		else{
			if(c[i].x==2) swap(c[i].l,c[i].r);
			e[c[i].l].push_back({c[i].r,i});
		}
	}
	for(re int i=1;i<=n;++i) if(!dfn[i]) tj(i);
	for(re int u=1;u<=n;++u)
	for(auto i:e[u]){
		int v=i.x;
		d[col[v]]+=(col[u]!=col[v]);
	}
	for(re int i=1;i<=n;++i)
	if( flag[i]&&!Vis[i]&&!d[col[i]]) dfs(i);
	for(re int i=1;i<=n;++i)
	if(!flag[i]&&!Vis[i]&&!d[col[i]]) dfs(i);
	for(auto x:ans_) a[c[x].l]=a[c[x].r]=1;
	reverse(ans.begin(),ans.end());
	for(auto x:ans ){
		if(c[x].x==2&&c[x].y==2) a[c[x].l]=a[c[x].r]=2;
		else a[c[x].l]=1,a[c[x].r]=2;
	}	
    return print(),void(0);
}
```

---

## 作者：david0911 (赞：0)

由于后续操作可能覆盖前面的操作，这不好。时光倒流变成只有第一次操作有效。以下的顺序都是时光倒流之后的。

观察到赋值只会是 $1$ 或 $2$，首先所有将两个位置都赋值为 $2$ 的操作必定最先进行，将两个位置都赋值为 $1$ 的操作必定最后进行。现在只用考虑将一个赋值为 $1$，另一个赋值为 $2$ 的操作的顺序。

不妨记这样的一个操作为 $(u,v)$ 表示将 $u$ 赋值为 $1$ 并将 $v$ 赋值为 $2$。容易发现一旦执行了 $(u,v)$ 后，所有 $(v,*)$ 的操作都可以按任意顺序执行了。

图论建模，将 $(u,v)$ 视作一条有向边，那么上面的过程描述的其实是从 $u$ 出发的任意一条路径上，只有 $u$ 可能被赋值为 $1$，其他的点必然被赋值为 $2$。称这里的 $u$ 为起始点。

对图进行强连通分量缩点，显然只有入度为 $0$ 的强连通分量中才可能出现被赋值为 $1$ 的点。入度非 $0$ 的强连通分量中的每个点，必然有从入度为 $0$ 的强连通分量中的点到它的路径，所以一定会被赋值为 $2$。

对于入度为 $0$ 的强连通分量，优先选择已经被将两个点都赋值为 $2$ 的操作赋值过的点作为起始点。否则任意选一个点作为起始点均可。

简单 DFS 即可求得操作顺序。由于时光倒流，最后记得翻转一下。

时间复杂度 $O(n+m)$。

---

