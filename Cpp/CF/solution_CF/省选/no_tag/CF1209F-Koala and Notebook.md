# Koala and Notebook

## 题目描述

考拉之国有 $m$ 条双向道路连接着 $n$ 座城市。道路按输入顺序编号为 $1$ 到 $m$。保证任意两座城市之间都可以互相到达。

考拉从第 $1$ 座城市出发旅行。每当他经过一条道路时，他会把这条道路的编号记在笔记本上。考拉不会在编号之间加空格，因此所有编号会被直接拼接成一个数字。

在出发前，考拉很好奇，对于所有可能的目的地，他最终写下的数字分别是多少。对于每一个目的地，考拉想知道他可能写下的最小数字是多少。

由于这些数字可能非常大，请输出它们对 $10^9+7$ 取模的结果。请注意，你需要输出最小可能数字的余数，而不是最小余数。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
11 10
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 11
```

### 输出

```
1
12
123
1234
12345
123456
1234567
12345678
123456789
345678826
```

## 样例 #2

### 输入

```
12 19
1 2
2 3
2 4
2 5
2 6
2 7
2 8
2 9
2 10
3 11
11 12
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
```

### 输出

```
1
12
13
14
15
16
17
18
19
1210
121011
```

## 样例 #3

### 输入

```
12 14
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 11
11 12
1 3
1 4
1 10
```

### 输出

```
1
12
13
134
1345
13456
1498
149
14
1410
141011
```

# 题解

## 作者：Alex_Wei (赞：15)

> [CF1209F Koala and Notebook](https://www.luogu.com.cn/problem/CF1209F)

无脑小丑做法。

不拆边，而是类似 [CF464E](https://www.luogu.com.cn/problem/CF464E) 用可持久化线段树维护从 $1$ 开始每个点的最短路，跑 dijkstra。

区间维护十进制数哈希值，比较两个 $dist$ 只需线段树上从右往左二分。时间复杂度 $\mathcal{O}(m\log ^ 2 m)$，注意线段树大小要开 $m\log_{10} m$ 即 $5\times 10 ^ 5$。

```cpp
#include <bits/stdc++.h>
using namespace std;
bool Mbe;
constexpr int N = 1e5 + 5;
constexpr int mod = 1e9 + 7;
constexpr int mod2 = 998244353;
constexpr int L = 5e5;
constexpr int K = L << 5;
int n, m, pw[L], pw2[L], lg[N];
vector<pair<int, int>> e[N];
int node, ls[K], rs[K];
struct dat {
  int val, val2, len;
  dat operator + (const dat &rhs) const {
    dat res = {rhs.val, rhs.val2, len + rhs.len};
    res.val = (res.val + 1ll * val * pw[rhs.len]) % mod;
    res.val2 = (res.val2 + 1ll * val2 * pw2[rhs.len]) % mod;
    return res;
  }
} val[K];
void modify(int pre, int &x, int l, int r, int ql, int qr, int v) {
  x = ++node, ls[x] = ls[pre], rs[x] = rs[pre];
  if(l == r) return val[x] = {v / pw[qr - l] % 10, v / pw[qr - l] % 10, 1}, void();
  int m = l + r >> 1;
  if(ql <= m) modify(ls[pre], ls[x], l, m, ql, qr, v);
  if(m < qr) modify(rs[pre], rs[x], m + 1, r, ql, qr, v);
  val[x] = val[ls[x]] + val[rs[x]];
}
dat query(int l, int r, int ql, int qr, int x) {
  if(!x || ql <= l && r <= qr) return val[x];
  int m = l + r >> 1;
  dat ans = {0, 0};
  if(ql <= m) ans = query(l, m, ql, qr, ls[x]);
  if(m < qr) ans = ans + query(m + 1, r, ql, qr, rs[x]);
  return ans;
}
int binary(int l, int r, int x, int y) {
  if(val[x].val == val[y].val && val[x].val2 == val[y].val2) return -1;
  if(l == r) return l;
  int m = l + r >> 1;
  int res = binary(l, m, ls[x], ls[y]);
  if(res != -1) return res;
  return binary(m + 1, r, rs[x], rs[y]);
}
int querybit(int p, int x) {
  int l = 1, r = L;
  while(l != r) {
    int m = l + r >> 1;
    if(p <= m) r = m, x = ls[x];
    else l = m + 1, x = rs[x];
  }
  return val[x].val;
}
struct dist {
  int id, R, len;
  bool operator > (const dist &rhs) const {
    if(len != rhs.len) return len > rhs.len;
    int v = binary(1, L, R, rhs.R);
    if(v == -1) return 0;
    return querybit(v, R) > querybit(v, rhs.R);
  }
} dis[N];
priority_queue<dist, vector<dist>, greater<dist>> q;
bool Med;
int main() {
  fprintf(stderr, "%.4lf\n", (&Mbe - &Med) / 1048576.0);
#ifdef ALEX_WEI
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
#endif
  cin >> n >> m;
  for(int i = 1; i <= m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    e[x].push_back({y, i});
    e[y].push_back({x, i});
  }
  for(int i = 10; i <= m; i++) lg[i] = lg[i / 10] + 1;
  for(int i = pw[0] = 1; i < L; i++) pw[i] = pw[i - 1] * 10ll % mod;
  for(int i = pw2[0] = 1; i < L; i++) pw2[i] = pw2[i - 1] * 10ll % mod2;
  q.push(dis[1] = {1, 0, 0});
  while(!q.empty()) {
    dist t = q.top();
    q.pop();
    int id = t.id, le = t.len;
    if(dis[id].R != t.R) continue;
    for(auto it : e[id]) {
      int tmpR, to = it.first, eid = it.second;
      modify(t.R, tmpR, 1, L, le + 1, le + lg[eid] + 1, eid);
      dist d = {to, tmpR, le + lg[eid] + 1};
      if(to != 1 && (!dis[to].R || dis[to] > d)) q.push(dis[to] = d);
    }
  }
  for(int i = 2; i <= n; i++) printf("%d\n", query(1, n, 1, dis[i].len, dis[i].R).val);
  return cerr << "Time: " << clock() << endl, 0;
}
/*
2022/6/17
start coding at 20:09
finish debugging at 21:06
*/
```

---

## 作者：xtx1092515503 (赞：11)

~~冬令营上碰到，不会，过来水题解~~

非常直观的思路就是将每条边$c$拆成$\lg c$个点，这样就可以保证每条边的边权都是一位数。


然后贪心的想，发现我们的最优路径一定经过的边的数量一定是**最少的**（因为最小的$x+1$位数一定大于最大的$x$位数）。那么就可以bfs爆搜了（bfs保证距离起始状态更近的状态会被先搜到），优先更新那些边权更小的边。

如果不出所料的话，你应该会WA10。

为什么呢？因为我们这样bfs是保证了距离较小的点先被访问，但并不能保证距离相等的点之间的关系。对于距离相等的点，我们应该同时查看它们的$0$权边，然后是$1$权边……最后是$9$权边。

如果按照我们之前的做法，我们则是先查看了某个点的所有边，然后是第二个点的……

这样的话，举个例子，有可能$5$号点本来可以被从$3$号节点来的一条权值为$5$的路径更新的，但是因为在队列里$2$在$3$前面，因此$5$号点就被$2$号点来的权值为$7$的路径更新了！如果$2$号点和$3$号点到$1$号点的距离都为$2$的话，则我们很明显是错了！明明人家$5$号点的距离可以达到$25$，但这样跑下来就是$27$了！

我们这时就需要把距离相同的点全都打包到一个```std::vector<int>```里面，一起更新。因此，我们bfs时应该用的数据结构是```std::queue<vector<int>>```。

除了这个“一起更新”的要求比较难注意到，其它部分还是很简单的~~

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,m,num[10],tot,res[2001000];
vector<int>v[2001000][10];
queue<vector<int> >q;
int main(){
	scanf("%d%d",&n,&m),tot=n,memset(res,-1,sizeof(res));
	for(int i=1,x,y;i<=m;i++){
		scanf("%d%d",&x,&y);
		int tmp=i,sz=0;
		while(tmp)num[++sz]=tmp%10,tmp/=10;
		if(sz==1)v[x][num[sz]].push_back(y);
		else v[x][num[sz]].push_back(tot+1),v[tot+sz-1][num[1]].push_back(y);
		for(int j=2;j<sz;j++)v[tot+j-1][num[sz-j+1]].push_back(tot+j);
		
		if(sz==1)v[y][num[sz]].push_back(x);
		else v[y][num[sz]].push_back(tot+sz-1),v[tot+1][num[1]].push_back(x);
		for(int j=2;j<sz;j++)v[tot+sz-j+1][num[sz-j+1]].push_back(tot+sz-j);
		
		tot+=sz;
	}
	q.push({1}),res[1]=0;
	while(!q.empty()){
		vector<int>x=q.front();q.pop();
//		for(int i=0;i<x.size();i++)printf("%d ",x[i]);puts("");
		for(int i=0;i<10;i++){
			vector<int>y;
			for(int j=0;j<x.size();j++)for(int k=0;k<v[x[j]][i].size();k++)if(res[v[x[j]][i][k]]==-1)res[v[x[j]][i][k]]=(10ll*res[x[j]]+i)%mod,y.push_back(v[x[j]][i][k]);
			if(!y.empty())q.push(y);
		}
	}
	for(int i=2;i<=n;i++)printf("%d\n",res[i]);
	return 0;
}
```


---

## 作者：_soul_ (赞：9)

将每一条边按 $10$ 进制位拆开，然后BFS 贪心，用优先队列维护即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
vector<int> son[2000010][10];
int n, m, cnt, vis[2000010];
int dis[2000010];
inline void addedge(int u, int v, int w) {
    while(w >= 10) {
        cnt++;
        son[cnt][w % 10].push_back(v);
        v = cnt;
        w /= 10;
    }
    son[u][w].push_back(v);
}
vector<vector<int> > q1, q2;
int main() {
    scanf("%d%d", &n, &m);
    cnt = n;
    for(int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        addedge(u, v, i);
        addedge(v, u, i);
    }
    dis[1] = 0;
    vector<int> tmp;
    tmp.push_back(1);
    q1.push_back(tmp);
    vis[1] = 1;
    while(1) {
        if(q1.empty()) break;
        for(auto x : q1) {
            for(int d = 0; d < 10; d++) {
                tmp.clear();
                for(auto i : x) {
                    for(auto v : son[i][d]) {
                        if(vis[v]) continue;
                        vis[v] = 1, dis[v] = (dis[i] * 10ll + d) % mod;
                        tmp.push_back(v);
                    }
                }
                if(!tmp.empty()) q2.push_back(tmp);
            }
        }
        q1 = q2;
        q2.clear();
    }
    for(int i = 2; i <= n; i++) printf("%d\n", dis[i]);
    return 0;
}
```


---

## 作者：皎月半洒花 (赞：5)

这题是真的有趣。虽然场上并没有去写（感觉写了也是不可能过的，因为细节比较多）。

一开始觉得「难道不是把出边 xjb 排个序就做完了嘛」。然后发现被叉了，心情郁闷(x

考虑如何比较「编号相连得到的十进制数」的大小，那必然是先比较位数，再从头开始比较权值。于是就有个特别强的建图技巧：拆边。考虑把一条编号为 $(\overline{a_1a_2\cdots a_k})_{10}$ 的边拆成两条有向链，链上的边的边权分别为 $a_1,a_2\cdots a_k$。

然后考虑进行类似分层图的 BFS。这个分层图的细节很丰富：

0、分层的目的是，控制遍历顺序，使得 BFS 的最优性也在当前问题中体现。即使得对于每个点，最先被遍历时一定是最短路。

1、首先要先忽略边权进行分层。

2、其次考虑如果存在多条出边，必然是走权最小的那条边。

3、只符合上面两条还是不对的。因为考虑如果某个点 $t$ 有两条入边 $e_1,e_2$ 满足 $val(e_1)<val(e_2)$，他们在 BFS 树上的深度相同，那么如果单纯按点来转移，可能会出现先走 $e_2$ 再走 $e_1$ 的情况，而此时 $t$ 已经被更新完毕就会导致出错。所以还要按照边权从 $0$ 到 $9$ 进行再分层。

可以知道这样做最后复杂度一定不会超过 $O(10\times m)$ 。

```[cpp
int ob ;
int cnt ;
int n, m ;
int arr[M] ;
int f[N] ;
int g[N] ;
int T ;
 
vector <int> q[N] ;
vector <int> E[N][10] ;
 
int main(){
    cin >> n >> m ;
    int x, y, z ; cnt = n ;
    for (int i = 1 ; i <= m ; ++ i){
        x = qr(), y = qr() ; ob = 0 ; z = i ;
        while (z) arr[++ ob] = z % 10, z /= 10 ; z = x ;
        for (int j = ob ; j > 1 ; -- j)
            E[x][arr[j]].push_back(++ cnt), x = cnt ;
        E[x][arr[1]].push_back(y) ;
        for (int j = ob ; j > 1 ; -- j)
            E[y][arr[j]].push_back(++ cnt), y = cnt ;
        E[y][arr[1]].push_back(z) ;
    }
    g[1] = T = 1 ;
    q[1].push_back(1) ;
    for (int d = 1 ; d <= T ; ++ d){
//        if (!q[d].size()) break ;
        for (z = 0 ; z < 10 ; ++ z){
            auto t = q[d].begin() ;
            while (t != q[d].end()){
                x = *t ;
                for (auto y : E[x][z]){
                    if (g[y]) continue ;
                    f[y] = (f[x] * 10ll + z) % P ;
                    g[y] = 1, q[T + 1].push_back(y) ;
                }
                ++ t ;
            }
            if (q[T + 1].size()) ++ T ;
        }
    }
    for (int i = 2 ; i <= n ; ++ i)
        printf("%d\n", f[i]) ; return 0 ;
}
```

# 

---

## 作者：wxh666 (赞：4)

这题细节很多，但是思路还是很好想的。

考虑贪心，先考虑 $m<10$ 的情况。

肯定是优先走经过边最少的情况。

经过边相同在按小到大排序。

就可以规避调 $mod$ 之后无法判断大小的的问题。


------------

拓展到 $m>10$ 的情况。

可以考虑把一条大于 $10$ 的边 $w$ 拆成 $\lg_{}{(w+1)}$ 个边，而且由于是双向边，所以每个边与其对应的反边可能不会相同，例如一条边 $10$ 会被拆成边 $1,0$ 与边 $0,1$，再使用 BFS 进行搜索。

但是，可能会出现如下图所示的情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/fm43gn5m.png)

从点 $1$ 开始遍历，如果按照点 $2$ 先遍历的顺序，点 $4$ 会先被点 $2$ 更新为 $11$ 而得不到正确的答案 $10$。

因此，我们需要进行分布 BFS，把目前所有到起点距离相等的点放在一起处理，按照这些点的所有出边的边权从小到大排序，就能得到正确的答案。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
struct wxh{
    int v,w;
};
vector<wxh>q[2000005];
int dcnt;
int n,m;
int x,y;
int dis[2000005];
int vis[2000005];
struct wxh666{
    int u,v,w;
    bool operator <(wxh666 x)const
    {
        return w>x.w;
    }
};
void BFS()
{
    queue<vector<int> >p;
    p.push({1});vis[1]=1;
    while(!p.empty())
    {
        priority_queue<wxh666>to;
        vector<int>k;
        vector<int>in;
        k=p.front();p.pop();
        for(auto i:k)
            for(auto j:q[i])
                if(!vis[j.v])
                    to.push(wxh666{i,j.v,j.w});
        int g=0;
        if(!to.empty())
            g=to.top().w;
        while(!to.empty())
        {
            wxh666 w=to.top();to.pop();
            if(vis[w.v]) continue;
            if(g!=w.w)
            {
                if(!in.empty())
                    p.push(in);
                in.clear();
                g=w.w;
            }
            vis[w.v]=1;
            dis[w.v]=(dis[w.u]*10+w.w)%mod;
            in.push_back(w.v);
        }
        if(!in.empty())
            p.push(in);
        in.clear();
    }
}
signed main()
{
	cin>>n>>m;
    dcnt=n;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        stack<int>s;
        queue<int>sq;
        int _=i;
        while(_) s.push(_%10),sq.push(_%10),_/=10;//拆边
        if(s.size()==1)
        {
            q[x].push_back(wxh{y,i});
            q[y].push_back(wxh{x,i});
        }
        else
        {
            q[x].push_back(wxh{++dcnt,s.top()});
            q[dcnt].push_back(wxh{x,sq.front()});
            s.pop();sq.pop();
            while(s.size()>1)
            {
                q[dcnt].push_back(wxh{dcnt+1,s.top()});
                q[dcnt+1].push_back(wxh{dcnt,sq.front()});
                dcnt++;s.pop();sq.pop();
            }
            q[y].push_back(wxh{dcnt,sq.front()});
            q[dcnt].push_back(wxh{y,s.top()});
            ++dcnt;s.pop();sq.pop();
        }
    }
    for(int i=1;i<=dcnt;i++)
        sort(q[i].begin(),q[i].end(),[&](auto x,auto y){return x.w<y.w;});
    BFS();
    for(int i=2;i<=n;i++)
        printf("%d\n",dis[i]);
	return 0;
}
```


---

## 作者：xcrr (赞：4)

这题做法不止一种，我这里讲下 Dijkstra 的做法。

首先拆边，每个边最多拓展 $\log_{10}m=5$ 个边。

距离点 1 相同的点，**同时扩展**同样的边，扩展出来的点同样距离点 1 相同。（这里距离指的是按照题面方法拼接出的数）。实现就是距离点 1 相同的点放在一个 vector 里，剩下搜索即可。

```cpp
const int mod=1e9+7;
int nn,n,m,T;
const int N=1e6+10;
vector<int>q[N],G[12][N];
bool vis[N];
int ans[N];
inline void solve(){
	cin>>n>>m;
	nn=n;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		cin>>u>>v;
		int t=0,t2=0;
		int c[7],b[7];
		int j=i;
		b[++t2]=u;
		while(j){c[++t]=j%10;j/=10;}
		for(int k=1;k<t;k++) b[++t2]=++n;
		b[++t2]=v;
		for(int k=1;k<=t;k++)
		G[c[t-k+1]][b[k]].push_back(b[k+1]);
		b[1]=v,b[t2]=u;
		for(int k=1;k<=t;k++)
		G[c[t-k+1]][b[k]].push_back(b[k+1]);
	}//以上拆边
	//同一个 T 的 q 存的是距离1同“距离”的点。
	q[++T].push_back(1);
	vis[1]=1;
	for(int i=1;i<=T;i++)
	{
		for(int j=0;j<=9;j++)
		{
			bool flag=0;
			for(auto u:q[i])
			for(auto v:G[j][u])
			{
				if(vis[v])continue;
				flag=vis[v]=1;
				q[T+1].push_back(v);
				ans[v]=(ans[u]*10+j)%mod;
			}
			if(flag)++T;//是否产生了更新。
		}
	}
	for(int i=2;i<=nn;i++)
	cout<<ans[i]<<'\n';
}
```

---

## 作者：cjZYZtcl (赞：2)

~~真正的无脑小丑做法~~

## 思路

不拆边，以编号数字串总长度作为路径长度，跑 Dijkstra。

同时建一颗字典树，对于一次成功的松弛，在字典树上添加一些新节点，同时更新字典树上的倍增数组。

如果松弛的时候遇到路径长度相同的情况，需要比较两个数字串的字典序，这个可以通过字典树上求 LCA 快速比较。

实现细节见代码。

[Code](https://codeforces.com/contest/1209/submission/221773359)

---

## 作者：complete_binary_tree (赞：0)

发现可以把边权拆成 $\lg V$ 条边权为单位的边，然后使用任意方法排序（计数/sort）然后 bfs 即可，第一个搜到的一定最小。

但是这个做法 WA on Test 10 了，考虑哪里假了。

发现有可能多个点的答案是一样的，它们在向外扩展时扩展出的顺序就不从小到大了。举个例子：

- 现在 $u_1 \to v$ 有一条边权为 $8$ 的边，$u_2 \to v$ 有一条边权为 $4$ 的边，而且 $u_1,u_2$ 的答案一样（设为 $x$）。

- 如果 $u_1$ 先被访问到，那么答案就会被更新为 $10x+8$，但是显然 $u_2$ 更新为 $10x+4$ 更优。

考虑怎么解决。可以把答案一样的所有点打包到 `vector` 里，然后集体转移即可。

细节上，空 `vector` 不要 `push` 进队列，否则会 MLE。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,mod=1e9+7;
vector<pair<int,int>>e[N<<4];
int n,m,cnt,dis[N<<4];
bool vis[N<<4];
queue<vector<pair<int,int>>>q;
vector<pair<int,int>>lin,lin2;
void bfs(){
	q.push(vector<pair<int,int>>({make_pair(1,0)}));
	vis[1]=1;
	while(q.size()){
		lin=q.front();q.pop();
		for(auto[u,val]:lin)dis[u]=val;
		for(int i=0;i<10;++i){
			for(auto[u,val]:lin){
				for(auto[v,w]:e[u]){
					if(w<i)continue;
					if(w>i)break;
					if(!vis[v]){
						vis[v]=1;
						lin2.push_back(make_pair(v,(10ll*val%mod+w)%mod));
					}
				}
			}
			if(lin2.size())q.push(lin2),lin2.clear();
		}
	}
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	cnt=n;
	for(int i=1;i<=m;++i){
		int u,v,u1,v1,w=i;
		cin>>u>>v;
		u1=u,v1=v;
		while(w>=10){
			e[++cnt].push_back({v,w%10});
			v=cnt,w/=10;
		}
		e[u].push_back({v,w});
		u=u1,v=v1,w=i;
		while(w>=10){
			e[++cnt].push_back({u,w%10});
			u=cnt,w/=10;
		}
		e[v].push_back({u,w});
	}
	for(int i=1;i<=cnt;++i)sort(e[i].begin(),e[i].end(),[](pair<int,int>a,pair<int,int>b){return a.second<b.second;});
	bfs();
	for(int i=2;i<=n;++i)cout<<dis[i]<<'\n';
	return 0;
} 
```

---

## 作者：daniEl_lElE (赞：0)

首先对所有的边拆分，拆成每条边上的数字均为 $0\sim 9$。

在这个图上到每个点的最短路显然需要满足经过的边数最少。考虑分层图。

将一层向下一层转移时，从位权的角度考虑不难发现第一关键字是前一层的顺序，第二关键字是经过的边上的数。按顺序转移即可。

总复杂度 $O(n\log^2n)$，瓶颈在于拆点后的排序。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int tot;
vector<pair<int,int>> vc[2000005];
int dist[2000005];
vector<int> tlev[2000005];
vector<int> plev[2000005];
int it[2000005];
int toplev;
void adde(int u,int v,int p){
	vector<int> tmp;
	while(p) tmp.push_back(p%10),p/=10;
	reverse(tmp.begin(),tmp.end());
	int lst=u;
	for(int i=0;i+1<tmp.size();i++){
		vc[lst].push_back(make_pair(tmp[i],++tot));
		lst=tot;
	}
	vc[lst].push_back(make_pair(tmp[tmp.size()-1],v));
}
signed main(){
	int n,m; cin>>n>>m;
	tot=n;
	memset(dist,-1,sizeof(dist));
	for(int i=1;i<=m;i++){
		int u,v; cin>>u>>v;
		adde(u,v,i);
		adde(v,u,i);
	}
	for(int i=1;i<=tot;i++) sort(vc[i].begin(),vc[i].end());
	toplev=1;
	tlev[1].push_back(1); dist[1]=0;
	while(toplev){
		int nlev=0;
		for(int i=1;i<=toplev;i++){
			for(int j=0;j<tlev[i].size();j++) it[j]=0;
			for(int k=0;k<10;k++){
				vector<int> tmpp;
				for(int j=0;j<tlev[i].size();j++){
					int v=tlev[i][j];
					while(it[j]!=vc[v].size()&&vc[v][it[j]].first==k){
						int to=vc[v][it[j]].second;
						if(dist[to]==-1){
							dist[to]=(dist[v]*10+k)%mod;
							tmpp.push_back(to);
						}
						it[j]++;
					}
				}
				if(tmpp.size()) plev[++nlev]=tmpp;
			}
		}
		toplev=nlev;
		for(int i=1;i<=toplev;i++) tlev[i]=plev[i];
	}
	for(int i=2;i<=n;i++){
		cout<<dist[i]<<"\n";
	}
	return 0;
}
```

---

## 作者：skyworldp (赞：0)

### 题意
给定一张无向图，边权为 $1 \sim m$。   
从 $1$ 号点出发到达 $2 \sim n$ 号点，要求出对于每个点 $i$，将从 $1 \sim i$ 所经过的边以字符串形式拼接，最后形成的数字最小，输出这个数字 $\bmod10^9+7$。
### 初见
模拟赛时最开始想把边拆成若干段 $1$，由于边长到了 $10^5$ 否定了拆边的做法，最后打了部分分~~润了~~。  
不过在CF的题没有部分分，所以直接看正解。
### 正解
这道题的难点就是在跑单源最短路的时候由于取模的原因不能获得正确的大小关系，导致最短路跑的不正确。  
正解还是拆边，把边的每一十进制位拆出来，这么拆之后，简单计算一下，点的总数是小于 $9\times10^5$ 的，可以接受。  
接下来就可以暴力 BFS 了。  
这样的话每次走过一条边，数字的长度一定增加 $1$，现在我们假设已经正确维护了点 $u$ 的答案，由点 $u$ 走向点 $v$ 的过程中我们优先选择走边权更小的（即从 $0 \sim 9$ 遍历），就可以维护正确的大小关系了。  
**注意：**  
队列内部的形状大概是这样的：二元组 $(i,j)$ 表示长度 $i$，末尾为 $j$ 的所有点的集合。   
 $(1,0),(1,1)...(1,9),(2,0),(2,1)...(2,9)...$  
显然要注意的是如果当前枚举的 $(i+1,j)$ 并没有更新点，那么队列末尾就不需要 push。   
具体实现看代码。
### 代码:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
const int mod = 1000000007;
const int M = 900000;
int tot; // 节点数
int dis[M];
bool vis[M];
vector<int> e[M][10], q[M]; // e[i][num]:i的边权为num（拆后）的边
int it = 0;                 // 队列指针
int n, m;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    tot = n;
    for (int i = 1, u, v; i <= m; i++)
    {
        cin >> u >> v;
        int tmp = i, pre = v; 
        // u->a->b->c->d->...z->v 数位分解，从z开始向u
        while (tmp > 9)
            e[++tot][tmp % 10].pb(pre), pre = tot, tmp /= 10;
        e[u][tmp].pb(pre);
        tmp = i, pre = u;
        while (tmp > 9)
            e[++tot][tmp % 10].pb(pre), pre = tot, tmp /= 10;
        e[v][tmp].pb(pre);
    }
    q[++it].pb(1);
    vis[1] = 1;
    for (int i = 1; i <= it; i++)
        for (int j = 0; j < 10; j++)
        {
            bool f = 0;
            for (auto k : q[i])        // 当前长度为i的所有点
                for (auto v : e[k][j]) // 走最小的点，看看能不能走
                    if (!vis[v])
                    {
                        vis[v] = 1;
                        q[it + 1].pb(v);
                        f = 1;
                        dis[v] = (1ll * dis[k] * 10 + j) % mod;
                    }
            if (f)
                it++; // 证明当前是有往it+1里面放东西的，所以队列右端点右移
        }
    for (int i = 2; i <= n; i++)
        cout << dis[i] << '\n';
    return 0;
}
```

---

## 作者：MiRaciss (赞：0)

## 题目链接
[link.](https://www.luogu.com.cn/problem/CF1209F)

## 题解
可以发现，如果每一条边的编号位数相同就会很好处理，又可以发现走过一条编号为 1 的边和一条编号为 2 的边的贡献与走过一条编号为 12 的边相等，所以我们考虑拆边，将边按照十进制进行拆分。因为每条边只有一位了，所以最短的距离肯定走最少的边，所以我们把问题转换成了最短路问题。

然后因为如果存在多条出边，我们要走权最小的那条边，所以可以将出边进行 0~9 分类。

然还有一个问题，上文提到过走 1 再走 2 和走 12 是等价的，但如果出现下图的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/vkwahd5a.png)

从 $s$ 出发，我们有可能会选择走 1->2->3->4 的道路到达 $t$ ，但显然这不是最近的道路。

为了避免这种情况，我们需要在每次搜索时让层数相同的一起扩展。

但还有一个问题：

![](https://cdn.luogu.com.cn/upload/image_hosting/mjkb7xvo.png)

如图，将第三层的放在一起扩展，但可能会出现 $2< 3$ ，所以我先从下面扩展的终点的情况。所以其实我们扩展并不是将同一层的放一起，而是将目前为止价值相同的放在一起，并按照下一条边的权值从小到大进行扩展。

### code
````cpp
#include<bits/stdc++.h>
using namespace std;
#define db double

int n,k,ans=0;
struct zz{
	int x,y;	
}a[15],b[1005];
vector<int> v[15][1005];
bool cmp(zz x,zz y){
	if(x.x==y.x) return x.y<y.y;
	return x.x<y.x; 
}

bool Cheak(zz x,zz y,zz yy){
	if(x.x==y.x&&x.x==yy.x) return 1;
	if(x.x==y.x&&x.x==yy.x) return 1;
	return (x.y-y.y)*(x.x-yy.x)==(x.y-yy.y)*(x.x-y.x);
}

void Fk(){
	for(int i=1;i<=k;i++) for(int j=1;j<=n;j++) for(int l=1;l<=n;l++) if(j!=l&&Cheak(a[i],b[j],b[l]))
		if(min(a[i].x,b[j].x)<=b[l].x&&b[l].x<=max(a[i].x,b[j].x)&&min(a[i].y,b[j].y)<=b[l].y&&b[l].y<=max(a[i].y,b[j].y)) 
			v[i][j].push_back(l);
}

bool f[15];
int t[15],sum=0;
bool vis[1005];


bool DFS(int x){
	if(sum==k+1) return 0;
	int now=t[sum++];
	for(auto y:v[now][x]) if(!vis[y]&&!DFS(y)) return 0;
	vis[x]=1;
	return 1;
}

bool Check(int x,int tot){
	if(tot==k+1){ memset(vis,0,sizeof vis);sum=1;return DFS(x); }
	for(int i=1;i<=k;i++) if(!f[i]){
		f[i]=1;t[tot]=i;
		if(Check(x,tot+1)) return 1;
		f[i]=0;
	}
	return 0;
}

int main(){
	cin>>k>>n;
	for(int i=1;i<=k;i++) scanf("%d%d",&a[i].x,&a[i].y);
	for(int i=1;i<=n;i++) scanf("%d%d",&b[i].x,&b[i].y);
	Fk();
	for(int i=1;i<=n;i++){
		ans+=Check(i,1);
		memset(f,0,sizeof f);
	}
	cout<<ans<<endl;
	return 0;
}
```











---

