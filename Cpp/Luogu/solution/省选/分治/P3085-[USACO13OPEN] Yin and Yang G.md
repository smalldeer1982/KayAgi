# [USACO13OPEN] Yin and Yang G

## 题目描述

Farmer John is planning his morning walk on the farm. The farm is structured like a tree: it has N barns (1 <= N <= 100,000) which are connected by N-1 edges such that he can reach any barn from any other. Farmer John wants to choose a path which starts and ends at two different barns, such that he does not traverse any edge twice. He worries that his path might be a little long, so he also wants to choose another "rest stop" barn located on this path (which is distinct from the start or the end).

Along each edge is a herd of cows, either of the Charcolais (white hair) or the Angus (black hair) variety. Being the wise man that he is, Farmer John wants to balance the forces of yin and yang that weigh upon his walk. To do so, he wishes to choose a path such that he will pass by an equal number of Charcolais herds and Angus herds-- both on the way from the start to his rest stop, and on the way from the rest stop to the end.

Farmer John is curious how many different paths he can choose that are "balanced" as described above.  Two paths are different only if they consist of different sets of edges; a path should be counted only once even if there are multiple valid "rest stop" locations along the path that make it balanced.

Please help determine the number of paths Farmer John can choose!

给出一棵n个点的树，每条边为黑色或白色。问满足以下条件的路径条数：路径上存在一个不是端点的点，使得两端点到该点的路径上两种颜色的边数都相等。


## 说明/提示

There are 7 barns and 6 edges. The edges from 1 to 2, 2 to 4 and 2 to 5 have Charcolais herds along them.


No path of length 2 can have a suitable rest stop on it, so we can only consider paths of length 4. The only path that has a suitable rest stop is 3-1-2-5-7, with a rest stop at 2.


## 样例 #1

### 输入

```
7 
1 2 0 
3 1 1 
2 4 0 
5 2 0 
6 3 1 
5 7 1 
```

### 输出

```
1 
```

# 题解

## 作者：FlashHu (赞：14)

### 闲话

偶然翻到一道没有题解的~~淀粉质~~，想证明一下自己是真的弱

然而ZSYC(字符串组合)早就切了

然后证明成功了，WA到怀疑人生，只好借着ZSY的代码拍，拍了几万组就出来了。。。

## 思路

是人都能想到的：路径统计，点分治跑不了了。

然而这个统计有些麻烦。。。

首先别看错题，是中间的一个点到两个端点的两条路径都要满足黑白相等。（因为蒟蒻就看错了）

显然，我们每次要统计经过重心的路径，但是这个中点不一定会在重心。于是，必须要更一般化地统计了。

容易想到的是差分。记$d_x$为$x$到重心路径上黑白个数的差，可以改一下边权变成$1$和$-1$，更好实现。

这时候，我们已经可以做到统计黑白个数相等的路径了，一对差分值为$d$和$-d$的路径就可以产生贡献。

但是，题目要两条子路径都黑白相等啊！再想想，假设有两个点$x,y,d_x=-d_y$，那么是不是只有在$x$的祖先中存在$z$且$d_z=-d_y$，或者在$y$的祖先中存在$z$且$d_x=-d_z$，路径$x-y$才能贡献答案？

这也就是说，我们选择的中点$z$的$d$值，需要和$d_x$或$d_y$相等才行。

于是，我们根据每个点是否有祖先的$d$等于它的$d$，分成两类。显然，没有的点只能和有的点算贡献，而有的点可以和两种点都算贡献。开两个桶区别统计一下就好了。

具体实现的话，蒟蒻直接依次枚举重心的子树，先统计一个子树的答案，再把子树的每个点丢进桶里。这样就不用容斥去除不合法情况了。但是要特判一个端点在重心上的路径的贡献。

如何快速判断当前点的属于哪一类？开一个数组$b$统计祖先中每个$d$值出现的次数就可以了（$d$可能是负数，要把所有下标加$n$）。注意回溯的时候要减掉。

注意答案要开long long，注意清空数组。

代码算是很短的了。
```cpp
#include<cstdio>
#include<cstring>
#define RG register
#define R RG int
#define G c=getchar()
const int N=1e5+1,M=N<<1;
int n,rt,mx,mn,he[N],ne[M],to[M],c[M],s[N],m[N],b[M],f[M],g[M];
bool vis[N];
long long ans;
inline void min(R&x,R y){if(x>y)x=y;}
inline void max(R&x,R y){if(x<y)x=y;}
inline int in(){
	RG char G;
	while(c<'-')G;
	R x=c&15;G;
	while(c>'-')x=x*10+(c&15),G;
	return x;
}
void dfs(R x){//求重心
	vis[x]=1;s[x]=1;m[x]=0;
	for(R y,i=he[x];i;i=ne[i])
		if(!vis[y=to[i]])
			dfs(y),s[x]+=s[y],max(m[x],s[y]);
	max(m[x],n-s[x]);
	if(m[rt]>m[x])rt=x;
	vis[x]=0;
}
void upd(R x,R d){//统计答案，f没有g有
	min(mn,d);max(mx,d);
	ans+=g[M-d];//分类贡献
	if(b[d])ans+=f[M-d];
	if(d==N)ans+=b[d]>1;//特判
	vis[x]=1;++b[d];
	for(R i=he[x];i;i=ne[i])
		if(!vis[to[i]])upd(to[i],d+c[i]);
	vis[x]=0;--b[d];//回溯清零
}
void mdf(R x,R d){//修改桶
	++(b[d]?g[d]:f[d]);
	vis[x]=1;++b[d];
	for(R i=he[x];i;i=ne[i])
		if(!vis[to[i]])mdf(to[i],d+c[i]);
	vis[x]=0;--b[d];
}
void div(R x){//分治
	rt=0;dfs(x);x=rt;
	vis[x]=1;b[mn=mx=N]=1;//此处注意初始化
	R t=n,y,i;
	for(i=he[x];i;i=ne[i])
		if(!vis[y=to[i]])
			upd(y,N+c[i]),mdf(y,N+c[i]);
	memset(f+mn,0,(mx-mn+1)<<2);//注意清空
	memset(g+mn,0,(mx-mn+1)<<2);
	for(i=he[x];i;i=ne[i])
		if(!vis[y=to[i]])
			n=s[x]>s[y]?s[y]:t-s[x],div(y);
}
int main(){
	m[0]=1e9;n=in();
	for(R a,b,p=0,i=1;i<n;++i){
		a=in();b=in();
		ne[++p]=he[a];to[he[a]=p]=b;
		ne[++p]=he[b];to[he[b]=p]=a;
		c[p]=c[p-1]=in()?1:-1;//处理边权
	}
	div(1);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：_LAUV_ (赞：5)

统计路径？嗯往点分治上想。

把0和1转化为-1和1，求和完dis为0的路径就是阴阳平衡的路径了。

如果题目没有限制要有中间休息站那就是比较裸的点分治淀粉质题了。

用两个数组 f[dis]和g[dis]。

f[dis]：此时DFS的这棵子树**里**到根距离为dis的路径条数。

g[dis]：此时DFS的这棵子树**外**到根距离为dis的路径条数。

然后里外配对一下统计答案就可以啦~

如果有休息站也没复杂到哪里去。

f[dis][0/1]和g[dis][0/1]多加上一维，表示这条距离为dis的这些路径上是否到之前某个地方距离和为0。

（有点抽象 画个图）

![](https://img2018.cnblogs.com/blog/1397390/201903/1397390-20190328173310290-768892976.jpg)

那这时中间的那个点就可以作为中间0点了上面dis的部分再和子树外的路径配对即可。

这样就可以完美统计出答案了。

代码~ [博客里查看~](https://www.cnblogs.com/HLAUV/p/10616536.html)


```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>

#define For(i,a,b) for(register int i=a;i<=b;++i)
#define Dwn(i,a,b) for(register int i=a;i>=b;--i)
#define Re register
#define Pn putchar('\n')
#define llg long long
#define f(a,b) fx[a+100000][b]
#define g(a,b) gx[a+100000][b]
#define t(a) tx[a+100000]

using namespace std;

const int N=1e5+5;

llg ans=0,fx[N*2][2],gx[N*2][2],tx[N*2];
int head[N],nxt[N*2],v[N*2],w[N*2],siz[N],cnt=1;
int tot,n,m,x,y,opt,vis[N],mx[N],rt;

void read(int &v){
	v=0;
	char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')v=v*10+c-'0',c=getchar();
}
void add(int ux,int vx,int wx){
	cnt++;
	nxt[cnt]=head[ux]; head[ux]=cnt; v[cnt]=vx; w[cnt]=wx;
	cnt++;
	nxt[cnt]=head[vx]; head[vx]=cnt; v[cnt]=ux; w[cnt]=wx;
}

void dfsRT(int x,int fa){
	mx[x]=0; siz[x]=1;
	for(Re int i=head[x];i;i=nxt[i]){
		int vv=v[i]; 
		if(vv==fa||vis[vv])continue;
		dfsRT(vv,x); siz[x]+=siz[vv];
		if(siz[vv]>mx[x])mx[x]=siz[vv];
	}
	if(tot-siz[x]>mx[x])mx[x]=tot-siz[x];
	if(mx[x]<mx[rt])rt=x;
}
int getRT(int x,int fa,int sz){
	rt=0; mx[rt]=2147483600;
    tot=sz; dfsRT(x,fa); return rt;
}

int mxD;
void dfsSV(int x,int dis,int fa){
	if(t(dis))f(dis,0)++;
	else f(dis,1)++;
	mxD=max(mxD,abs(dis));
	t(dis)++;
	for(Re int i=head[x];i;i=nxt[i]){
		int vv=v[i];if(vv==fa||vis[vv])continue;
		dfsSV(vv,dis+w[i],x);
	}
	t(dis)--;
}
void Solve(int x){
	vis[x]=1;
	int maxD=0; 
	for(Re int i=head[x];i;i=nxt[i]){
		int vv=v[i];
		if(vis[vv])continue;
		mxD=0;
		dfsSV(vv,w[i],x);
		maxD=max(mxD,maxD);  
	    ans+=f(0,0);
		For(j,-mxD,mxD){
		    if(j==0)ans+=f(j,1)*g(j,1);
			ans+=f(j,0)*g(-j,0);
			ans+=f(j,0)*g(-j,1);
			ans+=f(j,1)*g(-j,0);
		} 
		For(j,-mxD,mxD){
			g(j,0)+=f(j,0);
			g(j,1)+=f(j,1);
			f(j,0)=f(j,1)=0;
		}
	}
	For(j,-maxD,maxD)g(j,0)=g(j,1)=0;
	for(Re int i=head[x];i;i=nxt[i]){
		int vv=v[i]; if(vis[vv])continue;
		int Nrt=getRT(vv,x,siz[vv]);
		Solve(Nrt);
	}
}
			
int main(){ 
	read(n);
	For(i,1,n-1){
		read(x); read(y); read(opt);
		if(!opt)opt=-1;
		add(x,y,opt);
	}
	int Wrt=getRT(1,0,n); 
	Solve(Wrt);
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：ImmortalWatcher (赞：4)

看题目，树上路径求解，点分治稳了。

因为是点分治，所以我们肯定要在重心上做事情。

## 思路

首先为了更好的计算答案，我们把输入的 $0$ 换成 $-1$，这样如果一个路径的值是 $0$ 的话，那么它肯定阴阳平衡。

然后我们一步一步解决问题。

**第一：如何判断一条路径是否合法？**

我们对于一个点 $i$，设它离重心的距离为 $dis[i]$，对于一条路径的起点和终点 $x$，$y$，$dis[x]=-dis[y]$，那么整条路径就阴阳平衡了。

但是我们还有休息站要考虑，对于 $x$ 的祖先 $z$，$dis[z]=-dis[x]$，或者对于 $y$ 的祖先 $z$，$dis[z]=-dis[y]$，那么 $z$ 就是这条路径的一个合法休息站。

理由显而易见：整条路径平衡，一半路径平衡，那么另一半路径一定也平衡。

所以我们得出结论：

当 $dis[z]=dis[x]$ 或 $dis[y]$ 时，且 $dis[x]=-dis[y]$，那么这就是一条合法的路径。

懂了这里，求答案就容易了。

**第二：如何求答案？**

求答案比较难理解，我们来一段代码：

```cpp
ans+=f[n][0]*(g[n][0]-1);
for (int j=-mxdep;j<=mxdep;j++)
	ans+=f[n+j][1]*g[n-j][1]+f[n+j][0]*g[n-j][1]+f[n+j][1]*g[n-j][0];
```
我们一点一点去理解。

**$g$ 和 $f$ 的定义？**

$g[dis][0]$ 表示对于这个重心，以前遍历过，离重心的距离为 $dis$，找不到休息站的点的个数。

$g[dis][1]$ 表示对于这个重心，以前遍历过，离重心的距离为 $dis$，找得到休息站的点的个数。

$f[dis][0]$ 表示对于这个重心，以前遍历过，离重心的距离为 $dis$，找不到休息站的点的个数。

$f[dis][1]$ 表示对于这个重心，以前遍历过，离重心的距离为 $dis$，找得到休息站的点的个数。

**如何更新 $g$ 和 $f$？**

对于 $g$ 数组，我们直接把 $f$ 数组的值加进去就可以更新了，但是如何更新 $f$ 数组呢？

我们再看一段代码：

```cpp
if (a[dis]) f[dis][1]++;
else f[dis][0]++;
```
之前我们讲过，$f$ 数组是把找得到休息站和找不到休息站的点分类，那如何判断这个点找不找得到休息站呢？

这就要回到我们之前研究过的“如何判断一条路径是否合法”的内容了——如果它的祖先和它的 $dis$ 是相同的，那么它的祖先就可以当休息站，所以我们开一个桶 $a$，记录这个 $dis$ 出现的次数就可以了。

**怎么运用 $g$ 和 $f$ 求答案？**

我们回到代码。

```cpp
ans+=f[n][0]*(g[n][0]-1);
for (int j=-mxdep;j<=mxdep;j++)
	ans+=f[n+j][1]*g[n-j][1]+f[n+j][0]*g[n-j][1]+f[n+j][1]*g[n-j][0];
```
求答案的思路可以分为以下几点：

$1$ 、因为要保证整条路径阴阳平衡，所以两个点的 $dis$ 和要为 $0$。

$2$ 、因为至少要有一个休息站，所以现在找不到休息站的点只能跟以前找得到休息站的点配对，而现在找得到休息站的点可以跟以前任意一种点配对。

$3$ 、$i$ 的范围是多少呢？我们可以记录一个层数 $dep$，重心那层层数为 $0$。那 $i$ 的范围就是 $-dep$ ~ $dep$之间。注意 $i$ 可能是负数，所以我们要把它加上 $n$ 才能当做下标。

$4$ 、还有一种特殊情况，就是当重心为休息站时，它的贡献就是 $f[0][0]*$（$g[0][0]-1$）。因为重心已经是休息站，所以找不到休息站的点也可以配对，同时要排除重心是端点的情况，所以要 $g$ 的个数要减 $1$。

$5$ 、由于数组太大，在换重心继续分治时，数组清空用 $memset$ 会很慢，需要手动清空。

到此为止，求答案就讲完了。

完整代码如下：

```cpp
#include<cstdio>
#define max(x,y) (x>y?x:y)
using namespace std;
struct node{int next,en,last,v;} e[200001];
long long ans;
int a[200001],mxdep,n,m,x,y,z,tot,sum,root,maxs[100001],vis[100001],size[100001],dis[100001],f[200001][2],g[200001][2];
void add(int x,int y,int z)
{
	e[++tot].en=y;
	e[tot].v=z;
	e[tot].next=e[x].last;
	e[x].last=tot;
}
void getroot(int x,int fa) 
{
    maxs[x]=0,size[x]=1;
    for(int i=e[x].last;i;i=e[i].next) 
	{
        if(vis[e[i].en]||e[i].en==fa) continue;
        getroot(e[i].en,x);
        size[x]+=size[e[i].en];
        maxs[x]=max(maxs[x],size[e[i].en]);
    }
    maxs[x]=max(maxs[x],sum-size[x]);
    if(maxs[x]<maxs[root]) root=x;
}
void change(int x,int fa,int dis,int dep) 
{
    mxdep=max(mxdep,dep);
    if (a[dis]) f[dis][1]++;
    else f[dis][0]++;
    a[dis]++;
    for (int i=e[x].last;i;i=e[i].next)
    {
    	if (e[i].en==fa||vis[e[i].en]) continue;
    	change(e[i].en,x,dis+e[i].v,dep+1);
	}
    a[dis]--;
}
void getans(int x) 
{
    int mx=0;
    g[n][0]=1;
    for (int i=e[x].last;i;i=e[i].next)
    {
    	if (vis[e[i].en]) continue;
    	mxdep=1;
    	change(e[i].en,x,n+e[i].v,1);
    	mx=max(mx,mxdep);
    	ans+=f[n][0]*(g[n][0]-1);
    	for (int j=-mxdep;j<=mxdep;j++)
    		ans+=f[n+j][1]*g[n-j][1]+f[n+j][0]*g[n-j][1]+f[n+j][1]*g[n-j][0];
    	for (int j=n-mxdep;j<=n+mxdep;j++)
    	{
    		g[j][0]+=f[j][0];
    		g[j][1]+=f[j][1];
    		f[j][0]=f[j][1]=0;
		}
	}
    for (int i=n-mx;i<=n+mx;i++) g[i][0]=g[i][1]=0;
}
void solve(int x) 
{
    vis[x]=1;
    getans(x);
    for(int i=e[x].last;i;i=e[i].next) 
	{
        if(vis[e[i].en]) continue;
        root=0,sum=size[e[i].en];
        getroot(e[i].en,0);
        solve(root);
    }
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		if (!z) z=-1;
		add(x,y,z);
		add(y,x,z);
	}
	maxs[root]=sum=n;
	getroot(1,0);
	solve(1);
	printf("%lld",ans);
	return 0;
}
```




---

## 作者：Reanap (赞：2)

我们考虑使用点分治，先找到一条路径，然后判断它是否可行？

经过研究，我们发现一条路径是可行解，当且仅当它是多条平衡路径合并而来的，于是我们把以根节点出发的路径分为两种，一种是包含有平衡路径的路径，它的贡献就是在其他子树中能够与它组成平衡路径的路径数目。

另一种是不包含有平衡路径的路径，则它的贡献就是其他子树的路径中能与它组成平衡路径且包含有平衡路径的路径数。

最后特判一下以根节点为端点的可行解。

以上这些路径都可以用map维护快速求解。

细节见代码：

```cpp
#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
void read(int &x){ 
	int f=1;x=0;char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
	x*=f;
}
const int MAXN = 1e5 + 5;
int head[MAXN] , to[MAXN << 1] , nxt[MAXN << 1] , cnt , edge[MAXN << 1];
void add(int u , int v , int w) {nxt[++cnt] = head[u];head[u] = cnt;to[cnt] = v;edge[cnt] = w;}
int n , siz[MAXN] , rt , _max , vis[MAXN];
LL ans;
void get_siz(int x , int fa) {
	siz[x] = 1;
	for (int i = head[x]; i; i = nxt[i]) {
		if(to[i] == fa || vis[to[i]]) continue;
		get_siz(to[i] , x);
		siz[x] += siz[to[i]];
	}
}
void get_root(int x , int fa , int num) {
	int res = 0;
	for (int i = head[x]; i; i = nxt[i]) {
		if(to[i] == fa || vis[to[i]]) continue;
		get_root(to[i] , x , num);
		if(siz[to[i]] > res) res = siz[to[i]];
	}
	if(num - siz[x] > res) res = num - siz[x];
	if(res < _max) _max = res , rt = x;
}
map <int , int> M[2];
map <int , int> C;
struct node {
	int val , ty;
}s[MAXN];
int tot;
void dfs(int x , int fa , int val) {
	s[++tot].val = val;
	if(C[val]) s[tot].ty = 1; //C有值则它包含有平衡路径
	else s[tot].ty = 0;
	if(val == 0 && C[val] > 1) ans ++;//特判与根节点合法的路径
	C[val] ++; 
	for (int i = head[x]; i; i = nxt[i]) {
		if(to[i] == fa || vis[to[i]]) continue;
		dfs(to[i] , x , val + edge[i]);
	}
	C[val] --;
}
void work(int x) {
	get_siz(x , 0);
	rt = 0 , _max = 1e9;
	get_root(x , 0 , siz[x]);
	x = rt;vis[x] = 1;
	C[0] = 1; 
	M[0].clear();M[1].clear();
	for (int i = head[x]; i; i = nxt[i]) {
		if(vis[to[i]]) continue;
		tot = 0;
		dfs(to[i] , x , edge[i]);
		for (int j = 1; j <= tot; ++j) {
			if(s[j].ty == 0) ans += M[1][-s[j].val];
        		//当不包含平衡路径时在以找到的路径中查找包含平衡路径且能与自己组成平衡路径。
			else ans += M[0][-s[j].val] + M[1][-s[j].val];
        		//当包含时，能组成平衡路径中包不包含都可以
		}
		for (int j = 1; j <= tot; ++j) M[s[j].ty][s[j].val] ++;
	}
	for (int i = head[x]; i; i = nxt[i]) {
		if(vis[to[i]]) continue;
		work(to[i]);
	}
}
int main() {
	read(n);
	for (int i = 1; i < n; ++i) {
		int u , v , w;
		read(u);read(v);read(w);
		if(w == 0) w = -1;//这样做后，当一条路径是平衡路径则它的权值和为0
		add(u , v , w);add(v , u , w);
	}
	work(1);
	printf("%lld" , ans);
	return 0;
} 
```

---

## 作者：Iota2029 (赞：2)

这道题也是很久才A了。其实这道题十分的简单。

很明显这是以到点分治的题目。虽然是统计路径，但是仍然。。。怎么有个休息站？

于是对于每个点戳一个标记bz，代表从分治到的根到当前节点有没有休息站。这个很简单，其实就是看从分治到的根到当前节点有没有一个节点和它的d相同（d代表距离，我们认为1为1,0为-1）。

然后对于统计路径，其实就是用两个桶，一个代表有休息站的，一个代表没有休息的，长度为dx的分别有多少条。

最后答案的统计其实就是枚举每一个点，然后匹配从分治根到那个节点的路径。注意匹配的是相反数。然后呢，如果此路径为有休息站的，那么它可以匹配有休息站的或没有休息站的，否则只能匹配有休息站的。

这道题的细节比较多，然后自己写代码的时候不怎么专心，导致由很多细节漏掉了。

然后呢，就没了。以后写代码是要理清思路，认真写。

代码：
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 200010
#define INF 0x3f3f3f3f
using namespace std;

int max_s[N], sz[N], dis[N], d[N];
int vis[N], rt, sum;
struct Edge {int to, nxt, val;}g[N * 2];
int last[N], cn = 0;
int n, sz_x, len;
long long ans;
int t_y[2][N], t_n[2][N]; 
int cnt[2][N], bz[N], z, Z;
void get_rt(int x,int fa)
{
	sz[x] = 1, max_s[x] = 0;
	for (int i = last[x];i;i = g[i].nxt)
		if (g[i].to != fa && !vis[g[i].to])
			get_rt(g[i].to, x), sz[x] += sz[g[i].to], max_s[x] = max(max_s[x], sz[g[i].to]);
	max_s[x] = max(max_s[x], sum - sz[x]);
	if (max_s[x] < max_s[rt]) rt = x;
}
void get_dis(int x,int fa) 
{
	if (x != rt)
	{
		int xx = d[x];
		if (xx < 0) bz[x] = (cnt[0][-xx] > 1 ? 1 : 0);
		else if (xx > 0) bz[x] = (cnt[1][xx] > 1 ? 1 : 0);
		else bz[x] = z > 1 ? 1 : 0;
		if (bz[x]) {if (xx > 0) ++t_y[1][xx]; else if (xx < 0) ++t_y[0][-xx]; else ++Z;}
		else {if (xx > 0) ++t_n[1][xx]; else if (xx < 0) ++t_n[0][-xx]; else ++Z;}
	}
	for (int i = last[x];i;i = g[i].nxt)
		if (g[i].to != fa && !vis[g[i].to])
		{
			d[g[i].to] = d[x] + g[i].val;
			int xx = d[g[i].to];
			if (xx > 0) ++cnt[1][xx]; else if (xx < 0) ++cnt[0][-xx]; else ++z;
			get_dis(g[i].to, x);
			if (xx > 0) --cnt[1][xx]; else if (xx < 0) --cnt[0][-xx]; else --z;
		}
}
void Dfs(int x,int fa)
{
	int xx = d[x];
	if  (bz[x]) {if (xx > 0) --t_y[1][xx]; else if (xx < 0) --t_y[0][-xx]; else --Z;}
	else {if (xx > 0) --t_n[1][xx]; else if (xx < 0) --t_n[0][-xx]; else --Z;} 
	for (int i = last[x];i;i = g[i].nxt)
		if (g[i].to != fa && !vis[g[i].to])
			Dfs(g[i].to, x); 
}
void Dfs2(int x,int fa)
{
	int xx = d[x];
	if (xx > 0) bz[x] && (ans += t_n[0][xx]), ans += t_y[0][xx];
	else if (xx < 0) bz[x] && (ans += t_n[1][-xx]), ans += t_y[1][-xx];
	else ans += Z, bz[x] && ++ans;
	for (int i = last[x];i;i = g[i].nxt)
		if (g[i].to != fa && !vis[g[i].to])
			Dfs2(g[i].to, x);
}
void solve(int rt_x)
{
	d[rt_x] = 0, vis[rt_x] = 1;
	get_dis(rt_x, 0);
	for (int i = last[rt_x];i;i = g[i].nxt)
		if (!vis[g[i].to])
			Dfs(g[i].to, rt_x), Dfs2(g[i].to, rt_x);
	for (int i = last[rt_x];i;i = g[i].nxt)
		if (!vis[g[i].to])
			sum = sz[g[i].to], rt = 0, get_rt(g[i].to, 0), solve(rt);
}
void add(int u,int v,int w) {g[ ++cn] = (Edge){v, last[u], w}, last[u] = cn;}
void Add_Edge(int u,int v,int w) {add(u, v, w), add(v, u, w);}

int main()
{
	scanf("%d", &n); sum = n;
	for (int i = 1, u, v, w;i < n; ++i) 	
		scanf("%d %d %d", &u, &v, &w), w = !w ? -1 : 1, Add_Edge(u, v, w);
	max_s[0] = INF;
	get_rt(1, 0), solve(rt);
	printf("%lld", ans);
	return 0;
}
```
写的有点丑。。。大家不要介意。。。

---

## 作者：SoyTony (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P3085)

本题两个限制条件：整体为黑白颜色个数相同，且路径中存在一点使得分开的两条路径分别黑白颜色个数相同。

不难发现是点分治的题。

可以把边权为 $0$ 的改为 $-1$，就能通过计算链长来判断这个链是否满足条件。

唯一要解决的问题：在普通点分治过程中，我们找到的子树的重心被定义为为两点的最近公共祖先，然而题目中要找的这一点，不一定是子树的重心。换言之，遍历到一个本应为断点的重心时，其所在路径可能不完全在这个子树中。

假设路径 $(u,v)$ 上一点 $p$，使得 $dis(u,p)$ 以及 $dis(p,v)$ 都是 $0$。不难发现 $dis(u,v)=dis(u,p)=dis(p,v)=0$ 时，令 $p$ 为 $(rt,u)$ 上一点，则 $dis(rt,p)=dis(rt,u)-dis(u,p)=dis(rt,u)$。

所以我们要找的就是一条距离相等的“真前缀”，可以用桶解决。

之后按照同样的套路，用 $mark(i,0/1)$ 与 $now(i,0/1)$ 分别记录前面已经遍历的子树和当前子树，长度为 $i$ 的链中有/无与其相等的真前缀的个数。

于是求出最大深度 $maxdep$，在 $[-maxdep,maxdep]$ 中，满足 $now$ 或 $mark$ 有一个存在这样的真前缀即可，也就是：

$$ans=\sum_{i=-maxdep}^{maxdep} now(i,0)\times mark(-i,1)+now(i,1)\times mark(-i,0)+now(i,1)\times mark(-i,1)$$

当然不能忽略重心本身就是断点的情况，也就是 $now(0,0)\times (mark(0,0)-1)$，这里 $mark$ 数值减 $1$ 的原因是初始化中根可以是端点，但不能既是端点又是断点。

转移方程有负数，直接加上 $n$，数组开 $2$ 倍。

```cpp
int n;
ll ans;
struct Tree{
    struct edge{
        int to,nxt,w;
    }e[maxn<<1];
    int head[maxn],cnt;
    inline void add_edge(int u,int v,int w){
        e[++cnt].to=v,e[cnt].nxt=head[u],e[cnt].w=w,head[u]=cnt;
    }
    int rt,siz[maxn],maxsiz[maxn],sumsiz;
    bool vis[maxn];
    void dfs(int u,int f){
        siz[u]=1,maxsiz[u]=0;
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(v==f||vis[v]) continue;
            dfs(v,u);
            siz[u]+=siz[v],maxsiz[u]=max(maxsiz[u],siz[v]);
        }
        maxsiz[u]=max(maxsiz[u],sumsiz-siz[u]);
        if(maxsiz[u]<maxsiz[rt]) rt=u;
    }
    int dis[maxn],dep[maxn],maxdep,tot[maxn<<1];
    ll now[maxn<<1][2],mark[maxn<<1][2];
    void get_dis(int u,int f,int d){
        dep[u]=d,maxdep=max(maxdep,d);
        if(tot[n+dis[u]]) ++now[n+dis[u]][1];
        else ++now[n+dis[u]][0];
        //printf("%d %d %d %d %lld %lld\n",u,f,dis[u],tot[n+dis[u]],now[n+dis[u]][0],now[n+dis[u]][1]);
        ++tot[n+dis[u]];
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to,w=e[i].w;
            if(v==f||vis[v]) continue;
            //cout<<dis[u]<<" "<<w<<endl;
            dis[v]=dis[u]+w;
            get_dis(v,u,d+1);
        }
        --tot[n+dis[u]];
    }
    inline void calc(int u){
        int totdep=1;
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to,w=e[i].w;
            if(vis[v]) continue;
            dis[v]=w,maxdep=1;
            get_dis(v,u,1);
            totdep=max(totdep,maxdep);
            //根作为站点
            ans+=now[n][0]*(mark[n][0]-1);
            //cout<<u<<" "<<v<<" "<<maxdep<<endl;
            for(int j=-maxdep;j<=maxdep;++j){
                //存在一个真前缀即合法
                //printf("%d-> (+,0) %lld (+,1) %lld (-,0) %lld (-,1) %lld\n",j,now[n+j][0],now[n+j][1],mark[n-j][0],mark[n-j][1]);
                ans+=now[n+j][1]*mark[n-j][1]+now[n+j][1]*mark[n-j][0]+now[n+j][0]*mark[n-j][1];
                //printf("**%lld\n",ans);
            }
            for(int j=n-maxdep;j<=n+maxdep;++j){
                mark[j][0]+=now[j][0],mark[j][1]+=now[j][1];
                now[j][0]=0,now[j][1]=0;
            }
        } 
        for(int i=n-totdep;i<=n+totdep;++i) mark[i][0]=mark[i][1]=0;
    }
    void solve(int u){
        vis[u]=1,mark[n][0]=1;
        calc(u);
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(vis[v]) continue;
            rt=0,maxsiz[0]=siz[v],sumsiz=siz[v];
            dfs(v,0);
            solve(rt);
        }
    }
}T;
int main(){
    //freopen("1.in","r",stdin);
    n=read();
    for(int i=1;i<n;++i){
        int u=read(),v=read(),w=read();
        if(!w) w=-1;
        T.add_edge(u,v,w),T.add_edge(v,u,w);
    }
    T.rt=0,T.maxsiz[0]=n,T.sumsiz=n;
    T.dfs(1,0);
    //printf("%d\n",T.rt);
    T.solve(T.rt);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：devout (赞：0)

一道比较好想的淀粉质的题目。

发现是求路径条数，可以考虑点分治。

首先如果不考虑休息站，就是把 $0$ 变成 $-1$，然后统计边权和为 $0$ 的条数。

如果有休息站，考虑在点分治的时候有两种情况，设 $s$ 位于已经搜索过的子树中，$u$ 为当前重心，$t$ 位于新的子树中。

$s-u-t$ 这条路径是合法的，要么在 $s-u$ 上存在一个点 $x$，使得 $s-x$ 的边权和为 $0$，要么在 $u-t$ 上存在一个点 $y$，使得 $y-t$ 的边权和为 $0$，我们记录一下从 $u$ 出发的所有在已经搜索过的子树中的边权和为 $i$，有几条是没有休息站的，有几条是有的，然后点分治的时候顺便统计一下答案就可以了。

因为 $i$ 可能是负数，所以需要值域平移一下。

实现上细节比较多，注意 $u-t$ 这种的路径也要算到答案里面。

剩下的就是套个板子啦（

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=1e5+5;
const int R=1e5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n;
int head[N],cnt;
int p[N],totp,q[N],totq;
int done[N<<1],todo[N<<1],appr[N<<1];
int f[N],siz[N];
int dis[N];
bool vis[N],flag[N];
ll ans;

struct Edge{
	int to,next,w;	
}e[N<<1];

void add(int x,int y,int c){
	e[++cnt]=(Edge){y,head[x],c},head[x]=cnt;	
}

void dfs1(int u,int fa){
	p[++totp]=u;
	siz[u]=1;
	RepG(i,u){
		int v=e[i].to;
		if(v==fa||vis[v])continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		f[u]=max(f[u],siz[v]);	
	}
}

void dfs2(int u,int fa){
	q[++totq]=u;
	if(appr[dis[u]+R])flag[u]=true;
	appr[dis[u]+R]++;
	RepG(i,u){
		int v=e[i].to;
		if(v==fa||vis[v])continue;
		dis[v]=dis[u]+e[i].w;
		dfs2(v,u);	
	}
	appr[dis[u]+R]--;
}

void solve(int u){
	totp=0;
	dfs1(u,0);
	Rep(i,1,totp)f[p[i]]=max(f[p[i]],totp-siz[p[i]]);
	int rt=-1;
	Rep(i,1,totp)if(rt==-1||f[p[i]]<f[rt])rt=p[i];
	Rep(i,1,totp)f[p[i]]=0;
	vis[rt]=true;	
	RepG(i,rt){
		int v=e[i].to;
		if(vis[v])continue;
		totq=0;
		dis[v]=e[i].w;
		dfs2(v,rt);	
		Rep(j,1,totq)
			if(!dis[q[j]]){
				if(flag[q[j]])ans++;
				ans+=todo[R];	
			}
			else if(flag[q[j]])ans+=todo[-dis[q[j]]+R];
			else ans+=done[-dis[q[j]]+R];
		Rep(j,1,totq)
			if(!dis[q[j]])done[R]++,todo[R]++;
			else if(flag[q[j]])todo[dis[q[j]]+R]++,done[dis[q[j]]+R]++;
			else todo[dis[q[j]]+R]++;
	}
	Rep(i,1,totp){
		flag[p[i]]=false;
		todo[dis[p[i]]+R]=done[dis[p[i]]+R]=0; 
	}	
	RepG(i,rt){
		int v=e[i].to;
		if(vis[v])continue;
		solve(v);	
	}
}

int main()
{
	memset(head,-1,sizeof(head));
	read(n);
	Rep(i,1,n-1){
		int x,y,c;
		read(x),read(y),read(c);
		if(!c)c=-1;
		add(x,y,c),add(y,x,c);	
	}
	solve(1);
	printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：Shikita (赞：0)

# 树上路径统计 点分治

点分治是用来解决树上路径问题的一种方法。

在解决树上路径问题时，我们可以选取一点为根，将树转化为有根树，然后考虑经过根的所有路径（有时将两条从根出发的路径连接为一条）。统计完这些路径的答案后，将根节点标记为删除，对剩下的若干棵树进行同样的操作。

每次确认一个根节点后，共有$n$条需要考虑的路径（$n$为当前子树大小）。若将当前根节点删除后，剩下某棵的子树较大，和原树大小相当，继续处理这棵子树时仍然需要与前一过程相当的时间。

最严重的情况，当整棵树是一条链时，每次需要考虑的路径数量是$O(n)$级别的，如果每条路径需要常数时间进行统计，则总时间复杂度为$O(n^2)$

而对于形态随机的树，则远远小于这个级别。

所以我们应该合理选取树的根节点

而树的重心能够很好满足我们的需求

我们定义一棵树的重心为以该点为根时最大子树最小的点。

那么我们每次删除掉当前根节点后，剩余的子树能够保证尽量平衡，这就可以大大减小复杂度

```
//mx[x] 记录的是x的子树中最大的子树大小
inline void getroot(int x,int fa)
{
	size[x]=1,mx[x]=0;
	for(int i=head[x];i;i=e[i].next)
	if(v!=fa&&!vis[v])
	{
		getroot(v,x);
		size[x]+=size[v];
		mx[x]=max(mx[x],size[v]);
	}
	mx[x]=max(mx[x],sum-size[x]);
	if(mx[x]<mx[rt]) rt=x;
}
```

~~我觉得你们自己看代码应该好懂，不解释了~~

那么对于本题，我们将阴阳点分别置为1和-1，求路径上有一个0点且终点为0的路径条数


我们令$g[dis][0/1]$表示之前dfs过的子树中，到根的距离为$dis$的路径数目

$f$数组表示当前正在dfs的子树，到根的距离为$dis$的路径数目

0/1表示其中是否出现过前缀和为0的点。

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
    int x=0;
    char c=getchar();
    bool flag=0;
    while(c<'0'||c>'9') {if(c=='-')flag=1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x+(x<<2)<<1)+ c-'0';c=getchar();}
    return flag?-x:x;
}
const int N=1e5+5;
int n,sum,rt,mxdep;
int vis[N],t[N<<1],mx[N],size[N],dep[N],dis[N];
ll ans,g[N<<1][2],f[N<<1][2];

int head[N],cnt;
struct node{int to,next,w;}e[N<<1];
inline void add(int u,int v,int w)
{
	e[++cnt].to=v,e[cnt].next=head[u],e[cnt].w=w,head[u]=cnt;
	e[++cnt].to=u,e[cnt].next=head[v],e[cnt].w=w,head[v]=cnt;
}
//mx[x] x的最大子树 

#define v e[i].to
inline void getroot(int x,int fa)
{
	size[x]=1,mx[x]=0;
	for(int i=head[x];i;i=e[i].next)
	if(v!=fa&&!vis[v])
	{
		getroot(v,x);
		size[x]+=size[v];
		mx[x]=max(mx[x],size[v]);
	}
	mx[x]=max(mx[x],sum-size[x]);
	if(mx[x]<mx[rt]) rt=x;
}
//找重心 
inline void dfs(int x,int fa)
{
	mxdep=max(mxdep,dep[x]);
	(t[dis[x]])?++f[dis[x]][1]:++f[dis[x]][0];
	++t[dis[x]];
	for(int i=head[x];i;i=e[i].next) if(v!=fa&&!vis[v])
	{
		dep[v]=dep[x]+1;
		dis[v]=dis[x]+e[i].w;
		dfs(v,x);
	}
	--t[dis[x]];
}
inline void solve(int x)
{
	int mx=0;vis[x]=g[n][0]=1;
	for(int i=head[x];i;i=e[i].next) if(!vis[v])
	{
		dis[v]=n+e[i].w;dep[v]=1;mxdep=1;
		dfs(v,0);mx=max(mx,mxdep);
		ans+=(g[n][0]-1)*f[n][0];
		for(int j=-mxdep;j<=mxdep;++j)
		ans+=g[n-j][1]*f[n+j][1]+g[n-j][0]*f[n+j][1]+g[n-j][1]*f[n+j][0];
		for(int j=n-mxdep;j<=n+mxdep;++j)
		{
			g[j][0]+=f[j][0];
			g[j][1]+=f[j][1];
			f[j][0]=f[j][1]=0;
		}
	}
	for(int i=n-mx;i<=n+mx;++i) g[i][0]=g[i][1]=0;
	for(int i=head[x];i;i=e[i].next)
	if(!vis[v])
	{
		sum=size[v];rt=0;getroot(v,0);solve(rt);
	}
}
#undef v
int main()
{
	n=read();
	for(int i=1;i<n;++i)
	{
		int u=read(),v=read(),w=read();
		if(!w) w=-1;
		add(u,v,w);
	}
	sum=mx[0]=n;
	getroot(1,0);
	solve(rt);
	printf("%d\n",ans);
}
```

---

## 作者：asuldb (赞：0)

[题目](https://www.luogu.org/problemnew/show/P4930)

考虑一下把$0$看成$-1$，那么就是找到一条边权和为$0$的路径，且这条路径可以被分成两段，边权和都是$0$

没有第二个限制就是点分裸题了

~~其实有了第二个限制还是点分裸题~~

考虑那个断点肯定会存在于当前分治重心的某一边，或者直接在分治重心上，我们在求每个点到分治重心的距离的时候判断一下上面能否有一个点成为断点就好了

具体做法就是开个桶，判断每个点的祖先是否有一个和它的分治重心的距离相等

之后就把点分成了两类，一类是到分治重心的路径上存在断点，一类是不存在的，显然不存在的只能和存在的拼成路径，同时还要满足距离和加起来为$0$就好了

于是开两个桶分别维护一下就好了

代码

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define LL long long
#define re register
#define maxn 100005
inline int read() {
    char c=getchar();int x=0;while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-48,c=getchar();return x;
}
struct E{int v,nxt,w;}e[maxn<<1];
int n,m,num,now,rt,S;LL ans;
int head[maxn],sum[maxn],mx[maxn],vis[maxn],pre[maxn];
int f[maxn<<1],tax[maxn<<1][2],top[2],st[maxn<<1][2];
inline void add(int x,int y,int z) {e[++num].v=y;e[num].nxt=head[x];head[x]=num;e[num].w=z;}
void getroot(int x,int fa) {
    sum[x]=1,mx[x]=0;
    for(re int i=head[x];i;i=e[i].nxt) {
        if(vis[e[i].v]||e[i].v==fa) continue;
        getroot(e[i].v,x);sum[x]+=sum[e[i].v];
        mx[x]=max(mx[x],sum[e[i].v]);
    }
    mx[x]=max(mx[x],S-sum[x]);
    if(mx[x]<now) rt=x,now=mx[x];
}
void getdis(int x,int fa,int o) {
    pre[x]=pre[fa]+o;
    if(f[pre[x]+n]) {
        st[++top[1]][1]=x;
        if(f[pre[x]+n]>1&&pre[x]==0) ans++;
    }
        else st[++top[0]][0]=x;
    f[pre[x]+n]++;
    for(re int i=head[x];i;i=e[i].nxt) {
        if(vis[e[i].v]||e[i].v==fa) continue;
        getdis(e[i].v,x,e[i].w);
    }
    f[pre[x]+n]--;
}
void clear(int x,int fa) {
    tax[n+pre[x]][0]=tax[n+pre[x]][1]=0;pre[x]=0;
    for(re int i=head[x];i;i=e[i].nxt) {
        if(vis[e[i].v]||e[i].v==fa) continue;
        clear(e[i].v,x);
    }
}
void dfs(int x) {
    vis[x]=1;f[0+n]=1;
    for(re int i=head[x];i;i=e[i].nxt) {
        if(vis[e[i].v]) continue;
        top[0]=top[1]=0;getdis(e[i].v,x,e[i].w);
        for(re int j=1;j<=top[0];j++) 
            ans+=tax[n-pre[st[j][0]]][1];
        for(re int j=1;j<=top[1];j++) 
            ans+=tax[n-pre[st[j][1]]][1]+tax[n-pre[st[j][1]]][0];
        for(re int j=1;j<=top[0];j++) tax[n+pre[st[j][0]]][0]++;
        for(re int j=1;j<=top[1];j++) tax[n+pre[st[j][1]]][1]++;
    }f[0+n]=0;
    for(re int i=head[x];i;i=e[i].nxt) {
        if(vis[e[i].v]) continue;
        clear(e[i].v,x);
    }
    for(re int i=head[x];i;i=e[i].nxt) {
        if(vis[e[i].v]) continue;
        S=sum[e[i].v],now=n,getroot(e[i].v,0),dfs(rt);
    }
}
int main() {
    n=read();
    for(re int x,y,z,i=1;i<n;i++) {
        x=read(),y=read(),z=read();
        if(!z) z=-1;add(x,y,z),add(y,x,z);
    }
    now=n,S=n,getroot(1,0);dfs(rt);
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：daklqw (赞：0)

## 题意
树上，有黑白边  
定义是否“阴阳平衡的”函数$f(u, v)$为：
u 到 v 上所有黑点之和与白点之和是否相等  
求满足以下性质  

1. $f(u, v) == true$
2. 存在$ k \neq u, v $， 使得 $f(u, k) == f(k, v) == true$  

的点对个数  

考虑点分治，现在只需要写出calc函数就行  
因为只要满足条件2， 就能满足条件1，所以就考虑分治中心$c$两边$u, v$的合并  
定义0边权为-1，1边权为1  
从分治中心开始，从上到下开始前缀  
我们发现，两条路径能合并，当且仅当  

1. 两条路径中至少有一条$(c, u)$有至少一个$k \neq c, u$使得$f(u, k) == true$即$val[u] == val[k]$  
2. 两个点处的值互为相反数$val[u] = -val[v]$  

我们考虑条件1，可以按一条链是否有这个k满足来分类  
我们计A[i]为无k的，值为i的个数  
计B[i]为有k的，值为i的个数  
那么统计答案时，一个点u的贡献就是 $A[-f[u]] + B[-f[u]]$

但是累计答案时要注意去重  
所以可以枚举有k的点，然后单独累计A，B，最后再将B中：

1. 自己到自己
2. u -> v 同时一定还会有 v -> u

两种情况去重

现在考虑计算k  
我们发现，只要当它父亲到分治中心的路径上有一个点的值与自己相同，它就是属于B类的  
于是开个数组记录一下  

但是发现，会有B类合并到空的(分治中心到分治中心的路径)，但是有些B类到分治中心的路径上只有分治中心的值是等于B的  
这个时候就会计算多余  
但是执行这个操作同时不能忘记在分治子树去重的时候，也会容斥掉同样的路径  
所以记得要在分治子树的时候特判，这种路径不要算上去，不然相当于什么也没做  

我是不是太弱了，写得那么复杂……

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <assert.h>
using namespace std;
#define MAXN 100010
struct arr {
	int cnt[MAXN << 1];
	inline int & operator [] (const int index) { return cnt[index + MAXN]; }
} A, B, rec;
int n, head[MAXN], nxt[MAXN << 1], to[MAXN << 1], val[MAXN << 1], tot;
void addedge(int b, int e, int v) {
	nxt[++tot] = head[b]; head[b] = tot; to[tot] = e; val[tot] = v;
	nxt[++tot] = head[e]; head[e] = tot; to[tot] = b; val[tot] = v;
}
int sz[MAXN], sznow, rt, rtv;
bool vis[MAXN];
void getroot(int u, int fa) {
	int maxn = 0;
	sz[u] = 1;
	for (int i = head[u]; i; i = nxt[i])
		if (!vis[to[i]] && to[i] != fa) {
			getroot(to[i], u);
			sz[u] += sz[to[i]];
			maxn = max(maxn, sz[to[i]]);
		}
	maxn = max(maxn, sznow - sz[u]);
	if (maxn < rtv) rtv = maxn, rt = u;
}
int liA[MAXN], liB[MAXN], baka, bakb, tcnt;
void dfs(int u, int fa, int v) {
	if (rec[v]) {
		tcnt += v == 0 && rec[v] == 1;
		++B[v], liB[++bakb] = v;
	} else ++A[v], liA[++baka] = v;
	++rec[v];
	for (int i = head[u]; i; i = nxt[i])
		if (to[i] != fa && !vis[to[i]])
			dfs(to[i], u, v + val[i]);
	--rec[v];
}
long long calc(int u, int v) {
	tcnt = baka = bakb = 0;
	if (v) liA[++baka] = 0, ++rec[0];
	dfs(u, 0, v);
	if (v) --rec[0];
	long long resA = !v ? -tcnt : 0, resB = 0;
	for (int i = 1; i <= bakb; ++i) {
		resA += A[-liB[i]];
		resB += B[-liB[i]];
		if (liB[i] == 0) --resB;
	}
	resB >>= 1;
	for (int i = 1; i <= baka; ++i) A[liA[i]] = 0;
	for (int i = 1; i <= bakb; ++i) B[liB[i]] = 0;
	return resA + resB;
}
long long ans;
void solve(int u) {
	vis[u] = true;
	ans += calc(u, 0);
	for (int i = head[u]; i; i = nxt[i])
		if (!vis[to[i]]){
			ans -= calc(to[i], val[i]);
			rtv = 0x3f3f3f3f; sznow = sz[to[i]];
			getroot(to[i], 0);
			solve(rt);
		}
}
int t1, t2, t3;
int main() {
	scanf("%d", &n);
	for (int i = 1; i != n; ++i) {
		scanf("%d%d%d", &t1, &t2, &t3);
		addedge(t1, t2, t3 == 1 ? 1 : - 1);
	}
	rtv = 0x3f3f3f3f; sznow = n;
	getroot(1, 0); solve(rt);
	printf("%lld\n", ans);
	return 0;
}

```

---

## 作者：Shikita (赞：0)

# 树上路径统计 点分治

点分治是用来解决树上路径问题的一种方法。

在解决树上路径问题时，我们可以选取一点为根，将树转化为有根树，然后考虑经过根的所有路径（有时将两条从根出发的路径连接为一条）。统计完这些路径的答案后，将根节点标记为删除，对剩下的若干棵树进行同样的操作。

每次确认一个根节点后，共有$n$条需要考虑的路径（$n$为当前子树大小）。若将当前根节点删除后，剩下某棵的子树较大，和原树大小相当，继续处理这棵子树时仍然需要与前一过程相当的时间。

最严重的情况，当整棵树是一条链时，每次需要考虑的路径数量是$O(n)$级别的，如果每条路径需要常数时间进行统计，则总时间复杂度为$O(n^2)$

而对于形态随机的树，则远远小于这个级别。

所以我们应该合理选取树的根节点

而树的重心能够很好满足我们的需求

我们定义一棵树的重心为以该点为根时最大子树最小的点。

那么我们每次删除掉当前根节点后，剩余的子树能够保证尽量平衡，这就可以大大减小复杂度

```
//mx[x] 记录的是x的子树中最大的子树大小
inline void getroot(int x,int fa)
{
	size[x]=1,mx[x]=0;
	for(int i=head[x];i;i=e[i].next)
	if(v!=fa&&!vis[v])
	{
		getroot(v,x);
		size[x]+=size[v];
		mx[x]=max(mx[x],size[v]);
	}
	mx[x]=max(mx[x],sum-size[x]);
	if(mx[x]<mx[rt]) rt=x;
}
```

~~我觉得你们自己看代码应该好懂，不解释了~~

那么对于本题，我们将阴阳点分别置为1和-1，求路径上有一个0点且终点为0的路径条数


我们令$g[dis][0/1]$表示之前dfs过的子树中，到根的距离为$dis$的路径数目

$f$数组表示当前正在dfs的子树，到根的距离为$dis$的路径数目

0/1表示其中是否出现过前缀和为0的点。

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
    int x=0;
    char c=getchar();
    bool flag=0;
    while(c<'0'||c>'9') {if(c=='-')flag=1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x+(x<<2)<<1)+ c-'0';c=getchar();}
    return flag?-x:x;
}
const int N=1e5+5;
int n,sum,rt,mxdep;
int vis[N],t[N<<1],mx[N],size[N],dep[N],dis[N];
ll ans,g[N<<1][2],f[N<<1][2];

int head[N],cnt;
struct node{int to,next,w;}e[N<<1];
inline void add(int u,int v,int w)
{
	e[++cnt].to=v,e[cnt].next=head[u],e[cnt].w=w,head[u]=cnt;
	e[++cnt].to=u,e[cnt].next=head[v],e[cnt].w=w,head[v]=cnt;
}
//mx[x] x的最大子树 

#define v e[i].to
inline void getroot(int x,int fa)
{
	size[x]=1,mx[x]=0;
	for(int i=head[x];i;i=e[i].next)
	if(v!=fa&&!vis[v])
	{
		getroot(v,x);
		size[x]+=size[v];
		mx[x]=max(mx[x],size[v]);
	}
	mx[x]=max(mx[x],sum-size[x]);
	if(mx[x]<mx[rt]) rt=x;
}
//找重心 
inline void dfs(int x,int fa)
{
	mxdep=max(mxdep,dep[x]);
	(t[dis[x]])?++f[dis[x]][1]:++f[dis[x]][0];
	++t[dis[x]];
	for(int i=head[x];i;i=e[i].next) if(v!=fa&&!vis[v])
	{
		dep[v]=dep[x]+1;
		dis[v]=dis[x]+e[i].w;
		dfs(v,x);
	}
	--t[dis[x]];
}
inline void solve(int x)
{
	int mx=0;vis[x]=g[n][0]=1;
	for(int i=head[x];i;i=e[i].next) if(!vis[v])
	{
		dis[v]=n+e[i].w;dep[v]=1;mxdep=1;
		dfs(v,0);mx=max(mx,mxdep);
		ans+=(g[n][0]-1)*f[n][0];
		for(int j=-mxdep;j<=mxdep;++j)
		ans+=g[n-j][1]*f[n+j][1]+g[n-j][0]*f[n+j][1]+g[n-j][1]*f[n+j][0];
		for(int j=n-mxdep;j<=n+mxdep;++j)
		{
			g[j][0]+=f[j][0];
			g[j][1]+=f[j][1];
			f[j][0]=f[j][1]=0;
		}
	}
	for(int i=n-mx;i<=n+mx;++i) g[i][0]=g[i][1]=0;
	for(int i=head[x];i;i=e[i].next)
	if(!vis[v])
	{
		sum=size[v];rt=0;getroot(v,0);solve(rt);
	}
}
#undef v
int main()
{
	n=read();
	for(int i=1;i<n;++i)
	{
		int u=read(),v=read(),w=read();
		if(!w) w=-1;
		add(u,v,w);
	}
	sum=mx[0]=n;
	getroot(1,0);
	solve(rt);
	printf("%d\n",ans);
}
```

---

