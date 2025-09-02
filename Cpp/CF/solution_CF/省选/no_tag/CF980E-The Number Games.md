# The Number Games

## 题目描述

Panel 国将举办名为数字游戏的年度表演。每个省派出一名选手。

国家有  $n$  个编号从  $1$  到  $n$  的省，每个省刚好有一条路径将其与其他省相连。第  $i$  个省出来的代表有  $2^i$  名粉丝。

今年，主席打算削减开支，他想要踢掉  $k$  个选手。但是，被踢掉的选手的省将很 angry 并且不会让别的任何人从这个省经过。

主席想确保所有剩下选手的省都互相可达，他也希望最大化参与表演的选手的粉丝数。

主席该踢掉哪些选手呢？

## 样例 #1

### 输入

```
6 3
2 1
2 6
4 2
5 6
2 3
```

### 输出

```
1 3 4
```

## 样例 #2

### 输入

```
8 4
2 6
2 7
7 8
1 2
3 1
2 4
7 5
```

### 输出

```
1 3 4 5
```

# 题解

## 作者：AubRain (赞：8)

显然错误的思路：用堆维护叶子节点的编号最小值。依次删除即可。

正确的做法；

因为是二进制，所以是要 **从大到小** 贪心的，尽可能的保留编号大的节点，这样肯定是最优的。

首先 $n$ 节点肯定要保留，不妨把它作为根。然后编号从大到小依次判断能否保留。

如果想要保留的话，就要把该节点到根的路径所有点都要留下来。如果加起来不超过 $n-k$ 就是合法的。否则就不保留。

如何记录每个点到根有多少没被保留的节点？

用 $dfs$ 序+树状数组维护即可，每次保留时把子树加改为$dfs$ 序上区间加。然后每次暴力标记点就行了，因为每个点最多被标记一次。

代码：

```cpp
#include <bits/stdc++.h>
#define N 1000005
using namespace std;

inline void rd(int &X){
    X=0;int w=0;char ch=0;
    while(!isdigit(ch))w|=ch=='-',ch=getchar();
    while( isdigit(ch))X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    X=w?-X:X;
}

int n,k,tot,now;
int head[N],cnt;
int sz[N],dfn[N],ok[N],f[N],g[N],d[N];
struct nd{int nxt,to;}e[N<<1];

inline void ins(int x,int pd){
	for(;x<=n;x+=x&-x) g[x]+=pd;
}
inline int ask(int x,int ans=0){
	for(;x;x-=x&-x) ans+=g[x]; return ans;
}
inline void add(int x,int y){
	e[++cnt]=(nd){head[x],y};head[x]=cnt;
	e[++cnt]=(nd){head[y],x};head[y]=cnt;
}
void dfs(int x,int fa=0){
	f[x]=fa;dfn[x]=++tot;d[x]=d[fa]+1;sz[x]=1;
	for(int y,i=head[x];(y=e[i].to);i=e[i].nxt)
		if(y!=fa) dfs(y,x),sz[x]+=sz[y];
}
void work(int x){
	if(d[x]-ask(dfn[x])+now>k) return ;
	for(;x!=n;x=f[x]){
		if(ok[x]) break;
		ok[x]=1;ins(dfn[x],1);ins(dfn[x]+sz[x],-1);now++;
	}
}
signed main(){
	rd(n);rd(k);k=n-k;
	for(int x,y,i=1;i<n;i++)
		rd(x),rd(y),add(x,y);
	ok[n]=1;dfs(n);
	for(int i=n-1;i;i--)
		if(!ok[i]) work(i);
	for(int i=1;i<=n;i++)
		if(!ok[i]) printf("%d ",i);
}
```

---

## 作者：Nasaepa (赞：4)

这是道紫题，但是非常的水。主要难在怎么想到把删点转化成选点。

***

这道题思路就是**贪心** + **倍增**。删点很复杂，我们可以倒过来选点组成图。我们定义一个整数 $t = n - k$ 作为我们需要选择的点的点数。

首先我们论证一下这道题可以贪心。我们都知道，$2^i \gt 2^{i-1} + 2^{i-2} + \dots + 2^1$ ，这个推一下就知道了，顾不做讲解。因此，第 $i$ 个节点贡献的粉丝人数一定大于第 $1$ 到第 $i-1$ 贡献的粉丝人数之和。这就代表，如果选择第 $i$ 个节点需要舍弃第 $1$ 到第 $i-1$ 个节点，我们**宁愿舍弃**第 $1$ 到第 $i-1$ 和节点，**也要选择**第 $i$ 个节点。

贪心的思路知道了，我们就可以开始选点了。根据如上的推论，第 $n$ 个节点**绝对要选**。因此，$t$ 需要减掉 $1$ 代表选择了 $n$ 号节点。随后，我们需要从第 $n-1$ 个节点枚举到第 $1$ 个节点。假设我们已经选择了**黑色节点**，**绿边**连接的是还没有选择的节点，**黑边**链接的是已经选择的节点，当前遍历到了**蓝色节点**。

![](https://cdn.luogu.com.cn/upload/image_hosting/xkjaipch.png)

那么我们就要从蓝色节点向上跳，找到离这个节点**最近的黑色节点**。这个实现起来非常简单。我们设置一个 $f$ 数组，$f_{i,j}$ 代表从第 $i$ 个节点向上走 $2^j$ 步可以到达的节点。我们可以利用 $f_{i,j} = f_{f_{i,j-1},j-1}$ 求出 $f$ 数组。随后，求出第 $i$ 个节点与**最近的黑色节点的距离**，这个值即把第 $i$ 个节点选入图中需要花费的**选点名额数量**。代码如下：

```cpp
void dfs(const int &idx,const int &dad){
    // 解决 f 节点
    for(int i = 1;i <= 20;++i)f[idx][i] = f[f[idx][i-1]][i-1];
    for(int edg = head[idx];edg;edg = nxt[edg]){
        if(to[edg] == dad)continue;
        d[to[edg]] = d[idx] + 1;
        f[to[edg]][0] = idx;
        dfs(to[edg],idx);
    }
}
inline int dist(int x){
    int ans = 0;
    for(int i = 20;i >= 0;--i){
        if(!used[f[x][i]]){
            ans += (1<<i);
            x = f[x][i];
        }
    }
    return ans + 1;
}
```

其中，`dfs` 函数用于初始化 $f$ ，`dist` 函数用于求出距离。随后，判断 $t \ge dist$ 是否成立。如果成立，则将第 $i$ 个节点即其所有没被选入的父节点都标记为**黑色节点**，随后 $t$ 赋值为 $t - dist$。

![](https://cdn.luogu.com.cn/upload/image_hosting/7ytd0to4.png)

如果不成立，则不做选择。

另外，当当前节点已经被标记为**黑色节点**时，我们便不对这个点进行处理。

代码如下：

```cpp
for(int i = n-1;i >= 1;--i){
    if(used[i])continue;
    // 争取剩下的节点都能入
    tmp = dist(i);
    if(tmp <= t){
        t -= tmp;
        // 向上寻找
        tmp = i;
        while(!used[tmp]){
            used[tmp] = 1;
            tmp = f[tmp][0];// 向上
        }
    }
}
```

代码中，$used$ 数组标记当前节点是否被标记为**黑色节点**。

当这些处理完了之后，我们便遍历 $used$ 数组，如果 $used_i$ 为 $0$ ，则输出 $i$ 。

完整代码如下：

```cpp
// #pragma GCC optimize(2) // 开启O2优化
#include<bits/stdc++.h>
using namespace std;
#define N 1000010 // 最大数据范围 = 1e6+10
#define INF 0x3f3f3f3f // 无穷大
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define func function<void()> 
namespace weighted_Graph{
    int head[N],nxt[N<<1],to[N<<1];//三个数组，分别为节点的第一条边，边的下一条边，边指向的节点
    int cnt_edge = 0;//边的个数
    inline void connect_head(const int &x,const int &y){//头部插入函数O(1)
        ++cnt_edge;
        nxt[cnt_edge] = head[x];
        head[x] = cnt_edge;
        to[cnt_edge] = y;
    }
}
using namespace weighted_Graph;
int n,a,b,t,k,tmp;
int f[N][25];
int d[N];
bool used[N];
// x 节点向上到 used 节点需要的路径
inline int dist(int x){
    int ans = 0;
    for(int i = 20;i >= 0;--i){
        if(!used[f[x][i]]){
            ans += (1<<i);
            x = f[x][i];
        }
    }
    return ans + 1;
}

void dfs(const int &idx,const int &dad){
    // 解决 f 节点
    for(int i = 1;i <= 20;++i)f[idx][i] = f[f[idx][i-1]][i-1];
    for(int edg = head[idx];edg;edg = nxt[edg]){
        if(to[edg] == dad)continue;
        d[to[edg]] = d[idx] + 1;
        f[to[edg]][0] = idx;
        dfs(to[edg],idx);
    }
}

// 输入函数
void input(){
    scanf("%d%d",&n,&k);
    t = n - k - 1;
    for(int i = 1;i<n;++i){
        scanf("%d%d",&a,&b);
        connect_head(a,b);
        connect_head(b,a);
    }
    dfs(n,-1);
}

// 处理函数
void solve(){
    // 判断 n-1 个节点是否可以加入
    used[0] = used[n] = 1;
    for(int i = n-1;i >= 1;--i){
        if(used[i])continue;
        // 争取剩下的节点都能入
        tmp = dist(i);
        if(tmp <= t){
            t -= tmp;
            // 向上寻找
            tmp = i;
            while(!used[tmp]){
                used[tmp] = 1;
                tmp = f[tmp][0];// 向上
            }
        }
    }
}

// 输出函数
void output(){
    for(int i = 1;i<=n;++i)if(!used[i])printf("%d ",i);
}

// 主函数
int main(int argc,char* argv[]){
    input();
    solve();
    output();
    system("pause");
    return 0;
}
```

---

## 作者：xh39 (赞：4)

请先学会倍增算法再来看本题解。

建议看题解时要自己照着题解意思画图。

题意:给定一棵树，第 $i$ 个节点权值为 $2^i$。求其权和最大且需要删掉 $m$ 个结点的联通子图。

$1+2+4+...+2^{n}=2^{(n+1)}-1$。这个是小学奥数，故不写计算过程。

所以可见如果一个数不选，比它小的数无论如何选都无法补救。所以尽可能从大的选。

注意:不能从小的结点开始删，因为无法保证图的连通性。还有一种错误的算法是每次删最小的叶节点保证图联通。但是也是不正确的。比如对于这棵树 ```2-4-5-1-3```，按此算法会将 $2,3$ 删去,但显然删 $1,3$ 更好。

首先，如果 $m=n$，说明要删掉所有结点，特判即可。否则必须选$n$结点。

将题目中的删去结点改为选结点。接下来从 $(n-1)$ 到 $1$ 依次选。设当前选的是 $i$结点。如果可选则一定选 $i$ 结点。但是不能仅选取 $i$ 结点，还需选取其它结点确保已选结点联通。现在问题就是判断是否可选。

因为目前可选结点联通。而整棵树**不存在回路**，所以 $i$ 结点在仅经过未选结点时，**恰好连到其中的 1 个结点**。(下面称这个结点为 a)

而它们中间的结点全部都需要选,所以只需要判断需要选的结点数是否小于目前还可选的结点数。若小于则说明可以选。并将中间这些点都选上。

现在的问题是如何找到 a。若 $i$ 结点已选,则说明 a 就是 $i$ 结点。$n$ 结点一定选。并且已选的点是联通的。所以 $i$ 结点到 $n$ 结点的路径上一定是有一部分是已选,一部分未选。并且**这两部分的结点都在一起(构成链)**。

所以相当于满足单调,就用倍增算法做即可。求出两点距离也用倍增算法优化即可。求距离也用倍增算法即可。求距离也用倍增即可。

实现时以 $n$ 结点为根即可。

时间复杂度:由于每个节点最多被选一次，所以是 $O(n)$，加上倍增就是 $O(n\times \log_{2}(n))$。

```cpp
#include<iostream>
using namespace std;
struct xyq{
	int v,next;
}_[2000005];
int head[1000005],tot=1;
void add(int u,int v){
	_[tot].v=v;
	_[tot].next=head[u];
	head[u]=tot;
	tot++;
}
int f[21][1000005],dis[1000005];
void dfs(int iakioi,int step){
	dis[iakioi]=step;
	int i;
	for(i=head[iakioi];i;i=_[i].next){
		if(!dis[_[i].v]){
			f[0][_[i].v]=iakioi;
			dfs(_[i].v,step+1);
		}
	}
}
bool chose[1000005]; //chose:已选。zyl:已选结点的父亲。 
int main(){
	int n,m,i,j,A,B,ykb=-1,logn,now,sum=0;
	cin>>n>>m;
	m=n-m;
	if(!m){ //一个结点都不能选,什么都不需要输出。
		return 0;
	}
	for(logn=0;(1<<logn)<=n;logn++){
	}
	for(i=1;i<n;i++){
		scanf("%d %d",&A,&B);
		add(A,B);
		add(B,A);
	}
	f[0][n]=n;
	dfs(n,1);
	for(i=1;i<=logn;i++){
		for(j=1;j<=n;j++){
			f[i][j]=f[i-1][f[i-1][j]];
		}
	}
	chose[n]=1;
	m--;
	for(i=n-1;i>=1;i--){
		if(chose[i]){ //特判如果被选过则不需要再选。否则有可能出错。(sum 最终会算成 1)。
			continue;
		}
		now=i;
		sum=0;
		for(j=logn;j>=0;j--){
			if(!chose[f[j][now]]){
				now=f[j][now];
				sum+=(1<<j); //(1<<j)=pow(2,j)。跳了 2 的 j 次方步。
			}
		}
		now=f[0][now]; //这里倍增找出的是仍未选过的深度最小结点。所以还需要跳一步。
		sum++;
		if(sum<=m){ //如果可以选。将中间所有结点都选了。
			m-=sum;
			for(j=i;j!=now;j=f[0][j]){
				chose[j]=1;
			}
			chose[now]=1;
		}
	}
	for(i=1;i<=n;i++){
		if(!chose[i]){
			cout<<i<<" ";
		}
	}
	return 0;
}
```

---

## 作者：Albedo (赞：3)

# CF980E The Number Games

## Solution

我们发现，删去 $ k $ 个点，其实就是保留 $ n-k $ 个点，而且我们观察到，选一个 $ n $ 的价值，比选前面所有的总价值都要大，所以根据贪心，我们以 $ n $ 为根建树，然后从 $ n-1 $ 开始加点，每次判断加进来合不合法，如果合法就直接加进来，至于维护？一个树剖走天下。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
inline long long read()
{
  long long x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
long long pow(long long x,long long y,long long p)
{
	long long ans=1;
	for (;y;y>>=1,x=x*x % p)
		if (y&1) ans=ans*x % p;
	return ans;
}
long long gcd(long long x,long long y)
{
	if (y==0) return x;
	long long ans=gcd(y,x % y);return ans;
}
//build1:find depth,father,size,height_son 
//build2:find height_son's top and height_son's id
struct SegmentTree{
	int sum,mx,tag;
} tree[8010100];
struct node{
	int top,fa,siz,hson,dep;
} E[2010100];
int sum,K,H[2010100],dfn[2010100],e[2010100],a[2010100],b[2010100],d[2010100],ans;
int u,v,cnt,n,m,i,T,x,y,id;
bool exist[2010100];
void add(int x,int y)
{
	cnt++;a[cnt]=y;b[cnt]=d[x];d[x]=cnt;
}
void pushup(int x)
{
	tree[x].sum=tree[x*2].sum+tree[x*2+1].sum;
}
void pushdown(int x,int l,int r)
{
	int mid=(l+r)/2;
	if (tree[x].tag==1) tree[x*2].sum=0,tree[x*2].tag=1;
	if (tree[x].tag==1) tree[x*2+1].sum=0,tree[x*2+1].tag=1;
}
void build(int x,int l,int r)
{
	if (l==r)
	    {
	    	if (r!=dfn[n]) tree[x].sum=1;
			return ;
		}
	int mid=(l+r)/2;
	build(x*2,l,mid);build(x*2+1,mid+1,r);
	pushup(x);
}
void build1(int x,int fa)
{
	E[x].siz=1;int mx=0;E[x].hson=0;
	for (int i=d[x];i;i=b[i])
	   if (a[i]!=fa)
	     {
	     	E[a[i]].dep=E[x].dep+1;
            E[a[i]].fa=x;build1(a[i],x);E[x].siz+=E[a[i]].siz; 
			if (E[a[i]].siz>mx) mx=E[a[i]].siz,E[x].hson=a[i];    	
		 }
	if (E[x].hson!=0) exist[E[x].hson]=true;
}
void build2(int x,int fa)
{
	id++;dfn[x]=id;
	if (exist[x]==false) E[x].top=x;
	for (int i=d[x];i;i=b[i])
	    if (a[i]==E[x].hson)
	       {
	        	if (exist[a[i]]) E[a[i]].top=E[x].top;
	        	build2(a[i],x);
		    }
	for (int i=d[x];i;i=b[i])
	   if (a[i]!=E[x].hson)
	     if (a[i]!=fa)
	        {
	        	if (exist[a[i]]) E[a[i]].top=E[x].top;
	        	build2(a[i],x);
		    }
}
void modify(int x,int l,int r,int tl,int tr)
{
	if ((l>=tl)&&(r<=tr))
	     { 
	     tree[x].tag=1;
	     tree[x].sum=0;
	     return ;
		 }
	pushdown(x,l,r);
	int mid=(l+r)/2;
	if (mid>=tl) modify(x*2,l,mid,tl,tr);
	if (mid<tr) modify(x*2+1,mid+1,r,tl,tr);
	pushup(x);
}
long long query_sum(int x,int l,int r,int tl,int tr)
{
	if ((l>=tl)&&(r<=tr)) return tree[x].sum;
	pushdown(x,l,r);
	int mid=(l+r)/2;
	long long ans=0;
	if (mid>=tl) ans=ans+query_sum(x*2,l,mid,tl,tr);
	if (mid<tr) ans=ans+query_sum(x*2+1,mid+1,r,tl,tr);
	pushup(x);
	return ans;
}
int main()
{
	//ios::sync_with_stdio(0);cin.tie();cout.tie();
	char s[1010];
	n=read();K=read();K=n-K;
	for (i=1;i<n;i++) 
	    {
	    	x=read();y=read();
	    	add(x,y);add(y,x);
		 } 
	for (i=1;i<=n;i++) e[i]=1;
	E[n].dep=1;build1(n,0);build2(n,0);
	for (i=1;i<=n;i++) H[dfn[i]]=i;
	build(1,1,n);sum=1;
	for (i=n-1;i>=1;i--)
	     {
			     	ans=0;
			     	//cout<<E[E[v].top].fa<<endl;
			     	u=i;v=n;
	     	     	while (E[u].top!=E[v].top)
	     	     	     {
	     	     	     	if (E[E[u].top].dep>E[E[v].top].dep)
	     	     	     	    { 
	     	     	     	       ans=ans+query_sum(1,1,n,dfn[E[u].top],dfn[u]);
	     	     	     	       u=E[E[u].top].fa;
								   }
							else
							    {
							    	ans=ans+query_sum(1,1,n,dfn[E[v].top],dfn[v]);v=E[E[v].top].fa;
								}
						   }
					if (dfn[u]>dfn[v]) swap(u,v);
					ans=ans+query_sum(1,1,n,dfn[u],dfn[v]);
					if (sum+ans<=K)
					    {
					    	u=i;v=n;
						while (E[u].top!=E[v].top)
	     	     	     {
	     	     	     	if (E[E[u].top].dep>E[E[v].top].dep)
	     	     	     	    { 
	     	     	     	      modify(1,1,n,dfn[E[u].top],dfn[u]);
	     	     	     	       u=E[E[u].top].fa;
								   }
							else
							    {
							    	modify(1,1,n,dfn[E[v].top],dfn[v]);v=E[E[v].top].fa;
								}
						   }
					if (dfn[u]>dfn[v]) swap(u,v);
					modify(1,1,n,dfn[u],dfn[v]);
					    	sum+=ans;
						}
		 }
	for (i=1;i<=n;i++)
	   if (query_sum(1,1,n,dfn[i],dfn[i])==1)
	       printf("%d ",i);
	puts("");
 return 0;
}
```



---

## 作者：封禁用户 (赞：3)

思路没什么难度，我就简略阐述一下：

以n作为根跑dfs，从大到小依次判断能否保留,如果加起来不超过 n−k 就保留，否则就不保留。（贪心）

楼下几位大佬都用了树状数组来维护。其实，直接倍增即可。

然后没啥好说了，就贴个代码吧：

```cpp
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <string>
#include <cstring>
#include <algorithm>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <ctime>
#include <vector>
#include <fstream>
#include <list>
#include <iomanip>
#include <numeric>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define ms(s) memset(s, 0, sizeof(s))
const int INF = 1e9;
inline int read(){
	int X = 0,w = 0 ;
	char ch = 0;
	while(!isdigit(ch)) {w |= ch == '-';ch = getchar();}
	while(isdigit(ch)) X = (X<<3) + (X<<1) + (ch ^ 48),ch = getchar();
	return w ? -X : X;
}
int n,m;
bool vis[1000005];
vector<int> edg[1000005];
int par[1000005];
int tre[1000005][35];
int dep[1000005];
void dfs(int x,int f)
{
	par[x]=f;
	for(int i=0;i<edg[x].size();i++)
	{
		if(edg[x][i]!=f)
		{
			dep[edg[x][i]]=dep[x]+1;
			dfs(edg[x][i],x);
		}
	}
}
void dfs2(int x,int f)
{
	vis[x]=1;
	if(x==f)
	{
		return;
	}
	dfs2(par[x],f);
}
int main()
{
	cin>>n>>m;
	m=n-m;
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		x--,y--;
		edg[x].push_back(y);
		edg[y].push_back(x);
	}
	dfs(n-1,-1);
	memset(tre,-1,sizeof(tre));
	for(int i=0;i<n;i++)
	{
		tre[i][0]=par[i];
		for(int j=1;(1<<j)<n;j++)
		{
			tre[i][j]=-1;
		}
	}
	for(int j=1;(1<<j)<n;j++)
	{
		for(int i=0;i<n;i++)
		{
			if(tre[i][j-1]!=-1)
			{
				int a=tre[i][j-1];
				tre[i][j]=tre[a][j-1];
			}
		}
	}
	vis[n-1]=true;
	int sum=1;
	for(int i=n-2;i>=0;i--)
	{
		if(vis[i])
		{
			continue;
		}
		int t=i;
		for(int j=20;j>=0;j--)
		{
			if(tre[t][j]==-1)
			{
				continue;
			}
			else
			{
				if(!vis[tre[t][j]])
				{
					t=tre[t][j];
				}
			}
		}
		if(dep[i]-dep[t]+sum+1<=m)
		{
			sum+=dep[i]-dep[t]+1;
			dfs2(i,t);
		}
	}
	for(int i=0;i<n;i++)
	{
		if(!vis[i])
		{
			cout<<i+1<<' ';
		}
	}
	return 0;
}
```

感谢[Hal()](https://codeforces.com/profile/Hal0)巨佬提供的代码

---

## 作者：peterwuyihong (赞：3)

题意：给定一棵树和一个 $k$，第 $i$ 个点的点权是 $2^i$，求保留 $k$ 个点联通块的最大点权。

显然取了点 $o$ 得到的点权比取了 $o-1,o-2,\ldots1$ 的点权和还要大，于是倒序贪心取点，一个一个加点，使用一个树剖加线段树维护就行了。

具体来说，就是以 $n$ 为根，权值设为 $1$，代表选了这个点，然后倒着加点，加点时询问当前点到根的权值不为 $1$ 的个数，如果大于余量就跳过，否则就把这个点到根的所有权值涂成 $1$，代表全选，最后把所有权值为 $0$ 的输出就行了。

现在是 $14:40$，我看我什么时候写完。

现在是 $15:02$，我写完了。

```cpp
#define maxn 1000010
int n,k,s,x,y;
int head[maxn],Next[maxn<<1],ver[maxn<<1],tot;
void add(int x,int y){
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}
int dep[maxn],fa[maxn],siz[maxn];
int son[maxn],dfn[maxn],top[maxn],cnt;
void dfs1(int x){
	siz[x]=1;
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		if(dep[y])continue;
		dep[y]=dep[x]+1;
		dfs1(y);
		fa[y]=x;
		siz[x]+=siz[y];
		if(siz[son[x]]<siz[y])son[x]=y;
	}
}
void dfs2(int x,int t){
	top[x]=t;
	dfn[x]=++cnt;
	if(!son[x])return;
	dfs2(son[x],t);
	for(int i=head[x];i;i=Next[i])
	if(ver[i]!=fa[x]&&ver[i]!=son[x])dfs2(ver[i],ver[i]);
}
struct prpr{
	int l,r;
	int tg,sm;
}tree[maxn<<2];
void pushup(int x){
	tree[x].sm=tree[x<<1].sm+tree[x<<1|1].sm;
}
void pushdown(int x){
	if(tree[x].tg){
		tree[x<<1].tg=tree[x<<1|1].tg=1;
		tree[x<<1].sm=tree[x<<1].r-tree[x<<1].l+1;
		tree[x<<1|1].sm=tree[x<<1|1].r-tree[x<<1|1].l+1;
		tree[x].tg=0;
	}
}
void build(int l,int r,int x=1){
	tree[x].l=l,tree[x].r=r;
	if(l==r){
		tree[x].sm=l==1;
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,x<<1);
	build(mid+1,r,x<<1|1);
	pushup(x);
}
int ask(int l,int r,int x=1){
	if(tree[x].l>=l&&tree[x].r<=r)return tree[x].sm;
	pushdown(x);
	int mid=(tree[x].l+tree[x].r)>>1;
	int ans=0;
	if(l<=mid)ans+=ask(l,r,x<<1);
	if(r>mid)ans+=ask(l,r,x<<1|1);
	return ans;
}
void change(int l,int r,int x=1){
	if(tree[x].l>=l&&tree[x].r<=r){
		tree[x].sm=tree[x].r-tree[x].l+1;
		tree[x].tg=1;
		return;
	}
	pushdown(x);
	int mid=(tree[x].l+tree[x].r)>>1;
	if(l<=mid)change(l,r,x<<1);
	if(r>mid)change(l,r,x<<1|1);
	pushup(x);
}
int ask(int x){
	int ans=0;
	while(x){
		ans+=ask(dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	return ans;
}
void change(int x){
	while(x)change(dfn[top[x]],dfn[x]),x=fa[top[x]];
}
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	cin>>n>>k;
	s=n-k-1;
	for(int i=1;i<n;i++){
		cin>>x>>y;
		add(x,y),add(y,x);
	}
	dep[n]=1;dfs1(n);dfs2(n,n);
	build(1,n,1);
	for(int i=n-1;i;i--){
		int u=dep[i]-ask(i);
		if(u>s)continue;
		s-=u;
		change(i);
	}
	for(int i=1;i<=n;i++)
	if(ask(dfn[i],dfn[i])==0)cout<<i<<' ';
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
```


---

## 作者：t162 (赞：2)

这题总的来说还是比较套路的。

# 题意理解

给定一颗 $n$ 个结点的无根树，$i$ 号结点权值是 $2^i$ ，求在保证联通的情况下，如何删去 $k$ 个结点使得剩下结点的权值和最大。

# 题解正文

题目让我们求的是删去的结点，我们不妨先求出保留的结点。

容易想到的一个贪心策略是从 $n$ 号结点往 $1$ 号结点贪，能保留的一定保留。

容易证明这个贪心策略是正确的。因为 $2^n>\sum\limits_{i<n}2^i$。

然后我们考虑如何判断一个结点是否能保留。

显然，这个结点到当前已经加入的结点组成的联通块（以下简称`联通块`）的距离如果小于等于还能加入的结点的个数，那么这个结点就能够加入。

那么如何维护某个结点到联通块的距离呢？

树状数组可以做到。

我们要维护的是一些子树内的结点到已经加入的结点组成的联通块的距离。这个操作在基于`DFS序`和`差分`的树状数组上可以很轻松地维护。

实际上新加入的所有结点构成的是一条链。我们只需要暴力跳父亲，直到跳到联通块内的同时对每个子树（除了根在这条链上的）进行维护。

还剩下一个问题，我们贪心的时候要注意当前结点是否已经加入联通块内。

这个问题很好解决，在加入新结点暴力跳父亲时打个标记就行了。

最后输出的时候根据标记输出就好了。

容易证明，这个程序的复杂度是 $O[(n-k)\log n]$。

# 代码

```cpp
//This code was made by Bambusoideae
#include<cstdio>
#include<queue>
#include<vector>
std::vector<int> edge[1000010];
long long tree[1000010];
int begin[1000010],end[1000010],dis[1000010],fix[1000010],vis[1000010],f[1000010],cnt,n,k;
int lowbit(int x){return x&(-x);}
void add(int x,int y){
	while(x<=n)tree[x]+=y,x+=lowbit(x);
}
int query(int x){
	int ret=0;while(x)ret+=tree[x],x-=lowbit(x);return ret;
}
void dfs(int u,int fa){
	begin[u]=++cnt,fix[cnt]=u,f[u]=fa;    //算DFS序、距离
	for(int i=0;i<edge[u].size();i++){
		int v=edge[u][i];
		if(v!=fa)dis[v]=dis[u]+1,dfs(v,u);
	}
	end[u]=cnt;
}
void fil(int x,int l){
	add(begin[x],-l),add(end[x]+1,l),vis[x]=1;int last=x;l--;
	if(vis[f[x]])return;
	for(int i=f[x];!vis[i];last=i,i=f[i],l--)
	vis[i]=1,                  //打标记
	add(begin[i],-l),add(end[i]+1,l),
	add(begin[last],l),add(end[last]+1,-l);    //维护树状数组
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v),edge[u].push_back(v),edge[v].push_back(u);
	}
	dis[n]=1,dfs(n,0),cnt=0;
	k=n-k;add(1,1),vis[0]=1;
	for(int i=2;i<=n;i++)add(i,dis[fix[i]]-dis[fix[i-1]]);  //建树状数组
	for(int i=n;i>0;i--){
		if(vis[i])continue;
		if(query(begin[i])>k)continue;int l=query(begin[i]);
		k-=l,fil(i,l);
	}
	for(int i=1;i<=n;i++)if(!vis[i])printf("%d ",i);
}
```

---

## 作者：Inker (赞：2)

2^i说明点号越大点就一定要留，小的点全加起来也不如大的点。

以n节点为根，构造树T，

显然i在T内时，i的父亲一定在T内（否则不连通），

所以，从大到小贪心，模拟向上跳，把经过的点加入T。

优化：

树状数组维护i有多少个父亲在T内，

每次i入T时将in[u]到out[u]的加1。

代码：
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1000003;
struct bian{
    int to,nxt;
}e[2000003];
int hea[N],en=1;
void add(int u,int v)
{
    e[++en].to=v;
    e[en].nxt=hea[u];
    hea[u]=en;
}
int idc=0,in[N],out[N],fa[N],dep[N];
void dfs(int u,int f)
{
    in[u]=++idc;fa[u]=f;
    for(int i=hea[u];i;i=e[i].nxt)
    {
        int v=e[i].to;
        if(v==f)continue;
        dep[v]=dep[u]+1;
        dfs(v,u);
    }
    out[u]=idc;
}
int c[N*3];
void modify(int l,int r)
{
    int x=l;
    while(x<=idc){
        c[x]++;
        x+=(x&-x);
    }
    x=r+1;
    while(x<=idc){
        c[x]--;
        x+=(x&-x);
    }
}
int query(int pos)
{
    int ans=0;
    while(pos){
        ans+=c[pos];
        pos-=(pos&-pos);
    }
    return ans;
}
int n,kik,vis[N],now,pre;
int main()
{
    scanf("%d%d",&n,&kik);
    kik=n-kik;
    int xx,yy;
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&xx,&yy);
        add(xx,yy);add(yy,xx);
    }
    dep[n]=1;
    dfs(n,n);
    modify(in[n],out[n]);
    vis[n]=1;
    now=n-1;
    while(now>=1)
    {
        if(vis[now]){
            now--;continue;
        }
        int diss=dep[now]-query(in[now])+1;
        if(diss>kik){
            now--;continue;
        }
        pre=now;
        while(!vis[pre]){
            modify(in[pre],out[pre]);
            vis[pre]=1;
            kik--;
            pre=fa[pre];
        }
        now--;
    }
    for(int i=1;i<n;i++)
    {
        if(!vis[i]){
            printf("%d ",i);
        }
    }
    return 0;
}
```

---

## 作者：HasNoName (赞：1)

### 思路
其实这道题非常简单。

考虑贪心。

先得到删掉最大为 $2^p$ 时一定可以得到合法答案的 $p$ 的最小值。

可以用类似于拓扑排序的方法用 $O(N)$ 的时间求出。

然后设根节点为 $r$，显然，$r$ 可以等于 $n$，因为 $n$ 如果取得到，则答案一定比 $2^n$ 小。又因为 $k<n$，所以一定至少有一个可以选，所以把其中任意一个替换成 $2^n$ 权值的点一定更优。

再对每一个点倍增，得到至少要删几个点，从大到小统计答案即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000005,L=20;
struct T
{
	int ne,to;
}e[2*N];
int he[N],idx,d[N],vis[N],top,fa[N][L+5];
void add(int x,int y)
{
	e[++idx].ne=he[x];
	e[idx].to=y;
	he[x]=idx;
	d[y]++;
}
int dfs(int x,int fat,int u)
{
	if(vis[x])u++;
	fa[x][0]=fat;
	d[x]=d[fat]+1;
	for(int i=he[x];i;i=e[i].ne)
	{
		int y=e[i].to;
		if(y==fat)continue;
		dfs(y,x,u);
	}
}
int main()
{
//	freopen("shop.in","r",stdin);
//	freopen("shop.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,k,p;
	cin>>n>>k;
	for(int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		add(x,y);
		add(y,x);
	}
	for(int i=1;i<=n;i++)//用于求出p
	{
		if(d[i]>1)continue;
		vis[i]=1;
		top++;
		bool flag=0,t=1;
		int x=i;
		while(t)
		{
			t=0;
			for(int j=he[x];j;j=e[j].ne)
			{
				int y=e[j].to;
				if(vis[y])continue;
				d[y]--;
				if(d[y]<=1&&y<=i)
				{
					top++;
					x=y;
					t=1;
					vis[y]=1;
				}
			}
		}
		if(top>=k)
		{
			p=top;
			break;
		}
	}
	int s=n;
	memset(d,0,sizeof(d));
	dfs(s,0,0);
	fa[s][0]=s;
	for(int j=1;j<=L;j++)
		for(int i=1;i<=n;i++)
			fa[i][j]=fa[fa[i][j-1]][j-1];
	for(int i=n;i>=1;i--)
	{
		if(!vis[i])continue;
		int l,x=i;
		for(int j=L;j>=0;j--)
			if(vis[fa[x][j]])
				x=fa[x][j];
	//	cout<<i<<' '<<l<<'\n';
		l=d[i]-d[x]+1;
		if(p-l>=k)
		{
			p-=l;
			x=i;
			while(vis[x])
			{
				vis[x]=0;
				x=fa[x][0];
			}
		}
	}
	for(int i=1;i<=n;i++)
		if(vis[i])cout<<i<<' ';
	cout<<'\n';
	return 0;
}
```

---

## 作者：TH911 (赞：1)

> [题目传送门](https://www.luogu.com.cn/problem/CF980E)

# 题意分析

给定一棵 $n$ 个节点的树，第 $i$ 个节点的权值为 $2^i$。从中删除 $k$ 个节点，使得剩下 $n-k$ 个节点联通且权值和最大。

求删除哪 $k$ 个节点。

## 贪心性质

权值为 $2^i$ 毫无疑问是极其特殊的，因此我们可以考虑有没有一些性质。

显然，$2^x>2^{x-1}+2^{x-2}+2^{x-3}+\cdots+2^{0}$，因此我们可以考虑贪心。

即：因为需要使权值和最大，因此让删除的 $k$ 个点的权值和尽可能小，所以让这 $k$ 个点的编号尽可能小。

## 增加点

删除点不好做。

因此我们可以尝试转换为增加点——若确定了剩下 $n-k$ 个点，也即确定了删除的 $k$ 个点。

那么我们就需要贪心地使增加的点的编号尽可能大，则 $n$ 号点肯定是需要保留的。

以 $n$ 为根节点建立一棵有根树，加入节点 $i$ 即将 $i$ 至 $n$ 的路径上所有的点加入。

贪心从大致小加入节点即可。

## 维护路径上尚未加入的点的数量

这样，我们才能判断当前节点 $i$ 能否加入（如果加入后有根树内的节点数大于 $n-k$ 则不符合条件）。

考虑暴力的思路，一个一个节点向上跳，跳到已经加入有根树的节点时停止，跳的过程中计数即可。

那么我们优化这样的思路，使用倍增 $\mathcal O(\log n)$ 向上跳，跳的同时计数即可。

# AC 代码

时间复杂度：$\mathcal O(n\log n)$。

```cpp
//#include<bits/stdc++.h>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<string>
#include<vector>
#include<cmath>
#include<ctime>
#include<deque>
#include<queue>
#include<stack>
#include<list>
using namespace std;
constexpr const int N=1e6;
struct graph{
	struct edge{
		int v,r;
	}a[N-1<<1|1];
	int size,h[N+1];
	void create(int u,int v){
		a[++size]={v,h[u]};
		h[u]=size;
	}
}g;
int n,k,f[N+1][__lg(N+1)+1];
bool flag[N+1];
void dfs(int x,int fx){
	f[x][0]=fx;
	for(int i=g.h[x];i;i=g.a[i].r){
		int &v=g.a[i].v;
		if(v==fx){
			continue;
		}
		dfs(v,x);
	}
}
void pre(){
	dfs(n,0);
	k--;
	flag[n]=true;
	for(int i=1;(1<<i)<=n;i++){
		for(int x=1;x<=n;x++){
			f[x][i]=f[f[x][i-1]][i-1];
		}
	}
}
int query(int x){
	int ans=1;
	for(int i=__lg(n);i>=0;i--){
		if(!f[x][i]){
			continue;
		}
		if(flag[f[x][i]]){
			continue;
		}
		ans+=(1<<i);
		x=f[x][i];
	}
	return ans;
}
int main(){
	/*freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);*/
	
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	cin>>n>>k;
	k=n-k;//注意k此时表示有根树能加入的节点数
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		g.create(u,v);g.create(v,u);
	}
	pre();
	vector<int>ans;
	for(int i=n-1;i>=1;i--){
		if(flag[i]){
			continue;
		}
		int pl=query(i);
		if(pl<=k){
			k-=pl;
			int x=i;
			while(!flag[x]){
				flag[x]=true;
				x=f[x][0];
			}
		}else{
			ans.push_back(i);
		}
	}
	for(int i=ans.size()-1;i>=0;i--){
		cout<<ans[i]<<' ';
	}
	cout.flush();
	
	/*fclose(stdin);
	fclose(stdout);*/
	return 0;
}
```

---

## 作者：wangzikang (赞：1)

这题怎么还能评上紫了，个人感觉比今年联合省选的签到简单。

----

显然，取最后一个点一定是最优的，那我们先选上点 $n$， 然后我们又可以发现，要是你已经决策好了后 $m$ 个点，你准备选前一个点，那么能选上一定选。

证明： $2^k>\sum\limits_{i=0}^{k-1} 2^{i}$

然后我们把 $n$ 设成根，每次做的就是当前最小没选的点祖先中深度最小的没被选上的点，要是这个点和当前点的距离足够小使得我们能够选上它而不违反限制条件，我们就直接把路径上所有点选上。

那我们把找点用倍增做，求距离随便做，选点是 $O(n)$ 的，然后就做完了？？？？？？？？？

没想到这么水。

code:

```cpp
#include<bits/stdc++.h>
#define spc() ALL_OUT[++ALL_LEN]=' '
#define nxtl() ALL_OUT[++ALL_LEN]='\n'
#define clrout() ALL_OUT[ALL_LEN+1]=0,fputs(ALL_OUT,stdout),ALL_LEN=-1
#define rt() return clrout(),0;
using namespace std;
char OUT_LIST[41],ALL_OUT[100100];
int ALL_LEN=-1;
void write(int x,short l=40){
    const int k=x/10;
	OUT_LIST[l]=(x-(k<<1)-(k<<3))|'0';
    if(x>9)write(k,l-1);
    else{
    	if(ALL_LEN>100000)clrout();
    	for(;l<33;l+=8){
    		ALL_OUT[1+ALL_LEN]=OUT_LIST[l];
    		ALL_OUT[2+ALL_LEN]=OUT_LIST[l+1];
    		ALL_OUT[3+ALL_LEN]=OUT_LIST[l+2];
    		ALL_OUT[4+ALL_LEN]=OUT_LIST[l+3];
    		ALL_OUT[5+ALL_LEN]=OUT_LIST[l+4];
    		ALL_OUT[6+ALL_LEN]=OUT_LIST[l+5];
    		ALL_OUT[7+ALL_LEN]=OUT_LIST[l+6];
    		ALL_OUT[ALL_LEN=(8+ALL_LEN)]=OUT_LIST[l+7];
		}
		switch(40-l){
			case 7:ALL_OUT[++ALL_LEN]=OUT_LIST[l++];
			case 6:ALL_OUT[++ALL_LEN]=OUT_LIST[l++];
			case 5:ALL_OUT[++ALL_LEN]=OUT_LIST[l++];
			case 4:ALL_OUT[++ALL_LEN]=OUT_LIST[l++];
			case 3:ALL_OUT[++ALL_LEN]=OUT_LIST[l++];
			case 2:ALL_OUT[++ALL_LEN]=OUT_LIST[l++];
			case 1:ALL_OUT[++ALL_LEN]=OUT_LIST[l++];
			case 0:ALL_OUT[++ALL_LEN]=OUT_LIST[l++];
		}
	}
}
int read(){
   char ch=getchar();
   int s=0;
   while(ch<'0'||ch>'9')ch=getchar();
   while(ch>='0'&&ch<='9') s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
   return s;
}
struct node{
	int to,nxt;
}g[3000010];
int n,q,cnt,dep[1000010],c[1000010],fa[1000010][21];
void add(int u,int v){
	g[++cnt].nxt=h[u],g[cnt].to=v,h[u]=cnt;
}
void dfs(int u){
	dep[u]=dep[fa[u][0]]+1;
	for(int i=1;i<=20;++i){
		fa[u][i]=fa[fa[u][i-1]][i-1];
	} 
	for(int i=h[u];i;i=g[i].nxt){
		const int v=g[i].to;
		if(v!=fa[u][0])fa[v][0]=u,dfs(v);
	}
}
void solve(){
	int n=read(),k=n-read()-1;
	for(int i=1;i<n;++i){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(n);
	c[n]=1;
	for(int u=n-1;u!=0&&k;--u){
		if(c[u])continue;
		int v=u;
		for(int level=20;level>=0;--level){
			if(fa[v][level]&&!c[fa[v][level]]){
				v=fa[v][level];
			}
		}
		int d=dep[u]-dep[v]+1;
		if(d<=k){
			int w=u;
			while(!c[w])c[w]=1,w=fa[w][0];
			k-=max(d,0);
		}
	}
	for(int i=1;i<=n;++i){
		if(!c[i])cout<<i<<' ';
	}
}
signed main(){
//	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int t=1;
	while(t--)solve();
	rt();
}

```
---
信息课写题解同学老看我怎么办/qd

---

## 作者：Milthm (赞：1)

这个删节点很难选，所以我们转化成选节点。

你发现 $n$ 是必须选的，因为 $2^n>2^{n-1}+2^{n-2}+\dots+1=2^n-1$。所以我们可以重新以 $n$ 为根建一下树。

然后我们肯定从 $n-1$ 往 $1$ 贪心。因为如果这个点要选，它到根路径之间所有的点都要选（要保证联通），所以如果这个点到根节点（新的根节点 $n$）上没有被选过的数是小于等于当前最多能选的节点数量，那么就可以选。

然后这个过程可以用树状数组优化，树状数组存 $x$ 节点到根节点有多少数被选了，每次选择节点把它的整个子树都加 $1$，用差分就可以实现。

### AC code

```cpp
#include<iostream>
#define int long long
#define N 1000005
using namespace std;
int n,k,h[N*2],num,f[N],c[N],dep[N],dfn[N],siz[N],cnt,vis[N],now;
int read(){
	char c=getchar();int ans=0;
	while(!isdigit(c))c=getchar();
	while(isdigit(c))ans=ans*10+c-'0',c=getchar();
	return ans;
}
struct edge{
	int u,v,nxt;
}e[N*2];
void add(int u,int v){
	e[++num]={u,v,h[u]};h[u]=num;
}
void dfs(int u,int fa){
	f[u]=fa;dep[u]=dep[fa]+1;dfn[u]=++cnt;siz[u]=1;
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v!=fa)dfs(v,u),siz[u]+=siz[v];
	}
}
void upd(int x,int k){
	while(x<=n){
		c[x]+=k;x+=x&-x;
	}
}
int ask(int x){
	int ans=0;
	while(x){
		ans+=c[x];x-=x&-x;
	}
	return ans;
}
void solve(int x){
	if(dep[x]-ask(dfn[x])+now>k)return;
	while(x!=n){
		if(vis[x])break;
		vis[x]=1;upd(dfn[x],1);upd(dfn[x]+siz[x],-1);++now;
		x=f[x];
	}
}
signed main(){
	n=read();k=read();k=n-k;
	for(int i=1;i<n;++i){
		int u,v;u=read();v=read();
		add(u,v);add(v,u);
	}
	dfs(n,0);vis[n]=1;
	for(int i=n-1;i>=1;--i)solve(i);
	for(int i=1;i<=n;++i)if(!vis[i])printf("%lld ",i);
	return 0;
} 
```


---

## 作者：Crazyouth (赞：0)

## 分析

考虑主席会选择哪 $n-k$ 位选手留下。

注意到 $\displaystyle\sum_{i=1}^x 2^i=2^{x+1}-1<2^{x+1}$，所以即使需要放弃 $1\sim x$，也要选择 $x+1$。因此 $n$ 一定会被选择，所以我们以 $n$ 为根，并从大到小枚举剩余的点，若该点未被选择且选择该点到根的所有节点（因为我们需要保证选出的图连通）之后仍然不超过 $n-k$ 个，我们就选上该点，并暴力将路径上所有未选择的点选上，由于每个点至多被选择一次，所以该操作复杂度为 $O(n)$。

至于如何寻找一个点到根的路径上最后一个未被选择的节点，可以通过倍增解决。因此总复杂度 $O(n\log n)$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,k,vis[N],f[N][21],dep[N];
vector<int> G[N];
void dfs(int u,int fa)
{
	dep[u]=dep[fa]+1;
	f[u][0]=fa;
	for(int i=1;i<=20;i++) f[u][i]=f[f[u][i-1]][i-1];
	for(auto v:G[u])
	{
		if(v==fa) continue;
		dfs(v,u);
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>k;
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(n,n);
	int now=1;
	vis[n]=1;
	for(int i=n-1;i;i--)
	{
		if(vis[i]) continue;
		int u=i;
		for(int j=20;~j;j--) if(!vis[f[u][j]]) u=f[u][j];
		if(dep[i]-dep[u]+1+now>n-k) continue;
		now+=dep[i]-dep[u]+1;
		vis[u]=1;
		for(int j=i;!vis[j];j=f[j][0]) vis[j]=1;
	}
	for(int i=1;i<=n;i++) if(!vis[i]) cout<<i<<' ';
}

---

## 作者：Purslane (赞：0)

# Solution

我摊牌了，我是偷看 Reunite 的 CF 提交记录找到这道题的。

贪心选择编号最大的点。 最后我们只能保留 $n-k$ 个点。

显然，$n$ 号点肯定能选，作为树根。

维护我们选择的点构成的虚树。加入一个点，如果新的虚树的大小还是小于等于 $n-k$ 就贪心的加入。

使用倍增维护这一过程。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10;
int n,k,dep[MAXN],fa[MAXN][21],vis[MAXN],cnt;
vector<int> G[MAXN];
void dfs(int u,int f) {
	fa[u][0]=f,dep[u]=dep[f]+1; ffor(i,1,20) fa[u][i]=fa[fa[u][i-1]][i-1];
	for(auto v:G[u]) if(v!=f) dfs(v,u);
	return ;
}
int dis(int u) {
	int ori=u; if(vis[u]) return 0;
	roff(i,20,0) if(fa[u][i]&&!vis[fa[u][i]]) u=fa[u][i];
	return u=fa[u][0],dep[ori]-dep[u];
}
void update(int u) {
	while(vis[u]==0) vis[u]=1,u=fa[u][0];
	return ;	
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k; ffor(i,1,n-1) {int u,v;cin>>u>>v,G[u].push_back(v),G[v].push_back(u);}
	dfs(n,0),vis[n]=1,cnt=1;
	vector<int> ans;
	roff(i,n-1,1) {
		if(cnt+dis(i)<=n-k) cnt+=dis(i),update(i);
		else ans.push_back(i);	
	}
	sort(ans.begin(),ans.end());
	for(auto v:ans) cout<<v<<' ';
	return 0;
}
```

代码好短。

---

## 作者：Hoks (赞：0)

## 前言
比较简单的树剖题？好像也不能算树剖了，根本没必要树剖。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842#information)。

广告：[『从入门到入土』树链剖分学习笔记](https://www.luogu.com.cn/article/56o68hfu)。
## 思路分析
首先扫一眼题面顺便看下数据范围 $10^6$，结合上 $3$ 秒时限，应该是 $O(n\log n)$ 或小常 $O(n\log^2n)$ 了。

感觉这种题意很不好做，寻找突破口。

因为让我们求的是最大权值，所以重点关注权值。

发现题目中给的权值全是 $2^i$，而且 $i$ 各不相同。

那这有什么性质呢？

根据最大和 $2^i$，很自然的会想到一个性质：
$$2^x>\sum\limits_{i=1}^{x-1}$$
这说明什么？

如果我能选择点 $x$，那么肯定优于不选择点 $x$ 而选择点 $y(y<x)$。

用人话说就是**无后效性**，可以**贪心**的**从大到小**的选取点。

接着就是判断一个点是否可以被选择了。

也就是对于点 $x$，查询其到根路径上**还没被选择**的点数是否比**还能选择**的点数小。

考虑大力点，直接树剖线段树维护即可。

选择了这个点后，给路径整个赋 $0$ 即可。

记得下传懒标记。
## 代码
```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
using namespace std;
const int N=1e6+10,INF=0x3f3f3f3f;
int n,k,t[N<<2];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
namespace tree_decomposition
{
    int cnt;vector<pair<int,int>>e[N];
    int fa[N],son[N],si[N],dep[N];
    int top[N],dfn[N];
    inline void add(int u,int v,int w){e[u].emplace_back(make_pair(v,w)),e[v].emplace_back(make_pair(u,w));}
    inline void dfs1(int u,int ff)
    {
        fa[u]=ff,si[u]=1,dep[u]=dep[ff]+1;
        for(auto [v,w]:e[u])
        {
            if(v==ff) continue;
            dfs1(v,u);si[u]+=si[v];
            if(si[son[u]]<si[v]) son[u]=v;
        }
    }
    inline void dfs2(int u,int topf)
    {
        top[u]=topf,dfn[u]=++cnt;
        if(son[u]) dfs2(son[u],topf);
        for(auto [v,w]:e[u])
        {
            if(v==fa[u]||v==son[u]) continue;
            dfs2(v,v);
        }
    }
    inline int LCA(int x,int y)
    {
        while(top[x]!=top[y])
        {
            if(dep[top[x]]<dep[top[y]]) swap(x,y);
            x=fa[top[x]];
        }
        return dep[x]<dep[y]?x:y;
    }
}
using namespace tree_decomposition;
inline void build(int p,int l,int r)
{
    t[p]=r-l+1;if(l==r) return ;
    build(ls,l,mid);build(rs,mid+1,r);
}
inline void modify(int p,int l,int r,int s,int e)
{
    if(l>=s&&r<=e) return t[p]=0,void();
    if(!t[p]) return t[ls]=t[rs]=0,void();
    if(mid>=s) modify(ls,l,mid,s,e);
    if(mid<e) modify(rs,mid+1,r,s,e);
    t[p]=t[ls]+t[rs];
}
inline int query(int p,int l,int r,int s,int e)
{
    if(l>=s&&r<=e) return t[p];int res=0;
    if(!t[p]) return t[ls]=t[rs]=0,0;
    if(mid>=s) res=query(ls,l,mid,s,e);
    if(mid<e) res+=query(rs,mid+1,r,s,e);
    return res;
}
inline int get(int x)
{
    int res=0;
    while(top[x]^top[n]) res+=query(1,1,n,dfn[top[x]],dfn[x]),x=fa[top[x]];
    return res+query(1,1,n,dfn[top[n]],dfn[x]);
}
inline void modify(int x)
{
    while(top[x]^top[n]) modify(1,1,n,dfn[top[x]],dfn[x]),x=fa[top[x]];
    modify(1,1,n,dfn[top[n]],dfn[x]);
}
signed main()
{
    n=read(),k=n-read();for(int i=1,u,v;i<n;i++) u=read(),v=read(),add(u,v,0);
    dfs1(n,0),dfs2(n,n);build(1,1,n);modify(1,1,n,dfn[n],dfn[n]);
    for(int i=n-1,cnt=1,x;i>=1;i--)
    {
        if(!query(1,1,n,dfn[i],dfn[i])) continue;
        x=get(i);if(x+cnt>k) continue;
        cnt+=x;modify(i);
    }k=n-k;
    for(int i=1;i<=n;i++) if(query(1,1,n,dfn[i],dfn[i])&&k) k--,print(i),put(' ');
    genshin:;flush();return 0;
}
```

---

