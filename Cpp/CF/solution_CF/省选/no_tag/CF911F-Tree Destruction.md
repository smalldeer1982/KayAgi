# Tree Destruction

## 题目描述

You are given an unweighted tree with $ n $ vertices. Then $ n-1 $ following operations are applied to the tree. A single operation consists of the following steps:

1. choose two leaves;
2. add the length of the simple path between them to the answer;
3. remove one of the chosen leaves from the tree.

Initial answer (before applying operations) is $ 0 $ . Obviously after $ n-1 $ such operations the tree will consist of a single vertex.

Calculate the maximal possible answer you can achieve, and construct a sequence of operations that allows you to achieve this answer!

## 样例 #1

### 输入

```
3
1 2
1 3
```

### 输出

```
3
2 3 3
2 1 1
```

## 样例 #2

### 输入

```
5
1 2
1 3
2 4
2 5
```

### 输出

```
9
3 5 5
4 3 3
4 1 1
4 2 2
```

# 题解

## 作者：mrsrz (赞：15)

我们需要最大化删掉的叶子节点的贡献。

由于无权树上任意一个节点，与它距离最远的节点一定是直径的某个端点，所以把直径的端点求出来，然后对于每个不在直径上的叶子节点，判断哪个端点与它距离较远，加上贡献即可。

最后删到只剩直径时，就一个一个删即可。

时间复杂度$O(n)$。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
struct edge{
	int to,nxt;
}e[N<<1];
int n,dis[N],head[N],cnt=0,u,v,fa[N];
long long ans=0;
bool on[N];
vector<pair<int,int>>s;
void dfs(int now){
	for(int i=head[now];i;i=e[i].nxt)
	if(!~dis[e[i].to]){
		dis[e[i].to]=dis[now]+1;
		dfs(e[i].to);
	}
}
void dfs2(int now){
	for(int i=head[now];i;i=e[i].nxt)
	if(dis[e[i].to]>dis[now]){
		fa[e[i].to]=now;
		dfs2(e[i].to);
		on[now]=on[now]||on[e[i].to];
	}
}
inline void dfs3(int now,int rt){
	for(int i=head[now];i;i=e[i].nxt)
	if(dis[e[i].to]>dis[now])dfs3(e[i].to,on[e[i].to]?e[i].to:rt);
	if(!on[now]){
		if(dis[now]>dis[now]+dis[v]-(dis[rt]<<1)){
			ans+=dis[now];
			s.push_back(make_pair(u,now));
		}else{
			ans+=dis[now]+dis[v]-(dis[rt]<<1);
			s.push_back(make_pair(v,now));
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;++i){
		scanf("%d%d",&u,&v);
		e[++cnt]=(edge){v,head[u]};
		head[u]=cnt;
		e[++cnt]=(edge){u,head[v]};
		head[v]=cnt;
	}
	memset(dis,-1,sizeof dis);
	dis[1]=0;
	dfs(1);
	u=1;
	for(int i=2;i<=n;++i)
	if(dis[i]>dis[u])u=i;
	memset(dis,-1,sizeof dis);
	dis[u]=0;
	dfs(u);
	v=u;
	for(int i=1;i<=n;++i)
	if(dis[v]<dis[i])v=i;
	on[v]=true;
	dfs2(u);dfs3(u,u);
	for(;u!=v;v=fa[v])ans+=dis[v],s.push_back(make_pair(u,v));
	printf("%lld\n",ans);
	for(auto i:s)printf("%d %d %d\n",i.first,i.second,i.second);
	return 0;
}
```

---

## 作者：reyik (赞：9)

## 打了一个上午，终于打完了

补一下输出的翻译：

第一行一个整数，表示最大的距离和。

后面几行，每行三个整数，分别表示：

选择的两个叶子，以及删掉的结点。

好了，接下来是思路。

我们肯定要让两个点尽量远，那么远的点怎么快速求？？

每一次去做一遍dfs显然不够优秀。

我们来回顾一下树的直径的求法。（~~没学过的去补习~~）

找任意一个结点，然后找到离他最远的一个节点，

然后从这个结点开始找最远的点，就好了。

那么，因为任意一个结点都可以得到答案

所以任意一个结点的最远点一定是树的直径的端点的其中一个！！！

然后把剩下的树的直径的结点一个一个统计然后删掉。

具体步骤：

1.找出树的直径。

2.用$vis$数组表示该点是否在树的直径上。更新vis。

3.统计不在直径上的点，比较离树的两个端点的距离，取大的并累加，将两点存入。

4.把在直径上的点距离累加，将两点存入。

代码：

```
#include <iostream>
#include <cstdio>
#include <cstring> 
using namespace std;
struct edge{
    int to,nxt;
}e[400005];
int n,dep[300005],head[300005],father[300005],x1,x2,cnt=0,maxn=0,sum=0,ax[300005],bx[300005];
long long ans=0;
bool vis[300005];
void addedge(int x,int y) {
	e[++cnt].to=y;
	e[cnt].nxt=head[x];
	head[x]=cnt;
}
void dfs(int u){
    for(int i=head[u];i;i=e[i].nxt)
    if(!~dep[e[i].to]){
        dep[e[i].to]=dep[u]+1;
        dfs(e[i].to);
    }
}
void dfs2(int u){
    for(int i=head[u];i;i=e[i].nxt)
    	if(dep[e[i].to]>dep[u]){
        	father[e[i].to]=u;
        	dfs2(e[i].to);
        	vis[u]=vis[u]||vis[e[i].to];
    	}
    return ;
}
inline void dfs3(int u,int v) {
    for(int i=head[u];i;i=e[i].nxt)
    	if(dep[e[i].to]>dep[u]) {
    		if(vis[e[i].to]) dfs3(e[i].to,e[i].to);
    		else dfs3(e[i].to,v);
		}
    if(!vis[u]){
        if(dep[u]>dep[u]+dep[x2]-(dep[v]<<1)) {
            ans+=dep[u];
            ++sum;
            ax[sum]=x1;
            bx[sum]=u;
        }else{
            ans+=dep[u]+dep[x2]-(dep[v]<<1);
            ++sum;
            ax[sum]=x2;
            bx[sum]=u;
        }
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<n;++i) {
    	int a,b;
        scanf("%d%d",&a,&b);
        addedge(a,b);
        addedge(b,a);
    }
    memset(dep,-1,sizeof(dep));
    dep[1]=0;
    dfs(1);
    maxn=0;
    for(int i=2;i<=n;++i) 
		if(dep[i]>maxn) {
			maxn=dep[i];
			x1=i;
		}
    memset(dep,-1,sizeof(dep));
    dep[x1]=0;
	dfs(x1);
	maxn=0;
    for(int i=1;i<=n;++i) {
    	if(dep[i]>maxn) {
    		maxn=dep[i];
    		x2=i;
		}
	}
    vis[x2]=1;
    dfs2(x1);
	dfs3(x1,x1);
    while(x1!=x2) {
		ans+=dep[x2];
		++sum;
		ax[sum]=x1;
		bx[sum]=x2;
		x2=father[x2];
	}
    printf("%lld\n",ans);
    for (int i=1;i<=sum;++i) {
    	printf("%d %d %d\n",ax[i],bx[i],bx[i]);
	}
    return 0;
}

```

---

## 作者：蒟蒻丁 (赞：8)

[更好体验](https://www.cnblogs.com/caijiLYC/p/14375280.html)  
WC讲的第二道例题，被一分钟带过，我裂开了  
首先知道一个比较显然的东西，对于一个点，距离最长的点必定是该树的直径的其中一个端点。  
虽然这个挺显然的，不过还是证一下（老师昨天一秒带过太让人炸裂了）（这里用一个反证法吧）  
![y3y28O.png](https://s3.ax1x.com/2021/02/04/y3y28O.png)  
设 $0,4$ 为直径两端，$5,6$ 为直径外两点  
若 $5->6$ 为最长的链，那么 $1->6$ 会大于 $1->4$  
那么直径就会变成 $0->6$ 这与前提矛盾，所以对于 $5$ ，$4$ 是最优的选择，对 $6$，$0$ 是最优的选择  
然后怎么整呢，我们先把直径搞出来，对于每一个点，选择一个端点使得链最长，最后再按顺序删掉链上的所有点  
然后想一下细节（会的同志可以直接开始写了）  
对于一个点，可能有两种情况（这里使用换根法，没考虑不使用的做法）
* 1.与上面的端点匹配
* 2.与下面的端点匹配
怎么找到最优的端点，还要计算长度呢，我们想到了经典的 $dep_x+dep_y-2*dep_{lca_{x,y}}$  
又想到，因为其中一个端点是在链上的，所以两点的 $lca$也会在链上  
于是我们在 $dfs$ 的时候，记录一个 $top$ ，表示在 $dfs$ 过程中上一个找到的一个在链上的点，这个点一定就是 $lca$了  
这是考虑下面哪个端点，而与上面端点匹配的情况其实我们求过了  
由于是换根法，根节点就是上面的端点，所以直接用 $dep$ 值就好  
啊，本人语文不好，如果看不懂也别慌，结合代码还是比较好懂得

```
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const ll N=2e5+10;
ll n,m,cnt,head[N],dep[N],faa[N],toper;
ll ans,Ans,final_ans,Time;
bool on[N];

struct answer{
	ll a,b,c;
}A[N];

struct star_platinum{
	ll to,nxt;
}q[N*3];

inline void add(ll u,ll v){
	q[++cnt].to=v,q[cnt].nxt=head[u],head[u]=cnt;
	q[++cnt].to=u,q[cnt].nxt=head[v],head[v]=cnt;
}

void dfs1(ll x,ll fa){
	if(Time==0&&dep[x]>dep[ans])ans=x;
	if(Time==1&&dep[x]>dep[Ans])Ans=x;
	for(ll i=head[x];i;i=q[i].nxt){
		ll v=q[i].to;
		if(v!=fa){
			dep[v]=dep[x]+1;
			dfs1(v,x);
		}
	}
}

void dfs2(ll x,ll fa){
	for(ll i=head[x];i;i=q[i].nxt){
		ll v=q[i].to;
		if(v!=fa){
			dfs2(v,x);
			faa[v]=x;
			if(on[v])on[x]=1;
		}
	}
}

void dfs3(ll x,ll fa,ll topf){
	for(ll i=head[x];i;i=q[i].nxt){
		ll v=q[i].to; 
		if(fa!=v){
			if(on[v])dfs3(v,x,v);
			else dfs3(v,x,topf);
		}
	}
	if(!on[x]){
		if(dep[x]>dep[x]+dep[Ans]-(dep[topf]*2)){
			final_ans+=dep[x];
			A[++toper]=(answer){x,ans,x};
		}
		else {
			final_ans+=dep[x]+dep[Ans]-(dep[topf]*2);
			A[++toper]=(answer){Ans,x,x};
		}
	}
}

int main(){
	scanf("%lld",&n);
	for(ll a1,a2,i=1;i<n;i++){
		scanf("%lld%lld",&a1,&a2);
		add(a1,a2);
	}
	dfs1(1,0);
	memset(dep,0,sizeof(dep)),Time++;
	dfs1(ans,0);
	on[Ans]=1;
	dfs2(ans,0);
	dfs3(ans,0,ans);
	for(ll i=Ans;i!=ans;i=faa[i]){
		final_ans+=dep[i];
		A[++toper]=(answer){ans,i,i};
	}
	printf("%lld\n",final_ans);
	for(ll i=1;i<=toper;i++){
		printf("%lld %lld %lld\n",A[i].a,A[i].b,A[i].c);
	}
}

```


---

## 作者：jun头吉吉 (赞：7)

## 题意
给出一棵树，执行$n-1$次如下操作
- 选择两个叶子结点
- 加上这两点的距离
- 删去其中的一个点

请求出距离之和的最大值
## 题解
一道灰常神奇的贪心题

很明显，对于$n-1$次操作，我们都希望其距离最大，但是前面的操作似乎会影响后面的操作，那该这么办呢？（雾

我们知道，对于一个点$x$，其贡献最大为$max(dis_{x\to\text{直径的一端}},dis_{x\to\text{直径的另一端}})$，我们稍微来证明一下：

对于任意不在直径上的两点$e,f$，都能转换为一条直径和两条从$e,f$到直径的简单路径，如下图所示（$a,b$为直径两端点）
![一张神奇的图片](https://cdn.luogu.com.cn/upload/image_hosting/u0zza8vl.png)


那么，根据直径的性质$dis_{a\to d}\leq dis_{e\to d}$，即
$$dis_{a\to b}+dis_{b\to d}\leq dis_{e\to b}+dis_{b\to d} \ \Rightarrow dis_{a\to b} \leq dis_{e\to b}$$

同理可得，$dis_{c\to f}\leq dis_{c \to d}$
因此，$e$的最大贡献为$max(dis_{e\to a},dis_{e\to d})$

知道了这个性质，我们就可以构造答案了，即
1. 对于不在直径上的点，直接构造到直径更远的一端即可
1. 对于在直径上的点，那就直接删去到某一端即可

但是我们发现，答案是有顺序要求的，所以我们需要以某种顺序构造答案，我的方法是这样的：

1. 把直径上的点加入队列
1. 对队列里的点进行搜索并加入某种数据结构
1. 倒叙输出答案

### 为什么这是正确的？？

广搜保证了处理的点离直径的距离是递增的，那么我们倒着输出，就很好的确保了删去$x$的时候，它后面的节点已经删完了。那么很明显这就是正确的
## ~~乱打的~~代码
```cpp
#include<bits/stdc++.h>
namespace in{
	char buf[1<<21],*p1=buf,*p2=buf;
	inline int getc(){
	    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
	}
	template <typename T>inline void read(T& t){
	    t=0;int f=0;char ch=getc();
	    while (!isdigit(ch)){
	        if(ch=='-')f = 1;
	        ch=getc();
	    }
	    while(isdigit(ch)){
   	    	t=t*10+ch-48;
   	    	ch = getc();
   		}
		if(f)t=-t;
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args){
	    read(t);read(args...);
	}
}
namespace out{
	char buffer[1<<21];
	int p1=-1;
	const int p2 = (1<<21)-1;
	inline void flush() {
		fwrite(buffer,1,p1+1,stdout),
		p1=-1;
	}
	inline void putc(const char &x) {
		if(p1==p2)flush();
		buffer[++p1]=x;
	}
	template <typename T>void write(T x) {
		static char buf[15];
		static int len=-1;
		if(x>=0){
			do{
    			buf[++len]=x%10+48,x/=10;
    		}while (x);
		}else{
    		putc('-');
			do {
    			buf[++len]=-(x%10)+48,x/=10;
			}while(x);
		}
		while (len>=0)
			putc(buf[len]),--len;
	}
}
using namespace std;
const int maxn=2e5+1000;
struct node{int v,nxt;}e[maxn<<1];
int cnt=0,head[maxn];
void add(int u,int v){e[++cnt]=(node){v,head[u]};head[u]=cnt;}
int dis[maxn],fath[maxn],maxp;
bool flag[maxn];//直径标记 
int n,u,v;long long sum; 
struct nnn{int a,b,c;nnn(int A=0,int B=0,int C=0){a=A,b=B,c=C;}};
vector<nnn>ans;
queue<nnn>q;
int st,ed;
#define v e[i].v
void dfs1(int u,int fa){
	//用来找最远的点
	//printf("%d %d\n",u,fa); 
	if(dis[u]>dis[maxp])maxp=u;fath[u]=fa; 
	for(int i=head[u];i;i=e[i].nxt){
		if(v==fa)continue;
		dis[v]=dis[u]+1;dfs1(v,u);
	}
}
void dfs2(int u){
	q.push(nnn(u,dis[u],dis[ed]-dis[u]));
	for(int i=head[u];i;i=e[i].nxt)
	if(flag[v]&&fath[u]!=v)dfs2(v);
}
#undef v
#define mp make_pair
#define pb push_back
signed main(){
	in::read(n);
	for(int i=1;i<n;i++)in::read(u,v),add(u,v),add(v,u);
	dis[maxp=0]=0,dfs1(1,-1);
	st=maxp;//找到直径起点 
	dis[st]=dis[maxp=0]=0,dfs1(st,-1);
	ed=maxp;//找到直径终点
	int _tmp=maxp;
	while(_tmp!=st)flag[_tmp]=true,_tmp=fath[_tmp];
	flag[st]=true;
	dfs2(st);
	while(!q.empty()){
		#define v e[i].v
		nnn tmp=q.front();q.pop();
		//printf("%d %d %d\n",tmp.a,tmp.b,tmp.c);
		if(flag[tmp.a])sum+=tmp.b,ans.pb(nnn(tmp.a,st,tmp.a));
		else {
			if(tmp.b>tmp.c)sum+=tmp.b,ans.pb(nnn(tmp.a,st,tmp.a));
			else 		   sum+=tmp.c,ans.pb(nnn(tmp.a,ed,tmp.a));
		} 
		for(int i=head[tmp.a];i;i=e[i].nxt){
			if(v==fath[tmp.a]||flag[v])continue;
			else	   q.push(nnn(v,tmp.b+1,tmp.c+1));
		}
		#undef v
	}
	out::write(sum);out::putc('\n');
	for(int i=ans.size()-1;i>=0;i--)if(ans[i].c!=st)
		out::write(ans[i].a),out::putc(' '),
		out::write(ans[i].b),out::putc(' '),
		out::write(ans[i].c),out::putc('\n'); 
	out::flush();
	return 0;
}

```

---

## 作者：luckydrawbox (赞：5)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF911F)

## 前置知识

- [深度优先搜索 DFS](https://oi-wiki.org/graph/dfs/)
- [树的直径](https://oi-wiki.org/graph/tree-diameter/)
- [拓扑排序](https://oi-wiki.org/graph/topo/)

## 题意

一棵 $n$ 个点的无根无权树，进行 $n-1$ 次操作，每次进行如下操作：

- 选择树上的两个点 $u,v$。
- $ans$ 加上 $u,v$ 之间的简单路径经过的边数。
- 删除点 $u$ 或点 $v$，并输出删除过程。

求 $ans$ 的最大值。

## 分析

我们知道一个点在树上能最远达到的点必定是树的直径的端点，为了使答案最大，我们要使每个点的贡献最大，于是就可以先把不在直径上的点删去（要保证不影响其他点的最大贡献），再逐个删直径上的点。

我们就有了一个贪心策略：

- 求出树的直径长度 $len$、两个端点 $s,t$。
- 用两次 $\text{dfs}$ 计算每个点到 $s,t$ 的距离 $ds_i,dt_i$。
- 答案 $ans$ 初始为 $\sum_{i=1}^{len}i=\frac{len\times(len+1)}{2}$，也就是最后要逐个删掉直径上的点，贡献为 $\sum_{i=1}^{len}i$。
- 通过比较 $ds_i+dt_i$ 是否和 $len$ 相等判断点 $i$ 是否是直径上的点，并打上标记 $vis_i\Leftarrow 1$。
- 对于所有不在直径上的点 $i$，$ans$ 加上 $i$ 到 $s$ 或 $t$ 的最大距离 $\max(ds_i,dt_i)$。这个过程可以和上一步一起实现。
- 输出 $ans$。
- 不断找出一个不在直径上的点直至没有，要保证这个点所连接的点到直径任意一端的路径不经过这个点，删除这个点并输出过程。**可以这样理解**：把直径 $s\Rightarrow t$ 这条线举起来，让其他点沿地心引力自由下落，形成一颗颗子树，一个节点可以删除当且仅当它的子节点都被删除，~~作者画图技术太烂请读者自行脑补~~。
- 选择直径的一端，从这一端开始删直径上的节点并输出过程。

求出 $ans$ 显然十分简单，但是求出删点过程却比较麻烦，这也正是这篇题解与其他题解的不同之处：如何求。

我们可以在输入加边时记录每个点所连的边数 $in_i$，对于每个不在直径上的点 $i$，令 $in_i$ 自减，也就是减去它到父节点的一条边（**树的形态就是贪心策略中所说的，只不过我们暂时不知道具体长什么样**），此时一个没有子节点的 $i$ 的 $in_i$ 为 $0$，仿照**拓扑排序**的做法，将 $in_i=0$ 的节点入队。

不断取出队头 $x$，输出 $x$ 点的删除过程，把所有与 $x$ 相连的点 $y$ 的 $in_y$ 减 $1$，使父节点 $y$ 的 $in_y$ 减少 $1$，如果 $in_y=0$，把 $y$ 入队。

上述操作执行到队列为空，我们就删完了所有不在直径上的点。

>**Q:** 为什么要把所有与 $x$ 相连的点 $y$ 的 $in_y$ 减 $1$？这样不是会把子节点 $y$ 的 $in_y$ 重复减了吗？
>
>**A:** 这样是使其父节点的边数减少，让其父亲成为一个新的叶子节点；子节点重复减不会有影响，因为这些节点的 $in$ 之前已经为 $0$，再减 $1$ 就变成负数，不会被入队。

处理好不在直径上的点后，我们从直径的一端开始 $\text{dfs}$ 删点并输出过程即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=2e5+10;
int n,u,v,in[N];
vector<int>e[N];
bool vis[N];
#define T_D_T long long
struct Tree_Diameter{
	int s,t;
	T_D_T d[N],len;
	void init(){
		s=t=len=0;
		memset(d,0,sizeof(d));
	}
	void dfs(int x,int fa){
		for(int i=0;i<e[x].size();i++){
			if(e[x][i]==fa)
				continue;
			d[e[x][i]]=d[x]+1;
			if(d[e[x][i]]>d[s])
				s=e[x][i];
			dfs(e[x][i],x);
		}
	}
	void calc(){
		init();
		dfs(1,0);
		d[t=s]=0;
		dfs(s,0);
		len=d[s];
	}
}tree;
ll D[2][N];
void dfs(int t,int x,int fa){
	for(int i=0;i<e[x].size();i++){
		if(e[x][i]==fa)
			continue;
		D[t][e[x][i]]=D[t][x]+1;
		dfs(t,e[x][i],x);
	}
}
void topu(){
	queue<int>q;
	for(int i=1;i<=n;i++)
		if(!in[i])
			q.push(i);
	while(q.size()){
		int x=q.front();q.pop();
		printf("%d %d %d\n",(D[0][x]>D[1][x]?tree.s:tree.t),x,x);
		for(int i=0;i<e[x].size();i++)
			if(vis[e[x][i]]&&!(--in[e[x][i]]))
				q.push(e[x][i]);
	}
}
void dfs2(int x,int fa){
	if(x==tree.t)
		return;
	printf("%d %d %d\n",tree.t,x,x);
	for(int i=0;i<e[x].size();i++)
		if(!vis[e[x][i]]&&e[x][i]!=fa)
			dfs2(e[x][i],x);
}
int main(){
	n=read();
	for(int i=1;i<n;i++){
		u=read();v=read();
		e[u].push_back(v);
		e[v].push_back(u);
		in[u]++;in[v]++;
	}
	tree.calc();
	ll ans=(tree.len+1)*tree.len/2;
	dfs(0,tree.s,0);dfs(1,tree.t,0);
	for(int i=1;i<=n;i++)
		if(D[0][i]+D[1][i]!=tree.len){
			ans+=max(D[0][i],D[1][i]);
			vis[i]=1;
			in[i]--;
		}
	write(ans);cout<<endl;
	topu();
	dfs2(tree.s,0);
	return 0;
}
```

时间复杂度 $O(n)$。

---

## 作者：tommymio (赞：3)

有一个非常经典的结论，对于任意点 $x$，与其距离最远的点只会是一条直径 $\text{Path}(s\to t)$ 的两个端点 $s,t$ 之一。经典的图论书籍上都存在相关证明，可以自行翻阅。

那么，我们先求出直径，从叶子开始一个一个删就可以了，每个节点 $x$ 的贡献为 $\max(\text{dis}(x,s),\text{dis}(x,t))$。但是这样非常难实现。

不妨使用 $\text{bfs}$，从直径开始向外延伸，最后倒序输出。由于 $\text{bfs}$ 的性质，这样能够保证在删除一个点 $x$ 之前，它的所有子节点都已被删除，所以是合法的。

感觉自己的代码越写越毒瘤了（雾

```cpp
#include<cstdio>
#include<queue>
typedef long long ll;
int cnt=0,pos;
struct state {int x,st,ed;}ans[200005];
std::queue<state> Q;
int s[200005],dep[200005],pre[200005],tag[200005];
int h[200005],to[400005],ver[400005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline void add(int x,int y) {to[++cnt]=y;ver[cnt]=h[x];h[x]=cnt;}
inline void dfs(int x,int fa) {
	pre[x]=fa; pos=(dep[pos]<dep[x]? x:pos);
	for(register int i=h[x];i;i=ver[i]) {
		int y=to[i];
		if(y==fa) continue;
		dep[y]=dep[x]+1; dfs(y,x);
	}
}
int main() {
	ll res=0;
	int n=read(),top=0,st,ed;
	for(register int i=1;i<n;++i) {int x=read(),y=read();add(x,y);add(y,x);}
	dfs(1,-1); st=pos; pos=dep[st]=pre[st]=0; dfs(st,-1); ed=pos; 
	int cur=ed; while(cur!=-1) {s[++top]=cur;tag[cur]=1;cur=pre[cur];} 
	for(;top;--top) {Q.push((state){s[top],dep[s[top]],dep[ed]-dep[s[top]]});}
	while(Q.size()) {
		state now=Q.front(); Q.pop();
		if(tag[now.x]) {ans[++top]=(state){now.x,st,now.x};res+=now.st;}
		else {
			if(now.st<now.ed) ans[++top]=(state){now.x,ed,now.x},res+=now.ed;
			else ans[++top]=(state){now.x,st,now.x},res+=now.st;
		}
		for(register int i=h[now.x];i;i=ver[i]) {int y=to[i]; if(pre[now.x]==y||tag[y]) continue; Q.push((state){y,now.st+1,now.ed+1});}
	}
	printf("%lld\n",res);
	for(;top-1;--top) {printf("%d %d %d\n",ans[top].x,ans[top].st,ans[top].ed);}
	return 0;
}
```

---

## 作者：NashChen (赞：0)

## 题意

给定一棵 $N$ 个点的树，每次选定两个叶子结点，将它们之间的距离加入到结果中，并删掉其中一个叶子节点。直到树上剩下一个点。求结果的最大值和删点的方案。

$$ N \leq 2 \times 10^5 $$

## 题解

这道题的结论比较好想，但是要严谨证明下来还是挺有意思的。

题目要求选两个叶子结点，然后删掉一个点。实际上没删掉的那个点对后面的操作没有任何影响。

所以原问题可以转变为每次选一个叶子结点，向结果中加入这个点在树上的最远距离，然后删掉该点。

删点的操作看起来会对后面选的点产生影响。但是，联系直径的性质可以知道，对于**树上的每一个点**，离它最远的点一定是**直径的一端**。只要树的直径不被删掉，**直径外**每一个点可能的最大贡献就是到直径较远端的距离。

唯一需要考虑的就是直径上的点。直径上的点因为删点的影响，有一半的点的贡献取不到最大。

但仔细一想就可以发现，因为最后无论如何都是删成一条链，所以这和先将其他点删掉，再将直径上的点删掉一些的**效果是一样**的。而先删直径上的的点可能会导致其他点贡献减少，所以先删直径上的点的方案**不优于**最后再删直径上的点。

至此，可以推出，**将树删剩直径，最后一个一个点删**的做法是最优的。

时间复杂度 $O(N)$ 。

## 代码

树的直径和拓扑排序代码细节比较多，写的时候要保持思路清晰。

别忘了无向图双向边开双倍数组。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN= 400005;

int N,head[MAXN],nex[MAXN],targ[MAXN],indeg[MAXN],cur;
int dis[MAXN][2],maxv[2];
int ans[MAXN],ansv[MAXN],cnt;
long long sumans;
int Que[MAXN],Qhead,Qtail;
void BFS(int s,int k){
	Qhead= Qtail= 1;
	for(int i=1;i<=N;++i) dis[i][k]= -1;
	Que[Qtail++]= s;
	dis[s][k]= 0;maxv[k]= s;
	while(Qhead<Qtail){
		int u= Que[Qhead++],v;
		for(int e=head[u];e;e=nex[e]){
			v= targ[e];
			if(dis[v][k]!= -1) continue;
			dis[v][k]= dis[u][k]+1;
			if(dis[v][k]>dis[maxv[k]][k]) maxv[k]= v;
			Que[Qtail++]= v;
		}
	}
	return;
}

void Topsort(){
	Qhead= Qtail= 1;
	for(int i=1;i<=N;++i)
		if(indeg[i]<=1 && i!=maxv[0] && i!=maxv[1])
			Que[Qtail++]= i;
	while(Qhead<Qtail){
		int u= Que[Qhead++],v;
		ans[++cnt]= u;
		sumans+= max(dis[u][0],dis[u][1]);
		if(dis[u][0]> dis[u][1]) ansv[cnt]= 1;
		else ansv[cnt]= 0;
		for(int e=head[u];e;e=nex[e]){
			v= targ[e];
			if(indeg[v]<=1) continue;
			indeg[u]--;
			indeg[v]--;
			if(indeg[v]<=1) Que[Qtail++]= v;
		}
	}
	return;
}

void solve(){
	BFS(1,0);
	BFS(maxv[0],0);
	BFS(maxv[0],1);
	Topsort();
	int u= maxv[1],v;
	while(u!=maxv[0]){
		sumans+= dis[u][1];
		ans[++cnt]= u;
		ansv[cnt]= 0;
		for(int e=head[u];e;e=nex[e]){
			v= targ[e];
			if(dis[v][1]+1 == dis[u][1]){
				u= v;
				break;
			}
		}
	}
	return;
}

void AddEdge(int u,int v){
	nex[++cur]= head[u];
	head[u]= cur;
	targ[cur]= v;
	indeg[v]++;
	return;
}

void Input(){
	scanf("%d",&N);
	for(int i=1;i<=N-1;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		AddEdge(x,y);
		AddEdge(y,x);
	}
	return;
}

int main(){
	Input();
	solve();
	printf("%lld\n",sumans);
	for(int i=1;i<=cnt;++i)
		printf("%d %d %d\n",ans[i],maxv[ansv[i]],ans[i]);
	return 0;
}
```

---

