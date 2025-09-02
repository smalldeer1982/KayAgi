# [ICPC 2016 WF] Branch Assignment

## 题目描述

创新消费品公司（ICPC）计划启动一个绝密项目。该项目由 $s$ 个子项目组成。将有 $b \ge s$ 个 ICPC 的分支机构参与此项目，ICPC 希望将每个分支机构分配给一个子项目。换句话说，这些分支机构将形成 $s$ 个不相交的组，每个组负责一个子项目。

每个月底，每个分支机构将向其组内的每个其他分支机构发送一条消息（每个分支机构接收不同的消息）。ICPC 有一个特定的通信协议。每个分支机构 $i$ 有一个只有该分支机构和 ICPC 总部知道的密钥 $k_i$。假设分支机构 $i$ 想要向分支机构 $j$ 发送消息。分支机构 $i$ 用其密钥 $k_i$ 加密消息。一个可信的信使从该分支机构取走消息并将其交付给 ICPC 总部。总部用密钥 $k_i$ 解密消息，并用密钥 $k_j$ 重新加密。然后信使将这个新加密的消息交付给分支机构 $j$，分支机构 $j$ 用其自己的密钥 $k_j$ 解密。出于安全原因，信使一次只能携带一条消息。

给定一个道路网络以及分支机构和总部在此网络中的位置，你的任务是确定信使在所有可能的分支机构到子项目的分配中，传递所有月底消息所需的最小总距离。

## 说明/提示

时间限制：2000 毫秒，内存限制：1048576 kB。

国际大学生程序设计竞赛（ACM-ICPC）世界总决赛 2016。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5 4 2 10
5 2 1
2 5 1
3 5 5
4 5 0
1 5 1
2 3 1
3 2 5
2 4 5
2 1 1
3 4 2
```

### 输出

```
13
```

## 样例 #2

### 输入

```
5 4 2 10
5 2 1
2 5 1
3 5 5
4 5 10
1 5 1
2 3 1
3 2 5
2 4 5
2 1 1
3 4 2
```

### 输出

```
24
```

# 题解

## 作者：5u0i5n11i (赞：4)

大家应该都可以想到，一个点对另一个点传递信息的价值为它到总部的最短路加上总部到另一个点的最短路，在下文，我们设一个点到总部的最短路加上总部到它的最短路为$d_i$。



对于分到一个子集的点，若子集的大小为m，那么这个子集的总代价是：



$(m-1)\sum_{i=1}^md_i$



于是，我们得到一个明显的贪心思想，那就是，d越大的值，它所在的子集就应该越小。然后，我们便可以把那些小的放一个大一点的子集，大的放一个小一点的子集。



我们把这些点按照$d$的大小排序，然后可以得到一个明显的转移方程式：



设 $f_{i,j}$ 为当前是第i个点，放了j个子集。

计 $(r-l-1)\sum_{i=l}^rd_i$ 这个为 $cost_{l,r}$



$f_{i,j}=min_{k=0}^{i-1}(f_{k,j-1}+cost_{k,i})$



上面这个方程式明显是 $O(n^3)$ 的，通不过此题。



### 能不能快一点？



可以，我们发现后面的 $cost$ 满足四边形不等式，于是可以用四边形不等式优化dp



按理来说，这就已经可以通过了，但是，我在https://www.luogu.com.cn/problem/UVA1737看到了这么一句话：



**有 $nlog^2$ 级的算法**



### 能不能再快一点？



观察题目，注意到 **正好建立s个集合**



想到带权二分，我们通~~打表~~证明发现若我们给选的集合数带上代价，是一个凸函数。



然后我们干掉dp的一维，不管集合数那一维，列出方程式：



$f_{i}=min_{k=0}^{i-1}(f_{k}+cost_{k,i})$



代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#define maxn 50005
#define maxr 200005
#define eps 1e-8

using namespace std;

struct node {
	long long val;
	int c;
	node operator + (node x) {
		return (node){val + x.val,c + x.c};
	}
}f[maxn];

struct dot{
	int c,l,r;
}qu[maxn];

node mins(node q,node p) {
	if (q.val < p.val) return q;
	else return p;
}

int n,b,s,r,nex[maxr],to[maxr],head[maxr],tot = 0,front,tail;
long long edge[maxr],dis[maxn],vis[maxn],sum[maxn],from[maxn],go[maxn],len[maxn],sum1[maxn],d[maxn];

std::priority_queue <std::pair<long long ,long long > > q;

void add(long long x,long long y,long long z) {
	to[++tot] = y; nex[tot] = head[x]; edge[tot] = z; head[x] = tot;
}

void dijkstra(long long st) {
	for (int i = 1;i <= n;i++) dis[i] = 9999999999999999;
	memset(vis,0,sizeof(vis));
	dis[st] = 0;
	q.push(std::make_pair(0,st));
	while (!q.empty()) {
		int x = q.top().second;
		q.pop();
		if (vis[x]) continue;
		vis[x] = 1;
		for (int i = head[x];i;i = nex[i]) {
			int y = to[i],z = edge[i];
			if (dis[y] > dis[x] + z) {
				dis[y] = dis[x] + z;
				q.push(std::make_pair(-dis[y],y));
			}
		}
	}
}

long long cost(int i,int j,long long num) {
	return f[j].val + (long long)(sum[i] - sum[j]) * (long long)(i - j - 1) + num;
}

void run(long long num) {
	qu[front = tail = 1] = {0,1,b};
	for (int i = 1;i <= b;i++) {
		f[i] = {999999999999,0};
		for (int j = 0;j < i;j++) {
			f[i] = mins(f[i],(node){cost(i,j,num),f[j].c + 1});
		}
	}
}

void half() {
	long long l = 0,r = 9999999999999999,ans = 0;
	while (r >= l) {
		long long  mid = (r + l) / 2;
		run(mid);
		if (f[b].c > s) l = mid + 1;
		else if (f[b].c < s) r = (ans = mid) - 1;
		else {printf("%lld\n",f[b].val - mid * s);return;}
	}
	l--;
	run(l);
	printf("%lld\n",f[b].val - l * s);
}

int main() {
	scanf("%d%d%d%d",&n,&b,&s,&r);
	for (int i = 1;i <= r;i++) {
		int x,y;
		long long z;
		scanf("%lld%lld%lld",&from[i],&go[i],&len[i]);
		add(from[i],go[i],len[i]);
	}
	dijkstra(b + 1);
	for (int i = 1;i <= b;i++) d[i] = dis[i];
	memset(head,0,sizeof(head)); tot = 0;
	for (int i = 1;i <= r;i++) add(go[i],from[i],len[i]);
	dijkstra(b + 1);
	for (int i = 1;i <= b;i++) d[i] += dis[i];
	std::sort(d + 1,d + b + 1);
	for (int i = 1;i <= b;i++) sum[i] = sum[i - 1] + d[i];
	for (int i = 1;i <= b;i++) sum[i] += sum1[i];
	half();
	return 0;
}
```



复杂度：$O(n^2logn)$



复杂度不减反增。。。



### 能不能再快一点？




思考一下，我们的d数组排序后是不断递增的，并且，越大的数所在的集合应该越小。



那么我们在dp过程中，越靠后的的 $d_i$ 会选取的决策点离它就越近，同时，这也证明了这个dp满足**决策单调性**



然后我们就可以果断地使用决策单调性优化dp，来把又一个n化成 $logn$



代码：



```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#define maxn 50005
#define maxr 200005
#define eps 1e-8

using namespace std;

struct node {
	long long val;
	int c;
	node operator + (node x) {
		return (node){val + x.val,c + x.c};
	}
}f[maxn];

struct dot{
	int c,l,r;
}qu[maxn];

node mins(node q,node p) {
	if (q.val < p.val) return q;
	else return p;
}

int n,b,s,r,nex[maxr],to[maxr],head[maxr],tot = 0,front,tail;
long long edge[maxr],dis[maxn],vis[maxn],sum[maxn],from[maxn],go[maxn],len[maxn],sum1[maxn],d[maxn];

std::priority_queue <std::pair<long long ,long long > > q;

void add(long long x,long long y,long long z) {
	to[++tot] = y; nex[tot] = head[x]; edge[tot] = z; head[x] = tot;
}

void dijkstra(long long st) {
	for (int i = 1;i <= n;i++) dis[i] = 9999999999999999;
	memset(vis,0,sizeof(vis));
	dis[st] = 0;
	q.push(std::make_pair(0,st));
	while (!q.empty()) {
		int x = q.top().second;
		q.pop();
		if (vis[x]) continue;
		vis[x] = 1;
		for (int i = head[x];i;i = nex[i]) {
			int y = to[i],z = edge[i];
			if (dis[y] > dis[x] + z) {
				dis[y] = dis[x] + z;
				q.push(std::make_pair(-dis[y],y));
			}
		}
	}
}

long long cost(int i,int j,long long num) {
	return f[j].val + (long long)(sum[i] - sum[j]) * (long long)(i - j - 1) + num;
}

void search(int i,long long num){
    int now = qu[tail].c,ll = qu[tail].l,rr = qu[tail].r;
    int ret = qu[tail].r + 1;
    while(ll <= rr){
        int mid = (ll + rr) / 2;
        if(cost(mid,i,num) <= cost(mid,now,num)) rr = mid - 1,ret = mid;
        else ll = mid + 1;
    }
    if(ret != qu[tail].l) qu[tail].r = ret - 1;
    else tail--;
    if(ret <= b) qu[++tail] = (dot){i,ret,b};
}

void run(long long num) {
	qu[front = tail = 1] = {0,1,b};
	memset(f,0,sizeof(f));
	for (int i = 1;i <= b;i++) {
		while (front < tail && qu[front].r < i) front++;
		qu[front].l++;
		int j = qu[front].c;
		f[i] = node{cost(i,j,num),f[j].c + 1};
		while (front < tail && cost(qu[tail].l,qu[tail].c,num) >= cost(qu[tail].l,i,num)) tail--;
		search(i,num); 
	}
}

void half() {
	long long l = 0,r = 9999999999999999,ans = 0;
	while (r >= l) {
		long long  mid = (r + l) / 2;
		run(mid);
		if (f[b].c > s) l = mid + 1;
		else if (f[b].c < s) r = (ans = mid) - 1;
		else {printf("%lld\n",f[b].val - mid * s);return;}
	}
	l--;
	run(l);
	printf("%lld\n",f[b].val - l * s);
}

int main() {
	scanf("%d%d%d%d",&n,&b,&s,&r);
	for (int i = 1;i <= r;i++) {
		int x,y;
		long long z;
		scanf("%lld%lld%lld",&from[i],&go[i],&len[i]);
		add(from[i],go[i],len[i]);
	}
	dijkstra(b + 1);
	for (int i = 1;i <= b;i++) d[i] = dis[i];
	memset(head,0,sizeof(head)); tot = 0;
	for (int i = 1;i <= r;i++) add(go[i],from[i],len[i]);
	dijkstra(b + 1);
	for (int i = 1;i <= b;i++) d[i] += dis[i];
	std::sort(d + 1,d + b + 1);
	for (int i = 1;i <= b;i++) sum[i] = sum[i - 1] + d[i];
	for (int i = 1;i <= b;i++) sum[i] += sum1[i];
	half();
	return 0;
}
```


---

## 作者：another_world (赞：2)

### 题目链接：[P6918](https://www.luogu.com.cn/problem/P6918)


------------

### 思路分析：
1. 对于所求答案，首先我们需知道**任意一点到总部的最短路径**，以及**总部到任意一点的最短路径**，对于后者，直接在原图上跑单源最短路 dijkstra 得到 $dis1[i]$，而于前者，思考**反向建边**，同样操作可得到 $dis2[i]$.


2. 接下来考虑将 $b$ 个节点分成 $s$ 组，使得答案总代价最小，对于每组的代价为该组内 $ (dis1[i] + dis2[i]) \times($该组内节点个数$-1)$.




3. 令 $d[i]=dis1[i]+dis2[i]$，将 **$d$ 从小到大排序**，显然一定存在一种最优划分方案，其中每组的元素都是排完序后连续的一段(调整法证明).




4. 动态规划：状态设计 $dp[i][j]$ 表示前 $i$ 个点，分成 $j$ 段的最小代价，转移方程：

$f[i][j]=min_{k=j-1}^{i-1}(dp[k][j-1]+(d[k+1]+\dots+d[i]) \times (i-k-1))$

5. 上述转移方程的时间复杂度 $O(n^3)$，考虑在最优解中，$d$ 从小到大排序后**依次划分的段的长度一定是单调不增的**，则 $k$ 的取值范围缩减到
$[i-i/j,i)$ 之间，总转移时间复杂度 $ O(n^2(\frac{1}{1}+\frac{1}{2}+\dots+\frac{1}{n-1}+\frac{1}{n}))=O(n^2 \log n)$.

------------
### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f
#define mkp make_pair
const int N=5010;
const int M=51000;
int n,b,s,m,x[M],y[M],z[M];
int d[N],sum[N];
int dp[N][N]; // dp[i][j] 表示前 i 个点，分成 j 段的最小代价 
struct EDGE {
	int v,w,lt;
}E[M];
int head[N],tot;
void add(int u,int v,int w) {
	E[++tot].v=v;
	E[tot].w=w;
	E[tot].lt=head[u];
	head[u]=tot;
}
priority_queue<pair<int,int> > q;
int dis[N],vis[N];
void dij(int st) {
	for(int i=0; i<=n; i++) dis[i]=inf,vis[i]=0;
	dis[st]=0;
	q.push(mkp(0,st));
	while(!q.empty()) {
		int x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=head[x]; i; i=E[i].lt) {
			int y=E[i].v,z=E[i].w;
			if(dis[y]>dis[x]+z) {
				dis[y]=dis[x]+z;
				q.push(mkp(-dis[y],y));
			}
		} 
	} 
	for(int i=1; i<=b; i++) 
	    d[i]+=dis[i];
} 
signed main() {
    freopen("assignment.in","r",stdin);
    freopen("assignment.out","w",stdout);
    scanf("%lld%lld%lld%lld",&n,&b,&s,&m);
    for(int i=1; i<=m; i++) {
    	scanf("%lld%lld%lld",&x[i],&y[i],&z[i]);
    	add(x[i],y[i],z[i]);
	}
	dij(b+1);
	memset(head,0,sizeof(head)); 
	tot=0;
	for(int i=1; i<=m; i++) add(y[i],x[i],z[i]);  
	dij(b+1); 
	sort(d+1,d+b+1);
	for(int i=1; i<=b; i++) sum[i]=sum[i-1]+d[i];
	memset(dp,inf,sizeof(dp));
	dp[0][0]=0;
	for(int i=1; i<=b; i++) 
	    for(int j=1; j<=i; j++)
            for(int k=i-i/j; k<=i-1; k++) {
			    dp[i][j]=min(dp[i][j],dp[k][j-1]+(sum[i]-sum[k])*(i-k-1));
			}
	printf("%lld",dp[b][s]);
	return 0;
}
```


---

## 作者：ty_xyz (赞：1)

个人感觉这题前半部分和后半部分完全割裂。~~烂题~~

图是有向图，代价计算既要从 $x$ 到 $b+1$，又要从 $b+1$ 到 $x$。考虑把正图和反图都建出来，跑最短路得到两个路径长度，这是简单的。

然后考虑怎么算最小值。观察一个点对答案的贡献是怎样的：这个点要给同一个子集内的点发送信息，并且又要接收子集内的点的信息。那么，设 $s(x)$ 为点 $x$ 到总部的路径长，$t(x)$ 为总部到点 $x$ 的路径长，$d(x)=s(x)+t(x)$，则一个子集 $S$ 对答案的贡献就是 $\sum\limits_{x\in S}d(x)\times(|S|-1)$，应该很好理解。

发现对于一个点来说，跟哪些点分在一个子集对贡献没有关系，只跟子集大小有关系。那么感性理解一下，$d$ 值小的点应该分在一起，于是我们就可以把点按照 $d$ 值从小到大排序，得到一个 $\mathcal{O}(sb^2)$ 的做法。具体来说，定义 $f_{i,j}$ 为前 $i$ 个集合分了 $j$ 个点的最小代价，于是就有

$$f_{i,j}=\min_{i-1\le k<j}(f_{i-1,k}+(\sum_{l=k+1}^jd(l))\times(j-k-1))$$

发现这个方程可以写成 $f_{i,j}=f_{i-1,k}+w(k,j)$ 的形式，尝试套用四边形不等式优化。发现 $w$ 满足四边形不等式，则对于$f_{i,j}$ 的最优决策点 $opt_{i,j}$，满足 $opt_{i-1,j}\le opt_{i,j}\le opt_{i,j+1}$。于是，我们正序枚举 $i$，倒序枚举 $j$，即可把时间复杂度优化到 $\mathcal{O}(s(s+b))$。加上 Dijsktra 算法的时间复杂度，总时间复杂度为 $\mathcal{O}(r\log_2r+s(s+b))$。滚动数组下空间是 $\mathcal{O}(n+r)$ 的。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct edge
{
    int id,d;
    bool operator<(edge a)const{return d>a.d;}
};
vector<edge>g[5001][2];
int n,b,s,m,d[5001][2],w[5000],opt[5001];//滚动数组
long long f[5000],sum[5000];
bool vis[5001][2];
priority_queue<edge>q;
void dijsktra(bool tp)//tp 为 0 是正图，为 1 是反图
{
    for(int i=1;i<=n;i++)d[i][tp]=500000001;
    d[b+1][tp]=0;//注意 b+1 并不一定等于 n
    q.push(edge{b+1,0});
    while(!q.empty())
    {
        int u=q.top().id;
        q.pop();
        vis[u][tp]=1;
        for(auto&[v,w]:g[u][tp])
        {
            if(!vis[v][tp]&&d[v][tp]>d[u][tp]+w)
            {
                d[v][tp]=d[u][tp]+w;
                q.push(edge{v,d[v][tp]});
            }
        }
    }
}
signed main()
{
    scanf("%d%d%d%d",&n,&b,&s,&m);
    for(int i=1,x,y,z;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        g[x][0].push_back(edge{y,z});
        g[y][1].push_back(edge{x,z});
    }
    dijsktra(0);
    dijsktra(1);
    for(int i=1;i<=b;i++)w[i]=d[i][0]+d[i][1];
    sort(w+1,w+b+1);
    for(int i=1;i<=b;i++)
    {
        sum[i]=sum[i-1]+w[i];
        f[i]=5000000000000000001ll;
    }
    for(int i=1;i<=s;i++)
    {
        opt[b+1]=b;//存 b+1 的决策点，转移要用
        for(int j=b;j>=i;j--)
        {
            for(int k=opt[j];k<=opt[j+1];k++)
            {
                if(f[j]>f[k]+(sum[j]-sum[k])*(j-k-1))
                {
                    f[j]=f[k]+(sum[j]-sum[k])*(j-k-1);
                    opt[j]=k;
                }
            }
        }
    }
    printf("%lld\n",f[b]);
    return 0;
}
```

---

## 作者：SFlyer (赞：1)

主播差点不会写决策单调性。

首先预处理出每一个点从 $b+1$ 到它和从它到 $b+1$ 的距离，设和为 $dis_i$。我们发现如果 $i$ 被分到了一个大小为 $x$ 的组，$dis_i$ 就会贡献 $x-1$ 次。

如果我们已经确定了分成的组的大小，显然我们把 $dis_i$ 大的放到个数小的组里面更优。因此，有一个结论就是同一个组里面，都是 $dis_i$ 排序后连续的一段。这样我们把 $dis_i$ 从小到大排序，设 $sum_i$ 为 $dis_i$ 的前缀和，就可以有 dp：$dp_{i,j}$ 表示前 $i$ 个分了 $j$ 组了。转移是枚举组的大小，$dp_{i,j}=\min (dp_{k,j-1}+(i-k-1)\times (sum_i-sum_k)))$。可以 $\mathcal{O}(n^3)$ 暴力转移。

状态不能优化了，我们考虑优化转移。我们考虑：

假设 $dp_{i,j+1}$ 是从 $dp_{k,j}$ 转移过来的，比从 $dp_{k-1,j}$ 转移过来优。那么 $dp_{i+1,j}$ 的转移是不是 $dp_{k,j-1}$ 更优？我们计算 $(dp_{k,j}+(i-k)\times (s_{i+1}-s_k))-(dp_{k,j}+(i-k-1)\times(s_i-s_k))$ 和 $(dp_{k-1,j}+(i-k+1)\times (s_{i+1}-s_{k-1}))-(dp_{k-1,j}+(i-k)\times(s_{i}-s_{k-1}))$，发现前者是 $s_i-s_k+i-k$，后者是 $s_i-s_{k-1}+i-k+1$，显然前者小于后者。因此从 $dp_{k,j}$ 转移更优。

这样，就有决策单调性了。复杂度 $\mathcal{O}(n^2\log n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 5e3+3;

int n,b,s,r;
vector<pair<int,int> > g[N],_g[N];
int dis[N],vis[N],id[N],_dis[N];
ll sum[N],f[N],ff[N];

bool cmp(int x,int y){
	return dis[x]+_dis[x]<dis[y]+_dis[y];
}

void sol(int l,int r,int L,int R){
	if (r-l+1<=5 || R-L+1<=5){
		for (int i=L; i<=R; i++){
			ff[i]=1e18;
			for (int j=l; j<=min(i-1,r); j++){
				ff[i]=min(ff[i],f[j]+1ll*(i-j-1)*(sum[i]-sum[j]));
			}
		}
		return;
	}
	int mid=L+R>>1;
	ff[mid]=1e18;
	int pos=-1;
	for (int i=l; i<=r && i<mid; i++){
		if (ff[mid]>f[i]+1ll*(mid-i-1)*(sum[mid]-sum[i])){
			ff[mid]=f[i]+1ll*(mid-i-1)*(sum[mid]-sum[i]);
			pos=i;
		}
	}
	sol(l,pos,L,mid-1);
	sol(pos,r,mid+1,R);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n>>b>>s>>r;
	bool fl=1;
	for (int i=1; i<=r; i++){
		int u,v,w;
		cin>>u>>v>>w;
		fl&=(w==0);
		g[v].push_back({u,w});
		_g[u].push_back({v,w});
	}
	memset(dis,0x3f,sizeof dis);
	dis[b+1]=0;
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
	q.push({dis[b+1],b+1});
	while (!q.empty()){
		int u=q.top().second;
		q.pop();
		if (vis[u]){
			continue;
		}
		vis[u]=1;
		for (auto p : g[u]){
			int v=p.first,w=p.second;
			if (dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				q.push({dis[v],v});
			}
		}
	}
	memset(vis,0,sizeof vis);
	memset(_dis,0x3f,sizeof _dis);
	_dis[b+1]=0;
	q.push({_dis[b+1],b+1});
	while (!q.empty()){
		int u=q.top().second;
		q.pop();
		if (vis[u]){
			continue;
		}
		vis[u]=1;
		for (auto p : _g[u]){
			int v=p.first,w=p.second;
			if (_dis[v]>_dis[u]+w){
				_dis[v]=_dis[u]+w;
				q.push({_dis[v],v});
			}
		}
	}
	for (int i=1; i<=b; i++){
		id[i]=i;
	}
	sort(id+1,id+1+b,cmp);
	for (int i=1; i<=b; i++){
		sum[i]=sum[i-1]+dis[id[i]]+_dis[id[i]];
	}
	memset(f,0x3f,sizeof f);
	f[0]=0;
	for (int i=1; i<=s; i++){
		sol(0,b,1,b);
		for (int j=0; j<=b; j++){
			f[j]=ff[j];
		}
	}
	cout<<f[b]<<"\n";
	return 0;
}
```

---

## 作者：RPChe_ (赞：1)

其实发第一篇题解的那位老哥的决策单调性应该是错的，他只考虑了下界，因此时间复杂度应该是 $O(n^3)$ 的。

---

通过在原图和反图上分别跑一次 $\rm dijkstra$ 算法，我们可以预处理出每个点 $u$ 一来一去的代价，不妨分别记其为 $dis_1(u)$ 与 $dis_2(u)$ 。若 $u$ 被分配在一个大小为 $s$ 的集合中，我们知道 $dis_1(u)$ 与 $dis_2(u)$ 分别会被计算 $s-1$ 次，令 $dis_u=dis_1(u)+dis_2(u)$ ，也就是说此时点 $u$ 的代价是 $(s-1)dis_u$ 。

称 $dis_u$ 为点 $u$ 的权，那么显然每个集合中点的权都应该是连续的。我们可以先对要处理的点按权排序，这样我们每次的选择必然都是一个连续的区间。设 $f_{i,j}$ 为当前划分出 $i$ 个区间，考虑到第 $j$ 个点的最小代价，并对排序后的点权做前缀和，记其为 $sm$ ，那么显然：
$$
f_{i,j}=\min_{k\in[i,j]} f_{i-1,k-1}+(j-k)(sm_j-sm_{k-1})
$$
现在直接做是 $O(n^3)$ 的。不妨考虑一些简明的性质，去掉 $\min$ ，并对上式移项：
$$
f_{i,j}-j\times sm_j=(f_{i-1,k-1}+k\times sm_{k-1})-k\times sm_j-j\times sm_{k-1}
$$
鉴于 $k$ 和 $sm_k$ 都具有单调性，对于确定 $i$ 的 $f_{i,j}$ ，转移点显然是单调递增的。并且可以注意到 $f_{i,j}$ 的转移点必然要小于 $f_{i+1,j}$ ，所以我们可以使用决策单调性来做到 $O(n^2)$ 。

但其实这道题的数据范围可以做到更大。既然是要划分出恰好 $s$ 个集合，我们可以通过带权二分来去掉这个限制，此时直接按一开始的式子转移是 $O(n^2\log w)$ 的，$w$ 是斜率的范围。不妨继续使用决策单调性优化，通过单调栈和二分我们就可以以单次 $O(n\log n)$ 的复杂度来完成 DP 的过程，这样我们就可以做到 $O(n\log n\log w)$ 了。

$O(n\log n\log w)$ 的做法并不难实现，而且已经有人放过代码了，所以这里仅仅给出 $O(n^2)$ 的实现：

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define endl putchar('\n')
const int N=5005,M=50005;
const long long inf=0x3f3f3f3f3f3f3f3f;
#define int long long
using namespace std;

int n,m,s,b,ct,head[N],cnt,dis[2][N],vis[N],val[N],sm[N],ans,f[N][N],g[N][N];
struct edge { int a,b,next,v; } e[M],E[M];
void add(int a,int b,int v) {
	e[++cnt]={a,b,head[a],v};
	head[a]=cnt;
}
typedef pair<int,int> pii;
#define fi first
#define se second
priority_queue<pii,vector<pii>,greater<pii> > q;

void dijk(int S,int* dis) {
	rep(i,1,n) dis[i]=inf,vis[i]=0;
	dis[S]=0,q.push({dis[S],S});
	while(!q.empty()) {
		int x=q.top().se; q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=head[x];i;i=e[i].next) {
			if(dis[e[i].b]>dis[x]+e[i].v) {
				dis[e[i].b]=dis[x]+e[i].v;
				q.push({dis[e[i].b],e[i].b});
			}
		}
	}
}

void init() {
	rep(i,1,m) add(E[i].a,E[i].b,E[i].v);
	dijk(ct,dis[1]);
	rep(i,1,n) head[i]=0; cnt=0;
	rep(i,1,m) add(E[i].b,E[i].a,E[i].v);
	dijk(ct,dis[0]);
	rep(i,1,b) val[i]=dis[0][i]+dis[1][i];
	sort(val+1,val+b+1);
	rep(i,1,b) sm[i]=val[i]+sm[i-1];
}

void solve() {
	rep(i,0,b) rep(j,0,b) f[i][j]=inf;
	rep(i,0,b) g[i][i]=i,f[i][i]=0;//count now
	rep(d,1,b-s) {
		rep(i,1,b-d) {
			int j=i+d;
			rep(k,g[i][j-1],g[i+1][j]) {
				int nw=(j-k)*(sm[j]-sm[k-1])+f[i-1][k-1];
				if(f[i][j]>nw) f[i][j]=nw,g[i][j]=k;
			}
		}
	}
	ans=f[s][b];
}

signed main() {
	scanf("%lld%lld%lld%lld",&n,&b,&s,&m),ct=b+1;
	rep(i,1,m) scanf("%lld%lld%lld",&E[i].a,&E[i].b,&E[i].v);
	init();
	solve();
	printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：elonzhang (赞：0)

# [P6918 [ICPC2016 WF] Branch Assignment](https://www.luogu.com.cn/problem/P6918)

## 思路
可以建正图和反图先求出每个部门到总部的最短路和总部到每个部门的最短路，这里可以直接跑正图和反图从总部出发的单源最短路。然后对所有部门的耗费，也就是 $dis(x,b+1)+dis(b+1,x)$ 进行一个排序，然后我们就可以用 dp 来分组。设 $dp_{i,j}$ 为前 $i$ 个人中分成 $j$ 组的最小花费，再枚举一个 $k$ 表示从 $dp_{k,j-1}$ 转移过来，也就是 $[k+1,i)$ 分为一组，其中相比于 $dp_{k,j-1}$ 多出来的花费就是$\sum_{i=k+1}^{n}{(dis(x,b+1)+dis(b+1,x))\times (i-k)}$。

## 优化
仔细算一下上面 $dp$ 的时间复杂度，会发现它一眼都不能多看，所以我们要对其进行一些优化防止爆炸。首先，转移时多出来的贡献可以预处理出一个前缀和数组来优化，式子就变成了 $dp_{i,j}=\min(dp_{i,j},dp_{k,j-1}+(sum_i-sum_k)\times (i-k)$。还有，$k$ 的枚举范围只能在 $[i-\frac{i}{j},i-1]$ 里面，假如从 $1$ 开始枚举就会时间复杂度就会爆炸。~~其实也可以用四边形不等式优化，但本蒟蒻不会。~~

## ACcode
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define endl '\n'
#define inf 0x3f3f3f3f3f3f3f3f
const int N=5001;
int n,b,s,m,mn,sum[N],d1[N],d[N],dp[N][N],val[N];
bool vis[N],vis2[N];
struct road{
	int v,w;
};vector<road> adj[N],jda[N];

void Dij(int s) {
	memset(d, 0x3f, sizeof(d));
	d[s] = 0;
	priority_queue<pair<int,int> , vector<pair<int,int> >, greater<pair<int,int> > > pq;
	pq.push({0, s});
	while (!pq.empty()) {
		pair<int,int>  p = pq.top();
		pq.pop();
		int u = p.second;
//		if (d[u] < p.first) continue;
		if(vis[u]) continue;
		vis[u] = true;
		for (unsigned int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].v, w = adj[u][i].w;
			if (d[u] + w < d[v]) {
				d[v] = d[u] + w;
				pq.push({d[v], v});
			}
		}
	}
}
void Dji(int s) {
	memset(d1,0x3f,sizeof(d1));
	d1[s] = 0;
	priority_queue<pair<int,int> , vector<pair<int,int> >, greater<pair<int,int> > > pq;
	pq.push({0, s});
	while (!pq.empty()) {
		pair<int,int>  p = pq.top();
		pq.pop();
		int u = p.second;
//		if (d1[u] < p.first) continue;
		if(vis2[u]) continue;
		vis2[u] = true;
		for (unsigned int i = 0; i < jda[u].size(); i++) {
			int v = jda[u][i].v, w = jda[u][i].w;
			if (d1[u] + w < d1[v]) {
				d1[v] = d1[u] + w;
				pq.push({d1[v], v});
			}
		}
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
// 	freopen("assignment.in","r",stdin);
// 	freopen("assignment.out","w",stdout);
//↑以上为初始化 ↑
//------------------------------
	cin >> n >> b >> s >> m;
	for(int i = 1;i<=m;i++){
		int u,v,w;
		cin >> u >> v >> w;
		adj[u].push_back({v,w});
		jda[v].push_back({u,w});
	}
	Dij(b + 1);
	Dji(b + 1);
	for(int i = 1;i<=b;i++) {
		val[i]=d[i]+d1[i];
	}
	sort(val+1,val+b+1);
	for(int i = 1;i<=b;i++) sum[i]=sum[i-1]+val[i];
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;
	for(int j = 1;j<=s;j++){
		for(int i = 1;i<=b;i++){
			for(int k = i-i/j;k<i;k++){
				dp[i][j]=min(dp[i][j],dp[k][j-1]+(sum[i]-sum[k])*(i-k));
			}
		}
	}
	cout << dp[b][s]-sum[b] << endl;
	return 0;
}
```

---

## 作者：_shining (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P6918)

## 题意

这题就是让我们求最小的总代价。

## 思路

首先，我们可以很方便地求出总部到每个分部的最短路，再通过将边反向求出每个分部到总部的最短路。

记 $d_i$ 为分部 $i$ 到总部和总部到分部 $i$ 的两条最短路长度之和。

则接下来的任务就是将 $d_1,d_2$ ... $d_b$ 分成 $s$ 组，每组的代价为：$sum_d$  $\times$ ($s_{size}-1$)。

将 $d$ 从小到大排序，显然一定存在一个最优划分方案，其中每组的所有元素都是排完序后连续的一段（可以使用调整法证明）。

考虑动态规划做法，定义 $f_{i,j}$ 表示前 $i$ 个元素被划分成 $j$ 段的最小代价，状态转移方程为 
$$f_{i,j}=\min(f_{k,j-1}+(d_{k+1}+...+d_i)\times(i-k))$$

时间复杂度 $O(n^3)$。但是注意到，在最优解中，$d$ 从小到大依次划分所得到的段的长度一定是单调不增的，则上述 $\texttt{DP}$ 转移中 $k$ 的最优取值一定在 $[i-i/j,i)$ 之间，于是时间复杂度就是$O(n^2(1/1+1/2+1/3+...+1/n)) =O(n^2\log n)$，可以通过本题。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdio>
#include <queue>
#include <cmath>
#define int long long
using namespace std;
int n, b, s, m;
const int N = 5005;
queue<int> q;
bool vis[N];
vector<pair<int, int> > g[N], h[N];
int d[N], d1[N], d2[N], sum[N], f[N][N];
void dijkstra(int x) 
{
	priority_queue<pair<int, int> > q;
	memset(f, 127, sizeof(f));
	memset(d1, 127, sizeof(d1));
	memset(d2, 127, sizeof(d2));
	memset(vis, 0, sizeof(vis));
	d1[x] = 0;
	q.push({0, x});
	while(!q.empty()){
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(int i = 0; i < g[u].size(); i++){
			int v = g[u][i].first, w = g[u][i].second;
			if(d1[u] + w < d1[v]){
				d1[v] = d1[u] + w;
				q.push({-d1[v], v});
			}
		}
	}
	memset(vis, 0, sizeof(vis));
	d2[x] = 0;
	q.push({0, x});
	while(!q.empty()){
		int u = q.top().second;
		q.pop();
		if (vis[u]) continue;
		vis[u] = true;
		for(int i = 0; i < h[u].size(); i++){
			int v = h[u][i].first, w = h[u][i].second;
			if(d2[u] + w < d2[v]){
				d2[v] = d2[u] + w;
				q.push({-d2[v], v});
			}
		}
	}
	for(int i = 1; i <= b; i++) d[i] = d1[i] + d2[i];
}
signed main()
{
	cin >> n >> b >> s >> m;
	for(int i = 1; i <= m; i++){
		int u, v, l;
		cin >> u >> v >> l;
		g[u].push_back({v, l});
		h[v].push_back({u, l});
	}
	dijkstra(b + 1);
	sort(d + 1, d + b + 1);
	f[0][0] = 0;
	for(int i = 1; i <= b; i++) sum[i] = sum[i - 1] + d[i];
	for(int i = 1; i <= s; i++){
		for(int j = i; j <= b; j++){
			for(int k = j - j / i; k < j; k++) f[i][j] = min(f[i][j], f[i - 1][k] + (sum[j] - sum[k]) * (j - k - 1));
		}
	} 		
	cout << f[s][b];
	return 0;
}
```

---

## 作者：homo_snow (赞：0)

# 简单题

先正反图最短路求出每个点到总部和总部到每个点的距离。

假设分部 $i$ 在一个处理同一个子任务的团队 $s$ 里，设总部为 $r$。

则代价为 $cost = \sum^{s}_{i=1}[dist(i,r) \times (s_{size} - 1) + \sum^s_{j=1}dist(r,j) - dist(r,i)]$。

打个草稿就可以看出, 从 $i$ 出发了多少次,也就会从其他地方回来多少次。

所以可以化简得 $cost = (s_{size}-1 )\times \sum^s_{i=1}dist(i,r)+dist(r,i)$。

根据贪心思想,越小的越好, 排序一下就能直接打 dp 了。

设 $f_{i,j}$ 为将前 $i$ 个分成 $j$ 团的最小代价。

得出 $f_{i,j} = min^{i - 1}_{k=0} \{f_{k,j-1} + (i - k - 1) \times \sum^i_{p=k}[dist(p,r)+dist(r,p)]\}$。

对于后面那个求和打个前缀和就能 O(1) 处理。

再打个区间 dp 就能拿到 70 分的好成绩。

### 对于优化

[四边形不等式优化 - OI Wiki (oi-wiki.com)](http://oi-wiki.com/dp/opt/quadrangle/)

发现方程本质符合：

$f_i = min^i_{j=1}f_{j-1} + w(j,i)$

设函数 $w(i,j)$ 为  $(i - j - 1) \times \sum^i_{p=j}[dist(p,r)+dist(r,p)]$。

且对于任意 $i\le j\le k \le p$：

有 $w(i,k)+w(j,p) \le w(i,p) + w(j,k)$。

符合四边形不等式。

套板子优化即可。

还有，卡空间，记得打滚动数组。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6+10;
const int INF = 0x3f3f3f3f;

struct edge{
	int to , val, nxt;
}e1[N<<1],e2[N<<1];

int t, n, b,s,m,edges1,edges2,dis1[N],dis2[N],book[N],last1[N],last2[N],f[N][2],sum[N],opt[N][2];
priority_queue<pair<int,int>> q;

void build1(int x,int y,int z){
	e1[++edges1] = {y,z,last1[x]};
	last1[x] = edges1;
}

void build2(int x,int y,int z){
	e2[++edges2] = {y,z,last2[x]};
	last2[x] = edges2;
}

void dijkstra1(int x){
	memset(dis1,INF,sizeof(dis1));
	memset(book,0,sizeof(book));
	dis1[x] = 0;
	q.push({0,x});
	
	while(q.size()){
		int top = q.top().second;
		q.pop();
		if(book[top]) continue;
		book[top] = 1;
		for(int i = last1[top]; i; i = e1[i].nxt){
			int t = e1[i].to;
			if(dis1[t] > dis1[top] + e1[i].val){
				dis1[t] = dis1[top] + e1[i].val;
				q.push({-dis1[t],t});
			}
		}
	}
}

void dijkstra2(int x){
	memset(dis2,INF,sizeof(dis2));
	memset(book,0,sizeof(book));
	dis2[x] = 0;
	q.push({0,x});
	
	while(q.size()){
		int top = q.top().second;
		q.pop();
		if(book[top]) continue;
		book[top] = 1;
		for(int i = last2[top]; i; i = e2[i].nxt){
			int t = e2[i].to;
			if(dis2[t] > dis2[top] + e2[i].val){
				dis2[t] = dis2[top] + e2[i].val;
				q.push({-dis2[t],t});
			}
		}
	}
}

signed main(){
	freopen("assignment.in","r",stdin);
	freopen("assignment.out","w",stdout);
	scanf("%lld%lld%lld%lld",&n,&b,&s,&m);
	for(int i = 1; i <= m; i++){
		int x , y, z;
		scanf("%lld%lld%lld",&x,&y,&z);
		build1(x,y,z);
		build2(y,x,z);
	}
	dijkstra1(b+1);
	dijkstra2(b+1);
	for(int i = 1; i <= b; i++) dis1[i] += dis2[i];
	sort(dis1+1,dis1+b+1);
	for(int i = 1; i <= b; i++) sum[i] = sum[i-1] + dis1[i];
	memset(f,INF,sizeof(f));
	f[0][0] = 0;
	int flag = 0;
	for(int j = 1; j <= s; j++){
		opt[b+1][j&1] = b;
		for(int i = b; i >= 1; i--){
			for(int k = (!flag ? 0 : opt[i][(j-1)&1]); k <= opt[i+1][j&1] && k < i; k++){
				int val = f[k][(j-1)&1] + (i - k - 1) * (sum[i] - sum[k]);
				if(f[i][j&1] > val){
					f[i][j&1] = val;
					opt[i][j&1] = k; 
				}	
			}
		}
		flag = 1;
	}
	printf("%lld\n",f[b][s&1]);
	return 0;
}
```

---

## 作者：xujingyu (赞：0)

## 题意

将 $s$ 个子项目分配给 $b$ 个分部使得通信代价最小。

## 解法

先求出总部到每个分部的最短路，再通过将边反向求出每个分部到总部的最短路，这里求得很方便。

记 $d_i$ 为分部 $i$ 到总部和总部到分部 $i$ 的两条最短路长度之和。

接下来，将 $d_1,d_2,\dots,d_b$ 分成 $s$ 组，设该组内 $d$ 元素个数为 $num$，每组的代价就为该组内 $\sum d\times(num-1)$，目标是最小化所有组的代价之和。

将 $d$ 从小到大排序，显然一定存在一个最优划分方案，其中每组的所有元素都是排完序后连续的一段（可以使用调整法证明）。

则我们有动态规划做法如下：$f_{i,j}$ 表示前 $i$ 个元素被划分成 $j$ 段的最小代价，转移方程：

$$
f_{i,j}=\min(f_{k,j-1}+\sum\limits_{a=k+1}^i d_a\times(i-k))
$$

直接这样做时间复杂度是 $\mathcal{O(n^3)}$ 的，但是注意到，在最优解中，$d$ 从小到大依次划分所得到的段的长度一定是单调不增的，则上述 DP 转移中 $k$ 的最优取值一定在 $[i-\dfrac{i}{j},i)$ 之间，于是总转移复杂度就是 $O(n^2(\dfrac{1}{1}+\dfrac{1}{2}+\dfrac{1}{3}+\dots+\dfrac{1}{n}))=O(n^2\log n)$（计算过程见[调和级数](https://www.luogu.com.cn/article/7795drge)），足以通过本题。

---

## 作者：elbissoPtImaerD (赞：0)

从 $i$ 到 $j$ 的距离始终是 $dis_{i\to b+1}+dis_{b+1\to j}$，那么对于点对 $(i,j)$ 他们的贡献就是 $dis_{i\to b+1}+dis_{b+1 \to j}+dis_{j \to b+1}+dis_{b+1\to i}$。  
如果我们记 $dist_i=dis_{i\to b+1}+dis_{b+1 \to i}$，则 $(i,j)$ 的贡献就是 $dist_i+dist_j$，他们所在的那一子集 $S_i$ 的贡献就是 $(|S_i|-1)\sum\limits_{x\in S_i}dist_x$。

按照这个式子贪心地划分集合时不难想到要让 $dist$ 值大的 $|S_i|$ 小，$dist$ 值小的 $|S_i|$ 大。  
自然猜到：若将 $dist$ 升序排序，则对于一个集合，他里面的数一定是在 $dist$ 序列中连续的一段。  
事实上这是对的。

那很容易想到一个 DP：记 $f_{i,j}$ 为前 $i$ 个分成 $j$ 组的最小值。  
转移自然就是：$f_{i,j}=\min\limits_{1\le k <i}\{f_{k,j-1}+(i-k-1)\sum\limits_{x=k+1}^idist_x\}$。

直接 DP 复杂度是 $\mathcal{O(n^3)}$。

考虑优化，这个东西很自然地想到四边形不等式，一算发现真是对的。

直接四边形不等式优化一下就是 $\mathcal{O(n^2\ln n)}$ 的了。


$Code:$
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<assert.h>
#define re register
#define il inline
#define int long long
#define ast(x) assert(x)
#define rd(yx) scanf("%lld",&yx)
#define prt(w,t) printf("%lld%c",w,t)
const int N=5e3+3,M=5e4+3;
int n,b,s,m,dist[N],f[N][N],pre[N];
struct wt
{
	int ind=1,hd[N],to[M],nxt[M],val[M],t[N<<2],dis[N];
	il void add(int u,int v,int w){return ++ind,to[ind]=v,nxt[ind]=hd[u],val[ind]=w,hd[u]=ind,void();}
	il int Merge(int x,int y){return dis[x]<dis[y]?x:y;}
	#define ls (o<<1)
	#define rs (o<<1|1)
	#define mid (l+r>>1)
	il void Modify(int o,int l,int r,int x,int y)
	{
		if(l==r) return t[o]=y,void();
		return x>mid?Modify(rs,mid+1,r,x,y):Modify(ls,l,mid,x,y),t[o]=Merge(t[ls],t[rs]),void();
	}
	#undef ls
	#undef rs
	#undef mid
	il void Dijkstra(re int s)
	{
		std::memset(dis,0x3f,sizeof(dis)),dis[s]=0,Modify(1,1,n,s,s);
		for(re int j=1,u;j<n;++j)
		{
			u=t[1],Modify(1,1,n,u,0);
			for(re int i=hd[u],v,w;w=val[i],v=to[i];i=nxt[i])
				dis[u]+w<dis[v]&&(dis[v]=dis[u]+w,Modify(1,1,n,v,v),7);
		}
		return;
	}
}G[2];
void Solve()
{
	rd(n),rd(b),rd(s),rd(m);
	for(re int i=1,u,v,w;i<=m;++i) rd(u),rd(v),rd(w),G[0].add(u,v,w),G[1].add(v,u,w);
	G[0].Dijkstra(b+1),G[1].Dijkstra(b+1),std::memset(f,0x3f,sizeof(f));
	for(re int i=1;i<=b;++i) dist[i]=G[0].dis[i]+G[1].dis[i];
	std::sort(dist+1,dist+b+1);
	for(re int i=1;i<=b;++i) pre[i]=pre[i-1]+dist[i];
	for(re int i=0;i<=s;++i) f[0][i]=0;
	for(re int i=0;i<=b;++i)
		for(re int j=1;j<=s;++j)
			for(re int k=i-i/j;k<i;++k)
				f[i][j]=std::min(f[i][j],f[k][j-1]+(pre[i]-pre[k])*(i-k-1));
	prt(f[b][s],' ');
	return;
}
main()
{
	return Solve(),0;
}
```

---

## 作者：MuYC (赞：0)

抢到第一篇题解哩！

#### 题目分析：

首先我们观察一下，肯定得先正着跑一遍最短路再建反图跑一遍最短路,这样可以对于所有的 $i$ 求出 $dis(b + 1, i)$ 以及 $dis(i, b + 1)$ 。

然后我们继续观察，题目里面有一个条件是： 同一个子集内的点**两两之间**会**互相**发送信息。

于是我们可以知道

**性质一**：
+ **每一个点的贡献**实际上只跟自己所处在的子集的大小有关，跟哪一些元素在一起其实并不重要。假设点 $i$ 所处的集合大小为 $siz$ ,那么它对于答案的贡献就会是 $(dis(i, b + 1) + dis(b + 1, i)) * (siz - 1)$。

下面我们把 $(dis(i, b + 1) + dis(b + 1, i))$ 叫做 $w_i$

**性质二**:
+ 根据性质一，我们可以知道，对于 $w_i$ 相近的一些数我们总是将它们分到一组更优。为什么呢？感性的用贪心来思考这个问题，因为如果它们的 $w_i$ 比较小，我们总是希望它们能够与**相对较多** 的元素在同一个集合，毫无疑问的，相近的一些搭配在一起更好，如果 $w_i$ 比较大也是类似的。

通过性质二的分析，我们将 $[1,b]$ 所有的点按照 $w_i$ 排序。问题就转化为了将一个长度为 $b$ 的 **单调不减序列** 划分成 $s$ 段，每一段的花费为这一段的数的和 * (这一段的长度 $-$ $1$)。

这样的话我们就轻松写出一个 $n^3$ 的 $dp$:

设 $dp[i][j]$ 表示将前 $i$ 个数分成 $j$ 段的最小费用。

那么 $dp[i][j] = Min(dp[k][j - 1] + (sum[i] - sum[k]) * (i - k - 1)); (0 <= k < i)$

这样的话是肯定过不了的。

考虑优化：

首先上面 $dp[i][j]$ 可以通过滚动数组优化为一维，这样子空间复杂度就变成了 O$(n)$。

在做划分第 $j$ 段的时候，~~打表知道~~ 随着 $i$ 往右边移动，对应的最优决策点是不断右移的。

证明：

首先明确一点，我们进行划分的序列是 **单调不减** 的。下面称这个序列为 $A$ 序列，这个序列的第 $i$ 项我们就称之为 $A_i$。

我们假设现在在对 $dp[i]$ 进行决策，$dp[i - 1]$ 的最佳决策点是 $k (0 <= k < i)$。

那么倘若 $dp[i]$ 的最优决策点为 $j$ 并且 $j < k$。

那么意味着 :

$dp[k] + (sum[i] - sum[k]) * (i - k - 1) > dp[j] + (sum[i] - sum[j]) * (i - j - 1)$

但是又同时有：

$dp[k] + (sum[i - 1] - sum[k]) * (i - k - 2) < dp[j] + (sum[i - 1] - sum[j]) * (i - j - 2)$

上下两式作差则有(中间的化简过程就略了，读者可以自行化简，其中重要的一步就是要将 $sum[i]$ 转化为 $sum[i - 1] + A[i]$)：

$(i - k - 2)A_i + sum[i] - sum[k] > (i - j - 2)A_i + sum[i] - sum[j]$

这个式子显然就矛盾了。所以可以知道，无论如何最佳决策点都是 **单调不减** 的。

于是时间复杂度： O($n^2$) , 空间复杂度: O($n$) 就水过去了。

#### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read() {
    int x = 0 , flag = 1;
    char ch = getchar();
    for( ; ch > '9' || ch < '0' ; ch = getchar()) if(ch == '-') flag = -1;
    for( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
    return x * flag;
}
const int MAXN = 5e4 + 50;
int n,r,b,s;
int disA[MAXN], disB[MAXN],start[MAXN],tot = 0,book[MAXN];
int sum[MAXN], dp[MAXN][2];
struct Edge {
    int next, to, w;
} edge[MAXN << 1];

struct Dijk {
    int id, dis;
    bool operator <(const Dijk& A) const {return A.dis < dis;}
} ;

struct Point {
    int val,id;
} P[MAXN];

priority_queue <Dijk> q;

void add(int from, int to, int w) {
    edge[++tot].next = start[from];
    edge[tot].to = to;
    edge[tot].w = w;
    start[from] = tot;
    return ;
}

void Dijkstra(int *dis,int op) {
    memset(book,0,sizeof(book));
    for(int i = 1 ; i <= n ; i ++) dis[i] = 1e9 + 7;
    dis[b + 1] = 0;
    q.push({b + 1, 0});
    while(!q.empty()) {
        int x = q.top().id, d = q.top().dis; q.pop();
        if(dis[x] != d) continue; 
        book[x] = 1;
        for(int i = start[x] ; i ; i = edge[i].next) {
            int to = edge[i].to, w = edge[i].w;
            if(i % 2 == op) continue;
            if(dis[x] + w < dis[to]) {
                dis[to] = dis[x] + w;
                if(!book[to]) q.push({to, dis[to]});
            }
        }
    }
    return ;
}

bool cmp(Point a, Point b) {return a.val < b.val;}
int Q[5005];

signed main() {
    n = read(), b = read(), s = read(), r = read();
    for(int i = 1 ; i <= r ; i ++) {
        int u = read(), v = read(), w = read();
        add(u, v, w); add(v, u, w);
    }
    Dijkstra(disA, 0); Dijkstra(disB, 1);
    for(int i = 1 ; i <= n ; i ++) {
        P[i].val = disA[i] + disB[i];
        P[i].id = i;
    }
    sort(P + 1, P + 1 + b , cmp);
    for(int i = 1 ; i <= b ; i ++) sum[i] = sum[i - 1] + P[i].val;
    int now = 1;
    for(int i = 1 ; i <= b ; i ++) dp[i][1] = sum[i] * (i - 1);
    for(int j = 2 ; j <= s ; j ++) {
        now ^= 1;
        memset(Q, 0, sizeof(Q));
        for(int i = 1 ; i <= b ; i ++) dp[i][now] = 1e18 + 7;
        for(int i = j ; i <= b ; i ++) {
            for(int k = i - 1 ; k >= Q[i - 1] ; k --) {
                if(dp[k][now ^ 1] + (sum[i] - sum[k]) * (i - k - 1) < dp[i][now]) Q[i] = k;
                dp[i][now] = min(dp[i][now], dp[k][now ^ 1] + (sum[i] - sum[k]) * (i - k - 1));
            }
        }
    }
    cout << dp[b][now];
    return 0;
}
```

---

