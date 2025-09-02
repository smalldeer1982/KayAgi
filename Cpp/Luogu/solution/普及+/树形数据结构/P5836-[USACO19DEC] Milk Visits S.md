# [USACO19DEC] Milk Visits S

## 题目描述

Farmer John 计划建造 $N$ 个农场，用 $N-1$ 条道路连接，构成一棵树（也就是说，所有农场之间都互相可以到达，并且没有环）。每个农场有一头奶牛，品种为更赛牛或荷斯坦牛之一。

Farmer John 的 $M$ 个朋友经常前来拜访他。在朋友 $i$ 拜访之时，Farmer John 会与他的朋友沿着从农场 $A_i$ 到农场 $B_i$ 之间的唯一路径行走（可能有 $A_i = B_i$）。除此之外，他们还可以品尝他们经过的路径上任意一头奶牛的牛奶。由于 Farmer John 的朋友们大多数也是农场主，他们对牛奶有着极强的偏好。他的有些朋友只喝更赛牛的牛奶，其余的只喝荷斯坦牛的牛奶。任何 Farmer John 的朋友只有在他们访问时能喝到他们偏好的牛奶才会高兴。

请求出每个朋友在拜访过后是否会高兴。

## 说明/提示

在这里，从农场 1 到农场 4 的路径包括农场 1、2 和 4。所有这些农场里都是荷斯坦牛，所以第一个朋友会感到满意，而第二个朋友不会。

关于部分分：

测试点 $1$ 样例。

测试点 $2\sim 5$ 满足 $N\le 10^3$，$M\le 2\cdot 10^3$。

对于 $100\%$ 的数据，$1 \leq N \leq 10^5$，$1 \leq M \leq 10^5$。

供题：Spencer Compton

## 样例 #1

### 输入

```
5 5
HHGHG
1 2
2 3
2 4
1 5
1 4 H
1 4 G
1 3 G
1 3 H
5 5 H```

### 输出

```
10110```

# 题解

## 作者：ycmir27 (赞：183)

# 不得不说，这题看上去就是一道裸的LCA...
但是，我们要记住，USACO的**silver**并不难！

于是，就出现了（并查集）这个代码难度极小的做法

这一棵树只有两种颜色，故我们只要记录树上一个个颜色相同的连通块，只有当所查询两点是同一连通块且连通块颜色与目标颜色不同时输出0。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int fa[100010],ans[100010],M,N;
char col[100010];
int find(int x)
{
	if(x==fa[x])	return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y)
{
	fa[find(x)]=find(y);
}
int main()
{
	int cnt=0;
	cin>>N>>M;
	for(int i=1;i<=N;i++)
	{
		fa[i]=i;
		cin>>col[i];
	}	
	for(int i=1;i<=N-1;i++)
	{
		int u,v;cin>>u>>v;
		if(col[u]==col[v])	merge(u,v);
	}
	for(int i=1;i<=M;i++)
	{
		int a,b;	cin>>a>>b;
		char c;		cin>>c;
		if(find(a)==find(b)&&col[a]!=c)		ans[++cnt]=0;//判断路径上是否有偏好的牛奶
		else	ans[++cnt]=1;
	}
	for(int i=1;i<=cnt;i++)	cout<<ans[i];
	return 0;
}
```

听大佬说，有利用连通块的O（n）做法，可以留给大家自行思考

---

## 作者：Y_B_Y (赞：38)

可以用类似LCA的方法来做这一题

我们定义,$hv[x][i][1]$为$x$节点向父亲方向走$2^i$步所经过的点是否含有'H'(包括自己)

类似地,$hv[x][i][2]$为$x$节点向父亲方向走$2^i$步所经过的点是否含有'G'(包括自己)

特别地,定义$hv[x][i][0]$为$x$节点向父亲方向走$2^i$步所经过到的点

所以我们先倍增求hv,再想LCA那样两个点向上跳,如果遇到相应的奶牛种类就返回1并输出,直到结束都没有就返回0

时间复杂度$O(N~logN)$

比较多的细节可以看代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,cow[N],dep[N],fa[N],ft[N],nx[2*N],to[2*N];//cow[i]为奶牛种类,dep为点的深度,fa我点的父亲,ft,nx,to记录路径
int hv[N][21][3];//定义在上面
inline int read()
{
    char c=getchar();int sum=0,f=1;
    while(!(c>='0'&&c<='9')) {if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9') {sum=((sum<<1)+(sum<<3))+(c-'0');c=getchar();}
    return sum*f;
}
int cnt;//记录路径数,输入用
void add(int x,int y)
{
	nx[++cnt]=ft[x];
	ft[x]=cnt;
	to[cnt]=y;
}
void dfs(int x,int d)
{
	dep[x]=d;//记录深度
	hv[x][0][0]=fa[x];//跳2^0步为跳到父节点
	hv[x][0][1]=(cow[x]==1)||(cow[fa[x]]==1);//自己与父节点中只要有一个包含H即为1(路径中有H)
	hv[x][0][2]=(cow[x]==2)||(cow[fa[x]]==2);//同上
	for(int i=1;(1<<i)<=dep[x];i++)//1<<i等同于2^i
	{
		hv[x][i][0]=hv[hv[x][i-1][0]][i-1][0];//向LCA那样更新
		hv[x][i][1]=(hv[x][i-1][1])||(hv[hv[x][i-1][0]][i-1][1]);//类似前面
	    hv[x][i][2]=(hv[x][i-1][2])||(hv[hv[x][i-1][0]][i-1][2]);//同上
	}
	for(int i=ft[x];i;i=nx[i])
	{
		if(to[i]!=fa[x])/*保证不往回走*/ fa[to[i]]=x,dfs(to[i],d+1);//继续向下
	}
}
int jp(int x,int y,int w)///开始跳,w为要求种类
{	
	if(dep[x]>dep[y]) swap(x,y);//LCA
	for(int i=(int)log2(dep[y]-dep[x]);i>=0;i--)//这里dep[x]=dep[y]时,log2(0)=-无穷大,不会进行循环
	{
		if(dep[hv[y][i][0]]>=dep[x])
		{
			if(hv[y][i][w]) return 1;//只要找到就返回
			y=hv[y][i][0];//跳
		}
	}
	if(x==y)//LCA中有详细解释,如果发现跳到重合了
	{
		if(cow[x]==w) return 1;//虽然一般情况前面判定过了,但是如果x一开始就等于y时前面循环没有进行,没进行过判定,所以需要再判一次
		else return 0;
	}
	for(int i=(int)log2(dep[x]);i>=0;i--)//跳
	{
		if((1<<i)<=dep[x])
		{
			if(hv[x][i][0]!=hv[y][i][0])//LCA
			{
				if(hv[x][i][w]||hv[y][i][w]) return 1;//找到
				x=hv[x][i][0],y=hv[y][i][0];
			}
		}
	}
	if(hv[x][0][w]||hv[y][0][w]) return 1;//差一步跳到他们的公共祖先,同上面的原因,可能前面的循环内操作没有进行过,所以要用hv[x][0][w]||hv[y][0][w]顺便判断一下他们自身
	return 0;//都没有返回0
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++) 
	{
		char c;
		scanf("%c",&c);
		if(c=='H') cow[i]=1;//记H为1
		else cow[i]=2;//G为2
	}
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read();
		add(x,y);
		add(y,x);
	}
	dfs(1,0);//求hv
	for(int i=1;i<=m;i++)
	{
		int a=read(),b=read(),w;
		char c;
		scanf("%c",&c);
		if(c=='H') w=1;
		else w=2;
		cout<<jp(a,b,w);//跳
	}
	return 0;
}
```


---

## 作者：密期望 (赞：32)

即是只用了10min不到，由大常数选手编写，$O(n)$还是毫无悬念拿了最优解。

大家都把问题想复杂了，这题根本用不到lca。

为什么这道题特意只给了两种颜色？

因为只有两种颜色时，想要输出0，必须是一条路径上全都是另一种颜色。因此我们把题目转化为了如何判断一条路径是否同色。

我们用$top[i]$表示$i$号点向上连续与它同色最多能走到哪里。即

$top[i]=$

$top[father[i]],if(color[father[i]]==color[i])$

$i,if(color[father[i]]!=color[i])$

那么路径$i->j$同色当且仅当$top[i]==top[j]$

$O(n)$大常数代码如下：

```
#include<cstdio>
typedef long long ll;
typedef long double ld;
const int N=1e5+10;
void file(const char *str){
    char in[100],out[100];
    sprintf(in,"%s.in",str),sprintf(out,"%s.out",str);
    freopen(in,"r",stdin),freopen(out,"w",stdout);
}
#define fast_io
#ifdef fast_io
const int _IB=1e6;
char _ibuf[_IB],*_s,*_t;
#define getchar()\
 (_s==_t&&(_t=(_s=_ibuf)+fread(_ibuf,1,_IB,stdin),_s==_t)?EOF:*_s++)
#endif
ll read(){
    ll a=0;int op=1;char ch=getchar();
    while(ch<'0'||'9'<ch){if(ch=='-')op=-1;ch=getchar();}
    while('0'<=ch&&ch<='9'){a=(a<<3)+(a<<1)+(48^ch);ch=getchar();}
    return a*op;
}
int read_color(){
    char c;
    while((c=getchar())!=EOF){
        switch(c){
            case 'H':return 0;
            case 'G':return 1;
        }
    }
    return -1;
}
struct L{
    int to,next;
};
int head[N];
L l[N<<1];
int lcount;
void add(int from,int to){
    l[++lcount].to=to;
    l[lcount].next=head[from];
    head[from]=lcount;
}
#define REPL(S,I,T) for(int I=head[S],T;T=l[I].to,I;I=l[I].next)
int n,m;
int c[N];
int top[N];
void dfs(int now=1,int t=1,int f=0){
    top[now]=t;
    REPL(now,i,to)if(f!=to)dfs(to,c[to]==c[now]?t:to,now);
}
void input(){
    n=read();
    m=read();
    for(int i=1;i<=n;i++)c[i]=read_color();
    int p1,p2;
    for(int i=1;i<n;i++){
        p1=read();
        p2=read();
        add(p1,p2);
        add(p2,p1);
    }
}
void ini(){
    dfs();
}
void solve(){
    int p1,p2,p3;
    for(int i=0;i<m;i++){
        p1=read();
        p2=read();
        p3=read_color();
        printf("%d",c[p1]==p3||c[p2]==p3||top[p1]!=top[p2]?1:0);
    }
}
void output(){
}
void test(){
    input();
    ini();
    solve();
    output();
}
void all(){
    file("tmp");
    test();
}
int main(){
    all();
    return 0;
}
```

---

## 作者：tiger2005 (赞：30)

### 做题全过程

做完Silver T1之后就看这道题了。

由于T2看起来是一道模拟(对于我来说)，就先放一边了。

扫了一眼T3，发现了树上路径这个东西。

LCA在我脑中显现，我开始敲倍增(Tips:在这里打树剖明显慢了很多，在这种普通的LCA使用中可以用倍增加快写代码速度)。

又看了一眼题目，发现只有两种状态要维护。

舍然大喜。开了两个数组维护就行了。

思维Correct!之后只剩代码了。

提交的时候还想着为什么只有两种状态……怎么不搞一个N种的呢……

---

### 题意简述

给定一棵树，树上的点只有两种状态——H或G。

Q次询问，每次询问两点间路径有没有H或者G。

---

### 做法

正如我的做题过程所说的，这道题需要使用LCA这个东西。

我们可以想到，树上两点间路径可以这么表示：

![](https://cdn.luogu.com.cn/upload/image_hosting/lvmc2cwo.png)

蓝色=P1+P2-2*P3+(LCA上的信息)。

(这张图中没有表示出LCA被加减的次数，请读者自行思考)

也就是说，我们可以只维护一个节点到根节点路径上H和G的数量就行。

由于一个节点的信息和其父亲的信息只差1，所以这很好修改。

那么复杂度就是$O(N+QlogN)$(前面是DFS，后面是LCA)。

Code:
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int N,M;
char PZ[100010];
int qxx[200010][2],tt[100010],nn;
int fa[100010],dep[100010];
int bz[100010][20];
int H[100010],G[100010];
void ad(int u,int v){
	qxx[++nn][0]=v;
	qxx[nn][1]=tt[u];
	tt[u]=nn;
}
void dfs(int u){
	H[u]=H[fa[u]]+(PZ[u]=='H');
	G[u]=G[fa[u]]+(PZ[u]=='G');
	dep[u]=dep[fa[u]]+1;
	for(int i=tt[u];i;i=qxx[i][1]){
		int v=qxx[i][0];
		if(v==fa[u])	continue;
		fa[v]=u;
		dfs(v);
	}
}
int lca(int u,int v){
	if(dep[u]<dep[v])	swap(u,v);
	for(int i=17;i+1;i--)
		if(dep[bz[u][i]]>=dep[v])	u=bz[u][i];
	if(u==v)	return u;
	for(int i=17;i+1;i--)
		if(bz[u][i]!=bz[v][i])	u=bz[u][i],v=bz[v][i];
	return fa[u];
}
int main(){
	freopen("milkvisits.in","r",stdin);
	freopen("milkvisits.out","w",stdout);
	scanf("%d%d",&N,&M);
	scanf(" %s",PZ+1);
	for(int i=1,a,b;i<N;i++){
		scanf("%d%d",&a,&b);
		ad(a,b);ad(b,a);
	}
	fa[1]=1;dfs(1);
	for(int i=1;i<=N;i++)	bz[i][0]=fa[i];
	for(int i=1;i<18;i++)
		for(int j=1;j<=N;j++)
			bz[j][i]=bz[bz[j][i-1]][i-1];
	for(int i=1,a,b;i<=M;i++){
		scanf("%d%d",&a,&b);
		char c;scanf(" %c",&c);
		int u=lca(a,b);
		int hh=H[a]+H[b]-H[u]*2+(PZ[u]=='H');
		int gg=G[a]+G[b]-G[u]*2+(PZ[u]=='G');
		if(c=='H'){
			if(hh)	printf("1");
			else	printf("0");
		}
		else{
			if(gg)	printf("1");
			else	printf("0");
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
```

---

## 作者：老咸鱼了 (赞：20)

介绍一种并查集的写法

因为题目只有2种颜色，那么我们把同一种颜色连在一起的放在同一个连通块里面，也就是把两个点合并，查询的时候如果两个点没有公共祖先，那么他一定经过了2种颜色，如果是相同的公共祖先，那么我们只要判断它的节点的颜色是不是查询的颜色。

~~具体写法看代码，如果会并查集的话理解还是比较简单的。~~
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='H'||c=='G')return c;
		if(c=='-')f=-1;c=getchar();
	}
	while(c>='0'&&c<='9'){
		s=(s<<1)+(s<<3)+(c^48);c=getchar();
	}
	return f*s;
}
const int N=1555555;
int n,m,b[N];
char c[N];
vector<int>q[N];
int find(int x){
	if(b[x]!=x){
		b[x]=find(b[x]);
	}
	return b[x];
}
int main(){
	n=read(),m=read();
	scanf("%s",c+1);
	for(int i=1;i<=n;i++)b[i]=i;
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		if(c[x]==c[y])b[find(x)]=find(y);
	}
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		printf("%d",find(x)!=find(y)||c[x]==z);
	}
	return 0;
}
```
如果代码有问题希望大佬能够指正

---

## 作者：7KByte (赞：17)

抢第一篇题解


题意
>求路径u-v上是否有颜色$H/G$

这里提供一个好的[方法](https://www.luogu.com.cn/blog/onlinewlq123/solution-p5838)（狗头

但显然并不需要这么复杂

我们对$1-i$路径上记录颜色$H/G$的个数（树上前缀和即可

查询时直接树上差分即可

$O(NlogN)$

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
#define N 100005
int n,m,h[N],tot;
struct edge{
	int to,nxt;
}e[N<<1];
void add(int x,int y){
	e[++tot].to=y;e[tot].nxt=h[x];h[x]=tot;
}
char s[N];
int H[N],G[N],f[N][20],t,d[N];
void dfs(int x,int fa){
	d[x]=d[fa]+1;f[x][0]=fa;
	if(s[x]=='H')H[x]=1;
	else G[x]=1;
	H[x]+=H[fa];G[x]+=G[fa];
	rep(i,1,t)f[x][i]=f[f[x][i-1]][i-1];
	for(int i=h[x];i;i=e[i].nxt)
	  if(e[i].to!=fa)dfs(e[i].to,x);
}
int lca(int x,int y){
	if(d[x]<d[y])swap(x,y);
	for(int i=t;i>=0;i--)if(d[f[x][i]]>=d[y])x=f[x][i];
	if(x==y)return x;
	for(int i=t;i>=0;i--)if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
	return f[x][0];
}
int main(){
	//freopen("milkvisits.in","r",stdin);
	//freopen("milkvisits.out","w",stdout);
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	rep(i,1,n-1){
		int x,y;scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	t=log2(n);
	dfs(1,0);
	//cout<<endl<<endl;
	//rep(i,1,n)printf("%d %d\n",H[i],G[i]);
	//cout<<endl<<endl;
	int x,y;char op[2];
	rep(i,1,m){
		scanf("%d%d%s",&x,&y,op);
		int val,L=lca(x,y);
		if(op[0]=='H')val=H[x]+H[y]-H[L]-H[f[L][0]];
		else val=G[x]+G[y]-G[L]-G[f[L][0]];
		if(val)putchar('1');
		else putchar('0');
		//cout<<val<<" "<<L<<endl;
	}
	putchar('\n');
	return 0;
}
```

---

## 作者：LinkyChristian (赞：13)

# 连通块做法
首先，这是一颗只有两种颜色的树。
根据题面我们知道，当一个访客不高兴时仅限于他所经过的路径上没有他想要的颜色，即这条路径上全为另一种颜色。

这种情况是极为罕见的，因为大部分情况下一条路径是两种颜色都有的。

于是我们将同一种颜色且相连的节点视作一个联通块。

1. 询问的两点不处于同一连通块 此时两种颜色都有

2. 询问的两点属于同一连通块，且为想要的颜色

2. 询问的两点属于同一连通块，为不想要的颜色

另外还有LCA做法（更难）

---

## 作者：封禁用户 (赞：11)

使用树链剖分，把每一个值为$H$的点赋值为$1$，每一个值为$G$的点赋值为$0$。

这样我们就可以把本来的找元素在路径上有没有出现转化为求路径的值。如果这个值$>0$，那么一定经过过含$H$的点，如果这个值不等于$dep[u]+dep[v]-2*dep[lca(u,v)]+1$，那么一定经过过含$G$的点。

用树链剖分lca会比较快，而且在处理后面元素出现时会比较方便。

总时间复杂度是$O(n\log n+ m(\log^2n+\log n))=O(n\log^2n)$


```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i) 
#define gc() getchar()
#define endll putchar('\n')
using namespace std;
typedef long long ll;
inline ll read(){
    char ch=gc();
    ll x=0,f=1;
    while(ch<'0'||ch>'9'){
	if(ch=='-') f=-1;
	ch=gc();
    }
    while(ch>='0'&&ch<='9'){
	x=x*10+ch-'0';
	ch=gc();
    }
    return x*f;
}
inline void print(ll k){
    if(k<0) k=-k,putchar('-');
    if(k>9) print(k/10);
    putchar(k%10+48);
}
inline void println(ll k){
    print(k);
    endll;
}
inline void printsp(ll k){
    print(k);
    putchar(' ');
}
const int maxn=200499;
int seg[maxn<<2],tag[maxn<<2];
int head[maxn],nextt[maxn],to[maxn],tot;
int MOD;
int cnt;
int n,m,r;
int siz[maxn];
int ans[maxn];
int son[maxn],id[maxn],fa[maxn],top[maxn],wt[maxn],w[maxn];
int dep[maxn];
int tmp[maxn];
inline int lson(int p){
    return p<<1;
}
inline int rson(int p){
    return p<<1|1;
}
inline void push_up(int p){
    seg[p]=(seg[lson(p)]+seg[rson(p)]);
}
inline void addedge(int u,int v){
    to[++tot]=v;
    nextt[tot]=head[u];
    head[u]=tot;
}
inline void build(int p,int l,int r){
    tag[p]=0;
    if(l==r){
        seg[p]=wt[l];
        //seg[p]=tmp[l];
        return;
    }
    int mid=(l+r)>>1;
    build(lson(p),l,mid);
    build(rson(p),mid+1,r);
    push_up(p);
}
inline void f(int p,int l,int r,int k){
    tag[p]+=k;
    seg[p]=(seg[p]+k*(r-l+1));
}
inline void push_down(int p,int l,int r){
    int mid=(l+r)>>1;
    f(lson(p),l,mid,tag[p]);
    f(rson(p),mid+1,r,tag[p]);
    tag[p]=0;
}
int query(int dl,int dr,int l,int r,int p){
    int res=0;
    if(dl<=l&&r<=dr) return seg[p];
    int mid=(l+r)>>1;
    push_down(p,l,r);
    if(dl<=mid) res=(query(dl,dr,l,mid,lson(p))+res);
    if(dr>mid) res=(query(dl,dr,mid+1,r,rson(p))+res);
    return res;
}
inline int qrange(int x,int y){
    int ans=0;
    int res;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        res=0;
        res=query(id[top[x]],id[x],1,n,1);
        ans=(ans+res);
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    res=query(id[x],id[y],1,n,1);
    ans+=res;
    return ans;
}
void dfs1(int x,int f,int deep){
    dep[x]=deep;
    fa[x]=f;
    siz[x]=1;
    int maxson=-1;
    for(int i=head[x];i;i=nextt[i]){
        int y=to[i];
        if(y==f) continue;
        dfs1(y,x,deep+1);
        siz[x]+=siz[y];
        if(siz[y]>maxson) son[x]=y,maxson=siz[y];
    }
}
inline void dfs2(int x,int topf){
    id[x]=++cnt;
    wt[cnt]=w[x];
    top[x]=topf;
    if(!son[x]) return ;
    dfs2(son[x],topf);
    for(int i=head[x];i;i=nextt[i]){
        int y=to[i];
        if(y==fa[x]||y==son[x]) continue;
        dfs2(y,y);
    }
}
int lca(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]>=dep[top[y]]) x=fa[top[x]];
        else y=fa[top[y]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    return x;
}
int main(){
    n=read(),m=read();
    r=1;
    string tt;
    cin>>tt;
    rep(i,0,tt.length()-1){
        if(tt[i]=='H') w[i+1]=1;
        else w[i+1]=0;
    }
    rep(i,1,n-1){
        int u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(r,0,1);
    dfs2(r,r);
    build(1,1,n);
    rep(i,1,m){
        int u=read(),v=read();
        char tmp;
        cin>>tmp;
        if(u==v){
            if(tmp=='H'){
                if(w[u]==1) ans[i]=1;
                else ans[i]=0;
            }
            else{
                if(w[u]==0) ans[i]=1;
                else ans[i]=0;
            }
        }
        int opt=qrange(u,v);
        //cout<<"opt:"<<opt<<endl;
        if(tmp=='H'){
            if(opt>0) ans[i]=1;
            else ans[i]=0;
        }
        else{
            if(opt!=(dep[u]+dep[v]-2*dep[lca(u,v)]+1))  ans[i]=1;
            else ans[i]=0;
        }
    }
    for(int i=1;i<=m;++i) print(ans[i]);
    return 0;
}

```


---

## 作者：gznpp (赞：7)

这题是整个 12 月银组里面最没思维难度的题……倍增 LCA 板子还行……  
[洛谷模板](https://www.luogu.com.cn/problem/P3379)

但是银组参赛者不一定会学到 LCA，这里简单讲一下。

关键数组 $f$：$f(i, j)$ 表示从点 $i$ 开始向根的方向走 $2^j$ 条边所能到达的点。

状态转移方程：$f(i, j) = f(\ f(i, j-1), j-1)$。  
初值：$f(i, 0) = \mathrm{parent}(i)$。

预处理：从根开始往下 dfs 或 bfs，处理好初值并记录深度。时间复杂度 $O(N)$。再对每个点做一次 dp，在 dfs 或 bfs 内外都行。时间复杂度 $O(N \log N)$。

可以看到，这里的 $f$ 数组可以推广一下，保存每个点往根方向的路径上各个边/点的性质。常见的维护值有路径长度（树上求最短路）以及点的特殊性质（比如本题中各个农场的奶牛种类）等。

在本题当中，我们再开一个布尔数组 $g(i, j, k\in \{0,1\}\ )$，表示从点 $i$ 开始向根的方向走 $2^j$ 条边的过程中，有没有碰到 $k$ 类型的奶牛。

状态转移方程：$g(i, j, k)\ |= g(i, j-1, k)\ |\ g(\ g(i, j-1), j-1, k)$，其中 $|$ 表示按位或（此题也可用逻辑或）。  
初值：$g(i, 0, k)$ 保存自己和双亲节点这两个点中有没有 $k$ 类型的奶牛。

最后处理 LCA 询问，设询问两点为 $x,y\ (\operatorname{dep}(x) \le \operatorname{dep}(y)\ )$，先从大到小枚举 $j$，把 $y$ 跳到和 $x$ 深度一样，此时特判：`if (x == y) return x;` 否则接着跳，再从大到小枚举 $j$，当两点不一样时就往上跳，最后状态是 $x$ 和 $y$ 跳到还差一步就相遇了。

LCA 代码：
```cpp
il void init()
{
    que.push(s);
    dep[s]=1;
    while(que.size())
    {
        int x=que.front();
        que.pop();
        for(rgi i=fst[x];i;i=nxt[i])
        {
            int y=v[i];
            if(dep[y])
                continue;
            dep[y]=dep[x]+1;
            f[y][0]=x;
            for(rgi j=1;j<=t;++j)
                f[y][j]=f[f[y][j-1]][j-1];
            que.push(y);
        }
    }
    return;
}
il int lca(int x,int y)
{
    if(dep[x]>dep[y])
        swap(x,y);
    for(rgi i=t;i>=0;--i)
        if(dep[f[y][i]]>=dep[x])
            y=f[y][i];
    if(x==y)
        return x;
    for(rgi i=t;i>=0;--i)
        if(f[x][i]!=f[y][i])
            x=f[x][i],y=f[y][i];
    return f[x][0];
}
```
接下来把 $g$ 带上，转移 $f$ 同时转移 $g$，询问时定义一个变量按位/逻辑或上沿途遇到的 $g$ 即可。

完整代码：
```cpp
#include <cstdio>
#include <cctype>
#include <queue>
#include <cmath>
#define il inline
#define rgi register int
using namespace std;
const int maxn=1e5+5,maxm=maxn<<1;
int n,m,q,t,s;
int u[maxm],v[maxm],fst[maxn],nxt[maxm];
int dep[maxn],f[maxn][20];
char str[maxn];
bool book[maxn],dp[maxn][20][2];
queue<int> que;
il int ri()
{
	register int o1=0;
	register char o3=getchar();
	while(!isdigit(o3))
		o3=getchar();
	while(isdigit(o3))
		o1=(o1<<1)+(o1<<3)+(o3^48),o3=getchar();
	return o1;
}
void inital()
{
    que.push(s);
    dep[s]=1;
    while(!que.empty())
    {
        int x=que.front();
        que.pop();
        for(rgi i=fst[x];i;i=nxt[i])
        {
            int y=v[i];
            if(dep[y])
                continue;
            dep[y]=dep[x]+1;
            f[y][0]=x,dp[y][0][book[x]]=1;
            que.push(y);
        }
    }
}
int lca(int x,int y,bool z)
{
    bool ret=0;
	if(dep[x]>dep[y])
        swap(x,y);
    for(rgi i=t;i>=0;--i)
        if(dep[f[y][i]]>=dep[x])
            ret|=dp[y][i][z],y=f[y][i];
    if(x==y)
        return ret;
    for(rgi i=t;i>=0;--i)
        if(f[x][i]!=f[y][i])
        {
            ret|=dp[x][i][z],ret|=dp[y][i][z];
	        x=f[x][i],y=f[y][i];//往上跳的时候先 dp 再跳 x 和 y，可以考虑一下不这样做的后果
        }
    ret|=dp[x][0][z],ret|=dp[y][0][z];//注意这步别丢
    return ret;
}
int main()
{
    // freopen("milkvisits.in","r",stdin);
    // freopen("milkvisits.out","w",stdout);
	n=ri(),q=ri();
    s=1,m=n-1,t=log(n)/log(2)+1;
    scanf("%s",str+1);
    for(rgi i=1;i<=n;++i)
    {
    	if(str[i]=='H')
    		book[i]=1;
    	for(rgi j=0;j<=t;++j)
			dp[i][j][book[i]]=1;//这么写也行
    }
    for(rgi i=1;i<=m;++i)
    {
        u[i]=ri(),v[i]=ri();
        nxt[i]=fst[u[i]];
        fst[u[i]]=i;
        u[i+m]=v[i];
        v[i+m]=u[i];
        nxt[i+m]=fst[u[i+m]];
        fst[u[i+m]]=i+m;
    }
    inital();
    for(rgi j=1;j<=t;++j)
		for(rgi y=1;y<=n;++y)
        {
            f[y][j]=f[f[y][j-1]][j-1];
			dp[y][j][0]|=(dp[y][j-1][0]|dp[f[y][j-1]][j-1][0]);
			dp[y][j][1]|=(dp[y][j-1][1]|dp[f[y][j-1]][j-1][1]);
		}
    while(q--)
    {
        int x=ri(),y=ri();
        char z=getchar();
        bool b=0;
        while(z!='H'&&z!='G')
        	z=getchar();
        if(z=='H')
        	b=1;
        if(x==y)
        	printf("%1d",book[x]==b);
        //这个特判要加，因为 g 数组不会保存单个点的性质
        else
		{
			int ans=lca(x,y,b);
        	printf("%1d",ans);
		}
    }
    putchar(10);
    return 0;
}
```

---

## 作者：神仙酱 (赞：3)

### 前言
考虑激光炮打文蚊子，树上莫队。莫队是一种奇妙的算法，可以在 $O(n\sqrt{n})$ 的时间解决有多组询问的区间查询题目，它不一定是正解，但是足够暴力和好想。只要答案可以以 $O(1)$ 的复杂度，通过左移右移一次查询的区间端点统计出来，就满足莫队的使用条件。如果你还不会莫队，我强烈建议你参考莫队的神之入门教程[莫队算法——从入门到黑题 ](https://www.cnblogs.com/WAMonster/p/10118934.html)。

### 思路与注意事项
我简单介绍一下树上莫队的过程：

1. DFS 统计出每个结点的高度`dep`和即将用于求 LCA 的倍增祖先数组 `fa`，还需要求出欧拉序 `id` 和每个结点在欧拉序中管辖的范围 `in` 和 `out`。
2. 读入查询，分块、排序（莫队基本操作）。由于树上莫队实际上是在欧拉序上进行的，因此要把读入的查询从结点编号变换到其在欧拉序上的位置。
3. 根据排好的顺序依次处理每一个查询，如果当前这个牛首次出现，则在哈希表中加一，否则减一，要知道这个朋友开不开心只需要去查询这段区间对应哈希表里出现的喜欢的牛个数是否大于零即可。
4. 根据读入的顺序输出每一个查询的结果。

在这里我要再强调一下树上莫队与普通莫队的不同点。
- 欧拉序的长度是结点长度的两倍，因此分块大小是 `sqrt(n << 1)`。
- 只需要写一个 `add` 而不需要写 `del`。这得利于欧拉序的美好性质。
- 要把读入的查询从结点编号变换到其在欧拉序上的位置。为了保证变换后的位置 `l < r`,如果第一个所要查询结点的`in` 大于第二个所要查询结点的 `in`，要交换这两个结点。
- 在第三步中，**不要忘记统计来自 LCA的答案** （因为这个调了四五个小时）。
### AC代码
```c++
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
const int N = 1e5 + 10, M = N << 1;
int e[M], h[N], nxt[M], idx = 1;
int in[N], out[N], id[N << 1], dfn; // 欧拉序两倍空间
int dep[N], fa[N][22], ht[2], v[N], bsz;
bool ans[N], vis[N]; // vis 记录莫队时当前结点是否访问过

int n, m;
struct query_t {
    int l, r, id;
    bool t;
    bool operator<(const query_t& rhs) const {
        return l / bsz != rhs.l / bsz ? l < rhs.l : (l / bsz & 1) ? r < rhs.r : r > rhs.r;
    }
} q[M];

void add(int a, int b) {
    e[idx] = b, nxt[idx] = h[a], h[a] = idx++;
}

void add(int x) {
    if (vis[x])
        ht[v[x]]--;
    else
        ht[v[x]]++;
    vis[x] ^= 1;
}

void dfs(int u, int pa) {
    id[in[u] = ++dfn] = u;
    dep[u] = dep[pa] + 1;
    fa[u][0] = pa;
    for (int i = h[u]; i; i = nxt[i]) {
        int son = e[i];
        if (son == pa)
            continue;
        dfs(son, u);
    }
    id[out[u] = ++dfn] = u;
}

int lca(int x, int y) {
    if (dep[x] > dep[y])
        swap(x, y);
    for (int i = 20; i + 1; i--) {
        if (dep[y] - (1 << i) >= dep[x])
            y = fa[y][i];
    }
    if (x == y)
        return x;
    for (int i = 20; i + 1; i--)
        if (fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}
int main() {
    cin >> n >> m;
    bsz = sqrt(n << 1);
    for (int i = 1; i <= n; ++i) {
        char ch;
        cin >> ch;
        v[i] = ch == 'H';
    }
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    dfs(1, 0);
    for (int j = 1; j <= 20; j++) {
        for (int i = 1; i <= n; ++i)
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
    }
    for (int i = 1; i <= m; i++) {
        int a, b;
        char t;
        cin >> a >> b >> t;
        if (in[a] > in[b]) // 注意点3
            swap(a, b);

        int l = lca(a, b) == a ? in[a] : out[a];
        int r = in[b];

        q[i] = { l, r, i, t == 'H' };
    }
    sort(q + 1, q + 1 + m);
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        while (r < q[i].r)
            add(id[++r]);
        while (l > q[i].l)
            add(id[--l]);
        while (r > q[i].r)
            add(id[r--]);
        while (l < q[i].l)
            add(id[l++]);
        int x = id[l], y = id[r]; 
        int ca = lca(x, y);
        if (x != ca && y != ca) { // 注意点4
            add(ca);
            ans[q[i].id] = ht[q[i].t];
            add(ca);
        }
        else
            ans[q[i].id] = ht[q[i].t];
    }
    for (int i = 1; i <= m; ++i)
        cout << ans[i];
}
```

---

