# [USACO06DEC] Wormholes G

## 题目背景

[英文题面见此链接](https://www.luogu.com.cn/paste/mxuf6zpl)

## 题目描述

John 在他的农场中闲逛时发现了许多虫洞。虫洞可以看作一条十分奇特的有向边，并可以使你返回到过去的一个时刻（相对你进入虫洞之前）。

John 的每个农场有 $m$ 条小路（无向边）连接着 $n$ 块地（从 $1 \sim n$ 标号），并有 $w$ 个虫洞。

现在 John 希望能够从某块地出发，走过一条路径回到出发点，且同时也回到了出发时刻以前的某一时刻。请你告诉他能否做到。

## 说明/提示

#### 样例 2 解释

John 只需要沿着 $1 \rightarrow 2 \rightarrow 3 \rightarrow 1$ 的路径一直转圈即可，每转完一圈，时间就会减少一秒。

#### 数据范围与约定

对于 $100\%$ 的数据，$1 \le T \le 5$，$1 \le n \le 500$，$1 \le m \le 2500$，$1 \le w \le 200$，$1 \le p \le 10^4$。

## 样例 #1

### 输入

```
2
3 3 1
1 2 2
1 3 4
2 3 1
3 1 3
3 2 1
1 2 3
2 3 4
3 1 8```

### 输出

```
NO
YES```

# 题解

## 作者：Drifting (赞：24)

这题居然没有用 $Floyd$ 判负环的题解...

(卡常极为痛苦，请开 $O2$ 优化)

因为代码极简单，直接看吧。

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int INF = 0x3f3f3f3f;
int T, n, m, W, dis[505][505];
inline int read()
{
	register int x = 0;
	char c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while (c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
	return x;
}
bool check()
{
	for (register int k = 1; k <= n; k++)
		for (register int i = 1; i <= n; i++)
		{
			for (register int j = 1; j <= n; j++)
			{
				int res = dis[i][k] + dis[k][j];
				if (dis[i][j] > res)
					dis[i][j] = res;
			}
			if (dis[i][i] < 0)
				return 1;
		}
	return 0;
}
int main()
{
	T = read();
	while (T--)
	{
		n = read(), m = read(), W = read();
		for (register int i = 1; i <= n; i++)
			for (register int j = 1; j <= n; j++)
				dis[i][j] = INF;
		for (int i = 1; i <= m; i++)
		{
			int u = read(), v = read(), w = read();
			if (dis[u][v] > w)
				dis[u][v] = dis[v][u] = w;
		}
		for (int i = 1; i <= W; i++)
		{
			int u = read(), v = read(), w = read();
			dis[u][v] = -w;
		}
		if (check())
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
```

---

## 作者：wjy666 (赞：14)

C++的dfs版spfa

用dfs的spfa判负环的优越性，楼下pascal大佬已经讲得很清楚了，这题dfs快的飞起，2ms就过了

AC了这题的同学可以去试着做负环模板练练手，那题数据范围大很多，bfs是过不了的

上代码，注释在代码里

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#define N 505
#define For(i,j,k) for(int i=j;i<=k;i++)
using namespace std;
int read(){//快读
    int l=1,x=0; char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if (ch=='-') ch=getchar(),l=-1;
    while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*l;
}
struct node{int dis,nex;}f;
vector<node> mp[N]; //vector存图，下标是边的起始点，dis边权，nex是边的终点(蒟蒻不会链式前向星5555)
int sum[N],fl[N]={0},flag;
void spfa(int k){ //dfs的spfa
    if (fl[k]==1) {fl[k]=0; flag=1; return;} //只要一个点第二次走到就说明有负环了，标记退出
    fl[k]=1; //标记这个点走过了
    if (!mp[k].empty())
        For(i,0,mp[k].size()-1)
            if (sum[mp[k][i].nex]>mp[k][i].dis+sum[k]){
                sum[mp[k][i].nex]=mp[k][i].dis+sum[k];
                spfa(mp[k][i].nex); if (flag==1) {fl[k]=0; return;} //有负环就一层层退，注意清空数组标记
            }
    fl[k]=0; //取消这个点的标记
}
int main(){
    int _=read(),m,n=0,w,x,y,z,k;
    while(_--){
        For(i,1,n) mp[i].clear(); //清空vector
        n=read(),m=read(),k=read();
        For(i,1,m){ //存正边，无向边要存2次
            x=read(),y=read(),z=read();
            f.dis=z; f.nex=y; mp[x].push_back(f);
            f.nex=x; mp[y].push_back(f);
        }
        For(i,1,k){ //存负边，注意边权取负
            x=read(),y=read(),z=read();
            f.dis=-z; f.nex=y; mp[x].push_back(f);
        }
        memset(sum,0,sizeof(sum)); //多组数据，清空最短路数组
        flag=0;
        For(i,1,n) {spfa(i); if (flag) break;} //没有原点，所以每个点当起始点找一遍，找到一个负环就退出
        if (flag==1) printf("YES\n"); else printf("NO\n");
    }
    return 0;
}
```

---

## 作者：Sakura_Peng (赞：12)

如果我们把每一条路权值看成通过所用的时间的话，那么我们便可以把虫洞的时间看成负权边，这样的话**如果从一个点出发回到这个点所花的时间小于0，则说明虫洞起了作用回到了出发时间之前**。

对于这个理解，我们可以看成负权环，如果我们枚举每一个点进行寻找是否存在负权环的话可能这道题能过，但是如果数据范围更大一点可能就会TLE了。

这个时候我们就可以采用**超级源点**的方法进行解决：

详情请看：[超级源点和超级汇点的建立](https://blog.csdn.net/qq_40772692/article/details/83090675)

**<1>同时有多个源点和多个汇点，建立超级源点和超级汇点**

**<2>同时有多个源点和一个汇点，建立超级源点**

**<3>同时有多个汇点和一个源点，建立超级汇点**


那么我们这里是要从多个地方进行寻找是否存在负变权，如果我们建立了超级源点，就只需要从超级源点开始进行找负权环，**这样就可以自动找到是否存在负权环，省去了每一个点枚举一次找负权环的冗余操作**，也就是<2>的情况。

对于超级源点，我们可以设置为0也可以设置为n+1，再将其与所有的图中的点相连，权值设为0（因为超级源点是一个模拟点，为了方便省时间，**所以不存在，不可对整个图产生影响，故权值设为0）**

接下来就是寻找负权环的操作，对于负权环，我们可以使用SPFA算法进行实现，因为如果出现负权边，对于SPFA的思想，他一定会一直围绕这条边不断进行松弛，则我们可以通过这个特性来判断负权环，而这个操作可以通过dfs的SPFA和bfs的SPFA进行。

如果对于**dfs**的SPFA，则就是在SPFA的松弛操作里，
**如果新扩展的这个点之前已经扩展过了，就说明一条路中存在了两次这个点**

那么就说明出现了环的情况。

部分代码如下

```cpp
void pd(int x)
{
	if (flag)
	return ;
	b[x]=1;
	int k=h[x];
	while (k!=-1)
	{
		if (dis[a[k].to]>dis[x]+a[k].dis)
		{
			dis[a[k].to]=dis[x]+a[k].dis;
			if (b[a[k].to])
			{
				flag=1;  //标记出现负权环
				return ;
			}
			else
			pd(a[k].to);
		}
		k=a[k].next;
		}
	b[x]=0;
}
```

对于**bfs**的SPFA，我们可以利用这么一个思想：

如果对于一个有N个点的图，找到两个点存在最短路，**那么他们经过的点一定小于等于n个点，那么如果我们到了当前这个点发现经过的点大于n个了，那么就说明一定存在环的情况了**

部分代码如下：

```cpp
while (!q.empty())
		{
			int x=q.front();
			q.pop();
			b[x]=0;
			int k=h[x];
			while (k!=-1)
			{
				if (dis[a[k].to]>dis[x]+a[k].dis)
				{
				    dis[a[k].to]=dis[x]+a[k].dis;
				    cnt[a[k].to]=cnt[x]+1;
				    if (cnt[a[k].to]>n)
				    {
						flag=1;  //标记出现负权环
						return ;
						}
					if(b[a[k].to]==0)
					{
						b[a[k].to]=1;
						q.push(a[k].to);
						} 
					} 
					k=a[k].next;
				}
			}
```

本题代码如下：

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
struct CZP
{
	int next,to,dis;
}a[1000001];
int n,m,h[100001],b[100001],flag,t,top,dis[100001],w;
void cun(int from,int to,int dis)
{
	a[++top].next=h[from];
	a[top].to=to;
	a[top].dis=dis;
	h[from]=top;
}
void pd(int x)
{
	if (flag)
	return ;
	b[x]=1;
	int k=h[x];
	while (k!=-1)
	{
		if (dis[a[k].to]>dis[x]+a[k].dis)
		{
			dis[a[k].to]=dis[x]+a[k].dis;
			if (b[a[k].to])
			{
				flag=1;
				return ;
			}
			else
			pd(a[k].to);
		}
		k=a[k].next;
		}
	b[x]=0;
}   //这里使用了dfs的求负权环操作
int main()
{
	scanf("%d",&t);
	for (int k=1;k<=t;k++)
	{
		flag=0;
	    scanf("%d%d%d",&n,&m,&w);
		for (int i=0;i<=n;i++)
		h[i]=-1;
		for (int i=1;i<=m;i++)
		{
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			cun(x,y,z);
			cun(y,x,z);
			}     //小路为双向边！
		for (int i=1;i<=w;i++)
		{
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			cun(x,y,-z);
		}   //虫洞改为负权值
		memset(b,0,sizeof(b));
		for (int i=1;i<=n;i++)
		cun(0,i,0);  //建立超级源点0
		for (int i=1;i<=n;i++)
		dis[i]=100000000;
		dis[0]=0;
		b[0]=1;
		pd(0);  
		if (flag==1)
		printf("YES\n");
		else
		printf("NO\n");
	}
	return 0;
}
*/
```


---

## 作者：ljcljc (赞：4)

一道负环的裸题, 基于$SPFA$ ~~(这个死了的算法)~~,我们有两种思路：

(1)统计每个点入队的次数， 如果某个点入队$n$次， 说明存在负环；

(2)统计当前每个点的最短路中所包含的边数， 如果某个点的最短路所包含的边数大于等于$n$， 则说明存在负环；

我使用的是第二种写法：
```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int N = 510;
const int M = 5500;
int n, m1, m2;
int cnt[N], vis[N], dis[N];
struct edge {
	int to, w;
};
vector<edge> G[M];

bool spfa() {
	queue<int> q;
	memset(cnt, 0, sizeof cnt);
	memset(vis, 0, sizeof vis);
	memset(dis, 0, sizeof dis);
	for(int i=1; i<=n; i++) {
		q.push(i);
		vis[i] = 1;
	}
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for(int i=0; i<G[u].size(); i++) {
			int v = G[u][i].to;
			int w = G[u][i].w;
			if(dis[v] > dis[u] + w){
				dis[v] = dis[u] + w;
				cnt[v] = cnt[u] + 1;
				if(cnt[v] >= n) return true;
				if(!vis[v]) {
					q.push(v);
					vis[v] = 1;
				}
			}
		}
	}
	return false;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		memset(G, 0, sizeof(G));
		scanf("%d %d %d", &n, &m1, &m2);
		while(m1--) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			G[u].push_back((edge){v, w});
			G[v].push_back((edge){u, w});
		}
		while(m2--) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			G[u].push_back((edge){v, -w});
		}
		if(spfa()) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```


---

## 作者：kczno1 (赞：3)

spfa用dfs会对一个非最优的状态进行较多的无用的搜索，所以比bfs慢一些。

但在判断负环时如果用bfs就不知道到这个点的路径，所以只有入队>n次才能判断，所以时间最差为O(n\*m)

而用dfs就可以知道路径，所以一旦一个点两次出现就可判断，时间仍能保持O(k\*m)。

```cpp
var
 farm,n,m,w,f,o,i,num,x,y,len:longint;
 t,g:array[1..500] of longint;
 l:array[1..10000,1..3] of longint;
 ok:boolean;//1则找到负环了，直接退出
 ing:array[1..500] of boolean;

procedure jia(x,y,len:longint);//加一条x->y的边
begin
 inc(num);
 l[num,3]:=t[x];t[x]:=num;
 l[num,1]:=y;l[num,2]:=len;
end;

procedure spfa(x:longint);
var i:longint;
begin
 ing[x]:=true;//在路径上
 i:=t[x];
 while i<>0 do
 begin
  if g[x]+l[i,2]<g[l[i,1]] then
  begin
   if ing[l[i,1]] then begin ok:=true;break; end;

   g[l[i,1]]:=g[x]+l[i,2];
   spfa(l[i,1]);
   if ok then break;
  end;

  i:=l[i,3];
 end;
 ing[x]:=false;
end;

procedure try;
begin
  readln(n,m,w);

 num:=0;
 for i:=1 to n do t[i]:=0;

 for i:=1 to m do
 begin
  read(x,y,len);
  jia(x,y,len);
  jia(y,x,len);
 end;
 for i:=1 to w do
 begin
  read(x,y,len);
  jia(x,y,-len);
 end;

 for i:=1 to n do g[i]:=1<<29;ok:=false;

 for f:=1 to n do
 if g[f]=1<<29 then
 begin
  g[f]:=0;
  spfa(f);
  if ok then exit;
 end;

end;

begin 
 readln(farm);
 for o:=1 to farm do
 begin
  try;
  if ok then writeln('YES')
  else writeln('NO');
 end;
end.

```

之前a了后才发现出发点不一定在负环中，于是造了这个点。a了的人可以试试看，说不定会re

1
3 2 1
1 2 5
2 3 3
3 2 4

---

## 作者：动态WA (赞：1)

众所周知，这是一道判断有没有负环的模板题

SPFA判负环太难打？

Floyd时间太长？

选择~~打表~~Bellman-Ford，简单的理解，简单的代码

SPFA只是在它的基础上修改
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
int F,h;
int n,m,w;
struct edge{
	int x,y,v;
}e[5500];
int d[501];
bool bellman(){
	memset(d,0x3f,sizeof(d));
	d[1]=0;
	for (int i=1;i<n;i++)
		for (int j=1;j<=h;j++)
			if (d[e[j].x]+e[j].v<d[e[j].y])
				d[e[j].y]=d[e[j].x]+e[j].v;
   //经过n-1次更新，此时答案应为最短路
	for (int j=1;j<=h;j++)
		if (d[e[j].x]+e[j].v<d[e[j].y]) return 1;
   //若还能更新，说明存在负环
	return 0;
}
int main(){
	scanf("%d",&F);
	for (int i=1;i<=F;i++){
		h=0;
		scanf("%d%d%d",&n,&m,&w);
		for (int i=1;i<=m;i++){
			int u,v,c;
			scanf("%d%d%d",&u,&v,&c);
			e[++h].x=u;
			e[h].y=v;
			e[h].v=c;
			e[++h].x=v;
			e[h].y=u;
			e[h].v=c;
		}
		for (int i=1;i<=w;i++){
			int u,v,c;
			scanf("%d%d%d",&u,&v,&c);
			e[++h].x=u;
			e[h].y=v;
			e[h].v=-c;
		}
		if (bellman()) printf("YES\n");
		else printf("NO\n");
	}
}
```


---

## 作者：dunko (赞：1)

又是一道最短路水题。

##**题目**

自己看吧 [点这里](https://www.luogu.org/problemnew/show/P2850)

##**思路**

看完了题目不知大家是怎么想的，我看这与[【模板】负环](https://www.luogu.org/problemnew/show/P3385)实在太像了，就是简单的判断负环吗，改了一下输入和输出就完美AC了。就是这样简单。真的没了。

为什么会是这种情况呢？（~~会不会是数据太水了呢~~），其实出现了负环才会回到之前的时空（题目背景还是不错的~）。再看了一眼题目，只要注意输入和输出就可以AC了，想必大家一定有更好的想法。（~~但是我不听我不听我不听~~）

再多说一句，SPFA是个好东西（只因为我忘了Bellman-ford）。

###### 以上只是我这个蒟蒻瞎说的一切，这肯定不是正解，希望大家不要参考！！！

##**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
    int to,next,w;
}edge[5000001];//前向星建边
int t,n,m,ww,cnt,head[100001],in[100001],dis[100001];
bool vis[100001];
void add(int x,int y,int w){//前向星建边
    edge[++cnt]=(node){y,head[x],w};
    head[x]=cnt;
}
void SPFA(){
    queue<int>que; memset(dis,127,sizeof(dis));
    memset(vis,0,sizeof(vis)); memset(in,0,sizeof(in));//初始化不要忘了
    vis[1]=1; dis[1]=0; que.push(1); in[1]=1;
    while(que.size()){//开始了正文
        int d=que.front(); que.pop(); vis[d]=0;
        for(int i=head[d];i;i=edge[i].next){
            int x=edge[i].to;//枚举与它相关的点
            if(dis[x]>dis[d]+edge[i].w){//松弛操作
                dis[x]=dis[d]+edge[i].w;
                in[x]=in[d]+1;
                if(in[x]>n){//这个是最基本的操作，不懂可以参考大佬的解释
                    cout<<"YES"<<endl;
                    return;
                }
                if(!vis[x]) vis[x]=1,que.push(x);
            }
        }
    }
    cout<<"NO"<<endl;//没有负环
}
int main(){
    cin>>t;
    while(t--){
        cnt=0; memset(head,0,sizeof(head));
        scanf("%d%d%d",&n,&m,&ww);
        for(int i=1;i<=m;i++){
            int x,y,w;
            scanf("%d%d%d",&x,&y,&w);
            add(x,y,w); add(y,x,w);//建边和输入
        }
        for(int i=1;i<=ww;i++){
            int x,y,w;
            scanf("%d%d%d",&x,&y,&w);
            add(x,y,-w);//建负边
        }
        SPFA();
    }
    return 0;
}
```

---

## 作者：EightSixSun (赞：1)

存在负环时就是可以回到过去的情况

这个就可以用DFS版的SPFA，但是如果用原来的松弛方法很慢，那么可以加速一下，把所有的距离都设置为0，这样就只有有负权边的时候才会松弛下去，很大程度上加速了运行速度，当然你也可以记录下所有负权边的起点，逐个提取跑SPFA，不过我试验了一下，把距离设置为0用时和记录所有负权边的起点的用时都是0ms，空间上记录所有负权边的起点不如距离设置为0优秀，要多占用0.05MB

但是凭我只能想到记录所有负权边起点。。。

那么下边给出所有的距离均设置为0的写法
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define For(i,l,r) for(int i=l;i<=r;++i)
using namespace std;
int read()
{
    bool t=0;
    int a=0;
    char c;
    while((c=getchar())==' '||c=='\r'||c=='\n');
    if(c=='-')
    {
        t=1;
        c=getchar();
    }
    while(isdigit(c))
    {
        a*=10;
        a+=c;
        a-='0';
        c=getchar();
    }
    return a*(t?-1:1);
}
struct line{
    int to,next,v;
}edge[5210];
int n,m,w,dis[501],last[501];
bool vis[501],t;
void setup()//初始化，多组数据。。。
{
    t=0;
    memset(last,0,sizeof last);
}
void dfs(int x)
{
    if(vis[x])
    {
        t=1;
        return;
    }
    vis[x]=1;
    int p=last[x];
    while(p&&!t)
    {
        if(dis[edge[p].to]>edge[p].v+dis[x])
        {
         dis[edge[p].to]=edge[p].v+dis[x];
         dfs(edge[p].to);
        }
        p=edge[p].next;
    }
    vis[x]=0;
}
void spfa(int s)
{
    memset(dis,0,sizeof dis);//距离设置为0
    dfs(s);
}
void add(int from,int to,int v,int i)
{
    edge[i].to=to;
    edge[i].v=v;
    edge[i].next=last[from];
    last[from]=i;
}
int main()
{
    int f=read(),tx,ty,tz;
    For(i,1,f)
    {
        setup();
        n=read();
        m=read();
        w=read();
        m*=2;
        For(j,1,m)
        {
            tx=read();
            ty=read();
            tz=read();
            add(tx,ty,tz,j++);
            add(ty,tx,tz,j);
        }
        For(j,1,w)
        {
            tx=read();
            ty=read();
            tz=read();
            add(tx,ty,tz*(-1),m+j);
        }
        For(j,1,n)
        {
            spfa(j);
            if(t)
             break;
        }
        if(t)
         printf("YES\n");
        else
         printf("NO\n");
    }
    return 0;
}
```

---

## 作者：Arcturus1350 (赞：1)

其实楼下说的负环那题我就拿bfs过了……

这里说一个小小的优化……

就是我们(楼下)的正常思路是以每一个点为起点都跑一遍spfa看看有没有负环。

这里呢，小可爱又开了一个bool数组来记录一下每个点在最短路更新的时候有没有被扫到过，有过的话就直接标记。而这些有被扫到过的节点跑最短路的话，当然就是浪费时间了啊qaq

话不多说，上代码

```cpp
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
int t;
int n,m,s;
struct data{
    int v;int val;int next;
}edge[1000010];int alist[1000010];
int cnt;
void add(int u,int v,int val){
    edge[++cnt].v=v;
    edge[cnt].val=val;
    edge[cnt].next=alist[u];
    alist[u]=cnt;
    return ;
}
queue<int> q;
int dis[100010];
bool ins[100010];
bool book[100010];
int inq[100010];
bool spfa(int s){
    q.push(s);
    dis[s]=0;
    book[s]=true;
    ins[s]=true;inq[s]++;
    while(!q.empty()) {
        int x=q.front();
        q.pop();ins[x]=false;
        for(int next=alist[x];next;next=edge[next].next){
            book[edge[next].v]=true;//被扫到过就直接标记就好了
            if(dis[edge[next].v]>dis[x]+edge[next].val){
                dis[edge[next].v]=dis[x]+edge[next].val;
                if(!ins[edge[next].v]) {
                    q.push(edge[next].v),ins[edge[next].v]=true,inq[edge[next].v]++;
                    if(inq[edge[next].v]>n) return false;
                }
            }
        }
    }
    return true;
}
int u,v,val;
int main(){
//    freopen("1.in","r",stdin);
//    freopen("1.out","w",stdout);
    scanf("%d",&t);
    while(t--){
        memset(inq,0,sizeof(inq));
        memset(book,false,sizeof(book));
        memset(ins,0,sizeof(ins));
        memset(alist,0,sizeof(alist));
        cnt=0;
        while(!q.empty())q.pop();//清空
        scanf("%d%d%d",&n,&m,&s);
        for(int i=1;i<=m;i++)scanf("%d%d%d",&u,&v,&val),add(u,v,val),add(v,u,val);
        for(int i=1;i<=s;i++)scanf("%d%d%d",&u,&v,&val),add(u,v,-val);//建图
        for(int i=1;i<=n;i++) if(!book[i]) {memset(dis,0x3f3f3f3f3f,sizeof(dis));if(!spfa(i)) {puts("YES");goto qwq;}}//这里的book数组
        puts("NO");
        qwq:;
    }
}

```

---

## 作者：Los_chase (赞：1)

pascal详解（74分）

问题分析：给出一张图和其中的虫洞，判断能否回到过去。

注意：虫洞是有向边，小路是无向边。

算法分析：用邻接矩阵存储两点间关系，然后用SPFA依次判断从任一点出发是否可以回到过去。（好吧，虽然现实生活中不可能，毕竟有祖父悖论）（温馨提示：可能会有重边）

代码：

```cpp
const maxn=10000000;
var r:array[1..maxn] of longint;
    a,l:array[1..500,0..500] of longint;
    u:array[1..500,1..500] of boolean;
    f:array[1..500] of longint;
    o,i,j,s,e,t,n,m,w,p,q:longint;
function spfa(x:longint):boolean;
var h,t,i,k:longint;
    begin
        fillchar(f,sizeof(f),$20);
        f[x]:=0;
        u[x,x]:=true;
        h:=0;
        t:=1;
        r[t]:=x;
        while h<t do
            begin
                h:=h mod maxn+1;
                k:=r[h];
                u[x,k]:=false;
                for i:=1 to a[k,0] do
                    if f[k]+l[k,a[k,i]]<f[a[k,i]] then
                        begin
                            f[a[k,i]]:=f[k]+l[k,a[k,i]];
                            if f[x]<0 then
                                begin
                                    writeln('YES');
                                    exit(true);
                                end;
                            if not(u[x,a[k,i]]) then
                                begin
                                    t:=t mod maxn+1;
                                    r[t]:=a[k,i];
                                    u[x,a[k,i]]:=true;
                                end;
                        end;
            end;
        if x=n then
            writeln('NO')
                else
                    exit(false);
    end;
procedure readin;
    begin
        readln(n,m,w);
        fillchar(l,sizeof(l),$20);
        for j:=1 to m do
            begin
                readln(s,e,t);
                if t<l[s,e] then
                    l[s,e]:=t;
                if t<l[e,s] then
                    l[e,s]:=t;
            end;
        for j:=1 to w do
            begin
                readln(s,e,t);
                if -t<l[s,e] then
                    l[s,e]:=-t;
            end;
    end;
procedure main;
    begin
        for p:=1 to n do
            for q:=1 to n do
                if l[p,q]<200000 then
                    begin
                        inc(a[p,0]);
                        a[p,a[p,0]]:=q;
                    end;
        for j:=1 to n do
            if spfa(j) then
                break;
    end;
begin
    readln(o);
    for i:=1 to o do
        begin
            readin;
            main;
        end;
end.
```

---

## 作者：C20210114卢思吉 (赞：0)

# [题目点这里](https://www.luogu.org/problem/P2850)

题意是找负环

一看就是已死的SPFA，直接跑

[没学过SPFA的点这里](http://www.sohu.com/a/244179200_100201031)

但是，一定要注意两点

1.虫洞是有向边，但小路不是(~~所以说我交了好多遍没A，就是这个的锅~~)

2.我用的前向星存图。但是，前向星也要每次清零~~难怪之前好多多组数据的题WA，就是忘了memset~~

### 虽然这道题跑的是SPFA，但是请记住，SPFA他死了,Q千万别乱用SPFA

-----------------------------------------------------下面是代码--------------------------------------------------------------

```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
const int MAXN = 25005;
using namespace std;
int n,m,cnt1;
int v[MAXN],G[MAXN],nextpoint[MAXN];
int dis[MAXN],cnt[MAXN],first[MAXN],w;
bool flag,vis[MAXN];

void add_edge(int x,int y,int z){
    cnt1++;
    nextpoint[cnt1] = first[x];
    first[x] = cnt1;
    v[cnt1] = y;
    G[cnt1] = z;
}

bool SPFA(int s){ //已死的SPFA
	queue<int> q; //这个队列放全局和局部都行,主要是它在全局有可能出事
    int x,y,i,j;
    memset(dis,127,sizeof(dis));
    memset(vis,false,sizeof(vis));
    dis[s] = 0;
    cnt[s] = 1;
    q.push(s);
    vis[s] = true;
    while(!q.empty()){
        x = q.front();
        q.pop();
        vis[x] = false;
        for(int i = first[x] ; i ; i = nextpoint[i]){
            y = v[i];
            if(dis[y] > dis[x] + G[i]){
                dis[y] = dis[x] + G[i];
                cnt[y] = cnt[x] + 1;
                if(cnt[y] > n) return false;
                if(!vis[y]){
                    q.push(y);
                    vis[y] = true;
                }
            }
        }
    }
    return true;
}

inline long long read() { //一本通提高上的玄学写法
    long long k = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        k = (k << 1) + (k << 3) + (ch & 15);//哲学跑法(k << 1) 就是k * 2,(k << 3)就是k * 8,讲道理,影响不大，但看起来很nb
        ch = getchar();
    }
    if (f == -1) k = ~k + 1;//这里也是花里胡哨
    return k;
}

int main(){
	int t1;
	t1 = read();
	while(t1--){	
	    n = read(),m = read(),w = read();
	    cnt1 = 0;//清零前向星
	    
	    for(int i = 1 ; i <= m ; ++i){
		    int x = read(),y = read(),z = read();
	        add_edge(x,y,z); //小路
	        add_edge(y,x,z);
	    }
	    
	    for (int i = 1; i <= w ; i++){
	    	int x = read(),y = read(),z = read();
	    	add_edge(x,y,-z); //虫洞
	    } 
		
	    flag = SPFA(1); //从1开始跑SPFA找负环
	    if(!flag)  printf("YES\n");
	    else  printf("NO\n");
	}
    return 0;
}
```



# 最后在CSP2019的前夕，祝大家CSP.RP++,CSP.SCORE++


---

## 作者：EarthGiao (赞：0)

## 【思路】
SFPA判负环    
很水的一道SPFA判负环的板子题    

### 【题目分析】 
在农田没有虫洞的道路上面走回消耗时间   
在有虫洞的道路上面会回到之前的时间     
也就是得到时间    
所以会使之前消耗的时间减少    
只要消耗的时间能够成为负数    
就是回到了出发时间之间    
能够成为负数    
也就是权值为负的一个环    
就是负环     
所以只需要判断有没有负环就可以了    

### 【SPFA判负环】
板子    
赤裸裸的一道板子题    
详情解释见    
[这里](https://www.cnblogs.com/acioi/p/11694294.html)     

## 【完整代码】
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int Max = 6004;
const int M = 505;
struct node
{
	int y,ne,z;
}a[Max];
int n,m,w; 
int head[M],sum = 0;

void add(int x,int y,int z)
{
	a[++ sum].y = y;
	a[sum].ne = head[x];
	a[sum].z = z;
	head[x] = sum;
}

int d[M],cnt[M];
bool use[M];
bool SPFA()
{
	memset(cnt,0,sizeof(cnt));
	memset(use,false,sizeof(use));
	for(register int i = 1;i <= n;++ i)
		d[i] = 999999;
	d[1] = 0;
	queue<int>q;
	q.push(1);
	while(!q.empty())
	{
		int qwq = q.front();
		q.pop();use[qwq] = false;
		for(register int i = head[qwq];i != 0;i = a[i].ne)
		{
			int awa = a[i].y;
			if(d[awa] > d[qwq] + a[i].z)
			{
				d[awa] = d[qwq] + a[i].z;
				cnt[awa] = cnt[qwq] + 1;
				if(cnt[awa] > n)
					return false;
				if(use[awa] == false)
				{
					use[awa] = true;
					q.push(awa);
				}
			}
		}
	}
	return true;
}

int main()
{
	int f;
	scanf("%d",&f);
	while(f --)
	{
		sum = 0;
		memset(head,0,sizeof(head));
		scanf("%d%d%d",&n,&m,&w);
		int x,y,z;
		for(register int i = 1;i <= m;++ i)
		{
			scanf("%d%d%d",&x,&y,&z);
			add(x,y,z);add(y,x,z);
		}
		for(register int i = 1;i <= w;++ i)
		{
			scanf("%d%d%d",&x,&y,&z);
			add(x,y,-z);
		}
		if(SPFA() == false)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}
```

---

## 作者：piuke (赞：0)

[$$My\ Blog$$](https://blog.csdn.net/qq_43906740)

# 题意简介
因为要回到过去,所以回到起点时是一个负数。所以,就是求负环的问题了。

# 输入浅析
输入,就是说,有很多无向边,还有一些虫洞在单向边上,这些单向边为负权。

# 算法分析
算法的话,判负环有3 kinds of algorithm : SPFA, Bellman-Ford and Floyd。看这道题的神奇数据范围,三种是都可以用的。

等一下,不是多源负环吗?怎么能用SPFA呢?不要急,等一下再说。

# Floyd
老师：在循环体足够简单的情况下,$O(500^3)$是可以过的……
~~看来老师很擅长卡常+O2啊~~

附上本篇题解里某位大佬的话：
> 因为代码极简单,直接看吧。

还有,记住,有重边……

```
// luogu-judger-enable-o2
#include<cstdio>
#include<cstring>
#define reg register
#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
char buf[1 << 21], *p1 = buf, *p2 = buf;
inline int getc() {
    return p1 == p2 && (++p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;
}
#define getchar getc
#endif
template <typename T>
inline T read() {
    T a = 0; char c = getchar(), f = 1;
    while(c < '0' || c > '9') {
        if(c == '-') f = -f;
        if(c == -1) return c;
        c = getchar();
    }
    while(c >= '0' && c <= '9') a = (a << 1) + (a << 3) + (c ^ 48), c = getchar();
    return a * f;
}
template <class T>
inline T Min(T a, T b) { return a < b ? a : b; }
int x[501], y[501];
int G[501][501];
int n, m, w;
inline bool Floyd() {//Floyd多源负环
    for(reg int k = 1; k <= n; k++)
        for(reg int i = 1; i <= n; i++)
            for(reg int j=1; j <= n; j++)
                G[i][j]=Min(G[i][j], G[i][k] + G[k][j]);
    for(reg int i = 1; i <= n; i++)
        if(G[i][i] < 0) return 1;//判负环,即自环为负
    return 0;
}
inline void init() {
    n = read<int>(); m = read<int>(); w = read<int>();
    memset(G, 0x3f, sizeof G);//记得要赋初始值
    for(reg int i = 1; i <= m; i++) {
        int u = read<int>(), v = read<int>(), l = read<int>();
        if(G[u][v] > l) G[u][v] = G[v][u] = l;//想打人的重边
    }
    for(reg int i = 1; i <= w; i++) {
        int u = read<int>(), v = read<int>(), l = read<int>();
        G[u][v] = -l;//负权
    }
}
int main() {
    int T = read<int>();
    while(T--) {
        init();
        puts(Floyd() ? "YES" : "NO");
    }
}

```
# SPFA
~~因为这道题“极水”，所以朴素SPFA能过~~

附上代码(因为用了邻接表，所以不用管重边)
```
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
using namespace std;
#define reg register
#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
char buf[1 << 21], *p1 = buf, *p2 = buf;
inline int getc() {
    return p1 == p2 && (++p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;
}
#define getchar getc
#endif
template <typename T>
inline T read() {
    T a = 0; char c = getchar(), f = 1;
    while(c < '0' || c > '9') {
        if(c == '-') f = -f;
        if(c == -1) return c;
        c = getchar();
    }
    while(c >= '0' && c <= '9') a = (a << 1) + (a << 3) + (c ^ 48), c = getchar();
    return a * f;
}
int n, m, w;
vector<pair<int,int> >G[501];//用pair好像会快一点?!
inline void init() {
    n = read<int>(); m = read<int>(); w = read<int>();
    for(reg int i=1; i<=n; i++) G[i].clear();
    for(reg int i=1; i<=m; i++) {
        int u = read<int>(), v = read<int>(), l = read<int>();
        G[u].push_back(make_pair(v, l));
        G[v].push_back(make_pair(u, l));
    }
    for(reg int i=1; i<=w; i++) {
        int u = read<int>(), v = read<int>(), l = read<int>();
        G[u].push_back(make_pair(v, -l));
    }
}
int SPFA(int S) {
    int dis[501], cnt[501]={}; bool vis[501]={};
    memset(dis,0x3f,sizeof dis);
    dis[S] = 0, vis[S] = 1; queue<int>q; q.push(S);
    while(!q.empty()) {
        int t = q.front(); q.pop(); vis[t] = 0;
        for(reg int i = 0; i < int(G[t].size()); i++) {
            int v = G[t][i].first,w = G[t][i].second;
            if(cnt[v] >= n)//判环,其实应该是 >= n-1 的,但是负环就是会被访问无限次,所以不紧要
                return 1;
            if(dis[v] > dis[t] + w) {
                dis[v] = dis[t] + w;
                if(!vis[v]) vis[v] = 1, q.push(v), cnt[v]++;//松弛,被遍历次数+1，以便判环
            }
        }
    }
    return 0;
}
int main() {
    int T = read<int>();
    while(T--) {
        init();
        puts(SPFA(1) ? "YES" : "NO");
    }
}

```
其实,这道题用SPFA的正解,是先用DFS染色,然后每个不同色的区间SPFA一遍,但是因为我~~懒~~相信你们的能力,就不展示了。
# Bellman-Ford
老师：因为Belman-Ford能做的事,SPFA基本都能做,因为SPFA是Bellman-Ford的一个优化,所以就不讲了……
~~这事就要怪老师了吧~~


---

## 作者：q2368126021 (赞：0)

##### 改了一晚上的题，借鉴了前面各位大佬的经验（当然，肯定没有抄）。才过了这题
#### 一开始我tle了很多个点，实际上这题是一道负环处理问题，使用一个fp数组存储即可，只要超过n，这此为负环
```cpp
#include<cstdio>
#include<queue>
#include<cstring>

using namespace std;

struct pel {
	int to;
	int next;
	int dis;
};

pel a[10000];

deque<int> q;
  
int num=0;
  
int dis[10000],h[10000];

int f;

int n,m,w;

int x,y,z;

void add(int x,int y,int z) {

	num++;
	a[num]=(pel) {
		y,h[x],z
	};
	h[x]=num;
}

int fp[10000];

bool SPFA(int t) {

	int i;
	for(i=1; i<=n; i++)dis[i]=999999,fp[i]=0;
	q.push_front(t);
	dis[t]=0;
	while(!q.empty()) {
		int past=q.front();
		q.pop_front();
		if(fp[past]>n)return 1;
		for(i=h[past]; i; i=a[i].next) {
			int now=a[i].to;
			if(dis[now]>dis[past]+a[i].dis) {
				dis[now]=dis[past]+a[i].dis;
				if(dis[now]<0&&now==t)return 1;
				if(!q.empty()&&dis[now]<dis[q.front()])
					q.push_front(now);
				else q.push_back(now);
				fp[now]++;
			}
		}
	}
    return 0;
    }
int main(){

    scanf("%d",&f);
	int i,j;
	bool ff=1;
	for(i=1; i<=f; i++) {
		scanf("%d%d%d",&n,&m,&w);
		num=0;
        memset(h,0,sizeof(h));
        
		for(j=1; j<=m; j++) {
			scanf("%d%d%d",&x,&y,&z);
			add(x,y,z);
			add(y,x,z);
		}
		for(j=1; j<=w; j++) {
			scanf("%d%d%d",&x,&y,&z);
			add(x,y,-z);
		}

        for(j=1;j<=n;j++)
		if(SPFA(j)) {
				printf("YES\n");
				ff=0;
				break;
			}
			if(ff)printf("NO\n");
			ff=1;
	     }
}

---

## 作者：Accele_Rator (赞：0)

#链式前向星存图+spfa求负权回路


##一道裸的找负环，建议在熟练地了解spfa和链式前向星后再做（~~好吧其实我也不会~~）


利用负权回路可以无限被松弛的特点来做，若一个点被松弛两次（以上），则必定存在负环，即可以回到从前，用一个bool数组来记录，这一点可以用去掉正权边来优化


代码奉上：




```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 100010
#define maxm 1000010
using namespace std;
struct node{
  int to;
  int w;
}e[maxm];
int N_ext[maxm];
int H_ead[maxn];//链式前向星，需重复使用 
int d[maxn];//记录该点到其他点最短路 
bool V[maxn];
int tot=0;
bool flag;
void ins(int x,int y,int w)
{
    e[++tot].to=y;
    e[tot].w=w;
    N_ext[tot]=H_ead[x];
    H_ead[x]=tot;
```
}//链式前向星存图



    
      
```cpp
void clean()
{
    tot=0;
    flag=true;
    memset(V,false,sizeof(V));
    memset(H_ead,0,sizeof(H_ead));
    memset(N_ext,0,sizeof(N_ext));
    memset(d,0,sizeof(d));//（重点！！！）初始化为零，只看边权为负的边 ，极大的优化，模板中不这么做会T（别问我怎么知道的） 
}
void spfa(int x)
{
    if(!flag) return;
    V[x]=true;//首先把要看的点赋值为true 
    for(int p=H_ead[x];p;p=N_ext[p])//进链表 
    {
        if(!flag) return;
        int y=e[p].to;
        if(d[y]>d[x]+e[p].w)
        {
            d[y]=d[x]+e[p].w;
            if(V[y])//若一个点被重复松弛，则必定有负权回路 
            {
                flag=false;
                return;
            }
            else spfa(y);//从此点开始新的松弛 
        }
    }
    V[x]=false;//恢复 
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
      clean();//每次循环需清空重复使用的数组等 
      int n,m,w;
      scanf("%d%d%d",&n,&m,&w);
      for(int i=1;i<=m;i++)
      {
          int s,e,t;
          scanf("%d%d%d",&s,&e,&t);
          ins(s,e,t);
          ins(e,s,t);
```
}//小路建无向边
      
```cpp
      for(int i=1;i<=w;i++)
      {
          int s,e,t;
          scanf("%d%d%d",&s,&e,&t);
          ins(s,e,-t);
```
}//虫洞建有向负边
      
      
    
```cpp
      for(int i=1;i<=n;i++)
      {
        if(!flag) break;
        spfa(i);//由于只看负边，必须每个点都做
      }
      if(flag) printf("NO\n");
      else printf("YES\n");
    }
    return 0;
}
```

---

## 作者：如我西沉 (赞：0)

裸的SPFA判负环，有输出YES，没输出NO，注意一下数据范围，貌似是被偷偷扩大过的。。。

一开始开maxn=5000没过，一直开到1000000。。。

6,8两个点贼大的

```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define fr(k) edge[k].from
#define nx(k) edge[k].next
#define ev(k) edge[k].value
#define to(k) edge[k].to
#define ll long long
const ll maxn=100000;
ll hd[maxn],mm[maxn],c[maxn],d[maxn],f,n,m,w,x,y,z;
bool m1[maxn],mark;
struct edge
{
    ll from,next,value,to;
}edge[maxn<<1];
void add(ll x,ll y,ll v,ll k)
{
    fr(k)=x;
    to(k)=y;
    ev(k)=v;
    nx(k)=hd[x];
    hd[x]=k;
}
ll spfa(ll s)
{
    ll l,r;
    memset(m1,false,sizeof(m1));
    memset(mm,0,sizeof(mm));
    memset(c,0,sizeof(c));
    l=1;
    r=1;
    c[1]=s;
    d[s]=0;
    m1[s]=true;
    mm[s]=1;
    for (int i=1;i<=n;i++)
        if (i!=s) d[i]=2147483647;
    while (l<=r)
    {
        for (int i=hd[c[l]];i!=0;i=nx(i))
            if (ev(i)+d[c[l]]<d[to(i)])
            {
                d[to(i)]=ev(i)+d[c[l]];
                if (m1[to(i)]==false)
                {
                    r++;
                    c[r]=to(i);
                    m1[to(i)]=true;
                    mm[to(i)]++;
                    if (mm[to(i)]>n) return 1;
                }
            }
        m1[c[l]]=false;
        l++;    
    }
    return 0;
}
int main()
{
    scanf("%d",&f);
    for (int i=1;i<=f;i++)
    {
        memset(edge,0,sizeof(edge));
        memset(hd,0,sizeof(hd));
        scanf("%lld%lld%lld",&n,&m,&w);
        for (int j=1;j<=m;j++)
        {
            scanf("%lld%lld%lld",&x,&y,&z);
            add(x,y,z,j);
            add(y,x,z,j+m);
        }
        for (int j=1;j<=w;j++)
        {
            scanf("%lld%lld%lld",&x,&y,&z);
            add(x,y,-z,2\*m+j);
        }
        if (spfa(1)==1) printf("YES\n");
            else printf("NO\n");
    }
    return 0;
}

---

## 作者：fuking (赞：0)

这题可以用SPFA做，跑得很快

###**但是用Bellman-Ford判负环更简（ruo）单（zhi）直接，也（dan）更（shi）不（hui）容（man）易（yi）出（dian）错**

这里是Bellman-Ford

Bellman-Ford对每一条边已经做了n-1次松弛操作。如果再进行n-1次松弛后，仍然可以继续成功松弛，则该图必然存在负权环

当然为了防止MLE，不要用邻接矩阵，用邻接表或者链式前向星会省很多空间

注意：

1.有多个农场

2.有负环是YES，没负环是NO，不要弄反了

3.小路是无向边！虫洞是有向边！

4.这种算法比神犇们的SPFA简单很多，所以理解就好，别抄代码

附上代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
const int maxn=5550;//数组开大点，RE你懂的 
int dis[maxn],u[maxn],v[maxn],w[maxn]; //用邻接表防止MLE
const int inf=1e9;
int main(){
    int TT;cin>>TT;
    for(int ii=1;ii<=TT;ii++){//注意有多个农场 
        memset(dis,0,sizeof(dis));
        memset(u,0,sizeof(u));
        memset(v,0,sizeof(v));
        memset(w,0,sizeof(w));//每次计算的时候要初始化 
        int n,m,W;cin>>n>>m>>W;
        for(int i=1;i<=m;i++){
            int x,y,z;scanf("%d%d%d",&x,&y,&z);
            u[i]=v[i+m]=x;
            v[i]=u[i+m]=y;
            w[i]=w[i+m]=z;//小路是无向的 
        }
        m*=2;//由于小路是无向的，边数要乘2 
        for(int i=1;i<=W;i++){
            int x,y,z;scanf("%d%d%d",&x,&y,&z);
            u[i+m]=x;v[i+m]=y;w[i+m]=-z;//虫洞是有向的 
        }m+=W;//边数再加上虫洞数量 
        for(int i=1;i<=n;i++)dis[i]=inf;
        dis[1]=0;
        for(int k=1;k<=n-1;k++){
            for(int i=1;i<=m;i++){
                if(dis[v[i]]>dis[u[i]]+w[i]){
                    dis[v[i]]=dis[u[i]]+w[i];
                }
            }
```
}//跑一遍Bellman-Ford

```cpp
        bool flag=false;
        for(int i=1;i<=m;i++)
            if(dis[v[i]]>dis[u[i]]+w[i])flag=true;//判负环，再进行n-1松弛，还能成功松弛，就存在负环 
        if(flag)cout<<"YES"<<endl;
        else cout<<"NO"<<endl;//输出
    }
    return 0;
}

```

---

## 作者：licone (赞：0)

SPFA判负环~

经过次数大于n时，输出yes即可~

（加边用了数组模拟，感觉写得挺简洁的……）

（不用考虑重边，直接加就可以了~）


  
  
  
  
```cpp
#include<cstdio>  
#include<cstring>  
#include<iostream>  
#include<queue>  
using namespace std;  
int T,n,m,W,s,e,t,fi[10001],ne[10001],w[10001],v[10001],cnt,num[10001],tot[10001];  
bool b[10001];  
void add(int u,int vv,int val)  
{  
    w[++cnt]=vv;ne[cnt]=fi[u];fi[u]=cnt;v[cnt]=val;  
}  
void cal()  
{  
    for(int i=1;i<=n;i++) num[i]=999999999;  
    queue<int> q;q.push(1);b[1]=1;num[1]=0;tot[1]=1;  
    while(!q.empty())  
    {  
        int k=q.front();q.pop();b[k]=0;  
        if(tot[k]>n)  
        {  
            printf("YES\n");return;  
        }  
        for(int j=fi[k];j;j=ne[j])  
          if(num[w[j]]>v[j]+num[k])  
          {  
            num[w[j]]=v[j]+num[k];  
            if(!b[w[j]])  
            {  
                q.push(w[j]);b[w[j]]=1;tot[w[j]]++;  
            }  
          }  
    }  
    printf("NO\n");  
}  
int main()  
{  
    scanf("%d",&T);  
    while(T--)  
    {  
        scanf("%d%d%d",&n,&m,&W);  
        memset(fi,0,sizeof(fi));  
        memset(tot,0,sizeof(tot));  
        memset(b,0,sizeof(b));cnt=0;  
        for(int i=1;i<=m;i++)  
        {  
            scanf("%d%d%d",&s,&e,&t);  
            add(s,e,t);add(e,s,t);  
        }  
        for(int i=1;i<=W;i++)  
        {  
            scanf("%d%d%d",&s,&e,&t);  
            add(s,e,-t);  
        }  
        cal();  
    }  
    return 0;  
}  

```

---

## 作者：saisai (赞：0)

//判断有无负环的方法： 

一个点背经过n次以上就说明有负环，所以这个题只需要在spfa的基础上加一个判断就好了

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<queue>
#define INF 2000000000
using namespace std;
const int maxn=1000+100;
const int maxm=10000+100;
struct Edge{int u,v,w,next;};
Edge e[maxm];
int g[maxn],inq[maxn];
int d[maxn],cnt[maxn];
int N,M,W;
void init(){
    cin>>N>>M>>W;
    int u,v,w;
    memset(g,0,sizeof(g));//勿忘 
    for(int i=1;i<=M;i++){        
        scanf("%d%d%d",&u,&v,&w);
        e[2*i-1]=(Edge){u,v,w,g[u]};g[u]=2*i-1;
        e[2*i]=(Edge){v,u,w,g[v]};g[v]=2*i;
    }
    for(int i=1;i<=W;i++){
        scanf("%d%d%d",&u,&v,&w);
        e[2*M+i]=(Edge){u,v,-w,g[u]};g[u]=2*M+i;
    }
}
int spfa(int s){
    queue<int>q;
    memset(inq,0,sizeof(inq));
    memset(cnt,0,sizeof(cnt));
    for(int i=1;i<=N;i++) d[i]=INF;
    d[s]=0;
    q.push(s);
    inq[s]=1;cnt[s]=1;
    while(!q.empty()){
        int u=q.front();q.pop();
        inq[u]=0;
        if(cnt[u]>N) return 1;
        for(int i=g[u];i>0;i=e[i].next){
            int v=e[i].v,w=e[i].w;
            if(d[u]+w<d[v]){
                d[v]=d[u]+w;
                if(!inq[v]){
                    q.push(v);
                    inq[v]=1;
                    cnt[v]++;
                }
            }
        }    
    }
    return 0;
}
int main(){
    int T;
    cin>>T;
    while(T--){
        init();
        if(spfa(1)) cout<<"YES\n";
        else cout<<"NO\n";        
    }
    return 0;
}
```

---

## 作者：Erina (赞：0)

神犇们都用SPFA，蒟蒻来发个Bellman-Ford

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
double dis[5000],w[5000],minl;//w记录路的长度
int n,m,x,y,k,f[5000][3],s,t,len;//f记录了边的两端
int bh;
bool black[5000];//如果是黑洞black[i]==1
int hhh;
bool flag;
bool b[5000];
int main(){
    cin>>hhh;
    for(int hhhh=0;hhhh<hhh;hhhh++){
        flag=0;
        cin>>n;
        cin>>m;
        cin>>bh;
        for(int i=0;i<m;i++){
            dis[i]=0xfffffff/3;
            f[i][1]=f[i][2]=dis[i];
        }
        for(int i=0;i<m;i++){
            cin>>x>>y>>len;
            f[i][1]=x;f[i][2]=y;
            w[i]=len;
        }
        for(int i=m;i<m+bh;i++){
            cin>>x>>y>>len;
            black[i]=1;
            f[i][1]=x;f[i][2]=y;
            w[i]=-len;
        }
        dis[0]=0;//单独判负权时不需要单独设起始点
        for(int i=0;i<n;i++){
            for(int j=0;j<m+bh;j++){
                if(dis[f[j][1]]+w[j]<dis[f[j][2]])dis[f[j][2]]=dis[f[j][1]]+w[j];
                if(!black[j])if(dis[f[j][2]]+w[j]<dis[f[j][1]])dis[f[j][1]]=dis[f[j][2]]+w[j];
            }
        }
        for(int j=0;j<m+bh;j++){//要是存在一条边（u,v）让dis[u]+w[u]<dis[v]存在负权
            if(dis[f[j][1]]+w[j]<dis[f[j][2]]){
                if(!flag)
                cout<<"YES"<<endl;
                flag=1;
            }
            if(!black[j])if(dis[f[j][2]]+w[j]<dis[f[j][1]]){
                if(!flag)//小心！！这里很容易错！！
                cout<<"YES"<<endl;
                flag=1;
            }
        }
        if(!flag)cout<<"NO"<<endl;
    }
}
```

---

## 作者：睿屿青衫 (赞：0)

#都说dfs版的spfa比较快，可是周围的神犇们bfs都过了，我的dfsT了两个点74分

##不要抄代码这是74！74！74！过不了的

###就是个负环的模板题，大佬们说这道题其实用bfs就行

加一下博客（可能停更，但大家可以去看一下友链里面的大佬）

[睿少个人博客](http://blog.ruishao.cf/)

、、、cpp

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 2510
using namespace std;
struct EDGE
{
    int next;
    int to;
    int co;
}edge[maxn];
int f,qr,n,m,w,a,b,l,head[maxn],dis[maxn],exist[maxn],flag;
void add(int from,int to,int co)
{
    edge[++qr].next=head[from];
    edge[qr].to=to;
    edge[qr].co=co;
    head[from]=qr;
}
int read()
{
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9')
     {
         x=x*10+ch-'0';
         ch=getchar();
     }
    return x;
}
void dfs_spfa(int x)
{
    if(flag) return;
    exist[x]=1;
    for(int i=head[x];i;i=edge[i].next)
     {
         int v=edge[i].to;
         if(dis[v]>dis[x]+edge[i].co)
          {
              dis[v]=dis[x]+edge[i].co;
              if(flag||exist[v])
               {
                   flag=1;
                   break;
               }
                else dfs_spfa(v);
          }
     }
    exist[x]=0;
}
int main()
{
    f=read();
    for(int o=1;o<=f;++o)
     {
         memset(dis,0,sizeof(dis));
         memset(exist,0,sizeof(exist));
         memset(head,0,sizeof(head));
         qr=0;
         n=read();m=read();w=read();
         for(int i=1;i<=m;++i)
          {
              a=read();
              b=read();
              l=read();
              add(a,b,l);
              add(b,a,l);
          }
        for(int i=1;i<=w;++i)
         {
             a=read();
             b=read();
             l=read();
             add(a,b,-l);
         }
        flag=0;
        for(int i=1;i<=n;++i)
         {
             if(flag) break;
            dfs_spfa(i);
         }
        if(flag) printf("YES\n");
         else printf("NO\n");
     }
    return 0;
}
、、、
```

---

