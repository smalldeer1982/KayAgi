# [ABC409F] Connecting Points

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc409/tasks/abc409_f

在二维平面上有一个初始为 $N$ 个顶点、$0$ 条边的图 $G$。顶点编号为 $1$ 到 $N$，顶点 $i$ 的坐标为 $(x_i,y_i)$。

对于图 $G$ 中的顶点 $u$ 和 $v$，定义它们之间的距离 $d(u,v)$ 为曼哈顿距离：$d(u,v)=|x_u-x_v|+|y_u-y_v|$。

对于图 $G$ 的两个连通分量 $A$ 和 $B$，设它们的顶点集合分别为 $V(A)$ 和 $V(B)$，则定义 $A$ 和 $B$ 之间的距离 $d(A,B)$ 为：$d(A,B)=\min\lbrace d(u,v) \mid u \in V(A), v \in V(B) \rbrace$。

请处理以下 $Q$ 个查询，查询分为三种类型：

1. `1 a b`：设当前图 $G$ 的顶点数为 $n$，在坐标 $(a,b)$ 处新增顶点 $n+1$，并将其加入图 $G$。
2. `2`：设当前图 $G$ 的顶点数为 $n$，连通分量数为 $m$：
   - 若 $m=1$，输出 `-1`。
   - 若 $m \geq 2$，找到距离最小的连通分量对，并将它们合并（即在这些连通分量之间添加边，使得所有距离等于最小值的顶点对相连），然后输出该最小距离值。
3. `3 u v`：若顶点 $u$ 和 $v$ 属于同一连通分量，输出 `Yes`；否则输出 `No`。

## 说明/提示

### 约束条件

- $2 \leq N \leq 1500$
- $1 \leq Q \leq 1500$
- $0 \leq x_i, y_i \leq 10^9$
- 对于类型 `1` 的查询，$0 \leq a, b \leq 10^9$
- 对于类型 `3` 的查询，设处理该查询前图 $G$ 的顶点数为 $n$，则 $1 \leq u < v \leq n$
- 输入均为整数

### 样例解释 1

初始时，顶点 $1,2,3,4$ 的坐标分别为 $(3,4),(3,3),(7,3),(2,2)$。  
- 第 1 个查询：顶点 $1$ 和 $2$ 不连通，输出 `No`。  
- 第 2 个查询：有 4 个连通分量（$\lbrace 1 \rbrace, \lbrace 2 \rbrace, \lbrace 3 \rbrace, \lbrace 4 \rbrace$），最小距离为 $1$（顶点 $1$ 和 $2$ 之间），合并后输出 $1$。  
- 第 3 个查询：顶点 $1$ 和 $2$ 已连通，输出 `Yes`。  
- 第 4 个查询：新增顶点 $5$，坐标为 $(6,4)$。  
- 第 5 个查询：最小距离为 $2$（顶点 $2$ 和 $4$、顶点 $3$ 和 $5$ 之间），合并后输出 $2$。  
- 第 6 个查询：顶点 $2$ 和 $5$ 不连通，输出 `No`。  
- 第 7 个查询：最小距离为 $3$（顶点 $1$ 和 $5$ 之间），合并后输出 $3$。  
- 第 8 个查询：顶点 $2$ 和 $5$ 已连通，输出 `Yes`。  
- 第 9 个查询：所有顶点连通，输出 `-1`。  
- 第 10 个查询：新增顶点 $6$，坐标为 $(2,2)$。  
- 第 11 个查询：最小距离为 $0$（顶点 $4$ 和 $6$ 之间），合并后输出 $0$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4 11
3 4
3 3
7 3
2 2
3 1 2
2
3 1 2
1 6 4
2
3 2 5
2
3 2 5
2
1 2 2
2```

### 输出

```
No
1
Yes
2
No
3
Yes
-1
0```

# 题解

## 作者：chenxi2009 (赞：2)

## 思路
看到合并肯定有个并查集。难点在于如何高效进行操作二。

由于每次要取出当前距离最小的一批点对，所以考虑维护点对的小根堆，排序关键字是点对距离。进行操作一时把新点和所有旧点构成的对推入堆中，进行操作二时持续取出堆顶的点对合并直至出现不同的距离即可。时间复杂度 $O((N+Q)^2\log(N+Q))$。

控诉卡常题，用 `set`、`multiset`、`map` 的做法基本都会超时，只能使用 `priority_queue`。
## 代码
```cpp
#include<bits/stdc++.h>
#define gc getchar
#define eb emplace_back
#define ef emplace_front
#define ep emplace
#ifndef DEBUG
#define debug
#endif
using namespace std;
template<typename T>void read(T &x){x = 0;int f = 1;char c = gc();while(!isdigit(c)){if(c == '-') f = -1;c = gc();}while(isdigit(c)) x = x * 10 + c - '0',c = gc();x *= f;}
const int N = 4000;
int n,m,op,u,v,f[N],cnt,x[N],y[N],ans;
priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,greater<tuple<int,int,int>>>q;
int find(int x){return x == f[x] ? x : f[x] = find(f[x]);}
int main(){
  read(n),read(m);
  for(int i = 1;i < N;i ++) f[i] = i;
  for(int i = 1;i <= n;i ++) read(x[i]),read(y[i]);
  for(int i = 1;i < n;i ++) for(int j = i + 1;j <= n;j ++) 
    q.ep(abs(x[i] - x[j]) + abs(y[i] - y[j]),i,j);//每个点对都推入优先队列
  for(int i = 1;i <= m;i ++){
    read(op);
    if(op == 1){
      read(u),read(v),x[++ n] = u,y[n] = v;//记录新点
      for(int i = 1;i < n;i ++) q.ep(abs(x[i] - u) + abs(y[i] - v),i,n);//所有新点对推入优先队列
    }
    else if(op == 2){
      ans = -1;//记录要输出的 k 值
      while(q.size()){
        auto [a,b,c] = q.top();
        if(~ans && (ans ^ a)) break;//出现了距离 >k 的点对，不再合并
        q.pop();
        if(find(b) ^ find(c)) f[find(b)] = find(c),ans = a;//如果是未合并的点对，合并并记录 k=a
      }
      printf("%d\n",ans);
    }
    else{
      read(u),read(v);
      if(find(u) == find(v)) printf("Yes\n");
      else printf("No\n");
    }
  }
  return 0;
}
```
[submission](https://atcoder.jp/contests/abc409/submissions/66611416)\
[map 离散死亡回放](https://atcoder.jp/contests/abc409/submissions/66550049)

---

## 作者：littlebug (赞：1)

第一次知道 priority 比 set 快这么多。这就是多打 AT 的好处吗！

## Solution

注意到 $n,q \le 1500$，所以考虑复杂度 $O((n+q)^2 \log (n+q))$ 的暴力。

直接按照题目中的操作，建一个小根堆和一个 dsu，小根堆维护所有点两两之间的距离以及这两个点的编号，dsu 维护连通块。

具体地：

- 对于操作一，新建点 $i$，再把这个点向 $1 \sim i-1$ 都连一条边并塞到小根堆里面即可。

- 对于操作二，首先 $m$ 是很好维护的，输出 $-1$ 的情况可以直接判（这样更快一些，不过不维护 $m$ 也可以）；对于 $m>1$ 的情况，一直弹出堆顶直到堆顶表示的两个点不在同一个连通块内，记录这两点之间的距离 $k$，然后把堆里面所有距离 $=k$ 的点对全部在 dsu 上合并。\
  †这里有一个小优化，可以在 $m=1$ 的时候直接清空队列，会优化一点常数。

- 对于操作三，显然是 dsu 的基本操作。

## Code

```cpp
int n,m,q;
pii a[N];
const int B=1e5;

il int dist(int u,int v){return abs(a[u].st-a[v].st)+abs(a[u].nd-a[v].nd);}
il int calc(int u,int v){return max(u,v)*B+min(u,v);}

prque(pii,greater) que;

struct __dsu
{
    int n,fa[N],rk[N];

    il void init() {rep(i,0,n+1) fa[i]=i,rk[i]=0;}
    il void init(int _n) {n=_n,init();}

    il int find(int x) {return x==fa[x] ? fa[x] : fa[x]=find(fa[x]);}
    il bool merge(int x,int y)
    {
        x=find(x),y=find(y);
        if(x==y) return 1;
        if(rk[x]>rk[y]) fa[y]=x;
        else if(rk[y]>rk[x]) fa[x]=y;
        else ++rk[x],fa[y]=x;
        return 0;
    }
} dsu;

il void solve()
{
    read(n,q);
    m=n;

    dsu.init(n+q+1);

    int cnt=0,x,y;
    rep(i,1,n)
    {
        read(x,y),a[++cnt]={x,y};
        rep(j,1,cnt-1) que.emplace(mp(dist(i,j),calc(i,j)));
    }

    int op,u,v;
    while(q--)
    {
        read(op);

        if(op==1)
        {
            read(x,y),a[++cnt]={x,y};
            rep(j,1,cnt-1) que.emplace(mp(dist(cnt,j),calc(cnt,j)));
            ++m;
        }

        else if(op==2)
        {
            if(m==1) {clr(que),write(-1ll,'\n'); continue;}

            while(!que.empty() && dsu.merge(que.top().nd/B,que.top().nd%B)) que.pop();
            --m;
            int k=que.top().st;
            while(!que.empty() && que.top().st==k) dsu.merge(que.top().nd/B,que.top().nd%B) || --m,que.pop();

            write(k,'\n');

            if(m==1) clr(que);
        }

        else
        {
            read(u,v);
            if(dsu.find(u)==dsu.find(v)) write((string)"Yes",'\n');
            else write((string)"No",'\n');
        }
    }
}
```

---

华风夏韵，洛水天依！

---

## 作者：Tang_chao (赞：1)

你们那套优先队列做法太高级了，在下高攀不起。那么接下来你将看到：

## ABC409F 最~~无脑~~朴素解法

### 引入

先要会写[平面内最近点对](https://www.luogu.com.cn/problem/solution/P1429)。

使用**分治法**和**归并排序**，时间复杂度 $O(N\log N)$。

### 分析

记 $N=n+q$。

回到原问题。考虑用并查集维护连通块。

操作 $1$、$3$ 只需并查集简单维护即可。操作 $2$ 这么做：

首先，记 $grp_i$ 为并查集中 $i$ 在哪个块。显然，$grp_i$ 相等的点对不能更新答案。

其次，需要维护所有最近点对来更新。  
类比一下，对于 $\operatorname{solve}(l,r)$ 跨两半的，只考虑 $[x_{mid}-d,x_{mid}+d]$ 中的点，其中 $d$ 为两个子问题的答案（**因为需要所有点对，一定要取上两端**qwq）

考虑记 $\operatorname{res}(l,r)$ 为 $[l,r]$ 中所有最优点对，为 ```vector``` 类型。顺手更新即可。每次操作 $2$ 要在并查集上连接所有最近点对。

$$

$$

一共有 $q$ 次操作 $2$，会超时或爆空间吗？

时间复杂度为 $O(qN\log N)$，就是跑 $q$ 次归并。和优先队列的做法差不多。

空间复杂度为 $O(N^2)$，证明如下。

---

**不考虑重合**

对于 $\operatorname{res}(l,r)$，其大小最多为 $r-l+1$。  
因为：对于任意一个点集，连接最近点对的边集最多是一个环，长度最多就是点数。

考虑做完 $\operatorname{res}(l,r)$ 后清空两个子任务的 ```vector```。那么任意时刻最多存在 $O(N)$ 条边，所有操作的复杂度为 $O(qN)$。

---
**考虑重合**

如果一次操作 $2$ 时，有 $a$ 个点重合，那么会有 $a^2$ 条边。但是在下一轮它们就会被缩成一个点，意味着**这个 $a^2$ 最多被贡献一次**！

正式地，考虑把 $N$ 个点划分成 $K$ 个部分，第 $i$ 个部分的大小为 $sz_i$，并且这里面的点都重合。  
如果只考虑重合的，所有操作的复杂度为：$O(\sum_{i=1}^K sz_i^2)$，其中 $\sum_{i=1}^K sz_i=N$。这玩意是 $O(N^2)$ 的。

---

所以空间复杂度为 $O(qN+N^2)=O(N^2)$。而且很难跑满。

### 代码

坑点：

1. 注意每个 $\operatorname{res}(l,r)$ 都是一个独立的 ```vector```，不然更新答案时会挂。  
2. 归并写法中，区间正中间的 $x$ 不能直接访问 $x_{mid}$，因为这是已经被 $y$ 影响过的排序结果。可以先复制一份按 $x$ 排序的版本。  
3. 新点要初始化并查集。

[AC Code](https://atcoder.jp/contests/abc409/submissions/66647064)

他甚至特地罚了一发来测复杂度，太感动了，快给他点个赞吧。

---

## 作者：Union_Find (赞：1)

比较简单的题，毕竟 $O(n^2\log n^2)$ 可过。这里认为 $n,q$ 同阶。

不难注意到，这里有至多 $n+q$ 个点，所以在不考虑同一连通块不连的情况下，至多有 $O(n^2)$ 条边，我只要可以快速找到每次 $2$ 操作连接的边即可暴力并查集。

实际上，如果我们把剩下的边按照长度排序，然后依次判断两端是否在连通块内。如果不在，说明这次操作的 $k$ 就是这个长度。如果在，就丢掉这条边，后面一定用不到。

至于操作 $1$，直接暴力加边即可。

排序直接用优先队列即可，时间复杂度是 $O(n^2\log n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define il inline
#define N 5005
il int rd(){
	int s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
struct Point{
	int x, y;
}p[N];
int n, m, fa[N], op, u, v;
int find(int x){return x == fa[x] ? x : fa[x] = find(fa[x]);}
il int dis(Point a, Point b){return abs(a.x - b.x) + abs(a.y - b.y);}
priority_queue <pair<int, pair<int, int> > > q;
signed main(){
	n = rd(), m = rd();
	for (int i = 1; i <= n + m; i++) fa[i] = i;
	for (int i = 1; i <= n; i++){
		p[i] = Point{rd(), rd()};
		for (int j = 1; j < i; j++) q.push({-dis(p[i], p[j]), {i, j}});
	}
	while (m--){
		op = rd();
		if (op == 1){
			p[++n] = Point{rd(), rd()};
			for (int i = 1; i < n; i++) q.push({-dis(p[i], p[n]), {i, n}});
		}
		else if (op == 2){
			int k = -1;
			while (!q.empty()){
				int u = q.top().second.first, v = q.top().second.second;
				if (find(u) == find(v)) q.pop();
				else if (k == -1) k = dis(p[u], p[v]), fa[find(u)] = find(v), q.pop();
				else if (k == dis(p[u], p[v])) fa[find(u)] = find(v), q.pop();
				else break;
			}
			printf ("%lld\n", k);
		}
		else{
			u = rd(), v = rd();
			puts(find(u) == find(v) ? "Yes" : "No");
		}
	}
	return 0;
}

```

---

## 作者：RainWetPeopleStart (赞：0)

疑似是爆标了。

首先维护无向图连通性显然可以并查集。

下文定义 $bel_i$ 表示 $i$ 所属的连通块，$mindis$ 表示 $2$ 操作求出的最小值。

重点在 $2$ 操作上，一个想法是对每一个连通块 $S$，维护 $dis_{i}=\min\limits_{j\in S}d(i,j)$，加点时可以直接枚举 $j$ 更新 $dis$，合并两个连通块时就对 $dis$ 对位取 $\min$ 即可，因为有效的合并次数只有 $O(n+q)$ 次，所以这一部分复杂度有保证。

对于求最小值的部分，直接对合法的 $dis$ 取 $\min$ 是单次 $O((n+q)^2)$ 的，所以要对连通块 $S$ 维护一个 $mn$ 表示 $\min\limits_{bel_j\neq S} dis_j$，对于 $mn$ 的更新，加点时相当于对每个连通块的 $mn$ 进行 checkmin，合并时直接重新求 $mn$ 即可。

这样，求最小值就等价于求 $mn$ 的最小值，直接暴力是可接受的。

对于加边的部分，参考 Boruvka 算法的过程，找到所有满足 $mn=mindis$ 的连通块 $S$，然后取出所有 $dis_j=mindis$ 的点，合并 $bel_j$ 和 $S$ 即可。

取出所有 $dis_j=mindis$ 的点可以暴力，虽然付出了 $O(n+q)$ 的代价，但是会让连通块数减至少 $1$，所以这一部分复杂度是对的。

对于并查集的部分，你可能需要做 $O((n+q)^2)$ 次 find 操作，但因为只有路径压缩的并查集复杂度是 $O(m\log_{1+\frac{m}{n}}n)$（对合并进行优化显然不劣于这个），本题中 $n=O(n+q)$，$m=O((n+q)^2)$，故 $\log$ 的部分实际是 $O(1)$ 的，总复杂度 $O((n+q)^2)$。

参考实现：


```cpp
#include<bits/stdc++.h>
#define ll long long
#define vi vector<int>
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
using namespace std;
const int N=3500;
int n,q;
int w[N];
int cnt[N];
ll ans=0;
int fa[N];
int fd(int x){
    if(x==fa[x]) return x;
    return fa[x]=fd(fa[x]);
}
int x[N],y[N];
int to[N][N],mn[N];
int d(int i,int j){
    return abs(x[i]-x[j])+abs(y[i]-y[j]);
}
int md[N];
void add(int a,int b){
    x[n+1]=a,y[n+1]=b;
    memset(md,0x7f,sizeof(md));
    for(int i=1;i<=n;i++){
        md[fd(i)]=min(md[fd(i)],d(n+1,i));
    }
    for(int i=1;i<=n;i++){
        if(md[i]<2e9){
            to[i][n+1]=md[i];mn[i]=min(mn[i],md[i]);
            to[n+1][i]=md[i];mn[n+1]=min(mn[n+1],md[i]);
        }
    }
}
void mg(int a,int b){
    a=fd(a),b=fd(b);
    if(a==b) return ;
    for(int i=1;i<=n;i++) to[b][i]=min(to[b][i],to[a][i]);
    fa[a]=b;
    mn[b]=0x7f7f7f7f;
    for(int i=1;i<=n;i++) if(fd(i)!=fd(b)) mn[b]=min(mn[b],to[b][i]);
}
bool chk(int a,int b){
    return (fd(a)==fd(b));
}
void slv(){
    cin>>n>>q;
    memset(to,0x7f,sizeof(to));
    memset(mn,0x7f,sizeof(mn));
    for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
    for(int i=1;i<=n+q;i++) fa[i]=i;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i!=j){
                to[i][j]=d(i,j);
                mn[i]=min(mn[i],d(i,j));
            }
        }
    }
    for(int i=1;i<=q;i++){
        int op,a,b;
        cin>>op;
        if(op==1){
            cin>>a>>b;
            add(a,b);n++;
        }else if(op==2){
            int mind=0x7f7f7f7f;
            for(int j=1;j<=n;j++){
                if(fd(j)!=j) continue;
                mind=min(mind,mn[j]);
            }
            if(mind>2e9) mind=-1;
            cout<<mind<<endl;
            for(int j=1;j<=n;j++){
                if(fd(j)!=j) continue;
                if(mn[j]==mind) 
                for(int k=1;k<=n;k++){
                    if(fd(j)==fd(k)) continue;
                    if(to[j][k]==mind) mg(j,k);
                }
            }
        }else{
            cin>>a>>b;
            if(chk(a,b)) cout<<"Yes"<<endl;
            else cout<<"No"<<endl;
        }
        //for(int j=1;j<=n;j++) cout<<mn[j]<<' ';cout<<endl;
    }
}
int main(){
    int t=1;//cin>>t;
    while(t--) slv();
    return 0;
}
```

---

## 作者：xxgirlxx (赞：0)

敢写就敢 A 系列。

用优先队列维护目前所有可连边的最小值并用并查集维护连通块。

然后就没有然后了。

输入一个点就跟之前的所有点能连的边加入优先队列。

问边就从队头开始取一直到两点不相连，输出值后把所有能连的连上。

问是否连通用并查集一查就完事。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,Q,x[30010],y[30010],fa[30010],cnt;
struct node{
	int u,v,vl;
	bool operator<(const node& o)const{
		return vl>o.vl;
	}
};
priority_queue<node>q;
int find(int z){
	if(z==fa[z])return z;
	return fa[z]=find(fa[z]);
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>Q;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
		for(int j=1;j<i;j++){
			q.push({j,i,abs(x[i]-x[j])+abs(y[i]-y[j])});
		}
	}
	for(int i=1;i<=n;i++)fa[i]=i;
	cnt=n;
	for(int i=1;i<=Q;i++){
		int opt,a,b;
		cin>>opt;
		if(opt==1){
			n++;
			cin>>x[n]>>y[n];
			for(int j=1;j<n;j++){
				q.push({j,n,abs(x[j]-x[n])+abs(y[j]-y[n])});
			}
			fa[n]=n;
			cnt++;
		}
		else if(opt==2){
			if(cnt==1)cout<<"-1\n";
			else{
				node tmp;
				while(1){
					int U=find(q.top().u),V=find(q.top().v);
					if(U!=V){
						tmp=q.top();
						break;
					}
					q.pop();
				} 
				cout<<tmp.vl<<"\n";
				while(q.top().vl==tmp.vl&&!q.empty()){
					int U=find(q.top().u),V=find(q.top().v);
					if(U!=V){
						cnt--;
						fa[V]=U;
					}
					q.pop();
				}
			}
		}
		else{
			cin>>a>>b;
			int U=find(a),V=find(b);
			if(U==V)cout<<"Yes\n";
			else cout<<"No\n";
		}
	}
	return 0;
}
```

---

## 作者：Ryanhao (赞：0)

# [F. 连接点](https://atcoder.jp/contests/abc409/tasks/abc409_f)

## 思路

一眼并查集。

共 $3$ 个操作：

1. 增加一个点
2. 合并两个最近的集
3. 查询两个点是否在同一个集合内

~~赛时没看数据范围：$1\le n,q \le 1500$。~~

也就是说最多 $n+q \le 3000$ 个节点，于是先 $O(n^2)$ 暴力出任意两点的距离，塞进堆里面。以下是具体操作工艺：

1. 用 $O(n+q)$ 的时间把新点其他点的距离塞进堆里面。
2. 在堆里找出距离最近、没被连接的两个点，连接，把距离更近的点踢出堆里（可以证明它们已经被连上了）。这样，花在操作 $2$ 的时间最多是 $O\left[(n+q)^2\log_2 (n+q)^2\right]$。
3. 基础并查集。

总时间复杂度约为 $O\left[(n+q)^2\log_2 (n+q)^2\right]$（以上全部忽略反阿），$3000$ 可过。

## ACCode

```cpp
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
#include <cmath>
#include <cctype>
using namespace std;
int read();
void write(int x);
int disdis(int x1, int y1, int x2, int y2) {
  return abs(x2-x1)+abs(y2-y1);
}

const int maxn = 3e3+5;
int vat[maxn];
void init(int n) {
  for (int i = 1; i <= n; i++)
    vat[i] = i;
}
int find_root(int u) {
  if (u == vat[u]) return u;
  else return vat[u] = find_root(vat[u]);
}
void meege(int u, int v) {
  int ru = find_root(u);
  int rv = find_root(v);
  if (ru != rv) vat[ru] = rv;
}
struct node {
  int u,v; int dis;
  friend bool operator < (const node x, const node y) {
    return x.dis > y.dis;
  }
};
int X[maxn], Y[maxn];
priority_queue<node> q;

int main() {
  int n = read(), m = read();
  init(n+m);
  for (int i = 1; i <= n; i++) {
    X[i] = read(); Y[i] = read();
  }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j < i; j++)
      q.push(node{i,j,disdis(X[i],Y[i],X[j],Y[j])});
  while (m--) {
    int op = read();
    if (op == 1) {
      int x = read(), y = read();
      X[++n] = x; Y[n] = y;
      for (int i = n, j = 1; j < i; j++)
        q.push(node{i,j,disdis(X[i],Y[i],X[j],Y[j])});
    } else if (op == 2) {
      int ans = -1;
      while(!q.empty()) {
        int u = q.top().u;
        int v = q.top().v;
        int d = q.top().dis;
        q.pop();
        if (find_root(u) != find_root(v)) {
          ans = d; meege(u,v); 
          while(!q.empty() && q.top().dis == ans) {
            meege(q.top().u,q.top().v); q.pop();
            // 注意此处所有距离最近的点都要连起来
          }
          break;
        }
      }
      write(ans); putchar('\n');
    } else {
      int u = read(), v = read();
      if (find_root(u) == find_root(v)) puts("Yes");
      else                              puts("No");
    }
  }
  return 0;
}
// ---------------- Q R E A D ----------------
int read() {
  int re = 0, mk = 1;
  char c = getchar();
  while(!isdigit(c)) {
    if (c == '-') {
      mk = (~mk)+1;
    }
    c = getchar();
  }
  while(isdigit(c)) {
    re = (re<<1)+(re<<3)+(c^48);
    c = getchar();
  }
  return re*mk;
}
void write(int x) {
  if (x < 0) {
    putchar('-');
    x = (~x)+1;
  }
  if (x >= 10) {
    write(x/10);
  }
  putchar(x%10^48);
}
```

---

## 作者：Ivan422 (赞：0)

你说的对但是这题比较容易。比赛仅花 $20$ 分钟就啥都打完了。

### 题意

题意就是给你 $n$ 个平面上的点，一开始每一个点单独为一个块。有 $q$ 次操作，操作为：

1. 加点。
2. 合并最近且不在一个块内的点对。当有多个点时**全部**连上。
3. 问 $u$ 和 $v$ 是否在一个块内。

看数据范围，$n\leq1500$，$q\leq1500$。第一次见这么小的数据呢。


我们发现这个块感觉就是一个并查集，一开始 $fa_i=i$。然后合并点就是普通的合并，查询直接查。当没有**最近**和**加点**操作时这就是个模版。

### 解决加点问题

我们发现本质上直接增加一个点在并查集上没有多大影响。可以直接赋值一下 $fa_{n+1}=n+1$，然后 $n$ 增加一下。

### 解决最近问题

注意到最多点数为 $n+q=3000$。此时我们可以考虑建 $\frac{(n+q)(n+q-1)}{2}$ 个距离关系，复杂度可以接受。这时对于加点操作，我们就需要在加点后两两增加距离。

我们考虑查询。由于我们要维护**最近**点，那么可以考虑使用优先队列维护**可合并点对**。~~但是这样好像就是绿题了诶~~。接着我们发现每一次合并操作后都可能出现**已经处于一个集合内的点对在队列中**这种错误情况。对此，我们要在操作前先把这种情况的点对删掉，然后继续操作。

接着就是考虑取出一个距离 $k$，再暴力弹出队列中符合条件的点对。这时有小伙伴就会问了，当**队列中还有已经合并的点对**会怎么样？注意我们只需要求距离 $k$，取出这个 $k$ 的条件就是**当前点对可合并**，所以不会出问题。

### 代码

  然后我们就愉快写完了？哦不对忘记分析复杂度了。我们注意到一个点对最多进出一次，即复杂度为 $(n+q)\log_2(n+q)$，再加上处理点对复杂度，总复杂度为 $\mathcal O((n+q)^2+(n+q)\log_2(n+q))$。我们通过计算，这个东西应该是能过了，最慢点还不过半秒。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e3+10;
int n,fa[N],qs,mer;
struct dot{
	int x,y;
}a[N];
int dis(dot x,dot y){
	return abs(x.x-y.x)+abs(x.y-y.y);
}
int find(int x){
	return(fa[x]==x?x:fa[x]=find(fa[x]));
}
struct prp{
	int len,i,j;
};
bool operator<(prp x,prp y){
	return x.len>y.len;
}
void join(int x,int y){
	int zx=find(x),zy=find(y);
	if(zx==zy)
		return;
	fa[zx]=zy;
	return;
}
priority_queue<prp>q;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>qs;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y;
	for(int i=1;i<=n;i++)
		for(int j=1;j<i;j++)q.push({dis(a[i],a[j]),i,j});
	for(int i=1;i<=n;i++)
		fa[i]=i;
	while(qs--){
		int op,u,v;
		cin>>op;
		if(op==1){
			cin>>u>>v;
			a[++n]={u,v};
			fa[n]=n;
			for(int i=1;i<n;i++)
				q.push({dis(a[i],a[n]),i,n});
		}else if(op==2){
			while(q.size()){
				int i=q.top().i,j=q.top().j;
				if(find(i)==find(j))
					q.pop();
				else break;
			}
			if(!q.size())
				cout<<"-1\n";
			else{
				int mins=q.top().len;
				while(q.size()&&q.top().len==mins){
					int i=q.top().i,j=q.top().j;
					join(i,j);
					q.pop();
				}
				cout<<mins<<"\n";
			}
		}else if(op==3){
			cin>>u>>v;
			if(find(u)==find(v))
				cout<<"Yes\n";
			else
				cout<<"No\n";
		}
	}
	return 0;
}
```

---

## 作者：sodalyghat (赞：0)

### 分析
这个题要维护连通性，考虑并查集。然后显然是第二个操作最难维护，因此来看需要什么来做第二个操作。发现它要合并距离最小的连通块，因此我们可以用一个堆来维护连通块之间的距离，每次取出最小的，如果堆顶的两个点现在属于一个连通块就继续往下取，直到不属于即可。然后第一个操作就把新建的点和之前每一个连通块的距离扔到堆里，第三个操作直接查并查集就好。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Luo_ty{
	const int MAXN = 3005, inf = 0x7fffffff - 1;
	int x[MAXN], y[MAXN];
	int fa[MAXN], sz[MAXN], now;
	int belong(int x){
		if(x == fa[x]) return x;
		return fa[x] = belong(fa[x]);
	}
	void Union(int u, int v){
		int x = belong(u), y = belong(v);
		if(x == y) return ;
		now--;
		if(sz[x] < sz[y]) swap(x, y);
		fa[y] = x;
		sz[x] += sz[y];
	}
	struct node{
		int x, y, len;
	};
	bool operator < (node a, node b){
		return a.len > b.len;
	}
	priority_queue<node> q;
	int Min[MAXN];
	int main(){
		int n, Q;
		scanf("%d%d", &n, &Q);
		for(int i = 1;i <= n;i++){
			scanf("%d%d", &x[i], &y[i]);
			fa[i] = i;
			sz[i] = 1;
		}
		for(int i = 1;i <= n;i++){
			for(int j = i + 1;j <= n;j++){
				q.push((node){i, j, abs(x[i] - x[j]) + abs(y[i] - y[j])});
//				printf("%d %d %d\n", i, j, abs(x[i] - x[j]) + abs(y[i] - y[j]));
			}
		}
		now = n;
		for(int i = 1, op, u, v;i <= Q;i++){
			scanf("%d", &op);
			if(op == 1){
				n++;
				now++;
				scanf("%d%d", &x[n], &y[n]);
				fa[n] = n;
				sz[n] = 1;
				for(int i = 1;i < n;i++){
					Min[i] = inf;
				}
				for(int i = 1;i < n;i++){
					Min[belong(i)] = min(Min[belong(i)], abs(x[n] - x[i]) + abs(y[n] - y[i]));
				}
				for(int i = 1;i < n;i++){
					if(Min[i] != inf){
						q.push((node){i, n, Min[i]});
					}
				}
			}
			else if(op == 2){
//				printf("--%d ", now);
				if(now == 1){
					puts("-1");
					continue;
				}
				int lim = inf;
				while(q.size()){
					node tmp = q.top();
					q.pop();
//					printf("-%d %d %d-\n", tmp.x, tmp.y, tmp.len);
					if(belong(tmp.x) == belong(tmp.y)) continue;
					if(lim == inf){
						lim = tmp.len;
					}
					else{
						if(lim != tmp.len){
							q.push(tmp);
							break;
						}
					}
					Union(tmp.x, tmp.y);
				} 
				printf("%d\n", lim);
//				printf("--%d\n", now);
			}
			else{
				scanf("%d%d", &u, &v);
				if(belong(u) == belong(v)) puts("Yes");
				else puts("No");
			}
		}
		return 0;
	}
}
int main(){
	return Luo_ty::main();
}//International Milan is the best team.
```

---

