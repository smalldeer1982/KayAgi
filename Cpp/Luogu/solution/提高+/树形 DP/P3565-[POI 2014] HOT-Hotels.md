# [POI 2014] HOT-Hotels

## 题目描述

在 Byteotia 有 $n$ 个城镇，通过 $n-1$ 条道路连接。

每条道路直接连接两个城镇。

所有的道路长度相同，并且是双向的。

已知每个城镇都可以通过一条或多条（直接连接的）道路到达其他城镇。

换句话说，道路网络形成了一棵树。

Byteotia 的国王 Byteasar 希望建造三家豪华酒店，以吸引来自世界各地的游客。

国王希望这些酒店位于不同的城镇，并且彼此之间的距离相同。

请通过编写程序来帮助国王，确定在 Byteotia 中可能的酒店三元组位置的数量。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
7
1 2
5 7
2 5
2 3
5 6
4 5
```

### 输出

```
5
```

# 题解

## 作者：xht (赞：78)

# 请到博客中查看

设 $f_{i,j}$ 为满足 $x$ 在 $i$ 的子树中且 $d(x, i) = j$ 的 $x$ 的个数，$g_{i,j}$ 为满足 $x,y$ 在 $i$ 的子树中且 $d(\operatorname{lca}(x, y), x) = d(\operatorname{lca}(x, y), y) = d(\operatorname{lca}(x, y), i) + j$ 的无序数对 $(x,y)$ 的个数。

有转移：

$$ans \leftarrow g_{i, 0}$$

$$ans \leftarrow \sum_{x,y \in \operatorname{son}(i), x \ne y} f_{x,j-1} \times g_{y,j+1}$$

$$g_{i,j} \leftarrow \sum_{x,y \in \operatorname{son}(i), x \ne y} f_{x,j-1} \times f_{y,j-1}$$

$$g_{i,j} \leftarrow \sum_{x \in \operatorname{son}(i)} g_{x, j+1}$$

$$f_{i,j} \leftarrow \sum_{x \in \operatorname{son}(i)} f_{x, j-1}$$

显然这可以利用前缀和，或者说是所有儿子「向 $i$ 合并」，做到 $\mathcal O(n)$ 转移，总时间复杂度 $\mathcal O(n^2)$。

这个复杂度已经可以通过本题了。

---

考虑继续优化。

注意到这里的信息都是以深度为下标的，那么可以利用长链剖分将复杂度降为均摊 $\mathcal O(1)$，总时间复杂度即可降为 $\mathcal O(n)$。

在「直接继承重儿子的信息」时，需要用指针维护，具体见代码。

```cpp
const int N = 1e5 + 7;
int n, d[N], dep[N], son[N];
vi e[N];
ll *f[N], *g[N], p[N<<2], *o = p, ans;

void dfs(int x, int fa) {
	d[x] = d[fa] + 1;
	for (auto y : e[x])
		if (y != fa) {
			dfs(y, x);
			if (dep[y] > dep[son[x]]) son[x] = y;
		}
	dep[x] = dep[son[x]] + 1;
}

void dp(int x, int fa) {
	if (son[x])
		f[son[x]] = f[x] + 1, g[son[x]] = g[x] - 1, dp(son[x], x);
	f[x][0] = 1, ans += g[x][0];
	for (auto y : e[x])
		if (y != fa && y != son[x]) {
			f[y] = o, o += dep[y] << 1, g[y] = o, o += dep[y] << 1;
			dp(y, x);
			for (int i = 0; i < dep[y]; i++) {
				if (i) ans += f[x][i-1] * g[y][i];
				ans += g[x][i+1] * f[y][i];
			}
			for (int i = 0; i < dep[y]; i++) {
				g[x][i+1] += f[x][i+1] * f[y][i];
				if (i) g[x][i-1] += g[y][i];
				f[x][i+1] += f[y][i];
			}
		}
}

int main() {
	rd(n);
	for (int i = 1, x, y; i < n; i++)
		rd(x), rd(y), e[x].pb(y), e[y].pb(x);
	dfs(1, 0), f[1] = o, o += dep[1] << 1, g[1] = o, o += dep[1] << 1;
	dp(1, 0), print(ans);
	return 0;
}
```

---

## 作者：devout (赞：65)

这道题两维的做法应该挺好想的，但是要开2个$5000\times 5000$的数组，好像有点大？开$short$，算出来差不多96M，好像能卡过去？一看空间：67.5M（大艹

那我们考虑一维的做法

我们发现，三个点距离相等的话就是他们深度较深的两个点的$lca$到三个点的距离相等

我开始想的做法是枚举两个点（复杂度显然是$O(n^2)$），然后预处理出来什么东西然后搞，但是不太好弄

等等，如果把那个$lca$拎上来变成根，那么这三个点就在同一深度了，不是很好做了吗？

所以，我们枚举那个点，然后树形$dp\ O(n)$统计一下答案就可以了

但是统计答案还是有点麻烦，我们不能单纯的统计每个深度的点有多少个（样例都过不去），因为我们要保证任意两个的$lca$还是这个根节点，也就是说，我们当前枚举的根节点的每条出边指向的点所在的子树上最多只能选一个点

所以我们要枚举每一个子树，然后统计答案，因为要三个点，所以是当前子树中的个数乘上之前选过的里面选了2个点的情况数了

我们让$box[d]$表示当前子树中深度为$d$的点的个数，$f[d]$表示在整棵树之前遍历的部分中，深度为$d$的所有点中，选出两个点的合法方案数

为了方便转移，我们再引入一个$g[d]$表示在整棵树之前遍历的部分中，深度为$d$的所有点中，选出一个点的方案数

那么对于一次枚举子树，

$$ans=ans+f[d]\times box[d]$$
$$f[d]=f[d]+g[d]\times box[d]$$
$$g[d]=g[d]+box[d]$$

然后输出答案就可以了，记得开$long\  long$

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=5005;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n;
int head[N],cnt;
ll box[N],f[N],g[N],deepest;
ll ans;

struct Edge{
    int to,next;
}e[N<<1];

void add(int x,int y){
    e[++cnt]=(Edge){y,head[x]},head[x]=cnt;
}

void dfs(int u,int fa,int dep){
    deepest=max(deepest,1ll*dep);
    box[dep]++;
    RepG(i,u){
        int v=e[i].to;
        if(v==fa)continue;
        dfs(v,u,dep+1);
    }
}

int main()
{
    memset(head,-1,sizeof(head));
    read(n);
    Rep(i,1,n-1){
        int x,y;
        read(x),read(y);
        add(x,y),add(y,x);
    }
    Rep(i,1,n){
        memset(f,0,sizeof(box));
        memset(g,0,sizeof(g));
        RepG(j,i){
            int v=e[j].to;
            deepest=0;
            memset(box,0,sizeof(box));
            dfs(v,i,1);
            Rep(k,1,deepest){
                ans+=f[k]*box[k];
                f[k]+=g[k]*box[k];
                g[k]+=box[k];
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：Kelin (赞：28)

## [题意](https://blog.csdn.net/BeNoble_/article/details/79901441)

给你一棵树$,$求任选$3$个点使得两两树上距离相同的方案数

[$n\le 10^5$](https://www.lydsy.com/JudgeOnline/problem.php?id=4543)

---

## 题解

设$f[u][i]$表示$u$子树里距离$u$为$i$的节点个数

$g[u][i]$表示$u$子树里两个点$x,y$到其$lca$的距离都是$d,lca$到$u$的距离是$d-i$的方案数

画个图就是这样![这里写图片描述](https://cdn.luogu.com.cn/upload/image_hosting/zwwmtsu2.png)

$\forall v\in son_u$可以得到

$$ans=\sum_u(\sum_i f[u][i]*g[v][i+1]+f[u][i-1]*g[v][i])+g[u][0]$$

考虑怎么转移$($初值$f[u][0]=1)$

$$g[u][i]=\sum_vg[v][j+1]+f[u][i]*f[v][i-1]$$

$$f[u][i]=\sum_vf[v][i-1]$$

第一个式子中的$f[u][i]$是遍历完$v$前面子树得到的$dp$值

$($大概根据定义画个图应该就能理解了$)$

设$mx[u]$表示$dep[u$子树里最深的点$]-dep[u]+1$

可以发现对于$u$的任意一个儿子$v$上面的转移复杂度都是是$mx[v]$

而如果$u$只有一个儿子$v$可以发现

$$f[u][i]=f[v][i-1]$$

$$g[u][i]=g[v][i+1]$$

用指针表示就是

$$f[u]=f[v]-1$$

$$g[u]=g[v]+1$$

也就是说如果是链的话我们可以线性转移

所以考虑长链剖分$,u$的重儿子$son[u]$就是$mx$最大的节点

对于重儿子我们用上面的转移$,$其他轻儿子暴力转移

可以证明这样的复杂度是线性的

考虑每个点$u$转移的复杂度$p(u)=\sum_vmx[v]-mx[son[u]]=\sum_vmx[v]-mx[u]+1$

总复杂度就是$\sum_up(u)=\sum_u\sum_vmx[v]-mx[u]+1=n$

空间复杂度度就是$O(\sum$长链长度$)=O(n),$用指针分配内存就好了

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
const int N=1e5+5;
typedef int arr[N];
typedef long long ll;
struct eg{int nx,to;}e[N<<1];
int n,df[N*5],*f[N],*idf=df+1;arr fi,fa,mx,son;ll ans,dg[N*5],*g[N],*idg=dg+1;
inline void add(int u,int v){static int ce=0;e[++ce]={fi[u],v},fi[u]=ce;}
void dfs(int u){
	go(u)if(v^fa[u]){
		fa[v]=u,dfs(v),cmax(mx[u],mx[v]);
		if(mx[v]>mx[son[u]])son[u]=v;
	}++mx[u];
}
inline void Give(int u){f[u]=idf,idf+=mx[u]+1,idg+=mx[u]+1,g[u]=idg,idg+=mx[u]+1;}
void dp(int u){
	if(son[u])f[son[u]]=f[u]+1,g[son[u]]=g[u]-1,dp(son[u]);
	f[u][0]=1,ans+=g[u][0];
	go(u)if(v^fa[u]&&v^son[u]){
		Give(v),dp(v);
		fd(j,mx[v],0)ans+=g[v][j]*f[u][j-1]+g[u][j+1]*f[v][j];	
		fp(j,0,mx[v])g[u][j]+=g[v][j+1]+.3,f[u][j]+=f[v][j-1];
	}
}
int main(){
    #ifndef ONLINE_JUDGE
        file("s");
    #endif
   	sd(n);int u,v;
   	fp(i,2,n)sd(u),sd(v),add(u,v),add(v,u);
   	dfs(1);Give(1);dp(1);
   	printf("%lld\n",ans);
return 0;
}
```

---

## 作者：nofind (赞：21)

感觉其他题解中对转移方程的解释不够详细,因此蒟蒻就写一篇详细解释转移方程的题解吧,正解的讲解可以看看其他题解

------------
题意：https://www.luogu.org/problem/P3565

考虑O(n^2)

首先考虑所求的三点的分布一定是这样:
![](https://cdn.luogu.com.cn/upload/pic/75272.png)
即每个满足条件的三元组都会存在一个中间点(2),注意图中高低顺序不代表深度大小,只是为了好看...

于是考虑在中间点处计数

因此设状态:f[x][i]表示在x的子树中,到x距离为i的点的个数,g[x][i]表示在x的子树中到lca距离相等(设为d)，且它们的lca到x的距离为d-i的点对个数

这里f数组的转移显然为:f[x][i]+=f[y][i-1],但是g数组的转移却不好想(蒟蒻想了半个小时才想明白,dalao不要嘲讽)

1.g[x][i]+=g[y][i+1]:

这个画图很好理解,但是强行想(比如我~)就会很绕

见图：
![](https://cdn.luogu.com.cn/upload/pic/75276.png)

在2处点对（3,4）是存在g[2][1]中的,而在5处,(3,4)是存在g[5][0]中的

2.g[x][i]+=f[x][i]*f[y][i-1]

这里要注意:上式中的f[x][i]是不包含y中的点的

![](https://cdn.luogu.com.cn/upload/pic/75279.png)
比如上图:
假设1有两颗,新遍历的子树为3的,之前处理好的子树为2的,假设2号子树中的4到1距离为i,5到3的距离为i-1,那么显然3,4到它们的lca(即1)的距离为i,因此应该加到g[x][i](1为lca,根据g数组的定义,i-i=0,因此是g[x] [i])

f和g数组求好了,求答案就很简单了

1.在x之前处理好的子树中选两个点,与y中的点拼接:ans+=g[x][i]*f[y][i-1]

2.在y中选两个点,与x之前处理好的子树中的点拼接ans+=f[x][i]*g[y][i+1]

于是N^2的就写完了

code(只有80pts,f和g要用指针,不然会MLE,反正是暴力就懒得改了)：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=5010;
int n,cnt,ans;
int head[maxn];
int f[maxn][maxn],g[maxn][maxn];
struct edge
{
	int to,nxt;
}e[maxn<<1];
inline int read()
{
	char c=getchar();int res=0,f=1;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')res=res*10+c-'0',c=getchar();
	return res*f;
}
inline void add(int u,int v)
{
	e[++cnt].nxt=head[u];
	head[u]=cnt;
	e[cnt].to=v;
}
void dfs(int x,int fa)
{
	f[x][0]=1;
	for(int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(y==fa)continue;
		dfs(y,x);
		for(int j=0;j<n;j++)	
		{
			if(j)ans+=f[x][j-1]*g[y][j];
			ans+=g[x][j+1]*f[y][j];
		}
		for(int j=0;j<n;j++)
		{
			g[x][j+1]+=f[x][j+1]*f[y][j];
			if(j)g[x][j-1]+=g[y][j];
			f[x][j+1]+=f[y][j];
		}
	}
}
signed main()
{
	n=read();
	for(int i=1;i<n;i++)
	{
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	dfs(1,0);
	printf("%lld",ans);
	return 0;
}
```
假设我们无视n<=5000,偏要想O(N)的算法,那么就要用到长链剖分,这个题解的各位dalao已经写得很详细了:用长链剖分优化

code（抄的别人的,玄学指针不会用啊）:
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=100010;
int n,cnt,ans;
int head[maxn],maxdep[maxn],son[maxn];
int *f[maxn],*g[maxn],tmp[maxn<<2],*id=tmp;
struct edge
{
	int to,nxt;
}e[maxn<<1];
inline int read()
{
	char c=getchar();int res=0,f=1;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')res=res*10+c-'0',c=getchar();
	return res*f;
}
inline void add(int u,int v)
{
	e[++cnt].nxt=head[u];
	head[u]=cnt;
	e[cnt].to=v;
}
void dfs1(int x,int fa)
{
	for(int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(y==fa)continue;
		dfs1(y,x);
		maxdep[x]=max(maxdep[x],maxdep[y]);
		if(maxdep[y]>maxdep[son[x]])son[x]=y;
	}
	maxdep[x]=maxdep[son[x]]+1;
}
void dfs(int x,int fa)
{
	if(son[x])f[son[x]]=f[x]+1,g[son[x]]=g[x]-1,dfs(son[x],x);
	f[x][0]=1;ans+=g[x][0];
	for(int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(y==fa||y==son[x])continue;
		f[y]=id,id+=maxdep[y]<<1;g[y]=id,id+=maxdep[y]<<1;
		dfs(y,x);
		for(int j=0;j<maxdep[y];j++)
		{
			if(j)ans+=f[x][j-1]*g[y][j];
			ans+=g[x][j+1]*f[y][j];
		}
		for(int j=0;j<maxdep[y];j++)
		{
			g[x][j+1]+=f[x][j+1]*f[y][j];
			if(j)g[x][j-1]+=g[y][j];
			f[x][j+1]+=f[y][j];
		}
	}
}
signed main()
{
	n=read();
	for(int i=1;i<n;i++)
	{
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	dfs1(1,0);
	f[1]=id,id+=maxdep[1]<<1;g[1]=id,id+=maxdep[1]<<1;
	dfs(1,0);
	printf("%lld",ans);
	return 0;
}
```




---

## 作者：BeyondStars (赞：16)

神仙状态。
画画图可以发现有如下两种可能：  
![图片标题](https://leanote.com/api/file/getImage?fileId=5d38067bab64414b8a006248)

(此时5是根)  
![图片标题](https://leanote.com/api/file/getImage?fileId=5d380684ab64414d870060fb)
(此时1是根)  
然后就是推到状态~~看题解~~  
我们用$f[i][j]$表示在$i$的子树中距离$i$的长度为$j$的点有多少个，那么显然，$f[i][j] = \sum f[t][j-1]$。
另$g[i][j]$为在以$i$为根的子树中，$x$,$y$ 到其$LCA(x,y)$的距离为$d$，$i$到$LCA(x,y)$的距离为$d-i$的这样的点对$(x,y)$有多少对。那么~~显然~~$g[i][j] = \sum g[t][j+1]$关于为什么$g$是这样转移，我们可以用下图解释  
![图片标题](https://leanote.com/api/file/getImage?fileId=5d380905ab64414d8700617a)
图中，g[2][0] 表示的点有2个，那么￥g[2][0] = 2￥，那么因为$2->1=1$，所以$1$号点的状态就是$g[1][d-(j-1)]=g[1][d-j+1]$(向上挪了一步，所以距离要减1）。  
所以他是这么转移的。  
好，现在我们考虑如何统计答案。  
对于一个点$i$显然。$g[i][0]$就是答案的一部分，因为此时$i$已经是LCA了。然后我们新加入一个子节点是，对答案的贡献通过乘法原理可以计算的到是$g[i][j]*f[t][j-1]$至于为什么，可以看一下下面这个图  
![图片标题](https://leanote.com/api/file/getImage?fileId=5d380bccab64414b8a006390)  
一下子就明白了，6 2 3 构成3个符合条件的的hotel。，我们发现如果可以从子树中把f和j继承过来就好了，然后跑一波长链剖分。(如果不会可以看这篇[博客](https://www.cnblogs.com/cjyyb/p/9479258.html)，如果不会指针，可以看zxyoi神仙的[博客]  (https://blog.csdn.net/zxyoi_dreamer/article/details/84828291))
注意一下代码细节  
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#define int long long 
using namespace std;
const int MAXN = 300100;
int len[MAXN],lson[MAXN];
struct edge{
    int t,w,next;
}edges[MAXN<<2];
int head[MAXN];
int top;
void add(int f,int t,int w = 0) {
    edges[++top].next = head[f];
    edges[top].t = t;
    edges[top].w = w;
    head[f] = top;
}
int n,q;
void dfs1(int x,int fa){
    for(int i = head[x];i;i = edges[i].next){
        int t = edges[i].t;
        if(t==fa)continue;
        dfs1(t,x);
        if(len[t]>len[lson[x]])lson[x] = t;
    }
    len[x] = len[lson[x]]+1;
}
long long tmp[MAXN<<2],*f[MAXN],*g[MAXN],*id = tmp;
long long ans;
void work(int x,int fa){
	if(lson[x])f[lson[x]] = f[x]+1,g[lson[x]] = g[x]-1,work(lson[x],x);
	f[x][0] = 1;ans+=g[x][0];
	for(int i = head[x];i;i = edges[i].next){
		int t = edges[i].t;
		if(t==fa||to==lson[x])continue;
		f[t] = id;id+=len[t]<<1;
		g[t] = id;id+=len[t]<<1;
		work(t,x);
		for( int j = 0; j < len[t]; j++){//处理答案
            if(j) ans += f[x][j - 1] * g[t][j];
            ans += g[x][j + 1] * f[t][j];//为了处理三个点均是x的子节点和1个不是x的子节点的情况。不可能2个都不是x的子节点，因为这是一棵树
        }
        for( int j = 0; j < len[t]; j++){//处理转移
            g[x][j + 1] += f[x][j + 1] * f[t][j];
            if(j) g[x][j - 1] += g[t][j];
            f[x][j + 1] += f[t][j];
        }
    }
}
signed main(){
    scanf("%lld",&n);
    int fr,t;
    for(int i = 1;i<n;i++){
        scanf("%lld%lld",&fr,&t);add(fr,t);add(t,fr);
    }
    dfs1(1,0);
    f[1] = id,id+=len[1]<<1;
    g[1] = id;id+=len[1]<<1;
    work(1,0);
    printf("%lld",ans);
    return 0;
}
```
如果哪天图片炸了，请加我QQ1724458359我会补图，注明省份学校，反正我做这道题的时候感觉有个图挺形象的

---

## 作者：FC_Viiiiictor_K (赞：11)

# 这篇题解的算法非常暴力，但思维难度很低且可过，请酌情参考

首先考虑要选的三个点长什么样子，显然它们得有共同的LCA，而且以LCA为根时这三个点的深度一定相等；

然后看到数据范围是n=5000，显然O(n²)可过，那么不难想到先枚举点，然后用O(n)以内的复杂度处理出**以这个点为根时**的所有方案。

然后我们可以马上**暴力地**想到，可以对根的每一个**儿子**开桶，桶里放**这个儿子为根的子树内**对应深度的点的数量，同时我们再对**整棵树**开一个桶，放整棵树内对应深度的点的数量；

然后我们直接dfs，求出桶里的点数，然后枚举每一个深度，如果这个深度下点数小于等于2则直接跳过，否则把答案加上**该深度下整棵树的对应点数中选三个的组合数**；

但我们又很容易发现这样会算错，**因为如果有两个点在同一个儿子的子树内，这两个点的LCA就不是当前枚举的根**，违背了我们的定义，应该是不能算的；

我们再考虑不合法的情况：

1.在同一个子树内选两个，在其他一个子树内选一个；

2.在同一个子树内选三个；

对于后一种直接求组合；前一种的话还得乘上整体对应深度的点数减去该子树内的点数（因为另一个点是在其他子树内选的）。

算法分析完毕，**总结起来就是暴力枚举+简单组合数学+简单容斥原理**，~~由于涉及到枚举深度内枚举子树，时间复杂度不会分析，推测为O(n²)~~

代码：

```cpp
#define INL inline
#define REG register
#include <cstdio>
#include <iostream>
#include <memory.h>
#include <vector>
using namespace std;
typedef long long ll;
const int maxn=5050;
int n,sum[maxn];
ll ans;
vector<int> graf[maxn],buck[maxn];
ll c[maxn][5];//记忆化数组，由于最多用到选3个，第二维不用开太大
INL int read(){//快读
    REG int sum=0,sign=1;
    REG char tmp=getchar();
    while(tmp<'0'||tmp>'9'){
        if(tmp=='-'){
            sign=-1;
        }
        tmp=getchar();
    }
    while(tmp>='0'&&tmp<='9'){
        sum=(sum<<1)+(sum<<3)+(tmp-'0');
        tmp=getchar();
    }
    return sum*sign;
}
ll comb(int x,int y){//记忆化搜索求组合数
    if(y<0||x<0||y>x){
        return 0;
    }
    if(c[x][y]){
        return c[x][y];
    }
    if(x==y||!y){
        return 1;
    }
    return c[x][y]=comb(x-1,y)+comb(x-1,y-1);
}
void dfs(int pos,int fa,int root/*桶编号*/,int dep/*当前深度*/){
    if((int)buck[root].size()==dep){//子树内的桶
        buck[root].push_back(1);
    }
    else{
        buck[root][dep]++;
    }
    sum[dep]++;//全局桶
    for(REG unsigned i=0;i<graf[pos].size();i++){
        REG int tar=graf[pos][i];
        if(tar==fa){//防止倒流
            continue;
        }
        dfs(tar,pos,root,dep+1);
    }
}
int main(){
    //freopen("P3565.in","r",stdin);
    //freopen("P3565.out","w",stdout);
    n=read();
    for(REG int i=0;i<n-1;i++){
        REG int x=read(),y=read();
        graf[x].push_back(y);
        graf[y].push_back(x);
    }
    for(REG int pos=1;pos<=n;pos++){//枚举LCA
        if(graf[pos].size()<=2){//只有两个以下的儿子一定没法当三个点的LCA
            continue;
        }
        REG int maxd=-1;
        memset(sum,0,sizeof(sum));//记得清空！！
        for(REG unsigned i=0;i<graf[pos].size();i++){
            dfs(graf[pos][i],pos,graf[pos][i],0);
            maxd=max<int>(maxd,buck[graf[pos][i]].size()-1);//保证枚举到最深深度
        }
        for(REG int i=0;i<=maxd;i++){//枚举深度
            if(sum[i]<=2){//不到三个点，没得选
                continue;
            }
            ans+=comb(sum[i],3);//算上不合法方案的该深度下的方案数
            for(REG unsigned j=0;j<graf[pos].size();j++){
                if(i>=(int)buck[graf[pos][j]].size()){//有可能有的子树深度不足枚举到的深度
                    continue;
                }
                if(buck[graf[pos][j]][i]>=2){//去除第一种不合法方案
                    ans-=comb(buck[graf[pos][j]][i],2)*(sum[i]-buck[graf[pos][j]][i]);
                }
                if(buck[graf[pos][j]][i]>=3){//去除第二种不合法方案
                    ans-=comb(buck[graf[pos][j]][i],3);
                }
            }
        }
        for(REG unsigned i=0;i<graf[pos].size();i++){//记得清空*2
            buck[graf[pos][i]].clear();
        }
    }
    cout<<ans;
    return 0;
}
```


---

## 作者：Treaker (赞：9)

$$\color{cornflowerblue}{\mathcal{Treaker}}$$
# 树形DP
这题比较难想~~对于我这种DP蒟蒻~~

我们设两个数组$f[x][i]$表示以$x$为根的子树里到$x$距离为$i$的节点个数，$g[x][i]$以$x$为根的子树内，再来一条长度为$i$的链就能形成方案的节点个数。

转移方程如下：还是比较好理解的

这个$n$不要太在意，懒得那么细致了。
```cpp
for(int i = 0;i <= n;i ++) ans += g[x][i] * (i == 0 ? 0 : f[to][i-1]) + g[to][i+1] * f[x][i];
for(int i = 0;i <= n;i ++) g[x][i] += f[x][i] * (i == 0 ? 0 : f[to][i-1]) + g[to][i+1];
for(int i = 1;i <= n;i ++) f[x][i] += f[to][i-1];
```
肿么统计$ans$呢。

两种情况，一种是两个点在左边，一个点在右边；还有一种是两个点在右边，一个点在左边。

$g$数组的话，分3种情况，一种是原来就有的，另一种是一个点在左边，另一个点在右边，还有一种是全在右边。

$f$更简单了，不多赘述

暴力代码如下：（更精彩的在后面）
```cpp
#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;
const int N = 5001;
inline int read()
{
    int x = 0 , f = 1;  char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-')  f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
    return x * f;
}
int n;
int dep[N] , f[N][N] , g[N][N];
ll ans;
struct Edge
{
	int to; Edge *nxt;
	Edge(int to,Edge *nxt) : to(to) , nxt(nxt) {}
}*head[N];
inline void add(int u,int v) {head[u] = new Edge(v,head[u]);}
void get_tree(int x)
{
	f[x][0] = 1;
	for(Edge *i = head[x];i;i = i -> nxt)
	{
		int to = i -> to;
		if(dep[to]) continue;
		dep[to] = dep[x] + 1;
		get_tree(to);
		for(int i = 0;i <= n;i ++) ans += g[x][i] * (i == 0 ? 0 : f[to][i-1]) + g[to][i+1] * f[x][i];
		for(int i = 0;i <= n;i ++) g[x][i] += f[x][i] * (i == 0 ? 0 : f[to][i-1]) + g[to][i+1];
		for(int i = 1;i <= n;i ++) f[x][i] += f[to][i-1];
	}
}
int main()
{
//	freopen("c.in","r",stdin);
//	freopen("c.out","w",stdout);
	n = read();
	for(int i = 1 , u , v;i < n;i ++) 
	{
		u = read(); v = read();
		add(u,v); add(v,u);
	}
	dep[1] = 1;
	get_tree(1);
	printf("%lld\n",ans);
	return 0;
}
```
我又回来了，如果$n$是$1e5$考虑如何优化。

先给他长链剖分（学过树剖应该都知道），那么对它进行势能分析，然后他就成$O(n)$的了？？？

![](https://cdn.luogu.com.cn/upload/image_hosting/n577xs81.png)

可没这么简单，这样的复杂度的前提是我们直接处理长儿子（手动滑稽），

我们直接把长儿子赋给$x$，然后在对短儿子进行处理

势能分析的话是：这里$u$是$x$的子节点
$$\sum_{x=1}^n((\sum_uh(u)) - h(x))$$

它会相互抵消，最后就是近似$O(n)$.

这里采用了指针是因为，直接开数组真的开不下。

我们开一个大数组，每个节点都从大数组里面取一段出来赋值，节省空间。

我这里采用从上向下赋地址，因为我从下往上赋一直RE（我对内存的理解还是太浅显了）。

细节代码如下：
```cpp
#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;
const int N = 100005 , M = 100005;
inline int read()
{
    int x = 0 , f = 1;  char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-')  f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
    return x * f;
}
int n;
int dep[M] , hs[M] , in[M] , fa[M] , h[M];
ll ans , pool[N << 2] , *f[M] , *g[M] , *tail = pool;
struct Edge
{
	int to; Edge *nxt;
	Edge(int to,Edge *nxt) : to(to) , nxt(nxt) {}
}*head[N];
inline void add(int u,int v) {head[u] = new Edge(v,head[u]); in[v] ++;}
void get_tree(int x)
{
	h[x] = 1;
	for(Edge *i = head[x];i;i = i -> nxt)
	{
		int to = i -> to;
		if(dep[to]) continue;
		fa[to] = x;
		dep[to] = dep[x] + 1;
		get_tree(to);
		h[x] = max(h[x],h[to] + 1);
		if(h[to] > h[hs[x]]) hs[x] = to; 
	}
}
void dfs(int x)
{
	if(hs[x])
	{
		f[hs[x]] = f[x] + 1;
		g[hs[x]] = g[x] - 1;
		dfs(hs[x]);		
	}
	f[x][0] = 1; ans += g[x][0];
	for(Edge *i = head[x];i;i = i -> nxt)
	{
		int to = i -> to;
		if(to == hs[x] || to == fa[x]) continue;
		f[to] = tail; tail += h[to] << 1; g[to] = tail; tail += h[to] << 1;
		dfs(to);
		for(int j = 0;j <= h[to];j ++) ans += g[x][j] * (j == 0 ? 0 : f[to][j-1]) + g[to][j+1] * f[x][j];
		for(int j = 0;j <= h[to];j ++) g[x][j] += f[x][j] * (j == 0 ? 0 : f[to][j-1]) + g[to][j+1];
		for(int j = 1;j <= h[to];j ++) f[x][j] += f[to][j-1];
	}
}
int main()
{
//	freopen("c.in","r",stdin);
//	freopen("c.out","w",stdout);
	n = read();
	for(int i = 1 , u , v;i < n;i ++) 
	{
		u = read(); v = read();
		add(u,v); add(v,u);
	}
	dep[1] = 1;
	get_tree(1); f[1] = tail; tail += h[1] << 1; g[1] = tail; tail += h[1] << 1;
	dfs(1);
	printf("%lld\n",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
```


---

## 作者：是个汉子 (赞：7)

[洛谷传送门](https://www.luogu.com.cn/problem/P3565)

~~为什么总有人说这是长链剖分板子题？~~

### Solution

题意非常简洁，这让我少了转化题意这一步。

我们考虑什么样的三个点**在树上**满足两两之间距离 $d$ 相等：

1. 对于某一个点，它的子树内以它为LCA，距它 $d$ 的三个点
2. 对于某一个点，它的 $d$ 级祖先以及子树内两个以它为LCA，距它 $d$ 的点

那么我们选择用树形DP。

对于情况1，设 $f_{i,j}$ 表示以 $i$ 为根的子树中，距 $i$ 距离为 $j$ 的点数。

那么情况2怎么表示比较好？~~看题解~~发现可以用上面提到的 `某一个点` ，即中间点 。

设 $g_{i,j}$ 表示以 $i$ 为根的子树中，两个点到LCA的距离相等（此处用 $d$ 表示），LCA到 $i$ 的距离为 $d-j$ 的**点对**数。

 那么可以得到最朴素的转移：
$$
ans+=g_{i,0},ans+=\sum_{u,v\in son_i,u\not=v}f_{u,j-1}\times g_{v,j+1}$$
$$g_{i,j}+=\sum_{u,v\in son_i,u\not=v}f_{u,j-1}\times f_{v,j-1}$$
$$
f_{i,j}+=\sum_{u\in son_i}f_{u,j-1},g_{i,j}+=\sum_{u\in son_i}g_{u,j+1}
$$
这个转移有的地方比较好想，但是考虑周全还是要谨慎思考的。至于这里面每个转移的含义，画个图会恍然大悟的。

~~讲完了~~

因为是最朴素的，在会枚举子树的两个点的转移中，复杂度显然是会爆炸的。

---

来到第一个优化——利用前缀和的**思想**

考虑将 $i$ 的**一个**新儿子 $u$ 加入树中对 $ans$ 产生的贡献，应该是 $ans+=g_{i,j}\times f_{u,j-1}$ ，因为这个儿子只对之前加入的有贡献（也可以自己模拟插入儿子算算）

同理可以得到： $g_{i,j}+=f_{i,j}\times f_{u,j-1}$ 

那么这五种转移就都是 $O(n)$ 转移的了，时间复杂度就变成了 $O(n^2)$ (´▽`ʃ♡ƪ)

~~完结~~

什么，你说我上面提到了长链剖分？

---

这里是第二次优化——长链剖分

仔细看最后两个转移： $f_{i,j}+=\sum_{u\in son_i}f_{u,j-1},g_{i,j}+=\sum_{u\in son_i}g_{u,j+1}$ 

这样可能不明显，如果只有一个儿子： $f_{i,j}=f_{son,j-1},g_{i,j}=g_{son,j+1}$ 

也就是说，如果只有一个儿子，我们是可以做到直接赋值的

用**指针**写就是 $f_i=f_{son}-1,g_{i}=g_{son}+1$ 

如果是在树上，我们可以进行长链剖分，让重儿子直接赋值，轻儿子和原来一样转移

因为轻儿子都是重链的顶部，所以转移复杂度就是重链长度

那么全局时间复杂度就是 $O(\sum len)=O(n)$ 

正式完结(≧∇≦)ﾉ

### Code

```c++
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long

using namespace std;
const int N=100010;
int n;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

struct edge{
    int to,nxt;
}e[N<<1];
int head[N],cnt;
inline void add(int u,int v){
    e[++cnt].to=v;
    e[cnt].nxt=head[u];
    head[u]=cnt;
}

int h[N],son[N];
void dfs1(int u,int fa){
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==fa) continue;
        dfs1(v,u);
        h[u]=max(h[u],h[v]);
        if(h[v]>h[son[u]]) son[u]=v;
    }
    h[u]=h[son[u]]+1;
}

ll *f[N],*g[N],tmp[N<<2],*id=tmp,ans;//这里是指针
void dfs2(int u,int fa){
    if(son[u]) f[son[u]]=f[u]+1,g[son[u]]=g[u]-1,dfs2(son[u],u);
    f[u][0]=1;ans+=g[u][0];
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==fa||v==son[u]) continue;
        f[v]=id;id+=h[v]<<1;
        g[v]=id;id+=h[v]<<1;
        dfs2(v,u);
        for(int j=0;j<h[v];j++){
            if(j) ans+=f[u][j-1]*g[v][j];
            ans+=g[u][j+1]*f[v][j];
        }
        for(int j=0;j<h[v];j++){
            g[u][j+1]+=f[u][j+1]*f[v][j];
            if(j) g[u][j-1]+=g[v][j];
            f[u][j+1]+=f[v][j];
        }
    }
}

int main(){
    n=read();
    for(int i=1,u,v;i<n;i++){
        u=read();v=read();
        add(u,v);add(v,u);
    }
    dfs1(1,0);
    f[1]=id;id+=h[1]<<1;
    g[1]=id;id+=h[1]<<1;
    dfs2(1,0);
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：小塘空明 (赞：6)

~~这个是n方做法，以后再补长链剖分的~~

很明显到一个点距离相等的三个点两两之间距离相等。

所以我们枚举重心，对子树进行暴力统计,注意统计的顺序。

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long ll;
const ll size=5e3+10;
ll n,ans,tot,mx,d[size],tmp[size],s1[size],s2[size];
ll head[size],ver[size*2],next[size*2];
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
inline void add(ll x,ll y){
	ver[++tot]=y;next[tot]=head[x];head[x]=tot;
}
inline void dfs(ll x,ll fa){
	mx=max(mx,d[x]);
	tmp[d[x]]++;
	for(ll i=head[x];i;i=next[i]){
		ll y=ver[i];
		if(y==fa) continue;
		d[y]=d[x]+1;dfs(y,x);
	}
}
int main(){
	n=read();
	for(ll i=1;i<n;i++){
		ll x=read(),y=read();
		add(x,y);add(y,x);
	}
	for(ll x=1;x<=n;x++){
		memset(s1,0,sizeof(s1));
		memset(s2,0,sizeof(s2));
		for(ll i=head[x];i;i=next[i]){
			ll y=ver[i];mx=0;
			d[y]=1;dfs(y,x);
			for(ll j=1;j<=mx;j++){
				ans+=s2[j]*tmp[j];
				s2[j]+=s1[j]*tmp[j];
				s1[j]+=tmp[j];
			}
			for(ll j=1;j<=mx;j++) tmp[j]=0;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：miaokehao (赞：4)

对于每一个点做一次树形dp，把每个深度的点使用乘法原理：   
```
设f1,f2,f3分别为有1，2，3个距离相同的点的方案数
设f3[k]+=f2[k]*g[k],f2[k]+=f1[k]*g[k],f1[k]+=g[k],g[k]=0;
```
```
#include <bits/stdc++.h>
#define ll long long
#define res register ll
#define N 5001
using namespace std;
ll maxdeep,f3[N],f2[N],f1[N],d[N],n,tot,g[N],deep[N],ans;
bool vis[N];
struct papa{
	ll to,next;
}e[N];
inline ll read(){
   ll s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
inline void add(ll x,ll y){
	e[++tot].to=y;
	e[tot].next=d[x];
	d[x]=tot;
}
inline void dfs(ll now,ll fa){
	maxdeep=max(maxdeep,deep[now]);
	g[deep[now]]++;
	for(res i=d[now];i;i=e[i].next){
		if(e[i].to==fa) continue;
		deep[e[i].to]=deep[now]+1;
		dfs(e[i].to,now);
	}
}
int main(){
	n=read();
	for(res i=1;i<=n-1;i++){
		ll x=read(),y=read();
		add(x,y);
	    add(y,x);
	}
	for(res i=1;i<=n;i++)
	{
		memset(f3,0,sizeof(f3));
		memset(f1,0,sizeof(f1));
		memset(f2,0,sizeof(f2));
	    for(res j=d[i];j;j=e[j].next){
	    	deep[e[j].to]=maxdeep=1;
	    	dfs(e[j].to,i);
	    	for(res k=maxdeep;k>=1;k--)
	    	  f3[k]+=f2[k]*g[k],f2[k]+=f1[k]*g[k],f1[k]+=g[k],g[k]=0;
		}
		for(res k=n;k>=1;k--)
		  ans+=f3[k];
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：破壁人 (赞：4)

很明显这是一道树形DP

用f[i][j]表示i子树中有多少个深度为j的点

g[i][j]表示i子树中有多少到lca距离=d的点对，且lca的深度为d-j。

（这个表述有点难理解，通俗地讲，就是在以i为根能和距离i为j的点组成答案的点对数）

那么容易得到转移方程：

f[x][a]+=f[y][a-1]

g[x][a]+=g[y][a+1]+f[x][a]\*f[y][a]

ans+=f[x][a]\*g[y][a+1]+g[x][a]\*f[y][a-1]

（注意方程顺序，实际操作中于给出顺序不同）

总复杂度是O(n^2)

对于POI原题（n<=5000）是足够了。

但是BZOJ的加强版（n<=100000）就不行了。

如何优化呢？用长链剖分。

发现每个节点的第一次转移就相当于将y的f数组向右移一格，g数组向左移一格。

所以考虑用指针优化这个过程，这样每个点的第一次转移就是O(1)的了。

我们对原树进行长链剖分，对于一个点的长儿子，用指针O(1)转移，其余的暴力转移。

复杂度变成了O(n)







```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
using namespace std;
vector<int> a[100001];
int deep[100001],son[100001],fa[100001],n,cnt;
long long *f[100001],*g[100001],ans,mem[1000010],*now=mem+1;
void dfs1(int o)
{
    deep[o]=0;
    for(int i=0;i<a[o].size();i++)  
        if(a[o][i]!=fa[o])
        {
            fa[a[o][i]]=o;
            dfs1(a[o][i]);
            deep[o]=max(deep[o],deep[a[o][i]]+1);
            if(deep[a[o][i]]>deep[son[o]]) son[o]=a[o][i];
        }
}
void dfs2(int o)
{
    if(son[o])
    {
        f[son[o]]=f[o]+1;
        g[son[o]]=g[o]-1;
        dfs2(son[o]);
    }
    f[o][0]=1;
    ans+=g[o][0];
    for(int i=0;i<a[o].size();i++)  
        if((a[o][i]!=fa[o])&&(a[o][i]!=son[o]))
        {
            int y=a[o][i];
            f[y]=now;
            now+=deep[y]+1;
            g[y]=now+deep[y]+1;
            now+=deep[y]*2+2;
            dfs2(y);
            for(int j=deep[y];j>=0;j--)
            {
                if(j)
                    ans+=f[o][j-1]*g[y][j];
                ans+=g[o][j+1]*f[y][j];
                g[o][j+1]+=f[o][j+1]*f[y][j];
            }
            for(int j=0;j<=deep[y];j++)
            {
                if(j)
                    g[o][j-1]+=g[y][j];
                f[o][j+1]+=f[y][j];
            }
        }
}
int main()
{
    cin>>n;
    deep[0]=-1;
    for(int i=1;i<n;i++) 
    {
        int x,y;
        cin>>x>>y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    dfs1(1);
    f[1]=now;
    now+=deep[1]+1;
    g[1]=now+deep[1]+1;
    now+=deep[1]*2+2;
    dfs2(1);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：yukuai26 (赞：2)

poi2014 hotel

题意：给定一棵树，求3个点俩俩距离相等的个数

$f[i][j]$表示以i为根，距离为j的个数

$g[i][j]$表示2个点距离其lca为d，且其lca距离i为d-j的个数

设y为i儿子

显然

$ans+=g[i][0]$

$ans+=g[i][j]*f[y][j-1]$

$f[i][j]+=f[y][j-1]$

$g[i][j]=g[y][j+1]$

然而我们就可以余快地n^2dp了

但是，b站上有个n<=10w的加强版

这时就需要长链剖分了

我们发现一次合并需要的是深度的较小值，而父亲节点第一次能o(1)继承一个子儿子

这时候我们将最长的儿子为重儿子就可以做到o(n)了

证明，易证（雾）

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
#define M 200005
#define inf 1000000005
#define mod 1000000007
#define put putchar('\n')
#define dg putchar('x')
#define int ll
#define db double
#define eps 1e-5
using namespace std;
inline int read(){char c=getchar();int tot=1;while ((c<'0'|| c>'9')&&c!='-') c=getchar();if (c=='-'){tot=-1;c=getchar();}
int sum=0;while (c>='0'&&c<='9'){sum=sum*10+c-'0';c=getchar();}return sum*tot;}
inline void wr(int x){if (x<0) {putchar('-');wr(-x);return;}if(x>=10)wr(x/10);putchar(x%10+'0');}
inline void wrn(int x){wr(x);put;}inline void wri(int x){wr(x);putchar(' ');}
int l,u,cnt,x,y,n,m,ans,dis[N],fa[N],mx[N],son[N];
struct xx{
	db add,max;
}tree[M*4];
int f[N],num[N];
int Next[N*2],head[N],to[N*2],nedge;
db pd,lon[N*2],v1;
void add(int a,int b,db c){Next[++nedge]=head[a];head[a]=nedge;to[nedge]=b;lon[nedge]=c;}
void dfs(int x){
	dis[x]=dis[fa[x]]+1;
	mx[x]=x;
	for (int i=head[x];i;i=Next[i]){
		if (to[i]!=fa[x]) {fa[to[i]]=x,dfs(to[i]);if (dis[mx[to[i]]]>dis[mx[x]]) mx[x]=mx[to[i]];son[x]=to[i];}
	}
}
#define V to[i]
//f[i]表示i的起始位置 ,num[i]表示i需要多少 
void init(int x){	
	if (!f[x]) f[x]=cnt,cnt+=num[x];
	else if (f[x]+num[x]>cnt) cnt=f[x]+num[x]; 
	if (son[x]) f[son[x]]=f[x]+1,init(son[x]);
	for (int i=head[x];i;i=Next[i]){
		if (V==fa[x]||V==son[x]) continue;
		init(V);
	}
}
void build(int x,int l,int r){
	tree[x].max=-inf;tree[x].add=0;
	if (l==r) return;
	int mid=(l+r)>>1;
	build(x*2,l,mid);build(x*2+1,mid+1,r);
}
void change(int x,int k,db p,int l,int r){
	p-=tree[x].add;
	if (l==r){
		tree[x].max=p;return;
	}
	int mid=l+r>>1;
	if (k<=mid) change(x*2,k,p,l,mid);
	else change(x*2+1,k,p,mid+1,r);
	tree[x].max=max(tree[x*2].max+tree[x*2].add,tree[x*2+1].max+tree[x*2+1].add);
}
db get_max(int x,int l,int r,int l1,int r1){
	if (l>r) return -inf;
	if (l==l1&&r==r1) return tree[x].add+tree[x].max;
	int mid=l1+r1>>1;
	if (r<=mid) return get_max(x*2,l,r,l1,mid)+tree[x].add;
	else if (l>mid) return get_max(x*2+1,l,r,mid+1,r1)+tree[x].add;
	return max(get_max(x*2,l,mid,l1,mid),get_max(x*2+1,mid+1,r,mid+1,r1))+tree[x].add; 
}
void tadd(int x,int l,int r,db k,int l1,int r1){
	if (l1==l&&r1==r){
		tree[x].add+=k;return;
	}
	int mid=l1+r1>>1;
	if (r<=mid) tadd(x*2,l,r,k,l1,mid);
	else if (l>mid) tadd(x*2+1,l,r,k,mid+1,r1);
	else tadd(x*2,l,mid,k,l1,mid),tadd(x*2+1,mid+1,r,k,mid+1,r1);
	tree[x].max=max(tree[x*2].max+tree[x*2].add,tree[x*2+1].max+tree[x*2+1].add);
}
void dfs2(int x){
	change(1,f[x],0,1,cnt);
	if (son[x]){
		dfs2(son[x]);		
//		printf("%.3lf %d\n",get_max(1,4,4,1,cnt),x);
		for (int i=head[x];i;i=Next[i])
		if (V==son[x])
		tadd(1,f[x]+1,f[x]+num[x]-1,lon[i],1,cnt);
//		printf("%.3lf %d %d %d \n",get_max(1,4,4,1,cnt),x,f[x]+1,f[x]+num[x]-1);
	}
	if (num[x]>l) pd=max(pd,get_max(1,f[x]+l,f[x]+min(num[x]-1,u),1,cnt));
	//转移时f[i][j]=f[p][j-1],g[i][j]=g[i][j+1],即f右移一位，j左移一位 
	for (int i=head[x];i;i=Next[i]){
		if (V==son[x]||V==fa[x]) continue;
		dfs2(V);
		for (int j=min(u-1,num[V]-1);~j;j--){
			if (j+num[x]>=l) pd=max(pd,lon[i]+get_max(1,f[V]+j,f[V]+j,1,cnt)+get_max(1,f[x]+max((ll)0,l-j-1),f[x]+min(num[x]-1,u-j-1),1,cnt));
		}
		for(int j=1;j<=min(u,num[V]);j++)
        {
        	db t1=get_max(1,f[x]+j,f[x]+j,1,cnt),t2=get_max(1,f[V]+j-1,f[V]+j-1,1,cnt)+lon[i];
        	if (t2>t1) change(1,f[x]+j,t2,1,cnt);
        }
	}
}
bool check(db x){
	for (int i=1;i<=nedge;i++) lon[i]-=x;
	pd=-100;build(1,1,cnt);
	dfs2(1);
	for (int i=1;i<=nedge;i++) lon[i]+=x;
	return pd>=-(1e-5);
}
signed main(){
//	freopen(".in","r",stdin);freopen(".out","w",stdout);
	n=read();dis[0]=-1;l=read();u=read();cnt=1;
	for (int i=1;i<n;i++){
		x=read();y=read();v1=read();add(x,y,v1);add(y,x,v1);
	}
	dfs(1);
	for (int i=1;i<=n;i++) num[i]=dis[mx[i]]-dis[i]+1;
	init(1); 
	if (cnt!=n+1) return 0;
	db L=0,r=1e9;
	while (r-L>eps){
		db mid=(L+r)/2;
		if (check(mid)) L=mid;
		else r=mid;
	}
	printf("%.3lf",L);
	return 0;
}
```

另外wc2010也可以用这个弄过去，二分+线段树即可

---

## 作者：Nateiru (赞：2)

### [P3565 \[POI2014\]HOT-Hotels](https://www.luogu.com.cn/problem/P3565)
 [参考题解](https://www.luogu.com.cn/blog/jasony/p3565-poi2014hot-hotels)

>  题目大意：
>  给定一棵树，在树上选 3 个点，要求两两距离相等，求方案数。
>  
三个点树上两两距离为d存在下面两种情况

 - 某个点三个子树（保证该点是LCA）中分别由三个点距离它为d
 - 对于某一个点，它的 d 级祖先以及子树内两个以它为LCA，距它 d 的点

对于情况一，设计dp： $f_{u,j}$表示以$u$为根的子树，距i距离为$j$的点数

对于情况二，设计dp：$g_{u,j}$表示以$u$为根的子树，两个点的到LCA距离相等（此出用d表示），LCA到$u$的距离为$d-j$的**点对**

对于$f_{u,j}$的状态转移十分显然：$f_{u,j}=\sum_{v\in son_u }f_{v,j-1}$


而对于$g_{u,j}$来说存在两种情况

 - 某个子树内部存在两个点：$g_{u,j}=\sum_{v\in son_u}g_{v,j+1}$
 - 两个不同的子树各贡献一个点，以$u$为LCA：$g_{u,j}=\sum_{v,w\in son_u,v \ne w} f_{v,j-1}×f_{w,j-1}$

很明显，第二中情况$f_{v,j-1}×f_{w,j-1}, f_{w,j-1}×f_{v,j-1}$是同一种情况，这里我们让$v$是$u$**较靠前**的儿子即可避免重复计算

而对于答案计算来说也存在两种情况：
首先对于三个点**树上两两距离为d**的情况都可以看成两个点在一个子树中，而另一个点“**别处**”

 - 在子树$v$中选一个点，而在**其他子树**中选两个点：$g_{u,j+1}×f_{v,j}$
 - 在子树$v$中选两个点，而在**其他子树**中选一个点：$f_{u,j-1}×g_{v,j}$

同样为了避免重复计算只需要让**其他子树**搞成$v$前面的子树即可
注意上述$g_{u,j+1}$和$f_{u,j-1}$都还未算$v$对其的贡献，这个只需要先计算答案在加贡献即可。

计算状态数组和答案时，都有计算前面子树的情况，直接运用前缀和的思想即可边计算答案，边转移数组。

这里要提一点，我们至今没有提到$g_{u,0}$对答案的贡献，它确实对答案有贡献，但是我们**已经计算过了**，如果在此加上会重复计算。

而其他博主在计算的时候加上$g_{u,0}$**实际上**增加的时$g_{wson,1}$即重儿子的贡献。

根据g的转移方程可知道：$g_{u,0}$的贡献**全部**来自于$\sum_{v\in son_u}g_{v,1}$，而计算$f_{u,j-1}×g_{v,j}$对答案的贡献时我们具体写一下$f_{u,0}×g_{v,1}$而$f_{u,0}=1$，因此已经计算过$g_{u,0}$的贡献！！！
* * *
然后就是长链剖分优化dp，每次保存长儿子的贡献，其他儿子暴力合并，每条长链都会在链头暴力合并一次时间复杂度$O(len)$总的合并时间复杂度$O(n)$

最后如果写指针版本的话，由于g数组是倒着转移的，$f$要多开一倍的内存，否则g可能倒回来覆盖掉$f$
### code
```cpp
#define IO ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr)
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
using ll=long long;
constexpr int N=5010;
int h[N],e[2*N],ne[2*N],idx;
void add(int a,int b){e[idx]=b,ne[idx]=h[a],h[a]=idx++;}
int n;
int dep[N],son[N];
void dfs1(int u,int fa)
{
    for(int i=h[u];i!=-1;i=ne[i])
    {
        int v=e[i];
        if(v==fa) continue;
        dfs1(v,u);
        if(dep[v]>dep[son[u]]) son[u]=v;
    }
    dep[u]=dep[son[u]]+1;
}

ll pool[4*N];
ll *f[N],*g[N],*now=pool;
ll ans;
void dfs2(int u,int fa)
{
    f[u][0]=1;
    if(son[u])
    {
        f[son[u]]=f[u]+1;
        g[son[u]]=g[u]-1;
        dfs2(son[u],u);
        ans+=g[son[u]][1];// 加上重儿子的贡献
    }
    for(int i=h[u];i!=-1;i=ne[i])
    {
        int v=e[i];
        if(v==fa||v==son[u]) continue;
        f[v]=now;now+=dep[v]<<1;
        g[v]=now;now+=dep[v];
        dfs2(v,u);
        // 边计算
        for(int j=0;j<dep[v];j++)
        {
            if(j) ans+=f[u][j-1]*g[v][j];
            ans+=g[u][j+1]*f[v][j];
        }
        // 边转移
        for(int j=0;j<dep[v];j++)
        {
            g[u][j+1]+=f[u][j+1]*f[v][j];
            if(j) g[u][j-1]+=g[v][j];
            f[u][j+1]+=f[v][j];
        }
    }
    
}
int main()
{
    IO;
    cin>>n;
    memset(h,-1,sizeof h);
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs1(1,0);
    f[1]=now;now+=dep[1]<<1;//多开一倍的内存
    g[1]=now;now+=dep[1];
    dfs2(1,0);
    cout<<ans<<'\n';
    return 0;
}
```
菜菜的我搞了一天这个题啊啊啊啊


---

## 作者：foreverlasting (赞：2)

[题面](https://www.luogu.org/problemnew/show/P3565)

[加强版](https://www.lydsy.com/JudgeOnline/problem.php?id=4543)

长链剖分。

长链剖分模板题。首先考虑DP，$f[i][j]$表示以$i$为根的子树中离$i$距离为$j$的节点个数，$g[i][j]$表示以$i$为根的子树中存在两个点离这两个点的$lca$的距离一样（假设为$d$），$lca$离$i$距离为$d-j$的结点对个数。$ans$表示最终答案。转移方程也很好写。$f[i][j]+=f[tox][j-1],g[i][j]+=g[tox][j+1]+f[i][j]*f[tox][j],ans+=f[i][j]*g[i][j]$。然后再把转移方程写得好看一点，先处理$ans$，再处理$f$和$g$。

那么就是$ans+=f[i][j]*g[tox][j+1]+g[i][j]*f[tox][j-1],g[i][j+1]+=f[i][j+1]*f[tox][j],g[i][j-1]+=g[tox][j],f[i][j+1]+=f[tox][j]$

这是$O(n^2)$的。发现转移方程的下标是深度，所以长链剖分一下就好了。

code:
```
//2018.9.12 by ljz
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
const int N=1e5+10;
namespace MAIN{
    int n;
    struct E{
        int next,to;
        E() {}
        E(res next,res to):next(next),to(to) {}
    }edge[N<<1];
    int head[N],cnt;
    inline void addedge(res u,res v){
        edge[++cnt]=E(head[u],v),head[u]=cnt;
        edge[++cnt]=E(head[v],u),head[v]=cnt;
    }
    int fa[N],dep[N],maxdep[N],son[N];
    void dfs(res x,res fax,res depx){
        fa[x]=fax,dep[x]=maxdep[x]=depx;
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(tox==fax)continue;
            dfs(tox,x,depx+1);
            maxdep[x]=_max(maxdep[x],maxdep[tox]);
            if(maxdep[tox]>maxdep[son[x]])son[x]=tox;
        }
    }
    LL ans;
    LL *f[N],*g[N],tmp[N<<5],*now=tmp+1;
    inline void Dp(res x){
        f[x]=now,now+=(maxdep[x]-dep[x]+1)<<1,g[x]=now,now+=(maxdep[x]-dep[x]+1)<<1;
    }
    void DP(res x){
        if(son[x])f[son[x]]=f[x]+1,g[son[x]]=g[x]-1,DP(son[x]);
        f[x][0]=1,ans+=g[x][0];
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(tox==fa[x]||tox==son[x])continue;
            Dp(tox);
            DP(tox);
            for(res j=maxdep[tox]-dep[tox];~j;j--){
                if(j)ans+=f[x][j-1]*g[tox][j];
                ans+=f[tox][j]*g[x][j+1];
                g[x][j+1]+=f[x][j+1]*f[tox][j];
            }
            for(res j=0;j<=maxdep[tox]-dep[tox];j++){
                if(j)g[x][j-1]+=g[tox][j];
                f[x][j+1]+=f[tox][j];
            }
        }
    }
    inline void MAIN(){
        memset(head,-1,sizeof(head));
        n=read();
        for(res i=1;i<n;i++){
            res u=read(),v=read();
            addedge(u,v);
        }
        dfs(1,0,1);
        Dp(1);
        DP(1);
        printf("%lld\n",ans);
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：Galois_Field_1048576 (赞：1)

## 补充证明

题解区有一些题解用到了这样一个结论：

> 对于树 $\Gamma = (V, E)$，$u, v, w \in V$ 使得 $\mathrm d(u, v) = \mathrm d(v, w) = \mathrm d(u, w)$，则存在 $c$ 使得 $\mathrm d(c, u) = \mathrm d(c, v) = \mathrm d(c, w)$。

但是均没有给出证明。下面是一个证明：

设点 $x$ 使得 $\mathrm d(u, x) + \mathrm d(v, x) + \mathrm d(w, x)$（记为 $A(x)$）最小。将 $\Gamma$ 按照 $x$ 为根变为一棵有根树，则我们有 $\mathrm{lca}(u, v) = \mathrm{lca}(v, w) = \mathrm{lca}(u, w) = x$（否则若其中一个不为 $x$，记为 $y$，则将 $x$ 改为 $y$ 会将 $A(x)$ 的两项减少 $1$，一项增加 $1$，与 $x$ 使得 $A(x)$ 最小矛盾），这样根据 $\mathrm{d}(u, v) = \mathrm{dep}(u) + \mathrm{dep}(v) - 2 \mathrm{dep}(\mathrm{lca}(u, v))$，可知 $\mathrm{dep}(u) + \mathrm{dep}(v) = \mathrm{dep}(u) + \mathrm{dep}(w) = \mathrm{dep}(v) + \mathrm{dep}(w)$，适当变形可知 $\mathrm{dep}(u) = \mathrm{dep}(v) = \mathrm{dep}(w)$，即 $\mathrm d(x, u) = \mathrm d(x, v) = \mathrm d(x, w)$


## 本题解法
对于一个 $\mathrm d(u, v) = \mathrm d(v, w) = \mathrm d(u, w)$ 的三元组 $(u, v, w)$，考虑上述证明构造的 $A$ 函数，则 $A(x)$ 最小的 $x$ 唯一。（证明：考虑到使得 $A(x)$ 最小的 $x$，必然是 $u \to v$ 唯一路径的中点。）

因此考虑枚举这个 $x$ 作为根，因此我们只需要考虑三元组 $(u, v, w)$，使得：

* 不存在 $y \in \mathrm{child}(x)$，使得 $u, v, w$ 中有至少两个属于 $\mathrm{subtree}(y)$。
* $u, v, w$ 的深度相同。

对于枚举的特定深度 $\delta$，考虑 $E_y~(y \in \mathrm{child}(x))$ 为 $y$ 的子树内深度为 $\delta$ 的点的个数，因此我们需要计算
$$
\sum_{\{a, b, c\} \subseteq \mathrm{child}(x), |\{a, b, c\}| = 3} E_a E_b E_c.
$$
首先尝试将 $3$ 换成 $2$，不难发现答案为
$$
\sum_{i} A_i \left(\sum_{j < i} A_j\right),
$$
动态维护 $\sum\limits_{j<i}A_j$ 即可。这启发我们如果考虑
$$\Sigma_0(i) = 1,\Sigma_1(i) = \sum\limits_{j < i}A_j \Sigma_0(j), \Sigma_2(i) = \sum_{j < i} A_j \Sigma_1(j),\Sigma_3(i) = \sum_{j < i} A_j \Sigma_2(j),$$
则 $\Sigma_3$ 就是答案。而动态地维护各个 $\Sigma_k(i)$ 即可。

注意到对于每个根 $x$，每个点只会被统计一次，所以时间复杂度是 $\Theta(n^2)$ 的，可以通过。

---

## 作者：傅天宇 (赞：1)

[luogu's link](https://www.luogu.com.cn/problem/P3565)

#### 题意：

给定一棵树，在树上选 $3$ 个点，要求两两距离相等，求方案数。

#### Solution：

来个题解区没有的做法。

我们可以枚举中间点，枚举中间点的子树，再枚举下距离。

考虑子树的个数：

$3$ 个：对答案的贡献即为 $x_1 \times x_2 \times x_3$

$4$ 个：对答案贡献为 $x_1 \times x_2 \times x_3+x_1 \times x_2 \times x_4+x_1 \times x_3 \times x_4+x_2 \times x_3 \times x_4$，即在 $3$ 个的基础上增加  $x_4\times (x_1\times x_2+x_1\times x_3+x_2\times x_3)$。

同理可得 $5$ 个时，在 $4$ 个的基础上增加 $x_5\times(x_1\times x_2+x_1\times x_3+x_1\times x_4+x_2\times x_3+x_2\times x_4+x_3\times x_4)$。

增加的用 $sum2$ 维护。

$x_4\times (x_1\times x_2+x_1\times x_3+x_2\times x_3) \Rightarrow x_5\times(x_1\times x_2+x_1\times x_3+x_1\times x_4+x_2\times x_3+x_2\times x_4+x_3\times x_4)$，增加了 $x_5\times(x_1+x_2+x_3)$，再用 $sum1$ 维护即可。

#### Code：

```cpp
/*
 * @Author: FuTianyu 
 * @Date: 2020-11-08 18:44:32 
 * @Last Modified by: FuTianyu
 * @Last Modified time: 2020-11-08 19:18:09
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(i,a,b) for(int i=a;i>=b;i--)
/*
快读快输
*/
const int N=5e3+5;
int n,fir[N],tot;
struct edge{
	int nxt,to;
}e[N<<1];
void add(int u,int v){
	e[++tot]={fir[u],v};
	fir[u]=tot;
	e[++tot]={fir[v],u};
	fir[v]=tot;
}
int MaxDeep,dep[N],Ans,sum1[N],sum2[N];
void dfs(int u,int dad,int Deep){
	MaxDeep=max(MaxDeep,Deep+1);
	dep[Deep]++;
	for(int i=fir[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==dad) continue;
		dfs(v,u,Deep+1);
	}
}
void work(int u){
	for(int i=fir[u];i;i=e[i].nxt){
		int v=e[i].to;
		MaxDeep=1;
		dfs(v,u,1);
		FOR(j,1,MaxDeep){
			Ans+=sum2[j]*dep[j];
			sum2[j]+=dep[j]*sum1[j];
			sum1[j]+=dep[j];
			dep[j]=0;
		}
	}
}
signed main(){
	n=read();
	FOR(i,1,n-1) add(read(),read());
	FOR(i,1,n){
		memset(sum1,0,sizeof sum1);
		memset(sum2,0,sizeof sum2);
		work(i);
	}
	write(Ans);
	return 0;
}
```



---

## 作者：LCuter (赞：1)

## [POI2014]Hot-Hotels 题解

##### $\text{Description}$

给定一棵树，求树上存在多少个三元组 $(a,b,c)$，满足 $\operatorname{dis}(a,b)=\operatorname{dis}(a,c)=\operatorname{dis}(b,v)$。

$n\le 10^5$

##### $\text{Solution}$

为了将来优化复杂度，我们先以 $1$ 为根。考虑满足条件的三元组会呈现什么样的形态：

![](https://lcuter.gitee.io/picture/Picture/clpf1.png)

对于第一种情况，我们容易想到令 $f_{i,j}$ 表示 $i$ 的子树中到 $i$ 距离为 $j$ 的节点个数。但是直接对每个节点的每个深度进行统计会重复，我们先来考虑第二种情况。考虑令 $g_{i,j}$ 表示 $i$ 的子树中，有多少二元组 $(a,b)$ 满足 $\operatorname{dis}(\operatorname{LCA}(a,b),a)=\operatorname{dis}(\operatorname{LCA(a,b),b})=\operatorname{dis}(\operatorname{LCA}(a,b),i)+j$。那么第一种情况可以看成：

![](https://lcuter.gitee.io/picture/Picture/clpf2.png)

这样的话，只需保证左边的节点和右边两个节点不在某一个点的同一个儿子的子树内，那么就不会被重复统计。

那么，节点 $now$ 对答案的贡献应是：

$$g_{now,0}+\sum_{j}\sum_{x,y\in son(now)}f_{x,j-1}\cdot g_{y,j+1}$$

上式的主要问题在于，我们要让左节点和右二节点不在同一个儿子的子树内，所以需要枚举不同的儿子进行统计，那么深度那一维也需要发生相应的改变。

$f$ 的转移比较容易：

$$f_{now,j}=\sum_{x\in son(now)}f_{x,j-1}$$

接下来考虑 $g$ 的转移。我们发现，$g$ 可以有两种从儿子转移的方式：

![](https://lcuter.gitee.io/picture/Picture/clpf3.png)

对于第一种情况，其实就是 $j$ 少了一个。对于第二种情况，发现 $\operatorname{LCA}(a,b)=now$，那么 $\operatorname{dis}(\operatorname{LCA}(a,b),a)=\operatorname{dis}(\operatorname{LCA}(a,b),b)=j$，然后 $now$ 到它本身的距离显然为 $0$，故就差了 $j$，于是有：

$$g_{now,j}=\sum_{x,y\in son(now),x\neq y}f_{x,j-1}\cdot f_{y,j-1}+\sum_{x\in son(now)}g_{x,j+1}$$

这样的话，我们得到了一个 $O(n^2)$ 的动态规划方程，但是要想达到这个复杂度需要用到前缀和，具体参考代码。

然后发现以深度为下标的话，可以使用长链剖分优化至 $O(n)$。具体请参考代码及代码注释。

##### $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define REG register
#define MAXN 100005
#define LL long long
#define FORE(i,now) for(REG int i=head[now];i;i=ed[i].nxt)
using namespace std;
inline int read(){
    REG int x(0);
    REG char c=getchar();
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)) x=(x*10)+(c^48),c=getchar();
    return x;
}

struct Edge{
    int v,nxt;
}ed[MAXN<<1];
int head[MAXN],cnt;
inline void adde(int u,int v){ed[++cnt]=(Edge){v,head[u]},head[u]=cnt;}
inline void add(int u,int v){adde(u,v),adde(v,u);}

int n;

LL *f[MAXN],*g[MAXN],*p,G[MAXN<<2],ans;
int Son[MAXN],Len[MAXN];

void dfs1(int now,int fa){
    FORE(i,now){
        int v=ed[i].v;
        if(v==fa) continue;
        dfs1(v,now);
        if(Len[v]>Len[Son[now]]) Son[now]=v;
    }
    Len[now]=Len[Son[now]]+1;
}

inline void Assign(int now){f[now]=p,p+=Len[now]<<1,g[now]=p,p+=Len[now]<<1;}

void dfs2(int now,int fa){
    if(Son[now])
        f[Son[now]]=f[now]+1,g[Son[now]]=g[now]-1,dfs2(Son[now],now);
    f[now][0]=1,ans+=g[now][0];
    FORE(i,now){
        int v=ed[i].v;
        if(v==fa||v==Son[now]) continue;
        Assign(v),dfs2(v,now);
        for(REG int j=0;j<Len[v];++j){
            if(j) ans+=f[now][j-1]*g[v][j]; // 这里含 now 的实际上是之前遍历过的儿子的 f[son][j-2] 之和 
            ans+=g[now][j+1]*f[v][j]; // 考虑到上式的前缀和没有计算后者，这里实际上就是在计算后者 
        }
        for(REG int j=0;j<Len[v];++j){
            g[now][j+1]+=f[now][j+1]*f[v][j];
            if(j) g[now][j-1]+=g[v][j];
            f[now][j+1]+=f[v][j];
        }
    }
}

void Work(){
    n=read();
    for(REG int i=1;i<n;++i)
        add(read(),read());
    dfs1(1,0);
    p=G,Assign(1);
    dfs2(1,0);
    printf("%lld\n",ans);
}

int main(){
    Work();
}
```


---

## 作者：zhouenji (赞：1)

这道题还是有难度；就在于公式很难推，其实也不是很难想，只是代码处理有点烦，

废话不多说，直接上思路：我们在考虑方案个数的时候，肯定要以每一个点作为根，于是我们就可以先dfs一遍找出以x为根的子树对答案的贡献

那么剩下的就是以x为根的子树和它父亲对答案的贡献，于是我们第二遍dfs就可以来解决这个问题

我们用dp【i】【j】【k】表示以x为根的树的节点中距离x  j个单位长度的节点中选出k个的方案数

然后就上代码：

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=5000+10;
struct nod
{
    int next,to;
}e[maxn*2];
long long n,m,k=1,ans;
long long head[maxn];
int dp[maxn][maxn][3];
void adde(int u,int v)
{
    e[++k].next=head[u];
    e[k].to=v;head[u]=k;
}
void dfs1(int x,int f)
{
    dp[x][0][1]=1;
    for(int i=head[x];i;i=e[i].next)
    {
        if(e[i].to==f)continue;
        dfs1(e[i].to,x);
        for(int j=1;dp[e[i].to][j-1][1]!=0;j++)
        {
            ans+=dp[x][j][2]*dp[e[i].to][j-1][1];
            dp[x][j][2]+=dp[x][j][1]*dp[e[i].to][j-1][1];
            dp[x][j][1]+=dp[e[i].to][j-1][1];
        }
    }
}
void dfs2(int x,int f)
{
    if(x!=1)
    {
        int h=1;
        for(int i=1;dp[f][i-1][1] && dp[x][i][1];i++)
        {
            if(i==1)ans+=dp[x][i][2]*dp[f][i-1][1];
            else ans+=dp[x][i][2]*(dp[f][i-1][1]-dp[x][i-2][1]);h=i;
        }
        for(int i=h;i>=1;i--)
        {
            if(i==1)dp[x][i][2]+=dp[x][i][1],dp[x][i][1]+=dp[f][i-1][1];
            else dp[x][i][2]+=dp[x][i][1]*(dp[f][i-1][1]-dp[x][i-2][1]),dp[x][i][1]+=(dp[f][i-1][1]-dp[x][i-2][1]);
        }
    }
    for(int i=head[x];i;i=e[i].next)
    {
        if(e[i].to==f)continue;
        dfs(e[i].to,x);
    }
}
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);adde(u,v);adde(v,u);
    }dfs1(1,1);dfs2(1,1);printf("%lld\n",ans);
}
```

---

