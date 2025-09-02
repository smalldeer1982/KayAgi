# Kingdom and its Cities

## 题目描述

Meanwhile, the kingdom of K is getting ready for the marriage of the King's daughter. However, in order not to lose face in front of the relatives, the King should first finish reforms in his kingdom. As the King can not wait for his daughter's marriage, reforms must be finished as soon as possible.

The kingdom currently consists of $ n $ cities. Cities are connected by $ n-1 $ bidirectional road, such that one can get from any city to any other city. As the King had to save a lot, there is only one path between any two cities.

What is the point of the reform? The key ministries of the state should be relocated to distinct cities (we call such cities important). However, due to the fact that there is a high risk of an attack by barbarians it must be done carefully. The King has made several plans, each of which is described by a set of important cities, and now wonders what is the best plan.

Barbarians can capture some of the cities that are not important (the important ones will have enough protection for sure), after that the captured city becomes impassable. In particular, an interesting feature of the plan is the minimum number of cities that the barbarians need to capture in order to make all the important cities isolated, that is, from all important cities it would be impossible to reach any other important city.

Help the King to calculate this characteristic for each of his plan.

## 说明/提示

In the first sample, in the first and the third King's plan barbarians can capture the city 3, and that will be enough. In the second and the fourth plans all their attempts will not be effective.

In the second sample the cities to capture are 3 and 5.

## 样例 #1

### 输入

```
4
1 3
2 3
4 3
4
2 1 2
3 2 3 4
3 1 2 4
4 1 2 3 4
```

### 输出

```
1
-1
1
-1
```

## 样例 #2

### 输入

```
7
1 2
2 3
3 4
1 5
5 6
5 7
1
4 2 4 6 7
```

### 输出

```
2
```

# 题解

## 作者：宁_缺 (赞：28)

挺水的貌似这题……但我还是WA了一次……感觉自己快AFO了。

[$\color{black}\text{原题链接}$](https://www.luogu.com.cn/problem/CF613D)

首先这道题肯定是树形DP，先特判一下不行的情况：如果父子两位都关键了直接输-1。

然后我们设g[x]为**以x为根的子树**中有没有关键点与x联通(**如果x为关键点则g[x]为true**），f[x]为以x为根的子树的答案，那么设v为x的儿子节点，首先f[x]=∑f[v]（~~很抱歉我不会用Latex~~），然后判断x：

①如果x为关键点，那么f[x]+=∑g[v]，也就是说，将它和每个没断的关键点子孙全部断掉；

②如果x不是关键点，那么分两种情况：如果它有多个关键点子孙都没断，那就把它自己切掉即可，f[x]++；否则，如果就一个关键点没断就留到它的祖宗那去（也许到时候能和别的一起断掉），g[x]=true，如果一个都没，g[x]=false。

然后我们发现：这答案只会在两个地方改变：一种是在关键点处，另一种是在几个关键点的LCA处，而跟其他的点一毛钱关系都没有啊。再一看数据范围和∑k有关，那就用虚树搞一搞，然后轻松过掉~

题解区有问神人说这题难点就在弄虚树，但本人真觉得这题套上虚树很轻松……一脸尴尬……

WA是因为初始化的一点问题，一个是那个特判发现是-1时没有将vis数组清空，还有一个是没考虑∑g[v]为0的情况(其实就是x为叶子的时候)。

然后就没啥好说的了，顺带一提，本人是用树剖求LCA的，所以如果你用倍增应该代码更短，可能就六七十行。还有就是，我为了省空间(其实完全没必要)将f数组换成了临时变量res，不要误解。

最后附上代码：
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;
const int N=1e6+9,M=2*N;
int n,m,pn,to[M],nt[M],hd[N];
int sz[N],id[N],son[N],fa[N];
int dp[N],q[N],st[N],h,tp[N];
int vn,vhd[N],vto[M],vnt[M],top;
bool vs[N],flg=true,g[N];
bool cmp(int x,int y){
	return id[x]<id[y];
}
void adve(int u,int v){
	vn++,vnt[vn]=vhd[u],
	vhd[u]=vn,vto[vn]=v;
}	
int rd(){
	char c=getchar();int x=0;
	while(c>57||c<48)c=getchar();
	while(c>47&&c<58)
		x+=(x<<3)+x+c-48,c=getchar();
	return x;
}
void make(int x,int dep){
	dp[x]=dep,sz[x]=1;
	for(int i=hd[x],v;i;i=nt[i]){
		if(to[i]==fa[x])continue;
		fa[v=to[i]]=x;
		make(v,dep+1),sz[x]+=sz[v];
		if(sz[v]>sz[son[x]])son[x]=v;
	}
}
void hvd(int x){
	id[x]=++h;
	if(!tp[x])tp[x]=tp[fa[x]];
	if(!son[x])return;
	hvd(son[x]);
	for(int i=hd[x],v;i;i=nt[i]){
		if(id[v=to[i]])continue;
		tp[v]=v,hvd(v);
	}		
}
int lca(int x,int y){
	while(tp[x]!=tp[y])
		if(dp[tp[x]]>dp[tp[y]])
			x=fa[tp[x]];
		else y=fa[tp[y]];
	return dp[x]<dp[y]?x:y;
}
int dfs(int x){
	int nm=0,res=0;
	for(int i=vhd[x];i;i=vnt[i])
		res+=dfs(vto[i]),nm+=g[vto[i]];
	if(vs[x])res+=nm,g[x]=true;
	else if(nm>1)++res,g[x]=false;
	else g[x]=nm?true:false;
	vhd[x]=0,vs[x]=false;
	return res;
}
int main(){
	scanf("%d",&n);
	for(int i=1,u,v;i<n;++i)
		u=rd(),v=rd(),nt[++pn]=hd[u],
		hd[u]=pn,to[pn]=v,to[++pn]=u,
		nt[pn]=hd[v],hd[v]=pn;
	tp[1]=1,make(1,1),hvd(1),m=rd();
	for(int k;m--&&(k=rd());flg=1){
		for(int i=1;i<=k;++i)
			q[i]=rd(),vs[q[i]]=1;
		for(int i=1;i<=k;++i)
			if(vs[fa[q[i]]])flg=0;
		if(!flg){
			for(int i=1;i<=k;++i)vs[q[i]]=0;
			puts("-1");continue;
		}
		sort(q+1,q+k+1,cmp),st[top=1]=q[1];
		for(int i=2,z;i<=k;++i){
			z=lca(st[top],q[i]);
			while(dp[z]<dp[st[top-1]])
				adve(st[top-1],st[top]),top--;
			if(z!=st[top]){
				adve(z,st[top]);
				if(st[top-1]==z)top--;
				else st[top]=z;
			}
			st[++top]=q[i];
		}
		while(--top)adve(st[top],st[top+1]);
		printf("%d\n",dfs(st[1])),vn=0;	
	}	
	return 0;
}
```
_亦悲亦喜，才明白宿命的意义_

---

## 作者：pitiless0514 (赞：18)

## 题目大意
有一颗 $n$ 个节点的树，一些节点设为了重要节点。
重要节点是不会被选中的。重要节点之外的节点就是非重要节点，选到这些节点之后，与之相连的边就会断掉，求能否选择一些节点让重要节点两两不连通。

重要节点会选择 $m$ 次，每次选择 $k$ 个节点。


## 题解
[在博客园获得更加阅读体验](https://www.cnblogs.com/orzpls/p/15170015.html)

首先考虑不行的情况，如果有两个重要节点之间是直接连边的，那么就是不行的，否则都是行的。

考虑怎么转移做这个东西，分类讨论一下。

当 $u$ 为关键节点的时候，将每个没有断开的子孙全部断开就是了。

当 $u$ 不为关键节点时，如果他有多个关键节点都没有断开，那么就将他自己断开就是了。

否则的话，我们将他传到父节点去，让他与其他节点一起断开就是了。

这么做的话每次都要遍历一遍全树，这让我们的复杂度变得不可接受，为 $O(nm)$ 。

考虑到其实对于选择的点不同有些点是可以不用选上的，我们是否可以将这些点给删去？

当然可以。

我们考虑哪些节点是无所谓的，发现每次其实只会更你重要节点的 $\text{LCA}$ 有关，那么你就只需要保留的是这些节点以及它们的 $\text{LCA}$ 就行了。

这么删去无关节点之后形成的树就是虚树。

虚树建立出来之后就会让你的复杂度变小这是显而易见的。


然后我的虚树的建立可能比较不一样，这是从神仙  $\textcolor{black}{\text{p}}\textcolor{red}{\text{\_b\_p\_b}}$ 
在日报里的回答学到的。

>把点按dfn排序，相邻点的lca丢进去，再排序，每个点在虚树上的父亲就是自己和前驱的lca。  

很妙，这个东西的证明就不证明了吧，联合 $dfn$ 序想一下就知道这是正确的。

然后这个东西还很好写，这样做你就可以通过本题目了。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace IO {
int len = 0;
char ibuf[(1 << 20) + 1], *iS, *iT, out[(1 << 25) + 1];
#define gh()                                                                   \
  (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin),         \
   (iS == iT ? EOF : *iS++) : *iS++)
inline int read() {
  char ch = gh();
  int x = 0;
  char t = 0;
  while (ch < '0' || ch > '9')
    t |= ch == '-', ch = gh();
  while (ch >= '0' && ch <= '9')
    x = x * 10 + (ch ^ 48), ch = gh();
  return t ? -x : x;
}
inline void putc(char ch) { out[len++] = ch; }
template <class T> inline void write(T x) {
  if (x < 0)
    putc('-'), x = -x;
  if (x > 9)
    write(x / 10);
  out[len++] = x % 10 + 48;
}
string getstr(void) {
  string s = "";
  char c = gh();
  while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF)
    c = gh();
  while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF))
    s.push_back(c), c = gh();
  return s;
}
void putstr(string str, int begin = 0, int end = -1) {
  if (end == -1)
    end = str.size();
  for (int i = begin; i < end; i++)
    putc(str[i]);
  return;
}
inline void flush() {
  fwrite(out, 1, len, stdout);
  len = 0;
}
} // namespace IO
using IO::flush;
using IO::getstr;
using IO::putc;
using IO::putstr;
using IO::read;
using IO::write;
const int N = 5e5;
int n, m, num, cnt, q, siz[N], dep[N], dfn[N], id[N], ask[N], f[N];
int top[N], son[N], mark[N], tp;
vector<int> ver[N];
int cmp(int a, int b) { return dfn[a] < dfn[b]; }
void dfs1(int x, int fa) {
  dfn[x] = ++cnt;
  id[cnt] = x;
  siz[x] = 1;
  dep[x] = dep[fa] + 1;
  for (int i = 0; i < ver[x].size(); i++) {
    int to = ver[x][i];
    if (to == fa)
      continue;
    f[to] = x;
    dfs1(to, x);
    siz[x] += siz[to];
    if (siz[to] > siz[son[x]])
      son[x] = to;
  }
}
void dfs2(int now, int x) {
  top[now] = x;
  if (son[now])
    dfs2(son[now], x);
  for (int i = 0; i < ver[now].size(); i++) {
    int to = ver[now][i];
    if (to == f[now] || to == son[now])
      continue;
    dfs2(to, to);
  }
}
int LCA(int x, int y) {
  while (top[x] != top[y]) {
    if (dep[top[x]] >= dep[top[y]])
      x = f[top[x]];
    else
      y = f[top[y]];
  }
  return dep[x] < dep[y] ? x : y;
}
int dp[N], dp2[N];
vector<int> p[N];
int getans(int x) {
  int ret = 0;
  for (int i = 0; i < p[x].size(); i++)
    ret += getans(p[x][i]);
  if (mark[x]) {
    for (int i = 0; i < p[x].size(); i++)
      if (mark[p[x][i]])
        ret++;
  } else {
    int bel = 0;
    for (int i = 0; i < p[x].size(); i++)
      if (mark[p[x][i]])
        bel++;
    if (bel > 1)
      ret++;
    else if (bel == 1)
      mark[x] = 1;
  }
  return ret;
}
signed main() {
  n = read();
  for (int i = 1; i < n; i++) {
    int u = read(), v = read();
    ver[u].push_back(v);
    ver[v].push_back(u);
  }
  dfs1(1, 0);
  dfs2(1, 1);
  q = read();
  while (q--) {
    m = read();
    for (int i = 1; i <= m; i++)
      ask[i] = read(), mark[ask[i]] = 1;
    int fl = 0;
    for (int i = 1; i <= m; i++)
      if (mark[f[ask[i]]]) {
        fl = 1;
        break;
      }
    if (fl) {
      for (int i = 1; i <= m; i++)
        mark[ask[i]] = 0;
      write(-1);
      putc('\n');
      continue;
    }
    num = m;
    sort(ask + 1, ask + num + 1, cmp);
    for (int i = 2; i <= m; i++) {
      int lca = LCA(ask[i], ask[i - 1]);
      if (lca != ask[i] && lca != ask[i - 1])
        ask[++num] = lca;
    }
    sort(ask + 1, ask + num + 1);
    tp = num;
    num = unique(ask + 1, ask + num + 1) - (ask + 1);
    sort(ask + 1, ask + num + 1, cmp);
    for (int i = 2; i <= num; i++) {
      int lca = LCA(ask[i], ask[i - 1]);
      p[lca].push_back(ask[i]);
    }
    write(getans(ask[1]));
    putc('\n');
    for (int i = 1; i <= num; i++)
      mark[ask[i]] = 0;
    for (int i = 1; i <= num; i++)
      p[ask[i]].clear();
  }
  flush();
  return 0;
}

```


---

## 作者：_ctz (赞：14)

[安利$blog$](https://ctz45562.github.io/2019/08/04/洛谷-CF613D-Kingdom-and-its-Cities)

[传送门](https://www.luogu.org/problem/CF613D)

一个思路清奇代码复杂常数大看起来很假的$DP$做法。

建出虚树，设$f(i,0)$为使点$i$的子树内的关键点互不联通，且存在关键点与点$i$联通的最小代价；$f(i,1)$为使点$i$的子树内的关键点互不联通，且不存在关键点与点$i$联通的最小代价。

**若$i$为关键点：**

$f(i,1)$的情况不可能成立（关键点$i$和$i$联通），$f(i,1)=inf$。

判断一下是否有$i$的儿子为关键点且与$i$在原树上有边，存在则无解。

对于$f(i,0)$，处于情况$0$的儿子为满足**关键点互不联通**，需断掉路径上的某个点，处于情况$1$的儿子不用管，$f(i,0)=\sum\limits_{j\in son(i)}\min\{f(j,1),f(j,0)+1\}$

**若$i$不为关键点：**

若$i$有不少于$2$个点为关键点，不可能存在情况$0$，此时$f(i,0)=inf$。

否则其儿子里需有且只有处于情况$0$，即$f(i,0)=\sum\limits_{j\in son(i)}f(j,1)+\min\limits_{j\in son(i)}\{f(j,0)-f(j,1)\}$

对于$f(i,1)$，要么断开点$i$，儿子随便选；要么儿子都处于情况$1$。即$f(i,1)=\min\{\left(\sum\limits_{j\in son(i)}\min\{f(j,0),f(j,1)\}\right)+1,\sum\limits_{j\in son(i)}f(j,1)\}$

 

最后答案为$\min\{f(1,0),f(1,1)\}$。

代码：

``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>

#define maxn 100005
#define inf 0x3f3f3f3f

using namespace std;

inline int read(){
	int x=0,y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}
namespace origin{
	int seg[maxn],top[maxn],son[maxn],fa[maxn],deep[maxn],siz[maxn],h[maxn],all,num;
	struct edge{
		int pre,to;
	}e[maxn<<1];
	inline void add(int from,int to){
		e[++num].pre=h[from],h[from]=num,e[num].to=to;
	}
	void dfs1(int node=1){
		siz[node]=1;
		int x;
		for(register int i=h[node];i;i=e[i].pre){
			x=e[i].to;
			if(!siz[x]){
				fa[x]=node,deep[x]=deep[node]+1,dfs1(x),siz[node]+=siz[x];
				if(siz[x]>siz[son[node]])son[node]=x;
			}
		}
	}
	void dfs2(int node=1){
		seg[node]=++all;
		if(son[node]){
			top[son[node]]=top[node],dfs2(son[node]);
			int x;
			for(register int i=h[node];i;i=e[i].pre){
				x=e[i].to;
				if(!seg[x])top[x]=x,dfs2(x);
			}
		}
	}
	int lca(int x,int y){
		while(top[x]!=top[y])deep[top[x]]<deep[top[y]]?y=fa[top[y]]:x=fa[top[x]];
		return deep[x]<deep[y]?x:y;
	}
}
namespace virt{
	int h[maxn],f[maxn][2],num,n;
	bool vis[maxn],flag;
	vector<int>p;
	struct edge{
		int pre,to;
		bool l;
	}e[maxn<<1];
	inline void add(int from,int to){
		bool l=(origin::fa[from]==to)||(origin::fa[to]==from);
		e[++num].pre=h[from],h[from]=num,e[num].to=to,e[num].l=l;
		e[++num].pre=h[to],h[to]=num,e[num].to=from,e[num].l=l;
	}	
	inline bool cmp(int x,int y){return origin::seg[x]<origin::seg[y];}
	struct Monostack{
		int sta[maxn],top;
		void push(int x){sta[++top]=x;}
		void clear(){
			for(register int i=2;i<=top;++i)add(sta[i],sta[i-1]);
			top=0;
		}
		void check(int x){
			if(x==1)return;
			int l=origin::lca(x,sta[top]);
			h[x]=0;
			if(l!=sta[top]){
				while(origin::seg[l]<origin::seg[sta[top-1]])add(sta[top],sta[top-1]),--top;
				--top;
				if(l!=sta[top])h[l]=0,add(sta[top+1],l),push(l);
				else add(sta[top+1],l);
			}
			push(x);
		}
	}s;
	void dfs(int node=1,int fa=0){
		f[node][0]=(vis[node]^1)*n,f[node][1]=vis[node]*n;
		int x,siz=0,rec=0,ma=0;
		for(register int i=h[node];i;i=e[i].pre){
			x=e[i].to;
			if(x==fa)continue;
			siz+=vis[x],dfs(x,node);
			if(vis[node]){
				if(vis[x]&&e[i].l)flag=1;	
				f[node][0]+=min(f[x][1],f[x][0]+1);
			}
			else {
				ma=max(ma,f[x][1]-f[x][0]);
				rec+=min(f[x][0],f[x][1]);
				f[node][1]+=f[x][1];
			}
		}
		if(!vis[node]){
			if(siz<=1)f[node][0]=f[node][1]-ma;
			f[node][1]=min(f[node][1],rec+1);
		}
	}
	void build(){
		h[1]=0,s.push(1);
		for(vector<int>::iterator iter=p.begin();iter!=p.end();++iter)s.check(*iter);
		s.clear();
	}
	void solve(){
		p.clear(),flag=0,n=read(),num=0;
		int x;
		for(register int i=1;i<=n;++i)p.push_back(x=read()),vis[x]=1;
		sort(p.begin(),p.end(),cmp);
		build(),dfs();
		printf("%d\n",flag?-1:min(f[1][0],f[1][1]));
		for(vector<int>::iterator iter=p.begin();iter!=p.end();++iter)vis[*iter]=0;
	}
}
int main(){
	using namespace origin;
	int n=read(),x,y;
	for(register int i=1;i<n;++i)x=read(),y=read(),add(x,y),add(y,x);
	dfs1(),dfs2(),n=read();
	while(n--)virt::solve();
}
```



---

## 作者：resftlmuttmotw (赞：8)

#### $Firstly$,$DP$的好助手

适用前提

有些问题 $n$过大

导致$m$次询问 $n*m$太大

且每次DP的关键点是确定的

这时我们需要**虚树**

每一次树上$DP$

我们都构建虚树然后在树上$DP$  

自然虚树上只包含 关键点 和关键点的$LCA$

直接枚举$LCA$ 时间复杂度是不降反升的

#### $Secondly$,实现

所以 如何保证复杂度 构建出虚树 就是虚树的核心了

大概方法是 

将关键点按前序排序

然后最开始用栈维护一条链

若 此时的 $u$与栈顶元素的$LCA$不在链内

**则 $u$与栈顶元素是$LCA$的两个不同子树的节点**

(只要这句话懂了 就写得出虚树了)

明显 后期栈维护的不再只是一条链

这里用数组模拟栈

具体操作 看代码

```cpp
inline void BuildTree(int m)
{
	top = 1,st[1] = 1,G[1].clear();
	for(reg i = 1;i <= m;i++)
	{
		if(poi[i] == 1) continue;
		int lc = lca(poi[i],st[top]);
		if(lc != st[top])
		{
			while(dfn[st[top - 1]] > dfn[lc]) add(st[top - 1],st[top]),top--;
			if(lc != st[top - 1]) G[lc].clear(),add(lc,st[top]),st[top] = lc;
			else add(lc,st[top--]);
		}
		G[poi[i]].clear(),st[++top] = poi[i];
	}
	for(reg i = 1;i < top;i++) add(st[i],st[i + 1]);
}
```
#### $Finally$,例题

[Kingdom and its Cities](https://www.luogu.org/problem/CF613D)

```cpp
#include <map>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define reg register int
#define isdigit(x) ('0' <= (x)&&(x) <= '9')
template<typename T>
inline T Read(T Type)
{
	T x = 0,f = 1;
	char a = getchar();
	while(!isdigit(a)) {if(a == '-') f = -1;a = getchar();}
	while(isdigit(a)) {x = (x << 1) + (x << 3) + (a ^ '0');a = getchar();}
	return x * f;
}
const int MAXN = 100010;
vector<int> G[MAXN];
int dp[MAXN],size[MAXN];
int dfn[MAXN],dep[MAXN],fa[MAXN][20],poi[MAXN],st[MAXN],top,cnt;
bool vis[MAXN];
inline void add(int u,int v) {G[u].push_back(v);G[v].push_back(u);}
inline void dfs(int x,int f)
{
	dfn[x] = ++cnt;
	for(reg i = 0;i < G[x].size();i++)
	{
		int v = G[x][i];
		if(v == f) continue;
		dep[v] = dep[x] + 1,fa[v][0] = x;
		dfs(v,x);
	}
}
inline void adjust(int &u,int val)
{
	for(reg i = 18;i >= 0;i--)
		if(dep[fa[u][i]] >= val)
			u = fa[u][i];
}
inline int lca(int u,int v)
{
	if(dep[u] > dep[v]) adjust(u,dep[v]);
	if(dep[v] > dep[u]) adjust(v,dep[u]);
	if(u == v) return v;
	for(reg i = 18;i >= 0;i--)
		if(fa[u][i] != fa[v][i])
			u = fa[u][i],v = fa[v][i];
	return fa[u][0];
}
bool cmp(int a,int b) {return dfn[a] < dfn[b];}
inline void BuildTree(int m)
{
	top = 1,st[1] = 1,G[1].clear();
	for(reg i = 1;i <= m;i++)
	{
		if(poi[i] == 1) continue;
		int lc = lca(poi[i],st[top]);
		if(lc != st[top])
		{
			while(dfn[st[top - 1]] > dfn[lc]) add(st[top - 1],st[top]),top--;
			if(lc != st[top - 1]) G[lc].clear(),add(lc,st[top]),st[top] = lc;
			else add(lc,st[top--]);
		}
		G[poi[i]].clear(),st[++top] = poi[i];
	}
	for(reg i = 1;i < top;i++) add(st[i],st[i + 1]);
}
inline void dfs2(int x,int f)
{
	dp[x] = size[x] = 0;
	for(reg i = 0;i < G[x].size();i++)
	{
		int v = G[x][i];
		if(v == f) continue;
		dfs2(v,x);
		dp[x] += dp[v],size[x] += size[v]; 
	}
	if(vis[x]) dp[x] += size[x],size[x] = 1;
	else if(size[x] > 1) dp[x]++,size[x] = 0;
}
int main()
{
	int n = Read(1);
	for(reg i = 1;i < n;i++)
	{
		int u = Read(1),v = Read(1);
		add(u,v);
	}
	dep[1] = 1,dfs(1,0);
	for(reg i = 1;i <= 18;i++)
		for(reg j = 1;j <= n;j++)
			fa[j][i] = fa[fa[j][i - 1]][i - 1];
	int T = Read(1);
	while(T--)
	{
		memset(vis,0,sizeof(vis));
		int m = Read(1);
		for(reg i = 1;i <= m;i++)
		{
			poi[i] = Read(1);
			vis[poi[i]] = 1;
		}
		bool able = 0;
		for(reg i = 1;i <= m;i++)
			if(vis[fa[poi[i]][0]]&&poi[i] != 1)
			{
				printf("-1\n");
				able = 1;
				break;
			}
		if(able) continue;
		sort(poi + 1,poi + 1 + m,cmp);
		BuildTree(m);
		dfs2(1,0);
		printf("%d\n",dp[1]); 
	}
    return 0;
}
```

---

## 作者：Kelin (赞：7)

题意:标记一些点,问使得所有标记点不连通最少要去掉多少点

首先如果一个点的父亲被标记了那么就可以直接返回$-1$了

考虑建出虚树然后树形$DP$

①:如果一个点被标记了,那么就要把他所有子树里有标记点的儿子都去掉

②:如果一个点没有被标记,但是这个点有两颗以上的子树里有标记点

那么这个点就要去掉,然后这棵子树就没有可标记点了

③:如果一个点子树里只有一个/没有标记点那么就标记点的贡献挪到这个点上面来

稍微$yy$一下就发现这道题难度真的就只在于建虚树

~~不然的话这题就是普及-了~~

```
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?-1:*A++;}
template<class T>inline void sd(T&x){
    char c;T y=1;while(c=gc(),(c<48||57<c)&&c!=-1)if(c==45)y=-1;x=c-48;
    while(c=gc(),47<c&&c<58)x=x*10+c-48;x*=y;
}
char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
template<class T>inline void we(T x){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]='\n';
}
const int N=3e5+5,M=19,inf=1e9;
typedef int arr[N];
struct eg{int nx,to;}e[N<<1];
int n,m,k,ce,dft;arr a,b,fi,fa,fg,sz,son,top,dep,dfn,S;
void dfs(int u){
    dep[u]=dep[fa[u]]+(sz[u]=1);dfn[u]=++dft;
    go(u)if(v^fa[u]){
        fa[v]=u,dfs(v),sz[u]+=sz[v];
        if(sz[v]>sz[son[u]])son[u]=v;
    }
}
void dfs(int u,int t){
    top[u]=t;if(son[u])dfs(son[u],t);
    go(u)if(v^fa[u]&&v^son[u])dfs(v,v);
}
inline int lca(int u,int v){
    for(;top[u]^top[v];dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]]);
    return dep[u]<dep[v]?u:v;
}
inline void add(int u,int v){e[++ce]={fi[u],v},fi[u]=ce;}
inline bool cmp(const int&a,const int&b){return dfn[a]<dfn[b];}
int dp(int u){
	int ans=0,sum=0;
	go(u)ans+=dp(v),sum+=b[v];
	if(fg[u])b[u]=1,ans+=sum;
	else if(sum>1)b[u]=0,++ans;
	else b[u]=sum;return fi[u]=0,ans;
}
inline void sol(){
    sd(k);fp(i,1,k)sd(a[i]),fg[a[i]]=1;ce=0;
    fp(i,1,k)if(fg[fa[a[i]]])return we(-1);
    sort(a+1,a+k+1,cmp);static int top=1;S[1]=1;
    fp(i,1,k){
        int x=a[i],p=lca(S[top],x);
        while(dep[p]<dep[S[top]]){
            if(dep[p]>=dep[S[top-1]]){
                add(p,S[top--]);
                if(S[top]^p)S[++top]=p;
                break;
            }add(S[top-1],S[top]),--top;
        }if(S[top]^x)S[++top]=x;
    }while(top>1)add(S[top-1],S[top]),--top;
    we(dp(1));
}
int main(){
    #ifndef ONLINE_JUDGE
        file("s");
    #endif
    sd(n);int u,v;
    fp(i,2,n)sd(u),sd(v),add(u,v),add(v,u);
    dfs(1),dfs(1,1);sd(m);memset(fi,0,sizeof fi);
    while(m--){sol();fp(i,1,k)fg[a[i]]=0;}
return Ot(),0;
}
```

---

## 作者：水库中的水库 (赞：5)

[博客更佳哦](http://ljf-cnyali.cn/2019/08/09/%E8%99%9A%E6%A0%91/)

虚树一般解决如下问题:

在一棵树上给定一个点集$S$，求删除最少的非点集的点使得点集$S$中点两两互不联通(多次询问)

通常我们将点集$S$中的点称为关键点

可以发现，我们所有可以删除的点只跟所有关键点的$LCA$有关，于是就有了虚树这个概念

建树是用一个单调栈来维护的，保证只将所有与关键点及$LCA$的点加入虚树中

这里还有一个技巧，因为我们建新图使用$memset$复杂度会原地爆炸，只需要在遇见需要连边的点的时候将$begin[i]$清零即可

建完树后求解答案可以用贪心的思想:

对于当前点$i$，父亲为$fa$，$size[i]$表示$i$的子树内和$i$联通的关键点数

-   如果$i$和$fa$均为关键点，无解
-   如果$i$为关键点，且$size[i]>1$，说明$i$必须包含在答案内，则$size[i]=1$
-   否则直接从下向上累加即可

```cpp
/***************************************************************
	File name: CF613D.cpp
	Author: ljfcnyali
	Create time: 2019年08月09日 星期五 19时01分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 400010;

int Begin[maxn], Next[maxn], To[maxn], e;
int n, m, q, dis[maxn], anc[maxn][20], dfn[maxn], cnt;
int a[maxn], size[maxn], ans[maxn], Stack[maxn], top;
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    dfn[u] = ++ cnt; 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v][0] = u;
        DFS1(v, u);
    }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int j = 18; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 18; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
    return anc[x][0];
}

inline void Get_Tree()
{
    Stack[top = 1] = 1; Begin[1] = 0;
    REP(i, 1, m)
    {
        if ( a[i] == 1 ) continue ;
        int fa = LCA(Stack[top], a[i]);
        if ( fa != Stack[top] ) 
        {
            while ( dfn[Stack[top - 1]] > dfn[fa] ) 
            {
                add(Stack[top - 1], Stack[top]); -- top;
            }
            if ( dfn[Stack[top - 1]] != dfn[fa] ) { Begin[fa] = 0; add(fa, Stack[top]); Stack[top] = fa; }
            else add(fa, Stack[top --]);
        }
        Begin[a[i]] = 0;
        Stack[++ top] = a[i];
    }
    REP(i, 1, top - 1) add(Stack[i], Stack[i + 1]);
}

inline void DFS2(int u, int fa)
{
    ans[u] = size[u] = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS2(v, u);
        ans[u] += ans[v]; size[u] += size[v];
    }
    if ( vis[u] ) ans[u] += size[u], size[u] = 1;
    else if ( size[u] > 1 ) size[u] = 0, ++ ans[u];
}

inline int cmp(int x, int y) { return dfn[x] < dfn[y]; }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS1(1, 0);
    REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    scanf("%d", &q);
    REP(o, 1, q)
    {
        scanf("%d", &m); 
        REP(i, 1, m) { scanf("%d", &a[i]); vis[a[i]] = true; } 
        REP(i, 1, m) if ( vis[anc[a[i]][0]] ) { puts("-1"); goto finish; }
        sort(a + 1, a + m + 1, cmp);
        Get_Tree();
        DFS2(1, 0);
        printf("%d\n", ans[1]);
finish: ; 
        REP(i, 1, m) vis[a[i]] = false;
    }
    return 0;
}
```



---

## 作者：Umbrella_Leaf (赞：4)

### 题意
> 有一棵 $n$ 个点的树，现在有 $q$ 个询问，每个询问给出 $k$ 个关键节点，查询删除一些点使这些关键点两两不连通时最小的删除点数目。无解输出 `-1`。$1\le n,q\le 10^5,\sum k\le 10^5$ 。

### 分析

首先，如果关键点之间有边相连，那么直接 `-1`。

注意到每个询问的点数之和与 $n$ 同阶，很容易想到虚树——建立一棵新树，里面只有关键点和关键点之间的 $LCA$ 。

那么，如何求一棵树内最小的删除点数目呢？考虑`dfs`。记录 $f_x$ 表示以 $x$ 为根的子树中在以最优方案删除点之后是否有关键点与 $x$ 连通。

首先，让关键点两两不连通，必然要先让每个子树内部不连通。那么答案先加上每个子树内部的答案。

如果当前点 $x$ 就是关键点，那肯定让子树里每个有关键点未与 $x$ 断开的都断开。答案加上子树里 $f$ 的和。并且 $f_x=1$ 。

如果 $x$ 不是关键点：

- 如果 $x$ 的子树里未断开关键点的总数多于 $1$ 个，那就直接把 $x$ 删掉好了。
- 否则，把这一个未断开关键点留着，或许能到 $x$ 的祖先处断开，省一个。同时也要让 $f_x=1$ 。

做一遍这样的贪心就行了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,m;
int head[100005],Next[200005],to[200005],tot;
int flag[100005];
vector<int>edge[100005];
int fa[100005][25],dep[100005],dfn[100005],cnt;
int st[100005],top;
int vis[100005];
vector<int>vec,tr;
bool cmp(int x,int y){
	return dfn[x]<dfn[y];
}
void addedge(int x,int y){
	Next[++tot]=head[x];
	to[tot]=y;
	head[x]=tot;
}
void addedge2(int x,int y){
	edge[x].push_back(y);
}
void dfs(int x,int f){
	dfn[x]=++cnt;
	for(int i=head[x];i;i=Next[i])
		if(to[i]!=f){
			fa[to[i]][0]=x;
			for(int j=1;j<=20;j++)fa[to[i]][j]=fa[fa[to[i]][j-1]][j-1];
			dep[to[i]]=dep[x]+1;
			dfs(to[i],x);
		}
}
int LCA(int x,int y){
	int k=20;
	while(dep[x]!=dep[y]&&k>=0){
		if(dep[x]<dep[y])swap(x,y);
		if(dep[fa[x][k]]>=dep[y])x=fa[x][k];
		k--;
	}
	if(x==y)return x;
	k=20;
	while(fa[x][0]!=fa[y][0]&&k>=0){
		if(fa[x][k]!=fa[y][k])x=fa[x][k],y=fa[y][k];
		k--;
	}
	return fa[x][0];
}
int dfs2(int x){
	int res=0;flag[x]=0;
	int num=0;
	for(auto y:edge[x]){
		res+=dfs2(y);
		num+=flag[y];
	}
	if(vis[x])res+=num,flag[x]=1;
	else{
		if(num>1)res++;
		else if(num==1)flag[x]=1;
	}
	return res;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		addedge(x,y);
		addedge(y,x);
	}
	dep[1]=1;
	dfs(1,0);
	scanf("%d",&m);
	while(m--){
		int k;
		scanf("%d",&k);
		vec.clear();
		tr.clear();
		st[top=1]=1;
		tr.push_back(1);
		for(int i=1;i<=k;i++){
			int x;scanf("%d",&x);
			vec.push_back(x);vis[x]=1;
		}
		int ans=0;
		for(auto x:vec)
			if(vis[fa[x][0]]){
				ans=1;
				break;
			}
		if(ans){
			for(auto x:vec)vis[x]=0;
			puts("-1");
			continue;
		}
		sort(vec.begin(),vec.end(),cmp);
		for(auto x:vec){
			int tp=st[top];
			int lca=LCA(x,tp);
			if(lca==tp){
				if(x>1)st[++top]=x,tr.push_back(x);
			}else{
				int tp2=st[top-1];
				while(dep[lca]<dep[tp2]&&top>=2){
					addedge2(tp2,tp);
					top--;
					tp=st[top],lca=LCA(x,tp),tp2=st[top-1];
				}
				addedge2(lca,tp);
				top--;
				if(lca!=tp2)st[++top]=lca,tr.push_back(lca);
				st[++top]=x,tr.push_back(x);
			}
		}
		while(top>=2){
			int tp=st[top],tp2=st[top-1];
			addedge2(tp2,tp);
			top--;
		}
		printf("%d\n",dfs2(1));
		for(auto x:tr)edge[x].clear();
		for(auto x:vec)vis[x]=0;
	}
	return 0;
}
```

---

## 作者：huangzirui (赞：3)

公式好像挂了。。为更好的阅读体验，请移步[我的博客](https://www.luogu.com.cn/blog/My-luoguBuoke-HZR/solution-cf613d)。

题意：

给定一颗 $n$ 个点的树， $q$ 次询问删除若干个点令给定的 $k_i$ 个点互相不连通，求最少删点数。

$n,q,\sum k \leq 10^5$

---

虚树 $dp$ 入门题。

考虑树形 $dp$ ，设 $dp[x]$ 为以 $x$ 为根时的答案，$g[x]$ 为此时有没有关键点直连到 $x$ 的父亲，$is[x]$ 为这个点是否关键，那么有：

$$
dp[x]=
\begin{cases}
\sum\limits_{y \in \{son[x]\}} (dp[y]),g[x]=\sum g[y] & is[x]=0 , \sum g[y] \leq 1 \\
(\sum\limits_{y \in \{son[x]\}} dp[y])+1,g[x]=0 & is[x]=0 , \\
\sum\limits_{y \in \{son[x]\}} (dp[y]+g[y]),g[x]=1 & is[x]=1
\end{cases}
$$

第一种情况：不是关键点而且子树关键点个数只有 $0/1$ 个，那么不删除这个节点。

第二种情况：不是关键点而且子树关键点个数很多，直接删掉这个点就行了。

第三种情况：是关键点，那么就断开所有有关键点的子树。

注意如果有两个关键点直接相连那么输出 ``-1`` 即可。

算法复杂度为 $O(nq)$

注意到 $\sum k$ 很少，考虑能否设计一个只和 $k$ 有关的算法。

## 虚树

虚树是原树上的某些节点构成的树，并包含指定的若干节点与它们的 $lca$ 。

下图是一个例子：

红点为被选择的点，蓝点为它们的 $lca$

![](https://cdn.luogu.com.cn/upload/image_hosting/4i0gcbxz.png)

具体实现后附，算法复杂度 $O(\text{节点数}\times\text{lca})$

在此题中，由于非红蓝节点的转移都是无效的，可以建立一个以若干个关键点为基础的虚树，然后在虚树上 $dp$ 即可。

此题代码量较大。

---

实现：

对原树取 $dfs$ 序后建立一个栈，依次按 $dfs$ 序加入红节点，加入过程中如果加入点非栈顶子树那么加入它们的 $lca$ 。

```cpp
// h 数组储存红节点
// 首先加入 1 号点方便建树
Sta[top=1]=1;
for(j=1;j<=Cnt;j++){
	if(h[j]==1)continue;
	int l=lca(Sta[top],h[j]);
	while(deep[Sta[top-1]]>deep[l]){
   		// 这里拿栈顶第二个节点比较，方便处理加边
		add2(Sta[top-1],Sta[top]);
		top--;
	}
	if(Sta[top]!=l){
		//注意不要重复
		if(Sta[top-1]==l)add2(Sta[top-1],Sta[top]),top--;
		else add2(l,Sta[top]),Sta[top]=l;
	}
	Sta[++top]=h[j];
}
while(top>1){
	add2(Sta[top-1],Sta[top]);
	top--;
}
```

具体代码如下：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define Mid ((L+R)>>1)
using namespace std;
typedef pair<int,int> pii;
inline int read(){
	char c;int x=0;int b=1;do{c=getchar();if(c==45)b=-1;}while(c>57||c<48);
	do x=x*10+c-48,c=getchar();while(c<=57&&c>=48);x*=b;return x;
}
const int maxn=100010;
int id,i,j,k,n,m;
struct edge{
	int next,to;
}a[maxn*2],e[maxn*2];
int head[maxn],len;
int head2[maxn],len2;
void add(int x,int y){
	a[++len]={head[x],y};
	head[x]=len;
}
void add2(int x,int y){
	//cout<<x<<' '<<y<<endl;
	e[++len2]={head2[x],y};
	head2[x]=len2;
	e[++len2]={head2[y],x};
	head2[y]=len2;
}
int F[maxn][21],deep[maxn],dfn[maxn],cnt;
void dfs(int now,int fa){
	F[now][0]=fa;deep[now]=deep[fa]+1;
	dfn[now]=++cnt;
	for(int i=head[now];i;i=a[i].next){
		int u=a[i].to;
		if(u==fa)continue;
		dfs(u,now);
	}
}
void LCA(){
	for(int j=1;j<=20;j++)
		for(int i=1;i<=n;i++)
			F[i][j]=F[F[i][j-1]][j-1];
}
int lca(int x,int y){
	if(deep[x]<deep[y])swap(x,y);
	for(int j=20;j>=0;j--)
		if(deep[F[x][j]]>=deep[y])
			x=F[x][j];
	if(x==y)return x;
	for(int j=20;j>=0;j--)
		if(F[x][j]!=F[y][j])
			x=F[x][j],y=F[y][j];
	return F[x][0];
}
bool cmp(int x,int y){
	return dfn[x]<dfn[y];
}
int is[maxn],h[maxn],Cnt;
int Sta[maxn],top;
int dp[maxn],g[maxn],can;
void dfs2(int now,int fa){
	//cout<<now<<' '<<fa<<' '<<is[now]<<' '<<id<<endl;
	for(int i=head2[now];i;i=e[i].next){
		int u=e[i].to;
		if(u==fa)continue;
		dfs2(u,now);
	}
	dp[now]=g[now]=0;
	if(is[now]==id){
		for(int i=head2[now];i;i=e[i].next){
			int u=e[i].to;
			if(is[u]==id && abs(deep[u]-deep[now])==1)can=-1;
			if(u==fa)continue;
			dp[now]+=dp[u]+g[u];
		}g[now]=1;
	}else{
		int Sum=0;
		for(int i=head2[now];i;i=e[i].next){
			int u=e[i].to;
			if(u==fa)continue;
			dp[now]+=dp[u];
			if(g[u])++Sum;
		}
		if(Sum<=1)g[now]=Sum;
		else dp[now]++;
	}
	head2[now]=0;
}
int main() {
	freopen("CF613D.in","r",stdin);
	freopen("CF613D.out","w",stdout);
	cin>>n;
	for(i=1;i<n;i++){
		int x,y;
		x=read();y=read();
		add(x,y);add(y,x);
	}
	dfs(1,0);LCA();
	cin>>m;
	for(id=1;id<=m;id++){
		k=read();Cnt=can=0;
		for(j=1;j<=k;j++){
			int x;
			x=read();
			is[x]=id;
			h[++Cnt]=x;
		}
		sort(h+1,h+1+Cnt,cmp);
		Sta[top=1]=1;
		//cout<<"i="<<i<<endl;
		for(j=1;j<=Cnt;j++){
			if(h[j]==1)continue;
			int l=lca(Sta[top],h[j]);
			while(deep[Sta[top-1]]>deep[l]){
				add2(Sta[top-1],Sta[top]);
				top--;
			}
			if(Sta[top]!=l){
				if(Sta[top-1]==l)add2(Sta[top-1],Sta[top]),top--;
				else add2(l,Sta[top]),Sta[top]=l;
			}
			Sta[++top]=h[j];
		}
		while(top>1){
			add2(Sta[top-1],Sta[top]);
			top--;
		}
		dfs2(1,0);
		if(!can)printf("%d\n",dp[1]);
		else puts("-1");
		len2=0;
	}
	//cerr << 1.0*clock()/CLOCKS_PER_SEC << endl;
	return 0;
}
```

---

## 作者：Uniecho1 (赞：2)

嗯...好像还没有人脑栈的？

赶快来水一发。

首先虚树是啥你得知道。

然后这个题的难点其实就是构造虚树...

~~所以其实没什么好讲的~~

具体讲解见代码

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int maxn=2e5+5;
//其实只有tmp需要开二倍 
int N,Q;
int dep[maxn],lg2[maxn],fa[maxn][20];
int indx,ins[maxn],ous[maxn];
int K,tmp[maxn],book[maxn],import[maxn],size[maxn];
vector<int>G[maxn];
void Prepare(int u,int p) {
	ins[u]=++indx;//欧拉序：进栈 
	fa[u][0]=p;
	dep[u]=dep[p]+1;
	for(int k=1; k<=lg2[dep[u]]; k++)
		fa[u][k]=fa[fa[u][k-1]][k-1];//我还是喜欢倍增一点 
	for(int i=0; i<G[u].size(); i++) {
		int v=G[u][i];
		if(v==p)
			continue;
		Prepare(v,u);
	}
	ous[u]=++indx;//欧拉序：出栈 
}
il int LCA(int u,int v) {
	if(dep[u]<dep[v])
		swap(u,v);
	while(dep[u]!=dep[v])
		u=fa[u][lg2[dep[u]-dep[v]]];
	if(u==v)
		return u;
	for(int k=lg2[dep[u]]; k>=0; k--)
		if(fa[u][k]!=fa[v][k])
			u=fa[u][k],v=fa[v][k];
	return fa[u][0];
}
il bool cmp(int a,int b) {//按欧拉序排序 
	int k1=a>0?ins[a]:ous[-a];
	int k2=b>0?ins[b]:ous[-b];
	return k1<k2;
}
int main() {
	//freopen("in.txt","r",stdin);
	ios::sync_with_stdio(false);
	cin>>N;
	lg2[0]=-1;
	for(int i=1; i<=N; i++)
		lg2[i]=lg2[i>>1]+1;
	for(int i=1,u,v; i<N; i++) {
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	Prepare(1,0);//预处理一波 
	cin>>Q;
	while(Q) {
		int flag=0;
		int ans=0;
		stack<int>s;
		cin>>K;
		for(int i=1; i<=K; i++) {
			cin>>tmp[i];
			book[tmp[i]]=Q;//已经放进在人脑栈里了 
			import[tmp[i]]=size[tmp[i]]=1;//指定了这个点 
		}
		sort(tmp+1,tmp+K+1,cmp);
		for(int i=1; i<K; i++) {
			int lca=LCA(tmp[i],tmp[i+1]);//把lca给塞进来 
			if(book[lca]!=Q) {
				book[lca]=Q;
				tmp[++K]=lca;
			}
		}
		int tmpk=K;
		for(int i=1; i<=tmpk; i++)
			tmp[++K]=-tmp[i];//出栈点塞进来 
		if(book[1]!=Q) {//特判root 
			tmp[++K]=1;
			tmp[++K]=-1;
		}
		sort(tmp+1,tmp+K+1,cmp);//欧拉排序（口胡） 
		for(int i=1; i<=K; i++) {
			if(tmp[i]>0)
				s.push(tmp[i]);//模拟深搜不断往下扩展 
			else {
				int cur=s.top();//开始回溯 
				s.pop();
				if(cur!=1) {
					int pa=s.top();
					if(import[pa]&&import[cur]&&dep[cur]==dep[pa]+1)
						flag=1;//判断两个被指定的点连在一起的情况 
					if(import[pa]) {//case1：父亲被指认，那么每有一个被指认的儿子 
						if(size[cur])//答案就需要+1 
							ans++;
						size[cur]=0;
					} else {
						size[pa]+=size[cur];//case2：父亲不被指认 
						size[cur]=0;
						if(tmp[i+1]==-pa)//统计完父亲的最后一个儿子了 
							if(size[pa]>1){//有超过两个儿子被指认 
								ans++;//就把父亲给删了 
								size[pa]=0;//该子树以下都切了，不会产生贡献了 
							}
					}
				}
			}
		}
		for(int i=1;i<=K;i++)
			if(tmp[i]>0)
				import[tmp[i]]=size[tmp[i]]=0;
		if(flag)
			cout<<"-1"<<endl;
		else
			cout<<ans<<endl;
		--Q;
	}
	return 0;
}
```

---

## 作者：lhm_ (赞：1)

考虑树形$DP$，设$num_x$记录的为当$1$为根时，以$x$为子树中重要城市的个数。

那么进行分类讨论：

① 当$num_x≠0$时，则需将其所有满足$num_y≠0$的儿子$y$删去。

② 当$num_x=0$时，若满足$num_y≠0$的儿子$y$个数$cnt=1$，则直接让$num$进行向上传递，若满足$num_y≠0$的儿子$y$个数$cnt>1$，则需删去$x$本身。

不合法的情况特判掉。

考虑到多次询问和树上点集的特性，考虑用虚树来优化$DP$。

多次建虚树时记得清空$num$，但不要用$memset$，无法保证复杂度，应记录虚树上的点，只清零这些点。

其他实现细节就看代码吧。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 200010
using namespace std;
template<typename T> inline void read(T &x)
{
	x=0;char c=getchar();bool flag=false;
	while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	if(flag) x=-x;
}
int n,q,ans,tmp_cnt;
bool flag;
int query[maxn],tmp[maxn],num[maxn];
struct edge
{
    int to,nxt;
}e[maxn];
int head[maxn],edge_cnt;
void add(int from,int to)
{
    e[++edge_cnt]=(edge){to,head[from]};
    head[from]=edge_cnt;
}
int dfn_cnt;
int de[maxn],dfn[maxn],top_fa[maxn],fa[maxn],son[maxn],siz[maxn];
void dfs_son(int x,int fath)
{
    siz[x]=1;
    fa[x]=fath;
    de[x]=de[fath]+1;
    for(int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        if(y==fath) continue;
        dfs_son(y,x);
        siz[x]+=siz[y];
        if(siz[son[x]]<siz[y]) son[x]=y;
    }
}
void dfs_chain(int x,int tp)
{
    dfn[x]=++dfn_cnt,top_fa[x]=tp;
    if(son[x]) dfs_chain(son[x],tp);
    for(int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        if(dfn[y]) continue;
        dfs_chain(y,y);
    }
}
int lca(int x,int y)
{
    while(top_fa[x]!=top_fa[y])
    {
        if(de[top_fa[x]]<de[top_fa[y]]) swap(x,y);
        x=fa[top_fa[x]];
    }
    if(dfn[x]>dfn[y]) swap(x,y);
    return x;
}
bool cmp(const int &a,const int &b)
{
    return dfn[a]<dfn[b];
}
int st[maxn],top;
void insert(int x)
{
    if(x==1) return;
	if(top==1)
    {
        st[++top]=x;
        return;
    }
    int anc=lca(x,st[top]);
    if(anc==st[top])
    {
        st[++top]=x;
        return;
    }
    while(top>1&&dfn[anc]<=dfn[st[top-1]]) add(st[top-1],st[top]),top--,tmp[++tmp_cnt]=st[top];
    if(anc!=st[top]) add(anc,st[top]),st[top]=anc,tmp[++tmp_cnt]=st[top];
    st[++top]=x;
}
void dp(int x)
{
    int cnt=0,sum=0;
    for(int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        dp(y);
        if(num[x]&&num[y]) ans++;
        if(!num[x]&&num[y])
        {
            cnt++;
            sum+=num[y];
        }
    }
    if(!num[x])
    {
        if(cnt==1) num[x]+=sum;
        if(cnt>1) ans++;
    }
    head[x]=0;
}
void clear()
{
    edge_cnt=0;
    memset(head,0,sizeof(head));
}
int main()
{
	read(n);
    for(int i=1;i<n;++i)
    {
        int a,b;
        read(a),read(b);
        add(a,b),add(b,a);
    }
    dfs_son(1,0);
    dfs_chain(1,1);
    clear();
    read(q);
    while(q--)
    {
        int k;
        read(k);
        edge_cnt=tmp_cnt=flag=ans=0;
        for(int i=1;i<=k;++i)
        {
            read(query[i]);
            num[query[i]]++;
        }
        for(int i=1;i<=k;++i)
        {
            if(num[fa[query[i]]])
            {
                puts("-1");
                flag=true;
                break;
            }
        }
        if(flag)
        {
            for(int i=1;i<=k;++i) num[query[i]]=0;
            continue;
        }
        sort(query+1,query+k+1,cmp);
        st[top=1]=1,tmp[tmp_cnt=1]=1;
        for(int i=1;i<=k;++i) insert(query[i]);
        while(top) add(st[top-1],st[top]),top--,tmp[++tmp_cnt]=st[top];
        dp(1);
        for(int i=1;i<=tmp_cnt;++i) num[tmp[i]]=0;
        for(int i=1;i<=k;++i) num[query[i]]=0;
        printf("%d\n",ans);
    }         
	return 0;
}
```


---

## 作者：GavinZheng (赞：1)

一道虚树板子题。

虚树的作用就是：有的时候解决一些树上问题时，整棵树大小很大，但是所需要的“关键点”大小很小。为了节省时间 对有$k$个关键点的虚树进行处理，能使得整棵树的大小变成$2k$。

虚树在这里：[OIWIKI-虚树](https://oi-wiki.org/graph/virtual-tree/#cf613d-kingdom-and-its-cities)有很详细的介绍。

其实就是利用栈维护树上的一条链。然后考虑栈顶节点和下一个关键点的关系，如果$lca$等于栈顶（在同一条链）就直接入栈。否则分类讨论栈中$top-1$的节点$x$和$lca$的关系：

1. $dfs(x)>dfs(lca)$这代表$x$和栈顶节点构成的链在树的“分叉点”下面的情况（$lca$为分叉点）。所以直接加入$x$和栈顶之间的边，然后弹栈顶。注意 这一步显然需要用`while`执行多次。
2. $dfs(x)<dfs(lca)$这代表$x$和栈顶节点构成的链（不包含两端，因为这里$lca\neq x$，前面又判断了$lca\neq stk[top]$）上的一个节点就是$lca$。所以$lca$没入栈，因此添加栈顶和$lca$的边，栈顶出栈，$lca$入栈即可。
3. $dfs(x)=dfs(lca)$这代表$lca=x$。因此加入边$(lca,x)$，然后出栈即可。

这里有个实现的小技巧：在每次入栈一个新的节点时进行临接表初始化即可。

最后不要忘了将栈中剩余的节点代表的链加进去。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<queue>
#define vi vector<int>
#define pb push_back
#define mk make_pair
#define pii pair<int,int>
#define rep(i,a,b) for(int i=(a),i##end=(b);i<=i##end;i++)
#define fi first
#define se second
typedef long long ll;
using namespace std;
const int maxn=100500;
vi side[maxn],vit[maxn],kp;
int dfn[maxn],f[maxn][23],dep[maxn],dfn_cnt,stk[maxn],top;
void dfs(int u,int fa){
    f[u][0]=fa;dep[u]=dep[fa]+1;dfn[u]=++dfn_cnt;
    rep(i,1,22)f[u][i]=f[f[u][i-1]][i-1];
    rep(i,0,(int)side[u].size()-1){
        int v=side[u][i];if(v==fa)continue;
        dfs(v,u);
    }
}
bool iskp[maxn];
bool cmp(int a,int b){return dfn[a]<dfn[b];}
void roll_back(int k){
    rep(i,0,k-1)iskp[kp[i]]=0;
}
void in(int x){
    vit[x].clear();stk[++top]=x;
}   
int k;
int c[maxn];
ll dp(int u,int fa){
    ll tot=0,ans=0;
    rep(i,0,(int)vit[u].size()-1){
        int v=vit[u][i];if(v==fa)continue;
        ans+=dp(v,u);tot+=c[v];
    }
    if(iskp[u]){
        c[u]=1;ans+=tot;        
    }
    else if(tot>1)c[u]=0,ans++;
    else c[u]=tot;
    return ans;
}
int lca(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    for(int i=22;i>=0;i--)if(dep[f[u][i]]>=dep[v])u=f[u][i];
    if(u==v)return u;
    for(int i=22;i>=0;i--)if(f[u][i]!=f[v][i])u=f[u][i],v=f[v][i];
    return f[u][0];
}
int main(){
    int n;scanf("%d",&n);
    rep(i,1,n-1){
        int u,v;scanf("%d%d",&u,&v);side[u].pb(v);side[v].pb(u);
    }
    dfs(1,0);
    int q;scanf("%d",&q);
    while(q--){
        scanf("%d",&k);kp.clear();
        rep(i,1,k){
            int u;scanf("%d",&u);kp.pb(u);iskp[u]=1;
        }
        bool flag=1;
        rep(i,0,k-1){
            if(iskp[f[kp[i]][0]]){
                printf("-1\n");roll_back(k);flag=0;break;
            }
        }
        if(!flag)continue;
        sort(kp.begin(),kp.end(),cmp);
        stk[top=1]=1;vit[1].clear();
        rep(i,0,k-1){
            int x=kp[i];
            if(x==1)continue;
            int l=lca(x,stk[top]);
            if(l==stk[top]){in(x);continue;}
            while(dfn[l]<dfn[stk[top-1]]){vit[stk[top-1]].pb(stk[top]);vit[stk[top]].pb(stk[top-1]);top--;}
            if(dfn[l]>dfn[stk[top-1]]){
                vit[l].clear();vit[l].pb(stk[top]);vit[stk[top]].pb(l);stk[top]=l;
            }
            else {vit[stk[top]].pb(l);vit[l].pb(stk[top]);top--;}
            in(x);
        }
        rep(i,1,top-1){vit[stk[i]].pb(stk[i+1]);vit[stk[i+1]].pb(stk[i]);}
        printf("%lld\n",dp(1,0));
        roll_back(k);
    }
}
```



---

## 作者：ZBHRuaRua (赞：0)

**蒟蒻刚学虚树不久，感觉这道题很水的亚子，就来做一下**

题意：

给定一棵树，每次询问有k个关键节点，问最少选取几个除这k个点外的点能将这些点隔开

$\sum k\leq 100000$ 

看到最后的限制条件就很容易联想到虚树了，首先随便构建一下虚树（这个构建没什么难的吧把询问点和lca一通塞进来就可以了）

然后考虑树形DP：

**不妨设当前节点为x,temp为F[x]，bj数组表示某个点是不是关键点**

1.如果x是关键节点，那么如果他的儿子也是关键节点，temp+=dp（儿子）+1即可，如果他的儿子是非关键节点（也就是一个lca点），那么我们把要考虑的情况扔给这个lca点，在当前层直接temp+=dp（儿子）。

**注意，如果x和他的儿子都是关键节点，要特判在原树中有没有父子关系（具体就是特判一下深度即可），有的话打个标记在这次询问直接输出-1**

2.如果x是非关键节点，也就是x是某个lca，我们考虑他的各个子树，如果有大于一个子树能传递上来关键点，很显然x点必须封堵，那么return temp+1。如果只有一个子树能传递上来关键点，那么lca号点不必封堵，直接将这个关键点信息继续向上传递。如果没有子树能传递上来关键点，就什么也不用管。

**那么如何表示这个传递关键点操作？**

直接开一个数组g，在遍历x号点的儿子时加上这样一句：

```
if(g[e[x][i]]||bj[e[x][i]]) t++; //t表示有几个子树能传递关键点
```

即可判断传递信息的子树个数，然后在t==1时，g[x]设为1即可。

注意要特判当x为非关键节点时，t==1并且在虚树中x的父亲是关键节点时，直接返回temp+1（这就是前文提到的“把要考虑的情况扔给这个lca点”）

这样就做完了，我的写法描述起来可能有点怪异？适当理解，应该有更好理解的描述方法。

然而...

依然还是在Test 11 Wa了5次啊(#`O′)！！

一阵肉眼观察发现原来是因为：

```
for(int i=0;i<e[x].size();i++)
{
	if(g[e[x][i]]||bj[e[x][i]]) t++;
	temp+=dp(e[x][i],x);
}
```
循环里两句话位置反了，导致下一层的g还没初始化为0就已经在这一层用来判断了QAQ

改一下，轻松AC

下面上代码：

```
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<iomanip>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
inline int read()
{
	int res=0,f=1;char c=getchar();
	while(c<'0'||c>'9') 
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		res=res*10+(c-'0');
		c=getchar();
	}
	return res*f;
}
int n,m;
int cnt,tot;
int ver[200050];
int nxt[200050];
int head[100050];
int deep[100050];
int F[100050][21];
int a[100050];
int st[100050];
int dfn[100050];
int tmp;
int root;
bool flag;
bool bj[100050];
vector<int> e[100050];
int g[100050];
inline bool cmp(int x,int y)
{
	return dfn[x]<dfn[y];
}
inline void add(int x,int y)
{
	cnt++;
	ver[cnt]=y;
	nxt[cnt]=head[x];
	head[x]=cnt;
}
inline void dfs(int x,int fa)
{
	dfn[x]=++tot;
	deep[x]=deep[fa]+1;
	F[x][0]=fa;
	for(int i=head[x];i;i=nxt[i])
	{
		if(ver[i]==fa) continue;
		dfs(ver[i],x);
	}
}
inline int lca(int x,int y)
{
	if(deep[x]<deep[y]) swap(x,y);
	for(int i=20;i>=0;i--)
	{
		if(deep[F[x][i]]>=deep[y]) x=F[x][i];
	}
	if(x==y) return x;
	for(int i=20;i>=0;i--)
	{
		if(F[x][i]!=F[y][i]) 
		{
			x=F[x][i];y=F[y][i];
		}
	}
	return F[x][0];
}
inline void insert(int x)
{
	if(!tmp)
	{
		st[++tmp]=x;
		return;
	}
	int f=lca(x,st[tmp]);
	if(f==st[tmp])
	{
		st[++tmp]=x;
		return;
	}
	while(tmp>1&&dfn[st[tmp-1]]>=dfn[f])
	{
		e[st[tmp-1]].push_back(st[tmp]);
		if(!root||deep[st[tmp-1]]<deep[root]) root=st[tmp-1];
		--tmp;
	}
	if(st[tmp]!=f)
	{
		e[f].push_back(st[tmp]);
		if(!root||deep[f]<deep[root]) root=f;
		tmp--;
		st[++tmp]=f;
	}
	st[++tmp]=x;
}
inline int dp(int x,int fa)
{
	g[x]=0;
	int temp=0;
	if(bj[x])
	{
		for(int i=0;i<e[x].size();i++)
		{
			if(bj[e[x][i]])
			{
				if(deep[e[x][i]]==deep[x]+1) flag=0;
				temp+=dp(e[x][i],x)+1;
			}
			else
			{
				temp+=dp(e[x][i],x);
			}
		}
		e[x].clear();
		return temp;
	}
	else
	{
		int t=0;
		for(int i=0;i<e[x].size();i++)
		{
			temp+=dp(e[x][i],x);
			if(g[e[x][i]]||bj[e[x][i]]) t++;
		}
		e[x].clear();
		if(t>1)
		return temp+1;
		else
		{
			if(bj[fa]&&t==1) return temp+1;
			else
			{
				if(t==1)
				g[x]=1;
				return temp;
			}
		}
	}
}
int main()
{
	n=read();
	for(int i=1;i<n;i++)
	{
		int x,y;
		x=read();y=read();
		add(x,y);add(y,x);
	}
	dfs(1,0);
	for(int i=1;i<=20;i++)
	{
		for(int j=1;j<=n;j++)
		{
			F[j][i]=F[F[j][i-1]][i-1];
		}
	}
	m=read();
	while(m--)
	{
		root=0;flag=1;
		int k;k=read();
		for(int i=1;i<=k;i++)
		{
			a[i]=read();
			bj[a[i]]=1;
		}
		sort(a+1,a+k+1,cmp);
		for(int i=1;i<=k;i++) insert(a[i]);
		while(tmp>1)
		{
			e[st[tmp-1]].push_back(st[tmp]);
			if(!root||deep[st[tmp-1]]<deep[root]) root=st[tmp-1];
			tmp--;
		}
		tmp--;
		int rua=dp(root,0);
		if(flag)
		printf("%d\n",rua);
		else printf("-1\n");
		for(int i=1;i<=k;i++) bj[a[i]]=0;
	}
	return 0;
}
```


---

## 作者：zsaskk (赞：0)

~~虚树入门题目~~

数据范围中提到$The$ $sum$ $of$ $all$ $ki's$ $does't$ $exceed$ $100000 $，我们可以考虑使用虚树。

首先[建立虚树](https://zsaskk-rzll.blog.luogu.org/solution-p4103)，然后考虑问题怎么用$dp$解决。

首先，无解的情况很好判断，当$x$与$fa[x]$都成为钦定点，就无法断开，无解。

当确定有解时，考虑$dp$。

当$dp$到$x$，如果$x$是亲定点，对于$x$的一颗子树$y$，如果$y$的顶上有钦定点，那么断开中间的任意一个点，$++ans$。

如果$x$不是钦定点，当且仅当有多个含钦定点子树，$++ans$，并把$x$定义为子树内无钦定点，否则就等到更高层去处理，这样显然是优的。

每次回答一个询问后，应当清空数组。

------------
```
#include<bits/stdc++.h>
using namespace std;
#define reg register
#define chk_digit(c) (c>='0'&&c<='9')
#define maxsize 200010
inline int read() {
	reg int x=0,f=1;reg char c=getchar();
	while(!chk_digit(c)) { if(c=='-') f=-1;c=getchar(); }
	while(chk_digit(c)) x=x*10+c-'0',c=getchar();
	return x*f;
}
int a[maxsize],stop,stac[maxsize],vist,dfn[maxsize],h[maxsize],cnt,top[maxsize],siz[maxsize],son[maxsize],dep[maxsize],fa[maxsize],st[maxsize],n,m,q,ans,ance;
struct node { int y,next; }edg[maxsize<<1];
inline bool cmp(int x,int y) { return dfn[x]<dfn[y]; }
inline void add(int x,int y) { edg[++cnt].next=h[x],edg[cnt].y=y,h[x]=cnt; }
inline void dfs1(int x,int fat){//求重儿子 
	siz[x]=1;
	for(reg int i=h[x];i;i=edg[i].next) {
		int y=edg[i].y;if(y==fat) continue;
		dep[y]=dep[fa[y]=x]+1,dfs1(y,x),siz[x]+=siz[y];
		if(siz[son[x]]<siz[y]) son[x]=y;
	}
}
inline void dfs2(int x) {//划分轻重链 
	dfn[x]=++vist;
	if(!son[x]) return;
	top[son[x]]=top[x],dfs2(son[x]);
	for(reg int i=h[x];i;i=edg[i].next) {
		int y=edg[i].y;if(y==fa[x]||y==son[x]) continue;
		dfs2(top[y]=y);
	}
}
inline int lca(int x,int y) {//树剖lca 
	while(top[x]^top[y]) {
		if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
		else y=fa[top[y]];
	}
	if(dep[x]<dep[y]) return x;return y;
}
inline void ins(int x) {//建立虚树 
	if(!stop) { stac[stop=1]=x;return; }
	int anc=lca(stac[stop],x);
	while(stop&&dep[anc]<dep[stac[stop]]) add(stac[stop-1],stac[stop]),--stop;
	if(!stop||stac[stop]!=anc) stac[++stop]=anc;
	stac[++stop]=x;
}
inline void dfs3(int x) {
	if(siz[x]) {
		for(reg int i=h[x];i;i=edg[i].next) {
			int y=edg[i].y;dfs3(y);
			if(siz[y]) siz[y]=0,++ans;//如果子树中有钦定点，直接断开 （一定合法，因为不合法的已经去除） 
		}
	}
	else {
		for(reg int i=h[x];i;i=edg[i].next) {
			int y=edg[i].y;
			dfs3(y),siz[x]+=siz[y],siz[y]=0;
		}
		if(siz[x]>1) ++ans,siz[x]=0;//即使当前点不是钦定点，如果子树中有多个钦定点，断开 
	}
	h[x]=0;//清空 
}
int main() {
	n=read();
	for(reg int i=1;i<n;++i) {
		int x=read(),y=read();
		add(x,y),add(y,x);
	}
	dfs1(dep[1]=1,0),dfs2(top[1]=1),q=read(),vist=0;;
	memset(h,0,sizeof(h))/*清空原先的边的关系*/,memset(siz,0,sizeof(siz));
	for(reg int i=1;i<=q;++i) {
		int x=1;m=read();
		for(reg int i=1;i<=m;++i) a[i]=read(),siz[a[i]]=1;
		for(reg int i=1;i<=m;++i) if(siz[fa[a[i]]]) { printf("-1\n"),x=0;break; }//判无解 
		if(!x) { while(m) siz[a[m]]=0,--m;continue; }
		ans=0,sort(a+1,a+m+1,cmp);//按dfs序排序 
		if(a[1]!=1) stac[stop=1]=1;
		for(reg int i=1;i<=m;++i) ins(a[i]);
		if(stop) while(--stop) add(stac[stop],stac[stop+1]);
		dfs3(1),siz[1]=vist=0,printf("%d\n",ans);
	} 
}
```


---

