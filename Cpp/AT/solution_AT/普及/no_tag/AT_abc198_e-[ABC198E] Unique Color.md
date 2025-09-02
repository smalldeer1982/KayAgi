# [ABC198E] Unique Color

## 题目描述

给定一棵以 $1$ 节点为根的树。每个节点上都被染了一种颜色，不同颜色用不同整数表示。问：有多少个节点，它们到根节点的路径上的所有点（除了自己）的颜色都与自己的颜色不同。

## 样例 #1

### 输入

```
6
2 7 1 8 2 8
1 2
3 6
3 2
4 3
2 5```

### 输出

```
1
2
3
4
6```

## 样例 #2

### 输入

```
10
3 1 4 1 5 9 2 6 5 3
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10```

### 输出

```
1
2
3
5
6
7
8```

# 题解

## 作者：CQ_Bab (赞：1)

# 思路
我们可以直接遍历整棵树，然后用一个标记数组记录下有哪些颜色出现过，若没出现过则可以累加进答案，这里可以在传参时用一个参数来表示是否有过此颜色，若没遍历过直接计入答案即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define rep(i,x,y) for(int i=x;i<=y;i++)
const int N=2e5+10;
int n,x,y,h[N];
int c[N],tot;
int cnt,ans[N];
bool mp[N];
struct node {
	int x,y;
} edg[N];
void add(int x,int y) {
	edg[++tot].x=y;
	edg[tot].y=h[x];
	h[x]=tot;
}
void dfs(int x,int fa,int f) {
	if(!f) ans[x]=1; //没遍历过计入答案
	for(int i=h[x]; i; i=edg[i].y) {
		int to=edg[i].x;
		if(to!=fa&&!mp[c[to]]) {
			mp[c[to]]=1; //标记
			dfs(to,x,0); 
			mp[c[to]]=0; //回溯
		}else if(mp[c[to]]&&to!=fa) dfs(to,x,1);
	} 
}
signed main() {
	cin>>n;
	rep(i,1,n) cin>>c[i];
	rep(i,1,n-1) {
		cin>>x>>y;
		add(x,y);
		add(y,x);
	}
	mp[c[1]]=1;
	dfs(1,0,0);
	rep(i,1,n) if(ans[i]) cout<<i<<endl; //输出
	return false;
}
/*
6
2 7 1 8 2 8
1 2
3 6
3 2
4 3
2 5
10
3 1 4 1 5 9 2 6 5 3
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
*/
```

---

## 作者：_shine_ (赞：1)

## 题目大意
现在有一个由 $n$ 个顶点组成的树，现在问你有多少个从 $1$ 到 $x$ 的最短路径中，没有跟颜色 $c_x$ 一样的 $x$？ 
## 思路
一道很经典的深度优先搜索题。我们可以遍历整棵树，记录下每一个节点的颜色，每一次搜索时都判断是否是好的即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int n,c[maxn];
vector<int>a[maxn];//vector存边，可以不使用链式前项星
bool vis[maxn];
int ans[maxn],idx,cnt[maxn];
void dfs(int np){
	if(vis[np]==true)return ;
	if(cnt[c[np]]==0)ans[++idx]=np;
	vis[np]=true;
	cnt[c[np]]++;
	for(int i=0;i<a[np].size();++i){
		if(vis[a[np][i]]==false){
			dfs(a[np][i]);
		}
	}
	cnt[c[np]]--;
}
signed main(){
	cin >> n;
	for(int i=1;i<=n;++i){
		cin >> c[i];
	}
	for(int i=1;i<n;++i){
		int x,y;
		cin >> x >> y;
		a[x].push_back(y);
		a[y].push_back(x);
	}
	dfs(1);
	sort(ans+1,ans+idx+1);
	for(int i=1;i<=idx;++i){
		cout << ans[i] << endl;
	}
	return 0;
}
/*
6
2 7 1 8 2 8
1 2
3 6
3 2
4 3
2 5

10
3 1 4 1 5 9 2 6 5 3
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
*/
```


---

## 作者：tZEROちゃん (赞：0)

比较简单的 E 题。

可以使用 dfs 解决此题。

考虑记 $cnt_i$ 表示从 $1$ 号点到当前点第 $i$ 种颜色用的数量。

然后遍历整棵树，一边遍历一边记录即可。

时间复杂度是 $O(n)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for(auto i = (l); i <= (r); ++i)
#define per(i, r, l) for(auto i = (r); i >= (l); --i)
#define _rep(i, l, r) for(auto i = (l); i < (r); ++i)
#define _per(i, r, l) for(auto i = (r); i > (l); --i)
#define pb push_back

const int N = 1e5 + 10;
vector<int> G[N];
bool ck[N], vis[N]; int cnt[N];
int c[N];
int n;

void dfs(int rt) {
  if (cnt[c[rt]] == 0) ck[rt] = 1;
  cnt[c[rt]]++;
  vis[rt] = 1;
  for (auto v : G[rt]) {
    if (!vis[v]) dfs(v);
  }
  cnt[c[rt]]--;
}

int main() {
  cin >> n;
  rep (i, 1, n) cin >> c[i];
  _rep (i, 1, n) {
    int u, v; cin >> u >> v;
    G[u].pb(v), G[v].pb(u);
  }  
  dfs(1);
  rep (i, 1, n) if (ck[i]) cout << i << '\n';
}
```

---

## 作者：loser_seele (赞：0)

在所有 E 题里算简单的了。

实际上题目可以转化为在树上从 $ 1 $ 号点到所有点的路径中统计某种颜色的数量。因为给定的图是树，不难想到直接跑一遍 dfs，在 dfs 过程中维护当前路径上每种颜色的数量，到达一个点时更新这种颜色的数量，回溯的时候去掉这个点的颜色，这个显然是 $ \mathcal{O}(1) $ 的，然后看当前颜色的数量是否为 $ 1 $，这个也是 $ \mathcal{O}(1) $ 的。所以只需要遍历一遍树即可获得全部答案。

因为要 dfs 整个树一遍，所以时间复杂度 $ \mathcal{O}(n) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int cnt[maxn],ans[maxn],vis[maxn],col[maxn];
vector<int>g[maxn];
void dfs(int x)
{
cnt[col[x]]++;
vis[x]=1;
if(cnt[col[x]]==1)
ans[x]=1;
for(auto v:g[x])
if(!vis[v])
dfs(v);
cnt[col[x]]--;
}
int main() 
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    cin>>col[i];
    for(int i=1;i<=n-1;i++)
    {
    int u,v;
    cin>>u>>v;
    g[u].push_back(v);
    g[v].push_back(u);
    }
    dfs(1);
    for(int i=1;i<=n;i++)
    if(ans[i])
    cout<<i<<'\n';
}
```


---

