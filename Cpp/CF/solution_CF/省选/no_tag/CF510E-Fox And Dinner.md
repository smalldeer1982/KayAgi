# Fox And Dinner

## 题目描述

小狐狸Ciel参加了一个派对，加上他自己这个派对里总共有$n$只狐狸，每只狐狸有一个年龄$a_i$。

它们想要在几张圆桌旁吃晚饭，你需要帮忙分配座位，使得满足以下要求：

1. 每只狐狸都在其中
2. 每张桌子边至少有3只狐狸
3. 任意两只相邻的狐狸的年龄之和为质数（圆桌上每只狐狸都有2只相邻的狐狸）

## 样例 #1

### 输入

```
4
3 4 8 9
```

### 输出

```
1
4 1 2 4 3
```

## 样例 #2

### 输入

```
5
2 2 2 2 2
```

### 输出

```
Impossible
```

## 样例 #3

### 输入

```
12
2 3 4 5 6 7 8 9 10 11 12 13
```

### 输出

```
1
12 1 2 3 6 5 12 9 8 7 10 11 4
```

## 样例 #4

### 输入

```
24
2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
```

### 输出

```
3
6 1 2 3 6 5 4
10 7 8 9 12 15 14 13 16 11 10
8 17 18 23 22 19 20 21 24
```

# 题解

## 作者：yuzhechuan (赞：7)

挺有意思的dinic二分图匹配问题

---

### 题解：

首先观察性质，$a_i\ge 2$，所以两数相加的质数不包括数字2这个例外，因此一定都是要用一奇一偶组合成的

因此题目让我们搞的环一定是偶环，且环内奇数与偶数个数相等

套路地，把奇数和偶数分成二分图的左右部，暴力枚举，根据和是否为质数来连容量1的边

由于是环，那么一个数肯定要正好匹配两个，所以左右部向两个超级点都要连容量为2的边

假如都能匹配成环，那么最大流肯定是左部图的大小乘2（即容量），又因为奇数与偶数要满足数量相同，所以左部图的大小就是$\frac{n}{2}$，所以最大流需要满足等于$n$

判定完后，在残量网络上跑dfs就可以得到具体的匹配情况了

---

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
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

const int N=205,M=3e5+5;
int en=1,h[N],cur[N],d[N],n,m,a[N];
vector<vector<int> > ans;
vector<int> vec,odd,even;
bool v[N];

struct edge{
	int n,v,w;
}e[M<<1];

void add(int x,int y,int z){
	e[++en]=(edge){h[x],y,z};
	h[x]=en;
}

bool bfs(int s,int aim){
	memset(d,0,sizeof d);
	memcpy(cur,h,sizeof cur);
	queue<int> q;
	q.push(s);
	d[s]=1;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=h[x];i;i=e[i].n){
			int y=e[i].v;
			if(!d[y]&&e[i].w){
				d[y]=d[x]+1;
				if(y==aim) return 1;
				q.push(y);
			}
		}
	} 
	return 0;
}

int dfs(int x,int flow,int aim){
	if(x==aim) return flow;
	int rest=flow;
	for(int &i=cur[x];i&&rest;i=e[i].n){
		int y=e[i].v;
		if(d[y]==d[x]+1&&e[i].w){
			int tp=dfs(y,min(rest,e[i].w),aim);
			rest-=tp;
			e[i].w-=tp;
			e[i^1].w+=tp;
		}
	}
	return flow-rest;
}

int dinic(int s,int t){
	int res=0;
	while(bfs(s,t)) res+=dfs(s,INT_MAX,t);
	return res;
}

void exadd(int x,int y,int f){
	add(x,y,f);
	add(y,x,0);
}
//以上为模板
bool isprime(int x){ //暴力判质数
	for(int i=2;i*i<=x;i++) if(x%i==0) return 0;
	return 1;
}

void go(int x){
	v[x]=1;
	vec.push_back(x); //加入当前的环
	for(int i=h[x];i;i=e[i].n){
		int y=e[i].v;
		if(v[y]) continue;
		if(!e[i^(a[x]&1)].w) continue; //左部点向右要看相反边，右部点向左则看当前边（这句话看不懂可以画个二分图琢磨下）
		go(y);
		break;
	}
}

signed main(){
	read(n);
	for(int i=1;i<=n;i++){
		read(a[i]);
		if(a[i]&1) odd.push_back(i),exadd(0,i,2);
		else even.push_back(i),exadd(i,n+1,2);
	}
	if(odd.size()!=even.size()){ //根据性质，奇数与偶数个数要相等
		puts("Impossible");
		return 0;
	}
	for(int x:odd) for(int y:even) if(isprime(a[x]+a[y])) exadd(x,y,1); //暴力枚举左右部点看看能否连边
	if(dinic(0,n+1)!=n){ //n在这里表示奇数点个数(n/2)乘2
		puts("Impossible");
		return 0;
	}
	v[0]=v[n+1]=1; //超级点不能走
	for(int x:odd) if(!v[x]){ //枚举奇数点
		vec.clear();
		go(x); //从奇数点出发遍历残量网络
		ans.push_back(vec);
	}
	write(ans.size());puts(""); //输出
	for(auto a:ans){
		write(a.size());putchar(' ');
		for(int x:a) write(x),putchar(' ');puts("");
	}
}
```

---

## 作者：chenxia25 (赞：3)

$a_i\geq2$，和是质数，那么仅当一奇一偶，显然的二分图。

我们考虑一个合法的坐桌子方案。显然环的大小是偶数，又要 $\geq3$，那么 $\geq4$。那么当且仅当每个点的入度出度都为 $1$，并且入出不相等。这个在二分图上就很好建了，等价于每个左部点都有两个不同的出点，每个右部点都有两个不同的入点。那就连边，然后源汇相连的边的容量是 $2$，中间是 $1$。跑最大流，看是否满流。

方案随便构造。

---

## 作者：lhm_ (赞：2)

可以用网络流解决这个题。

注意到$a_i \geqslant 2$，所以当相邻数字要和为质数时，这两个数要一个为奇数，一个为偶数。

所以就先将所有数按奇偶分为两列，其就构成了一个二分图，二分图中和为质数的两个数间连容量为$1$的边，表示只能匹配一次。

因为是圆桌，所以一个数要恰好匹配两个数，所以每个点在和源汇点连边时，容量要为$2$，同时这也保证了每个圆桌中至少有$3$个狐狸。

无解的情况就是二分图两个部分大小不是都为$\frac{n}{2}$或最大流的结果不为$n$。

在跑完最大流后的残量网络中找环即可确定满足要求的分配方案。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 400010
#define all 20000
#define inf 1000000000
using namespace std;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,tot,s,t,cnt1,cnt2,ans;
int a[maxn],p1[maxn],p2[maxn],p[maxn],cur[maxn],d[maxn];
bool tag[maxn],vis[maxn];
vector<int> ve[maxn];
struct edge
{
    int to,nxt,v;
}e[maxn];
int head[maxn],edge_cnt=1;
void add(int from,int to,int val)
{
    e[++edge_cnt]=(edge){to,head[from],val},head[from]=edge_cnt;
    e[++edge_cnt]=(edge){from,head[to],0},head[to]=edge_cnt;
}
bool bfs()
{
	queue<int> q;
	for(int i=s;i<=t;++i) cur[i]=head[i],d[i]=0;
	q.push(s),d[s]=1;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=e[i].nxt)
		{
			int y=e[i].to,v=e[i].v;
			if(d[y]||!v) continue;
			d[y]=d[x]+1,q.push(y);
		}
	}
	return d[t];
}
int dfs(int x,int lim)
{
	if(x==t) return lim;
	int res=lim,flow;
	for(int &i=cur[x];i;i=e[i].nxt)
	{
		int y=e[i].to,v=e[i].v;
		if(d[y]!=d[x]+1||!v) continue;
		if(flow=dfs(y,min(res,v)))
		{
			res-=flow;
			e[i].v-=flow;
			e[i^1].v+=flow;
			if(!res) break;
		}
	}
	return lim-res;
}
int dinic()
{
    int flow,v=0;
    while(bfs())
        while(flow=dfs(s,inf))
            v+=flow;
    return v;
}
void init()
{
    for(int i=2;i<=all;++i)
    {
        if(!tag[i]) p[++tot]=i;
        for(int j=1;j<=tot;++j)
        {
            int k=i*p[j];
            if(k>all) break;
            tag[k]=true;
            if(i%p[j]==0) break;
        }
    }
}
void dfs_ans(int x,int type)
{
    vis[x]=true,ve[ans].push_back(x);
    for(int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        if(e[i^type].v||vis[y]) continue;
        dfs_ans(y,type^1);
    }
}
int main()
{
    init(),read(n),t=n+1;
    for(int i=1;i<=n;++i)
    {
        read(a[i]);
        if(a[i]&1) p1[++cnt1]=i;
        else p2[++cnt2]=i;
    }
    if(cnt1!=cnt2)
    {
        puts("Impossible");
        return 0;
    }
    for(int i=1;i<=n/2;++i)
        for(int j=1;j<=n/2;++j)
            if(!tag[a[p1[i]]+a[p2[j]]])
                add(p1[i],p2[j],1);
    for(int i=1;i<=n/2;++i) add(s,p1[i],2);
    for(int i=1;i<=n/2;++i) add(p2[i],t,2);
    if(dinic()!=n)
    {
        puts("Impossible");
        return 0;
    }
    vis[s]=vis[t]=true;
    for(int i=1;i<=n/2;++i)
    {
        if(vis[p1[i]]) continue;
        ans++,dfs_ans(p1[i],0);
    }
    printf("%d\n",ans);
    for(int i=1;i<=ans;++i)
    {
        printf("%d ",ve[i].size());
        for(int j=0;j<ve[i].size();++j)
            printf("%d ",ve[i][j]);
        puts("");
    }
    return 0;
}
```

---

## 作者：AC_love (赞：1)

因为每只狐狸有且只有两个与它相邻的狐狸，那么我们可以考虑从源点向狐狸连边权为 $2$ 的边，然后从狐狸向汇点连边权为 $2$ 的边，然后狐狸和狐狸之间连边权为 $1$ 的边，跑最大流。

我们把每只狐狸拆成两个点，左边的点都从超级源点连过来，右边的点都连向超级汇点，每条边容量都是 $2$。然后每只狐狸向所有能和它挨着坐的从左到右连边，每条边的容量为 $1$，然后跑一遍 Dinic。

如果我们发现此时最大流等于 $2n$，说明有合法方案，否则就没有。然后在残留网络上找一下环，dfs 一遍求方案。

这是一开始我的思路，看完其他人的题解之后意识到其实不需要拆点。因为 $a_i \ge 2$，所以两个 $a_i$ 相加之后一定大于等于 $4$，此时如果和是质数的话一定是一奇一偶。所以我们可以直接把奇点放左面，偶点放右面，然后类似地连边跑最大流，如果最大流等于 $n$，说明有合法方案。

---

## 作者：xgzc (赞：1)

首先可以发现：由于$a_i \geq 2$，所以质数肯定是被拆成一个奇数和一个偶数。

这样的话很类似一个二分图模型，所以考虑网络流。

当$a_i$是奇数时连边$(S, i, 2)$，当$a_i$是偶数时连边$(i, T, 2)$，表示一个点的邻居最多有两个点。

若$a_i$是奇数，$a_j$是偶数，$a_i + a_j$是质数，则连边$(i, j, 1)$。

跑出来如果最大流不是$n$则不合法，否则直接暴力找环即可。

代码见我的[$\texttt{blog}$](https://www.cnblogs.com/cj-xxz/p/11234253.html)

---

## 作者：tder (赞：0)

我们观察数据范围，有 $a_i\ge2$，并且相邻两个 $a_x$ 和 $a_y$ 之和为质数，那么显然一奇一偶，而又为环，所以若有解 $n$ 必为偶数，且 $\sum[a_i\in\text{odd}]=\frac n2$。

那么，我们对于所有满足 $(a_x+a_y)\in\mathbb{P}$，连一条 $x\to y$ 的边。由于只能在奇数值和偶数值之间连边，于是显然是二分图，同时约定上文中的 $a_x\in\text{odd}$ 为左点，而 $a_y\in\text{even}$ 为右点。

与通常的二分图匹配不同的是，每个点可以连出两个边，于是将源点 $s$ 到左点 $i$ 的边 $s\to i$ 的容量设为 $2$，同样的，将右点 $j$ 到汇点 $t$ 的边 $j\to t$ 的容量设为 $2$。

那么，若有解，最后一定能匹配 $n$ 条边。

对于最后的构造方案，我们可以枚举每个左点，并在残量网络上跑 dfs 即可。

---

## 作者：Wilson_Lee (赞：0)

### 形式化题意

------------

给你 $n$ 个整数，需要将它们分成任意个至少包含 $3$ 个数的环，使得相邻两个数的和是质数。

## 做法

注意到 $a_i\ge2$，显然质数是需要一奇一偶构成，所以可以按奇偶构一个二分图。那么每个狐狸就要和两个狐狸相邻（匹配），因此可以将源点和所有奇数狐狸连一条流量为 $2$ 的边，所有偶数狐狸向汇点连一条流量为 $2$ 的边，所有能够匹配的奇偶狐狸间连一条流量为 $1$ 的边，跑最大流，若满流说明有解。

输出方案：按照流量在网络上搜即可，具体看代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN=405;
const int MAXM=4e4+5;
const int MAXK=2e4+1;
const int INF=100;
struct EDGE
{
    int to,nxt,flow;
}edge[MAXM];
vector<int>ans[MAXN];
int head[MAXN],tot=1;
int d[MAXN],now[MAXN],a[MAXN];
int n,s,t,maxflow,cnt;
bool isprime[MAXK],vis[MAXN];
void add(int x,int y,int z)
{
    edge[++tot]=(EDGE){y,head[x],z},head[x]=tot;
    edge[++tot]=(EDGE){x,head[y],0},head[y]=tot;
}
void init()
{
    memset(isprime,true,sizeof(isprime));
    for(int i=2;i*i<MAXK;++i)
        if(isprime[i])
            for(int j=i*2;j<MAXK;j+=i)
                isprime[j]=0;
}
bool bfs()
{
    queue<int>q;
    memset(d,0,sizeof(d));
    d[s]=1,now[s]=head[s],q.push(s);
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=edge[i].nxt)
        {
            int y=edge[i].to,z=edge[i].flow;
            if(d[y] || !z) continue;
            d[y]=d[x]+1,now[y]=head[y],q.push(y);
            if(y==t) return 1;
        }
    }
    return 0;
}
int dinic(int x,int flow)
{
    if(x==t) return flow;
    int incf=0;
    for(int i=now[x];i;i=edge[i].nxt)
    {
        now[x]=i;
        int y=edge[i].to,z=edge[i].flow;
        if(d[y]==d[x]+1 && z)
        {
            int tmp=dinic(y,min(flow-incf,z));
            if(tmp) edge[i].flow-=tmp,edge[i^1].flow+=tmp,incf+=tmp;
            else d[y]=0;
            if(incf==flow) return incf;
        }
    }
    return incf;
}
void output(int x)
{
    if(vis[x]) return;
    ans[cnt].push_back(x),vis[x]=1;
    for(int i=head[x];i;i=edge[i].nxt)
    {
        int y=edge[i].to;
        if(y<=n && !vis[y] && (((a[x]&1) && !edge[i].flow) || (!(a[x]&1) && edge[i].flow)))
        {
            output(y);
            break;
        }
    }
}
int main()
{
    init();
    cin>>n;
    s=n+1,t=n+2;
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    int cnt1=0,cnt2=0;
    for(int i=1;i<=n;++i)
        if(a[i]&1) add(s,i,2),++cnt1;
        else add(i,t,2),++cnt2;
    if(cnt1!=cnt2)
    {
        printf("Impossible");
        return 0;
    }
    for(int i=1;i<=n;++i)
        if(a[i]&1)
            for(int j=1;j<=n;++j)
                if(!(a[j]&1) && isprime[a[i]+a[j]])
                    add(i,j,1);
    while(bfs()) maxflow+=dinic(s,INF);
    if(maxflow==cnt1*2)
    {
        for(int i=1;i<=n;++i) if(!vis[i]) ++cnt,output(i);
        printf("%d\n",cnt);
        for(int i=1;i<=cnt;++i)
        {
            printf("%ld",ans[i].size());
            for(auto x:ans[i]) printf(" %d",x);
            putchar('\n');
        }
    }
    else printf("Impossible");
    return 0;
}
```


---

