# Two Arrays

## 题目描述

给定两个长度为 $n$ 的数组 $a$ 和 $b$。你可以无限次进行如下操作：

- 选择一个整数 $i$，其中 $1 \le i \le n$，交换 $a_i$ 和 $b_i$。

定义 $f(c)$ 为数组 $c$ 中不同数字的个数。请你求出 $f(a) + f(b)$ 的最大值，并输出所有操作后得到的数组 $a$ 和 $b$。

## 说明/提示

在第一个测试用例中，经过 $i=2$、$i=4$ 和 $i=5$ 三次操作后，可以得到 $a = [1, 3, 4, 5, 2]$，$b = [1, 2, 3, 4, 4]$。此时 $f(a) + f(b) = 5 + 4 = 9$。可以证明无法得到更大的答案。

在第二个测试用例中，经过操作后有 $f([2, 3, 4, 2, 1, 5, 6]) + f([1, 2, 3, 4, 5, 6, 5]) = 6 + 6 = 12$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
5
1 2 4 4 4
1 3 3 5 2
7
2 2 4 4 5 5 5
1 3 3 2 1 6 6
7
12 3 3 4 5 6 4
1 2 13 8 10 13 7```

### 输出

```
9
1 3 4 5 2 
1 2 3 4 4 
12
2 3 4 2 1 5 6 
1 2 3 4 5 6 5 
14
12 3 13 8 10 6 4 
1 2 3 4 5 13 7```

# 题解

## 作者：StayAlone (赞：7)

令 $cnt_i$ 表示 $i$ 的出现总次数，显然有答案上界 $\sum\min(cnt_i, 2)$。

可以构造性证明该上界可取。

考虑连双向边 $(a_i, b_i)$，给边定向。对于一条边 $(x, y)$，若定向为 $x\to y$，则答案为 $(x, y)$，否则答案为 $(y, x)$。

如此，问题转化成需要让所有非一度点都既有入边，又有出边。

一种较为直接的做法是：

- 对于一个存在一度点的连通块，以一度点为根，找出 dfs 树。对于树边，父亲指儿子；对于非树边，指向祖先。
- 否则，该连通块一定存在环。以环上任意一点为根，做同上的事情。

-----

还有一种办法。将条件转化为使得所有点的入度与出度之差不超过 $1$。

考虑将奇度点任意两两配对连边（奇度点有偶数个），使得新图存在欧拉回路。

按照欧拉回路的路径定向，再删除加上的边即可。

下面是第一种做法的实现。

[AC record](https://codeforces.com/contest/2113/submission/324590060)

```cpp
int n, a[MAXN], b[MAXN], vis[MAXN], cnt[MAXN], dfn[MAXN];
int ansx[MAXN], ansy[MAXN];
vector <pii> lnk[MAXN];

il void solve() {
    read(n); rer(i, 1, n, a); rer(i, 1, n, b);
    int ans = 0;
    rep1(i, 1, n) lnk[a[i]].eb(b[i], i), lnk[b[i]].eb(a[i], i), ++cnt[a[i]], ++cnt[b[i]];
    rep1(i, 1, n << 1) ans += min(2, cnt[i]);
    int stp = 0; vector <int> dot;
    auto froot = [&](auto self, int x, int pa) -> int {
        if (vis[x]) return x;
        vis[x] = 1; dot.eb(x);
        for (auto [v, id] : lnk[x]) if (id ^ pa) {
            int w = self(self, v, id);
            if (~w) return w;
        } return -1;
    };
    auto dfs = [&](auto self, int x) -> void {
        dfn[x] = ++stp; vis[x] = 1;
        for (auto [v, id] : lnk[x]) if (!vis[v]) {
            ansx[id] = x; ansy[id] = v; self(self, v);
        }
    };
    rep1(i, 1, n << 1) if (lnk[i].size() == 1 && !vis[i]) dfs(dfs, i);
    rep1(i, 1, n << 1) if (!vis[i]) {
        int rt = froot(froot, i, -1);
        for (auto v : dot) vis[v] = 0;
        dfs(dfs, rt); dot.clear();
    }
    rep1(i, 1, n) if (!ansx[i]) {
        ansx[i] = a[i], ansy[i] = b[i];
        if (dfn[a[i]] < dfn[b[i]]) swap(ansx[i], ansy[i]);
    } printf("%d\n", ans);
    rep1(i, 1, n) printf("%d ", ansx[i]); puts("");
    rep1(i, 1, n) printf("%d ", ansy[i]); puts("");
    rep1(i, 1, n << 1) lnk[i].clear(), cnt[i] = vis[i] = ansx[i] = 0;
}

int main() {
    for (int T = read(); T--; ) solve();
    return 0;
}
```

---

## 作者：tyr_04 (赞：5)

[传送门](https://www.luogu.com.cn/problem/CF2113F)

闲话：赛时卡 D 20min 无果后开了 F，吸取 [CF2097B](https://www.luogu.com.cn/problem/CF2097B) 和 [CF2110E](https://www.luogu.com.cn/problem/CF2110E) 的经验看到 $a,b$ 两种元素就想到建图，但感觉 D 更可做没有深入，~~最后喜提 ABC。~~

### 题意

给定两个数组 $a_{1 \sim n},b_{1 \sim n}$，保证 $1 \le a_{1 \sim n},b_{1 \sim n} \le 2n$，可以交换任意的 $a_{i},b_{i}$（$1 \le i \le n$），求 $f(a) + f(b)$ 的最大值，其中 $f(c)$ 表示数组 $c$ 中不同的元素个数。

### 思路

求出每种元素在 $a,b$ 中出现的次数，设元素 $i$ 出现的次数为 $sum_{i}$，显然无论进行任何交换 $f(a) + f(b)$ 的值一定小于等于 $\sum_{i = 1}^{2n} \min(2,sum_{i})$，我们思考能否构造一种方案使答案等于这个最大值。

考虑将任意的 $a_{i},b_{i}$ 连无向边，边的编号为 $i$，我们对每一条边定向，若第 $i$ 条边由 $x$ 指向 $y$，我们看作答案序列的 $a_{i} = x$，$b_{i} = y$。

问题转化为：给定一张无向图，将图上的每一条边定向，使得所有度数大于等于 $2$ 的点至少一条出边和一条入边。

对于每一个连通块，我们任意指定一个点作为根，dfs 遍历整张图（走过的点不再走），每个连通块经过的边构成了一棵 dfs 树。如果 dfs 树里**包含根节点的子树**的边按照**深度小的点通向深度大的点**（边的方向从上往下）或**深度大的点通向深度小的点**（边的方向从下往上）的方向定向，显然除了叶子节点和根节点以外其他的点都达到了构造目标。

由于这是一棵 dfs 树，一个点能作叶子节点当且仅当该点的边连向它的祖先，对于这种边，如果当前子树定向从上往下，该边作叶子节点出边（该边的方向从下往上）；如果当前子树定向从下往上，该边作叶子节点入边（该边的方向从上往下）。这样构造使得所有叶子节点也达到目标。

接下来就只剩根节点了。如果 dfs 树中某个深度大于 $2$ 的点与根节点有边，那么该点根据当前子树的定向方向相反（正好与叶子节点定向的方式契合）；如果没有，但根节点度数大于等于 $2$，即有两个以上**包含根节点且边互相独立的子树**，因此一棵子树从下往上，其它子树从上往下，保证根节点也出入至少一次；否则，根节点度数为 $1$。根节点也达到了构造目标，因此我们构造出了一种答案达到上界的方法。

总结：找出 dfs 树后，根据根节点之前搜过的树边条数确定该子树的定向方向（代码里以奇偶性区分），任何一条返祖边的方向都和该子树的定向方向相反（“相反”指**深度小的点通向深度大的点**变为**深度大的点通向深度小的点**，反之亦然），时间复杂度 $O(n)$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,s,ans,a[200005],b[200005],za[200005],sum[200005];
bool z[200005];
vector<pair<int,int> > v[200005];
void dfs(int x,int fa,int h)
{
	z[x]=1;
	for(int i=0;i<v[x].size();i++)
	{
		int y=v[x][i].first,id=v[x][i].second;
		if(za[id]==0)
		{
			if(x==s)
			{
				h++;
				h%=2;
			}
			if(h==1)
			{
				za[id]=x;
			}
			else
			{
				za[id]=y;
			}
			if(z[y]==0)
			{
				dfs(y,id,h);
			}
		}
	}
	return;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		ans=0;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			sum[a[i]]++;
		}
		for(int i=1;i<=n;i++)
		{
			cin>>b[i];
			sum[b[i]]++;
		}
		for(int i=1;i<=n;i++)
		{
			v[a[i]].push_back({b[i],i});
			v[b[i]].push_back({a[i],i});
		}
		for(int i=1;i<=2*n;i++)
		{
			ans+=min(sum[i],2ll);
			if(z[i]==0)
			{
				s=i;
				dfs(i,0,0);
			}
		}
		for(int i=1;i<=n;i++)
		{
			if(a[i]!=za[i])
			{
				swap(a[i],b[i]);
			}
		}
		cout<<ans<<'\n';
		for(int i=1;i<=n;i++)
		{
			cout<<a[i]<<' ';
		}
		cout<<'\n';
		for(int i=1;i<=n;i++)
		{
			cout<<b[i]<<' ';
		}
		cout<<'\n';
		for(int i=1;i<=2*n;i++)
		{
			v[i].clear();
			za[i]=0;
			z[i]=0;
			sum[i]=0;
		}
	}
	return 0;
}
```

---

## 作者：ddxrS_loves_zxr (赞：2)

这个题给出的限制很弱。

对于一个数，我们希望它在 $a$ 中和在 $b$ 中出现的次数尽可能接近。考虑将每一个 $a_i$ 和 $b_i$ 之间连一条边，然后给边定向为从 $x$ 到 $y$，那么我们把 $x$ 放到 $a$ 中，$y$ 放到 $b$ 中。

欧拉回路可以保证每个点的出度等于入度，但要求每个点的度数都是偶数。于是，对于度数不是偶数的点，我们新建一个虚点与它连边。这样子每个点的度数都是偶数，包括虚点（因为总度数是偶数）。跑完欧拉回路后，忽略虚点，每个点的出度与入度的差不会超过 $1$，也就是在 $a$ 中出现的次数和在 $b$ 中出现的次数不会超过 $1$。

令 $c_i$ 表示 $i$ 一共在 $a$ 和 $b$ 中出现的次数，那么对于所有 $c_i\ge 2$ 的 $i$ 它就可以在 $a$ 和 $b$ 中都出现。这种构造方案可以取到答案的上界 $\sum \min(2,c_i)$。

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 4e5 + 5;
int n, a[N], b[N], cnt[N], p[N], deg[N], pos[N], tot;
vector<pair<int, int> > E[N];
bool vis[N];
void dfs(int x) {
	while(!E[x].empty()) {
		int y = E[x].back().first, id = E[x].back().second; E[x].pop_back();
		if(vis[id]) continue;
		pos[id] = x, vis[id] = true;
		dfs(y); 
	}
}
void solve() {
	cin>>n; tot = 0;
	for(int i = 1; i <= n; i++) cin>>a[i], cnt[a[i]]++, deg[a[i]]++;
	for(int i = 1; i <= n; i++) cin>>b[i], cnt[b[i]]++, deg[b[i]]++;
	for(int i = 1; i <= n; i++) vis[++tot] = false, E[a[i]].push_back({b[i], tot}), E[b[i]].push_back({a[i], tot});
	for(int i = 1; i <= n + n; i++) if(deg[i] % 2 == 1) vis[++tot] = false, E[0].push_back({i, tot}), E[i].push_back({0, tot});
	for(int i = 0; i <= n + n; i++) dfs(i);
	int ans = 0;
	for(int i = 1; i <= n + n; i++) ans += min(cnt[i], 2), cnt[i] = 0;
	cout<<ans<<'\n';
	for(int i = 1; i <= n; i++) {
		int s = a[i] + b[i];
		a[i] = pos[i], b[i] = s - pos[i];
	}
	for(int i = 1; i <= n; i++) cout<<a[i]<<" \n"[i == n];
	for(int i = 1; i <= n; i++) cout<<b[i]<<" \n"[i == n];
	for(int i = 0; i <= n + n; i++) E[i].clear(), cnt[a[i]] = 0, deg[i] = 0;
}
int main() {
#ifdef ddxrS
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t; cin>>t;
	while(t--) solve();
    return 0;
}
```

---

## 作者：ax_by_c (赞：0)

翻某卷批的做题记录看到这题，居然秒了。为啥是 *2500 啊？可能是因为构造题个人差大。

一开始没看数据范围的话可能会以为是流子之类的东西，所以就会考虑将 $(a_i,b_i)$ 连边。（我反正是这么想到的）

那么就是要给这些边定向，答案就是既有入边又有出边的点数加上总点数。

对每个连通块考虑，容易发现一度点不可能既有入边又有出边。

如果有一度点，以一度点为根随便找一个 dfs 树并让所有树边指向父亲，返祖边全部指向后代，即可让所有二度点既有入边又有出边。

没有一度点的时候随便找一个二度点，然后往某条边用上述规则搜，其余边用相反的规则搜，即可在其他二度点合法的条件下使该点也合法。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,r,l) for(int i=(r);i>=(l);i--)
#define repll(i,l,r) for(ll i=(l);i<=(r);i++)
#define perll(i,r,l) for(ll i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std;
namespace ax_by_c{
typedef long long ll;
const int N=2e5+5;
int n,a[N],b[N],to[N];
struct E{
    int v,id;
};
vector<E>g[N];
bool vis[N];
void dfs(int u,int fa){
    vis[u]=1;
    int fc=0;
    for(auto e:g[u]){
        if(e.v==fa&&!fc){
            fc=1;
            continue;
        }
        if(!to[e.id])to[e.id]=u;
        if(!vis[e.v])dfs(e.v,u);
    }
}
void dfs_(int u,int fa){
    vis[u]=1;
    int fc=0;
    for(auto e:g[u]){
        if(e.v==fa&&!fc){
            fc++;
            continue;
        }
        if(!to[e.id])to[e.id]=e.v;
        if(!vis[e.v])dfs_(e.v,u);
    }
}
void slv(int _csid,int _csi){
	scanf("%d",&n);
    rep(i,1,n)scanf("%d",&a[i]);
    rep(i,1,n)scanf("%d",&b[i]);
    rep(i,1,n*2)g[i].clr(),vis[i]=0;
    rep(i,1,n){
        g[a[i]].pb({b[i],i});
        g[b[i]].pb({a[i],i});
        to[i]=0;
    }
    int ans=0;
    rep(i,1,n*2){
        if(g[i].size()){
            ans++;
            if(g[i].size()>=2)ans++;
            if(!vis[i]&&g[i].size()==1)dfs(i,-1);
        }
    }
    rep(i,1,n*2)if(!vis[i]&&g[i].size()){
        vis[i]=1;
        to[g[i][0].id]=i;
        dfs(g[i][0].v,i);
        for(int j=1;j<(int)g[i].size();j++){
            if(vis[g[i][j].v])continue;
            to[g[i][j].id]=g[i][j].v;
            dfs_(g[i][j].v,i);
        }
    }
    printf("%d\n",ans);
    rep(i,1,n)if(to[i]==b[i])swap(a[i],b[i]);
    rep(i,1,n)printf("%d ",a[i]);putchar('\n');
    rep(i,1,n)printf("%d ",b[i]);putchar('\n');
}
void main(){
//	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T=1,csid=0;
//	scanf("%d",&csid);
	scanf("%d",&T);
	rep(i,1,T)slv(csid,i);
}
}
int main(){
	string __name="";
	if(__name!=""){
		freopen((__name+".in").c_str(),"r",stdin);
		freopen((__name+".out").c_str(),"w",stdout);
	}
	ax_by_c::main();
	return 0;
}
```

---

