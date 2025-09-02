# Distance in Tree

## 题目描述

给定一棵 $n$ 个节点的树和一个正整数 $k$。求树上有多少对 $(u,v)$，其距离恰好为 $k$。

注意 $(u,v)$ 和 $(v,u)$ 算作同一对节点。

## 说明/提示

### 样例解释

样例 #1 中距离为 $2$ 的节点有四对：$(1,3),(1,5),(3,5),(2,4)$。

### 数据范围

$1 \leq n \leq 50000$，$1 \leq k \leq 500$。

## 样例 #1

### 输入

```
5 2
1 2
2 3
3 4
2 5
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 3
1 2
2 3
3 4
4 5
```

### 输出

```
2
```

# 题解

## 作者：Rhodoks (赞：47)

# 愉快的一题多解

### 树形$dp$

由于$k$限制在了$500$的范围之内，所以儿子节点状态的暴力合并实际上也是可以接受的，这就是树形$dp$的做法了。

复杂度$O(nk)$

部分代码：

```cpp
//LINK(i,g,pos)指在图g中用变量i遍历点pos所连边
//RPT(i,st,en)指for (int i=st;i<en;++i)计数循环
//下同
void dfs(int pos,int f)
{
	dp[pos][0]=1;
	LINK(i,g,pos)
		if (g.to[i]!=f)
		{
			dfs(g.to[i],pos);
			RPT(j,0,k)
				ans+=dp[g.to[i]][j]*dp[pos][k-j-1];
			RPT(j,0,k)
				dp[pos][j+1]+=dp[g.to[i]][j];
		}
}
```


### 树上启发式合并

如果不限制$k$呢？那么子树暴力合并的时间代价就难以承受。不过，保留重儿子状态的$dsu~on~tree$做法能做到$O(nlogn)$的优秀复杂度。

部分代码：

```cpp
//son数组为重儿子，在dfs1中已预处理
void calc(int pos,int top)
{
	ans+=buc[k-depth[pos]+2*depth[top]];
	LINK(i,g,pos)
		if (g.to[i]!=pa[pos])
			calc(g.to[i],top);
}

void add(int pos)
{
	buc[depth[pos]]++;
	LINK(i,g,pos)
		if (g.to[i]!=pa[pos])
			add(g.to[i]);
}

void del(int pos)
{
	buc[depth[pos]]=0;
	LINK(i,g,pos)
		if (g.to[i]!=pa[pos])
			del(g.to[i]);
}

void dfs2(int pos,int topf)
{
	LINK(i,g,pos)
		if (g.to[i]!=son[pos] && g.to[i]!=pa[pos])
			dfs2(g.to[i],g.to[i]);
	if (son[pos])
		dfs2(son[pos],topf);
	ans+=buc[depth[pos]+k];
	buc[depth[pos]]++;
	LINK(i,g,pos)
		if (g.to[i]!=son[pos] && g.to[i]!=pa[pos])
		{
			calc(g.to[i],pos);
			add(g.to[i]);
		}
	if (pos==topf)
		del(pos);
}
```

### 长链剖分

鉴于状态是和深度相关的，那么自然而然地我们可以使用长链剖分去做这题。思想和树形$dp$类似，但通过指针的灵活运用，我们可以不用再做繁琐的转移。

时间复杂度很优秀$O(n)$

部分代码：

```cpp
//son为长儿子数组
//len为子树深度数组（叶子节点为1）
//ptr为指针数组
void add(int pos,int to)
{
	RPT(i,max(0,k-len[pos]),min(len[to],k))
		ans+=ptr[to][i]*ptr[pos][k-i-1];
	RPT(i,0,len[to])
		ptr[pos][i+1]+=ptr[to][i];
}

void dfs2(int pos,int topf)
{
	if (pos==topf)
	{
		ptr[pos]=pool+cnt;
		cnt+=len[pos];
	}
	else
		ptr[pos]=ptr[pa[pos]]+1;
	LINK(i,g,pos)
		if (g.to[i]!=son[pos] && g.to[i]!=pa[pos])
			dfs2(g.to[i],g.to[i]);
	if (son[pos])
		dfs2(son[pos],topf);
	if (k<len[pos])
		ans+=ptr[pos][k];
	ptr[pos][0]++;
	LINK(i,g,pos)
		if (g.to[i]!=son[pos] && g.to[i]!=pa[pos])
			add(pos,g.to[i]);
}
```

### 点分治

是时候祭出点分治了。

部分代码：

```cpp
void getdis(int pos,int f,int len)
{
	if (len>k)
		return;
	dis[cnt++]=len;
	LINK(i,g,pos)
		if (g.to[i]!=f && !visit[g.to[i]])
			getdis(g.to[i],pos,len+1);
}

void conquer(int pos)
{
	LINK(i,g,pos)
		if (!visit[g.to[i]])
		{
			int tmp=cnt;
			getdis(g.to[i],pos,1);
			RPT(j,tmp,cnt)
				ans+=buc[k-dis[j]];
			RPT(j,tmp,cnt)
				buc[dis[j]]++;
		}
	RPT(j,0,cnt)
		buc[dis[j]]--;
	cnt=0;
}

void divide(int pos)
{
	buc[0]=1;
	conquer(pos);
	visit[pos]=true;
	LINK(i,g,pos)
		if (!visit[g.to[i]])
		{
			core=0;
			sumsize=size[pos];
			mx[0]=INF; 
			getcore(g.to[i],pos);
			divide(core);
		}
}
```



### update 2021/2/14: 修正错误


---

## 作者：vacation (赞：30)

题意简述（copy 题面）  
输入点数为N一棵树  
求树上长度恰好为K的路径个数  

看见julao们的题解都这么长，蒟蒻瑟瑟发抖。  
  
这道题我们可以用树形DP做  
dfs便为树形DP过程  
笔者在这里用了动态数组（防止爆空间），来存储邻接链表。 

设f[i][j]为以i为根的子树中距离根距离为j的点有多少个。    
对于我们现在所处的点now，我们枚举它的子节点v，则我们可以计算出经过以now-v为顶点的这条边的答案  
我们从1到k进行枚举，则我们可以推出ans+=(dp[now][j]*dp[to][k-j-1])  
枚举完以后，我们将这一棵子树合并到now节点去，dp[now]j+1]+=dp[to][j];    
再统计now的其它子树。  
于是我们就愉快地dfs。  
不要忘记设计初值，对于每个叶子结点now，f[now][0]=1。 
然后不断向上回溯进行如上计算，最后即可算出正确答案。  
其实就是暴力啦（逃  
这道题用点分治做是很简单的（~~可惜我不会~~）  


代码如下所示


```cpp
#include <bits/stdc++.h>
using namespace std;
int dp[50050][505],n,k,m,c;
long long ans=0;
vector <int> v[50050];
void dfs(int now,int p)
{
    dp[now][0]=1;
    for (int i=0;i<v[now].size();i++)
    {
        int to=v[now][i];
        if (to!=p)
        {
            dfs(to,now);
            for (int j=0;j<k;j++) ans+=(dp[now][j]*dp[to][k-j-1]);
            for (int j=0;j<k;j++) dp[now][j+1]+=dp[to][j];
        }
    }
}
int main()
{
    cin>>n>>k;
    for (int i=1;i<n;i++)
    {
        int x,y;
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    dfs(1,0);
    cout<<ans;
    return 0;
}
```


---

## 作者：MyukiyoMekya (赞：15)

题意：

输入点数为N的一棵树，求树上长度恰好为K的路径个数

---

```
    A
   / \
  B   C
     / \
    D   E
```

我们先dp出 $u$ 节点到 $u$ 子树内的叶子的那种链（比如$A\leftrightarrow B$ , $A \leftrightarrow C \leftrightarrow D$ ）的长度 $i$ 以及其个数，记为 $f_{u,i}$

显然，转移方程为 $f_{u,i}=\sum f_{v,i-1}$，$v$ 是 $u$ 的儿子 

那么我们分两类讨论

一类就是  $u$ 节点到 $u$ 子树内的叶子链的长度为 $k$ ，比如 $A\leftrightarrow B$ , $A \leftrightarrow C \leftrightarrow D$ 那么这里 $u$ 节点对答案的贡献就为 $ans_1=f_{u,k}$

我们还可以把两条这种形状的链拼在一起，比如把 $A\leftrightarrow B$ , $A \leftrightarrow C \leftrightarrow D$ 拼在一起变成 $B \leftrightarrow A \leftrightarrow C \leftrightarrow D$ ，也就是要从 $u$ 的每两个子节点中算答案，这里不用暴力枚举，有一种巧妙地做法
$$
ans_2=\sum \{(f_{u,k-i}-f_{v,k-i-1})\times f_{v,i-1}\}
$$
两个 $-1$ 都是因为 $u \leftrightarrow v$ 有一条边

这个柿子的意思就是说，在 $v$ 子树中选长度为 $i-1$ 的链，然后和 $u$ 子树中长度为 $k-i$ 的链匹配，因为 $f_{u,0}$ 子树之前已经把 $v$ 子树的链统计过了，所以要先减去，这样就不会算重

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define reg register
#define int long long
using namespace std;
const int MaxN=50005;
const int MaxK=505;
struct Edge
{
	int nxt,to;
}E[MaxN<<1];
template <class t> inline void rd(t &s)
{
	s=0;
	reg char c=getchar();
	while(!isdigit(c))
		c=getchar();
	while(isdigit(c))
		s=(s<<3)+(s<<1)+(c^48),c=getchar();
	return;
}
int n,k,en,ans;
int hd[MaxN];
int f[MaxN][MaxK];
inline void adde(int u,int v)
{
	++en;
	E[en].nxt=hd[u];
	E[en].to=v;
	hd[u]=en;
	return;
}
inline void dfs(int u,int fa)
{
	f[u][0]=1;
	for(int i=hd[u];~i;i=E[i].nxt)
	{
		reg int v=E[i].to;
		if(v==fa)
			continue;
		dfs(v,u);
		for(int j=1;j<=k;++j)
			f[u][j]+=f[v][j-1];
	}
	ans+=f[u][k];
	reg int res=0;
	for(int i=hd[u];~i;i=E[i].nxt)
	{
		reg int v=E[i].to;
		if(v==fa)
			continue;
		for(int j=1;j<k;++j)
			res+=(f[v][j-1]*(f[u][k-j]-f[v][k-j-1]));
	}
	ans+=res>>1;
	return;
}
signed main(void)
{
	memset(hd,-1,sizeof hd);
	reg int u,v;
	rd(n);rd(k);
	for(int i=1;i<n;++i)
	{
		rd(u);rd(v);
		adde(u,v);
		adde(v,u);
	}
	dfs(1,0);
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：yijan (赞：10)

 为啥又在Itst发题解的地方发题解啊pwq  
 而且又是他点分治窝dp
 
 点分太难了不会啊～
 
 就是统计树上长度为k的路径树。。
 
 确实是点分治裸题（然而我不会（（
 
 考虑dp
 
 $dp[u][k]$ 表示当前在u这个点走k的长度可以达到的点的个数。。
 
 直接考虑转移，由于可以向上走所以显得不方便。。
 
 我们可以考虑先用$dp[u][k]$来跑dfs跑出向下走k后的点的位置的个数。。  
 然后自底向上更新 更新出 结果。。
 
 具体更新方法，对于当前点i，其向上走d然后再从向上走d后的位置向下走(k-d)就好了，但是注意向下走k-d不能走上去的时候统计过了的。。直接减去就行了啊QAQ 然后我对于 向上走了k次的时候特判了一下但是貌似不加这个也可以过的pwq
 
 ACCODE
 ```cpp
 /*Heroes Never Die!*/
#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
using namespace std;
typedef long long ll;
#define MAXN 50006
#define MAXK 506
ll dp[MAXN][MAXK];
struct edge{
    ll u;edge* next;
    edge(ll u=0,edge*next=NULL):u(u),next(next){}
    void insert(ll u){
        if(this->next == NULL) this->next = new edge(u,NULL);
        else this->next = new edge(u,this->next);
    }
}e[MAXN];
ll yn,yk;
ll pre[MAXN];
void dfs(ll u,ll fa){
    dp[u][0] = 1;
    for(edge* n=e[u].next;n!=NULL;n=n->next){
        ll v = n->u;
        if(v == fa) continue;
        pre[v] = u;
        dfs(v,u);
        for(ll k=1;k<=yk;++k)
            dp[u][k] += dp[v][k-1];
    }
}
ll res;
int main(){
    cin >> yn >> yk;
    for(ll i=0;i<yn-1;++i){
        static ll u,v;scanf("%I64d%I64d",&u,&v);
        e[u].insert(v),e[v].insert(u);
    }
    dfs(1,1);
    for(ll i=1;i<=yn;++i){
        ll cur = i,las = i;
        for(ll d = 1;d <= yk;++d){
            cur = pre[cur];
            if(!cur) break;
            dp[i][yk] += dp[cur][yk - d] - (yk==d?0:dp[las][yk-d-1]);
            las = cur;
        }
        res += dp[i][yk];
    }
    cout << res/2;
}
 ```

---

## 作者：jiazhaopeng (赞：8)

# 题意简述

给一个 $n$ 个点的树（边权都为 $1$），求树上长度恰好为 $k$ 的路径条数。

数据规模：$1 <= n <= 50000$,$1 <= k <= 500$。

# 思路

这里运用点分治解决此问题。

点分治可以解决一些有关树上路径的问题。点分治其实还可以搞有边权的问题，用到这道题有点大材小用了，但也可以用来练手。

如果不会点分治可以做一做这道题：[P3806 【模板】点分治1](https://www.luogu.com.cn/problem/P3806)

主要思想就是用容斥，先算出经过某点的所有路径（找两个点到该点的距离直接加），然后递归到子树时减去多余的贡献。这里就不多说了。

## 具体实现及优化

基本上套用模板，把 $dis$ 数组（存 到 $root$ 节点的距离 的数组）搞出来后把 $dis$ 存到桶里，然后就很好做了。

由于 $k$ 很小，所以这样做会快很多。

还有个小小的优化：找 $dis$ 时如果当前的 $dis$ 已经超过 $k$，那么就直接返回即可，因为再向下递归已经不会对答案产生贡献了。

更具体的可以看代码。

$Code:$
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <string>
#define N 50010
#define NN 100010
typedef long long ll;
template<typename T> inline void read(T &x) {
	x = 0; char c = getchar(); bool flag = false;
	while (!isdigit(c)) {if (c == '-') flag = true; c = getchar(); }
	while (isdigit(c)) {x = (x << 1) + (x << 3) + (c ^ 48); c = getchar(); }
	if (flag)	x = -x;
}
using namespace std;
int n, k;
ll ans;
struct edge{
	int nxt;
	int to;
}e[NN];
int head[N], ecnt;
inline void addedge(int from, int to) {
	e[++ecnt] = (edge){head[from], to};
	head[from] = ecnt;
}
int root, h[N], Siz, siz[N];
//这里的Siz指的是当前范围内子树的大小，h[i]指i点的最大子树大小，找重心时用 
bool vis[N];
void find_root(int cur, int faa) {//找重心 
	int to;
	siz[cur] = 1, h[cur] = 0;
	for (register int i = head[cur]; i; i = e[i].nxt) {
		to = e[i].to;
		if (to == faa || vis[to])	continue;
		find_root(to, cur);
		siz[cur] += siz[to];
		h[cur] = max(h[cur], siz[to]);
	}
	h[cur] = max(h[cur], Siz - siz[cur]);
	if (h[cur] < h[root])	root = cur;
}
ll known_dis[510];//桶：known_dis[i]为距离为i的路径条数 
int dis[N];
void get_dis(int cur, int faa) {//递归找出dis数组 
	int to;
	if (dis[cur] > k)	return ;
	//一个小小的优化：如果dis>k，那么这以后更新的dis都对答案没有贡献。 
	known_dis[dis[cur]]++;
	for (register int i = head[cur]; i; i = e[i].nxt) {
		to = e[i].to;
		if (to == faa || vis[to])	continue;
		dis[to] = dis[cur] + 1;
		get_dis(to, cur);
	}
}
inline void sol(int cur, int len, int flag) {//找出dis并统计答案 
	memset(known_dis, 0, sizeof(known_dis));
	dis[cur] = len;
	get_dis(cur, 0);
	ll res = 0;
	int tmp;
	for (register int i = 0; i <= k; ++i) {
		tmp = k - i;
		if (tmp <= i)	break;//防止算重 
		res += known_dis[i] * known_dis[tmp];
	}
	if (!(k & 1)) {//k为偶数时，k/2将统计不到，所以加了个特判 
		tmp = k >> 1;
		res += (known_dis[tmp] * (known_dis[tmp] - 1)) >> 1;
	}
	ans += res * flag;
}
void work(int cur) {
	vis[cur] = true;
	sol(cur, 0, 1);
	int to;
	for (register int i = head[cur]; i; i = e[i].nxt) {
		to = e[i].to;
		if (vis[to])	continue;
		sol(to, 1, -1);
		root = 0, h[root] = n, Siz = siz[to];
		find_root(to, cur);
		work(root);
	}
}
int main() {
	read(n); read(k);
	register int aa, bb;
	for (register int i = 1; i < n; ++i) {
		read(aa); read(bb);
		addedge(aa, bb);
		addedge(bb, aa);
	}
	root = 0; h[root] = n, Siz = n;
	find_root(1, 0);
	work(root);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：da32s1da (赞：4)

在统计答案的时候，我和各位大佬的方法可能略有不同。

我们先统计**小于等于k**的数量，再减去**小于k**的数量。

于是类似[P4178](https://www.luogu.org/problemnew/show/P4178)即可。

```
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=5e4+50;
typedef long long LL;
int to[N<<1],las[N<<1],fir[N],ds[N<<1],cnt;
inline void add_edge(int u,int v,int a){
	to[++cnt]=v;las[cnt]=fir[u];fir[u]=cnt;ds[cnt]=a;
	to[++cnt]=u;las[cnt]=fir[v];fir[v]=cnt;ds[cnt]=a;
}
inline int max(int u,int v){return u>v?u:v;}
inline int min(int u,int v){return u<v?u:v;}
int n,k,x,y;
int f[N],dep[N],siz[N],vis[N],sth[N];
int Cnt,rot,sum;
LL ans;
void grot(int u,int v){
	siz[u]=1;f[u]=0;
	for(int i=fir[u];i;i=las[i])
	if(to[i]!=v&&!vis[to[i]]){
		grot(to[i],u);
		siz[u]+=siz[to[i]];
		f[u]=max(f[u],siz[to[i]]);
	}
	f[u]=max(f[u],sum-siz[u]);
	if(f[u]<f[rot])rot=u;
}
void gsth(int u,int v){
	sth[++Cnt]=dep[u];
	for(int i=fir[u];i;i=las[i])
	if(to[i]!=v&&!vis[to[i]]){
		dep[to[i]]=dep[u]+ds[i];
		gsth(to[i],u);
	}
}
int calc(int u,int dis){
	dep[u]=dis;Cnt=0;
	gsth(u,0);
	sort(sth+1,sth+Cnt+1);
	
	int l=1,r=Cnt,res=0;
	while(l<r)
	if(sth[l]+sth[r]<=k)res+=r-l,l++;
	else r--;
    //加上 长度 小于等于k 的
	
	l=1,r=Cnt;
	while(l<r)
	if(sth[l]+sth[r]<k)res-=r-l,l++;
	else r--;
    //减去 长度 小于k 的
	
	return res;
}
void solve(int u){
	ans+=calc(u,0);vis[u]=1;
	for(int i=fir[u];i;i=las[i])
	if(!vis[to[i]]){
		ans-=calc(to[i],ds[i]);
		rot=0;sum=siz[to[i]];
		grot(to[i],0);
		solve(rot);
	}
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		add_edge(x,y,1);
	}
	f[0]=sum=n;
	grot(1,0);
	solve(rot);
	printf("%I64d\n",ans);
}
```

---

## 作者：Graphcity (赞：2)

这道题可以使用**点分治**的方法来做。

不会点分治的可以来看看这个博客：[there](https://www.luogu.com.cn/blog/148913/qian-tan-dian-fen-zhi)

我们可以这样做：将标记距离的数组（这里定义的是 alive 数组）改为 int 类型，把它重新定义为**之前子树到根距离的个数**，新增一个 Right 变量表示正确答案个数，我们就可以这样子做了：

```cpp
		for(register int j=1;j<=nowdis;++j)
			if(q>=now[j])
				Right+=alive[q-now[j]];
```
统一处理距离的时候，只要把模板题里面的 true, false 改为 ++ 和 - - 操作即可。

完整代码如下：

```cpp
#include<bits/stdc++.h>
#define Maxn int(5e4)
#define Maxk int(5e4)
using namespace std;

//===============邻接表=================

struct Node
{
	int to,nxt,w;
} Edge[(Maxn<<1)+5];
int tot,Head[Maxn+5];

inline void Addedge(int u,int v,int w)//加边操作 
{
	Edge[++tot].to=v;
	Edge[tot].nxt=Head[u];
	Edge[tot].w=w;
	Head[u]=tot;
}

//===========找重心 & 更新距离==========

int n,q,root;
int siz[Maxn+5],maxs[Maxn+5];//siz:子树大小 maxs:最大儿子的大小
int vis[Maxn+5];//vis:代表是否删去 
int sum;//sum:记录当前子树大小 

void getroot(int x,int f)//找重心 
{
	siz[x]=1;
	maxs[x]=0;
	for(register int i=Head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].to;
		if(vis[v] || v==f) continue;
		getroot(v,x);
		siz[x]+=siz[v];
		maxs[x]=max(maxs[x],siz[v]);
	}
	maxs[x]=max(maxs[x],sum-siz[x]);
	root=maxs[x]<maxs[root]?x:root;
}

int dis[Maxn+5],now[Maxn+5],nowdis;
//dis:各结点到根结点的距离 now:存放这些距离 nowdis:计数器 

void getdis(int x,int f)
{
	now[++nowdis]=dis[x];
	for(register int i=Head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].to;
		if(vis[v] || v==f) continue;
		dis[v]=dis[x]+Edge[i].w;
		getdis(v,x);
	}
} 

//================点分治==================

int Right;
int alive[Maxk+5];//alive:表示之前子树距离的个数 
stack<int> s;//使用栈统一处理 

void count(int x)//计算距离 
{
	for(register int i=Head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].to;
		if(vis[v]) continue;
		nowdis=0;
		dis[v]=Edge[i].w;
		getdis(v,x);
		
		for(register int j=1;j<=nowdis;++j)
			if(q>=now[j])
				Right+=alive[q-now[j]];
					
		for(register int j=1;j<=nowdis;++j)//存放距离 
		{
			s.push(now[j]);
			alive[now[j]]++;
		}
	}
	while(!s.empty())//清空 
	{
		alive[s.top()]--;
		s.pop();
	}
}

void devide(int x)//点分治
{
	vis[x]=true;
	alive[0]=true;
	count(x);
	for(register int i=Head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].to;
		if(vis[v]) continue;
		root=0;
		maxs[0]=sum=siz[v];
		getroot(v,0);
		getroot(root,0);
		devide(root);
	}
} 

int main()
{
	scanf("%d%d",&n,&q);
	for(register int i=1;i<n;++i)//连边 
	{
		int a,b;
		scanf("%d%d",&a,&b);
		Addedge(a,b,1);
		Addedge(b,a,1);
	}

	maxs[0]=sum=n;
	getroot(1,0);
	getroot(root,0);//找重心并更新子树大小 
	devide(root);
	
	printf("%d",Right);
    return 0;
}

```


---

## 作者：foreverlasting (赞：2)

题解同步发在[博客](https://foreverlasting1202.github.io/)

点分治。

感觉这里的点分治题解好麻烦啊，这不是记个桶再讨论一下$dis$是否相等就没了，为什么要两边扫描啊。

code:
```cpp
//2018.11.30 by ljz
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
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
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
const int N=5e4+10;
namespace MAIN{
    struct E{
        int next,to,val;
        E() {}
        E(res next,res to,res val):next(next),to(to),val(val) {}
    }edge[N<<1];
    int head[N],cnt;
    inline void addedge(const res &u,const res &v,const res &w){
        edge[++cnt]=E(head[u],v,w),head[u]=cnt;
        edge[++cnt]=E(head[v],u,w),head[v]=cnt;
    }
    int n,k;
    int siz[N],rt,w[N];
    bool vis[N];
    void dfs_siz(const res &x,const res &fax,res sum){
        siz[x]=1,w[x]=0;
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(tox==fax||vis[tox])continue;
            dfs_siz(tox,x,sum);
            siz[x]+=siz[tox],w[x]=_max(w[x],siz[tox]);
        }
        w[x]=_max(w[x],sum-siz[x]);
        if(w[x]<w[rt])rt=x;
    }
    int vec[N],tot;
    int pos[N];
    LL ans;
    int dis[N];
    inline void dfs_dis(const res &x,const res &fax){
        vec[++tot]=dis[x],pos[dis[x]]++;
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(tox==fax||vis[tox])continue;
            dis[tox]=dis[x]+edge[i].val;
            dfs_dis(tox,x);
        }
    }
    inline void calc(const res &x,const res &d0,const res &flag){
        tot=0,dis[x]=d0;
        dfs_dis(x,0);
        for(res i=1;i<=tot;i++){
            if(k>=vec[i])ans+=(vec[i]*2!=k)?1LL*flag*pos[vec[i]]*pos[k-vec[i]]:1LL*flag*pos[vec[i]]*(pos[vec[i]]-1)/2;
            pos[vec[i]]=pos[k-vec[i]]=0;
        }
    }
    void solve(const res &x){
        calc(x,0,1),vis[x]=1;
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(vis[tox])continue;
            calc(tox,edge[i].val,-1);
            rt=0,dfs_siz(tox,0,siz[tox]),solve(rt);
        }
    }
    inline void MAIN(){
        memset(head,-1,sizeof(head)),w[0]=inf;
        n=read(),k=read();
        for(res i=1;i<n;i++){
            res u=read(),v=read(),w=1;
            addedge(u,v,w);
        }
        dfs_siz(1,0,n),solve(rt);
        printf("%lld\n",ans);
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```


---

## 作者：Itst (赞：2)

### 比较基础的静态点分治，初学者~~（比如我）~~拿来练手是不错的选择
### 对点分治了解不深的请右转模板，这里主要提及一下在不同子树上的路径的处理方法（这也基本上是静态点分治题目之间的主要不同点了）
### 自己原本写了一个$O(n^2)$的路径处理（因为在很多时候跑不满）结果被一个菊花图卡到TLE qwq所以得使用一个$O(n)$的路径处理方式
### 比较快的$O(n)$路径处理方法是在扫的过程中把同一路径长度路径的数量与子树分布记录下来，在之后的询问过程中就可以直接获得满足条件的路径数量
### 描述比较抽象，代码体现实质qwq（最快1310ms暂时Rk2）
```
#include<bits/stdc++.h>
#define MAXN 50001
using namespace std;
inline int read(){
    int a = 0;
    bool f = 0;
    char c = getchar();
    while(!isdigit(c)){
        if(c == '-')    f = 1;
        c = getchar();
    }
    while(isdigit(c))	a += (a << 3) + a + (c ^ '0') , c = getchar();
    return f ? -a : a;
}
struct Edge{
    int end , upEd;
}Ed[MAXN << 1];
struct node{//记录子树上根到各个点的路径长度与子树分布
    int in , wei;
    bool operator <(node a){return wei < a.wei;}
}Node[MAXN];
int head[MAXN] , size[MAXN] , cnt[MAXN];
int nowSize , N , K , minN , pos , cntEd , cntNode;
long long ans;
bool vis[MAXN];
inline int max(int a , int b){return a > b ? a : b;}

inline void addEd(int a , int b){//加边
    Ed[++cntEd].end = b;
    Ed[cntEd].upEd = head[a];
    head[a] = cntEd;
}

inline void addNode(int a , int b){//加点
    Node[++cntNode].in = a;
    Node[cntNode].wei = b;
}

void getSize(int k){//获得子树大小
    nowSize++;
    vis[k] = 1;
    for(int i = head[k] ; i ; i = Ed[i].upEd)
        if(!vis[Ed[i].end])
            getSize(Ed[i].end);
    vis[k] = 0;
}

void getZX(int k){//得到子树的重心
    int maxSize = 0; 
    size[k] = vis[k] = 1;
    for(int i = head[k] ; i ; i = Ed[i].upEd)
        if(!vis[Ed[i].end]){
            getZX(Ed[i].end);
            maxSize = max(maxSize , size[Ed[i].end]);
            size[k] += size[Ed[i].end];
        }
    if(minN > (maxSize = max(maxSize , nowSize - size[k]))){
        minN = maxSize;
        pos = k;
    }
    vis[k] = 0;
}

void dfs(int k , int in , int len){//获得根到各节点的路径长度
    if(len > K)	return;
    addNode(in , len);
    vis[k] = 1;
    for(int i = head[k] ; i ; i = Ed[i].upEd)
        if(!vis[Ed[i].end])
            dfs(Ed[i].end , in , len + 1);
    vis[k] = 0;
}

void solve(int dir){
    nowSize = cntNode = 0;
    addNode(0 , 0);//根自己也算在计算内容中
    minN = N + 1;
    getSize(dir);
    getZX(dir);
    vis[pos] = 1;//分割子树+避免死循环
    int in = 0;
    for(int i = head[pos] ; i ; i = Ed[i].upEd)
        if(!vis[Ed[i].end])
            dfs(Ed[i].end , ++in , 1);
    sort(Node + 1 , Node + cntNode + 1);//排序方便O(n)计算答案
    int l = 1 , r = cntNode , p = cntNode , count = 0;
    bool f = 0;
    while(l < r){
    	if(l == 1 || Node[l].wei != Node[l - 1].wei){//计算长度为相同值的个数与子树分布
        	while(r > p)
				cnt[Node[r--].in]--;//把上一次的记录清除(不推荐使用memset，会有较多冗余，前面的代码中的vis数组同理)
        	count = 0;
			while(l < r && Node[l].wei + Node[r].wei > K)//缩小r的范围
            	r--;
            if(l >= r)	break;//到达计算边界
        	p = r;
        	while(l < p && Node[l].wei + Node[p].wei == K){//找距离相同的节点
        	    cnt[Node[p].in]++;
        	    count++;
        	    f = 1;
            	p--;
        	}
        }
        ans += count - cnt[Node[l].in];
        if(p == l){//注意这个细节！
			cnt[Node[++p].in]--;
			count--;
		}
        l++;
    }
    for(int i = head[pos] ; i ; i = Ed[i].upEd)//递归调用子树
        if(!vis[Ed[i].end])
            solve(Ed[i].end);
}
int main(){
    N = read();
    K = read();
    for(int i = 1 ; i < N ; i++){
        int a = read() , b = read();
        addEd(a , b);
        addEd(b , a);
    }
    solve(1);
    cout << ans;
    return 0;
}
```
### 题目细节不少一定要多加小心！

---

## 作者：newbiechd (赞：1)

# CF161D Distance in Tree

长链剖分板子题。  

长链剖分那么好写，跑得又快，为什么要写点分治呢？~~完了我现在看一道点分治题就想写长链剖分，虽然只要带边权就咕咕咕了~~  

如果还不会长链剖分请看[我博客](https://www.cnblogs.com/cj-chd/p/10076199.html)。  

没什么好说的，时空复杂度$O(n)$直接洛谷rank1。  

```cpp
#include<cstdio>
#include<cctype>
#define R register
#define I inline
using namespace std;
const int S=50003,N=100003;
char buf[1000000],*p1,*p2;
I char gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,S,stdin),p1==p2)?EOF:*p1++;}
I int rd(){
	R int f=0; R char c=gc();
	while(c<48||c>57) c=gc();
	while(c>47&&c<58) f=f*10+(c^48),c=gc();
	return f;
}
int h[S],s[N],g[N],p[S],q[S],d[S],t[S],*f[S],u[S],c,K,*e=u+1; long long o;
I int max(int x,int y){return x>y?x:y;}
I int min(int x,int y){return x<y?x:y;}
I void add(int x,int y){s[++c]=h[x],h[x]=c,g[c]=y;}
void dfs1(int x,int f){p[x]=f,d[x]=t[x]=d[f]+1;
	for(R int i=h[x],y;i;i=s[i])
		if((y=g[i])^f){dfs1(y,x);
			if(t[y]>t[x]) t[x]=t[y],q[x]=y;
		}
}
void dfs2(int x){f[x][0]=1;
	R int i,j,y,m,n=t[x]-d[x],k;
	if(q[x]) f[q[x]]=f[x]+1,dfs2(q[x]);
	for(i=h[x];i;i=s[i])
		if((y=g[i])^p[x]&&y^q[x]){f[y]=e,m=t[y]-d[y],e+=m+1,dfs2(y);
			for(j=max(K-n,0),k=min(m,K-1);j<=k;++j) o+=f[x][K-j]*f[y][j];
			for(j=0;j<=m;++j) f[x][j+1]+=f[y][j];
		}
	if(n>K) o+=f[x][K+1];
}
int main(){
	R int n=rd(),i,x,y;
	for(K=rd()-1,i=1;i<n;++i) x=rd(),y=rd(),add(x,y),add(y,x);
	dfs1(1,0),f[1]=e,e+=t[1],dfs2(1),printf("%lld",o);
	return 0;
}
```



---

