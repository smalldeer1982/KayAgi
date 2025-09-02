# [USACO04OPEN] Cave Cows 4

## 题目描述

一道竖直的石墙横在贝茜前面，她必须越过去。

石墙可以看成一个xz平面，贝茜开始的时候在(0，0)，只要她到达 $ z=T $ 
 ( $ 1 \leq T \leq 200000 $ )的位置，就算翻越成功。

墙上有 $ N $ ( $ 1 \leq N \leq 50000 $ )块石头突出，成为贝茜的落蹄石。如果两个落蹄石之间x方向和z方向的距离均不超过2，那贝茜就可以攀上另一块落蹄石。

帮助贝茜计算她是否能够翻越石墙，如果可以，最少需要踩多少块落蹄石。

## 说明/提示

一种可行的方案是：(0,0) -> (1,2) -> (3,2) -> (4,1) -> (6,3) 。

## 样例 #1

### 输入

```
5 3
1 2
6 3
4 1
3 2
0 2```

### 输出

```
4```

# 题解

## 作者：LJC00118 (赞：8)

简单 $ bfs $

直接枚举两个点判断能否连边，复杂度 $ n^2 $，不可行

发现每个石头能够到达的点有限，只有自己周围的几个格子，于是用 $ map $ 存每一个格子中有哪块石头，枚举自己周围的石头进行连边后 $ bfs $ 即可

~~因为 map 很慢，你可能需要 O2~~

```cpp
#include <bits/stdc++.h>
#define Fast_cin ios::sync_with_stdio(false), cin.tie();
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

const int N = 5e4 + 5, INF = 0x7fffffff;

map <pair <int, int>, int> pre;
queue <int> q;
vector <int> adj[N];
int x[N], y[N], dis[N];
int n, t, m;

int main() {
    read(t); read(m); while(t--) {
        int a, b; read(a); read(b);
        pair <int, int> t = make_pair(a, b);
        if(pre.count(t)) continue;
        x[++n] = a; y[n] = b; pre[t] = n;
    }
    n++; x[n] = 0; y[n] = 0; pre[make_pair(0, 0)] = n;
    for(register int i = 1; i <= n; i++) {
        for(register int t1 = -2; t1 <= 2; t1++) {
            for(register int t2 = -2; t2 <= 2; t2++) {
                if(!t1 && !t2) continue;
                int _x = x[i] + t1, _y = y[i] + t2;
                if(pre.count(make_pair(_x, _y))) {
                    adj[i].push_back(pre[make_pair(_x, _y)]);
                }
            }
        }
    }
    memset(dis, -1, sizeof(dis)); dis[n] = 0; q.push(n);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(register int i = 0; i < (int)adj[u].size(); i++) {
            int v = adj[u][i];
            if(dis[v] == -1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    int ans = INF;
    for(register int i = 1; i < n; i++) {
        if(y[i] == m && ~dis[i]) {
            ans = min(ans, dis[i]);
        }
    }
    if(ans == INF) ans = -1;
    print(ans, '\n');
    return 0;
}
```

---

## 作者：lidagua1004 (赞：2)

一道广搜的题。

一开始想的是访问到一个落脚石时枚举所有其他石头判断是否可以落脚。

但是我们发现这里搜索时每次都要进行一次 $O(n)$ 的搜索，最终的时间复杂度肯定高。

如何优化呢？

容易发现，一个点周围能符合要求的点只有 $24$ 个。

这样我们就可以换一个方法标记石头。

可以开一个二维数组，有石头的地方标为 $1$，否则标为 $0$。

这样每次判断可以到达哪些石头时只要枚举周围几个点即可。

可是二维数组开不了这么大，于是可以用 map 来储存。

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{//用结构体储存落脚石的信息
	int x,y,dep;//dep用来记录步数
};
queue<node> q;
int n,t,ans;
map<int,map<int,int> > mp,vis;//用map来储存石头的位置
int solve(){
	q.push({0,0,0});
	while(!q.empty()){//广搜
		int x=q.front().x;
		int y=q.front().y;
		int dep=q.front().dep;
		q.pop();
		if(y==t) return dep;
		for(int i=-2;i<=2;i++){
			for(int j=-2;j<=2;j++){
				int xi=x+i,yj=y+j;
				if(mp[xi][yj]&&!vis[xi][yj]){
					vis[xi][yj]=1;
					q.push({xi,yj,dep+1});
				}
			}
		}
	}
	return -1;//不行就返回-1
}
signed main(){
	cin>>n>>t;
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		mp[x][y]=1;
	}
	cout<<solve();
	return 0;
} 
```


---

## 作者：SmallTownKid (赞：2)

一个不同于已有题解的思路，算法就是最短路，先排序，然后对于每个点考虑哪些可以建边，因为排序后有单调性所以可以舍弃很多无效边 ,建图再跑最短路就不超时了，实际不到 $O(n^2)$ 
```
#include<bits/stdc++.h>
using namespace std;
int n,T,idx;
int head[50010],dis[50010],vis[50010];
struct node{
	int nxt,to,w;
}edge[10000010];
struct node2{
	int x,y;
}a[50010];
void add(int u,int v,int w)
{
	edge[++idx].nxt=head[u];
	edge[idx].to=v;
	edge[idx].w=w;
	head[u]=idx;
}
bool cmp(node2 a,node2 b)
{
	if(a.x!=b.x) return a.x<b.x;
	return a.y<b.y;
}
void dijkstra(int s)
{
	memset(dis,0x3f,sizeof(dis));
	priority_queue< pair<int,int> > q;
	q.push(make_pair(0,s));
	dis[s]=0;
	while(!q.empty())
	{
		int x=q.top().second;
		q.pop();
		if(vis[x])
		continue;
		vis[x]=1;
		for(int i=head[x];i;i=edge[i].nxt)
		{
			int y=edge[i].to;
			if(dis[x]+edge[i].w<dis[y])
			{
				dis[y]=dis[x]+edge[i].w;
				q.push(make_pair(-dis[y],y));
			}
		}
	}
}
int main()
{
	cin>>n>>T;
	a[0].x=0,a[0].y=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
	}
	sort(a+1,a+1+n,cmp);
	for(int i=0;i<=n;i++)//按x排了，检索y，x不行直接退 
	{
		for(int j=i+1;j<=n;j++)
		{
			if(abs(a[i].x-a[j].x)>2)
			break;
			if(abs(a[i].y-a[j].y)>2)
			continue;
			add(i,j,1);
			add(j,i,1);
		}
	}
	dijkstra(0);
	int ans=0x3f3f3f3f;
	for(int i=1;i<=n;i++)
	{
		if(a[i].y>=T)
		ans=min(ans,dis[i]);
	}
	if(ans==0x3f3f3f3f)
	cout<<"-1";
	else cout<<ans;
	return 0;
} 
```

---

## 作者：Light_az (赞：1)

## 拒绝优化，暴力搜索

当然，此处暴力并不是指深搜，而是指普通的广搜，下面大佬的代码令人难解，因此我来简化一下。

首先根据题意我们知道搜索跳石子的合法坐标条件是 $-2 \leq x_i-x_j \leq 2$ 以及 $-2 \leq y_i-y_j \leq 2$，那么我们只需要两个循环来枚举可行的方案，再使用标记数组防止重复的方案，最后套上广搜的模板，即可以轻松拿满本题的分数了。值得高兴的是，在 $50000$ 个方案内，可行的方案数并不多，因此即使我们使用哈希 `map` 不用优化我们也可以通过本题。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(int i=j;i<=n;i++)
#define Tr(v,e) for(int v:e)
#define D double
#define ps push_back
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e6+10,NN=1e4+10;
ll n,m,k,x,y,u,v,w,cnt=0,ans=0,t=0,l,r,len,T;
ll mini=INT_MAX,maxi=0,Mod;
string s1,s2;
map<int,map<int,int> > mp,vis;
struct Node{
	ll x,y,dep;
};
ll bfs(){
	queue<Node> q;
	q.push({0,0,0});//起点
	while(!q.empty()){
		Node p=q.front();
		q.pop();
		if(p.y==k) return p.dep;//有解
		F(i,-2,2) F(j,-2,2){//判断合法方案
			x=p.x+i,y=p.y+j;
			if(mp[x][y]&&!vis[x][y]){//合法
				vis[x][y]=1;//标记避免重复
				q.push({x,y,p.dep+1});//广搜
			}
		}
	}
	return -1;//无解
}
int main(){
	cin>>n>>k;
	F(i,1,n){
		cin>>x>>y;
		mp[x][y]=1;//编辑建边
	}
	cout<<bfs();
	return 0;
}
```


---

## 作者：快斗游鹿 (赞：0)

广搜。

最简单的想法就是，对于搜到的每一个点，都把剩下 $n-1$ 个点枚举一遍，看看能不能走。但这样太慢了。

怎么办呢？发现题目中限制条件是不超过 $2$。容易发现，一个点周围能符合要求的点数只有 $24$ 个点。这时采用 `map` 来标记一个坐标是否出现过就行了。

还有一个优化，就是对于每个第一次扔进队列里的点，都打上标记，下次遇到就不做处理了。为什么呢？因为第一次的代价一定小于后面的，这时再处理没有任何意义。

代码：

```
#include<bits/stdc++.h>
using namespace std;
const int N=5e4+5;
struct Node{
	int xx,zz,step;
};
int n,t,x[N],z[N];
queue<Node>q;
map<pair<int,int>,int>mp,flag;
int fx[50]={0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,-1,-1,-1,-1,-1,-2,-2,-2,-2,-2};
int fy[50]={0,1,-1,2,-2,0,1,-1,2,-2,0,1,-1,2,-2,0,1,-1,2,-2,0,1,-1,2,-2};
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void BFS(){
	q.push({0,0,0});
	while(!q.empty()){
		int xx=q.front().xx;
		int zz=q.front().zz;
		int step=q.front().step;q.pop();
		if(zz==t){
			cout<<step;return;
		}
		for(int i=1;i<=24;i++){
			int xxx=xx+fx[i];
			int zzz=zz+fy[i];
			if(!mp[make_pair(xxx,zzz)]||flag[make_pair(xxx,zzz)])continue;
			flag[make_pair(xxx,zzz)]=1;
			q.push({xxx,zzz,step+1});
		}
	}
	puts("-1");
}
int main(){
	n=read();t=read();
	for(int i=1;i<=n;i++)x[i]=read(),z[i]=read(),mp[make_pair(x[i],z[i])]=1;
	BFS();
	return 0;
}

```


---

## 作者：i_love_tym (赞：0)

这题 bfs 即可，具体实现方法如下。

首先，因为 $1\leq T \leq 2 \times 10^5,x \leq 10^6$，所以数组是不可能用来标记 ``vis`` 和是否可以落脚的，那么我们就可以使用 ``map`` 来代替数组。

定义方法：```map<int,map<int int>>``` $+$ 数组名。

使用方式在这题中与正常数组一样。

那怎么实现 bfs 呢？大家可以先看看 [P1443](https://www.luogu.com.cn/problem/P1443)，这两题的 bfs 实现基本一样。在 ``P1443`` 中，是遍历所有可以到的点，如果符合条件就入队。那么我们可以照着这个思路写一写这题的 bfs。

我们不难写出下面代码：

```
while(!q.empty()){
	node d=q.front();
	q.pop();	
	if(d.y==t) {
		cout<<d.ans;
		return 0;
	}
	for(int i=-2;i<=2;i++){
		for(int j=-2;j<=2;j++){
			int x=d.x+i, y=d.y+j;
			if(m[x][y]&&!vis[x][y]){
				q.push((node){x,y,d.ans+1});
				vis[x][y]=1;
			}
		}
	}
}
```

这便是此题的 bfs 部分。

完整代码就不放了，难点主要就在 bfs 上。

有问题可以私信我。

---

## 作者：Zvelig1205 (赞：0)

提供一种不同的解法：DBFS（双向广度优先搜索）。

一方面，我们可以从坐标为 $(0,0)$ 的点出发，去找纵坐标为 $t$ 的点；

另一方面，我们可以从纵坐标为 $t$ 的点出发，去找 $(0,0)$。

这样的话，我们规定，从 $(0,0)$ 出发走过的点标记为 $1$，从纵坐标为 $t$ 的点出发走过的点标记为 $2$，未走过的点标记为 $0$。

每到达一个点，判断其标记：

* 未走过，标记，点入队列。
* 与当前点相同，路径重复。
* 与当前点不同，找到通路。

现在的问题就在于怎么找点。

可以用一个 `map` 标记某个坐标**有没有点**，**点的标记情况**，**到当前点的最短距离**。

然后暴力枚举每个点周围的 $24$ 个位置是否有点，有则加入队列。

最后的答案就是当前的步数 $+1$ 与不同点的步数之和。

```cpp
typedef pair<int,int> Pr;
int n,m;
struct node{
	int have,vis,step;
};
map<Pr,node>v;
struct dots{
	int x,y,k,op;
	dots(int x,int y,int k=0,int op=0):
		x(x),y(y),k(k),op(op){}
};
queue<dots>h;
int main()
{
	n=re();m=re();
	h.push(dots(0,0,0,1));
	v[Pr(0,0)].vis=1;
	for(int i=1;i<=n;i++)
	{
		int x=re(),y=re();
		v[Pr(x,y)].have=1;
		if(y==m)
		{
			h.push(dots(x,y,0,2));
			v[Pr(0,0)].vis=2;
		}
	}
	while(h.size())
	{
		dots now=h.front();h.pop();
		for(int i=-2;i<=2;i++)
		{
			for(int j=-2;j<=2;j++)
			{
				if(i==0&&j==0)continue;
				int x=now.x+i,y=now.y+j;
				if(v[Pr(x,y)].have)
				{
					if(v[Pr(x,y)].vis==0)
					{
						v[Pr(x,y)].vis=now.op;
						v[Pr(x,y)].step=now.k+1;
						h.push(dots(x,y,now.k+1,now.op));
					}
					if(v[Pr(x,y)].vis==now.op)
						continue;
					wr(v[Pr(x,y)].step+now.k+1,'\n');
					return 0;
				}
			}
		}
	}
	puts("-1");
	return 0;
}
```


---

## 作者：BreakPlus (赞：0)

$\large \text{Solution:}$

题目中没有输入起点的坐标，我们为了方便可以将它存在数组的 $0$ 号位置。

$x,z$ 距离不超过 $2$ ？ 暴力连边 $\text{O}(n^2)$ 不可行，考虑 ``map`` 来存储某个坐标的编号。

对于连边方式因人而异，本人使用的是链式前向星。

连边过后，我们考虑 $\texttt{SPFA}$ 。其实队列中存放的不是坐标而是编号，不然又要用到 ``map`` ，它的常数巨大，所以我们连的边也应该连序号。

跑完 $\texttt{SPFA}$ 过后，寻找最小值。要注意特判走不到的情况。

另外可能连很多边！！我在这里卡了很多次，链式前向星的数组要开大一些。

~~常数太大，开 $\text{O2}$ 喽！~~


$\large \text{Code:}$

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#include<map>
using namespace std;
const int maxn=5e4+10;
int n,t,x[maxn],z[maxn],dis[maxn];
bool vis[maxn];
map<int,map<int,int> >M;//编号
map<int,map<int,int> >B;//是否存在
struct Edge{
	int to,next;
}edge[1000010];
int head[1000010],tot;//开大点
void add(int u,int v){
	tot++;
	edge[tot].to=v;
	edge[tot].next=head[u];
	head[u]=tot;
}
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int main(){
	for(register int i=0;i<maxn;i++) dis[i]=2e9;
	n=read(),t=read();
	for(register int i=1;i<=n;i++) {x[i]=read(),z[i]=read(); M[x[i]][z[i]]=i;B[x[i]][z[i]]=true;}
	M[0][0]=0; B[0][0]=true;
	for(register int i=0;i<=n;i++)
		for(register int j=-2;j<=2;j++)
			for(register int k=-2;k<=2;k++)
				if(B[x[i]+j][z[i]+k]) add(i,M[x[i]+j][z[i]+k]),add(M[x[i]+j][z[i]+k],i);// 连边（要算上起点）
	queue<int>q;
	q.push(0);//从起点开始
	dis[0]=0;
	while(!q.empty()){
		int X=q.front();
		q.pop();
		if(vis[X]) continue;
		vis[X]=true;
		for(register int i=head[X];i;i=edge[i].next){
			int tmp=edge[i].to;
			if(dis[X]+1<dis[tmp]){
				dis[tmp]=dis[X]+1;
				if(!vis[tmp]) q.push(tmp);
			}
		}
	}//SPFA
	int ans=2e9;
	for(register int i=0;i<=n;i++)
		if(z[i]==t && dis[i]<ans) ans=dis[i];
	if(ans==2e9) puts("-1");
	else printf("%d\n",ans);
	return 0;
}
```

$\large \text{Others}$

大战前夕，这是我 $\text{CSP2020}$ 之前做的最后一题。$\text{CSP}$ 是一年 $\text{OI}$  比赛的新起点，衷心祝大家 $\text{CSP2020 Score++ RP++}$！

---

## 作者：littleKtian (赞：0)

考虑石头之间如何建边

因为在建边时我们只需要考虑自身这行以及其下面两行中的石头，所以先将石头按$z$坐标排序，数组$lb[i][j]$记录坐标$(i,j)$位置的石头编号，在一定范围内枚举即可

因为$t$值较大会爆空间，可以用滚动数组的方法记录

建边后用bfs即可求出答案

```
#include<bits/stdc++.h>
using namespace std;
struct stone{
	int x,z;
};
stone ro[50005],ls[50005];
bool vi[50005];
int lst[50005],lsw[50005],bi[3000005][2],bs;
int dl[50005],tzz,wzz,f[50005];
int lb[3][1000005];
int n,t;
int dr()//快读 
{
	int xx=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')xx=(xx<<1)+(xx<<3)+ch-'0',ch=getchar();
	return xx;
}
void px(int l,int r)//手打排序 
{
	if(l==r)return;
	int mid=(l+r)>>1;
	px(l,mid),px(mid+1,r);
	int i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r)
	{
		if(ro[i].z<ro[j].z||(ro[i].z==ro[j].z&&ro[i].x<=ro[j].x))ls[k++]=ro[i++];
		else ls[k++]=ro[j++];
	}
	while(i<=mid)ls[k++]=ro[i++];
	while(j<=r)ls[k++]=ro[j++];
	for(i=l;i<=r;i++)ro[i]=ls[i];
}
void tj(int u,int v)//建边 
{
	++bs;
	if(lst[u]==0)lst[u]=bs;
	else bi[lsw[u]][0]=bs;
	bi[bs][1]=v,lsw[u]=bs;
}
int main()
{
	n=dr()+1,t=dr();
	ro[1]=(stone){0,0};
	for(int i=2;i<=n;i++)ro[i].x=dr(),ro[i].z=dr();
	px(1,n);
	for(int i=1;i<=n;i++)
	{
		for(int j=max(0,ro[i].x-2);j<=ro[i].x+2;j++)
		  for(int k=0;k<3;k++)
		    if(lb[k][j]&&ro[i].z-ro[lb[k][j]].z<3)tj(i,lb[k][j]),tj(lb[k][j],i);//因为是无向边，要建两条边
		lb[ro[i].z%3][ro[i].x]=i;
	}
	/*
	建边的过程中并不需要将lb数组清空，可以在枚举时判断是否可行（清空可能会超时）
	*/
	dl[++wzz]=1,f[1]=0,vi[1]=true;
	while(tzz<wzz)//bfs 
	{
		++tzz;
		int u=dl[tzz],o_o=lst[u];
		while(o_o)
		{
			int v=bi[o_o][1];
			if(!vi[v])
			{
				vi[v]=true;
				f[v]=f[u]+1;
				if(ro[v].z==t){printf("%d",f[v]);return 0;}
				dl[++wzz]=v;
			}
			o_o=bi[o_o][0];
		}
	}
	printf("-1");
}//成功混到最优解
```


---

## 作者：HRLYB (赞：0)

### ~~玄学题目卡时间~~

楼下的巨佬说要用map来存图，~~在我看来完全不需要~~实际上是不必要的。我们在建边时适当剪枝，就可以把这道题卡过了

而且他的一堆template类模板我也看不懂，所以发一份比较简洁的

另外，手写队列会比$STL$的队列快，而且不止快一倍两倍，所以见到这种玄学卡时就得想想要不要手写

$bfs$的思路大家想必都清楚（毕竟是分层找最小值嘛）我在这里用了一个vis数组，来存一个点是否访问过,易证如果一个点已经走过了，那么接下来路径一定不会再经过这个点，否则就不是最优的了


------------


------------


------------


稍微放下代码

~~在这里我偷个懒，放一份吸了氧的$queue$~~

```cpp
#include<bits/stdc++.h>
#define maxn 50010
using namespace std;
int n,h,dis[maxn];
struct stone{
	int x,y;
}s[maxn];
struct edge{
	int v,next;
}e[maxn*5];//不要忘记边比点多
queue<int >q;
bool vis[maxn];
int head[maxn],num;
inline void add(int u,int v){
	e[++num].v =v;
	e[num].next =head[u];
	head[u]=num;
}
inline void bfs(){
	while(!q.empty()){
		int u=q.front();
		if(s[u].y ==h){
			printf("%d\n",dis[u]);
			exit(0);//程序直接终止
		}
		for(register int i=head[u];i;i=e[i].next ){
			int v=e[i].v ;
			if(!vis[v]){
				vis[v]=true;
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
		q.pop();
	}
}
int main(){
	scanf("%d%d",&n,&h);
	int x,y;
	for(register int i=1;i<=n;i++){
		scanf("%d%d",&x,&y);
		s[i].x =x,s[i].y =y;
		if(s[i].x <=2&&s[i].y <=2){
			q.push(i);
			vis[i]=true;
			dis[i]=1;
		}//一点准备工作
		for(register int j=1;j<i;j++){//abs的速度较慢，也可以用三目手写
			if(abs(s[i].x -s[j].x )<=2&&abs(s[i].y -s[j].y )<=2){
				add(i,j);
				add(j,i);//双向建边
			}
		} 
	}
	bfs();
	printf("-1\n");//如果进行完bfs还没终止，输出-1（第6、7个点）
	return 0;
}

//1548ms, ok accepted

```


---

