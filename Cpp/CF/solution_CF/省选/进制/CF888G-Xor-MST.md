# Xor-MST

## 题目描述

You are given a complete undirected graph with $ n $ vertices. A number $ a_{i} $ is assigned to each vertex, and the weight of an edge between vertices $ i $ and $ j $ is equal to $ a_{i}xora_{j} $ .

Calculate the weight of the minimum spanning tree in this graph.

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
8
```

## 样例 #2

### 输入

```
4
1 2 3 4
```

### 输出

```
8
```

# 题解

## 作者：Nemlit (赞：97)

妙妙题……

~~看到$MST$，想到$Kruskal$，看到异或，想到$Trie$~~

首先我们模拟一下$Kruskal$的流程：找到最小边，如果联通就忽略，未联通就加边

我们把所有点权值加入$0-1\ Trie$中，然后画张图，可以发现有$n-1$个点是有两个儿子的，而其他点都是只有$0/1$个儿子

权值最小的边应该是$Trie$中，$LCA$深度最大的两个数

而且这$n-1$个节点是一些在$Trie$中结尾节点的$LCA$

所以我们只需要遍历整颗$Trie$，然后对所有可能为$LCA$的点，找到一条最小的边，把它的两颗子树合并起来即可

一个小$trick:$我们可以把所有元素排好序，因为$Trie$上的点从左往右看是递增的，于是$Trie$的每一个节点就会对应排好序的数列中的一段区间，这样就不需要启发式合并之类的复杂操作了
## $Code:$
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf (1 << 30)
#define rep(i, s, t) for(int i = s; i <= t; ++ i)
#define maxn 200005
int n, m, a[maxn], L[maxn * 32], R[maxn * 32], ch[2][maxn * 32], rt, cnt;
void insert(int&k, int id, int dep) {
	if(!k) k = ++ cnt;
	if(!L[k]) L[k] = id; R[k] = id;
	if(dep == -1) return;
	insert(ch[(a[id] >> dep) & 1][k], id, dep - 1);
}
int query(int k, int x, int dep) {
	if(dep == -1) return 0;
	int v = (x >> dep) & 1;
	if(ch[v][k]) return query(ch[v][k], x, dep - 1);
	return query(ch[v ^ 1][k], x, dep - 1) + (1 << dep);
}
int dfs(int k, int dep) {
	if(dep == -1) return 0;
	if(ch[0][k] && ch[1][k]) {
		int ans = inf;
		rep(i, L[ch[0][k]], R[ch[0][k]]) {
			ans = min(ans, query(ch[1][k], a[i], dep - 1) + (1 << dep));
		}
		return dfs(ch[0][k], dep - 1) + dfs(ch[1][k], dep - 1) + ans;
	}
	else if(ch[0][k]) return dfs(ch[0][k], dep - 1);
	else if(ch[1][k]) return dfs(ch[1][k], dep - 1);
	return 0;
}
signed main() {
	scanf("%lld", &n);
	rep(i, 1, n) scanf("%lld", &a[i]);
	sort(a + 1, a + n + 1);
	rep(i, 1, n) insert(rt, i, 30);
	printf("%lld", dfs(rt, 30));
	return 0;
}
```

---

## 作者：Genius_Z (赞：44)

对于完全图的$MST$问题，一般考虑使用$Boruvka$算法，我们要在$nlogn$或$nlog^2n$时间内求出每个连通块最小的连接的边，而这个边权一般可通过点权以一定方式求出。

对于本题来说，要求的就只是点权异或最小值，考虑用$01trie$维护，对全局建一棵$trie$，然后对于每个连通块建一棵$trie$，每次$Boruvka$算法合并两个联通块时，合并相应的$trie$，在$trie$上维护子树$size$，点权异或最小值就直接在全局$trie$与当前连通块的$trie$的$size$作差得到的树上贪心即可。总共会迭代$logn$次，所以总时间复杂度为$\Theta(nlog_nlog_{size})$，空间复杂度为$\Theta(nlog_{size})$

$\large Code:$

```cpp
int a[200001], cnt, ch[200001 * 50][2], siz[200001 * 50], minn[200001], nxt[200001], fa[200001], tail[200001 * 50], tmp[200001], st[200001], top, root[200005];
inl int find(int x) { return fa[x] ? fa[x] = find(fa[x]) : x; }
inl void insert(int &x, int dep, int i, int w) {
	if (!x)x = ++cnt;
	if (dep < 0)return (void)(tail[x] = i, siz[x] = 1);
	bool c = w >> dep & 1;
	insert(ch[x][c], dep - 1, i, w), siz[x]++;
}
inl void merge(int &p, int q) {
	if (!p || !q)return (void)(p = p + q);
	merge(ch[p][0], ch[q][0]), merge(ch[p][1], ch[q][1]);
	siz[p] = siz[ch[p][0]] + siz[ch[p][1]], tail[p] = tail[q];
}
inl pair<int, int> query(int x, int pre, int w) {
	int ans = 0;
	for (re i = 30; ~i; i--) {
		bool c = w >> i & 1;
		if (ch[x][c] && siz[ch[x][c]] - siz[ch[pre][c]] > 0)x = ch[x][c], pre = ch[pre][c];
		else ans = ans | 1 << i, x = ch[x][c ^ 1], pre = ch[pre][c ^ 1];
	}
	return make_pair(ans, tail[x]);
}
signed main() {
	re n = read<int>(), flag;
	ll ans = 0;
	for (re i = 1; i <= n; i++)a[i] = read<int>();
	sort(a + 1, a + 1 + n), n = unique(a + 1, a + 1 + n) - a - 1;
	for (re i = 1; i <= n; i++) insert(root[0], 30, i, a[i]), insert(root[i], 30, i, a[i]);
	while (1) {
		memset(minn, 0x3f, sizeof(minn)), flag = 0;
		for (re i = 1; i <= n; i++) {
			re x = find(i), y, w;
			pair<int, int> ret = query(root[0], root[x], a[i]);
			y = find(ret.second), w = ret.first;
			if (x != y) {
				if (w < minn[x])minn[x] = w, nxt[x] = y;
				if (w < minn[y])minn[y] = w, nxt[y] = x;
			}
		}
		for (re i = 1; i <= n; i++) {
			if (minn[i] < inf&&find(i) != find(nxt[i])) {
				ans += minn[i], flag = 1, merge(root[find(i)], root[find(nxt[i])]), fa[find(nxt[i])] = find(i);
			}
		}
		if (!flag)break;
	}
	writeln(ans);
}
```



---

## 作者：周道_Althen (赞：41)

## 题目大意

$\ \ \ \ \ \ \,$给你一个 $n$ 个节点的完全图，第 $i$ 个点的权值为 $a_i$ ，两点的之间边权为这两个点权值的异或值，求最小生成树的权值。

## 想法

$\ \ \ \ \ \ \,$其实这道题没有那么复杂，还是好想的。

$\ \ \ \ \ \ \,$最小生成树的话，我们显然有一个基于贪心的$Kruskal$ 算法，复杂度 $O(n^2\log n)$，想想还是算了吧。

$\ \ \ \ \ \ \,$而遇到关于异或的题呢，我们一般会有两种想法：整形异或线性基，$Trie$ 树。

$\ \ \ \ \ \ \,$容易想到的，这道题当然和线性基没有关系了，我们思考一下 $Trie$ 树，首先，我们先把第一个样例从高位到低位插入线性基看看：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190226084314824.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80Mzk3Mzk2Ng==,size_16,color_FFFFFF,t_70)

$\ \ \ \ \ \ \,$容易发现，对于每个叶子节点，既每个点值之间，要是需要互相连边，那么求 **他们 $Lca$ 以后的边的亦或值** 即可。

$\ \ \ \ \ \ \,$由此可得，若是 $Lca$ 的深度越深，便约优。因为我们是从高位到低位插入的，所以浅的点权值较大，要尽量避免选择浅的点。

$\ \ \ \ \ \ \,$我们不妨把可能是 $Lca$ 的点拉出来瞅瞅：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190226085043371.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80Mzk3Mzk2Ng==,size_16,color_FFFFFF,t_70)
$\ \ \ \ \ \ \,$惊喜地发现，刚好有 $4$ 个点，也就是所有拥有两个儿子的点一共有 $4$ 个，可以证明，如果 $a_i$ 两两不等的话，那么这种点一共有 $n-1$ 个，那么答案就呼之欲出了：

$\ \ \ \ \ \ \,$我们每找到这样的点，就暴力贪心 $DFS$ 下去：
- 每次尽量同时走左儿子或右儿子；
- 如果两个都有，就两个都走，然后返回值取 $min$ 。
- 如果两个只有不一样的儿子，就在返回值加上这一深度$bit$的值，然后继续走

$\ \ \ \ \ \ \,$最终答案就是他们的 $DFS$ 值的和。

$\ \ \ \ \ \ \,$那如果 $a_i$ 不是两两不等的话怎么办呢，如果 $a_u=a_v$ 的话，我们当然首先建一条边连接 $u$，$v$，权值为 $0$，对答案完全没有影响，所以我们正常建，正常搜，是不会有问题的。

```cpp
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<cstdio>
#include<vector>
#include<string>
#include<queue>
#include<stack>
#include<cmath>
#include<map>
#include<set>
using namespace std;
const int inf=0x7fffffff;
const double eps=1e-10;
const double pi=acos(-1.0);
//char buf[1<<15],*S=buf,*T=buf;
//char getch(){return S==T&&(T=(S=buf)+fread(buf,1,1<<15,stdin),S==T)?0:*S++;}
inline int read(){
	int x=0,f=1;char ch;ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=0;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch&15);ch=getchar();}
	if(f)return x;else return -x;
}
struct Trie{
	int son[2][200000*30+10],tot;
	void Insert(int a){
		int now=0,id;
		for(int i=30;i>=0;i--){
	    	id=(a>>i)&1;
	    	if(!son[id][now])son[id][now]=++tot;
	    	now=son[id][now];
		}
	}
	int Find(int r1,int r2,int b){
		if(b<0) return 0;
		int a1=-1,a2=-1;
		if(son[0][r1]&&son[0][r2]) a1=Find(son[0][r1],son[0][r2],b-1);
		if(son[1][r1]&&son[1][r2]) a2=Find(son[1][r1],son[1][r2],b-1);
		if(~a1&&~a2) return min(a1,a2);
		if(~a1) return a1;if(~a2) return a2;
		if(son[1][r1]&&son[0][r2]) a1=Find(son[1][r1],son[0][r2],b-1)+(1<<b);
		if(son[0][r1]&&son[1][r2]) a2=Find(son[0][r1],son[1][r2],b-1)+(1<<b);
		if(~a1&&~a2) return min(a1,a2);
		if(~a1) return a1;if(~a2) return a2;
	}
}T;
long long ans;
void dfs(int a,int b){
	if(b<0) return;
	if(T.son[0][a]&&T.son[1][a]) ans+=1ll*T.Find(T.son[0][a],T.son[1][a],b-1)+(1ll<<b);
	if(T.son[0][a]) dfs(T.son[0][a],b-1);
	if(T.son[1][a]) dfs(T.son[1][a],b-1);
}
int n,v;
int main()
{
	n=read();
	for(int i=1;i<=n;i++)T.Insert(read());
	dfs(0,30);
	printf("%I64d\n",ans);
	return 0;
}

```

---

## 作者：ButterflyDew (赞：38)

有一种B开头的MST算法

大致流程是这样的

当前每个集合伸出去一条最短的边，然后把联通块缩成一个新的集合，因为每次缩集合个数减半，所以复杂度对。

事实上基本不会让我们真去写它，有时候需要用这种方法或者思想处理处MST。

比如这个题就可以这么做，每次合并实际上对trie树做启发式合并，然后在里面查一下最小值。

然后有一种神奇的思路，这里sto attack巨佬

发现每次合并的集合都是最高位的1不同的两个集合进行合并，于是可以从上往下做，从最高位把集合分开，然后查询两个集合的最小连边。

如果我们把所有元素按从小到大排序加入trie，那么一个集合内的元素就在一个连续的区间里啦

这样我们就可以非常方便的直接遍历一遍字典树统计出答案了，具体过程可以看看代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using std::min;
using std::max;
const int N=2e5+10;
const int inf=0x3f3f3f3f;
#define ls ch[now][0]
#define rs ch[now][1]
int L[N*40],R[N*40],ch[N*40][2],tot;
int n,a[N],root;
void Insert(int &now,int x,int dep)
{
    if(!now) now=++tot;
    L[now]=min(L[now],x),R[now]=max(R[now],x);
    if(dep<0) return;
    int bit=a[x]>>dep&1;
    Insert(ch[now][bit],x,dep-1);
}
int query(int now,int val,int dep)
{
    if(dep<0) return 0;
    int bit=val>>dep&1;
    if(ch[now][bit]) return query(ch[now][bit],val,dep-1);
    else return query(ch[now][bit^1],val,dep-1)+(1<<dep);
}
ll dfs(int now,int dep)
{
    if(dep<0) return 0;
    if(R[ls]&&R[rs])
    {
        int mi=inf;
        for(int i=L[ls];i<=R[ls];i++) mi=min(mi,query(rs,a[i],dep-1));
        return dfs(ls,dep-1)+dfs(rs,dep-1)+mi+(1<<dep);
    }
    if(R[ls]) return dfs(ls,dep-1);
    if(R[rs]) return dfs(rs,dep-1);
    return 0;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    std::sort(a+1,a+1+n);
    memset(L,0x3f,sizeof(L));
    for(int i=1;i<=n;i++) Insert(root,i,30);
    printf("%lld\n",dfs(root,30));
    return 0;
}
```

---

## 作者：STUDENT0 (赞：21)

Xor-MST 更优秀的做法。

转换部分略过，重点讲优化。转换后，对于 trie 上的每一个节点，你需要求出它左右子树中异或的最小值。

目前有两种做法，一种是把一棵子树内所有数插入另一棵子树，另一种是两棵子树同时遍历，能同侧递归就同侧递归，否则异侧递归，这种做法不把 trie 建出来也行。

分析一下复杂度，由于树高是 $O(\log a)$ 的，每个节点最多被遍历 $O(\log a)$ 次。第一种做法还可以用启发式合并优化到 $O(\log n)$ 次。又因为总结点数是 $O(n\log v)$ 的，所以总时间复杂度是 $O(n\log^2a)$ 或 $O(n\log a\log n)$，是能卡满的。

看上去就很能优化。

注意到，trie 上有用的节点只有 $O(n)$ 个，具体地说，只保留 trie 上有两个儿子的节点和叶子就能发挥相同的作用，建 trie 的虚树就行。就完了。时间复杂度 $O(n\log v)$。

实现上，每个节点需要存下它的深度和它代表的从根到这个节点的路径（用一个数表示）。往下跳时直接选一个儿子跳，每次会跳过一段。

先放一份实现得很史的代码：

~~~cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
const int NN=500000,L=30,K=2,INF=2000000000;
int d[NN],vv[NN][K],trans[NN][K],b[L+1],vvv[NN],mi,pp[NN];
long long ans;
bool ss;
int work(int l,int r)
{
	return b[r-l]<<l+1;
}
void init(int p)
{
	if (trans[p][0])
	{
		vv[p][0]&=work(d[trans[p][0]],d[p]);
		vvv[trans[p][0]]=vvv[p]^vv[p][0];
		init(trans[p][0]);
	}
	if (trans[p][1])
	{
		vv[p][1]&=work(d[trans[p][1]],d[p]);
		vvv[trans[p][1]]=vvv[p]^vv[p][1];
		init(trans[p][1]);
	}
}
void dfs(int p)
{
	int ppp,to,p1,p2;
	bool k;
	ppp=pp[p];
	if (d[ppp]>-1)
	{
		k=vvv[p]>>d[ppp]&1;
		while (1)
		{
			to=trans[ppp][k];
			if (!to||d[to]<d[p]) break;
			ppp=to;
			if (d[ppp]>d[p]) k=vvv[p]>>d[ppp]&1;
		}
	}
	if (d[p]>-1)
	{
		p1=trans[p][0];
		pp[p1]=ppp;
		dfs(p1);
		p2=trans[p][1];
		pp[p2]=ppp;
		dfs(p2);
	}
	else mi=min(mi,vvv[p]^vvv[ppp]);
}
void trie(int p)
{
	if (trans[p][0]) trie(trans[p][0]);
	if (trans[p][1]) trie(trans[p][1]);
	if (trans[p][0]&&trans[p][1])
	{
		mi=INF;
		pp[trans[p][0]]=trans[p][1];
		dfs(trans[p][0]);
		ans+=mi;
	}
}
int main()
{
	int n,tot,i,a,j,p,v;
	bool k;
	scanf("%d",&n);
	ss=n==800;
	d[0]=L-1;
	tot=1;
	for (i=0;i<n;i++)
	{
		scanf("%d",&a);
		p=0;
		for (j=L-1;j>-1;j--)
		{
			if (d[p]>j)
			{
				v=vv[p][k];
				if ((a>>j&1)!=(v>>j&1))
				{
					d[tot]=j;
					vv[tot][a>>j&1]=a;
					vv[tot][v>>j&1]=v;
					trans[tot][a>>j&1]=tot+1;
					trans[tot][v>>j&1]=trans[p][k];
					trans[p][k]=tot++;
					d[tot++]=-1;
					break;
				}
			}
			else
			{
				if (!trans[p][a>>j&1])
				{
					d[tot]=-1;
					vv[p][a>>j&1]=a;
					trans[p][a>>j&1]=tot++;
					break;
				}
				k=a>>j&1;
			}
			if (d[trans[p][k]]==j-1) p=trans[p][k];
		}
	}
	for (i=1;i<=L;i++) b[i]=(1<<i)-1;
	init(0);
	trie(0);
	printf("%lld",ans);
	return 0;
}
~~~
这份代码可读性低（我已经看不懂了），跑起来也不那么快。

简单解释一下，建 trie 时是暴力插入，init 函数是预处理节点信息的，后面的思路大概是上面讲的第一种，遍历左子树，对于其中每一个节点维护其对应的右子树中的节点，转移到儿子时在右子树暴力跳。

有没有更好的实现方法呢？

先看建树（和上面的代码没有任何关系）：
~~~cpp
int build(int l,int r,int al,int ar,int deep)
{
	int mid,id,amid;
	if (l==r)
	{
		d[t]=deep;
		v[t]=a[al];
		return t++;
	}
	mid=l+r>>1;
	if (a[ar]<=mid) return build(l,mid,al,ar,deep-1);
	if (a[al]>mid) return build(mid+1,r,al,ar,deep-1);
	id=t++;
	d[id]=deep;
	amid=upper_bound(a+al,a+ar,mid)-a-1;
	e[id][0]=build(l,mid,al,amid,deep-1);
	e[id][1]=build(mid+1,r,amid+1,ar,deep-1);
	v[id]=v[e[id][0]];
	return id;
}
~~~
思想上类似于线段树或整体二分。

如果区间中的数集中在一侧就直接向一侧递归，否则二分出断开的位置。递归次数 $O(n\log v)$，二分次数 $O(n)$，时间复杂度 $O(n(\log a+\log n))$。

再看查询：
~~~cpp
int work(int rt1,int rt2)
{
	int rt3,rt4;
	if (d[rt1]==-1&&d[rt2]==-1) return v[rt1]^v[rt2];
	if (d[rt1]==d[rt2]) return min(work(e[rt1][0],e[rt2][0]),work(e[rt1][1],e[rt2][1]));
	rt3=rt1;
	rt4=rt2;
	if (d[rt3]<d[rt4]) swap(rt3,rt4);
	return work(e[rt3][v[rt4]>>d[rt3]&1],rt4);
}
~~~
用的是上面讲的第二种，按深度简单分讨一下。

那么，结束了，上完整代码：
~~~cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
char buf[1 << 20], *p1 = buf, *p2 = buf;
#define getc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)
#define putc(x) putchar(x)
inline int read() {
  int x = 0, sgn = 0; char s = getc();
  while(!isdigit(s)) sgn |= s == '-', s = getc();
  while(isdigit(s)) x = x * 10 + s - '0', s = getc();
  return sgn ? -x : x;
}
inline void print(long long x) {if(x >= 10) print(x / 10); putc(x % 10 + '0');}
const int N=400000,V=1073741823,K=2,D=29;
int a[N],t,d[N],v[N],e[N][K];
int build(int l,int r,int al,int ar,int deep)
{
	int mid,id,amid;
	if (l==r)
	{
		d[t]=deep;
		v[t]=a[al];
		return t++;
	}
	mid=l+r>>1;
	if (a[ar]<=mid) return build(l,mid,al,ar,deep-1);
	if (a[al]>mid) return build(mid+1,r,al,ar,deep-1);
	id=t++;
	d[id]=deep;
	amid=upper_bound(a+al,a+ar,mid)-a-1;
	e[id][0]=build(l,mid,al,amid,deep-1);
	e[id][1]=build(mid+1,r,amid+1,ar,deep-1);
	v[id]=v[e[id][0]];
	return id;
}
int work(int rt1,int rt2)
{
	int rt3,rt4;
	if (d[rt1]==-1&&d[rt2]==-1) return v[rt1]^v[rt2];
	if (d[rt1]==d[rt2]) return min(work(e[rt1][0],e[rt2][0]),work(e[rt1][1],e[rt2][1]));
	rt3=rt1;
	rt4=rt2;
	if (d[rt3]<d[rt4]) swap(rt3,rt4);
	return work(e[rt3][v[rt4]>>d[rt3]&1],rt4);
}
int main()
{
	int n,i;
	long long ans;
	n=read();
	for (i=0;i<n;i++) a[i]=read();
	sort(a,a+n);
	build(0,V,0,n-1,D);
	ans=0;
	for (i=0;i<t;i++) if (d[i]>-1) ans+=work(e[i][0],e[i][1]);
	print(ans);
	return 0;
}
~~~
小清新很多，跑到 CF 第一页，略逊于卡常巨佬。

[我与 Xor-MST 的故事](https://www.luogu.com.cn/paste/hkwqver5)。

---

## 作者：奇米 (赞：16)

# 题解 - $\mathrm{CF888G}$

## 题目意思

* [题目传送门](https://www.luogu.com.cn/problem/CF888G)

* 给你一张完全图，每个点有个权值 $a_i$，对于一条 $(u,v)$ 边的权值 $W_{(u,v)}=a_u\oplus a_v$。求这张完全图的最小生成树。

* $n\leq 2\times 10^5$

## $\mathrm{Sol}$

* 我们考虑到异或最小就想到让高位尽量保持相等。具体地，就是对每一个 $a_i$ 建一颗 $\mathrm{Trie}$ 树，要使得异或值最小显然就是尽量走同一条路径。

* 于是我们要计算每一颗子树的贡献，于是考虑启发式合并。每次我们做 $siz$ 小的一边在字典树上去计算 $siz$ 大的一边的贡献，这样复杂度是 $O(n\log n)$ 的。

* 最后时间复杂度：$O(n\log^2 n)$。注意 $\mathrm{long\ long}$ 不能都开要不然要保内存的。

## $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
#define For(i,a,b) for ( int i=(a);i<=(b);i++ )
#define Dow(i,b,a) for ( int i=(b);i>=(a);i-- )
#define GO(i,x) for ( int i=head[x];i;i=e[i].nex )
#define mem(x,s) memset(x,s,sizeof(x))
#define cpy(x,s) memcpy(x,s,sizeof(x))
#define YES return puts("YES"),0
#define NO return puts("NO"),0
#define GG return puts("-1"),0
#define pb push_back
using namespace std;

struct IO
{
	#define MAXSIZE (1 << 20)
	#define isdigit(x) (x >= '0' && x <= '9')
  	char buf[MAXSIZE],*p1,*p2;
  	char pbuf[MAXSIZE],*pp;
  	IO():p1(buf),p2(buf),pp(pbuf){}
  	inline char gc() {
  		return getchar();
    	if (p1==p2) p2=(p1=buf)+fread(buf,1,MAXSIZE,stdin);
    	return p1==p2?' ':*p1++;
  	}
	inline bool blank(char ch) {return ch==' '||ch =='\n'||ch == '\r'||ch == '\t';}
  	template <class T>
  	inline void read(T &x)
	{
	    register double tmp=1;register bool sign=0; x=0;
	    register char ch=gc();
	    for (;!isdigit(ch);ch=gc()) if(ch=='-') sign=1;
	    for (;isdigit(ch);ch=gc()) x=x*10+(ch-'0');
	    if (ch=='.') for (ch=gc();isdigit(ch);ch=gc()) tmp/=10.0,x+=tmp*(ch-'0');
	    if (sign) x=-x;
  	}
  	inline void read(char *s)
	{
    	register char ch=gc();
		for (;blank(ch);ch=gc());
		for (;!blank(ch);ch=gc()) *s++=ch;
    	*s=0;
  	}
  	inline void read(char &c) {for(c=gc();blank(c);c=gc());}
  	template<class t> inline void write(t x){
		if(x<0) putchar('-'),write(-x);
		else{if(x>9) write(x/10);putchar('0'+x%10);}
	}
} io;

const int mod=1e9+7;
const int mo=998244353;
const int N=2e5+5;
const int M=35;

int n,m,a[N],A[M],ch[N*M][2],bit[N*M],tot;
long long fac[M],ans;
vector<int> vec[N*M];

inline void insert(int s)
{
	int u=0;
	vec[u].pb(s);
	Dow(i,33,0) 
	{
		if(!ch[u][A[i]]) ch[u][A[i]]=++tot;
		u=ch[u][A[i]];
		s-=fac[i]*A[i];
		vec[u].pb(s);
		bit[u]=i;
	}
}

inline long long ask(int u,int s)
{
	long long ans=0;
	For(i,0,bit[u]-1) A[i]=s&1,s>>=1;
	Dow(i,bit[u]-1,0) 
	{
		if(ch[u][A[i]]) u=ch[u][A[i]];
		else u=ch[u][A[i]^1],ans+=fac[bit[u]];
	}
	return ans;
}

inline long long Ask(int u)
{
	if(vec[u].size()==1) return 0;
	if(ch[u][0]) ans+=Ask(ch[u][0]);
	if(ch[u][1]) ans+=Ask(ch[u][1]);
	if(!ch[u][0]||!ch[u][1]) return 0;
	long long Mi=1e12;
	int flg=((int)vec[ch[u][0]].size())>(int)(vec[ch[u][1]].size());
	int siz=(int)vec[ch[u][flg]].size()-1;
	For(i,0,siz) Mi=min(Mi,ask(ch[u][flg^1],vec[ch[u][flg]][i]));
	Mi+=fac[bit[u]-1];
	return Mi;
}

signed main()
{
	io.read(n);
	fac[0]=1;
	For(i,1,33) fac[i]=fac[i-1]*2ll;
	For(i,1,n) io.read(a[i]);
	sort(a+1,a+n+1);
	n=unique(a+1,a+n+1)-a-1;
	For(i,1,n) 
	{
		int x=a[i];
		For(j,0,33) A[j]=x&1,x>>=1;
		insert(a[i]);
	}
	ans+=Ask(0);
	io.write(ans);
	return 0;
}


```


---

## 作者：MikukuOvO (赞：10)

考虑每一次选择最小的边，连接两个连通块，这样做一定是对的。

但是如果我们要使得异或和最小，这个很容易想到$01Trie$，考虑将每一个点按照权值插到$Trie$中，这样我们考虑叶子节点就是实际存在的点，而非叶子节点一定时若干对叶子节点的$lca$。

根据二进制的性质，不难发现我们先合并$lca$深度大的点对更优，这样我们考虑$dfs$整个$Trie$，对于一个非叶子节点，我们枚举他的$0/1$子树的所有儿子，然后在$1/0$子树中找到边权最小的来合并，如果我们从小到大插入，那么编号就是连续的，然后启发式合并即可。

```cpp
const int N=2e5+5;
const int S=35;

int n,rt,tot;
int a[N],l[N*S],r[N*S],ch[N*S][2];

void insert(int &o,int id,int dep)
{
    if(!o) o=++tot;
    if(!l[o]) l[o]=id;
    r[o]=id;
    if(dep<0) return;
    insert(ch[o][(a[id]>>dep)&1],id,dep-1);
}
ll query(int o,ll x,int dep)
{
    if(dep<0) return 0;
    ll v=(x>>dep)&1;
    if(ch[o][v]) return query(ch[o][v],x,dep-1);
    return query(ch[o][v^1],x,dep-1)+(1<<dep);
}
ll dfs(int o,int dep)
{
    if(dep<0) return 0;
    if(ch[o][0]&&ch[o][1])
    {
        ll ans=LINF;
        if(r[ch[o][0]]-l[ch[o][0]]<r[ch[o][1]]-l[ch[o][1]])
            for(int i=l[ch[o][0]];i<=r[ch[o][0]];++i) ans=min(ans,query(ch[o][1],a[i],dep-1)+(1<<dep));
        else
            for(int i=l[ch[o][1]];i<=r[ch[o][1]];++i) ans=min(ans,query(ch[o][0],a[i],dep-1)+(1<<dep));
        return dfs(ch[o][0],dep-1)+dfs(ch[o][1],dep-1)+ans;
    }
    else if(ch[o][0]) return dfs(ch[o][0],dep-1);
    else if(ch[o][1]) return dfs(ch[o][1],dep-1);
    return 0;
}
int main()
{
    fio();
    gi(n);
    for(int i=1;i<=n;++i) gi(a[i]);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;++i) insert(rt,i,30);
    print(dfs(rt,30));
    end();
}
```

---

## 作者：Fading (赞：10)

$Borůvka$算法。

[算法介绍](https://www.luogu.org/blog/Tweetuzki/solution-p3366)

考虑算法流程：对于每一个连通块，枚举其出边。取其最小出边，合并两个连通块。

显然这样每一次连通块的个数$/2$（均摊），所以是$O(nlog_2n)$的。

但是对于这道题：

我们把每一个点的权值加入$\texttt{01 trie}$中，一开始所有连通块要去找最小出边。

对于每一个$\texttt{01 trie}$上的非叶子节点，其两个儿子（一边$0$,一边$1$） 一定没有连通。

证明？根据$Borůvka$算法+二进制来证明，$2^a>2^{a-1}+...+1$。
其连通块一定会找更小的边连通，而不是与另一个儿子连通块连通。

下一步，就是连通此节点的$01$儿子连通块。

可以发现$\texttt{01 trie}$就成为了这个完全图对于$B$算法的分治树。 

考虑一个分治算法：对于一个节点，显然根据$Borůvka$算法流程，$0,1$儿子要连通。

所以用$1$儿子内的所有子节点求与$0$儿子内的所有子节点最小异或值，作为边连起来。

答案就是这些边的和了。 

```
#include<bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;
#ifdef Fading
#define gc getchar
#endif
#ifndef Fading
inline char gc(){
	static char now[1<<16],*S,*T;
	if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
	return *S++;
}
#endif
inline ll read(){
    register ll x=0,f=1;char ch=gc();
    while (!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while (isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=gc();}
    return (f==1)?x:-x;
}
struct node{
	int son[2];
}g[6200001];
int cnt;
void insert(int T,int &rt,int w){
	if (!rt) rt=++cnt;
	if (T==-1) return;
	int op=(w>>T)&1LL;
	insert(T-1,g[rt].son[op],w);
}
int query(int T,int rt,int w){
	if (T==-1) return 0;
	int op=(w>>T)&1LL;
	if (g[rt].son[op]) return query(T-1,g[rt].son[op],w);
	else return query(T-1,g[rt].son[op^1],w)+(1<<T);
}	
int solve(const vector<int> &now,int rt,int T){
	if (!rt) return 0;
	int len=now.size();
	vector<int> D[2];
	for (int i=0;i<len;i++){
		D[(now[i]>>T)&1].push_back(now[i]);
	}
	if ((int)D[0].size()==0) return solve(D[1],g[rt].son[1],T-1);
	if ((int)D[1].size()==0) return solve(D[0],g[rt].son[0],T-1);
	len=D[1].size();
	ll rem=(1LL<<31LL);
	for (int i=0;i<len;i++)
		rem=min(rem,(1LL<<T)+query(T-1,g[rt].son[0],D[1][i]));
	return rem+solve(D[0],g[rt].son[0],T-1)+solve(D[1],g[rt].son[1],T-1);	
}
signed main(){
	vector<int> sb;sb.clear();
	int n=read(),root=0;
	for (int i=1;i<=n;i++) sb.push_back(read());
	for (int i=0;i<n;i++) 
		insert(31,root,sb[i]);
	//printf("%lld\n",query(31,root,6));
	printf("%lld\n",solve(sb,root,31));
	return 0;
}

```


---

## 作者：_⁢　 (赞：9)

本题在 Trie 上爆搜的复杂度也是 $O(n\log n\log\omega)$。（代码附后）

代码中 `qry()` 的复杂度，看似是 $O(n^2\log\omega)$ 的，但实际上只有 $O(n\log n\log\omega)$。

令 $size_x$ 表示子树 $x$ 中的叶子节点个数，每次进入 `qry(x, y, d)` 只会遍历 $\min(size_x,size_y)$ 个叶子节点。

证明如下：

$\min(size_x,size_y)=1$ 时显然。

$\min(size_x,size_y)=k>1$ 时，使用归纳法。考虑第一个分叉点，$x$ 分成 $a$、$b$，$y$ 分成 $c$、$d$。

不妨设 $size_a\ge size_b$，$size_c\ge size_d$，$size_a\ge size_c$，$\max(size_b,size_d)>0$。

因为我们已经证明了 $\min(size_x,size_y)<k$ 时只会遍历 $\min(size_x,size_y)$ 个叶子节点，因此 `qry(a, c, d - 1)` 只会遍历 $\min(size_a,size_c)=size_c$ 个叶子节点。要使另一侧的复杂度最劣（即使 $size_b$ 尽量大），就要让 $size_a=size_c$。

此时遍历的叶子节点数 $=\min(size_a,size_c)+\min(size_b,size_d)=\min(size_x,size_y)$，得证。

需要添加一个注释部分的剪枝，不然会超时。

ps: 其实不剪枝节点个数也是对的，但是每一个分叉常数会 $\times 2$，虽然 $n=2\times{10}^5$ 卡不满 $\omega$，但是用时会大很多。

又由于 `dfs()` 本质上是在合并 Trie 的两颗子树，因此复杂度就是启发式合并的 $O(n\log n)$，再乘上树高就是 $O(n\log n\log\omega)$。

```cpp
int n, a[maxn]; ll A;

struct Trie {
    int s[maxm][2], tt;
    void ins(int x) {
        for (int i = 30, u = 0, p; i--; ) {
            if (!s[u][p = (x >> i) & 1]) s[u][p] = ++tt;
            u = s[u][p];
        }
    }
    int qry(int x, int y, int d) {
        if (d < 0) return 0;
        int A = inf;
        for (int i = 0; i < 2; ++i) if (s[x][i] && s[y][i])
            A = min(A, qry(s[x][i], s[y][i], d - 1));
        if (A != inf) return A; // 剪枝
        for (int i = 0; i < 2; ++i) if (s[x][i] && s[y][!i])
            A = min(A, qry(s[x][i], s[y][!i], d - 1) + (1 << d));
        return A;
    }
    void dfs(int u, int d) {
        if (d < 0) return;
        if (s[u][0] && s[u][1]) A += qry(s[u][0], s[u][1], d - 1) + (1 << d);
        if (s[u][0]) dfs(s[u][0], d - 1);
        if (s[u][1]) dfs(s[u][1], d - 1);
    }
} tr;

int main() {
    rd(n);
    for (int i = 1; i <= n; ++i) rd(a[i]);
    sort(a + 1, a + n + 1), n = unique(a + 1, a + n + 1) - a - 1;
    for (int i = 1; i <= n; ++i) tr.ins(a[i]);
    tr.dfs(0, 30 - 1);
    printf("%lld", A);
    return 0;
}
```

---

## 作者：wu3412790 (赞：8)

题意：给定一张n个点的完全图，每个点有一个点权，点i和点j的边的权值为$a_i\;\mathrm{xor}\;a_j$,求最小生成树。

解法：处理异或，考虑使用Trie树，把点按权值插入Trie。而求最小生成树，则考虑使用Kruskal算法。注意到，Trie树中两个叶子节点的LCA越深，则异或值越小(LCA相等的情况不一定)。由于Kruskal算法是从小到大加边，所以一定是LCA深的点先被连起来，换句话，可以dfs Trie树，递归地把同一棵子树内的点连通。不难看出，Trie树恰好有n-1个有两个儿子的节点，它们组成的子树就是Kruskal重构树。

  考虑dfs到一个点x，如果它有左右两个儿子，注意左右两子树已经递归地被连通成一个连通块了，那么还需要一条边连接它的左右两棵子树对应的连通块，我们可以暴力地找这条边，同时从左右两边走下去，如果能同时走左边就同时走左边，能同时走右边就同时走右边，都能就都走(要回溯，取最小的)。这样的话时间似乎会超时，但根据启发式合并的思想，每次连边的复杂度等于 树的深度$\times$小的子树的大小，故DFS+连边总时间不超过$O(n\log^2 n)$.
  
  ```cpp
#include <iostream>
using namespace std;
int const N=30,M=2e5+1;
struct tree{
	int son[2],d;
}t[N*M]; 
int n;
long long ans,pow[N],a[M],root,tot,r;
void connect(int x, int y,long long now){
	if (t[x].d==N){
		if (now<r) r=now;
		return;
	}
	bool flag=false;
	for (int i=0;i<=1;i++)
		if (t[x].son[i] && t[y].son[i]){
			connect(t[x].son[i],t[y].son[i],now);
			flag=true;
		}
	if (!flag){
		if (t[x].son[0] && t[y].son[1]) connect(t[x].son[0],t[y].son[1],now+pow[N-t[x].d-1]);
		else connect(t[x].son[1],t[y].son[0],now+pow[N-t[x].d-1]);
	}
}
void dfs(int x){
	if (!x || t[x].d==N) return;
	for (int i=0;i<=1;i++) dfs(t[x].son[i]);
	if (t[x].son[0] && t[x].son[1]){
		r=2e9;
		connect(t[x].son[0],t[x].son[1],pow[N-t[x].d-1]);
		ans=ans+r;
	}
}
int main(){
	ios::sync_with_stdio(false);
	pow[0]=1;
	for (int i=1;i<N;i++) pow[i]=pow[i-1]+pow[i-1];
	cin>>n;
	root=tot=1;
	for (int i=1;i<=n;i++){
		cin>>a[i];
		int x=root; 
		for (int j=0;j<N;j++){
			int r=((pow[N-j-1] & a[i])>0);
			if (!t[x].son[r]){
				t[x].son[r]=++tot;
				t[tot].d=t[x].d+1;
			}
			x=t[x].son[r];
		} 
	}
	dfs(1);
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Y_B_X (赞：6)

[原题链接](https://www.luogu.com.cn/problem/CF888G)

提供一个易 (luan) 懂 (gao) 的分治算法。

容易发现如果将序列每次分成两半，每一半都得到了最优方案，

此时要做的就是在两块中分别找出一个数让其异或和最小，这可以用 $\text{01trie}$ 轻松实现。

但不过此题中分的方法很有讲究，并不能直接取两端点的中点。

通过几次观察可以得出这样的结论：

- 将原序列去重排好序后，在每次分治时传一个参数 d (最开始 $ d=30 $ ) ，
每次按二进制下按第 d 位是 0 还是 1 分成两半，
- 接下来对两边继续分治时 $ d\leftarrow d-1 $ ，就能得到最优方案。


证明：
设这样得到的答案为 x ，在第 d 位上将一个数从另一半中放入这一半所得答案为 y ，

此时第 d 位上至少会贡献 $ 2\cdot 2^d $ 。

则 $ y\geq 2\cdot2^d $ , $x \leq 1+2+\dots +2^{d-1}+2^d$ 

$y-x\geq 2^d-(1+2+\dots +2^{d-1})=1>0$

故 $y>x$ ，证毕。

再考虑 $ \text{01trie} $ 如何实现。

这只需让每次递归完后区间内的点都插入即可，

先递归左边，再在右边查与左边各选两数的最小异或和，再递归右边，递归到只有一个数时插入后返回。

时间复杂度是 $ O(n\log(n)) $ 。

这个算法实际上也无形地建了一个 $ \text{01trie} $ 出来，非要有个名字不妨称为 $ \text{01trie} $ 分治。

代码：

```cpp#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10,K=30,NN=5e6+10;
int n,nn,x,y,rt,res,tot,cnt,tmp;
long long ans;int a[N];char ch;
inline void read(int &x){
	x=0;ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
}
struct trie{int s[2],sz;}t[N*K];
void insert(int &k,int x,int d,int v){
	if(!k)k=++tot;t[k].sz+=v;if(d<0)return;
	bool b=x&(1<<d);insert(t[k].s[b],x,d-1,v);
}
void inquiry(int k,int x,int d){
	if(d<0)return;bool b=x&(1<<d);
	if(t[t[k].s[b]].sz)inquiry(t[k].s[b],x,d-1);
	else res+=1<<d,inquiry(t[k].s[b^1],x,d-1);
}
void solve(int l,int r,int d){
	if(l==r)return insert(rt,a[l],K,1);
	register int pos=r+1,i;
	for(i=r;i>=l;--i)if((a[i]>>d)&1)pos=i;
	if(pos==r+1||pos==l)return solve(l,r,d-1);
	solve(l,pos-1,d-1);
	tmp=1<<30;
	for(i=pos;i<=r;++i){
		res=0;inquiry(rt,a[i],K);
		tmp=min(tmp,res);
	}
	ans+=tmp;
	solve(pos,r,d-1);
}
main(){
	read(n);register int i;
	for(i=1;i<=n;++i)read(a[i]);
	sort(a+1,a+n+1);n=unique(a+1,a+n+1)-a-1;
	solve(1,n,K);
	printf("%lld",ans);
}
```


---

## 作者：rainygame (赞：4)

看到完全图最小生成树想到 [Boruvka](https://oi-wiki.org/graph/mst/#boruvka-%E7%AE%97%E6%B3%95)。

每一轮合并时需要维护每个连通块的最小出边，异或最小值可以用 01-Trie 求出。

大概思路是对于每一个连通块，先把这个连通块内的 $a_i$ 从 01-Trie 中删除，然后再对于它们找出异或最小值并加上这条边，最后再加回 01-Trie。

01-Trie 的删除可以对于每个结点维护 `cnt` 表示这里面有多少个数 $a_i$，删除时路径上的 `cnt` 减一，查询时只走 `cnt` 非零的结点。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 200001
#define MAXK 30

int n, ans;
int a[MAXN], f[MAXN]; bool vis[MAXN];
int find(int x){return f[x] == x ? x : f[x] = find(f[x]);}
vector<int> vid[MAXN];

namespace Trie{
    struct Node{int s[2], cnt, id;};
    vector<Node> tr(1, {{0, 0}, 0});
    void ins(int x, int id){
        int now(0);
        for (int i(MAXK-1); ~i; --i){
            if (!tr[now].s[(x>>i)&1]){
                tr[now].s[(x>>i)&1] = tr.size();
                tr.push_back({{0, 0}, 0});
            }
            ++tr[now=tr[now].s[(x>>i)&1]].cnt;
        }
        tr[now].id = id;
    }
    void del(int x){
        for (int i(MAXK-1), now(0); ~i; --i) --tr[now=tr[now].s[(x>>i)&1]].cnt;
    }
    pair<int, int> query(int x){
        int res(0), now(0);
        for (int i(MAXK-1); ~i; --i){
            if (!tr[now].s[(x>>i)&1] || !tr[tr[now].s[(x>>i)&1]].cnt){
                now = tr[now].s[!((x>>i)&1)];
                res += 1<<i;
            }else now = tr[now].s[(x>>i)&1];
        }
        return {res, tr[now].id};
    }
}

void boruvka(){
    iota(f+1, f+n+1, 1);
    while (true){
        set<int> id; for (int i(1); i<=n; ++i) id.insert(find(i));
        // cout << id.size() << '\n';
        if (id.size() == 1) return;
        for (int i(1); i<=n; ++i) vid[find(i)].push_back(i);
        for (auto i: id) if (!vis[i]){
            for (auto j: vid[find(i)]) Trie::del(a[j]);
            pair<int, int> res(INT_MAX, 0);
            for (auto j: vid[find(i)]){
                auto p(Trie::query(a[j]));
                if (p.first < res.first) res = p;
            }
            for (auto j: vid[find(i)]) Trie::ins(a[j], j);
            f[find(i)] = find(res.second); vis[find(res.second)] = vis[i] = 1;
            ans += res.first;
            // cout << res.first << ' ' << res.second << '\n';
        }
        for (auto i: id) vis[i] = 0;
        for (int i(1); i<=n; ++i) vid[i].clear();
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n; for (int i(1); i<=n; ++i) cin >> a[i];
    sort(a+1, a+n+1); n = unique(a+1, a+n+1)-(a+1);
    for (int i(1); i<=n; ++i) Trie::ins(a[i], i);
    boruvka(); cout << ans;

    return 0;
}
```

---

## 作者：tonylin1026 (赞：4)

校内模拟赛竟然考到这题神题，太神奇了。
~~只不过数据范围减半就弱很多~~

主要方法是Trie+DFS（大佬的最短路太巨了根本没学过

由于异或的特性，异或值大小取决于二进制下相同位置01值相同的数量，最小代价就是相同的多，所以可以看成两颗子树的合并。

所以我们设置一个size数组，若根的两端都有节点就进行合并：枚举一个子树中的所有树，到另一个子树中查找最小异或和，更新答案。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int N=200010,INF=0x3f3f3f3f;
int n,tot=1;
long long cost,ans;
int ch[N<<5][2],si[N<<5],val[N<<5],num[N<<5];
inline int read()//养成函数加inline，大数据写快读的好习惯（不
{
	int f=1,ret=0;char c=getchar();
	while(c>'9'||c<'0')
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0')
	{
		ret=ret*10+c-'0';
		c=getchar();
	}
	return f*ret;
}
inline void insert(int a)
{
	int u=0;
	for(int i=1<<30;i;i>>=1)
	{
		int c=(a&i)?1:0;
		if(!ch[u][c])
		{
			memset(ch[tot],0,sizeof(ch[tot]));
			num[tot]=val[tot]=0;
			ch[u][c]=tot++;
		}
		u=ch[u][c];
		num[u]++;
	}
	val[u]=a;
}//trie树读入
inline int gets(int x)
{
	if(!ch[x][0]&&!ch[x][1])
		return si[x]=1;
	if(ch[x][0]) si[x]+=gets(ch[x][0]);
	if(ch[x][1]) si[x]+=gets(ch[x][1]);
	return si[x];
}//初始化size
inline int query(int x,int p)
{
	int u=0;
	for(int i=1<<30;i;i>>=1)
	{
		int c=(x&i)?1:0;
		if(!ch[u][c])
			c=1-c;
		if(p==u) c=1-c;
		u=ch[u][c];
	}
	return u;
}
inline void calc(int x,int u)
{
	if(ch[x][0]) calc(ch[x][0],u);
	if(ch[x][1]) calc(ch[x][1],u);
	if(!ch[x][0]&&!ch[x][1])
	{
		int c=query(val[x],u);
		cost=min(cost,(long long)val[c]^val[x]);
	}
}
inline void dfs(int x)
{
	if(ch[x][0]) dfs(ch[x][0]);
	if(ch[x][1]) dfs(ch[x][1]);
	if(ch[x][0]&&ch[x][1])
	{
		cost=INF;
		int lson=ch[x][0],rson=ch[x][1];
		if(si[lson]<si[rson]) calc(lson,x);
		else calc(rson,x);//根据深度大小判断
		ans+=cost;
	}
}//dfs部分
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		int a;
		a=read();
		insert(a);
	}
	gets(0);
	dfs(0);
	cout<<ans;//震惊！用scanf竟然会溢出！
	return 0;
}
```

---

## 作者：foreverlasting (赞：2)

[题面](https://www.luogu.org/problemnew/show/CF888G)

最小生成树是+Trie。

这题好神啊，完全不会，看了题解才知道这题需要第三种最小生成树的做法啊，那个好像叫Sollin(Boruvka)算法，具体原理看这篇博客：[这里](https://blog.csdn.net/djs_k_d/article/details/48131303)。那个算法就是慢慢减半连通块数量，那在这题里在减少的时候维护一棵Trie树就好了。

code:
```
//2018.9.16 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y){
    return x<y?x:y;
}
const int N=2e5+10;
namespace MAIN{
    namespace Trie{
        struct Trie{
            int son[2];
        }tr[N<<5];
        int cnt;
        inline void clean(const res &x){
            memset(tr[x].son,0,sizeof(tr[x].son));
        }
        void insert(res &x,const res &w,const res &p){
            if(!x)x=++cnt,clean(cnt);
            if(p==-1)return;
            insert(tr[x].son[(w>>p)&1],w,p-1);
        }
        int query(const res &x,const res &w,const res &p) {
            if(p==-1)return 0;
            res c=(w>>p)&1;
            return tr[x].son[c]?query(tr[x].son[c],w,p-1):query(tr[x].son[c^1],w,p-1)^(1<<p);
        }
    }
#define pb push_back
    int n;
    LL solve(vector<int> qaq,const res &p){
        if(!qaq.size()||p==-1)return 0;
        vector<int> vec[2];
        for(res i=0,siz=qaq.size();i<siz;i++)vec[(qaq[i]>>p)&1].pb(qaq[i]);
        res ret=0,rt;
        if(vec[0].size()&&vec[1].size()){
            ret=1<<(p+1);
            rt=0;
            Trie::cnt=0;
            for(res i=0,siz=vec[0].size();i<siz;i++)Trie::insert(rt,vec[0][i],30);
            for(res i=0,siz=vec[1].size();i<siz;i++)ret=_min(ret,Trie::query(rt,vec[1][i],30));
        }
        return ret+solve(vec[0],p-1)+solve(vec[1],p-1);
    }
    inline void MAIN(){
        n=read();
        vector<int> a;
        for(res i=1;i<=n;i++)a.pb(read());
        printf("%lld\n",solve(a,30));
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

