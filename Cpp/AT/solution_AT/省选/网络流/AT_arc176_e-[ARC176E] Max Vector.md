# [ARC176E] Max Vector

## 题目描述

给定两个长度为 $N$ 的正整数序列 $X=(X_1,X_2,\dots,X_N), Y=(Y_1,Y_2,\dots,Y_N)$。

另外，还给定 $M$ 个长度为 $N$ 的正整数序列。第 $i$ 个正整数序列为 $A_i = (A_{i,1},A_{i,2},\dots,A_{i,N})$。

你需要依次对 $i=1,2,\dots,M$ 进行如下两种操作之一。对于每个 $i$，可以独立选择要执行哪种操作。

- 对所有满足 $1 \le j \le N$ 的整数 $j$，将 $X_j$ 替换为 $\max(X_j, A_{i,j})$。
- 对所有满足 $1 \le j \le N$ 的整数 $j$，将 $Y_j$ 替换为 $\max(Y_j, A_{i,j})$。

请你求出操作结束后 $\sum_{j=1}^{N} (X_j + Y_j)$ 的最小值。

## 说明/提示

## 限制条件

- $1 \le N \le 10$
- $1 \le M \le 500$
- $1 \le X_j, Y_j, A_{i,j} \le 500$

## 样例解释 1

一种最优的操作序列如下：

- 将 $X_j$ 替换为 $\max(X_j, A_{1,j})$，此时 $X=(4,5,2)$。
- 将 $Y_j$ 替换为 $\max(Y_j, A_{2,j})$，此时 $Y=(3,2,5)$。

这样操作后，可以得到 $\sum_{j=1}^{N} (X_j + Y_j) = 21$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2
4 4 2
3 1 5
2 5 2
1 2 4```

### 输出

```
21```

## 样例 #2

### 输入

```
3 5
4 13 10
14 9 4
4 6 4
13 18 16
8 13 5
7 18 17
20 20 14```

### 输出

```
84```

## 样例 #3

### 输入

```
5 12
330 68 248 387 491
295 366 376 262 192
280 121 17 168 455
288 179 210 378 490
150 275 165 264 287
66 331 207 282 367
303 215 456 214 18
227 326 103 443 427
395 57 107 350 227
318 231 146 2 116
57 325 124 383 260
147 319 23 177 445
254 198 32 85 56
68 177 356 41 471```

### 输出

```
3595```

# 题解

## 作者：Drind (赞：13)

首先看到要把每个操作分给 X 和 Y 两侧，我们就可以开始想最小割模型了。然后看到这个取 $\max$ 的操作跟值域有关，而且值域还是给定的，为 $500$，这么小，我们可以考虑对于每个值建一个点。

所以我们对于 $X_i$ 建立 $V+1$ 个点，其中 $V$ 为值域，然后从上往下依次连 $V$ 条边，边权为 $[1,V]$。

在第 $V+1$ 个点，也就是最下面的点，连向汇点，边权无限大，也就是这个边不许割。

因为 $X_i$ 的取值已经有了一个上界，所以源点连向第 $X_i$ 个点，边权无限大，这个边也不许你割。

我们当然可以直接把这个建图搬到 $Y$ 上去，但是这样就不好做之后的 $\max$ 操作了，所以我们先不管 $Y$，考虑一下这些操作该怎么做。

假设第 $i$ 个操作对 $X$ 做，也就是限制了 $X_j\ge A_{i,j}$，那我们直接把源点连向 $X_j$ 的第 $A_{i,j}$ 个点不就行了。

但是这个操作也可以对 $Y$ 做，所以我们建一个虚拟点作为这个操作，然后如果虚拟点被割到 $S$ 就代表对 $X$ 做了（因为此时虚拟点和 S 等价）。

反过来，如果虚拟点被割到 $T$ 也就是对 $Y$ 做了，所以我们对 $Y$ 侧的建图有一点思路了，就是把 $X$ 侧反过来对吧。

具体的，就是把每个边反过来，源点连向最下面的点，第 $Y_i$ 个点连向汇点。

然后把 $Y_j$ 的第 $A_{i,j}$ 个点连向虚拟点，把虚拟点连向 $X_j$ 的第 $A_{i,j}$ 个点，边权全部都是无限大，这个边不能割。

这时候，就能做到把虚拟点割到源点和汇点了，我们直接在这个图上跑最小割即为答案。

代码里 $X$ 侧和 $Y$ 侧反过来了，也就是 $X$ 侧是从下往上，$Y$ 侧是从上往下的。

省略最大流板子代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int inf=0x3f3f3f3f;
const int P=500;

inline void fake_main(){
	memset(head,-1,sizeof head);
	int n,m; cin>>n>>m;
	s=N-1,t=s-1;
	
	auto id=[n,m](int x,int y,int op){
		return (x-1)*(P+1)+y+(op-1)*n*(P+1);
	};//op代表X侧或Y侧，计算第x个数的第y个点
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=P;j++){
			adde(id(i,j+1,1),id(i,j,1),j);//X侧从下往上	
			adde(id(i,j,2),id(i,j+1,2),j);//Y侧从上往下
		}
		adde(s,id(i,P+1,1),inf);//连源汇
		adde(id(i,P+1,2),t,inf);
	}
	
	for(int i=1;i<=n;i++){
		int tmp; cin>>tmp;
		adde(id(i,tmp,1),t,inf);//最初的限制
	}
	for(int i=1;i<=n;i++){
		int tmp; cin>>tmp;
		adde(s,id(i,tmp,2),inf);
	}
	
	int res=(P+1)*n*2;//新建的虚拟点
	for(int i=1;i<=m;i++){
		++res;
		for(int j=1;j<=n;j++){
			int tmp; cin>>tmp;
			adde(id(j,tmp,1),res,inf);//虚拟点带来的限制
			adde(res,id(j,tmp,2),inf);
		}
	}
	
	cout<<dinic()<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}

```

---

## 作者：honglan0301 (赞：12)

## 分析

数据范围这么小，场上一下子就想到乱搞啊！下面讲一讲对乱搞策略的研究过程。

------------


<1> 首先考虑**贪心**，依次（根据代价大小）贪心选择每个 $a_{i,\_}$ 与 $x_\_$ 还是 $y\_$ 放到一起，这样会 WA 65 个点。

<2> 考虑经典乱搞技巧。采用**随机化+贪心**，每次随一个顺序，然后按此顺序执行算法 <1>，这样只 WA 了 31 个点，效果显著！

*考虑 hack 算法 <2>。很容易发现一些比较简单的想法，比如 当同时存在 $a_{1,j}=\{500,500,0,0\},a_{2,j}=\{0,0,500,500\},a_{3,j}=\{0,500,500,0\}$ 时，显然把它们都放到同一边最优，但我们对于 $a_{1,j}$ 和 $a_{2,j}$ 的贪心策略几乎是独立的，很可能被卡。

<3> 根据以上 hack 方法进行**有针对性的乱搞**。我们先 $2^n$ 钦定每个最大值放到哪边，然后再随顺序贪心。这样仅仅会 WA 1 个点（test #14）。可惜[赛时](https://atcoder.jp/contests/arc176/submissions/52666641)时间不够止步于此了（><）

<4> 最后再套用经典乱搞技巧。每次进行随机扰动/贪心**调整**，只要写得不太差就能 AC。 

------------


什么？你问我这为什么能过？——“乱搞哥都是从不证明的，感受那股劲！”

## 代码

核心代码如下。

```cpp

#define mp make_pair
#define pb push_back
#define fi first
#define se second
int n,m,x[15],y[15],a[505][15],bh[505],nx[15],ny[15],zt[505],bx[505],jy[15];
int mxn[15],nmx[15];

int getrd(int l,int r)
{
	return l+(rnd()%(r-l+1));
}

int cx[11][505],cy[11][505];

int cc()
{
	int na=0; for(int i=1;i<=n;i++) na+=nx[i]+ny[i]; return na;
}
void cg(int x)
{
	if(zt[x]==1)
	{
		for(int j=1;j<=n;j++)
		{
			cx[j][a[x][j]]--; cy[j][a[x][j]]++; ny[j]=max(ny[j],a[x][j]);
		}
	}
	else
	{
		for(int j=1;j<=n;j++)
		{
			cy[j][a[x][j]]--; cx[j][a[x][j]]++; nx[j]=max(nx[j],a[x][j]);
		}
	}
	zt[x]=3-zt[x];
}
int sa(int pp)
{
	memset(cx,0,sizeof(cx));
	memset(cy,0,sizeof(cy));
	for(int j=1;j<=n;j++) cx[j][x[j]]++,cy[j][y[j]]++;
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(zt[i]==1) cx[j][a[i][j]]++; else cy[j][a[i][j]]++;
		}
	}
	for(int t=1;t<=10;t++)
	{
		int op=getrd(1,2),wz=getrd(1,n);
		vector <int> num;
		if(op==1)
		{
			int val=getrd(x[wz],nx[wz]);
			for(int i=1;i<=m;i++)
			{
				if(zt[i]!=1||a[i][wz]<=val) continue;
				num.pb(i); cg(i);
			}
		}
		else
		{
			int val=getrd(y[wz],ny[wz]);
			for(int i=1;i<=m;i++)
			{
				if(zt[i]!=2||a[i][wz]<=val) continue;
				num.pb(i); cg(i);
			}
		}
		for(int j=1;j<=n;j++)
		{
			while(!cx[j][nx[j]]) nx[j]--;
			while(!cy[j][ny[j]]) ny[j]--;
		}
		int to=cc();
		if(to<=pp) pp=to;
		else
		{
			for(auto i:num) cg(i);
			for(int j=1;j<=n;j++)
			{
				while(!cx[j][nx[j]]) nx[j]--;
				while(!cy[j][ny[j]]) ny[j]--;
			}
		}
		pp=min(pp,cc());
	}
	//cout<<pp<<endl;
	return pp;
}
int cntt=0;
int calc(int ff,int op)
{
	cntt++;
	for(int i=1;i<=n;i++) nx[i]=x[i],ny[i]=y[i];
	int ok=1;
	for(int j=1;j<=n;j++)
	{
		if(ff&(1<<j-1)) bx[mxn[j]]|=1,nx[j]=max(nx[j],a[mxn[j]][j]); else bx[mxn[j]]|=2,ny[j]=max(ny[j],a[mxn[j]][j]);
		if(bx[mxn[j]]==3) ok=0;
	}
	for(int j=1;j<=n;j++) bx[mxn[j]]=0;
	if(!ok) return 1000000000;
	for(int t=1;t<=m;t++)
	{
		int i=bh[t];
		int dt1=0,dt2=0;
		for(int j=1;j<=n;j++) dt1+=max(nx[j],a[i][j])-nx[j],dt2+=max(ny[j],a[i][j])-ny[j];
		if(dt1<dt2||dt1==dt2&&rnd()&1)
		{
			zt[i]=1;
			for(int j=1;j<=n;j++) nx[j]=max(nx[j],a[i][j]);
		}
		else
		{
			zt[i]=2;
			for(int j=1;j<=n;j++) ny[j]=max(ny[j],a[i][j]);
		}
	}
	int na=cc();
	if(!op) return na; return min(na,sa(na));
}

signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>x[i];
	for(int i=1;i<=n;i++) cin>>y[i];
	for(int i=1;i<=m;i++) for(int j=1;j<=n;j++) cin>>a[i][j];
	for(int i=1;i<=m;i++) bh[i]=i;
	int ans=1000000000;
	shuffle(bh+1,bh+m+1,rnd);
	for(int i=1;i<=n;i++)
	{
		for(int t=1;t<=m;t++)
		{
			int j=bh[t];
			if(a[j][i]>a[mxn[i]][i]) mxn[i]=j,nmx[i]=a[j][i];
		}
	}
	int tt=0;
	while(clock()<=1.9*CLOCKS_PER_SEC)
	{
		tt++; if(tt>=(1<<n)) tt-=(1<<n);
		shuffle(bh+1,bh+m+1,rnd);
		ans=min(ans,calc(tt,1));
	}
	cout<<ans<<endl; return 0;
	cout<<ans<<" "<<cntt<<endl;
}
```

---

## 作者：WrongAnswer_90 (赞：8)

# [My Blogs](https://www.cnblogs.com/WrongAnswer90/p/18158723)

### [[ARC176E] Max Vector](https://www.luogu.com.cn/problem/AT_arc176_e)

$n=10$ 其实有点误导性。其实这个题不是指数级的算法，而且贪心也不是很合理，同时“要么...要么...”有点像最小割。

一次操作可以看成要求 $x_j\geq a_{i,j}$ 或者 $y_j\geq a_{i,j}$。考虑切糕的模型，建 $2n$ 条链，割哪条边就表示第 $i$ 个变量的取值。其中 $x_i$ 的链要正着建，$y_i$ 的链要反着建：

![](https://s2.loli.net/2024/04/25/UDz7xNcIeurd9t3.png)

对于每次操作，建一个点 $i$，向 $2n$ 条链连边，其中向 $x$ 的是出边，假设权值是 $a_j$,则向第 $j$ 条链上的第 $j$ 个点连边，容量 inf。向 $y$ 的是入边，从第 $j$ 条链上的第 $v-a_j+2$ 个点连边向 $i$。

这样，就刻画出了“$\{\forall i,x_i\geq a_i\}\lor\{\forall i,y_i\geq a_i\}$” 。直接跑最大流就是答案。

```cpp
const int N=300000,M=3000000,V=500;
int n,m,S,T,s,cnt=1,now[N+10],head[N+10],to[M+10],nex[M+10],v[M+10],d[N+10];
inline void Add(int x,int y,int z){to[++cnt]=y,v[cnt]=z,nex[cnt]=head[x],head[x]=cnt;}
inline void add(int x,int y,int z){Add(x,y,z),Add(y,x,0);}
queue<int> q;
inline bool bfs()
{
	while(!q.empty())q.pop();
	q.e(S),memset(d,0,sizeof(d)),d[S]=1,now[S]=head[S];
	while(!q.empty())
	{
		int nw=q.front();q.pop();
		for(int i=head[nw];i;i=nex[i])
		{
			if(!d[to[i]]&&v[i])
			{
				now[to[i]]=head[to[i]],d[to[i]]=d[nw]+1,q.e(to[i]);
				if(to[i]==T)return 1;
			}
		}
	}
	return 0;
}
int dinic(int x,int flow)
{
	if(x==T)return flow;
	int rest=flow,t;
	for(int i=now[x];i&&rest;i=nex[i])
	{
		now[x]=i;
		if(!v[i]||d[to[i]]!=d[x]+1)continue;
		t=dinic(to[i],min(rest,v[i])),rest-=t;
		if(!t)d[to[i]]=0;
		v[i]-=t,v[i^1]+=t;
	}
	return flow-rest;
}
#define id(i,j) ((i-1)*(V+1)+j)
inline void mian()
{
	read(n,m),S=n*2*(V+1)+m+1,T=S+1;int x;
	for(int i=1;i<=n;++i)
	{
		read(x),add(S,id(i,x),inf),add(id(i,V+1),T,inf);
		for(int j=1;j<=V;++j)add(id(i,j),id(i,j+1),j),v[cnt]=inf;
	}
	for(int i=n+1;i<=n*2;++i)
	{
		read(x),add(S,id(i,1),inf),add(id(i,V+2-x),T,inf);
		for(int j=1;j<=V;++j)add(id(i,j),id(i,j+1),V-j+1),v[cnt]=inf;
	}
	for(int i=1;i<=m;++i)for(int j=1;j<=n;++j)
	read(x),add(i+n*2*(V+1),id(j,x),inf),add(id(j+n,V+2-x),i+n*2*(V+1),inf);
	while(bfs())while((x=dinic(S,inf)))s+=x;
	write(s);
}
```

---

## 作者：zifanwang (赞：3)

发现数据范围很小，考虑最小割。先对题面做一个转化：

构造两个序列 $X=(X_1,X_2,\dots,X_N),Y=(Y_1,Y_2,\dots,Y_N)$ 最小化 $\sum X_i+Y_i$，有 $M$ 个限制，每个限制有一个序列 $A_1,A_2,\dots,A_n$，需要满足 $\forall i,X_i\ge A_i$ 或者 $\forall i,Y_i\ge A_i$。

考虑怎么建图。对每个 $Y_i$ 新建 $500$ 个点，每个点从前一个点连一条边权为这个点对应值的边（点 $1$ 从源点连），表示选这个数。$500$ 对应的点向汇点连一条边权为 $+\infty$ 的边。$X$ 序列同理，但是考虑到后面的限制需要倒着建。

接下来对于每个限制，从每一个 $X_i$ 的点中 $A_i$ 对应的点向 $Y_i$ 的点中 $A_i+1$ 对应的点连一条边权为 $+\infty$ 的边，表示如果 $X_i<A_i$ 那么 $Y_i$ 就必须 $\ge A_i$。

然后跑一边最小割就做完了。

参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
int n,m,s,t,cnt,f[12],f1[12],f2[12],d[10005],a[12][502],b[12][502];
int tot,vr[200000],ed[200000],nx[200000],now[10005],hd[10005];
ll ans;
inline void add(int x,int y,int z){
	vr[++tot]=y,ed[tot]=z,nx[tot]=hd[x],hd[x]=tot;
	vr[++tot]=x,ed[tot]=0,nx[tot]=hd[y],hd[y]=tot;
}
bool bfs(){
	queue<int>q;
	memset(d,0,sizeof(d));
	d[s]=1,now[s]=hd[s],q.push(s);
	while(q.size()){
		int x=q.front();q.pop();
		for(int i=hd[x],y;i;i=nx[i])if(ed[i]&&!d[y=vr[i]]){
			d[y]=d[x]+1,now[y]=hd[y];
			if(y==t)return 1;
			q.push(y);
		}
	}
	return 0;
}
int dinic(int x,int flow){
	if(x==t)return flow;
	int rest=flow,num,i,y;
	for(i=now[x];i;i=nx[i])if(ed[i]&&d[y=vr[i]]==d[x]+1){
		num=dinic(y,min(rest,ed[i]));
		if(num){
			ed[i]-=num,ed[i^1]+=num;
			rest-=num;
			if(!rest)break;
		}else d[y]=0;
	}
	now[x]=i;
	return flow-rest;
}
signed main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n)scanf("%d",&f1[i]);
	rep(i,1,n)scanf("%d",&f2[i]);
	tot=1,t=n*1000+1;
	rep(i,1,n){
		drep(j,500,1){
			a[i][j]=++cnt;
			add(a[i][j+1],cnt,j<f1[i]?1e9:j);
		}
		add(a[i][1],t,1e9);
		rep(j,1,500){
			b[i][j]=++cnt;
			add(b[i][j-1],cnt,j<f2[i]?1e9:j);
		}
		add(b[i][500],t,1e9);
	}
	rep(i,1,m){
		rep(j,1,n)scanf("%d",&f[j]);
		rep(j,1,n){
			rep(k,1,n)add(a[j][f[j]],b[k][f[k]-1],1e9);
		}
	}
	while(bfs())ans+=dinic(s,0x7fffffff);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Take_A_Single_6 (赞：1)

没做过最小割建模，感觉这题很妙。  
第一眼看到这题肯定想到的是贪心，每次操作选择增加少的。但是仔细想一下，这是不对的，因为后面的操作可能覆盖前面的操作，整体劣有可能单点优，所以不能直接决策。  
爆搜的话 $1 \le m \le 500$ 显然没法搜，似乎dp也不好设计状态。那么就要运用抽象思维，考虑在图上建模。  
观察到值域很小，考虑把 $X_i$ 拆成 $501$ 个点，第 $j$ 个点向第 $j+1$ 个点连一条权值为 $j$ 的边表示 $X_i$ 的取值，从源点向初始的 $X_i$ 连权值为 $inf$ 的边表示取值下界，从最后一个点向汇点连权值为 $inf$ 的边，这两条边不能割。  
因为每次操作只能操作一边，所以 $X$ 与 $Y$ 的取值存在冲突。自然的，考虑对每次操作建一个虚拟节点，由这个虚拟节点向 $X_j,a_{i,j}$ 和 $Y_j,a_{i,j}$ 连权值为 $inf$ 的边，不能割。  
考虑网络流的过程，对于 $Y$ 应当倒着连，源连最后一个点，初始的 $Y_i$ 连汇，然后 $Y_j,a_{i,j}$ 连虚点，虚点连 $X_j,a_{i,j}$。  
![](https://cdn.luogu.com.cn/upload/image_hosting/2iigrv0r.png)  
图为选择 $X$ 和 $Y$ 的两种割法，画得有点抽象。  
建好图直接跑最大流就行，因为有向图最大流就是最小割。  
```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
#define maxn 1000005
#define mod 1000000007
#define fir first
#define sec second
#define pr pair<int,int>
#define mk make_pair
#define inf 10000000000000000
using namespace std;
inline int read()
{
    int SS=0,WW=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')WW=-1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        SS=(SS<<1)+(SS<<3)+(ch^48);
        ch=getchar();
    }
    return SS*WW;
}
inline void write(int XX)
{
    if(XX<0)putchar('-'),XX=-XX;
    if(XX>9)write(XX/10);
    putchar(XX% 10 + '0');
}
struct edge
{
	int to,val,nxt;
}e[maxn];
int n,m,x[maxn],y[maxn],a[505][15],ans,cnt=1,s,t,idx[15][505],idy[15][505],id,head[maxn];//避免编号冲突
void add(int x,int y,int z)
{
	e[++cnt].to=y;
	e[cnt].val=z;
	e[cnt].nxt=head[x];
	head[x]=cnt;
}
int pre[maxn],dis[maxn];
bool vis[maxn];
queue<int>q;
bool bfs()
{
	for(int i=1;i<=id;i++)vis[i]=0;
	while(q.size())q.pop();
	q.push(s),vis[s]=1,dis[s]=inf;
	int u;
	while(q.size())
	{
		u=q.front(),q.pop();
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].to;
			if(e[i].val&&!vis[v])
			{
				dis[v]=min(dis[u],e[i].val),pre[v]=i,vis[v]=1,q.push(v);
				if(v==t)return 1;
			}
		}
	}
	return 0;
}
void upd()
{
	int u=t;
	while(u!=s)
	{
		int v=pre[u];
		e[v].val-=dis[t];
		e[v^1].val+=dis[t];
		u=e[v^1].to;
	}
	ans+=dis[t];
}//dinic板子
signed main()
{
	n=read(),m=read(),s=++id,t=++id;
	for(int i=1;i<=n;i++)x[i]=read();
	for(int i=1;i<=n;i++)y[i]=read();
	for(int i=1;i<=m;i++)for(int j=1;j<=n;j++)a[i][j]=read();
	for(int i=1;i<=n;i++)
	{
		idx[i][1]=++id,idy[i][1]=++id;
		for(int j=1;j<=500;j++)
		{
			idx[i][j+1]=++id,add(idx[i][j],idx[i][j+1],j),add(idx[i][j+1],idx[i][j],0);
			idy[i][j+1]=++id,add(idy[i][j+1],idy[i][j],j),add(idy[i][j],idy[i][j+1],0);
		}
		add(s,idx[i][x[i]],inf),add(idx[i][x[i]],s,0);
		add(s,idy[i][501],inf),add(idy[i][501],s,0);
		add(idx[i][501],t,inf),add(t,idx[i][501],0);
		add(idy[i][y[i]],t,inf),add(t,idy[i][y[i]],0);
	}
	for(int i=1;i<=m;i++)
	{
		++id;
		for(int j=1;j<=n;j++)
		{
			add(idy[j][a[i][j]],id,inf),add(id,idy[j][a[i][j]],0);
			add(id,idx[j][a[i][j]],inf),add(idx[j][a[i][j]],id,0);
		}
	}//建图
	while(bfs())upd();
	write(ans);
	return 0;
}
```

---

## 作者：xiezheyuan (赞：0)

## 简要题意

> 给定两个长度为 $n$ 的序列 $X,Y$ 和一个 $m\times n$ 的矩阵 $A$。你需要恰好进行 $m$ 次操作，第 $i$ 次操作选择下列两个操作中的一个执行：
> - 令 $\forall k\in[1, n], X_k\gets \max(X_k,A_{i,k})$。
> - 令 $\forall k\in[1, n], Y_k\gets \max(Y_k,A_{i,k})$。
>
> 求出最终 $\sum_{i=1}^{n} X_i+Y_i$ 的最小值。
>
> $1\neq n\leq 10,1\leq X_i,Y_i,A_{i,j},m\leq 500$。

## 思路

首先看到题意应该可以想到不少贪心，但是这些贪心几乎都是假的。不过参考 [P3227 \[HNOI2013\] 切糕](https://www.luogu.com.cn/problem/P3227)，不妨想想最小割建模。

由于 $X,Y,A$ 三者的值域都不大，因此可以考虑用切糕一题的方法将每个 $X_i,Y_i$ 拆成一条链。具体地，我们取一个值域上界 $V$，将 $X_i$ 拆成 $V$ 个点 $U_{i, 1}, U_{i, 2}, \cdots, U_{i, V}$。然后连边 $(U_{i,j}, U_{i,j+1}, j), (S, U_{i,1}, +\infty), (U_{i, n}, T, V)$。另外 $X_i$ 初始时已经有了一个下界（也就是初始值），我们连边 $(S,U_{i,X_i},+\infty)$ 来保证总是割断 $X_i$ 及以后的边。

![](https://cdn.luogu.com.cn/upload/image_hosting/am6cuxsc.png)

对于 $Y_i$ 也是类似的，不过为了体现他们的不同，我们不妨将 $Y$ 倒过来拆成一条链：

![](https://cdn.luogu.com.cn/upload/image_hosting/s3ydjf29.png)

然后我们考虑第 $k$ 次操作，枚举 $i$ 考察限制 $A_{k,i}$。我们新建一个点 $O$，$O$ 划分到 $S$ 割集意味着我们选择 $X$，否则选择 $Y$，连边 $(O, U_{i, A_{k, i}}, +\infty)$ 以及 $(V_{i, A_{k, i}}, O, +\infty)$。前者表示当 $O$ 划分到 $S$ 割集时，$U_{i, A_{k,i}}$ 始终在 $S$ 割集，那么 $X_i$ 就必须大于等于 $A_{k,i}$；后者同理。

> 如何判断与 $O$ 连接的两种边的方向？
> 当 $O$ 被划分到割集 $S$ 时，可以将 $O$ 就看成 $S$，那么肯定是 $O\to U$ 不是 $U\to O$，$V$ 同理。


![](https://cdn.luogu.com.cn/upload/image_hosting/0q34v5km.png)

根据最小割最大流定理，我们可以用最大流算法求该图的最小割。时间复杂度 $O(\mathrm{maxflow}(Vn+m, n(V+m)))$ 可以通过本题，[Submission](https://atcoder.jp/contests/arc176/submissions/67241338)。

---

