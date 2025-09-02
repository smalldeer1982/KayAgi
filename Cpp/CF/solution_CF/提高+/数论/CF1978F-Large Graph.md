# Large Graph

## 题目描述

Given an array $ a $ of length $ n $ . Let's construct a square matrix $ b $ of size $ n \times n $ , in which the $ i $ -th row contains the array $ a $ cyclically shifted to the right by $ (i - 1) $ . For example, for the array $ a = [3, 4, 5] $ , the obtained matrix is

 $ $$$b = \begin{bmatrix} 3 & 4 & 5 \\ 5 & 3 & 4 \\ 4 & 5 & 3 \end{bmatrix} $ $ </p><p>Let's construct the following graph:</p><ul> <li> The graph contains  $ n^2 $  vertices, each of which corresponds to one of the elements of the matrix. Let's denote the vertex corresponding to the element  $ b\_{i, j} $  as  $ (i, j) $ .</li><li> We will draw an edge between vertices  $ (i\_1, j\_1) $  and  $ (i\_2, j\_2) $  if  $ |i\_1 - i\_2| + |j\_1 - j\_2| \\le k $  and  $ \\gcd(b\_{i\_1, j\_1}, b\_{i\_2, j\_2}) &gt; 1 $ , where  $ \\gcd(x, y) $  denotes the <a href="https://en.wikipedia.org/wiki/Greatest_common_divisor">greatest common divisor</a> of integers  $ x $  and  $ y $ . </li></ul><p>Your task is to calculate the number of connected components $ ^{\\dagger} $  in the obtained graph.</p><p> $ ^{\\dagger}$$$A connected component of a graph is a set of vertices in which any vertex is reachable from any other via edges, and adding any other vertex to the set violates this rule.

## 说明/提示

In the first test case, the matrix $ b $ is given in the statement. The first connected component contains the vertices $ (1, 1) $ , $ (2, 2) $ , and $ (3, 3) $ . The second connected component contains the vertices $ (1, 2) $ , $ (2, 3) $ , and $ (3, 1) $ . The third connected component contains the vertices $ (1, 3) $ , $ (2, 1) $ , and $ (3, 2) $ . Thus, the graph has $ 3 $ connected components.

In the second test case, the following matrix is obtained:

 $ $$$b = \begin{bmatrix} 3 & 4 & 9 \\ 9 & 3 & 4 \\ 4 & 9 & 3 \end{bmatrix} $ $ </p><p>The first connected component contains all vertices corresponding to elements with values  $ 3 $  and  $ 9 $ . The second connected component contains all vertices corresponding to elements with the value  $ 4$$$.

In the fourth test case, all vertices are in one connected component.

## 样例 #1

### 输入

```
6
3 3
3 4 5
3 3
3 4 9
3 2
3 4 9
2 2
2 8
5 3
8 27 5 4 3
4 10
2 2 2 2```

### 输出

```
3
2
3
1
4
1```

# 题解

## 作者：CarroT1212 (赞：5)

被 C&D 创了没细想，哈哈。

------------

感觉像是考验注意力的题目，于是你尝试注意一些东西。然后注意到 $k\ge 2$？

说明斜着相邻的格子如果有 $\gcd>1$ 必定连边。那题目里有什么格子是斜着相邻的呢？

很明显有每个 $a_i$ 在循环移位之后分成的至多两条全是 $a_i$ 的斜线。除了 $a_i=1$，特判掉即可。

$$\begin{bmatrix} 3 & 4 & 5 \\ 5 & 3 & 4 \\ 4 & 5 & 3 \end{bmatrix}$$

比如题面里这个矩阵。$3$ 是完整的一条，$4,5$ 都被分成两条。

所以每条这样的斜线（除了 $a_i=1$）必定形成一个连通块。而相邻两条斜线的距离是 $1$，于是我们把二维问题完全的转为了一维。把斜线上的数分别写下来得到 $4\ 5\ 3\ 4\ 5$。在这个上面再去做。令它为新的 $a_i$。

那这就比较好做了。预处理每个数的质因子，每次求一下每个质因子被哪些 $a_i$ 包含。对于包含同一个质因子的 $a_i$，我们将距离不超过 $k$ 的相邻两个数连在一起。对每一个存在 $a_i$ 包含的质因子这么做一遍。并查集维护一下，得到最终的连通块数量就完事了。

注意由于多测的存在，枚举包含的质因子的时候必须只枚举存在至少一个 $a_i$ 包含的，然后枚举包含质因子的数的时候也得预处理出来，不能多枚。

复杂度是 $O(n\ln n)$ 左右的东西。

记得特判 $a_i=1$。

------------

```cpp
ll n,k,a[N*2],vis[N],ans;
vector<ll> prm[N],cnt[N],has;
struct dsu {
	ll f[N*2];
	void ini(ll n) { iota(f+1,f+n+1,1); }
	void mrg(ll x,ll y) { f[fnd(x)]=fnd(y); }
	ll fnd(ll x) { return f[x]==x?x:f[x]=fnd(f[x]); }
} D;
void mian() {
	for (ll i=2;i<N;i++) if (!vis[i]) {
		prm[i].pb(i);
		for (ll j=i+i;j<N;j+=i) vis[j]=i,prm[j].pb(i); 
	}
	scanf("%lld%lld",&n,&k),ans=0;
	for (ll i=1;i<=n;i++) {
		scanf("%lld",&a[i+n-1]);
		if (a[i+n-1]==1) ans+=n;
	}
	for (ll i=1;i<n;i++) a[i]=a[i+n];
	has.clear();
	for (ll i=1;i<n*2;i++) for (ll j:prm[a[i]]) has.pb(j),cnt[j].pb(i);
	sort(has.begin(),has.end());
	ll len=unique(has.begin(),has.end())-has.begin();
	D.ini(n*2-1);
	for (ll i=0;i<len;i++) {
		for (ll j=0;j+1<cnt[has[i]].size();j++)
			if (cnt[has[i]][j+1]-cnt[has[i]][j]<=k) D.mrg(cnt[has[i]][j+1],cnt[has[i]][j]);
		cnt[has[i]].clear();
	}
	set<ll> s;
	for (ll i=1;i<n*2;i++) if (a[i]>1) s.insert(D.fnd(i));
	cout<<ans+s.size()<<"\n";
}
```

---

## 作者：Lu_xZ (赞：3)

**F		\*2518**

题目保证了 $k \ge 2$，所以对角线一定同属一个连通块。

![](https://cdn.luogu.com.cn/upload/image_hosting/pkbrixz0.png)

所以只需要在 $2n - 1$ 条对角线间连边即可，元素个数由 $O(n^2)$ 骤减为 $O(n)$。

把对角线从左下到右上依次编号为 $b_1, \cdots {b_{2n - 1}}$。不难发现，$b_i$ 与 $b_j$ 间的最短距离恰为 $\vert i - j\vert$。

因此，可以如下转化为序列上的问题。

![](https://cdn.luogu.com.cn/upload/image_hosting/1569dchj.png)

接下来就很经典了。

枚举质因数 $p$，把包含 $p$ 的元素提出来，检查相邻两数的间距是否超过 $k$，并查集维护连通性。

注意特判 $a_i = 1$ 的情况，每个 $1$ 都是孤立点。

```cpp
#include<bits/stdc++.h>
#define eb emplace_back
using namespace std;

using ll = long long;
constexpr int N = 1e6 + 5, V = 1e6;

int p[N], low[N], idx;

void Euler_Sieve() {
	low[1] = 1;
	for(int i = 2; i <= V; ++ i) {
		if(!low[i]) {
			low[i] = ++ idx;
			p[idx] = i;
		}
		for(int j = 1; j <= idx && p[j] <= V / i; ++ j) {
			low[i * p[j]] = j;
			if(i % p[j] == 0)
				break;
		}
	}
}

int n, k, b[N * 2], fa[N * 2];
vector<int> a[N];
ll ans, one;

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
};
void merge(int x, int y) {
	x = find(x), y = find(y);
	if(x != y)
		fa[y] = x;
}

void solve() {
	cin >> n >> k;
	one = 0;
	for(int i = 1; i <= n; ++ i) {
		int x; cin >> x;
		if(x == 1) {
			++ one;
		}
		b[i - 1] = b[n + i - 1] = x;
	}
	ans = one * n;
	n *= 2;
	set<int> P;
	for(int i = 1; i < n; ++ i) {
		int tmp = b[i];
		while(tmp > 1) {
			P.insert(low[tmp]);
			a[low[tmp]].eb(i);
			tmp /= p[low[tmp]];
		}
	}
	iota(fa + 1, fa + n, 1);
	for(auto x : P) {
		a[x].erase(unique(a[x].begin(), a[x].end()), a[x].end());
		int j = 0;
		for(auto i : a[x]) {
			if(j && i - j <= k) {
				merge(i, j);
			}
			j = i;
		}
		a[x].clear();
	}
	for(int i = 1; i < n; ++ i) {
		if(b[i] > 1) 
			ans += (i == find(i));
	}
	cout << ans << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	
	Euler_Sieve();
	int T;
	cin >> T;
	
	while(T --) {
		solve();
	}
	return 0;
}
```

---

## 作者：Rosabel (赞：2)

挺套路的一题。

把原正的正方形顺时针旋转 $45\degree$ 后发现转换后的斜的正方形。从左往右扫过去发现就是 $2n-1$ 组数，每组内的数均相同，第 $i$ 组数内的个数是 $\min(i,2n-i)$。那么原序列可看做长度为 $2n-1$ 的，权重（就是每组个数）不同的序列。

由于 $k\ge 2$，所以每组中的数必定联通。注意这里要特判 $1$ 的情况，若 1 组中的数全为 $1$，那么由于 $\gcd(1,1)=1$，每一个 $1$ 都构成一个联通块。

排除掉 $1$ 的情况，也就是剩下最多 $2n-1$ 个元素（因为有可能一个 $1$ 都没有）计算联通块个数。并查集维护即可。

暴力连边是 $\Theta(n^2)$ 的。考虑优化。注意到若 $i,j$ 有连边，那么 $\gcd(a_i,a_j)\ge2$ 的性质，我们发现连边的操作可以从关注下标转移到关注值。对于 $a_i\mid p,a_j\mid p,p\in \text{Prime}$ 可以连边。实际操作时，只需要对于每一个 $i$ 都去枚举 $p$ 即可（固定了 $i,p$ 以后若有多个 $j$ 只需向其中一个连边即可，这是由于所有合法的 $j$ 一定已经成为一个联通块了）。对于 $a_i\le 10^6$，$p$ 的个数最多不超过 $7$（$2\times3\times5\times7\times11\times13\times17\times19=9699690\gt10^6$）。

至于 $k$ 的限制，只需要动态维护每个质因数倍数对应下标即可。$\texttt{list}$ 可以轻松实现。

预处理每个数的质因数可以通过枚举每个质因数倍数。上限是 $\Theta(V\log V)$。查询是 $\Theta(7n\alpha(n))$（这里写法不严谨，$7$ 是质因数个数上限，个人觉得 $7$ 与值域有关所以不将其视为常数而写出来）。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+5;
vector<int>lnk[N];
int prime[N],tot,isprime[N];
void Prime(int lmt=1e6){
    isprime[1]=1;
    for(int i=2;i<=lmt;i++){
        if(!isprime[i]){
            prime[++tot]=i;
        }
        for(int j=1;j<=tot&&i*prime[j]<=lmt;j++){
            isprime[i*prime[j]]=1;
            if(i%prime[j]==0){
                break;
            }
        }
    }
}
void init(int lmt=1e6){
    for(int i=1;i<=tot;i++){
        for(int j=1;prime[i]*j<=lmt;j++){
            lnk[prime[i]*j].push_back(prime[i]);
        }
    }
}
int n,k,a[N<<1],buc[N];
namespace DSU{
    int fa[N<<1];
    void Init(int lmt){
        for(int i=1;i<=lmt;i++){
            fa[i]=i;
        }
    }
    int Find(int x){
        if(fa[x]==x){
            return x;
        }
        return fa[x]=Find(fa[x]);
    }
    bool merge(int x,int y){
        x=Find(x),y=Find(y);
        fa[x]=y;
        return x!=y;
    }
}
using namespace DSU;
list<int>lnk2[N];
ll res;
void check(int pos,int x){
    for(auto i:lnk[x]){
        if(!buc[i]){
            continue;
        }
        int j=lnk2[i].front();
        if(merge(pos,j)){
            --res;
        }
    }
}
void add(int pos,int x){
    bool flag=0;
    for(auto i:lnk[x]){
        ++buc[i];
        lnk2[i].push_back(pos);
    }
}
void del(int x){
    for(auto i:lnk[x]){
        --buc[i];
        lnk2[i].pop_front();
    }
}
ll solve(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    reverse(a+1,a+n+1);
    for(int i=1;i<n;i++){
        a[n+i]=a[i];
    }
    Init((n<<1)-1);
    res=(n<<1)-1;
    for(int i=1;i<n<<1;i++){
        check(i,a[i]);
        add(i,a[i]);
        if(a[i]==1){
            res=res+min(i,(n<<1)-i)-1;
        }
        if(i-k>0){
            del(a[i-k]);
        }
    }
    for(int i=1;i<=n;i++){
        for(auto j:lnk[a[i]]){
            buc[j]=0;
            lnk2[j].clear();
        }
    }
    return res;
}
int main(){
    Prime();
    init();
    int T;
    scanf("%d",&T);
    while(T--){
        printf("%lld\n",solve());
    }
    return 0;
}
```

---

## 作者：Exp10re (赞：1)

好题，可惜是简单题。

顺便提一嘴，题面炸完了。

## 解题思路

注意到 $k\geq 2$ 是很优秀的性质：如果 $a_i$ 不为 $1$ 那么斜线一定会连成联通块。

那么这些联通块就形如 $b=a_{2,3,\cdots,n}+a_{1,2,\cdots,n}$，考虑筛出 $1$ 到 $10^6$ 的所有数的质因子，遍历 $b$ 中每一个数，记录每一个质因子最后出现的位置然后用并查集维护连通性即可。

最终答案即为联通块个数。

注意特判 $b_i=1$，其在原矩阵中的斜线不会形成连通块。

---

## 作者：TernaryTree (赞：1)

![](https://cdn.luogu.com.cn/upload/image_hosting/v0lbgufg.png)

所以我们把矩阵转成了长为 $2n-1$ 的数列。从前往后处理，将当前数分解质因子，往前找最后面的也出现过这个质因子的数，若距离 $\le k$ 则连边。这个可以用一个桶记录每个质因子最后一次出现位置解决。注意特判 $a_i=1$ 时，这一列不会像上图那样连边，答案要加上 $\min(i-1,2n-i-1)$。

[Code。](https://www.luogu.com.cn/paste/s90mavb8)

---

## 作者：int_R (赞：1)

把矩阵写出来，每条直线 $j-i=p(p\in(-n,n))$，也就是每条从左上到右下的线上的数都是一样的，同时 $k\geq 2$，所以除了数字为 $1$ 的情况，每条这样的线都是一个连通块。

于是我们直接把每条线的数字按 $p$ 的顺序写出来，总共有 $2n-1$ 个数，每对数的距离就是他们下标的差，问题转化成对这个序列做。

不互质就是有公约数，所以直接对每个数在 $\log$ 范围内分解质因数，对于每个质因数找到上一次出现的位置，如果距离 $\leq k$ 就有边，并查集维护连通性，特判 $1$ 的情况即可。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#define ll long long
using namespace std;
const int MAXN=2e6+10;
int p[MAXN],s[MAXN],tot;
inline void init(int n)
{
    for(int i=2;i<=n;++i)
    {
        if(!s[i]) s[i]=p[++tot]=i;
        for(int j=1;j<=tot&&p[j]<=n/i;++j)
        {
            s[i*p[j]]=p[j];
            if(!(i%p[j])) break;
        }
    }
}
int T,n,k,a[MAXN],lst[MAXN],fa[MAXN];
vector <int> used;bool vis[MAXN];ll ans;
inline int find(int x)
    {return fa[x]==x?x:fa[x]=find(fa[x]);}
inline void merge(int x,int y)
    {if(find(x)!=find(y)) fa[fa[x]]=fa[y];}
inline void work()
{
    cin>>n>>k;
    for(int i=n;i<n+n;++i)
        cin>>a[i],a[i-n]=a[i];
    int N=n;n=(n<<1)-1;
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=1;i<=n;++i)
    {
        int x=a[i];while(x!=1)
        {
            int now=s[x],pre=lst[now];
            if(pre&&i-pre<=k) merge(i,pre);
            lst[now]=i;while(!(x%now)) x/=now;
            if(!vis[now]) vis[now]=true,used.push_back(now);
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(a[i]==1) ans+=N-abs(N-i);
        else if(find(i)==i) ++ans;
    }
    cout<<ans<<'\n';ans=0;
    for(int x:used) vis[x]=false,lst[x]=0;
    used.clear();return ;
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    init(1000000);
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>T;while(T--) work();
}
```

---

## 作者：Ghosty_Neutrino (赞：0)

## 题意

给定一个长度为 $n$ 的数组 $a$。我们来构造一个大小为 $n \times n$ 的方阵 $b$，其中第 $i$ 行包含了循环右移 $(i-1)$ 的数组 $a$。例如，对于数组 $a=[3,4,5]$，得到的矩阵是
$$
b=\begin{pmatrix}
  3 & 4 & 5 \\
  7 & 9 & 2 \\
   1 & 8 & 4 \\
\end{pmatrix}
$$
让我们构建下面的图形：

该图包含 $n^2$ 个顶点，每个顶点对应矩阵中的一个元素。我们把元素 $b_{i,j}$ 对应的顶点记为 $(i,j)$。

我们将在顶点 $(i_1,j_1)$ 和 $(i_2,j_2)$ 之间画一条边，如果 $|i_1-i_2|+|j_1-j_2| \le k$ 和 $\gcd(b_{i1,j1},b_{i2,j2})>1$，其中 $\gcd(x,y)$ 表示整数 $x$ 和 $y$ 的最大公约数。

你的任务是计算所得图形中的连通块数。

图中的连通块是一个顶点集合，在这个集合中，任何顶点都可以通过边到达其他顶点，如果在这个集合中添加任何其他顶点，都会违反这一规则。

## 分析

题目保证 $k \le 2$，说明斜着相邻的格子如果 $\gcd>1$，必定连边，很明显每个 $a_i$ 在循环移位之后分成的至多两条全是 $a_i$ 的斜线，所以除了数字为 $1$ 的情况，对角线的斜线一定同属一个连通块。

相邻两条斜线的距离是 $1$，由此我们可以把二维问题转为一维。使用 $\log$ 分解质因数，预处理每个数的质因子，对于每个质因数找到上一次出现的位置，如果距离 $\le k$ 就有边，并查集维护连通性，特判 $1$ 的情况即可。

## 代码

```cpp
#include<bits/stdc++.h>

typedef long long LL;
using namespace std;
const int N = 2e6 + 10;
int p[N], s[N], tot, k, a[N], lst[N], fa[N];

void init(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!s[i])
            s[i] = p[++tot] = i;
        for (int j = 1; j <= tot && p[j] <= n / i; ++j) {
            s[i * p[j]] = p[j];
            if (!(i % p[j]))
                break;
        }
    }
}

int n;
vector<int> used;
bool vis[N];
LL ans;

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    if (find(x) != find(y))
        fa[fa[x]] = fa[y];
}

void solve() {
    cin >> n >> k;
    for (int i = n; i < n + n; ++i) {
        cin >> a[i];
        a[i - n] = a[i];
    }
    int tmp = n;
    n = (n << 1) - 1;
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
    for (int i = 1; i <= n; ++i) {
        int x = a[i];
        while (x != 1) {
            int now = s[x];
            int pre = lst[now];
            if (pre && i - pre <= k)
                merge(i, pre);
            lst[now] = i;
            while (!(x % now))
                x /= now;
            if (!vis[now]) {
                vis[now] = true;
                used.push_back(now);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (a[i] == 1)
            ans += tmp - abs(tmp - i);
        else if (find(i) == i)
            ++ans;
    }
    cout << ans << endl;
    ans = 0;
    for (int x: used) {
        vis[x] = false;
        lst[x] = 0;
    }
    used.clear();
}

int main() {
    init(1000000);
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}

```

---

## 作者：SegTree (赞：0)

## 题意
一个 $n\times n$ 的数表，满足 $b_{i,j}=a_{(j+(i-1)-1)\bmod n+1}$，两个点 $(x_1,y_1)$ 和 $(x_2,y_2)$ 连一条边当且仅当：

+ $|x_1-x_2|+|y_1-y_2|\le K$

+ $\gcd(b_{x_1,y_1},b_{x_2,y_2})>1$

给你序列 $a$ 和 $K$，求联通块个数，$n,a_{i,j}\le 10^6,2\le K\le 2\times 10^6$。

## 题解
由于 $K\ge 2$，所以同一非 $1$ 元素形成的对角线一定是一个联通块。

![](https://cdn.luogu.com.cn/upload/image_hosting/80hs7c5j.png)

因此，我们只需要考虑这 $\mathcal{O}(n)$ 个行之间的建边情况了。

我们考虑对于质因子 $g$，把它出现过的所有位置排序，将相邻位置差在 $K$ 以内的连一条边，使用并查集维护即可。

注意：特判 $a_i=1$。

[代码。](https://codeforces.com/contest/1978/submission/266546416)

---

## 作者：__vector__ (赞：0)

这场 Div.2 CDEF 难度是反过来的。  
**本做法复杂度可能劣于正解，但是能过。**
- 模拟样例。  
这个是倒数第二个样例：  
![](https://cdn.luogu.com.cn/upload/image_hosting/g3ntvclh.png)  
相同颜色圈住的数字代表相同连通块。  
容易发现，每个数组都构成了 $1$ 或 $2$ 条对角线。  
容易得出结论，左上角到右下角的对角线是由第一个元素组成，由此向左的每条对角线分别是第 $5,4,3,2$ 个元素构成的。  
由此向右的每条对角线分别是第 $2,3,4,5$ 个元素构成的。  

- 结论  
注意除了 $1$ 号元素以外，所有元素都分别组成了 $2$ 条对角线，分别位于 $1$ 号元素对角线的左边和右边，为了方便，暂时称 $1$ 号元素对角线左边的对角线成为左对角线，右边同理。  
将下面所述 $1$ 号构成的左对角线和右对角线看作同一条对角线。  
由上述，第 $1,2,3,4,5$ 个元素组成的右对角线的依次相邻（前后距离为 $1$）。第 $1,5,4,3,2$ 个元素组成的左对角线依次相邻。  
形式化，$1,2,3,\cdots,n$ 个元素组成的右对角线前后距离为 $1$，另外 $1,n,n-1,\cdots,2$ 的前后距离也是 $1$。  
由于 $k \ge 2$，除了值为 $1$ 的元素，所有元素组成的单独一条对角线（左对角线和右对角线独立）都是同一个连通块。
- 做法  
问题是如何处理所有非互质的数对。  
看到 $a_i \le 10^6$，这个限制意味着可以在调和级数复杂度内预处理每个数的质因数，随后每个 testcase 只需要枚举所有出现过的质因数，并记录包含这个质因数的所有元素，按照上述规则建边就可以了，然后按照上述结论建边就可以了。  
最后 dfs 一遍求出连通块个数。  
- 小细节  
值为 $1$ 的所有元素都是不同连通块，一个 $1$ 就能贡献 $n$ 个连通块，$1$ 应该被单独计算。  

最后复杂度是一开始的预处理质因数，再加上每个测试数据的所有元素的质因数个数总和，大量 STL 的使用也不影响通过。  
```cpp
#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(i,a,b) for(int i=a;i>=b;i--)
#define pb push_back
#define mkpr make_pair
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
int T;
template<class T>
void ckmx(T& a,T b){
    a=max(a,b);
}
template<class T>
void ckmn(T& a,T b){
    a=min(a,b);
}
typedef vector<int> vi;
typedef vector<ll> vl;
#define fi first
#define se second 
template<class T>
T gcd(T a,T b){
    return !b?a:gcd(b,a%b);
}
template<class T>
T lcm(T a,T b){
    return a/gcd(a,b)*b;
}
/*1,2,3,4,5
5,1,2,3,4
4,5,1,2,3
3,4,5,1,2
2,3,4,5,1
可以注意到，从 1 形成的左上-右下对角线向左右延申，向左分别是 5,4,3,2 形成的。  
向右分别是 2,3,4,5 形成的。  
同一个对角线全部连接。  
1-5-4-3-2 或 1-2-3-4-5 对角线距离是 1   
本质上，可以枚举所有出现过的质因数，枚举这个质因数对应的所有元素。  
然后枚举所有相邻编号元素，单独处理 1 号对角线
考虑 1~1e6 所有数的质因数。
*/
const int maxn=1e6+5;
int n,k,a[maxn];
vector<int> prims[maxn];
bool vis[maxn];
vector<int> div_to_elem[maxn];
vector<int> g[maxn*2];
void con(vi& ids){
	// ids 所有元素 gcd 不为 1，且按照元素 id 升序
	for(int& id:ids){
		if(id==1)continue;
		if(id-1+(n-id+1)<=k){
			g[id].emplace_back(id+n);
			g[id+n].emplace_back(id);
		}
	}
	if(ids.size()==1)return;
	//for(int& id:ids)printf("id %d\n",id);
//	puts("==========");
	for(int i=1;i<ids.size();i++){
		if(ids[i]-ids[i-1]<=k){
			g[ids[i]].emplace_back(ids[i-1]);
			g[ids[i-1]].emplace_back(ids[i]);
		//	printf("con = z(%d) z(%d)\n",ids[i],ids[i-1]);
		}
	}
	if(ids.front()==1){
		reverse(ids.begin()+1,ids.end());
		for(int i=1;i<ids.size();i++){
			if((ids[i-1]==1?(n+1):ids[i-1])-ids[i]<=k){
				g[ids[i]+n].emplace_back(ids[i-1]+n);
				g[ids[i-1]+n].emplace_back(ids[i]+n);
			//	printf("con = f(%d) f(%d)\n",ids[i],ids[i-1]);
			}
		}	
	}else{
		reverse(ids.begin(),ids.end());
		// mx,mx-1,...,mn
		if(n-ids.front()+1+ids.back()-1<=k){
			g[ids.front()+n].emplace_back(ids.back());
			g[ids.back()].emplace_back(ids.front()+n);
		}
		for(int i=1;i<ids.size();i++){
			if(((ids[i-1]==1?(n+1):ids[i-1]))-(ids[i])<=k){
				g[ids[i]+n].emplace_back(ids[i-1]+n);
				g[ids[i-1]+n].emplace_back(ids[i]+n);
			//	printf("con = f(%d) f(%d)\n",ids[i],ids[i-1]);
			}
		}	
	}
}
bool dfsvis[maxn*2];
void dfs(int u){
	dfsvis[u]=1;
	for(int& v:g[u]){
		if(!dfsvis[v])dfs(v);
	}
}
void solve(){
	scanf("%d%d",&n,&k);
	ll ans=0;
	FOR(i,1,n){
		scanf("%d",&a[i]);
		if(a[i]==1){
			ans+=n;
		}
	}
	vector<int> divs;
	FOR(i,1,n){
		for(int& div:prims[a[i]]){
			if(!vis[div]){
				vis[div]=1;
				divs.emplace_back(div);
			}
			div_to_elem[div].emplace_back(i);
		}
	}
	if(a[1]!=1)g[1].emplace_back(n+1);
	for(int& div:divs){
		con(div_to_elem[div]);
	}
	
	FOR(i,1,2*n){
		if(a[((i>n)?(i-n):(i))]!=1&&!dfsvis[i]){
			ans++;
			dfs(i);
		}
	}
	printf("%lld\n",ans);
	// clear
	for(int& div:divs){
		vis[div]=0;
		div_to_elem[div].clear();
	}
	FOR(i,1,2*n){
		g[i].clear();
		dfsvis[i]=0;
	}
}
int main()
{
	FOR(i,2,1000000){
		if(prims[i].empty()==0)continue;
		for(int j=i;j<=1000000;j+=i){
			prims[j].emplace_back(i);
		}
	}
	scanf("%d",&T);
	while(T--){
		solve();
	}
	return 0;
}

```

---

## 作者：未来姚班zyl (赞：0)

冷知识：这场 CDEF 是倒序排的。

## 题目大意

~~英语题面已经很详细了，可以用翻译软件翻译看看。~~

## 题目分析

首先由于 $k\ge 2$，所以对角线都在同一个连通块。

所以可以把矩阵翻转 $45\degree$ 来看，这样相当于 $2n-1$ 个数组成的序列，曼哈顿距离直接变成了下标距离。

连边也非常简单，我们从左往右扫，记录每个质因子出现的最后一个位置，然后连边就行了。

复杂度 $O(n\ln n)$。

然后你 WA 了。

因为初始时如果对角线上的数是 $1$，则这个对角线不会连成连通块。特判一下就可以。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(int x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=2e6+5,M=7e6+5,inf=(1LL<<31)-1,mod=998244353;
const ll llf=1e18;
int n,k,a[N],b[N],f[N];
bool vis[N];
int p[N],cnt,pre[N];
inline int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
inline void prep(){
	rep(i,2,N-5){
		if(!vis[i])pre[i]=i,p[++cnt]=i;
		for(int j=1;j<=cnt&&i*p[j]<=N-5;j++){
			vis[i*p[j]]=1,pre[i*p[j]]=p[j];
			if(i%p[j]==0)break;
		}
	}
}
map<int,int>P;
inline void Main(){
	n=read(),k=read();
	repn(i)a[i]=read();
	repn(i)b[i+n-1]=a[i];
	rep(i,2,n)b[i-1]=a[i];
	n=n*2-1;
	repn(i)f[i]=i;
	repn(i)a[i]=b[i];
	P.clear();
	int ans=0;
	repn(i)if(a[i]==1)ans+=n/2+1-abs(i-(n/2+1))-1;
	repn(i){
		while(a[i]>1){
			int w=P[pre[a[i]]];
			if(w&&i-w<=k)f[find(i)]=find(w);
			P[pre[a[i]]]=i;
			a[i]/=pre[a[i]];
		}
	}
	repn(i)vis[i]=0;
	repn(i)vis[find(i)]=1;
	repn(i)ans+=vis[i];
	cout <<ans<<'\n';
}
signed main(){
	prep();
	int T=read();
	while(T--)Main();
	return 0;
}	

```

---

