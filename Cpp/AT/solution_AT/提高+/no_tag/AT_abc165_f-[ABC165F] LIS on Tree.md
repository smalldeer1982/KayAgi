# [ABC165F] LIS on Tree

## 题目描述

给您一棵$n$个节点的树，树的每个节点上都有一个值$a_i$。现在要您求出从$1$号点到$i$号点的路径上最长上升子序列的长度。

## 说明/提示

$2\le n\le 2e5,a_i\le 1e9, u\le n,v\le n,u\neq v$

## 样例 #1

### 输入

```
10
1 2 5 3 4 6 7 3 2 4
1 2
2 3
3 4
4 5
3 6
6 7
1 8
8 9
9 10```

### 输出

```
1
2
3
3
4
4
5
2
2
3```

# 题解

## 作者：ctq1999 (赞：10)

## 题解

题意简述：求树上的$\text{LIS(Longest Increasing Sequence)}$。

树上序列的题，先知道在一个序列上怎么求后，直接套树上，遍历完子树时回溯即可。

所以我开题顺序是 $ABFCD$，$E$ 没做出来（（。

我的方法是二分做的。

首先先看一个序列 $a[]$ 上处理的方式。

建立一个数组 $f[i]$，含义是长度为 $i$ 的 $\text{LIS}$ 的结尾是 $f[i]$ 。 $ans[i]$ 表示 $[1,n]$ 中 $\text{LIS}$ 最大的长度的值。

对于第一个数，$ans[1]=1$，$f[1]=a[1]$。

对于之后的数，二分出最大的 $f[j]$，且 $f[j]<a[i]$。所以 $f[j+1]=a[i]$。如果 $j+1>ans[i-1]$，那么 $ans[i]=ans[i-1]+1$，否则 $ans[i]=ans[i-1]$。

那么转移到树上的话，显然回溯时需要修改的是 $f[]$。

如果还不明白，就是你想想 $dfs$ 遍历树的过程，第一次会一直沿左子节点一直遍历。那么遍历的就是一个序列，中间计算并更新这几个节点的 $ans[]$。到了叶节点后下一个就要遍历当前节点的兄弟节点（节点的父亲的右节点），故之前更新的 $f[]$ 要变回原来的数，再遍历当前节点的兄弟节点。

## 代码

```cpp
#include <bits/stdc++.h>

#define ll long long

using namespace std;

const int MAXN = 200010;
const int MAXM = 100010;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;

int n, m, k;
int tot, cnt;

int a[MAXN], f[MAXN], ans[MAXN];
int head[MAXN];

struct edge {
	int to, next;
}e[MAXN * 2];

void add_edge(int x, int y) {
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
	return;
}

void Dfs(int x, int fa) {
	int last;
	int l = 1, r = ans[fa], mid;
	if (!fa) f[1] = a[x], ans[1] = 1;
	else {
		while (l <= r) {
			mid = (l + r) >> 1;
			if (a[x] <= f[mid]) r = mid - 1;
			else l = mid + 1;
		}
		last = f[l];
		f[l] = a[x];
		ans[x] = ans[fa];
		if (l > ans[fa]) ++ans[x];
	}
	for (int i = head[x]; i; i = e[i].next) {
		int v = e[i].to;
		if (v != fa) Dfs(v, x);
	}
	f[l] = last;
	return;
}

int main(){
	int t;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	
	Dfs(1, 0);
	
	for (int i = 1; i <= n; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}
```

码风好看吧/cy


---

## 作者：Sqrtyz (赞：4)

博客内阅读效果更佳，感谢您的阅读。

### 题意

给定一棵 $n$ 个点的树，每个点上都有一个值。对于每个树上的点 $k \in [1,n]$，求出由 $1$ 径直走到 $k$ 所经过的值形成的序列的最长严格上升子序列。

### 解题

如果是在序列上跑 LIS，想必大家都已经了解其 $O(n \log n)$ 的解法。可以用 树状数组 / 贪心 + 二分 的方式来解决。没有学过 $O(n \log n)$ 求 LIS 的同学可以参见 [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)，在此就不再赘述。

想了想这道题是在树上，用树状数组不是很好操作（如果您有树状数组解法可以评论），于是考虑用后一种方法。

令 $low_i$ 表示从 $1$ 到当前位置所形成的序列中长为 $i$ 的上升子序列的末尾所能达到的最小数字。

我们 dfs 遍历此树。现在唯一的问题是，由于我们是按 dfs 序遍历，我们在回溯时需要撤回一些操作。

回顾维护 $low$ 数组的方法——我们是如何维护 $low$ 数组的？

+ 当 $val_u > low_{len}$，令 `low[++len] = val[u]`。

+ 当 $val_u \leq low_{len}$，二分查找满足 $low_i < val_u \leq low_{i+1}$ 的位置，把 $low_{i+1}$ 替换为 $val_u$。

显然我们每次经过一个点，都只会对 $low$ 数组中 $1$ 个位置进行修改 —— 因此我们只需要记录下 $low$ 数组修改的位置和修改前该位置的值，在回溯时还原就可以了。

细节还请移步代码。

### 程序

```cpp

int n, f[Maxn], val[Maxn], low[Maxn];

struct Edge {
    int next, to;
}
edge[Maxn * 2];
int head[Maxn], edge_num = 1;

void add_edge(int from, int to) {
    edge[++edge_num].next = head[from];
    edge[edge_num].to = to;
    head[from] = edge_num;
}

pair <int, int> update(int l, int r, int v) {
    while(l < r) {
        int mid = (l + r) >> 1;
        if(low[mid] < v) l = mid + 1;
        else r = mid;
    }
    int temp = low[l];
    low[l] = v;
    return make_pair(l, temp);
} // 二分 + 贪心 部分

void dfs(int u, int fa, int len) {
    bool flag;
    pair <int, int> info;
    if(val[u] > low[len]) low[++len] = val[u], flag = 1;
    else info = update(0, len, val[u]), flag = 0;
    f[u] = len;
    for(int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if(v == fa) continue;
        dfs(v, u, len);
    }
    if(flag) low[len] = 0;
    else low[info.first] = info.second;
} // 按 dfs 序进行遍历

int main() {
    n = read();
    for(int i = 1; i <= n; ++i) val[i] = read();
    int u, v;
    for(int i = 1; i < n; ++i) {
        u = read(); v = read();
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, 0, 0);
    for(int i = 1; i <= n; ++i) printf("%d\n", f[i]);
    return 0;
}
```


---

## 作者：yuzhechuan (赞：3)

既然没有树状数组题解我就来水一篇

---

### 题解：

既然是正常LIS的树上版，那我们就在原做法——树状数组维护dp的基础上套个dfs来遍历这棵树

由于树状数组维护的是前缀max，而max无法直接回撤，所以我们在修改时可以同时保存原值，最后再用原值覆盖回来就好了

由于一个点最多需保存log个原值，所以空间复杂度是一只log的，与时间相同

要注意的是题目问的是链上的LIS，而我们得到的是以i结尾的LIS，所以最后还要做一遍树上前缀max，得到最终答案

---

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#ifdef ONLINE_JUDGE
#define getchar gc
inline char gc(){
	static char buf[1<<16],*p1=buf,*p2=buf;
	if(p1==p2){
		p2=(p1=buf)+fread(buf,1,1<<16,stdin);
		if(p2==p1) return EOF;
	}
	return *p1++;
}
#endif
template<class t> inline t read(t &x){
    char c=getchar();bool f=0;x=0;
    while(!isdigit(c)) f|=c=='-',c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f) x=-x;return x;
}
template<class t> inline void write(t x){
    if(x<0) putchar('-'),write(-x);
    else{if(x>9) write(x/10);putchar('0'+x%10);}
}

const int N=2e5+5;
int num[N],n,un,a[N],tr[N],ans[N],tp[N][21],cur;
vector<int> g[N];

#define lowbit(x) (x&(-x))

void up(int x,int v){
	while(x<=un){
		tp[cur][++tp[cur][0]]=tr[x]; //保存原值
		tr[x]=max(tr[x],v);
		x+=lowbit(x);
	}
}

int que(int x){
	int res=0;
	while(x){
		res=max(res,tr[x]);
		x-=lowbit(x);
	}
	return res;
}

void reset(int x){
	int n=0;
	while(x<=un){
		tr[x]=tp[cur][++n]; //用原值覆盖
		x+=lowbit(x);
	}
}

void dfs(int x,int fa){
	ans[x]=que(a[x]-1)+1;
	cur=x;
	up(a[x],ans[x]);
	for(int y:g[x]) if(y^fa) dfs(y,x);
	cur=x;
	reset(a[x]);
}

void pre(int x,int fa){ //取个树上前缀max
	ans[x]=max(ans[x],ans[fa]);
	for(int y:g[x]) if(y^fa) pre(y,x);
}

signed main(){
	read(n);
	for(int i=1;i<=n;i++) num[i]=read(a[i]);
	sort(num+1,num+1+n);
	un=unique(num+1,num+1+n)-num-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(num+1,num+1+un,a[i])-num;
	for(int i=1,x,y;i<n;i++){
		read(x);read(y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1,0);
	pre(1,0);
	for(int i=1;i<=n;i++) write(ans[i]),puts("");
}
```

---

## 作者：Others (赞：3)

这是一道很水的题······

树上 LIS，首先看树的节点个数是 $10^5$ 级别，所以普通的 dp 的 $O(n^2)$ 是过不了的，于是我们就要搞一下这个 dp 的本质了，这样才能优化。

我们将 $dp_i$ 的定义更改为：当前的 LIS 的最优情况的数组，也就是说我们每次就将一个元素处理进这个集合就行了，那么我们想想：这个最优情况指的是每个元素都在合理范围内最小（合理范围：符合 LIS 的定义），这样就有了一个 naive 的想法：我们就将它可以替换的比它大的数换掉，这样就可以让这个序列更优或者没有改变，这里就可以二分了。

在树上求就是一个 dfs，很常规，这里打个 $vis_i$ 标记一下，就是遍历 $n$ 次就完了，然后每次都是一个二分，也就是 $O(n\log n)$ 的复杂度就轻松的过去了，最后记得打回溯 qwq。

**code**

```cpp
#include <bits/stdc++.h>
using namespace std;
int head[200005],nxt[400006],to[400005],cnt,dp[200005],top,fa[200005],ans[200005],a[200005],p,q,n;
void add(int u,int v){//加边 
	nxt[++cnt]=head[u],head[u]=cnt,to[cnt]=v;
}
void dfs(int x){
	int tmp=lower_bound(dp+1,dp+top+1,a[x])-dp;//找到插进去的位置 
	int Tmp=dp[tmp];//方便回溯 
	dp[tmp]=a[x];//修改 
	int flag=0;//看下一行 
	if(tmp==top+1) flag++,top++;//是不是可以在序列后面再加一位 
	ans[x]=top;//存答案 
	for(int i=head[x];i;i=nxt[i]){//遍历出边 
		if(to[i]!=fa[x]){//如果不是爸爸 
			fa[to[i]]=x;//更新父节点 
			dfs(to[i]);//继续 dfs 
		}
	}
	if(flag) top--;//回溯 1 
	dp[tmp]=Tmp;//回溯 2 
	return;
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<n;i++){
		scanf("%d%d",&p,&q);
		add(p,q),add(q,p);//树上的是没说方向的 
	}
	dfs(1);//搞答案 
	for(int i=1;i<=n;i++){//输出就完事了 
		printf("%d",ans[i]);
		if(i<n) putchar('\n');
	}
	return 0;
}
```

---

## 作者：chenxia25 (赞：2)

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/AT5392) & [AtCoder题目页面传送门](https://atcoder.jp/contests/abc165/tasks/abc165_f)

>给定一棵大小为$n$的树，求对于每个点，$1$到这个点组成的序列的LIS。

>$n\in\left[1,2\times10^5\right]$。

（这是我第一个做出来的题）

考虑跟普通的线性结构上的LIS设类似的状态，状态转移方程也类似。

普通的线性LIS可以用BIT优化，而这里树上DFS回溯的时候需要撤销，我们可以对于每个离散化后的值开一个`multiset`来撤销，每次将`multiset`中最大的数扔到BIT里。可是，这样有可能变小，BIT是处理不了的，于是可以用线段树维护。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int N=200000;
int n;
int a[N+1];
vector<int> nums;
void discrete(){//离散化 
	sort(nums.begin(),nums.end());
	nums.resize(unique(nums.begin(),nums.end())-nums.begin());
	for(int i=1;i<=n;i++)a[i]=lower_bound(nums.begin(),nums.end(),a[i])-nums.begin();
}
vector<int> nei[N+1];
multiset<int> st[N];
struct segtree{//线段树 
	struct node{int l,r,mx;}nd[N<<2];
	#define l(p) nd[p].l
	#define r(p) nd[p].r
	#define mx(p) nd[p].mx
	void bld(int l=0,int r=nums.size()-1,int p=1){
		l(p)=l;r(p)=r;mx(p)=0;
		if(l==r)return;
		int mid=l+r>>1;
		bld(l,mid,p<<1);bld(mid+1,r,p<<1|1);
	}
	void init(){bld();}
	void sprup(int p){mx(p)=max(mx(p<<1),mx(p<<1|1));}
	void chg(int x,int v,int p=1){//单点修改 
		if(l(p)==r(p))return mx(p)=v,void();
		int mid=l(p)+r(p)>>1;
		chg(x,v,p<<1|(x>mid));
		sprup(p);
	}
	int _mx(int l,int r,int p=1){//区间最大值 
		if(l>r)return 0;
		if(l<=l(p)&&r>=r(p))return mx(p);
		int mid=l(p)+r(p)>>1,res=0;
		if(l<=mid)res=max(res,_mx(l,r,p<<1));
		if(r>mid)res=max(res,_mx(l,r,p<<1|1));
		return res;
	}
}segt;
int dp[N+1],ans[N+1];
void dfs(int x=1,int fa=0){ 
	dp[x]=segt._mx(0,a[x]-1)+1;//转移方程 
	ans[x]=max(ans[fa],dp[x]);
	st[a[x]].insert(dp[x]);
	segt.chg(a[x],*--st[a[x]].end());
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];
		if(y==fa)continue;
		dfs(y,x);
	}
	st[a[x]].erase(st[a[x]].find(dp[x]));//回溯时撤销 
	segt.chg(a[x],*--st[a[x]].end());//撤销 
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],nums.pb(a[i]);
	discrete();
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		nei[x].pb(y);nei[y].pb(x);
	}
	for(int i=0;i<nums.size();i++)st[i].insert(0);
	segt.init();
	dfs();
	for(int i=1;i<=n;i++)cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：gyh20 (赞：2)

之前我们求 LIS 有两种做法，二分或树状数组。

而树状数组可以由另一种数据结构代替 -> 线段树。

再看树上的问题，我们其实是以父亲的状态为历史状态来建立线段树并插入一个点，很容易想到可持久化线段树/主席树来查找区间最大值。

可以直接去搬个模板，所以其实不用写太多。

这种方法思维难度极低，基本是一眼看出来，代码难度也不算高，可以去搬模板或者手打一遍。

最后记得要与父亲的答案取 $\max$ ，因为它询问的是路径的 LIS 而不是以某一个点结束的 LIS，因此我赛时没做出来（还是太菜了）。

代码：
```cpp
#include<bits/stdc++.h>
#define in inline
#define re register
using namespace std;
in int read() {
	re int t=0;
	re char v=getchar();
	while(v<'0'||v>'9')v=getchar();
	while(v>='0'&&v<='9') {
		t=(t<<3)+(t<<1)+(v^48);
		v=getchar();
	}
	return t;
}
int n,m,rt[200002],head[200002],a[200002],ls[20000002],rs[20000002],ans[200002],u,v,cnt,tot,s[20000002],la,r[200002],val[20000002];
struct edge{
	int to,next;
}e[400002];
inline void bu(re int x,re int y){
	e[++tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}
inline int insert(re int v,re int l,re int r,re int x,re int vv) {
	int y=++cnt;
	s[y]=s[x]+1;val[y]=max(val[x],vv);
	if(l==r)return y;
	ls[y]=ls[x];rs[y]=rs[x];
	int mid=(l+r)>>1;
	if(v<=mid)ls[y]=insert(v,l,mid,ls[x],vv);
	else rs[y]=insert(v,mid+1,r,rs[x],vv);
	return y;
}
inline int find(re int p,re int l,re int r,re int x){
	if(!p)return 0;
	if(r<=x)return val[p];
	re int mid=l+r>>1;
	if(x>mid)return max(find(ls[p],l,mid,x),find(rs[p],mid+1,r,x));
	else return find(ls[p],l,mid,x);
}
inline void dfs(re int x,re int y){
	ans[x]=find(rt[y],1,1e9+1,a[x]);
	rt[x]=insert(a[x]+1,1,1e9+1,rt[y],ans[x]+1);
	ans[x]=max(ans[x],ans[y]);
	for(re int i=head[x];i;i=e[i].next)
		if(e[i].to!=y)dfs(e[i].to,x);
}
int main(){
	n=read();
	for(re int i=1;i<=n;++i)a[i]=read();
	for(re int i=1;i<n;++i){
		u=read();v=read();
		bu(u,v);bu(v,u);
	}
	dfs(1,1);
	for(re int i=1;i<=n;++i)printf("%d\n",ans[i]+1);
}

```


---

## 作者：Grisses (赞：1)

[题面](https://www.luogu.com.cn/problem/AT5392)

本题是一道搜索题。我们从根节点往下遍历，选取最长上升子序列。但是，如果我们直接每一个点都跑一遍 DP 的话，肯定是会 TLE 的。所以我们需要采取一些措施。

我们设现在遍历到了 $x$ 节点，它的值为 $a_x$。另外，我们开一个数组 $f$ 来存储最长上升子序列，$len$ 是它的长度。

如果 $a_x>f_{len}$，那么说明 $x$ 可以加入最长上升子序列，那就加入。否则我们就用 $a_x$ 将第 1 个大于等于 $a_x$ 的值给换下来，有利于之后的加入元素。

代码：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,cnt,tot,a[200005],f[200005],ans[200005],h[200005];
  bool vis[200005];
  //前项星
  struct edge{
      int v,nxt;
  }e[400005];
  void adde(int u,int v){
      e[++cnt].nxt=h[u];
      h[u]=cnt;
      e[cnt].v=v;
  }
  //搜索
  void dfs(int x){
      if(vis[x])return;
      vis[x]=1;
      bool F=0;
      int t,X;
      if(a[x]>f[tot])f[++tot]=a[x],F=1;//直接加入
      else{
          t=lower_bound(f+1,f+tot+1,a[x])-f;//替换
          X=f[t];
          f[t]=a[x];
      }
      ans[x]=tot;
      for(int j=h[x];j;j=e[j].nxt){
          dfs(e[j].v);//往下一层搜索
      }
      if(F)tot--;//回溯要将其恢复成原来的样子
      else f[t]=X;
  }
  int main()
  {
      scanf("%d",&n);
      for(int i=1;i<=n;i++)scanf("%d",&a[i]);
      for(int i=1,x,y;i<n;i++)scanf("%d%d",&x,&y),adde(x,y),adde(y,x);//建边
      dfs(1);//从根节点开始搜索
      for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
      return 0;
  }
```

---

## 作者：BotYoung (赞：1)

## AT5392 题解
**前置知识：树形结构、线性 DP**

考验读题能力的一道好题。题目大意很简单，就是把一个简单的线性 DP 移植到了树上。

但是这道题有一个难点：即给定的树是一棵无根树，也就是说边是无向的。所以说在输入时应该建立一条双向的边。

参考下面的一段错误代码：
```cpp
for (int i = 1; i < n; i++) {
        scanf("%d %d", &x, &y);
        G[x].push_back(y);
    }
/*可以看到在输入时没有在y->x方向上建边*/
```

至于最长上升子序列，在遍历树时打一个记忆化搜索就可以，萌新可以参考下面的DP状态转移方程：
$$DP[i] = \max(DP[j]+1)$$
其中 $j$ 满足 $a[j]<a[i]$。直接枚举的暴力思路在算法竞赛中很常见，但是在这道题中显然不适用，因为 $n \leq 2 \times 10^5$，同时又有数据结构的限制。

因此我们要在原来状态的基础上做一个优化。引入 LIS 问题的优化算法--二分法。这种算法刚开始可能很难理解，它在原先的状态转移方程的基础上进行了改动。考虑贪心的思想，优先选择较小的数可以使后来增加的数的取值变小，意味着我们可以选择更多的数，可以构造出一个符合条件的序列，让序列的长度表示当前 LIS 的长度。当一个新数加入时，用二分法查看它能够在原序列中替换的位置，这里的“替换”是暂时的，并不是当前的序列。真正的序列应该取决于当前序列的最后一个元素，只有这个数改动，才意味着序列发生了变化。

最后我们根据构造好的最终“序列”的长度，判断出 LIS 的长度。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, x, y, a[200005], dp[200005], f[200005], tot, ans;
//tot表示当前序列的长度
//f[i]表示以i为一棵子树的根时，序列的长度 
vector<int> G[200005];
//用邻接表表示树 
bool vis[200005];
//vis判断是否走过，因为是无向边 
void dfs(int rt){//因为我们的目的是找一条链，所以用DFS遍历，同时方便记忆化。 
	vis[rt] = 1;
	ans = max(ans, tot);
	int l, r, t, mid;
	bool flag = 0;
	if (!tot || a[rt] > dp[tot]) dp[++tot] = a[rt], flag = 1;
	//判断能否在序列的末尾增加新元素
	//如果可以则加入，并将序列长度增加一 
	else{
		l = 1, r = tot;
		while (l <= r) {
            mid = (l + r) >> 1;
            if (dp[mid] >= a[rt])
                r = mid - 1;
            else
                l = mid + 1;
        }
        t = dp[l];
        dp[l] = a[rt];
        //否则就在原序列中“替换”一个数
		//此时“序列”长度不变 
	}
	f[rt] = tot;
	for (int i = 0; i < G[rt].size(); i++)
		if (!vis[G[rt][i]]) dfs(G[rt][i]);
	//对下一个节点进行遍历 
	if (flag) dp[tot] = 0, tot--;
	else dp[l] = t; 
	//在回溯时撤回当前的操作 
}
int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i < n; i++){
		scanf("%d %d", &x, &y);
		G[x].push_back(y);
		G[y].push_back(x);//正确的建树方法 
	}
	dfs(1);//dfs遍历树 
	for (int i = 1; i <= n; i++)
		printf("%d\n", f[i]);//按要求输出 
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：1)

### 前置知识
[最长上升子序列](https://www.cnblogs.com/frankchenfu/p/7107019.html)，在二分的优化下可以达到 $O(n\log n)$。
### 算法分析
建边后，我们从最长上升子序列的角度出发，我们的答案 $ans_i$ 就是 dp 数组的元素个数 top，然后 $ans_i\gets top$，我们注意分类讨论，也就是回溯法，把每次更改的值在操作后改回去，最后输出答案，时间复杂度 $O(n\log n)$，可以过，AC！
### AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int n,a[maxn],dp[maxn],ans[maxn],top,len[maxn];
bool vis[maxn];
vector<int> son[maxn]; 
void dfs(int id){
	if(vis[id])
		return;
	vis[id]=1;
	bool p=0;
	int f=0,k=0;
	if(a[id]>dp[top])
		dp[++top]=a[id],p=1;
	else{
		f=lower_bound(dp+1,dp+top+1,a[id])-dp,k=dp[f];
		dp[f]=a[id];
	}//最长上升子序列
	ans[id]=top;
	for(int i=0;i<len[id];i++)
		dfs(son[id][i]);
	if(p)
		dp[top--]=0;
	else
		dp[f]=k;//回溯
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for(int u,v,i=1;i<n;++i){
		scanf("%d%d",&u,&v);
		son[u].push_back(v);
		son[v].push_back(u);
	}
	for(int i=1;i<=n;++i)
		len[i]=son[i].size();
	vis[1]=ans[1]=1;
	for(int i=0;i<len[1];++i){
		top=1,dp[1]=a[1];
		dfs(son[1][i]);
	}
	for(int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
	return 0;
} 
```

---

