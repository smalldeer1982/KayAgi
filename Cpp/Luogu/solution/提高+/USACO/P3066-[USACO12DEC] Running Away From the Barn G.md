# [USACO12DEC] Running Away From the Barn G

## 题目描述

给定一颗 $n$ 个点的有根树，边有边权，节点从 $1$ 至 $n$ 编号，$1$ 号节点是这棵树的根。

再给出一个参数 $t$，对于树上的每个节点 $u$，请求出 $u$ 的子树中有多少节点满足该节点到 $u$ 的距离不大于 $t$。

## 说明/提示

#### 数据规模与约定

对于全部的测试点，保证：

- $1 \leq n \leq 2 \times 10^5$，$1 \leq t \leq 10^{18}$。
- $1 \leq p_i \lt i$，$1 \leq w_i \leq 10^{12}$。



## 样例 #1

### 输入

```
4 5 
1 4 
2 3 
1 5 
```

### 输出

```
3 
2 
1 
1 
```

# 题解

## 作者：Kelin (赞：32)

题意:给出以1号点为根的一棵有根树,问每个点的子树中与它距离小于等于l的点有多少个

注意输入格式是输入fa[i]&dis[fa[i],i],因为特殊的输入格式,似乎连DFS都不要

法1:如果dep[u]-dep[v]<=len那么u->v路径上的点都要+1,这样我们就可以倍增求出最远的点然后差分就ok了

法2:先把dep,dfs序算出,然后按dep降序排序.对于每个点,需要删除深度相差超过L的点,并加入当前点,在子树中统计答案.(树状数组)

法3:主席树,dep[v]-dep[u]<=L(v∈u)=>dep[v]<=L+dep[u]=>静态区间查询小于某个数的个数 上主席树

法4:树套树,外层区间线段树,内层权值线段树 来做法3的算法

法5:左偏树,先dfs求出dep,再按dfs序倒过来操作

似乎好像,树套树的做法是可以做带修改的,主席树的做法是可以在线给L做的


---

## 作者：Treaker (赞：18)

$$\color{cornflowerblue}{\mathcal{Treaker}}$$

有一种比较神奇的树上差分的思路。

我们考虑一个点会被怎么样的点计入答案，当且仅当那个点是他的祖先，并且距离$~\le~$l。

但是由于权值是正的，那么这些点在树上必然是一段区间（在这里一个点也可以算作一段区间）。

对于树上的区间修改问题，我们直接用树上差分就行了。

然后最后在统计答案就好了。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
inline ll read()
{
	ll x = 0 , f = 1;	char ch = getchar();
	while(ch < '0' || ch > '9')	{if(ch == '-')	f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
	return x * f;
}
const int N = 2e5+5;
int n;
ll l;
int fa[N][20] , val[N];
ll dis[N];
struct Tree
{
	void get_fa(int x) { for(int i = 1;i <= 19;i ++) fa[x][i] = fa[fa[x][i - 1]][i - 1];}
	inline void work(int x)
	{
		val[x] ++; ll tmp = l;
		for(int i = 19;i >= 0;i --) if(dis[x] - dis[fa[x][i]] <= tmp) tmp -= dis[x] - dis[fa[x][i]] , x = fa[x][i];
		if(x != 1) val[fa[x][0]] --;
	}
	inline void LOL()
	{
		n = read(); l = read(); fa[1][0] = 1;
		for(int i = 2;i <= n;i ++) fa[i][0] = read() , dis[i] = dis[fa[i][0]] + read() , get_fa(i);
		for(int i = 1;i <= n;i ++) work(i);
		for(int i = n;i > 1;i --) val[fa[i][0]] += val[i];
		for(int i = 1;i <= n;i ++) printf("%d\n",val[i]);
	}
}DNF;
int main() { return DNF.LOL() , 0;}
```


---

## 作者：沧海映繁星 (赞：9)

~~这是一个极其良（dú）心（liú）的题目~~

首先，当本蒟蒻第一眼看到这个题目的时候，首先想到的就是：暴力枚举每个节点的子树中的合法节点个数

不过显然，看看那2 × $10 ^ 5$的数据范围，暴力枚举显然是会T炸的

那么究竟应该怎么做呢？

让我们来将这个题目换成一个生动形象的说法：

有一户人家，给定他们的父亲和他们的父亲比他们大的岁数，求家中每个人在他的直系后代比他小了不超过t岁的人的数量（描述可能有点不准确，了解就行）

原本的题目中，是让长辈们去找后辈；但是，孝顺是中华名族的传统美德，身为一个孝顺的好孩子，我们怎么能让长辈们找我们呢？我们应该自己找长辈。

好吧，开玩笑的。

但，我们确实可以通过逆向思维，将统计子树中合法节点的个数，改为从每个节点，将合法的祖先节点加上1

让我们先来看看这个题目里的样例

![](https://cdn.luogu.com.cn/upload/image_hosting/lebpkxe8.png)

不难发现，其实每节点能产生贡献的祖先，都在从该节点到根节点的路径上，并且都是从该节点开始的连续节点

题目分析到这里，我们已经不难发现这是一道树上差分的题目

#不会树上差分的同学请移步此处：[树上差分](https://www.cnblogs.com/gzh-red/p/11185914.html)

接下来，找出距离每个节点最远，且距离不超过t的节点，再进行差分即可

但是，这样就能AC了吗？

计算一下时间复杂度，从每个节点暴力找祖先，如果是一条链的话，就像这样:

![](https://cdn.luogu.com.cn/upload/image_hosting/6nev4zsk.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

不难发现，这样的时间复杂度还是 O（$n^2$）

~~嗯，在本题良（dú）心（liú）的数据面前还是会卡成孙子~~

所以说，我们还得进行优化

怎么做呢？

谁规定一次只能跳一格了？

反正也只需要找出最远的那个节点，我们可以使用倍增进行优化，一次跳 $2^n$ 格

#不会倍增的同学请移步这里：[倍增](https://blog.csdn.net/dong_qian/article/details/81702697)

这样，世界复杂度就能优化为：O(n logn) 刚好可以过

下面上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 500005
#define int long long
struct node{
    int w,next,to;
}a[maxn];
int n,t,P,W,tot,head[maxn];
int fa[maxn][30],h[maxn],s[maxn];
int f[maxn],ans[maxn];
void add(int l,int r,int w){
    a[++tot].next = head[l];
    a[tot].to = r;
    a[tot].w = w;
    head[l] = tot;
}
void build(int p,int last){
    fa[p][0] = last;
    h[p] = h[last] + 1;
    for(int i = 1; i <= 20; i++)fa[p][i] = fa[fa[p][i - 1]][i - 1];
    for(int i = head[p]; i; i = a[i].next){
        if(a[i].to != last){
            s[a[i].to] = s[p] + a[i].w;
            build(a[i].to,p);
        }
    } 
    return;
}
int far(int p){
    int k = p;
    for(int i = 20; i >= 0; i--){
        if(s[p] - s[fa[k][i]] <= t){
            k = fa[k][i];
        }
    }
    return k;
}
void query(int p,int last){
    for(int i = head[p]; i; i = a[i].next){
        if(a[i].to != last){
            query(a[i].to,p);
            ans[p] += ans[a[i].to];
        }
    }
    ans[p] += f[p];
    return;
}
signed main(){
    scanf("%lld%lld",&n,&t);
    for(int i = 2; i <= n; i++){
        scanf("%lld%lld",&P,&W);
        add(P,i,W);
        add(i,P,W);
    }
    build(1,0);
    s[0] = -99999999;
    for(int i = 1; i <= n; i++){
        int k = far(i);
        f[i]++;
        f[fa[k][0]]--;
    }
    query(1,0);
    for(int i = 1; i <= n; i++) printf("%lld\n",ans[i]);
    return 0;
}
```


---

## 作者：zhzh2001 (赞：6)

## 思路


这题也有很多方法，其实并不用可并堆。类似于上一种方法，计算出dfs序和每个点的深度，然后按深度降序排序。对于每个点，需要删除深度相差超过L的点，并加入当前点，在子树中统计答案。而这些用树状数组就可以了（单点修改+区间查询）。时间复杂度$O(N\log N)$


当然，还有一种更加巧妙的方法。用倍增求出$2^i$步祖先，然后就可以找到第一个距离超过L的祖先，用差分区间加，最后就能算出答案。时间复杂度也是$O(N\log N)$，下面提供了官方题解中的这种方法的代码供参考。


## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,id[N],r[N],now,ans[N];
pair<long long,int> a[N];
struct BIT
{
    int tree[N];
    void modify(int x,int val)
    {
        for(;x<=n;x+=x&-x)
            tree[x]+=val;
    }
    int query(int x)
    {
        int ans=0;
        for(;x;x-=x&-x)
            ans+=tree[x];
        return ans;
    }
}T;
//树状数组模板
vector<pair<int,long long>> mat[N];
void dfs(int k)
{
    id[k]=++now;
  //dfs序
    for(auto e:mat[k])
    {
        a[e.first]=make_pair(a[k].first+e.second,e.first);
        dfs(e.first);
    }
    r[k]=now;
  //结束时间戳
}
int main()
{
    long long l;
    cin>>n>>l;
    for(int i=2;i<=n;i++)
    {
        int p;
        long long w;
        cin>>p>>w;
        mat[p].push_back(make_pair(i,w));
    }
    a[1]=make_pair(0ll,1);
    dfs(1);
    sort(a+1,a+n+1);
    int j=n;
    for(int i=n;i;i--)
    {
        for(;a[j].first-a[i].first>l;j--)
            T.modify(id[a[j].second],-1);
      //删除超过距离超过L的点
        T.modify(id[a[i].second],1);
      //插入当前点
        ans[a[i].second]=T.query(r[a[i].second])-T.query(id[a[i].second]-1);
      //统计子树答案
    }
    for(int i=1;i<=n;i++)
        cout<<ans[i]<<endl;
    return 0;
}
```

官方题解中的代码：


```pascal
var ans,d:array[0..200333]of int64;
    i,n,j,v:longint;
    len:int64;
    p:array[0..200333,0..19]of longint;
  begin
    assign(input,'runaway.in');reset(input);
    assign(output,'runaway.out');rewrite(output);
    read(n,len);
    ans[1]:=1;
    for i:=2 to n do
      begin
        read(p[i,0]);
        read(d[i]);
        d[i]:=d[i]+d[p[i,0]];
        //计算深度
        for j:=1 to 18 do
          p[i,j]:=p[p[i,j-1],j-1];
          //倍增求祖先
        v:=i;
        for j:=18 downto 0 do
          if d[i]-d[p[v,j]]<=len then v:=p[v,j];
          //找到最远的距离不超过L的祖先
        inc(ans[i]);
        dec(ans[p[v,0]]);
        //差分
      end;
    for i:=n downto 1 do
      ans[p[i,0]]:=ans[p[i,0]]+ans[i];
    for i:=1 to n do
      Writeln(ans[i]);
  end.
```

---

## 作者：NaVi_Awson (赞：6)

简要来说，左偏树

具体思想是：先Dfs求出根节点到各个节点的距离，再按逆Dfs时间戳顺序进行操作（为了使得处理的当前节点的所有子节点均被处理过，至于为何不正向，就不解释了）

建大根堆，每次做完合并操作后，将不可行的边从堆中弹出（即堆顶所表示的点到当前点的距离>L（同时以操作顺序为前提的条件下必有“相距距离=两点到根节点的距离差”））

另一个需要解决的问题就是如何求解，我们可以按逆Dfs序模拟一个回溯过程：将所以pop掉的值和其子节点的值累加，再相减即可。

详见（完美的100行）又蛇又皮的代码，必要处有注释：





```cpp
#include<cmath>
#include<queue>
#include<stack>
#include<ctime>
#include<cstdio>
#include<string>
#include<cstdlib>
#include<iostream>
#include<algorithm>
 using namespace std;
const long long N=200000;
struct tt
{
    long long cost,next,to;
}edge[2*N+5];//保存边的信息 
long long path[N+5],top;
struct node
{
    long long key,dist;
    node *l,*r;
    long long ldist() {return l ? l->dist:-1;}
    long long rdist() {return r ? r->dist:-1;}
}T[N+5],*root[N+5];//T[i]表示节点i的相关信息;root[i]表示序号为i的节点所在堆的根的地址 
long long n,l,a,b;
long long remain[N+5],tail,Rank[N+5];//remain[]表示逆Dfs顺序,tail表示remain[]的大小;Rank[]表示Bfs序 
long long popnum[N+5],cnt[N+5];//popnum[i]保存在i节点时,弹出元素的数量 cnt[i]表示以i为根，其子树节点数量(不含根节点) 
void Add(long long x,long long y,long long cost);
void Dfs(long long x);
node* Merge(node* a,node* b);
int main()
{
    scanf("%lld%lld",&n,&l);
    for (long long i=2;i<=n;i++)
    {
        scanf("%lld%lld",&a,&b);
        Add(a,i,b);
        Add(i,a,b);
```
}//连双向边,正向用于Dfs用,逆向用于求解用

```cpp
    Rank[1]=1;
    Dfs(1);
    for (long long i=1;i<=tail;i++) 
    {
        for (long long j=path[remain[i]];j;j=edge[j].next)
        {
            if (Rank[remain[i]]==Rank[edge[j].to]+1)//找到前驱节点 
            {
                root[edge[j].to]=Merge(root[remain[i]],root[edge[j].to]);//将当前节点构成的堆并入前驱节点 
                while(root[edge[j].to]->key-T[edge[j].to].key>l)//弹出 
                {
                    popnum[edge[j].to]++;
                    root[edge[j].to]=Merge(root[edge[j].to]->l,root[edge[j].to]->r);
                }
            }
        }
    }
    for (long long i=1;i<=tail;i++) //对最终答案数据的处理 
    {
        for (long long j=path[remain[i]];j;j=edge[j].next)
        {
            if (Rank[remain[i]]==Rank[edge[j].to]+1)
            {
                cnt[edge[j].to]+=cnt[remain[i]]+1;
                popnum[edge[j].to]+=popnum[remain[i]];
            }
        }
    }
    for (long long i=1;i<=n;i++) printf("%lld\n",cnt[i]+1-popnum[i]);
    return 0;
}
void Add(long long x,long long y,long long cost)
{
    edge[++top].to=y;
    edge[top].cost=cost;
    edge[top].next=path[x];
    path[x]=top;
}
void Dfs(long long x)
{
    root[x]=x+T;
    for (long long i=path[x];i;i=edge[i].next) if (!Rank[edge[i].to])
    {
        Rank[edge[i].to]=Rank[x]+1;
        T[edge[i].to].key=T[x].key+edge[i].cost;//key保存的是根节点到该点的距离 
        Dfs(edge[i].to);
    }
    remain[++tail]=x;
}
node* Merge(node* a,node* b)
{
    if (!a||!b) return a ? a:b;
    if (a->key<b->key) swap(a,b);
    a->r=Merge(a->r,b);
    if (a->ldist()<a->rdist()) swap(a->l,a->r);
    a->dist=a->rdist()+1;
    return a;
}
```

---

## 作者：天泽龟 (赞：5)

## 好像很久没有写主席树了，临近省选之际通过写这道题回顾一下一些基础做法。

**题意：** 给出以1号点为根的一棵有根树,问每个点的子树中与它距离小于等于l的点有多少个

**分析：**

根据题目$dep[v]<=L+dep[u]$一式的变形，我们的思路可以向找一个数据结构，它可以在一个子树内维护$[dep[u],dep[u]+L]$区间的点数量并快速求出。

如果没有子树的限制，我们可以利用**线段树，以深度为下标，通过一个$dfs$找到并顺手维护当前深度的点个数**，给人感觉是这样的：

```cpp

void dfs(int u)  //有向图不必判父亲
{
	size[u]=1; add(1,1,maxd,d[u],1);//将当前深度点个数加1
	for (int i=fir[u];i;i=e[i].next) {
		addt(e[i].u); size[u]+=size[e[i].u];
	} 
}
```
**可以注意到d[u]可能会非常非常大，所以我们要先对其离散化。。**



但是现在有了子树限制~~就不会做了~~，我们可以想到**主席树**可以支持对于历史信息的追查，从而利用前缀和的思想，搞出一个子树的信息。

~~不用说我都知道上面的话十分的拗口难懂~~，可以简单的举一个例子：

![](https://cdn.luogu.com.cn/upload/pic/55862.png)

如图，假如我们要求节点为2的子树，我们应该如何去处理？

1. 我们通过dfs到1，在此处建一颗主席树，维护[1]组成的子树，可以得到深度为0的有1个。

2. 我们通过dfs到5（或3，看你怎么建图）,再建一颗主席树，维护[1,2,3,5]的子树，可以得到深度为0的有1，深度为1的有1，深度为2的有2。

3. 把两颗主席树情况一减，得到一棵由[2,3,5]组成的子树，深度为1的有1，深度为2的有2。这正是子树的信息。

大概就是以上这样。。我们可以看出来此时我们是以**dfs序为时间轴**，所以在dfs时的时候还要开一个数组存他的dfs序，否则查询的时候不方便。

此外，一个点的子树dfs序范围为$[dfs[i]-1,dfs[i]+size[i]-1]$，这个应该很容易看出来。。

**可能会是一些坑点/优化：**

1. 其实你离散化后二分$L+dep[u]$可能回比最大深度还大。可以通过在离散化数组后面加一个$inf$，如果你查到inf了说明你的子树你都可以达到，直接输出子树大小即可。

2. 别忘了$LL$...

3. lower_bound的范围是小于，题目要求小于等于，所以判断下一个深度能否达到，若能就加1.

**上丑陋的代码：**

```cpp
#include <iostream>
#include <algorithm>
#define maxn 200100
#define midd (l+r)/2
using namespace std;

struct ed{
	long long u,next;
}e[maxn*2];
long long n,m,ll,st,cnt,fir[maxn],fa[maxn],size[maxn],d[maxn],a[maxn],ha[maxn];
long long dfn[maxn],t,w[maxn*30],ls[30*maxn],rs[30*maxn],rt[maxn*30];
void add(long long x,long long y){
	e[++st].u=y; e[st].next=fir[x]; fir[x]=st;
}

long long buildd(long long l,long long r)
{
	long long now=++cnt; if (l==r) return now;
	ls[now]=buildd(l,midd); rs[now]=buildd(midd+1,r);
	return now;
}

long long build(long long pre,long long l,long long r,long long x)
{
	long long now=++cnt; w[now]=w[pre]+1; ls[now]=ls[pre]; rs[now]=rs[pre];
	if (l==r) return now; 
	if (x<=midd) ls[now]=build(ls[pre],l,midd,x);
	else rs[now]=build(rs[pre],midd+1,r,x);
	return now;
}

long long query(long long r1,long long r2,long long l,long long r,long long x,long long y)
{
	if (r<x||l>y) return 0;
	
	if (x<=l&&r<=y) return w[r2]-w[r1];
	return query(ls[r1],ls[r2],l,midd,x,y)+query(rs[r1],rs[r2],midd+1,r,x,y);
}

void addt(long long u)
{
	size[u]=1; long long dd=lower_bound(ha+1,ha+ll+1,d[u])-(ha+1)+1;
	dfn[u]=++t; rt[t]=build(rt[t-1],1,ll,dd);
	for (long long i=fir[u];i;i=e[i].next) {
		addt(e[i].u); size[u]+=size[e[i].u];
	} 
}

int main()
{
	cin>>n>>m; long long dd; ha[1]=0;
	for (long long i=2;i<=n;i++) 
		cin>>fa[i]>>dd,ha[i]=d[i]=dd+d[fa[i]],add(fa[i],i);
	ha[n+1]=2147483646;
	sort(ha+1,ha+n+2);
	ll=unique(ha+1,ha+n+2)-(ha+1);	
	rt[0]=buildd(1,ll); addt(1);
//building

	for (long long i=1;i<=n;i++)
	{
		long long k1=lower_bound(ha+1,ha+ll+1,d[i])-(ha+1);
		if (ha[k1+1]==d[i]) k1++;
		long long k=lower_bound(ha+1,ha+ll+1,d[i]+m)-(ha+1);
		if (ha[k+1]==d[i]+m) k++;
		if (k==ll-1) cout<<size[i]<<endl;
		else cout<<query(rt[dfn[i]-1],rt[dfn[i]+size[i]-1],1,ll,k1,k)<<endl;
	}
}
```

---

## 作者：Peter_Z (赞：3)

**博客内食用更佳：[qwq](https://blog.csdn.net/The_OIer/article/details/97908938)**

**题目链接：[传送门](https://www.luogu.org/problem/P3066)**

## 题目大意：

给出以$1$号点为根的一棵有根树，问每个点的子树中与它距离小于等于$L$的点有多少个。

## 大致思路

在节点子树内，想到用dfs序。

询问距离$<=L$的点，想到用权值线段树。

又因为这里询问的是区间内距离$<=L$的点，因此要可持久化。

## 具体操作

考虑主席树的维护和查询：

令$dis[i]$表示第$i$个节点到根的距离。

第$i$棵主席树维护的是$dfs$序为$1～i$的节点的$dis$信息。

令$dfn[x]$表示$dfs$序中$x$出现的位置，$out[x]$表示$x$的子树中$dfs$序的最大值。

那么$x$的子树的区间就是$[dfn[x],out[x]]$。

然后按照$dfs$序建一棵主席树。

建完主席树后，假设当前节点到根距离为$dis[x]$，

则现在需要询问区间内有多少个节点到根距离$<=dis[x]+L$。

考虑主席树的性质，主席树维护了前缀信息。

因此答案就是

(前$out[x]$个节点有多少个到根距离$<=dis[x]+L$)

减去

(前$dfn[x]-1$个节点有多少个到根距离$<=dis[x]+L$)。

另外这里距离很大，离散化一下就可以了qwq。

~~丑陋的~~代码：

```cpp
#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<queue>
#define re register int
#define rl register ll
using namespace std;
typedef long long ll;
ll read() {
	rl x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9') {
		if(ch=='-')	f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9') {
		x=10*x+ch-'0';
		ch=getchar();
	}
	return x*f;
}
const int Size=200005;
const int LOG=20;
ll n,L,maxn,a[Size],b[Size],T[Size];
int cnt,tot,tim,head[Size],dfn[Size],out[Size];
struct Edge {
	int v,next;
	ll t;
} w[Size];
void AddEdge(int u,int v,ll t) {
	w[++cnt].v=v;
	w[cnt].t=t;
	w[cnt].next=head[u];
	head[u]=cnt;
}
void dfs(int x,ll d) {
	//a[i]表示dfs序为i的节点到根距离 
	dfn[x]=++tim;
	a[tim]=d;
	for(int i=head[x]; i; i=w[i].next) {
		int nxt=w[i].v;
		dfs(nxt,d+w[i].t);
	}
	out[x]=tim;
}
int ls[Size*LOG],rs[Size*LOG],sum[Size*LOG];
int update(int pre,int l,int r,int v) {
	int rt=++tot;
	ls[rt]=ls[pre]; rs[rt]=rs[pre];
	sum[rt]=sum[pre]+1;
	if(l<r) {
		int mid=(l+r)>>1;
		if(v<=mid) {
			ls[rt]=update(ls[pre],l,mid,v);
		} else {
			rs[rt]=update(rs[pre],mid+1,r,v);
		}
	}
	return rt;
}
int Query(int u,int v,int l,int r,int rt) {
	//主席树区间求和 
	if(u<=l && r<=v) {
		return sum[rt];
	}
	int mid=(l+r)>>1,ans=0;
	if(u<=mid)	ans+=Query(u,v,l,mid,ls[rt]);
	if(v>mid)	ans+=Query(u,v,mid+1,r,rs[rt]);
	return ans;
}
int main() {
	n=read();
	L=read();
	for(re i=2; i<=n; i++) {
		int p=read();
		ll t=read();
		AddEdge(p,i,t);
	}
	dfs(1,0);
	//离散化 
	memcpy(b,a,sizeof(a));
	sort(b+1,b+1+n);
	maxn=unique(b+1,b+1+n)-(b+1);
	for(re i=1; i<=n; i++) {
		int k=lower_bound(b+1,b+1+maxn,a[i])-b;
		//按照dfs序建出主席树 
		T[i]=update(T[i-1],1,maxn,k);
	}
	for(re i=1; i<=n; i++) {
		ll maxd=a[dfn[i]]+L;
		//查找一下a[dfn[i]]+L在去重后在离散化数组b中的位置 
		int alb=upper_bound(b+1,b+1+maxn,maxd)-b-1;
		int ans1=Query(1,alb,1,maxn,T[out[i]]);
		int ans2=Query(1,alb,1,maxn,T[dfn[i]-1]);
		printf("%d\n",ans1-ans2);
	}
	return 0;
}
```

---

## 作者：Akura (赞：3)

这道题有很多高级的做法~~，但是我都不会~~

而且还没有倍增+树上差分的题解，赶紧来补一发~

我们分析题目可以得出这样一条结论——对于当前节点$u$，$u$的子树中与$u$的距离大于$l$的点与$u$的所有祖先的距离都大于$l$($u$也是自己的祖先)。所以不难想到我们对于每个节点$u$，我们计算出$u$的第一个与它距离大于$l$的祖先$anc$，那么对于这个祖先，它的答案就要减去$size(u)$。$size$表示子树的节点数，初始化每个点的答案为子树的节点数。然后结合之前得到的性质，我们可以用树上前缀和的思想，把这个减去的$size(u)$累加到$anc$的祖先中去。

但是你会发现，直接算是有问题的。

首先对于$u$，它对$anc$的答案做了值为$-size(u)$的贡献，并且我们要将这个贡献累加到$anc$的祖先中去。然后我们发现，对于$u$的祖先，比如$u$的父亲$fa(u)$，第一个与$fa(u)$距离大于$l$的祖先也必定是$anc$的祖先，但我们将$-size(fa(u))$加到了这个祖先中，也就是说这个祖先的答案累加了两次$-size(u)$，答案显然是错的。如何避免呢？很简单，我们将$size(fa(u))$减去$size(u)$即可。那么问题就解决了。

对于求第一个距离大于$l$的祖先，我们可以用倍增来做，那么总的时间复杂度就是$O(NlogN)$。

*由于$size(fa(u))$减去的是$size(u)$原本的大小，而此时$size(u)$可能已经被$u$的子节点减去了一些，所以我们要再开一个$size$数组来记录原本的$size$。

*不开long long见祖宗

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#define maxn 200001
using namespace std;
 
struct edge{
    int to,next; long long dis;
    edge(){}
    edge(const int &_to,const long long &_dis,const int &_next){ to=_to,dis=_dis,next=_next; }
}e[maxn<<1];
int head[maxn],k;
 
int fa[maxn][20],size[maxn],size2[maxn],sum[maxn],maxdep;
int n;
long long m,dis[maxn][20];
 
inline long long read(){
    register long long x(0),f(1); register char c(getchar());
    while(c<'0'||'9'<c){ if(c=='-') f=-1; c=getchar(); }
    while('0'<=c&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
inline void add(const int &u,const int &v,const long long &w){ e[k]=edge(v,w,head[u]),head[u]=k++; }
 
void dfs(int u){
    size[u]=1;
    for(register int i=head[u];~i;i=e[i].next){
        int v=e[i].to;
        if(v==fa[u][0]) continue;
        fa[v][0]=u,dis[v][0]=e[i].dis;
        for(register int j=1;j<=maxdep;j++) fa[v][j]=fa[fa[v][j-1]][j-1],dis[v][j]=dis[v][j-1]+dis[fa[v][j-1]][j-1];
        dfs(v),size[u]+=size[v];
    }
}
 
void dfs_getsum(int u){
    for(register int i=head[u];~i;i=e[i].next){
        int v=e[i].to;
        if(v==fa[u][0]) continue;
        dfs_getsum(v);
        long long len=0; int tmp=size[v],tmp2=size2[v];
        for(register int j=maxdep;j>=0;j--) if(len+dis[v][j]<=m&&fa[v][j]) len+=dis[v][j],v=fa[v][j];
        if(len+dis[v][0]>m&&fa[v][0]) sum[fa[v][0]]+=tmp,size[u]-=tmp2;
    }
}
 
void dfs_getans(int u){
    for(register int i=head[u];~i;i=e[i].next){
        int v=e[i].to;
        if(v==fa[u][0]) continue;
        dfs_getans(v),sum[u]+=sum[v];
    }
}
 
int main(){
    memset(head,-1,sizeof head);
    n=read(),m=read();
    for(register int i=2;i<=n;i++){
        int v=read(); long long w=read();
        add(i,v,w),add(v,i,w);
    }
    maxdep=(int)log(n)/log(2),dfs(1);
    for(register int i=1;i<=n;i++) size2[i]=size[i];
     
    dfs_getsum(1);
    dfs_getans(1);
     
    for(register int i=1;i<=n;i++) printf("%d\n",size2[i]-sum[i]);
    return 0;
}
```


---

## 作者：hovny (赞：2)


## 解题思路

方法很多，比如楼上楼下讲的`左偏树`、`主席树`、`树上查分`

这里提供一种新的算法 $\large \to$ **树状数组+离散化**（并不用记录 $dfs$ 序

### 分析

求子树中到根的距离在一定范围内的点，可以对每棵子树用树状数组维护一个所有点到根的距离，查询时查询一定范围即可

但是明显这是不行的，**空间和时间都不允许**

考虑一下优化，**绝对距离**是没必要的，可以有**相对距离**来表示两点间的情况（也就是说，我们只需要知道两者的大小关系），因此可以预处理出每个点到 $root$ 的距离，排序后维护其离散值即可，查询时也可以用离散值来代替

再考虑对每个点维护子树信息的优化，不难发现，$dfs$ 实现时，对于一个点，$dfs$ 其子树前 和 完成后，对答案造成的影响只有子树里的信息，因此可以只开一个树状数组维护信息，每次记录 $dfs$ 前后的结果，两者之差即为答案

### 实现过程

1、先 $dfs$ 跑一遍，预处理出所有点到 $root(1)$ 的 $dis$ 值，用 $p$ 数组记录

2、将 $p$ 数组按升序排序

3、再次 $dfs$，用树状数组 $f$ 记录各点到 $root$ 距离的离散值，每次在访问一个节点的儿子前，查询该点能到最远距离的离散值，然后在树状数组中标记这个点的 $dis$，遍历子树，最后再次查询，两次查询之差即为该点的答案，因为只对该点子树进行的操作，不会产生额外的影响

```cpp
cur=lower_bound(p+1,p+t+1,dis[k])-p;//当前点的离散值
pos=lower_bound(p+cur,p+t+1,dis[k]+R)-p;//最远能到的点的离散值
if(p[pos]>dis[k]+R) --pos;//要求 小于等于
res=Query(pos),Modify(cur);//先查询，再修改
. . .
Ans[k]=Query(pos)-res;//再次查询，记录两次查询的差为答案
```

### warning

1、记得开 $long\ long $

2、$1$ 到 $root$ 的 $dis$ 值，虽然是 $0$ 也要记录，否则会影响上述过程中 $cur$ 的值，间接影响答案，如下图情况，若题目中的 $L<10$ 则 $root$ 的答案会少 $1$ ，当然，也可以通过特判解决

![](https://hovnysilence.github.io/image/USACO12DEC-1.jpg)

## Code

```cpp
#include<bits/stdc++.h>
#define rgt register
#define LL long long
#define N 200003
using namespace std;
struct Edge{
	int to,nxt;
	LL dis;
	Edge(int a,int b,LL c):to(a),nxt(b),dis(c){}
	Edge(){}
}b[N];//记录边
int head[N],n,t;
int f[N],Ans[N];
LL dis[N],p[N],R;
inline LL read() {
	rgt LL s=0;
	rgt char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) s=(s<<1)+(s<<3)+c-'0',c=getchar();
	return s;
}
inline void add(rgt int x,rgt int y) {
	b[++t]=Edge(y,head[x],read()),head[x]=t;
}
inline void built(rgt int k) {//预处理dis
	p[++t]=dis[k];//1到root的距离也要加入
	rgt int i,to;
	for(i=head[k];i;i=b[i].nxt) {
		to=b[i].to,
		dis[to]=dis[k]+b[i].dis;
		built(to);
	}
}
inline int Query(rgt int x) {
	int res=0;
	for(;x;x-=x&(-x)) res+=f[x];
	return res;
}
inline void Modify(rgt int x) {
	for(;x<=t;x+=x&(-x)) ++f[x];
}
inline void solve(rgt int k) {
	rgt int i,to,cur,res,pos;
	cur=lower_bound(p+1,p+t+1,dis[k])-p;
	pos=lower_bound(p+cur,p+t+1,dis[k]+R)-p;//假装从cur开始查能省点时间
	if(p[pos]>dis[k]+R) --pos;
	res=Query(pos),Modify(cur);
	for(i=head[k];i;i=b[i].nxt)
		to=b[i].to,solve(to);
	Ans[k]=Query(pos)-res;
}
int main()
{
	int i;
	n=read(),R=read();//n点数，R距离
	for(i=2;i<=n;i++) add(read(),i);
	t=0,built(1),//第一遍dfs
	sort(p+1,p+t+1),solve(1);//第二遍dfs得出结果
	for(i=1;i<=n;i++) printf("%d\n",Ans[i]);
	return 0;
}
```

## 最后

如果题目没有 `子树中`的限制…

---

## 作者：Styx (赞：2)

没错，又是线段树合并的做法  
只需要把深度离散化一下，对每个点建一棵权值线段树，然后区间查询就可以了  
详细做法是在dfs到一个点的时候将这个点的深度插入该点对应的权值线段树，然后将所有子树的线段树合并到该点的线段树上，查询该点深度到该点深度$+l$的区间上有几个点就行了

代码如下：   
```cpp
#include<bits/stdc++.h>
#define lson tr[now].l
#define rson tr[now].r
#define pii pair<int,long long>
#define mp make_pair
using namespace std;

struct tree
{
    int l,r,sum;
}tr[5000020];
vector<pii> g[400010];
int n,cnt,cnt2,rt[400010],deep[400010],q[400010],ans[400010];
long long gg,tmp[400010],dis[400010];
int N=400000;

int push_up(int now)
{
    tr[now].sum=tr[lson].sum+tr[rson].sum;
}

int insert(int &now,int l,int r,int pos,int val)
{
    if(!now) now=++cnt;
    if(l==r)
    {
        tr[now].sum+=val;
        return 0;
    }
    int mid=(l+r)>>1;
    if(pos<=mid)
    {
        insert(lson,l,mid,pos,val);
    }
    else
    {
        insert(rson,mid+1,r,pos,val);
    }
    push_up(now);
}

int query(int now,int l,int r,int ll,int rr)
{
    if(ll<=l&&r<=rr)
    {
        return tr[now].sum;
    }
    int mid=(l+r)>>1;
    if(rr<=mid)
    {
        return query(lson,l,mid,ll,rr);
    }
    else
    {
        if(mid<ll)
        {
            return query(rson,mid+1,r,ll,rr);
        }
        else
        {
            return query(lson,l,mid,ll,mid)+query(rson,mid+1,r,mid+1,rr);
        }
    }
}

int merge(int a,int b,int l,int r)
{
    if(!a) return b;
    if(!b) return a;
    if(l==r)
    {
        tr[a].sum+=tr[b].sum;
        return a;
    }
    int mid=(l+r)>>1;
    tr[a].l=merge(tr[a].l,tr[b].l,l,mid);
    tr[a].r=merge(tr[a].r,tr[b].r,mid+1,r);
    push_up(a);
    return a;
}

int dfs(int now,int fa,long long dep)
{
    dis[now]=dep;
    tmp[++cnt2]=dep;
    tmp[++cnt2]=dep+gg;
    rt[now]=now;
    ++cnt;
    for(int i=0;i<g[now].size();i++)
    {
        if(g[now][i].first==fa) continue;
        dfs(g[now][i].first,now,dep+g[now][i].second);
    }
}

int solve(int now,int fa)
{
    insert(rt[now],1,N,deep[now],1);
    for(int i=0;i<g[now].size();i++)
    {
        if(g[now][i].first==fa) continue;
        solve(g[now][i].first,now);
        merge(rt[now],rt[g[now][i].first],1,N);
    }
    ans[now]=query(rt[now],1,N,deep[now],q[now]);
}

int init()
{
	sort(tmp+1,tmp+cnt2+1);
	int tot=unique(tmp+1,tmp+cnt2+1)-tmp-1;
	for(int i=1;i<=n;i++)
	{
		deep[i]=lower_bound(tmp+1,tmp+tot+1,dis[i])-tmp;
	}	
	for(int i=1;i<=n;i++)
	{
		q[i]=lower_bound(tmp+1,tmp+tot+1,dis[i]+gg)-tmp;
	}
}

int main()
{
	ios::sync_with_stdio(0);
    cin>>n>>gg;
    int from;
	long long to;
    for(int i=2;i<=n;i++)
    {
        cin>>from>>to;
        g[i].push_back(mp(from,to));
        g[from].push_back(mp(i,to));
    } 
    dfs(1,0,0);
	init();
    solve(1,0);
    for(int i=1;i<=n;i++)
    {
        cout<<ans[i]<<endl;
    }
}
```

---

## 作者：bztMinamoto (赞：2)

发现没有主席树的题解……来一发好了……感觉楼下讲的也不是很清楚……

安利一发[blog](https://www.cnblogs.com/bztMinamoto/p/9395186.html)

调了一个上午一直WA……狠下心来重打一遍居然直接一遍过……

先dfs一遍，把到根节点的距离算出来，然后建出树上的主席树

然后考虑，$d[v]-d[u]<=L$，$d[v]<=L+d[u]$

然后就是对于每一个$d[u]+L$查询一下区间内有多少比它小的就好

细节问题：因为不能保证$d[u]+L$在离散化后的数组内存在，所以要用upper_bound，并查询比它小的，而且要在离散化的数组后面加一个inf
```
//minamoto
#include<bits/stdc++.h>
#define N 200005
#define M 4000005
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline ll read(){
    #define num ch-'0'
    char ch;bool flag=0;ll res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
char obuf[1<<24],*o=obuf;
void print(int x){
	if(x>9) print(x/10);
	*o++=x%10+48;
}
int sum[M],L[M],R[M],rt[N];
int ver[N<<1],Next[N<<1],head[N];ll edge[N<<1];
int ls[N],rs[N];ll a[N],b[N];
int n,m,cnt,tot;ll p;
void update(int last,int &now,int l,int r,int x){
    sum[now=++cnt]=sum[last]+1;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(x<=mid) R[now]=R[last],update(L[last],L[now],l,mid,x);
    else L[now]=L[last],update(R[last],R[now],mid+1,r,x);
}
int query(int u,int v,int l,int r,int k){
    if(r<k) return sum[v]-sum[u];
    if(l>=k) return 0;
    int mid=(l+r)>>1;
    if(k<=mid) return query(L[u],L[v],l,mid,k);
    else return query(R[u],R[v],mid+1,r,k)+sum[L[v]]-sum[L[u]];
}
inline void add(int u,int v,ll e){
	ver[++tot]=v,Next[tot]=head[u],head[u]=tot,edge[tot]=e;
}
void dfs(int u,int fa,ll d){
	b[ls[u]=++m]=d,a[m]=d;
	for(int i=head[u];i;i=Next[i])
	if(ver[i]!=fa) dfs(ver[i],u,d+edge[i]);
	rs[u]=m;
}
int main(){
	n=read(),p=read();
	for(int u=2;u<=n;++u){
		int v=read();ll e=read();
		add(v,u,e);
	}
	dfs(1,0,0);
	sort(b+1,b+1+m);
	m=unique(b+1,b+1+m)-b-1;
	for(int i=1;i<=n;++i){
		int k=lower_bound(b+1,b+1+m,a[i])-b;
		update(rt[i-1],rt[i],1,m,k);
	}
	b[m+1]=inf;
	for(int i=1;i<=n;++i){
		int k=upper_bound(b+1,b+2+m,a[ls[i]]+p)-b;
		k=query(rt[ls[i]-1],rt[rs[i]],1,m,k);
		print(k);
		*o++='\n';
	}
    fwrite(obuf,o-obuf,1,stdout);
    return 0;
}
```

---

## 作者：Dirt、 (赞：1)

题解区一片主席树/左偏树，害怕

考虑每个点对其祖先的贡献，发现对于节点 $i$ ，假设其深度最小且与 $i$ 深度之差 $\le L$ 的祖先为 $j$ ，那么 $i$ 对于从 $i$ 到 $j$ 的每个节点的答案都会产生贡献。

可以维护一个差分数组和节点祖先的倍增数组，对于节点 $i$ ，每次找到深度最大且与 $i$ 深度之差 $>L$ 的节点，将该节点对应的差分数组值 -1，$i$ 节点对应的值 +1 即可。

因为读入时已经确定了父子关系，可以动态地维护深度和倍增数组。

最后统计答案即可。

注意：初始时节点 1 的差分数组值为 1 ，因为 1 在它自己的子树内。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=200005;
int n;
ll m;
int cnt;
int head[N];
struct Edge{
	int nxt,to;
}e[N];
int idx;
int poi[N];
int f[N][23];
ll dis[N];
int dlt[N];
void add(int u,int v)
{
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
int find(int x)
{
	int now=x;
	for(int j=20;j>=0;j--)
		if(dis[x]-dis[f[now][j]]<=m) now=f[now][j];
	return f[now][0];
}
void dfs(int x)
{
	idx++;
	poi[idx]=x;
	for(int i=head[x];i;i=e[i].nxt)
		dfs(e[i].to);
}
int main()
{
	scanf("%d%lld",&n,&m);
	dlt[1]=1;
	for(int i=2;i<=n;i++)
	{
		int x;ll w;
		scanf("%d%lld",&x,&w);
		add(x,i);
		f[i][0]=x;
		dis[i]=dis[x]+w;
		for(int j=1;j<=20;j++)
			f[i][j]=f[f[i][j-1]][j-1];
		dlt[i]++;
		dlt[find(i)]--;
	}
	dfs(1);
	for(int i=n;i;i--)
		dlt[f[poi[i]][0]]+=dlt[poi[i]];
	for(int i=1;i<=n;i++)
		printf("%d\n",dlt[i]);
	return 0;
}
```



---

## 作者：Santiego (赞：1)

~~55行左偏树吊打主席树、树套树~~


题意：给出以1号点为根的一棵有根树，问每个点的子树中与它距离小于等于l的点有多少个。

注意到答案的两个性质：

- 一个点的所有答案一定**包含**在其所有儿子的答案中
- 如果节点$i​$当前满足条件，那么所有距离（相对于根节点）比它小的节点当前也都满足（所以建个大根堆）

所以考虑使用左偏树，每个节点都建个大根堆，在$dfs$时计算出所有点深度，再利用这些性质回溯时依次合并所有堆，显然答案即为堆的大小。

注意`long long`~~卡了我好久~~


```cpp
#include <cstdio>
#include <algorithm>
#define MAXN 200002
#define LL long long
using namespace std;
int n;long long l;
int head[MAXN],nxt[MAXN*2],vv[MAXN*2],tot;
LL ww[MAXN*2];
inline void add_edge(int u, int v, LL w){
    ww[++tot]=w;
    vv[tot]=v;
    nxt[tot]=head[u];
    head[u]=tot;
}
LL val[MAXN];
int root[MAXN],sz[MAXN],sl[MAXN],sr[MAXN],dis[MAXN];
int merge(int a, int b){
    if(a==0||b==0) return a+b;
    if(val[a]<val[b]) swap(a,b);
    sr[a]=merge(sr[a], b);
    if(dis[sl[a]]<dis[sr[a]]) swap(sl[a], sr[a]);
    dis[a]=dis[sr[a]]+1;
    return a;
}
void dfs(int u, LL wnow){
    root[u]=u;
    val[u]=wnow;
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=vv[i];
        LL w=ww[i];
        dfs(v, wnow+w);
        root[u]=merge(root[u], root[v]);
        sz[u]+=sz[v];
        while(val[root[u]]-val[u]>l){
            root[u]=merge(sl[root[u]], sr[root[u]]);
            sz[u]--;
        }
    }
}
int main()
{
    scanf("%d %lld", &n, &l);
    for(int i=2;i<=n;++i){
        int fa;LL w;
        scanf("%d %lld", &fa, &w);
        add_edge(fa,i,w);
    }
    dfs(1,0);
    for(int i=1;i<=n;++i)
        printf("%d\n", sz[i]);
    return 0;
}
```

---

## 作者：sdgzy (赞：1)

显然想到如果最大的小于等于L,那么比最大值小的一定可以.        
所以采用左偏树维护.     
考虑怎么样维护权值.    
左偏树可以通过打标记来维护这个点的权值 , 因为他满足堆的性质.    
所以维护一个lazy标记表示这个点需要下放的值.   
只需要在合并或者删除这个点的时候,下放即可.   
写的太丑了.跑的太慢了(捂脸)   
```cpp
/*1037ms -> 864ms*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define rep(i , x, p) for(int i = x;i <= p;++ i)
#define sep(i , x, p) for(int i = x;i >= p;-- i)
const int maxN = 1000000 + 7;
#define gc getchar()
#define pc putchar
#define ll long long
using std::min;
using std::max;
using std::swap;

inline int read() {int x = 0,f = 1;char c = gc;while(c < '0' || c > '9') {if(c == '-')f = -1;c = gc;}while(c >= '0' && c <= '9') {x = x * 10 + c - '0';c = gc;}return x * f;}
inline ll readll() {ll x = 0,f = 1;char c = gc;while(c < '0' || c > '9') {if(c == '-')f = -1;c = gc;}while(c >= '0' && c <= '9') {x = x * 10 + c - '0';c = gc;}return x * f;}
void print(int x) {if(x < 0) {pc('-');x = -x;}if(x >= 10) print(x / 10);pc(x % 10 + '0');}

struct Node {
    int ch[2] , dis;
	ll key, lazy;
}P[maxN];

void pushdown(int a) {
    ll lazy = P[a].lazy;
    P[a].lazy = 0;
    P[P[a].ch[0]].key += lazy;P[P[a].ch[1]].key += lazy;
    P[P[a].ch[0]].lazy += lazy;P[P[a].ch[1]].lazy += lazy;
    return ;
}

int Merge(int a , int b) {
    if(!a || !b) return a + b;
    if(P[a].key < P[b].key) swap(a , b);
    pushdown(a) ;pushdown(b) ;
    P[a].ch[1] = Merge(P[a].ch[1] , b);
    if(P[P[a].ch[1]].dis > P[P[a].ch[0]].dis) swap(P[a].ch[1] , P[a].ch[0]);
    P[a].dis = P[P[a].ch[1]].dis + 1;
    return a;
}

struct edge {
    int v , nxt;
	ll w;
}Map[maxN];
int head[maxN] , num , size[maxN];

void add_Node(int u , int v, ll w) {
    Map[++ num] = (edge) {v , head[u], w};
    head[u] = num;
}

int Dele(int q) {
    pushdown(q);
    return Merge(P[q].ch[0] , P[q].ch[1]);
}

int n ;
ll L;
int dfs(int now) {
    size[now] = 1;int top = now;
    for(int i = head[now];i;i = Map[i].nxt) {
        int v = Map[i].v;
		ll w = Map[i].w;
        int q = dfs(v);
        size[now] += size[v];
        P[q].lazy += w;P[q].key += w;
        top = Merge(top , q);
    }
    while(P[top].key > L) {
        int q = Dele(top);
        top = q;
        size[now] --;
    }
    return top;
}

int main() {
    n = read() , L = readll();
    int v;
	ll w;
    rep(i , 2, n) {
        v = read();w = readll();
        add_Node(v , i, w);
    }
    dfs(1);
    rep(i , 1, n) print(size[i]) , pc('\n');
    return 0;
}
```


---

## 作者：kikuss (赞：1)

这道题做法也是千千万万...倍增+差分/左偏树/主席树/...

蒟蒻我写的主席树

左偏树只写过一道题,所以对这道题思路不是很熟,稍微讲一下倍增+差分的思路吧,我们要找到一个点的子树中距离小于等于L的节点的个数,最朴素的做法就是暴力查找,找到一个打标记,但是这样的优化空间很大,寻找我们可以用倍增优化,标记可以差分,时间复杂度$O(nlogn)$

下面是主席树的思路,我们要寻找一个节点$u$子树中距离小于等于L的节点$v$的个数,即需要满足这样的条件:$dis[v]-dis[u]<=L\to dis[u]>=dis[v]+L$

问题就转化成了求子树内小于一个值的个数,主席树啊

对权值建树....

**注意:dis[v]+L不一定在原序列中出现过,所以我们用upper_bound,找的时候就变成严格<才统计答案,最后为了一定能找到,我们在序列的末尾加一个inf**

# Code
```cpp
#include<bits/stdc++.h>
#define mid ((l+r)>>1) 
#define in(i) (i=read())
#define lol long long 
using namespace std;

const lol N=2e5+10,inf=2e15;

lol read()
{
    lol ans=0,f=1; char i=getchar();
    while(i<'0' || i>'9') {if(i=='-') f=-1; i=getchar();} 
    while(i>='0' && i<='9') ans=(ans<<1)+(ans<<3)+i-'0',i=getchar();
    return ans*f; 
}

lol n,m,cur,tot,dfscnt,L;
lol head[N],nex[N<<1],to[N<<1],w[N<<1];
lol a[N],b[N],inc[N],ouc[N],rt[N];

struct Chair_Tree {
    lol l,r,v;
}t[N<<5];

void add(lol a,lol b,lol c) {
    to[++cur]=b,nex[cur]=head[a],w[cur]=c,head[a]=cur;
    to[++cur]=a,nex[cur]=head[b],w[cur]=c,head[b]=cur;
} 

void insert(lol &u,lol l,lol r,lol pre,lol p) {
    t[u=++tot]=t[pre], t[u].v++;
    if(l==r) return;
    if(p<=mid) insert(t[u].l,l,mid,t[pre].l,p);
    else insert(t[u].r,mid+1,r,t[pre].r,p);
}

lol query(lol u,lol v,lol l,lol r,lol k) {
    if(r<k) return t[v].v-t[u].v;
    if(l>=k) return 0;
    if(k<=mid) return query(t[u].l,t[v].l,l,mid,k);
    else return query(t[u].r,t[v].r,mid+1,r,k)+t[t[v].l].v-t[t[u].l].v;
}

void init(lol u,lol fa,lol now) {
    inc[u]=++dfscnt, a[++m]=b[m]=now;
    for (lol i=head[u];i;i=nex[i]) {
        if(to[i]==fa) continue;
        init(to[i],u,now+w[i]);
    }ouc[u]=dfscnt;
}

int main()
{
    in(n), in(L);
    for (lol i=2,f,c;i<=n;i++)
        in(f), in(c), add(i,f,c);
    init(1,0,0);
    sort(b+1,b+1+m); m=unique(b+1,b+1+m)-b-1;
    for (lol i=1;i<=n;i++) {
        lol p=lower_bound(b+1,b+1+m,a[i])-b;
        insert(rt[i],1,m,rt[i-1],p);
    }
    b[m+1]=inf;
    for (lol i=1,ans;i<=n;i++) {
        lol k=upper_bound(b+1,b+2+m,a[inc[i]]+L)-b;
        ans=query(rt[inc[i]-1],rt[ouc[i]],1,m,k);
        printf("%lld\n",ans);
    }
} 
```

---

## 作者：lcy09 (赞：0)

### 题目

[P3066 Running Away From the Barn G](https://www.luogu.com.cn/problem/P3066)


### 分析

看到题解里还没有直接用STL堆的启发式合并的，我来写一篇。

题目问每个点的子树内距离该点距离不超过$t$的点个数（包含本身），我就想到了堆的启发式合并。

对于每个节点开一个大根堆（堆中存的是距离）并且记录$added$标记（开大根堆的原因是我们需要小于等于$t$的元素个数，凡是堆顶加上$added$大于$t$的直接弹掉，最后堆的$size$就是答案）.

因为是树，我们必然要在dfs中解决问题。我们每新到一个节点，该点对应的堆push进一个$0$（其本身）.因为到每个节点弄答案的时候需要其下面每个节点都处理过，所以我们先递归到底，然后回溯的时候进行操作。假设我们正在处理的节点是$x$,先按上文所言处理出$x$的答案。把$x$的堆合并到其父节点上时，所有的点需要经过连接$x$与$fa_x$的边$edge$，所以$added$要加上$edge$的边权，然后向上合并的时候$x$对应的堆中元素加上$added_x$再减去$added_{fa_x}$,塞进$fa_x$对应的堆即可。

但是直接这么整复杂度容易被卡成$\Theta(n^2)$，所以要用堆的启发式合并，即如果$x$的堆的大小大于$fa_x$的堆的大小，我们交换这两个点的堆和$added$.我这里是用C++11直接把交换的复杂度优化成了$\Theta(1)$,如果强制使用C++98的时候再记录个数组表示每个点对应的堆的编号直接即可.

注：堆的启发式合并的复杂度本人不是很懂，欢迎补充。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=200005;
const int MAXE=400005;
inline int read()
{
    int weight=0,symbol=1;
    char in=getchar();
    while(!isdigit(in))
    {
        if(in=='-') symbol=-1;
        in=getchar();
    }
    while(isdigit(in))
    {
        weight=weight*10+in-'0';
        in=getchar();
    }
    return symbol*weight;
}
int n,t;
int fa[MAXN];
int head[MAXN];//链式前向星存图
struct EDGE
{
    int from,to;
    int val;
    int next;
}edge[MAXE];
int edge_cnt;
void add_edge(int fr,int to,int val)
{
    edge[++edge_cnt].from=fr;
    edge[edge_cnt].to=to;
    edge[edge_cnt].val=val;
    edge[edge_cnt].next=head[fr];
    head[fr]=edge_cnt;
}
priority_queue<int>q[MAXN];//对应上文
int added[MAXN];
int Ans[MAXN];//答案数组
void dfs(int x)
{
    q[x].push(0);//每新到一个节点先塞进自己的距离
    for(int i=head[x];i;i=edge[i].next)
    {
        int y=edge[i].to;
        if(y==fa[x]) continue;
        dfs(y);//先递归到底
    }
    while(q[x].top()+added[x]>t) q[x].pop();//把不符合条件的丢掉
    Ans[x]=q[x].size();//记录该节点的答案
    if(x==1) return ;//到了根节点就不需要下面的向fa合并了
    added[x]+=edge[(x<<1)-2].val;//这是建边时的特殊性质，因为是按从2到n的顺序建边
    if(q[fa[x]].size()<q[x].size()) swap(q[fa[x]],q[x]),swap(added[fa[x]],added[x]);//哪个元素数量多哪个在上面
    while(q[x].size())//合并
    {
        q[fa[x]].push(q[x].top()+added[x]-added[fa[x]]);
        q[x].pop();
    }
}
signed main()
{
    n=read(),t=read();
    for(int i=2;i<=n;i++)
    {
        fa[i]=read();
        int va=read();
        add_edge(i,fa[i],va),add_edge(fa[i],i,va);
    }
    dfs(1);
    for(int i=1;i<=n;i++) printf("%lld\n",Ans[i]);
    return 0;
}
```


---

## 作者：试试事实上吗 (赞：0)

题意很清晰，我们可以用前缀和转化一下，设$u$到根的距离为$dis[u]$，则在$u$的子树中满足到$u$的距离不大于$t$的点$v$满足
$$
dis[v]-dis[u]\leq t
$$
即
$$
dis[u]+t\geq dis[v]
$$
我们先跑一边$dfs$，每个点的子树就对应一段区间，然后问题就转化成了：求一段区间内小于等于某个数的值有几个，裸的主席树。

然后上板子即可，但细节有点多。

### $Code$

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn=2e5+5;

struct edge
{
    int v,nxt;
    ll w;
    edge(int v=0,ll w=0,int nxt=0) :v(v),w(w),nxt(nxt){}
}e[maxn<<1];
int lc[maxn<<5],rc[maxn<<5],sum[maxn<<5];
int rt[maxn],tot;
int head[maxn],kt,dfn[maxn],siz[maxn],n,cnt,m,id[maxn];
ll dis[maxn],b[maxn],t;

template<typename T>
inline void read(T &x)
{
    char c;int f=1;
    while(!isdigit(c=getchar())) (c=='-')&&(f=-1);
    x=c^48;
    while(isdigit(c=getchar())) x=x*10+(c^48);
    x*=f;
}

inline void add(int u,int v,ll w)
{
    e[++kt] = edge(v, w, head[u]);
    head[u] = kt;
}

void dfs(int u,int fa,ll ds)
{
    dis[u] = ds;siz[u] = 1;
    dfn[u] = ++cnt;id[cnt]=u;
    for (int i = head[u];i;i=e[i].nxt)
        if(e[i].v!=fa) {
            dfs(e[i].v, u, ds + e[i].w);
            siz[u] += siz[e[i].v];
        }
}

void build(int &u,int l,int r)
{
    u=++tot;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(lc[u],l,mid);build(rc[u],mid+1,r);
}

void insert(int &u,int pre,int l,int r,int x)
{
    u=++tot;lc[u]=lc[pre];rc[u]=rc[pre];sum[u]=sum[pre]+1;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(x<=mid) insert(lc[u],lc[pre],l,mid,x);
    else insert(rc[u],rc[pre],mid+1,r,x);
}

int query(int u,int v,int l,int r,int x,int y)
{
    if(r<x||l>y) return 0;
    if(x<=l&&r<=y) return sum[v]-sum[u];
    int mid=(l+r)>>1;
    return query(rc[u],rc[v],mid+1,r,x,y)+query(lc[u],lc[v],l,mid,x,y);
}

int main()
{
    int u;
    ll w;
    read(n);read(t);
    for (int i=2;i<=n;++i)
    {
        read(u);read(w);
        add(i,u,w);add(u,i,w);
    }
    dfs(1,0,0);
    for(int i=1;i<=n;++i) b[i]=dis[i];
    sort(b+1,b+n+1);b[n+1]=1e18;
    m=unique(b+1,b+n+2)-b-1;
    build(rt[0],1,m);
    for(int i=1;i<=n;++i)
        insert(rt[i],rt[i-1],1,m,lower_bound(b+1,b+m+1,dis[id[i]])-b);
    for(int i=1;i<=n;++i)
    {
        int x=lower_bound(b+1,b+m+1,dis[i])-b-1,y=lower_bound(b+1,b+m+1,dis[i]+t)-b-1;
        if(b[x+1]==dis[i]) ++x;if(b[y+1]==dis[i]+t) ++y;
        if(y==m-1) printf("%d\n",siz[i]); 
        else printf("%d\n",query(rt[dfn[i]-1],rt[dfn[i]+siz[i]-1],1,m,x,y));
    }
    return 0;
}
```



---

## 作者：Kushina_Anna (赞：0)

首先,通过读题我们可以知道:

1.无修改操作;

2.每个节点(除叶子)可由子树答案经删减得到.

那么,就可以用dsu on tree(树上启发式合并)来切这道题了:

只需要更改几个地方就可以了,所以直接贴上代码(~~码风极丑~~):

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rg register
#define ll long long
const int inf = 2147483647;
const int maxn = 2e5 + 7;
int n,in_a,H,sum,tot;
ll m,in_b,lit;
int head[maxn],size[maxn],h[maxn],ans[maxn];
bool vis[maxn];
struct node{
	int id;
	ll val;
	bool operator < (const node &A) const{
		return val < A.val;
	}
};
multiset<node> s;//记录在对答案有贡献的集合中的节点
ll Dis[maxn];
struct edge{int nxt,v;ll dis;}e[maxn << 1];
inline void add(int u,int v,ll dis){
	e[++tot].nxt = head[u];
	e[tot].v = v;
	e[tot].dis = dis;
	head[u] = tot;
	return;
}
void dfs1(int x){
	size[x] = 1;
	int Max = 0;
	for(rg int i = head[x];i; i = e[i].nxt){
		int v = e[i].v;
		dfs1(v);
		size[x] += size[v];
		if(size[v] > Max) Max = size[v],h[x] = v;
	}
	return;
}
void update(int x,int ori_x,bool opt){
	if(opt){
		if(Dis[x] > lit) return;//判断是否满足条件
		vis[x] = true;
		s.insert((node){x,Dis[x]});
		sum++;
	}//若要加入x节点
	else if(vis[x]){//若要删除x节点,如果在有贡献的集合中
		s.erase(s.find((node){x,Dis[x]}));
		vis[x] = false;
		sum--;
	}//如果不在的话,他和他的子孙都不会在
	else return;
	for(rg int i = head[x];i; i = e[i].nxt){
		int v = e[i].v;
		if(v == H) continue;
		update(v,ori_x,opt);
	}
	return;
}
void dfs(int x,bool opt){
	int h_edge = 0;
	for(rg int i = head[x];i; i = e[i].nxt){
		int v = e[i].v;
		Dis[v] = Dis[x] + e[i].dis;
		if(v == h[x]) {h_edge = i;continue;}
		dfs(v,false);
	}
	if(h_edge) dfs(h[x],true),H = h[x];
	lit = m + Dis[x];//对于节点x到根距离最大值
	while(!s.empty()){
		node Node = *(--s.end());
		if(Node.val > lit){
			s.erase(--s.end());
			vis[Node.id] = false; 
			sum--;
		}
		else break;
	}//将不符合要求的删去
	update(x,x,true);
	ans[x] = sum;H = 0;
	if(!opt) update(x,x,false),sum = 0;
	return;
}
int main()
{
	scanf("%d%lld",&n,&m);
	for(rg int i = 2;i <= n; i++) scanf("%d%lld",&in_a,&in_b),add(in_a,i,in_b);
	dfs1(1);dfs(1,1);
	for(rg int i = 1;i <= n; i++) printf("%lld\n",ans[i]);
	return 0;
}
```
但是没开O2跑2.03s,开了O2跑580ms...

---

## 作者：Fuko_Ibuki (赞：0)

行,我假设这题真有省选难度.  
我感觉这题的做法数量非常之多,接下来介绍第$5$种奇怪做法:树上二分.   
这个做法还是基于树上差分的,也就是对于每一个点$u$,我们要找到它向上跳$L$的长度最高能够跳到的祖先.(当然倍增求出这个连$dfs$都不用更加粗暴.)  
因此我们不仅要记录每一个节点到根节点的距离$dis$,还要记录每一个节点到根节点要经过边的边数,也即点的深度$dep$.  
然后再用$tmp$数组记录从根节点到$u$经过的每一个点,$tmp[i]$表示从根节点到$u$的路径上深度为$i$的节点的编号,   
只要用`tmp[dep[u]]=u`一句话就可以记录了.   
记录了路径上的点,接下来神奇的事情发生了.  
可以发现,路径上的点到根的距离是单调递增的,我们在$tmp$数组里二分可以找到离$u$距离不超过$L$的最高祖先.
这样对每个点都差分,最后$dfs$处理一遍就可以了.
```cpp
#include<bits/stdc++.h> //Ithea Myse Valgulious
/*省略快读快写*/
using namespace std;
const int yuzu=2e5;
typedef int fuko[yuzu|10];
typedef ll rize[yuzu|10];
struct edge{int to; ll c;};
vector<edge> lj[yuzu|10];
fuko fa,ans,dep,tmp,cha;
rize dis;

void dfs(int u,ll len) {
dep[u]=dep[fa[u]]+1; // 求节点u的深度
tmp[dep[u]]=u; // 记录从根节点到u深度为dep[u]的点.
int l=1,r=dep[u],mid;
for (;l<r;dis[u]-dis[tmp[mid]]<=len?r=mid:l=mid+1) mid=l+r>>1;
/*在这条路径上二分能跳到的最高祖先*/
cha[fa[tmp[l]]]--,cha[u]++; // 差分
for (edge i:lj[u]) 
  dis[i.to]=dis[u]+i.c,dfs(i.to,len);
}

int main() {
int i,n; ll l,x;
scanf("%d%lld",&n,&l);
for (i=2;i<=n;++i) 
  scanf("%d%lld",&fa[i],&x),
  lj[fa[i]].push_back(edge{i,x});
dfs(1,l);
for (i=n;i;--i) cha[fa[i]]+=cha[i]; 
/*由于每个点的父节点已知并且肯定比原节点编号小,可以倒过来用一个循环代替dfs*/
for (i=1;i<=n;++i) printf("%d\n",cha[i]);
}
```

---

