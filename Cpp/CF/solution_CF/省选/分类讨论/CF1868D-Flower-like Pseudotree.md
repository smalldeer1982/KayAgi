# Flower-like Pseudotree

## 题目描述

伪树是一种连通图，恰好包含一个环且没有自环。注意，伪树可以包含重边。可以证明，一个有 $n$ 个顶点的伪树总是包含 $n$ 条边。

在伪树中删除所有环上的边后，会形成一片森林 $^\dagger$。可以证明，森林中的每棵树都恰好包含一个在删除前属于环的顶点。如果当以环上的顶点作为根时，森林中所有树的深度 $^\ddagger$ 都相同，则称原伪树为“花状”。

你的朋友 sszcdjr 有一个包含 $n$ 个顶点和 $n$ 条边的花状伪树。但他忘记了伪树中的所有边。幸运的是，他还记得每个顶点的度数。具体来说，第 $i$ 个顶点的度数为 $d_i$。

你需要帮助 sszcdjr 构造一个可能的花状伪树，使得第 $i$ 个顶点的度数恰好为 $d_i$，或者告诉他这是不可能的。

$^\dagger$ 森林是指所有连通分量都是树的图。一个无环且无自环的连通图称为树。

$^\ddagger$ 一棵有根树的深度是指从根到该树中最远顶点的距离。

## 说明/提示

在第一个测试用例中，唯一可能的花状伪树为：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1868D/cef326e6c38f8a7ed31108a0dd8a82ca77066a75.png)

在伪树中删除所有环上的边后，每棵树的深度为 $0$。

在第二个测试用例中，可以证明不存在这样的花状伪树。

在第三个测试用例中，可能的花状伪树之一为：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1868D/48e01c1853662d07718526eb1ce31700d09724f0.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
3
2 2 2
4
1 2 3 4
7
4 3 3 1 1 1 1
6
1 1 2 2 3 3
10
1 1 5 2 1 1 1 1 1 6
9
1 1 3 1 1 4 1 1 5```

### 输出

```
Yes
1 2
2 3
3 1
No
Yes
1 2
2 3
3 1
1 4
1 5
2 6
3 7
Yes
5 6
6 5
1 3
2 4
3 5
4 6
No
Yes
3 6
6 9
9 3
1 3
2 6
4 6
5 9
7 9
8 9```

# 题解

## 作者：Rainbow_qwq (赞：11)

虽然是垃圾分类讨论题，但我写了个不那么需要分类讨论的做法。

首先进行一些平凡的讨论：

- 如果度数之和 $\ne 2n$ 则为 `No`（注意度数之和要开 `long long` /tuu）
- 如果所有点度数都为 $2$，则可以连成一个大环。
- 如果度数只有为 $1$ 或 $>2$，则把所有度数 $>2$ 的点连成一个环，然后挂上所有叶子。
- 否则，度数为 $2$ 的点一定不能出现在环上。此时如果度数 $>2$ 的点只有 $1$ 个则为 `No`。

然后尝试钦定环上只有 $2$ 个点，进行构造。

先忽略掉所有叶子，最后的时候再添加，容易发现这样最后每个子树的深度都 $+1$，不影响结果。

把度数 $\ge 2$ 的点按照度数大小从大到小排序，钦定环上的两个点为度数最大的两个点，设为 $x,y$。

然后依次把度数 $\ge 2$ 的点挂上去，形成两条链，并且交替地在 $x,y$ 的两条链上挂点（每挂一个点都挂在链上最深的点下面，增加一条链的深度）。最后在所有空的地方挂上叶子。

这样做完两颗树的长度一定差为 $0$ 或 $1$。

如果差为 $0$ 就结束了。

如果差为 $1$，考虑取出深的链上最深的度数 $\ge 2$ 的点，这个点需要调整位置。

考虑取出整个基环树上深度最小的叶子，如果这个叶子的深度比这个点小，则可以 swap 这两个点的父亲，然后调整成功。

如果这样调整不成功（叶子深度 $\ge$ 这个点的深度），发现是以下几种 case：

- $\{3,3,2,2,2,2,2\}$ （奇数个 $2$）
- $\{3,3,3,2,2\}$
- $\{3,3,3,3,2\}$

手玩发现这几种情况在环长不为 $2$ 的时候也不可行，于是就做完了。

```cpp
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i>=(b);--i)

#define fi first
#define se second
#define pb push_back
#define mkp make_pair
typedef pair<int,int>pii;
typedef vector<int>vi;

#define maxn 1000005
#define inf 0x3f3f3f3f

int n,d[maxn],vis[maxn],a[maxn];

int fa[maxn],dep[maxn];
vi vec[maxn],e[maxn];

void work()
{
	n=read();
	For(i,1,n)d[i]=read(),vis[i]=0;
	
	long long sumd=0;
	For(i,1,n)sumd+=d[i];
	if(sumd!=n*2){
		puts("No");
		return;
	}
	bool all2=1;
	For(i,1,n)if(d[i]!=2)all2=0;
	if(all2){
		puts("Yes");
		For(i,1,n-1)cout<<i<<' '<<i+1<<"\n";
		cout<<n<<" "<<1<<"\n";
		return;
	}
	bool no2=1;
	For(i,1,n)
		if(d[i]==2) no2=0;
	if(no2){
		vi o;
		For(i,1,n) if(d[i]>1) o.pb(i),vis[i]=1;
		int m=o.size();
		if(m==1){
			puts("No");
			return;
		}
		puts("Yes");
		For(i,0,m-1){
			int u=o[i],v=o[(i+1)%m];
			cout<<u<<" "<<v<<"\n";
		}
		For(i,0,m-1) d[o[i]]-=2;
		For(i,1,n){
			if(!vis[i]){
				while(o.size() && d[o.back()]==0) o.pop_back();
				d[o.back()]--;
				cout<<i<<" "<<o.back()<<"\n";
			}
		}
		return;
	}
	// 2 can't be on ring
	
	int x=-1,y=-1;
	For(i,1,n){
		if(d[i]>2){
			if(x==-1 || d[i]>d[x]) y=x,x=i;
			else if(y==-1 || d[i]>d[y]) y=i;
		}
	}
	if(x==-1 || y==-1){
		puts("No");
		return;
	}
	
	vis[x]=vis[y]=1;
	cerr<<"x,y "<<x<<" "<<y<<"\n";
	
	if(d[x]==3 && d[y]==3){
		int cnt3=0;
		For(i,1,n) cnt3+=(d[i]>2);
		if(cnt3==2){
			int cnt2=0;
			For(i,1,n) cnt2+=(d[i]==2);
			if(cnt2%2){
				puts("No");
				return;
			}
		}
	}
	
	For(i,1,n) a[i]=d[i]-1;
	a[x]--,a[y]--;
	
	For(i,1,n)fa[i]=0,vec[i].clear();
	For(i,1,n) if(i!=x && i!=y) vec[d[i]].pb(i);
	int dx=0,dy=0;
	int nx=x,ny=y;
	Rep(i,n,2)
		if(vec[i].size()){
			for(int u:vec[i]){
				if(dx<=dy){
					fa[u]=nx,--a[nx],nx=u;
					++dx;
				}else{
					fa[u]=ny,--a[ny],ny=u;
					++dy;
				}
			}
		}
	assert(vec[1].size()>=2);
	
//	For(i,1,n) cout<<a[i]<<" "; cout<<" a\n";
	
	vi go;
	For(i,1,n) if(a[i]>=0) {
		For(j,1,a[i]) go.pb(i);
	}
	
	For(i,1,n)
		if(d[i]==1) {
			assert(go.size());
			int u=go.back(); go.pop_back();
			fa[i]=u;
		}
	assert(!go.size());
	
	For(i,1,n) e[i].clear();
	For(i,1,n) e[fa[i]].pb(i);
	
	function<void(int)> dfs = [&](int u){
		for(int v:e[u]) dep[v]=dep[u]+1,dfs(v);
	};
	dep[x]=dep[y]=0;
	dfs(x);
	dfs(y);
	
	if(dx!=dy){
		int leaf=0;
		For(i,1,n)
			if(d[i]==1){
				if(leaf==0 || dep[i]<dep[leaf]) leaf=i;
			}
		if(!leaf || dep[leaf]>=dep[nx]){
			puts("No");
			return;
		}
		swap(fa[leaf],fa[nx]);
	}
	
	puts("Yes");
	cout<<x<<" "<<y<<"\n";
	cout<<x<<" "<<y<<"\n";
	For(i,1,n)
		if(i!=x && i!=y) cout<<fa[i]<<" "<<i<<"\n";
}
```

---

## 作者：Alex_Wei (赞：6)

### [CF1868D Flower-like Pseudotree](https://www.luogu.com.cn/problem/CF1868D)

一个不需要在代码里分类讨论且细节很少的做法（可能需要在草稿纸上分类讨论）。

首先特判掉两种平凡情况：

- $\sum d_i \neq 2n$，无解。
- $\forall i, d_i = 2$，成环。

除此以外，存在至少一个环上的点有至少一棵子树，导致环上的点的度数必须大于 $2$。因此如果 $d_i > 2$ 的点只有一个，那也寄了。

不妨先将所有叶子去掉，也就是删去度数为 $1$ 的点，得到的新树同样需要满足条件。反过来，如果新树满足条件，那么将叶子加上去同样满足条件。

这样，问题转化为了：构造一棵基环树，使得每个点的度数不超过它的限制，且所有叶子不出现。

如果 $d_i > 1$ 的点数是偶数，那就太好构造了：任选两个 $d_i > 2$ 的点作为环上的点，剩下来的点以链的形式分别接到这两个点上即可。

尝试将这种做法套到一般情况：当数量是奇数时，先丢掉一个点。如果构造出来的新树有一个非叶子没有达到度数上限，就可以将丢掉的点挂在这个非叶子上，不影响合法性。

为了避免没有达到度数上限的点是叶子的情况，根据 “环上的点的度数减去 $3$，新树非叶子的度数减去 $2$”，需要给环安排度数最大的两个点，给叶子安排度数最小的两个点。如果这种情况下依然没有非叶子未达到度数上限，那无论怎么调整也无法使得非叶子未达到度数上限了。

考虑上述做法在哪些情况下得不到解：

- 新树深度为 $0$：$d_i > 1$ 的点数为 $3$。又因为 $d_i > 2$ 的点数不小于 $2$，所以 $d_i > 1$ 的点集只有可能是（用 $3$ 表示大于 $2$ 的度数）：
  - $\{3, 3, 2\}$：思考后发现这种情况无解。
  - $\{3, 3, 3\}$：构造这三个点的三元环。
- 新树深度为 $1$：$d_i > 1$ 的点数为 $5$。如果此时有 $d_i > 3$，那么环上的点就未达到度数限制，所以 $d_i \leq 3$。
  - $\{3, 3, 2, 2, 2\}$：思考后发现这种情况无解。
  - $\{3, 3, 3, 2, 2\}$：思考后发现这种情况无解。
  - $\{3, 3, 3, 3, 2\}$：思考后发现这种情况无解。
  - $\{3, 3, 3, 3, 3\}$：构造这五个点的五元环。
- 新树深度大于 $1$：类似有 $d_i\leq 3$。只要有至少三个 $d_i > 2$ 的点，那么其中两个作为环点，另一个作为非叶子即可。因此恰有两个 $d_i = 3$，其它都是 $d_i = 2$，且 $d_i = 2$ 的点数为奇数。思考后发现这种情况无解。

综上，我们只需要再特判掉不存在 $d_i = 2$ 时将 $d_i > 2$ 的点连成大环，就可以用上述做法求解。具体求解方式是容易的，详见代码。

时间复杂度 $\mathcal{O}(n)$ 或 $\mathcal{O}(n\log n)$（排序）。

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> sma;
vector<pair<int, int>> mid, lar, ans;
void print() {
  cout << "YES\n";
  for(auto it : ans) cout << it.first << " " << it.second << "\n";
  return;
}
void add(int u, int v) {
  ans.push_back({u, v});
}
void add2(auto &u, auto &v) {
  ans.push_back({u.first, v.first});
  u.second--, v.second--;
}

int n;
void solve() {
  sma.clear(), mid.clear(), lar.clear(), ans.clear();
  cin >> n;
  long long s = 0;
  for(int i = 1, d; i <= n; i++) {
    cin >> d, s += d;
    if(d == 1) sma.push_back(i);
    if(d == 2) mid.push_back({i, 2});
    if(d > 2) lar.push_back({i, d});
  }
  if(s != 2 * n) return cout << "NO\n", void();
  if(lar.empty()) {
    for(int i = 1; i <= n; i++) add(i, i % n + 1);
    return print();
  }
  if(lar.size() == 1) return cout << "NO\n", void();
  auto fill = [&](auto x) {
    while(x.second--) {
      add(x.first, sma.back());
      sma.pop_back();
    }
  };
  if(mid.empty()) {
    for(int i = 0; i < lar.size(); i++) {
      add(lar[i].first, lar[(i + 1) % lar.size()].first);
      lar[i].second -= 2, fill(lar[i]);
    }
    return print();
  }
  lar.insert(lar.end(), mid.begin(), mid.end());
  sort(lar.begin(), lar.end(), [&](const auto &x, const auto &y) {
    return x.second < y.second;
  });
  auto u = lar.back(); lar.pop_back();
  auto v = lar.back(); lar.pop_back();
  add2(u, v), add2(v, u);
  while(!lar.empty()) {
    auto get = [&]() {
      auto res = lar.back(); lar.pop_back();
      return res;
    };
    auto nu = get();
    if(lar.empty()) return cout << "NO\n", void();
    if((lar.size() & 1 ^ 1) && u.second > 1) add2(u, nu), fill(nu), nu = get();
    add2(u, nu), fill(u), u = nu;
    auto nv = get();
    if((lar.size() & 1) && v.second > 1) add2(v, nv), fill(nv), nv = get();
    add2(v, nv), fill(v), v = nv;
  }
  fill(u), fill(v), print();
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  cin >> T;
  while(T--) solve();
  return 0;
}
```

---

## 作者：DeaphetS (赞：5)

题目链接：[D - Flower-like Pseudotree](https://codeforces.com/contest/1868/problem/D)

题目大意：给定度数数组 ${d_n}$，要求构造一个 $n$ 个点 $n$ 条边的连通图（也就是基环树），允许有重边，但不能有自环。需要满足第 $i$ 个点的度数恰好为 $d_i$，并且将环上的边全部删去后，剩下的每棵树的高度（以原先在环上的点为根）相同。

首先考虑几个特殊情况：

- 当 $\sum d_i\neq 2n$ 时，无解
- 若 $\forall i,d_i=2$，则直接输出一个大小为 $n$ 的环

将构造分两步完成，先将非叶子结点全部安排好以完成深度限制，然后再把所有叶子结点连到这些点上以符合度数限制，其中后者做法平凡。基于这一点考虑，如果不存在度数为 $2$ 的点，那么直接把所有非叶子结点连成一个环就能完成第一步构造。剩下的情况都是必然存在一个度数为 $2$ 的点的。

接下来，考虑在环上延伸出点以完成构造。这时发现由于在环上的点度数必须 $\gt 2$，而环的大小至少为 $2$。所以若度数 $>2$ 的点数为 $1$ 则无解。显然，若不在环上的非叶子结点个数是环大小的倍数，那么直接在环上挂几条长度相等的链即可。于是对环长为 $2$ 的情况进行讨论。

若钦定了环长为 $2$，那么只需要判断剩余的非叶子结点个数是否为偶数，若是则直接可以完成构造。若不是，那我们先尽量让两边的链长平均，这样有一边会多出来一个点 $x$ ，考虑将这个多出来的点移到某个深度比 $x$ 小的点 $y$ 后面，让他作为 $y$ 的儿子。

此时，$dep(x)=dep(y)+1$，于是只需保证在删去$x$ 后，$y$ 不是当前基环树上的叶子结点即可。那么可以在一开始放链的时候，优先让 $d_i$ 大的点先连（深度更小），这样 $x$ 在找爹的时候，直接找深度最浅的有空位的父亲即可，这样做一定是较优的。

接下来说明用上述方法无法完成构造时，一定无解，不感兴趣可跳过。

> 先考虑无法构造时，是什么样的一种情况。
>
> 此时一定是 $x$ 在找爹时，找不到一个比当前爹深度更浅的，且有空位的新爹了。
>
> 由于我们是优先连 $d_i$ 更大的点，所以此时所有的点一定都没有空位，那么显然除了和当前 $x$ 的父亲深度一样的两个点，其它点的 $d_i$ 一定为 $2$，而环上的两个点 $d_i=3$。
>
> 当 $x$ 的父亲深度 $\gt 1$（环上的点深度看做 $0$）时，深度为 $1$ 的点没有空位，那么其 $d_i$ 一定为 $2$。对应非叶子结点的 $d_i$ 可重集的情况就是 $\{3,3,2,2,2,\dots,2,2\}$，其中 $2$ 的个数为奇数。那么显然此时只能有两个点在环上，因为有叶子时度数为 $2$ 的点不能在环上。于是无法通过调整环长来求解，对应情况无解。
>
> 当 $x$ 的父亲深度为 $1$ 时，此时是深度为 $0$ 的点没有空位，对应情况则为 $\{3,3,2\ or\ 3,2\ or\ 3,2\}$。此时虽然可以调整环长，但是调整环长后剩下的非叶子结点不足以连出一条长度为 $1$ 的链，所以也无解。
>
> 当 $x$ 的父亲深度为 $0$ 时，那么此时情况为 $\{G_1,G_2,2\}$，$G_i$ 表示某个 $\gt 2$ 的数，与 $x$ 的父亲深度 $\gt 1$ 的情况一样，也是无解的。

那么完成几个特殊情况的判断后，贪心连链即可。由于需要找新爹的点最多只会有一个，所以直接按度数从大到小找到一个满足条件的点就好。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000010
#define GG {printf("No\n");return;}
int T,n,fa[N],dep[N];
struct rua
{
	int deg,id;
	void read(int i){scanf("%d",&deg),id=i;}
	bool operator <(const rua &t)const{return deg>t.deg;}
}a[N];
void init()
{	
	int d2=0,d1=0;
	long long sum=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		dep[i]=fa[i]=0;
		a[i].read(i);
		if(a[i].deg==1)d1++;
		if(a[i].deg==2)d2++;
		sum+=a[i].deg;
	}
	if(sum!=2*n)GG
	if(n-d1-d2==1)GG
	if(d2==n){
		printf("Yes\n");
		for(int i=1;i<=n;i++)
			printf("%d %d\n",i,i%n+1);
		return;
	}
	sort(a+1,a+n+1);
	if(d2==0){
		printf("Yes\n");
		vector<int>d;
		int id=1;
		while(id<=n && a[id].deg>1)id++;id--;
		for(int i=1;i<=id;i++){
			printf("%d %d\n",a[i].id,a[i%id+1].id);
			for(int j=1;j<=a[i].deg-2;j++)d.push_back(a[i].id);
		}
		for(int i=id+1;i<=n;i++)
			printf("%d %d\n",a[i].id,d[i-id-1]);
		return;
	}
	int lst=0;
	a[1].deg-=2,a[2].deg-=2;
	for(int i=3;a[i].deg>=2;i++){
		a[i].deg--;
		fa[a[i].id]=a[i-2].id;
		dep[a[i].id]=dep[fa[a[i].id]]+1;
		a[i-2].deg--;
		lst=i;
	}
	if(lst&1){
		int f=0;
		for(int i=1;i<lst;i++)
			if(a[i].deg && dep[a[i].id]<dep[fa[a[lst].id]]){
				f=1;
				a[lst-2].deg++;
				fa[a[lst].id]=a[i].id;
				a[i].deg--;
				break;
			}
		if(f==0)GG
	}
	vector<int>d;
	for(int i=1;i<=lst;i++)
		for(int j=1;j<=a[i].deg;j++)
			d.push_back(a[i].id);
	for(int i=lst+1;i<=n;i++)
		fa[a[i].id]=d[i-lst-1];
	printf("Yes\n");
	for(int i=1;i<=2;i++)
		printf("%d %d\n",a[i].id,a[i%2+1].id);
	for(int i=3;i<=n;i++)
		printf("%d %d\n",a[i].id,fa[a[i].id]);
}
int main()
{
	scanf("%d",&T);
	while(T--)init();
}
```

---

## 作者：_Diu_ (赞：2)

赛时差点做出来好伤心。

---

题意：给出每个点度数，要求构造一棵基环树满足把环删掉之后每棵树深度相同。

---

首先判断 $\sum d_i=2n$，判掉整体是一个环的情况。

有一个结论：事实上大部分的环点数 $\ge 3$ 的基环树都可以进一步构造出环点数为 $2$ 的基环树。

但是发现样例 `4 3 3 1 1 1 1` 就不行。

我们尝试找到一个能够从环点数为 $k(k\ge 3)$ 的基环树转换成环点数小于 $k$ 的基环树的条件与方法。

- 如果环大小为 $>2$ 的偶数：

容易做到环大小除以二。

- 如果存在一个非环点有两个高度不相同的儿子：

这种情况比较平凡：

![](https://cdn.luogu.com.cn/upload/image_hosting/aeu3s3kc.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

- 如果存在一个非环电有两个高度相同的儿子并且环大小为奇数：

这种情况稍微复杂一点：

![](https://cdn.luogu.com.cn/upload/image_hosting/g42js404.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这样综合起来只有一种情况无法通过上面的情况转化成环大小为 $2$ 的情况：

环大小为奇数并且**不存在一个非环点存在分叉**。

奇数的条件并没有什么用，考虑不存在分叉的图长什么样：

![](https://cdn.luogu.com.cn/upload/image_hosting/ihsq7tpb.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

~~也就是海胆图。~~

这种情况所有度数 $\ge3$ 的点都是环上点，假设有 $x$ 个环上点 $y$ 个叶子，有 $m$ 个二度点，枚举每棵树内最深的链中二度点个数 $k$，如果 $xk\le m\le yk$ 即可构造出相应的基环树。

---

现在只需要考虑环大小为 $2$ 的情况。

把叶子删掉实际上要求剩下的点度数 $\le d_i$ 并且两边高度相同。

- 如果 $d_i\ge 2$ 的点数为偶数，那么把所有点排成两条链即可。

- 否则先把除了 $d_i$ 最小的点之外的点排成两条链，然后剩余一个点随便找个位置插入。

如果插入不了，只有一种情况：`3 3 2 2 ... 2 1 1`（奇数个 $2$），这种情况确实无解。

复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+10;
int T,n,d[N];
struct node{
	int x,i;
	bool operator<(const node h)const{return x>h.x;}
}a[N];
bool solve1(){
	bool flg=1;
	for(int i=1;i<=n;i++)flg&=d[i]==2;
	if(flg){
		puts("Yes");
		for(int i=1;i<n;i++)printf("%d %d\n",i,i+1);
		printf("%d %d\n",1,n);
		return 1;
	}
	return 0;
}
bool solve2(){
	int cnt=0,res=0;
	for(int i=1;i<=n;i++)cnt+=d[i],res+=d[i]==1;
	if(cnt!=2*n||res<=1){puts("No");return 1;}
	return 0;
}
bool solve3(){
	int cnt=0;
	for(int i=1;i<=n;i++)cnt+=d[i]==1;
	int res=0,rs=0,fr=0;
	for(int i=1;i<=n;i++)if(d[i]>2)res+=d[i]-2,++rs;
	for(int i=1;i<=n;i++)fr+=d[i]==2;
	if(res!=cnt||rs==1)return 0;
	int x=rs,y=res;
	for(int k=0;k*x<=n;k++){
		if(k*x<=fr&&fr<=k*y){
			puts("Yes");
			vector<int> g;g.clear();
			for(int i=1;i<=rs;i++)printf("%d %d\n",a[i].i,a[i%rs+1].i);
			for(int i=1;i<=rs;i++)g.push_back(a[i].i);
			for(int i=1;i<=rs;i++){
				int tmp=a[i].x-3;
				for(;tmp--;)g.push_back(a[i].i);
			}
			int p=rs+1,q=n-cnt;
			for(int x:g){
				int lst=x;
				for(int j=1;j<=k&&p<=n&&a[p].x==2;j++,p++){
					printf("%d %d\n",lst,a[p].i),lst=a[p].i;
				}
				++q;printf("%d %d\n",lst,a[q].i);
			}
			return 1;
		}
	}
	return 0;
}
vector<int> a1,a2;
bool solve4(){
	int cnt=0;
	for(int i=1;i<=n;i++)if(d[i]>1)++cnt;
	if(cnt==1)return 0;
	a1.clear(),a2.clear();
	a1.push_back(a[1].i),a2.push_back(a[2].i);
	a1.push_back(a[2].i),a2.push_back(a[1].i);
	if(a[2].x<=2)return 0;
	a[1].x-=2,a[2].x-=2;
	for(int i=3;i<=cnt/2*2;i++){
		a[i].x--,a[i-2].x--;
		a1.push_back(a[i-2].i),a2.push_back(a[i].i);
	}
	if(cnt&1){
		bool flg=0;
		for(int i=1;i<cnt-2;i++)if(a[i].x){
			a1.push_back(a[i].i),a2.push_back(a[cnt].i);
			--a[i].x,--a[cnt].x;
			flg=1;
			break;
		}
		if(!flg)return 0;
	}
	puts("Yes");
	for(int i=0;i<a1.size();i++)printf("%d %d\n",a1[i],a2[i]);
	int p=cnt+1;
	for(int i=1;i<=cnt;i++){
		while(a[i].x)--a[i].x,printf("%d %d\n",a[i].i,a[p].i),++p;
	}
	return 1;
}
signed main(){
	scanf("%d",&T);
	for(;T--;){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&d[i]);
		for(int i=1;i<=n;i++)a[i]={d[i],i};
		sort(a+1,a+n+1);
		if(solve1())continue;
		if(solve2())continue;
		if(solve3())continue;
		if(solve4())continue;
		puts("No");
	}
}
```

---

