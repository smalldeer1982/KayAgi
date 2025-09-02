# [USACO11JAN] Traffic Lights S

## 题目描述

和FJ靠的最近的城市Kenosha市有 $M$条道路。(编号为$1-M$) 连接着$N$个路口 (编号为$1-N$) 。保证没有重边和自环。 

从点$i$到点$j$需要的时间是$T_{ij}$， 且保证$T_{ij}$ = $T_{ji}$

每个路口有一个交通灯，有两种颜色：蓝色和紫色。两个颜色周期性的交替。蓝色持续一定时间，然后紫色持续一定时间。
想要从$i$到$j$只有在$i$和$j$的信号灯颜色相同的时候才可以走(从T1离开i走向j，只需T1时刻i与j的颜色相同即可，无其他任何约束。)

如果在变幻灯的那一秒到$j$，考虑的是变幻后的颜色。
给你所有第$i$个路口的蓝色灯持续时间$DB_i$和紫色灯持续时间$DP_i$
和每个路口刚开始灯的颜色$C_i$,剩余持续时间$R_i$
求一个给定的原点$S$到给定目标点$D$的最小时间。

## 样例 #1

### 输入

```
1 4 
4 5 
B 2 16 99 
P 6 32 13 
P 2 87 4 
P 38 96 49 
1 2 4 
1 3 40 
2 3 75 
2 4 76 
3 4 77 
```

### 输出

```
127 
```

# 题解

## 作者：WerChange (赞：6)

题意很清晰，直接跑 SPFA 求最短路。

只是我们在松弛操作时，需要注意从 $u$ 是否可以到达 $v$。

怎么判断呢？

请移步下面三个部分。

## Part 1
先解释一下，下面点 $i$ 的信息分别为以下变量：
+ `color` 表示颜色， `1` 表示蓝色，`0` 表示紫色
+ `num` 表示初始状态持续时间
+ `t1` 表示蓝色状态持续时间
+ `t2` 表示紫色状态持续时间

我们写一个函数 `getcolor(int i,int tim)`，表示点 $i$ 在 $tim$ 时刻的下一个颜色状态是什么。

分一下情况：
1. $tim<num[i]$，直接返回 `color[i]^1`。
2. $tim\geq num[i]$
    + $color[i]$ 为紫色
        - $(tim-num[i])\mod \ (t1[i]+t2[i])<t1[i]$，返回 `color[i]`。
        - $(tim-num[i])\mod \ (t1[i]+t2[i])\geq t1[i]$，返回 `color[i]^1`。
    + $color[i]$ 为蓝色
        - $(tim-num[i])\mod \ (t1[i]+t2[i])<t2[i]$，返回 `color[i]`。
        - $(tim-num[i])\mod \ (t1[i]+t2[i])\geq t2[i]$，返回 `color[i]^1`。

code
```cpp
bool getcolor(int i,int tim)
{
    bool color=a[i].color^1;
    if(tim<a[i].num)
        return color;
    tim-=a[i].num;
    tim%=(a[i].t1+a[i].t2);
    if(a[i].color==0)
    {
        if(tim<a[i].t1)
            return color^1;
        return color;
    }
    else
    {
        if(tim<a[i].t2)
            return color^1;
        return color;
    }
}
```
## Part 2
得到一个函数，仅仅只能求第 $tim$ 时刻的下一个颜色状态是远远不够的。

我们还需要与这个函数类似功能的函数 `gettim(int i,int tim)`。

意义为：
> 得到一个值，这个值表示点 $i$ 在 $tim$ 时刻变成下一个状态还需要多少时间。

与上一 Part 类似的，可以分讨一下：
1. $tim<num[i]$，直接返回 `num[i]-tim`。
2. $tim\geq num[i]$
    + $color[i]$ 为紫色
        - $(tim-num[i])\mod \ (t1[i]+t2[i])<t1[i]$，返回 `t1[i]-tim`。
        - $(tim-num[i])\mod \ (t1[i]+t2[i])\geq t1[i]$，返回 `t1[i]+t2[i]-tim`。
    + $color[i]$ 为蓝色
        - $(tim-num[i])\mod \ (t1[i]+t2[i])<t2[i]$，返回 `t2[i]-tim`。
        - $(tim-num[i])\mod \ (t1[i]+t2[i])\geq t2[i]$，返回 `t1[i]+t2[i]-tim`。

代码也很类似。

code
```cpp
int gettim(int i,int tim)
{
    if(tim<a[i].num)
        return a[i].num-tim;
    tim-=a[i].num;
    tim%=(a[i].t1+a[i].t2);
    if(a[i].color==0)
    {
        if(tim<a[i].t1)
            return a[i].t1-tim;
        return a[i].t1+a[i].t2-tim;
    }
    else
    {
        if(tim<a[i].t2)
            return a[i].t2-tim;
        return a[i].t1+a[i].t2-tim;
    }
}
```
## Part 3
得到了这两个函数，一切都变得简单多啦~

现在思考在松弛中面对 $u$ 和 $v$ 两个点时的情况。

先是用变量 `cu` 和 `cv` 分别表示 $u$ 的下一个颜色与 $v$ 的下一个颜色。
+ 如果 $cu=cv$，直接松弛。
+ 如果 $cu\neq cv$，多拿一个变量 `tmp` 负责接下来记录要等待多少时间才能从 $u$ 走到 $v$。

现在讨论 $cu\neq cv$ 的情况。

先分别得到 $u$ 和 $v$ 变成下一个状态所需要的时间 `tu` 和 `tv`。
+ 如果 $tu=tv$，则 `tmp=min(tu,tv)`。
+ 如果 $tu\neq tv$，说明接下来要看周期性的颜色变换是否可以让 $u$ 走到 $v$。

现在讨论周期性的颜色变换。

由于是周期性的，所以如果 $u$ 注定永远走不到 $v$，说明它们的周期总是交叉相等。

什么意思呢？举个例子。
```
u: B 6 10 70
v: P 6 70 10
```
上面这两个点，总是同时变换状态，所以永远不能到达。所以我们判断周期是否交叉相等就可以筛掉无法到达的情况。直接 `continue` 松弛下一个 $v'$。

那接下来就注定可以到达，直接分讨一下就可以得到 `tmp` 了。

`tmp` 一出，有手就行。只需要在松弛的判断中加上一个 `tmp` 就好了。

## 代码
code
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN=400+5,MAXM=14000+5,INF=1e18;

int s,t;
int n,m;
int su,hd[MAXN],vl[MAXM<<1],lt[MAXM<<1],en[MAXM<<1];
int dis[MAXN];
bool vis[MAXN];
struct node
{
    bool color;
    int num,t1,t2;
}a[MAXN];

void add(int u,int v,int w)
{
    en[++su]=v,vl[su]=w,lt[su]=hd[u],hd[u]=su;
}

bool getcolor(int i,int tim)
{
    bool color=a[i].color^1;
    if(tim<a[i].num)
        return color;
    tim-=a[i].num;
    tim%=(a[i].t1+a[i].t2);
    if(a[i].color==0)
    {
        if(tim<a[i].t1)
            return color^1;
        return color;
    }
    else
    {
        if(tim<a[i].t2)
            return color^1;
        return color;
    }
}

int gettim(int i,int tim)
{
    if(tim<a[i].num)
        return a[i].num-tim;
    tim-=a[i].num;
    tim%=(a[i].t1+a[i].t2);
    if(a[i].color==0)
    {
        if(tim<a[i].t1)
            return a[i].t1-tim;
        return a[i].t1+a[i].t2-tim;
    }
    else
    {
        if(tim<a[i].t2)
            return a[i].t2-tim;
        return a[i].t1+a[i].t2-tim;
    }
}

void SPFA()
{
    for(int i=1;i<=n;i++) dis[i]=INF;
    queue<int> q;
    q.push(s);
    vis[s]=1,dis[s]=0;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int i=hd[u];i;i=lt[i])
        {
            int v=en[i];
            int tmp=0;
            bool cu=getcolor(u,dis[u]);
            bool cv=getcolor(v,dis[u]);
            if(cu^cv)
            {
                int tu=gettim(u,dis[u]);
                int tv=gettim(v,dis[u]); // simple turn once
                if(tu==tv) // hard turn more
                {
                    if(a[u].t2==a[v].t1&&a[u].t1==a[v].t2)
                        continue;
                    if(cu==0) // now u is purple
                    {
                        if(a[u].t2==a[v].t1)
                            tmp=a[u].t2+min(a[u].t1,a[v].t2);
                        else
                            tmp=min(a[u].t2,a[v].t1);
                    }
                    else // now u is blue
                    {
                        if(a[u].t1==a[v].t2)
                            tmp=a[u].t1+min(a[u].t2,a[v].t1);
                        else
                            tmp=min(a[u].t1,a[v].t2);
                    }
                    tmp+=tu;
                }
                else
                    tmp=min(tu,tv);
            }
            if(dis[v]>dis[u]+tmp+vl[i])
            {
                dis[v]=dis[u]+tmp+vl[i];
                if(!vis[v])
                    vis[v]=1,q.push(v);
            }
        }
        vis[u]=0;
    }
}

signed main()
{
    scanf("%lld%lld%lld%lld",&s,&t,&n,&m);
    for(int i=1,num,t1,t2;i<=n;i++)
    {
        char ch;
        scanf("%s%lld%lld%lld",&ch,&num,&t1,&t2);
        a[i]={(ch=='B'),num,t1,t2};
    }
    for(int i=1,u,v,w;i<=m;i++)
    {
        scanf("%lld%lld%lld",&u,&v,&w);
        add(u,v,w);
        add(v,u,w);
    }
    SPFA();
    if(dis[t]==INF)
        dis[t]=0;
    printf("%lld\n",dis[t]);
    return 0;
}
```

---

## 作者：Hope2075 (赞：2)

这题很坑

首先，没有比较好的中文题面

```
If a vehicle arrives at a junction just at the moment the lights switch it must consider the new colors of lights.
```
如果车恰好在灯改变颜色时到达一个节点，需要考虑改变后的颜色

其次，细节比较多

而且简单暴力可能会TLE

~~但实际上也许真能过~~

分析一下问题：

如果较早到达一个点，总比晚到达要好

所以记录最早到达某个点的时间

然后，更新只会使数值变小

和最短路很像


考虑边权是多少

首先，需要一段时间等待

然后需要经过边的时间

经过时间好算

主要是等待时间

考虑先按类似题目输入的格式求出当前状态

直接将当前时间对两个点的周期取模，分类讨论即可
```cpp
	int m1=(t[0][a]+t[1][a]);
	
	if(ti%m1<r[a]){
    	//如果在第一次切换前
		st1=col[a];
		r1=r[a]-ti%m1+m1;
	}else if(ti%m1>=(r[a]+t[!col[a]][a])){
    	//如果已经切换两次
		st1=col[a];
		r1=r[a]-ti%m1+m1;
	}else{
    	//如果只切换了一次
		st1=!col[a];
		r1=r[a]-ti%m1+t[!col[a]][a];
	}
	r1%=m1;
	if(r1<0)r1+=m1;
    //另一半类似
```
注意上面的一条要求
```cpp
	if(r1==0){
    	//如果赶上切换，就应该特判一下
		st1=!st1;
		r1=t[st1][a];
	}
```

然后讨论什么时候能通过

第一种：灯的颜色一样，则等待时间为0
```cpp
	if(st1==st2){
		return 0;
	}
```

第二种：灯的颜色不一样

如果接下来的第一次切换时间不同，则取较小值即可

```cpp
	else if(r1!=r2){
		return min(r1,r2);
	}
```
如果第一次一样，则看第二次

如果不一样，还是取较小值

```cpp
	else if(t[!st1][a]!=t[!st2][b]){
		return r1+min(t[!st1][a],t[!st2][b]);
	}
```
如果还是一样，就要看第三次了

这里需要注意，如果周期不同，则此时第三次一定能通过，否则一定不能通过
```cpp
	else if(m1!=m2){
        return r1+t[!st1][a]+min(t[st1][a],t[st2][b]);
    }else{
        return -1;
    }
```

但是边权会变化

不过考虑dijkstra的过程，只有距离已经被固定的点才能更新周围点，也就意味着边权是固定值

这道题的图是稠密图，邻接表和堆优化对效率影响不大

这里用邻接矩阵和朴素dijkstra

~~不怕死可以试试SPFA~~

完整代码
```cpp
#include<iostream>
using namespace std;
const int N=360,M=14400;
#define int long long
//这里也许没必要
//不过还是以防万一比较好
long long INF=0x3fffffffffffffffll;
int gr[N][N];
int dis[N];
bool used[N];
char col[N];
int t[2][N],r[N];
int s,e;
int n,m;

int getdelay(int a,int b,int ti){
	bool st1,st2;
	int r1,r2;
	int m1=(t[0][a]+t[1][a]),m2=(t[0][b]+t[1][b]);
	
	if(ti%m1<r[a]){
		st1=col[a];
		r1=r[a]-ti%m1+m1;
	}else if(ti%m1>=(r[a]+t[!col[a]][a])){
		st1=col[a];
		r1=r[a]-ti%m1+m1;
	}else{
		st1=!col[a];
		r1=r[a]-ti%m1+t[!col[a]][a];
	}
	r1%=m1;
	if(r1<0)r1+=m1;
	
	if(ti%m2<r[b]){
		st2=col[b];
		r2=r[b]-ti%m2;
	}else if(ti%m2>=(r[b]+t[!col[b]][b])){
		st2=col[b];
		r2=r[b]-ti%m2+m2;
	}else{
		st2=!col[b];
		r2=r[b]-ti%m2+t[!col[b]][b];
	}
	r2%=m2;
	if(r2<0)r2+=m2;
	
	if(r1==0){
		st1=!st1;
		r1=t[st1][a];
	}
	
	if(r2==0){
		st2=!st2;
		r2=t[st2][b];
	}
	
	
	if(st1==st2){
		return 0;
	}else if(r1!=r2){
		return min(r1,r2);
	}else if(t[!st1][a]!=t[!st2][b]){
		return r1+min(t[!st1][a],t[!st2][b]);
	}else if(m1!=m2){
		return r1+t[!st1][a]+min(t[st1][a],t[st2][b]);
	}else{
		return -1;
	}
}

int a,b,w;
#undef int
int main(){
#define int long long
	ios::sync_with_stdio(false);
	cin>>s>>e;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>col[i];
		if(col[i]=='B')col[i]=0;
        //直接把颜色变为0/1便于操作
		else col[i]=1;
		cin>>r[i]>>t[0][i]>>t[1][i];
		dis[i]=INF;
		for(int j=1;j<=n;j++)gr[i][j]=INF;
	}
	while(m--){
		cin>>a>>b>>w;
		gr[a][b]=gr[b][a]=min(gr[a][b],w);
	}
	dis[s]=0;
	for(int k=1;k<=n;k++){
		int id=0,mindis=INF,del;
		for(int i=1;i<=n;i++){
			if(!used[i]&&dis[i]<mindis){
				id=i;
				mindis=dis[i];
			}
		}
		if(id==0)break;
		used[id]=1;
		for(int i=1;i<=n;i++){
			if(used[i])continue;
			del=getdelay(id,i,mindis);
			if(del==-1)continue;
			dis[i]=min(dis[i],mindis+del+gr[id][i]);
		}
	}
	if(dis[e]==INF)cout<<"0";
    //注意这里是0而不是-1
	else cout<<dis[e];
}
```

其实这题难点就在于讨论等待时间

如果少一种情况就会WA

---

## 作者：Hog_Dawa_IOI (赞：1)

今天模拟赛的一道题，其他啥的都对，结果在数等待时间的时候脑残用了循环去求，一百分秒变六十七分（洛谷评测结果为六十三分）……       
好吧转入正题。        
### 题目大意    
一个无向图图上 $n$ 个点 $m$ 条边，从点 $i$ 到点 $j$ 需要 $t_{i,j}$ 的时间。       
然而过分的是这个图上每一个点都有一个类似红绿灯的“蓝紫灯”，给出**一开始这盏灯的初始颜色**、**距离下一次变换状态要等待的时间**、**灯变为蓝色的持续时间**和**灯变为紫色的持续时间**。      
当且仅当在时刻 $t$ 时，一条边两端的点的灯的颜色相同，我们可以从一端走到另一端。         
问最少要多久才能从给定起点走到给定终点。       
如果无法走到终点则输出零。     
数据范围：$2 \le N \le 300,1 \le M \le 14000,1 \le t_{i,j} \le 100,t_{i,j} = t_{j,i}$

### 思路分析
一眼得最短路，这里采用 Dijkstra 求最短路。（Dijkstra 永远的神！）  
这里用不用堆优化问题都不大，因为数据范围太小。我用的是朴素版。   
其实这道题最关键的是如何求出一个点到另一个点实际上要走多久。   
下面将结合代码进行讲解。     
这小段代码是准备工作，寻找目前离起点最近的且当前还没有被访问到的点。
```cpp
long long min=n+1;
for(int i=1;i<=n;i++) if((!flag[i])&&shortest[i]<shortest[min]) min=i;
flag[min]=1;
```
#### 一、求出当前两个点的各种状态。  
```cpp
long long dq1=0,shengyuer1=shengyu[min],dq2=0,shengyuer2=shengyu[bian[i].end];
bool color1=f[min],color2=f[bian[i].end];
while(dq1+shengyuer1<=shortest[min])
dq1+=shengyuer1,color1^=1,shengyuer1=(color1)?blue[min]:purple[min];
while(dq2+shengyuer2<=shortest[min])
dq2+=shengyuer2,color2^=1,shengyuer2=(color2)?blue[bian[i].end]:purple[bian[i].end];
shengyuer1-=(shortest[min]-dq1),dq1=shortest[min],
shengyuer2-=(shortest[min]-dq2),dq2=shortest[min];
```

`bian[i].end` 指 `min` 的邻接点，`dq1` 和 `dq2` 分别指计算的时候两个点所经过的时间， `shengyuer1` 和 `shengyuer2` 分别指两个点处于当前状态还剩下的时间。分别计算两个点到 `shortest[min]`（即我已经走到 `min` 这个点，等待走到 `bian[i].end` 时的时刻）时的状态，以及距离下一次状态变换的时间。    
最后，把两个点当前所处的时间点统一为 `shortest[min]`（指从起点到当前这个点最少需要的时间）的时刻，剩下的时间也相应更改。        
#### 二、计算等待两个点颜色相同还需要多长时间。 
```cpp
if(color1!=color2)
{
    if(shengyuer1<shengyuer2)
    dq+=shengyuer1,color1^=1,
    shengyuer1=(color1)?blue[min]:purple[min];
    else if(shengyuer1>shengyuer2)
    dq+=shengyuer2,color2^=1,
    shengyuer2=(color2)?blue[bian[i].end]:purple[bian[i].end];
    else
    {
        dq+=shengyuer1,color1^=1,shengyuer1=(color1)?blue[min]:purple[min],
        color2^=1,shengyuer2=(color2)?blue[bian[i].end]:purple[bian[i].end];
        if(shengyuer1<shengyuer2)
        dq+=shengyuer1,color1^=1,
        shengyuer1=(color1)?blue[min]:purple[min];
        else if(shengyuer1>shengyuer2)
        dq+=shengyuer2,color2^=1,
        shengyuer2=(color2)?blue[bian[i].end]:purple[bian[i].end];
        else
        {
            dq+=shengyuer1,color1^=1,shengyuer1=(color1)?blue[min]:purple[min],
            color2^=1,shengyuer2=(color2)?blue[bian[i].end]:purple[bian[i].end];
            if(shengyuer1<shengyuer2)
            dq+=shengyuer1,color1^=1,
            shengyuer1=(color1)?blue[min]:purple[min];
            else if(shengyuer1>shengyuer2)
            dq+=shengyuer2,color2^=1,
            shengyuer2=(color2)?blue[bian[i].end]:purple[bian[i].end];
            else dq=shortest[n+1];
        }
    }
}
```
如果两个点颜色不相同，那么就需要等待，等到两个点颜色相同为止。  
**先判断哪个点先改变状态**，即哪个点剩余的时间最少。如果两个点同时改变颜色，那么**再等待第二个回合**。如果再不行，**就等第三个回合**。但**如果最后依旧不行，那么就说明两个点就是单曲循环，它们颜色永远无法相同**。（这里用了 `shortest[n+1]`，即一个很大的大数来赋值。）      
为什么这么说？我是这样理解的：第一个回合，先把上次剩下的时间先耗掉。如果同时改变颜色， 就说明它们同时进入了一个新的回合，一蓝一紫或一紫一蓝。第二个回合结束后它们又同时进入了一个新回合，这回它们的状态又反了过来，并且我们可以得出它们**一对相对颜色的时间长度是相等的**。到第三个回合结束的时候，它们已经一起把紫色和蓝色都经历了一遍，如果还是同时改变状态，那么又可以推出**另一对相对颜色的时间长度是相等的**。这样一来，**这两个点就会反反复复的循环**，它们的颜色永远相同不了。永远不会！  
#### 三、更新 `shortest` 数组。
需要注意的是，这里的 `dq` 其实指的是从起点出发沿着一条我们不关心的路径走到 `min`，再等到 `min` 和 `bian[i].end` 相等所需要的时间。所以最后判断时我们直接这样写：      
```cpp
if(dq+bian[i].quan<shortest[bian[i].end])
shortest[bian[i].end]=dq+bian[i].quan;
```

最后的最后就是输出了，这里记得判断，如果 `shortest[t]` 未被更新还是最开始被赋值的那个数，则要输出零。      
代码长度 $2.93$ 千字节，就[给个链接](https://www.luogu.com.cn/record/122281457)，不放完整代码了。    
~~虽然我的代码长，但速度快，二零二三年八月二十二日交的代码，直到同年十月三日还是以 $44$ 毫秒的速度领先众多代码成为洛谷最优解。【小小的自豪！】~~

---

## 作者：creation_hy (赞：0)

码农题。

这数据范围明显 spfa。正确性证明很简单，一个点到达的时间如果很早暂时没办法往下走，可以在这里原地不动。

难点就是找出某个时刻后两个点第一次灯色相同是在什么时候。

前面这个第一次变换的时间贼恶心，直接暴力循环 $[cur,cur+100]$ 即可。

后面部分，能发生的前提是两边开始不同且第一次变换时间相同。先把 $cur$ 提到大于等于第一次变换时间。然后暴力枚举接下来三次变换是否不是同时进行，如果是返回答案，如果不是的话，已经陷入死循环，返回 $inf$。

建议自己写，我写的巨乱，前方地狱绘图（

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 305;
const int M = 3e4 + 5;
int n, m, s, t, head[N], to[M], nxt[M], val[M], etot;
ll dis[N];
bool vis[N];
struct node
{
    int st, rem, x, y;
} a[N];
inline void link(int u, int v, int w)
{
    to[etot] = v;
    val[etot] = w;
    nxt[etot] = head[u];
    head[u] = etot++;
}
inline ll getnow(ll cur, int x)
{
    ll res = a[x].st + (a[x].rem <= cur ? 1 + (cur - a[x].rem) / (a[x].x + a[x].y) * 2 : 0) & 1;
    ll rem = max(0ll, cur - a[x].rem) % (a[x].x + a[x].y), k = res ? a[x].y : a[x].x;
    return res + (rem >= k) & 1;
}
inline ll getnxt(ll cur, int x)
{
    ll res = a[x].st + (a[x].rem <= cur ? 1 + (cur - a[x].rem) / (a[x].x + a[x].y) * 2 : 0) & 1;
    ll rem = max(0ll, cur - a[x].rem) % (a[x].x + a[x].y), k = res ? a[x].y : a[x].x, nxt = res ? a[x].x : a[x].y;
    return rem >= k ? nxt - (rem - k) : k - rem;
}
inline ll getnnxt(ll cur, int x)
{
    ll res = a[x].st + (a[x].rem <= cur ? 1 + (cur - a[x].rem) / (a[x].x + a[x].y) * 2 : 0) & 1;
    ll rem = max(0ll, cur - a[x].rem) % (a[x].x + a[x].y), k = res ? a[x].y : a[x].x, nxt = res ? a[x].x : a[x].y;
    return rem >= k ? k : nxt;
}
inline ll getnnnxt(ll cur, int x)
{
    ll res = a[x].st + (a[x].rem <= cur ? 1 + (cur - a[x].rem) / (a[x].x + a[x].y) * 2 : 0) & 1;
    ll rem = max(0ll, cur - a[x].rem) % (a[x].x + a[x].y), k = res ? a[x].y : a[x].x, nxt = res ? a[x].x : a[x].y;
    return rem >= k ? nxt : k;
}
inline ll calc(ll cur, int x, int y)
{
    for (ll i = cur; i <= cur + 100; i++)
        if (getnow(i, x) == getnow(i, y))
            return i;
    cur = cur <= a[x].rem ? a[x].rem : cur;
    ll res = cur + min(getnxt(cur, x), getnxt(cur, y));
    if (getnxt(cur, x) != getnxt(cur, y))
        return res;
    res += min(getnnxt(cur, x), getnnxt(cur, y));
    if (getnnxt(cur, x) != getnnxt(cur, y))
        return res;
    res += min(getnnnxt(cur, x), getnnnxt(cur, y));
    if (getnnnxt(cur, x) != getnnnxt(cur, y))
        return res;
    return 1e10;
}
inline void spfa()
{
    queue<int> q;
    q.emplace(s);
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        vis[x] = false;
        for (int i = head[x]; ~i; i = nxt[i])
        {
            ll k = calc(dis[x], x, to[i]) + val[i];
            if (dis[to[i]] > k)
            {
                dis[to[i]] = k;
                if (!vis[to[i]])
                    q.emplace(to[i]), vis[to[i]] = true;
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(head, -1, sizeof(head));
    cin >> s >> t >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        char c;
        cin >> c >> a[i].rem >> a[i].x >> a[i].y;
        a[i].st = c == 'P';
    }
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w, link(u, v, w), link(v, u, w);
    spfa();
    cout << (dis[t] >= 1e10 ? 0 : dis[t]) << '\n';
    return 0;
}
```

---

## 作者：Epworth (赞：0)

### [BLOG]<https://epworth.cn>

一道数据范围很小的最短路问题，但是不能直接松弛了。

> 想要从$i$到$j$只有在$i$和$j$的信号灯颜色相同的时候才可以走

于是可以考虑将$SPFA$魔改一发+暴力等待每条边两端点同色水过。

在$SPFA$中，我们用队列来储存结构体$node$。

$node.id$表示点的编号，$node.d$表示所用的时间。

不妨设我们在第$now$个单位的时间到了点$x$，可以通过一条边花费$w$单位个时间到达点$y$:

若$now+w<dist[y]$则表示经过这条边可以在更早的时间到达$y$。

如果此时$x$和$y$处的信号灯是一个颜色，直接更新。

反之我们暴力地等待$1$个单位的时间，$inqueue$判断后看是否将$(node)${$x,now+1$}入队。

(这里可以计算需要多久同色，但数据范围太小了$QwQ$)(能水则水我真是太菜了)

【注意】

①如何判断第$now$个单位时间信号灯的颜色?

​	$c[i]$为初始颜色，$r[i]$为初始颜色剩余时间，$p_1[i]，p_2[i]$分别为两种颜色持续时间。

​	Ⅰ 如果$now<r[i]$ 一次都没变 返回$c[i]$

​	Ⅱ进行$n$轮变化后还剩下$xx=(now-r[x])\%(p1[x]+p2[x])$ 个单位的时间。

​		讨论初始颜色的另一颜色的周期与$xx$的大小确定当前颜色。

②如果在变幻灯的那一秒，考虑的是变幻后的颜色。(如果不注意会$WA$前两个点)

③如果$now$很大了就$continue$了，有可能两点的灯根本不可能同色。

   (这里有点玄学，具体多大有待考究$QwQ$，但是不考虑会在第$9$个点$TLE$)

考场上瞎搞的，肯定有许多可以优化的地方，大佬们轻喷$QAQ$

## 代码

```cpp
#include<bits/stdc++.h>
#define maxn 50005
using namespace std;
int s,e,n,m;
int c[maxn],r[maxn];
int p1[maxn],p2[maxn];
struct data{
    int to;
    int p;
    int nextt;
}line[maxn];
int tail;
int first[maxn];
void add(int x,int y,int w){
    tail++;
    line[tail].to=y;
    line[tail].p=w;
    line[tail].nextt=first[x];
    first[x]=tail;
}
int color(int now,int x){
    if(now<r[x]) return c[x];
    int xx=(now-r[x])%(p1[x]+p2[x]);
       if(c[x]==1){
            if(xx-p2[x]>=0) return 1;
            return 2;
       }
       else{
       		if(xx-p1[x]>=0) return 2;
       		return 1;
       }
}
struct node{
    int id,d;
};
int dist[maxn];
int inqueue[305][100005];
queue<node> q;
void SPFA(){
    memset(dist,0x3f,sizeof(dist));
    dist[s]=0;
    q.push((node){s,0});
    inqueue[s][0]=1;
    while(!q.empty()){
        node t=q.front();q.pop();
        int x=t.id;
        int now=t.d;
        inqueue[x][now]=0;
        if(now>100005) continue; 
        for(int i=first[x];i;i=line[i].nextt){
            int y=line[i].to;
            int w=line[i].p;
            if(now+w<dist[y]){
                node xx;
                if(color(now,x)==color(now,y)){
                    dist[y]=now+w;
                    xx.id=y;xx.d=dist[y];	
                }
                else xx.id=x,xx.d=now+1;
                if(!inqueue[xx.id][xx.d]){
                    q.push(xx);
                    inqueue[xx.id][xx.d]=1;
                }
            }
        }
    }
}
int main(){
    scanf("%d%d%d%d",&s,&e,&n,&m);
    int a,b,q;char xx;
    for(int i=1;i<=n;i++){
        cin>>xx;
        c[i]=(xx=='B')?1:2;
        scanf("%d%d%d",&r[i],&p1[i],&p2[i]);
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&a,&b,&q);
        add(a,b,q);add(b,a,q);
    }
    SPFA();
    if(dist[e]>200000000) puts("0");
    else printf("%d\n",dist[e]);
    return 0;
}

```



---

