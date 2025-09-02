# [USACO23FEB] Fertilizing Pastures G

## 题目描述

有 $N$ 个顶点的树，经过节点之间的每一条边都需要 $1s$。每个顶点一开始的权值均为 $0$，第 $i$ 个点的权值的增长速率为 $a_i/s$。FJ 从 $1$ 号顶点出发遍历整棵树。当 FJ 走到某个节点时，若该节点的权值为 $x$，则需要支出大小为 $x$ 的费用。（当然，只需在第一次经过该节点时需要支出。）

给出一个参数 $T$:

+ **若 $T=0$，FJ 必须回到 $1$ 号节点**。

+ **若 $T=1$，FJ 可以在任意节点结束他的遍历**。

求遍历所有节点的最小时间和此时需要付出的最小的费用。

## 样例 #1

### 输入

```
5 0
1 1
1 2
3 1
3 4```

### 输出

```
8 21```

## 样例 #2

### 输入

```
5 1
1 1
1 2
3 1
3 4```

### 输出

```
6 29```

# 题解

## 作者：Elma_ (赞：7)

先考虑 $T=0$ 时怎么做。显然，最优的遍历顺序是树的某个 DFS 序，对于 $n$ 个点的树遍历的步数是 $2n-2$。我们只需要对于每个节点 $u$，决定其儿子的遍历顺序。

设 $f_u$ 为 $u$ 子树内的答案，$sz_u$ 为 $u$ 子树的大小，$sum_u$ 为 $u$ 子树内 $a_i$ 的和。假设我们现在在 $u$，先进入了别的子树，经过 $T$ 时间后再进入 $v$，我们把每个节点的贡献拆开，可以得到 $v$ 对 $f_u$ 的贡献是 $sum_v \times T + f_v$。而当我们确定顺序后，遍历某个子树 $v$ 之前的子树所需的时间是确定的，相当于有 $k$ 个二元组 $(a_i,b_i)$，其中 $a_i = sum_{v_i},b_i = 2 \times sz_{v_i}$，求一个排列 $p$ 使得 $\sum \limits_{i = 1}^k \left( a_{p_i} \times \big( \sum \limits_{j=1}^{j<i} b_{p_j} + 1 \big) + f_{p_i} \right)$ 最小。

 式子中和 $f$ 有关的项都是确定的，我们要最小化的其实是 $\sum \limits_{i = 1}^k a_{p_i} \times \sum \limits_{j=1}^{j<i} b_{p_j}$。这是个经典 exchange argument，考虑序列中相邻的两个位置 $i,i+1$，显然交换他们不会影响其他项的贡献。设 $i$ 之前的 $b_i$ 和为 $S$，如果交换后答案变得更优，那么有 $a_i \times S + a_{i+1} \times (S + b_i) > a_{i+1} \times S + a_{i} \times (S + b_{i+1})$，即 $\frac{a_{i+1}}{b_{i+1}} > \frac{a_i}{b_i}$。这个条件也是充要的，也就是说，如果序列中存在相邻两个位置满足这个条件，那么交换后答案一定更优。

那么最优的顺序一定按照 $\frac{a_i}{b_i}$ 降序排列，据此容易计算答案，总时间复杂度 $\mathcal{O}(n \log n)$。

------------------------------------------------

对于 $T = 1$ 有相似的结论，如果我们停留在深度为 $d$ 的节点，那么遍历的最小步数为 $(2n - 2) - d$。所以我们最后一定会停留在深度最大的节点。

设最大深度为 $D$。同样，我们还是需要为每个节点决定其儿子的遍历顺序，但与之前不同的是，我们需要选择一个儿子 $v$ 满足其子树内存在深度为 $D$ 的节点，把 $v$ 留到最后进入。我们可以先预处理出哪些节点可以作为这样的 $v$，而对于剩余的儿子节点，和 $T=1$ 时一样，按照 $\frac{a_i}{b_i}$ 排序即可。

当然，我们不可能对于每个可能的 $v$ 都排一遍序。一个简单的优化方式是，由于每次确定 $v$ 后其余的节点都是按照 $\frac{a_i}{b_i}$ 排序，因此这和 $T=0$ 时的结果只会有一项不同，我们可以先算出 $T=0$ 时的答案，枚举 $v$ 时扣掉 $v$ 的贡献，然后加上把 $v$ 放在最后的贡献。这可以通过一些简单的预处理做到单次 $\mathcal{O}(1)$。总时间复杂度 $\mathcal{O}(n \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 5e5 + 5;
const LL inf = 2e18;
int n, t, mxd, a[N], sz[N], dep[N]; LL sum[N], f[N], g[N], suf[N];
bool mark[N];
vector <int> e[N];
struct dat {
	LL a, b; int v;
} d[N];
void dfs0(int u) {
	for (auto v : e[u]) dfs0(v), dep[u] = max(dep[u], dep[v] + 1);
}
void ptag(int u, int d) {
	if (d + dep[u] == mxd) mark[u] = 1;
	for (auto v : e[u]) ptag(v, d + 1);
}
void dfs(int u) {
	sz[u] = 1, sum[u] = a[u];
	int m = 0;
	for (auto v : e[u]) {
		dfs(v);
		sz[u] += sz[v], sum[u] += sum[v];
		f[u] += f[v];
	}
	for (auto v : e[u]) {
		d[++m] = (dat){ sum[v], 2 * sz[v], v };
	}
	sort(d + 1, d + m + 1, [&](dat i, dat j) { return j.a * i.b < i.a * j.b; });
	LL val = 0, sb = 1;
	for (int i = 1; i <= m; i++) {
		val += d[i].a * sb, sb += d[i].b;
	}
	suf[m + 1] = 0;
	for (int i = m; i >= 1; i--) suf[i] = suf[i + 1] + d[i].a;
	LL ret = inf, pre = 1;
	for (int i = 1; i <= m; i++) {
		int v = d[i].v;
		if (mark[v]) ret = min(ret, f[u] - f[v] + g[v] + val - d[i].b * suf[i + 1] - d[i].a * pre + d[i].a * (sb - d[i].b));	
		pre += d[i].b;	
	}
	f[u] += val, g[u] = ret;
	if (m == 0) g[u] = 0;
}
int main() { 
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> t;
    for (int i = 2, ff; i <= n; i++) {
		cin >> ff >> a[i];
		e[ff].push_back(i);
	}
	dfs0(1), mxd = 0;
	for (int i = 1; i <= n; i++) mxd = max(mxd, dep[i]);
	ptag(1, 0), dfs(1);
	if (t == 0) cout << 2 * (n - 1) << " " << f[1] << "\n";
	else cout << 2 * (n - 1) - mxd << " " << g[1] << "\n";
    return 0;
}
```

---

## 作者：double_zero (赞：5)

咋没人写题解/fn

考虑行走的过程跟你 dfs 一棵树的过程是等价的，所以 $T=0$ 时走的边数为 $2(n-1)$，$T=1$ 时，当遍历完最后一个点 $x$ 时，不用再回溯到 $1$，因此少了 $dep_x$ 的时间。

那么你一旦进去一个点，你不走完它子树内的所有结点，它一定不会出来，倘若未走完就出来，则时间花费一定更劣。

考虑 $T=0$ 时咋做，记 $dp(x)$ 从 $x$ 出发走完 $x$ 子树并回到 $x$ 的最小花费，显然你要安排各个儿子间的顺序，记其为序列 $p$，使得 $\sum\limits_{i=1}dp(p_i)+sum(p_i)\sum\limits_{1\le j<i}2(sz_{p_j}+1)$ 最小，即一定是走第一个儿子，然后出来，此时第二个儿子的时间点就多了第一个走进去又走出来的时间。这种往往可以考虑单独拎两个考虑在 $p$ 中的先后关系，你假设 $x$ 先还是 $y$ 先然后分别计算其贡献即可。又因为你这个偏序关系有传递性，所以你直接 sort 就是对的。需要注意的是，当你当前考虑的子树根不为 $1$ 的时候，你应该设其初始时间为 $1$，这样你从父亲从儿子转移的时候才好转移，因为会经过一条边。而注意当考虑 $1$ 的时候，初始时间应设为 $0$。这样设立的原因其实还有一点是你当根不为 $1$ 时，你需要在根花费 1 单位时间。不这样的话，你可以不降 $a_x$ 计入 $dp_x$ 同样也可以做。

考虑 $T=1$，显然还是类似，只不过你一定存在一个点，使得它在它的祖先当中永远是最后走的。这个点需要满足其深度最深。当然，显然这个点不唯一。因此你要把这个点贪出来。具体的，在当前树根为 $x$ 时，记当前有资格最后走的点集为 $S$，那么你不是最后走的你内部不必钦定最后走的点，只需按 $T=0$ 的做法做即可。所以同样的，拎出 $(a,b)$ 进行比较即可。

**总结，这类贪心确定排列顺序问题往往可以通过点对间的偏序来确定，因此分析的时候可以考虑一对，然后计算极端情况贡献，即仅考虑当前序列只有这两个元素，这两个元素的先后各自的贡献。**

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N=(int)(2e5+5);
vector<int>g[N];
int n,T,t[N],sz[N],dp[N],a[N];

bool cmp(int x,int y) {
	return (t[x]+2)*a[y]<(t[y]+2)*a[x];
}

void dfs(int x) {
	sz[x]=1; dp[x]=a[x];
	for(int y:g[x]) {
		dfs(y); sz[x]+=sz[y]; a[x]+=a[y];
	}
	t[x]=2*(sz[x]-1);
	sort(g[x].begin(),g[x].end(),cmp);
	int res=1;
	if(x==1) res=0;
	for(int y:g[x]) {
		dp[x]=dp[x]+res*a[y]+dp[y];
		res+=t[y]+2;
	}
}

int dep[N],mx[N],dp2[N];
void dfsmxd(int x) {
	mx[x]=dep[x];
	for(int y:g[x]) {
		dep[y]=dep[x]+1;
		dfsmxd(y);
		mx[x]=max(mx[x],mx[y]);
	}
}
int ed;
bool cmpp(int x,int y) {
	return (t[x]+2)*a[y]+dp2[x]+dp[y]<(t[y]+2)*a[x]+dp2[y]+dp[x];
}
vector<int>vec1[N];
void dfs2(int x) {
	sz[x]=1; dp[x]=dp2[x]=a[x];
	for(int y:g[x]) {
		dfs2(y); sz[x]+=sz[y]; a[x]+=a[y];
	}
	t[x]=2*(sz[x]-1);
	for(int y:g[x]) {
		if(mx[y]==mx[1]) vec1[x].pb(y);
	}
	sort(vec1[x].begin(),vec1[x].end(),cmpp);
	ed=0;
	if(!vec1[x].empty()) ed=vec1[x].back();
	vector<int>vec; vec.clear();
	for(int y:g[x]) if(y!=ed) vec.pb(y); 
	sort(vec.begin(),vec.end(),cmp);
	int res=1;
	if(x==1) res=0;
	for(int y:vec) {
		dp[x]=dp[x]+res*a[y]+dp2[y];
		res+=t[y]+2;
	}
	if(ed) dp[x]=dp[x]+res*a[ed]+dp[ed];
	res=1; if(x==1) res=0;
	sort(g[x].begin(),g[x].end(),cmp);
	for(int y:g[x]) {
		dp2[x]+=res*a[y]+dp2[y];
		res+=t[y]+2;
	} 
}

signed main() {
//	freopen("11.in","r",stdin);
	cin.tie(0); ios::sync_with_stdio(false);
	cin>>n>>T;
	for(int i=2;i<=n;i++) {
		int x; cin>>x>>a[i];
		g[x].pb(i);
	}
	if(T==0) {
		dfs(1);
		cout<<2*n-2<<" "<<dp[1];
	} else {
		dfsmxd(1);
		cout<<2*n-2-mx[1]<<" ";
		dfs2(1);
		cout<<dp[1];
	}
	return 0; 
}
```


---

## 作者：Graphcity (赞：4)

根据经典结论，$T=0$ 时答案就是 dfs 一遍，$T=1$ 时 dfs 经过的最后一条链可以不用遍历。所以第一问的答案为 $2(n-1)-[T=1]\times \max_i dep_i$。

设 $f_x,g_x$ 分别为第一问 / 第二问中，零时刻刚好在 $x$，遍历完 $x$ 的整棵子树的最小代价。对于 $f_x$，设 $x$ 的儿子分别为 $p_{1\cdots k}$，我们需要确定一个儿子的遍历顺序使得代价最小化。

代价等于 $\sum_{i=1}^kf_{p_i}+sum_{p_i}+\sum_{i=1}^k 2\times sum_{p_i}\sum_{j=1}^{i-1}siz_{p_j}$。前面一个和式是定值，可以直接计算。后面一个和式中，发现是 $siz$ 的前缀和乘上单点 $sum$ 的形式。根据经典贪心结论，只需要将 $\dfrac{sum_i}{siz_i}$ 从大往小排序即可。

接下来是第二问。在原有贡献的基础上，我们需要将一个有着最长链的儿子推到最后一处。这个很简单，只需要考虑变化量即可。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;
const ll inf=LONG_LONG_MAX;

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

int n,OP,siz[Maxn+5],maxd[Maxn+5];
ll f[Maxn+5],g[Maxn+5],val[Maxn+5],sum[Maxn+5];
vector<int> v[Maxn+5];

inline void dfs0(int x)
{
    siz[x]=1,sum[x]=val[x],maxd[x]=1;
    for(auto y:v[x])
    {
        dfs0(y),siz[x]+=siz[y],sum[x]+=sum[y];
        maxd[x]=max(maxd[x],maxd[y]+1);
    }
}
inline void dfs1(int x)
{
    sort(v[x].begin(),v[x].end(),[&](int a,int b){return sum[a]*siz[b]>sum[b]*siz[a];});
    for(auto y:v[x]) dfs1(y),f[x]+=f[y]+sum[y];
    ll s=0; for(auto y:v[x]) f[x]+=sum[y]*s,s+=(siz[y]*2);
}
inline void dfs2(int x)
{
    if(!v[x].empty()) g[x]=inf; else g[x]=0;
    reverse(v[x].begin(),v[x].end()); ll s=0,all=0;
    for(auto y:v[x]) dfs2(y);
    for(auto y:v[x])
    {
        if(maxd[y]+1==maxd[x])
            g[x]=min(g[x],f[x]-f[y]+g[y]-s*(siz[y]*2)+all*2*sum[y]);
        s+=sum[y],all+=siz[y];
    }
}

int main()
{
    n=read(),OP=read();
    For(i,2,n) v[read()].push_back(i),val[i]=read();
    dfs0(1),dfs1(1),dfs2(1);
    if(OP==0) cout<<(n-1)*2<<' '<<f[1]<<endl;
    else cout<<(n-1)*2-(maxd[1]-1)<<' '<<g[1]<<endl;
    return 0;
}
```



---

## 作者：Jorge_Filho (赞：1)

# USACO23FEB GOLD T2 Solution

## 题意:
给定一颗树，每个节点上都有一个数（初始都为 $0$），第 $i$ 个点上的数每秒增大 $w_i$。你一开始在 $1$ 号节点，你需要用最短的时间走遍每个节点，每条边都需要 $1$ 秒的时间经过，每第一次到达一个节点时你会记录下当前的数（第二次及以后就不用管了），求最短的时间以及在**这个时间下**：

（1）若最后必须回到 $1$ 号节点，你所记录的数之和的最小值是多少。

（2）若你可以在任意一个点结束行程（当然其他点都必须走到过），你所记录的数之和的最小值是多少。

## 解析:

先考虑第一问，不难发现走过的点的顺序一定是原树的一个欧拉序（就是那个可以配合 st 表求 lca 的）。设 $g(u,1)$ 表示在以 $u$ 为根的子树内从 $u$ 出发并且回到 $u$ 所需要的最小时间，由于进出每个儿子都需要 $2$ 秒，故有 $g(u,1)=\sum_{v \in son_u} 2+g(v,2)$。设 $f(u,1)$ 表示在以 $u$ 为根的子树内在 $0$ 时刻从 $u$ 出发并且回到 $u$ 在所需要最小时间的情况下所记录的数之和的最小值，那么转移的关键就是如何决定访问儿子的先后顺序（大家有没有发现这是带权排队接水问题）。

类似于排队接水问题，我们向贪心的方向出发，思考如何排序。这里用到的一个常用的套路：微扰。考虑两个相邻访问的儿子 $x$ 和 $y$，设以 $u$ 为根的子树内所有节点的 $w$ 之和为 $sz_u$、已经访问过的节点耗时为 $t$，则先访问 $x$ 比 先访问 $y$ 更优当且仅当 $f(x,1)+t \cdot sz_x+f(y,1)+[t+2+g(x,1)] \cdot sz_y<f(y,1)+t \cdot sz_y+f(x,1)+[t+2+g(y,1)] \cdot sz_x$，化简得 $\frac{g(x,1)+2}{sz_x}<\frac{g(y,1)+2}{sz_y}$。于是以 $\frac{g(v,1)+2}{sz_v}$ 为关键字升序排序即可。证明：运用冒泡排序的思想，对于任意一个无序的序列都可以通过 $O(n^2)$ 次交换相邻逆序元素达到有序，我们可以得出：因为每次交换都会使方案更优，于是所有方案都不优于有序的方案，故按照 $\frac{g(v,1)+2}{sz_v}$ 升序排序的方案时最优的（或之一）。

再来看第二问，如果不需要回到 $1$ 号点，则有且仅有一个儿子不需要返航，设 $g(u,0)$ 表示在以 $u$ 为根的子树内从 $u$ 出发但不回到 $u$ 所需要的最少时间，得：$g(u,0)=\min\{1+g(x,0)+\sum_{v \in son_u \wedge v \not =x} 2+g(v,1) | x \in son_u\}$，使用树形 dp 常用技巧可以转化为 $g(u,1)-\max\{g(v,1)+2-g(v,0)-1|v \in son_u\}$。再来看 $f$ 的转移，应该是把那个最后访问的儿子确定了以后再把剩下的排个序即可，但是问题是满足 $g(v,1)+2-g(v,0)-1$ 最大的 $v$ 不唯一，如果硬做会使得复杂度最高上升到 $O(n^2)$，这是我们不能接受的。考虑优化，其实仔细想想会发现前面的顺序是和第一问的情况是一样的，于是我们只 $O(1)$ 找出那个移动到最后一个位置的贡献即可，这里的细节希望读者自己实现了，一是在纸上不好描述，二是到这一步了如果自己都没想出来这道题确实 A 了也没有一点价值。


时间复杂度（设第 $i$ 个节点的儿子数为 $s_i$）：$\Theta(\sum_{u \in V} s_u \cdot \log_2 s_u)=O(n \cdot \log_2 n)$。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=2e5,A=1e8,T=1,INF=1ll<<62;
long long n,t,w[N+4],f[N+4][2],g[N+4][2],sz[N+4],x,pss[N+4],pst[N+4],bjt[N+4];
long long h[N+4],ne[N+4],e[N+4],idx;

struct node
{
	long long t,c,s,pos;
	bool operator <(const node &a) const
	{
		return t*a.s<a.t*s;
	}
};

inline void Add(const long long &x,const long long &y)
{
	e[idx]=y;
	ne[idx]=h[x];
	h[x]=idx++;
}

void Dfs(const long long &u)
{
	long long maxx=0;
	sz[u]=w[u];
	for(long long i=h[u];~i;i=ne[i])
	{
		long long v=e[i];
		Dfs(v);
		sz[u]+=sz[v];
	}
	vector<node> a;
	vector<long long> b;
	for(long long i=h[u];~i;i=ne[i])
	{
		long long v=e[i];
		g[u][1]+=g[v][1]+2;
		maxx=max(maxx,g[v][1]+2-g[v][0]-1);
		a.push_back((node) {g[v][1]+2,f[v][1],sz[v],v});
	}
	for(long long i=h[u];~i;i=ne[i])
	{
		long long v=e[i];
		if(g[v][1]+2-g[v][0]-1==maxx)
		{
			b.push_back(v);
		}
	}
	g[u][0]=g[u][1]-maxx;
	if(a.empty())
	{
		return ;
	}
	sort(a.begin(),a.end());
	long long len=a.size();
	pss[0]=a[0].s;
	pst[0]=a[0].t;
	bjt[a[0].pos]=0;
	f[u][1]=a[0].c+a[0].s;
	for(long long i=1;i<len;i++)
	{
		pss[i]=pss[i-1]+a[i].s;
		pst[i]=pst[i-1]+a[i].t;
		bjt[a[i].pos]=i;
		f[u][1]+=a[i].c+(pst[i-1]+1)*a[i].s;
	}
	f[u][0]=INF;
	for(auto i:b)
	{
		f[u][0]=min(f[u][0],f[u][1]+(pst[len-1]-pst[bjt[i]])*sz[i]-f[i][1]+f[i][0]-(g[i][1]+2)*(pss[len-1]-pss[bjt[i]]));
	}
}

int main()
{
	scanf("%lld%lld",&n,&t);
	t=!t;
	memset(h,-1,sizeof(h));
	for(long long i=2;i<=n;i++)
	{
		scanf("%lld%lld",&x,w+i);
		Add(x,i);
	}
	Dfs(1);
	printf("%lld %lld\n",g[1][t],f[1][t]);
	return 0;
}
```

---

## 作者：OtterZ (赞：0)

# 题意
你需要遍历整棵树，树上每个点有毒气，每个单位时间毒气量增长 $a_i$ 个单位，每个点毒气类型不同，每个点的毒气在你抵抗过后就不会对你产生伤害，有时你需要回来，有时不需要，问你最短的遍历时间和同时最少要抵抗的毒气总量。
# 当你有必要回来时
你会遍历 $2 \times (N - 1)$ 单位时间，显然进入子树后要走完，当你先遍历 $u$ 点对应的子树再遍历 $v$ 所在的子树，你在 $v$ 子树的时候每个点 $i$ 都要多抵抗 $sz_u \times a_i$ 的毒气，总共多 $2 \times sz_u \times \sum a_i$ 单位毒气，以此当 $sz_u \times \sum a_i < sz_v \times \sum a_j$ 时应先去 $a_u$。
# 当你没必要回来时
你可以呆在深度最大的点，但你要把其中一个含深度最大的点的子树放最后，而这会多 $\sum sz_v \times \sum a_i - \sum a_j \times sz_u$ 的毒气量。我们亦可以此贪心，但不要忘了你过去后继续走的情况。
# 注意事项

1. 请开 `long long`。
2. 不用回来时先把每颗子树放最后的额外贡献求出来，贪心时要算进去。
3. 你回去父节点要花时间。

# 代码

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int n,m,dep[200005];//sz[i]为第i颗子树的子树个数，ta[i]表示子树中a_i之和
vector<int>e[200005];
long long ta[200005],a[200005],sz[200005],ctr[200005];
bool ssp[200005];

void srh1(int nk){//用来求sz_i,ta_i,dep_i
	sz[nk] = 1,ta[nk] = a[nk];
	for(int i = 0; i < e[nk].size(); i ++){
		dep[e[nk][i]] = dep[nk] + 1; 
		srh1(e[nk][i]);
		 sz[nk] += sz[e[nk][i]];
		 ta[nk] += ta[e[nk][i]];
	} 
}

void srh2(int nk){//用来求ssp[i]
	for(int i = 0; i < e[nk].size(); i ++){
		srh2(e[nk][i]);
		ssp[nk] = ssp[nk] || ssp[e[nk][i]];
	} 
}

bool cmp(int x,int y){//遍历先后顺序 
	return ta[y] * sz[x] < ta[x] * sz[y];
} 
void ex_srh(int nk){
	if(e[nk].size() == 0)
		return;//不用调顺序 
	sort(e[nk].begin(),e[nk].end(),cmp);
	for(int i = 0; i < e[nk].size(); i ++){
		if(ssp[e[nk][i]])
			ex_srh(e[nk][i]);
	}
	int j = 0;
	unsigned long long atr = 0,atk = 0,pd = 9e18;
	for(int i = e[nk].size() - 1; i >= 0; i --){//留一个最后走 
		atk += ta[e[nk][i]];
		atr += sz[e[nk][i]];
	}
	for(int i = 0; i < e[nk].size(); i ++){//留一个最后走 
	    atk -= ta[e[nk][i]],atr -= sz[e[nk][i]];
		if(ssp[e[nk][i]] && atr * ta[e[nk][i]] - atk * sz[e[nk][i]] + ctr[e[nk][i]] < pd){
			j = i;
			pd = atr * ta[e[nk][i]] - atk * sz[e[nk][i]] + ctr[e[nk][i]];
		}
	}
	ctr[nk] = pd;
	//printf("%d %lld\n",nk,pd);
}
void srh3(int nk,bool flg){//用来求遍历顺序 
//printf("%d %s\n",nk,flg ? "Y" : "N");
	if(e[nk].size() == 0)
		return;//不用调顺序 
	sort(e[nk].begin(),e[nk].end(),cmp);
	if(flg){
		//printf("Y\n");
		int j = 0;
		unsigned long long atr = 0,atk = 0,pd = 9e18;
		for(int i = e[nk].size() - 1; i >= 0; i --){//留一个最后走 
			atk += ta[e[nk][i]];
			atr += sz[e[nk][i]];
		}
		for(int i = 0; i < e[nk].size(); i ++){//留一个最后走 
		    atk -= ta[e[nk][i]],atr -= sz[e[nk][i]];
			if(ssp[e[nk][i]] && atr * ta[e[nk][i]] - atk * sz[e[nk][i]] + ctr[e[nk][i]] < pd){
				j = i;
				pd = atr * ta[e[nk][i]] - atk * sz[e[nk][i]] + ctr[e[nk][i]];
			}
		}
		//printf("%d %d\n",j,e[nk].size());
		while(j < e[nk].size() - 1){//换到最后一个 
			swap(e[nk][j],e[nk][j + 1]);
			j ++;
		}
	}
	for(int i = 0; i < e[nk].size(); i ++){
		if(flg && i == e[nk].size() - 1)//北流了
			srh3(e[nk][i],true); 
		else
			srh3(e[nk][i],false);
	}
}

long long o;
long long ans;
void srh4(int nk){//求要对多少甘草 
//printf("%d\n",nk);
	ans += 1ll * a[nk] * o;
	//printf("%lld\n",1ll * a[nk] * o);
	for(int i = 0; i < e[nk].size(); i ++){
		o ++;
		srh4(e[nk][i]);
		o ++;//有来有回 
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 2; i <= n; i ++){
		int p;
		scanf("%d %d",&p,&a[i]);
		e[p].push_back(i);
	}
	if(m == 0){
		srh1(1);
		srh3(1,false);
		srh4(1);
		printf("%d %lld\n",((n - 1) << 1),ans);
	}
	else{
		srh1(1);
		int u = 0;
		for(int i = 1; i <= n; i ++){
			u = max(u,dep[i]);
		}
		for(int i = 1; i <= n; i ++){
			ssp[i] = (u == dep[i]);
		}
		srh2(1);
		//printf("FH\n");
		ex_srh(1);
		srh3(1,true);
		//printf("JJJ\n");
		srh4(1);
		printf("%d %lld\n",((n - 1) << 1) - u,ans);
	}
	return 0;
}
```


---

## 作者：StarRain3 (赞：0)

第一次全对，发个迟到题解纪念一下。这里介绍一种更容易理解的方法。我们把每个读入的 $x$ 放入儿子节点中，再伪搜索，把每个节点处理一遍，排一下序，排序也是个贪心的过程，这里的贪心确定的是排列顺序问题，它往往可以通过点对间的偏序来确定最后枚举最后不回的点，用 $f$ 将其修改。

其余代码无需解释，模拟即可。比其他大佬的码都清楚的多，详细请看代码。
```
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;

int n, T, sz[N], mxd[N];
LL sa[N], f[N], g[N];
typedef long long LL;//数据过大
vector<int> erzi[N];//定义儿子节点
bool cmp(int i, int j) { 
	return sa[i] * sz[j] < sa[j] * sz[i]; //排序
}
int main() {
    cin >> n >> T;
    for(int i = 2, x; i <= n; i ++)
        scanf("%d%lld", &x, sa + i), erzi[x].push_back(i);
    for(int u = n; u; u --) { //伪搜索
        sz[u] = 1;
        for(int v : erzi[u]) {
            mxd[u] = smax(mxd[u], mxd[v] + 1);
            sz[u] += sz[v], sa[u] += sa[v], f[u] += f[v] + sa[v];
        }
        stable_sort(erzi[u].begin(), erzi[u].end(), cmp);//排序
        LL suma = 0, sums = 0;
        for(int v : erzi[u]) f[u] += (sz[v] << 1) * suma, suma += sa[v];//枚举，贪心
        g[u] = erzi[u].size() ? 9e18 : 0, suma = 0;
        for(int v : erzi[u]) {
            if(mxd[u] == mxd[v] + 1) //枚举最后不回的点
                g[u] = std::min(g[u], f[u] - (sz[v] << 1) * suma + sums * sa[v] - f[v] + g[v]);
            suma += sa[v], sums += sz[v] << 1;
        }
    }
    //输出
    if(T) printf("%d %lld\n", 2 * (n - 1) - mxd[1], g[1]);
    else printf("%d %lld\n", 2 * (n - 1), f[1]);
    return 0;
}

```

---

