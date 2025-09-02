# [AGC002D] Stamp Rally

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc002/tasks/agc002_d



## 样例 #1

### 输入

```
5 6
2 3
4 5
1 2
1 3
1 4
1 5
6
2 4 3
2 4 4
2 4 5
1 3 3
1 3 4
1 3 5
```

### 输出

```
1
2
3
1
5
5
```

# 题解

## 作者：ZCETHAN (赞：32)

# 引入
大家都知道$Kruskal$求最小生成树吧，这个算法就是建立在前面说的算法的基础上的一个奇妙的想法。
有这么一个问题，给你一张图，每条边都有权值，然后规定一堆东西后问：满足条件的路径中，所经过边权最大值最小是多少。
# 初步想法
二分，一定是最先想到的，我们接下来就以标题中的[那题](https://www.luogu.com.cn/problem/AT1998)为例讲讲这个算法。

我们很容易想到二分最大边权，然后验证。但是每次验证都跑$dfs$肯定得炸。
那么怎么办呢。

来看看重构树算法的实现吧。
# 实现
首先，根据$Kruskal$的贪心思路，如果我从$x$节点出发，有较小的边可以走，肯定是不会走较大的边的，换句话说，就是一定是在图的最小生成树上走最优。

所以无疑，算法第一步：将边按权排序，求出最小生成树。

然后在求的过程中，就是本算法的构造了。对于我当前枚举的边所连接的两个点(或者点集)，用一个虚拟节点建在上方作为这两个点的父节点，然后将这个父节点的权值赋为边的权值。

也许不是很清楚，那么来看看题目中样例这个图：
(注意本题是把编号当成边权的)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210103154908981.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3poYW5nY2hpemM=,size_16,color_FFFFFF,t_70)

和$Kruskal$一样，先取出$Edge(2,3)$，然后建立一个父子关系，加入到同一集合里。已经有5个点了，所以他们的父节点就记为6，权值为1。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210103155309782.png)

然后是$Edge(4,5)$，进行同样的操作。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210103155423938.png)

然后是$Edge(2,1)$，但是此时$2$已经属于一个点集了，所以实质上是把1和2所在的点集连起来，所以应该是连结$(1,6)$。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210103155643892.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3poYW5nY2hpemM=,size_16,color_FFFFFF,t_70)

然后查到$Edge(1,3)$，但是在前面的并查集中可以查到，1和3已经在同一集合里了，所以跳过。
所以最后一条边是$Edge(1,4)$，实质是把$8,7$连起来。
其他的都会跳过，因为已经合并好了。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210103160005752.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3poYW5nY2hpemM=,size_16,color_FFFFFF,t_70)

然后就可以在这棵树上做一些奇奇怪怪的操作了，因为它有一个美妙的性质：每一条树枝上，边权是单调的，那么可以倍增来快速找到最大的不超过某个值的最小位置是哪里了。

比如本题，就可以二分答案，然后对于$x$和$y$，分别向上跳到点权是大于我二分的值为止，然后向下子树中叶节点个数一加就是我经过点的个数，和$z$比一下，就可以实现这个二分了。

$\color{Red}{Ps:}$一定一定一定要注意倍增不要写错以及，如果$xy$跳到一起去了，只能算一个。

相信理解起来不难吧。上代码。

# Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 1<<30
using namespace std;
const int MAXN=2e5+10;
vector<int> vec[MAXN];
void add(int fa,int u,int v){
	vec[fa].push_back(u);
	vec[fa].push_back(v);
}
int cnt,son[MAXN],f[MAXN][20],v[MAXN];
void dfs(int x,int fa){
	f[x][0]=fa;
	for(int i=1;i<20;i++) f[x][i]=f[f[x][i-1]][i-1];
	if(vec[x].size()==0){son[x]=1;return;}
	son[x]=0;
	for(int i=0;i<vec[x].size();i++){
		int s=vec[x][i];
		if(s==fa) continue;
		dfs(s,x);son[x]+=son[s];
	}
}//预处理倍增和子树中叶节点的个数
int check(int p,int x,int y){
	for(int i=19;i>=0;i--){
		if(v[f[x][i]]<=p) x=f[x][i];
		if(v[f[y][i]]<=p) y=f[y][i];
	}
	if(x==y) return son[x];
	else return son[x]+son[y];
}//验算，得到经过节点个数
int ff[MAXN];
int find(int x){return ff[x]==x?x:ff[x]=find(ff[x]);}
int main()
{
	int n,m,x,y,z;
	scanf("%d%d",&n,&m);cnt=n;
	for(int i=1;i<=2*n;i++) v[i]=0,ff[i]=i;
	v[0]=inf;//防止跳到根的外面去
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		int fx=find(x),fy=find(y);
		if(cnt<n*2-1&&fx!=fy){
			cnt++;
			v[cnt]=i;
			ff[fy]=cnt;
			ff[fx]=cnt;//这里其实和裸的Kruskal很像的，但是由于有新建的节点所以更优美了
			add(cnt,fx,fy);
		}//本题的特殊性，否则需要按权排序后再做
	}
	dfs(cnt,0);int Q;
	for(scanf("%d",&Q);Q--;){
		scanf("%d%d%d",&x,&y,&z);
		int ans=m,l=0,r=m;
		while(l<=r){
			int mid=l+r>>1;
			if(check(mid,x,y)<z) l=mid+1,ans=l;
			else r=mid-1;
		}
		printf("%d\n",ans);
	}
}
```
# END
很多人用可持久化并查集和整体二分过了这题……

---

## 作者：peterwuyihong (赞：15)

题意：一张连通图，第 $i$ 条边的边权是 $i$，多次询问，每次询问给定 $x,y,k$，询问从 $x$ 和 $y$ 两个点走出来的点集（包括 $x,y$，满足大小等于 $k$ 的时候，走过的边最大值的最小值是多少，允许离线。

最大值的最小值？二分。

多次询问？整体二分。

设一个函数 $\text{solve(1,m,1,q)}$ 表示接下来要搞定 $[1,q]$ 之间的问题，并且我们可以保证答案在 $[1,m]$ 之间。

然后每次做出来一个 $\text{mid}$，它表示我们接下来要二分，然后我们把边权小于等于 $\text{mid}$ 的边留下，判断哪些询问的答案在 $[1,mid]$，哪些在 $[mid+1,r]$。

然后就是这个判断的过程了，看看询问的两个点通过留下的边能走到哪里，把能走出来的点集与 $k$ 比较即可，大于 $k$ 就表示留下来的边太大了，我们还能更小。

同时使用一个并查集维护即可。

现在是 $15:44$，我看我什么时候写完。

现在是 $16:26$，我写完了。

```cpp
#define maxn 100010
int n,m,G;
int x[maxn],y[maxn];
struct prpr{
	int x,y,k,id;
}q[maxn],tmpl[maxn],tmpr[maxn];
int fa[maxn],ans[maxn],siz[maxn];
int get(int x){
	if(x==fa[x])return fa[x];
	return get(fa[x]);
}
pair<int,int>sta[maxn];
int top;
void merge(int x,int y){//又维护了siz，又按秩合并了，我觉得很巧妙啊！！ 
	x=get(x),y=get(y);
	if(x==y)return;
	if(siz[x]>siz[y])swap(x,y);
	fa[x]=y;siz[y]+=siz[x];
	sta[++top]=make_pair(x,y);
}
void solve(int l,int r,int L,int R){
	if(l==r){
		for(int i=L;i<=R;i++)ans[q[i].id]=l;
		int X=get(x[l]),Y=get(y[l]);
		if(X==Y)return;
		if(siz[X]>siz[Y])swap(X,Y);
		fa[X]=Y;siz[Y]+=siz[X];
		return;
	}
	int mid=(l+r)>>1;
	for(int i=l;i<=mid;i++)merge(x[i],y[i]);
	int ll=0,rr=0;
	for(int i=L;i<=R;i++){
		int x=get(q[i].x),y=get(q[i].y);
		if(x==y){
			if(siz[x]>=q[i].k)tmpl[++ll]=q[i];
			else tmpr[++rr]=q[i];
		}else{
			if(siz[x]+siz[y]>=q[i].k)tmpl[++ll]=q[i];
			else tmpr[++rr]=q[i];
		}
	}
	for(int i=1;i<=ll;i++)q[L+i-1]=tmpl[i];
	for(int i=1;i<=rr;i++)q[L+ll+i-1]=tmpr[i];
	while(top)fa[sta[top].first]=sta[top].first,siz[sta[top].second]-=siz[sta[top].first],top--;
	solve(l,mid,L,L+ll-1);
	solve(mid+1,r,L+ll,L+ll+rr-1);
}
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	cin>>n>>m;
	for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1;
	for(int i=1;i<=m;i++)cin>>x[i]>>y[i];
	cin>>G;
	for(int i=1;i<=G;i++)cin>>q[i].x>>q[i].y>>q[i].k,q[i].id=i;
	solve(1,m,1,G);
	for(int i=1;i<=G;i++)cout<<ans[i]<<endl;
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
```
被埋伏到了，之前加上了 ```L>R``` 的优化，这样就不能遍历到底，有一些边没连上，就白给了。

最优解还蛮好拿的。

$\text{Update 2021.10.8}$

学了 $\text{Kruskal}$ 重构树，补一个重构树做法。

[前置芝士](https://www.luogu.com.cn/blog/Peterprpr/p1967-noip2013-ti-gao-zu-huo-ju-yun-shu-ji-lu)

边权是排好的，nice

建出重构树，使得上面的代表节点表示，子树的所有叶子节点构成的图，拥有这个代表节点的点权，可以随便走。

然后二分这个阈值，对两个点一起往上跳着做就行了。

现在是 $20:24$，我看我什么时候写完。

现在是 $20:43$，我写完了。

```cpp
#define maxn 200010
int n,m,Q,x,y,z;
int fa[maxn],val[maxn];
int get(int x){
	if(x==fa[x])return x;
	return fa[x]=get(fa[x]);
}
int cnt;
int head[maxn],Next[maxn<<1],ver[maxn<<1],__;
void add(int x,int y){
	ver[++__]=y;
	Next[__]=head[x];
	head[x]=__;
}
int FA[maxn][20],t,siz[maxn];
void dfs(int x){
	if(!head[x])siz[x]=1;
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		FA[y][0]=x;
		for(int j=1;j<=t;j++)
		FA[y][j]=FA[FA[y][j-1]][j-1];
		dfs(y);
		siz[x]+=siz[y];
	}
}
bool check(int x,int y,int mid){
	for(int i=t;~i;i--)
	if(val[FA[x][i]]<=mid)x=FA[x][i];
	for(int i=t;~i;i--)
	if(val[FA[y][i]]<=mid)y=FA[y][i];
	if(x==y)return siz[x]>=z;
	return siz[x]+siz[y]>=z;
}
int l,r,mid;
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	cin>>n>>m;
	for(int i=1;i<=2*n;i++)fa[i]=i;
	cnt=n;
	for(int i=1;i<=m;i++){
		cin>>x>>y;
		x=get(x),y=get(y);
		if(x==y)continue;
		fa[x]=fa[y]=++cnt;
		add(cnt,x),add(cnt,y);
		val[cnt]=i;
	}
	t=ceil(log(n)/log(2));
	val[0]=INT_MAX;
	dfs(cnt);
	cin>>Q;
	while(Q--){
		cin>>x>>y>>z;	
		l=1,r=m;
		while(l<=r){
			mid=(l+r)>>1;
			if(check(x,y,mid))r=mid-1;
			else l=mid+1;
		}cout<<l<<endl;
	}
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
```
代码还挺短。。。

---

## 作者：hwk0518 (赞：9)

这道题是可以做到一个$log$的。

首先看到最大值最小，想到二分。二分一个答案$mid$，把前$mid$条边暴力用并查集连上，如果两个点在一个集合，就判这个集合大小是否大于$z$，否则就把两个集合并起来判，这毋庸赘述。

这样做，时间复杂度是$O(n^2*log n)$。

瓶颈在于，如果所有问题的答案都是$m$，在连完$m$条边后，我们本可以一次性输出所有答案，但这个做法需要对于每个询问，从头再写并查集，不够优秀。想到整体二分。

开一棵线段树，先把所有询问挂在根，从上到下处理。设当前区间是$[l,r]$，$[l,mid]$连完后一次性判断所有询问，已合法就下传到左儿子，否则下传到右儿子。再把$[mid+1,r]$连完。

但如果深搜树，时间复杂度仍是$O(n^2*log n)$，原因是做完$[1,4]$后做$[1,2]$，要回退到两步之前的状态，这是路径压缩并查集做不到的。（当然，可以用按秩合并做到$O(n*(log n)^2)$。）

想到可以广搜树。先把$m$补到$2$的方幂，这样树是一棵满二叉树。一层一层处理，询问区间连续，且并在一起恰好是$[1,m]$，

实现方面，用队列维护即可。当左端点是$1$时，要清空数组。

代码：

```

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<math.h>
#include<vector>
using namespace std;

const int N=1e6+5;
int n,m,q,ans[N],fa[N],sz[N];
pair<int,int> p[N],pre[N];
struct node
{
	int x,y,z;
};
node que[N];
vector<int> v[N];

void init()
{
	int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;++i) scanf("%d%d",&p[i].first,&p[i].second);
	int tmp=1;while(tmp<m) tmp<<=1;
	for(i=m+1;i<=tmp;++i) p[i]=make_pair(1,1);m=tmp;
	scanf("%d",&q);
	for(i=1;i<=q;++i) scanf("%d%d%d",&que[i].x,&que[i].y,&que[i].z);
}

void prework(int l,int r,int rt)
{
	pre[rt]=make_pair(l,r);
	if(l==r) return;
	int mid=(l+r)>>1;
	prework(l,mid,rt<<1);
	prework(mid+1,r,rt<<1|1);
}

int getfa(int x)
{
	if(fa[x]!=x) fa[x]=getfa(fa[x]);
	return fa[x];
}
void mer(int x,int y)
{
	int fx=getfa(x),fy=getfa(y);
	if(fx!=fy) fa[fx]=fy,sz[fy]+=sz[fx];
}

void work()
{
	int i,j;
	for(i=1;i<=q;++i) v[1].push_back(i);
	for(i=1;i<m;++i)
	{
		if(pre[i].first==1)
			for(j=1;j<=n;++j) fa[j]=j,sz[j]=1;
		int mid=(pre[i].first+pre[i].second)>>1;
		
		for(j=pre[i].first;j<=mid;++j)
			mer(p[j].first,p[j].second);
			
		vector<int>::iterator it;
		for(it=v[i].begin();it!=v[i].end();++it)
		{
			int to=*it;
			int fx=getfa(que[to].x);
			int fy=getfa(que[to].y);
			int ans=sz[fx];
			if(fx!=fy) ans+=sz[fy]; 
			if(ans>=que[to].z) v[i<<1].push_back(to);
			else v[i<<1|1].push_back(to);
		}
		
		for(j=mid+1;j<=pre[i].second;++j)
			mer(p[j].first,p[j].second);
	}
	
	for(j=m;j<2*m;++j)
	{
		vector<int>::iterator it;
		for(it=v[j].begin();it!=v[j].end();++it)
			ans[*it]=pre[j].first;
	}
	
	for(i=1;i<=q;++i) printf("%d\n",ans[i]);
}

int main()
{
	init();prework(1,m,1);work();
	return 0;
}

```

---

## 作者：ImmortalWatcher (赞：5)

- 这题限制了经过点的个数要恰好为 $z$，不能大也不能小，所以二分是一个比较好的解决方案。

- 依据题目，它要求的是所有满足条件的路径，也就是从点 $x$ 和 $y$ 出发，经过的点(不重复)数量等于 $z$ 的路径，经过的边最大编号最小是多少。

- 令边的权值为边的编号，求路径的边权最大值最小容易想到 $\text{Kruskal}$ 重构树。

考虑二分答案，那么就给了点在 $\text{Kruskal}$ 重构树上的限制，也就是一个点可以找到深度最浅的一个祖先，满足它的点权小于二分值，那么这个点就可以走到这棵子树上的所有点。

记录每棵字数的叶子结点个数，然后 $x,y$ 倍增计算答案，然后与 $z$ 比较即可完成二分。

在细节上，需要注意在倍增的时候，要记得判断 $x,y$ 最后跳到的是不是一个点，小心算重。

代码复杂度较低，时间复杂度为两个 $\log$。


```cpp
#include<cstdio>
using namespace std;
int n,m,fa[200010],tot,x,y,val[200010],f[200010][18],cnt,dep[200010],ans,leave[200010],q,z;
struct node{int last,en,next;} e[400010];
int get(int x){return fa[x]==x?x:fa[x]=get(fa[x]);}
void add(int x,int y)
{
	e[++tot].en=y;
	e[tot].next=e[x].last;
	e[x].last=tot;
}
void dg(int x,int fa)
{
	f[x][0]=fa;dep[x]=dep[fa]+1;
	for (int i=e[x].last;i;i=e[i].next)
		if (e[i].en!=fa) dg(e[i].en,x),leave[x]+=leave[e[i].en];
}
int check(int x,int y,int mid)
{
	for (int i=17;i>=0;i--)
	{
		if (val[f[x][i]]<=mid) x=f[x][i];
		if (val[f[y][i]]<=mid) y=f[y][i];
	}
	if (x==y) return leave[x];
	else return leave[x]+leave[y];
}
int main()
{
	scanf("%d%d",&n,&m);
	cnt=n;
	for (int i=1;i<2*n;i++) fa[i]=i;
	for (int i=1;i<=n;i++) leave[i]=1;
	val[0]=0x3f3f3f3f;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		if (cnt==2*n-1) continue;
		int u=get(x),v=get(y);
		if (u!=v)
		{
			++cnt;
			fa[u]=fa[v]=cnt;
			val[cnt]=i;
			add(cnt,u);add(cnt,v);
		}
	}
	dg(cnt,0);
	for (int j=1;j<=17;j++)
		for (int i=1;i<=cnt;i++)
			f[i][j]=f[f[i][j-1]][j-1];
	scanf("%d",&q);
	for (int i=1;i<=q;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		int l=1,r=m,mid;ans=0;
		while (l<=r)
		{
			mid=(l+r)>>1;
			if (check(x,y,mid)>=z) ans=mid,r=mid-1;
			else l=mid+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：gyh20 (赞：4)

其实这道题有一个很暴力的方法。

很容易想到离线加边，判断每一个询问是否满足条件，但必须每次检查每一个询问，时间复杂度 $O(mq\log n)$。

上述过程每一次检验非常浪费时间，考虑分块，每插入 $O(\sqrt m)$ 次检验一次，对于每一个询问倒着扫一遍用带撤销并查集断一下就行了。

时间复杂度 $O(q\sqrt m\log n)$ 常数较小。

```cpp
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
#define re register
using namespace std;
const int Mxdt=100000;	//单次大小 
inline char gc(){
	static char buf[Mxdt],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mxdt,stdin),p1==p2)?EOF:*p1++;
}
inline char pc(char ch,bool bj){
	static char buf[Mxdt],*p1=buf,*p2=buf+Mxdt;
	return (bj||(*p1++=ch)&&p1==p2)&&fwrite(p1=buf,1,p1-buf,stdout),0;
}
void print(int x)
{
	if(x>9)print(x/10);
	pc(x%10^48,false);
}
inline void printnum(int x,char ch)
{
	print(x),pc(ch,false);
}
inline int read(){
	re int t=0;re char v=gc();
	while(v<'0')v=gc();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=gc();
	return t;
}
int fa[100002],n,m,q,a[100002],b[100002],A[100002],B[100002],C[100002],ans[100002],siz[100002],tp,stkx[100002],stky[100002],t[100002],aa[100002],bb[100002],sss,cc[100002];
inline int root(re int x){return x==fa[x]?x:root(fa[x]);}
inline void merge(re int x,re int y,re int z){
	if((x=root(x))==(y=root(y)))return;
	if(siz[x]>siz[y])swap(x,y);
	fa[x]=y,stkx[++tp]=x,stky[tp]=y,siz[y]+=siz[x],t[tp]=z;
}
inline void undo(){
	siz[stky[tp]]-=siz[stkx[tp]];
	fa[stkx[tp]]=stkx[tp];
	--tp;
}
inline bool check(re int x){
	re int xx=root(A[x]),yy=root(B[x]);
	if(xx==yy)return siz[xx]>=C[x];
	return (siz[xx]+siz[yy])>=C[x];
}
int main(){
	n=read(),m=read();
	for(re int i=1;i<=n;++i)siz[fa[i]=i]=1;
	for(re int i=1;i<=m;++i)a[i]=read(),b[i]=read();
	q=read();
	for(re int i=1;i<=q;++i)A[i]=read(),B[i]=read(),C[i]=read();
	re int ss=sqrt(m),lst=0;
	for(re int i=1;i<=m;++i){
		merge(a[i],b[i],i);
		if(i%ss==0||(i==m)){
			for(re int j=1;j<=q;++j)
				if(!ans[j]){
					re int pos=i;sss=0;
					while(check(j)){
						if(pos==t[tp])undo();
						ans[j]=pos;--pos;
					}
					for(re int k=pos;k<=i;++k)merge(a[k],b[k],k);
				}
			lst=i;
		}
	}
	for(re int i=1;i<=q;++i)printnum(ans[i],'\n');
	return pc('o',1);
}
```


---

## 作者：psoet (赞：3)

**克鲁斯塔尔重构树**是最小生成树中的Krustal算法的一个衍生物。

我们在跑Krustal时，将边权按从小到大排序，然后每次只要这条边不在同一个连通块中，就将其加入最小生成树，同时用并查集维护连通性。

与此不同的是，Krustal重构树不是直接连边，而是**新建一个节点，然后将这个点作为这两个连通块根节点父亲的父亲，将其点权设为边权**。整个过程维护的是一个有根二叉树森林（带点权），同时由于一般是把边按边权从小到大排序，维护的是一个大根堆。

由于一些Feature，克鲁斯塔尔重构树可以方便维护“从一个点，经过一定约束的边能够到达点的集合”。（具体可以看往年日报）在此题中，我们只需要二分点权（即边的编号），并向上倍增跳父亲即可，每次跳的时候不能超过二分出来的点权,然后判定两个子树并的大小是否大于等于z即可。

（建议将此题作为板题）
```cpp
#include <bits/stdc++.h>
#define LL long long
#define F(i, a, b) for(int i = a; i <= b; ++i)

using namespace std;

const int maxn = 1e5 + 5;
int n, m, q, tot = 0, f[maxn * 2][25], p[maxn * 2], s[maxn * 2], val[maxn * 2],dep[maxn * 2];
int getf(int x)
{
    return x == p[x] ? x : (p[x] = getf(p[x]));
}
int lca(int u, int v)
{
    if(dep[u] < dep[v]) swap(u, v);
    int delt = dep[u] - dep[v];
    for(int i = 0; i < 20; ++i) if(1 << i & delt) u = f[u][i];
    if(u == v) return u;
    for(int i = 19; i >= 0; --i)
        if(f[u][i] && f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
    return f[u][0];
}
int ancestor(int u, int lim)
{
    int v = u;
    for(int i = 19; i >= 0; --i) if(f[v][i] && val[f[v][i]] <= lim) v = f[v][i];
    return v;
}//从u向上跳，每次点权不能超过lim，最远能跳到的祖先
int main()
{
    scanf("%d%d", &n, &m);
    F(i, 1, n) p[i] = i, s[i] = 1;
    tot = n;
    F(i, 1, m)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        int fu = getf(u), fv = getf(v);
        if(fu != fv)
        {
            ++tot;
            p[fu] = p[fv] = p[tot] = tot;
            f[fu][0] = f[fv][0] = tot;
            val[tot] = i;
        }
    }
    for(int i = tot; i; --i)
    {
        for(int j = 0; f[i][j]; ++j) f[i][j + 1] = f[f[i][j]][j];
        if(f[i][0]) dep[i] = dep[f[i][0]] + 1;
    }
    F(i, 1, tot)
    {
        if(f[i][0]) s[f[i][0]] += s[i];
    }
    scanf("%d", &q);
    F(i, 1, q)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        int l = 1, r = m, mid, ans = 0;
        while(l <= r)
        {
            mid = (l + r) / 2;
            int u = ancestor(x, mid), v = ancestor(y, mid), t = lca(u, v);
            bool flag = false;
            if(t == u) flag = (s[u] >= z);
            else if(t == v) flag = (s[v] >= z);
            else flag = (s[u] + s[v] >= z);
            if(flag) ans = mid, r = mid - 1;
            else l = mid + 1;
            //如果其中一个祖先是另一个祖先的祖先，直接加起来会有问题
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：_SeeleVollerei_ (赞：2)

一个比较显然的思路是建出可持久化并查集同时维护 size，然后二分时间直接取出 size 判断即可。

但是发现这题每个版本只会衍生出一个新的版本，所以不用真的写个主席树去维护这个并查集。

考虑按秩合并，这种合并的方式发现每个点的 fa 数组只会有两个取值，一个是它自己，一个是它作为根被合并出去时的 fa，我们只需要顺便维护一下这个被合并的时间就行了。

考虑维护 size，发现每个时间只会更新一个根的 size，所以对每个点开个 vector 存下更新的时间和更新后的 size 即可。

每次询问外面有一层二分，并查集按秩合并和利用 vector 查询 size 都是 $O(\log n)$ 的复杂度，所以总复杂度为 $O(n\log^2n)$。

具体实现见代码。

https://atcoder.jp/contests/agc002/submissions/33327714

---

## 作者：ZSH_ZSH (赞：2)

### AGC002D

~~差点不会做，身败名裂~~

显然发现这两个人只会走最小生成树上的边 ~~然而并没有什么用~~

一开始想对每个询问二分，但是时间复杂度太高，是 $O(q n \log n)$，无法接受

考虑二分的过程，只需要判断在 $mid$ 时刻， ` size[getfa(x)]+size[getfa(y)]>=z` 即可，而对于每个询问，这样的 $mid$ 不超过 $\log m$ 个

于是可以手动模拟 $\log m$ 次完整的连边过程，对于每一个询问，维护当前的 $l,r$ ，在这次连边过程中询问 $mid$，之后更新 $l,r$ 即可

总的时间复杂度 $O((n+m+q) \log m)$

代码（注意 `size` 在 AtCoder 是关键字，因为这个 CE 了一发 /youl ）
```
#include<bits/stdc++.h>
#define rep(i,a,b) for (register int i=(a);i<=(b);i++)
#define drep(i,a,b) for (register int i=(a);i>=(b);i--)
typedef long long ll;
using namespace std;
inline ll read()
{
	ll sum=0,f=0;char c=getchar();
	while (!isdigit(c)) f|=(c=='-'),c=getchar();
	while (isdigit(c)) sum=(sum<<1)+(sum<<3)+(c^48),c=getchar();
	return f?-sum:sum;
}

#define fir first
#define sec second
const int N=500010;
int n,m,Q,a[N],fa[N],siz[N],sure[N],ans[N];
pair<int,int>p[N],e[N];
pair<pair<int,int>,int>q[N];
vector<int>vec[N];

int getfa(int x){return x==fa[x]?x:fa[x]=getfa(fa[x]);}
inline void merge(int x,int y)
{
	x=getfa(x),y=getfa(y);
	if (x==y) return;
	fa[y]=x,siz[x]+=siz[y];
}

int main()
{
	n=read(); m=read(); rep(i,1,m) e[i].fir=read(),e[i].sec=read();
	Q=read(); rep(i,1,Q) q[i].fir.fir=read(),q[i].fir.sec=read(),q[i].sec=read(),p[i].fir=1,p[i].sec=m;
	rep(times,1,20)
	{
		rep(i,1,m) vec[i].clear();
		rep(i,1,Q) if (!sure[i])
		{
			int mid=(p[i].fir+p[i].sec)>>1;
			vec[mid].push_back(i);
		}
		rep(i,1,n) fa[i]=i,siz[i]=1;
		rep(i,1,m)
		{
			merge(e[i].fir,e[i].sec);
			for (auto id:vec[i])
			{
				int u=q[id].fir.fir,v=q[id].fir.sec;
				if (getfa(u)!=getfa(v)) ans[id]=siz[getfa(u)]+siz[getfa(v)];
				else ans[id]=siz[getfa(u)];
			}
		}
		rep(i,1,Q) if (!sure[i])
		{
			if (ans[i]>=q[i].sec) p[i].sec=(p[i].fir+p[i].sec)>>1;
			else p[i].fir=((p[i].fir+p[i].sec)>>1)+1;
			if (p[i].fir==p[i].sec) sure[i]=1;
		}
	}
	rep(i,1,Q) printf("%d\n",p[i].fir);
} 
```

---

## 作者：ezoiLZH (赞：2)

## 题解：
先想一想，可以用并查集解决，但 $n^2$ 太慢了，于是就想到了整体二分。

我先是用了一个普通的并查集，结果发现每次都要初始化一遍，T 飞了。

后来想着可以支持删除，就不能路径压缩了（还是T飞），我了解到了一个黑科技，按秩合并。

我们合并两棵树的时候，我们把树高小的挂在树高大的下面，这样就能把树高控制在log级别。

然后我们加边的时候，用栈记录合并的两个节点，分完之后，再从栈中一个个地取出来恢复原样就好了。

到最后一个点的时候我们再把这条边连上，成功AC。

对了，我之前加了这个剪枝：
``` cpp
if(x<y)return;
```
就是说如果区间里没有数就不往下了，但这会导致有些边没有连，就WA了。

## CODE：
```cpp
#include<iostream>
#include<stack>
#include<cstdio>
using namespace std;

int n,m,q,ans[100005];
int siz[100005],fa[100005];
struct Edge{
	int x,y;
}e[100005];
struct Question{
	int x,y,z,id;
}Q[100005],tmp[100005];
stack<Edge> s;

int find(int x){
	if(x==fa[x])return x;
	return find(fa[x]);
}

void solve(int l,int r,int x,int y){
	if(l==r){
		for(int i=x;i<=y;i++)ans[Q[i].id]=l;
		int fx=find(e[l].x),fy=find(e[l].y);
		if(siz[fx]>siz[fy])swap(fx,fy);
		if(fx!=fy)fa[fx]=fy,siz[fy]+=siz[fx];
		return;
	}
	int mid=l+r>>1;
	for(int i=l;i<=mid;i++){
		int fx=find(e[i].x),fy=find(e[i].y);
		if(siz[fx]>siz[fy])swap(fx,fy);
		if(fx!=fy){
			fa[fx]=fy,siz[fy]+=siz[fx];
			s.push((Edge){fx,fy});
		}
	}
	int tot1=x-1,tot2=0;
	for(int i=x,size;i<=y;i++){
		int fx=find(Q[i].x),fy=find(Q[i].y);
		if(fx==fy)size=siz[fx];
		else size=siz[fx]+siz[fy];
		if(size>=Q[i].z)Q[++tot1]=Q[i];
		else tmp[++tot2]=Q[i];
	}
	for(int i=1;i<=tot2;i++)Q[tot1+i]=tmp[i];
	while(!s.empty()){
		Edge e=s.top();s.pop();
		fa[e.x]=e.x,siz[e.y]-=siz[e.x];
	}
	solve(l,mid,x,tot1);
	solve(mid+1,r,tot1+1,y);
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&e[i].x,&e[i].y);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++)siz[i]=1;
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		scanf("%d%d%d",&Q[i].x,&Q[i].y,&Q[i].z);
		Q[i].id=i;
	}
	solve(1,m,1,q);
	for(int i=1;i<=q;i++)
		printf("%d\n",ans[i]);
}
```

---

## 作者：小木虫 (赞：1)

### Preface  
又是一道重构树经典例题。  
### Problem  
一张连通图，$q$ 次询问从两个点 $x$ 和 $y$ 出发，希望经过的点(不重复)数量等于 $z$，经过的边最大编号最小是多少。   
### Solution  
我们看到最大编号最小马上就想到了二分，我们可以二分最大编号，然后看看小于等于该编号的边组成的图中的 $x$ 与 $y$ 的连通点数。只要联通点数大于 $z$ 个就可以。  

现在这个问题转换成了一个连通性问题，我们要维护顺序加边的情况下每张图的联通状态。那么摆在我们面前的有两个选择：可持久化并查集以及 kruksal 重构树。  

很明显重构树是更易于实现的，于是我们建出一棵重构树，然后二分节点。当二分值小于两点 lca 的时候两点连通集没有交，反之两点连通，我们分类讨论，两次二分即可。  

code：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int n,m,q,u[N],v[N];int fa[N];
int sz[N];int f[N];int st[N][21];
int son[N][2];int root,x,y,z;int deep[N];
int find(int x){
	if(fa[x]==x)return x;
	else return fa[x]=find(fa[x]);
}
void merge(int x,int y){fa[find(y)]=find(x);}
void build(){
	for(int i=1;i<=n;i++)sz[i]=1;
	for(int i=1;i<=n+m;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		int x=u[i];int y=v[i];
		if(find(x)==find(y))continue;
		x=find(x);y=find(y);root=i+n;
		sz[i+n]=sz[x]+sz[y];f[x]=f[y]=i+n;
		son[i+n][0]=x,son[i+n][1]=y;
		merge(i+n,x);merge(i+n,y);
	}
} 
void dfs(int x){
//	cout<<x<<" "<<f[x]<<endl;
	st[x][0]=f[x];deep[x]=deep[f[x]]+1;
	for(int i=1;i<=20;i++)st[x][i]=st[st[x][i-1]][i-1];
	if(son[x][0])dfs(son[x][0]);
	if(son[x][1])dfs(son[x][1]);
}
int LCA(int x,int y){
	if(deep[x]<deep[y])swap(x,y);
	for(int i=20;i>=0;i--){
		if(deep[st[x][i]]>=deep[y])x=st[x][i];
	}
	if(x==y)return x;
	for(int i=20;i>=0;i--){
		if(st[x][i]!=st[y][i])
			x=st[x][i],y=st[y][i];
	}
	return st[x][0];
}
int res;
int check(int x,int y,int bas){
	//cout<<x<<" "<<y<<" "<<bas<<" "<<z<<endl; 
	for(int i=20;i>=0;i--){
		if((st[x][i]<bas||bas==0)&&st[x][i]!=0&&(1<<i)<=y){
			y-=(1<<i);x=st[x][i];
		}
	}res=x;
	if(y!=0)return -1;
	if(sz[x]>=z)return 1;
	else return 0;
}
int bin(int x){
	int l=0;int r=m;
	while(l<r){
		int mid=(l+r)/2;
		int c=check(x,mid,0);
		if(c==1)r=mid;
		if(c==-1)r=mid-1;
		if(c==0)l=mid+1;
	}
	if(check(x,l,0)!=1)return 1e9;
	//cout<<x<<" "<<l<<" "<<res-n<<endl;
	return res-n;
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		cin>>u[i]>>v[i];
	build();dfs(root);
	cin>>q;
	while(q--){
		cin>>x>>y>>z;int lca=LCA(x,y);int ans=1e9;
		ans=min(ans,bin(lca));int l=n+1;int r=lca;
		while(l<r){
			int mid=(l+r)/2;int sum=0;
			//cout<<l<<" "<<r<<endl;
			check(x,1e9,mid);sum+=sz[res];
			check(y,1e9,mid);sum+=sz[res];
			if(sum>=z)r=mid,ans=min(ans,mid-1-n);
			else l=mid+1;
		}int sum=0;
		check(x,1e9,l);sum+=sz[res];
		check(y,1e9,l);sum+=sz[res];
		if(sum>=z)ans=min(ans,l-1-n);
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：Demoe (赞：1)

[$\large\text{题目传送门}$](https://www.luogu.com.cn/problem/AT1998)

## $\text{Description}$

- 给定一张连通图，有 $q$ 次询问，每次询问给定两点 $x$ 和 $y$，当从 $x$ 和 $y$ 出发到达的点集大小为 $z$ 时，求最大边权最小值。

## $\text{Solution}$

最小瓶颈，容易想到 Kruskal 重构树。

考虑 Kruskal 重构树有性质：

> 原图中两个点之间的所有简单路径上最大边权的最小值 = 最小生成树上两个点之间的简单路径上的最大值 = Kruskal 重构树上两点之间的 LCA 的权值。
>——OI WIKI

那么即到点 $x$ 的简单路径上最大边权的最小值不超过 $val$ 的所有点均在 Kruskal 重构树上的某一棵子树内，且恰好为该子树的所有叶子节点。

我们再来看这道题。

对于一个点 $x$，由如上性质，我们可以知道当最大边权为 $k$ 时点集大小。

同样的对于两个点我们也可以类推，考虑两个子树相不相同，不同相加，相同取一个即可。

那么我们就可以二分答案。

时间复杂度 $O(q\log V\log n)$

## $\text{Code}$

```cpp
const int N=2e5+5,M=8e5+5;
int T,n,m,tot,hd[N],Q,f[N<<1][20];
struct edge{int t,nxt;}es[M];
int fa[N],siz[N];
inline int found(int x){return fa[x]==x?x:fa[x]=found(fa[x]);}
inline void merge(int x,int y){
	int fx=found(x),fy=found(y);
	if(siz[fx]<siz[fy]) swap(fx,fy);
	fa[fy]=fx;siz[fx]+=siz[fy];siz[fy]=0;
}

int cnte,cnt,val[N<<1],sz[N<<1];
struct Edge{int u,v,w;}e[M];
struct EDGE{int t,nxt;}E[N<<3];
inline void add(int x,int y,int z){es[++tot]=(edge){y,hd[x]};hd[x]=tot;e[tot]=(Edge){x,y,z};}
inline void Add(int x,int y){E[++cnte]=(EDGE){y,hd[x]};hd[x]=cnte;}
inline bool cmp(Edge x,Edge y){return x.w<y.w;}
inline void kruscal(){
	cnt=n;
	for(re i=1;i<=(n<<1);++i) fa[i]=i,siz[i]=1,hd[i]=0;
	sort(e+1,e+tot+1,cmp);
	for(re i=1;i<=tot;++i)
		if(found(e[i].u)^found(e[i].v)){
			val[++cnt]=e[i].w;
			Add(found(e[i].u),cnt);Add(cnt,found(e[i].u));Add(found(e[i].v),cnt);Add(cnt,found(e[i].v));
			fa[found(e[i].u)]=fa[found(e[i].v)]=cnt;
		}
}

inline void dfs(int x,int fa){
	f[x][0]=fa;sz[x]=(x<=n);
	for(re i=hd[x];i;i=E[i].nxt)
		if(E[i].t^fa) dfs(E[i].t,x),sz[x]+=sz[E[i].t];
}

inline bool check(int x,int y,int z,int k){
	for(re i=19;i>=0;--i)
		if(f[x][i]&&(f[x][i]<=n||val[f[x][i]]<=k)) x=f[x][i];
	for(re i=19;i>=0;--i)
		if(f[y][i]&&(f[y][i]<=n||val[f[y][i]]<=k)) y=f[y][i];
	return x==y?sz[x]>=z:sz[x]+sz[y]>=z;
}

// ---------- Kruskal ---------- //

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	rd(n);rd(m);
	for(re i=1;i<=m;++i){int x,y;rd(x);rd(y);add(x,y,i);add(y,x,i);}
	kruscal();dfs(cnt,0);
	for(re s=1;s<=19;++s)
		for(re i=1;i<=cnt;++i) f[i][s]=f[f[i][s-1]][s-1];
	rd(Q);
	for(re i=1;i<=Q;++i){
		int x,y,z;rd(x);rd(y);rd(z);
		int l=1,r=m;
		#define mid ((l+r)>>1)
		while(l<=r){
			if(check(x,y,z,mid)) r=mid-1;
			else l=mid+1;
		}
		wr(l);puts("");
	}
	return 0;
}

// ---------- Main ---------- //
```

---

## 作者：UnyieldingTrilobite (赞：0)

**前置说明：本题解时间复杂度为 $O(m\log^2 n+q\log^3n)$，空间复杂度为 $O(n\log n)$，在线，属于较劣解，更好的解法可以去看其他题解。**

这里是一种很暴力的解法。

看到这个最大值最小，很容易想到利用二分解决。只留下前若干条边，那么我们 $x,y$ 能走到 $z$ 个点就等价于是 $x,y$ 在新图上的连通块的并的大小$\ge k$。容易想到使用并查集。然后我们意识到给这个并查集加个可持久化就做完了。

优点是真的很好想啊，是属于那种可以看完题秒出的解法……然后代码也全是板子而且巨大好写，而且还强制在线少了很多整体二分的离线处理。但是题解区的神仙们似乎没~~提到~~（经评论区指正）写它？在实战中这实际上是个性价比巨大高的玩意啊，美滋滋。

代码（可持久化并查集的写法因人而异，我这里的写法是并查集每个节点维护的父亲指针，当对应节点是所在连通块的根时转为维护集合大小的相反数。`findf` 函数返回连通块根和大小打包起来的一个 `pair`）：

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e5 + 9;
struct {
  int val;
  int l, r;
} tr[N * 40];
int rt[N], tot, n, m, q;
int build(int L, int R) {
  if (L == R) return tr[++tot].val = -1, tot;
  int mid = (L + R) >> 1, l = build(L, mid), r = build(mid + 1, R);
  return tr[++tot].l = l, tr[tot].r = r, tot;
}
int update(int tcop, int pos, int val, int L, int R) {
  if (pos < L || pos > R) return tcop;
  if (L == R) return tr[++tot].val = val, tot;
  int mid = (L + R) >> 1, l = update(tr[tcop].l, pos, val, L, mid),
      r = update(tr[tcop].r, pos, val, mid + 1, R);
  return tr[++tot].l = l, tr[tot].r = r, tot;
}
int query(int now, int pos) {
  int L = 1, R = n;
  while (L < R) {
    if (int mid = (L + R) >> 1; pos <= mid)
      R = mid, now = tr[now].l;
    else
      L = mid + 1, now = tr[now].r;
  }
  return tr[now].val;
}
pair<int, int> findf(int now, int x) {
  while (true) {
    int nx = query(now, x);
    if (nx < 0) return {x, -nx};
    x = nx;
  }
  return {0, 0};
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n >> m, rt[0] = build(1, n);
  for (int a, b, i = 1; i <= m; ++i) {
    rt[i] = rt[i - 1];
    cin >> a >> b;
    auto [fa, sa] = findf(rt[i], a);
    auto [fb, sb] = findf(rt[i], b);
    if (fa == fb) continue;
    if (sa > sb) swap(fa, fb), swap(sa, sb);
    rt[i] = update(rt[i], fa, fb, 1, n);
    rt[i] = update(rt[i], fb, -(sa + sb), 1, n);
  }
  for (cin >> q; q; --q) {
    int x, y, z;
    cin >> x >> y >> z;
    int L = 1, R = m, ans = 0;
    while (L <= R) {
      int mid = (L + R) >> 1;
      auto [fa, sa] = findf(rt[mid], x);
      auto [fb, sb] = findf(rt[mid], y);
      if ((fa == fb ? sa : sa + sb) >= z)
        ans = mid, R = mid - 1;
      else
        L = mid + 1;
    }
    cout << ans << '\n';
  }
  return cout.flush(), 0;
}
```

---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15877040.html)

# 题目大意

一张连通图，$q$ 次询问从两个点 $x$ 和 $y$ 出发，希望经过的点(不重复)数量等于 $z$，经过的边最大编号最小是多少。

# 题目分析

## 什么是 $\rm Kruskal$ 重构树

从下面的例子入手：

![](https://cdn.luogu.com.cn/upload/image_hosting/190404v9.png)

-----------
$\rm Kruskal$ 最小生成树算法都知道吧 $\verb!qwq!$，该例最小生成树为：

![](https://cdn.luogu.com.cn/upload/image_hosting/s289duoo.png)

我们按照 $\rm Kruskal$ 的方式建树，设要连接的边为 $(u,v)$，通过并查集可求得 $u$ 的祖先节点为 $x$，$v$ 的祖先节点为 $y$。

若 $x\neq y$，则新建一个节点 $z$ 作为 $x,y$ 的父亲来合并 $x,y$，$z$ 的点权为边 $(x,y)$ 的长度。

最后我们建出来了一棵二叉树，具体长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/3lekyexq.png)

这棵树拥有以下性质：

+ 叶子节点都是构成最小生成树的节点。

+ 生成树中有 $n$ 个节点，会产生 $n-1$ 个含有点权的节点，共 $n+n-1=2\cdot n-1$ 个节点。

+ 按最小生成树重构的重构树是大根堆，按最大生成树重构的重构树是小根堆。

+ 按最小生成树重构的重构树中任意两点 $a,b$ 的路径中的最大边权为它们 $\operatorname{LCA}(a,b)$ 的点权，也是 $a,b$ 路径中最大边权的最小值，按最大生成树重构的重构树中任意两点 $a,b$ 的路径中的最小边权为它们 $\operatorname{LCA}(a,b)$ 的点权，也是 $a,b$ 路径中最小边权的最大值。

------------
模板代码：

```cpp
namespace ex_Kruskal{
	// 注意数组开两倍! 
	
	int nowidx,idx;
	inline bool cmp1(Node x,Node y) { // 按最小生成树重构的重构树
		return x.w < y.w;
	}
	inline bool cmp2(Node x,Node y) { // 按最大生成树重构的重构树
		return x.w > y.w;
	}
	inline void add(int u,int v) {
		gra[++ idx].v = v,gra[idx].nxt = head[u];
		head[u] = idx;
	}
	
	inline void Kruskal() {
		for (register int i = 1;i <= n * 2 - 1; ++ i) {
			fa[i] = i;
		}
		sort (node + 1,node + m + 1,ex_Kruskal::cmp);
		
		nowidx = n;
		for (register int i = 1;i <= m; ++ i) {
			int x = getf(node[i].u),y = getf(node[i].v);
			if (x != y) {
				val[++ nowidx] = node[i].w;//存储当前节点的点权
				fa[x] = fa[y] = nowidx;
				
				add(nowidx,x),add(nowidx,y);
			}
		}
	}
}
```

## 应用

本题我们可以二分编号（显然满足单调性），对于询问 $x,y$，我们倍增向上跳到点权大于当前二分值的位置，然后再判断此时 $x,y$ 跳到的节点 $x',y'$ 的子树中的叶子节点数之和是否达到了 $z$。

如果没有达到 $z$，说明经过的点的数量少了，应该调大一点，即 $l\gets mid+1$；如果超过了 $z$，说明应该调小一点，即 $r\gets mid-1$；如果等于 $z$，那么此时的 $mid$ 即为答案。

# 代码

```cpp
//2022/2/8

//2022/2/9

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <cstdio>

#include <climits>//need "INT_MAX","INT_MIN"

#include <cstring>//need "memset"

#include <algorithm>

#define enter() putchar(10)

#define debug(c,que) cerr<<#c<<" = "<<c<<que

#define cek(c) puts(c)

#define blow(arr,st,ed,w) for(register int i=(st);i<=(ed);i++)cout<<arr[i]<<w;

#define speed_up() cin.tie(0),cout.tie(0)

#define endl "\n"

#define Input_Int(n,a) for(register int i=1;i<=n;i++)scanf("%d",a+i);

#define Input_Long(n,a) for(register long long i=1;i<=n;i++)scanf("%lld",a+i);

#define mst(a,k) memset(a,k,sizeof(a))

namespace Newstd
{
	inline int read()
	{
		int x=0,k=1;
		char ch=getchar();
		while(ch<'0' || ch>'9')
		{
			if(ch=='-')
			{
				k=-1;
			}
			ch=getchar();
		}
		while(ch>='0' && ch<='9')
		{
			x=(x<<1)+(x<<3)+ch-'0';
			ch=getchar();
		}
		return x*k;
	}
	inline void write(int x)
	{
		if(x<0)
		{
			putchar('-');
			x=-x;
		}
		if(x>9)
		{
			write(x/10);
		}
		putchar(x%10+'0');
	}
}

using namespace Newstd;

using namespace std;

const int ma=1e5+5;

struct Gragh
{
	int v;
	
	int nxt;
};

Gragh gra[ma<<1];

int head[ma<<1],fa[ma<<1],val[ma<<1],sons[ma<<1];

int fath[ma<<1][21];

int n,m,q;

int nowidx,idx;

inline void add(int u,int v)
{
	gra[++idx].v=v;
	
	gra[idx].nxt=head[u];
	
	head[u]=idx;
}

inline void dfs(int now,int dad)
{
	fath[now][0]=dad;
	
	for(register int i=1;i<=20;i++)
	{
		fath[now][i]=fath[fath[now][i-1]][i-1];
	}
	
	if(head[now]==0)
	{
		sons[now]=1;
		
		return;
	}
	
	for(register int i=head[now];i;i=gra[i].nxt)
	{
		int v=gra[i].v;
		
		if(v!=dad)
		{
			dfs(v,now);
			
			sons[now]+=sons[v];
		}
	}
}

namespace dsu
{
	inline int getf(int x)
	{
		return fa[x]==x?x:fa[x]=getf(fa[x]);
	}
}

namespace ex_Kruskal
{
	inline void Kruskal()
	{
		for(register int i=1;i<=n*2-1;i++)
		{
			fa[i]=i;
		}

		val[0]=INT_MAX;
		
		nowidx=n;
		
		for(register int i=1;i<=m;i++)
		{
			int u=read(),v=read();

			int x=dsu::getf(u),y=dsu::getf(v);
			
			if(x!=y)
			{
				val[++nowidx]=i;
				
				fa[x]=fa[y]=nowidx;
				
				add(nowidx,x),add(nowidx,y);
			}
		}
	}
}

namespace bs
{
	inline bool check(int now,int x,int y,int num)
	{
		for(register int i=20;i>=0;i--)
		{
			if(val[fath[x][i]]<=now)
			{
				x=fath[x][i];
			}
			
			if(val[fath[y][i]]<=now)
			{
				y=fath[y][i];
			}
		}
		
		if(x==y)
		{
			return sons[x]<num;
		}
		
		return sons[x]+sons[y]<num;
	}
}

int main(void)
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif

	n=read(),m=read();
	
	ex_Kruskal::Kruskal();
	
	dfs(nowidx,0);
	
	q=read();
	
	while(q--)
	{
		int u=read(),v=read(),w=read();
		
		int l=1,r=m;
		
		int ans;
		
		while(l<=r)
		{
			int mid=l+r>>1;
			
			if(bs::check(mid,u,v,w)==true)
			{
				l=mid+1;
			}
			
			else
			{
				r=mid-1;
				
				ans=mid;
			}
		}
		
		write(ans);
		
		enter();
	}
	
	return 0;
}
```

---

## 作者：Mobius127 (赞：0)

[题传](https://www.luogu.com.cn/problem/AT1998)

~~感谢这题让我想起来我还学过整体二分~~

一开始读错题意了，以为 $x, y$ 要联通。。

题目要求最大值最小，答案显然具有单调性。

考虑直接二分这个值 $mid$，显然就是一张前 $mid$ 条边所形成的的连通图，$x, y$ 所在连通块大小之和是否超过 $z$（如果共块只用算一个），考虑使用并查集暴力合并，那么单次复杂度就是 $O(n \alpha(n) \log m)$。

但是这里有 $m$ 次询问，显然就是整体二分了，标准板子不多说，只是询问的时候若询问左端点 $>$ 右端点仍要递归下去，我们需要把前面的边全部加上。

考虑到我们在整体二分时需要把并查集还原，为了保证复杂度只与 $r-l$ 相关，所以使用可撤销并查集，不能路径压缩，复杂度 $O(m \log n \log m)$。

### Code：

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cctype>
#include <stack>
using namespace std;
typedef long long ll;
const int INF=0x3f3f3f3f;
const int mo=1e9+7;
typedef pair <int, int> PI;
inline int read(){
	char ch=getchar();int x=0, f=1;
	while(!isdigit(ch)){if(ch=='-') f=-1; ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
const int N=1e5+5;
int n, m, q;
struct query{int x, y, z, id;}Q[N], lq[N], rq[N];
struct Edge{int x, y;}d[N];
int ans[N];
namespace Dsu{
	int f[N], siz[N];
	stack < PI > rub;
	void Init(int n){
		for(int i=1; i<=n; i++)
			f[i]=i, siz[i]=1;
		return ;
	}
	int find(int x){
		while(x!=f[x]) x=f[x];
		return x;
	}
	bool merge(int x, int y, bool flg){
		//合并 x, y 所在连通块，并返回原来是否同块 
		x=find(x), y=find(y);
		if(x==y) return 1;
		if(siz[x]<siz[y]) swap(x, y);
		if(flg) rub.push((PI){x, y});
		f[y]=x;siz[x]+=siz[y];
		return 0;
	}
	void deleet(){
		int x=rub.top().first, y=rub.top().second;
		f[y]=y, siz[x]-=siz[y];rub.pop();
	}
	void Clear(){while(!rub.empty()) deleet();}
}
void solve(int L, int R, int ql, int qr){
	if(L==R){
		for(int i=ql; i<=qr; i++) ans[Q[i].id]=L&R;
		Dsu :: merge(d[L&R].x, d[L&R].y, 0);
		return ;
	}
	int mid=L+R>>1;
	for(int i=L; i<=mid; i++) 
		Dsu :: merge(d[i].x, d[i].y, 1);
	int lt=0, rt=0;
	for(int i=ql; i<=qr; i++){
		int x=Dsu :: find(Q[i].x), y=Dsu :: find(Q[i].y);
		int Now=Dsu :: siz[x]+(x==y?0:1)*(Dsu :: siz[y]);
		if(Now>=Q[i].z) lq[++lt]=Q[i];
		else rq[++rt]=Q[i];
	}
	for(int i=1; i<=lt; i++) Q[ql+i-1]=lq[i];
	for(int i=1; i<=rt; i++) Q[ql+lt+i-1]=rq[i];
	Dsu :: Clear();
	solve(L, mid, ql, ql+lt-1);
	solve(mid+1, R, ql+lt, qr);
}
signed main(){
	n=read(), m=read();Dsu :: Init(n);
	for(int i=1; i<=m; i++) d[i]=(Edge){read(), read()};
	q=read();
	for(int i=1, x, y, z; i<=q; i++)
		x=read(), y=read(), z=read(),
		Q[i]=(query){x, y, z, i};
	solve(1, m, 1, q);
	for(int i=1; i<=q; i++) printf("%d\n", ans[i]);
	return 0;
}
```



---

