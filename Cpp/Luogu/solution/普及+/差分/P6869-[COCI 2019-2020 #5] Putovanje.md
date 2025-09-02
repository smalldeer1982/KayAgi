# [COCI 2019/2020 #5] Putovanje

## 题目描述

给你一棵有 $n$ 个点的树，节点编号从 $1$ 到 $n$。

你会按编号从小到大顺序访问每个节点。

经过树上的边需要收费。第 $i$ 条边有单程票（只能用一次）价格 $c_{i1}$ 和多程票（可以用无限次）价格 $c_{i2}$。你在访问途中可能会重复走一条边，所以多程票有时更划算。

请你求出从 $1$ 访问到 $n$ 最少需要多少费用。

## 说明/提示

### 样例#1 解释

- $1\to 2$：多程票，费用 $5$。
- $2\to 1\to 3$：$2\to 1$ 使用买过的多程票，无费用；$1\to 3$ 单程票，费用 $2$。
- $3\to 1\to 2\to 4$：$3\to 1$ 单程票，费用 $2$；$1\to 2$ 使用买过的多程票，无费用；$2\to 4$ 单程票，费用 $1$。
- 费用共 $5+2+2+1=10$。

### 数据范围

**本题捆绑测试。**

- 对于 $20 pts$ 的数据，$2\leq n\leq 2000$。

- 对于另外 $25 pts$ 的数据，每个城镇最多与另外两个城镇直接相连。

- 对于所有的数据，$2\leq n\leq 200000$，$1\leq a_i,b_i\leq n$，$1\leq c_{i1}\leq c_{i2}\leq 100000$。

### 说明

**题目译自 [COCI2019-2020](https://hsin.hr/coci/archive/2019_2020/) [CONTEST #5](https://hsin.hr/coci/archive/2019_2020/contest5_tasks.pdf)  _T4 Putovanje_**。

## 样例 #1

### 输入

```
4
1 2 3 5
1 3 2 4
2 4 1 3
```

### 输出

```
10```

## 样例 #2

### 输入

```
4
1 4 5 5
3 4 4 7
2 4 2 6
```

### 输出

```
16```

## 样例 #3

### 输入

```
5
1 2 2 3
1 3 2 3
1 4 2 3
1 5 2 3
```

### 输出

```
11```

# 题解

## 作者：MY（一名蒟蒻） (赞：32)

[原题传送门](https://www.luogu.com.cn/problem/P6869)

前置知识：

1. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
2. [树上差分——P3128 [USACO15DEC]Max Flow P](https://www.luogu.com.cn/problem/P3128)

---
考虑这样一个性质：如果你第一次走过一条边买了多程票，就不会再买这条边的单程票。**反之亦然**。

所以对于每一条边，我们一定只买单程票或多程票。

于是只要求出每条边经过的次数 $k$ ，然后算出你需要花在这条边上的最少花费 $\min(k\times c_{i1},c_{i2})$ 统计进答案。

每条边经过的次数用树上差分搞，由于是边差分，直接在 $val_{\operatorname{lca(u,v)}}$ 上减两次。

### Code
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int N=2e5+10;

int n,fir[N],tot,fa[N][40],dep[N];
long long ans,val[N];
struct node {int to,nex,oned,twod;} e[N << 1];

void add(int u,int v,int xgf,int xrc)
{
	e[++tot].to=v;
	e[tot].oned=xgf;//这是两位同级机房神仙的名字
	e[tot].twod=xrc;
	e[tot].nex=fir[u];
	fir[u]=tot;
	return ;
}
void swap(int &x,int &y) {x^=y^=x^=y; return ;}

void dfs(int x,int dad)//LCA预处理
{
	dep[x]=dep[dad]+1;
	fa[x][0]=dad;
	for(int i=1;(1<<i)<=dep[x];i++)
		fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int i=fir[x];i;i=e[i].nex)
		if(e[i].to^dad) dfs(e[i].to,x);
	return ;
}

int lca(int x,int y)//倍增求LCA
{
	if(dep[x] < dep[y]) swap(x,y);
	for(int i=35;i>=0;i--)
	{
		if(dep[fa[x][i]] >= dep[y]) x=fa[x][i];
		if(x == y) return y;
	}
	for(int i=35;i>=0;i--)
		if(fa[x][i]^fa[y][i]) {x=fa[x][i]; y=fa[y][i];}
	return fa[x][0];
}

void solve(int x)
{
	int u;
	for(int i=fir[x];i;i=e[i].nex)
		if(e[i].to^fa[x][0])
		{
			solve(e[i].to);
			val[x]+=val[e[i].to];//统计经过的次数
		}
		else u=i;
	if(e[u].oned*val[x] < e[u].twod) ans+=e[u].oned*val[x];
	else ans+=e[u].twod;//统计答案
	return ;
}

int main()
{
//	freopen("work.in","r",stdin); freopen("work.out","w",stdout);
	scanf("%d",&n);
	for(int i=1,u,v,c1,c2;i<n;i++)
	{
		scanf("%d%d%d%d",&u,&v,&c1,&c2);
		add(u,v,c1,c2); add(v,u,c1,c2);
	}
	dfs(1,0);
	for(int i=1;i<n;i++)
	{
		val[i]++; val[i+1]++;
		val[lca(i,i+1)]-=2;//树上差分，题目要求编号从小到大访问
	}
	solve(1);
	printf("%lld",ans);
//	fclose(stdin); fclose(stdout);
	return 0;
}
```
感谢阅读！您的点赞和留言是对作者最大的支持！

---

## 作者：_•́へ•́╬_ (赞：18)

### 题意

求按节点编号顺序遍历一棵树的最小费用，边权分成单程票和多程票两种。

### 思路

套路。

既然是在树上行走，那么常规方法就是求 $LCA$ ，再树上差分，得到每一条边经过的次数。

对于某一条边，它的费用就是 $\min(\texttt{经过次数}\times\texttt{单程票费用},\texttt{多程票费用})$。

#### $LCA$ 是什么？树上倍增是什么？

窝喜欢用树上倍增求 $LCA$。

树上倍增就是在树上倍增。记 $jmp[i][j]$ 为从节点 $i$ 向上跳 $2^j$ 步到达的节点。如果跳 $2^j$ 步超过根节点了，那么 $jmp[i][j]=-1$。

$jmp$ 要通过递推得到，$jmp[i][j]=jmp[jmp[i][j-1]][j-1]$。

#### 树上差分是什么？

树上差分就是在树上差分。

如果每个点有一个权值 $a_i$，那么它的差分数组 $d_i=a_i-\sum\limits_{\forall j\texttt{,j是i的孩子}}a_j$。

如果要把 $a_i$ 到 $a_j$ （$i$ 是 $j$ 的祖先节点）加 $x$，那么操作就是 $a_j+=x$，$a_{i\texttt{的父亲节点}}-=x$。

### $code$

```cpp
#include<stdio.h>
#include<vector>
#define N 200000
using namespace std;
inline void read(int&x)
{
	register char c=getchar();for(;c<'0'||'9'<c;c=getchar());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=getchar());
}
/*这里使用0下标
 *e1记录边到达的顶点编号，e2记录边本身的编号
 *fid[i]表示连接i和i的父亲节点的边的编号，特别地fid[0]=-1
 *jmp是树上倍增求LCA的数组
 *dep是节点的深度，也是树上倍增求LCA用的，规定dep[0]=0
 *cf是树上差分的数组
 *cnt[i]表示第i条边一共经过几次
 */
int n,c1[N],c2[N],cnt[N],fid[N],dep[N],cf[N],jmp[N][20];long long ans;vector<int>e1[N],e2[N];
void dfs1(const int&i,const int&f)
{
	jmp[i][0]=f;
	for(register int j=1;j<20;++j)//处理倍增数组
		if(jmp[i][j-1]==-1)jmp[i][j]=-1;//跳2^j-1都不行，跳2^j肯定也不行
		else jmp[i][j]=jmp[jmp[i][j-1]][j-1];//跳2^j的结果就是跳两次2^j-1的结果
	fid[i]=-1;
	for(register int j=0;j<e1[i].size();++j)
		if(e1[i][j]==f)fid[i]=e2[i][j];//记录连接i和i的父亲节点的边的编号
		else dep[e1[i][j]]=dep[i]+1,dfs1(e1[i][j],i);//递归
}
int dfs2(const int&i)
{
	for(register int j=0;j<e1[i].size();++j)if(e1[i][j]!=jmp[i][0])cf[i]+=dfs2(e1[i][j]);//前缀和
	if(fid[i]!=-1)cnt[fid[i]]=cf[i];//记录i到i的父亲节点的边一共经过的次数
	return cf[i];
}
main()
{
	read(n);
	for(register int i=0,u,v;i<n-1;++i)//输入
	{
		read(u);read(v);read(c1[i]);read(c2[i]);--u;--v;
		e1[u].push_back(v);e2[u].push_back(i);
		e1[v].push_back(u);e2[v].push_back(i);
	}
	dfs1(0,-1);//为倍增作准备
	for(register int i=0;i<n-1;++i)
	{
		register int j=i,k=i+1;//倍增求LCA(i,i+1)模板
		if(dep[j]<dep[k])j^=k^=j^=k;
		for(register int l=19;dep[j]>dep[k];--l)if(dep[j]-(1<<l)>=dep[k])j=jmp[j][l];//跳到同一高度
		for(register int l=19;l>=0;--l)if(jmp[j][l]!=jmp[k][l])j=jmp[j][l],k=jmp[k][l];//枚举跳2^i
		if(j!=k)j=jmp[j][0];//终于得到j=LCA(i,i+1)了
		++cf[i];++cf[i+1];cf[j]-=2;//树上差分
	}
	dfs2(0);//树上前缀和
	for(register int i=0;i<n-1;++i)//统计答案
		if(1ll*c1[i]*cnt[i]<c2[i])ans+=1ll*c1[i]*cnt[i];//多张单程票划算
		else ans+=c2[i];//一张多程票划算
	printf("%lld",ans);//输出
}
```

### 后记

$std$ 代码写的好丑，不放上来了，有需要上官网自取。

官方题解提到了一种 $small-to-large$ 的算法，并给了一个[链接](https://codeforc.es/blog/entry/72017#comment-563190)，`PinkRabbit` 说是启发式合并，可惜窝不会，在此不做深究。



---

## 作者：lei_yu (赞：4)

我们热静分析这道题:
# 题意转化
首先在树上按编号从小到大访问每个结点，即从1出发到2再到3一直到N。

显然，在一颗树上，两个结点之间的简单路径是唯一的，而这个路径可以通过LCA求出。

经过树上的边需要用有消耗的单程票或者没有消耗的多程票，显然选择哪种票花费少就用哪种。即若经过一条边$(u,v)$共$k$次，则经过这条边的总花费是$min(c1(u,v)*k,c2)$

于是我们的问题就转化到了求每条边一共走了多少次上。

# 差分求解
直接暴力求肯定是不行的，我们可以考虑边求LCA边计算经过边的次数。

显然边比较难统计，可以把边转化到点上，即某个点$u$存储$(u,father[u])$这条边。

通过倍增（树剖应该也行），我们可以把两点的LCA转化为几根由点$u$到它的某个祖先的线段，如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/u2xvz9l5.png)

接着通过差分就可以求出每条边经过了多少次了。差分是什么不赘述。

在树上差分和在数组上差分一个道理，对于一条线段$(u,v)$（v是u的某个祖先），我们只需要建立一个差分数组t，将$t[u]++$，$t[v]--$即可。

最后在找完所有的路径（线段）后dfs一遍整颗树，每一条边$(u,v)$让$t[u]+=t[v]$，最后的t数组就是每条边经过的次数。

通过这张图可以比较直观的理解（不同的颜色代表不同的线段）

![](https://cdn.luogu.com.cn/upload/image_hosting/7n7pjb10.png)

# 参考代码

主要提供思路，代码没有过多的解释。

——大括号换行令人担忧

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
struct node
{
	int to,next,dis1,dis2;//1单程2多程 
}a[1000001];
int n,c1[1000001],head[1000001],cnt,c2[1000001],deep[1000001],fa[200005][25],t[1000001];
int ans=0;
void add_edge(int from,int to,int dis1,int dis2)
{
	a[++cnt].to=to;
	a[cnt].next=head[from];
	head[from]=cnt;
	a[cnt].dis1=dis1;
	a[cnt].dis2=dis2;
}
inline int r()//慢读
{
	int s=0,k=1;char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')k=-1;
		c=getchar();
	}
	while(isdigit(c))
	{
		s=s*10+c-'0';
		c=getchar();
	}
	return s*k;
}
void lca_dfs(int u,int father,int dp)
{
	fa[u][0]=father;
	deep[u]=dp;
	for(int i=1;i<=20;i++)
	fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=head[u];i;i=a[i].next)
	{
		int v=a[i].to;
		if(v!=father)
		{
			c1[v]=a[i].dis1;
			c2[v]=a[i].dis2;
			lca_dfs(v,u,dp+1);
		}
	}
}
void dfs(int u,int father)
{
	for(int i=head[u];i;i=a[i].next)
	{
		int v=a[i].to;
		if(v!=father)dfs(v,u);
	}
	t[fa[u][0]]+=t[u];
}
void lca(int x,int y)
{
	if(deep[x]<deep[y])swap(x,y);
	if(deep[x]!=deep[y])
	for(int i=20;i>=0;i--)
	{
		if(deep[fa[x][i]]>=deep[y])
		{
			t[x]+=1;
			t[fa[x][i]]-=1;
			x=fa[x][i];
		}
	}
	if(x==y)return;
	for(int i=20;i>=0;i--)
	{
		if(fa[x][i]!=fa[y][i])
		{
			t[x]+=1;
			t[y]+=1;
			t[fa[x][i]]-=1;
			t[fa[y][i]]-=1;
			x=fa[x][i];
			y=fa[y][i];
		}
	}
	t[x]+=1;
	t[y]+=1;
	t[fa[x][0]]-=1;
	t[fa[y][0]]-=1;
}
signed main()
{
	int y,h,s,b;
	n=r();
	for(int i=1;i<n;i++)
	{
		y=r();h=r();s=r();b=r();
		add_edge(y,h,s,b);
		add_edge(h,y,s,b);
	}
	lca_dfs(1,0,1);
	for(int i=1;i<n;i++)
	lca(i,i+1);
	dfs(1,0);
	for(int i=1;i<=n;i++)
	{
		if(c1[i]*t[i]>c2[i])
		ans+=c2[i];
		else ans+=c1[i]*t[i];
	}
	printf("%lld",ans);
}
```


---

## 作者：空清虚 (赞：3)

# 背景

日常练习`lca`

# 正文

（此为倍增`lca`做法，至于其他`lca`做法不确定是否一致，蒟蒻并没有对此进行深究）

`lca`+树上差分练习题

与某道题相似[CF191C Fools and Roads](https://www.luogu.com.cn/problem/CF191C)

`vector`存边

然后做`dfs`获得父节点和深度数组，并同时通过深度为下标多建一个`vector`，作用是方便按照深度遍历整棵树进行树上差分

树上差分在起点点和终点点标记$+1$，在lca点处标记$-2$

然后双重循环，外循环深度由大至小循环，内循环扫描 深度`vector`（标明重点），不断向上累加。

最后输出，边的经过次数为深度较大点的标记值。

最终答案大小需要`long long`。(导致本人`wa`一次)

code：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#define N 200003
#define ll long long
using namespace std;
int n,x[N],y[N],f[N][21],len[N],lg[N],lm;
ll va1[N],va2[N],ans[N],an;
vector<int>ed[N];
vector<int>le[N];
void dfs(int w,int fa)
{
	f[w][0]=fa,len[w]=len[fa]+1;
	lm=max(lm,len[w]);
	le[len[w]].push_back(w);
	for (register int i=1;i<=lg[len[w]];++i)
		f[w][i]=f[f[w][i-1]][i-1];
	for (register int i=0;i<ed[w].size();++i)
		if (ed[w][i]!=fa) dfs(ed[w][i],w);
}
int lca(int x,int y)
{
	if (len[x]<len[y]) swap(x,y);
	while (len[x]>len[y])
		x=f[x][lg[len[x]-len[y]]-1];
	if (x==y) return x;
	for (register int i=lg[len[x]]-1;i>=0;--i)
		if (f[x][i]!=f[y][i])
			x=f[x][i],y=f[y][i];
	return f[x][0];
}
int main()
{
	scanf("%d",&n);
	for (register int i=1;i<n;++i)
	{
		scanf("%d%d%d%d",&x[i],&y[i],&va1[i],&va2[i]);
		ed[x[i]].push_back(y[i]);
		ed[y[i]].push_back(x[i]);
	}
	for (register int i=1;i<=n;++i)
		lg[i]=lg[i-1]+(1<<lg[i-1]==i);
	dfs(1,0);
	for (register int i=1;i<n;++i)
	{
		ans[i]++;
		ans[i+1]++;
		ans[lca(i,i+1)]-=2;
	}
	for (register int i=lm;i>1;--i)
		for (register int j=0;j<le[i].size();++j)
			ans[f[le[i][j]][0]]+=ans[le[i][j]];
	for (register int i=1;i<n;++i)
	{
		ll as;
		if (len[x[i]]>len[y[i]]) as=ans[x[i]];
		else as=ans[y[i]];
		if (as*va1[i]<va2[i]) an+=as*va1[i];
		else an+=va2[i];
	}
	printf("%lld",an);
	return 0;
}
```
# 结尾

继续加强`lca`的码力啊——

---

## 作者：Suuon_Kanderu (赞：2)

套路题。

我们看到这题，从一顺次走到 $n$ ，先不说用单程票还是多程票，直接模拟肯定 T。 

OI 中有一种套路的思想：如果答案的值域较小可以想办法计算值域中每个数出现多少次。

这个题是类似的，我们可以想办法统计每条边需要经过多少次。之后只需要看看是多程票还是单程票更划算即可。

我们注意到 从一顺次走到 $n$ 的修改操作很多，但最终只需要一次查询，这肯定要用树上差分。比较板，属于边上的差分。

设 $t_i$ 为 $i$ 到 $i$ 父亲的边所走过的次数。

看这个图 ![](https://cdn.luogu.com.cn/upload/image_hosting/ci7j065c.png)

假设我们想要从 $(4 \rightarrow 5) + k$，那么可以拆解为 $(4 \rightarrow rt) + k$,$(5 \rightarrow rt) + k$ ,$(\operatorname{LCA}(4,5) \rightarrow rt) - 2k$。

而从一个节点到根操作很简单，只需要在 $t_i$ 本节点上修改。最后 dfs 一遍，把每个节点的 $t_i$ 加上它的所有后代即可。这样我们发现每个节点上操作的值实际上会在根到节点上的路径上起作用。

这里 LCA 我用树剖求得，很简单，比倍增好写。

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <ctime>
#define FOR(i , j , k) for(int i = j; i <= k; i++)
typedef long long ll;
using namespace std;
const int N = 200000 + 1000;
struct node{int v1 , v2 , id;};
vector<node> a[N];
int siz[N] , fa[N] , dep[N] , top[N] , son[N];

void dfs1(int f , int now) {//树剖1
	siz[now] = 1;
	fa[now] = f;
	dep[now] = dep[f] + 1;
	FOR(i , 0 , a[now].size() - 1) {
		int v = a[now][i].id;
		if(v == f)continue;
		dfs1(now , v);
		siz[now] += siz[v];
		if(siz[v] > siz[son[now]]) son[now] = v;

	}
}int t[N]  , c1[N] , c2[N];
void dfs(int v1 , int v2 , int now) {//求出每条边对应票的钱数。
	c1[now] = v1;c2[now] = v2;
	FOR(i , 0 , a[now].size() - 1) {
		if(a[now][i].id == fa[now])continue;
		dfs(a[now][i].v1, a[now][i].v2 , a[now][i].id);
	}
}
void dfs2(int f , int now) {//树剖2
	top[now] = f;
	if(son[now])dfs2(f , son[now]);
	FOR(i , 0 , a[now].size() - 1) {
		int v = a[now][i].id;
		if(v == fa[now] || v == son[now])continue;
		dfs2(v , v);
	}
}
int find(int x , int y) {//跳LCA
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]])swap(x , y);
		x = fa[top[x]];
	}
	return (dep[x] < dep[y] ? x : y);
}
void query(int x , int y) {// 从 x 到 y
//	printf("%d\n---" , x);
	int k = find(x , y);
	t[x]++; t[y]++;
	t[k] -= 2;
}
void dfs3(int now) {//树上差分后处理
	FOR(i , 0 , a[now].size() - 1) {
		int v = a[now][i].id;
		if(v == fa[now])continue;
		dfs3(v);
		t[now] += t[v];
		
	}
}
int main() {
	int n;scanf("%d" , &n);
	FOR(i , 1 , n - 1) {
		int u , v , w , x;
		scanf("%d%d%d%d" , &u , &v , &w , &x);
		a[u].push_back(node{w , x , v});
		a[v].push_back(node{w , x , u});
	}	
	dfs1(0 , 1);dfs(0 ,0 , 1);dfs2(1 , 1);
	FOR(i , 1 , n - 1)query(i , i + 1);
//	FOR(i , 1 , n)printf("%d\n" , t[i]);
	dfs3(1);
	ll ans = 0;
	FOR(i , 2 , n)//计算单程票还是多程票省钱，记录答案。
		ans += min(1ll * c1[i] * t[i] , 1ll * c2[i]);
	printf("%lld\n" , ans);
}
```


---

## 作者：FutureThx (赞：2)

~~一道树上差分的板子题~~
### 题目大意

给定一棵 $n$ 个节点的树

从小到大顺序访问每个节点，从 $1$ 开始

每条边两种状态：

- 单程票：重复经过此边将会重复计算权重

- 多程票：重复经过仅仅会计算第一次经过的权重

一条边只能拥有一种状态

因为可能会多次经过边，所以有时多程票会比单程票更加划算

现在请你输出访问的最小代价

### 思路

显然，只要对于每条边取最小经过代价，输出总和即可

而一条边的最小经过代价为：

$edge_{min} = min(t \times w_1 ,w_2 )$ 

其中 $t$ 表示此边经过次数 ， $w1,w2$ 分别表示此条边单、多程价格

所以我们着重计算 $t$ 即可，这里就可以使用树上差分进行处理

如果不会树上差分，请移步 P3128 

$m1,m2$ 的计算只需要在建图的时候附带一下即可

比较直观的是使用边差分

设数组 $ans[i]$ 表示节点 $i$ 与其父亲节点之间边的 $t$,

数组 $disw1[i]$ 表示节点 $i$ 与其父亲节点边的 $w1$

数组 $disw2[i]$ 表示节点 $i$ 与其父亲节点边的 $w2$

最后按照公式计算即可

具体见代码
### 代码

$110pts:$
```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;
#define int long long
#define MAX_N 200010
struct tree{
    vector<int> next;
    vector<int> nextw1;
    vector<int> nextw2;
}node[MAX_N];
int n;
int d[MAX_N],f[MAX_N][21],disw1[MAX_N],disw2[MAX_N];
int num[MAX_N],ans[MAX_N];
void bfs(int v){
    queue<int> q;
    d[v] = 1;
    q.push(v);
    int t = (int)(log(n) / log(2)) + 1;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i = 0;i < node[u].next.size();i++){
            int y = node[u].next[i];
            if(d[y] != 0)continue;
            d[y] = d[u] + 1;
            f[y][0] = u;
            int w1 = node[u].nextw1[i];
            int w2 = node[u].nextw2[i];
            disw1[y] = w1;
            disw2[y] = w2;
            for(int j = 1;j <= t;j++)
                f[y][j] = f[f[y][j-1]][j-1];
            q.push(y);
        }
    }
}
int LCA(int x,int y){
    int t = (int)(log(n) / log(2)) + 1;
    if(d[x] > d[y])
        swap(x,y);
    for(int i = t;i >= 0;i--)
        if(d[f[y][i]] >= d[x])
            y = f[y][i];
    if(x == y)return x;
    for(int i = t;i >= 0;i--)
        if(f[y][i] != f[x][i])
            y = f[y][i],x = f[x][i];
    return f[x][0];
}
int dfs(int now,int fa){
    ans[now] += num[now];
    for(int i = 0;i < node[now].next.size();i++){
        int y = node[now].next[i];
        if(fa != y)
            ans[now] += dfs(y,now);
    }
    return ans[now];
} 
signed main()
{
    cin >> n;
    for(int i = 1;i < n;i++){
        int u,v,w1,w2;
        cin >> u >> v >> w1 >> w2;
        node[u].next.push_back(v);
        node[u].nextw1.push_back(w1);
        node[u].nextw2.push_back(w2);
        node[v].next.push_back(u);
        node[v].nextw1.push_back(w1);
        node[v].nextw2.push_back(w2);
    }
    bfs(1);
    for(int i = 2;i <= n;i++){
        int u = i - 1,v = i;
        int z = LCA(u,v);
        num[u] += 1;
        num[v] += 1;
        num[z] -= 2;
    }
    dfs(1,-1);
    int min_ans = 0;
    for(int i = 2;i <= n;i++){
        int w1 = disw1[i];
        int w2 = disw2[i];
        int t = ans[i];
        min_ans += min(w1 * t,w2);
    }
    cout << min_ans << endl;
    return 0;
}
```
注意开 $long \ long$

### 后记

$Updata \ 2020.11.12:$ 完成题解

---

## 作者：STrAduts (赞：2)

比较有趣。

分析一下，你会发现我们只需要知道每条边走过多少遍。我们定义边 $e$ 走过 $t$ 次。则如果 $c_e \times t$ 小于 $c2_e$，我们选择单程票最优，反之，多程票最优。

前两个数据范围很好想嘛。第一个直接暴力找边经过的次数。第二个因为是链，就是一个区间修改，单点查询。所以可以直接差分去做，当然也可以线段树。

最后考虑正解。因为部分分可以差分，也可以线段树，那么转换为树上，直接树剖或者树上差分均可。

```cpp
#include <queue>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long LL;
int read() {
    int k = 1, x = 0;
    char s = getchar();
    while (s < '0' || s > '9') {
        if (s == '-')
            k = -1;
        s = getchar();
    }
    while (s >= '0' && s <= '9') {
        x = (x << 3) + (x << 1) + s - '0';
        s = getchar();
    }
    return x * k;
}

void write(LL x) {
    if(x < 0) {
    	putchar('-');
		x = -x;
    }
    if(x > 9)
		write(x / 10);
    putchar(x % 10 + '0');
}

void print(LL x, char s) {
	write(x);
	putchar(s);
}

void Swap(int &x, int &y) {
	int t = x;
	x = y;
	y = t;
}

const int MAXN = 2e5 + 5;

struct edge {
	int v, id;
	edge() {}
	edge(int V, int Id) {
		v = V;
		id = Id;
	}
};
vector<edge> mp[MAXN];
void Add_Edge(int u, int v, int id) {
	mp[u].push_back(edge(v, id)); 
	mp[v].push_back(edge(u, id)); 
}

int c[MAXN], c2[MAXN], fa[MAXN][32], w[MAXN], dep[MAXN];

bool vis[MAXN];
void bfs() {
	queue<int> q;
	q.push(1);
	dep[1] = 1;
	vis[1] = true;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i = 0; i < mp[u].size(); i++) {
			int v = mp[u][i].v;
			if(!vis[v]) {
				q.push(v);
				fa[v][0] = u;
				dep[v] = dep[u] + 1;
				for(int i = 1; i <= 20; i++)
					fa[v][i] = fa[fa[v][i - 1]][i - 1];
				vis[v] = true;
			}
		}
	}
}

void LCA(int x, int y) {
	w[x]++;
	w[y]++;
	if(dep[x] < dep[y])
		Swap(x, y);
	for(int i = 20; i >= 0; i--)
		if(dep[fa[x][i]] >= dep[y])
			x = fa[x][i];
	if(x == y) {
		w[x] -= 2;
		return ;
	}
	for(int i = 20; i >= 0; i--) 
		if(fa[x][i] != fa[y][i]) {
			x = fa[x][i];
			y = fa[y][i];
		}
	w[fa[x][0]] -= 2;
	return ;
}

LL ans = 0;
int dfs(int u, int fa) {
	int res = 0;
	for(int i = 0; i < mp[u].size(); i++) {
		int v = mp[u][i].v;
		if(v == fa)
			continue;
		int t = dfs(v, u);
		res += t;
		if((LL)t * c[mp[u][i].id] > c2[mp[u][i].id])
			ans += c2[mp[u][i].id];
		else
			ans += (LL)t * c[mp[u][i].id];
	}
	return res + w[u];
}

int main() {
	int n = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read();
		Add_Edge(u, v, i);
		c[i] = read(), c2[i] = read();
	}
	bfs();
	for(int i = 1; i < n; i++)
		LCA(i, i + 1);
	dfs(1, -1);
	print(ans, '\n');
	return 0;
} 
```

---

## 作者：BreakPlus (赞：1)

本题算法/技巧： LCA + 树上差分 + 点边对应

## Part1 本题大致思路

我们要依次走完 $1\sim n$ 这些点，要统计每条边走的次数，需要将在树上 $i\sim i+1$ 之间的边的走过次数都加一，不难想到树上差分与最近公共祖先。它们如何实现？

首先，我们需要将 **边** 化为 **点**：把边权放在深度更高的点上面。根节点是没有边权的。


我们设 $i,i+1$ 之间的 LCA 为 $f$，定义数组 $t_i$ 表示树上差分的值。（注：树上差分数组 $t_i$ 表示 $a_i- \sum \limits_{}a_k$，其中 $k$ 为 $i$ 的儿子，$d_i$ 为第 $i$ 个点本身的值）我们其实只需要把 $t_i$ 和 $t_{i+1}$ 都加上 $1$，$t_f$ 减去 $2$ 即可。（想一想，为什么要减 $2$）

最后一次 dfs 过后就求出了每条边经过的次数，还要看看单程票、多程票哪个便宜，最后统计答案即可。

## Part2 代码

![image.png](https://i.loli.net/2021/01/09/hrWNUunA27RB3VF.png)

---

## 作者：Hexarhy (赞：1)

### Preface

大家好，我喜欢暴力无脑解法，所以我用树剖两个 $\log$ 过了这题。

### Solution

和【松鼠的新家】差不多，可以直接进行树链剖分，用线段树维护。

首先要边权压成点权，这是基本功。

然后根据题意模拟一下，对 $i\in[1,n)$，树上 $i$ 到 $i+1$ 节点的路径进行覆盖。

覆盖完了之后对每个点进行访问，如果这个点被覆盖次数为 $w$，满足 $w\times c_1\le c_2$，显然买 $w$ 张单程票更划算；否则买多程票。

都挺无脑的，时间复杂度 $O(n\log ^2n)$，实际跑不满。

### Code

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cctype>
using namespace std;

namespace IO
{
    inline char getc(void)
    {
        static const int IN_LEN=1<<21|1;static char buf[IN_LEN],*s,*t;
        return (s==t)&&(t=(s=buf)+fread(buf,1,IN_LEN,stdin)),s==t?-1:*s++;
    }
    template<typename tp>
    void read(tp& a)
    {
        register tp num=0;register int f=1;register char ch=getc();
        while(!isdigit(ch) && ch!='-') ch=getc();
        if(ch=='-') f=-1,ch=getc();
        do
            num=num*10+int(ch-'0'),ch=getc();
        while(isdigit(ch));
        a=num*f;
    }
}using namespace IO;

typedef long long ll;
typedef const int cint;
cint MAXN=2e5+5;
int n;
struct Edge
{
    int u,v,c1,c2;
}e[MAXN];
vector<int> edge[MAXN];
int c1[MAXN],c2[MAXN];
int fa[MAXN],size[MAXN],top[MAXN],son[MAXN],dep[MAXN],dfn[MAXN],cnt;
#define foreach(vec)    for(vector<int>::const_iterator it=vec.begin();it!=vec.end();it++)

void dfs1(cint& u,cint& Fa)
{
    fa[u]=Fa;
    dep[u]=dep[Fa]+1;
    size[u]=1;
    foreach(edge[u])
    {
        cint& v=*it;
        if(v==Fa)   continue;
        dfs1(v,u);
        size[u]+=size[v];
        if(size[son[u]]<size[v])    son[u]=v;
    }
}

void dfs2(cint& u,cint& Top)
{
    top[u]=Top;
    dfn[u]=++cnt;
    if(son[u]) dfs2(son[u],Top);
    foreach(edge[u])
    {
        cint& v=*it;
        if(v==fa[u] || v==son[u])   continue;
        dfs2(v,v);
    }
}

class segment_tree
{
private:
    #define mid ((tree[cur].l+tree[cur].r)>>1)
    #define lson (cur<<1)
    #define rson (cur<<1|1)
    struct node
    {
        int l,r,val,tag;
    }tree[MAXN<<2];
    inline void pushup(cint& cur)
    {
        tree[cur].val=tree[lson].tag+tree[rson].tag;
    }
    inline void pushdown(cint& cur)
    {
        if(!tree[cur].tag)  return;
        tree[lson].val+=tree[cur].tag*(tree[lson].r-tree[lson].l+1);
        tree[rson].val+=tree[cur].tag*(tree[rson].r-tree[rson].l+1);
        tree[lson].tag+=tree[cur].tag;
        tree[rson].tag+=tree[cur].tag;
        tree[cur].tag=0;
    }
public:
    void build(cint& cur,cint& l,cint& r)
    {
        tree[cur].l=l;tree[cur].r=r;
        if(l==r)    return;
        build(lson,l,mid);
        build(rson,mid+1,r);
    }
    void modify(cint& cur,cint& l,cint& r,cint& val)
    {
        if(l<=tree[cur].l && tree[cur].r<=r)
        {
            tree[cur].tag+=val;
            tree[cur].val+=val*(tree[cur].r-tree[cur].l+1);
            return;
        }
        pushdown(cur);
        if(l<=mid)  modify(lson,l,r,val);
        if(mid<r)   modify(rson,l,r,val);
        pushup(cur);
    }
    int query(cint& cur,cint& pos)
    {
        if(pos==tree[cur].l && pos==tree[cur].r)
            return tree[cur].val;
        pushdown(cur);
        if(pos<=mid)  return query(lson,pos);
        return query(rson,pos);
    }
}t;

void modify_path(int u,int v,cint& val)
{
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        t.modify(1,dfn[top[u]],dfn[u],val);
        u=fa[top[u]];
    }
    if(dep[u]>dep[v])   swap(u,v);
    t.modify(1,dfn[son[u]],dfn[v],val);
}

int main()
{
    read(n);
    for(register int i=1;i<n;++i)
    {
        read(e[i].u);read(e[i].v);read(e[i].c1);read(e[i].c2);
        register cint u=e[i].u,v=e[i].v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs1(1,1);
    dfs2(1,1);
    t.build(1,1,n);
    for(register int i=1;i<n;++i)//奇特的边权转点权
    {
        register cint u=e[i].u,v=e[i].v;
        if(fa[u]==v)
        {
            c1[u]=e[i].c1;
            c2[u]=e[i].c2;
        }
        else
        {
            c1[v]=e[i].c1;
            c2[v]=e[i].c2;
        }
    }
    for(register int i=1;i<n;++i)    modify_path(i,i+1,1);
    ll ans=0;
    for(register int i=2;i<=n;++i)
    {
        register cint res=t.query(1,dfn[i]);
        if(1ll*res*c1[i]<=c2[i])    ans+=1ll*res*c1[i];//贪心
        else    ans+=c2[i];
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：天南地北 (赞：1)

如何求从$1$访问到$n$最少需要多少费用?

其实**我们可以从“按编号从小到大顺序访问每个节点”入手**

如果我们要尽可能的花费更小，肯定走两点之间花费最小的简单路径。

**找到两个点之间的最短路径，会经过他们距离最近的公共祖先**，所以我们需要用到$LCA$，而且为了尽可能快，我们需要优化$LCA$(优化有多种，具体看读者喜爱)

问题继续简化，现在的问题是**我们并不知道我走一条路是买单程票呢，还是买多程票呢？**

考虑数组记数，每次经过一个边就以这条边的编号为下标加$1$，表示这条边又经过了一次。但是有一个很现实的问题：这样多次记数会超时……

考虑树上差分，显然是可以的，因为树上差分明显快多了……

树上差分不会？[传送门](https://www.luogu.com.cn/blog/kurlisjoey-julao/shu-shang-ci-fen)

本人使用**点差分**，就和线性数组差分一个道理的去增减，最后遍历整棵树的时候，将从根节点一直累加到当前节点（累加的值为根节点到当前节点的简单路径），即可求出次数。

所以本题算法为：树上差分+LCA，做完了。

参考程序：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm> 
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define drep(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int maxm=200000+10;
int n,m;
struct Edge
{
	int next,to;
	int one_way,some_way;
}edge[maxm];
int cnt; 
int head[maxm],deep[maxm];
long long fa[maxm][23],dp[maxm];
long long way1[maxm],way2[maxm];

void Add_edge(int u,int v,int way1,int way2)
{
	cnt++;
	edge[cnt].next=head[u];
	edge[cnt].to=v;
	edge[cnt].one_way=way1;
	edge[cnt].some_way=way2;
	head[u]=cnt;	
}
void dfs(int u,int father)
{
    deep[u]=deep[father]+1;
    for(int i=1;(1<<i)<=deep[u];i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head[u];i;i=edge[i].next)
    {
        int v=edge[i].to;
        if(v==father)continue;
        fa[v][0]=u;
        way1[v]=edge[i].one_way;
		way2[v]=edge[i].some_way;
        dfs(v,u);
    }
}
void LCA(int x,int y)
{
	if(deep[x]<deep[y])swap(x,y);
	if(deep[x]!=deep[y])
		drep(i,20,0)
			if(deep[fa[x][i]]>=deep[y])
			{
				dp[x]+=1;dp[fa[x][i]]-=1;
				x=fa[x][i];
			}
	if(x==y)return;
	drep(i,20,0)
		if(fa[x][i]!=fa[y][i])
		{
			dp[x]+=1;dp[y]+=1;
			dp[fa[x][i]]-=1;dp[fa[y][i]]-=1;
			x=fa[x][i];y=fa[y][i];
		}
	dp[x]+=1;dp[y]+=1;
	dp[fa[x][0]]-=1;dp[fa[y][0]]-=1;
}
void Dfs(int u,int father)
{
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v==father)continue;
		Dfs(v,u);
	}
	dp[fa[u][0]]+=dp[u];
}
int main()
{
	std::ios::sync_with_stdio(false);
	cin>>n;
	rep(i,1,n-1)
	{
		int x,y,way1,way2;
		cin>>x>>y>>way1>>way2;
		Add_edge(x,y,way1,way2);
		Add_edge(y,x,way1,way2);//建树
	} 
	dfs(1,0);//跑图，用来求LCA
	rep(i,1,n-1)
		LCA(i,i+1);//求两点之间的简单路径
	Dfs(1,0);//跑图，顺便求出每条边的次数
	long long ans=0;
	rep(i,1,n)//贪心
	{
		if(way1[i]*dp[i]<way2[i])ans+=way1[i]*dp[i];
		else ans+=way2[i];
	}
	cout<<ans;
	return 0;
}
```
举一反三：

如果本题修改为是一个图，且每个点到每个点有多条路径，又或者说多程票限制次数，如何求？





---

