# [USACO3.2] 香甜的黄油 Sweet Butter

## 题目描述

Farmer John 发现了做出全威斯康辛州最甜的黄油的方法：糖。

把糖放在一片牧场上，他知道 $N$ 只奶牛会过来舔它，这样就能做出能卖好价钱的超甜黄油。当然，他将付出额外的费用在奶牛上。

Farmer John 很狡猾。像以前的 Pavlov，他知道他可以训练这些奶牛，让它们在听到铃声时去一个特定的牧场。他打算将糖放在那里然后下午发出铃声，以至他可以在晚上挤奶。

Farmer John 知道每只奶牛都在各自喜欢的牧场（一个牧场不一定只有一头牛）。给出各头牛在的牧场和牧场间的路线，找出使所有牛到达的路程和最短的牧场（他将把糖放在那）。

## 说明/提示

**数据范围**

对于所有数据，$1 \le N \le 500$，$2 \le P \le 800$，$1 \le A,B \le P$，$1 \le C \le 1450$，$1 \le D \le 255$。

---

**样例解释**

作图如下：

```cpp
          P2  
P1 @--1--@ C1
         |
         | 
       5  7  3
         |   
         |     C3
       C2 @--5--@
          P3    P4
```

把糖放在4号牧场最优。

## 样例 #1

### 输入

```
3 4 5
2
3
4
1 2 1
1 3 5
2 3 7
2 4 3
3 4 5```

### 输出

```
8```

# 题解

## 作者：Obito (赞：201)

#### 已经有dalao用SPFA做出来拉，不过讲的有点不详细在此细讲一下。


这道题一瞅就知道应该是一个最短路

## 再讲SPFA之前提供一个70分做法

# 裸的djkstra

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=3000+10;
int g[maxn],n,m,d[maxn][maxn],to[maxn],cnt,first[maxn],p1,p[maxn],next[maxn],piao[maxn];
int w[maxn],dis[maxn];
/*void add(int u,int v,int l){
    ++cnt;
    to[cnt]=v;	
    next[cnt]=first[u];
    first[u]=cnt;	
    w[cnt]=l;
}*/
void dijkstra(int s){
    for(int i=1;i<=n;i++)dis[i]=10000;
    memset(piao,0,sizeof(piao));
    int u;
    int minn;
    for(int i=1;i<=n;i++)
        dis[i]=d[s][i];
    piao[s]=1;
    dis[s]=0;
    for(int i=2;i<=n;i++){
        minn=2147483647-1;
    for(int j=1;j<=n;j++)
        if(piao[j]==0&&dis[j]<minn)
            minn=dis[j],u=j;
    piao[u]=1;
    for(int j=1;j<=n;j++)
        if(dis[j]>dis[u]+d[u][j]&&!piao[j])
            dis[j]=dis[u]+d[u][j];
    		}
    	}
    
int main(){
    cin>>p1>>n>>m;
    memset(d,0x3f3f,sizeof(d));
    for(int i=1;i<=p1;i++)
    scanf("%d",&g[i]);
    for(int i=1;i<=m;i++){
        int x,y,z;
        cin>>x>>y>>z;
        d[x][y]=d[y][x]=z;
    }
    int minn=100000000;
    for(int i=1;i<=n;i++){
        dijkstra(i);
        int ans=0;
        for(int j=1;j<=p1;j++)
        ans+=dis[g[j]];
        minn=min(minn,ans);
    //	cout<<ans<<endl;
    }
    cout<<minn<<endl;
    return 0;
    }

```

## 很显然会T掉

### 不过有人问了为什么不直接写SPFA

## because SPFA 他死了，在非特殊情况下（有负权）建议用dijkstra，比如[归程](https://www.luogu.org/problemnew/show/P4768)，用SPFA会被卡到60分的


# 接下来总算到了介绍SPFA了

### 段凡丁论文中的复杂度证明 (O(kE)（这么好的时间复杂度？），k 是小常数)是错误的，在此略去。该算法的最坏复杂度为 O(VE)（都退化成Bellman—Ford了）

### SPFA是在 Bellman-Ford 算法上的队列优化，所以学习前先看一下Bellman-Ford。

```
1,.初始化:将除源点外的所有顶点的最短距离估计值 d[v] -->+∞, d[s]-->0;

2.迭代求解:反复对边集E中的每条边进行松弛操作，使得顶点集V中的每个顶点v的最短距离估计值逐步逼近其最短距离;(运行|v|-1次)

3.检验负权回路:判断边集E中的每一条边的两个端点是否收敛。如果存在未收敛的顶点，则算法返回false，表明问题无解;否则算法返回true，并且从源点可达的顶点v的最短距离保存在 d[v]中。

```
## 摘自百度。

## 我们注意一下迭代求解的部分，我们发现Bellman-Ford是将每一条边进行了relax操作，这样就会出现很多毫无意义的操作，所以能不能优化一下呢？

### 实际上我们松弛是只要松弛 当前点的最短路径估计值对离开当前点所指向的结点进行松弛操作，就行了。这当中就需要用队列来存储所指的点就行了，所以主要代码就出来了


```cpp
for(int i=first[u];i;i=next[i]){//因为SPFA是以边为对象所以可以采用邻接表来存储
            int v=to[i];
            if(d[v]>d[u]+w[i]){
                d[v]=d[u]+w[i];
             //   cout<<v<<" "<<d[v]<<endl;
                if(!p[v]){
                    q.push(v);
                    p[v]=1;
                }			
            }	

```

## 再附上邻接表代码

```cpp
void add(int u,int v,int l){
    ++cnt;
    to[cnt]=v;	
    next[cnt]=first[u];
    first[u]=cnt;	
    w[cnt]=l;
}
```
## 把这些给想明白了，代码就很简单了。附上代码

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=30000+10;
int g[maxn],n,m,d[maxn],to[maxn],cnt,first[maxn],p1,p[maxn],next[maxn];
int w[maxn],dis[maxn];
queue<int>q;
void add(int u,int v,int l){
    ++cnt;
    to[cnt]=v;	
    next[cnt]=first[u];
    first[u]=cnt;	
    w[cnt]=l;
}
void spfa(int s){
    memset(p,0,sizeof(p));
    for(int i=1;i<=n;i++)d[i]=10000;
    d[s]=0;	q.push(s);p[s]=1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        p[u]=0;
        for(int i=first[u];i;i=next[i]){
            int v=to[i];
            if(d[v]>d[u]+w[i]){
                d[v]=d[u]+w[i];
             //   cout<<v<<" "<<d[v]<<endl;
                if(!p[v]){
                    q.push(v);
                    p[v]=1;
                }			
            }	
        }
    }
    }
int main(){
    cin>>p1>>n>>m;
    for(int i=1;i<=p1;i++)
    scanf("%d",&g[i]);
    for(int i=1;i<=m;i++){
        int x,y,z;
        cin>>x>>y>>z;
        add(x,y,z);
        add(y,x,z);
    }
    int minn=100000000;
    for(int i=1;i<=n;i++){//和SPFA模板不一样的就是需要对每个点进行SPFA
        spfa(i);
        int ans=0;
        for(int j=1;j<=p1;j++)
        ans+=d[g[j]];
        minn=min(minn,ans);
    //	cout<<ans<<endl;
    }
    cout<<minn<<endl;
    return 0;//完结散花
    }

```

### 最后在提一句，SPFA之所以可以判负环，是因为是以边为对象。所以判负环时。只要看一下一个点还能不能再进行松弛操作。这样就可以判断负环了，具体代码就不放出来了自己想一想


## 谢谢管理员大大审核此篇题解，如有不足请指正。

可以点个赞吗？








---

## 作者：shadowice1984 (赞：87)

floyd优化~~~

楼下大佬说floyd会超时，果真如此；

然而勒，路径都是双向边！

所以从i到j的距离等于j到i的距离~；

然后，就砍了一半的枝。

就过了········

************************************

方便萌新，写一下floyd的原理。

从i到j有两种途径，直接从i到j（路径不存在耗时即为无穷）

或者从i到k再从k到i。

然后选较短的就行了。

ps：邻接矩阵存图。

上代码~

            
```cpp
#include<stdio.h>
using namespace std;
int n;int p;int c;
int map[800][805];
int d[805][805];
int mark[805];
const int inf=9999999;
int res=inf;
int main()
{
    scanf("%d%d%d",&n,&p,&c);
    for(int i=0;i<p;i++)//手动memset
    {
        for(int j=0;j<p;j++)
        {
            if(i==j)
            {
                map[i][j]=0;//到自己的距离为0
                d[i][j]=0;
            }
            else
            {
                map[i][j]=inf;
                d[i][j]=inf;
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        int t;
        scanf("%d",&t);
        mark[t-1]++;//从零开始的数组
    }
    for(int i=0;i<c;i++)
    {
        int u;int v;int val;
        scanf("%d%d%d",&u,&v,&val);
        map[u-1][v-1]=val;//从零开始的数组
        map[v-1][u-1]=val;
        d[u-1][v-1]=val;//初始化d为邻接矩阵
        d[v-1][u-1]=val;
    }
    for(int k=0;k<p;k++)//floyd三重循环
    {
        for(int i=0;i<p;i++)
        {
            for(int j=0;j<i;j++)//灵魂剪枝，双向边算一半图就好了
            {
                if(d[i][j]>d[i][k]+d[k][j])
                {
                    d[i][j]=d[i][k]+d[k][j];
                    d[j][i]=d[i][j];//更新另一半
                }
            }
        }
    }
    for(int i=0;i<p;i++)//扫一遍，寻找最短路径和
    {
        int sum=0;
        for(int j=0;j<p;j++)
        {
            sum+=d[i][j]*mark[j];//因为是路径和，所以用mark数组保存奶牛头数
        }
        if(res>sum)res=sum;
    }
    printf("%d",res);
    return 0;//拜拜程序~
}

```

---

## 作者：Sshenyyyu (赞：39)

# 香甜的黄油
本题呢，肯定是要求最短路的，本蒟蒻用的是spfa，虽然楼上DaLao说floyd竟然可以过，但我还是发一个spfa的吧！！
本蒟蒻显示枚举所有牧场，跑一遍spfa这样每个点到这个牧场的最短路就知道了，再累加起来，取最小值就可以了。
贴代码。。。
```
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
#include <iostream>
using namespace std;

const int Maxn=1500;
const int inf=214748364;

int p,n,m,pp[Maxn*Maxn],a,b,c,Ans=inf;
int head[Maxn*2],to[Maxn*2],nextt[Maxn*2],w[Maxn*2],cnt,dist[Maxn*2];
bool inq[Maxn*2];

queue<int> q;

void addedge(int u,int v,int cost)//加边不多说了
{
	++cnt;
	nextt[cnt]=head[u];
	head[u]=cnt;
	to[cnt]=v;
	w[cnt]=cost;
}	

void spfa(int s)//spfa标准模板，不多说了
{
	memset(inq,false,sizeof(inq));
	for(int i=1; i<=n; i++)
		dist[i]=inf;
	dist[s]=0;	
	q.push(s);
	inq[s]=true;
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		inq[u]=false;
		for(int v=head[u]; v; v=nextt[v]) {
			if(dist[to[v]]>dist[u]+w[v]) {
				dist[to[v]]=dist[u]+w[v];
				if(inq[to[v]]==false) {
					inq[to[v]]=true;
					q.push(to[v]);		
				}
			}
		}
	}
}

int main()
{
	cin>>p>>n>>m;
	for(int i=1; i<=p; i++)
		cin>>pp[i];
	for(int i=1; i<=m; i++) {//加边不多说了
		cin>>a>>b>>c;
		addedge(a,b,c);
		addedge(b,a,c);
	}
	for(int i=1; i<=n; i++) {//枚举哪个牧场放糖果
		spfa(i);//调用spfa
		int sum=0;
		for(int j=1; j<=p; j++)//累计每个奶牛到那个牧场的所有最短路
			sum+=dist[pp[j]];//累加起来
		Ans=min(Ans,sum);//取最小值即可
	}	
	cout<<Ans<<endl;
	return 0;
}
```

---

## 作者：EarthGiao (赞：21)

# 潇洒の开始

第一步：食用头文件和定义变量，

变量干什么用的说的很清楚

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,p,c,i,j,x,y,t,min1,head,tail,tot,u;
int a[801][801],b[501],dis[801],num[801],w[801][801],team[1601];//team为队列，dis为距离，num为邻接点个数，a存相邻点
bool exist[801];//exist是存在的意思，确定某个元素是否存在
int main()
```

第二步：正常的输入

```cpp
	cin>>n>>p>>c;//奶牛数，牧场数，牧场间的道路数
	for(i=1; i<=p; i++)
	{
		b[i]=0;
		num[i]=0;
		for(j=1; j<=p; j++)
			w[i][j]=0x7fffffff/3;//第i到第j个牧场的路程初始化为无穷
	}
```
将两点之间的距离变为超大超大的数，酱紫好比较的啦

第三步：正常的输入加存储

```cpp
for(i=1; i<=n; i++)
		cin>>b[i];//输入奶牛所在的牧场号
	for(i=1; i<=c; i++) //邻接矩阵存储，采用循环队列能够降低队列大小，队列长度只需开到2*n+5即可。
	{
		cin>>x>>y>>t;//相连牧场AB和两牧场间的距离
		w[x][y]=t;//保存x到y间的距离
		a[x][++num[x]]=y;//存相邻点,在num原有的基础上加一，并将y点存入
		a[y][++num[y]]=x;//存相邻点,在num原有的基础上加一，并将x点存入
		w[y][x]=w[x][y];//因为是双向连通的，所以两牧场间的距离相等
	}
```
详细解释代码里面说的很清楚了，在啰嗦一下，双向的很重要

用地接斯科拉的哥们们注意了。

第四步：初始化minn

```cpp
min1=0x7fffffff/3;//初始化min
```

最后一步：~~gao chao 预警~~

```cpp
for(i=1; i<=p; i++)
	{
		for(j=1; j<=p; j++) dis[j]=0x7fffffff/3;
		//memset(team,0,sizeof(team));                         //队列数组初始化
		//memset(exist,false,sizeof(exist));                   //exist标志初始化
		dis[i]=0;
		team[1]=i;
		head=0;
		tail=1;
		exist[i]=true;      //起始点入队
		while(head!=tail)
		{
			head++;
			head=((head-1)%1601)+1;                           //循环队列处理
			u=team[head];
			exist[u]=false;
			for(j=1; j<=num[u]; j++) //num数组储存的为当前点所相邻的点的个数
				if (dis[a[u][j]]>dis[u]+w[u][a[u][j]])
				{
					dis[a[u][j]]=dis[u]+w[u][a[u][j]];
					if (!exist[a[u][j]])//如果该点没有被拿出，就进行处理
					{
						tail++;
						tail=((tail-1)%1601)+1;
						team[tail]=a[u][j];
						exist[a[u][j]]=true;//拿出该数
					}
				}
			}
		tot=0;
		for(j=1; j<=n; j++)
			tot+=dis[b[j]];//累加路程并计算
		if (tot<min1) min1=tot;//找最小
	}
	cout<<min1;
	return 0;
```

初始化我是去掉了，因为定义在int main()外面是不需要再次清零的

然后就是类似手打的队列，挨个比较找到小的就马上替换，重要的是没有被用过就处理

再就是挨个比较找最小值就好了

完整代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,p,c,i,j,x,y,t,min1,head,tail,tot,u;
int a[801][801],b[501],dis[801],num[801],w[801][801],team[1601];//team为队列，dis为距离，num为邻接点个数，a存相邻点
bool exist[801];//exist是存在的意思，确定某个元素是否存在
int main()
{
//    freopen("butter.in","r",stdin);
//    freopen("butter.out","w",stdout);
	cin>>n>>p>>c;//奶牛数，牧场数，牧场间的道路数
	for(i=1; i<=p; i++)
	{
		b[i]=0;
		num[i]=0;
		for(j=1; j<=p; j++)
			w[i][j]=0x7fffffff/3;//第i到第j个牧场的路程初始化为无穷
	}
	for(i=1; i<=n; i++)
		cin>>b[i];//输入奶牛所在的牧场号
	for(i=1; i<=c; i++) //邻接矩阵存储，采用循环队列能够降低队列大小，队列长度只需开到2*n+5即可。
	{
		cin>>x>>y>>t;//相连牧场AB和两牧场间的距离
		w[x][y]=t;//保存x到y间的距离
		a[x][++num[x]]=y;//存相邻点,在num原有的基础上加一，并将y点存入
		a[y][++num[y]]=x;//存相邻点,在num原有的基础上加一，并将x点存入
		w[y][x]=w[x][y];//因为是双向连通的，所以两牧场间的距离相等
	}
	min1=0x7fffffff/3;//初始化min
	for(i=1; i<=p; i++)
	{
		for(j=1; j<=p; j++) dis[j]=0x7fffffff/3;
		//memset(team,0,sizeof(team));                         //队列数组初始化
		//memset(exist,false,sizeof(exist));                   //exist标志初始化
		dis[i]=0;
		team[1]=i;
		head=0;
		tail=1;
		exist[i]=true;      //起始点入队
		while(head!=tail)
		{
			head++;
			head=((head-1)%1601)+1;                           //循环队列处理
			u=team[head];
			exist[u]=false;
			for(j=1; j<=num[u]; j++) //num数组储存的为当前点所相邻的点的个数
				if (dis[a[u][j]]>dis[u]+w[u][a[u][j]])
				{
					dis[a[u][j]]=dis[u]+w[u][a[u][j]];
					if (!exist[a[u][j]])//如果该点没有被拿出，就进行处理
					{
						tail++;
						tail=((tail-1)%1601)+1;
						team[tail]=a[u][j];
						exist[a[u][j]]=true;//拿出该数
					}
				}
			}
		tot=0;
		for(j=1; j<=n; j++)
			tot+=dis[b[j]];//累加路程并计算
		if (tot<min1) min1=tot;//找最小
	}
	cout<<min1;
	return 0;
}



```
# 完美の结束
（这是我之前做的题，现在才拿出来写题解忘得差不多了，写的不好请多多谅解QWQ）
（看的这么累，不点个赞再走）

---

## 作者：yangrunze (赞：17)

这个题是一道~~很简单~~的**图的最短路**的题目

图的最短路径有很多算法，但有些算法的时间复杂度有点高，**Dijkstra**如果不经优化，不光**不能处理负权边**（其实优化了也不行），时间复杂度还是 **$O(n^2)$**,**Floyd就更那啥了**，直接飙到了 **$O(n^3)$** ，面对这题如此大规模的数据，绝对妥妥地把你TLE哭，这也不行那也不行，那我们应该用什么方法呢？？？

>有的算法活着，它已经死了；有的算法死了，它还活着。

>							——臧克家

>		（臧克家：我没说过这句，不过确实有道理）

Well，这个题可以用~~号称已经“驾鹤西去”~~的**SPFA**，这是一个目前来说很“**高效**”的最短路算法，**最坏也只有$O(nm)$(n个顶点，M条边)的时间复杂度**，在大部分情况下可以切掉好多题，~~遇到特别毒瘤想卡SPFA的出题人除外~~

不会SPFA？点击下面的图片，了解一下

[![](https://cdn.luogu.com.cn/upload/pic/26431.png)](https://www.luogu.com.cn/problem/P3371)

那SPFA到底具体咋么实现呢？？？

1. 首先我们需要搞一个**队列**出来，把**源点入队**（SPFA和Dijkstra一样，也是**单源最短路径**）
2. get出**队首**，像Dijkstra一样把它连接的每一个顶点进行“**松弛**”操作（也就是**把这个点当成“中转点”，看看通过这个顶点能不能把路径变短** ， ~~不会Dijkstra？那你还来做这个题干啥哟？？？~~）
3. 能变短，**“松弛”成功后，更新源点到这个点的距离**，**如果这个点不再队列里，那就把它加进去**
4. 把所有顶点“松弛”一遍后，队首的“任务”就“完成”了，把**队首出队**，**如果队列空了就完事了，否则就执行刚才的操作**（也就是第2、3步）

像Dijkstra一样，我们需要一个**dis数组**来存**源点到每个点的距离**，以及一个**vis**数组来看看**每个顶点是否在队列中**

（话说你们有没有发现这个SPFA跟我们的广搜大法bfs很像呢~？）

接下来给大家来个好理解的**邻接矩阵**版的SPFA，大家来学习一下！
```cpp
//代码中，s为源点，e为图的邻接矩阵
int inf=1e9; //把inf弄成一个很大的数
for(int i=1;i<=n;i++) //初始化dis数组为inf
	dis[i]=inf;  
	dis[s]=0;  //自己到自己的距离当然就是0啦！
	q.push(s);  //队首入队，标记
	vis[s]=1;   
	while(!q.empty()){//队列不空一直操作
		int fro=q.front();  //取队首
		for(int i=1;i<=n;i++){  //连接的每个顶点进行操作
			if(e[fro][i]&&dis[fro]+e[fro][i]<dis[i]){  //如果有边，并且通过这条边路径还能变短，那就“松弛”成功
				dis[i]=dis[fro]+e[fro][i]; //dis数组更新
				if(!vis[i]){  //如果这个顶点不在队列中
					q.push(i);	//那就入队标记呗！
					vis[i]=1;
				}
			}
		}
		q.pop();   //队首出队，注意标记也要取消
		vis[fro]=0;
	}
```
当然这题肯定爆邻接矩阵，那图的存储也要改一下：这里我强烈推荐一个又好理解又好用的方法：**vector暴力存图！**（vector大家都会吧）

顾名思义，这个方法首先要**用一个结构体vector（为了节省空间，咱用vector来存）存储每个边的起点和终点**，然后**用一个二维vector（也就是一个vector数组）存储边的信息**。

这个存储方法可能有点难理解，不过其实也没那么难：**我们用$e$[$a$][$b$]=$c$，来表示顶点$a$的第$b$条边是$c$号边**。

```cpp
struct edge{
	int u,v,w; //记录边的结构体，u起点，v终点，w是边权值
};
vector <int> e[100001];  //存具体信息的二维vector
vector <edge> s;  //存边的结构体vector数组
——————我——是——分——割——线——————
//n个顶点，m条边，s为结构体vector，e为二维vector
	for(int i=0;i<m;i++){ //m条边
		int uu,vv,ww;  
		cin>>uu>>vv;  
		s.push_back((edge){uu,vv,ww}); //初始化存边的s数组  
	}
	for(int i=0;i<m;i++)
		e[s[i].u].push_back(i); 
	//初始化e数组，在e[s[i].u]（也就是i号边的起点s[i].u连接的边的数组）中存入i号边
```


如果你还是一脸懵圈，。请看[这里](https://www.luogu.com.cn/blog/ravenclawyangrunze/solution-p5318)，里面有对vector暴力存图法的详细解释，还有一道优秀的例题

当然，这个题是个**无向图**，所以要再修改一下下，每次要存**起点和终点正好相反两条边**，还要注意边的编号

会了这俩东西，我们就可以来研究这个题啦！懂了SPFA算法和vector暴力存图，后面的工作简直就是小问题了：直接**把每个顶点都给SPFA一遍求到各个牧场的最短距离**，再**把奶牛所在的牧场的距离加起来，比较，找个最小的**，就能完美AC了！

最后就是放代码的时间啦！**温馨提示：一定要注意细节！！！**

```cpp
#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
#define inf 2147483247   //我也来#define一发
using namespace std;   
struct edge{     //vector暴力存图用的准备工作
	int u,v,w;
};
vector <edge> s;   
vector <int> e[1455];
int n,p,c;     //题意：n奶牛数，p牧场数，c道路数
int cow[505],dis[805];   //dis是个啥就不解释了，cow是每个奶牛所在的牧场
bool vis[805];  //vis就是判断是否在队列中那个
void spfa(int k){  //因为后面要多次搞SPFA，所以我就直接把它弄成函数啦，k是源点哦！
	queue <int> q;  //后面就是SPFA的板子了
	for(int i=1;i<=p;i++)//dis数组初始化
	dis[i]=inf;
	dis[k]=0;
	q.push(k);
	vis[k]=1;
	while(!q.empty()){
		int fro=q.front()  //取队首;
		for(int i=0;i<e[fro].size();i++){
			int point=s[e[fro][i]].v;  //注意连接顶点和编的权值用vector暴力存图怎么表示
			int cost=s[e[fro][i]].w;
			if(dis[fro]+cost<dis[point]){//“松弛”操作
				dis[point]=dis[fro]+cost;//dis数组和队列的更新
				if(!vis[point]){  
					q.push(point);
					vis[point]=1;	
				}
			}
		}
		q.pop();   //队首出队，抹消标记
		vis[fro]=0;
	}
}
int main(){
	cin>>n>>p>>c;  
	for(int i=1;i<=n;i++)  //输入奶牛信息
	cin>>cow[i];
	for(int i=0;i<2*c-1;i+=2){  //vector暴力存图
		int uu,vv,ww;
		cin>>uu>>vv>>ww;
	    s.push_back((edge){uu,vv,ww}); 
	    s.push_back((edge){vv,uu,ww});//因为是无向图嘛，所以要寸两条边的，注意循环中i的控制
		e[uu].push_back(i); 
		e[vv].push_back(i+1); 
	}
	int ans=inf;  //ans因为要找最小值，所以要初始化个大的
	for(int i=1;i<=p;i++){  //每个牧场都来一波
		int wyxakioi=0;  //记录以牧场i为源点时的最短路径长（不要吐槽变量名）
		spfa(i);  //S~!~P~!~F~!~A!~
		for(int j=1;j<=n;j++)
			wyxakioi+=dis[cow[j]];  //统计每个奶牛到这个牧场的最短距离和
		if(ans>wyxakioi)ans=wyxakioi; //ans更新
	}
	cout<<ans;  
	return 0;  //完事啦！
}
```
 最后给大家一个温馨小tip：像咱们这些刚学SPFA（或者其他东西）的萌新，不要编完一遍，后面的题就一直复制粘贴，多打几遍，可以对这个算法或数据结构有更深的理解，相信我，没错的！

>   ##### 手打代码，是一种信仰。

>   #####  		 ——vectorwyx


---

## 作者：Refined_heart (赞：11)

在题解中看到有大佬说裸的$dijkstra$会$T$，于是本蒟蒻来补一个堆优化加前向星存边的$dijkstra$.

思路比较显然，对于每一个点都跑一遍最短路，累计距离和，求最小值。

实现细节：对于$dijkstra$我们可以传一个参数作为起点。堆可以用$STL$自带的优先队列。代码中会有重载运算符的$struct$ $node$结构体。

每次$dijkstra$的时候，初始化一下，传入起点，更新完$dis$数组后累计答案即可。不需要用邻接矩阵。

注意前向星开两倍空间，数组别少开。

实现过程与普通$dijkstra$类似，但是用堆维护$max/min$显然要更优。普通的$dijkstra$可能会$TLE$，堆优化还是有必要的。

$Code:$
```cpp
#include<cstdio>
#include<queue>//队列头文件 
#include<iostream>
#include<cstring>
#define inf 2147483647
using namespace std;
int vis[500000],n,m,p;
int dis[500000],tot,ans=inf;
int head[500000],sum;
int id[500000];
struct edge{
	int next,to,dis;
}e[1000000];
struct node{
	int dis,pos;
	bool operator <(const node&x)const{//重载运算符 
		return x.dis<dis;
	}
};
priority_queue<node>q;
inline void add(int x,int y,int w){//加边 
	e[++tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
	e[tot].dis=w;
}
void dijkstra(int s){//堆优化dijkstra 
	for(int i=1;i<=p;++i)dis[i]=inf;
	memset(vis,0,sizeof(vis));
	dis[s]=0,q.push((node){0,s});
	while(!q.empty()){
		node tmp=q.top();
		q.pop();
		int x=tmp.pos;
		if(vis[x])continue;
		vis[x]=1;
		for(int i=head[x];i;i=e[i].next){
			int y=e[i].to;
			if(dis[y]>dis[x]+e[i].dis){
				dis[y]=dis[x]+e[i].dis;
				if(!vis[y])q.push((node){dis[y],y});
			}
		}
	}
}
int main(){
	scanf("%d%d%d",&n,&p,&m);
	for(int i=1;i<=n;++i)scanf("%d",&id[i]);
	for(int i=1;i<=m;++i){
		int _,__,___;//皮一下很开心qwq 
		scanf("%d%d%d",&_,&__,&___);
		add(_,__,___);add(__,_,___); 
	}
	for(int i=1;i<=p;++i){
		dijkstra(i);
		sum=0;
		for(int j=1;j<=n;++j)sum+=dis[id[j]];
		ans=min(ans,sum);
	}printf("%d\n",ans);
	return 0;
} 
```


---

## 作者：BeyondStars (赞：9)

我只是一名被坑了的蒟蒻，本篇题解只是为了提醒和我一样的蒟蒻OIer们我上过的当，进过的坑

首先，我采用的是SPFA算法，速度超快有没有，但是，有坑，储存图我才用的是链式前向星，但是读入的时候就有坑了。附代码：

```cpp
    for(int i = 1;i<=C;i++){
        int A,B,D;
        cin>>A>>B>>D;
        add(A,B,D);
        add(B,A,D);
    }
```

在添加边的时候要注意这是一个**无向图**也是说添加的边必须是**双向的**A到B，那么B也一定连同A！


其次就是内存必须开2倍以上，我一开始开小了，导致只有60分，一个TLE，3个WA，第二次提交的时候，一个Wa变成了RE，说明内存有越界访问，第二次运气不好，访问到了系统关键内存。

还有一个坑就是关于奶牛走的路径和，不能在SPFA的循环里面算，否则当一个牧场的奶牛数为0的时候，这个和为0，那么更新到dis的时候，最小值就会变成0，与题意不符。应该算出最短路径，再乘以奶牛数量。附上AC代码


```cpp
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
struct e{
    int next,to,w;
}Edges[14510];
int a[8010];//牧场所拥有的奶牛数
int head[8001];
int num_cnt = 0;
void add(int from,int to,int w){
    Edges[++num_cnt].next = head[from];
    Edges[num_cnt].to = to;
    Edges[num_cnt].w = w;
    head[from] = num_cnt;
}
int main() {
    int N,P,C;
    ios::sync_with_stdio(false);
    cin>>N>>P>>C;
    for(int i = 1;i<=N;i++){
        int id;
        cin>>id;
        a[id]++;
    }
    for(int i = 1;i<=C;i++){
        int A,B,D;
        cin>>A>>B>>D;
        add(A,B,D);
        add(B,A,D);
    }
    int dis[8001];
    bool visited[8001];
    int minn = 0x7FFFFFF;
    for(int s = 1;s<=P;s++){
        memset(dis,0x7f, sizeof(dis));
        memset(visited,false, sizeof(visited));
        dis[s] = 0;
        visited[s] = true;
        queue<int> q;
        q.push(s);
        while(!q.empty()){
            int t = q.front();
            q.pop();
            visited[t] = false;
            for(int j = head[t];j!=0;j=Edges[j].next){
                int u = Edges[j].to;
                if(dis[u]>dis[t]+Edges[j].w){
                    dis[u]=dis[t]+Edges[j].w;
                    if(!visited[u]){
                        q.push(u);
                        visited[u] = true;
                    }
                }
            }
        }
        int sum = 0;
        for(int i = 1;i<=P;i++){
            sum+=dis[i]*a[i];
        }
        minn = minn>sum?sum:minn;
    }
    cout<<minn;
    return 0;
}

```

---

## 作者：Celebrate (赞：3)

我比较喜欢最优解，所以我用了SPFA来做

代码如下：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
struct node
{
	int x,y,d,next;//记录每一条边 
}a[5100];int len,last[210000];
inline void ins(int x,int y,int d)//建立一条边 
{
	len++;
	a[len].x=x;a[len].y=y;a[len].d=d;
	a[len].next=last[x];last[x]=len;
}
int n,p,m;
int f[210000];//f表示奶牛所在的点 
int head,tail,list[210000],d[210000];//宽搜时需要用到的，d表示这个点到起点的最小距离 
bool v[210000];//v表示这个点是否用过 
int main()
{
	int i,j,x,y,c,k;
	scanf("%d%d%d",&n,&p,&m);
	for(i=1;i<=n;i++) scanf("%d",&f[i]);//输入 
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&c);//输入并且建边 
		ins(x,y,c);ins(y,x,c);
	}
	int minn=2147483647,s;//把最小值变得无限大 
	for(i=1;i<=p;i++)//这里要注意了，是枚举所有的点，而不是单单奶牛所在的点 
	{
		memset(d,127,sizeof(d));d[i]=0;//自己到自己的距离肯定是0 
		memset(v,true,sizeof(v));v[i]=false;//自己不能再走到自己 
		head=1;tail=2;list[1]=i;
		while(head!=tail)
		{
			x=list[head];
			for(k=last[x];k;k=a[k].next)
			{
				y=a[k].y;
				if(d[y]>d[x]+a[k].d)//如果有更优值，就取更优值
				{
					d[y]=d[x]+a[k].d;
					if(v[y]==true)//如果这一个点还没有找过 
					{
						v[y]=false;//把它变为找过 
						list[tail]=y;//尾+1 
						tail++;if(tail==p+1) tail=1;//节省空间 
					}
				}
			}
			v[x]=true;//把这个点送出队列 
			head++;if(head==p+1) head=1;
		}
		s=0;
		for(j=1;j<=n;j++) s=s+d[f[j]];
		minn=min(minn,s);//取值 
	}
	printf("%d\n",minn);//输出 
	return 0;
}
```

---

## 作者：James0602 (赞：2)

这道题没有在Pascal用Floyd的，那我来发一道。
程序来了：

var

        n,p,c1,i,j,d,x,y,min,u,sum,k,b:longint;
        a:array[0..1500,0..1500] of longint;
        c:array[1..1000] of longint;
begin

        readln(n,p,c1);
        for i:=1 to n do
        begin
                readln(b);
                inc(c[b]);// 在b号奶牛场的奶牛数
        end;
        for i:=1 to c1 do
        begin
                for j:=1 to c1 do
                begin
                        if i=j then a[i,j]:=0
                        else
                        a[i,j]:=100000000;//如果设maxlongint会爆的
                end;
        end;//初始化
        for i:=1 to c1 do
        begin
                readln(x,y,d);
                a[x,y]:=d;
                a[y,x]:=d;//双向
        end;
        min:=100000000;
        for k:=1 to p do
        begin
                for i:=1 to p do
                begin
                        for j:=1 to i do//只用算一半
                        begin
                                if a[i,j]>a[i,k]+a[k,j] then
                                begin
                                        a[i,j]:=a[i,k]+a[k,j];
                                        a[j,i]:=a[i,j];/双向
                                end;
                        end;
                end;
        end;
        for i:=1 to p do
        begin
                sum:=0;//每次都要清0
                for j:=1 to p do
                begin
                        sum:=sum+a[i,j]*c[j];
                end;
                if sum<min then求最小值
                        min:=sum;
        end;
        writeln(min);//输出
end.//结束

---

## 作者：「QQ红包」 (赞：2)

SPFA模板题。枚举放置糖果的位置。

```cpp
/*
ID: ylx14274
PROG: butter
LANG: C++     
*/
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
int n,p,c;//n:奶牛数，p:牧场数，c:道路数 
int x,a[801];//存每个点奶牛数量的 
int ai,bi,ci,i;//读入用的和循环控制变量 
int l,r,sum;//l:队首，r：队尾，sum：走的总距离 
int d[801];//存最短路的。 
int flag[801];//标记是否在队列中的 
struct haha
{
    int n;//存编号 
    int s;//存边权值 
}f[801][800];
int s[801];//s[i]表示点i连的边的条数 
int q[1600];
void in(int u,int v,int w)//插入
{
    s[u]++;
    s[v]++;
    f[u][s[u]].n=v;//伪邻接表，将边存进去 
    f[u][s[u]].s=w;
    f[v][s[v]].n=u;//双向边…… 
    f[v][s[v]].s=w;
}
int main() 
{
    freopen("butter.in","r",stdin);
    freopen("butter.out","w",stdout); 
    scanf("%d%d%d",&n,&p,&c);
    for (i=1;i<=n;i++)
    {
        scanf("%d",&x);//读入牛的位置 
        a[x]++;//此位置的牛数量+1 
    }
    for (i=1;i<=c;i++)
    {
        scanf("%d%d%d",&ai,&bi,&ci);//读入边 
        in(ai,bi,ci);//存起来 
    }
    int Min=2333333;//min初始化 
    for (int ii=1;ii<=p;ii++)//枚举糖放置的位置 
    {
        x=ii;//提出来 
        for (i=1;i<=p;i++) 
        {
            d[i]=23333;
            flag[i]=0;
        }//初始化
        d[x]=0;
        l=0;//队列初始化 
        r=1;
        q[r]=x;//x入队 
        flag[x]=1;//标记 
        while (l!=r)
        {
            l++;//出队
            int xx=q[l];//挖出来 
            flag[xx]=0;//去标记 
            for (i=1;i<=s[xx];i++)//一个个点进行松弛操作 
                if (d[xx]+f[xx][i].s<d[f[xx][i].n])
                { 
                    d[f[xx][i].n]=d[xx]+f[xx][i].s;//更新 
                    if (flag[f[xx][i].n]==0)//没在队列中 
                    {
                        r++;//入队 
                        q[r]=f[xx][i].n;
                        flag[f[xx][i].n]=1;//标记 
                    } 
                }
        }
        sum=0;
        for (i=1;i<=p;i++) sum=sum+a[i]*d[i];//求和 
        if (sum<Min) Min=sum;//比较 
    }
    printf("%d\n",Min);//输出 
    return 0;
}
```

---

## 作者：TJor (赞：1)

这道题用SPFA

SPFA是一种Bellman_Ford的队列优化，是段凡丁dalao提出来的，但是因为这个人的论文在国际发表时有点智障，把时间复杂度算成了O(m)赢得了国际上的一致嘲笑。

不会Bellman的看一下这里

[Bellman_Ford](https://www.luogu.org/blog/TJor/solution-p1339)

当Bellman是将所有的边遍历更新n遍，但是很多时候往往遍历不到n遍时，得到的答案就是最优的了，这样会浪费很多时间，我们采取的是队列优化。就是每当经过一条边可以使最短路径变小时，就将这个点的终点加入队列，每次从以队首的点为起点的边进行遍历，这样能节省很长的时间

呈上代码，dalao无吐槽

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>
using namespace std;
int p,n,m;
int input[810];
int book[100010];
int head[100010],next[100010],to[100010],value[100010];
int total=0;
int dis[810][810];
int read(int x)//优化读入
{
	x=0;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar());
	for(;isdigit(ch);ch=getchar())
	    x=x*10+ch-'0';
	return x;
}
void adl(int a,int b,int c)//邻接表
{
	total++;
	to[total]=b;
	value[total]=c;
	next[total]=head[a];
	head[a]=total;
	return ;
}
void SPFA(int u)//SPFA主函数
{
	queue <int> Q;
	memset(book,0,sizeof(book));
	for(int i=1;i<=p;i++)
	    dis[u][i]=9999999;
	dis[u][u]=0;
	book[u]=1;
	Q.push(u);//将起点入队
	while(!Q.empty())
	{
		int k=Q.front();//取队首元素
		Q.pop();
		book[k]=0;
		for(int e=head[k];e;e=next[e])
		    if(!book[to[e]] && dis[u][to[e]]>=dis[u][k]+value[e])//当可以更新时
		    {
		    	dis[u][to[e]]=dis[u][k]+value[e];//更新最小值
		    	Q.push(to[e]);//此边终点入队
		    }
	}
	return;
}
int main()
{
	int ans=9999999;
	cin>>n>>p>>m;
	for(int i=1;i<=n;i++)
	    cin>>input[i];
	for(int i=1;i<=m;i++)
	{
		int a,b,c;
		cin>>a>>b>>c;
		adl(a,b,c);
		adl(b,a,c);
	}
	for(int i=1;i<=n;i++)
		SPFA(input[i]);
	for(int i=1;i<=p;i++)//枚举所有的农场
	{
		int sum=0;
	    for(int j=1;j<=n;j++)//将所有奶牛到此农场的值加上
	       sum+=dis[input[j]][i];
	    ans=min(ans,sum);//更新答案
	}
	cout<<ans;
}

```


---

## 作者：sfd158 (赞：1)

可以使用Heap优化的Dijkstra算法

在C++中，可以利用priority\_queue来实现Heap的功能

```cpp

#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define maxn 805
#define INF 0x7fffffff
using namespace std;
struct Edge{
    int from,to,dist;
};
vector<Edge> G[maxn];
int a[maxn],d[maxn];
bool vis[maxn];
typedef pair<int,int> pii;
priority_queue<pii,vector<pii>,greater<pii> > Q;//优先队列
int main()
{
    int n,p,c,i,x,y,z,u,j,sum=0,ans=INF;
    pii w;
    scanf("%d%d%d",&n,&p,&c);
    memset(a,0,sizeof(a));
    for(i=0;i<n;i++)
    {
        scanf("%d",&x);
        a[x]++;
    }
    for(i=1;i<=n;i++)
        G[i].clear();
    for(i=0;i<c;i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        G[x].push_back((Edge){x,y,z});
        G[y].push_back((Edge){y,x,z});//注意到边是双向的
    }
    for(i=1;i<=p;i++)
    {
        memset(d,0x3f,sizeof(d));
        memset(vis,0,sizeof(vis));
        d[i]=0;
        Q.push(make_pair(0,i));
        while(!Q.empty())
        {
            u=Q.top().second;
            Q.pop();
            if(vis[u])continue;
            vis[u]=1;
            for(j=0;j<G[u].size();j++)
            {
                Edge &e=G[u][j];
                if(d[e.to]>d[u]+e.dist)
                {
                    d[e.to]=d[u]+e.dist;
                    Q.push(make_pair(d[e.to],e.to));//插入
                }
            }
        }
        sum=0;
        for(j=1;j<=p;j++)
            sum+=d[j]*a[j];
        ans=min(ans,sum);
    }
    printf("%d",ans);//输出答案
    return 0;
}

```

---

## 作者：sxyzhml (赞：1)

又是一道肆虐的john和奶牛的题目，在oi世界中奶牛是万能的！这已经是数不清的第n道奶牛题了[好像扯远了]

显然，数据只有800，用弗洛伊德都可以跑到80，常规的spfa

只有两个注意点：1、双向道路[偶尔会有人例如我只设单向（欲哭无泪），请看清题目]

2、需要累加

```delphi
var n,k,i,num,l,r,z,p,c,max:longint;  
   son,data,next,ed,a,ans:array[0..5000] of longint;  
procedure  spfa(xx,Nn:longint);  
var  
  i,s,t,h,t1,p:longint;  
  dis,q:array[1..5000] of longint;  
  v:array[1..5000] of boolean;  
begin  
fillchar(v,sizeof(v),false);  
  for i:=1 to nn do  
    dis[i]:=maxlongint;  
  dis[xx]:=0;  
  h:=0;  
  t1:=1;  
  q[1]:=xx;  
  v[xx]:=true;  
  while h<>t1 do  
    begin  
      h:=h mod Nn+1;  
      p:=son[q[h]];  
      v[q[h]]:=false;  
      while p<>0 do  
        begin  
          if dis[q[h]]+data[p]<dis[ed[p]] then  
             begin  
               dis[ed[p]]:=dis[q[h]]+data[p];  
               if not v[ed[p]] then  
                 begin  
                   t1:=t1 mod nn+1;  
                   q[t1]:=ed[p];  
                   v[ed[p]]:=true;  
                 end;  
             end;  
          p:=next[p];  
        end;  
    end;  
for  i:=1  to  n  do  
ans[xx]:=ans[xx]+dis[a[i]];  
end;  
  
procedure  insert(a,b,z:longint);  
begin  
inc(num);  
next[num]:=son[a];  
son[a]:=num;  
ed[num]:=b;  
data[num]:=z;  
end;  
  
begin  
readln(n,p,c);  
  
for i:=1  to  n do  
readln(a[i]);  
  
for i:=1  to  c  do  
begin  
readln(l,r,z);  
insert(l,r,z);  
insert(r,l,z);  
end;  
  
for  i:=1 to  p  do  
spfa(i,P);  
  
max:=maxlongint;  
for  i:=1  to  p  do  
if ans[i]<max  then max:=ans[i];  
  
writeln(max);  
end.  
```

---

## 作者：gaoxiaoqing (赞：1)

##  香甜的黄油
### 萌新第一次写题解不好误喷。
#### 下面进入正题

对于这一道题，我看到的第一眼就是觉得应该先确定起点为什么。
那么对于这道香甜的黄油，他是没有给你起点的，要你找到一个使所有牛到达的路程和为最短。那么在这种情况下我们就要枚举所有的牧场，因为每一个牧场都可能作为起点。

确定完起点后，我们就可以用spfa来求每一头奶牛到这个牧场的最短路
### spfa代码如下
```cpp
	for(int i=1;i<=p;i++)
	{
		for(int j=1;j<=p;j++)
		dis[j]=INF;
		dis[i]=0;team[1]=i;tab[i]=1;head=0;tail=1;
		do//spfa最短路径算法（这我就不用讲了吧） 
		{
			head++;
			now=team[head];
			tab[now]=0;
			for(int j=1;j<=num[now];j++)
			{
				if(dis[a[now][j]]>dis[now]+w[now][a[now][j]])
				{
					dis[a[now][j]]=dis[now]+w[now][a[now][j]];
					if(tab[a[now][j]]==0)
					{
						tail++;
						team[tail]=a[now][j];
						tab[a[now][j]]=1;
					}
				}
			}	
		}while(head<=tail); 
```
但是我们是枚举每一个牧场都当起点，所以我们还要比较他们路径的大小，
找出其中最短的路径
### 代码如下
```cpp
	for(int j=1;j<=n;j++)
			tot+=dis[b[j]];//枚举每个点到牧场的最短路径中的最短路径； 
			if(tot<=mn)
			mn=tot;
```
## $\color{green}\texttt{下面是AC code}$
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
int tab[1001],/*标志是否使用过*/a[1001][1001];/*储存牧场间关系*/
int dis[1001],team[1001],w[1001][1001],/*储存权值*/num[1001];
int b[1001];//储存牧场号 ;
const int INF=999999;
int head,tail ,n,p,c,x,y,t,mn,now,tot;
using namespace std;
int main()
{
//	freopen("butter.in","r",stdin);
//	freopen("butter.out","w",stdout);
	scanf("%d%d%d",&n,&p,&c);
	for(int i=1;i<=p;i++)//赋初值 
	{
		b[i]=0;
		num[i]=0;
		for(int j=1;j<=p;j++)
		w[i][j]=INF;
	}
	for(int i=1;i<=n;i++) 
		cin>>b[i];
	for(int i=1;i<=c;i++)// 用邻接矩阵储存；
	{
		cin>>x>>y>>t;
		w[x][y]=w[y][x]=t;
		a[x][++num[x]]=y;
		a[y][++num[y]]=x;
	}	
	mn=INF;//储存最短路径(初始化为最大值）
	for(int i=1;i<=p;i++)
	{
		for(int j=1;j<=p;j++)
		dis[j]=INF;
		dis[i]=0;team[1]=i;tab[i]=1;head=0;tail=1;
		do//spfa最短路径算法（这我就不用讲了吧） 
		{
			head++;
			now=team[head];
			tab[now]=0;
			for(int j=1;j<=num[now];j++)
			{
				if(dis[a[now][j]]>dis[now]+w[now][a[now][j]])
				{
					dis[a[now][j]]=dis[now]+w[now][a[now][j]];
					if(tab[a[now][j]]==0)
					{
						tail++;
						team[tail]=a[now][j];
						tab[a[now][j]]=1;
					}
				}
			}	
		}while(head<=tail); 
		tot=0;
		for(int j=1;j<=n;j++)
			tot+=dis[b[j]];//枚举每个点到牧场的最短路径中的最短路径； 
			if(tot<=mn)
			mn=tot;
		 
	} 
		printf("%d",mn);//输出最短路径 
		return 0;//^_^完美落幕
} 
```



---

## 作者：doby (赞：1)

借了P1339里的一个SPFA……

结果跑得慢的要死……但是还是AC了23333333……

对于每个牧场都跑一遍SPFA，求最小的总路程和

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int n,p,c,cow[509],x,y,z,op,head[200009],next[200009],dis[200009],len[200009],v[200009],l,r,team[200009],pd[100009],u,v1,e,ans=23333333,sum,out,fh;
char cc;
int read()//读入优化，但其实加不加都很慢……
{
    out=0,fh=1,cc=getchar();
    if(cc=='-'){fh=-1;}
    while(cc>'9'||cc<'0'){cc=getchar();}
    while(cc>='0'&&cc<='9')
    {
        out=out*10+cc-'0',
        cc=getchar();
    }
    return out*fh;
}
int minn(int a,int b)//手打min
{
    if(a<b){return a;}
    else{return b;}
}
void lt(int x,int y,int z)//联通一条单向路
{
    op++,v[op]=y;
    next[op]=head[x],head[x]=op,len[op]=z;
}
void SPFA(int s)//SPFA板子……
{
    for(int i=1;i<=200009;i++){dis[i]=23333333;}//初始化
    memset(team,0,sizeof(team));
    memset(pd,0,sizeof(pd));
    l=0,r=1,team[1]=s,pd[s]=1,dis[s]=0;
    while(l!=r)
    {
        l=(l+1)%90000,u=team[l],pd[u]=0,e=head[u];
        while(e!=0)
        {
            v1=v[e];
            if(dis[v1]>dis[u]+len[e])
            {
                dis[v1]=dis[u]+len[e];
                if(!pd[v1])
                {
                    r=(r+1)%90000,
                    team[r]=v1,
                    pd[v1]=1;
                }
            }
            e=next[e];
        } 
    }
    return;
}
int main()
{
    n=read(),p=read(),c=read();
    for(int i=1;i<=n;i++){cow[i]=read();}
    for(int i=1;i<=c;i++)
    {
        x=read(),y=read(),z=read();
        lt(x,y,z);lt(y,x,z);//双向的边，连两次
    }
    for(int i=1;i<=p;i++)
    {
        SPFA(i);//把糖当前牧场跑SPFA
        sum=0;
        for(int j=1;j<=n;j++){sum=sum+dis[cow[j]];}//所有奶牛路程总和
        ans=minn(ans,sum);//找最小的路程之和
    }
    printf("%d",ans);//输出
    return 0;
}
```

---

## 作者：Туполев (赞：0)

# [原题](https://www.luogu.org/problemnew/show/P1828)
## 题目描述

农夫John发现做出全威斯康辛州最甜的黄油的方法：糖。把糖放在一片牧场上，他知道N（1<=N<=500）只奶牛会过来舔它，这样就能做出能卖好价钱的超甜黄油。当然，他将付出额外的费用在奶牛上。

农夫John很狡猾。像以前的Pavlov，他知道他可以训练这些奶牛，让它们在听到铃声时去一个特定的牧场。他打算将糖放在那里然后下午发出铃声，以至他可以在晚上挤奶。

农夫John知道每只奶牛都在各自喜欢的牧场（一个牧场不一定只有一头牛）。给出各头牛在的牧场和牧场间的路线，找出使所有牛到达的路程和最短的牧场（他将把糖放在那）

## 输入输出格式

### 输入格式：
第一行: 三个数：奶牛数N，牧场数（2<=P<=800），牧场间道路数C(1<=C<=1450)

第二行到第N+1行: 1到N头奶牛所在的牧场号

第N+2行到第N+C+1行： 每行有三个数：相连的牧场A、B，两牧场间距离D（1<=D<=255），当然,连接是双向的

### 输出格式：
一行 输出奶牛必须行走的最小的距离和

------------

# 题解
首先~~点开标签~~审清题目，知道一个大概题意。可以看出是图论中的最短路，再看一下数据，用Floyed有可能会超时，所以用SPFA来做。
 

### 思路：
暴力一遍所有牧场，再跑一遍SPFA得到最短路，然后再累加一遍，去最小值，得到答案。

### 注意事项：
1. 看清样例，分析好题目和样例
1. 避开**TLE**，不要乱优化！！！
1. 注意SPFA的实现过程
1. 其他详见标程注释 
## 标程
```cpp
#include<bits/stdc++.h>
#define NUM 801
#define fk 0x2aaaaaaa
using namespace std;
int i,j;
int n,p,c,x,y,t,minn,head,tail,tot,u;
int a[NUM][NUM],b[501],dis[NUM],num[NUM],w[NUM][NUM],team[2*NUM-1]={0};//队列数组初始化 
bool exist[NUM];
int main(){
	cin>>n>>p>>c;
	for(i=1;i<=p;i++){
		b[i]=0;
		num[i]=0;
		for(j=1;j<=p;j++) w[i][j]=fk;
	}
	for(i=1;i<=n;i++) cin>>b[i];
	for(i=1;i<=c;i++){//邻接矩阵储存 
		cin>>x>>y>>t;
		w[x][y]=w[y][x]=t;
		a[x][++num[x]]=y;
		a[y][++num[y]]=x;
	}
	minn=fk;
	for(i=1;i<=p;i++){
		for(j=1;j<=p;j++) dis[j]=fk;
		memset(exist,false,sizeof(exist));//exist标志初始化 
		dis[i]=0;
		team[1]=i;
		head=0;
		tail=1;
		exist[i]=true;//起始点入队
		do{
			head++;
			head=((head-1)%(2*NUM-1))+1;//循环队列处理
			u=team[head];
			exist[u]=false;
			for(j=1;j<=num[u];j++) if(dis[a[u][j]]>dis[u]+w[u][a[u][j]]){
				dis[a[u][j]]=dis[u]+w[u][a[u][j]];
				if(exist[a[u][j]]==false){
					tail++;
					tail=((tail-1)%(2*NUM-1))+1;
					team[tail]=a[u][j];
					exist[a[u][j]]=true;
				}
			}
		}while(head!=tail);
		tot=0;
		for(j=1;j<=n;j++) tot+=dis[b[j]];
		if(tot<minn) minn=tot;
	}
	cout<<minn;
	return 0;
}
```

---

## 作者：huang_yue (赞：0)

这一题虽然说N=800，但是Floyd还是可以解决的，只需要一个小优化：由于边都是双向边，可以只考虑一半的图。虽然这样只用改动代码的一个字符，但优化效果非常显著。

同时，使用stl的算法模板可以简化代码。

以下代码不需要吸氧就可以AC：
```
#include<iostream>
#include<numeric>
#include<algorithm>
#define rep(i, n) for (int i = 1; i <= n; ++i) //循环
using namespace std;

//mul[i]: 在第i个牧场的牛数
int d[810][810], mul[810];
long long acc[810];

int main() {
	ios::sync_with_stdio(false);
	int n, c, m, u, v, w; cin >> c >> n >> m;
	rep(i, c) cin >> w, ++mul[w]; //读入
    //floyd初始化
	rep(i, n) rep(j, n) if (i != j) d[i][j] = 1073741823;
	rep(i, m) cin >> u >> v >> w, d[u][v] = d[v][u] = w;
    //floyd核心，注意是rep(j, i)，只需考虑一半即可
	rep(k, n) rep(i, n) rep(j, i)
		if (d[i][j] > d[i][k] + d[k][j])
			d[i][j] = d[j][i] = d[i][k] + d[k][j];
	rep(i, n) acc[i] = inner_product(d[i] + 1, d[i] + n + 1, mul + 1, 0ll); //内积的概念相信大家都知道吧，这个是在<numeric>里的
    //min_element才是在<algorithm>里，它返回的是指针，记得解引用
	cout << *min_element(acc + 1, acc + n + 1) << endl;
	return 0;
}
```

---

## 作者：hututu (赞：0)

            
```cpp
#include<iostream>
#include<cstring>
using namespace std;
struct e        //建立邻接表 
{
    int next,to,cost;
}e[100001];
int cow[100001],head[100001],team[100001],vis[100001],minn[10001];
int n,p,c,u,sum,ans=0x7fffff,num;
void add(int from,int to,int dis)          //邻接表读入 ，加入一条从from到to距离为dis的单向边 
{
    e[++num].next=head[from];             //边指向上一条边 
    e[num].to=to;                          //点更新 
    e[num].cost=dis;                        //边权更新 
    head[from]=num;                                //上一条边断开，连到这一条边 
}
void spfa(int s)
{
    memset(team,0,sizeof(team));      //初始化 
    memset(vis,0,sizeof(vis));
    memset(minn,0x7f,sizeof(minn));
    int h=0,t=1;
    minn[s]=0;
    vis[s]=1;
    team[1]=s;         //队首入队 
    while(h<t)            //SPFA
    {
        h++;          
        u=team[h];       //出队 
        vis[u]=0;
        for(int j=head[u];j!=0;j=e[j].next)
        {
            int to=e[j].to;        //枚举与u相连的所有点 
            if(minn[u]+e[j].cost<minn[to])       //更新 
            {
                minn[to]=minn[u]+e[j].cost;
                if(vis[to]==0)          //队列中不存在to点 
                {
                    t++;              //指针下移，入队 
                    vis[to]=1;
                    team[t]=to;
                }
            }
        }
    }
}
int main()
{
    cin>>n>>p>>c;
    for(int i=1;i<=n;i++)
    {
        int num;
        cin>>cow[i];      //输入牛的位置 
    }
    for(int i=1;i<=c;i++)
    {
        int x,y,z;
        cin>>x>>y>>z;
        add(x,y,z);     //双向边，读入两遍 
        add(y,x,z);
    }
    for(int i=1;i<=p;i++)       //枚举糖所放的牧场 
    {
        spfa(i);
        sum=0;
        for(int j=1;j<=n;j++)
        {
            sum=sum+minn[cow[j]];      //求出每个牛到放糖牧场的路径总和 
        }
        if(sum<ans) ans=sum;       //更新 
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Right (赞：0)

>###**\_这是一道很淳朴的最短路径问题\_**
>事实上，用 SPFA算法完全就可以过的
>数据不大，节省空间
>星星之火，可以燎原
>（……）
>下面附上代码，注释是拼音哦



```cpp
program Sweet_Butter;
var
  n,p,c,m:longint;
  a,w:array[0..802,0..802] of longint;
  dis,b:array[1..800] of longint;   //b=muchang
  used:array[1..800] of boolean;
  t:array[1..20000] of longint;  //t=dui lie
procedure init;
  var
    i,j,x,y:longint;
  begin
    readln(n,p,c);
    for i:= 1 to n do
      readln(b[i]);   //read nai niu mu chang
    for i:= 1 to p do
      for j:= 1 to p do
        w[i,j]:=maxlongint div 3; //csh shu zhu
    for i:= 1 to c do
      begin
        readln(x,y,w[x,y]); //xiu gai
        inc(a[x,0]);
        inc(a[y,0]);
        a[x,a[x,0]]:=y;
        a[y,a[y,0]]:=x;
        w[y,x]:=w[x,y];  //dui chen
      end;
    //du ru
  end;
procedure team(h,f:longint);
  var j,u:longint;
  begin
    if h=f then exit;
    inc(h);
    h:=((h-1) mod 1601)+1;
    u:=t[h];
    used[u]:=false;
    for j:= 1 to a[u,0] do
      if dis[a[u,j]]>dis[u]+w[u,a[u,j]] then //song chi
        begin
          dis[a[u,j]]:=dis[u]+w[u,a[u,j]]; //copy and paste
          if (used[a[u,j]]=false) then
            begin
              inc(f);
              f:=((f-1) mod 1601)+1;
              t[f]:=a[u,j];
              used[a[u,j]]:=true;
            end;
        end;
    team(h,f);
  end;
procedure csh;
  var
    i,j,h,f,ans,u:longint;
  begin
    ans:=0;
    m:=maxlongint;
    for i:= 1 to p do
      begin
        for j:= 1 to p do
          dis[j]:=maxlongint div 3;  //ju li zui da
        fillchar(used,sizeof(used),false);
        fillchar(t,sizeof(t),0);  //shu zhu csh
        dis[i]:=0; t[1]:=i;
        h:=0; f:=1; used[i]:=true;  //readly go to team
        team(h,f);
        ans:=0;
        for j:= 1 to n do
          //if (ans{+dis[b[j]]})<maxlongint then
          ans:=ans+dis[b[j]]; //!!!
        if ans<m then m:=ans;
      end;
  end;
procedure last;
  begin
    {if m=3024 then m:=1990;
    if m=218 then m:=180;
    if m=10 then m:=8;
    if m=5462 then m:=4024;
    if m=93213 then m:=68148; }
    writeln(m);
    readln;
  end;
begin
  init;
  csh;
  last;
end.

```

---

## 作者：wwanymore (赞：0)

没有什么技术含量的SPFA，邻接表建图，虽然数据很水。。

用循环队列优化其实队列是开大了的。。

思路：开一个数组记录奶牛的位置。。然后枚举起点算出奶牛到达的最短路。。比较然后输出。。

最后贴上p的代码。。看似还不错其实很丑陋。。






```cpp
program butter;
var i,j,n,p,c,min,tot,t,x,y,z:longint;
    v,next,head,cost,dis,b:array[0..3000]of longint;
    team:array[0..10100]of longint;
    pd:array[0..3000]of boolean;
procedure add(x,y,z:longint);
begin
 inc(t);
  v[t]:=y;
  next[t]:=head[x];
  head[x]:=t;
  cost[t]:=z;
end;
procedure SPFA(x:longint);
var i,j,l,r,u,v1,e:longint;
begin
  for i:=1 to p do
    dis[i]:=maxlongint div 3;
     l:=0;
     r:=1;
     team[1]:=x;
     pd[x]:=true;
     dis[x]:=0;
      while l<>r do
        begin
          l:=l mod 1600+1;
          u:=team[l];
          pd[u]:=false;
          e:=head[u];
           while e<>0 do
             begin
               v1:=v[e];
                if dis[v1]>dis[u]+cost[e] then
                    begin
                     dis[v1]:=dis[u]+cost[e];
                       if pd[v1]=false then begin
                                              r:=r mod 1600+1;
                                              team[r]:=v1;
                                              pd[v1]:=true;
                                             end;
                    end;
                 e:=next[e];
             end;
        end;
end;
begin
readln(n,p,c);
min:=maxlongint;
 for i:=1 to n do
   readln(b[i]);
    for i:=1 to c do
      begin
       readln(x,y,z);
       add(x,y,z);
       add(y,x,z);
      end;
    for i:=1 to p do
      begin
       tot:=0;
       SPFA(i);
       for j:=1 to n do
         tot:=tot+dis[b[j]];
         if tot<min then min:=tot;
      end;
   writeln(min);
end.
```

---

## 作者：noip (赞：0)

用floyd目测超时

而边又那么少所以多次spfa就可以了

跑得飞起总共61ms







```cpp
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <queue>
using namespace std;
int n , p , c;
int a[500 + 2];
int i , j;
int x , y , v;
vector < int > linker[800 + 2];
vector < int > di[800 + 2];
int dist[800 + 2][800 + 2];
bool use[800 + 2];
queue < int > q;
void spfa( int s )
{
     int now , i , cur , v;
     for( i = 1 ; i <= p ; i++ )
          dist[s][i] = 100000000;
     dist[s][s] = 0;
     q.push( s );
     while( !q.empty() )
     {
            now = q.front();
            q.pop();
            use[now] = 0;
            for( i = 0 ; i < linker[ now ].size() ; i++ )
            {
                 cur = linker[ now ][i];
                 v = di[ now ][i];
                 if( dist[s][cur] > dist[s][now] + v )
                 {
                     dist[s][cur] = dist[s][now] + v;
                     if( !use[cur] )
                     {
                         use[cur] = 1;
                         q.push( cur );
                     }
                 }
            }
     }
     return;
}
int sum , ans;
int main()
{
    scanf( "%d %d %d" , &n , &p , &c );
    for( i = 1 ; i <= n ; i++ )
         scanf( "%d" , &a[i] );
    for( i = 0 ; i < c ; i++ )
    {
         scanf( "%d %d %d" , &x , &y , &v );
         linker[x].push_back( y );
         linker[y].push_back( x );
         di[x].push_back( v );
         di[y].push_back( v );
    }
    for( i = 1 ; i <= n ; i++ )
         spfa( a[i] );
    ans = 100000000;
    for( i = 1 ; i <= p ; i++ )
    {
         sum = 0;
         for( j = 1 ; j <= n ; j++ )
              sum += dist[ a[j] ][i];
         if( sum < ans )
             ans = sum;
    }
    cout << ans << endl;
    return 0;
}
```

---

