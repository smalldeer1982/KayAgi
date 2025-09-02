# Team-Building

## 题目描述

The new academic year has started, and Berland's university has $ n $ first-year students. They are divided into $ k $ academic groups, however, some of the groups might be empty. Among the students, there are $ m $ pairs of acquaintances, and each acquaintance pair might be both in a common group or be in two different groups.

Alice is the curator of the first years, she wants to host an entertaining game to make everyone know each other. To do that, she will select two different academic groups and then divide the students of those groups into two teams. The game requires that there are no acquaintance pairs inside each of the teams.

Alice wonders how many pairs of groups she can select, such that it'll be possible to play a game after that. All students of the two selected groups must take part in the game.

Please note, that the teams Alice will form for the game don't need to coincide with groups the students learn in. Moreover, teams may have different sizes (or even be empty).

## 说明/提示

The acquaintances graph for the first example is shown in the picture below (next to each student there is their group number written).

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1444C/71054646081c6b01196013cc48076c6e988e2a9f.png)

In that test we can select the following groups:

- Select the first and the second groups. For instance, one team can be formed from students $ 1 $ and $ 4 $ , while other team can be formed from students $ 2 $ and $ 3 $ .
- Select the second and the third group. For instance, one team can be formed $ 3 $ and $ 6 $ , while other team can be formed from students $ 4 $ and $ 5 $ .
- We can't select the first and the third group, because there is no way to form the teams for the game.

In the second example, we can select any group pair. Please note, that even though the third group has no students, we still can select it (with some other group) for the game.

## 样例 #1

### 输入

```
6 8 3
1 1 2 2 3 3
1 3
1 5
1 6
2 5
2 6
3 4
3 5
5 6```

### 输出

```
2```

## 样例 #2

### 输入

```
4 3 3
1 1 2 2
1 2
2 3
3 4```

### 输出

```
3```

## 样例 #3

### 输入

```
4 4 2
1 1 1 2
1 2
2 3
3 1
1 4```

### 输出

```
0```

## 样例 #4

### 输入

```
5 5 2
1 2 1 2 1
1 2
2 3
3 4
4 5
5 1```

### 输出

```
0```

# 题解

## 作者：SSerxhs (赞：20)

题意：给定一张点有类型的无向图，求有多少组无序类型对 $(a,b)$ 使得两种类型节点的导出子图是二分图。

众所周知，二分图判定等价于奇环存在性，那么奇环只会出现在类型内部和类型之间。能对答案贡献的类型必定没有奇环，可以先对每个类型 dfs 染色判定。判定得到以下值：$f_i$ 表示 $i$ 属于第 $f_i$ 个连通块，$g_i$ 表示其被染色 $i$。

接下来就是考虑哪些剩下的类型对之间不成奇环，显然数目是非常大的，考虑转化为求哪些类型对成奇环。显然类型对能成奇环的必要条件是类型对之间有边，可以考虑将类间边按照端点所属类型排序一起处理，这样需要处理的类型对数目是 $O(m)$ 的。

考虑一个类型对时，建立一张新图，设类间连边 $(u,v)$，若 $g_u=g_v$ 则连边 $(f_u,f_v)$ 表示 $f_u,f_v$ 的标色是反的，否则连边 $(f_u,newnode),(newnode,f_v)$ 表示 $f_u,f_v$ 的标色相同，则显然原图不矛盾当且仅当新图是二分图，对新图再跑个二分图判定即可。

复杂度 $O(n+m)$ 或 $O(n+m\log m)$，取决于排序是快排还是基排。由于没有并查集，复杂度并没有 $\alpha$。

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pa;
const int N=2e6+2;
vector<int> lb[N],bh[N];
ll ans;
int bel[N],ed[N],f[N],nf[N],app[N],fir[N],nxt[N],lj[N];
int n,c,fh,i,j,k,t,x,y,m,bs,q,tp,cnt,cur,atp,ld;
bool av[N],ned[N];
struct Q
{
	int bu,bv,u,v;
	Q(int a=0,int b=0):bu(bel[a]),bv(bel[b]),u(a),v(b){}
	bool operator<(const Q &o) const {return (bu<o.bu)||(bu==o.bu)&&(bv<o.bv);}
};
Q st[N];
inline void add(int x,int y)
{
	lj[++bs]=y;
	nxt[bs]=fir[x];
	fir[x]=bs;
	lj[++bs]=x;
	nxt[bs]=fir[y];
	fir[y]=bs;
}
inline void read(int &x)
{
	c=getchar();fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
void dfs1(int x,int y)
{
	ed[x]=cnt;f[x]=y;
	for (int i=0;i<lb[x].size();i++) if (!ed[lb[x][i]]) dfs1(lb[x][i],y^1); else
	{
		if (y==f[lb[x][i]]) {av[cur]=0;return;}
	}
}
void dfs2(int x,int y)
{
	//printf("dfs2 %d %d\n",x,y);
	ned[x]=1;nf[x]=y;
	for (int i=fir[x];i;i=nxt[i]) if (!ned[lj[i]]) dfs2(lj[i],y^1); else
	{
		if (y==nf[lj[i]]) {av[cur]=0;return;}
	}
}
int main()
{
	//freopen("a.in","r",stdin);
	read(n);read(m);read(q);
	for (i=1;i<=n;i++) {read(bel[i]);bh[bel[i]].push_back(i);}
	while (m--)
	{
		read(x);read(y);if (bel[x]!=bel[y])
		{
			if (bel[x]>bel[y]) swap(x,y);
			st[++tp]=Q(x,y);
		} else lb[x].push_back(y),lb[y].push_back(x);
	}
	for (i=1;i<=q;i++) av[i]=1;ld=n;
	for (i=1;i<=q;i++)
	{
		cur=i;
		for (j=0;(j<bh[i].size())&&(av[cur]);j++) if (!ed[bh[i][j]]) {++cnt;dfs1(bh[i][j],0);}
	}cnt=0;
	for (i=1;i<=q;i++) if (!av[i]) ++cnt;
	ans=(ll)(q-cnt)*(q-cnt-1)>>1;
	sort(st+1,st+tp+1);
	for (i=1;i<=tp;i=j+1)
	{
		j=i;
		while ((j<tp)&&(st[j+1].bu==st[i].bu)&&(st[j+1].bv==st[i].bv)) ++j;
		if (!(av[st[i].bv]&&av[st[i].bu])) continue;
		atp=0;
		for (k=i;k<=j;k++)
		{
			//if ((st[k].bu==2)&&(st[k].bv==3)) printf("%d %d %d %d %d\n",st[k].u,st[k].v,(int)f[st[k].u]==f[st[k].v],ed[st[k].u],ed[st[k].v]);
			if (f[st[k].u]==f[st[k].v])
			{
				add(ed[st[k].u],++ld);
				add(ld,ed[st[k].v]);
			} else add(ed[st[k].u],ed[st[k].v]);
			if (!ned[ed[st[k].u]]) app[++atp]=ed[st[k].u],ned[ed[st[k].u]]=1;
			if (!ned[ed[st[k].v]]) app[++atp]=ed[st[k].v],ned[ed[st[k].v]]=1;
		}
		for (k=1;k<=atp;k++) ned[app[k]]=0;
		av[cur=i+q]=1;
		for (k=1;(k<=atp)&&(av[cur]);k++) if (!ned[app[k]]) dfs2(app[k],0);
		if (!av[cur]) --ans;
		//printf("%d:%d %d\n",(int)av[cur],st[i].bu,st[i].bv);
		for (k=1;k<=atp;k++) fir[app[k]]=0,ned[app[k]]=0;bs=0;
	}
	printf("%lld",ans);
}
```

---

## 作者：George1123 (赞：9)


更木棒的阅读体验 $\to $ [`George1123`](https://www.cnblogs.com/George1123/p/13912680.html)

---

## 题面

> [CF1444C Team-Building](https://www.luogu.com.cn/problem/CF1444C)

> 给 $n$ 个点 $m$ 条边，每个点有颜色 $c_i(1\le c_i\le k)$，求有多少个颜色对两组点并后是二分图。

> 数据范围：$1\le n,m,k\le 5\cdot 10^5$。

---

## 蒟蒻语

听人说是可撤销并查集后弃疗了，打出正解了没打完，其实普通并查集（~~权值并查集套权值并查集~~）就够了。

因为前面好多法师塔，只下了 $7$ 分。

---

## 题解

看到判断二分图想到黑白染色。但是不想 `dfs`，怎么办？

有两种办法：拆点并查集和路径带权值并查集。蒟蒻选了后者。

对于一个颜色，内部不是二分图那么加入了另一组也不是二分图了。

所以可以先用路径带权值并查集在每个颜色内部把黑白关系连好，内部不是二分图的以后也不用管了。

然后处理两个颜色之间的。虽然看似 $\Theta(n^2)$，但是如果两个颜色间没边必然是二分图，否则只有 $\Theta(m)$ 个。

处理两个颜色间的，可以把两个颜色内部的每个连通块看作一个点，再套一层权值并查集然后连黑白关系。

外面那层并查集每次只需要初始化要用的就可以了，所以不需要可撤销。

---

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
#define mp(a,b) make_pair((a),(b))
#define x first
#define y second
#define bg begin()
#define ed end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
#define R(i,a,b) for(int i=(a),i##E=(b);i<i##E;i++)
#define L(i,a,b) for(int i=(b)-1,i##E=(a)-1;i>i##E;i--)
const int iinf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;

//Data
const int N=5e5;
int n,m,k,c[N],good;
bool bad[N];

//Graph
map<pair<int,int>,int> mp;
int mc; pair<int,int> me[N];
vector<pair<int,int>> e[N];

//Dsu
struct dsu{
    int te[N],dep[N];
    int find(int u){
        if(te[u]==u) return u;
        int an=find(te[u]);
        dep[u]^=dep[te[u]];
        return te[u]=an;
    }
}d[2];

//Main
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>k,good=k;
    R(i,0,n) cin>>c[i],--c[i];
    R(i,0,m){
        int u,v; cin>>u>>v,--u,--v;
        if(c[u]>c[v]) swap(u,v);
        pair<int,int> t=mp(c[u],c[v]);
        if(!mp.count(t)) mp[t]=mc,me[mc]=t,mc++;
        e[mp[t]].pb(mp(u,v));
    }
    iota(d[0].te,d[0].te+n,0);
    R(i,0,k)if(mp.count(mp(i,i))){
        for(pair<int,int> t:e[mp[mp(i,i)]]){
            int x=d[0].find(t.x),y=d[0].find(t.y);
            if(x==y&&(d[0].dep[t.x]^d[0].dep[t.y]^1)!=0){bad[i]=true,good--;break;}
            d[0].dep[x]=d[0].dep[t.x]^d[0].dep[t.y]^1,d[0].te[x]=y;
        }
    }
    // cout<<"good="<<good<<'\n';
    ll ans=1ll*good*(good-1)/2;
    R(i,0,mc)if(me[i].x!=me[i].y){
        if(bad[me[i].x]||bad[me[i].y]) continue;
        for(pair<int,int> t:e[i]){
            int xi=d[0].find(t.x),yi=d[0].find(t.y);
            d[1].dep[xi]=0,d[1].te[xi]=xi,d[1].dep[yi]=0,d[1].te[yi]=yi;
        }
        for(pair<int,int> t:e[i]){
            int xi=d[0].find(t.x),yi=d[0].find(t.y);
            int x=d[1].find(xi),y=d[1].find(yi);
            if(x==y&&(d[1].dep[xi]^d[0].dep[t.x]
                ^d[1].dep[yi]^d[0].dep[t.y]^1)!=0){ans--;break;}
            d[1].dep[x]=d[1].dep[xi]^d[0].dep[t.x]
                ^d[1].dep[yi]^d[0].dep[t.y]^1,d[1].te[x]=y;
        }
    }    
    cout<<ans<<'\n';
    return 0;
}
```

---

**祝大家学习愉快！**

---

## 作者：灵乌路空 (赞：6)

# 知识点：可撤销并查集，枚举 


原题面：[Codeforces](https://codeforces.com/problemset/problem/1444/C)

扯

题解的这个缩点有点 nb。

这个转化枚举对象有点 nb。


感谢 [DrCold](https://codeforces.com/profile/DrCold) 的注释代码！  
提交记录：[https://codeforces.com/contest/1445/submission/97408824](https://codeforces.com/contest/1445/submission/97408824)。

---

## 题意简述


>给定一张 $n$ 个节点 $m$ 条边的无向图，没有自环重边。  
>每个节点都在一个组 (group) 中，共有 $k$ 组，可能存在某组为空。  
>求选出两组点，是它们能构成二分图的 方案数。  
>$1\le n\le 5\times 10^5$，$0\le m\le 5\times 10^5$，$2\le k\le 5\times 10^5$。  
>$1\le c_i\le k$。  
>3S，512MB。  

---

## 分析题意

一张图是二分图的充要条件是不存在奇环。  
先考虑每一组是否为二分图，使用扩展域并查集维护。  
将内部不为二分图的组删除，再反向转化一下，求剩下的 $k'$ 组里，有多少对不能组成二分图，答案即 $\frac{k'(k'-1)}{2} -$ 对数。

之后枚举所有点对检查？太慢啦！  
发现两组点 不能构成二分图的必要条件，是两组点之间有至少一条边。  
发现图很稀疏，考虑枚举所有的 **连接不同组** 的边检查。

先将所有连接不同组的边按照 它们两端的点的组号排序，使得连接的组相同的边 是 被连续枚举的。

在判断每组内是否为二分图后，得到的扩展域并查集的基础上，将枚举到的新的边加入图中。  
若新边连接的两个点的组中出现奇环，则该边无用，直接跳过。  
若加入后出现奇环，则说明连接的两组不能构成二分图，答案 -1。  
当当前枚举的边 与 上一条边连接的组不同时，回退之前的连接操作。  

因此需要一个可撤销并查集维护，则以上过程的复杂度为 $O(m\log n)$。

---

## 爆零小技巧

注意一些为了使答案不重不漏而添加的特判，详见代码。

---

## 代码实现

```cpp
//知识点：可撤销并查集，枚举 
/*
By:Luckyblock
*/
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <vector>
#define LL long long
const int kMaxn = 5e5 + 10;
//=============================================================
LL ans;
int n, m, k, cnt, col[kMaxn];
bool no[kMaxn];

int top, fa[kMaxn << 1], size[kMaxn << 1];
struct Stack {
  int u, v, fa, size;
} st[kMaxn << 1];

int e_num;
struct Edge {
  int u, v, colu, colv;
} e[kMaxn];
//=============================================================
inline int read() {
  int f = 1, w = 0;
  char ch = getchar();
  for (; !isdigit(ch); ch = getchar())
    if (ch == '-') f = -1;
  for (; isdigit(ch); ch = getchar()) w = (w << 3) + (w << 1) + (ch ^ '0');
  return f * w;
}
void Chkmax(int &fir_, int sec_) {
  if (sec_ > fir_) fir_ = sec_;
}
void Chkmin(int &fir_, int sec_) {
  if (sec_ < fir_) fir_ = sec_;
}
bool CompareEdge(Edge f_, Edge s_) {
  if (f_.colu != s_.colu) return f_.colu< s_.colu;
  return f_.colv < s_.colv;
}
int Find(int x_) {
  while (x_ != fa[x_]) x_ = fa[x_];
  return x_;
}
void Union(int u_, int v_) {
  int fu = Find(u_), fv = Find(v_);
  if (size[fu] > size[fv]) std::swap(fu, fv); //没写按秩合并 
  st[++ top] = (Stack) {fu, fv, fa[fu], size[fu]};
  if (fu != fv) {
    fa[fu] = fv;
    size[fv] += size[fu];
    size[fu] = 0;
  }
}
void Restore() {
  Stack now = st[top];
  if (now.u != now.v) {
    fa[now.u] = now.fa;
    size[now.u] = now.size;
    size[now.v] -= now.size;
  }
  top --;
}
//=============================================================
int main() {
  n = read(), m = read(), cnt = k = read();
  for (int i = 1; i <= n; ++ i) col[i] = read();
  for (int i = 1; i <= 2 * n; ++ i) {
    fa[i] = i;
    size[i] = 1;
  }
  for (int i = 1; i <= m; ++ i) {
    int u_ = read(), v_ = read();
    if (col[u_] != col[v_]) {
      e[++ e_num] = (Edge) {u_, v_, col[u_], col[v_]};
      if (e[e_num].colu > e[e_num].colv) {
        std::swap(e[e_num].colu, e[e_num].colv); 
      }
      continue ;
    }
    if (no[col[u_]]) continue ; //特判，防止重复统计  
    if (Find(u_) == Find(v_)) {
      cnt --;
      no[col[u_]] = true;
      continue ;
    }
    Union(u_, v_ + n);
    Union(v_, u_ + n);
  }
  
  ans = 1ll * (cnt - 1ll) * cnt / 2ll;
  int last_top = top, flag = false;
  
  std::sort(e + 1, e + e_num + 1, CompareEdge);
  for (int i = 1; i <= e_num; ++ i) {
    Edge now = e[i];
    if (no[now.colu] || no[now.colv]) continue ;
    if (now.colu != e[i - 1].colu || now.colv != e[i - 1].colv) {
      while (top != last_top) Restore();
      flag = false;
    }
    if (flag) continue ; //特判，防止重复统计 
    if (Find(now.u) == Find(now.v)) {
      ans --;
      flag = true;
      continue ;
    }
    Union(now.u, now.v + n);
    Union(now.v, now.u + n);
  }
  printf("%lld\n", ans);
  return 0;
}
```

---

## 作者：zac2010 (赞：3)

### 前置知识

1. 二分图的基础概念，怎么用并查集判定二分图。
2. 可撤销并查集，看[这](https://www.luogu.com.cn/blog/zaczac/ke-che-xiao-bing-zha-ji)。

### 思路

比较基础的一道题，可以和模板题相媲美。

先再提一下吧，找能否构成二分图的关键性质在于此图是否有奇环。

我们考虑对于两个端点都是同一组内的边，只要选了这一组就必须要选这些边，所以初始的时候把同组内的边都连上，且这样不会影响其他组。

这时，单组内构不成二分图的那些组别一定不会和其它组产生贡献。所以我们只考虑单组内能构成二分图的那些组。

我们把所有两个端点分别处于 $i$ 与 $j$ 这两组的边弄到一起去（排序可以实现），然后我们把这些边加到并查集里去，即用并查集去判断是否能构成二分图。而对于新的一对组别——第 $k$ 组以及第 $t$ 组，前面的 $i$ 与 $j$ 这两组的边没用了，所以要撤销掉。而这正是一个可撤销并查集。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define L(i, a, b) for(int i = a; i <= b; i++)
#define R(i, a, b) for(int i = a; i >= b; i--) 
using namespace std;
const int N = 1e6 + 10;
int n, m, k, c[N], tu[N], sum[N]; ll ans;
vector<pair<int, int> >e[N];
struct DSU{
	int n, top, s[N], fa[N], sz[N];
	void ins(int x){n++, fa[x] = x, sz[x] = 1;}
	int F(int x){return x == fa[x]? x : F(fa[x]);}
	void U(int x, int y){
		x = F(x), y = F(y); if(x == y) return;
		if(sz[x] < sz[y]) swap(x, y);
		fa[y] = x, sz[x] += sz[y], s[++top] = y;
	}
	void D(){
		if(!top) return;
		int y = s[top--]; sz[fa[y]] -= sz[y], fa[y] = y;
	}
	void back(int t){while(top > t) D();}
}d;
bool cmp(pair<int, int> a, pair<int, int> b){return c[a.second] < c[b.second];}
int main(){
	scanf("%d%d%d", &n, &m, &k);
	L(i, 1, n) scanf("%d", &c[i]);
	L(i, 1, n * 2) d.ins(i);
	L(i, 1, k) tu[i] = 1;
	L(i, 1, m){
		int x, y; scanf("%d%d", &x, &y);
		if(c[x] > c[y]) swap(x, y);
		if(c[x] == c[y]){
			if(d.F(x) == d.F(y))
				tu[c[x]] = 0;
			else d.U(x, y + n), d.U(x + n, y);
		}
		else e[c[x]].push_back(make_pair(x, y));
	}
	R(i, k, 1) sum[i] = sum[i + 1] + tu[i];
	L(cl, 1, k){
		if(!tu[cl]) continue;
		sort(e[cl].begin(), e[cl].end(), cmp);
		int flag = 1, t = d.top; ans += sum[cl + 1];
		for(int i = 0; i < e[cl].size(); i++){
			int x = e[cl][i].first, y = e[cl][i].second;
			if(!tu[c[y]]) flag = -1;
			if(flag == 1 && d.F(x) == d.F(y))
				flag = 0;
			else d.U(x, y + n), d.U(x + n, y);
			if(i == e[cl].size() - 1 || c[y] != c[e[cl][i + 1].second]){
				ans -= (!flag), flag = 1, d.back(t);
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
} 
```


---

## 作者：Elma_ (赞：3)

从别的题解那里抄来的题意：给定一张点有类型的无向图，求有多少组无序类型对 $(a,b)$ 使得两种类型节点的导出子图是二分图。

容易想到把同一类型的点内部先判断是否是二分图，可以用带权并查集搞搞（类似 dfs 黑白染色）。如果某种类型的点本身就不是二分图，之后就无需考虑这类点，可以把它们直接删去。

然后就只剩下连接不同类型点的边了。容易发现这个图很稀，因此考虑改为计算有多少组 $(a,b)$ 使得两种类型节点的导出子图不是二分图，这样只需枚举图中存在的类型对判断即可。

具体来说，对于图中一条连接类型 $(a,b)$ 的边，若连接后会产生奇环，那么这条边就不合法，进而得到这个类型对 $(a,b)$ 不合法，这也可以使用带权并查集维护。每次枚举到一个新的类型对时，要撤销上一个类型对产生的影响，于是就把并查集改成可撤销的就做完了。时间复杂度 $O(m \log n)$。

```cpp
#define int long long
#define pii pair<int, int>
#define mp(x, y) make_pair(x, y)

const int maxn = 5e5 + 5;

int n, m, k, cnt, ans, tot, flag;
int col[maxn], fa[maxn], g[maxn], siz[maxn], vis[maxn];

int tp, sta[maxn];

inline int find(int x, int &c) {
    while (fa[x] != x) {
        c ^= g[x], x = fa[x];
    }
    return x;
}
inline bool merge(int x, int y) {
    int res1 = 0, res2 = 0;
    x = find(x, res1);
    y = find(y, res2);
    int w = res1 ^ res2 ^ 1;
    if (x == y) {
        if (w == 1) return 0;
        return 1;
    }
    if (siz[x] > siz[y]) swap(x, y);
    fa[x] = y, g[x] = w, siz[y] += siz[x];
    if (flag) sta[++tp] = x;
    return 1;
}

inline void del(int x, int y) {
    while (true) {
        siz[x] -= y;
        if (fa[x] == x) return;
        x = fa[x];
    }
}

int buc[maxn][2];
map <pii, int> mp;
vector <pii> e[maxn];

signed main(void) {
    n = read(), m = read(), cnt = k = read();
    for (int i = 1;i <= n;i++) col[i] = read(), fa[i] = i, siz[i] = 1;
    for (int i = 1, u, v;i <= m;i++) {
        u = read(), v = read();
        if (col[u] != col[v]) {
            if (col[u] > col[v]) swap(u, v);
            pii p = mp(col[u], col[v]);
            if (!mp.count(p)) { 
                mp[p] = ++tot;
                buc[tot][0] = col[u], buc[tot][1] = col[v];
            }
            e[mp[p]].push_back(mp(u, v));
            continue;
        }
        if (!merge(u, v)) {
            if (!vis[col[u]]) cnt--;
            vis[col[u]] = 1;
        }
    }
    ans = cnt * (cnt - 1) / 2, flag = 1;
    for (int i = 1;i <= tot;i++) {
        if (vis[buc[i][0]] || vis[buc[i][1]]) continue;
        int fl = 1;
        for (pii p : e[i]) {
            int u = p.first, v = p.second;
            if (!merge(u, v)) {
                fl = 0;
                break;
            } 
        }
        if (!fl) ans--;
        for (int i = 1;i <= tp;i++) {
            if (fa[sta[i]] != sta[i]) del(fa[sta[i]], siz[sta[i]]);
            fa[sta[i]] = sta[i], g[sta[i]] = 0;
        }
        tp = 0;
    }
    printf("%lld\n", ans);
    return 0;
}
```


---

## 作者：shao0320 (赞：3)

### CF1444C Team-Building

首先想到把一组点缩在一起之后在搞，如果某一组点自己内部都有奇环那就指定 $\text{GG}$ 了。

那么首先我们可以用一个扩展域并查集搞一下每组点的内部，注意到这个图很稀，那么不用枚举组对，只需要加边即可。

我们先把连接同样组的边扔掉，然后对于剩下的边我们把连接同一对组的边扔在一起处理。

首先设没有 $\text{GG}$ 的组有 $L$ 个，那么我们只要求出两个本来很好但是连上边之后就歇了的对数。

直接维护一个可撤销的扩展域并查集即可。



---

## 作者：Masterwei (赞：2)

#### 前言

刚刚 VP 的，赛时想到了，没打完，赛后过的。

#### 思路

容易发现我们只需要判断两个点集的导出子图是否有奇环。

具体的，我们将同个点集的边用并查集联起来，将不同点集的边存起来，然后枚举每一个点集，再对于同样的点集，将边集体加起来，再判断是否有奇环。最后将边删掉即可。实现可用启发式合并的并查集。

代码还好。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0;bool f=0;char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int Maxn=1e6+5;
int n,m,k;
int a[Maxn];
struct edge{int u,v;};
vector<edge>v[Maxn];
vector<int>b[Maxn];
int ok[Maxn];
int f[Maxn<<1],dep[Maxn<<1];
struct node{int son,op;};
stack<node>stk;
inline int find(int x){
	while(x^f[x])x=f[x];
	return x;
}
int pd=1;
inline void merge(int x,int y,int op){
	int u=find(x),v=find(y);
	if(dep[u]>dep[v])swap(u,v);
	if(op)stk.push({u,(dep[u]==dep[v])});
	f[u]=v;dep[v]+=(dep[u]==dep[v]);
	if(find(x)==find(x+n))pd=0;
	if(find(y)==find(y+n))pd=0;
}
inline void del(){
	while(stk.size()){
		dep[f[stk.top().son]]-=stk.top().op;
		f[stk.top().son]=stk.top().son;
		stk.pop();
	}
}
struct point{
	vector<int>val;
}p[Maxn];
map<pair<int,int>,vector<edge> >e;
signed main(){
	n=read();m=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n*2;i++)f[i]=i;
	for(int i=1;i<=m;i++){
		int u=read(),v1=read();
		if(a[u]>a[v1])swap(u,v1);
		if(a[u]==a[v1])v[a[u]].push_back({u,v1}),p[a[u]].val.push_back(u),p[a[u]].val.push_back(v1);
		else b[a[u]].push_back(a[v1]),e[{a[u],a[v1]}].push_back({u,v1});
	}int cnt=0;
//	printf("gfdehtrh\n");
	for(int i=1;i<=k;i++){
		pd=1;
		for(int j=0;j<v[i].size();j++){
			int u=v[i][j].u;
			int v1=v[i][j].v;
			merge(u+n,v1,0);merge(u,v1+n,0);
		}
		ok[i]=pd;
		cnt+=ok[i];
//		printf("%lld %lld\n",i,ok[i]);
	}int ans=0;
	for(int i=1;i<k;i++){
		if(!ok[i])continue;
		sort(b[i].begin(),b[i].end());
		int len=unique(b[i].begin(),b[i].end())-b[i].begin();
		cnt--;
		int now=cnt;
		for(int kk=0,j;kk<len;kk++){
			j=b[i][kk];
			vector<edge>ve=e[{i,j}];
			pd=1;
			for(edge tmp:ve){
				int u=tmp.u,v=tmp.v;
//				printf("%lld %lld:%lld %lld\n",i,j,u,v);
				merge(u+n,v,1);merge(u,v+n,1);
			}
			del();
			if(ok[j]&&!pd)now--;
		}ans+=now;
	}printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：daniEl_lElE (赞：1)

首先判断二分图可以使用带权并查集。

先对同一种颜色的点之间的边跑带权并查集。

对于两种颜色之间没边的颜色组，能成为二分图等价于两边都是二分图。

否则，最多有 $O(m)$ 组两种颜色之间有边的颜色组。对于每个分别跑带权并查集判断即可。注意需要可撤销。

总复杂度 $O((n+m)\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int c[1000005];
int f[1000005],siz[1000005],dis[1000005],tag[1000005];
int u[1000005],v[1000005];
int find(int i){
	return f[i]==i?f[i]:find(f[i]);
}
int getval(int i){
	return f[i]==i?0:dis[i]^getval(f[i]);
}
vector<pair<pair<int,int>,int>> vc;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,m,k; cin>>n>>m>>k;
	for(int i=1;i<=n;i++) cin>>c[i];
	for(int i=1;i<=n;i++) f[i]=i,siz[i]=1;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i];
		if(c[u[i]]==c[v[i]]){
			int U=find(u[i]),V=find(v[i]),disu=getval(u[i]),disv=getval(v[i]);
//			cout<<U<<" "<<V<<" "<<(disu^disv^1)<<"\n";
			if(U==V){
				if(disu==disv){
					tag[c[u[i]]]=1;
				}
			}
			else{
				if(siz[U]<siz[V]){
					f[U]=V;
					dis[U]=disu^disv^1;
					siz[V]+=siz[U]; 
				}
				else{
					f[V]=U;
					dis[V]=disu^disv^1;
					siz[U]+=siz[V];
				} 
			}
		}
		else{
			if(c[u[i]]>c[v[i]]) swap(u[i],v[i]);
			vc.push_back(make_pair(make_pair(c[u[i]],c[v[i]]),i));
		}
	}
//	cout<<find(5)<<" "<<find(6)<<" "<<getval(5)<<" "<<getval(6)<<"\n";
	int tot=0;
	for(int i=1;i<=k;i++) tot+=(!tag[i]);
//	cout<<tot<<" ";
	int del=0;
	sort(vc.begin(),vc.end());
	for(int i=0;i<vc.size();i++){
		int j=i;
		while(j+1<vc.size()&&vc[j+1].first==vc[i].first) j++;
		if(!tag[vc[i].first.first]&&!tag[vc[j].first.second]){
			vector<pair<int,int>> ret;
			int er=0;
			for(int l=i;l<=j;l++){
				int t=vc[l].second;
				int U=find(u[t]),V=find(v[t]),disu=getval(u[t]),disv=getval(v[t]);
//				cout<<u[t]<<" "<<v[t]<<" "<<U<<" "<<V<<" "<<disu<<" "<<disv<<"\n";
				if(U==V){
					if(disu==disv){
						er=1;
					}
				}
				else{
					if(siz[U]<siz[V]){
						f[U]=V;
						dis[U]=disu^disv^1;
						siz[V]+=siz[U]; 
						ret.push_back(make_pair(U,V));
					}
					else{
						f[V]=U;
						dis[V]=disu^disv^1;
						siz[U]+=siz[V];
						ret.push_back(make_pair(V,U));
					} 
				}
			}
			del+=er;
//			cout<<"\n";
//			if(er) cout<<vc[i].first.first<<" "<<vc[i].first.second<<"\n";
			reverse(ret.begin(),ret.end());
			for(auto x:ret){
				f[x.first]=x.first;
				dis[x.first]=0;
				siz[x.second]-=siz[x.first];
			}
		}
		i=j;
	}
	cout<<tot*(tot-1)/2-del;
	return 0;
}
```

---

## 作者：SnowTrace (赞：1)

首先，相当显然的是，如果一个组内部的导出子图不是二分图那这一组就一定没用。

继续思考，假如两个组之间没有连边，而且这两个组内部都满足，那是不是就可以直接满足了？

注意到边数不多，也就是说，实际上有效的，需要计算的点对只有 $O(m)$ 个（其他点对要么内部不合法，要么中间没有边，直接成立了）。

考虑如何实现，考虑我们枚举其中一个组 $c$，可以先遍历得到和 $c$ 之间有边的所有组，把这些组取出来计算，用可撤销并查集维护二分图，把两组之间的边全部加进去，然后再撤销即可。

实际上记录一下初始状态每次还原回去也行，并不需要可撤销并查集。

复杂度 $O(m\log n)$。

代码写的特别丑。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
vector<pair<int,int> >edge[500005];
vector<int>neib,cc[500005],ss[500005];
vector<int>p[500005];int cnt =0;
int col[500005],c[500005],be[500005],ok[500005],s[500005];
vector<pair<int,int> >lf;int sz[1000005],fa[1000005];
int find(int x){
	if(fa[x] == x)return x;return find(fa[x]);
}void merge(int x,int y){
	x = find(x),y = find(y);if(x == y)return;
	if(sz[x]<sz[y]){
		sz[y]+=sz[x];fa[x] = y;
		lf.push_back({x,y});
	}else{
		sz[x]+=sz[y];fa[y] = x;
		lf.push_back({y,x});
	}
}void roll(){
	int x = lf.back().first,y = lf.back().second;
	fa[x] = x,sz[y]-=sz[x];lf.pop_back();
}
void dfs(int now,int C,int cc){
	be[now] = cc;col[now] = C;
	for(int x:p[now]){
		if(c[x] == c[now] and !be[x])merge(now+n,x),merge(now,x+n),dfs(x,1^C,cc);
		if(c[x] == c[now] and be[x]){
			if(col[x] == col[now]){
				ok[c[x]] = 0;
			}
		}
	}
}int kk[500005];int nsz;
signed main(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> m >> k;
	for(int i =1;i<=n+n;i++)fa[i] = i,sz[i] = 1;
	for(int i = 1;i<=k;i++)ok[i] = 1;
	for(int i = 1;i<=n;i++){
		cin >> c[i];ss[c[i]].push_back(i);
	}for(int i = 1;i<=m;i++){
		int a,b;cin >>a >> b;
		p[a].push_back(b),p[b].push_back(a);
	}
	for(int i = 1;i<=n;i++)col[i] = -1;
	for(int i = 1;i<=n;i++){
		if(col[i]==-1)dfs(i,1,++cnt);
	}int tot = 0;for(int i = 1;i<=k;i++)tot+=ok[i];
	for(int i =0;i<=cnt;i++)s[i] = -1;long long ans =0 ;
	nsz = lf.size();
	for(int i = 1;i<=k;i++){
		if(!ok[i])continue;
		for(int x:ss[i]){
			for(int xx:p[x]){
				if(c[xx]!=i and ok[c[xx]]){
					neib.push_back(c[xx]);edge[c[xx]].push_back({x,xx});
				}
			}
		}
		sort(neib.begin(),neib.end());neib.erase(unique(neib.begin(),neib.end()),neib.end());
		for(int x:neib){
			int okk = 1;
			for(auto e:edge[x]){
				int a = e.first,b =e.second;
				if(find(a) == find(b) or find(a+n) == find(b+n))okk =0 ;
				merge(a,b+n),merge(a+n,b);
			}ans+=okk;
			edge[x].clear();
			while(lf.size()>nsz)roll();
		}ans+=tot-1-neib.size();neib.clear();
	}cout << ans/2 << endl;
	return 0;
}/*

 
I see those tears in your eyes
I feel so helpless inside
Oh love there's no need to hide
Just let me love you when your heart is tired
 

*/
```

---

## 作者：OtterZ (赞：1)

# 题意
给定一张有 $N$ 个点和 $M$ 条边的图和图中每个点的分组（共 $K$ 组），问有多少对组使两组内点与点之间的边形成二分图。
# 二分图判定
二分图判定可以用拆点并查集完成，此题中要用的并查集是可删除并查集。
# 两种情况
我们考虑排除法。  
初始时默认有 $\frac{K \times (K - 1)}{2}$ 组，当两组点满足任意情况下可排除：

1. 任意一组内无法形成二分图；
2. 两组点之间的边打破二分图要求。

我们此时不能保留其他组的点和两组的点的边，事实上，我们可以回撤之前两组的点之间的边。
# 动态判定
一张图不是二分图当且仅当出现有奇数个点的环，故而我们可以在每次加边后只判定对两点状态是否符合二分图中每个点性质即可，因为若加入此边后出现奇数个点的环，这两点必然在环内，只需有其中一个点在对应环内即可。
# 注意事项

1. 答案要开 `long long`；
2. 判定时将两种情况分开算，避免重复计算；
3. 一组无法形成二分图的点和为空的集合一样要排除；
4. 可回撤并查集不能路径压缩，但可以启发式合并，使整体复杂度为 $\operatorname{O}(m\log m + m\log n)$（用快排的情况下）。

# 上代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,k;
int c[500009],cnt;
bool dead[500009];//内部无法成为二分图 
struct edge{
	int begin,end;
	edge(int b = 0,int e = 0){
		if(c[b] > c[e]){//一号点分组需小于等于二号点 
			int t = e;
			e = b;
			b = t;
		}
		begin = b,end = e;
	}
	bool operator<(const edge &b)const{
			return c[begin] < c[b.begin] || (c[begin] == c[b.begin] && c[end] < c[b.end]);
	}
}e[500009];

//拆点可回撤并查集 
int kb = 0;//回溯用 
int dfa[1000009],dsz[1000009];
int stk[2000009],*top = stk;
int find(int x){
	if(dfa[x] == x)
		return x;
	else
		return find(dfa[x]);//为了可回撤不用路劲优化 
}
void Union(int x,int y){
	int u = find(x),v = find(y);
	if(u == v)
		return;
	if(dsz[u] > dsz[v]){
		int t = u;
		u = v;
		v = t;
	}
	dfa[u] = v;
	dsz[v] += dsz[u];
	top++;
	*top = u; 
	kb++;
}
void d_back(){//回撤 
	dsz[dfa[*top]] -= dsz[*top];
	dfa[*top] = *top;
	top--;
	kb--;
}
void d_init(){
	for(int i = 1; i <= 2 * n; i ++){
		dfa[i] = i;
		dsz[i] = 1;
	}
	top = stk;
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1; i <= n; i ++){
		scanf("%d",&c[i]);
	}
	d_init();
	long long ans = 1ll * k * (k - 1) >> 1;
	int o = 0;
	for(int i = 1; i <= m; i ++){
		int u,v;
		scanf("%d %d",&u,&v);
		if(c[u] == c[v]){//同组处理
			Union(u,v + n);
			Union(v,u + n);
			if(find(u) == find(u + n) || find(v) == find(v + n)){//自相矛盾，自家后院起火
			    o += !dead[c[u]];
				dead[c[u]] = true;//上报 
			} 
		}
		else{
			e[++cnt] = edge(u,v);
		}
	}
	ans -= 1ll * o * (o - 1) / 2 + 1ll * o * (k - o);
	sort(e + 1,e + cnt + 1);
	int i = 1;
	kb = 0;//不能删现有的 
	if(i <= cnt){
		do{
			if(i != 1 && (c[e[i].begin] != c[e[i - 1].begin] || c[e[i].end] != c[e[i - 1].end])){//变了 
				if(kb > 0){//要回溯
					do{
						d_back();
					} while(kb > 0);
				}
			}
			if(dead[c[e[i].begin]]){//内部起火1
			//	printf("%d %d 1\n",e[i].begin,e[i].end);
				int s = c[e[i].begin];//起火处
				do{//跳过 
					i++;
				} while(i <= cnt && c[e[i].begin] == s);
				continue;
			}
			else if(dead[c[e[i].end]]){//内部起火2
			//	printf("%d %d 2\n",e[i].begin,e[i].end);
				int s = c[e[i].end],t = c[e[i].begin];
				do{//跳过 
					i++;
				} while(i <= cnt && c[e[i].end] == s && c[e[i].begin] == t);
				continue;
			}
			Union(e[i].begin,e[i].end + n);
			Union(e[i].end,e[i].begin + n);
			int u = e[i].begin,v = e[i].end;
			if(find(u) == find(u + n) || find(v) == find(v + n)){//自相矛盾，合作不当 
			//	printf("%d %d 3\n",e[i].begin,e[i].end);
				ans--;
				int s = c[e[i].end],t = c[e[i].begin];
				do{//跳过 
					i++;
				} while(i <= cnt && c[e[i].end] == s && c[e[i].begin] == t);
				continue;
			} 
			i++;
		}while(i <= cnt);
	} 
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：快斗游鹿 (赞：1)

## 思路

如果一个图有奇环，则该图不是二分图。反之则是。

先对每组每个点连边，如果某组自身就不是个二分图，那么它和其他组也不会组成二分图。

连完后，可以想到要枚举。但数据范围只允许我们枚举 $n,m,k$ 的其中一个。枚举前两个肯定超时，所以枚举 $k$。那么对于第 $i$ 组点，我们可以记下所有满足 $c_x<c_y$ 且 $x$ 在第 $i$ 组的点对。其中 $c_x,c_y$ 分别表示点 $x,y$ 的组别。枚举时枚举这些点对就行。这样也保证了不会算重。

接下来想如何判定二分图。显然如果黑白染色复杂度会比较高，所以用并查集来判。对于第 $i$ 组点，可以先按 $y$ 的组别排个序，这样能方便地实现一次加入一段组别相同的点对。一段组别相同的点对加完后，自然想到如果这时满足条件，答案就加一。但这样可能会少算。

因为题目中提到，可能存在某组为空。这时统计合法的并不方便，所以应该用总方案数减去不合法方案数。只要一段组别相同的点加完后，不满足条件，不合法方案数就加一。方案数更新完后就把刚刚加的边删掉，这时就需要可撤销并查集。而总方案数用前缀和算就行。

## 代码

```
#include<bits/stdc++.h>
#define int long long
#define mk make_pair 
using namespace std;
const int N=1e6+5;
int n,m,c[N],fa[N],size[N],sum[N],ans,k;
bool flag[N];
vector<pair<int,int> >e[N];
stack<int>st;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
bool cmp(pair<int,int>a,pair<int,int>b){
	return c[a.second]<c[b.second];
}
int find(int x){
	return x==fa[x]?x:find(fa[x]);
}
void merge(int u,int v){
	int U=find(u);
	int V=find(v);
	if(U!=V){
		if(size[U]<size[V])swap(U,V);
		size[U]+=size[V];
		fa[V]=U;
		st.push(V);
	}
}
void del(int u){
	while(st.size()>u){
		int uu=st.top();st.pop();
		size[fa[uu]]-=size[uu];fa[uu]=uu;
	}
}
signed main(){
	//freopen("data.txt","r",stdin);
	n=read();m=read();k=read();
	for(int i=1;i<=n;i++){
		c[i]=read();
	}
	for(int i=1;i<=2*n;i++)fa[i]=i,size[i]=1;
	for(int i=1;i<=m;i++){
		int u,v;u=read();v=read();
		if(c[u]==c[v]){
			if(find(u)==find(v)){
				flag[c[u]]=1;
			}
			//else{
				merge(u,v+n);
				merge(v,u+n);
			//}
		}
		else{
			if(c[u]>c[v])swap(u,v);
			e[c[u]].push_back(mk(u,v));
		}
	}
	for(int i=k;i>=1;i--){
		if(flag[i])sum[i]=sum[i+1];
		else sum[i]=sum[i+1]+1;
	}
	for(int i=1;i<=k;i++){
		if(flag[i])continue;
		ans+=sum[i+1];
		//cout<<i<<endl;
		//cout<<sum[i+1]<<endl;
		sort(e[i].begin(),e[i].end(),cmp);
		int aaa=st.size();
		int f=1;
		for(int j=0;j<e[i].size();j++){
			int x=e[i][j].first;
			int y=e[i][j].second;
			//cout<<x<<" "<<y<<endl;
			if(flag[c[y]]){
				//continue;
				f=-1;
			}
			if(f==1&&find(x)==find(y)){
				f=0;
			}
			//else{
				merge(x,y+n);
				merge(y,x+n);
			//}
			if(j==e[i].size()-1||c[y]!=c[e[i][j+1].second]){
				//cout<<c[x]<<" "<<c[y]<<endl;
				//cout<<x<<" "<<y<<endl;
				ans-=(!f);
				f=1;
				del(aaa);
			}
		}
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：封禁用户 (赞：1)

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF1444C)

[Codeforces](https://codeforces.com/problemset/problem/1444/C)

### 前置知识

#### 二分图及其并查集判定法

对于一个二分图我们有三种判定方法

1. 根据定义判定。先定义第一个点的颜色为 $0$，与其相邻的点颜色定义为 $1$，以此类推，如果每一条边的两个点的颜色都不同，则原图为二分图。我们通常称其为“染色法”。

1. 根据结构判定。原图为二分图的充分必要条件是原图存在长度为奇数的环。

1. 使用并查集判断。我们应当先进行拆点，若共有 $n$ 个点。把每个点拆成两个点，点 $x$ 颜色为 $0$ 定义为 $x$，颜色为 $1$ 定义为 $x+n$。如果存在一条 $x$ 和 $y$ 的边，就通过并查集合并 $(x,y+n)$ 和 $(x+n,y)$。最终如果对于任何一条 $x$ 和 $y$ 的边，$x$ 和 $y$ 都不在一个并查集内，则原图为二分图。

#### [并查集的启发式按秩合并与删除](https://oi-wiki.org/ds/dsu-complexity/)

+ 按秩合并即按照其结构进行合并，不进行路径压缩操作，保证其结构不变，便于删除操作。

+ 启发式合并通俗来讲就是把小的集合合并到大的集合，保证其时间复杂的为 $\log (n)$ 级别的。

启发式按秩合并：

```cpp
inline int find(int u)
{
	while(u != f[u]) u = f[u];
	return u;
}
inline int merge(int u,int v)
{
	u = find(u),v = find(v);
	if(u == v) return 0;
	if(sz[u] < sz[v]) swap(u,v);
	f[v] = u,sz[u] += sz[v];
	s.push((pii){u,v});
	return 1;
}
```
删除

```cpp
inline void erase(int u,int v)
{
	sz[u] -= sz[v],f[v] = v;
}
inline void erase(int &len)
{
	while(len--)
	{
		erase(s.top().first,s.top().second);
		s.pop()	;
	}
	len = 0;
}
```

### 题意

对于一张无向图，每个节点都有一个颜色，询问有多少个无序颜色点对 $(x,y) \ (x \not= y)$ 满足颜色 $x$ 和颜色 $y$ 组成的图是一个二分图。

### 分析

首先，我们肯定无法枚举无序颜色对 $(x,y)$，因为这样会超时。

我们分析点对 $(x,y)$，首先，颜色 $x$ 和颜色 $y$ 的子图必须是二分图，其次，加入跨颜色 $(x,y)$ 的边也必须是二分图。

可以发现，边只有 $m$ 条，所以跨颜色的边也不多，我们以较小的颜色为下标开 vector 把它们都记下来即可。对于两边同一个颜色的边，我们也记下来。

然后，我们对每一个颜色按照以上方法建立并查集，判断一下其子图是否是二分图。

接着，我们枚举每个合法的颜色，将其 vector 按另一个颜色从小到大排序，当另一个颜色也合法时，不断地加并查集的边。

这里，我们每加一条边都判断一下它还是不是二分图，**如果这已经不是二分图了，再加边也一定不是二分图**，我们减去这种情况，并在并查集内删除这个颜色的边，这是最近加的，我们可以用栈记下来。当另一个颜色加完时，我们也删除这写边。

$sum_i$ 表示在颜色区间 $[i,k]$ 中不合法的颜色个数。

这部分的代码：

```cpp
if(vis[i]) continue;
sort(r[i].begin(),r[i].end());
ans += k-i-sum[i];
int lst = 0,len = 0,no = 0;
for(auto p:r[i])
{
	if(vis[p.t]||p.t == no) continue;
	if(lst&&p.t != lst) erase(len);
	len += merge(p.u,p.v+n) + merge(p.u+n,p.v); 
	if(find(p.u) == find(p.v)) 
	{
		--ans;
		no = p.t;
	}			
	lst = p.t;		
}
erase(len);	
```
### 总结

这是一道图论好题，灵活运用了并查集和二分图的判定方法。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1,num = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -p;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		num = (num<<3)+(num<<1)+(c^48);
		c = getchar();
	}
	x = p * num;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10+48);
}
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
#define pii pair<int,int>
#define N 500010
int f[N<<1],sz[N<<1],c[N],sum[N],n,m,k;
vector<int> g[N],a[N];
struct node
{
	int u,v,t;
	inline bool friend operator<(const node &X,const node &Y)
	{
		return X.t < Y.t;
	}
};
vector<node> r[N];
stack<pii> s;
bitset<N> vis;
inline int find(int u)
{
	while(u != f[u]) u = f[u];
	return u;
}
inline int merge(int u,int v)
{
	u = find(u),v = find(v);
	if(u == v) return 0;
	if(sz[u] < sz[v]) swap(u,v);
	f[v] = u,sz[u] += sz[v];
	s.push((pii){u,v});
	return 1;
}
inline void erase(int u,int v)
{
	sz[u] -= sz[v],f[v] = v;
}
inline void erase(int &len)
{
	while(len--)
	{
		erase(s.top().first,s.top().second);
		s.pop();
	}
	len = 0;
}
ll ans = 0; 
int main()
{
	read(n),read(m),read(k);
	F(i,1,n) 
	{
		read(c[i]);
		a[c[i]].push_back(i);
	}
	while(m--)
	{
		int u,v;
		read(u),read(v);
		if(c[u] == c[v])
		{
			g[u].push_back(v);
			g[v].push_back(u); 
		}
		else
		{
			if(c[u] > c[v]) swap(u,v);
			r[c[u]].push_back((node){u,v,c[v]}); 
		}
	}
	F(i,1,n<<1) f[i] = i,sz[i] = 1;
	F(i,1,k)
	{
		for(auto u:a[i])
  			for(auto v:g[u])
  				merge(u,v+n),merge(u+n,v);	
	  	for(auto u:a[i])
	  		if(find(u) == find(u+n))
	  		{
	  			vis[i] = 1;
				break;	
			}
	}
	D(i,k,1) sum[i] = sum[i+1] + vis[i];
	F(i,1,k)
	{
		if(vis[i]) continue;
		sort(r[i].begin(),r[i].end());
		ans += k-i-sum[i];
		int lst = 0,len = 0,no = 0;
		for(auto p:r[i])
		{
			if(vis[p.t]||p.t == no) continue;
			if(lst&&p.t != lst) erase(len);
			len += merge(p.u,p.v+n) + merge(p.u+n,p.v); 
			if(find(p.u) == find(p.v)) 
			{
				--ans;
				no = p.t;
			}			
			lst = p.t;		
		}
		erase(len);		
	} 
	write(ans); 
	return 0;
}
```


---

## 作者：lfxxx (赞：0)

简单题。

题意简单转化后变为求存在多少个颜色对 $(a,b)$ 满足存在一个只有颜色 $a,b$ 的点构成的奇环。

对于只有一种颜色构成的奇环，可以简单 dfs。

对于至少由两种颜色 $a,b$ 构成的奇环，注意到至少存在一条两个端点颜色分别为 $a,b$ 的边，于是只用 check $O(m)$ 种情况。

对于每种情况，不妨把两个端点分别为颜色 $a,b$ 的边视作特殊边，两个端点分别为颜色 $a,a$ 或颜色 $b,b$ 的边视为平凡边，还是考虑去 dfs 染色 check，注意到每条特殊边只会在一种情况中被 check，而平凡边则会在多种情况中出现，我们考虑加速一下在平凡边上 dfs 的过程。

注意到对于一个由平凡边构成的连通块而言，其中一个点的颜色被确定后整个连通块内所有点颜色都被确定，这是因为假若预先给每个由平凡边构成的连通块内所有点染色后，当连通块内某个点的真实颜色被确定，剩余点颜色只与其预先染的颜色有关。

这说明同色点是等价的！考虑缩起一个连通块中所有同色点后再去对特殊边涉及的连通块 dfs 即可做到 $O(n + m \log m)$，瓶颈在排序。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e6+114;
vector<int> E[maxn];
pair<int,int> e[maxn];
vector<int> edge[maxn];
int n,m,k;
int K,del[maxn];
int c[maxn];
int tot=1;
int ans;
int col[maxn];
void dfs(int u,int cl){
    col[u]=cl;
    for(int v:E[u]){
        if(col[v]==0) dfs(v,cl^1);
        else if(col[v]!=(cl^1)) del[c[u]]=true;
    }
}
int lst;
int flag;
int chi[maxn];
void fan(int u,int cl){
    chi[u]=cl;
    for(int v:edge[u]){
        if(chi[v]==0) fan(v,cl^1);
        else if(chi[v]!=(cl^1)) flag=true;
    }
}
bool cmp(pair<int,int> x,pair<int,int> y){
    if(c[x.first]!=c[y.first]) return c[x.first]<c[y.first];
    else return c[x.second]<c[y.second];
}
int main(){
    cin>>n>>m>>k;
    K=k;
    for(int i=1;i<=n;i++) cin>>c[i];
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        if(c[u]<c[v]) swap(u,v);
        e[i]=make_pair(u,v);
        if(c[u]==c[v]) E[u].push_back(v),E[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(col[i]==0){
            tot++;
            dfs(i,tot);
            tot++;
        }
    }
    for(int i=1;i<=k;i++){
        if(del[i]==1) K--;
    }
    if(K<=1){
        cout<<0<<'\n';
        return 0;
    }
    sort(e+1,e+m+1,cmp);
    for(int i=1;i<=m;i++){
        if(i==m||(c[e[i].first]!=c[e[i+1].first]||c[e[i].second]!=c[e[i+1].second])){
            //[lst+1,i]
            if(c[e[i].first]!=c[e[i].second]&&del[c[e[i].first]]==0&&del[c[e[i].second]]==0){
                vector<int> S;
                for(int j=lst+1;j<=i;j++) S.push_back(col[e[j].first]),S.push_back(col[e[j].second]),edge[col[e[j].first]].push_back(col[e[j].second]),edge[col[e[j].second]].push_back(col[e[j].first]);
                for(int x:S) edge[x].push_back(x^1);
                flag=false;
                for(int x:S){
                    if(chi[x]==0){
                        fan(x,2);
                    }
                }
                if(flag==true) ans--;
                for(int x:S) chi[x]=0,edge[x].clear(),chi[x^1]=0,edge[x^1].clear();
            }
            lst=i;
        }
    }
    cout<<1ll*K*(K-1)/2+ans<<'\n';
    return 0;
}
```

---

## 作者：Engulf (赞：0)

这题是昨晚做的，现在补一下题解。

这是**不用**可撤销并查集的做法。

首先要知道，一个图是二分图等价于这个图没有长度为奇数的环。

不妨对每一组的导出子图染色，看看它是不是二分图。如果它自己都不是二分图，和别的组组成的导出子图又怎么可能是二分图呢。

去掉这样的组，假设剩下 $k'$ 个组。每次合并两组判定导出子图是不是二分图比较麻烦，不妨考虑容斥，如果能算出合并之后不是二分图，也即形成了奇环的组的对数 $c$，答案就是 $C_{k'}^2 - c = \dfrac{k'(k' - 1)}{2} - c$。

似乎还是要 $O(k'^2)$ 枚举组对？其实不然，因为连接剩下的组之间的边最多只有 $m' \le m$ 条，不妨对这 $m'$ 条边排序，使得连接某两组的边全部紧挨着，方便统计。

设想一下现在我们找到了连接两个**组** $(x, y)$ 的一条边 $(u, v)$，也即 $u$ 的组别是 $x$，$v$ 的组别是 $y$。

![](https://cdn.luogu.com.cn/upload/image_hosting/5k4idg4t.png)

看绿色的边。我们之前染过一次色，图上显示的就是染色后的结果。

- 如果 $u$ 的颜色和 $v$ 的颜色相同，则 $u$ **所在的连通块**和 $v$ **所在的连通块**的所有连接都必须是**相同颜色**连接，这两个连通块合并起来才有可能是一个二分图，不妨把 $v$ 所在的连通块颜色全部反转，这个图就是完成了正确的黑白染色，也即是二分图。
- 如果 $u$ 的颜色和 $v$ 的颜色不同，同理可得 $u$ **所在的连通块**和 $v$ **所在的连通块**的所有连接都必须是**不同颜色**连接，这两个连通块合并起来才有可能是一个二分图。

而遗憾的是，根据上面的图，$(x, y)$ 并不是一个合法的组对。

对每个连通块进行编号，用扩展域并查集或带边权并查集去维护这个关系。

记 $a$ 是 $u$ 所在的连通块编号，$b$ 是 $v$ 所在的连通块编号。

代码中，
如果 $u$ 的颜色和 $v$ 的颜色不同，视为 $a$ 和 $b$ 是**同类**。否则视为**异类**。并查集可以轻松维护这个关系。这个不会的话去做食物链或者关押罪犯或者团伙。

遍历完连接一组 $(x, y)$ 的所有边后，如果出现了矛盾，说明这组是不合法的，答案减去 $1$。

每次都只初始化需要用的并查集节点，就不用可撤销并查集了。时间复杂度 $O(n + k + m\log m)$。

代码没看懂就问我，写得有点乱。到后面变量名都是乱取的。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 1e6 + 5;

int fa[N << 1];
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
void merge(int x, int y) {if (find(x) != find(y)) fa[find(x)] = find(y);}

int n, m, k;

int bel[N];
vector<int> c[N];
vector<int> cc[N];

vector<int> g[N];

bool vis[N];
int col[N];

bool valid[N];

int tot;
int id[N];

bool bfs(int s, int b) {
    queue<int> q;
    q.push(s);
    col[s] = 0;
    ++tot;
    cc[b].emplace_back(tot);
    id[s] = tot;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = 1;
        id[u] = tot;
        for (auto v: g[u]) {
            if (bel[v] != b) continue;
            if (col[v] == -1) {
                col[v] = col[u] ^ 1;
                q.push(v);
            } else if (col[u] == col[v]) return false;
        }
    }
    return true;
}

pii e[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) cin >> bel[i], c[bel[i]].emplace_back(i);

    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        e[i] = {u, v};
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    for (int i = 1; i <= n; i++) col[i] = -1;

    int sati = k;

    for (int i = 1; i <= k; i++) {
        valid[i] = 1;
        for (auto j: c[i])
            if (!vis[j]) {
                valid[i] &= bfs(j, i);
                if (!valid[i]) {sati--; break;}
            }
    }

    ll ans = 1ll * sati * (sati - 1) / 2;

    vector<pii> edges;
    for (int i = 1; i <= m; i++) {
        int u = e[i].first, v = e[i].second;
        if (!valid[bel[u]] || !valid[bel[v]]) continue;
        if (bel[u] == bel[v]) continue;
        if (bel[u] > bel[v]) swap(u, v);
        edges.emplace_back(u, v);
    }

    sort(edges.begin(), edges.end(), [](pii x, pii y) {return bel[x.first] != bel[y.first] ? bel[x.first] < bel[y.first] : bel[x.second] < bel[y.second];});

    for (int i = 0; i < edges.size(); i++) {
        for (auto x: cc[bel[edges[i].first]])
            fa[x] = x, fa[x + tot] = x + tot;
        for (auto x: cc[bel[edges[i].second]])
            fa[x] = x, fa[x + tot] = x + tot;
        int j = i;
        bool skip = false;
        while (j < edges.size() && bel[edges[j].first] == bel[edges[i].first] && bel[edges[j].second] == bel[edges[i].second]) {
            int u = edges[j].first, v = edges[j].second;
            if (!skip) {
                if (col[u] == col[v]) {
                    if (find(id[u]) == find(id[v] + tot) || find(id[v]) == find(id[u] + tot))
                        skip = true;
                    fa[find(id[u])] = find(id[v]);
                    fa[find(id[u] + tot)] = find(id[v] + tot);
                } else {
                    if (find(id[u]) == find(id[v]) || find(id[u] + tot) == find(id[v] + tot))
                        skip = true;
                    fa[find(id[u])] = find(id[v] + tot);
                    fa[find(id[v])] = find(id[u] + tot);
                }
            }
            j++;
        }
        i = j - 1;
        ans -= skip;
    }

    cout << ans << "\n";

    return 0;
}
```

---

## 作者：shinkuu (赞：0)

可撤销并查集好题。

首先考虑如果已经确定选哪两组，该怎么判断。发现是一个二分图判定的问题，拓展域并查集即可。

那如果要求出所有可能的两组的答案怎么办。首先，如果两组中至少有一组，在只加入组内边时就已经不可能是二分图了，这种情况就显然是不行的。

否则，可以考虑预先加入所有组内的连边，枚举每一种出现过的组之间的边，并加入所有同种的边，再判定是否是二分图。

但是这样有个问题：判定每一对组时，都要将并查集数组初始化，时间会爆炸。于是考虑使用可撤销并查集撤销加边操作，就可以解决了。

注意还要判断之间没有连边的组，这种就直接判断各自是否是二分图即可。

总时间复杂度 $O(m\log(n+m))$。

code：

```cpp
int n,m,k,s,top,fa[N],st[N],vl[N],c[N];
bool vis[N];
mt19937 rnd(time(0));
struct node{int u,v;}e[N];
int find(int x){return fa[x]==x?x:find(fa[x]);}
il void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y)return;
	if(vl[x]>vl[y])swap(x,y);
	fa[x]=y,st[++top]=x;
}
il bool cmp(node x,node y){return c[x.u]!=c[y.u]?c[x.u]<c[y.u]:c[x.v]<c[y.v];}
void Yorushika(){
	scanf("%d%d%d",&n,&m,&k);
	rep(i,1,n)scanf("%d",&c[i]);
	rep(i,1,n*2)fa[i]=i,vl[i]=rnd();
	mems(vis,1);
	rep(i,1,m){
		int u,v;scanf("%d%d",&u,&v);
		if(c[u]==c[v]){
			if(find(u)==find(v))vis[c[u]]=0;
			merge(u,v+n),merge(u+n,v);
		}else{
			if(c[u]>c[v])swap(u,v);
			e[++s]=(node){u,v};
		}
	}
	sort(e+1,e+s+1,cmp);
	ll ans=0;
	rep(i,1,k)ans+=vis[i];
	ans=ans*(ans-1)/2;
	bool fl=1;
	top=0;
	rep(i,1,s){
		int u=e[i].u,v=e[i].v;
		if(find(u)==find(v))fl=0;
		merge(u,v+n),merge(u+n,v);
		if(c[u]==c[e[i+1].u]&&c[v]==c[e[i+1].v])continue;
		if(!vis[c[u]]||!vis[c[v]]){
			while(top)fa[st[top]]=st[top],top--;
			fl=1;continue;
		}
		ans-=!fl,fl=1;
		while(top)fa[st[top]]=st[top],top--;
	}
	printf("%lld\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

