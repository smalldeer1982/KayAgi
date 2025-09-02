# [USACO08JAN] Telephone Lines S

## 题目描述

多年以后，笨笨长大了，成为了电话线布置师。由于地震使得某市的电话线全部损坏，笨笨是负责接到震中市的负责人。该市周围分布着 $1\le N\le10^3$ 根据 $1\sim N$ 顺序编号的废弃的电话线杆，任意两根线杆之间没有电话线连接，一共有 $1\le p\le10^4$ 对电话杆可以拉电话线。其他的由于地震使得无法连接。

第i对电线杆的两个端点分别是 $a_i,b_i$，它们的距离为 $1\le l_i\le10^6$。数据中每对 $(a_i,b_i)$ 只出现一次。编号为 $1$ 的电话杆已经接入了全国的电话网络，整个市的电话线全都连到了编号 $N$ 的电话线杆上。也就是说，笨笨的任务仅仅是找一条将 $1$ 号和 $N$ 号电线杆连起来的路径，其余的电话杆并不一定要连入电话网络。

电信公司决定支援灾区免费为此市连接 $k$ 对由笨笨指定的电话线杆，对于额外的那些电话线，需要为它们付费，总费用决定于其中最长的电话线的长度（每根电话线仅连接一对电话线杆）。如果需要连接的电话线杆不超过 $k$ 对，那么支出为 $0$。

请你计算一下，将电话线引导震中市最少需要在电话线上花多少钱？

## 样例 #1

### 输入

```
5 7 1
1 2 5
3 1 4
2 4 8
3 2 3
5 2 9
3 4 7
4 5 6
```

### 输出

```
4
```

# 题解

## 作者：浅色调 (赞：72)

###本题的解法：二分答案+spfa###

首先概括一下题意：求原点1到n的所有路中的第k+1长的路最小。

**思考**：为什么可以这样概括呢？因为题意中的答案要最小，我们贪心肯定要使k次免费的资格用完，那么最划算的方案肯定是拿最长的k条路使之免费，然后付第k+1长路的长度的钱。。。这样的贪心思路显然是正确的。

**思路**：我们首先二分第k+1长的路的长度(即答案)，边界值l显然是0、r是1000000(题目中说边最长为1000000)，然后关键是如何判断正确性。我们考虑简化问题，对于长度小于二分出的答案的线段，因为不需要付价钱，所以可以将其权值看作是0;同理，大于二分的值的路径，我们将长度看作1(意味着我需要使用1次免费的资格)。so，我们跑一遍spfa，看到了n点的最短路的长度，如果大于k，则不行，缩小r范围继续二分;如果小于，则有可能更小，缩小l范围继续二分。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
#define ll long long 
#define il inline
struct edge{
int to,next,v;
}e[20005];
int n,p,k,cnt,h[1005],dis[1005],q[1005];
bool pd[1005];
il void add(int u,int v,int w){
    e[++cnt].to=v;
    e[cnt].v=w;
    e[cnt].next=h[u];
    h[u]=cnt;
}
il bool check(int x)
{
         memset(dis,0x3f,sizeof(dis));
    int t=0,w=1,i,now,s;
         dis[1]=0;q[t]=1;pd[1]=1;
    while(t!=w)
     {
        now=q[t];t++;
        if(t==1001)t=0;
        i=h[now];
            while(i){
                if(e[i].v>x)s=dis[now]+1;
                else s=dis[now];
                if(s<dis[e[i].to])
                    {
                        dis[e[i].to]=s;
                        if(!pd[e[i].to])
                            {
                                q[w++]=e[i].to;
                                pd[e[i].to]=1;
                                if(w==1001)w=0;
                            }
                    }
                    i=e[i].next;
                    }
            pd[now]=0; 
        }
     if(dis[n]<=k)return 1;
     return 0;
 }
int main()
{
    //freopen("phoneline.in","r",stdin);
    //freopen("phoneline.out","w",stdout);
    scanf("%d%d%d",&n,&p,&k);
    int u,v,w,l=0,r=1000000,mid;
    for(int i=1;i<=p;i++){
            scanf("%d%d%d",&u,&v,&w);
            add(u,v,w);
            add(v,u,w);
    }
    int ans=-1;
    while(l<=r){
                   mid=(l+r)>>1;
            if(check(mid)){r=mid-1;ans=mid;}
            else l=mid+1;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Blair3863 (赞：46)

# 本题作法 ： 二分答案+双端队列bfs

## 前序知识点：图的储存与遍历，二分答案，bfs求最短路
在做这道题之前，可以看一下 [p2243](https://www.luogu.org/problemnew/show/P2243) 电路维修，注意到转化为一个边权只为 _0_ 或 _1_ 的无向图。

因此，我们可以二分最大的花费x，x属于[l,r],(l为最小花费，r为最大花费)， x然后将大于x的边看做权值为1的边，将小于等于x的边看做权值为零的边，然后找到从点1到点n的最短路，若最短路的长度大于k，则要连接的对数大于k对，在[x+1,r]中继续二份查找；若最短路的长度小于k，则要连接的对数比k小，在[l,x]中继续二份查找，最终，l即为所求。

贴上ac代码
```cpp
#include <iostream>
#include <algorithm>
#include <deque>
#include <cstring>

using namespace std;

int vis[10008];
int d[10008];
int head[10008], edge[100008], ver[100008], next[100008];
int tot;
int n, p, k, maxx = 0;
void add(int x, int y, int z) //邻接表建图，注意无向
{
	ver[++tot] = y;
	edge[tot] = z;
	next[tot] = head[x];
	head[x] = tot;
	ver[++tot] = x;
	edge[tot] = z;
	next[tot] = head[y];
	head[y] = tot;
}
int check(int x) //二分检测
{
//	cout<<x<<":";
	//双端bfs，参考p2243
	memset(d,0,sizeof(d));
	memset(vis,0,sizeof(vis));
	deque<int> q;
	q.push_back(1);
	d[1] = 0;
	vis[1] = 1;
	while(q.size())
	{
		int a = q.front();
		q.pop_front();
		for(int i = head[a]; i; i = next[i])
		{
			int y = ver[i];
			if(!vis[y] || d[y] >= d[a] + 1)
			if(edge[i] <= x)
			{
				vis[y] = 1;
				q.push_front(y);
				d[y] = d[a];
			//	cout<<"d"<<y<<"="<<d[a]<<endl;
			}
			else 
			{
				vis[y] = 1;
				q.push_back(y);
				d[y] = d[a] + 1; 
			//	cout<<"d"<<y<<"="<<d[a]+1<<endl;
			}
		}
	}
	//cout<<d[n]<<endl;
	if(d[n] > k)
	return 0;
	else
	return 1;
}
int main()
{
	cin>>n>>p>>k;
	for(int i = 0; i < p; i++)
	{
		int x, y, z;
		cin>>x>>y>>z;
		add(x, y, z);
		maxx = max(maxx, z);
	} 
//	cout<<maxx<<endl;
	int l = 1, r = maxx;
	while(l < r)
	{
		int mid = (l + r) / 2;
		if(check(mid))
		r  = mid;
		else
		l = mid + 1;
	 } 
	 if(l!=1) 
	 cout<<l;
	 else
	 cout<<"-1";
	return 0;
}
```
注意几点：

1. 最后答案需特判，若不满足，输出-1；
1. 请注意这一行
```cpp
if(!vis[y] || d[y] >= d[a] + 1)
```
可结合样例的图示，尝试理解；![](https://cdn.luogu.com.cn/upload/pic/39954.png)

---

## 作者：ViXpop (赞：34)

#### 虽然这题题解已经有不少了，但是蒟蒻还是想来一发题解qwq

看了看各路神仙的题解，发现大部分都是spfa+二分的答案

但是本蒟蒻看完题目的第一反应就是

## 这不就是个分层图最短路吗

#### 直接建图开冲

测一波样例...... 输出5？？？

原来是没看题的锅，题目给出的计算规则是只花费路线中最长的一条路的价钱，而不是将所有路径长度相加求出k次免费的总的最短路

那只需要把代码改一下就好了

但是蒟蒻本来就不是很会分层图，卡了半天总是出0......

无奈之下只能换dijkstra+dp切了这题

当然还用了堆优化，总的来说这题还是~~很水的~~，就是代码比较难以实现（个人观点）

### 代码还是最直观的，各位神仙可以结合代码进行理解

```
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;

const int N=100050,M=10005,inf=(1<<30);
int cnt,to[N],nxt[N],w[N],n,T,head[N],m,flag[M][21],d[M][21];
int read()
{
    int res=0,kkk=1;char ch=' ';
    while(ch<'0'||ch>'9'){
        ch=getchar();
        if(ch=='-')kkk=-1;
    }
    while(ch>='0'&&ch<='9'){
        res=res*10+ch-'0';
        ch=getchar();
    }
    return res*kkk;
}
struct node{
    int x,d,num;
    friend bool operator < (node p, node q){
        return p.d > q.d;
    }
};
void addedge(int x,int y,int dis)
{
    to[++cnt]=y;
    w[cnt]=dis;
    nxt[cnt]=head[x];
    head[x]=cnt;
}
void add(int x,int y,int z)
{
    addedge(x,y,z);
    addedge(y,x,z);
}
priority_queue <node> q;
void dijkstra()
{
    for(int i=1;i<=n;i++){
        for(int j=0;j<=T;j++)
            d[i][j]=inf;
    }
    d[1][0]=0;
    q.push(node{1,0,0});
    while(!q.empty()){
        node k=q.top();
        q.pop();
        int x=k.x,num=k.num;
        if(flag[x][num])continue;
        flag[x][num]=1;
        for(register int i=head[x];i;i=nxt[i])
        {
            int kk=to[i];
            if(d[kk][num]>max(d[x][num],w[i])){
                d[kk][num]=max(d[x][num],w[i]);
                if(!flag[kk][num])q.push(node{kk,d[kk][num],num});
                }
                if(num<T&&d[kk][num+1]>d[x][num]){
                    d[kk][num+1]=d[x][num];
                    if(!flag[kk][num+1])q.push(node{kk,d[kk][num+1],num+1});
                }
        }
    }
}
int main()
{
    n=read(),m=read(),T=read();
    for(register int i=1;i<=m;i++){
        int l,r,dis;
        l=read(),r=read(),dis=read();
        add(l,r,dis);
    }
    dijkstra();
    if(d[n][T]!=inf)
        printf("%d\n",d[n][T]);
    else printf("-1\n");
    return 0;
}
```
### 下面再提供一份分层图最短路的代码

```
#include <bits/stdc++.h>

using namespace std;

const int N=100050;
int to[N],w[N],n,K,m,cnt,nxt[N],head[N],d[N],vis[N],s,t;
int read(){
    int res=0,kkk=1;char ch=' ';
    while(!isdigit(ch)){ch=getchar();if(ch=='-')kkk=-1;}
    while(isdigit(ch)){res=res*10+ch-'0';ch=getchar();}
    return res*kkk;
}
void qxx(int x,int y,int dis){
    to[++cnt]=y;
    w[cnt]=dis;
    nxt[cnt]=head[x];
    head[x]=cnt;
}
void add(int x,int y,int z){
    qxx(x,y,z),qxx(y,x,z);
}
struct node{
    int x,d;
    friend bool operator<(node x,node y){
        return x.d>y.d;
    }
};
priority_queue<node>q;
void dijkstra(){
    memset(d,63,sizeof(d));
    q.push(node{s,0});
    d[s]=0;
    while(!q.empty()){
        int k=q.top().x;
        q.pop();
        if(vis[k])continue;
        vis[k]=1;
        for(register int i=head[k];i;i=nxt[i]){
            int kk=to[i];
            if(d[kk]>max(d[k],w[i]))
            {
                d[kk]=max(d[k],w[i]);
                if(!vis[kk]){
                    q.push(node{kk,d[kk]});
                }
            }
        }
    }
}
int main()
{
    n=read(),m=read(),K=read();
    s=1,t=n;
    for(register int i=1;i<=m;i++){
        int l=read(),r=read(),q=read();
        add(l,r,q);
        for(register int j=1;j<=K;j++){
            add(j*n+l,j*n+r,q);
            qxx((j-1)*n+l,j*n+r,0);
            qxx((j-1)*n+r,j*n+l,0);
        }
    }
    dijkstra();
    if(d[K*n+t]!=1061109567)//初始化的值若没有改变就说明无解
        printf("%d\n",d[K*n+t]);
    else printf("-1\n");
    return 0;
}
```

如果有需要的话，可以看看[这里](https://pzhpzhpzh.github.io/2019/03/01/%E6%9C%80%E7%9F%AD%E8%B7%AF/#more)，讲解的还是很赞的ovo

~~虽然最后有神仙告诉蒟蒻二分+spfa就是分层图，但是我还是要发题解qaq~~

---

## 作者：hf_xz (赞：30)

考虑用$f[i][j]$表示**从1到点i，用了j条免费线**的最小花费。


这样的状态空间是1000\*1000的，可以存下来。


对于一条边e，u->v，我们有如下转移


​    不用免费线:$f[v][k] = min(f[v][k],max(f[u][k],len[e]))$


​    用免费线:$f[v][k+1]=min(f[v][k+1],f[u][k])$


考虑给的不是一个DAG图，没有一个确定的顺序来dp，所以我们用spfa来转移这些状态。把每一个状态想成一个点，按上面的转移来连边，然后跑最短路就求出了每个状态的最小值。当然我们实际在做的时候不用真的建出这样1e6个点的图，只需要松弛的时候分类就行了，具体看代码。


```cpp
/*
###########################################################################
#                                Code by :                                #
#  /$$              /$$$$$$                                               #
# | $$             /$$__  $$                                              #
# | $$$$$$$       | $$  \__/                    /$$   /$$       /$$$$$$$$ #
# | $$__  $$      | $$$$                       |  $$ /$$/      |____ /$$/ #
# | $$  \ $$      | $$_/                        \  $$$$/          /$$$$/  #
# | $$  | $$      | $$                           >$$  $$         /$$__/   #
# | $$  | $$      | $$                          /$$/\  $$       /$$$$$$$$ #
# |__/  |__/      |__/            /$$$$$$      |__/  \__/      |________/ #
#                                |______/                                 #
###########################################################################
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>
#include<cmath>
#include<set>
using namespace std;

const int maxn = 1005, maxm = 20005;
int n,p,k;
int h[maxn],nxt[maxm],to[maxm],len[maxm],tot;
int dis[maxn][maxn];
bool vis[maxn][maxn];
struct Node{
    int u,k;//存当前点和用过的免费线
    Node(int x,int y){
        u = x; k = y;
    }
    void operator=(const Node b){
        u = b.u; k = b.k;
    }
    void is(int x,int y){
        u = x; k = y;
    }
};

inline void spfa(){
    memset(dis,0x2f,sizeof(dis));
    queue<Node> q;
    Node a(1,0);//边界条件，f[1][0] = 0
    q.push(a); vis[1][0] = 1; dis[1][0] = 0;
    while(!q.empty()){
        a = q.front(); q.pop();
        int u =a.u, uk = a.k; //取出当前点和当前用了的免费线数量
        vis[u][uk] = 0;
        for(int i=h[u],v;i;i=nxt[i]){
            v = to[i];
            //不用免费线
            if(max(dis[u][uk],len[i]) < dis[v][uk]){
                dis[v][uk] = max(dis[u][uk],len[i]);
                if(!vis[v][uk]){
                    a.is(v,uk);
                    q.push(a); vis[v][uk] = 1;
                }
            }
            //用免费线
            if(uk < k && dis[u][uk] < dis[v][uk+1]){
                dis[v][uk+1] = dis[u][uk];
                if(!vis[v][uk+1]){
                    a.is(v,uk+1);
                    q.push(a); vis[v][uk+1] = 1;
                }
            }
        }
    }
}

int main(){
    cin>>n>>p>>k;
    for(int i=1;i<=p;i++){
        int u,v,w; cin>>u>>v>>w;
        to[++tot] = v; nxt[tot] = h[u]; len[tot] = w; h[u] = tot;
        to[++tot] = u; nxt[tot] = h[v]; len[tot] = w; h[v] = tot;
    }
    spfa();
    //判断无解 791621423是开始赋的INF
    if(dis[n][k] == 791621423) cout<<-1<<endl;
    else cout<<dis[n][k]<<endl;
    return 0;
}
```

其实楼下有一篇bfs，就是没有判断重复进队的spfa。


~~p.s. 其实平时这种带环的dp，范围比较小的话都可以信仰spfa~~


---

## 作者：狸狸养的敏敏 (赞：29)

**Tips：看到这样的字眼，你就要想起二分**  
>最大……里的最小……

 or
 
>最小……里的最大……

那么这题显然是一个最短路问题，区别于别的最短路，本题可以有$K$条免费线路  
第一个想到的当然是~~枚举~\(≧▽≦)/~啦啦啦~~  

然后就$TLE$了QAQ  

这道题目显然要用二分去做，那么，二分什么呢？当然是二分答案，本题有一个很~~和谐的~~友好的字眼：答案是**最**长的长度。  

至于思路如下：首先二分答案，将所有线中大于答案的标记为$1$（需要使用一次免费机会）,不大于答案的标记为0（不需要使用免费机会）,有人说，这题不能用**Dijkstra**？当然不行，为什么呢？因为迪杰斯特拉~~算法效率低下~~他无法对0边权进行处理，极有可能死循环，而SPFA的原理是：更新后不低于当前长度就**不进队列**，可以有效的处理0的问题。

代码如下
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
inline int read() {//快读
    int X=0,w=0;
    char ch=0;
    while(!isdigit(ch)) {
        w|=ch=='-';
        ch=getchar();
    }
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline double dbread() {//小数快读
    double X=0,Y=1.0;
    int w=0;
    char ch=0;
    while(!isdigit(ch)) {
        w|=ch=='-';
        ch=getchar();
    }
    while(isdigit(ch)) X=X*10+(ch^48),ch=getchar();
    ch=getchar();
    while(isdigit(ch)) X+=(Y/=10)*(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x) {//快些
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
```

# 至此为止，上面都是我的模板AwA

```cpp
struct node {//程序核心
    int to,next,val;
} e[20005];//前向星
int tot=0,head[1005],dis[1005],n,k,p,ans=-1;
bool vis[1005];
queue<int> q;//SPFA队列
void add(int u,int v,int w) {//建边(前向星)
    e[++tot]=(node) {
        v,head[u],w
    };
    head[u]=tot;
}
bool spfa(int x) {//SPFA(judge函数)
    memset(dis,42,sizeof(dis));//初始化,因为有多次judge
    memset(vis,0,sizeof(vis));//初始化,因为有多次judge
    dis[1]=0;
    q.push(1);
    vis[1]=true;
    int s;
    while(!q.empty()) {//SPFA（STL队列实现）
        int now=q.front();
        q.pop();
        for(int i=head[now]; i; i=e[i].next) {
            if(e[i].val>x)s=dis[now]+1;//如果大于当前二分出来的答案（如上所述）
            else s=dis[now];
            if(s<dis[e[i].to]) {
                dis[e[i].to]=s;
                if(!vis[e[i].to])q.push(e[i].to),vis[e[i].to]=true;
            }
        }
        vis[now]=0;
    }
    if(dis[n]<=k)return 1;//如果需要免费的边在范围之内，说明这种答案是可行的,寻找更小的答案
    return 0;
}
int main() {
    n=read();//读入
    p=read();//读入
    k=read();//还是读入
    for(int i=1; i<=p; i++) {//建边
        int u,v,w;
        u=read();
        v=read();
        w=read();
        add(u,v,w);//因为是无向图，所以要建来去两边
        add(v,u,w);
    }
    int l=0,r=1000000;
    //二分,我这里直接从最大距离开始查找，你们也可以从输入的数据中找最大值（可能会比我这个快一点）
    while(l<=r) {//二分
        int mid=(l+r)>>1;
        if(spfa(mid)) {
            ans=mid;//保存下当前答案，就可以放心的去找更小的了
            r=mid-1;
        } else l=mid+1;
    }
    write(ans);//输出
    return 0;//这可是个好习惯
}
```

关于二分，有很多写法，我个人喜欢这种写法，找到答案之后保存下来，有一些写法是输出R或L的，这个就要看个人喜好了


手打挺辛苦，不如让我过？

---

## 作者：jins3599 (赞：14)

比较套路的一道题。

首先可以想到是要二分这个费用，然后我们思考如何`check`他合不合法。

一个比较妙的思路就是，我们把整个图上所有大于`mid`的边赋为`0`，所有小于等于`mid`的边赋值为`1`，这样的话只需要跑一边$bfs$，然后看到终点的距离是否小于等于$k$即可.

时间复杂度$O(NlogN)$

$Code:$

```cpp
#include <bits/stdc++.h>

using namespace std;

int n , p , k, ans=-1;
int l = 1, r;

const int N = 1e4 + 10;

struct Edge {
	int to , nxt , w;
}e[N << 1];

int head[N] , cnt;
void add(int u , int v  ,int w) {
	e[++ cnt].to = v;
	e[cnt].w = w;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}

bool inq[N];
int dis[N];
bool check(int x) {
	queue <int> q;
	q.push(1);
	for(int i = 2 ; i <= n ; ++ i) dis[i] = 0x3f3f3f3f;
	inq[1] = 1; dis[1] = 0;
	while(!q.empty()) {
		int now = q.front(); q.pop();
		inq[now] = 0;
		for(int i = head[now] ; i ; i = e[i].nxt) {
			int v = e[i].to , w = e[i].w;
			if(w <= x) w = 0; 
			else w = 1;
			if(dis[v] > dis[now] + w) {
				dis[v] = dis[now] + w;
				if(!inq[v]) inq[v] = 1 , q.push(v); 
			}
		}
	}
	return dis[n] <= k;
} 

int main () {
	scanf("%d %d %d" , &n , &p , &k);
	for(int i = 1 ;  i <= p ; ++ i) {
		int u , v , w;
		scanf("%d %d %d" , &u , &v, &w);
		add(u , v , w); add(v  , u , w); 
		r += w;
	}
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(mid)) ans = mid , r = mid - 1;
		else l = mid + 1; 
	}
	printf("%d\n" , ans);
	return 0;
}

```

---

## 作者：利刃随人 (赞：12)

## 自认为很清奇的思路
### %你赛用了30min憋出来的思路，较好理解，适用于初学者，跑的有点慢。
#### 总思路: 最短路+二分 (Dijkstra堆优化)最短路
#### 思路描述
仔细理解了一下题意，是让求一个最大的最小，那么很显然具有单调性，二分答案是没跑了。众所周知，二分答案的难点在于check函数，那么怎么检验一个答案是否合法呢？

提取一下题意，就知道只要至少有一条路径中边的边权大于所二分的答案的条数≤k就合法。

~~其实我一开始想的是DFS,写挂了才想出这个思路~~

然后怎么实现呢？首先考虑最短路，思考能不能用最短路维护出一条路径中边的边权大于所二分的答案的条数。仔细想一下是可以的。具体实现步骤如下：

首先我们将所有边权都减去你二分到的答案（下图以样例为例，二分到的答案为4）：

![](https://cdn.luogu.com.cn/upload/image_hosting/ayspcift.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

那么这有什么用呢？很显然，图中所有权值≤0的边权都是小于所枚举到的答案的，所以只有＞0的权值对答案有贡献。我们重新定义一个权值，此权值＞0的所有边的新边权为1，≤0的则为0，由于只要有一条路径满足条件即可，所以只要跑最短路就可以了。

新权值图：

![](https://cdn.luogu.com.cn/upload/image_hosting/45j4yr74.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

跑出最短路的值和k相比较，如果≤k就返回true，否则返回false。这道题就做完了。

AC代码如下:
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define inf 0x7fffffff
const int maxn=1e3+1;
const int maxp=1e4+1;
using namespace std;
struct jg{
	int dis,jd;
	bool operator < (const jg &a) const{
		return a.dis<dis;
	}
};
struct Edge{
	int next,to,worth,gx;
}e[maxp*2];
int head[maxn],cnt,ans=inf,dis[maxn];
int ma,mi=inf;
int n,p,k;
bool vis[maxn];
void add(int from,int to,int worth)
{
	e[++cnt].next=head[from];
	e[cnt].to=to;
	e[cnt].worth=worth;
	head[from]=cnt;
}
void dijkstra()
{
	priority_queue<jg> q;
	for(int i=1;i<=n;i++) dis[i]=inf;
	dis[1]=0;
	q.push((jg){0,1});
	while(!q.empty())
	{
		jg now=q.top();
		q.pop();
		if(vis[now.jd]) continue;
		vis[now.jd]=true;
		for(int i=head[now.jd];i;i=e[i].next)
			if(dis[e[i].to]>dis[now.jd]+e[i].gx)
			{
				dis[e[i].to]=dis[now.jd]+e[i].gx;
				q.push((jg){dis[e[i].to],e[i].to});
			}
	}
}
bool check(int in)
{
	memset(vis,0,n+1);
	for(int i=1;i<=cnt;i++)
	{
		e[i].worth-=in;	
		if(e[i].worth>0) e[i].gx=1;
		else e[i].gx=0;	
	}
	dijkstra();
	for(int i=1;i<=cnt;i++)
		e[i].worth+=in;
	if(dis[n]<=k) return true;
	else return false;
}
int mian()
{
//	freopen("line.in","r",stdin);
//	freopen("line.out","w",stdout);
	scanf("%d%d%d",&n,&p,&k);
	for(int i=1;i<=p;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
		ma=max(z,ma);
		mi=min(z,mi);
	}
	int l=mi-1,r=ma+1,mid;
	while(l<=r)
	{
		mid=(l+r)>>1; 
		if(check(mid))
		{
		r=mid-1;
		ans=min(ans,mid);			
		}
		else
		l=mid+1;
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：BinDir0 (赞：11)

## 二分+dij题目

**首先读一遍题目，一定要仔细读（不要问我为什么，我就是受害者qwq**

你会发现最终的费用是由最长的电话线决定的，而非电话线长度和。

至此就有了一个基本思路——枚举（二分）出可能的最长电话线长度，然后对其进行dij判断。

dij思路如下：

1.已知枚举出了假定答案ans；

2.在最短路过程中，判断有多少条线长度大于ans，并将其免费；

3.最后判断免费条数，若大于给出的t即不可行，反之可行。

## ~~开long long！！！~~

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ca,k,ma,ans,cnt,n,m,vis[2050],a,b,dis[2050],nex[20500],fst[2050],v[20500],w[20500],f[2050],sum[2050],ww;
int dj(long long ans)
{
    memset(dis,0x7f/3,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[1]=0;
    long long minn,t=0;
   	for(register long long i=1;i<=n;i++) 
    {
       	minn=1e12;
       	for(long long j=1;j<=n;j++)
       	{
            if(!vis[j]&&dis[j]<minn)
       		{
        	   	minn=dis[j];
        	   	t=j;
        	}	
       	}
       	vis[t]=1;
       	for(register long long j=fst[t];j;j=nex[j])
       	{
       		if(w[j]>ans)
       		dis[v[j]]=min(dis[v[j]],dis[t]+1);
       		else
       		dis[v[j]]=min(dis[v[j]],dis[t]);
       	}
   	}
   	if(dis[n]>1e8)
   	{
   		cout<<-1;
   		return 2;
   	}
    if(dis[n]>k)
    return 0;
    return 1;
}
void binary(long long l,long long r)
{
    if(l>r)
    {
        cout<<ans;
        return ;
    }
    long long mid=(l+r)>>1;
    int dij=dj(mid);
    if(dij==2)
        return;
    if(dij==1)
    {
        ans=mid;
        binary(l,mid-1);
    }
    else
        binary(mid+1,r);
    return ;
}
int main()
{
    scanf("%lld%lld%lld",&n,&m,&k);
    for(long long i=1;i<=m;i++)
    {
        scanf("%lld%lld%lld",&a,&b,&ww);
        ma+=ww;
        nex[++cnt]=fst[a];
        fst[a]=cnt;
        v[cnt]=b;
        w[cnt]=ww;
        nex[++cnt]=fst[b];
        fst[b]=cnt;
        v[cnt]=a;
        w[cnt]=ww;
    }
    binary(0,ma);
    return 0;
} 

```


---

## 作者：controlf2 (赞：11)

在题解栏看到各位dalao都用二分潇洒地秒过，我弱弱的写了一个BFS，期望得分50，没想到A掉了。

思路很简单，用一个状态{now,nowk,nowdis}来记录每个节点的请况：走到了哪那个节点，用掉了多少个免费线，当前花费是几

然后从每个节点，向与它相连的节点扩展免费和不免费两种请况，

但是这样很可能不是TLE就是RE，所以说我们要加上剪枝（BFS的剪枝好神奇的说），

用数组mink[i][j]表示走到i节点，用了j根免费线，花费的最小值是多少，

如果扩展的新状态还不如mink[i][j]中已经储存的状态优，那就没必要扩展了。

这样时间就控制在了可以接受的范围之内。

队列最好是循环，否则我也不知道会不会炸掉。

最后，在mink[n][0~k]之中取最小值就是结果了。

附代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std; 
struct edge{
    int to;int dis;int next;
};
struct node{
    int now;int nowk;int nowdis;
};
node q[1000000+666];
edge e[10000*3+666];
int h[1000+666];
int p,hh,tt;
int n,m,k;
int mink[1005][1005];//到达i点，使用j个免费线，其中花费最小值。
inline int ra()
{
    int x=0;char ch=getchar();int flag=1;
    while(ch>'9'||ch<'0'){if(ch=='-')flag=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x*=10;x+=ch-'0';ch=getchar();}
    return x*flag;
 } 
void add(int a,int b,int c)
{
     p++;
    e[p].next=h[a];
    e[p].to=b;
     e[p].dis=c;
     h[a]=p;
     return ;
}
inline void in(int now,int k,int dis)
{
     q[tt].now=now;
     q[tt].nowk=k;
     q[tt].nowdis=dis;
     tt++;
    if(tt==1000000+666)tt=0;
    return;
}
void bfs()
{
    while(hh!=tt)
    {
        int now,nowk,nowdis;
        now=q[hh].now;nowk=q[hh].nowk;nowdis=q[hh].nowdis;
        hh++;
        if(hh==1000000+666)hh=0;
        for(int i=h[now];i;i=e[i].next)
        {
            int to=e[i].to;
            if(max(nowdis,e[i].dis)<mink[to][nowk])
            {
                mink[to][nowk]=max(nowdis,e[i].dis);
                in(to,nowk,max(nowdis,e[i].dis));
            }
            if(nowdis<mink[to][nowk+1]&&nowk<k)
            {
                mink[to][nowk+1]=nowdis;
                in(to,nowk+1,nowdis);
            }
        }
    }
}
int main()
{
    n=ra();m=ra();k=ra();
    for(int i=1;i<=m;i++)
    {
        int a,b,c;
        a=ra();b=ra();c=ra();
        add(a,b,c);
        add(b,a,c);
    }
    in(1,0,0);
    memset(mink,0x3f,sizeof(mink));
    for(int i=0;i<=k;i++)mink[1][i]=0;
    bfs();
    int ans=0x7fffffff;
    for(int i=0;i<=k;i++)
    ans=min(ans,mink[n][i]);
    //cout<<ans<<endl;
    if(ans==0x3f3f3f3f)cout<<"-1"<<endl;
    else cout<<ans<<endl;
    return 0;
}
```
//有点丑



---

## 作者：Mark_ZZY (赞：10)

```cpp
/*
在下面的题解中看不到这种做法,那就来发一波题解.
首先,看到题目,自然想到二分,那么怎么分呢?
1.二分长度mid;
2.构图将>mid的长度设为1,<=mid的长度设为0;
3.跑一遍spfa,算出dis数组(dis[i]表示从起点1到i点所经过的边>mid的数量); 
4.如果dis[n]<=k,即说明"免费"的边数符合题目要求,这时,mid可以作为一个答案.
*/
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define I inline
#define R register
using namespace std;
queue<int> f;
	int n,m,k,len,ans=-1;
	int last[100000],dis[100000];
	struct node1{int x,y,z;} p[100000];
	struct node2{int x,y,z,next;} a[100000];
	bool bz[100000];
I int readint()
{
	int x=0,f=1;
	char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())
		if(ch=='-') f=-1;
	for(;ch>='0'&&ch<='9';x=(x<<3)+(x<<1)+(ch^48),ch=getchar());
	return x*f;
}
I void ins(int x,int y,int z)
{
	a[++len].x=x;a[len].y=y;a[len].z=z;a[len].next=last[x];last[x]=len;
}
I void init(int x)//构图 
{
	len=0;
	memset(last,0,sizeof(last));
	for(R int i=1;i<=m;i++)
	{
		ins(p[i].x,p[i].y,p[i].z>x);
		ins(p[i].y,p[i].x,p[i].z>x);
	}
}
I int spfa()//spfa 
{
	memset(dis,63,sizeof(dis));
	dis[1]=0;
	memset(bz,true,sizeof(bz));
	bz[1]=false;
	f.push(1);
	while(!f.empty())
	{
		int x=f.front();
		for(R int i=last[x];i;i=a[i].next)
		{
			int y=a[i].y;
			if(dis[x]+a[i].z<dis[y])
			{
				dis[y]=dis[x]+a[i].z;
				if(bz[y])
				{
					bz[y]=false;
					f.push(y);
				}
			}
		}
		bz[x]=true;
		f.pop();
	}
	return dis[n];
}
I bool pd(int x)
{
	init(x);
	return spfa()<=k;
}
int main()
{
	int l=0,r=0,mid;
	n=readint();m=readint();k=readint();
	for(R int i=1;i<=m;i++)
	{
		p[i].x=readint();p[i].y=readint();p[i].z=readint();
		r=max(r,p[i].z);
	}
	while(l<=r)//二分长度
	{
		mid=(l+r)>>1;
		if(pd(mid))
		{
			r=mid-1;
			ans=mid;
			if(!ans) break;
		}
		else l=mid+1;
	}
	printf("%d",ans);
}
```

---

## 作者：youngk (赞：8)

这里绝大多数题解都是二分答案的方法，其实可以用分成图做，并且效率会比二分高的多,稍微介绍一下分层图的原理。

既然有k条路可以免费，呢么将整个图分成k+1层，每一层都复制一遍原本的图，同时每一题路都构造一个从下一层通向上一层的路，但价格为0的路，这表示选择走这题路是将免费的机会用在这题路上。并且从下层通往上层，所以最多这种免费的路只能走k次，满足题意。

当然还有要注意的是可以不使用这个免费的机会，所以建立从每一层的 i 顶点通往上一层的 i 顶点的价格为0的路，但貌似洛谷并没有卡这种情况(如果k的值大于m应该是可以卡住的)

最后再将dijkstra魔改一下，因为这里要求的答案不是最短路径，而是路径上的最大路的最小值，所以把原本的是否dis[v] > dis[u] + val[i]，改成是否dis[v] > max(dis[u], val[i])，这里表示的是求得路径上使最大路的值最小。判断是否1与n联通也可以直接判断最后dis[(k+1)*n] 是否等于inf。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<set>
#define _USE_MATH_DEFINES
#include<math.h>
#include<queue>
#include<vector>
#include<limits.h>
#include<functional>
#include<stack>
typedef long long ll;
#pragma GCC optimize(2)
using namespace std;
inline void write(int x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
#define maxm 200010
#define maxn 10010
int n, m, cnt = 1, s, t, maxflow, cost;
int head[maxn], to[maxm], Next[maxm], val[maxm], dis[maxn];
bool vis[maxn];
void add(int u, int v, int w)
{
	to[++cnt] = v;
	val[cnt] = w;
	Next[cnt] = head[u];
	head[u] = cnt;
}
struct node
{
	int x, w;
	inline bool operator <(const node& a) const
	{
		return w > a.w;
	}
};
void dijkstra()
{
	priority_queue<node> q;
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	dis[s] = 0;
	q.push({ s,0 });
	while (q.size())
	{
		int u = q.top().x;
		q.pop();
		if (vis[u])
			continue;
		vis[u] = true;
		for (int i = head[u]; i; i = Next[i])
		{
			int v = to[i];
			if (dis[v] > max(dis[u], val[i]))
			{
				dis[v] = max(dis[u], val[i]);
				q.push({ v,dis[v] });
			}
		}
	}
}
signed main()
{
	n = read(), m = read();
	int k = read();
	s = 1;
	while (m--)
	{
		int x = read(), y = read(), z = read();
		add(x, y, z);
		add(y, x, z);
		for (int i = 1; i <= k; i++)
		{
			add(i * n + x, i * n + y, z);
			add(i * n + y, i * n + x, z);
			add((i - 1) * n + x, i * n + y, 0);
			add((i - 1) * n + y, i * n + x, 0);
		}
	}
    for (int i = 1; i <= n; i++)
		for (int j = 1; j <= k; j++)
			add((j - 1) * n + i, j * n + i, 0);
	
	dijkstra();
	if (dis[(k + 1) * n] != 0x3f3f3f3f)
		write(dis[(k + 1) * n]);
	else
		puts("-1");
	return 0;
}
```


---

## 作者：_LPF_ (赞：6)

# 前言+闲聊

好像是一道比较简单的最短路题目，其实这个思路题解里面好像有一片一样的。

但是我个人认为那位同学的代码是有问题的，他/她的判断无解的方法好像是 ~~面向数据编程~~

如果是我理解错了当我没说，但是我认为我的代码更加容易理解吧。（逃...

# 题意描述

在无向图中求一条从 $1$ 到 $N$ 的路径，使得路径上第 $K+1$ 大的边权最小。

等等，最大的最小...如此熟悉的字眼，难道是 **二分答案**。

下面进入正题。

# 算法分析

没错就是酱紫，二分这个第 $K+1$ 大的边权的值，设这条边的边权为 $val$ 那么：

$$edge[i]=
\begin{cases}
0& \text{edge[i] <= val}\\
1& \text{edge[i] > val}
\end{cases}$$

然后就跑一遍最短路（01 图的最短路可以用双端队列优化来跑，不懂的话自行百度吧，很简单的）。

$$find=
\begin{cases}
[1,val]& \text{dis[N] <= k}\\
[val+1,r]& \text{dis[N] > k}
\end{cases}$$

这样就确定了寻找范围，然后就结束了...。

记得初始化时 $l=-1$，避免无解情况误判。

为什么令 $l=-1$ 呢？因为当无解时，当且仅当 $1$ 与 $N$ 不连通，那么 $dis[N]$ 永远 $\leq k$，

那么二分时将永远进入 $[l,val]$ 区间，最终 $l=-1$ 即答案。

# 代码实现

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<cstring>
#include<deque>
#define N 1010
#define M 10010
using namespace std;

int n,p,k,head[N],cnt=0,dis[N];
bool vis[N];
struct Edge{
	int next,to,val;
}edge[M<<1];
deque<int>q;

int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0' || c>'9') f=(c=='-')?-1:1,c=getchar();
	while(c>='0' && c<='9') x=x*10+c-48,c=getchar();
	return x*f;
}

void addedge(int x,int y,int z){
	cnt++;
	edge[cnt].next=head[x];
	edge[cnt].to=y;
	edge[cnt].val=z;
	head[x]=cnt;
	return;
}

bool chck(int x){
	while(!q.empty()) q.pop_front();
	memset(vis,false,sizeof(vis));
	memset(dis,0,sizeof(dis));
	dis[1]=0;vis[1]=true;
	q.push_front(1);
	while(!q.empty()){
		int now=q.front();
		q.pop_front();
		for(int i=head[now];i;i=edge[i].next){
			int y=edge[i].to;
			int z=edge[i].val<=x?0:1;
			if(!z && (!vis[y] || dis[y]>dis[now])){
				dis[y]=dis[now];
				q.push_front(y);
				vis[y]=true;
			}
			else if(!vis[y] || dis[y]>dis[now]+1){
				dis[y]=dis[now]+1;
				q.push_back(y);
				vis[y]=true;
			}
		}
	}
	if(dis[n]<=k) return true;
	return false;
}

int main(){
	n=read();p=read();k=read();
	int mx=0,x,y,z;
	for(int i=1;i<=p;i++){
		x=read();y=read();z=read();
		addedge(x,y,z);
		addedge(y,x,z);
		mx=max(mx,z);
	} 
	int l=-1,r=mx,mid;
	while(l<r){
		int mid=(l+r)>>1;
		if(chck(mid)) r=mid;
		else l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}
```

完结撒花。

---

## 作者：Unstoppable728 (赞：6)

这道题，第一眼看去非常像分层图，但和裸的分层图不太一样。因为它只要求路径总权值为路径上最大一条路径的权值，但仔细考虑，这同时也满足一个贪心的性质，那就是当你每次用路径总权值小的方案来更新，那么可以保证新的路径权值尽量小。

所以这道题在不删边的情况下可以使用Dij来跑，而删边权的情况就是分层图。

所以就拿分层图来搞好了^_^。

由于这个数据p和k都比较大，所以直接建k+1层图是要爆的，而k+1层图边都一样，我们就用dis[层数（0-k）]来表示。

具体的就是每次Dij转移是要分两种情况：

		1.在原层跑，也就是说，在这层中用Dij
        2.若下一层边的另一端不够优秀，就用这一层来直接更新，当然就是把这一端的点的解直接复制

大概就是这样了

/代码-本人的结构体用的比较多，大神不喜勿喷

```c++
#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct tmp{
    int no;
    int ler;
    int dis;
    bool friend operator < (tmp x,tmp y)
    {
        return x.dis>y.dis;
    }
};
struct pnt{
    int no;
    int hd;
    int dis[1005];
    bool vis[1005];
}p[1005];
struct ent{
    int twd;
    int lst;
    int vls;
}e[50000];
int n,m,d;
int cnt;
priority_queue<tmp>Q;
void ade(int f,int t,int v)
{
    cnt++;
    e[cnt].twd=t;
    e[cnt].lst=p[f].hd;
    p[f].hd=cnt;
    e[cnt].vls=v;
}
int main()
{
    scanf("%d%d%d",&n,&m,&d);
    for(int i=1;i<=n;i++)
    {
        p[i].no=i;
        for(int j=0;j<=d;j++)
        {
            p[i].dis[j]=0x3f3f3f3f;
        }
    }
    p[1].dis[0]=0;
    for(int i=1;i<=m;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        ade(a,b,c);
        ade(b,a,c);
    }
    tmp x;
    x.no=1;
    x.ler=0;
    x.dis=0;
    Q.push(x);
    while(!Q.empty())
    {
        x=Q.top();
        Q.pop();
        int nw=x.no;
        int t=x.ler;
        if(x.no==n&&x.ler==d)
        {
            printf("%d\n",x.dis);
            return 0;
        }
        if(p[nw].vis[t])continue;
        p[nw].vis[t]=true;
        for(int i=p[nw].hd;i;i=e[i].lst)
        {
            int to=e[i].twd;
            if(p[to].dis[t]>max(p[nw].dis[t],e[i].vls))
            {
                p[to].dis[t]=max(p[nw].dis[t],e[i].vls);
                x=(tmp){to,t,p[to].dis[t]};
                Q.push(x);
            }
            if(p[to].dis[t+1]>p[nw].dis[t]&&t<d)
            {
                p[to].dis[t+1]=p[nw].dis[t];
                x=(tmp){to,t+1,p[to].dis[t+1]};
                Q.push(x);
            }
        }
    }
    printf("-1\n");
    return 0;
}
```

---

## 作者：ycyaw (赞：6)

~~这道题没有那么难的吧~~


### 咳咳我们开始正题

题意简述一下，就是在加权无向图上求出一条从$1$号结点到$N$号结点的路径，使路径上第$K+1$大的边权尽量小

恩，作为一名OIER，我们先看一下~~题解~~数据范围

好的不大，我们可以跑好多次最短路(逃

由于题目求最值，那就二分答案喽

我们转化问题：二分$mid$，每次判断是否能使$1$到$N$的路径上第$K+1$大的边权小于$mid$。那么只需要把升级价格大于$mid$的边权值赋为1，其余权值赋为0，跑最短路得到$dis[n]$与$K$进行比较，若小于等于$K$，说明该答案可行，缩小$r$继续二分，否则缩小$l$。

至于跑最短路，各种神仙算法都可以，反正我用的$SPFA$。

上代码（~~或许有的人只看这个~~）：

宏定义不要在意，个人习惯哈哈
```cpp
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define ts cout<<"ok"<<endl
#define lowbit(x) (x)&(-x)
#define oo (1e18)
#define soo (1e9)
#define INF 2147483647
#define Bigprime 212370440130137957int
#define ll long long
#define LL unsigned long long
#define lll __int128
#define hash Hash
#define gc getchar()
#define pc(x) putchar(x)
#define ls(x) x<<1
#define rs(x) x<<1|1
#define hh puts("")
#define mp make_pair
#define fi first
#define se second
using namespace std;
int head[1005],dis[1005],n,p,k,cnt,tot,s[100005];
bool vis[1005];
struct Edge{
	int u,v,s,nx;
}e[100005];
inline ll read(){
    ll ret=0,ff=1;char c=gc;
    while(!isdigit(c)){if(c=='-') ff=-ff;c=gc;}
    while(isdigit(c)){ret=(ret<<3)+(ret<<1)+c-'0';c=gc;}
    return ret*ff;
}
void add(int x,int y){
	e[++cnt].u=x;
	e[cnt].v=y;
	e[cnt].nx=head[x];
	head[x]=cnt;
}
void spfa(){
	for(int i=1;i<=n;i++) dis[i]=soo,vis[i]=0;
	vis[1]=1,dis[1]=0;
	queue<int> q;
	q.push(1);
	while(!q.empty()){
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(int i=head[x];i;i=e[i].nx){
			int y=e[i].v,z=e[i].s;
			if(dis[y]>dis[x]+z){
				dis[y]=dis[x]+z;
				if(!vis[y]){
					vis[y]=1;
					q.push(y);
				}
			}
		}
	}
}
int main(){	
	n=read(),p=read(),k=read();
	for(int i=1;i<=p;i++){
		int x=read(),y=read(),z=read();
		s[++tot]=z;
		s[++tot]=z;
		add(x,y);
		add(y,x);
	}
	int ans=-1;
	int l=0,r=1000000;
	while(l<=r){
		int mid=(l+r)>>1;
		for(int i=1;i<=cnt;i++){
			if(s[i]<=mid) e[i].s=0;
			else e[i].s=1;
		}
		spfa();
		if(dis[n]<=k){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%d",ans);
    return 0;
}
```

---

## 作者：超级小帆船RP (赞：4)

典型的二分答案配套SPFA，由于是无向图遍历，所以每条边要存储两次。

由于可能会出现稀疏图，所以用邻接矩阵空间复杂度过大，可用邻接表解决问题。

代码中的tpe函数为邻接表加边操作，同时需要注意：二分枚举答案时用下取整，因为本体的函数图象为先不可行后可行。下附C++代码，供读者参考。

```cpp
#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int M=30005;
int a[M],b[M],l[M],to[M],now,head[M],nest[M],dist[M],adj[M],in[M];
int n,p,k,x,y,z,tmp;
void tpe(int x,int  y,int z){
    to[++now]=y;
    nest[now]=head[x];
    head[x]=now;
    l[now]=z;
}
void spfa(){
     memset(dist,0x7f7f,sizeof(dist));
     memset(in,0,sizeof(in));
     queue <int> q;
     q.push(1);
     in[1]=1;dist[1]=0;
     while(!q.empty()){
            int x=q.front();q.pop();in[x]=0;
            for(int j=head[x];j!=-1;j=nest[j]){
                     if(dist[x]+adj[j]<dist[to[j]]){
                               dist[to[j]]=dist[x]+adj[j];
                               if(!in[to[j]] ) q.push(to[j]),in[to[j]]=1;
                     }
            }
     }
     return ;
}
int pd(int x){
    for(int i=1;i<=n;i++){ 
            for(int j=head[i];j!=-1;j=nest[j]){
                    if(l[j]<=x) adj[j]=0;
                    else adj[j]=1;
            }
    } 
    spfa();
    return dist[n]<=k;
}
int main(){
    scanf("%d%d%d",&n,&p,&k);
    memset(head,-1,sizeof(head));
    for(int i=1;i<=p;i++){
            scanf("%d%d%d",&x,&y,&z);
            tpe(x,y,z);
            tpe(y,x,z);
    }
    int l=0,r=1000001;
    while(l<r){
            int m=(l+r)/2;
            if(pd(m)) r=m;
            else l=m+1;
    }
    if(r==1000001) printf("-1");
    else printf("%d",r);
    return  0;
}
```

---

## 作者：bits (赞：3)

蒟蒻发一下Dijkstra题解
# 堆优化！
可能本人想多了，因为n<=1000，
## ~~但...n方可以直接过~~
## 个人认为与[P2939 改造路Revamping Trails](https://www.luogu.org/problemnew/show/P2939)很相似
我们可以把这题当做分层图最短路做

蒟蒻不知道怎么二分，感兴趣的可以看下楼下**大佬**们的题解

免费的电话线，边长即为0

在求最短路时分类即可：
1.花钱建电话线：min(在当前节点的费用，max(与其相连的所有点的费用，这条边的费用));
2.不花钱:分层，min(当前点的费用，与其相连且是**上一层的节点**的费用);

请具体见代码。

(利用优先队列，每次取出其中最小的点，并对相连的边进行“松弛”操作)
~~(怎么感觉只是把spfa的普通队列换成了堆)~~
->可能是因为我Dijkstra学的不太好。。。水平有限，敬请谅解

```cpp
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <algorithm>
using namespace std;
const int N=1005,M=20005;
//无向边，即把有向边建两次即可，数组开2倍
struct edge{
    int node,next,val;
}Edge[M];
//用边集数组的方式实现邻接表
//似乎点太少了，邻接矩阵都可以。。。
//(我写完才发现)
//注意：邻接表不计当前节点，只记录与其连接的点
int Head[N],Dis[N][N],n,m,Cnt,tot;
bool v[N][N];
struct qNode{
    int key,dep,len;
    //dep:层次
    friend bool operator < (qNode x, qNode y){
        return x.len>y.len;//小根堆
    }
};
inline void Add(int x,int y,int l){
    tot++;
    Edge[tot].node=y;
    Edge[tot].next=Head[x];
    Edge[tot].val=l;
    Head[x]=tot;
}
void Dijkstra(){
//模板
    for(int i=1;i<=n;i++){
        for(int j=0;j<=Cnt;j++)
            Dis[i][j]=1e9;
    }
    Dis[1][0]=0;
    //Dis[i][j]表示从源点到点i时用j次免费电话线时的最小花费
    priority_queue<qNode> q;
    q.push((qNode){1,0,0});
    qNode r;
    while(!q.empty()){
        r=q.top();
        q.pop();
        if(v[r.key][r.dep])
            continue;
        v[r.key][r.dep]=1;
        //key:节点编号
       //当然用pair<int,int>保存也可以
        //遍历相邻的点
        for(int k=Head[r.key];k;k=Edge[k].next){
            if(max(Dis[r.key][r.dep],Edge[k].val)<Dis[Edge[k].node][r.dep]){//在同一层，花费建电话线
                Dis[Edge[k].node][r.dep]=max(Dis[r.key][r.dep],Edge[k].val);
                q.push((qNode){Edge[k].node,r.dep,Dis[Edge[k].node][r.dep]});
                //若源点到当前点的距离被更新了，
                //则源点到与其相邻的点的距离也有可能被更新
            }
            if(r.dep<Cnt && Dis[r.key][r.dep]<Dis[Edge[k].node][r.dep+1]){
            //免费的电话线
                Dis[Edge[k].node][r.dep+1]=Dis[r.key][r.dep];
                //下一层上的点
                q.push((qNode){Edge[k].node,r.dep+1,Dis[Edge[k].node][r.dep+1]});
            }
        }
    }
}
int main(){
    scanf("%d%d%d",&n,&m,&Cnt);
    int u,v,l;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&l);
        Add(u,v,l);
        Add(v,u,l);//无向图
    }
    Dijkstra();
    if(Dis[n][Cnt]<1e9)
        printf("%d\n",Dis[n][Cnt]);
    else
        puts("-1");//无解
    return 0;
}
```
//求通过；谢谢！

---

## 作者：EarthGiao (赞：3)

## 【思路】
二分答案+SPFA    

### 【题目大意】
点1到点n中间有很多对可以连接电线的电线杆子   
连接的权值不一样   
可以让你免费连接K条    
求最少的花费（花费等于连接的最长的那个电线，这里连接的电线当然不包括免费的）    

### 【题目分析】   
答案是具有单调性的    
因为如果花费i的钱可以的话   
那花费i+1块钱也一定可以   
花费i块钱不行的话   
那花费i-1块钱也一定是不可以的   
所以用二分答案就很显然了吧    

### 【核心思路】
二分什么呢？    
当然是二分花费了    
因为是可以免去k条的    
所以大于二分出来的值的那就变为0就好了   
所以如果1到n被免去最少电线的那条路   
只要满足免去电线的根数小于等于k    
那这个答案就是属于可行范围的    
反之则是不可行的    
这就是二分的思路   
 
不过，既然是求最小的那根    
那为什么不用SPFA呢？       
当成最短路来写就好了   
被免去的边的权值就赋值为1   
没有被免去的那就是0   
这样就能求出1到n之间连接的边中    
被免去最少边的那条边的免去的值是多少了        

### 【题外话】
一开始我想的是二分出来值之后搜索的    
然后搜索中如果某一条边不行的话   
那应该返回去搜另一条边的    
但是如果这个点之后的下一个点不行的话    
那应该是搜索另外的和这个点连着的点的    
所以应该是continue    
但是我打成了return     
还莫名其妙的比continue多了20分成了70分    
因为这个玄学的return让我少跑了很多的东西导致不会超时   
因为这个我被gyh大佬戏称为“最强优化大师”！    
（在最后附上我的错误解法代码）    

## 【完整代码——AC】
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int Max = 20010;
struct node
{
	int y,ne,z;
}a[Max];
int sum = 0,head[1010];
void add(int x,int y,int z)
{
	a[++ sum].y = y;
	a[sum].ne = head[x];
	a[sum].z = z;
	head[x] = sum; 
}
int n,p,k;
int d[1010];
bool use[1010];
bool check(int x)
{
	memset(d,0x3f,sizeof(d));
//	memset(use,false,sizeof(use));
//	memset(cnt,0,sizeof(cnt));
	queue<int>q;
	d[1] = 0;
	q.push(1);
	use[1] = true;
	while(!q.empty())
	{
		int qwq = q.front();
		q.pop();
		use[qwq] = true;
		for(register int i = head[qwq];i != 0;i = a[i].ne)
		{
			int owo;
			if(a[i].z > x)
			owo = d[qwq] + 1;
			else
			owo = d[qwq];
			if(owo < d[a[i].y])
			{
				d[a[i].y] = owo;
				if(!use[a[i].y])
				{
					q.push(a[i].y);
					use[a[i].y] = true;
				}
			}
		}
		use[qwq] = false;
	}
	if(d[n] <= k)return true;
	else	return false;
}

int main()
{
	cin >> n >> p >> k;
	for(register int i = 1;i <= p;++ i)
	{
		int u,v,w;
		cin >> u >> v >> w;
		add(u,v,w);add(v,u,w);
	}
	int ans = -1;
	int l = 0,r = 1000000;
	while(l <= r)
	{
		int mid = (r + l) >> 1;
		if(check(mid))r = mid - 1,ans = mid;
		else	l = mid + 1;
	}
	cout << ans << endl;
	return 0; 
}
```

### 【买一赠一 —— 错解】
```cpp
/*
我二分出来最长的那条电话线的长度
然后从1开始搜索
如果这条线长度超出了二分出来的值
那就先用那k对免费的电话线
如果k对用完了那这条路就是行不通的
就回到上一个点换条路接着搜索
如果这个搜索里面有能够在满足刚好用完或者用不完k条免费的电话线的情况下
还能够让最长的电话线小于等于二分出来的数
那二分返回就是真  
*/
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
const int Max = 10004;
const int M = 1003;
struct node
{
	int y,ne;
	int w;
}a[Max << 1];
int sum = 0;
int head[M];
void add(int u,int v,int w)
{
	a[++ sum].y = v;
	a[sum].ne = head[u];
	a[sum].w = w;
	head[u] = sum;
	
	a[++ sum].y = u;
	a[sum].ne = head[v];
	a[sum].w = w;
	head[v] = sum; 
}
int n,p,k;
int fg;
bool use[M];

void dfs(int x,int fath,int js,int mm)
{
	if(fg == 0)
	{
		if(x == n)
		{
			fg = 1;
			return;
		}
		for(register int i =head[x];i != 0;i = a[i].ne)
		{
			if(a[i].y != fath && use[a[i].y] == false)
			{
				if(a[i].w > mm)
				{
					if(js > 0)
					{
						use[a[i].y] = true;
						dfs(a[i].y,x,js - 1,mm);	
						use[a[i].y] = false;
					}
					else	return;	
				}
				else
				{
					use[a[i].y] = true;
					dfs(a[i].y,x,js,mm);	
					use[a[i].y] = false;
				}
			}
		}
	}
}

bool check(int x)
{
	fg = 0;
	dfs(1,0,k,x);
	if(fg == 0)return false;
	else	return true;
}

int father[M];

int find(int x)
{
	if(father[x] != x)father[x] = find(father[x]);
	return father[x];
}

void hebing(int x,int y)
{
	x = find(x);
	y = find(y);
	if(x != y)
		father[x] = y;
}

signed main()
{
	cin >> n >> p >> k;
	int MM = 0; 
	for(register int i = 1;i <= n;++ i)
		father[i] = i;
	for(register int i = 1;i <= p;++ i)
	{
		int u,v,w;
		cin >> u >> v >> w;
		if(find(u) != find(v))
			hebing(u,v);
		add(u,v,w);
		MM = max(MM,w);
	}
	if(find(1) != find(n))
	{
		cout << -1 << endl;
		return 0;
	}
	int l = 0,r = MM;
	while(l < r)
	{
		int mid = (l + r) >> 1;
		if(check(mid))r = mid;
		else	l = mid + 1;
	}
	cout << l << endl;
	return 0;
}
```

---

## 作者：LB_tq (赞：3)

# 二分答案+双端队列BFS
看到题解区大多是SPFA，所以写一下BFS。

大体思路：二分答案mid作为花费，因为只需支付第k+1大的边的花费（显然应免费权值最大的k条边）,所以将边权大于mid的看作边权1，小于等于的看作边权0。此时求一条从节点1到n的最短路即可。

如果最短路大于k说明需要免费的超过了k条边，则将右端点r=mid-1，否则将左端点l=mid+1。

至于初始边界，k>=1,所以l初始化为最小边权，r初始化为最大边权。

**对于这种边权只有0和1的最短路，就可以用双端队列BFS求解。**

**与普通BFS不同的是，当加入0边权的边时，从队首加入；加入1边权的边时，从队尾加入。这样就可以保证每次取队首是都是当前最短距离来更新其他的节点。**

时间复杂度((n+m)log(r-l))，如果用SPFA，复杂度(kmlog(r-l))(k是较小的常数，蒟蒻也不会证)。

**代码很好理解，手写队列。记得一定要将队列开大一些，因为要在两端插入。队首和队尾指针初始化为中间位置。**

附上代码：
```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=1e3+10;
const int maxm=1e5+10;
int n,m,k,s,ans=2e9,f[maxn];
int q[maxn<<6],dis[maxn],h1,t1;//q是队列，dis存储1号节点到其他节点的距离。
struct edge{
	int t;
	int v;
	int w;
}e[maxm<<1];
int fr(){
	char ch=getchar();
	while(ch>'9'||ch<'0')
		ch=getchar();
	int sum=ch-'0';
	while((ch=getchar())>='0'&&ch<='9')
		sum=(sum<<3)+(sum<<1)+ch-'0';
	return sum;
}//快读
void add(int x,int y,int z){
	s++;
	e[s].t=f[x];
	e[s].v=y;
	e[s].w=z;
	f[x]=s;
}//邻接表存边
bool check(int x){
	int y;
	h1=t1=maxn<<3;
	q[++t1]=1;
	dis[1]=0;
	while(h1<t1){
		h1++;
		y=q[h1];
		for(int i=f[y];i!=0;i=e[i].t)
			if(dis[e[i].v]>dis[y]){
				if(e[i].w<=x){
					q[h1--]=e[i].v;
					dis[e[i].v]=dis[y];
				}
				else{
					q[++t1]=e[i].v;
					dis[e[i].v]=dis[y]+1;
				}
			}
	}
	if(dis[n]>k)
		return false;
	return true;
}
int main(){
	n=fr();
	m=fr();
	k=fr();
	int x,y,z,l=2e9,r=0,mid;
	for(int i=1;i<=m;i++){
		x=fr();
		y=fr();
		z=fr();
		l=min(l,z);
		r=max(r,z);
		add(x,y,z);
		add(y,x,z);
	}	
	while(l<=r){
		memset(dis,0x3f,sizeof(dis));//每次记得初始化dis数组
		mid=(l+r)>>1;
		if(check(mid)){
			ans=min(ans,mid);
			r=mid-1;
		}
		else
			l=mid+1;
	}
	if(ans!=2e9)
		printf("%d",ans);
	else
		printf("-1");
	return 0;
}
```
祝大家AC！

---

## 作者：Dying_Light (赞：3)



------------
## 废话

看到所有题解都没有用pair的，打完pair之后真的感觉清爽了许多，STL大法好啊！

## 基本思路

我们用二元组代表一个点，这样我们就可以更清楚的理解此题与最短路之间的关系，

从$ <u,k> -> <v,k> $ 有长度为l的边;

从$<u,k> -> <v,k+1>$ 有长度为0的边;

我们的dp数组就是代表从起点到<u,k>的路径上最大的边最短是多少
我们很容易得出状态转移方程:

不用:$dp[v][k] = min(dp[v][k],max(dp[u][k],e[i].dis))$

用:$dp[v][k+1]=min(dp[v][k+1],dp[u][k])$

**解释一下：**
用max(dp[u][k],e[i].dis)来更新dp[v][k]的最小值，因为你要找一个第k-1大的边，让这个边更小，你转移相当于松弛操作，先找一个更大的来当做第k大，
然后转移最小值，

实现就用pair就好了

vans~~~~

```cpp
#include<algorithm>
#include<cstdio>
#include<queue>
#include<cmath>
#include<cstring>
#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
const int maxn=1005;
const int maxm=500000;
const int INF=0x3f3f3f3f;
struct edge{
	int to,next,dis;
}e[maxm];
int head[maxm],cnt;
int N,P,K;
int dis[maxn][maxn];
bool vis[maxn][maxn];
void add_edge(int u,int v,int w){
	e[++cnt].next=head[u];
	e[cnt].to=v;
	e[cnt].dis=w;
	head[u]=cnt;
}
queue<pair<int,int> >q;
void spfa(){
	memset(dis,INF,sizeof(dis));
	dis[1][0]=0;
	vis[1][0]=1;
	q.push(pair<int,int>(1,0));
	while(!q.empty()){
		pair<int,int> tmp=q.front();q.pop();
		int u=tmp.first,k=tmp.second;
		vis[u][k]=0;
		for(int i=head[u];i;i=e[i].next){
	 		int v=e[i].to;
			if(max(dis[u][k],e[i].dis)<dis[v][k]){
				dis[v][k]=max(dis[u][k],e[i].dis);
				if(!vis[v][k]){
					q.push(pair<int,int>(v,k));
					vis[v][k]=1;
				}
			}
			if(k<K&&dis[u][k]<dis[v][k+1]){
				dis[v][k+1]=dis[u][k];
				if(!vis[v][k+1]){
					q.push(pair<int,int>(v,k+1));
					vis[v][k+1]=1;
				}
			}
		}
	}
}
int main(){
	scanf("%d%d%d",&N,&P,&K);
	for(int i=1;i<=P;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	spfa();
	if(dis[N][K]==INF) cout<<-1<<endl;
	else cout<<dis[N][K]<<endl;
	//printf("Time used= %.2f\n",(double)clock()/CLOCKS_PER_SEC);
	//system("pause");
	return 0;
}

```

---

## 作者：Adove (赞：2)

“市场经济就像一只看不见的手，悄悄地影响着资本主义世界的发展”

分层图也像一只看不见的手，拥有非常强大的自我调控能力，是~~暴力~~解决问题的利器。

思路：二分+~~暴力~~分层图BFS

我们构建k+1层图，以底层为0，那么每层代表的就是使用免费的次数，对于每条边，我们在每层建边的同时，还要向上一层对应的点连一条0边，然后在这个分层图上bfs遍历，若遍历到终点就立刻返回true，若无法遍历到则返回false。

至于无解的情况，立个flag判一下就好

上代码↓

```
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int MAXN=1e6,MAXM=1e7;

int n,p,k,x,y,z,np;
int h[MAXN<<1],ln[MAXN<<1],q[MAXM<<1];
bool vis[MAXN<<1],fl;
struct rpg{
    int li,nx,ln;
}a[MAXM<<1];

void add(int ls,int nx,int ln){
    a[++np]=(rpg){h[ls],nx,ln};
    h[ls]=np;
}

bool check(int mid){
	memset(vis,0,sizeof(vis));
	int hd=1,tl=1;
	q[hd]=1;
	vis[1]=1;
	while(hd<=tl){
		int nw=q[hd++];
		for(int i=h[nw];i;i=a[i].li){
			if(!vis[a[i].nx]&&a[i].ln<=mid){
				vis[a[i].nx]=1;
				q[++tl]=a[i].nx;
				fl|=(a[i].nx%n==0);
				if(a[i].nx%n==0) return 1;
			}
		}
	}return 0;
}

int main(){
    scanf("%d%d%d",&n,&p,&k);
    for(int i=1;i<=p;++i){
        scanf("%d%d%d",&x,&y,&z);
        for(int j=0;j<k;++j){
            add(x+n*j,y+n*j,z);
            add(y+n*j,x+n*j,z);
            add(x+n*j,y+n*(j+1),0);
            add(y+n*j,x+n*(j+1),0);
        }add(x+n*k,y+n*k,z);
        add(y+n*k,x+n*k,z);
    }int l=0,r=MAXN;
    while(l<r){
    	int mid=l+r>>1;
    	if(check(mid)) r=mid;
    	else l=mid+1;
	}if(!fl){
		puts("-1");
		return 0;
	}printf("%d\n",l);
    return 0;
}
```

---

## 作者：asuldb (赞：2)

```cpp
//二分答案+最短路判断 
//我们需要二分每一条边的长度，再跑一遍最短路判断答案是否可行 
//只不过这里采用的是比较稀有的堆优dij了 
//不过我们这里dij跑的不是距离，而是使用那个免费名额的次数 
//还是上代码吧 
#pragma GCC optimize(3)
#include<cstring>
#include<queue>
#include<cstdio>
#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;
#define maxn 1001
#define re register
#define inf 999999999
#define maxw 10001*2//无向图前向星开两倍 
typedef pair<int,int> pii;
priority_queue<pii,vector<pii>,greater<pii> > q;//一个dij要用的小根堆 
struct node
{
    int u,v,w,nxt;
}edge[maxw];
int d[maxn],head[maxn],a[maxw];
//d[i]储存的是从1到i所使用免费名额的最小次数 
int n,m,p,s=1,num=1,ans=inf;
bool f[maxn];
inline void read(int &x)
{
    char c=getchar();
    x=0;
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9')
    {
        x=x*10+c-48;
        c=getchar();
    }
}//读入优化
inline void add_edge(int x,int y,int z)
{
    edge[num].u=x;
    edge[num].v=y;
    edge[num].w=z;
    edge[num].nxt=head[x];
    head[x]=num;
    num++;
}//前向星加边
inline bool dijkstra(int now)
{
    for(re int i=1;i<=n;i++)
    {
        d[i]=inf;
        f[i]=false;
    }
    d[s]=0;
    q.push(make_pair(d[s],s));
    while(!q.empty())
    {
        pii mind=q.top();
        q.pop();
        int k=mind.second;
        if(f[k]) continue;
        else
        {
            f[k]=true;
            for(re int i=head[k];i!=-1;i=edge[i].nxt)
            {
                if(edge[i].w>now)
                if(d[edge[i].v]>d[k]+1)
                {
                    d[edge[i].v]=d[k]+1;
                    q.push(make_pair(d[edge[i].v],edge[i].v));
}//如果到edge[i].v的边大于当前二分的答案，那么就要使用一次名额
                if(edge[i].w<=now)
                if(d[edge[i].v]>d[k])
                {
                    d[edge[i].v]=d[k];
                    q.push(make_pair(d[edge[i].v],edge[i].v));
}//如果 edge[i].v的边不大于当前二分的答案，那么就无需使用名额，直接松弛操作
            }
        }
    }
    if(d[n]>p) return false;//如果到达n的次数大于免费的次数限制，那么当前答案不可行
    return true;//反之，则可行 
}
int main()
{
    read(n);
    read(m);
    read(p);
    for(re int i=1;i<=n;i++)
      head[i]=-1;
    int xx,yy,zz;
    for(re int i=1;i<=m;i++)
    {
        read(xx);
        read(yy);
        read(zz);
        add_edge(xx,yy,zz);
        add_edge(yy,xx,zz);
        a[i]=zz;
    }
    sort(a+1,a+1+m);
    if(dijkstra(0))
    {
        cout<<"0"<<endl;
        return 0;
	}//特判，答案为0的情况
    if(!dijkstra(a[m]))
    {
        cout<<"-1"<<endl;
        return 0;
	}//特判，如果答案最大都不能到达，输出-1退出
    int l=1,r=m;
    while(l<=r)
    {
        int mid=(l+r)/2;
        if(dijkstra(a[mid]))
        {
            ans=min(ans,a[mid]);
            r=mid-1;
        }
        else l=mid+1;//可以说是很标准的二分了 
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：战影 (赞：2)

提供另一种二分的思路，考试考模板烤到这道题了，据说是一道二分+$spfa$的题，的确是这样的

正常的二分套路是把$>mid$的边的代价看成$1$，而$<=mid$的边的代价看成是$0$，那么$spfa$最短路，判断终点的最短路径代价是否超过$k$即可。

最短路更新的想法就是这么奇特：

同样是二分$mid$，但是这里判断的是能否到达终点，

设$d[i]$为到达$i$的最短路径条数，$px[i]$表示到达$i$的使用了多少次免费次数

每次按照最短路的套路更新$d$和$px$


```
#include<cstdio>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cstring>
#include<string>
#include<queue>

#define LL long long
using namespace std;

void in(int &x) {
	register char c=getchar();
	x=0;
	int f=1;
	while(!isdigit(c)) {
		if(c=='-') f=-1;
		c=getchar();
	}
	while(isdigit(c)) {
		x=x*10+c-'0';
		c=getchar();
	}
	x*=f;
}

void print(int x) {
	if(x<0) putchar('-'),x=-x;
	if(x>9) print(x/10);
	putchar(x%10+'0');
}

#define N 100000

int n,p,k,tot,head[N];
struct node {
	int to,next,w;
} e[N];

void add(int u,int v,int w) {
	e[++tot].to=v,e[tot].next=head[u],head[u]=tot,e[tot].w=w;
}

int d[N],px[N];
bool vis[N];
queue<int>Q;
bool spfa(int X) {
	memset(d,0x7f,sizeof(d));
	memset(vis,0,sizeof(vis));
	Q.push(1),d[1]=0,px[1]=k;
	while(!Q.empty()) {
		int u=Q.front();
		Q.pop();
		vis[u]=false;
		for(int i=head[u]; i; i=e[i].next) {
			int v=e[i].to;
			if(e[i].w<=X&&d[v]>d[u]+1) {
				d[v]=d[u]+1,px[v]=px[u];
				if(!vis[v]) Q.push(v),vis[v]=true;
			}
			if(e[i].w>X&&d[v]>d[u]+1&&px[u]!=0) {
				px[v]=px[u]-1,d[v]=d[u]+1;
				if(!vis[v]) Q.push(v),vis[v]=true;
			}
			if(d[v]<=d[u]+1) {
				if(e[i].w<=X&&px[v]<px[u]) {
					px[v]=px[u];
					if(!vis[v]) Q.push(v),vis[v]=true;
				}
				if(e[i].w>X&&px[v]<px[u]-1) {
					px[v]=px[u]-1;
					if(!vis[v]) Q.push(v),vis[v]=true;
				}
			}
		}
	}
	return d[n]!=d[0];
}

int main() {
	in(n),in(p),in(k);
	int l=0,r=0,mid,ans;
	for(int u,v,w,i=1; i<=p; i++) {
		in(u),in(v),in(w);
		add(u,v,w),add(v,u,w);
		if(w>r) r=w;
	}
	if(!spfa(2147483647)) return print(-1),0;

	while(l<=r) {
		mid=(l+r)>>1;
		if(spfa(mid)) r=mid-1,ans=mid;
		else l=mid+1;
	}
	print(ans);

	return 0;
}
```

---

## 作者：Starlight237 (赞：1)

二分是最显然的思路，而如今最短路的最优解法是堆优化Dijkstra。但看到题解里用二分答案的都没有用堆优化dijkstra，蒟蒻来水一发：

首先大致思路如下：
```
由于此题不是直接求从源点 1 到终点 n 总费用最小之类的，所以不能用 dijkstra 直接来跑最短路径，需要对原来的图进行重新建图。

对于求答案尽可能小这样的问题，很明显是一个二分答案类的问题， 所以可以采用二分答案来求满足要求的长度 x。 

对于所有大于 x 的长度都认为需要采用免费方式（即代价为 1，
表示占用一个免费名额），而所有小于等于 x 的长度的边不采用免费方式（即代价为 0，即表示不占用免费名额） ，那么如果从点 1 到点 n 的最短距离小于等于 k，说明花 x 费用可以实现要求，否则就不可以。

这样就用二分一直找到满足要求的最小的 x 就可以了。
```
这样的程序跑出来开O2也有几百ms，效率较低。因此我们采用堆优化Dijkstra！
```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
#define IOSIZE 10000000
static char in[IOSIZE],*p=in,out[IOSIZE],*q=out,ch[20],*t=ch;
inline int read(){
	reg int x=0;
	while(*p<48)++p;
	while(*p>47)x=(x<<1)+(x<<3)+(*p++^48);
	return x;
}
inline void write(int x){
	x<0&&(*q++='-',x=-x);
	!x&&(*q++='0');
	while(x)*t++=x%10+48,x/=10;
	while(t!=ch)*q++=*--t;
}
static int n,m,ans=-1,tot,k,head[5001],dis[5001];
struct Edge{
	int v,w,nxt;
}eg1[100001],eg[100001];
inline void addedge(int u,int v,int w){
	eg[++tot]=Edge{v,w,head[u]},head[u]=tot;
}
struct Node{
	int to,dis;
	friend inline bool operator<(Node a,Node b){
		return a.dis>b.dis;
	}
};
priority_queue<Node>Q;
inline int dij(int x){
	memset(dis,0x3f,sizeof dis);
	Q.push(Node{1,0}),dis[1]=0;
	while(!Q.empty()){
		Node now=Q.top();Q.pop();
		reg int v=now.to,w=now.dis;
		if(w!=dis[v])continue;
		for(reg int i=head[v],vv,ww;i;i=eg[i].nxt)
			vv=eg[i].v,ww=eg[i].w>x,w+ww<dis[vv]&&(
			dis[vv]=w+ww,Q.push(Node{vv,dis[vv]}),0);
	}return dis[n];
}
int main(){
	fread(in,1,IOSIZE,stdin);
	n=read(),m=read(),k=read();
	for(reg int i=1,u,v,w;i<=m;++i)
		u=read(),v=read(),w=read(),
		addedge(u,v,w),addedge(v,u,w);
	reg int l=0,r=1000000,mid;
	while(l<=r)
		mid=l+r>>1,dij(mid)<=k?ans=mid,r=mid-1:l=mid+1;
	write(ans);
	fwrite(out,1,q-out,stdout);
	return 0;
}
```
55ms with O2

# 完结撒花

---

## 作者：Sol1 (赞：1)

其实我用的也是二分答案，但是在Check的时候我用了一种不同的方法来找到最短路。

先说一下**思路**吧：

- $\texttt{step1:}$显然在路径上要选最贵的$K$条边 ~~obviously~~
- $\texttt{step2:}$所以答案有明显的单调性
- $\texttt{step3:}$于是我们有了二分的思路
- $\texttt{step4:}$问题转变为，对一个已知图，求一个路径，使得第$K+1$条边的权值不超过$mid$。
- $\texttt{step5:}$此时问题就很好解决了：将边权$>K$的边的权值设为$1$，其余设为$0$，然后跑一遍点$1$的单源最短路径即可完成Check。
- $\texttt{Extra:}$由于在Check时只有$0$边和$1$边，于是我们可以选取**BFS双端队列优化**求解，0边往后放，1边往前放，最后取的时候从后面取就可以了~

上代码！

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 1005, MAXM = 10005;
int u[MAXM], v[MAXM], w[MAXM], N, M, K;
vector <pair <int, int> > G[MAXN];
bool book[MAXN];
int dis[MAXN];
void BuildGraph(int L)
{
    for (int i = 1;i <= N;i++)
        G[i].clear();
    for (int i = 1;i <= M;i++)
        if (w[i] <= L)
        {
            G[u[i]].push_back(make_pair(v[i], 0));
            G[v[i]].push_back(make_pair(u[i], 0));
        }
        else
        {
            G[u[i]].push_back(make_pair(v[i], 1));
            G[v[i]].push_back(make_pair(u[i], 1));
        }
}
int Bfs(int x)
{
    memset(dis, 0x3f, sizeof(dis));
    deque <pair <int, int> > que;
    que.push_back(make_pair(x, 0));
    dis[x] = 0;
    while (!que.empty())
    {
        pair <int, int> Curr = que.back();
        if (Curr.second > dis[Curr.first])
        {
            que.pop_back();
            continue;
        }
        que.pop_back();
        int siz = G[Curr.first].size();
        for (int i = 0;i < siz;i++)
            if (dis[G[Curr.first][i].first] > 
            dis[Curr.first] + G[Curr.first][i].second)
            {
                dis[G[Curr.first][i].first] =
                dis[Curr.first] + G[Curr.first][i].second;
                if (G[Curr.first][i].second == 0)
                    que.push_front(make_pair(G[Curr.first][i].first, 
                    dis[G[Curr.first][i].first]));
                else
                    que.push_back(make_pair(G[Curr.first][i].first, 
                    dis[G[Curr.first][i].first]));
            }
    }
    return dis[N];
}
bool Chk(int x)
{
    BuildGraph(x);
    return Bfs(1) <= K;
}
int main()
{
    scanf("%d%d%d", &N, &M, &K);
    int L = -1, R = 0;
    for (int i = 1;i <= M;i++)
    {
        scanf("%d%d%d", &u[i], &v[i], &w[i]);
        R += w[i];
    }
    R++;
    int INF = R;
    while (L < R - 1)
    {
        int mid = (L + R) / 2;
        if (Chk(mid))
            R = mid;
        else
            L = mid;
    }
    printf("%d", (R == INF ? -1 : R));
    return 0;
}
```

---

## 作者：Chevalier (赞：1)

二分的部分请参照其他题解，他们讲的很详细，我就不再赘述了。在这里我提供一种与众不同的check方法——双端队列BFS。

具体做法就是在普通的BFS的基础上，将原来的队列改成双端队列。每次取出队头x后更新节点y时，如果x、y之间的边权为1，就把y从队尾入队，否则从队首入队。

为什么可以这样做呢？在这种类型的图中，通过这样的手段维护双端队列，双端队列中的点到源点的距离是具有单调性的。

证明很显然：

	在边权全部是1的图中进行BFS时，队列中的点显然具有单调性。在这个基础上，如果取出的队头为x，x到y的边权为0,那么y到源点的距离就等于x，此时将y塞到x之前在的位置（队头），队列就相当于没取出x，不会破坏原本就存在的单调性。
    
    证毕

就这样双端队列起到了dijkstra中单调队列的作用，剩下的按照dijkstra打就行。实际上这里用到的双端队列BFS就是特殊情况下的简易版dijkstra。

这种方法适用于在边权只有0和1的图上跑最短路，跑一次的时间复杂度仅为O(N+P)。且代码实现十分清爽。

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<deque>
using namespace std;
int n,m,k,mx=0,d[1010],v[1010];//v=1表示在队列中，=2表示已经出过队了。
int tot,head[1010],ver[20010],nxt[20010],edge[20010];
deque<int> q;

void add(int x,int y,int z){
	ver[++tot]=y;
	edge[tot]=z;
	nxt[tot]=head[x];
	head[x]=tot;
}

bool check(int mid){
	memset(d,0x3f,sizeof d);
	memset(v,0,sizeof v);
	v[1]=1;d[1]=0;
	q.push_back(1);
	while(q.size()){
		int x=q.front();q.pop_front();
		v[x]=2;
		for(int i=head[x];i;i=nxt[i]){
			int y=ver[i],z=edge[i];
			if(v[y]==2)continue;
			if(z>mid)z=1;
			else z=0;
			d[y]=min(d[y],d[x]+z);
			if(v[y])continue;
			if(z)q.push_back(y);
			else q.push_front(y);
		}
	}
	if(!v[n]||d[n]>k)
		return 0;
	return 1;
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		mx=max(mx,z);
		add(x,y,z);
		add(y,x,z);
	}
	int l=0,r=mx+1;
	while(l<r){
		int mid=(l+r)>>1;
		if(check(mid))r=mid;
		else l=mid+1;
	}
	if(r==mx+1)puts("-1");
	else printf("%d",l);
	return 0;
}
```

---

## 作者：bztMinamoto (赞：1)

首先我们可以发现，本题的答案是具有单调性的，因为当付更少钱可以时，付更多的钱必然也是可以的。所以我们可以二分，判断当答案为mid时是否可行

怎样判断mid是否可行呢？我们可以将长度小于等于mid的边视为长度为0的边，大于mid的边视为长度为1的边，最后用dijkstra检查d[n]是否小于等于k即可

具体细节看注解，上代码
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cmath>
#include<cstring>
#define a(a,b,c) for(int a=b;a<=c;a++)
#define b(a,b,c) for(int a=b;a>=c;a--)
using namespace std;
const int N=1050,M=20050,INF=0x3f3f3f3f;
struct ab{
    int y,z;
};
struct node{
    int from,to,cost;
};
node a[M];
int ver[M],Next[M],head[N],used[N],d[N],edge[M];
int n,m,tot,l=0,r=0,ans=-1,k;
void add(int x,int y,double z)
{
    ver[++tot]=y,edge[tot]=z,Next[tot]=head[x],head[x]=tot;
    return;
}
bool operator < (ab x,ab y)
{
    return x.z>y.z;
}
void dijkstra(int x)
{
//堆优化的dijkstra
    priority_queue<ab> q;
    d[x]=0;
    ab a;
    a.y=x,a.z=0;
    q.push(a);
    while(!q.empty())
    {
        int x=q.top().y;
        q.pop();
        if(used[x]) continue;
        if(x==n) return;
        used[x]=1;
        for(int i=head[x];i;i=Next[i])
        {
            int y=ver[i],z=edge[i];
            if(d[y]>d[x]+z)
            {
                d[y]=d[x]+z;
                ab a;
                a.y=y,a.z=d[y];
                q.push(a);
            }
            
        }
    }
    return;
}
bool check(int mid)
{
    memset(d,0x3f,sizeof(d));
    memset(used,0,sizeof(used));
    tot=0;
    a(i,1,n)
    head[i]=0;
    a(i,0,m-1)
    {
        int x=a[i].from,y=a[i].to,z=a[i].cost;
        if(z>mid) z=1;
        else z=0;
        add(x,y,z);
        add(y,x,z);
    }
    //建图
    dijkstra(1);
    if(d[n]>k) return false;
    return true;
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    a(i,0,m-1)
    scanf("%d%d%d",&a[i].from,&a[i].to,&a[i].cost),r=max(r,a[i].cost);
    while(l<=r)
    {
        int mid=(l+r)/2;
        if(check(mid)) ans=mid,r=mid-1;
        else l=mid+1;
        //二分答案
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：OptimusPrime_L (赞：1)

# 分析

【瞎扯】

不好意思我又要瞎扯了，还是提醒各位审题！

拿到题目看了一遍然后默默地想起了【BZOJ 2763 飞行路线】（别找了这题我压根儿就没过）。题面完全一毛一样的！然后所以这是分层图？等下我们图论专题才刚开始上了半天就给我做分层图？哦是吗我要投诉清北学堂。

……又没看题目

【正经】

首先我们来一起读题【雾

    As it turns out, the phone company is willing to provide Farmer John with K (0 ≤ K < N) lengths of cable for free. Beyond that he will have to pay a price equal to the length of the longest remaining cable he requires (each pair of poles is connected with a separate cable), or 0 if he does not need any additional cables.

本题最重要的一句话↑，它告诉我们，电信公司【移动：？】愿意支付其中k条电话线的费用，其余的电话线中，FJ支付最贵的一条（电信公司真差劲，下次找移动【电信：？】）。简单想一下：贪心的想法，最佳情况，我们找前k贵的让电信公司付钱，第k+1贵的让FJ付钱。

假设我们有一个check(int c)来检查当我们支付价格为c的电话线时，我们是否能成功让整个线路运行起来。有了它我们就可以肆无忌惮地二分了！原因很简单：显然是单调的且我们有check()来帮我们检查可行性。

那么本题的终点就转移到了如何写出check()函数。

假如当前我们二分到mid，我们将所有权值大于mid的所有电话线的权值全部设置为1（意味着我们需要消耗一次【电话线抵用券】来假设电话线），而权值小于mid则全部设置为0（我们不需要让FJ付款，也不需要让电信掏钱）。对于这个0/1的图跑SPFA，如果我们发现最短路径长度大于k，意味着这个k然而并不可行，我们缩小左边界继续二分；若我们发现它小于等于k，说明我们仍然有可能有更优解，缩小右边界继续二分。

本题的一大重点还是搞清楚left/mid/right的关系，或者说这就是二分的一个难点吧。

# 程序
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2000, MAXM = 20000;
int n, m, k, Head[MAXN], Edge_Count, ans, G[MAXN][MAXN];
struct edge
{
    int Next, From, Aim, Weight;
}Edge[MAXM];
void insert(int u, int v, int w)
{
    Edge[++Edge_Count] = (edge){Head[u], u, v, w};
    Head[u] = Edge_Count;
}
bool check(int Len)
{
    // 初始化G数组为-1,-1代表没有边相连
    for (int i = 1; i < MAXN; i++)
        for (int j = 1; j < MAXN; j++)
            G[i][j] = -1;
    memset(dis,0x3F,sizeof(dis));
    for (int i = 1; i <= Edge_Count; i++)
        if (Edge[i].Weight > Len)
            G[Edge[i].From][Edge[i].Aim] = 1, G[Edge[i].Aim][Edge[i].From] = 1;
        else
            G[Edge[i].From][Edge[i].Aim] = 0, G[Edge[i].Aim][Edge[i].From] = 0;
    // 0:有边相连,且权值小于Len
    // 1:有边相连,且权值大于Len,消耗一次电话线抵用券
    // 以下标准SPFA
    queue<int> Q;
    Q.push(1);
    int dis[MAXN];
    dis[1] = 0;
    bool vis[MAXN];
    vis[1] = true;
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (int i = 1; i <= n; i++)
        {
            if (G[u][i] != -1 && dis[u]+G[u][i] < dis[i])
            {
                dis[i] = dis[u]+G[u][i];
                if (!vis[i])
                    vis[i] = true, Q.push(i);
            }
        }
        vis[u] = false;
    }
    // 若最少的小号次数大于k,这种情况不可信,返回假
    // 否则说明是一个可行解,但不一定是最优解,返回真继续二分
    if (dis[n] > k)
        return false;
    else
        return true;
}
int main()
{
    freopen("tele.in","r",stdin);
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        insert(u,v,w);
        insert(v,u,w);
    }
    int l = 0, r = 1000000000, mid;
    bool flag = false;
    while (l < r)
    {
        mid = (l+r)/2;
        if (check(mid))
            r = mid, flag = true;
        else
            l = mid + 1;
    }
    // flag说明我们是否找到过可行的解
    // 若没有,输出-1
    if (flag)
        cout << l << endl;
    else
        cout << -1 << endl;
    return 0;
}
```

---

## 作者：John_Fu (赞：1)

这道题用二分枚举答案。枚举一个值，验证这个值是否满足修筑成本能达到这么小。（假设当前二分枚举到mid这个值）


跑SPFA，把所有大于mid的边的边权都看作1，其余看作0.若终点的距离大于k，也就是说有不止k条边大于等于mid，无法全部报销，那么修筑成本将大于mid，于是重新枚举mid。假如终点n的距离小于等于mid，那么修筑成本能达到mid这么小，于是用mid更新答案，但是要枚举更小的mid值，看修筑成本能不能更小。


```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iostream>
#include<queue>
#include<cstdlib>
using namespace std;
int n,m,k;
struct E{
    int v,next,dis;
};
E edge[20010];
int sum=0;
int fir[1010];
int read(){
    char c;
    do{
        c=getchar();
    }while(c<'0'||c>'9');
    int ret=0;
    do{
        ret=ret*10+c-48;
        c=getchar();
    }while(c>='0'&&c<='9');
    return ret;
}
void add(int u,int v,int dis){
    edge[++sum].next=fir[u];
    fir[u]=sum;
    edge[sum].v=v;
    edge[sum].dis=dis;
}
int mid;
int dis[1010];
bool ex[1010];
void SPFA(){
    queue<int> q;
    q.push(1);
    ex[1]=1;
    dis[1]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        ex[u]=0;
        for(int i=fir[u];i;i=edge[i].next)
        {
            int v=edge[i].v;
            int d=edge[i].dis>=mid?1:0;
            if(dis[v]>dis[u]+d)
            {
                dis[v]=dis[u]+d;
                if(!ex[v])
                {
                    ex[v]=1;
                    q.push(v);
                }
            }
        }
    }
}
int anss=999999999;
int main(){
    cin>>n>>m>>k;
    int x,y,z;
    for(int i=1;i<=m;i++)
    {
        x=read();y=read();z=read();
        add(x,y,z);
        add(y,x,z);
    }
    int l=0;
    int r=1000000;
    while(l<=r)
    {
        memset(dis,63,sizeof(dis));
        memset(ex,0,sizeof(ex));
        mid=(l+r)>>1;
        SPFA();
        if(dis[n]>k)
        {
            l=mid+1;
        }
        else if(dis[n]<=k)
        {
            r=mid-1;
            anss=min(anss,mid);
        }
    }
    if(anss>999999990)
    {
        cout<<-1;return 0;
    }
    cout<<anss;
    return 0;
}
```

---

## 作者：Memorize (赞：1)

这道题很容易想到二分最大的电话线长度 然后最重要的就是验证

（实话说我最先看标签是搜索 所以我写的是宽搜 然后RE... 然后看的题解第一句话都是最短路...被坑了...）

那么最短路的想法便应运而生了

当边权大于我们二分的答案时候 我们就让dist+1 否则就是原来的dist

核心代码：

```cpp
if(e[i].w<=len&&dist[e[i].to]>dist[p])
            {
                dist[e[i].to]=dist[p];
                if(!vis[e[i].to])
                {
                    vis[e[i].to]=true;
                    que[++qtail]=e[i].to;
                }
            }
            else if(e[i].w>len&&dist[e[i].to]>dist[p]+1)
            {
                dist[e[i].to]=dist[p]+1;
                if(!vis[e[i].to])
                {
                    vis[e[i].to]=true;
                    que[++qtail]=e[i].to;
                } 
            }
剩下的就是裸裸的二分框架和spfa啦！
```

---

## 作者：kczno1 (赞：1)

分析问题后，我们发现，答案只取决于那条第k+1长的边。（先特判0和-1）因此想到二分这条边

我们先将边按长度排序。选择第x长的边后1-x的边赋为0，x+1到p的赋为1，跑一遍最短路，得到的g[n]跟k比一下就好了。

···pascal












```cpp
var
 n,p,k,i,x,y:longint;
 len,num:array[1..10010] of longint;
 t,a,g:array[1..2010] of longint;
 l:array[1..10010*2,1..3] of longint;
 ing:array[1..2010] of boolean;
procedure swap(var x,y:longint);
var t:longint;
begin
 t:=x;x:=y;y:=t;
end;
procedure sort(l,r: longint);
      var
         i,j,x: longint;
      begin
         i:=l;
         j:=r;
         x:=len[(l+r)>>1];
         repeat
           while len[i]<x do
            inc(i);
           while x<len[j] do
            dec(j);
           if not(i>j) then
             begin
                swap(len[i],len[j]);swap(num[i],num[j]);
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort(l,j);
         if i<r then
           sort(i,r);
      end;
procedure jia(var x:longint);
begin
 if x=n then x:=1
 else inc(x);
end;
function spfa:boolean;
var i,head,tail,now:longint;
begin
 for i:=2 to n do begin g[i]:=k+1;ing[i]:=false; end;//初值赋为k+1是一个小优化，因为我们实际并不求g[n]，只求g[n]与k的大小关系
 head:=0;tail:=1;a[1]:=1;
 repeat
  jia(head); now:=a[head];
  ing[now]:=false;
  i:=t[now];
  while i<>0 do
  begin
   if g[l[i,1]]>g[now]+l[i,2] then
   begin
    if l[i,1]=n then exit(true);//一旦点n被更新就跳出
    g[l[i,1]]:=g[now]+l[i,2];
    if not ing[l[i,1]] then begin ing[l[i,1]]:=true;jia(tail);a[tail]:=l[i,1]; end;
   end;
   i:=l[i,3];
  end;
 until head=tail;
 exit(false);
end;
function ok(x:longint):boolean;
var i:longint;
begin
 for i:=1 to x do
 begin
  l[num[i],2]:=0;l[num[i]+p,2]:=0;
 end;
 for i:=x+1 to p do
 begin
  l[num[i],2]:=1;l[num[i]+p,2]:=1;
 end;
 exit(spfa);
end;
procedure try;
var
 l,r,mid:longint;
begin
  l:=0;r:=p;
 while l+1<r do
 begin
  mid:=(l+r)>>1;
  if ok(mid) then r:=mid
  else l:=mid;
 end;
 writeln(len[r]);
end;
begin assign(input,'1.in') ;reset(input);
 readln(n,p,k);
 for i:=1 to p do
 begin
  read(x,y,len[i]);num[i]:=i;//记录一下该边对应的编号
  l[i,3]:=t[x];t[x]:=i;l[i,1]:=y;
  l[i+p,3]:=t[y];t[y]:=i+p;l[i+p,1]:=x;
 end;
 if not ok(p) then writeln(-1)
 else
 if ok(0) then writeln(0)
 else
 begin
  sort(1,p);
  try;
 end;
end.
···
```

---

## 作者：Created_equal1 (赞：1)

看到题目，很容易想到二分答案。

那么check函数怎么写呢？

设当前二分的答案为ans，那么我们如果能够找到一条1到n的路径，使得路径上边权>ans的边的个数不大于k就代表该答案可行。

check函数可以用最短路来实现。

```cpp


#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const size_t Max_N(1050);
const size_t Max_P(20050);

size_t N;
unsigned int P;
unsigned int K;

unsigned int Total;
unsigned int Head[Max_N];
unsigned int To[Max_P];
unsigned int Weight[Max_P];
unsigned int Next[Max_P];

unsigned int Left, Right, Mid;

inline
void Add_Edge(const size_t &s, const size_t &t, const unsigned int &w)
{
    ++Total, To[Total] = t, Weight[Total] = w, Next[Total] = Head[s], Head[s] = Total;
}

void init()
{
    unsigned int a, b, l;
    
    Left = 0;
    
    scanf("%u%u%u", &N, &P, &K);
    
    while (P--)
    {
        scanf("%u%u%u", &a, &b, &l);
        Add_Edge(a, b, l);
        Add_Edge(b, a, l);
        Right = max(Right, l);
    }
}

unsigned int Dist[Max_N];
bool In_Q[Max_N];
bool Check(const unsigned int &d)
{
    memset(Dist, 0X7F, sizeof(Dist));
    
    queue<unsigned int> Q;
    Q.push(1);
    Dist[1] = 0;
    In_Q[1] = true;
    
    unsigned int Top;
    while (Q.size())
    {
        Top = Q.front();
        Q.pop();
        In_Q[Top] = false;
        
        for (size_t i = Head[Top];i;i = Next[i])
            if (Dist[To[i]] > Dist[Top] + (Weight[i] > d))
            {
                Dist[To[i]] = Dist[Top] + (Weight[i] > d);
                if (!In_Q[To[i]])
                {
                    In_Q[To[i]] = true;
                    Q.push(To[i]);
                }
            }
    }
    
    return Dist[N] <= K;
}

void slove()
{
    while (Left < Right)
    {
        Mid = Left + ((Right - Left) >> 1);
        if (Check(Mid))
            Right = Mid;
        else
            Left = Mid + 1;
    }
    
    if (Check(Left))
        printf("%u", Left);
    else
        printf("-1");
}

int main()
{
    init();
    
    slove();
    
    return 0;
}

```

我自己还yy了一个做法。。没写所以不知道对不对

设dist[i][k]表示从1到i的路径中，k条免费可以获得的最优解。

dist[i][0]=min{max(dist[j][0],w(j,i))}

dist[i][k]=min{max(dist[j][k], w(j,i)),dist[j][k-1]}

然后把这个状态转移方程扔到spfa里面去。。

最后ans=min{dist[n][k]}


---

## 作者：fdszlzl (赞：0)

[P1948 [USACO08JAN]电话线Telephone Lines](https://www.luogu.org/problem/P1948)

### 题解一水的二分+最短路，这里提供一种二分+dfs的做法。

二分一个最大花费mid：小于等于mid路径没有花费，大于mid的路径消耗一次花费。

dfs一条可以到n且消耗小于等于K的路径即可。

设u点的花费为cost[u]，则连接点v本次的花费为cost[u]+(e[i].w>mid)

若v点之前已经走过：

1、如果 cost[v] <= cost[u]+(e[i].w>mid) 则本次不优，剪枝  
2、否则 更新cost[v] = cost[u]+(e[i].w>mid)

最终得到cost[n]，若cost[n]大于K，说明mid太小，加大，否则mid变小。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,m,k,K,vex[1005],vis[1005],cost[1005],f;
struct edge {
	int u,v,w,next;
}e[20005];

void add(int u,int v,int w){
	k++;
	e[k].u=u;
	e[k].v=v;
	e[k].w=w;
	e[k].next=vex[u];
	vex[u]=k;
	return;
}

void dfs(int u,int mid){
	if(f||cost[u]>K) return;
	if(u==n) {
		f=1;
		return;
	}
	for(int i=vex[u];i;i=e[i].next){
		int v=e[i].v;
		if(cost[u]+(e[i].w>mid)>=cost[v]) continue;
		cost[v]=cost[u]+(e[i].w>mid);
		dfs(v,mid);		
	}
	return;
}

int check(int mid){
	memset(cost,0x3f,sizeof(cost));
	f=cost[1]=0;
	dfs(1,mid);
	return cost[n]>K;
}

int main(){
	int u,v,w,maxn=0;
	cin>>n>>m>>K;
	for(int i=1;i<=m;i++){
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
		maxn=max(maxn,w);
	}
	int l=1,r=maxn,mid;
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	if(l==maxn+1) cout<<-1;
	else cout<<l;
	return 0;
} 
```




---

## 作者：卡车cckk (赞：0)

简单粗暴

二分花费

当二分到花费为c时

跑SPFA
对每次SPFA，求花费小于c时，从1到n最少需要电信公司帮忙连接电线杆对的个数
（最好画图分析）

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
struct Edge
{
	int to,hp;
};
struct Dian
{
	int cost;
	vector<Edge> edge;
}dian[1003];
int n,m,k,dist[1003],bj[1003];
//dist即到当前电线杆我需要电信公司帮忙出钱的电线杆对
bool spfa(int wh)
{
	queue<int> q;
	q.push(1);memset(dist,0x3f,sizeof(dist));memset(bj,0,sizeof(bj));dist[1]=0;
	while(!q.empty())
	{
		int a=q.front();q.pop();
		for(int i=0;i<dian[a].edge.size();i++)
		{
			int b=dian[a].edge[i].to;
			int hp=dian[a].edge[i].hp;
			if(dist[a]+(hp>wh)<dist[b])
			{
				dist[b]=dist[a]+(hp>wh);
				if(bj[b]!=233)
				{
					bj[b]=233;q.push(b);
				}
			}
		}
		bj[a]=0;
	}
	if(dist[n]<=k)return true;
    //如果我最少的求助数不多于上限，则这个方案通过
	return false;
}
int minn=0,maxx;
int findd()//粗劣的二分。。。轻喷QAQ
{
	int mid;
	while(minn+1<maxx)
	{
		mid=(minn+maxx)/2;
		if(spfa(mid))maxx=mid;
		else minn=mid;
	}
	if(spfa(minn))return minn;
	else if(!spfa(minn)&&!spfa(maxx))return -1;
	else return maxx;
}
int x,y,z;
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		if(x==y)continue;
		dian[x].edge.push_back(Edge{y,z});
		dian[y].edge.push_back(Edge{x,z});
		maxx=max(maxx,z);
	}
	printf("%d",findd());
	return 0;
}

```

---

## 作者：李若谷 (赞：0)

### 本题有两种做法，二分+bfs和分层图最短路

二分的已经很多人讲了，这里主要讲分层图最短路。


分层图就是把图中节点分开，变成许多不同的状态。

本题可以仿照动态规划的思想，用D[x,p]表示1号到x号图中已经指定了p条免费电缆是，最贵的经过的电缆最小是多少。若有一条从x到y长度为z的无向边，应该用max(D[x,p],z)更新D[y,p]的最小值，用D[x,p]更新D[y,p+1]的最小值。


很显然这种做法是有有效性的，但是，我们可以用spfa或dij来跑一遍，使得D数组不能更新。这样也解决了后效性。用spfa来做时间复杂度为 O(tNP)，其中t为常数。这道题没有卡spfa。

代码
```cpp
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
const int N = 1001;
const int M = 20001;
int n,m,k;
struct EDGE{
	int next;
	int to;
	int len;
}edge[M];
struct NODE{
	int pos;
	int free;
};
queue <NODE> q;
int head[N];
bool vis[N][N];
int cnt = 0;
int dist[N][N];
void add_edge(int x,int y,int len)
{
	edge[++cnt].to = y;
	edge[cnt].len = len;
	edge[cnt].next = head[x];
	head[x] = cnt;
}
void spfa()
{
	memset(dist,0x3f,sizeof dist);
	q.push((NODE){1,0});
	vis[1][0] = 1;
	dist[1][0] = 0;
	while(!q.empty())
	{
		NODE top = q.front();
		q.pop();
		vis[top.pos][top.free] = 0;
		for(int i=head[top.pos];i;i=edge[i].next)
		{
			int y = edge[i].to;
			if(max(dist[top.pos][top.free],edge[i].len) < dist[y][top.free])
			{
				dist[y][top.free] = max(dist[top.pos][top.free],edge[i].len);
				if(!vis[y][top.free])
				{
					vis[y][top.free] = 1;
					q.push((NODE){y,top.free});
				}
			}

			if(top.free < k && dist[y][top.free+1] > dist[top.pos][top.free])
			{
				dist[y][top.free+1] = dist[top.pos][top.free];
				if(!vis[y][top.free+1])
				{
					q.push((NODE){y,top.free+1});
					vis[y][top.free+1] = 1;
				}
			}
		}
	}

}

// dist[next][top.free] --> max(dist[top.pos][top.free] , edge[i].len
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++)
	{
		int x,y,l;
		scanf("%d%d%d",&x,&y,&l);
		add_edge(x,y,l);   //无向图加条边
		add_edge(y,x,l);
	}
	spfa();
	if(dist[n][k] == 0x3f3f3f3f)
		printf("-1\n");
	else
		printf("%d\n",dist[n][k]);
}
```





以上内容部分借鉴与算法竞赛进阶指南。



---

