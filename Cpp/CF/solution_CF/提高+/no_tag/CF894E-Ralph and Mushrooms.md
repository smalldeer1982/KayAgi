# Ralph and Mushrooms

## 题目描述

Ralph is going to collect mushrooms in the Mushroom Forest.

There are $ m $ directed paths connecting $ n $ trees in the Mushroom Forest. On each path grow some mushrooms. When Ralph passes a path, he collects all the mushrooms on the path. The Mushroom Forest has a magical fertile ground where mushrooms grow at a fantastic speed. New mushrooms regrow as soon as Ralph finishes mushroom collection on a path. More specifically, after Ralph passes a path the $ i $ -th time, there regrow $ i $ mushrooms less than there was before this pass. That is, if there is initially $ x $ mushrooms on a path, then Ralph will collect $ x $ mushrooms for the first time, $ x-1 $ mushrooms the second time, $ x-1-2 $ mushrooms the third time, and so on. However, the number of mushrooms can never be less than $ 0 $ .

For example, let there be $ 9 $ mushrooms on a path initially. The number of mushrooms that can be collected from the path is $ 9 $ , $ 8 $ , $ 6 $ and $ 3 $ when Ralph passes by from first to fourth time. From the fifth time and later Ralph can't collect any mushrooms from the path (but still can pass it).

Ralph decided to start from the tree $ s $ . How many mushrooms can he collect using only described paths?

## 说明/提示

In the first sample Ralph can pass three times on the circle and collect $ 4+4+3+3+1+1=16 $ mushrooms. After that there will be no mushrooms for Ralph to collect.

In the second sample, Ralph can go to tree $ 3 $ and collect $ 8 $ mushrooms on the path from tree $ 1 $ to tree $ 3 $ .

## 样例 #1

### 输入

```
2 2
1 2 4
2 1 4
1
```

### 输出

```
16```

## 样例 #2

### 输入

```
3 3
1 2 4
2 3 3
1 3 8
1
```

### 输出

```
8```

# 题解

## 作者：Maktub (赞：5)

这个题思路不难想，但代码实现不是很容易。我的代码实现完全取自[elijahqi](https://www.luogu.org/space/show?uid=5037)大佬。我只是想将大佬的思路和代码理的更清楚一些。

思路很容易想清晰的。缩点，一个强联通分量里所有边的蘑菇都能取干净，所以将这些蘑菇作为新点的点权，在兼顾点权和边权的同时获得最大值。

代码实现分为以下几个部分：

1.缩点，这里先不要进行任何处理，单纯的tarjan缩点，因为tarjan缩点不容易处理边权。

2.处理条边的边权，方法是枚举每条边，如果边的两端点在一个强联通分量中，该强联通分量加上这条边所能产生的全部蘑菇。这需要推一下，也不难。

3.建新图。

4.在新图上进行拓扑排序+DP。用f[u]记录以u为起点所能获得的最大权值。先把所有新点f[i]更新为-inf，并统计入度为0的点。然后将源点所在的新点f[s]更新为新点的权值。然后在拓扑排序的过程中DP就行了。在DP过程中，f[v]为最大的f[u]+w(u,v)。（u连向v）

5.找最优解，在所有新点中找最大的f[i]就可以了。

~~抄来的~~代码：

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
#define ll long long
#define inf 1LL<<60
inline ll read(){
    ll x=0,f=1;char c=getchar();
    while(c>'9'||c<'0'){if(c=='-')f=-f;c=getchar();
    }
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();
    }
    return x*f;
}
const int mx=1e6+1000;
int dfn[mx],h[mx],low[mx],st[mx],co[mx],de[mx];ll ww[mx],f[mx];
int p,num,top,col,n,m,s;
ll ans;
int h1[mx],p1;
struct edge{
    int next,v,x;ll w;
}e[mx],e1[mx];
inline void add(int a,int b,ll c){
    p++;e[p].next=h[a]; h[a]=p; e[p].v=b; e[p].w=c; e[p].x=a;
}
inline void add1(int a,int b, ll c){
    p1++;e1[p1].next=h1[a];h1[a]=p1;e1[p1].v=b;e1[p1].w=c;e1[p1].x=a;
}
//-------
inline void tarjan(int u){
    dfn[u]=low[u]=++num;
    st[++top]=u;
    for(int i=h[u];i;i=e[i].next){
        int v=e[i].v;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!co[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(dfn[u]==low[u]){
        ++col;
        while(st[top+1]!=u){
            co[st[top]]=col;
            top--;
        }
    }
}
inline ll calc(ll x){//抄来的函数
    ll tt=sqrt(2*x+0.25)-0.5;
    return x+tt*x-(tt+1)*(tt+2)*tt/6;
}
int main(){
    n=read();m=read();
    for(int i=1,u,v,w;i<=m;i++){
        u=read();v=read();w=read();
        add(u,v,w);
        
    }//duru
    s=read();
    for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);//suodian
    
    for(int i=1;i<=m;i++){
        int u=e[i].x,v=e[i].v;
        if(co[u]==co[v]){
            ww[co[u]]+=calc(e[i].w);
        }
    }//quanzhi
    
    for(int i=1;i<=n;i++){
        for(int j=h[i];j;j=e[j].next){
            int v=e[j].v;
            if(co[i]!=co[v]){
                add1(co[i],co[v],e[j].w+ww[co[v]]);de[co[v]]++;
            }
        }
    }//rebuild
    top=0;num=0;
    for(int i=1;i<=col;i++){
        if(!de[i])st[++top]=i;
        f[i]=-inf;
    }
    f[co[s]]=ww[co[s]];
    
    while(top){
        int u=st[top--];
        for(int i=h1[u];i;i=e1[i].next){
            int v=e1[i].v;ll w=e1[i].w;
            de[v]--;
            if(!de[v]){
                st[++top]=v;
            }
            f[v]=max(f[v],f[u]+w);
        }
    }//topo order
    for(int i=1;i<=col;i++)ans=max(ans,f[i]);
    printf("%lld",ans);return 0;

    
}
```
感谢 elijahqi 大佬让我学到很多。

---

## 作者：dz_ice (赞：2)

这道题看了不久就想到了思路，但是代码却调了一个上午。。。~~（太毒瘤了）~~

如果某一条道路会走不止一次，那么显然这条路是位于一个环中，同时，我们也可以将这个环走很多次只到能采的蘑菇数量等于０，强连通分量缩点＋重新建图即可

那么怎么算取完蘑菇的数量呢？题解里都推出了式子，~~那么我就来个暴力一点的~~，先预处理出蘑菇数量为１，３，６，１０.....取完蘑菇的数量，然后每次二分查找一下即可

这是预处理

$w$数组是$\displaystyle \sum^{i}_{1}{i}$，$sum$数组是$\displaystyle \sum^{i}_{1}{w[i]}$

```
    for(long long i=1;i<=100000;i++)
   	{
		if(w[i-1]+i>100000000)
		{
	    		wsum=i-1;
	    		break;
		}
		w[i]=w[i-1]+i,sum[i]=sum[i-1]+w[i];
   	}
```

二分查找
```
long long check(long long x)
{
    long long le=1,ri=wsum,mid;
    while(le<=ri)
    {
	mid=(le+ri)/2;
	if(x>w[mid])
	    le=mid+1;
	else
	    ri=mid-1;
    }
    return (ri+1)*x-sum[ri];
}
```

做完这些再来一个拓扑＋DP即可

完整代码
```
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,v,df[1000003],low[1000003],dfn,col,co[1000003],ru[1000003],zhan[1000003],hd,p,s;
vector<int>l[1000003],l1[1000003],g[1000003],g1[1000003];
long long w[1000003],sum[1000003],dis[1000003],quan[1000003],ans,wsum;
queue<int>q;
long long check(long long x)
{
    long long le=1,ri=wsum,mid;
    while(le<=ri)
    {
	mid=(le+ri)/2;
	if(x>w[mid])
	    le=mid+1;
	else
	    ri=mid-1;
    }
    return (ri+1)*x-sum[ri];
}
void dfs(int x)
{
    dfn++,df[x]=low[x]=dfn,hd++,zhan[hd]=x;
    for(int j=0;j<l[x].size();j++)
    {
	if(df[l[x][j]]==0)
	{
	    dfs(l[x][j]);
	    low[x]=min(low[x],low[l[x][j]]);
	}
	else
	    if(co[l[x][j]]==0)		
		low[x]=min(low[x],df[l[x][j]]);
    }
    if(df[x]==low[x])
    {
	col++,co[x]=col;
	while(zhan[hd]!=x)
	    co[zhan[hd]]=col,hd--;
	hd--;	     
    }
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
	scanf("%d%d%d",&x,&y,&v);
	l[x].push_back(y),l1[x].push_back(v);
    }
    cin>>s;
    for(long long i=1;i<=100000;i++)
    {
	if(w[i-1]+i>100000000)
	{
	    wsum=i-1;
	    break;
	}
	w[i]=w[i-1]+i,sum[i]=sum[i-1]+w[i];
    }
    dfs(s);
    for(int i=1;i<=n;i++)
	for(int j=0;j<l[i].size();j++)
	    if(co[i]==co[l[i][j]]&&co[i]!=0)
		quan[co[i]]+=check((long long)l1[i][j]);
	    else
		if(co[i]!=0&&co[l[i][j]]!=0)
		    g[co[i]].push_back(co[l[i][j]]),g1[co[i]].push_back(l1[i][j]),ru[co[l[i][j]]]++;
    q.push(co[s]);
    dis[co[s]]=quan[co[s]],ans=dis[co[s]];
    while(!q.empty())
    {
	p=q.front();q.pop();
	for(int j=0;j<g[p].size();j++)
	{
	    dis[g[p][j]]=max(dis[g[p][j]],dis[p]+(long long)g1[p][j]+quan[g[p][j]]),ans=max(ans,dis[g[p][j]]),ru[g[p][j]]--;
	    if(ru[g[p][j]]==0)
		q.push(g[p][j]);
	}
    }
    cout<<ans;
    return 0;
}

```

[福利（双倍经验）](https://www.luogu.org/problem/P2656)稍微修改一点即可

---

## 作者：elijahqi (赞：2)

 http://www.elijahqi.win/archives/1627
 https://blog.csdn.net/elijahqi/article/details/80686912
 
题目题意 给定边权 每次可以取边上x x-1 x-1-2 x-1-2-3 直到减到0为止

那么首先可以tarjan缩点 就是所有强连通的点上可以都取到  那么 我们可以采用数学方法计算强连通

点的权值 这个假设我们 最大值是x  然后 求出1+2+3+..x<=n 这个最大的x的整数解出现在哪里

那么整个环的答案就是：首先求出n∗(n+1)<=w的最大的n，然后价值就是n∗w−∑i∗(i+1)/2+w(1<=i&i<=n)，也就是n∗w−n∗(n+1)∗(n+2)/6+w

然后根据拓扑序求出我的最长路即可 然后我就把点权直接记在边上 跑拓扑序dp

最后输出答案即可 注意有些地方需要使用Long long
```
#include<cstdio>
#include<stack>
#include<cmath>
#include<queue>
#include<algorithm>
#define ll long long
#define inf 1LL<<60
#define N 1100000
using namespace std;
inline char gc(){
	static char now[1<<16],*S,*T;
	if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
	return *S++;
}
inline int read(){
	int x=0;char ch=gc();
	while (ch<'0'||ch>'9') ch=gc();
	while (ch<='9'&&ch>='0'){x=x*10+ch-'0';ch=gc();}
	return x;
}
stack<int>q;
struct node{
	int x,y,next;ll z;
}data[N<<1],data1[N<<1];
ll ans=-1,f[N],w[N];
int b[N],stackf[N],dfn[N],low[N],h1[N],h[N],num,s,n,m,in[N];
void tarjan(int x){
	dfn[x]=low[x]=++num;stackf[x]=1;q.push(x);
	for (int i=h[x];i;i=data[i].next){
		int y=data[i].y;
		if (!dfn[y]) tarjan(y),low[x]=min(low[x],low[y]);else if (stackf[y]) low[x]=min(low[x],dfn[y]);
	}
	if (dfn[x]==low[x]){
		int y;++s;
		do{
			y=q.top();q.pop();
			b[y]=s;stackf[y]=0;
		}while (y!=x);
	}
}
inline ll calc(ll x){
	ll tt=sqrt(2*x+0.25)-0.5;
	return x+tt*x-(tt+1)*(tt+2)*tt/6;
}
inline void insert1(int x,int y,ll z){
	data1[++num].y=y;data1[num].z=z;data1[num].next=h1[x];h1[x]=num;data1[num].x=x;
}
int main(){
	freopen("cf.in","r",stdin);
	n=read();m=read();
	for (int i=1;i<=m;++i){
		int x=read(),y=read(),z=read();
		data[++num].y=y;data[num].z=z;data[num].next=h[x];h[x]=num;data[num].x=x;
	}
	int st=read();num=0;
	for (int i=1;i<=n;++i) if (!dfn[i]) tarjan(i);
	for (int i=1;i<=m;++i){
		int x=data[i].x,y=data[i].y;
		if (b[x]==b[y]) w[b[x]]+=calc(data[i].z);
	}num=0;
	for (int i=1;i<=n;++i){
		for (int j=h[i];j;j=data[j].next){
			int y=data[j].y;if (b[y]==b[i]) continue;
			insert1(b[i],b[y],data[j].z+w[b[y]]);
		}
	}queue<int>q;
	for (int i=1;i<=s;++i) f[i]=-inf;f[b[st]]=w[b[st]];
	for (int i=1;i<=num;++i) in[data1[i].y]++;
	for (int i=1;i<=s;++i)  if (!in[i]) q.push(i);
	while(!q.empty()){
		int x=q.front();q.pop();
		for (int i=h1[x];i;i=data1[i].next){
			int y=data1[i].y;ll z=data1[i].z;if (--in[y]==0) q.push(y);f[y]=max(f[y],f[x]+z);
		}
	}
	for (int i=1;i<=s;++i) ans=max(ans,f[i]);
	printf("%I64d",ans);
	return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

# 前言
我是通过[ P2656 采蘑菇 ](https://www.luogu.com.cn/problem/P2656)来的，所以说这也是一道双倍经验题了。
# 思路
我们可以发现如果存在一个环，那么我们一定可以把这个环中的所有边的边权的所有值都取到（就是相当于可以将每一条边上的值都取到 $0$），然后我们就很容易地想到 Tarjan 缩点了，因为这样我们就可以算出每一个环中的总和，然后就是一个图了，这里我们可以用拓扑来跑一个最长路即可，但是这里有一个问题就是如何处理和，其实也很好解决，因为如果我们的 $\sum_{i=1}^{j} i$ 是最后一个小于等于边权的，那么我们的和就是 $val\times (i+1)-\sum_{now=1}^{i}\sum_{y=1}^{now} y$ 这个公式既然出来了，那么我们就可以通过二分来求出最大的 $i$ 然后再通过预处理来算出要减去的值，最后直接套公式即可。

细节见代码。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define il inline
#define pb push_back
#define w(x) while(x--)
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int n,m;
const int N=1e6+10;
struct node{
	int x,y,z,yuan,io;
}edg[N];
int head[N],tot,cnt,sum[N]; 
void add(int x,int y,int z) {
	edg[++tot]={y,head[x],z,x};
	head[x]=tot;
}
int low[N],dfn[N],idx;
stack<int>s;
vector<pair<int,int>>v[N];
int is[N],zai[N];
void tarjan(int x) { //模板Tarjan缩点 
	dfn[x]=low[x]=++idx;
	s.push(x);
	is[x]=1;
	for(int i=head[x];i;i=edg[i].y) {
		int to=edg[i].x;
		if(!dfn[to]) {
			tarjan(to);
			low[x]=min(low[x],low[to]);
		}else if(is[to]) low[x]=min(low[x],dfn[to]);
	}
	if(low[x]==dfn[x]) {
		int p;
		cnt++;
		do{
			p=s.top();
			s.pop();
			zai[p]=cnt;//将每一个点所在的环记录下来 
			is[p]=false;
		}while(p!=x);
	}
}
int dis[N],vis[N];
int mp[100010],c[100100];
int in[N];
void dfs(int s) { //拓扑 
	dis[s]=sum[s];
	queue<int>q;
	rep(i,1,cnt) if(!in[i]) q.push(i);
	while(q.size()) {
		int x=q.front();
		q.pop();
		for(auto io:v[x]) {
			int to=io.first,z=io.second;
			if(dis[x]>=0) dis[to]=max(dis[to],dis[x]+z+sum[to]);//如果更新过 
			in[to]--;
			if(!in[to]) q.push(to);
		}
	}
}
fire main() {
	in(n),in(m);
	rep(i,1,m) {
		int x,y;
		int z;
		in(x),in(y),in(z);
		add(x,y,z);
	}
	rep(i,1,50000) mp[i]=mp[i-1]+(i*(i+1)/2),c[i]=c[i-1]+i;//预处理，处理出要减的 
	rep(i,1,n) if(!dfn[i]) tarjan(i);
	rep(i,1,m) {
		int x=edg[i].yuan,y=edg[i].x;
		int ip=edg[i].z;
		if(zai[x]!=zai[y]) {//如果说一条边的两个点不在一个环中，那么就建边 
			v[zai[x]].push_back({zai[y],ip});
			in[zai[y]]++;
		}else {//否则算出贡献 
			int r=upper_bound(c+1,c+1+30000,ip)-c-1;//二分 
			int now=ip*(r+1);
			sum[zai[x]]+=now-mp[r];//套公式 
		} 
	}
	int s;
	cin>>s;
	memset(dis,-1,sizeof dis);
	dfs(zai[s]);
	int res=0;
	rep(i,1,cnt) res=max(res,dis[i]);//终点不固定所以要就最大值 
	cout<<res<<endl;
	return false;
}
```

---

## 作者：Ray662 (赞：1)

### 题目大意

一个图，$n$ 点 $m$ 边，边为有向边且有边权，一条边第 $k$ 次经过得到的获利是 $w - \frac{k(k - 1)}{2}$，出发点是 $st$，求最大获利。

### 思路

我们不难想到，在一个强连通分量（以下简称 SCC）中的任意一条边都可以无限次经过。

于是我们考虑把每一个 SCC 缩成一个点，缩点之后把每个 SCC 中的获利算出来，当做缩点后的点权。

每个 SCC 的获利就是 SCC 中每条边的获利之和，这里记每条边的边权为 $w$，获利为 $p$。

考虑如何计算 $p$：我们需要找到一个 $i$，使得 $\frac{i(i + 1)}{2} < w$ 且 $\frac{(i + 1)(i + 2)}{2} \ge w$，那么：

$$
p = w + (w - 1) + (w - 1 - 2) + \cdots + (w - 1 - 2 - \cdots - i)
$$

整理一下得到：

$$
p = w (i + 1) - \sum_{j = 1}^i \frac{j(j+1)}{2}
$$

这里 $\sum_{j = 1}^i \frac{j(j+1)}{2}$ 可以通过前缀和维护。

那么如何计算 $i$ 呢？我们可以使用二分，时间复杂度 $O(\log t)$，其中 $t = \max \{w\}$，代码如下：

```cpp
inline int solve(int x) {  // 找出最大的i使得 i*(i+1)/2 < x，并且计算 x+(x-1)+...+(x-1-2-...-i)
    int l = 1, r = M, i = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (T(mid) < x)  i = mid, l = mid + 1;
        else  r = mid - 1;
    }
    return x * (i + 1) - sum[i];
}
```

于是就好做了，我们缩点以后计算每个点的权值（就是原来 SCC 中每条边的获利之和），最后 dfs 跑一趟（拓扑排序亦可）即可。

时间复杂度：$O(m \log t)$，非常优秀。

附代码：

```cpp
#include <bits/stdc++.h>
#define F first
#define S second
#define U e[i].u
#define V e[i].v
#define W e[i].w
#define int long long
#define mp make_pair
#define pb push_back
#define PII pair<int, int>
#define _for(i, a, b)  for (int i = (int)(a); i <= (int)(b); i ++ )
#define _all(i, a, b)  for (int i = (int)(a); i >= (int)(b); i -- )
using namespace std;
const int N = 1e6 + 5, M = 15000;  // sqrt(2e8) < 15000
int n, m, start, dfn_cnt, top, scc, dfn[N], low[N], in_stack[N], st[N], bel[N];
int sum[M], w[N], dis[N];
vector<int> G[N];
vector<PII > F[N];
struct edge { int u, v, w; } e[N];
inline int T(int x) { return ((x * (x + 1)) >> 1); }
inline int solve(int x) {  // 找出最大的i使得 i*(i+1)/2 < x，并且计算 x+(x-1)+...+(x-1-2-...-i)
    int l = 1, r = M, i = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (T(mid) < x)  i = mid, l = mid + 1;
        else  r = mid - 1;
    }
    return x * (i + 1) - sum[i];
}
void tarjan(int u) {
    dfn[u] = low[u] = ++ dfn_cnt, st[ ++ top] = u, in_stack[u] = 1;
    for (int v : G[u]) {
        if (! dfn[v])  tarjan(v), low[u] = min(low[u], low[v]);
        else if (in_stack[v])  low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        scc ++ ;
        while (st[top] != u)  in_stack[st[top]] = 0, bel[st[top]] = scc, top -- ;
        in_stack[st[top]] = 0, bel[st[top]] = scc, top -- ;
    }
}
int dfs(int u) {  // 记忆化 
    if (dis[u])  return dis[u];
    for (PII v : F[u])  dis[u] = max(dis[u], v.S + dfs(v.F));
    dis[u] += w[u];
    return dis[u];
}
signed main() {
    ios :: sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    int u, v, ww;
    _for (i, 1, M - 1)  sum[i] = sum[i - 1] + T(i);  // sum[i] = 1+(1+2)+...+(1+2+...+i)
    _for (i, 1, m)  cin >> u >> v >> ww, G[u].pb(v), e[i] = (edge){u, v, ww};
    cin >> start;
    _for (i, 1, n)  if (! dfn[i])  tarjan(i);
    _for (i, 1, m) {  // 如果在同一强连通分量中，则该边可以无限次经过；否则连边 
        if (bel[U] == bel[V])  w[bel[U]] += solve(W);
        else  F[bel[U]].pb(mp(bel[V], W));  // 不同的图，不能再用 G 
    }
    cout << dfs(bel[start]) << endl;  // 从起点处开始搜索（这里的遍历，既有点权又有边权） 
    return 0;
}

```


---

## 作者：空の軌跡 (赞：1)

# 思路

这道题由于我们可以重复的走一些路径，所以说我们可以先缩点，把这个强连通分量里的边走无数次，把蘑菇~~采到不能再采~~，然后其余的边在新图上跑 拓扑排序 并计算最大值。

所以我们要处理一个边多次行走所能带来的价值。

我看到别的题解里好像有直接计算的公式，你们可以参考一下，至于我~~比较弱~~，所以我用了另一种方法。


### 这里我用 EXCEL 表示。

![](https://cdn.luogu.com.cn/upload/image_hosting/6olna4li.png)

- 左侧的图为我们要计算的图，右边的图为辅助图。

- 黑色区域为我们要计算的面积区域，也就是总共可以采到的蘑菇数量。整个图形的高度就是我们首次到达时的蘑菇数量。

- 这两幅图请分别从从右向左看。

- 中间的数字表示在各个高度下可以图形的宽度，也就是当蘑菇为 $i$ 需要采集多少次才变为 $0$。

- 每列红色区域的大小依次递加 $k$ 。

### 如何计算：

1. 首先预处理出来数组 $cou$ ，表示 当我采集 $i$ 次才采集完时，蘑菇数量最多为多少。这个就是我们图形的宽度了。可以用于后面的二分。然后我们要计算数组 $ina$，表示 当宽度为 $i$ 时红色区域的面积，这个直接累加就好了。（不要问我为什么数组名这么奇怪）

2. 我们看到右面的图为 采集 $i$ 次的最多的蘑菇数量，显然黑色区域面积为 蘑菇数量 × 宽度 - 红色区域面积 ，用我们的数组表示为 $cou[i]*i-ina[i-1]$, 其中 $i$表示宽度。

3. 得到右边图形黑色的面积后，显然左边的也很好求了，就是每列高度都降低相同的数字。用数组表示 $cou[i]*i-ina[i-1]+(now-cou[i])*i$ 。其中   $now$ 表示为当前蘑菇的数量。

4. 具体操作为：先二分找到我们当前蘑菇的采集次数 $pos$ ,然后就代入上方的公式计算即可。（不要喷我为什么变量名这么奇怪）

## 代码顺序：

- 预处理出数组。

- $tarjan$ 缩点。

- 建新图，计算一个强连通分量内总计可以采集的蘑菇数量。

- $dfs$ 处理起点可达的强联通分量以及它的入度。

- $Topo$ 计算每个强联通分量作为终点的最大答案，然后更新最终答案。

## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cmath>
#include<stack>
#include<queue>
#include<iomanip>
using namespace std;
int dfn[1000010],low[1000010],bel[1000010],ru[1000010];
long long ina[20000],cou[20000],sum[1000010],maxx[1000010];
stack<int>sta;
bool ins[1000010];
int cnt,ti;
struct road
{
	int to;
	long long val;
};
vector<road>side[1000010],newside[1000010];
void tarjan(int x)
{
	dfn[x]=low[x]=++ti;
	ins[x]=1;sta.push(x);
	for(int i=0;i<side[x].size();i++)
	{
		int to=side[x][i].to;
		if(!dfn[to])
		{
			tarjan(to);
			low[x]=min(low[x],low[to]);
		}
		else if(ins[to])low[x]=min(low[x],dfn[to]);
	}
	if(dfn[x]==low[x])
	{
		bel[x]=++cnt;
		ins[x]=0;
		while(sta.top()!=x)
		{
			bel[sta.top()]=cnt;
			ins[sta.top()]=0;
			sta.pop();
		}
		sta.pop();
	}
}
void dfs(int x)
{
	ins[x]=1;
	for(int i=0;i<newside[x].size();i++)
	{
		int to=newside[x][i].to;
		++ru[to];
		if(!ins[to])dfs(to);
	}
}
queue<int>que;
int main()
{
	ios::sync_with_stdio(0);
	int now=0,sx;long long tot=0;
	for(int i=1;i<=20000;i++)
	{
		now+=i;tot+=now;
		cou[i]=now;ina[i]=tot;
		if(now>110000000)
		{
			sx=i;
			break;
		}
	}
	int n,m,a,b;long long c;cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a>>b>>c;
		side[a].push_back((road){b,c});
	}
	for(int i=1;i<=n;i++)
	if(!dfn[i])tarjan(i);
	for(int x=1;x<=n;x++)
	for(int i=0;i<side[x].size();i++)
	{
		int to=side[x][i].to;
		long long val=side[x][i].val;
		if(bel[x]!=bel[to])newside[bel[x]].push_back((road){bel[to],val});
		else 
		{
			int pos=lower_bound(cou+1,cou+sx+1,val)-cou;
			long long nu=cou[pos]*pos-ina[pos-1]+(val-cou[pos])*pos;
			sum[bel[x]]+=nu;
		}
	}
	long long ans=0;
	cin>>a;
	dfs(bel[a]);
	que.push(bel[a]);
	while(!que.empty())
	{
		int x=que.front();que.pop();
		maxx[x]+=sum[x];ans=max(ans,maxx[x]);
		for(int i=0;i<newside[x].size();i++)
		{
			int to=newside[x][i].to;
			long long val=newside[x][i].val;
			--ru[to];if(!ru[to])que.push(to);
			maxx[to]=max(maxx[to],maxx[x]+val);
		}
	}
	cout<<ans;
}
```

---

## 作者：谁是鸽王 (赞：1)

## 【题解】CF894E Ralph and Mushrooms (缩点)

这是紫？给个解方程算法

考虑一条边若可以重复遍历说明一定有环，有环的话一定会把环上的蘑菇榨干，考虑一条边从全部到榨干的贡献是多少

$\sum_{i=0}^x (w-\sum_{j=0}^i j)=\sum_{i=0}^x (w-{i(i+1)\over 2})$


那么考虑解出$x$的值，解出来$x=\lfloor{-1+\sqrt{1+8w}\over 2}\rfloor$，预处理$\sum {i(i+1)\over 2}$可以直接计算贡献(其实也可以解通项公式)

然后Tarjan缩点之后变成DAG上的DP，同时有点权和边权的DAG DP

时间复杂度$O(n)$

```cpp
//@winlere
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>

using namespace std;  typedef long long ll;   char __buf[1<<18],*__c=__buf,*__ed=__buf;
inline int qr(){
	register int ret=0,f=0;
	register char c=getchar();
	while(!isdigit(c))f|=c==45,c=getchar();
	while(isdigit(c)) ret=ret*10+c-48,c=getchar();
	return f?-ret:ret;
}

const int maxn=1e6+5;
struct E{int to,w;};
vector<E> e[maxn],e2[maxn];
inline void add(const int&fr,const int&to,const int&w){e[fr].push_back({to,w});}
inline void add2(const int&fr,const int&to,const int&w){
	e2[fr].push_back({to,w});
}
int n,m;
int qaq[maxn],cnt;
ll w[maxn],dp[maxn];
bool usd[maxn];
int low[maxn],dfn[maxn],in[maxn],stk[maxn],top,siz[maxn];
ll s[maxn];
 
void dfs(const int&now){
	stk[++top]=now; in[now]=1;
	low[now]=dfn[now]=++*dfn;
	for(auto t:e[now]){
		if(!dfn[t.to]) dfs(t.to),low[now]=min(low[now],low[t.to]);
		else if(in[t.to]) low[now]=min(dfn[t.to],low[now]);
	}
	if(low[now]==dfn[now]){
		++cnt;
		int temp;
		do temp=stk[top--],in[temp]=0,qaq[temp]=cnt,++siz[cnt];
		while(temp!=now);
	}
}

ll Dp(const int&now){
	if(usd[now]) return dp[now];
	dp[now]=0;
	for(auto t:e2[now]) dp[now]=max(dp[now],Dp(t.to)+t.w);
	usd[now]=1;
	return dp[now]=w[now]+dp[now];
}

int main(){
	n=qr(); m=qr();
	for(int t=1,t1,t2,t3;t<=m;++t) t1=qr(),t2=qr(),t3=qr(),add(t1,t2,t3);
	for(int t=1;t<maxn;++t) s[t]=s[t-1]+(1ll*t*(t+1)>>1);
	int S=qr();
	dfs(S);
	for(int t=1;t<=n;++t)
		for(auto i:e[t]){
			if(qaq[t]==qaq[i.to]) {
				int k=(sqrt((long double)1+8ll*i.w)-1)/2.0;
				w[qaq[t]]=w[qaq[t]]+(k+1ll)*i.w-s[k];
			}
			else add2(qaq[t],qaq[i.to],i.w);
		}
	ll ans=Dp(qaq[S]);
	printf("%lld\n",ans);
	return 0;
}



```





---

## 作者：gyyyyx (赞：0)

[题面](https://www.luogu.com.cn/problem/CF894E)

又是一道好想不好做的题。

做过[采蘑菇](https://www.luogu.com.cn/problem/P2656)的童鞋应该知道这题的思路（几乎一模一样）。不过为了~~过审~~照顾其它人，我还是讲一下。

显然，强联通分量里可以随便走，也就是可以走每条边无数次，那肯定可以将**包括新长出在内的**所有蘑菇取完。那就先缩点，然后每个点的点权代表了这个强联通分量里所有蘑菇数量。然后跑一趟最长路就可以了。

需要注意的是，缩完点后的 DAG 既有点权又有边权，可以把点权加到边权上，也可以跑最长路的时候加上。

结果交上去后发现超时了。

为什么？因为计算强联通分量里边的蘑菇数量要 $\sqrt{n}$ 的复杂度，加上枚举边，$m\sqrt{n}$ 的时间这题肯定接受不了。

怎么办？

针对每一条边，设这条边初始蘑菇数为 $s$，可以走的次数为 $x$（即走了 $x$ 次之后就没有蘑菇了）。

显然有：

$$
\frac{x(x+1)}{2}\leq s<\frac{(x+1)(x+2)}{2}
$$

也就是说，$x$ 为方程 $\frac{x(x+1)}{2}=s$ 的非负数解向下取整。

易得 $x=\frac{\sqrt{8s+1}-1}{2}$，即 $x=\sqrt{2s+0.25}-0.5$，求出这个值然后向下取正就行。

但怎么算蘑菇总数呢？

明显，蘑菇总数等于初始蘑菇数量乘走的次数加一的和，再减去每次会减少的蘑菇数量的和。

加一是因为要加上第一次走，还未减少蘑菇。

设蘑菇总数为 $v$，每次会减少的蘑菇数量的和为 $y$。

所以 $v=s(x+1)-y$。

因为 $s$ 和 $x$ 都知道了，只需要求 $y$。

怎么求？别急，将所有 $x$ 所代表的 $y$ 打个表：

```
1 4 10 20 35...
```

是不是很熟悉？组合数！！

发现 $y=C^3_{x+2}=\frac{x(x+1)(x+2)}{6}$。

那就可以完美求解了。

你可能会问为什么？下面是我对于上面求 $y$ 时的公式的证明，大佬可跳过。

$$
\begin{aligned}
y
&=\frac{\underset{i=1}{\overset{x}{\sum}}i(i+1)}{2}\\
&=\frac{\underset{i=1}{\overset{x}{\sum}}i^2+\underset{i=1}{\overset{x}{\sum}}i}{2}\\
&=\frac{\frac{x(x+1)(2x+1)}{6}+\frac{x(x+1)}{2}}{2}\\
&=\frac{x(x+1)(2x+1)+3x(x+1)}{12}\\
&=\frac{x(x+1)(x+2)}{6}\\
&=C^3_{x+2}
\end{aligned}
$$

好的，最后上具体代码：

```cpp#include<bits/stdc++.h>
#define ll long long
#define N 1000005
using namespace std;
int n,m,start;
struct Edge{int v;ll w;};
vector <Edge> g[N],G[N];
int dfn[N],low[N],cnt,S[N],tot;
stack <int> st;
ll val[N],dis[N];
bool vis[N];
void Tarjan(int k){
	dfn[k]=low[k]=++cnt;st.push(k);vis[k]=1;
	for(int i(0);i<g[k].size();++i){
		int s(g[k][i].v);
		if(!dfn[s]){
			Tarjan(s);
			low[k]=min(low[k],low[s]);
		}
		else if(vis[s]) low[k]=min(low[k],dfn[s]);
	}
	if(low[k]==dfn[k]){
		int x(-1);++tot;
		while(x^k){
			x=st.top();st.pop();
			S[x]=tot;vis[x]=0;
		}
	}
}
inline ll dfs(int k){
	if(dis[k]) return dis[k];
	for(int i(0);i<G[k].size();++i)
		dis[k]=max(dis[k],dfs(G[k][i].v)+G[k][i].w);
	return dis[k]+=val[k];
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i(1);i<=m;++i){
		int u,v;ll w;
		scanf("%d%d%lld",&u,&v,&w);
		g[u].push_back((Edge){v,w});
	}
	for(int i(1);i<=n;++i) if(!dfn[i]){cnt=0;Tarjan(i);}
	for(int u(1);u<=n;++u)
		for(int i(0);i<g[u].size();++i){
			int v(g[u][i].v);
			if(S[u]==S[v]){
				ll t(sqrt(2*g[u][i].w+0.25)-0.5);
				val[S[u]]+=(t+1)*g[u][i].w-t*(t+1)*(t+2)/6;
			}
			else G[S[u]].push_back((Edge){S[v],g[u][i].w});
		}
	scanf("%d",&start);
	printf("%lld\n",dfs(S[start]));
	return 0;
}
```

---

## 作者：Hexarhy (赞：0)

### Preface

远古 CF 图论板子题，套了个数学。

### Solution

不难想到，在有向图中，环上的边可以一直遍历直到取完。其余的边只能走一次。

因此可以考虑缩点，在 DAG 上拓扑求出答案。

关键在于如何计算环上的点可以得到多少贡献。

考虑一条边，权值为 $w$，有效经过次数为 $t$，那么满足：

$$\frac{t(t+1)}{2}\le w$$

解一下二次不等式，可以得到：

$$t=\lceil\dfrac{\sqrt{1+8w}-1}{2} \rceil$$

然后就是计算这 $t$ 次经过能产生的总贡献：

$$w+(w-1)+(w-1-2)+\cdots +(w-1-2-\cdots -(t-1))$$

写成和式就是（**考虑每个数字减去的次数**）：

$$tw-\sum_{i=0}^{t-1} (t-i)i$$

把 $\sum$ 里的拆开，最后得到：

$$tw-\left(\frac{t^2(t-1)}{2}-\frac{t(t-1)(2t-1)}{6}\right)$$

----------

接下来是图论部分。

缩点之后这个环上的权值加在这个缩成点上，然后拓扑排序 +dp 就行了，很套路。dp 写出来就是：

$$f_v=\max\{f_{u}+w_v+val(u,v)\}$$

其中 $w_v$ 是 $v$ 这个点缩点后的点权，$val(u,v)$ 是 $u\to v$ 的边权。

### Code

笔者的缩点是并查集实现的，有很多细节。这里不便悉数指出。

```cpp
int find(cint& a)
{
	return f[a]==a?a:f[a]=find(f[a]);
}

inline ll calc(const ll n)
{
	const ll t=ceil((sqrt(1+8ll*n)-1.0)/2.0);
	const ll p=(t-1)*t*t/2-(t-1)*t*(2*t-1)/6;
	return t*n-p;
}

void dfs(cint& u)
{
	for(const auto& it:edge[u])
	{
		cint& v=it.to;
		if(!visit[v])
		{
			visit[v]=visit[u]+1;
			dfs(v);
		}
		cint fu=find(u),fv=find(v);
		if(visit[fv]>0)
		{
			if(visit[fu]<visit[fv])	f[fv]=fu;
			else	f[fu]=fv;
		}
	}
	visit[u]=-1;
}

void topo_sort(void)
{
	for(int i=1;i<=n;i++)
		dis[find(i)]=w[find(i)];
	queue <int> q;
	for(int i=1;i<=n;i++)
		if(!indeg[i])
			q.emplace(i);
	memset(visit,0,sizeof(visit));
	while(!q.empty())
	{
		cint u=q.front();q.pop();
		if(visit[u])	continue;
		visit[u]=true;
		for(const auto& it:edge[u])
		{
			cint v=it.to;
			dis[v]=max(dis[v],dis[u]+it.val+w[v]);
			indeg[v]--;
			if(!indeg[v])	q.emplace(v);
		}
	}
}

int main()
{
	read(n,m);
	for(int i=1;i<=n;i++)	f[i]=i;
	for(int i=1;i<=m;i++)
	{
		int u,v,val;read(u,v,val);
		e[i]=Edge{u,v,val};
		edge[u].emplace_back(node{v,val});
	}
	read(st);
	for(int i=1;i<=n;i++)
		if(!visit[i])
		{
			visit[i]=1;
			dfs(i);
		}
	for(int i=1;i<=n;i++)	edge[i].clear();
	for(int i=1;i<=m;i++)
	{
		cint x=find(e[i].u),y=find(e[i].v);
		if(x==y)	w[x]+=calc(e[i].w);
	}
	for(int i=1;i<=m;i++)
	{
		cint x=find(e[i].u),y=find(e[i].v);
		if(x==y)	continue;
		edge[find(e[i].v)].emplace_back(node{find(e[i].u),e[i].w});
		indeg[find(e[i].u)]++;
	}
	topo_sort();
	cout<<dis[find(st)]<<endl; 
	return 0;
}
```

---

## 作者：zhmshitiancai (赞：0)

[门](https://codeforces.ml/contest/894/problem/E)

题意：给定一个$n$个点$m$条边的图，每条边有边权，第一次经过时，边权是$k_i$，第二次是$k_i-1$，第三次是$k_i-1-2$，以此类推，边权不会低于$0$。问从$S$点出发，最多的边权和为多少。

题解：对于$scc$中的点，应该把其中的边权跑满，如何计算一条边跑满的代价呢？

先二分出第几次时这条边会$<0$，为$x$，则这条边的贡献是$x*k_i-he(x)$，$he(i)$是$1\sim i$的和的和。

把所有边的贡献加到$scc$中作为点权。

然后逆着拓扑序跑$DP$,因为题目要算$S$出发的最大值。

因为已经跑过$tarjan$，所以不用拓扑排序，直接循环即可。
```cpp
	for(i=1;i<=tot;i++)
	{
		for(j=0;j<v[i].size();j++)
		{
			int u=v[i][j].fi;ll nu=v[i][j].se;
			ans[u]=max(ans[u],ans[i]+nu+a[u]);
		}	
	}
```

#### Tips
我也不知道为什么拓扑排序会T。

**code(AC)**
```cpp
//love yjl forever
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
const int INF=0x3f3f3f3f,N=1e6+5,M=1e6+5;
int n,m,S;
int head[N],to[M],Next[M],cnt;
ll num[M];
void add(int x,int y,ll z)
{
	Next[++cnt]=head[x];head[x]=cnt;to[cnt]=y;num[cnt]=z;
}
int dfn[N],low[N],belong[N],sta[N],top,tot,bh;
bool vis[N];
void tarjan(int x)
{
	dfn[x]=low[x]=++bh;
	sta[++top]=x;vis[x]=1;
	for(int i=head[x];i;i=Next[i])
	{
		int u=to[i];
		if(!dfn[u])
		{
			tarjan(u);
			low[x]=min(low[x],low[u]);
		}
		else if(vis[u])
		{
			low[x]=min(low[x],dfn[u]);
		}
	}
	if(low[x]==dfn[x])
	{
		int y;tot++;
		do
		{
			y=sta[top--];
			belong[y]=tot;
			vis[y]=0;
		}while(y!=x);
	}
}
ll hehe[15005],he[15005],a[N],ans[N];
ll calc(ll x)
{
	ll k=lower_bound(he+1,he+15001,x)-he;
	return k*x-hehe[k-1];
}
vector<pair<int,ll> > v[N];
int main()
{
/*	freopen("","r",stdin);
	freopen("","w",stdout);*/
	int i,j;
	for(i=1;i<=15000;i++)
		he[i]=(i*(i+1)/2),hehe[i]=hehe[i-1]+he[i];
		
	cin>>n>>m;
	for(i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
	}
	for(i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i);
	cin>>S;
//	for(i=1;i<=tot;i++)
//		cout<<a[i]<<" ";
		
	for(i=1;i<=n;i++)
		for(j=head[i];j;j=Next[j])
		{
			int u=to[j];ll nu=num[j];
			if(belong[i]==belong[u])
			{
				a[belong[i]]+=calc(nu);
			}
			else 
			{
				v[belong[u]].pb(mp(belong[i],nu));
			}
		}
	for(i=1;i<=tot;i++)
		ans[i]=a[i];
	for(i=1;i<=tot;i++)
	{
		for(j=0;j<v[i].size();j++)
		{
			int u=v[i][j].fi;ll nu=v[i][j].se;
			ans[u]=max(ans[u],ans[i]+nu+a[u]);
		}	
	}
	cout<<ans[belong[S]]<<endl;
}
```

**code(T)**
```cpp
//love yjl forever
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
const int INF=0x3f3f3f3f,N=1e6+5,M=1e6+5;
int n,m,S;
int head[N],to[M],Next[M],cnt;
ll num[M];
void add(int x,int y,int z)
{
	Next[++cnt]=head[x];head[x]=cnt;to[cnt]=y;num[cnt]=z;
}
int dfn[N],low[N],belong[N],sta[N],top,tot,bh;
bool vis[N];
void tarjan(int x)
{
	dfn[x]=low[x]=++bh;
	sta[++top]=x;vis[x]=1;
	for(int i=head[x];i;i=Next[i])
	{
		int u=to[i];
		if(!dfn[u])
		{
			tarjan(u);
			low[x]=min(low[x],low[u]);
		}
		else if(vis[u])
		{
			low[x]=min(low[x],dfn[u]);
		}
	}
	if(low[x]==dfn[x])
	{
		int y;tot++;
		do
		{
			y=sta[top--];
			belong[y]=tot;
			vis[y]=0;
		}while(y!=x);
	}
}
ll hehe[15005],he[15005],a[N],ans[N],bi[N];
int de[N];
ll calc(ll x)
{
	ll k=lower_bound(he+1,he+15001,x)-he;
	return k*x-hehe[k-1];
}
int live[N];
vector<pair<int,ll> > v[N];
void dfs(int x)
{
	live[x]=1;
	for(int i=0;i<v[x].size();i++)
	{
		int u=v[x][i].fi;
		dfs(u);
	}
}
void topsort()
{
	int i,j;
	for(i=1;i<=n;i++)
		for(j=head[i];j;j=Next[j])
		{
			int u=to[j],nu=num[j];
			if(belong[i]!=belong[u]&&live[belong[i]]&&live[belong[u]])
			{
				de[belong[u]]++;
			}
		}	
	queue<int> q;
	q.push(belong[S]);
	ans[belong[S]]=a[belong[S]];
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(i=0;i<v[x].size();i++)
		{
			int u=v[x][i].fi;ll nu=v[x][i].se;
			if(!live[u]) continue;
		//	cout<<x<<" "<<u<<" "<<nu<<endl;
			ans[u]=max(ans[u],ans[x]+nu);
			de[u]--;
			if(!de[u])
			{
				ans[u]+=a[u];
				q.push(u);
			}
				
		}
	}
}
int main()
{
/*	freopen("","r",stdin);
	freopen("","w",stdout);*/
	int i,j;
	for(i=1;i<=15000;i++)
		he[i]=(i*(i+1)/2),hehe[i]=hehe[i-1]+he[i];
		
	cin>>n>>m;
	for(i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
	}
	for(i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i);
	cin>>S;
//	for(i=1;i<=tot;i++)
//		cout<<a[i]<<" ";
		
	for(i=1;i<=n;i++)
		for(j=head[i];j;j=Next[j])
		{
			int u=to[j];ll nu=num[j];
			if(belong[i]==belong[u])
			{
				a[belong[i]]+=calc(nu);
			}
			else 
			{
				v[belong[i]].pb(mp(belong[u],nu));
			}
		}
//	for(i=1;i<=tot;i++)
//		cout<<a[i]<<endl;
//		
	dfs(belong[S]);
	
	
	topsort();
	cout<<*max_element(ans+1,ans+1+tot)<<endl;
//	for(i=1;i<=tot;i++)
//		cout<<ans[i]<<" ";
}
```

---

## 作者：Rainybunny (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[$luogu$](https://www.luogu.org/problem/CF894E).
# 题解
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;应该算是一道比较板的缩点了.
## $Part_1$ 思路
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;首先我们考虑一条边, 如果它是环上的边, $Ralph$当然应该一直转圈圈直到环上没有一点蘑菇. 所以想到利用$Tarjan$缩点, 在算出每个点的收益, 最后$DAG$上$DP$求最长链即可.
## $Part_2$ 点权计算
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;说是点权, 其实它是原图上若干边的收益之和.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;首先, 我们考虑一条权为$w$的边提供的收益. 假设这条边最多提供$n+1$次收益, 那么:
$$
\sum_{i=0}^ni\le w
$$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;即:
$$
\frac{n(n+1)}2\le w
$$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑通过一元二次方程的根求出$n$的最大值, 那么:
$$
\frac{1}2n^2+\frac{1}2n-w\le0
$$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;由于$n\ge0$, 该方程的正根就是$n$的最大值, 下去整便是所求的$n$. 即:
$$
n=\lfloor-\frac{1}2+\sqrt{\frac{1}4+2w}\rfloor
$$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;于是轻易地求出这条边的贡献为:
$$
w(n+1)-\frac{1}2\sum_{i=0}^ni(i+1)
$$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;对于后一项, 可以裂项展开, 化为:
$$
w(n+1)-\frac{n(n+1)(n+2)}6
$$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$O(1)$计算完成.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;此后, 我们在建新图时, 考虑如果一条边连接两个$SCC$, 就把其加入新图, 否则加入这个$SCC$的权. 然后跑一边最长链即可.
## $Part_3$ 代码
```cpp
#include <cmath>
#include <stack>
#include <cstdio>

#define Int register int

using namespace std;

typedef long long int LL;

const int MAXN = 1e6, MAXM = 1e6;
int n, m, s, Cnte, CprC, Head[MAXN + 5] = {}, CprH[MAXN + 5] = {};
int Indx, Cnts, DFN[MAXN + 5] = {}, Low[MAXN + 5] = {}, SCC[MAXN + 5] = {};
LL Val[MAXN + 5] = {}, F[MAXN + 5] = {};
bool Instk[MAXN + 5] = {};
stack<int> S;

struct Edge { int To, Cost, _nxt; } Graph[MAXM + 5] = {}, CprG[MAXM + 5] = {};

template<typename _T>
inline _T Min ( const _T a, const _T b ) { return a < b ? a : b; }

template<typename _T>
inline _T Max ( const _T a, const _T b ) { return a > b ? a : b; }

inline void Link ( const int From, const int To, const int Cost ) {
	Graph[++ Cnte] = { To, Cost, Head[From] };
	Head[From] = Cnte;
}

inline void CprLink ( const int From, const int To, const int Cost ) {
	CprG[++ CprC] = { To, Cost, CprH[From] };
	CprH[From] = CprC;
}

inline LL Calc ( const int w ) {
	LL n = sqrt ( 2.0 * w + 0.25 ) - 0.5;
	return w * ( n + 1 ) - n * ( n + 1 ) / 2 * ( n + 2 ) / 3;
}

inline void Tarjan ( const int u ) {
	int v;
	DFN[u] = Low[u] = ++ Indx, Instk[u] = true, S.push ( u );
	for ( Int i = Head[u], v; i; i = Graph[i]._nxt ) {
		if ( ! DFN[v = Graph[i].To] ) {
			Tarjan ( v ), Low[u] = Min ( Low[u], Low[v] );
		} else if ( Instk[v] ) {
			Low[u] = Min ( Low[u], DFN[v] );
		}
	}
	if ( DFN[u] == Low[u] ) {
		++ Cnts;
		do {
			Instk[v = S.top ()] = false, S.pop ();
			SCC[v] = Cnts;
		} while ( u ^ v );
	}
}

inline void MakeGraph () {
	for ( Int i = 1; i <= n; ++ i ) {
		if ( ! DFN[i] ) continue;
		int u = SCC[i], v;
		for ( Int j = Head[i]; j; j = Graph[j]._nxt ) {
			if ( u ^ ( v = SCC[Graph[j].To] ) ) {
				CprLink ( u, v, Graph[j].Cost );
			} else {
				Val[u] += Calc ( Graph[j].Cost );
			}
		}
	}
}

inline void DFS ( const int u ) {
	if ( F[u] ) return ;
	for ( Int i = CprH[u], v; i; i = CprG[i]._nxt ) {
		DFS ( v = CprG[i].To ), F[u] = Max ( F[u], F[v] + CprG[i].Cost );
	}
	F[u] += Val[u];
}

inline void Work () {
	scanf ( "%d %d", &n, &m );
	for ( Int i = 1, u, v, w; i <= m; ++ i ) {
		scanf ( "%d %d %d", &u, &v, &w );
		Link ( u, v, w );
	}
	scanf ( "%d", &s );
	Tarjan ( s );
	MakeGraph ();
	DFS ( SCC[s] );
	printf ( "%lld\n", F[SCC[s]] );
}

int main () {
	Work ();
	return 0;
}
```

---

## 作者：Xx_queue (赞：0)

题目链接:[https://www.luogu.org/problem/CF894E](https://www.luogu.org/problem/CF894E)

题目大意
Ralph打算去蘑菇森林采蘑菇。

蘑菇森林里有n个蘑菇丛，有m条有向的路连接这些丛林（可能连向自己，也可能两个丛林之间有多条路）。经过某条路时，Ralph可以采走这条路上的全部蘑菇。然而，这是一片神奇的蘑菇森林，蘑菇被采走后会重新长出来一些。但是，第k次走过这条路后，这条路上重新长出的蘑菇会比上次少k。（举个栗子，第一次有w个蘑菇，第二次有w-1个蘑菇，第三次有w-1-2个蘑菇，以此类推……）（还有，蘑菇的数量大于0）。

那么，Ralph最多可以采到多少蘑菇呢？

输入输出样例

输入 #1

2 2
1 2 4
2 1 4
1

输出 #1

16

输入 #2

3 3
1 2 4
2 3 3
1 3 8
1

输出 #2

8

这个题目应该不难想到,一个强连通分量内的所有蘑菇都可以采光(重复走,一直绕圈把路上的所有蘑菇采掉)

那么一个强连通分量内的所有蘑菇数量是多少呢?

${n(n+1)<=w}$ 的最大的 ${n}$ ，解二次不等式,$n$ 就是 $1.0*\sqrt{0.25+2a}-0.5$

然后价值就是$nw-\sum^{n}_{i=1}i(i+1)/2+w$，也就是 $nw-n(n+1)(n+2)/6+w$

所以我们可以先用Tarjan缩点求出强连通分量,把边权合并到点上,重新建图,再来搜索一下就OK了;

那么注意几个地方:1.要开long long;

2.点权与边权混合加时不要漏加了终点的点权;

3.代码可能有点难调,耐心一点,一定可以调出来的(祭本题提交9次);

附上双倍经验:[P2656 采蘑菇](https://www.luogu.org/problem/P2656),稍微修改一下就能过了!

```cpp
#include <bits/stdc++.h>
#define N (2000000+5)
#define int long long
using namespace std;
int n,m,s;
int top,sum,deep;
int dfn[N],low[N],color[N],vis[N],st[N];
int cnt[N],in[N],wp[N],f[N];
int u[N],v[N],wei[N];
vector <int> edge[N],w[N];
void Tarjan(int u)
{
	vis[u]=1;
	dfn[u]=low[u]=++deep;
	st[++top]=u;
	for(int i=0;i<edge[u].size();i++)
	{
		int now=edge[u][i];
		if(!dfn[now])
		{
			Tarjan(now);
			low[u]=min(low[u],low[now]);
		}
		else
		{
			if(vis[now]) low[u]=min(low[u],low[now]);
		}
	}
	if(dfn[u]==low[u])
	{
		color[u]=++sum;
		vis[u]=0;
		while(st[top]!=u)
		{
			color[st[top]]=sum;
			vis[st[top--]]=0;
		}
		top--;
	}
}
int dfs(int u)
{
    if(vis[u]) return f[u];
    int res=0;
	vis[u]=1;
    for (int i=0;i<edge[u].size();i++)
	{
        int now=edge[u][i];
        res=max(res,dfs(now)+w[u][i]);
    }
    return f[u]=res+wp[u];
}
int cont(int a)
{
	int k=1.0*sqrt(0.25+2*a)-0.5;
	return a*k-k*(k+1)*(k+2)/6+a;
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld%lld",&u[i],&v[i],&wei[i]);
		edge[u[i]].push_back(v[i]);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i);
	for(int i=1;i<=n;i++) vector<int>().swap(edge[i]);
	for(int i=1;i<=m;i++)
	{
		if(color[u[i]]==color[v[i]])
		{
			wp[color[u[i]]]+=cont(wei[i]);
		}
		else
		{
			//printf("u=%lld v=%lld\n",color[u[i]],color[v[i]]);
			edge[color[u[i]]].push_back(color[v[i]]);
			w[color[u[i]]].push_back(wei[i]);
			in[color[v[i]]]++;
		}
	}
	scanf("%lld",&s);
	memset(vis,0,sizeof(vis));
	printf("%lld\n",dfs(color[s]));
	return 0;
```

---

