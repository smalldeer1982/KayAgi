# Wires

## 题目描述

Polycarpus has a complex electronic device. The core of this device is a circuit board. The board has $ 10^9 $ contact points which are numbered from $ 1 $ to $ 10^9 $ . Also there are $ n $ wires numbered from $ 1 $ to $ n $ , each connecting two distinct contact points on the board. An electric signal can pass between wires $ A $ and $ B $ if:

- either both wires share the same contact point;
- or there is a sequence of wires starting with $ A $ and ending with $ B $ , and each pair of adjacent wires in the sequence share a contact point.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1250N/6e2b2c43d3bbdc24d7f958ca966b6424ae4f2ebd.png)The picture shows a circuit board with $ 5 $ wires. Contact points with numbers $ 2, 5, 7, 8, 10, 13 $ are used. Here an electrical signal can pass from wire $ 2 $ to wire $ 3 $ , but not to wire $ 1 $ .Currently the circuit board is broken. Polycarpus thinks that the board could be fixed if the wires were re-soldered so that a signal could pass between any pair of wires.

It takes $ 1 $ minute for Polycarpus to re-solder an end of a wire. I.e. it takes one minute to change one of the two contact points for a wire. Any contact point from range $ [1, 10^9] $ can be used as a new contact point. A wire's ends must always be soldered to distinct contact points. Both wire's ends can be re-solded, but that will require two actions and will take $ 2 $ minutes in total.

Find the minimum amount of time Polycarpus needs to re-solder wires so that a signal can pass between any pair of wires. Also output an optimal sequence of wire re-soldering.

## 样例 #1

### 输入

```
2
1
4 7
4
1 2
2 3
4 5
5 6
```

### 输出

```
0
1
2 3 5
```

# 题解

## 作者：123zbk (赞：1)

先用并查集求出连通块的个数 $cnt$，那么操作次数就是 $cnt-1$。因为我们可以在其他 $cnt-1$ 个连通块中各找到一条边，而不影响它成为连通块，然后将它和最后一条边连上。

对于每一个连通块 dfs 一遍，遍历到的最后一条边就是所求的边。然后记录一下这是第几条边和 $v$ 即可。

注意本题要离散化。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
int tot,id,num[maxn],cnt,T,m,sum;
int head[maxn],u[maxn],v[maxn],fa[maxn],vis[maxn],rk[maxn];
map <pair<int,int>,int> mp;
pair <int,int> ans[maxn];
struct edge
{
	int to,nxt;
}e[maxn];
void add(int u,int v)
{
	++tot;
	e[tot].to=v;
	e[tot].nxt=head[u];
	head[u]=tot;
}
int get_fa(int x)
{
	return fa[x]==x?x:fa[x]=get_fa(fa[x]);
}
void dfs(int u,int fa,int &to,int &t)
{
	vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa)
		{
			continue;
		}
		if(vis[v]==1)
		{
			return;
		}
		to=v;
		t=mp[make_pair(min(u,v),max(u,v))];
		dfs(v,u,to,t); 
	}
}
void clear()
{
	for(int i=1;i<=id;i++)
	{
		head[i]=vis[i]=0;	
	} 
	tot=cnt=id=sum=0;
	mp.clear();
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&m);
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&u[i],&v[i]);
			num[++cnt]=u[i];
			num[++cnt]=v[i];
		}	
		sort(num+1,num+cnt+1);
		id=unique(num+1,num+cnt+1)-num-1;
		for(int i=1;i<=m;i++)
		{
			int x=u[i];
			u[i]=lower_bound(num+1,num+id+1,u[i])-num;
			rk[u[i]]=x;
			int y=v[i];
			v[i]=lower_bound(num+1,num+id+1,v[i])-num;
			rk[v[i]]=y;
		}
		for(int i=1;i<=id;i++)
		{
			fa[i]=i;
		}
		for(int i=1;i<=m;i++)
		{
			add(u[i],v[i]);
			add(v[i],u[i]);
			int a=min(u[i],v[i]);
			int b=max(u[i],v[i]); 
			mp[make_pair(a,b)]=i;
			int uu=get_fa(u[i]);
			int vv=get_fa(v[i]);
			if(uu!=vv)
			{
				fa[vv]=uu;
			}
		} 
		for(int i=1;i<=id;i++)
		{
			if(fa[i]==i)
			{
				int to=0,t=0;
				dfs(i,0,to,t);
				ans[++sum].first=to;
				ans[sum].second=t;
			}
		}
		for(int i=id;i>=1;i--)
		{
			if(fa[i]==i)
			{
				printf("%d\n",sum-1);
				for(int j=1;j<=sum-1;j++)
				{
					printf("%d %d %d\n",ans[j].second,rk[ans[j].first],rk[i]);
				}
				break;
			}
		}
		clear();
	}	
	return 0;
} 
```

---

## 作者：wangyibo201026 (赞：0)

## solution

首先离散化。

感受一下，如果是将 $cnt$ 个连通块连起来，最少应该是要更改 $cnt - 1$ 条边的（就是将连通块连成一个树结构）。

然后考虑如何连边，随便找到一个度数为 $1$ 的结点，可以将其之间的边办掉，然后全部连向 $1$ 结点。如果没有度数为 $1$ 的结点，那么随便办掉一条边都是可以的。

比较好的写法是，对于每个连通块，求出 DFS 树上任意一个叶子所连的树边，把这条边办掉连向 $1$ 结点，不难发现其与上面说的连边方式一样。

## code

code：

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )
 
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair < int, int > pii;
 
char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}
 
template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 2e5 + 5;

int t, n, cnt;
bool vis[N];
map < int, int > mp, mp2;
vector < pair < int, pii > > ans;
pii tmp;

int head[N], tot = 1;

struct Node {
  int to, id, next;
} edges[N << 1];

void add ( int u, int v, int id ) {
  tot ++;
  edges[tot].to = v;
  edges[tot].id = id;
  edges[tot].next = head[u];
  head[u] = tot;
}

void dfs ( int x, int lst ) {
  vis[x] = 1;
  int son = 0;
  for ( int i = head[x]; i; i = edges[i].next ) {
    if ( !vis[edges[i].to] ) {
      son ++;
      dfs ( edges[i].to, i );
    }
  }
  if ( !son ) {
    tmp = { edges[lst].id, x };
  }
}

void Solve () {
  cin >> t;
  while ( t -- ) {
    mp.clear (), mp2.clear (), ans.clear ();
    cnt = 0;
    tot = 1;
    cin >> n;
    for ( int i = 1; i <= 2 * n; i ++ ) {
      head[i] = vis[i] = 0;
    }
    for ( int i = 1; i <= n; i ++ ) {
      int u, v;
      cin >> u >> v;
      if ( !mp[u] ) {
        mp[u] = ++ cnt;
        mp2[cnt] = u;
      }
      if ( !mp[v] ) {
        mp[v] = ++ cnt;
        mp2[cnt] = v;
      }
      add ( mp[u], mp[v], i ), add ( mp[v], mp[u], i );
    }
    for ( int i = 1; i <= cnt; i ++ ) {
      if ( !vis[i] ) {
        dfs ( i, 0 );
        if ( i != 1 ) {
          ans.push_back ( { tmp.first, { mp2[tmp.second], mp2[1] } } );
        }
      }
    }
    cout << ans.size () << '\n';
    for ( pair < int, pii > x : ans ) {
      cout << x.first << " " << x.second.first << " " << x.second.second << '\n';
    }
  }
}

signed main () {
#ifdef judge
  freopen ( "Code.in", "r", stdin );
  freopen ( "Code.out", "w", stdout );
  freopen ( "Code.err", "w", stderr );
#endif
  Solve ();
  return 0;
}
```

---

## 作者：LOVE_Ynoi (赞：0)

观察题目，容易发现每个连通块只需要重连一条边就可以达成题目要求。  
考虑我们可以切掉哪些边，发现只要在 ``dfs`` 中不能继续往下搜索的边就是我们可以割掉的边，因为它下面没有其他边，不会创造新的连通块。  
我们只要记录这条边的起点或终点，然后将所有其他连通块的起点全都连向第一个连通块终点即可。  
代码上先将点离散化，`dfs` 求连通块和可以割掉的边，然后统计答案即可。


代码：（有点丑）
```c++
#include <bits/stdc++.h>
using namespace std;
int m;
vector<int> G[200010];
int col[200010];
int u[200010], v[200010];
map<pair<int, int>, int> id;
map<pair<int, int>, int> book;
bool vis[200010];
int tag[200010];
vector<pair<int, int>> ans;
int cnt = 0;
void dfs(int u, int x)
{
    vis[x] = true;
    bool fl = false;
    for (auto to : G[x])
        if (!vis[to])
            dfs(x, to), fl = true;
    if (!fl)
        ans.push_back({u, x});
}
int leaf[200010], reaf[200010];
void solve()
{
    vector<int> p;
    map<int, int> mp;
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> u[i] >> v[i];
        p.push_back(u[i]), p.push_back(v[i]);
    }
    sort(p.begin(), p.end());
    int n = unique(p.begin(), p.end()) - p.begin();
    cnt = 0;
    for (int i = 1; i <= n; i++)
        G[i].clear(), vis[i] = 0, tag[i] = 0, col[i] = 0, leaf[i] = 0, reaf[i] = 0;
    id.clear(), ans.clear(), book.clear();
    for (int i = 1; i <= m; i++)
    {
        u[i] = lower_bound(p.begin(), p.begin() + n, u[i]) - p.begin() + 1;
        v[i] = lower_bound(p.begin(), p.begin() + n, v[i]) - p.begin() + 1;
        G[u[i]].push_back(v[i]);
        G[v[i]].push_back(u[i]);
        id[{u[i], v[i]}] = id[{v[i], u[i]}] = i;
    }
    int y = -1;
    for (int i = 1; i <= n; i++)
    {
        ans.clear();
        if (!vis[i])
        {
            dfs(i, i), cnt++;
            if (y == -1)
                y = ans.front().second;
            else if (leaf[i] == 0)
                leaf[i] = ans.front().second, reaf[i] = ans.front().first;
        }
    }
    cout << cnt - 1 << endl;
    for (int i = 1; i <= n; i++)
    {
        if (leaf[i] != 0)
            cout << id[{reaf[i], leaf[i]}] << " " << p[leaf[i] - 1] << " " << p[y - 1] << "\n";
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int _;
    cin >> _;
    while (_--)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：I_am_Accepted (赞：0)

似乎还没有人写题解……

设初始连通块数为 $cnt$，似乎很显然最终答案一定是 $cnt-1$：

* 由于最后要连通，所以答案 $\ge cnt-1$。

* 接下来我们构造一组 $cnt-1$ 的方案。

我们对于每一个连通块随便找一个生成树，每一棵生成树随便找一个叶子，得知我们将这个叶子随意拖动都不会分裂这个本来的连通块，所以我们将 $cnt-2$ 个叶子连到剩下那个连通块的任意一个点即可。

```cpp
//We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define Rof(i,j,k) for(int i=(j),i##_=(k);i>=i##_;i--)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define Fi(s) freopen(s,"r",stdin)
#define Fo(s) freopen(s,"w",stdout)
#define Fre(s) Fi(s".in"),Fo(s".out")
#define debug(...) cerr<<"#"<<__LINE__<<": "<<__VA_ARGS__<<endl
#define ll long long
const ll mod=1;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
#define int ll
#define pi pair<int,int>
#define N 100010
pi a[N];
vector<pi> e[2*N];
int b[2*N],n,lim,lst,id;
bool v[2*N];
int f[2*N],rep[2*N],ed[2*N];
vector<pi> ans;
inline int gf(int x){
	return x==f[x]?x:f[x]=gf(f[x]);
}
void dfs(int x){
	v[x]=1;
	lst=x;
	for(auto i:e[x]) if(!v[i.fir]) id=i.sec,dfs(i.fir);
}
void work(){
	cin>>n;
	For(i,1,n) cin>>a[i].fir>>a[i].sec;
	For(i,1,n) b[2*i-1]=a[i].fir,b[2*i]=a[i].sec;
	sort(b+1,b+1+2*n);
	lim=unique(b+1,b+1+2*n)-b-1;
	For(i,1,n)
		a[i].fir=lower_bound(b+1,b+1+lim,a[i].fir)-b,
		a[i].sec=lower_bound(b+1,b+1+lim,a[i].sec)-b;
	For(i,1,lim) e[i].clear();
	For(i,1,n) e[a[i].fir].pb(mkp(a[i].sec,i)),e[a[i].sec].pb(mkp(a[i].fir,i));
	fill(v+1,v+1+lim,false);
	iota(f+1,f+1+lim,1);
	For(i,1,n) f[gf(a[i].fir)]=gf(a[i].sec);
	For(i,1,lim) gf(i);
	For(i,1,lim) if(!v[i]){
		dfs(i);
		rep[f[i]]=lst;
		ed[f[i]]=id;
	}
	ans.clear();
	fill(v+1,v+1+lim,false);
	For(i,1,lim) if(!v[f[i]]){
		v[f[i]]=1;
		ans.pb(mkp(rep[f[i]],ed[f[i]]));
	}
	int k=ans.size()-1;
	cout<<k<<endl;
	For(i,0,k-1) cout<<ans[i].sec<<" "<<b[ans[i].fir]<<" "<<b[ans.back().fir]<<endl;
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(nullptr);
	int T;cin>>T;
	while(T--)work();
return 0;}
```

---

