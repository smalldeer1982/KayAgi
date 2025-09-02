# [AHOI2017初中组] guide

## 题目描述

农场主John最近在网上买了一辆新车，在购买汽车配件时，John不小心点了两次“提交”按钮。导致汽车上安装了两套GPS系统，更糟糕的是John在使用GPS导航时，两套系统常常给出不同的路线。从地图上看，John居住的地区有N(2 ≤ N ≤ 100,000)个十字路口和M(1 ≤ M ≤ 500,000)条限定通行方向的道路。第i条道路连接路口 A\_i (1 ≤ A\_i ≤ N)和B\_i (1 ≤ B\_i ≤ N)，两个路口之间可能连接有多条道路。允许双向通⾏的道路是将两条单向通⾏的道路隔开所形成的。


John的家在路口1位置，农场在路口N的位置。John可以沿着⼀系列单向道路从家驾车到农场。所有GPS系统的底层地图信息都是⼀样的，区别仅在于对每一条道路的通⾏时间计算不同。对于第i条道路第一套GPS系统计算通行时间为P\_i个单位时间，而第二套GPS系统则给出Q\_i个单位时间。（所有道路的通行时间都是范围在1到100，000之间的整数）John想要驾车从家到农场。可是，一路上GPS系统总是不厌其烦的提醒John（请从路口X开往路口Y），这是由于John选取了某套GPS系统建议的路径，而另一套GPS系统则认为这不是从路口X到农场的最短路径。我们称之为GPS系统的抱怨。


请你计算一下如果John选择合适的路径到达农场能听到的最少GPS系统的抱怨数 。如果John经过某条道路两套GPS系统都发出抱怨，则抱怨总数加2。


## 样例 #1

### 输入

```
5 7 3 4 7 1
1 3 2 20
1 4 17 18
4 5 25 3
1 2 10 1
3 5 4 14
2 4 6 5```

### 输出

```
1```

# 题解

## 作者：houpingze (赞：15)

提供一种不一样的解法（

~~也就想、调了5h吧，嗯不算长![/cy](https://cdn.luogu.com.cn/upload/pic/62225.png)~~

考虑$3$次`SPFA`。

第一次，我们使用`SPFA`建立 $Mx$数组，$Mx_i$表示**导航1认为的**$1$到$n$的最短路径 。

第二次，我们再一次使用`SPFA`建立 $My$数组，$My_i$表示**导航2认为的**$1$到$n$的最短路径。

注意区分$p_i$和$q_i$不要写错了

## 重点来了！

我们可以再建一个图$G$，其中$G_{i,j}$表示从结点$i$走到结点$j$，抱怨数之和，当然结点$i$和结点$j$有直接的边相连。

那么咋算有直接边的两点之间的抱怨数和呢？


我们想到，如果从$i$结点出发，到$j$结点，第一个GPS会抱怨，当前仅当$Mx_i+u\neq Mx_j$（**注意是$\neq$**）。

其中u为第一个GPS认为的从$i$结点出发，到$j$结点的时间。

第二个GPS会抱怨的情况也同理。

我们可以把经过每条边的抱怨值都算出来（第一个GPS是否抱怨+第二个GPS是否抱怨），构成一个图，再跑一遍`SPFA`，就可以算出抱怨值最小是多少了。





---

## 作者：Misaka19280 (赞：14)

这题怕是USCAO的题

这道题的题目大意是说有两个系统，他们对于1到n的每条路径的点的时间不一样，所以对于最短路的判定也不一样

如果你走的路和某套系统的最短路判定不一样，则这个系统会抱怨一次。你需要使抱怨最少。

思路非常简单

首先你必须求出两套系统的最短路

然后用这两套系统的最短路重新建图，权值为走这条路的抱怨数

```
if (d1[v]!=d1[u]+w1) cnt++;
if (d2[v]!=d2[u]+w2) cnt++;
G[i][j].w[0]=cnt;
```
像这样

然后再用这个图跑一遍最短路，就过了

这题数据范围比较大，所以要用spfa或dijstra

```
#include<iostream>
#include<queue>
#include<vector>
using namespace std;
const int INF=1000000;
struct edge
{
	int to;
	int w[2];
};

vector<edge> G[500010];
int d1[500010];
int d2[500010];
int n,m;
bool used[500010];

void spfa(int d[],int mode)
{
	for (int i=1;i<=n;i++)
	{
		d[i]=INF;
		used[i]=false;
	}
	queue<int> q;
	d[n]=0;
	q.push(n);
	used[n]=true;
	while (!q.empty())
	{
		int u=q.front();q.pop();
		used[u]=false;
		for (int i=0;i<G[u].size();i++)
		{
			edge e=G[u][i];
			int v=e.to;
			int w=e.w[mode];
			if (d[v]>d[u]+w)
			{
				d[v]=d[u]+w;
				if (!used[v])
				{
					q.push(v);
					used[v]=true;
				}
			}
		}
	}
}	

int main()
{
	cin>>n>>m;
	
	for (int i=1;i<=m;i++)
	{
		int u,v,w1,w2;
		cin>>u>>v>>w1>>w2;
		edge e;
		e.to=u;
		e.w[0]=w1;
		e.w[1]=w2;
		G[v].push_back(e);
	}
	spfa(d1,0);
	spfa(d2,1);
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<G[i].size();j++)
		{
			edge e=G[i][j];
			int u=i,v=e.to,w1=e.w[0],w2=e.w[1];
			int cnt=0;
			if (d1[v]!=d1[u]+w1) cnt++;
			if (d2[v]!=d2[u]+w2) cnt++;
			G[i][j].w[0]=cnt;
		}
	}
	spfa(d1,0);
	cout<<d1[1];
	return 0;
}
```

后天AHOI，RP++

---

## 作者：AC_Evil (赞：12)

这道题乍一看很难，我们来仔细分析一下


本题说的是John有两个GPS系统（题目好像改了，不过意义一样），给了n个点和m条边。唯一独特的是，两个GPS所给的路途时间不同，所以从点1到点n的最短路径不同。如果John从当点走的路线与两个GPS给的从当点到终点的最短路径不同，则GPS会抱怨（一个不同抱怨一下，两个的话两下），求最少抱怨总数。


怎么判断走这条边会抱怨几次呢？


我们无论怎么走，都是要从此点沿最短路径走到终点，不妨我们都用最短路径算法求出两个GPS从点1->n-1到点n的最短路径（就是以点n为源点，求到所有点的最短路径，反过来就是从点1->n-1到点n的最短路径了。这里要注意，反着求的时候，边的方向要反过来，否则求得的结果是错误的！！）


由于极限情况是100000个点，只能选择效率高的算法，例如SPFA，或者我写的dijkstra堆优化版。


求得两个GPS从前n-1个点到终点的最短路径后，判断走这条边，是否抱怨，方法不难：枚举每条边，沿着这条边走时，若原来该点的最短路径值 - 该边的权值（即时间）=下一点的最短路径时，说明该边是最短路径上的一条边，不会抱怨；若不等于，则说明该边不是最短路径上的边，该边抱怨次数+1。于是我们得到了每条边抱怨的次数。


最后再以抱怨次数为边的权值，求一下从起点到终点的最短路径，即为最少抱怨数。


时间复杂度：O(nlogn)；空间复杂度：O(m)；//堆及数组的开支为m


话说数据范围好像和比赛的不一样啊。。。我用的是比赛时的范围。


下面是程序（我加了防抄袭处理，希望大家认真对待这道题，不要投机取巧）

        
    
    
    




    
        
        
    
    
    
    
    
    
    
        
    

```cpp
type
    arr=array[0..100000] of record .//定义基类型
        x,y.long:longint; .//起点、终点、时间
    end;
var
    g:array[1..3,1..50000] of longint; .//
    e:array[1..3] of arr;
    s,t:array[0..50000] of longint;
    n,m.i,x.y,w1.w2:longint;
    heap,p1.p2:array[1..50000] of longint;
procedure sort(l,r:longint;var a:arr);
var    i.j.mid:longint;
begin
    i:=l; j:=r;
    mid:=a[(l+r) div 2].x;
    repeat
        while a[i].x<mid do inc(i);
        while a[j].x>mid do dec(j);
        if i<=j then
            begin
                a[0]:=a[i];a[i]:=a[j];a[j]:=a[0];
                inc(i); dec(j);
            end;
    until i>j;
    if l<j then sort(l,j,a);
    if i<r then sort(i,r,a);
end;
procedure swap(x,y:longint);
var t:longint;
begin
    t:=heap[x]; heap[x]:=heap[y]; heap[y]:=t;
    p2[p1[x]]:=y;p2[p1[y]]:=x;
    t:=p1[x]; p1[x]:=p1[y]; p1[y]:=t;
end;
procedure delete(x:longint);
var    i:longint;
begin
    swap(1,x);
    dec(x);
    i:=2;
    while i<=x do
    begin
        if (i<x) and (heap[i]>heap[i+1]) then inc(i);
        if heap[i]<heap[i shr 1] then swap(i,i shr 1) else exit;        
        i:=i shl 1;
    end;
end;
procedure move(x:longint);
begin
    while x<>1 do
    begin
        if heap[x]<heap[x shr 1] then swap(x,x shr 1) else exit;
        x:=x shr 1; .//这里用的是位移，速度快，但习惯让我在赛场上打成了2，结果还好，差点爆0。
    end;
end;
procedure dijkstar(xx:longint); .//dijkstra堆优化算法核心。不懂的上网度下，这里不解释了
var
        i.j.k:longint;
begin
    fillchar(heap,sizeof(heap),$7f);
    heap[1]:=0;
    for i:=n downto 1 do
        begin
            p1[n-i+1]:=i;
            p2[n-i+1]:=i;
        end;
    for i:=n downto 2 do
    begin
        delete(i);
        for j:=s[p1[i]] to t[p1[i]] do
            if heap[i]+e[xx,j].long<heap[p2[e[xx,j].y]] then
            begin
                heap[p2[e[xx,j].y]]:=heap[i]+e[xx,j].long;
                move(p2[e[xx,j].y]);
            end;
        g[xx,p1[1]]:=heap[1];
    end;
end;
begin
    readln(n,m);
    for i:=1 to m do
        begin
            readln(x,y,w1,w2);
            e[1,i].x:=y;e[1,i].y:=x;e[1,i].long:=w1; .//两台GPS边的反处理
            e[2,i].x:=y;e[2,i].y:=x;e[2,i].long:=w2;
        end;
    sort(1,m,e[1]); .//以起点为关键字，排序
    sort(1,m,e[2]);
    fillchar(t,sizeof(t),-1); .//将数组初始化为-1
    e[1,0].x:=0; .// s[i],t[i]记录以点i为起点的边在数组中的区间
    for i:=1 to m do
        if e[1,i].x<>e[1,i-1].x then
            begin
                s[e[1,i].x]:=i;
                t[e[1,i-1].x]:=i-1;
            end;
    t[e[1,m].x]:=m;
    dijkstar(1); .//两趟最短路径
    dijkstar(2);
    for i:=1 to m do
    begin
        e[3,i].x:=e[1,i].x; // 复制边的信息
        e[3,i].y:=e[1,i].y;
        if g[1,e[1,i].y]-e[1,i].long<>g[1,e[1,i].x] then inc(e[3,i].long); //判断是否会抱怨
        if g[2,e[2,i].y]-e[2,i].long<>g[2,e[2,i].x] then inc(e[3,i].long);
    end;
    dijkstar(3); // 最后一趟最短路径
    writeln(g[3,1]); // 输出
end.
再次申明，请大家不要抄袭，后果自负
```

---

## 作者：Zekrom (赞：6)

同[P3106](https://www.luogu.org/problemnew/show/P3106)完全一样的题目，处理出对任意一个GPS求出的最短距离di    
再对于任意一条边是不是某个GPS的最短路，在求一次最短路  
总上：只要求三遍最短路   
注意点：建边时建反向边，因为GPS表示u到n的最短路    
上代码：    
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#define N 100010
#define M 500010
using namespace std;
int n,m,Q,P,head[N],tot,x[M],y[M],v1[M],v2[M];
bool vis[N];
int d[N],d1[N],d2[N]; 
struct node{
	int id,s;
	node(int x,int y){id=x;s=y;}
};
struct Edge{
	int v,next,val;
}edge[M]; 
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return  x*f;
}
inline void add(int x,int y,int z){edge[++tot].v=y;edge[tot].val=z;edge[tot].next=head[x];head[x]=tot;}
void dijk(int s){
	priority_queue<pair<int,int> >q1;memset(d,0x3f,sizeof(d));memset(vis,0,sizeof(vis));
	q1.push(make_pair(0,s));d[s]=0;
	while(q1.size()){
		int u=q1.top().second;q1.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].v,z=edge[i].val;
			if(d[v]>d[u]+z){
				d[v]=d[u]+z;
				q1.push(make_pair(-d[v],v));
			}
		}
	}
}
int main()
{
	n=read();m=read(); 
	for(int i=1;i<=m;i++){
		x[i]=read(),y[i]=read(),v1[i]=read(),v2[i]=read();
		add(y[i],x[i],v1[i]);
	}
	dijk(n);for(int i=1;i<=n;i++)d1[i]=d[i];
	memset(head,0,sizeof(head));tot=0;
	for(int i=1;i<=m;i++)
		add(y[i],x[i],v2[i]);
	dijk(n);for(int i=1;i<=n;i++)d2[i]=d[i];
	memset(head,0,sizeof(head));tot=0;
	for(int i=1;i<=m;i++){
		int sum=0;
		if(d1[x[i]]!=d1[y[i]]+v1[i])sum++;
		if(d2[x[i]]!=d2[y[i]]+v2[i])sum++;
		add(x[i],y[i],sum);
	} 
	dijk(1);
	printf("%lld\n",d[n]); 
	return 0;
}

```


---

## 作者：Eismcs (赞：4)

看上去此题很棘手，但是只要慢慢推理便可以“顺利”解题

**1.**一看此题就知道该用最短路径，由于数据很大，所以我们用spfa来解，并用链式前向星存储。

**2.**因为答案要求的是最少抱怨值，所以我们要知道两个GPS分别指的路是什么，也就是我们要找到这两个GPS所指的“最短路径”。

**3.**我们求出两个GPS所指的“最短路径”后，需要重新构图，以从这个点到另一个点的抱怨值，再求一次最短路。至于判断我们只需用求出的最短路径来判断是否走了此路入x为此点，y为此边到达的点，z为这条边的权值。则如果
```cpp
 f[y]!=f[x]+z
```
就说明此边没有经过，GPS会抱怨。

**4.**spfa原来的dis[i]表示从原点到i这个点的最短路径，此题的原点明显为1。但是由于为了统计到点n是否经过了某便，所以我们需要倒着求，同样存储时也要倒着


最后便是调试代码了。我代码由于我的想法变来变去，写得贼丑，有点啰嗦。需要改进。

下面是用时89ms的代码。各个重要的已在代码中标出对应序号。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=0,ff=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*ff;
}
int h[100010],me,f[100010],n,m,fl[100010];
bool b[100010];
//1
struct qxx{
    int to,next,xa,ya;
}a[500005];
void add(int x,int y,int zs,int zz){
    a[++me].next=h[x];
    a[me].to=y;
    a[me].xa=zs;a[me].ya=zz;
    h[x]=me;
}
//1
void spfa(int x){
    int c,e,y;
    if(x)for(int i=0;i<=n;i++)f[i]=1<<30,b[i]=0;
    else for(int i=0;i<=n;i++)fl[i]=1<<30,b[i]=0;
    if(x)f[n]=0,b[n]=1;
    else fl[n]=0,b[n]=1;
    queue<int> p;
    p.push(n);
    while(!p.empty()){
        c=p.front();p.pop();
        e=h[c];b[c]=0;
        while(a[e].next){
            y=(x)?a[e].xa:a[e].ya;
            if(x)if(f[a[e].to]>f[c]+y){
                f[a[e].to]=f[c]+y;
                if(!b[a[e].to]){
                    b[a[e].to]=1;
                    p.push(a[e].to);
                }
            }
            if(!x)if(fl[a[e].to]>fl[c]+y){
                fl[a[e].to]=fl[c]+y;
                if(!b[a[e].to]){
                    b[a[e].to]=1;
                    p.push(a[e].to);
                }
            }
            e=a[e].next;
        }
        y=(x)?a[e].xa:a[e].ya;
        if(x)if(f[a[e].to]>f[c]+y){
            f[a[e].to]=f[c]+y;
            if(!b[a[e].to]){
                b[a[e].to]=1;
                p.push(a[e].to);
            }
        }
        if(!x) if(fl[a[e].to]>fl[c]+y){
                fl[a[e].to]=fl[c]+y;
                if(!b[a[e].to]){
                    b[a[e].to]=1;
                    p.push(a[e].to);
                }
            }
    }
}
int main(){
    int x,y,zs,zz;
    n=read();m=read();
    for(int i=1;i<=m;i++){
    	x=read();y=read();zs=read();zz=read();
        //4
    	add(y,x,zs,zz);
    }
    //2
    spfa(1);
    spfa(0);
    //3
    for(int i=1;i<=n;i++){
        int e=h[i];
        for(;e;e=a[e].next){
            x=a[e].xa;y=a[e].ya;
            int t=0;
            if(f[a[e].to]!=f[i]+x)t++;
            if(fl[a[e].to]!=fl[i]+y)t++;
            a[e].xa=t;
        }
    }
    spfa(1);
    printf("%d\n",f[1]);
    return 0;
}
```

---

## 作者：Chavapa (赞：2)

## 重点+坑点：必须反向建边，从点n开始跑最短路

注意读题：**每次到达一个节点，GPS都是推荐你走从这一个节点到农场的最短路径**

也就是说，你必须从终点开始跑最短路。

显然，对于两套不同的$GPS$系统（仅权值不同的两张图），我们需要跑两遍最短路，将这些最短路所经过的边打标记。

然后我们用这两套系统的最短路重新建图，权值为走这条路的抱怨数，从节点$n$开始再跑一遍最短路即可。

 对于这样庞大的无负权稠密图，**强烈推荐使用堆优化版的$Dijkstra$**。
 
 ## Code（Pascal）
 
 ```c
 program Luogu_P3720;
var a,b,cost1,cost2,next,f:array[0..1000010] of qword;
    vis:array[0..100010] of boolean;
    dis,head,h,p,from:array[0..100010] of qword;
    n,m,s,x,y,z,zz,cnt,len:qword; i:longint;
  procedure add(x,y,z,zz:qword);
  begin
    inc(cnt); a[cnt]:=x; b[cnt]:=y;
    cost1[cnt]:=z; cost2[cnt]:=zz;
    next[cnt]:=head[x]; head[x]:=cnt;
  end;
  procedure push(x,y:qword);  //堆操作
  var t:qword; i:longint;
  begin
    inc(len); h[len]:=x; p[len]:=y;
    i:=len;
    while (i>1)and(h[i]<h[i>>1]) do
    begin
      t:=h[i]; h[i]:=h[i>>1]; h[i>>1]:=t;
      t:=p[i]; p[i]:=p[i>>1]; p[i>>1]:=t;
      i:=i>>1;
    end;
  end;
  procedure pop;
  var t,x:qword; i:longint;
  begin
    h[1]:=h[len]; p[1]:=p[len];
    dec(len);
    i:=1;
    while i<<1<=len do
    begin
      if (i<<1+1>len)or(h[i<<1]<h[i<<1+1]) then x:=i<<1 else x:=i<<1+1;
      if h[i]>h[x] then
      begin
        t:=h[i]; h[i]:=h[x]; h[x]:=t;
        t:=p[i]; p[i]:=p[x]; p[x]:=t;
        i:=x;
      end
      else break;
    end;
  end;
  procedure dijkstra(s,num:longint);
  var u,d,cost:qword; i:longint;
  begin
    for i:=1 to n do dis[i]:=99999999999999;
    dis[s]:=0;
    push(0,s);
    fillchar(vis,sizeof(vis),false);
    while len>0 do
    begin
      d:=h[1]; u:=p[1];
      pop;
      if vis[u] then continue;
      vis[u]:=true;
      dec(f[from[u]]);  //是最短路的一部分，抱怨值--
      i:=head[u];
      while i<>0 do
      begin
        if num=1 then cost:=cost1[i]
        else if num=2 then cost:=cost2[i]
        else cost:=f[i];
        if d+cost<dis[b[i]] then
        begin
          dis[b[i]]:=d+cost; push(dis[b[i]],b[i]);
          from[b[i]]:=i;  //记录来时的路径
        end;
        i:=next[i];
      end;
    end;
  end;
begin
  readln(n,m);
  for i:=1 to m do
  begin
    readln(x,y,z,zz);
    add(y,x,z,zz);  //注意反向连边！
  end;
  for i:=1 to cnt do f[i]:=2;  //抱怨值初始为2
  dijkstra(n,1);
  dijkstra(n,2);
  dijkstra(n,3);
  writeln(dis[1]);
end.
 ```

---

## 作者：hongzy (赞：2)

链式前向星存储 + 3次 SPFA.

前两次按两个时间权值SPFA.

不过要以N为源点进行SPFA，这样可以判断一条边在不在最短路径上。

判断方法：若一条边的起点为from，终点为to，权值w，Dis i 表示结点i到N的距离

if Dis from + w == Dis to

then 这条边在最短路径上.

抱怨权值也就能算出了：这条边不在A个导航的最短路径上，这条边的抱怨权值就是A.(A只可能是0，1，2)

最后遍历所有边，把时间权值更改为抱怨值，再SPFA就行了.

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

struct Edge { //链式前向星
    int from, to, next;
    int w[2]; //两个导航给出的权值
} edge[500010];
int head[500010], cnt, N, M;
int Dis1[100010], Dis2[100010]; //i点到终点到最短距离
bool InQue[100010];

inline void Add(int u, int v, int w1, int w2) {
    edge[++cnt].w[0] = w1;
    edge[cnt].w[1] = w2;
    edge[cnt].from = u; //比链式前向星多记录一个from
    edge[cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
}

inline void Update_W(int index) { //把边的值改成抱怨次数
    int W = 0;
    if(Dis1[edge[index].from] + edge[index].w[0] != Dis1[edge[index].to]) W ++;
    if(Dis2[edge[index].from] + edge[index].w[1] != Dis2[edge[index].to]) W ++;
    edge[index].w[0] = W;
}

void SPFA(int *Dis, int x) { //SPFA模版
    int k, to;
    queue<int> Q;
    for(int i=0; i<N; i++) Dis[i] = 1e9, InQue[i] = false;
    Dis[N] = 0;
    Q.push(N); //N为源点 
    InQue[N] = true;
    while(!Q.empty()) {
        k = Q.front();
        Q.pop();
        InQue[k] = false;
        for(int i = head[k]; i != 0; i = edge[i].next) {
            to = edge[i].to;
            if(Dis[to] > Dis[k] + edge[i].w[x]) {
                Dis[to] = Dis[k] + edge[i].w[x];
                if(!InQue[to]) {
                    Q.push(to);
                    InQue[to] = true;
                }
            }
        }
    }
}

int main() {
    int u, v, w1, w2;
    scanf("%d%d", &N, &M);
    for(int i=1; i<=M; i++) {
        scanf("%d%d%d%d", &u, &v, &w1, &w2);
        Add(v, u, w1, w2); //v, u很重要(反过来的)
    }
    SPFA(Dis1, 0);
    SPFA(Dis2, 1);
    for(int i=1; i<=cnt; i++) Update_W(i);
    SPFA(Dis1, 0); //按抱怨值找最短路径
    printf("%d\n", Dis1[1]);
    return 0;
}

```
156ms.~~不过应该还能优化不少地方.~~


---

## 作者：hf_xz (赞：2)

总体思路跟楼下（上？）一样。


显然，如果我们知道走某条边有几个gps会抱怨，并把这个数量设为边权值的话，我们就可以很简单的通过一个最短路算法求出从1到n最少抱怨几次了。


那么我们就要判断走某条边，某个gps是否会抱怨。根据题意，如果这条边在某个gps看来，是最短路上的一条边，那么它就不会抱怨。所以我们要**判断某条边是否在某个gps的图上的最短路里**。这个判断我们可以通过**把边反过来，从终点跑最短路**并处理出来dis数组来判断，这样的dis数组里存的是每个点到终点的最短路。此时如果某条边是从u到v的权值为w的一条边，它在最短路上当且仅当dis[u]+w == dis[v]。


至此，整个题的做法就明了了：


1.反向将图存下来。


2.分别用两个gps的信息从终点跑最短路。


3.遍历所有边，记录gps会抱怨几次。


4.用处理出来的抱怨次数再跑一次最短路。


贴一下C++代码，不要直接粘哦，a不了的。


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

const int maxn = 100005, maxm = 500005;
int n,m;
int h[maxn],frm[maxn],to[maxm],nxt[maxm],l1[maxm],l2[maxm],l3[maxn],tot;
int d1[maxn],d2[maxn],d3[maxn];
//l1,l2是gps的边权，l3是抱怨次数  d1,d2,d3是分别用l1,l2,l3跑的最短路dis数组
bool vis[maxn];

inline void spfa(int len[],int dis[]){
      memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    queue<int> q;
    q.push(n); vis[n] = 1; dis[n] = 0; //从终点开始跑最短路
    while(!q.empty()){
        int u = q.front(); q.pop(); vis[u] = 0;
        for(int i=h[u],v;i;i=nxt[i])
            if(dis[(v = to[i])] > dis[u] + len[i]){
                dis[v] = dis[u] + len[i];
                if(!vis[v]){
                    q.push(v); vis[v] = 1;
                }
            }
    }
}

inline void check(int len[],int dis[]){
    for(int i=1;i<=m;i++)
        if(dis[frm[i]] + len[i] != dis[to[i]])
            l3[i]++; //记录某条边gps抱怨次数
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&v,&u); //反向存边
        to[++tot] = v; frm[tot] = u; nxt[tot] = h[u]; h[u] = tot;
        scanf("%d%d",l1+tot,l2+tot);
    }
    spfa(l1,d1);
    spfa(l2,d2);
    check(l1,d1);
    check(l2,d2);
    spfa(l3,d3);
    printf("%d\n",d3[1]);
    return 0;
}

```


---

## 作者：Suzt_ilymtics (赞：1)

~~五分钟出idea，改了三遍代码原来是因为读错题了（~~

[弱化版](https://www.luogu.com.cn/problem/P3106)

[更好的阅读体验？](https://www.cnblogs.com/Silymtics/p/14824835.html)

## Description

> 简化题意：给你一张有向图，有两个边权。对于每条边 $(u,v)$，通过它的代价（也就是抱怨）就是两种边权不在 $u$ 到 $n$ 的最短路上的边权的数量

## Solution

先来说一下大体思路：

发现两种 GPS 眼中的边权不一样且不会相互影响，把两个 GPS 分开考虑就好了

因为要求的是 $u$ 到 $n$ 的最短路，所以考虑建反图来求。
规定下面讨论是对应的边是给定的反边。

我们把每条边都带上三个权值，分别表示两个 GPS 认为的通过时间和通过这条边的抱怨数。

显然抱怨数初始为 $2$，这条边符合几个 GPS 的要求就在减去几。

已经很明确了，先对两个 GPS 跑最短路，减去对抱怨数的贡献。

然后对抱怨数跑最短路即可。

这里我用的是已经死掉的 $\text{SPFA}$，题目数据应该是用脚造的，并没有卡 $\text{SPFA}$，所以跑的飞快，吸口氧是目前的最优解。

---------------

如何确定一条边$(u,v)$ 是否在 $u$ 到 $n$ 的最短路上？

设 $dis_x$ 表示 $x$ 到 $n$ 的最短路，$e_{u,v}$ 表示边 $(u,v)$ 的长度，如果满足

$$dis_u + e_{u,v} == dis_v$$

那么这条边就在 $v$ 到 $n$ 的最短路上，对应的抱怨数减一。

下面看代码吧

## Code

把三个量放进一个图里，写起来码量更短。

```cpp
/*
Work by: Suzt_ilymics
Problem: 不知名屑题
Knowledge: 垃圾算法
Time: O(能过)
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#define int long long
#define LL long long
#define orz cout<<"lkp AK IOI!"<<endl

using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 5e5+5;
const int INF = 1e9+7;
const int mod = 1e9+7;

struct edge {
    int from, to, t[3], nxt;
}e[MAXN << 1];
int head[MAXN], num_edge = 1;

int n, m;
int dis[MAXN];
bool vis[MAXN];

int read(){
    int s = 0, f = 0;
    char ch = getchar();
    while(!isdigit(ch))  f |= (ch == '-'), ch = getchar();
    while(isdigit(ch)) s = (s << 1) + (s << 3) + ch - '0' , ch = getchar();
    return f ? -s : s;
}

void add_edge(int from, int to, int t1, int t2) { 
    e[++num_edge].from = from, e[num_edge].to = to;
    e[num_edge].t[0] = 2, e[num_edge].t[1] = t1, e[num_edge].t[2] = t2;
    e[num_edge].nxt = head[from]; 
    head[from] = num_edge; 
}

void SPFA(int type) {
    queue<int> q;
    memset(vis, false, sizeof vis);
    memset(dis, 0x3f, sizeof dis);
    q.push(n), dis[n] = 0, vis[n] = true;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = false;
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            if(dis[v] > dis[u] + e[i].t[type]) {
                dis[v] = dis[u] + e[i].t[type];
                if(!vis[v]) q.push(v), vis[v] = true;
            }
        }
    }
}

signed main()
{
    n = read(), m = read();
    for(int i = 1, u, v, t1, t2; i <= m; ++i) {
        u = read(), v = read(), t1 = read(), t2 = read();
        add_edge(v, u, t1, t2);
    }
    for(int k = 1; k <= 2; ++k) {
        SPFA(k); // 分别对两个 GPS 跑最短路
        for(int i = 2; i <= num_edge; ++i) { // 减去最短路上的边的抱怨
            int u = e[i].from, v = e[i].to;
            if(dis[v] == dis[u] + e[i].t[k]) e[i].t[0]--;
        }
    }
//    for(int i = 2; i <= num_edge; ++i) cout<<e[i].from<<" "<<e[i].to<<" "<<e[i].t[0]<<"\n";
    SPFA(0);
    printf("%lld", dis[1]);
    return 0;
}
```

---

## 作者：lili_flyingcutter (赞：1)

**这题运用了重新构图，需三次最短路，前两次求出单终点最短路，为什么要单终点，不是单源点呢？见题 “不是从路口X到农场的最短路径”，所以是单终点。** 

重点来了，求完两个最短路之后，如何重新构图？
 
### 实际上，我们只需枚举每条边，运用“三角不等式”dis[v]==dis[u]+w(u,v),u-v就是就是最短路径上的一条边。
 
这样就可以重新造边权了，在求单源点最短路，用新边权即可。

我用的是dijkstra，速度还行。
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#define r register int
using namespace std;
const int M=100005;
inline void read(int &a){
    a=0;char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')a=(a<<1)+(a<<3)+c-'0',c=getchar();
}
struct N{
    int x;
    long long value;
    bool operator <(const N &a)const{
        return value>a.value;
    }
};
priority_queue<N>q;
int vis[M],aj[M],nx[M],h[M],va[M],top,n,m,vb[M],vc[M];
//va:gps1权值
//vb:gps2权值
//vc:重构图权值
//q:优先队列
long long da[M],db[M];
inline void dijkstra(int s,long long dis[],int val[]){//最短路
    for(r i=1;i<=n;++i)dis[i]=9999999999,vis[i]=0;//初始化
    dis[s]=0;
    q.push((N){s,0});
    while(!q.empty()){
        N tt=q.top();//取堆顶
        int u=tt.x;
        long long w=tt.value;
        q.pop();
        if(vis[u])continue;
        vis[u]=1;
        for(r i=h[u];i;i=nx[i]){
            int v=aj[i],wv=val[i];
            if(!vis[v]&&dis[v]>w+wv)dis[v]=w+wv,q.push((N){v,dis[v]});//松弛操作
        }
    }
    while(!q.empty())q.pop();
}
inline void add(int x,int y){//加边
    aj[++top]=y;nx[top]=h[x];h[x]=top;
}
int main(){
    int x[M],y[M],z,t;
    scanf("%d%d",&n,&m);
    for(r i=1;i<=m;++i){
        read(x[i]);read(y[i]);read(va[i]);read(vb[i]);
        add(y[i],x[i]);//单终点需将边逆转
    }
    dijkstra(n,da,va);//第一遍
    dijkstra(n,db,vb);//第二遍
    for(r i=1;i<=n;++i){
        for(r j=h[i];j;j=nx[j]){
            int v=x[j];
            if(da[v]!=da[i]+va[j])vc[j]++;//不在gps1的最短路上
            if(db[v]!=db[i]+vb[j])vc[j]++;//不在gps2的最短路上
        }
    }
    top=0;
    memset(h,0,sizeof(h));
    for(r i=1;i<=m;++i)add(x[i],y[i]);//单源点逆转回来
    dijkstra(1,da,vc);
    cout<<da[n]<<endl;
    return 0;
}
```

---

## 作者：SIXIANG32 (赞：0)

一道还不错的题，挺考验 CE 一大串的耐心的（不是   
闲话少说，切入正题——  

---
*PS：由于这道题很恶心，要反向存边，所以要跑 $n\sim 1$ 的最短路*  
下面我们称边权集合是 $p$ 的图为图 $p$，边权集合是 $q$ 的图成为图 $q$。  
显而易见的思路，先分别算出来图 $p$ 和 $q$ 中从 $n$ 出发的单源最短路 $dis1$ 和 $dis2$    
然后我们就要运用到很多最短路算法都运用的一个三角形不等式 $dis_v = dis_u + w$，$w$ 代表边权。  
那么如果算出来 $dis1_v \ne dis1_u + w_0$，那么也就是说这条边不在 $p$ 的最短路上，$yyy + 1$。$dis2$ 亦然。重构一张图，最终算出来的这个 $yyy$ 就是这条边的边权，代表走这条边的报警次数。  
对于这张新图，我们只要跑一遍从 $n$ 开始的最短路就行啦~  

---
说起来简单，但是做起来还是要考虑很多东西的。  
很不明白为什么这道题没卡 SPFA（不是  
这里我用 ```vector``` 存图的（菜鸡本性暴露  
上述的算法要跑三次 dij，为了方便我们 dij 传参的时候传一个指针代表 $dis1/dis2/dis3$，这样的话能剩很多代码。  
然后由于我是个懒癌重症患者不想再开四个数组存储 $a_i,b_i,p_i,q_i$ 所以我边权放了两个成一个数组 $val_{0/1}$，$0$ 代表 $p$，$1$ 代表 $q$。  
在跑 dij 的时候搞一个 $k$ 代表是 $val_k$ 的边权。对于求报警的图默认 $k = 0$。  

---
代码：  
```cpp
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#define MAXN 500000
using namespace std;
int k;
struct node {
    int to, val[2];
    node(int t, int p, int q) {
        to = t, val[0] = p, val[1] = q;
    }
    bool operator < (const node &other) const {
		return val[k] > other.val[k];
	}
};
vector <node> gra[MAXN + 10], ngr[MAXN + 10];
bool vis[MAXN + 10];
int dis1[MAXN + 10], dis2[MAXN + 10], dis3[MAXN + 10];
void Dijkstra(int s, int *dis) {//dij，dis 是一个指针，这样会方便一点
    for(int p = 1; p <= MAXN; p++)
        dis[p] = 0x7f7f7f7f;
    memset(vis, 0, sizeof(vis));
	priority_queue <node> que;
	que.push(node(s, 0, 0));
	dis[s] = 0;
	while(!que.empty()) {
		node fr = que.top(); que.pop();
		int u = fr.to;
		if(vis[u]) continue;
		vis[u] = 1;
		for(int p = 0; p < gra[u].size(); p++) {
			int v = gra[u][p].to;
			if(dis[u] + gra[u][p].val[k] < dis[v]) {
				dis[v] = dis[u] + gra[u][p].val[k];
				if(!vis[v])
                    if(k == 0) que.push(node(v, dis[v], 0));
                    else que.push(node(v, 0, dis[v]));
			}
		}
	}
}
int main() {
    int n, m;
    cin >> n >> m;
    for(int p = 1, x, y, P, Q; p <= m; p++) {
        cin >> y >> x >> P >> Q;
        gra[x].push_back(node(y, P, Q));//存图
    }
    k = 0, Dijkstra(n, dis1);
    k = 1, Dijkstra(n, dis2);
    //跑两次
    int yyy = 0;
    //建立新图
    for(int u = 1; u <= n; u++) {
        for(int p = 0; p < gra[u].size(); p++) {
            int v = gra[u][p].to;
            if(dis1[v] != dis1[u] + gra[u][p].val[0]) yyy++;
            if(dis2[v] != dis2[u] + gra[u][p].val[1]) yyy++;
            ngr[u].push_back(node(v, yyy, 0));
            yyy = 0;
        }
    }
    for(int p = 1; p <= n; p++)
        for(int i = 0; i < ngr[p].size(); i++)
            gra[p][i] = ngr[p][i];
    k = 0, Dijkstra(n, dis3);
    cout << dis3[1] << endl;
}
```

---

## 作者：天命之路 (赞：0)

写在前面：这个题目，需要一点巧思。

分析：既然要抱怨次数最短，我们就要先求抱怨次数。

让我们看一下，什么时候，GPS系统会抱怨呢？

当 John 行走在道路 $(x,y)$，且$x$ 到 $n$ 的最短路中没有道路 $(x,y)$，则该系统会抱怨一次。

那么，我们是不是要求每一个点到 $n$ 的最短路？显然不可能，否则我们要做 $n$ 次最短路，显然超时，且大多数数据显得没有必要。

那我们怎么办？

我们考虑把图反过来，把$(x,y)$ 变成$(y,x)$，那么，每一个点到$n$ 的最短路就变成了$n$ 到每一个点的最短路，对于两套系统，我们只要跑两遍最短路即可。

完成最短路后，判定一条边$(x,y)$ 在不在最短路径上就十分简单了，设最短路数组为$dis$ ,一条边$(x,y,w)$ 不在最短路上当且仅当$dis[x]+w\ne dis[y]$。对于每一条边，我们只需要求出它在两套系统中分别属不属于最短路，就可以得到经过这条边的抱怨次数。接下来只要以抱怨次数为边权，再重新跑一遍最短路即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
void read(T &a)   //快读
{
 	char ch;int sign=1;
 	for(ch=getchar();!isdigit(ch);ch=getchar())
 	if(ch=='-') sign=-1;
 	a=ch&15;
 	for(ch=getchar();isdigit(ch);ch=getchar())
 	a=(a<<3)+(a<<1)+(ch&15);
 	a*=sign;
}
const int N=1e5+5,M=5e5+5;

struct node
{
	int id,dis;  //id 为节点编号，dis 为所对应最短路
	bool operator <(const node &p)const  //重载运算符，定义比较方式
	{
		return dis>p.dis;
	}
	node(){}
	node(int _id,int _dis)
	{
		id=_id,dis=_dis;
	}
};
int vst[N],n,m;
priority_queue<node>q;
struct graph
{
	int fir[N],nxt[M],to[M],w[M],st[M],ect=0,dis[N];
	
	inline void dij(int s)
	{
		for(int i=1;i<=n;i++) dis[i]=0x7f7f7f7f;
		memset(vst,0,sizeof vst);
		dis[s]=0;
		q.push(node(s,0));
		while(q.size())
		{
			int x=q.top().id;
			q.pop();
			if(vst[x]) continue;
			vst[x]=1;
			for(int i=fir[x];i;i=nxt[i])
			{
				int y=to[i],z=w[i];
				if(dis[y]>dis[x]+z)
				dis[y]=dis[x]+z,
				q.push(node(y,dis[y]));
			}
		}
	}
	inline void addedge(int u1,int v1,int w1)
	{
		nxt[++ect]=fir[u1];fir[u1]=ect;st[ect]=u1;to[ect]=v1;w[ect]=w1;
	}
}gr1,gr2,gres;

//gr1,gr2 分别是两套系统的反图，gres 是最后重构的图
int main()
{
	read(n);read(m);
	for(int i=1,x,y,p,q;i<=m;i++)
	{
		read(x);read(y);read(p);read(q);
		gr1.addedge(y,x,p);
		gr2.addedge(y,x,q);
	}
	gr1.dij(n);
	gr2.dij(n);  //两遍最短路，用堆优化+Dijkstra
	for(int i=1;i<=m;i++)   //依据最短路的结果重构图
	{
		int x=gr1.st[i],y=gr1.to[i],rw=0;
		if(gr1.dis[x]+gr1.w[i]!=gr1.dis[y]) rw++;
		if(gr2.dis[x]+gr2.w[i]!=gr2.dis[y]) rw++;
		gres.addedge(y,x,rw);
		
	}

gres.dij(1);  //最后跑一遍最短路
cout<<gres.dis[n];

}

```

---

## 作者：水無月嘉祥 (赞：0)

$$\Huge\color{gold}\texttt{My Blog}$$
**双倍经验**请做[$\huge\texttt{P3106}$](https://www.luogu.com.cn/problem/P3106)

# 前言

最开始的时候我还说“这题怎么是蓝题？充其量一道绿题吧”

然而事实无情的打了我的脸……

## 前置知识

最短路算法、最短路问题变种（多起点同终点）、记录最短路路径

# 开始吧

根据题意，我们要找的东西有三个，分别是GPS1的最短路，GPS2的最短路和报警次数的最短路

## GPS最短路

这个东西相当于多起点同终点的最短路

这种类型的题目一般把边取反，变成反图来求解

比如这道：[$\huge\texttt{P1821-牛的派对}$](https://www.luogu.com.cn/problem/P1821)

### 具体代码如下：

```cpp
inline void add1(int u,int v,int w,int id)
{
    e1[++k1[0]][0].u=u;
	e1[++k1[1]][1].v=u;
    e1[k1[1]][1].u=v;
	e1[k1[0]][0].v=v;
    e1[k1[0]][0].w=e1[k1[1]][1].w=w;
    e1[k1[0]][0].next=head1[u][0];
    e1[k1[1]][1].next=head1[v][1];
    e1[k1[0]][0].id=e1[k1[1]][1].id=id;
    head1[u][0]=k1[0];
	head1[v][1]=k1[1];
}

queue <int> q;

void spfa1(void)
{
    for(register int i=1;i<=n;++i)
        dis1[i]=0x3f3f3f3f3f3f3f3f;
    dis1[n]=0;
    vis1[n]=true;
    q.push(n);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=head1[u][1];i;i=e1[i][1].next)
        {
            int v=e1[i][1].v;
            if(dis1[v]>dis1[u]+e1[i][1].w)
            {
            	from1[v]=e1[i][1].id;
                dis1[v]=dis1[u]+e1[i][1].w;
                if(!vis1[v])
                {
                    vis1[v]=true;
                    q.push(v);
                }
            }
        }
        vis1[u]=false;
    }
}
```

## 报警次数最短路

有两种处理方法

1. 对于跑出的GPS最短路进行重新建图，并跑最短路

2. 打下最短路标记，然后直接跑最短路，进行比对

为了简便，这里我采取方法二。

![](https://cdn.luogu.com.cn/upload/image_hosting/f8sm6tq6.png)

# 进阶

当你按照这样来打下一份代码，恭喜你，进入了调试阶段

因为这份代码　根　本　拿　不　满　分

冥思苦想啊……

## 标记优化

后来跑去隔壁重题交了一发……搞到了一个点的数据，长下面这样

```
10000 20000
1 2 1 100000
2 1 100000 1
2 3 1 100000
3 2 100000 1
3 4 1 100000
4 3 100000 1
4 5 1 100000
5 4 100000 1
5 6 1 100000
6 5 100000 1
6 7 1 100000
7 6 100000 1
7 8 1 100000
8 7 100000 1
8 9 1 100000
9 8 100000 1
9 10 1 100000
10 9 100000 1

...
```

豁然开朗啊。这数据卡掉了使用距离相减的路径标记

于是乎打出了下面这样

![](https://cdn.luogu.com.cn/upload/image_hosting/jzxyg6tx.png)

## 优化 2.0

然而上面那份也wa了，不过至少这次能拿60分

于是又跑去隔壁找灵感，一瞅题干明白了，**有重边！**

什么意思呢？就是说你这两个spfa跑出来的都是$u\rightarrow v$，但是走的是不同的边！

又优化……

![](https://cdn.luogu.com.cn/upload/image_hosting/q18vb545.png)

这次A了！

# 总结

这道题综合性挺强的，最短路好几个细节处理都考到了，适合下午debug
~~(笑)~~

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN=100010;
const int MAXM=500010;

int n,m;
int k1[2],k2[2];
int head1[MAXN][2],head2[MAXN][2];
int dis1[MAXN],dis2[MAXN],vis1[MAXN],vis2[MAXN],from1[MAXN],from2[MAXN];

struct edge{
    int u,v,w,next,id;
}e1[MAXM*2][2],e2[MAXM*2][2];

inline int read(void)
{
    int ans=0;
    char a=getchar();
    while(!isdigit(a))
        a=getchar();
    while(isdigit(a))
    {
        ans=ans*10+a-'0';
        a=getchar();
    }
    return ans;
}

inline void add1(int u,int v,int w,int id)
{
    e1[++k1[0]][0].u=u;
	e1[++k1[1]][1].v=u;
    e1[k1[1]][1].u=v;
	e1[k1[0]][0].v=v;
    e1[k1[0]][0].w=e1[k1[1]][1].w=w;
    e1[k1[0]][0].next=head1[u][0];
    e1[k1[1]][1].next=head1[v][1];
    e1[k1[0]][0].id=e1[k1[1]][1].id=id;
    head1[u][0]=k1[0];
	head1[v][1]=k1[1];
}

inline void add2(int u,int v,int w,int id)
{
    e2[++k2[0]][0].u=u;
	e2[++k2[1]][1].v=u;
    e2[k2[1]][1].u=v;
	e2[k2[0]][0].v=v;
    e2[k2[0]][0].w=e2[k2[1]][1].w=w;
    e2[k2[0]][0].next=head2[u][0];
    e2[k2[1]][1].next=head2[v][1];
    e2[k2[0]][0].id=e2[k2[1]][1].id=id;
    head2[u][0]=k2[0];head2[v][1]=k2[1];
}

queue <int> q;

void spfa1(void)
{
    for(register int i=1;i<=n;++i)
        dis1[i]=0x3f3f3f3f3f3f3f3f;
    dis1[n]=0;
    vis1[n]=true;
    q.push(n);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=head1[u][1];i;i=e1[i][1].next)
        {
            int v=e1[i][1].v;
            if(dis1[v]>dis1[u]+e1[i][1].w)
            {
            	from1[v]=e1[i][1].id;
                dis1[v]=dis1[u]+e1[i][1].w;
                if(!vis1[v])
                {
                    vis1[v]=true;
                    q.push(v);
                }
            }
        }
        vis1[u]=false;
    }
}

void spfa2(void)
{
    for(register int i=1;i<=n;++i)
        dis2[i]=0x3f3f3f3f3f3f3f3f;
    dis2[n]=0;
    vis2[n]=true;
    q.push(n);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=head2[u][1];i;i=e2[i][1].next)
        {
            int v=e2[i][1].v;
            if(dis2[v]>dis2[u]+e2[i][1].w)
            {
            	from2[v]=e2[i][1].id;
                dis2[v]=dis2[u]+e2[i][1].w;
                if(!vis2[v])
                {
                    vis2[v]=true;
                    q.push(v);
                }
            }
        }
        vis2[u]=false;
    }
}

int dis[MAXN],vis[MAXN];

void spfa(void)
{
    for(int i=1;i<=n;++i)
        dis[i]=0x3f3f3f3f3f3f3f3f;
    dis[1]=0;
    vis[1]=1;
    q.push(1);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=head1[u][0];i;i=e1[i][0].next)
        {
            int v=e1[i][0].v,temp_a=1,temp_b=1;
            if(from1[u]==e1[i][0].id)
                temp_a=0;
            if(from2[u]==e1[i][0].id)
                temp_b=0;
            if(dis[v]>(dis[u]+temp_a+temp_b))
            {
                dis[v]=dis[u]+temp_a+temp_b;
                if(!vis[v])
                {
                    vis[v]=true;
                    q.push(v);
                }
            }
        }
        vis[u]=false;
    }
}

signed main(void)
{
	//freopen("C:\\Users\\HP\\Desktop\\debug.txt","r",stdin);
    n=read();m=read();
    for(register int i=1;i<=m;++i)
    {
        int u=read();int v=read();int p=read();int q=read();
        add1(u,v,p,i);
        add2(u,v,q,i);
    }
    spfa1();
    spfa2();
    spfa();
    printf("%lld",dis[n]);
    return 0;
}

```

---

## 作者：muse_umbra (赞：0)

可能是我太弱了，一口气写了三个spfa(大雾)。  
前两个分别求的是两个导航所建议的最短路  
最后一个了就是求最少抱怨的路径  
我本来存的是一个点是由哪个点跑来的(60分)，但一想到最短路可能不止一条，我就觉得我太蒻了  
dis[u]!=dis[v]+val(u,v)  这条路径的抱怨值就加1  
为什么是不等于 ~~因为我懒，逃~~  
还有，因为要保证一条边绝对在1到n的最短路上，我们可以反向建边  
这样可以求出n到其他点的最短路  
也就是其他点到n的最短路  
具体还是看代码吧，不过我觉得建个新图真的没必要~~因为我懒~~  
讲真，spfa双端队列优化真好用  
以下代码
```cpp
#include<bits/stdc++.h>
#define M 500005
#define ll long long
#define INF 0x3f
using namespace std;
inline int read()
{
	int w=0,q=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')q=-1;c=getchar();}
	while(c>='0'&&c<='9'){w=(w<<1)+(w<<3)+c-'0';c=getchar();}
	return w*q;
}
int h[M],cnt,h1[100005],h2[100005],vis[100005],n,m;
ll dis1[100005],dis2[100005],dis3[100005];
struct node{int nxt,to;ll p,q;}c[M];
inline void add(int u,int v,int w1,int w2)
{
	c[++cnt].nxt=h[u];
	c[cnt].to=v;
	c[cnt].p=w1;
	c[cnt].q=w2;
	h[u]=cnt;
}
void spfa1()
{
	memset(vis,0,sizeof(vis));
	memset(dis1,0x3f,sizeof(dis1));
	deque<int> q;
	q.push_back(n);
	dis1[n]=0;
	vis[n]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop_front();
		vis[u]=0;
		for(int i=h[u];i;i=c[i].nxt)
		{
			int v=c[i].to;ll val=c[i].p;
			if(dis1[v]>dis1[u]+val)
			{
				h1[v]=u;
				dis1[v]=dis1[u]+val;
				if(!vis[v])
				{
					if(q.size()&&dis1[v]>dis1[q.front()])q.push_back(v);
					else q.push_front(v);
					vis[v]=1;
				}
			}
		}
	}
}
void spfa2()
{
	memset(vis,0,sizeof(vis));
	memset(dis2,0x3f,sizeof(dis2));
	deque<int> q;
	q.push_back(n);
	dis2[n]=0;
	vis[n]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop_front();
		vis[u]=0;
		for(int i=h[u];i;i=c[i].nxt)
		{
			int v=c[i].to;ll val=c[i].q;
			if(dis2[v]>dis2[u]+val)
			{
				h2[v]=u;
				dis2[v]=dis2[u]+val;
				if(!vis[v])
				{
					if(q.size()&&dis2[v]>dis2[q.front()])q.push_back(v);
					else q.push_front(v);
					vis[v]=1;
				}
			}
		}
	}
}
void spfa3()
{
	memset(vis,0,sizeof(vis));
	memset(dis3,0x3f,sizeof(dis3));
	deque<int> q;
	q.push_back(n);
	dis3[n]=0;
	vis[n]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop_front();
		vis[u]=0;
		for(int i=h[u];i;i=c[i].nxt)
		{
			int v=c[i].to;ll val=0;
			if(dis1[u]+c[i].p!=dis1[v])val++;
			if(dis2[u]+c[i].q!=dis2[v])val++;
			if(dis3[v]>dis3[u]+val)
			{
				dis3[v]=dis3[u]+val;
				if(!vis[v])
				{
					if(q.size()&&dis3[v]>dis3[q.front()])q.push_back(v);
					else q.push_front(v);
					vis[v]=1;
				}
			}
		}
	}
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=m;i++){int u=read(),v=read(),w1=read(),w2=read();add(v,u,w1,w2);}//建图
	spfa1();
	spfa2();
	spfa3();
	printf("%lld",dis3[1]);
	return 0;
}
```

---

