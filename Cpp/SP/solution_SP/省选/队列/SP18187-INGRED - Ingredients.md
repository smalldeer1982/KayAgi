# INGRED - Ingredients

## 题目描述

 You are given **n** cities with **m** bi-directional roads connecting them and the length of each road. There are two friends living in different cities who wish to collect some ingredients available at different stores to make cake. There are s such stores. They need not come back home after purchasing the ingredients. Petrol is expensive and they would hence like to travel minimum total distance (sum of distance distance traveled by both kids). Help them find out what this distance is.

# 题解

## 作者：旋转卡壳 (赞：2)

```cpp
//爆搜
/*
外国友人的数据
5 6 
0 1 5 
0 2 2 
0 4 10 
1 3 5 
1 2 3 
1 4 10 
3 
2 4 3 
0 1 
ANS->19
*/
#pragma GCC optimize (2)
#pragma G++ optimize (2)
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;
//数组开大点 第一次交RE 第二次交数组开2倍AC QAQ
const int maxn=1e3+50; //最多点
const int maxm=(maxn<<1); //最多边
const int maxs=((1<<9)+50); //拥有材料的最多种情况
//范围为00000000~11111111(二进制) 开大点 准没错

int n,m,s,s1,s2;
int e[10]; //e[i] 2的i次幂
int tag[maxn]; //tag[u]=i 代表u结点有第i个材料
//二进制为1<<(i-1) 如有第三个材料就是100

inline int read() 
{	int a=0;char c=getchar();
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9') a=(a<<3)+(a<<1)+c-'0',c=getchar();
    return a;
}

int edgeNum,head[maxn],next[maxm],to[maxm],w[maxm];

inline void add_edge(int u,int v,int c)
{	next[++edgeNum]=head[u];head[u]=edgeNum;
    to[edgeNum]=v;w[edgeNum]=c;
}

int dis[maxs][maxn],vis[maxs][maxn]; //dis vis辅助spfa
//开二维的原因(精髓)在上面说了0 0
int dis1[maxs],dis2[maxs];
//dis1[1001](二进制) 表示s1出发的人得到第4个材料和第1个材料的最小距离

queue< pair<int,int> > Q;
//first存材料 second存到的点

int tim; //spfa的次数

inline void spfa()
{	while(!Q.empty())
    {	pair<int,int> p=Q.front();Q.pop();
        int u=p.first,got=p.second;vis[got][u]=0; //got为原有材料
        for(int i=head[u];i!=-1;i=next[i])
            if(tag[to[i]]) //如果这个商店有材料 特殊对待
            {	int Got=(got|(1<<(tag[to[i]]-1)));
                //Got为经过该商店后拥有的材料 具体实现看代码
                if(dis[Got][to[i]]>dis[got][u]+w[i])
                {	dis[Got][to[i]]=dis[got][u]+w[i];
                    !tim?dis1[Got]=min(dis1[Got],dis[Got][to[i]]):dis2[Got]=min(dis2[Got],dis[Got][to[i]]);
                    //更新dis[Got]
                    if(!vis[Got][to[i]])
                        vis[Got][to[i]]=1,Q.push(make_pair(to[i],Got));
                }
            }else if(dis[got][to[i]]>dis[got][u]+w[i])
            {	dis[got][to[i]]=dis[got][u]+w[i];
                !tim?dis1[got]=min(dis1[got],dis[got][to[i]]):dis2[got]=min(dis2[got],dis[got][to[i]]);
                //更新dis[got]
                if(!vis[got][to[i]])
                    vis[got][to[i]]=1,Q.push(make_pair(to[i],got));
            }
    }
}

int main()
{	e[0]=1;for(register int i=1;i<9;++i) e[i]=e[i-1]<<1;
    n=read();m=read();
    for(register int i=0;i<=n;++i) head[i]=-1;
    for(register int i=1;i<=m;++i)
    {	int u=read(),v=read(),c=read();
        add_edge(u,v,c);add_edge(v,u,c);
    }s=read();
    for(register int i=1;i<=s;++i) tag[read()]=i;
    s1=read();s2=read();
    //以下作求dis1的预处理
    memset(dis,0x3f,sizeof(dis));
    memset(dis1,0x3f,sizeof(dis1));dis1[0]=0;
    if(tag[s1]) //如果起点有商店
    {	Q.push(make_pair(s1,e[tag[s1]-1]));
        dis[e[tag[s1]-1]][s1]=0;
    }else Q.push(make_pair(s1,0)),dis[0][s1]=0;
    spfa();
    //以下作求dis2的预处理
    ++tim;
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    memset(dis2,0x3f,sizeof(dis2));dis2[0]=0;
    if(tag[s2])
    {	Q.push(make_pair(s2,e[tag[s2]-1]));
        dis[e[tag[s2]-1]][s2]=0;
    }else Q.push(make_pair(s2,0)),dis[0][s2]=0;
    spfa();
    //输出部分
    int ans=2147483647;
    ans=min(dis1[e[s]-1],dis2[e[s]-1]); //判断一个人全拿完的情况
    for(register int i=1;i<e[s];++i)
        ans=min(ans,dis1[i]+dis2[i^(e[s]-1)]);
        //枚举 具体实现看代码 两个人拿的异或起来肯定是11111(s-1个1)
    printf("%d",ans);
    return 0;
}
```

---

## 作者：2018ljw (赞：0)

虽然这题 $s\le 8$ 能放过 $s!$ 甚至更慢的爆搜，但我们还是要知道一些相对优秀的做法，比如 dp。

首先跑一遍 Floyd 求出点对之间的最短路。记必须经过的城市序列为 $a$，若两个起点不在 $a$ 中则将其加入。设第一个人的起点城市在 $a$ 中的下标为 $i_1$，第二个人的为 $i_2$。

设 $\mathit{dp}_{S,l1,l2}$ 表示目前已经遍历点集 $S$，第一个人当前在 $a_{l1}$，第二个人当前在 $a_{l2}$ 最小总路程。初值 $\mathit{dp}_{2^{i1}|2^{i2},i_1,i_2}=0$，其余均为正无穷。

转移时枚举点集，两个人位置和新到达的城市 $k$，那么有

$$
\begin{cases}\mathit{dp}_{S|2^k,x,k}\leftarrow \mathit{dp}_{S,x,y}+dis(a_y,a_k)\\\mathit{dp}_{S|2^k,k,y}\leftarrow \mathit{dp}_{S,x,y}+dis(a_x,a_k)\end{cases}
$$

其中转移部分需要和原数取 $\min$。

答案即为 $\min\{\mathit{dp}_{2^{|a|}-1,x,y}\}$。

由于初始节点必定被遍历，对应的二进制位必须为 $1$，故合法状态只有 $2^s$ 个，总复杂度 $O(2^{s}s^3)$。
```cpp
const int inf=1e9;
int n,d[101][101];
int s,a[10];
bool ip[101];
int dp[1024][10][10];
int main(){
    int i,j,k,l,m;
    scanf("%d%d",&n,&m);
    memset(d,0x3f,sizeof(d));
    for(i=1;i<=n;i++)d[i][i]=0;
    while(m--){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        x++;y++;
        d[x][y]=d[y][x]=min(d[x][y],z);
    }
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            for(k=1;k<=n;k++)d[j][k]=min(d[j][k],d[j][i]+d[i][k]);
        }
    }
    scanf("%d",&s);
    for(i=0;i<s;i++){
        scanf("%d",&a[i]);a[i]++;
        ip[a[i]]=1;
    }
    int pa,pb;
    scanf("%d%d",&pa,&pb);pa++;pb++;
    if(!ip[pa])ip[pa]=1,a[s++]=pa;
    if(!ip[pb])a[s++]=pb;
    int ps=0,py=0;
    for(i=0;i<s;i++){
        if(a[i]==pa)ps=i;
        if(a[i]==pb)py=i;
    }
    memset(dp,0x3f,sizeof(dp));
    dp[(1<<ps)|(1<<py)][ps][py]=0;
    for(i=0;i<1<<s;i++){
        if(!(i&(1<<ps)))continue;
        if(!(i&(1<<py)))continue;
        for(j=0;j<s;j++){
            if(!(i&(1<<j)))continue;
            for(k=0;k<s;k++){
                if(!(i&(1<<k)))continue;
                if(dp[i][j][k]>=inf)continue;
                for(l=0;l<s;l++){
                    if(i&(1<<l))continue;
                    dp[i|(1<<l)][l][k]=min(dp[i|(1<<l)][l][k],dp[i][j][k]+d[a[j]][a[l]]);
                    dp[i|(1<<l)][j][l]=min(dp[i|(1<<l)][j][l],dp[i][j][k]+d[a[k]][a[l]]);
                }
            }
        }
    }
    int ans=inf;
    for(i=0;i<s;i++)for(j=0;j<s;j++)ans=min(ans,dp[(1<<s)-1][i][j]);
    printf("%d",ans);
}

```

---

## 作者：华为2X (赞：0)

昨天下午神犇学长[@SPiCa](https://www.luogu.org/space/show?uid=52435&myuid=86281&follow=1)临走前给我们留下这道神犇题目，然后...然后...一个晚上就栽在这里了[大哭]！


------------



让我们先来看一下题目：


##### You are given n cities with m bi-directional roads connecting them and the length of each road. There are two friends living in different cities who wish to collect some ingredients available at different stores to make cake. There are s such stores. They need not come back home after purchasing the ingredients. Petrol is expensive and they would hence like to travel minimum total distance (sum of distance distance traveled by both kids). Help them find out what this distance is.

什么鬼？？？English？？？

让我们看看神犇的解读
### 一张n个点m条边的无向图，图上有s个特殊点。有两个人从各自的起点a,b出发，要求他们经过的点并起来覆盖所有特殊点。求走过的最小总距离。

题目的毒瘤在于没有给出任何的测试数据和数据范围，更毒瘤的是SPOJ要翻墙才能注册账号。

简而言之，毒瘤题目，毒瘤OJ

还好神犇给了测试数据和数据范围[偷笑]

##### 输入格式 
##### 第一行包含两个数n,m,表示点数和边数
##### 接下来m行，每行包含3个数x,y,z表示x到y有一条长为z的双向边。点从0开始标号
##### 接下来一行包含一个整数s，表示特殊点数量
##### 接下来一行包含s个整数表示每个特殊点的编号
##### 接下来一行包含2个整数表示两个人的起点a,b
##### n<=100, m<=n(n-1)/2, s<=8, z≤1000

##### 测试数据
##### 5 6
##### 0 1 5
##### 1 4 1
##### 0 4 10
##### 0 2 2
##### 1 2 3
##### 2 3 4
##### 2
##### 2 4
##### 0 1
##### ANS
##### 3

直接上程序

```cpp
#include<cstdio>
#include<queue>
#define maxn 110//点数（昨晚开小了，调了一个晚上，肝）
#define maxm 5050//边数
#define inf 100000000//初始化最大值
#define M(x,y) make_pair(x,y)//用队列存数对
using namespace std;
int n,m,s,ans=inf;
int x,y,z;
int vis[maxn][300],d[maxn][300]；//vis/d[i][j]表示在第i个点经过二进制为j的最短路
int a[maxn];//用二进制记录特殊点
int gg[3][300];//gg[i][j]表示第i个人经过二进制为j的最短路
int h[maxm],num;
int sum=1;
struct node
{
	int v,next,l;
}hw[maxm];
void add(int x,int y,int z)
{
	hw[++num].v=y;
	hw[num].l=z;
	hw[num].next=h[x];
	h[x]=num;
	return ;
}//链式前向星存图
priority_queue< pair<int,int> > q;
void dfs(int k)//可能是spfa
{
	for(int i=1;i<=n;i++)
    for(int j=0;j<=sum;j++)
	 d[i][j]=inf,vis[i][j]=0;//初始化
	int t=a[k];
	d[k][t]=0;
	vis[k][t]=1;
	q.push(M(k,t));//数对入列，k是节点，t是二进制数
	int temp;
	while(!q.empty())
	 {
	  temp=q.top().first;//取出队首元素的节点
	  t=q.top().second;//取出队首元素的二进制数
	  q.pop();//队首元素出队
	  for(int i=h[temp];i;i=hw[i].next)
	   {
	   	int v=hw[i].v,tt=t;
	   	if(a[v]>0)
	   	 tt|=a[v];//用位运算增加经过的特殊点
	   	if(d[v][tt]>d[temp][t]+hw[i].l)//更新最短路
	   	 {
	   	  d[v][tt]=d[temp][t]+hw[i].l;
	   	  if(!vis[v][tt])//不在队列中则入队
	   	   {
	   	   	vis[v][tt]=1;
	   	   	q.push(M(v,tt));
		   }
		 }
	   }
	  vis[temp][t]=0;//该点已完成
	 }
	if(k==x)
	 {
	  for(int i=0;i<=sum;i++)
	   gg[1][i]=inf;//初始化
	  for(int i=1;i<=n;i++)
	   for(int j=0;j<sum;j++)
	    if(d[i][j]<gg[1][j])//存在d[i][j]或d[i][j]比g[][j]更小则更新
		 gg[1][j]=d[i][j];	
	 }//保存第一个人的最短路
	if(k==y)//同上
	 {
	  for(int i=0;i<=sum;i++)
	   gg[2][i]=inf;
	  for(int i=1;i<=n;i++)
	   for(int j=0;j<sum;j++)
	    if(d[i][j]<gg[2][j])
         gg[2][j]=d[i][j];	
	 }//保存第二个人的最短路
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	 scanf("%d%d%d",&x,&y,&z),add(x+1,y+1,z),add(y+1,x+1,z);//双向图，让点从1开始
	scanf("%d",&s);
	for(int i=1;i<=s;i++)
	 {
	  scanf("%d",&x);
	  if(a[x+1]>0)
	   continue ;//已经存在就不用再赋予二进制数
	  a[x+1]=sum;
	  sum=(sum<<1);
	 }//用二进制记录特殊点
	scanf("%d%d",&x,&y);
	x=x+1,y=y+1;//两个起点
	dfs(x);
	dfs(y);
/*	for(int i=1;i<=n;i++)
      cout<<gg[1][i]<<" ";
	cout<<endl;
	for(int i=1;i<=n;i++)
      cout<<gg[2][i]<<" ";
	cout<<endl;*///测试数据用的，懒得删了
	for(int i=0;i<sum;i++)
	 for(int j=0;j<sum;j++)
	  if((i|j)==(sum-1)&&gg[1][i]+gg[2][j]<ans)
	   ans=gg[1][i]+gg[2][j];//（i|j）==（sum-1）表示经过了所有的特殊点
    printf("%d\n", ans);//输出
	return 0;
}
```


------------
写在后面

关于spfa,还可以用双向队列优化，神犇用的是手写队列，
而我比较懒，~~反正queue也能AC[呲牙]~~

And，这道题，一个晚上，被我和另一位犇犇同学，硬生生的，从六提交三通过，变成了
十七提交五通过[奔泪]







---

