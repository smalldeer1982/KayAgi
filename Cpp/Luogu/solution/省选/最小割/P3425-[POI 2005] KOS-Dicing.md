# [POI 2005] KOS-Dicing

## 题目描述

掷骰子是一种双人游戏，它的结果是完全随机的。最近它在整个 Byteotia 变得非常流行。在 Byteotia 的首都甚至有一个特别的掷骰子业余爱好者俱乐部。俱乐部的老主顾们花时间互相聊天并每隔一阵子就和一个随机选择的对手玩这他们最喜欢的游戏。一天中赢得最多游戏的人会得到“幸运者”头衔。有时晚上俱乐部很安静，只有很少的比赛。这是哪怕赢一场也能获得“幸运者”头衔的时间。

很久很久以前有一个很不走运的人，叫 Byteasar，赢得了这个光荣的头衔。他被深深地震惊了以至于完全忘了他已经赢了多少场。现在他想知道他有多幸运，以及幸运之神是否最终会向他微笑——也许他的运气会变好？他确切地知道在那个幸运的晚上有多少场游戏以及是谁玩的。然而，他不知道结果。Byteasar 希望查明至少要赢几场才能获得“幸运者”头衔。做个好人，帮他满足他的好奇心吧！

- - -

写一个程序：

对于每场游戏读入这场游戏的一对玩家。

找到最小的数 $k$，使得存在一个游戏结果的集合，其中赢最多的玩家赢了 $k$ 场。

输出数 $k$ 和找到的集合中游戏的结果。

玩家从 $1$ 到 $n$ 编号。

## 说明/提示

$1\le n,m\le 10^4$。

样例：

![](https://szkopul.edu.pl/problemset/problem/8OrJo8TOlY9pynt7Tr9jMzzW/site/images/OI12/koszad-img2.gif)

## 样例 #1

### 输入

```
4 4
1 2
1 3
1 4
1 2```

### 输出

```
1
0
0
0
1```

# 题解

## 作者：T_Q_X (赞：6)

## 二分+网络流
- 看到"最大值最小",显然要二分最少赢多少场。
- 源点向每一个比赛连一条流量为1的边，表明每个比赛只能赢一次
- 每个比赛向2位选手各连一条流量为1的边，表明每个比赛只能有一个人赢
- 最后每个选手向汇点连一条流量为mid的边，如果总流量>=比赛数，那么这个做法可行
- 等等，要输出方案！
- 每一个比赛向哪一个选手连的边流量是1，就代表这个选手赢了
- 好吧，下面就是我的code


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const int p=2e4;
const int inf=0x3f3f3f3f;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,m,U[N],V[N],de[N],first[N],cur[N],cnt,dis[N],s,t;
struct node{
	int v,w,nxt;
}e[N];
inline void add(int u,int v,int w){
   e[++cnt].v=v;e[cnt].w=w;
   e[cnt].nxt=first[u];first[u]=cnt;
}
inline int bfs(){
	queue<int>q;
	memset(dis,-1,sizeof(dis));
	dis[s]=0;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=first[u];i;i=e[i].nxt){
			int v=e[i].v;
			if(e[i].w>0&&dis[v]==-1){
				dis[v]=dis[u]+1;
				q.push(v);
				if(v==t) return 1;
			}
		}
	}
	return 0;
}
inline int dfs(int x,int f){
	if(x==t||f==0) return f;
	int used=0;
	for(int& i=cur[x];i;i=e[i].nxt){
		if(e[i].w&&dis[e[i].v]==dis[x]+1){
			int w=dfs(e[i].v,min(f,e[i].w));
			if(!w) continue;
			used+=w;
			f-=w;
			e[i].w-=w;
			e[i^1].w+=w;
			if(f==0) break;
		}
	}
	if(!used) dis[x]=-1;
	return used;
}
inline int dinic(){
	int ans=0;
	while(bfs()){
		memcpy(cur,first,sizeof(first));
		ans+=dfs(s,inf);
	}
	return ans;
}//网络流板子 
inline int check(int x){
	memset(first,0,sizeof(first));
	cnt=1;s=n+p+1,t=s+1;
	for(int i=1;i<=m;i++){
		add(s,i,1);add(i,s,0);
		add(i,U[i]+p,1);add(U[i]+p,i,0);
		add(i,V[i]+p,1);add(V[i]+p,i,0);
	}
	for(int i=1;i<=n;i++)
		add(i+p,t,x),add(t,i+p,0);
	return dinic()>=m;
}//本题的重点：建图 
inline int Print(){
	for(int i=0;i<m;i++){
		if(e[i*6+4].w==0) puts("1");
		else puts("0");
	}
}//打印方案 
int main(){
	n=read();m=read();
	for(int i=1;i<=m;i++)
		U[i]=read(),V[i]=read();
	int l=m/n,r=m;
	while(l<r){
		int mid=(l+r)>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}//二分 
	printf("%d\n",l);
	check(l);
	Print();
	return 0;
}
```


---

## 作者：MSqwq (赞：5)

### 前置芝士：网络流  
比较好的一道网络流题了，比较适合来练习思维和构图能力，还是老生常谈的一句话：图论的题就是构图 $+$ 跑板子  
首先~~最难~~的一步，画出源点和汇点这里用 st 和 en 表示 
![](https://cdn.luogu.com.cn/upload/image_hosting/lmxdtbnp.png)
好然后我们考虑将起点和每一场比赛连线，容量为 1，这个的意思就是每个比赛最多有一个人获胜，这里用粉色表示，~~因为粉色好康~~  
![](https://cdn.luogu.com.cn/upload/image_hosting/q6mbio13.png)
然后将每一场比赛和相对应的两个人连线，容量为 1，代表这个人获胜或者是不获胜，这里用绿色表示  
![](https://cdn.luogu.com.cn/upload/image_hosting/5p4n7cwf.png)
然后将所有人和终点连线 
![](https://cdn.luogu.com.cn/upload/image_hosting/bh7wv3a9.png)  
那么问题来了，容量为多少呢？  
这个值我们不确定对吧，表示的是胜场的场数，所以我们要去枚举，怎么枚举呢 $1-n$ 依次枚举？那岂不直接上天。很容易可以发现这个其中是有单调性的，如果给的容量越大，那么胜场就会相应的变大，所以我们考虑二分答案，好像 二分答案 $+$ 网络流 已经成固定套路了    
此题有可能还过不了，可能会 T 掉，所以简单的再观察亿下，可以发现，我们画的是二分图，所以曾广路会很短，所以我们可以缩小退出 $dfs$ 当然如果你用的是 $dinic$ 就当我没说啦，因为是到源点的距离，所以也无所谓啦，我这种只是提醒使用 $ISAP$ 的同学qwq      
然后就轻松的解决了这一题啦，代码也就很简单了  
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#define ll long long
using namespace std;
const int N=300010,M=80000010;
struct MS{
	int from,to,next,z;
}e[M];
int elast[N],cur[N],k=1;
void print(int x,int y,int z){cout<<x<<"->"<<y<<"="<<z<<endl;}
void add(int x,int y,int z)
{
	//print(x,y,z);
	e[++k].to=y,e[k].from=x,e[k].z=z,e[k].next=elast[x],elast[x]=k;
	e[++k].to=x,e[k].from=y,e[k].z=0,e[k].next=elast[y],elast[y]=k;
}
struct MSQWQ{
	int x,y;
}a[N];
int n,m;
int ans;
int st,en;
int dis[N],cnt[N];
void bfs(int en)
{
	queue<int>q;
	q.push(en);
	for(int i=0;i<=N-10;i++)cur[i]=elast[i],dis[i]=-1,cnt[i]=0;
	dis[en]=0;
	cnt[0]=1;
	while(!q.empty())
	{
		int now=q.front();q.pop();
		for(int i=elast[now];i;i=e[i].next)
		{
			int to=e[i].to;
			if(dis[to]==-1)
			{
				dis[to]=dis[now]+1;
				cnt[dis[to]]++;
				q.push(to);
			}
		}
	}
}
int dfs(int x,int flow)
{
	if(x==en)return flow;
	int d=0;
	for(int i=cur[x];i;i=e[i].next)
	{
		cur[x]=i;
		int to=e[i].to;
		if(e[i].z>0&&dis[x]==dis[to]+1)
		{
			int tmp=dfs(to,min(e[i].z,flow-d));
			e[i].z-=tmp;
			e[i^1].z+=tmp;
			d+=tmp;
			if(d==flow||dis[st]>=666)return d;
		}
	}
	if(dis[st]>=666)return d;
	cnt[dis[x]]--;
	if(cnt[dis[x]]==0)dis[st]=666;
	dis[x]++;
	cur[x]=elast[x];
	cnt[dis[x]]++;
	return d;
}
int L,R,mid,qans;
int id[N];
bool check(int mid)
{
	k=1;
	memset(elast,0,sizeof(elast));
	for(int i=1;i<=m;i++)add(st,i,1);
	for(int i=1;i<=m;i++)
	{
		id[i]=k+1;
		add(i,m+a[i].x,1);
		add(i,m+a[i].y,1);		
	}
	for(int i=1;i<=n;i++)add(m+i,en,mid);
	ans=0;
	bfs(en);
	while(dis[st]<666)ans+=dfs(st,1e9);
	if(ans>=m)return true;
	return false;
}
int main()
{
	scanf("%d%d",&n,&m);
	st=0,en=n+m+1;
	for(int i=1;i<=m;i++)scanf("%d%d",&a[i].x,&a[i].y);
	L=m/n,R=m;
	while(L<=R)
	{
		mid=(L+R)/2;
		if(check(mid))qans=mid,R=mid-1;
		else L=mid+1;
	}
	printf("%d\n",qans);
	check(qans);
	for(int i=1;i<=m;i++)
	{
		if(e[id[i]].z==0)printf("1\n");
		else printf("0\n");
	}
	return 0;
}
```


---

## 作者：ker_xyxyxyx_xxs (赞：2)

[P3425 [POI2005]KOS-Dicing](https://www.luogu.com.cn/problem/P3425)

题意非常简单，。

考虑建图。

1、源点向每一场比赛连边，边权为 $ 1 $，表示每一场比赛只能有一个人获胜。

2、每场比赛向它所对应的两个人连边，边权为 $ 1 $，表示这个人获胜或者输掉。

3、每个人向汇点连边。这个时候发现边权的意义为每个人胜利的场数，但我们不知道。但是思考一下（其实也是常见套路），容量越大胜场越多，具有单调性。考虑进行二分答案即可。如果总流量 $ \geq $ 比赛数，就合法，缩小容量。

Code

```cpp
# include <iostream>
# include <cstdio>
# include <queue>
# include <cstring>

using namespace std;

const int N = 2e6 + 5;
const int M = 1e7 + 5;
const int inf = 0x3f3f3f3f;
int S , T;

typedef struct {
	int x , y , z , next;
} Edge;
Edge edge[M];
typedef struct {
	int xuexsshuan , Kikyo;
}Yzj;
Yzj match[M];
int E = 1 , elast[N];
int n , m;

void add(int x , int y , int z) {
	E ++;
	edge[E].x = x;
	edge[E].y = y;
	edge[E].z = z;
	edge[E].next = elast[x];
	elast[x] = E;
}
int x;
int dis[N] , cnt[N];
void bfs(int start) {
	queue<int> q;
	q.push(start);
	dis[start] = 0;
	cnt[S] = 1;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = elast[cur] ; i ; i = edge[i].next) {
			int v = edge[i].y;
			if (dis[v] != -1) continue;
			dis[v] = dis[cur] + 1;
			q.push(v);
			cnt[dis[v]] ++;
		}
	}
}
int cur[N];
int dfs(int u , int flow) {
	if (u == T) return flow;
	int temp , delta = 0;
	for (int i = cur[u] ; i ; i = edge[i].next) {
		cur[u] = i;
		int v = edge[i].y;
		if (edge[i].z > 0 && dis[u] == dis[v] + 1) {
			temp = dfs(v , min(flow - delta , edge[i].z));
			edge[i].z -= temp;
			edge[i ^ 1].z += temp;
			delta += temp;
			if (delta == flow) return delta;
		}
	}
	if (dis[S] >= T) return delta;
	cur[u] = elast[u];
	if (-- cnt[dis[u]] == 0) dis[S] = T;
	cnt[++ dis[u]] ++;
	return delta;
}
int Isap() {
	int ans = 0;
	memset(cnt , 0 , sizeof cnt);
	memset(dis , -1 , sizeof dis);
	bfs(T);
	for (int i = 0 ; i <= T ; i ++) {
		cur[i] = elast[i];
	}
	while (dis[S] < T) ans += dfs(S , inf);
	return ans;
}
void init() {
	memset(elast , 0 , sizeof elast);
	E = 1;
}
int id[M];
bool check(int x) {
	init();
	for (int i = 1 ; i <= m ; i ++) {
		add(S , i , 1);
		add(i , S , 0);
	}
	for (int i = 1 ; i <= m ; i ++) {
		id[i] = E + 1;
		int attack = match[i].xuexsshuan , suffer = match[i].Kikyo;
		add(i , attack + m , 1);
		add(attack + m , i , 0);
		add(i , suffer + m , 1);
		add(suffer + m , i , 0);
	}
	for (int i = 1 ; i <= n ; i ++) {
		add(i + m , T , x);
		add(T , i + m , 0);
	}
	if (Isap() >= m) return true;
	else return false;
}
int main() {
	cin >> n >> m;
	S = 0 , T = n + m + 1;
	for (int i = 1 ; i <= m ; i ++) {
	    scanf("%d%d" , &match[i].xuexsshuan , &match[i].Kikyo);
	} 
	int l = m / n , r = m;
	int ans = 0;
	while (l <= r) {
		int mid = l + r >> 1;
		if (check(mid) == true) r = mid - 1 , ans = mid;
		else l = mid + 1;
	}
	printf("%d\n" , ans);
	check(ans);

	for (int i = 1 ; i <= m ; i ++) {
		if (edge[id[i]].z == 0) printf("1\n");
		else printf("0\n");
	}
	return 0;
}
```

---

## 作者：partychicken (赞：2)

### 为什么所有人做法都和我不一样

不会画图，全凭口胡

看到这道题，我们可以显然地把它转化为一个图论模型：

给一个无向图的的所有边定向，令出度最大的点出度最小

这个东西怎么搞呢？我们可以借鉴混合图判定欧拉回路的思想

显然，要解决这个问题还是要**二分答案**

然后，先给每条边随意定向，统计每个点的出度。可以发现，反悔实际上就是通过一条边把一个点的出度匀给其他点。

于是，就有了建图思路：（令二分出的答案为$x$）

- 源点连出度大于$x$的点，流量为差值

- 出度小于$x$的点连汇点，流量为差值

- 图中原有的边按照原方向连边，流量为$1$

如果左侧与原点相连的边全部满流，说明所有的点的出度都控制在了$x$以下，$check$通过。

输出方案的话，看原图每条边是否满流。满流则说明与原定向不同，并不难写。然而，我dinic封装了，边还放在了private里，于是。。。等我哪天有时间再补这个坑吧QAQ

以下是第一问代码


```
#include<bits/stdc++.h>

using namespace std;

const int inf=0x3f3f3f3f;

class MaxFlow
{
    private:
        struct Edge
        {
            int to,nxt,val;

            Edge():nxt(-1){}
            Edge(int to,int nxt,int val):to(to),nxt(nxt),val(val){}

            ~Edge(){}
        }e[500010];
        int head[10010],cnt;

        void addedge(int u,int v,int val)
        {
            e[++cnt]=Edge(v,head[u],val);
            head[u]=cnt;
        }

        queue<int>q;
        int dpth[10010];
        bool bfs(int s,int t)
        {
            memset(dpth,0,sizeof(dpth));
            q.push(s);
            dpth[s]=1;
            while(!q.empty())
            {
                int now=q.front();
                q.pop();
                for(int i=head[now];~i;i=e[i].nxt)
                {
                    int vs=e[i].to,valn=e[i].val;
                    if(dpth[vs]||!valn) continue;
                    dpth[vs]=dpth[now]+1;
                    q.push(vs);
                }
            }
            return dpth[t];
        }

        int dfs(int now,int fl,int t)
        {
            if(now==t||fl==0)
            {
                return fl;
            }
            int res=0;
            for(int i=head[now];~i;i=e[i].nxt)
            {
                int vs=e[i].to;
                if(dpth[now]!=dpth[vs]-1||!e[i].val) continue;
                int tmp=dfs(vs,min(fl-res,e[i].val),t);
                if(!tmp)
                {
                    dpth[vs]=0;
                }
                res+=tmp;
                e[i].val-=tmp;
                e[i^1].val+=tmp;
                if(res==fl) break;
            }
            return res;
        }

    public:
        MaxFlow(){}

        ~MaxFlow(){}

        void insedge(int u,int v,int val)
        {
            addedge(u,v,val);
            addedge(v,u,0);
        }

        int dinic(int s,int t)
        {
            int res=0;
            while(bfs(s,t))
            {
                res+=dfs(s,inf,t);
            }
            return res;
        }

        void init()
        {
            memset(head,-1,sizeof(head));
            cnt=-1;
        }
}a;

int n,m;

int dgr[10010];

struct Edge
{
    int to,nxt;

    Edge(){}
    Edge(int to,int nxt):to(to),nxt(nxt){}
}e[10010];
int head[10010],cnt;

void addedge(int u,int v)
{
    e[++cnt]=Edge(v,head[u]);
    head[u]=cnt;
}

bool check(long long x)
{
    a.init();
    int s=n+1,t=s+1;
    int sum=0;
    for(int i=1;i<=n;i++)
    {
        int tmp=dgr[i]-x;
        if(tmp>0)
        {
            a.insedge(s,i,tmp);
            sum+=tmp;
        }
        else if(tmp<0)
        {
            a.insedge(i,t,-tmp);
        }
        for(int j=head[i];j;j=e[j].nxt)
        {
            int vs=e[j].to;
            a.insedge(i,vs,1);
        }
    }
    int ans=a.dinic(s,t);
    return ans==sum;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        if(u==v) while(1)cout<<"fuck!";
        if(u>v) swap(u,v);
        addedge(u,v);
        dgr[u]++;
    }
    long long l=1,r=m;
    while(l<r)
    {
        long long mid=(l+r)>>1;
        if(check(mid))
        {
            r=mid;
        }
        else
        {
            l=mid+1;
        }
    }
    cout<<l<<'\n';
}
```

---

## 作者：oscar (赞：1)

【POI补全计划#9 POI2005 KOS】

思维难度算比较简单的一题了

二分后用网络流判定

建图分3部分

1.S->人，流量为二分的mid

2.人->比赛，流量为1（只有参赛选手需要连边）

3.比赛->T，流量为1

输出方案只需要记录每一场比赛的满流边连向那个人就行

**不要忘记初始化**

贴代码

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int MAXN=20010,inf=0x3f3f3f3f;
struct edge
{
    int v,f;
    edge *next,*rev;
}*h[MAXN],pool[MAXN*5];
const int S=20005,T=20006,SHIFT=10000;
int top;
inline void addedge(int u,int v,int c)
{
    edge *tmp=&pool[++top];tmp->v=v;tmp->f=c;tmp->next=h[u];h[u]=tmp;
    edge *pmt=&pool[++top];pmt->v=u;pmt->f=0;pmt->next=h[v];h[v]=pmt;
    tmp->rev=pmt;pmt->rev=tmp;
}
int level[MAXN];
queue<int> q;
inline bool mklevel()
{
    while(!q.empty())q.pop();
    memset(level,-1,sizeof(level));
    level[S]=0;
    q.push(S);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(edge *tmp=h[u];tmp;tmp=tmp->next)
        {
            if(tmp->f&&level[tmp->v]==-1)
            {
                level[tmp->v]=level[u]+1;
                q.push(tmp->v);
            }
        }
        if(level[T]!=-1)return true;
    }
    return false;
}
int dinic(int u,int minf)
{
    if(u==T)return minf;
    int totf=0,f;
    for(edge *tmp=h[u];tmp&&totf<minf;tmp=tmp->next)
    {
        if(tmp->f&&level[tmp->v]==level[u]+1)
        {
            if(minf-totf<tmp->f)f=dinic(tmp->v,minf-totf);
            else f=dinic(tmp->v,tmp->f);
            totf+=f;
            tmp->f-=f;
            tmp->rev->f+=f;
        }
    }
    if(!totf)level[u]=-1;
    return totf;
}
int n,m,a[MAXN],b[MAXN],ans[MAXN];
inline void getans()
{
    for(int i=1;i<=m;i++)
    {
        for(edge *tmp=h[i+SHIFT];tmp;tmp=tmp->next)
        {
            if(tmp->v!=T&&tmp->f==1)
            {
                if(tmp->v==a[i])ans[i]=1;
                else ans[i]=0;
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    if(!m)
    {
        printf("0\n");
        return 0;
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&a[i],&b[i]);
    }
    int l=1,r=10000;
    while(l<r)
    {
        int mid=(l+r)/2;
        memset(h,0,sizeof(h));
        top=0;
        for(int i=1;i<=n;i++)
        {
            addedge(S,i,mid);
        }
        for(int i=1;i<=m;i++)
        {
            addedge(a[i],i+SHIFT,1);
            addedge(b[i],i+SHIFT,1);
            addedge(i+SHIFT,T,1);
        }
        int totf=0;
        while(mklevel())totf+=dinic(S,inf);
        if(totf==m)
        {
            getans();
            r=mid;
        }
        else l=mid+1;
    }
    printf("%d\n",l);
    for(int i=1;i<=m;i++)
    {
        printf("%d\n",ans[i]);
    }
    return 0;
}
```

---

## 作者：asd_a (赞：1)

## 为什么网络流要二分！！！
残量网络万岁！！！  
我们大大可以从1到m枚举答案，每次将所有连向t的边流量加1  
根据残量网络复杂度事实上只跑了一次网络流  
现在只需要建图了  
s向每场比赛连条流量为1的边，表示每场比赛只有一个人能赢  
每场比赛向参赛者连边。  
每人向t 连边，然后像前面那样动态更新流量即可  
每次看最大流是否等于m（即都决出胜负）
Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
inline int rd(){
	int x=0,fl=1;char ch=getchar();
	for(;ch>'9'||ch<'0';ch=getchar())fl=(ch=='-'?-1:1);
	for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	return x*fl;
}
int fi[N],ne[N],to[N],w[N],tot=1;
void add(int x,int y,int z){ne[++tot]=fi[x];to[tot]=y;w[tot]=z;fi[x]=tot;}
void ad(int x,int y,int z){add(x,y,z);add(y,x,0);}
int n,m,dis[N],s,t,mf,pre[N];
bool bfs(){
	for(int i=1;i<=t;i++)
		dis[i]=-1;
	dis[s]=1;
	queue<int>q;
	q.push(s);
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=fi[x];i;i=ne[i]){
			if(!w[i]||dis[to[i]]!=-1)continue;
			dis[to[i]]=dis[x]+1;
			if(to[i]==t)return true;
			q.push(to[i]);
		}
	}
	return false;
}
int dfs(int x,int fl){
	if(x==t||!fl)return fl;
	int u,ans=0;
	for(int i=fi[x];i;i=ne[i]){
		if(!w[i]||dis[to[i]]!=dis[x]+1)continue;
		u=dfs(to[i],min(w[i],fl));
		w[i]-=u;w[i^1]+=u;fl-=u;ans+=u;
		if(!fl)break;
	}
	if(!ans||fl)dis[x]=-1;
	return ans;
}
int dinic(){
	int mxf=0,x;
	while(bfs())
		while(x=dfs(s,INT_MAX))
			mxf+=x;
	return mxf;
}//网络流板子
int main(){
	n=rd();m=rd();
	s=n+m+1;t=s+1;
	for(int i=1;i<=m;i++){
		int x,y;
		x=rd();y=rd();
		ad(s,i,1);
		ad(i,x+m,1);
		ad(i,y+m,1);
	}
	for(int i=1;i<=n;i++)
		pre[i]=tot+1,ad(i+m,t,1);//建图，存连向t的边
	for(int k=1;k<=m;k++){
		mf+=dinic();
		if(mf==m){
			printf("%d\n",k);
			break;
		}
		for(int i=1;i<=n;i++)
			w[pre[i]]++;//更新流量
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",w[fi[i]]);//fi[i]是连向y的边
	return 0;
}
```


---

## 作者：yllcm (赞：0)

考虑二分答案 $x$，问题转化为判断是否存在方案使得所有人赢的次数都小于 $x$。

### 方法一

花里胡哨做法.jpg

发现原题相当于给一个无向图定向，使得 $\forall i,\text{out}_i\leq x$。

考虑钦定一种定向方案然后调整。为了方便接下来的调整操作，我们把条件转化为 $\forall i,f(i)=(\text{in}_i-\text{out}_i)-(\text{deg}_i-2x)\geq 0$（其实就是考虑 $\text{in}_i-\text{out}_i$ 的范围，然后移了个项）。此时翻转一条边 $(u,v)$ 相当于 $f(u)\gets f(u)+2,f(v)\gets f(v)-2$。

此时我们令 $g(i)=f(i)/2$。那么把 $g(i)\geq 0$ 的和 $g(i)<0$ 的分别拉出来分成两类，建立如下模型：

* $g(i)\geq 0$，建边 $(S,i)$，流量 $g(i)$。
* $g(i)<0$，建边 $(i,T)$，流量 $-g(i)$。
* $(u,v)\in E$，建边 $(u,v)$，流量 $1$。

证明如上操作的正确性：对于 $S\to u\to v\to T,g(u)\geq 0,g(v)<0$ 的路径，合法性显然。否则对于同侧的边，它所属的调整路径必然起点满足 $g(u)\geq 0$，终点满足 $g(v)<0$，否则这次调整是无效的。

### 方法二

传统做法。

考虑到一次比赛的结果合法当且仅当恰好有一方的胜负次数 $+1$，此时比赛向双方连边，双方向汇点连流量为 $x$ 边。判断是否满流则存在合法方案。

代码（方法一）

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define db double
#define ldb long double
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
using namespace std;
inline int read() {
    int x = 0; bool op = 0;
    char c = getchar();
    while(!isdigit(c))op |= (c == '-'), c = getchar();
    while(isdigit(c))x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return op ? -x : x;
}
template<int N> struct MFL {
  	const int INF = 1e9;
    int n, etot, S, T, head[N], to[N], nxt[N], flow[N];
    void addedge(int u, int v, int w) { 
        to[++etot] = v; flow[etot] = w; nxt[etot] = head[u]; head[u] = etot;
    }
    void add(int u, int v, int w) {
        addedge(u, v, w); addedge(v, u, 0);
        return ;
    }
    void init(int nn, int ns, int nt) {
        n = nn; S = ns; T = nt; etot = 1;
        memset(head, 0, sizeof(head));
        return ;
    }
    int lev[N], cur[N];
    bool bfs() {
        for(int i = 0; i <= n; i++)cur[i] = head[i], lev[i] = 0;
        queue<int> q;
        q.push(S); lev[S] = 1;
        while(q.empty() == false) {
            int u = q.front(); q.pop();
            for(int i = head[u]; i; i = nxt[i]) {
                if(lev[to[i]] || flow[i] == 0)continue;
                lev[to[i]] = lev[u] + 1;
                if(to[i] == T)return true;
                q.push(to[i]);
            }
        }
        return false;
    }
    int dinic(int u, int fl) {
        if(u == T)return fl;
        int rest = fl;
        for(int i = cur[u]; i && rest; i = nxt[i]) {
            cur[u] = i;
            if(lev[to[i]] ^ (lev[u] + 1) || flow[i] == 0)continue;
            int inc = dinic(to[i], min(flow[i], rest));
            if(inc == 0)lev[to[i]] = 0;
            flow[i] -= inc; flow[i ^ 1] += inc; rest -= inc;
        }
        return fl - rest;
    }
    int query() {
        int mxfl = 0, fl = 0;
        while(bfs()) {
            while(fl = dinic(S, INF))mxfl += fl;
        }
        return mxfl;
    }
};
const int N = 1e6 + 10;
MFL<N> mf;
int n, m;
int deg[N], in[N], out[N], val[N];
struct Node {
    int u, v;
    Node() {}
    Node(int u, int v):u(u), v(v) {}
}e[N];
bool check(int x) {
    mf.init(n + 1, 0, n + 1);
    int sum = 0;
    for(int i = 1; i <= m; i++) {
        int u = e[i].u, v = e[i].v;
        mf.add(v, u, 1);
    }
    for(int i = 1; i <= n; i++) {
        int val = ((in[i] - out[i]) - (deg[i] - 2 * x)) / 2;
        if(val < 0)mf.add(i, mf.T, -val), sum += -val;
        else mf.add(mf.S, i, val);
    }
    if(mf.query() < sum)return false;
    for(int i = 1; i <= m; i++) {
        val[i] = mf.flow[i << 1]; 
    }
    return true;
}
int main() {
    n = read(); m = read();
    for(int i = 1; i <= m; i++) {
        int u = read(), v = read();
        e[i] = Node(u, v); 
        deg[u]++; deg[v]++; in[v]++; out[u]++;
    }
    int lef = 0, rig = m + 1;
    while(lef + 1 < rig) {
        int mid = lef + rig >> 1;
        // printf("%d %d\n", lef, rig); 
        if(check(mid))rig = mid;
        else lef = mid;
    }
    // printf("chk:%d\n", check(1));
    printf("%d\n", rig);
    for(int i = 1; i <= m; i++)printf("%d\n", val[i]);
    return 0;
}
```




---

## 作者：Leap_Frog (赞：0)

### P.S.
草，这种无名题是我 2k AC。  
好不甘心。。。/kel  
不过还是纪念一下吧。。。  
### Description.
给定一张无向图，给其定向。  
现在要求最优方案，使每个点最大入度最小，并输出方案。  
### Solution.
最大值最小问题直接二分转判定，现在每个点入度有限制。  
每条边能且仅能贡献一个入度。  
所以直接对入度来讨论。  
直接对每条边向两个顶连边，容量随意（不是0就行。  
再从源点向每条边连边容量为1，每个点向汇点连边容量为限制。  
直接dinic判每条边的容量是否全都能贡献掉。  
输出的话直接看每边入度贡献给谁了就好了。  
~~刚开始空间开小了直接TLE然后调自闭~~  
完结撒花
### Coding.
```cpp
int n,m,X[100005],Y[100005];
inline char check(int x)
{
	memset(head,0,sizeof(head)),et=0;
	for(int i=1;i<=m;i++) adde(s,i,1),adde(i,X[i]+m,1),adde(i,Y[i]+m,1);
	for(int i=1;i<=n;i++) adde(i+m,t,x);
	return dinic(s,t)==m;
}
inline void paint()
{
	for(int x=1;x<=m;x++) for(int i=head[x];i;i=e[i].nxt) if(!e[i].w) printf("%d\n",X[x]==e[i].to-m);
}
int main()
{
	read(n),read(m),s=n+m+1,t=s+1;for(int i=1;i<=m;i++) read(X[i]),read(Y[i]);
	int le=0,ri=n,md,rs=n;while(le<=ri) {md=(le+ri)>>1;if(check(md)) ri=md-1,rs=md;else le=md+1;}
	return check(rs),printf("%d\n",rs),paint(),0;
}
```


---

## 作者：温词 (赞：0)

### 这是一道最大流加二分的好题
#### 为了良好的阅读体验，可以访问https://www.cnblogs.com/wenci/p/10122656.html进行查看
#### 题面说赢的最多的人最少赢几场，肯定是向二分的方向思考

#### 建立源点向每一场比赛连容量为1的边，从每场比赛向参赛两个人各连一条容量为1的边，表示一场比赛有一个人赢

#### 二分一个最多的人赢的场数，从每个人向汇点连容量为mid的边，若最大流等于场数，说明符合题意，可以减小最多的人赢的场数，反之缩小

#### 因为要输出方案，可以记录下满足条件的最小答案，然后以这个答案再跑一次，从比赛流向个人的边如果容量为0（也就是在增广时被流过了）说明他赢了这场比赛
```cpp
#include<bits/stdc++.h>
#include<queue>
using namespace std;
#define INF 0x3f3f3f3f
inline int read(){
    int w=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        w=(w<<3)+(w<<1)+ch-48;
        ch=getchar();
    }
    return w*f;
}
int n,m,cnt=-1,head[100010],cur[100010],depth[100010],S,T,u[100010],v[100010],ans,x[100010],y[100010];
const int p=10000;
bool vis[100010];
struct Edge{
    int from,to,next,flow;
}edge[1000010];
inline void addedge(int u,int v,int w){
    cnt++;
    edge[cnt].from=u;
    edge[cnt].to=v;
    edge[cnt].flow=w;
    edge[cnt].next=head[u];
    head[u]=cnt;
}
inline void ins(int u,int v,int w){
    addedge(u,v,w);addedge(v,u,0);
}
queue<int> q;
inline bool bfs(int st,int ed){
    memset(depth,0,sizeof(depth));
    int u,v,i,j,k;q.push(st);depth[st]=1;
    for(i=S;i<=T;i++)cur[i]=head[i]; 
    while(!q.empty()){
        u=q.front();q.pop();
        for(i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!depth[v]&&edge[i].flow){
                depth[v]=depth[u]+1;q.push(v);
            }
        }
    }
    return depth[ed];
}
inline int dfs(int u,int ed,int limit){
    if(!limit||u==ed) return limit;
    int v,i,j,k;int flow=0,f;
    for(i=cur[u];i!=-1;i=edge[i].next){
        v=edge[i].to;cur[u]=i;
        if(depth[v]==depth[u]+1&&(f=dfs(v,ed,min(limit,edge[i].flow)))){
            limit-=f;flow+=f;
            edge[i].flow-=f;edge[i^1].flow+=f;
            if(!limit) break;
        }
    }
    return flow;
}
inline void Dinic(){
    while(bfs(S,T)){
        ans+=dfs(S,T,INF);
    }
}
inline bool check(int mid){
    cnt=-1;memset(head,-1,sizeof(head));
    int i,j,k;
    for(i=1;i<=m;i++){
        ins(S,i,1);
        ins(i,x[i]+p,1);
        ins(i,y[i]+p,1);
    }
    for(i=1;i<=n;i++){
        ins(i+p,T,mid);
    }
    ans=0;Dinic();
    return ans==m;
}
int main(){
    n=read();m=read();int i,j,k;int ans1;
    memset(head,-1,sizeof(head));S=0;T=99999;
    for(i=1;i<=m;i++){
        x[i]=read();y[i]=read();
    }
    int l=0,r=m+1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) r=mid-1,ans1=mid;
        else l=mid+1;
    }
    cout<<ans1<<endl;
    check(ans1);
    for(int u=1;u<=m;u++){
        for(i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].to;v-=p;if(v<1 or edge[i].flow) continue;
            if(v==x[u]) vis[u]=true;
        }
    }
    for(i=1;i<=m;i++){
        printf("%d\n",vis[i]);
    }
    return 0;
}
```

---

## 作者：Victorique (赞：0)

网络流神题！

首先理解题意是第一要义，实在不行就看一下博客里那些BZOJ的题面就可以。

然后说一下输出方案的意思：对于每场比赛的a，b选手，如果a要赢b，那么这场比赛输出1，否则输出0.

建图比较正常，比较容易想的是二分求解。首先我们从超级汇向所有比赛连一条流量为1的边，然后从每个比赛向它所包含的两个选手连流量为1的边。最后我们把每个选手向超级汇连边，流量就是你二分的那个值。然后判断最大流是否是比赛总场数m。

好了，然后是输出方案的问题，这个部分按照惯例有很多方法，那么我们现在推出最简单的暴力枚举。每次我们缩小二分上界时，我们都是找出了一种可行解，所以暴力枚举所有比赛，判断一下它的对那个选手满流即可。

为什么不能在最后面求得顺序？你在二分的时候，退出二分的条件就是你的dinic跑不出来期望的最大流了，这个时候每场比赛的结果也和刚才你求出来的时候不一样了，所以必须在二分内部求出。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define re register
#define inf 400000000
using namespace std;
int n,s,q,dis[2000011],t,l,cur[200051];
struct po
{
    int nxt,to,w;
}edge[3000021];
int head[40151],tot,dep[40051],map[20005][2],id,d,num=-1,ct[20001];
int x,y,m;
inline int read()
{
    int x=0,c=1;
    char ch=' ';
    while((ch>'9'||ch<'0')&&ch!='-')ch=getchar();
    while(ch=='-')c*=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-'0',ch=getchar();
    return x*c;
}
inline void add_edge(int from,int to,int w)
{
    edge[++num].nxt=head[from];
    edge[num].to=to;
    edge[num].w=w;
    head[from]=num;
}
inline void add(int from,int to,int w)
{
    add_edge(from,to,w);
    add_edge(to,from,0);
}
inline bool bfs()
{
    memset(dep,0,sizeof(dep));
    queue<int> q;
    while(!q.empty())
    q.pop();
    q.push(s);
    dep[s]=1;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(re int i=head[u];i!=-1;i=edge[i].nxt)
        {
            int v=edge[i].to;
            if(dep[v]==0&&edge[i].w>0)
            {
                dep[v]=dep[u]+1;
                if(v==t)
                return 1;
                q.push(v);
            }
        }
    }
    return 0;
}
inline int dfs(int u,int dis)
{
    if(u==t)
    return dis;
    int diss=0;
    for(re int& i=cur[u];i!=-1;i=edge[i].nxt)
    {
        int v=edge[i].to;
        if(edge[i].w!=0&&dep[v]==dep[u]+1)
        {
            int check=dfs(v,min(dis,edge[i].w));
            if(check>0)
            {
                dis-=check;
                diss+=check;
                edge[i].w-=check;
                edge[i^1].w+=check;
                if(dis==0)
                break;
            }
        }
    }
    return diss;
}
inline int dinic()
{
    int ans=0;
    while(bfs())
    {
        for(re int i=0;i<=t;i++)
        cur[i]=head[i];
        while(int d=dfs(s,inf))
        ans+=d;
    }
    return ans;
}
inline void build(int x)
{
	num=-1;
	memset(head,-1,sizeof(head));
	for(re int i=1;i<=m;i++){
		add(s,i,1),add(i,map[i][0],1),add(i,map[i][1],1);
	}
	for(re int i=m+1;i<=m+n;i++)
	add(i,t,x);
}
int main()
{
	n=read();m=read();
	s=0;t=n+m+1;
	for(re int i=1;i<=m;i++){
		map[i][0]=read()+m;map[i][1]=read()+m;
	}
	int l=0,r=m;
	while(l<=r){
		int mid=l+r>>1;
		build(mid);
		if(dinic()==m) {
			int winner=0;
			for(re int i=1;i<=m;i++)
			{
					for(re int j=head[i];j!=-1;j=edge[j].nxt){
					int v=edge[j].to;
					if(v!=t&&edge[j^1].w==1)
					if(v==map[i][0])
					ct[i]=1; else ct[i]=0;
				}
			}	
			r=mid-1;
		}
		else {
			
			l=mid+1;
		}
	}
	cout<<l<<endl;
	
	
	for(re int i=1;i<=m;i++)
	cout<<ct[i]<<endl;
}
```

---

## 作者：creation_hy (赞：0)

水题，最大值最小显然二分，那剩下的就是判断是否有一种合法的分配。

直接最大流，对于每个比赛从 $S$ 连 $1$ 的流量，然后在分别向两个选手连 $1$ 的流量，最后每个选手向 $T$ 连 $k$ 的流量（$k$ 是二分的数）。

输出方案直接记下每个比赛对应的边的编号就行了。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e4 + 5;
const int M = 1e5 + 5;
const ll inf = 1e18;
int n, m, s, t, etot, head[N], to[M], nxt[M], stt[N], d[N], pos[N];
ll val[M];
inline void link(int u, int v, ll w)
{
    to[etot] = v;
    nxt[etot] = head[u];
    val[etot] = w;
    head[u] = etot++;
}
inline void add(int u, int v, ll w)
{
    link(u, v, w);
    link(v, u, 0);
}
inline bool bfs()
{
    queue<int> q;
    memset(d, 0, sizeof(d));
    d[s] = 1;
    q.emplace(s);
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        for (int i = head[x]; ~i; i = nxt[i])
            if (!d[to[i]] && val[i])
            {
                d[to[i]] = d[x] + 1;
                q.emplace(to[i]);
                if (to[i] == t)
                    return true;
            }
    }
    return false;
}
inline ll dfs(int x, ll flow)
{
    if (x == t)
        return flow;
    ll res = 0;
    for (int &i = stt[x]; ~i && res < flow; i = nxt[i])
        if (d[to[i]] == d[x] + 1 && val[i])
        {
            ll tmp = dfs(to[i], min(flow - res, val[i]));
            if (tmp)
            {
                res += tmp;
                val[i] -= tmp;
                val[i ^ 1] += tmp;
            }
        }
    return res;
}
inline ll dinic()
{
    ll res = 0;
    while (bfs())
    {
        memcpy(stt, head, sizeof(head));
        res += dfs(s, inf);
    }
    return res;
}
struct Query
{
    int x, y;
} qy[N];
inline bool check(int k)
{
    memset(head, -1, sizeof(head)), etot = 0;
    s = 0, t = n + m + 1;
    for (int i = 1; i <= m; i++)
    {
        add(s, i, 1);
        add(i, qy[i].x + m, 1), pos[i] = etot - 2;
        add(i, qy[i].y + m, 1);
    }
    for (int i = 1; i <= n; i++)
        add(i + m, t, k);
    return dinic() == m;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> qy[i].x >> qy[i].y;
    int l = 0, r = m;
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (check(mid))
            r = mid - 1;
        else
            l = mid + 1;
    }
    cout << r + 1 << '\n';
    check(r + 1);
    for (int i = 1; i <= m; i++)
        cout << !val[pos[i]] << '\n';
    return 0;
}
```

---

