# [ABC219G] Propagation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc219/tasks/abc219_g

$ N $ 頂点 $ M $ 辺の単純無向グラフが与えられます。$ N $ 個の頂点はそれぞれ頂点 $ 1 $ 、頂点 $ 2 $ 、$ \ldots $ 、頂点 $ N $ と呼ばれます。  
 $ i\ =\ 1,\ 2,\ \ldots,\ M $ について、$ i $ 番目の辺は頂点 $ u_i $ と頂点 $ v_i $ を結んでいます。  
 また、$ i\ =\ 1,\ 2,\ \ldots,\ N $ について、頂点 $ i $ には整数 $ i $ が書かれています。

$ Q $ 個のクエリが与えられます。  
 $ i\ =\ 1,\ 2,\ \ldots,\ Q $ について、$ i $ 番目のクエリは整数 $ x_i $ で表されます。 $ i $ 番目のクエリでは以下の操作をおこないます。

1. 頂点 $ x_i $ に書かれている整数を $ X $ とおく。
2. 頂点 $ x_i $ と隣接するすべての頂点について、それに書かれた整数を $ X $ に書き換える。

ただし、頂点 $ u $ と頂点 $ v $ が隣接するとは、頂点 $ u $ と頂点 $ v $ を結ぶ辺が存在することを言います。

入力で与えられる順にすべてのクエリを処理した後の時点における、各頂点に書かれた整数をそれぞれ出力して下さい。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ \min(2\ \times\ 10^5,\ N(N-1)/2) $
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ u_i,\ v_i\ \leq\ N $
- $ 1\ \leq\ x_i\ \leq\ N $
- 与えられるグラフは単純である。すなわち、自己ループや多重辺は存在しない。
- 入力はすべて整数

### Sample Explanation 1

それぞれのクエリでは以下のような操作が行われます。 - $ 1 $ 番目のクエリ $ (x_1\ =\ 1) $ : 頂点 $ 1 $ に書かれた整数は $ 1 $ であり、頂点 $ 1 $ に隣接する頂点は頂点 $ 2 $ と頂点 $ 5 $ です。 よって、頂点 $ 2 $ と頂点 $ 5 $ に書かれた整数がそれぞれ $ 1 $ に書き換えられます。 - $ 2 $ 番目のクエリ $ (x_2\ =\ 3) $ : 頂点 $ 3 $ に書かれた整数は $ 3 $ であり、頂点 $ 3 $ に隣接する頂点は頂点 $ 2 $ と頂点 $ 4 $ です。よって、頂点 $ 2 $ と頂点 $ 4 $ に書かれた整数がそれぞれ $ 3 $ に書き換えられます。 - $ 3 $ 番目のクエリ $ (x_3\ =\ 4) $ : 頂点 $ 4 $ に書かれた整数は $ 3 $ であり、頂点 $ 4 $ に隣接する頂点は頂点 $ 2 $ 、頂点 $ 3 $ 、頂点 $ 5 $ です。よって、頂点 $ 2 $ 、頂点 $ 3 $ 、頂点 $ 5 $ に書かれた整数がそれぞれ $ 3 $ に書き換えられます。 （頂点 $ 2 $ と頂点 $ 3 $ にはすでに $ 3 $ が書かれているので、書かれた整数が実際に変更されるのは頂点 $ 5 $ のみです。）

## 样例 #1

### 输入

```
5 6 3
4 2
4 3
1 2
2 3
4 5
1 5
1 3 4```

### 输出

```
1 3 3 3 3```

## 样例 #2

### 输入

```
14 14 8
7 4
13 9
9 8
4 3
7 2
13 8
12 8
11 3
6 3
7 14
6 5
1 4
10 13
5 2
2 6 12 9 1 10 5 4```

### 输出

```
1 6 1 1 6 6 1 9 9 10 11 12 10 14```

# 题解

## 作者：ziyistudy (赞：3)

学校断网 VP 的时候 A 的，于是决定来写一篇题解。

很容易就可以想到根号分治。至于为什么可以想到，引用某大佬的话“啪的一下就想到根号分治，很快啊”。

以下简称与节点 $u$ 直接相连的节点的个数（即节点 $u$ 的边数）为 $u$ 的大小。令 $hal=\sqrt{2\times10^5}$。

当你发现：大小超过 $hal$ 的节点不会超过 $hal$ 个时，本题就结束了（证明过于简单，此处略）。

所以，当点 $u$ 的大小小于 $hal$，直接暴力染色周围节点即可；否则，给当前节点打上标记（分别为：颜色和时间）。

当要更新该节点时，只需要搜索与它直接相连的节点中大小不超过 $hal$ 的节点，依次查看是否需要更新（更新时查看该节点的更改时间是否晚于本节点）。

以上操作均为更号级别。

时间复杂度：$O(q\sqrt{m})$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
const int hal=450;
vector<vector<int>> G(N);
vector<vector<int>> nxt(N);
int a[N];
int col[N],tim[N],tim1[N];
signed main()
{
	
	int n,m,q;cin>>n>>m>>q;
	for(int i=1;i<=n;i++) a[i]=i;
	for(int i=1;i<=m;i++){
		int u,v;cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		if(G[i].size()<hal) continue;
		for(auto it:G[i]) nxt[it].push_back(i);
	}
	for(int i=1;i<=q;i++)
	{
		int dir;cin>>dir;
		
		int cnt=0,maxn=0;
		for(auto it:nxt[dir]) {
			if(tim1[it]>maxn&&tim1[it]>tim[dir]){
				maxn=tim1[it];
				cnt=col[it];
			}
		}
		if(cnt!=0) a[dir]=cnt,tim[dir]=maxn;
		
		if(G[dir].size()<hal) for(auto it:G[dir]) a[it]=a[dir],tim[it]=i;
		else {
			col[dir]=a[dir];
			tim1[dir]=i;
		}
	}
	for(int i=1;i<=n;i++) {
		int cnt=0,maxn=0;
		for(auto it:nxt[i]) {
			if(tim1[it]>maxn&&tim1[it]>tim[i]){
				maxn=tim1[it];
				cnt=col[it];
			}
		}
		if(cnt!=0) a[i]=cnt,tim[i]=maxn;
		cout<<a[i]<<" ";
	}
}
```

---

## 作者：mojoege (赞：3)

## 题意

给你一个 $n$ 个点 $m$ 条边的无向图, 每个点上有数 $a_i$. 初始情况下, $a_i=i$.

现在进行 $q$ 次操作, 每次给定一个数 $u$. 对于所有与 $u$ 直接相连的点 $v$, 把 $a_v$ 改为 $a_u$.

所有操作后, 求 $a$ 序列

## 分析

根号分治，简单来说就是小于某一个值和大于某个值分开来做。

这题如果用暴力就是 $n^2$ 级别的，会炸。在想优化的过程中，我们发现如果把所有要修改的点都打上标记的话，还是在 $n^2$ 级别的，但是变成了修改 $O(1)$，查询 $O(n)$ 的东西，这种跟分块有点类似——就是根号分治。我们的目的就是平摊复杂度，修改 $\sqrt {n}$，查询 $\sqrt{n}$。

如何分块？只要把点分成两类，重点和轻点——重点代表所连边数大于等于 $\sqrt{m}$，轻点则相反。

轻点就可以直接在操作的时候暴力修改，而重点就可以打一个类似于线段树的 lazytag，包含一个当前颜色 color 和修改时间 time。**注意**，这里的 tag 是指这个重点放出的颜色的 color 和 time，而不是这个点最终颜色。

还需要预处理一下，再建一个图，只由轻点和所连接的重点构成。

具体操作时，先把要修改的那个点还原出来，也就是把与它邻接的重点的 tag 扒出来，找到修改时间最晚并且晚于当前节点修改时间的重点，覆盖掉当前节点，并更新当前节点的 time。

然后分治重点和轻点，轻点直接更新，重点打上一个 tag，等到下次要用到这个重点的时候再按上一个步骤中的操作还原到需要的节点上。

对于复杂度的证明，重点不超过 $\sqrt{m}$ 个（每个点连出 $\sqrt{m}$ 条边，只有 $\frac{m}{\sqrt{m}}=\sqrt{m}$ 个点），于是还原节点最多 $O(\sqrt{m})$；打上 tag 的复杂度为 $O(1)$；轻点所连的边不超过 $\sqrt{m}$，更新一次复杂度也不超过 $\sqrt{m}$。预处理阶段，只连接轻点和重点，不超过 $n \sqrt{m}$；最后输出操作也不超过 $n \sqrt{m}$。总复杂度在 $n\sqrt{n}$ 级，可过。

## 代码
```cpp
#include  <bits/stdc++.h>
using namespace std;

int n, m, q, len;
int col[200005], tim[200005];//最终答案和标记时间
int col1[200005], tim1[200005];//重点放出的color和放出时间
vector<int> g[200005], e[200005];//完整的图和每一个轻点连向重点的图

int find(int x){//找到更新时间最晚的重点
    int mxt = tim[x], tmp = col[x];//先记录当前节点更新时间，便于后面判断是否晚于当前节点
    for (int i = 0; i < e[x].size(); i++){
        int v = e[x][i];
        if (mxt < tim1[v]) mxt = tim1[v], tmp = col1[v];
    }
    return tmp;
}

int main(){
    cin >> n >> m >> q;
    len = sqrt(m);
    for (int i = 1; i <= n; i++) col[i] = i;
    for (int i = 1, u, v; i <= m; i++){
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++){
        if (g[i].size() < len) continue;
        for (int j = 0; j < g[i].size(); j++) e[g[i][j]].push_back(i);//只记录轻点连向重点的边，达到 根号 m 的复杂度
    }
    for (int _ = 1, x; _ <= q; _++){
        cin >> x;
        col[x] = find(x), tim[x] = _;
        if (g[x].size() >= len) col1[x] = col[x], tim1[x] = _;//重点打上lazytag
        else{
            for (int i = 0; i < g[x].size(); i++) col[g[x][i]] = col[x], tim[g[x][i]] = _;//轻点直接更新
        }
    }
    for (int i = 1; i <= n; i++) cout << find(i) << " ";//跟上面还原 col[x] 一个道理
    return 0;
}
```

---

## 作者：Dream__Sky (赞：2)

考虑根号分治。

首先我们把这 $n$ 个点，分成两种考虑，一种是连边数大于 $\sqrt{m}$ 的重点，一种是小于 $\sqrt{m}$ 的轻点。我们要保证复杂度为 $O(q\sqrt{m})$，那么重点只能打标记，与线段树的懒标记类似，需要用到时再下放。轻点则可以暴力更改。

首先考虑如何暴力修改。无论是哪种点，我们首先建立两个数组 $col$ 和 $t$，分别代表，当前点现在的颜色和最后一次被更改的时间。我们对每一个与当前轻点 $u$ 连边的点 $v$ 修改，即 $col_v=col_u,t_v=i$。

再考虑如何打标记。对于每一个重点，我们再建立两个数组 $lc$ 和 $lt$，分别代表，当前这个重点最后一次需要向外更改的时间，与需要更改的颜色。每次更新为 $lt_u=i,lc_u=col_u$（$u,v,col$ 与上文提到的意思一致）。


接着考虑如何下放。由于轻点是直接修改的，那我们只要考虑重点对于当前颜色的更改情况。在进行 $q$ 次操作前，我们先预处理出与每一个点连边的重点。每次遍历这些重点，寻找一个更改时间最迟的点进行更改的，更新颜色。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m,q,col[N],t[N],lc[N],lt[N],fg[N];
vector<int> v[N],e[N];
void init()
{
	int len=sqrt(m),x,y;
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	
	for(int i=1;i<=n;i++) col[i]=i;
	
	for(int i=1;i<=n;i++)
		if(v[i].size()>=len) fg[i]=1;
	
	for(int i=1;i<=n;i++)
		for(int j=0;j<v[i].size();j++) 
			if(fg[v[i][j]]) e[i].push_back(v[i][j]);
}
int find(int u)
{
	int k=col[u],tim=t[u];
	for(int i=0;i<e[u].size();i++)
		if(tim<lt[e[u][i]]) k=lc[e[u][i]],tim=lt[e[u][i]];
	return k;
}
int main()
{
	cin>>n>>m>>q;
	init();
	for(int i=1,x;i<=q;i++)
	{
		cin>>x;
		col[x]=find(x),t[x]=i;
		if(fg[x]) lt[x]=i,lc[x]=col[x];
		else for(int j=0;j<v[x].size();j++) col[v[x][j]]=col[x],t[v[x][j]]=i;
	}
	for(int i=1;i<=n;i++) cout<<find(i)<<" ";
	return 0;
}

```




---

## 作者：Purslane (赞：1)

## Solution

暴力肯定是 $O(qm)$ 的。$q$ 毫无商榷之地，它不可能改变的，那么只能在 $m$ 上面下功夫。

考虑根号分治。我们把节点分成两种：重要点，它的度数大于等于 $\sqrt m$，另一种是非重要点，它的度数小于 $\sqrt m$。

对于非重要点的操作，由于与之相邻的点比较少，可以暴力修改；重要点，显然只能在原地打标记。

我们对于每个点维护它最后一次被修改的时间和修改的数值，而重要点还要维护最后一次往外修改的时间和往外修改的值。求一个点现在的值，要从自己和周围所有重要点中选取能修改到这个点的最晚的时间。

具体如下 ：

```cpp
int get_val(int u) {
	int ans=v[u],lst_time=lst[u];
	for(auto to:GG[u]) if(t[to]>ltime) ans=tv[to],lst_time=t[to];
	return ans;
}
```

其中 `GG` 数组表示所有相邻的重要点。

这样单次的复杂度是 $O(\sqrt m)$ 的，总体复杂度是 $O(q\sqrt m)$ 的。

代码 ：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,m,q,bl,v[MAXN],lst[MAXN],deg[MAXN],flg[MAXN],t[MAXN],tv[MAXN];
vector<int> imp,nimp[MAXN],G[MAXN],GG[MAXN];
int get_val(int u) {
	int ans=v[u],ltime=lst[u];
	for(auto to:GG[u]) if(t[to]>ltime) ans=tv[to],ltime=t[to];
	return ans;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>q; bl=sqrt(m);
	ffor(i,1,m) {
		int u,v; cin>>u>>v;
		G[u].push_back(v),G[v].push_back(u),deg[u]++,deg[v]++;	
	}
	ffor(i,1,n) if(G[i].size()>=bl) flg[i]=1;
	ffor(i,1,n) for(auto v:G[i]) if(flg[v]) GG[i].push_back(v);
	ffor(i,1,n) v[i]=i;
	ffor(i,1,q) {
		int u; cin>>u;
		v[u]=get_val(u),lst[u]=i;
		if(flg[u]) tv[u]=v[u],t[u]=i;
		else for(auto to:G[u]) v[to]=v[u],lst[to]=i;
	}
	ffor(i,1,n) cout<<get_val(i)<<' ';
	return 0;
}
```

---

## 作者：vicky2048_2 (赞：0)

遇到这种无路可走操作题，直接上根号分治乱搞就能使我们 win 得很彻底！！！

------------
去掉重边之后直接暴力处理是 $O(qn)$ 的，稳寄。

考虑优化，不难想到对结点 $u$ 打标记，标记其最后一次操作的时间  $i$ 和最后一次操作时的 $a_u$。

然后在需要求 $a_u$ 时把它所有邻接点最晚打出的标记打在 $u$ 身上即，每次求 $a_u$ 都是 $O(n)$ 的。

但我们分析之后发现，每次打标记都需要求 $a_u$，也就是说只以打标记的思路做优化的时间复杂度是让人很难绷的 $O(qn)$。

打标记操作为什么没起到优化作用呢？

因为每个点的邻接点数量没有得到优化。

~~哦哦，只要我们根号分治题做得足够多，我们便不难得到新的思考方向。~~

我们尝试为每次操作中的 $u$ 的度数设置一个阈值 $\sqrt{n}$。

很容易得到度数大于 $\sqrt{n}$ 的点个数一定小于 $\sqrt{n}$。

发现度数小于等于 $\sqrt{n}$ 的结点直接暴力操作，每次的时间复杂度也就 $O(\sqrt{n})$。

于是我们不难想到：

拼盘！启动！

预处理出每个结点邻接的度数大于 $\sqrt n$ 的点有哪些，时间复杂度 $O(n\sqrt n)$。

关于度数小于等于 $\sqrt n$ 的结点，我们直接暴力更新，顺便记录下每个被更新节点的最后一次被更新时间，这样做每次更新的时间复杂度为 $O(\sqrt n)$。

关于度数大于 $\sqrt n$ 的结点 $u$，~~根据根号分治拼盘原则，~~我们参考上面想到的打标记思想以及线段树的懒标记思想，遍历一遍与 $u$ 邻接的所有度数大于 $\sqrt n$ 的结点去更新 $a_u$，然后对 $u$ 标记上最后一次关于它的操作时间以及最后一次操作时的 $a_u$。

遍历一遍与 $u$ 邻接的所有度数大于 $\sqrt n$ 的结点以更新 $a_u$ 所需的时间复杂度为 $O(\sqrt n)$，打标记时间复杂度为 $O(1)$。

于是最终的时间复杂度就是 $O(n\sqrt n)$。

---

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;

int n,m,q,c[N],fir[N],cnt,in[N],t[N],lt[N],lc[N];
bool w[N];
vector<int>v[N];

struct E{ int nex,to;}e[N<<1];

void add(int,int),upd(int);

signed main(){
    scanf("%d%d%d",&n,&m,&q); int sq=sqrt(n);
    for(int i=1,a,b;i<=m;++i) scanf("%d%d",&a,&b),add(a,b);
    for(int i=1;i<=n;++i) c[i]=i,w[i]=in[i]>sq?1:0;
    for(int i=1;i<=n;++i){
        if(!w[i]) continue;
        for(int j=fir[i];j;j=e[j].nex){
            int to=e[j].to;
            v[to].push_back(i);
        }
    }
    for(int u,i=1;i<=q;++i){
        scanf("%d",&u);
        upd(u);
        if(!w[u]){
            for(int j=fir[u];j;j=e[j].nex){
                int v=e[j].to;
                c[v]=c[u],t[v]=i;
            }
            continue;
        }
        lt[u]=i,lc[u]=c[u];
    }
    for(int i=1;i<=n;++i) upd(i),printf("%d ",c[i]);
    return 0;
}
void add(int a,int b){ e[++cnt].nex=fir[a],e[cnt].to=b,fir[a]=cnt,e[++cnt].nex=fir[b],e[cnt].to=a,fir[b]=cnt,++in[a],++in[b];}
void upd(int no){ for(auto i:v[no]) if(lt[i]>t[no]) c[no]=lc[i],t[no]=lt[i];}
```



---

## 作者：User_Unauthorized (赞：0)

考虑根号分治，出边集合大小超过 $\sqrt{M}$ 的节点一定不会超过 $\sqrt{M}$ 个。因此我们可以对于每个节点存储与其相邻的，出边集合大小超过 $\sqrt{M}$ 的节点集合，其大小一定不超过 $\sqrt{M}$。对于每次操作的节点 $u$，我们先通过遍历其存储的节点集合，找出当前其的颜色，然后再根据其出边集合大小进行判断，若其大小小于 $\sqrt{M}$ 则直接暴力进行遍历，否则不处理。

复杂度为 $\mathcal{O}(\left(Q + N\right) \sqrt{M} + M)$。

[Submission](https://atcoder.jp/contests/abc219/submissions/49424780).

---

## 作者：Xiphi (赞：0)

### AT_abc219_g

考虑对每个点的度根号分治。先记录每个点连着哪些度大于 $\sqrt m$ 的边，代码中使用 e 数组保存。然后考虑修改。若修改的点的度大于等于 $\sqrt m$，在此点打一个 lazytag，并记录修改的时间；若修改的点的度小于 $\sqrt m$，枚举他的所有相邻点暴力修改即可。

特别的，由于之前的 lazytag 是会对打后续标记或暴力修改有影响的，考虑 lazytag 只打在度大于 $\sqrt m$ 的点上，所以可以枚举当前修改的点连着哪些度大于 $\sqrt m$ 的边，然后取修改时间最晚的那个 lazytag 的值作为现在修改的点的值。特别的，这个值也有可能是其本身。

注意实现细节。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q;
pair<int,int> a[200005];
set<int> s[200005],e[200005];
pair<int,int> tag[200005];
int main(){
    cin>>n>>m>>q;
    for(int i=1;i<=n;++i) a[i]={-1,i},tag[i]={-1,-1};//必要的预处理。
    for(int i=1,x,y;i<=m;++i){
        cin>>x>>y;
        s[x].insert(y);
        s[y].insert(x);
    }
    for(int i=1;i<=n;++i){
    	for(set<int>::iterator it=s[i].begin();it!=s[i].end();++it){
    		if(s[*it].size()>sqrt(m)) e[i].insert(*it);
       }
    }
    int tim=0;
    while(q--){
        tim++;
        int u;
        cin>>u;
        for(set<int>::iterator it=e[u].begin();it!=e[u].end();++it){
            if(tag[*it].first>a[u].first) a[u]=tag[*it];
        }
        if(s[u].size()<=sqrt(m)){
            for(set<int>::iterator it=s[u].begin();it!=s[u].end();++it){
           		a[*it]={tim,a[u].second};
        	}
        }else{
            tag[u]={tim,a[u].second};
        }
    }
    for(int u=1;u<=n;++u){
        for(set<int>::iterator it=e[u].begin();it!=e[u].end();++it){
            if(tag[*it].first>a[u].first) a[u]=tag[*it];
        }
    }
    for(int i=1;i<=n;++i) cout<<a[i].second<<' ';
    return 0;
}

```

后续习题：

CF398D

---

## 作者：CrTsIr400 (赞：0)

[[ABC219G] Propagation](https://www.luogu.com.cn/problem/AT_abc219_g) 

考虑暴力更新，时间复杂度 $O(qn)$ 的，能否优化？因为这是一般情况的图，所以没办法用数据结构优化。

这个时候考虑一些比较神奇的算法：平衡规划。度数小直接暴力更新。

观察到一个点的度数太大不是好事，因为它更新时候耗时很大。那么是否可以**暂缓更新**？

形式化一下，若 $d[i]>T$ 则暂缓更新，但是记录标记 $b[i]$，时间戳 $t[i]$。此时我们需要知道这个标记上原来是啥颜色。此时应该知道它到底被哪个标记所覆盖了。

能否暴力遍历 $i$ 所有出度？不可行。

我们重新规划一下这张图。

设 $d[i]>T$ 的 $i$ 为**重点**，其余为**轻点**，重点个数不会超过 $O(\dfrac{m}{T})$ 个。

我们先要知道一个点的颜色。假设我已经知道了。

若修改了轻点，那么直接暴力更新其出度所有点（顺便更新时间戳），无论轻重。时间复杂度 $O(T)$。

若修改了重点，那么在重点上打上标记，暂缓更新。

---

那么我们怎么知道一个点的颜色呢？遍历一下一个点邻接的重点，找到时间戳最大的标记。此过程 $O(\dfrac{m}{T})$。

这个标记是否会被反复更新？其实是不会的，每次更新过程保证它是最新的。

于是这个题就做完了。具体看代码。不能更短了。

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define fo(i,a,b) for(I i(a),_ed(b);i<=_ed;++i)
using namespace std;using I=int;using LL=long long;using V=void;
const I N=2e5+10;
I at[N],bt[N],a[N],b[N],n,m,q,bl;
vector<I>e[N],f[N];bool u[N];
I gx(I x){I ans=a[x],ti=at[x];
	for(I&y:f[x])if(ti<bt[y])ti=bt[y],ans=b[y];
	return ans;}
I main(){ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m>>q;bl=sqrt(m*2);iota(a,a+n+1,0);
	fo(i,1,m){I x,y;cin>>x>>y;
		e[x].pb(y);e[y].pb(x);}
	fo(i,1,n)if(e[i].size()>bl)u[i]=1;
	fo(x,1,n)for(I&y:e[x])if(u[y])f[x].pb(y);
	fo(i,1,q){I x;cin>>x;
		a[x]=gx(x);at[x]=i;
		if(u[x])b[x]=a[x],bt[x]=i;
		else for(I&y:e[x])at[y]=i,a[y]=a[x];}
	fo(i,1,n)printf("%d ",gx(i));
	return 0;}
```



---

## 作者：Unordered_OIer (赞：0)

一个 $n$ 个点，$m$ 条边的图，一开始节点 $i$ 上的数是 $i$，$q$ 次操作，每次操作会把与节点 $x$ 直接相邻的所有节点的数改成 $x$ 上的数，问最终状态。

# Sol

考虑一个暴力显然是直接更新一个点连接的所有点的数。

对于随机数据来说暴力其实并不慢，甚至加一点玄学优化（例如不重复更新一个节点）可以做到只 T 两个点 qwq

考虑暴力慢的一个原因是可能有部分节点的 $deg$ 特别大，这样一次暴力更新一个节点的所有直接相邻节点就接近 $O(n)$ 了。这个图也没有连通，看上去不太能用数据结构干。

那么考虑根号分治，对于 $deg[u] \leq \sqrt m$ 的我们直接暴力更新；对于 $deg[u]>\sqrt m$ 的，我们可以在这个节点上打个 tag 表示它需要更新，同时记录时间戳，显然我们如果多次修改一个节点只关心最后一次修改它的时间。

具体实现的话，我们可以把所有的满足 $deg[u]>\sqrt m$ 的 $u$ 的连边取出来，然后询问答案的时候根据这张图里面所有的边记录的时间戳，与暴力的答案得到的时间戳（可能暴力没有答案 qwq）进行比对更新得到最终答案即可。

对于 $deg\leq\sqrt m$ 的修改是 $O(\sqrt m)$ 的，对于 $deg>\sqrt m$ 的修改是 $O(1)$ 的，查询时更新的节点数不会超过 $O(\sqrt m)$，那么整体就是 $O(q\sqrt m)$ 的。

```cpp
void UPD(int u){for(int v:es[u])if(tag[v].second>A[u].second)A[u]=tag[v];}
//根据所有deg>sqrt(m)的点更新有关它们的tag 
int main(){
  n=read(),m=read(),q=read();
  for(int i=1;i<=n;i++)a[i]=i,A[i]=make_pair(i,0),tag[i]=make_pair(0,0);
  for(int i=1,u,v;i<=m;i++){
    u=read(),v=read();
    add(u,v),add(v,u);
    ++dg[u],++dg[v];
  }
  int B=sqrt(m);
  for(int i=1;i<=n;i++)for(int v:to[i])if(dg[v]>=B)add2(i,v);
  //取出deg>sqrt(m)的点的边，实际上>和>=因为下面写的是<=所以不影响 
  for(int i=1;i<=q;i++)x[i]=read();
  for(int i=1;i<=q;i++){
    UPD(x[i]);
    if(dg[x[i]]<=B){//暴力更新 
      for(int v:to[x[i]])
        A[v]=make_pair(A[x[i]].first,i);
    }else{//打个tag 
      tag[x[i]]=make_pair(A[x[i]].first,i);
    }
  }
  for(int i=1;i<=n;i++){
    UPD(i);//和tag比较 
    cout<<A[i].first<<' ';
  }
  return 0;
}
```

---

## 作者：Saint_ying_xtf (赞：0)

这道题最暴力的方案，就是每一个询问，然后往外扩散，但如果是一个菊花图，那么就会被卡到 $O(qm)$。显然是不行的。

首先 $O(q)$ 这个是免不了的，只能从优化 $O(m)$ 入手。我们是不是可以根号分治？对于这个点连边小于 $\sqrt(n)$，我们可以直接把暴力去处理，然后如果大于，那么就不管了。

这里的不管，实际上类似线段树上的懒标记，等到要用的时候再来更新，正是线段树的精髓，也是这道题最重要，最巧妙的一点。

下面讲一下代码实现的流程。

先把所有的边数大于等于 $\sqrt n$ 的点预处理出来，最多也只有 $\sqrt n$ 个这样的点，时间和空间代价不大。

再预处理一下每一个点所能到达那些这些**重点**，存在 vector 里，重点，代表的是边数大于等于 $\sqrt n$ 的点。

我们在每一次操作之前先 update 一下这个点，可以理解为线段树中的 pushdown，将标记下沉，或者是将标记更新。

更新里面，我们只需要访问这个点预处理的 vector，也就是所连向的重点，最多只有 $\sqrt n$ 个。

如果这个点是轻点，也就是边数小于 $\sqrt n$ 的点，那么还需要 $\sqrt n$ 的暴力枚举转移。

到了最后，我们再把每一个点更新一遍。

所以，总的时间复杂度是 $O(m + q \sqrt n + n \sqrt n)$。

分别为，预处理，询问过程，最后更新。

AC 代码：[link](https://atcoder.jp/contests/abc219/submissions/51010714)。

---

