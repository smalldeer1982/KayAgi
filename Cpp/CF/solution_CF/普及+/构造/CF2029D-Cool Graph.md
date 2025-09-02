# Cool Graph

## 题目描述

You are given an undirected graph with $ n $ vertices and $ m $ edges.

You can perform the following operation at most $ 2\cdot \max(n,m) $ times:

- Choose three distinct vertices $ a $ , $ b $ , and $ c $ , then for each of the edges $ (a,b) $ , $ (b,c) $ , and $ (c,a) $ , do the following: 
  - If the edge does not exist, add it. On the contrary, if it exists, remove it.

A graph is called cool if and only if one of the following holds:

- The graph has no edges, or
- The graph is a tree.

You have to make the graph cool by performing the above operations. Note that you can use at most $ 2\cdot \max(n,m) $ operations.

It can be shown that there always exists at least one solution.

## 说明/提示

In the first test case, the graph is already cool because there are no edges.

In the second test case, after performing the only operation, the graph becomes a tree, so it is cool.

In the third test case, the graph is already cool because it is a tree.

In the fourth test case, after performing the only operation, the graph has no edges, so it is cool.

In the fifth test case:

 OperationGraph before the operationGraph after the operation $ 1 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/b0f7ac35f24bdd1ef25527e8445c75c07c81b1cd.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/967d0caf549d17edc01f85e8fd3b92d4a29c78a4.png) $ 2 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/8fc9b337d57d63328a0f768cb6979898a6acb589.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/e76a67a3a1dfd30fecae063029760f2fec760cd4.png) $ 3 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/cd4bbe994192de9db9336eff41b4aa05bb7c27af.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/278495e89dce856c8d1c4a31851cd95fdb2f1cd3.png)Note that after the first operation, the graph has already become cool, and there are two extra operations. As the graph is still cool after the two extra operations, this is a valid answer.

## 样例 #1

### 输入

```
5
3 0
3 1
1 2
3 2
1 2
2 3
3 3
1 2
2 3
3 1
6 6
1 2
1 6
4 5
3 4
4 6
3 6```

### 输出

```
0
1
1 2 3
0
1
1 2 3
3
1 3 6
2 4 5
3 4 6```

# 题解

## 作者：Autumn_Rain (赞：9)

如果这个图本身就符合要求，直接输出 $0$。

找到所有度不小于 $2$ 的点，选和它有另外两个相邻的点进行操作（这会使边的数量刚好减 $1$），直到没有这样的点，那么整张图变成了一堆单点和边，这个操作最多进行 $m$ 次。

![](https://cdn.luogu.com.cn/upload/image_hosting/4s9aozrc.png)

图变成了下面那样的森林。

![](https://cdn.luogu.com.cn/upload/image_hosting/avu2skdk.png)

然后我们找到所有大小为 $2$ 的联通块，也就是下面这个东西。姑且命名为 $X$。

![](https://cdn.luogu.com.cn/upload/image_hosting/2eqkj6hu.png)

如果有多于一个的 $X$，那么我们选其中两个，从中随便选出三个点进行操作，变成一颗树。

![](https://cdn.luogu.com.cn/upload/image_hosting/odo7qpcq.png)

若还有剩下的 $X$，我们就选择已经生成树的树根，再把 $X$ 的两个点都选上，使其合并到树中，最后只剩下一个菊花图和一群单点。然后我们选树根，树上与根相邻的一点，和一个单点进行操作。不断重复直到没有单点，即可生成一棵树。

![](https://cdn.luogu.com.cn/upload/image_hosting/buaqso20.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/4ev4xtfv.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/aoyweow3.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/7vyt8gkx.png)

以此类推，操作数不超过 $n-1$（因为“已经生成的树”中至少有一个点，剩下的点每个被操作一次，次数不超过总点数）。令总操作数为 $S$，则存在如下关系符合题意。

$$ S \le m-1+n-1=m+n-2 \le 2 \times \max(n,m)$$

---

## 作者：Enoch006 (赞：3)

对于这种构造题，我们该怎么做呢？

题意要求把原图变成空图或者树，于是思考方向就有两个：

1. 把原图变成空图。手膜后发现对于一些图，是不可能的。
2. 把原图变成一棵树。这时候也有两个思路：
- 由于树不需要太多边，因此可以考虑先尽量减少边的数量。

  这就是[官方题解](https://codeforces.com/blog/entry/133516)的思路。
- 另一种就考虑构建特殊树，我们可以试着构建菊花图。
 
  当原图中的一条边所连的两个端点 $(x,y)$ 都不是一号节点时，我们可以对三元组 $(1,x,y)$ 进行操作，这时，边 $(x,y)$ 就被我们清除了。

  通过这样的操作，原图会变成以一号节点为中心的菊花图以及一些空点。我们想要把空点接到菊花图上去，只需要找一条原有的边然后进行如图所示的操作即可：

![](https://cdn.luogu.com.cn/upload/image_hosting/u5n05cws.png)

  因此总操作数最大为 $n+m\le 2\times\max(n,m)$。

  最后记得在第一轮操作后判一下图是不是变成了空图哦。


代码：
  
```cpp
#include <bits/stdc++.h>
#define int long long
#define maxm 500005
#define maxn 1005
#define inf 0x3f3f3f3f3f3f
using namespace std;
int T,n,m,cnt;
int a[maxm],v[maxm];
set<int>e[maxm];
struct node{
    int x,y,z;
}ans[maxm];
int X,Y;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;cnt=0;
        for(int i=1;i<=n;i++)e[i].clear(),v[i]=0;
        for(int i=1;i<=m;i++){
            int x,y;cin>>x>>y;
            e[x].insert(y);e[y].insert(x);
        }
        for(int i=2;i<=n;i++){
            while(e[i].size()){
                int x=*e[i].rbegin();
                if(x==1)break;
                e[i].erase(x);e[x].erase(i);
                if(e[1].count(i))e[1].erase(i),e[i].erase(1);
                else e[1].insert(i),e[i].insert(1);
                if(e[1].count(x))e[1].erase(x),e[x].erase(1);
                else e[1].insert(x),e[x].insert(1);
                ans[++cnt]=(node){1,i,x};
            }
        }
        if(e[1].size()){
            int X=1,Y=*e[1].begin();
            for(int i=2;i<=n;i++){
                if(e[i].size())continue;
                ans[++cnt]=(node){X,Y,i};
                X=i;
            }
        }
        cout<<cnt<<"\n";
        for(int i=1;i<=cnt;i++)
            cout<<ans[i].x<<" "<<ans[i].y<<" "<<ans[i].z<<"\n";
    }
    return 0;
}
```

---

## 作者：Exp10re (赞：2)

好题。

## 解题思路

遇到这一类题目先考虑简化状态。

注意到将一个任意图变为空图较为复杂，考虑将其变为一棵树，而且这棵树最好是具有特殊性质的树。

钦定 $1$ 为根，我们不难发现用不大于 $m$ 次操作将其变为一个类菊花图（每个非 $1$ 的点要么独立，要么与 $1$ 之间存在一条边，即非 $1$ 的点两两之间无边）是简单的，构造如下：

- 在读入一条边 $(u,v)$ 时，若该条边的一个端点为 $1$，则不进行任意操作。
- 否则，进行一次操作 $(1,u,v)$，这一定会删掉这一条边并且剩余被修改的两条边的一个端点是 $1$。

可以发现这些操作完毕后非 $1$ 的点两两之间无边，操作次数不大于 $m$。

接下来，若该图为一个空图，则其符合条件，否则一定存在一个点 $p$ 满足 $p$ 与 $1$ 在一个连通块内且边 $(1,p)$ 一定存在。

此时该图必定是一个以 $1$ 为根的菊花图加上若干个孤立点，考虑将其变成一棵树。注意到若我们选择一个点 $x$ 满足边 $(1,x)$ 存在并选择一个孤立点 $y$，执行操作 $(1,x,y)$ 就一定能将 $y$ 与 $1$ 以及 $x$ 合并进一个连通块，并且该连通块仍然是一棵树。

故我们考虑以下做法，执行以下步骤直到图是一棵树：

- 找到一个点 $p$ 满足边 $(p,1)$ 存在。
- 找到另一个孤立点 $q$。
- 执行操作 $(1,p,q)$。

根据上面的结论正确性显然，操作次数不大于 $n-2$，但是时间复杂度是 $O(n^2)$ 的，考虑优化。

- 第一步的寻找 $p$ 可以从先前连的边找到，具体的，每次操作完毕后使得 $p\leftarrow q$，因为此时 $(1,p)$ 断开，$(1,q)$ 相连。
- 考虑遍历所有点来去掉每次寻找孤立点的开销。

如此优化完毕。

时间复杂度 $O(n+m)$，操作次数上界 $n+m-2\leq 2\max(n,m)$，可以通过。

---

## 作者：bsdsdb (赞：1)

题意：给定一个简单无向图，你可以进行至多 $2\max(n,m)$ 次如下操作：「选择三个点 $i,j,k$，令 $E\gets E\oplus\{(i,j),(j,k),(k,i)\}$，记作操作 $(i,j,k)$」，其中 $A\oplus B$ 被定义为 $\{x\mid x\in A\cup B\land x\notin A\cap B\}$. 你的目标是让图满足以下两个条件之一：「没有边」和「是个树」。

将操作分为两部分进行，先让每个点的度不超过 $1$，此时如果全是孤点则结束；然后将所有连通分量连成一棵树。对于第一部分，可以不停选择度数超过 $1$ 的节点 $i$，随便选择他的两个邻点 $x,y$，进行操作 $(i,x,y)$，让边数至少减少 $1$. 这部分的操作至多进行 $m-1$ 次。用优先队列维护每个点的度数，set 维护邻点即可。对于第二部分，维护一条在树上的边 $(u,v)$（初始可以是一个有邻点的点和他的邻点），然后遍历每个点 $i$. 如果他已经被加入树中则跳过。如果他是孤点，则进行操作 $(u,v,i)$，然后令 $v\gets i$；否则，他一定有唯一的邻点 $j$，进行操作 $(v,i,j)$，同时把 $j$ 标记为「已经加入树中」即可。这部分操作会把图的边数从至少 $1$ 加到 $n-1$，每次操作边数都会加 $1$，故共操作 $n-1-1=n-2$ 次。总操作次数 $m-1+n-2=m_n-3\le 2\max(n,m)$，符合要求。

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
inline ostream& operator<<(ostream& out, __int128 x){if(!x){out<<"0";return out;}if(x<0){out<<"-";x*=-1;}char op[40]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){out<<op[cur--];}return out;}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const ll MAXN = 1e5 + 5;

ll n, m, dg[MAXN];
set<ll> e[MAXN];
prque<pll, vector<pll>, less<pll> > q;
vector<array<ll, 3> > ans;
bool inct[MAXN];

void ed() {
	write(ans.size()), enter();
	for (auto i : ans) {
		write(i[0]), space(), write(i[1]), space(), write(i[2]), enter();
	}
}

void init() {
	fill(dg, dg + n + 1, 0);
	fill(inct, inct + n + 1, 0);
	ans.clear();
	for (ll i = 1; i <= n; ++i) e[i].clear();
	while (!q.empty()) q.pop();
}
int mian() {
	read(n), read(m);
	for (ll i = 1, u, v; i <= m; ++i) {
		read(u), read(v);
		e[u].emp(v), ++dg[u];
		e[v].emp(u), ++dg[v];
	}
	for (ll i = 1; i <= n; ++i) {
		q.emp(mkp(dg[i], i));
	}
	while (!q.empty() && q.top().first >= 2) {
		ll h = q.top().second;
		if (dg[h] != q.top().first) {
			q.pop();
			continue;
		}
		q.pop();
		ll u = *e[h].begin(), v = *next(e[h].begin());
		e[h].erase(u), e[h].erase(v), dg[h] -= 2;
		e[u].erase(h), e[v].erase(h);
		if (e[u].find(v) != e[u].end()) {
			e[u].erase(v), e[v].erase(u);
			dg[u] -= 2, dg[v] -= 2;
			q.emp(mkp(dg[u], u)), q.emp(mkp(dg[v], v));
		} else {
			e[u].emp(v), e[v].emp(u);
		}
		q.emp(mkp(dg[h], h));
		ans.empb(array<ll, 3>({h, u, v}));
	}
	if (q.top().first == 0) {
		ed();
		return 0;
	}
	ll u = q.top().second, v = *e[u].begin();
	inct[u] = inct[v] = 1;
	for (ll i = 1; i <= n; ++i) {
		if (inct[i]) {
			continue;
		}
		inct[i] = 1;
		if (e[i].empty()) {
			ans.empb(array<ll, 3>({i, u, v}));
			v = i;
		} else {
			ll j = *e[i].begin();
			ans.empb(array<ll, 3>({v, i, j}));
			inct[j] = 1;
		}
	}
	ed();
	return 0;
}

int main() {
	ll T;
	read(T);
	while (T--) {
		init();
		mian();
	}
	return 0;
}

;             ;;;;;;;;;;;         ;
;                      ;         ; ;
;                    ;          ;   ;
;                   ;          ;     ;
;                 ;           ;;;;;;;;;
;               ;            ;         ;
;              ;            ;           ;
;;;;;;;;;;;   ;;;;;;;;;;   ;             ;

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

## 作者：gu51yo (赞：1)

通过把玩操作可以发现，我们可以试图构造以 $1$ 为根的树。

  首先对边操作，只要把和 $1$ 不相关的边都删掉，然后对点操作，使得所有点都和 $1$ 相连即可。

  做多操作 $m+n$ 次，时间复杂度 $O(m+n)$。
```
const int N=2e5+9;
int T, n, m, k, q;
int v, u, b[N];

void solve() {
	vector<int> A;
	cin >> n >> m;
	for(int i=1; i<=n; i++) b[i] = 0;
	for(int i=1; i<=m; i++) {
		cin >> u >> v;
		if(u!=1 && v!=1) {  // 所有不是1的点就操作
			A.push_back(1);
			A.push_back(u);
			A.push_back(v);
		}
		b[u]^= 1;  // 记录点的度数，如果是奇数，说明点和1有边。对点操作时就可以跳过。
		b[v]^= 1;
	}

	int p = 0;
	for(int i=2; i<=n; i++) if(b[i]) {p = i; break;}

	if(p) for(int i=2; i<=n; i++){ //对点操作
		if(!b[i]) {
			A.push_back(1);
			A.push_back(p);
			A.push_back(i);
			p = i;
		}
	}

	cout<< A.size()/3 << "\n";
	for(int i=0; i<A.size(); i++) cout << A[i] << "  \n"[i%3];
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);
	cin >> T; while(T--)
		solve ();
	return 0;
}
```

---

## 作者：_lmh_ (赞：0)

考虑边数非常多的情况，显然我们需要通过操作去掉一些边。

注意到我们操作次数上限是 $2(n+m)$，所以一次操作只要能去掉一条边就行。这就是说，**每次操作的 $a,b,c$ 三个点中至少两对节点之间有边**，等价于存在一个度数至少为 $2$ 的节点。

这样就很好做了，用 set 维护每个节点的出边，从 $1 \sim n$ 枚举每个度数 $>1$ 的节点，随便抽两条出边操作就行。

假设目前枚举到的度数 $>1$ 的节点是 $a$，那么剩下两个节点 $b,c$ 显然不会增加（必定删掉一条边，最多再增加一条边），所以这样枚举不会出现后面操作几次之后前面变出来度数大于一的节点的情况。

然后就剩下来一堆单点和孤立的边（度数最多为 $1$）。如果没有边就万事大吉了。

否则，随便搞一条边出来，将它的两个端点和其它连通块任意一点操作就能把两个连通块合并成一个，用并查集维护联通性即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=100007;
struct edge{ll to,nxt,pre,stat;}e[N<<2];
ll T,n,m,deg[N],fa[N];
set<ll> s[N];
vector<pair<pair<ll,ll>,ll> > ans;
ll getfa(ll x){return x==fa[x]?x:(fa[x]=getfa(fa[x]));}
void go(ll a,ll b,ll c){ans.emplace_back(make_pair(make_pair(a,b),c));}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m;ans.clear();
		for (int u,v,i=1;i<=m;++i){
			cin>>u>>v;
			s[u].insert(v);
			s[v].insert(u);
			++deg[u];++deg[v];
		}
		for (int i=1;i<=n;++i) while(deg[i]>=2){
			auto it=s[i].begin();
			ll x=*it;ll y=*next(it);
			s[i].erase(x);s[i].erase(y);
			s[x].erase(i);s[y].erase(i);
			deg[i]-=2;
			go(i,x,y);
			if (s[x].find(y)!=s[x].end()){
				s[x].erase(y);s[y].erase(x);
				deg[x]-=2;deg[y]-=2;
			}
			else{
				s[x].insert(y);s[y].insert(x);
			}
		}
		ll a,b,p=0;
		for (int i=1;i<=n;++i){fa[i]=i;}
		for (int i=1;i<=n;++i){
			if (deg[i]){
				a=i;b=*s[i].begin();
				p=1;
				fa[getfa(a)]=getfa(b);
			}
		}
		if (p){
			for (int i=1;i<=n;++i) if (getfa(i)!=getfa(a)){
				p=getfa(i);
				go(p,a,b);b=p;fa[p]=getfa(a);
			}
		}
		cout<<ans.size()<<'\n';
		for (auto p:ans) cout<<p.first.first<<' '<<p.first.second<<' '<<p.second<<'\n';
		for (int i=1;i<=n;++i){s[i].clear();deg[i]=0;}
	}
	return 0;
}
```

---

## 作者：tai_chi (赞：0)

可以在 [cnblog](https://www.cnblogs.com/tai-chi/p/18538159) 中阅读。

#### 题意

给一个 $n$ 个点 $m$ 条边的无向图，定义一次操作为：

- 选三个两两不同的顶点 $a,b,c$，考虑边 $(a,b),(a,c),(b,c)$，若该边存在则删除，若该边不存在则加入；

定义好图为满足下列之一的图：

- 没有边的图；
- 树。

最多可以进行 $2 \times \max\left\{n,m\right\}$ 次操作，构造方案将原图变为好图。

#### 分析

注意到操作次数的上界很有特点，这可能提示我们操作分为两步。

考虑先把图变为较为稀疏的图。我们对每个度数不小于 $2$ 的点 $x$，都对这个点和它的相邻节点进行一次操作。若相邻节点之间有连边，则操作删除了一个三元环的所有边；否则操作相当于将两个相邻节点连起来并断开 $x$ 与这两个节点的连边。

第一步后，原图转化为两类连通块：孤立点和两个点相连。如果不存在边那就做完了。

如果还有边我们就尝试将原图连成一棵树。选取当前已经连成一棵树的一个连通块为基础，将其他连通块合并到其中。若新的连通块是一个孤立点，选取其中的一个叶子和与它相连的一个点与之操作；若新的连通块是相连的两个点，选取一个叶子与之操作。不难验证操作的正确性。

由于需要动态维护边，使用 `set` 维护与一个节点相邻的点。

```cpp
void solve()
{
	int n,m; cin>>n>>m;
	vector<set<int>> gr(n+5);
	for(int i=1;i<=m;i++)
	{
		int u,v; cin>>u>>v;
		gr[u].insert(v);
		gr[v].insert(u);
	}
	vector<array<int,3>> ans;
	auto fun=[&](int a,int b,int c)
	{
		ans.push_back({a,b,c});
		if(gr[b].find(c)!=gr[b].end())
		{
			gr[a].erase(b); gr[a].erase(c);
			gr[b].erase(a); gr[b].erase(c);
			gr[c].erase(a); gr[c].erase(b);
		}
		else
		{
			gr[a].erase(b); gr[b].erase(a);
			gr[a].erase(c); gr[c].erase(a);
			gr[b].insert(c); gr[c].insert(b);
		}
	};
	for(int i=1;i<=n;i++)
	{
		while(gr[i].size()>=2)
		{
			auto x=gr[i].begin(), y=next(x);
			fun(i,*x,*y);
		}
	}
	int x=0,y=0;
	for(int i=1;i<=n;i++)
	{
		if(gr[i].size()==1)
		{
			x=i; y=*gr[i].begin();
			break;
		}
	}
	if(x==0)
	{
		cout<<ans.size()<<"\n";
		for(auto [a,b,c]:ans) cout<<a<<" "<<b<<" "<<c<<"\n";
		return;
	}
	vector<int> vis(n+5,0);
	vis[x]=vis[y]=1;
	for(int i=1;i<=n;i++)
	{
		if(vis[i]) continue;
		if(gr[i].size()==1) ans.push_back({i,*gr[i].begin(),x}), vis[*gr[i].begin()]=1;
		else ans.push_back({x,y,i}), y=i;
	}
	cout<<ans.size()<<"\n";
	for(auto [a,b,c]:ans) cout<<a<<" "<<b<<" "<<c<<"\n";
}
```

---

