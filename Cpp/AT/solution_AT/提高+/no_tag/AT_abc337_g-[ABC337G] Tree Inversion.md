# [ABC337G] Tree Inversion

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc337/tasks/abc337_g

頂点 $ 1, $ 頂点 $ 2,\ldots, $ 頂点 $ N $ の $ N $ 頂点からなる木 $ T $ が与えられます。 $ i $ 番目 $ (1\leq\ i\lt\ N) $ の辺は頂点 $ u\ _\ i $ と頂点 $ v\ _\ i $ を結んでいます。

$ T $ の頂点 $ u $ について $ f(u) $ を次のように定めます。

- $ f(u)\coloneqq $ $ T $ の頂点 $ v $ と頂点 $ w $ の組であって、次の $ 2 $ つの条件を満たすものの個数
  - 頂点 $ u $ と頂点 $ v $ を結ぶパス上に頂点 $ w $ が含まれる。
  - $ v\lt\ w $
 
ただし、「頂点 $ u $ と頂点 $ v $ を結ぶパス上に頂点 $ w $ が含まれる」は、$ u=w $ や $ v=w $ のときにも成立するとします。

$ f(1),f(2),\ldots,f(N) $ の値を求めてください。

## 说明/提示

### 制約

- $ 2\leq\ N\leq2\times10\ ^\ 5 $
- $ 1\leq\ u\ _\ i\leq\ N\ (1\leq\ i\leq\ N) $
- $ 1\leq\ v\ _\ i\leq\ N\ (1\leq\ i\leq\ N) $
- 与えられるグラフは木
- 入力はすべて整数
 
### Sample Explanation 1

与えられる木は以下のようになります。 !\[\](https://img.atcoder.jp/abc337/f02c6287abee93272dda64faf9499a81.png) 例えば、$ f(4)=4 $ です。 実際、$ u=4 $ に対して $ (v,w)=(1,2),(1,4),(2,4),(3,4) $ の $ 4 $ 通りが条件を満たします。

### Sample Explanation 2

与えられる木は以下のようになります。 !\[\](https://img.atcoder.jp/abc337/e59ed095480b6f8ec4ecfc212f14e635.png) $ f(14) $ の値は、数列 $ (14,9,1,6,12,2,15,4,11,13,3,8,10,7,5) $ の転倒数 $ 57 $ になります。

## 样例 #1

### 输入

```
7
1 2
2 3
2 4
4 5
4 6
6 7```

### 输出

```
0 1 3 4 8 9 15```

## 样例 #2

### 输入

```
15
14 9
9 1
1 6
6 12
12 2
2 15
15 4
4 11
11 13
13 3
3 8
8 10
10 7
7 5```

### 输出

```
36 29 32 29 48 37 45 37 44 42 33 36 35 57 35```

## 样例 #3

### 输入

```
24
7 18
4 2
5 8
5 15
6 5
13 8
4 6
7 11
23 16
6 18
24 16
14 21
20 15
16 18
3 16
11 10
9 11
15 14
12 19
5 1
9 17
5 22
11 19```

### 输出

```
20 20 41 20 21 20 28 28 43 44 36 63 40 46 34 40 59 28 53 53 66 42 62 63```

# 题解

## 作者：yshpdyt (赞：8)

## 题意
一颗 $n$ 个节点的树，求所有 $u \in [1,n]$，以 $u$ 为根时，求点对 $(v,w)$ 数，满足 $v< w$ 且 $w$ 在 $u \rightarrow v$ 的路径上。

## Sol
就如题目所说的，采用 换根 $dp$。这里先规定一些名称。

记 $f_i$ 表示以 $i$ 为根的**子树**的答案。

记 $a_i$ 表示以 $i$ 为根的**子树**内小于 $i$ 的节点数量。

记 $h_i$ 表示以 $i$ 为根的**子树**内小于 $farher_{i}$ 的节点数量。

记 $g_i$ 表示以 $i$ 为根的**树**的答案。


根据换根 $dp$ 惯例，先考虑钦定 $1$为根节点，求出 $f_{1}$。

由题目描述，不难找出关系式。
$$f_x=a_x+\sum_{y\in son_x} f_y$$

而 $g_1=f_1$。

接着考虑换根。

![](https://cdn.luogu.com.cn/upload/image_hosting/qu50411x.png)

原来以 $x$ 为根，现在要把 $y$ 换成根，维护换根后 $g_y$ 基于 $g_x$ 的变化。

**红色部分**原来是 $x$ 的子树，换根后要减去这部分对 $x$ 的贡献，也就是减去 $y$ **子树内小于** $x$ 的结点数，即减去 $h_y$。

**蓝色部分**原来不是 $y$ 的子树，换根后要加上这部分对 $y$ 的贡献，也就是加上 $y$ **子树外小于** $y$ 的节点数，小于 $y$ 的节点树只有 $y-1$ 个，子树内占了 $a_y$ 个，所以要加上 $y-1-a_y$ 。

所以：
$$g_y=g_x+(y-1-a_y)-h_y$$

到这里推到出所有公式都比较简单，那么如何得到 $a_i$，$h_i$ 呢？

类似前缀和的思想，记录递归 $x$ 子树之前的答案，以及递归 $x$ 子树之后的答案，后者减去前者即可，用树状数组或线段树都可以做。

~~当然也可以可持久化~~。

时间复杂度 $O(n\log n)$。
## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 500005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll n;
ll f[N],g[N],a[N],h[N],tr[N];
//ai:以i为根的子树内比i小的数的个数
//fi:以i为根的子树的答案
//fu+=fv+au
//gv=gu-fv
vector<ll>v[N];
void add(ll x,ll t){
    for(int i=x;i<=n;i+=(i&(-i)))tr[i]+=t;
}
ll qr(ll x){
    ll ans=0;
    for(int i=x;i>0;i-=(i&(-i)))ans+=tr[i];
    return ans;
}
void dfs1(ll x,ll fa){
    a[x]=-qr(x-1);
    h[x]=-qr(fa-1);  
    //要在查完fa后再加入x，否则会导致x<fa的情况无法被统计到
    for(auto y:v[x])if(y!=fa)dfs1(y,x);
    add(x,1);
    a[x]+=qr(x-1);
    h[x]+=qr(fa-1);
    f[x]=a[x];
    for(auto y:v[x])if(y!=fa)f[x]+=f[y];
}
void dfs2(ll x,ll fa){
    for(auto y:v[x]){
        if(y==fa)continue;
        g[y]=g[x]-h[y]+(y-a[y]-1);
        dfs2(y,x);
    }
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>n;
    for(int i=1,x,y;i<n;i++){
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    dfs1(1,0);
    g[1]=f[1];
    dfs2(1,0);
    for(int i=1;i<=n;i++)cout<<g[i]<<" ";
    return 0;
}

```


---

## 作者：Genius_Star (赞：6)

### 思路：

定义 $sum_u$ 表示当 $1$ 为根时 $u$ 子树内编号 $<u$ 的点的个数。

定义 $dp_u$ 表示当 $1$ 为根时 $u$ 子树内 $w,u$ 满足的个数，明显：

$$dp_u=sum_u+\sum_{v \in E_u} dp_v$$

然后显然 $f_1=dp_1$。

考虑通过 $f_{fa_u}$ 将 $f_u$ 推出来：

- 首先是当 $u$ 转化为根后，$sum_u$ 的值将会变化，变化的值记为 $h_u$（即以 $1$ 为根时不在 $u$ 子树内且编号 $<u$ 的点的个数，当 $u$ 为根时，这些值将会被考虑到）。

- 其次当 $u$ 为根之后，$fa_u$ 是不能再算 $u$ 子树的贡献的，但是原来的 $f_{fa_u}$ 是计算了的，需要将其减去记为 $g_u$（即为在 $1$ 为根时 $u$ 子树内且编号 $<fa_u$ 的个数）。

则得到：

$$f_u=f_{fa_u}+h_u-g_u$$

最后 $sum$ 和 $g$ 的值可以树状数组或者线段树解决。（每次维护值域的前缀和，先减去不在子树内 $<u$ 的值，然后再加上全局 $<u$ 的值）

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=200200;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n;
ll a[N],sum[N],g[N],h[N],dp[N],f[N];
vector<ll> E[N];
void Add(ll u,ll v){
	E[u].push_back(v);
	E[v].push_back(u);
}
ll lowbit(ll x){
	return x&(-x);
}
void add(ll x,ll v){
    for(ll i=x;i<=n;i+=lowbit(i)) 
	  a[i]+=v;
}
ll qurey(ll x){
    ll ans=0;
    for(ll i=x;i;i-=lowbit(i))
	  ans+=a[i];
    return ans;
}
void dfs1(ll x,ll fa){
    sum[x]=-qurey(x-1),g[x]=-qurey(fa-1),add(x,1);
    for(auto y:E[x]){
        if(y==fa) 
		  continue;
        dfs1(y,x);
    }
    sum[x]+=qurey(x-1),g[x]+=qurey(fa-1),h[x]=x-1-sum[x];
    dp[x]=sum[x];
    for(auto y:E[x]){
        if(y==fa) 
		  continue;
        dp[x]+=dp[y];
    }
}
void dfs2(ll x,ll fa){
    if(fa)
      f[x]=f[fa]-g[x]+h[x];
    for(auto y:E[x]){
        if(y==fa) 
		  continue;
        dfs2(y,x);
    }
}
int main(){
	n=read();
	for(int u,v,i=1;i<n;i++){
		u=read(),v=read();
		Add(u,v);
	}
	dfs1(1,1);
	f[1]=dp[1];
	dfs2(1,0);
	for(int i=1;i<=n;i++){
		write(f[i]);
		putchar(' ');
	}
	return 0;
}
```
###### 

---

## 作者：FFTotoro (赞：4)

题解区似乎都用的 BIT（树状数组），这里供一个使用 `pbds` 平衡树的神奇做法。

对于一个结点 $u$，考虑贡献是怎么来的：一种可能是 $v$ 和 $w$ 在其子树内——此时只需统计每个结点的子树内有多少个编号比它小的，可以使用**树上启发式合并**，合并的东西是平衡树$\color{Red}^1$，可以借助 `gnu_pbds` 内置的 `tree` 实现；还有一种来源是子树外的（分两种情况，$v$ 在 $w$ 子树内和 $v$ 在 $w$ 子树外只需直接一路下传父亲贡献并去掉 $u$ 本身的贡献），是比较显然的换根 DP。细节比较多注意不要写错。

时间复杂度 $O(n\log^2n)$，可以通过。

关于 `__gnu_pbds::tree` 的合并$\color{Red}^1$：选手可能在赛时使用 `swap(A,B)` 这种写法来合并，但是与 STL（C++11 往后）不同，在 `__gnu_pbds::tree` 中这样写的**时间复杂度是 $O(\max\{|A|,|B|\})$ 的**，然而 `A.swap(B)` 却是 $O(1)$ 的，需要注意一下。

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define int long long
using namespace std;
using namespace __gnu_pbds;
typedef tree<int,null_type,less<>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
main(){
  ios::sync_with_stdio(false);
  int n; cin>>n;
  vector<vector<int> > g(n);
  for(int i=1;i<n;i++){
    int u,v; cin>>u>>v;
    g[--u].emplace_back(--v);
    g[v].emplace_back(u);
  }
  vector<int> fl(n),f1(n),f2(n),f3(n);
  vector<ordered_set> s(n);
  function<void(int,int)> dfs=[&](int u,int r){
    int h_id=-1,h=0;
    for(int i:g[u])
      if(i!=r){
        dfs(i,u),f3[u]+=f3[i];
        if(s[i].size()>h)h=s[i].size(),h_id=i;
      } // 找重儿子
    if(~h_id)s[u].swap(s[h_id]); // 就这儿要注意
    for(int i:g[u])
      if(i!=r&&i!=h_id)
        for(int j:s[i])s[u].insert(j); // 暴力合并
    int x=s[u].order_of_key(u);
    f3[u]+=(fl[u]=x),s[u].insert(u);
    f1[u]=s[u].order_of_key(r);
  }; // 预处理及计算子树内的答案
  function<void(int,int)> dfs2=[&](int u,int r){
    if(u)f2[u]=f2[r]+f3[r]-f3[u]+(u-fl[u])-f1[u];
    for(int i:g[u])
      if(i!=r)dfs2(i,u);
  }; // 计算子树外的答案
  dfs(0,0),dfs2(0,0);
  for(int i=0;i<n;i++)
    cout<<f2[i]+f3[i]<<' ';
  cout<<endl;
  return 0;
}
```

---

## 作者：lfxxx (赞：4)

最简单的一集。

考虑从小到大枚举 $w$ 顺便加入所有的 $v$，偏序关系就已经没了，然后讨论 $u,v$ 相对 $w$ 的位置关系，如一个在子树内一个在子树外与在不同的子树内，无论如何都是一个子树或者全局刨去一个子树或者一个子树刨去一个子树内的 $v$ 给类似的 $u$ 做贡献，直接树状数组在 dfs 序上维护即可，时间复杂度 $O(n \log n)$ 毫无卡常就过了。

```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
#define int long long
using namespace std;
const int maxn = 2e5+114;
int dfncnt,L[maxn],R[maxn],sz[maxn],n;
int p[maxn],answer[maxn];
//p 数组是点加区间查询 answer 数组是区间加点查询
void ins(int u){
    int pos=L[u];
    while(pos<=n) p[pos]++,pos+=lowbit(pos);
}
int pre(int x){
    int res=0;
    while(x>0) res+=p[x],x-=lowbit(x);
    return res;
}
int ask(int u){
    return pre(R[u])-pre(L[u]-1);
}
void add(int l,int r,int c){
    if(l>r) return ;
    r++;
    while(l<=n) answer[l]+=c,l+=lowbit(l);
    while(r<=n) answer[r]-=c,r+=lowbit(r);
}
int solve(int u){
    int pos=L[u];
    int res=0;
    while(pos>0) res+=answer[pos],pos-=lowbit(pos);
    return res;
}
int father[maxn];
vector<int> edge[maxn];
void dfs(int u,int fa){
    L[u]=++dfncnt;
    father[u]=fa;
    for(int v:edge[u]) if(v!=fa) dfs(v,u);
    R[u]=dfncnt;
}
signed main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++){
        //将点 i 作为 w 加入，此前已经加入的点视为 v
        int w=i;
        add(1,L[w]-1,ask(w));
        add(R[w]+1,n,ask(w));
        add(L[w],R[w],ask(1)-ask(w));
        for(int u:edge[w]){
            if(u==father[w]) continue;
            add(L[u],R[u],ask(w)-ask(u));
        }
        add(L[w],L[w],ask(w));
        ins(w);
    }
    for(int i=1;i<=n;i++) cout<<solve(i)<<' ';
    return 0;
}
```



---

## 作者：zhongpeilin (赞：4)

## 题目大意：
有一个 $n$ 个点的树，设 $f_{u}$ 表示有多少个 $v, w$ 满足 $w$ 在 $u \to v$ 路径上且 $w > v$。
## 解题思路：
因为要对每个点都算一遍，我们不难想到换根 dp。  
首先我们需要算出来 $f_{1}$，为了方便算出，我们设 $dp_{u}$ 表示以 $u$ 为根的子树里，有多少个 $w, v$ 满足条件。但是我们发现这个不能直接算，因为有可能出现 $w=u$ 的情况，所以我们设 $cnt_{u}$ 表示在 $u$ 的子树中，有多少 $v$ 满足 $u > v$。那么 $cnt$ 就可以用树状数组来解决，可是我们不难想到现在在树状数组中的不一定全都是 $x$ 子树里的，于是我们可以在一开始进入 $x$ 时，将 $x$ 子树以外的给减去。  
回到 $dp_{u}$，我们讨论一下 $w,v$ 是在 $u$ 的哪个儿子节点的子树里的，有：
$$dp_{u} = \sum_{v \in son_{u}}dp_{v} + cnt_{u}$$
$cnt_{u}$ 是因为 $w=u$ 的情况。  
然后 $f_{1} = dp_{1}$。  
接下来就是换根了，考虑从 `1` 号到他的儿子节点会发生那些变化。  
1. 当他的儿子变成根的时候，`1` 号所在的子树中的答案就变成了 $f_{1} - dp_{son}$ 再减去不在子树 $son$ 且 $u = w = 1$ 的方案数再加上 $u=w=son$ 且 $v$ 在 $son$ 子树以外的的方案数。
2. 原本的 $son$ 的子树内的方案数，即 $dp_{son}$。  

但是我们发现如果只有 $cnt, dp,f$ 的话是无法算出第一种情况的，所以我们再设 $g_{x}$ 表示 $x$ 子树内，有多少个节点 $v$ 使得 $v < fa$，设 $h_{x}$ 表示在 $x$ 子树以外的节点里，有多少 $v$ 满足 $x > v$。  
那么 $g_{x}$ 的求法和 $cnt$ 同理，然后 $h_{x} = x-1 - cnt_{x}$。  
所以综上，我们有 
$$f_{son} = dp_{son} + f_{fa} -dp_{son} - g_{son} + h_{son}$$
$$f_{son} = f_{fa} - g_{son} + h_{son}$$
复杂度就是 $O(n \log n)$。

## code：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int C[200005];
vector<int> G[200005];
int n, cnt[200005], dp[200005], f[200005], g[200005], h[200005];

void add(int x, int c){
	for(int i = x; i <= n; i += (i & (-i))) C[i] += c;
}
int ask(int x){
	int ans = 0;
	for(int i = x; i; i -= (i & (-i))) ans +=C[i];
	return ans;
}

void dfs1(int x, int fa){
	cnt[x] = -ask(x - 1); g[x] = -ask(fa - 1);
	add(x, 1);
	for(int i = 0; i < G[x].size(); i++){
		int y = G[x][i];
		if(y == fa) continue;
		dfs1(y, x);
	}
	cnt[x] += ask(x - 1); g[x] += ask(fa - 1);
	h[x] = x - 1 - cnt[x];
	dp[x] = cnt[x];
	for(int i = 0; i < G[x].size(); i++){
		int y = G[x][i];
		if(y == fa) continue;
		dp[x] += dp[y];
	}
}

void dfs2(int x, int fa){
	if(x != 1){
		f[x] = f[fa] - g[x] + h[x];
	}
	for(int i = 0; i < G[x].size(); i++){
		int y = G[x][i];
		if(y == fa) continue;
		dfs2(y, x);
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin >> n;
	for(int i = 1; i < n; i++){
		int x, y;
		cin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	dfs1(1, 1);
	f[1] = dp[1];
	dfs2(1, 0);
	for(int i = 1; i <= n; i++) cout << f[i] << " ";
	return 0;
}
```

---

## 作者：SunsetLake (赞：2)

## 思路

对于每个 $1 \le i \le n$ 的 $i$ 都要求答案，那我们考虑 dp，去思考如何转移 $f_i$。先不考虑全局，只考虑子树内的贡献，设 $g_u$ 表示以 $u$ 为根的子树内，对 $u$ 来说满足条件的点对数。对于 $u$ 的儿子 $v$，对 $v$ 来说合法那么对 $u$ 来说也一定合法。因为从 $v$ 开始的路径扩展到从 $u$ 开始的路径只会让路径边长增加，自然也会包含那些点对，那么 $g_u$ 就可以累加所有的 $g_v$。接下来就只有 $w=u$ 的情况了（其他情况会包括在 $g_v$ 中），问题就转化成了：求一棵子树内，小于点 $u$ 的点有多少个。把每个节点按照他们的 dfs 序编号，子树内的编号就连续了，变成了一个序列问题，直接主席树就好了。

接下来就可以考虑换根了。从 $u$ 转移到他的儿子 $v$，可以先累加 $f_u$（全局的点对数）的贡献，但这样会把 $w=u$，且他和 $v$ 子树内的点配对的情况算进去，这实际是不合法的，因此减去 $v$ 子树中 $<u$ 的点的数量。同时还要加上 $v$ 子树外的点与 $w=v$ 配对的情况，这部分就整体减局部，用全局 $<v$ 的点的数量减去 $v$ 子树内 $<v$ 的点的数量即可。

此题便做完了。
## code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const int N=2e5+5;
int n;
int idx,id[N],node[N],sz[N];
ll f[N];
vector<int>e[N];
int root[N],cnt;
struct Tree{
	int l,r;
	int sum;
}tr[N<<5];
void build(int &p,int l,int r){
	p=++cnt;
	if(l==r)return;
	int mid=l+r>>1;
	build(tr[p].l,l,mid);
	build(tr[p].r,mid+1,r);
}
int update(int p,int l,int r,int v){
	++cnt;
	tr[cnt]=tr[p];
	tr[cnt].sum++;
	p=cnt;
	if(l==r)return p;
	int mid=l+r>>1;
	if(v<=mid)tr[p].l=update(tr[p].l,l,mid,v);
	else tr[p].r=update(tr[p].r,mid+1,r,v);
	return p;
}
int query(int pl,int pr,int l,int r,int v){
	if(!v)return 0;
	if(l==r)return tr[pr].sum-tr[pl].sum;
	int mid=l+r>>1;
	int res=0;
	if(v<=mid)res+=query(tr[pl].l,tr[pr].l,l,mid,v);
	else res+=tr[tr[pr].l].sum-tr[tr[pl].l].sum+query(tr[pl].r,tr[pr].r,mid+1,r,v);
	return res;
}
void dfs1(int u,int fa){
	id[u]=++idx;node[idx]=u;sz[u]=1;
	for(auto v:e[u])if(v!=fa)dfs1(v,u),sz[u]+=sz[v];
}
void dfs(int u,int fa){
	f[u]=query(root[id[u]-1],root[id[u]+sz[u]-1],1,n,u-1);//预处理出 g[u]
	for(auto v:e[u]){
		if(v==fa)continue;
		dfs(v,u);
		f[u]+=f[v];
	}
}
void fds(int u,int fa){
	for(auto v:e[u]){
		if(v==fa)continue;
		f[v]=f[u]-query(root[id[v]-1],root[id[v]+sz[v]-1],1,n,u-1)+query(root[0],root[n],1,n,v-1)-query(root[id[v]-1],root[id[v]+sz[v]-1],1,n,v-1);//换根
		fds(v,u);
	}
}
int main(){
	cin>>n;
	for(int i=1;i<n;++i){
		int a,b;
		cin>>a>>b;
		e[a].pb(b);e[b].pb(a);
	}
	dfs1(1,0);
	build(root[0],1,n);
	for(int i=1;i<=n;++i)root[i]=update(root[i-1],1,n,node[i]);//主席树求区间小于某个数的个数
	dfs(1,0);
	fds(1,0);
	for(int i=1;i<=n;++i)cout<<f[i]<<" ";
	return 0;
}
```


---

## 作者：Super_Cube (赞：1)

# Solution

简单路径不好统计，但是若 $u$ 为根节点，将会方便得多。

换根 dp。

先来做不换根的情况。设 $dp_i$ 为 $i$ 的子树内且不考虑点 $i$ 的情况下符合条件的点对数量，$f_i$ 为 $i$ 的子树内点编号小于 $i$ 的个数。转移：$dp_i=\displaystyle\sum_{j\in\operatorname{son}_i}{dp}_j+f_j$。$f$ 可单独用线段树合并求出。假设此时根节点编号为 $rt$，那么其答案即为 $dp_{rt}+f_{rt}$，且 $f_{rt}$ 必为 $rt-1$。

接下来考虑换根。对于写换根的技巧，就是把 $i$ 当作 $j$ 的儿子，把 $i$ 中 $j$ 存在的贡献消除掉，然后正常转移就好了。具体的，令 $dp'=dp_i-dp_j-f_j$，$f'=i-1-g_j$，其中 $g_j$ 为点 $j$ 及其子树内点编号小于 $i$ 的个数，也可以提前用线段树合并求出。那么新转移为 $dp_j\gets dp_j+dp'+f'$。

---

## 作者：不知名用户 (赞：1)

给定 $n$ 个节点的树，对每个点 $u$ 求满足一下要求的点对 $(v,w)$ 的数量：$v<w;w$ 在 $u$ 到 $v$ 的路径上（$w$ 可以等于 $u$ 或 $v$）。对每个点输出这个值。

发现直接求这个值不好求，考虑 $w$ 对 $u$ 的贡献。从小到大枚举 $w$，同步插入 $v$，考虑不同位置的 $v$ 对 $u$ 的贡献。

若 $v$ 在 $w$ 子树外，$v$ 贡献到 $w$ 子树内。

否则设 $v$ 在 $w$ 的子节点 $x$ 的子树内，$v$ 贡献到所有点除了 $x$ 子树的点。

发现这些点的 DFN 序是树上连续的一段。维护两个树状数组：一个用来插入 $v$（单点加一）同时查询子树和（对应到 DFN 序上的区间），另一个用来实现区间加、统计答案（也可以最后前缀和一下）。复杂度 $\Theta(n\log n)$，瓶颈在树状数组上。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
vector<int>g[N];
int n, l[N], r[N], fa[N], dfn;
struct jzc
{
	int c[N];
	void add(int a, int x){for(;a<=n;a+=(a&-a))c[a]+=x;}
	void add(int l, int r, int x){add(l,x),add(r+1,-x);}
	int ask(int a){int b=0;for(;a;a-=(a&-a))b+=c[a];return b;}
	int ask(int l, int r){return ask(r)-ask(l-1);}
}c1,c2;
void dfs(int x, int f)
{
	fa[x] = f, l[x] = ++dfn;
	for(auto j:g[x]) if(j!=f) dfs(j,x);
	r[x] = dfn;
}

signed main()
{
	int i, a, b;
	scanf("%lld", &n);
	for(i=1;i<n;i++) scanf("%lld%lld", &a, &b), g[a].emplace_back(b), g[b].emplace_back(a);
	dfs(1,0);
	for(i=1;i<=n;i++)
	{
		c2.add(l[i],r[i],c1.ask(1,n)-c1.ask(l[i],r[i]));
		for(auto j:g[i]) if(j!=fa[i])
			c2.add(1,n,c1.ask(l[j],r[j])), c2.add(l[j],r[j],-c1.ask(l[j],r[j]));
		c1.add(l[i],1);
	}
	for(i=1;i<=n;i++) printf("%lld ", c2.ask(l[i]));
	return 0;
}
```

---

## 作者：OldDriverTree (赞：1)

场切 G 题祭。

双倍经验：[AT_ttpc2019_m Inversion Numbers of Tree](https://www.luogu.com.cn/problem/AT_ttpc2019_m)。

~~众所周知，双倍经验等于题解双倍经验~~。

# Solution

换根 $\texttt{DP}$，设 $f_x$ 表示以 $x$ 为根的逆序对个数。

先求出 $f_1$ 的值，枚举路径的另一个端点 $u$，$u$ 对 $f_1$ 的贡献就是 $u$ 到 $1$ 的路径上大于 $u$ 的节点个数，$\texttt{DFS}$ 一遍，拿树状数组搞一下就行了。

再考虑求出 $f_{fa_u}$ 后，怎么求出 $f_u$ 的值。

先考虑对于在 $u$ 子树内的节点 $x$ 对 $f_u$ 贡献的变化，由于到 $u$ 的路径上都少了一个节点 $fa_u$，答案就减少了 $\sum_{x\in tree_u} [y<fa_x]$。

再考虑子树外的节点 $x$ 对 $f_u$ 贡献的变化，由于到 $u$ 的路径上都多了一个节点 $u$，答案就增加了 $\sum_{x\not\in tree_u} [x<u]$。考虑补集转化，用整棵树的个数减去子树内的个数，就是 $u-1-\sum_{x\in tree_u} [x<u]$。

那么只需要维护 $u$ 子树内的所有数构成的树状数组就能求出 $f_u$，$\texttt{DSU on tree}$ 即可，时间复杂度 $O(n\log^2 n)$。

# Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+1;
int siz[N],son[N];
vector<int> g[N];
long long f[N];
int n,Son,T[N];
int w[N];

int read() {
	int x=0; char c=0; while (!isdigit(c) ) c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return x;
}
void add(int x,int v) { while (x<=n) T[x]+=v,x+=x&-x; }
int query(int x,int sum=0) { while (x) sum+=T[x],x&=x-1; return sum; }

void dfs1(int u,int fa)
{
	siz[u]=1,add(u,1);
	f[1]+=query(n)-query(u);
	for (int v:g[u]) if (v^fa) {
		dfs1(v,u),siz[u]+=siz[v];
		if (siz[v]>siz[son[u] ]) son[u]=v;
	}
	add(u,-1);
}
void add(int u,int fa,int w) {
	add(u,w); for (int v:g[u])
	if (v^fa&&v^Son) add(v,u,w);
}
void dfs(int u,int fa) {
	for (int v:g[u]) if (v^fa&&v^son[u]) dfs(v,u),add(v,u,-1);
	if (son[u]) dfs(son[u],u),Son=son[u]; add(u,fa,1),Son=0;
	if (fa) w[u]=-query(fa-1)+u-1-query(u-1);
}
void solve(int u,int fa) {
	for (int v:g[u]) if (v^fa)
	f[v]=f[u]+w[v],solve(v,u);
}
main()
{
	n=read();
	for (int i=1,x,y;i<n;i++)
	{
		x=read(),y=read();
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs1(1,0),dfs(1,0),solve(1,0);
	for (int i=1;i<=n;i++) printf("%lld ",f[i]);
	return 0;
}
```

---

## 作者：_fairytale_ (赞：1)

# 前言

我怎么感觉我做法这么小丑。就嗯做是吧。

赛时感觉比 F 简单，先开的这个，比赛结束都没调出来，结果挂在线段树合并上了，绷不住了。

## 本题解使用线段树合并 + 换根 DP，复杂度 $\mathcal O(n \log n)$。

首先钦定 $1$ 号节点为根，定义**此时**的结点 $u$ 的父亲为 $fa[u]$。

我们不难发现，假设 $w,v$ 都在 $u$ 的子树中，这个问题是非常好处理的。只需要记 $h[u]$ 表示 $u$ 子树中有多少个点的编号比 $u$ 小，然后答案就是 $u$ 子树中的所有 $h$ 之和，这个记为 $s[u]$。$h[u]$ 的处理可以轻松地用线段树合并解决。

然后我们显然还有一部分没有算，即来自**以 $u$ 为根**时，$fa[u]$ 这棵子树对 $u$ 的贡献，记为 $q[u]$。对于 $q[u]$ 的处理，我们借用换根 DP 的思想和一个小容斥。我们画个图理解一下。

下面简记 $fa[u]$ 为 $f$。

![](https://cdn.luogu.com.cn/upload/image_hosting/l5v3oum9.png)

这里假设 $q[f]$ 已经处理好了，由定义可知，$q[f]$ 为图中红色部分对 $f$ 的贡献，这部分贡献可以原封不动地继承给 $u$。

然后 $u$ 所需要的还有绿色部分对 $f$ 的贡献，这部分也应该继承过来，而且是好处理的，答案是 $s[f]-s[u]-h[f]$。

但 $f$ 对 $u$ 的贡献，除开红色部分已经计算好了以外，应该描述为，“绿色部分中有多少点的编号小于 $f$”。这个问题可以用 $h[f]$ 减去“紫色部分中有多少点的编号小于 $f$”。这个同样可以用线段树合并解决，但是这里有一个点要注意：

如果你写的是不新开结点的线段树合并，查询“紫色部分中有多少点的编号小于 $f$ ”时要在第一次 dfs 时就处理好，记 $prew[u]$ 表示“在 $u$ 的子树中有多少结点编号小于 $f$”。因为当你这个结点的线段树往上合并的时候会改变线段树的形态，最后只有根结点的线段树是一定正确的。

最后还有一部分，是在红色和蓝色部分中所有结点直接对 $u$ 的贡献，可以描述为“这两部分中有多少结点编号小于 $u$”，这个答案直接用 $u-1-h[u]$ 计算即可。

所以我们得到了最终式子：
$$q[u]=q[f]+s[f]-s[u]-h[f]+h[f]-prew[u]+u-1-h[u]$$
发现可以化简一下：
$$q[u]=q[f]+s[f]-s[u]-prew[u]+u-1-h[u]$$

最终题目中的 $f(u)$ 即为 $s[u]+q[u]$。

```cpp
#include<bits/stdc++.h>
#define re register
#define ll long long
#define mid ((l+r)>>1)
#define rep(x,a,b) for(re int (x)=(a);(x)<=(b);++(x))
using namespace std;
#define maxn 201000
int n,m;
int h[maxn];
vector<int>g[maxn];
struct tree{
	int ls,rs,sum;
}t[maxn<<5];
int rt[maxn],tot;
void mrg(int &x,int y,int l,int r){
	if(!x||!y)x+=y;
	else if(l==r)t[x].sum+=t[y].sum;
	else{
		mrg(t[x].ls,t[y].ls,l,mid);
		mrg(t[x].rs,t[y].rs,mid+1,r);
		t[x].sum=t[t[x].ls].sum+t[t[x].rs].sum;
	}
}
void modify(int &p,int l,int r,int pos,int v){
	if(!p)p=++tot;
	t[p].sum+=v;
	if(l==r)return;
	if(mid>=pos)modify(t[p].ls,l,mid,pos,v);
	else modify(t[p].rs,mid+1,r,pos,v);
}
int query(int p,int l,int r,int L,int R){
	if(L>R||!p)return 0;
	if(L<=l&&r<=R)return t[p].sum;
	int res=0;
	if(mid>=L)res+=query(t[p].ls,l,mid,L,R);
	if(mid<R)res+=query(t[p].rs,mid+1,r,L,R);
	return res;
}
ll s[maxn];
ll w[maxn],q[maxn];
int prew[maxn];
void dfs1(int u,int f){
	modify(rt[u],1,n,u,1);
	for(auto v:g[u]){
		if(v==f)continue;
		dfs1(v,u);
		s[u]+=s[v];
		mrg(rt[u],rt[v],1,n);
	}
	h[u]=query(rt[u],1,n,1,u-1);
	prew[u]=query(rt[u],1,n,1,f-1);
	s[u]+=h[u];
}
void dfs2(int u,int f){
	if(u!=1)q[u]=q[f]+u-1-h[u]+s[f]-s[u]-prew[u];
	for(auto v:g[u])if(v!=f){
		dfs2(v,u);
	}
}
int u,v;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin>>n;
    rep(i,1,n-1){
    	cin>>u>>v;
    	g[u].emplace_back(v);
    	g[v].emplace_back(u);
	}
	dfs1(1,0);
	dfs2(1,0);
	rep(i,1,n){
		cout<<s[i]+q[i]<<' ';
	} 
	return 0;
}
```

---

## 作者：zzzyyyyhhhhh (赞：0)

树套树加换根。

考虑换根 dp，先思考如何统计子树中的答案。点 $i$ 答案是所有儿子的答案加上 $i$ 作为 $w$ 点的贡献，即 $i$ 的子树内编号小于 $i$ 的点的个数。

这个操作可以用树状数组套平衡树解决，因为是静态查询，所以直接用`vector`代替平衡树即可,这部分实现。
```cpp

vector<int> v[N];
void add(int pos,int x)
{
	for(;pos<=n;pos+=pos&-pos)v[pos].push_back(x);
}
int get(int l,int r,int x)
{
	int res=0;
	for(;r;r-=r&-r)res+=lower_bound(v[r].begin(),v[r].end(),x)-v[r].begin();
	l--;
	if(l>0)for(;l;l-=l&-l)res-=lower_bound(v[l].begin(),v[l].end(),x)-v[l].begin();
	return res;
}
```

有了子树答案后考虑计算最终的答案，以 $1$ 作为根，$1$ 号节点答案即子树内答案，其他节点可以从自己的父亲转移过来。设 $p_i$ 为子树外编号小于 $i$ 的点的个数，$k_i$ 为子树内小于父节点编号的点的个数。 
$ans_i=ans_{f_i}-k_i+p_i$。

整体代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5+100;
int n;
vector<int> a[N];
vector<int> v[N];
void add(int pos,int x)
{
	for(;pos<=n;pos+=pos&-pos)v[pos].push_back(x);
}
int get(int l,int r,int x)
{
	int res=0;
	for(;r;r-=r&-r)res+=lower_bound(v[r].begin(),v[r].end(),x)-v[r].begin();
	l--;
	if(l>0)for(;l;l-=l&-l)res-=lower_bound(v[l].begin(),v[l].end(),x)-v[l].begin();
	return res;
}
inline int get1(int l,int r,int x)
{
	int res=0;
	if(l>1)
	{
		res+=get(1,l-1,x);
	}
	if(r<n)
	{
		res+=get(r+1,n,x);
	}
	return res;
}
int dfn[N],udfn[N],tot,ls[N];
void dfs(int x,int fa)
{
	dfn[x]=++tot;
	udfn[tot]=x;
	for(auto i:a[x])
	{
		if(i==fa)continue;
		dfs(i,x);
	}
	ls[x]=tot;
}
int g[N],f[N];
void dfs1(int x,int fa)
{
	for(auto i:a[x])
	{
		if(i==fa)continue;
		dfs1(i,x);
		g[x]+=g[i];
	}
	g[x]+=get(dfn[x],ls[x],x);
}
void dfs2(int x,int fa)
{
	f[x]+=f[fa];
	f[x]-=get(dfn[x],ls[x],fa);
	f[x]+=get1(dfn[x],ls[x],x);
	for(auto i:a[x])
	{
		if(i==fa)continue;
		dfs2(i,x);
	}
}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	int x,y;
	for(int i=1;i<n;i++)
	{
		cin>>x>>y;
		a[x].push_back(y);
		a[y].push_back(x);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)
	{
		add(dfn[i],i);
	}
	for(int i=1;i<=n;i++)
	{
		sort(v[i].begin(),v[i].end());
	}
	dfs1(1,0);
	f[1]=g[1];
	dfs2(1,0);
	for(int i=1;i<=n;i++)cout<<f[i]<<' ';
}
```

---

## 作者：AC_love (赞：0)

换根 DP + dsu on tree。

设 $f(i)$ 表示以 $i$ 为根时的答案。

首先 dfs 一遍可以求出 $f(1)$。

考虑如何根据 $f(fa_x)$ 求出 $f(x)$。

不难发现：从 $f(fa_x)$ 到 $f(x)$ 需要减去 $fa_x$ 在 $x$ 子树中的贡献，然后加上 $x$ 对整棵树的贡献，最后再减去 $x$ 对自己子树的贡献（因为这一部分重复计算了两次）。

这三个贡献可以分别维护。

$fa_x$ 在 $x$ 子树中的贡献和 $x$ 在 $x$ 子树的贡献，我们可以 dsu on tree 一起解决。

$x$ 对整棵树的贡献就是 $x - 1$。

[code](https://atcoder.jp/contests/abc337/submissions/59459080)

---

## 作者：Fzrcy (赞：0)

> 简要题意：给你一个树 $T$，设 $f(i)$ 表示满足合法二元组 $(v,w)$ 的个数（$(v,w)$ 合法当且仅当 $w$ 在 $u$ 到 $v$ 的最短路径上，且 $w>v$）。求 $f(1),\dots,f(n)$。

首先我们把树 $T$ 的根定为 $1$，然后枚举 $w$，然后枚举 $w$ 的子树中的合法的 $v$（$v\not\in \operatorname{subtree}(w)$ 的情况类似），设 $v$ 在子树 $x$ 中（$x$ 是 $w$ 的儿子），那么二元组 $(v,w)$ 会对所有 $u\not\in \operatorname{subtree}(x)$ 产生贡献，放在 dfs 序上就是区间加，然后用线段树合并维护子树 $x$ 代表的集合，那么求出子树 $x$ 中合法的 $v$ 的个数就很简单了，时间空间复杂度均为 $O(n\log n)$。

```cpp
// Fzrcy
#include <bits/stdc++.h>
using namespace std;
constexpr int N=4e5+9;
int n,d1[N],d2[N],dc,rt[N];
vector<int>e[N];
struct SGT{
    int lc[N*30],rc[N*30],t[N*30],cnt;
    void I(int &k,int l,int r,int x){
        !k&&(k=++cnt);++t[k];
        if(l==r)return;int m=l+r>>1;
        if(x<=m)I(lc[k],l,m,x);
        else I(rc[k],m+1,r,x);
    }
    int A(int k,int l,int r,int x,int y){
        if(x>y)return 0;
        if(!k||l>=x&&r<=y)return t[k];
        int m=l+r>>1,e=0;
        if(x<=m)e+=A(lc[k],l,m,x,y);
        if(y>m)e+=A(rc[k],m+1,r,x,y);
        return e;
    }
    int g(int x,int y){
        if(!x||!y)return x|y;t[x]+=t[y];
        lc[x]=g(lc[x],lc[y]);
        rc[x]=g(rc[x],rc[y]);
        return x;
    }
}SMT;
typedef long long ll;
struct BIT{
    ll c[N];
    void I(ll x,ll v){for(;x<N;x+=x&-x)c[x]+=v;}
    void I(ll l,ll r,ll v){I(l,v),I(r+1,-v);}
    ll A(ll x){ll r=0;for(;x;x-=x&-x)r+=c[x];return r;}
}Tr;
void dfs(int u,int fa){
    d1[u]=++dc;
    for(int v:e[u])if(v^fa)dfs(v,u);
    d2[u]=dc;
}
void oth(ll k,ll v){
    ll l=d1[k],r=d2[k];
    if(l>1)Tr.I(1,l-1,v);
    if(r<n)Tr.I(r+1,n,v);
}
void dp(int u,int fa){
    for(int v:e[u])if(v^fa)
        dp(v,u),oth(v,SMT.A(rt[v],1,n,1,u)),
        rt[u]=SMT.g(rt[u],rt[v]);
    SMT.I(rt[u],1,n,u);
    Tr.I(d1[u],d2[u],u-SMT.A(rt[u],1,n,1,u));
}
int main(){
    cin>>n;
    for(int i=1,x,y;i<n;i++)
        cin>>x>>y,e[x].push_back(y),
        e[y].push_back(x);
    dfs(1,0),dp(1,0);
    for(ll i=1;i<=n;i++)cout<<Tr.A(d1[i])<<' ';
    return cout<<endl,0;
}
```

---

## 作者：huangrenheluogu (赞：0)

$w$ 在 $u,v$ 中间，所以一个比较套路的做法是枚举 $w$。

考虑 $u$ 和 $w$ 没关系，而且求 $f_u$，所以从 $v$ 入手。

![](https://cdn.luogu.com.cn/upload/image_hosting/b7n1i2he.png)

那么，$w$ 可以把树切成很多连通块，标号就是 $1,2,\cdots,k$。

因为要找和 $v$ 的关系，所以记 $s_i$ 为第 $i$ 个连通块内数字小于 $w$ 的元素个数，他们可以成为 $v$，为其他连通块做贡献。

所以，连通块 $i$ 整体增加的贡献就是 $\sum\limits_{j=1,j\ne i}^{k}s_j$。

这个答案统计用线段树是好维护的。

由于作者脑残了，写的时候写了一个树剖，其实不用，略去即可。

那么，下面的问题就是快速统计出上面 $s_i$ 了。

发现非常简单，倒叙统计答案，然后逐个点删除即可。

这样开 $2$ 棵线段树就好了。

复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls p << 1
#define rs p << 1 | 1
using namespace std;
const int N = 2e5 + 5;
int n, u, v, fir[N], nxt[N << 1], son[N << 1], tot, fa[N], sz[N], top[N], dfn[N], idx, sum[N << 2], tag[N << 2];
int in[N], ou[N], ans[N], hs[N], sum2[N << 2];
struct node{
	int to, w;
}tmp;
vector<node>vec[N];
inline void add(int x, int y){
	nxt[++tot] = fir[x];
	fir[x] = tot;
	son[tot] = y;
}
inline void dfs(int x, int ff = 0){
	fa[x] = ff;
	sz[x] = 1;
	for(int i = fir[x]; i ; i = nxt[i]){
		if(son[i] == ff) continue ;
		dfs(son[i], x);
		sz[x] += sz[son[i]];
		if(sz[son[i]] > sz[hs[x]]){
			hs[x] = son[i];
		}
	}
}
inline void dfs2(int x, int tp){
	top[x] = tp;
	in[x] = ou[x] = dfn[x] = ++idx;
	if(!hs[x]) return ;
	dfs2(hs[x], tp);
	for(int i = fir[x]; i ; i = nxt[i]){
		if(son[i] == fa[x] || son[i] == hs[x]) continue ;
		dfs2(son[i], son[i]);
	}
	ou[x] = idx;
}
inline void build(int p, int l, int r){
	if(l == r){
		sum[p] = 1;
		return ;
	}
	int mid = l + r >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	sum[p] = sum[ls] + sum[rs];
}
inline void push_down(int p, int l, int r){
	int mid = l + r >> 1;
	sum2[ls] += (mid - l + 1) * tag[p];
	sum2[rs] += (r - mid) * tag[p];
	tag[ls] += tag[p];
	tag[rs] += tag[p];
	tag[p] = 0;
}
inline void modify(int p, int l, int r, int x, int y, int val){
	if(l == r){
		sum[p] += val;
		return ;
	}
	int mid = l + r >> 1;
	if(mid >= x) modify(ls, l, mid, x, y, val);
	if(mid < y) modify(rs, mid + 1, r, x, y, val);
	sum[p] = sum[ls] + sum[rs];
}
inline int query(int p, int l, int r, int x, int y){
	if(x <= l && r <= y) return sum[p];
	int mid = l + r >> 1, res = 0;
	if(mid >= x) res += query(ls, l, mid, x, y);
	if(mid < y) res += query(rs, mid + 1, r, x, y);
	return res;
}
inline void modify2(int p, int l, int r, int x, int y, int val){
	if(x <= l && r <= y){
		sum2[p] += (r - l + 1) * val;
		tag[p] += val;
		return ;
	}
	push_down(p, l, r);
	int mid = l + r >> 1;
	if(mid >= x) modify2(ls, l, mid, x, y, val);
	if(mid < y) modify2(rs, mid + 1, r, x, y, val);
	sum2[p] = sum2[ls] + sum2[rs];
}
inline int query2(int p, int l, int r, int x, int y){
	if(x <= l && r <= y) return sum2[p];
	push_down(p, l, r);
	int mid = l + r >> 1, res = 0;
	if(mid >= x) res += query2(ls, l, mid, x, y);
	if(mid < y) res += query2(rs, mid + 1, r, x, y);
	return res;
}
inline void getans(int x){
	int res = 0, tmp;
	modify(1, 1, n, dfn[x], dfn[x], -1);
	if(fa[x]) res += x - 1 - query(1, 1, n, in[x], ou[x]);
	for(int i = fir[x]; i ; i = nxt[i]){
		if(son[i] == fa[x]) continue ;
		res += query(1, 1, n, in[son[i]], ou[son[i]]);
	}
	if(fa[x]){
		tmp = res - (x - 1 - query(1, 1, n, in[x], ou[x]));
		modify2(1, 1, n, 1, n, tmp);
		modify2(1, 1, n, in[x], ou[x], -tmp);
	}
	for(int i = fir[x]; i ; i = nxt[i]){
		if(son[i] == fa[x]) continue ;
		tmp = res - query(1, 1, n, in[son[i]], ou[son[i]]);
		modify2(1, 1, n, in[son[i]], ou[son[i]], tmp);
	}
}
signed main(){
	scanf("%lld", &n);
	for(int i = 1; i < n; i++){
		scanf("%lld%lld", &u, &v);
		add(u, v), add(v, u);
	}
	dfs(1);
	dfs2(1, 1);
	build(1, 1, n);
//	printf("%d\n", query2(1, 1, n, dfn[2], dfn[2]));
	for(int i = n; i >= 1; i--){
		getans(i);
//		printf("%d %d\n", i, query2(1, 1, n, dfn[2], dfn[2]));
	}
	for(int i = 1; i <= n; i++){
		ans[i] = i - 1;
		ans[i] += query2(1, 1, n, dfn[i], dfn[i]);
	}
	for(int i = 1; i <= n; i++) printf("%lld ", ans[i]);
	puts("");
	return 0;
}
```

---

## 作者：int_R (赞：0)

[更好的阅读体验](https://www.cnblogs.com/int-R/p/17979029/AT_abc337_g)

[原题链接](https://www.luogu.com.cn/problem/AT_abc337_g)

换根 dp，先随便钦定一个根。

记 $a_x$ 为以 $x$ 为根的子树中小于 $x$ 的点的个数，$g_x$ 为以 $x$ 为根的子树中小于 $fa_x$ 的点的个数，也就是 $x$ 对 $f_{fa_x}$ 的贡献。

上述两个东西可以直接在按 DFS 序差分加树状数组求出。

```cpp
void dfs(int x,int fa=0)
{
    dfn[x]=++tot,pos[tot]=x,siz[x]=1;
    bit::change(x,1);
    for(int y:v[x])
    {
        if(y==fa) continue;
        //这里计算 y 对 x 的贡献
        g[y]-=a[x];a[x]-=bit::query(x-1);
        dfs(y,x),siz[x]+=siz[y];
        a[x]+=bit::query(x-1);g[y]+=a[x];
    }
    return ;
}
```

然后考虑对于一个点 $p$ 的答案，不在其到根的路径上的点 $x$ 此时对答案的贡献是 $a_x$；而对于在其到根路径上的点 $x$，$y$ 是子树中包含 $p$ 的 $x$ 的儿子，$x$ 的贡献应当是所有小于 $x$ 的数的个数减去以 $y$ 为根的子树中小于 $x$ 的个数即 $(x-1)-g_y$（对于 $p$ 本身来说贡献就是 $p-1$）。

所以可以先求出 $\sum a_i$，然后从根开始再 DFS 一遍，从 $x$ 往 $y$ 递归时更改 $x$ 的贡献即可。

```cpp
void dp(int x,int sum,int fa=0)
{
    ans[x]=sum-a[x]+(x-1);
    for(int y:v[x])
    {
        if(y==fa) continue;
        dp(y,sum-a[x]+(x-1)-g[y],x);
    }
    return ;
}
signed main()
{
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>n;
    for(int i=1,x,y;i<n;++i)
        cin>>x>>y,v[x].push_back(y),v[y].push_back(x);
    dfs(1);for(int i=1;i<=n;++i) sum+=a[i];
    dp(1,sum);for(int i=1;i<=n;++i) cout<<ans[i]<<' ';
    cout<<'\n';return 0;
}
```


---

## 作者：gdf_yhm (赞：0)

[abc337g](https://www.luogu.com.cn/problem/solution/AT_abc337_g)

### 思路

我想复杂了。比较直接粗暴。

固定 $w$，将树分为子树内外两部分，分别考虑子树内到子树外，子树外到子树内，两个儿子之间的贡献。

需要支持查询 $u$ 子树内比 $u$ 大的数的个数，做子树加。后半部分可以 dfn 序上线段树区间加，前面部分没想到从小到大加入 $w$，直接用权值线段树合并。复杂度 $O(n\log n)$。

不知道为什么线段树合并 $32$ 倍空间 RE 了，挂了两发。

### code

```cpp
int n,m;
int head[maxn],tot;
struct edgend{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
namespace sgt{
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
	int tree[maxn<<2],tag[maxn<<2];
	void push(int nd,int l,int r){
		tree[ls]+=(mid-l+1)*tag[nd],tag[ls]+=tag[nd];
		tree[rs]+=(r-mid)*tag[nd],tag[rs]+=tag[nd];
		tag[nd]=0;
	}
	void updata(int nd,int l,int r,int ql,int qr,int w){
		if(ql>qr)return ;
		if(l>=ql&&r<=qr){
			tree[nd]+=(r-l+1)*w;tag[nd]+=w;
			return ;
		}
		if(tag[nd])push(nd,l,r);
		if(ql<=mid)updata(ls,l,mid,ql,qr,w);
		if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
		tree[nd]=tree[ls]+tree[rs];
	}
	int query(int nd,int l,int r,int p){
		if(l==r)return tree[nd];
		if(tag[nd])push(nd,l,r);
		if(p<=mid)return query(ls,l,mid,p);
		else return query(rs,mid+1,r,p);
	}
#undef mid
#undef ls
#undef rs
}
int dfn[maxn],idx,rnk[maxn],siz[maxn];
void dfs(int u,int fa){
	rnk[dfn[u]=++idx]=u;siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa)continue;
		dfs(v,u);siz[u]+=siz[v];
	}
}
namespace tr{
#define mid (l+r>>1)
#define ls lc[nd]
#define rs rc[nd]
	int rt[maxn],idx;
	int tree[maxn<<6],lc[maxn<<6],rc[maxn<<6];
	void updata(int &nd,int l,int r,int p,int w){
		if(!nd)nd=++idx;
		if(l==r){tree[nd]+=w;return ;}
		if(p<=mid)updata(ls,l,mid,p,w);
		else updata(rs,mid+1,r,p,w);
		tree[nd]=tree[ls]+tree[rs];
	}
	int merge(int u,int v,int l,int r){
		if(!u||!v)return u|v;
		int nd=++idx;
		if(l==r){tree[nd]=tree[u]+tree[v];return nd;}
		ls=merge(lc[u],lc[v],l,mid);
		rs=merge(rc[u],rc[v],mid+1,r);
		tree[nd]=tree[ls]+tree[rs];
		return nd;
	}
	int query(int nd,int l,int r,int ql,int qr){
//		if(!nd)return 0;
		if(ql>qr)return 0;
		if(l>=ql&&r<=qr)return tree[nd];
		if(qr<=mid)return query(ls,l,mid,ql,qr);
		if(ql>mid)return query(rs,mid+1,r,ql,qr);
		return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
	}
}
void dfs2(int u,int fa){
	tr::updata(tr::rt[u],1,n,u,1);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa)continue;
		dfs2(v,u);
		int num=tr::query(tr::rt[v],1,n,1,u-1);
		sgt::updata(1,1,n,dfn[u]+1,dfn[v]-1,num);sgt::updata(1,1,n,dfn[v]+siz[v],dfn[u]+siz[u]-1,num);
		tr::rt[u]=tr::merge(tr::rt[u],tr::rt[v],1,n);
	}
	int num=tr::query(tr::rt[u],1,n,1,u-1);
//	cout<<u<<" "<<num<<" ";
	sgt::updata(1,1,n,1,dfn[u],num);sgt::updata(1,1,n,dfn[u]+siz[u],n,num);
	num=u-1-tr::query(tr::rt[u],1,n,1,u-1);
//	cout<<num<<"\n";
	sgt::updata(1,1,n,dfn[u],dfn[u]+siz[u]-1,num);
	
}
int ans[maxn];
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	dfs(1,0);
	dfs2(1,0);
	for(int i=1;i<=n;i++)ans[rnk[i]]=sgt::query(1,1,n,i);
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
}
```


---

